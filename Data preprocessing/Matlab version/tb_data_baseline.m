clear all;
clc;
close all;

%下面是输入参数的样例
data = [1,2,3,4,5,6;4,5,6,7,8,9];
peak_threshold = 8000;
smooth_window = 4;
noise_window = 6;

%上面是输入参数的样例
%下面是函数的调用
[data_baselined, base] = data_baseline(data, peak_threshold, smooth_window, noise_window);