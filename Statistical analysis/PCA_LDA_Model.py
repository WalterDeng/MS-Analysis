from sklearn import model_selection
import pandas as pd
from data_util import normalizeA




class PCA_LDA_model:

    def __init__(self):
        """
        TODO:
            1. add arg for specifying the method for performing Model

        """
        self.X = None
        self.Y = None
        self.x_train = None
        self.x_test = None
        self.y_train = None
        self.y_test = None
        self.target_names = None
        self.max_feature = None
        self.reduction = None
        self.classification = None

        self.CSV_NAME = None
        self.biomarkers = None
        self.MODEL_TAG = None
        self.biomarkers_num = None
        self.n_component = None

    def fit(self, X, Y, target_names, MODEL_TAG, test_size=0.3, random_state=0):

        # X = normalizeArea(X)

        self.X = X
        self.Y = Y

        x_train, x_test, y_train, y_test = model_selection.train_test_split(X, Y, test_size=test_size, random_state=random_state)
        self.x_train = x_train
        self.x_test = x_test
        self.y_train = y_train
        self.y_test = y_test
        self.target_names = target_names
        self.MODEL_TAG = MODEL_TAG
        self.CSV_NAME = MODEL_TAG + "_biomarkers_of_VIP.csv"
        self.n_component = 2

        y_train_labels = pd.get_dummies(y_train)
        model = PLSRegression(n_components=self.n_component)
        model.fit(x_train, y_train_labels)
        self.model = model

    # 根据各大分类模型的得分进行子集选择
    def peak_subset_selection_by_score(self, is_plot=True, is_write=True, is_print=True, data_path=""):
        X = self.x_train
        y = self.y_train
        max_feature = self.max_feature
        reduction = self.reduction
        classification = self.classification

        n_samples, n_features = X.shape
        ## 初始化一维特征数据
        cur_aucs = dict()  # {features1 : [auc1, distanct1], features2 : [auc2, distanct2], ...}, features: (1, 2, ...)
        history_features = dict()  # 记录各个数量最好值的特征
        history_aucs = list()  # 记录各个数量特征的最好值
        for f1 in range(0, n_features):
            temp = (f1,)
            cur_aucs[temp] = [0, 0]

        best_features = ()
        best_score = [0, 0]

        ## 外层for循环，最多考虑几个特征
        for i in range(2, max_feature):
            new_aucs = dict()
            last_best_score = best_score
            ## 遍历当前特征列表
            for features in cur_aucs.keys():
                ## 内层for循环，加入 n_features 个新的特征并计算auc
                for num_f in range(0, n_features):
                    if num_f in features:
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
                        Xs = normalizeA(Xs)
                        if reduction == 'pls':
                            cur_score = compute_PLS_DA_score(Xs, y)
                        else:
                            # cur_score = compute_score(Xs, y, scoreing=scoreing)
                            cur_score = compute_PCA_LDA_score(Xs, y, reduction=reduction, classification=classification)
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
            sorted_list.sort(key=lambda a: a[1], reverse=True)
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
            plt.plot(np.arange(2, max_feature), history_aucs)
            plt.title("Boundary distance variation diagram")
            plt.show()

        return best_score, best_features, history_aucs, history_features


    # ---------------------------------- private function --------------------------------------------- #
    def compute_PCA_LDA_score(self, X, y, reduction='pca', classification='lda'):
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
        reductor, classificator, X_r = self.get_reductor_and_classificator(X, y, reduction=reduction,
                                                                      classification=classification)
        # if reductor =='none':
        #     Xrr = X
        # else:
        #     Xrr = reductor.transform(X)
        first_score, second_score = self.get_two_score(classificator, X_r, y, classification)

        score = [first_score, second_score]
        return score

    def get_two_score(self, classificator, X_r, y, classification):
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
        if classification in ['lda', 'svm']:  # 分类器有decision_function函数则计算边界距离
            # 计算20%临界点的平均距离
            boundary_distance = classificator.decision_function(X_r)
            index_20 = int(np.floor(boundary_distance.shape[0] * 0.2))
            abs_boundary_distance = np.abs(boundary_distance)
            idx = np.argpartition(abs_boundary_distance, index_20)[:(index_20 + 1)]
            boundary_distance = boundary_distance[idx]
            y = np.array(y)[idx]
            boundary_distance[y == 0] = 0 - boundary_distance[y == 0]
            second_score = np.mean(boundary_distance)
        elif classification in ['knn']:  # 有predict_proba(X)则计算平均概率
            proba = classificator.predict_proba(X_r)
            mean_0 = np.mean(proba[y == 0, 0] - proba[y == 0, 1])
            mean_1 = np.mean(proba[y == 1, 1] - proba[y == 1, 0])
            second_score = (mean_0 + mean_1) / 2

        return first_score, second_score

    def get_reductor_and_classificator(self, X, y, reduction='pca', classification='lda'):
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
        # classificator = discriminant_analysis.LinearDiscriminantAnalysis(solver="svd", store_covariance=True)
        classificator = discriminant_analysis.LinearDiscriminantAnalysis(store_covariance=True)
        if classification == 'qda':
            classificator = discriminant_analysis.QuadraticDiscriminantAnalysis()
        elif classification == 'svm':
            classificator = svm.LinearSVC(random_state=0)
        elif classification == 'knn':
            classificator = neighbors.KNeighborsClassifier(n_neighbors=3, weights='distance')

        classificator.fit(X_r, y)

        return reductor, classificator, X_r