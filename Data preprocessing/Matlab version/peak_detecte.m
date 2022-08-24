function peaks_info = peak_detecte(data)
% peak_detecte 检测data数据的谱峰，并输出所有峰的 {start, apex, end, height, width, area}信息
% start,end分别为峰的起始，结束点（也是凹点），apex为峰值顶点
% data 每一横代表一个样本数据，每一列代表所有样本在该变量的取值，尺寸为(sample_num,
% feature_num)，sample_num可以为1
    
    % --------------------- 要自动化处理的参数 -------------------------------------
    min_half_width = 0.01; % 最小半峰宽
    max_half_width = 10; % 最大半峰宽
    min_peak_height = 10000; % 最小峰高
    smooth_window = 4; % 数据平滑窗口
    % ----------------------------------------------------------

    [n, m]  = size(data);
    I       = isnan(data);
    data(I) = 0;
    a1      = 1:m;
    sx      = zeros(n,m);
    iv      = round(smooth_window/2);
    for i = smooth_window:m-iv+1
        sx(:,i-iv+1) = mean(data(:,a1(i-iv+1):a1(i)), 2);  % 对每行依次求出窗口内的均值
    end

    peaks_info = zeros(m, 6);
    peaks_i = 0;
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
        l = length(M);

        for i2 = 1:l % 遍历每一个凸点
            [~,J] = min(abs(S-M(1,i2)));
            %start must be located before max
            x1 = 0;
            x2 = 0;
            x3 = 0;
            % 找到距离最接近的凹点，并分配两边的凹点作为该凸点的start\end，边界不考虑
            if M(1,i2)>S(J)&& J<length(S)
                x1 = S(J);
                x2 = M(1,i2);
                x3 = S(J+1);
            elseif J>1 && M(1,i2)<S(J)
                x1 = S(J-1);
                x2 = M(1,i2);
                x3 = S(J);
            end
    
            if x1 == 0
                continue
            end
    
            %peakheight at start(y1), max(y2) and end(y3)
%                     y2 = (data(ii,x2) + data(ii,x2+1)) /2;  % 前面默认取最后一个点，此处取一个均值
            y2 = data(ii,x2);
            % Area
            area = trapz(data(ii,x1:x3));
            % 求半峰宽，找到左右两边Y值最接近半峰高的数据点，然后左右作差得出半峰宽
            [~,I1] = min(abs(data(ii,x1:x2)-(y2*0.5)));%The closest point left of apex.
            [~,I2] = min(abs(data(ii,x2:x3)-(y2*0.5)));%The closest point right of apex.
            
            w = time_series(x2+I2) - time_series(x1+I1);
            % 判断峰宽、峰高是否符合要求
            if w>min_half_width && w<max_half_width && y2>min_peak_height
                A = mean(sx(ii,x1:x3));
                c = 0;
    
                for i4 = x1:x3 % The signal must only cross average twice
                    if sx(ii,i4)<A && sx(ii,i4+1)>A || sx(ii,i4)>A && sx(ii,i4+1)<A
                        c = c+1;
                    end
                end
    
                if c<=4 % 进出各两次，因此c要小于等于4
%                   检测到峰，记录
                    P = [time_series(x1), time_series(x2), time_series(x3), y2, w, area]; % peaks consiste of start, apex, end, height, width, area
                    peaks_i = peaks_i + 1;
                    peaks_info(peaks_i, :) = P;
                end
            end  
        end
    
        %If no peaks are detected
        if peaks_i == 0
            peaks_info = zeros(1, 6);
        else
            peaks_info = peaks_info(1:peaks_i, :);
        end
    end
end