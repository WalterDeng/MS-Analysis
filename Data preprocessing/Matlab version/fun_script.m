

%% 峰检测判断
% raw = readmatrix("C:\data\注册检验 样机测试\100ppt_test2.csv")';
raw = readmatrix("C:\data\uGC-Alan.csv")';

% wind = gausswin(5);
% sraw = filter(wind,1,raw(2, :));)
% hold on;
% plot(raw(1, :), sraw', 'red')

[data_baselined, base, peaks_info] = data_preprocessing(raw);
hold on;
plot(raw(1, :), data_baselined, 'color', 'red')
hold on;
plot(raw(1, :), raw(2, :), 'color', 'red')
plot(raw(1, :), base, 'color', 'black')
% writematrix([raw(1, :) ;data_baselined]', "D:\DATA\uGC_data\data_baselined.csv")
for j = 1:length(peaks_info)
    hold on;
    scatter(peaks_info(j, 2), peaks_info(j, 4), 'red');
    scatter(raw(1, peaks_info(j, 1)), data_baselined(1, peaks_info(j, 1)), 'blue', '.');
    scatter(raw(1, peaks_info(j, 3)), data_baselined(1, peaks_info(j, 3)), 'blue', '.');
end
% writematrix(peaks_info, "D:\DATA\retest consistency\A006\1-own.csv")


%% 一致性判断
% 2.提取峰信息
namelist = dir('D:\DATA\retest consistency\A002-0614\f_*.csv');
len = length(namelist);
peaks = cell(len);
for i = 1:len
    raw = readmatrix(namelist(i).folder+"\" + namelist(i).name)';
    [data_baselined, base, peaks_info] = data_preprocessing(raw);
    p1 = sortrows(peaks_info,-4);
    p2 = sortrows(p1(1:10, :),2);
%     plot(raw(1, :), data_baselined)
%     for j = 1:length(peaks_info)
%         hold on;
%         scatter(peaks_info(j, 2), peaks_info(j, 4));
%     end
    write_name = namelist(i).folder+"\peaks_info\i" +string(i) + "_" + namelist(i).name;
    writematrix(p2, write_name);
    peaks{i} = p2;
end

