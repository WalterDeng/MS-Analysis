function [data_baselined, base] = data_baseline(data)
% 对传入的二维数据data执行平滑、基线校准，并输出为data_baselined, base为确定的基线
%   此处显示详细说明
% smooth_window, noise_window最好为偶数
% peak_threshold = 8000，smooth_window=4，noise_window=6
% 输入 data ：(1, feature_num)
% 输出 data_baselined ：(feature_num)
% 输出 base : (feature_num)

    % --------------------- 要自动化处理的参数 -------------------------------------
    peak_threshold = 8000;
    smooth_window = 4;
    noise_window = 6;
    % --------------------- 要自动化处理的参数 -------------------------------------

    %Smoothing (moving average)
    [n1, m1] = size(data);
    a1      = 1:m1;
    Sx      = zeros(m1,n1);
    iv      = round(smooth_window/2);
    
    vv = m1-iv+1;
    %assignin('base','vv',vv);
    %assignin('base','m1',m1);
   % assignin('base','iv',iv);
    for i = smooth_window:vv
        Sx(i-iv+1, :) = mean(data(:, a1(i-smooth_window+1):a1(i)));
    end
    
    data_baselined_ = zeros(n1,m1);
    Base_          = zeros(n1,m1);
    for I = 1:n1 %from sample 1 to n1
        sx   = Sx(:,I);
        x    = data(I, :);
        l    = length(x);
        j    = l-noise_window;
        Mstd = zeros(1,m1);
    
        for i=1:j
            Mstd(1,i)=std(sx(i:i+noise_window-1));
        end

        %Noiese is separated from peaks by making a matrix only containing noise:
        noise = x(1, 1:m1);
        for i=6:m1
            if Mstd(1,i)<peak_threshold && Mstd(1,i-5)<peak_threshold && x(i)<500000000
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
            if N(i-1) == 0 && N(i) == 1 && c <= i
                start = i;
                stop  = find(N(i:end)-1, 1)+i-2;
                stop = stop(1);
                c     = stop + 1;
    
                slope                   = (x(stop+1)-x(start-1)) / (stop - start+1);
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
end

function [x_baselined, base, S] = Baseline(x_baselined, start, stop, x, I, base)
    % 执行数据中单个段落的对齐，该段落由start和stop来界定，
    % x_baselined为处理后的数据，x为原始数据，base为基线
    
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
    
    % Ii2是一个索引，显示非零的位置
    Ii2 = find(Ii);
    Ii2 = [0 Ii2];
    % 如果范围内只有一个非零
    if length(Ii2) == 1 && isempty(Ii2)==0
        [Xmin, S]        = min(x_baselined(start:stop));
        S                = S + start -1;
        slope1           = (x(S)-x(start-1)) /(S - start + 1);
        slope2           = (x(stop+1)-x(S)) /(stop -S + 1);
        base(start:(S-1))= x(start-1) + (1:(S-start))*slope1;
        base((S+1):stop) = x(S) + (1:(stop-S))*slope2;
        base(S)          = x(S);
    elseif max(Ii2(2:end)-Ii2(1:end-1)) > ceil(V1/2)
        [Xmin, S]        = min(x_baselined(start:stop));
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
