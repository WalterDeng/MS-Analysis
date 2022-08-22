//
// MATLAB Compiler: 8.3 (R2021b)
// Date: Thu Feb 17 17:56:41 2022
// Arguments:
// "-B""macro_default""-W""cpplib:data_baseline""-T""link:lib""data_baseline.m""
// -C"
//

#ifndef data_baseline_h
#define data_baseline_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#include "mclcppclass.h"
#ifdef __cplusplus
extern "C" { // sbcheck:ok:extern_c
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_data_baseline_C_API 
#define LIB_data_baseline_C_API /* No special import/export declaration */
#endif

/* GENERAL LIBRARY FUNCTIONS -- START */

extern LIB_data_baseline_C_API 
bool MW_CALL_CONV data_baselineInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_data_baseline_C_API 
bool MW_CALL_CONV data_baselineInitialize(void);

extern LIB_data_baseline_C_API 
void MW_CALL_CONV data_baselineTerminate(void);

extern LIB_data_baseline_C_API 
void MW_CALL_CONV data_baselinePrintStackTrace(void);

/* GENERAL LIBRARY FUNCTIONS -- END */

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

extern LIB_data_baseline_C_API 
bool MW_CALL_CONV mlxData_baseline(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */

#ifdef __cplusplus
}
#endif


/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__MINGW64__)

#ifdef EXPORTING_data_baseline
#define PUBLIC_data_baseline_CPP_API __declspec(dllexport)
#else
#define PUBLIC_data_baseline_CPP_API __declspec(dllimport)
#endif

#define LIB_data_baseline_CPP_API PUBLIC_data_baseline_CPP_API

#else

#if !defined(LIB_data_baseline_CPP_API)
#if defined(LIB_data_baseline_C_API)
#define LIB_data_baseline_CPP_API LIB_data_baseline_C_API
#else
#define LIB_data_baseline_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_data_baseline_CPP_API void MW_CALL_CONV data_baseline(int nargout, mwArray& data_baselined, mwArray& base, const mwArray& data, const mwArray& peak_threshold, const mwArray& smooth_window, const mwArray& noise_window);

/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */
#endif

#endif
