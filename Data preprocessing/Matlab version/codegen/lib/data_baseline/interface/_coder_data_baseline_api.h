//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// _coder_data_baseline_api.h
//
// Code generation for function 'data_baseline'
//

#ifndef _CODER_DATA_BASELINE_API_H
#define _CODER_DATA_BASELINE_API_H

// Include files
#include "coder_array_mex.h"
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void data_baseline(coder::array<real_T, 2U> *data, real_T peak_threshold,
                   real_T smooth_window, real_T noise_window,
                   coder::array<real_T, 2U> *data_baselined,
                   coder::array<real_T, 2U> *base);

void data_baseline_api(const mxArray *const prhs[4], int32_T nlhs,
                       const mxArray *plhs[2]);

void data_baseline_atexit();

void data_baseline_initialize();

void data_baseline_terminate();

void data_baseline_xil_shutdown();

void data_baseline_xil_terminate();

#endif
// End of code generation (_coder_data_baseline_api.h)
