/*
 * q_2dsfl_pos_cntrl_OG_dt.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "q_2dsfl_pos_cntrl_OG".
 *
 * Model version              : 1.74
 * Simulink Coder version : 9.0 (R2018b) 24-May-2018
 * C source code generated on : Mon Feb  9 15:37:36 2026
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
  sizeof(t_task),
  sizeof(t_boolean),
  sizeof(t_card)
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
  "t_task",
  "t_boolean",
  "t_card"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid_o1), 0, 0, 43 },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_B.LogicalOperator4), 8, 0, 12 },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_B.BiasRemoval_m.Switch), 0, 0, 7 },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_B.BiasRemoval.Switch), 0, 0, 7 }
  ,

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_DW.HILInitialize_AIMinimums[0]), 0, 0, 74 },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_DW.HILReadEncoderTimebase_Task), 14, 0, 1 },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card), 16, 0, 1 },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.Time), 0, 0, 3 },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_DW.theta11deg_PWORK.LoggedData), 11, 0, 18
  },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_DW.HILInitialize_DOStates[0]), 6, 0, 26 },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_DW.TransportDelay_IWORK.Tail), 10, 0, 1 },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_DW.PositionWatchdog_SubsysRanBC), 2, 0, 2 },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Flag), 3, 0, 2 },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_DW.HILInitialize_DOBits[0]), 8, 0, 8 },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_DW.HILWriteDigital_Buffer[0]), 15, 0, 7 },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_DW.PositionWatchdog_MODE), 8, 0, 2 },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_DW.BiasRemoval_m.UnitDelay_DSTATE), 0, 0, 2
  },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_DW.BiasRemoval_m.SwitchCase_ActiveSubsystem),
    2, 0, 5 },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_DW.BiasRemoval_m.EnabledMovingAverage_MODE),
    8, 0, 1 },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_DW.BiasRemoval.UnitDelay_DSTATE), 0, 0, 2 },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_DW.BiasRemoval.SwitchCase_ActiveSubsystem),
    2, 0, 5 },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_DW.BiasRemoval.EnabledMovingAverage_MODE),
    8, 0, 1 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  22U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&q_2dsfl_pos_cntrl_OG_P.DTH1_LIM_ENABLE), 0, 0, 25 },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_P.HILReadEncoderTimebase_clock), 6, 0, 1 },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_P.HILReadEncoderTimebase_channels), 7, 0,
    16 },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_P.StopwithMessage_message_icon), 2, 0, 8 },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_P.Cnstant2_Value[0]), 0, 0, 100 },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_P.HILInitialize_CKChannels[0]), 6, 0, 7 },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_P.HILInitialize_AIChannels[0]), 7, 0, 57 },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_P.Constant_Value), 8, 0, 51 },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_P.ManualSwitch1_CurrentSetting), 3, 0, 2 },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_P.BiasRemoval_m.unity_Value), 0, 0, 11 },

  { (char_T *)(&q_2dsfl_pos_cntrl_OG_P.BiasRemoval.unity_Value), 0, 0, 11 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  11U,
  rtPTransitions
};

/* [EOF] q_2dsfl_pos_cntrl_OG_dt.h */
