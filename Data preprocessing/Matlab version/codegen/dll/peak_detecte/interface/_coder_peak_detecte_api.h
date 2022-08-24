/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_peak_detecte_api.h
 *
 * Code generation for function 'peak_detecte'
 *
 */

#ifndef _CODER_PEAK_DETECTE_API_H
#define _CODER_PEAK_DETECTE_API_H

/* Include files */
#include "emlrt.h"
#include "tmwtypes.h"
#include <string.h>

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
struct emxArray_real_T {
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};
#endif /* struct_emxArray_real_T */
#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T
typedef struct emxArray_real_T emxArray_real_T;
#endif /* typedef_emxArray_real_T */

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void peak_detecte(emxArray_real_T *data, real_T scanF,
                  emxArray_real_T *peaks_info);

void peak_detecte_api(const mxArray *const prhs[2], const mxArray **plhs);

void peak_detecte_atexit(void);

void peak_detecte_initialize(void);

void peak_detecte_terminate(void);

void peak_detecte_xil_shutdown(void);

void peak_detecte_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (_coder_peak_detecte_api.h) */
