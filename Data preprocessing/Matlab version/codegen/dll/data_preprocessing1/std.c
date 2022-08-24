/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * std.c
 *
 * Code generation for function 'std'
 *
 */

/* Include files */
#include "std.h"
#include "data_preprocessing_emxutil.h"
#include "data_preprocessing_types.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
double b_std(const emxArray_real_T *x)
{
  emxArray_real_T *absdiff;
  const double *x_data;
  double bsum;
  double xbar;
  double y;
  double *absdiff_data;
  int firstBlockLength;
  int hi;
  int ib;
  int k;
  int lastBlockLength;
  int n;
  int nblocks;
  x_data = x->data;
  n = x->size[0];
  if (x->size[0] == 0) {
    y = rtNaN;
  } else if (x->size[0] == 1) {
    if ((!rtIsInf(x_data[0])) && (!rtIsNaN(x_data[0]))) {
      y = 0.0;
    } else {
      y = rtNaN;
    }
  } else {
    if (x->size[0] <= 1024) {
      firstBlockLength = x->size[0];
      lastBlockLength = 0;
      nblocks = 1;
    } else {
      firstBlockLength = 1024;
      nblocks = x->size[0] >> 10;
      lastBlockLength = x->size[0] - (nblocks << 10);
      if (lastBlockLength > 0) {
        nblocks++;
      } else {
        lastBlockLength = 1024;
      }
    }
    xbar = x_data[0];
    for (k = 2; k <= firstBlockLength; k++) {
      xbar += x_data[k - 1];
    }
    for (ib = 2; ib <= nblocks; ib++) {
      firstBlockLength = (ib - 1) << 10;
      bsum = x_data[firstBlockLength];
      if (ib == nblocks) {
        hi = lastBlockLength;
      } else {
        hi = 1024;
      }
      for (k = 2; k <= hi; k++) {
        bsum += x_data[(firstBlockLength + k) - 1];
      }
      xbar += bsum;
    }
    emxInit_real_T(&absdiff, 1);
    xbar /= (double)x->size[0];
    firstBlockLength = absdiff->size[0];
    absdiff->size[0] = x->size[0];
    emxEnsureCapacity_real_T(absdiff, firstBlockLength);
    absdiff_data = absdiff->data;
    for (k = 0; k < n; k++) {
      absdiff_data[k] = fabs(x_data[k] - xbar);
    }
    y = 0.0;
    xbar = 3.3121686421112381E-170;
    firstBlockLength = x->size[0];
    for (k = 0; k < firstBlockLength; k++) {
      if (absdiff_data[k] > xbar) {
        bsum = xbar / absdiff_data[k];
        y = y * bsum * bsum + 1.0;
        xbar = absdiff_data[k];
      } else {
        bsum = absdiff_data[k] / xbar;
        y += bsum * bsum;
      }
    }
    emxFree_real_T(&absdiff);
    y = xbar * sqrt(y);
    y /= sqrt((double)x->size[0] - 1.0);
  }
  return y;
}

/* End of code generation (std.c) */
