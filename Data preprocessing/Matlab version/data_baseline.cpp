//
// MATLAB Compiler: 8.3 (R2021b)
// Date: Thu Feb 17 17:56:41 2022
// Arguments:
// "-B""macro_default""-W""cpplib:data_baseline""-T""link:lib""data_baseline.m""
// -C"
//

#define EXPORTING_data_baseline 1
#include "data_baseline.h"

static HMCRINSTANCE _mcr_inst = NULL; /* don't use nullptr; this may be either C or C++ */

#if defined( _MSC_VER) || defined(__LCC__) || defined(__MINGW64__)
#ifdef __LCC__
#undef EXTERN_C
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#define NOMINMAX
#include <windows.h>
#undef interface

static char path_to_dll[_MAX_PATH];

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, void *pv)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        if (GetModuleFileName(hInstance, path_to_dll, _MAX_PATH) == 0)
            return FALSE;
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
    }
    return TRUE;
}
#endif
#ifdef __cplusplus
extern "C" { // sbcheck:ok:extern_c
#endif

static int mclDefaultPrintHandler(const char *s)
{
    return mclWrite(1 /* stdout */, s, sizeof(char)*strlen(s));
}

#ifdef __cplusplus
} /* End extern C block */
#endif

#ifdef __cplusplus
extern "C" { // sbcheck:ok:extern_c
#endif

static int mclDefaultErrorHandler(const char *s)
{
    int written = 0;
    size_t len = 0;
    len = strlen(s);
    written = mclWrite(2 /* stderr */, s, sizeof(char)*len);
    if (len > 0 && s[ len-1 ] != '\n')
        written += mclWrite(2 /* stderr */, "\n", sizeof(char));
    return written;
}

#ifdef __cplusplus
} /* End extern C block */
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_data_baseline_C_API
#define LIB_data_baseline_C_API /* No special import/export declaration */
#endif

LIB_data_baseline_C_API 
bool MW_CALL_CONV data_baselineInitializeWithHandlers(
    mclOutputHandlerFcn error_handler,
    mclOutputHandlerFcn print_handler)
{
    int bResult = 0;
    if (_mcr_inst)
        return true;
    if (!mclmcrInitialize())
        return false;
    if (!GetModuleFileName(GetModuleHandle("data_baseline"), path_to_dll, _MAX_PATH))
        return false;
    bResult = mclInitializeComponentInstanceNonEmbeddedStandalone(&_mcr_inst,
        path_to_dll,
        "data_baseline",
        LibTarget,
        error_handler, 
        print_handler);
    if (!bResult)
    return false;
    return true;
}

LIB_data_baseline_C_API 
bool MW_CALL_CONV data_baselineInitialize(void)
{
    return data_baselineInitializeWithHandlers(mclDefaultErrorHandler, 
                                             mclDefaultPrintHandler);
}

LIB_data_baseline_C_API 
void MW_CALL_CONV data_baselineTerminate(void)
{
    if (_mcr_inst)
        mclTerminateInstance(&_mcr_inst);
}

LIB_data_baseline_C_API 
void MW_CALL_CONV data_baselinePrintStackTrace(void) 
{
    char** stackTrace;
    int stackDepth = mclGetStackTrace(&stackTrace);
    int i;
    for(i=0; i<stackDepth; i++)
    {
        mclWrite(2 /* stderr */, stackTrace[i], sizeof(char)*strlen(stackTrace[i]));
        mclWrite(2 /* stderr */, "\n", sizeof(char)*strlen("\n"));
    }
    mclFreeStackTrace(&stackTrace, stackDepth);
}


LIB_data_baseline_C_API 
bool MW_CALL_CONV mlxData_baseline(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
    return mclFeval(_mcr_inst, "data_baseline", nlhs, plhs, nrhs, prhs);
}

LIB_data_baseline_CPP_API 
void MW_CALL_CONV data_baseline(int nargout, mwArray& data_baselined, mwArray& base, 
                                const mwArray& data, const mwArray& peak_threshold, const 
                                mwArray& smooth_window, const mwArray& noise_window)
{
    mclcppMlfFeval(_mcr_inst, "data_baseline", nargout, 2, 4, &data_baselined, &base, &data, &peak_threshold, &smooth_window, &noise_window);
}

