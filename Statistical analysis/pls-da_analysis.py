import numpy as np
from sklearn.cross_decomposition import PLSRegression
from sklearn.decomposition import PCA
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import MinMaxScaler  # 归一化
from sklearn.metrics import confusion_matrix, recall_score, classification_report, accuracy_score
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.model_selection import GridSearchCV
import warnings
from sklearn.model_selection import validation_curve
from sklearn.model_selection import KFold
from data_util import *
from myEvaluation import LDA_evaluation, LDA_cross_evaluation, get_cross_evaluation, compute_cross_score, evaluation_model
from myPreprocessing import normalizeArea, peak_subset_selection_by_score, find_reduction_model, \
    find_classification_model, change_by_features, plot_data
from features_tag import *
from sklearn.metrics import roc_curve, auc, roc_auc_score
from plot_lasso_model_selection import LassoLarsCV_plot

import warnings
warnings.filterwarnings("ignore")

def compute_VIP(X, y, R, T, A):
    """
    计算模型中各预测变量的VIP值
    :param X: 数据集X
    :param y: 标签y
    :param R: A个PLS成分中，每个成分a都对应一套系数wa将X转换为成分得分，系数矩阵写作R，大小为p×A
    :param T: 得分矩阵记做T，大小为n×A，ta代表n个样本的第a个成分的得分列表
    :param A: PLS成分的总数
    :return: VIPs = np.zeros(p)
    """
    p = X.shape[1]
    Q2 = np.square(np.dot(y.T, T))

    VIPs = np.zeros(p)
    temp = np.zeros(A)
    for j in range(p):
        for a in range(A):
            temp[a] = Q2[a] * pow(R[j, a] / np.linalg.norm(R[:, a]), 2)
        VIPs[j] = np.sqrt(p * np.sum(temp) / np.sum(Q2))
    return VIPs

# 读取数据集
X, Y, target_names, RawData, tags = load_healthy_thoracic()
# X = RawData
# X, _ = del_0(X, 0.3)

# best_feauure = [51, 35, 90, 17, 8, 42, 14, 19, 9]
# X = X[:, best_feauure]
# X = normalizeArea(X)

# markers_index = LassoLarsCV_plot(X, Y)
# print("生成非0特征序号", np.arange(0,X.shape[1])[markers_index])
# X = X[:, markers_index]

# scaler = MinMaxScaler()
# scaler.fit(X)
# X = scaler.transform(X)

# print_sample_num(Y)




def record_variable_times(X, Y, coef_thresh = 0.04, VIPs_thresh = 1.4):
    """
    记录预测变量出现次数，利用相关性系数和VIP两种评价指标。
    重复10000次，统计所有预测变量出现次数，输出最终结果
    :param X:
    :param Y:
    :return: biomarkers_of_coefs, biomarkers_of_VIP : pd.Dataframe({'index', 'times'})
    """
    biomarkers = dict()
    VIP_biomarkers = dict()

    for j in range(10):
        try:
            # 循环测试10000次
            for i in range(10000):

                # 数据划分训练集、测试集
                # x_train, x_test, y_train, y_test = model_selection.train_test_split(X, Y, test_size=0.3, random_state=5)
                x_train, x_test, y_train, y_test = model_selection.train_test_split(X, Y, test_size=0.3)

                # 然后对y进行转换
                y_train_labels = pd.get_dummies(y_train)

                # 建模
                n_component = 3
                model = PLSRegression(n_components=n_component)
                model.fit(x_train, y_train_labels)

                # 计算VIP值
                x_test_trans = model.transform(x_test)
                VIPs = compute_VIP(x_test, y_test, model.x_rotations_, x_test_trans, n_component)

                # 预测
                y_pred = model.predict(x_test)
                second_0_score = np.sum(y_pred[y_test==0, 0])
                second_1_score = np.sum(y_pred[y_test == 1, 1])
                second_score = second_0_score + second_1_score
                # 计算roc面积
                # roc_score_0 = roc_auc_score(y_test, y_pred[:, 0])
                roc_score_1 = roc_auc_score(y_test, y_pred[:, 1])

                # 将预测结果（类别矩阵）转换为数值标签
                y_pred = np.array([np.argmax(i) for i in y_pred])

                # 各特征系数处理
                xx = np.arange(0, X.shape[1])
                coef_ = np.abs(model.coef_[:, 1])
                # print("top variables: ", xx[coef_>thresh])
                for ii in xx[coef_>coef_thresh]:
                    biomarkers[ii] = biomarkers.get(ii, 0) + 1
                # plt.scatter(xx[coef_>thresh], coef_[coef_>thresh], color='blue')
                # plt.scatter(xx[coef_ < thresh], coef_[coef_ < thresh], color='black')
                # plt.xlabel("Predictor variable")
                # plt.ylabel("Coefficients of the linear model")
                # plt.show()

                # 各特征VIP值处理
                for ii in xx[VIPs>VIPs_thresh]:
                    VIP_biomarkers[ii] = VIP_biomarkers.get(ii, 0) + 1
                plt.scatter(xx[VIPs>1], VIPs[VIPs>1], color='blue')
                plt.scatter(xx[VIPs < 1], VIPs[VIPs < 1], color='black')
                plt.xlabel("Predictor variable")
                plt.ylabel("VIP")
                plt.show()
            break
        except Exception as e:
            biomarkers = dict()
            VIP_biomarkers = dict()
            print(e)

    # 统计biomarkers
    biomarkers = list(biomarkers.items())
    biomarkers.sort(key=lambda a:a[1], reverse=True)
    biomarkers = np.array(biomarkers)
    biomarkers_of_coefs = pd.DataFrame({
        'index' : biomarkers[:, 0],
        'times' : biomarkers[:, 1],
    })
    biomarkers_of_coefs.to_csv("biomarkers_of_coefs.csv")
    print("Biomarkers for coefs:")
    print(biomarkers[:20])

    VIP_biomarkers = list(VIP_biomarkers.items())
    VIP_biomarkers.sort(key=lambda a:a[1], reverse=True)
    VIP_biomarkers = np.array(VIP_biomarkers)
    biomarkers_of_VIP = pd.DataFrame({
        'index' : VIP_biomarkers[:, 0],
        'times' : VIP_biomarkers[:, 1],
    })
    biomarkers_of_VIP.to_csv("biomarkers_of_VIP.csv")
    print("Biomarkers for VIPs:")
    print(VIP_biomarkers[:20])

    return biomarkers_of_coefs, biomarkers_of_VIP

# 找到biomarkers，有模型相关性系数和VIP两种指标
# biomarkers_of_coefs, biomarkers_of_VIP = record_variable_times(X, Y, coef_thresh = 0.04, VIPs_thresh = 1.4)

def accuracy_for_PLS(X, Y, repeat_times=10000, is_print=True):
    accuracy_list = np.zeros((repeat_times, 1))
    AUC_list = np.zeros((repeat_times, 1))
    sensitivity_list = np.zeros((repeat_times, 1))
    specificity_list = np.zeros((repeat_times, 1))
    precision_list = np.zeros((repeat_times, 1))
    F1_list = np.zeros((repeat_times, 1))
    npv_list = np.zeros((repeat_times, 1))

    # 循环测试1000次
    for i in range(repeat_times):

        # 数据划分训练集、测试集
        # x_train, x_test, y_train, y_test = model_selection.train_test_split(X, Y, test_size=0.3, random_state=5)
        x_train, x_test, y_train, y_test = model_selection.train_test_split(X, Y, test_size=0.3)

        # 然后对y进行转换
        y_train_labels = pd.get_dummies(y_train)

        # 建模
        n_component = 3
        if X.shape[1] <= 3:
            n_component = X.shape[1]
        model = PLSRegression(n_components=n_component)
        model.fit(x_train, y_train_labels)

        # 预测
        y_pred = model.predict(x_test)
        y_score = y_pred[:, 1]

        # 将预测结果（类别矩阵）转换为数值标签
        y_pred = np.array([np.argmax(i) for i in y_pred])

        # 计算模型评价值
        socres = evaluation_model(y_test, y_pred, y_score, target_names, is_print=False)
        AUC_list[i] = socres["AUC"]
        sensitivity_list[i] = socres["sensitivity"]
        specificity_list[i] = socres["specificity"]
        accuracy_list[i] = socres["accuracy"]
        precision_list[i] = socres["precision"]
        F1_list[i] = socres["F1"]
        npv_list[i] = socres["npv"]

    mean_accuracy = np.mean(accuracy_list)
    mean_AUC = np.mean(AUC_list)
    mean_sensitivity = np.mean(sensitivity_list)
    mean_specificity = np.mean(specificity_list)
    mean_precision = np.mean(precision_list)
    mean_F1 = np.mean(F1_list)
    mean_npv = np.mean(npv_list)

    if is_print:
        print('平均准确度ACC为：\n', mean_accuracy)
        print('平均AUC为：\n', mean_AUC)
        print('平均灵敏度为：\n', mean_sensitivity)
        print('平均特异度为：\n', mean_specificity)
        print('平均精确度PPV为：\n', mean_precision)
        print('平均NPV为：\n', mean_npv)
        print('平均F1值为：\n', mean_F1)

    return mean_accuracy, mean_AUC, mean_sensitivity, mean_specificity, mean_precision, mean_F1

def plot_biomarkers(X, Y, biomarkers):
    """
    画出对应于biomarkers特征的各级准确率图
    :param X:
    :param Y:
    :param biomarkers:
    :return:
    """
    start_num = 2
    biomarkers_num = biomarkers.shape[0]
    accuracy_list = np.zeros(biomarkers_num-start_num+1)

    for i in range(start_num, biomarkers_num+1):
        X_cut = X[:, biomarkers[np.arange(0, i, dtype='int')]]
        X_cut = normalizeArea(X_cut)
        for j in range(10):
            # 至多重复10次，避免出现测试集只有一种类别报错的偶然情况
            try:
                mean_accuracy, mean_AUC, mean_sensitivity, mean_specificity, mean_precision, mean_F1 = accuracy_for_PLS(X_cut, Y, repeat_times=2000)
                accuracy_list[i-start_num] = mean_accuracy
                break
            except Exception as e:
                print("error: ", e)
                print("biomarker_num: ", i, ", test_times: ", j)

    print("accuracy_list: ", accuracy_list)
    the_best_index = np.argmax(accuracy_list)
    the_best_value = accuracy_list[the_best_index]
    true_best_num = the_best_index+start_num
    print("the_best_num: ", true_best_num, ", the_best_value: ", the_best_value)
    plt.plot(np.arange(start_num, biomarkers_num+1), accuracy_list)
    plt.vlines(true_best_num, 0, 1, colors= 'black', linestyles='--')
    plt.text(true_best_num, the_best_value, (true_best_num, round(the_best_value, 4)), color='black')
    plt.xlabel("Amount of biomarker")
    plt.ylabel("Mean accuracy of test set")
    plt.show()

# print("开始测试 Coefs-biomarkers:")
# biomarkers_index = biomarkers_of_coefs['index']
# plot_biomarkers(X, Y, biomarkers_index)
# print("开始测试 VIP-biomarkers:")
# biomarkers_index = biomarkers_of_VIP['index']
# plot_biomarkers(X, Y, biomarkers_index)

def biomarker_result_display(X, y, repeat_times=10000):
    #画样本分布图
    y_train_labels = pd.get_dummies(y)
    # 建模
    model = PLSRegression(n_components=3)
    model.fit(X, y_train_labels)
    # 画出分类后的数据
    title = "Distribution of the subjects' data for the three PLS components"
    Y_pred = model.predict(X)
    Y_pred = np.array([np.argmax(i) for i in Y_pred])
    X_tran = model.transform(X)
    plot_data(model, X_tran, Y, Y_pred, target_names, title, is_plot_false=False)
    return

VIP_biomarker_index = [51, 35, 19, 8, 50, 17, 90, 9, 14, 42, 22, 37, 2, 60, 47, 33, 27, 58, 78]
X = X[:, VIP_biomarker_index]
X = normalizeArea(X)
biomarker_result_display(X, Y)
mean_accuracy, mean_AUC, mean_sensitivity, mean_specificity, mean_precision, mean_F1 = accuracy_for_PLS(X, Y, repeat_times=10000)

def accuracy_component(x_train, x_test, y_train, y_test, component, n_fold):
    k_range = np.linspace(1, component, component)

    kf = KFold(n_splits=n_fold, random_state=None, shuffle=True)
    accuracy_validation = np.zeros((1, component))
    accuracy_train = np.zeros((1, component))
    for j in range(component):
        p = 0
        acc = 0
        model_pls = PLSRegression(n_components=j + 1)
        y_train_labels = pd.get_dummies(y_train)
        model_pls.fit(x_train, y_train_labels)
        y_pred = model_pls.predict(x_test)
        y_pred = np.array([np.argmax(i) for i in y_pred])
        accuracy_train[:, j] = accuracy_score(y_test, y_pred)
        for train_index, test_index in kf.split(x_train):
            X_train, X_test = x_train[train_index], x_train[test_index]
            Y_train, Y_test = y_train[train_index], y_train[test_index]

            Y_TRAIN_labels = pd.get_dummies(Y_train)
            # Y_TEST_labels = pd.get_dummies(Y_test)
            model_1 = PLSRegression(n_components=j + 1)
            model_1.fit(X_train, Y_TRAIN_labels)
            Y_pred = model_1.predict(X_test)
            Y_pred = np.array([np.argmax(i1) for i1 in Y_pred])
            acc = accuracy_score(Y_test, Y_pred) + acc
            p = p + 1
        accuracy_validation[:, j] = acc / p
    print(accuracy_validation)
    plt.plot(k_range, accuracy_validation.T, 'o-', label="Training", color="r")
    plt.plot(k_range, accuracy_train.T, 'o-', label="Cross-validation", color="b")
    plt.xlabel("N components")
    plt.ylabel("Score")
    plt.legend(loc="best")
    plt.rc('font', family='Times New Roman')
    plt.rcParams['font.size'] = 10
    plt.show()
    return accuracy_validation, accuracy_train

# params = model.get_params()
# coef = model.coef_
# # plt.plot(coef[:, 1])
# # plt.show()
# weights = np.abs(coef[:, 1])
# index_10 = 20
# idx = sorted(range(len(weights)), key=lambda k: weights[k], reverse=True)[:index_10]
# X = X[:, idx]
# # 数据划分训练集、测试集
# x_train, x_test, y_train, y_test = model_selection.train_test_split(X, Y, test_size=0.3, random_state=2)
# accuracy_validation, accuracy_train = accuracy_component(x_train, x_test, y_train, y_test, 15, 5)