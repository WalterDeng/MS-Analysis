import matplotlib.pyplot as plt

from data_util import load_samples
from SCI_PLOT import *
import numpy as np
import pandas as pd

test = pd.read_csv("F:\\test-data\\test-02.csv")
test = test.loc[:, ['TimeStamp', 'PID/HDPID_ADC']]
plt.plot(test.loc[:, ['TimeStamp']], test.loc[:, ['PID/HDPID_ADC']], linewidth=0.5)
plt.show()

# spectrum = pd.read_csv("saved_picture\\data.csv", header=None)
# # plot_spectrum(np.array(spectrum))
# spectrum_baselined = pd.read_csv("saved_picture\\data_baselined.csv", header=None)
# baseline = pd.read_csv("saved_picture\\base.csv", header=None)
# # plot_baseline(np.array(spectrum), np.array(spectrum_baselined), np.array(baseline).transpose())
# peaks_info = pd.read_csv("saved_picture\\PeaksInfo.csv")
# peaks_info = peaks_info.loc[:, ["Rt", "Theight"]]
# spectrum_alignment = pd.read_csv("saved_picture\\data_aligned.csv", header=None)
# plot_peak_identify(np.array(spectrum_alignment), np.array(peaks_info))

# 观察产品机上的峰挑选是否有误
# PEAKS = pd.read_csv("F:\\test-data\\local-PEAKS.csv", header=None)
# PEAKS = PEAKS.transpose()
# PEAKS.iloc[:, 1] = PEAKS.iloc[:, 1] / 100
# PEAKS = PEAKS.loc[:, [1, 3]]
# BASED = pd.read_csv("F:\\test-data\\undef-BASED.csv", index_col=False)
# AJL = pd.read_csv("C:\\Users\DELL\OneDrive\工作\DATA\\M-000001.csv", index_col=False)
# plot_spectrum(np.array(AJL))
# plot_peak_identify(np.array(BASED), np.array(PEAKS))

# 画C5-12的箱线图
peak_top = pd.read_csv("F:\\test-data\\peak_top.csv")
# print(peak_top)
print(peak_top.describe())
peak_top = peak_top.loc[17:, :]
plot_boxplot(peak_top, title="")

# plot_chanpinji_3_times(np.array(peak_top))



data_tag = 'ZS1E_LUNG-S'
data_root = "DATA\\"
Height, Area, Y, target_names, extra_info = load_samples(data_root, data_tag)
# raw_data = extra_info["raw_data"]
X = Area[:, [43, 65, 144, 149, 215]]
positive = X[Y==1, :]
positive = positive[:5, :]
negative = X[Y==0, :]
negative = negative[:10, :]
X = np.concatenate([positive, negative]).transpose()
# plot_cluster_map(X)