//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// data_baseline.cpp
//
// Code generation for function 'data_baseline'
//

// Include files
#include "data_baseline.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "std.h"
#include "coder_array.h"
#include <cmath>

// Function Declarations
static double Baseline(coder::array<double, 2U> &x_baselined, double start,
                       double stop, const coder::array<double, 1U> &x,
                       coder::array<double, 2U> &base);

static void b_binary_expand_op(coder::array<double, 2U> &x_baselined, int i1,
                               const coder::array<double, 1U> &x, int i2,
                               int i3, const coder::array<double, 2U> &base,
                               int i4, int i5);

static void binary_expand_op(coder::array<double, 2U> &x_baselined, int i1,
                             const coder::array<double, 1U> &x, int i2, int i3,
                             const coder::array<double, 2U> &a1, int i4,
                             int i5);

// Function Definitions
static double Baseline(coder::array<double, 2U> &x_baselined, double start,
                       double stop, const coder::array<double, 1U> &x,
                       coder::array<double, 2U> &base)
{
  coder::array<double, 2U> c_x;
  coder::array<double, 2U> neg;
  coder::array<int, 2U> ii;
  coder::array<boolean_T, 2U> b_x;
  double S;
  double ex;
  int b_ii;
  int i;
  int i1;
  int idx;
  int nx;
  boolean_T exitg1;
  //  执行数据中单个段落的对齐，该段落由start和stop来界定，
  //  x_baselined为处理后的数据，x为原始数据，base为基线
  if (start > stop) {
    i = 0;
    i1 = 0;
  } else {
    i = static_cast<int>(start) - 1;
    i1 = static_cast<int>(stop);
  }
  nx = i1 - i;
  b_x.set_size(1, nx);
  for (i1 = 0; i1 < nx; i1++) {
    b_x[i1] = (x_baselined[i + i1] < 0.0);
  }
  nx = b_x.size(1);
  idx = 0;
  ii.set_size(1, b_x.size(1));
  b_ii = 0;
  exitg1 = false;
  while ((!exitg1) && (b_ii <= nx - 1)) {
    if (b_x[b_ii]) {
      idx++;
      ii[idx - 1] = b_ii + 1;
      if (idx >= nx) {
        exitg1 = true;
      } else {
        b_ii++;
      }
    } else {
      b_ii++;
    }
  }
  if (b_x.size(1) == 1) {
    if (idx == 0) {
      ii.set_size(1, 0);
    }
  } else {
    if (1 > idx) {
      idx = 0;
    }
    ii.set_size(ii.size(0), idx);
  }
  neg.set_size(1, ii.size(1));
  nx = ii.size(1);
  for (i = 0; i < nx; i++) {
    neg[i] = ii[i];
  }
  // if there are no more than half of V1 instances below zero, the for loop
  // should terminate
  if (neg.size(1) < 3) {
    S = 0.0;
  } else {
    int i2;
    i = neg.size(1);
    neg.set_size(neg.size(0), neg.size(1) + 1);
    neg[i] = rtInf;
    //  zeroes in Ii indicates that two consecetive valeus are below zero, 5 in
    //  a row indicates 6 places below zero in a row
    //  Ii2是一个索引，显示非零的位置
    nx = neg.size(1) - 1;
    c_x.set_size(1, neg.size(1) - 1);
    for (i = 0; i < nx; i++) {
      c_x[i] = (neg[i] - neg[i + 1]) + 1.0;
    }
    nx = c_x.size(1);
    idx = 0;
    ii.set_size(1, c_x.size(1));
    b_ii = 0;
    exitg1 = false;
    while ((!exitg1) && (b_ii <= nx - 1)) {
      if (c_x[b_ii] != 0.0) {
        idx++;
        ii[idx - 1] = b_ii + 1;
        if (idx >= nx) {
          exitg1 = true;
        } else {
          b_ii++;
        }
      } else {
        b_ii++;
      }
    }
    if (c_x.size(1) == 1) {
      if (idx == 0) {
        ii.set_size(1, 0);
      }
    } else {
      if (1 > idx) {
        idx = 0;
      }
      ii.set_size(ii.size(0), idx);
    }
    neg.set_size(1, ii.size(1) + 1);
    neg[0] = 0.0;
    nx = ii.size(1);
    for (i = 0; i < nx; i++) {
      neg[i + 1] = ii[i];
    }
    //  如果范围内只有一个非零
    if (neg.size(1) == 1) {
      double b;
      double b_b;
      double b_b_tmp;
      double b_tmp;
      if (start > stop) {
        i = 0;
        i1 = 0;
      } else {
        i = static_cast<int>(start) - 1;
        i1 = static_cast<int>(stop);
      }
      nx = i1 - i;
      neg.set_size(1, nx);
      for (i1 = 0; i1 < nx; i1++) {
        neg[i1] = x_baselined[i + i1];
      }
      coder::internal::minimum(neg, &ex, &nx);
      S = (static_cast<double>(nx) + start) - 1.0;
      ex = x[static_cast<int>(S) - 1];
      b_tmp = S - start;
      b_b_tmp = x[static_cast<int>(start - 1.0) - 1];
      b = (ex - b_b_tmp) / (b_tmp + 1.0);
      b_b = (x[static_cast<int>(stop + 1.0) - 1] - ex) / ((stop - S) + 1.0);
      if (start > S - 1.0) {
        i = 1;
      } else {
        i = static_cast<int>(start);
      }
      if (std::isnan(b_tmp)) {
        neg.set_size(1, 1);
        neg[0] = rtNaN;
      } else if (b_tmp < 1.0) {
        neg.set_size(1, 0);
      } else {
        nx = static_cast<int>(std::floor(b_tmp - 1.0));
        neg.set_size(1, nx + 1);
        for (i1 = 0; i1 <= nx; i1++) {
          neg[i1] = static_cast<double>(i1) + 1.0;
        }
      }
      nx = neg.size(1);
      for (i1 = 0; i1 < nx; i1++) {
        base[(i + i1) - 1] = b_b_tmp + neg[i1] * b;
      }
      if (S + 1.0 > stop) {
        i = 1;
      } else {
        i = static_cast<int>(S + 1.0);
      }
      b = stop - S;
      if (std::isnan(b)) {
        neg.set_size(1, 1);
        neg[0] = rtNaN;
      } else if (b < 1.0) {
        neg.set_size(1, 0);
      } else {
        nx = static_cast<int>(std::floor(b - 1.0));
        neg.set_size(1, nx + 1);
        for (i1 = 0; i1 <= nx; i1++) {
          neg[i1] = static_cast<double>(i1) + 1.0;
        }
      }
      nx = neg.size(1);
      for (i1 = 0; i1 < nx; i1++) {
        base[(i + i1) - 1] = x[static_cast<int>(S) - 1] + neg[i1] * b_b;
      }
      base[static_cast<int>(S) - 1] = x[static_cast<int>(S) - 1];
    } else {
      nx = neg.size(1) - 1;
      c_x.set_size(1, neg.size(1) - 1);
      for (i = 0; i < nx; i++) {
        c_x[i] = static_cast<int>(neg[i + 1]) - static_cast<int>(neg[i]);
      }
      nx = c_x.size(1);
      if (c_x.size(1) <= 2) {
        if (c_x.size(1) == 1) {
          idx = static_cast<int>(c_x[0]);
        } else if (static_cast<int>(c_x[0]) <
                   static_cast<int>(c_x[c_x.size(1) - 1])) {
          idx = static_cast<int>(c_x[c_x.size(1) - 1]);
        } else {
          idx = static_cast<int>(c_x[0]);
        }
      } else {
        idx = static_cast<int>(c_x[0]);
        for (b_ii = 2; b_ii <= nx; b_ii++) {
          ex = c_x[b_ii - 1];
          if (idx < static_cast<int>(ex)) {
            idx = static_cast<int>(ex);
          }
        }
      }
      if (idx > 3) {
        double b;
        double b_b;
        double b_b_tmp;
        double b_tmp;
        double c_b_tmp;
        if (start > stop) {
          i = 0;
          i1 = 0;
        } else {
          i = static_cast<int>(start) - 1;
          i1 = static_cast<int>(stop);
        }
        nx = i1 - i;
        neg.set_size(1, nx);
        for (i1 = 0; i1 < nx; i1++) {
          neg[i1] = x_baselined[i + i1];
        }
        coder::internal::minimum(neg, &ex, &nx);
        S = (static_cast<double>(nx) + start) - 1.0;
        ex = x[static_cast<int>(S) - 1];
        b_tmp = S - start;
        b_b_tmp = x[static_cast<int>(start - 1.0) - 1];
        b = (ex - b_b_tmp) / (b_tmp + 1.0);
        c_b_tmp = stop - S;
        b_b = (x[static_cast<int>(stop + 1.0) - 1] - ex) / (c_b_tmp + 1.0);
        if (start > S - 1.0) {
          i = 1;
        } else {
          i = static_cast<int>(start);
        }
        if (std::isnan(b_tmp)) {
          neg.set_size(1, 1);
          neg[0] = rtNaN;
        } else if (b_tmp < 1.0) {
          neg.set_size(1, 0);
        } else {
          nx = static_cast<int>(std::floor(b_tmp - 1.0));
          neg.set_size(1, nx + 1);
          for (i1 = 0; i1 <= nx; i1++) {
            neg[i1] = static_cast<double>(i1) + 1.0;
          }
        }
        nx = neg.size(1);
        for (i1 = 0; i1 < nx; i1++) {
          base[(i + i1) - 1] = b_b_tmp + neg[i1] * b;
        }
        if (S + 1.0 > stop) {
          i = 1;
        } else {
          i = static_cast<int>(S + 1.0);
        }
        if (std::isnan(c_b_tmp)) {
          neg.set_size(1, 1);
          neg[0] = rtNaN;
        } else if (c_b_tmp < 1.0) {
          neg.set_size(1, 0);
        } else {
          nx = static_cast<int>(std::floor(c_b_tmp - 1.0));
          neg.set_size(1, nx + 1);
          for (i1 = 0; i1 <= nx; i1++) {
            neg[i1] = static_cast<double>(i1) + 1.0;
          }
        }
        nx = neg.size(1);
        for (i1 = 0; i1 < nx; i1++) {
          base[(i + i1) - 1] = ex + neg[i1] * b_b;
        }
        base[static_cast<int>(S) - 1] = ex;
      } else {
        S = 0.0;
      }
    }
    if (start > stop) {
      i = 0;
      i1 = 0;
      idx = 0;
      b_ii = 0;
      i2 = 0;
    } else {
      i = static_cast<int>(start) - 1;
      i1 = static_cast<int>(stop);
      idx = static_cast<int>(start) - 1;
      b_ii = static_cast<int>(stop);
      i2 = static_cast<int>(start) - 1;
    }
    nx = i1 - i;
    if (nx == b_ii - idx) {
      for (i1 = 0; i1 < nx; i1++) {
        x_baselined[i2 + i1] = x[i + i1] - base[idx + i1];
      }
    } else {
      b_binary_expand_op(x_baselined, i2, x, i, i1 - 1, base, idx, b_ii - 1);
    }
  }
  return S;
}

static void b_binary_expand_op(coder::array<double, 2U> &x_baselined, int i1,
                               const coder::array<double, 1U> &x, int i2,
                               int i3, const coder::array<double, 2U> &base,
                               int i4, int i5)
{
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  stride_0_1 = ((i3 - i2) + 1 != 1);
  stride_1_1 = ((i5 - i4) + 1 != 1);
  if ((i5 - i4) + 1 == 1) {
    loop_ub = (i3 - i2) + 1;
  } else {
    loop_ub = (i5 - i4) + 1;
  }
  for (int i{0}; i < loop_ub; i++) {
    x_baselined[i1 + i] = x[i2 + i * stride_0_1] - base[i4 + i * stride_1_1];
  }
}

static void binary_expand_op(coder::array<double, 2U> &x_baselined, int i1,
                             const coder::array<double, 1U> &x, int i2, int i3,
                             const coder::array<double, 2U> &a1, int i4, int i5)
{
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  stride_0_1 = (i3 - i2 != 1);
  stride_1_1 = (i5 - i4 != 1);
  if (i5 - i4 == 1) {
    loop_ub = i3 - i2;
  } else {
    loop_ub = i5 - i4;
  }
  for (int i{0}; i < loop_ub; i++) {
    x_baselined[(i1 + i) + 1] =
        x[(i2 + i * stride_0_1) + 1] - a1[(i4 + i * stride_1_1) + 1];
  }
}

void data_baseline(const coder::array<double, 2U> &data, double peak_threshold,
                   double smooth_window, double noise_window,
                   coder::array<double, 2U> &data_baselined,
                   coder::array<double, 2U> &base)
{
  coder::array<double, 2U> Sx;
  coder::array<double, 2U> a1;
  coder::array<double, 2U> x_baselined;
  coder::array<double, 2U> y;
  coder::array<double, 1U> noise;
  coder::array<double, 1U> x;
  coder::array<signed char, 1U> b_x;
  coder::array<boolean_T, 1U> N;
  double S3;
  double b;
  double bsum;
  double iv;
  int b_i;
  int firstBlockLength;
  int i;
  int i1;
  int i2;
  int i3;
  int i4;
  int k;
  int lastBlockLength;
  int m1;
  int nblocks;
  int npages;
  unsigned int stop_data;
  //  对传入的二维数据data执行平滑、基线校准，并输出为data_baselined,
  //  base为确定的基线
  //    此处显示详细说明
  //  smooth_window, noise_window最好为偶数
  //  peak_threshold = 8000，smooth_window=4，noise_window=6
  // Smoothing (moving average)
  m1 = data.size(0);
  if (data.size(0) < 1) {
    a1.set_size(1, 0);
  } else {
    a1.set_size(1, data.size(0));
    npages = data.size(0) - 1;
    for (i = 0; i <= npages; i++) {
      a1[i] = static_cast<double>(i) + 1.0;
    }
  }
  Sx.set_size(data.size(0), data.size(1));
  npages = data.size(0) * data.size(1);
  for (i = 0; i < npages; i++) {
    Sx[i] = 0.0;
  }
  iv = std::round(smooth_window / 2.0);
  // assignin('base','vv',vv);
  // assignin('base','m1',m1);
  //  assignin('base','iv',iv);
  i = static_cast<int>(((static_cast<double>(data.size(0)) - iv) + 1.0) +
                       (1.0 - smooth_window));
  for (b_i = 0; b_i < i; b_i++) {
    bsum = smooth_window + static_cast<double>(b_i);
    b = a1[static_cast<int>((bsum - smooth_window) + 1.0) - 1];
    S3 = a1[static_cast<int>(bsum) - 1];
    if (b > S3) {
      i1 = -1;
      i2 = -1;
    } else {
      i1 = static_cast<int>(b) - 2;
      i2 = static_cast<int>(S3) - 1;
    }
    i3 = static_cast<int>((bsum - iv) + 1.0) - 1;
    i2 -= i1;
    if ((i2 == 0) || (data.size(1) == 0) || (i2 == 0)) {
      y.set_size(1, data.size(1));
      npages = data.size(1);
      for (i1 = 0; i1 < npages; i1++) {
        y[i1] = 0.0;
      }
    } else {
      npages = data.size(1) - 1;
      y.set_size(1, data.size(1));
      if (i2 <= 1024) {
        firstBlockLength = i2;
        lastBlockLength = 0;
        nblocks = 1;
      } else {
        firstBlockLength = 1024;
        nblocks = i2 / 1024;
        lastBlockLength = i2 - (nblocks << 10);
        if (lastBlockLength > 0) {
          nblocks++;
        } else {
          lastBlockLength = 1024;
        }
      }
      for (int xi{0}; xi <= npages; xi++) {
        int xpageoffset;
        xpageoffset = xi * i2;
        y[xi] =
            data[((i1 + xpageoffset % i2) + data.size(0) * (xpageoffset / i2)) +
                 1];
        for (k = 2; k <= firstBlockLength; k++) {
          i4 = (xpageoffset + k) - 1;
          y[xi] = y[xi] + data[((i1 + i4 % i2) + data.size(0) * (i4 / i2)) + 1];
        }
        for (int ib{2}; ib <= nblocks; ib++) {
          int hi;
          int xblockoffset;
          xblockoffset = xpageoffset + ((ib - 1) << 10);
          bsum = data[((i1 + xblockoffset % i2) +
                       data.size(0) * (xblockoffset / i2)) +
                      1];
          if (ib == nblocks) {
            hi = lastBlockLength;
          } else {
            hi = 1024;
          }
          for (k = 2; k <= hi; k++) {
            i4 = (xblockoffset + k) - 1;
            bsum += data[((i1 + i4 % i2) + data.size(0) * (i4 / i2)) + 1];
          }
          y[xi] = y[xi] + bsum;
        }
      }
    }
    npages = y.size(1);
    for (i1 = 0; i1 < npages; i1++) {
      Sx[i3 + Sx.size(0) * i1] = y[i1] / static_cast<double>(i2);
    }
  }
  data_baselined.set_size(data.size(1), data.size(0));
  base.set_size(data.size(1), data.size(0));
  i = data.size(1);
  for (lastBlockLength = 0; lastBlockLength < i; lastBlockLength++) {
    unsigned int c;
    // from sample 1 to n1
    npages = data.size(0);
    x.set_size(data.size(0));
    for (i1 = 0; i1 < npages; i1++) {
      x[i1] = data[i1 + data.size(0) * lastBlockLength];
    }
    a1.set_size(1, m1);
    for (i1 = 0; i1 < m1; i1++) {
      a1[i1] = 0.0;
    }
    i1 = static_cast<int>(static_cast<double>(data.size(0)) - noise_window);
    for (b_i = 0; b_i < i1; b_i++) {
      b = ((static_cast<double>(b_i) + 1.0) + noise_window) - 1.0;
      if (static_cast<double>(b_i) + 1.0 > b) {
        i2 = 0;
        i3 = 0;
      } else {
        i2 = b_i;
        i3 = static_cast<int>(b);
      }
      npages = i3 - i2;
      noise.set_size(npages);
      for (i3 = 0; i3 < npages; i3++) {
        noise[i3] = Sx[(i2 + i3) + Sx.size(0) * lastBlockLength];
      }
      a1[b_i] = coder::b_std(noise);
    }
    // Noiese is separated from peaks by making a matrix only containing noise:
    if (1 > m1) {
      npages = 0;
    } else {
      npages = m1;
    }
    noise.set_size(npages);
    for (i1 = 0; i1 < npages; i1++) {
      noise[i1] = data[i1 + data.size(0) * lastBlockLength];
    }
    for (b_i = 0; b_i <= m1 - 6; b_i++) {
      if ((a1[b_i + 5] < peak_threshold) && (a1[b_i] < peak_threshold)) {
        b = data[(b_i + data.size(0) * lastBlockLength) + 5];
        if (b < 5.0E+8) {
          noise[b_i + 5] = b;
        } else {
          noise[b_i + 5] = rtNaN;
        }
      } else {
        noise[b_i + 5] = rtNaN;
      }
    }
    npages = data.size(0);
    a1.set_size(1, data.size(0));
    for (i1 = 0; i1 < npages; i1++) {
      a1[i1] = data[i1 + data.size(0) * lastBlockLength];
    }
    // The baseline is estimated as straight line from start to stop of
    // intervals:
    x_baselined.set_size(1, m1);
    for (i1 = 0; i1 < m1; i1++) {
      x_baselined[i1] = 0.0;
    }
    N.set_size(noise.size(0));
    npages = noise.size(0);
    for (i1 = 0; i1 < npages; i1++) {
      N[i1] = std::isnan(noise[i1]);
    }
    c = 0U;
    i1 = N.size(0);
    for (b_i = 0; b_i <= i1 - 2; b_i++) {
      if ((!N[b_i]) && N[b_i + 1] &&
          (c <= static_cast<unsigned int>(b_i + 2))) {
        boolean_T exitg1;
        if (b_i + 2 > N.size(0)) {
          i2 = 0;
          i3 = 0;
        } else {
          i2 = b_i + 1;
          i3 = N.size(0);
        }
        npages = i3 - i2;
        b_x.set_size(npages);
        for (i3 = 0; i3 < npages; i3++) {
          b_x[i3] = static_cast<signed char>(N[i2 + i3] - 1);
        }
        k = (1 <= b_x.size(0));
        npages = 0;
        firstBlockLength = 0;
        exitg1 = false;
        while ((!exitg1) && (firstBlockLength <= b_x.size(0) - 1)) {
          if (b_x[firstBlockLength] != 0) {
            npages = 1;
            nblocks = firstBlockLength + 1;
            exitg1 = true;
          } else {
            firstBlockLength++;
          }
        }
        if (k == 1) {
          if (npages == 0) {
            k = 0;
          }
        } else {
          k = (1 <= npages);
        }
        for (i2 = 0; i2 < k; i2++) {
          stop_data = static_cast<unsigned int>(nblocks) + b_i;
        }
        c = stop_data + 1U;
        bsum = (static_cast<double>(stop_data) -
                (static_cast<double>(b_i) + 2.0)) +
               1.0;
        b = (data[static_cast<int>(stop_data) +
                  data.size(0) * lastBlockLength] -
             data[b_i + data.size(0) * lastBlockLength]) /
            bsum;
        if (static_cast<unsigned int>(b_i + 2) > stop_data) {
          i2 = 0;
        } else {
          i2 = b_i + 1;
        }
        if (bsum < 1.0) {
          y.set_size(1, 0);
        } else {
          y.set_size(1, static_cast<int>(bsum - 1.0) + 1);
          npages = static_cast<int>(bsum - 1.0);
          for (i3 = 0; i3 <= npages; i3++) {
            y[i3] = static_cast<double>(i3) + 1.0;
          }
        }
        bsum = data[(b_i + data.size(0) * lastBlockLength) + 1];
        npages = y.size(1);
        for (i3 = 0; i3 < npages; i3++) {
          a1[i2 + i3] = bsum + y[i3] * b;
        }
        if (static_cast<unsigned int>(b_i + 2) > stop_data) {
          i2 = 0;
          i3 = 0;
          i4 = 0;
          firstBlockLength = 0;
          nblocks = -1;
        } else {
          i2 = b_i + 1;
          i3 = static_cast<int>(stop_data);
          i4 = b_i + 1;
          firstBlockLength = static_cast<int>(stop_data);
          nblocks = b_i;
        }
        npages = i3 - i2;
        if (npages == firstBlockLength - i4) {
          for (i3 = 0; i3 < npages; i3++) {
            x_baselined[(nblocks + i3) + 1] = x[i2 + i3] - a1[i4 + i3];
          }
        } else {
          binary_expand_op(x_baselined, nblocks, x, i2 - 1, i3 - 1, a1, i4 - 1,
                           firstBlockLength - 1);
        }
        bsum = Baseline(x_baselined, static_cast<double>(b_i) + 2.0,
                        static_cast<double>(stop_data), x, a1);
        if (bsum != 0.0) {
          b = Baseline(x_baselined, static_cast<double>(b_i) + 2.0, bsum, x,
                       a1);
          S3 = Baseline(x_baselined, bsum, static_cast<double>(stop_data), x,
                        a1);
          if ((b != 0.0) && (S3 != 0.0)) {
            Baseline(x_baselined, static_cast<double>(b_i) + 2.0, b, x, a1);
            Baseline(x_baselined, b, bsum, x, a1);
            Baseline(x_baselined, bsum, S3, x, a1);
            Baseline(x_baselined, S3, static_cast<double>(stop_data), x, a1);
          } else if (b != 0.0) {
            Baseline(x_baselined, static_cast<double>(b_i) + 2.0, b, x, a1);
            Baseline(x_baselined, b, bsum, x, a1);
          } else if (S3 != 0.0) {
            Baseline(x_baselined, bsum, S3, x, a1);
            Baseline(x_baselined, S3, static_cast<double>(stop_data), x, a1);
          }
        }
      } else if (c < static_cast<unsigned int>(b_i + 2)) {
        a1[b_i + 1] = noise[b_i + 1];
        x_baselined[b_i + 1] =
            data[(b_i + data.size(0) * lastBlockLength) + 1] - a1[b_i + 1];
      }
    }
    // baseline and noise are removed from raw data
    npages = a1.size(1);
    for (i1 = 0; i1 < npages; i1++) {
      base[lastBlockLength + base.size(0) * i1] = a1[i1];
    }
    for (b_i = 0; b_i < m1; b_i++) {
      if (x_baselined[b_i] < 0.0) {
        x_baselined[b_i] = 0.0;
      }
    }
    npages = x_baselined.size(1);
    for (i1 = 0; i1 < npages; i1++) {
      data_baselined[lastBlockLength + data_baselined.size(0) * i1] =
          x_baselined[i1];
    }
  }
}

// End of code generation (data_baseline.cpp)
