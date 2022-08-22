//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// data_baseline.h
//
// Code generation for function 'data_baseline'
//

#ifndef DATA_BASELINE_H
#define DATA_BASELINE_H

// Include files
#include "data_baseline_spec.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
DATA_BASELINE_DLL_EXPORT extern void
data_baseline(const coder::array<double, 2U> &data, double peak_threshold,
              double smooth_window, double noise_window,
              coder::array<double, 2U> &data_baselined,
              coder::array<double, 2U> &base);

#endif
// End of code generation (data_baseline.h)
