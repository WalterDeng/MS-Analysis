/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * vmedian.c
 *
 * Code generation for function 'vmedian'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "data_preprocessing.h"
#include "vmedian.h"
#include "data_preprocessing_emxutil.h"
#include "quickselect.h"

/* Function Definitions */
double vmedian(emxArray_real_T *v, int n)
{
  double m;
  int k;
  emxArray_real_T *unusedU3;
  int exitg1;
  int midm1;
  int ilast;
  boolean_T p;
  int loop_ub;
  double b;
  int unusedU2;
  k = 0;
  emxInit_real_T(&unusedU3, 2);
  do {
    exitg1 = 0;
    if (k <= n - 1) {
      if (rtIsNaN(v->data[k])) {
        m = rtNaN;
        exitg1 = 1;
      } else {
        k++;
      }
    } else {
      if (n <= 4) {
        if (n == 0) {
          m = rtNaN;
        } else if (n == 1) {
          m = v->data[0];
        } else if (n == 2) {
          if (rtIsInf(v->data[0]) || rtIsInf(v->data[1])) {
            m = (v->data[0] + v->data[1]) / 2.0;
          } else {
            m = v->data[0] + (v->data[1] - v->data[0]) / 2.0;
          }
        } else if (n == 3) {
          if (rtIsNaN(v->data[1])) {
            p = !rtIsNaN(v->data[0]);
          } else {
            p = ((!rtIsNaN(v->data[0])) && (v->data[0] < v->data[1]));
          }

          if (p) {
            if (rtIsNaN(v->data[2])) {
              p = !rtIsNaN(v->data[1]);
            } else {
              p = ((!rtIsNaN(v->data[1])) && (v->data[1] < v->data[2]));
            }

            if (p) {
              loop_ub = 1;
            } else {
              if (rtIsNaN(v->data[2])) {
                p = !rtIsNaN(v->data[0]);
              } else {
                p = ((!rtIsNaN(v->data[0])) && (v->data[0] < v->data[2]));
              }

              if (p) {
                loop_ub = 2;
              } else {
                loop_ub = 0;
              }
            }
          } else {
            if (rtIsNaN(v->data[2])) {
              p = !rtIsNaN(v->data[0]);
            } else {
              p = ((!rtIsNaN(v->data[0])) && (v->data[0] < v->data[2]));
            }

            if (p) {
              loop_ub = 0;
            } else {
              if (rtIsNaN(v->data[2])) {
                p = !rtIsNaN(v->data[1]);
              } else {
                p = ((!rtIsNaN(v->data[1])) && (v->data[1] < v->data[2]));
              }

              if (p) {
                loop_ub = 2;
              } else {
                loop_ub = 1;
              }
            }
          }

          m = v->data[loop_ub];
        } else {
          if (rtIsNaN(v->data[1])) {
            p = !rtIsNaN(v->data[0]);
          } else {
            p = ((!rtIsNaN(v->data[0])) && (v->data[0] < v->data[1]));
          }

          if (p) {
            if (rtIsNaN(v->data[2])) {
              p = !rtIsNaN(v->data[1]);
            } else {
              p = ((!rtIsNaN(v->data[1])) && (v->data[1] < v->data[2]));
            }

            if (p) {
              k = 0;
              loop_ub = 1;
              unusedU2 = 2;
            } else {
              if (rtIsNaN(v->data[2])) {
                p = !rtIsNaN(v->data[0]);
              } else {
                p = ((!rtIsNaN(v->data[0])) && (v->data[0] < v->data[2]));
              }

              if (p) {
                k = 0;
                loop_ub = 2;
                unusedU2 = 1;
              } else {
                k = 2;
                loop_ub = 0;
                unusedU2 = 1;
              }
            }
          } else {
            if (rtIsNaN(v->data[2])) {
              p = !rtIsNaN(v->data[0]);
            } else {
              p = ((!rtIsNaN(v->data[0])) && (v->data[0] < v->data[2]));
            }

            if (p) {
              k = 1;
              loop_ub = 0;
              unusedU2 = 2;
            } else {
              if (rtIsNaN(v->data[2])) {
                p = !rtIsNaN(v->data[1]);
              } else {
                p = ((!rtIsNaN(v->data[1])) && (v->data[1] < v->data[2]));
              }

              if (p) {
                k = 1;
                loop_ub = 2;
                unusedU2 = 0;
              } else {
                k = 2;
                loop_ub = 1;
                unusedU2 = 0;
              }
            }
          }

          if (v->data[k] < v->data[3]) {
            if (v->data[3] < v->data[unusedU2]) {
              if (rtIsInf(v->data[loop_ub]) || rtIsInf(v->data[3])) {
                m = (v->data[loop_ub] + v->data[3]) / 2.0;
              } else {
                m = v->data[loop_ub] + (v->data[3] - v->data[loop_ub]) / 2.0;
              }
            } else if (rtIsInf(v->data[loop_ub]) || rtIsInf(v->data[unusedU2]))
            {
              m = (v->data[loop_ub] + v->data[unusedU2]) / 2.0;
            } else {
              m = v->data[loop_ub] + (v->data[unusedU2] - v->data[loop_ub]) /
                2.0;
            }
          } else if (rtIsInf(v->data[k]) || rtIsInf(v->data[loop_ub])) {
            m = (v->data[k] + v->data[loop_ub]) / 2.0;
          } else {
            m = v->data[k] + (v->data[loop_ub] - v->data[k]) / 2.0;
          }
        }
      } else {
        midm1 = n >> 1;
        if ((n & 1) == 0) {
          quickselect(v, midm1 + 1, n, &m, &k, &ilast);
          if (midm1 < k) {
            k = unusedU3->size[0] * unusedU3->size[1];
            unusedU3->size[0] = 1;
            unusedU3->size[1] = v->size[1];
            emxEnsureCapacity_real_T(unusedU3, k);
            loop_ub = v->size[0] * v->size[1];
            for (k = 0; k < loop_ub; k++) {
              unusedU3->data[k] = v->data[k];
            }

            quickselect(unusedU3, midm1, ilast - 1, &b, &k, &unusedU2);
            if (rtIsInf(m) || rtIsInf(b)) {
              m = (m + b) / 2.0;
            } else {
              m += (b - m) / 2.0;
            }
          }
        } else {
          k = unusedU3->size[0] * unusedU3->size[1];
          unusedU3->size[0] = 1;
          unusedU3->size[1] = v->size[1];
          emxEnsureCapacity_real_T(unusedU3, k);
          loop_ub = v->size[0] * v->size[1];
          for (k = 0; k < loop_ub; k++) {
            unusedU3->data[k] = v->data[k];
          }

          quickselect(unusedU3, midm1 + 1, n, &m, &k, &loop_ub);
        }
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  emxFree_real_T(&unusedU3);
  return m;
}

/* End of code generation (vmedian.c) */
