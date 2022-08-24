/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_data_preprocessing_api.h
 *
 * Code generation for function 'data_preprocessing'
 *
 */

#ifndef _CODER_DATA_PREPROCESSING_API_H
#define _CODER_DATA_PREPROCESSING_API_H

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
void data_preprocessing(emxArray_real_T *atlas_data,
                        emxArray_real_T *data_baselined, emxArray_real_T *base,
                        emxArray_real_T *peaks_info);

void data_preprocessing_api(const mxArray *prhs, int32_T nlhs,
                            const mxArray *plhs[3]);

void data_preprocessing_atexit(void);

void data_preprocessing_initialize(void);

void data_preprocessing_terminate(void);

void data_preprocessing_xil_shutdown(void);

void data_preprocessing_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (_coder_data_preprocessing_api.h) */
