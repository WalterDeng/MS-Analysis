//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// data_baseline_spec.h
//
// Code generation for function 'data_baseline'
//

#ifndef DATA_BASELINE_SPEC_H
#define DATA_BASELINE_SPEC_H

// Include files
#ifdef DATA_BASELINE_XIL_BUILD
#if defined(_MSC_VER) || defined(__LCC__)
#define DATA_BASELINE_DLL_EXPORT __declspec(dllimport)
#else
#define DATA_BASELINE_DLL_EXPORT __attribute__((visibility("default")))
#endif
#elif defined(BUILDING_DATA_BASELINE)
#if defined(_MSC_VER) || defined(__LCC__)
#define DATA_BASELINE_DLL_EXPORT __declspec(dllexport)
#else
#define DATA_BASELINE_DLL_EXPORT __attribute__((visibility("default")))
#endif
#else
#define DATA_BASELINE_DLL_EXPORT
#endif

#endif
// End of code generation (data_baseline_spec.h)
