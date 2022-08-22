function [outputArg1,outputArg2] = peak_detecte(data, smooth_window, min_peak_height, min_half_width, max_half_width)
%peak_detecte 检测data数据的谱峰，并输出所有峰的 {start, apex, end, height, width, area}信息
%   此处提供详细说明
% data 为基线校准后的数据
% smooth

    min_half_width = app.V1.Value;
    max_half_width = app.V2.Value;
    min_peak_height = app.minPeakHeight.Value; 
%             a = app.startTime.Value; 
    
    smooth_window = app.smooth.Value;
    
    data    = app.dataAligned;
    if isempty(data)
        data = app.dataBaselined;
    end
    [n, m]  = size(data);
    I       = isnan(data);
    data(I) = 0;
    a1      = 1:m;
    sx      = zeros(n,m);
    iv      = round(smooth_window/2);
    for i = smooth_window:m-iv+1
        sx(:,i-iv+1) = mean(data(:,a1(i-smooth_window+1):a1(i)), 2);  % 对每行依次求出窗口内的均值
    end
    
    for ii = 1:n %for each sample
        d      = diff(sx(ii,:),1,2);  % 对该行作差
        [~,m] = size(d);
        Peaks  = [];
    
        S = []; M = [];
        % Determination of peak start (S), max (M) and end slut (S)
        for i2 = 3:m % from the first to the last scan
            if d(1,i2-1)<=0 && d(1,i2)>0 || d(1,i2-1)<0 && d(1,i2)>=0 % 求每一个凹点（start\end 都在凹点上）
                S = [S i2];
            end
            if d(1,i2-2)>0 && d(1,i2-1)>=0 && d(1,i2)<=0 && d(1,i2+1)<0 % 求每一个凸点（apex 在凸点上），这个取法默认取后一个点,且有概率忽略共溶峰
            % 共溶峰的忽略是由于平滑窗口导致的
            % 上面的检测方法同时检测四个点，会忽略紧凑的共溶峰，故改为以下的检测方法
%                     if d(1,i2-1)>0 && d(1,i2)<=0 || d(1,i2-1)>=0 && d(1,i2)<0
                M = [M i2-1];
            end
        end
        l = length(M);
        scanF_ = app.scanFrequency;
        %Test of if the identified start/end/max is fullfilling the
        %requirements
        
         % for test 
%                 hold(app.UIAxes, 'on')
%                 Mx = M / scanF_ + app.X(1,1);
%                 scatter(app.UIAxes, Mx', data(ii,M), ...
%                      'Marker', '^','markerEdgecolor','b', MarkerFaceColor='b');
%                 Sx = S / scanF_ + app.X(1,1);
%                 hold(app.UIAxes, 'on')
%                 scatter(app.UIAxes, Sx', data(ii,S), ...
%                     'markerEdgecolor','r', MarkerFaceColor='r');

        for i2 = 1:l % 遍历每一个凸点
            [~,J] = min(abs(S-M(1,i2)));
            %start must be located before max
            x2 = 0;
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
    
            if x2 == 0
                continue
            end
    
            %peakheight at start(y1), max(y2) and end(y3)
%                     y2 = (data(ii,x2) + data(ii,x2+1)) /2;  % 前面默认取最后一个点，此处取一个均值
            y2 = data(ii,x2);
            % Area
            area = trapz(data(ii,x1:x3));
            %peak width in half height
            % 求半峰宽，找到左右两边Y值最接近半峰高的数据点，然后左右作差得出半峰宽
            [~,I1] = min(abs(data(ii,x1:x2)-(y2*0.5)));%The closest point left of apex.
            [~,I2] = min(abs(data(ii,x2:x3)-(y2*0.5)));%The closest point right of apex.
            
            w = ((x2+I2)-(x1+I1)) / scanF_;
            P = [];
            
            % 判断峰宽、峰高是否符合要求
            if w>min_half_width && w<max_half_width && y2>min_peak_height
                p = [x1; x2; x3]; %start peak end
                % 此时P的值只是一个Index，需要对应到X的时间轴上，才能取得真值
                %p = ([x1; x2; x3]) / scanF_  + app.X(1, 1);%start peak end
                A = mean(sx(ii,x1:x3));
                c = 0;
    
                for i4 = x1:x3 % The signal must only cross average twice
                    if sx(ii,i4)<A && sx(ii,i4+1)>A || sx(ii,i4)>A && sx(ii,i4+1)<A
                        c = c+1;
                    end
                end
    
                if c<=4 % 进出各两次，因此c要小于等于4
%                             P = [p'+a y2 w];   %% P内是序号，+a之后有问题
                    P = [p' y2 w area];
                end
    
            end
            
            if isempty(P)==0
                Peaks = [Peaks; P];
            end
    
        end
    
        %If no peaks are detected
        if isempty(Peaks)==1
            Peaks(1,5) = 0;
        end
        TotalPeaks_{ii,1} = Peaks;% peaks consiste of start, apex, end, height, width, area
    end
    app.totalPeaks = TotalPeaks_;
    

    % plot
%             hold(app.UIAxes, 'on')
    peak1 = TotalPeaks_{1, 1};
%             apex_ = peak1(:, 2) / scanF_ + app.X(1,1);
%             scatter(app.UIAxes, apex_, peak1(:, 4), ...
%                 'filled' ,'Marker', '^','markerEdgecolor','r', MarkerFaceColor='r');
%             hold(app.UIAxes, 'on')
%             if size(TotalPeaks_, 1) > 1
%                 peak2 = TotalPeaks_{2, 1};
%                 apex_2 = peak2(:, 2) / scanF_ + app.X(1,1);
%                 scatter(app.UIAxes, apex_2, peak2(:, 4), ...
%                     'filled' ,'Marker', '^','markerEdgecolor','g', MarkerFaceColor='g');
%             end
%             hold(app.UIAxes, 'on')
%             plot(app.UIAxes, app.X, ones(app.msLen, 1) * app.minPeakHeight.Value)

    % plot
%             cla(app.UIAxes)
    for ii = 1:n %for each sample
        hold(app.UIAxes, 'on')
        peaki = TotalPeaks_{ii, 1};
        apex_ = peaki(:, 2) / scanF_ + app.X(1,1);
        scatter(app.UIAxes, apex_, peaki(:, 4), ...
            5, 'filled', 'b');
    end
  

    % update table
    Tstart = peak1(:, 1);
    Theight = peak1(:, 4);
    Tend = peak1(:, 3);
    Tapex = peak1(:, 2);
    indexs = 1:1:length(Tapex);
    peaksTable = table(indexs', Tapex, Theight, Tstart, Tend);
    app.UITable2.Data = peaksTable;
    app.TabGroup.SelectedTab = app.peakTab;
end