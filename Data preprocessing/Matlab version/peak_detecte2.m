function [tops, troughs] = peak_detecte2(data)
% peak_detecte 检测data数据的谱峰，并输出所有峰的顶点、凹点信息
% data 每一横代表一个样本数据，每一列代表所有样本在该变量的取值，尺寸为(sample_num,
% feature_num)，sample_num可以为1
    

    smooth_window = 2; % 数据平滑窗口

    [n, m]  = size(data);
    I       = isnan(data);
    data(I) = 0;
    a1      = 1:m;
    sx      = zeros(n,m);
    iv      = round(smooth_window/2);
    for i = smooth_window:m-iv+1
        sx(:,i-iv+1) = mean(data(:,a1(i-iv+1):a1(i)), 2);  % 对每行依次求出窗口内的均值
    end

    tops = [];
    troughs = [];
    
    for ii = 1:n %for each sample
        d      = diff(sx(ii,:),1,2);  % 对该行作差
        [~,m] = size(d);
    
%         S = []; 
%         M = [];
        S = zeros(1, m);
        M = zeros(1, m);
        S_i = 0;
        M_i = 0;
        % Determination of peak start (S), max (M) and end slut (S)
        for i2 = 3:m % from the first to the last scan
            if d(1,i2-1)<=0 && d(1,i2)>0 || d(1,i2-1)<0 && d(1,i2)>=0 % 求每一个凹点（start\end 都在凹点上）
                S_i = S_i + 1;
                S(S_i) = i2;
%                 S = [S i2];
            end
            if d(1,i2-2)>0 && d(1,i2-1)>=0 && d(1,i2)<=0 && d(1,i2+1)<0 % 求每一个凸点（apex 在凸点上），这个取法默认取后一个点,且有概率忽略共溶峰
            % 共溶峰的忽略是由于平滑窗口导致的
            % 上面的检测方法同时检测四个点，会忽略紧凑的共溶峰，故改为以下的检测方法
%             if d(1,i2-1)>0 && d(1,i2)<=0 || d(1,i2-1)>=0 && d(1,i2)<0
                M_i = M_i + 1;
                M(M_i) = i2;
%                 M = [M i2-1];
            end
        end
        S = S(1:S_i);
        M = M(1:M_i); 
        tops = [tops M];
        troughs = [troughs S];
    end
end