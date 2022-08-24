/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * data_preprocessing.h
 *
 * Code generation for function 'data_preprocessing'
 *
 */

#ifndef DATA_PREPROCESSING_H
#define DATA_PREPROCESSING_H

/* Include files */
#include "data_preprocessing_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void data_preprocessing(const emxArray_real_T *atlas_data,
                               emxArray_real_T *data_baselined,
                               emxArray_real_T *base,
                               emxArray_real_T *peaks_info);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (data_preprocessing.h) */
