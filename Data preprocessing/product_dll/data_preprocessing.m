function [data_baselined, base, peaks_info] = data_preprocessing(atlas_data)
% 对传入的二维数据data执行平滑、基线校准，并输出为data_baselined, base为确定的基线
%   此处显示详细说明
% smooth_window, noise_window�?好为偶数
% peak_threshold = 8000，smooth_window=4，noise_window=6
% 输入 data �?(time_series; feature_num)
% 输出 data_baselined �?(feature_num)
% 输出 base : (feature_num)

    % --------------------- 要自动化处理的参�? -------------------------------------
    time_series = atlas_data(1, :);
    smooth_window = 6;
    noise_window = 8;
    noise_vote_rate = 0.5; 
    
    min_area = 0.000001;  % V*s
    
    peak_threshold = 0.00002;
    min_peak_height = 0.00002 * 2;
    frequency = 1 / abs(time_series(1) - time_series(2));
    peak_smooth_window = ceil(frequency * 1.2);
    min_half_width = 4 / frequency; % s
    % -------------------------------------------------------------------------------


    %Smoothing (moving average)
    

    
    data = atlas_data(2, :);
    [n1, m1] = size(data);
    a1      = 1:m1;
    Sx      = zeros(n1, m1);
    iv      = round(smooth_window/2);
    vv = m1-iv+1;
    for i = smooth_window:vv     
        Sx(:, i-iv+1) = mean(data(:, (i-smooth_window+1):i)); % �õ�ƽ�������ڵľ�ֵ
    end

%     % smooth the chromatogram
%     for i=1:n1
%         Sx(i, :) = smooth(data(i, :), 0.002,'loess')';
%     end
    
    data_baselined_ = zeros(n1,m1);
    Base_          = zeros(n1,m1);
    for I = 1:n1 %from sample 1 to n1
        x    = data(I, :);
        sx    = Sx(I, :);
        l    = length(x);
        j    = l-noise_window;
        Mstd = zeros(1,m1);
    
        for i=1:j
            Mstd(1,i)=std(sx(i:i+noise_window-1));  % �������������ڵ�ƽ����ֵ�����׼��
        end
        
        [c,l] = wavedec(sx, 2, 'db3');
        stdc = wnoisest(c,l);
        peak_threshold = stdc(2);
        
%         min_peak_height = stdc(2) * 3;

        Mask = Mstd > peak_threshold;
        %Noiese is separated from peaks by making a matrix only containing noise:
        noise = x(1, 1:m1);
        inw = noise_window / 2;    
        for i= inw : m1-inw
%             if Mstd(1,i)<peak_threshold && Mstd(1,i-5)<peak_threshold
            if (sum(Mask(i-inw+1: i+inw)) / noise_window) < noise_vote_rate
                noise(i) = x(i);
            else
                noise(i) = NaN;
            end
        end

        base_ = x;
        %The baseline is estimated as straight line from start to stop of intervals:
        x_baselined = zeros(1,m1);
        N = isnan(noise);
        c = 0;
        for i = 2:length(N)
            if N(i-1) == 0 && N(i) == 1 && c <= i % ������������Ľ����
                start = i;
                fi = find(N(i:end)-1);
                if isempty(fi)       % 2022.6.27 ����Ҳ�������Ĭ�ϵ���β���Ƿ�����
                    fi = length(N)-i;
                else
                    fi = fi(1);
                end
                stop  = fi+i-2;
%                 stop  = find(N(i:end)-1, 1)+i-2;
%                 stop = stop(1);
                c     = stop + 1;
    
                slope                   = (x(stop)-x(start)) / (stop - start+1);
                base_(start:stop)        = x(start) + (1:(stop-start+1))*slope;
                x_baselined(start:stop) = (x(start:stop)-base_(start:stop));
    
                [x_baselined, base_, S1]       = Baseline(x_baselined, start, stop, x, I, base_);
                if S1 ~= 0
                    [x_baselined, base_, S2]       = Baseline(x_baselined, start, S1, x, I, base_);
                    [x_baselined, base_, S3]       = Baseline(x_baselined, S1, stop, x, I, base_);
                    if S2 ~= 0 && S3 ~= 0
                        [x_baselined, base_, ~]        = Baseline(x_baselined, start, S2, x, I, base_);
                        [x_baselined, base_, ~]        = Baseline(x_baselined, S2, S1, x, I, base_);
                        [x_baselined, base_, ~]        = Baseline(x_baselined, S1, S3, x, I, base_);
                        [x_baselined, base_, ~]        = Baseline(x_baselined, S3, stop, x, I, base_);
                    elseif S2 ~= 0
                        [x_baselined, base_, ~]        = Baseline(x_baselined, start, S2, x, I, base_);
                        [x_baselined, base_, ~]        = Baseline(x_baselined, S2, S1, x, I, base_);
                    elseif S3 ~= 0
                        [x_baselined, base_, ~]        = Baseline(x_baselined, S1, S3, x, I, base_);
                        [x_baselined, base_, ~]        = Baseline(x_baselined, S3, stop, x, I, base_);
                    end
                end
    
            elseif c < i
                base_(i) = noise(i);
                x_baselined(i) = (x(i)-base_(i));
            end
    
        end

        %baseline and noise are removed from raw data
        Base_(I,:) = base_;
        for i = 1:m1
            if x_baselined(i)<0
                x_baselined(i) = 0;
            end
        end
    
        data_baselined_(I,:) = x_baselined;
    end
    data_baselined = data_baselined_(1, :);
    base = Base_(1, :);

    %% --------------------- 峰检�? -----------------------------------
    %peak_detecte �?测data数据的谱峰，并输出所有峰�? {start, apex, end, height, width, area}信息
    %   此处提供详细说明
    % data 为基线校准后的数�?(sample_num, feature_num)
    data = data_baselined;
    [n, m]  = size(data);
    I       = isnan(data);
    data(I) = 0;
    
    Sx      = zeros(n1, m1);
    iv      = round(peak_smooth_window/2);
    vv = m1-iv+1;
    for i = peak_smooth_window:vv     
        Sx(:, i-iv+1) = mean(data(:, (i-peak_smooth_window+1):i)); % �õ�ƽ�������ڵľ�ֵ
    end
    
    plot(time_series, Sx(1,:), 'black');

    peaks_info = zeros(m, 6);
    peaks_i = 0;
    for ii = 1:n %for each sample
        d      = diff(Sx(ii,:),1,2);  % 对该行作�?
        [~,m] = size(d);
    
%         S = []; 
%         M = [];
        S = zeros(1, m);
        M = zeros(1, m);
        S_i = 0;
        M_i = 0;
        % Determination of peak start (S), max (M) and end slut (S)
        for i2 = 3:m-1 % from the first to the last scan
            if d(1,i2-1)<=0 && d(1,i2)>0 || d(1,i2-1)<0 && d(1,i2)>=0 % 求每�?个凹点（start\end 都在凹点上）
                if ~is_noise_pit(d, i2, Sx(ii, i2), peak_threshold)  % �����������С��Χ�ڰ�
                    S_i = S_i + 1;
                    S(S_i) = i2;
                end
            end
%             if d(1,i2-2)>0 && d(1,i2-1)>=0 && d(1,i2)<=0 && d(1,i2+1)<0 % 求每�?个凸点（apex 在凸点上），这个取法默认取后�?个点,且有概率忽略共溶�?
            % 共溶峰的忽略是由于平滑窗口导致的
            % 上面的检测方法同时检测四个点，会忽略紧凑的共溶峰，故改为以下的检测方�?
%             if d(1,i2-1)>0 && d(1,i2)<=0 || d(1,i2-1)>=0 && d(1,i2)<0
            if d(1,i2-1)>0 && d(1,i2)<0
%                 if (d(1,i2-2) < 0 && d(1,i2-2)*10+d(1,i2-1) > 0) || (d(1,i2+1) > 0 && d(1,i2)+10*d(1,i2+1) < 0)
%                     continue
%                 end
                M_i = M_i + 1;
                M(M_i) = i2;
%                 M = [M i2-1];
            end
        end
        
        S = S(1:S_i);
        M = M(1:M_i);
        l = length(M);
%         S = delete_near_S(S, M);

        for i2 = 1:l % 遍历每一个凸�?
            [~,J] = min(abs(S-M(1,i2)));
            %start must be located before max
            x1 = 0;
            x2 = 0;
            x3 = 0;
            % 找到距离�?接近的凹点，并分配两边的凹点作为该凸点的start\end，边界不考虑
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
            
            if not_one(x1, x3, M, i2, data) == 0
                continue
            end
    
            %peakheight at start(y1), max(y2) and end(y3)
%                     y2 = (data(ii,x2) + data(ii,x2+1)) /2;  % 前面默认取最后一个点，此处取�?个均�?
            y2 = data(ii,x2);
            
            
            % 求半峰宽，找到左右两边Y值最接近半峰高的数据点，然后左右作差得出半峰�?
            w0_5 = compute_half_width(data(ii, :), time_series, x1, x2, x3);

            % Area
            area = compute_area(w0_5, y2);
%             area = trapz(data(ii,x1:x3)) / frequency;
            
            % 判断峰宽、峰高是否符合要�?
            if w0_5>min_half_width && area>min_area && y2>min_peak_height
%             if y2>min_peak_height
                A = mean(sx(ii,x1:x3));
                c = 0;
    
                for i4 = x1:x3 % The signal must only cross average twice
                    if sx(ii,i4)<A && sx(ii,i4+1)>A || sx(ii,i4)>A && sx(ii,i4+1)<A
                        c = c+1;
                    end
                end
    
                if c<=4 % 进出各两次，因此c要小于等�?4
%                   �?测到峰，记录
                    P = [time_series(x1), time_series(x2), time_series(x3), y2, w0_5, area]; % peaks consiste of start, apex, end, height, width, area
%                     P = [x1, time_series(x2), x3, y2, w0_5, area]; % delete
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

function [x_baselined, base, S] = Baseline(x_baselined, start, stop, x, ~, base)
    % 执行数据中单个段落的对齐，该段落由start和stop来界定，
    % x_baselined为处理后的数据，x为原始数据，base为基�?
    
    V1= 5;
    neg  = find(x_baselined(start:stop)<0);
    
    %if there are no more than half of V1 instances below zero, the for loop should terminate
    if length(neg) < ceil(V1/2)
        S = 0;
        return
    end
    neg  = [neg inf];
    % zeroes in Ii indicates that two consecetive valeus are below zero, 5 in a row indicates 6 places below zero in a row
    Ii = neg(1:end-1)-neg(2:end)+1;
    
    % Ii2是一个索引，显示非零的位�?
    Ii2 = find(Ii);
    Ii2 = [0 Ii2];
    % 如果范围内只有一个非�?
    if length(Ii2) == 1 && isempty(Ii2)==0
        [~, S]        = min(x_baselined(start:stop));
        S                = S + start -1;
        slope1           = (x(S)-x(start-1)) /(S - start + 1);
        slope2           = (x(stop+1)-x(S)) /(stop -S + 1);
        base(start:(S-1))= x(start-1) + (1:(S-start))*slope1;
        base((S+1):stop) = x(S) + (1:(stop-S))*slope2;
        base(S)          = x(S);
    elseif max(Ii2(2:end)-Ii2(1:end-1)) > ceil(V1/2)
        [~, S]        = min(x_baselined(start:stop));
        S                = S + start -1;
        slope1           = (x(S)-x(start-1)) /(S - start + 1);
        slope2           = (x(stop+1)-x(S)) /(stop -S + 1);
        base(start:(S-1))= x(start-1) + (1:(S-start))*slope1;
        base((S+1):stop) = x(S) + (1:(stop-S))*slope2;
        base(S)          = x(S);
    else
        S                = 0;
    end
    x_baselined(start:stop) = (x(start:stop)-base(start:stop));
end

function is_right_one = not_one(x1, x3, M, i2, sx)
    is_right_one = 1;
    peak_height = sx(M(i2));
    
    i = i2 + 1;
    while (i<=length(M)&& M(i)<x3 )
        if sx(M(i)) > peak_height
           is_right_one = 0;
        end
        i = i + 1;
    end
    
    i = i2 - 1;
    while (i>0 && M(i)>x1 )
        if sx(M(i)) > peak_height
           is_right_one = 0;
        end
        i = i - 1;
    end
end

function res = is_noise_pit(d, i, x, threshold)
    res = false;
    if x > threshold && d(i-2) > 0 && d(i+1) < 0
        res = true;
    end
end

function w = compute_half_width(data, time_series, x1, x2, x3)
    %% ���������x123Ϊ��ʼ�㡢���㡢�յ����ţ�heightΪ���
    start_h = data(x1);
    end_h = data(x3);
    half_height = data(x2) * 0.5;
    if (start_h < half_height && end_h > half_height)
        [~,I1] = min(abs(data(x1:x2)-half_height));%The closest point left of apex.
        w = 2 * (time_series(x2) - time_series(x1+I1-1));
    elseif (start_h > half_height && end_h < half_height)
        [~,I2] = min(abs(data(x2:x3)-half_height));%The closest point right of apex.
        w = 2 * (time_series(x2+I2-1) - time_series(x2));
    else
        [~,I1] = min(abs(data(x1:x2)-half_height));%The closest point left of apex.
        [~,I2] = min(abs(data(x2:x3)-half_height));%The closest point right of apex.
        w = time_series(x2+I2-1) - time_series(x1+I1-1);
    end
end

function area = compute_area(half_width, height)
    % �ԳƷ� A = 1.065 * h * W0.5
    % �ǶԳƷ� A = 0.5 * h * (W0.15 + W0.85)
    area = 1.065 * half_width * height;
end

function S = delete_near_S(S, M)
    for i=1:length(M)
       Si = abs(S - M(i));
       I = find(Si == 1);
       if ~ isempty(I)
           S(I) = [];
       end
    end
end