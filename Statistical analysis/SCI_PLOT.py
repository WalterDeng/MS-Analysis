import numpy as np
import matplotlib.pyplot as plt

plt.style.use('science')


def plot_two_dimension_data(X, y, target_names, title):
    """
    传入训练好的数据、模型和预测值，画出二维分布图
    :param X: n_sample * n_feature
    :param y: n_sample * 1
    """
    # fig, ax = plt.plot(figsize=(4, 3), dpi=200)
    fig = plt.figure(figsize=(4, 3), dpi=200)

    # class 1: dots
    plt.scatter(X[y == 1, 0], X[y == 1, 1], marker=".", color="red", label=target_names[1])

    # class 0: dots
    plt.scatter(X[y == 0, 0], X[y == 0, 1], marker="+", color="blue", label=target_names[0])

    # class 2: dots
    # plt.scatter(X[y == 2, 0], X[y == 2, 1], marker="*", color="yellow", label="test person")

    # ax.set_ylim(bottom=10, top=45)

    plt.legend(frameon=True, loc="best")
    plt.title(title)
    plt.xlabel("PC1")
    plt.ylabel("PC2")
    plt.autoscale(tight=True)

    plt.show()
    return


def plot_spectrum(spectrum):
    """
    绘制图谱示例
    :param spectrum: n_feature * 2
    """
    fig = plt.figure(figsize=(6,3), dpi=300)
    plt.plot(spectrum[:, 0], spectrum[:, 1], linewidth=0.5, color='black')
    plt.xlabel("Time(s)")
    plt.ylabel("Value(mv)")
    plt.autoscale(tight=True)
    plt.show()
    # plt.savefig("saved_picture/" + "spectrum_1.jpg")


def plot_baseline(spectrum, spectrum_baselined, baseline):
    """
    绘制基线校正示例
    :param spectrum: n_feature * 2
    :param spectrum_baselined: n_feature * 2
    :param baseline: n_feature * 1
    :return:
    """
    fig = plt.figure(figsize=(6,3), dpi=300)
    plt.plot(spectrum[:, 0], spectrum[:, 1], linewidth=0.5, color='black', label="Raw spectrum")
    plt.plot(spectrum_baselined[:, 0], spectrum_baselined[:, 1], linewidth=0.5, color='red', label="Spectrum baselined")
    plt.plot(spectrum_baselined[:, 0], baseline, linewidth=0.5, color='blue', label="Baseline")
    plt.xlabel("Time(s)")
    plt.ylabel("Value(mv)")
    plt.autoscale(tight=True)
    plt.legend(frameon=True, loc="best")
    plt.show()


def plot_peak_identify(spectrum_alignment, peaks_info):
    """
    绘制峰挑选示例
    :param spectrum_alignment: n_feature * 2
    :param peaks_info: n_peak * 2
    :return:
    """
    fig = plt.figure(figsize=(6,3), dpi=300)
    plt.plot(spectrum_alignment[:, 0], spectrum_alignment[:, 1], linewidth=0.5, color='black', label="Raw spectrum")
    plt.scatter(peaks_info[:, 0], peaks_info[:, 1], marker="^", color="red", s=10, label="Peak")
    plt.xlabel("Time(s)")
    plt.ylabel("Value(mv)")
    plt.autoscale(tight=True)
    plt.legend(frameon=True, loc="best")
    plt.show()


def plot_cluster_map(X):
    """
    绘制样本聚类热图，前5疾病组，后10为健康组
    :param X:
    """
    import seaborn as sns

    fig = plt.figure(figsize=(4, 3), dpi=200)

    sns.clustermap(X)

    plt.show()

def plot_boxplot(X, title):
    """
    绘制箱线图
    :param X:
    :return:
    """
    fig = plt.figure(figsize=(4, 3), dpi=200)
    plt.boxplot(x=X.values, labels=X.columns, whis=1.5)  # columns列索引，values所有数值
    plt.title(title)
    plt.show()

def plot_chanpinji_3_times(X):
    """
    绘制图谱示例
    :param spectrum: n_feature * 2
    """
    fig = plt.figure(figsize=(6,3), dpi=300)


    x = np.arange(0, X.shape[1])

    plt.plot(x, X[0, :], label='First', marker="o")  # marker设置标记形状 markersize设置标记大小
    plt.plot(x, X[1, :], label='Second', marker="x")
    plt.plot(x, X[2, :], label='Third', marker=".")

    plt.xlabel("All standard gas")
    plt.ylabel("Peak top times(s)")
    plt.xticks(x, ["C5H12", "C8H18", "C9H20", "C10H22", "C11H24", "C12H26"])
    plt.autoscale(tight=True)
    plt.legend(frameon=True, loc="best")
    plt.show()