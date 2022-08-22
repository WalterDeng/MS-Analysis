//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// find.cpp
//
// Code generation for function 'find'
//

// Include files
#include "find.h"
#include "data_baseline_data.h"
#include "eml_int_forloop_overflow_check.h"
#include "indexShapeCheck.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Variable Definitions
static emlrtRSInfo lb_emlrtRSI{
    144,        // lineNo
    "eml_find", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\lib\\matlab\\elmat\\find.m" // pathName
};

static emlrtRSInfo mb_emlrtRSI{
    402,                  // lineNo
    "find_first_indices", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\lib\\matlab\\elmat\\find.m" // pathName
};

static emlrtRSInfo nb_emlrtRSI{
    382,                  // lineNo
    "find_first_indices", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\lib\\matlab\\elmat\\find.m" // pathName
};

static emlrtRTEInfo g_emlrtRTEI{
    81,         // lineNo
    1,          // colNo
    "eml_find", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\lib\\matlab\\elmat\\find.m" // pName
};

static emlrtRTEInfo h_emlrtRTEI{
    392,                  // lineNo
    1,                    // colNo
    "find_first_indices", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\lib\\matlab\\elmat\\find.m" // pName
};

static emlrtRTEInfo gb_emlrtRTEI{
    144,    // lineNo
    9,      // colNo
    "find", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\lib\\matlab\\elmat\\find.m" // pName
};

static emlrtRTEInfo hb_emlrtRTEI{
    364,    // lineNo
    24,     // colNo
    "find", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\lib\\matlab\\elmat\\find.m" // pName
};

// Function Definitions
namespace coder {
void b_eml_find(const emlrtStack *sp, const ::coder::array<boolean_T, 2U> &x,
                ::coder::array<int32_T, 2U> &i)
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack st;
  int32_T idx;
  int32_T ii;
  int32_T nx;
  boolean_T exitg1;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  nx = x.size(1);
  st.site = &lb_emlrtRSI;
  idx = 0;
  i.set_size(&hb_emlrtRTEI, &st, 1, x.size(1));
  b_st.site = &nb_emlrtRSI;
  if ((1 <= x.size(1)) && (x.size(1) > 2147483646)) {
    c_st.site = &x_emlrtRSI;
    check_forloop_overflow_error(&c_st);
  }
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii <= nx - 1)) {
    if (x[ii]) {
      idx++;
      i[idx - 1] = ii + 1;
      if (idx >= nx) {
        exitg1 = true;
      } else {
        ii++;
      }
    } else {
      ii++;
    }
  }
  if (idx > x.size(1)) {
    emlrtErrorWithMessageIdR2018a(&st, &h_emlrtRTEI,
                                  "Coder:builtins:AssertionFailed",
                                  "Coder:builtins:AssertionFailed", 0);
  }
  if (x.size(1) == 1) {
    if (idx == 0) {
      i.set_size(&gb_emlrtRTEI, &st, 1, 0);
    }
  } else {
    if (1 > idx) {
      idx = 0;
    }
    i.set_size(&gb_emlrtRTEI, &st, i.size(0), idx);
  }
}

void eml_find(const emlrtStack *sp, const ::coder::array<real_T, 1U> &x,
              int32_T i_data[], int32_T *i_size)
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack st;
  int32_T iv[2];
  int32_T idx;
  int32_T ii;
  boolean_T exitg1;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  *i_size = (1 <= x.size(0));
  if (*i_size > x.size(0)) {
    emlrtErrorWithMessageIdR2018a(sp, &g_emlrtRTEI,
                                  "Coder:builtins:AssertionFailed",
                                  "Coder:builtins:AssertionFailed", 0);
  }
  st.site = &lb_emlrtRSI;
  idx = 0;
  b_st.site = &nb_emlrtRSI;
  if ((1 <= x.size(0)) && (x.size(0) > 2147483646)) {
    c_st.site = &x_emlrtRSI;
    check_forloop_overflow_error(&c_st);
  }
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii <= x.size(0) - 1)) {
    if (x[ii] != 0.0) {
      idx = 1;
      i_data[0] = ii + 1;
      exitg1 = true;
    } else {
      ii++;
    }
  }
  if (idx > *i_size) {
    emlrtErrorWithMessageIdR2018a(&st, &h_emlrtRTEI,
                                  "Coder:builtins:AssertionFailed",
                                  "Coder:builtins:AssertionFailed", 0);
  }
  if (*i_size == 1) {
    if (idx == 0) {
      *i_size = 0;
    }
  } else {
    *i_size = (1 <= idx);
    iv[0] = 1;
    iv[1] = *i_size;
    b_st.site = &mb_emlrtRSI;
    internal::indexShapeCheck(&b_st, 0, iv);
  }
}

void eml_find(const emlrtStack *sp, const ::coder::array<real_T, 2U> &x,
              ::coder::array<int32_T, 2U> &i)
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack st;
  int32_T idx;
  int32_T ii;
  int32_T nx;
  boolean_T exitg1;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  nx = x.size(1);
  st.site = &lb_emlrtRSI;
  idx = 0;
  i.set_size(&hb_emlrtRTEI, &st, 1, x.size(1));
  b_st.site = &nb_emlrtRSI;
  if ((1 <= x.size(1)) && (x.size(1) > 2147483646)) {
    c_st.site = &x_emlrtRSI;
    check_forloop_overflow_error(&c_st);
  }
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii <= nx - 1)) {
    if (x[ii] != 0.0) {
      idx++;
      i[idx - 1] = ii + 1;
      if (idx >= nx) {
        exitg1 = true;
      } else {
        ii++;
      }
    } else {
      ii++;
    }
  }
  if (idx > x.size(1)) {
    emlrtErrorWithMessageIdR2018a(&st, &h_emlrtRTEI,
                                  "Coder:builtins:AssertionFailed",
                                  "Coder:builtins:AssertionFailed", 0);
  }
  if (x.size(1) == 1) {
    if (idx == 0) {
      i.set_size(&gb_emlrtRTEI, &st, 1, 0);
    }
  } else {
    if (1 > idx) {
      idx = 0;
    }
    i.set_size(&gb_emlrtRTEI, &st, i.size(0), idx);
  }
}

} // namespace coder

// End of code generation (find.cpp)
