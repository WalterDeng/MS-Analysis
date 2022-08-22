from sklearn import preprocessing
from sklearn import model_selection
from sklearn import discriminant_analysis
from myEvaluation import LDA_cross_evaluation, compute_PCA_LDA_score, get_reductor_and_classificator, evaluation_model, get_cross_evaluation, compute_cross_score
from plot_lda_qda import plot_data, plot_lda_cov, plot_one_dimension_data
import numpy as np
from ROCandAUC import get_roc, draw_roc_picture
from data_util import *
from features_tag import *
from myEvaluation import myPCA, compute_PLS_DA_score, get_PLS_scores
from sklearn import decomposition
import matplotlib.pyplot as plt

def test_standard_scaler(X, y):
    print("test_standard_scaler...")
    scaler = preprocessing.StandardScaler()
    scaler.fit(X)
    X_transformed = scaler.transform(X)
    LDA_cross_evaluation(X_transformed, y)
    return

def normalizeArea(X):
    A_sum = np.sum(X, axis=1).reshape(-1, 1)
    X = np.nan_to_num(X / A_sum)

    # for i in range(X.shape[0]):
    #     X[i, :] = X[i, :] / A_sum[i]
    return X

def test_all_area_scaler(X, y):
    print("test_all_area_scaler...")
    X_transformed = normalizeArea(X)
    LDA_cross_evaluation(X_transformed, y)
    return

def test_normalization_to_roc(X, y, n_classes = 3):
    title = "Before any normalization."
    get_roc(X, y, title)

    title = "After standard normalization."
    X_standard = X
    scaler = preprocessing.StandardScaler()
    scaler.fit(X_standard)
    X_standarded = scaler.transform(X_standard)
    get_roc(X_standarded, y, title)

    title = "After all_area normalization."
    X_area = X
    X_areaed = normalizeArea(X_area)
    get_roc(X_areaed, y, title)

    return

# 根据各大分类模型的得分进行子集选择
def peak_subset_selection_by_score(X, y, max_feature=20, reduction='lda', classification='lda', is_plot=True, is_write=True, is_print=True, data_path=""):
    n_samples, n_features = X.shape

    # 初始化迭代的cache
    cur_aucs = dict()  # {features1 : [auc1, distanct1], features2 : [auc2, distanct2], ...}, features: (1, 2, ...)
    history_features = dict()
    history_aucs = list()
    for f1 in range(0, n_features):
        temp = (f1,)
        cur_aucs[temp] = [0, 0]

    best_features = ()
    best_score = [0, 0]

    # 依次遍历最大特征
    for i in range(2, max_feature):
        new_aucs = dict()
        last_best_score = best_score

        ## 遍历当前特征列表
        for features in cur_aucs.keys():

            ## 依次加入新特征并计算auc
            for num_f in range(0, n_features):

                if num_f in features:
                    # 加入重复特征则跳过
                    continue

                features_l = list(features)
                features_l.append(num_f)
                features_l.sort()
                features_t = tuple(features_l)
                ## 先查重，再计算，减少计算量
                if new_aucs.get(features_t, -1) != -1:
                    continue
                ## 使用添加后的features计算auc
                try:
                    Xs = X[:, features_l]
                    Xs = normalizeArea(Xs)
                    if reduction == 'pls':
                        cur_score = compute_PLS_DA_score(Xs, y)
                    else:
                        # cur_score = compute_score(Xs, y, scoreing=scoreing)
                        cur_score = compute_PCA_LDA_score(Xs, y,reduction=reduction, classification=classification)
                        # cur_score = compute_cross_score(Xs, y, reduction=reduction, classification=classification)

                    new_aucs[features_t] = cur_score
                    ## 记录最佳组合
                    if cur_score > best_score:
                        best_features = features_l
                        best_score = cur_score
                except Exception as e:
                    # print("Xs: ", X[:, features_l])
                    print("error: ", e)

        ## 排序，输出前100项
        sorted_list = list(new_aucs.items())
        sorted_list.sort(key=lambda a : a[1], reverse=True)
        sorted_list = sorted_list[0:200]

        history_aucs.append(sorted_list[0][1][1])
        this_best_score = sorted_list[0][1]


        history_features[i] = list(sorted_list[0][0])

        ## 更新数据
        cur_aucs.clear()
        cur_aucs = dict(sorted_list)

        ## 写入文件
        if is_write:
            write_list(data_path + "features_file\\" + "features" + str(i) + ".txt", sorted_list)

        if is_print:
            print("already completed: ", i)

        # 分类精度下降时停止
        if best_score > this_best_score:
            print("best_score begin down from i:", i)
            print("this_best_score: ", this_best_score)
        #     break
    if is_print:
        print("best_score: ", best_score, ", best_features: ", best_features)

    if is_write:
        write_list(data_path + "features_file\\" + "features_best.txt", list(history_features.items()))

    if is_plot:
        fig = plt.figure()
        plt.plot(np.arange(2,max_feature), history_aucs)
        plt.title("Boundary distance variation diagram")
        plt.show()

    return best_score, best_features, history_aucs, history_features

def PCA_change_by_features(X, y, target_names, feature_chage_tag):
    features = FEATURE_CHANGE.get(feature_chage_tag)
    fig, axes = plt.subplots(3, 3)
    colors = ['navy', 'turquoise']
    for features_i, ax in zip(features.items(), axes.ravel()):
        [n_features, best_features] = features_i
        Xi = X[:, best_features]
        title = "PCA of " + str(n_features) + " features"
        X_r = myPCA(Xi, y, target_names, n_components=2, title=title, is_picture=False)
        for color, i, target_name in zip(colors, [0, 1], target_names):
            ax.scatter(X_r[y == i, 0], X_r[y == i, 1], color=color, alpha=.8, lw=2,
                        label=target_name)
        ax.legend(loc='best', shadow=False, scatterpoints=1)
        ax.set_title(title)
    # fig.show()

from SCI_PLOT import plot_two_dimension_data

def visual_optimal_subset(x_train, x_test, y_train, y_test, target_names, feature_change_tag, train_names, test_names, reduction='pca', classification='lda', is_draw_ROC=True):
    """
    对各个特征子集的模型训练情况进行分析和可视化
    """
    features = FEATURE_CHANGE.get(feature_change_tag)

    # 遍历最优子集
    for features_i in features.items():
        [n_features, best_features] = features_i

        print("n_features: %i" % n_features)
        x_train_i = x_train[:, best_features]
        x_test_i = x_test[:, best_features]
        x_train_i = normalizeArea(x_train_i)
        x_test_i = normalizeArea(x_test_i)

        # 模型 fit
        reductor, classificator, x_train_reduction = \
            get_reductor_and_classificator(x_train_i, y_train, reduction=reduction, classification=classification)

       # 单独测试个人在模型中的情况
       # one_person_test()

        # 模型参数评价
        print("train set parameter evaluation begin:")
        x_train_reduction, y_train_pred = parameter_evaluation(x_train_i, y_train, reductor, classificator, target_names)
        print("test set parameter evaluation begin:")
        x_test_reduction, y_test_pred = parameter_evaluation(x_test_i, y_test, reductor, classificator, target_names)

        # 打印错误样本
        print("train set error samples:")
        print_error_sample_name(y_train, y_train_pred, train_names)
        print("test set error samples:")
        print_error_sample_name(y_test, y_test_pred, test_names)

        # 绘制散点分布图
        sample_plot(x_test_reduction, y_test, y_test_pred, target_names, reduction, classificator)



def one_person_test(best_features, reductor, classificator):
    from onePersonTest import get_person_X
    onePerson = get_person_X(best_features)
    onePerson = normalizeArea(onePerson)
    onePerson_reduction = reductor.transform(onePerson)
    onePerson_reduction[0, 1] = onePerson_reduction[0, 1]-0.7
    predict = classificator.predict_proba(onePerson_reduction)
    distance = classificator.decision_function(onePerson_reduction)
    print("predict: ", np.round(predict, 3), ", distance: ", distance)

def print_error_sample_name(y, y_pred, sample_names):
    print("error_sample_name:", sample_names[y != y_pred])

def sample_plot(X, y, y_pred, target_names, reduction, classificator):
    """
    # 绘制散点分布图
    """
    if reduction == 'pca':
        title = "PCA Plot"
        plot_two_dimension_data(X, y, target_names, title)
    elif reduction == 'lda':
        title = "Distribution of the subjects' data for the three LDA components"
        plot_data(classificator, X, y, y_pred, target_names, title)
    elif reduction == 'pls':
        title = "Distribution of the subjects' data for the three PLS components"
        plot_data(classificator, X, y, y_pred, target_names, title)
    plt.show()

def parameter_evaluation(X, y, reductor, classificator, target_names):
    """
    # 模型参数评价
    """
    X_tran = reductor.transform(X)
    y_pred = classificator.predict(X_tran)
    y_distance = classificator.decision_function(X_tran)
    evaluation_model(y, y_pred, y_distance, target_names)
    return X_tran, y_pred

def get_test_scores(x_train, x_test, y_train, y_test, features, reduction='pca', classification='lda'):

    test_scores = []

    for features_i in features.items():
        [n_features, best_features] = features_i

        x_train_i = x_train[:, best_features]
        x_test_i = x_test[:, best_features]
        x_train_i = normalizeArea(x_train_i)
        x_test_i = normalizeArea(x_test_i)

        reductor, classificator, x_train_reduction = get_reductor_and_classificator(x_train_i, y_train,
                                                                                    reduction=reduction,
                                                                                    classification=classification)
        # 转变测试数据
        x_test_reduction = reductor.transform(x_test_i)
        y_test_pred = classificator.predict(x_test_reduction)
        y_test_distance = classificator.decision_function(x_test_reduction)
        scores = evaluation_model(y_test, y_test_pred, y_test_distance, [], is_print=False)

        ACC = scores["accuracy"]
        AUC = scores["AUC"]
        sensitivity = scores["sensitivity"]
        specificity = scores["specificity"]

        test_scores.append([n_features, [ACC, AUC, sensitivity, specificity]])

    test_scores.sort(key=lambda a: a[1], reverse=True)
    best_n = test_scores[0][0]
    best_score = test_scores[0][1]
    return best_n, best_score



def find_reduction_model(Height, Area, y, target_names, reduction='pca', classification='lda'):
    """
    针对有降维的模型：对比不同test_size, Height/Area的5倍交叉验证值
    :param Height:
    :param Area:
    :param y:
    :param target_names:
    :param reduction:
    :param classification:
    :return:
    """
    for X, tag in zip([Height, Area], ['Height', 'Area']):
        X = normalizeArea(X)
        history = pd.DataFrame(columns=['test_size', 'y_score', 'scores_mean', 'scores'])
        for test_size in range(2, 8, 1):
            test_size = test_size / 10
            x_train, x_test, y_train, y_test = model_selection.train_test_split(X, y, test_size=test_size, random_state=16)
            print_sample_num(y_test)
            best_score, best_features, history_aucs, history_features = peak_subset_selection_by_score(x_train, y_train,
                                                                                                       max_feature=20,
                                                                                                       reduction=reduction,
                                                                                                       classification=classification, is_write=False, is_plot=False)
            x_train_i = x_train[:, best_features]
            reductor, classificator, x_train_reduction = get_reductor_and_classificator(x_train_i, y_train,
                                                                                        reduction=reduction,
                                                                                        classification=classification)
            # 转变测试数据
            x_test_i = x_test[:, best_features]
            x_test_reduction = reductor.transform(x_test_i)
            Xi = np.concatenate((x_train_reduction, x_test_reduction), axis=0)
            yi = np.concatenate((y_train, y_test), axis=0)
            y_score = classificator.score(Xi, yi)
            scores, scores_mean = LDA_cross_evaluation(Xi, yi)
            a = pd.DataFrame([[test_size, y_score, scores_mean, scores]], columns=['test_size', 'y_score', 'scores_mean', 'scores'])
            history = history.append(a)
        print(tag + ": ")
        print(history)

def find_classification_model(Height, Area, y):
    """
    针对直接分类的模型：对比不同test_size, Height/Area的5倍交叉验证值
    :param Height:
    :param Area:
    :param y:
    :return:
    """
    X = Area
    X = normalizeArea(X)
    for reduction, classification in zip(['none', 'nca'], ['svm', 'knn']):
        history = pd.DataFrame(columns=['test_size', 'y_score', 'scores_mean', 'scores'])
        for test_size in range(1, 8, 1):
            test_size = test_size / 10
            x_train, x_test, y_train, y_test = model_selection.train_test_split(X, y, test_size=test_size, random_state=16)
            print_sample_num(y_test)
            best_score, best_features, history_aucs, history_features = peak_subset_selection_by_score(x_train, y_train,
                                                                                                       max_feature=20,
                                                                                                       reduction=reduction,
                                                                                                       classification=classification, is_write=False, is_plot=False)
            x_train_i = x_train[:, best_features]
            reductor, classificator, x_train_reduction = get_reductor_and_classificator(x_train_i, y_train,
                                                                                        reduction=reduction,
                                                                                        classification=classification)
            # 转变测试数据
            x_test_i = x_test[:, best_features]
            x_test_reduction = reductor.transform(x_test_i)
            Xi = np.concatenate((x_train_reduction, x_test_reduction), axis=0)
            yi = np.concatenate((y_train, y_test), axis=0)
            y_score = classificator.score(Xi, yi)
            scores, scores_mean = get_cross_evaluation(Xi, yi, classification)
            a = pd.DataFrame([[test_size, y_score, scores_mean, scores]], columns=['test_size', 'y_score', 'scores_mean', 'scores'])
            history = history.append(a)
        print(reduction + classification + ": ")
        print(history)

def draw_pictures():
    # 1、PCA-LDA和LDA-LDA的差异
    test_size = [0.2, 0.3, 0.4, 0.5, 0.6, 0.7]
    lda_area = [0.9, 0.75, 0.8, 0.75, 0.75, 0.65]
    lda_height = [0.9, 0.9, 0.85, 0.7, 0.75, 0.30]
    pca_area = [0.4, 0.6, 0.8, 0.7, 0.7, 0.6]
    pca_height = [0.6, 0.55, 0.5, 0.7, 0.65, 0.45]



    plt.scatter(test_size, lda_area, marker=".", color="navy", label='lda_area')
    plt.plot(test_size, lda_area, color="navy", lw=2)
    plt.scatter(test_size, lda_height, marker="^", color="navy", label='lda_height')
    plt.plot(test_size, lda_height, color="navy", lw=2)
    plt.scatter(test_size, pca_area, marker=".", color="darkorange", label='pca_area')
    plt.plot(test_size, pca_area, color="darkorange", lw=2)
    plt.scatter(test_size, pca_height, marker="^", color="darkorange", label='pca_height')
    plt.plot(test_size, pca_height, color="darkorange", lw=2)

    plt.show()

    n_feauture = np.arange(3,20, 2)
    test_score = np.array([0.5,0.5,0.5,0.625,0.625,0.375,0.625,0.625,0.625])
    plt.plot(n_feauture, test_score, color="darkorange", lw=2)
    plt.title("svm score in different features")
    plt.show()


    # 2、source和normalize的差异

# draw_pictures()

def check_feature_set(DataTag, X, y, target_name, feature_set, retain_index):
    Rt = load_peak_group_infos(DataTag)
    ymin = -0.1
    ymax = np.max(X)
    Rt = Rt.iloc[retain_index]
    # plt.plot(X[y==0, :].T, color="#990000", lw=0.5)  # dark blue
    #
    # plt.plot(X[y == 1, :].T, color="#000099", lw=0.5)  # dark blue
    plt.plot(X[y == 1, :].T, color="#000099", lw=0.5)  # dark blue
    for feature in feature_set:
        rt = Rt.iloc[feature]
        print(feature, ": ", rt)
        plt.vlines(feature, ymin, ymax, 'black', '--', label=str(feature))

    plt.title("check_feature_set")
    plt.legend()
    plt.show()

def see_biomarkers_in_data(group_infos, index, time_series, Raw_data, y, target_name, biomarkers, retain_index):

    # 画出两种样本图谱
    Raw_data = Raw_data[index, :]
    y = y[index]
    plt.plot(time_series, Raw_data[0, :].T + 0, color="darkblue", label=target_name[0])  # dark blue
    plt.plot(time_series, Raw_data[1, :].T + 3000000, color="darkblue")  # dark blue
    plt.plot(time_series, Raw_data[2, :].T + 6000000, color="darkred", label=target_name[1])  # dark blue
    plt.plot(time_series, Raw_data[3, :].T + 9000000, color="darkred")  # dark blue

    # 标记峰的位置
    Rt = group_infos["avgRt"]
    Height = group_infos["avgH"]

    ymin = -0.1
    ymax = np.max(Raw_data)
    ylimit = 15000000
    xlimit = 25
    if len(retain_index) != 0:
        Rt = Rt.iloc[retain_index]
        Height = Height.iloc[retain_index]

    for feature in biomarkers:
        rt = Rt.iloc[feature]
        height = Height.iloc[feature]
        print(feature, ": ", rt)
        plt.vlines(rt, ymin, ylimit, color="darkorange")
        plt.text(rt, ylimit, str(feature), color="darkorange")
        # plt.scatter(rt, ymin, marker="*", color="darkorange", label='biomarker_'+ str(feature))
    plt.ylim(0, ylimit)
    plt.xlim(0, xlimit)
    # plt.title("Biomarker distribution plot")
    plt.legend()
    plt.show()