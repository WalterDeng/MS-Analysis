/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_foo_api.h
 *
 * Code generation for function 'foo'
 *
 */

#ifndef _CODER_FOO_API_H
#define _CODER_FOO_API_H

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
real_T foo(real_T a);

void foo_api(const mxArray *prhs, const mxArray **plhs);

void foo_atexit(void);

void foo_initialize(void);

void foo_terminate(void);

void foo_xil_shutdown(void);

void foo_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (_coder_foo_api.h) */
