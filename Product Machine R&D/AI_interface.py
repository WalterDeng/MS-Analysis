# 产品机AI界面接口定义

import os
import numpy as np
import joblib
import pandas as pd
from sql_util import *

def normalizeA(X):
    A_sum = np.sum(X, axis=1).reshape(-1, 1)
    X = np.nan_to_num(X / A_sum)
    return X

def get_Models():
    """
    获取所有模型标签（字符串）
    :return: [MODEL1, …]
    """
    Models = set()
    for Model_name in os.listdir("saved_model\\"):
        tags = Model_name.split("_")
        Models.add(tags[0])

    Models = list(Models)

    return Models


def match_VOC_id(voc_data, peaks_info):
    """
    对该次检测到的peak_infos进行VOC数据表的匹配，能匹配到的物质标记上VOC_ID_INTERNAL和CAS_NUMBER，匹配不上的物质VOC_ID_INTERNAL和CAS_NUMBER = "-"
    :param voc_data: VOCDATABASE表 中 VOC_ID_INTERNAL, CAS_NUMBER, RT_START, RT_END 字段对应数据
    :param peaks_info: [[峰起始位置, 峰顶点位置, 峰结束位置, 峰高, 半峰宽, 峰面积], ...]
    :return:
        error_code:0成功/1失败；
        error_str:"错误信息"；
        display_info： [[VOC_ID_INTERNAL, CAS_NUMBER, RT, Peak_area, Peak_height], ...]
    """
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
                    VOC_ID_INTERNAL = VOC_ID_INTERNAL_1
                    CAS_NUMBER = CAS_NUMBER_1
                    break

            display_info.append([VOC_ID_INTERNAL, CAS_NUMBER, RT, Peak_area, Peak_height])

    except Exception as ep:
        error_code = 1
        error_str = ep
        display_info = []
    return error_code, error_str, display_info

def get_analysis_result(model_type, method_type, queues_path, queues_num, VOC_ids, cur_patient_info):
    """
    获取模型分析结果
    :param model_type: 模型类别，例如："COLON", "LUNG"
    :param method_type: 方法类别，例如："PCA", "PLS", "OPLS"
    :param queues_path: 所有队列病人数据的路径，例如：["queue1_path", "queue2_path"]
    :param queues_path: 各个队列病人数据的数量，例如：[3, 8], 该数量加起来应与queues_path的长度相同
    :param VOC_ids: 该分析模式关注的VOC_ID_INTERNAL的数组
    :param cur_patient_info: 当前检测人的峰数据
    :return:
        error_code: 0成功/1失败；
        error_str: "错误信息"；
        points: 点坐标数组，例如：[[x, y, z], ...]
        Y: 对应points顺序的点标签，例如：[0, 1,1,1, 2,2,2,2,2, 3,3,3]，第一个标签固定为0，代表当前检测人的数据点，后续的1,2,3分别代表队列1,2,3
    """

    error_code = 0
    error_str = 'success'
    queue_num = len(queues_num)
    VOC_num = len(VOC_ids)
    MODEL_TAG = model_type + "_" + str(queue_num) + "_" + method_type

    X = pd.DataFrame([], columns=VOC_ids)
    Y = np.ones(sum(queues_num)+1)  # +1 代表当前病人

    cur_patient_biomarker = np.zeros(VOC_num)
    for i in range(VOC_num):
        for peak in cur_patient_info:
            # peak : [VOC_ID_INTERNAL, Index, CAS_NUMBER, RT, Peak_area, Peak_height]
            if peak[0] == VOC_ids[i]:
                cur_patient_biomarker[i] = peak[4]

    X.loc[0] = list(cur_patient_biomarker)
    # X = pd.DataFrame(list(cur_patient_biomarker), columns=VOC_ids)
    Y[0] = 0 # 当前病人类别默认为0

    j = 1
    for i in queues_num:
        j += i
        Y[j:] += 1

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

    return error_code, error_str, points, Y

# ------------------------------------------- TEST ------------------------------------------------------------
# import matplotlib.pyplot as plt
#
# def plot_three_dimension_data(X, y, target_names, title):
#     # 定义坐标轴
#     fig = plt.figure()
#     ax1 = plt.axes(projection='3d')
#
#     plt.title(title)
#     plt.ylabel("Data with\n fixed covariance")
#
#     X0 = X[y == 0, :]
#     X1 = X[y == 1, :]
#     X2 = X[y == 2, :]
#
#     # class 0: dots
#     ax1.scatter(X0[:, 0], X0[:, 1], X0[:, 2], label=target_names[0])
#
#     # class 1: dots
#     ax1.scatter3D(X1[:, 0], X1[:, 1], X1[:, 2], label=target_names[1])
#
#     # class 2: dots
#     ax1.scatter3D(X2[:, 0], X2[:, 1], X2[:, 2], label=target_names[2])
#
#     plt.legend(loc='best', shadow=False, scatterpoints=1)
#     # ax1.set_zlim(-5, 20)
#     ax1.set_xlabel('1 component')
#     ax1.set_ylabel('2 component')
#     ax1.set_zlabel('3 component')
#
#     plt.show()
#     return
#
# # 写入 VOCDATABASE 数据
# # PATH = "D:\work_local\DATA\MXG_COLON2\pre_data\groupsTable.xlsx"
# # group_infos = pd.read_excel(PATH)
# # VOCDATA = pd.DataFrame({
# #     "VOC_ID_INTERNAL": group_infos["Var1"].apply(str) + "-ID",
# #     "CAS_NUMBER": group_infos["Var1"].apply(str) + "-CAS",
# #     "RT_START": group_infos["Rt_start"],
# #     "RT_END": group_infos["Rt_end"]
# # })
# # db_write_table("VOCDATABASE", VOCDATA)
#
# # 测试接口1
# print(get_Models())
#
# 测试 match_VOC_id 接口，并生成queues文件
for i in range(29, 30):
    VOCDATABASE = db_read_table("select * from VOCDATABASE")
    voc_data = np.array(VOCDATABASE)
    voc_data = voc_data.tolist()
    peak_info = pd.read_csv("D:\work_local\DATA\MXG_COLON2\pre_data\peaks_info\\peaks_info_" + str(i) + ".csv")
    peak_info = np.array(peak_info)
    peak_info = peak_info.tolist()
    error_code, error_str, display_info = match_VOC_id(voc_data, peak_info)
    display_info = pd.DataFrame(display_info, columns=["VOC_ID_INTERNAL", "CAS_NUMBER", "RT", "Peak_area", "Peak_height"])
    print(display_info)
    # display_info.to_csv("D:\work_local\DATA\MXG_COLON2\pre_data\queue2\\queue2_" + str(i) + ".csv", index=False)

# 测试 get_analysis_result 接口，并画出三维图
queues_path = ["D:\work_local\DATA\MXG_COLON2\pre_data\queue1\queue1_10.csv",
               "D:\work_local\DATA\MXG_COLON2\pre_data\queue1\queue1_11.csv",
               "D:\work_local\DATA\MXG_COLON2\pre_data\queue2\queue2_30.csv",
               "D:\work_local\DATA\MXG_COLON2\pre_data\queue2\queue2_31.csv",]
model_type="COLON"
method_type="PLS"
VOC_ids = ["2-ID","3-ID","13-ID","4-ID","76-ID","8-ID","24-ID","81-ID","14-ID","107-ID","35-ID"]

cur_patient_info = pd.read_csv("D:\work_local\DATA\MXG_COLON2\pre_data\queue1\\queue1_2.csv")
cur_patient_info = np.array(cur_patient_info)
cur_patient_info = cur_patient_info.tolist()

error_code, error_str, points, Y = get_analysis_result(model_type, method_type, queues_path, [2,2], VOC_ids, cur_patient_info)
X = np.array(points)
Y = np.array(Y)
# plot_three_dimension_data(X, Y, ["0", "1", "2"], "TEST")

