"""
模型评估脚本
记录实验过程
"""
import numpy as np
import pandas as pd
from sklearn import model_selection
from sklearn.utils import shuffle
from data_util import *
from myEvaluation import LDA_evaluation, LDA_cross_evaluation, get_cross_evaluation, compute_cross_score
from myPreprocessing import normalizeArea, peak_subset_selection_by_score, get_test_scores, find_classification_model, visual_optimal_subset, check_feature_set, see_biomarkers_in_data
from features_tag import *
from ROCandAUC import get_roc
from Peak_subset_selection import peak_subset_selection
from sklearn.metrics import classification_report, matthews_corrcoef, roc_auc_score, zero_one_loss, average_precision_score, hinge_loss, log_loss
import warnings
warnings.filterwarnings("ignore")


def grid_search_pca_lda():
    """
    网格搜索最优的 test_size, random_state
    :return:
    """
    # 从data_tag加载数据
    Height, Area, Y, target_names, extra_info = load_samples(data_root, data_tag)

    X_1 = Area[Y == 0, :]
    X30 = gauss_noisy(X_1, 30)
    X50 = gauss_noisy(X_1, 50)

    X = np.concatenate((Area, X30, X50), axis=0)
    Y = np.concatenate((Y, Y[Y == 0], Y[Y == 0]))

    # X, retain_index = del_0(X, 0.1)
    # X = normalizeArea(X)
    print_sample_num(Y)

    reduction = 'pca'
    classification = 'lda'
    sizes = np.arange(0.4, 0.7, 0.1)
    randoms = np.arange(1, 50, 10)
    for test_size in sizes:
        for random_state in randoms:
            print("test_size=", test_size, ", random_state=", random_state, ".")

            # 数据划分训练集、测试集
            x_train, x_test, y_train, y_test = model_selection.train_test_split(X, Y, test_size=test_size, random_state=random_state)

            best_score, best_features, history_aucs, history_features = peak_subset_selection_by_score(x_train, y_train, max_feature=11,
                       reduction=reduction, classification=classification, is_plot=False, is_write=False, is_print=False)

            best_n, best_score = get_test_scores(x_train, x_test, y_train, y_test, history_features, reduction=reduction, classification=classification)
            cols = ["test_size", "random_state", "best_n", "best_ACC", "best_AUC", "sensitivity", "specificity"]
            new = [(test_size, random_state, best_n, best_score[0], best_score[1], best_score[2], best_score[3])]
            new_df = pd.DataFrame(new, columns=cols)
            print("new_value: ", str(new))
            try:
                grid_search_score = pd.read_csv("D:\DATA\\grid_search_score.csv")
                new_grid_search_score = grid_search_score.append(new_df, ignore_index=True)
                new_grid_search_score.to_csv("D:\DATA\\grid_search_score.csv", index=False)
            except Exception as e:
                print(e)



def evaluation_pca_lda_model():
    
    # 从data_tag加载数据
    Height, Area, Y, target_names, extra_info = load_samples(data_root, data_tag)
    sample_names = extra_info['sample_names']

    X_1 = Area[Y == 0, :]
    X30 = gauss_noisy(X_1, 30)
    X50 = gauss_noisy(X_1, 50)

    X = np.concatenate((Area, X30, X50), axis=0)
    sample_names = np.concatenate((sample_names, sample_names[Y == 0], sample_names[Y == 0]))
    Y = np.concatenate((Y, Y[Y == 0], Y[Y == 0]))


    print_sample_num(Y)
    # 数据划分训练集、测试集
    test_size = 0.4
    random_state = 0
    x_train, x_test, y_train, y_test, train_names, test_names = \
        model_selection.train_test_split(X, Y, sample_names, test_size=test_size, random_state=random_state)

    # print_train_test_name(X, Y, np.squeeze(extra_info["file_list"]), target_names, test_size=test_size, valid_size=0.2, random_state=0)

    print_sample_num(y_test)

    pre_path = data_root + data_tag + "\model_data\pca\\test_size_" + str(test_size) + "\\"
    # peak_subset_selection_by_score(x_train, y_train, max_feature=12, reduction='pca',classification='lda', data_path=pre_path)
    visual_optimal_subset(x_train, x_test, y_train, y_test, target_names, "lsd_healthy_PCA", train_names, test_names, reduction='pca',classification='lda',is_draw_ROC=False)
    # set = [25]
    # check_feature_set(data_tag, X, Y, target_names, set, retain_index)

    I = np.arange(0, Y.shape[0])
    index = np.concatenate((I[Y==1][6:8], I[Y==0][6:8])) # 挑选阳性、阴性两个样本来看
    time_series = extra_info["time_series"]
    raw_data = extra_info["raw_data"]
    biomarkers = [127, 132, 154, 192, 228, 246]
    retain_index = []
    see_biomarkers_in_data(extra_info["group_infos"], index, time_series, raw_data, Y, target_names, biomarkers, retain_index)

    # model_name = "LUNG-S_2_PCA"
    # pack_model(model_name, x_train, y_train, biomarkers)
    return



def evaluation_lung_healthy():
    data_tag = 'ZS1E_LUNG'
    Height, Area, Y, target_names, extra_info = load_samples(data_tag)
    # 0:9 :1月colon | 10:37 :2月colon | 38:47 :1月control | 48:58 :2月control
    X = Area
    X, retain_index = del_0(X, 0.2)
    # X = normalizeArea(X)
    # X = X[:, BEST_FEATURES.get("thoracic_healthy")]
    # X_to_csv(X, Y, tags, "lung_healthy")
    # db_execute("drop table lung_healthy_data")
    # X_to_db(X, Y, tags, "lung_healthy")
    print_sample_num(Y)

    # 数据划分训练集、测试集
    x_train, x_test, y_train, y_test = model_selection.train_test_split(X, Y, test_size=0.3, random_state=11)
    # print_train_test_name(X, Y, tags, test_size=0.3, random_state=2)
    # x_train_add, y_train_add, x_train, y_train = gauss_noisy(x_train, y_train, 30)
    # x_train = normalizeArea(x_train)
    # x_train_add = normalizeArea(x_train_add)
    # x_test = normalizeArea(x_test)

    print_sample_num(y_test)
    best_score, best_features, history_aucs, history_features = peak_subset_selection_by_score(x_train, y_train,max_feature=20, reduction='pca',classification='lda')
    # visual_optimal_subset(x_train, x_test, y_train, y_test, target_names, "colon_healthy_PCA", reduction='pca',classification='lda', is_draw_ROC=False)
    # set = [25]
    # check_feature_set(data_tag, X, Y, target_names, set, retain_index)

    # index = [8, 33]
    # time_series = extra_info["time_series"]
    # raw_data = extra_info["raw_data"]
    # biomarkers = [2, 8, 14, 17, 31, 32, 38, 74, 84, 90]
    # retain_index = []
    # see_biomarkers_in_data(data_tag, index, time_series, raw_data, Y, target_names, biomarkers, retain_index)
    return

def evaluation_lung_thoracic():
    X, Y, target_names, X3, Y3 = load_lung_thoracic()
    X = normalizeArea(X)
    # best_features = [1, 51, 84, 122, 129, 153, 206, 235, 244, 300]
    X = X[:, BEST_FEATURES.get("lung_thoracic")]
    # 随机打乱
    X, Y = shuffle(X, Y)
    print_sample_num(Y)

    LDA_evaluation(X, Y)
    LDA_cross_evaluation(X, Y)

    # best_score, best_features = peak_subset_selection_by_score(X, Y, max_feature=15)
    # Xr = X[:, best_features]
    # LDA_cross_evaluation(Xr, Y)
    return

def evaluation_thoracic_healthy():
    X, Y, target_names, RawData, tags = load_healthy_thoracic()
    # X_to_csv(X, Y, tags, "thoracic_healthy")
    # db_execute("drop table thoracic_healthy_data")
    # X_to_db(X, Y, tags, "thoracic_healthy")
    X, retain_index = del_0(X, 0.3)
    # X = normalizeArea(X)
    # X = X[:, BEST_FEATURES.get("thoracic_healthy")]
    print_sample_num(Y)

    # 数据划分训练集、测试集
    x_train, x_test, y_train, y_test = model_selection.train_test_split(X, Y, test_size=0.3, random_state=2)
    # print_train_test_name(X, Y, tags, test_size=0.3, random_state=2)
    # x_train_add, y_train_add, x_train, y_train = gauss_noisy(x_train, y_train, 30)
    # x_train = normalizeArea(x_train)
    # x_train_add = normalizeArea(x_train_add)
    # x_test = normalizeArea(x_test)

    print_sample_num(y_test)
    # best_score, best_features, history_aucs, history_features = peak_subset_selection_by_score(x_train, y_train, max_feature=20, reduction='pca', classification='lda')
    # PCA_visual_optimal_subset(x_train, y_train, target_names, "colon_healthy")
    # visual_optimal_subset(x_train, x_test, y_train, y_test, target_names, "thoracic_healthy_pca", reduction='pca', classification='lda', is_draw_ROC=False)
    set = [3, 35, 49, 64]
    check_feature_set(X, Y, target_names, set, retain_index)

def evaluation_colon_healthy():
    data_tag = 'MXG_COLON2'
    Height, Area, Y, target_names, extra_info = load_samples(data_tag)
    # 0:9 :1月colon | 10:37 :2月colon | 38:47 :1月control | 48:58 :2月control
    X = Area
    X, retain_index = del_0(X, 0.2)
    # X = normalizeArea(X)
    # X = X[:, BEST_FEATURES.get("thoracic_healthy")]
    # X_to_csv(X, Y, tags, "lung_healthy")
    # db_execute("drop table lung_healthy_data")
    # X_to_db(X, Y, tags, "lung_healthy")
    print_sample_num(Y)

    # 数据划分训练集、测试集
    x_train, x_test, y_train, y_test = model_selection.train_test_split(X, Y, test_size=0.4, random_state=11)
    # print_train_test_name(X, Y, tags, test_size=0.3, random_state=2)
    # x_train_add, y_train_add, x_train, y_train = gauss_noisy(x_train, y_train, 30)
    # x_train = normalizeArea(x_train)
    # x_train_add = normalizeArea(x_train_add)
    # x_test = normalizeArea(x_test)

    print_sample_num(y_test)
    # best_score, best_features, history_aucs, history_features = peak_subset_selection_by_score(x_train, y_train,max_feature=20, reduction='pca',classification='lda')
    visual_optimal_subset(x_train, x_test, y_train, y_test, target_names, "colon_healthy_PCA", reduction='pca', classification='lda', is_draw_ROC=False)
    # set = [25]
    # check_feature_set(data_tag, X, Y, target_names, set, retain_index)

    # index = [8, 33]
    # time_series = extra_info["time_series"]
    # raw_data = extra_info["raw_data"]
    # biomarkers = [2, 8, 14, 17, 31, 32, 38, 74, 84, 90]
    # retain_index = []
    # see_biomarkers_in_data(data_tag, index, time_series, raw_data, Y, target_names, biomarkers, retain_index)
    return

### --------------------------------------------------------- API ----------------------------------------------------- ###
# Height, Area, Y = load_colon2()
# Y[Y >= 1] = 1
# X = Area
# print_sample_num(Y)
# 随机打乱
# X, Y = shuffle(X, Y, random_state=0)

# 根据选出的最优子集切片
# best_features=[36, 39, 79, 81, 83, 91, 96, 99, 130, 146, 183, 187, 231, 243, 256, 264, 282, 292, 326]
# X = X[:, best_features]

# print("Before Normalization...")
# LDA_evaluation(X, Y)
# LDA_cross_evaluation(X, Y)
# X = normalizeArea(X)
# print("After Normalization...")
# LDA_evaluation(X, Y)
# LDA_cross_evaluation(X, Y)

# 实验一：对比高度和面积分分类结果
# test_standard_scaler(X, Y)
# test_all_area_scaler(X, Y)

# 实验二：不同归一化方式对ROC图的改变
# test_normalization_to_roc(X, Y)

#实验三：测试SVM模型分类准确率
# SVM_cross_evaluation(X, Y)

#实验四：测试先PCA再LDA
# Xr = myPCAResult(X, Y, n_components=9)
# LDA_cross_evaluation(Xr, Y)

#实验五：子集选择算法挑选出峰值
# best_score, best_features = peak_subset_selection_by_score(X, Y)
# Xr = X[:, best_features]
# LDA_cross_evaluation(Xr, Y)

#实验六：观察单例时间序列
# single_case_time_series(X, Y, indices)

#试验七：肺癌和胸腺瘤
# evaluation_lung_thoracic()

#试验八：胸腺瘤和对照
# evaluation_thoracic_healthy()

# 肺癌和对照
# evaluation_lung_healthy()

# 结肠癌和对照（密西根大学数据）
# evaluation_colon_healthy()


# grid_search_pca_lda()
evaluation_pca_lda_model()





