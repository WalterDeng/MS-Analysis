/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * mean.c
 *
 * Code generation for function 'mean'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "data_preprocessing.h"
#include "mean.h"
#include "combineVectorElements.h"

/* Function Definitions */
double mean(const emxArray_real_T *x)
{
  return combineVectorElements(x) / (double)x->size[1];
}

/* End of code generation (mean.c) */
