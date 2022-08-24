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
#include "data_preprocessing.h"
#include "combineVectorElements.h"
#include "data_preprocessing_emxutil.h"
#include "data_preprocessing_types.h"
#include "diff.h"
#include "find.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "std.h"
#include "trapz.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Declarations */
static double Baseline(emxArray_real_T *x_baselined, double start, double stop,
                       const emxArray_real_T *x, emxArray_real_T *base);

static void b_binary_expand_op(emxArray_real_T *x_baselined, int i1,
                               const emxArray_real_T *x, int i2, int i3,
                               const emxArray_real_T *base, int i4, int i5);

static void binary_expand_op(emxArray_real_T *x_baselined, int i1,
                             const emxArray_real_T *x, int i2, int i3,
                             const emxArray_real_T *a1, int i4, int i5);

/* Function Definitions */
static double Baseline(emxArray_real_T *x_baselined, double start, double stop,
                       const emxArray_real_T *x, emxArray_real_T *base)
{
  emxArray_boolean_T *b_x;
  emxArray_int32_T *ii;
  emxArray_real_T *c_x;
  emxArray_real_T *neg;
  const double *x_data;
  double S;
  double b;
  double b_b;
  double b_b_tmp;
  double b_tmp;
  double c_b_tmp;
  double ex;
  double *base_data;
  double *c_x_data;
  double *neg_data;
  double *x_baselined_data;
  int i;
  int i1;
  int i2;
  int idx;
  int last;
  int nx;
  int *ii_data;
  bool exitg1;
  bool *b_x_data;
  base_data = base->data;
  x_data = x->data;
  x_baselined_data = x_baselined->data;
  /*  执行数据中单个段落的对齐，该段落由start和stop来界定， */
  /*  x_baselined为处理后的数据，x为原始数据，base为基线 */
  if (start > stop) {
    i = 0;
    i1 = 0;
  } else {
    i = (int)start - 1;
    i1 = (int)stop;
  }
  emxInit_boolean_T(&b_x);
  last = b_x->size[0] * b_x->size[1];
  b_x->size[0] = 1;
  nx = i1 - i;
  b_x->size[1] = nx;
  emxEnsureCapacity_boolean_T(b_x, last);
  b_x_data = b_x->data;
  for (i1 = 0; i1 < nx; i1++) {
    b_x_data[i1] = (x_baselined_data[i + i1] < 0.0);
  }
  emxInit_int32_T(&ii);
  nx = b_x->size[1];
  idx = 0;
  i = ii->size[0] * ii->size[1];
  ii->size[0] = 1;
  ii->size[1] = b_x->size[1];
  emxEnsureCapacity_int32_T(ii, i);
  ii_data = ii->data;
  last = 0;
  exitg1 = false;
  while ((!exitg1) && (last <= nx - 1)) {
    if (b_x_data[last]) {
      idx++;
      ii_data[idx - 1] = last + 1;
      if (idx >= nx) {
        exitg1 = true;
      } else {
        last++;
      }
    } else {
      last++;
    }
  }
  if (b_x->size[1] == 1) {
    if (idx == 0) {
      ii->size[0] = 1;
      ii->size[1] = 0;
    }
  } else {
    i = ii->size[0] * ii->size[1];
    if (1 > idx) {
      ii->size[1] = 0;
    } else {
      ii->size[1] = idx;
    }
    emxEnsureCapacity_int32_T(ii, i);
    ii_data = ii->data;
  }
  emxFree_boolean_T(&b_x);
  emxInit_real_T(&neg, 2);
  i = neg->size[0] * neg->size[1];
  neg->size[0] = 1;
  neg->size[1] = ii->size[1];
  emxEnsureCapacity_real_T(neg, i);
  neg_data = neg->data;
  nx = ii->size[1];
  for (i = 0; i < nx; i++) {
    neg_data[i] = ii_data[i];
  }
  /* if there are no more than half of V1 instances below zero, the for loop
   * should terminate */
  if (neg->size[1] < 3) {
    S = 0.0;
  } else {
    emxInit_real_T(&c_x, 2);
    i = neg->size[1];
    i1 = neg->size[0] * neg->size[1];
    neg->size[1]++;
    emxEnsureCapacity_real_T(neg, i1);
    neg_data = neg->data;
    neg_data[i] = rtInf;
    /*  zeroes in Ii indicates that two consecetive valeus are below zero, 5 in
     * a row indicates 6 places below zero in a row */
    /*  Ii2是一个索引，显示非零的位置 */
    nx = neg->size[1] - 1;
    i = c_x->size[0] * c_x->size[1];
    c_x->size[0] = 1;
    c_x->size[1] = neg->size[1] - 1;
    emxEnsureCapacity_real_T(c_x, i);
    c_x_data = c_x->data;
    for (i = 0; i < nx; i++) {
      c_x_data[i] = (neg_data[i] - neg_data[i + 1]) + 1.0;
    }
    nx = c_x->size[1];
    idx = 0;
    i = ii->size[0] * ii->size[1];
    ii->size[0] = 1;
    ii->size[1] = c_x->size[1];
    emxEnsureCapacity_int32_T(ii, i);
    ii_data = ii->data;
    last = 0;
    exitg1 = false;
    while ((!exitg1) && (last <= nx - 1)) {
      if (c_x_data[last] != 0.0) {
        idx++;
        ii_data[idx - 1] = last + 1;
        if (idx >= nx) {
          exitg1 = true;
        } else {
          last++;
        }
      } else {
        last++;
      }
    }
    if (c_x->size[1] == 1) {
      if (idx == 0) {
        ii->size[0] = 1;
        ii->size[1] = 0;
      }
    } else {
      i = ii->size[0] * ii->size[1];
      if (1 > idx) {
        ii->size[1] = 0;
      } else {
        ii->size[1] = idx;
      }
      emxEnsureCapacity_int32_T(ii, i);
      ii_data = ii->data;
    }
    i = neg->size[0] * neg->size[1];
    neg->size[0] = 1;
    neg->size[1] = ii->size[1] + 1;
    emxEnsureCapacity_real_T(neg, i);
    neg_data = neg->data;
    neg_data[0] = 0.0;
    nx = ii->size[1];
    for (i = 0; i < nx; i++) {
      neg_data[i + 1] = ii_data[i];
    }
    /*  如果范围内只有一个非零 */
    if (neg->size[1] == 1) {
      if (start > stop) {
        i = 0;
        i1 = 0;
      } else {
        i = (int)start - 1;
        i1 = (int)stop;
      }
      last = neg->size[0] * neg->size[1];
      neg->size[0] = 1;
      nx = i1 - i;
      neg->size[1] = nx;
      emxEnsureCapacity_real_T(neg, last);
      neg_data = neg->data;
      for (i1 = 0; i1 < nx; i1++) {
        neg_data[i1] = x_baselined_data[i + i1];
      }
      minimum(neg, &ex, &last);
      S = ((double)last + start) - 1.0;
      ex = x_data[(int)S - 1];
      b_tmp = S - start;
      b_b_tmp = x_data[(int)(start - 1.0) - 1];
      b = (ex - b_b_tmp) / (b_tmp + 1.0);
      b_b = (x_data[(int)(stop + 1.0) - 1] - ex) / ((stop - S) + 1.0);
      if (start > S - 1.0) {
        i = 1;
      } else {
        i = (int)start;
      }
      if (rtIsNaN(b_tmp)) {
        i1 = neg->size[0] * neg->size[1];
        neg->size[0] = 1;
        neg->size[1] = 1;
        emxEnsureCapacity_real_T(neg, i1);
        neg_data = neg->data;
        neg_data[0] = rtNaN;
      } else if (b_tmp < 1.0) {
        neg->size[0] = 1;
        neg->size[1] = 0;
      } else {
        i1 = neg->size[0] * neg->size[1];
        neg->size[0] = 1;
        nx = (int)floor(b_tmp - 1.0);
        neg->size[1] = nx + 1;
        emxEnsureCapacity_real_T(neg, i1);
        neg_data = neg->data;
        for (i1 = 0; i1 <= nx; i1++) {
          neg_data[i1] = (double)i1 + 1.0;
        }
      }
      nx = neg->size[1];
      for (i1 = 0; i1 < nx; i1++) {
        base_data[(i + i1) - 1] = b_b_tmp + neg_data[i1] * b;
      }
      if (S + 1.0 > stop) {
        i = 1;
      } else {
        i = (int)(S + 1.0);
      }
      b = stop - S;
      if (rtIsNaN(b)) {
        i1 = neg->size[0] * neg->size[1];
        neg->size[0] = 1;
        neg->size[1] = 1;
        emxEnsureCapacity_real_T(neg, i1);
        neg_data = neg->data;
        neg_data[0] = rtNaN;
      } else if (b < 1.0) {
        neg->size[0] = 1;
        neg->size[1] = 0;
      } else {
        i1 = neg->size[0] * neg->size[1];
        neg->size[0] = 1;
        nx = (int)floor(b - 1.0);
        neg->size[1] = nx + 1;
        emxEnsureCapacity_real_T(neg, i1);
        neg_data = neg->data;
        for (i1 = 0; i1 <= nx; i1++) {
          neg_data[i1] = (double)i1 + 1.0;
        }
      }
      ex = x_data[(int)S - 1];
      nx = neg->size[1];
      for (i1 = 0; i1 < nx; i1++) {
        base_data[(i + i1) - 1] = ex + neg_data[i1] * b_b;
      }
      base_data[(int)S - 1] = x_data[(int)S - 1];
    } else {
      nx = neg->size[1] - 1;
      i = c_x->size[0] * c_x->size[1];
      c_x->size[0] = 1;
      c_x->size[1] = neg->size[1] - 1;
      emxEnsureCapacity_real_T(c_x, i);
      c_x_data = c_x->data;
      for (i = 0; i < nx; i++) {
        c_x_data[i] = (int)neg_data[i + 1] - (int)neg_data[i];
      }
      last = c_x->size[1];
      if (c_x->size[1] <= 2) {
        if (c_x->size[1] == 1) {
          nx = (int)c_x_data[0];
        } else if ((int)c_x_data[0] < (int)c_x_data[c_x->size[1] - 1]) {
          nx = (int)c_x_data[c_x->size[1] - 1];
        } else {
          nx = (int)c_x_data[0];
        }
      } else {
        nx = (int)c_x_data[0];
        for (idx = 2; idx <= last; idx++) {
          ex = c_x_data[idx - 1];
          if (nx < (int)ex) {
            nx = (int)ex;
          }
        }
      }
      if (nx > 3) {
        if (start > stop) {
          i = 0;
          i1 = 0;
        } else {
          i = (int)start - 1;
          i1 = (int)stop;
        }
        last = neg->size[0] * neg->size[1];
        neg->size[0] = 1;
        nx = i1 - i;
        neg->size[1] = nx;
        emxEnsureCapacity_real_T(neg, last);
        neg_data = neg->data;
        for (i1 = 0; i1 < nx; i1++) {
          neg_data[i1] = x_baselined_data[i + i1];
        }
        minimum(neg, &ex, &last);
        S = ((double)last + start) - 1.0;
        ex = x_data[(int)S - 1];
        b_tmp = S - start;
        b_b_tmp = x_data[(int)(start - 1.0) - 1];
        b = (ex - b_b_tmp) / (b_tmp + 1.0);
        c_b_tmp = stop - S;
        b_b = (x_data[(int)(stop + 1.0) - 1] - ex) / (c_b_tmp + 1.0);
        if (start > S - 1.0) {
          i = 1;
        } else {
          i = (int)start;
        }
        if (rtIsNaN(b_tmp)) {
          i1 = neg->size[0] * neg->size[1];
          neg->size[0] = 1;
          neg->size[1] = 1;
          emxEnsureCapacity_real_T(neg, i1);
          neg_data = neg->data;
          neg_data[0] = rtNaN;
        } else if (b_tmp < 1.0) {
          neg->size[0] = 1;
          neg->size[1] = 0;
        } else {
          i1 = neg->size[0] * neg->size[1];
          neg->size[0] = 1;
          nx = (int)floor(b_tmp - 1.0);
          neg->size[1] = nx + 1;
          emxEnsureCapacity_real_T(neg, i1);
          neg_data = neg->data;
          for (i1 = 0; i1 <= nx; i1++) {
            neg_data[i1] = (double)i1 + 1.0;
          }
        }
        nx = neg->size[1];
        for (i1 = 0; i1 < nx; i1++) {
          base_data[(i + i1) - 1] = b_b_tmp + neg_data[i1] * b;
        }
        if (S + 1.0 > stop) {
          i = 1;
        } else {
          i = (int)(S + 1.0);
        }
        if (rtIsNaN(c_b_tmp)) {
          i1 = neg->size[0] * neg->size[1];
          neg->size[0] = 1;
          neg->size[1] = 1;
          emxEnsureCapacity_real_T(neg, i1);
          neg_data = neg->data;
          neg_data[0] = rtNaN;
        } else if (c_b_tmp < 1.0) {
          neg->size[0] = 1;
          neg->size[1] = 0;
        } else {
          i1 = neg->size[0] * neg->size[1];
          neg->size[0] = 1;
          nx = (int)floor(c_b_tmp - 1.0);
          neg->size[1] = nx + 1;
          emxEnsureCapacity_real_T(neg, i1);
          neg_data = neg->data;
          for (i1 = 0; i1 <= nx; i1++) {
            neg_data[i1] = (double)i1 + 1.0;
          }
        }
        nx = neg->size[1];
        for (i1 = 0; i1 < nx; i1++) {
          base_data[(i + i1) - 1] = ex + neg_data[i1] * b_b;
        }
        base_data[(int)S - 1] = ex;
      } else {
        S = 0.0;
      }
    }
    emxFree_real_T(&c_x);
    if (start > stop) {
      i = 0;
      i1 = 0;
      last = 0;
      idx = 0;
      i2 = 0;
    } else {
      i = (int)start - 1;
      i1 = (int)stop;
      last = (int)start - 1;
      idx = (int)stop;
      i2 = (int)start - 1;
    }
    nx = i1 - i;
    if (nx == idx - last) {
      for (i1 = 0; i1 < nx; i1++) {
        x_baselined_data[i2 + i1] = x_data[i + i1] - base_data[last + i1];
      }
    } else {
      b_binary_expand_op(x_baselined, i2, x, i, i1 - 1, base, last, idx - 1);
    }
  }
  emxFree_int32_T(&ii);
  emxFree_real_T(&neg);
  return S;
}

static void b_binary_expand_op(emxArray_real_T *x_baselined, int i1,
                               const emxArray_real_T *x, int i2, int i3,
                               const emxArray_real_T *base, int i4, int i5)
{
  const double *base_data;
  const double *x_data;
  double *x_baselined_data;
  int i;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  base_data = base->data;
  x_data = x->data;
  x_baselined_data = x_baselined->data;
  stride_0_1 = ((i3 - i2) + 1 != 1);
  stride_1_1 = ((i5 - i4) + 1 != 1);
  if ((i5 - i4) + 1 == 1) {
    loop_ub = (i3 - i2) + 1;
  } else {
    loop_ub = (i5 - i4) + 1;
  }
  for (i = 0; i < loop_ub; i++) {
    x_baselined_data[i1 + i] =
        x_data[i2 + i * stride_0_1] - base_data[i4 + i * stride_1_1];
  }
}

static void binary_expand_op(emxArray_real_T *x_baselined, int i1,
                             const emxArray_real_T *x, int i2, int i3,
                             const emxArray_real_T *a1, int i4, int i5)
{
  const double *a1_data;
  const double *x_data;
  double *x_baselined_data;
  int i;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  a1_data = a1->data;
  x_data = x->data;
  x_baselined_data = x_baselined->data;
  stride_0_1 = (i3 - i2 != 1);
  stride_1_1 = (i5 - i4 != 1);
  if (i5 - i4 == 1) {
    loop_ub = i3 - i2;
  } else {
    loop_ub = i5 - i4;
  }
  for (i = 0; i < loop_ub; i++) {
    x_baselined_data[(i1 + i) + 1] =
        x_data[(i2 + i * stride_0_1) + 1] - a1_data[(i4 + i * stride_1_1) + 1];
  }
}

void data_preprocessing(const emxArray_real_T *atlas_data,
                        emxArray_real_T *data_baselined, emxArray_real_T *base,
                        emxArray_real_T *peaks_info)
{
  emxArray_boolean_T *N;
  emxArray_real_T *Base_;
  emxArray_real_T *Sx;
  emxArray_real_T *a1;
  emxArray_real_T *b_Sx;
  emxArray_real_T *b_data;
  emxArray_real_T *data;
  emxArray_real_T *data_baselined_;
  emxArray_real_T *noise;
  emxArray_real_T *x;
  emxArray_real_T *x_baselined;
  const double *atlas_data_data;
  double A;
  double S3;
  double c;
  double min_peak_height;
  double peak_threshold;
  double stop_data;
  double *Base__data;
  double *Sx_data;
  double *a1_data;
  double *b_data_data;
  double *data_baselined__data;
  double *data_baselined_data;
  double *data_data;
  double *x_baselined_data;
  double *x_data;
  int tmp_size[2];
  unsigned int M_i;
  unsigned int S_i;
  int b_i;
  int b_i2;
  int i;
  int i1;
  int i2;
  int i3;
  int i4;
  int k;
  int loop_ub;
  int nx;
  unsigned int peaks_i;
  int x1;
  int x2;
  int x3;
  bool *N_data;
  atlas_data_data = atlas_data->data;
  emxInit_real_T(&data, 2);
  /*  对传入的二维数据data执行平滑、基线校准，并输出为data_baselined,
   * base为确定的基线 */
  /*    此处显示详细说明 */
  /*  smooth_window, noise_window最好为偶数 */
  /*  peak_threshold = 8000，smooth_window=4，noise_window=6 */
  /*  输入 data ：(time_series; feature_num) */
  /*  输出 data_baselined ：(feature_num) */
  /*  输出 base : (feature_num) */
  /*  --------------------- 要自动化处理的参数
   * ------------------------------------- */
  /*      peak_threshold = 0.004; */
  /*      min_peak_height = 0.01;  */
  /*  -------------------------------------------------------------------------------
   */
  /* Smoothing (moving average) */
  loop_ub = atlas_data->size[1];
  i = data->size[0] * data->size[1];
  data->size[0] = 1;
  data->size[1] = atlas_data->size[1];
  emxEnsureCapacity_real_T(data, i);
  data_data = data->data;
  for (i = 0; i < loop_ub; i++) {
    data_data[i] = atlas_data_data[2 * i + 1];
  }
  emxInit_real_T(&a1, 2);
  a1_data = a1->data;
  if (atlas_data->size[1] < 1) {
    a1->size[0] = 1;
    a1->size[1] = 0;
  } else {
    i = a1->size[0] * a1->size[1];
    a1->size[0] = 1;
    a1->size[1] = atlas_data->size[1];
    emxEnsureCapacity_real_T(a1, i);
    a1_data = a1->data;
    loop_ub = atlas_data->size[1] - 1;
    for (i = 0; i <= loop_ub; i++) {
      a1_data[i] = (double)i + 1.0;
    }
  }
  emxInit_real_T(&Sx, 1);
  loop_ub = atlas_data->size[1];
  i = Sx->size[0];
  Sx->size[0] = atlas_data->size[1];
  emxEnsureCapacity_real_T(Sx, i);
  Sx_data = Sx->data;
  for (i = 0; i < loop_ub; i++) {
    Sx_data[i] = 0.0;
  }
  /* assignin('base','vv',vv); */
  /* assignin('base','m1',m1); */
  /*  assignin('base','iv',iv); */
  i = atlas_data->size[1] - 2;
  emxInit_real_T(&b_data, 2);
  for (b_i = 0; b_i <= i; b_i++) {
    S3 = a1_data[b_i];
    peak_threshold = a1_data[b_i + 1];
    if (S3 > peak_threshold) {
      i1 = -1;
      i2 = -1;
    } else {
      i1 = (int)S3 - 2;
      i2 = (int)peak_threshold - 1;
    }
    i3 = b_data->size[0] * b_data->size[1];
    b_data->size[0] = 1;
    loop_ub = i2 - i1;
    b_data->size[1] = loop_ub;
    emxEnsureCapacity_real_T(b_data, i3);
    b_data_data = b_data->data;
    for (i2 = 0; i2 < loop_ub; i2++) {
      b_data_data[i2] = data_data[(i1 + i2) + 1];
    }
    Sx_data[b_i + 1] = combineVectorElements(b_data) / (double)loop_ub;
  }
  emxInit_real_T(&data_baselined_, 2);
  loop_ub = atlas_data->size[1];
  i = data_baselined_->size[0] * data_baselined_->size[1];
  data_baselined_->size[0] = 1;
  data_baselined_->size[1] = atlas_data->size[1];
  emxEnsureCapacity_real_T(data_baselined_, i);
  data_baselined__data = data_baselined_->data;
  for (i = 0; i < loop_ub; i++) {
    data_baselined__data[i] = 0.0;
  }
  emxInit_real_T(&Base_, 2);
  loop_ub = atlas_data->size[1];
  i = Base_->size[0] * Base_->size[1];
  Base_->size[0] = 1;
  Base_->size[1] = atlas_data->size[1];
  emxEnsureCapacity_real_T(Base_, i);
  Base__data = Base_->data;
  for (i = 0; i < loop_ub; i++) {
    Base__data[i] = 0.0;
  }
  emxInit_real_T(&x, 2);
  /* from sample 1 to n1 */
  loop_ub = atlas_data->size[1] - 1;
  i = x->size[0] * x->size[1];
  x->size[0] = 1;
  x->size[1] = atlas_data->size[1];
  emxEnsureCapacity_real_T(x, i);
  x_data = x->data;
  for (i = 0; i <= loop_ub; i++) {
    x_data[i] = atlas_data_data[2 * i + 1];
  }
  loop_ub = atlas_data->size[1];
  i = a1->size[0] * a1->size[1];
  a1->size[0] = 1;
  a1->size[1] = atlas_data->size[1];
  emxEnsureCapacity_real_T(a1, i);
  a1_data = a1->data;
  for (i = 0; i < loop_ub; i++) {
    a1_data[i] = 0.0;
  }
  i = atlas_data->size[1] - 9;
  emxInit_real_T(&b_Sx, 1);
  for (b_i = 0; b_i <= i; b_i++) {
    i1 = b_Sx->size[0];
    b_Sx->size[0] = 8;
    emxEnsureCapacity_real_T(b_Sx, i1);
    data_baselined_data = b_Sx->data;
    for (i1 = 0; i1 < 8; i1++) {
      data_baselined_data[i1] = Sx_data[b_i + i1];
    }
    a1_data[b_i] = b_std(b_Sx);
  }
  emxFree_real_T(&b_Sx);
  emxFree_real_T(&Sx);
  peak_threshold = combineVectorElements(a1) / (double)a1->size[1] / 10.0;
  min_peak_height = peak_threshold * 2.5;
  /* Noiese is separated from peaks by making a matrix only containing noise: */
  if (1 > atlas_data->size[1]) {
    loop_ub = -1;
  } else {
    loop_ub = atlas_data->size[1] - 1;
  }
  emxInit_real_T(&noise, 2);
  i = noise->size[0] * noise->size[1];
  noise->size[0] = 1;
  noise->size[1] = loop_ub + 1;
  emxEnsureCapacity_real_T(noise, i);
  Sx_data = noise->data;
  for (i = 0; i <= loop_ub; i++) {
    Sx_data[i] = atlas_data_data[2 * i + 1];
  }
  i = atlas_data->size[1] - 6;
  for (b_i = 0; b_i <= i; b_i++) {
    if ((a1_data[b_i + 5] < peak_threshold) &&
        (a1_data[b_i] < peak_threshold)) {
      S3 = data_data[b_i + 5];
      if (S3 < 5.0E+8) {
        Sx_data[b_i + 5] = S3;
      } else {
        Sx_data[b_i + 5] = rtNaN;
      }
    } else {
      Sx_data[b_i + 5] = rtNaN;
    }
  }
  loop_ub = atlas_data->size[1] - 1;
  i = a1->size[0] * a1->size[1];
  a1->size[0] = 1;
  a1->size[1] = atlas_data->size[1];
  emxEnsureCapacity_real_T(a1, i);
  a1_data = a1->data;
  for (i = 0; i <= loop_ub; i++) {
    a1_data[i] = atlas_data_data[2 * i + 1];
  }
  emxInit_real_T(&x_baselined, 2);
  /* The baseline is estimated as straight line from start to stop of intervals:
   */
  loop_ub = atlas_data->size[1];
  i = x_baselined->size[0] * x_baselined->size[1];
  x_baselined->size[0] = 1;
  x_baselined->size[1] = atlas_data->size[1];
  emxEnsureCapacity_real_T(x_baselined, i);
  x_baselined_data = x_baselined->data;
  for (i = 0; i < loop_ub; i++) {
    x_baselined_data[i] = 0.0;
  }
  emxInit_boolean_T(&N);
  i = N->size[0] * N->size[1];
  N->size[0] = 1;
  N->size[1] = noise->size[1];
  emxEnsureCapacity_boolean_T(N, i);
  N_data = N->data;
  loop_ub = noise->size[1];
  for (i = 0; i < loop_ub; i++) {
    N_data[i] = rtIsNaN(Sx_data[i]);
  }
  c = 0.0;
  i = N->size[1];
  for (b_i = 0; b_i <= i - 2; b_i++) {
    if ((!N_data[b_i]) && N_data[b_i + 1] && (c <= (double)b_i + 2.0)) {
      if (b_i + 2 > N->size[1]) {
        i1 = 0;
        i2 = 0;
      } else {
        i1 = b_i + 1;
        i2 = N->size[1];
      }
      i3 = b_data->size[0] * b_data->size[1];
      b_data->size[0] = 1;
      loop_ub = i2 - i1;
      b_data->size[1] = loop_ub;
      emxEnsureCapacity_real_T(b_data, i3);
      b_data_data = b_data->data;
      for (i2 = 0; i2 < loop_ub; i2++) {
        b_data_data[i2] = (double)N_data[i1 + i2] - 1.0;
      }
      eml_find(b_data, (int *)&nx, tmp_size);
      loop_ub = tmp_size[1];
      for (i1 = 0; i1 < loop_ub; i1++) {
        stop_data = ((double)nx + ((double)b_i + 2.0)) - 2.0;
      }
      c = stop_data + 1.0;
      peak_threshold = (stop_data - ((double)b_i + 2.0)) + 1.0;
      A = (data_data[(int)(stop_data + 1.0) - 1] - data_data[b_i]) /
          peak_threshold;
      if ((double)b_i + 2.0 > stop_data) {
        i1 = 0;
      } else {
        i1 = b_i + 1;
      }
      if (peak_threshold < 1.0) {
        b_data->size[0] = 1;
        b_data->size[1] = 0;
      } else {
        i2 = b_data->size[0] * b_data->size[1];
        b_data->size[0] = 1;
        b_data->size[1] = (int)(peak_threshold - 1.0) + 1;
        emxEnsureCapacity_real_T(b_data, i2);
        b_data_data = b_data->data;
        loop_ub = (int)(peak_threshold - 1.0);
        for (i2 = 0; i2 <= loop_ub; i2++) {
          b_data_data[i2] = (double)i2 + 1.0;
        }
      }
      peak_threshold = data_data[b_i + 1];
      loop_ub = b_data->size[1];
      for (i2 = 0; i2 < loop_ub; i2++) {
        a1_data[i1 + i2] = peak_threshold + b_data_data[i2] * A;
      }
      if ((double)b_i + 2.0 > stop_data) {
        i1 = 0;
        i2 = 0;
        i3 = 0;
        i4 = 0;
        k = -1;
      } else {
        i1 = b_i + 1;
        i2 = (int)stop_data;
        i3 = b_i + 1;
        i4 = (int)stop_data;
        k = b_i;
      }
      loop_ub = i2 - i1;
      if (loop_ub == i4 - i3) {
        for (i2 = 0; i2 < loop_ub; i2++) {
          x_baselined_data[(k + i2) + 1] = x_data[i1 + i2] - a1_data[i3 + i2];
        }
      } else {
        binary_expand_op(x_baselined, k, x, i1 - 1, i2 - 1, a1, i3 - 1, i4 - 1);
      }
      peak_threshold =
          Baseline(x_baselined, (double)b_i + 2.0, stop_data, x, a1);
      a1_data = a1->data;
      x_baselined_data = x_baselined->data;
      if (peak_threshold != 0.0) {
        A = Baseline(x_baselined, (double)b_i + 2.0, peak_threshold, x, a1);
        S3 = Baseline(x_baselined, peak_threshold, stop_data, x, a1);
        a1_data = a1->data;
        x_baselined_data = x_baselined->data;
        if ((A != 0.0) && (S3 != 0.0)) {
          Baseline(x_baselined, (double)b_i + 2.0, A, x, a1);
          Baseline(x_baselined, A, peak_threshold, x, a1);
          Baseline(x_baselined, peak_threshold, S3, x, a1);
          Baseline(x_baselined, S3, stop_data, x, a1);
          a1_data = a1->data;
          x_baselined_data = x_baselined->data;
        } else if (A != 0.0) {
          Baseline(x_baselined, (double)b_i + 2.0, A, x, a1);
          Baseline(x_baselined, A, peak_threshold, x, a1);
          a1_data = a1->data;
          x_baselined_data = x_baselined->data;
        } else if (S3 != 0.0) {
          Baseline(x_baselined, peak_threshold, S3, x, a1);
          Baseline(x_baselined, S3, stop_data, x, a1);
          a1_data = a1->data;
          x_baselined_data = x_baselined->data;
        }
      }
    } else if (c < (double)b_i + 2.0) {
      a1_data[b_i + 1] = Sx_data[b_i + 1];
      x_baselined_data[b_i + 1] = data_data[b_i + 1] - a1_data[b_i + 1];
    }
  }
  /* baseline and noise are removed from raw data */
  loop_ub = a1->size[1];
  for (i = 0; i < loop_ub; i++) {
    Base__data[i] = a1_data[i];
  }
  i = atlas_data->size[1] - 1;
  for (b_i = 0; b_i <= i; b_i++) {
    if (x_baselined_data[b_i] < 0.0) {
      x_baselined_data[b_i] = 0.0;
    }
  }
  loop_ub = x_baselined->size[1];
  for (i = 0; i < loop_ub; i++) {
    data_baselined__data[i] = x_baselined_data[i];
  }
  loop_ub = data_baselined_->size[1];
  i = data_baselined->size[0] * data_baselined->size[1];
  data_baselined->size[0] = 1;
  data_baselined->size[1] = data_baselined_->size[1];
  emxEnsureCapacity_real_T(data_baselined, i);
  data_baselined_data = data_baselined->data;
  for (i = 0; i < loop_ub; i++) {
    data_baselined_data[i] = data_baselined__data[i];
  }
  loop_ub = Base_->size[1];
  i = base->size[0] * base->size[1];
  base->size[0] = 1;
  base->size[1] = Base_->size[1];
  emxEnsureCapacity_real_T(base, i);
  data_baselined_data = base->data;
  for (i = 0; i < loop_ub; i++) {
    data_baselined_data[i] = Base__data[i];
  }
  /*     %% --------------------- 峰检测 ----------------------------------- */
  /* peak_detecte 检测data数据的谱峰，并输出所有峰的 {start, apex, end, height,
   * width, area}信息 */
  /*    此处提供详细说明 */
  /*  data 为基线校准后的数据(sample_num, feature_num) */
  loop_ub = data_baselined_->size[1];
  i = data->size[0] * data->size[1];
  data->size[0] = 1;
  data->size[1] = data_baselined_->size[1];
  emxEnsureCapacity_real_T(data, i);
  data_data = data->data;
  for (i = 0; i < loop_ub; i++) {
    data_data[i] = data_baselined__data[i];
  }
  loop_ub = data_baselined_->size[1];
  i = N->size[0] * N->size[1];
  N->size[0] = 1;
  N->size[1] = data_baselined_->size[1];
  emxEnsureCapacity_boolean_T(N, i);
  N_data = N->data;
  for (i = 0; i < loop_ub; i++) {
    N_data[i] = rtIsNaN(data_baselined__data[i]);
  }
  nx = N->size[1];
  for (b_i = 0; b_i < nx; b_i++) {
    if (N_data[b_i]) {
      data_data[b_i] = 0.0;
    }
  }
  emxFree_boolean_T(&N);
  if (data_baselined_->size[1] < 1) {
    a1->size[0] = 1;
    a1->size[1] = 0;
  } else {
    i = a1->size[0] * a1->size[1];
    a1->size[0] = 1;
    a1->size[1] = data_baselined_->size[1];
    emxEnsureCapacity_real_T(a1, i);
    a1_data = a1->data;
    loop_ub = data_baselined_->size[1] - 1;
    for (i = 0; i <= loop_ub; i++) {
      a1_data[i] = (double)i + 1.0;
    }
  }
  loop_ub = data_baselined_->size[1];
  i = Base_->size[0] * Base_->size[1];
  Base_->size[0] = 1;
  Base_->size[1] = data_baselined_->size[1];
  emxEnsureCapacity_real_T(Base_, i);
  Base__data = Base_->data;
  for (i = 0; i < loop_ub; i++) {
    Base__data[i] = 0.0;
  }
  i = data_baselined_->size[1] - 2;
  for (b_i = 0; b_i <= i; b_i++) {
    S3 = a1_data[b_i + 1];
    i1 = b_data->size[0] * b_data->size[1];
    b_data->size[0] = 1;
    b_data->size[1] = 1;
    emxEnsureCapacity_real_T(b_data, i1);
    b_data_data = b_data->data;
    b_data_data[0] = data_data[(int)S3 - 1];
    Base__data[b_i + 1] = combineVectorElements(b_data);
    /*  对每行依次求出窗口内的均值 */
  }
  i = peaks_info->size[0] * peaks_info->size[1];
  peaks_info->size[0] = data_baselined_->size[1];
  peaks_info->size[1] = 6;
  emxEnsureCapacity_real_T(peaks_info, i);
  data_baselined_data = peaks_info->data;
  loop_ub = data_baselined_->size[1] * 6;
  emxFree_real_T(&data_baselined_);
  for (i = 0; i < loop_ub; i++) {
    data_baselined_data[i] = 0.0;
  }
  peaks_i = 0U;
  /* for each sample */
  loop_ub = Base_->size[1];
  i = b_data->size[0] * b_data->size[1];
  b_data->size[0] = 1;
  b_data->size[1] = Base_->size[1];
  emxEnsureCapacity_real_T(b_data, i);
  b_data_data = b_data->data;
  for (i = 0; i < loop_ub; i++) {
    b_data_data[i] = Base__data[i];
  }
  diff(b_data, a1);
  a1_data = a1->data;
  /*  对该行作差 */
  /*          S = [];  */
  /*          M = []; */
  i = x_baselined->size[0] * x_baselined->size[1];
  x_baselined->size[0] = 1;
  x_baselined->size[1] = a1->size[1];
  emxEnsureCapacity_real_T(x_baselined, i);
  x_baselined_data = x_baselined->data;
  loop_ub = a1->size[1];
  for (i = 0; i < loop_ub; i++) {
    x_baselined_data[i] = 0.0;
  }
  i = noise->size[0] * noise->size[1];
  noise->size[0] = 1;
  noise->size[1] = a1->size[1];
  emxEnsureCapacity_real_T(noise, i);
  Sx_data = noise->data;
  loop_ub = a1->size[1];
  for (i = 0; i < loop_ub; i++) {
    Sx_data[i] = 0.0;
  }
  S_i = 0U;
  M_i = 0U;
  /*  Determination of peak start (S), max (M) and end slut (S) */
  i = a1->size[1];
  for (b_i2 = 0; b_i2 <= i - 3; b_i2++) {
    /*  from the first to the last scan */
    S3 = a1_data[b_i2 + 1];
    if (((S3 <= 0.0) && (a1_data[b_i2 + 2] > 0.0)) ||
        ((S3 < 0.0) && (a1_data[b_i2 + 2] >= 0.0))) {
      /*  求每一个凹点（start\end 都在凹点上） */
      S_i++;
      x_baselined_data[(int)S_i - 1] = (double)b_i2 + 3.0;
      /*                  S = [S i2]; */
    }
    if ((a1_data[b_i2] > 0.0) && (S3 >= 0.0) && (a1_data[b_i2 + 2] <= 0.0) &&
        (a1_data[b_i2 + 3] < 0.0)) {
      /*  求每一个凸点（apex
       * 在凸点上），这个取法默认取后一个点,且有概率忽略共溶峰 */
      /*  共溶峰的忽略是由于平滑窗口导致的 */
      /*  上面的检测方法同时检测四个点，会忽略紧凑的共溶峰，故改为以下的检测方法
       */
      /*              if d(1,i2-1)>0 && d(1,i2)<=0 || d(1,i2-1)>=0 && d(1,i2)<0
       */
      M_i++;
      Sx_data[(int)M_i - 1] = (double)b_i2 + 3.0;
      /*                  M = [M i2-1]; */
    }
  }
  emxFree_real_T(&a1);
  if (1 > (int)S_i) {
    loop_ub = 0;
  } else {
    loop_ub = (int)S_i;
  }
  i = x_baselined->size[0] * x_baselined->size[1];
  x_baselined->size[1] = loop_ub;
  emxEnsureCapacity_real_T(x_baselined, i);
  x_baselined_data = x_baselined->data;
  if (1 > (int)M_i) {
    i = 0;
  } else {
    i = (int)M_i;
  }
  i1 = noise->size[0] * noise->size[1];
  noise->size[1] = i;
  emxEnsureCapacity_real_T(noise, i1);
  Sx_data = noise->data;
  for (b_i2 = 0; b_i2 < i; b_i2++) {
    /*  遍历每一个凸点 */
    i1 = x->size[0] * x->size[1];
    x->size[0] = 1;
    x->size[1] = loop_ub;
    emxEnsureCapacity_real_T(x, i1);
    x_data = x->data;
    peak_threshold = Sx_data[b_i2];
    for (i1 = 0; i1 < loop_ub; i1++) {
      x_data[i1] = x_baselined_data[i1] - peak_threshold;
    }
    nx = x->size[1];
    i1 = b_data->size[0] * b_data->size[1];
    b_data->size[0] = 1;
    b_data->size[1] = x->size[1];
    emxEnsureCapacity_real_T(b_data, i1);
    b_data_data = b_data->data;
    for (k = 0; k < nx; k++) {
      b_data_data[k] = fabs((double)(int)x_data[k]);
    }
    minimum(b_data, &peak_threshold, &b_i);
    /* start must be located before max */
    x1 = 0;
    x2 = 0;
    x3 = 0;
    /*  找到距离最接近的凹点，并分配两边的凹点作为该凸点的start\end，边界不考虑
     */
    S3 = Sx_data[b_i2];
    i1 = (int)(unsigned int)x_baselined_data[b_i - 1];
    if (((int)S3 > i1) && (b_i < loop_ub)) {
      x1 = i1;
      x2 = (int)S3;
      x3 = (int)(unsigned int)x_baselined_data[b_i];
    } else if ((b_i > 1) && ((int)S3 < i1)) {
      x1 = (int)(unsigned int)x_baselined_data[b_i - 2];
      x2 = (int)S3;
      x3 = i1;
    }
    if (x1 != 0) {
      /* peakheight at start(y1), max(y2) and end(y3) */
      /*                      y2 = (data(ii,x2) + data(ii,x2+1)) /2;  %
       * 前面默认取最后一个点，此处取一个均值 */
      stop_data = data_data[x2 - 1];
      /*  Area */
      if (x1 > x3) {
        i1 = 0;
        i2 = 0;
      } else {
        i1 = x1 - 1;
        i2 = x3;
      }
      /*  求半峰宽，找到左右两边Y值最接近半峰高的数据点，然后左右作差得出半峰宽
       */
      if (x1 > x2) {
        i3 = 0;
        i4 = 0;
      } else {
        i3 = x1 - 1;
        i4 = x2;
      }
      A = stop_data * 0.5;
      k = x->size[0] * x->size[1];
      x->size[0] = 1;
      nx = i4 - i3;
      x->size[1] = nx;
      emxEnsureCapacity_real_T(x, k);
      x_data = x->data;
      for (i4 = 0; i4 < nx; i4++) {
        x_data[i4] = data_data[i3 + i4] - A;
      }
      nx = x->size[1];
      i3 = b_data->size[0] * b_data->size[1];
      b_data->size[0] = 1;
      b_data->size[1] = x->size[1];
      emxEnsureCapacity_real_T(b_data, i3);
      b_data_data = b_data->data;
      for (k = 0; k < nx; k++) {
        b_data_data[k] = fabs(x_data[k]);
      }
      minimum(b_data, &peak_threshold, &b_i);
      /* The closest point left of apex. */
      if (x2 > x3) {
        i3 = 0;
        i4 = 0;
      } else {
        i3 = x2 - 1;
        i4 = x3;
      }
      k = x->size[0] * x->size[1];
      x->size[0] = 1;
      nx = i4 - i3;
      x->size[1] = nx;
      emxEnsureCapacity_real_T(x, k);
      x_data = x->data;
      for (i4 = 0; i4 < nx; i4++) {
        x_data[i4] = data_data[i3 + i4] - A;
      }
      nx = x->size[1];
      i3 = b_data->size[0] * b_data->size[1];
      b_data->size[0] = 1;
      b_data->size[1] = x->size[1];
      emxEnsureCapacity_real_T(b_data, i3);
      b_data_data = b_data->data;
      for (k = 0; k < nx; k++) {
        b_data_data[k] = fabs(x_data[k]);
      }
      minimum(b_data, &peak_threshold, &nx);
      /* The closest point right of apex. */
      peak_threshold = atlas_data_data[2 * ((x2 + nx) - 1)] -
                       atlas_data_data[2 * ((x1 + b_i) - 1)];
      /*  判断峰宽、峰高是否符合要求 */
      if ((peak_threshold > 0.01) && (peak_threshold < 10.0) &&
          (stop_data > min_peak_height)) {
        if (x1 > x3) {
          i3 = -1;
          i4 = -1;
        } else {
          i3 = x1 - 2;
          i4 = x3 - 1;
        }
        k = b_data->size[0] * b_data->size[1];
        b_data->size[0] = 1;
        nx = i4 - i3;
        b_data->size[1] = nx;
        emxEnsureCapacity_real_T(b_data, k);
        b_data_data = b_data->data;
        for (i4 = 0; i4 < nx; i4++) {
          b_data_data[i4] = Base__data[(i3 + i4) + 1];
        }
        A = combineVectorElements(b_data) / (double)nx;
        c = 0.0;
        i3 = x3 - x1;
        for (nx = 0; nx <= i3; nx++) {
          S_i = (unsigned int)x1 + nx;
          /*  The signal must only cross average twice */
          S3 = Base__data[(int)S_i - 1];
          if (((S3 < A) && (Base__data[(int)S_i] > A)) ||
              ((S3 > A) && (Base__data[(int)S_i] < A))) {
            c++;
          }
        }
        if (c <= 4.0) {
          /*  进出各两次，因此c要小于等于4 */
          /*                    检测到峰，记录 */
          /*  peaks consiste of start, apex, end, height, width, area */
          peaks_i++;
          i3 = b_data->size[0] * b_data->size[1];
          b_data->size[0] = 1;
          nx = i2 - i1;
          b_data->size[1] = nx;
          emxEnsureCapacity_real_T(b_data, i3);
          b_data_data = b_data->data;
          for (i2 = 0; i2 < nx; i2++) {
            b_data_data[i2] = data_data[i1 + i2];
          }
          data_baselined_data[(int)peaks_i - 1] = atlas_data_data[2 * (x1 - 1)];
          data_baselined_data[((int)peaks_i + peaks_info->size[0]) - 1] =
              atlas_data_data[2 * (x2 - 1)];
          data_baselined_data[((int)peaks_i + peaks_info->size[0] * 2) - 1] =
              atlas_data_data[2 * (x3 - 1)];
          data_baselined_data[((int)peaks_i + peaks_info->size[0] * 3) - 1] =
              stop_data;
          data_baselined_data[((int)peaks_i + peaks_info->size[0] * 4) - 1] =
              peak_threshold;
          data_baselined_data[((int)peaks_i + peaks_info->size[0] * 5) - 1] =
              trapz(b_data);
        }
      }
    }
  }
  emxFree_real_T(&b_data);
  emxFree_real_T(&x_baselined);
  emxFree_real_T(&noise);
  emxFree_real_T(&x);
  emxFree_real_T(&Base_);
  emxFree_real_T(&data);
  /* If no peaks are detected */
  if ((int)peaks_i == 0) {
    i = peaks_info->size[0] * peaks_info->size[1];
    peaks_info->size[0] = 1;
    peaks_info->size[1] = 6;
    emxEnsureCapacity_real_T(peaks_info, i);
    data_baselined_data = peaks_info->data;
    for (i = 0; i < 6; i++) {
      data_baselined_data[i] = 0.0;
    }
  } else {
    loop_ub = (int)peaks_i;
    for (i = 0; i < 6; i++) {
      for (i1 = 0; i1 < loop_ub; i1++) {
        data_baselined_data[i1 + (int)peaks_i * i] =
            data_baselined_data[i1 + peaks_info->size[0] * i];
      }
    }
    i = peaks_info->size[0] * peaks_info->size[1];
    peaks_info->size[0] = (int)peaks_i;
    peaks_info->size[1] = 6;
    emxEnsureCapacity_real_T(peaks_info, i);
  }
}

/* End of code generation (data_preprocessing.c) */
