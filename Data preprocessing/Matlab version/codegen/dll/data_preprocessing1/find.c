/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * find.c
 *
 * Code generation for function 'find'
 *
 */

/* Include files */
#include "find.h"
#include "data_preprocessing_emxutil.h"
#include "data_preprocessing_types.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void eml_find(const emxArray_real_T *x, int i_data[], int i_size[2])
{
  emxArray_int32_T *i;
  const double *x_data;
  int idx;
  int ii;
  int k;
  int *b_i_data;
  bool exitg1;
  x_data = x->data;
  emxInit_int32_T(&i);
  k = (1 <= x->size[1]);
  idx = 0;
  ii = i->size[0] * i->size[1];
  i->size[0] = 1;
  i->size[1] = k;
  emxEnsureCapacity_int32_T(i, ii);
  b_i_data = i->data;
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii <= x->size[1] - 1)) {
    if (x_data[ii] != 0.0) {
      idx++;
      b_i_data[idx - 1] = ii + 1;
      if (idx >= k) {
        exitg1 = true;
      } else {
        ii++;
      }
    } else {
      ii++;
    }
  }
  if (k == 1) {
    if (idx == 0) {
      i->size[0] = 1;
      i->size[1] = 0;
    }
  } else {
    ii = i->size[0] * i->size[1];
    i->size[1] = (1 <= idx);
    emxEnsureCapacity_int32_T(i, ii);
    b_i_data = i->data;
  }
  i_size[0] = 1;
  i_size[1] = i->size[1];
  ii = i->size[1];
  if (0 <= ii - 1) {
    i_data[0] = b_i_data[0];
  }
  emxFree_int32_T(&i);
}

/* End of code generation (find.c) */
