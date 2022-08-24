clear all;
clc;
close all;

%下面是输入参数的样例
data = [1, 2, 3, 2, 1, 1,1,1,3,5,4,1,1,1,];
scanF = 120;

%上面是输入参数的样例
%下面是函数的调用
peaks_info = peak_detecte(data, scanF);