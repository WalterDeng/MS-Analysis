set "VSCMD_START_DIR=%CD%"

call "%VS15ROOTDIR%\VC\Auxiliary\Build\vcvarsall.bat" amd64_x86

cd .

if "%1"=="" (nmake  -f data_preprocessing_rtw.mk all) else (nmake  -f data_preprocessing_rtw.mk %1)
@if errorlevel 1 goto error_exit

exit 0

:error_exit
echo The make command returned an error of %errorlevel%
exit 1
