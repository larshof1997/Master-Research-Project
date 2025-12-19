/*
 * motor_calibration.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "motor_calibration".
 *
 * Model version              : 1.73
 * Simulink Coder version : 9.0 (R2018b) 24-May-2018
 * C source code generated on : Fri Dec 19 14:23:41 2025
 *
 * Target selection: quarc_windows.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "motor_calibration.h"
#include "motor_calibration_private.h"
#include "motor_calibration_dt.h"

/* Block signals (default storage) */
B_motor_calibration_T motor_calibration_B;

/* Block states (default storage) */
DW_motor_calibration_T motor_calibration_DW;

/* Real-time model */
RT_MODEL_motor_calibration_T motor_calibration_M_;
RT_MODEL_motor_calibration_T *const motor_calibration_M = &motor_calibration_M_;

/* Model output function */
void motor_calibration_output(void)
{
  /* local block i/o variables */
  real_T rtb_PulseGenerator;
  boolean_T rtb_HILReadDigital_o1;
  boolean_T rtb_HILReadDigital_o2;
  boolean_T rtb_HILReadDigital_o3;
  boolean_T rtb_HILReadDigital_o4;

  /* Gain: '<Root>/Max Voltage' incorporates:
   *  Gain: '<Root>/Amplitude'
   *  Sin: '<Root>/Sine Wave'
   */
  motor_calibration_B.MaxVoltage = (sin(motor_calibration_P.SineWave_Freq *
    motor_calibration_M->Timing.t[0] + motor_calibration_P.SineWave_Phase) *
    motor_calibration_P.SineWave_Amp + motor_calibration_P.SineWave_Bias) *
    motor_calibration_P.Amplitude_Gain * motor_calibration_P.MaxVoltage_Gain;

  /* S-Function (hil_write_analog_block): '<Root>/HIL Write Analog' */

  /* S-Function Block: motor_calibration/HIL Write Analog (hil_write_analog_block) */
  {
    t_error result;
    result = hil_write_analog(motor_calibration_DW.HILInitialize_Card,
      &motor_calibration_P.HILWriteAnalog_channels, 1,
      &motor_calibration_B.MaxVoltage);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(motor_calibration_M, _rt_error_message);
    }
  }

  /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn1' */
  motor_calibration_B.VectorConcatenate[0] = motor_calibration_B.MaxVoltage;

  /* S-Function (hil_read_analog_block): '<Root>/HIL Read Analog' */

  /* S-Function Block: motor_calibration/HIL Read Analog (hil_read_analog_block) */
  {
    t_error result = hil_read_analog(motor_calibration_DW.HILInitialize_Card,
      &motor_calibration_P.HILReadAnalog_channels, 1,
      &motor_calibration_DW.HILReadAnalog_Buffer);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(motor_calibration_M, _rt_error_message);
    }

    motor_calibration_B.VectorConcatenate[1] =
      motor_calibration_DW.HILReadAnalog_Buffer;
  }

  /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
  rtb_PulseGenerator = (motor_calibration_DW.clockTickCounter <
                        motor_calibration_P.PulseGenerator_Duty) &&
    (motor_calibration_DW.clockTickCounter >= 0) ?
    motor_calibration_P.PulseGenerator_Amp : 0.0;
  if (motor_calibration_DW.clockTickCounter >=
      motor_calibration_P.PulseGenerator_Period - 1.0) {
    motor_calibration_DW.clockTickCounter = 0;
  } else {
    motor_calibration_DW.clockTickCounter++;
  }

  /* End of DiscretePulseGenerator: '<Root>/Pulse Generator' */
  /* S-Function (hil_write_digital_timebase_block): '<Root>/HIL Write Digital Timebase' */

  /* S-Function Block: motor_calibration/HIL Write Digital Timebase (hil_write_digital_timebase_block) */
  {
    t_error result;
    motor_calibration_DW.HILWriteDigitalTimebase_Buffer = (rtb_PulseGenerator !=
      0);
    result = hil_task_write_digital
      (motor_calibration_DW.HILWriteDigitalTimebase_Task, 1,
       &motor_calibration_DW.HILWriteDigitalTimebase_Buffer);
    if (motor_calibration_DW.HILWriteDigitalTimebase_Started == false && result >=
        0) {
      result = hil_task_start(motor_calibration_DW.HILWriteDigitalTimebase_Task,
        (t_clock) motor_calibration_P.HILWriteDigitalTimebase_clock, 500.0, -1);
      motor_calibration_DW.HILWriteDigitalTimebase_Started = (result == 0);
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(motor_calibration_M, _rt_error_message);
    }
  }

  /* S-Function (hil_write_digital_block): '<S1>/HIL Write Digital' incorporates:
   *  Constant: '<S1>/Enable: Active Low'
   *  Constant: '<S1>/Master Enable: Active High'
   */

  /* S-Function Block: motor_calibration/Enable AMPAQ/HIL Write Digital (hil_write_digital_block) */
  {
    t_error result;
    motor_calibration_DW.HILWriteDigital_Buffer[0] =
      (motor_calibration_P.EnableActiveLow_Value[0] != 0);
    motor_calibration_DW.HILWriteDigital_Buffer[1] =
      (motor_calibration_P.EnableActiveLow_Value[1] != 0);
    motor_calibration_DW.HILWriteDigital_Buffer[2] =
      (motor_calibration_P.MasterEnableActiveHigh_Value != 0);
    result = hil_write_digital(motor_calibration_DW.HILInitialize_Card,
      motor_calibration_P.HILWriteDigital_channels, 3,
      &motor_calibration_DW.HILWriteDigital_Buffer[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(motor_calibration_M, _rt_error_message);
    }
  }

  /* S-Function (hil_read_digital_block): '<S1>/HIL Read Digital' */

  /* S-Function Block: motor_calibration/Enable AMPAQ/HIL Read Digital (hil_read_digital_block) */
  {
    t_error result = hil_read_digital(motor_calibration_DW.HILInitialize_Card,
      motor_calibration_P.HILReadDigital_channels, 3,
      &motor_calibration_DW.HILReadDigital_Buffer[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(motor_calibration_M, _rt_error_message);
    } else {
      motor_calibration_B.HILReadDigital_o1 =
        motor_calibration_DW.HILReadDigital_Buffer[0];
      motor_calibration_B.HILReadDigital_o2 =
        motor_calibration_DW.HILReadDigital_Buffer[1];
      motor_calibration_B.HILReadDigital_o3 =
        motor_calibration_DW.HILReadDigital_Buffer[2];
    }
  }

  /* S-Function (hil_read_digital_block): '<S2>/HIL Read Digital' */

  /* S-Function Block: motor_calibration/Limit Switches/HIL Read Digital (hil_read_digital_block) */
  {
    t_error result = hil_read_digital(motor_calibration_DW.HILInitialize_Card,
      motor_calibration_P.HILReadDigital_channels_p, 4,
      &motor_calibration_DW.HILReadDigital_Buffer_c[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(motor_calibration_M, _rt_error_message);
    } else {
      rtb_HILReadDigital_o1 = motor_calibration_DW.HILReadDigital_Buffer_c[0];
      rtb_HILReadDigital_o2 = motor_calibration_DW.HILReadDigital_Buffer_c[1];
      rtb_HILReadDigital_o3 = motor_calibration_DW.HILReadDigital_Buffer_c[2];
      rtb_HILReadDigital_o4 = motor_calibration_DW.HILReadDigital_Buffer_c[3];
    }
  }

  /* Logic: '<S2>/Logical Operator4' incorporates:
   *  Constant: '<S2>/Constant'
   *  Logic: '<S2>/Logical Operator2'
   */
  motor_calibration_B.LogicalOperator4 =
    ((motor_calibration_P.LIMIT_SWITCHES_ENABLE != 0.0) &&
     (!rtb_HILReadDigital_o1));

  /* Stop: '<S3>/Stop Simulation' incorporates:
   *  Constant: '<S7>/Constant'
   *  RelationalOperator: '<S7>/Compare'
   */
  if (motor_calibration_B.LogicalOperator4 != motor_calibration_P.Constant_Value)
  {
    rtmSetStopRequested(motor_calibration_M, 1);
  }

  /* End of Stop: '<S3>/Stop Simulation' */

  /* Logic: '<S2>/Logical Operator5' incorporates:
   *  Constant: '<S2>/Constant'
   *  Logic: '<S2>/Logical Operator3'
   */
  motor_calibration_B.LogicalOperator5 =
    ((motor_calibration_P.LIMIT_SWITCHES_ENABLE != 0.0) &&
     (!rtb_HILReadDigital_o2));

  /* Stop: '<S4>/Stop Simulation' incorporates:
   *  Constant: '<S8>/Constant'
   *  RelationalOperator: '<S8>/Compare'
   */
  if (motor_calibration_B.LogicalOperator5 !=
      motor_calibration_P.Constant_Value_i) {
    rtmSetStopRequested(motor_calibration_M, 1);
  }

  /* End of Stop: '<S4>/Stop Simulation' */

  /* Logic: '<S2>/Logical Operator6' incorporates:
   *  Constant: '<S2>/Constant'
   *  Logic: '<S2>/Logical Operator1'
   */
  motor_calibration_B.LogicalOperator6 =
    ((motor_calibration_P.LIMIT_SWITCHES_ENABLE != 0.0) &&
     (!rtb_HILReadDigital_o3));

  /* Stop: '<S5>/Stop Simulation' incorporates:
   *  Constant: '<S9>/Constant'
   *  RelationalOperator: '<S9>/Compare'
   */
  if (motor_calibration_B.LogicalOperator6 !=
      motor_calibration_P.Constant_Value_e) {
    rtmSetStopRequested(motor_calibration_M, 1);
  }

  /* End of Stop: '<S5>/Stop Simulation' */

  /* Logic: '<S2>/Logical Operator7' incorporates:
   *  Constant: '<S2>/Constant'
   *  Logic: '<S2>/Logical Operator'
   */
  motor_calibration_B.LogicalOperator7 =
    ((motor_calibration_P.LIMIT_SWITCHES_ENABLE != 0.0) &&
     (!rtb_HILReadDigital_o4));

  /* Stop: '<S6>/Stop Simulation' incorporates:
   *  Constant: '<S10>/Constant'
   *  RelationalOperator: '<S10>/Compare'
   */
  if (motor_calibration_B.LogicalOperator7 !=
      motor_calibration_P.Constant_Value_d) {
    rtmSetStopRequested(motor_calibration_M, 1);
  }

  /* End of Stop: '<S6>/Stop Simulation' */
}

/* Model update function */
void motor_calibration_update(void)
{
  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++motor_calibration_M->Timing.clockTick0)) {
    ++motor_calibration_M->Timing.clockTickH0;
  }

  motor_calibration_M->Timing.t[0] = motor_calibration_M->Timing.clockTick0 *
    motor_calibration_M->Timing.stepSize0 +
    motor_calibration_M->Timing.clockTickH0 *
    motor_calibration_M->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [0.002s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++motor_calibration_M->Timing.clockTick1)) {
      ++motor_calibration_M->Timing.clockTickH1;
    }

    motor_calibration_M->Timing.t[1] = motor_calibration_M->Timing.clockTick1 *
      motor_calibration_M->Timing.stepSize1 +
      motor_calibration_M->Timing.clockTickH1 *
      motor_calibration_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Model initialize function */
void motor_calibration_initialize(void)
{
  /* Start for DiscretePulseGenerator: '<Root>/Pulse Generator' */
  motor_calibration_DW.clockTickCounter = 0;

  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: motor_calibration/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8", "0", &motor_calibration_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(motor_calibration_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options
      (motor_calibration_DW.HILInitialize_Card, " ", 2);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(motor_calibration_M, _rt_error_message);
      return;
    }

    if ((motor_calibration_P.HILInitialize_CKPStart && !is_switching) ||
        (motor_calibration_P.HILInitialize_CKPEnter && is_switching)) {
      result = hil_set_clock_mode(motor_calibration_DW.HILInitialize_Card,
        (t_clock *) motor_calibration_P.HILInitialize_CKChannels, 2U,
        (t_clock_mode *) motor_calibration_P.HILInitialize_CKModes);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(motor_calibration_M, _rt_error_message);
        return;
      }
    }

    result = hil_watchdog_clear(motor_calibration_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(motor_calibration_M, _rt_error_message);
      return;
    }

    if ((motor_calibration_P.HILInitialize_AIPStart && !is_switching) ||
        (motor_calibration_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &motor_calibration_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (motor_calibration_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &motor_calibration_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = motor_calibration_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges
        (motor_calibration_DW.HILInitialize_Card,
         motor_calibration_P.HILInitialize_AIChannels, 8U,
         &motor_calibration_DW.HILInitialize_AIMinimums[0],
         &motor_calibration_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(motor_calibration_M, _rt_error_message);
        return;
      }
    }

    if ((motor_calibration_P.HILInitialize_AOPStart && !is_switching) ||
        (motor_calibration_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &motor_calibration_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (motor_calibration_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &motor_calibration_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = motor_calibration_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges
        (motor_calibration_DW.HILInitialize_Card,
         motor_calibration_P.HILInitialize_AOChannels, 8U,
         &motor_calibration_DW.HILInitialize_AOMinimums[0],
         &motor_calibration_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(motor_calibration_M, _rt_error_message);
        return;
      }
    }

    if ((motor_calibration_P.HILInitialize_AOStart && !is_switching) ||
        (motor_calibration_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &motor_calibration_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = motor_calibration_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(motor_calibration_DW.HILInitialize_Card,
        motor_calibration_P.HILInitialize_AOChannels, 8U,
        &motor_calibration_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(motor_calibration_M, _rt_error_message);
        return;
      }
    }

    if (motor_calibration_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &motor_calibration_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = motor_calibration_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (motor_calibration_DW.HILInitialize_Card,
         motor_calibration_P.HILInitialize_AOChannels, 8U,
         &motor_calibration_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(motor_calibration_M, _rt_error_message);
        return;
      }
    }

    result = hil_set_digital_directions(motor_calibration_DW.HILInitialize_Card,
      motor_calibration_P.HILInitialize_DIChannels, 8U,
      motor_calibration_P.HILInitialize_DOChannels, 9U);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(motor_calibration_M, _rt_error_message);
      return;
    }

    if ((motor_calibration_P.HILInitialize_DOStart && !is_switching) ||
        (motor_calibration_P.HILInitialize_DOEnter && is_switching)) {
      {
        int_T i1;
        boolean_T *dw_DOBits = &motor_calibration_DW.HILInitialize_DOBits[0];
        for (i1=0; i1 < 9; i1++) {
          dw_DOBits[i1] = motor_calibration_P.HILInitialize_DOInitial;
        }
      }

      result = hil_write_digital(motor_calibration_DW.HILInitialize_Card,
        motor_calibration_P.HILInitialize_DOChannels, 9U, (t_boolean *)
        &motor_calibration_DW.HILInitialize_DOBits[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(motor_calibration_M, _rt_error_message);
        return;
      }
    }

    if (motor_calibration_P.HILInitialize_DOReset) {
      {
        int_T i1;
        int32_T *dw_DOStates = &motor_calibration_DW.HILInitialize_DOStates[0];
        for (i1=0; i1 < 9; i1++) {
          dw_DOStates[i1] = motor_calibration_P.HILInitialize_DOWatchdog;
        }
      }

      result = hil_watchdog_set_digital_expiration_state
        (motor_calibration_DW.HILInitialize_Card,
         motor_calibration_P.HILInitialize_DOChannels, 9U, (const
          t_digital_state *) &motor_calibration_DW.HILInitialize_DOStates[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(motor_calibration_M, _rt_error_message);
        return;
      }
    }

    if ((motor_calibration_P.HILInitialize_EIPStart && !is_switching) ||
        (motor_calibration_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &motor_calibration_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] =
            motor_calibration_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (motor_calibration_DW.HILInitialize_Card,
         motor_calibration_P.HILInitialize_EIChannels, 8U,
         (t_encoder_quadrature_mode *)
         &motor_calibration_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(motor_calibration_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_FilterFrequency =
          &motor_calibration_DW.HILInitialize_FilterFrequency[0];
        for (i1=0; i1 < 8; i1++) {
          dw_FilterFrequency[i1] = motor_calibration_P.HILInitialize_EIFrequency;
        }
      }

      result = hil_set_encoder_filter_frequency
        (motor_calibration_DW.HILInitialize_Card,
         motor_calibration_P.HILInitialize_EIChannels, 8U,
         &motor_calibration_DW.HILInitialize_FilterFrequency[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(motor_calibration_M, _rt_error_message);
        return;
      }
    }

    if ((motor_calibration_P.HILInitialize_EIStart && !is_switching) ||
        (motor_calibration_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &motor_calibration_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = motor_calibration_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(motor_calibration_DW.HILInitialize_Card,
        motor_calibration_P.HILInitialize_EIChannels, 8U,
        &motor_calibration_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(motor_calibration_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_write_digital_timebase_block): '<Root>/HIL Write Digital Timebase' */

  /* S-Function Block: motor_calibration/HIL Write Digital Timebase (hil_write_digital_timebase_block) */
  {
    t_error result;
    motor_calibration_DW.HILWriteDigitalTimebase_Started = false;
    result = hil_task_create_digital_writer
      (motor_calibration_DW.HILInitialize_Card,
       motor_calibration_P.HILWriteDigitalTimebase_samples,
       &motor_calibration_P.HILWriteDigitalTimebase_channel, 1,
       &motor_calibration_DW.HILWriteDigitalTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(motor_calibration_M, _rt_error_message);
    }
  }
}

/* Model terminate function */
void motor_calibration_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: motor_calibration/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_digital_outputs = 0;
    hil_task_stop_all(motor_calibration_DW.HILInitialize_Card);
    hil_monitor_stop_all(motor_calibration_DW.HILInitialize_Card);
    is_switching = false;
    if ((motor_calibration_P.HILInitialize_AOTerminate && !is_switching) ||
        (motor_calibration_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &motor_calibration_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = motor_calibration_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((motor_calibration_P.HILInitialize_DOTerminate && !is_switching) ||
        (motor_calibration_P.HILInitialize_DOExit && is_switching)) {
      {
        int_T i1;
        boolean_T *dw_DOBits = &motor_calibration_DW.HILInitialize_DOBits[0];
        for (i1=0; i1 < 9; i1++) {
          dw_DOBits[i1] = motor_calibration_P.HILInitialize_DOFinal;
        }
      }

      num_final_digital_outputs = 9U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_digital_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(motor_calibration_DW.HILInitialize_Card
                         , motor_calibration_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , NULL, 0
                         , motor_calibration_P.HILInitialize_DOChannels,
                         num_final_digital_outputs
                         , NULL, 0
                         , &motor_calibration_DW.HILInitialize_AOVoltages[0]
                         , NULL
                         , (t_boolean *)
                         &motor_calibration_DW.HILInitialize_DOBits[0]
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog
            (motor_calibration_DW.HILInitialize_Card,
             motor_calibration_P.HILInitialize_AOChannels,
             num_final_analog_outputs,
             &motor_calibration_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_digital_outputs > 0) {
          local_result = hil_write_digital
            (motor_calibration_DW.HILInitialize_Card,
             motor_calibration_P.HILInitialize_DOChannels,
             num_final_digital_outputs, (t_boolean *)
             &motor_calibration_DW.HILInitialize_DOBits[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(motor_calibration_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(motor_calibration_DW.HILInitialize_Card);
    hil_monitor_delete_all(motor_calibration_DW.HILInitialize_Card);
    hil_close(motor_calibration_DW.HILInitialize_Card);
    motor_calibration_DW.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  motor_calibration_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  motor_calibration_update();
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
  motor_calibration_initialize();
}

void MdlTerminate(void)
{
  motor_calibration_terminate();
}

/* Registration function */
RT_MODEL_motor_calibration_T *motor_calibration(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)motor_calibration_M, 0,
                sizeof(RT_MODEL_motor_calibration_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&motor_calibration_M->solverInfo,
                          &motor_calibration_M->Timing.simTimeStep);
    rtsiSetTPtr(&motor_calibration_M->solverInfo, &rtmGetTPtr
                (motor_calibration_M));
    rtsiSetStepSizePtr(&motor_calibration_M->solverInfo,
                       &motor_calibration_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&motor_calibration_M->solverInfo, (&rtmGetErrorStatus
      (motor_calibration_M)));
    rtsiSetRTModelPtr(&motor_calibration_M->solverInfo, motor_calibration_M);
  }

  rtsiSetSimTimeStep(&motor_calibration_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&motor_calibration_M->solverInfo,"FixedStepDiscrete");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = motor_calibration_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    motor_calibration_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    motor_calibration_M->Timing.sampleTimes =
      (&motor_calibration_M->Timing.sampleTimesArray[0]);
    motor_calibration_M->Timing.offsetTimes =
      (&motor_calibration_M->Timing.offsetTimesArray[0]);

    /* task periods */
    motor_calibration_M->Timing.sampleTimes[0] = (0.0);
    motor_calibration_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    motor_calibration_M->Timing.offsetTimes[0] = (0.0);
    motor_calibration_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(motor_calibration_M, &motor_calibration_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = motor_calibration_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    motor_calibration_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(motor_calibration_M, 3.0);
  motor_calibration_M->Timing.stepSize0 = 0.002;
  motor_calibration_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  motor_calibration_M->Sizes.checksums[0] = (2953468686U);
  motor_calibration_M->Sizes.checksums[1] = (1028518001U);
  motor_calibration_M->Sizes.checksums[2] = (2062848508U);
  motor_calibration_M->Sizes.checksums[3] = (2072127110U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    motor_calibration_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(motor_calibration_M->extModeInfo,
      &motor_calibration_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(motor_calibration_M->extModeInfo,
                        motor_calibration_M->Sizes.checksums);
    rteiSetTPtr(motor_calibration_M->extModeInfo, rtmGetTPtr(motor_calibration_M));
  }

  motor_calibration_M->solverInfoPtr = (&motor_calibration_M->solverInfo);
  motor_calibration_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&motor_calibration_M->solverInfo, 0.002);
  rtsiSetSolverMode(&motor_calibration_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  motor_calibration_M->blockIO = ((void *) &motor_calibration_B);
  (void) memset(((void *) &motor_calibration_B), 0,
                sizeof(B_motor_calibration_T));

  {
    motor_calibration_B.MaxVoltage = 0.0;
    motor_calibration_B.VectorConcatenate[0] = 0.0;
    motor_calibration_B.VectorConcatenate[1] = 0.0;
    motor_calibration_B.HILReadDigital_o1 = 0.0;
    motor_calibration_B.HILReadDigital_o2 = 0.0;
    motor_calibration_B.HILReadDigital_o3 = 0.0;
  }

  /* parameters */
  motor_calibration_M->defaultParam = ((real_T *)&motor_calibration_P);

  /* states (dwork) */
  motor_calibration_M->dwork = ((void *) &motor_calibration_DW);
  (void) memset((void *)&motor_calibration_DW, 0,
                sizeof(DW_motor_calibration_T));
  motor_calibration_DW.HILReadAnalog_Buffer = 0.0;

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      motor_calibration_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      motor_calibration_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      motor_calibration_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      motor_calibration_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      motor_calibration_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      motor_calibration_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    motor_calibration_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 17;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  motor_calibration_M->Sizes.numContStates = (0);/* Number of continuous states */
  motor_calibration_M->Sizes.numY = (0);/* Number of model outputs */
  motor_calibration_M->Sizes.numU = (0);/* Number of model inputs */
  motor_calibration_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  motor_calibration_M->Sizes.numSampTimes = (2);/* Number of sample times */
  motor_calibration_M->Sizes.numBlocks = (44);/* Number of blocks */
  motor_calibration_M->Sizes.numBlockIO = (9);/* Number of block outputs */
  motor_calibration_M->Sizes.numBlockPrms = (142);/* Sum of parameter "widths" */
  return motor_calibration_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
