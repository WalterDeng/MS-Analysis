from data_util import load_colon
from sklearn import datasets, linear_model
from sklearn import model_selection
from sklearn import discriminant_analysis
from myPreprocessing import normalizeArea
from sklearn.pipeline import Pipeline
from sklearn.decomposition import PCA
import numpy as np
import matplotlib.pyplot as plt
from plot_lda_qda import plot_one_dimension_data

def test_cross_val_socre():
    Height, Area, Y, target_names = load_colon()
    X = normalizeArea(Area)
    estimators = [('reduce_dim', PCA()),
                  ('clf', discriminant_analysis.LinearDiscriminantAnalysis())]
    pipe = Pipeline(estimators)
    scores = model_selection.cross_validate(pipe, X, Y, cv=4, scoring=('roc_auc', 'accuracy', 'neg_brier_score'))
    first_score = np.mean(scores.get('test_roc_auc'))
    second_score = np.mean(scores.get('test_accuracy'))
    third_score = np.mean(scores.get('test_neg_brier_score'))
    print(scores)
    print(first_score)
    print(second_score)
    print(third_score)

# test_cross_val_socre()

def test_draw_one_dimension_data():
    Height, Area, Y, target_names = load_colon2()
    X = normalizeArea(Area)
    lda = discriminant_analysis.LinearDiscriminantAnalysis(n_components=1)
    lda.fit(X, Y)
    X_r = lda.transform(X)

    lda2 = discriminant_analysis.LinearDiscriminantAnalysis()
    lda2.fit(X_r, Y)
    y_pred = lda2.predict(X_r)
    plot_one_dimension_data(lda2, X_r, Y, y_pred, target_names, "LDA Score for All Patient Tests", is_plot_false=True)
# test_draw_one_dimension_data()

def draw_pictures():
    # 1、PCA-LDA和LDA-LDA的差异
    test_size = [0.2, 0.3, 0.4, 0.5, 0.6, 0.7]
    lda_area = [0.9, 0.75, 0.8, 0.75, 0.75, 0.65]
    lda_height = [0.9, 0.9, 0.85, 0.7, 0.75, 0.30]
    pca_area = [0.4, 0.6, 0.8, 0.7, 0.7, 0.6]
    pca_height = [0.6, 0.55, 0.5, 0.7, 0.65, 0.45]

    plt.scatter(test_size, lda_area, color="navy", label='lda_area')
    plt.plot(test_size, lda_area, color="navy", lw=1)
    plt.scatter(test_size, lda_height, marker="^", color="navy", label='lda_height')
    plt.plot(test_size, lda_height, color="navy", lw=1)
    plt.scatter(test_size, pca_area, color="darkorange", label='pca_area')
    plt.plot(test_size, pca_area, '--', color="darkorange", lw=1)
    plt.scatter(test_size, pca_height, marker="^", color="darkorange", label='pca_height')
    plt.plot(test_size, pca_height, '--', color="darkorange", lw=1)

    plt.legend()
    plt.title("PCA-LDA vs LDA-LDA")
    plt.ylabel("CV=4 Test Score")
    plt.xlabel("Test Size")
    plt.show()

    # 2、source和normalize的差异


draw_pictures()

