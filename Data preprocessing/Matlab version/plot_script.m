% ALL_BASED = readmatrix("\\192.168.60.38\ChromX Share\ʵ���¼��Alan��\Data saved by    Excel\test-C5-12\ALL-BASED.csv");
% 
% h = stackedplot(peak_top(8:end, :));
% h.DisplayLabels = {'C5H12', 'C8H18  ', 'C9H20  ', 'C10H22  ', 'C11H24  ', 'C12H26  '};
% h.XLabel = {'���Դ���'};
% h.Title = {'�ظ���������4�α���ʱ��Ǩ������'};
% h.LineProperties(1).Marker = 's';
% h.LineProperties(1).LineStyle = '--';
% h.LineProperties(2).Marker = 's';
% h.LineProperties(2).LineStyle = '--';
% h.LineProperties(3).Marker = 's';
% h.LineProperties(3).LineStyle = '--';
% h.LineProperties(4).Marker = 's';
% h.LineProperties(4).LineStyle = '--';
% h.LineProperties(5).Marker = 's';
% h.LineProperties(5).LineStyle = '--';
% h.LineProperties(6).Marker = 's';
% h.LineProperties(6).LineStyle = '--';

% h.LineProperties(1).Color = 'b';
% h.LineProperties(2).Color = 'b';
% h.LineProperties(3).Color = 'g';
% h.LineProperties(4).Color = 'g';



peak_top = readmatrix("\\192.168.60.38\ChromX Share\ʵ���¼��Alan��\Data saved by    Excel\test-C5-12\peak_top.csv");
boxplot(peak_top, 'LABELS',['C5H12', "C8H18", "C9H20", "C10H22", "C11H24", "C12H26"])
xlabel('All standard gas')
ylabel('Average deviation(s)')
title('Retention time range of standard gas')

