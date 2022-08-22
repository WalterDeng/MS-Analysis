"""
================================
Nearest Neighbors Classification
================================

Sample usage of Nearest Neighbors classification.
It will plot the decision boundaries for each class.

"""

import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from matplotlib.colors import ListedColormap
from sklearn import neighbors, datasets
from data_util import load_healthy_lung
from sklearn.model_selection import train_test_split
from myPreprocessing import normalizeArea
from myEvaluation import BEST_FEATURES, myPCA


n_neighbors = 15

# import some data to play with
iris = datasets.load_iris()

# we only take the first two features. We could avoid this ugly
# slicing by using a two-dim dataset
X, Y, target_names, tags, X3, Y3 = load_healthy_lung()
X = normalizeArea(X)
# X = X[:, BEST_FEATURES.get("lung_healthy")]
X_r = myPCA(X, Y, target_names, n_components=5)
# X_r = X_r[:, [1,3]]
X, x_test, y, y_test = train_test_split(X_r, Y, test_size=0.2, random_state=7)

h = 0.02  # step size in the mesh

# Create color maps
cmap_light = ListedColormap(["orange", "cyan"])
cmap_bold = ["darkorange", "c"]

for weights in ["uniform", "distance"]:
    # we create an instance of Neighbours Classifier and fit the data.
    clf = neighbors.KNeighborsClassifier(n_neighbors, algorithm='brute', weights=weights)
    clf.fit(X, y)
    y_predict = clf.predict(x_test)
    print(np.mean(y_predict == y_test))

    # Plot the decision boundary. For that, we will assign a color to each
    # point in the mesh [x_min, x_max]x[y_min, y_max].
    # x_min, x_max = X[:, 0].min() - 1, X[:, 0].max() + 1
    # y_min, y_max = X[:, 1].min() - 1, X[:, 1].max() + 1
    # xx, yy = np.meshgrid(np.arange(x_min, x_max, h), np.arange(y_min, y_max, h))
    # Z = clf.predict(np.c_[xx.ravel(), yy.ravel()])
    #
    # # Put the result into a color plot
    # Z = Z.reshape(xx.shape)
    # plt.figure(figsize=(8, 6))
    # plt.contourf(xx, yy, Z, cmap=cmap_light)
    #
    # # Plot also the training points
    # sns.scatterplot(
    #     x=X[:, 0],
    #     y=X[:, 1],
    #     hue=iris.target_names[y],
    #     palette=cmap_bold,
    #     alpha=1.0,
    #     edgecolor="black",
    # )
    # plt.xlim(xx.min(), xx.max())
    # plt.ylim(yy.min(), yy.max())
    # plt.title(
    #     "3-Class classification (k = %i, weights = '%s')" % (n_neighbors, weights)
    # )
    # plt.xlabel(iris.feature_names[0])
    # plt.ylabel(iris.feature_names[1])

plt.show()
