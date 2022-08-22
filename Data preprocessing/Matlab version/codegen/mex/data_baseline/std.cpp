//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// std.cpp
//
// Code generation for function 'std'
//

// Include files
#include "std.h"
#include "data_baseline_data.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "sumMatrixIncludeNaN.h"
#include "blas.h"
#include "coder_array.h"
#include "mwmathutil.h"
#include <cstddef>

// Variable Definitions
static emlrtRSInfo fb_emlrtRSI{
    9,     // lineNo
    "std", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\lib\\matlab\\datafun\\std.m" // pathName
};

static emlrtRSInfo gb_emlrtRSI{
    102,      // lineNo
    "varstd", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\lib\\matlab\\datafun\\private\\varstd"
    ".m" // pathName
};

static emlrtRSInfo hb_emlrtRSI{
    96,        // lineNo
    "vvarstd", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\lib\\matlab\\datafun\\private\\vvarst"
    "d.m" // pathName
};

static emlrtRSInfo ib_emlrtRSI{
    127,       // lineNo
    "vvarstd", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\lib\\matlab\\datafun\\private\\vvarst"
    "d.m" // pathName
};

static emlrtRSInfo jb_emlrtRSI{
    143,       // lineNo
    "vvarstd", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\lib\\matlab\\datafun\\private\\vvarst"
    "d.m" // pathName
};

static emlrtRTEInfo fb_emlrtRTEI{
    126,       // lineNo
    34,        // colNo
    "vvarstd", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\lib\\matlab\\datafun\\private\\vvarst"
    "d.m" // pName
};

// Function Definitions
namespace coder {
real_T b_std(const emlrtStack *sp, const ::coder::array<real_T, 1U> &x)
{
  ptrdiff_t incx_t;
  ptrdiff_t n_t;
  array<real_T, 1U> absdiff;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  emlrtStack g_st;
  emlrtStack st;
  real_T y;
  int32_T n;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  e_st.prev = &d_st;
  e_st.tls = d_st.tls;
  f_st.prev = &e_st;
  f_st.tls = e_st.tls;
  g_st.prev = &f_st;
  g_st.tls = f_st.tls;
  emlrtHeapReferenceStackEnterFcnR2012b((emlrtCTX)sp);
  st.site = &fb_emlrtRSI;
  n = x.size(0);
  b_st.site = &gb_emlrtRSI;
  if (x.size(0) == 0) {
    y = rtNaN;
  } else if (x.size(0) == 1) {
    if ((!muDoubleScalarIsInf(x[0])) && (!muDoubleScalarIsNaN(x[0]))) {
      y = 0.0;
    } else {
      y = rtNaN;
    }
  } else {
    real_T s;
    int32_T nfb;
    c_st.site = &hb_emlrtRSI;
    d_st.site = &q_emlrtRSI;
    e_st.site = &r_emlrtRSI;
    f_st.site = &s_emlrtRSI;
    if (x.size(0) < 4096) {
      g_st.site = &u_emlrtRSI;
      s = sumColumnB(&g_st, x, x.size(0));
    } else {
      int32_T inb;
      int32_T nleft;
      nfb = x.size(0) / 4096;
      inb = nfb << 12;
      nleft = x.size(0) - inb;
      s = sumColumnB4(x, 1);
      for (int32_T ib{2}; ib <= nfb; ib++) {
        s += sumColumnB4(x, ((ib - 1) << 12) + 1);
      }
      if (nleft > 0) {
        g_st.site = &w_emlrtRSI;
        s += sumColumnB(&g_st, x, nleft, inb + 1);
      }
    }
    s /= static_cast<real_T>(x.size(0));
    absdiff.set_size(&fb_emlrtRTEI, &b_st, x.size(0));
    c_st.site = &ib_emlrtRSI;
    if (x.size(0) > 2147483646) {
      d_st.site = &x_emlrtRSI;
      check_forloop_overflow_error(&d_st);
    }
    for (nfb = 0; nfb < n; nfb++) {
      absdiff[nfb] = muDoubleScalarAbs(x[nfb] - s);
    }
    n_t = (ptrdiff_t)x.size(0);
    incx_t = (ptrdiff_t)1;
    y = dnrm2(&n_t, &(absdiff.data())[0], &incx_t);
    c_st.site = &jb_emlrtRSI;
    y /= muDoubleScalarSqrt(static_cast<real_T>(x.size(0)) - 1.0);
  }
  emlrtHeapReferenceStackLeaveFcnR2012b((emlrtCTX)sp);
  return y;
}

} // namespace coder

// End of code generation (std.cpp)
