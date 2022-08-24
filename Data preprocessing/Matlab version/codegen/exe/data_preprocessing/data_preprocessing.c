/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * data_preprocessing.c
 *
 * Code generation for function 'data_preprocessing'
 *
 */

/* Include files */
#include <math.h>
#include "rt_nonfinite.h"
#include "data_preprocessing.h"
#include "data_preprocessing_emxutil.h"
#include "trapz.h"
#include "mean.h"
#include "abs.h"
#include "diff.h"
#include "combineVectorElements.h"
#include "wnoisest.h"
#include "wavedec.h"
#include "std.h"

/* Function Declarations */
static double Baseline(emxArray_real_T *x_baselined, double start, double stop,
  const emxArray_real_T *x, emxArray_real_T *base);

/* Function Definitions */
static double Baseline(emxArray_real_T *x_baselined, double start, double stop,
  const emxArray_real_T *x, emxArray_real_T *base)
{
  double S;
  int i8;
  int i9;
  emxArray_boolean_T *b_x;
  int i10;
  int nx;
  emxArray_int32_T *ii;
  int idx;
  int n;
  boolean_T exitg1;
  emxArray_real_T *neg;
  emxArray_real_T *Ii;
  int k;
  double ex;
  double b;
  double b_b;
  double b_tmp;

  /*  执行数据中单个段落的对齐，该段落由start和stop来界定， */
  /*  x_baselined为处理后的数据，x为原始数据，base为基�? */
  if (start > stop) {
    i8 = 1;
    i9 = 0;
  } else {
    i8 = (int)start;
    i9 = (int)stop;
  }

  emxInit_boolean_T(&b_x, 2);
  i10 = b_x->size[0] * b_x->size[1];
  b_x->size[0] = 1;
  nx = i9 - i8;
  b_x->size[1] = nx + 1;
  emxEnsureCapacity_boolean_T(b_x, i10);
  for (i9 = 0; i9 <= nx; i9++) {
    b_x->data[i9] = (x_baselined->data[(i8 + i9) - 1] < 0.0);
  }

  emxInit_int32_T(&ii, 2);
  nx = b_x->size[1];
  idx = 0;
  i8 = ii->size[0] * ii->size[1];
  ii->size[0] = 1;
  ii->size[1] = b_x->size[1];
  emxEnsureCapacity_int32_T(ii, i8);
  n = 0;
  exitg1 = false;
  while ((!exitg1) && (n <= nx - 1)) {
    if (b_x->data[n]) {
      idx++;
      ii->data[idx - 1] = n + 1;
      if (idx >= nx) {
        exitg1 = true;
      } else {
        n++;
      }
    } else {
      n++;
    }
  }

  if (b_x->size[1] == 1) {
    if (idx == 0) {
      ii->size[0] = 1;
      ii->size[1] = 0;
    }
  } else if (1 > idx) {
    ii->size[1] = 0;
  } else {
    i8 = ii->size[0] * ii->size[1];
    ii->size[1] = idx;
    emxEnsureCapacity_int32_T(ii, i8);
  }

  emxFree_boolean_T(&b_x);
  emxInit_real_T(&neg, 2);
  i8 = neg->size[0] * neg->size[1];
  neg->size[0] = 1;
  neg->size[1] = ii->size[1];
  emxEnsureCapacity_real_T(neg, i8);
  nx = ii->size[0] * ii->size[1];
  for (i8 = 0; i8 < nx; i8++) {
    neg->data[i8] = ii->data[i8];
  }

  /* if there are no more than half of V1 instances below zero, the for loop should terminate */
  if (neg->size[1] < 3) {
    S = 0.0;
  } else {
    emxInit_real_T(&Ii, 2);
    i8 = neg->size[1];
    i9 = neg->size[0] * neg->size[1];
    neg->size[1] = i8 + 1;
    emxEnsureCapacity_real_T(neg, i9);
    neg->data[i8] = rtInf;

    /*  zeroes in Ii indicates that two consecetive valeus are below zero, 5 in a row indicates 6 places below zero in a row */
    nx = neg->size[1] - 1;
    i8 = Ii->size[0] * Ii->size[1];
    Ii->size[0] = 1;
    Ii->size[1] = nx;
    emxEnsureCapacity_real_T(Ii, i8);
    for (i8 = 0; i8 < nx; i8++) {
      Ii->data[i8] = (neg->data[i8] - neg->data[1 + i8]) + 1.0;
    }

    /*  Ii2是一个索引，显示非零的位�? */
    nx = Ii->size[1];
    idx = 0;
    i8 = ii->size[0] * ii->size[1];
    ii->size[0] = 1;
    ii->size[1] = Ii->size[1];
    emxEnsureCapacity_int32_T(ii, i8);
    n = 0;
    exitg1 = false;
    while ((!exitg1) && (n <= nx - 1)) {
      if (Ii->data[n] != 0.0) {
        idx++;
        ii->data[idx - 1] = n + 1;
        if (idx >= nx) {
          exitg1 = true;
        } else {
          n++;
        }
      } else {
        n++;
      }
    }

    if (1 > idx) {
      ii->size[1] = 0;
    } else {
      i8 = ii->size[0] * ii->size[1];
      ii->size[1] = idx;
      emxEnsureCapacity_int32_T(ii, i8);
    }

    i8 = neg->size[0] * neg->size[1];
    neg->size[0] = 1;
    neg->size[1] = 1 + ii->size[1];
    emxEnsureCapacity_real_T(neg, i8);
    neg->data[0] = 0.0;
    nx = ii->size[1];
    for (i8 = 0; i8 < nx; i8++) {
      neg->data[i8 + 1] = ii->data[i8];
    }

    /*  如果范围内只有一个非�? */
    if (neg->size[1] == 1) {
      if (start > stop) {
        i8 = 1;
        i9 = -1;
      } else {
        i8 = (int)start;
        i9 = (int)stop - 1;
      }

      n = (i9 - i8) + 2;
      if (n <= 2) {
        if (n == 1) {
          idx = 1;
        } else if ((x_baselined->data[i8 - 1] > x_baselined->data[i8]) ||
                   (rtIsNaN(x_baselined->data[i8 - 1]) && (!rtIsNaN
                     (x_baselined->data[i8])))) {
          idx = 2;
        } else {
          idx = 1;
        }
      } else {
        if (!rtIsNaN(x_baselined->data[i8 - 1])) {
          idx = 1;
        } else {
          idx = 0;
          k = 2;
          exitg1 = false;
          while ((!exitg1) && (k <= n)) {
            if (!rtIsNaN(x_baselined->data[(i8 + k) - 2])) {
              idx = k;
              exitg1 = true;
            } else {
              k++;
            }
          }
        }

        if (idx == 0) {
          idx = 1;
        } else {
          ex = x_baselined->data[(i8 + idx) - 2];
          i9 = idx + 1;
          for (k = i9; k <= n; k++) {
            i10 = (i8 + k) - 2;
            if (ex > x_baselined->data[i10]) {
              ex = x_baselined->data[i10];
              idx = k;
            }
          }
        }
      }

      S = ((double)idx + start) - 1.0;
      n = (int)(start - 1.0) - 1;
      b = (x->data[(int)S - 1] - x->data[n]) / ((S - start) + 1.0);
      b_b = (x->data[(int)(stop + 1.0) - 1] - x->data[(int)S - 1]) / ((stop - S)
        + 1.0);
      if (start > S - 1.0) {
        i8 = 1;
      } else {
        i8 = (int)start;
      }

      ex = S - start;
      if (rtIsNaN(ex)) {
        i9 = neg->size[0] * neg->size[1];
        neg->size[0] = 1;
        neg->size[1] = 1;
        emxEnsureCapacity_real_T(neg, i9);
        neg->data[0] = rtNaN;
      } else if (ex < 1.0) {
        neg->size[0] = 1;
        neg->size[1] = 0;
      } else {
        i9 = neg->size[0] * neg->size[1];
        neg->size[0] = 1;
        nx = (int)floor(ex - 1.0);
        neg->size[1] = nx + 1;
        emxEnsureCapacity_real_T(neg, i9);
        for (i9 = 0; i9 <= nx; i9++) {
          neg->data[i9] = 1.0 + (double)i9;
        }
      }

      ex = x->data[n];
      nx = neg->size[1];
      for (i9 = 0; i9 < nx; i9++) {
        base->data[(i8 + i9) - 1] = ex + neg->data[i9] * b;
      }

      if (S + 1.0 > stop) {
        i8 = 1;
      } else {
        i8 = (int)(S + 1.0);
      }

      b = stop - S;
      if (rtIsNaN(b)) {
        i9 = neg->size[0] * neg->size[1];
        neg->size[0] = 1;
        neg->size[1] = 1;
        emxEnsureCapacity_real_T(neg, i9);
        neg->data[0] = rtNaN;
      } else if (b < 1.0) {
        neg->size[0] = 1;
        neg->size[1] = 0;
      } else {
        i9 = neg->size[0] * neg->size[1];
        neg->size[0] = 1;
        nx = (int)floor(b - 1.0);
        neg->size[1] = nx + 1;
        emxEnsureCapacity_real_T(neg, i9);
        for (i9 = 0; i9 <= nx; i9++) {
          neg->data[i9] = 1.0 + (double)i9;
        }
      }

      ex = x->data[(int)S - 1];
      nx = neg->size[1];
      for (i9 = 0; i9 < nx; i9++) {
        base->data[(i8 + i9) - 1] = ex + neg->data[i9] * b_b;
      }

      base->data[(int)S - 1] = x->data[(int)S - 1];
    } else {
      nx = neg->size[1] - 2;
      i8 = Ii->size[0] * Ii->size[1];
      Ii->size[0] = 1;
      Ii->size[1] = nx + 1;
      emxEnsureCapacity_real_T(Ii, i8);
      for (i8 = 0; i8 <= nx; i8++) {
        Ii->data[i8] = (int)neg->data[1 + i8] - (int)neg->data[i8];
      }

      n = Ii->size[1];
      if (Ii->size[1] <= 2) {
        if (Ii->size[1] == 1) {
          nx = (int)Ii->data[0];
        } else if ((int)Ii->data[0] < (int)Ii->data[1]) {
          nx = (int)Ii->data[1];
        } else {
          nx = (int)Ii->data[0];
        }
      } else {
        nx = (int)Ii->data[0];
        for (k = 2; k <= n; k++) {
          if (nx < (int)Ii->data[k - 1]) {
            nx = (int)Ii->data[k - 1];
          }
        }
      }

      if (nx > 3) {
        if (start > stop) {
          i8 = 1;
          i9 = -1;
        } else {
          i8 = (int)start;
          i9 = (int)stop - 1;
        }

        n = (i9 - i8) + 2;
        if (n <= 2) {
          if (n == 1) {
            idx = 1;
          } else if ((x_baselined->data[i8 - 1] > x_baselined->data[i8]) ||
                     (rtIsNaN(x_baselined->data[i8 - 1]) && (!rtIsNaN
                       (x_baselined->data[i8])))) {
            idx = 2;
          } else {
            idx = 1;
          }
        } else {
          if (!rtIsNaN(x_baselined->data[i8 - 1])) {
            idx = 1;
          } else {
            idx = 0;
            k = 2;
            exitg1 = false;
            while ((!exitg1) && (k <= n)) {
              if (!rtIsNaN(x_baselined->data[(i8 + k) - 2])) {
                idx = k;
                exitg1 = true;
              } else {
                k++;
              }
            }
          }

          if (idx == 0) {
            idx = 1;
          } else {
            ex = x_baselined->data[(i8 + idx) - 2];
            i9 = idx + 1;
            for (k = i9; k <= n; k++) {
              i10 = (i8 + k) - 2;
              if (ex > x_baselined->data[i10]) {
                ex = x_baselined->data[i10];
                idx = k;
              }
            }
          }
        }

        S = ((double)idx + start) - 1.0;
        n = (int)S - 1;
        ex = S - start;
        b = (x->data[n] - x->data[(int)(start - 1.0) - 1]) / (ex + 1.0);
        b_tmp = stop - S;
        b_b = (x->data[(int)(stop + 1.0) - 1] - x->data[n]) / (b_tmp + 1.0);
        if (start > S - 1.0) {
          i8 = 1;
        } else {
          i8 = (int)start;
        }

        if (rtIsNaN(ex)) {
          i9 = neg->size[0] * neg->size[1];
          neg->size[0] = 1;
          neg->size[1] = 1;
          emxEnsureCapacity_real_T(neg, i9);
          neg->data[0] = rtNaN;
        } else if (ex < 1.0) {
          neg->size[0] = 1;
          neg->size[1] = 0;
        } else {
          i9 = neg->size[0] * neg->size[1];
          neg->size[0] = 1;
          nx = (int)floor(ex - 1.0);
          neg->size[1] = nx + 1;
          emxEnsureCapacity_real_T(neg, i9);
          for (i9 = 0; i9 <= nx; i9++) {
            neg->data[i9] = 1.0 + (double)i9;
          }
        }

        ex = x->data[(int)(start - 1.0) - 1];
        nx = neg->size[1];
        for (i9 = 0; i9 < nx; i9++) {
          base->data[(i8 + i9) - 1] = ex + neg->data[i9] * b;
        }

        if (S + 1.0 > stop) {
          i8 = 1;
        } else {
          i8 = (int)(S + 1.0);
        }

        if (rtIsNaN(b_tmp)) {
          i9 = neg->size[0] * neg->size[1];
          neg->size[0] = 1;
          neg->size[1] = 1;
          emxEnsureCapacity_real_T(neg, i9);
          neg->data[0] = rtNaN;
        } else if (b_tmp < 1.0) {
          neg->size[0] = 1;
          neg->size[1] = 0;
        } else {
          i9 = neg->size[0] * neg->size[1];
          neg->size[0] = 1;
          nx = (int)floor(b_tmp - 1.0);
          neg->size[1] = nx + 1;
          emxEnsureCapacity_real_T(neg, i9);
          for (i9 = 0; i9 <= nx; i9++) {
            neg->data[i9] = 1.0 + (double)i9;
          }
        }

        ex = x->data[n];
        nx = neg->size[1];
        for (i9 = 0; i9 < nx; i9++) {
          base->data[(i8 + i9) - 1] = ex + neg->data[i9] * b_b;
        }

        base->data[n] = x->data[n];
      } else {
        S = 0.0;
      }
    }

    emxFree_real_T(&Ii);
    if (start > stop) {
      i8 = 1;
      i9 = 0;
      i10 = 1;
      n = 1;
    } else {
      i8 = (int)start;
      i9 = (int)stop;
      i10 = (int)start;
      n = (int)start;
    }

    nx = i9 - i8;
    for (i9 = 0; i9 <= nx; i9++) {
      x_baselined->data[(n + i9) - 1] = x->data[(i8 + i9) - 1] - base->data[(i10
        + i9) - 1];
    }
  }

  emxFree_int32_T(&ii);
  emxFree_real_T(&neg);
  return S;
}

void data_preprocessing(const emxArray_real_T *atlas_data, emxArray_real_T
  *data_baselined, emxArray_real_T *base, emxArray_real_T *peaks_info)
{
  emxArray_real_T *data;
  int loop_ub;
  int i0;
  emxArray_real_T *Sx;
  emxArray_real_T *noise;
  int i;
  emxArray_real_T *data_baselined_;
  int i1;
  int i2;
  int i3;
  emxArray_real_T *Base_;
  emxArray_real_T *x;
  emxArray_real_T *Mstd;
  emxArray_real_T *b_Sx;
  emxArray_real_T *fi;
  double l[4];
  double stdc[2];
  double peak_threshold;
  emxArray_real_T *base_;
  emxArray_real_T *x_baselined;
  emxArray_boolean_T *N;
  double c;
  emxArray_int32_T *ii;
  int nx;
  int idx;
  int b_fi;
  boolean_T exitg1;
  double stop;
  double w;
  int i4;
  double y2;
  unsigned int peaks_i;
  unsigned int S_i;
  unsigned int M_i;
  int b_i2;
  emxArray_real_T *b_peaks_info;
  int x1;
  int x2;
  int x3;
  emxInit_real_T(&data, 2);

  /*  对传入的二维数据data执行平滑、基线校准，并输出为data_baselined, base为确定的基线 */
  /*    此处显示详细说明 */
  /*  smooth_window, noise_window�?好为偶数 */
  /*  peak_threshold = 8000，smooth_window=4，noise_window=6 */
  /*  输入 data �?(time_series; feature_num) */
  /*  输出 data_baselined �?(feature_num) */
  /*  输出 base : (feature_num) */
  /*  --------------------- 要自动化处理的参�? ------------------------------------- */
  /*      peak_threshold = 0.00002; */
  /*  ------------------------------------------------------------------------------- */
  /* Smoothing (moving average) */
  loop_ub = atlas_data->size[1];
  i0 = data->size[0] * data->size[1];
  data->size[0] = 1;
  data->size[1] = loop_ub;
  emxEnsureCapacity_real_T(data, i0);
  for (i0 = 0; i0 < loop_ub; i0++) {
    data->data[i0] = atlas_data->data[1 + (i0 << 1)];
  }

  emxInit_real_T(&Sx, 1);
  loop_ub = atlas_data->size[1];
  i0 = Sx->size[0];
  Sx->size[0] = loop_ub;
  emxEnsureCapacity_real_T(Sx, i0);
  for (i0 = 0; i0 < loop_ub; i0++) {
    Sx->data[i0] = 0.0;
  }

  /* assignin('base','vv',vv); */
  /* assignin('base','m1',m1); */
  /*  assignin('base','iv',iv); */
  i0 = atlas_data->size[1];
  i0 -= 5;
  emxInit_real_T(&noise, 2);
  for (i = 0; i <= i0; i++) {
    if (i + 1 > 4 + i) {
      i1 = 0;
      i2 = -1;
    } else {
      i1 = i;
      i2 = i + 3;
    }

    i3 = noise->size[0] * noise->size[1];
    noise->size[0] = 1;
    loop_ub = i2 - i1;
    noise->size[1] = loop_ub + 1;
    emxEnsureCapacity_real_T(noise, i3);
    for (i2 = 0; i2 <= loop_ub; i2++) {
      noise->data[i2] = data->data[i1 + i2];
    }

    Sx->data[i + 2] = mean(noise);

    /*  �õ�ƽ�������ڵľ�ֵ */
  }

  emxInit_real_T(&data_baselined_, 2);
  loop_ub = atlas_data->size[1];
  i0 = data_baselined_->size[0] * data_baselined_->size[1];
  data_baselined_->size[0] = 1;
  data_baselined_->size[1] = loop_ub;
  emxEnsureCapacity_real_T(data_baselined_, i0);
  for (i0 = 0; i0 < loop_ub; i0++) {
    data_baselined_->data[i0] = 0.0;
  }

  emxInit_real_T(&Base_, 2);
  loop_ub = atlas_data->size[1];
  i0 = Base_->size[0] * Base_->size[1];
  Base_->size[0] = 1;
  Base_->size[1] = loop_ub;
  emxEnsureCapacity_real_T(Base_, i0);
  for (i0 = 0; i0 < loop_ub; i0++) {
    Base_->data[i0] = 0.0;
  }

  emxInit_real_T(&x, 2);

  /* from sample 1 to n1 */
  loop_ub = atlas_data->size[1] - 1;
  i0 = x->size[0] * x->size[1];
  x->size[0] = 1;
  x->size[1] = loop_ub + 1;
  emxEnsureCapacity_real_T(x, i0);
  for (i0 = 0; i0 <= loop_ub; i0++) {
    x->data[i0] = atlas_data->data[1 + (i0 << 1)];
  }

  emxInit_real_T(&Mstd, 2);
  loop_ub = atlas_data->size[1];
  i0 = Mstd->size[0] * Mstd->size[1];
  Mstd->size[0] = 1;
  Mstd->size[1] = loop_ub;
  emxEnsureCapacity_real_T(Mstd, i0);
  for (i0 = 0; i0 < loop_ub; i0++) {
    Mstd->data[i0] = 0.0;
  }

  i0 = atlas_data->size[1];
  i0 -= 21;
  emxInit_real_T(&b_Sx, 1);
  for (i = 0; i <= i0; i++) {
    if (1 + i > i + 20) {
      i1 = 0;
      i2 = -1;
    } else {
      i1 = i;
      i2 = i + 19;
    }

    i3 = b_Sx->size[0];
    loop_ub = i2 - i1;
    b_Sx->size[0] = loop_ub + 1;
    emxEnsureCapacity_real_T(b_Sx, i3);
    for (i2 = 0; i2 <= loop_ub; i2++) {
      b_Sx->data[i2] = Sx->data[i1 + i2];
    }

    Mstd->data[i] = b_std(b_Sx);

    /*  �������������ڵ�ƽ����ֵ�����׼�� */
  }

  emxFree_real_T(&b_Sx);
  emxFree_real_T(&Sx);
  loop_ub = atlas_data->size[1];
  i0 = noise->size[0] * noise->size[1];
  noise->size[0] = 1;
  noise->size[1] = loop_ub;
  emxEnsureCapacity_real_T(noise, i0);
  for (i0 = 0; i0 < loop_ub; i0++) {
    noise->data[i0] = atlas_data->data[1 + (i0 << 1)];
  }

  emxInit_real_T(&fi, 2);
  wavedec(noise, fi, l);
  wnoisest(fi, l, stdc);
  peak_threshold = stdc[0];

  /*          min_peak_height = stdc(2) * 3; */
  /* Noiese is separated from peaks by making a matrix only containing noise: */
  i0 = atlas_data->size[1];
  if (1 > i0) {
    loop_ub = 0;
  } else {
    loop_ub = atlas_data->size[1];
  }

  i0 = noise->size[0] * noise->size[1];
  noise->size[0] = 1;
  noise->size[1] = loop_ub;
  emxEnsureCapacity_real_T(noise, i0);
  for (i0 = 0; i0 < loop_ub; i0++) {
    noise->data[i0] = atlas_data->data[1 + (i0 << 1)];
  }

  i0 = atlas_data->size[1];
  i0 -= 6;
  for (i = 0; i <= i0; i++) {
    if ((Mstd->data[5 + i] < peak_threshold) && (Mstd->data[i] < peak_threshold))
    {
      noise->data[5 + i] = data->data[i + 5];
    } else {
      noise->data[5 + i] = rtNaN;
    }
  }

  emxInit_real_T(&base_, 2);
  loop_ub = atlas_data->size[1] - 1;
  i0 = base_->size[0] * base_->size[1];
  base_->size[0] = 1;
  base_->size[1] = loop_ub + 1;
  emxEnsureCapacity_real_T(base_, i0);
  for (i0 = 0; i0 <= loop_ub; i0++) {
    base_->data[i0] = atlas_data->data[1 + (i0 << 1)];
  }

  emxInit_real_T(&x_baselined, 2);

  /* The baseline is estimated as straight line from start to stop of intervals: */
  loop_ub = atlas_data->size[1];
  i0 = x_baselined->size[0] * x_baselined->size[1];
  x_baselined->size[0] = 1;
  x_baselined->size[1] = loop_ub;
  emxEnsureCapacity_real_T(x_baselined, i0);
  for (i0 = 0; i0 < loop_ub; i0++) {
    x_baselined->data[i0] = 0.0;
  }

  emxInit_boolean_T(&N, 2);
  i0 = N->size[0] * N->size[1];
  N->size[0] = 1;
  N->size[1] = noise->size[1];
  emxEnsureCapacity_boolean_T(N, i0);
  loop_ub = noise->size[0] * noise->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    N->data[i0] = rtIsNaN(noise->data[i0]);
  }

  c = 0.0;
  i0 = N->size[1];
  emxInit_int32_T(&ii, 2);
  for (i = 0; i <= i0 - 2; i++) {
    if ((!N->data[i]) && N->data[1 + i] && (c <= 2.0 + (double)i)) {
      /*  ������������Ľ���� */
      if (2 + i > N->size[1]) {
        i1 = 0;
        i2 = 0;
      } else {
        i1 = i + 1;
        i2 = N->size[1];
      }

      i3 = fi->size[0] * fi->size[1];
      fi->size[0] = 1;
      loop_ub = i2 - i1;
      fi->size[1] = loop_ub;
      emxEnsureCapacity_real_T(fi, i3);
      for (i2 = 0; i2 < loop_ub; i2++) {
        fi->data[i2] = (double)N->data[i1 + i2] - 1.0;
      }

      nx = fi->size[1];
      idx = 0;
      i1 = ii->size[0] * ii->size[1];
      ii->size[0] = 1;
      ii->size[1] = fi->size[1];
      emxEnsureCapacity_int32_T(ii, i1);
      b_fi = 0;
      exitg1 = false;
      while ((!exitg1) && (b_fi <= nx - 1)) {
        if ((signed char)fi->data[b_fi] != 0) {
          idx++;
          ii->data[idx - 1] = b_fi + 1;
          if (idx >= nx) {
            exitg1 = true;
          } else {
            b_fi++;
          }
        } else {
          b_fi++;
        }
      }

      if (fi->size[1] == 1) {
        if (idx == 0) {
          ii->size[0] = 1;
          ii->size[1] = 0;
        }
      } else if (1 > idx) {
        ii->size[1] = 0;
      } else {
        i1 = ii->size[0] * ii->size[1];
        ii->size[1] = idx;
        emxEnsureCapacity_int32_T(ii, i1);
      }

      i1 = fi->size[0] * fi->size[1];
      fi->size[0] = 1;
      fi->size[1] = ii->size[1];
      emxEnsureCapacity_real_T(fi, i1);
      loop_ub = ii->size[0] * ii->size[1];
      for (i1 = 0; i1 < loop_ub; i1++) {
        fi->data[i1] = ii->data[i1];
      }

      if (fi->size[1] == 0) {
        /*  2022.6.27 ����Ҳ�������Ĭ�ϵ���β���Ƿ����� */
        b_fi = (N->size[1] - i) - 2;
      } else {
        b_fi = (int)(unsigned int)fi->data[0];
      }

      stop = ((double)b_fi + (2.0 + (double)i)) - 2.0;

      /*                  stop  = find(N(i:end)-1, 1)+i-2; */
      /*                  stop = stop(1); */
      c = stop + 1.0;
      nx = (int)stop;
      peak_threshold = (data->data[nx - 1] - data->data[i + 1]) / ((stop - (2.0
        + (double)i)) + 1.0);
      if (2 + i > (int)stop) {
        i1 = 0;
      } else {
        i1 = i + 1;
      }

      b_fi = (nx - i) - 1;
      if (b_fi < 1) {
        Mstd->size[0] = 1;
        Mstd->size[1] = 0;
      } else {
        i2 = Mstd->size[0] * Mstd->size[1];
        Mstd->size[0] = 1;
        Mstd->size[1] = b_fi;
        emxEnsureCapacity_real_T(Mstd, i2);
        loop_ub = b_fi - 1;
        for (i2 = 0; i2 <= loop_ub; i2++) {
          Mstd->data[i2] = 1.0 + (double)i2;
        }
      }

      w = data->data[i + 1];
      loop_ub = Mstd->size[1];
      for (i2 = 0; i2 < loop_ub; i2++) {
        base_->data[i1 + i2] = w + Mstd->data[i2] * peak_threshold;
      }

      if (2 + i > nx) {
        i1 = 0;
        nx = 0;
      } else {
        i1 = i + 1;
      }

      if (2 + i > (int)stop) {
        i2 = 0;
        i3 = 0;
      } else {
        i2 = i + 1;
        i3 = i + 1;
      }

      loop_ub = nx - i1;
      for (i4 = 0; i4 < loop_ub; i4++) {
        x_baselined->data[i3 + i4] = x->data[i1 + i4] - base_->data[i2 + i4];
      }

      peak_threshold = Baseline(x_baselined, 2.0 + (double)i, stop, x, base_);
      if (peak_threshold != 0.0) {
        w = Baseline(x_baselined, 2.0 + (double)i, peak_threshold, x, base_);
        y2 = Baseline(x_baselined, peak_threshold, stop, x, base_);
        if ((w != 0.0) && (y2 != 0.0)) {
          Baseline(x_baselined, 2.0 + (double)i, w, x, base_);
          Baseline(x_baselined, w, peak_threshold, x, base_);
          Baseline(x_baselined, peak_threshold, y2, x, base_);
          Baseline(x_baselined, y2, stop, x, base_);
        } else if (w != 0.0) {
          Baseline(x_baselined, 2.0 + (double)i, w, x, base_);
          Baseline(x_baselined, w, peak_threshold, x, base_);
        } else {
          if (y2 != 0.0) {
            Baseline(x_baselined, peak_threshold, y2, x, base_);
            Baseline(x_baselined, y2, stop, x, base_);
          }
        }
      }
    } else {
      if (c < 2.0 + (double)i) {
        base_->data[1 + i] = noise->data[1 + i];
        x_baselined->data[1 + i] = data->data[i + 1] - base_->data[1 + i];
      }
    }
  }

  emxFree_int32_T(&ii);
  emxFree_real_T(&x);

  /* baseline and noise are removed from raw data */
  loop_ub = base_->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    Base_->data[i0] = base_->data[i0];
  }

  i0 = atlas_data->size[1];
  for (i = 0; i < i0; i++) {
    if (x_baselined->data[i] < 0.0) {
      x_baselined->data[i] = 0.0;
    }
  }

  loop_ub = x_baselined->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    data_baselined_->data[i0] = x_baselined->data[i0];
  }

  loop_ub = data_baselined_->size[1];
  i0 = data_baselined->size[0] * data_baselined->size[1];
  data_baselined->size[0] = 1;
  data_baselined->size[1] = loop_ub;
  emxEnsureCapacity_real_T(data_baselined, i0);
  for (i0 = 0; i0 < loop_ub; i0++) {
    data_baselined->data[i0] = data_baselined_->data[i0];
  }

  loop_ub = Base_->size[1];
  i0 = base->size[0] * base->size[1];
  base->size[0] = 1;
  base->size[1] = loop_ub;
  emxEnsureCapacity_real_T(base, i0);
  for (i0 = 0; i0 < loop_ub; i0++) {
    base->data[i0] = Base_->data[i0];
  }

  emxFree_real_T(&Base_);

  /*     %% --------------------- 峰检�? ----------------------------------- */
  /* peak_detecte �?测data数据的谱峰，并输出所有峰�? {start, apex, end, height, width, area}信息 */
  /*    此处提供详细说明 */
  /*  data 为基线校准后的数�?(sample_num, feature_num) */
  loop_ub = data_baselined_->size[1];
  i0 = data->size[0] * data->size[1];
  data->size[0] = 1;
  data->size[1] = loop_ub;
  emxEnsureCapacity_real_T(data, i0);
  for (i0 = 0; i0 < loop_ub; i0++) {
    data->data[i0] = data_baselined_->data[i0];
  }

  loop_ub = data_baselined_->size[1];
  i0 = N->size[0] * N->size[1];
  N->size[0] = 1;
  N->size[1] = loop_ub;
  emxEnsureCapacity_boolean_T(N, i0);
  for (i0 = 0; i0 < loop_ub; i0++) {
    N->data[i0] = rtIsNaN(data_baselined_->data[i0]);
  }

  b_fi = N->size[1];
  for (i = 0; i < b_fi; i++) {
    if (N->data[i]) {
      data->data[i] = 0.0;
    }
  }

  emxFree_boolean_T(&N);
  i0 = data_baselined_->size[1];
  if (i0 < 1) {
    fi->size[0] = 1;
    fi->size[1] = 0;
  } else {
    i0 = data_baselined_->size[1];
    i1 = fi->size[0] * fi->size[1];
    fi->size[0] = 1;
    loop_ub = (int)((double)i0 - 1.0);
    fi->size[1] = loop_ub + 1;
    emxEnsureCapacity_real_T(fi, i1);
    for (i0 = 0; i0 <= loop_ub; i0++) {
      fi->data[i0] = 1.0 + (double)i0;
    }
  }

  loop_ub = data_baselined_->size[1];
  i0 = x_baselined->size[0] * x_baselined->size[1];
  x_baselined->size[0] = 1;
  x_baselined->size[1] = loop_ub;
  emxEnsureCapacity_real_T(x_baselined, i0);
  for (i0 = 0; i0 < loop_ub; i0++) {
    x_baselined->data[i0] = 0.0;
  }

  i0 = data_baselined_->size[1];
  i0 -= 5;
  for (i = 0; i <= i0; i++) {
    if (fi->data[i + 2] > fi->data[i + 3]) {
      i1 = 1;
      i2 = 0;
    } else {
      i1 = (int)fi->data[i + 2];
      i2 = (int)fi->data[i + 3];
    }

    i3 = noise->size[0] * noise->size[1];
    noise->size[0] = 1;
    loop_ub = i2 - i1;
    i2 = loop_ub + 1;
    noise->size[1] = i2;
    emxEnsureCapacity_real_T(noise, i3);
    for (i3 = 0; i3 <= loop_ub; i3++) {
      noise->data[i3] = data->data[(i1 + i3) - 1];
    }

    x_baselined->data[i + 2] = combineVectorElements(noise) / (double)i2;

    /*  对每行依次求出窗口内的均�? */
  }

  i0 = data_baselined_->size[1];
  i1 = peaks_info->size[0] * peaks_info->size[1];
  peaks_info->size[0] = i0;
  peaks_info->size[1] = 6;
  emxEnsureCapacity_real_T(peaks_info, i1);
  loop_ub = i0 * 6;
  emxFree_real_T(&data_baselined_);
  for (i0 = 0; i0 < loop_ub; i0++) {
    peaks_info->data[i0] = 0.0;
  }

  peaks_i = 0U;

  /* for each sample */
  loop_ub = x_baselined->size[1];
  i0 = noise->size[0] * noise->size[1];
  noise->size[0] = 1;
  noise->size[1] = loop_ub;
  emxEnsureCapacity_real_T(noise, i0);
  for (i0 = 0; i0 < loop_ub; i0++) {
    noise->data[i0] = x_baselined->data[i0];
  }

  diff(noise, fi);

  /*  对该行作�? */
  /*          S = [];  */
  /*          M = []; */
  i0 = Mstd->size[0] * Mstd->size[1];
  Mstd->size[0] = 1;
  Mstd->size[1] = fi->size[1];
  emxEnsureCapacity_real_T(Mstd, i0);
  loop_ub = fi->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    Mstd->data[i0] = 0.0;
  }

  i0 = base_->size[0] * base_->size[1];
  base_->size[0] = 1;
  base_->size[1] = fi->size[1];
  emxEnsureCapacity_real_T(base_, i0);
  loop_ub = fi->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    base_->data[i0] = 0.0;
  }

  S_i = 0U;
  M_i = 0U;

  /*  Determination of peak start (S), max (M) and end slut (S) */
  i0 = fi->size[1];
  for (b_i2 = 0; b_i2 <= i0 - 4; b_i2++) {
    /*  from the first to the last scan */
    if (((fi->data[b_i2 + 1] <= 0.0) && (fi->data[2 + b_i2] > 0.0)) ||
        ((fi->data[b_i2 + 1] < 0.0) && (fi->data[2 + b_i2] >= 0.0))) {
      /*  求每�?个凹点（start\end 都在凹点上） */
      S_i++;
      Mstd->data[(int)S_i - 1] = 3.0 + (double)b_i2;

      /*                  S = [S i2]; */
    }

    /*              if d(1,i2-2)>0 && d(1,i2-1)>=0 && d(1,i2)<=0 && d(1,i2+1)<0 % 求每�?个凸点（apex 在凸点上），这个取法默认取后�?个点,且有概率忽略共溶�? */
    /*  共溶峰的忽略是由于平滑窗口导致的 */
    /*  上面的检测方法同时检测四个点，会忽略紧凑的共溶峰，故改为以下的检测方�? */
    /*              if d(1,i2-1)>0 && d(1,i2)<=0 || d(1,i2-1)>=0 && d(1,i2)<0 */
    if ((fi->data[b_i2 + 1] > 0.0) && (fi->data[2 + b_i2] < 0.0)) {
      /*                  if (d(1,i2-2) < 0 && d(1,i2-2)*10+d(1,i2-1) > 0) || (d(1,i2+1) > 0 && d(1,i2)+10*d(1,i2+1) < 0) */
      /*                      continue */
      /*                  end */
      M_i++;
      base_->data[(int)M_i - 1] = 3.0 + (double)b_i2;

      /*                  M = [M i2-1]; */
    }
  }

  if (1 > (int)S_i) {
    i0 = 0;
  } else {
    i0 = (int)S_i;
  }

  i1 = Mstd->size[0] * Mstd->size[1];
  Mstd->size[1] = i0;
  emxEnsureCapacity_real_T(Mstd, i1);
  if (1 > (int)M_i) {
    i1 = 0;
  } else {
    i1 = (int)M_i;
  }

  i2 = base_->size[0] * base_->size[1];
  base_->size[1] = i1;
  emxEnsureCapacity_real_T(base_, i2);
  for (b_i2 = 0; b_i2 < i1; b_i2++) {
    /*  遍历每一个凸�? */
    peak_threshold = base_->data[b_i2];
    i2 = noise->size[0] * noise->size[1];
    noise->size[0] = 1;
    noise->size[1] = Mstd->size[1];
    emxEnsureCapacity_real_T(noise, i2);
    loop_ub = Mstd->size[0] * Mstd->size[1];
    for (i2 = 0; i2 < loop_ub; i2++) {
      noise->data[i2] = Mstd->data[i2] - peak_threshold;
    }

    b_abs(noise, fi);
    b_fi = fi->size[1];
    if (fi->size[1] <= 2) {
      if (fi->size[1] == 1) {
        idx = 1;
      } else if ((fi->data[0] > fi->data[1]) || (rtIsNaN(fi->data[0]) &&
                  (!rtIsNaN(fi->data[1])))) {
        idx = 2;
      } else {
        idx = 1;
      }
    } else {
      if (!rtIsNaN(fi->data[0])) {
        idx = 1;
      } else {
        idx = 0;
        nx = 2;
        exitg1 = false;
        while ((!exitg1) && (nx <= fi->size[1])) {
          if (!rtIsNaN(fi->data[nx - 1])) {
            idx = nx;
            exitg1 = true;
          } else {
            nx++;
          }
        }
      }

      if (idx == 0) {
        idx = 1;
      } else {
        peak_threshold = fi->data[idx - 1];
        i2 = idx + 1;
        for (nx = i2; nx <= b_fi; nx++) {
          if (peak_threshold > fi->data[nx - 1]) {
            peak_threshold = fi->data[nx - 1];
            idx = nx;
          }
        }
      }
    }

    /* start must be located before max */
    x1 = 0;
    x2 = 0;
    x3 = 0;

    /*  找到距离�?接近的凹点，并分配两边的凹点作为该凸点的start\end，边界不考虑 */
    if (((int)base_->data[b_i2] > (int)Mstd->data[idx - 1]) && (idx < i0)) {
      x1 = (int)Mstd->data[idx - 1];
      x2 = (int)base_->data[b_i2];
      x3 = (int)Mstd->data[idx];
    } else {
      if ((idx > 1) && ((int)base_->data[b_i2] < (int)Mstd->data[idx - 1])) {
        x1 = (int)Mstd->data[idx - 2];
        x2 = (int)base_->data[b_i2];
        x3 = (int)Mstd->data[idx - 1];
      }
    }

    if (x1 != 0) {
      /* peakheight at start(y1), max(y2) and end(y3) */
      /*                      y2 = (data(ii,x2) + data(ii,x2+1)) /2;  % 前面默认取最后一个点，此处取�?个均�? */
      y2 = data->data[x2 - 1];

      /*  Area */
      if (x1 > x3) {
        i2 = 1;
        i3 = 0;
      } else {
        i2 = x1;
        i3 = x3;
      }

      /*  求半峰宽，找到左右两边Y值最接近半峰高的数据点，然后左右作差得出半峰�? */
      if (x1 > x2) {
        i4 = 1;
        nx = 0;
      } else {
        i4 = x1;
        nx = x2;
      }

      peak_threshold = y2 * 0.5;
      b_fi = noise->size[0] * noise->size[1];
      noise->size[0] = 1;
      loop_ub = nx - i4;
      noise->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(noise, b_fi);
      for (nx = 0; nx <= loop_ub; nx++) {
        noise->data[nx] = data->data[(i4 + nx) - 1] - peak_threshold;
      }

      b_abs(noise, fi);
      b_fi = fi->size[1];
      if (fi->size[1] <= 2) {
        if (fi->size[1] == 1) {
          idx = 1;
        } else if ((fi->data[0] > fi->data[1]) || (rtIsNaN(fi->data[0]) &&
                    (!rtIsNaN(fi->data[1])))) {
          idx = 2;
        } else {
          idx = 1;
        }
      } else {
        if (!rtIsNaN(fi->data[0])) {
          idx = 1;
        } else {
          idx = 0;
          nx = 2;
          exitg1 = false;
          while ((!exitg1) && (nx <= fi->size[1])) {
            if (!rtIsNaN(fi->data[nx - 1])) {
              idx = nx;
              exitg1 = true;
            } else {
              nx++;
            }
          }
        }

        if (idx == 0) {
          idx = 1;
        } else {
          peak_threshold = fi->data[idx - 1];
          i4 = idx + 1;
          for (nx = i4; nx <= b_fi; nx++) {
            if (peak_threshold > fi->data[nx - 1]) {
              peak_threshold = fi->data[nx - 1];
              idx = nx;
            }
          }
        }
      }

      /* The closest point left of apex. */
      if (x2 > x3) {
        i4 = 1;
        nx = 0;
      } else {
        i4 = x2;
        nx = x3;
      }

      peak_threshold = y2 * 0.5;
      b_fi = noise->size[0] * noise->size[1];
      noise->size[0] = 1;
      loop_ub = nx - i4;
      noise->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(noise, b_fi);
      for (nx = 0; nx <= loop_ub; nx++) {
        noise->data[nx] = data->data[(i4 + nx) - 1] - peak_threshold;
      }

      b_abs(noise, fi);
      b_fi = fi->size[1];
      if (fi->size[1] <= 2) {
        if (fi->size[1] == 1) {
          i = 1;
        } else if ((fi->data[0] > fi->data[1]) || (rtIsNaN(fi->data[0]) &&
                    (!rtIsNaN(fi->data[1])))) {
          i = 2;
        } else {
          i = 1;
        }
      } else {
        if (!rtIsNaN(fi->data[0])) {
          i = 1;
        } else {
          i = 0;
          nx = 2;
          exitg1 = false;
          while ((!exitg1) && (nx <= fi->size[1])) {
            if (!rtIsNaN(fi->data[nx - 1])) {
              i = nx;
              exitg1 = true;
            } else {
              nx++;
            }
          }
        }

        if (i == 0) {
          i = 1;
        } else {
          peak_threshold = fi->data[i - 1];
          i4 = i + 1;
          for (nx = i4; nx <= b_fi; nx++) {
            if (peak_threshold > fi->data[nx - 1]) {
              peak_threshold = fi->data[nx - 1];
              i = nx;
            }
          }
        }
      }

      /* The closest point right of apex. */
      w = atlas_data->data[((x2 + i) - 1) << 1] - atlas_data->data[((x1 + idx) -
        1) << 1];

      /*  判断峰宽、峰高是否符合要�? */
      /*              if w>min_half_width && w<max_half_width && y2>min_peak_height */
      if (y2 > 4.0E-5) {
        if (x1 > x3) {
          i4 = 1;
          nx = 0;
        } else {
          i4 = x1;
          nx = x3;
        }

        b_fi = noise->size[0] * noise->size[1];
        noise->size[0] = 1;
        loop_ub = nx - i4;
        noise->size[1] = loop_ub + 1;
        emxEnsureCapacity_real_T(noise, b_fi);
        for (nx = 0; nx <= loop_ub; nx++) {
          noise->data[nx] = x_baselined->data[(i4 + nx) - 1];
        }

        peak_threshold = mean(noise);
        c = 0.0;
        i4 = x3 - x1;
        for (b_fi = 0; b_fi <= i4; b_fi++) {
          S_i = (unsigned int)x1 + b_fi;

          /*  The signal must only cross average twice */
          nx = (int)S_i - 1;
          if (((x_baselined->data[nx] < peak_threshold) && (x_baselined->data
                [(int)S_i] > peak_threshold)) || ((x_baselined->data[nx] >
                peak_threshold) && (x_baselined->data[(int)S_i] < peak_threshold)))
          {
            c++;
          }
        }

        if (c <= 4.0) {
          /*  进出各两次，因此c要小于等�?4 */
          /*                    �?测到峰，记录 */
          /*  peaks consiste of start, apex, end, height, width, area */
          peaks_i++;
          i4 = noise->size[0] * noise->size[1];
          noise->size[0] = 1;
          loop_ub = i3 - i2;
          noise->size[1] = loop_ub + 1;
          emxEnsureCapacity_real_T(noise, i4);
          for (i3 = 0; i3 <= loop_ub; i3++) {
            noise->data[i3] = data->data[(i2 + i3) - 1];
          }

          peak_threshold = trapz(noise);
          peaks_info->data[(int)peaks_i - 1] = atlas_data->data[(x1 - 1) << 1];
          peaks_info->data[((int)peaks_i + peaks_info->size[0]) - 1] =
            atlas_data->data[(x2 - 1) << 1];
          peaks_info->data[((int)peaks_i + (peaks_info->size[0] << 1)) - 1] =
            atlas_data->data[(x3 - 1) << 1];
          peaks_info->data[((int)peaks_i + peaks_info->size[0] * 3) - 1] = y2;
          peaks_info->data[((int)peaks_i + (peaks_info->size[0] << 2)) - 1] = w;
          peaks_info->data[((int)peaks_i + peaks_info->size[0] * 5) - 1] =
            peak_threshold;
        }
      }
    }
  }

  emxFree_real_T(&fi);
  emxFree_real_T(&x_baselined);
  emxFree_real_T(&base_);
  emxFree_real_T(&noise);
  emxFree_real_T(&Mstd);
  emxFree_real_T(&data);

  /* If no peaks are detected */
  if ((int)peaks_i == 0) {
    i0 = peaks_info->size[0] * peaks_info->size[1];
    peaks_info->size[0] = 1;
    peaks_info->size[1] = 6;
    emxEnsureCapacity_real_T(peaks_info, i0);
    for (i0 = 0; i0 < 6; i0++) {
      peaks_info->data[i0] = 0.0;
    }
  } else {
    emxInit_real_T(&b_peaks_info, 2);
    loop_ub = (int)peaks_i;
    i0 = b_peaks_info->size[0] * b_peaks_info->size[1];
    b_peaks_info->size[0] = (int)peaks_i;
    b_peaks_info->size[1] = 6;
    emxEnsureCapacity_real_T(b_peaks_info, i0);
    for (i0 = 0; i0 < 6; i0++) {
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_peaks_info->data[i1 + b_peaks_info->size[0] * i0] = peaks_info->
          data[i1 + peaks_info->size[0] * i0];
      }
    }

    i0 = peaks_info->size[0] * peaks_info->size[1];
    peaks_info->size[0] = b_peaks_info->size[0];
    peaks_info->size[1] = 6;
    emxEnsureCapacity_real_T(peaks_info, i0);
    loop_ub = b_peaks_info->size[0] * b_peaks_info->size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      peaks_info->data[i0] = b_peaks_info->data[i0];
    }

    emxFree_real_T(&b_peaks_info);
  }
}

/* End of code generation (data_preprocessing.c) */
