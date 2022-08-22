from components import cal_status

# 四种方法所得ICC值满足以下关系:ICC3 > ICC1 > ICC4 > ICC2，
# ICC4和 ICC2明显偏小，ICC3平均水平大于r，ICC1平均水平小于r，且ICC3和ICC1高度相关（r接近1)
# 应用中，不宜采用ICC4和ICC2，采用ICC3和ICC1均可，但前者恒大于后者，应注意可比性的问题。
# feats 大小：[受试者人数， 检测组数]

def icc1(feats):
    inter_ms, intra_ms, error_ms = cal_status(feats=feats)
    numerator = (intra_ms - error_ms) / len(feats)
    denominator = (intra_ms - error_ms) / len(feats) + error_ms
    icc1 = numerator / denominator
    return icc1


def icc2(feats):
    inter_ms, intra_ms, error_ms = cal_status(feats=feats)
    numerator = (intra_ms - error_ms) / len(feats)
    denominator = (intra_ms - error_ms) / len(feats) + error_ms + (inter_ms - error_ms) / len(feats[0])
    icc2 = numerator / denominator
    return icc2


def icc3(feats):
    inter_ms, intra_ms, error_ms = cal_status(feats=feats)
    numerator = intra_ms - (len(feats[0]) / (len(feats[0]) - 1)) * error_ms
    denominator = intra_ms + (len(feats) - 1) * (len(feats[0]) / (len(feats[0]) - 1)) * error_ms
    icc3 = numerator / denominator
    return icc3


def icc4(feats):
    inter_ms, intra_ms, error_ms = cal_status(feats=feats)
    numerator = intra_ms - error_ms
    denominator = intra_ms + (len(feats) - 1) * error_ms + (len(feats) / len(feats[0])) * (inter_ms - error_ms)
    icc4 = numerator / denominator
    return icc4