import os
import sys
import re
import chardet
from data_util import write_list

def get_files(root):
    files = list()
    for filepath,dirnames,filenames in os.walk(root):
        for filename in filenames:
            files.append(os.path.join(filepath,filename))
    return files

def changeName(root, origWord, targetWord):

    files = get_files(root)
    cur_path = os.getcwd()
    fLog = open(cur_path + "\\changeLog.txt", 'w')
    for file in files:
        try:
            encode = 'utf-8'
            with open(file, 'rb') as f:
                text = f.read()
                dicta = chardet.detect(text)
                encode1 = dicta.get('encoding')
                if encode1: encode = encode1
            f = open(file, 'r', encoding=encode)
            alllines = f.readlines()
            f.close()
            f = open(file, 'w+', encoding=encode)
            for eachline in alllines:
                if re.search(origWord, eachline):
                    a = re.sub(origWord, targetWord, eachline)
                    fLog.write("file_name: " + file)
                    fLog.write("eachline: " + eachline)
                    f.writelines(a)
                else:
                    f.writelines(eachline)
            f.close()
        except:
            fLog.write("file_name: " + file + " read fail!!! \n")
            # fLog.write("exec: " + str(exec) + "\n")
    fLog.close()

import os
import shutil



def mycopyfile(srcfile,dstpath):                       # 复制函数
    if not os.path.isfile(srcfile):
        print ("%s not exist!"%(srcfile))
    else:
        fpath,fname=os.path.split(srcfile)             # 分离文件名和路径
        if not os.path.exists(dstpath):
            os.makedirs(dstpath)                       # 创建路径
        shutil.copy(srcfile, dstpath + "\\" + fname)          # 复制文件
        print ("copy %s -> %s"%(srcfile, dstpath + "\\" + fname))

def pickTicFile(root, targetDir):
    for filepath, dirnames, filenames in os.walk(root):
        if "tic_front.csv" in filenames:
            newName = filepath+ "\\" + filepath.split('\\')[-1] + ".csv"
            oldName = filepath+ "\\" + "tic_front.csv"
            os.rename(oldName, newName)
            mycopyfile(newName, targetDir)

pickTicFile(r"D:\DATA\中山一医采样数据11-17~11-28", r"D:\DATA\Samples")

def get_files_name():
    files = list()
    # 期刊网
    qikan_path = r"C:\Users\DELL\OneDrive\工作\研青部\研究生学志\挑选30篇文章\期刊网\期刊网"
    write_qikan_path = r"C:\Users\DELL\OneDrive\工作\研青部\研究生学志\挑选30篇文章" + "\\file.txt"
    for filepath, dirnames, filenames in os.walk(qikan_path):
        for filename in filenames:
            file = filename[0:-4].split('-')

            files.append(file)
    # print(files)
    write_list(write_qikan_path, files)

    files2 = list()
    # 重要文章
    important_path = r"C:\Users\DELL\OneDrive\工作\研青部\研究生学志\挑选30篇文章\学志重要文章"
    write_important_path = r"C:\Users\DELL\OneDrive\工作\研青部\研究生学志\挑选30篇文章" + "\\file2.txt"
    for filepath, dirnames, filenames in os.walk(important_path):
        for dirname in dirnames:
            # print(dirname)
            path = os.path.join(filepath, dirname)
            for _, _, filenames2 in os.walk(path):
                for filename2 in filenames2:

                    files2.append([dirname, filename2[0:-4]])

        for filename in filenames:
            if "-" in filename:
                file = filename[0:-4].split('-')
                files2.append(file)
    # print(files)
    write_list(write_important_path, files2)
    return True

# changeName(r"D:\20211117-tube1-250sccm-4min.D", r"GCMS", r"DYX")
# get_files_name()
