//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// data_baseline_initialize.cpp
//
// Code generation for function 'data_baseline_initialize'
//

// Include files
#include "data_baseline_initialize.h"
#include "_coder_data_baseline_mex.h"
#include "data_baseline_data.h"
#include "rt_nonfinite.h"

// Function Declarations
static void data_baseline_once();

// Function Definitions
static void data_baseline_once()
{
  const int32_T postfix_exprs_0_0[5]{0, 1, -3, 2, -3};
  const int32_T postfix_exprs_0_1[5]{0, 1, -3, 2, -3};
  const int32_T cond_ends_0_0[3]{1126, 1156, 1174};
  const int32_T cond_ends_0_1[3]{1521, 1534, 1544};
  const int32_T cond_starts_0_0[3]{1102, 1130, 1160};
  const int32_T cond_starts_0_1[3]{1510, 1525, 1538};
  const int32_T postfix_exprs_0_2[3]{0, 1, -3};
  const int32_T postfix_exprs_0_3[3]{0, 1, -3};
  const int32_T cond_ends_0_2[2]{2294, 2305};
  const int32_T cond_ends_0_3[2]{4383, 4402};
  const int32_T cond_starts_0_2[2]{2287, 2298};
  const int32_T cond_starts_0_3[2]{4367, 4387};
  mex_InitInfAndNan();
  // Allocate instance data
  covrtAllocateInstanceData(&emlrtCoverageInstance);
  // Initialize Coverage Information
  covrtScriptInit(&emlrtCoverageInstance,
                  "C:\\Users\\DELL\\PycharmProjects\\MS-analysis\\Data "
                  "preprocessing\\Matlab version\\data_baseline.m",
                  0U, 2U, 26U, 11U, 0U, 0U, 0U, 6U, 0U, 10U, 4U);
  // Initialize Function Information
  covrtFcnInit(&emlrtCoverageInstance, 0U, 0U, "data_baseline", 0, -1, 3704);
  covrtFcnInit(&emlrtCoverageInstance, 0U, 1U, "Baseline", 3706, -1, 5313);
  // Initialize Basic Block Information
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 18U, 3649, -1, 3700);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 17U, 3601, -1, 3636);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 16U, 3540, -1, 3559);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 15U, 3451, -1, 3470);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 14U, 3284, -1, 3354);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 13U, 3014, -1, 3193);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 12U, 2774, -1, 2954);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 11U, 2330, -1, 2714);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 10U, 2085, -1, 2263);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 9U, 1561, -1, 2037);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 8U, 1294, -1, 1466);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 7U, 1241, -1, 1256);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 6U, 1191, -1, 1207);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 5U, 1049, -1, 1067);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 4U, 907, -1, 945);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 3U, 745, -1, 871);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 2U, 632, -1, 698);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 1U, 555, -1, 614);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 0U, 294, -1, 424);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 25U, 5249, -1, 5309);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 24U, 5215, -1, 5236);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 23U, 4835, -1, 5197);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 22U, 4411, -1, 4773);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 21U, 4098, -1, 4341);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 20U, 4064, -1, 4086);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 19U, 3874, -1, 3924);
  // Initialize If Information
  covrtIfInit(&emlrtCoverageInstance, 0U, 0U, 1099, 1174, 1220, 1272);
  covrtIfInit(&emlrtCoverageInstance, 0U, 1U, 1507, 1544, 3255, 3355);
  covrtIfInit(&emlrtCoverageInstance, 0U, 2U, 2054, 2064, -1, 3237);
  covrtIfInit(&emlrtCoverageInstance, 0U, 3U, 2284, 2305, 2735, 2955);
  covrtIfInit(&emlrtCoverageInstance, 0U, 4U, 2735, 2749, 2975, 3217);
  covrtIfInit(&emlrtCoverageInstance, 0U, 5U, 2975, 2989, -1, 3194);
  covrtIfInit(&emlrtCoverageInstance, 0U, 6U, 3255, 3267, -1, 3355);
  covrtIfInit(&emlrtCoverageInstance, 0U, 7U, 3504, 3523, -1, 3575);
  covrtIfInit(&emlrtCoverageInstance, 0U, 8U, 4028, 4055, 4364, 5244);
  covrtIfInit(&emlrtCoverageInstance, 0U, 9U, 4364, 4402, 4778, 5244);
  covrtIfInit(&emlrtCoverageInstance, 0U, 10U, 4778, 4826, 5202, 5244);
  // Initialize MCDC Information
  covrtMcdcInit(&emlrtCoverageInstance, 0U, 0U, 1102, 1174, 3, 0,
                *(int32_T(*)[3]) & cond_starts_0_0[0],
                *(int32_T(*)[3]) & cond_ends_0_0[0], 5,
                *(int32_T(*)[5]) & postfix_exprs_0_0[0]);
  covrtMcdcInit(&emlrtCoverageInstance, 0U, 1U, 1510, 1544, 3, 3,
                *(int32_T(*)[3]) & cond_starts_0_1[0],
                *(int32_T(*)[3]) & cond_ends_0_1[0], 5,
                *(int32_T(*)[5]) & postfix_exprs_0_1[0]);
  covrtMcdcInit(&emlrtCoverageInstance, 0U, 2U, 2287, 2305, 2, 6,
                *(int32_T(*)[2]) & cond_starts_0_2[0],
                *(int32_T(*)[2]) & cond_ends_0_2[0], 3,
                *(int32_T(*)[3]) & postfix_exprs_0_2[0]);
  covrtMcdcInit(&emlrtCoverageInstance, 0U, 3U, 4367, 4402, 2, 8,
                *(int32_T(*)[2]) & cond_starts_0_3[0],
                *(int32_T(*)[2]) & cond_ends_0_3[0], 3,
                *(int32_T(*)[3]) & postfix_exprs_0_3[0]);
  // Initialize For Information
  covrtForInit(&emlrtCoverageInstance, 0U, 0U, 522, 546, 622);
  covrtForInit(&emlrtCoverageInstance, 0U, 1U, 703, 715, 3644);
  covrtForInit(&emlrtCoverageInstance, 0U, 2U, 885, 894, 957);
  covrtForInit(&emlrtCoverageInstance, 0U, 3U, 1076, 1086, 1284);
  covrtForInit(&emlrtCoverageInstance, 0U, 4U, 1475, 1494, 3387);
  covrtForInit(&emlrtCoverageInstance, 0U, 5U, 3479, 3491, 3587);
  // Initialize While Information
  // Initialize Switch Information
  // Start callback for coverage engine
  covrtScriptStart(&emlrtCoverageInstance, 0U);
}

void data_baseline_initialize()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  emlrtBreakCheckR2012bFlagVar = emlrtGetBreakCheckFlagAddressR2012b();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, nullptr);
  emlrtEnterRtStackR2012b(&st);
  if (emlrtFirstTimeR2012b(emlrtRootTLSGlobal)) {
    data_baseline_once();
  }
}

// End of code generation (data_baseline_initialize.cpp)
