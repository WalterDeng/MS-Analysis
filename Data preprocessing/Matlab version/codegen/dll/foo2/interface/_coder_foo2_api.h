/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_foo2_api.h
 *
 * Code generation for function 'foo2'
 *
 */

#ifndef _CODER_FOO2_API_H
#define _CODER_FOO2_API_H

/* Include files */
#include "emlrt.h"
#include "tmwtypes.h"
#include <string.h>

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
real_T foo2(real_T a);

void foo2_api(const mxArray *prhs, const mxArray **plhs);

void foo2_atexit(void);

void foo2_initialize(void);

void foo2_terminate(void);

void foo2_xil_shutdown(void);

void foo2_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (_coder_foo2_api.h) */
