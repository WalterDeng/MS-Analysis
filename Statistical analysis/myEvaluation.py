from sklearn import discriminant_analysis
from sklearn import model_selection
from sklearn import neighbors
from sklearn.pipeline import Pipeline
from sklearn.cross_decomposition import PLSRegression
from sklearn import preprocessing
from sklearn import svm
import matplotlib.pyplot as plt
from sklearn import decomposition
from sklearn.utils import shuffle
import numpy as np
from plot_lda_qda import plot_lda_result, plot_time_series
import pandas as pd
from sklearn import tree
from sklearn.ensemble import AdaBoostClassifier
from sklearn.metrics import classification_report, matthews_corrcoef, roc_auc_score, zero_one_loss
from sklearn.metrics import confusion_matrix, recall_score, accuracy_score
from data_util import *

# 评估LDA分数
def LDA_evaluation(X, y):
    # 随机打乱
    # X, y = shuffle(X, y, random_state=0)

    # 分割数据集
    X_train, X_test, y_train, y_test = model_selection.train_test_split(X, y, test_size = 0.2)

    lda = discriminant_analysis.LinearDiscriminantAnalysis()

    lda.fit(X_train, y_train)

    # score函数获取各子集平均正确率
    scores = lda.score(X_test, y_test)

    print("LDA_evaluation scores: ", scores)

    return scores

# 输出模型相关参数
def evaluation_model(y_true, y_pred, y_distance, target_names, is_print=True):
    """
    AUC、灵敏度、特异度、ACC和F1值
    :param X_train:
    :param X_test:
    :param y_train:
    :param y_test:
    :param reduction:
    :param classification:
    :return:
    """
    # AUC
    AUC = roc_auc_score(y_true, y_distance)

    # 计算混淆矩阵
    CM = confusion_matrix(y_true, y_pred)
    (tn, fp, fn, tp) = CM.ravel()

    # 灵敏度TPR：在真实值是positive中，预测对的占比，也叫recall
    sensitivity = tp / (tp + fn)

    # 特异度 Specificity
    specificity = tn / (tn + fp)

    # 准确率ACC：所有判断正确的结果占总的观测值比重
    accuracy = accuracy_score(y_true, y_pred)

    # 精确率PPV：在预测值是positive中，预测对的占比
    precision = tp / (tp + fp)

    # F1
    F1 = 2 * precision * sensitivity / (precision + sensitivity)

    # 打印
    if is_print:
        print("tn:%i, fp:%i, fn:%i, tp:%i" % (tn, fp, fn, tp))
        print("AUC: ", AUC)
        print("灵敏度: ", sensitivity)
        print("特异度: ", specificity)
        print("准确率: ", accuracy)
        print("精确率: ", precision)
        print("F1: ", F1)
        # 分类评估报告
        print("classification_report = \n", classification_report(y_true, y_pred, target_names=target_names))


    socres = {
        "AUC": AUC,
        "sensitivity": sensitivity,
        "specificity": specificity,
        "accuracy": accuracy,
        "precision": precision,
        "F1": F1,
    }
    return socres


def LDA_cross_evaluation(X, y):
    # 随机打乱
    # X, y = shuffle(X, y, random_state=0)

    lda = discriminant_analysis.LinearDiscriminantAnalysis()

    # 评分默认采用各评估器自带score函数，也可用scoring指定
    scores = model_selection.cross_val_score(lda, X, y, cv=5)
    scores_mean = scores.mean()
    print("LDA_cross_evaluation scores: ", scores)
    print("Accuracy: %0.2f (+/- %0.2f)" % (scores_mean, scores.std() * 2))

    # scores_f1 = model_selection.cross_val_score(lda, X, y, cv=10, scoring="f1_macro")
    # print("LDA_cross_evaluation f1_macro scores: ", scores_f1)
    # print("f1_macro Accuracy: %0.2f (+/- %0.2f)" % (scores_f1.mean(), scores_f1.std() * 2))

    return scores, scores_mean

def get_cross_evaluation(X, y, classification):
    """
    获取对应分类器的5倍交叉验证值
    :param X:
    :param y:
    :param classification:
    :return: scores, scores_mean
    """
    # 定义分类器
    classificator = discriminant_analysis.LinearDiscriminantAnalysis(solver="svd", store_covariance=True)
    if classification == 'qda':
        classificator = discriminant_analysis.QuadraticDiscriminantAnalysis()
    elif classification == 'l-svm':
        classificator = svm.LinearSVC(random_state=0)
    elif classification == 'knn':
        classificator = neighbors.KNeighborsClassifier(n_neighbors=3, weights='distance')

    # 评分默认采用各评估器自带score函数
    scores = model_selection.cross_val_score(classificator, X, y, cv=5)
    scores_mean = scores.mean()
    print(classification + "cross_evaluation scores: ", scores)
    print(classification + "Accuracy: %0.2f (+/- %0.2f)" % (scores_mean, scores.std() * 2))
    return scores, scores_mean


def get_distance(y_true, y_predict, direction = -1):
    return

def compute_cross_score(X, y, reduction, classification):
    K = 5
    accuracy = np.zeros(K)
    distance = np.zeros(K)
    l = np.ceil(X.shape[0] / K)
    indices = np.arange(0, X.shape[0])
    for i in range(K):
        if i != K-1:
            test_index = np.arange(i * l, (i + 1) * l, dtype=int)
        else:
            test_index = np.arange(i * l, X.shape[0], dtype=int)

        train_index = np.delete(indices, test_index)
        x_train = X[train_index]
        y_train = y[train_index]
        x_test = X[test_index]
        y_test = y[test_index]

        if reduction == 'pca':
            estimators = [
                ('reduce_dim', decomposition.PCA(n_components=2)),
                ('clf', discriminant_analysis.LinearDiscriminantAnalysis()),
                # ('clf', svm.SVC()),
            ]
        elif reduction == 'none':
            estimators = [
                ('clf', discriminant_analysis.LinearDiscriminantAnalysis()),
            ]
            # ('clf', svm.SVC()),
        else:
            estimators = [
                ('reduce_dim', discriminant_analysis.LinearDiscriminantAnalysis(n_components=1)),
                ('clf', discriminant_analysis.LinearDiscriminantAnalysis()),
                # ('clf', svm.SVC()),
            ]
        pipe = Pipeline(estimators)

        pipe.fit(x_train, y_train)

        first_score = pipe.score(x_test, y_test)
        accuracy[i] = first_score

        # 计算20%临界点的平均距离
        # boundary_distance = pipe.decision_function(X)
        # index_20 = int(np.floor(boundary_distance.shape[0] * 0.2))
        # abs_boundary_distance = np.abs(boundary_distance)
        # idx = np.argpartition(abs_boundary_distance, index_20)[:(index_20 + 1)]
        # boundary_distance = boundary_distance[idx]
        # yi = y[idx]
        # boundary_distance[yi == 0] = 0 - boundary_distance[yi == 0]

        # 20200120 改：计算所有测试集的距离
        boundary_distance = pipe.decision_function(x_test)
        boundary_distance[y_test == 0] = 0 - boundary_distance[y_test == 0]
        second_score = np.mean(boundary_distance)
        distance[i] = second_score

    score = [np.mean(accuracy), np.mean(distance)]
    # scores = model_selection.cross_validate(pipe, X, y, cv=4, scoring=('roc_auc', 'accuracy', 'neg_brier_score'))
    # make_scorer()
    # first_score = np.mean(scores.get('test_roc_auc'))
    # second_score = np.mean(scores.get('test_accuracy'))
    # third_score = np.mean(scores.get('test_neg_brier_score'))
    # score = [first_score, second_score, third_score]
    return score

def compute_PLS_DA_score(X, y):
    """
    用于迭代特征子集选择算法中计算某个特征子集的分数
    :param X:
    :param y:
    :return:
    """
    K = 5
    accuracy = np.zeros((K, 1))
    distance = np.zeros((K, 1))
    for i in range(K):
        x_train, x_test, y_train, y_test = model_selection.train_test_split(X, y, test_size=0.3)
        scores_data = get_PLS_scores(x_train, y_train, x_test, y_test, is_test_accuracy=True, is_distance_score=True)
        distance[i] = scores_data['distance_score']
        accuracy[i] = scores_data['test_accuracy']
    score = [np.mean(accuracy), np.mean(distance)]
    return score

def get_PLS_scores(x_train, y_train, x_test, y_test, is_train_accuracy=False, is_test_accuracy=False, is_distance_score=False, is_AUC=False, is_y_test_score=False):
    """
    根据分好的训练集/测试集，用tag选择返回评价指标
    :return: scores_data = dict() ：{train_accuracy， test_accuracy， distance_score， AUC}
    """
    scores_data = dict()

    # 然后对y进行转换
    y_train_labels = pd.get_dummies(y_train)

    # 建模
    n_component = 10
    if x_train.shape[1] <= 10:
        n_component = x_train.shape[1]
    model = PLSRegression(n_components=n_component)
    model.fit(x_train, y_train_labels)

    # 预测
    y_pred = model.predict(x_test)

    # 计算roc面积
    if is_AUC:
        AUC = roc_auc_score(y_test, y_pred[:, 1])
        scores_data['AUC'] = AUC

    # 计算预测距离
    if is_distance_score:
        second_0_score = np.sum(y_pred[y_test == 0, 0])
        second_1_score = np.sum(y_pred[y_test == 1, 1])
        distance_score = second_0_score + second_1_score
        scores_data['distance_score'] = distance_score

    # 计算测试集准确度
    if is_test_accuracy:
        # 将预测结果（类别矩阵）转换为数值标签
        y_pred_value = np.array([np.argmax(i) for i in y_pred])
        test_accuracy = accuracy_score(y_test, y_pred_value)
        scores_data['test_accuracy'] = test_accuracy

    # 计算训练集准确度
    if is_train_accuracy:
        y_train_pred = model.predict(x_train)
        # 将预测结果（类别矩阵）转换为数值标签
        y_train_pred_value = np.array([np.argmax(i) for i in y_train_pred])
        train_accuracy = accuracy_score(y_train, y_train_pred_value)
        scores_data['train_accuracy'] = train_accuracy

    # 计算测试集得分
    if is_y_test_score:
        y_test_score = y_pred[:, 1]
        scores_data['y_test_score'] = y_test_score

    return scores_data

def compute_PCA_LDA_score(X, y, reduction='pca', classification='lda'):
    """
    用于特征子集选择算法中计算某特征对应的分数
    :param X:
    :param y:
    :param n_features:
    :param reduction:
    :param classification:
    :return:
    """
    # 设置验证集
    # x_train, x_valid, y_train, y_valid = model_selection.train_test_split(X, y, test_size=0.2, random_state=16)
    reductor, classificator, X_r = get_reductor_and_classificator(X, y, reduction=reduction, classification=classification)
    # if reductor =='none':
    #     Xrr = X
    # else:
    #     Xrr = reductor.transform(X)
    first_score, second_score = get_two_score(classificator, X_r, y, classification)

    score = [first_score, second_score]
    return score

def get_two_score(classificator, X_r, y, classification):
    """
    获取用于特征子集比较的两个分数
    :param classificator: 训练好的分类器
    :param X_r: 降维处理后的数据
    :param y:
    :param classification: 分类器标志：'lda', 'l-svm', 'knn'
    :return: first_score, second_score
    """
    first_score = classificator.score(X_r, y)
    second_score = 0
    if classification in ['lda', 'svm']: # 分类器有decision_function函数则计算边界距离
        # 计算20%临界点的平均距离
        boundary_distance = classificator.decision_function(X_r)
        index_20 = int(np.floor(boundary_distance.shape[0] * 0.2))
        abs_boundary_distance = np.abs(boundary_distance)
        idx = np.argpartition(abs_boundary_distance, index_20)[:(index_20 + 1)]
        boundary_distance = boundary_distance[idx]
        y = np.array(y)[idx]
        boundary_distance[y == 0] = 0 - boundary_distance[y == 0]
        second_score = np.mean(boundary_distance)
    elif classification in ['knn']: # 有predict_proba(X)则计算平均概率
        proba = classificator.predict_proba(X_r)
        mean_0 = np.mean(proba[y==0, 0] - proba[y==0, 1])
        mean_1 = np.mean(proba[y == 1, 1] - proba[y == 1, 0])
        second_score = (mean_0 + mean_1) / 2

    return first_score, second_score

def get_reductor_and_classificator(X, y, reduction='pca', classification='lda'):
    """
    获取训练好的降维-分类模型
    :param X:
    :param y:
    :param reduction:
    :param classification:
    :return: reductor, classificator, X_r(降维后的数据)
    """
    # # 增加噪声
    # X, y = gauss_noisy(X, y)
    # 定义降维器
    n_components = 2
    # if X.shape[1] >= 3:
    #     n_components = 3
    reductor = decomposition.PCA(n_components=n_components)
    # reductor = decomposition.PCA()
    reductor.fit(X)
    X_r = reductor.transform(X)
    if reduction == 'lda':
        reductor = discriminant_analysis.LinearDiscriminantAnalysis(n_components=1)
        reductor.fit(X, y)
        X_r = reductor.transform(X)
    elif reduction == 't-pca':
        reductor = decomposition.TruncatedSVD(n_components=2)
        reductor.fit(X)
        X_r = reductor.transform(X)
    elif reduction == 'nca':
        reductor = neighbors.NeighborhoodComponentsAnalysis(random_state=42)
        reductor.fit(X, y)
        X_r = reductor.transform(X)
    elif reduction == 'pls':
        # 然后对y进行转换
        y_labels = pd.get_dummies(y)
        # 建模
        reduction = PLSRegression(n_components=n_components)
        reduction.fit(X, y_labels)
        X_r = reductor.transform(X)
    elif reduction == 'none':
        X_r = X

    # 定义分类器
    classificator = discriminant_analysis.LinearDiscriminantAnalysis(solver="svd")
    # classificator = discriminant_analysis.LinearDiscriminantAnalysis(solver='lsqr')
    if classification == 'qda':
        classificator = discriminant_analysis.QuadraticDiscriminantAnalysis()
    elif classification == 'svm':
        classificator = svm.LinearSVC(random_state=0)
    elif classification == 'knn':
        classificator = neighbors.KNeighborsClassifier(n_neighbors=3, weights='distance')

    classificator.fit(X_r, y)

    return reductor, classificator, X_r

# 交叉评估SVM分数
def SVM_cross_evaluation(X, y):
    # 随机打乱
    random_state = 0

    svmm = svm.SVC(kernel="linear", probability=True, random_state=random_state)

    # 评分默认采用各评估器自带score函数，也可用scoring指定
    scores = model_selection.cross_val_score(svmm, X, y, cv=5)
    print("SVM_cross_evaluation scores: ", scores)
    print("Accuracy: %0.2f (+/- %0.2f)" % (scores.mean(), scores.std() * 2))

    # scores_f1 = model_selection.cross_val_score(lda, X, y, cv=10, scoring="f1_macro")
    # print("LDA_cross_evaluation f1_macro scores: ", scores_f1)
    # print("f1_macro Accuracy: %0.2f (+/- %0.2f)" % (scores_f1.mean(), scores_f1.std() * 2))

    return scores

# PCA及结果绘制
def myPCA(X, y, target_names, isnumber=False, n_components=5, title='PCA of dataset', is_picture=True):
    pca = decomposition.PCA(n_components=n_components)
    X_r = pca.fit_transform(X)

    if is_picture:
        plt.figure()
        lw = 2
        if isnumber:
            for i in range(X_r.shape[0]):
                plt.text(X_r[i, 0], X_r[i, 1], str(i))

        if n_components == 3:
            ax3d = plt.gca(projection="3d")  # 创建三维坐标
            colors = ['navy', 'turquoise', 'darkorange']
            for color, i, target_name in zip(colors, [0, 1], target_names):
                ax3d.scatter(X_r[y == i, 0], X_r[y == i, 1], X_r[y == i, 2], color=color, alpha=.8, lw=lw,
                             label=target_name)

            plt.legend(loc='best', shadow=False, scatterpoints=1)
            plt.title(title)
            plt.show()
        if n_components == 2:
            colors = ['navy', 'turquoise']
            for color, i, target_name in zip(colors, [0, 1], target_names):
                plt.scatter(X_r[y == i, 0], X_r[y == i, 1], color=color, alpha=.8, lw=lw,
                             label=target_name)

            plt.legend(loc='best', shadow=False, scatterpoints=1)
            plt.title(title)
            plt.show()
    return X_r

# PCA及结果绘制
def myPCAResult(X, y, n_components=2):
    pca = decomposition.PCA(n_components=n_components)
    X_r = pca.fit(X).transform(X)
    return X_r

# 多分类LDA及结果绘制
def myLDAForMul(X, y, target_names, isnumber=False, tag_false=False):
    lda = discriminant_analysis.LinearDiscriminantAnalysis(n_components=2)
    X_r2 = lda.fit(X, y).transform(X)
    scores = lda.decision_function(X)
    predict_y = lda.predict(X)

    # plt.figure()
    # colors = ['navy', 'turquoise']
    colors = ['navy', 'turquoise', 'darkorange']
    lw = 2
    plt.figure()
    # 数字标记
    if isnumber:
        for i in range(X_r2.shape[0]):
            plt.text(X_r2[i, 0], X_r2[i, 1], str(i))
    # 错误标记
    if tag_false:
        for i in range(X_r2.shape[0]):
            if(predict_y[i] != y[i]):
                plt.text(X_r2[i, 0], X_r2[i, 1], str(i), color='red')

    # for color, i, target_name in zip(colors, [0, 1, 2], target_names):
    #     plt.scatter(X_r2[y == i, 0], X_r2[y == i, 1], alpha=.8, color=color,
    #                 label=target_name)
    # plt.legend(loc='best', shadow=False, scatterpoints=1)
    plt.title('LDA of Thoracic Dataset')
    # # 画一下决策边界
    # plot_decision_boundary(X_r2, y)
    plot_lda_result(X_r2, y, target_names)
    plt.show()

# 多分类LDA及结果绘制
def myLDAForTwo(X, y, target_names, title, isnumber=False, tag_false=False):
    lda = discriminant_analysis.LinearDiscriminantAnalysis(n_components=2)
    X_r2 = lda.fit(X, y).transform(X)
    predict_y = lda.predict(X)

    plt.figure()
    # # 数字标记
    if isnumber:
        for i in range(X_r2.shape[0]):
            plt.text(X_r2[i, 0], X_r2[i, 1], str(i))
    # 错误标记
    if tag_false:
        for i in range(X_r2.shape[0]):
            if(predict_y[i] != y[i]):
                plt.text(X_r2[i, 0], X_r2[i, 1], str(i), color='red')

    # plt.title('LDA of Thoracic Dataset')
    # # 画一下决策边界
    # plot_decision_boundary(X_r2, y)
    plot_lda_result(X_r2[:-1, :], y[:-1], target_names, title)
    plt.show()

# 二分类时序图
def binaryTimeSeries(X, y, before_series, after_series, target_names, title, isnumber=False, tag_false=False):
    lda = discriminant_analysis.LinearDiscriminantAnalysis(n_components=2)
    lda.fit(X, y)
    X_r2 = lda.transform(X)
    before_series_r2 = lda.transform(before_series)
    after_series_r2 = lda.transform(after_series)

    plt.figure()
    plot_time_series(X_r2[:-3, :], y[:-3], before_series_r2, after_series_r2, target_names, title)
    plt.show()


# 二分类LDA及结果绘制
def myLDA(X, y, target_names, isnumber=False):
    lda = discriminant_analysis.LinearDiscriminantAnalysis(n_components=1)
    X_r2 = lda.fit(X, y).transform(X)
    scores = lda.decision_function(X)
    predict_y = lda.predict(X)

    # plt.figure()
    # colors = ['navy', 'turquoise']
    colors = ['navy', 'turquoise', 'darkorange']
    lw = 2
    plt.figure()
    # 数字标记
    if isnumber:
        for i in range(X_r2.shape[0]):
            if(predict_y[i] == y[i]):
                plt.text(X_r2[i, 0], X_r2[i, 0], str(i))
            else:
                plt.text(X_r2[i, 0], X_r2[i, 0], str(i), color='red')

    for color, i, target_name in zip(colors, [0, 1, 2], target_names):
        plt.scatter(X_r2[y == i, 0], X_r2[y == i, 0], alpha=.8, color=color,
                    label=target_name)
    plt.legend(loc='best', shadow=False, scatterpoints=1)
    plt.title('LDA of Thoracic Dataset')
    # # 画一下决策边界
    # plot_decision_boundary(X, y)
    # plot_lda_result(X_r2, y, target_names)
    plt.show()

# 绘制决策边界(二分类可用）
def plot_decision_boundary(X, y):
    x_min, x_max = X[:, 0].min() - .5, X[:, 0].max() + .5
    y_min, y_max = X[:, 1].min() - .5, X[:, 1].max() + .5
    h = 0.01
    xx, yy = np.meshgrid(np.arange(x_min, x_max, h), np.arange(y_min, y_max, h))

    lda = discriminant_analysis.LinearDiscriminantAnalysis(n_components=2)
    lda.fit(X, y)
    # 用预测函数预测一下
    Z = lda.predict(np.c_[xx.ravel(), yy.ravel()])
    Z = Z.reshape(xx.shape)

    # 然后画出图
    plt.contourf(xx, yy, Z, cmap=plt.cm.Spectral)
    # plt.scatter(X[:, 0], X[:, 1], c=y, cmap=plt.cm.Spectral)



def single_case_time_series(X, y, indices, target_names):
    caseX = X[indices, :]
    caseY = y[indices]

    lda = discriminant_analysis.LinearDiscriminantAnalysis(n_components=2)
    lda.fit(X, y)
    X_r2 = lda.transform(X)
    caseX_r2 = lda.transform(caseX)
    scores = lda.decision_function(X)
    predict_y = lda.predict(X)

    # plt.figure()
    # colors = ['navy', 'turquoise']
    colors = ['navy', 'turquoise', 'darkorange']
    lw = 2
    plt.figure()
    # 数字标记

    for i in range(X_r2.shape[0]):
        if(predict_y[i] == y[i]):
            plt.text(X_r2[i, 0], X_r2[i, 1], str(i))
        else:
            plt.text(X_r2[i, 0], X_r2[i, 1], str(i), color='red')

    for color, i, target_name in zip(colors, [0, 1, 2], target_names):
        plt.scatter(X_r2[y == i, 0], X_r2[y == i, 1], alpha=.8, color=color,
                    label=target_name)
    # 画时间序列样本点
    plt.scatter(caseX_r2[:, 0], caseX_r2[:, 1], color='red', label='target')
    # 连虚线
    plt.plot(caseX_r2[:, 0], caseX_r2[:, 1], color='red', linestyle='--')


    plt.legend(loc='best', shadow=False, scatterpoints=1)
    plt.title('LDA of Thoracic Dataset')
    # # 画一下决策边界
    # plot_decision_boundary(X, y, lambda x: lda.predict(x))
    plt.show()


def find_error_samples(X, Y, tags, target_names):
    """
    输出模型预测中错误预测的样本信息
    :param X:
    :param Y:
    :param tags: 对应X中样本顺序的样本编号(即样本采样管贴的编号)，list()
    :param target_names: 对应y值编码的样本类型, list()
    :return: 模型预测中错误预测的样本信息, pd.DataFrame(columns=["index", "real_type", "predict_type"])
    """
    lda = discriminant_analysis.LinearDiscriminantAnalysis(n_components=len(target_names)-1)
    lda.fit(X, Y)
    predict_Y = lda.predict(X)
    error_samples = pd.DataFrame(columns=["index", "real_type", "predict_type"])
    for i in range(Y.shape[0]):
        if(predict_Y[i] != Y[i]):
            error_samples.append([tags[i], target_names[Y[i]], target_names[predict_Y[i]]])
    print(error_samples)
    return error_samples

def treeForKBest(X, Y):
    """
    使用分类数找到K个最关联的特征
    :param X:
    :param Y:
    :return:
    """
    X = pd.DataFrame(X)
    Y = pd.DataFrame(Y)
    display_num = min(20, X.shape[1])
    pd.set_option('display.max_columns', None)
    x_train, x_test, y_train, y_test = model_selection.train_test_split(X, Y, test_size=0.2, random_state=7)
    classifier = AdaBoostClassifier(n_estimators=100)
    classifier.fit(x_train, y_train)
    y_test_pred = classifier.predict(x_test)
    print(np.mean(y_test_pred == np.array(y_test)))
    feature_importances = 100.0 * classifier.feature_importances_ / max(classifier.feature_importances_)
    values = np.flipud(np.sort(feature_importances))[0:display_num]
    index_sorted = np.flipud(np.argsort(feature_importances))[0:display_num]
    plt.figure()
    plt.bar(np.arange(display_num), values)
    plt.xticks(np.arange(display_num), X.columns.values[index_sorted])
    plt.show()

def KNNforKBest():
    return



