
%%% ��MATLAB����ת����32λC/C++��.dll�ļ�

%% ���ȣ��õ��Լ�MSVC�İ汾�ţ�����VS2015����14.0�������������Զ����
installed_compilers = mex.getCompilerConfigurations('C', 'Installed');
MSVC_InstalledVersions = regexp({installed_compilers.Name}, 'Microsoft Visual C\+\+ 20\d\d');
MSVC_InstalledVersions = cellfun(@(a)~isempty(a), MSVC_InstalledVersions);
VersionNumbers = {installed_compilers(MSVC_InstalledVersions).Version}'; % 15.0


%% ע�Ṥ����
% ����
tc = my_msvc_32bit_tc(VersionNumbers{end});
save my_msvc_37bit_tc tc;
% ע��
copyfile myRtwTargetInfo.txt rtwTargetInfo.m
RTW.TargetRegistry.getInstance('reset');

%% ����Dll
% ��������
cfg = coder.config('dll');
cfg.HardwareImplementation.ProdHWDeviceType = 'Generic->Unspecified (assume 32-bit Generic)';
cfg.Toolchain = 'Microsoft 32 Bit Toolchain | nmake makefile (64-bit Windows)'; % ʹ����ע���32λ������
cfg.Verbose = true; % ��ʾ������Ϣ�����ڼ���Ƿ�32λ����
% ����
codegen -config cfg data_preprocessing -args {coder.typeof(0, [2, Inf])};
    
%% ���ɲ���Exe��dll�Ƿ���׼ȷ����
% ����
cfge = coder.config('exe');
cfge.CustomInclude = pwd;
cfge.CustomSource = 'yourFunction_main.c';
cfge.Toolchain = 'Microsoft 32 Bit Toolchain | nmake makefile (64-bit Windows)';
% ����
codegen -config cfge data_preprocessing -args {coder.typeof(2, [2, Inf])};

% ��5s��exeӦ�����ɳɹ���ִ�в���Ч��
pause(5);
system('yourFunction');