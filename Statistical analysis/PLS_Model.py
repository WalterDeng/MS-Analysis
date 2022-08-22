from PLS_Method import *


# 读取数据集
MODEL_TAG = 'ZS1E_LUNG2'
Height, Area, Y, target_names, extra_info = load_samples(MODEL_TAG)
X = Area

PLS = PLS_Model()

# 获取最好的删减比例
# PLS.get_del_value(X, Y, target_names)

# 删减稀疏数据
# X, _ = del_0(X, 0.2)

test_size = 0.2
PLS.fit(X, Y, target_names, MODEL_TAG, test_size=test_size, random_state=0)

PLS.plot_VIP()

PLS.plot_scores(PLS.x_train, PLS.x_test, PLS.y_train, PLS.y_test)
PLS.show_metrics(PLS.x_train, PLS.x_test, PLS.y_train, PLS.y_test)

print("取biomarker后：")
PLS.training_for_biomarkers()
# biomarkers = PLS.biomarkers_of_VIP['index'][:PLS.biomarkers_num]
biomarkers = [38 ,97,88,84,42,64,98,99,61,106,24]
PLS.plot_scores(PLS.x_train[:, biomarkers], PLS.x_test[:, biomarkers], PLS.y_train, PLS.y_test)
PLS.show_metrics(PLS.x_train[:, biomarkers], PLS.x_test[:, biomarkers], PLS.y_train, PLS.y_test)





x_train, x_test, y_train, y_test = model_selection.train_test_split(X, Y, test_size=test_size, random_state=0)
print_sample_num(Y)
print_sample_num(y_test)

# # 获取biomarkers次数表，有模型相关性系数和VIP两种指标
# biomarkers_of_coefs, biomarkers_of_VIP = record_variable_times(X, Y, MODEL_TAG, coef_thresh=0.035, VIPs_thresh=1.5)
#
# # 测试获取最终biomarker
# print("开始测试 VIP-biomarkers:")
# VIP_biomarkers_index = biomarkers_of_VIP['index']
# VIP_best_num = plot_biomarkers(X, Y, VIP_biomarkers_index, target_names, MODEL_TAG + "_biomarkers_of_VIP.csv")
# # 提取biomarker数据获取最终结果
# VIP_biomarker_index = VIP_biomarkers_index[0:VIP_best_num]
# print("VIP_best_num: ", VIP_best_num)
# # VIP_biomarker_index = [57, 66, 65, 3, 67, 56, 17, 24, 5, 58, 27, 7, 4, 73, 45, 80, 33, 70, 90, 79, 39, 12, 63, 6, 37]
# X_VIP = X[:, VIP_biomarker_index]
# # X_VIP = normalizeArea(X_VIP)
# biomarker_result_display(X_VIP, Y, target_names)
# mean_accuracy, mean_AUC, mean_sensitivity, mean_specificity, mean_precision, mean_F1 = accuracy_for_PLS(X_VIP, Y, target_names, repeat_times=10000)
#
# print("开始测试 Coefs-biomarkers:")
# coef_biomarkers_index = biomarkers_of_coefs['index']
# coef_best_num = plot_biomarkers(X, Y, coef_biomarkers_index, target_names, MODEL_TAG + "_biomarkers_of_coefs.csv")
# # 提取biomarker数据获取最终结果
# coef_biomarkers_index = coef_biomarkers_index[0:coef_best_num]
# print("coef_best_num: ", coef_best_num)
# X_Coef = X[:, coef_biomarkers_index]
# # X_Coef = normalizeArea(X_Coef)
# biomarker_result_display(X_Coef, Y, target_names)
# accuracy_for_PLS(X_Coef, Y, target_names, repeat_times=10000)