from data_util import *

DataTag = 'ZS1E_LUNG'
Height, Area, Y, target_names, extra_info = load_samples(DataTag)
X = Area

# model_name = "LUNG_2_PCA"
# biomarkers = [2, 8, 14, 17, 31, 32, 38, 74, 84, 90]
# pack_model(model_name, X, Y, biomarkers)

model_name = "LUNG_2_PLS"
biomarkers = [69,64,77,31,68,22]
pack_model(model_name, X, Y, biomarkers)


