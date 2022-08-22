import os
def get_Models():
    """
    获取所有模型标签（字符串）
    :return: [MODEL1, …]
    """
    Models = set()
    for Model_name in os.listdir("saved_model\\"):
        tags = Model_name.split("_")
        Models.add(tags[0])

    Models = list(Models)

    return Models

def test_add(a, b):
    return a+b