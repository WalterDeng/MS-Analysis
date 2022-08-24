/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * diff.c
 *
 * Code generation for function 'diff'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "data_preprocessing.h"
#include "diff.h"
#include "data_preprocessing_emxutil.h"

/* Function Definitions */
void diff(const emxArray_real_T *x, emxArray_real_T *y)
{
  int dimSize;
  int ySize_idx_1;
  int iyLead;
  double work;
  int m;
  double tmp2;
  dimSize = x->size[1];
  if (x->size[1] <= 1) {
    y->size[0] = 1;
    y->size[1] = 0;
  } else {
    ySize_idx_1 = x->size[1] - 1;
    iyLead = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = ySize_idx_1;
    emxEnsureCapacity_real_T(y, iyLead);
    ySize_idx_1 = 1;
    iyLead = 0;
    work = x->data[0];
    for (m = 2; m <= dimSize; m++) {
      tmp2 = work;
      work = x->data[ySize_idx_1];
      y->data[iyLead] = x->data[ySize_idx_1] - tmp2;
      ySize_idx_1++;
      iyLead++;
    }
  }
}

/* End of code generation (diff.c) */
