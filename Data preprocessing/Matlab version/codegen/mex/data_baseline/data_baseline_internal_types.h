//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// data_baseline_internal_types.h
//
// Code generation for function 'data_baseline'
//

#pragma once

// Include files
#include "data_baseline_types.h"
#include "rtwtypes.h"
#include "emlrt.h"

// Type Definitions
struct rtDesignRangeCheckInfo {
  int32_T lineNo;
  int32_T colNo;
  const char_T *fName;
  const char_T *pName;
};

struct rtRunTimeErrorInfo {
  int32_T lineNo;
  int32_T colNo;
  const char_T *fName;
  const char_T *pName;
};

// End of code generation (data_baseline_internal_types.h)
