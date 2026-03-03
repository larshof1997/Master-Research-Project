/*
 * motor_calibration_dt.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "motor_calibration".
 *
 * Model version              : 1.94
 * Simulink Coder version : 9.0 (R2018b) 24-May-2018
 * C source code generated on : Mon Mar  2 17:06:40 2026
 *
 * Target selection: quarc_windows.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ext_types.h"

/* data type size table */
static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(pointer_T),
  sizeof(action_T),
  2*sizeof(uint32_T),
  sizeof(t_boolean),
  sizeof(t_card),
  sizeof(t_task)
};

/* data type name table */
static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T",
  "t_boolean",
  "t_card",
  "t_task"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&motor_calibration_B.Product), 0, 0, 10 },

  { (char_T *)(&motor_calibration_B.LogicalOperator4), 8, 0, 4 }
  ,

  { (char_T *)(&motor_calibration_DW.HILReadAnalog_Buffer), 0, 0, 49 },

  { (char_T *)(&motor_calibration_DW.HILInitialize_Card), 15, 0, 1 },

  { (char_T *)(&motor_calibration_DW.HILWriteDigitalTimebase_Task), 16, 0, 1 },

  { (char_T *)(&motor_calibration_DW.HILWriteAnalog_PWORK), 11, 0, 10 },

  { (char_T *)(&motor_calibration_DW.HILReadEncoder_Buffer[0]), 6, 0, 28 },

  { (char_T *)(&motor_calibration_DW.HILInitialize_DOBits[0]), 8, 0, 10 },

  { (char_T *)(&motor_calibration_DW.HILWriteDigitalTimebase_Buffer), 14, 0, 11
  }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  9U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&motor_calibration_P.KE_D1), 0, 0, 6 },

  { (char_T *)(&motor_calibration_P.HILWriteDigitalTimebase_clock), 6, 0, 1 },

  { (char_T *)(&motor_calibration_P.HILWriteAnalog_channels), 7, 0, 16 },

  { (char_T *)(&motor_calibration_P.StopwithMessage_message_icon), 2, 0, 4 },

  { (char_T *)(&motor_calibration_P.Step_Y0), 0, 0, 27 },

  { (char_T *)(&motor_calibration_P.HILInitialize_CKChannels[0]), 6, 0, 7 },

  { (char_T *)(&motor_calibration_P.HILInitialize_AIChannels[0]), 7, 0, 42 },

  { (char_T *)(&motor_calibration_P.HILWriteAnalog_Active), 8, 0, 46 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  8U,
  rtPTransitions
};

/* [EOF] motor_calibration_dt.h */
