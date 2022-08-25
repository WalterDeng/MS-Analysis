function myRtwTargetInfo(tr)
tr.registerTargetInfo(@createToolchainRegistryFor32BitMSVCToolchain);
end
function config = createToolchainRegistryFor32BitMSVCToolchain
config(1)                       = coder.make.ToolchainInfoRegistry;
config(1).Name                  = 'Microsoft 32 Bit Toolchain | nmake makefile (64-bit Windows)';
config(1).FileName              = fullfile(fileparts(mfilename('fullpath')), 'my_msvc_32bit_tc.mat');
config(1).TargetHWDeviceType    = {'Intel->x86-32 (Windows32)','AMD->x86-32 (Windows32)','Generic->Unspecified (assume 32-bit Generic)'};
config(1).Platform              =  {'win64'};
end