/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * data_baseline.c
 *
 * Code generation for function 'data_baseline'
 *
 */

/* Include files */
#include "data_baseline.h"
#include "data_baseline_emxutil.h"
#include "data_baseline_types.h"

/* Function Definitions */
void data_baseline(const emxArray_real_T *data, int peak_threshold,
                   int smooth_window, int noise_window,
                   emxArray_real_T *data_baselined, emxArray_real_T *base)
{
  emxArray_real_T *Base_;
  emxArray_uint32_T *a1;
  const double *data_data;
  double x;
  double *Base__data;
  double *data_baselined_data;
  int i;
  int loop_ub;
  unsigned int *a1_data;
  (void)peak_threshold;
  (void)smooth_window;
  (void)noise_window;
  data_data = data->data;
  emxInit_uint32_T(&a1);
  /*  对传入的二维数据data执行平滑、基线校准，并输出为data_baselined,
   * base为确定的基线 */
  /*    此处显示详细说明 */
  /*  smooth_window, noise_window最好为偶数 */
  /*  peak_threshold = 8000，smooth_window=4，noise_window=6 */
  /*  输入 data ：(1, feature_num) */
  /*  输出 data_baselined ：(feature_num) */
  /*  输出 base : (feature_num) */
  /* Smoothing (moving average) */
  /* assignin('base','vv',vv); */
  /* assignin('base','m1',m1); */
  /*  assignin('base','iv',iv); */
  i = a1->size[0] * a1->size[1];
  a1->size[0] = 1;
  a1->size[1] = data->size[1];
  emxEnsureCapacity_uint32_T(a1, i);
  a1_data = a1->data;
  loop_ub = data->size[1];
  for (i = 0; i < loop_ub; i++) {
    a1_data[i] = 0U;
  }
  emxInit_real_T(&Base_, 2);
  i = Base_->size[0] * Base_->size[1];
  Base_->size[0] = 1;
  Base_->size[1] = data->size[1];
  emxEnsureCapacity_real_T(Base_, i);
  Base__data = Base_->data;
  loop_ub = data->size[1];
  for (i = 0; i < loop_ub; i++) {
    Base__data[i] = 0.0;
  }
  /* from sample 1 to n1 */
  x = data_data[0];
  /* Noiese is separated from peaks by making a matrix only containing noise: */
  /* The baseline is estimated as straight line from start to stop of intervals:
   */
  /* baseline and noise are removed from raw data */
  loop_ub = data->size[1];
  for (i = 0; i < loop_ub; i++) {
    Base__data[i] = x;
  }
  loop_ub = data->size[1];
  for (i = 0; i < loop_ub; i++) {
    a1_data[i] = 0U;
  }
  loop_ub = a1->size[1];
  i = data_baselined->size[0] * data_baselined->size[1];
  data_baselined->size[0] = 1;
  data_baselined->size[1] = a1->size[1];
  emxEnsureCapacity_real_T(data_baselined, i);
  data_baselined_data = data_baselined->data;
  emxFree_uint32_T(&a1);
  for (i = 0; i < loop_ub; i++) {
    data_baselined_data[i] = 0.0;
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
  emxFree_real_T(&Base_);
}

/* End of code generation (data_baseline.c) */
