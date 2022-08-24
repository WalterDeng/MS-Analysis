/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * data_baseline.h
 *
 * Code generation for function 'data_baseline'
 *
 */

#ifndef DATA_BASELINE_H
#define DATA_BASELINE_H

/* Include files */
#include "data_baseline_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void data_baseline(const emxArray_real_T *data, int peak_threshold,
                          int smooth_window, int noise_window,
                          emxArray_real_T *data_baselined,
                          emxArray_real_T *base);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (data_baseline.h) */
