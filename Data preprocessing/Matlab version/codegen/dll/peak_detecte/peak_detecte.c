/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * peak_detecte.c
 *
 * Code generation for function 'peak_detecte'
 *
 */

/* Include files */
#include "peak_detecte.h"
#include "combineVectorElements.h"
#include "minOrMax.h"
#include "peak_detecte_emxutil.h"
#include "peak_detecte_types.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
void peak_detecte(emxArray_real_T *data, double scanF,
                  emxArray_real_T *peaks_info)
{
  emxArray_boolean_T *b_I;
  emxArray_int32_T *M;
  emxArray_int32_T *S;
  emxArray_real_T *a1;
  emxArray_real_T *b_data;
  emxArray_real_T *c;
  emxArray_real_T *sx;
  double area;
  double b_c;
  double d;
  double tmp2;
  double work;
  double y2;
  double *a1_data;
  double *b_data_data;
  double *data_data;
  double *peaks_info_data;
  double *sx_data;
  int M_i;
  int S_i;
  int b_i;
  int i;
  int i1;
  int i2;
  unsigned int i4;
  int ia;
  int loop_ub;
  unsigned int peaks_i;
  int x1;
  int x2;
  int x3;
  int *M_data;
  int *S_data;
  bool *I_data;
  data_data = data->data;
  emxInit_boolean_T(&b_I);
  /* peak_detecte 检测data数据的谱峰，并输出所有峰的 {start, apex, end, height,
   * width, area}信息 */
  /*    此处提供详细说明 */
  /*  data 为基线校准后的数据(sample_num, feature_num) */
  /*  smooth */
  /*  --------------------- 要自动化处理的参数
   * ------------------------------------- */
  M_i = data->size[1];
  i = b_I->size[0] * b_I->size[1];
  b_I->size[0] = 1;
  b_I->size[1] = data->size[1];
  emxEnsureCapacity_boolean_T(b_I, i);
  I_data = b_I->data;
  loop_ub = data->size[1];
  for (i = 0; i < loop_ub; i++) {
    I_data[i] = rtIsNaN(data_data[i]);
  }
  S_i = b_I->size[1];
  for (b_i = 0; b_i < S_i; b_i++) {
    if (I_data[b_i]) {
      data_data[b_i] = 0.0;
    }
  }
  emxFree_boolean_T(&b_I);
  emxInit_real_T(&a1, 2);
  a1_data = a1->data;
  if (M_i < 1) {
    a1->size[0] = 1;
    a1->size[1] = 0;
  } else {
    i = a1->size[0] * a1->size[1];
    a1->size[0] = 1;
    a1->size[1] = M_i;
    emxEnsureCapacity_real_T(a1, i);
    a1_data = a1->data;
    loop_ub = M_i - 1;
    for (i = 0; i <= loop_ub; i++) {
      a1_data[i] = (double)i + 1.0;
    }
  }
  emxInit_real_T(&sx, 2);
  i = sx->size[0] * sx->size[1];
  sx->size[0] = 1;
  sx->size[1] = M_i;
  emxEnsureCapacity_real_T(sx, i);
  sx_data = sx->data;
  for (i = 0; i < M_i; i++) {
    sx_data[i] = 0.0;
  }
  emxInit_real_T(&b_data, 2);
  for (b_i = 0; b_i <= M_i - 5; b_i++) {
    d = a1_data[b_i];
    work = a1_data[b_i + 3];
    if ((int)(unsigned int)d > (int)(unsigned int)work) {
      i = -1;
      i1 = -1;
    } else {
      i = (int)(unsigned int)d - 2;
      i1 = (int)(unsigned int)work - 1;
    }
    ia = b_data->size[0] * b_data->size[1];
    b_data->size[0] = 1;
    loop_ub = i1 - i;
    b_data->size[1] = loop_ub;
    emxEnsureCapacity_real_T(b_data, ia);
    b_data_data = b_data->data;
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_data_data[i1] = data_data[(i + i1) + 1];
    }
    sx_data[b_i + 2] = combineVectorElements(b_data) / (double)loop_ub;
    /*  对每行依次求出窗口内的均值 */
  }
  i = peaks_info->size[0] * peaks_info->size[1];
  peaks_info->size[0] = M_i;
  peaks_info->size[1] = 6;
  emxEnsureCapacity_real_T(peaks_info, i);
  peaks_info_data = peaks_info->data;
  loop_ub = M_i * 6;
  for (i = 0; i < loop_ub; i++) {
    peaks_info_data[i] = 0.0;
  }
  peaks_i = 0U;
  /* for each sample */
  i = sx->size[1];
  if (sx->size[1] <= 1) {
    a1->size[0] = 1;
    a1->size[1] = 0;
  } else {
    i1 = a1->size[0] * a1->size[1];
    a1->size[0] = 1;
    a1->size[1] = sx->size[1] - 1;
    emxEnsureCapacity_real_T(a1, i1);
    a1_data = a1->data;
    work = sx_data[0];
    for (M_i = 2; M_i <= i; M_i++) {
      tmp2 = work;
      work = sx_data[M_i - 1];
      a1_data[M_i - 2] = work - tmp2;
    }
  }
  emxInit_int32_T(&S);
  /*  对该行作差 */
  /*          S = [];  */
  /*          M = []; */
  i = S->size[0] * S->size[1];
  S->size[0] = 1;
  S->size[1] = a1->size[1];
  emxEnsureCapacity_int32_T(S, i);
  S_data = S->data;
  loop_ub = a1->size[1];
  for (i = 0; i < loop_ub; i++) {
    S_data[i] = 0;
  }
  emxInit_int32_T(&M);
  i = M->size[0] * M->size[1];
  M->size[0] = 1;
  M->size[1] = a1->size[1];
  emxEnsureCapacity_int32_T(M, i);
  M_data = M->data;
  loop_ub = a1->size[1];
  for (i = 0; i < loop_ub; i++) {
    M_data[i] = 0;
  }
  S_i = 0;
  M_i = 0;
  /*  Determination of peak start (S), max (M) and end slut (S) */
  i = a1->size[1];
  for (i2 = 0; i2 <= i - 3; i2++) {
    /*  from the first to the last scan */
    d = a1_data[i2 + 1];
    if (((d <= 0.0) && (a1_data[i2 + 2] > 0.0)) ||
        ((d < 0.0) && (a1_data[i2 + 2] >= 0.0))) {
      /*  求每一个凹点（start\end 都在凹点上） */
      S_i++;
      S_data[S_i - 1] = i2 + 3;
      /*                  S = [S i2]; */
    }
    if ((a1_data[i2] > 0.0) && (d >= 0.0) && (a1_data[i2 + 2] <= 0.0) &&
        (a1_data[i2 + 3] < 0.0)) {
      /*  求每一个凸点（apex
       * 在凸点上），这个取法默认取后一个点,且有概率忽略共溶峰 */
      /*  共溶峰的忽略是由于平滑窗口导致的 */
      /*  上面的检测方法同时检测四个点，会忽略紧凑的共溶峰，故改为以下的检测方法
       */
      /*                      if d(1,i2-1)>0 && d(1,i2)<=0 || d(1,i2-1)>=0 &&
       * d(1,i2)<0 */
      M_i++;
      M_data[M_i - 1] = i2 + 2;
      /*                  M = [M i2-1]; */
    }
  }
  if (1 > S_i) {
    loop_ub = 0;
  } else {
    loop_ub = S_i;
  }
  i = S->size[0] * S->size[1];
  S->size[1] = loop_ub;
  emxEnsureCapacity_int32_T(S, i);
  S_data = S->data;
  if (1 > M_i) {
    i = 0;
  } else {
    i = M_i;
  }
  i1 = M->size[0] * M->size[1];
  M->size[1] = i;
  emxEnsureCapacity_int32_T(M, i1);
  M_data = M->data;
  emxInit_real_T(&c, 1);
  for (i2 = 0; i2 < i; i2++) {
    /*  遍历每一个凸点 */
    i1 = a1->size[0] * a1->size[1];
    a1->size[0] = 1;
    a1->size[1] = loop_ub;
    emxEnsureCapacity_real_T(a1, i1);
    a1_data = a1->data;
    S_i = M_data[i2];
    for (i1 = 0; i1 < loop_ub; i1++) {
      a1_data[i1] = S_data[i1] - S_i;
    }
    S_i = a1->size[1];
    i1 = b_data->size[0] * b_data->size[1];
    b_data->size[0] = 1;
    b_data->size[1] = a1->size[1];
    emxEnsureCapacity_real_T(b_data, i1);
    b_data_data = b_data->data;
    for (b_i = 0; b_i < S_i; b_i++) {
      b_data_data[b_i] = fabs((double)(int)a1_data[b_i]);
    }
    minimum(b_data, &work, &M_i);
    /* start must be located before max */
    x1 = 0;
    x2 = 0;
    x3 = 0;
    /*  找到距离最接近的凹点，并分配两边的凹点作为该凸点的start\end，边界不考虑
     */
    i1 = M_data[i2];
    ia = S_data[M_i - 1];
    if ((i1 > ia) && (M_i < loop_ub)) {
      x1 = ia;
      x2 = i1;
      x3 = S_data[M_i];
    } else if ((M_i > 1) && (i1 < ia)) {
      x1 = S_data[M_i - 2];
      x2 = i1;
      x3 = ia;
    }
    if (x1 != 0) {
      /* peakheight at start(y1), max(y2) and end(y3) */
      /*                      y2 = (data(ii,x2) + data(ii,x2+1)) /2;  %
       * 前面默认取最后一个点，此处取一个均值 */
      y2 = data_data[x2 - 1];
      /*  Area */
      if (x1 > x3) {
        i1 = -1;
        ia = -1;
      } else {
        i1 = x1 - 2;
        ia = x3 - 1;
      }
      area = 0.0;
      b_i = ia - i1;
      if (b_i > 1) {
        ia = c->size[0];
        c->size[0] = b_i;
        emxEnsureCapacity_real_T(c, ia);
        a1_data = c->data;
        for (ia = 0; ia < b_i; ia++) {
          a1_data[ia] = 1.0;
        }
        a1_data[0] = 0.5;
        a1_data[b_i - 1] = 0.5;
        S_i = 0;
        for (M_i = 1; M_i <= b_i; M_i++) {
          for (ia = M_i; ia <= M_i; ia++) {
            area += data_data[i1 + ia] * a1_data[S_i];
          }
          S_i++;
        }
      }
      /* peak width in half height */
      /*  求半峰宽，找到左右两边Y值最接近半峰高的数据点，然后左右作差得出半峰宽
       */
      if (x1 > x2) {
        i1 = 0;
        ia = 0;
      } else {
        i1 = x1 - 1;
        ia = x2;
      }
      tmp2 = y2 * 0.5;
      S_i = a1->size[0] * a1->size[1];
      a1->size[0] = 1;
      b_i = ia - i1;
      a1->size[1] = b_i;
      emxEnsureCapacity_real_T(a1, S_i);
      a1_data = a1->data;
      for (ia = 0; ia < b_i; ia++) {
        a1_data[ia] = data_data[i1 + ia] - tmp2;
      }
      S_i = a1->size[1];
      i1 = b_data->size[0] * b_data->size[1];
      b_data->size[0] = 1;
      b_data->size[1] = a1->size[1];
      emxEnsureCapacity_real_T(b_data, i1);
      b_data_data = b_data->data;
      for (b_i = 0; b_i < S_i; b_i++) {
        b_data_data[b_i] = fabs(a1_data[b_i]);
      }
      minimum(b_data, &work, &M_i);
      /* The closest point left of apex. */
      if (x2 > x3) {
        i1 = 0;
        ia = 0;
      } else {
        i1 = x2 - 1;
        ia = x3;
      }
      S_i = a1->size[0] * a1->size[1];
      a1->size[0] = 1;
      b_i = ia - i1;
      a1->size[1] = b_i;
      emxEnsureCapacity_real_T(a1, S_i);
      a1_data = a1->data;
      for (ia = 0; ia < b_i; ia++) {
        a1_data[ia] = data_data[i1 + ia] - tmp2;
      }
      S_i = a1->size[1];
      i1 = b_data->size[0] * b_data->size[1];
      b_data->size[0] = 1;
      b_data->size[1] = a1->size[1];
      emxEnsureCapacity_real_T(b_data, i1);
      b_data_data = b_data->data;
      for (b_i = 0; b_i < S_i; b_i++) {
        b_data_data[b_i] = fabs(a1_data[b_i]);
      }
      minimum(b_data, &work, &S_i);
      /* The closest point right of apex. */
      work = (((double)x2 + (double)S_i) - ((double)x1 + (double)M_i)) / scanF;
      /*  判断峰宽、峰高是否符合要求 */
      if ((work > 0.01) && (work < 10.0) && (y2 > 10000.0)) {
        /*  此时P的值只是一个Index，需要对应到X的时间轴上，才能取得真值 */
        /* p = ([x1; x2; x3]) / scanF_  + app.X(1, 1);%start peak end */
        if (x1 > x3) {
          i1 = -1;
          ia = -1;
        } else {
          i1 = x1 - 2;
          ia = x3 - 1;
        }
        S_i = b_data->size[0] * b_data->size[1];
        b_data->size[0] = 1;
        b_i = ia - i1;
        b_data->size[1] = b_i;
        emxEnsureCapacity_real_T(b_data, S_i);
        b_data_data = b_data->data;
        for (ia = 0; ia < b_i; ia++) {
          b_data_data[ia] = sx_data[(i1 + ia) + 1];
        }
        tmp2 = combineVectorElements(b_data) / (double)b_i;
        b_c = 0.0;
        i1 = x3 - x1;
        for (S_i = 0; S_i <= i1; S_i++) {
          i4 = (unsigned int)x1 + S_i;
          /*  The signal must only cross average twice */
          d = sx_data[(int)i4 - 1];
          if (((d < tmp2) && (sx_data[(int)i4] > tmp2)) ||
              ((d > tmp2) && (sx_data[(int)i4] < tmp2))) {
            b_c++;
          }
        }
        if (b_c <= 4.0) {
          /*  进出各两次，因此c要小于等于4 */
          /*                    检测到峰，记录 */
          /*  peaks consiste of start, apex, end, height, width, area */
          peaks_i++;
          peaks_info_data[(int)peaks_i - 1] = x1;
          peaks_info_data[((int)peaks_i + peaks_info->size[0]) - 1] = x2;
          peaks_info_data[((int)peaks_i + peaks_info->size[0] * 2) - 1] = x3;
          peaks_info_data[((int)peaks_i + peaks_info->size[0] * 3) - 1] = y2;
          peaks_info_data[((int)peaks_i + peaks_info->size[0] * 4) - 1] = work;
          peaks_info_data[((int)peaks_i + peaks_info->size[0] * 5) - 1] = area;
        }
      }
    }
  }
  emxFree_real_T(&b_data);
  emxFree_real_T(&c);
  emxFree_int32_T(&M);
  emxFree_int32_T(&S);
  emxFree_real_T(&sx);
  emxFree_real_T(&a1);
  /* If no peaks are detected */
  if ((int)peaks_i == 0) {
    i = peaks_info->size[0] * peaks_info->size[1];
    peaks_info->size[0] = 1;
    peaks_info->size[1] = 6;
    emxEnsureCapacity_real_T(peaks_info, i);
    peaks_info_data = peaks_info->data;
    for (i = 0; i < 6; i++) {
      peaks_info_data[i] = 0.0;
    }
  } else {
    loop_ub = (int)peaks_i;
    for (i = 0; i < 6; i++) {
      for (i1 = 0; i1 < loop_ub; i1++) {
        peaks_info_data[i1 + (int)peaks_i * i] =
            peaks_info_data[i1 + peaks_info->size[0] * i];
      }
    }
    i = peaks_info->size[0] * peaks_info->size[1];
    peaks_info->size[0] = (int)peaks_i;
    peaks_info->size[1] = 6;
    emxEnsureCapacity_real_T(peaks_info, i);
  }
}

/* End of code generation (peak_detecte.c) */
