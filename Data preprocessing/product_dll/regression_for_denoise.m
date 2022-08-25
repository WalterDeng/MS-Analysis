% 峰值缓变函数最优化（去噪方法、回归方法）
% CopyRight @ TSENG ChihYuan
%
clear,clc,close all
%% 构造峰值缓变函数
% x = 0 : 0.01 : 2;
% %y = 1 ./ ( 1 + ( (x-1).^6) ); % 巴特沃斯低通滤波函数（峰值缓变）
% y = 1 ./ ( 1 + ( (x-1).^6 + 0.02 * x ) );

colon_test = readmatrix("F:\test-data\colon_test.csv");
x = colon_test(1:1000, 1)';
y = colon_test(1:1000, 2)';

% 最值求解
pos = find( y == max(y) );%寻找最大值
disp([ '原始曲线 : ','最优解=' , num2str( x(pos) ) ,'， 最优函数值=' , num2str( y(pos) ) ])
%% 加噪（高斯白噪声）
% sigma = 0.01; %噪声方差
% noise = normrnd(0,sigma,1,length(x));
% yn = y + noise ;
yn = y;
% 最值求解
pos2 = find( yn == max(yn) );%寻找最大值
disp([ '加噪曲线 : ','最优解=' , num2str( x(pos2) ) ,'， 最优函数值=' , num2str( y(pos2) ) ])
%% %%%%%%%%%%%%%%%%%%%%%%%%% 峰值缓变函数最优化（去噪思路）%%%%%%%%%%%%%%%%%%%%%%%%
disp(['------- 去噪方法 -------'])
%% 低通滤波去噪
f2 = fft(yn);
f2(7:193) = 0; %这里选取的主频个数为7（后面的方法和这里保持一致）
y3 = ifft(f2);
% 最值求解
pos3 = find( y3 == max(y3) );%寻找最大值
disp([ '低通滤波去噪 : ','最优解=' , num2str( x(pos3) ) ,'， 最优函数值=' , num2str( y(pos3) ) ])
%% 小波分解去噪
% https://ww2.mathworks.cn/help/wavelet/ref/wfilters.html
[c,l] = wavedec(yn,7,'coif5'); %Mallat小波分解（分解层数为7层，小波基为coif5）
ca11=appcoef(c,l,'coif5',7); %获取低频信号
%获取高频细节
cd1=detcoef(c,l,1);
cd2=detcoef(c,l,2); 
cd3=detcoef(c,l,3);
cd4=detcoef(c,l,4);
cd5=detcoef(c,l,5);
cd6=detcoef(c,l,6);
cd7=detcoef(c,l,7);
% 1-3层置0,4-7层用软阈值函数处理
sd1=zeros(1,length(cd1));
sd2=zeros(1,length(cd2)); 
sd3=zeros(1,length(cd3));
sd4=wthresh(cd4,'s',0.014);
sd5=wthresh(cd5,'s',0.014);
sd6=wthresh(cd6,'s',0.014);
sd7=wthresh(cd7,'s',0.014);
c2=[ca11,sd7,sd6,sd5,sd4,sd3,sd2,sd1];
y4=waverec(c2,l,'coif5'); %小波重构 
% 最值求解
pos4 = find( y4 == max(y4) );%寻找最大值
disp([ '小波分解去噪 : ','最优解=' , num2str( x(pos4) ) ,'， 最优函数值=' , num2str( y(pos4) ) ])
%% 奇异值分解去噪
% N = length(yn);%信号长度
% A = CorMat(yn,floor(N/2));%由信号构造相关矩阵
% [U,S,V] = svd(A); %SVD
% S( 5:floor(N/2),5:floor(N/2) ) = 0; %这里主元数选5
% B = U * S * V';
% y5 = CorMat2(B);
% % 最值求解
% pos5 = find( y5 == max(y5) );%寻找最大值
% disp([ '奇异值分解去噪 : ','最优解=' , num2str( x(pos5) ) ,'， 最优函数值=' , num2str( y(pos5) ) ])


%% %%%%%%%%%%%%%%%%%%%%%%%%% 峰值缓变函数最优化（回归思路）%%%%%%%%%%%%%%%%%%%%%%%%
disp(['------- 回归方法 -------'])
%% 最小二乘
% y = X * c 其中，yn为 n×1 向量，X为 n×7矩阵 ，c为 7×1向量
x = x'; yn = yn'; 
X = [ x.^6 , x.^5 , x.^4 , x.^3 , x.^2 , x.^1 , x.^0 ]; %这里采用6多项式（因为原函数是6次）
c = pinv(X) * yn; %LS
yLS = X * c;
% 最值求解
pos13 = find( yLS == max(yLS) );%寻找最大值
disp([ '最小二乘回归 : ','最优解=' , num2str( x(pos13) ) ,'， 最优函数值=' , num2str( y(pos13) ) ])
%% 岭回归
lamda = 0.001;
X = [ x.^6 , x.^5 , x.^4 , x.^3 , x.^2 , x.^1 , x.^0 ]; %这里采用6多项式（因为原函数是6次）
E = eye(size(X'*X));
w = (X'*X + lamda * E) \ ( X'*yn ); %岭回归
yRidge = X * w;
% 最值求解
pos14 = find( yRidge == max(yRidge) );%寻找最大值
disp([ '岭回归 : ','最优解=' , num2str( x(pos14) ) ,'， 最优函数值=' , num2str( y(pos14) ) ])
%% 高斯过程回归
% fitrgp()的说明页面 - https://ww2.mathworks.cn/help/stats/fitrgp.html#butnn96-2
gprMdl = fitrgp(x,yn);
%gprMdl = fitrgp(x,yn,'Basis','pureQuadratic','FitMethod','exact','PredictMethod','exact');
yGauss = resubPredict(gprMdl);
% 最值求解
pos15 = find( yGauss == max(yGauss) );%寻找最大值
disp([ '高斯过程回归 : ','最优解=' , num2str( x(pos15) ) ,'， 最优函数值=' , num2str( y(pos15) ) ])

%% 绘图
h = stackedplot(x, [y', yn, abs(y3)',y4',yLS,yGauss, yRidge]);
h.DisplayLabels = {'原始峰值缓变函数', '原函数加噪  ', '低通滤波去噪  ', '小波分解去噪  ', '最小二乘回归  ', '高斯过程回归  ', '岭回归  '};
% figure,plot(x,y,'.-'),title('原始峰值缓变函数')
% figure,plot(x,yn,'.-'),title('原函数加噪')
% figure,plot(x,abs(y3),'.-'),title('低通滤波去噪')
% figure,plot(x,y4,'.-'),title('小波分解去噪')
% % figure,plot(x,y5,'.-'),title('奇异值分解去噪')
% figure,plot(x,yLS,'.-'),title('最小二乘回归')
% figure,plot(x,yRidge,'.-'),title('岭回归')
% figure,plot(x,yGauss,'.-'),title('高斯过程回归')
