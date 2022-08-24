/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * wavedec.c
 *
 * Code generation for function 'wavedec'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "data_preprocessing.h"
#include "wavedec.h"
#include "data_preprocessing_emxutil.h"

/* Function Declarations */
static int div_s32(int numerator, int denominator);

/* Function Definitions */
static int div_s32(int numerator, int denominator)
{
  int quotient;
  unsigned int b_numerator;
  unsigned int b_denominator;
  unsigned int tempAbsQuotient;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    if (numerator < 0) {
      b_numerator = ~(unsigned int)numerator + 1U;
    } else {
      b_numerator = (unsigned int)numerator;
    }

    if (denominator < 0) {
      b_denominator = ~(unsigned int)denominator + 1U;
    } else {
      b_denominator = (unsigned int)denominator;
    }

    tempAbsQuotient = b_numerator / b_denominator;
    if ((numerator < 0) != (denominator < 0)) {
      quotient = -(int)tempAbsQuotient;
    } else {
      quotient = (int)tempAbsQuotient;
    }
  }

  return quotient;
}

void wavedec(const emxArray_real_T *x, emxArray_real_T *c, double l[4])
{
  emxArray_real_T *xv;
  int nwrap;
  int i5;
  emxArray_real_T *y;
  emxArray_int32_T *J;
  emxArray_real_T *b_c;
  emxArray_real_T *a;
  emxArray_real_T *c_c;
  int k;
  int lx;
  int b_lx;
  int lx2;
  int ia;
  unsigned int unnamed_idx_1;
  int ic;
  static const double b[6] = { 0.035226291882100656, -0.085441273882241486,
    -0.13501102001039084, 0.45987750211933132, 0.80689150931333875,
    0.33267055295095688 };

  static const double b_b[6] = { -0.33267055295095688, 0.80689150931333875,
    -0.45987750211933132, -0.13501102001039084, 0.085441273882241486,
    0.035226291882100656 };

  c->size[0] = 1;
  c->size[1] = 0;
  l[0] = 0.0;
  l[1] = 0.0;
  l[2] = 0.0;
  l[3] = 0.0;
  emxInit_real_T(&xv, 2);
  nwrap = x->size[1];
  i5 = xv->size[0] * xv->size[1];
  xv->size[0] = 1;
  xv->size[1] = nwrap;
  emxEnsureCapacity_real_T(xv, i5);
  for (i5 = 0; i5 < nwrap; i5++) {
    xv->data[i5] = x->data[i5];
  }

  if (x->size[1] != 0) {
    l[3] = x->size[1];
    emxInit_real_T(&y, 2);
    emxInit_int32_T(&J, 2);
    emxInit_real_T(&b_c, 1);
    emxInit_real_T(&a, 1);
    emxInit_real_T(&c_c, 2);
    for (k = 0; k < 2; k++) {
      lx = xv->size[1] + 3;
      if (xv->size[1] == 0) {
        i5 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = 10;
        emxEnsureCapacity_real_T(y, i5);
        for (i5 = 0; i5 < 10; i5++) {
          y->data[i5] = 0.0;
        }
      } else {
        b_lx = xv->size[1];
        lx2 = xv->size[1] << 1;
        i5 = J->size[0] * J->size[1];
        J->size[0] = 1;
        J->size[1] = 10 + xv->size[1];
        emxEnsureCapacity_int32_T(J, i5);
        ia = 10 + xv->size[1];
        for (i5 = 0; i5 < ia; i5++) {
          J->data[i5] = 0;
        }

        if (xv->size[1] < 5) {
          nwrap = 4 - xv->size[1];
          for (ic = 0; ic <= nwrap; ic++) {
            if (lx2 == 0) {
              ia = 1;
            } else {
              ia = 5 - (ic + lx2 * div_s32(4 - ic, lx2));
            }

            J->data[ic] = ia;
            if (ia > b_lx) {
              J->data[ic] = (lx2 - ia) + 1;
            }
          }

          i5 = 6 - xv->size[1];
          for (ic = i5; ic < 6; ic++) {
            J->data[ic - 1] = 6 - ic;
          }
        } else {
          for (ic = 0; ic < 5; ic++) {
            J->data[ic] = 5 - ic;
          }
        }

        for (ic = 0; ic < b_lx; ic++) {
          J->data[ic + 5] = ic + 1;
        }

        if (xv->size[1] < 5) {
          for (ic = 0; ic < b_lx; ic++) {
            J->data[(b_lx + ic) + 5] = b_lx - ic;
          }

          i5 = xv->size[1] + 1;
          for (ic = i5; ic < 6; ic++) {
            nwrap = ic - b_lx;
            if (nwrap > b_lx) {
              if (lx2 == 0) {
                nwrap = 1;
              } else {
                nwrap -= lx2 * div_s32(nwrap - 1, lx2);
              }

              if (nwrap > b_lx) {
                nwrap = (lx2 - nwrap) + 1;
              }
            }

            J->data[(b_lx + ic) + 4] = nwrap;
          }
        } else {
          for (ic = 0; ic < 5; ic++) {
            J->data[(b_lx + ic) + 5] = b_lx - ic;
          }
        }

        i5 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = J->size[1];
        emxEnsureCapacity_real_T(y, i5);
        ia = J->size[1];
        for (i5 = 0; i5 < ia; i5++) {
          y->data[i5] = xv->data[J->data[i5] - 1];
        }
      }

      unnamed_idx_1 = (unsigned int)y->size[1];
      ia = (int)unnamed_idx_1;
      i5 = a->size[0];
      a->size[0] = (int)unnamed_idx_1;
      emxEnsureCapacity_real_T(a, i5);
      for (i5 = 0; i5 < ia; i5++) {
        a->data[i5] = y->data[i5];
      }

      lx2 = a->size[0];
      i5 = b_c->size[0];
      b_c->size[0] = a->size[0] - 5;
      emxEnsureCapacity_real_T(b_c, i5);
      ia = a->size[0];
      for (i5 = 0; i5 <= ia - 6; i5++) {
        b_c->data[i5] = 0.0;
      }

      for (nwrap = 0; nwrap < 6; nwrap++) {
        ia = nwrap;
        ic = 0;
        for (b_lx = 0; b_lx <= lx2 - 6; b_lx++) {
          b_c->data[ic] += b[5 - nwrap] * a->data[ia];
          ic++;
          ia++;
        }
      }

      i5 = xv->size[1] + 4;
      nwrap = xv->size[0] * xv->size[1];
      xv->size[0] = 1;
      ia = (i5 - 1) >> 1;
      xv->size[1] = ia + 1;
      emxEnsureCapacity_real_T(xv, nwrap);
      for (i5 = 0; i5 <= ia; i5++) {
        xv->data[i5] = b_c->data[1 + (i5 << 1)];
      }

      unnamed_idx_1 = (unsigned int)y->size[1];
      ia = (int)unnamed_idx_1;
      i5 = a->size[0];
      a->size[0] = (int)unnamed_idx_1;
      emxEnsureCapacity_real_T(a, i5);
      for (i5 = 0; i5 < ia; i5++) {
        a->data[i5] = y->data[i5];
      }

      lx2 = a->size[0];
      i5 = b_c->size[0];
      b_c->size[0] = a->size[0] - 5;
      emxEnsureCapacity_real_T(b_c, i5);
      ia = a->size[0];
      for (i5 = 0; i5 <= ia - 6; i5++) {
        b_c->data[i5] = 0.0;
      }

      for (nwrap = 0; nwrap < 6; nwrap++) {
        ia = nwrap;
        ic = 0;
        for (b_lx = 0; b_lx <= lx2 - 6; b_lx++) {
          b_c->data[ic] += b_b[5 - nwrap] * a->data[ia];
          ic++;
          ia++;
        }
      }

      i5 = c_c->size[0] * c_c->size[1];
      c_c->size[0] = 1;
      ia = lx >> 1;
      c_c->size[1] = (ia + c->size[1]) + 1;
      emxEnsureCapacity_real_T(c_c, i5);
      for (i5 = 0; i5 <= ia; i5++) {
        c_c->data[i5] = b_c->data[1 + (i5 << 1)];
      }

      nwrap = c->size[1];
      for (i5 = 0; i5 < nwrap; i5++) {
        c_c->data[(i5 + ia) + 1] = c->data[i5];
      }

      i5 = c->size[0] * c->size[1];
      c->size[0] = 1;
      c->size[1] = c_c->size[1];
      emxEnsureCapacity_real_T(c, i5);
      nwrap = c_c->size[0] * c_c->size[1];
      for (i5 = 0; i5 < nwrap; i5++) {
        c->data[i5] = c_c->data[i5];
      }

      l[2 - k] = (double)ia + 1.0;
    }

    emxFree_real_T(&c_c);
    emxFree_real_T(&a);
    emxFree_real_T(&b_c);
    emxFree_int32_T(&J);
    i5 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = xv->size[1] + c->size[1];
    emxEnsureCapacity_real_T(y, i5);
    ia = xv->size[1];
    for (i5 = 0; i5 < ia; i5++) {
      y->data[i5] = xv->data[i5];
    }

    ia = c->size[1];
    for (i5 = 0; i5 < ia; i5++) {
      y->data[i5 + xv->size[1]] = c->data[i5];
    }

    i5 = c->size[0] * c->size[1];
    c->size[0] = 1;
    c->size[1] = y->size[1];
    emxEnsureCapacity_real_T(c, i5);
    ia = y->size[0] * y->size[1];
    for (i5 = 0; i5 < ia; i5++) {
      c->data[i5] = y->data[i5];
    }

    emxFree_real_T(&y);
    l[0] = xv->size[1];
  }

  emxFree_real_T(&xv);
}

/* End of code generation (wavedec.c) */
