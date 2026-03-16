/*
 * TRACKING_CONTROL_RasconIET_dt.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "TRACKING_CONTROL_RasconIET".
 *
 * Model version              : 1.177
 * Simulink Coder version : 9.0 (R2018b) 24-May-2018
 * C source code generated on : Mon Mar 16 16:01:42 2026
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
  { (char_T *)(&TRACKING_CONTROL_RasconIET_B.UnaryMinus), 0, 0, 43 },

  { (char_T *)(&TRACKING_CONTROL_RasconIET_B.LogicalOperator4), 8, 0, 4 }
  ,

  { (char_T *)(&TRACKING_CONTROL_RasconIET_DW.UnitDelay2_DSTATE), 0, 0, 68 },

  { (char_T *)(&TRACKING_CONTROL_RasconIET_DW.HILInitialize_Card), 15, 0, 1 },

  { (char_T *)(&TRACKING_CONTROL_RasconIET_DW.HILWriteDigitalTimebase_Task), 16,
    0, 1 },

  { (char_T *)(&TRACKING_CONTROL_RasconIET_DW.HILReadEncoder_PWORK), 11, 0, 29 },

  { (char_T *)(&TRACKING_CONTROL_RasconIET_DW.HILReadEncoder_Buffer[0]), 6, 0,
    32 },

  { (char_T *)(&TRACKING_CONTROL_RasconIET_DW.FromWorkspace4_IWORK.PrevIndex),
    10, 0, 4 },

  { (char_T *)(&TRACKING_CONTROL_RasconIET_DW.HILInitialize_DOBits[0]), 8, 0, 10
  },

  { (char_T *)(&TRACKING_CONTROL_RasconIET_DW.HILWriteDigitalTimebase_Buffer),
    14, 0, 11 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  10U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&TRACKING_CONTROL_RasconIET_P.KE_D1), 0, 0, 30 },

  { (char_T *)(&TRACKING_CONTROL_RasconIET_P.HILWriteDigitalTimebase_clock), 6,
    0, 1 },

  { (char_T *)(&TRACKING_CONTROL_RasconIET_P.HILReadEncoder_channels[0]), 7, 0,
    22 },

  { (char_T *)(&TRACKING_CONTROL_RasconIET_P.StopwithMessage_message_icon), 2, 0,
    4 },

  { (char_T *)(&TRACKING_CONTROL_RasconIET_P.UnitDelay2_InitialCondition), 0, 0,
    44 },

  { (char_T *)(&TRACKING_CONTROL_RasconIET_P.HILInitialize_CKChannels[0]), 6, 0,
    7 },

  { (char_T *)(&TRACKING_CONTROL_RasconIET_P.HILInitialize_AIChannels[0]), 7, 0,
    42 },

  { (char_T *)(&TRACKING_CONTROL_RasconIET_P.HILReadEncoder_Active), 8, 0, 50 },

  { (char_T *)(&TRACKING_CONTROL_RasconIET_P.ManualSwitch3_CurrentSetting), 3, 0,
    8 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  9U,
  rtPTransitions
};

/* [EOF] TRACKING_CONTROL_RasconIET_dt.h */
