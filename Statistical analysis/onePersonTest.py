# 完成单个人的模型分析

import os
import numpy as np
import joblib
import pandas as pd
from data_util import load_samples

OPT_ROOT = "C:\\Users\月神IIIANJIU\OneDrive\工作\DATA\\"
MODEL_TAG = 'ZS1E_LUNG-S'
RAW_DATA_PATH = OPT_ROOT + MODEL_TAG + "\\raw_data"
TEST_DATA_PATH = OPT_ROOT + MODEL_TAG + "\\test_data\\PeaksInfo.csv"
VOC_DATA_PATH = OPT_ROOT + MODEL_TAG + "\\pre_data\\groupsTable.xlsx"


def normalizeA(X):
    A_sum = np.sum(X, axis=1).reshape(-1, 1)
    X = np.nan_to_num(X / A_sum)
    return X

def get_person_X(VOC_ids):
    VOC_num = len(VOC_ids)
    # 加载分析模式对应的biomarker

    test_df = pd.read_csv(TEST_DATA_PATH)
    voc_df = pd.read_excel(VOC_DATA_PATH)
    test_biomarker = np.zeros(VOC_num)

    for i in range(VOC_num):
        j = VOC_ids[i]
        rt_start = voc_df.loc[j, "Rt_start"]
        rt_end = voc_df.loc[j, "Rt_end"]

        for (index, rows) in test_df.iterrows():
            test_b = rows["Rt"]
            if test_b >= rt_start and test_b <= rt_end:
                test_biomarker[i] = test_biomarker[i] + rows["TArea"]
    print("test_biomarker: ", test_biomarker)
    return test_biomarker.reshape(1,-1)

def get_analysis_result(VOC_ids):

    VOC_num = len(VOC_ids)
    # 加载分析模式对应的biomarker

    test_df = pd.read_csv(TEST_DATA_PATH)
    voc_df = pd.read_excel(VOC_DATA_PATH)
    test_biomarker = np.zeros(VOC_num)

    for i in range(VOC_num):
        j = VOC_ids[i]
        test_b = test_df.loc[j, "Rt"]

        for rows in voc_df.iterrows():
            rt_start = rows["Rt_start"]
            rt_end = rows["Rt_end"]
            if test_b >= rt_start and test_b <= rt_end:
                test_biomarker[i] = test_df.loc[j, "TArea"]
    print("test_biomarker: ", test_biomarker)

    Height, Area, Y, target_names, extra_info = load_samples(MODEL_TAG)

    # X = Area[:, VOC_ids]
    X = normalizeA(test_biomarker)

    # 加载分析模式对应训练模型
    Model_name = "saved_model//" + MODEL_TAG + ".pkl"
    Model = joblib.load(Model_name)

    # 评分
    score = Model.score(X)
    print("score:", score)

    return

# ------------------------------------------- TEST ------------------------------------------------------------
# get_analysis_result([])

