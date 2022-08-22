from iccs import *
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

def normalizeA(X):
    A_sum = np.sum(X, axis=1).reshape(-1, 1)
    X = np.nan_to_num(X / A_sum)
    # for i in range(X.shape[0]):
    #     X[i, :] = X[i, :] / A_sum[i]
    return X

group_pd = pd.read_excel("F:\ShareCache\邓月喜_2001213282\工作\MS-analysis\Statistical test\ICC\\test_1_GCMS\groupsTable.xlsx")
fileList = pd.read_csv("F:\ShareCache\邓月喜_2001213282\工作\MS-analysis\Statistical test\ICC\\test_1_GCMS\\fileList.csv")

group_infos = group_pd.iloc[:, 6:] # 取峰值数据
RT_infos = group_pd["avgRt"]
RT_infos = RT_infos.apply(lambda x:round(x, 3))

columns = [] # 更改列标签
for c in fileList.columns:
    [_, c1] = c.split("_")
    [c2, _, _] = c1.split(".")
    columns.append(c2)
group_infos.columns = columns

# group_infos = np.array(group_infos)
#
# group_infos = normalizeA(group_infos.T)

# 第一种挑选峰方法：每隔5分钟取峰
# groups_id = np.array([1, 51, 80, 112, 165, 214, 242], dtype='int') - 1
# [0.47781224981342313, 0.9595728390554664, 0.5746365820616192, 0.9157484900846954, 0.29889359810281596, 0.9835701568057343, 0.13589891068631435]
# 0.6208761180871526

# 第二种挑选峰方法：随机挑选
# groups_id = np.sort(np.random.random_integers(1, 247, 10))
# groups_id = [8, 121, 155, 28, 173, 118, 143, 109]
# groups_id = []
# for _ in range(9):
#     for _ in range(100):
#         id = np.random.randint(0, group_infos.shape[0])
#         if id not in groups_id and 0 not in group_infos.iloc[id, :].values:
#         # if id not in groups_id:
#             groups_id.append(id)
#             break
# # groups_id = [84, 96, 45, 42, 63, 73, 65, 14, 134]
# groups_id.sort()

# 第三种峰挑选方法，选择全部非0峰
groups_id = []
for id in range(group_infos.shape[0]):
    if 0 not in group_infos.iloc[id, :].values:
        groups_id.append(id)
print("groups_id:", groups_id)



# 存储路径
write_path = "F:\ShareCache\邓月喜_2001213282\工作\MS-analysis\Statistical test\ICC\\test_1_GCMS\ICC_data"

def one_icc(df):
    icc_list = []

    for id in groups_id:
        data = np.zeros(df.shape)
        for index, S in df.iterrows():
            data[index, 0] = group_infos.loc[id, S["first"]]
            data[index, 1] = group_infos.loc[id, S["second"]]
        # data = data[[1,3,5,7], :]
        # print(data)
        df2 = pd.DataFrame(data)
        df2.columns = ["test_1", "test_2"]
        icc_value = icc1(data.T)
        df2.loc[0, "icc_value"] = icc_value
        print(df2)
        df2.to_csv("F:\ShareCache\邓月喜_2001213282\工作\MS-analysis\Statistical test\ICC\\test_1_GCMS\ICC_data\\df2.csv", )
        icc_list.append(round(icc_value, 3))


    icc_df = pd.DataFrame({
        "Peak_RT" : RT_infos[groups_id],
        "ICC_Value" : icc_list
    })
    # icc_df["mean_ICC"] = np.mean(np.array(icc_list))
    icc_df.to_csv("F:\ShareCache\邓月喜_2001213282\工作\MS-analysis\Statistical test\ICC\\test_1_GCMS\ICC_data\\ICC_DATA.csv", mode='a')
    print(icc_df.describe())
    return RT_infos[groups_id], icc_list

# 设备一致性检验
# df = pd.read_excel("F:\ShareCache\邓月喜_2001213282\工作\MS-analysis\Statistical test\ICC\\test_1_GCMS\\equipment_consistency.xlsx")
# df = df.iloc[:, 1:]
# df.columns = ["first", "second"]
# RTs, icc111 = one_icc(df)
# # 呼气方式一致性检验
# df = pd.read_excel("F:\ShareCache\邓月喜_2001213282\工作\MS-analysis\Statistical test\ICC\\test_1_GCMS\\respiratory_patten_consistency.xlsx")
# df = df.iloc[:, 1:]
# df.columns = ["first", "second"]
# _, icc222 = one_icc(df)

# plt.scatter(RTs, icc111, label="equipment_consistency", color="r")
# plt.scatter(RTs, icc222, label="respiratory_patten_consistency", color="b")
# plt.xlabel("RT")
# plt.ylabel("ICC-Score")
# plt.legend(loc="best")
# plt.rc('font', family='Times New Roman')
# plt.rcParams['font.size'] = 10
# plt.show()

ICC_DATA4 = pd.read_csv("F:\ShareCache\邓月喜_2001213282\工作\MS-analysis\Statistical test\ICC\\test_1_GCMS\ICC_data\\ICC_DATA4.csv")

print(ICC_DATA4.describe())

import seaborn as sns
sns.set_palette("hls") #设置所有图的颜色，使用hls色彩空间
sns.distplot(ICC_DATA4["ICC1"],bins=30,kde=True)
plt.title("equipment_consistency")
plt.show()

import seaborn as sns
sns.set_palette("hls") #设置所有图的颜色，使用hls色彩空间
sns.distplot(ICC_DATA4["ICC2"],bins=30,kde=True)
plt.title("respiratory_patten_consistency")
plt.show()
