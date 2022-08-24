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
#include "diff.h"
#include "data_preprocessing_emxutil.h"
#include "data_preprocessing_types.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void diff(const emxArray_real_T *x, emxArray_real_T *y)
{
  const double *x_data;
  double tmp2;
  double work;
  double *y_data;
  int dimSize;
  int m;
  x_data = x->data;
  dimSize = x->size[1];
  if (x->size[1] <= 1) {
    y->size[0] = 1;
    y->size[1] = 0;
  } else {
    m = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = x->size[1] - 1;
    emxEnsureCapacity_real_T(y, m);
    y_data = y->data;
    work = x_data[0];
    for (m = 2; m <= dimSize; m++) {
      tmp2 = work;
      work = x_data[m - 1];
      y_data[m - 2] = work - tmp2;
    }
  }
}

/* End of code generation (diff.c) */
