
%%% 将MATLAB代码转换成32位C/C++的.dll文件

%% 首先，得到自己MSVC的版本号，比如VS2015就是14.0。下面代码可以自动检测
installed_compilers = mex.getCompilerConfigurations('C', 'Installed');
MSVC_InstalledVersions = regexp({installed_compilers.Name}, 'Microsoft Visual C\+\+ 20\d\d');
MSVC_InstalledVersions = cellfun(@(a)~isempty(a), MSVC_InstalledVersions);
VersionNumbers = {installed_compilers(MSVC_InstalledVersions).Version}'; % 15.0


%% 注册工具链
% 定义
tc = my_msvc_32bit_tc(VersionNumbers{end});
save my_msvc_37bit_tc tc;
% 注册
copyfile myRtwTargetInfo.txt rtwTargetInfo.m
RTW.TargetRegistry.getInstance('reset');

%% 生成Dll
% 创建配置
cfg = coder.config('dll');
cfg.HardwareImplementation.ProdHWDeviceType = 'Generic->Unspecified (assume 32-bit Generic)';
cfg.Toolchain = 'Microsoft 32 Bit Toolchain | nmake makefile (64-bit Windows)'; % 使用新注册的32位工具链
cfg.Verbose = true; % 显示编译信息，便于检查是否32位编译
% 编译
codegen -config cfg data_preprocessing -args {coder.typeof(0, [2, Inf])};
    
%% 生成测试Exe看dll是否能准确运行
% 配置
cfge = coder.config('exe');
cfge.CustomInclude = pwd;
cfge.CustomSource = 'yourFunction_main.c';
cfge.Toolchain = 'Microsoft 32 Bit Toolchain | nmake makefile (64-bit Windows)';
% 编译
codegen -config cfge data_preprocessing -args {coder.typeof(2, [2, Inf])};

% 等5s后exe应该生成成功，执行测试效果
pause(5);
system('yourFunction');