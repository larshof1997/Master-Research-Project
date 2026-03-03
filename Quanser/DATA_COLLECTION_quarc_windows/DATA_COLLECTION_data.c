/*
 * DATA_COLLECTION_data.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "DATA_COLLECTION".
 *
 * Model version              : 1.114
 * Simulink Coder version : 9.0 (R2018b) 24-May-2018
 * C source code generated on : Tue Mar  3 13:11:22 2026
 *
 * Target selection: quarc_windows.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "DATA_COLLECTION.h"
#include "DATA_COLLECTION_private.h"

/* Block parameters (default storage) */
P_DATA_COLLECTION_T DATA_COLLECTION_P = {
  /* Variable: KE_D1
   * Referenced by:
   *   '<Root>/Motor #1 Encoder Calib1'
   *   '<S7>/Motor #1 Encoder Calib1'
   *   '<S8>/Motor #1 Encoder Calib1'
   */
  1.5339807878856413E-5,

  /* Variable: KE_D2
   * Referenced by:
   *   '<Root>/Motor #2 Encoder Calib1'
   *   '<S7>/Motor #2 Encoder Calib1'
   *   '<S8>/Motor #2 Encoder Calib1'
   */
  3.0679615757712826E-5,

  /* Variable: Kt1
   * Referenced by: '<S8>/Torque to current '
   */
  3.018583,

  /* Variable: Kt2
   * Referenced by: '<S7>/Torque to current '
   */
  1.111065,

  /* Variable: L1
   * Referenced by:
   *   '<S7>/Motor #1 Encoder Calib2'
   *   '<S8>/Motor #1 Encoder Calib2'
   */
  0.047544,

  /* Variable: L2
   * Referenced by:
   *   '<S7>/Motor #1 Encoder Calib5'
   *   '<S8>/Motor #1 Encoder Calib5'
   */
  0.04819,

  /* Variable: LIMIT_SWITCHES_ENABLE
   * Referenced by: '<S3>/Constant'
   */
  1.0,

  /* Variable: R1
   * Referenced by:
   *   '<S7>/Motor #1 Encoder Calib6'
   *   '<S8>/Motor #1 Encoder Calib6'
   *   '<S8>/Saturation'
   */
  4.2737,

  /* Variable: R2
   * Referenced by:
   *   '<S7>/Motor #1 Encoder Calib7'
   *   '<S7>/Saturation'
   *   '<S8>/Motor #1 Encoder Calib7'
   */
  4.0364,

  /* Variable: a1_hat
   * Referenced by: '<Root>/Constant'
   */
  0.27437240180000005,

  /* Variable: a2_hat
   * Referenced by: '<Root>/Constant1'
   */
  0.051334874999999995,

  /* Variable: b1_hat
   * Referenced by: '<Root>/Constant5'
   */
  0.209044,

  /* Variable: b2_hat
   * Referenced by: '<Root>/Constant4'
   */
  0.225127,

  /* Variable: b_hat
   * Referenced by:
   *   '<Root>/Constant2'
   *   '<Root>/Constant3'
   */
  0.059916955,

  /* Variable: fc1_hat
   * Referenced by: '<Root>/Constant7'
   */
  0.169008,

  /* Variable: fc2_hat
   * Referenced by: '<Root>/Constant8'
   */
  0.336889,

  /* Variable: i_sat1
   * Referenced by: '<S8>/Saturation'
   */
  0.92,

  /* Variable: i_sat2
   * Referenced by: '<S7>/Saturation'
   */
  1.2,

  /* Variable: ke1
   * Referenced by:
   *   '<S7>/Motor #1 Encoder Calib3'
   *   '<S8>/Motor #1 Encoder Calib3'
   */
  0.06847,

  /* Variable: ke2
   * Referenced by:
   *   '<S7>/Motor #1 Encoder Calib8'
   *   '<S8>/Motor #1 Encoder Calib8'
   */
  0.007983,

  /* Variable: ki1
   * Referenced by:
   *   '<S7>/Gain1'
   *   '<S8>/Gain1'
   */
  0.0,

  /* Variable: ki_traj
   * Referenced by: '<Root>/Gain1'
   */
  { 0.0, 0.0, 0.0, 0.0 },

  /* Variable: kp1
   * Referenced by: '<S8>/Gain'
   */
  1.5,

  /* Variable: kp2
   * Referenced by: '<S7>/Gain'
   */
  1.0,

  /* Variable: v_eps_hat
   * Referenced by: '<Root>/Constant6'
   */
  0.039272,

  /* Mask Parameter: DiscreteDerivative3_ICPrevScale
   * Referenced by: '<S20>/UD'
   */
  0.0,

  /* Mask Parameter: DiscreteDerivative_ICPrevScaled
   * Referenced by: '<S17>/UD'
   */
  0.0,

  /* Mask Parameter: DiscreteDerivative_ICPrevScal_k
   * Referenced by: '<S1>/UD'
   */
  0.0,

  /* Mask Parameter: DiscreteDerivative2_ICPrevScale
   * Referenced by: '<S19>/UD'
   */
  0.0,

  /* Mask Parameter: DiscreteDerivative1_ICPrevScale
   * Referenced by: '<S18>/UD'
   */
  0.0,

  /* Mask Parameter: DiscreteDerivative3_ICPrevSca_i
   * Referenced by: '<S24>/UD'
   */
  0.0,

  /* Mask Parameter: DiscreteDerivative_ICPrevScal_l
   * Referenced by: '<S21>/UD'
   */
  0.0,

  /* Mask Parameter: DiscreteDerivative2_ICPrevSca_n
   * Referenced by: '<S23>/UD'
   */
  0.0,

  /* Mask Parameter: DiscreteDerivative1_ICPrevSca_c
   * Referenced by: '<S22>/UD'
   */
  0.0,

  /* Mask Parameter: HILWriteDigitalTimebase_clock
   * Referenced by: '<Root>/HIL Write Digital Timebase'
   */
  0,

  /* Mask Parameter: HILReadEncoder_channels
   * Referenced by: '<S7>/HIL Read Encoder'
   */
  { 0U, 2U },

  /* Mask Parameter: HILReadEncoder_channels_d
   * Referenced by: '<Root>/HIL Read Encoder'
   */
  { 0U, 2U },

  /* Mask Parameter: HILReadAnalog_channels
   * Referenced by: '<S7>/HIL Read Analog'
   */
  1U,

  /* Mask Parameter: HILWriteAnalog_channels
   * Referenced by: '<S7>/HIL Write Analog'
   */
  1U,

  /* Mask Parameter: HILReadEncoder_channels_g
   * Referenced by: '<S8>/HIL Read Encoder'
   */
  { 0U, 2U },

  /* Mask Parameter: HILReadAnalog_channels_e
   * Referenced by: '<S8>/HIL Read Analog'
   */
  0U,

  /* Mask Parameter: HILWriteAnalog_channels_h
   * Referenced by: '<S8>/HIL Write Analog'
   */
  0U,

  /* Mask Parameter: HILWriteDigitalTimebase_channel
   * Referenced by: '<Root>/HIL Write Digital Timebase'
   */
  16U,

  /* Mask Parameter: HILWriteDigital_channels
   * Referenced by: '<S2>/HIL Write Digital'
   */
  { 0U, 1U, 4U },

  /* Mask Parameter: HILReadDigital_channels
   * Referenced by: '<S2>/HIL Read Digital'
   */
  { 8U, 9U, 12U },

  /* Mask Parameter: HILReadDigital_channels_j
   * Referenced by: '<S3>/HIL Read Digital'
   */
  { 8U, 9U, 10U, 11U },

  /* Mask Parameter: HILWriteDigitalTimebase_samples
   * Referenced by: '<Root>/HIL Write Digital Timebase'
   */
  100U,

  /* Mask Parameter: StopwithMessage_message_icon
   * Referenced by: '<S9>/Show Message on Host'
   */
  1,

  /* Mask Parameter: StopwithMessage1_message_icon
   * Referenced by: '<S10>/Show Message on Host'
   */
  1,

  /* Mask Parameter: StopwithMessage2_message_icon
   * Referenced by: '<S11>/Show Message on Host'
   */
  1,

  /* Mask Parameter: StopwithMessage3_message_icon
   * Referenced by: '<S12>/Show Message on Host'
   */
  1,

  /* Computed Parameter: TSamp_WtEt
   * Referenced by: '<S20>/TSamp'
   */
  100.0,

  /* Computed Parameter: TSamp_WtEt_p
   * Referenced by: '<S17>/TSamp'
   */
  100.0,

  /* Expression: 0
   * Referenced by: '<Root>/Unit Delay'
   */
  0.0,

  /* Expression: [2; 1]
   * Referenced by: '<Root>/Gain'
   */
  { 2.0, 1.0 },

  /* Computed Parameter: DiscreteTimeIntegrator_gainval
   * Referenced by: '<Root>/Discrete-Time Integrator'
   */
  0.01,

  /* Expression: 0
   * Referenced by: '<Root>/Discrete-Time Integrator'
   */
  0.0,

  /* Computed Parameter: TSamp_WtEt_e
   * Referenced by: '<S1>/TSamp'
   */
  100.0,

  /* Expression: 0
   * Referenced by: '<Root>/Unit Delay1'
   */
  0.0,

  /* Expression: [0; 0]
   * Referenced by: '<Root>/Gain2'
   */
  { 0.0, 0.0 },

  /* Computed Parameter: TSamp_WtEt_ei
   * Referenced by: '<S19>/TSamp'
   */
  100.0,

  /* Computed Parameter: DiscreteTimeIntegrator_gainva_p
   * Referenced by: '<S7>/Discrete-Time Integrator'
   */
  0.01,

  /* Expression: 0
   * Referenced by: '<S7>/Discrete-Time Integrator'
   */
  0.0,

  /* Computed Parameter: TSamp_WtEt_a
   * Referenced by: '<S18>/TSamp'
   */
  100.0,

  /* Expression: 0
   * Referenced by: '<S7>/Gain2'
   */
  0.0,

  /* Computed Parameter: TSamp_WtEt_h
   * Referenced by: '<S24>/TSamp'
   */
  100.0,

  /* Computed Parameter: TSamp_WtEt_l
   * Referenced by: '<S21>/TSamp'
   */
  100.0,

  /* Computed Parameter: TSamp_WtEt_g
   * Referenced by: '<S23>/TSamp'
   */
  100.0,

  /* Computed Parameter: DiscreteTimeIntegrator_gainva_k
   * Referenced by: '<S8>/Discrete-Time Integrator'
   */
  0.01,

  /* Expression: 0
   * Referenced by: '<S8>/Discrete-Time Integrator'
   */
  0.0,

  /* Computed Parameter: TSamp_WtEt_pz
   * Referenced by: '<S22>/TSamp'
   */
  100.0,

  /* Expression: 0
   * Referenced by: '<S8>/Gain2'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<Root>/Unit Delay2'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<Root>/Pulse Generator'
   */
  1.0,

  /* Computed Parameter: PulseGenerator_Period
   * Referenced by: '<Root>/Pulse Generator'
   */
  2.0,

  /* Computed Parameter: PulseGenerator_Duty
   * Referenced by: '<Root>/Pulse Generator'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<Root>/Pulse Generator'
   */
  0.0,

  /* Expression: set_other_outputs_at_terminate
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: set_other_outputs_at_switch_out
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: set_other_outputs_at_start
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: set_other_outputs_at_switch_in
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: final_analog_outputs
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: final_pwm_outputs
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: analog_input_maximums
   * Referenced by: '<Root>/HIL Initialize'
   */
  10.0,

  /* Expression: analog_input_minimums
   * Referenced by: '<Root>/HIL Initialize'
   */
  -10.0,

  /* Expression: analog_output_maximums
   * Referenced by: '<Root>/HIL Initialize'
   */
  10.0,

  /* Expression: analog_output_minimums
   * Referenced by: '<Root>/HIL Initialize'
   */
  -10.0,

  /* Expression: initial_analog_outputs
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: watchdog_analog_outputs
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: encoder_filter_frequency
   * Referenced by: '<Root>/HIL Initialize'
   */
  8.333333333333334E+6,

  /* Expression: pwm_frequency
   * Referenced by: '<Root>/HIL Initialize'
   */
  16276.041666666668,

  /* Expression: initial_pwm_outputs
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: [ 0 0 ]
   * Referenced by: '<S2>/Enable: Active Low'
   */
  { 0.0, 0.0 },

  /* Expression: 1
   * Referenced by: '<S2>/Master Enable: Active High'
   */
  1.0,

  /* Computed Parameter: HILInitialize_CKChannels
   * Referenced by: '<Root>/HIL Initialize'
   */
  { 0, 1 },

  /* Computed Parameter: HILInitialize_CKModes
   * Referenced by: '<Root>/HIL Initialize'
   */
  { 0, 0 },

  /* Computed Parameter: HILInitialize_DOWatchdog
   * Referenced by: '<Root>/HIL Initialize'
   */
  2,

  /* Computed Parameter: HILInitialize_EIInitial
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_POModes
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_AIChannels
   * Referenced by: '<Root>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },

  /* Computed Parameter: HILInitialize_AOChannels
   * Referenced by: '<Root>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },

  /* Computed Parameter: HILInitialize_DIChannels
   * Referenced by: '<Root>/HIL Initialize'
   */
  { 8U, 9U, 10U, 11U, 12U, 13U, 14U, 15U },

  /* Computed Parameter: HILInitialize_DOChannels
   * Referenced by: '<Root>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 16U },

  /* Computed Parameter: HILInitialize_EIChannels
   * Referenced by: '<Root>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },

  /* Computed Parameter: HILInitialize_EIQuadrature
   * Referenced by: '<Root>/HIL Initialize'
   */
  4U,

  /* Computed Parameter: HILReadEncoder_Active
   * Referenced by: '<S7>/HIL Read Encoder'
   */
  1,

  /* Computed Parameter: HILReadEncoder_Active_a
   * Referenced by: '<Root>/HIL Read Encoder'
   */
  1,

  /* Computed Parameter: HILReadAnalog_Active
   * Referenced by: '<S7>/HIL Read Analog'
   */
  1,

  /* Computed Parameter: HILWriteAnalog_Active
   * Referenced by: '<S7>/HIL Write Analog'
   */
  0,

  /* Computed Parameter: HILReadEncoder_Active_j
   * Referenced by: '<S8>/HIL Read Encoder'
   */
  1,

  /* Computed Parameter: HILReadAnalog_Active_l
   * Referenced by: '<S8>/HIL Read Analog'
   */
  1,

  /* Computed Parameter: HILWriteAnalog_Active_l
   * Referenced by: '<S8>/HIL Write Analog'
   */
  0,

  /* Computed Parameter: HILInitialize_Active
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_AOTerminate
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_AOExit
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_DOTerminate
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_DOExit
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_POTerminate
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_POExit
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_CKPStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_CKPEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_CKStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_CKEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_AIPStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_AIPEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_AOPStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_AOPEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_AOStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_AOEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_AOReset
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_DOPStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_DOPEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_DOStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_DOEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_DOReset
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_EIPStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_EIPEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_EIStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_EIEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_POPStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_POPEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_POStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_POEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_POReset
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_OOReset
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_DOFinal
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_DOInitial
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILWriteDigitalTimebase_Active
   * Referenced by: '<Root>/HIL Write Digital Timebase'
   */
  0,

  /* Computed Parameter: HILWriteDigital_Active
   * Referenced by: '<S2>/HIL Write Digital'
   */
  0,

  /* Computed Parameter: HILReadDigital_Active
   * Referenced by: '<S2>/HIL Read Digital'
   */
  1,

  /* Computed Parameter: HILReadDigital_Active_c
   * Referenced by: '<S3>/HIL Read Digital'
   */
  1,

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S13>/Constant'
   */
  0,

  /* Computed Parameter: Constant_Value_h
   * Referenced by: '<S14>/Constant'
   */
  0,

  /* Computed Parameter: Constant_Value_m
   * Referenced by: '<S15>/Constant'
   */
  0,

  /* Computed Parameter: Constant_Value_i
   * Referenced by: '<S16>/Constant'
   */
  0,

  /* Computed Parameter: ManualSwitch3_CurrentSetting
   * Referenced by: '<S7>/Manual Switch3'
   */
  0U,

  /* Computed Parameter: ManualSwitch2_CurrentSetting
   * Referenced by: '<S7>/Manual Switch2'
   */
  0U,

  /* Computed Parameter: ManualSwitch1_CurrentSetting
   * Referenced by: '<S7>/Manual Switch1'
   */
  0U,

  /* Computed Parameter: ManualSwitch4_CurrentSetting
   * Referenced by: '<S7>/Manual Switch4'
   */
  0U,

  /* Computed Parameter: ManualSwitch3_CurrentSetting_n
   * Referenced by: '<S8>/Manual Switch3'
   */
  1U,

  /* Computed Parameter: ManualSwitch2_CurrentSetting_j
   * Referenced by: '<S8>/Manual Switch2'
   */
  1U,

  /* Computed Parameter: ManualSwitch1_CurrentSetting_k
   * Referenced by: '<S8>/Manual Switch1'
   */
  1U,

  /* Computed Parameter: ManualSwitch4_CurrentSetting_i
   * Referenced by: '<S8>/Manual Switch4'
   */
  1U
};
