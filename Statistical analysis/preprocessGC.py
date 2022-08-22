import numpy as np
from sklearn import preprocessing
from sklearn import model_selection
from data_util import *
from myPreprocessing import *
from myEvaluation import *
from features_tag import *
from Peak_subset_selection import peak_subset_selection
from diomenReduction import diomensionReduction
import pandas as pd
from pandas import DataFrame

# BEST_FEATURES_HEALTHY_LUNG = [0, 51, 84, 122, 129, 153, 206, 235, 244, 300]

# ------------------------------------------------------- FUNCTION ------------------------------------------------#
# 肺癌病人时序变化
def lung_time_series():
    X, Y, target_names, Area, lung_series_dict = load_lung_series()
    # test_evaluation(X, Y)

    X = normalizeArea(X)
    X = X[:, BEST_FEATURES.get("lung_healthy")]

    Area = normalizeArea(Area)
    Area = Area[:, BEST_FEATURES.get("lung_healthy")]

    for person_name, lung_indices in lung_series_dict.items():
        before_series = Area[lung_indices["before"], :]
        after_series = Area[lung_indices["after"], :]
        print("person_name: ",person_name, ", lung_indices: ", lung_indices)
        binaryTimeSeries(X, Y, before_series, after_series, target_names, title="Time Series Of "+person_name, isnumber=False, tag_false=True)
    return

# 肺癌与对照
def healthy_and_lung():
    X, Y, target_names, tags, X3, Y3 = load_healthy_lung()
    X3 = normalizeArea(X3)
    X3 = X3[:, BEST_FEATURES.get("lung_healthy")]
    find_error_samples(X, Y, tags, target_names)
    # myPCA(X, Y, target_names)
    myLDAForTwo(X3, Y3, target_names, title="LDA oF healthy_and_lung", isnumber=False, tag_false=True)
    return

# 胸腺瘤与对照
def healthy_and_thoracic():
    X, Y, target_names, RawData = load_healthy_thoracic()
    # X3 = normalizeArea(X3)
    # X3 = X3[:, BEST_FEATURES.get("thoracic_healthy")]
    # myLDAForTwo(X3, Y3, target_names, title="LDA oF healthy_and_thoracic", isnumber=False, tag_false=True)
    return

# 肺癌与胸腺瘤
def lung_and_thoracic():
    X, Y, target_names, X3, Y3 = load_lung_thoracic()
    X3 = normalizeArea(X3)
    X3 = X3[:, BEST_FEATURES.get("lung_thoracic")]
    myLDAForTwo(X3, Y3, target_names, title="LDA Of lung_and_thoracic", isnumber=False, tag_false=True)
    return

# 密西根结肠癌数据
def colon_and_healthy():
    X, Y, target_names, tags, X3, Y3 = load_healthy_lung()
    print_sample_num(Y)
    X = normalizeArea(X)
    # X = X[:, BEST_FEATURES.get("lung_healthy")]
    # 随机打乱
    # X, Y = shuffle(X, Y)
    # print_sample_num(Y)
    x_train, x_test, y_train, y_test = model_selection.train_test_split(X, Y, test_size=0.2, random_state=16)
    # x_train_add, y_train_add, x_train, y_train = gauss_noisy(x_train, y_train, 30)
    # x_train = normalizeArea(x_train)
    # x_train_add = normalizeArea(x_train_add)
    # x_test = normalizeArea(x_test)
    print_sample_num(y_test)
    # change_by_features(x_train, x_test, y_train, y_test, target_names, "lung_healthy_PCA", reduction='pca', classification='lda')
    check_feature_set(X, Y, target_names, [0, 9, 36, 56, 57, 64, 73, 76, 84, 105, 115, 126, 138, 145, 149, 157, 159, 166, 173, 182, 201])
    return


###### ------------------------------------------------------ API -------------------------------------------------- #####
# 肺癌与对照
# healthy_and_lung()

# 肺癌病人时序变化
# lung_time_series()

# 胸腺瘤与对照
# healthy_and_thoracic()

# 肺癌与胸腺瘤
# lung_and_thoracic()

# 密西根结肠癌数据
colon_and_healthy()




def test():
    X, Y, target_names, tags, X3, Y3 = load_healthy_lung()
    X = normalizeArea(X)
    X = X[:, BEST_FEATURES.get("lung_healthy")]
    # # find_error_samples(X, Y, tags, target_names)
    X_r = myPCA(X, Y, target_names, n_components=7)
    # # diomensionReduction(X3, Y3)
    # treeForKBest(X, Y)
    SVM_cross_evaluation(X, Y)
# test()


