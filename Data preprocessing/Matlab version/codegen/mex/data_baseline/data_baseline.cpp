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
#include "data_baseline_data.h"
#include "eml_int_forloop_overflow_check.h"
#include "find.h"
#include "indexShapeCheck.h"
#include "mean.h"
#include "rt_nonfinite.h"
#include "std.h"
#include "coder_array.h"
#include "mwmathutil.h"

// Variable Definitions
static emlrtRSInfo emlrtRSI{
    18,              // lineNo
    "data_baseline", // fcnName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pathName
};

static emlrtRSInfo b_emlrtRSI{
    31,              // lineNo
    "data_baseline", // fcnName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pathName
};

static emlrtRSInfo c_emlrtRSI{
    52,              // lineNo
    "data_baseline", // fcnName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pathName
};

static emlrtRSInfo d_emlrtRSI{
    58,              // lineNo
    "data_baseline", // fcnName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pathName
};

static emlrtRSInfo e_emlrtRSI{
    60,              // lineNo
    "data_baseline", // fcnName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pathName
};

static emlrtRSInfo f_emlrtRSI{
    62,              // lineNo
    "data_baseline", // fcnName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pathName
};

static emlrtRSInfo g_emlrtRSI{
    63,              // lineNo
    "data_baseline", // fcnName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pathName
};

static emlrtRSInfo h_emlrtRSI{
    65,              // lineNo
    "data_baseline", // fcnName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pathName
};

static emlrtRSInfo i_emlrtRSI{
    66,              // lineNo
    "data_baseline", // fcnName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pathName
};

static emlrtRSInfo j_emlrtRSI{
    67,              // lineNo
    "data_baseline", // fcnName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pathName
};

static emlrtRSInfo k_emlrtRSI{
    68,              // lineNo
    "data_baseline", // fcnName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pathName
};

static emlrtRSInfo l_emlrtRSI{
    70,              // lineNo
    "data_baseline", // fcnName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pathName
};

static emlrtRSInfo m_emlrtRSI{
    71,              // lineNo
    "data_baseline", // fcnName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pathName
};

static emlrtRSInfo n_emlrtRSI{
    73,              // lineNo
    "data_baseline", // fcnName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pathName
};

static emlrtRSInfo o_emlrtRSI{
    74,              // lineNo
    "data_baseline", // fcnName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pathName
};

static emlrtRSInfo kb_emlrtRSI{
    39,     // lineNo
    "find", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\lib\\matlab\\elmat\\find.m" // pathName
};

static emlrtRSInfo ob_emlrtRSI{
    138,        // lineNo
    "Baseline", // fcnName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pathName
};

static emlrtRSInfo pb_emlrtRSI{
    128,        // lineNo
    "Baseline", // fcnName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pathName
};

static emlrtRSInfo qb_emlrtRSI{
    127,        // lineNo
    "Baseline", // fcnName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pathName
};

static emlrtRSInfo rb_emlrtRSI{
    120,        // lineNo
    "Baseline", // fcnName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pathName
};

static emlrtRSInfo sb_emlrtRSI{
    116,        // lineNo
    "Baseline", // fcnName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pathName
};

static emlrtRSInfo tb_emlrtRSI{
    104,        // lineNo
    "Baseline", // fcnName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pathName
};

static emlrtRSInfo ub_emlrtRSI{
    17,    // lineNo
    "min", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\lib\\matlab\\datafun\\min.m" // pathName
};

static emlrtRSInfo
    vb_emlrtRSI{
        40,         // lineNo
        "minOrMax", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2021b\\toolbox\\eml\\eml\\+coder\\+internal\\minOrMax."
        "m" // pathName
    };

static emlrtRSInfo
    wb_emlrtRSI{
        90,        // lineNo
        "minimum", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2021b\\toolbox\\eml\\eml\\+coder\\+internal\\minOrMax."
        "m" // pathName
    };

static emlrtRSInfo xb_emlrtRSI{
    169,             // lineNo
    "unaryMinOrMax", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\unaryMinOrMax.m" // pathName
};

static emlrtRSInfo yb_emlrtRSI{
    62,                      // lineNo
    "vectorMinOrMaxInPlace", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\vectorMinOrMaxInPlace.m" // pathName
};

static emlrtRSInfo ac_emlrtRSI{
    54,                      // lineNo
    "vectorMinOrMaxInPlace", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\vectorMinOrMaxInPlace.m" // pathName
};

static emlrtRSInfo bc_emlrtRSI{
    103,         // lineNo
    "findFirst", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\vectorMinOrMaxInPlace.m" // pathName
};

static emlrtRSInfo cc_emlrtRSI{
    120,                        // lineNo
    "minOrMaxRealVectorKernel", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\vectorMinOrMaxInPlace.m" // pathName
};

static emlrtRSInfo dc_emlrtRSI{
    15,    // lineNo
    "max", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\lib\\matlab\\datafun\\max.m" // pathName
};

static emlrtRSInfo
    ec_emlrtRSI{
        44,         // lineNo
        "minOrMax", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2021b\\toolbox\\eml\\eml\\+coder\\+internal\\minOrMax."
        "m" // pathName
    };

static emlrtRSInfo
    fc_emlrtRSI{
        79,        // lineNo
        "maximum", // fcnName
        "C:\\Program "
        "Files\\MATLAB\\R2021b\\toolbox\\eml\\eml\\+coder\\+internal\\minOrMax."
        "m" // pathName
    };

static emlrtRSInfo gc_emlrtRSI{
    186,             // lineNo
    "unaryMinOrMax", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\unaryMinOrMax.m" // pathName
};

static emlrtRSInfo hc_emlrtRSI{
    897,                    // lineNo
    "maxRealVectorOmitNaN", // fcnName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\unaryMinOrMax.m" // pathName
};

static emlrtECInfo emlrtECI{
    -1,              // nDims
    86,              // lineNo
    9,               // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtBCInfo emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    86,              // lineNo
    15,              // colNo
    "Base_",         // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtECInfo b_emlrtECI{
    -1,              // nDims
    93,              // lineNo
    9,               // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtBCInfo b_emlrtBCI{
    -1,                // iFirst
    -1,                // iLast
    93,                // lineNo
    25,                // colNo
    "data_baselined_", // aName
    "data_baseline",   // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtECInfo c_emlrtECI{
    -1,              // nDims
    58,              // lineNo
    17,              // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtBCInfo c_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    58,              // lineNo
    35,              // colNo
    "x_baselined",   // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo d_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    58,              // lineNo
    29,              // colNo
    "x_baselined",   // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtECInfo d_emlrtECI{
    2,               // nDims
    58,              // lineNo
    44,              // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtBCInfo e_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    58,              // lineNo
    71,              // colNo
    "base_",         // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo f_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    58,              // lineNo
    65,              // colNo
    "base_",         // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtECInfo e_emlrtECI{
    -1,              // nDims
    57,              // lineNo
    17,              // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtBCInfo g_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    57,              // lineNo
    29,              // colNo
    "base_",         // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo h_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    57,              // lineNo
    23,              // colNo
    "base_",         // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo i_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    58,              // lineNo
    52,              // colNo
    "x",             // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo j_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    58,              // lineNo
    46,              // colNo
    "x",             // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo k_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    53,              // lineNo
    29,              // colNo
    "stop",          // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo l_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    52,              // lineNo
    32,              // colNo
    "N",             // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo m_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    31,              // lineNo
    32,              // colNo
    "sx",            // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtDCInfo emlrtDCI{
    31,              // lineNo
    32,              // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    1                           // checkKind
};

static emlrtBCInfo n_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    31,              // lineNo
    30,              // colNo
    "sx",            // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtRTEInfo emlrtRTEI{
    30,              // lineNo
    15,              // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtBCInfo o_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    25,              // lineNo
    23,              // colNo
    "data",          // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo p_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    24,              // lineNo
    21,              // colNo
    "Sx",            // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtECInfo f_emlrtECI{
    -1,              // nDims
    18,              // lineNo
    9,               // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtBCInfo q_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    18,              // lineNo
    12,              // colNo
    "Sx",            // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtDCInfo b_emlrtDCI{
    18,              // lineNo
    12,              // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    1                           // checkKind
};

static emlrtBCInfo r_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    18,              // lineNo
    57,              // colNo
    "data",          // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtDCInfo c_emlrtDCI{
    18,              // lineNo
    57,              // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    1                           // checkKind
};

static emlrtBCInfo s_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    18,              // lineNo
    35,              // colNo
    "data",          // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtDCInfo d_emlrtDCI{
    18,              // lineNo
    35,              // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    1                           // checkKind
};

static emlrtBCInfo t_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    18,              // lineNo
    60,              // colNo
    "a1",            // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtDCInfo e_emlrtDCI{
    18,              // lineNo
    60,              // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    1                           // checkKind
};

static emlrtRTEInfo b_emlrtRTEI{
    17,              // lineNo
    13,              // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtBCInfo u_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    18,              // lineNo
    38,              // colNo
    "a1",            // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtDCInfo f_emlrtDCI{
    18,              // lineNo
    38,              // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    1                           // checkKind
};

static emlrtBCInfo v_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    37,              // lineNo
    23,              // colNo
    "Mstd",          // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo w_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    31,              // lineNo
    20,              // colNo
    "Mstd",          // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo x_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    37,              // lineNo
    51,              // colNo
    "Mstd",          // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo y_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    37,              // lineNo
    76,              // colNo
    "x",             // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo ab_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    40,              // lineNo
    23,              // colNo
    "noise",         // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo bb_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    38,              // lineNo
    30,              // colNo
    "x",             // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo cb_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    38,              // lineNo
    23,              // colNo
    "noise",         // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo db_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    50,              // lineNo
    18,              // colNo
    "N",             // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo eb_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    50,              // lineNo
    33,              // colNo
    "N",             // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo fb_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    79,              // lineNo
    34,              // colNo
    "noise",         // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo gb_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    79,              // lineNo
    23,              // colNo
    "base_",         // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo hb_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    88,              // lineNo
    28,              // colNo
    "x_baselined",   // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo ib_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    80,              // lineNo
    37,              // colNo
    "x",             // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo jb_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    80,              // lineNo
    46,              // colNo
    "base_",         // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo kb_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    80,              // lineNo
    29,              // colNo
    "x_baselined",   // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo lb_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    89,              // lineNo
    29,              // colNo
    "x_baselined",   // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo mb_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    56,              // lineNo
    46,              // colNo
    "x",             // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo nb_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    56,              // lineNo
    56,              // colNo
    "x",             // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo ob_emlrtBCI{
    -1,              // iFirst
    -1,              // iLast
    57,              // lineNo
    46,              // colNo
    "x",             // aName
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtECInfo g_emlrtECI{
    -1,         // nDims
    138,        // lineNo
    5,          // colNo
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtBCInfo pb_emlrtBCI{
    -1,            // iFirst
    -1,            // iLast
    138,           // lineNo
    23,            // colNo
    "x_baselined", // aName
    "Baseline",    // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo qb_emlrtBCI{
    -1,            // iFirst
    -1,            // iLast
    138,           // lineNo
    17,            // colNo
    "x_baselined", // aName
    "Baseline",    // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtECInfo h_emlrtECI{
    2,          // nDims
    138,        // lineNo
    32,         // colNo
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtBCInfo rb_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    138,        // lineNo
    58,         // colNo
    "base",     // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo sb_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    138,        // lineNo
    52,         // colNo
    "base",     // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtECInfo i_emlrtECI{
    -1,         // nDims
    133,        // lineNo
    9,          // colNo
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtBCInfo tb_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    133,        // lineNo
    20,         // colNo
    "base",     // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo ub_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    133,        // lineNo
    15,         // colNo
    "base",     // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtECInfo j_emlrtECI{
    -1,         // nDims
    132,        // lineNo
    9,          // colNo
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtBCInfo vb_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    132,        // lineNo
    21,         // colNo
    "base",     // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo wb_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    132,        // lineNo
    14,         // colNo
    "base",     // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtECInfo k_emlrtECI{
    -1,         // nDims
    125,        // lineNo
    9,          // colNo
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtBCInfo xb_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    125,        // lineNo
    20,         // colNo
    "base",     // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo yb_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    125,        // lineNo
    15,         // colNo
    "base",     // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtECInfo l_emlrtECI{
    -1,         // nDims
    124,        // lineNo
    9,          // colNo
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtBCInfo ac_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    124,        // lineNo
    21,         // colNo
    "base",     // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo bc_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    124,        // lineNo
    14,         // colNo
    "base",     // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo cc_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    138,        // lineNo
    40,         // colNo
    "x",        // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo dc_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    138,        // lineNo
    34,         // colNo
    "x",        // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo ec_emlrtBCI{
    -1,            // iFirst
    -1,            // iLast
    128,           // lineNo
    50,            // colNo
    "x_baselined", // aName
    "Baseline",    // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo fc_emlrtBCI{
    -1,            // iFirst
    -1,            // iLast
    128,           // lineNo
    44,            // colNo
    "x_baselined", // aName
    "Baseline",    // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo gc_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    127,        // lineNo
    33,         // colNo
    "Ii2",      // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo hc_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    127,        // lineNo
    22,         // colNo
    "Ii2",      // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo ic_emlrtBCI{
    -1,            // iFirst
    -1,            // iLast
    120,           // lineNo
    50,            // colNo
    "x_baselined", // aName
    "Baseline",    // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo jc_emlrtBCI{
    -1,            // iFirst
    -1,            // iLast
    120,           // lineNo
    44,            // colNo
    "x_baselined", // aName
    "Baseline",    // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo kc_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    113,        // lineNo
    29,         // colNo
    "neg",      // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo lc_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    113,        // lineNo
    16,         // colNo
    "neg",      // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo mc_emlrtBCI{
    -1,            // iFirst
    -1,            // iLast
    104,           // lineNo
    35,            // colNo
    "x_baselined", // aName
    "Baseline",    // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo nc_emlrtBCI{
    -1,            // iFirst
    -1,            // iLast
    104,           // lineNo
    29,            // colNo
    "x_baselined", // aName
    "Baseline",    // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtRTEInfo k_emlrtRTEI{
    130,             // lineNo
    27,              // colNo
    "unaryMinOrMax", // fName
    "C:\\Program "
    "Files\\MATLAB\\R2021b\\toolbox\\eml\\eml\\+coder\\+"
    "internal\\unaryMinOrMax.m" // pName
};

static emlrtBCInfo oc_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    122,        // lineNo
    31,         // colNo
    "x",        // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo pc_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    122,        // lineNo
    36,         // colNo
    "x",        // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo qc_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    123,        // lineNo
    31,         // colNo
    "x",        // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo rc_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    123,        // lineNo
    41,         // colNo
    "x",        // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo sc_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    124,        // lineNo
    30,         // colNo
    "x",        // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo tc_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    130,        // lineNo
    31,         // colNo
    "x",        // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo uc_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    130,        // lineNo
    36,         // colNo
    "x",        // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo vc_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    131,        // lineNo
    31,         // colNo
    "x",        // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo wc_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    131,        // lineNo
    41,         // colNo
    "x",        // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo xc_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    125,        // lineNo
    30,         // colNo
    "x",        // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo yc_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    126,        // lineNo
    30,         // colNo
    "x",        // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo ad_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    126,        // lineNo
    14,         // colNo
    "base",     // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo bd_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    132,        // lineNo
    30,         // colNo
    "x",        // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo cd_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    133,        // lineNo
    30,         // colNo
    "x",        // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo dd_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    134,        // lineNo
    30,         // colNo
    "x",        // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtBCInfo ed_emlrtBCI{
    -1,         // iFirst
    -1,         // iLast
    134,        // lineNo
    14,         // colNo
    "base",     // aName
    "Baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m", // pName
    0                           // checkKind
};

static emlrtRTEInfo l_emlrtRTEI{
    9,               // lineNo
    5,               // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtRTEInfo m_emlrtRTEI{
    10,              // lineNo
    5,               // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtRTEInfo n_emlrtRTEI{
    18,              // lineNo
    30,              // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtRTEInfo o_emlrtRTEI{
    21,              // lineNo
    23,              // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtRTEInfo p_emlrtRTEI{
    22,              // lineNo
    22,              // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtRTEInfo q_emlrtRTEI{
    25,              // lineNo
    9,               // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtRTEInfo r_emlrtRTEI{
    28,              // lineNo
    9,               // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtRTEInfo s_emlrtRTEI{
    31,              // lineNo
    27,              // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtRTEInfo t_emlrtRTEI{
    35,              // lineNo
    9,               // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtRTEInfo u_emlrtRTEI{
    44,              // lineNo
    9,               // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtRTEInfo v_emlrtRTEI{
    46,              // lineNo
    9,               // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtRTEInfo w_emlrtRTEI{
    47,              // lineNo
    9,               // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtRTEInfo x_emlrtRTEI{
    52,              // lineNo
    30,              // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtRTEInfo
    y_emlrtRTEI{
        28,      // lineNo
        9,       // colNo
        "colon", // fName
        "C:\\Program "
        "Files\\MATLAB\\R2021b\\toolbox\\eml\\lib\\matlab\\ops\\colon.m" // pName
    };

static emlrtRTEInfo ab_emlrtRTEI{
    57,              // lineNo
    55,              // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtRTEInfo bb_emlrtRTEI{
    58,              // lineNo
    44,              // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtRTEInfo ib_emlrtRTEI{
    104,             // lineNo
    17,              // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtRTEInfo jb_emlrtRTEI{
    104,             // lineNo
    5,               // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtRTEInfo kb_emlrtRTEI{
    99,              // lineNo
    35,              // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtRTEInfo lb_emlrtRTEI{
    113,             // lineNo
    10,              // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtRTEInfo mb_emlrtRTEI{
    117,             // lineNo
    5,               // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtRTEInfo nb_emlrtRTEI{
    127,             // lineNo
    16,              // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtRTEInfo ob_emlrtRTEI{
    132,             // lineNo
    41,              // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtRTEInfo pb_emlrtRTEI{
    133,             // lineNo
    35,              // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtRTEInfo qb_emlrtRTEI{
    124,             // lineNo
    41,              // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtRTEInfo rb_emlrtRTEI{
    125,             // lineNo
    35,              // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

static emlrtRTEInfo sb_emlrtRTEI{
    138,             // lineNo
    32,              // colNo
    "data_baseline", // fName
    "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data preprocessing\\Matlab "
    "version\\data_baseline.m" // pName
};

// Function Declarations
static real_T Baseline(const emlrtStack *sp,
                       coder::array<real_T, 2U> &x_baselined, real_T start,
                       real_T stop, const coder::array<real_T, 1U> &x,
                       coder::array<real_T, 2U> &base);

static void binary_expand_op(const emlrtStack *sp, coder::array<real_T, 2U> &r,
                             const coder::array<real_T, 1U> &x, int32_T i1,
                             int32_T i2, const coder::array<real_T, 2U> &base_,
                             int32_T i3, int32_T i4);

// Function Definitions
static real_T Baseline(const emlrtStack *sp,
                       coder::array<real_T, 2U> &x_baselined, real_T start,
                       real_T stop, const coder::array<real_T, 1U> &x,
                       coder::array<real_T, 2U> &base)
{
  coder::array<real_T, 2U> b_neg;
  coder::array<real_T, 2U> neg;
  coder::array<int32_T, 2U> ii;
  coder::array<boolean_T, 2U> b_x_baselined;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  emlrtStack g_st;
  emlrtStack h_st;
  emlrtStack st;
  real_T S;
  int32_T iv[2];
  int32_T i;
  int32_T i1;
  int32_T loop_ub;
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
  h_st.prev = &g_st;
  h_st.tls = g_st.tls;
  emlrtHeapReferenceStackEnterFcnR2012b((emlrtCTX)sp);
  covrtLogFcn(&emlrtCoverageInstance, 0, 1);
  covrtLogBasicBlock(&emlrtCoverageInstance, 0, 19);
  //  执行数据中单个段落的对齐，该段落由start和stop来界定，
  //  x_baselined为处理后的数据，x为原始数据，base为基线
  if (start > stop) {
    i = 0;
    i1 = 0;
  } else {
    i = x_baselined.size(1);
    if ((static_cast<int32_T>(start) < 1) ||
        (static_cast<int32_T>(start) > i)) {
      emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(start), 1, i,
                                    &nc_emlrtBCI, (emlrtCTX)sp);
    }
    i = static_cast<int32_T>(start) - 1;
    i1 = x_baselined.size(1);
    if ((static_cast<int32_T>(stop) < 1) || (static_cast<int32_T>(stop) > i1)) {
      emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(stop), 1, i1,
                                    &mc_emlrtBCI, (emlrtCTX)sp);
    }
    i1 = static_cast<int32_T>(stop);
  }
  st.site = &tb_emlrtRSI;
  loop_ub = i1 - i;
  b_x_baselined.set_size(&ib_emlrtRTEI, &st, 1, loop_ub);
  for (i1 = 0; i1 < loop_ub; i1++) {
    b_x_baselined[i1] = (x_baselined[i + i1] < 0.0);
  }
  b_st.site = &kb_emlrtRSI;
  coder::b_eml_find(&b_st, b_x_baselined, ii);
  neg.set_size(&jb_emlrtRTEI, &st, 1, ii.size(1));
  loop_ub = ii.size(1);
  for (i = 0; i < loop_ub; i++) {
    neg[i] = ii[i];
  }
  // if there are no more than half of V1 instances below zero, the for loop
  // should terminate
  if (covrtLogIf(&emlrtCoverageInstance, 0, 0, 8, neg.size(1) < 3)) {
    covrtLogBasicBlock(&emlrtCoverageInstance, 0, 20);
    S = 0.0;
  } else {
    int32_T a;
    int32_T i2;
    int32_T i3;
    int32_T k;
    int32_T last;
    covrtLogBasicBlock(&emlrtCoverageInstance, 0, 21);
    i = neg.size(1);
    neg.set_size(&kb_emlrtRTEI, sp, neg.size(0), neg.size(1) + 1);
    neg[i] = rtInf;
    //  zeroes in Ii indicates that two consecetive valeus are below zero, 5 in
    //  a row indicates 6 places below zero in a row
    if ((neg.size(1) - 1 < 1) || (neg.size(1) - 1 > neg.size(1))) {
      emlrtDynamicBoundsCheckR2012b(neg.size(1) - 1, 1, neg.size(1),
                                    &lc_emlrtBCI, (emlrtCTX)sp);
    }
    if (neg.size(1) < 1) {
      emlrtDynamicBoundsCheckR2012b(neg.size(1), 1, neg.size(1), &kc_emlrtBCI,
                                    (emlrtCTX)sp);
    }
    //  Ii2是一个索引，显示非零的位置
    st.site = &sb_emlrtRSI;
    loop_ub = neg.size(1) - 1;
    b_neg.set_size(&lb_emlrtRTEI, &st, 1, neg.size(1) - 1);
    for (i = 0; i < loop_ub; i++) {
      b_neg[i] = (neg[i] - neg[i + 1]) + 1.0;
    }
    b_st.site = &kb_emlrtRSI;
    coder::eml_find(&b_st, b_neg, ii);
    neg.set_size(&mb_emlrtRTEI, sp, 1, ii.size(1) + 1);
    neg[0] = 0.0;
    loop_ub = ii.size(1);
    for (i = 0; i < loop_ub; i++) {
      neg[i + 1] = ii[i];
    }
    //  如果范围内只有一个非零
    if (covrtLogCond(&emlrtCoverageInstance, 0, 0, 8, neg.size(1) == 1)) {
      real_T b;
      real_T b_b;
      real_T ex;
      covrtLogCond(&emlrtCoverageInstance, 0, 0, 9, true);
      covrtLogMcdc(&emlrtCoverageInstance, 0, 0, 3, true);
      covrtLogIf(&emlrtCoverageInstance, 0, 0, 9, true);
      covrtLogBasicBlock(&emlrtCoverageInstance, 0, 22);
      if (start > stop) {
        i = -1;
        i1 = -1;
      } else {
        i = x_baselined.size(1);
        if ((static_cast<int32_T>(start) < 1) ||
            (static_cast<int32_T>(start) > i)) {
          emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(start), 1, i,
                                        &jc_emlrtBCI, (emlrtCTX)sp);
        }
        i = static_cast<int32_T>(start) - 2;
        i1 = x_baselined.size(1);
        if ((static_cast<int32_T>(stop) < 1) ||
            (static_cast<int32_T>(stop) > i1)) {
          emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(stop), 1, i1,
                                        &ic_emlrtBCI, (emlrtCTX)sp);
        }
        i1 = static_cast<int32_T>(stop) - 1;
      }
      st.site = &rb_emlrtRSI;
      b_st.site = &ub_emlrtRSI;
      c_st.site = &vb_emlrtRSI;
      d_st.site = &wb_emlrtRSI;
      last = i1 - i;
      if (last < 1) {
        emlrtErrorWithMessageIdR2018a(
            &d_st, &k_emlrtRTEI, "Coder:toolbox:eml_min_or_max_varDimZero",
            "Coder:toolbox:eml_min_or_max_varDimZero", 0);
      }
      e_st.site = &xb_emlrtRSI;
      if (last <= 2) {
        if (last == 1) {
          loop_ub = 1;
        } else {
          b = x_baselined[i1];
          if ((x_baselined[i + 1] > b) ||
              (muDoubleScalarIsNaN(x_baselined[i + 1]) &&
               (!muDoubleScalarIsNaN(b)))) {
            loop_ub = 2;
          } else {
            loop_ub = 1;
          }
        }
      } else {
        f_st.site = &ac_emlrtRSI;
        if (!muDoubleScalarIsNaN(x_baselined[i + 1])) {
          loop_ub = 1;
        } else {
          boolean_T exitg1;
          loop_ub = 0;
          g_st.site = &bc_emlrtRSI;
          if (last > 2147483646) {
            h_st.site = &x_emlrtRSI;
            coder::check_forloop_overflow_error(&h_st);
          }
          k = 2;
          exitg1 = false;
          while ((!exitg1) && (k <= last)) {
            if (!muDoubleScalarIsNaN(x_baselined[i + k])) {
              loop_ub = k;
              exitg1 = true;
            } else {
              k++;
            }
          }
        }
        if (loop_ub == 0) {
          loop_ub = 1;
        } else {
          boolean_T overflow;
          f_st.site = &yb_emlrtRSI;
          ex = x_baselined[i + loop_ub];
          a = loop_ub + 1;
          g_st.site = &cc_emlrtRSI;
          overflow = ((loop_ub + 1 <= last) && (last > 2147483646));
          if (overflow) {
            h_st.site = &x_emlrtRSI;
            coder::check_forloop_overflow_error(&h_st);
          }
          for (k = a; k <= last; k++) {
            b = x_baselined[i + k];
            if (ex > b) {
              ex = b;
              loop_ub = k;
            }
          }
        }
      }
      S = (static_cast<real_T>(loop_ub) + start) - 1.0;
      if ((static_cast<int32_T>(S) < 1) ||
          (static_cast<int32_T>(S) > x.size(0))) {
        emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(S), 1, x.size(0),
                                      &oc_emlrtBCI, (emlrtCTX)sp);
      }
      if ((static_cast<int32_T>(start - 1.0) < 1) ||
          (static_cast<int32_T>(start - 1.0) > x.size(0))) {
        emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(start - 1.0), 1,
                                      x.size(0), &pc_emlrtBCI, (emlrtCTX)sp);
      }
      b = (x[static_cast<int32_T>(S) - 1] -
           x[static_cast<int32_T>(start - 1.0) - 1]) /
          ((S - start) + 1.0);
      if ((static_cast<int32_T>(stop + 1.0) < 1) ||
          (static_cast<int32_T>(stop + 1.0) > x.size(0))) {
        emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(stop + 1.0), 1,
                                      x.size(0), &qc_emlrtBCI, (emlrtCTX)sp);
      }
      if ((static_cast<int32_T>(S) < 1) ||
          (static_cast<int32_T>(S) > x.size(0))) {
        emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(S), 1, x.size(0),
                                      &rc_emlrtBCI, (emlrtCTX)sp);
      }
      b_b = (x[static_cast<int32_T>(stop + 1.0) - 1] -
             x[static_cast<int32_T>(S) - 1]) /
            ((stop - S) + 1.0);
      if (start > S - 1.0) {
        i = 0;
        i1 = 0;
      } else {
        i = base.size(1);
        if ((static_cast<int32_T>(start) < 1) ||
            (static_cast<int32_T>(start) > i)) {
          emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(start), 1, i,
                                        &bc_emlrtBCI, (emlrtCTX)sp);
        }
        i = static_cast<int32_T>(start) - 1;
        i1 = base.size(1);
        if ((static_cast<int32_T>(S - 1.0) < 1) ||
            (static_cast<int32_T>(S - 1.0) > i1)) {
          emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(S - 1.0), 1, i1,
                                        &ac_emlrtBCI, (emlrtCTX)sp);
        }
        i1 = static_cast<int32_T>(S - 1.0);
      }
      ex = S - start;
      if (muDoubleScalarIsNaN(ex)) {
        neg.set_size(&y_emlrtRTEI, sp, 1, 1);
        neg[0] = rtNaN;
      } else if (ex < 1.0) {
        neg.set_size(&y_emlrtRTEI, sp, neg.size(0), 0);
      } else {
        loop_ub = static_cast<int32_T>(muDoubleScalarFloor(ex - 1.0));
        neg.set_size(&y_emlrtRTEI, sp, 1, loop_ub + 1);
        for (i2 = 0; i2 <= loop_ub; i2++) {
          neg[i2] = static_cast<real_T>(i2) + 1.0;
        }
      }
      neg.set_size(&qb_emlrtRTEI, sp, 1, neg.size(1));
      loop_ub = neg.size(1) - 1;
      for (i2 = 0; i2 <= loop_ub; i2++) {
        neg[i2] = neg[i2] * b;
      }
      i1 -= i;
      if (i1 != neg.size(1)) {
        emlrtSubAssignSizeCheck1dR2017a(i1, neg.size(1), &l_emlrtECI,
                                        (emlrtCTX)sp);
      }
      if ((static_cast<int32_T>(start - 1.0) < 1) ||
          (static_cast<int32_T>(start - 1.0) > x.size(0))) {
        emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(start - 1.0), 1,
                                      x.size(0), &sc_emlrtBCI, (emlrtCTX)sp);
      }
      loop_ub = neg.size(1);
      for (i1 = 0; i1 < loop_ub; i1++) {
        base[i + i1] = x[static_cast<int32_T>(start - 1.0) - 1] + neg[i1];
      }
      if (S + 1.0 > stop) {
        i = 0;
        i1 = 0;
      } else {
        i = base.size(1);
        if ((static_cast<int32_T>(S + 1.0) < 1) ||
            (static_cast<int32_T>(S + 1.0) > i)) {
          emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(S + 1.0), 1, i,
                                        &yb_emlrtBCI, (emlrtCTX)sp);
        }
        i = static_cast<int32_T>(S + 1.0) - 1;
        i1 = base.size(1);
        if ((static_cast<int32_T>(stop) < 1) ||
            (static_cast<int32_T>(stop) > i1)) {
          emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(stop), 1, i1,
                                        &xb_emlrtBCI, (emlrtCTX)sp);
        }
        i1 = static_cast<int32_T>(stop);
      }
      b = stop - S;
      if (muDoubleScalarIsNaN(b)) {
        neg.set_size(&y_emlrtRTEI, sp, 1, 1);
        neg[0] = rtNaN;
      } else if (b < 1.0) {
        neg.set_size(&y_emlrtRTEI, sp, neg.size(0), 0);
      } else {
        loop_ub = static_cast<int32_T>(muDoubleScalarFloor(b - 1.0));
        neg.set_size(&y_emlrtRTEI, sp, 1, loop_ub + 1);
        for (i2 = 0; i2 <= loop_ub; i2++) {
          neg[i2] = static_cast<real_T>(i2) + 1.0;
        }
      }
      neg.set_size(&rb_emlrtRTEI, sp, 1, neg.size(1));
      loop_ub = neg.size(1) - 1;
      for (i2 = 0; i2 <= loop_ub; i2++) {
        neg[i2] = neg[i2] * b_b;
      }
      i1 -= i;
      if (i1 != neg.size(1)) {
        emlrtSubAssignSizeCheck1dR2017a(i1, neg.size(1), &k_emlrtECI,
                                        (emlrtCTX)sp);
      }
      if ((static_cast<int32_T>(S) < 1) ||
          (static_cast<int32_T>(S) > x.size(0))) {
        emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(S), 1, x.size(0),
                                      &xc_emlrtBCI, (emlrtCTX)sp);
      }
      loop_ub = neg.size(1);
      for (i1 = 0; i1 < loop_ub; i1++) {
        base[i + i1] = x[static_cast<int32_T>(S) - 1] + neg[i1];
      }
      if ((static_cast<int32_T>(S) < 1) ||
          (static_cast<int32_T>(S) > x.size(0))) {
        emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(S), 1, x.size(0),
                                      &yc_emlrtBCI, (emlrtCTX)sp);
      }
      i = base.size(1);
      if ((static_cast<int32_T>(S) < 1) || (static_cast<int32_T>(S) > i)) {
        emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(S), 1, i,
                                      &ad_emlrtBCI, (emlrtCTX)sp);
      }
      base[static_cast<int32_T>(S) - 1] = x[static_cast<int32_T>(S) - 1];
    } else {
      real_T b;
      real_T ex;
      covrtLogMcdc(&emlrtCoverageInstance, 0, 0, 3, false);
      covrtLogIf(&emlrtCoverageInstance, 0, 0, 9, false);
      if (neg.size(1) < 1) {
        emlrtDynamicBoundsCheckR2012b(neg.size(1), 1, neg.size(1), &hc_emlrtBCI,
                                      (emlrtCTX)sp);
      }
      loop_ub = neg.size(1) - 1;
      if ((neg.size(1) - 1 < 1) || (neg.size(1) - 1 > neg.size(1))) {
        emlrtDynamicBoundsCheckR2012b(neg.size(1) - 1, 1, neg.size(1),
                                      &gc_emlrtBCI, (emlrtCTX)sp);
      }
      st.site = &qb_emlrtRSI;
      b_neg.set_size(&nb_emlrtRTEI, &st, 1, neg.size(1) - 1);
      for (i = 0; i < loop_ub; i++) {
        b_neg[i] = static_cast<real_T>(static_cast<int32_T>(neg[i + 1])) -
                   static_cast<real_T>(static_cast<int32_T>(neg[i]));
      }
      b_st.site = &dc_emlrtRSI;
      c_st.site = &ec_emlrtRSI;
      d_st.site = &fc_emlrtRSI;
      if (b_neg.size(1) < 1) {
        emlrtErrorWithMessageIdR2018a(
            &d_st, &k_emlrtRTEI, "Coder:toolbox:eml_min_or_max_varDimZero",
            "Coder:toolbox:eml_min_or_max_varDimZero", 0);
      }
      e_st.site = &gc_emlrtRSI;
      f_st.site = &hc_emlrtRSI;
      last = b_neg.size(1);
      if (b_neg.size(1) <= 2) {
        if (b_neg.size(1) == 1) {
          ex = b_neg[0];
        } else if (b_neg[0] < b_neg[1]) {
          ex = b_neg[1];
        } else {
          ex = b_neg[0];
        }
      } else {
        g_st.site = &ac_emlrtRSI;
        g_st.site = &yb_emlrtRSI;
        ex = b_neg[0];
        for (k = 2; k <= last; k++) {
          b = b_neg[k - 1];
          if (ex < b) {
            ex = b;
          }
        }
      }
      if (covrtLogIf(&emlrtCoverageInstance, 0, 0, 10, ex > 3.0)) {
        real_T b_b;
        covrtLogBasicBlock(&emlrtCoverageInstance, 0, 23);
        if (start > stop) {
          i = -1;
          i1 = -1;
        } else {
          i = x_baselined.size(1);
          if ((static_cast<int32_T>(start) < 1) ||
              (static_cast<int32_T>(start) > i)) {
            emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(start), 1, i,
                                          &fc_emlrtBCI, (emlrtCTX)sp);
          }
          i = static_cast<int32_T>(start) - 2;
          i1 = x_baselined.size(1);
          if ((static_cast<int32_T>(stop) < 1) ||
              (static_cast<int32_T>(stop) > i1)) {
            emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(stop), 1, i1,
                                          &ec_emlrtBCI, (emlrtCTX)sp);
          }
          i1 = static_cast<int32_T>(stop) - 1;
        }
        st.site = &pb_emlrtRSI;
        b_st.site = &ub_emlrtRSI;
        c_st.site = &vb_emlrtRSI;
        d_st.site = &wb_emlrtRSI;
        last = i1 - i;
        if (last < 1) {
          emlrtErrorWithMessageIdR2018a(
              &d_st, &k_emlrtRTEI, "Coder:toolbox:eml_min_or_max_varDimZero",
              "Coder:toolbox:eml_min_or_max_varDimZero", 0);
        }
        e_st.site = &xb_emlrtRSI;
        if (last <= 2) {
          if (last == 1) {
            loop_ub = 1;
          } else {
            b = x_baselined[i1];
            if ((x_baselined[i + 1] > b) ||
                (muDoubleScalarIsNaN(x_baselined[i + 1]) &&
                 (!muDoubleScalarIsNaN(b)))) {
              loop_ub = 2;
            } else {
              loop_ub = 1;
            }
          }
        } else {
          f_st.site = &ac_emlrtRSI;
          if (!muDoubleScalarIsNaN(x_baselined[i + 1])) {
            loop_ub = 1;
          } else {
            boolean_T exitg1;
            loop_ub = 0;
            g_st.site = &bc_emlrtRSI;
            if (last > 2147483646) {
              h_st.site = &x_emlrtRSI;
              coder::check_forloop_overflow_error(&h_st);
            }
            k = 2;
            exitg1 = false;
            while ((!exitg1) && (k <= last)) {
              if (!muDoubleScalarIsNaN(x_baselined[i + k])) {
                loop_ub = k;
                exitg1 = true;
              } else {
                k++;
              }
            }
          }
          if (loop_ub == 0) {
            loop_ub = 1;
          } else {
            boolean_T overflow;
            f_st.site = &yb_emlrtRSI;
            ex = x_baselined[i + loop_ub];
            a = loop_ub + 1;
            g_st.site = &cc_emlrtRSI;
            overflow = ((loop_ub + 1 <= last) && (last > 2147483646));
            if (overflow) {
              h_st.site = &x_emlrtRSI;
              coder::check_forloop_overflow_error(&h_st);
            }
            for (k = a; k <= last; k++) {
              b = x_baselined[i + k];
              if (ex > b) {
                ex = b;
                loop_ub = k;
              }
            }
          }
        }
        S = (static_cast<real_T>(loop_ub) + start) - 1.0;
        if ((static_cast<int32_T>(S) < 1) ||
            (static_cast<int32_T>(S) > x.size(0))) {
          emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(S), 1, x.size(0),
                                        &tc_emlrtBCI, (emlrtCTX)sp);
        }
        if ((static_cast<int32_T>(start - 1.0) < 1) ||
            (static_cast<int32_T>(start - 1.0) > x.size(0))) {
          emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(start - 1.0), 1,
                                        x.size(0), &uc_emlrtBCI, (emlrtCTX)sp);
        }
        ex = S - start;
        b = (x[static_cast<int32_T>(S) - 1] -
             x[static_cast<int32_T>(start - 1.0) - 1]) /
            (ex + 1.0);
        if ((static_cast<int32_T>(stop + 1.0) < 1) ||
            (static_cast<int32_T>(stop + 1.0) > x.size(0))) {
          emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(stop + 1.0), 1,
                                        x.size(0), &vc_emlrtBCI, (emlrtCTX)sp);
        }
        if ((static_cast<int32_T>(S) < 1) ||
            (static_cast<int32_T>(S) > x.size(0))) {
          emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(S), 1, x.size(0),
                                        &wc_emlrtBCI, (emlrtCTX)sp);
        }
        b_b = (x[static_cast<int32_T>(stop + 1.0) - 1] -
               x[static_cast<int32_T>(S) - 1]) /
              ((stop - S) + 1.0);
        if (start > S - 1.0) {
          i = 0;
          i1 = 0;
        } else {
          i = base.size(1);
          if ((static_cast<int32_T>(start) < 1) ||
              (static_cast<int32_T>(start) > i)) {
            emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(start), 1, i,
                                          &wb_emlrtBCI, (emlrtCTX)sp);
          }
          i = static_cast<int32_T>(start) - 1;
          i1 = base.size(1);
          if ((static_cast<int32_T>(S - 1.0) < 1) ||
              (static_cast<int32_T>(S - 1.0) > i1)) {
            emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(S - 1.0), 1, i1,
                                          &vb_emlrtBCI, (emlrtCTX)sp);
          }
          i1 = static_cast<int32_T>(S - 1.0);
        }
        if (muDoubleScalarIsNaN(ex)) {
          neg.set_size(&y_emlrtRTEI, sp, 1, 1);
          neg[0] = rtNaN;
        } else if (ex < 1.0) {
          neg.set_size(&y_emlrtRTEI, sp, neg.size(0), 0);
        } else {
          loop_ub = static_cast<int32_T>(muDoubleScalarFloor(ex - 1.0));
          neg.set_size(&y_emlrtRTEI, sp, 1, loop_ub + 1);
          for (i2 = 0; i2 <= loop_ub; i2++) {
            neg[i2] = static_cast<real_T>(i2) + 1.0;
          }
        }
        neg.set_size(&ob_emlrtRTEI, sp, 1, neg.size(1));
        loop_ub = neg.size(1) - 1;
        for (i2 = 0; i2 <= loop_ub; i2++) {
          neg[i2] = neg[i2] * b;
        }
        i1 -= i;
        if (i1 != neg.size(1)) {
          emlrtSubAssignSizeCheck1dR2017a(i1, neg.size(1), &j_emlrtECI,
                                          (emlrtCTX)sp);
        }
        if ((static_cast<int32_T>(start - 1.0) < 1) ||
            (static_cast<int32_T>(start - 1.0) > x.size(0))) {
          emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(start - 1.0), 1,
                                        x.size(0), &bd_emlrtBCI, (emlrtCTX)sp);
        }
        loop_ub = neg.size(1);
        for (i1 = 0; i1 < loop_ub; i1++) {
          base[i + i1] = x[static_cast<int32_T>(start - 1.0) - 1] + neg[i1];
        }
        if (S + 1.0 > stop) {
          i = 0;
          i1 = 0;
        } else {
          i = base.size(1);
          if ((static_cast<int32_T>(S + 1.0) < 1) ||
              (static_cast<int32_T>(S + 1.0) > i)) {
            emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(S + 1.0), 1, i,
                                          &ub_emlrtBCI, (emlrtCTX)sp);
          }
          i = static_cast<int32_T>(S + 1.0) - 1;
          i1 = base.size(1);
          if ((static_cast<int32_T>(stop) < 1) ||
              (static_cast<int32_T>(stop) > i1)) {
            emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(stop), 1, i1,
                                          &tb_emlrtBCI, (emlrtCTX)sp);
          }
          i1 = static_cast<int32_T>(stop);
        }
        b = stop - S;
        if (muDoubleScalarIsNaN(b)) {
          neg.set_size(&y_emlrtRTEI, sp, 1, 1);
          neg[0] = rtNaN;
        } else if (b < 1.0) {
          neg.set_size(&y_emlrtRTEI, sp, neg.size(0), 0);
        } else {
          loop_ub = static_cast<int32_T>(muDoubleScalarFloor(b - 1.0));
          neg.set_size(&y_emlrtRTEI, sp, 1, loop_ub + 1);
          for (i2 = 0; i2 <= loop_ub; i2++) {
            neg[i2] = static_cast<real_T>(i2) + 1.0;
          }
        }
        neg.set_size(&pb_emlrtRTEI, sp, 1, neg.size(1));
        loop_ub = neg.size(1) - 1;
        for (i2 = 0; i2 <= loop_ub; i2++) {
          neg[i2] = neg[i2] * b_b;
        }
        i1 -= i;
        if (i1 != neg.size(1)) {
          emlrtSubAssignSizeCheck1dR2017a(i1, neg.size(1), &i_emlrtECI,
                                          (emlrtCTX)sp);
        }
        if ((static_cast<int32_T>(S) < 1) ||
            (static_cast<int32_T>(S) > x.size(0))) {
          emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(S), 1, x.size(0),
                                        &cd_emlrtBCI, (emlrtCTX)sp);
        }
        loop_ub = neg.size(1);
        for (i1 = 0; i1 < loop_ub; i1++) {
          base[i + i1] = x[static_cast<int32_T>(S) - 1] + neg[i1];
        }
        if ((static_cast<int32_T>(S) < 1) ||
            (static_cast<int32_T>(S) > x.size(0))) {
          emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(S), 1, x.size(0),
                                        &dd_emlrtBCI, (emlrtCTX)sp);
        }
        i = base.size(1);
        if ((static_cast<int32_T>(S) < 1) || (static_cast<int32_T>(S) > i)) {
          emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(S), 1, i,
                                        &ed_emlrtBCI, (emlrtCTX)sp);
        }
        base[static_cast<int32_T>(S) - 1] = x[static_cast<int32_T>(S) - 1];
      } else {
        covrtLogBasicBlock(&emlrtCoverageInstance, 0, 24);
        S = 0.0;
      }
    }
    covrtLogBasicBlock(&emlrtCoverageInstance, 0, 25);
    if (start > stop) {
      i = -1;
      i1 = -1;
    } else {
      if ((static_cast<int32_T>(start) < 1) ||
          (static_cast<int32_T>(start) > x.size(0))) {
        emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(start), 1, x.size(0),
                                      &dc_emlrtBCI, (emlrtCTX)sp);
      }
      i = static_cast<int32_T>(start) - 2;
      if ((static_cast<int32_T>(stop) < 1) ||
          (static_cast<int32_T>(stop) > x.size(0))) {
        emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(stop), 1, x.size(0),
                                      &cc_emlrtBCI, (emlrtCTX)sp);
      }
      i1 = static_cast<int32_T>(stop) - 1;
    }
    iv[0] = 1;
    loop_ub = i1 - i;
    iv[1] = loop_ub;
    st.site = &ob_emlrtRSI;
    coder::internal::indexShapeCheck(&st, x.size(0), iv);
    if (start > stop) {
      i2 = -1;
      a = -1;
    } else {
      i2 = base.size(1);
      if ((static_cast<int32_T>(start) < 1) ||
          (static_cast<int32_T>(start) > i2)) {
        emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(start), 1, i2,
                                      &sb_emlrtBCI, (emlrtCTX)sp);
      }
      i2 = static_cast<int32_T>(start) - 2;
      a = base.size(1);
      if ((static_cast<int32_T>(stop) < 1) ||
          (static_cast<int32_T>(stop) > a)) {
        emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(stop), 1, a,
                                      &rb_emlrtBCI, (emlrtCTX)sp);
      }
      a = static_cast<int32_T>(stop) - 1;
    }
    last = a - i2;
    if ((loop_ub != last) && ((loop_ub != 1) && (last != 1))) {
      emlrtDimSizeImpxCheckR2021b(loop_ub, last, &h_emlrtECI, (emlrtCTX)sp);
    }
    if (start > stop) {
      k = 0;
      i3 = 0;
    } else {
      k = x_baselined.size(1);
      if ((static_cast<int32_T>(start) < 1) ||
          (static_cast<int32_T>(start) > k)) {
        emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(start), 1, k,
                                      &qb_emlrtBCI, (emlrtCTX)sp);
      }
      k = static_cast<int32_T>(start) - 1;
      i3 = x_baselined.size(1);
      if ((static_cast<int32_T>(stop) < 1) ||
          (static_cast<int32_T>(stop) > i3)) {
        emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(stop), 1, i3,
                                      &pb_emlrtBCI, (emlrtCTX)sp);
      }
      i3 = static_cast<int32_T>(stop);
    }
    if (loop_ub == last) {
      neg.set_size(&sb_emlrtRTEI, sp, 1, loop_ub);
      for (i1 = 0; i1 < loop_ub; i1++) {
        neg[i1] = x[(i + i1) + 1] - base[(i2 + i1) + 1];
      }
    } else {
      st.site = &ob_emlrtRSI;
      binary_expand_op(&st, neg, x, i + 1, i1, base, i2 + 1, a);
    }
    i = i3 - k;
    if (i != neg.size(1)) {
      emlrtSubAssignSizeCheck1dR2017a(i, neg.size(1), &g_emlrtECI,
                                      (emlrtCTX)sp);
    }
    loop_ub = neg.size(1);
    for (i = 0; i < loop_ub; i++) {
      x_baselined[k + i] = neg[i];
    }
  }
  emlrtHeapReferenceStackLeaveFcnR2012b((emlrtCTX)sp);
  return S;
}

static void binary_expand_op(const emlrtStack *sp, coder::array<real_T, 2U> &r,
                             const coder::array<real_T, 1U> &x, int32_T i1,
                             int32_T i2, const coder::array<real_T, 2U> &base_,
                             int32_T i3, int32_T i4)
{
  int32_T i;
  int32_T loop_ub;
  int32_T stride_0_1;
  int32_T stride_1_1;
  if ((i4 - i3) + 1 == 1) {
    i = (i2 - i1) + 1;
  } else {
    i = (i4 - i3) + 1;
  }
  r.set_size(&bb_emlrtRTEI, sp, 1, i);
  stride_0_1 = ((i2 - i1) + 1 != 1);
  stride_1_1 = ((i4 - i3) + 1 != 1);
  if ((i4 - i3) + 1 == 1) {
    loop_ub = (i2 - i1) + 1;
  } else {
    loop_ub = (i4 - i3) + 1;
  }
  for (i = 0; i < loop_ub; i++) {
    r[i] = x[i1 + i * stride_0_1] - base_[i3 + i * stride_1_1];
  }
}

void data_baseline(const emlrtStack *sp, const coder::array<real_T, 2U> &data,
                   real_T peak_threshold, real_T smooth_window,
                   real_T noise_window,
                   coder::array<real_T, 2U> &data_baselined,
                   coder::array<real_T, 2U> &base)
{
  coder::array<real_T, 2U> Sx;
  coder::array<real_T, 2U> a1;
  coder::array<real_T, 2U> b_data;
  coder::array<real_T, 2U> base_;
  coder::array<real_T, 2U> r;
  coder::array<real_T, 2U> x_baselined;
  coder::array<real_T, 1U> b_N;
  coder::array<real_T, 1U> noise;
  coder::array<real_T, 1U> x;
  coder::array<boolean_T, 1U> N;
  emlrtStack b_st;
  emlrtStack st;
  real_T S2;
  real_T b;
  real_T iv;
  real_T j;
  real_T stop_data;
  real_T vv;
  int32_T b_iv[2];
  int32_T b_i;
  int32_T b_loop_ub;
  int32_T c_loop_ub;
  int32_T d_loop_ub;
  int32_T e_loop_ub;
  int32_T f_loop_ub;
  int32_T i;
  int32_T i1;
  int32_T i10;
  int32_T i2;
  int32_T i3;
  int32_T i4;
  int32_T i5;
  int32_T i6;
  int32_T i7;
  int32_T i8;
  int32_T i9;
  int32_T ii_data;
  int32_T ii_size;
  int32_T loop_ub;
  int32_T m1;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  emlrtHeapReferenceStackEnterFcnR2012b((emlrtCTX)sp);
  covrtLogFcn(&emlrtCoverageInstance, 0, 0);
  covrtLogBasicBlock(&emlrtCoverageInstance, 0, 0);
  //  对传入的二维数据data执行平滑、基线校准，并输出为data_baselined,
  //  base为确定的基线
  //    此处显示详细说明
  //  smooth_window, noise_window最好为偶数
  //  peak_threshold = 8000，smooth_window=4，noise_window=6
  // Smoothing (moving average)
  m1 = data.size(0);
  if (data.size(0) < 1) {
    a1.set_size(&l_emlrtRTEI, sp, 1, 0);
  } else {
    a1.set_size(&l_emlrtRTEI, sp, 1, data.size(0));
    loop_ub = data.size(0) - 1;
    for (i = 0; i <= loop_ub; i++) {
      a1[i] = static_cast<real_T>(i) + 1.0;
    }
  }
  Sx.set_size(&m_emlrtRTEI, sp, data.size(0), data.size(1));
  loop_ub = data.size(0) * data.size(1);
  for (i = 0; i < loop_ub; i++) {
    Sx[i] = 0.0;
  }
  iv = muDoubleScalarRound(smooth_window / 2.0);
  vv = (static_cast<real_T>(data.size(0)) - iv) + 1.0;
  // assignin('base','vv',vv);
  // assignin('base','m1',m1);
  //  assignin('base','iv',iv);
  i = static_cast<int32_T>(vv + (1.0 - smooth_window));
  emlrtForLoopVectorCheckR2021a(smooth_window, 1.0, vv, mxDOUBLE_CLASS, i,
                                &b_emlrtRTEI, (emlrtCTX)sp);
  if (0 <= i - 1) {
    i1 = data.size(1);
    ii_data = data.size(1);
    b_iv[0] = 1;
  }
  for (b_i = 0; b_i < i; b_i++) {
    vv = smooth_window + static_cast<real_T>(b_i);
    covrtLogFor(&emlrtCoverageInstance, 0, 0, 0, 1);
    covrtLogBasicBlock(&emlrtCoverageInstance, 0, 1);
    b = (vv - smooth_window) + 1.0;
    if (b != static_cast<int32_T>(muDoubleScalarFloor(b))) {
      emlrtIntegerCheckR2012b(b, &f_emlrtDCI, (emlrtCTX)sp);
    }
    if ((static_cast<int32_T>(b) < 1) ||
        (static_cast<int32_T>(b) > a1.size(1))) {
      emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(b), 1, a1.size(1),
                                    &u_emlrtBCI, (emlrtCTX)sp);
    }
    b = a1[static_cast<int32_T>(b) - 1];
    if (vv != static_cast<int32_T>(muDoubleScalarFloor(vv))) {
      emlrtIntegerCheckR2012b(vv, &e_emlrtDCI, (emlrtCTX)sp);
    }
    if ((static_cast<int32_T>(vv) < 1) ||
        (static_cast<int32_T>(vv) > a1.size(1))) {
      emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(vv), 1, a1.size(1),
                                    &t_emlrtBCI, (emlrtCTX)sp);
    }
    S2 = a1[static_cast<int32_T>(vv) - 1];
    if (b > S2) {
      i6 = 0;
      i7 = 0;
    } else {
      if (b != static_cast<int32_T>(b)) {
        emlrtIntegerCheckR2012b(b, &d_emlrtDCI, (emlrtCTX)sp);
      }
      if (static_cast<int32_T>(b) > data.size(0)) {
        emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(b), 1, data.size(0),
                                      &s_emlrtBCI, (emlrtCTX)sp);
      }
      i6 = static_cast<int32_T>(b) - 1;
      if (S2 != static_cast<int32_T>(S2)) {
        emlrtIntegerCheckR2012b(a1[static_cast<int32_T>(vv) - 1], &c_emlrtDCI,
                                (emlrtCTX)sp);
      }
      i7 = static_cast<int32_T>(a1[static_cast<int32_T>(vv) - 1]);
      if (i7 > data.size(0)) {
        emlrtDynamicBoundsCheckR2012b(i7, 1, data.size(0), &r_emlrtBCI,
                                      (emlrtCTX)sp);
      }
    }
    b = (vv - iv) + 1.0;
    if (b != static_cast<int32_T>(muDoubleScalarFloor(b))) {
      emlrtIntegerCheckR2012b(b, &b_emlrtDCI, (emlrtCTX)sp);
    }
    if ((static_cast<int32_T>(b) < 1) ||
        (static_cast<int32_T>(b) > Sx.size(0))) {
      emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(b), 1, Sx.size(0),
                                    &q_emlrtBCI, (emlrtCTX)sp);
    }
    loop_ub = i7 - i6;
    b_data.set_size(&n_emlrtRTEI, sp, loop_ub, i1);
    for (i7 = 0; i7 < ii_data; i7++) {
      for (i10 = 0; i10 < loop_ub; i10++) {
        b_data[i10 + b_data.size(0) * i7] =
            data[(i6 + i10) + data.size(0) * i7];
      }
    }
    st.site = &emlrtRSI;
    coder::mean(&st, b_data, r);
    b_iv[1] = Sx.size(1);
    emlrtSubAssignSizeCheckR2012b(&b_iv[0], 2, r.size(), 2, &f_emlrtECI,
                                  (emlrtCTX)sp);
    loop_ub = r.size(1);
    for (i6 = 0; i6 < loop_ub; i6++) {
      Sx[(static_cast<int32_T>(b) + Sx.size(0) * i6) - 1] = r[i6];
    }
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b((emlrtCTX)sp);
    }
  }
  covrtLogFor(&emlrtCoverageInstance, 0, 0, 0, 0);
  covrtLogBasicBlock(&emlrtCoverageInstance, 0, 2);
  data_baselined.set_size(&o_emlrtRTEI, sp, data.size(1), data.size(0));
  base.set_size(&p_emlrtRTEI, sp, data.size(1), data.size(0));
  i = data.size(1);
  if (0 <= data.size(1) - 1) {
    i2 = data.size(0);
    b_loop_ub = data.size(0);
    j = static_cast<real_T>(data.size(0)) - noise_window;
    c_loop_ub = data.size(0);
    i3 = static_cast<int32_T>(j);
    if (1 > data.size(0)) {
      d_loop_ub = 0;
    } else {
      d_loop_ub = data.size(0);
    }
    i4 = data.size(0);
    i5 = data.size(0);
    e_loop_ub = data.size(0);
    f_loop_ub = data.size(0);
    i8 = data.size(0);
  }
  for (int32_T b_I{0}; b_I < i; b_I++) {
    boolean_T guard1{false};
    covrtLogFor(&emlrtCoverageInstance, 0, 0, 1, 1);
    covrtLogBasicBlock(&emlrtCoverageInstance, 0, 3);
    // from sample 1 to n1
    if (b_I + 1 > Sx.size(1)) {
      emlrtDynamicBoundsCheckR2012b(b_I + 1, 1, Sx.size(1), &p_emlrtBCI,
                                    (emlrtCTX)sp);
    }
    if (b_I + 1 > data.size(1)) {
      emlrtDynamicBoundsCheckR2012b(b_I + 1, 1, data.size(1), &o_emlrtBCI,
                                    (emlrtCTX)sp);
    }
    x.set_size(&q_emlrtRTEI, sp, i2);
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      x[i1] = data[i1 + data.size(0) * b_I];
    }
    a1.set_size(&r_emlrtRTEI, sp, 1, m1);
    for (i1 = 0; i1 < c_loop_ub; i1++) {
      a1[i1] = 0.0;
    }
    emlrtForLoopVectorCheckR2021a(1.0, 1.0, j, mxDOUBLE_CLASS,
                                  static_cast<int32_T>(j), &emlrtRTEI,
                                  (emlrtCTX)sp);
    if (0 <= i3 - 1) {
      i9 = Sx.size(0);
      b_iv[0] = 1;
    }
    for (b_i = 0; b_i < i3; b_i++) {
      covrtLogFor(&emlrtCoverageInstance, 0, 0, 2, 1);
      covrtLogBasicBlock(&emlrtCoverageInstance, 0, 4);
      b = ((static_cast<real_T>(b_i) + 1.0) + noise_window) - 1.0;
      if (static_cast<real_T>(b_i) + 1.0 > b) {
        i1 = 0;
        i6 = 0;
      } else {
        if ((static_cast<int32_T>(b_i + 1U) < 1) ||
            (static_cast<int32_T>(b_i + 1U) > Sx.size(0))) {
          emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(b_i + 1U), 1,
                                        Sx.size(0), &n_emlrtBCI, (emlrtCTX)sp);
        }
        i1 = b_i;
        if (b != static_cast<int32_T>(muDoubleScalarFloor(b))) {
          emlrtIntegerCheckR2012b(b, &emlrtDCI, (emlrtCTX)sp);
        }
        if ((static_cast<int32_T>(b) < 1) ||
            (static_cast<int32_T>(b) > Sx.size(0))) {
          emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(b), 1, Sx.size(0),
                                        &m_emlrtBCI, (emlrtCTX)sp);
        }
        i6 = static_cast<int32_T>(b);
      }
      loop_ub = i6 - i1;
      b_iv[1] = loop_ub;
      st.site = &b_emlrtRSI;
      coder::internal::indexShapeCheck(&st, i9, b_iv);
      noise.set_size(&s_emlrtRTEI, sp, loop_ub);
      for (i6 = 0; i6 < loop_ub; i6++) {
        noise[i6] = Sx[(i1 + i6) + Sx.size(0) * b_I];
      }
      if ((static_cast<int32_T>(b_i + 1U) < 1) ||
          (static_cast<int32_T>(b_i + 1U) > a1.size(1))) {
        emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(b_i + 1U), 1,
                                      a1.size(1), &w_emlrtBCI, (emlrtCTX)sp);
      }
      st.site = &b_emlrtRSI;
      a1[b_i] = coder::b_std(&st, noise);
      if (*emlrtBreakCheckR2012bFlagVar != 0) {
        emlrtBreakCheckR2012b((emlrtCTX)sp);
      }
    }
    covrtLogFor(&emlrtCoverageInstance, 0, 0, 2, 0);
    covrtLogBasicBlock(&emlrtCoverageInstance, 0, 5);
    // Noiese is separated from peaks by making a matrix only containing noise:
    noise.set_size(&t_emlrtRTEI, sp, d_loop_ub);
    for (i1 = 0; i1 < d_loop_ub; i1++) {
      noise[i1] = data[i1 + data.size(0) * b_I];
    }
    for (b_i = 0; b_i <= i4 - 6; b_i++) {
      covrtLogFor(&emlrtCoverageInstance, 0, 0, 3, 1);
      if (b_i + 6 > a1.size(1)) {
        emlrtDynamicBoundsCheckR2012b(b_i + 6, 1, a1.size(1), &v_emlrtBCI,
                                      (emlrtCTX)sp);
      }
      guard1 = false;
      if (covrtLogCond(&emlrtCoverageInstance, 0, 0, 0,
                       a1[b_i + 5] < peak_threshold)) {
        if (b_i + 1 > a1.size(1)) {
          emlrtDynamicBoundsCheckR2012b(b_i + 1, 1, a1.size(1), &x_emlrtBCI,
                                        (emlrtCTX)sp);
        }
        if (covrtLogCond(&emlrtCoverageInstance, 0, 0, 1,
                         a1[b_i] < peak_threshold)) {
          if (b_i + 6 > data.size(0)) {
            emlrtDynamicBoundsCheckR2012b(b_i + 6, 1, data.size(0), &y_emlrtBCI,
                                          (emlrtCTX)sp);
          }
          if (covrtLogCond(&emlrtCoverageInstance, 0, 0, 2,
                           data[(b_i + data.size(0) * b_I) + 5] < 5.0E+8)) {
            covrtLogMcdc(&emlrtCoverageInstance, 0, 0, 0, true);
            covrtLogIf(&emlrtCoverageInstance, 0, 0, 0, true);
            covrtLogBasicBlock(&emlrtCoverageInstance, 0, 6);
            if (b_i + 6 > data.size(0)) {
              emlrtDynamicBoundsCheckR2012b(b_i + 6, 1, data.size(0),
                                            &bb_emlrtBCI, (emlrtCTX)sp);
            }
            if (b_i + 6 > noise.size(0)) {
              emlrtDynamicBoundsCheckR2012b(b_i + 6, 1, noise.size(0),
                                            &cb_emlrtBCI, (emlrtCTX)sp);
            }
            noise[b_i + 5] = data[(b_i + data.size(0) * b_I) + 5];
          } else {
            guard1 = true;
          }
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }
      if (guard1) {
        covrtLogMcdc(&emlrtCoverageInstance, 0, 0, 0, false);
        covrtLogIf(&emlrtCoverageInstance, 0, 0, 0, false);
        covrtLogBasicBlock(&emlrtCoverageInstance, 0, 7);
        if (b_i + 6 > noise.size(0)) {
          emlrtDynamicBoundsCheckR2012b(b_i + 6, 1, noise.size(0), &ab_emlrtBCI,
                                        (emlrtCTX)sp);
        }
        noise[b_i + 5] = rtNaN;
      }
      if (*emlrtBreakCheckR2012bFlagVar != 0) {
        emlrtBreakCheckR2012b((emlrtCTX)sp);
      }
    }
    covrtLogFor(&emlrtCoverageInstance, 0, 0, 3, 0);
    covrtLogBasicBlock(&emlrtCoverageInstance, 0, 8);
    base_.set_size(&u_emlrtRTEI, sp, 1, i5);
    for (i1 = 0; i1 < e_loop_ub; i1++) {
      base_[i1] = data[i1 + data.size(0) * b_I];
    }
    // The baseline is estimated as straight line from start to stop of
    // intervals:
    x_baselined.set_size(&v_emlrtRTEI, sp, 1, m1);
    for (i1 = 0; i1 < f_loop_ub; i1++) {
      x_baselined[i1] = 0.0;
    }
    N.set_size(&w_emlrtRTEI, sp, noise.size(0));
    loop_ub = noise.size(0);
    for (i1 = 0; i1 < loop_ub; i1++) {
      N[i1] = muDoubleScalarIsNaN(noise[i1]);
    }
    iv = 0.0;
    i1 = N.size(0);
    for (b_i = 0; b_i <= i1 - 2; b_i++) {
      covrtLogFor(&emlrtCoverageInstance, 0, 0, 4, 1);
      if (b_i + 1 > N.size(0)) {
        emlrtDynamicBoundsCheckR2012b(b_i + 1, 1, N.size(0), &db_emlrtBCI,
                                      (emlrtCTX)sp);
      }
      guard1 = false;
      if (covrtLogCond(&emlrtCoverageInstance, 0, 0, 3, !N[b_i])) {
        if (b_i + 2 > N.size(0)) {
          emlrtDynamicBoundsCheckR2012b(b_i + 2, 1, N.size(0), &eb_emlrtBCI,
                                        (emlrtCTX)sp);
        }
        if (covrtLogCond(&emlrtCoverageInstance, 0, 0, 4, N[b_i + 1]) &&
            covrtLogCond(&emlrtCoverageInstance, 0, 0, 5,
                         iv <= static_cast<real_T>(b_i) + 2.0)) {
          int32_T i11;
          int32_T i12;
          covrtLogMcdc(&emlrtCoverageInstance, 0, 0, 1, true);
          covrtLogIf(&emlrtCoverageInstance, 0, 0, 1, true);
          covrtLogBasicBlock(&emlrtCoverageInstance, 0, 9);
          if (b_i + 2 > N.size(0)) {
            i6 = 0;
            i7 = 0;
          } else {
            if (b_i + 2 > N.size(0)) {
              emlrtDynamicBoundsCheckR2012b(b_i + 2, 1, N.size(0), &l_emlrtBCI,
                                            (emlrtCTX)sp);
            }
            i6 = b_i + 1;
            i7 = N.size(0);
          }
          b_iv[0] = 1;
          loop_ub = i7 - i6;
          b_iv[1] = loop_ub;
          st.site = &c_emlrtRSI;
          coder::internal::indexShapeCheck(&st, N.size(0), b_iv);
          st.site = &c_emlrtRSI;
          b_N.set_size(&x_emlrtRTEI, &st, loop_ub);
          for (i7 = 0; i7 < loop_ub; i7++) {
            b_N[i7] = static_cast<real_T>(N[i6 + i7]) - 1.0;
          }
          b_st.site = &kb_emlrtRSI;
          coder::eml_find(&b_st, b_N, (int32_T *)&ii_data, &ii_size);
          for (i6 = 0; i6 < ii_size; i6++) {
            stop_data = (static_cast<real_T>(ii_data) +
                         (static_cast<real_T>(b_i) + 2.0)) -
                        2.0;
          }
          if (1 > ii_size) {
            emlrtDynamicBoundsCheckR2012b(1, 1, ii_size, &k_emlrtBCI,
                                          (emlrtCTX)sp);
          }
          iv = stop_data + 1.0;
          if ((static_cast<int32_T>(stop_data + 1.0) < 1) ||
              (static_cast<int32_T>(stop_data + 1.0) > data.size(0))) {
            emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(stop_data + 1.0),
                                          1, data.size(0), &mb_emlrtBCI,
                                          (emlrtCTX)sp);
          }
          if (b_i + 1 > data.size(0)) {
            emlrtDynamicBoundsCheckR2012b(b_i + 1, 1, data.size(0),
                                          &nb_emlrtBCI, (emlrtCTX)sp);
          }
          vv = (stop_data - (static_cast<real_T>(b_i) + 2.0)) + 1.0;
          b = (data[(static_cast<int32_T>(stop_data + 1.0) +
                     data.size(0) * b_I) -
                    1] -
               data[b_i + data.size(0) * b_I]) /
              vv;
          if (static_cast<real_T>(b_i) + 2.0 > stop_data) {
            i6 = 0;
            i7 = 0;
          } else {
            if (b_i + 2 > base_.size(1)) {
              emlrtDynamicBoundsCheckR2012b(b_i + 2, 1, base_.size(1),
                                            &h_emlrtBCI, (emlrtCTX)sp);
            }
            i6 = b_i + 1;
            if ((static_cast<int32_T>(stop_data) < 1) ||
                (static_cast<int32_T>(stop_data) > base_.size(1))) {
              emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(stop_data), 1,
                                            base_.size(1), &g_emlrtBCI,
                                            (emlrtCTX)sp);
            }
            i7 = static_cast<int32_T>(stop_data);
          }
          if (vv < 1.0) {
            a1.set_size(&y_emlrtRTEI, sp, a1.size(0), 0);
          } else {
            a1.set_size(&y_emlrtRTEI, sp, 1,
                        static_cast<int32_T>(vv - 1.0) + 1);
            loop_ub = static_cast<int32_T>(vv - 1.0);
            for (i10 = 0; i10 <= loop_ub; i10++) {
              a1[i10] = static_cast<real_T>(i10) + 1.0;
            }
          }
          a1.set_size(&ab_emlrtRTEI, sp, 1, a1.size(1));
          loop_ub = a1.size(1) - 1;
          for (i10 = 0; i10 <= loop_ub; i10++) {
            a1[i10] = a1[i10] * b;
          }
          i7 -= i6;
          if (i7 != a1.size(1)) {
            emlrtSubAssignSizeCheck1dR2017a(i7, a1.size(1), &e_emlrtECI,
                                            (emlrtCTX)sp);
          }
          if (b_i + 2 > data.size(0)) {
            emlrtDynamicBoundsCheckR2012b(b_i + 2, 1, data.size(0),
                                          &ob_emlrtBCI, (emlrtCTX)sp);
          }
          vv = data[(b_i + data.size(0) * b_I) + 1];
          loop_ub = a1.size(1);
          for (i7 = 0; i7 < loop_ub; i7++) {
            base_[i6 + i7] = vv + a1[i7];
          }
          if (static_cast<real_T>(b_i) + 2.0 > stop_data) {
            i6 = -1;
            i7 = -1;
          } else {
            if (b_i + 2 > data.size(0)) {
              emlrtDynamicBoundsCheckR2012b(b_i + 2, 1, data.size(0),
                                            &j_emlrtBCI, (emlrtCTX)sp);
            }
            i6 = b_i;
            if ((static_cast<int32_T>(stop_data) < 1) ||
                (static_cast<int32_T>(stop_data) > data.size(0))) {
              emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(stop_data), 1,
                                            data.size(0), &i_emlrtBCI,
                                            (emlrtCTX)sp);
            }
            i7 = static_cast<int32_T>(stop_data) - 1;
          }
          b_iv[0] = 1;
          loop_ub = i7 - i6;
          b_iv[1] = loop_ub;
          st.site = &d_emlrtRSI;
          coder::internal::indexShapeCheck(&st, data.size(0), b_iv);
          if (static_cast<real_T>(b_i) + 2.0 > stop_data) {
            i10 = -1;
            ii_data = -1;
          } else {
            if (b_i + 2 > base_.size(1)) {
              emlrtDynamicBoundsCheckR2012b(b_i + 2, 1, base_.size(1),
                                            &f_emlrtBCI, (emlrtCTX)sp);
            }
            i10 = b_i;
            if ((static_cast<int32_T>(stop_data) < 1) ||
                (static_cast<int32_T>(stop_data) > base_.size(1))) {
              emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(stop_data), 1,
                                            base_.size(1), &e_emlrtBCI,
                                            (emlrtCTX)sp);
            }
            ii_data = static_cast<int32_T>(stop_data) - 1;
          }
          ii_size = ii_data - i10;
          if ((loop_ub != ii_size) && ((loop_ub != 1) && (ii_size != 1))) {
            emlrtDimSizeImpxCheckR2021b(loop_ub, ii_size, &d_emlrtECI,
                                        (emlrtCTX)sp);
          }
          if (static_cast<real_T>(b_i) + 2.0 > stop_data) {
            i11 = 0;
            i12 = 0;
          } else {
            if (b_i + 2 > x_baselined.size(1)) {
              emlrtDynamicBoundsCheckR2012b(b_i + 2, 1, x_baselined.size(1),
                                            &d_emlrtBCI, (emlrtCTX)sp);
            }
            i11 = b_i + 1;
            if ((static_cast<int32_T>(stop_data) < 1) ||
                (static_cast<int32_T>(stop_data) > x_baselined.size(1))) {
              emlrtDynamicBoundsCheckR2012b(static_cast<int32_T>(stop_data), 1,
                                            x_baselined.size(1), &c_emlrtBCI,
                                            (emlrtCTX)sp);
            }
            i12 = static_cast<int32_T>(stop_data);
          }
          if (loop_ub == ii_size) {
            r.set_size(&bb_emlrtRTEI, sp, 1, loop_ub);
            for (i7 = 0; i7 < loop_ub; i7++) {
              r[i7] = x[(i6 + i7) + 1] - base_[(i10 + i7) + 1];
            }
          } else {
            st.site = &d_emlrtRSI;
            binary_expand_op(&st, r, x, i6 + 1, i7, base_, i10 + 1, ii_data);
          }
          i6 = i12 - i11;
          if (i6 != r.size(1)) {
            emlrtSubAssignSizeCheck1dR2017a(i6, r.size(1), &c_emlrtECI,
                                            (emlrtCTX)sp);
          }
          loop_ub = r.size(1);
          for (i6 = 0; i6 < loop_ub; i6++) {
            x_baselined[i11 + i6] = r[i6];
          }
          st.site = &e_emlrtRSI;
          vv = Baseline(&st, x_baselined, static_cast<real_T>(b_i) + 2.0,
                        stop_data, x, base_);
          if (covrtLogIf(&emlrtCoverageInstance, 0, 0, 2, vv != 0.0)) {
            covrtLogBasicBlock(&emlrtCoverageInstance, 0, 10);
            st.site = &f_emlrtRSI;
            S2 = Baseline(&st, x_baselined, static_cast<real_T>(b_i) + 2.0, vv,
                          x, base_);
            st.site = &g_emlrtRSI;
            b = Baseline(&st, x_baselined, vv, stop_data, x, base_);
            if (covrtLogCond(&emlrtCoverageInstance, 0, 0, 6, S2 != 0.0) &&
                covrtLogCond(&emlrtCoverageInstance, 0, 0, 7, b != 0.0)) {
              covrtLogMcdc(&emlrtCoverageInstance, 0, 0, 2, true);
              covrtLogIf(&emlrtCoverageInstance, 0, 0, 3, true);
              covrtLogBasicBlock(&emlrtCoverageInstance, 0, 11);
              st.site = &h_emlrtRSI;
              Baseline(&st, x_baselined, static_cast<real_T>(b_i) + 2.0, S2, x,
                       base_);
              st.site = &i_emlrtRSI;
              Baseline(&st, x_baselined, S2, vv, x, base_);
              st.site = &j_emlrtRSI;
              Baseline(&st, x_baselined, vv, b, x, base_);
              st.site = &k_emlrtRSI;
              Baseline(&st, x_baselined, b, stop_data, x, base_);
            } else {
              covrtLogMcdc(&emlrtCoverageInstance, 0, 0, 2, false);
              covrtLogIf(&emlrtCoverageInstance, 0, 0, 3, false);
              if (covrtLogIf(&emlrtCoverageInstance, 0, 0, 4, S2 != 0.0)) {
                covrtLogBasicBlock(&emlrtCoverageInstance, 0, 12);
                st.site = &l_emlrtRSI;
                Baseline(&st, x_baselined, static_cast<real_T>(b_i) + 2.0, S2,
                         x, base_);
                st.site = &m_emlrtRSI;
                Baseline(&st, x_baselined, S2, vv, x, base_);
              } else if (covrtLogIf(&emlrtCoverageInstance, 0, 0, 5,
                                    b != 0.0)) {
                covrtLogBasicBlock(&emlrtCoverageInstance, 0, 13);
                st.site = &n_emlrtRSI;
                Baseline(&st, x_baselined, vv, b, x, base_);
                st.site = &o_emlrtRSI;
                Baseline(&st, x_baselined, b, stop_data, x, base_);
              }
            }
          }
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }
      if (guard1) {
        covrtLogMcdc(&emlrtCoverageInstance, 0, 0, 1, false);
        covrtLogIf(&emlrtCoverageInstance, 0, 0, 1, false);
        if (covrtLogIf(&emlrtCoverageInstance, 0, 0, 6,
                       iv < static_cast<real_T>(b_i) + 2.0)) {
          covrtLogBasicBlock(&emlrtCoverageInstance, 0, 14);
          if (b_i + 2 > noise.size(0)) {
            emlrtDynamicBoundsCheckR2012b(b_i + 2, 1, noise.size(0),
                                          &fb_emlrtBCI, (emlrtCTX)sp);
          }
          if (b_i + 2 > base_.size(1)) {
            emlrtDynamicBoundsCheckR2012b(b_i + 2, 1, base_.size(1),
                                          &gb_emlrtBCI, (emlrtCTX)sp);
          }
          base_[b_i + 1] = noise[b_i + 1];
          if (b_i + 2 > data.size(0)) {
            emlrtDynamicBoundsCheckR2012b(b_i + 2, 1, data.size(0),
                                          &ib_emlrtBCI, (emlrtCTX)sp);
          }
          if (b_i + 2 > base_.size(1)) {
            emlrtDynamicBoundsCheckR2012b(b_i + 2, 1, base_.size(1),
                                          &jb_emlrtBCI, (emlrtCTX)sp);
          }
          if (b_i + 2 > x_baselined.size(1)) {
            emlrtDynamicBoundsCheckR2012b(b_i + 2, 1, x_baselined.size(1),
                                          &kb_emlrtBCI, (emlrtCTX)sp);
          }
          x_baselined[b_i + 1] =
              data[(b_i + data.size(0) * b_I) + 1] - base_[b_i + 1];
        }
      }
      if (*emlrtBreakCheckR2012bFlagVar != 0) {
        emlrtBreakCheckR2012b((emlrtCTX)sp);
      }
    }
    covrtLogFor(&emlrtCoverageInstance, 0, 0, 4, 0);
    covrtLogBasicBlock(&emlrtCoverageInstance, 0, 15);
    // baseline and noise are removed from raw data
    if (b_I + 1 > base.size(0)) {
      emlrtDynamicBoundsCheckR2012b(b_I + 1, 1, base.size(0), &emlrtBCI,
                                    (emlrtCTX)sp);
    }
    b_iv[0] = 1;
    b_iv[1] = base.size(1);
    emlrtSubAssignSizeCheckR2012b(&b_iv[0], 2, base_.size(), 2, &emlrtECI,
                                  (emlrtCTX)sp);
    loop_ub = base_.size(1);
    for (i1 = 0; i1 < loop_ub; i1++) {
      base[b_I + base.size(0) * i1] = base_[i1];
    }
    for (b_i = 0; b_i < i8; b_i++) {
      covrtLogFor(&emlrtCoverageInstance, 0, 0, 5, 1);
      if (b_i + 1 > x_baselined.size(1)) {
        emlrtDynamicBoundsCheckR2012b(b_i + 1, 1, x_baselined.size(1),
                                      &hb_emlrtBCI, (emlrtCTX)sp);
      }
      if (covrtLogIf(&emlrtCoverageInstance, 0, 0, 7, x_baselined[b_i] < 0.0)) {
        covrtLogBasicBlock(&emlrtCoverageInstance, 0, 16);
        if (b_i + 1 > x_baselined.size(1)) {
          emlrtDynamicBoundsCheckR2012b(b_i + 1, 1, x_baselined.size(1),
                                        &lb_emlrtBCI, (emlrtCTX)sp);
        }
        x_baselined[b_i] = 0.0;
      }
      if (*emlrtBreakCheckR2012bFlagVar != 0) {
        emlrtBreakCheckR2012b((emlrtCTX)sp);
      }
    }
    covrtLogFor(&emlrtCoverageInstance, 0, 0, 5, 0);
    covrtLogBasicBlock(&emlrtCoverageInstance, 0, 17);
    if (b_I + 1 > data_baselined.size(0)) {
      emlrtDynamicBoundsCheckR2012b(b_I + 1, 1, data_baselined.size(0),
                                    &b_emlrtBCI, (emlrtCTX)sp);
    }
    b_iv[0] = 1;
    b_iv[1] = data_baselined.size(1);
    emlrtSubAssignSizeCheckR2012b(&b_iv[0], 2, x_baselined.size(), 2,
                                  &b_emlrtECI, (emlrtCTX)sp);
    loop_ub = x_baselined.size(1);
    for (i1 = 0; i1 < loop_ub; i1++) {
      data_baselined[b_I + data_baselined.size(0) * i1] = x_baselined[i1];
    }
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b((emlrtCTX)sp);
    }
  }
  covrtLogFor(&emlrtCoverageInstance, 0, 0, 1, 0);
  covrtLogBasicBlock(&emlrtCoverageInstance, 0, 18);
  emlrtHeapReferenceStackLeaveFcnR2012b((emlrtCTX)sp);
}

// End of code generation (data_baseline.cpp)
