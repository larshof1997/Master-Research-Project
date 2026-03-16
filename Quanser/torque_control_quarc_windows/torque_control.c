/*
 * torque_control.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "torque_control".
 *
 * Model version              : 1.112
 * Simulink Coder version : 9.0 (R2018b) 24-May-2018
 * C source code generated on : Mon Mar 16 15:01:25 2026
 *
 * Target selection: quarc_windows.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "torque_control.h"
#include "torque_control_private.h"
#include "torque_control_dt.h"

/* Block signals (default storage) */
B_torque_control_T torque_control_B;

/* Block states (default storage) */
DW_torque_control_T torque_control_DW;

/* Real-time model */
RT_MODEL_torque_control_T torque_control_M_;
RT_MODEL_torque_control_T *const torque_control_M = &torque_control_M_;

/* Model output function */
void torque_control_output(void)
{
  /* local block i/o variables */
  real_T rtb_PulseGenerator;
  real_T rtb_DiscreteTimeIntegrator;
  boolean_T rtb_HILReadDigital_o1;
  boolean_T rtb_HILReadDigital_o2;
  boolean_T rtb_HILReadDigital_o3;
  boolean_T rtb_HILReadDigital_o4;
  real_T rtb_Add;
  real_T rtb_Clock1;

  /* S-Function (hil_read_encoder_block): '<Root>/HIL Read Encoder' */

  /* S-Function Block: torque_control/HIL Read Encoder (hil_read_encoder_block) */
  {
    t_error result = hil_read_encoder(torque_control_DW.HILInitialize_Card,
      torque_control_P.HILReadEncoder_channels, 2,
      &torque_control_DW.HILReadEncoder_Buffer[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(torque_control_M, _rt_error_message);
    } else {
      rtb_PulseGenerator = torque_control_DW.HILReadEncoder_Buffer[0];
      rtb_DiscreteTimeIntegrator = torque_control_DW.HILReadEncoder_Buffer[1];
    }
  }

  /* Gain: '<Root>/Motor #1 Encoder Calib1' */
  rtb_PulseGenerator *= torque_control_P.KE_D1;

  /* SampleTimeMath: '<S3>/TSamp'
   *
   * About '<S3>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  torque_control_B.TSamp = rtb_PulseGenerator * torque_control_P.TSamp_WtEt;

  /* Gain: '<Root>/Motor #2 Encoder Calib1' */
  rtb_DiscreteTimeIntegrator *= torque_control_P.KE_D2;

  /* SampleTimeMath: '<S2>/TSamp'
   *
   * About '<S2>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  torque_control_B.TSamp_l = rtb_DiscreteTimeIntegrator *
    torque_control_P.TSamp_WtEt_e;

  /* ManualSwitch: '<Root>/Manual Switch3' incorporates:
   *  Gain: '<Root>/Motor #1 Encoder Calib3'
   *  Gain: '<Root>/Motor #1 Encoder Calib8'
   *  Sum: '<S2>/Diff'
   *  Sum: '<S3>/Diff'
   *  UnitDelay: '<S2>/UD'
   *  UnitDelay: '<S3>/UD'
   */
  if (torque_control_P.ManualSwitch3_CurrentSetting == 1) {
    torque_control_B.ManualSwitch3 = (torque_control_B.TSamp -
      torque_control_DW.UD_DSTATE) * torque_control_P.ke1;
  } else {
    torque_control_B.ManualSwitch3 = (torque_control_B.TSamp_l -
      torque_control_DW.UD_DSTATE_f) * torque_control_P.ke2;
  }

  /* End of ManualSwitch: '<Root>/Manual Switch3' */

  /* Clock: '<S1>/Clock1' */
  rtb_Clock1 = torque_control_M->Timing.t[0];

  /* Gain: '<S1>/Gain' incorporates:
   *  Constant: '<S1>/deltaFreq'
   *  Constant: '<S1>/targetTime'
   *  Product: '<S1>/Product'
   */
  torque_control_B.Gain = (torque_control_P.ChirpSignal_f2 -
    torque_control_P.ChirpSignal_f1) * 6.2831853071795862 /
    torque_control_P.ChirpSignal_T * torque_control_P.Gain_Gain;

  /* Sin: '<Root>/Sine Wave' */
  rtb_Add = sin(torque_control_P.SineWave_Freq * torque_control_M->Timing.t[0] +
                torque_control_P.SineWave_Phase) * torque_control_P.SineWave_Amp
    + torque_control_P.SineWave_Bias;

  /* ManualSwitch: '<Root>/Manual Switch4' incorporates:
   *  Constant: '<S1>/initialFreq'
   *  Product: '<S1>/Product1'
   *  Product: '<S1>/Product2'
   *  Sum: '<S1>/Sum'
   *  Trigonometry: '<S1>/Output'
   */
  if (torque_control_P.ManualSwitch4_CurrentSetting == 1) {
    rtb_Add = sin((rtb_Clock1 * torque_control_B.Gain + 6.2831853071795862 *
                   torque_control_P.ChirpSignal_f1) * rtb_Clock1);
  }

  /* End of ManualSwitch: '<Root>/Manual Switch4' */

  /* Gain: '<Root>/Torque to current ' incorporates:
   *  Constant: '<Root>/tau_ref'
   *  Product: '<Root>/Product'
   */
  torque_control_B.Torquetocurrent = 1.0 / torque_control_P.Kt2 *
    (torque_control_P.tau_ref_Value * rtb_Add);

  /* SampleTimeMath: '<S5>/TSamp'
   *
   * About '<S5>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  torque_control_B.TSamp_lo = torque_control_B.Torquetocurrent *
    torque_control_P.TSamp_WtEt_o;

  /* ManualSwitch: '<Root>/Manual Switch1' incorporates:
   *  Gain: '<Root>/Motor #1 Encoder Calib2'
   *  Gain: '<Root>/Motor #1 Encoder Calib5'
   *  Sum: '<S5>/Diff'
   *  UnitDelay: '<S5>/UD'
   */
  if (torque_control_P.ManualSwitch1_CurrentSetting == 1) {
    torque_control_B.ManualSwitch1 = (torque_control_B.TSamp_lo -
      torque_control_DW.UD_DSTATE_a) * torque_control_P.L1;
  } else {
    torque_control_B.ManualSwitch1 = (torque_control_B.TSamp_lo -
      torque_control_DW.UD_DSTATE_a) * torque_control_P.L2;
  }

  /* End of ManualSwitch: '<Root>/Manual Switch1' */

  /* S-Function (hil_read_analog_block): '<Root>/HIL Read Analog' */

  /* S-Function Block: torque_control/HIL Read Analog (hil_read_analog_block) */
  {
    t_error result = hil_read_analog(torque_control_DW.HILInitialize_Card,
      &torque_control_P.HILReadAnalog_channels, 1,
      &torque_control_DW.HILReadAnalog_Buffer);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(torque_control_M, _rt_error_message);
    }

    torque_control_B.Current = torque_control_DW.HILReadAnalog_Buffer;
  }

  /* Sum: '<Root>/Sum1' */
  torque_control_B.Sum1 = torque_control_B.Torquetocurrent -
    torque_control_B.Current;

  /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
  rtb_DiscreteTimeIntegrator = torque_control_DW.DiscreteTimeIntegrator_DSTATE;

  /* Gain: '<Root>/Gain1' */
  torque_control_B.Gain1 = torque_control_P.Gain1_Gain *
    rtb_DiscreteTimeIntegrator;

  /* SampleTimeMath: '<S4>/TSamp'
   *
   * About '<S4>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  torque_control_B.TSamp_n = torque_control_B.Sum1 *
    torque_control_P.TSamp_WtEt_o3;

  /* Gain: '<Root>/Gain2' incorporates:
   *  Sum: '<S4>/Diff'
   *  UnitDelay: '<S4>/UD'
   */
  torque_control_B.Gain2 = (torque_control_B.TSamp_n -
    torque_control_DW.UD_DSTATE_m) * torque_control_P.Gain2_Gain;

  /* ManualSwitch: '<Root>/Manual Switch2' incorporates:
   *  Gain: '<Root>/Motor #1 Encoder Calib6'
   *  Gain: '<Root>/Motor #1 Encoder Calib7'
   */
  if (torque_control_P.ManualSwitch2_CurrentSetting == 1) {
    rtb_Clock1 = torque_control_P.R1 * torque_control_B.Torquetocurrent;
  } else {
    rtb_Clock1 = torque_control_P.R2 * torque_control_B.Torquetocurrent;
  }

  /* End of ManualSwitch: '<Root>/Manual Switch2' */

  /* Sum: '<Root>/Add' incorporates:
   *  Gain: '<Root>/Gain'
   *  Sum: '<Root>/Add1'
   */
  rtb_Add = ((torque_control_P.Gain_Gain_k * torque_control_B.Sum1 +
              torque_control_B.Gain1) + torque_control_B.Gain2) +
    ((torque_control_B.ManualSwitch3 + rtb_Clock1) +
     torque_control_B.ManualSwitch1);

  /* Saturate: '<Root>/Im_r1: Saturation' */
  if (rtb_Add > torque_control_P.Im_r1Saturation_UpperSat) {
    torque_control_B.Im_r1Saturation = torque_control_P.Im_r1Saturation_UpperSat;
  } else if (rtb_Add < torque_control_P.Im_r1Saturation_LowerSat) {
    torque_control_B.Im_r1Saturation = torque_control_P.Im_r1Saturation_LowerSat;
  } else {
    torque_control_B.Im_r1Saturation = rtb_Add;
  }

  /* End of Saturate: '<Root>/Im_r1: Saturation' */

  /* S-Function (hil_write_analog_block): '<Root>/HIL Write Analog' */

  /* S-Function Block: torque_control/HIL Write Analog (hil_write_analog_block) */
  {
    t_error result;
    result = hil_write_analog(torque_control_DW.HILInitialize_Card,
      &torque_control_P.HILWriteAnalog_channels, 1,
      &torque_control_B.Im_r1Saturation);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(torque_control_M, _rt_error_message);
    }
  }

  /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn1' */
  torque_control_B.VectorConcatenate[0] = torque_control_B.Torquetocurrent;

  /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn2' */
  torque_control_B.VectorConcatenate[1] = torque_control_B.Current;

  /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn3' */
  torque_control_B.VectorConcatenate[2] = torque_control_B.Im_r1Saturation;

  /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn4' */
  torque_control_B.VectorConcatenate[3] = torque_control_B.ManualSwitch3;

  /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
  rtb_PulseGenerator = (torque_control_DW.clockTickCounter <
                        torque_control_P.PulseGenerator_Duty) &&
    (torque_control_DW.clockTickCounter >= 0) ?
    torque_control_P.PulseGenerator_Amp : 0.0;
  if (torque_control_DW.clockTickCounter >=
      torque_control_P.PulseGenerator_Period - 1.0) {
    torque_control_DW.clockTickCounter = 0;
  } else {
    torque_control_DW.clockTickCounter++;
  }

  /* End of DiscretePulseGenerator: '<Root>/Pulse Generator' */
  /* S-Function (hil_write_digital_timebase_block): '<Root>/HIL Write Digital Timebase' */

  /* S-Function Block: torque_control/HIL Write Digital Timebase (hil_write_digital_timebase_block) */
  {
    t_error result;
    torque_control_DW.HILWriteDigitalTimebase_Buffer = (rtb_PulseGenerator != 0);
    result = hil_task_write_digital
      (torque_control_DW.HILWriteDigitalTimebase_Task, 1,
       &torque_control_DW.HILWriteDigitalTimebase_Buffer);
    if (torque_control_DW.HILWriteDigitalTimebase_Started == false && result >=
        0) {
      result = hil_task_start(torque_control_DW.HILWriteDigitalTimebase_Task,
        (t_clock) torque_control_P.HILWriteDigitalTimebase_clock, 100.0, -1);
      torque_control_DW.HILWriteDigitalTimebase_Started = (result == 0);
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(torque_control_M, _rt_error_message);
    }
  }

  /* S-Function (hil_write_digital_block): '<S6>/HIL Write Digital' incorporates:
   *  Constant: '<S6>/Enable: Active Low'
   *  Constant: '<S6>/Master Enable: Active High'
   */

  /* S-Function Block: torque_control/Enable AMPAQ1/HIL Write Digital (hil_write_digital_block) */
  {
    t_error result;
    torque_control_DW.HILWriteDigital_Buffer[0] =
      (torque_control_P.EnableActiveLow_Value[0] != 0);
    torque_control_DW.HILWriteDigital_Buffer[1] =
      (torque_control_P.EnableActiveLow_Value[1] != 0);
    torque_control_DW.HILWriteDigital_Buffer[2] =
      (torque_control_P.MasterEnableActiveHigh_Value != 0);
    result = hil_write_digital(torque_control_DW.HILInitialize_Card,
      torque_control_P.HILWriteDigital_channels, 3,
      &torque_control_DW.HILWriteDigital_Buffer[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(torque_control_M, _rt_error_message);
    }
  }

  /* S-Function (hil_read_digital_block): '<S7>/HIL Read Digital' */

  /* S-Function Block: torque_control/Limit Switches1/HIL Read Digital (hil_read_digital_block) */
  {
    t_error result = hil_read_digital(torque_control_DW.HILInitialize_Card,
      torque_control_P.HILReadDigital_channels, 4,
      &torque_control_DW.HILReadDigital_Buffer[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(torque_control_M, _rt_error_message);
    } else {
      rtb_HILReadDigital_o1 = torque_control_DW.HILReadDigital_Buffer[0];
      rtb_HILReadDigital_o2 = torque_control_DW.HILReadDigital_Buffer[1];
      rtb_HILReadDigital_o3 = torque_control_DW.HILReadDigital_Buffer[2];
      rtb_HILReadDigital_o4 = torque_control_DW.HILReadDigital_Buffer[3];
    }
  }

  /* Logic: '<S7>/Logical Operator4' incorporates:
   *  Constant: '<S7>/Constant'
   *  Logic: '<S7>/Logical Operator2'
   */
  torque_control_B.LogicalOperator4 = ((torque_control_P.LIMIT_SWITCHES_ENABLE
    != 0.0) && (!rtb_HILReadDigital_o1));

  /* Stop: '<S8>/Stop Simulation' incorporates:
   *  Constant: '<S12>/Constant'
   *  RelationalOperator: '<S12>/Compare'
   */
  if (torque_control_B.LogicalOperator4 != torque_control_P.Constant_Value) {
    rtmSetStopRequested(torque_control_M, 1);
  }

  /* End of Stop: '<S8>/Stop Simulation' */

  /* Logic: '<S7>/Logical Operator5' incorporates:
   *  Constant: '<S7>/Constant'
   *  Logic: '<S7>/Logical Operator3'
   */
  torque_control_B.LogicalOperator5 = ((torque_control_P.LIMIT_SWITCHES_ENABLE
    != 0.0) && (!rtb_HILReadDigital_o2));

  /* Stop: '<S9>/Stop Simulation' incorporates:
   *  Constant: '<S13>/Constant'
   *  RelationalOperator: '<S13>/Compare'
   */
  if (torque_control_B.LogicalOperator5 != torque_control_P.Constant_Value_k) {
    rtmSetStopRequested(torque_control_M, 1);
  }

  /* End of Stop: '<S9>/Stop Simulation' */

  /* Logic: '<S7>/Logical Operator6' incorporates:
   *  Constant: '<S7>/Constant'
   *  Logic: '<S7>/Logical Operator1'
   */
  torque_control_B.LogicalOperator6 = ((torque_control_P.LIMIT_SWITCHES_ENABLE
    != 0.0) && (!rtb_HILReadDigital_o3));

  /* Stop: '<S10>/Stop Simulation' incorporates:
   *  Constant: '<S14>/Constant'
   *  RelationalOperator: '<S14>/Compare'
   */
  if (torque_control_B.LogicalOperator6 != torque_control_P.Constant_Value_m) {
    rtmSetStopRequested(torque_control_M, 1);
  }

  /* End of Stop: '<S10>/Stop Simulation' */

  /* Logic: '<S7>/Logical Operator7' incorporates:
   *  Constant: '<S7>/Constant'
   *  Logic: '<S7>/Logical Operator'
   */
  torque_control_B.LogicalOperator7 = ((torque_control_P.LIMIT_SWITCHES_ENABLE
    != 0.0) && (!rtb_HILReadDigital_o4));

  /* Stop: '<S11>/Stop Simulation' incorporates:
   *  Constant: '<S15>/Constant'
   *  RelationalOperator: '<S15>/Compare'
   */
  if (torque_control_B.LogicalOperator7 != torque_control_P.Constant_Value_me) {
    rtmSetStopRequested(torque_control_M, 1);
  }

  /* End of Stop: '<S11>/Stop Simulation' */
}

/* Model update function */
void torque_control_update(void)
{
  /* Update for UnitDelay: '<S3>/UD' */
  torque_control_DW.UD_DSTATE = torque_control_B.TSamp;

  /* Update for UnitDelay: '<S2>/UD' */
  torque_control_DW.UD_DSTATE_f = torque_control_B.TSamp_l;

  /* Update for UnitDelay: '<S5>/UD' */
  torque_control_DW.UD_DSTATE_a = torque_control_B.TSamp_lo;

  /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
  torque_control_DW.DiscreteTimeIntegrator_DSTATE +=
    torque_control_P.DiscreteTimeIntegrator_gainval * torque_control_B.Sum1;

  /* Update for UnitDelay: '<S4>/UD' */
  torque_control_DW.UD_DSTATE_m = torque_control_B.TSamp_n;

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++torque_control_M->Timing.clockTick0)) {
    ++torque_control_M->Timing.clockTickH0;
  }

  torque_control_M->Timing.t[0] = torque_control_M->Timing.clockTick0 *
    torque_control_M->Timing.stepSize0 + torque_control_M->Timing.clockTickH0 *
    torque_control_M->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [0.01s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++torque_control_M->Timing.clockTick1)) {
      ++torque_control_M->Timing.clockTickH1;
    }

    torque_control_M->Timing.t[1] = torque_control_M->Timing.clockTick1 *
      torque_control_M->Timing.stepSize1 + torque_control_M->Timing.clockTickH1 *
      torque_control_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Model initialize function */
void torque_control_initialize(void)
{
  /* Start for DiscretePulseGenerator: '<Root>/Pulse Generator' */
  torque_control_DW.clockTickCounter = 0;

  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: torque_control/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8", "0", &torque_control_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(torque_control_M, _rt_error_message);
      return;
    }

    is_switching = false;
    if ((torque_control_P.HILInitialize_CKPStart && !is_switching) ||
        (torque_control_P.HILInitialize_CKPEnter && is_switching)) {
      result = hil_set_clock_mode(torque_control_DW.HILInitialize_Card, (t_clock
        *) torque_control_P.HILInitialize_CKChannels, 2U, (t_clock_mode *)
        torque_control_P.HILInitialize_CKModes);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(torque_control_M, _rt_error_message);
        return;
      }
    }

    result = hil_watchdog_clear(torque_control_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(torque_control_M, _rt_error_message);
      return;
    }

    if ((torque_control_P.HILInitialize_AIPStart && !is_switching) ||
        (torque_control_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &torque_control_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (torque_control_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &torque_control_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = torque_control_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges(torque_control_DW.HILInitialize_Card,
        torque_control_P.HILInitialize_AIChannels, 8U,
        &torque_control_DW.HILInitialize_AIMinimums[0],
        &torque_control_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(torque_control_M, _rt_error_message);
        return;
      }
    }

    if ((torque_control_P.HILInitialize_AOPStart && !is_switching) ||
        (torque_control_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &torque_control_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (torque_control_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &torque_control_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = torque_control_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges(torque_control_DW.HILInitialize_Card,
        torque_control_P.HILInitialize_AOChannels, 8U,
        &torque_control_DW.HILInitialize_AOMinimums[0],
        &torque_control_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(torque_control_M, _rt_error_message);
        return;
      }
    }

    if ((torque_control_P.HILInitialize_AOStart && !is_switching) ||
        (torque_control_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &torque_control_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = torque_control_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(torque_control_DW.HILInitialize_Card,
        torque_control_P.HILInitialize_AOChannels, 8U,
        &torque_control_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(torque_control_M, _rt_error_message);
        return;
      }
    }

    if (torque_control_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &torque_control_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = torque_control_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (torque_control_DW.HILInitialize_Card,
         torque_control_P.HILInitialize_AOChannels, 8U,
         &torque_control_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(torque_control_M, _rt_error_message);
        return;
      }
    }

    result = hil_set_digital_directions(torque_control_DW.HILInitialize_Card,
      torque_control_P.HILInitialize_DIChannels, 8U,
      torque_control_P.HILInitialize_DOChannels, 9U);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(torque_control_M, _rt_error_message);
      return;
    }

    if ((torque_control_P.HILInitialize_DOStart && !is_switching) ||
        (torque_control_P.HILInitialize_DOEnter && is_switching)) {
      {
        int_T i1;
        boolean_T *dw_DOBits = &torque_control_DW.HILInitialize_DOBits[0];
        for (i1=0; i1 < 9; i1++) {
          dw_DOBits[i1] = torque_control_P.HILInitialize_DOInitial;
        }
      }

      result = hil_write_digital(torque_control_DW.HILInitialize_Card,
        torque_control_P.HILInitialize_DOChannels, 9U, (t_boolean *)
        &torque_control_DW.HILInitialize_DOBits[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(torque_control_M, _rt_error_message);
        return;
      }
    }

    if (torque_control_P.HILInitialize_DOReset) {
      {
        int_T i1;
        int32_T *dw_DOStates = &torque_control_DW.HILInitialize_DOStates[0];
        for (i1=0; i1 < 9; i1++) {
          dw_DOStates[i1] = torque_control_P.HILInitialize_DOWatchdog;
        }
      }

      result = hil_watchdog_set_digital_expiration_state
        (torque_control_DW.HILInitialize_Card,
         torque_control_P.HILInitialize_DOChannels, 9U, (const t_digital_state *)
         &torque_control_DW.HILInitialize_DOStates[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(torque_control_M, _rt_error_message);
        return;
      }
    }

    if ((torque_control_P.HILInitialize_EIPStart && !is_switching) ||
        (torque_control_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &torque_control_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = torque_control_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (torque_control_DW.HILInitialize_Card,
         torque_control_P.HILInitialize_EIChannels, 8U,
         (t_encoder_quadrature_mode *)
         &torque_control_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(torque_control_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_FilterFrequency =
          &torque_control_DW.HILInitialize_FilterFrequency[0];
        for (i1=0; i1 < 8; i1++) {
          dw_FilterFrequency[i1] = torque_control_P.HILInitialize_EIFrequency;
        }
      }

      result = hil_set_encoder_filter_frequency
        (torque_control_DW.HILInitialize_Card,
         torque_control_P.HILInitialize_EIChannels, 8U,
         &torque_control_DW.HILInitialize_FilterFrequency[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(torque_control_M, _rt_error_message);
        return;
      }
    }

    if ((torque_control_P.HILInitialize_EIStart && !is_switching) ||
        (torque_control_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &torque_control_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = torque_control_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(torque_control_DW.HILInitialize_Card,
        torque_control_P.HILInitialize_EIChannels, 8U,
        &torque_control_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(torque_control_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_write_digital_timebase_block): '<Root>/HIL Write Digital Timebase' */

  /* S-Function Block: torque_control/HIL Write Digital Timebase (hil_write_digital_timebase_block) */
  {
    t_error result;
    torque_control_DW.HILWriteDigitalTimebase_Started = false;
    result = hil_task_create_digital_writer(torque_control_DW.HILInitialize_Card,
      torque_control_P.HILWriteDigitalTimebase_samples,
      &torque_control_P.HILWriteDigitalTimebase_channel, 1,
      &torque_control_DW.HILWriteDigitalTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(torque_control_M, _rt_error_message);
    }
  }

  /* InitializeConditions for UnitDelay: '<S3>/UD' */
  torque_control_DW.UD_DSTATE = torque_control_P.DiscreteDerivative1_ICPrevScale;

  /* InitializeConditions for UnitDelay: '<S2>/UD' */
  torque_control_DW.UD_DSTATE_f =
    torque_control_P.DiscreteDerivative_ICPrevScaled;

  /* InitializeConditions for UnitDelay: '<S5>/UD' */
  torque_control_DW.UD_DSTATE_a =
    torque_control_P.DiscreteDerivative3_ICPrevScale;

  /* InitializeConditions for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
  torque_control_DW.DiscreteTimeIntegrator_DSTATE =
    torque_control_P.DiscreteTimeIntegrator_IC;

  /* InitializeConditions for UnitDelay: '<S4>/UD' */
  torque_control_DW.UD_DSTATE_m =
    torque_control_P.DiscreteDerivative2_ICPrevScale;
}

/* Model terminate function */
void torque_control_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: torque_control/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_digital_outputs = 0;
    hil_task_stop_all(torque_control_DW.HILInitialize_Card);
    hil_monitor_stop_all(torque_control_DW.HILInitialize_Card);
    is_switching = false;
    if ((torque_control_P.HILInitialize_AOTerminate && !is_switching) ||
        (torque_control_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &torque_control_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = torque_control_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((torque_control_P.HILInitialize_DOTerminate && !is_switching) ||
        (torque_control_P.HILInitialize_DOExit && is_switching)) {
      {
        int_T i1;
        boolean_T *dw_DOBits = &torque_control_DW.HILInitialize_DOBits[0];
        for (i1=0; i1 < 9; i1++) {
          dw_DOBits[i1] = torque_control_P.HILInitialize_DOFinal;
        }
      }

      num_final_digital_outputs = 9U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_digital_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(torque_control_DW.HILInitialize_Card
                         , torque_control_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , NULL, 0
                         , torque_control_P.HILInitialize_DOChannels,
                         num_final_digital_outputs
                         , NULL, 0
                         , &torque_control_DW.HILInitialize_AOVoltages[0]
                         , NULL
                         , (t_boolean *)
                         &torque_control_DW.HILInitialize_DOBits[0]
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(torque_control_DW.HILInitialize_Card,
            torque_control_P.HILInitialize_AOChannels, num_final_analog_outputs,
            &torque_control_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_digital_outputs > 0) {
          local_result = hil_write_digital(torque_control_DW.HILInitialize_Card,
            torque_control_P.HILInitialize_DOChannels, num_final_digital_outputs,
            (t_boolean *) &torque_control_DW.HILInitialize_DOBits[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(torque_control_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(torque_control_DW.HILInitialize_Card);
    hil_monitor_delete_all(torque_control_DW.HILInitialize_Card);
    hil_close(torque_control_DW.HILInitialize_Card);
    torque_control_DW.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  torque_control_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  torque_control_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  torque_control_initialize();
}

void MdlTerminate(void)
{
  torque_control_terminate();
}

/* Registration function */
RT_MODEL_torque_control_T *torque_control(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)torque_control_M, 0,
                sizeof(RT_MODEL_torque_control_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&torque_control_M->solverInfo,
                          &torque_control_M->Timing.simTimeStep);
    rtsiSetTPtr(&torque_control_M->solverInfo, &rtmGetTPtr(torque_control_M));
    rtsiSetStepSizePtr(&torque_control_M->solverInfo,
                       &torque_control_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&torque_control_M->solverInfo, (&rtmGetErrorStatus
      (torque_control_M)));
    rtsiSetRTModelPtr(&torque_control_M->solverInfo, torque_control_M);
  }

  rtsiSetSimTimeStep(&torque_control_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&torque_control_M->solverInfo,"FixedStepDiscrete");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = torque_control_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    torque_control_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    torque_control_M->Timing.sampleTimes =
      (&torque_control_M->Timing.sampleTimesArray[0]);
    torque_control_M->Timing.offsetTimes =
      (&torque_control_M->Timing.offsetTimesArray[0]);

    /* task periods */
    torque_control_M->Timing.sampleTimes[0] = (0.0);
    torque_control_M->Timing.sampleTimes[1] = (0.01);

    /* task offsets */
    torque_control_M->Timing.offsetTimes[0] = (0.0);
    torque_control_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(torque_control_M, &torque_control_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = torque_control_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    torque_control_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(torque_control_M, 30.0);
  torque_control_M->Timing.stepSize0 = 0.01;
  torque_control_M->Timing.stepSize1 = 0.01;

  /* External mode info */
  torque_control_M->Sizes.checksums[0] = (800594721U);
  torque_control_M->Sizes.checksums[1] = (3094476336U);
  torque_control_M->Sizes.checksums[2] = (1805165371U);
  torque_control_M->Sizes.checksums[3] = (1842586916U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[8];
    torque_control_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = &rtAlwaysEnabled;
    systemRan[7] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(torque_control_M->extModeInfo,
      &torque_control_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(torque_control_M->extModeInfo,
                        torque_control_M->Sizes.checksums);
    rteiSetTPtr(torque_control_M->extModeInfo, rtmGetTPtr(torque_control_M));
  }

  torque_control_M->solverInfoPtr = (&torque_control_M->solverInfo);
  torque_control_M->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&torque_control_M->solverInfo, 0.01);
  rtsiSetSolverMode(&torque_control_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  torque_control_M->blockIO = ((void *) &torque_control_B);
  (void) memset(((void *) &torque_control_B), 0,
                sizeof(B_torque_control_T));

  {
    torque_control_B.TSamp = 0.0;
    torque_control_B.TSamp_l = 0.0;
    torque_control_B.ManualSwitch3 = 0.0;
    torque_control_B.Gain = 0.0;
    torque_control_B.Torquetocurrent = 0.0;
    torque_control_B.TSamp_lo = 0.0;
    torque_control_B.ManualSwitch1 = 0.0;
    torque_control_B.Current = 0.0;
    torque_control_B.Sum1 = 0.0;
    torque_control_B.Gain1 = 0.0;
    torque_control_B.TSamp_n = 0.0;
    torque_control_B.Gain2 = 0.0;
    torque_control_B.Im_r1Saturation = 0.0;
    torque_control_B.VectorConcatenate[0] = 0.0;
    torque_control_B.VectorConcatenate[1] = 0.0;
    torque_control_B.VectorConcatenate[2] = 0.0;
    torque_control_B.VectorConcatenate[3] = 0.0;
  }

  /* parameters */
  torque_control_M->defaultParam = ((real_T *)&torque_control_P);

  /* states (dwork) */
  torque_control_M->dwork = ((void *) &torque_control_DW);
  (void) memset((void *)&torque_control_DW, 0,
                sizeof(DW_torque_control_T));
  torque_control_DW.UD_DSTATE = 0.0;
  torque_control_DW.UD_DSTATE_f = 0.0;
  torque_control_DW.UD_DSTATE_a = 0.0;
  torque_control_DW.DiscreteTimeIntegrator_DSTATE = 0.0;
  torque_control_DW.UD_DSTATE_m = 0.0;
  torque_control_DW.HILReadAnalog_Buffer = 0.0;

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      torque_control_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      torque_control_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      torque_control_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      torque_control_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      torque_control_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      torque_control_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    torque_control_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 17;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  torque_control_M->Sizes.numContStates = (0);/* Number of continuous states */
  torque_control_M->Sizes.numY = (0);  /* Number of model outputs */
  torque_control_M->Sizes.numU = (0);  /* Number of model inputs */
  torque_control_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  torque_control_M->Sizes.numSampTimes = (2);/* Number of sample times */
  torque_control_M->Sizes.numBlocks = (98);/* Number of blocks */
  torque_control_M->Sizes.numBlockIO = (18);/* Number of block outputs */
  torque_control_M->Sizes.numBlockPrms = (172);/* Sum of parameter "widths" */
  return torque_control_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
