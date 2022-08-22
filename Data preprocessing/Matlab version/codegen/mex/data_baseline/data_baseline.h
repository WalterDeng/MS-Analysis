//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// data_baseline.h
//
// Code generation for function 'data_baseline'
//

#pragma once

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#include "covrt.h"
#include "emlrt.h"
#include "mex.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// Function Declarations
void data_baseline(const emlrtStack *sp, const coder::array<real_T, 2U> &data,
                   real_T peak_threshold, real_T smooth_window,
                   real_T noise_window,
                   coder::array<real_T, 2U> &data_baselined,
                   coder::array<real_T, 2U> &base);

// End of code generation (data_baseline.h)
