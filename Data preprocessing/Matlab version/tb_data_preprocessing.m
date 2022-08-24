clear all;
clc;
close all;

%下面是输入参数的样例
% atlas_data = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15; 1,2,3,1,2,3,4,5,6,2,1,4,6,7,1]+1;
% lung_test = readmatrix("C:\Users\DELL\source\repos\data_preprocessing_32\data_preprocessing_32\nanova test.csv");
lung_test = readmatrix("F:\test-data\nanova test.csv");
atlas_data = lung_test';
%上面是输入参数的样例
%下面是函数的调用
[data_baselined, base, peaks_info] = data_preprocessing(atlas_data);