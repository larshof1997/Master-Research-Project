/*
 * TRACKING_CONTROL_RasconIET_data.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "TRACKING_CONTROL_RasconIET".
 *
 * Model version              : 1.176
 * Simulink Coder version : 9.0 (R2018b) 24-May-2018
 * C source code generated on : Mon Mar 16 13:33:07 2026
 *
 * Target selection: quarc_windows.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "TRACKING_CONTROL_RasconIET.h"
#include "TRACKING_CONTROL_RasconIET_private.h"

/* Block parameters (default storage) */
P_TRACKING_CONTROL_RasconIET_T TRACKING_CONTROL_RasconIET_P = {
  /* Variable: KE_D1
   * Referenced by:
   *   '<Root>/Motor #1 Encoder Calib1'
   *   '<S4>/Motor #1 Encoder Calib1'
   *   '<S5>/Motor #1 Encoder Calib1'
   */
  1.5339807878856413E-5,

  /* Variable: KE_D2
   * Referenced by:
   *   '<Root>/Motor #2 Encoder Calib1'
   *   '<S4>/Motor #2 Encoder Calib1'
   *   '<S5>/Motor #2 Encoder Calib1'
   */
  3.0679615757712826E-5,

  /* Variable: Kt1
   * Referenced by: '<S5>/Torque to current '
   */
  3.018583,

  /* Variable: Kt2
   * Referenced by: '<S4>/Torque to current '
   */
  1.111065,

  /* Variable: L1
   * Referenced by:
   *   '<S4>/Motor #1 Encoder Calib2'
   *   '<S5>/Motor #1 Encoder Calib2'
   */
  0.047544,

  /* Variable: L2
   * Referenced by:
   *   '<S4>/Motor #1 Encoder Calib5'
   *   '<S5>/Motor #1 Encoder Calib5'
   */
  0.04819,

  /* Variable: LIMIT_SWITCHES_ENABLE
   * Referenced by: '<S2>/Constant'
   */
  1.0,

  /* Variable: R1
   * Referenced by:
   *   '<S4>/Motor #1 Encoder Calib6'
   *   '<S5>/Motor #1 Encoder Calib6'
   *   '<S5>/Saturation'
   */
  4.2737,

  /* Variable: R2
   * Referenced by:
   *   '<S4>/Motor #1 Encoder Calib7'
   *   '<S4>/Saturation'
   *   '<S5>/Motor #1 Encoder Calib7'
   */
  4.0364,

  /* Variable: a1_hat
   * Referenced by: '<Root>/Constant'
   */
  0.092202,

  /* Variable: a2_hat
   * Referenced by: '<Root>/Constant1'
   */
  0.023242,

  /* Variable: b1_hat
   * Referenced by: '<Root>/Constant5'
   */
  0.396193,

  /* Variable: b2_hat
   * Referenced by: '<Root>/Constant4'
   */
  0.195026,

  /* Variable: b_hat
   * Referenced by: '<Root>/Constant2'
   */
  0.027542,

  /* Variable: dt
   * Referenced by: '<Root>/Constant3'
   */
  0.001,

  /* Variable: i_sat1
   * Referenced by: '<S5>/Saturation'
   */
  0.92,

  /* Variable: i_sat2
   * Referenced by: '<S4>/Saturation'
   */
  1.2,

  /* Variable: ke1
   * Referenced by:
   *   '<S4>/Motor #1 Encoder Calib3'
   *   '<S5>/Motor #1 Encoder Calib3'
   */
  0.0,

  /* Variable: ke2
   * Referenced by:
   *   '<S4>/Motor #1 Encoder Calib8'
   *   '<S5>/Motor #1 Encoder Calib8'
   */
  0.0,

  /* Variable: ki1
   * Referenced by:
   *   '<S4>/Gain1'
   *   '<S5>/Gain1'
   */
  0.0,

  /* Variable: kp1
   * Referenced by: '<S5>/Gain'
   */
  2.0,

  /* Variable: kp2
   * Referenced by: '<S4>/Gain'
   */
  0.5,

  /* Mask Parameter: DiscreteDerivative3_ICPrevScale
   * Referenced by: '<S17>/UD'
   */
  0.0,

  /* Mask Parameter: DiscreteDerivative_ICPrevScaled
   * Referenced by: '<S14>/UD'
   */
  0.0,

  /* Mask Parameter: DiscreteDerivative2_ICPrevScale
   * Referenced by: '<S16>/UD'
   */
  0.0,

  /* Mask Parameter: DiscreteDerivative1_ICPrevScale
   * Referenced by: '<S15>/UD'
   */
  0.0,

  /* Mask Parameter: DiscreteDerivative3_ICPrevSca_k
   * Referenced by: '<S21>/UD'
   */
  0.0,

  /* Mask Parameter: DiscreteDerivative_ICPrevScal_n
   * Referenced by: '<S18>/UD'
   */
  0.0,

  /* Mask Parameter: DiscreteDerivative2_ICPrevSca_b
   * Referenced by: '<S20>/UD'
   */
  0.0,

  /* Mask Parameter: DiscreteDerivative1_ICPrevSca_n
   * Referenced by: '<S19>/UD'
   */
  0.0,

  /* Mask Parameter: HILWriteDigitalTimebase_clock
   * Referenced by: '<Root>/HIL Write Digital Timebase'
   */
  0,

  /* Mask Parameter: HILReadEncoder_channels
   * Referenced by: '<Root>/HIL Read Encoder'
   */
  { 0U, 2U },

  /* Mask Parameter: HILReadEncoder_channels_n
   * Referenced by: '<S4>/HIL Read Encoder'
   */
  { 0U, 2U },

  /* Mask Parameter: HILReadAnalog_channels
   * Referenced by: '<S4>/HIL Read Analog'
   */
  1U,

  /* Mask Parameter: HILWriteAnalog_channels
   * Referenced by: '<S4>/HIL Write Analog'
   */
  1U,

  /* Mask Parameter: HILReadEncoder_channels_l
   * Referenced by: '<S5>/HIL Read Encoder'
   */
  { 0U, 2U },

  /* Mask Parameter: HILReadAnalog_channels_b
   * Referenced by: '<S5>/HIL Read Analog'
   */
  0U,

  /* Mask Parameter: HILWriteAnalog_channels_a
   * Referenced by: '<S5>/HIL Write Analog'
   */
  0U,

  /* Mask Parameter: HILWriteDigitalTimebase_channel
   * Referenced by: '<Root>/HIL Write Digital Timebase'
   */
  16U,

  /* Mask Parameter: HILWriteDigital_channels
   * Referenced by: '<S1>/HIL Write Digital'
   */
  { 0U, 1U, 4U },

  /* Mask Parameter: HILReadDigital_channels
   * Referenced by: '<S1>/HIL Read Digital'
   */
  { 8U, 9U, 12U },

  /* Mask Parameter: HILReadDigital_channels_p
   * Referenced by: '<S2>/HIL Read Digital'
   */
  { 8U, 9U, 10U, 11U },

  /* Mask Parameter: HILWriteDigitalTimebase_samples
   * Referenced by: '<Root>/HIL Write Digital Timebase'
   */
  1000U,

  /* Mask Parameter: StopwithMessage_message_icon
   * Referenced by: '<S6>/Show Message on Host'
   */
  1,

  /* Mask Parameter: StopwithMessage1_message_icon
   * Referenced by: '<S7>/Show Message on Host'
   */
  1,

  /* Mask Parameter: StopwithMessage2_message_icon
   * Referenced by: '<S8>/Show Message on Host'
   */
  1,

  /* Mask Parameter: StopwithMessage3_message_icon
   * Referenced by: '<S9>/Show Message on Host'
   */
  1,

  /* Expression: 0
   * Referenced by: '<Root>/Unit Delay2'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<Root>/Unit Delay3'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<Root>/Unit Delay1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<Root>/Unit Delay'
   */
  0.0,

  /* Expression: 15
   * Referenced by: '<Root>/Constant10'
   */
  15.0,

  /* Expression: 3
   * Referenced by: '<Root>/Constant11'
   */
  3.0,

  /* Expression: 0
   * Referenced by: '<Root>/Unit Delay4'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<Root>/Unit Delay5'
   */
  0.0,

  /* Computed Parameter: TSamp_WtEt
   * Referenced by: '<S17>/TSamp'
   */
  1000.0,

  /* Computed Parameter: TSamp_WtEt_p
   * Referenced by: '<S14>/TSamp'
   */
  1000.0,

  /* Computed Parameter: TSamp_WtEt_i
   * Referenced by: '<S16>/TSamp'
   */
  1000.0,

  /* Computed Parameter: DiscreteTimeIntegrator_gainval
   * Referenced by: '<S4>/Discrete-Time Integrator'
   */
  0.001,

  /* Expression: 0
   * Referenced by: '<S4>/Discrete-Time Integrator'
   */
  0.0,

  /* Computed Parameter: TSamp_WtEt_o
   * Referenced by: '<S15>/TSamp'
   */
  1000.0,

  /* Expression: 0
   * Referenced by: '<S4>/Gain2'
   */
  0.0,

  /* Computed Parameter: TSamp_WtEt_d
   * Referenced by: '<S21>/TSamp'
   */
  1000.0,

  /* Computed Parameter: TSamp_WtEt_m
   * Referenced by: '<S18>/TSamp'
   */
  1000.0,

  /* Computed Parameter: TSamp_WtEt_c
   * Referenced by: '<S20>/TSamp'
   */
  1000.0,

  /* Computed Parameter: DiscreteTimeIntegrator_gainva_p
   * Referenced by: '<S5>/Discrete-Time Integrator'
   */
  0.001,

  /* Expression: 0
   * Referenced by: '<S5>/Discrete-Time Integrator'
   */
  0.0,

  /* Computed Parameter: TSamp_WtEt_f
   * Referenced by: '<S19>/TSamp'
   */
  1000.0,

  /* Expression: 0
   * Referenced by: '<S5>/Gain2'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<Root>/Pulse Generator'
   */
  1.0,

  /* Computed Parameter: PulseGenerator_Period
   * Referenced by: '<Root>/Pulse Generator'
   */
  20.0,

  /* Computed Parameter: PulseGenerator_Duty
   * Referenced by: '<Root>/Pulse Generator'
   */
  10.0,

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
   * Referenced by: '<S1>/Enable: Active Low'
   */
  { 0.0, 0.0 },

  /* Expression: 1
   * Referenced by: '<S1>/Master Enable: Active High'
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
   * Referenced by: '<Root>/HIL Read Encoder'
   */
  1,

  /* Computed Parameter: HILReadEncoder_Active_l
   * Referenced by: '<S4>/HIL Read Encoder'
   */
  1,

  /* Computed Parameter: HILReadAnalog_Active
   * Referenced by: '<S4>/HIL Read Analog'
   */
  1,

  /* Computed Parameter: HILWriteAnalog_Active
   * Referenced by: '<S4>/HIL Write Analog'
   */
  0,

  /* Computed Parameter: HILReadEncoder_Active_d
   * Referenced by: '<S5>/HIL Read Encoder'
   */
  1,

  /* Computed Parameter: HILReadAnalog_Active_n
   * Referenced by: '<S5>/HIL Read Analog'
   */
  1,

  /* Computed Parameter: HILWriteAnalog_Active_e
   * Referenced by: '<S5>/HIL Write Analog'
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
   * Referenced by: '<S1>/HIL Write Digital'
   */
  0,

  /* Computed Parameter: HILReadDigital_Active
   * Referenced by: '<S1>/HIL Read Digital'
   */
  1,

  /* Computed Parameter: HILReadDigital_Active_e
   * Referenced by: '<S2>/HIL Read Digital'
   */
  1,

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S10>/Constant'
   */
  0,

  /* Computed Parameter: Constant_Value_o
   * Referenced by: '<S11>/Constant'
   */
  0,

  /* Computed Parameter: Constant_Value_f
   * Referenced by: '<S12>/Constant'
   */
  0,

  /* Computed Parameter: Constant_Value_d
   * Referenced by: '<S13>/Constant'
   */
  0,

  /* Computed Parameter: ManualSwitch3_CurrentSetting
   * Referenced by: '<S4>/Manual Switch3'
   */
  0U,

  /* Computed Parameter: ManualSwitch2_CurrentSetting
   * Referenced by: '<S4>/Manual Switch2'
   */
  0U,

  /* Computed Parameter: ManualSwitch1_CurrentSetting
   * Referenced by: '<S4>/Manual Switch1'
   */
  0U,

  /* Computed Parameter: ManualSwitch4_CurrentSetting
   * Referenced by: '<S4>/Manual Switch4'
   */
  0U,

  /* Computed Parameter: ManualSwitch3_CurrentSetting_g
   * Referenced by: '<S5>/Manual Switch3'
   */
  1U,

  /* Computed Parameter: ManualSwitch2_CurrentSetting_o
   * Referenced by: '<S5>/Manual Switch2'
   */
  1U,

  /* Computed Parameter: ManualSwitch1_CurrentSetting_i
   * Referenced by: '<S5>/Manual Switch1'
   */
  1U,

  /* Computed Parameter: ManualSwitch4_CurrentSetting_l
   * Referenced by: '<S5>/Manual Switch4'
   */
  1U
};
