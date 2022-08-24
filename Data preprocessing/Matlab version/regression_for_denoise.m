% ��ֵ���亯�����Ż���ȥ�뷽�����ع鷽����
% CopyRight @ TSENG ChihYuan
%
clear,clc,close all
%% �����ֵ���亯��
% x = 0 : 0.01 : 2;
% %y = 1 ./ ( 1 + ( (x-1).^6) ); % ������˹��ͨ�˲���������ֵ���䣩
% y = 1 ./ ( 1 + ( (x-1).^6 + 0.02 * x ) );

colon_test = readmatrix("F:\test-data\colon_test.csv");
x = colon_test(1:1000, 1)';
y = colon_test(1:1000, 2)';

% ��ֵ���
pos = find( y == max(y) );%Ѱ�����ֵ
disp([ 'ԭʼ���� : ','���Ž�=' , num2str( x(pos) ) ,'�� ���ź���ֵ=' , num2str( y(pos) ) ])
%% ���루��˹��������
% sigma = 0.01; %��������
% noise = normrnd(0,sigma,1,length(x));
% yn = y + noise ;
yn = y;
% ��ֵ���
pos2 = find( yn == max(yn) );%Ѱ�����ֵ
disp([ '�������� : ','���Ž�=' , num2str( x(pos2) ) ,'�� ���ź���ֵ=' , num2str( y(pos2) ) ])
%% %%%%%%%%%%%%%%%%%%%%%%%%% ��ֵ���亯�����Ż���ȥ��˼·��%%%%%%%%%%%%%%%%%%%%%%%%
disp(['------- ȥ�뷽�� -------'])
%% ��ͨ�˲�ȥ��
f2 = fft(yn);
f2(7:193) = 0; %����ѡȡ����Ƶ����Ϊ7������ķ��������ﱣ��һ�£�
y3 = ifft(f2);
% ��ֵ���
pos3 = find( y3 == max(y3) );%Ѱ�����ֵ
disp([ '��ͨ�˲�ȥ�� : ','���Ž�=' , num2str( x(pos3) ) ,'�� ���ź���ֵ=' , num2str( y(pos3) ) ])
%% С���ֽ�ȥ��
% https://ww2.mathworks.cn/help/wavelet/ref/wfilters.html
[c,l] = wavedec(yn,7,'coif5'); %MallatС���ֽ⣨�ֽ����Ϊ7�㣬С����Ϊcoif5��
ca11=appcoef(c,l,'coif5',7); %��ȡ��Ƶ�ź�
%��ȡ��Ƶϸ��
cd1=detcoef(c,l,1);
cd2=detcoef(c,l,2); 
cd3=detcoef(c,l,3);
cd4=detcoef(c,l,4);
cd5=detcoef(c,l,5);
cd6=detcoef(c,l,6);
cd7=detcoef(c,l,7);
% 1-3����0,4-7��������ֵ��������
sd1=zeros(1,length(cd1));
sd2=zeros(1,length(cd2)); 
sd3=zeros(1,length(cd3));
sd4=wthresh(cd4,'s',0.014);
sd5=wthresh(cd5,'s',0.014);
sd6=wthresh(cd6,'s',0.014);
sd7=wthresh(cd7,'s',0.014);
c2=[ca11,sd7,sd6,sd5,sd4,sd3,sd2,sd1];
y4=waverec(c2,l,'coif5'); %С���ع� 
% ��ֵ���
pos4 = find( y4 == max(y4) );%Ѱ�����ֵ
disp([ 'С���ֽ�ȥ�� : ','���Ž�=' , num2str( x(pos4) ) ,'�� ���ź���ֵ=' , num2str( y(pos4) ) ])
%% ����ֵ�ֽ�ȥ��
% N = length(yn);%�źų���
% A = CorMat(yn,floor(N/2));%���źŹ�����ؾ���
% [U,S,V] = svd(A); %SVD
% S( 5:floor(N/2),5:floor(N/2) ) = 0; %������Ԫ��ѡ5
% B = U * S * V';
% y5 = CorMat2(B);
% % ��ֵ���
% pos5 = find( y5 == max(y5) );%Ѱ�����ֵ
% disp([ '����ֵ�ֽ�ȥ�� : ','���Ž�=' , num2str( x(pos5) ) ,'�� ���ź���ֵ=' , num2str( y(pos5) ) ])


%% %%%%%%%%%%%%%%%%%%%%%%%%% ��ֵ���亯�����Ż����ع�˼·��%%%%%%%%%%%%%%%%%%%%%%%%
disp(['------- �ع鷽�� -------'])
%% ��С����
% y = X * c ���У�ynΪ n��1 ������XΪ n��7���� ��cΪ 7��1����
x = x'; yn = yn'; 
X = [ x.^6 , x.^5 , x.^4 , x.^3 , x.^2 , x.^1 , x.^0 ]; %�������6����ʽ����Ϊԭ������6�Σ�
c = pinv(X) * yn; %LS
yLS = X * c;
% ��ֵ���
pos13 = find( yLS == max(yLS) );%Ѱ�����ֵ
disp([ '��С���˻ع� : ','���Ž�=' , num2str( x(pos13) ) ,'�� ���ź���ֵ=' , num2str( y(pos13) ) ])
%% ��ع�
lamda = 0.001;
X = [ x.^6 , x.^5 , x.^4 , x.^3 , x.^2 , x.^1 , x.^0 ]; %�������6����ʽ����Ϊԭ������6�Σ�
E = eye(size(X'*X));
w = (X'*X + lamda * E) \ ( X'*yn ); %��ع�
yRidge = X * w;
% ��ֵ���
pos14 = find( yRidge == max(yRidge) );%Ѱ�����ֵ
disp([ '��ع� : ','���Ž�=' , num2str( x(pos14) ) ,'�� ���ź���ֵ=' , num2str( y(pos14) ) ])
%% ��˹���̻ع�
% fitrgp()��˵��ҳ�� - https://ww2.mathworks.cn/help/stats/fitrgp.html#butnn96-2
gprMdl = fitrgp(x,yn);
%gprMdl = fitrgp(x,yn,'Basis','pureQuadratic','FitMethod','exact','PredictMethod','exact');
yGauss = resubPredict(gprMdl);
% ��ֵ���
pos15 = find( yGauss == max(yGauss) );%Ѱ�����ֵ
disp([ '��˹���̻ع� : ','���Ž�=' , num2str( x(pos15) ) ,'�� ���ź���ֵ=' , num2str( y(pos15) ) ])

%% ��ͼ
h = stackedplot(x, [y', yn, abs(y3)',y4',yLS,yGauss, yRidge]);
h.DisplayLabels = {'ԭʼ��ֵ���亯��', 'ԭ��������  ', '��ͨ�˲�ȥ��  ', 'С���ֽ�ȥ��  ', '��С���˻ع�  ', '��˹���̻ع�  ', '��ع�  '};
% figure,plot(x,y,'.-'),title('ԭʼ��ֵ���亯��')
% figure,plot(x,yn,'.-'),title('ԭ��������')
% figure,plot(x,abs(y3),'.-'),title('��ͨ�˲�ȥ��')
% figure,plot(x,y4,'.-'),title('С���ֽ�ȥ��')
% % figure,plot(x,y5,'.-'),title('����ֵ�ֽ�ȥ��')
% figure,plot(x,yLS,'.-'),title('��С���˻ع�')
% figure,plot(x,yRidge,'.-'),title('��ع�')
% figure,plot(x,yGauss,'.-'),title('��˹���̻ع�')
