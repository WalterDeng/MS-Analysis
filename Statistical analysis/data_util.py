"""
    数据读取工具模块
"""

import joblib
import numpy as np
import scipy.io as sio
import pandas as pd
from sql_util import db_read_table, db_write_table, db_execute, db_delete_data
from sklearn import model_selection
from sklearn.decomposition import PCA
from sklearn.cross_decomposition import PLSRegression
import json

with open('config_.json', encoding='utf-8') as f:
    config_ = json.load(f)



def get_Y(dict):
    Y = np.zeros(0, dtype=int)
    for y1, num in dict.items():
        Y1 = np.ones(num, dtype=int) * y1
        Y = np.concatenate((Y, Y1))
    return Y

# 写入文件
def write_list(fileName, landmarks):
    fp = open(fileName, 'w+')
    for i in range(len(landmarks)):
        fp.write(str(landmarks[i][0]))
        fp.write(" : ")
        fp.write(str(landmarks[i][1]) + ',\n')
    fp.close()
    return

## 加载matlab处理后的conlon数据
def load_colon():
    # path = "Z:\home\D1+D2 lookfor peaks\colon.mat"
    load_samples('MXG_COLON')
    Hpath = "Z:\home\chromx\Height.mat"
    HDict = sio.loadmat(Hpath)
    Apath = "Z:\home\chromx\Area.mat"
    ADict = sio.loadmat(Apath)
    Height = HDict.get('Hr')
    Area = ADict.get('Ar')
    Area = np.concatenate((Area[10:20, :], Area[0:10, :]), axis=0) # 前十个样本为健康
    Y = get_Y({0:10, 1:10})
    target_names = ['healthy', 'colon']
    # X = pd.DataFrame(Area)
    # eda(X)
    return Height, Area, Y, target_names
# load_colon2()

data_tag = config_['data_tag']
data_root = config_['data_root']
pre_path = data_root + data_tag + config_['pre_data']
model_path = data_root + data_tag + config_['model_data']

def load_samples(data_root, data_tag):
    """
    加载样本数据
    :return: Height, Area, Y, target_names, extra_info
    """

    data_tags = data_tag.split("_") # data_tag格式为 "Organization_Disease"，可用于区分不同机构的不同疾病。 add by AlanDeng, 2022年3月31日,
    Organization = data_tags[0]
    Disease = data_tags[1]

    # 峰值高度信息：Height.mat
    Hpath = pre_path + "Height.mat"
    HDict = sio.loadmat(Hpath)
    Height = HDict.get('Hr')

    # 峰值高度信息：Area.mat
    Apath = pre_path + "Area.mat"
    ADict = sio.loadmat(Apath)
    Area = ADict.get('Ar')

    # 对齐后的色谱数据：data_auto_aligned.mat
    RawPath = pre_path + "data_auto_aligned.mat"
    RawDict = sio.loadmat(RawPath)
    RawData = RawDict.get('data_auto_aligned').T
    time_series = RawData[0, :]
    raw_data = RawData[1:, :]

    # 样本名称
    fileList = pd.read_csv(pre_path + "fileList.csv", header=None).values.reshape(-1)

    # 峰值信息矩阵
    group_infos = pd.read_excel(pre_path + "groupsTable.xlsx")

    # 样本标签
    Y = np.zeros(fileList.shape[0], dtype='int')

    # 队列名称（主要用于图像显示）
    target_names = ['control']
    for disease in data_tags[1:]:
        target_names.append(disease.lower())

    if Organization == 'MXG':
        # 处理密西根colon数据标签
        Y = Y + 1
        for (col, S) in fileList.iteritems():
            if 'Control' in S[0]:
                Y[col] = 0

    elif Organization == 'ZS1E':
        # 处理中山一医数据

        # 读取疾病分类编号表
        diseaseTag = pd.read_excel(data_root + "diseaseTag.xlsx", sheet_name=None)
        disease_sheet = diseaseTag.get(Disease.lower())
        before = disease_sheet["before"].dropna()
        control = disease_sheet["control"].dropna()
        data_ids = []
        col = 0
        for S in fileList:
            for index,value in before.items():
                if value in S:
                    Y[col] = 1
                    data_ids.append(col)
                    break
            for index, value in control.items():
                if value in S:
                    Y[col] = 0
                    data_ids.append(col)
                    break
            col = col + 1
        Height = Height[data_ids, :]
        Area = Area[data_ids, :]
        Y = Y[data_ids]
        fileList = fileList[data_ids]

    # 额外信息
    extra_info = {
        "raw_data" : raw_data,
        "time_series": time_series,
        "sample_names": fileList,
        "group_infos": group_infos,
    }

    df = pd.DataFrame({
        '编号':fileList,
        'Y':Y
    })
    df = pd.concat([df, pd.DataFrame(Area)], axis=1)
    df.to_csv("D:\DATA\ZS1E_LUNG\\A_mat_all.csv")


    return Height, Area, Y, target_names, extra_info



def load_peak_group_infos(data_tag):
    """
    :return: pd.DataFrame("index", "avgRt")
    """
    data_tags = data_tag.split(
        "_")  # data_tag为数据文件夹名，Organization, Disease可用于区分不同机构或疾病后面需要做特殊处理的情况。 add by dyx, 2022年3月31日,
    Organization = data_tags[0]
    Disease = data_tags[1]

    ROOT_PATH = ROOT + data_tag + pre_path

    group_infos = pd.read_excel(io=ROOT_PATH + "\groupsTable.xlsx")

    # print(a.loc[1].avgRt)
    return group_infos

# load_peak_group_infos()

def load_healthy_lung_thoracic():
    Height, Area, Y, extra_info= load_samples()
    diseaseDict = extra_info["diseaseDict"]

    lung_before_indices = diseaseDict.get('lung_before_indices')
    thoracic_before_indices = diseaseDict.get('thoracic_before_indices')
    lung_after_indices = diseaseDict.get('lung_after_indices')
    Thoracic_after_indices = diseaseDict.get('Thoracic_after_indices')

    X = Area

    healthy = X[Y == 0, :]
    lung = X[lung_before_indices, :]
    Thoracic = X[thoracic_before_indices, :]
    target_names = ['healthy', 'lung', 'Thoracic']

    n_healthy = 20
    n_lung_before = 20
    n_Thoracic_before = 10

    train_X = np.concatenate((healthy[0:n_healthy, :], lung[0:n_lung_before, :], Thoracic[0:n_Thoracic_before, :]),
                             axis=0)
    test_X = np.concatenate((healthy[n_healthy:, :], lung[n_lung_before:, :], Thoracic[n_Thoracic_before:, :]), axis=0)

    train_Y = np.zeros((n_healthy + n_lung_before + n_Thoracic_before, 1), dtype='int')
    train_Y[n_healthy:n_healthy + n_lung_before, :] += 1
    train_Y[n_healthy + n_lung_before:, :] += 2
    train_Y = np.squeeze(train_Y)

    left_healthy = healthy.shape[0] - n_healthy
    left_lung_before = len(lung_before_indices) - n_lung_before
    left_Thoracic_before = len(thoracic_before_indices) - n_Thoracic_before

    test_Y = np.zeros((left_healthy + left_lung_before + left_Thoracic_before, 1), dtype='int')
    test_Y[left_healthy:left_healthy + left_lung_before, :] += 1
    test_Y[left_healthy + left_lung_before:, :] += 2
    test_Y = np.squeeze(test_Y)

    return train_X, train_Y, test_X, test_Y, target_names

def load_lung_thoracic():
    Height, Area, Y, extra_info = load_samples()
    diseaseDict = extra_info["diseaseDict"]

    lung_before_indices = diseaseDict.get('lung_before_indices')
    thoracic_before_indices = diseaseDict.get('thoracic_before_indices')
    lung_after_indices = diseaseDict.get('lung_after_indices')
    Thoracic_after_indices = diseaseDict.get('Thoracic_after_indices')

    X = Area

    # healthy = X[Y == 0, :][0:1, :]
    healthy = X[Y == 0, :]
    lung = X[lung_before_indices, :]
    thoracic = X[thoracic_before_indices, :]
    target_names = ['lung', 'thoracic', 'healthy']

    X = np.concatenate((lung, thoracic), axis=0)
    X3 = np.concatenate((lung, thoracic, healthy), axis=0)

    n_healthy = healthy.shape[0]
    n_lung_before = len(lung_before_indices)
    n_Thoracic_before = len(thoracic_before_indices)

    Y = get_Y({0: n_lung_before, 1: n_Thoracic_before})
    Y3 = get_Y({0:n_lung_before, 1:n_Thoracic_before, 2:n_healthy})

    return X, Y, target_names, X3, Y3

def load_healthy_lung():
    Height, Area, Y, extra_info = load_samples()
    tags = extra_info["tags"]
    diseaseDict = extra_info["diseaseDict"]

    lung_before_indices = diseaseDict.get('lung_before_indices')
    # lung_before_indices = lung_before_indices[0:37]
    lung_after_indices = diseaseDict.get('lung_after_indices')[0:1]

    X = Area
    Y = np.concatenate((Y, [2,2,2]))

    healthy = X[Y == 0, :]
    lung = X[lung_before_indices, :]
    lung_after = X[lung_after_indices, :]
    X = np.concatenate((healthy, lung), axis=0)
    X3 = np.concatenate((healthy, lung, lung_after), axis=0)

    target_names = ['healthy', 'lung']
    tags = np.concatenate((tags[Y == 0], tags[lung_before_indices]), axis=0)

    n_healthy = healthy.shape[0]
    n_lung_before = len(lung_before_indices)
    n_lung_after = len(lung_after_indices)

    Y = get_Y({0: n_healthy, 1: n_lung_before})
    Y3 = get_Y({0:n_healthy, 1:n_lung_before, 2:n_lung_after})



    return X, Y, target_names, tags, X3, Y3

def load_healthy_thoracic(isHeight=False):
    Height, Area, Y, extra_info = load_samples()
    RawData = extra_info["RawData"]
    diseaseDict = extra_info["diseaseDict"]
    tags = extra_info["tags"]
    thoracic_before_indices = diseaseDict.get('thoracic_before_indices')
    thoracic_after_indices = diseaseDict.get('thoracic_after_indices')
    control_before_indices = diseaseDict.get('control_before_indices')


    X = Area
    if isHeight:
        X = Height

    healthy = X[control_before_indices, :]
    thoracic = X[thoracic_before_indices, :]
    thoracic_after = X[thoracic_after_indices, :]
    X = np.concatenate((healthy, thoracic), axis=0)
    X3 = np.concatenate((healthy, thoracic, thoracic_after), axis=0)
    RawData = RawData[np.concatenate((control_before_indices, thoracic_before_indices)), :]
    tags = tags[np.concatenate((control_before_indices, thoracic_before_indices))]
    target_names = ['healthy', 'thoracic']

    n_healthy = healthy.shape[0]
    n_thoracic_before = len(thoracic_before_indices)
    n_thoracic_after = len(thoracic_after_indices)

    Y = get_Y({0:n_healthy, 1:n_thoracic_before})
    Y3 = get_Y({0: n_healthy, 1: n_thoracic_before, 2:n_thoracic_after})

    return X, Y, target_names, RawData, tags

def load_lung_series():
    Height, Area, Y, extra_info = load_samples()
    diseaseDict = extra_info["diseaseDict"]
    lung_series_dict = extra_info["lung_series_dict"]
    lung_before_indices = diseaseDict.get('lung_before_indices')
    lung_after_indices = diseaseDict.get('lung_after_indices')[0:3]

    X = Area

    healthy = X[Y == 0, :]
    lung = X[lung_before_indices, :]
    lung_after = X[lung_after_indices, :]
    X = np.concatenate((healthy, lung, lung_after), axis=0)

    target_names = ['healthy', 'lung']

    n_healthy = healthy.shape[0]
    n_lung_before = len(lung_before_indices)
    n_lung_after = len(lung_after_indices)

    Y = get_Y({0: n_healthy, 1: n_lung_before, 2: n_lung_after})
    # Y = np.zeros((n_healthy + n_lung_before + n_lung_after, 1), dtype='int')
    # Y[n_healthy:, :] += 1
    # Y[n_healthy + n_lung_before:, :] += 1
    # Y = np.squeeze(Y)

    return X, Y, target_names, Area, lung_series_dict

def print_sample_num(Y):
    uniques, counts = np.unique(Y, return_counts=True)
    for i in range(uniques.shape[0]):
        y = uniques[i]
        count = counts[i]
        print("sample ", y, " count ", count)

## 对数据进行分箱处理
def Bining2(AreaY, XPeak, YPeak, width1=1, width2=2):
    """
       动态规划思想处理并返回分箱好的数据.

       Parameters
       ----------
       AreaY : array_like
           样本的面积列表.
       XPeak : array_like
           样本检测峰的时间.
       YPeak : array_like
           样本检测峰值.
       padding : int
           样本峰数较少时填充值.
       width1 : int
           峰值检测的半宽度.
       width2 : int
           峰值检测的全宽度.

       Returns
       -------
       Time_list : ndarray. (sample_num, 2)
       Area_list : ndarray. (sample_num, features)

    """
    Time_list = list()
    Area_list = list()
    left = 0
    right = 0
    sample_num = XPeak.shape[0]
    i_to_j = np.zeros(sample_num, int)
    j_max = [XPeak[i].shape[0] - 1 for i in range(sample_num)]
    # print("j_max: ", j_max)
    while(True):
        # print("i_to_j: ", i_to_j)
        # print("left: ", left, "right: ", right)
        # 过滤没有数据的样本
        arg_index = np.squeeze(np.argwhere(i_to_j <= j_max))
        # print("arg_index: ", arg_index)
        arg_num = arg_index.size
        if arg_num == 1: arg_index = np.array([arg_index])
        # print("arg_num: ", arg_num)

        # 当所有样本都已遍历，跳出循环
        if arg_num == 0: break

        # 取出该列数据
        cur_time = np.zeros(sample_num)
        for i in arg_index:
            j = i_to_j[i]
            cur_time[i] = XPeak[i][j]

        # 获取该列参数
        mean = np.sum(cur_time) / arg_num
        min_val = np.min(cur_time[np.where(cur_time > 0)])
        max_val = np.max(cur_time)

        # 参数检验
        if min_val < right:
            print("error, min_val: ", min_val, "right: ", right, "arg_index: ", arg_index)
            break

        # 确定左右边界

        # 初步定义边界，左边界为当前列最小值， 后边界为下一列最小值（下一列最小值为当前列最大值）
        new_left = min_val
        new_right = min(new_left+width2, mean+width1)  # 取较小值，确保峰集中在固定范围内
        # 进一步确定边界
        left_num = 0
        is_over = False
        for i in range(sample_num):
            rt = cur_time[i]
            # 仅考虑在边界左边的样本
            if rt <= new_right:
                left_num += 1
                if i_to_j[i] + 1 <= j_max[i] and new_right > XPeak[i][i_to_j[i] + 1]:
                    new_right = XPeak[i][i_to_j[i] + 1]
                    is_over = True
        # # 如果没有越界且
        # if not is_over and left_num < arg_num / 2:

        Time_list.append((new_left, new_right))

        # 根据边界分组
        cur_A_list = list()
        for i in range(sample_num):

            rt = cur_time[i]
            # 仅处理数据在边界内的样本
            if new_left <= rt <= new_right:
                cur_A_list.append(AreaY[i][i_to_j[i]])

                # 处理i_to_j数组
                i_to_j[i] += 1
            # 其余补0
            else:
                cur_A_list.append(0)
        # 分组数据放入最终结果
        Area_list.append(cur_A_list)

        # 更新边界
        left = new_left
        right = new_right
    Area_list = np.transpose(np.array(Area_list))
    Time_list = np.transpose(np.array(Time_list))
    # print("Time_list: ", Time_list)
    # print("Area_list: ", Area_list)
    # print("Area_list.shape: ", Area_list.shape)

    return Time_list, Area_list

## 对数据进行分箱处理
def Bining3(AreaY, XPeak, YPeak, width1=1, width2=2, ratio_zero=0.5):
    """
       动态规划思想处理并返回分箱好的数据.

       Parameters
       ----------
       AreaY : array_like
           样本的面积列表.
       XPeak : array_like
           样本检测峰的时间.
       YPeak : array_like
           样本检测峰值.
       padding : int
           样本峰数较少时填充值.
       width1 : int
           峰值检测的半宽度.
       width2 : int
           峰值检测的全宽度.

       Returns
       -------
       Time_list : ndarray. (sample_num, 2)
       Area_list : ndarray. (sample_num, features)

    """
    print(XPeak.shape)
    Time_list = list()
    Area_list = list()
    left = 0
    right = 0
    sample_num = XPeak.shape[0]
    i_to_j = np.zeros(sample_num, int)
    j_max = [XPeak[i].shape[0] - 1 for i in range(sample_num)]
    # print("j_max: ", j_max)
    while(True):
        # print("i_to_j: ", i_to_j)
        # print("left: ", left, "right: ", right)
        # 过滤没有数据的样本
        arg_index = np.squeeze(np.argwhere(i_to_j <= j_max))
        # print("arg_index: ", arg_index)
        arg_num = arg_index.size
        if arg_num == 1: arg_index = np.array([arg_index])
        # print("arg_num: ", arg_num)

        # 当所有样本都已遍历，跳出循环
        if arg_num == 0: break

        # 取出该列数据
        cur_time = np.zeros(sample_num)
        for i in arg_index:
            j = i_to_j[i]
            cur_time[i] = XPeak[i][j]

        # 获取该列参数
        mean = np.sum(cur_time) / arg_num
        min_val = np.min(cur_time[arg_index])
        max_val = np.max(cur_time)

        # 参数检验
        if min_val < right:
            print("error, min_val: ", min_val, "right: ", right, "arg_index: ", arg_index)
            break

        # 确定左右边界

        # 初步定义边界，左边界为当前列最小值， 后边界为下一列最小值（下一列最小值为当前列最大值）
        new_left = min_val
        new_right = get_col_min(i_to_j+1, j_max, sample_num, XPeak, min(new_left+width2, mean+width1))
        # new_right = min(new_left+width2, mean+width1)  # 取较小值，确保峰集中在固定范围内
        # # 进一步确定边界
        # left_num = 0
        # left_max_rt = 0
        # for i in range(arg_index):
        #     rt = cur_time[i]
        #     # 仅考虑在边界左边的样本
        #     if rt <= new_right:
        #         left_num += 1
        #
        # if left_num > arg_num / 2:

        Time_list.append((new_left, new_right))

        # 根据边界分组
        cur_A_list = list()
        for i in range(sample_num):

            rt = cur_time[i]
            # 仅处理数据在边界内的样本
            if new_left <= rt <= new_right:
                cur_A_list.append(AreaY[i][i_to_j[i]])

                # 处理i_to_j数组
                i_to_j[i] += 1
            # 其余补0
            else:
                cur_A_list.append(0)
        # 分组数据放入最终结果
        Area_list.append(cur_A_list)

        # 更新边界
        left = new_left
        right = new_right
    Area_list = np.transpose(np.array(Area_list))
    # Time_list = np.transpose(np.array(Time_list))
    # print("Time_list: ", Time_list)
    # print("Area_list: ", Area_list)
    print("Area_list.shape: ", Area_list.shape)

    Area_del_0 = del_0(Area_list, ratio_zero)

    return Time_list, Area_list, Area_del_0

# P=0.8时, 特征列中不为0的样本数量占到80%及以上，该列将会被保留
def del_0(data, p):
    sample_num = data.shape[0]
    feature_num = data.shape[1]
    retain_index = []
    # test = [1, 3, 41, 71, 85, 97, 118, 139, 185]
    # test_i = [1, 3, 41, 71, 85, 97, 118, 139, 185]
    for i in range(feature_num):
        notZeroNum = np.size(np.where(data[:, i] > 0))
        if notZeroNum > sample_num * p:
            retain_index.append(i)
        # else:
        #     for ii in range(9):
        #         if test[ii] > i:
        #             test_i[ii] = test_i[ii] - 1
        #         elif test[ii] == i:
        #             print(test[ii], "is pass!")
    Area_del_0 = data[:, retain_index]
    # print("test_i: ", test_i)
    print("Area_del_0.shape: ", Area_del_0.shape)
    return Area_del_0, retain_index

def get_col_min(i_to_j, j_max, sample_num, XPeak, default):
    arg_index = np.squeeze(np.argwhere(i_to_j <= j_max))
    # print("arg_index: ", arg_index)
    arg_num = arg_index.size
    if arg_num == 1: arg_index = np.array([arg_index])
    # print("arg_num: ", arg_num)

    # 当前所有样本都已遍历
    if arg_num == 0: return default

    # 取出该列数据
    cur_time = np.zeros(sample_num)
    for i in arg_index:
        j = i_to_j[i]
        cur_time[i] = XPeak[i][j]

    # 获取该列参数
    min_val = np.min(cur_time[arg_index])
    return min_val

# load_colon()



## 对数据进行分箱处理
def Bining(AreaY, XPeak, YPeak, padding, width=0.5, ratio=0.2):
    """
       返回分箱好的数据.

       Parameters
       ----------
       AreaY : array_like
           样本的面积列表.
       XPeak : array_like
           样本检测峰的时间.
       YPeak : array_like
           样本检测峰值.
       padding : int
           样本峰数较少时填充值.
       width : int
           峰值检测的宽度.
       ratio : float
           比例.

       Returns
       -------
       Time_list : ndarray.
       Area_list : ndarray.

    """

    max_time = np.max(XPeak)
    sample_num = np.shape(XPeak)[0]

    cur_col = 1
    tolal_col = 1
    Time_list = list()
    Area_list = list()
    Area_index = 0
    Time_index = 0
    i_to_j = np.zeros(sample_num)
    while(True):
        # 取出该列数据
        cur_time = np.zeros(sample_num)
        for i in range(sample_num):
            cur_time[i] = (XPeak[i, i_to_j[i]])
        # 求该列均值 （有填充要处理）
        mean = np.mean(cur_time)

        min_val = mean - width
        min_args = np.squeeze(np.argwhere(cur_time < min_val))
        min_num = min_args.shape[0]

        max_val = mean + width
        max_args = np.squeeze(np.argwhere(cur_time > min_val))
        max_num = max_args.shape[0]

        # 先判断有无前峰
        if min_num / sample_num < ratio:
            # 少的单独成列
            for i in range(sample_num):
                if(i in min_args):
                    Area_list.append(AreaY[i, i_to_j[i]])  ### 有j超出上限的可能
                else:
                    Area_list.append(0)

            i_to_j[min_args] += 1

        elif min_num / sample_num < ratio:
            return


def gauss_noisy(X, y, snr = 30):
    """
    对输入数据加入高斯噪声，数据扩张至1.2倍，并打乱顺序
    :param X:
    :param y:
    :param snr:
    :return: X3, y3 增加后的数据； X2
    """

    np.random.seed(12)
    X2 = np.zeros(X.shape)
    for i in range(X2.shape[0]):
        X2[i, :] = awgn(X[i, :], snr)
    return X2

def awgn(x, snr, seed=7):
    '''
    加入高斯白噪声 Additive White Gaussian Noise
    :param x: 原始信号
    :param snr: 信噪比
    :return: 加入噪声后的信号
    '''
    np.random.seed(seed)  # 设置随机种子
    snr = 10 ** (snr / 10.0)
    xpower = np.sum(x ** 2) / len(x)
    npower = xpower / snr
    noise = np.random.randn(len(x)) * np.sqrt(npower)
    return x + noise


def print_train_test_name(X, Y, tags, target_names, test_size=0.3, valid_size=0, random_state=2):
    """
    按照给样本随机分配的情况，找到分配后的训练组和测试组样本对应的名称，并输出到 "train_set.csv"、 "test_set.csv" 两个文件中
    :param X:
    :param Y:
    :param tags: 样本名称
    :param test_size:
    :param random_state:
    :return:
    """
    Y = Y.astype(int)
    indexs = np.arange(0, X.shape[0]).astype(int)
    x_train, x_test, train_index, test_index = model_selection.train_test_split(X, indexs, test_size=test_size, random_state=random_state)
    train_set = {
        'name': tags[train_index],
        'type': [target_names[i] for i in Y[train_index]],
    }
    train_set = pd.DataFrame(train_set)
    print("训练集为：")
    print(train_set)

    if valid_size != 0:
        x_valid, x_test, index_valid, test_index = model_selection.train_test_split(x_test, test_index, test_size=valid_size/test_size, random_state=6)
        valid_set = {
            'name': tags[index_valid],
            'type': [target_names[i] for i in Y[index_valid]],
        }
        valid_set = pd.DataFrame(valid_set)
        valid_set.to_csv("valid_set.csv")
    test_set = {
        'name': tags[test_index],
        'type': [target_names[i] for i in Y[test_index]],
    }
    test_set = pd.DataFrame(test_set)
    print("测试集为：")
    print(test_set)
    train_set.to_csv("train_set.csv")
    test_set.to_csv("test_set.csv")
    return

def X_to_csv(X, Y, tags, name):
    """
    将X保存到.csv文件中，文件名为 “name + _data.csv”
    表结构为： 【sample, type, feature_1, feature_2, ..., feature_n】
    :param X:
    :param tags:
    :param name:
    :return:
    """
    set = dict()
    set["sample"] = tags
    set["type"] = Y
    for i in range(X.shape[1]):
        set["feature_"+str(i+1)] = X[:, i]

    df_set = pd.DataFrame(set)

    df_set.to_csv(name + "_data.csv", index=False)
    return


def X_to_db(X, Y, tags, name):
    """
    将X保存到.csv文件中，文件名为 “name + _data.csv”
    表结构为： 【sample, feature_1, feature_2, ..., feature_n】
    :param X:
    :param tags:
    :param name:
    :return:
    """
    set = dict()
    set["sample"] = tags
    set["type"] = Y
    for i in range(X.shape[1]):
        set["feature_" + str(i + 1)] = X[:, i]

    df_set = pd.DataFrame(set)
    db_write_table(table_name=name+"_data", df_data=df_set)
    return

def normalizeA(X):
    A_sum = np.sum(X, axis=1).reshape(-1, 1)
    X = np.nan_to_num(X / A_sum)

    # for i in range(X.shape[0]):
    #     X[i, :] = X[i, :] / A_sum[i]
    return X

def pack_PCA_LDA_model(model_name, X, Y, n_components=3):
    model = PCA(n_components=n_components)
    model.fit(X, Y)
    joblib.dump(model, 'saved_model/' + model_name + ".pkl")
    return

def pack_PLS_DA_model(model_name, X, Y, n_components=3):
    y_train_labels = pd.get_dummies(Y)
    model = PLSRegression(n_components=n_components)
    model.fit(X, y_train_labels)
    joblib.dump(model, 'saved_model/' + model_name + ".pkl")
    return

def pack_OPLS_DA_model(model_name, X, Y, n_components=3):
    y_train_labels = pd.get_dummies(Y)
    model = PLSRegression(n_components=n_components)
    model.fit(X, y_train_labels)
    joblib.dump(model, 'saved_model/' + model_name + ".pkl")
    return

def pack_model(model_name, X, Y, biomarkers):
    """
    模型封装入口
    :param model_name: 依据模型名称选择合适的封装方法，封装后的文件也以此命名，saved_model/model_name.pkl
                       格式：疾病模式_队列数量_模型类型，例如：COLON_2_PCA, LUNG_3_OPLS
    :param X:
    :param Y:
    :param biomarkers:
    :return:
    """
    disease_tag, queue_num, model_type = model_name.split("_")
    X = X[:, biomarkers]
    X = normalizeA(X)
    model_pkl = ""
    if model_type == 'PCA':
        model_pkl = pack_PCA_LDA_model(model_name, X, Y)
    elif model_type == 'PLS':
        model_pkl = pack_PLS_DA_model(model_name, X, Y)
    elif model_type == 'OPLS':
        model_pkl = pack_OPLS_DA_model(model_name, X, Y)

    return model_pkl

def data_to_single_csv(path, names, data):
    # 四川肿瘤医院的数据转出单个的csv文件，方便Matlab程序读入
    time = np.arange(0, data.shape[1])
    f = path + names + ".csv"
    for i in range(data.shape[0]):
        value = data[i, :]
        df = pd.DataFrame({"time":time, "value":value})
        df.to_csv(f[i], index=False)


