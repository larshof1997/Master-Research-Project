/*
 * DATA_COLLECTION.c
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
#include "DATA_COLLECTION_dt.h"

/* Block signals (default storage) */
B_DATA_COLLECTION_T DATA_COLLECTION_B;

/* Block states (default storage) */
DW_DATA_COLLECTION_T DATA_COLLECTION_DW;

/* Real-time model */
RT_MODEL_DATA_COLLECTION_T DATA_COLLECTION_M_;
RT_MODEL_DATA_COLLECTION_T *const DATA_COLLECTION_M = &DATA_COLLECTION_M_;

/* Model output function */
void DATA_COLLECTION_output(void)
{
  /* local block i/o variables */
  real_T rtb_Product1[2];
  real_T rtb_PulseGenerator;
  boolean_T rtb_HILReadDigital_o1;
  boolean_T rtb_HILReadDigital_o2;
  boolean_T rtb_HILReadDigital_o3;
  boolean_T rtb_HILReadDigital_o4;
  real_T rtb_ManualSwitch1;
  real_T rtb_ManualSwitch2;
  real_T rtb_UnaryMinus2;
  real_T rtb_Add;
  real_T rtb_Product_idx_0;
  real_T u2;
  real_T rtb_Product1_tmp;

  /* S-Function (hil_read_encoder_block): '<S7>/HIL Read Encoder' */

  /* S-Function Block: DATA_COLLECTION/Torque Control Elbow/HIL Read Encoder (hil_read_encoder_block) */
  {
    t_error result = hil_read_encoder(DATA_COLLECTION_DW.HILInitialize_Card,
      DATA_COLLECTION_P.HILReadEncoder_channels, 2,
      &DATA_COLLECTION_DW.HILReadEncoder_Buffer[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(DATA_COLLECTION_M, _rt_error_message);
    } else {
      rtb_ManualSwitch1 = DATA_COLLECTION_DW.HILReadEncoder_Buffer[0];
      rtb_ManualSwitch2 = DATA_COLLECTION_DW.HILReadEncoder_Buffer[1];
    }
  }

  /* UnaryMinus: '<S7>/Unary Minus' incorporates:
   *  Gain: '<S7>/Motor #1 Encoder Calib1'
   */
  rtb_ManualSwitch1 = -(DATA_COLLECTION_P.KE_D1 * rtb_ManualSwitch1);

  /* SampleTimeMath: '<S20>/TSamp'
   *
   * About '<S20>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  DATA_COLLECTION_B.TSamp = rtb_ManualSwitch1 * DATA_COLLECTION_P.TSamp_WtEt;

  /* UnaryMinus: '<S7>/Unary Minus1' incorporates:
   *  Gain: '<S7>/Motor #2 Encoder Calib1'
   */
  rtb_ManualSwitch2 = -(DATA_COLLECTION_P.KE_D2 * rtb_ManualSwitch2);

  /* SampleTimeMath: '<S17>/TSamp'
   *
   * About '<S17>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  DATA_COLLECTION_B.TSamp_d = rtb_ManualSwitch2 * DATA_COLLECTION_P.TSamp_WtEt_p;

  /* S-Function (hil_read_encoder_block): '<Root>/HIL Read Encoder' */

  /* S-Function Block: DATA_COLLECTION/HIL Read Encoder (hil_read_encoder_block) */
  {
    t_error result = hil_read_encoder(DATA_COLLECTION_DW.HILInitialize_Card,
      DATA_COLLECTION_P.HILReadEncoder_channels_d, 2,
      &DATA_COLLECTION_DW.HILReadEncoder_Buffer_a[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(DATA_COLLECTION_M, _rt_error_message);
    } else {
      rtb_UnaryMinus2 = DATA_COLLECTION_DW.HILReadEncoder_Buffer_a[0];
      rtb_PulseGenerator = DATA_COLLECTION_DW.HILReadEncoder_Buffer_a[1];
    }
  }

  /* UnaryMinus: '<Root>/Unary Minus' incorporates:
   *  Gain: '<Root>/Motor #1 Encoder Calib1'
   */
  DATA_COLLECTION_B.VectorConcatenate1[0] = -(DATA_COLLECTION_P.KE_D1 *
    rtb_UnaryMinus2);

  /* UnaryMinus: '<Root>/Unary Minus1' incorporates:
   *  Gain: '<Root>/Motor #2 Encoder Calib1'
   */
  DATA_COLLECTION_B.VectorConcatenate1[1] = -(DATA_COLLECTION_P.KE_D2 *
    rtb_PulseGenerator);

  /* Sum: '<Root>/Sum2' incorporates:
   *  UnitDelay: '<Root>/Unit Delay'
   */
  DATA_COLLECTION_B.Sum2[0] = DATA_COLLECTION_DW.UnitDelay_DSTATE[0] -
    DATA_COLLECTION_B.VectorConcatenate1[0];

  /* SampleTimeMath: '<S1>/TSamp'
   *
   * About '<S1>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  DATA_COLLECTION_B.TSamp_i[0] = DATA_COLLECTION_B.VectorConcatenate1[0] *
    DATA_COLLECTION_P.TSamp_WtEt_e;

  /* Sum: '<Root>/Sum2' incorporates:
   *  UnitDelay: '<Root>/Unit Delay'
   */
  DATA_COLLECTION_B.Sum2[1] = DATA_COLLECTION_DW.UnitDelay_DSTATE[1] -
    DATA_COLLECTION_B.VectorConcatenate1[1];

  /* SampleTimeMath: '<S1>/TSamp'
   *
   * About '<S1>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  DATA_COLLECTION_B.TSamp_i[1] = DATA_COLLECTION_B.VectorConcatenate1[1] *
    DATA_COLLECTION_P.TSamp_WtEt_e;

  /* FromWorkspace: '<Root>/From Workspace3' */
  {
    real_T *pDataValues = (real_T *)
      DATA_COLLECTION_DW.FromWorkspace3_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      DATA_COLLECTION_DW.FromWorkspace3_PWORK.TimePtr;
    int_T currTimeIndex = DATA_COLLECTION_DW.FromWorkspace3_IWORK.PrevIndex;
    real_T t = DATA_COLLECTION_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[2999]) {
      currTimeIndex = 2998;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    DATA_COLLECTION_DW.FromWorkspace3_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&DATA_COLLECTION_B.FromWorkspace3[0])[elIdx] =
                pDataValues[currTimeIndex];
              pDataValues += 3000;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&DATA_COLLECTION_B.FromWorkspace3[0])[elIdx] =
                pDataValues[currTimeIndex + 1];
              pDataValues += 3000;
            }
          }
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;

        {
          int_T elIdx;
          for (elIdx = 0; elIdx < 2; ++elIdx) {
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            (&DATA_COLLECTION_B.FromWorkspace3[0])[elIdx] = (real_T)
              rtInterpolate(d1, d2, f1, f2);
            pDataValues += 3000;
          }
        }
      }
    }
  }

  /* MATLAB Function: '<Root>/MATLAB Function' */
  /* MATLAB Function 'MATLAB Function': '<S4>:1' */
  /* '<S4>:1:2' */
  rtb_UnaryMinus2 = cos(DATA_COLLECTION_B.FromWorkspace3[1]);

  /* FromWorkspace: '<Root>/From Workspace2' */
  /* '<S4>:1:3' */
  {
    real_T *pDataValues = (real_T *)
      DATA_COLLECTION_DW.FromWorkspace2_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      DATA_COLLECTION_DW.FromWorkspace2_PWORK.TimePtr;
    int_T currTimeIndex = DATA_COLLECTION_DW.FromWorkspace2_IWORK.PrevIndex;
    real_T t = DATA_COLLECTION_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[2999]) {
      currTimeIndex = 2998;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    DATA_COLLECTION_DW.FromWorkspace2_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&rtb_Product1[0])[elIdx] = pDataValues[currTimeIndex];
              pDataValues += 3000;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&rtb_Product1[0])[elIdx] = pDataValues[currTimeIndex + 1];
              pDataValues += 3000;
            }
          }
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;

        {
          int_T elIdx;
          for (elIdx = 0; elIdx < 2; ++elIdx) {
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            (&rtb_Product1[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1, f2);
            pDataValues += 3000;
          }
        }
      }
    }
  }

  /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<Root>/Constant2'
   */
  rtb_Add = DATA_COLLECTION_P.b_hat * rtb_UnaryMinus2 + DATA_COLLECTION_P.a2_hat;

  /* Product: '<Root>/Product' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<Root>/Constant1'
   *  Constant: '<Root>/Constant2'
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  rtb_Product_idx_0 = (2.0 * DATA_COLLECTION_P.b_hat * rtb_UnaryMinus2 +
                       (DATA_COLLECTION_P.a1_hat + DATA_COLLECTION_P.a2_hat)) *
    rtb_Product1[0] + rtb_Add * rtb_Product1[1];
  rtb_Add = rtb_Add * rtb_Product1[0] + DATA_COLLECTION_P.a2_hat * rtb_Product1
    [1];

  /* FromWorkspace: '<Root>/From Workspace1' */
  {
    real_T *pDataValues = (real_T *)
      DATA_COLLECTION_DW.FromWorkspace1_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      DATA_COLLECTION_DW.FromWorkspace1_PWORK.TimePtr;
    int_T currTimeIndex = DATA_COLLECTION_DW.FromWorkspace1_IWORK.PrevIndex;
    real_T t = DATA_COLLECTION_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[2999]) {
      currTimeIndex = 2998;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    DATA_COLLECTION_DW.FromWorkspace1_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&DATA_COLLECTION_B.FromWorkspace1[0])[elIdx] =
                pDataValues[currTimeIndex];
              pDataValues += 3000;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&DATA_COLLECTION_B.FromWorkspace1[0])[elIdx] =
                pDataValues[currTimeIndex + 1];
              pDataValues += 3000;
            }
          }
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;

        {
          int_T elIdx;
          for (elIdx = 0; elIdx < 2; ++elIdx) {
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            (&DATA_COLLECTION_B.FromWorkspace1[0])[elIdx] = (real_T)
              rtInterpolate(d1, d2, f1, f2);
            pDataValues += 3000;
          }
        }
      }
    }
  }

  /* MATLAB Function: '<Root>/MATLAB Function1' */
  /* MATLAB Function 'MATLAB Function1': '<S5>:1' */
  /* '<S5>:1:2' */
  rtb_UnaryMinus2 = sin(DATA_COLLECTION_B.FromWorkspace3[1]);

  /* Product: '<Root>/Product1' */
  /* '<S5>:1:3' */
  /* MATLAB Function 'MATLAB Function2': '<S6>:1' */
  /* '<S6>:1:3' */
  /* '<S6>:1:4' */
  /* '<S6>:1:5' */
  rtb_Product1[0] = 0.0;

  /* MATLAB Function: '<Root>/MATLAB Function1' incorporates:
   *  Constant: '<Root>/Constant3'
   */
  rtb_Product1_tmp = -DATA_COLLECTION_P.b_hat * rtb_UnaryMinus2;

  /* Product: '<Root>/Product1' incorporates:
   *  Constant: '<Root>/Constant3'
   *  MATLAB Function: '<Root>/MATLAB Function1'
   */
  rtb_Product1[0] += rtb_Product1_tmp * DATA_COLLECTION_B.FromWorkspace1[1] *
    DATA_COLLECTION_B.FromWorkspace1[0];
  rtb_Product1[0] += rtb_Product1_tmp * (DATA_COLLECTION_B.FromWorkspace1[0] +
    DATA_COLLECTION_B.FromWorkspace1[1]) * DATA_COLLECTION_B.FromWorkspace1[1];
  rtb_Product1[1] = 0.0;
  rtb_Product1[1] += DATA_COLLECTION_P.b_hat * rtb_UnaryMinus2 *
    DATA_COLLECTION_B.FromWorkspace1[0] * DATA_COLLECTION_B.FromWorkspace1[0];
  rtb_Product1[1] += 0.0 * DATA_COLLECTION_B.FromWorkspace1[1];

  /* Gain: '<S7>/Torque to current ' incorporates:
   *  Constant: '<Root>/Constant4'
   *  Constant: '<Root>/Constant6'
   *  Constant: '<Root>/Constant8'
   *  DiscreteIntegrator: '<Root>/Discrete-Time Integrator'
   *  Gain: '<Root>/Gain'
   *  Gain: '<Root>/Gain1'
   *  Gain: '<Root>/Gain2'
   *  MATLAB Function: '<Root>/MATLAB Function2'
   *  Sum: '<Root>/Add1'
   *  Sum: '<Root>/Sum1'
   *  Sum: '<S1>/Diff'
   *  UnitDelay: '<Root>/Unit Delay1'
   *  UnitDelay: '<S1>/UD'
   */
  DATA_COLLECTION_B.Torquetocurrent = ((((((DATA_COLLECTION_P.ki_traj[1] *
    DATA_COLLECTION_DW.DiscreteTimeIntegrator_DSTATE[0] +
    DATA_COLLECTION_P.ki_traj[3] *
    DATA_COLLECTION_DW.DiscreteTimeIntegrator_DSTATE[1]) +
    DATA_COLLECTION_P.Gain_Gain[1] * DATA_COLLECTION_B.Sum2[1]) +
    (DATA_COLLECTION_DW.UnitDelay1_DSTATE[1] - (DATA_COLLECTION_B.TSamp_i[1] -
    DATA_COLLECTION_DW.UD_DSTATE_e[1])) * DATA_COLLECTION_P.Gain2_Gain[1]) +
    rtb_Add) + rtb_Product1[1]) + (tanh(DATA_COLLECTION_B.FromWorkspace1[1] /
    DATA_COLLECTION_P.v_eps_hat) * DATA_COLLECTION_P.fc2_hat +
    DATA_COLLECTION_P.b2_hat * DATA_COLLECTION_B.FromWorkspace1[1])) * (1.0 /
    DATA_COLLECTION_P.Kt2);

  /* ManualSwitch: '<S7>/Manual Switch2' incorporates:
   *  Gain: '<S7>/Motor #1 Encoder Calib6'
   *  Gain: '<S7>/Motor #1 Encoder Calib7'
   */
  if (DATA_COLLECTION_P.ManualSwitch2_CurrentSetting == 1) {
    rtb_PulseGenerator = DATA_COLLECTION_P.R1 *
      DATA_COLLECTION_B.Torquetocurrent;
  } else {
    rtb_PulseGenerator = DATA_COLLECTION_P.R2 *
      DATA_COLLECTION_B.Torquetocurrent;
  }

  /* End of ManualSwitch: '<S7>/Manual Switch2' */

  /* SampleTimeMath: '<S19>/TSamp'
   *
   * About '<S19>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  DATA_COLLECTION_B.TSamp_f = DATA_COLLECTION_B.Torquetocurrent *
    DATA_COLLECTION_P.TSamp_WtEt_ei;

  /* ManualSwitch: '<S7>/Manual Switch1' incorporates:
   *  Gain: '<S7>/Motor #1 Encoder Calib2'
   *  Gain: '<S7>/Motor #1 Encoder Calib5'
   *  Sum: '<S19>/Diff'
   *  UnitDelay: '<S19>/UD'
   */
  if (DATA_COLLECTION_P.ManualSwitch1_CurrentSetting == 1) {
    rtb_UnaryMinus2 = (DATA_COLLECTION_B.TSamp_f -
                       DATA_COLLECTION_DW.UD_DSTATE_g1) * DATA_COLLECTION_P.L1;
  } else {
    rtb_UnaryMinus2 = (DATA_COLLECTION_B.TSamp_f -
                       DATA_COLLECTION_DW.UD_DSTATE_g1) * DATA_COLLECTION_P.L2;
  }

  /* End of ManualSwitch: '<S7>/Manual Switch1' */

  /* S-Function (hil_read_analog_block): '<S7>/HIL Read Analog' */

  /* S-Function Block: DATA_COLLECTION/Torque Control Elbow/HIL Read Analog (hil_read_analog_block) */
  {
    t_error result = hil_read_analog(DATA_COLLECTION_DW.HILInitialize_Card,
      &DATA_COLLECTION_P.HILReadAnalog_channels, 1,
      &DATA_COLLECTION_DW.HILReadAnalog_Buffer);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(DATA_COLLECTION_M, _rt_error_message);
    }

    DATA_COLLECTION_B.Current = DATA_COLLECTION_DW.HILReadAnalog_Buffer;
  }

  /* Sum: '<S7>/Sum1' */
  DATA_COLLECTION_B.Sum1 = DATA_COLLECTION_B.Torquetocurrent -
    DATA_COLLECTION_B.Current;

  /* SampleTimeMath: '<S18>/TSamp'
   *
   * About '<S18>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  DATA_COLLECTION_B.TSamp_p = DATA_COLLECTION_B.Sum1 *
    DATA_COLLECTION_P.TSamp_WtEt_a;

  /* ManualSwitch: '<S7>/Manual Switch3' incorporates:
   *  Gain: '<S7>/Motor #1 Encoder Calib3'
   *  Gain: '<S7>/Motor #1 Encoder Calib8'
   *  Sum: '<S17>/Diff'
   *  Sum: '<S20>/Diff'
   *  UnitDelay: '<S17>/UD'
   *  UnitDelay: '<S20>/UD'
   */
  if (DATA_COLLECTION_P.ManualSwitch3_CurrentSetting == 1) {
    rtb_Add = (DATA_COLLECTION_B.TSamp - DATA_COLLECTION_DW.UD_DSTATE) *
      DATA_COLLECTION_P.ke1;
  } else {
    rtb_Add = (DATA_COLLECTION_B.TSamp_d - DATA_COLLECTION_DW.UD_DSTATE_g) *
      DATA_COLLECTION_P.ke2;
  }

  /* End of ManualSwitch: '<S7>/Manual Switch3' */

  /* Sum: '<S7>/Add' incorporates:
   *  DiscreteIntegrator: '<S7>/Discrete-Time Integrator'
   *  Gain: '<S7>/Gain'
   *  Gain: '<S7>/Gain1'
   *  Gain: '<S7>/Gain2'
   *  Sum: '<S18>/Diff'
   *  Sum: '<S7>/Add1'
   *  UnitDelay: '<S18>/UD'
   */
  rtb_Add = ((DATA_COLLECTION_P.kp2 * DATA_COLLECTION_B.Sum1 +
              DATA_COLLECTION_P.ki1 *
              DATA_COLLECTION_DW.DiscreteTimeIntegrator_DSTATE_p) +
             (DATA_COLLECTION_B.TSamp_p - DATA_COLLECTION_DW.UD_DSTATE_j) *
             DATA_COLLECTION_P.Gain2_Gain_c) + ((rtb_Add + rtb_PulseGenerator) +
    rtb_UnaryMinus2);

  /* Saturate: '<S7>/Saturation' */
  rtb_Product1_tmp = -DATA_COLLECTION_P.i_sat2 * DATA_COLLECTION_P.R2;
  u2 = DATA_COLLECTION_P.i_sat2 * DATA_COLLECTION_P.R2;
  if (rtb_Add > u2) {
    DATA_COLLECTION_B.Saturation = u2;
  } else if (rtb_Add < rtb_Product1_tmp) {
    DATA_COLLECTION_B.Saturation = rtb_Product1_tmp;
  } else {
    DATA_COLLECTION_B.Saturation = rtb_Add;
  }

  /* End of Saturate: '<S7>/Saturation' */

  /* S-Function (hil_write_analog_block): '<S7>/HIL Write Analog' */

  /* S-Function Block: DATA_COLLECTION/Torque Control Elbow/HIL Write Analog (hil_write_analog_block) */
  {
    t_error result;
    result = hil_write_analog(DATA_COLLECTION_DW.HILInitialize_Card,
      &DATA_COLLECTION_P.HILWriteAnalog_channels, 1,
      &DATA_COLLECTION_B.Saturation);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(DATA_COLLECTION_M, _rt_error_message);
    }
  }

  /* SignalConversion: '<S7>/ConcatBufferAtVector ConcatenateIn1' */
  DATA_COLLECTION_B.VectorConcatenate[0] = DATA_COLLECTION_B.Torquetocurrent;

  /* SignalConversion: '<S7>/ConcatBufferAtVector ConcatenateIn2' */
  DATA_COLLECTION_B.VectorConcatenate[1] = DATA_COLLECTION_B.Current;

  /* SignalConversion: '<S7>/ConcatBufferAtVector ConcatenateIn3' */
  DATA_COLLECTION_B.VectorConcatenate[2] = DATA_COLLECTION_B.Saturation;

  /* ManualSwitch: '<S7>/Manual Switch4' */
  if (DATA_COLLECTION_P.ManualSwitch4_CurrentSetting == 1) {
    DATA_COLLECTION_B.VectorConcatenate[3] = rtb_ManualSwitch1;
  } else {
    DATA_COLLECTION_B.VectorConcatenate[3] = rtb_ManualSwitch2;
  }

  /* End of ManualSwitch: '<S7>/Manual Switch4' */
  /* S-Function (hil_read_encoder_block): '<S8>/HIL Read Encoder' */

  /* S-Function Block: DATA_COLLECTION/Torque Control Shoulder/HIL Read Encoder (hil_read_encoder_block) */
  {
    t_error result = hil_read_encoder(DATA_COLLECTION_DW.HILInitialize_Card,
      DATA_COLLECTION_P.HILReadEncoder_channels_g, 2,
      &DATA_COLLECTION_DW.HILReadEncoder_Buffer_d[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(DATA_COLLECTION_M, _rt_error_message);
    } else {
      rtb_PulseGenerator = DATA_COLLECTION_DW.HILReadEncoder_Buffer_d[0];
      rtb_UnaryMinus2 = DATA_COLLECTION_DW.HILReadEncoder_Buffer_d[1];
    }
  }

  /* UnaryMinus: '<S8>/Unary Minus1' incorporates:
   *  Gain: '<S8>/Motor #1 Encoder Calib1'
   */
  rtb_PulseGenerator = -(DATA_COLLECTION_P.KE_D1 * rtb_PulseGenerator);

  /* SampleTimeMath: '<S24>/TSamp'
   *
   * About '<S24>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  DATA_COLLECTION_B.TSamp_g = rtb_PulseGenerator *
    DATA_COLLECTION_P.TSamp_WtEt_h;

  /* UnaryMinus: '<S8>/Unary Minus2' incorporates:
   *  Gain: '<S8>/Motor #2 Encoder Calib1'
   */
  rtb_UnaryMinus2 = -(DATA_COLLECTION_P.KE_D2 * rtb_UnaryMinus2);

  /* SampleTimeMath: '<S21>/TSamp'
   *
   * About '<S21>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  DATA_COLLECTION_B.TSamp_b = rtb_UnaryMinus2 * DATA_COLLECTION_P.TSamp_WtEt_l;

  /* Gain: '<S8>/Torque to current ' incorporates:
   *  Constant: '<Root>/Constant5'
   *  Constant: '<Root>/Constant6'
   *  Constant: '<Root>/Constant7'
   *  DiscreteIntegrator: '<Root>/Discrete-Time Integrator'
   *  Gain: '<Root>/Gain'
   *  Gain: '<Root>/Gain1'
   *  Gain: '<Root>/Gain2'
   *  MATLAB Function: '<Root>/MATLAB Function2'
   *  Sum: '<Root>/Add1'
   *  Sum: '<Root>/Sum1'
   *  Sum: '<S1>/Diff'
   *  UnitDelay: '<Root>/Unit Delay1'
   *  UnitDelay: '<S1>/UD'
   */
  DATA_COLLECTION_B.Torquetocurrent_k = ((((((DATA_COLLECTION_P.ki_traj[0] *
    DATA_COLLECTION_DW.DiscreteTimeIntegrator_DSTATE[0] +
    DATA_COLLECTION_P.ki_traj[2] *
    DATA_COLLECTION_DW.DiscreteTimeIntegrator_DSTATE[1]) +
    DATA_COLLECTION_P.Gain_Gain[0] * DATA_COLLECTION_B.Sum2[0]) +
    (DATA_COLLECTION_DW.UnitDelay1_DSTATE[0] - (DATA_COLLECTION_B.TSamp_i[0] -
    DATA_COLLECTION_DW.UD_DSTATE_e[0])) * DATA_COLLECTION_P.Gain2_Gain[0]) +
    rtb_Product_idx_0) + rtb_Product1[0]) + (tanh
    (DATA_COLLECTION_B.FromWorkspace1[0] / DATA_COLLECTION_P.v_eps_hat) *
    DATA_COLLECTION_P.fc1_hat + DATA_COLLECTION_P.b1_hat *
    DATA_COLLECTION_B.FromWorkspace1[0])) * (1.0 / DATA_COLLECTION_P.Kt1);

  /* ManualSwitch: '<S8>/Manual Switch2' incorporates:
   *  Gain: '<S8>/Motor #1 Encoder Calib6'
   *  Gain: '<S8>/Motor #1 Encoder Calib7'
   */
  if (DATA_COLLECTION_P.ManualSwitch2_CurrentSetting_j == 1) {
    rtb_ManualSwitch2 = DATA_COLLECTION_P.R1 *
      DATA_COLLECTION_B.Torquetocurrent_k;
  } else {
    rtb_ManualSwitch2 = DATA_COLLECTION_P.R2 *
      DATA_COLLECTION_B.Torquetocurrent_k;
  }

  /* End of ManualSwitch: '<S8>/Manual Switch2' */

  /* SampleTimeMath: '<S23>/TSamp'
   *
   * About '<S23>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  DATA_COLLECTION_B.TSamp_j = DATA_COLLECTION_B.Torquetocurrent_k *
    DATA_COLLECTION_P.TSamp_WtEt_g;

  /* ManualSwitch: '<S8>/Manual Switch1' incorporates:
   *  Gain: '<S8>/Motor #1 Encoder Calib2'
   *  Gain: '<S8>/Motor #1 Encoder Calib5'
   *  Sum: '<S23>/Diff'
   *  UnitDelay: '<S23>/UD'
   */
  if (DATA_COLLECTION_P.ManualSwitch1_CurrentSetting_k == 1) {
    rtb_ManualSwitch1 = (DATA_COLLECTION_B.TSamp_j -
                         DATA_COLLECTION_DW.UD_DSTATE_er) * DATA_COLLECTION_P.L1;
  } else {
    rtb_ManualSwitch1 = (DATA_COLLECTION_B.TSamp_j -
                         DATA_COLLECTION_DW.UD_DSTATE_er) * DATA_COLLECTION_P.L2;
  }

  /* End of ManualSwitch: '<S8>/Manual Switch1' */

  /* S-Function (hil_read_analog_block): '<S8>/HIL Read Analog' */

  /* S-Function Block: DATA_COLLECTION/Torque Control Shoulder/HIL Read Analog (hil_read_analog_block) */
  {
    t_error result = hil_read_analog(DATA_COLLECTION_DW.HILInitialize_Card,
      &DATA_COLLECTION_P.HILReadAnalog_channels_e, 1,
      &DATA_COLLECTION_DW.HILReadAnalog_Buffer_n);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(DATA_COLLECTION_M, _rt_error_message);
    }

    DATA_COLLECTION_B.Current_b = DATA_COLLECTION_DW.HILReadAnalog_Buffer_n;
  }

  /* Sum: '<S8>/Sum1' */
  DATA_COLLECTION_B.Sum1_d = DATA_COLLECTION_B.Torquetocurrent_k -
    DATA_COLLECTION_B.Current_b;

  /* SampleTimeMath: '<S22>/TSamp'
   *
   * About '<S22>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  DATA_COLLECTION_B.TSamp_bl = DATA_COLLECTION_B.Sum1_d *
    DATA_COLLECTION_P.TSamp_WtEt_pz;

  /* ManualSwitch: '<S8>/Manual Switch3' incorporates:
   *  Gain: '<S8>/Motor #1 Encoder Calib3'
   *  Gain: '<S8>/Motor #1 Encoder Calib8'
   *  Sum: '<S21>/Diff'
   *  Sum: '<S24>/Diff'
   *  UnitDelay: '<S21>/UD'
   *  UnitDelay: '<S24>/UD'
   */
  if (DATA_COLLECTION_P.ManualSwitch3_CurrentSetting_n == 1) {
    rtb_Add = (DATA_COLLECTION_B.TSamp_g - DATA_COLLECTION_DW.UD_DSTATE_h) *
      DATA_COLLECTION_P.ke1;
  } else {
    rtb_Add = (DATA_COLLECTION_B.TSamp_b - DATA_COLLECTION_DW.UD_DSTATE_i) *
      DATA_COLLECTION_P.ke2;
  }

  /* End of ManualSwitch: '<S8>/Manual Switch3' */

  /* Sum: '<S8>/Add' incorporates:
   *  DiscreteIntegrator: '<S8>/Discrete-Time Integrator'
   *  Gain: '<S8>/Gain'
   *  Gain: '<S8>/Gain1'
   *  Gain: '<S8>/Gain2'
   *  Sum: '<S22>/Diff'
   *  Sum: '<S8>/Add1'
   *  UnitDelay: '<S22>/UD'
   */
  rtb_Add = ((DATA_COLLECTION_P.kp1 * DATA_COLLECTION_B.Sum1_d +
              DATA_COLLECTION_P.ki1 *
              DATA_COLLECTION_DW.DiscreteTimeIntegrator_DSTATE_a) +
             (DATA_COLLECTION_B.TSamp_bl - DATA_COLLECTION_DW.UD_DSTATE_d) *
             DATA_COLLECTION_P.Gain2_Gain_l) + ((rtb_Add + rtb_ManualSwitch2) +
    rtb_ManualSwitch1);

  /* Saturate: '<S8>/Saturation' */
  rtb_Product1_tmp = -DATA_COLLECTION_P.i_sat1 * DATA_COLLECTION_P.R1;
  u2 = DATA_COLLECTION_P.i_sat1 * DATA_COLLECTION_P.R1;
  if (rtb_Add > u2) {
    DATA_COLLECTION_B.Saturation_m = u2;
  } else if (rtb_Add < rtb_Product1_tmp) {
    DATA_COLLECTION_B.Saturation_m = rtb_Product1_tmp;
  } else {
    DATA_COLLECTION_B.Saturation_m = rtb_Add;
  }

  /* End of Saturate: '<S8>/Saturation' */

  /* S-Function (hil_write_analog_block): '<S8>/HIL Write Analog' */

  /* S-Function Block: DATA_COLLECTION/Torque Control Shoulder/HIL Write Analog (hil_write_analog_block) */
  {
    t_error result;
    result = hil_write_analog(DATA_COLLECTION_DW.HILInitialize_Card,
      &DATA_COLLECTION_P.HILWriteAnalog_channels_h, 1,
      &DATA_COLLECTION_B.Saturation_m);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(DATA_COLLECTION_M, _rt_error_message);
    }
  }

  /* SignalConversion: '<S8>/ConcatBufferAtVector ConcatenateIn1' */
  DATA_COLLECTION_B.VectorConcatenate_d[0] = DATA_COLLECTION_B.Torquetocurrent_k;

  /* SignalConversion: '<S8>/ConcatBufferAtVector ConcatenateIn2' */
  DATA_COLLECTION_B.VectorConcatenate_d[1] = DATA_COLLECTION_B.Current_b;

  /* SignalConversion: '<S8>/ConcatBufferAtVector ConcatenateIn3' */
  DATA_COLLECTION_B.VectorConcatenate_d[2] = DATA_COLLECTION_B.Saturation_m;

  /* ManualSwitch: '<S8>/Manual Switch4' */
  if (DATA_COLLECTION_P.ManualSwitch4_CurrentSetting_i == 1) {
    DATA_COLLECTION_B.VectorConcatenate_d[3] = rtb_PulseGenerator;
  } else {
    DATA_COLLECTION_B.VectorConcatenate_d[3] = rtb_UnaryMinus2;
  }

  /* End of ManualSwitch: '<S8>/Manual Switch4' */
  /* UnitDelay: '<Root>/Unit Delay2' */
  DATA_COLLECTION_B.UnitDelay2[0] = DATA_COLLECTION_DW.UnitDelay2_DSTATE[0];
  DATA_COLLECTION_B.UnitDelay2[1] = DATA_COLLECTION_DW.UnitDelay2_DSTATE[1];

  /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
  rtb_PulseGenerator = (DATA_COLLECTION_DW.clockTickCounter <
                        DATA_COLLECTION_P.PulseGenerator_Duty) &&
    (DATA_COLLECTION_DW.clockTickCounter >= 0) ?
    DATA_COLLECTION_P.PulseGenerator_Amp : 0.0;
  if (DATA_COLLECTION_DW.clockTickCounter >=
      DATA_COLLECTION_P.PulseGenerator_Period - 1.0) {
    DATA_COLLECTION_DW.clockTickCounter = 0;
  } else {
    DATA_COLLECTION_DW.clockTickCounter++;
  }

  /* End of DiscretePulseGenerator: '<Root>/Pulse Generator' */
  /* S-Function (hil_write_digital_timebase_block): '<Root>/HIL Write Digital Timebase' */

  /* S-Function Block: DATA_COLLECTION/HIL Write Digital Timebase (hil_write_digital_timebase_block) */
  {
    t_error result;
    DATA_COLLECTION_DW.HILWriteDigitalTimebase_Buffer = (rtb_PulseGenerator != 0);
    result = hil_task_write_digital
      (DATA_COLLECTION_DW.HILWriteDigitalTimebase_Task, 1,
       &DATA_COLLECTION_DW.HILWriteDigitalTimebase_Buffer);
    if (DATA_COLLECTION_DW.HILWriteDigitalTimebase_Started == false && result >=
        0) {
      result = hil_task_start(DATA_COLLECTION_DW.HILWriteDigitalTimebase_Task,
        (t_clock) DATA_COLLECTION_P.HILWriteDigitalTimebase_clock, 100.0, -1);
      DATA_COLLECTION_DW.HILWriteDigitalTimebase_Started = (result == 0);
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(DATA_COLLECTION_M, _rt_error_message);
    }
  }

  /* S-Function (hil_write_digital_block): '<S2>/HIL Write Digital' incorporates:
   *  Constant: '<S2>/Enable: Active Low'
   *  Constant: '<S2>/Master Enable: Active High'
   */

  /* S-Function Block: DATA_COLLECTION/Enable AMPAQ/HIL Write Digital (hil_write_digital_block) */
  {
    t_error result;
    DATA_COLLECTION_DW.HILWriteDigital_Buffer[0] =
      (DATA_COLLECTION_P.EnableActiveLow_Value[0] != 0);
    DATA_COLLECTION_DW.HILWriteDigital_Buffer[1] =
      (DATA_COLLECTION_P.EnableActiveLow_Value[1] != 0);
    DATA_COLLECTION_DW.HILWriteDigital_Buffer[2] =
      (DATA_COLLECTION_P.MasterEnableActiveHigh_Value != 0);
    result = hil_write_digital(DATA_COLLECTION_DW.HILInitialize_Card,
      DATA_COLLECTION_P.HILWriteDigital_channels, 3,
      &DATA_COLLECTION_DW.HILWriteDigital_Buffer[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(DATA_COLLECTION_M, _rt_error_message);
    }
  }

  /* S-Function (hil_read_digital_block): '<S2>/HIL Read Digital' */

  /* S-Function Block: DATA_COLLECTION/Enable AMPAQ/HIL Read Digital (hil_read_digital_block) */
  {
    t_error result = hil_read_digital(DATA_COLLECTION_DW.HILInitialize_Card,
      DATA_COLLECTION_P.HILReadDigital_channels, 3,
      &DATA_COLLECTION_DW.HILReadDigital_Buffer[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(DATA_COLLECTION_M, _rt_error_message);
    } else {
      DATA_COLLECTION_B.HILReadDigital_o1 =
        DATA_COLLECTION_DW.HILReadDigital_Buffer[0];
      DATA_COLLECTION_B.HILReadDigital_o2 =
        DATA_COLLECTION_DW.HILReadDigital_Buffer[1];
      DATA_COLLECTION_B.HILReadDigital_o3 =
        DATA_COLLECTION_DW.HILReadDigital_Buffer[2];
    }
  }

  /* S-Function (hil_read_digital_block): '<S3>/HIL Read Digital' */

  /* S-Function Block: DATA_COLLECTION/Limit Switches/HIL Read Digital (hil_read_digital_block) */
  {
    t_error result = hil_read_digital(DATA_COLLECTION_DW.HILInitialize_Card,
      DATA_COLLECTION_P.HILReadDigital_channels_j, 4,
      &DATA_COLLECTION_DW.HILReadDigital_Buffer_g[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(DATA_COLLECTION_M, _rt_error_message);
    } else {
      rtb_HILReadDigital_o1 = DATA_COLLECTION_DW.HILReadDigital_Buffer_g[0];
      rtb_HILReadDigital_o2 = DATA_COLLECTION_DW.HILReadDigital_Buffer_g[1];
      rtb_HILReadDigital_o3 = DATA_COLLECTION_DW.HILReadDigital_Buffer_g[2];
      rtb_HILReadDigital_o4 = DATA_COLLECTION_DW.HILReadDigital_Buffer_g[3];
    }
  }

  /* Logic: '<S3>/Logical Operator4' incorporates:
   *  Constant: '<S3>/Constant'
   *  Logic: '<S3>/Logical Operator2'
   */
  DATA_COLLECTION_B.LogicalOperator4 = ((DATA_COLLECTION_P.LIMIT_SWITCHES_ENABLE
    != 0.0) && (!rtb_HILReadDigital_o1));

  /* Stop: '<S9>/Stop Simulation' incorporates:
   *  Constant: '<S13>/Constant'
   *  RelationalOperator: '<S13>/Compare'
   */
  if (DATA_COLLECTION_B.LogicalOperator4 != DATA_COLLECTION_P.Constant_Value) {
    rtmSetStopRequested(DATA_COLLECTION_M, 1);
  }

  /* End of Stop: '<S9>/Stop Simulation' */

  /* Logic: '<S3>/Logical Operator5' incorporates:
   *  Constant: '<S3>/Constant'
   *  Logic: '<S3>/Logical Operator3'
   */
  DATA_COLLECTION_B.LogicalOperator5 = ((DATA_COLLECTION_P.LIMIT_SWITCHES_ENABLE
    != 0.0) && (!rtb_HILReadDigital_o2));

  /* Stop: '<S10>/Stop Simulation' incorporates:
   *  Constant: '<S14>/Constant'
   *  RelationalOperator: '<S14>/Compare'
   */
  if (DATA_COLLECTION_B.LogicalOperator5 != DATA_COLLECTION_P.Constant_Value_h)
  {
    rtmSetStopRequested(DATA_COLLECTION_M, 1);
  }

  /* End of Stop: '<S10>/Stop Simulation' */

  /* Logic: '<S3>/Logical Operator6' incorporates:
   *  Constant: '<S3>/Constant'
   *  Logic: '<S3>/Logical Operator1'
   */
  DATA_COLLECTION_B.LogicalOperator6 = ((DATA_COLLECTION_P.LIMIT_SWITCHES_ENABLE
    != 0.0) && (!rtb_HILReadDigital_o3));

  /* Stop: '<S11>/Stop Simulation' incorporates:
   *  Constant: '<S15>/Constant'
   *  RelationalOperator: '<S15>/Compare'
   */
  if (DATA_COLLECTION_B.LogicalOperator6 != DATA_COLLECTION_P.Constant_Value_m)
  {
    rtmSetStopRequested(DATA_COLLECTION_M, 1);
  }

  /* End of Stop: '<S11>/Stop Simulation' */

  /* Logic: '<S3>/Logical Operator7' incorporates:
   *  Constant: '<S3>/Constant'
   *  Logic: '<S3>/Logical Operator'
   */
  DATA_COLLECTION_B.LogicalOperator7 = ((DATA_COLLECTION_P.LIMIT_SWITCHES_ENABLE
    != 0.0) && (!rtb_HILReadDigital_o4));

  /* Stop: '<S12>/Stop Simulation' incorporates:
   *  Constant: '<S16>/Constant'
   *  RelationalOperator: '<S16>/Compare'
   */
  if (DATA_COLLECTION_B.LogicalOperator7 != DATA_COLLECTION_P.Constant_Value_i)
  {
    rtmSetStopRequested(DATA_COLLECTION_M, 1);
  }

  /* End of Stop: '<S12>/Stop Simulation' */
}

/* Model update function */
void DATA_COLLECTION_update(void)
{
  /* Update for UnitDelay: '<S20>/UD' */
  DATA_COLLECTION_DW.UD_DSTATE = DATA_COLLECTION_B.TSamp;

  /* Update for UnitDelay: '<S17>/UD' */
  DATA_COLLECTION_DW.UD_DSTATE_g = DATA_COLLECTION_B.TSamp_d;

  /* Update for UnitDelay: '<S19>/UD' */
  DATA_COLLECTION_DW.UD_DSTATE_g1 = DATA_COLLECTION_B.TSamp_f;

  /* Update for DiscreteIntegrator: '<S7>/Discrete-Time Integrator' */
  DATA_COLLECTION_DW.DiscreteTimeIntegrator_DSTATE_p +=
    DATA_COLLECTION_P.DiscreteTimeIntegrator_gainva_p * DATA_COLLECTION_B.Sum1;

  /* Update for UnitDelay: '<S18>/UD' */
  DATA_COLLECTION_DW.UD_DSTATE_j = DATA_COLLECTION_B.TSamp_p;

  /* Update for UnitDelay: '<S24>/UD' */
  DATA_COLLECTION_DW.UD_DSTATE_h = DATA_COLLECTION_B.TSamp_g;

  /* Update for UnitDelay: '<S21>/UD' */
  DATA_COLLECTION_DW.UD_DSTATE_i = DATA_COLLECTION_B.TSamp_b;

  /* Update for UnitDelay: '<S23>/UD' */
  DATA_COLLECTION_DW.UD_DSTATE_er = DATA_COLLECTION_B.TSamp_j;

  /* Update for DiscreteIntegrator: '<S8>/Discrete-Time Integrator' */
  DATA_COLLECTION_DW.DiscreteTimeIntegrator_DSTATE_a +=
    DATA_COLLECTION_P.DiscreteTimeIntegrator_gainva_k * DATA_COLLECTION_B.Sum1_d;

  /* Update for UnitDelay: '<S22>/UD' */
  DATA_COLLECTION_DW.UD_DSTATE_d = DATA_COLLECTION_B.TSamp_bl;

  /* Update for UnitDelay: '<Root>/Unit Delay' */
  DATA_COLLECTION_DW.UnitDelay_DSTATE[0] = DATA_COLLECTION_B.FromWorkspace3[0];

  /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
  DATA_COLLECTION_DW.DiscreteTimeIntegrator_DSTATE[0] +=
    DATA_COLLECTION_P.DiscreteTimeIntegrator_gainval * DATA_COLLECTION_B.Sum2[0];

  /* Update for UnitDelay: '<S1>/UD' */
  DATA_COLLECTION_DW.UD_DSTATE_e[0] = DATA_COLLECTION_B.TSamp_i[0];

  /* Update for UnitDelay: '<Root>/Unit Delay1' */
  DATA_COLLECTION_DW.UnitDelay1_DSTATE[0] = DATA_COLLECTION_B.FromWorkspace1[0];

  /* Update for UnitDelay: '<Root>/Unit Delay2' */
  DATA_COLLECTION_DW.UnitDelay2_DSTATE[0] = DATA_COLLECTION_B.FromWorkspace3[0];

  /* Update for UnitDelay: '<Root>/Unit Delay' */
  DATA_COLLECTION_DW.UnitDelay_DSTATE[1] = DATA_COLLECTION_B.FromWorkspace3[1];

  /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
  DATA_COLLECTION_DW.DiscreteTimeIntegrator_DSTATE[1] +=
    DATA_COLLECTION_P.DiscreteTimeIntegrator_gainval * DATA_COLLECTION_B.Sum2[1];

  /* Update for UnitDelay: '<S1>/UD' */
  DATA_COLLECTION_DW.UD_DSTATE_e[1] = DATA_COLLECTION_B.TSamp_i[1];

  /* Update for UnitDelay: '<Root>/Unit Delay1' */
  DATA_COLLECTION_DW.UnitDelay1_DSTATE[1] = DATA_COLLECTION_B.FromWorkspace1[1];

  /* Update for UnitDelay: '<Root>/Unit Delay2' */
  DATA_COLLECTION_DW.UnitDelay2_DSTATE[1] = DATA_COLLECTION_B.FromWorkspace3[1];

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++DATA_COLLECTION_M->Timing.clockTick0)) {
    ++DATA_COLLECTION_M->Timing.clockTickH0;
  }

  DATA_COLLECTION_M->Timing.t[0] = DATA_COLLECTION_M->Timing.clockTick0 *
    DATA_COLLECTION_M->Timing.stepSize0 + DATA_COLLECTION_M->Timing.clockTickH0 *
    DATA_COLLECTION_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void DATA_COLLECTION_initialize(void)
{
  /* Start for FromWorkspace: '<Root>/From Workspace3' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06,
      0.07, 0.08, 0.09, 0.1, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18,
      0.19, 0.2, 0.21, 0.22, 0.23, 0.24, 0.25, 0.26, 0.27, 0.28, 0.29, 0.3, 0.31,
      0.32, 0.33, 0.34, 0.35000000000000003, 0.36, 0.37, 0.38, 0.39, 0.4,
      0.41000000000000003, 0.42, 0.43, 0.44, 0.45, 0.46, 0.47000000000000003,
      0.48, 0.49, 0.5, 0.51, 0.52, 0.53, 0.54, 0.55, 0.56, 0.57000000000000006,
      0.58, 0.59, 0.6, 0.61, 0.62, 0.63, 0.64, 0.65, 0.66, 0.67, 0.68,
      0.69000000000000006, 0.70000000000000007, 0.71, 0.72, 0.73, 0.74, 0.75,
      0.76, 0.77, 0.78, 0.79, 0.8, 0.81, 0.82000000000000006,
      0.83000000000000007, 0.84, 0.85, 0.86, 0.87, 0.88, 0.89, 0.9, 0.91, 0.92,
      0.93, 0.94000000000000006, 0.95000000000000007, 0.96, 0.97, 0.98, 0.99,
      1.0, 1.01, 1.02, 1.03, 1.04, 1.05, 1.06, 1.07, 1.08, 1.09, 1.1, 1.11, 1.12,
      1.1300000000000001, 1.1400000000000001, 1.1500000000000001, 1.16, 1.17,
      1.18, 1.19, 1.2, 1.21, 1.22, 1.23, 1.24, 1.25, 1.26, 1.27, 1.28, 1.29, 1.3,
      1.31, 1.32, 1.33, 1.34, 1.35, 1.36, 1.37, 1.3800000000000001,
      1.3900000000000001, 1.4000000000000001, 1.41, 1.42, 1.43, 1.44, 1.45, 1.46,
      1.47, 1.48, 1.49, 1.5, 1.51, 1.52, 1.53, 1.54, 1.55, 1.56, 1.57, 1.58,
      1.59, 1.6, 1.61, 1.62, 1.6300000000000001, 1.6400000000000001,
      1.6500000000000001, 1.6600000000000001, 1.67, 1.68, 1.69, 1.7, 1.71, 1.72,
      1.73, 1.74, 1.75, 1.76, 1.77, 1.78, 1.79, 1.8, 1.81, 1.82, 1.83, 1.84,
      1.85, 1.86, 1.87, 1.8800000000000001, 1.8900000000000001,
      1.9000000000000001, 1.9100000000000001, 1.92, 1.93, 1.94, 1.95, 1.96, 1.97,
      1.98, 1.99, 2.0, 2.0100000000000002, 2.02, 2.0300000000000002, 2.04, 2.05,
      2.06, 2.07, 2.08, 2.09, 2.1, 2.11, 2.12, 2.13, 2.14, 2.15, 2.16, 2.17,
      2.18, 2.19, 2.2, 2.21, 2.22, 2.23, 2.24, 2.25, 2.2600000000000002, 2.27,
      2.2800000000000002, 2.29, 2.3000000000000003, 2.31, 2.32, 2.33, 2.34, 2.35,
      2.36, 2.37, 2.38, 2.39, 2.4, 2.41, 2.42, 2.43, 2.44, 2.45, 2.46, 2.47,
      2.48, 2.49, 2.5, 2.5100000000000002, 2.52, 2.5300000000000002, 2.54,
      2.5500000000000003, 2.56, 2.57, 2.58, 2.59, 2.6, 2.61, 2.62, 2.63, 2.64,
      2.65, 2.66, 2.67, 2.68, 2.69, 2.7, 2.71, 2.72, 2.73, 2.74, 2.75,
      2.7600000000000002, 2.77, 2.7800000000000002, 2.79, 2.8000000000000003,
      2.81, 2.82, 2.83, 2.84, 2.85, 2.86, 2.87, 2.88, 2.89, 2.9, 2.91, 2.92,
      2.93, 2.94, 2.95, 2.96, 2.97, 2.98, 2.99, 3.0, 3.0100000000000002, 3.02,
      3.0300000000000002, 3.04, 3.0500000000000003, 3.06, 3.0700000000000003,
      3.08, 3.09, 3.1, 3.11, 3.12, 3.13, 3.14, 3.15, 3.16, 3.17, 3.18, 3.19, 3.2,
      3.21, 3.22, 3.23, 3.24, 3.25, 3.2600000000000002, 3.27, 3.2800000000000002,
      3.29, 3.3000000000000003, 3.31, 3.3200000000000003, 3.33, 3.34, 3.35, 3.36,
      3.37, 3.38, 3.39, 3.4, 3.41, 3.42, 3.43, 3.44, 3.45, 3.46, 3.47, 3.48,
      3.49, 3.5, 3.5100000000000002, 3.52, 3.5300000000000002, 3.54,
      3.5500000000000003, 3.56, 3.5700000000000003, 3.58, 3.59, 3.6, 3.61, 3.62,
      3.63, 3.64, 3.65, 3.66, 3.67, 3.68, 3.69, 3.7, 3.71, 3.72, 3.73, 3.74,
      3.75, 3.7600000000000002, 3.77, 3.7800000000000002, 3.79,
      3.8000000000000003, 3.81, 3.8200000000000003, 3.83, 3.84, 3.85, 3.86, 3.87,
      3.88, 3.89, 3.9, 3.91, 3.92, 3.93, 3.94, 3.95, 3.96, 3.97, 3.98, 3.99, 4.0,
      4.01, 4.0200000000000005, 4.03, 4.04, 4.05, 4.0600000000000005, 4.07, 4.08,
      4.09, 4.1, 4.11, 4.12, 4.13, 4.14, 4.15, 4.16, 4.17, 4.18, 4.19, 4.2, 4.21,
      4.22, 4.23, 4.24, 4.25, 4.26, 4.2700000000000005, 4.28, 4.29, 4.3,
      4.3100000000000005, 4.32, 4.33, 4.34, 4.3500000000000005, 4.36, 4.37, 4.38,
      4.39, 4.4, 4.41, 4.42, 4.43, 4.44, 4.45, 4.46, 4.47, 4.48, 4.49, 4.5, 4.51,
      4.5200000000000005, 4.53, 4.54, 4.55, 4.5600000000000005, 4.57, 4.58, 4.59,
      4.6000000000000005, 4.61, 4.62, 4.63, 4.64, 4.65, 4.66, 4.67, 4.68, 4.69,
      4.7, 4.71, 4.72, 4.73, 4.74, 4.75, 4.76, 4.7700000000000005, 4.78, 4.79,
      4.8, 4.8100000000000005, 4.82, 4.83, 4.84, 4.8500000000000005, 4.86, 4.87,
      4.88, 4.89, 4.9, 4.91, 4.92, 4.93, 4.94, 4.95, 4.96, 4.97, 4.98, 4.99, 5.0,
      5.01, 5.0200000000000005, 5.03, 5.04, 5.05, 5.0600000000000005, 5.07, 5.08,
      5.09, 5.1000000000000005, 5.11, 5.12, 5.13, 5.14, 5.15, 5.16, 5.17, 5.18,
      5.19, 5.2, 5.21, 5.22, 5.23, 5.24, 5.25, 5.26, 5.2700000000000005, 5.28,
      5.29, 5.3, 5.3100000000000005, 5.32, 5.33, 5.34, 5.3500000000000005, 5.36,
      5.37, 5.38, 5.39, 5.4, 5.41, 5.42, 5.43, 5.44, 5.45, 5.46, 5.47, 5.48,
      5.49, 5.5, 5.51, 5.5200000000000005, 5.53, 5.54, 5.55, 5.5600000000000005,
      5.57, 5.58, 5.59, 5.6000000000000005, 5.61, 5.62, 5.63, 5.64, 5.65, 5.66,
      5.67, 5.68, 5.69, 5.7, 5.71, 5.72, 5.73, 5.74, 5.75, 5.76,
      5.7700000000000005, 5.78, 5.79, 5.8, 5.8100000000000005, 5.82, 5.83, 5.84,
      5.8500000000000005, 5.86, 5.87, 5.88, 5.89, 5.9, 5.91, 5.92, 5.93, 5.94,
      5.95, 5.96, 5.97, 5.98, 5.99, 6.0, 6.01, 6.0200000000000005, 6.03, 6.04,
      6.05, 6.0600000000000005, 6.07, 6.08, 6.09, 6.1000000000000005, 6.11, 6.12,
      6.13, 6.1400000000000006, 6.15, 6.16, 6.17, 6.18, 6.19, 6.2, 6.21, 6.22,
      6.23, 6.24, 6.25, 6.26, 6.2700000000000005, 6.28, 6.29, 6.3,
      6.3100000000000005, 6.32, 6.33, 6.34, 6.3500000000000005, 6.36, 6.37, 6.38,
      6.3900000000000006, 6.4, 6.41, 6.42, 6.43, 6.44, 6.45, 6.46, 6.47, 6.48,
      6.49, 6.5, 6.51, 6.5200000000000005, 6.53, 6.54, 6.55, 6.5600000000000005,
      6.57, 6.58, 6.59, 6.6000000000000005, 6.61, 6.62, 6.63, 6.6400000000000006,
      6.65, 6.66, 6.67, 6.68, 6.69, 6.7, 6.71, 6.72, 6.73, 6.74, 6.75, 6.76,
      6.7700000000000005, 6.78, 6.79, 6.8, 6.8100000000000005, 6.82, 6.83, 6.84,
      6.8500000000000005, 6.86, 6.87, 6.88, 6.8900000000000006, 6.9, 6.91, 6.92,
      6.93, 6.94, 6.95, 6.96, 6.97, 6.98, 6.99, 7.0, 7.01, 7.0200000000000005,
      7.03, 7.04, 7.05, 7.0600000000000005, 7.07, 7.08, 7.09, 7.1000000000000005,
      7.11, 7.12, 7.13, 7.1400000000000006, 7.15, 7.16, 7.17, 7.18, 7.19, 7.2,
      7.21, 7.22, 7.23, 7.24, 7.25, 7.26, 7.2700000000000005, 7.28, 7.29, 7.3,
      7.3100000000000005, 7.32, 7.33, 7.34, 7.3500000000000005, 7.36, 7.37, 7.38,
      7.3900000000000006, 7.4, 7.41, 7.42, 7.43, 7.44, 7.45, 7.46, 7.47, 7.48,
      7.49, 7.5, 7.51, 7.5200000000000005, 7.53, 7.54, 7.55, 7.5600000000000005,
      7.57, 7.58, 7.59, 7.6000000000000005, 7.61, 7.62, 7.63, 7.6400000000000006,
      7.65, 7.66, 7.67, 7.68, 7.69, 7.7, 7.71, 7.72, 7.73, 7.74, 7.75, 7.76,
      7.7700000000000005, 7.78, 7.79, 7.8, 7.8100000000000005, 7.82, 7.83, 7.84,
      7.8500000000000005, 7.86, 7.87, 7.88, 7.8900000000000006, 7.9, 7.91, 7.92,
      7.9300000000000006, 7.94, 7.95, 7.96, 7.97, 7.98, 7.99, 8.0, 8.01, 8.02,
      8.03, 8.0400000000000009, 8.05, 8.06, 8.07, 8.08, 8.09, 8.1, 8.11,
      8.120000000000001, 8.13, 8.14, 8.15, 8.16, 8.17, 8.18, 8.19, 8.2, 8.21,
      8.22, 8.23, 8.24, 8.25, 8.26, 8.27, 8.28, 8.2900000000000009, 8.3, 8.31,
      8.32, 8.33, 8.34, 8.35, 8.36, 8.370000000000001, 8.38, 8.39, 8.4, 8.41,
      8.42, 8.43, 8.44, 8.45, 8.46, 8.47, 8.48, 8.49, 8.5, 8.51, 8.52, 8.53,
      8.5400000000000009, 8.55, 8.56, 8.57, 8.58, 8.59, 8.6, 8.61,
      8.620000000000001, 8.63, 8.64, 8.65, 8.66, 8.67, 8.68, 8.69,
      8.7000000000000011, 8.71, 8.72, 8.73, 8.74, 8.75, 8.76, 8.77, 8.78,
      8.7900000000000009, 8.8, 8.81, 8.82, 8.83, 8.84, 8.85, 8.86,
      8.870000000000001, 8.88, 8.89, 8.9, 8.91, 8.92, 8.93, 8.94,
      8.9500000000000011, 8.96, 8.97, 8.98, 8.99, 9.0, 9.01, 9.02, 9.03,
      9.0400000000000009, 9.05, 9.06, 9.07, 9.08, 9.09, 9.1, 9.11,
      9.120000000000001, 9.13, 9.14, 9.15, 9.16, 9.17, 9.18, 9.19,
      9.2000000000000011, 9.21, 9.22, 9.23, 9.24, 9.25, 9.26, 9.27, 9.28,
      9.2900000000000009, 9.3, 9.31, 9.32, 9.33, 9.34, 9.35, 9.36,
      9.370000000000001, 9.38, 9.39, 9.4, 9.41, 9.42, 9.43, 9.44,
      9.4500000000000011, 9.46, 9.47, 9.48, 9.49, 9.5, 9.51, 9.52, 9.53,
      9.5400000000000009, 9.55, 9.56, 9.57, 9.58, 9.59, 9.6, 9.61,
      9.620000000000001, 9.63, 9.64, 9.65, 9.66, 9.67, 9.68, 9.69,
      9.7000000000000011, 9.71, 9.72, 9.73, 9.74, 9.75, 9.76, 9.77, 9.78,
      9.7900000000000009, 9.8, 9.81, 9.82, 9.83, 9.84, 9.85, 9.86,
      9.870000000000001, 9.88, 9.89, 9.9, 9.91, 9.92, 9.93, 9.94,
      9.9500000000000011, 9.96, 9.97, 9.98, 9.99, 10.0, 10.01, 10.02, 10.03,
      10.040000000000001, 10.05, 10.06, 10.07, 10.08, 10.09, 10.1, 10.11,
      10.120000000000001, 10.13, 10.14, 10.15, 10.16, 10.17, 10.18, 10.19,
      10.200000000000001, 10.21, 10.22, 10.23, 10.24, 10.25, 10.26, 10.27, 10.28,
      10.290000000000001, 10.3, 10.31, 10.32, 10.33, 10.34, 10.35, 10.36,
      10.370000000000001, 10.38, 10.39, 10.4, 10.41, 10.42, 10.43, 10.44,
      10.450000000000001, 10.46, 10.47, 10.48, 10.49, 10.5, 10.51, 10.52, 10.53,
      10.540000000000001, 10.55, 10.56, 10.57, 10.58, 10.59, 10.6, 10.61,
      10.620000000000001, 10.63, 10.64, 10.65, 10.66, 10.67, 10.68, 10.69,
      10.700000000000001, 10.71, 10.72, 10.73, 10.74, 10.75, 10.76, 10.77, 10.78,
      10.790000000000001, 10.8, 10.81, 10.82, 10.83, 10.84, 10.85, 10.86,
      10.870000000000001, 10.88, 10.89, 10.9, 10.91, 10.92, 10.93, 10.94,
      10.950000000000001, 10.96, 10.97, 10.98, 10.99, 11.0, 11.01, 11.02, 11.03,
      11.040000000000001, 11.05, 11.06, 11.07, 11.08, 11.09, 11.1, 11.11,
      11.120000000000001, 11.13, 11.14, 11.15, 11.16, 11.17, 11.18, 11.19,
      11.200000000000001, 11.21, 11.22, 11.23, 11.24, 11.25, 11.26, 11.27, 11.28,
      11.290000000000001, 11.3, 11.31, 11.32, 11.33, 11.34, 11.35, 11.36,
      11.370000000000001, 11.38, 11.39, 11.4, 11.41, 11.42, 11.43, 11.44,
      11.450000000000001, 11.46, 11.47, 11.48, 11.49, 11.5, 11.51, 11.52, 11.53,
      11.540000000000001, 11.55, 11.56, 11.57, 11.58, 11.59, 11.6, 11.61,
      11.620000000000001, 11.63, 11.64, 11.65, 11.66, 11.67, 11.68, 11.69,
      11.700000000000001, 11.71, 11.72, 11.73, 11.74, 11.75, 11.76, 11.77, 11.78,
      11.790000000000001, 11.8, 11.81, 11.82, 11.83, 11.84, 11.85, 11.86,
      11.870000000000001, 11.88, 11.89, 11.9, 11.91, 11.92, 11.93, 11.94,
      11.950000000000001, 11.96, 11.97, 11.98, 11.99, 12.0, 12.01, 12.02,
      12.030000000000001, 12.040000000000001, 12.05, 12.06, 12.07, 12.08, 12.09,
      12.1, 12.11, 12.120000000000001, 12.13, 12.14, 12.15, 12.16, 12.17, 12.18,
      12.19, 12.200000000000001, 12.21, 12.22, 12.23, 12.24, 12.25, 12.26, 12.27,
      12.280000000000001, 12.290000000000001, 12.3, 12.31, 12.32, 12.33, 12.34,
      12.35, 12.36, 12.370000000000001, 12.38, 12.39, 12.4, 12.41, 12.42, 12.43,
      12.44, 12.450000000000001, 12.46, 12.47, 12.48, 12.49, 12.5, 12.51, 12.52,
      12.530000000000001, 12.540000000000001, 12.55, 12.56, 12.57, 12.58, 12.59,
      12.6, 12.61, 12.620000000000001, 12.63, 12.64, 12.65, 12.66, 12.67, 12.68,
      12.69, 12.700000000000001, 12.71, 12.72, 12.73, 12.74, 12.75, 12.76, 12.77,
      12.780000000000001, 12.790000000000001, 12.8, 12.81, 12.82, 12.83, 12.84,
      12.85, 12.86, 12.870000000000001, 12.88, 12.89, 12.9, 12.91, 12.92, 12.93,
      12.94, 12.950000000000001, 12.96, 12.97, 12.98, 12.99, 13.0, 13.01, 13.02,
      13.030000000000001, 13.040000000000001, 13.05, 13.06, 13.07, 13.08, 13.09,
      13.1, 13.11, 13.120000000000001, 13.13, 13.14, 13.15, 13.16, 13.17, 13.18,
      13.19, 13.200000000000001, 13.21, 13.22, 13.23, 13.24, 13.25, 13.26, 13.27,
      13.280000000000001, 13.290000000000001, 13.3, 13.31, 13.32, 13.33, 13.34,
      13.35, 13.36, 13.370000000000001, 13.38, 13.39, 13.4, 13.41, 13.42, 13.43,
      13.44, 13.450000000000001, 13.46, 13.47, 13.48, 13.49, 13.5, 13.51, 13.52,
      13.530000000000001, 13.540000000000001, 13.55, 13.56, 13.57, 13.58, 13.59,
      13.6, 13.61, 13.620000000000001, 13.63, 13.64, 13.65, 13.66, 13.67, 13.68,
      13.69, 13.700000000000001, 13.71, 13.72, 13.73, 13.74, 13.75, 13.76, 13.77,
      13.780000000000001, 13.790000000000001, 13.8, 13.81, 13.82, 13.83, 13.84,
      13.85, 13.86, 13.870000000000001, 13.88, 13.89, 13.9, 13.91, 13.92, 13.93,
      13.94, 13.950000000000001, 13.96, 13.97, 13.98, 13.99, 14.0, 14.01, 14.02,
      14.030000000000001, 14.040000000000001, 14.05, 14.06, 14.07, 14.08, 14.09,
      14.1, 14.11, 14.120000000000001, 14.13, 14.14, 14.15, 14.16, 14.17, 14.18,
      14.19, 14.200000000000001, 14.21, 14.22, 14.23, 14.24, 14.25, 14.26, 14.27,
      14.280000000000001, 14.290000000000001, 14.3, 14.31, 14.32, 14.33, 14.34,
      14.35, 14.36, 14.370000000000001, 14.38, 14.39, 14.4, 14.41, 14.42, 14.43,
      14.44, 14.450000000000001, 14.46, 14.47, 14.48, 14.49, 14.5, 14.51, 14.52,
      14.530000000000001, 14.540000000000001, 14.55, 14.56, 14.57, 14.58, 14.59,
      14.6, 14.61, 14.620000000000001, 14.63, 14.64, 14.65, 14.66, 14.67, 14.68,
      14.69, 14.700000000000001, 14.71, 14.72, 14.73, 14.74, 14.75, 14.76, 14.77,
      14.780000000000001, 14.790000000000001, 14.8, 14.81, 14.82, 14.83, 14.84,
      14.85, 14.86, 14.870000000000001, 14.88, 14.89, 14.9, 14.91, 14.92, 14.93,
      14.94, 14.950000000000001, 14.96, 14.97, 14.98, 14.99, 15.0, 15.01, 15.02,
      15.030000000000001, 15.040000000000001, 15.05, 15.06, 15.07, 15.08, 15.09,
      15.1, 15.11, 15.120000000000001, 15.13, 15.14, 15.15, 15.16, 15.17, 15.18,
      15.19, 15.200000000000001, 15.21, 15.22, 15.23, 15.24, 15.25, 15.26, 15.27,
      15.280000000000001, 15.290000000000001, 15.3, 15.31, 15.32, 15.33, 15.34,
      15.35, 15.36, 15.370000000000001, 15.38, 15.39, 15.4, 15.41, 15.42, 15.43,
      15.44, 15.450000000000001, 15.46, 15.47, 15.48, 15.49, 15.5, 15.51, 15.52,
      15.530000000000001, 15.540000000000001, 15.55, 15.56, 15.57, 15.58, 15.59,
      15.6, 15.610000000000001, 15.620000000000001, 15.63, 15.64, 15.65, 15.66,
      15.67, 15.68, 15.69, 15.700000000000001, 15.71, 15.72, 15.73, 15.74, 15.75,
      15.76, 15.77, 15.780000000000001, 15.790000000000001, 15.8, 15.81, 15.82,
      15.83, 15.84, 15.85, 15.860000000000001, 15.870000000000001, 15.88, 15.89,
      15.9, 15.91, 15.92, 15.93, 15.94, 15.950000000000001, 15.96, 15.97, 15.98,
      15.99, 16.0, 16.01, 16.02, 16.03, 16.04, 16.05, 16.06, 16.07,
      16.080000000000002, 16.09, 16.1, 16.11, 16.12, 16.13, 16.14, 16.15, 16.16,
      16.17, 16.18, 16.19, 16.2, 16.21, 16.22, 16.23, 16.240000000000002, 16.25,
      16.26, 16.27, 16.28, 16.29, 16.3, 16.31, 16.32, 16.330000000000002, 16.34,
      16.35, 16.36, 16.37, 16.38, 16.39, 16.4, 16.41, 16.42, 16.43, 16.44, 16.45,
      16.46, 16.47, 16.48, 16.490000000000002, 16.5, 16.51, 16.52, 16.53, 16.54,
      16.55, 16.56, 16.57, 16.580000000000002, 16.59, 16.6, 16.61, 16.62, 16.63,
      16.64, 16.65, 16.66, 16.67, 16.68, 16.69, 16.7, 16.71, 16.72, 16.73,
      16.740000000000002, 16.75, 16.76, 16.77, 16.78, 16.79, 16.8, 16.81, 16.82,
      16.830000000000002, 16.84, 16.85, 16.86, 16.87, 16.88, 16.89, 16.9, 16.91,
      16.92, 16.93, 16.94, 16.95, 16.96, 16.97, 16.98, 16.990000000000002, 17.0,
      17.01, 17.02, 17.03, 17.04, 17.05, 17.06, 17.07, 17.080000000000002, 17.09,
      17.1, 17.11, 17.12, 17.13, 17.14, 17.150000000000002, 17.16, 17.17, 17.18,
      17.19, 17.2, 17.21, 17.22, 17.23, 17.240000000000002, 17.25, 17.26, 17.27,
      17.28, 17.29, 17.3, 17.31, 17.32, 17.330000000000002, 17.34, 17.35, 17.36,
      17.37, 17.38, 17.39, 17.400000000000002, 17.41, 17.42, 17.43, 17.44, 17.45,
      17.46, 17.47, 17.48, 17.490000000000002, 17.5, 17.51, 17.52, 17.53, 17.54,
      17.55, 17.56, 17.57, 17.580000000000002, 17.59, 17.6, 17.61, 17.62, 17.63,
      17.64, 17.650000000000002, 17.66, 17.67, 17.68, 17.69, 17.7, 17.71, 17.72,
      17.73, 17.740000000000002, 17.75, 17.76, 17.77, 17.78, 17.79, 17.8, 17.81,
      17.82, 17.830000000000002, 17.84, 17.85, 17.86, 17.87, 17.88, 17.89,
      17.900000000000002, 17.91, 17.92, 17.93, 17.94, 17.95, 17.96, 17.97, 17.98,
      17.990000000000002, 18.0, 18.01, 18.02, 18.03, 18.04, 18.05, 18.06, 18.07,
      18.080000000000002, 18.09, 18.1, 18.11, 18.12, 18.13, 18.14,
      18.150000000000002, 18.16, 18.17, 18.18, 18.19, 18.2, 18.21, 18.22, 18.23,
      18.240000000000002, 18.25, 18.26, 18.27, 18.28, 18.29, 18.3, 18.31, 18.32,
      18.330000000000002, 18.34, 18.35, 18.36, 18.37, 18.38, 18.39,
      18.400000000000002, 18.41, 18.42, 18.43, 18.44, 18.45, 18.46, 18.47, 18.48,
      18.490000000000002, 18.5, 18.51, 18.52, 18.53, 18.54, 18.55, 18.56, 18.57,
      18.580000000000002, 18.59, 18.6, 18.61, 18.62, 18.63, 18.64,
      18.650000000000002, 18.66, 18.67, 18.68, 18.69, 18.7, 18.71, 18.72, 18.73,
      18.740000000000002, 18.75, 18.76, 18.77, 18.78, 18.79, 18.8, 18.81, 18.82,
      18.830000000000002, 18.84, 18.85, 18.86, 18.87, 18.88, 18.89,
      18.900000000000002, 18.91, 18.92, 18.93, 18.94, 18.95, 18.96, 18.97, 18.98,
      18.990000000000002, 19.0, 19.01, 19.02, 19.03, 19.04, 19.05, 19.06, 19.07,
      19.080000000000002, 19.09, 19.1, 19.11, 19.12, 19.13, 19.14,
      19.150000000000002, 19.16, 19.17, 19.18, 19.19, 19.2, 19.21, 19.22, 19.23,
      19.240000000000002, 19.25, 19.26, 19.27, 19.28, 19.29, 19.3, 19.31, 19.32,
      19.330000000000002, 19.34, 19.35, 19.36, 19.37, 19.38, 19.39,
      19.400000000000002, 19.41, 19.42, 19.43, 19.44, 19.45, 19.46, 19.47, 19.48,
      19.490000000000002, 19.5, 19.51, 19.52, 19.53, 19.54, 19.55, 19.56, 19.57,
      19.580000000000002, 19.59, 19.6, 19.61, 19.62, 19.63, 19.64,
      19.650000000000002, 19.66, 19.67, 19.68, 19.69, 19.7, 19.71, 19.72, 19.73,
      19.740000000000002, 19.75, 19.76, 19.77, 19.78, 19.79, 19.8, 19.81, 19.82,
      19.830000000000002, 19.84, 19.85, 19.86, 19.87, 19.88, 19.89,
      19.900000000000002, 19.91, 19.92, 19.93, 19.94, 19.95, 19.96, 19.97, 19.98,
      19.990000000000002, 20.0, 20.01, 20.02, 20.03, 20.04, 20.05, 20.06, 20.07,
      20.080000000000002, 20.09, 20.1, 20.11, 20.12, 20.13, 20.14,
      20.150000000000002, 20.16, 20.17, 20.18, 20.19, 20.2, 20.21, 20.22, 20.23,
      20.240000000000002, 20.25, 20.26, 20.27, 20.28, 20.29, 20.3, 20.31, 20.32,
      20.330000000000002, 20.34, 20.35, 20.36, 20.37, 20.38, 20.39,
      20.400000000000002, 20.41, 20.42, 20.43, 20.44, 20.45, 20.46, 20.47, 20.48,
      20.490000000000002, 20.5, 20.51, 20.52, 20.53, 20.54, 20.55, 20.56, 20.57,
      20.580000000000002, 20.59, 20.6, 20.61, 20.62, 20.63, 20.64,
      20.650000000000002, 20.66, 20.67, 20.68, 20.69, 20.7, 20.71, 20.72, 20.73,
      20.740000000000002, 20.75, 20.76, 20.77, 20.78, 20.79, 20.8, 20.81, 20.82,
      20.830000000000002, 20.84, 20.85, 20.86, 20.87, 20.88, 20.89,
      20.900000000000002, 20.91, 20.92, 20.93, 20.94, 20.95, 20.96, 20.97, 20.98,
      20.990000000000002, 21.0, 21.01, 21.02, 21.03, 21.04, 21.05, 21.06, 21.07,
      21.080000000000002, 21.09, 21.1, 21.11, 21.12, 21.13, 21.14,
      21.150000000000002, 21.16, 21.17, 21.18, 21.19, 21.2, 21.21, 21.22, 21.23,
      21.240000000000002, 21.25, 21.26, 21.27, 21.28, 21.29, 21.3, 21.31, 21.32,
      21.330000000000002, 21.34, 21.35, 21.36, 21.37, 21.38, 21.39,
      21.400000000000002, 21.41, 21.42, 21.43, 21.44, 21.45, 21.46, 21.47, 21.48,
      21.490000000000002, 21.5, 21.51, 21.52, 21.53, 21.54, 21.55, 21.56, 21.57,
      21.580000000000002, 21.59, 21.6, 21.61, 21.62, 21.63, 21.64,
      21.650000000000002, 21.66, 21.67, 21.68, 21.69, 21.7, 21.71, 21.72, 21.73,
      21.740000000000002, 21.75, 21.76, 21.77, 21.78, 21.79, 21.8, 21.81, 21.82,
      21.830000000000002, 21.84, 21.85, 21.86, 21.87, 21.88, 21.89,
      21.900000000000002, 21.91, 21.92, 21.93, 21.94, 21.95, 21.96, 21.97, 21.98,
      21.990000000000002, 22.0, 22.01, 22.02, 22.03, 22.04, 22.05, 22.06, 22.07,
      22.080000000000002, 22.09, 22.1, 22.11, 22.12, 22.13, 22.14,
      22.150000000000002, 22.16, 22.17, 22.18, 22.19, 22.2, 22.21, 22.22, 22.23,
      22.240000000000002, 22.25, 22.26, 22.27, 22.28, 22.29, 22.3, 22.31, 22.32,
      22.330000000000002, 22.34, 22.35, 22.36, 22.37, 22.38, 22.39,
      22.400000000000002, 22.41, 22.42, 22.43, 22.44, 22.45, 22.46, 22.47, 22.48,
      22.490000000000002, 22.5, 22.51, 22.52, 22.53, 22.54, 22.55, 22.56, 22.57,
      22.580000000000002, 22.59, 22.6, 22.61, 22.62, 22.63, 22.64,
      22.650000000000002, 22.66, 22.67, 22.68, 22.69, 22.7, 22.71, 22.72, 22.73,
      22.740000000000002, 22.75, 22.76, 22.77, 22.78, 22.79, 22.8, 22.81, 22.82,
      22.830000000000002, 22.84, 22.85, 22.86, 22.87, 22.88, 22.89,
      22.900000000000002, 22.91, 22.92, 22.93, 22.94, 22.95, 22.96, 22.97, 22.98,
      22.990000000000002, 23.0, 23.01, 23.02, 23.03, 23.04, 23.05, 23.06, 23.07,
      23.080000000000002, 23.09, 23.1, 23.11, 23.12, 23.13, 23.14,
      23.150000000000002, 23.16, 23.17, 23.18, 23.19, 23.2, 23.21, 23.22, 23.23,
      23.240000000000002, 23.25, 23.26, 23.27, 23.28, 23.29, 23.3, 23.31, 23.32,
      23.330000000000002, 23.34, 23.35, 23.36, 23.37, 23.38, 23.39,
      23.400000000000002, 23.41, 23.42, 23.43, 23.44, 23.45, 23.46, 23.47, 23.48,
      23.490000000000002, 23.5, 23.51, 23.52, 23.53, 23.54, 23.55, 23.56, 23.57,
      23.580000000000002, 23.59, 23.6, 23.61, 23.62, 23.63, 23.64,
      23.650000000000002, 23.66, 23.67, 23.68, 23.69, 23.7, 23.71, 23.72, 23.73,
      23.740000000000002, 23.75, 23.76, 23.77, 23.78, 23.79, 23.8, 23.81, 23.82,
      23.830000000000002, 23.84, 23.85, 23.86, 23.87, 23.88, 23.89,
      23.900000000000002, 23.91, 23.92, 23.93, 23.94, 23.95, 23.96, 23.97, 23.98,
      23.990000000000002, 24.0, 24.01, 24.02, 24.03, 24.04, 24.05,
      24.060000000000002, 24.07, 24.080000000000002, 24.09, 24.1, 24.11, 24.12,
      24.13, 24.14, 24.150000000000002, 24.16, 24.17, 24.18, 24.19, 24.2, 24.21,
      24.22, 24.23, 24.240000000000002, 24.25, 24.26, 24.27, 24.28, 24.29, 24.3,
      24.310000000000002, 24.32, 24.330000000000002, 24.34, 24.35, 24.36, 24.37,
      24.38, 24.39, 24.400000000000002, 24.41, 24.42, 24.43, 24.44, 24.45, 24.46,
      24.47, 24.48, 24.490000000000002, 24.5, 24.51, 24.52, 24.53, 24.54, 24.55,
      24.560000000000002, 24.57, 24.580000000000002, 24.59, 24.6, 24.61, 24.62,
      24.63, 24.64, 24.650000000000002, 24.66, 24.67, 24.68, 24.69, 24.7, 24.71,
      24.72, 24.73, 24.740000000000002, 24.75, 24.76, 24.77, 24.78, 24.79, 24.8,
      24.810000000000002, 24.82, 24.830000000000002, 24.84, 24.85, 24.86, 24.87,
      24.88, 24.89, 24.900000000000002, 24.91, 24.92, 24.93, 24.94, 24.95, 24.96,
      24.97, 24.98, 24.990000000000002, 25.0, 25.01, 25.02, 25.03, 25.04, 25.05,
      25.060000000000002, 25.07, 25.080000000000002, 25.09, 25.1, 25.11, 25.12,
      25.13, 25.14, 25.150000000000002, 25.16, 25.17, 25.18, 25.19, 25.2, 25.21,
      25.22, 25.23, 25.240000000000002, 25.25, 25.26, 25.27, 25.28, 25.29, 25.3,
      25.310000000000002, 25.32, 25.330000000000002, 25.34, 25.35, 25.36, 25.37,
      25.38, 25.39, 25.400000000000002, 25.41, 25.42, 25.43, 25.44, 25.45, 25.46,
      25.47, 25.48, 25.490000000000002, 25.5, 25.51, 25.52, 25.53, 25.54, 25.55,
      25.560000000000002, 25.57, 25.580000000000002, 25.59, 25.6, 25.61, 25.62,
      25.63, 25.64, 25.650000000000002, 25.66, 25.67, 25.68, 25.69, 25.7, 25.71,
      25.72, 25.73, 25.740000000000002, 25.75, 25.76, 25.77, 25.78, 25.79, 25.8,
      25.810000000000002, 25.82, 25.830000000000002, 25.84, 25.85, 25.86, 25.87,
      25.88, 25.89, 25.900000000000002, 25.91, 25.92, 25.93, 25.94, 25.95, 25.96,
      25.97, 25.98, 25.990000000000002, 26.0, 26.01, 26.02, 26.03, 26.04, 26.05,
      26.060000000000002, 26.07, 26.080000000000002, 26.09, 26.1, 26.11, 26.12,
      26.13, 26.14, 26.150000000000002, 26.16, 26.17, 26.18, 26.19, 26.2, 26.21,
      26.22, 26.23, 26.240000000000002, 26.25, 26.26, 26.27, 26.28, 26.29, 26.3,
      26.310000000000002, 26.32, 26.330000000000002, 26.34, 26.35, 26.36, 26.37,
      26.38, 26.39, 26.400000000000002, 26.41, 26.42, 26.43, 26.44, 26.45, 26.46,
      26.47, 26.48, 26.490000000000002, 26.5, 26.51, 26.52, 26.53, 26.54, 26.55,
      26.560000000000002, 26.57, 26.580000000000002, 26.59, 26.6, 26.61, 26.62,
      26.63, 26.64, 26.650000000000002, 26.66, 26.67, 26.68, 26.69, 26.7, 26.71,
      26.72, 26.73, 26.740000000000002, 26.75, 26.76, 26.77, 26.78, 26.79, 26.8,
      26.810000000000002, 26.82, 26.830000000000002, 26.84, 26.85, 26.86, 26.87,
      26.88, 26.89, 26.900000000000002, 26.91, 26.92, 26.93, 26.94, 26.95, 26.96,
      26.97, 26.98, 26.990000000000002, 27.0, 27.01, 27.02, 27.03, 27.04, 27.05,
      27.060000000000002, 27.07, 27.080000000000002, 27.09, 27.1, 27.11, 27.12,
      27.13, 27.14, 27.150000000000002, 27.16, 27.17, 27.18, 27.19, 27.2, 27.21,
      27.22, 27.23, 27.240000000000002, 27.25, 27.26, 27.27, 27.28, 27.29, 27.3,
      27.310000000000002, 27.32, 27.330000000000002, 27.34, 27.35, 27.36, 27.37,
      27.38, 27.39, 27.400000000000002, 27.41, 27.42, 27.43, 27.44, 27.45, 27.46,
      27.47, 27.48, 27.490000000000002, 27.5, 27.51, 27.52, 27.53, 27.54, 27.55,
      27.560000000000002, 27.57, 27.580000000000002, 27.59, 27.6, 27.61, 27.62,
      27.63, 27.64, 27.650000000000002, 27.66, 27.67, 27.68, 27.69, 27.7, 27.71,
      27.72, 27.73, 27.740000000000002, 27.75, 27.76, 27.77, 27.78, 27.79, 27.8,
      27.810000000000002, 27.82, 27.830000000000002, 27.84, 27.85, 27.86, 27.87,
      27.88, 27.89, 27.900000000000002, 27.91, 27.92, 27.93, 27.94, 27.95, 27.96,
      27.97, 27.98, 27.990000000000002, 28.0, 28.01, 28.02, 28.03, 28.04, 28.05,
      28.060000000000002, 28.07, 28.080000000000002, 28.09, 28.1, 28.11, 28.12,
      28.13, 28.14, 28.150000000000002, 28.16, 28.17, 28.18, 28.19, 28.2, 28.21,
      28.22, 28.23, 28.240000000000002, 28.25, 28.26, 28.27, 28.28, 28.29, 28.3,
      28.310000000000002, 28.32, 28.330000000000002, 28.34, 28.35, 28.36, 28.37,
      28.38, 28.39, 28.400000000000002, 28.41, 28.42, 28.43, 28.44, 28.45, 28.46,
      28.47, 28.48, 28.490000000000002, 28.5, 28.51, 28.52, 28.53, 28.54, 28.55,
      28.560000000000002, 28.57, 28.580000000000002, 28.59, 28.6, 28.61, 28.62,
      28.63, 28.64, 28.650000000000002, 28.66, 28.67, 28.68, 28.69, 28.7, 28.71,
      28.72, 28.73, 28.740000000000002, 28.75, 28.76, 28.77, 28.78, 28.79, 28.8,
      28.810000000000002, 28.82, 28.830000000000002, 28.84, 28.85, 28.86, 28.87,
      28.88, 28.89, 28.900000000000002, 28.91, 28.92, 28.93, 28.94, 28.95, 28.96,
      28.97, 28.98, 28.990000000000002, 29.0, 29.01, 29.02, 29.03, 29.04, 29.05,
      29.060000000000002, 29.07, 29.080000000000002, 29.09, 29.1, 29.11, 29.12,
      29.13, 29.14, 29.150000000000002, 29.16, 29.17, 29.18, 29.19, 29.2, 29.21,
      29.22, 29.23, 29.240000000000002, 29.25, 29.26, 29.27, 29.28, 29.29, 29.3,
      29.310000000000002, 29.32, 29.330000000000002, 29.34, 29.35, 29.36, 29.37,
      29.38, 29.39, 29.400000000000002, 29.41, 29.42, 29.43, 29.44, 29.45, 29.46,
      29.47, 29.48, 29.490000000000002, 29.5, 29.51, 29.52, 29.53, 29.54, 29.55,
      29.560000000000002, 29.57, 29.580000000000002, 29.59, 29.6, 29.61, 29.62,
      29.63, 29.64, 29.650000000000002, 29.66, 29.67, 29.68, 29.69, 29.7, 29.71,
      29.72, 29.73, 29.740000000000002, 29.75, 29.76, 29.77, 29.78, 29.79, 29.8,
      29.810000000000002, 29.82, 29.830000000000002, 29.84, 29.85, 29.86, 29.87,
      29.88, 29.89, 29.900000000000002, 29.91, 29.92, 29.93, 29.94, 29.95, 29.96,
      29.97, 29.98, 29.990000000000002 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, -2.0816681711721685E-17, 0.010929504180230046, 0.021826423502508234,
      0.032689556756095653, 0.043517716267360618, 0.054309728140734724,
      0.065064432495683236, 0.075780683699623055, 0.086457350596715818,
      0.097093316732473178, 0.10768748057410088, 0.1182387557265247,
      0.12874607114402709, 0.13920837133743658, 0.14962461657680631,
      0.15999378308952306, 0.1703148632537882, 0.18058686578741187,
      0.19080881593186766, 0.20097975563155035, 0.21109874370818588,
      0.22116485603034269, 0.23117718567799203, 0.24113484310207245,
      0.25103695627900818, 0.26088267086013878, 0.27067115031601607,
      0.2804015760755233, 0.29007314765978132, 0.29968508281079759,
      0.30923661761482485, 0.31872700662038933, 0.32815552295096123,
      0.33752145841222625, 0.34682412359393633, 0.35606284796630344,
      0.36523697997091475, 0.37434588710613781, 0.38338895600699863,
      0.392365592519503, 0.40127522176938746, 0.41011728822527493,
      0.41889125575622427, 0.42759660768365282, 0.43623284682762126,
      0.44479949554747011, 0.45329609577679353, 0.46172220905274797,
      0.47007741653968388, 0.47836131904709966, 0.48657353704191203,
      0.49471371065504388, 0.502781499682329, 0.510776583579736,
      0.51869866145291665, 0.52654745204108355, 0.53432269369522511,
      0.54202414435066693, 0.549651581493993, 0.55720480212433487,
      0.564683622709052, 0.57208787913380832, 0.57941742664707407,
      0.58667213979906818, 0.59385191237516044, 0.60095665732376269,
      0.607986306678731, 0.61494081147630519, 0.62182014166661692,
      0.62862428601979448, 0.635353252026697, 0.642007065794314,
      0.64858577193586109, 0.65508943345561466, 0.66151813162851869,
      0.66787196587461028, 0.67415105362829808, 0.68035553020254691,
      0.6864855486480036, 0.69254127960712031, 0.69852291116331666,
      0.70443064868523453, 0.71026471466613561, 0.71602534855849687,
      0.72171280660385262, 0.72732736165794842, 0.7328693030112553,
      0.73833893620491009, 0.74373658284213662, 0.74906258039521467,
      0.75431728200805737, 0.75950105629446019, 0.76461428713209145,
      0.76965737345228824, 0.77463072902572483, 0.7795347822440335,
      0.7843699758974324, 0.78913676694844692, 0.79383562630179383,
      0.79846703857049983, 0.80303150183833316, 0.80752952741862694,
      0.81196163960956946, 0.81632837544604109, 0.82063028444808173,
      0.82486792836606448, 0.82904188092266329, 0.83315272755169578,
      0.83720106513392367, 0.84118750172990142, 0.84511265630995314,
      0.84897715848136956, 0.85278164821291025, 0.85652677555670487,
      0.86021320036763049, 0.863841592020276, 0.86741262912356143,
      0.87092699923312389, 0.87438539856154851, 0.87778853168654658,
      0.8811371112571682, 0.88443185769815025, 0.8876734989124867,
      0.89086276998232539, 0.89400041286827869, 0.89708717610725242,
      0.90012381450888124, 0.90311108885067692, 0.90604976557198058,
      0.90894061646681612, 0.91178441837575019, 0.91458195287684829,
      0.917334005975832, 0.92004136779553547, 0.92270483226475353,
      0.92532519680659386, 0.9279032620264156, 0.93043983139947184,
      0.93293571095833794, 0.93539170898024193, 0.93780863567437933,
      0.94018730286932639, 0.9425285237006461, 0.94483311229877853,
      0.94710188347732682, 0.94933565242183071, 0.95153523437912579,
      0.95370144434739079, 0.95583509676697409, 0.95793700521211034,
      0.96000798208360527, 0.96204883830260535, 0.96406038300553587,
      0.96604342324030668, 0.96799876366388649, 0.969927206241335,
      0.97182954994638815, 0.9737065904636929, 0.97555911989278532,
      0.977387926453902, 0.979193794195721, 0.98097750270511719,
      0.98273982681903371, 0.98448153633854674, 0.98620339574522631,
      0.98790616391986652, 0.98959059386369053, 0.99125743242209974,
      0.99290742001106636, 0.99454129034624628, 0.99615977017490354,
      0.99776357901071855, 0.99935342887157741, 1.0009300240204064,
      1.0024940607091508, 1.0040462269259538, 1.0055872021456387,
      1.0071176570835525, 1.0086382534528497, 1.0101496437253037,
      1.0116524708956989, 1.0131473682498948, 1.0146349591366135,
      1.0161158567430446, 1.017590663874308, 1.0190599727368639,
      1.0205243647259261, 1.0219844102169384, 1.0234406683611919,
      1.0248936868856262, 1.0263440018968872, 1.0277921376897008,
      1.0292386065596075, 1.0306839086201287, 1.0321285316244071,
      1.0335729507913836, 1.03501762863655, 1.0364630148073473,
      1.0379095459232279, 1.0393576454204605, 1.0408077234016968,
      1.0422601764903652, 1.0437153876899081, 1.045173726247933,
      1.0466355475252884, 1.0481011928701187, 1.0495709894969272,
      1.0510452503706833, 1.0525242740960028, 1.0540083448114319,
      1.0554977320888683, 1.0569926908381395, 1.0584934612167718,
      1.0600002685449612, 1.0615133232257827, 1.0630328206706467,
      1.0645589412300258, 1.0660918501294669, 1.0676316974109088,
      1.0691786178793068, 1.0707327310545887, 1.0722941411289419,
      1.0738629369294503, 1.0754391918860691, 1.0770229640049647,
      1.0786142958472054, 1.0802132145128081, 1.081819731630145,
      1.0834338433507036, 1.0850555303491904, 1.0866847578289867,
      1.0883214755329353, 1.0899656177594514, 1.0916171033839543,
      1.0932758358855923, 1.0949417033792639, 1.0966145786529029,
      1.0982943192100179, 1.0999807673174684, 1.1016737500584446,
      1.1033730793906433, 1.1050785522095985, 1.1067899504171583,
      1.1085070409950626, 1.1102295760836016, 1.1119572930653263,
      1.1136899146537638, 1.1154271489871228, 1.1171686897269359,
      1.118914216161609, 1.1206633933148376, 1.1224158720588489,
      1.124171289232426, 1.12592926776367, 1.1276894167974605,
      1.1294513318275581, 1.1312145948333039, 1.1329787744208735,
      1.1347434259690257, 1.1365080917792907, 1.1382723012305569,
      1.1400355709379877, 1.1417974049162143, 1.1435572947467603,
      1.1453147197496087, 1.147069147158887, 1.1488200323025766,
      1.150566818786207, 1.1523089386804521, 1.1540458127125779,
      1.155776850461663, 1.1575014505575323, 1.1592190008833276,
      1.1609288787816567, 1.1626304512642309, 1.1643230752249385,
      1.1660060976562634, 1.1676788558689939, 1.1693406777151241,
      1.1709908818138888, 1.1726287777808491, 1.1742536664599448,
      1.1758648401584479, 1.1774615828847206, 1.1790431705887134,
      1.1806088714051095, 1.18215794589904, 1.1836896473142862,
      1.185203221823881, 1.1866979087830307, 1.1881729409842725,
      1.1896275449147722, 1.19106094101569, 1.1924723439435192,
      1.1938609628333112, 1.1952260015637026, 1.1965666590236488,
      1.1978821293807871, 1.1991716023513288, 1.2004342634714005,
      1.2016692943697347, 1.2028758730416267, 1.2040531741240732,
      1.2052003691719806, 1.20631662693538, 1.2074011136375344,
      1.2084529932538655, 1.2094714277915901, 1.2104555775699954,
      1.211404601501239, 1.212317657371607, 1.2131939021231162,
      1.2140324921353829, 1.21483258350766, 1.2155933323409578,
      1.2163138950201504, 1.216993428495978, 1.217631090566859,
      1.2182260401604155, 1.218777437614627, 1.219284444958513,
      1.2197462261922714, 1.2201619475667618, 1.2205307778622643,
      1.2208518886664108, 1.2211244546512059, 1.2213476538490562,
      1.221520667927704, 1.2216426824639983, 1.2217128872163976,
      1.2217304763961365, 1.2216946489369538, 1.2216046087633161,
      1.2214595650570319, 1.2212587325221929, 1.221001331648345,
      1.2206865889718159, 1.2203137373351174, 1.2198820161443322,
      1.219390671624424, 1.218838957072373, 1.2182261331080735,
      1.217551467922908, 1.2168142375259279, 1.216013725987555,
      1.2151492256807472, 1.2142200375195427, 1.2132254711949015,
      1.2121648454078058, 1.2110374880995096, 1.209842736678896,
      1.2085799382468643, 1.2072484498176796, 1.2058476385372217,
      1.2043768818980691, 1.202835567951352, 1.2012230955153131,
      1.1995388743805173, 1.1977823255116504, 1.1959528812458469,
      1.1940499854874862, 1.1920730938994091, 1.1900216740904976,
      1.1878952057995602, 1.1856931810754718, 1.1834151044535266,
      1.1810604931279431, 1.178628877120476, 1.1761197994450987,
      1.173532816268696, 1.1708674970677337, 1.1681234247808598,
      1.1653001959573983, 1.1623974209016943, 1.159414723813269,
      1.1563517429227581, 1.1532081306235951, 1.14998355359939,
      1.1466776929470084, 1.143290244295277, 1.1398209179193173,
      1.1362694388504719, 1.132635546981795, 1.1289189971690781,
      1.1251195593274055, 1.121237018523197, 1.1172711750617359,
      1.1132218445701527, 1.1090888580758542, 1.1048720620803807,
      1.1005713186286787, 1.0961865053737758, 1.0917175156368542,
      1.0871642584626997, 1.0825266586705375, 1.0778046569002353,
      1.072998209653875, 1.0681072893326917, 1.0631318842693789,
      1.0580719987557534, 1.0529276530657974, 1.0476988834740661,
      1.0423857422694733, 1.0369882977644664, 1.0315066342995878,
      1.025940852243441, 1.0202910679880748, 1.0145574139397926,
      1.0087400385053997, 1.0028391060739159, 0.99685479699375745,
      0.99078730754541833, 0.98463684990966449, 0.97840365213126346,
      0.97208795807827741, 0.96569002739693954, 0.95921013546214517,
      0.952648573323576, 0.94600564764749906, 0.939281680654261,
      0.93247701005151384, 0.92559198896320438, 0.9186269858543622,
      0.91158238445172124, 0.90445858366021636, 0.89725599747538243,
      0.8899750548917098, 0.88261619980698891, 0.87517989092268822,
      0.86766660164040443, 0.8600768199544393, 0.85241104834054171,
      0.84466980364086452, 0.83685361694518157, 0.82896303346841949,
      0.82099861242454919, 0.81296092689689625, 0.80485056370490982,
      0.79666812326746028, 0.78841421946270385, 0.78008947948458651,
      0.77169454369603185, 0.76323006547886618, 0.754696711080563,
      0.746095159457838, 0.73742610211717474, 0.7286902429523322,
      0.719888298078901, 0.7110209956659701, 0.70208907576496837,
      0.69309329013574117, 0.68403440206993638, 0.67491318621175478,
      0.66573042837614471, 0.65648692536449027, 0.64718348477788246,
      0.63782092482802255, 0.62840007414584453, 0.61892177158790662,
      0.60938686604064174, 0.59979621622252655, 0.590150690484243,
      0.58045116660690088, 0.57069853159840433, 0.56089368148802032,
      0.55103752111923265, 0.54113096394095661, 0.53117493179717057,
      0.5211703547150629, 0.51111817069175125, 0.50101932547965866,
      0.49087477237060617, 0.48068547197872025, 0.47045239202220845,
      0.46017650710409458, 0.44985879849196941, 0.43950025389685976,
      0.42910186725126304, 0.41866463848644414, 0.4081895733090557,
      0.39767768297716771, 0.38712998407577237, 0.37654749829185052,
      0.36593125218906258, 0.35528227698214609, 0.34460160831109726,
      0.33389028601520543, 0.32314935390701044, 0.31237985954627667,
      0.3015828540140304, 0.29075939168675669, 0.27991053001082361,
      0.26903732927718582, 0.25814085239647955, 0.24722216467454411,
      0.23628233358846484, 0.22532242856319268, 0.2143435207488259,
      0.20334668279861171, 0.19233298864774856, 0.1813035132930442,
      0.17025933257351217, 0.1592015229519676, 0.14813116129769058,
      0.13704932467021802, 0.12595709010434747, 0.11485553439638947,
      0.10374573389177016, 0.092628764274006958, 0.081505700355154448,
      0.070377615867761839, 0.059245583258417958, 0.048110673482924714,
      0.036973955803183009, 0.025836497585830204, 0.014699364102697419,
      0.0035636183331425458, -0.0075696792316927025, -0.018699470782633926,
      -0.029824701384191486, -0.040944319164174924, -0.052057275501179175,
      -0.063162525209861514, -0.074259026723975025, -0.085345742277108422,
      -0.096421638081088168, -0.10748568450197743, -0.11853685623365184,
      -0.12957413246888663, -0.14059649706792318, -0.1516029387244692,
      -0.16259245112908857, -0.17356403312994206, -0.18451668889084694,
      -0.19544942804660653, -0.20636126585557882, -0.21725122334944807,
      -0.22811832748017019, -0.23896161126404764, -0.24978011392291569,
      -0.26057288102239407, -0.2713389646071902, -0.28207742333342345,
      -0.29278732259792584, -0.30346773466452492, -0.31411773878725086,
      -0.32473642133047653, -0.33532287588594767, -0.34587620338668945,
      -0.35639551221776711, -0.36687991832390104, -0.3773285453138906,
      -0.38774052456185293, -0.39811499530525957, -0.40845110473975377,
      -0.41874800811073953, -0.42900486880173866, -0.439220858419491,
      -0.449395156875814, -0.45952695246620145, -0.46961544194515092,
      -0.47965983059823442, -0.48965933231090325, -0.49961316963401342,
      -0.50952057384609883, -0.51938078501236851, -0.52919305204044254,
      -0.538956632732847, -0.54867079383623529, -0.55833481108738692,
      -0.5679479692559547, -0.57750956218400518, -0.58701889282232911,
      -0.59647527326356364, -0.60587802477211661, -0.61522647781093143,
      -0.62451997206508081, -0.63375785646223537, -0.64293948918999988,
      -0.65206423771016264, -0.66113147876984879, -0.67014059840963391,
      -0.67909099196860589, -0.68798206408643225, -0.696813228702434,
      -0.70558390905170643, -0.71429353765830406, -0.72294155632553492,
      -0.73152741612337469, -0.74005057737304747, -0.74851050962879229,
      -0.75690669165686064, -0.76523861141177352, -0.77350576600986953,
      -0.78170766170018624, -0.78984381383270663, -0.797913746824017,
      -0.80591699412040774, -0.81385309815845186, -0.82172161032311952,
      -0.82952209090345752, -0.83725410904587028, -0.84491724270506463,
      -0.85251107859268749, -0.86003521212370293, -0.86748924736056177,
      -0.87487279695520714, -0.882185482088951, -0.88942693241029669,
      -0.89659678597072345, -0.90369468915851359, -0.91072029663064091,
      -0.91767327124280584, -0.92455328397763048, -0.931360013871103,
      -0.93809314793728971, -0.94475238109139248, -0.95133741607119493,
      -0.95784796335694766, -0.96428374108975534, -0.970644474988512,
      -0.97692989826544729, -0.98313975154033728, -0.98927378275342559,
      -0.995331747077129, -1.0013134068265699, -1.0072185313689976,
      -1.013046897032156, -1.0187982870116525, -1.0244724912773913,
      -1.0300693064791167, -1.0355885358511434, -1.0410299891163111,
      -1.0463934823892354, -1.0516788380789133, -1.0568858847907254,
      -1.0620144572279206, -1.0670643960926138, -1.0720355479863757,
      -1.0769277653104563, -1.0817409061657184, -1.0864748342523247,
      -1.09112941876924, -1.0957045343136114, -1.1002000607800764,
      -1.1046158832600663, -1.1089518919411567, -1.1132079820065151,
      -1.1173840535345156, -1.1214800113985754, -1.1254957651672519,
      -1.1294312290046866, -1.1332863215714231, -1.1370609659256661,
      -1.1407550894250458, -1.1443686236289201, -1.1479015042012906,
      -1.1513536708143663, -1.1547250670528513, -1.1580156403189774,
      -1.1612253417383693, -1.1643541260667616, -1.1674019515976435,
      -1.170368780070862, -1.1732545765822435, -1.1760593094942851,
      -1.1787829503479565, -1.1814254737756584, -1.1839868574153984,
      -1.1864670818262091, -1.1888661304048731, -1.1911839893039928,
      -1.1934206473514406, -1.1955760959712418, -1.1976503291059364,
      -1.1996433431404427, -1.2015551368274882, -1.2033857112146218,
      -1.2051350695728644, -1.2068032173270329, -1.2083901619877588,
      -1.209895913085266, -1.2113204821049079, -1.2126638824245337,
      -1.2139261292536814, -1.2151072395746614, -1.2162072320855395,
      -1.2172261271450564, -1.2181639467195167, -1.2190207143316687,
      -1.2197964550116023, -1.2204911952496997, -1.2211049629516482,
      -1.2216377873955515, -1.222089699191151, -1.2224607302411945,
      -1.2227509137049521, -1.2229602839639133, -1.2230888765896737,
      -1.2231367283140395, -1.2231038770013452, -1.2229903616230278,
      -1.2227962222344391, -1.2225214999539298, -1.2221662369442114,
      -1.2217304763959966, -1.2212142625139393, -1.2206176405048714,
      -1.219940656568351, -1.2191833578895126, -1.2183457926342427,
      -1.2174280099466652, -1.2164300599489464, -1.215351993743421,
      -1.214193863417026, -1.2129557220480613, -1.2116376237152497,
      -1.2102396235091066, -1.2087617775456034, -1.207204142982133,
      -1.205566778035744, -1.2038497420036598, -1.2020530952860509,
      -1.2001768994110604, -1.1982212170620672, -1.1961861121071626,
      -1.1940716496308434, -1.191877895967884, -1.189604918739382,
      -1.1872527868909577, -1.1848215707330787, -1.1823113419834939,
      -1.1797221738117591, -1.1770541408858157, -1.1743073194206137,
      -1.1714817872287375, -1.1685776237730274, -1.1655949102211403,
      -1.162533729502049, -1.1593941663644283, -1.1561763074369118,
      -1.1528802412901695, -1.1495060585007935, -1.1460538517169387,
      -1.1425237157256911, -1.1389157475221334, -1.1352300463800524,
      -1.1314667139242651, -1.1276258542045259, -1.1237075737709532,
      -1.1197119817509644, -1.1156391899276483, -1.1114893128195544,
      -1.1072624677618359, -1.1029587749887251, -1.0985783577172612,
      -1.0941213422322658, -1.0895878579724838, -1.0849780376178566,
      -1.0802920171778849, -1.0755299360810149, -1.0706919372650152,
      -1.0657781672682778, -1.0607887763220074, -1.0557239184432303,
      -1.0505837515285867, -1.0453684374488381, -1.0400781421440439,
      -1.0347130357193588, -1.0292732925413737, -1.0237590913349763,
      -1.0181706152806445, -1.0125080521121363, -1.0067715942145137,
      -1.0009614387224413, -0.99507778761870014, -0.98912084783286347,
      -0.98309083134007935, -0.9769879552598888, -0.97081244195502592,
      -0.96456451913015451, -0.95824441993045517, -0.9518523830400285,
      -0.94538865278003736, -0.93885347920653406, -0.93224711820791717,
      -0.92556983160194817, -0.91882188723227287, -0.91200355906438435,
      -0.90511512728097732, -0.89815687837661384, -0.891129105251651,
      -0.88403210730538484, -0.87686619052831238, -0.86963166759349231,
      -0.86232885794691883, -0.85495808789685146, -0.84751969070205313,
      -0.84001400665886283, -0.83244138318705074, -0.824802174914399,
      -0.81709674375993568, -0.80932545901578068, -0.80148869742754247,
      -0.793586843273182, -0.78562028844033449, -0.7775894325019832,
      -0.76949468279045574, -0.76133645446968334, -0.75311517060566779,
      -0.74483126223507978, -0.73648516843198031, -0.72807733637254657,
      -0.71960822139782576, -0.71107828707437926, -0.70248800525284416,
      -0.69383785612429871, -0.68512832827442272, -0.67635991873537782,
      -0.667533133035368, -0.65864848524583031, -0.649706498026205,
      -0.64070770266624644, -0.63165263912581437, -0.62254185607210666,
      -0.61337591091429866, -0.60415536983553109, -0.59488080782220321,
      -0.58555280869054316, -0.57617196511040181, -0.56673887862623884,
      -0.557254159675244, -0.54771842760258438, -0.53813231067371614,
      -0.52849644608373514, -0.51881147996373067, -0.50907806738410255,
      -0.49929687235482145, -0.48946856782259207, -0.47959383566487412,
      -0.46967336668076903, -0.459707860578712, -0.449698025960946,
      -0.43964458030477116, -0.42954824994052471, -0.41940977002627133,
      -0.40922988451919673, -0.39900934614367134, -0.38874891635594477,
      -0.37844936530550649, -0.36811147179304005, -0.35773602322498271,
      -0.34732381556467462, -0.33687565328007985, -0.32639234928806204,
      -0.31587472489522872, -0.30532360973528788, -0.29473984170296491,
      -0.28412426688443693, -0.27347773948428816, -0.2628011217489819,
      -0.25209528388686, -0.24136110398464247, -0.23059946792046521,
      -0.21981126927340638, -0.2089974092295627, -0.1981587964846353,
      -0.18729634714305854, -0.17641098461365937, -0.16550363950187891,
      -0.15457524949853646, -0.14362675926519447, -0.13265912031606947,
      -0.12167329089658188, -0.11067023585849629, -0.099650926531714576,
      -0.088616340592704221, -0.077567461929613515, -0.06650528050408587,
      -0.055430792209775086, -0.044344998727629314, -0.033248907377925366,
      -0.022143530969108788, -0.011029887643461904, 9.0999280364212343E-5,
      0.011218101467949201, 0.022350385732757244, 0.03348681420284641,
      0.044626344490575634, 0.055767929865303656, 0.066910519428983961,
      0.078053058294684591, 0.089194487767934622, 0.10033374553088906,
      0.11146976582925237, 0.12260147966192456, 0.1337278149733051,
      0.14484769684824883, 0.15596004770956398, 0.16706378751805245,
      0.17815783397501947, 0.18924110272720518, 0.20031250757407856,
      0.21137096067744243, 0.22241537277329743, 0.23344465338589698,
      0.24445771104394917, 0.25545345349888915, 0.26643078794517694,
      0.27738862124254576, 0.28832586014014649, 0.299241411502526,
      0.31013418253736147, 0.32100308102489622, 0.33184701554901846,
      0.3426648957298849, 0.35345563245805328, 0.36421813813003862,
      0.37495132688521549, 0.38565411484401346, 0.39632542034732465,
      0.40696416419703146, 0.41756926989762472, 0.428139663898792,
      0.43867427583892249, 0.44917203878945716, 0.45963188949999217,
      0.47005276864406753, 0.48043362106556053, 0.49077339602561426,
      0.50107104744999154, 0.51132553417681925, 0.52153582020461009,
      0.53170087494048368, 0.54181967344852011, 0.55189119669815612,
      0.561914431812532, 0.57188837231672962, 0.58181201838578778,
      0.59168437709244648, 0.6015044626545053, 0.61127129668173119,
      0.62098390842221862, 0.63064133500813613, 0.64024262170074542,
      0.64978682213464578, 0.65927299856111743, 0.66870022209052038,
      0.67806757293362674, 0.68737414064183033, 0.69661902434612455,
      0.70580133299478509, 0.71492018558965942, 0.72397471142097336,
      0.73296405030059553, 0.741887352793633, 0.7507437804483178,
      0.75953250602407574, 0.76825271371768677, 0.77690359938747766,
      0.78548437077544386, 0.79399424772722327, 0.80243246240984312,
      0.81079825952714535, 0.81909089653282952, 0.82730964384101247,
      0.835453785034232, 0.84352261706881082, 0.85151545047750887,
      0.85943160956936893, 0.86727043262670267, 0.87503127209910414,
      0.88271349479445171, 0.8903164820667866, 0.89783963000102052,
      0.90528234959436837, 0.912644066934475, 0.9199242233741064,
      0.92712227570238082, 0.93423769631244535, 0.94126997336552065,
      0.94821861095126836, 0.95508312924439454, 0.96186306465741533,
      0.96855796998953458, 0.97516741457156, 0.98169098440678981,
      0.98812828230781435, 0.9944789280291515, 1.0007425583956908,
      1.0069188274268366, 1.013007406456341, 1.0190079842477242,
      1.0249202671052653, 1.0307439789804755, 1.0364788615740208,
      1.042124674433029, 1.0476811950437446, 1.0531482189194585,
      1.058525559683688, 1.0638130491485425, 1.069010537388239,
      1.074117892807722, 1.0791350022063304, 1.0840617708365017,
      1.0888981224574352, 1.0936439993837084, 1.0982993625287885,
      1.1028641914434172, 1.1073384843488188, 1.1117222581647273,
      1.116015548532169, 1.1202184098309966, 1.124330915192133,
      1.1283531565045135, 1.1322852444166862, 1.1361273083330596,
      1.1398794964047743, 1.1435419755151781, 1.1471149312598929,
      1.1505985679214488, 1.1539931084384798, 1.1572987943694686,
      1.1605158858510285, 1.1636446615507139, 1.1666854186143505,
      1.1696384726078888, 1.1725041574537756, 1.1752828253618242,
      1.177974846754624, 1.180580610187447, 1.1831005222626869,
      1.1855350075388256, 1.1878845084339333, 1.1901494851237175,
      1.1923304154341337, 1.1944277947285575, 1.1964421357895567,
      1.1983739686952568, 1.2002238406903425, 1.201992316051687,
      1.2036799759486683, 1.2052874182981603, 1.2068152576142523,
      1.2082641248527117, 1.2096346672502254, 1.2109275481584438,
      1.2121434468728767, 1.2132830584566583, 1.2143470935592318,
      1.2153362782299868, 1.2162513537268913, 1.2170930763201611,
      1.2178622170910116, 1.2185595617255398, 1.2191859103037777,
      1.2197420770839702, 1.2202288902821443, 1.2206471918469859,
      1.2209978372301153, 1.2212816951518064, 1.2214996473621915,
      1.2216525883980405, 1.221741425335146, 1.2217670775364027,
      1.2217304763956278, 1.2216325650771991, 1.2214742982515732,
      1.2212566418267523, 1.2209805726757756, 1.2206470783603056,
      1.2202571568503786, 1.2198118162404008, 1.2193120744614636,
      1.2187589589900545, 1.2181535065532514, 1.2174967628304665,
      1.2167897821518374, 1.216033627193343, 1.2152293686687214,
      1.2143780850182933, 1.2134808620947539, 1.212538792846054,
      1.211552976995429, 1.2105245207186806, 1.2094545363188152,
      1.208344141898106, 1.2071944610276952, 1.206006622414822,
      1.2047817595677748, 1.2035210104586658, 1.2022255171841303,
      1.2008964256240329, 1.1995348850983107, 1.1981420480220273,
      1.196719069558752, 1.1952671072723691, 1.1937873207774159,
      1.1922808713880522, 1.1907489217657767, 1.1891926355659812,
      1.1876131770834668, 1.1860117108970112, 1.1843894015131093,
      1.1827474130089852, 1.1810869086749964, 1.1794090506565211,
      1.177714999595457, 1.1760059142714392, 1.1742829512428674,
      1.1725472644878809, 1.170800005045382, 1.1690423206562053,
      1.1672753554045723, 1.1655002493599187, 1.163718138219217,
      1.1619301529499069, 1.1601374194335505, 1.1583410581103062,
      1.156542183624361, 1.1547419044704044, 1.1529413226412837,
      1.15114153327693, 1.1493436243146893, 1.1475486761411406,
      1.1457577612455503, 1.1439719438750389, 1.1421922796916011,
      1.140419815431061, 1.1386555885640999, 1.1369006269594548,
      1.13515594854939, 1.1334225609975626, 1.131701461369393,
      1.1299936358050326, 1.1283000591950483, 1.1266216948589425,
      1.12495949422658, 1.1233143965226624, 1.1216873284543385,
      1.1200792039020597, 1.1184909236137754, 1.1169233749025937,
      1.1153774313479665, 1.1138539525005557, 1.1123537835908306,
      1.1108777552415272, 1.1094266831840509, 1.10800136797893,
      1.106602594740403, 1.1052311328652475, 1.1038877357659451,
      1.1025731406082562, 1.101288068053313, 1.1000332220043276,
      1.098809289357974, 1.0976169397605626, 1.0964568253690761,
      1.095329580617157, 1.0942358219861339, 1.0931761477811572,
      1.0921511379125306, 1.0911613536823292, 1.0902073375763572,
      1.089289613061545, 1.0884086843888394, 1.0875650364016942,
      1.0867591343501677, 1.0859914237107795, 1.0852623300121238,
      1.0845722586663513, 1.0839215948065535, 1.0833107031301412,
      1.08273992774824, 1.0822095920412111, 1.0817199985203092,
      1.0812714286955594, 1.0808641429498991, 1.0804983804196342,
      1.0801743588812638, 1.0798922746447319, 1.0796523024531102,
      1.0794545953888195, 1.0792992847863836, 1.079186480151763,
      1.0791162690883316, 1.0790887172294994, 1.0791038681780434,
      1.0791617434521565, 1.0792623424382652, 1.0794056423506186,
      1.0795915981977033, 1.0798201427554854, 1.0800911865475071,
      1.0804046178318725, 1.0807603025951089, 1.0811580845529509,
      1.0815977851580396, 1.0820792036145563, 1.0826021168997961,
      1.0831662797926953, 1.0837714249092949, 1.0844172627451776,
      1.0851034817248484, 1.0858297482580686, 1.0865957068031347,
      1.0874009799371056, 1.0882451684329517, 1.089127851343634,
      1.0900485860930822, 1.091006908574069, 1.0920023332529682,
      1.0930343532813456, 1.0941024406144011, 1.0952060461362096,
      1.0963445997917514, 1.0975175107256849, 1.0987241674278547,
      1.0999639378854755, 1.1012361697419772, 1.1025401904624743,
      1.103875307505795, 1.1052408085030618, 1.1066359614427603,
      1.1080600148622486, 1.1095121980456693, 1.1109917212282161,
      1.1124977758066854, 1.1140295345562781, 1.1155861518535837,
      1.1171667639056968, 1.1187704889853924, 1.1203964276723166,
      1.1220436631001125, 1.1237112612094176, 1.1253982710066821,
      1.1271037248287044, 1.1288266386128429, 1.1305660121728167,
      1.13232082948002, 1.1340900589502725, 1.1358726537359347, 1.13766755202328,
      1.1394736773350886, 1.1412899388383251, 1.1431152316568491,
      1.1449484371890641, 1.1467884234303944, 1.1486340453005341,
      1.1504841449753385, 1.1523375522232837, 1.1541930847464033,
      1.1560495485255873, 1.1579057381701443, 1.1597604372715473,
      1.1616124187612391, 1.1634604452724002, 1.1653032695055778,
      1.1671396345980674, 1.1689682744969305, 1.1707879143355535,
      1.1725972708136334, 1.1743950525804656, 1.17617996062144,
      1.177950688647623, 1.1797059234883007, 1.1814443454863841,
      1.1831646288965532, 1.1848654422860092, 1.1865454489377405,
      1.1882033072561542, 1.1898376711749696, 1.191447190567257,
      1.1930305116574758, 1.1945862774354108, 1.1961131280718702,
      1.1976097013360296, 1.1990746330142752, 1.2005065573304583,
      1.2019041073673897, 1.2032659154894763, 1.2045906137663696,
      1.2058768343974775, 1.2071232101372307, 1.2083283747209725,
      1.2094909632913298, 1.2106096128249453, 1.2116829625594441,
      1.2127096544204869, 1.2136883334488004, 1.214617648227037,
      1.21549625130635, 1.21632279963253, 1.2170959549715998, 1.2178143843347029,
      1.2184767604021918, 1.219081761946758, 1.219628074255481,
      1.2201143895506679, 1.2205394074093563, 1.2209018351813379,
      1.2212003884055895, 1.2214337912249673, 1.2216007767990469,
      1.2217000877149706, 1.2217304763961885, 1.2216907055089428,
      1.221579548366392, 1.2213957893302336, 1.2211382242097077,
      1.2208056606578566, 1.2203969185648968, 1.2199108304486146,
      1.219346241841633, 1.2187020116754421, 1.2179770126610654,
      1.2171701316662555, 1.2162802700890669, 1.215306344227735,
      1.2142472856467086, 1.2131020415387301, 1.211869575082847,
      1.2105488657982562, 1.2091389098938341, 1.207638720613285,
      1.2060473285757589, 1.2043637821118534, 1.2025871475948893,
      1.2007165097673353, 1.1987509720623089, 1.1966896569200212,
      1.1945317060990785, 1.1922762809825396, 1.18992256287863,
      1.1874697533160032, 1.184917074333478, 1.1822637687641335,
      1.1795091005136882, 1.1766523548330612, 1.173692838585028,
      1.1706298805048903, 1.1674628314550681, 1.1641910646735347,
      1.160813976016007, 1.1573309841918287, 1.1537415309934322,
      1.1500450815193553, 1.1462411243906834, 1.1423291719608915,
      1.1383087605189885, 1.1341794504859068, 1.129940826604064,
      1.1255924981200411, 1.1211340989603134, 1.1165652878999717,
      1.1118857487243698, 1.1070951903836723, 1.1021933471401963,
      1.0971799787085568, 1.0920548703885222, 1.0868178331905547,
      1.081468703953981, 1.0760073454577677, 1.0704336465238327,
      1.0647475221128857, 1.0589489134127452, 1.0530377879191022,
      1.047014139508704, 1.0408779885049271, 1.0346293817357053,
      1.0282683925838096, 1.0217951210294409, 1.0152096936851185,
      1.0085122638228565, 1.0017030113936158, 0.99478214303899737,
      0.98774989209519937, 0.98060651858921, 0.97335230922723426,
      0.965987577375366, 0.95851266303248506, 0.95092793279539489,
      0.94323377981620993, 0.93543062375198871, 0.92751891070662851,
      0.91949911316504063, 0.91137172991960069, 0.90313728598891563,
      0.89479633252891988, 0.88634944673630189, 0.877797231744317,
      0.86914031651099977, 0.8603793556997934, 0.85151502955264557,
      0.84254804375559922, 0.83347912929690526, 0.82430904231771518,
      0.81503856395536978, 0.80566850017934455, 0.79619968161989707,
      0.78663296338945654, 0.77696922489680409, 0.76720936965411157,
      0.75735432507686673, 0.74740504227678062, 0.737362495847683,
      0.72722768364452206, 0.71700162655549282, 0.70668536826738571,
      0.69627997502419126, 0.68578653537906742, 0.67520615993971678,
      0.66453998110725221, 0.65378915280864147, 0.6429548502227761,
      0.63203826950028164, 0.62104062747712629, 0.60996316138212558,
      0.598807128538416, 0.58757380605900045, 0.57626449053643358,
      0.56488049772677618, 0.55342316222785182, 0.54189383715197192,
      0.53029389379316361, 0.51862472128904469, 0.50688772627740941,
      0.49508433254765577, 0.48321598068713995, 0.47128412772257888,
      0.45929024675657565, 0.44723582659942129, 0.43512237139624194,
      0.42295140024963163, 0.41072444683785891, 0.3984430590287813,
      0.38610879848957219, 0.3737232402923773, 0.36128797251602213,
      0.34880459584388257, 0.33627472315804924, 0.32369997912990034,
      0.31108199980720452, 0.29842243219788051, 0.28572293385053538,
      0.27298517243191206, 0.26021082530137019, 0.24740157908251628,
      0.23455912923213862, 0.22168517960655043, 0.2087814420254798,
      0.19584963583364629, 0.18289148746014092, 0.16990872997575046,
      0.15690310264836754, 0.14387635049658881, 0.13083022384167595,
      0.11776647785798783, 0.10468687212202618, 0.091593170160227916,
      0.078487138995644856, 0.065370548693644892, 0.052245171906762054,
      0.0391127834188628, 0.025975159688709136, 0.012834078393121152,
      -0.00030868203016761603, -0.013451342839813418, -0.02659212544818304,
      -0.039729251878555125, -0.052860945222067426, -0.065985430094264191,
      -0.079100933091135223, -0.092205683244465445, -0.10529791247638773,
      -0.118375856053003, -0.13143775303691904, -0.14448184673857062,
      -0.15750638516621157, -0.17050962147439719, -0.18348981441088183,
      -0.19644522876173912, -0.20937413579461145, -0.22227481369993995,
      -0.23514554803004648, -0.24798463213593436, -0.26079036760167335,
      -0.27356106467625857, -0.28629504270278183, -0.29899063054481279,
      -0.31164616700985986, -0.3242600012697715, -0.33683049327796094,
      -0.34935601418333451, -0.36183494674078853, -0.37426568571816304,
      -0.38664663829952833, -0.39897622448468523, -0.41125287748474559,
      -0.4234750441137094, -0.43564118517588285, -0.44774977584906267,
      -0.45979930606331604, -0.47178828087532548, -0.48371522083810914,
      -0.49557866236605852, -0.50737715809514927, -0.51910927723827149,
      -0.53077360593550571, -0.54236874759930254, -0.55389332325442575,
      -0.56534597187258528, -0.57672535070163555, -0.58803013558928,
      -0.59925902130113384, -0.61041072183312339, -0.62148397071805583,
      -0.63247752132632973, -0.6433901471606619, -0.65422064214477282,
      -0.66496782090592488, -0.67563051905124016, -0.68620759343773419,
      -0.6966979224359563, -0.70710040618719039, -0.71741396685413428,
      -0.72763754886497511, -0.7377701191508067, -0.747810667376318,
      -0.75775820616368184, -0.7676117713095949, -0.77737042199537865,
      -0.787033240990142, -0.79659933484686762, -0.80606783409145111,
      -0.81543789340457828, -0.82470869179642792, -0.83387943277413568,
      -0.84294934450199044, -0.85191767995429357, -0.86078371706088253,
      -0.86954675884523269, -0.87820613355514743, -0.88676119478596327,
      -0.89521132159628158, -0.90355591861615825, -0.91179441614775114,
      -0.91992627025839691, -0.92795096286608081, -0.93586800181731977,
      -0.94367692095739, -0.95137728019292978, -0.9589686655468761,
      -0.966450689205752, -0.97382298955927649, -0.98108523123230384,
      -0.98823710510908491, -0.99527832834986107, -1.0022086443997866,
      -1.0090278229901797, -1.0157356601321232, -1.0223319781024174,
      -1.0288166254218929, -1.0351894768261254, -1.0414504332285166,
      -1.0475994216758311, -1.0536363952961487, -1.0595613332392964,
      -1.065374240609767, -1.0710751483921694, -1.0766641133692303,
      -1.0821412180323746, -1.0875065704849582, -1.0927603043381426,
      -1.0979025785994738, -1.1029335775542373, -1.1078535106395759,
      -1.1126626123114718, -1.1173611419046128, -1.121949383485205,
      -1.1264276456967925, -1.1307962615991158, -1.1350555885001123,
      -1.1392060077810626, -1.1432479247150076, -1.1471817682784451,
      -1.1510079909564133, -1.1547270685410067, -1.1583394999234149,
      -1.161845806879531, -1.1652465338492424, -1.1685422477094425,
      -1.1717335375408733, -1.1748210143888482, -1.1778053110179825,
      -1.1806870816609687, -1.1834670017615143, -1.1861457677115206,
      -1.1887240965825856, -1.1912027258519475, -1.1935824131229231,
      -1.195863935839977, -1.1980480909984785, -1.2001356948493027,
      -1.2021275825982891, -1.204024608100748, -1.2058276435510666,
      -1.2075375791675194, -1.2091553228724181, -1.2106817999676882,
      -1.2121179528059614, -1.2134647404573515, -1.2147231383719563,
      -1.2158941380382478, -1.2169787466374455, -1.217977986693993,
      -1.218892895722228, -1.2197245258694225, -1.220473943555235,
      -1.2211422291077594, -1.2217304763962533, -1.2222397924606763,
      -1.2226712971381579, -1.2230261226865393, -1.2233054134050629,
      -1.2235103252523924, -1.2236420254620426, -1.2237016921553885,
      -1.2236905139523093, -1.2236096895796937, -1.2234604274778353,
      -1.223243945404914, -1.2229614700396716, -1.2226142365823869,
      -1.222203488354316, -1.2217304763957144, -1.2211964590625541,
      -1.2206027016220931, -1.2199504758474116, -1.2192410596110392,
      -1.2184757364778274, -1.2176557952971812, -1.21678252979477,
      -1.2158572381638839, -1.2148812226565324, -1.213855789174425,
      -1.2127822468599836, -1.2116619076874857, -1.2104960860544935,
      -1.2092860983736942, -1.2080332626652641, -1.2067388981499145,
      -1.2054043248427198, -1.2040308631478862, -1.2026198334545559,
      -1.2011725557337976, -1.1996903491369175, -1.1981745315951779,
      -1.1966264194211009, -1.1950473269114432, -1.1934385659519815,
      -1.1918014456242421, -1.1901372718142715, -1.1884473468235925,
      -1.1867329689824662, -1.1849954322655709, -1.1832360259102042,
      -1.1814560340371782, -1.1796567352744545, -1.1778394023836931,
      -1.1760053018898069, -1.1741556937136219, -1.1722918308077928,
      -1.1704149587960553, -1.1685263156159253, -1.166627131164985,
      -1.1647186269508294, -1.1628020157447907, -1.1608785012395515,
      -1.1589492777107633, -1.1570155296827274, -1.1550784315982847,
      -1.1531391474930082, -1.1511988306737602, -1.1492586234017521,
      -1.1473196565801835, -1.1453830494465467, -1.1434499092697057,
      -1.1415213310518213, -1.1395983972352222, -1.1376821774143024,
      -1.135773728052538, -1.1338740922046819, -1.1319842992442561,
      -1.1301053645963866, -1.1282382894760632, -1.1263840606319233,
      -1.1245436500956014, -1.1227180149367315, -1.12090809702368,
      -1.1191148227900507, -1.1173391030070512, -1.115581832561775,
      -1.1138438902414574, -1.1121261385237693, -1.1104294233732026,
      -1.1087545740436033, -1.1071024028869059, -1.1054737051681189,
      -1.1038692588866075, -1.1022898246037214, -1.1007361452768247,
      -1.0992089460997345, -1.097708934349652, -1.096236799240591,
      -1.0947932117833579, -1.0933788246521012, -1.0919942720574742,
      -1.0906401696264352, -1.0893171142887061, -1.0880256841699218,
      -1.0867664384914866, -1.0855399174771567, -1.0843466422663777,
      -1.0831871148343672, -1.08206181791898, -1.0809712149543591,
      -1.0799157500113696, -1.0788958477448327, -1.0779119133475688,
      -1.0769643325112239, -1.0760534713939174, -1.0751796765946731,
      -1.0743432751346436, -1.0735445744451262, -1.0727838623623418,
      -1.0720614071289858, -1.0713774574025139, -1.0707322422701628,
      -1.070125971270683, -1.0695588344227593, -1.0690310022600897,
      -1.0685426258731114, -1.0680938369573334, -1.0676847478682534,
      -1.0673154516828149, -1.0669860222673879, -1.0666965143522196,
      -1.0664469636123235, -1.066237386754765, -1.0660677816123059,
      -1.065938127243347, -1.065848384038143, -1.0657984938312191,
      -1.065788380019951, -1.0658179476892555, -1.0658870837423271,
      -1.0659956570373692, -1.0661435185302601, -1.0663305014230955,
      -1.0665564213185339, -1.0668210763798949, -1.0671242474969245,
      -1.0674656984571815, -1.067845176122957, -1.0682624106136509,
      -1.0687171154935582, -1.0692089879649556, -1.0697377090664333,
      -1.0703029438763876, -1.0709043417215822, -1.0715415363907175,
      -1.0722141463529, -1.0729217749809412, -1.0736640107794051,
      -1.0744404276172812, -1.0752505849652414, -1.0760940281373523,
      -1.0769702885371608, -1.0778788839080671, -1.0788193185878774,
      -1.0797910837674414, -1.0807936577532866, -1.081826506234131,
      -1.0828890825511996, -1.0839808279722112, -1.0851011719689554,
      -1.0862495324983577, -1.0874253162868999, -1.0886279191183286,
      -1.0898567261245113, -1.0911111120793449, -1.0923904416956174,
      -1.0936940699246955, -1.095021342258929, -1.0963715950366866,
      -1.0977441557498633, -1.0991383433538009, -1.1005534685794591,
      -1.1019888342477506, -1.1034437355859281, -1.1049174605458856,
      -1.1064092901242755, -1.1079184986843278, -1.1094443542792305,
      -1.1109861189769858, -1.1125430491866029, -1.1141143959855133,
      -1.1156994054480964, -1.117297318975194, -1.1189073736244839,
      -1.120528802441616, -1.1221608347919734, -1.1238026966929497,
      -1.1254536111466134, -1.1271127984726443, -1.128779476641443,
      -1.1304528616072516, -1.1321321676412086, -1.1338166076641973,
      -1.135505393579374, -1.1371977366042585, -1.1388928476022688,
      -1.1405899374135766, -1.142288217185194, -1.1439868987001189,
      -1.1456851947054829, -1.1473823192395551, -1.149077487957481,
      -1.1507699184556601, -1.152458830594641, -1.1541434468204188,
      -1.1558229924840095, -1.1574966961592283, -1.1591637899585123,
      -1.1608235098467079, -1.1624750959527033, -1.1641177928788049,
      -1.1657508500077367, -1.1673735218071615, -1.1689850681316283,
      -1.1705847545218193, -1.1721718525010216, -1.1737456398686887,
      -1.1753054009910042, -1.1768504270883786, -1.1783800165197058,
      -1.179893475063355, -1.181390116194776, -1.1828692613605833,
      -1.184330240249104, -1.1857723910572153, -1.1871950607534365,
      -1.1885976053371596, -1.1899793900939382, -1.1913397898467373,
      -1.1926781892030793, -1.1939939827979753, -1.1952865755325781,
      -1.1965553828084723, -1.1977998307575179, -1.1990193564671665,
      -1.2002134082011884, -1.2013814456157184, -1.2025229399705606,
      -1.2036373743356721, -1.2047242437927661, -1.205783055631954,
      -1.2068133295433721, -1.2078145978037296, -1.2087864054576956,
      -1.2097283104941035, -1.2106398840168633, -1.2115207104105785,
      -1.2123703875007708, -1.2131885267086941, -1.2139747532006395,
      -1.2147287060317538, -1.2154500382842546, -1.2161384172000238,
      -1.2167935243075698, -1.2174150555432592, -1.2180027213668132,
      -1.2185562468710414, -1.2190753718857434, -1.2195598510757759,
      -1.2200094540332489, -1.2204239653638098, -1.2208031847669996,
      -1.2211469271106619, -1.2214550224993661, -1.2217273163368445,
      -1.2219636693824045, -1.2221639578013257, -1.2223280732091948,
      -1.2224559227102116, -1.2225474289294016, -1.2226025300387795,
      -1.2226211797774305, -1.222603347465508, -1.2225490180121539,
      -1.2224581919173421, -1.2223308852676507, -1.222167129725942,
      -1.2219669725150175, -1.2217304763951891, -1.2214577196358243,
      -1.2211487959808616, -1.2208038146083182, -1.2204229000838012,
      -1.2200061923080516, -1.2195538464585349, -1.2190660329251128,
      -1.2185429372398047, -1.2179847600007037, -1.2173917167900083,
      -1.2167640380863136, -1.2161019691710537, -1.2154057700292751,
      -1.2146757152446783, -1.2139120938889993, -1.2131152094058109,
      -1.2122853794887041, -1.2114229359539985, -1.2105282246079399,
      -1.2096016051084886, -1.2086434508217452, -1.2076541486730208,
      -1.2066340989927047, -1.2055837153568529, -1.2045034244226966,
      -1.2033936657590358, -1.2022548916715858, -1.2010875670234282,
      -1.1998921690505104, -1.1986691871723441, -1.1974191227979722,
      -1.1961424891272048, -1.1948398109472864, -1.1935116244250055,
      -1.1921584768943547, -1.1907809266397928, -1.1893795426752214,
      -1.1879549045187332, -1.1865076019631959, -1.1850382348428239,
      -1.1835474127957162, -1.1820357550225669, -1.1805038900415246,
      -1.1789524554393644, -1.1773820976190414, -1.1757934715436857,
      -1.1741872404771949, -1.1725640757214366, -1.1709246563502387,
      -1.1692696689402042, -1.1675998072984521, -1.1659157721874336,
      -1.1642182710468432, -1.1625080177127871, -1.1607857321342963,
      -1.15905214008724, -1.1573079728858304, -1.1555539670917179,
      -1.1537908642208763, -1.1520194104482984, -1.1502403563106829,
      -1.1484544564071628, -1.1466624690982044, -1.1448651562027889,
      -1.1430632826939582, -1.1412576163928783, -1.1394489276614881,
      -1.1376379890938426, -1.1358255752063091, -1.1340124621266559,
      -1.1321994272821991, -1.1303872490870965, -1.1285767066288939,
      -1.1267685793544462, -1.1249636467553203, -1.1231626880527881,
      -1.1213664818825289, -1.1195758059791359, -1.1177914368605717,
      -1.1160141495126259, -1.1142447170735708, -1.1124839105190312,
      -1.110732498347254, -1.1089912462648628, -1.1072609168731846,
      -1.1055422693553076, -1.1038360591639318, -1.1021430377101611,
      -1.1004639520533233, -1.0987995445919287, -1.097150552755894,
      -1.0955177087001147, -1.0939017389995203, -1.0923033643456839,
      -1.0907232992451388, -1.0891622517194783, -1.087620923007331,
      -1.0861000072683655, -1.0846001912893712, -1.0831221541925657,
      -1.0816665671462053, -1.0802340930775998, -1.0788253863886503,
      -1.0774410926739904, -1.0760818484418413, -1.074748280837684,
      -1.0734410073708205, -1.0721606356439588, -1.0709077630858743,
      -1.0696829766872753, -1.0684868527399576, -1.0673199565793108,
      -1.0661828423303308, -1.0650760526571468, -1.0640001185162185,
      -1.0629555589132531, -1.0619428806639502, -1.0609625781586294,
      -1.0600151331308481, -1.0591010144301072, -1.0582206777986549,
      -1.0573745656525602, -1.0565631068670578, -1.0557867165662769,
      -1.0550457959174375, -1.0543407319295353, -1.0536718972566554,
      -1.0530396500059318, -1.052444333550236, -1.0518862763456835,
      -1.0513657917539752, -1.050883177869689, -1.0504387173525429,
      -1.0500326772647179, -1.0496653089132704, -1.0493368476977134,
      -1.0490475129628241, -1.0487975078566956, -1.0485870191941213,
      -1.048416217325352, -1.0482852560102516, -1.0481942722979312,
      -1.0481433864118703, -1.0481327016405975, -1.0481623042339403,
      -1.0482322633049179, -1.048342630737275, -1.048493441098707,
      -1.0486847115598414, -1.0489164418189256, -1.0491886140323354,
      -1.0495011927508855, -1.0498541248619553, -1.0502473395375003,
      -1.0506807481879128, -1.0511542444217958, -1.0516677040116427,
      -1.0522209848654336, -1.0528139270041972, -1.0534463525454763,
      -1.0541180656928051, -1.0548288527311014, -1.0555784820280567,
      -1.056366704041489, -1.0571932513326598, -1.0580578385855788,
      -1.0589601626322434, -1.0598999024838789, -1.0608767193680957,
      -1.0618902567720143, -1.0629401404913101, -1.0640259786851773,
      -1.0651473619372145, -1.0663038633221564, -1.0674950384785202,
      -1.068720425687067, -1.0699795459550845, -1.0712719031064937,
      -1.0725969838776919, -1.0739542580191614, -1.0753431784027805,
      -1.0767631811348068, -1.07821368567452, -1.0796940949584493,
      -1.0812037955301903, -1.0827421576757377, -1.084308535564307,
      -1.0859022673946059, -1.0875226755464915, -1.0891690667379916,
      -1.0908407321876148, -1.0925369477819122, -1.0942569742482511,
      -1.0960000573327182, -1.0977654279831142, -1.099552302536978,
      -1.1013598829145985, -1.1031873568169051, -1.10503389792824,
      -1.1068986661238955, -1.1087808076823766, -1.1106794555023221,
      -1.1125937293239934, -1.1145227359552941, -1.1164655695022345,
      -1.1184213116037394, -1.120389031670793, -1.1223677871297648,
      -1.1243566236699107, -1.1263545754949154, -1.1283606655784388,
      -1.130373905923564, -1.1323932978260522, -1.1344178321413652,
      -1.1364464895553248, -1.1384782408583494, -1.1405120472231702,
      -1.1425468604859532, -1.1445816234307189, -1.1466152700769841,
      -1.1486467259705302, -1.1506749084772048, -1.1526987270796767,
      -1.1547170836770231, -1.1567288728870795, -1.1587329823514632,
      -1.1607282930431297, -1.1627136795764237, -1.1646880105194912,
      -1.1666501487089502, -1.1685989515667545, -1.1705332714191097,
      -1.1724519558173783, -1.174353847860844, -1.1762377865212521,
      -1.1781026069690241, -1.1799471409010236, -1.1817702168697988,
      -1.1835706606141829, -1.1853472953911472, -1.1870989423088181,
      -1.1888244206605261, -1.1905225482598223, -1.1921921417763168,
      -1.1938320170722656, -1.1954409895397775, -1.1970178744385651,
      -1.1985614872340966, -1.2000706439360744, -1.2015441614371325,
      -1.20298085785162, -1.2043795528544097, -1.2057390680195805,
      -1.207058227158907, -1.2083358566600373, -1.2095707858242339,
      -1.210761847203617, -1.2119078769377707, -1.2130077150896188,
      -1.2140602059804702, -1.2150641985241366, -1.2160185465600004,
      -1.2169221091849489, -1.2177737510840725, -1.218572342860009,
      -1.2193167613608609, -1.2200058900065487, -1.2206386191135465,
      -1.2212138462178579, -1.2217304763961623, -1.2221874225850229,
      -1.222583605898061, -1.2229179559410077, -1.2231894111245218,
      -1.2233969189746974, -1.223539436441162, -1.2236159302026604,
      -1.2236253769700558, -1.2235667637866408, -1.2234390883256643,
      -1.2232413591850118, -1.2229725961789131, -1.2226318306266306,
      -1.2222181056380121, -1.2217304763958377, -1.2211680104348763,
      -1.2205297879175689, -1.2198149019062583, -1.2190224586318763,
      -1.2181515777590344, -1.2172013926474041, -1.2161710506093513,
      -1.2150597131637184, -1.213866556285689, -1.2125907706526857,
      -1.2112315618861897, -1.209788150789449, -1.2082597735809908,
      -1.2066456821238658, -1.2049451441505894, -1.20315744348367,
      -1.2012818802517031, -1.1993177711009617, -1.197264449402389,
      -1.1951212654540098, -1.1928875866786142, -1.1905627978167457,
      -1.18814630111487, -1.1856375165087256, -1.1830358818017719,
      -1.1803408528387158, -1.1775519036740403, -1.174668526735519,
      -1.1716902329826624, -1.168616552060036, -1.165447032445458,
      -1.162181241592982, -1.1588187660706792, -1.1553592116931466,
      -1.1518022036487461, -1.1481473866214975, -1.144394424907647,
      -1.1405430025268446, -1.1365928233279314, -1.1325436110892908,
      -1.1283951096137639, -1.1241470828180915, -1.11979931481687,
      -1.1153516100010128, -1.1108037931106884, -1.1061557093027334,
      -1.1014072242125328, -1.0965582240103173, -1.0916086154519626,
      -1.0865583259241602, -1.0814073034840757, -1.0761555168933996,
      -1.0708029556468486, -1.0653496299950989, -1.0597955709621321,
      -1.0541408303570614, -1.048385480780357, -1.0425296156245649,
      -1.0365733490694642, -1.0305168160717175, -1.0243601723490103,
      -1.0181035943586718, -1.0117472792708642, -1.0052914449362635,
      -0.99873632984834049, -0.99208219310020207, -0.98532931433605175,
      -0.97847799369728661, -0.97152855176323749, -0.96448132948660958,
      -0.95733668812365857, -0.95009500915908318, -0.94275669422573194,
      -0.93532216501911725, -0.92779186320678608, -0.92016625033260679,
      -0.91244580771593753, -0.90463103634585351, -0.8967224567703137,
      -0.88872060898043648, -0.88062605228988611, -0.87243936520937582,
      -0.86416114531644272, -0.85579200912039988, -0.84733259192267585,
      -0.83878354767244623, -0.83014554881771685, -0.82141928615188375,
      -0.81260546865576744, -0.80370482333531734, -0.79471809505485758,
      -0.78564604636614477, -0.77648945733311, -0.76724912535244694,
      -0.75792586497013437, -0.74852050769387446, -0.73903390180158079,
      -0.72946691214593129, -0.71982041995511836, -0.71009532262980224,
      -0.70029253353637988, -0.69041298179662325, -0.6804576120737571,
      -0.67042738435507532, -0.66032327373111654, -0.65014627017154669,
      -0.6398973782977545, -0.6295776171522941, -0.61918801996520312,
      -0.60872963391732959, -0.59820351990067389, -0.58761075227590276,
      -0.57695241862706459, -0.56622961951360906, -0.5554434682197853,
      -0.54459509050149157, -0.5336856243307041, -0.5227162196374876,
      -0.51168803804975216, -0.500602252630803, -0.48946004761475714,
      -0.4782626181399689, -0.4670111699804208, -0.45570691927538121,
      -0.44435109225715047, -0.43294492497724735, -0.42148966303088448,
      -0.40998656128000388, -0.3984368835748654, -0.38684190247425604,
      -0.37520289896453257, -0.363521162177404, -0.35179798910670929,
      -0.34003468432416634, -0.32823255969423887, -0.31639293408819857,
      -0.3045171330973977, -0.29260648874602196, -0.2806623392031658,
      -0.2686860284945326, -0.256678906213715, -0.2446423272331982,
      -0.23257765141517808, -0.2204862433222235, -0.20836947192792429,
      -0.19622871032764294, -0.18406533544932344, -0.1718807277645808,
      -0.159676271000102, -0.14745335184940336, -0.1352133596851311,
      -0.12295768627183129, -0.1106877254794765, -0.098404872997620463,
      -0.086110526050414526, -0.073806083112520543, -0.061492943625930344,
      -0.049172507717939962, -0.0368461759201292, -0.024515348888673565,
      -0.012181427125831909, 0.00015418929713859747, 0.012490101015628655,
      0.024824909645880675, 0.0371572180574809, 0.049485630644342922,
      0.061808753593804305, 0.074125195154023923, 0.08643356589948975,
      0.098732478994519646, 0.11102055045481062, 0.12329639940686353,
      0.13555864834529596, 0.147805923387902, 0.16003685452845065,
      0.17225007588712954, 0.18444422595859583, 0.19661794785753753,
      0.20876988956170692, 0.22089870415240143, 0.23300305005223587,
      0.24508159126026308, 0.25713299758429931, 0.26915594487046013,
      0.2811491152297993, 0.29311119726206286, 0.30504088627644171,
      0.31693688450931556, 0.32879790133892606, 0.34062265349693327,
      0.35240986527681278, 0.36415826873902757, 0.37586660391299,
      0.3875336189956905, 0.39915807054702, 0.41073872368170883,
      0.42227435225784732, 0.43376373906202159, 0.4452056759908562,
      0.45659896422918095, 0.46794241442451967, 0.4792348468581108,
      0.4904750916122611, 0.50166198873406542, 0.51279438839553071,
      0.52387115104991311, 0.53489114758444667, 0.54585325946927588,
      0.55675637890267138, 0.56759940895246108, 0.57838126369366,
      0.58910086834236386, 0.59975715938570329, 0.61034908470809734,
      0.62087560371356554, 0.63133568744423718, 0.6417283186949797,
      0.65205249212414063, 0.66230721436045248, 0.67249150410603187,
      0.68260439223545655, 0.69264492189103533, 0.70261214857412313,
      0.71250514023257361, 0.722322977344318, 0.732064752997022,
      0.7417295729639477, 0.751316555775835, 0.76082483278902857,
      0.77025354824969228, 0.779601859354181, 0.78886893630564425,
      0.79805396236671478, 0.80715613390851215, 0.81617466045575182,
      0.82510876472817385, 0.83395768267817594, 0.84272066352472363,
      0.85139696978358992, 0.85998587729383735, 0.86848667524074363,
      0.87689866617497392, 0.88522116602823786, 0.89345350412534252,
      0.90159502319265, 0.90964507936307182, 0.91760304217752231,
      0.92546829458295454, 0.933240232926946, 0.94091826694889358,
      0.94850181976786052, 0.95599032786709937, 0.96338324107530071,
      0.97068002254458441, 0.97788014872530571, 0.98498310933768929,
      0.99198840734034266, 0.99889555889569492, 1.0057040933324037,
      1.0124135531047573, 1.0190234937491636, 1.025533483837715,
      1.0319431049289034, 1.0382519515155579, 1.0444596309699972,
      1.0505657634865, 1.0565699820211105, 1.0624719322288596, 1.068271272398404,
      1.0739676733842065, 1.0795608185362382, 1.0850504036272997,
      1.0904361367780426, 1.0957177383796295, 1.1008949410142665,
      1.1059674893734794, 1.1109351401743377, 1.1157976620736036,
      1.1205548355798647, 1.1252064529637764, 1.1297523181663605,
      1.1341922467055352, 1.1385260655808704, 1.1427536131766125,
      1.1468747391631127, 1.1508893043966233, 1.1547971808176398,
      1.1585982513477007, 1.1622924097848562, 1.1658795606977705,
      1.1693596193185476, 1.1727325114343474, 1.1759981732778411,
      1.1791565514165974, 1.1822076026414114, 1.18515129385368,
      1.1879876019518787, 1.1907165137171702, 1.1933380256982702,
      1.1958521440955554, 1.19825888464452, 1.2005582724986792,
      1.2027503421118584, 1.2048351371200818, 1.2068127102230102,
      1.2086831230650275, 1.2104464461160584, 1.2121027585521196,
      1.2136521481357394, 1.2150947110962269, 1.2164305520099246,
      1.2176597836804401, 1.2187825270189503, 1.2197989109246494,
      1.2207090721653426, 1.2215131552583103, 1.2222113123514422,
      1.2228037031047521, 1.2232904945722598, 1.2236718610843829,
      1.2239479841308005, 1.2241190522439183, 1.2241852608829507,
      1.2241468123186736, 1.2240039155189051, 1.223756786034788,
      1.2234056458878633, 1.2229507234580794, 1.2223922533726752,
      1.2217304763960806, 1.2209656393208366, 1.2200979948595729,
      1.2191278015381204, 1.218055323589788, 1.216880830850835,
      1.2156045986572208, 1.2142269077426151, 1.2127480441377834,
      1.2111682990713137, 1.209487968871795, 1.2077073548714232,
      1.2058267633111102, 1.2038465052471468, 1.2017668964593917,
      1.1995882573610908, 1.1973109129103321, 1.1949351925231575,
      1.192461429988376, 1.1898899633841231, 1.1872211349961668,
      1.1844552912379984, 1.1815927825727641, 1.1786339634370226,
      1.175579192166361, 1.1724288309229389, 1.169183245624914,
      1.1658428058778139, 1.1624078849078905, 1.1588788594974204,
      1.1552561099220173, 1.15154001988996, 1.147730976483549,
      1.1438293701025177, 1.1398355944094578, 1.1357500462774019,
      1.1315731257393993, 1.1273052359402396, 1.1229467830902615,
      1.1184981764212774, 1.1139598281446088, 1.1093321534112395,
      1.104615570274126, 1.0998104996525706, 1.0949173652988216,
      1.0899365937667123, 1.0848686143824871, 1.0797138592177471,
      1.0744727630645057, 1.0691457634123875, 1.0637333004279326,
      1.0582358169360264, 1.0526537584033853, 1.0469875729242288,
      1.041237711207913, 1.0354046265687711, 1.0294887749178943,
      1.0234906147570388, 1.0174106071745324, 1.0112492158432036,
      1.0050069070203291, 0.99868414954950624, 0.99228141486457877,
      0.98579917699541642, 0.97923791257567216, 0.97259810085241549,
      0.96588022369764881, 0.95908476562166933, 0.95221221378825971,
      0.945263058031691, 0.93823779087546011, 0.9311369075528132,
      0.923960906028939, 0.91671028702490964, 0.9093855540431891,
      0.90198721339482324, 0.89451577422819062, 0.88697174855930716,
      0.87935565130364657, 0.87166800030943892, 0.86390931639242807,
      0.8560801233719938, 0.84818094810868583, 0.84021232054305284,
      0.8321747737357762, 0.8240688439090369, 0.815895070489089,
      0.80765399614999756, 0.7993461668584988, 0.79097213191990878,
      0.78253244402509126, 0.77402765929839035, 0.76545833734651048,
      0.756825041308277, 0.74812833790525068, 0.739368797493127,
      0.73054699411389445, 0.72166350554867842, 0.71271891337125581,
      0.70371380300213382, 0.694648763763206, 0.68552438893290335,
      0.67634127580177583, 0.66710002572848714, 0.6578012441961385,
      0.64844554086888706, 0.639033529648823, 0.62956582873297839,
      0.62004306067052906, 0.61046585242003371, 0.60083483540671212,
      0.59115064557969221, 0.58141392346916421, 0.57162531424343155,
      0.5617854677656865, 0.5518950386506577, 0.54195468632082833,
      0.53196507506241686, 0.52192687408084026, 0.51184075755578562,
      0.50170740469571928, 0.49152749979184668, 0.48130173227141027,
      0.47103079675033038, 0.46071539308510412, 0.45035622642386242,
      0.43995400725666745, 0.42950945146481356, 0.41902328036923686,
      0.4084962207778769, 0.39792900503200135, 0.3873223710514041,
      0.3766770623783986, 0.36599382822068516, 0.35527342349279928,
      0.34451660885640395, 0.33372415075904471, 0.32289682147159732,
      0.31203539912416844, 0.30114066774049042, 0.29021341727075423,
      0.27925444362277024, 0.26826454869153071, 0.25724454038694478,
      0.24619523265991405, 0.23511744552651026, 0.22401200509033342,
      0.21287974356293896, 0.20172149928233576, 0.19053811672947046,
      0.17933044654266972, 0.16809934553003508, 0.15684567667964089,
      0.14557030916767524, 0.13427411836425582, 0.12295798583711845,
      0.11162279935292843, 0.10026945287632193, 0.088898846566589168,
      0.077511886771945052, 0.066109486021400307, 0.054692563014120704,
      0.043262042606376311, 0.031818855795871667, 0.02036393970358065,
      0.0088982375529748914, -0.0025773013533710656, -0.014061721659795794,
      -0.025554061986287437, -0.037053354959832731, -0.048558627248605768,
      -0.060068899598768419, -0.071583186874167232, -0.083100498098715614,
      -0.09461983650165541, -0.10614019956562362, -0.11766057907755106,
      -0.12917996118246639, -0.14069732644012478, -0.15221164988459712,
      -0.16372190108669898, -0.17522704421939472, -0.18672603812611688,
      -0.1982178363919947, -0.20970138741809083, -0.22117563449853714,
      -0.23263951590067689, -0.24409196494815044, -0.25553191010694259,
      -0.26695827507445441, -0.27836997887147269, -0.28976593593718558,
      -0.30114505622711685, -0.31250624531406518, -0.32384840449197883,
      -0.33517043088282639, -0.34647121754636878, -0.3577496535929458,
      -0.36900462429911207, -0.38023501122627795, -0.39143969234222281,
      -0.40261754214549739, -0.4137674317927485, -0.42488822922886671,
      -0.435978799320042, -0.447038003989592, -0.45806470235664237,
      -0.46905775087760548, -0.480016003490387, -0.49093831176139874,
      -0.50182352503522676, -0.51267049058706726, -0.52347805377775825,
      -0.53424505821150781, -0.54497034589621829, -0.5556527574063479,
      -0.5662911320484072, -0.576884308028855, -0.58743112262458241,
      -0.59793041235575684, -0.60838101316112458, -0.61878176057564283,
      -0.62913148991047141, -0.63942903643521964, -0.64967323556245793,
      -0.65986292303443972, -0.669996935111947, -0.68007410876528818,
      -0.69009328186732477, -0.700053293388557, -0.70995298359413417,
      -0.71979119424282478, -0.72956676878784377, -0.739278552579479,
      -0.74892539306952666, -0.75850614001738392, -0.76801964569785408,
      -0.7774647651105111, -0.7868403561906343, -0.79614528002163,
      -0.80537840104886671, -0.814538587294906, -0.82362471057601072,
      -0.83263564671995483, -0.84157027578495125, -0.85042748227978515,
      -0.85920615538493439, -0.86790518917474913, -0.87652348284052573,
      -0.885059940914459, -0.89351347349442811, -0.90188299646944714,
      -0.91016743174586823, -0.91836570747410884, -0.92647675827596643,
      -0.934499525472359, -0.94243295731146837, -0.9502760091972231,
      -0.95802764391798623, -0.96568683187547755, -0.97325255131375565,
      -0.98072378854826592, -0.98809953819483332, -0.99537880339854279,
      -1.0025605960624673, -1.0096439370760733, -1.0166278565433708,
      -1.0235113940105873, -1.030293598693413, -1.0369735297036575,
      -1.0435502562752892, -1.0500228579897579, -1.05639042500056,
      -1.0626520582569055, -1.0688068697264939, -1.0748539826172574,
      -1.0807925315980258, -1.0866216630180352, -1.0923405351251851,
      -1.0979483182830276, -1.1034441951863061, -1.1088273610750852,
      -1.11409702394733, -1.1192524047698456, -1.1242927376875842,
      -1.1292172702311238, -1.1340252635223775, -1.1387159924783321,
      -1.1432887460128511, -1.1477428272363914, -1.1520775536535881,
      -1.1562922573586645, -1.16038628522852, -1.1643589991135186,
      -1.1682097760258137, -1.1719380083252169, -1.1755431039024784,
      -1.1790244863599579, -1.1823815951895837, -1.1856138859480285,
      -1.1887208304290837, -1.1917019168330909, -1.1945566499334275,
      -1.1972845512399297, -1.1998851591592441, -1.2023580291519662,
      -1.2047027338866028, -1.2069188633901837, -1.2090060251955492,
      -1.2109638444852118, -1.2127919642317284, -1.2144900453345477,
      -1.2160577667532406, -1.2174948256371039, -1.2188009374510114,
      -1.2199758360975397, -1.2210192740352255, -1.2219310223929896,
      -1.2227108710806067, -1.2233586288951808, -1.2238741236236335,
      -1.2242572021410532, -1.2245077305049656, -1.2246255940453978,
      -1.2246106974507291, -1.224462964849268, -1.2241823398865326,
      -1.2237687857981674, -1.223222285478454, -1.2225428415444202,
      -1.2217304763954451, -1.2207852322683752, -1.2197071712880803,
      -1.2184963755134495, -1.2171529469787428, -1.2156770077303438,
      -1.2140686998587942, -1.2123281855261479, -1.2104556469885857,
      -1.2084512866142862, -1.2063153268964928, -1.204048010461795,
      -1.2016496000735852, -1.1991203786306288, -1.1964606491608447,
      -1.1936707348101223, -1.1907509788262862, -1.1877017445381519,
      -1.1845234153296205, -1.1812163946088763, -1.1777811057726109,
      -1.1742179921653191, -1.1705275170335885, -1.1667101634754906,
      -1.1627664343849338, -1.1586968523911059, -1.1545019597928996,
      -1.150182318488395, -1.1457385098993653, -1.1411711348908278,
      -1.136480813685639, -1.1316681857741162, -1.1267339098187734,
      -1.1216786635540772, -1.1165031436813153, -1.1112080657585537,
      -1.1057941640857252, -1.1002621915848225, -1.0946129196752594,
      -1.0888471381444267, -1.0829656550133659, -1.0769692963977724,
      -1.0708589063641187, -1.0646353467811653, -1.0582994971666695,
      -1.0518522545294811, -1.0452945332069863, -1.0386272646979242,
      -1.0318513974906578, -1.0249678968868843, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, -1.3877787807814457E-17, -0.011312063450616888,
      -0.022621439937777738, -0.033927042754330082, -0.045227784936598105,
      -0.056522579450043006, -0.067810339376279838, -0.07908997810140872,
      -0.09036040950560903, -0.101620548153952, -0.11286930948837874,
      -0.12410561002079663, -0.13532836752724306, -0.14653650124306353,
      -0.15772893205905469, -0.1689045827185188, -0.18006237801517552,
      -0.19120124499187874, -0.20232011314008444, -0.21341791460001255,
      -0.22449358436144845, -0.23554606046513016, -0.24657428420466068,
      -0.25757720032889253, -0.26855375724472308, -0.27950290722024651,
      -0.29042360658820104, -0.3013148159496532, -0.31217550037786213,
      -0.32300462962226073, -0.33380117831249556, -0.34456412616246634,
      -0.35529245817429955, -0.36598516484220311, -0.37664124235613194,
      -0.38725969280520828, -0.39783952438083475, -0.40837975157943573,
      -0.41887939540476549, -0.42933748356972279, -0.43975305069760534,
      -0.45012513852274633, -0.46045279609046336, -0.47073507995626573,
      -0.48097105438424759, -0.49115979154461, -0.50130037171024711,
      -0.511391883452333, -0.52143342383484459, -0.53142409860796092,
      -0.54136302240027234, -0.55124931890973594, -0.56108212109332034,
      -0.57086057135527, -0.5805838217339272, -0.59025103408705626,
      -0.59986138027559588, -0.60941404234579011, -0.61890821270962393,
      -0.62834309432351254, -0.6377179008651751, -0.64703185690863263,
      -0.65628419809727889, -0.66547417131494613, -0.67460103485492184,
      -0.68366405858685042, -0.69266252412145612, -0.70159572497303768,
      -0.71046296671966569, -0.71926356716103657, -0.72799685647391232,
      -0.7366621773651002, -0.745258885221911, -0.75378634826003665,
      -0.76224394766880132, -0.77063107775372031, -0.77894714607631987,
      -0.78719157359116221, -0.79536379478002261, -0.80346325778316474,
      -0.81148942452766815, -0.8194417708527485, -0.82731978663203043,
      -0.835122975892715, -0.84285085693159723, -0.85050296242788848,
      -0.8580788395527883, -0.8655780500757706, -0.87300017046753009,
      -0.88034479199954752, -0.88761152084023287, -0.89479997814759726,
      -0.90190980015842093, -0.90894063827386673, -0.91589215914150723,
      -0.9227640447337202, -0.929555992422422, -0.93626771505009154,
      -0.9428989409970614, -0.94944941424502893, -0.9559188944367647,
      -0.96230715693197377, -0.96861399285929073, -0.97483920916436606,
      -0.9809826286540243, -0.98704409003645854, -0.9930234479574358,
      -0.9989205730324896, -1.0047353518750719, -1.0104676871206417,
      -1.0161174974466658, -1.0216847175885169, -1.0271692983512364,
      -1.032571206617156, -1.0378904253493524, -1.0431269535909173,
      -1.048280806460038, -1.0533520151408577, -1.0583406268701183,
      -1.0632467049195624, -1.0680703285740953, -1.0728115931056852,
      -1.0774706097430025, -1.0820475056367924, -1.0865424238209678,
      -1.0909555231694268, -1.0952869783485844, -1.0995369797656251,
      -1.1037057335124747, -1.1077934613054796, -1.1118004004208233,
      -1.1157268036256491, -1.1195729391049305, -1.123339090384065,
      -1.1270255562472209, -1.130632650651433, -1.1341607026364642,
      -1.1376100562304454, -1.1409810703513017, -1.1442741187039858,
      -1.147489589673528, -1.1506278862139292, -1.1536894257329027,
      -1.1566746399724983, -1.1595839748856196, -1.1624178905084626,
      -1.1651768608288979, -1.1678613736508221, -1.1704719304545004,
      -1.1730090462529412, -1.175473249444313, -1.1778650816604501,
      -1.1801850976114723, -1.1824338649265487, -1.1846119639908461,
      -1.1867199877786951, -1.188758541683006, -1.1907282433409834,
      -1.1926297224561639, -1.1944636206168346, -1.1962305911108566,
      -1.1979312987369521, -1.1995664196124898, -1.2011366409778115,
      -1.2026426609971634, -1.204085188556254, -1.2054649430565123,
      -1.2067826542060769, -1.2080390618075845, -1.2092349155427917,
      -1.2103709747541029, -1.2114480082230386, -1.212466793945719,
      -1.2134281189054086, -1.2143327788421767, -1.2151815780197386,
      -1.2159753289895474, -1.2167148523521663, -1.2174009765160174,
      -1.2180345374535526, -1.218616378454906, -1.2191473498791072,
      -1.219628308902907, -1.22006011926729, -1.2204436510217405,
      -1.2207797802663263, -1.2210693888916755, -1.2213133643169032,
      -1.2215125992255813, -1.2216679912997976, -1.221780442952396,
      -1.2218508610574565, -1.221880156679102, -1.2218692447986945,
      -1.2218190440405003, -1.2217304763959036, -1.2216044669462403,
      -1.2214419435843276, -1.2212438367347722, -1.2210110790731314,
      -1.2207446052440072, -1.2204453515781513, -1.2201142558086608,
      -1.219752256786351, -1.2193602941943711, -1.2189393082621618,
      -1.2184902394788224, -1.2180140283059757, -1.2175116148902148,
      -1.2169839387752026, -1.2164319386135274, -1.2158565518783746,
      -1.2152587145751155, -1.214639360952888, -1.2139994232162545,
      -1.2133398312370218, -1.2126615122663114, -1.2119653906469512,
      -1.2112523875262897, -1.210523420569507, -1.2097794036735081,
      -1.2090212466814836, -1.2082498550982266, -1.2074661298062843,
      -1.206670966783032, -1.2058652568187507, -1.2050498852357994,
      -1.2042257316089577, -1.203393669487032, -1.2025545661157953,
      -1.2017092821623623, -1.2008586714410696, -1.2000035806409484,
      -1.1991448490548684, -1.1982833083104509, -1.1974197821028096,
      -1.1965550859292196, -1.1956900268257886, -1.194825403106214,
      -1.1939620041026995, -1.1931006099091246, -1.1922419911265338,
      -1.1913869086110285, -1.1905361132241483, -1.1896903455858034,
      -1.1888503358298532, -1.188016803362397, -1.1871904566228511,
      -1.1863719928479026, -1.1855620978383932, -1.1847614457292268,
      -1.1839706987623657, -1.1831905070629822, -1.1824215084188499,
      -1.181664328063037, -1.1809195784599764, -1.1801878590949773,
      -1.1794697562672507, -1.178765842886518, -1.1780766782732621,
      -1.1774028079626959, -1.1767447635125039, -1.1761030623144293,
      -1.175478207409768, -1.1748706873088151, -1.1742809758143593,
      -1.1737095318492476, -1.1731567992880996, -1.1726232067932298,
      -1.1721091676548208, -1.171615079635421, -1.1711413248188003,
      -1.1706882694632328, -1.1702562638592577, -1.16984564219195,
      -1.1694567224077834, -1.1690898060860924, -1.1687451783152238,
      -1.168423107573384, -1.1681238456142571, -1.1678476273574128,
      -1.1675946707835667, -1.1673651768347106, -1.1671593293191773,
      -1.166977294821653, -1.1668192226181904, -1.1666852445962497,
      -1.1665754751798032, -1.1664900112595318, -1.166428932128148,
      -1.1663922994208791, -1.1663801570611196, -1.1663925312113017,
      -1.1664294302289955, -1.1664908446282622, -1.1665767470462898,
      -1.1666870922153185, -1.1668218169398907, -1.1669808400794293,
      -1.1671640625361621, -1.1673713672484176, -1.167602619189287,
      -1.1678576653706798, -1.1681363348527669, -1.1684384387588402,
      -1.1687637702955653, -1.1691121047786659, -1.1694831996640125,
      -1.1698767945841404, -1.1702926113901788, -1.1707303541992067,
      -1.1711897094470181, -1.1716703459462947, -1.1721719149501943,
      -1.1726940502213181, -1.1732363681060825, -1.1737984676144539,
      -1.1743799305050528, -1.1749803213756032, -1.1755991877587182,
      -1.1762360602230002, -1.17689045247944, -1.1775618614930858,
      -1.1782497675999788, -1.1789536346293088, -1.1796729100307781,
      -1.1804070250071514, -1.181155394651948, -1.1819174180922607,
      -1.1826924786366635, -1.183479943928176, -1.1842791661022509,
      -1.1850894819497515, -1.1859102130848729, -1.1867406661179838,
      -1.1875801328333286, -1.1884278903715679, -1.1892832014170993,
      -1.1901453143901226, -1.1910134636433991, -1.1918868696636595,
      -1.1927647392776102, -1.1936462658624902, -1.1945306295611209,
      -1.1954169975014077, -1.1963045240202193, -1.1971923508916187,
      -1.19807960755935, -1.1989654113735628, -1.199848867831681,
      -1.2007290708233822, -1.2016051028796013, -1.2024760354255146,
      -1.2033409290374286, -1.2041988337035092, -1.2050487890882904,
      -1.2058898248008829, -1.2067209606668252, -1.2075412070034972,
      -1.2083495648990332, -1.2091450264946526, -1.2099265752703403,
      -1.2106931863338004, -1.21144382671261, -1.2121774556494864,
      -1.2128930249006054, -1.2135894790368771, -1.2142657557481065,
      -1.214920786149958, -1.2155534950936426, -1.21616280147824,
      -1.216747618565575, -1.2173068542975731, -1.2178394116159927,
      -1.2183441887844575, -1.21882007971271, -1.2192659742829852,
      -1.219680758678416, -1.220063315713404, -1.2204125251658313,
      -1.2207272641110543, -1.2210064072575701, -1.2212488272842745,
      -1.2214533951792077, -1.2216189805797129, -1.2217444521139,
      -1.221828677743322, -1.2218705251067834, -1.2218688618651694,
      -1.2218225560472149, -1.2217304763961039, -1.2215914927168239,
      -1.2214044762241598, -1.2211682998912381, -1.2208818387985358,
      -1.2205439704832395, -1.220153575288867, -1.2197095367150603,
      -1.2192107417674425, -1.2186560813074436, -1.2180444504020045,
      -1.217374748673054, -1.2166458806466662, -1.2158567561017983,
      -1.2150062904185113, -1.2140934049255816, -1.2131170272473963,
      -1.212076091650043, -1.2109695393864952, -1.2097963190407965,
      -1.2085553868711381, -1.2072457071517551, -1.2058662525135175,
      -1.2044160042831407, -1.2028939528209104, -1.2012990978568288,
      -1.1996304488250862, -1.1978870251967659, -1.1960678568106815,
      -1.19417198420226, -1.1921984589303773, -1.1901463439020441,
      -1.188014713694858, -1.1858026548771317, -1.1835092663255966,
      -1.1811336595405988, -1.1786749589586949, -1.1761323022625574,
      -1.1735048406881046, -1.1707917393287579, -1.1679921774367508,
      -1.1651053487213945, -1.1621304616442176, -1.159066739710892,
      -1.1559134217598668, -1.1526697622476174, -1.1493350315304383,
      -1.1459085161426861, -1.1423895190714024, -1.1387773600272273,
      -1.1350713757115387, -1.1312709200797186, -1.1273753646004891,
      -1.1233840985112311, -1.1192965290692163, -1.115112081798673,
      -1.1108302007336213, -1.1064503486563959, -1.1019720073317973,
      -1.0973946777367927, -1.0927178802857009, -1.0879411550508031,
      -1.0830640619782956, -1.0780861810995412, -1.0730071127375396,
      -1.0678264777085609, -1.0625439175188864, -1.05715909455659,
      -1.0516716922783016, -1.046081415390905, -1.0403879900281046,
      -1.034591163921817, -1.0286907065683202, -1.0226864093891281,
      -1.0165780858865259, -1.0103655717937225, -1.0040487252195804,
      -0.99762742678785865, -0.99110157977095, -0.98447111021804945,
      -0.977735967077725, -0.97089612231484257, -0.96395157102181528,
      -0.95690233152413617, -0.94974844548016246, -0.94248997797510847,
      -0.93512701760923267, -0.92765967658017379, -0.92008809075941123,
      -0.91241241976282916, -0.90463284701534985, -0.896749579809615,
      -0.88876284935870242, -0.880672910842839, -0.87248004345010688,
      -0.86418455041112063, -0.85578675902765855, -0.84728702069522721,
      -0.838685710919568, -0.82998322932706725, -0.82117999966908251,
      -0.81227646982017032, -0.80327311177019711, -0.79417042161035634,
      -0.78496891951306158, -0.77566914970573464, -0.76627168043847382,
      -0.75677710394561737, -0.74718603640119963, -0.73749911786830957,
      -0.727717012242349, -0.71784040718821451, -0.70787001407140371,
      -0.69780656788305961, -0.68765082715896653, -0.67740357389252015,
      -0.66706561344167137, -0.65663777442989357, -0.6461209086411529,
      -0.63551589090894023, -0.62482361899936711, -0.61404501348836282,
      -0.60318101763298271, -0.59223259723688026, -0.58120074050995008,
      -0.57008645792218815, -0.55889078205179676, -0.54761476742756576,
      -0.53625949036557286, -0.52482604880023609, -0.51331556210976514,
      -0.50172917093603309, -0.49006803699893403, -0.47833334290526014,
      -0.4665262919521409, -0.45464810792508603, -0.44270003489070237,
      -0.43068333698410666, -0.41859929819110425, -0.40644922212517687,
      -0.39423443179933437, -0.38195626939288974, -0.36961609601321221,
      -0.3572152914525063, -0.34475525393969148, -0.33223739988743528,
      -0.3196631636344, -0.30703399718276264, -0.29435136993108652,
      -0.28161676840259009, -0.26883169596889994, -0.25599767256934058,
      -0.24311623442582717, -0.23018893375345587, -0.217217338466829,
      -0.20420303188221967, -0.19114761241562114, -0.17805269327677298,
      -0.16491990215923805, -0.15175088092660483, -0.13854728529487867,
      -0.12531078451116875, -0.11204306102872783, -0.098745810178432508,
      -0.085420739836785359, -0.072069570090522117, -0.058694032897902086,
      -0.0452958717467781, -0.031876841309515278, -0.018438707094846716,
      -0.004983245096772046, 0.0084877585594397634, 0.021972507974047508,
      0.035469197832331351, 0.048976013766719062, 0.06249113272143017,
      0.076012723319560868, 0.089538946232530447, 0.1030679545517597,
      0.11659789416253566, 0.13012690411992583, 0.14365311702669242,
      0.15717465941307002, 0.17068965211834639, 0.18419621067412556,
      0.19769244568920741, 0.21117646323595252, 0.22464636523807088,
      0.23810024985970957, 0.25153621189577025, 0.26495234316333294,
      0.27834673289411294, 0.29171746812783, 0.3050626341064207,
      0.31838031466897027, 0.33166859264728188, 0.34492555026197369,
      0.3581492695190282, 0.3713378326066652, 0.38448932229246779,
      0.3976018223206419, 0.41067341780933003, 0.42370219564787237,
      0.436686244893914, 0.44962365717026753, 0.46251252706142743,
      0.47535095250965081, 0.48813703521049467, 0.5008688810077091,
      0.51354460028740945, 0.52616230837141975, 0.53872012590967755,
      0.55121617927163291, 0.56364860093652158, 0.57601552988243032,
      0.58831511197405439, 0.6005455003490584, 0.61270485580293288,
      0.624791347172278, 0.63680315171639146, 0.64873845549709419,
      0.66059545375668216, 0.6723723512939348, 0.68406736283805769,
      0.69567871342051146, 0.70720463874458861, 0.71864338555269691,
      0.72999321199122913, 0.7412523879729408, 0.75241919553675762,
      0.76349192920490749, 0.77446889633731919, 0.785348417483179,
      0.7961288267295682, 0.80680847204710626, 0.81738571563251661,
      0.82785893424802182, 0.83822651955749872, 0.84848687845931825,
      0.85863843341577839, 0.86867962277906352, 0.87860890111365164,
      0.88842473951508849, 0.89812562592506351, 0.90771006544271138,
      0.91717658063205521, 0.92652371182554116, 0.93575001742358066,
      0.94485407419003042, 0.95383447754354855, 0.96268984184475792,
      0.97141880067915276, 0.98002000713567849, 0.9884921340809284,
      0.99683387442888827, 1.0050439414061767, 1.0131210688127159,
      1.0210640112777745, 1.0288715445113235, 1.036542465550661,
      1.0440755930022292, 1.0514697672786033, 1.0587238508305608,
      1.0658367283742094, 1.0728073071131248, 1.0796345169554209,
      1.086317310725748, 1.0928546643721311, 1.0992455771676477,
      1.1054890719068542, 1.1115841950969734, 1.1175300171437479,
      1.1233256325319758, 1.1289701600006434, 1.134462742712651,
      1.1398025484190843, 1.1449887696180094, 1.1500206237077404,
      1.1548973531345728, 1.1596182255349368, 1.1641825338719543,
      1.1685895965663731, 1.1728387576218464, 1.17692938674454,
      1.1808608794570552, 1.1846326572066275, 1.1882441674676059,
      1.1916948838381782, 1.1949843061313323, 1.1981119604600532,
      1.2010773993167136, 1.2038802016466874, 1.2065199729161327,
      1.2089963451739787, 1.2113089771080732, 1.21345755409552,
      1.2154417882471709, 1.217261418446296, 1.2189162103814155,
      1.2204059565733003, 1.2217304763961461, 1.222889616092923,
      1.223883248784899, 1.2247112744753583, 1.2253736200475061,
      1.2258702392565888, 1.2262011127162227, 1.2263662478789537,
      1.2263656790110562, 1.2261994671616003, 1.2258677001257781,
      1.2253704924025381, 1.2247079851465232, 1.2238803461143437,
      1.2228877696052076, 1.2217304763959276, 1.2204087136703394,
      1.2189227549431376, 1.2172728999781881, 1.2154594747013061,
      1.2134828311075747, 1.2113433471631958, 1.2090414267019287,
      1.2065774993161498, 1.203952020242552, 1.2011654702425512,
      1.1982183554773973, 1.1951112073780692, 1.1918445825099626,
      1.1884190624324338, 1.1848352535532292, 1.1810937869778479,
      1.1771953183538861, 1.1731405277104048, 1.1689301192923722,
      1.1645648213902204, 1.1600453861645803, 1.1553725894662314,
      1.1505472306513296, 1.1455701323919514, 1.1404421404820246,
      1.1351641236386898, 1.129736973299152, 1.1241616034130706,
      1.1184389502305676, 1.112569972085879, 1.1065556491767465,
      1.1003969833395739, 1.0940949978204382, 1.087650737041999,
      1.0810652663663822, 1.0743396718540872, 1.0674750600189977,
      1.0604725575795511, 1.0533333112061343, 1.0460584872647816,
      1.0386492715572246, 1.0311068690573784, 1.0234325036443326,
      1.0156274178319029, 1.0076928724948246, 0.99963014659166627,
      0.99144053688451128, 0.98312535765550768, 0.97468594042033829,
      0.96612363363868925, 0.9574398024218026, 0.94863582823717352,
      0.93971310861046453, 0.93067305682473034, 0.92151710161701073,
      0.91224668687237931, 0.90286327131551158, 0.89336832819986978,
      0.88376334499455733, 0.87404982306894685, 0.86422927737512978,
      0.85430323612829506, 0.84427324048509766, 0.834140844220097,
      0.823907613400356, 0.81357512605826376, 0.80314497186267042,
      0.792618751788416, 0.78199807778433372, 0.77128457243978676,
      0.7604798686498534, 0.749585609279216, 0.73860344682483792,
      0.7275350430775096, 0.71638206878235489, 0.70514620329835576,
      0.69382913425700155, 0.68243255722011487, 0.67095817533696089,
      0.659407699000701, 0.64778284550428566, 0.63608533869584316,
      0.62431690863367462, 0.61247929124091294, 0.60057422795993187,
      0.588603465406575, 0.57656875502431149, 0.56447185273835332,
      0.55231451860986136, 0.54009851649027507, 0.52782561367586756,
      0.51549758056260464, 0.50311619030136989, 0.49068321845364765,
      0.47820044264773143, 0.46566964223553237, 0.4530925979500719,
      0.44047109156373576, 0.42780690554733397, 0.41510182273009982,
      0.4023576259606319, 0.38957609776890584, 0.37675902002940692,
      0.36390817362546035, 0.35102533811481745, 0.33811229139659937,
      0.32517080937962706, 0.31220266565226235, 0.29920963115375554,
      0.28619347384725319, 0.27315595839445583, 0.26009884583205689,
      0.24702389324998136, 0.23393285347152046, 0.22082747473541467,
      0.20770950037994915, 0.19458066852914341, 0.18144271178106172,
      0.16829735689834449, 0.15514632450100568, 0.14199132876155818,
      0.1288340771025196, 0.11567626989637679, 0.10251960016805073,
      0.089365753299932613, 0.076216406739524317, 0.063073229709775608,
      0.049937882922142518, 0.03681201829243496, 0.023697278659507118,
      0.010595297506831726, -0.0024923013129703533, -0.015563903850603893,
      -0.028617906329551426, -0.041652715412399614, -0.05466674846404232,
      -0.067658433811694341, -0.080626211001660952, -0.093568531052833914,
      -0.10648385670686629, -0.1193706626749676, -0.13222743588129293,
      -0.14505267570289787, -0.15784489420617231, -0.17060261637976454,
      -0.18332438036392851, -0.19600873767626389, -0.20865425343381394,
      -0.22125950657148943, -0.23382309005676222, -0.24634361110064323,
      -0.25881969136485533, -0.271249967165205, -0.28363308967111567,
      -0.29596772510129721, -0.30825255491550341, -0.32048627600238305,
      -0.332667600863358, -0.34479525779255615, -0.35686799105271633,
      -0.36888456104708761, -0.38084374448727409, -0.39274433455702512,
      -0.40458514107192589, -0.41636499063500509, -0.42808272678818843,
      -0.43973721015965561, -0.45132731860700281, -0.46285194735626378,
      -0.47431000913673033, -0.48570043431159393, -0.49702217100436891,
      -0.50827418522109458, -0.5194554609683314, -0.53056500036689347,
      -0.54160182376136079, -0.55256496982533376, -0.5634534956624323,
      -0.57426647690302912, -0.58500300779674153, -0.59566220130063341,
      -0.60624318916316655, -0.616745122003871, -0.62716716938877637,
      -0.63750851990153867, -0.64776838121034186, -0.6579459801305142,
      -0.66804056268290435, -0.67805139414800186, -0.68797775911581882,
      -0.6978189615315249, -0.7075743247368792, -0.71724319150741445,
      -0.72682492408543209, -0.73631890420879043, -0.74572453313551468,
      -0.75504123166423065, -0.764268440150434, -0.77340561851862577,
      -0.7824522462703084, -0.79140782248787467, -0.80027186583439969,
      -0.80904391454935454, -0.81772352644025992, -0.8263102788702994,
      -0.83480376874191953, -0.84320361247642361, -0.85150944598959211,
      -0.85972092466336136, -0.86783772331355258, -0.8758595361537117,
      -0.88378607675506682, -0.89161707800262413, -0.89935229204744249,
      -0.90699149025511416, -0.914534463150454, -0.92198102035847018,
      -0.92933099054160373, -0.93658422133328911, -0.94374057926786525,
      -0.95079994970686221, -0.957762236761697, -0.96462736321281706,
      -0.97139527042532225, -0.9780659182610858, -0.98463928498743369,
      -0.99111536718240423, -0.99749417963661324, -1.0037757552517794,
      -1.009960144935943, -1.0160474174953988, -1.0220376595234106,
      -1.0279309752857106, -1.0337274866028587, -1.0394273327294687,
      -1.0450306702303676, -1.050537672853707, -1.0559485314010859,
      -1.0612634535947068, -1.0664826639416325, -1.0716064035951525,
      -1.0766349302133391, -1.0815685178147969, -1.0864074566316866,
      -1.0911520529600323, -1.0958026290073895, -1.1003595227378866,
      -1.1048230877147074, -1.1091936929400519, -1.1134717226926159,
      -1.1176575763626397, -1.121751668284579, -1.1257544275674261,
      -1.1296662979227414, -1.1334877374904446, -1.1372192186623979,
      -1.1408612279038408, -1.1444142655727172, -1.147878845736948,
      -1.1512554959896897, -1.1545447572626344, -1.1577471836373889,
      -1.1608633421549954, -1.1638938126236216, -1.1668391874244963,
      -1.1697000713161083, -1.1724770812367422, -1.1751708461053845,
      -1.1777820066210558, -1.1803112150606079, -1.1827591350750597,
      -1.1851264414844831, -1.1874138200715196, -1.1896219673735657,
      -1.1917515904736629, -1.1938034067901664, -1.1957781438652237,
      -1.1976765391521125, -1.1994993398014908, -1.2012473024466139,
      -1.2029211929875512, -1.2045217863744686, -1.2060498663900074,
      -1.2075062254308284, -1.2088916642883509, -1.2102069919287437,
      -1.2114530252722158, -1.2126305889716535, -1.2137405151906524,
      -1.2147836433809889, -1.2157608200595815, -1.2166728985849926,
      -1.21752073893351, -1.2183052074748604, -1.2190271767475944,
      -1.219687525234209, -1.2202871371360284, -1.2208269021478992,
      -1.2213077152327598, -1.2217304763961052, -1.2220960904604126,
      -1.2224054668395585, -1.2226595193132852, -1.2228591658017474,
      -1.2230053281401991, -1.2230989318538474, -1.2231409059329328,
      -1.2231321826080648, -1.223073697125872, -1.2229663875249948,
      -1.2228111944124695, -1.2226090607405513, -1.2223609315840029,
      -1.2220677539179086, -1.221730476396043, -1.2213500491298372,
      -1.2209274234679821, -1.2204635517767164, -1.2199593872208332,
      -1.2194158835454358, -1.2188339948585005, -1.2182146754142738,
      -1.2175588793975349, -1.2168675607087842, -1.2161416727503684,
      -1.2153821682135972, -1.2145899988668858, -1.2137661153449506,
      -1.2129114669391001, -1.2120270013886676, -1.2111136646735905,
      -1.2101724008082029, -1.209204151636261, -1.208209856627233,
      -1.2071904526738872, -1.2061468738912231, -1.2050800514167619,
      -1.2039909132122355, -1.2028803838667084, -1.2017493844011613,
      -1.2005988320745575, -1.199429640191447, -1.1982427179111053,
      -1.197038970058264, -1.1958192969354482, -1.1945845941369504,
      -1.1933357523644725, -1.1920736572444603, -1.1907991891471603,
      -1.1895132230074197, -1.1882166281472639, -1.1869102681002714,
      -1.1855950004377711, -1.1842716765968904, -1.1829411417104749,
      -1.18160423443891, -1.1802617868038512, -1.1789146240239106,
      -1.1775635643522977, -1.176209418916458, -1.1748529915597092,
      -1.1734950786849174, -1.1721364691002172, -1.1707779438668022,
      -1.1694202761488113, -1.168064231065316, -1.166710565544443,
      -1.1653600281796377, -1.1640133590880932, -1.1626712897713622,
      -1.1613345429781614, -1.1600038325693991, -1.1586798633854232,
      -1.1573633311155249, -1.1560549221696903, -1.1547553135526436,
      -1.1534651727401637, -1.1521851575577167, -1.1509159160613969,
      -1.1496580864211983, -1.148412296806631, -1.1471791652746874,
      -1.1459592996601748, -1.1447532974684218, -1.1435617457703735,
      -1.1423852211000849, -1.1412242893546123, -1.1400795056963315,
      -1.1389514144576685, -1.137840549048275, -1.1367474318646349,
      -1.1356725742021254, -1.1346164761695279, -1.1335796266060063,
      -1.1325625030005506, -1.1315655714138981, -1.1305892864029317,
      -1.1296340909475617, -1.1287004163801027, -1.12778868231714,
      -1.1268992965938966, -1.1260326552010973, -1.1251891422243461,
      -1.1243691297859992, -1.1235729779895569, -1.1228010348665607,
      -1.1220536363260087, -1.1213311061062825, -1.1206337557295889,
      -1.1199618844589136, -1.1193157792574995, -1.11869571475083,
      -1.1181019531911329, -1.1175347444243984, -1.1169943258599011,
      -1.1164809224422403, -1.1159947466258873, -1.1155359983522326,
      -1.1151048650291397, -1.1147015215130041, -1.1143261300932927,
      -1.1139788404795927, -1.1136597897911358, -1.1133691025488111,
      -1.1131068906696575, -1.1128732534638279, -1.1126682776340147,
      -1.1124920372773479, -1.1123445938897436, -1.1122259963726986,
      -1.1121362810425361, -1.1120754716420709, -1.1120435793547225,
      -1.11204060282103, -1.112066528157589, -1.11212132897839,
      -1.1122049664185498, -1.1123173891604268, -1.1124585334621195,
      -1.1126283231883245, -1.1128266698435569, -1.1130534726077119,
      -1.1133086183739727, -1.1135919817890272, -1.1139034252956188,
      -1.1142427991773858, -1.1146099416060002, -1.1150046786905836,
      -1.1154268245293906, -1.1158761812637503, -1.116352539134245,
      -1.1168556765391253, -1.1173853600949368, -1.1179413446993507,
      -1.1185233735961893, -1.1191311784426172, -1.1197644793784993,
      -1.1204229850979066, -1.1211063929227529, -1.1218143888785417,
      -1.1225466477722303, -1.1233028332721608, -1.1240825979900766,
      -1.1248855835651843, -1.1257114207502605, -1.1265597294997736,
      -1.1274301190600204, -1.1283221880612311, -1.1292355246116752,
      -1.1301697063936893, -1.1311243007616663, -1.1320988648419472,
      -1.1330929456346153, -1.1341060801171758, -1.1351377953501027,
      -1.1361876085842098, -1.1372550273698743, -1.1383395496680497,
      -1.139440663963063, -1.1405578493771902, -1.1416905757869706,
      -1.1428383039412535, -1.1440004855809423, -1.1451765635604407,
      -1.1463659719707464, -1.1475681362642012, -1.1487824733808638,
      -1.1500083918764756, -1.15124529205202, -1.1524925660848324,
      -1.1537495981612456, -1.1550157646107566, -1.1562904340416811,
      -1.1575729674782806, -1.158862718499335, -1.1601590333781346,
      -1.1614612512238871, -1.1627687041244863, -1.164080717290648,
      -1.1653966092013641, -1.1667156917506805, -1.1680372703957356,
      -1.1693606443060809, -1.1706851065142141, -1.1720099440673359,
      -1.173334438180291, -1.1746578643896584, -1.1759794927089864,
      -1.1772985877851305, -1.1786144090556796, -1.17992621090744,
      -1.18123324283595, -1.1825347496059946, -1.1838299714131133,
      -1.1851181440460561, -1.1863984990501582, -1.1876702638916283,
      -1.1889326621227081, -1.1901849135476661, -1.1914262343896289,
      -1.1926558374581937, -1.1938729323178063, -1.1950767254568881,
      -1.1962664204576483, -1.1974412181666099, -1.198600316865758,
      -1.1997429124443368, -1.2008681985712319, -1.2019753668679241,
      -1.2030636070819889, -1.2041321072610927, -1.2051800539274911,
      -1.2062066322529612, -1.2072110262341733, -1.208192418868453,
      -1.2091499923299058, -1.2100829281458805, -1.21099040737374,
      -1.2118716107779075, -1.2127257190071592, -1.2135519127721375,
      -1.2143493730230512, -1.2151172811275246, -1.2158548190485832,
      -1.2165611695227312, -1.217235516238093, -1.2178770440125986,
      -1.218484938972157, -1.2190583887288211, -1.2195965825588884,
      -1.2200987115809068, -1.2205639689335774, -1.2209915499534931,
      -1.2213806523527002, -1.2217304763960521, -1.2220402250783158,
      -1.2223091043010044, -1.2225363230489024, -1.2227210935662594,
      -1.2228626315326006, -1.2229601562381542, -1.2230128907588389,
      -1.2230200621307779, -1.2229809015243409, -1.2228946444176394,
      -1.2227605307694629, -1.2225778051916438, -1.2223457171207812,
      -1.2220635209893178, -1.2217304763959347, -1.221345848275224,
      -1.2209089070666135, -1.2204189288825145, -1.2198751956756528,
      -1.2192769954055578, -1.2186236222041811, -1.2179143765405929,
      -1.2171485653847565, -1.2163255023703254, -1.2154445079564347,
      -1.2145049095884641, -1.2135060418577401, -1.2124472466601326,
      -1.2113278733535238, -1.2101472789141328, -1.2089048280916344,
      -1.2075998935630639, -1.2062318560854755, -1.204800104647304,
      -1.2033040366184213, -1.2017430578988593, -1.2001165830661353,
      -1.1984240355211855, -1.1966648476328718, -1.1948384608809997,
      -1.1929443259978607, -1.1909819031082391, -1.1889506618678674,
      -1.18685008160029, -1.1846796514321254, -1.1824388704266666,
      -1.1801272477158229, -1.1777443026303525, -1.1752895648283648,
      -1.1727625744220731, -1.1701628821027361, -1.1674900492638092,
      -1.1647436481222377, -1.161923261837879, -1.1590284846310288,
      -1.156058921898024, -1.1530141903248776, -1.1498939179989507,
      -1.1466977445186068, -1.1434253211008358, -1.1400763106868177,
      -1.1366503880454042, -1.1331472398744811, -1.1295665649002053,
      -1.1259080739740768, -1.1221714901678177, -1.1183565488660598,
      -1.1144629978567753, -1.1104905974194685, -1.1064391204110788,
      -1.1023083523495767, -1.0980980914952418, -1.0938081489295872,
      -1.0894383486319104, -1.0849885275534559, -1.0804585356891607,
      -1.0758482361469692, -1.0711575052146951, -1.0663862324243931,
      -1.0615343206142551, -1.0566016859879794, -1.0515882581716109,
      -1.0464939802678288, -1.0413188089076695, -1.0360627142996495,
      -1.0307256802763018, -1.0253077043380712, -1.019808797694586,
      -1.014228985303272, -1.0085683059053014, -1.0028268120588451,
      -0.9970045701696395, -0.991101660518839, -0.98511817728813855,
      -0.97905422858215718, -0.97290993644807933, -0.9666854368925154,
      -0.96038087989560628, -0.95399642942233076, -0.94753226343101982,
      -0.940988573879062, -0.9343655667258044, -0.927663461932611,
      -0.9208824934601012, -0.91402290926254515, -0.90708497127941023,
      -0.90006895542405219, -0.89297515156955276, -0.88580386353167817,
      -0.87855540904897744, -0.87123011976000764, -0.86382834117766383,
      -0.856350432660645, -0.84879676738202992, -0.84116773229495589,
      -0.83346372809542335, -0.82568516918220392, -0.81783248361385774,
      -0.8099061130628723, -0.8019065127668985, -0.79383415147710934,
      -0.78568951140367538, -0.77747308815835725, -0.76918539069421776,
      -0.76082694124247219, -0.7523982752464492, -0.743899941292709,
      -0.73533250103930126, -0.72669652914115679, -0.71799261317265561,
      -0.709221353547354, -0.70038336343488117, -0.69147926867502163,
      -0.68250970768899177, -0.67347533138792, -0.66437680307854774,
      -0.65521479836614271, -0.64599000505466331, -0.63670312304417376,
      -0.62735486422553011, -0.61794595237233529, -0.60847712303020729,
      -0.5989491234033415, -0.58936271223842607, -0.57971865970587522,
      -0.57001774727844856, -0.560260767607245, -0.55044852439510528,
      -0.54058183226741907, -0.5306615166403954, -0.520688413586784,
      -0.51066336969908388, -0.50058724195027016, -0.49046089755203143,
      -0.48028521381058104, -0.470061077980036, -0.45978938711340894,
      -0.44947104791122078, -0.43910697656778014, -0.42869809861513214,
      -0.41824534876474045, -0.40774967074687657, -0.39721201714781051,
      -0.38663334924477372, -0.37601463683876812, -0.36535685808521867,
      -0.35466099932252537, -0.34392805489853023, -0.33315902699495287,
      -0.32235492544978894, -0.31151676757775237, -0.3006455779887599,
      -0.28974238840451316, -0.27880823747320232, -0.2678441705823712,
      -0.25685123966998774, -0.24583050303373888, -0.23478302513860916,
      -0.22370987642276172, -0.21261213310177629, -0.20149087697127618,
      -0.19034719520797927, -0.17918218016922705, -0.16799692919101622,
      -0.15679254438458706, -0.14557013243160677, -0.13433080437797862,
      -0.12307567542634604, -0.11180586472730789, -0.1005224951693986,
      -0.089226693167888019, -0.07791958845242411, -0.066602313853582479,
      -0.055276005088366456, -0.043941800544679055, -0.032600841064850644,
      -0.021254269728243656, -0.0099032316329889757, 0.0014511263231013136,
      0.012807655662394224, 0.024165206548019784, 0.0355226280051392,
      0.046878768142823518, 0.058232474376542734, 0.0695825936511559,
      0.080927972664393888, 0.092267458090773677, 0.10359989680589232,
      0.11492413611104721, 0.12623902395813841, 0.13754340917479066,
      0.14883614168967235, 0.16011607275791848, 0.17138205518663335,
      0.18263294356042431, 0.19386759446689461, 0.20508486672205364,
      0.21628362159560668, 0.22746272303603271, 0.23862103789545555,
      0.24975743615419035, 0.26087079114496581, 0.27195997977674063,
      0.28302388275807122, 0.29406138481997668, 0.30507137493823872,
      0.31605274655510868, 0.32700439780033591, 0.33792523171148259,
      0.34881415645348157, 0.35967008553735869, 0.37049193803808478,
      0.38127863881150237, 0.39202911871026835, 0.40274231479876094,
      0.4134171705669103, 0.42405263614288391, 0.43464766850457121,
      0.44520123168984749, 0.45571229700551985, 0.4661798432349471,
      0.4766028568442281, 0.48698033218697989, 0.49731127170758249,
      0.50759468614288783, 0.51782959472230439, 0.52801502536625866,
      0.53815001488291925, 0.5482336091631862, 0.55826486337386361,
      0.56824284214898713, 0.57816661977923411, 0.58803528039940423,
      0.597847918173865, 0.60760363747998769, 0.61730155308945323,
      0.62694079034743466, 0.63652048534957439, 0.64603978511673776,
      0.65549784776747411, 0.66489384268814444, 0.67422695070069549,
      0.68349636422798921, 0.692701287456683, 0.701840936497611,
      0.7109145395435994, 0.71992133702469729, 0.72886058176077906,
      0.73773153911146139, 0.74653348712331435, 0.75526571667429965,
      0.76392753161544, 0.77251824890962217, 0.78103719876755362,
      0.78948372478078843, 0.7978571840518156, 0.80615694732115684,
      0.81438239909145116, 0.82253293774847092, 0.830607975679067,
      0.83860693938596942, 0.84652926959944941, 0.854374421385775,
      0.862141864252467, 0.8698310822502886, 0.87744157407195611,
      0.88497285314754781, 0.89242444773656138, 0.89979590101662243,
      0.90708677116878633, 0.91429663145943074, 0.92142507031869014,
      0.928471691415444, 0.93543611372879976, 0.94231797161606456,
      0.94911691487717476, 0.95583260881558785, 0.96246473429558177,
      0.96901298779596212, 0.97547708146016021, 0.98185674314270011,
      0.98815171645200706, 0.99436176078958427, 1.0004866513854684,
      1.0065261793300384, 1.0124801516020927, 1.0183483910932265,
      1.0241307366284733, 1.029827042983225, 1.0354371808963989,
      1.0409610370798474, 1.046398514224034, 1.05174953099992,
      1.0570140220570883, 1.0621919380181102, 1.0672832454691155,
      1.0722879269465988, 1.0772059809204433, 1.0820374217731668,
      1.0867822797753974, 1.0914406010575528, 1.0960124475777864,
      1.1004978970861212, 1.1048970430848615, 1.1092099947852203,
      1.1134368770602181, 1.1175778303938217, 1.121633010826375,
      1.12560258989628, 1.1294867545780012, 1.1332857072163436,
      1.1369996654570715, 1.1406288621738254, 1.1441735453914257,
      1.1476339782055074, 1.1510104386985403, 1.1543032198522614,
      1.1575126294564977, 1.1606389900144596, 1.1636826386444634,
      1.1666439269781583, 1.1695232210552287, 1.1723209012146734,
      1.1750373619825802, 1.177673011956526, 1.1802282736865723,
      1.182703583552879, 1.1850993916400097, 1.1874161616079231,
      1.1896543705596745, 1.1918145089059071, 1.1938970802261029,
      1.1959026011266793, 1.1978316010959418, 1.1996846223559323,
      1.2014622197111995, 1.2031649603945638, 1.204793423909857,
      1.2063482018717386, 1.2078298978425954, 1.2092391271665506,
      1.2105765168006646, 1.2118427051433458, 1.2130383418600066,
      1.214164087706036, 1.2152206143471007, 1.2162086041768747,
      1.21712875013215, 1.2179817555054986, 1.218768333755416,
      1.2194892083140834, 1.2201451123927511, 1.2207367887848055,
      1.2212649896665693, 1.2217304763959038, 1.2221340193086296,
      1.2224763975128579, 1.2227583986812685, 1.2229808188413709,
      1.2231444621638463, 1.2232501407489931, 1.2232986744113297,
      1.2232908904624435, 1.2232276234921198, 1.2231097151477872,
      1.2229380139124084, 1.2227133748807852, 1.222436659534414,
      1.2221087355149118, 1.2217304763960724, 1.221302761454639,
      1.2208264754398259, 1.2203025083416823, 1.2197317551583224,
      1.2191151156621152, 1.2184534941648966, 1.2177477992822365,
      1.2169989436968645, 1.2162078439212913, 1.2153754200596987,
      1.2145025955691673, 1.2135902970202979, 1.2126394538572955,
      1.2116509981575858, 1.2106258643910361, 1.2095649891787978,
      1.2084693110519369, 1.2073397702097912, 1.2061773082782379,
      1.2049828680678596, 1.2037573933321015, 1.2025018285255,
      1.2012171185620302, 1.1999042085736318, 1.1985640436690137,
      1.1971975686927754, 1.1958057279849046, 1.1943894651407523,
      1.1929497227715302, 1.1914874422653838, 1.1900035635491308,
      1.188499024850733, 1.1869747624625371, 1.1854317105053842,
      1.1838708006936367, 1.1822929621011884, 1.1806991209285316,
      1.1790902002709311, 1.1774671198877928, 1.1758307959732635,
      1.1741821409281521, 1.1725220631332152, 1.1708514667238867,
      1.1691712513665093, 1.1674823120361144, 1.16578553879585,
      1.1640818165780771, 1.1623720249672209, 1.1606570379844405,
      1.1589377238741594, 1.157214944892524, 1.1554895570978667,
      1.1537624101432054, 1.1520343470708569, 1.1503062041092142,
      1.1485788104717518, 1.1468529881583016, 1.1451295517586773,
      1.1434093082586809, 1.1416930568485575, 1.1399815887339626,
      1.1382756869494635, 1.1365761261746636, 1.1348836725529812,
      1.1331990835131402, 1.1315231075934191, 1.1298564842687109,
      1.1281999437804511, 1.1265542069694414, 1.1249199851116414,
      1.1232979797569489, 1.1216888825710438, 1.1200933751803155,
      1.1185121290199231, 1.1169458051850443, 1.1153950542853448,
      1.1138605163027064, 1.1123428204522574, 1.1108425850467583,
      1.109360417364351, 1.1078969135197372, 1.1064526583388155,
      1.1050282252367953, 1.1036241760998486, 1.102241061170314,
      1.1008794189354889, 1.0995397760200543, 1.0982226470821341,
      1.0969285347130537, 1.0956579293407955, 1.0944113091371959,
      1.0931891399289033, 1.0919918751121218, 1.0908199555711706,
      1.0896738096008707, 1.0885538528327836, 1.0874604881653367,
      1.0863941056978317, 1.0853550826683678, 1.0843437833956953,
      1.0833605592250122, 1.0824057484777181, 1.0814796764051438,
      1.0805826551462581, 1.0797149836893816, 1.0788769478378895,
      1.0780688201799387, 1.0772908600622151, 1.0765433135676941,
      1.0758264134974536, 1.0751403793565038, 1.0744854173436587,
      1.0738617203454548, 1.0732694679340964, 1.0727088263694411,
      1.0721799486050267, 1.0716829742981167, 1.0712180298237883,
      1.0707852282930217, 1.0703846695748123, 1.0700164403222869,
      1.0696806140028106, 1.0693772509320731, 1.0691063983121583,
      1.0688680902735488, 1.0686623479210966, 1.0684891793839062,
      1.0683485798691235, 1.0682405317196257, 1.0681650044755808,
      1.0681219549398444, 1.0681113272472031, 1.0681330529374087,
      1.0681870510320033, 1.0682732281148901, 1.0683914784166384,
      1.0685416839024959, 1.068723714364052, 1.0689374275145684,
      1.0691826690879005, 1.0694592729410053, 1.0697670611599945,
      1.0701058441696936, 1.0704754208466696, 1.0708755786357138,
      1.0713060936697036, 1.0717667308928378, 1.0722572441871858,
      1.0727773765025126, 1.073326859989354, 1.0739054161352717,
      1.0745127559042598, 1.0751485798792657, 1.075812578407755,
      1.0765044317502999, 1.0772238102321172, 1.0779703743975344,
      1.0787437751673095, 1.0795436539987651, 1.0803696430486864,
      1.0812213653389251, 1.0820984349246541, 1.0830004570652367,
      1.083927028397623, 1.0848777371122371, 1.0858521631313152,
      1.0868498782895926, 1.0878704465173206, 1.0889134240255398,
      1.0899783594935386, 1.0910647942584675, 1.0921722625070007,
      1.0933002914690304, 1.0944484016133071, 1.095616106844957,
      1.0968029147048275, 1.0980083265705936, 1.0992318378595405,
      1.1004729382329936, 1.1017311118022923, 1.1030058373362646,
      1.1042965884701146, 1.105602833915688, 1.1069240376730132,
      1.1082596592430558, 1.1096091538416402, 1.1109719726144458,
      1.1123475628530097, 1.1137353682116737, 1.1151348289254102,
      1.1165453820284232, 1.1179664615735103, 1.1193974988520554,
      1.1208379226146012, 1.1222871592919732, 1.1237446332167931,
      1.1252097668453893, 1.1266819809800042, 1.1281606949912029,
      1.1296453270404514, 1.1311352943027562, 1.1326300131893219,
      1.1341288995701162, 1.1356313689963216, 1.1371368369225396,
      1.138644718928733, 1.1401544309417833, 1.1416653894566282,
      1.1431770117568771, 1.1446887161348676, 1.1461999221110342,
      1.1477100506525859, 1.1492185243913611, 1.1507247678408254,
      1.1522282076121089, 1.1537282726290625, 1.1552243943421892,
      1.1567160069414448, 1.1582025475678064, 1.1596834565235352,
      1.1611581774810884, 1.1626261576905679, 1.1640868481856894,
      1.1655397039881634, 1.1669841843104329, 1.1684197527566984,
      1.1698458775221723, 1.1712620315904896, 1.1726676929291793,
      1.1740623446832057, 1.1754454753664267, 1.1768165790509644,
      1.1781751555544042, 1.1795207106247583, 1.1808527561231277,
      1.1821708102040167, 1.1834743974932203, 1.1847630492632355,
      1.1860363036061332, 1.1872937056038348, 1.1885348074957258,
      1.1897591688435663, 1.1909663566936244, 1.192155945735984,
      1.1933275184609895, 1.194480665312728, 1.1956149848395514,
      1.1967300838415511, 1.1978255775149391, 1.198901089593299,
      1.1999562524856395, 1.2009907074112272, 1.2020041045311058,
      1.2029961030763323, 1.2039663714727902, 1.2049145874626235,
      1.2058404382221852, 1.2067436204764963, 1.2076238406101545,
      1.2084808147746671, 1.209314268992153, 1.2101239392554011,
      1.2109095716242151, 1.211670922318052, 1.2124077578048655,
      1.2131198548862008, 1.2138070007784072, 1.2144689931900412,
      1.2151056403953575, 1.2157167613038851, 1.2163021855260929,
      1.2168617534350423, 1.2173953162240996, 1.2179027359606054,
      1.2183838856355191, 1.2188386492090233, 1.2192669216520278,
      1.2196686089836317, 1.2200436283044205, 1.2203919078256948,
      1.220713386894557, 1.2210080160148098, 1.22127575686377,
      1.2215165823048559, 1.2217304763960328, 1.2219174343940771,
      1.222077462754642, 1.2222105791281512, 1.2223168123514836,
      1.2223962024354884, 1.2224488005482776, 1.2224746689943591,
      1.2224738811895639, 1.2224465216317824, 1.2223926858675538,
      1.2223124804544454, 1.2222060229193019, 1.2220734417123262,
      1.2219148761570127, 1.22173047639598, 1.2215204033326508,
      1.2212848285688676, 1.2210239343383935, 1.2207379134363754,
      1.2204269691447496, 1.2200913151536121, 1.2197311754786155,
      1.2193467843743517, 1.2189383862438001, 1.2185062355438565,
      1.2180505966869248, 1.2175717439386831, 1.2170699613119635,
      1.2165455424568594, 1.215998790547014, 1.2154300181622026,
      1.2148395471671813, 1.2142277085868665, 1.2135948424778888,
      1.2129412977965313, 1.2122674322631315, 1.2115736122229586,
      1.2108602125036059, 1.210127616268988, 1.2093762148699105,
      1.208606407691335, 1.2078186019963386, 1.2070132127668338,
      1.2061906625410941, 1.2053513812481398, 1.2044958060390312,
      1.2036243811151253, 1.2027375575533423, 1.20183579312852,
      1.2009195521328659, 1.19998930519263, 1.1990455290819833,
      1.198088706534219, 1.1971193260503166, 1.1961378817049078,
      1.1951448729497434, 1.1941408044147024, 1.1931261857064028,
      1.1921015312045007, 1.1910673598557107, 1.1900241949656514,
      1.1889725639885458, 1.1879129983148802, 1.1868460330570476,
      1.1857722068330954, 1.184692061548607, 1.1836061421768018,
      1.1825149965369333, 1.1814191750710368, 1.18031923061913,
      1.1792157181929104, 1.1781091947480322, 1.1770002189550515,
      1.1758893509690964, 1.1747771521983423, 1.1736641850713836,
      1.1725510128035459, 1.1714381991622602, 1.1703263082315258,
      1.1692159041755885, 1.1681075510018788, 1.1670018123232977,
      1.1658992511199444, 1.1648004295003327, 1.1637059084622177,
      1.1626162476530641, 1.161532005130294, 1.1604537371213273,
      1.1593819977835553, 1.1583173389643062, 1.1572603099608514,
      1.1562114572805957, 1.1551713244014827, 1.1541404515327065,
      1.1531193753758417, 1.1521086288864189, 1.1511087410360732,
      1.1501202365753342, 1.1491436357971081, 1.1481794543009998,
      1.1472282027584679, 1.1462903866789778, 1.1453665061771712,
      1.1444570557411713, 1.1435625240020741, 1.1426833935047307,
      1.1418201404798927, 1.1409732346177783, 1.1401431388431731,
      1.1393303090921227, 1.1385351940902904, 1.137758235133087,
      1.1369998658675982, 1.1362605120764548, 1.1355405914636474,
      1.1348405134424364, 1.1341606789253624, 1.1335014801164762,
      1.132863300305871, 1.1322465136665285, 1.1316514850536301,
      1.1310785698063541, 1.1305281135522389, 1.1300004520142084,
      1.1294959108202813, 1.129014805316096, 1.1285574403802634,
      1.1281241102426423, 1.1277150983056177, 1.1273306769684002,
      1.1269711074544804, 1.1266366396422309, 1.1263275118987759,
      1.1260439509171662, 1.1257861715569111, 1.1255543766879639,
      1.1253487570381673, 1.1251694910442833, 1.1250167447065986,
      1.1248906714472153, 1.1247914119720515, 1.1247190941366083,
      1.1246738328155936, 1.124655729776378, 1.1246648735564277,
      1.1247013393446958, 1.1247651888670362, 1.1248564702757198,
      1.1249752180430441, 1.1251214528591371, 1.1252951815339647,
      1.1254963969035849, 1.1257250777407193, 1.1259811886696389,
      1.1262646800854494, 1.1265754880777696, 1.1269135343588725,
      1.127278726196314, 1.1276709563500629, 1.1280901030142094,
      1.1285360297632248, 1.1290085855028562, 1.1295076044256511,
      1.130032905971144, 1.1305842947907492, 1.1311615607173404,
      1.1317644787396124, 1.1323928089811466, 1.1330462966843,
      1.1337246721988707, 1.1344276509755677, 1.1351549335643329,
      1.1359062056174778, 1.1366811378976858, 1.1374793862908905,
      1.1383005918239937, 1.1391443806875052, 1.1400103642630308,
      1.1408981391556807, 1.1418072872313572, 1.1427373756589372,
      1.1436879569573692, 1.1446585690476316, 1.1456487353096163,
      1.1466579646438815, 1.147685751538281, 1.1487315761394858,
      1.1497949043293481, 1.1508751878061381, 1.1519718641706047,
      1.1530843570168769, 1.1542120760281724, 1.1553544170773022,
      1.1565107623319564, 1.1576804803647358, 1.1588629262679424,
      1.1600574417730616, 1.1612633553749399, 1.1624799824606447,
      1.163706625442926, 1.1649425738983259, 1.1661871047098296,
      1.167439482214089, 1.168698958353152, 1.1699647728306581,
      1.1712361532725026, 1.1725123153918815, 1.1737924631587129,
      1.1750757889733947, 1.1763614738448283, 1.1776486875727037,
      1.1789365889339636, 1.1802243258734406, 1.1815110356985805,
      1.1827958452782328, 1.1840778712454472, 1.1853562202042263,
      1.186629988940181, 1.1878982646350311, 1.1891601250849173,
      1.1904146389224333, 1.1916608658423551, 1.1928978568309865,
      1.1941246543990687, 1.1953402928182024, 1.1965437983606952,
      1.1977341895427969, 1.1989104773712569, 1.2000716655931065,
      1.2012167509486462, 1.2023447234275342, 1.2034545665279246,
      1.2045452575185827, 1.2056157677038992, 1.2066650626917488,
      1.2076921026641012, 1.2086958426503172, 1.20967523280307,
      1.2106292186767935, 1.2115567415085917, 1.2124567385015403,
      1.2133281431102847, 1.2141698853288752, 1.2149808919807359,
      1.215760087010721, 1.2165063917791379, 1.2172187253576818,
      1.2178960048272003, 1.2185371455771845, 1.2191410616069196,
      1.2197066658282107, 1.2202328703695835, 1.2207185868818966,
      1.2211627268452592, 1.2215642018771793, 1.2219219240418504,
      1.2222348061604889, 1.2225017621226428, 1.22272170719836,
      1.222893558351168, 1.2230162345517244, 1.2230886570920929,
      1.2231097499005332, 1.2230784398567138, 1.2229936571072684,
      1.2228543353815944, 1.2226594123078136, 1.2224078297287884,
      1.2220985340181165, 1.2217304763960162, 1.2213026132449847,
      1.2208139064251695, 1.2202633235893539, 1.21964983849743,
      1.2189724313303385, 1.2182300890033042, 1.217421805478341,
      1.2165465820758941, 1.2156034277855425, 1.2145913595756808,
      1.2135094027020679, 1.212356591015173, 1.2111319672662098,
      1.2098345834117923, 1.208463500917093, 1.2070177910574404,
      1.2054965352182505, 1.2038988251932152, 1.202223763480645,
      1.2004704635778984, 1.198638050273783, 1.1967256599388734,
      1.1947324408136302, 1.1926575532942594, 1.1905001702162021,
      1.1882594771351955, 1.1859346726058011, 1.1835249684573208,
      1.1810295900670327, 1.1784477766306394, 1.1757787814298717,
      1.1730218720971619, 1.1701763308772675, 1.1672414548858596,
      1.1642165563648756, 1.16110096293467, 1.157894017842813,
      1.1545950802094898, 1.1512035252694361, 1.147718744610301,
      1.1441401464074161, 1.1404671556548371, 1.1366992143926407,
      1.1328357819303805, 1.1288763350666313, 1.1248203683045797,
      1.1206673940635394, 1.1164169428864117, 1.1120685636429266,
      1.1076218237286901, 1.103076309259917, 1.0984316252638093,
      1.0936873958645372, 1.088843264464719, 1.083898893922383,
      1.0788539667233628, 1.0737081851490118, 1.0684612714392574,
      1.0631129679508859, 1.0576630373110407, 1.0521112625658833,
      1.0464574473243116, 1.0407014158968169, 1.0348430134292717,
      1.0288821060317372, 1.0228185809021872, 1.0166523464450872,
      1.0103833323848772, 1.004011489874191, 0.99753679159691744,
      0.99095923186593093, 0.98427882671556888, 0.9774956139887705,
      0.970609653418811, 0.963621026705729, 0.95652983758722809,
      0.94933621190424078, 0.94204029766094788, 0.9346422650793087,
      0.92714230664812736, 0.919540637166532, 0.91183749378193335,
      0.90403313602238167, 0.89612784582336669, 0.88812192754900543,
      0.880015708007614, 0.87180953646166759, 0.8635037846321163,
      0.855098846697079, 0.84659513928486985, 0.83799310146139627,
      0.82929319471188834, 0.82049590291699459, 0.81160173232320343,
      0.80261121150764525, 0.79352489133720128, 0.78434334492202207,
      0.77506716756337457, 0.76569697669589165, 0.75623341182418424,
      0.74667713445385653, 0.73702882801695269, 0.72728919779178469,
      0.71745897081724, 0.7075388958015324, 0.697529743025428, 0.687432304240009,
      0.677247392558867, 0.66697584234497975, 0.65661850909201747,
      0.646176269300383, 0.63565002034776741, 0.62504068035444,
      0.6143491880432147, 0.60357650259409179, 0.59272360349375863,
      0.58179149037978006, 0.57078118287969559, 0.55969372044496,
      0.5485301621798041, 0.5372915866650726, 0.52597909177698854,
      0.51459379450108822, 0.50313683074112114, 0.49160935512316667,
      0.48001254079491418, 0.46834757922017561, 0.45661567996871921,
      0.4448180705014031, 0.43295599595071832, 0.42103071889684512,
      0.40904351913912212, 0.396995693463153, 0.38488855540352751,
      0.37272343500220922, 0.36050167856272425, 0.34822464840007877,
      0.33589372258666711, 0.32351029469401704, 0.31107577353060833,
      0.29859158287576787, 0.286059161209648, 0.27347996143953074,
      0.26085545062228632, 0.24818710968332391, 0.23547643313185729,
      0.22272492877274408, 0.20993411741490256, 0.19710553257631414,
      0.18424072018588225, 0.17134123828194092, 0.15840865670781268,
      0.14544455680421808, 0.13245053109874336, 0.11942818299250128,
      0.10637912644392836, 0.093304985649916988, 0.080207394724278236,
      0.06708799737369979, 0.053948446571221276, 0.040790404227347754,
      0.027615540858852084, 0.014425535255400072, 0.0012220741440535782,
      -0.01199314814829671, -0.025218430034374906, -0.038452063007872753,
      -0.051692331986536548, -0.0649375156569536, -0.078185886820896042,
      -0.091435712743205333, -0.10468525550104857, -0.1179327723345058,
      -0.13117651599838587, -0.14441473511517333, -0.15764567452902814,
      -0.17086757566071464, -0.18407867686343574, -0.1972772137793955,
      -0.21046141969706247, -0.22362952590900831, -0.23677976207022752,
      -0.24991035655692809, -0.26301953682550372, -0.27610552977187586,
      -0.28916656209081643, -0.30220086063542012, -0.31520665277644977,
      -0.32818216676153505, -0.34112563207419133, -0.35403527979239935,
      -0.36690934294686289, -0.37974605687868179, -0.39254365959645426,
      -0.40530039213266122, -0.41801449889925341, -0.43068422804242723,
      -0.44330783179631111, -0.45588356683572628, -0.46840969462770315,
      -0.48088448178181736, -0.49330620039918543, -0.50567312842003354,
      -0.51798354996981388, -0.53023575570370884, -0.54242804314943083,
      -0.55455871704835014, -0.56662608969471617, -0.57862848127297528,
      -0.59056422019309529, -0.60243164342375966, -0.61422909682347127,
      -0.62595493546928394, -0.63760752398331566, -0.64918523685678553,
      -0.66068645877154741, -0.67210958491912631, -0.68345302131699437,
      -0.69471518512224806, -0.70589450494236317, -0.71698942114317066,
      -0.72799838615383738, -0.73891986476881266, -0.74975233444674039,
      -0.760494285606114, -0.771144221917812, -0.78170066059420584,
      -0.79216213267498936, -0.80252718330955186, -0.81279437203579719,
      -0.82296227305545833, -0.83302947550572515, -0.84299458372723157,
      -0.852856217528237, -0.86261301244502264, -0.87226361999839519,
      -0.88180670794626814, -0.89124096053225255, -0.90056507873018921,
      -0.90977778048460745, -0.91887780094700622, -0.92786389270795078,
      -0.93673482602489766, -0.94548938904574, -0.95412638802797023,
      -0.96264464755348322, -0.971043010738915, -0.97932033944148589,
      -0.98747551446034976, -0.99550743573333544, -1.0034150225291103,
      -1.0111972136346703, -1.0188529675381752, -1.0263812626070308,
      -1.0337810972612556, -1.0410514901420178, -1.0481914802753816,
      -1.0552001272312264, -1.0620765112772179, -1.06881973352797,
      -1.0754289160891906, -1.0819032021969368, -1.0882417563518694,
      -1.0944437644484959, -1.1005084338994433, -1.1064349937546292,
      -1.1122226948154443, -1.117870809743833, -1.1233786331662929,
      -1.1287454817727973, -1.1339706944105863, -1.1390536321728892,
      -1.1439936784824591, -1.1487902391700373, -1.1534427425476483,
      -1.1579506394767773, -1.1623134034313813, -1.1665305305557838,
      -1.1706015397174248, -1.174525972554451, -1.1783033935181988,
      -1.1819333899105282, -1.1854155719160313, -1.1887495726291462,
      -1.1919350480761424, -1.1949716772319994, -1.1978591620322554,
      -1.2005972273797068, -1.2031856211461158, -1.2056241141688513,
      -1.2079125002425009, -1.2100505961055037, -1.2120382414217696,
      -1.2138752987573658, -1.2155616535522435, -1.2170972140870659,
      -1.2184819114451366, -1.2197156994694689, -1.220798554715032,
      -1.2217304763961787, -1.2225114863293109, -1.223141628870797,
      -1.2236209708501917, -1.2239496014987659, -1.2241276323734278,
      -1.2241551972760052, -1.2240324521680013, -1.2237595750808108,
      -1.2233367660214551, -1.2227642468738726, -1.2220422612958286,
      -1.2211710746114404, -1.2201509736994354, -1.2189822668771051,
      -1.2176652837800626, -1.2162003752378394, -1.2145879131453468,
      -1.2128282903302718, -1.2109219204164705, -1.2088692376833776,
      -1.2066706969215162, -1.2043267732841341, -1.2018379621350617,
      -1.19920477889279, -1.1964277588708911, -1.1935074571147757,
      -1.1904444482348862, -1.1872393262363943, -1.183892704345398,
      -1.1804052148317596, -1.176777508828601, -1.1730102561485205,
      -1.1691041450965927, -1.1650598822802516, -1.1608781924160609,
      -1.1565598181334775, -1.1521055197756755, -1.1475160751974725,
      -1.1427922795604297, -1.1379349451252248, -1.1329449010413175,
      -1.1278229931339989, -1.1225700836889247, -1.117187051234126,
      -1.1116747903196411, -1.1060342112947958, -1.1002662400832204,
      -1.0943718179556783, -1.0883519013007195, -1.082207461393363,
      -1.0759394841617089, -1.0695489699516889, -1.0630369332899599,
      -1.0564044026450357, -1.0496524201867137, -1.0427820415438789,
      -1.0357943355607886, -1.0286903840518016, -1.0214712815548144,
      -1.0141381350832601, -1.0066920638769123, -0.99913419915148716,
      -0.99146568384712552, -0.98368767237584531, -0.97580133036802119,
      -0.96780783441799245, -0.95970837182878987, -0.95150414035622211,
      -0.94319634795214835, -0.934786212507301, -0.9262749615934418,
      -0.91766383220514547, -0.9089540705011695, -0.900146931545503,
      -0.89124367904820545, -0.88224558510599871, -0.87315392994286978,
      -0.86397000165053128, -0.85469509592899484, -0.84533051582721808,
      -0.83587757148394526, -0.82633757986878742, -0.81671186452361155,
      -0.80700175530434093, -0.79720858812315754, -0.78733370469126807,
      -0.77737845226220892, -0.76734418337587174, -0.75723225560315066,
      -0.74704403129143471, -0.73678087731092268, -0.72644416480184315,
      -0.716035268922646, -0.70555556859921953, -0.69500644627522523,
      -0.68438928766353946, -0.67370548149894982, -0.66295641929210958,
      -0.65214349508481961, -0.64126810520670829, -0.6303316480333444,
      -0.61933552374586265, -0.60828113409215634, -0.59716988214964273,
      -0.58600317208974251, -0.57478240894404242, -0.563508998372252,
      -0.55218434643195846, -0.54080985935027748, -0.52938694329740144,
      -0.51791700416213737, -0.50640144732943826, -0.49484167746003593,
      -0.48323909827212574, -0.47159511232525042, -0.45991112080636959,
      -0.44818852331814923, -0.43642871766955887, -0.42463309966876289,
      -0.41280306291839047, -0.40093999861321417, -0.38904529534020904,
      -0.3771203388811622, -0.36516651201772732, -0.35318519433905476,
      -0.34117776205198058, -0.3291455877938248, -0.31709004044785466,
      -0.30501248496133471, -0.2929142821664, -0.28079678860351132,
      -0.26866135634779748, -0.25650933283805266, -0.24434206070862186,
      -0.23216087762405704, -0.21996711611665543, -0.20776210342682588,
      -0.1955471613463744, -0.18332360606469295, -0.17109274801781382,
      -0.15885589174050765, -0.14661433572122648, -0.13436937226008977,
      -0.12212228732981076, -0.109874360439638, -0.097626864502300389,
      -0.085381065703915821, -0.073138223377031436, -0.060899589876539276,
      -0.048666410458797493, -0.036439923163632183, -0.024221358699503745,
      -0.012011940331653273, 0.00018711622668746153, 0.012374602920012231,
      0.024549319453258445, 0.036710073391402573, 0.048855680256112491,
      0.06098496361925089, 0.073096755193425483, 0.08518989491946298,
      0.097263231050888049, 0.10931562023535731, 0.12134592759311336,
      0.13335302679244027, 0.14533580012209721, 0.15729313856086416,
      0.16922394184400402, 0.18112711852691823, 0.19300158604574058,
      0.20484627077512013, 0.21666010808305708, 0.22844204238285692,
      0.24019102718224933, 0.25190602512963783, 0.2635860080575827,
      0.27522995702339925, 0.28683686234707684, 0.29840572364638529,
      0.30993554986927224, 0.32142535932356919, 0.3328741797039958,
      0.34428104811656562, 0.35564501110029295, 0.36696512464641579,
      0.3782404542149328, 0.38947007474872852, 0.40065307068509626,
      0.41178853596486586, 0.42287557403905496, 0.43391329787312188,
      0.44490082994887026, 0.45583730226397667, 0.46672185632927454,
      0.477553643163709, 0.48833182328712094, 0.49905556671081674,
      0.50972405292596323, 0.520336470889916, 0.53089201901042071,
      0.54138990512781915, 0.55182934649523241, 0.56220956975678338,
      0.57252981092394362, 0.58278931534994549, 0.59298733770241907,
      0.60312314193419136, 0.61319600125237306, 0.62320519808570984,
      0.6331500240503074, 0.64302977991368881, 0.65284377555734452,
      0.66259132993767156, 0.6722717710455, 0.68188443586414793,
      0.69142867032606437, 0.70090382926816, 0.71030927638579422,
      0.71964438418555, 0.72890853393674326, 0.73810111562180281,
      0.7472215278855292, 0.75626917798325066, 0.765243481727993,
      0.77414386343662411, 0.78296975587511108, 0.79172060020284241,
      0.80039584591614421, 0.808994950791002, 0.81751738082498981,
      0.82596261017857941, 0.83433012111569715, 0.84261940394376067,
      0.850829956953095, 0.85896128635586722, 0.8670129062245252,
      0.87498433842984047, 0.88287511257854545, 0.89068476595065482,
      0.89841284343650818, 0.90605889747354307, 0.91362248798289858,
      0.9211031823058452, 0.92850055514013374, 0.93581418847623621,
      0.94304367153361524, 0.95018860069698685, 0.95724857945264741,
      0.96422321832493241, 0.97111213481279324, 0.97791495332659717,
      0.98463130512513475, 0.9912608282529205, 0.99780316747780451,
      1.0042579742289248, 1.0106249065350765, 1.0169036289634892,
      1.0230938125591074, 1.0291951347843364, 1.035207279459389,
      1.0411299367031634, 1.0469628028747775, 1.052705580515743,
      1.0583579782928219, 1.0639197109416421, 1.0693904992110144,
      1.0747700698081015, 1.0800581553443604, 1.0852544942823756,
      1.0903588308835586, 1.0953709151567643, 1.1002905028078775,
      1.1051173551903288, 1.1098512392566626, 1.114491927511104,
      1.1190391979631888, 1.1234928340824895, 1.1278526247544218,
      1.1321183642372272, 1.1362898521200504, 1.1403668932822606,
      1.1443492978539185, 1.1482368811774986, 1.1520294637708388,
      1.1557268712913487, 1.1593289345015045, 1.1628354892356412,
      1.1662463763680442, 1.16956144178239, 1.1727805363425179,
      1.1759035158645648, 1.1789302410904761, 1.1818605776628814,
      1.1846943961014083, 1.1874315717803494, 1.1900719849077845,
      1.1926155205061195, 1.1950620683940376, 1.1974115231699336,
      1.199663784196739, 1.2018187555882549, 1.2038763461968887,
      1.2058364696028974, 1.207699044105055, 1.2094639927127986,
      1.2111312431398515, 1.2127007277992756, 1.2141723838000258,
      1.215546152944933, 1.2168219817301658, 1.2179998213461309,
      1.2190796276798301, 1.2200613613186688, 1.2209449875556708,
      1.2217304763961621, 1.2224178025658452, 1.2230069455203005,
      1.2234978894558795, 1.2238906233219984, 1.2241851408347952,
      1.2243814404921776, 1.2244795255901941, 1.22447940424076,
      1.2243810893907061, 1.2241845988421252, 1.223889955274019,
      1.2234971862651989, 1.2230063243184746, 1.2224174068860216,
      1.2217304763960319, 1.2209455802804814, 1.2200627710041396,
      1.2190821060946821, 1.2180036481739305, 1.2168274649902306,
      1.2155536294518534, 1.2141822196614942, 1.2127133189517703,
      1.2111470159217257, 1.2094834044742997, 1.2077225838547505,
      1.2058646586899828, 1.2039097390287521, 1.2018579403827407,
      1.1997093837684452, 1.19746419574986, 1.1951225084819084,
      1.1926844597546251, 1.1901501930379961, 1.1875198575275079,
      1.1847936081902708, 1.1819716058117664, 1.1790540170431365,
      1.1760410144490083, 1.1729327765557727, 1.1697294879003397,
      1.1664313390793044, 1.1630385267984302, 1.1595512539225661,
      1.1559697295257556, 1.1522941689416639, 1.1485247938142233,
      1.1446618321484119, 1.1407055183612249, 1.1366560933327063,
      1.1325138044570664, 1.1282789056937703, 1.1239516576186745,
      1.1195323274750202, 1.1150211892243909, 1.1104185235974653,
      1.1057246181446105, 1.1009397672862398, 1.0960642723628917,
      1.0910984416850009, 1.086042590582283, 1.0808970414527688,
      1.075662123811346, 1.0703381743378413, 1.0649255369245585,
      1.0594245627232755, 1.0538356101915796, 1.0481590451385843,
      1.0423952407699519, 1.0365445777321125, 1.0306074441558046,
      1.0245842356986625, 1.0184753555870683, 1.0122812146569746,
      1.0060022313938517, 0.99963883197161174, 0.99319145029049738,
      0.98666052801390014, 0.9800465146040549 } ;

    DATA_COLLECTION_DW.FromWorkspace3_PWORK.TimePtr = (void *) pTimeValues0;
    DATA_COLLECTION_DW.FromWorkspace3_PWORK.DataPtr = (void *) pDataValues0;
    DATA_COLLECTION_DW.FromWorkspace3_IWORK.PrevIndex = 0;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace2' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06,
      0.07, 0.08, 0.09, 0.1, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18,
      0.19, 0.2, 0.21, 0.22, 0.23, 0.24, 0.25, 0.26, 0.27, 0.28, 0.29, 0.3, 0.31,
      0.32, 0.33, 0.34, 0.35000000000000003, 0.36, 0.37, 0.38, 0.39, 0.4,
      0.41000000000000003, 0.42, 0.43, 0.44, 0.45, 0.46, 0.47000000000000003,
      0.48, 0.49, 0.5, 0.51, 0.52, 0.53, 0.54, 0.55, 0.56, 0.57000000000000006,
      0.58, 0.59, 0.6, 0.61, 0.62, 0.63, 0.64, 0.65, 0.66, 0.67, 0.68,
      0.69000000000000006, 0.70000000000000007, 0.71, 0.72, 0.73, 0.74, 0.75,
      0.76, 0.77, 0.78, 0.79, 0.8, 0.81, 0.82000000000000006,
      0.83000000000000007, 0.84, 0.85, 0.86, 0.87, 0.88, 0.89, 0.9, 0.91, 0.92,
      0.93, 0.94000000000000006, 0.95000000000000007, 0.96, 0.97, 0.98, 0.99,
      1.0, 1.01, 1.02, 1.03, 1.04, 1.05, 1.06, 1.07, 1.08, 1.09, 1.1, 1.11, 1.12,
      1.1300000000000001, 1.1400000000000001, 1.1500000000000001, 1.16, 1.17,
      1.18, 1.19, 1.2, 1.21, 1.22, 1.23, 1.24, 1.25, 1.26, 1.27, 1.28, 1.29, 1.3,
      1.31, 1.32, 1.33, 1.34, 1.35, 1.36, 1.37, 1.3800000000000001,
      1.3900000000000001, 1.4000000000000001, 1.41, 1.42, 1.43, 1.44, 1.45, 1.46,
      1.47, 1.48, 1.49, 1.5, 1.51, 1.52, 1.53, 1.54, 1.55, 1.56, 1.57, 1.58,
      1.59, 1.6, 1.61, 1.62, 1.6300000000000001, 1.6400000000000001,
      1.6500000000000001, 1.6600000000000001, 1.67, 1.68, 1.69, 1.7, 1.71, 1.72,
      1.73, 1.74, 1.75, 1.76, 1.77, 1.78, 1.79, 1.8, 1.81, 1.82, 1.83, 1.84,
      1.85, 1.86, 1.87, 1.8800000000000001, 1.8900000000000001,
      1.9000000000000001, 1.9100000000000001, 1.92, 1.93, 1.94, 1.95, 1.96, 1.97,
      1.98, 1.99, 2.0, 2.0100000000000002, 2.02, 2.0300000000000002, 2.04, 2.05,
      2.06, 2.07, 2.08, 2.09, 2.1, 2.11, 2.12, 2.13, 2.14, 2.15, 2.16, 2.17,
      2.18, 2.19, 2.2, 2.21, 2.22, 2.23, 2.24, 2.25, 2.2600000000000002, 2.27,
      2.2800000000000002, 2.29, 2.3000000000000003, 2.31, 2.32, 2.33, 2.34, 2.35,
      2.36, 2.37, 2.38, 2.39, 2.4, 2.41, 2.42, 2.43, 2.44, 2.45, 2.46, 2.47,
      2.48, 2.49, 2.5, 2.5100000000000002, 2.52, 2.5300000000000002, 2.54,
      2.5500000000000003, 2.56, 2.57, 2.58, 2.59, 2.6, 2.61, 2.62, 2.63, 2.64,
      2.65, 2.66, 2.67, 2.68, 2.69, 2.7, 2.71, 2.72, 2.73, 2.74, 2.75,
      2.7600000000000002, 2.77, 2.7800000000000002, 2.79, 2.8000000000000003,
      2.81, 2.82, 2.83, 2.84, 2.85, 2.86, 2.87, 2.88, 2.89, 2.9, 2.91, 2.92,
      2.93, 2.94, 2.95, 2.96, 2.97, 2.98, 2.99, 3.0, 3.0100000000000002, 3.02,
      3.0300000000000002, 3.04, 3.0500000000000003, 3.06, 3.0700000000000003,
      3.08, 3.09, 3.1, 3.11, 3.12, 3.13, 3.14, 3.15, 3.16, 3.17, 3.18, 3.19, 3.2,
      3.21, 3.22, 3.23, 3.24, 3.25, 3.2600000000000002, 3.27, 3.2800000000000002,
      3.29, 3.3000000000000003, 3.31, 3.3200000000000003, 3.33, 3.34, 3.35, 3.36,
      3.37, 3.38, 3.39, 3.4, 3.41, 3.42, 3.43, 3.44, 3.45, 3.46, 3.47, 3.48,
      3.49, 3.5, 3.5100000000000002, 3.52, 3.5300000000000002, 3.54,
      3.5500000000000003, 3.56, 3.5700000000000003, 3.58, 3.59, 3.6, 3.61, 3.62,
      3.63, 3.64, 3.65, 3.66, 3.67, 3.68, 3.69, 3.7, 3.71, 3.72, 3.73, 3.74,
      3.75, 3.7600000000000002, 3.77, 3.7800000000000002, 3.79,
      3.8000000000000003, 3.81, 3.8200000000000003, 3.83, 3.84, 3.85, 3.86, 3.87,
      3.88, 3.89, 3.9, 3.91, 3.92, 3.93, 3.94, 3.95, 3.96, 3.97, 3.98, 3.99, 4.0,
      4.01, 4.0200000000000005, 4.03, 4.04, 4.05, 4.0600000000000005, 4.07, 4.08,
      4.09, 4.1, 4.11, 4.12, 4.13, 4.14, 4.15, 4.16, 4.17, 4.18, 4.19, 4.2, 4.21,
      4.22, 4.23, 4.24, 4.25, 4.26, 4.2700000000000005, 4.28, 4.29, 4.3,
      4.3100000000000005, 4.32, 4.33, 4.34, 4.3500000000000005, 4.36, 4.37, 4.38,
      4.39, 4.4, 4.41, 4.42, 4.43, 4.44, 4.45, 4.46, 4.47, 4.48, 4.49, 4.5, 4.51,
      4.5200000000000005, 4.53, 4.54, 4.55, 4.5600000000000005, 4.57, 4.58, 4.59,
      4.6000000000000005, 4.61, 4.62, 4.63, 4.64, 4.65, 4.66, 4.67, 4.68, 4.69,
      4.7, 4.71, 4.72, 4.73, 4.74, 4.75, 4.76, 4.7700000000000005, 4.78, 4.79,
      4.8, 4.8100000000000005, 4.82, 4.83, 4.84, 4.8500000000000005, 4.86, 4.87,
      4.88, 4.89, 4.9, 4.91, 4.92, 4.93, 4.94, 4.95, 4.96, 4.97, 4.98, 4.99, 5.0,
      5.01, 5.0200000000000005, 5.03, 5.04, 5.05, 5.0600000000000005, 5.07, 5.08,
      5.09, 5.1000000000000005, 5.11, 5.12, 5.13, 5.14, 5.15, 5.16, 5.17, 5.18,
      5.19, 5.2, 5.21, 5.22, 5.23, 5.24, 5.25, 5.26, 5.2700000000000005, 5.28,
      5.29, 5.3, 5.3100000000000005, 5.32, 5.33, 5.34, 5.3500000000000005, 5.36,
      5.37, 5.38, 5.39, 5.4, 5.41, 5.42, 5.43, 5.44, 5.45, 5.46, 5.47, 5.48,
      5.49, 5.5, 5.51, 5.5200000000000005, 5.53, 5.54, 5.55, 5.5600000000000005,
      5.57, 5.58, 5.59, 5.6000000000000005, 5.61, 5.62, 5.63, 5.64, 5.65, 5.66,
      5.67, 5.68, 5.69, 5.7, 5.71, 5.72, 5.73, 5.74, 5.75, 5.76,
      5.7700000000000005, 5.78, 5.79, 5.8, 5.8100000000000005, 5.82, 5.83, 5.84,
      5.8500000000000005, 5.86, 5.87, 5.88, 5.89, 5.9, 5.91, 5.92, 5.93, 5.94,
      5.95, 5.96, 5.97, 5.98, 5.99, 6.0, 6.01, 6.0200000000000005, 6.03, 6.04,
      6.05, 6.0600000000000005, 6.07, 6.08, 6.09, 6.1000000000000005, 6.11, 6.12,
      6.13, 6.1400000000000006, 6.15, 6.16, 6.17, 6.18, 6.19, 6.2, 6.21, 6.22,
      6.23, 6.24, 6.25, 6.26, 6.2700000000000005, 6.28, 6.29, 6.3,
      6.3100000000000005, 6.32, 6.33, 6.34, 6.3500000000000005, 6.36, 6.37, 6.38,
      6.3900000000000006, 6.4, 6.41, 6.42, 6.43, 6.44, 6.45, 6.46, 6.47, 6.48,
      6.49, 6.5, 6.51, 6.5200000000000005, 6.53, 6.54, 6.55, 6.5600000000000005,
      6.57, 6.58, 6.59, 6.6000000000000005, 6.61, 6.62, 6.63, 6.6400000000000006,
      6.65, 6.66, 6.67, 6.68, 6.69, 6.7, 6.71, 6.72, 6.73, 6.74, 6.75, 6.76,
      6.7700000000000005, 6.78, 6.79, 6.8, 6.8100000000000005, 6.82, 6.83, 6.84,
      6.8500000000000005, 6.86, 6.87, 6.88, 6.8900000000000006, 6.9, 6.91, 6.92,
      6.93, 6.94, 6.95, 6.96, 6.97, 6.98, 6.99, 7.0, 7.01, 7.0200000000000005,
      7.03, 7.04, 7.05, 7.0600000000000005, 7.07, 7.08, 7.09, 7.1000000000000005,
      7.11, 7.12, 7.13, 7.1400000000000006, 7.15, 7.16, 7.17, 7.18, 7.19, 7.2,
      7.21, 7.22, 7.23, 7.24, 7.25, 7.26, 7.2700000000000005, 7.28, 7.29, 7.3,
      7.3100000000000005, 7.32, 7.33, 7.34, 7.3500000000000005, 7.36, 7.37, 7.38,
      7.3900000000000006, 7.4, 7.41, 7.42, 7.43, 7.44, 7.45, 7.46, 7.47, 7.48,
      7.49, 7.5, 7.51, 7.5200000000000005, 7.53, 7.54, 7.55, 7.5600000000000005,
      7.57, 7.58, 7.59, 7.6000000000000005, 7.61, 7.62, 7.63, 7.6400000000000006,
      7.65, 7.66, 7.67, 7.68, 7.69, 7.7, 7.71, 7.72, 7.73, 7.74, 7.75, 7.76,
      7.7700000000000005, 7.78, 7.79, 7.8, 7.8100000000000005, 7.82, 7.83, 7.84,
      7.8500000000000005, 7.86, 7.87, 7.88, 7.8900000000000006, 7.9, 7.91, 7.92,
      7.9300000000000006, 7.94, 7.95, 7.96, 7.97, 7.98, 7.99, 8.0, 8.01, 8.02,
      8.03, 8.0400000000000009, 8.05, 8.06, 8.07, 8.08, 8.09, 8.1, 8.11,
      8.120000000000001, 8.13, 8.14, 8.15, 8.16, 8.17, 8.18, 8.19, 8.2, 8.21,
      8.22, 8.23, 8.24, 8.25, 8.26, 8.27, 8.28, 8.2900000000000009, 8.3, 8.31,
      8.32, 8.33, 8.34, 8.35, 8.36, 8.370000000000001, 8.38, 8.39, 8.4, 8.41,
      8.42, 8.43, 8.44, 8.45, 8.46, 8.47, 8.48, 8.49, 8.5, 8.51, 8.52, 8.53,
      8.5400000000000009, 8.55, 8.56, 8.57, 8.58, 8.59, 8.6, 8.61,
      8.620000000000001, 8.63, 8.64, 8.65, 8.66, 8.67, 8.68, 8.69,
      8.7000000000000011, 8.71, 8.72, 8.73, 8.74, 8.75, 8.76, 8.77, 8.78,
      8.7900000000000009, 8.8, 8.81, 8.82, 8.83, 8.84, 8.85, 8.86,
      8.870000000000001, 8.88, 8.89, 8.9, 8.91, 8.92, 8.93, 8.94,
      8.9500000000000011, 8.96, 8.97, 8.98, 8.99, 9.0, 9.01, 9.02, 9.03,
      9.0400000000000009, 9.05, 9.06, 9.07, 9.08, 9.09, 9.1, 9.11,
      9.120000000000001, 9.13, 9.14, 9.15, 9.16, 9.17, 9.18, 9.19,
      9.2000000000000011, 9.21, 9.22, 9.23, 9.24, 9.25, 9.26, 9.27, 9.28,
      9.2900000000000009, 9.3, 9.31, 9.32, 9.33, 9.34, 9.35, 9.36,
      9.370000000000001, 9.38, 9.39, 9.4, 9.41, 9.42, 9.43, 9.44,
      9.4500000000000011, 9.46, 9.47, 9.48, 9.49, 9.5, 9.51, 9.52, 9.53,
      9.5400000000000009, 9.55, 9.56, 9.57, 9.58, 9.59, 9.6, 9.61,
      9.620000000000001, 9.63, 9.64, 9.65, 9.66, 9.67, 9.68, 9.69,
      9.7000000000000011, 9.71, 9.72, 9.73, 9.74, 9.75, 9.76, 9.77, 9.78,
      9.7900000000000009, 9.8, 9.81, 9.82, 9.83, 9.84, 9.85, 9.86,
      9.870000000000001, 9.88, 9.89, 9.9, 9.91, 9.92, 9.93, 9.94,
      9.9500000000000011, 9.96, 9.97, 9.98, 9.99, 10.0, 10.01, 10.02, 10.03,
      10.040000000000001, 10.05, 10.06, 10.07, 10.08, 10.09, 10.1, 10.11,
      10.120000000000001, 10.13, 10.14, 10.15, 10.16, 10.17, 10.18, 10.19,
      10.200000000000001, 10.21, 10.22, 10.23, 10.24, 10.25, 10.26, 10.27, 10.28,
      10.290000000000001, 10.3, 10.31, 10.32, 10.33, 10.34, 10.35, 10.36,
      10.370000000000001, 10.38, 10.39, 10.4, 10.41, 10.42, 10.43, 10.44,
      10.450000000000001, 10.46, 10.47, 10.48, 10.49, 10.5, 10.51, 10.52, 10.53,
      10.540000000000001, 10.55, 10.56, 10.57, 10.58, 10.59, 10.6, 10.61,
      10.620000000000001, 10.63, 10.64, 10.65, 10.66, 10.67, 10.68, 10.69,
      10.700000000000001, 10.71, 10.72, 10.73, 10.74, 10.75, 10.76, 10.77, 10.78,
      10.790000000000001, 10.8, 10.81, 10.82, 10.83, 10.84, 10.85, 10.86,
      10.870000000000001, 10.88, 10.89, 10.9, 10.91, 10.92, 10.93, 10.94,
      10.950000000000001, 10.96, 10.97, 10.98, 10.99, 11.0, 11.01, 11.02, 11.03,
      11.040000000000001, 11.05, 11.06, 11.07, 11.08, 11.09, 11.1, 11.11,
      11.120000000000001, 11.13, 11.14, 11.15, 11.16, 11.17, 11.18, 11.19,
      11.200000000000001, 11.21, 11.22, 11.23, 11.24, 11.25, 11.26, 11.27, 11.28,
      11.290000000000001, 11.3, 11.31, 11.32, 11.33, 11.34, 11.35, 11.36,
      11.370000000000001, 11.38, 11.39, 11.4, 11.41, 11.42, 11.43, 11.44,
      11.450000000000001, 11.46, 11.47, 11.48, 11.49, 11.5, 11.51, 11.52, 11.53,
      11.540000000000001, 11.55, 11.56, 11.57, 11.58, 11.59, 11.6, 11.61,
      11.620000000000001, 11.63, 11.64, 11.65, 11.66, 11.67, 11.68, 11.69,
      11.700000000000001, 11.71, 11.72, 11.73, 11.74, 11.75, 11.76, 11.77, 11.78,
      11.790000000000001, 11.8, 11.81, 11.82, 11.83, 11.84, 11.85, 11.86,
      11.870000000000001, 11.88, 11.89, 11.9, 11.91, 11.92, 11.93, 11.94,
      11.950000000000001, 11.96, 11.97, 11.98, 11.99, 12.0, 12.01, 12.02,
      12.030000000000001, 12.040000000000001, 12.05, 12.06, 12.07, 12.08, 12.09,
      12.1, 12.11, 12.120000000000001, 12.13, 12.14, 12.15, 12.16, 12.17, 12.18,
      12.19, 12.200000000000001, 12.21, 12.22, 12.23, 12.24, 12.25, 12.26, 12.27,
      12.280000000000001, 12.290000000000001, 12.3, 12.31, 12.32, 12.33, 12.34,
      12.35, 12.36, 12.370000000000001, 12.38, 12.39, 12.4, 12.41, 12.42, 12.43,
      12.44, 12.450000000000001, 12.46, 12.47, 12.48, 12.49, 12.5, 12.51, 12.52,
      12.530000000000001, 12.540000000000001, 12.55, 12.56, 12.57, 12.58, 12.59,
      12.6, 12.61, 12.620000000000001, 12.63, 12.64, 12.65, 12.66, 12.67, 12.68,
      12.69, 12.700000000000001, 12.71, 12.72, 12.73, 12.74, 12.75, 12.76, 12.77,
      12.780000000000001, 12.790000000000001, 12.8, 12.81, 12.82, 12.83, 12.84,
      12.85, 12.86, 12.870000000000001, 12.88, 12.89, 12.9, 12.91, 12.92, 12.93,
      12.94, 12.950000000000001, 12.96, 12.97, 12.98, 12.99, 13.0, 13.01, 13.02,
      13.030000000000001, 13.040000000000001, 13.05, 13.06, 13.07, 13.08, 13.09,
      13.1, 13.11, 13.120000000000001, 13.13, 13.14, 13.15, 13.16, 13.17, 13.18,
      13.19, 13.200000000000001, 13.21, 13.22, 13.23, 13.24, 13.25, 13.26, 13.27,
      13.280000000000001, 13.290000000000001, 13.3, 13.31, 13.32, 13.33, 13.34,
      13.35, 13.36, 13.370000000000001, 13.38, 13.39, 13.4, 13.41, 13.42, 13.43,
      13.44, 13.450000000000001, 13.46, 13.47, 13.48, 13.49, 13.5, 13.51, 13.52,
      13.530000000000001, 13.540000000000001, 13.55, 13.56, 13.57, 13.58, 13.59,
      13.6, 13.61, 13.620000000000001, 13.63, 13.64, 13.65, 13.66, 13.67, 13.68,
      13.69, 13.700000000000001, 13.71, 13.72, 13.73, 13.74, 13.75, 13.76, 13.77,
      13.780000000000001, 13.790000000000001, 13.8, 13.81, 13.82, 13.83, 13.84,
      13.85, 13.86, 13.870000000000001, 13.88, 13.89, 13.9, 13.91, 13.92, 13.93,
      13.94, 13.950000000000001, 13.96, 13.97, 13.98, 13.99, 14.0, 14.01, 14.02,
      14.030000000000001, 14.040000000000001, 14.05, 14.06, 14.07, 14.08, 14.09,
      14.1, 14.11, 14.120000000000001, 14.13, 14.14, 14.15, 14.16, 14.17, 14.18,
      14.19, 14.200000000000001, 14.21, 14.22, 14.23, 14.24, 14.25, 14.26, 14.27,
      14.280000000000001, 14.290000000000001, 14.3, 14.31, 14.32, 14.33, 14.34,
      14.35, 14.36, 14.370000000000001, 14.38, 14.39, 14.4, 14.41, 14.42, 14.43,
      14.44, 14.450000000000001, 14.46, 14.47, 14.48, 14.49, 14.5, 14.51, 14.52,
      14.530000000000001, 14.540000000000001, 14.55, 14.56, 14.57, 14.58, 14.59,
      14.6, 14.61, 14.620000000000001, 14.63, 14.64, 14.65, 14.66, 14.67, 14.68,
      14.69, 14.700000000000001, 14.71, 14.72, 14.73, 14.74, 14.75, 14.76, 14.77,
      14.780000000000001, 14.790000000000001, 14.8, 14.81, 14.82, 14.83, 14.84,
      14.85, 14.86, 14.870000000000001, 14.88, 14.89, 14.9, 14.91, 14.92, 14.93,
      14.94, 14.950000000000001, 14.96, 14.97, 14.98, 14.99, 15.0, 15.01, 15.02,
      15.030000000000001, 15.040000000000001, 15.05, 15.06, 15.07, 15.08, 15.09,
      15.1, 15.11, 15.120000000000001, 15.13, 15.14, 15.15, 15.16, 15.17, 15.18,
      15.19, 15.200000000000001, 15.21, 15.22, 15.23, 15.24, 15.25, 15.26, 15.27,
      15.280000000000001, 15.290000000000001, 15.3, 15.31, 15.32, 15.33, 15.34,
      15.35, 15.36, 15.370000000000001, 15.38, 15.39, 15.4, 15.41, 15.42, 15.43,
      15.44, 15.450000000000001, 15.46, 15.47, 15.48, 15.49, 15.5, 15.51, 15.52,
      15.530000000000001, 15.540000000000001, 15.55, 15.56, 15.57, 15.58, 15.59,
      15.6, 15.610000000000001, 15.620000000000001, 15.63, 15.64, 15.65, 15.66,
      15.67, 15.68, 15.69, 15.700000000000001, 15.71, 15.72, 15.73, 15.74, 15.75,
      15.76, 15.77, 15.780000000000001, 15.790000000000001, 15.8, 15.81, 15.82,
      15.83, 15.84, 15.85, 15.860000000000001, 15.870000000000001, 15.88, 15.89,
      15.9, 15.91, 15.92, 15.93, 15.94, 15.950000000000001, 15.96, 15.97, 15.98,
      15.99, 16.0, 16.01, 16.02, 16.03, 16.04, 16.05, 16.06, 16.07,
      16.080000000000002, 16.09, 16.1, 16.11, 16.12, 16.13, 16.14, 16.15, 16.16,
      16.17, 16.18, 16.19, 16.2, 16.21, 16.22, 16.23, 16.240000000000002, 16.25,
      16.26, 16.27, 16.28, 16.29, 16.3, 16.31, 16.32, 16.330000000000002, 16.34,
      16.35, 16.36, 16.37, 16.38, 16.39, 16.4, 16.41, 16.42, 16.43, 16.44, 16.45,
      16.46, 16.47, 16.48, 16.490000000000002, 16.5, 16.51, 16.52, 16.53, 16.54,
      16.55, 16.56, 16.57, 16.580000000000002, 16.59, 16.6, 16.61, 16.62, 16.63,
      16.64, 16.65, 16.66, 16.67, 16.68, 16.69, 16.7, 16.71, 16.72, 16.73,
      16.740000000000002, 16.75, 16.76, 16.77, 16.78, 16.79, 16.8, 16.81, 16.82,
      16.830000000000002, 16.84, 16.85, 16.86, 16.87, 16.88, 16.89, 16.9, 16.91,
      16.92, 16.93, 16.94, 16.95, 16.96, 16.97, 16.98, 16.990000000000002, 17.0,
      17.01, 17.02, 17.03, 17.04, 17.05, 17.06, 17.07, 17.080000000000002, 17.09,
      17.1, 17.11, 17.12, 17.13, 17.14, 17.150000000000002, 17.16, 17.17, 17.18,
      17.19, 17.2, 17.21, 17.22, 17.23, 17.240000000000002, 17.25, 17.26, 17.27,
      17.28, 17.29, 17.3, 17.31, 17.32, 17.330000000000002, 17.34, 17.35, 17.36,
      17.37, 17.38, 17.39, 17.400000000000002, 17.41, 17.42, 17.43, 17.44, 17.45,
      17.46, 17.47, 17.48, 17.490000000000002, 17.5, 17.51, 17.52, 17.53, 17.54,
      17.55, 17.56, 17.57, 17.580000000000002, 17.59, 17.6, 17.61, 17.62, 17.63,
      17.64, 17.650000000000002, 17.66, 17.67, 17.68, 17.69, 17.7, 17.71, 17.72,
      17.73, 17.740000000000002, 17.75, 17.76, 17.77, 17.78, 17.79, 17.8, 17.81,
      17.82, 17.830000000000002, 17.84, 17.85, 17.86, 17.87, 17.88, 17.89,
      17.900000000000002, 17.91, 17.92, 17.93, 17.94, 17.95, 17.96, 17.97, 17.98,
      17.990000000000002, 18.0, 18.01, 18.02, 18.03, 18.04, 18.05, 18.06, 18.07,
      18.080000000000002, 18.09, 18.1, 18.11, 18.12, 18.13, 18.14,
      18.150000000000002, 18.16, 18.17, 18.18, 18.19, 18.2, 18.21, 18.22, 18.23,
      18.240000000000002, 18.25, 18.26, 18.27, 18.28, 18.29, 18.3, 18.31, 18.32,
      18.330000000000002, 18.34, 18.35, 18.36, 18.37, 18.38, 18.39,
      18.400000000000002, 18.41, 18.42, 18.43, 18.44, 18.45, 18.46, 18.47, 18.48,
      18.490000000000002, 18.5, 18.51, 18.52, 18.53, 18.54, 18.55, 18.56, 18.57,
      18.580000000000002, 18.59, 18.6, 18.61, 18.62, 18.63, 18.64,
      18.650000000000002, 18.66, 18.67, 18.68, 18.69, 18.7, 18.71, 18.72, 18.73,
      18.740000000000002, 18.75, 18.76, 18.77, 18.78, 18.79, 18.8, 18.81, 18.82,
      18.830000000000002, 18.84, 18.85, 18.86, 18.87, 18.88, 18.89,
      18.900000000000002, 18.91, 18.92, 18.93, 18.94, 18.95, 18.96, 18.97, 18.98,
      18.990000000000002, 19.0, 19.01, 19.02, 19.03, 19.04, 19.05, 19.06, 19.07,
      19.080000000000002, 19.09, 19.1, 19.11, 19.12, 19.13, 19.14,
      19.150000000000002, 19.16, 19.17, 19.18, 19.19, 19.2, 19.21, 19.22, 19.23,
      19.240000000000002, 19.25, 19.26, 19.27, 19.28, 19.29, 19.3, 19.31, 19.32,
      19.330000000000002, 19.34, 19.35, 19.36, 19.37, 19.38, 19.39,
      19.400000000000002, 19.41, 19.42, 19.43, 19.44, 19.45, 19.46, 19.47, 19.48,
      19.490000000000002, 19.5, 19.51, 19.52, 19.53, 19.54, 19.55, 19.56, 19.57,
      19.580000000000002, 19.59, 19.6, 19.61, 19.62, 19.63, 19.64,
      19.650000000000002, 19.66, 19.67, 19.68, 19.69, 19.7, 19.71, 19.72, 19.73,
      19.740000000000002, 19.75, 19.76, 19.77, 19.78, 19.79, 19.8, 19.81, 19.82,
      19.830000000000002, 19.84, 19.85, 19.86, 19.87, 19.88, 19.89,
      19.900000000000002, 19.91, 19.92, 19.93, 19.94, 19.95, 19.96, 19.97, 19.98,
      19.990000000000002, 20.0, 20.01, 20.02, 20.03, 20.04, 20.05, 20.06, 20.07,
      20.080000000000002, 20.09, 20.1, 20.11, 20.12, 20.13, 20.14,
      20.150000000000002, 20.16, 20.17, 20.18, 20.19, 20.2, 20.21, 20.22, 20.23,
      20.240000000000002, 20.25, 20.26, 20.27, 20.28, 20.29, 20.3, 20.31, 20.32,
      20.330000000000002, 20.34, 20.35, 20.36, 20.37, 20.38, 20.39,
      20.400000000000002, 20.41, 20.42, 20.43, 20.44, 20.45, 20.46, 20.47, 20.48,
      20.490000000000002, 20.5, 20.51, 20.52, 20.53, 20.54, 20.55, 20.56, 20.57,
      20.580000000000002, 20.59, 20.6, 20.61, 20.62, 20.63, 20.64,
      20.650000000000002, 20.66, 20.67, 20.68, 20.69, 20.7, 20.71, 20.72, 20.73,
      20.740000000000002, 20.75, 20.76, 20.77, 20.78, 20.79, 20.8, 20.81, 20.82,
      20.830000000000002, 20.84, 20.85, 20.86, 20.87, 20.88, 20.89,
      20.900000000000002, 20.91, 20.92, 20.93, 20.94, 20.95, 20.96, 20.97, 20.98,
      20.990000000000002, 21.0, 21.01, 21.02, 21.03, 21.04, 21.05, 21.06, 21.07,
      21.080000000000002, 21.09, 21.1, 21.11, 21.12, 21.13, 21.14,
      21.150000000000002, 21.16, 21.17, 21.18, 21.19, 21.2, 21.21, 21.22, 21.23,
      21.240000000000002, 21.25, 21.26, 21.27, 21.28, 21.29, 21.3, 21.31, 21.32,
      21.330000000000002, 21.34, 21.35, 21.36, 21.37, 21.38, 21.39,
      21.400000000000002, 21.41, 21.42, 21.43, 21.44, 21.45, 21.46, 21.47, 21.48,
      21.490000000000002, 21.5, 21.51, 21.52, 21.53, 21.54, 21.55, 21.56, 21.57,
      21.580000000000002, 21.59, 21.6, 21.61, 21.62, 21.63, 21.64,
      21.650000000000002, 21.66, 21.67, 21.68, 21.69, 21.7, 21.71, 21.72, 21.73,
      21.740000000000002, 21.75, 21.76, 21.77, 21.78, 21.79, 21.8, 21.81, 21.82,
      21.830000000000002, 21.84, 21.85, 21.86, 21.87, 21.88, 21.89,
      21.900000000000002, 21.91, 21.92, 21.93, 21.94, 21.95, 21.96, 21.97, 21.98,
      21.990000000000002, 22.0, 22.01, 22.02, 22.03, 22.04, 22.05, 22.06, 22.07,
      22.080000000000002, 22.09, 22.1, 22.11, 22.12, 22.13, 22.14,
      22.150000000000002, 22.16, 22.17, 22.18, 22.19, 22.2, 22.21, 22.22, 22.23,
      22.240000000000002, 22.25, 22.26, 22.27, 22.28, 22.29, 22.3, 22.31, 22.32,
      22.330000000000002, 22.34, 22.35, 22.36, 22.37, 22.38, 22.39,
      22.400000000000002, 22.41, 22.42, 22.43, 22.44, 22.45, 22.46, 22.47, 22.48,
      22.490000000000002, 22.5, 22.51, 22.52, 22.53, 22.54, 22.55, 22.56, 22.57,
      22.580000000000002, 22.59, 22.6, 22.61, 22.62, 22.63, 22.64,
      22.650000000000002, 22.66, 22.67, 22.68, 22.69, 22.7, 22.71, 22.72, 22.73,
      22.740000000000002, 22.75, 22.76, 22.77, 22.78, 22.79, 22.8, 22.81, 22.82,
      22.830000000000002, 22.84, 22.85, 22.86, 22.87, 22.88, 22.89,
      22.900000000000002, 22.91, 22.92, 22.93, 22.94, 22.95, 22.96, 22.97, 22.98,
      22.990000000000002, 23.0, 23.01, 23.02, 23.03, 23.04, 23.05, 23.06, 23.07,
      23.080000000000002, 23.09, 23.1, 23.11, 23.12, 23.13, 23.14,
      23.150000000000002, 23.16, 23.17, 23.18, 23.19, 23.2, 23.21, 23.22, 23.23,
      23.240000000000002, 23.25, 23.26, 23.27, 23.28, 23.29, 23.3, 23.31, 23.32,
      23.330000000000002, 23.34, 23.35, 23.36, 23.37, 23.38, 23.39,
      23.400000000000002, 23.41, 23.42, 23.43, 23.44, 23.45, 23.46, 23.47, 23.48,
      23.490000000000002, 23.5, 23.51, 23.52, 23.53, 23.54, 23.55, 23.56, 23.57,
      23.580000000000002, 23.59, 23.6, 23.61, 23.62, 23.63, 23.64,
      23.650000000000002, 23.66, 23.67, 23.68, 23.69, 23.7, 23.71, 23.72, 23.73,
      23.740000000000002, 23.75, 23.76, 23.77, 23.78, 23.79, 23.8, 23.81, 23.82,
      23.830000000000002, 23.84, 23.85, 23.86, 23.87, 23.88, 23.89,
      23.900000000000002, 23.91, 23.92, 23.93, 23.94, 23.95, 23.96, 23.97, 23.98,
      23.990000000000002, 24.0, 24.01, 24.02, 24.03, 24.04, 24.05,
      24.060000000000002, 24.07, 24.080000000000002, 24.09, 24.1, 24.11, 24.12,
      24.13, 24.14, 24.150000000000002, 24.16, 24.17, 24.18, 24.19, 24.2, 24.21,
      24.22, 24.23, 24.240000000000002, 24.25, 24.26, 24.27, 24.28, 24.29, 24.3,
      24.310000000000002, 24.32, 24.330000000000002, 24.34, 24.35, 24.36, 24.37,
      24.38, 24.39, 24.400000000000002, 24.41, 24.42, 24.43, 24.44, 24.45, 24.46,
      24.47, 24.48, 24.490000000000002, 24.5, 24.51, 24.52, 24.53, 24.54, 24.55,
      24.560000000000002, 24.57, 24.580000000000002, 24.59, 24.6, 24.61, 24.62,
      24.63, 24.64, 24.650000000000002, 24.66, 24.67, 24.68, 24.69, 24.7, 24.71,
      24.72, 24.73, 24.740000000000002, 24.75, 24.76, 24.77, 24.78, 24.79, 24.8,
      24.810000000000002, 24.82, 24.830000000000002, 24.84, 24.85, 24.86, 24.87,
      24.88, 24.89, 24.900000000000002, 24.91, 24.92, 24.93, 24.94, 24.95, 24.96,
      24.97, 24.98, 24.990000000000002, 25.0, 25.01, 25.02, 25.03, 25.04, 25.05,
      25.060000000000002, 25.07, 25.080000000000002, 25.09, 25.1, 25.11, 25.12,
      25.13, 25.14, 25.150000000000002, 25.16, 25.17, 25.18, 25.19, 25.2, 25.21,
      25.22, 25.23, 25.240000000000002, 25.25, 25.26, 25.27, 25.28, 25.29, 25.3,
      25.310000000000002, 25.32, 25.330000000000002, 25.34, 25.35, 25.36, 25.37,
      25.38, 25.39, 25.400000000000002, 25.41, 25.42, 25.43, 25.44, 25.45, 25.46,
      25.47, 25.48, 25.490000000000002, 25.5, 25.51, 25.52, 25.53, 25.54, 25.55,
      25.560000000000002, 25.57, 25.580000000000002, 25.59, 25.6, 25.61, 25.62,
      25.63, 25.64, 25.650000000000002, 25.66, 25.67, 25.68, 25.69, 25.7, 25.71,
      25.72, 25.73, 25.740000000000002, 25.75, 25.76, 25.77, 25.78, 25.79, 25.8,
      25.810000000000002, 25.82, 25.830000000000002, 25.84, 25.85, 25.86, 25.87,
      25.88, 25.89, 25.900000000000002, 25.91, 25.92, 25.93, 25.94, 25.95, 25.96,
      25.97, 25.98, 25.990000000000002, 26.0, 26.01, 26.02, 26.03, 26.04, 26.05,
      26.060000000000002, 26.07, 26.080000000000002, 26.09, 26.1, 26.11, 26.12,
      26.13, 26.14, 26.150000000000002, 26.16, 26.17, 26.18, 26.19, 26.2, 26.21,
      26.22, 26.23, 26.240000000000002, 26.25, 26.26, 26.27, 26.28, 26.29, 26.3,
      26.310000000000002, 26.32, 26.330000000000002, 26.34, 26.35, 26.36, 26.37,
      26.38, 26.39, 26.400000000000002, 26.41, 26.42, 26.43, 26.44, 26.45, 26.46,
      26.47, 26.48, 26.490000000000002, 26.5, 26.51, 26.52, 26.53, 26.54, 26.55,
      26.560000000000002, 26.57, 26.580000000000002, 26.59, 26.6, 26.61, 26.62,
      26.63, 26.64, 26.650000000000002, 26.66, 26.67, 26.68, 26.69, 26.7, 26.71,
      26.72, 26.73, 26.740000000000002, 26.75, 26.76, 26.77, 26.78, 26.79, 26.8,
      26.810000000000002, 26.82, 26.830000000000002, 26.84, 26.85, 26.86, 26.87,
      26.88, 26.89, 26.900000000000002, 26.91, 26.92, 26.93, 26.94, 26.95, 26.96,
      26.97, 26.98, 26.990000000000002, 27.0, 27.01, 27.02, 27.03, 27.04, 27.05,
      27.060000000000002, 27.07, 27.080000000000002, 27.09, 27.1, 27.11, 27.12,
      27.13, 27.14, 27.150000000000002, 27.16, 27.17, 27.18, 27.19, 27.2, 27.21,
      27.22, 27.23, 27.240000000000002, 27.25, 27.26, 27.27, 27.28, 27.29, 27.3,
      27.310000000000002, 27.32, 27.330000000000002, 27.34, 27.35, 27.36, 27.37,
      27.38, 27.39, 27.400000000000002, 27.41, 27.42, 27.43, 27.44, 27.45, 27.46,
      27.47, 27.48, 27.490000000000002, 27.5, 27.51, 27.52, 27.53, 27.54, 27.55,
      27.560000000000002, 27.57, 27.580000000000002, 27.59, 27.6, 27.61, 27.62,
      27.63, 27.64, 27.650000000000002, 27.66, 27.67, 27.68, 27.69, 27.7, 27.71,
      27.72, 27.73, 27.740000000000002, 27.75, 27.76, 27.77, 27.78, 27.79, 27.8,
      27.810000000000002, 27.82, 27.830000000000002, 27.84, 27.85, 27.86, 27.87,
      27.88, 27.89, 27.900000000000002, 27.91, 27.92, 27.93, 27.94, 27.95, 27.96,
      27.97, 27.98, 27.990000000000002, 28.0, 28.01, 28.02, 28.03, 28.04, 28.05,
      28.060000000000002, 28.07, 28.080000000000002, 28.09, 28.1, 28.11, 28.12,
      28.13, 28.14, 28.150000000000002, 28.16, 28.17, 28.18, 28.19, 28.2, 28.21,
      28.22, 28.23, 28.240000000000002, 28.25, 28.26, 28.27, 28.28, 28.29, 28.3,
      28.310000000000002, 28.32, 28.330000000000002, 28.34, 28.35, 28.36, 28.37,
      28.38, 28.39, 28.400000000000002, 28.41, 28.42, 28.43, 28.44, 28.45, 28.46,
      28.47, 28.48, 28.490000000000002, 28.5, 28.51, 28.52, 28.53, 28.54, 28.55,
      28.560000000000002, 28.57, 28.580000000000002, 28.59, 28.6, 28.61, 28.62,
      28.63, 28.64, 28.650000000000002, 28.66, 28.67, 28.68, 28.69, 28.7, 28.71,
      28.72, 28.73, 28.740000000000002, 28.75, 28.76, 28.77, 28.78, 28.79, 28.8,
      28.810000000000002, 28.82, 28.830000000000002, 28.84, 28.85, 28.86, 28.87,
      28.88, 28.89, 28.900000000000002, 28.91, 28.92, 28.93, 28.94, 28.95, 28.96,
      28.97, 28.98, 28.990000000000002, 29.0, 29.01, 29.02, 29.03, 29.04, 29.05,
      29.060000000000002, 29.07, 29.080000000000002, 29.09, 29.1, 29.11, 29.12,
      29.13, 29.14, 29.150000000000002, 29.16, 29.17, 29.18, 29.19, 29.2, 29.21,
      29.22, 29.23, 29.240000000000002, 29.25, 29.26, 29.27, 29.28, 29.29, 29.3,
      29.310000000000002, 29.32, 29.330000000000002, 29.34, 29.35, 29.36, 29.37,
      29.38, 29.39, 29.400000000000002, 29.41, 29.42, 29.43, 29.44, 29.45, 29.46,
      29.47, 29.48, 29.490000000000002, 29.5, 29.51, 29.52, 29.53, 29.54, 29.55,
      29.560000000000002, 29.57, 29.580000000000002, 29.59, 29.6, 29.61, 29.62,
      29.63, 29.64, 29.650000000000002, 29.66, 29.67, 29.68, 29.69, 29.7, 29.71,
      29.72, 29.73, 29.740000000000002, 29.75, 29.76, 29.77, 29.78, 29.79, 29.8,
      29.810000000000002, 29.82, 29.830000000000002, 29.84, 29.85, 29.86, 29.87,
      29.88, 29.89, 29.900000000000002, 29.91, 29.92, 29.93, 29.94, 29.95, 29.96,
      29.97, 29.98, 29.990000000000002 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, -0.3137144197564824, -0.32585965681118279, -0.33787196826660915,
      -0.34974890538488224, -0.361488058555004, -0.37308705800609343,
      -0.38454357450881926, -0.39585532006479507, -0.40702004858370111,
      -0.4180355565479017, -0.42889968366433351, -0.43961031350344226,
      -0.45016537412495011, -0.46056283869023873, -0.47080072606114154,
      -0.48087710138493661, -0.49079007666534225, -0.50053781131931963,
      -0.51011851271948816, -0.51953043672197008, -0.52877188817948084,
      -0.537841221439488, -0.54673684082726715, -0.5554572011136869,
      -0.56400080796756036, -0.57236621839240809, -0.58055204114747472,
      -0.58855693715286017, -0.5963796198786161, -0.60401885571767622,
      -0.61147346434248662, -0.61874231904521049, -0.62582434706138867,
      -0.63271852987693611, -0.63942390351837308, -0.64593955882617748,
      -0.65226464171116683, -0.6583983533938137, -0.66433995062640949,
      -0.6700887458979925, -0.67564410762196747, -0.68100546030634235,
      -0.68617228470652469, -0.69114411796061037, -0.69592055370712069,
      -0.70050124218513332, -0.70488589031677185, -0.709074261772016,
      -0.71306617701580288, -0.71686151333739612, -0.72046020486200968,
      -0.72386224254466369, -0.72706767414628193, -0.7300766041920167,
      -0.732889193911817, -0.735505661163248, -0.73792628033657892,
      -0.74015138224216726, -0.74218135398016472, -0.74401663879258284,
      -0.7456577358977613, -0.74710520030728123, -0.748359642625384,
      -0.749421728830949, -0.75029218004209752, -0.75097177226349454,
      -0.75146133611642241, -0.75176175655171351, -0.75187397254562249,
      -0.75179897677874119, -0.75153781529804786, -0.7510915871621997,
      -0.75046144407018023, -0.74964858997341532, -0.74865428067148021,
      -0.7474798233915283, -0.74612657635156943, -0.74459594830773979,
      -0.74288939808570587, -0.74100843409635087, -0.73895461383589922,
      -0.7367295433706369, -0.73433487680639375, -0.73177231574295742,
      -0.72904360871359186, -0.72615055060984313, -0.72309498209181489,
      -0.71987878898410418, -0.71650390165759315, -0.71297229439729093,
      -0.709285984756439, -0.70544703289707666, -0.70145754091729051,
      -0.69731965216535741, -0.69303555054100829, -0.6886074597840357,
      -0.684037642750476, -0.67932840067660316, -0.6744820724309708,
      -0.66950103375474435, -0.66438769649057217, -0.65914450780024636,
      -0.65377394937140454, -0.64827853661353307, -0.64266081784353346,
      -0.63692337346111427, -0.6310688151142817, -0.625099784855194,
      -0.61901895428666187, -0.61282902369956638, -0.60653272120148127,
      -0.60013280183678008, -0.59363204669851422, -0.58703326203235739,
      -0.58033927833290055, -0.573552949432599, -0.56667715158366694,
      -0.55971478253321583, -0.55266876059194381, -0.545542023696677,
      -0.53833752846706939, -0.53105824925676992, -0.5237071771993641,
      -0.516287319249408, -0.50880169721886037, -0.50125334680923062,
      -0.4936453166397623, -0.48598066727196426, -0.4782624702308092,
      -0.47049380702292315, -0.46267776815208222, -0.454817452132339,
      -0.4469159644991042, -0.43897641681850147, -0.43100192569532281,
      -0.42299561177990663, -0.41496059877426472, -0.40690001243777779,
      -0.39881697959279072, -0.39071462713042837, -0.38259608101695358,
      -0.37446446530099931, -0.36632290112199067, -0.358174505720085,
      -0.35002239144795211, -0.34186966478471503, -0.33371942535237414,
      -0.3255747649350354, -0.31743876650126052, -0.30931450322985982,
      -0.30120503753944161, -0.29311342012203706, -0.28504268898111429,
      -0.27699586847429036, -0.2689759683610613, -0.26098598285584862,
      -0.25302888968667792, -0.24510764915979358, -0.23722520323050944,
      -0.22938447458060016, -0.22158836570253423, -0.21383975799083763,
      -0.20614151084089222, -0.19849646075545249, -0.19090742045917541,
      -0.18337717802144402, -0.17590849598777428, -0.16850411052007971,
      -0.16116673054607511, -0.15389903691809256, -0.14670368158157976,
      -0.13958328675354909, -0.13254044411123897, -0.12557771399125633,
      -0.11869762459944366, -0.11190267123173731, -0.10519531550626043,
      -0.098577984606893154, -0.092053070538569426, -0.085622929394531977,
      -0.079289880635782517, -0.0730562063829549, -0.066924150720836462,
      -0.060895919015759525, -0.054973677246079822, -0.04915955134594957,
      -0.043455626562601324, -0.03786394682733274, -0.032386514140405165,
      -0.027025287970036949, -0.0217821846656851, -0.016659076885801927,
      -0.011657793040238396, -0.00678011674747353, -0.0020277863068373647,
      0.0025975058141132212, 0.0070941134768987557, 0.011460437353958852,
      0.015694925394874271, 0.019796073276834025, 0.023762424839204876,
      0.02759257250207453, 0.031285157668641428, 0.034838871111331715,
      0.038252453341522608, 0.041524694962773445, 0.044654437007445924,
      0.047640571256628905, 0.05048204054326616, 0.053177839038401009,
      0.055727012520461972, 0.058128658627507324, 0.060381927092361676,
      0.062486019960581785, 0.06444019179119026, 0.066243749840127431,
      0.067896054226374125, 0.0693965180807038, 0.070744607677030724,
      0.071939842546324462, 0.072981795573066832, 0.073870093074237309,
      0.074604414860811541, 0.075184494281769709, 0.075610118250618918,
      0.0758811272544263, 0.07599741534538812, 0.075958930114940759,
      0.075765672650447258, 0.075417697474484235, 0.074915112466765743,
      0.07425807876874907, 0.073446810670962315, 0.072481575483117289,
      0.07136269338705864, 0.070090537272617548, 0.06866553255643959,
      0.067088156983863723, 0.065358940413933586, 0.0634784645876299,
      0.061447362879413658, 0.059266320032184794, 0.056936071875754057,
      0.054457405028942751, 0.051831156585422311, 0.04905821378341696,
      0.046139513659393561, 0.043076042685869231, 0.039868836393475993,
      0.036518978977422789, 0.033027602888500873, 0.029395888408785043,
      0.025625063212189658, 0.021716401910038596, 0.017671225581818273,
      0.013490901291284996, 0.0091768415881040566, 0.00473050399519942,
      0.00015339048200346816, -0.0045529530762032921, -0.0093869374526695526,
      -0.014346930637064048, -0.019431258416678809, -0.024638204970734712,
      -0.029966013477577325, -0.035412886734543819, -0.040976987790285108,
      -0.046656440589310927, -0.052449330628534907, -0.0583537056255829,
      -0.064367576198630955, -0.0704889165575282, -0.076715665205966455,
      -0.083045725654443708, -0.089476967143772235, -0.096007225378879124,
      -0.10263430327263939, -0.10935597169948061, -0.11616997025849721,
      -0.12307400804580568, -0.13006576443587359, -0.13714288987154488,
      -0.14430300666249488, -0.15154370979182691, -0.15886256773053867,
      -0.16625712325957259, -0.17372489429916305, -0.1812633747451978,
      -0.1888700353123012, -0.19654232438334829, -0.20427766886511917,
      -0.21207347504979551, -0.21992712948200327, -0.22783599983110797,
      -0.23579743576845327, -0.24380876984925526, -0.25186731839883314,
      -0.259970382402895, -0.26811524840154988, -0.2762991893867604,
      -0.28451946570291636, -0.29277332595023481, -0.30105800789066445,
      -0.30937073935600023, -0.31770873915789061, -0.32606921799943106,
      -0.33444937938803482, -0.34284642054927611, -0.35125753334138721,
      -0.35967990517011089, -0.36811071990359279, -0.37654715878700662,
      -0.38498640135660533, -0.39342562635289363, -0.40186201263260674,
      -0.410292740079201, -0.41871499051154115, -0.42712594859048575,
      -0.43552280272306665, -0.44390274596396068, -0.45226297691395267,
      -0.4606007006150924, -0.46891312944224522, -0.47719748399074224,
      -0.48545099395983787, -0.49367089903167571, -0.50185444974548188,
      -0.50999890836668715, -0.51810154975070144, -0.52615966220104682,
      -0.534170548321577, -0.5421315258624918, -0.55003992855988737,
      -0.55789310696854355, -0.56568842928770513, -0.57342328217956,
      -0.581095071580171, -0.58870122350258569, -0.59623918483186311,
      -0.60370642411177666, -0.61110043232291211, -0.61841872365194006,
      -0.62565883625179253, -0.63281833299251722, -0.6398948022025529,
      -0.64688585840020929, -0.65378914301510016, -0.66060232509931494,
      -0.66732310202809275, -0.67394920018979065, -0.68047837566491631,
      -0.68690841489401944, -0.69323713533423681, -0.6994623861042748,
      -0.70558204861764273, -0.71159403720393133, -0.71749629971795137,
      -0.72328681813654228, -0.728963609142868, -0.7345247246980291,
      -0.73996825259980847, -0.74529231702838894, -0.75049507907887858,
      -0.7555747372804853, -0.76052952810218288, -0.76535772644472755,
      -0.77005764611887351, -0.77462764030965525, -0.77906610202659721,
      -0.783371464539729, -0.78754220180127588, -0.791576828852909,
      -0.79547390221845027, -0.79923202028190587, -0.80284982365074886,
      -0.80632599550433237, -0.80965926192736237, -0.8128483922283215,
      -0.81589219924278633, -0.81878953962154344, -0.82153931410344361,
      -0.82414046777293248, -0.82659199030218966, -0.82889291617782779,
      -0.83104232491210817, -0.83303934123862056, -0.83488313529239666,
      -0.83657292277442741, -0.838107965100552, -0.839487569534705,
      -0.84071108930650107, -0.84177792371315308, -0.84268751820571741,
      -0.84343936445966572, -0.84403300042979978, -0.84446801038951036,
      -0.84474402495440759, -0.84486072109034316, -0.84481782210585421,
      -0.84461509762906561, -0.84425236356908639, -0.84372948206195253,
      -0.84304636140116251, -0.84220295595286565, -0.84119926605576012,
      -0.84003533790577523, -0.83871126342560343, -0.83722718011916608,
      -0.83558327091109008, -0.83377976397129028, -0.83181693252474309,
      -0.82969509464655933, -0.827414613042452, -0.82497589481471056,
      -0.82237939121379688, -0.819625597375679, -0.81671505204502892,
      -0.81364833728440755, -0.81042607816957868, -0.80704894247107939,
      -0.80351764032219941, -0.79983292387350757, -0.79599558693408579,
      -0.79200646459961743, -0.787866432867502, -0.78357640823914942,
      -0.77913734730962947, -0.774550246344855, -0.76981614084646455,
      -0.76493610510459464, -0.75991125173872587, -0.754742731226798,
      -0.7494317314227712, -0.74397947706285372, -0.73838722926058131,
      -0.73265628499095459, -0.72678797656385674, -0.7207836710869413,
      -0.71464476991822767, -0.70837270810860664, -0.70196895383448921,
      -0.69543500782082213, -0.68877240275468277, -0.681982702689718,
      -0.67506750244162328, -0.66802842697493037, -0.66086713078132386,
      -0.65358529724973435, -0.64618463802846349, -0.63866689237956931,
      -0.63103382652578022, -0.62328723299017519, -0.61542892992889575,
      -0.60746076045714525, -0.59938459196871641, -0.59120231544933832,
      -0.58291584478407432, -0.574527116059059, -0.566038086857821,
      -0.55745073555246794, -0.54876706059000679, -0.53998907977405508,
      -0.53111882954222489, -0.52215836423944739, -0.51310975538751324,
      -0.5039750909510996, -0.49475647460056155, -0.48545602497175805,
      -0.476075874923192, -0.46661817079074686, -0.45708507164028339,
      -0.44747874851837816, -0.43780138370149385, -0.4280551699438343,
      -0.41824230972419074, -0.40836501449202106, -0.39842550391307907,
      -0.38842600511483466, -0.37836875193198483, -0.36825598415231936,
      -0.35808994676321754, -0.347872889199058, -0.33760706458980316,
      -0.32729472901103734, -0.31693814073573318, -0.30653955948800654,
      -0.29610124569914559, -0.28562545976615417, -0.27511446131311246,
      -0.26457050845558405, -0.25399585706835726, -0.2433927600567774,
      -0.23276346663190814, -0.22211022158981952, -0.21143526459521864,
      -0.20074082946970656, -0.19002914348489114, -0.17930242666061694,
      -0.16856289106856065, -0.15781274014142735, -0.14705416798799395,
      -0.13628935871424028, -0.12552048575080363, -0.11474971118699318,
      -0.10397918511157994, -0.093211044960618578, -0.082447414872491465,
      -0.071690405050432837, -0.060942111132717247, -0.050204613570749235,
      -0.039479977015262124, -0.028770249710831752, -0.018077462898902386,
      -0.0074036302295459877, 0.0032492528178701408, 0.013879209504894352,
      0.024484282394904022, 0.03506253390453018, 0.045612046845407872,
      0.056130924956077966, 0.066617293423862689, 0.077069299396554741,
      0.0874851124837362, 0.097862925247583138, 0.10820095368298327,
      0.11849743768683471, 0.1287506415163473, 0.13895885423622842,
      0.14912039015460238, 0.15923358924752604, 0.16929681757197906,
      0.17930846766718975, 0.18926695894418627, 0.19917073806345428,
      0.20901827930058522, 0.21880808489980932, 0.22853868541531241,
      0.23820864004024406, 0.24781653692330971, 0.25736099347287961,
      0.26684065664851048, 0.27625420323981792, 0.28560034013262525,
      0.29487780456231005, 0.30408536435429823, 0.31322181815163891,
      0.32228599562961691, 0.33127675769734743, 0.34019299668631253,
      0.34903363652580188, 0.35779763290523253, 0.36648397342331052,
      0.37509167772401653, 0.383619797619402, 0.39206741719917931,
      0.40043365292710509, 0.40871765372414953, 0.41691860103845657,
      0.42503570890210873, 0.43306822397471012, 0.44101542557379575,
      0.44887662569210607, 0.45665116900174962, 0.46433843284528725,
      0.471937827213779, 0.47944879471183655, 0.486870810509731,
      0.49420338228262162, 0.50144605013693455, 0.50859838652400025,
      0.51565999614097136, 0.52263051581913889, 0.52950961439968958,
      0.536296992597014, 0.54299238284963625, 0.54959554915887532,
      0.5561062869153135, 0.562524422713202, 0.56884981415288349,
      0.57508234963136851, 0.5812219481211548, 0.58726855893744445,
      0.59322216149384288, 0.59908276504670721, 0.60485040842825744,
      0.61052515976858579, 0.61610711620671932, 0.62159640359087365,
      0.62699317616805061, 0.63229761626313452, 0.63750993394763666,
      0.64263036669827334, 0.64765917904551273, 0.65259666221228763,
      0.6574431337430251, 0.66219893712318778, 0.66686444138950163,
      0.67144004073104746, 0.67592615408140844, 0.68032322470207118,
      0.68463171975726689, 0.68885212988044264, 0.69298496873258186,
      0.69703077255256607, 0.70099009969977377, 0.70486353018915093,
      0.70865166521894274, 0.71235512669130707, 0.71597455672603794,
      0.71951061716759634, 0.7229639890856967, 0.72633537226964406,
      0.72962548471668465, 0.732835062114554, 0.73596485731850092,
      0.73901563982297913, 0.741988195228267, 0.74488332470224328,
      0.74770184443755161, 0.75044458510440937, 0.75311239129927654,
      0.75570612098965462, 0.75822664495524783, 0.76067484622571568,
      0.76305161951529743, 0.76535787065452532, 0.76759451601928774,
      0.76976248195749031, 0.77186270421356784, 0.77389612735108781,
      0.77586370417370354, 0.7777663951447118, 0.77960516780545408,
      0.78138099619282608, 0.78309486025614616, 0.78474774527361713,
      0.78634064126866632, 0.78787454242638111, 0.78935044651031838,
      0.79076935427991735, 0.79213226890878885, 0.79344019540411459,
      0.79469414002740624, 0.795895109716891, 0.79704411151174226,
      0.79814215197843374, 0.799190236639444, 0.80018936940455454,
      0.80114055200499945, 0.80204478343069985, 0.80290305937081619,
      0.80371637165788146, 0.804485707715725, 0.805212050011443,
      0.80589637551164384, 0.80653965514319648, 0.80714285325871726,
      0.80770692710702352, 0.80823282630878235, 0.80872149233756119,
      0.80917385800653707, 0.80959084696104133, 0.80997337317719242,
      0.81032234046680984, 0.810638641988821, 0.81092315976739293,
      0.81117676421695672, 0.811400313674362, 0.81159465393833929,
      0.81176061781648134, 0.81189902467992492, 0.81201068002593368,
      0.81209637504856447, 0.81215688621759452, 0.81219297486591069,
      0.81220538678550358, 0.8121948518322788, 0.81216208353982033,
      0.81210777874229445, 0.81203261720664788, 0.81193726127425192,
      0.81182235551216531, 0.8116885263741378, 0.81153638187153554,
      0.81136651125429249, 0.81117948470205947, 0.81097585302566066,
      0.81075614737899837, 0.81052087898152991, 0.81027053885143119,
      0.81000559754957213, 0.8097265049344099, 0.80943368992790476,
      0.80912756029257227, 0.80880850241975177, 0.80847688112920557,
      0.80813303948012116, 0.80777729859360781, 0.8074099574867637,
      0.80703129291839382, 0.80664155924643943, 0.80624098829719271,
      0.80582978924634729, 0.80540814851195275, 0.804976229659307,
      0.80453417331784438, 0.80408209711005618, 0.80362009559247594,
      0.803148240208762, 0.802666579254902, 0.802175137856565,
      0.8016739179586021, 0.80116289832672494, 0.80064203456134986,
      0.80011125912361636, 0.79957048137358155, 0.79901958762055969,
      0.798458441185615, 0.79788688247617445, 0.79730472907273475,
      0.79671177582764341, 0.79610779497590622, 0.7954925362579901,
      0.79486572705457048, 0.79422707253317992, 0.79357625580668967,
      0.7929129381035811, 0.79223675894993, 0.791547336363033,
      0.79084426705661215, 0.79012712665750806, 0.78939546993377663,
      0.78864883103410954, 0.78788672373847435, 0.78710864171988049,
      0.78631405881716609, 0.78550242931869718, 0.78467318825686838,
      0.7838257517132875, 0.78295951713451561, 0.782073863658248,
      0.78116815244979576, 0.78024172704873229, 0.77929391372557621,
      0.77832402184835425, 0.7773313442588996, 0.77631515765873615,
      0.77527472300439393, 0.77420928591198723, 0.77311807707089741,
      0.772000312666391, 0.77085519481099718, 0.76968191198447755,
      0.76847963948219156, 0.76724753987169536, 0.76598476345736533,
      0.76469044875287762, 0.76336372296132682, 0.76200370246279914,
      0.76060949330920835, 0.75918019172615925, 0.75771488462166969,
      0.75621265010150629, 0.75467255799095234, 0.753093670362756,
      0.7514750420710743, 0.74981572129116514, 0.748114750064618,
      0.74637116484988753, 0.74458399707790013, 0.742752273712511,
      0.74087501781556553, 0.73895124911632726, 0.73697998458504976,
      0.73496023901043273, 0.73289102558072616, 0.73077135646823854,
      0.72860024341700969, 0.72637669833337648, 0.72409973387920767,
      0.72176836406754563, 0.71938160486039338, 0.7169384747684111,
      0.71443799545224618, 0.711879192325256, 0.70926109515736357,
      0.70658273867977528, 0.70384316319031781, 0.70104141515911778,
      0.698176547834389, 0.69524762184803046, 0.69225370582079748,
      0.68919387696679379, 0.68606722169698264, 0.68287283622150319,
      0.67960982715049312, 0.67627731209317044, 0.67287442025491506,
      0.66940029303208215, 0.66585408460428808, 0.6622349625239119,
      0.65854210830254134, 0.65477471799412168, 0.65093200277453334,
      0.64701318951734443, 0.64301752136548873, 0.63894425829860779,
      0.63479267769579806, 0.630562074893519, 0.62625176373841607,
      0.62186107713477878, 0.617389367586434, 0.61283600773277047,
      0.60820039087871347, 0.60348193151833907, 0.59868006585194866,
      0.59379425229631877, 0.58882397198791936, 0.58376872927885415,
      0.57862805222528491, 0.57340149306812715, 0.568088628705776,
      0.56268906115864459, 0.55720241802529413, 0.5516283529299264,
      0.5459665459610501, 0.54021670410107514, 0.53437856164664133,
      0.528451880619488, 0.522436451167634, 0.516332091956696,
      0.51013865055112184, 0.50385600378517459, 0.49748405812345908,
      0.49102275001080786, 0.48447204621135775, 0.47783194413661745,
      0.47110247216237933, 0.46428368993428693, 0.45737568866188527,
      0.450378591401026, 0.44329255332443507, 0.4361177619803055,
      0.428854437538768, 0.42150283302609326, 0.41406323454647603,
      0.40653596149128762, 0.39892136673565054, 0.39121983682219497,
      0.38343179213192224, 0.37555768704200643, 0.36759801007045634,
      0.35955328400751446, 0.35142406603370524, 0.343210947824416,
      0.33491455564094469, 0.32653555040789223, 0.31807462777685724,
      0.30953251817633015, 0.30090998684772136, 0.29220783386745591,
      0.28342689415508404, 0.27456803746733494, 0.26563216837808512,
      0.25662022624416125, 0.2475331851569838, 0.23837205387997429,
      0.22913787577173217, 0.21983172869492479, 0.21045472491090789,
      0.20100801096002074, 0.19149276752760805, 0.18191020929569096,
      0.1722615847803684, 0.1625481761549013, 0.15277129905852574,
      0.14293230239099738, 0.13303256809290495, 0.12307351091178903,
      0.11305657815407305, 0.10298324942289677, 0.092855036341854436,
      0.0826734822647166, 0.072440161971194184, 0.06215668134880431,
      0.051824677060895, 0.041445816200934571, 0.031021795933119878,
      0.020554343119407459, 0.010045213933031927, -0.00050380654134091207,
      -0.011090904720783223, -0.021714238950441445, -0.032371939942951233,
      -0.043062111230805389, -0.053782829631554618, -0.064532145725697154,
      -0.075308084347160464, -0.086108645086183044, -0.096931802804492984,
      -0.10777550816262277, -0.11863768815919939, -0.12951624668205752,
      -0.1404090650710062, -0.15131400269208567, -0.16222889752313807,
      -0.17315156675051491, -0.18407980737673268, -0.19501139683889746,
      -0.20594409363769711, -0.216875637976773, -0.22780375241226569,
      -0.23872614251232616, -0.24964049752638312, -0.26054449106396876,
      -0.27143578178285382, -0.28231201408629375, -0.29317081882916013,
      -0.30400981403269933, -0.31482660560772635, -0.32561878808598432,
      -0.33638394535942606, -0.34711965142721013, -0.35782347115011032,
      -0.36849296101212853, -0.37912566988903323, -0.38971913982357159,
      -0.40027090680709154, -0.41077850156730844, -0.42123945036196014,
      -0.43165127577804629, -0.44201149753642144, -0.45231763330143893,
      -0.46256719949535841, -0.4727577121172658, -0.4828866875661969,
      -0.49295164346818043, -0.50295009950692326, -0.51287957825783614,
      -0.522737606025117, -0.53252171368158441, -0.542229437510974,
      -0.55185832005239277, -0.56140591094664782, -0.57086976778411569,
      -0.58024745695388935, -0.58953655449386044, -0.59873464694146417,
      -0.60783933218475661, -0.61684822031352959, -0.62575893447015152,
      -0.63456911169981745, -0.6432764037999239, -0.65187847816821909,
      -0.66037301864945919, -0.66875772638022268, -0.67703032063160107,
      -0.68518853964944415, -0.69323014149183848, -0.70115290486352277,
      -0.70895462994692482, -0.71663313922950533, -0.72418627832711135,
      -0.73161191680300552, -0.73890794898229528, -0.74607229476143189,
      -0.75310290041246952, -0.75999773938180237, -0.76675481308305427,
      -0.7733721516838169, -0.77984781488595534, -0.78617989269915767,
      -0.79236650620744753, -0.79840580832834829, -0.80429598456441553,
      -0.8100352537468285, -0.81562186877078591, -0.82105411732236444,
      -0.82633032259659744, -0.831448844006472, -0.836408077882549,
      -0.84120645816297079, -0.84584245707352523, -0.85031458579753272,
      -0.85462139513526436, -0.85876147615263321, -0.86273346081889957,
      -0.866536022633109, -0.87016787723902267, -0.87362778302828537,
      -0.87691454173156269, -0.88002699899742964, -0.88296404495873193,
      -0.88572461478620979, -0.88830768922913139, -0.89071229514271111,
      -0.89293750600208055, -0.89498244240259273, -0.89684627254623606,
      -0.89852821271394578, -0.90002752772360062, -0.90134353137349921,
      -0.90247558687111917, -0.90342310724694586, -0.90418555575320281,
      -0.90476244624727709, -0.90515334355966881, -0.90535786384627737,
      -0.9053756749248606, -0.90520649659549712, -0.90485010094489082,
      -0.90430631263435557, -0.90357500917133748, -0.90265612116431926,
      -0.90154963256097342, -0.9002555808694318, -0.89877405736252725,
      -0.89710520726490617, -0.89524922992286626, -0.89320637895684019,
      -0.89097696239638968, -0.88856134279762289, -0.8859599373429411,
      -0.88317321792301851, -0.88020171120094859, -0.87704599865845312,
      -0.87370671662411037, -0.87018455628352842, -0.86648026367138775,
      -0.86259463964533867, -0.8585285398416701, -0.85428287461272845,
      -0.84985860894605447, -0.8452567623652002, -0.84047840881221725,
      -0.835524676511794, -0.83039674781702977, -0.82509585903685645,
      -0.81962330024510854, -0.81398041507123609, -0.80816860047270134,
      -0.8021893064890695, -0.796044035977827, -0.78973434433196044,
      -0.78326183917934633, -0.77662818006399148, -0.76983507810918883,
      -0.762884295662642, -0.75577764592363517, -0.74851699255231563,
      -0.741104249261183, -0.73354137938884778, -0.725830395456182,
      -0.71797335870494638, -0.709972378618994, -0.70182961242818864,
      -0.69354726459512028, -0.68512758628477755, -0.67657287481728412,
      -0.66788547310385238, -0.659067769066086, -0.65012219503878765,
      -0.64105122715642238, -0.63185738472341246, -0.62254322956839947,
      -0.61311136538268829, -0.60356443704301843, -0.59390512991886579,
      -0.584136169164456, -0.57426031899569252, -0.56428038195219687,
      -0.55419919814467666, -0.54401964448781093, -0.53374463391890692,
      -0.52337711460252, -0.51292006912128985, -0.50237651365320124,
      -0.49174949713553784, -0.48104210041575235, -0.47025743538950837,
      -0.45939864412615894, -0.44846889798189316, -0.43747139670084972,
      -0.42640936750444641, -0.41528606416919456, -0.40410476609329654,
      -0.39286877735227921, -0.38158142574397813, -0.37024606182315778,
      -0.35886605792603243, -0.34744480718504089, -0.33598572253412662,
      -0.32449223570485763, -0.31296779621369697, -0.30141587034072848,
      -0.2898399401001493, -0.27824350220288346, -0.26663006701159286,
      -0.25500315748845154, -0.2433663081360089, -0.23172306393145181,
      -0.22007697925463213, -0.20843161681018735, -0.19679054654408773,
      -0.18515734455497274, -0.1735355920006173, -0.16192887399986344,
      -0.15034077853039696, -0.13877489532270462, -0.12723481475057402,
      -0.11572412671848537, -0.10424641954627593, -0.0928052788514147,
      -0.081404286429278, -0.070047019131756191, -0.058737047744584062,
      -0.047477935863758605, -0.036273238771403343, -0.025126502311456425,
      -0.014041261765545668, -0.0030210407294184449, 0.0079306500096722327,
      0.018810313594315495, 0.029614468216576456, 0.040339648235614645,
      0.050982405292855887, 0.061539309424395075, 0.072006950170222031,
      0.082381937679912948, 0.092660903814427251, 0.10284050324361102,
      0.1129174145390703, 0.12288834126202601, 0.13275001304577524,
      0.1424991866724197, 0.15213264714347172, 0.16164720874397637,
      0.1710397160998039, 0.180307045227726, 0.18944610457794825,
      0.19845383606870326, 0.20732721611258675, 0.21606325663424431,
      0.22465900607910819, 0.23311155041277809, 0.24141801411074593,
      0.24957556113808793, 0.25758139591881135, 0.26543276429449647,
      0.27312695447190782, 0.28066129795924027, 0.28803317049066451,
      0.29523999293886988, 0.30227923221524972, 0.30914840215743178,
      0.31584506440383514, 0.32236682925493509, 0.32871135652094408,
      0.33487635635558488, 0.3408595900756668, 0.34665887096617626,
      0.35227206507058012, 0.35769709196606425, 0.36293192552340858,
      0.36797459465124988, 0.37282318402443504, 0.37747583479619257,
      0.38193074529390059, 0.38618617169813907, 0.39024042870481335,
      0.39409189017007629, 0.39773898973783078, 0.40118022144955146,
      0.40441414033621736, 0.40743936299209926, 0.410254568130215,
      0.41285849711922107, 0.41524995450152635, 0.41742780849243766,
      0.41939099146013814, 0.42113850038628425, 0.42266939730709269,
      0.42398280973466451, 0.42507793105843261, 0.42595402092654355,
      0.42661040560700758, 0.42704647832848586, 0.42726169960053584,
      0.42725559751320852, 0.42702776801583964, 0.42657787517491669,
      0.42590565141090642, 0.42501089771391454, 0.42389348383809078,
      0.42255334847465659, 0.4209904994034841, 0.41920501362312795,
      0.41719703745923142, 0.414966786651238, 0.4125145464173432,
      0.40984067149762482, 0.40694558617531473, 0.40382978427613636,
      0.40049382914571163, 0.39693835360498109, 0.39316405988362257,
      0.389171719531451, 0.3849621733078008, 0.38053633104887641,
      0.3758951715130906, 0.37103974220439317, 0.36597115917361872,
      0.36069060679788123, 0.35519933753805311, 0.34949867167435833,
      0.34358999702014992, 0.33747476861391451, 0.33115450838957855,
      0.32463080482517642, 0.31790531256997095, 0.31097975205010631,
      0.30385590905289533, 0.29653563428982332, 0.28902084293839442,
      0.28131351416293776, 0.27341569061446824, 0.265329477909767,
      0.257057044089789, 0.2486006190575567, 0.23996249399568786,
      0.23114502076369914, 0.22215061127527322, 0.21298173685564753,
      0.20364092757929014, 0.19413077158807296, 0.18445391439010617,
      0.17461305813945277, 0.16461096089690874, 0.15445043587207896,
      0.14413435064693569, 0.13366562638111507, 0.12304723699915787,
      0.11228220835994829, 0.10137361740856521, 0.090324591310822988,
      0.079138306570738448, 0.067817988131184948, 0.056366908458002574,
      0.044788386607828634, 0.033085787279937773, 0.021262519852362993,
      0.009322037402582195, -0.0027321642869226337, -0.014896547737948296,
      -0.027167534800382254, -0.039541507690253885, -0.052014810041674853,
      -0.064583747972393246, -0.07724459116260346, -0.089993573946705152,
      -0.10282689641766651, -0.11574072554366227, -0.1287311962966442,
      -0.14179441279247967, -0.15492644944235356, -0.16812335211502166,
      -0.18138113930959562, -0.19469580333849745, -0.20806331152018992,
      -0.22147960738134867, -0.23494061186807536, -0.2484422245657821,
      -0.26198032492739742, -0.27555077350945473, -0.28914941321572996,
      -0.30277207054800248, -0.31641455686358866, -0.3300726696392049,
      -0.34374219374080989, -0.3574189026989838, -0.37109855998949531,
      -0.38477692031860555, -0.39844973091272562, -0.41211273281202043,
      -0.42576166216755396, -0.43939225154154882, -0.45300023121037208,
      -0.46658133046981742, -0.48013127894226776, -0.49364580788534718,
      -0.50712065150160923, -0.5205515482488855, -0.5339342421508384,
      -0.54726448410733264, -0.56053803320418, -0.5737506580218662,
      -0.58689813794281376, -0.599976264456793, -0.61298084246402551,
      -0.62590769157559734, -0.63875264741074878, -0.65151156289061918,
      -0.6641803095280403, -0.67675477871296386, -0.68923088299308433,
      -0.70160455734930538, -0.71387176046555645, -0.72602847599261267,
      -0.73807071380547928, -0.74999451125394523, -0.76179593440590176,
      -0.7734710792830064, -0.78501607308831967, -0.7964270754254793,
      -0.80770027950906065, -0.81883191336568917, -0.82981824102553559,
      -0.84065556370379391, -0.851340220971771, -0.86186859191719489,
      -0.87223709629336577, -0.88244219565676119, -0.8924803944927614,
      -0.90234824132906821, -0.91204232983650868, -0.92155929991682428,
      -0.93089583877709936, -0.94004868199048963, -0.94901461454287239,
      -0.95779047186509914, -0.96637314085050507, -0.97475956085732451,
      -0.98294672469569688, -0.99093167959892847, -0.99871152817869635,
      -1.0062834293638669, -1.0136445993226189, -1.0207923123675759,
      -1.0277239018436346, -1.0344367609981946, -1.0409283438335044,
      -1.0471961659408375, -1.0532378053162077, -1.0590509031573749,
      -1.0646331646418492, -1.0699823596856397, -1.075096323682504,
      -1.0799729582234292, -1.0846102317961157, -1.0890061804642253,
      -1.0931589085261546, -1.0970665891531142, -1.1007274650063064,
      -1.1041398488329732, -1.1073021240411194, -1.110212745252718,
      -1.1128702388351983, -1.1152732034110364, -1.1174203103452709,
      -1.1193103042107828, -1.1209420032311623, -1.1223142997010127,
      -1.1234261603835582, -1.1242766268853794, -1.1248648160081913,
      -1.1251899200774889, -1.1252512072479761, -1.1250480217856498,
      -1.1245797843264485, -1.1238459921113462, -1.1228462191978292,
      -1.1215801166476584, -1.1200474126908477, -1.1182479128657916,
      -1.1161815001354913, -1.1138481349798117, -1.1112478554637502,
      -1.108380777281657, -1.1052470937774006, -1.1018470759404488,
      -1.0981810723778538, -1.0942495092621363, -1.0900528902550817,
      -1.0855917964074482, -1.080866886034614, -1.0758788945681914,
      -1.0706286343836271, -1.0651169946038608, -1.0593449408790758,
      -1.0533135151425763, -1.0470238353429164, -1.040477095152295,
      -1.0336745636513383, -1.026617584990329, -1.0193075780270113,
      -1.0117460359410431, -1.0039345258252448, -0.9958746882537175,
      -0.98756823682699935, -0.97901695769437991, -0.97022270905351271,
      -0.9611874206274662, -0.95191309311939709, -0.942401797644979,
      -0.93265567514279191, -0.92267693576280552, -0.9124678582331931,
      -0.90203078920563173, -0.89136814257931074, -0.88048239880383683,
      -0.869376104161264, -0.85805187002746741, -0.84651237211307884,
      -0.83476034968423951, -0.82279860476337263, -0.81063000131026908,
      -0.7982574643837036, -0.78568397928386213, -0.772912590675843,
      -0.75994640169449457, -0.746788573030877, -0.73344232200064585,
      -0.719910921594604, -0.7061976995117869, -0.69230603717530859,
      -0.67823936873134327, -0.66400118003150488, -0.64959500759897726,
      -0.63502443757870242, -0.62029310467196863, -0.60540469105570727,
      -0.59036292528687773, -0.57517158119225009, -0.55983447674396369,
      -0.54435547292118225, -0.52873847255824047, -0.51298741917962143,
      -0.49710629582214183, -0.48109912384471754, -0.46496996172606725,
      -0.44872290385077396, -0.43236207928404846, -0.41589165053560428,
      -0.39931581231302266, -0.38263879026501857, -0.36586483971498174,
      -0.34899824438523286, -0.33204331511234242, -0.31500438855397384,
      -0.29788582588763879, -0.28069201150176448, -0.26342735167951759,
      -0.24609627327577382, -0.22870322238766824, -0.21125266301916271,
      -0.19374907574000705, -0.17619695633958246, -0.15860081447600538,
      -0.14096517232094641, -0.1232945632005913, -0.10559353023316459,
      -0.087866624963471265, -0.070118405994857858, -0.052353437619082066,
      -0.034576288444446907, -0.016791530022720706, 0.00099626452476690719,
      0.018782521881428156, 0.036562669909635574, 0.054332139024458534,
      0.072086363566457409, 0.0898207831731073, 0.10753084414843012,
      0.12521200083036091, 0.14285971695544042, 0.16046946702040091,
      0.17803673764020256, 0.19555702890208068, 0.21302585571519556,
      0.23043874915541948, 0.24779125780488648, 0.26507894908581586,
      0.28229741058823138, 0.29944225139113156, 0.31650910337669957,
      0.333493622537123, 0.35039149027362548, 0.36719841468728209,
      0.38391013186120726, 0.40052240713372211, 0.41703103636207695,
      0.43343184717634631, 0.449720700223077, 0.46589349039831229,
      0.48194614806958613, 0.49787464028651512, 0.51367497197958056,
      0.52934318714675355, 0.54487537002754094, 0.56026764626412184,
      0.57551618404918425, 0.59061719526011081, 0.60556693657911653,
      0.62036171059905243, 0.6349978669144537, 0.6494718031975395,
      0.663779966258774, 0.677918853091723, 0.69188501190178786,
      0.70567504311857521, 0.71928560039151712, 0.73271339156847648,
      0.74595517965698943, 0.75900778376787625, 0.77186808004088681,
      0.7845330025521392, 0.79699954420300356, 0.80926475759020666,
      0.821325755856847, 0.83317971352408238, 0.84482386730320469,
      0.85625551688785573, 0.867472025726153, 0.87847082177244751,
      0.88924939821852422, 0.89980531420398191, 0.91013619550558467,
      0.92023973520536884, 0.930113694337311, 0.93975590251233088,
      0.94916425852146458, 0.95833673091699145, 0.96727135857137914,
      0.97596625121382286, 0.98441958994426337, 0.99262962772468977,
      1.0005946898476041, 1.008313174381485, 1.0157835525931445,
      1.0230043693468094, 1.0299742434798593, 1.0366918681550576,
      1.0431560111892184, 1.0493655153581745, 1.0553192986779942,
      1.0610163546623359, 1.0664557525558802, 1.0716366375437842,
      1.0765582309370805, 1.0812198303339966, 1.0856208097571258,
      1.0897606197664462, 1.0936387875481259, 1.0972549169791408,
      1.10060868866766, 1.10369985996921, 1.106528264978627, 1.1090938144978035,
      1.111396495979267, 1.1134363734455959, 1.1152135873847309,
      1.1167283546212259, 1.1179809681634709, 1.1189717970269932,
      1.1197012860338427, 1.1201699555882025, 1.1203784014282641,
      1.1203272943544818, 1.1200173799342972, 1.1194494781834492,
      1.1186244832239822, 1.1175433629190603, 1.1162071584847568,
      1.114616984078916, 1.1127740263672417, 1.1106795440668025,
      1.1083348674670512, 1.1057413979285839, 1.1029006073597787,
      1.0998140376715073, 1.0964833002101224, 1.0929100751688705,
      1.0890961109780082, 1.0850432236737515, 1.080753296246342,
      1.0762282779674095, 1.0714701836968847, 1.0664810931696826,
      1.0612631502624206, 1.0558185622404053, 1.0501495989851439,
      1.0442585922026557, 1.038147934612847, 1.0318200791202052,
      1.0252775379661392, 1.0185228818631988, 1.0115587391115013,
      1.0043877946976576, 0.99701278937649152, 0.98943651873587268,
      0.98166183224497083, 0.97369163228625977, 0.965528873171579,
      0.95717656014262564, 0.94863774835614523, 0.93991554185423,
      0.93101309252001108, 0.92193359901915928, 0.91268030572748138,
      0.90325650164501425, 0.89366551929695348, 0.88391073362183825,
      0.87399556084726915, 0.8639234573536112, 0.85369791852605648,
      0.84332247759538836, 0.832800704467839, 0.822136204544484,
      0.81133261753051422, 0.80039361623477512, 0.78932290536001337,
      0.7781242202842017, 0.76680132583336857, 0.75535801504632349,
      0.74379810793165235, 0.7321254502175063, 0.72034391209446025,
      0.70845738695196425, 0.69646979010871579, 0.6843850575374949,
      0.67220714458473341, 0.65994002468534052, 0.64758768807322553,
      0.635154140487846, 0.62264340187727829, 0.61005950509824536,
      0.59740649461349937, 0.58468842518698816, 0.57190936057723107,
      0.55907337222938414, 0.5461845379663558, 0.53324694067943357,
      0.52026466701886021, 0.50724180608479263, 0.49418244811903989,
      0.48109068319801157, 0.46797059992737211, 0.45482628413874104,
      0.44166181758891004, 0.4284812766619836, 0.41528873107490882,
      0.40208824258675585, 0.38888386371219641, 0.37567963643963176,
      0.362479590954343, 0.34928774436708421, 0.33610809944855879,
      0.3229446433701707, 0.30980134645146573, 0.29668216091464544,
      0.283591019646619, 0.27053183496892741, 0.25750849741597315,
      0.24452487452192234, 0.23158480961674069, 0.2186921206316664,
      0.20585059891452881, 0.19306400805535992, 0.18033608272258539,
      0.16767052751022773, 0.15507101579646385, 0.14254118861391735,
      0.13008465353206664, 0.11770498355208481, 0.10540571601446169,
      0.093190351519856385, 0.081062352863383424, 0.069025143982751169,
      0.05708210892060217, 0.04523659080135678, 0.033491890822866355,
      0.021851267263214347, 0.010317934503037085, -0.0011049379364376222,
      -0.012414226339250323, -0.023606853724185528, -0.034679790757569329,
      -0.045630056649126671, -0.0564547200306037, -0.0671508998168327,
      -0.077715766049061941, -0.088146540720215966, -0.09844049858185272,
      -0.10859496793255799, -0.11860733138754895, -0.12847502662926286,
      -0.13819554713863036, -0.14776644290689006, -0.15718532112768285,
      -0.1664498468692312, -0.17555774372637278, -0.18450679445228993,
      -0.19329484156971827, -0.201919787961455, -0.21037959743998416,
      -0.2186722952960696, -0.22679596882614739, -0.23474876783832768,
      -0.24252890513691272, -0.25013465698526072, -0.25756436354685763,
      -0.26481642930447175, -0.27188932345730538, -0.27878158029598948,
      -0.285491799555334, -0.29201864674474642, -0.29836085345622793,
      -0.30451721764985296, -0.31048660391666283, -0.31626794371892736,
      -0.32186023560769755, -0.32726254541759958, -0.33247400643882807,
      -0.33749381956631219, -0.34232125342603081, -0.34695564447842964,
      -0.35139639709895687, -0.3556429836357124, -0.35969494444418793,
      -0.363551887899132, -0.36721349038356521, -0.37067949625494545,
      -0.373949717788533, -0.37702403509800642, -0.37990239603336085,
      -0.38258481605615241, -0.38507137809215553, -0.38736223236150519,
      -0.38945759618640685, -0.39135775377648385, -0.3930630559918798,
      -0.39457392008420988, -0.39589082941545606, -0.39701433315495116,
      -0.39794504595454472, -0.39868364760210684, -0.39923088265349854,
      -0.39958756004314361, -0.39975455267337634, -0.39973279698271685,
      -0.39952329249321467, -0.39912710133708729, -0.39854534776277878,
      -0.39777921762066426, -0.39682995782858033, -0.39569887581737184,
      -0.39438733895668204, -0.39289677396119083, -0.39122866627750857,
      -0.38938455945198669, -0.38736605447962197, -0.38517480913436014,
      -0.38281253728099207, -0.38028100816890709, -0.37758204570798121,
      -0.374717527726839, -0.37168938521375405, -0.36849960154049144,
      -0.3651502116693518, -0.36164330134368627, -0.35798100626221269,
      -0.35416551123739259, -0.350199049338196, -0.34608390101754472,
      -0.34182239322473129, -0.33741689850318224, -0.33286983407382004,
      -0.3281836609043931, -0.32336088276508429, -0.31840404527074906,
      -0.31331573491009534, -0.30809857806216578, -0.30275524000047849,
      -0.29728842388514909, -0.29170086974335718, -0.28599535343853877,
      -0.28017468562864, -0.274241710713801, -0.26819930577383522,
      -0.26205037949589827, -0.25579787109269314, -0.24944474921159826,
      -0.24299401083510291, -0.23644868017293305, -0.22981180754625063,
      -0.22308646826428652, -0.21627576149386729, -0.20938280912214216,
      -0.20241075461296737, -0.19536276185731194, -0.18824201401809704,
      -0.18105171236985945, -0.17379507513363709, -0.16647533630748818,
      -0.15909574449305544, -0.15165956171853731, -0.14417006225852505,
      -0.13663053145107482, -0.1290442645124335, -0.12141456534982227,
      -0.11374474537268806, -0.10603812230283816, -0.098298018983840371,
      -0.09052776219010103, -0.082730681436077688, -0.074910107785960453,
      -0.067069372664260843, -0.059211806667723979, -0.051340738378968534,
      -0.043459493182225056, -0.035571392081610836, -0.027679750522324964,
      -0.019787877215200006, -0.011899072964922708, -0.0040166295024156307,
      0.0038561716782490874, 0.011716060478067281, 0.019559779345995065,
      0.027384084426135352, 0.035185746698859544, 0.042961553115461376,
      0.050708307725967877, 0.058422832799697594, 0.066101969938245242,
      0.073742581180476385, 0.0813415500991515, 0.088895782888857078,
      0.096402209444843012, 0.10385778443241889, 0.11125948834652982,
      0.11860432856120418, 0.12588934036846333, 0.13311158800640688,
      0.14026816567606798, 0.14735619854674153, 0.15437284374948007,
      0.16131529135833186, 0.1681807653590659, 0.1749665246050939,
      0.18166986376016786, 0.18828811422763017, 0.19481864506587948,
      0.20125886388975261, 0.20760621775750557, 0.21385819404314421,
      0.220012321293772, 0.22606617007171903, 0.23201735378112193,
      0.23786352947873596, 0.24360239866869182, 0.24923170808093273,
      0.25474925043307695, 0.26015286517548808, 0.2654404392192718,
      0.27060990764698623, 0.27565925440582445, 0.2805865129830768,
      0.28538976706359576, 0.2900671511691128, 0.29461685127917436,
      0.2990371054334981, 0.30332620431557389, 0.30748249181728149,
      0.3115043655844274, 0.31539027754294269, 0.31913873440562529,
      0.32274829815925554, 0.32621758653194743, 0.32954527344056872,
      0.33273008941808679, 0.33577082202076636, 0.33866631621501808,
      0.3414154747438336, 0.34401725847268227, 0.34647068671476378,
      0.34877483753552185, 0.3509288480363415, 0.352931914617331,
      0.3547832932191381, 0.35648229954370303, 0.35802830925392426,
      0.35942075815215258, 0.360659142337498, 0.36174301834188483,
      0.36267200324483861, 0.36344577476699924, 0.36406407134229585,
      0.36452669216883204, 0.36483349723844161, 0.36498440734493792,
      0.364979404071061, 0.36481852975415779, 0.36450188743060852,
      0.364029640759028, 0.36340201392233035, 0.36261929150863792,
      0.36168181837114677, 0.36058999946698966, 0.359344299675166,
      0.35794524359362845, 0.35639341531560348, 0.35468945818523773,
      0.35283407453268079, 0.35082802538868441, 0.34867213017887982,
      0.34636726639778337, 0.34391436926274166, 0.34131443134785977,
      0.33856850219814189, 0.33567768792392144, 0.332643150775765,
      0.32946610870002169, 0.32614783487515508, 0.32268965722905485,
      0.31909295793749715, 0.31535917290394355, 0.31148979122087728,
      0.30748635461283924, 0.30335045686144424, 0.29908374321249054,
      0.29468790976547432, 0.2901647028456506, 0.28551591835892021,
      0.28074340112977636, 0.27584904422250223, 0.27083478824592244,
      0.26570262064194056, 0.26045457495808472, 0.25509273010436817,
      0.24961920959472511, 0.24403618077325581, 0.23834585402558942,
      0.23255048197565709, 0.22665235866813402, 0.2206538187368354,
      0.21455723655940365, 0.20836502539853025, 0.20207963653009556,
      0.19570355835841674, 0.18923931551904677, 0.18268946796935259,
      0.17605661006721993, 0.1693433696382175, 0.16255240703152896,
      0.15568641416502205, 0.148748113559738, 0.14174025736416268,
      0.13466562636866208, 0.1275270290103464, 0.12032730036877788,
      0.11306930115284003, 0.10575591667913643, 0.098390055842272256,
      0.090974650077350422, 0.083512652315109528, 0.076007035929983827,
      0.068460793681511783, 0.060876936649434485, 0.053258493162877937,
      0.045608507723936285, 0.037930039926079927, 0.030226163367755764,
      0.022499964561554394, 0.014754541839257826, 0.00699300425326705,
      -0.0007815295253153498, -0.008565932311528697, -0.016357069513936069,
      -0.02415180024419368, -0.031946978428375072, -0.039739453919726192,
      -0.047526073612445929, -0.05530368255607733, -0.063069125070189871,
      -0.070819245858928584, -0.078550891125057087, -0.086260909683110315,
      -0.0939461540712877, -0.1016034816617274, -0.10922975576870467,
      -0.11682184675447316, -0.12437663313232129, -0.13189100266646309,
      -0.13936185346840652, -0.14678609508943297, -0.15416064960880912,
      -0.16148245271734238, -0.16874845479593606, -0.1759556219888018,
      -0.18310093727090265, -0.19018140150931115, -0.19719403451812528,
      -0.20413587610657374, -0.21100398711995078, -0.217795450473038,
      -0.22450737217567865, -0.23113688235013391, -0.23768113623990117,
      -0.24413731520964088, -0.25050262773588772, -0.25677431038821058,
      -0.26294962880047651, -0.26902587863193467, -0.27500038651776165,
      -0.28087051100875676, -0.286633643499894, -0.29228720914740236,
      -0.29782866777408523, -0.303255514762551, -0.308565281936094,
      -0.3137555384269195, -0.31882389153141083, -0.32376798755216252,
      -0.32858551262654168, -0.33327419354144178, -0.33783179853398165,
      -0.34225613807793154, -0.34654506565554422, -0.35069647851457281,
      -0.35470831841022055, -0.358578572331781, -0.36230527321374689,
      -0.36588650063111244, -0.36932038147869584, -0.37260509063424374,
      -0.37573885160506809, -0.37871993715807473, -0.38154666993292413,
      -0.38421742303814554, -0.38673062063002878, -0.38908473847408753,
      -0.39127830448892836, -0.39330989927234794, -0.39517815660949063,
      -0.39688176396291941, -0.39841946294442709, -0.39979004976845567,
      -0.40099237568696966, -0.40202534740567858, -0.40288792748142421,
      -0.40357913470068724, -0.4040980444390187, -0.40444378900135591,
      -0.40461555794308024, -0.40461259837172797, -0.40443421522928746,
      -0.40407977155497043, -0.40354868872840566, -0.40284044669318014,
      -0.40195458416064977, -0.40089069879401018, -0.3996484473725162,
      -0.39822754593586429, -0.39662776990868176, -0.39484895420507826,
      -0.39289099331328037, -0.3907538413602919, -0.38843751215660427,
      -0.38594207922094464, -0.38326767578506271, -0.38041449477857947,
      -0.37738278879391285, -0.37417287003132538, -0.3707851102240784,
      -0.36721994054379409, -0.36347785148603795, -0.35955939273617632,
      -0.3554651730155835, -0.35119585990824126, -0.346752179667854,
      -0.34213491700548937, -0.33734491485788409, -0.33238307413651114,
      -0.32725035345745335, -0.32194776885225912, -0.31647639345983547,
      -0.31083735719954686, -0.3050318464256031, -0.29906110356287197,
      -0.29292642672431357, -0.2866291693100872, -0.28017073958854033,
      -0.2735526002592466, -0.26677626799819831, -0.25984331298537272,
      -0.25275535841481822, -0.24551407998745331, -0.23812120538677917,
      -0.23057851373762075, -0.22288783504820228, -0.21505104963568933,
      -0.20707008753541248, -0.1989469278939888, -0.19068359834657922,
      -0.18228217437848246, -0.17374477867129678, -0.16507358043387835,
      -0.15627079471836022, -0.14733868172144857, -0.13827954607123369,
      -0.12909573609981126, -0.11978964310193843, -0.11036370057997991,
      -0.10082038347543165, -0.091162207387291139, -0.081391727777524125,
      -0.0715115391639341, -0.061524274300685217, -0.05143260334683053,
      -0.041239233023033367, -0.030946905756862458, -0.020558398816915319,
      -0.01007652343611222, 0.00049587607562946723, 0.011155923228908543,
      0.02190071026230718, 0.03272729905949992, 0.043632722075664349,
      0.054613983272872493, 0.065668059064153655, 0.07679189926588792,
      0.087982428058269169, 0.099236544953378636, 0.11055112577065609,
      0.12192302361941708, 0.13334906988799991, 0.14482607523930055,
      0.15635083061230071, 0.16792010822930042, 0.17953066260840894,
      0.19117923158108407, 0.20286253731429937, 0.21457728733696305,
      0.22632017557031239, 0.23808788336191575, 0.24987708052289748,
      0.261684426368088, 0.27350657075865853, 0.28534015514706573,
      0.29718181362373086, 0.3090281739652706, 0.32087585868386687,
      0.33272148607742824, 0.34456167128019077, 0.3563930273133889,
      0.36821216613571078, 0.38001569969312293, 0.3918002409677197,
      0.40356240502529694, 0.41529881006125646, 0.42700607844452315,
      0.43868083775909128, 0.45031972184290248, 0.4619193718237129,
      0.47347643715152465, 0.48498757662737324, 0.49644945942802676,
      0.50785876612631409, 0.51921218970670946, 0.53050643657589625,
      0.54173822756794654, 0.55290429894376936, 0.56400140338451243,
      0.57502631097867885, 0.58597581020248535, 0.59684670889326052,
      0.60763583521553954, 0.6183400386195339, 0.62895619079166976,
      0.63948118659687936, 0.64991194501237981, 0.6602454100526135,
      0.6704785516850329, 0.68060836673648328, 0.69063187978988638,
      0.70054614407090676, 0.71034824232433835, 0.720035287679959,
      0.7296044245075648, 0.73905282926087745, 0.7483777113101171,
      0.75757631376296453, 0.76664591427363349, 0.77558382583980856,
      0.78438739758723763, 0.793054015541699, 0.80158110338810551,
      0.80996612321652273, 0.81820657625490667, 0.82630000358826994,
      0.83424398686409651, 0.84203614898380719, 0.84967415478004971,
      0.857155711679578, 0.86447857035160891, 0.87164052534135306,
      0.8786394156886419, 0.88547312553138247, 0.89213958469371513,
      0.8986367692586934, 0.90496270212530372, 0.91111545354967927,
      0.917093141670358, 0.92289393301744194, 0.928516043005476,
      0.93395773640997293, 0.93921732782739442, 0.94429318211850888,
      0.94918371483497332, 0.95388739262904709, 0.958402733646333,
      0.96272830790142072, 0.96686273763636388, 0.97080469766189714,
      0.97455291568128821, 0.97810617259678356, 0.98146330279854954,
      0.98462319443606128, 0.98758478967186258, 0.99034708491767509,
      0.99290913105277245, 0.99527003362461963, 0.997428953031706,
      0.99938510468857655, 1.0011377591730248, 1.0026862423554295,
      1.0040299355102313, 1.0051682754095557, 1.0061007543989644,
      1.006826920455371, 1.0073463772271172, 1.007658784056229,
      1.0077638559829099, 1.0076613637322636, 1.0073511336833259,
      1.0068330478204224, 1.0061070436669204, 1.0051731142014309,
      1.0040313077565206, 1.0026817279000069, 1.0011245332989129,
      0.99935993756616415, 0.99738820909010961, 0.99520967084696965,
      0.99282470019630265, 0.99023372865960058, 0.98743724168211622,
      0.98443577837805174, 0.98122993125921587, 0.97782034594728373,
      0.97420772086979568, 0.97039280694002561, 0.96637640722086715,
      0.96215937657289052, 0.957742621286704, 0.953127098699806,
      0.948313816798087, 0.94330383380210736, 0.93809825773841782,
      0.93269824599599316, 0.92710500486803549, 0.92131978907932466,
      0.91534390129927057, 0.90917869164093623, 0.90282555714613633,
      0.89628594125692973, 0.88956133327361719, 0.88265326779952291,
      0.87556332417276672, 0.86829312588520891, 0.86084433998888554,
      0.85321867649003458, 0.84541788773112092, 0.83744376776090834,
      0.82929815169295473, 0.820982915052758, 0.81249997311375421,
      0.80385128022245711, 0.79503882911297719, 0.78606465021121519,
      0.776930810928941, 0.76763941494806687, 0.75819260149536938,
      0.74859254460791069, 0.73884145238947851, 0.728941566258267,
      0.71889516018614175, 0.70870453992968552, 0.69837204225341876,
      0.68790003414536061, 0.67729091202532665, 0.6665471009461762,
      0.65567105378832669, 0.64466525044785628, 0.63353219701844432,
      0.62227442496748508, 0.61089449030662535, 0.59939497275710429,
      0.587778474910099, 0.57604762138244636, 0.56420505796803722,
      0.55225345078514632, 0.54019548542007467, 0.52803386606727443,
      0.51577131466647952, 0.50341057003689038, 0.49095438700896349,
      0.47840553555389664, 0.46576679991129821, 0.453040977715226,
      0.44023087911893188, 0.42733932591868218, 0.41436915067683777,
      0.40132319584462806, 0.38820431288482521, 0.37501536139468633,
      0.3617592082294423, 0.34843872662657949, 0.33505679533139132,
      0.32161629772384714, 0.30812012094731955, 0.29457115503928449,
      0.2809722920644111, 0.26732642525029149, 0.25363644812607011,
      0.239905253664316, 0.22613573342645157, 0.21233077671191261,
      0.19849326971142972, 0.18462609466471894, 0.1707321290227416,
      0.1568142446149986, 0.14287530682193134, 0.12891817375290632,
      0.11494569542987126, 0.10096071297708031, 0.086966057817117637,
      0.072964550873413137, 0.058959001779671061, 0.044952208096254886,
      0.030946954534004867, 0.016946012185542259, 0.0029521377644423641,
      -0.011031927147517995, -0.025003456844868877, -0.038959742234308425,
      -0.05289809156192532, -0.0668158311312661, -0.080710306012283184,
      -0.09457888074081, -0.10841894000831698, -0.1222278893418364,
      -0.13600315577376154, -0.14974218850138374, -0.16344245953588965,
      -0.17710146434069685, -0.190716722458869, -0.20428577812949983,
      -0.21780620089278502, -0.23127558618368821, -0.24469155591401842,
      -0.258051759042657, -0.27135387213391055, -0.28459559990370842,
      -0.29777467575357197, -0.31088886229214008, -0.32393595184417778,
      -0.33691376694685488, -0.34982016083320555, -0.36265301790263238,
      -0.37541025417830443, -0.38808981775137347, -0.4006896892118349,
      -0.41320788206599757, -0.42564244314038369, -0.43799145297201758,
      -0.45025302618496055, -0.46242531185303809, -0.47450649384871296,
      -0.4864947911778727, -0.49838845830069639, -0.51018578543828941,
      -0.52188509886522072, -0.53348476118778254, -0.54498317160796206,
      -0.55637876617312976, -0.56767001801127515, -0.57885543755192481,
      -0.58993357273255542, -0.60090300919059936, -0.61176237044093973,
      -0.622510318038923, -0.633145551728924, -0.64366680957831979,
      -0.65407286809706977, -0.66436254234274039, -0.67453468601110644,
      -0.684588191512274, -0.69452199003238224, -0.70433505158094589,
      -0.71402638502380555, -0.72359503810175474, -0.73304009743494913,
      -0.74236068851304848, -0.75155597567122556, -0.760625162052084,
      -0.7695674895535044, -0.77838223876261914, -0.78706872887580026,
      -0.7956263176049494, -0.80405440107003479, -0.81235241367799671,
      -0.820519827988202, -0.82855615456440279, -0.83646094181346986,
      -0.844233775810868, -0.8518742801130964, -0.85938211555716681,
      -0.86675698004723523, -0.87399860832858089, -0.88110677174896179,
      -0.8880812780076327, -0.89492197089199887, -0.90162873000220978,
      -0.90820147046376454, -0.91464014262828364, -0.92094473176264147,
      -0.92711525772660042, -0.93315177463915322, -0.93905437053368979,
      -0.94482316700221025, -0.95045831882875875, -0.95596001361223826,
      -0.96132847137883459, -0.96656394418421809, -0.97166671570569463,
      -0.97663710082457134, -0.98147544519887775, -0.98618212482667056,
      -0.99075754560014428, -0.9952021428507265, -0.99951638088541772,
      -1.0037007525145525, -1.007755778571217, -1.0116820074225725,
      -1.0154800144732472, -1.0191504016611044, -1.0226937969455527,
      -1.0261108537886783, -1.0294022506293872, -1.0325686903508584,
      -1.0356108997414819, -1.038529628949558, -1.0413256509320385,
      -1.0439997608974358, -1.046552775743314, -1.0489855334884552,
      -1.051298892700061, -1.05349373191619, -1.0555709490636711,
      -1.0575314608718216, -1.0593762022821143, -1.061106125854147,
      -1.0627222011681587, -1.0642254142242455, -1.0656167668387102,
      -1.06689727603765, -1.0680679734481398, -1.0691299046872087,
      -1.0700841287489202, -1.0709317173897865, -1.0716737545127835,
      -1.0723113355502438, -1.0728455668458494, -1.0732775650360487,
      -1.0736084564310786, -1.0738393763959422, -1.0739714687315076,
      -1.0740058850560503, -1.0739437841875032, -1.0737863315266094,
      -1.0735346984412919, -1.0731900616524985, -1.0727536026217019,
      -1.0722265069404169, -1.0716099637219005, -1.0709051649953225,
      -1.0701133051026572, -1.0692355800985243, -1.068273187153244,
      -1.0672273239593457, -1.0660991881417625, -1.0648899766719633,
      -1.0636008852862635, -1.0622331079085208, -1.0607878360775078,
      -1.0592662583791261, -1.0576695598837413, -1.0559989215888437,
      -1.0542555198672487, -1.0524405259211074, -1.0505551052418602,
      -1.0486004170764445, -1.046577613899903, -1.0444878408946283,
      -1.0423322354364439, -1.0401119265877399, -1.0378280345978279,
      -1.0354816704107752, -1.033073935180834, -1.0306059197957218,
      -1.0280787044079021, -1.0254933579740677, -1.0228509378029891,
      -1.0201524891119313, -1.0173990445917773, -1.0145916239810526,
      -1.0117312336490003, -1.0088188661878836, -1.0058555000146459,
      -1.0028420989821183, -0.99977961199987164, -0.99666897266491339,
      -0.993511098902341, -0.990306892616057, -0.98705723934975031,
      -0.98376300795820337, -0.98042505028908356, -0.97704420087531,
      -0.97362127663815479, -0.97015707660112316, -0.9666523816147754,
      -0.963107954092558, -0.95952453775774349, -0.95590285740157543,
      -0.95224361865269691, -0.94854750775795937, -0.94481519137464343,
      -0.94104731637423744, -0.93724450965776285, -0.9334073779827452,
      -0.92953650780189923, -0.92563246511354147, -0.92169579532382606,
      -0.91772702312076837, -0.91372665236020412, -0.90969516596360378,
      -0.90563302582783334, -0.90154067274687677, -0.89741852634552066,
      -0.8932669850250039, -0.88908642592068277, -0.88487720487167032,
      -0.88063965640243846, -0.87637409371644592, -0.87208080870168092,
      -0.86776007194817151, -0.8634121327774128, -0.859037219283687,
      -0.85463553838723461, -0.85020727589925982, -0.84575259659870738,
      -0.84127164432074442, -0.83676454205698081, -0.8322313920672082,
      -0.82767227600282312, -0.82308725504160918, -0.81847637003401863,
      -0.81383964166077116, -0.809177070601689, -0.8044886377157483,
      -0.7997743042321328, -0.79503401195237577, -0.79026768346328047,
      -0.78547522236069733, -0.78065651348392984, -0.77581142316070584,
      -0.77093979946258884, -0.76604147247071064, -0.76111625455168408,
      -0.75616394064356873, -0.75118430855177165, -0.74617711925472063,
      -0.74114211721920253, -0.73607903072515257, -0.73098757219982158,
      -0.7258674385611108, -0.72071831156994337, -0.71553985819149268,
      -0.71033173096511937, -0.7050935683828341, -0.69982499527609021,
      -0.6945256232107998, -0.68919505089029875, -0.6838328645661641,
      -0.678438638456627, -0.67301193517243085, -0.66755230614994132,
      -0.66205929209128556, -0.65653242341133922, -0.65097122069135316,
      -0.64537519513903119, -0.63974384905482029, -0.6340766763042196,
      -0.6283731627959086, -0.62263278696543267, -0.6168550202643015,
      -0.61103932765419677, -0.6051851681061351, -0.59929199510430586,
      -0.59335925715440319, -0.58738639829620232, -0.58137285862013821,
      -0.57531807478767139, -0.56922148055521082, -0.56308250730131626,
      -0.55690058455703684, -0.55067514053899647, -0.54440560268515548,
      -0.53809139819287655, -0.53173195455911038, -0.525326700122467,
      -0.51887506460687216, -0.51237647966665734, -0.50583037943269638,
      -0.49923620105951766, -0.49259338527297819, -0.48590137691838248,
      -0.47915962550869123, -0.47236758577265664, -0.46552471820258695,
      -0.45863048960151293, -0.45168437362948077, -0.44468585134876981,
      -0.43763441176773837, -0.43052955238306562, -0.42337077972018178,
      -0.41615760987155648, -0.40888956903268214, -0.40156619403545313,
      -0.39418703287872642, -0.38675164525580252, -0.37925960307856588,
      -0.37171049099813547, -0.36410390692159278, -0.35643946252483039,
      -0.34871678376096549, -0.34093551136435529, -0.33309530134979815,
      -0.32519582550677778, -0.31723677188850136, -0.30921784529545759,
      -0.30113876775337212, -0.29299927898517275, -0.28479913687692754,
      -0.27653811793738703, -0.26821601775097781, -0.2598326514240229,
      -0.25138785402397779, -0.24288148101145474, -0.23431340866483413,
      -0.22568353449728365, -0.21699177766590369, -0.20823807937292721,
      -0.1994224032586237, -0.19054473578586503, -0.18160508661602318,
      -0.17260348897611055, -0.16354000001694727, -0.15441470116215553,
      -0.14522769844783043, -0.13597912285267547, -0.12666913061851104,
      -0.11729790356087344, -0.10786564936964302, -0.098372601899490375,
      -0.088819021449988045, -0.079205195035268211, -0.069531436643004929,
      -0.059798087482705986, -0.050005516222990376, -0.040154119217933382,
      -0.030244320722132734, -0.020276573094551442, -0.010251356990876259,
      -0.000169181544366237, 0.00996941546496849, 0.020163867452972828,
      0.03041357888578361, 0.040717925146301071, 0.051076252412662615,
      0.0614878775489357, 0.071952088008032489, 0.082468141746932733,
      0.093035267154367107, 0.10365266299091486, 0.11431949834170374,
      0.12503491258167798, 0.13579801535354086, 0.14660788655844403,
      0.15746357635939012, 0.16836410519750217, 0.1793084638210834,
      0.19029561332760636, 0.20132448521856056, 0.212393981467285,
      0.22350297459967944, 0.23465030778795631, 0.24583479495727117,
      0.25705522090539334, 0.26831034143532245, 0.27959888350083151,
      0.29091954536500614, 0.30227099677166597, 0.313651879129738,
      0.32506080571045132, 0.33649636185741161, 0.34795710520948636,
      0.35944156593640586, 0.37094824698713591, 0.38247562435084415,
      0.39402214733053537, 0.40558623882915212, 0.41716629564819474,
      0.42876068879872609, 0.44036776382464482, 0.45198584113827345,
      0.46361321636798986, 0.47524816071799708, 0.48688892133997025,
      0.49853372171661664, 0.510180762056907, 0.52182821970299709,
      0.53347424954859912, 0.54511698446878176, 0.55675453576102529,
      0.56838499359736727, 0.58000642748759734, 0.59161688675324231,
      0.60321440101232071, 0.61479698067459232, 0.6263626174472543,
      0.637909284850877, 0.64943493874538838, 0.66093751786603216,
      0.67241494436900173, 0.68386512438671709, 0.69528594859242721,
      0.70667529277406449, 0.718031018417113, 0.72935097329628629,
      0.74063299207587918, 0.7518748969185125, 0.7630744981021661,
      0.77422959464518881, 0.78533797493918833, 0.79639741738947978,
      0.80740569106297322, 0.81836055634319527, 0.82925976559230019,
      0.84010106381981187, 0.8508821893578189, 0.86160087454250522,
      0.87225484640165973, 0.88284182734803129, 0.89335953587820671,
      0.90380568727682609, 0.9141779943258781, 0.92447416801878934,
      0.934691918279139, 0.9448289546836437, 0.95488298718925824,
      0.96485172686406717, 0.97473288662173374, 0.98452418195927716,
      0.99422333169782162, 1.0038280587262041, 1.0133360907469882,
      1.0227451610248273, 1.0320530091367084, 1.0412573817239577,
      1.0503560332456474, 1.0593467267331902, 1.0682272345457966,
      1.0769953391265645, 1.0856488337589163, 1.0941855233230773,
      1.1026032250523705, 1.1108997692890012, 1.1190730002391189,
      1.1271207767267855, 1.1350409729466608, 1.14283147921511,
      1.1504902027193804, 1.1580150682647059, 1.1654040190189132,
      1.1726550172543815, 1.1797660450869851, 1.1867351052118071,
      1.1935602216353123, 1.2002394404036971, 1.2067708303272056,
      1.2131524837000354, 1.2193825170156825, 1.2254590716773293,
      1.2313803147031195, 1.2371444394259645, 1.2427496661876796,
      1.2481942430271296, 1.2534764463621475, 1.2585945816649946,
      1.2635469841310161, 1.2683320193403382, 1.2729480839122556,
      1.2773936061521387, 1.2816670466905133, 1.2857668991141882,
      1.28969169058905, 1.2934399824743628, 1.2970103709283296,
      1.3004014875046148, 1.3036119997396756, 1.3066406117305764,
      1.3094860647031532, 1.3121471375701954, 1.3146226474795144,
      1.3169114503516064, 1.3190124414067412, 1.3209245556812232,
      1.3226467685326209, 1.3241780961337994, 1.325517595955463,
      1.3266643672371123, 1.3276175514461181, 1.3283763327247977,
      1.3289399383252474, 1.3293076390317919, 1.3294787495708245,
      1.3294526290078823, 1.3292286811318008, 1.3288063548257369,
      1.3281851444249377, 1.327364590061048, 1.3263442779928658,
      1.3251238409233037, 1.3237029583025191, 1.3220813566169647,
      1.3202588096642913, 1.3182351388139395, 1.3160102132533151,
      1.3135839502193845, 1.3109563152156187, 1.3081273222141556,
      1.3050970338430175, 1.3018655615584172, 1.2984330658018788,
      1.29479975614222, 1.2909658914022537, 1.2869317797700925,
      1.2826977788950624, 1.2782642959680692, 1.2736317877864143,
      1.2688007608029233, 1.2637717711594521, 1.2585454247045642,
      1.25312237699549, 1.2475033332841936, 1.2416890484876015,
      1.2356803271419339, 1.2294780233411047, 1.2230830406592041,
      1.2164963320569839, 1.2097188997724533, 1.2027517951954516,
      1.1955961187263033, 1.1882530196185048, 1.1807236958055096,
      1.1730093937115684, 1.1651114080467029, 1.1570310815858549,
      1.1487698049321411, 1.1403290162644568, 1.131710201069223,
      1.122914891856595, 1.1139446678609572, 1.1048011547259295,
      1.0954860241739035, 1.0860009936601451, 1.0763478260116275,
      1.0665283290505969, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.016006450963417324, 0.026869267082796217, 0.037736492163437024,
      0.048606283637526004, 0.059476784881213579, 0.0703461256762079,
      0.081212422678996338, 0.092073779897555635, 0.10292828917541053,
      0.11377403068289019, 0.12460907341543878, 0.13543147569882391,
      0.14623928570109324, 0.15703054195111601, 0.16780327386355437,
      0.17855550227009753, 0.18928523995679528, 0.19999049220732165,
      0.21066925735199676, 0.22131952732239613, 0.231939288211366,
      0.242526520838273, 0.25307920131930206, 0.26359530164262124,
      0.2740727902482275, 0.28450963261228812, 0.29490379183578452,
      0.30525322923726828, 0.31555590494953711, 0.32580977852003284,
      0.33601280951476509, 0.34616295812555969, 0.35625818578043483,
      0.36629645575689629, 0.37627573379795276, 0.3861939887306422,
      0.396049193086864, 0.40583932372630627, 0.41556236246125977,
      0.42521629668310756, 0.43479911999027648, 0.444308832817437,
      0.45374344306574127, 0.46310096673387552, 0.47237942854972081,
      0.48157686260239607, 0.49069131297446944, 0.49972083437412257,
      0.50866349276704237, 0.51751736600782472, 0.52628054447067185,
      0.5349511316791572, 0.54352724493484261, 0.55200701594452728,
      0.5603885914459007, 0.56867013383138942, 0.57684982176996669,
      0.58492585082671111, 0.59289643407988979, 0.60075980273534935,
      0.60851420673799006, 0.61615791538010944, 0.62368921790639054,
      0.6311064241153217, 0.638407864956825, 0.64559189312588361,
      0.65265688365194108, 0.65960123448386943, 0.66642336707028238,
      0.67312172693498518, 0.67969478424734664, 0.68614103438738527,
      0.69245899850535475, 0.69864722407562807, 0.70470428544466335,
      0.71062878437285459, 0.71641935057006145, 0.72207464222461071,
      0.72759334652557528, 0.73297418017812932, 0.73821588991178122,
      0.74331725298129137, 0.74827707766008267, 0.75309420372594849,
      0.75776750293887452, 0.76229587951078381, 0.76667827056702331,
      0.77091364659940909, 0.77500101191064841, 0.7789394050499665,
      0.78272789923975783, 0.78636560279309542, 0.78985165952192138,
      0.79318524913576216, 0.796365587630795, 0.79939192766911049,
      0.802263558948011, 0.80497980855918994, 0.80754004133764168,
      0.80994366020014907, 0.81219010647320655, 0.81427886021023566,
      0.81620944049795074, 0.81798140575174116, 0.81959435399993819,
      0.82104792315683317, 0.8223417912843255, 0.82347567684207523,
      0.82444933892604211, 0.8252625774952963, 0.82591523358698837,
      0.82640718951937164, 0.82673836908277, 0.82690873771839579,
      0.82691830268491417, 0.82676711321266882, 0.82645526064547437,
      0.825982878569891, 0.82535014293190412, 0.82455727214092811,
      0.82360452716106347, 0.82249221158953567, 0.821220671722255,
      0.8197902966064321, 0.8182015180801967, 0.81645481079916338,
      0.81455069224989907, 0.81248972275024622, 0.81027250543646467,
      0.8078996862371508, 0.80537195383391036, 0.80269003960875318,
      0.79985471757818682, 0.7968668043139937, 0.79372715885067624,
      0.79043668257955824, 0.78699631912954315, 0.7834070542345215,
      0.77966991558743393, 0.77578597268100091, 0.77175633663512433,
      0.76758216001098445, 0.76326463661184918, 0.75880500127062267,
      0.754204529624163, 0.74946453787440248, 0.74458638253630927,
      0.73957146017273556, 0.73442120711619552, 0.72913709917762937,
      0.72372065134220509, 0.71817341745222263, 0.71249698987718235,
      0.70669299917108708, 0.70076311371705358, 0.69470903935930839,
      0.68853251902265034, 0.68223533231946876, 0.675819295144403,
      0.66928625925674212, 0.66263811185066224, 0.65587677511340292,
      0.649004205771492, 0.64202239462512822, 0.63493336607083972,
      0.62773917761253106, 0.62044191936105186, 0.613043713522405,
      0.60554671387473191, 0.59795310523420619, 0.5902651029099758,
      0.5824849521482991, 0.57461492756601329, 0.56665733257349793,
      0.55861449878727365, 0.55048878543240465, 0.54228257873486152,
      0.53399829130400633, 0.52563836150537491, 0.517205252823921,
      0.5087014532179045, 0.50012947446359357, 0.49149185149097063,
      0.48279114171062287, 0.47402992433200425, 0.46521079967326356,
      0.45633638846283203, 0.44740933113296544, 0.438432287105443,
      0.42940793406962779, 0.42033896725308922, 0.41122809868500404,
      0.40207805645254036, 0.3928915839504411, 0.38367143912402785,
      0.37442039370583635, 0.36514123244611263, 0.35583675233738682,
      0.34650976183336035, 0.33716308006232282, 0.32779953603534173,
      0.3184219678494476, 0.30903322188605709, 0.29963615200486288,
      0.29023361873343956, 0.28082848845279362, 0.27142363257910923,
      0.26202192674193081, 0.25262624995902327, 0.24323948380816612,
      0.23386451159611649, 0.22450421752500749, 0.2151614858564139,
      0.2058392000733556, 0.19654024204047493, 0.18726749116265728,
      0.17802382354233642, 0.16881211113575276, 0.15963522090840956,
      0.15049601398999682, 0.14139734482902613, 0.13234206034745213,
      0.12333299909552228, 0.11437299040712845, 0.10546485355591054,
      0.096611396912378911, 0.087815417102306337, 0.079079698166663132,
      0.070407010723338437, 0.06180011113092547, 0.053261740654813552,
      0.044794624635860023, 0.036401471661889874, 0.028084972742289722,
      0.019847800485951646, 0.011692608282817811, 0.0036220294892956861,
      -0.0043613233822164393, -0.012254859469422091, -0.020056010361599305,
      -0.027762230896188247, -0.035370999950250295, -0.042879821226541284,
      -0.050286224033955829, -0.057587764062090221, -0.064782024149681955,
      -0.0718666150466734, -0.078839176169667943, -0.085697376350523075,
      -0.092438914577855108, -0.099061520731202585, -0.1055629563076273,
      -0.11194101514050527, -0.11819352411028654, -0.12431834384698655,
      -0.13031336942418398, -0.13617653104430172, -0.141905794714945,
      -0.1474991629160767, -0.1529546752578137, -0.15827040912862717,
      -0.16344448033373321, -0.16847504372346775, -0.17336029381143245,
      -0.17809846538221391, -0.18268783408846778, -0.18712671703717698,
      -0.19141347336488165, -0.19554650480169278, -0.19952425622389855,
      -0.20334521619498092, -0.20700791749485373, -0.2105109376371494,
      -0.21385289937437696, -0.21703247119077615, -0.22004836778270087,
      -0.22289935052637358, -0.22558422793283364, -0.22810185608994152,
      -0.23045113909126733, -0.23263102945172634, -0.23464052850980874,
      -0.23647868681626369, -0.23814460450910085, -0.23963743167476881,
      -0.24095636869539094, -0.24210066658192303, -0.24306962729311576,
      -0.2438626040401608, -0.24447900157691721, -0.24491827647558853,
      -0.24517993738777147, -0.24526354529075661, -0.24516871371898807,
      -0.24489510898060141, -0.24444245035893886, -0.24381051029896936,
      -0.24299911457852474, -0.24200814246429245, -0.24083752685248175,
      -0.23948725439410837, -0.23795736560483222, -0.23624795495929574,
      -0.23435917096991427, -0.23229121625006313, -0.23004434756163444,
      -0.2276188758469162, -0.2250151662447632, -0.22223363809103844,
      -0.21927476490329811, -0.21613907434970084, -0.21282714820213702,
      -0.20933962227355893, -0.20567718633951484, -0.20184058404389288,
      -0.19783061278886904, -0.19364812360908273, -0.18929402103004808,
      -0.18476926291082613, -0.18007486027098005, -0.17521187710184677,
      -0.17018143016215809, -0.16498468875805286, -0.15962287450752263,
      -0.15409726108934307, -0.14840917397654269, -0.1425599901544698,
      -0.1365511378235198, -0.13038409608659085, -0.12406039462134558,
      -0.11758161333734465, -0.11094938201815549, -0.10416537994849256,
      -0.0972313355265175, -0.090149025861356175, -0.0829202763559713,
      -0.07554696027546276, -0.0680309983009256, -0.060374358068977646,
      -0.0525790536970587, -0.044647145294653634, -0.036580738460533724,
      -0.02838198376617404, -0.020053076225463123, -0.011596254750866286,
      -0.0030138015961587994, 0.0056919582140968761, 0.014518657468191726,
      0.023463887363866176, 0.03252519811770932, 0.041700099587184028,
      0.050986061905120492, 0.060380516126502651, 0.069880854887369379,
      0.079484433075652852, 0.0891885685137706, 0.098990542652783217,
      0.10888760127792967, 0.11887695522533685, 0.12895578110972403,
      0.13912122206287764, 0.14937038848271211, 0.15970035879269606,
      0.1701081802114407, 0.18059086953222864, 0.19114541391227391,
      0.20176877167148638, 0.21245787310052067, 0.22320962127788085,
      0.23402089289585562, 0.2448885390950469, 0.25580938630725986,
      0.26678023710652204, 0.27779787106797682, 0.28885904563443182,
      0.2999604969902912, 0.31109894094265061, 0.32227107380928105,
      0.33347357331327443, 0.34470309948407346, 0.35595629556464864,
      0.36722978892455505, 0.3785201919786132, 0.38982410311094678,
      0.40113810760412733, 0.41245877857314422, 0.42378267790394386,
      0.43510635719627416, 0.44642635871054887, 0.45773921631848347,
      0.46904145645720829, 0.48032959908660589, 0.49160015864958173,
      0.50284964503500673, 0.51407456454304745, 0.52527142085261058,
      0.53643671599062182, 0.5475669513028667, 0.55865862842610459,
      0.56970825026118965, 0.58071232194690581, 0.5916673518342459,
      0.60256985246085215, 0.6134163415253312, 0.62420334286117762,
      0.63492738741000787, 0.6455850141938384, 0.65617277128612039,
      0.66668721678125753, 0.67712491976232025, 0.68748246126667922,
      0.697756435249288, 0.70794344954331878, 0.71804012681790219,
      0.72804310553266027, 0.73794904088878843, 0.74775460577638808,
      0.757456491717798, 0.76705140980663034, 0.77653609164225756,
      0.78590729025946493, 0.79516178105301982, 0.80429636269687121,
      0.81330785805772232, 0.82219311510271131, 0.83094900780094427,
      0.83957243701860584, 0.84806033140740089, 0.85640964828606347,
      0.8646173745146849, 0.87268052736160029, 0.88059615536259,
      0.88836133917213667, 0.89597319240651385, 0.90342886247843213,
      0.91072553142302848, 0.91786041671494034, 0.92483077207624731,
      0.93163388827502436, 0.93826709391429641, 0.94472775621115423,
      0.95101328176580613, 0.95712111732035621, 0.96304875050707006,
      0.96879371058592945, 0.97435356917124971, 0.97972594094716148,
      0.98490848437174139, 0.98989890236959055, 0.99469494301266337,
      0.99929440018914883, 1.0036951142602104, 1.0078949727043953,
      1.0118919107495254, 1.015683911991897, 1.0192690090025931,
      1.022645283920754, 1.0258108690336167, 1.0287639473431709,
      1.0315027531192591, 1.0340255724389642, 1.0363307437121299,
      1.0384166581928644, 1.0402817604768773, 1.0419245489845046,
      1.0433435764292935, 1.0445374502719988, 1.0455048331598702,
      1.0462444433511009, 1.046755055124317, 1.0470354991729891,
      1.0470846629846535, 1.0469014912048364, 1.0464849859855752,
      1.0458342073184375, 1.0449482733519415, 1.0438263606932943,
      1.0424677046943502, 1.0408715997217195, 1.0390373994109445,
      1.0369645169046704, 1.0346524250747478, 1.0321006567282032,
      1.0293088047970118, 1.0262765225116328, 1.0230035235582471,
      1.0194895822196592, 1.0157345334998213, 1.0117382732319471,
      1.0075007581701867, 1.0030220060648327, 0.99830209572104611,
      0.99334116704107278, 0.98813942104995722, 0.98269711990473274,
      0.9770145868870983, 0.97109220637957583, 0.96493042382516125,
      0.95852974567048888, 0.95189073929251422, 0.94501403290874431,
      0.93790031547104835, 0.93055033654306873, 0.92296490616128568,
      0.9151448946797538, 0.90709123259858471, 0.89880491037619969,
      0.89028697822543312, 0.881538545893524, 0.8725607824260726,
      0.86335491591503488, 0.85392223323082084, 0.84426407973856976,
      0.83438185899870665, 0.824277032451842, 0.8139511190881249,
      0.80340569510113857, 0.79264239352643451, 0.78166290386482173,
      0.77046897169050788, 0.759062398244221, 0.74744504001140477,
      0.73561880828564175, 0.72358566871740126, 0.71134764084826618,
      0.69890679763074515, 0.68626526493384266, 0.67342522103450153,
      0.66038889609507523, 0.64715857162698243, 0.63373657994068788,
      0.620125303582183, 0.60632717475611531, 0.59234467473572949,
      0.57818033325980311, 0.56383672791673811, 0.54931648351599183,
      0.5346222714470098, 0.51975680902587429, 0.50472285882981927,
      0.48952322801983328, 0.47416076765152382, 0.45863837197443424,
      0.44295897772004023, 0.42712556337859442, 0.41114114846505362,
      0.39500879277427176, 0.37873159562568487, 0.3623126950977032,
      0.34575526725202033, 0.32906252534805425, 0.31223771904775366,
      0.29528413361099043, 0.27820508908176395, 0.26100393946543893,
      0.24368407189726282, 0.22624890580238413, 0.2087018920476236,
      0.19104651208521437, 0.1732862770887621, 0.15542472708168148,
      0.13746543005833045, 0.11941198109809506, 0.10126800147268092,
      0.0830371377468507, 0.064723060872869193, 0.046329465278897565,
      0.027860067951585646, 0.0093186075131479335, -0.0092911567068631185,
      -0.027965445604784755, -0.046700461240861774, -0.065492387781741074,
      -0.0843373924472343, -0.10323162646103511, -0.12217122600518777,
      -0.14115231317797589, -0.16017099695503456, -0.17922337415335809,
      -0.19830553039799959, -0.21741354109113964, -0.23654347238330514,
      -0.25569138214643145, -0.27485332094854364, -0.29402533302975092,
      -0.31320345727931442, -0.33238372821350004, -0.35156217695398145,
      -0.37073483220649039, -0.38989772123947608, -0.40904687086248825,
      -0.42817830840403304, -0.44728806268863852, -0.46637216501284728,
      -0.48542665011989139, -0.50444755717277279, -0.52343093072550939,
      -0.54237282169225953, -0.56126928831407175, -0.58011639712301655,
      -0.59891022390343207, -0.61764685465001012, -0.63632238652250261,
      -0.6549329287967568, -0.67347460381186, -0.69194354791311408,
      -0.710335912390615, -0.72864786441316032, -0.74687558795727682,
      -0.76501528473108116, -0.78306317509276846, -0.80101549896345214,
      -0.81886851673415884, -0.83661851016669275, -0.85426178328818136,
      -0.87179466327902277, -0.88921350135405675, -0.90651467363668292,
      -0.92369458202572885, -0.94074965505484076, -0.95767634874415408,
      -0.97447114744406949, -0.99113056467087535, -1.00765114393402,
      -1.0240294595548236, -1.0402621174764379, -1.056345756064812,
      -1.0722770469004881, -1.0880526955610339, -1.1036694423938944,
      -1.1191240632794814, -1.134413370384314, -1.14953421290401,
      -1.1644834777959654, -1.1792580905015222, -1.1938550156574486,
      -1.2082712577965742, -1.222503862037398, -1.2365499147624914,
      -1.2504065442855588, -1.264070921506967, -1.2775402605576165,
      -1.29081181943097, -1.3038829006031145, -1.3167508516406938,
      -1.3294130657965808, -1.3418669825931504, -1.3541100883930028,
      -1.3661399169570283, -1.3779540499896716, -1.3895501176712741,
      -1.4009257991773858, -1.4120788231849168, -1.4230069683650111,
      -1.4337080638625761, -1.444179989762302, -1.454420677541125,
      -1.4644281105070029, -1.4742003242239434, -1.4837354069231523,
      -1.4930314999002765, -1.5020867978985997, -1.510899549478173,
      -1.5194680573707637, -1.5277906788205773, -1.5358658259106912,
      -1.5436919658751311, -1.5512676213965366, -1.5585913708893717,
      -1.5656618487686276, -1.5724777457039731, -1.5790378088593295,
      -1.5853408421178132, -1.5913857062920258, -1.5971713193196817,
      -1.6026966564445175, -1.6079607503824975, -1.6129626914732877,
      -1.6177016278169796, -1.6221767653960837, -1.626387368182765,
      -1.6303327582313445, -1.634012315756052, -1.637425479194069,
      -1.6405717452538486, -1.6434506689487505, -1.6460618636160087,
      -1.6484050009210578, -1.6504798108472478, -1.6522860816709892,
      -1.6538236599223612, -1.6550924503312296, -1.6560924157589181,
      -1.6568235771154918, -1.6572860132626914, -1.6574798609026011,
      -1.6574053144520886, -1.6570626259031005, -1.65645210466887,
      -1.6555741174161263, -1.6544290878833632, -1.6530174966852715,
      -1.651339881103393, -1.6493968348631141, -1.6471890078970615,
      -1.6447171060950203, -1.6419818910404547, -1.6389841797337468,
      -1.6357248443022532, -1.6322048116972825, -1.628425063378123,
      -1.6243866349832208, -1.6200906159886317, -1.6155381493538683,
      -1.6107304311552744, -1.6056687102070493, -1.6003542876700447,
      -1.5947885166484916, -1.5889728017747662, -1.582908598782363,
      -1.5765974140671957, -1.5700408042373826, -1.5632403756516691,
      -1.5561977839466228, -1.5489147335527804, -1.54139297719987,
      -1.5336343154113037, -1.5256405959880737, -1.5174137134822334,
      -1.508955608660119, -1.5002682679554902, -1.4913537229127516,
      -1.4822140496204397, -1.4728513681351325, -1.4632678418959879,
      -1.4534656771300545, -1.4434471222485752, -1.4332144672344267,
      -1.4227700430209229, -1.4121162208621281, -1.4012554116949036,
      -1.3901900654928556, -1.3789226706123834, -1.3674557531310265,
      -1.3557918761783037, -1.3439336392592356, -1.3318836775707499,
      -1.319644661311177, -1.307219294983033, -1.2946103166892826,
      -1.2818204974232952, -1.2688526403526967, -1.2557095800973224,
      -1.2423941820014743, -1.2289093414006842, -1.2152579828832057,
      -1.2014430595464327, -1.1874675522484546, -1.1733344688549512,
      -1.1590468434816625, -1.1446077357326068, -1.1300202299342965,
      -1.1152874343661285, -1.1004124804871935, -1.0853985221596822,
      -1.0702487348691423, -1.0549663149417481, -1.0395544787588442,
      -1.0240164619689438, -1.0083555186974027, -0.99257492075399245,
      -0.97667795683856073, -0.96066793174501275, -0.94454816556381727,
      -0.928321992883254, -0.91199276198958679, -0.89556383406641416,
      -0.879038582393381, -0.86242039154446026, -0.84571265658601646,
      -0.82891878227486993, -0.81204218225654989, -0.79508627826395828,
      -0.77805449931663229, -0.76095028092082961, -0.74377706427062562,
      -0.726538295450234, -0.7092374246377301, -0.69187790531041116,
      -0.67446319345196937, -0.65699674676167363, -0.63948202386575848,
      -0.62192248353123558, -0.60432158388227841, -0.58668278161942233,
      -0.5690095312417206, -0.5513052842720827, -0.53357348848596087,
      -0.5158175871435815, -0.49804101822589536, -0.48024721367443735,
      -0.46243959863526007, -0.4446215907071418, -0.42679659919423762,
      -0.40896802436331431, -0.39113925670581606, -0.37331367620483857,
      -0.3554946516072538, -0.33768553970111792, -0.3198896845985324,
      -0.3021104170241084, -0.28435105360922475, -0.26661489619218881,
      -0.24890523112452226, -0.23122532858342992, -0.21357844189071279,
      -0.19596780683816922, -0.17839664101971017, -0.16086814317027823,
      -0.1433854925117356, -0.12595184810585289, -0.10857034821453176,
      -0.091244109667406953, -0.073976227236926928, -0.056769773021071751,
      -0.039627795833827806, -0.022553320603526938, -0.0055493477791711265,
      0.01138114725512071, 0.028235214757453414, 0.045009931197153463,
      0.061702399815346726, 0.078309751176964773, 0.094829143714115383,
      0.11125776426070132, 0.12759282857819254, 0.14383158187246142,
      0.15997129930158344, 0.17600928647450861, 0.19194287994056169,
      0.20776944766961342, 0.22348638952290889, 0.2390911377144522,
      0.25458115726286423, 0.26995394643365789, 0.28520703717186557,
      0.30033799552493162, 0.31534442205582408, 0.33022395224633116,
      0.34497425689042321, 0.35959304247768981, 0.37407805156677015,
      0.388427063148737, 0.40263789300038655, 0.41670839402740556,
      0.43063645659735017, 0.44442000886244737, 0.4580570170721357,
      0.47154548587534534, 0.48488345861248694, 0.49806901759713096,
      0.51110028438733413, 0.52397542004662745, 0.53669262539461471,
      0.54925014124722049, 0.56164624864651647, 0.57387926908017328,
      0.58594756469049625, 0.59784953847307887, 0.60958363446503749,
      0.62114833792288293, 0.63254217548996461, 0.64376371535359311,
      0.65481156739175594, 0.66568438330951707, 0.676380856765078,
      0.68689972348554285, 0.69723976137239962, 0.707399790596741,
      0.71737867368428254, 0.72717531559016546, 0.73678866376361551,
      0.74621770820248479, 0.75546148149770387, 0.76451905886769378,
      0.77338955818280541, 0.78207213997978475, 0.79056600746635664,
      0.79887040651595564, 0.80698462565268125, 0.81490799602649078,
      0.82263989137874038, 0.83017972799809736, 0.83752696466690213,
      0.84468110259804585, 0.85164168536242457, 0.85840829880704161,
      0.86498057096384384, 0.871358171949333, 0.87754081385506377,
      0.88352825062907947, 0.88932027794838375, 0.89491673308251907,
      0.90031749474833067, 0.90552248295602156, 0.91053165884656084,
      0.91534502452055044, 0.919962622858636, 0.92438453733355286,
      0.92861089181390388, 0.932641850359755, 0.93647761701016541,
      0.94011843556272523, 0.94356458934522158, 0.94681640097953035,
      0.94987423213781574, 0.95273848329117594, 0.95540959345081811,
      0.95788803990186733, 0.96017433792993023, 0.96226904054052,
      0.96417273817143867, 0.96588605839825037, 0.96740966563294239,
      0.96874426081588627, 0.96989058110123116, 0.97084939953582183,
      0.97162152473177288, 0.97220780053281652, 0.97260910567453029,
      0.97282635343857871, 0.97286049130106855, 0.97271250057517,
      0.97238339604808888, 0.97187422561252812, 0.97118606989277578,
      0.9703200418655058, 0.9692772864754533, 0.96805898024606207,
      0.96666633088523524, 0.96510057688632289, 0.96336298712445689,
      0.96145486044836925, 0.95937752526781517, 0.95713233913671736,
      0.95472068833218238, 0.95214398742948669, 0.949403678873177,
      0.94650123254439533, 0.9434381453245777, 0.94021594065563052,
      0.93683616809671932, 0.93330040287779914, 0.929610245450006,
      0.9257673210330396, 0.92177327915966412, 0.91762979321743832,
      0.91333855998782543, 0.90890129918278606, 0.90431975297898126,
      0.89959568554972047, 0.89473088259477151, 0.88972715086814758,
      0.88458631770401186, 0.87931023054080126, 0.87390075644370957,
      0.86835978162564031, 0.86268921096674656, 0.85689096753269378,
      0.85096699209173965, 0.844919242630777, 0.83874969387043818,
      0.83246033677937692, 0.82605317808786416, 0.81953023980078821,
      0.81289355871018543, 0.806145185907426, 0.79928718629513784,
      0.79232163809901335, 0.7852506323795897, 0.7780762725441146,
      0.77080067385861628, 0.76342596296026932, 0.7559542773701875,
      0.74838776500671633, 0.74072858369936223, 0.73297890070344751,
      0.72514089221557931, 0.717216742890072, 0.70920864535637484,
      0.70111879973764679, 0.692949413170554, 0.68470269932638472,
      0.67638087793358781, 0.66798617430182583, 0.6595208188476257,
      0.65098704662174167, 0.642387096838283, 0.63372321240573948,
      0.62499763945995923, 0.61621262689917666, 0.60737042592117818,
      0.59847328956268875, 0.58952347224105173, 0.58052322929829325,
      0.57147481654765109, 0.56238048982263678, 0.55324250452871215,
      0.54406311519766093, 0.5348445750447246, 0.52558913552856579,
      0.516299045914148, 0.50697655283858956, 0.49762389988005967,
      0.48824332712978447, 0.47883707076723231, 0.46940736263853883,
      0.45995642983823171, 0.45048649429431309, 0.44099977235677396,
      0.43149847438957978, 0.4219848043661969, 0.41246095946870065,
      0.40292912969053041, 0.39339149744295249, 0.3838502371652473,
      0.3743075149387054, 0.36476548810446918, 0.35522630488524221,
      0.345692104010954, 0.33616501434839513, 0.32664715453485538,
      0.31714063261583936, 0.30764754568686642, 0.29816997953940932,
      0.28871000831100418, 0.27926969413956038, 0.26985108682190728,
      0.26045622347662784, 0.25108712821116669, 0.24174581179328175,
      0.23243427132685296, 0.22315448993207335, 0.213908436430042,
      0.20469806503180274, 0.19552531503181922, 0.18639211050594356,
      0.17730036001386251, 0.1682519563060729, 0.15924877603537702,
      0.15029267947293784, 0.1413855102288761, 0.13252909497745752,
      0.12372524318687059, 0.11497574685358508, 0.10628238024134246,
      0.097646899624740241, 0.089071043037459247, 0.080556530025111442,
      0.072105061402732179, 0.063718319016907832, 0.055397965512550211,
      0.047145644104314231, 0.038962978352674496, 0.03085157194462778,
      0.022813008479066428, 0.014848851256773626, 0.0069606430750836154,
      -0.000850093972842289, -0.0085818586940918512, -0.016233170987463227,
      -0.023802572030285241, -0.031288624460654127, -0.038689912555038869,
      -0.046005042401309787, -0.053232642067169614, -0.060371361764019249,
      -0.067419874006255945, -0.0743768737660214, -0.0812410786234164,
      -0.088011228912189987, -0.094686087860921614, -0.10126444172971004,
      -0.10774509994238322, -0.11412689521425134, -0.12040868367541493,
      -0.12658934498964852, -0.13266778246887972, -0.13864292318327126,
      -0.14451371806695362, -0.15027914201939158, -0.15593819400243117,
      -0.16148989713304565, -0.16693329877178759, -0.17226747060698563,
      -0.17749150873470135, -0.18260453373446209, -0.18760569074081188,
      -0.192494149510686, -0.19726910448664034, -0.20192977485595895,
      -0.2064754046056711, -0.21090526257348663, -0.21521864249469708,
      -0.21941486304505151, -0.22349326787963192, -0.22745322566777043,
      -0.23129413012401992, -0.23501540003520802, -0.23861647928360344,
      -0.24209683686622258, -0.24545596691029667, -0.24869338868493818,
      -0.25180864660901536, -0.25480131025528796, -0.25767097435080666,
      -0.26041725877361943, -0.26303980854580483, -0.26553829382286609,
      -0.26791240987950071, -0.27016187709180156, -0.27228644091587162,
      -0.27428587186293296, -0.27615996547091248, -0.27790854227256034,
      -0.27953144776011107, -0.28102855234653412, -0.28239975132337847,
      -0.28364496481525875, -0.28476413773099274, -0.28575723971143452,
      -0.28662426507401334, -0.28736523275402426, -0.28798018624267452,
      -0.2884691935219289, -0.28883234699618304, -0.28906976342076729,
      -0.28918158382734055, -0.28916797344617018, -0.28902912162534433,
      -0.28876524174692741, -0.28837657114010018, -0.28786337099128662,
      -0.28722592625132171, -0.28646454553965256, -0.28557956104562809,
      -0.28457132842687771, -0.28344022670481395, -0.2821866581572845,
      -0.28081104820838931, -0.27931384531549341, -0.27769552085345067,
      -0.27595656899607057, -0.27409750659484244, -0.27211887305494187,
      -0.27002123020854674, -0.2678051621854679, -0.26547127528114073,
      -0.26302019782197972, -0.26045258002811444, -0.25776909387354924,
      -0.25497043294374411, -0.25205731229064804, -0.24903046828520359,
      -0.24589065846733615, -0.24263866139346346, -0.23927527648151337,
      -0.23580132385350927, -0.2322176441757059, -0.22852509849631611,
      -0.22472456808083113, -0.22081695424497214, -0.2168031781852616,
      -0.21268418080726956, -0.20846092255150578, -0.20413438321701916,
      -0.19970556178269616, -0.19517547622627845, -0.19054516334111354,
      -0.185815678550673, -0.1809880957208152, -0.17606350696986506,
      -0.17104302247646033, -0.16592777028523914, -0.16071889611034448,
      -0.15541756313677832, -0.15002495181962339, -0.14454225968112222,
      -0.13897070110566839, -0.13331150713268664, -0.12756592524743526,
      -0.12173521916975082, -0.11582066864072836, -0.1098235692073722,
      -0.1037452320052208, -0.09758698353895473, -0.091350165461024688,
      -0.085036134348280293, -0.07864626147664304, -0.07218193259381854,
      -0.065644547690075231, -0.059035520767098879, -0.052356279604920022,
      -0.045608265526961587, -0.038792933163198512, -0.031911750211441756,
      -0.024966197196774106, -0.017957767229142947, -0.010887965759126039,
      -0.003758310331892098, 0.0034296696606458017, 0.010674433229450577,
      0.017974428039752549, 0.025328090664183459, 0.032733846837665476,
      0.040190111714001275, 0.047695290124181541, 0.055247776836369375,
      0.062845956817578527, 0.070488205496984938, 0.0781728890308942,
      0.085898364569316973, 0.093662980524169812, 0.10146507683904964,
      0.10930298526057444, 0.11717502961129481, 0.1250795260641209,
      0.13301478341827266, 0.14097910337672914, 0.14897078082513734,
      0.15698810411220185, 0.16502935533149424, 0.17309281060467319,
      0.18117674036612202, 0.18927940964892961, 0.19739907837224518,
      0.20553400162994762, 0.21368242998063175, 0.22184260973885811,
      0.23001278326768293, 0.23819118927241137, 0.24637606309555776,
      0.25456563701299439, 0.26275814053125607, 0.270951800685978,
      0.27914484234143377, 0.28733548849116075, 0.2955219605596236,
      0.30370247870490763, 0.31187526212239824, 0.32003852934942145,
      0.32819049857082355, 0.33632938792544687, 0.34445341581346772,
      0.352560801204584, 0.360649763947005, 0.36871852507720609,
      0.37676530713042322, 0.38478833445185046, 0.39278583350850987,
      0.4007560332017388, 0.40869716518029525, 0.41660746415399663,
      0.42448516820788973, 0.43232851911690939, 0.44013576266096444,
      0.4479051489404382, 0.45563493269204391, 0.46332337360500109,
      0.47096873663749883, 0.47856929233339052, 0.4861233171390697,
      0.49362909372052388, 0.50108491128046628, 0.5084890658755421,
      0.51583986073354, 0.52313560657058356, 0.5303746219082256,
      0.53755523339043521, 0.54467577610038442, 0.55173459387703827,
      0.558730039631444, 0.56566047566271016, 0.572524273973599,
      0.57931981658570209, 0.58604549585412469, 0.59269971478163874,
      0.59928088733225193, 0.6057874387441311, 0.61221780584182706,
      0.61857043734775341, 0.62484379419285174, 0.63103634982639212,
      0.63714659052485345, 0.643173015699821, 0.64911413820484176,
      0.654968484641193, 0.660734595662485, 0.6664110262780405,
      0.67199634615501547, 0.6774891399191606, 0.68288800745419254,
      0.68819156419970251, 0.69339844144753426, 0.69850728663657691,
      0.70351676364591087, 0.70842555308622912, 0.713232352589486,
      0.71793587709669349, 0.7225348591438181, 0.7270280491456983,
      0.731414215677913, 0.73569214575655861, 0.7398606451158366,
      0.74391853848341549, 0.74786466985347355, 0.75169790275737769,
      0.75541712053190468, 0.759021226584973, 0.76250914465877973,
      0.7658798190903009, 0.76913221506906948, 0.77226531889218353,
      0.7752781382164452, 0.77816970230759508, 0.78093906228654941,
      0.78358529137257471, 0.78610748512335438, 0.78850476167183381,
      0.79077626195981887, 0.7929211499682346, 0.79493861294398049,
      0.79682786162331554, 0.79858813045170218, 0.8002186778000413,
      0.80171878617723147, 0.80308776243897573, 0.80432493799278593,
      0.80542966899909962, 0.80640133656843949, 0.80723934695457045,
      0.807943131743563, 0.808512148038707, 0.80894587864121048,
      0.80924383222661833, 0.80940554351686567, 0.80943057344794456,
      0.80931850933306237, 0.8090689650212729, 0.80868158105150056,
      0.80815602480188808, 0.80749199063440591, 0.8066892000346777,
      0.8057474017469396, 0.80466637190408152, 0.803445914152711,
      0.80208585977318259, 0.80058606779451624, 0.79894642510416858,
      0.79716684655259773, 0.79524727505254278, 0.79318768167298126,
      0.79098806572772173, 0.78864845485852686, 0.78616890511278559,
      0.78354950101561593, 0.78079035563638921, 0.77789161064960277,
      0.77485343639007631, 0.77167603190238254, 0.76835962498450849,
      0.76490447222567748, 0.76131085903828488, 0.75757909968391646,
      0.75370953729340284, 0.74970254388084934, 0.74555852035163639,
      0.74127789650431786, 0.7368611310263965, 0.73230871148393928,
      0.72762115430498631, 0.72279900475673131, 0.71784283691643525,
      0.71275325363604169, 0.70753088650046392, 0.7021763957795224,
      0.6966904703734782, 0.69107382775218251, 0.68532721388778506,
      0.67945140318096464, 0.67344719838071054, 0.66731543049759567,
      0.6610569587105295, 0.6546726702669784, 0.64816348037664417,
      0.64153033209857591, 0.6347741962217246, 0.62789607113888957,
      0.62089698271408655, 0.613777984143323, 0.60654015580877108,
      0.59918460512631444, 0.59171246638651442, 0.5841249005889444,
      0.57642309526994, 0.56860826432372669, 0.56068164781696617,
      0.55264451179670426, 0.5444981480917509, 0.53624387410746843,
      0.52788303261402736, 0.51941699152810761, 0.51084714368807493,
      0.50217490662266151, 0.49340172231313834, 0.48452905694905013,
      0.47555840067748506, 0.46649126734594676, 0.45732919423883334,
      0.44807374180756643, 0.43872649339437914, 0.42928905494983938,
      0.41976305474408415, 0.41015014307186992, 0.40045199195141584,
      0.39067029481713422, 0.38080676620624321, 0.37086314143935273,
      0.360841176295032, 0.35074264667844407, 0.34056934828405805,
      0.33032309625252687, 0.32000572482176859, 0.30961908697231388,
      0.29916505406697536, 0.28864551548489903, 0.27806237825006835,
      0.26741756665430927, 0.25671302187488942, 0.24595070158673946,
      0.23513257956941577, 0.2242606453088406, 0.21333690359390217,
      0.2023633741080029, 0.1913420910156208, 0.1802751025439569,
      0.16916447055978809, 0.15801227014154456, 0.14682058914676532,
      0.13559152777497621, 0.12432719812608109, 0.11302972375438641,
      0.10170123921830523, 0.090343889625881718, 0.078959830176206863,
      0.067551225696810768, 0.056120250177161574, 0.044669086298354366,
      0.033199924959086108, 0.021714964798040109, 0.010216411712759887,
      -0.0012935216248551595, -0.012812616256342974, -0.024338647427627397,
      -0.035869385083054123, -0.04740259436234695, -0.0589360361004011,
      -0.070467467329805883, -0.081994641785949784, -0.093515310414613,
      -0.10502722188191899, -0.11652812308651553, -0.12801575967389325,
      -0.13948787655267506, -0.15094221841277328, -0.1623765302453071,
      -0.17378855786411135, -0.18517604842874014, -0.19653675096882831,
      -0.20786841690966407, -0.21916880059887892, -0.23043565983406969,
      -0.24166675639126931, -0.25285985655409859, -0.26401273164347838,
      -0.27512315854776281, -0.28618892025315323, -0.29720780637426331,
      -0.30817761368469043, -0.31909614664744945, -0.3299612179451451,
      -0.34077064900972653, -0.35152227055168939, -0.36221392308858585,
      -0.3728434574726962, -0.38340873541772186, -0.39390763002436036,
      -0.40433802630461746, -0.41469782170469838, -0.42498492662636445,
      -0.43519726494658006, -0.44533277453533482, -0.455389407771455,
      -0.46536513205631913, -0.47525793032527508, -0.48506580155665469,
      -0.49478676127820709, -0.5044188420708553, -0.51396009406956811,
      -0.52340858546126445, -0.53276240297955713, -0.542019652396233,
      -0.55117845900928608, -0.560236968127404, -0.56919334555071677,
      -0.57804577804772217, -0.58679247382818445, -0.59543166301192052,
      -0.60396159809328731, -0.61238055440127048, -0.62068683055500462,
      -0.62887874891459494, -0.63695465602712265, -0.64491292306765446,
      -0.65275194627516553, -0.66047014738321319, -0.66806597404523249,
      -0.67553790025431781, -0.68288442675737748, -0.69010408146349245,
      -0.697195419846392, -0.70415702534087643, -0.71098750973310132,
      -0.71768551354455024, -0.72424970640962116, -0.730678787446649,
      -0.73697148562229142, -0.74312656010911693, -0.74914280063631156,
      -0.75501902783334918, -0.76075409356654633, -0.76634688126834671,
      -0.7717963062592631, -0.77710131606232835, -0.78226089070997973,
      -0.78727404304324, -0.79213981900309449, -0.79685729791398485,
      -0.80142559275927494, -0.80584385044863449, -0.81011125207719659,
      -0.81422701317643342, -0.81819038395661481, -0.82200064954080254,
      -0.825657130190251, -0.82915918152114731, -0.832506194712592,
      -0.83569759670575494, -0.83873285039410894, -0.84161145480466,
      -0.84433294527011238, -0.84689689359188192, -0.84930290819388465,
      -0.85155063426705679, -0.85363975390448021, -0.85556998622712443,
      -0.85734108750007765, -0.8589528512392518, -0.86040510830847339,
      -0.86169772700693259, -0.86283061314691212, -0.863803710121766,
      -0.86461699896410471, -0.86527049839412429, -0.8657642648580387,
      -0.86609839255661525, -0.866273013463719, -0.86628829733488233,
      -0.86614445170584431, -0.86584172188103892, -0.86538039091201968,
      -0.86476077956575936, -0.863983246282879, -0.86304818712570108,
      -0.8619560357162, -0.86070726316376889, -0.85930237798285736,
      -0.85774192600041377, -0.856026490253198, -0.85415669087490387,
      -0.85213318497314938, -0.84995666649630341, -0.847627866090193,
      -0.84514755094466054, -0.84251652463005111, -0.83973562692359649,
      -0.83680573362573418, -0.83372775636640994, -0.83050264240135641,
      -0.82713137439841256, -0.82361497021390373, -0.81995448265912352,
      -0.81615099925694712, -0.81220564198866851, -0.80811956703102594,
      -0.8038939644835531, -0.79953005808624611, -0.795029104927648,
      -0.79039239514337689, -0.78562125160517882, -0.780717029600559,
      -0.77568111650309535, -0.77051493143344163, -0.76521992491114454,
      -0.75979757849736329, -0.75424940442852606, -0.74857694524101692,
      -0.74278177338702944, -0.73686549084161135, -0.73082972870102592,
      -0.72467614677253067, -0.71840643315563979, -0.71202230381501441,
      -0.70552550214505128, -0.6989177985262669, -0.69220098987364431,
      -0.68537689917697509, -0.67844737503338837, -0.6714142911720935,
      -0.66427954597158212, -0.6570450619692676, -0.6497127853637874,
      -0.64228468551007878, -0.6347627544073261, -0.62714900617991709,
      -0.61944547655158666, -0.61165422231284128, -0.60377732078180724,
      -0.59581686925866018, -0.58777498447378052, -0.57965380202976446,
      -0.57145547583745271, -0.56318217754611111, -0.55483609596796213,
      -0.54641943649715941, -0.53793442052337914, -0.52938328484024222,
      -0.520768281048654, -0.51209167495526353, -0.50335574596619459,
      -0.49456278647623581, -0.48571510125362855, -0.47681500682062516,
      -0.4678648308300366, -0.45886691143787717, -0.44982359667231231,
      -0.44073724379910162, -0.43161021868368354, -0.4224448951501053,
      -0.41324365433695237, -0.40400888405050461, -0.39474297811525449,
      -0.38544833572199988, -0.37612736077367431, -0.36678246122914826,
      -0.35741604844514008, -0.3480305365164168, -0.33862834161456556,
      -0.32921188132540247, -0.31978357398530705, -0.31034583801662086,
      -0.30090109126232, -0.29145175032018056, -0.2820002298765879,
      -0.272548942040181, -0.263100295675614, -0.25365669573751565,
      -0.24422054260489823, -0.2347942314162309, -0.22538015140535572,
      -0.21598068523841349, -0.20659820835200471, -0.19723508829282724,
      -0.18789368405888607, -0.17857634544255302, -0.16928541237564887,
      -0.1600232142767512, -0.15079206940090445, -0.14159428419193276,
      -0.13243215263760122, -0.12330795562773536, -0.11422396031555883,
      -0.10518241948242346, -0.096185570906129544, -0.087235636733022467,
      -0.078334822854035854, -0.069485318284946931, -0.060689294550946668,
      -0.051948905075770851, -0.043266284575550887, -0.034643548457603229,
      -0.026082792224307719, -0.017586090882283516, -0.0091554983570407214,
      -0.00079304691330205068, 0.007499253418852582, 0.015719415411819926,
      0.023865475202089675, 0.031935492845501318, 0.039927552865955354,
      0.047839764797379752, 0.055670263718805041, 0.063417210782384534,
      0.071078793734172668, 0.078653227427485858, 0.086138754328715011,
      0.093533645015403982, 0.1008361986664341, 0.10804474354415276,
      0.11515763746830987, 0.12217326828163275, 0.1290900543068868,
      0.13590644479526878, 0.14262092036599949, 0.14923199343697632,
      0.15573820864630242, 0.16213814326460171, 0.16843040759796868,
      0.17461364538138946, 0.18068653416253902, 0.18664778567580942,
      0.19249614620645794, 0.19823039694470582, 0.20384935432973245,
      0.20935187038340006, 0.21473683303361069, 0.22000316642717352,
      0.22514983123209403, 0.23017582492917155, 0.23508018209276682,
      0.2398619746607103, 0.24452031219319709, 0.24905434212058902,
      0.25346324998004793, 0.25774625964090303, 0.26190263351867377,
      0.26593167277766494, 0.2698327175220484, 0.27360514697538341,
      0.27724837964848581, 0.28076187349557863, 0.28414512605867909,
      0.28739767460014365, 0.29051909622333105, 0.29350900798131629,
      0.29636706697362014, 0.299092970430911, 0.30168645578762132,
      0.30414730074245444, 0.30647532330675853, 0.30867038184070333,
      0.31073237507727436, 0.31266124213403479, 0.31445696251264388,
      0.31611955608611941, 0.31764908307383677, 0.31904564400424185,
      0.32030937966529466, 0.32144047104262008, 0.32243913924540168,
      0.3233056454199974, 0.32404029065129952, 0.32464341585185463,
      0.32511540163877406, 0.325456668198427, 0.32566767513898681,
      0.32574892133082267, 0.32570094473478606, 0.32552432221844696,
      0.32521966936029051, 0.324787640241944, 0.32422892722847496,
      0.32354426073682108, 0.32273440899239808, 0.32180017777395387,
      0.32074241014673976, 0.31956198618405968, 0.31825982267725927,
      0.3168368728342752, 0.31529412596675388, 0.3136326071658932,
      0.31185337696705417, 0.30995753100323969, 0.30794619964754438,
      0.30582054764467831, 0.30358177373163286, 0.30123111024763982,
      0.29876982273350283, 0.29619920952042061, 0.29352060130842628,
      0.29073536073454231, 0.28784488193079871, 0.2848505900722218,
      0.28175394091492639, 0.27855642032446137, 0.27525954379450868,
      0.27186485595611315, 0.26837393007756505, 0.26478836755507795,
      0.26110979739442641, 0.25733987568367506, 0.25348028505718145,
      0.24953273415099803, 0.24549895704984234, 0.24138071272583558,
      0.2371797844691261, 0.23289797931057168, 0.22853712743670027,
      0.22409908159707215, 0.21958571650423858, 0.21499892822648264,
      0.21034063357351324, 0.20561276947532237, 0.20081729235434351,
      0.19595617749114685, 0.19103141838385693, 0.18604502610146015,
      0.18099902863121284, 0.1758954702203723, 0.17073641071240778,
      0.1655239248779263, 0.16026010174049909, 0.15494704389762157,
      0.14958686683697087, 0.14418169824820726, 0.13873367733053485,
      0.13324495409620069, 0.12771768867017194, 0.12215405058620421,
      0.11655621807952435, 0.11092637737631719, 0.10526672198029421,
      0.099579451956486209, 0.093866773212570559, 0.088130896777898038,
      0.082374038080432421, 0.076598416221898252, 0.070806253251314427,
      0.064999773437111191, 0.05918120253814467, 0.053352767073764448,
      0.047516693593194936, 0.041675207944444612, 0.035830534543011536,
      0.029984895640556911, 0.0241405105938355, 0.018299595134065885,
      0.012464360637022914, 0.0066370133940390486, 0.00081975388416152817,
      -0.0049852239522874126, -0.010775733438525115, -0.016549595884289711,
      -0.022304641306719289, -0.02803870914891568, -0.033749648995958365,
      -0.039435321288170261, -0.04509359803133059, -0.050722363503688021,
      -0.056319514959500772, -0.061882963328885876, -0.0674106339137612,
      -0.072900467079608677, -0.078350418942932223, -0.083758462054080524,
      -0.089122586075267463, -0.094440798453564928, -0.099711125088648087,
      -0.10493161099506759, -0.1101003209588088, -0.11521534018799613,
      -0.12027477495744876, -0.12527675324690765, -0.1302194253727425,
      -0.13510096461289958, -0.13991956782489706, -0.14467345605666282,
      -0.14936087515001212, -0.15398009633657306, -0.15852941682593183,
      -0.16300716038584376, -0.16741167791428041, -0.17174134800314658,
      -0.17599457749345579, -0.18016980202178856, -0.18426548655787528,
      -0.18828012593305324, -0.19221224535949125, -0.19606040093997951,
      -0.19982318016808931, -0.20349920241856051, -0.20708711942773542,
      -0.21058561576390011, -0.21399340928730567, -0.21730925159980052,
      -0.22053192848384243, -0.22366026033078665, -0.22669310255826708,
      -0.22962934601654944, -0.23246791738370748, -0.23520777954946637,
      -0.23784793198760273, -0.24038741111676262, -0.24282529064954544,
      -0.24516068192976459, -0.24739273425772926, -0.24952063520347373,
      -0.25154361090775262, -0.25346092637077167, -0.25527188572847737,
      -0.25697583251634065, -0.25857214992054883, -0.26006026101644697,
      -0.26143962899422213, -0.26270975737167745, -0.26387019019403912,
      -0.26492051222072355, -0.26586034909896772, -0.26668936752428651,
      -0.26740727538763692, -0.26801382190928807, -0.26850879775929748,
      -0.26889203516453752, -0.26916340800225869, -0.26932283188010209,
      -0.26937026420254262, -0.26930570422372269, -0.2691291930866393,
      -0.26884081384865388, -0.2684406914933104, -0.26792899292843364,
      -0.26730592697048661, -0.26657174431519837, -0.26572673749442144,
      -0.26477124081924625, -0.26370563030936378, -0.2625303236086694,
      -0.26124577988714826, -0.25985249972902652, -0.25835102500721852,
      -0.25674193874411244, -0.25502586495869189, -0.25320346850004288,
      -0.2512754548672792, -0.24924257001594219, -0.24710560015088776,
      -0.24486537150573923, -0.24252275010895707, -0.24007864153657238,
      -0.23753399065164679, -0.23488978133054839, -0.23214703617608803,
      -0.2293068162176089, -0.22637022059809908, -0.22333838624842417,
      -0.22021248754875614, -0.2169937359772979, -0.21368337974639395,
      -0.21028270342614927, -0.20679302755562706, -0.20321570824176005,
      -0.19955213674608752, -0.19580373905943027, -0.19197197546460937,
      -0.18805834008736766, -0.18406436043560348, -0.17999159692703554,
      -0.17584164240547231, -0.17161612164578938, -0.16731669084778877,
      -0.16294503711907349, -0.15850287794707987, -0.15399196066045437,
      -0.149414061879906, -0.14477098695869572, -0.14006456941296047,
      -0.13529667034200671, -0.13046917783876666, -0.12558400639057438,
      -0.12064309627047723, -0.11564841291922767, -0.11060194631815036,
      -0.1055057103531, -0.10036174216967425, -0.095172101519875374,
      -0.089938870100441159, -0.084664150883025979, -0.079350067436467775,
      -0.073998763241276688, -0.068612400996649392, -0.063193161920155255,
      -0.057743245040323743, -0.052264866482361227, -0.046760258747206795,
      -0.041231669984163111, -0.035681363257301923, -0.030111615805890141,
      -0.024524718299068243, -0.01892297408499008, -0.0133086984346861,
      -0.0076842177808517653, -0.0020518689518415623, 0.0035860015989439276,
      0.0092270385680046918, 0.014868878580775652, 0.020509150974528795,
      0.026145478584883475, 0.031775478535683757, 0.0373967630319791,
      0.043006940155883758, 0.048603614665060912, 0.054184388793552529,
      0.059746863054723223, 0.065288637046090878, 0.070807310255738679,
      0.07630048287006487, 0.081765756582664079, 0.087200735404021026,
      0.092603026471787572, 0.097970240861384117, 0.10329999439666696,
      0.10858990846041845, 0.11383761080434922, 0.11904073635842162,
      0.12419692803920819, 0.12930383755698283, 0.13435912622137544,
      0.13936046574525385, 0.14430553904660556, 0.1491920410481665,
      0.15401767947452927, 0.15878017564648184, 0.16347726527230536,
      0.16810669923579291, 0.17266624438072778, 0.17715368429157063,
      0.18156682007009384, 0.1859034711076992, 0.19016147585323734,
      0.19433869257595618, 0.1984330001234656, 0.20244229867435282,
      0.20636451048529933, 0.21019758063238417, 0.21393947774636204,
      0.21758819474168567, 0.22114174953900778, 0.22459818578092966,
      0.22795557354078794, 0.23121201002419653, 0.23436562026318225,
      0.23741455780258858, 0.2403570053786227, 0.2431911755892544,
      0.24591531155624746, 0.24852768757864654, 0.25102660977745056,
      0.25341041673129394, 0.25567748010289831, 0.25782620525609723,
      0.25985503186323544, 0.26176243450270775, 0.26354692324647833,
      0.26520704423733088, 0.26674138025571675, 0.2681485512759435,
      0.26942721501155353, 0.27057606744972196, 0.27159384337441678,
      0.27247931687825183, 0.27323130186274858, 0.27384865252690671,
      0.27433026384388609, 0.27467507202563324, 0.27488205497531348,
      0.2749502327273402, 0.27487866787491166, 0.27466646598486333,
      0.2743127759996743, 0.27381679062655973, 0.27317774671340433,
      0.272394925611495, 0.27146765352486923, 0.27039530184616328,
      0.26917728747885283, 0.26781307314574221, 0.26630216768361692,
      0.2646441263239222, 0.26283855095937519, 0.26088509039641039,
      0.25878344059335656, 0.25653334488426521, 0.25413459418825624,
      0.25158702720438808, 0.24889053059186855, 0.24604503913559864,
      0.24305053589696651, 0.23990705234980203, 0.23661466850147508,
      0.23317351299902958, 0.22958376322032495, 0.22584564535017809,
      0.22195943444137159, 0.217925454460587, 0.21374407831915535,
      0.20941572788864732, 0.20494087400126063, 0.2003200364349508,
      0.19555378388339278, 0.19064273391062536, 0.18558755289048412,
      0.18038895593078394, 0.175047706782243, 0.16956461773217529,
      0.16394054948295977, 0.15817641101533006, 0.15227315943645045,
      0.14623179981286996, 0.14005338498835398, 0.1337390153866323,
      0.12728983879913813, 0.12070705015772221, 0.11399189129246806,
      0.10714565067463802, 0.10016966314474983, 0.093065309625984916,
      0.085834016822861348, 0.078477256905349513, 0.070996547178426211,
      0.063393449737242508, 0.055669571107929527, 0.047826561874124623,
      0.039866116289414416, 0.031789971875687995, 0.023599909007541664,
      0.01529775048290577, 0.0068853610799032572, -0.0016353528997935518,
      -0.010262444101180379, -0.018993924599371131, -0.027827766396283676,
      -0.036761901930398772, -0.045794224599411182, -0.054922589295672591,
      -0.064144812954209929, -0.073458675113268646, -0.082861918487120545,
      -0.0923522495510129, -0.10192733913811836, -0.11158482304826797,
      -0.12132230266832708, -0.1311373456040138, -0.1410274863229837,
      -0.15099022680904078, -0.16102303722717035, -0.17112335659935055,
      -0.18128859349082213, -0.19151612670669246, -0.20180330599862256,
      -0.21214745278142308, -0.22254586085936853, -0.23299579716193636,
      -0.24349450248882348, -0.25403919226405181, -0.26462705729883074,
      -0.27525526456304894, -0.28592095796512995, -0.29662125914003973,
      -0.30735326824517994, -0.31811406476395376, -0.32890070831678575,
      -0.339710239479325, -0.35053968060758478, -0.36138603666979624,
      -0.37224629608473941, -0.38311743156626143, -0.39399640097373778,
      -0.40488014816827089, -0.41576560387433059, -0.42664968654655883,
      -0.43752930324152373, -0.44840135049416197, -0.45926271519860384,
      -0.47011027549313689, -0.48094090164908077, -0.49175145696325806,
      -0.50253879865380557, -0.513299778759047, -0.52403124503922416,
      -0.53473004188071238, -0.54539301120249861, -0.55601699336467836,
      -0.5665988280786628, -0.57713535531878535, -0.58762341623514536,
      -0.59805985406726314, -0.6084415150584187, -0.61876524937027877,
      -0.62902791199760877, -0.63922636368277341, -0.64935747182973169,
      -0.65941811141726, -0.66940516591114074, -0.67931552817504437,
      -0.68914610137976517, -0.698893799910638, -0.70855555027276085,
      -0.71812829199383466, -0.72760897852426076, -0.73699457813429725,
      -0.74628207480797626, -0.75546846913346666, -0.76455077918969172,
      -0.77352604142886727, -0.78239131155472108, -0.791143665396107,
      -0.79978019977578318, -0.80829803337405837, -0.8166943075870251,
      -0.82496618737919358, -0.83311086213016228, -0.84112554647517723,
      -0.84900748113921443, -0.85675393376441966, -0.8643621997306189,
      -0.87182960296862189, -0.8791534967661111, -0.88633126456586231,
      -0.89336032075603378, -0.90023811145229615, -0.90696211527157466,
      -0.91352984409712257, -0.91993884383477142, -0.926186695160026,
      -0.93227101425586434, -0.93818945354098116, -0.94393970238821978,
      -0.94951948783304652, -0.954926575271762, -0.9601587691493334,
      -0.96521391363653353, -0.9700898932962686, -0.97478463373884117,
      -0.97929610226594721, -0.9836223085032364, -0.98776130502122061,
      -0.9917111879443572, -0.99547009754808125, -0.99903621884366434,
      -1.0024077821506725, -1.0055830636568595, -1.008560385965332,
      -1.0113381186288137, -1.0139146786708526, -1.0162885310937784,
      -1.018458189373312, -1.0204222159396183, -1.0221792226446702,
      -1.0237278712158322, -1.0250668736954234, -1.0261949928662282,
      -1.0271110426627472, -1.0278138885681045, -1.0283024479964755,
      -1.0285756906609189, -1.0286326389265033, -1.0284723681485974,
      -1.0280940069962738, -1.0274967377606592, -1.0266797966481722,
      -1.0256424740585872, -1.0243841148477431, -1.0229041185749637,
      -1.0212019397349543, -1.0192770879741961, -1.017129128291794,
      -1.014757681224618, -1.0121624230167798, -1.0093430857733259,
      -1.0062994575981303, -1.0030313827159538, -0.99953876157858235,
      -0.99582155095509051, -0.99187976400610933, -0.98771347034216372,
      -0.98332279606599682, -0.97870792379889537, -0.97386909269100308,
      -0.96880659841563233, -0.96352079314754513, -0.95801208552524209,
      -0.95228094059722845, -0.94632787975234223, -0.94015348063407356,
      -0.93375837703900211, -0.92714325879928583, -0.92030887164930819,
      -0.91325601707650406, -0.905985552156373, -0.89849838937179438,
      -0.890795496416644, -0.88287789598379829, -0.87474666553762437,
      -0.86640293707087945, -0.85784789684635043, -0.849082785123018,
      -0.840108895867094, -0.83092757644779891, -0.821540227318138,
      -0.81194830168069276, -0.80215330513850014, -0.79215679533125194,
      -0.781960381556759, -0.771565724377924, -0.76097453521529235,
      -0.75018857592529375, -0.73920965836435337, -0.72803964393888354,
      -0.716680443141523, -0.70513401507347162, -0.69340236695331225,
      -0.68148755361233382, -0.66939167697654112, -0.65711688553555248,
      -0.64466537379845756, -0.63203938173686125, -0.619241194215334,
      -0.60627314040928548, -0.59313759321058768, -0.57983696862107981,
      -0.56637372513407913, -0.5527503631042141, -0.53896942410559889,
      -0.52503349027874258, -0.51094518366619035, -0.49670716553725613,
      -0.48232213570198362, -0.46779283181448644, -0.453122028666055,
      -0.43831253746799009, -0.4233672051246557, -0.40828891349671653,
      -0.393080578654969, -0.37774515012491527, -0.36228561012225557,
      -0.3467049727797023, -0.33100628336507371, -0.31519261749124361,
      -0.2992670803178703, -0.283232805745303, -0.26709295560094826,
      -0.25085071881820686, -0.23450931060834695, -0.21807197162546352,
      -0.2015419671248774, -0.18492258611513102, -0.16821714050391934,
      -0.15142896423811569, -0.13456141243826814, -0.1176178605277261,
      -0.10060170335666241, -0.083516354321371916, -0.066365244478932023,
      -0.049151821657640017, -0.03187954956339277, -0.014551906882356795,
      0.002827613619899319, 0.020255506002443472, 0.037728252055981557,
      0.055242322212549905, 0.072794176457582155, 0.090380265244153574,
      0.10799703040904142, 0.125640906090431, 0.14330831964690652,
      0.16099569257751331, 0.17869944144256877, 0.19641597878499087,
      0.21414171405192517, 0.23187305451618462, 0.24960640619755758,
      0.2673381747833759, 0.28506476654835411, 0.30278258927322715,
      0.32048805316202089, 0.33817757175770657, 0.35584756285582664,
      0.37349444941603893, 0.39111466047110566, 0.40870463203323076,
      0.42626080799733757, 0.44377964104112755, 0.46125759352166334,
      0.47869113836806554, 0.49607675997030282, 0.513410955063584,
      0.53069023360827883, 0.54791111966498762, 0.56507015226456436,
      0.58216388627287774, 0.5991888932499686, 0.61614176230340356,
      0.63301910093563751, 0.64981753588505176, 0.66653371396046024,
      0.68316430286888508, 0.69970599203627581, 0.71615549342109475,
      0.73250954232030563, 0.748764898167788, 0.76491834532479874,
      0.780966693862243, 0.79690678033469453, 0.81273546854571987,
      0.82844965030453444, 0.84404624617354462, 0.85952220620677489,
      0.8748745106788518, 0.89010017080433745, 0.90519622944733424,
      0.920159761820981, 0.934987876176871, 0.949677714483961,
      0.9642264530970005, 0.97863130341419069, 0.99288951252388435,
      1.0069983638402074, 1.0209551777274011, 1.0347573121127538,
      1.0484021630878726, 1.0618871654982591, 1.0752097935209175,
      1.0883675612299371, 1.1013580231498308, 1.1141787747965464,
      1.126827453205963, 1.1393017374497563, 1.1515993491385383,
      1.1637180529120477, 1.1756556569164109, 1.1874100132681951,
      1.1989790185052844, 1.210360614024391, 1.2215527865050746,
      1.2325535683202711, 1.2433610379330997, 1.2539733202799983,
      1.2643885871399616, 1.274605057489911, 1.2846209978460545,
      1.2944347225911956, 1.3040445942878707, 1.313449023977324,
      1.3226464714642259, 1.3316354455870194, 1.3404145044739819,
      1.3489822557847877, 1.3573373569376928, 1.3654785153221645,
      1.373404488497018, 1.3811140843740084, 1.3886061613868028,
      1.3958796286453985, 1.4029334460759233, 1.4097666245457885,
      1.4163782259742506, 1.4227673634283287, 1.4289332012041189,
      1.4348749548934667, 1.440591891436078, 1.4460833291570125,
      1.4513486377896645, 1.4563872384841592, 1.4611986038012961,
      1.4657822576920208, 1.4701377754624383, 1.4742647837245184,
      1.4781629603324054, 1.4818320343044966, 1.4852717857312996,
      1.4884820456691428, 1.491462696019777, 1.4942136693960089,
      1.4967349489733581, 1.4990265683278803, 1.5010886112602269,
      1.5029212116059996, 1.5045245530325373, 1.5058988688221993,
      1.5070444416422633, 1.5079616033015415, 1.5086507344938083,
      1.5091122645281767, 1.5093466710465424, 1.5093544797281515,
      1.5091362639815444, 1.5086926446238633, 1.5080242895477625,
      1.5071319133759924, 1.5060162771038392, 1.5046781877295412,
      1.5031184978728136, 1.5013381053816903, 1.4993379529277695,
      1.4971190275900532, 1.4946823604275496, 1.4920290260407825,
      1.4891601421223717, 1.4860768689968944, 1.4827804091501462,
      1.4792720067480147, 1.4755529471451256, 1.4716245563834722,
      1.4674882006811631, 1.4631452859115408, 1.4585972570728032,
      1.4538455977483493, 1.4488918295580455, 1.4437375116006081,
      1.4383842398872897, 1.4328336467671037, 1.4270874003437357,
      1.42114720388443, 1.4150147952209953, 1.4086919461431371,
      1.4021804617844047, 1.395482180000885, 1.3885989707429158,
      1.381532735419978, 1.3742854062590972, 1.366858945656823,
      1.3592553455251632, 1.3514766266315861, 1.3435248379333815,
      1.3354020559065809, 1.3271103838696634, 1.3186519513023234,
      1.3100289131594298, 1.3012434491805553, 1.2922977631951726,
      1.2831940824238186, 1.2739346567754761, 1.2645217581413475,
      1.2549576796853459, 1.2452447351314091, 1.2353852580480496,
      1.2253816011302003, 1.2152361354787153, 1.2049512498777217,
      1.1945293500700584, 1.1839728580310198, 1.1732842112407216,
      1.1624658619552333, 1.1515202764767305, 1.14044993442301,
      1.1292573279964304, 1.1179449612526735, 1.1065153493694517,
      1.0949710179154901, 1.0833145021199144, 1.071548346142374,
      1.0596751023440951, 1.0476973305600372, 1.0356175973725554,
      1.0234384753865202, 1.0111625425064874, 0.99879238121576175,
      0.98633057785787814, 0.97377972192059092, 0.96114240532257778,
      0.94842122170320253, 0.93561876571534841, 0.92273763232182526,
      0.90978041609526261, 0.89674971052194419, 0.883648107309667,
      0.87047819569987994, 0.85724256178431646, 0.84394378782628432,
      0.83058445158690053, 0.81716712565637484, 0.80369437679061573,
      0.79016876525332458, 0.77659284416382046, 0.7629691588506835,
      0.74930024621151992, 0.73558863407898833, 0.72183684059327025,
      0.70804737358117065, 0.69422272994203416, 0.68036539504067783,
      0.66647784210743211, 0.65256253164557132, 0.63862191084623043,
      0.624658413010985, 0.61067445698228062, 0.59667244658183094,
      0.58265477005718824, 0.5686237995366048, 0.55458189049232132,
      0.54053138121249278, 0.526474592281815, 0.51241382607106112,
      0.49835136623559029, 0.484289477223051, 0.47023040379030645,
      0.45617637052980836, 0.44212958140544167, 0.42809221929806252,
      0.41406644556073091, 0.40005439958383754, 0.38605819837021138,
      0.37207993612025814, 0.35812168382731352, 0.34418548888322276,
      0.33027337469430773, 0.31638734030777849, 0.3025293600486178,
      0.28870138316716154, 0.27490533349728297, 0.26114310912538025,
      0.24741658207015754, 0.23372759797330384, 0.22007797580113619,
      0.20646950755716659, 0.19290395800584337, 0.1793830644072556,
      0.1659085362631102, 0.1524820550737695, 0.13910527410660187,
      0.12577981817551231, 0.11250728343179964, 0.0992892371662587,
      0.086127217622642388, 0.073022733822446423, 0.059977265400978308,
      0.046992262454883665, 0.034069145400904943, 0.021209304846072724,
      0.0084141014691932747, -0.0043151340863115673, -0.016977101308241538,
      -0.029570529900204506, -0.04209417985481817, -0.054546841515807076,
      -0.066927335628712337, -0.079234513380566668, -0.09146725642830289,
      -0.10362447691611479, -0.11570511748174725, -0.127708151251739,
      -0.13963258182576191, -0.15147744324998083, -0.16324179997966562,
      -0.17492474683093548, -0.18652540892185077, -0.19804294160284605,
      -0.20947653037662117, -0.22082539080751645, -0.23208876842052695,
      -0.24326593858999507, -0.25435620641804685, -0.26535890660298966,
      -0.27627340329755279, -0.28709908995733791, -0.2978353891793184,
      -0.30848175253071108, -0.31903766036821035, -0.32950262164770705,
      -0.33987617372466883, -0.35015788214523158, -0.36034734042820804,
      -0.37044416983801154, -0.38044801914877974, -0.39035856439971833,
      -0.40017550864182666, -0.40989858167618276, -0.41952753978385954,
      -0.42906216544770109, -0.43850226706599482, -0.44784767865833375,
      -0.45709825956364497, -0.46625389413071894, -0.47531449140123044,
      -0.48427998478556089, -0.49315033173143613, -0.50192551338567548,
      -0.510605534249129, -0.51919042182499076, -0.52768022626070454,
      -0.53607501998353191, -0.54437489733009126, -0.55257997416991678,
      -0.56069038752327949, -0.56870629517346472, -0.57662787527361,
      -0.58445532594838823, -0.592188864890621, -0.59982872895307371,
      -0.60737517373559491, -0.61482847316778055, -0.62218891908737917,
      -0.62945682081456922, -0.636632504722389, -0.6437163138034111,
      -0.65070860723295643, -0.65760975992893234, -0.66442016210860044,
      -0.67114021884236641, -0.67777034960486759, -0.68431098782353184,
      -0.69076258042474492, -0.69712558737793062, -0.70340048123765408,
      -0.70958774668399438, -0.71568788006134954, -0.721701388915897,
      -0.72762879153191906, -0.73347061646714029, -0.73922740208733628,
      -0.74489969610036855, -0.75048805508986416, -0.755993044048725,
      -0.7614152359126769, -0.76675521109405642, -0.77201355701599306,
      -0.77719086764725587, -0.7822877430378713, -0.78730478885578248,
      -0.79224261592469913, -0.79710183976334648, -0.80188308012628484,
      -0.80658696054653467, -0.81121410788012949, -0.81576515185285758,
      -0.82024072460932262, -0.82464146026452667, -0.82896799445818181,
      -0.83322096391188016, -0.83740100598938372, -0.84150875826010751,
      -0.84554485806607849, -0.84950994209247821, -0.8534046459419663,
      -0.857229603712965, -0.86098544758204321, -0.86467280739062136,
      -0.868292310236102, -0.8718445800676381, -0.87533023728669379,
      -0.878749898352515, -0.88210417539273589, -0.88539367581921835,
      -0.88861900194930654, -0.89178075063264339, -0.894879512883686,
      -0.89791587352009039, -0.90089041080705934, -0.90380369610786637,
      -0.90665629354061084, -0.909448759641422, -0.91218164303416249,
      -0.91485548410682549, -0.91747081469472325, -0.92002815777057734,
      -0.92252802714167126, -0.92497092715413154, -0.92735735240450567,
      -0.929687787458687, -0.93196270657836167, -0.93418257345502553,
      -0.93634784095168944, -0.938458950852412, -0.940516333619668,
      -0.94252040815974847, -0.94447158159617284, -0.946370249051306,
      -0.94821679343615939, -0.9500115852485399, -0.95175498237956535,
      -0.95344732992862646, -0.95508896002690147, -0.95668019166942353,
      -0.95822133055582315, -0.95971266893975316, -0.96115448548708071,
      -0.96254704514288747, -0.96389059900731333, -0.96518538422029021,
      -0.96643162385523318, -0.9676295268216637, -0.96877928777684785,
      -0.96988108704646914, -0.97093509055431981, -0.97194144976110208,
      -0.97290030161226437, -0.97381176849498519, -0.97467595820421093,
      -0.97549296391785323, -0.97626286418105579, -0.9769857228995884,
      -0.9776615893423537, -0.97829049815295177, -0.97887246937036343,
      -0.97940750845865954, -0.979895606345771, -0.98033673947125943,
      -0.98073086984307944, -0.98107794510330071, -0.9813778986027184,
      -0.98163064948437939, -0.98183610277591149, -0.98199414949065633,
      -0.98210466673752528, -0.98216751783955292, -0.98218255246104713,
      -0.9821496067433475, -0.98206850344902874, -0.98193905211456944,
      -0.981761049211366, -0.98153427831503126, -0.98125851028289934,
      -0.98093350343963692, -0.98055900377093286, -0.98013474512506682,
      -0.97966044942241859, -0.97913582687265188, -0.97856057619963888,
      -0.97793438487389706, -0.977256929352482, -0.97652787532627761,
      -0.97574687797445248, -0.97491358222610847, -0.97402762302889312,
      -0.97308862562452147, -0.97209620583104661, -0.97104997033179663,
      -0.96994951697080189, -0.968794435054599, -0.96758430566031228,
      -0.9663187019498175, -0.96499718948990254, -0.96361932657822968,
      -0.96218466457503149, -0.96069274824029027, -0.95914311607638092,
      -0.95753530067589665, -0.95586882907459891, -0.95414322310928257,
      -0.95235799978045355, -0.95051267161957542, -0.94860674706081283,
      -0.94663973081707553, -0.944611124260119, -0.94252042580473039,
      -0.94036713129658744, -0.93815073440380392, -0.93587072701194418,
      -0.93352659962223294, -0.93111784175296675, -0.928643942343785,
      -0.92610439016272428, -0.92349867421579424, -0.9208262841590179,
      -0.91808671071260528, -0.915279446077207, -0.91240398435197156,
      -0.90945982195427533, -0.90644645804092139, -0.90336339493063389,
      -0.90021013852763421, -0.89698619874612429, -0.89369108993551749,
      -0.890324331306179, -0.88688544735552854, -0.8833739682942563,
      -0.87978943047259173, -0.87613137680623243, -0.87239935720194639,
      -0.86859292898254981, -0.8647116573110275, -0.8607551156137847,
      -0.85672288600257462, -0.85261455969521671, -0.84842973743461869,
      -0.84416802990613948, -0.839829058152996, -0.835412453989524,
      -0.83091786041216209, -0.82634493200791559 } ;

    DATA_COLLECTION_DW.FromWorkspace2_PWORK.TimePtr = (void *) pTimeValues0;
    DATA_COLLECTION_DW.FromWorkspace2_PWORK.DataPtr = (void *) pDataValues0;
    DATA_COLLECTION_DW.FromWorkspace2_IWORK.PrevIndex = 0;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace1' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06,
      0.07, 0.08, 0.09, 0.1, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18,
      0.19, 0.2, 0.21, 0.22, 0.23, 0.24, 0.25, 0.26, 0.27, 0.28, 0.29, 0.3, 0.31,
      0.32, 0.33, 0.34, 0.35000000000000003, 0.36, 0.37, 0.38, 0.39, 0.4,
      0.41000000000000003, 0.42, 0.43, 0.44, 0.45, 0.46, 0.47000000000000003,
      0.48, 0.49, 0.5, 0.51, 0.52, 0.53, 0.54, 0.55, 0.56, 0.57000000000000006,
      0.58, 0.59, 0.6, 0.61, 0.62, 0.63, 0.64, 0.65, 0.66, 0.67, 0.68,
      0.69000000000000006, 0.70000000000000007, 0.71, 0.72, 0.73, 0.74, 0.75,
      0.76, 0.77, 0.78, 0.79, 0.8, 0.81, 0.82000000000000006,
      0.83000000000000007, 0.84, 0.85, 0.86, 0.87, 0.88, 0.89, 0.9, 0.91, 0.92,
      0.93, 0.94000000000000006, 0.95000000000000007, 0.96, 0.97, 0.98, 0.99,
      1.0, 1.01, 1.02, 1.03, 1.04, 1.05, 1.06, 1.07, 1.08, 1.09, 1.1, 1.11, 1.12,
      1.1300000000000001, 1.1400000000000001, 1.1500000000000001, 1.16, 1.17,
      1.18, 1.19, 1.2, 1.21, 1.22, 1.23, 1.24, 1.25, 1.26, 1.27, 1.28, 1.29, 1.3,
      1.31, 1.32, 1.33, 1.34, 1.35, 1.36, 1.37, 1.3800000000000001,
      1.3900000000000001, 1.4000000000000001, 1.41, 1.42, 1.43, 1.44, 1.45, 1.46,
      1.47, 1.48, 1.49, 1.5, 1.51, 1.52, 1.53, 1.54, 1.55, 1.56, 1.57, 1.58,
      1.59, 1.6, 1.61, 1.62, 1.6300000000000001, 1.6400000000000001,
      1.6500000000000001, 1.6600000000000001, 1.67, 1.68, 1.69, 1.7, 1.71, 1.72,
      1.73, 1.74, 1.75, 1.76, 1.77, 1.78, 1.79, 1.8, 1.81, 1.82, 1.83, 1.84,
      1.85, 1.86, 1.87, 1.8800000000000001, 1.8900000000000001,
      1.9000000000000001, 1.9100000000000001, 1.92, 1.93, 1.94, 1.95, 1.96, 1.97,
      1.98, 1.99, 2.0, 2.0100000000000002, 2.02, 2.0300000000000002, 2.04, 2.05,
      2.06, 2.07, 2.08, 2.09, 2.1, 2.11, 2.12, 2.13, 2.14, 2.15, 2.16, 2.17,
      2.18, 2.19, 2.2, 2.21, 2.22, 2.23, 2.24, 2.25, 2.2600000000000002, 2.27,
      2.2800000000000002, 2.29, 2.3000000000000003, 2.31, 2.32, 2.33, 2.34, 2.35,
      2.36, 2.37, 2.38, 2.39, 2.4, 2.41, 2.42, 2.43, 2.44, 2.45, 2.46, 2.47,
      2.48, 2.49, 2.5, 2.5100000000000002, 2.52, 2.5300000000000002, 2.54,
      2.5500000000000003, 2.56, 2.57, 2.58, 2.59, 2.6, 2.61, 2.62, 2.63, 2.64,
      2.65, 2.66, 2.67, 2.68, 2.69, 2.7, 2.71, 2.72, 2.73, 2.74, 2.75,
      2.7600000000000002, 2.77, 2.7800000000000002, 2.79, 2.8000000000000003,
      2.81, 2.82, 2.83, 2.84, 2.85, 2.86, 2.87, 2.88, 2.89, 2.9, 2.91, 2.92,
      2.93, 2.94, 2.95, 2.96, 2.97, 2.98, 2.99, 3.0, 3.0100000000000002, 3.02,
      3.0300000000000002, 3.04, 3.0500000000000003, 3.06, 3.0700000000000003,
      3.08, 3.09, 3.1, 3.11, 3.12, 3.13, 3.14, 3.15, 3.16, 3.17, 3.18, 3.19, 3.2,
      3.21, 3.22, 3.23, 3.24, 3.25, 3.2600000000000002, 3.27, 3.2800000000000002,
      3.29, 3.3000000000000003, 3.31, 3.3200000000000003, 3.33, 3.34, 3.35, 3.36,
      3.37, 3.38, 3.39, 3.4, 3.41, 3.42, 3.43, 3.44, 3.45, 3.46, 3.47, 3.48,
      3.49, 3.5, 3.5100000000000002, 3.52, 3.5300000000000002, 3.54,
      3.5500000000000003, 3.56, 3.5700000000000003, 3.58, 3.59, 3.6, 3.61, 3.62,
      3.63, 3.64, 3.65, 3.66, 3.67, 3.68, 3.69, 3.7, 3.71, 3.72, 3.73, 3.74,
      3.75, 3.7600000000000002, 3.77, 3.7800000000000002, 3.79,
      3.8000000000000003, 3.81, 3.8200000000000003, 3.83, 3.84, 3.85, 3.86, 3.87,
      3.88, 3.89, 3.9, 3.91, 3.92, 3.93, 3.94, 3.95, 3.96, 3.97, 3.98, 3.99, 4.0,
      4.01, 4.0200000000000005, 4.03, 4.04, 4.05, 4.0600000000000005, 4.07, 4.08,
      4.09, 4.1, 4.11, 4.12, 4.13, 4.14, 4.15, 4.16, 4.17, 4.18, 4.19, 4.2, 4.21,
      4.22, 4.23, 4.24, 4.25, 4.26, 4.2700000000000005, 4.28, 4.29, 4.3,
      4.3100000000000005, 4.32, 4.33, 4.34, 4.3500000000000005, 4.36, 4.37, 4.38,
      4.39, 4.4, 4.41, 4.42, 4.43, 4.44, 4.45, 4.46, 4.47, 4.48, 4.49, 4.5, 4.51,
      4.5200000000000005, 4.53, 4.54, 4.55, 4.5600000000000005, 4.57, 4.58, 4.59,
      4.6000000000000005, 4.61, 4.62, 4.63, 4.64, 4.65, 4.66, 4.67, 4.68, 4.69,
      4.7, 4.71, 4.72, 4.73, 4.74, 4.75, 4.76, 4.7700000000000005, 4.78, 4.79,
      4.8, 4.8100000000000005, 4.82, 4.83, 4.84, 4.8500000000000005, 4.86, 4.87,
      4.88, 4.89, 4.9, 4.91, 4.92, 4.93, 4.94, 4.95, 4.96, 4.97, 4.98, 4.99, 5.0,
      5.01, 5.0200000000000005, 5.03, 5.04, 5.05, 5.0600000000000005, 5.07, 5.08,
      5.09, 5.1000000000000005, 5.11, 5.12, 5.13, 5.14, 5.15, 5.16, 5.17, 5.18,
      5.19, 5.2, 5.21, 5.22, 5.23, 5.24, 5.25, 5.26, 5.2700000000000005, 5.28,
      5.29, 5.3, 5.3100000000000005, 5.32, 5.33, 5.34, 5.3500000000000005, 5.36,
      5.37, 5.38, 5.39, 5.4, 5.41, 5.42, 5.43, 5.44, 5.45, 5.46, 5.47, 5.48,
      5.49, 5.5, 5.51, 5.5200000000000005, 5.53, 5.54, 5.55, 5.5600000000000005,
      5.57, 5.58, 5.59, 5.6000000000000005, 5.61, 5.62, 5.63, 5.64, 5.65, 5.66,
      5.67, 5.68, 5.69, 5.7, 5.71, 5.72, 5.73, 5.74, 5.75, 5.76,
      5.7700000000000005, 5.78, 5.79, 5.8, 5.8100000000000005, 5.82, 5.83, 5.84,
      5.8500000000000005, 5.86, 5.87, 5.88, 5.89, 5.9, 5.91, 5.92, 5.93, 5.94,
      5.95, 5.96, 5.97, 5.98, 5.99, 6.0, 6.01, 6.0200000000000005, 6.03, 6.04,
      6.05, 6.0600000000000005, 6.07, 6.08, 6.09, 6.1000000000000005, 6.11, 6.12,
      6.13, 6.1400000000000006, 6.15, 6.16, 6.17, 6.18, 6.19, 6.2, 6.21, 6.22,
      6.23, 6.24, 6.25, 6.26, 6.2700000000000005, 6.28, 6.29, 6.3,
      6.3100000000000005, 6.32, 6.33, 6.34, 6.3500000000000005, 6.36, 6.37, 6.38,
      6.3900000000000006, 6.4, 6.41, 6.42, 6.43, 6.44, 6.45, 6.46, 6.47, 6.48,
      6.49, 6.5, 6.51, 6.5200000000000005, 6.53, 6.54, 6.55, 6.5600000000000005,
      6.57, 6.58, 6.59, 6.6000000000000005, 6.61, 6.62, 6.63, 6.6400000000000006,
      6.65, 6.66, 6.67, 6.68, 6.69, 6.7, 6.71, 6.72, 6.73, 6.74, 6.75, 6.76,
      6.7700000000000005, 6.78, 6.79, 6.8, 6.8100000000000005, 6.82, 6.83, 6.84,
      6.8500000000000005, 6.86, 6.87, 6.88, 6.8900000000000006, 6.9, 6.91, 6.92,
      6.93, 6.94, 6.95, 6.96, 6.97, 6.98, 6.99, 7.0, 7.01, 7.0200000000000005,
      7.03, 7.04, 7.05, 7.0600000000000005, 7.07, 7.08, 7.09, 7.1000000000000005,
      7.11, 7.12, 7.13, 7.1400000000000006, 7.15, 7.16, 7.17, 7.18, 7.19, 7.2,
      7.21, 7.22, 7.23, 7.24, 7.25, 7.26, 7.2700000000000005, 7.28, 7.29, 7.3,
      7.3100000000000005, 7.32, 7.33, 7.34, 7.3500000000000005, 7.36, 7.37, 7.38,
      7.3900000000000006, 7.4, 7.41, 7.42, 7.43, 7.44, 7.45, 7.46, 7.47, 7.48,
      7.49, 7.5, 7.51, 7.5200000000000005, 7.53, 7.54, 7.55, 7.5600000000000005,
      7.57, 7.58, 7.59, 7.6000000000000005, 7.61, 7.62, 7.63, 7.6400000000000006,
      7.65, 7.66, 7.67, 7.68, 7.69, 7.7, 7.71, 7.72, 7.73, 7.74, 7.75, 7.76,
      7.7700000000000005, 7.78, 7.79, 7.8, 7.8100000000000005, 7.82, 7.83, 7.84,
      7.8500000000000005, 7.86, 7.87, 7.88, 7.8900000000000006, 7.9, 7.91, 7.92,
      7.9300000000000006, 7.94, 7.95, 7.96, 7.97, 7.98, 7.99, 8.0, 8.01, 8.02,
      8.03, 8.0400000000000009, 8.05, 8.06, 8.07, 8.08, 8.09, 8.1, 8.11,
      8.120000000000001, 8.13, 8.14, 8.15, 8.16, 8.17, 8.18, 8.19, 8.2, 8.21,
      8.22, 8.23, 8.24, 8.25, 8.26, 8.27, 8.28, 8.2900000000000009, 8.3, 8.31,
      8.32, 8.33, 8.34, 8.35, 8.36, 8.370000000000001, 8.38, 8.39, 8.4, 8.41,
      8.42, 8.43, 8.44, 8.45, 8.46, 8.47, 8.48, 8.49, 8.5, 8.51, 8.52, 8.53,
      8.5400000000000009, 8.55, 8.56, 8.57, 8.58, 8.59, 8.6, 8.61,
      8.620000000000001, 8.63, 8.64, 8.65, 8.66, 8.67, 8.68, 8.69,
      8.7000000000000011, 8.71, 8.72, 8.73, 8.74, 8.75, 8.76, 8.77, 8.78,
      8.7900000000000009, 8.8, 8.81, 8.82, 8.83, 8.84, 8.85, 8.86,
      8.870000000000001, 8.88, 8.89, 8.9, 8.91, 8.92, 8.93, 8.94,
      8.9500000000000011, 8.96, 8.97, 8.98, 8.99, 9.0, 9.01, 9.02, 9.03,
      9.0400000000000009, 9.05, 9.06, 9.07, 9.08, 9.09, 9.1, 9.11,
      9.120000000000001, 9.13, 9.14, 9.15, 9.16, 9.17, 9.18, 9.19,
      9.2000000000000011, 9.21, 9.22, 9.23, 9.24, 9.25, 9.26, 9.27, 9.28,
      9.2900000000000009, 9.3, 9.31, 9.32, 9.33, 9.34, 9.35, 9.36,
      9.370000000000001, 9.38, 9.39, 9.4, 9.41, 9.42, 9.43, 9.44,
      9.4500000000000011, 9.46, 9.47, 9.48, 9.49, 9.5, 9.51, 9.52, 9.53,
      9.5400000000000009, 9.55, 9.56, 9.57, 9.58, 9.59, 9.6, 9.61,
      9.620000000000001, 9.63, 9.64, 9.65, 9.66, 9.67, 9.68, 9.69,
      9.7000000000000011, 9.71, 9.72, 9.73, 9.74, 9.75, 9.76, 9.77, 9.78,
      9.7900000000000009, 9.8, 9.81, 9.82, 9.83, 9.84, 9.85, 9.86,
      9.870000000000001, 9.88, 9.89, 9.9, 9.91, 9.92, 9.93, 9.94,
      9.9500000000000011, 9.96, 9.97, 9.98, 9.99, 10.0, 10.01, 10.02, 10.03,
      10.040000000000001, 10.05, 10.06, 10.07, 10.08, 10.09, 10.1, 10.11,
      10.120000000000001, 10.13, 10.14, 10.15, 10.16, 10.17, 10.18, 10.19,
      10.200000000000001, 10.21, 10.22, 10.23, 10.24, 10.25, 10.26, 10.27, 10.28,
      10.290000000000001, 10.3, 10.31, 10.32, 10.33, 10.34, 10.35, 10.36,
      10.370000000000001, 10.38, 10.39, 10.4, 10.41, 10.42, 10.43, 10.44,
      10.450000000000001, 10.46, 10.47, 10.48, 10.49, 10.5, 10.51, 10.52, 10.53,
      10.540000000000001, 10.55, 10.56, 10.57, 10.58, 10.59, 10.6, 10.61,
      10.620000000000001, 10.63, 10.64, 10.65, 10.66, 10.67, 10.68, 10.69,
      10.700000000000001, 10.71, 10.72, 10.73, 10.74, 10.75, 10.76, 10.77, 10.78,
      10.790000000000001, 10.8, 10.81, 10.82, 10.83, 10.84, 10.85, 10.86,
      10.870000000000001, 10.88, 10.89, 10.9, 10.91, 10.92, 10.93, 10.94,
      10.950000000000001, 10.96, 10.97, 10.98, 10.99, 11.0, 11.01, 11.02, 11.03,
      11.040000000000001, 11.05, 11.06, 11.07, 11.08, 11.09, 11.1, 11.11,
      11.120000000000001, 11.13, 11.14, 11.15, 11.16, 11.17, 11.18, 11.19,
      11.200000000000001, 11.21, 11.22, 11.23, 11.24, 11.25, 11.26, 11.27, 11.28,
      11.290000000000001, 11.3, 11.31, 11.32, 11.33, 11.34, 11.35, 11.36,
      11.370000000000001, 11.38, 11.39, 11.4, 11.41, 11.42, 11.43, 11.44,
      11.450000000000001, 11.46, 11.47, 11.48, 11.49, 11.5, 11.51, 11.52, 11.53,
      11.540000000000001, 11.55, 11.56, 11.57, 11.58, 11.59, 11.6, 11.61,
      11.620000000000001, 11.63, 11.64, 11.65, 11.66, 11.67, 11.68, 11.69,
      11.700000000000001, 11.71, 11.72, 11.73, 11.74, 11.75, 11.76, 11.77, 11.78,
      11.790000000000001, 11.8, 11.81, 11.82, 11.83, 11.84, 11.85, 11.86,
      11.870000000000001, 11.88, 11.89, 11.9, 11.91, 11.92, 11.93, 11.94,
      11.950000000000001, 11.96, 11.97, 11.98, 11.99, 12.0, 12.01, 12.02,
      12.030000000000001, 12.040000000000001, 12.05, 12.06, 12.07, 12.08, 12.09,
      12.1, 12.11, 12.120000000000001, 12.13, 12.14, 12.15, 12.16, 12.17, 12.18,
      12.19, 12.200000000000001, 12.21, 12.22, 12.23, 12.24, 12.25, 12.26, 12.27,
      12.280000000000001, 12.290000000000001, 12.3, 12.31, 12.32, 12.33, 12.34,
      12.35, 12.36, 12.370000000000001, 12.38, 12.39, 12.4, 12.41, 12.42, 12.43,
      12.44, 12.450000000000001, 12.46, 12.47, 12.48, 12.49, 12.5, 12.51, 12.52,
      12.530000000000001, 12.540000000000001, 12.55, 12.56, 12.57, 12.58, 12.59,
      12.6, 12.61, 12.620000000000001, 12.63, 12.64, 12.65, 12.66, 12.67, 12.68,
      12.69, 12.700000000000001, 12.71, 12.72, 12.73, 12.74, 12.75, 12.76, 12.77,
      12.780000000000001, 12.790000000000001, 12.8, 12.81, 12.82, 12.83, 12.84,
      12.85, 12.86, 12.870000000000001, 12.88, 12.89, 12.9, 12.91, 12.92, 12.93,
      12.94, 12.950000000000001, 12.96, 12.97, 12.98, 12.99, 13.0, 13.01, 13.02,
      13.030000000000001, 13.040000000000001, 13.05, 13.06, 13.07, 13.08, 13.09,
      13.1, 13.11, 13.120000000000001, 13.13, 13.14, 13.15, 13.16, 13.17, 13.18,
      13.19, 13.200000000000001, 13.21, 13.22, 13.23, 13.24, 13.25, 13.26, 13.27,
      13.280000000000001, 13.290000000000001, 13.3, 13.31, 13.32, 13.33, 13.34,
      13.35, 13.36, 13.370000000000001, 13.38, 13.39, 13.4, 13.41, 13.42, 13.43,
      13.44, 13.450000000000001, 13.46, 13.47, 13.48, 13.49, 13.5, 13.51, 13.52,
      13.530000000000001, 13.540000000000001, 13.55, 13.56, 13.57, 13.58, 13.59,
      13.6, 13.61, 13.620000000000001, 13.63, 13.64, 13.65, 13.66, 13.67, 13.68,
      13.69, 13.700000000000001, 13.71, 13.72, 13.73, 13.74, 13.75, 13.76, 13.77,
      13.780000000000001, 13.790000000000001, 13.8, 13.81, 13.82, 13.83, 13.84,
      13.85, 13.86, 13.870000000000001, 13.88, 13.89, 13.9, 13.91, 13.92, 13.93,
      13.94, 13.950000000000001, 13.96, 13.97, 13.98, 13.99, 14.0, 14.01, 14.02,
      14.030000000000001, 14.040000000000001, 14.05, 14.06, 14.07, 14.08, 14.09,
      14.1, 14.11, 14.120000000000001, 14.13, 14.14, 14.15, 14.16, 14.17, 14.18,
      14.19, 14.200000000000001, 14.21, 14.22, 14.23, 14.24, 14.25, 14.26, 14.27,
      14.280000000000001, 14.290000000000001, 14.3, 14.31, 14.32, 14.33, 14.34,
      14.35, 14.36, 14.370000000000001, 14.38, 14.39, 14.4, 14.41, 14.42, 14.43,
      14.44, 14.450000000000001, 14.46, 14.47, 14.48, 14.49, 14.5, 14.51, 14.52,
      14.530000000000001, 14.540000000000001, 14.55, 14.56, 14.57, 14.58, 14.59,
      14.6, 14.61, 14.620000000000001, 14.63, 14.64, 14.65, 14.66, 14.67, 14.68,
      14.69, 14.700000000000001, 14.71, 14.72, 14.73, 14.74, 14.75, 14.76, 14.77,
      14.780000000000001, 14.790000000000001, 14.8, 14.81, 14.82, 14.83, 14.84,
      14.85, 14.86, 14.870000000000001, 14.88, 14.89, 14.9, 14.91, 14.92, 14.93,
      14.94, 14.950000000000001, 14.96, 14.97, 14.98, 14.99, 15.0, 15.01, 15.02,
      15.030000000000001, 15.040000000000001, 15.05, 15.06, 15.07, 15.08, 15.09,
      15.1, 15.11, 15.120000000000001, 15.13, 15.14, 15.15, 15.16, 15.17, 15.18,
      15.19, 15.200000000000001, 15.21, 15.22, 15.23, 15.24, 15.25, 15.26, 15.27,
      15.280000000000001, 15.290000000000001, 15.3, 15.31, 15.32, 15.33, 15.34,
      15.35, 15.36, 15.370000000000001, 15.38, 15.39, 15.4, 15.41, 15.42, 15.43,
      15.44, 15.450000000000001, 15.46, 15.47, 15.48, 15.49, 15.5, 15.51, 15.52,
      15.530000000000001, 15.540000000000001, 15.55, 15.56, 15.57, 15.58, 15.59,
      15.6, 15.610000000000001, 15.620000000000001, 15.63, 15.64, 15.65, 15.66,
      15.67, 15.68, 15.69, 15.700000000000001, 15.71, 15.72, 15.73, 15.74, 15.75,
      15.76, 15.77, 15.780000000000001, 15.790000000000001, 15.8, 15.81, 15.82,
      15.83, 15.84, 15.85, 15.860000000000001, 15.870000000000001, 15.88, 15.89,
      15.9, 15.91, 15.92, 15.93, 15.94, 15.950000000000001, 15.96, 15.97, 15.98,
      15.99, 16.0, 16.01, 16.02, 16.03, 16.04, 16.05, 16.06, 16.07,
      16.080000000000002, 16.09, 16.1, 16.11, 16.12, 16.13, 16.14, 16.15, 16.16,
      16.17, 16.18, 16.19, 16.2, 16.21, 16.22, 16.23, 16.240000000000002, 16.25,
      16.26, 16.27, 16.28, 16.29, 16.3, 16.31, 16.32, 16.330000000000002, 16.34,
      16.35, 16.36, 16.37, 16.38, 16.39, 16.4, 16.41, 16.42, 16.43, 16.44, 16.45,
      16.46, 16.47, 16.48, 16.490000000000002, 16.5, 16.51, 16.52, 16.53, 16.54,
      16.55, 16.56, 16.57, 16.580000000000002, 16.59, 16.6, 16.61, 16.62, 16.63,
      16.64, 16.65, 16.66, 16.67, 16.68, 16.69, 16.7, 16.71, 16.72, 16.73,
      16.740000000000002, 16.75, 16.76, 16.77, 16.78, 16.79, 16.8, 16.81, 16.82,
      16.830000000000002, 16.84, 16.85, 16.86, 16.87, 16.88, 16.89, 16.9, 16.91,
      16.92, 16.93, 16.94, 16.95, 16.96, 16.97, 16.98, 16.990000000000002, 17.0,
      17.01, 17.02, 17.03, 17.04, 17.05, 17.06, 17.07, 17.080000000000002, 17.09,
      17.1, 17.11, 17.12, 17.13, 17.14, 17.150000000000002, 17.16, 17.17, 17.18,
      17.19, 17.2, 17.21, 17.22, 17.23, 17.240000000000002, 17.25, 17.26, 17.27,
      17.28, 17.29, 17.3, 17.31, 17.32, 17.330000000000002, 17.34, 17.35, 17.36,
      17.37, 17.38, 17.39, 17.400000000000002, 17.41, 17.42, 17.43, 17.44, 17.45,
      17.46, 17.47, 17.48, 17.490000000000002, 17.5, 17.51, 17.52, 17.53, 17.54,
      17.55, 17.56, 17.57, 17.580000000000002, 17.59, 17.6, 17.61, 17.62, 17.63,
      17.64, 17.650000000000002, 17.66, 17.67, 17.68, 17.69, 17.7, 17.71, 17.72,
      17.73, 17.740000000000002, 17.75, 17.76, 17.77, 17.78, 17.79, 17.8, 17.81,
      17.82, 17.830000000000002, 17.84, 17.85, 17.86, 17.87, 17.88, 17.89,
      17.900000000000002, 17.91, 17.92, 17.93, 17.94, 17.95, 17.96, 17.97, 17.98,
      17.990000000000002, 18.0, 18.01, 18.02, 18.03, 18.04, 18.05, 18.06, 18.07,
      18.080000000000002, 18.09, 18.1, 18.11, 18.12, 18.13, 18.14,
      18.150000000000002, 18.16, 18.17, 18.18, 18.19, 18.2, 18.21, 18.22, 18.23,
      18.240000000000002, 18.25, 18.26, 18.27, 18.28, 18.29, 18.3, 18.31, 18.32,
      18.330000000000002, 18.34, 18.35, 18.36, 18.37, 18.38, 18.39,
      18.400000000000002, 18.41, 18.42, 18.43, 18.44, 18.45, 18.46, 18.47, 18.48,
      18.490000000000002, 18.5, 18.51, 18.52, 18.53, 18.54, 18.55, 18.56, 18.57,
      18.580000000000002, 18.59, 18.6, 18.61, 18.62, 18.63, 18.64,
      18.650000000000002, 18.66, 18.67, 18.68, 18.69, 18.7, 18.71, 18.72, 18.73,
      18.740000000000002, 18.75, 18.76, 18.77, 18.78, 18.79, 18.8, 18.81, 18.82,
      18.830000000000002, 18.84, 18.85, 18.86, 18.87, 18.88, 18.89,
      18.900000000000002, 18.91, 18.92, 18.93, 18.94, 18.95, 18.96, 18.97, 18.98,
      18.990000000000002, 19.0, 19.01, 19.02, 19.03, 19.04, 19.05, 19.06, 19.07,
      19.080000000000002, 19.09, 19.1, 19.11, 19.12, 19.13, 19.14,
      19.150000000000002, 19.16, 19.17, 19.18, 19.19, 19.2, 19.21, 19.22, 19.23,
      19.240000000000002, 19.25, 19.26, 19.27, 19.28, 19.29, 19.3, 19.31, 19.32,
      19.330000000000002, 19.34, 19.35, 19.36, 19.37, 19.38, 19.39,
      19.400000000000002, 19.41, 19.42, 19.43, 19.44, 19.45, 19.46, 19.47, 19.48,
      19.490000000000002, 19.5, 19.51, 19.52, 19.53, 19.54, 19.55, 19.56, 19.57,
      19.580000000000002, 19.59, 19.6, 19.61, 19.62, 19.63, 19.64,
      19.650000000000002, 19.66, 19.67, 19.68, 19.69, 19.7, 19.71, 19.72, 19.73,
      19.740000000000002, 19.75, 19.76, 19.77, 19.78, 19.79, 19.8, 19.81, 19.82,
      19.830000000000002, 19.84, 19.85, 19.86, 19.87, 19.88, 19.89,
      19.900000000000002, 19.91, 19.92, 19.93, 19.94, 19.95, 19.96, 19.97, 19.98,
      19.990000000000002, 20.0, 20.01, 20.02, 20.03, 20.04, 20.05, 20.06, 20.07,
      20.080000000000002, 20.09, 20.1, 20.11, 20.12, 20.13, 20.14,
      20.150000000000002, 20.16, 20.17, 20.18, 20.19, 20.2, 20.21, 20.22, 20.23,
      20.240000000000002, 20.25, 20.26, 20.27, 20.28, 20.29, 20.3, 20.31, 20.32,
      20.330000000000002, 20.34, 20.35, 20.36, 20.37, 20.38, 20.39,
      20.400000000000002, 20.41, 20.42, 20.43, 20.44, 20.45, 20.46, 20.47, 20.48,
      20.490000000000002, 20.5, 20.51, 20.52, 20.53, 20.54, 20.55, 20.56, 20.57,
      20.580000000000002, 20.59, 20.6, 20.61, 20.62, 20.63, 20.64,
      20.650000000000002, 20.66, 20.67, 20.68, 20.69, 20.7, 20.71, 20.72, 20.73,
      20.740000000000002, 20.75, 20.76, 20.77, 20.78, 20.79, 20.8, 20.81, 20.82,
      20.830000000000002, 20.84, 20.85, 20.86, 20.87, 20.88, 20.89,
      20.900000000000002, 20.91, 20.92, 20.93, 20.94, 20.95, 20.96, 20.97, 20.98,
      20.990000000000002, 21.0, 21.01, 21.02, 21.03, 21.04, 21.05, 21.06, 21.07,
      21.080000000000002, 21.09, 21.1, 21.11, 21.12, 21.13, 21.14,
      21.150000000000002, 21.16, 21.17, 21.18, 21.19, 21.2, 21.21, 21.22, 21.23,
      21.240000000000002, 21.25, 21.26, 21.27, 21.28, 21.29, 21.3, 21.31, 21.32,
      21.330000000000002, 21.34, 21.35, 21.36, 21.37, 21.38, 21.39,
      21.400000000000002, 21.41, 21.42, 21.43, 21.44, 21.45, 21.46, 21.47, 21.48,
      21.490000000000002, 21.5, 21.51, 21.52, 21.53, 21.54, 21.55, 21.56, 21.57,
      21.580000000000002, 21.59, 21.6, 21.61, 21.62, 21.63, 21.64,
      21.650000000000002, 21.66, 21.67, 21.68, 21.69, 21.7, 21.71, 21.72, 21.73,
      21.740000000000002, 21.75, 21.76, 21.77, 21.78, 21.79, 21.8, 21.81, 21.82,
      21.830000000000002, 21.84, 21.85, 21.86, 21.87, 21.88, 21.89,
      21.900000000000002, 21.91, 21.92, 21.93, 21.94, 21.95, 21.96, 21.97, 21.98,
      21.990000000000002, 22.0, 22.01, 22.02, 22.03, 22.04, 22.05, 22.06, 22.07,
      22.080000000000002, 22.09, 22.1, 22.11, 22.12, 22.13, 22.14,
      22.150000000000002, 22.16, 22.17, 22.18, 22.19, 22.2, 22.21, 22.22, 22.23,
      22.240000000000002, 22.25, 22.26, 22.27, 22.28, 22.29, 22.3, 22.31, 22.32,
      22.330000000000002, 22.34, 22.35, 22.36, 22.37, 22.38, 22.39,
      22.400000000000002, 22.41, 22.42, 22.43, 22.44, 22.45, 22.46, 22.47, 22.48,
      22.490000000000002, 22.5, 22.51, 22.52, 22.53, 22.54, 22.55, 22.56, 22.57,
      22.580000000000002, 22.59, 22.6, 22.61, 22.62, 22.63, 22.64,
      22.650000000000002, 22.66, 22.67, 22.68, 22.69, 22.7, 22.71, 22.72, 22.73,
      22.740000000000002, 22.75, 22.76, 22.77, 22.78, 22.79, 22.8, 22.81, 22.82,
      22.830000000000002, 22.84, 22.85, 22.86, 22.87, 22.88, 22.89,
      22.900000000000002, 22.91, 22.92, 22.93, 22.94, 22.95, 22.96, 22.97, 22.98,
      22.990000000000002, 23.0, 23.01, 23.02, 23.03, 23.04, 23.05, 23.06, 23.07,
      23.080000000000002, 23.09, 23.1, 23.11, 23.12, 23.13, 23.14,
      23.150000000000002, 23.16, 23.17, 23.18, 23.19, 23.2, 23.21, 23.22, 23.23,
      23.240000000000002, 23.25, 23.26, 23.27, 23.28, 23.29, 23.3, 23.31, 23.32,
      23.330000000000002, 23.34, 23.35, 23.36, 23.37, 23.38, 23.39,
      23.400000000000002, 23.41, 23.42, 23.43, 23.44, 23.45, 23.46, 23.47, 23.48,
      23.490000000000002, 23.5, 23.51, 23.52, 23.53, 23.54, 23.55, 23.56, 23.57,
      23.580000000000002, 23.59, 23.6, 23.61, 23.62, 23.63, 23.64,
      23.650000000000002, 23.66, 23.67, 23.68, 23.69, 23.7, 23.71, 23.72, 23.73,
      23.740000000000002, 23.75, 23.76, 23.77, 23.78, 23.79, 23.8, 23.81, 23.82,
      23.830000000000002, 23.84, 23.85, 23.86, 23.87, 23.88, 23.89,
      23.900000000000002, 23.91, 23.92, 23.93, 23.94, 23.95, 23.96, 23.97, 23.98,
      23.990000000000002, 24.0, 24.01, 24.02, 24.03, 24.04, 24.05,
      24.060000000000002, 24.07, 24.080000000000002, 24.09, 24.1, 24.11, 24.12,
      24.13, 24.14, 24.150000000000002, 24.16, 24.17, 24.18, 24.19, 24.2, 24.21,
      24.22, 24.23, 24.240000000000002, 24.25, 24.26, 24.27, 24.28, 24.29, 24.3,
      24.310000000000002, 24.32, 24.330000000000002, 24.34, 24.35, 24.36, 24.37,
      24.38, 24.39, 24.400000000000002, 24.41, 24.42, 24.43, 24.44, 24.45, 24.46,
      24.47, 24.48, 24.490000000000002, 24.5, 24.51, 24.52, 24.53, 24.54, 24.55,
      24.560000000000002, 24.57, 24.580000000000002, 24.59, 24.6, 24.61, 24.62,
      24.63, 24.64, 24.650000000000002, 24.66, 24.67, 24.68, 24.69, 24.7, 24.71,
      24.72, 24.73, 24.740000000000002, 24.75, 24.76, 24.77, 24.78, 24.79, 24.8,
      24.810000000000002, 24.82, 24.830000000000002, 24.84, 24.85, 24.86, 24.87,
      24.88, 24.89, 24.900000000000002, 24.91, 24.92, 24.93, 24.94, 24.95, 24.96,
      24.97, 24.98, 24.990000000000002, 25.0, 25.01, 25.02, 25.03, 25.04, 25.05,
      25.060000000000002, 25.07, 25.080000000000002, 25.09, 25.1, 25.11, 25.12,
      25.13, 25.14, 25.150000000000002, 25.16, 25.17, 25.18, 25.19, 25.2, 25.21,
      25.22, 25.23, 25.240000000000002, 25.25, 25.26, 25.27, 25.28, 25.29, 25.3,
      25.310000000000002, 25.32, 25.330000000000002, 25.34, 25.35, 25.36, 25.37,
      25.38, 25.39, 25.400000000000002, 25.41, 25.42, 25.43, 25.44, 25.45, 25.46,
      25.47, 25.48, 25.490000000000002, 25.5, 25.51, 25.52, 25.53, 25.54, 25.55,
      25.560000000000002, 25.57, 25.580000000000002, 25.59, 25.6, 25.61, 25.62,
      25.63, 25.64, 25.650000000000002, 25.66, 25.67, 25.68, 25.69, 25.7, 25.71,
      25.72, 25.73, 25.740000000000002, 25.75, 25.76, 25.77, 25.78, 25.79, 25.8,
      25.810000000000002, 25.82, 25.830000000000002, 25.84, 25.85, 25.86, 25.87,
      25.88, 25.89, 25.900000000000002, 25.91, 25.92, 25.93, 25.94, 25.95, 25.96,
      25.97, 25.98, 25.990000000000002, 26.0, 26.01, 26.02, 26.03, 26.04, 26.05,
      26.060000000000002, 26.07, 26.080000000000002, 26.09, 26.1, 26.11, 26.12,
      26.13, 26.14, 26.150000000000002, 26.16, 26.17, 26.18, 26.19, 26.2, 26.21,
      26.22, 26.23, 26.240000000000002, 26.25, 26.26, 26.27, 26.28, 26.29, 26.3,
      26.310000000000002, 26.32, 26.330000000000002, 26.34, 26.35, 26.36, 26.37,
      26.38, 26.39, 26.400000000000002, 26.41, 26.42, 26.43, 26.44, 26.45, 26.46,
      26.47, 26.48, 26.490000000000002, 26.5, 26.51, 26.52, 26.53, 26.54, 26.55,
      26.560000000000002, 26.57, 26.580000000000002, 26.59, 26.6, 26.61, 26.62,
      26.63, 26.64, 26.650000000000002, 26.66, 26.67, 26.68, 26.69, 26.7, 26.71,
      26.72, 26.73, 26.740000000000002, 26.75, 26.76, 26.77, 26.78, 26.79, 26.8,
      26.810000000000002, 26.82, 26.830000000000002, 26.84, 26.85, 26.86, 26.87,
      26.88, 26.89, 26.900000000000002, 26.91, 26.92, 26.93, 26.94, 26.95, 26.96,
      26.97, 26.98, 26.990000000000002, 27.0, 27.01, 27.02, 27.03, 27.04, 27.05,
      27.060000000000002, 27.07, 27.080000000000002, 27.09, 27.1, 27.11, 27.12,
      27.13, 27.14, 27.150000000000002, 27.16, 27.17, 27.18, 27.19, 27.2, 27.21,
      27.22, 27.23, 27.240000000000002, 27.25, 27.26, 27.27, 27.28, 27.29, 27.3,
      27.310000000000002, 27.32, 27.330000000000002, 27.34, 27.35, 27.36, 27.37,
      27.38, 27.39, 27.400000000000002, 27.41, 27.42, 27.43, 27.44, 27.45, 27.46,
      27.47, 27.48, 27.490000000000002, 27.5, 27.51, 27.52, 27.53, 27.54, 27.55,
      27.560000000000002, 27.57, 27.580000000000002, 27.59, 27.6, 27.61, 27.62,
      27.63, 27.64, 27.650000000000002, 27.66, 27.67, 27.68, 27.69, 27.7, 27.71,
      27.72, 27.73, 27.740000000000002, 27.75, 27.76, 27.77, 27.78, 27.79, 27.8,
      27.810000000000002, 27.82, 27.830000000000002, 27.84, 27.85, 27.86, 27.87,
      27.88, 27.89, 27.900000000000002, 27.91, 27.92, 27.93, 27.94, 27.95, 27.96,
      27.97, 27.98, 27.990000000000002, 28.0, 28.01, 28.02, 28.03, 28.04, 28.05,
      28.060000000000002, 28.07, 28.080000000000002, 28.09, 28.1, 28.11, 28.12,
      28.13, 28.14, 28.150000000000002, 28.16, 28.17, 28.18, 28.19, 28.2, 28.21,
      28.22, 28.23, 28.240000000000002, 28.25, 28.26, 28.27, 28.28, 28.29, 28.3,
      28.310000000000002, 28.32, 28.330000000000002, 28.34, 28.35, 28.36, 28.37,
      28.38, 28.39, 28.400000000000002, 28.41, 28.42, 28.43, 28.44, 28.45, 28.46,
      28.47, 28.48, 28.490000000000002, 28.5, 28.51, 28.52, 28.53, 28.54, 28.55,
      28.560000000000002, 28.57, 28.580000000000002, 28.59, 28.6, 28.61, 28.62,
      28.63, 28.64, 28.650000000000002, 28.66, 28.67, 28.68, 28.69, 28.7, 28.71,
      28.72, 28.73, 28.740000000000002, 28.75, 28.76, 28.77, 28.78, 28.79, 28.8,
      28.810000000000002, 28.82, 28.830000000000002, 28.84, 28.85, 28.86, 28.87,
      28.88, 28.89, 28.900000000000002, 28.91, 28.92, 28.93, 28.94, 28.95, 28.96,
      28.97, 28.98, 28.990000000000002, 29.0, 29.01, 29.02, 29.03, 29.04, 29.05,
      29.060000000000002, 29.07, 29.080000000000002, 29.09, 29.1, 29.11, 29.12,
      29.13, 29.14, 29.150000000000002, 29.16, 29.17, 29.18, 29.19, 29.2, 29.21,
      29.22, 29.23, 29.240000000000002, 29.25, 29.26, 29.27, 29.28, 29.29, 29.3,
      29.310000000000002, 29.32, 29.330000000000002, 29.34, 29.35, 29.36, 29.37,
      29.38, 29.39, 29.400000000000002, 29.41, 29.42, 29.43, 29.44, 29.45, 29.46,
      29.47, 29.48, 29.490000000000002, 29.5, 29.51, 29.52, 29.53, 29.54, 29.55,
      29.560000000000002, 29.57, 29.580000000000002, 29.59, 29.6, 29.61, 29.62,
      29.63, 29.64, 29.650000000000002, 29.66, 29.67, 29.68, 29.69, 29.7, 29.71,
      29.72, 29.73, 29.740000000000002, 29.75, 29.76, 29.77, 29.78, 29.79, 29.8,
      29.810000000000002, 29.82, 29.830000000000002, 29.84, 29.85, 29.86, 29.87,
      29.88, 29.89, 29.900000000000002, 29.91, 29.92, 29.93, 29.94, 29.95, 29.96,
      29.97, 29.98, 29.990000000000002 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 1.0945392870194164, 1.0913413068957425, 1.0880225369727905,
      1.0845843187825481, 1.081028018149347, 1.0773550247950163,
      1.0735667519369676, 1.0696646358793194, 1.0656501355971926,
      1.0615247323142971, 1.0572899290739339, 1.0529472503035451,
      1.0484982413729353, 1.0439444681463113, 1.0392875165282549,
      1.0345289920037855, 1.0296705191726361, 1.0247137412778953,
      1.0196603197291492, 1.0145119336202753, 1.0092702792420265,
      1.003937069589564, 0.99851403386508242, 0.99300291697567877,
      0.98740547902662135, 0.98172349481017529, 0.97595875329013537,
      0.97011305708223039, 0.964188221930557, 0.95818607618020035,
      0.95210846024620854, 0.945957226079085, 0.93973423662695432,
      0.93344136529458632, 0.92708049539942017, 0.92065351962478337,
      0.91416233947045178, 0.90760886470073809, 0.90099501279026928,
      0.89432270836762762, 0.88759388265703387, 0.88081047291823666,
      0.87397442188478647, 0.86708767720087132, 0.86015219085688843,
      0.85316991862392244, 0.84614281948731251, 0.83907285507948559,
      0.8319619891122243, 0.82481218680855906, 0.81762541433444791,
      0.81040363823043715, 0.80314882484346528, 0.79586293975899858,
      0.7885479472336705, 0.7812058096286052, 0.77383848684360157,
      0.76644793575235359, 0.75903610963888835, 0.751604957635389,
      0.74415642416159355, 0.73669244836593, 0.72921496356857263,
      0.72172589670659082, 0.71422716778136675, 0.70672068930845033,
      0.69920836577002854, 0.69169209307018353, 0.68417375799309987,
      0.6766552376644035, 0.66913839901579464, 0.6616250982531422,
      0.65411718032821065, 0.646616478414182, 0.63912481338514038,
      0.63164399329967846, 0.6241758128887922, 0.61672205304822347,
      0.609284480335408, 0.6018648464711881, 0.59446488784644791,
      0.587086325033824, 0.57973086230464221, 0.57240018715124186,
      0.565095969814821, 0.55781986281897, 0.55057350050902332,
      0.54335849859738272, 0.53617645371495026, 0.52902894296881786,
      0.52191752350634069, 0.51484373208574374, 0.50780908465338415,
      0.50081507592781094, 0.49386317899074517, 0.48695484488511254,
      0.48009150222025132, 0.47327455678441904, 0.46650539116472195,
      0.45978536437457973, 0.45311581148884483, 0.44649804328669185,
      0.43993334590238187, 0.43342298048401684, 0.42696818286038318,
      0.42057016321599305, 0.41423010577442071, 0.40794916849003204,
      0.40172848274820244, 0.39556915307411805, 0.38947225685024078,
      0.38343884404253814, 0.37746993693554542, 0.37156652987635519,
      0.36572958902760255, 0.35996005212952453, 0.35425882827116784,
      0.34862679767080806, 0.34306481146565354, 0.3375736915108915,
      0.33215423018813828, 0.32680719022335047, 0.32153330451425138,
      0.31633327596732264, 0.31120777734440846, 0.30615745111897763,
      0.30118290934208347, 0.29628473351806162, 0.29146347448999788,
      0.28671965233500091, 0.28205375626930596, 0.27746624456323582,
      0.27295754446604092, 0.268528052140638, 0.26417813260826223,
      0.25990811970304484, 0.25571831603652695, 0.25160899297211387,
      0.24758039060947398, 0.24363271777887974, 0.2397661520454894,
      0.23598083972355932, 0.23227689590057954, 0.228654404471319,
      0.22511341818175931, 0.22165395868290189, 0.2182760165944243,
      0.21497955157815815, 0.21176449242135745, 0.20863073712972935,
      0.20557815303018717, 0.20260657688328734, 0.19971581500530866,
      0.19690564339992919, 0.1941758078994503, 0.19152602431551602,
      0.18895597859927729, 0.18646532701093568, 0.18405369629861437,
      0.18172068388648444, 0.17946585807208523, 0.17728875823276802,
      0.17518889504118568, 0.17316575068975962, 0.17121877912403977,
      0.16934740628487838, 0.16755103035933247, 0.16582902204021005,
      0.16418072479416546, 0.16260545513825658, 0.16110250292486217,
      0.15967113163486971, 0.15831057867902304, 0.15702005570733374,
      0.15579874892644724, 0.15464581942485559, 0.15356040350584554,
      0.152541613028068, 0.15158853575361378, 0.15070023570347851,
      0.14987575352028989, 0.14911410683818321, 0.14841429065969272,
      0.14777527773953306, 0.14719601897514348, 0.14667544380385894,
      0.14621246060657761, 0.14580595711778732, 0.14545480084181051,
      0.14515783947513278, 0.14491390133466847, 0.14472179579182107,
      0.14458031371219435, 0.14448822790080432, 0.14444429355264507,
      0.14444724870845424, 0.14449581471553216, 0.14458869669345312,
      0.14472458400452093, 0.14490215072880247, 0.14512005614359419,
      0.14537694520714561, 0.14567144904649543, 0.14600218544924531,
      0.14636775935911445, 0.14676676337510919, 0.14719777825414238,
      0.14765937341693391, 0.14815010745702867, 0.14866852865275976,
      0.14921317548199076, 0.14978257713946386, 0.15037525405658739,
      0.15098971842348727, 0.15162447471315171, 0.15227802020749814,
      0.15294884552518806, 0.15363543515101424, 0.15433626796669098,
      0.1550498177828698, 0.1557745538722054, 0.15650894150330186,
      0.15725144247535913, 0.15800051565334738, 0.15875461750353465,
      0.15951220262919114, 0.16027172430629802, 0.16103163501908335,
      0.16179038699521231, 0.16254643274045855, 0.16329822557267817,
      0.16404422015492054, 0.164782873027496, 0.16551264313883132,
      0.1662319923749411, 0.16693938608734143, 0.16763329361923957,
      0.16831218882982493, 0.16897455061649422, 0.16961886343484522,
      0.17024361781626618, 0.17084731088296007, 0.17142844686023537,
      0.17198553758589885, 0.17251710301658685, 0.17302167173087871,
      0.1734977814290222, 0.17394397942911721, 0.17435882315960241,
      0.1747408806478794, 0.17508873100492656, 0.17540096490574739,
      0.17567618506549715, 0.17591300671114263, 0.17611005804850152,
      0.17626598072451732, 0.17637943028462133, 0.1764490766250415,
      0.17647360443991222, 0.17645171366304802, 0.17638211990424002,
      0.17626355487994536, 0.17609476683822492, 0.1758745209778079,
      0.17560159986114721, 0.17527480382133914, 0.17489295136278205,
      0.17445487955545036, 0.17395944442266392, 0.17340552132223136,
      0.17279200532085343, 0.17211781156167164, 0.17138187562484947,
      0.17058315388107775, 0.16972062383789793, 0.16879328447873948,
      0.16780015659456496, 0.16674028310803443, 0.16561272939007884,
      0.164416583568801, 0.16315095683060535, 0.16181498371347203,
      0.16040782239228746, 0.15892865495614833, 0.1573766876775648,
      0.15575115127347419, 0.1540513011580022, 0.15227641768689354,
      0.15042580639354675, 0.14849879821658135, 0.1464947497188866,
      0.14441304329807544, 0.14225308738830161, 0.140014316653379,
      0.13769619217115, 0.1352982016090617, 0.13281985939089797,
      0.13026070685463159, 0.12762031240135274, 0.12489827163524014,
      0.12209420749454286, 0.11920777037354038, 0.11623863823545771,
      0.11318651671630825, 0.11005113921964811, 0.10683226700221882,
      0.10352968925047135, 0.1001432231479531, 0.096672713933554949,
      0.093118034950610148, 0.08947908768684526, 0.085755801805182344,
      0.081948135165396174, 0.078056073836640552, 0.074079632100841009,
      0.070018852446980612, 0.0658738055562869, 0.061644590278343958,
      0.057331333598148182, 0.052934190594137766, 0.04845334438722089,
      0.043889006080836721, 0.039241414692079112, 0.034510837073932057,
      0.029697567828638451, 0.024801929212265948, 0.01982427103050111,
      0.014764970525730543, 0.0096244322554526075, 0.0044030879620843288,
      -0.00089860356578598012, -0.0062801566406387585, -0.01174105883168885,
      -0.017280771128913561, -0.02289872811537607, -0.028594338147768114,
      -0.034366983545099053, -0.04021602078545846, -0.046140780710767035,
      -0.052140568739438148, -0.058214665086861336, -0.064362324993626166,
      -0.070582778961389731, -0.0768752329963027, -0.083238868859894385,
      -0.089672844327322393, -0.096176293452886835, -0.10274832684270825,
      -0.10938803193446438, -0.1160944732840806, -0.12286669285926474,
      -0.12970371033977907, -0.13660452342433091, -0.14356810814397469,
      -0.15059341918190333, -0.1576793901995123, -0.16482493416861607,
      -0.17202894370969696, -0.17929029143605282, -0.18660783030373462,
      -0.19398039396712619, -0.20140679714005161, -0.2088858359622742,
      -0.21641628837125043, -0.22399691447901371, -0.23162645695404033,
      -0.23930364140797164, -0.24702717678704808, -0.25479575576811192,
      -0.26260805515904706, -0.27046273630350232, -0.2783584454897633,
      -0.28629381436362211, -0.29426746034510032, -0.30227798704888131,
      -0.31032398470829714, -0.31840403060272976, -0.32651668948826773,
      -0.33466051403147273, -0.34283404524610539, -0.3510358129326534,
      -0.35926433612051156, -0.36751812351266505, -0.37579567393270713,
      -0.38409547677405859, -0.39241601245121183, -0.40075575285285892,
      -0.40911316179674112, -0.41748669548606665, -0.42587480296733793,
      -0.43427592658943387, -0.44268850246378905, -0.45111096092551373,
      -0.45954172699529922, -0.46797922084194771, -0.47642185824537769,
      -0.48486805105993835, -0.49331620767788664, -0.50176473349286332,
      -0.51021203136321991, -0.518656502075031, -0.52709654480464918,
      -0.535530557580639, -0.54395693774493925, -0.55237408241310459,
      -0.5607803889334636, -0.56917425534505472, -0.57755408083417525,
      -0.585918266189405, -0.59426521425495116, -0.60259333038215757,
      -0.61090102287904846, -0.61918670345773652, -0.62744878767957923,
      -0.63568569539791009, -0.64389585119821957, -0.65207768483563533,
      -0.66022963166957349, -0.66835013309539837, -0.67643763697297943,
      -0.6844905980519842, -0.69250747839379467, -0.700486747789897,
      -0.70842688417661548, -0.71632637404606347, -0.72418371285318928,
      -0.73199740541876768, -0.73976596632823821, -0.74748792032624323,
      -0.75516180270676347, -0.76278615969871477, -0.7703595488468985,
      -0.77788053938817914, -0.78534771262279168, -0.79275966228064343,
      -0.80011499488252, -0.80741233009607116, -0.81465030108649128,
      -0.82182755486176, -0.82894275261237182, -0.83599457004543432,
      -0.842981697713045, -0.84990284133485694, -0.85675672211472431,
      -0.86354207705135755, -0.87025765924288079, -0.87690223818522162,
      -0.8834746000642405, -0.88997354804151652, -0.89639790253372209,
      -0.902746501485502, -0.90901820063578354, -0.91521187377744684,
      -0.92132641301029583, -0.92736072898724642, -0.93331375115368875,
      -0.93918442797994661, -0.94497172718678268, -0.9506746359638969,
      -0.95629216118136118, -0.9618233295939389, -0.96726718803824607,
      -0.97262280362271047, -0.97788926391027853, -0.98306567709384141,
      -0.98815117216433579, -0.99314489907148684, -0.99804602887717231,
      -1.0028537539013587, -1.007567287860609, -1.0121858659991161,
      -1.0167087452122618, -1.0211352041626691, -1.0254645433887424,
      -1.0296960854056758, -1.0338291747989379, -1.0378631783101984,
      -1.041797484915723, -1.0456315058972181, -1.0493646749051291,
      -1.0529964480144054, -1.0565263037727326, -1.0599537432412427,
      -1.0632782900277196, -1.0664994903123137, -1.0696169128657811,
      -1.0726301490602741, -1.0755388128727024, -1.0783425408806975,
      -1.081040992251199, -1.0836338487217072, -1.0861208145742289,
      -1.0885016166019552, -1.0907760040687127, -1.0929437486612266,
      -1.0950046444342423, -1.0969585077485617, -1.0988051772020249,
      -1.1005445135535084, -1.1021763996399816, -1.1037007402866934,
      -1.1051174622105271, -1.1064265139166063, -1.1076278655882086,
      -1.1087215089700473, -1.1097074572449992, -1.110585744904351,
      -1.1113564276116212, -1.1120195820600614, -1.1125753058238836,
      -1.1130237172033213, -1.1133649550635818, -1.113599178667801,
      -1.1137265675040542, -1.1137473211065472, -1.1136616588710431,
      -1.1134698198646455, -1.1131720626300123, -1.1127686649841091,
      -1.1122599238115882, -1.1116461548529042, -1.1109276924872573,
      -1.110104889510475, -1.1091781169079309, -1.1081477636226076,
      -1.1070142363184168, -1.1057779591388754, -1.1044393734612599,
      -1.1029989376463412, -1.1014571267838178, -1.0998144324335613,
      -1.0980713623627945, -1.0962284402793065, -1.0942862055608382,
      -1.0922452129807525, -1.0901060324300986, -1.0878692486362171,
      -1.0855354608779784, -1.0831052826978036, -1.0805793416105745,
      -1.0779582788095732, -1.0752427488695626, -1.0724334194471439,
      -1.06953097097852, -1.0665360963747816, -1.0634495007148639,
      -1.0602719009362838, -1.0570040255237978, -1.0536466141961105,
      -1.0502004175907651, -1.04666619694734, -1.0430447237890925,
      -1.0393367796031727, -1.03554315551955, -1.0316646519887676,
      -1.0277020784586792, -1.023656253050276, -1.0195280022327589,
      -1.0153181604979682, -1.0110275700343159, -1.0066570804003496,
      -1.0022075481980735, -0.99767983674616656, -0.99307481575322065,
      -0.98839336099113528, -0.98363635396879789, -0.97880468160617706,
      -0.97389923590895722, -0.96892091364384769, -0.963870616014692,
      -0.95874924833950514, -0.953557719728559, -0.94829694276365628,
      -0.9429678331787007, -0.93757130954170487, -0.93210829293834063,
      -0.92657970665717093, -0.92098647587667459, -0.91532952735418927,
      -0.90960978911688528, -0.903828190154896, -0.897985660116718,
      -0.89208312900699616, -0.88612152688680623, -0.88010178357655544,
      -0.87402482836160145, -0.86789158970071412, -0.86170299493746938,
      -0.85545997001470642, -0.84916343919213222, -0.84281432476719065,
      -0.836413546799298, -0.82996202283753617, -0.82346066765191472,
      -0.8169103929682926, -0.81031210720706137, -0.80366671522567057,
      -0.79697511806510357, -0.79023821270038963, -0.78345689179523037,
      -0.7766320434608408, -0.76976455101908425, -0.76285529276997754,
      -0.75590514176366386, -0.74891496557690851, -0.741885626094215,
      -0.73481797929362425, -0.72771287503727378, -0.7205711568667823,
      -0.71339366180353359, -0.70618122015392171, -0.698934655319623,
      -0.691654783612951, -0.68434241407736118, -0.67699834831315508,
      -0.66962338030844537, -0.66221829627542261, -0.65478387449198738,
      -0.64732088514878261, -0.63983009020167825, -0.632312243229753,
      -0.62476808929879846, -0.6171983648304038, -0.60960379747664162,
      -0.60198510600039423, -0.59434300016134267, -0.58667818060766,
      -0.57899133877342246, -0.57128315678176356, -0.56355430735379541,
      -0.55580545372330958, -0.5480372495572795, -0.540250338882171,
      -0.53244535601607246, -0.52462292550665335, -0.51678366207496207,
      -0.5089281705650518, -0.50105704589944455, -0.49317087304043605,
      -0.48527022695722061, -0.47735567259884371, -0.469427764872963,
      -0.46148704863041079, -0.453534058655539, -0.44556931966233521,
      -0.43759334629628172, -0.4296066431419398, -0.42160970473623749,
      -0.41360301558742646, -0.40558705019968572, -0.39756227310333569,
      -0.38952913889062424, -0.38148809225705743, -0.3734395680482383,
      -0.36538399131214322, -0.3573217773568369, -0.34925333181354268,
      -0.34117905070503923, -0.333099320519319, -0.32501451828847755,
      -0.31692501167274811, -0.30883115904965391, -0.30073330960819322,
      -0.29263180344801448, -0.28452697168351049, -0.27641913655275963,
      -0.26830861153125174, -0.26019570145033472, -0.25208070262029914,
      -0.243963902958027, -0.2358455821191428, -0.22772601163456482,
      -0.21960545505139936, -0.21148416807809003, -0.20336239873372283,
      -0.19524038750142986, -0.18711836748577615, -0.17899656457405955,
      -0.17087519760143283, -0.16275447851973762, -0.15463461256998143,
      -0.14651579845833865, -0.13839822853560776, -0.13028208897998664,
      -0.12216755998310708, -0.11405481593919783, -0.10594402563729538,
      -0.097835352456371538, -0.089728954563306443, -0.081624985113575244,
      -0.073523592454549841, -0.065424920331302788, -0.057329108094815541,
      -0.049236290912465917, -0.041146599980691242, -0.03306016273971174,
      -0.024977103090198502, -0.016897541611778255, -0.0088215957832539771,
      -0.00074938020442542885, 0.0073189931806054154, 0.015383414858762365,
      0.023443777522072815, 0.031499975840616437, 0.03955190623446643,
      0.0475994666447299, 0.055642556303831969, 0.063681075505133869,
      0.0717149253720335, 0.079744007626649752, 0.087768224358225858,
      0.095787477791357989, 0.10380167005419168, 0.11181070294668553,
      0.11981447770907819, 0.12781289479067887, 0.13580585361909364,
      0.14379325237002816, 0.151774987737761, 0.15975095470643189,
      0.16772104632225676, 0.17568515346679453, 0.1836431646313724,
      0.19159496569280426, 0.19954043969052143, 0.20747946660521643,
      0.21541192313914351, 0.22333768249817643, 0.23125661417573196,
      0.23916858373871475, 0.24707345261554003, 0.25497107788640772,
      0.26286131207589242, 0.27074400294800449, 0.27861899330378981,
      0.28648612078162705, 0.29434521766028721, 0.30219611066489482,
      0.31003862077588962, 0.31787256304107919, 0.32569774639091853,
      0.33351397345709477, 0.34132104039452366, 0.34911873670687349,
      0.35690684507569315, 0.36468514119326023, 0.37245339359925023,
      0.38021136352129253, 0.387958804719537, 0.39569546333531469,
      0.403421077743974, 0.41113537841198733, 0.41883808775842174,
      0.42652892002083909, 0.43420758112573421, 0.4418737685635698,
      0.44952717126850522, 0.45716746950287335, 0.46479433474652221,
      0.47240742959103782, 0.48000640763897734, 0.48759091340813432,
      0.49516058224094472, 0.50271504021905822, 0.51025390408317439,
      0.51777678115817782, 0.525283269283649, 0.53277295674979852,
      0.54024542223887306, 0.54770023477210228, 0.55513695366222049,
      0.56255512847161726, 0.56995429897616356, 0.57733399513474659,
      0.58469373706456507, 0.59203303502221716, 0.59935138939061738,
      0.60664829067176862, 0.613923219485432, 0.62117564657371782,
      0.628405032811608, 0.63561082922346734, 0.64279247700551689,
      0.64994940755433772, 0.657081042501375, 0.6641867937534891,
      0.67126606353953866, 0.67831824446302469, 0.68534271956078574,
      0.69233886236774289, 0.69930603698771365, 0.70624359817027815,
      0.71315089139368459, 0.72002725295380587, 0.7268720100591175,
      0.73368448093169547, 0.74046397491421723, 0.74720979258293474,
      0.75392122586661281, 0.76059755817140751, 0.76723806451163945,
      0.77384201164646571, 0.78040865822238659, 0.78693725492156652,
      0.793427044615944, 0.79987726252706171, 0.80628713639160421,
      0.81265588663258426, 0.81898272653613191, 0.82526686243382819,
      0.83150749389056033, 0.83770381389780313, 0.8438550090723087,
      0.84996025986010393, 0.85601874074578366, 0.862029620466982,
      0.867992062234, 0.87390522395448555, 0.87976825846312223,
      0.885580313756227, 0.89134053323120832, 0.897048055930782,
      0.90270201679186735, 0.90830154689910836, 0.913845773742892,
      0.91933382148180687, 0.92476481120944087, 0.93013786122543229,
      0.93545208731067242, 0.94070660300657116, 0.94590051989828483,
      0.95103294790180437, 0.95610299555481271, 0.96110977031119038,
      0.96605237883907669, 0.970929927322378, 0.9757415217656118,
      0.9804862683019715, 0.98516327350450683, 0.98977164470030443,
      0.99431049028754748, 0.99877892005534119, 1.0031760455061862,
      1.0075009801809718, 1.0117528399863818, 1.0159307435245717,
      1.0200338124250063, 1.0240611716783219, 1.0280119499720992,
      1.0318852800283989, 1.0356802989429448, 1.039396148525825,
      1.0430319756435618, 1.0465869325624391, 1.0500601772929417,
      1.0534508739351629, 1.0567581930250698, 1.0599813118814634,
      1.063119414953507, 1.0661716941686912, 1.0691373492810845,
      1.0720155882197293, 1.0748056274370654, 1.0775066922572061,
      1.0801180172239524, 1.0826388464483929, 1.0850684339559487,
      1.0874060440327207, 1.0896509515709987, 1.0918024424137862,
      1.0938598136982007, 1.0958223741976041, 1.0976894446623278,
      1.0994603581588327, 1.1011344604071829, 1.1027111101166664,
      1.1041896793194446, 1.1055695537020713, 1.1068501329347413,
      1.1080308309981304, 1.1091110765076864, 1.1100903130352298,
      1.1109679994277111, 1.111743610123012, 1.1124166354626193,
      1.1129865820010556, 1.113452972811922, 1.1138153477904149,
      1.1140732639521742, 1.1142262957283484, 1.1142740352567089,
      1.1142160926687183, 1.1140520963723881, 1.113781693330814,
      1.1134045493362434, 1.1129203492795718, 1.1123287974151064,
      1.1116296176204949, 1.1108225536516907, 1.1099073693928185,
      1.108883849100839, 1.1077517976448694, 1.1065110407400613, 1.1051614251759,
      1.1037028190388245, 1.1021351119290483, 1.1004582151714637,
      1.0986720620205339, 1.0967766078590397, 1.0947718303906009,
      1.0926577298258566, 1.0904343290621898, 1.0881016738569158,
      1.0856598329938252, 1.083108898442982, 1.0804489855136907,
      1.0776802330005371, 1.074802803322408, 1.0718168826544066,
      1.0687226810525843, 1.0655204325713918, 1.0622103953737807,
      1.0587928518338736, 1.0552681086321225, 1.0516364968428953,
      1.0478983720144046, 1.0440541142409168, 1.040104128227185,
      1.0360488433450232, 1.0318887136819823, 1.0276242180820598,
      1.023255860178385, 1.0187841684178383, 1.0142096960775466,
      1.0095330212732159, 1.0047547469592475, 0.99987550092061084,
      0.99489593575641566, 0.98981672885517835, 0.98463858236171176,
      0.97936222313564636, 0.97398840270153264, 0.96851789719050985,
      0.96295150727352519, 0.95729005808607737, 0.95153439914447335,
      0.94568540425359815, 0.93974397140616528, 0.93371102267347272,
      0.92758750408763535, 0.9213743855153208, 0.91507266052296254,
      0.90868334623348956, 0.90220748317456434, 0.89564613511833624,
      0.88900038891275723, 0.8822713543044387, 0.875460163753105,
      0.8685679722376618, 0.86159595705389125, 0.85454531760383146,
      0.8474172751768595, 0.84021307272251788, 0.83293397461513874,
      0.82558126641028717, 0.81815625459309183, 0.81066026631850607,
      0.80309464914355622, 0.7954607707516248, 0.78776001866884526,
      0.77999379997264406, 0.77216354099254059, 0.76427068700321543,
      0.75631670190997158, 0.748303067926634, 0.74023128524597981,
      0.7321028717027589, 0.72391936242941846, 0.71568230950459466,
      0.707393281594469, 0.69905386358708765, 0.6906656562197242,
      0.6822302756993911, 0.67374935331661145, 0.665224535052536,
      0.65665748117951894, 0.64804986585526791, 0.63940337671066294,
      0.63071971443138275, 0.62200059233342109, 0.61324773593265069,
      0.60446288250852365, 0.59564778066205493, 0.5868041898681936,
      0.57793388002273649, 0.569038630983888, 0.56012023210863093,
      0.551180481783999, 0.542221186953444, 0.53324416263838781,
      0.52425123145513541, 0.515244223127273, 0.50622497399370858,
      0.49719532651250259, 0.48815712876062362, 0.47911223392980928,
      0.47006249981865439, 0.46100978832111017, 0.45195596491153062,
      0.44290289812644823, 0.43385245904320147, 0.42480652075562353,
      0.41576695784692197, 0.40673564585993549, 0.39771446076490879,
      0.38870527842498392, 0.37970997405956619, 0.37073042170571668,
      0.36176849367778058, 0.35282606002538647, 0.3439049879900164,
      0.33500714146032029, 0.32613438042632892, 0.31728856043276626,
      0.30847153203163441, 0.29968514023424364, 0.29093122396286719,
      0.28221161550220936, 0.27352813995086039, 0.2648826146729143,
      0.2562768487499581, 0.2477126424335705, 0.23919178659855511,
      0.23071606219707549, 0.22228723971385772, 0.21390707862267216,
      0.20557732684426533, 0.19729972020592212, 0.18907598190284947,
      0.18090782196155258, 0.17279693670540597, 0.16474500822258492,
      0.15675370383655507, 0.14882467557928106, 0.14095955966737328,
      0.13315997598130019, 0.12542752754791558, 0.1177638000264071,
      0.11017036119791233, 0.10264876045893657, 0.095200528318779565,
      0.087827175901115717, 0.08053019444995077, 0.073311054840082115,
      0.066171207092273, 0.05911207989329767, 0.052135080121038277,
      0.045241592374782785, 0.038432978510933538, 0.031710577184259486,
      0.025075703394871682, 0.018529648041101993, 0.012073677478409484,
      0.0057090330845338266, -0.00056306916899950821, -0.0067414391388220252,
      -0.012824912924974799, -0.018812353279313146, -0.024702650006910104,
      -0.030494720360296212, -0.03618750942640088, -0.041779990506037049,
      -0.047271165485793964, -0.052660065202172583, -0.057945749797856022,
      -0.063127309069940157, -0.068203862810017737, -0.073174561135959,
      -0.078038584815271955, -0.08279514557990128, -0.0874434864323515,
      -0.091982881943000083, -0.096412638538479381, -0.10073209478101397,
      -0.1049406216385927, -0.10903762274585441, -0.11302253465560472,
      -0.1168948270808136, -0.12065400312702232, -0.12429959951504484,
      -0.127831186793864, -0.13124836954362415, -0.13455078656864133,
      -0.13773811108031886, -0.14081005086989445, -0.14376634847094147,
      -0.14660678131152577, -0.149331161855953, -0.15193933773603505,
      -0.15443119187179291, -0.15680664258153626, -0.15906564368125675,
      -0.16120818457326636, -0.16323429032403769, -0.16514402173117582,
      -0.16693747537947987, -0.16861478368604829, -0.170176114934386,
      -0.17162167329745812, -0.17295169884967782, -0.17416646756777893,
      -0.17526629132054672, -0.17625151784738663, -0.17712253072570047,
      -0.17787974932706196, -0.17852362876216873, -0.17905465981456486,
      -0.17947336886312104, -0.17978031779327555, -0.17997610389702831,
      -0.18006135976170862, -0.18003675314748802, -0.17990298685370154,
      -0.1796607985739391, -0.17931096073996822, -0.17885428035447765,
      -0.17829159881269738, -0.17762379171289794, -0.176851768655825,
      -0.17597647303308439, -0.17499888180454393, -0.17392000526476864,
      -0.17274088679856775, -0.17146260262567581, -0.17008626153464423,
      -0.16861300460599976, -0.16704400492471516, -0.1653804672820901,
      -0.1636236278670824, -0.16177475394718033, -0.15983514353888792,
      -0.15780612506790892, -0.15568905701910155, -0.15348532757631522,
      -0.15119635425216915, -0.14882358350789926, -0.14636849036335148,
      -0.14383257799722912, -0.14121737733770012, -0.1385244466434776,
      -0.13575537107547589, -0.13291176225916163, -0.12999525783772231,
      -0.12700752101617174, -0.12395024009650962, -0.12082512800408221,
      -0.11763392180525174, -0.1143783822165273, -0.11106029310528878,
      -0.10768146098223945, -0.1042437144857366, -0.10074890385815126,
      -0.097198900414387307, -0.093595596002738937, -0.0899409024582136,
      -0.086236751048504812, -0.082485091912749678, -0.078687893493256611,
      -0.074847141960352137, -0.070964840630525772, -0.067043009378036464,
      -0.063083684040160348, -0.05908891581624371, -0.05506077066076,
      -0.051001328670524218, -0.046912683466272531, -0.042796941568770556,
      -0.038656221769652749, -0.034492654497173064, -0.030308381177060074,
      -0.026105553588669738, -0.021886333216627543, -0.017652890598159422,
      -0.013407404666310012, -0.00915206208924535, -0.0048890566058444121,
      -0.000620588357777882, 0.0036511367817183421, 0.007923907882161553,
      0.012195509633046844, 0.016463723023738233, 0.020726326025848563,
      0.024981094277871797, 0.029225801771871049, 0.033458221541998442,
      0.037676126354647559, 0.041877289400001128, 0.046059484984784849,
      0.050220489225985515, 0.054358080745331647, 0.058470041364318645,
      0.062554156799547858, 0.066608217358176666, 0.070630018633247735,
      0.074617362198678649, 0.07856805630370893, 0.08247991656655751,
      0.08635076666709024, 0.090178439038271413, 0.093960775556173382,
      0.097695628228339493, 0.10138085988026152, 0.10501434483976378,
      0.10859396961907071, 0.11211763359434158, 0.11558324968245277,
      0.11898874501480428, 0.1223320616079434, 0.12561115703077658,
      0.12882400506816832, 0.13196859638069813, 0.13504293916036547,
      0.13804505978204007, 0.14097300345042435, 0.14382483484233985,
      0.1465986387441095, 0.14929252068383841, 0.15190460755838048,
      0.1544330482547851, 0.15687601426602391, 0.15923170030079176,
      0.16149832488717458, 0.16367413096999889, 0.16575738650164654,
      0.16774638502616043, 0.16963944625642435, 0.17143491664424185,
      0.17313116994311312, 0.17472660776353061, 0.17621966012059986,
      0.17760878597380381, 0.17889247375873124, 0.18006924191058665,
      0.1811376393793093, 0.18209624613612083, 0.18294367367133552,
      0.18367856548325712, 0.18429959755800346, 0.18480547884008891,
      0.18519495169360317, 0.18546679235383279, 0.18561981136916494,
      0.18565285403311921, 0.18556480080636795, 0.1853545677285845,
      0.18502110681998252, 0.18456340647240629, 0.18398049182983581,
      0.18327142515816564, 0.1824353062041322, 0.18147127254326156,
      0.18037849991670707, 0.17915620255686929, 0.17780363350166384,
      0.17632008489733497, 0.17470488828970004, 0.17295741490371869,
      0.17107707591128279, 0.16906332268712876, 0.1669156470527722,
      0.16463358150837623, 0.16221669945246994, 0.15966461538941479,
      0.1569769851245594, 0.15415350594698882, 0.15119391679980834,
      0.14809799843787574, 0.14486557357293567, 0.14149650700607813,
      0.13799070574747985, 0.13434811912335035, 0.13056873887006398,
      0.12665259921540689, 0.12259977694691497, 0.11841039146724754,
      0.11408460483658248, 0.10962262180199162, 0.10502468981377504,
      0.10029109902873314, 0.095422182300354749, 0.090418315155921344,
      0.085279915760504407, 0.080007444867859448, 0.074601405758216374,
      0.069062344162966777, 0.063390848176262476, 0.057587548153530232,
      0.05165311659691918, 0.045588268027717524, 0.039393758845736704,
      0.033070387175716906, 0.02661899270077267, 0.0200404564829217,
      0.013335700770736675, 0.0065056887941696284, -0.00044857545341155797,
      -0.0075260474459085749, -0.014725642367844578, -0.02204623537032712,
      -0.029486661839547568, -0.037045717677756204, -0.044722159596618641,
      -0.052514705422910951, -0.060422034416424054, -0.068442787600039953,
      -0.07657556810184743, -0.084818941509231832, -0.093171436234823879,
      -0.10163154389421661, -0.11019771969533261, -0.11886838283935219,
      -0.12764191693305449, -0.13651667041250168, -0.14549095697789435,
      -0.15456305603951553, -0.16373121317461134, -0.17299364059507824,
      -0.18234851762583934, -0.19179399119374752, -0.201328176326879,
      -0.21094915666409622, -0.22065498497468708, -0.23044368368796642,
      -0.24031324543266389, -0.25026163358594222, -0.26028678283189544,
      -0.27038659972933771, -0.28055896328874325, -0.290801725558138,
      -0.30111271221779318, -0.31148972318352719, -0.32193053321843595,
      -0.33243289255288061, -0.342994527512536, -0.35361314115431208,
      -0.36428641390996269, -0.37501200423718056, -0.38578754927799358,
      -0.39661066552424673, -0.40747894948998448, -0.41838997839052372,
      -0.42934131082800264, -0.44033048748321818, -0.45135503181352343,
      -0.46241245075657056, -0.47350023543971914, -0.48461586189483297,
      -0.49575679177831744, -0.50692047309611321, -0.51810434093347568,
      -0.52930581818928113, -0.54052231631465564, -0.551751236055695,
      -0.56298996820003744, -0.57423589432708055, -0.58548638756159621,
      -0.5967388133305106, -0.60799053012262694, -0.6192388902510545,
      -0.63048124061810074, -0.64171492348239911, -0.65293727722802886,
      -0.66414563713540575, -0.67533733615368019, -0.68650970567442338,
      -0.69766007630635118, -0.70878577865085957, -0.71988414407811152,
      -0.73095250550345914, -0.74198819816392791, -0.75298856039456341,
      -0.763950934404363, -0.77487266705156777, -0.78575111061807656,
      -0.79658362358273083, -0.80736757139324122, -0.81810032723650594,
      -0.8287792728070934, -0.83940179907362522, -0.84996530704285655,
      -0.86046720852118463, -0.87090492687336518, -0.8812758977781876,
      -0.89157756998089022, -0.901807406042062, -0.91196288308281037,
      -0.92204149352595166, -0.93204074583301433, -0.94195816523678166,
      -0.951791294469196, -0.96153769448436055, -0.9711949451764269,
      -0.98076064609214408, -0.99023241713783738, -0.99960789928059579,
      -1.0088847552434794, -1.0180606701944717, -1.0271333524290112,
      -1.0361005340458609, -1.0449599716161186, -1.0537094468451469,
      -1.0623467672272233, -1.0708697666927005, -1.0792763062474648,
      -1.0875642746045284, -1.0957315888075019, -1.1037761948457963,
      -1.1116960682613366, -1.1194892147466149, -1.1271536707338787,
      -1.1346875039752731, -1.1420888141137557, -1.1493557332446207,
      -1.1564864264674219, -1.1634790924281517, -1.1703319638514913,
      -1.1770433080629625, -1.1836114275008316, -1.1900346602175893,
      -1.1963113803708436, -1.2024399987035086, -1.2084189630130844,
      -1.2142467586099217, -1.2199219087643052, -1.2254429751422342,
      -1.2308085582297406, -1.2360172977456236, -1.241067873042478,
      -1.2459590034958763, -1.2506894488815796, -1.2552580097406885,
      -1.2596635277325745, -1.2639048859755184, -1.2679810093749331,
      -1.2718908649390643, -1.275633462082072, -1.279207852914418,
      -1.2826131325204313, -1.2858484392229892, -1.2889129548352376,
      -1.2918059048992436, -1.2945265589115325, -1.2970742305354244,
      -1.2994482778001109, -1.3016481032864016, -1.3036731542991,
      -1.3055229230259235, -1.3071969466829585, -1.3086948076465665,
      -1.3100161335717371, -1.3111605974968179, -1.3121279179346088,
      -1.3129178589497925, -1.313530230222669, -1.3139648870991847,
      -1.3142217306272259, -1.3143007075791979, -1.3142018104608322,
      -1.3139250775062814, -1.3134705926594537, -1.3128384855416237,
      -1.312028931405316, -1.3110421510744914, -1.309878410871036,
      -1.3085380225276022, -1.3070213430868076, -1.3053287747868423,
      -1.303460764933511, -1.3014178057587598, -1.2992004342657286,
      -1.2968092320603803, -1.2942448251697667, -1.2915078838469798,
      -1.288599122362867, -1.2855192987845607, -1.2822692147409085,
      -1.2788497151748657, -1.2752616880829535, -1.2715060642418357,
      -1.267583816922125, -1.2634959615895058, -1.2592435555932662,
      -1.2548276978423434, -1.2502495284689836, -1.2455102284801329,
      -1.2406110193966482, -1.2355531628804883, -1.2303379603499494,
      -1.22496675258311, -1.2194409193096074, -1.2137618787908531,
      -1.2079310873888502, -1.2019500391237274, -1.1958202652201551,
      -1.1895433336427697, -1.1831208486207652, -1.1765544501618008,
      -1.1698458135553742, -1.1629966488658448, -1.1560087004152302,
      -1.1488837462559751, -1.14162359763385, -1.134230098441136,
      -1.1267051246603044, -1.1190505837983418, -1.111268414311896,
      -1.1033605850234658, -1.0953290945287752, -1.0871759705955506,
      -1.0789032695538807, -1.070513075678363, -1.062007500562216,
      -1.0533886824835907, -1.0446587857642471, -1.0358200001208056,
      -1.0268745400088175, -1.017824643959818, -1.0086725739115949,
      -0.99942061453188935, -0.990071072535726, -0.98062627599661278,
      -0.97108857365182089, -0.96146033420195132, -0.95174394560503128,
      -0.94194181436536706, -0.932056364817351, -0.92209003840448389,
      -0.91204529295382852, -0.90192460194610558, -0.89173045378171034,
      -0.88146535104283008, -0.87113180975193494, -0.860732358626863,
      -0.85026953833272945, -0.83974590073091815, -0.82916400812536872,
      -0.818526432506413, -0.80783575479239456, -0.79709456406932833,
      -0.78630545682880071, -0.7754710362043985, -0.7645939112068848,
      -0.75367669595835107, -0.742722008925618, -0.73173247215310544,
      -0.7207107104954138, -0.709659350849883, -0.69858102138932565,
      -0.68747835079522712, -0.676353967491621, -0.66521049887988881,
      -0.6540505705747347, -0.64287680564155836, -0.6316918238354825,
      -0.62049824084227112, -0.609298667521352, -0.59809570915122878,
      -0.5868919646774744, -0.57569002596356611, -0.56449247704479133,
      -0.55330189338545377, -0.54212084113961556, -0.53095187641560737,
      -0.51979754454454674, -0.50866037935305408, -0.49754290244045074,
      -0.48644762246061413, -0.47537703440874579, -0.46433361891325675,
      -0.45331984153299631, -0.44233815206005089, -0.43139098382830782,
      -0.42048075302801841, -0.40960985802656669, -0.39878067869565237,
      -0.38799557574509913, -0.37725689006348506, -0.36656694206581114,
      -0.35592803104839921, -0.34534243455123442, -0.3348124077279066,
      -0.32434018272340265, -0.31392796805989925, -0.30357794803074922,
      -0.29329228210286362, -0.28307310432765542, -0.27292252276072848,
      -0.26284261889049415, -0.25283544707589078, -0.24290303399335023,
      -0.23304737809322151, -0.22327044906578059, -0.21357418731700994,
      -0.20396050345427594, -0.19443127778211156, -0.18498835980818829,
      -0.17563356775966638, -0.16636868811008632, -0.15719547511687848,
      -0.14811565036967861, -0.13913090234957681, -0.13024288599941508,
      -0.12145322230526678, -0.11276349788920084, -0.10417526461350986,
      -0.095690039196432888, -0.087309302839539221, -0.079034500866873358,
      -0.0708670423759606, -0.062808299900747142, -0.054859609086607017,
      -0.047022268377489573, -0.03929753871530528, -0.031686643251606611,
      -0.024190767071661998, -0.016811056931020266, -0.0095486210045866715,
      -0.0024045286483022205, 0.0046201898264876251, 0.011524543365961121,
      0.018307580373956911, 0.024968388899299324, 0.031506096810233,
      0.037919871955942153, 0.044208922315135665, 0.050372496131635705,
      0.056409882036938877, 0.062320409159766374, 0.0681034472225472,
      0.0737584066248108, 0.079284738513520456, 0.084681934840305825,
      0.089949528405591644, 0.095087092889645369, 0.10009424287053278,
      0.10497063382900312, 0.10971596214030291, 0.11432996505294504,
      0.1188124206544699, 0.12316314782420718, 0.12738200617306183,
      0.13146889597039632, 0.13542375805801002, 0.1392465737512909,
      0.14293736472754892, 0.14649619290163043, 0.14992316028885203,
      0.15321840885527679, 0.15638212035546473, 0.15941451615772592,
      0.16231585705693774, 0.16508644307504705, 0.16772661324928967,
      0.17023674540825323, 0.17261725593584618, 0.1748685995232748,
      0.1769912689091222, 0.17898579460763922, 0.18085274462532736,
      0.18259272416595995, 0.18420637532412087, 0.1856943767673789,
      0.18705744340724204, 0.18829632605898888, 0.1894118110905082,
      0.19040472006028866, 0.19127590934468286, 0.1920262697545764,
      0.19265672614161322, 0.19316823699412222, 0.19356179402287949,
      0.19383842173685334, 0.19399917700912564, 0.19404514863307415,
      0.19397745686904477, 0.19379725298164246, 0.19350571876779482,
      0.19310406607578878, 0.1925935363154325, 0.19197539995950844,
      0.1912509560367146, 0.19042153161626071, 0.189488481284293,
      0.18845318661236043, 0.1873170556180801, 0.18608152221818738,
      0.18474804567421471, 0.18331811003090867, 0.18179322354766547,
      0.1801749181231227, 0.17846474871313572, 0.17666429274234041,
      0.17477514950949247, 0.17279893958680215, 0.170737304213472,
      0.1685919046836335, 0.16636442172891625, 0.16405655489583737,
      0.16167002191824581, 0.15920655808503359, 0.15666791560330956,
      0.15405586295729884, 0.15137218426313587, 0.14861867861980571,
      0.14579715945645466, 0.14290945387627602, 0.13995740199719592,
      0.13694285628961506, 0.13386768091138593, 0.13073375104028215,
      0.12754295220419476, 0.12429717960922197, 0.12099833746598168,
      0.11764833831428395, 0.11424910234642008, 0.11080255672933381,
      0.10731063492584424, 0.10377527601519279, 0.10019842401311575,
      0.096582027191707359, 0.0929280373992544, 0.089238409380292871,
      0.085515100096150473, 0.081760068046131548, 0.077975272589618158,
      0.074162673269334428, 0.070324229135928715, 0.066461898074170023,
      0.062577636130944747, 0.058673396845296114, 0.054751130580708268,
      0.050812783859882707, 0.04686029870220694, 0.04289561196415316,
      0.0389206546828129, 0.034937351422768936, 0.030947619626577466,
      0.026953368969011696, 0.022956500715304307, 0.018958907083621662,
      0.014962470611936729, 0.010969063529550557, 0.0069805471334356828,
      0.002998771169639286, -0.00097442678008762, -0.0049372219062084055,
      -0.0088878027736753462, -0.012824371918366259, -0.016745146437485259,
      -0.020648358573726697, -0.024532256293059107, -0.0283951038558459,
      -0.032235182381229563, -0.036050790404526939, -0.039840244427455915,
      -0.043601879461047169, -0.047334049561064344, -0.051035128355723054,
      -0.054703509565572982, -0.058337607515376887, -0.061935857637802287,
      -0.065496716968780885, -0.0690186646343726, -0.072500202328973,
      -0.075939854784747934, -0.079336170232076231, -0.082687720850925656,
      -0.085993103212994332, -0.0892509387144647, -0.092459873999239356,
      -0.095618581372557479, -0.098725759204828178, -0.1017801323255471,
      -0.10478045240722798, -0.10772549833917884, -0.11061407659101939,
      -0.11344502156585005, -0.11621719594294561, -0.1189294910098649,
      -0.12158082698390391, -0.12417015332276103, -0.12669644902434812,
      -0.12915872291564762, -0.13155601393053079, -0.1338873913764495,
      -0.1361519551899536, -0.13834883618091581, -0.14047719626542904,
      -0.14253622868729809, -0.14452515822805945, -0.14644324140548662,
      -0.14828976666050731, -0.15006405453250288, -0.15176545782292397,
      -0.15339336174719975, -0.15494718407489139, -0.1564263752580568,
      -0.15783041854780611, -0.15915883009900916, -0.16041115906314107,
      -0.16158698766925655, -0.16268593129305131, -0.16370763851404441,
      -0.16465179116083967, -0.16551810434447453, -0.16630632647986771,
      -0.16701623929538031, -0.16764765783046143, -0.16820043042144911,
      -0.16867443867550075, -0.16906959743269798, -0.16938585471635212,
      -0.16962319167153136, -0.16978162249185422, -0.16986119433459196,
      -0.16986198722410714, -0.16978411394369075, -0.16962771991584102,
      -0.16939298307104614, -0.16908011370511813, -0.16868935432515528,
      -0.16822097948418757, -0.16767529560457423, -0.1670526407902472,
      -0.16635338462785595, -0.16557792797689655, -0.16472670274893575,
      -0.1638001716759851, -0.16279882806813728, -0.16172319556056713,
      -0.16057382784997476, -0.15935130842058506, -0.15805625025983172,
      -0.15668929556379146, -0.15525111543252457, -0.15374240955541169,
      -0.15216390588661644, -0.15051636031081234, -0.14880055629926384,
      -0.14701730455642942, -0.14516744265720274, -0.14325183467492503,
      -0.14127137080031588, -0.13922696695146308, -0.13711956437501346,
      -0.134950129238719, -0.13271965221547477, -0.1304291480590293,
      -0.128079655171498, -0.1256722351628401, -0.12320797240249341,
      -0.1206879735632814, -0.11811336715780321, -0.11548530306745169,
      -0.11280495206423453, -0.11007350532558002, -0.10729217394230216,
      -0.10446218841988979, -0.1015847981733302, -0.098661271015611882,
      -0.095692892640117017, -0.092680966097093864, -0.089626811264377673,
      -0.086531764312561613, -0.083397177164806144, -0.080224416951496819,
      -0.077014865459918147, -0.073769918579159752, -0.070490985740450623,
      -0.067179489353120833, -0.063836864236384128, -0.060464557047152673,
      -0.057064025704092247, -0.053636738808103407, -0.050184175059457714,
      -0.046707822671773688, -0.043209178783068194, -0.039689748864062735,
      -0.036151046123959668, -0.032594590913931909, -0.029021910128483389,
      -0.025434536604927033, -0.021834008521197115, -0.018221868792174412,
      -0.014599664464769513, -0.010968946111961336, -0.0073312672260032047,
      -0.0036881836110319172, -4.1252775241543138E-5, 0.00360796667710489,
      0.0072579156536412837, 0.010907035181638283, 0.014553767015297897,
      0.018196554242365146, 0.021833841889884076, 0.025464077528858403,
      0.029085711877631204, 0.032697199403735444, 0.03629699892404252,
      0.039883574202995251, 0.043455394548677917, 0.047010935406578386,
      0.050548678950785728, 0.054067114672438785, 0.057564739965221504,
      0.061040060707697734, 0.0644915918422893, 0.0679178579506882,
      0.071317393825512332, 0.0746887450379993, 0.078030468501555289,
      0.081341133030953361, 0.084619319896975548, 0.087863623376355934,
      0.0910726512967681, 0.0942450255767225, 0.097379382760167374,
      0.10047437454560451, 0.10352866830956084, 0.10654094762419337,
      0.10950991276890243, 0.11243428123575072, 0.11531278822849139,
      0.11814418715509438, 0.12092725011354273, 0.12366076837077494,
      0.12634355283458104, 0.1289744345183067, 0.13155226499821987,
      0.13407591686333914, 0.13654428415762621, 0.13895628281435637,
      0.14131085108252733, 0.14360694994516771, 0.14584356352939432,
      0.14801969950809568, 0.15013438949308061, 0.15218668941958219,
      0.15417567992197945, 0.15610046670060126, 0.15796018087950434,
      0.15975397935509317, 0.16148104513547781, 0.16314058767042436,
      0.16473184317184073, 0.16625407492463751, 0.167706573587886,
      0.169088657486183, 0.17039967289109026, 0.17163899429259594,
      0.17280602466048339, 0.17390019569550805, 0.17492096807035035,
      0.17586783166020492, 0.17674030576296895, 0.17753793930894413,
      0.17826031105998741, 0.17890702979804465, 0.17947773450299778,
      0.17997209451978491, 0.18038980971472462, 0.18073061062100268,
      0.18099425857327336, 0.1811805458313222, 0.18128929569277685,
      0.18132036259479947, 0.18127363220475615, 0.18114902149981529,
      0.18094647883547424, 0.18066598400296641, 0.18030754827555412,
      0.17987121444369578, 0.17935705683905506, 0.17876518134738068,
      0.17809572541023611, 0.17734885801556854, 0.17652477967717428,
      0.17562372240301014, 0.17464594965240135, 0.17359175628217019,
      0.17246146848167043, 0.17125544369680137, 0.16997407054298722,
      0.16861776870718442, 0.16718698883894773, 0.16568221243057979,
      0.16410395168643876, 0.16245274938141718, 0.16072917870867687,
      0.15893384311666611, 0.15706737613550864, 0.15513044119279981,
      0.15312373141888563, 0.15104796944170451, 0.14890390717125343,
      0.14669232557375783, 0.14441403443562542, 0.14206987211727135,
      0.13966070529690694, 0.13718742870434703, 0.13465096484499861,
      0.1320522637140529, 0.12939230250103342, 0.12667208528477875,
      0.12389264271897638, 0.12105503170835374, 0.11816033507564375,
      0.11520966121942663, 0.11220414376300457, 0.10914494119437143,
      0.10603323649746643, 0.10287023677478763, 0.099657172861543436,
      0.09639529893141735, 0.093085892094148387, 0.089730251985020743,
      0.08632970034641, 0.082885580601547881, 0.079399257420641148,
      0.0758721162794938, 0.07230556301078872, 0.068701023348172435,
      0.06505994246332, 0.06138378449611509, 0.057674032078123522,
      0.053932185849519226, 0.050159763969621143, 0.046358301621226561,
      0.042529350508867844, 0.038674478351240993, 0.034795268367889834,
      0.030893318760378541, 0.026970242188126006, 0.023027665239047979,
      0.019067227895230743, 0.01509058299376588, 0.011099395682982155,
      0.0070953428742419888, 0.0030801126894499237, -0.00094459609547983825,
      -0.0049770746110373021, -0.00901560445823131, -0.01305845827620207,
      -0.017103900313128972, -0.021150187000261542, -0.025195567528869603,
      -0.029238284429924766, -0.033276574156289027, -0.037308667667266524,
      -0.041332791015276066, -0.0453471659344637, -0.049350010431055906,
      -0.053339539375265504, -0.057313965094529427, -0.061271497967898686,
      -0.065210347021376638, -0.06912872052399352, -0.073024826584444133,
      -0.076896873748052208, -0.080743071593895085, -0.084561631331887016,
      -0.088350766399584224, -0.0921086930585591, -0.095833630990123708,
      -0.099523803890204529, -0.10317744006316518, -0.10679277301439152,
      -0.11036804204144464, -0.11390149282356105, -0.11739137800933661,
      -0.12083595780237535, -0.12423350054472163, -0.12758228329787721,
      -0.13088059242121297, -0.13412672414759111, -0.13731898515599125,
      -0.14045569314095852, -0.14353517737870622, -0.14655577928965333,
      -0.14951585299723527, -0.15241376588279026, -0.15524789913636339,
      -0.15801664830320555, -0.16071842382583107, -0.16335165158143963,
      -0.16591477341451083, -0.16840624766443713, -0.17082454968796723,
      -0.1731681723763554, -0.17543562666699491, -0.17762544204938546,
      -0.17973616706529388, -0.18176636980290228, -0.18371463838483548,
      -0.18557958144985484, -0.18735982862810469, -0.18905403100975257,
      -0.19066086160683957, -0.19217901580824318, -0.19360721182756849,
      -0.19494419114382436, -0.19618871893478665, -0.19733958450284506,
      -0.19839560169326026, -0.19935560930464602, -0.20021847149159261,
      -0.20098307815926833, -0.20164834534988352, -0.20221321562091787,
      -0.20267665841495303, -0.20303767042103149, -0.20329527592740387,
      -0.20344852716555845, -0.20349650464544766, -0.20343831748176663,
      -0.20327310371122995, -0.20300003060070429, -0.20261829494614264,
      -0.20212712336219302, -0.20152577256241613, -0.20081352963002624,
      -0.199989712279056, -0.19905366910588479, -0.198004779831058,
      -0.19684245553128757, -0.19556613886163426, -0.19417530426772686,
      -0.19266945818802855, -0.19104813924603384, -0.18931091843238049,
      -0.1874573992768141, -0.18548721800993193, -0.18340004371471624,
      -0.18119557846775958, -0.17887355747016742, -0.17643374916812504,
      -0.17387595536304459, -0.17120001131134394, -0.168405785813729,
      -0.16549318129407198, -0.16246213386778546, -0.15931261339970854,
      -0.15604462355150886, -0.15265820181856171, -0.14915341955635181,
      -0.14553038199632942, -0.14178922825130086, -0.13793013131030724,
      -0.13395329802301714, -0.12985896907367048, -0.12564741894454853,
      -0.121318955869036, -0.11687392177427976, -0.11231269221344642,
      -0.10763567628768685, -0.10284331655774262, -0.097936088945323768,
      -0.092914502624236478, -0.087779099901345747, -0.082530456087409457,
      -0.077169179357802348, -0.071695910603261331, -0.066111323270643674,
      -0.060416123193770904, -0.054611048414456111, -0.04869686899375459,
      -0.0426743868135182, -0.036544435368311479, -0.030307879547807958,
      -0.023965615409711757, -0.017518569943285288, -0.010967700823599772,
      -0.0043139961565749965, 0.0024415257850806879, 0.00929781683497466,
      0.016253799215022943, 0.023308365826260648, 0.03046038054838026,
      0.037708678547867178, 0.045052066594628064, 0.052489323386990958,
      0.060019199884998438, 0.06764041965184836, 0.075351679203312441,
      0.083151648365145769, 0.09103897063822769, 0.099012263571355369,
      0.10707011914158301, 0.11521110414195379, 0.12343376057648936,
      0.13173660606227877, 0.14011813423859082, 0.14857681518281166,
      0.15711109583306443, 0.16571940041743541, 0.17440013088954723,
      0.18315166737044425, 0.19197236859656397, 0.20086057237366131,
      0.20981459603657243, 0.21883273691457719, 0.2279132728022871,
      0.23705446243584927, 0.24625454597434951, 0.25551174548618449,
      0.26482426544031151, 0.27419029320217386, 0.283607999534138,
      0.29307553910028616, 0.30259105097537653, 0.31215265915784673,
      0.32175847308662342, 0.33140658816163304, 0.34109508626777446,
      0.35082203630227393, 0.36058549470511431, 0.37038350599252251,
      0.38021410329320249, 0.39007530888720893, 0.39996513474728634,
      0.40988158308245209, 0.41982264688370408, 0.42978631047161769,
      0.439770550045707, 0.44977333423533628, 0.45979262465200538,
      0.46982637644285546, 0.47987253884518077, 0.48992905574183021,
      0.49999386621719633, 0.51006490511379932, 0.52014010358907536,
      0.53021738967239374, 0.5402946888219633, 0.550369924481533,
      0.56044101863674423, 0.570505892370813, 0.58056246641955744,
      0.59060866172543824, 0.60064239999052538, 0.61066160422818694,
      0.6206641993133114, 0.63064811253096575, 0.64061127412318219,
      0.650551617833862, 0.66046708145149513, 0.67035560734962008,
      0.68021514302478481, 0.69004364163189824, 0.69983906251678707,
      0.70959937174579235, 0.71932254263221673, 0.72900655625953925,
      0.7386494020011567, 0.7482490780365304, 0.75780359186359481,
      0.76731096080722694, 0.77676921252370734, 0.78617638550089408,
      0.79553052955411152, 0.80482970631748219, 0.81407198973060768,
      0.82325546652049308, 0.8323782366784509, 0.841438413932033,
      0.85043412621163317, 0.85936351611182282, 0.86822474134716665,
      0.87701597520239749, 0.88573540697691144, 0.894381242423299,
      0.90295170417997617, 0.911445032197604, 0.91985948415933083,
      0.9281933358946679, 0.93644488178686469, 0.94461243517372107,
      0.95269432874170112, 0.960688914913255, 0.96859456622720908,
      0.97640967571217951, 0.98413265725284316, 0.99176194594903277,
      0.99929599846751826, 1.0067332933863868, 1.0140723315319804,
      1.0213116363082178, 1.0284497540183088, 1.0354852541787198,
      1.0424167298253366, 1.0492427978117407, 1.0559620990995529,
      1.0625732990407324, 1.0690750876517989, 1.075466179879907,
      1.0817453158607016, 1.0879112611679231, 1.0939628070546661,
      1.0998987706862926, 1.1057179953649119, 1.1114193507453936,
      1.1170017330428821, 1.1224640652317548, 1.1278052972360189,
      1.1330244061110637, 1.1381203962168072, 1.143092299382126,
      1.1479391750606431, 1.1526601104777581, 1.1572542207689656,
      1.1617206491094345, 1.166058566834802, 1.1702671735532373,
      1.1743456972487023, 1.1782933943754661, 1.1821095499438263,
      1.1857934775970675, 1.1893445196796781, 1.1927620472967784,
      1.1960454603648456, 1.199194187653702, 1.2022076868197944,
      1.2050854444308039, 1.2078269759815863, 1.2104318259015026,
      1.2128995675531389, 1.2152298032224542, 1.2174221641004241,
      1.2194763102561772, 1.2213919306016967, 1.2231687428481139,
      1.2248064934536496, 1.22630495756327, 1.2276639389400679,
      1.2288832698884709, 1.2299628111693113, 1.2309024519068217,
      1.2317021094876284, 1.2323617294517968, 1.2328812853760169,
      1.2332607787489722, 1.2335002388390066, 1.2335997225541238,
      1.2335593142944234, 1.2333791257970672, 1.2330592959738138,
      1.2325999907412617, 1.2320014028438557, 1.2312637516697595,
      1.2303872830596903, 1.2293722691087954, 1.2282190079616935,
      1.22692782360076, 1.2254990656277667, 1.2239331090389822,
      1.2222303539938244, 1.2203912255772016, 1.2184161735556154,
      1.2163056721271781, 1.2140602196656121, 1.2116803384583805,
      1.2091665744390709, 1.2065194969141133, 1.2037396982839852,
      1.2008277937590173, 1.1977844210699202, 1.1946102401731524,
      1.1913059329512765, 1.1878722029084, 1.1843097748608498,
      1.1806193946232229, 1.1768018286899045, 1.172857863912228,
      1.16878830717139, 1.164593985047256, 1.1602757434831821,
      1.1558344474470363, 1.151270980588498, 1.1465862448927875,
      1.141781160331018, 1.1368566645072256, 1.1318137123022944,
      1.1266532755148653, 1.1213763424994039, 1.1159839178015458,
      1.110477021790881, 1.1048566902913168, 1.0991239742091474,
      1.0932799391590033, 1.0873256650877832, 1.0812622458967751,
      1.0750907890620482, 1.0688124152532823, 1.0624282579512099,
      1.0559394630637675, 1.0493471885411383, 1.042652603989805,
      1.0358568902857799, 1.0289612391871434, 1.0219668529460242,
      1.0148749439201969, 1.0076867341844169, 1.0004034551416319,
      0.99302634713421745, 0.9855566590554159, 0.97799564796102378,
      0.97034457868160573, 0.96260472343521941, 0.95477736144094993,
      0.94686377853325232, 0.93886526677731841, 0.930783124085614,
      0.92261865383564179, 0.91437316448916939, 0.90604796921296149,
      0.8976443855012326, 0.88916373479987121, 0.88060734213261671,
      0.87197653572933731, 0.8632726466564371, 0.85449700844967469,
      0.84565095674934143, 0.8367358289380793, 0.82775296378136232,
      0.81870370107078072, 0.80958938127029034, 0.80041134516548984,
      0.79117093351607815, 0.7818694867115652, 0.77250834443041683,
      0.76308884530266763, 0.7536123265761614, 0.74408012378650645,
      0.7344935704308615, 0.72485399764564618, 0.71516273388825791,
      0.70542110462296181, 0.69563043201095409, 0.68579203460479565,
      0.67590722704720541, 0.6659773197744181, 0.65600361872407786,
      0.64598742504784334, 0.6359300348287551, 0.62583273880344037,
      0.61569682208925491, 0.60552356391640871, 0.59531423736520783,
      0.58507010910841228, 0.57479243915882849, 0.56448248062221285,
      0.5541414794555074, 0.54377067423052594, 0.53337129590307364,
      0.52294456758768659, 0.51249170433787161, 0.5020139129321044,
      0.49151239166543442, 0.48098833014690573, 0.47044290910276332,
      0.459877300185455, 0.44929266578860838, 0.4386901588678328,
      0.42807092276754483, 0.41743609105375362, 0.4067867873528862,
      0.3961241251966548, 0.38544920787298237, 0.37476312828308184,
      0.36406696880458167, 0.35336180116085592, 0.3426486862964615,
      0.33192867425876177, 0.32120280408573731, 0.3104721036999431,
      0.29973758980867415, 0.2890002678103552, 0.278261131707056,
      0.26752116402323028, 0.25678133573064349, 0.24604260617944895,
      0.235305923035456, 0.22457222222349538, 0.2138424278770025,
      0.20311745229362224, 0.19239819589697221, 0.18168554720446939,
      0.17098038280114436, 0.1602835673195788, 0.1495959534257035,
      0.1389183818106649, 0.12825168118852398, 0.11759666829986584,
      0.10695414792126999, 0.0963249128805157, 0.085709744077617042,
      0.075109410511466551, 0.06452466931223487, 0.053956265779277514,
      0.043404933424642578, 0.032871394022048694, 0.022356357661300178,
      0.011860522808077065, 0.0013845763689981742, -0.0090708062380247742,
      -0.019504961008307231, -0.029917235269764413, -0.040306987597291004,
      -0.050673587722155355, -0.061016416436505558, -0.071334865493111882,
      -0.0816283375003215, -0.091896245812410488, -0.1021380144153544,
      -0.11235307780813136, -0.12254088087960538, -0.13270087878114939,
      -0.14283253679501925, -0.15293533019860636, -0.16300874412468569,
      -0.17305227341769461, -0.18306542248619931, -0.19304770515159381,
      -0.20299864449318536, -0.21291777268971118, -0.2228046308574273,
      -0.2326587688848486, -0.2424797452642557, -0.25226712692010245,
      -0.2620204890343375, -0.27173941486888509, -0.28142349558524565,
      -0.29107233006147071, -0.30068552470649523, -0.31026269327201578,
      -0.3198034566620378, -0.32930744274009627, -0.33877428613443333,
      -0.34820362804108329, -0.3575951160251003, -0.36694840381996857,
      -0.37626315112534181, -0.38553902340326951, -0.39477569167291165,
      -0.40397283230401537, -0.4131301268091282, -0.42224726163476867,
      -0.43132392795161667, -0.44035982144386021, -0.44935464209784082,
      -0.45830809399007, -0.46721988507476431, -0.4760897269710353,
      -0.48491733474983184, -0.49370242672073072, -0.502444724218766,
      -0.51114395139133084, -0.51979983498536253, -0.52841210413482287,
      -0.536980490148705, -0.54550472629959923, -0.55398454761297466,
      -0.56241969065730013, -0.57080989333507437, -0.57915489467497516,
      -0.5874544346251136, -0.5957082538476336, -0.60391609351470021,
      -0.612077695105983, -0.62019280020783152, -0.62826115031410845,
      -0.63628248662897846, -0.64425654987156844, -0.652183080082772,
      -0.66006181643420436, -0.667892497039461, -0.6756748587677579,
      -0.683408637060091, -0.69109356574799885, -0.69872937687502068,
      -0.70631580052097331, -0.71385256462914715, -0.7213393948364919,
      -0.72877601430691508, -0.73616214356777654, -0.74349750034970308,
      -0.75078179942974477, -0.75801475247805916, -0.76519606790812189,
      -0.772325450730624, -0.77940260241109094, -0.78642722073133986,
      -0.79339899965484606, -0.80031762919608962, -0.807182795293977,
      -0.81399417968941656, -0.82075145980710418, -0.82745430864159886,
      -0.83410239464779057, -0.84069538163577961, -0.84723292867025812,
      -0.8537146899744894, -0.86014031483886977, -0.86650944753424808,
      -0.87282172722992379, -0.87907678791653365, -0.88527425833371931,
      -0.89141376190278754, -0.897494916664288, -0.90351733522061872,
      -0.9094806246837116, -0.9153843866277851, -0.92122821704728985,
      -0.927011706319989, -0.93273443917530652, -0.93839599466789514,
      -0.94399594615650906, -0.94953386128820938, -0.9550093019878646,
      -0.960421824453084, -0.96577097915448951, -0.9710563108414354,
      -0.97627735855312925, -0.98143365563521689, -0.986524729761813,
      -0.99155010296301094, -0.99650929165783619, -1.0014018066927226,
      -1.00622715338544, -1.0109848315745009, -1.0156743356740789,
      -1.0202951547343539, -1.0248467725073829, -1.0293286675183664,
      -1.0337403131424141, -1.0380811776867052, -1.0423507244780825,
      -1.0465484119560342, -1.0506736937710324, -1.0547260188882537,
      -1.0587048316965775, -1.0626095721229163, -1.0664396757517645,
      -1.0701945739500043, -1.0738736939968769, -1.0774764592191128,
      -1.0810022891311739, -1.0844505995805285, -1.0878208028979808,
      -1.0911123080529559, -1.0943245208136714, -1.0974568439122265,
      -1.1005086772144532, -1.1034794178945226, -1.1063684606142841,
      -1.1091751977071713, -1.1118990193667064, -1.1145393138395046,
      -1.1170954676226796, -1.1195668656656297, -1.1219528915760995,
      -1.1242529278304509, -1.1264663559880501, -1.1285925569097381,
      -1.1306309109802355, -1.1325807983344713, -1.1344415990876771,
      -1.1362126935692329, -1.1378934625601058, -1.1394832875338496,
      -1.1409815509010452, -1.1423876362570649, -1.1437009286331277,
      -1.1449208147504815, -1.1460466832776592, -1.1470779250906724,
      -1.1480139335360833, -1.1488541046967911, -1.1495978376605021,
      -1.1502445347907067, -1.1507936020000817, -1.1512444490262508,
      -1.1515964897096833, -1.1518491422737749, -1.152001829606824,
      -1.1520539795459341, -1.1520050251626339, -1.1518544050501556,
      -1.1516015636121941, -1.1512459513530993, -1.1507870251693249,
      -1.1502242486420129, -1.1495570923306593, -1.1487850340676344,
      -1.1479075592535333, -1.1469241611531529, -1.1458343411920331,
      -1.1446376092533825, -1.1433334839753186, -1.1419214930482313,
      -1.1404011735121955, -1.1387720720542884, -1.1370337453056663,
      -1.1351857601383017, -1.1332276939612185, -1.1311591350161332,
      -1.1289796826723326, -1.1266889477207003, -1.1242865526667318,
      -1.1217721320224052, -1.1191453325968137, -1.1164058137853923,
      -1.1135532478576331, -1.1105873202431358, -1.1075077298159022,
      -1.1043141891766934, -1.1010064249333904, -1.0975841779791433,
      -1.0940472037682603, -1.0903952725896755, -1.0866281698378442,
      -1.0827456962810051, -1.0787476683266009, -1.074633918283822,
      -1.0704042946230361, -1.0660586622321377, -1.0615969026694976,
      -1.0570189144136015, -1.0523246131090653, -1.0475139318090396,
      -1.0425868212138316, -1.0375432499056214, -1.0323832045791799,
      -1.0271066902684474, -1.0217137305688959, -1.0162043678554846,
      -1.0105786634962297, -1.0048366980611143, -0.99897857152637171,
      -0.99300440347393937, -0.98691433328603706, -0.98070852033472522,
      -0.97438714416635563, -0.967950404680836, -0.9613985223055197,
      -0.95473173816379064, -0.94795031423804021, -0.94105453352710922,
      -0.93404470019801733, -0.92692113973190182, -0.91968419906409893,
      -0.91233424671824948, -0.90487167293438486, -0.89729688979082478,
      -0.8896103313199587, -0.8818124536176426, -0.87390373494628371,
      -0.8658846758314781, -0.85775579915211142, -0.84951765022390191,
      -0.84117079687625962, -0.83271582952247125, -0.82415336122302529,
      -0.81548402774219475, -0.80670848759759983, -0.79782742210292756,
      -0.78884153540353141, -0.77975155450502587, -0.77055822929474971,
      -0.76126233255605058, -0.75186465997539509, -0.74236603014216362,
      -0.73276728454124651, -0.72306928753822775, -0.71327292635724926,
      -0.70337911105149176, -0.69338877446619684, -0.683302872194279,
      -0.67312238252443291, -0.66284830638178838, -0.65248166726098378,
      -0.64202351115181477, -0.6314749064572216, -0.62083694390385047,
      -0.6101107364449494, -0.59929741915576962, -0.58839814912137245,
      -0.57741410531688087, -0.56634648848017566, -0.55519652097701166,
      -0.54396544665863777, -0.532654530711828, -0.52126505950141877,
      -0.50979834040536454, -0.49825570164226907, -0.4866384920914984,
      -0.47494808110582631, -0.46318585831670261, -0.45135323343214462,
      -0.43945163602725446, -0.42748251532748494, -0.41544733998460515,
      -0.4033475978454667, -0.39118479571356424, -0.37896045910351378,
      -0.36667613198839571, -0.35433337654012964, -0.34193377286282312,
      -0.32947891871926582, -0.31697042925052415, -0.30440993668876765,
      -0.29179909006339161, -0.27913955490045333, -0.26643301291556348,
      -0.25368116170023847, -0.24088571440185103, -0.22804839939720728,
      -0.21517095995986166, -0.20225515392125976, -0.18930275332574673,
      -0.17631554407961864, -0.16329532559418897, -0.15024391042309254,
      -0.13716312389382779, -0.12405480373363054, -0.11092079968992431,
      -0.097762973145199286, -0.084583196726705639, -0.071383353910815156,
      -0.058165338622359807, -0.044931054828917981, -0.031682416130258094,
      -0.018421345342969186, -0.0051497740804935105, 0.0081303576713946876,
      0.021417101983569626, 0.034708503416704221, 0.048002599458718626,
      0.06129742096614442, 0.074590992609486872, 0.087881333322301136,
      0.10116645675392977, 0.11444437172579572, 0.12771308269097725,
      0.14097059019712033, 0.1542148913523797, 0.16744398029436525,
      0.1806558486618785, 0.19384848606934391, 0.20701988058378312,
      0.22016801920413492, 0.23329088834288583, 0.24638647430971491,
      0.25945276379717752, 0.27248774436808826, 0.28548940494464609,
      0.29845573629897559, 0.3113847315450694, 0.32427438663188546,
      0.33712270083749069, 0.34992767726410234, 0.36268732333381759,
      0.37539965128497144, 0.38806267866881949, 0.40067442884659732,
      0.4132329314865455, 0.42573622306097952, 0.4381823473430983,
      0.45056935590339331, 0.46289530860558775, 0.47515827410179012,
      0.48735633032689529, 0.49948756499186564, 0.51155007607592318,
      0.52354197231737187, 0.5354613737029108, 0.54730641195533625,
      0.55907523101938517, 0.57076598754565711, 0.58237685137235007,
      0.59390600600477672, 0.60535164909235639, 0.61671199290308243,
      0.627985264795162, 0.63916970768578019, 0.650263580516795,
      0.66126515871716007, 0.67217273466202454, 0.68298461812824685,
      0.69369913674626, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      -1.1313044797655929, -1.1310901056134384, -1.1307670797257874,
      -1.1303353672139627, -1.1297949516856276, -1.1291458353830421,
      -1.1283880393166719, -1.127521603394058, -1.1265465865438926,
      -1.1254630668352097, -1.124271141591632, -1.1229709275006021,
      -1.1215625607175217, -1.1200461969647419, -1.1184220116253378,
      -1.1166901998315966, -1.114850976548168, -1.1129045766498085,
      -1.1108512549936633, -1.1086912864860339, -1.1064249661435677,
      -1.1040526091488245, -1.1015745509001627, -1.0989911470559026,
      -1.0963027735727069, -1.093509826738146, -1.0906127231973985,
      -1.0876118999740387, -1.084507814484885, -1.0813009445488559,
      -1.0779917883898067, -1.0745808646333113, -1.0710687122973541,
      -1.0674558907769043, -1.0637429798223432, -1.059930579511718,
      -1.0560193102167992, -1.0520098125629203, -1.0479027473825751,
      -1.0436987956627617, -1.0393986584860546, -1.0350030569653859,
      -1.0305127321725351, -1.0259284450603086, -1.0212509763784052,
      -1.0164811265829681, -1.0116197157398066, -1.0066675834213044,
      -1.0016255885970011, -0.99649460951786162, -0.99127554359423187,
      -0.98596930726749388, -0.98057683587542521, -0.97509908351128682,
      -0.96953702287663546, -0.963891645127897, -0.958163959716708,
      -0.95235499422404957, -0.9464657941882, -0.94049742292652672,
      -0.93445096135115224, -0.92832750777851858, -0.92212817773288658,
      -0.91585410374379916, -0.90950643513755447, -0.90308633782271885,
      -0.89659499406972654, -0.89003360228460526, -0.883403376776876,
      -0.87670554752167684, -0.86994135991615218, -0.86311207453016781,
      -0.85621896685140286, -0.84926332702487251, -0.84224645958694078,
      -0.83516968319388751, -0.82803433034508434, -0.82084174710085056,
      -0.81359329279505044, -0.80629033974250341, -0.79893427294127606,
      -0.791526489769928, -0.78406839967978648, -0.77656142388232341,
      -0.76900699503171643, -0.76140655690267334, -0.75376156406359374,
      -0.74607348154516873, -0.73834378450448168, -0.730573957884715,
      -0.72276549607054608, -0.71491990253931914, -0.70703868950808835,
      -0.69912337757662935, -0.69117549536650968, -0.68319657915631782,
      -0.67518817251314744, -0.66715182592044386, -0.65908909640230451,
      -0.65100154714434544, -0.642890747111236, -0.6347582706610051,
      -0.62660569715623227, -0.61843461057222748, -0.6102465991023146,
      -0.6020432547603275, -0.5938261729804315, -0.58559695221438857,
      -0.577357193526376, -0.5691085001854812, -0.56085247725598242,
      -0.55259073118554736, -0.544324869391453, -0.53605649984496417,
      -0.52778723065397926, -0.51951866964407456, -0.51125242393806969,
      -0.50299009953423324, -0.49473330088326478, -0.486483630464167,
      -0.47824268835914646, -0.47001207182766258, -0.46179337487975858,
      -0.45358818784880051, -0.44539809696375554, -0.43722468392113834,
      -0.42906952545675875, -0.42093419291739936, -0.412820251832556,
      -0.40472926148637245, -0.39666277448990406, -0.38862233635383792,
      -0.38060948506180881, -0.37262575064443804, -0.36467265475423249,
      -0.35675171024147678, -0.34886442073124957, -0.34101228020169849,
      -0.3331967725637105, -0.32541937124210629, -0.31768153875849331,
      -0.30998472631591412, -0.30233037338541624, -0.29471990729468467,
      -0.28715474281886194, -0.27963628177369171, -0.27216591261111822,
      -0.26474501001746953, -0.25737493451436011, -0.25005703206243868,
      -0.24279263366811465, -0.23558305499339063, -0.22842959596892989,
      -0.22133354041048733, -0.21429615563883048, -0.20731869210327875,
      -0.200402383008984, -0.19354844394807902, -0.18675807253481927,
      -0.18003244804483698, -0.17337273105863402, -0.16678006310943214,
      -0.16025556633550087, -0.15380034313708346, -0.14741547583803691,
      -0.1411020263523034, -0.1348610358553296, -0.1286935244605478,
      -0.12260049090102734, -0.11658291221641776, -0.11064174344528208,
      -0.10477791732293953, -0.098992343984917588, -0.093285910676120853,
      -0.087659481465827624, -0.082113896968604716, -0.076649974071253429,
      -0.071268505665880541, -0.065970260389190141, -0.060755982368101438,
      -0.055626390971773652, -0.050582180570143874, -0.045624020299060736,
      -0.040752553832105826, -0.035968399159188036, -0.031272148372000791,
      -0.026664367456417853, -0.0221455960919189, -0.017716347458113915,
      -0.013377108048453018, -0.0091283374911908036, -0.00497046837768092,
      -0.00090390609807287914, 0.0030709713155210733, 0.0069538133383229631,
      0.010744297094582494, 0.014442127491607309, 0.018047037346067878,
      0.021558787502518141, 0.024977166944080434, 0.02830199289523521,
      0.031533110916670416, 0.034670394992134847, 0.037713747607257792,
      0.040663099820281122, 0.043518411324669506, 0.046279670503558523,
      0.048946894475996976, 0.051520129134960242, 0.0539994491770923,
      0.056384958124153325, 0.058676788336144259, 0.060875101016081845,
      0.062980086206404245, 0.064991962776989293, 0.0669109784047642,
      0.068737409544894781, 0.070471561393544574, 0.07211376784218923,
      0.073664391423484729, 0.075123823248683552, 0.076492482936593512,
      0.077770818534088709, 0.078959306428167, 0.08005845124956662,
      0.081068785767949084, 0.081990870778657549, 0.082825294981068068,
      0.083572674848549688, 0.084233654490048243, 0.0848089055033251,
      0.08529912681986318, 0.085705044541478745, 0.086027411768660217,
      0.086267008420670921, 0.086424641047449083, 0.086501142633342187,
      0.086497372392714114, 0.086414215557473459, 0.086252583156558885,
      0.08601341178743778, 0.0856976633796621, 0.085306324950537443,
      0.084840408352958641, 0.084300950015472484, 0.083689010674620257,
      0.083005675099632734, 0.082252051809535182, 0.081429272782730849,
      0.080538493159135346, 0.079580890934933507, 0.078557666650027641,
      0.077470043068264827, 0.076319264850511243, 0.07510659822066304,
      0.0738333306246729, 0.072500770382681393, 0.071110246334337962,
      0.069663107477406672, 0.068160722599745441, 0.066604479904755431,
      0.064995786630397123, 0.063336068661872455, 0.061626770138074882,
      0.059869353051908873, 0.058065296844585411, 0.05621609799400136,
      0.054323269597311347, 0.052388340947800947, 0.050412857106180348,
      0.048398378466406405, 0.046346480316155375, 0.044258752392061382,
      0.042136798429844038, 0.039982235709444758, 0.03779669459529679,
      0.035581818071855578, 0.033339261274513254, 0.031070691016030841,
      0.028777785308614079, 0.026462232881766863, 0.024125732696055849,
      0.021769993452919155, 0.019396733100659196, 0.017007678336749724,
      0.014604564106606203, 0.012189133098949936, 0.00976313523791393,
      0.00732832717202847, 0.0048864717602360094, 0.0024393375550707808,
      -1.1301716840272924E-5, -0.002463667676814163, -0.0049159778185421249,
      -0.0073664460347521374, -0.0098132831459696243, -0.012254697431210528,
      -0.01468889516047045, -0.0171140811288428, -0.019528459192124828,
      -0.021930232803752121, -0.024317605552908489, -0.0266887817036569,
      -0.029041966734936489, -0.031375367881270037, -0.03368719467402246,
      -0.035975659483059842, -0.038238978058647233, -0.040475370073429426,
      -0.04268305966433749, -0.044860275974263966, -0.047005253693346953,
      -0.0491162335997074, -0.051191463099480992, -0.053229196765985823,
      -0.055227696877868306, -0.057185233956070267, -0.059100087299459432,
      -0.060970545518963665, -0.062794907070054473, -0.064571480783422258,
      -0.066298586393684272, -0.067974555065971443, -0.069597729920239076,
      -0.071166466553141378, -0.07267913355732, -0.0741341130379506,
      -0.075529801126390642, -0.076864608490781514, -0.078136960843446457,
      -0.079345299444937456, -0.080488081604575726, -0.081563781177341657,
      -0.0825708890569586, -0.083507913665028521, -0.084373381436066888,
      -0.085165837298295591, -0.085883845150045171, -0.086525988331624684,
      -0.087090870092514552, -0.087577114053743049, -0.087983364665304709,
      -0.088308287658481352, -0.088550570492929317, -0.088708922798395,
      -0.088782076810926952, -0.088768787803445756, -0.088667834510544163,
      -0.0884780195473895, -0.0881981698225888, -0.087827136944902476,
      -0.087363797623674549, -0.086807054062853023, -0.08615583434848513,
      -0.085409092829562189, -0.084565810492097743, -0.083624995326321,
      -0.082585682686871581, -0.081446935645885732, -0.080207845338854722,
      -0.0788675313031581, -0.077425141809155246, -0.075879854183735773,
      -0.0742308751262249, -0.072477441016540939, -0.070618818215511747,
      -0.068654303357250077, -0.0665832236334922, -0.064404937069813428,
      -0.062118832793626594, -0.059724331293879877, -0.057220884672364872,
      -0.054607976886555609, -0.051885123983901091, -0.049051874327484112,
      -0.04610780881298341, -0.043052541076857555, -0.039885717695683248,
      -0.036607018376581479, -0.033216156138663154, -0.029712877485436752,
      -0.026096962568111011, -0.022368225339739506, -0.018526513700155338,
      -0.014571709631632478, -0.010503729325238693, -0.0063225232978207646,
      -0.0020280764995836975, 0.0023795915877765361, 0.0069004268624319742,
      0.011534340523301864, 0.016281209000491431, 0.021140873895318782,
      0.026113141929956785, 0.03119778490671897, 0.036394539677006468,
      0.041703108119941365, 0.047123157130700685, 0.052654318618561513,
      0.058296189514679964, 0.064048331789597485, 0.069910272480491947,
      0.0758815037281732, 0.081961482823820472, 0.088149632265461325,
      0.094445339824189, 0.1008479586201059, 0.10735680720798121,
      0.11397116967261646, 0.12069029573389754, 0.12751340086150487,
      0.13443966639928318, 0.14146823969921407, 0.14859823426499638,
      0.155828729905179, 0.16315877289582267, 0.17058737615265634,
      0.17811351941268816, 0.18573614942522457, 0.19345418015226173,
      0.2012664929781911, 0.20917193692878502, 0.21716932889939727,
      0.22525745389232407, 0.23343506526327645, 0.24170088497690034,
      0.25005360387127262, 0.25849188193132411, 0.26701434857110456,
      0.27561960292483345, 0.28430621414665141, 0.2930727217190105,
      0.30191763576960295, 0.31083943739678016, 0.31983657900334428,
      0.328907484638654, 0.33805055034893533, 0.34726414453573384,
      0.35654660832238066, 0.36589625592841135, 0.37531137505181633,
      0.38479022725903378, 0.39433104838258803, 0.40393204892625567,
      0.4135914144776644, 0.42330730612821049, 0.43307786090019335,
      0.44290119218104174, 0.45277539016452328, 0.46269852229882696,
      0.47266863374139023, 0.48268374782035595, 0.49274186650253293,
      0.50284097086773971, 0.51297902158940567, 0.52315395942129728,
      0.53336370569024361, 0.543606162794727, 0.5538792147092082,
      0.5641807274940549, 0.57450854981092425, 0.58486051344347434,
      0.5952344338232648, 0.60562811056069454, 0.61603932798084771,
      0.62646585566409274, 0.63690544899129475, 0.64735584969350368,
      0.65781478640594515, 0.6682799752261972, 0.678749120276373,
      0.68921991426918217, 0.69969003907770433, 0.71015716630872172,
      0.72061895787946084, 0.73107306659759619, 0.741517136744332,
      0.75194880466043734, 0.76236569933505449, 0.77276544299713223,
      0.783145651709318, 0.79350393596415425, 0.80383790128241084,
      0.81414514881340194, 0.82442327593711884, 0.8346698768680092,
      0.84488254326025336, 0.85505886481437177, 0.86519642988498646,
      0.87529282608958625, 0.88534564091812817, 0.8953524623432999,
      0.90531087943130306, 0.91521848295295782, 0.92507286599499661,
      0.93487162457135609, 0.94461235823432055, 0.9542926706853454,
      0.96391017038538673, 0.97346247116458429, 0.98294719283113507,
      0.99236196177917768, 1.0017044115955362, 1.0109721836651575,
      1.0201629277750799, 1.0292743027167579, 1.0383039768866078,
      1.047249628884573, 1.05610894811059, 1.0648796353587633,
      1.0735594034091025, 1.0821459776166542, 1.090637096497892,
      1.0990305123141688, 1.1073239916521145, 1.1155153160007936,
      1.1236022823254834, 1.1315827036379165, 1.1394544095628247,
      1.1472152469006518, 1.1548630801862572, 1.1623957922434909,
      1.1698112847354687, 1.1771074787104083, 1.184282315142879,
      1.1913337554703314, 1.1982597821247394, 1.2050583990592354,
      1.21172763226959, 1.2182655303103969, 1.2246701648058205,
      1.2309396309547858, 1.2370720480304538, 1.2430655598738745,
      1.2489183353816662, 1.2546285689876004, 1.2601944811379662,
      1.2656143187605895, 1.27088635572737, 1.2760088933102363,
      1.280980260630376, 1.2857988151006394, 1.2904629428609904,
      1.2949710592068966, 1.2993216090105426, 1.303513067134753,
      1.3075439388395276, 1.3114127601810719, 1.3151180984032229,
      1.3186585523211674, 1.3220327526973574, 1.3252393626095189,
      1.3282770778106596, 1.3311446270809901, 1.3338407725716563,
      1.3363643101402047, 1.338714069677686, 1.3408889154273211,
      1.3428877462946434, 1.3447094961490393, 1.3463531341166088,
      1.3478176648642759, 1.3491021288750753, 1.3502056027145435,
      1.3511271992881511, 1.3518660680897119, 1.3524213954407023,
      1.3527924047204412, 1.3529783565870621, 1.352978549189235,
      1.3527923183685726, 1.3524190378526904, 1.3518581194388561,
      1.3511090131681962, 1.3501712074904126, 1.3490442294189757,
      1.3477276446767552, 1.3462210578320513, 1.3445241124250065,
      1.3426364910843607, 1.3405579156345235, 1.3382881471929542,
      1.3358269862578098, 1.3331742727858593, 1.3303298862606474,
      1.3272937457508838, 1.3240658099590681, 1.3206460772603246,
      1.3170345857314552, 1.313231413170209, 1.3092366771047566,
      1.3050505347933967, 1.300673183214474, 1.296104859046542,
      1.2913458386387655, 1.2863964379715898, 1.2812570126076843,
      1.2759279576331808, 1.2704097075892427, 1.2647027363939702,
      1.2588075572546789, 1.2527247225705886, 1.2464548238259385,
      1.2399984914735838, 1.2333563948090902, 1.2265292418353868,
      1.2195177791180047, 1.2123227916309582, 1.2049451025933069,
      1.1973855732964531, 1.1896451029222324, 1.1817246283518421,
      1.1736251239656712, 1.165347601434094, 1.1568931094992803,
      1.1482627337481026, 1.139457596376187, 1.1304788559431938,
      1.1213277071193919, 1.1120053804235994, 1.1025131419525755,
      1.0928522931019222, 1.0830241702786039, 1.0730301446051398,
      1.0628716216155778, 1.0525500409433111, 1.0420668760008509,
      1.031423633651634, 1.0206218538739547, 1.0096631094171209,
      0.99854900544993319, 0.987281179201581, 0.97586129959505941,
      0.96429106687320354, 0.95257221221745036, 0.94070649735943723,
      0.92869571418553376, 0.91654168433441874, 0.90424625878783083,
      0.891811317454574, 0.87923876874792817, 0.86653054915654493,
      0.85368862280897717, 0.84071498103194042, 0.82761164190243885,
      0.81438064979387281, 0.80102407491624361, 0.78754401285059927,
      0.77394258407783012, 0.76022193350194867, 0.74638422996798426,
      0.73243166577461061, 0.7183664561816524, 0.70419083891261081,
      0.68990707365228854, 0.67551744153972926, 0.66102424465653709,
      0.64642980551075624, 0.631736466516413, 0.61694658946889924,
      0.602062555016295, 0.58708676212680244, 0.572021627552406,
      0.55686958528891961, 0.54163308603255844, 0.52631459663316837,
      0.51091659954425916, 0.49544159227000251, 0.47989208680931345,
      0.4642706090971766, 0.44857969844336365, 0.43282190696866735,
      0.41699979903882611, 0.40111595069627209, 0.38517294908984118,
      0.36917339190260728, 0.35311988677797773, 0.33701505074419941,
      0.32086150963743271, 0.30466189752351835, 0.2884188561186074,
      0.27213503420878538, 0.25581308706886191, 0.23945567588042865,
      0.22306546714938702, 0.20664513212304733, 0.1901973462069847,
      0.17372478838174932, 0.15723014061963703, 0.14071608730161736,
      0.12418531463459133, 0.1076405100691058, 0.091084361717688217,
      0.074519557773937067, 0.057948785932502384, 0.04137473281011983,
      0.024800083367816757, 0.0082275203344540013, -0.00834027636826666,
      -0.024900630199187472, -0.041450868569335442, -0.057988323411672864,
      -0.07451033174882371, -0.091014236258633946, -0.10749738583744922,
      -0.1239571361609335, -0.14039085024235018, -0.15679589898811133,
      -0.1731696617505174, -0.18950952687752093, -0.20581289225939628,
      -0.22207716587218262, -0.23829976631778471, -0.25447812336058545,
      -0.27060967846045697, -0.28669188530204359, -0.30272221032019619,
      -0.31869813322143492, -0.33461714750131411, -0.35047676095757407,
      -0.36627449619897268, -0.382007891149673, -0.39767449954905881,
      -0.41327189144688731, -0.4287976536936623, -0.44424939042610234,
      -0.45962472354761941, -0.47492129320368542, -0.490136758251971,
      -0.50526879672720082, -0.52031510630055267, -0.5352734047335681,
      -0.5501414303264236, -0.564916942360513, -0.57959772153519262,
      -0.59418157039865627, -0.60866631377279012, -0.62304979917196768,
      -0.63732989721566735, -0.65150450203482757, -0.66557153167187777,
      -0.679528928474344, -0.69337465948194754, -0.70710671680713766,
      -0.72072311800895694, -0.73422190646018382, -0.747601151707686,
      -0.76085894982588376, -0.77399342376328151, -0.7870027236820043,
      -0.79988502729025113, -0.81263854016762593, -0.82526149608327537,
      -0.83775215730677222, -0.85010881491170465, -0.86232978907189528,
      -0.87441342935022093, -0.88635811497995276, -0.89816225513862091,
      -0.90982428921428737, -0.92134268706425493, -0.93271594926611368,
      -0.94394260736113167, -0.95502122408991141, -0.96595039362031188,
      -0.97672874176757973, -0.98735492620667553, -0.99782763667675467,
      -1.0081455951777765, -1.0183075561592305, -1.0283123067009423,
      -1.0381586666859481, -1.0478454889654192, -1.0573716595156124,
      -1.066736097586843, -1.0759377558444665, -1.0849756205018584,
      -1.0938487114453743, -1.102556082351307, -1.1110968207948222,
      -1.1194700483508639, -1.1276749206870638, -1.1357106276486046,
      -1.1435763933351062, -1.1512714761694771, -1.1587951689587983,
      -1.1661467989472014, -1.1733257278607951, -1.1803313519446283,
      -1.1871631019917102, -1.1938204433641246, -1.2003028760062417,
      -1.2066099344500489, -1.2127411878126431, -1.218696239785894,
      -1.2244747286183133, -1.2300763270891708, -1.2355007424748683,
      -1.2407477165076224, -1.2458170253264935, -1.250708479420783,
      -1.255421923565861, -1.2599572367514476, -1.2643143321023924,
      -1.2684931567920243, -1.2724936919480725, -1.2763159525512451,
      -1.2799599873265077, -1.2834258786271033, -1.2867137423113635,
      -1.2898237276124003, -1.2927560170006873, -1.2955108260396317,
      -1.29808840323416, -1.3004890298724174, -1.3027130198606047,
      -1.3047607195510535, -1.3066325075635767, -1.3083287946001798,
      -1.3098500232531922, -1.3111966678069009, -1.3123692340327398,
      -1.3133682589781237, -1.3141943107489955, -1.3148479882861648,
      -1.3153299211355, -1.3156407692120844, -1.315781222558376,
      -1.3157520010964834, -1.3155538543746248, -1.3151875613078516,
      -1.3146539299131237, -1.3139537970388295, -1.3130880280888217,
      -1.312057516741064, -1.310863184660976, -1.3095059812095715,
      -1.3079868831464609, -1.306306894327832, -1.3044670453994853,
      -1.302468393485021, -1.3003120218692732, -1.2979990396770809,
      -1.2955305815474893, -1.2929078073034908, -1.2901319016173811,
      -1.2872040736718389, -1.2841255568168357, -1.2808976082224472,
      -1.2775215085276974, -1.2739985614855032, -1.2703300936038515,
      -1.2665174537832791, -1.2625620129507706, -1.2584651636901822,
      -1.254228319869277, -1.2498529162634848, -1.2453404081764803,
      -1.2406922710576969, -1.2359100001168577, -1.2309951099356491,
      -1.2259491340766195, -1.2207736246894221, -1.2154701521145015,
      -1.210040304484318, -1.2044856873222289, -1.1988079231391238,
      -1.1930086510279097, -1.1870895262559664, -1.1810522198556639,
      -1.1748984182130446, -1.1686298226547909, -1.1622481490335563,
      -1.1557551273117848, -1.149152501144117, -1.1424420274584768,
      -1.1356254760359523, -1.1287046290895748, -1.1216812808420864,
      -1.1145572371028099, -1.1073343148437262, -1.1000143417748425,
      -1.0925991559189696, -1.0850906051860081, -1.0774905469468388,
      -1.0698008476069125, -1.0620233821796512, -1.0541600338597577,
      -1.0462126935965188, -1.0381832596672178, -1.0300736372507415,
      -1.0218857380014879, -1.0136214796236649, -1.0052827854460764,
      -0.99687158399749221, -0.98838980858270065, -0.97983939685932953,
      -0.97122229041552921, -0.96254043434862091, -0.95379577684479278,
      -0.94499026875992964, -0.936125863201682, -0.92720451511285185,
      -0.91822818085618152, -0.9091988178006476, -0.90011838390933541,
      -0.8909888373289695, -0.88181213598122077, -0.87259023715583039,
      -0.86332509710566463, -0.85401867064377623, -0.844672910742539,
      -0.8352897681349567, -0.82587119091821626, -0.81641912415955253,
      -0.80693550950452386, -0.797422284787762, -0.78788138364626592,
      -0.77831473513533023, -0.76872426334716371, -0.7591118870322815,
      -0.74947951922374378, -0.73982906686429317, -0.73016243043647844,
      -0.72048150359583041, -0.71078817280714157, -0.70108431698392737,
      -0.69137180713113566, -0.6816525059911529, -0.67192826769318148,
      -0.6622009374060519, -0.65247235099450773, -0.64274433467904535,
      -0.63301870469935417, -0.62329726698141585, -0.61358181680831247,
      -0.60387413849480487, -0.59417600506571988, -0.58448917793822341,
      -0.57481540660799046, -0.56515642833935553, -0.55551396785947182,
      -0.54588973705653232, -0.53628543468209056, -0.5267027460575362,
      -0.5171433427847445, -0.50760888246098168, -0.49810100839804905,
      -0.48862134934576018, -0.47917151921974904, -0.46975311683366844,
      -0.46036772563579031, -0.45101691345006945, -0.44170223222168226,
      -0.43242521776706716, -0.42318738952852619, -0.41399025033337089,
      -0.40483528615768272, -0.39572396589469422, -0.386657741127801,
      -0.37763804590825906, -0.36866629653756655, -0.35974389135455481,
      -0.35087221052722622, -0.34205261584931806, -0.33328645054165179,
      -0.32457503905825641, -0.3159196868972966, -0.30732168041680447,
      -0.29878228665524542, -0.29030275315689535, -0.28188430780209855,
      -0.27352815864234092, -0.26523549374021066, -0.25700748101421178,
      -0.24884526808846161, -0.24074998214725038, -0.23272272979449257,
      -0.22476459691805423, -0.21687664855896169, -0.20905992878549781,
      -0.20131546057217542, -0.1936442456835788, -0.18604726456309795,
      -0.17852547622652165, -0.17107981816049075, -0.16371120622582278,
      -0.15642053456566687, -0.14920867551852163, -0.14207647953606012,
      -0.13502477510579131, -0.12805436867852685, -0.12116604460064286,
      -0.11436056505111572, -0.10763866998333607, -0.10100107707166772,
      -0.0944484816627506, -0.087981556731502014, -0.08160095284184056,
      -0.075307298112072069, -0.069101198184947324, -0.062983236202351134,
      -0.056953972784611423, -0.051013946014409964, -0.0451636714252462,
      -0.039403641994471925, -0.033734328140827378, -0.0281561777264858,
      -0.022669616063563082, -0.017275045925076275, -0.011972847560303302,
      -0.0067633787145416763, -0.0016469746532167921, 0.0033760518096749084,
      0.0083054102788456333, 0.013140832740711952, 0.017882073522165021,
      0.022528909245150552, 0.027081138777070045, 0.031538583177055816,
      0.035901085638150705, 0.040168511425416831, 0.044340747810026511,
      0.048417703999363175, 0.052399311063158052, 0.05628552185571703,
      0.060076310934271418, 0.063771674473479117, 0.067371630176132152,
      0.070876217180096651, 0.0742854959615272, 0.077599548234404292,
      0.0808184768464231, 0.083942405671278281, 0.086971479497393062,
      0.08990586391312877, 0.092745745188507173, 0.095491330153508566,
      0.0981428460729664, 0.10070054051812316, 0.1031646812348668,
      0.10553555600871339, 0.10781347252656373, 0.10999875823528824,
      0.11209176019716879, 0.11409284494227641, 0.11600239831777631,
      0.11782082533426363, 0.11954855000912301, 0.12118601520699647,
      0.12273368247737641, 0.12419203188939756, 0.12556156186384104,
      0.12684278900242402, 0.128036247914406, 0.12914249104056552,
      0.13016208847457925, 0.13109562778187842, 0.13194371381599251,
      0.13270696853245434, 0.133386030800303, 0.13398155621122376,
      0.13449421688639146, 0.13492470128104014, 0.13527371398682209,
      0.13554197553199621, 0.135730222179493, 0.13583920572290079,
      0.1358696932804293, 0.13582246708687679, 0.13569832428367126,
      0.13549807670701336, 0.13522255067417813, 0.13487258676801123,
      0.13444903961968008, 0.13395277768971298, 0.13338468304737783,
      0.13274565114844328, 0.13203659061137368, 0.13125842299199242,
      0.13041208255667774, 0.12949851605410839, 0.12851868248563247,
      0.12747355287428852, 0.12636411003252329, 0.1251913483286545,
      0.12395627345213212, 0.1226599021776176, 0.1213032621279551,
      0.11988739153605081, 0.11841333900572783, 0.1168821632715787,
      0.11529493295788022, 0.11365272633659397, 0.11195663108450241,
      0.11020774403953235, 0.10840717095629658, 0.10655602626089108,
      0.10465543280501088, 0.10270652161940577, 0.10071043166672242,
      0.0986683095937807, 0.096581309483316141, 0.0944505926052378,
      0.092277327167433421, 0.0900626880661685, 0.087807856636110931,
      0.085514020400037763, 0.083182372818236663, 0.080814113037667556,
      0.0784104456409098, 0.07597258039493178, 0.073501731999729064,
      0.0709991198368624, 0.068465967717936366, 0.065903503633054,
      0.063312959499289861, 0.060695570909210406, 0.058052576879482981,
      0.055385219599609389, 0.052694744180826814, 0.049982398405184425,
      0.047249432474879616, 0.04449709876183372, 0.0417266515575897,
      0.038939346823532631, 0.036136441941489246, 0.033319195464725747,
      0.030488866869391389, 0.027646716306422077, 0.024794004353964276,
      0.021931991770322089, 0.019061939247488148, 0.016185107165268046,
      0.013302755346045525, 0.010416142810218028, 0.0075265275323189648,
      0.004635166197884559, 0.0017433139610773668, -0.0011477757969024435,
      -0.0040368517085766012, -0.0069226646600947656, -0.00980396803026488,
      -0.01267951792865419, -0.015548073432766762, -0.018408396824232447,
      -0.02125925382400088, -0.024099413826507279, -0.0269276501327734,
      -0.0297427401824233, -0.03254346578458174, -0.035328613347635443,
      -0.038096974107813063, -0.040847344356571016, -0.043578525666755796,
      -0.046289325117503985, -0.048978555517874535, -0.0516450356291621,
      -0.054287590385882614, -0.056905051115401777, -0.059496255756173871,
      -0.062060049074569586, -0.0645952828802694, -0.067100816240189751,
      -0.069575515690930928, -0.0720182554496987, -0.07442791762370532,
      -0.0768033924179924, -0.079143578341678109, -0.081447382412587851,
      -0.083713720360256316, -0.085941516827261047, -0.088129705568886774,
      -0.090277229651068575, -0.092383041646621464, -0.094446103829704878,
      -0.096465388368517715, -0.098439877516194346, -0.10036856379987798,
      -0.10225045020794965, -0.10408455037539875, -0.10586988876728967,
      -0.10760550086033566, -0.10929043332252925, -0.11092374419082002,
      -0.1125045030468217, -0.11403179119051418, -0.11550470181193649,
      -0.11692234016082975, -0.1182838237142303, -0.11958828234197195,
      -0.12083485847009058, -0.12202270724210601, -0.12315099667815879,
      -0.12421890783198322, -0.12522563494570002, -0.12617038560239871,
      -0.12705238087650431, -0.12787085548189314, -0.12862505791775034,
      -0.12931425061214308, -0.12993771006329027, -0.13049472697851616,
      -0.13098460641085763, -0.13140666789331742, -0.13176024557073632,
      -0.13204468832927133, -0.13225935992345733, -0.132403639100836,
      -0.13247691972413306, -0.13247861089096719, -0.13240813705107154,
      -0.13226493812100748, -0.1320484695963586, -0.13175820266138477,
      -0.13139362429611567, -0.13095423738087353, -0.13043956079820268,
      -0.12984912953218986, -0.12918249476516042, -0.12843922397173446,
      -0.12761890101022308, -0.12672112621135209, -0.12574551646429522,
      -0.12469170530000206, -0.12355934297180338, -0.12234809653328313,
      -0.12105764991339509, -0.11968770398881258, -0.11823797665350039,
      -0.116708202885486, -0.11509813481081863, -0.11340754176471123,
      -0.11163621034983132, -0.10978394449174921, -0.10785056549151473,
      -0.10583591207535271, -0.10373984044146739, -0.10156222430394196,
      -0.099302954933715284, -0.096961941196628376, -0.094539109588531386,
      -0.092034404267428913, -0.089447787082661531, -0.086779237601107756,
      -0.084028753130397871, -0.081196348739122917, -0.078282057274037767,
      -0.07528592937423452, -0.07220803348229278, -0.069048455852382631,
      -0.06580730055531829, -0.062484689480550831, -0.059080762335093365,
      -0.055595676639368166, -0.05202960771996365, -0.048382748699302786,
      -0.044655310482210359, -0.040847521739369508, -0.036959628887659635,
      -0.032991896067382662, -0.028944605116347652, -0.024818055540834036,
      -0.020612564483409715, -0.016328466687604362, -0.011966114459435476,
      -0.0075258776257827176, -0.0030081434896029463, 0.0015866832180111839,
      0.0062581803889409648, 0.011005908592316913, 0.01582941113195116,
      0.02072821410695741, 0.025701826475527642, 0.03074974012188772,
      0.035871429926416856, 0.04106635383895392, 0.046333952955260556,
      0.051673651596663511, 0.057084857392855945, 0.062566961367884838,
      0.068119338029279053, 0.073741345460359126, 0.079432325415686317,
      0.085191603419685874, 0.091018488868403885, 0.096912275134413861,
      0.10287223967486228, 0.10889764414264311, 0.11498773450070887,
      0.12114174113948423, 0.12735887899740292, 0.13363834768454363,
      0.13997933160935375, 0.14638100010846811, 0.15284250757959059,
      0.15936299361744191, 0.1659415831527695, 0.17257738659437794,
      0.17926949997420566, 0.18601700509540603, 0.19281896968342926,
      0.19967444754009614, 0.20658247870063759, 0.2135420895936927,
      0.22055229320424502, 0.22761208923948878, 0.23472046429758919,
      0.24187639203933586, 0.24907883336266859, 0.25632673658004446,
      0.26361903759863542, 0.27095466010334524, 0.27833251574259188,
      0.28575150431688129, 0.29321051397009734, 0.3007084213835291,
      0.30824409197258251, 0.31581638008616991, 0.32342412920873009,
      0.33106617216488854, 0.33874133132668249, 0.34644841882337696,
      0.3541862367537949, 0.36195357740116585, 0.36974922345045125,
      0.37757194820810647, 0.38542051582427628, 0.39329368151736527,
      0.40119019180095195, 0.40910878471304418, 0.41704819004759747,
      0.42500712958830011, 0.43298431734456877, 0.44097845978971895,
      0.44898825610129378, 0.45701239840348362, 0.46504957201162989,
      0.47309845567874326, 0.48115772184402827, 0.4892260368833537,
      0.4973020613616273, 0.50538445028705548, 0.5134718533672169,
      0.52156291526692833, 0.52965627586785347, 0.53775057052980457,
      0.54584443035371077, 0.55393648244617844, 0.56202535018562749,
      0.57010965348994269, 0.5781880090855912, 0.58625903077816044,
      0.5943213297242822, 0.60237351470485934, 0.61041419239959849,
      0.61844196766273674, 0.62645544379996942, 0.63445322284648109,
      0.64243390584606341, 0.65039609313124191, 0.65833838460437721,
      0.666259380019669, 0.6741576792660301, 0.68203188265075387,
      0.68988059118394141, 0.69770240686361429, 0.70549593296145985,
      0.71325977430917287, 0.72099253758530579, 0.72869283160258935,
      0.73635926759565828, 0.743990459509135, 0.75158502428599161,
      0.75914158215614858, 0.766658756925242, 0.774135176263501,
      0.78156947199467208, 0.788960280384944, 0.79630624243177861,
      0.80360600415262917, 0.81085821687344528, 0.81806153751692545,
      0.82521462889044728, 0.83231615997360819, 0.83936480620532461,
      0.84635924977040755, 0.85329817988557632, 0.86018029308481669,
      0.86700429350404118, 0.87376889316498263, 0.8804728122582488,
      0.88711477942546946, 0.89369353204049673, 0.9002078164895595,
      0.90665638845032392, 0.91303801316980038, 0.91935146574101911,
      0.92559553137840178, 0.93176900569179366, 0.93787069495905206,
      0.94389941639715536, 0.94985399843175133, 0.95573328096507892,
      0.961536115642198, 0.96726136611547819, 0.97290790830724994,
      0.97847463067057461, 0.98396043444806025, 0.98936423392866,
      0.99468495670238422, 0.99992154391286225, 1.0050729505076905,
      1.0101381454864893, 1.0151161121466388, 1.0200058483265741,
      1.0248063666466296, 1.0295166947473215, 1.0341358755250545,
      1.0386629673651395, 1.0430970443720877, 1.04743719659711,
      1.0516825302627668, 1.0558321679846898, 1.059885248990329,
      1.0638409293346609, 1.067698382112775, 1.0714567976693257,
      1.0751153838047354, 1.0786733659781205, 1.0821299875068826,
      1.0854845097628878, 1.0887362123651865, 1.0918843933692184,
      1.0949283694524443, 1.0978674760963427, 1.1007010677647153,
      1.1034285180782633, 1.106049219985356, 1.1085625859289436,
      1.1109680480095818, 1.1132650581444878, 1.1154530882225879,
      1.1175316302555183, 1.1195001965244984, 1.1213583197230514,
      1.1231055530955338, 1.1247414705713819, 1.1262656668950717,
      1.1276777577517374, 1.1289773798883742, 1.1301641912306266,
      1.1312378709950754, 1.1321981197970175, 1.1330446597536652,
      1.1337772345827568, 1.1343956096965016, 1.1348995722908581,
      1.1352889314300749, 1.135563518126492, 1.1357231854155345,
      1.1357678084258749, 1.1356972844447475, 1.1355115329783596,
      1.135210495807381, 1.1347941370374728, 1.1342624431448489,
      1.1336154230167954, 1.1328531079871871, 1.1319755518669155,
      1.1309828309692369, 1.1298750441300123, 1.1286523127228143,
      1.1273147806688713, 1.1258626144418562, 1.1242960030674665,
      1.1226151581178123, 1.1208203137005734, 1.1189117264429189,
      1.1168896754701858, 1.1147544623792811, 1.1125064112068301,
      1.1101458683920262, 1.1076732027342109, 1.1050888053451413,
      1.1023930895959713, 1.0995864910589201, 1.0966694674436501,
      1.0936424985283235, 1.0905060860853619, 1.0872607538018972,
      1.0839070471949339, 1.0804455335212018, 1.0768768016817316,
      1.0732014621211461, 1.0694201467216715, 1.0655335086919082,
      1.0615422224503228, 1.0574469835035247, 1.0532485083193215,
      1.0489475341945562, 1.0445448191177737, 1.0400411416266959,
      1.0354373006605762, 1.030734115407405, 1.0259324251460329,
      1.0210330890831989, 1.016036986185515, 1.0109450150064339,
      1.0057580935082087, 1.0004771588789012, 0.99510316734445969,
      0.98963709397588107, 0.9840799324915338, 0.97843269505464492,
      0.97269641206598934, 0.9668721319518454, 0.96096092094723373,
      0.954963862874486, 0.9488820589172009, 0.94271662738961493,
      0.93646870350143518, 0.93013943911821251, 0.9237300025172509,
      0.91724157813913743, 0.91067536633495982, 0.904032583109221,
      0.89731445985853719, 0.89052224310617123, 0.88365719423244193,
      0.87672058920108487, 0.869713718281625, 0.86263788576780309,
      0.85549440969213508, 0.84828462153667583, 0.84100986594002014,
      0.83367150040063653, 0.82627089497659845, 0.81880943198175282,
      0.8112885056784418, 0.80370952196680545, 0.79607389807075957,
      0.78838306222072152, 0.78063845333314674, 0.77284152068697065,
      0.76499372359700646, 0.75709653108439434, 0.74915142154418024,
      0.741159882410102, 0.73312340981664714, 0.72504350825849184,
      0.7169216902473875, 0.70875947596657285, 0.70055839292281308,
      0.69231997559613512, 0.68404576508735415, 0.67573730876348315,
      0.66739615990109147, 0.65902387732773138, 0.65062202506150268,
      0.64219217194884159, 0.63373589130065011, 0.62525476052682294,
      0.61675036076930034, 0.60822427653371436, 0.59967809531972183,
      0.591113407250143, 0.58253180469898269, 0.57393488191841724,
      0.56532423466488368, 0.5567014598243174, 0.54806815503667949,
      0.53942591831984343, 0.53077634769296134, 0.522121040799376,
      0.51346159452921614, 0.50479960464174767, 0.49613666538759393,
      0.48747436913091513, 0.47881430597165653, 0.47015806336796406,
      0.46150722575885861, 0.45286337418728467, 0.44422808592362328,
      0.4356029340897774, 0.42698948728393205, 0.41838930920607709,
      0.40980395828441429, 0.40123498730273782, 0.39268394302889453,
      0.38415236584441259, 0.37564178937542686, 0.36715374012497859,
      0.35868973710679763, 0.35025129148067186, 0.34183990618950588,
      0.33345707559815352, 0.32510428513415324, 0.31678301093044448,
      0.30849471947016288, 0.30024086723363325, 0.29202290034764272,
      0.28384225423710518, 0.27570035327919046, 0.26759861046006328,
      0.25953842703427477, 0.25152119218693081, 0.24354828269875725,
      0.2356210626141016, 0.22774088291200706, 0.21990908118045174,
      0.21212698129383079, 0.20439589309378617, 0.19671711207345338,
      0.18909191906527384, 0.18152157993239096, 0.17400734526375966,
      0.16655045007307173, 0.15915211350155756, 0.15181353852474788,
      0.1445359116633104, 0.13732040269802206, 0.13016816438898843,
      0.12308033219915149, 0.11605802402219817, 0.10910233991496696,
      0.10221436183438509, 0.0953951533790458, 0.088645759535516122,
      0.081967206429417683, 0.075360501081385256, 0.068826631167949737,
      0.062366564787452047, 0.055981250231035951, 0.049671615758790186,
      0.043438569381115573, 0.037282998645405074, 0.031205770428054391,
      0.02520773073190205, 0.019289704489181846, 0.013452495369991768,
      0.0076968855963862187, 0.0020236357621458909, -0.0035665153417383869,
      -0.0090728508957924475, -0.014494676214957446, -0.019831318905584226,
      -0.025082129016490824, -0.030246479184038777, -0.035323764771166638,
      -0.040313404000319783, -0.045214838080277708, -0.050027531326786362,
      -0.054750971276996852, -0.059384668797620985, -0.063928158186815923,
      -0.068380997269751567, -0.072742767487775417, -0.077013073981218,
      -0.08119154566576918, -0.085277835302376329, -0.089271619560687243,
      -0.09317259907596602, -0.096980498499493792, -0.10069506654240792,
      -0.10431607601297407, -0.10784332384726238, -0.11127663113323445,
      -0.11461584312818102, -0.11786082926956262, -0.12101148317918885,
      -0.12406772266074816, -0.12702948969068775, -0.12989675040243306,
      -0.13266949506393866, -0.13534773804857791, -0.13793151779938018,
      -0.14042089678659542, -0.14281596145861344, -0.14511682218624222,
      -0.14732361320033874, -0.14943649252282176, -0.1514556418910854,
      -0.15338126667578608, -0.15521359579208305, -0.15695288160430326,
      -0.15859939982406482, -0.160153449401894, -0.16161535241235642,
      -0.16298545393270469, -0.16426412191511516, -0.16545174705251481,
      -0.16654874263802447, -0.16755554441808873, -0.16847261043929818,
      -0.16930042088893688, -0.170039477929354, -0.1706903055260991,
      -0.17125344926998018, -0.1717294761930096, -0.172118974578311,
      -0.17242255376405546, -0.17264084394144497, -0.17277449594683042,
      -0.17282418104799527, -0.17279059072466782, -0.17267443644334388,
      -0.17247644942643275, -0.17219738041584259, -0.17183799943104563,
      -0.17139909552165955, -0.17088147651469343, -0.17028596875643109,
      -0.16961341684909692, -0.16886468338234356, -0.16804064865964521,
      -0.16714221041966326, -0.16617028355268765, -0.16512579981219747,
      -0.16400970752165026, -0.16282297127658729, -0.16156657164208324,
      -0.1602415048457228, -0.15884878246610315, -0.15738943111698295,
      -0.15586449212719511, -0.15427502121636469, -0.15262208816656847,
      -0.15090677648999512, -0.14913018309274481, -0.14729341793481077,
      -0.14539760368638216, -0.14344387538057102, -0.14143338006262146,
      -0.1393672764357376, -0.13724673450365402, -0.13507293520997926,
      -0.13284707007449661, -0.13057034082648505, -0.12824395903517677,
      -0.12586914573746277, -0.12344713106295579, -0.12097915385651667,
      -0.11846646129836091, -0.11591030852186157, -0.11331195822912805,
      -0.11067268030454337, -0.10799375142630288, -0.10527645467610329,
      -0.10252207914711073, -0.099731919550286888, -0.0969072758192284,
      -0.094049452713613438, -0.091159759421391443, -0.088239509159813684,
      -0.085290018775442733, -0.082312608343258972, -0.079308600764968151,
      -0.076279321366656411, -0.0732260974959044, -0.070150258118442471,
      -0.067053133414566632, -0.0639360543753194, -0.060800352398635085,
      -0.057647358885564486, -0.054478404836675556, -0.051294820448753123,
      -0.048097934711955122, -0.044889075007517432, -0.041669566706133684,
      -0.038440732767142057, -0.035203893338637181, -0.031960365358628104,
      -0.028711462157376008, -0.025458493060992834, -0.0222027629964983,
      -0.018945572098384822, -0.015688215316833426, -0.012431982027724178,
      -0.0091781556445468815, -0.0059280132323083073, -0.0026828251235868489,
      0.00055614546313481616, 0.0037876428027993347, 0.0070104190405918948,
      0.010223234566137843, 0.013424858384994964, 0.0166140684872932,
      0.01978965221340942, 0.022950406616588079, 0.026095138822361169,
      0.029222666384677756, 0.032331817638623341, 0.035421432049617972,
      0.038490360558974548, 0.041537465925743575, 0.044561623064681935,
      0.047561719380285965, 0.050536655096759031, 0.053485343583816243,
      0.056406711678222032, 0.059299700000957113, 0.062163263269922234,
      0.06499637060805985, 0.0677980058468181, 0.070567167824847565,
      0.073302870681832472, 0.076004144147377356, 0.0786700338248366,
      0.081299601470008059, 0.083891925264608785, 0.0864461000844082,
      0.0889612377619905, 0.091436467344011174, 0.093870935342877215,
      0.096263805982782141, 0.09861426144001384, 0.10092150207743548,
      0.10318474667308838, 0.10540323264282644, 0.1075762162569175,
      0.10970297285053651, 0.11178279702807206, 0.11381500286120409,
      0.11579892408066066, 0.11773391426159495, 0.11961934700254068,
      0.12145461609785721, 0.12323913570363004, 0.12497234049694973,
      0.1266536858285385, 0.12828264786865723, 0.12985872374623275,
      0.13138143168119304, 0.13285031110993228, 0.13426492280385996,
      0.13562484898103025, 0.13692969341076697, 0.13817908151127389,
      0.13937266044019339, 0.14051009917806784, 0.14159108860468075,
      0.14261534156826403, 0.14358259294750891, 0.14449259970639144,
      0.14534514094178264, 0.14614001792380293, 0.14687705412893351,
      0.147556095265851, 0.14817700929397526, 0.14873968643472582,
      0.14924403917547358, 0.1496900022661885, 0.15007753270876159,
      0.15040660973903322, 0.15067723480149475, 0.15088943151668416,
      0.15104324564128291, 0.15113874502091729, 0.15117601953566717,
      0.15115518103831901, 0.15107636328534349, 0.15093972186065061,
      0.15074543409211577, 0.15049369896091122, 0.15018473700366092,
      0.14981879020745992, 0.14939612189775789, 0.14891701661917708,
      0.14838178000925945, 0.1477907386652057, 0.14714424000363663,
      0.14644265211341059, 0.14568636360154583, 0.14487578343229388,
      0.14401134075940691, 0.14309348475164874, 0.14212268441160408,
      0.14109942838783499, 0.14002422478044721, 0.13889760094011411,
      0.13772010326063158, 0.13649229696504778, 0.13521476588545633,
      0.13388811223649869, 0.13251295638264743, 0.13108993659935581,
      0.12961970882813026, 0.12810294642559816, 0.12654033990667302,
      0.12493259668185938, 0.1232804407888054, 0.1215846126181778,
      0.11984586863393715, 0.11806498108810815, 0.11624273773012754,
      0.11437994151086189, 0.11247741028139364, 0.11053597648664787,
      0.10855648685397797, 0.10653980207680629, 0.10448679649339364,
      0.10239835776086133, 0.10027538652457323, 0.098118796082948739,
      0.095929512047851231, 0.0937084720006218, 0.091456625143903222,
      0.08917493194933504, 0.086864363801233357, 0.084525902636396436,
      0.082160540580108368, 0.079769279578484967, 0.077353131027275479,
      0.074913115397219732, 0.072450261856107, 0.069965607887625916,
      0.067460198907161012, 0.064935087874623626, 0.062391334904473406,
      0.059830006873026559, 0.05725217702319009, 0.054658924566766812,
      0.052051334284404546, 0.049430496123386972, 0.046797504793345136,
      0.044153459360034314, 0.041499462837320991, 0.038836621777475974,
      0.036166045859965093, 0.033488847478802174, 0.030806141328636003,
      0.028119043989725402, 0.02542867351187364, 0.022736148997524755,
      0.02004259018410761, 0.017349117025798361, 0.014656849274818362,
      0.011966906062394408, 0.0092804054795599666, 0.0065984641578826081,
      0.00392219685028905, 0.0012527160121135056, -0.0014088686174883042,
      -0.0040614504336254353, -0.0067039263831314561, -0.009335197381229815,
      -0.011954168727300055, -0.014559750519596307, -0.017150858068764208,
      -0.019726412310048555, -0.022285340214033222, -0.0248265751957939,
      -0.027349057522291706, -0.0298517347179372, -0.032333561968117958,
      -0.034793502520600386, -0.037230528084667092, -0.039643619227829545,
      -0.042031765770019505, -0.044393967175105215, -0.046729232939584336,
      -0.049036582978377846, -0.05131504800753442, -0.053563669923746192,
      -0.0557815021805474, -0.057967610161064782, -0.060121071547188293,
      -0.06224097668503302, -0.0643264289465924, -0.066376545087427671,
      -0.068390455600295275, -0.070367305064569757, -0.072306252491362119,
      -0.074206471664210072, -0.07606715147520493, -0.077887496256464933,
      -0.079666726106820351, -0.081404077213620973, -0.083098802169508768,
      -0.084750170284097787, -0.086357467890429959, -0.087919998646070446,
      -0.089437083828798072, -0.090908062626736535, -0.092332292422826229,
      -0.093709149073579287, -0.095038027181960028, -0.09631834036433938,
      -0.0975495215114022, -0.098731023042918184, -0.099862317156296676,
      -0.10094289606881672, -0.10197227225345343, -0.10294997866821708,
      -0.10387556897892072, -0.10474861777527836, -0.1055687207802718,
      -0.10633549505270996, -0.10704857918287521, -0.10770763348122331,
      -0.10831234016003301, -0.10886240350794948, -0.1093575500573508,
      -0.10979752874447615, -0.11018211106224773, -0.11051109120571638,
      -0.11078428621010367, -0.1110015360813488, -0.11116270391910921,
      -0.11126767603220879, -0.11131636204640707, -0.11130869500452215,
      -0.11124463145880276, -0.11112415155553981, -0.11094725911186229,
      -0.11071398168469333, -0.11042437063181661, -0.11007850116503637,
      -0.10967647239538238, -0.10921840737035368, -0.10870445310315857,
      -0.10813478059393916, -0.10750958484295092, -0.10682908485570014,
      -0.10609352363998802, -0.10530316819489538, -0.10445830949165352,
      -0.10355926244643152, -0.10260636588500646, -0.10159998249933502,
      -0.10054049879601873, -0.099428325036657522, -0.098263895170117882,
      -0.09704766675671124, -0.095780120884278216, -0.094461762076236938,
      -0.093093118191564378, -0.0916747403167418, -0.090207202649719417,
      -0.0886911023758735, -0.0871270595360097, -0.085515716886450308,
      -0.08385773975121108, -0.082153815866323088, -0.080404655216324283,
      -0.078610989862965081, -0.076773573766175052, -0.0748931825973211,
      -0.072970613544806634, -0.071006685112088144, -0.069002236908112524,
      -0.066958129430270491, -0.064875243839903535, -0.06275448173043055,
      -0.06059676488815087, -0.058403035045782037, -0.056174253628824333,
      -0.053911401494785363, -0.051615478665356262, -0.049287504051617859,
      -0.046928515172334734, -0.044539567865428467, -0.042121735992704593,
      -0.039676111137919537, -0.037203802298264269, -0.034705935569366075,
      -0.032183653823875405, -0.029638116383757775, -0.027070498686357886,
      -0.024481991944335771, -0.021873802799594763, -0.019247152971274564,
      -0.0166032788979133, -0.013943431373902387, -0.011268875180319091,
      -0.00858088871025181, -0.0058807635887241916, -0.0031698042873371662,
      -0.00044932773372877155, 0.0022793370840194921, 0.0050148495179278829,
      0.00775585766548563, 0.01050099877972259, 0.013248899683875215,
      0.015998177190507376, 0.018747438524966339, 0.021495281753060452,
      0.024240296212816717, 0.026981062950190621, 0.029716155158602597,
      0.0324441386221776, 0.035163572162529633, 0.037873008088978491,
      0.040570992652066304, 0.043256066500211215, 0.045926765139396281,
      0.048581619395707917, 0.051219155880644004, 0.053837897458994435,
      0.056436363719175153, 0.059013071445888562, 0.061566535094928168,
      0.064095267270030329, 0.066597779201574114, 0.069072581227023866,
      0.0715181832729652, 0.073933095338543017, 0.076315827980217882,
      0.078664892797643993, 0.0809788029205221, 0.083256073496316363,
      0.085495222178628191, 0.087694769616131971, 0.089853239941865073,
      0.091969161262776267, 0.094041066149342684, 0.096067492125103765,
      0.098046982155994528, 0.099978085139277709, 0.10185935639196557,
      0.10368935813855118, 0.10546665999789273, 0.10718983946914445,
      0.10885748241650861, 0.11046818355272883, 0.11202054692111496,
      0.11351318637599744, 0.11494472606141554, 0.11631380088791167,
      0.11761905700729086, 0.11885915228517101, 0.12003275677118251,
      0.12113855316669274, 0.12217523728984811, 0.12314151853787089,
      0.12403612034636856, 0.12485778064559735, 0.12560525231346792,
      0.12627730362518133, 0.12687271869935784, 0.12739029794047288,
      0.127828858477527, 0.12818723459873677, 0.12846427818214548,
      0.12865885912203484, 0.128769865750929, 0.12879620525714927,
      0.12873680409768756, 0.12859060840634892, 0.1283565843969747,
      0.12803371876162778, 0.12762101906363937, 0.12711751412533162,
      0.12652225441036313, 0.12583431240048745, 0.1250527829666864,
      0.12417678373448471, 0.12320545544336287, 0.12213796230015457,
      0.1209734923262788, 0.11971125769871997, 0.11835049508464472,
      0.116890465969501, 0.11533045697856331, 0.11366978019172666,
      0.11190777345153713, 0.11004380066426933, 0.10807725209400021,
      0.10600754464959251, 0.10383412216440355, 0.10155645566875242,
      0.099174043654930738, 0.096686412334745883, 0.094093115889468185,
      0.09139373671210739, 0.088587885641941269, 0.085675202191177843,
      0.082655354763740252, 0.079528040866020874, 0.076292987309564853,
      0.072949950405628544, 0.069498716151492862, 0.0659391004085236,
      0.062270949071845355, 0.058494138231623354, 0.054608574325877575,
      0.05061419428473219, 0.046510965666110952, 0.042298886782757339,
      0.037977986820598324, 0.033548325948334311, 0.029009995418236262,
      0.024363117658184087, 0.019607846354730236, 0.014744366527334546,
      0.00977289459363457, 0.0046936784257328029, -0.00049300260250307454,
      -0.0057868375771961619, -0.011187484015226325, -0.01669456784411933,
      -0.022307683390998985, -0.028026393380649182, -0.033850228942729779,
      -0.039778689628072961, -0.04581124343416975, -0.051947326839775022,
      -0.058186344848651886, -0.06452767104250802, -0.070970647643004064,
      -0.077514585582963771, -0.084158764586662257, -0.0909024332592745,
      -0.0977448091853864, -0.10468507903660912, -0.11172239868825538,
      -0.11885589334504625, -0.12608465767585209, -0.13340775595738724,
      -0.14082422222690416, -0.14833306044377348, -0.15593324465996761,
      -0.16362371919937047, -0.17140339884593195, -0.17927116904051965,
      -0.1872258860865518, -0.19526637736423991, -0.20339144155346223,
      -0.21159984886519687, -0.219890341281436, -0.22826163280355033,
      -0.23671240970901411, -0.24524133081645583, -0.25384702775893264,
      -0.26252810526537884, -0.271283141450155, -0.28011068811060047,
      -0.2890092710325799, -0.29797739030379633, -0.30701352063500503,
      -0.31611611168880371, -0.32528358841612359, -0.3345143514001821,
      -0.34380677720786579, -0.35315921874849027, -0.36257000563971026,
      -0.3720374445806498, -0.3815598197320107, -0.3911353931031325,
      -0.40076240494587734, -0.41043907415521075, -0.42016359867644509,
      -0.42993415591890072, -0.43974890317602566, -0.44960597805172708,
      -0.45950349889289338, -0.46943956522791491, -0.47941225821112837,
      -0.48941964107305891, -0.49945975957631394, -0.50953064247698943,
      -0.51963030199152871, -0.5297567342688293, -0.53990791986749542,
      -0.550081824238122, -0.56027639821042419, -0.57048957848516724,
      -0.58071928813061668, -0.59096343708353949, -0.60121992265448032,
      -0.61148663003722092, -0.62176143282232788, -0.63204219351451452,
      -0.64232676405385969, -0.652612986340519, -0.662898692762986,
      -0.67318170672961963, -0.68345984320330855, -0.69373090923922,
      -0.70399270452529683, -0.71424302192557532, -0.72447964802594733,
      -0.73470036368238845, -0.744902944571421, -0.755085161742628,
      -0.76524478217312086, -0.77537956932377883, -0.78548728369711474,
      -0.7955656833965693, -0.80561252468713873, -0.81562556255711349,
      -0.82560255128082349, -0.83554124498219406, -0.84543939819895308,
      -0.85529476644738189, -0.865105106787355, -0.87486817838760911,
      -0.88458174309100424, -0.89424356597967369, -0.90385141593984342,
      -0.91340306622623213, -0.92289629502581316, -0.93232888602079345,
      -0.94169862895067835, -0.951003320173212, -0.960240763224102,
      -0.96940876937528175, -0.97850515819165, -0.9875277580860583,
      -0.99647440687240663, -1.0053429523167146, -1.0141312526859787,
      -1.0228371772947016, -1.0314586070488694, -1.0399934349873308,
      -1.0484395668202877, -1.0567949214648953, -1.0650574315776833,
      -1.0732250440837428, -1.0812957207024998, -1.0892674384698895,
      -1.0971381902568702, -1.1049059852840246, -1.1125688496322104,
      -1.1201248267490194, -1.1275719779509745, -1.134908382921304,
      -1.1421321402031122, -1.1492413676878859, -1.1562342030991166,
      -1.1631088044709819, -1.1698633506218756, -1.1764960416227153,
      -1.1830050992598775, -1.1893887674926136, -1.1956453129048272,
      -1.2017730251511138, -1.2077702173969138, -1.2136352267526356,
      -1.2193664147016938, -1.2249621675222606, -1.2304208967027064,
      -1.2357410393505137, -1.2409210585946369, -1.2459594439811661,
      -1.2508547118621554, -1.2556054057775712, -1.260210096830195,
      -1.2646673840534277, -1.2689758947718541, -1.2731342849545029,
      -1.2771412395606916, -1.2809954728783421, -1.2846957288547338,
      -1.2882407814195296, -1.2916294348000508, -1.2948605238286848,
      -1.29793291424235, -1.30084550297394, -1.3035972184356719,
      -1.3061870207942459, -1.3086139022377838, -1.3108768872344343,
      -1.3129750327825944, -1.3149074286526903, -1.3166731976204427,
      -1.3182714956915678, -1.3197015123178366, -1.3209624706044738,
      -1.3220536275087973, -1.3229742740300963, -1.3237237353906706,
      -1.324301371207981, -1.3247065756579139, -1.3249387776290626,
      -1.3249974408680267, -1.3248820641156995, -1.324592181234479,
      -1.3241273613264095, -1.3234872088422063, -1.3226713636811611,
      -1.3216795012818741, -1.3205113327038376, -1.3191666046998318,
      -1.3176450997791058, -1.3159466362613863, -1.314071068321653,
      -1.3120182860256964, -1.3097882153564835, -1.3073808182312792,
      -1.3047960925095821, -1.3020340719918477, -1.2990948264090179,
      -1.2959784614028746, -1.2926851184972261, -1.2892149750599515,
      -1.2855682442559109, -1.2817451749907605, -1.2777460518456776,
      -1.2735711950030633, -1.2692209601632063, -1.2646957384519601,
      -1.2599959563194927, -1.2551220754301171, -1.250074592543253,
      -1.244854039385574, -1.2394609825143754, -1.2338960231722236,
      -1.2281597971329123, -1.2222529745388202, -1.2161762597297014,
      -1.2099303910629622, -1.2035161407254944, -1.1969343145371636,
      -1.1901857517459224, -1.1832713248147604, -1.1761919392003994,
      -1.16894853312397, -1.1615420773336034, -1.1539735748591047,
      -1.1462440607587809, -1.1383546018584387, -1.1303062964827382,
      -1.1221002741788921, -1.1137376954328873, -1.1052197513782327,
      -1.0965476634973919, -1.0877226833159976, -1.0787460920898444,
      -1.0696192004849527, -1.0603433482505651, -1.0509199038853947,
      -1.0413502642970929, -1.0316358544550761, -1.0217781270368709,
      -1.0117785620680124, -1.0016386665556694, -0.99135997411604537,
      -0.98094404459575435, -0.970392463687209, -0.9597068425381845,
      -0.9488888173556651, -0.93794004900409989, -0.92686222259819073,
      -0.91565704709029849, -0.90432625485268481, -0.89287160125460252,
      -0.88129486423446757, -0.86959784386714345, -0.85778236192657931,
      -0.84585026144381281, -0.8338034062605667, -0.82164368057853121,
      -0.80937298850447048, -0.79699325359129869, -0.78450641837523227,
      -0.77191444390922859, -0.75921930929275117, -0.7464230111980662,
      -0.73352756339322189, -0.72053499626178741, -0.70744735631957256,
      -0.6942667057283638, -0.6809951218069803, -0.66763469653958163,
      -0.65418753608161528, -0.64065576026329951, -0.627041502090993,
      -0.613346907246485, -0.59957413358432765, -0.58572535062751407,
      -0.57180273906141965, -0.55780849022636114, -0.54374480560877636,
      -0.52961389633126377, -0.51541798264156669, -0.50115929340065779,
      -0.48684006557014381, -0.47246254369898838, -0.45802897940987353,
      -0.44354163088518994, -0.4290027623529154, -0.41441464357247237,
      -0.39977954932069132, -0.38509975887806908, -0.37037755551549212,
      -0.3556152259814459, -0.34081505998997369, -0.32597934970950382,
      -0.31111038925262563, -0.29621047416704754, -0.28128190092776273,
      -0.26632696643072046, -0.25134796748795418, -0.23634720032446013,
      -0.22132696007691058, -0.20628954029425242, -0.19123723244053789,
      -0.17617232539983591, -0.16109710498365534, -0.14601385344076356,
      -0.1309248489696748, -0.11583236523392525, -0.10073867088017027,
      -0.0856460290593926, -0.070556696951141529, -0.0554729252911643,
      -0.040396957902326378, -0.025331031229094941, -0.010277373875660488,
      0.0047617938522000122, 0.019784260401369057, 0.034787823421689609,
      0.049770290212089868, 0.0647294781625681, 0.0796632151917714,
      0.094569340180206657, 0.10944570339884885, 0.12429016693311086,
      0.13910060510208885, 0.15387490487288036, 0.16861096626999711,
      0.183306702779673, 0.19796004174905024, 0.21256892478005732,
      0.22713130811799248, 0.2416451630346394, 0.25610847620582622,
      0.27051925008342637, 0.28487550326157696, 0.29917527083718531,
      0.31341660476449462, 0.32759757420375291, 0.3417162658638242,
      0.35577078433870923, 0.36975925243786822, 0.38367981151031483,
      0.39753062176241749, 0.41130986256923519, 0.42501573277951449,
      0.43864645101406757, 0.4522002559576781, 0.46567540664429746,
      0.47907018273559959, 0.49238288479282083, 0.5056118345417292,
      0.51875537513086156, 0.531811871382788, 0.54477971003851677,
      0.55765729999488678, 0.57044307253496029, 0.583135481551413,
      0.59573300376276328, 0.60823413892258693, 0.6206374100215013,
      0.63294136348205376, 0.64514456934636444, 0.65724562145657872,
      0.66924313762809, 0.68113575981548635, 0.6929221542712346,
      0.704601011697088, 0.71617104738821524, 0.72763100136997416,
      0.73897963852744875, 0.75021574872760832, 0.76133814693421542,
      0.7723456733153572, 0.78323719334372621, 0.79401159788957076,
      0.80466780330633969, 0.81520475150908422, 0.82562141004552725,
      0.83591677215995, 0.846089856849771, 0.85613970891494917,
      0.86606539900018153, 0.87586602362990429, 0.8855407052361991,
      0.89508859217950476, 0.90450885876233245, 0.91380070523583956,
      0.92296335779944583, 0.93199606859344919, 0.94089811568469472,
      0.94966880304533652, 0.95830746052476479, 0.96681344381471468,
      0.97518613440759649, 0.983424939548132, 0.99152929217832575,
      0.999498650875832, 1.0073324997857538, 1.0150303485459666,
      1.0225917322060205, 1.0300162111396287, 1.0373033709509007,
      1.0444528223742864, 1.0514642011683821, 1.0583371680036033,
      1.0650714083438368, 1.0716666323221351, 1.0781225746105014,
      1.08443899428388, 1.090615674678411, 1.0966524232440189,
      1.1025490713914263, 1.108305474333692, 1.1139215109223226,
      1.1193970834780529, 1.1247321176164267, 1.1299265620681687,
      1.1349803884945657, 1.1398935912978105, 1.144666187426532,
      1.1492982161764831, 1.1537897389865903, 1.1581408392303754,
      1.162351622002894, 1.1664222139032816, 1.1703527628129824,
      1.1741434376698092, 1.1777944282378658, 1.1813059448735159,
      1.1846782182874218, 1.1879114993028221, 1.191006058610121,
      1.1939621865178778, 1.1967801927003636, 1.1994604059417135,
      1.2020031738768571, 1.2044088627292759, 1.2066778570457377,
      1.2088105594280849, 1.2108073902622454, 1.2126687874444639,
      1.2143952061050145, 1.2159871183293791, 1.2174450128770591,
      1.2187693948981502, 1.2199607856477346, 1.2210197221982741,
      1.2219467571500453, 1.2227424583398032, 1.2234074085477054,
      1.2239422052027029, 1.224347460086423, 1.2246237990357125,
      1.2247718616439442, 1.2247923009611821, 1.2246857831933542,
      1.2244529874004837, 1.2240946051941797, 1.2236113404344098,
      1.2230039089257374, 1.2222730381130911, 1.221419466777196,
      1.2204439447297804, 1.2193472325086694, 1.2181301010728505,
      1.216793331497668, 1.2153377146702153, 1.2137640509850238,
      1.2120731500402477, 1.2102658303343008, 1.2083429189631947,
      1.2063052513186083, 1.2041536707868026, 1.2018890284485022,
      1.1995121827798381, 1.1970239993544622, 1.1944253505468931,
      1.1917171152372932, 1.18890017851763, 1.1859754313994901,
      1.1829437705234782, 1.1798060978704339, 1.176563320474465,
      1.173216350137952, 1.1697661031486013, 1.1662134999985894,
      1.1625594651060023, 1.1588049265385227, 1.1549508157395614,
      1.1509980672568636, 1.1469476184736938, 1.1428004093426745,
      1.1385573821223731, 1.1342194811167197, 1.1297876524172867,
      1.1252628436486234, 1.1206460037165527, 1.1159380825597029,
      1.1111400309041537, 1.1062528000214209, 1.1012773414897594,
      1.0962146069588998, 1.0910655479182525, 1.0858311154686728,
      1.0805122600978465, 1.075109931459316, 1.0696250781552845,
      1.064058647523181, 1.0584115854260938, 1.0526848360470982,
      1.0468793416875479, 1.0409960425693652, 1.0350358766414147,
      1.0289997793899412, 1.022888683653195, 1.0167035194402376,
      1.0104452137539843, 1.0041146904185245, 0.99771286991075825,
      0.99124066919637865, 0.98469900157024515, 0.978088776501168,
      0.97141089948115678, 0.96466627187910947, 0.9578557907990396,
      0.95098034894281358, 0.9440408344774377, 0.93703813090691479,
      0.92997311694869267, 0.922846666414706, 0.9156596480970649,
      0.9084129256583261, 0.9011073575264531, 0.893743796794406,
      0.88632309112438434, 0.87884608265674513, 0.87131360792356849,
      0.86372649776691868, 0.85608557726170353, 0.84839166564329749,
      0.84064557623969571, 0.83284811640844192, 0.82500008747808717,
      0.81710228469434543, 0.80915549717083257, 0.80116050784441839,
      0.793118093435152, 0.7850290244107585, 0.77689406495568969,
      0.76871397294464228, 0.76048949992067361, 0.75222139107767749,
      0.74391038524738273, 0.73555721489071879, 0.72716260609359229,
      0.71872727856699292, 0.71025194565141114, 0.70173731432556652,
      0.69318408521928765, 0.68459295263071729, 0.67596460454754514,
      0.66729972267243232, 0.65859898245247661, 0.64986305311268455,
      0.64109259769344, 0.63228827309186009, 0.623450730107066,
      0.61458061348919013, 0.60567856199224923, 0.596745208430624,
      0.58778117973923094, 0.57878709703728681, 0.56976357569557246,
      0.56071122540718166, 0.55163065026165148, 0.54252244882246536,
      0.53338721420775237, 0.52422553417429518, 0.51503799120454685,
      0.50582516259684429, 0.496587620558494, 0.48732593230185584,
      0.47804066014324814, 0.46873236160461923, 0.45940158951795335,
      0.4500488921322201, 0.44067481322297669, 0.4312798922043336,
      0.42186466424336594, 0.41242966037681922, 0.40297540763002476,
      0.39350242913798256, 0.38401124426847333, 0.374502368747196,
      0.36497631478471609, 0.35543359120533413, 0.34587470357755368,
      0.33630015434630145, 0.32671044296660112, 0.31710606603877084,
      0.30748751744496139, 0.29785528848700005, 0.28820986802542459,
      0.27855174261961152, 0.26888139666895994, 0.25919931255495793,
      0.24950597078410972, 0.23980185013162766, 0.23008742778574831,
      0.22036317949264198, 0.2106295797017784, 0.20088710171169252,
      0.19113621781605081, 0.18137739944987852, 0.17161111733595094,
      0.16183784163117876, 0.15205804207292317, 0.14227218812514536,
      0.13248074912433297, 0.12268419442503481, 0.11288299354501988,
      0.10307761630985728, 0.093268532996938353, 0.083456214478749235,
      0.073641132365375755, 0.063823759146139331, 0.054004568330236348,
      0.044184034586352575, 0.034362633881116544, 0.024540843616326732,
      0.014719142764871485, 0.0048980120052434552, -0.0049220661454259015,
      -0.01474060719991727, -0.024557124571088041, -0.034371129443823284,
      -0.044182130648751206, -0.053989634537878584, -0.063793144862236334,
      -0.073592162651490989, -0.0833861860958026, -0.093174710429784674,
      -0.10295722781884217, -0.11273322724780788, -0.12250219441204599,
      -0.13226361161105249, -0.14201695764465455, -0.15176170771182745,
      -0.16149733331225413, -0.17122330215070142, -0.18093907804417195,
      -0.19064412083207907, -0.20033788628931826, -0.21001982604245584,
      -0.21968938748898462, -0.22934601371976157, -0.23898914344471317,
      -0.24861821092175534, -0.25823264588913564, -0.26783187350112103,
      -0.27741531426716082, -0.28698238399454923, -0.29653249373464219,
      -0.30606504973268617, -0.3155794533812657, -0.32507510117749838,
      -0.33455138468390183, -0.34400769049312291, -0.35344340019639581,
      -0.36285789035594973, -0.37225053248124451, -0.38162069300918167,
      -0.39096773328826639, -0.40029100956676039, -0.40958987298488025,
      -0.41886366957103582, -0.42811174024217663, -0.437333420808199,
      -0.44652804198055934, -0.45569492938494671, -0.46483340357821179,
      -0.47394278006944096, -0.48302236934522608, -0.492071476899204,
      -0.50108940326575058, -0.51007544405800109, -0.5190288900100386,
      -0.52794902702339552, -0.53683513621778978, -0.54568649398612112,
      -0.55450237205374442, -0.5632820375419807, -0.57202475303591882,
      -0.58072977665643033, -0.5893963621364765, -0.5980237589015992,
      -0.60661121215469271, -0.61515796296494185, -0.62366324836098186,
      -0.63212630142825588, -0.64054635141049221, -0.64892262381537114,
      -0.65725434052428189, -0.66554071990619323 } ;

    DATA_COLLECTION_DW.FromWorkspace1_PWORK.TimePtr = (void *) pTimeValues0;
    DATA_COLLECTION_DW.FromWorkspace1_PWORK.DataPtr = (void *) pDataValues0;
    DATA_COLLECTION_DW.FromWorkspace1_IWORK.PrevIndex = 0;
  }

  /* Start for DiscretePulseGenerator: '<Root>/Pulse Generator' */
  DATA_COLLECTION_DW.clockTickCounter = 0;

  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: DATA_COLLECTION/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8", "0", &DATA_COLLECTION_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(DATA_COLLECTION_M, _rt_error_message);
      return;
    }

    is_switching = false;
    if ((DATA_COLLECTION_P.HILInitialize_CKPStart && !is_switching) ||
        (DATA_COLLECTION_P.HILInitialize_CKPEnter && is_switching)) {
      result = hil_set_clock_mode(DATA_COLLECTION_DW.HILInitialize_Card,
        (t_clock *) DATA_COLLECTION_P.HILInitialize_CKChannels, 2U,
        (t_clock_mode *) DATA_COLLECTION_P.HILInitialize_CKModes);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(DATA_COLLECTION_M, _rt_error_message);
        return;
      }
    }

    result = hil_watchdog_clear(DATA_COLLECTION_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(DATA_COLLECTION_M, _rt_error_message);
      return;
    }

    if ((DATA_COLLECTION_P.HILInitialize_AIPStart && !is_switching) ||
        (DATA_COLLECTION_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &DATA_COLLECTION_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (DATA_COLLECTION_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &DATA_COLLECTION_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = DATA_COLLECTION_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges(DATA_COLLECTION_DW.HILInitialize_Card,
        DATA_COLLECTION_P.HILInitialize_AIChannels, 8U,
        &DATA_COLLECTION_DW.HILInitialize_AIMinimums[0],
        &DATA_COLLECTION_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(DATA_COLLECTION_M, _rt_error_message);
        return;
      }
    }

    if ((DATA_COLLECTION_P.HILInitialize_AOPStart && !is_switching) ||
        (DATA_COLLECTION_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &DATA_COLLECTION_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (DATA_COLLECTION_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &DATA_COLLECTION_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = DATA_COLLECTION_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges
        (DATA_COLLECTION_DW.HILInitialize_Card,
         DATA_COLLECTION_P.HILInitialize_AOChannels, 8U,
         &DATA_COLLECTION_DW.HILInitialize_AOMinimums[0],
         &DATA_COLLECTION_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(DATA_COLLECTION_M, _rt_error_message);
        return;
      }
    }

    if ((DATA_COLLECTION_P.HILInitialize_AOStart && !is_switching) ||
        (DATA_COLLECTION_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &DATA_COLLECTION_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = DATA_COLLECTION_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(DATA_COLLECTION_DW.HILInitialize_Card,
        DATA_COLLECTION_P.HILInitialize_AOChannels, 8U,
        &DATA_COLLECTION_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(DATA_COLLECTION_M, _rt_error_message);
        return;
      }
    }

    if (DATA_COLLECTION_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &DATA_COLLECTION_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = DATA_COLLECTION_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (DATA_COLLECTION_DW.HILInitialize_Card,
         DATA_COLLECTION_P.HILInitialize_AOChannels, 8U,
         &DATA_COLLECTION_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(DATA_COLLECTION_M, _rt_error_message);
        return;
      }
    }

    result = hil_set_digital_directions(DATA_COLLECTION_DW.HILInitialize_Card,
      DATA_COLLECTION_P.HILInitialize_DIChannels, 8U,
      DATA_COLLECTION_P.HILInitialize_DOChannels, 9U);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(DATA_COLLECTION_M, _rt_error_message);
      return;
    }

    if ((DATA_COLLECTION_P.HILInitialize_DOStart && !is_switching) ||
        (DATA_COLLECTION_P.HILInitialize_DOEnter && is_switching)) {
      {
        int_T i1;
        boolean_T *dw_DOBits = &DATA_COLLECTION_DW.HILInitialize_DOBits[0];
        for (i1=0; i1 < 9; i1++) {
          dw_DOBits[i1] = DATA_COLLECTION_P.HILInitialize_DOInitial;
        }
      }

      result = hil_write_digital(DATA_COLLECTION_DW.HILInitialize_Card,
        DATA_COLLECTION_P.HILInitialize_DOChannels, 9U, (t_boolean *)
        &DATA_COLLECTION_DW.HILInitialize_DOBits[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(DATA_COLLECTION_M, _rt_error_message);
        return;
      }
    }

    if (DATA_COLLECTION_P.HILInitialize_DOReset) {
      {
        int_T i1;
        int32_T *dw_DOStates = &DATA_COLLECTION_DW.HILInitialize_DOStates[0];
        for (i1=0; i1 < 9; i1++) {
          dw_DOStates[i1] = DATA_COLLECTION_P.HILInitialize_DOWatchdog;
        }
      }

      result = hil_watchdog_set_digital_expiration_state
        (DATA_COLLECTION_DW.HILInitialize_Card,
         DATA_COLLECTION_P.HILInitialize_DOChannels, 9U, (const t_digital_state *)
         &DATA_COLLECTION_DW.HILInitialize_DOStates[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(DATA_COLLECTION_M, _rt_error_message);
        return;
      }
    }

    if ((DATA_COLLECTION_P.HILInitialize_EIPStart && !is_switching) ||
        (DATA_COLLECTION_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &DATA_COLLECTION_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = DATA_COLLECTION_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (DATA_COLLECTION_DW.HILInitialize_Card,
         DATA_COLLECTION_P.HILInitialize_EIChannels, 8U,
         (t_encoder_quadrature_mode *)
         &DATA_COLLECTION_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(DATA_COLLECTION_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_FilterFrequency =
          &DATA_COLLECTION_DW.HILInitialize_FilterFrequency[0];
        for (i1=0; i1 < 8; i1++) {
          dw_FilterFrequency[i1] = DATA_COLLECTION_P.HILInitialize_EIFrequency;
        }
      }

      result = hil_set_encoder_filter_frequency
        (DATA_COLLECTION_DW.HILInitialize_Card,
         DATA_COLLECTION_P.HILInitialize_EIChannels, 8U,
         &DATA_COLLECTION_DW.HILInitialize_FilterFrequency[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(DATA_COLLECTION_M, _rt_error_message);
        return;
      }
    }

    if ((DATA_COLLECTION_P.HILInitialize_EIStart && !is_switching) ||
        (DATA_COLLECTION_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &DATA_COLLECTION_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = DATA_COLLECTION_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(DATA_COLLECTION_DW.HILInitialize_Card,
        DATA_COLLECTION_P.HILInitialize_EIChannels, 8U,
        &DATA_COLLECTION_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(DATA_COLLECTION_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_write_digital_timebase_block): '<Root>/HIL Write Digital Timebase' */

  /* S-Function Block: DATA_COLLECTION/HIL Write Digital Timebase (hil_write_digital_timebase_block) */
  {
    t_error result;
    DATA_COLLECTION_DW.HILWriteDigitalTimebase_Started = false;
    result = hil_task_create_digital_writer
      (DATA_COLLECTION_DW.HILInitialize_Card,
       DATA_COLLECTION_P.HILWriteDigitalTimebase_samples,
       &DATA_COLLECTION_P.HILWriteDigitalTimebase_channel, 1,
       &DATA_COLLECTION_DW.HILWriteDigitalTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(DATA_COLLECTION_M, _rt_error_message);
    }
  }

  /* InitializeConditions for UnitDelay: '<S20>/UD' */
  DATA_COLLECTION_DW.UD_DSTATE =
    DATA_COLLECTION_P.DiscreteDerivative3_ICPrevScale;

  /* InitializeConditions for UnitDelay: '<S17>/UD' */
  DATA_COLLECTION_DW.UD_DSTATE_g =
    DATA_COLLECTION_P.DiscreteDerivative_ICPrevScaled;

  /* InitializeConditions for UnitDelay: '<S19>/UD' */
  DATA_COLLECTION_DW.UD_DSTATE_g1 =
    DATA_COLLECTION_P.DiscreteDerivative2_ICPrevScale;

  /* InitializeConditions for DiscreteIntegrator: '<S7>/Discrete-Time Integrator' */
  DATA_COLLECTION_DW.DiscreteTimeIntegrator_DSTATE_p =
    DATA_COLLECTION_P.DiscreteTimeIntegrator_IC_i;

  /* InitializeConditions for UnitDelay: '<S18>/UD' */
  DATA_COLLECTION_DW.UD_DSTATE_j =
    DATA_COLLECTION_P.DiscreteDerivative1_ICPrevScale;

  /* InitializeConditions for UnitDelay: '<S24>/UD' */
  DATA_COLLECTION_DW.UD_DSTATE_h =
    DATA_COLLECTION_P.DiscreteDerivative3_ICPrevSca_i;

  /* InitializeConditions for UnitDelay: '<S21>/UD' */
  DATA_COLLECTION_DW.UD_DSTATE_i =
    DATA_COLLECTION_P.DiscreteDerivative_ICPrevScal_l;

  /* InitializeConditions for UnitDelay: '<S23>/UD' */
  DATA_COLLECTION_DW.UD_DSTATE_er =
    DATA_COLLECTION_P.DiscreteDerivative2_ICPrevSca_n;

  /* InitializeConditions for DiscreteIntegrator: '<S8>/Discrete-Time Integrator' */
  DATA_COLLECTION_DW.DiscreteTimeIntegrator_DSTATE_a =
    DATA_COLLECTION_P.DiscreteTimeIntegrator_IC_l;

  /* InitializeConditions for UnitDelay: '<S22>/UD' */
  DATA_COLLECTION_DW.UD_DSTATE_d =
    DATA_COLLECTION_P.DiscreteDerivative1_ICPrevSca_c;

  /* InitializeConditions for UnitDelay: '<Root>/Unit Delay' */
  DATA_COLLECTION_DW.UnitDelay_DSTATE[0] =
    DATA_COLLECTION_P.UnitDelay_InitialCondition;

  /* InitializeConditions for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
  DATA_COLLECTION_DW.DiscreteTimeIntegrator_DSTATE[0] =
    DATA_COLLECTION_P.DiscreteTimeIntegrator_IC;

  /* InitializeConditions for UnitDelay: '<S1>/UD' */
  DATA_COLLECTION_DW.UD_DSTATE_e[0] =
    DATA_COLLECTION_P.DiscreteDerivative_ICPrevScal_k;

  /* InitializeConditions for UnitDelay: '<Root>/Unit Delay1' */
  DATA_COLLECTION_DW.UnitDelay1_DSTATE[0] =
    DATA_COLLECTION_P.UnitDelay1_InitialCondition;

  /* InitializeConditions for UnitDelay: '<Root>/Unit Delay2' */
  DATA_COLLECTION_DW.UnitDelay2_DSTATE[0] =
    DATA_COLLECTION_P.UnitDelay2_InitialCondition;

  /* InitializeConditions for UnitDelay: '<Root>/Unit Delay' */
  DATA_COLLECTION_DW.UnitDelay_DSTATE[1] =
    DATA_COLLECTION_P.UnitDelay_InitialCondition;

  /* InitializeConditions for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
  DATA_COLLECTION_DW.DiscreteTimeIntegrator_DSTATE[1] =
    DATA_COLLECTION_P.DiscreteTimeIntegrator_IC;

  /* InitializeConditions for UnitDelay: '<S1>/UD' */
  DATA_COLLECTION_DW.UD_DSTATE_e[1] =
    DATA_COLLECTION_P.DiscreteDerivative_ICPrevScal_k;

  /* InitializeConditions for UnitDelay: '<Root>/Unit Delay1' */
  DATA_COLLECTION_DW.UnitDelay1_DSTATE[1] =
    DATA_COLLECTION_P.UnitDelay1_InitialCondition;

  /* InitializeConditions for UnitDelay: '<Root>/Unit Delay2' */
  DATA_COLLECTION_DW.UnitDelay2_DSTATE[1] =
    DATA_COLLECTION_P.UnitDelay2_InitialCondition;
}

/* Model terminate function */
void DATA_COLLECTION_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: DATA_COLLECTION/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_digital_outputs = 0;
    hil_task_stop_all(DATA_COLLECTION_DW.HILInitialize_Card);
    hil_monitor_stop_all(DATA_COLLECTION_DW.HILInitialize_Card);
    is_switching = false;
    if ((DATA_COLLECTION_P.HILInitialize_AOTerminate && !is_switching) ||
        (DATA_COLLECTION_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &DATA_COLLECTION_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = DATA_COLLECTION_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((DATA_COLLECTION_P.HILInitialize_DOTerminate && !is_switching) ||
        (DATA_COLLECTION_P.HILInitialize_DOExit && is_switching)) {
      {
        int_T i1;
        boolean_T *dw_DOBits = &DATA_COLLECTION_DW.HILInitialize_DOBits[0];
        for (i1=0; i1 < 9; i1++) {
          dw_DOBits[i1] = DATA_COLLECTION_P.HILInitialize_DOFinal;
        }
      }

      num_final_digital_outputs = 9U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_digital_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(DATA_COLLECTION_DW.HILInitialize_Card
                         , DATA_COLLECTION_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , NULL, 0
                         , DATA_COLLECTION_P.HILInitialize_DOChannels,
                         num_final_digital_outputs
                         , NULL, 0
                         , &DATA_COLLECTION_DW.HILInitialize_AOVoltages[0]
                         , NULL
                         , (t_boolean *)
                         &DATA_COLLECTION_DW.HILInitialize_DOBits[0]
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(DATA_COLLECTION_DW.HILInitialize_Card,
            DATA_COLLECTION_P.HILInitialize_AOChannels, num_final_analog_outputs,
            &DATA_COLLECTION_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_digital_outputs > 0) {
          local_result = hil_write_digital(DATA_COLLECTION_DW.HILInitialize_Card,
            DATA_COLLECTION_P.HILInitialize_DOChannels,
            num_final_digital_outputs, (t_boolean *)
            &DATA_COLLECTION_DW.HILInitialize_DOBits[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(DATA_COLLECTION_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(DATA_COLLECTION_DW.HILInitialize_Card);
    hil_monitor_delete_all(DATA_COLLECTION_DW.HILInitialize_Card);
    hil_close(DATA_COLLECTION_DW.HILInitialize_Card);
    DATA_COLLECTION_DW.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  DATA_COLLECTION_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  DATA_COLLECTION_update();
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
  DATA_COLLECTION_initialize();
}

void MdlTerminate(void)
{
  DATA_COLLECTION_terminate();
}

/* Registration function */
RT_MODEL_DATA_COLLECTION_T *DATA_COLLECTION(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)DATA_COLLECTION_M, 0,
                sizeof(RT_MODEL_DATA_COLLECTION_T));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = DATA_COLLECTION_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    DATA_COLLECTION_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    DATA_COLLECTION_M->Timing.sampleTimes =
      (&DATA_COLLECTION_M->Timing.sampleTimesArray[0]);
    DATA_COLLECTION_M->Timing.offsetTimes =
      (&DATA_COLLECTION_M->Timing.offsetTimesArray[0]);

    /* task periods */
    DATA_COLLECTION_M->Timing.sampleTimes[0] = (0.01);

    /* task offsets */
    DATA_COLLECTION_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(DATA_COLLECTION_M, &DATA_COLLECTION_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = DATA_COLLECTION_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    DATA_COLLECTION_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(DATA_COLLECTION_M, 30.0);
  DATA_COLLECTION_M->Timing.stepSize0 = 0.01;

  /* External mode info */
  DATA_COLLECTION_M->Sizes.checksums[0] = (392652915U);
  DATA_COLLECTION_M->Sizes.checksums[1] = (2986939835U);
  DATA_COLLECTION_M->Sizes.checksums[2] = (1195715854U);
  DATA_COLLECTION_M->Sizes.checksums[3] = (48111091U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[16];
    DATA_COLLECTION_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = &rtAlwaysEnabled;
    systemRan[7] = &rtAlwaysEnabled;
    systemRan[8] = &rtAlwaysEnabled;
    systemRan[9] = &rtAlwaysEnabled;
    systemRan[10] = &rtAlwaysEnabled;
    systemRan[11] = &rtAlwaysEnabled;
    systemRan[12] = &rtAlwaysEnabled;
    systemRan[13] = &rtAlwaysEnabled;
    systemRan[14] = &rtAlwaysEnabled;
    systemRan[15] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(DATA_COLLECTION_M->extModeInfo,
      &DATA_COLLECTION_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(DATA_COLLECTION_M->extModeInfo,
                        DATA_COLLECTION_M->Sizes.checksums);
    rteiSetTPtr(DATA_COLLECTION_M->extModeInfo, rtmGetTPtr(DATA_COLLECTION_M));
  }

  DATA_COLLECTION_M->solverInfoPtr = (&DATA_COLLECTION_M->solverInfo);
  DATA_COLLECTION_M->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&DATA_COLLECTION_M->solverInfo, 0.01);
  rtsiSetSolverMode(&DATA_COLLECTION_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  DATA_COLLECTION_M->blockIO = ((void *) &DATA_COLLECTION_B);
  (void) memset(((void *) &DATA_COLLECTION_B), 0,
                sizeof(B_DATA_COLLECTION_T));

  {
    DATA_COLLECTION_B.TSamp = 0.0;
    DATA_COLLECTION_B.TSamp_d = 0.0;
    DATA_COLLECTION_B.VectorConcatenate1[0] = 0.0;
    DATA_COLLECTION_B.VectorConcatenate1[1] = 0.0;
    DATA_COLLECTION_B.Sum2[0] = 0.0;
    DATA_COLLECTION_B.Sum2[1] = 0.0;
    DATA_COLLECTION_B.TSamp_i[0] = 0.0;
    DATA_COLLECTION_B.TSamp_i[1] = 0.0;
    DATA_COLLECTION_B.FromWorkspace3[0] = 0.0;
    DATA_COLLECTION_B.FromWorkspace3[1] = 0.0;
    DATA_COLLECTION_B.FromWorkspace1[0] = 0.0;
    DATA_COLLECTION_B.FromWorkspace1[1] = 0.0;
    DATA_COLLECTION_B.Torquetocurrent = 0.0;
    DATA_COLLECTION_B.TSamp_f = 0.0;
    DATA_COLLECTION_B.Current = 0.0;
    DATA_COLLECTION_B.Sum1 = 0.0;
    DATA_COLLECTION_B.TSamp_p = 0.0;
    DATA_COLLECTION_B.Saturation = 0.0;
    DATA_COLLECTION_B.VectorConcatenate[0] = 0.0;
    DATA_COLLECTION_B.VectorConcatenate[1] = 0.0;
    DATA_COLLECTION_B.VectorConcatenate[2] = 0.0;
    DATA_COLLECTION_B.VectorConcatenate[3] = 0.0;
    DATA_COLLECTION_B.TSamp_g = 0.0;
    DATA_COLLECTION_B.TSamp_b = 0.0;
    DATA_COLLECTION_B.Torquetocurrent_k = 0.0;
    DATA_COLLECTION_B.TSamp_j = 0.0;
    DATA_COLLECTION_B.Current_b = 0.0;
    DATA_COLLECTION_B.Sum1_d = 0.0;
    DATA_COLLECTION_B.TSamp_bl = 0.0;
    DATA_COLLECTION_B.Saturation_m = 0.0;
    DATA_COLLECTION_B.VectorConcatenate_d[0] = 0.0;
    DATA_COLLECTION_B.VectorConcatenate_d[1] = 0.0;
    DATA_COLLECTION_B.VectorConcatenate_d[2] = 0.0;
    DATA_COLLECTION_B.VectorConcatenate_d[3] = 0.0;
    DATA_COLLECTION_B.UnitDelay2[0] = 0.0;
    DATA_COLLECTION_B.UnitDelay2[1] = 0.0;
    DATA_COLLECTION_B.HILReadDigital_o1 = 0.0;
    DATA_COLLECTION_B.HILReadDigital_o2 = 0.0;
    DATA_COLLECTION_B.HILReadDigital_o3 = 0.0;
  }

  /* parameters */
  DATA_COLLECTION_M->defaultParam = ((real_T *)&DATA_COLLECTION_P);

  /* states (dwork) */
  DATA_COLLECTION_M->dwork = ((void *) &DATA_COLLECTION_DW);
  (void) memset((void *)&DATA_COLLECTION_DW, 0,
                sizeof(DW_DATA_COLLECTION_T));
  DATA_COLLECTION_DW.UD_DSTATE = 0.0;
  DATA_COLLECTION_DW.UD_DSTATE_g = 0.0;
  DATA_COLLECTION_DW.UnitDelay_DSTATE[0] = 0.0;
  DATA_COLLECTION_DW.UnitDelay_DSTATE[1] = 0.0;
  DATA_COLLECTION_DW.DiscreteTimeIntegrator_DSTATE[0] = 0.0;
  DATA_COLLECTION_DW.DiscreteTimeIntegrator_DSTATE[1] = 0.0;
  DATA_COLLECTION_DW.UD_DSTATE_e[0] = 0.0;
  DATA_COLLECTION_DW.UD_DSTATE_e[1] = 0.0;
  DATA_COLLECTION_DW.UnitDelay1_DSTATE[0] = 0.0;
  DATA_COLLECTION_DW.UnitDelay1_DSTATE[1] = 0.0;
  DATA_COLLECTION_DW.UD_DSTATE_g1 = 0.0;
  DATA_COLLECTION_DW.DiscreteTimeIntegrator_DSTATE_p = 0.0;
  DATA_COLLECTION_DW.UD_DSTATE_j = 0.0;
  DATA_COLLECTION_DW.UD_DSTATE_h = 0.0;
  DATA_COLLECTION_DW.UD_DSTATE_i = 0.0;
  DATA_COLLECTION_DW.UD_DSTATE_er = 0.0;
  DATA_COLLECTION_DW.DiscreteTimeIntegrator_DSTATE_a = 0.0;
  DATA_COLLECTION_DW.UD_DSTATE_d = 0.0;
  DATA_COLLECTION_DW.UnitDelay2_DSTATE[0] = 0.0;
  DATA_COLLECTION_DW.UnitDelay2_DSTATE[1] = 0.0;
  DATA_COLLECTION_DW.HILReadAnalog_Buffer = 0.0;
  DATA_COLLECTION_DW.HILReadAnalog_Buffer_n = 0.0;

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      DATA_COLLECTION_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      DATA_COLLECTION_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      DATA_COLLECTION_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      DATA_COLLECTION_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      DATA_COLLECTION_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      DATA_COLLECTION_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    DATA_COLLECTION_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 17;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  DATA_COLLECTION_M->Sizes.numContStates = (0);/* Number of continuous states */
  DATA_COLLECTION_M->Sizes.numY = (0); /* Number of model outputs */
  DATA_COLLECTION_M->Sizes.numU = (0); /* Number of model inputs */
  DATA_COLLECTION_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  DATA_COLLECTION_M->Sizes.numSampTimes = (1);/* Number of sample times */
  DATA_COLLECTION_M->Sizes.numBlocks = (179);/* Number of blocks */
  DATA_COLLECTION_M->Sizes.numBlockIO = (31);/* Number of block outputs */
  DATA_COLLECTION_M->Sizes.numBlockPrms = (217);/* Sum of parameter "widths" */
  return DATA_COLLECTION_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
