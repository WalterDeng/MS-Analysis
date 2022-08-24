/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * wnoisest.c
 *
 * Code generation for function 'wnoisest'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "data_preprocessing.h"
#include "wnoisest.h"
#include "data_preprocessing_emxutil.h"
#include "vmedian.h"
#include "abs.h"

/* Function Definitions */
void wnoisest(const emxArray_real_T *c, const double varargin_1[4], double stdc
              [2])
{
  cell_wrap_4 ccell[2];
  int first_idx_0_tmp;
  int b_first_idx_0_tmp;
  int first_idx_0;
  int last_idx_0;
  int i6;
  emxArray_real_T *x;
  emxArray_real_T *b_x;
  emxInitMatrix_cell_wrap_4(ccell);
  first_idx_0_tmp = (int)varargin_1[0];
  b_first_idx_0_tmp = first_idx_0_tmp + (int)varargin_1[1];
  first_idx_0 = b_first_idx_0_tmp + 1;
  last_idx_0 = (first_idx_0 + (int)varargin_1[2]) - 1;
  if (first_idx_0 > last_idx_0) {
    first_idx_0 = 1;
    last_idx_0 = 0;
  }

  i6 = ccell[0].f1->size[0] * ccell[0].f1->size[1];
  ccell[0].f1->size[0] = 1;
  last_idx_0 -= first_idx_0;
  ccell[0].f1->size[1] = last_idx_0 + 1;
  emxEnsureCapacity_real_T(ccell[0].f1, i6);
  for (i6 = 0; i6 <= last_idx_0; i6++) {
    ccell[0].f1->data[i6] = c->data[(first_idx_0 + i6) - 1];
  }

  if (first_idx_0_tmp + 1 > b_first_idx_0_tmp) {
    first_idx_0_tmp = 0;
    b_first_idx_0_tmp = 0;
  }

  i6 = ccell[1].f1->size[0] * ccell[1].f1->size[1];
  ccell[1].f1->size[0] = 1;
  last_idx_0 = b_first_idx_0_tmp - first_idx_0_tmp;
  ccell[1].f1->size[1] = last_idx_0;
  emxEnsureCapacity_real_T(ccell[1].f1, i6);
  for (i6 = 0; i6 < last_idx_0; i6++) {
    ccell[1].f1->data[i6] = c->data[first_idx_0_tmp + i6];
  }

  emxInit_real_T(&x, 2);
  emxInit_real_T(&b_x, 2);
  b_abs(ccell[0].f1, x);
  if (x->size[1] == 0) {
    stdc[0] = rtNaN;
  } else {
    i6 = b_x->size[0] * b_x->size[1];
    b_x->size[0] = 1;
    b_x->size[1] = x->size[1];
    emxEnsureCapacity_real_T(b_x, i6);
    last_idx_0 = x->size[0] * x->size[1];
    for (i6 = 0; i6 < last_idx_0; i6++) {
      b_x->data[i6] = x->data[i6];
    }

    stdc[0] = vmedian(b_x, x->size[1]);
  }

  b_abs(ccell[1].f1, x);
  if (x->size[1] == 0) {
    stdc[1] = rtNaN;
  } else {
    i6 = b_x->size[0] * b_x->size[1];
    b_x->size[0] = 1;
    b_x->size[1] = x->size[1];
    emxEnsureCapacity_real_T(b_x, i6);
    last_idx_0 = x->size[0] * x->size[1];
    for (i6 = 0; i6 < last_idx_0; i6++) {
      b_x->data[i6] = x->data[i6];
    }

    stdc[1] = vmedian(b_x, x->size[1]);
  }

  emxFree_real_T(&b_x);
  emxFree_real_T(&x);
  emxFreeMatrix_cell_wrap_4(ccell);
  stdc[0] /= 0.6745;
  stdc[1] /= 0.6745;
}

/* End of code generation (wnoisest.c) */
