import os

import numpy as np

from data_util import config_
import pandas as pd
from SCI_PLOT import plot_boxplot

root = config_["retest_consistency"]["path"]
start_time = config_["retest_consistency"]["start_time"]
# 1. 处理raw_data
# for file in os.listdir(root):
#     if file[-4:] != '.csv':
#         continue
#     raw = pd.read_csv(root+"\\" + file)
#     raw = raw.loc[:, ["TimeStamp", "PID/HDPID_ADC"]]
#     raw.loc[:, "PID/HDPID_ADC"] = raw.loc[:, "PID/HDPID_ADC"] / 2**31 * 5000
#     raw.loc[:, "TimeStamp"] = raw.loc[:, "TimeStamp"] / 100 - start_time
#     raw = raw.loc[raw.loc[:, "TimeStamp"]>=0, :]
#     raw.to_csv(root+"\\f_" + file, index=False, header=None)

# 3. VOC匹配
voc_data = []
for rt in config_["retest_consistency"]["peak_rt"]:
    diff = rt * 0.1
    RT_START = rt - diff
    RT_END = rt + diff
    voc_data.append([RT_START, RT_END])

match_infos = pd.DataFrame()
for file in os.listdir(root+"\peaks_info"):
    if file[-4:] != '.csv':
        continue
    peaks_info = pd.read_csv(root+"\peaks_info\\" + file, header=None).values

    peak_num = len(peaks_info)
    display_info = []
    for Index in range(peak_num):
        [_, RT, _, Peak_height, _, Peak_area] = peaks_info[Index]
        for row in voc_data:
            # 遍历VOC表
            [RT_START, RT_END] = row
            if RT >= RT_START and RT <= RT_END and Peak_height > 100:
                # 找到峰对应物质
                display_info.append([RT, Peak_area, Peak_height])
                break
    match_info = pd.DataFrame(display_info, columns=["RT", "Peak_area", "Peak_height"])
    match_infos = pd.concat([match_infos, match_info], axis=1)

# match_infos.to_csv(root + "\match_info.csv")

# 4. 画箱线图
# pd.set_option("display.max_rows", 1000)#可显示1000行
# pd.set_option("display.max_columns", 1000)#可显示1000列
# pd.set_option('display.float_format', lambda x:'%.3f'%x) # 小数点后面保留3位小数，诸如此类，按需修改吧
# # pd.reset_option("display.max_rows")#恢复默认设置
#
# match_infos = pd.read_csv(root + "\match_info.csv", header=None).values
# I = os.listdir(root+"\peaks_info")
#
# Time = pd.DataFrame([], columns=['C5H12 ', 'C8H18 ', 'C9H20 ', 'C10H22 ', 'C11H24 ', 'C12H26 '])
# Height = pd.DataFrame([], columns=['C5H12 ', 'C8H18 ', 'C9H20 ', 'C10H22 ', 'C11H24 ', 'C12H26 '])
#
# odd_index = np.arange(1, match_infos.shape[1], 3)
# even_index = np.arange(0, match_infos.shape[1], 3)
#
# Time_a = match_infos[:, even_index].T
# Time_a = np.concatenate([Time_a[0:5, :], Time_a[9:, :]])
# I = I[0:5] + I[9:]
# Time_b = Time_a - np.mean(Time_a, axis=0)
# Time_aa = Time.append(pd.DataFrame(Time_a, columns=['C5H12 ', 'C8H18 ', 'C9H20 ', 'C10H22 ', 'C11H24 ', 'C12H26 '], index=I))
# print(Time_aa.describe())
# Time_aa.describe().to_csv(root + "\describe_info.csv")
# Time_bb = Time.append(pd.DataFrame(Time_b, columns=['C5H12 ', 'C8H18 ', 'C9H20 ', 'C10H22 ', 'C11H24 ', 'C12H26 '], index=I))
# plot_boxplot(Time_bb, "Time")

# 5.画色谱图

