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
#include "rt_nonfinite.h"
#include "data_preprocessing.h"
#include "trapz.h"
#include "data_preprocessing_emxutil.h"

/* Function Definitions */
double trapz(const emxArray_real_T *x)
{
  double z;
  emxArray_real_T *c;
  int outsize_idx_0;
  int i7;
  int iac;
  int ia;
  z = 0.0;
  if (x->size[1] > 1) {
    emxInit_real_T(&c, 1);
    outsize_idx_0 = x->size[1];
    i7 = c->size[0];
    c->size[0] = outsize_idx_0;
    emxEnsureCapacity_real_T(c, i7);
    for (i7 = 0; i7 < outsize_idx_0; i7++) {
      c->data[i7] = 1.0;
    }

    c->data[0] = 0.5;
    c->data[x->size[1] - 1] = 0.5;
    outsize_idx_0 = 0;
    i7 = x->size[1];
    for (iac = 1; iac <= i7; iac++) {
      for (ia = iac; ia <= iac; ia++) {
        z += x->data[ia - 1] * c->data[outsize_idx_0];
      }

      outsize_idx_0++;
    }

    emxFree_real_T(&c);
  }

  return z;
}

/* End of code generation (trapz.c) */
