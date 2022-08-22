# import cross validation module
from pypls import cross_validation, plotting
# import plotting functions
import pandas as pd
from data_util import load_samples, del_0
from myPreprocessing import normalizeArea
from sklearn import model_selection
import numpy as np

# 读取数据集
MODEL_TAG = 'ZS1E_LUNG-S'
test_size = 0.2
Height, Area, Y, target_names, extra_info = load_samples(MODEL_TAG)
X = Area
X, _ = del_0(X, 0.2)
# X = normalizeArea(X)
x_train, x_test, y_train, y_test = model_selection.train_test_split(X, Y, test_size=test_size, random_state=0)

# 1. Initialize cross validation object for 10 fold cross validation using OPLS-DA.
# Parameters:
#     `kfold`: Fold in cross validation. For leave-one-out cross validation,
#     set it to `n`, is the number of samples.
#     `estimator`: The classifier, valid values are `opls` and `pls`, default is `opls`.
#     `scaler`: scaling of variable matrix.
#      * `uv`: zero mean and unit variance scaling.
#      * `pareto`: Pareto scaling. *This is the default.*
#      * `minmax`: min-max scaling so that the range for each variable is
#      between 0 and 1.
#      * `mean`: zero mean scaling.
cv = cross_validation.CrossValidation(kfold=10, estimator="opls", scaler='mean')

# 2. Fit the model.
#    `X` is the variable matrix with size `n` (rows) by `p` (columns), where
#    `n` is number of samples and `p` is number of variables.
#    `labels` can be numeric values or strings, with number of
#    elements equals to `n`.
cv.fit(x_train, y_train)

# 3. Visualization of results.
# For all these plots, set `save_plot=True` and `file_name=some_string.png`
# can save each plot to `some_string.png` with `dpi=1200`.

# construct the plotting object
plots = plotting.Plots(cv)

# Number of mis-classifications at different components.
plots.plot_cv_errors()

# Cross validated score plot.
# for OPLS-DA, predictive scores `tp` vs the first orthogonal
#     scores `to` will be shown; for PLS, the first and second component will
#     be shown.
plots.plot_scores()

# S-plot (only suitable for OPLS-DA).
plots.splot()

# Loading profile with Jack-knife confidence intervals (only suitable for OPLS-DA).
# Where `alpha` is significance level, default is `0.05`.
#     `means` are mean loadings, and `intervals` are
#     Jack-knife confidence intervals.
means, intervals = plots.jackknife_loading_plot(alpha=0.05)
print("means: ", means, ", intervals: ", intervals)
# 4. Model assessment.
"""
    # R2X
    cv.R2X
    # Q2
    cv.q2
    # R2y
    cv.R2y
    # Number of mis-classifications
    cv.min_nmc
"""
print("cv.R2X: ", cv.R2X, ", cv.q2: ", cv.q2)
print("cv.R2y: ", cv.R2y, ", cv.min_nmc: ", cv.min_nmc)

# 5. Access other metrics
"""
    * Cross validated predictive scores: `cv.scores`
    * Cross validated predictive loadings: `cv.loadings_cv`
    * Optimal number of components determined by cross
    validation: `cv.optimal_component_num`
"""
print("cv.scores: ", cv.scores, ", cv.optimal_component_num: ", cv.optimal_component_num)
# 6. Prediction of new data
"""
    predicted_scores = cv.predict(X)
    
    To predict the class, use:
    predicted_groups = (predicted_scores >= 0).astype(int)
    This will output values of `0` and `1` to indicate the
    groups of samples submitted for prediction. `cv` object
    has the attribute `groups` storing the group names which
    were assigned in `labels` input in training. 
    
    To access thegroup names after prediction, use
    print([cv.groups[g] for g in predicted_groups])
"""
predicted_scores = cv.predict(x_test)
predicted_groups = (predicted_scores >= 0).astype(int)
print(np.sum(predicted_groups == y_test)/len(y_test))
