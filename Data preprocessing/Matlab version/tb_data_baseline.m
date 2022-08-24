clear all;
clc;
close all;

%下面是输入参数的样例
data = [1, 2, 3,1,2,3,4,5,6,2,1,4,6,7,34,2,123,5,6,7,4,3,1] * 100000;

%上面是输入参数的样例
%下面是函数的调用
[data_baselined, base] = data_baseline(data);