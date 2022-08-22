"""
python filterFile.py "D:\DATA\data_analysis\allTic"
"""



import sys
import os
import pandas as pd



# root = sys.argv[1]
# print("root: " ,root)
root = "D:\\DATA\\allTic"
diseaseTagPath = "D:\DATA\diseaseTag.xlsx"

def filterFile(root):
    """
    保留 root 目录下名称中含有 "-M-"、"-Z-"、"-TJ-" 的文件
    :param root:
    :return:
    """
    for filepath, dirnames, filenames in os.walk(root):
        for fileName in filenames:
            if ("-M-" in fileName or "-Z-" in fileName or "-TJ-" in fileName or "LCLN" in fileName):
                continue
            else:
                oldName = filepath + "\\" + fileName
                os.remove(oldName)

def filterFile2(root, tag):
    """
    保留 root 目录下符合 diseaseTag.xlsx 标记的 tag sheet 下的before(疾病序号) control(对照组)
    :param root:
    :return:
    """
    diseaseTag = pd.read_excel(diseaseTagPath, sheet_name=None)
    sheet = diseaseTag.get(tag)
    before = sheet["before"]
    control = sheet["control"]

    before_num = 0
    control_num = 0
    for filepath, dirnames, filenames in os.walk(root):

        for fileName in filenames:
            dotSplit = str.split(fileName, '.')
            lineSplit = str.split(dotSplit[0], '_')
            f = lineSplit[1]

            if True in before.str.contains(f, na=False).array:
                before_num = before_num + 1
            elif True in control.str.contains(f, na=False).array:
                control_num = control_num + 1
            else:
                oldName = filepath + "\\" + fileName
                os.remove(oldName)

    print("before_num: %i"%before_num)
    print("control_num: %i" % control_num)


def findLostFile(root, TAG):
    """
    找到 diseaseTag.xlsx 中缺失的文件
    :param root:
    :return:
    """
    num_before = 0
    num_control = 0

    diseaseTag = pd.read_excel(diseaseTagPath, sheet_name=None)
    lung = diseaseTag.get(TAG)
    print("before:")
    lung_before = lung["before"].fillna("")
    for name in lung_before:
        find = False
        for filepath, dirnames, filenames in os.walk(root):
            if find:
                break
            for fileName in filenames:
                if name in fileName:
                    find = True
                    break
        if not find:
            print(name)
        else:
            num_before = num_before + 1

    print("control:")
    lung_control = lung["control"].fillna("")
    for name in lung_control:
        if name == "":
            continue
        find = False
        for filepath, dirnames, filenames in os.walk(root):
            if find:
                break
            for fileName in filenames:
                if name in fileName:
                    find = True
                    break
        if not find:
            print(name)
        else:
            num_control = num_control + 1

    print("num_before:", num_before, "num_control:", num_control)

filterFile("D:\DATA\\allTic")
# filterFile2(root, 'lung')
# findLostFile(root, 'lung')