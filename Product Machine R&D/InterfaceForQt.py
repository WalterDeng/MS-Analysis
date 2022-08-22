import os
import numpy as np
import joblib
import pandas as pd

RT_tag = 'RT_start'   # value: 'RT_start' / 'RT_top' / 'RT_end'

def normalizeA(X):
    A_sum = np.sum(X, axis=1).reshape(-1, 1)
    X = np.nan_to_num(X / A_sum)
    return X

def get_Models():
    Models = set()
    for Model_name in os.listdir("saved_model\\"):
        tags = Model_name.split("_")
        Models.add(tags[0])

    Models = list(Models)

    return Models

def match_VOC_id(voc_data, peaks_info):
    """
    匹配voc信息
    :param voc_data: list
    :param peaks_info:
    :return:
    """
    error_code = 0
    error_str = "success"
    try:
        n_peaks = len(peaks_info)

        voc_data = pd.DataFrame(
            voc_data,
            columns=['VOC_ID_INTERNAL', 'CAS_NUMBER', 'RT_START', 'RT_END'])
        peaks_info = pd.DataFrame(peaks_info,
                                  columns=[
                                      'RT_start', 'RT_top', 'RT_end',
                                      'Peak_height', 'Peak_width', 'Peak_area'
                                  ])

        voc_data['RT_mid'] = (voc_data['RT_START'] + voc_data['RT_END']) / 2
        voc_data['RT_mid_width'] = (voc_data['RT_END'] -
                                    voc_data['RT_START']) / 2

        peaks_info['RT'] = peaks_info[RT_tag]

        # find the nearest voc
        dif_mat = peaks_info['RT'].values.reshape(
            -1, 1) - voc_data['RT_mid'].values.reshape([1, -1])
        dif_mat = abs(dif_mat)
        peaks_info['voc_id'] = np.argmin(dif_mat, axis=1)
        peaks_info['dif_value'] = dif_mat[np.arange(n_peaks),
                                          peaks_info['voc_id']]
        peaks_info['is_voc_ok'] = peaks_info[
                                      'dif_value'].values <= voc_data.loc[peaks_info['voc_id'],
                                                                          'RT_mid_width'].values
        peaks_info.loc[peaks_info['is_voc_ok'] == False, 'voc_id'] = -1

        # find the repeat voc
        counts = peaks_info['voc_id'].value_counts()
        repeat_vocs = list(counts[counts > 1].index)

        # handle the repeat voc
        peaks_info.loc[peaks_info['voc_id'].isin(repeat_vocs),
                       'is_voc_ok'] = False

        new_df = pd.DataFrame([])
        new_df['rt_mid_width'] = voc_data['RT_mid_width']
        peaks_info = pd.merge(peaks_info,
                              new_df,
                              how='left',
                              left_on='voc_id',
                              right_index=True)
        peaks_info['factor'] = (peaks_info['rt_mid_width'] - peaks_info['dif_value']) / peaks_info['rt_mid_width']
        peaks_info['factor'].replace(to_replace=0, value=0.01, inplace=True)
        peaks_info['height_proportion'] = peaks_info['Peak_height'] * peaks_info['factor']

        for voc in repeat_vocs:
            idx = peaks_info.loc[peaks_info['voc_id'] == voc,
                                 'height_proportion'].idxmax()
            peaks_info.loc[idx, 'is_voc_ok'] = True
            # handle the out points

        peaks_info.loc[peaks_info['is_voc_ok'] == False, 'voc_id'] = -1

        # merge the return data
        data_return = pd.merge(peaks_info,
                               voc_data,
                               how='left',
                               left_on='voc_id',
                               right_index=True)
        data_return.fillna("-", inplace=True)
        data_return = data_return[[
            'VOC_ID_INTERNAL', 'CAS_NUMBER', 'RT', 'Peak_area', 'Peak_height'
        ]]
        data_return = data_return.values.tolist()

    except Exception as ep:
        error_code = 1
        error_str = str(ep)
        data_return = []
    return error_code, error_str, data_return

def match_VOC_id_(voc_data, peaks_info):
    error_code = 0
    error_str = "success"
    try:
        peak_num = len(peaks_info)
        display_info = []
        for Index in range(peak_num):
            [_, RT, _, Peak_height, _, Peak_area] = peaks_info[Index]
            VOC_ID_INTERNAL = "-"
            CAS_NUMBER = "-"
            for row in voc_data:
                # 遍历VOC表
                [VOC_ID_INTERNAL_1, CAS_NUMBER_1, RT_START, RT_END] = row
                if RT >= RT_START and RT <= RT_END:
                    # 找到峰对应物质

                    if len(display_info) == 0:
                        VOC_ID_INTERNAL = VOC_ID_INTERNAL_1
                        CAS_NUMBER = CAS_NUMBER_1
                        break

                    [_, CAS_NUMBER_old, RT_old, _, _] = display_info[-1]

                    if CAS_NUMBER_old == CAS_NUMBER_1:
                        Rt_mid = (RT_START + RT_END) / 2
                        dif_old = abs(RT_old - Rt_mid)
                        dif_new = abs(RT - Rt_mid)
                        if dif_new < dif_old:
                            # 替换上个VOC的标签
                            display_info[-1][0] = "-"
                            display_info[-1][1] = "-"
                            VOC_ID_INTERNAL = VOC_ID_INTERNAL_1
                            CAS_NUMBER = CAS_NUMBER_1
                    else:
                        VOC_ID_INTERNAL = VOC_ID_INTERNAL_1
                        CAS_NUMBER = CAS_NUMBER_1
                    break
            display_info.append([VOC_ID_INTERNAL, CAS_NUMBER, RT, Peak_area, Peak_height])

    except Exception as ep:
        error_code = 1
        error_str = str(ep)
        display_info = []
    return error_code, error_str, display_info

def get_analysis_result(model_type, method_type, queues_path, queues_num, VOC_ids, cur_patient_info):
    error_code = 0
    error_str = "success"
    try:
        queue_num = len(queues_num)
        VOC_num = len(VOC_ids)
        MODEL_TAG = model_type + "_" + str(queue_num) + "_" + method_type

        X = pd.DataFrame([], columns=VOC_ids)
        Y = np.ones(sum(queues_num)+1, dtype=int)  # +1 代表当前病人

        cur_patient_biomarker = np.zeros(VOC_num)
        for i in range(VOC_num):
            for peak in cur_patient_info:
                # peak : [VOC_ID_INTERNAL, Index, CAS_NUMBER, RT, Peak_area, Peak_height]
                if peak[0] == VOC_ids[i]:
                    cur_patient_biomarker[i] = peak[4]

        X.loc[0] = list(cur_patient_biomarker)
        Y[0] = 0 # 当前病人类别默认为0

        j = 1
        for i in queues_num:
            j += i
            Y[j:] += 1
        Y = list(Y)

        # 读取队列病人信息
        for file_path in queues_path:
            file_df = pd.read_csv(file_path)
            file_df = list(np.array(file_df))
            X_df = pd.DataFrame([], columns=VOC_ids)
            X1 = np.zeros(VOC_num)
            for j in range(VOC_num):
                for peak in file_df:
                    # peak : [VOC_ID_INTERNAL, CAS_NUMBER, RT, Peak_area, Peak_height]
                    if peak[0] == VOC_ids[j]:
                        X1[j] = X1[j] + peak[4]
            X_df.loc[0] = list(X1)
            X = X.append(X_df)

        X = np.array(X)
        X = normalizeA(X)

        # 加载分析模式对应训练模型
        Model_name = "saved_model//" + MODEL_TAG + ".pkl"
        Model = joblib.load(Model_name)


        # 开始降维
        queue_points = Model.transform(X)

        points = queue_points.tolist()
    except Exception as ep:
        error_code = 1
        error_str = str(ep)
        points = []
        Y = []
    print("model_type: ", model_type)
    print("method_type: ", method_type)
    print("queues_path: ", queues_path)
    print("queues_num: ", queues_num)
    print("VOC_ids: ", VOC_ids)
    print("Y: ", Y)
    return error_code, error_str, points, Y
