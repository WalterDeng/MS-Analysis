/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * main.c
 *
 * Code generation for function 'main'
 *
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/
/* Include files */
#include "rt_nonfinite.h"
#include "data_preprocessing.h"
#include "main.h"
#include "data_preprocessing_terminate.h"
#include "data_preprocessing_emxAPI.h"
#include "data_preprocessing_initialize.h"

/* Function Declarations */
static emxArray_real_T *argInit_2xUnbounded_real_T(void);
static double argInit_real_T(void);
static void main_data_preprocessing(void);

/* Function Definitions */
static emxArray_real_T *argInit_2xUnbounded_real_T(void)
{
  emxArray_real_T *result;
  int idx1;

  /* Set the size of the array.
     Change this size to the value that the application requires. */
  result = emxCreate_real_T(2, 2);

  /* Loop over the array to initialize each element. */
  for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result->data[idx1 << 1] = argInit_real_T();
  }

  for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result->data[1 + (idx1 << 1)] = argInit_real_T();
  }

  return result;
}

static double argInit_real_T(void)
{
  return 0.0;
}

static void main_data_preprocessing(void)
{
  emxArray_real_T *data_baselined;
  emxArray_real_T *base;
  emxArray_real_T *peaks_info;
  emxArray_real_T *atlas_data;
  emxInitArray_real_T(&data_baselined, 2);
  emxInitArray_real_T(&base, 2);
  emxInitArray_real_T(&peaks_info, 2);

  /* Initialize function 'data_preprocessing' input arguments. */
  /* Initialize function input argument 'atlas_data'. */
  atlas_data = argInit_2xUnbounded_real_T();

  /* Call the entry-point 'data_preprocessing'. */
  data_preprocessing(atlas_data, data_baselined, base, peaks_info);
  emxDestroyArray_real_T(peaks_info);
  emxDestroyArray_real_T(base);
  emxDestroyArray_real_T(data_baselined);
  emxDestroyArray_real_T(atlas_data);
}

int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  /* Initialize the application.
     You do not need to do this more than one time. */
  data_preprocessing_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_data_preprocessing();

  /* Terminate the application.
     You do not need to do this more than one time. */
  data_preprocessing_terminate();
  return 0;
}

/* End of code generation (main.c) */
