/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * trapz.c
 *
 * Code generation for function 'trapz'
 *
 */

/* Include files */
#include "trapz.h"
#include "data_preprocessing_emxutil.h"
#include "data_preprocessing_types.h"
#include "rt_nonfinite.h"

/* Function Definitions */
double trapz(const emxArray_real_T *x)
{
  emxArray_real_T *c;
  const double *x_data;
  double z;
  double *c_data;
  int i;
  int ia;
  int iac;
  int ix;
  x_data = x->data;
  z = 0.0;
  if (x->size[1] > 1) {
    emxInit_real_T(&c, 1);
    i = c->size[0];
    c->size[0] = x->size[1];
    emxEnsureCapacity_real_T(c, i);
    c_data = c->data;
    ix = x->size[1];
    for (i = 0; i < ix; i++) {
      c_data[i] = 1.0;
    }
    c_data[0] = 0.5;
    c_data[x->size[1] - 1] = 0.5;
    ix = 0;
    i = x->size[1];
    for (iac = 1; iac <= i; iac++) {
      for (ia = iac; ia <= iac; ia++) {
        z += x_data[ia - 1] * c_data[ix];
      }
      ix++;
    }
    emxFree_real_T(&c);
  }
  return z;
}

/* End of code generation (trapz.c) */
