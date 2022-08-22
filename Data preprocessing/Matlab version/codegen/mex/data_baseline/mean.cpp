//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// mean.cpp
//
// Code generation for function 'mean'
//

// Include files
#include "mean.h"
#include "data_baseline_data.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "sumMatrixIncludeNaN.h"
#include "coder_array.h"

// Variable Definitions
static emlrtRSInfo p_emlrtRSI{
    49,     // lineNo
    "mean", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\lib\\matlab\\datafun\\mean.m" // pathName
};

static emlrtRSInfo t_emlrtRSI{
    41,                 // lineNo
    "sumMatrixColumns", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\lib\\matlab\\datafun\\private\\sumMat"
    "rixIncludeNaN.m" // pathName
};

static emlrtRSInfo v_emlrtRSI{
    50,                 // lineNo
    "sumMatrixColumns", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\lib\\matlab\\datafun\\private\\sumMat"
    "rixIncludeNaN.m" // pathName
};

static emlrtRTEInfo c_emlrtRTEI{
    22,     // lineNo
    5,      // colNo
    "mean", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\lib\\matlab\\datafun\\mean.m" // pName
};

static emlrtRTEInfo d_emlrtRTEI{
    18,     // lineNo
    15,     // colNo
    "mean", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\lib\\matlab\\datafun\\mean.m" // pName
};

static emlrtRTEInfo cb_emlrtRTEI{
    35,                    // lineNo
    20,                    // colNo
    "sumMatrixIncludeNaN", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\lib\\matlab\\datafun\\private\\sumMat"
    "rixIncludeNaN.m" // pName
};

static emlrtRTEInfo db_emlrtRTEI{
    74,                      // lineNo
    9,                       // colNo
    "combineVectorElements", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\lib\\matlab\\datafun\\private\\combin"
    "eVectorElements.m" // pName
};

static emlrtRTEInfo eb_emlrtRTEI{
    49,     // lineNo
    5,      // colNo
    "mean", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\lib\\matlab\\datafun\\mean.m" // pName
};

// Function Definitions
namespace coder {
void mean(const emlrtStack *sp, const ::coder::array<real_T, 2U> &x,
          ::coder::array<real_T, 2U> &y)
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  emlrtStack st;
  int32_T ncols;
  int32_T nfb;
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
  if ((x.size(0) == 1) && (x.size(1) != 1)) {
    emlrtErrorWithMessageIdR2018a(sp, &d_emlrtRTEI,
                                  "Coder:toolbox:autoDimIncompatibility",
                                  "Coder:toolbox:autoDimIncompatibility", 0);
  }
  if ((x.size(0) == 0) && (x.size(1) == 0)) {
    emlrtErrorWithMessageIdR2018a(sp, &c_emlrtRTEI,
                                  "Coder:toolbox:UnsupportedSpecialEmpty",
                                  "Coder:toolbox:UnsupportedSpecialEmpty", 0);
  }
  st.site = &p_emlrtRSI;
  b_st.site = &q_emlrtRSI;
  if ((x.size(0) == 0) || (x.size(1) == 0)) {
    y.set_size(&db_emlrtRTEI, &b_st, 1, x.size(1));
    ncols = x.size(1);
    for (nfb = 0; nfb < ncols; nfb++) {
      y[nfb] = 0.0;
    }
  } else {
    c_st.site = &r_emlrtRSI;
    d_st.site = &s_emlrtRSI;
    y.set_size(&cb_emlrtRTEI, &d_st, 1, x.size(1));
    ncols = x.size(1) - 1;
    if (x.size(0) < 4096) {
      e_st.site = &t_emlrtRSI;
      if (x.size(1) > 2147483646) {
        f_st.site = &x_emlrtRSI;
        check_forloop_overflow_error(&f_st);
      }
      for (int32_T col{0}; col <= ncols; col++) {
        e_st.site = &u_emlrtRSI;
        y[col] = sumColumnB(&e_st, x, col + 1, x.size(0));
      }
    } else {
      int32_T inb;
      int32_T nleft;
      nfb = x.size(0) / 4096;
      inb = nfb << 12;
      nleft = x.size(0) - inb;
      e_st.site = &v_emlrtRSI;
      if (x.size(1) > 2147483646) {
        f_st.site = &x_emlrtRSI;
        check_forloop_overflow_error(&f_st);
      }
      for (int32_T col{0}; col <= ncols; col++) {
        real_T s;
        s = sumColumnB4(x, col + 1, 1);
        for (int32_T ib{2}; ib <= nfb; ib++) {
          s += sumColumnB4(x, col + 1, ((ib - 1) << 12) + 1);
        }
        if (nleft > 0) {
          e_st.site = &w_emlrtRSI;
          s += sumColumnB(&e_st, x, col + 1, nleft, inb + 1);
        }
        y[col] = s;
      }
    }
  }
  y.set_size(&eb_emlrtRTEI, sp, 1, y.size(1));
  ncols = y.size(1) - 1;
  for (nfb = 0; nfb <= ncols; nfb++) {
    y[nfb] = y[nfb] / static_cast<real_T>(x.size(0));
  }
}

} // namespace coder

// End of code generation (mean.cpp)
