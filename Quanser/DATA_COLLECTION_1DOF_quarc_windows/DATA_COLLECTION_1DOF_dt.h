/*
 * DATA_COLLECTION_1DOF_dt.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "DATA_COLLECTION_1DOF".
 *
 * Model version              : 1.114
 * Simulink Coder version : 9.0 (R2018b) 24-May-2018
 * C source code generated on : Mon Feb 23 11:25:51 2026
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
  { (char_T *)(&DATA_COLLECTION_1DOF_B.TSamp), 0, 0, 23 },

  { (char_T *)(&DATA_COLLECTION_1DOF_B.LogicalOperator4), 8, 0, 4 }
  ,

  { (char_T *)(&DATA_COLLECTION_1DOF_DW.UD_DSTATE), 0, 0, 58 },

  { (char_T *)(&DATA_COLLECTION_1DOF_DW.HILInitialize_Card), 15, 0, 1 },

  { (char_T *)(&DATA_COLLECTION_1DOF_DW.HILWriteDigitalTimebase_Task), 16, 0, 1
  },

  { (char_T *)(&DATA_COLLECTION_1DOF_DW.HILReadEncoder_PWORK), 11, 0, 18 },

  { (char_T *)(&DATA_COLLECTION_1DOF_DW.HILReadEncoder_Buffer[0]), 6, 0, 30 },

  { (char_T *)(&DATA_COLLECTION_1DOF_DW.FromWorkspace3_IWORK.PrevIndex), 10, 0,
    3 },

  { (char_T *)(&DATA_COLLECTION_1DOF_DW.HILInitialize_DOBits[0]), 8, 0, 10 },

  { (char_T *)(&DATA_COLLECTION_1DOF_DW.HILWriteDigitalTimebase_Buffer), 14, 0,
    11 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  10U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&DATA_COLLECTION_1DOF_P.KE_D1), 0, 0, 25 },

  { (char_T *)(&DATA_COLLECTION_1DOF_P.HILWriteDigitalTimebase_clock), 6, 0, 1 },

  { (char_T *)(&DATA_COLLECTION_1DOF_P.HILReadEncoder_channels[0]), 7, 0, 18 },

  { (char_T *)(&DATA_COLLECTION_1DOF_P.StopwithMessage_message_icon), 2, 0, 4 },

  { (char_T *)(&DATA_COLLECTION_1DOF_P.TSamp_WtEt), 0, 0, 37 },

  { (char_T *)(&DATA_COLLECTION_1DOF_P.HILInitialize_CKChannels[0]), 6, 0, 7 },

  { (char_T *)(&DATA_COLLECTION_1DOF_P.HILInitialize_AIChannels[0]), 7, 0, 42 },

  { (char_T *)(&DATA_COLLECTION_1DOF_P.HILReadEncoder_Active), 8, 0, 47 },

  { (char_T *)(&DATA_COLLECTION_1DOF_P.ManualSwitch3_CurrentSetting), 3, 0, 3 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  9U,
  rtPTransitions
};

/* [EOF] DATA_COLLECTION_1DOF_dt.h */
