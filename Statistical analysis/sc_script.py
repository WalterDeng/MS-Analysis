import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
import pandas as pd
from sklearn.cross_decomposition import PLSRegression
from sklearn import model_selection
from sklearn import discriminant_analysis
from data_util import *

df = pd.read_csv("D:\DATA\SC_LUNG\\total.csv", encoding='gbk')
out_path = "D:\DATA\SC_LUNG\\raw_data\\"

# 所有病理类型分布情况
# bg = df.groupby("S病理类型-简单版1")
# print(bg["S病理类型-简单版1"].agg(np.size))

# 腺癌各分期人数
# bg = df.groupby("S病理类型-简单版1")
# Tg = bg.get_group("腺癌").groupby("T分期--简单版")
# print(Tg["T分期--简单版"].agg(np.size))

# 取 【"肺良性疾病", "肺良性肿瘤"】, 【"腺癌"】, 【"鳞癌"】, 四种病理数据进行分类，病理标签编号依次为 0，1，2
target_names = ["肺良性疾病", "肺良性肿瘤", "腺癌", "鳞癌"]
# df_lung = df[df["S病理类型-简单版1"].isin(["肺良性疾病", "肺良性肿瘤", "腺癌", "鳞癌"])]
df_lung = df[df["S病理类型-简单版1"].isin(["腺癌", "鳞癌"])]
patient_info = df_lung.iloc[:, 0:99]
def get_tag(x):
    tag = np.NAN
    if x in "肺良性肿瘤":
        tag = 0
    elif x == "肺良性疾病":
        tag = 1
    elif x == "腺癌":
        tag = 2
    elif x == "鳞癌":
        tag = 3
    return tag
patient_info['tag'] = patient_info["S病理类型-简单版1"].apply(lambda x:get_tag(x))
y = patient_info['tag'].to_numpy()

""

# 取"腺癌"病人的 T1, T2, T3, T4, 四种T分期进行分类，病理标签编号依次为 0，1，2，3
# target_names = ["T1", "T2", "T3", "T4"]
# df_lung = df[df["S病理类型-简单版1"]=="腺癌"]
# patient_info = df_lung.iloc[:, 0:99]
# def get_tag(x):
#     tag = np.NAN
#     if x == "T1":
#         tag = 0
#     elif x == "T2":
#         tag = 1
#     elif x == "T3":
#         tag = 2
#     elif x == "T4":
#         tag = 3
#     return tag
# patient_info['tag'] = patient_info["T分期--简单版"].apply(lambda x:get_tag(x))
# y = patient_info['tag'].to_numpy()

y_label = pd.get_dummies(y).to_numpy()
GCMS_data = df_lung.iloc[:, 99:].to_numpy()
# GCMS_data = normalizeA(GCMS_data)

# 方便MATLAB处理，在数据前插入20列0值
GCMS_data = np.concatenate([np.zeros((GCMS_data.shape[0], 20)), GCMS_data], axis=1)
# 输出文件
data_to_single_csv(out_path, patient_info["编号(肺癌)"].to_numpy(), GCMS_data)

x_train, x_test, y_train, y_test = model_selection.train_test_split(GCMS_data, y, test_size=0.3, random_state=5)

# model = PLSRegression()
model = discriminant_analysis.LinearDiscriminantAnalysis()
model.fit(x_train, y_train)

# (x_scores, y_scores) = model.transform(GCMS_data)
# transed = model.transform(GCMS_data)
# x_scores = transed[:, 0]
# y_scores = transed[:, 1]
# mpl.rcParams['font.sans-serif'] = ['SimHei']
# plt.scatter(x_scores[y==0], y_scores[y==0], label=target_names[0])
# plt.scatter(x_scores[y==1], y_scores[y==1], label=target_names[1])
# plt.scatter(x_scores[y==2], y_scores[y==2], label=target_names[2])
# plt.scatter(x_scores[y==3], y_scores[y==3], label=target_names[3])
# plt.legend(frameon=True, loc="best")
# plt.show()

# 预测
y_pred = model.predict(x_test)
y_score = y_pred[:, 1]

# 将预测结果（类别矩阵）转换为数值标签
y_pred = np.array([np.argmax(i) for i in y_pred])
# y_test = np.array([np.argmax(i) for i in y_test])

# 计算模型评价值
print(np.sum(y_pred == y_test) / y_test.size)


import numpy as np
import matplotlib.pyplot as plt

from sklearn.datasets import load_iris
from sklearn.decomposition import PCA, IncrementalPCA



def pls_test():
    iris = load_iris()
    X = iris.data
    y = iris.target

    n_components = 2


    ipca = IncrementalPCA(n_components=n_components, batch_size=10)
    X_ipca = ipca.fit_transform(X)

    pca = PCA(n_components=n_components)
    X_pca = pca.fit_transform(X)

    colors = ["navy", "turquoise", "darkorange"]

    for X_transformed, title in [(X_ipca, "Incremental PCA"), (X_pca, "PCA")]:
        plt.figure(figsize=(8, 8))
        for color, i, target_name in zip(colors, [0, 1, 2], iris.target_names):
            plt.scatter(
                X_transformed[y == i, 0],
                X_transformed[y == i, 1],
                color=color,
                lw=2,
                label=target_name,
            )

        if "Incremental" in title:
            err = np.abs(np.abs(X_pca) - np.abs(X_ipca)).mean()
            plt.title(title + " of iris dataset\nMean absolute unsigned error %.6f" % err)
        else:
            plt.title(title + " of iris dataset")
        plt.legend(loc="best", shadow=False, scatterpoints=1)
        plt.axis([-4, 4, -1.5, 1.5])

    plt.show()

