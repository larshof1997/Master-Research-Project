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
 * C source code generated on : Tue Mar  3 11:06:22 2026
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
  if (rtb_Add > DATA_COLLECTION_P.i_sat2) {
    DATA_COLLECTION_B.Saturation = DATA_COLLECTION_P.i_sat2;
  } else if (rtb_Add < -DATA_COLLECTION_P.i_sat2) {
    DATA_COLLECTION_B.Saturation = -DATA_COLLECTION_P.i_sat2;
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
  if (rtb_Add > DATA_COLLECTION_P.i_sat1) {
    DATA_COLLECTION_B.Saturation_m = DATA_COLLECTION_P.i_sat1;
  } else if (rtb_Add < -DATA_COLLECTION_P.i_sat1) {
    DATA_COLLECTION_B.Saturation_m = -DATA_COLLECTION_P.i_sat1;
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
      0.0, 1.3877787807814457E-17, 0.0070410793955183321, 0.01409339506849136,
      0.021156321760687075, 0.028229230223370913, 0.035311487375677131,
      0.042402456464702004, 0.049501497227271138, 0.056607966053328435,
      0.063721216150896945, 0.0708405977125603, 0.077965458083410377,
      0.0850951419304102, 0.09222899141311601, 0.099366346355706084,
      0.10650654442025936, 0.11364892128122962, 0.12079281080105737,
      0.12793754520686412, 0.13508245526817014, 0.14222687047557864,
      0.1493701192203668, 0.15651152897492721, 0.16365042647399514,
      0.17078613789660813, 0.17791798904873191, 0.18504530554649562,
      0.19216741299997298, 0.19928363719744829, 0.206393304290107,
      0.21349574097708524, 0.22059027469081968, 0.2276762337826318,
      0.23475294770848509, 0.24181974721485189, 0.24887596452462446,
      0.25592093352301087, 0.262953989943345, 0.26997447155275489,
      0.27698171833761687, 0.28397507268873889, 0.29095387958620333,
      0.29791748678380647, 0.30486524499303158, 0.31179650806648906,
      0.31871063318076182, 0.32560698101858759, 0.33248491595031904,
      0.33934380621459215, 0.34618302409814344, 0.35300194611470903,
      0.35979995318294156, 0.36657643080328506, 0.37333076923373892,
      0.38006236366445367, 0.38677061439108906, 0.393454926986878,
      0.40011471247333058, 0.40674938748951539, 0.41335837445986123,
      0.41994110176041111, 0.42649700388347145, 0.43302552160059876,
      0.43952610212385751, 0.44599819926529227, 0.45244127359455821,
      0.45885479259464523, 0.46523823081564342, 0.47159107002648809,
      0.47791279936462866, 0.48420291548356825, 0.49046092269821095,
      0.49668633312797045, 0.50287866683757676, 0.50903745197553574,
      0.51516222491018193, 0.52125253036327324, 0.527307921541081,
      0.53332796026291729, 0.53931221708705412, 0.54526027143398426,
      0.5511717117069741, 0.55704613540986248, 0.56288314926205685,
      0.56868236931068283, 0.57444342103984247, 0.5801659394769314,
      0.58584956929598286, 0.59149396491798423, 0.5970987906081332,
      0.60266372056998962, 0.6081884390364849, 0.6136726403577506,
      0.6191160290857286, 0.624518320055527, 0.62987923846348726,
      0.63519851994192533, 0.640475910630521, 0.64571116724431465,
      0.65090405713828858, 0.65605435836849435, 0.66116185974971065,
      0.66622636090959242, 0.67124767233928762, 0.67622561544050475,
      0.68116002256899633, 0.68605073707444153, 0.69089761333670929,
      0.69570051679847367, 0.70045932399417021, 0.70517392257527267,
      0.70984421133187181, 0.71447010021054758, 0.71905151032851022,
      0.72358837398400944, 0.72808063466299222, 0.73252824704200048,
      0.736931176987307, 0.7412894015502679, 0.74560290895890313,
      0.74987169860568215, 0.75409578103152952, 0.75827517790603094,
      0.76240992200385216, 0.76650005717736414, 0.77054563832547807,
      0.77454673135869234, 0.77850341316036065, 0.78241577154417941,
      0.78628390520790814, 0.79010792368332683, 0.7938879472824425,
      0.797624107039958, 0.80131654465200719, 0.80496541241118258,
      0.80857087313785769, 0.81213310010783279, 0.81565227697631026,
      0.81912859769822721, 0.82256226644496133, 0.82595349751743374,
      0.82930251525562848, 0.83260955394455749, 0.83587485771669345,
      0.83909868045089753, 0.84228128566787153, 0.84542294642216,
      0.848523945190742, 0.8515845737582306, 0.85460513309872477,
      0.857585933254344, 0.86052729321047949, 0.86342954076779921,
      0.86629301241104983, 0.86911805317468427, 0.87190501650536834,
      0.8746542641213928, 0.8773661658690497, 0.88004109957600241,
      0.88267945090170263, 0.88528161318489906, 0.887847987288281,
      0.89037898144031, 0.89287501107428546, 0.89533649866469678,
      0.89776387356090859, 0.9001575718182393, 0.90251803602647973,
      0.90484571513590617, 0.907141064280848, 0.90940454460086162,
      0.91163662305957138, 0.91383777226123042, 0.91600847026506482,
      0.91814920039746084, 0.92026045106205256, 0.92234271554777625,
      0.92439649183494521, 0.92642228239942259, 0.92842059401493782,
      0.930391937553631, 0.932336827784871, 0.9342557831724283,
      0.93614932567006426, 0.93801798051560015, 0.93986227602354133,
      0.94168274337631985, 0.94347991641422546, 0.9452543314240992,
      0.94700652692685383, 0.94873704346389631, 0.95044642338252161,
      0.95213521062035023, 0.95380395048888444, 0.95545318945625024,
      0.95708347492920243, 0.95869535503446912, 0.96028937839950046,
      0.96186609393270528, 0.96342605060324449, 0.96496979722045806,
      0.9664978822130027, 0.96801085340776827, 0.96950925780865937,
      0.97099364137530642, 0.97246454880179223, 0.97392252329546092,
      0.97536810635589311, 0.97680183755411687, 0.97822425431213655,
      0.97963589168284859, 0.98103728213043162, 0.98242895531127072,
      0.98381143785550706, 0.985185253149284, 0.986550921117757,
      0.98790895800896161, 0.98925987617859, 0.99060418387577964,
      0.9919423850299639, 0.99327497903887274, 0.9946024605577618,
      0.99592531928992889, 0.99724403977860776, 0.99855910120030145,
      0.99987097715963735, 1.0011801354858059, 1.0024870380306687,
      1.003792140468597, 1.0050958920981148, 1.006398735645422,
      1.0077011070698647, 1.0090034353714141, 1.0103061424002484,
      1.011609642668466, 1.012914343164047, 1.0142206431670839,
      1.0155289340683777, 1.0168395991904613, 1.0181530136110992,
      1.0194695439893491, 1.0207895483942369, 1.0221133761361063,
      1.0234413676007161, 1.0247738540861357, 1.0261111576425013,
      1.0274535909146989, 1.0288014569880246, 1.0301550492368841,
      1.0315146511765834, 1.0328805363182789, 1.0342529680271206,
      1.0356321993836628, 1.0370184730485852, 1.0384120211307717,
      1.0398130650588087, 1.0412218154559436, 1.0426384720185549,
      1.044063223398179, 1.0454962470871467, 1.0469377093078607,
      1.0483877649057745, 1.0498465572461013, 1.0513142181143,
      1.0527908676203854, 1.0542766141070774, 1.0557715540618637,
      1.057275772032978, 1.058789340549344, 1.0603123200445272,
      1.0618447587847022, 1.0633866928006956, 1.0649381458241105,
      1.0664991292275743, 1.0680696419691345, 1.0696496705408227,
      1.0712391889214203, 1.0728381585334372, 1.0744465282043376,
      1.0760642341320197, 1.0776911998545835, 1.0793273362243887,
      1.0809725413864224, 1.0826267007610062, 1.0842896870308265,
      1.0859613601323272, 1.0876415672514632, 1.089330142823814,
      1.091026908539082, 1.0927316733499761, 1.0944442334854672,
      1.0961643724684498, 1.097891861137779, 1.0996264576747077,
      1.1013679076337053, 1.1031159439776603, 1.1048702871174725,
      1.1066306449559997, 1.1083967129363903, 1.1101681740947602,
      1.1119446991172171, 1.1137259464012195, 1.1155115621212566,
      1.117301180298832, 1.119094422876729, 1.1208908997975602,
      1.1226902090865503, 1.1244919369385635, 1.1262956578093259,
      1.1281009345108373, 1.1299073183109418, 1.1317143490370223,
      1.133521555183808, 1.1353284540252431, 1.1371345517304094,
      1.1389393434834525, 1.1407423136074835, 1.1425429356924255,
      1.1443406727267613, 1.1461349772331519, 1.1479252914078786,
      1.149711047264073, 1.1514916667786954, 1.1532665620432143,
      1.1550351354179391, 1.1567967796899734, 1.1585508782347269,
      1.160296805180949, 1.1620339255792267, 1.1637615955739036,
      1.165479162578362, 1.1671859654536194, 1.1688813346901787,
      1.1705645925930945, 1.1722350534701684, 1.17389202382325,
      1.1755348025425603, 1.1771626811039895, 1.1787749437693031,
      1.1803708677892009, 1.1819497236091623, 1.18351077507801,
      1.1850532796591375, 1.1865764886443255, 1.188079647370087,
      1.1895619954364691, 1.1910227669282487, 1.1924611906384452,
      1.1938764902940915, 1.1952678847841769, 1.196634588389706,
      1.1979758110157963, 1.199290758425734, 1.2005786324769221,
      1.2018386313586475, 1.2030699498315884, 1.2042717794689803,
      1.2054433088993828, 1.2065837240509503, 1.2076922083971375,
      1.208767943203767, 1.2098101077773677, 1.2108178797147242,
      1.2117904351535305, 1.2127269490240991, 1.2136265953020198,
      1.2144885472617055, 1.2153119777307286, 1.2160960593448846,
      1.2168399648038795, 1.217542867127585, 1.2182039399127531,
      1.2188223575901318, 1.2193972956818797, 1.2199279310592104,
      1.220413442200176, 1.220853009447519, 1.2212458152664871,
      1.2215910445025551, 1.2218878846389525, 1.2221355260539173,
      1.2223331622776037, 1.2224799902485433, 1.2225752105695979,
      1.2226180277632979, 1.2226076505265082, 1.2225432919843247,
      1.2224241699431169, 1.222249507142652, 1.2220185315072007,
      1.2217304763955519, 1.2213845808498591, 1.2209800898432333,
      1.2205162545260002, 1.2199923324705491, 1.2194075879146917,
      1.2187612920034456, 1.2180527230291787, 1.2172811666700243,
      1.216445916226492, 1.2155462728562048, 1.2145815458066815,
      1.2135510526460875, 1.2124541194918823, 1.2112900812372955,
      1.2100582817755399, 1.2087580742217148, 1.2073888211323069,
      1.2059498947222298, 1.2044406770793223, 1.2028605603762523,
      1.2012089470797365, 1.1994852501570274, 1.1976888932795939,
      1.1958193110239226, 1.1938759490693889, 1.191858264393125,
      1.1897657254618226, 1.1875978124204158, 1.1853540172775712,
      1.1830338440879389, 1.1806368091310959, 1.1781624410871299,
      1.1756102812088043, 1.1729798834902572, 1.1702708148321581,
      1.1674826552033051, 1.164614997798576, 1.1616674491932053,
      1.1586396294933288, 1.1555311724827479, 1.1523417257658723,
      1.1490709509067893, 1.1457185235644212, 1.14228413362372,
      1.1387674853228693, 1.1351682973764454, 1.1314863030944977,
      1.127721250497518, 1.1238729024272542, 1.119941036653344,
      1.1159254459757251, 1.1118259383227926, 1.1076423368452861,
      1.1033744800058489, 1.0990222216642691, 1.0945854311583398,
      1.0900639933803431, 1.0854578088491156, 1.0807667937776868,
      1.0759908801364559, 1.0711300157119066, 1.0661841641608243,
      1.0611533050600133, 1.0560374339514966, 1.0508365623831781,
      1.0455507179449681, 1.0401799443003561, 1.0347243012134182,
      1.0291838645712652, 1.0235587264019126, 1.0178489948875826,
      1.0120547943734197, 1.0061762653716373, 1.0002135645610846,
      0.99416686478223715, 0.98803635502762643, 0.98182224042769373,
      0.97552474223209884, 0.96914409778647326, 0.962680560504643,
      0.95613439983631765, 0.94950590123027512, 0.94279536609304326,
      0.9360031117431068, 0.929129471360642, 0.922174793932818,
      0.91513944419466631, 0.90802380256555737, 0.9008282650812911,
      0.8935532433218466, 0.88619916433479484, 0.87876647055442825,
      0.8712556197166087, 0.86366708476938725, 0.85600135377941955,
      0.84825892983420947, 0.8404403309402132, 0.83254608991685553,
      0.82457675428646937, 0.8165328861602299, 0.80841506212009839,
      0.80022387309682308, 0.79195992424405381, 0.78362383480859765,
      0.77521623799687123, 0.76673778083759037, 0.75818912404075189,
      0.7495709418529527, 0.74088392190909835, 0.73212876508054847,
      0.723306185319758, 0.71441690950146886, 0.70546167726049913,
      0.69644124082619119, 0.68735636485358087, 0.67820782625133524,
      0.66899641400652943, 0.65972292900631335, 0.65038818385653674,
      0.64099300269739257, 0.63153822101614154, 0.622024685456983,
      0.61245325362813119, 0.60282479390618326, 0.59314018523781287,
      0.58340031693889172, 0.57360608849107864, 0.56375840933596966,
      0.55385819866685737, 0.54390638521819468, 0.53390390705280333,
      0.52385171134693287, 0.51375075417321692, 0.50360200028161939,
      0.49340642287842362, 0.483165003403364, 0.47287873130495367,
      0.46254860381410079, 0.45217562571607228, 0.44176080912090088,
      0.43130517323229584, 0.42080974411515221, 0.41027555446171082,
      0.39970364335648118, 0.38909505603997252, 0.37845084367134252,
      0.36777206309001054, 0.35705977657634713, 0.34631505161149723,
      0.33553896063642341, 0.3247325808102583, 0.31389699376802249,
      0.30303328537782181, 0.29214254549756935, 0.28122586773134606,
      0.27028434918544797, 0.25931909022422472, 0.24833119422578018,
      0.23732176733761862, 0.22629191823230363, 0.21524275786323405,
      0.20417539922059202, 0.19309095708756613, 0.18199054779689841,
      0.17087528898787374, 0.15974629936379026, 0.14860469845002736,
      0.13745160635275325, 0.12628814351837903, 0.1151154304938205,
      0.1039345876876559, 0.092746735132237482, 0.08155299224685994,
      0.070354477602035559, 0.059152308684971885, 0.047947601666312747,
      0.036741471168218791, 0.025535030033867961, 0.014329389098444154,
      0.0031256569616852428, -0.0080750602379405546, -0.019271659047350224,
      -0.030463038921192103, -0.041648102442346374, -0.052825755540523586,
      -0.063994907708876211, -0.0751544722185701, -0.086303366331243539,
      -0.097440511509291949, -0.10856483362391314, -0.11967526316084695,
      -0.13077073542374842, -0.14185019073514024, -0.15291257463487323,
      -0.16395683807604031, -0.17498193761828515, -0.18598683561845425,
      -0.1969705004185254, -0.20793190653076402, -0.21887003482005585,
      -0.22978387268335057, -0.24067241422619062, -0.25153466043623868,
      -0.26236961935379094, -0.27317630623919481, -0.28395374373715776,
      -0.29470096203787072, -0.30541699903492286, -0.31610090047995093,
      -0.32675172013399872, -0.337368519915521, -0.34795037004502138,
      -0.35849634918625489, -0.36900554458399665, -0.37947705219830169,
      -0.38990997683525208, -0.40030343227414272, -0.41065654139108421,
      -0.42096843627898728, -0.4312382583639004, -0.44146515851767731,
      -0.4516482971669516, -0.46178684439838386, -0.47187998006017084,
      -0.48192689385978588, -0.49192678545794166, -0.50187886455874775,
      -0.51178235099604774, -0.5216364748159299, -0.5314404763553795,
      -0.54119360631708913, -0.55089512584038114, -0.56054430656826681,
      -0.57014043071060216, -0.57968279110337428, -0.58917069126406663,
      -0.59860344544314059, -0.60798037867160626, -0.61730082680469778,
      -0.62656413656164078, -0.63576966556153081, -0.64491678235530692,
      -0.65400486645385114, -0.66303330835219731, -0.67200150954987359,
      -0.68090888256737891, -0.68975485095882294, -0.69853884932071153,
      -0.70726032329692923, -0.71591872957989955, -0.72451353590797762,
      -0.73304422105905576, -0.74151027484043552, -0.7499111980749652,
      -0.758246502583479, -0.76651571116356076, -0.77471835756465446,
      -0.7828539864595474, -0.7909221534122679, -0.798922424842409,
      -0.80685437798592963, -0.81471760085244715, -0.82251169217906994,
      -0.83023626138080231, -0.83789092849755276, -0.84547532413779147,
      -0.85298908941889062, -0.86043187590419634, -0.86780334553686234,
      -0.87510317057050158, -0.88233103349668762, -0.88948662696936664,
      -0.89656965372621156, -0.90357982650697177, -0.91051686796887488,
      -0.91738051059912218, -0.9241704966245291, -0.93088657791836871,
      -0.93752851590446551, -0.94409608145859969, -0.95058905480727562,
      -0.95700722542390837, -0.96335039192248351, -0.96961836194876216,
      -0.975810952069071, -0.98192798765675637, -0.9879693027763472,
      -0.993934740065499, -0.99982415061478136, -1.0056373938453667,
      -1.0113743373846897, -1.0170348569401357, -1.0226188361708379,
      -1.0281261665576344, -1.0335567472712586, -1.0389104850388329,
      -1.0441872940087304, -1.0493870956138802, -1.0545098184335719,
      -1.0595553980538439, -1.0645237769265254, -1.0694149042269887,
      -1.074228735710697, -1.0789652335686244, -1.0836243662815925,
      -1.0882061084736394, -1.0927104407644532, -1.0971373496209675,
      -1.101486827208185, -1.1057588712393054, -1.10995348482523,
      -1.1140706763235162, -1.118110459186858, -1.1220728518111733,
      -1.1259578773833554, -1.1297655637287891, -1.1334959431586771,
      -1.13714905231728, -1.140724932029122, -1.1442236271462525,
      -1.1476451863956285, -1.1509896622266993, -1.1542571106592632,
      -1.1574475911316742, -1.1605611663494702, -1.1635979021345,
      -1.1665578672746157, -1.1694411333740171, -1.172247774704303,
      -1.1749778680563208, -1.177631492592875, -1.1802087297023707,
      -1.1827096628534577, -1.1851343774507652, -1.1874829606917654,
      -1.1897555014248737, -1.1919520900088254, -1.1940728181734057,
      -1.1961177788816235, -1.1980870661933518, -1.1999807751305525,
      -1.2017990015441105, -1.2035418419823736, -1.2052093935614374,
      -1.2068017538372646, -1.2083190206796801, -1.2097612921483183,
      -1.211128666370584, -1.2124212414216753, -1.2136391152067489,
      -1.2147823853452679, -1.2158511490576007, -1.21684550305393,
      -1.2177655434255172, -1.2186113655383926, -1.2193830639295093,
      -1.2200807322054357, -1.2207044629436083, -1.2212543475962274,
      -1.2217304763968304, -1.2221329382695811, -1.2224618207413518,
      -1.2227172098566108, -1.2228991900951893, -1.2230078442929546,
      -1.2230432535654356, -1.2230054972344471, -1.22289465275775,
      -1.2227107956617853, -1.2224539994775199, -1.2221243356794449,
      -1.2217218736277564, -1.2212466805137498, -1.220698821308472,
      -1.22007835871465, -1.2193853531219279, -1.2186198625654512,
      -1.217781942687802, -1.2168716467043408, -1.2158890253719514,
      -1.2148341269612239, -1.2137069972321002, -1.2125076794129916,
      -1.211236214183389, -1.2098926396599918, -1.2084769913863529,
      -1.2069893023260692, -1.2054296028595188, -1.203797920784162,
      -1.2020942813184108, -1.2003187071090724, -1.1984712182423762,
      -1.1965518322585904, -1.1945605641702217, -1.1924974264838084,
      -1.190362429225297, -1.1881555799690138, -1.1858768838702076,
      -1.1835263437011792, -1.1811039598909765, -1.1786097305686503,
      -1.176043651610063, -1.173405716688233, -1.1706959173272145,
      -1.1679142429594738, -1.1650606809867747, -1.1621352168445302,
      -1.1591378340696163, -1.1560685143716194, -1.1529272377074984,
      -1.1497139823596327, -1.1464287250172365, -1.1430714408611053,
      -1.1396421036516751, -1.1361406858203493, -1.1325671585640731,
      -1.1289214919431241, -1.1252036549820772, -1.1214136157738988,
      -1.1175513415871574, -1.1136167989762904, -1.1096099538948905,
      -1.1055307718119796, -1.1013792178312061, -1.0971552568129472,
      -1.0928588534992496, -1.0884899726415627, -1.084048579131232,
      -1.0795346381326769, -1.0749481152192262, -1.0702889765115344,
      -1.0655571888185493, -1.0607527197809492, -1.0558755380170195,
      -1.0509256132708868, -1.0459029165630636, -1.0408074203432474,
      -1.035639098645301, -1.0303979272443524, -1.0250838838159642,
      -1.0196969480972888, -1.0142371020501584, -1.0087043300260332,
      -1.0030986189327391, -0.99741995840293773, -0.99166834096424594,
      -0.98584376221092873, -0.97994622097712347, -0.97397571951147532,
      -0.96793226365316221, -0.96181586300918254, -0.95562653113287732,
      -0.949364285703572, -0.94302914870729826, -0.93662114661846851,
      -0.93014031058247582, -0.92358667659911231, -0.91696028570672372,
      -0.91026118416702984, -0.90348942365053, -0.896645061422403,
      -0.88972816052882675, -0.88273878998363164, -0.87567702495519961,
      -0.868542946953539, -0.86133664401743526, -0.8540582109015995,
      -0.84670774926373038, -0.83928536785140917, -0.83179118268872754,
      -0.82422531726257287, -0.81658790270848836, -0.80887907799601655,
      -0.801098990113427, -0.79324779425176983, -0.7853256539881408,
      -0.77733274146809062, -0.76926923758707555, -0.76113533217088447,
      -0.752931224154917, -0.7446571217622806, -0.73631324268056475,
      -0.72789981423724, -0.7194170735735913, -0.71086526781708459,
      -0.70224465425209437, -0.69355550048890513, -0.68479808463089142,
      -0.67597269543979965, -0.66707963249905289, -0.658119206374979,
      -0.649091738775883, -0.63999756270889152, -0.6308370226344755,
      -0.62161047461856511, -0.61231828648218689, -0.60296083794852917,
      -0.59353852078737412, -0.584051738956784, -0.57450090874199811,
      -0.56488645889143607, -0.55520883074974425, -0.54546847838780022,
      -0.53566586872959876, -0.525801481675948, -0.51587581022490647,
      -0.505889360588865, -0.49584265230822733, -0.48573621836160186,
      -0.47557060527244205, -0.46534637321205441, -0.45506409609891413,
      -0.44472436169422486, -0.43432777169363468, -0.42387494181508306,
      -0.41336650188265883, -0.40280309590645608, -0.3921853821583407,
      -0.38151403324357835, -0.37078973616824162, -0.36001319240237412,
      -0.34918511793882112, -0.33830624334770593, -0.32737731382644153,
      -0.31639908924530097, -0.30537234418842518, -0.29429786799026925,
      -0.28317646476739688, -0.27200895344561921, -0.26079616778238673,
      -0.24953895638444284, -0.23823818272063046, -0.22689472512987938,
      -0.21550947682429, -0.20408334588729812, -0.19261725526685888,
      -0.18111214276365215, -0.16956896101424862, -0.15798867746921366,
      -0.1463722743661259, -0.1347207486974695, -0.12303511217338625,
      -0.1113163911792629, -0.0995656267281238, -0.0877838744078086,
      -0.075972204322927367, -0.064131701031558963, -0.052263463476708322,
      -0.040368604912448043, -0.028448252824815674, -0.016503548847382948,
      -0.004535648671537891, 0.0074542780485575139, 0.019465047796311308,
      0.031495463298384062, 0.043544313635655654, 0.055610374359556104,
      0.067692407613666961, 0.0797891622606564, 0.091899374014499269,
      0.10402176557800998, 0.11615504678563834, 0.12829791475153959,
      0.1404490540229052, 0.15260713673851989, 0.16477082279254729,
      0.17693876000351216, 0.1891095842884524, 0.20128191984222771,
      0.21345437932195876, 0.22562556403655659, 0.23779406414132342,
      0.24995845883758189, 0.26211731657732962, 0.27426919527283034,
      0.28641264251115711, 0.29854619577361552, 0.31066838266001995,
      0.32277772111776848, 0.33487271967569537, 0.34695187768261287,
      0.35901368555055047, 0.37105662500258407, 0.38307916932524,
      0.39507978362540508, 0.40705692509170044, 0.41900904326024135,
      0.4309345802847343, 0.44283197121086815, 0.45469964425489423,
      0.46653602108637948, 0.4783395171150322, 0.49010854178154928,
      0.50184149885240359, 0.51353678671852176, 0.52519279869775315,
      0.53680792334108152, 0.54838054474247178, 0.55990904285232734,
      0.57139179379441152, 0.58282717018621422, 0.59421354146264171,
      0.60554927420296956, 0.61683273246095471, 0.62806227809805248,
      0.63923627111960013, 0.65035307001394638, 0.66141103209436625,
      0.67240851384372569, 0.68334387126176555, 0.69421546021494485,
      0.7050216367887161, 0.71576075764215275, 0.72643118036484355,
      0.73703126383592132, 0.74755936858516647, 0.75801385715605618,
      0.76839309447067006, 0.77869544819633929, 0.78891928911396025,
      0.79906299148783466, 0.80912493343696235, 0.81910349730764265,
      0.82899707004733669, 0.83880404357961147, 0.84852281518011319,
      0.8581517878534346, 0.86768937071076613, 0.87713397934823123,
      0.88648403622579208, 0.89573797104659292, 0.90489422113667484,
      0.91395123182489058, 0.92290745682295738, 0.93176135860549458,
      0.94051140878996553, 0.94915608851638233, 0.95769388882666506,
      0.96612331104355953, 0.97444286714896344, 0.98265108016157454,
      0.99074648451373537, 0.99872762642734758, 1.0065930642887537,
      1.0143413690224716, 1.0219711244636478, 1.0294809277291301,
      1.0368693895870307, 1.0441351348246886, 1.0512768026148669,
      1.058293046880129, 1.0651825366552228, 1.0719439564474003,
      1.0785760065945236, 1.0850774036208748, 1.0914468805905153,
      1.097683187458131, 1.1037850914171978, 1.1097513772453893,
      1.1155808476470974, 1.1212723235929687, 1.1268246446563177,
      1.1322366693463364, 1.1375072754379758, 1.1426353602983816,
      1.1476198412097876, 1.15245965568876, 1.1571537618016727,
      1.1617011384763125, 1.1661007858095207, 1.1703517253707421,
      1.1744530005014033, 1.1784036766099928, 1.1822028414627692,
      1.1858496054699652, 1.189343101967413, 1.1926824874934863,
      1.1958669420612478, 1.1988956694257236, 1.2017678973462071,
      1.2044828778434835, 1.2070398874519073, 1.209438227466217,
      1.2116772241830138, 1.213756229136808, 1.2156746193305576,
      1.2174317974605966, 1.2190271921358773, 1.2204602580914572,
      1.2217304763961259, 1.2228373546541074, 1.223780427200762,
      1.2245592552922067, 1.2251734272887755, 1.2256225588322591,
      1.2259062930168436, 1.2260243005536835, 1.2259762799290392,
      1.2257619575559171, 1.225381087919142, 1.2248334537138137,
      1.2241188659770719, 1.2232371642131183, 1.2221882165114402,
      1.2209719196581903, 1.2195881992406508, 1.2180370097447462,
      1.2163183346455559, 1.2144321864907754, 1.2123786069770839,
      1.210157667019379, 1.2077694668128385, 1.2052141358877602,
      1.2024918331571688, 1.1996027469571275, 1.1965470950797394,
      1.1933251247988155, 1.1899371128881648, 1.186383365632486,
      1.1826642188308574, 1.1787800377927748, 1.1747312173267459,
      1.1705181817214012, 1.1661413847191322, 1.1616013094822191,
      1.1568984685514703, 1.1520334037973328, 1.1470066863634909,
      1.1418189166029515, 1.1364707240066014, 1.1309627671242459,
      1.1252957334781419, 1.1194703394690164, 1.1134873302745931,
      1.1073474797406309, 1.1010515902644866, 1.0946004926712252,
      1.0879950460822931, 1.0812361377767634, 1.0743246830452036,
      1.0672616250361515, 1.0600479345952696, 1.052684610097169,
      1.0451726772699645, 1.0375131890125759, 1.0297072252048245,
      1.02175589251035, 1.0136603241724063, 1.0054216798025579,
      0.99704114516234543, 0.98851993193795118, 0.97985927750792245,
      0.97106044470399433, 0.962124721565084, 0.95305342108449831,
      0.94384788095042016, 0.93450946327972084, 0.9250395543451897,
      0.91543956429621487, 0.90571092687299881, 0.89585509911437522,
      0.885873561059297, 0.87576781544206928, 0.8655393873813978,
      0.85518982406334465, 0.84472069441823761, 0.834133588791665,
      0.82343011860958237, 0.81261191603766258, 0.80168063363494868,
      0.79063794400190524, 0.77948553942295651, 0.76822513150362082,
      0.75685845080229464, 0.74538724645683407, 0.73381328580598848,
      0.72213835400580317, 0.71036425364109379, 0.69849280433209315,
      0.68652584233635949, 0.67446522014608423, 0.66231280608086229,
      0.65007048387607869, 0.63774015226698355, 0.62532372456859586,
      0.61282312825152541, 0.60024030451384991, 0.58757720784913514,
      0.57483580561073966, 0.56201807757252142, 0.5491260154860349,
      0.536161622634377, 0.52312691338278949, 0.51002391272612457,
      0.49685465583333022, 0.48362118758904149, 0.47032556213243865,
      0.45696984239348459, 0.44355609962665488, 0.43008641294231453,
      0.41656286883585564, 0.40298756071473174, 0.38936258842351751,
      0.37569005776712727, 0.36197208003231424, 0.34821077150761626,
      0.33440825300183, 0.32056664936119672, 0.30668808898540761,
      0.29277470334257549, 0.27882862648329487, 0.2648519945539427,
      0.25084694530934737, 0.23681561762497277, 0.22276015100872543,
      0.20868268511256788, 0.19458535924403123, 0.18047031187779838,
      0.16633968016747519, 0.15219559945769295, 0.13804020279668483,
      0.12387562044946052, 0.10970397941174871, 0.095527402924791879,
      0.081348009991184467, 0.067167914891859359, 0.052989226704373373,
      0.038814048822621981, 0.02464447847811866, 0.010482606262979179,
      -0.0036694843452415513, -0.017809717456765621, -0.03193602524067371,
      -0.04604634839376022, -0.060138636607000952, -0.074210849029518133,
      -0.088260954729906582, -0.10228693315477874, -0.11628677458441161,
      -0.13025848058536363, -0.14420006445992523, -0.1581095516922823,
      -0.17198498039125718, -0.18582440172950893, -0.19962588037906889,
      -0.2133874949430809, -0.2271073383836244, -0.24078351844548826,
      -0.25441415807582146, -0.26799739583946336, -0.28153138632990332,
      -0.295014300575717, -0.30844432644238207, -0.321819669029337,
      -0.33513855106220136, -0.34839921327999884, -0.36159991481734211,
      -0.37473893358139909, -0.38781456662357805, -0.40082513050580604,
      -0.41376896166131966, -0.42664441674982989, -0.43944987300700167,
      -0.45218372858810407, -0.46484440290579049, -0.47743033696184872,
      -0.48993999367288665, -0.50237185818981422, -0.51472443821106806,
      -0.52699626428947266, -0.53918589013264651, -0.55129189289688918,
      -0.56331287347444126, -0.57524745677407152, -0.58709429199487428,
      -0.5988520528932274, -0.61051943804282915, -0.62209517108774359,
      -0.63357800098836969, -0.64496670226030528, -0.65626007520598251,
      -0.66745694613907713, -0.678556167601571, -0.68955661857344863,
      -0.70045720467494965, -0.71125685836134189, -0.72195453911013541,
      -0.73254923360072577, -0.74303995588636884, -0.75342574755850311,
      -0.76370567790331889, -0.77387884405057072, -0.78394437111458037,
      -0.79390141232739853, -0.80374914916409324, -0.813486791460123,
      -0.82311357752079373, -0.83262877422273585, -0.84203167710740456,
      -0.8513216104665835, -0.8604979274198481, -0.869560009984002,
      -0.87850726913445187, -0.88733914485852472, -0.89605510620069539,
      -0.90465465129975764, -0.91313730741789378, -0.92150263096165674,
      -0.92975020749488135, -0.93787965174350552, -0.94589060759231725,
      -0.953782748073637, -0.96155577534794678, -0.9692094206764672,
      -0.976743444385728, -0.9841576358241142, -0.99145181331043208,
      -0.99862582407450784, -1.0056795441898625, -1.0126128784984583,
      -1.0194257605275827, -1.0261181523988789, -1.0326900447295628,
      -1.0391414565258836, -1.0454724350688365, -1.0516830557921928,
      -1.0577734221528816, -1.0637436654937871, -1.0695939448989835,
      -1.0753244470414836, -1.0809353860235391, -1.086427003209568,
      -1.0917995670517469, -1.0970533729083407, -1.1021887428548331,
      -1.1072060254879146, -1.112105595722416, -1.1168878545812309,
      -1.1215532289783094, -1.1261021714948163, -1.1305351601484943,
      -1.1348526981563392, -1.1390553136906556, -1.1431435596285731,
      -1.1471180132951178, -1.1509792761999076, -1.1547279737675833,
      -1.1583647550620479, -1.1618902925045989, -1.1653052815860796,
      -1.168610440573109, -1.1718065102085089, -1.1748942534060172,
      -1.1778744549394005, -1.1807479211260454, -1.1835154795051723,
      -1.1861779785107249, -1.1887362871390847, -1.19119129461171,
      -1.1935439100327909, -1.1957950620420594, -1.1979456984628476,
      -1.1999967859455141, -1.2019493096063634, -1.2038042726621614,
      -1.2055626960603847, -1.2072256181052934, -1.2087940940799813,
      -1.2102691958645111, -1.2116520115502543, -1.2129436450505624,
      -1.2141452157079058, -1.215257857897587, -1.2162827206281832,
      -1.2172209671388132, -1.2180737744933896, -1.2188423331719616,
      -1.2195278466593042, -1.2201315310308569, -1.2206546145361727,
      -1.2210983371799842, -1.2214639503010498, -1.2217527161488841,
      -1.221965907458531, -1.2221048070235021, -1.2221707072670247,
      -1.2221649098117184, -1.2220887250478718, -1.2219434717004127,
      -1.2217304763947492, -1.2214510732215831, -1.2211066033008673,
      -1.2206984143450179, -1.2202278602215395, -1.2196963005151851,
      -1.2191051000897937, -1.2184556286499573, -1.2177492603026414,
      -1.2169873731188792, -1.2161713486957302, -1.2153025717185817,
      -1.2143824295239685, -1.2134123116630324, -1.2123936094657646,
      -1.2113277156061468, -1.2102160236683819, -1.2090599277142677,
      -1.2078608218519122, -1.2066200998059158, -1.205339154489119,
      -1.2040193775760852, -1.2026621590784383, -1.201268886922179,
      -1.1998409465271243, -1.198379720388584, -1.1968865876614221,
      -1.1953629237466159, -1.1938100998804382, -1.1922294827264148,
      -1.1906224339701408, -1.1889903099171155, -1.1873344610937013,
      -1.1856562318513333, -1.1839569599740969, -1.1822379762897974,
      -1.1805006042846347, -1.1787461597216027, -1.1769759502627313,
      -1.1751912750952778, -1.1733934245619839, -1.1715836797955148,
      -1.1697633123571811, -1.1679335838800535, -1.1660957457165839,
      -1.1642510385908347, -1.1624006922554024, -1.1605459251531729,
      -1.158687944083975, -1.1568279438762472, -1.1549671070638055,
      -1.15310660356782, -1.1512475903840762, -1.1493912112756293,
      -1.14753859647092, -1.1456908623674613, -1.1438491112411626,
      -1.1420144309613944, -1.1401878947118511, -1.138370560717304,
      -1.1365634719763293, -1.1347676560000772, -1.1329841245571437,
      -1.1312138734246422, -1.1294578821455237, -1.1277171137922173,
      -1.1259925147366621, -1.1242850144267817, -1.1225955251694657,
      -1.120924941920129, -1.1192741420788768, -1.1176439852933557,
      -1.1160353132683274, -1.11444894958202, -1.1128856995092951,
      -1.1113463498516827, -1.1098316687743277, -1.1083424056498785,
      -1.1068792909093568, -1.1054430359000509, -1.1040343327504571,
      -1.1026538542423039, -1.1013022536896779, -1.0999801648252887,
      -1.0986882016938828, -1.0974269585528449, -1.096197009779978,
      -1.0949989097884982, -1.0938331929492573, -1.0927003735201875,
      -1.0916009455829916, -1.0905353829870754, -1.089504139300733,
      -1.0885076477695754, -1.0875463212822138, -1.0866205523431769,
      -1.0857307130530742, -1.0848771550959766, -1.0840602097340251,
      -1.0832801878092242, -1.0825373797524407, -1.0818320555995475,
      -1.0811644650147354, -1.0805348373209249, -1.0799433815372863,
      -1.0793902864238241, -1.0788757205329975, -1.0783998322683435,
      -1.0779627499500688, -1.0775645818875659, -1.0772054164588332,
      -1.0768853221967249, -1.076604347882016, -1.0763625226432156,
      -1.0761598560630974, -1.0759963382918647, -1.0758719401669423,
      -1.0757866133392959, -1.0757402904062434, -1.0757328850506949,
      -1.07576429218676, -1.075834388111647, -1.0759430306638078,
      -1.0760900593872367, -1.0762752957018715, -1.0764985430800125,
      -1.0767595872286968, -1.077058196277928, -1.0773941209747151,
      -1.0777670948828106, -1.0781768345880895, -1.0786230399094614,
      -1.0791053941152506, -1.079623564144947, -1.0801772008362376,
      -1.0807659391572271, -1.0813893984437595, -1.0820471826417426,
      -1.08273888055438, -1.0834640660942088, -1.0842222985398546,
      -1.0850131227973829, -1.0858360696661744, -1.08669065610919,
      -1.0875763855275347, -1.0884927480392175, -1.0894392207619923,
      -1.0904152681001693, -1.0914203420352913, -1.0924538824205625,
      -1.0935153172789136, -1.0946040631045926, -1.0957195251681604,
      -1.096861097824783, -1.0980281648256991, -1.0992200996327388,
      -1.1004362657357845, -1.1016760169730513, -1.1029386978540536,
      -1.1042236438851525, -1.1055301818975571, -1.1068576303776549,
      -1.1082052997995266, -1.1095724929595716, -1.1109585053130586,
      -1.1123626253125214, -1.1137841347478485, -1.1152223090879494,
      -1.1166764178238631, -1.1181457248131943, -1.1196294886257305,
      -1.1211269628901268, -1.1226373966415235, -1.1241600346699723,
      -1.1256941178695263, -1.127238883587891, -1.1287935659764736,
      -1.1303573963407496, -1.1319296034907524, -1.1335094140916164,
      -1.1350960530140113, -1.1366887436843451, -1.1382867084346158,
      -1.1398891688517665, -1.1414953461264357, -1.1431044614009576,
      -1.1447157361164895, -1.1463283923591476, -1.1479416532050126,
      -1.1495547430638882, -1.1511668880216734, -1.1527773161812427,
      -1.1543852580016913, -1.155989946635839, -1.1575906182658406,
      -1.1591865124368212, -1.1607768723883816, -1.1623609453838646,
      -1.1639379830372616, -1.1655072416376444, -1.1670679824709975,
      -1.1686194721393368, -1.1701609828769988, -1.1716917928639841,
      -1.1732111865362453, -1.1747184548928002, -1.1762128957995621,
      -1.1776938142897782, -1.1791605228609685, -1.1806123417682437,
      -1.1820485993139254, -1.1834686321333252, -1.1848717854766138,
      -1.186257413486655, -1.1876248794727158, -1.188973556179947,
      -1.1903028260545432, -1.1916120815044831, -1.1929007251557462,
      -1.1941681701039373, -1.1954138401612022, -1.196637170098358,
      -1.1978376058821523, -1.1990146049075585, -1.2001676362250309,
      -1.2012961807626223, -1.202399731542918, -1.2034777938946568,
      -1.2045298856590094, -1.2055555373904194, -1.2065542925519286,
      -1.2075257077049315, -1.2084693526932788, -1.2093848108216663,
      -1.2102716790282517, -1.21112956805143, -1.2119581025907031,
      -1.2127569214615992, -1.2135256777445729, -1.2142640389278392,
      -1.2149716870441005, -1.215648318801078, -1.216293645705858,
      -1.2169073941829625, -1.2174893056861171, -1.218039136803684,
      -1.218556659357706, -1.2190416604965457, -1.2194939427810574,
      -1.2199133242643003, -1.2202996385647227, -1.2206527349328229,
      -1.2209724783112479, -1.2212587493883069, -1.2215114446448885,
      -1.2217304763947585, -1.2219157728182286, -1.2220672779891755,
      -1.2221849518954113, -1.2222687704523918, -1.2223187255102563,
      -1.2223348248542019, -1.2223170921981845, -1.2222655671719618,
      -1.2221803053014622, -1.2220613779825109, -1.2219088724479021,
      -1.2217228917278402, -1.2215035546037645, -1.2212509955555657,
      -1.2209653647022223, -1.2206468277358744, -1.2202955658493537,
      -1.2199117756572124, -1.2194956691102519, -1.2190474734036076,
      -1.2185674308784185, -1.2180557989170933, -1.2175128498322478,
      -1.2169388707493258, -1.216334163482951, -1.2156990444070721,
      -1.2150338443189157, -1.2143389082968228, -1.213614595552021,
      -1.2128612792743589, -1.2120793464720814, -1.2112691978057053,
      -1.210431247416039, -1.2095659227464186, -1.2086736643592266,
      -1.2077549257467486, -1.2068101731364491, -1.2058398852907279,
      -1.2048445533012317, -1.2038246803777963, -1.2027807816320961,
      -1.2017133838560738, -1.2006230252952341, -1.1995102554168919,
      -1.1983756346734422, -1.197219734260736, -1.1960431358716903,
      -1.1948464314451483, -1.1936302229101539, -1.1923951219256894,
      -1.1911417496159804, -1.1898707363014678, -1.1885827212255475,
      -1.1872783522771628, -1.185958285709366, -1.1846231858539398,
      -1.1832737248321825, -1.1819105822619833, -1.1805344449612556,
      -1.1791460066478596, -1.1777459676361421, -1.1763350345301484,
      -1.1749139199136851, -1.1734833420372841, -1.1720440245022286,
      -1.170596695941738, -1.1691420896994156, -1.1676809435050977,
      -1.1662139991482157, -1.1647420021487787, -1.1632657014261145,
      -1.1617858489654758, -1.1603031994826383, -1.1588185100866273,
      -1.157332539940656, -1.1558460499214558, -1.154359802277078,
      -1.1528745602833035, -1.1513910878988103, -1.1499101494191881,
      -1.1484325091299523, -1.1469589309586836, -1.1454901781264033,
      -1.1440270127983356, -1.1425701957341778, -1.1411204859379775,
      -1.1396786403078145, -1.1382454132853426, -1.1368215565053603,
      -1.1354078184455485, -1.1340049440764675, -1.1326136745119786,
      -1.1312347466601982, -1.1298688928751337, -1.1285168406091113,
      -1.1271793120661224, -1.1258570238562504, -1.1245506866512704,
      -1.1232610048415581, -1.1219886761944675, -1.1207343915142467,
      -1.1194988343036809, -1.1182826804275479, -1.1170865977780284,
      -1.1159112459421927, -1.1147572758716979, -1.1136253295548009,
      -1.1125160396908433, -1.111430029367287, -1.1103679117394645,
      -1.1093302897131507, -1.1083177556300634, -1.1073308909564241,
      -1.1063702659747185, -1.1054364394787191, -1.104529958471959,
      -1.1036513578697047, -1.1028011602045904, -1.1019798753360124,
      -1.1011880001633811, -1.1004260183433596, -1.0996944000112066,
      -1.098993601506296, -1.0983240651019748, -1.0976862187397947,
      -1.097080475768301, -1.0965072346864237, -1.0959668788915864,
      -1.0954597764326481, -1.094986279767773, -1.0945467255272905,
      -1.0941414342817033, -1.0937707103148777, -1.0934348414025423,
      -1.0931340985961815, -1.0928687360123936, -1.0926389906278209,
      -1.0924450820797382, -1.0922872124723466, -1.0921655661889214,
      -1.0920803097098057, -1.0920315914364156, -1.092019541521269,
      -1.092044271704133, -1.0921058751543671, -1.0922044263195325,
      -1.0923399807803098, -1.09251257511183, -1.0927222267514394,
      -1.092968933872994, -1.0932526752677332, -1.0935734102317616,
      -1.0939310784602498, -1.0943255999483372, -1.09475687489885,
      -1.0952247836368467, -1.0957291865310359, -1.0962699239221256,
      -1.0968468160581462, -1.0974596630367519, -1.0981082447545933,
      -1.0987923208637322, -1.099511630735184, -1.10026589342959,
      -1.1010548076750335, -1.1018780518520646, -1.1027352839859201,
      -1.103626141745963, -1.1045502424523816, -1.1055071830901311,
      -1.1064965403301548, -1.1075178705578881, -1.1085707099090345,
      -1.1096545743126456, -1.1107689595415062, -1.111913341269781,
      -1.1130871751379932, -1.1142898968252568, -1.115520922128808,
      -1.1167796470508027, -1.1180654478923655, -1.1193776813548857,
      -1.120715684648544, -1.1220787756080275, -1.1234662528154542,
      -1.1248773957304299, -1.1263114648272525, -1.1277677017392218,
      -1.1292453294100044, -1.1307435522520484, -1.1322615563119982,
      -1.1337985094430532, -1.1353535614842765, -1.1369258444467421,
      -1.1385144727065364, -1.1401185432045489, -1.1417371356529549,
      -1.1433693127484124, -1.145014120391874, -1.1466705879149404,
      -1.1483377283127472, -1.1500145384832754, -1.1516999994730419,
      -1.1533930767291154, -1.155092720357352, -1.1567978653868176,
      -1.1585074320403126, -1.160220326010903, -1.1619354387444094,
      -1.1636516477277659, -1.1653678167831552, -1.1670827963678525,
      -1.1687954238796814, -1.1705045239680074, -1.1722089088501613,
      -1.1739073786332166, -1.1755987216410346, -1.1772817147464412,
      -1.1789551237085019, -1.1806177035147474, -1.1822681987282582,
      -1.1839053438395259, -1.1855278636229754, -1.1871344734980245,
      -1.1887238798946216, -1.1902947806230888, -1.1918458652482204,
      -1.193375815467496, -1.1948833054932846, -1.1963670024389463,
      -1.1978255667087276, -1.199257652391275, -1.2006619076567249,
      -1.2020369751571884, -1.203381492430539, -1.2046940923073948,
      -1.205973403321108, -1.2072180501207295, -1.2084266538867441,
      -1.209597832749489, -1.2107302022101143, -1.2118223755639694,
      -1.2128729643262661, -1.2138805786598963, -1.2148438278052889,
      -1.2157613205121498, -1.2166316654729454, -1.2174534717580427,
      -1.218225349252319, -1.2189459090931218, -1.2196137641094627,
      -1.2202275292622904, -1.220785822085694, -1.2212872631289404,
      -1.2217304763991585, -1.2221140898045639, -1.2224367355980874,
      -1.2226970508212402, -1.2228936777480983, -1.2230252643292856,
      -1.2230904646357519, -1.2230879393022918, -1.2230163559705878,
      -1.2228743897316876, -1.2226607235677605, -1.2223740487929788,
      -1.2220130654934174, -1.2215764829657905, -1.2210630201549315,
      -1.2204714060898425, -1.2198003803181825, -1.2190486933390738,
      -1.2182151070340688, -1.2172983950961369, -1.2162973434565665,
      -1.2152107507095986, -1.2140374285347033, -1.212776202116324,
      -1.211425910560985, -1.2099854073115957, -1.2084535605588775,
      -1.2068292536496894, -1.2051113854922217, -1.203298870957852,
      -1.2013906412795492, -1.1993856444467541, -1.1972828455965061,
      -1.1950812274007825, -1.1927797904498758, -1.1903775536316921,
      -1.1878735545068642, -1.1852668496795153, -1.1825565151636259,
      -1.1797416467447877, -1.176821360337317, -1.1737947923365575,
      -1.1706610999662486, -1.1674194616209124, -1.1640690772030506,
      -1.1606091684551167, -1.1570389792861315, -1.1533577760928062,
      -1.1495648480751002, -1.1456595075461034, -1.1416410902361274,
      -1.1375089555908933, -1.1332624870637655, -1.1289010924018774,
      -1.1244242039260697, -1.1198312788045803, -1.1151217993203257,
      -1.1102952731317723, -1.10535123352721, -1.10028923967241,
      -1.0951088768515842, -1.0898097567015015, -1.0843915174387513,
      -1.0788538240800114, -1.07319636865532, -1.0674188704142011,
      -1.0615210760245886, -1.0555027597645479, -1.049363723706616,
      -1.0431037978947697, -1.0367228405139572, -1.0302207380520725,
      -1.0235974054544004, -1.0168527862703809, -1.0099868527927272,
      -1.0029996061887669, -0.99589107662402254, -0.98866132337793167,
      -0.98131043495170434, -0.97383852916823754, -0.96624575326405571,
      -0.95853228397326973, -0.95069832760349848, -0.942744120103661,
      -0.93466992712373642, -0.92647604406634954, -0.91816279613019969,
      -0.90973053834530992, -0.90117965560008284, -0.89251056266012063,
      -0.88372370417881307, -0.87481955469966821, -0.8657986186503851,
      -0.85666143032866116, -0.84740855387970926, -0.8380405832654837,
      -0.82855814222567348, -0.81896188423036276, -0.80925249242441422,
      -0.79943067956364389, -0.7894971879426631, -0.77945278931450335,
      -0.769298284802013, -0.75903450480102475, -0.74866230887532093,
      -0.73818258564342043, -0.7275962526572145, -0.71690425627249965,
      -0.70610757151134984, -0.69520720191647256, -0.68420417939753286,
      -0.67309956406944815, -0.66189444408274023, -0.65058993544596266,
      -0.639187181840284, -0.62768735442620527, -0.6160916516424898,
      -0.60440129899742112, -0.592617548852333, -0.58074168019750672,
      -0.56877499842056511, -0.55671883506730446, -0.54457454759512058,
      -0.53234351911902178, -0.52002715815036749, -0.507626898328339,
      -0.49514419814424865, -0.48258054065872968, -0.46993743321195691,
      -0.45721640712685446, -0.44441901740546363, -0.43154684241853736,
      -0.41860148358844046, -0.40558456506536816, -0.39249773339711758,
      -0.379342657192378, -0.366121026777679, -0.35283455384805851,
      -0.33948497111162496, -0.32607403192801354, -0.31260350994089231,
      -0.29907519870459159, -0.2854909113049966, -0.2718524799747627,
      -0.25816175570297828, -0.24442060783938402, -0.23063092369328245,
      -0.21679460812718945, -0.20291358314535374, -0.18898978747735651,
      -0.17502517615675062, -0.16102172009493593, -0.14698140565043963,
      -0.13290623419361627, -0.11879822166695303, -0.10465939814107977,
      -0.0904918073666028, -0.07629750632196905, -0.06207856475729142,
      -0.047837064734471114, -0.033575100163666181, -0.019294776336169529,
      -0.0049982094539169492, 0.0093124738442809871, 0.023635136959636004,
      0.037967633813301704, 0.052307809329197943, 0.0666534999194936,
      0.08100253397276895, 0.095352732344644892, 0.10970190885069246,
      0.12404787076158025, 0.138388419300276, 0.15272135014116936,
      0.16704445391095937, 0.1813555166912024, 0.19565232052236003,
      0.20993264390922042, 0.22419426232749634, 0.2384349487315589,
      0.2526524740631137, 0.26684460776063024, 0.28100911826943592,
      0.29514377355241139, 0.30924634160094727, 0.32331459094620135,
      0.33734629117043546, 0.35133921341830965, 0.36529113090798032,
      0.37919981944185288, 0.39306305791688961, 0.40687862883430059,
      0.42064431880845232, 0.43435791907492011, 0.44801722599749,
      0.46162004157398828, 0.47516417394079236, 0.4886474378758946,
      0.50206765530041531, 0.51542265577830793, 0.52871027701427331,
      0.54192836534966626, 0.55507477625622426, 0.56814737482755728,
      0.5811440362682444, 0.594062646380369, 0.60690110204741354,
      0.61965731171528438, 0.63232919587051384, 0.64491468751532177,
      0.6574117326394876, 0.66981829068894028, 0.68213233503090109,
      0.694351853415429, 0.7064748484332859, 0.71849933796998722,
      0.73042335565593275, 0.742244951312434, 0.75396219139359244,
      0.76557315942389348, 0.77707595643135841, 0.78846870137617142,
      0.79974953157468565, 0.81091660311866587, 0.82196809128964488,
      0.83290219096834051, 0.84371711703896535, 0.85441110478836746,
      0.86498241029984391, 0.87542931084159592, 0.88575010524968989,
      0.8959431143053862, 0.90600668110677918, 0.915939171434712,
      0.92573897411271766, 0.93540450136103925, 0.94493418914456428,
      0.95432649751462306, 0.96357991094452622, 0.97269293865877215,
      0.98166411495586181, 0.99049199952463163, 0.99917517775397946,
      1.0077122610359788, 1.0161018870622736, 1.024342720113653,
      1.0324334513427846, 1.0403727990500049, 1.0481595089521258,
      1.0557923544441592, 1.0632701368539168, 1.0705916856894544,
      1.0777558588792311, 1.0847615430049893, 1.0916076535272929,
      1.0982931350036447, 1.1048169612991603, 1.1111781357897264,
      1.1173756915576447, 1.123408691579671, 1.1292762289074132,
      1.1349774268400907, 1.1405114390895938, 1.1458774499377888,
      1.1510746743860674, 1.1561023582971215, 1.1609597785288754,
      1.1656462430605892, 1.1701610911110891, 1.1745036932491271,
      1.1786734514958281, 1.1826697994192212, 1.1864922022208497,
      1.1901401568144534, 1.193613191896673, 1.1969108680098397,
      1.2000327775967894, 1.2029785450477271, 1.2057478267391457,
      1.2083403110647806, 1.2107557184586324, 1.212993801410061,
      1.2150543444709274, 1.2169371642548665, 1.2186421094286248,
      1.2201690606955462, 1.2215179307711836, 1.2226886643510875,
      1.2236812380707736, 1.2244956604579009, 1.2251319718767077,
      1.225590244464712, 1.2258705820617137, 1.2259731201311515,
      1.2258980256738348, 1.2256454971340875, 1.225215764298365,
      1.2246090881863718, 1.2238257609347158, 1.2228661056731904,
      1.2217304763936754, 1.2204192578117516, 1.2189328652210767,
      1.2172717443405583, 1.215436371154397, 1.2134272517450708,
      1.2112449221192889, 1.208889948027025, 1.2063629247736398,
      1.2036644770252114, 1.2007952586071238, 1.197755952295964,
      1.1945472696048338, 1.1911699505621318, 1.1876247634838859,
      1.1839125047397181, 1.1800339985125086, 1.17599009655186,
      1.1717816779214345, 1.1674096487402272, 1.162874941917919,
      1.1581785168843273, 1.1533213593130967, 1.1483044808396878,
      1.1431289187737808, 1.1377957358061557, 1.132306019710192,
      1.1266608830380176, 1.120861462811481, 1.1149089202079787,
      1.1088044402412631, 1.1025492314373644, 1.096144525505657,
      1.0895915770052502, 1.0828916630067438, 1.0760460827495109,
      1.0690561572945623, 1.0619232291731246, 1.0546486620310704,
      1.0472338402692289, 1.039680168679793, 1.0319890720788281,
      1.0241619949350824, 1.0162004009951564, 1.0081057729051628,
      0.9998796118289911, 0.99152343706330892, 0.98303878564937519,
      0.97442721198179849, 0.96569028741440932, 0.95682959986325167,
      0.94784675340693325, 0.93874336788435464, 0.929521078490011,
      0.9201815353669246, 0.91072640319735587, 0.90115736079144282,
      0.89147610067379668, 0.881684328668302, 0.87178376348110387,
      0.8617761362820312, 0.85166319028447657, 0.84144668032389447,
      0.831128372435059, 0.82071004342815523, 0.81019348046386819,
      0.79958048062753018, 0.78887285050254452, 0.77807240574309833,
      0.76718097064633628, 0.756200377724138, 0.74513246727456828,
      0.73397908695315339, 0.72274209134406764, 0.71142334153141051,
      0.70002470467059885, 0.68854805356011306, 0.67699526621356543,
      0.66536822543236884, 0.65366881837898039, 0.64189893615090543,
      0.630060473355606, 0.61815532768632242, 0.60618539949905126,
      0.5941525913906629, 0.58205880777840224, 0.56990595448075554,
      0.55769593829987429, 0.54543066660567918, 0.5331120469216345,
      0.52074198651249082, 0.50832239197389373, 0.49585516882412989,
      0.48334222109803482, 0.47078545094315888, 0.4581867582183321,
      0.4455480400947387, 0.43287119065952967, 0.42015810052212688,
      0.40741065642335328, 0.39463074084736804, 0.38182023163664058,
      0.36898100160994152, 0.35611491818352758, 0.34322384299555575,
      0.33030963153383136, 0.31737413276702831, 0.30441918877935853,
      0.29144663440891544, 0.27845829688963397, 0.26545599549709442,
      0.25244154119811257, 0.23941673630429092, 0.22638337412958778,
      0.21334323865195121, 0.20029810417914923, 0.18724973501877459,
      0.17419988515264634, 0.16115029791551966, 0.14810270567825254,
      0.13505882953553541, 0.12202037899815241, 0.10898905168992148,
      0.095966533049309938, 0.082954496035863981, 0.069954600841409226,
      0.056968494606213393, 0.0439978111399925, 0.031044170648016234,
      0.018109179462184571, 0.0051944297772140435, -0.0076985006079771795,
      -0.020568048543774586, -0.033412665778056828, -0.046230819199168174,
      -0.059020991073512545, -0.071781679277821489, -0.08451139752604242,
      -0.097208675590710142, -0.10987205951895476, -0.12250011184291822,
      -0.13509141178469741, -0.14764455545570077, -0.16015815605040917,
      -0.17263084403455864, -0.18506126732767131, -0.19744809147989406,
      -0.20978999984321789, -0.22208569373699788, -0.23433389260770482,
      -0.24653333418303755, -0.25868277462023143, -0.27078098864867606,
      -0.2828267697067347, -0.29481893007283794, -0.306756300990804,
      -0.31863773278937468, -0.33046209499602325, -0.34222827644493997,
      -0.35393518537932056, -0.36558174954781897, -0.3771669162953149,
      -0.38868965264789984, -0.40014894539211965, -0.41154380114853212,
      -0.42287324643948676, -0.43413632775129585, -0.44533211159062974,
      -0.456459684535315, -0.46751815327949259, -0.47850664467309967,
      -0.489424305755803, -0.5002703037853462, -0.51104382626035294,
      -0.52174408093759694, -0.532370295843817, -0.54292171928202093,
      -0.5533976198324434, -0.56379728634802573, -0.57412002794460326,
      -0.58436517398577748, -0.59453207406245068, -0.60462009796720761,
      -0.61462863566342485, -0.62455709724928377, -0.63440491291664447,
      -0.64417153290486717, -0.65385642744963435, -0.66345908672677445,
      -0.67297902079121075, -0.68241575951100708, -0.69176885249663633,
      -0.70103786902546628, -0.71022239796155728, -0.719322047670811,
      -0.72833644593153712, -0.73726523984046077, -0.74610809571429759,
      -0.754864698986916, -0.76353475410210669, -0.77211798440212853,
      -0.780614132011997, -0.78902295771962461, -0.79734424085187294,
      -0.80557777914658335, -0.813723388620656, -0.82178090343422949,
      -0.82975017575106946, -0.83763107559516459, -0.84542349070371725,
      -0.85312732637645183, -0.8607425053214528, -0.86826896749752969,
      -0.875706669953174, -0.88305558666225348, -0.89031570835641649,
      -0.89748704235440724, -0.90456961238823752, -0.91156345842638886,
      -0.91846863649410149, -0.92528521849077372, -0.932013292004629,
      -0.93865296012468047, -0.94520434125008812, -0.95166756889697091,
      -0.95804279150281035, -0.96433017222841533, -0.9705298887576761,
      -0.97664213309504211, -0.98266711136091189, -0.988605043584985,
      -0.99445616349760169, -1.0002207183192513, -1.0058989685482589,
      -1.0114911877467432, -1.0169976623249621, -1.0224186913240705,
      -1.0277545861974464, -1.033005670590587, -1.0381722801197186,
      -1.0432547621491641, -1.0482534755675841, -1.0531687905631306,
      -1.0580010883976327, -1.0627507611798703, -1.0674182116380386,
      -1.0720038528914535, -1.0765081082216077, -1.0809314108426533,
      -1.0852742036713576, -1.0895369390966652, -1.0937200787488972,
      -1.097824093268694, -1.1018494620757591, -1.1057966731375213,
      -1.1096662227377296, -1.1134586152451018, -1.1171743628821229,
      -1.1208139854939783, -1.1243780103178247, -1.1278669717523446,
      -1.1312814111277512, -1.1346218764762839, -1.1378889223032422,
      -1.1410831093586808, -1.1442050044097776, -1.1472551800140067,
      -1.1502342142931341, -1.1531426907081184, -1.1559811978350145,
      -1.1587503291419028, -1.1614506827669269, -1.1640828612975165,
      -1.1666474715508501, -1.1691451243556104, -1.1715764343351143,
      -1.1739420196918573, -1.176242501993557, -1.178478505960729,
      -1.1806506592558745, -1.182759592274325, -1.1848059379368006,
      -1.1867903314837478, -1.1887134102714922, -1.1905758135702809,
      -1.1923781823642381, -1.1941211591533343, -1.1958053877573387,
      -1.1974315131218982, -1.1990001811267135, -1.2005120383958898,
      -1.2019677321105255, -1.2033679098235375, -1.2047132192768042,
      -1.2060043082206564, -1.2072418242357432, -1.2084264145573362,
      -1.2095587259020795, -1.2106394042972641, -1.2116690949126097,
      -1.2126484418946357, -1.2135780882036262, -1.2144586754532254,
      -1.2152908437527079, -1.21607523155193, -1.2168124754890075,
      -1.2175032102407468, -1.2181480683758359, -1.2187476802108441,
      -1.2193026736690331, -1.2198136741420207, -1.2202813043542891,
      -1.2207061842305906, -1.2210889307662434, -1.2214301579003339,
      -1.2217304763918737, -1.2219904936988661, -1.2222108138603609,
      -1.2223920373814499, -1.2225347611212647, -1.2226395781839379,
      -1.2227070778125704, -1.2227378452862021, -1.2227324618197772,
      -1.2226915044671209, -1.2226155460269381, -1.2225051549518062,
      -1.222360895260201, -1.2221833264515147, -1.2219730034240992,
      -1.2217304763963048, -1.2214562908305231, -1.2211509873602289,
      -1.2208151017200011, -1.22044916467853, -1.2200537019745967,
      -1.2196292342560024, -1.2191762770214569, -1.2186953405653906,
      -1.2181869299257058, -1.2176515448344032, -1.2170896796711372,
      -1.216501823419615, -1.2158884596268547, -1.2152500663652919,
      -1.2145871161976909, -1.2139000761448437, -1.2131894076560603,
      -1.2124555665823815, -1.2116990031525381, -1.210920161951587,
      -1.2101194819022461, -1.2092973962488438, -1.2084543325439063,
      -1.2075907126373322, -1.2067069526681067, -1.2058034630585703,
      -1.2048806485111638, -1.2039389080076415, -1.2029786348107188,
      -1.2020002164681145, -1.201004034818959, -1.1999904660025176,
      -1.1989598804692156, -1.197912642993922, -1.1968491126914276,
      -1.1957696430341243, -1.1946745818718134, -1.1935642714536154,
      -1.1924390484519332, -1.1912992439884489, -1.1901451836620882,
      -1.1889771875789159, -1.1877955703839473, -1.1866006412947789,
      -1.1853927041370593, -1.1841720573817047, -1.1829389941838369,
      -1.181693802423404, -1.1804367647474283, -1.1791681586138387,
      -1.1778882563368378, -1.1765973251337833, -1.1752956271734869,
      -1.173983419625944, -1.1726609547133904, -1.1713284797626948,
      -1.1699862372589809, -1.1686344649004927, -1.1672733956545953,
      -1.1659032578149187, -1.1645242750595541, -1.1631366665102736,
      -1.1617406467927358, -1.1603364260975977, -1.1589242102425112,
      -1.1575042007349639, -1.1560765948358678, -1.1546415856239092,
      -1.1531993620605678, -1.1517501090557807, -1.1502940075341836,
      -1.1488312345019023, -1.1473619631138288, -1.1458863627413554,
      -1.1444045990404803, -1.1429168340203026, -1.1414232261117776,
      -1.1399239302367625, -1.1384190978772568, -1.1369088771448017,
      -1.1353934128500192, -1.1338728465721937, -1.1323473167289066,
      -1.1308169586456385, -1.1292819046253169, -1.1277422840177442,
      -1.1261982232889014, -1.1246498460900247, -1.1230972733264719,
      -1.1215406232263065, -1.1199800114085385, -1.1184155509510421,
      -1.1168473524580305, -1.1152755241271151, -1.11370017181587,
      -1.1121213991078753, -1.1105393073782, -1.1089539958582912,
      -1.1073655617002092, -1.105774100040219, -1.1041797040616435,
      -1.1025824650569791, -1.1009824724892534, -1.0993798140525262,
      -1.0977745757315951, -1.0961668418607713, -1.0945566951817725,
      -1.0929442169006731, -1.0913294867438608, -1.0897125830130077,
      -1.0880935826389972, -1.086472561234799, -1.0848495931472446,
      -1.0832247515077071, -1.081598108281602, -1.0799697343167731,
      -1.0783396993906456, -1.0767080722561804, -1.0750749206866106,
      -1.0734403115188793, -1.071804310695841, -1.0701669833071412,
      -1.0685283936287768, -1.0668886051613382, -1.065247680666886,
      -1.06360568220445, -1.061962671164169, -1.0603187083000041,
      -1.0586738537610616, -1.0570281671214736, -1.0553817074088423,
      -1.0537345331312538, -1.0520867023028051, -1.0504382724676913,
      -1.0487893007227929, -1.0471398437387949, -1.0454899577798158,
      -1.0438396987215368, -1.0421891220678223, -1.0405382829658647,
      -1.0388872362197914, -1.0372360363027882, -1.0355847373677087,
      -1.0339333932561576, -1.032282057506096, -1.0306307833579282,
      -1.0289796237590656, -1.0273286313670393, -1.0256778585510671,
      -1.0240273573921657, -1.0223771796817727, -1.0207273769188812,
      -1.0190780003057309, -1.0174291007420226, -1.0157807288176808,
      -1.0141329348042127, -1.0124857686445912, -1.0108392799417776,
      -1.009193517945802, -1.0075485315394792, -1.00590436922276,
      -1.0042610790957061, -1.0026187088401453, -1.0009773056999975,
      -0.99933691646030354, -0.99769758742495929, -0.99605936439320375,
      -0.9944222926348405, -0.99278641686425617, -0.99115178121323644,
      -0.98951842920257715, -0.98788640371258873, -0.98625574695241824,
      -0.98462650042830957, -0.98299870491074892, -0.98137240040057139,
      -0.9797476260940432, -0.9781244203469347, -0.97650282063760874,
      -0.97488286352920039, -0.97326458463083754, -0.97164801855800675,
      -0.97003319889205009, -0.96842015813882687, -0.96680892768661109,
      -0.9651995377631879, -0.96359201739225175, -0.96198639434908639,
      -0.96038269511558416, -0.9587809448346476, -0.9571811672639704,
      -0.95558338472927251, -0.9539876180769965, -0.95239388662652646,
      -0.95080220812191563, -0.94921259868323749, -0.947625072757509,
      -0.94603964306928512, -0.94445632057094453, -0.94287511439267213,
      -0.94129603179224219, -0.93971907810455191, -0.93814425669103851,
      -0.93657156888893578, -0.93500101396044766, -0.93343258904188753,
      -0.93186628909278324, -0.93030210684501924, -0.92874003275204431,
      -0.92718005493816968, -0.92562215914802337, -0.92406632869617311,
      -0.92251254441696351, -0.92096078461462594, -0.91941102501366434,
      -0.91786323870958764, -0.91631739612000618, -0.91477346493613232,
      -0.91323141007475694, -0.91169119363067064, -0.91015277482964085,
      -0.90861610998193565, -0.907081152436457, -0.90554785253549352,
      -0.90401615757017073, -0.90248601173659115, -0.90095735609273175,
      -0.89943012851613124, -0.89790426366237863, -0.89637969292447894,
      -0.89485634439310058, -0.89333414281773826, -0.89181300956886911,
      -0.89029286260106355, -0.888773616417166, -0.88725518203350773,
      -0.88573746694623257, -0.88422037509875517, -0.88270380685037,
      -0.88118765894605844, -0.87967182448752779, -0.87815619290549274,
      -0.87664064993326307, -0.87512507758162683, -0.873609354115085,
      -0.8720933540294783, -0.87057694803098173, -0.869060003016563,
      -0.86754238205587664, -0.8660239443746427, -0.86450454533954457,
      -0.86298403644465194, -0.86146226529939551, -0.85993907561813931,
      -0.85841430721134337, -0.85688779597835263, -0.85535937390184535,
      -0.85382886904393607, -0.85229610554397628, -0.85076090361806178,
      -0.84922307956025378, -0.84768244574556983, -0.8461388106347093,
      -0.84459197878056813, -0.84304175083654753, -0.84148792356666346,
      -0.83993028985748253, -0.83836863873188627, -0.836802755364685,
      -0.83523242110008455, -0.83365741347102407, -0.83207750622038845,
      -0.830492469324107, -0.82890206901614161, -0.82730606781537663,
      -0.82570422455442449, -0.82409629441031884, -0.82248202893714972,
      -0.82086117610059683, -0.81923348031439913, -0.81759868247873235,
      -0.815956520020519, -0.81430672693566364, -0.81264903383319775,
      -0.81098316798135572, -0.80930885335556468, -0.80762581068833872,
      -0.80593375752109453, -0.80423240825785691, -0.80252147422086528,
      -0.80080066370806346, -0.79906968205247608, -0.79732823168344691,
      -0.79557601218973817, -0.79381272038448136, -0.79203805037195574,
      -0.790251693616199, -0.78845333901142189, -0.78664267295421153,
      -0.78481937941752178, -0.78298314002641656, -0.78113363413556491,
      -0.77927053890845077, -0.7773935293982992, -0.77550227863067578,
      -0.7735964576877683, -0.7716757357942895, -0.76973978040501267,
      -0.76778825729390587, -0.76582083064482265, -0.763837163143758,
      -0.76183691607260706, -0.759819749404433, -0.75778532190017911,
      -0.75573329120684729, -0.75366331395704877, -0.75157504586997115,
      -0.74946814185365451, -0.74734225610860883, -0.74519704223270167,
      -0.74303215332729955, -0.740847242104629, -0.73864196099630242,
      -0.73641596226302031, -0.734168898105342, -0.73190042077557826,
      -0.72961018269067834, -0.72729783654614111, -0.724963035430877,
      -0.72260543294299051, -0.72022468330645961, -0.71782044148861834,
      -0.71539236331850087, -0.71294010560587084, -0.71046332626104647,
      -0.70796168441533192, -0.70543484054212191, -0.70288245657858772,
      -0.70030419604789618, -0.69769972418194293, -0.69506870804453658,
      -0.69241081665499749, -0.6897257211121, -0.687013094718379,
      -0.684272613104665, -0.68150395435487032, -0.67870679913094434,
      -0.67588083079797345, -0.67302573554934764, -0.67014120253197951,
      -0.66722692397151717, -0.66428259529746, -0.66130791526823085,
      -0.65830258609601566, -0.65526631357147791, -0.6521988071881446,
      -0.64909978026653969, -0.645968950077941, -0.64280603796774083,
      -0.63961076947836681, -0.63638287447165709, -0.63312208725076291,
      -0.62982814668136422, -0.62650079631230426, -0.62313978449548046,
      -0.61974486450500943, -0.61631579465558917, -0.61285233842000642,
      -0.60935426454576269, -0.605821347170723, -0.60225336593782308,
      -0.59865010610866276, -0.59501135867608412, -0.59133692047553976,
      -0.58762659429532338, -0.58388018898552574, -0.58009751956574085,
      -0.57627840733141056, -0.572422679958809, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 2.7755575615628914E-17, -0.011321759566999802,
      -0.022642771987583694, -0.033961900037570575, -0.045278006578939808,
      -0.056589954778004027, -0.067896608323690183, -0.079196831645880927,
      -0.090489490133763811, -0.10177345035414148, -0.11304758026964858,
      -0.12431074945682917, -0.13556182932402217, -0.14679969332900428,
      -0.15802321719634235, -0.16923127913440172, -0.18042276005196367,
      -0.19159654377439889, -0.20275151725934859, -0.21388657081186255,
      -0.22500059829894328, -0.23609249736344837, -0.2471611696372987,
      -0.25820552095394378, -0.26922446156003627, -0.28021690632626239,
      -0.29118177495728187, -0.3021179922007286, -0.313024488055219,
      -0.32390019797732461, -0.33474406308745558, -0.34555503037460972,
      -0.35633205289993791, -0.36707408999907565, -0.37778010748319835,
      -0.38844907783874733, -0.39907998042578119, -0.40967180167490885,
      -0.42022353528275164, -0.43073418240589351, -0.44120275185327013,
      -0.4516282602769533, -0.46200973236128318, -0.47234620101030589,
      -0.48263670753347027, -0.49288030182953951, -0.50307604256867622,
      -0.51322299737265276, -0.52332024299314994, -0.53336686548809786,
      -0.54336196039601614, -0.55330463290831544, -0.56319399803951464,
      -0.57302918079533927, -0.58280931633865207, -0.59253355015318676,
      -0.60220103820503545, -0.611810947101859, -0.62136245424977776,
      -0.6308547480079072, -0.64028702784050051, -0.64965850446666062,
      -0.65896840000759016, -0.66821594813133844, -0.67740039419501341,
      -0.68652099538442679, -0.69557702085113338, -0.70456775184683818,
      -0.71349248185513237, -0.72235051672053341, -0.73114117477479246,
      -0.73986378696044164, -0.74851769695155357, -0.75710226127167679,
      -0.76561684940893027, -0.77406084392821717, -0.782433640580541,
      -0.79073464840939089, -0.79896328985417631, -0.80711900085067956,
      -0.8152012309285106, -0.82320944330553347, -0.831143114979245,
      -0.83900173681508461, -0.8467848136316517, -0.85449186428281365,
      -0.86212242173668086, -0.86967603315143471, -0.87715225994798462,
      -0.88455067787944386, -0.89187087709740109, -0.89911246221497665,
      -0.90627505236664674, -0.91335828126482066, -0.92036179725316014,
      -0.927285263356626, -0.93412835732824318, -0.9408907716925663,
      -0.94757221378585021, -0.95417240579289753, -0.96069108478058851,
      -0.967128002728083, -0.9734829265536814, -0.97975563813834843,
      -0.98594593434588451, -0.99205362703974864, -0.99807854309652544,
      -1.004020524416033, -1.0098794279280716, -1.0156551255958139,
      -1.0213475044158282, -1.0269564664147492, -1.032481928642585,
      -1.0379238231626671, -1.0432820970382513, -1.0485567123157644,
      -1.0537476460047117, -1.0588548900542403, -1.0638784513263739,
      -1.0688183515659186, -1.0736746273670588, -1.0784473301366344,
      -1.0831365260541295, -1.0877422960283698, -1.0922647356509385,
      -1.096703955146338, -1.1010600793188914, -1.105333247496409,
      -1.1095236134706354, -1.1136313454344855, -1.1176566259160858,
      -1.1215996517096511, -1.1254606338031945, -1.1292397973031016,
      -1.132937381355591, -1.1365536390650675, -1.1400888374094034,
      -1.1435432571521595, -1.1469171927517725, -1.1502109522677304,
      -1.1534248572637651, -1.1565592427080693, -1.1596144568705904,
      -1.1625908612174047, -1.1654888303021997, -1.168308751654914,
      -1.1710510256675322, -1.1737160654770842, -1.1763042968458748,
      -1.1788161580389667, -1.1812520996989531, -1.1836125847180503,
      -1.1858980881075465, -1.1881090968646257, -1.1902461098366179,
      -1.1923096375826985, -1.1943002022330698, -1.196218337345671,
      -1.1980645877604374, -1.1998395094511582, -1.20154366937496,
      -1.2031776453194618, -1.20474202574763, -1.2062374096403823,
      -1.2076644063369675, -1.2090236353731765, -1.2103157263174047,
      -1.2115413186046251, -1.2127010613683, -1.2137956132702794,
      -1.214825642328728, -1.2157918257441136, -1.2166948497233219,
      -1.2175354093019077, -1.2183142081645617, -1.2190319584638085,
      -1.2196893806370006, -1.2202872032216339, -1.2208261626690506,
      -1.2213070031565607, -1.2217304763980295, -1.2220973414529834,
      -1.2224083645342749, -1.2226643188143576, -1.2228659842302136,
      -1.2230141472869875, -1.2231096008603641, -1.2231531439977528,
      -1.2231455817183101, -1.223087724811863, -1.2229803896367684,
      -1.2228243979167763, -1.2226205765369231, -1.2223697573385155,
      -1.2220727769132635, -1.2217304763965924, -1.2213437012602002,
      -1.2209133011038971, -1.220440129446789, -1.2199250435178473,
      -1.219368904045913, -1.2187725750491998, -1.2181369236243194,
      -1.2174628197349129, -1.2167511359999081, -1.2160027474814721,
      -1.2152185314727049, -1.2143993672851163, -1.2135461360359499,
      -1.2126597204353915, -1.2117410045737218, -1.2107908737084621,
      -1.209810214051549, -1.2087999125566167, -1.2077608567064022,
      -1.2066939343003535, -1.2056000332424739, -1.2044800413294496,
      -1.2033348460391275, -1.2021653343193679, -1.200972392377343,
      -1.1997569054693189, -1.1985197576909665, -1.1972618317682653,
      -1.1959840088490268, -1.1946871682951052, -1.1933721874753265,
      -1.1920399415592005, -1.1906913033114479, -1.1893271428873939,
      -1.1879483276292824, -1.186555721863545, -1.1851501866990777,
      -1.1837325798265776, -1.182303755318963, -1.1808645634329502,
      -1.1794158504118084, -1.1779584582893499, -1.1764932246951938,
      -1.1750209826613531, -1.1735425604301717, -1.1720587812636842,
      -1.1705704632544032, -1.1690784191376076, -1.1675834561051563,
      -1.166086375620873, -1.1645879732375388, -1.1630890384155441,
      -1.1615903543432167, -1.1600926977588963, -1.1585968387747634,
      -1.1571035407024794, -1.1556135598806696, -1.1541276455042839,
      -1.1526465394558776, -1.1511709761388424, -1.1497016823126249,
      -1.1482393769299646, -1.1467847709761962, -1.1453385673106327,
      -1.1439014605100777, -1.1424741367144922, -1.1410572734748452,
      -1.1396515396031861, -1.138257595024968, -1.1368760906336437,
      -1.1355076681475751, -1.1341529599692837, -1.1328125890470551,
      -1.1314871687389467, -1.130177302679211, -1.1288835846471681,
      -1.1276065984385433, -1.126346917739308, -1.1251051060020387,
      -1.1238817163248218, -1.1226772913327197, -1.1214923630618348,
      -1.1203274528459823, -1.1191830712059896, -1.1180597177416534,
      -1.11695788102637, -1.1158780385044487, -1.1148206563911405,
      -1.1137861895753933, -1.1127750815253414, -1.1117877641965686,
      -1.1108246579431293, -1.1098861714313717, -1.108972701556556,
      -1.1080846333622933, -1.1072223399628103, -1.1063861824680552,
      -1.1055765099116579, -1.1047936591817473, -1.1040379549546442,
      -1.1033097096314353, -1.1026092232774336, -1.1019367835645373,
      -1.1012926657164912, -1.1006771324570581, -1.1000904339611079,
      -1.0995328078086224, -1.0990044789416276, -1.09850565962405,
      -1.0980365494045066, -1.0975973350820254, -1.097188190674699,
      -1.09680927739127, -1.0964607436056559, -1.0961427248344009,
      -1.0958553437170602, -1.0955987099995208, -1.0953729205202356,
      -1.0951780591993923, -1.0950141970309961, -1.0948813920778646,
      -1.0947796894695372, -1.094709121403076, -1.0946697071467759,
      -1.0946614530467491, -1.0946843525363996, -1.0947383861487605,
      -1.0948235215317024, -1.0949397134659795, -1.0950869038861322,
      -1.0952650219042048, -1.0954739838362928, -1.0957136932318849,
      -1.0959840409060053, -1.0962849049741286, -1.0966161508898578,
      -1.0969776314853585, -1.0973691870145217, -1.0977906451988377,
      -1.0982418212759835, -1.0987225180510845, -1.099232525950645,
      -1.0997716230791266, -1.1003395752781526, -1.1009361361883272,
      -1.1015610473136364, -1.1022140380884269, -1.1028948259469242,
      -1.1036031163952849, -1.1043386030861464, -1.105100967895672,
      -1.1058898810030349, -1.1067050009723611, -1.1075459748370675,
      -1.1084124381865967, -1.109304015255516, -1.1102203190149467,
      -1.1111609512663179, -1.1121255027373975, -1.1131135531805885,
      -1.1141246714734556, -1.1151584157214645, -1.1162143333628929,
      -1.1172919612758967, -1.1183908258877, -1.1195104432858733,
      -1.1206503193316857, -1.1218099497754839, -1.1229888203740819,
      -1.1241864070101295, -1.1254021758134181, -1.1266355832841122,
      -1.1278860764178547, -1.1291530928327345, -1.130436060898069,
      -1.13173439986498, -1.133047519998728, -1.1343748227127703,
      -1.1357157007045107, -1.1370695380927165, -1.1384357105565566,
      -1.1398135854762359, -1.1412025220751933, -1.1426018715638271,
      -1.1440109772847098, -1.1454291748592702, -1.1468557923358995,
      -1.1482901503394445, -1.1497315622220661, -1.15117933421542,
      -1.1526327655841198, -1.1540911487804628, -1.1555537696003719,
      -1.1570199073405198, -1.1584888349566078, -1.1599598192227558,
      -1.1614321208919745, -1.1629049948576777, -1.1643776903162111,
      -1.1658494509303476, -1.1673195149937294, -1.1687871155962042,
      -1.1702514807900397, -1.1717118337569628, -1.173167392976004,
      -1.1746173723920963, -1.1760609815854093, -1.1774974259413662,
      -1.1789259068213309, -1.1803456217338997, -1.1817557645067938,
      -1.1831555254592947, -1.184544091575205, -1.1859206466762766,
      -1.1872843715961028, -1.1886344443544072, -1.189970040331723,
      -1.1912903324444046, -1.1925944913199555, -1.1938816854726291,
      -1.1951510814792645, -1.1964018441553363, -1.1976331367311739,
      -1.1988441210283167, -1.2000339576359793, -1.2012018060875858,
      -1.2023468250373448, -1.203468172436827, -1.2045650057115216,
      -1.2056364819373271, -1.2066817580169502, -1.2076999908561916,
      -1.2086903375400555, -1.2096519555086898, -1.2105840027330967,
      -1.2114856378905983, -1.2123560205400106, -1.2131943112965158,
      -1.2139996720061854, -1.2147712659201286, -1.2155082578682397,
      -1.2162098144325106, -1.2168751041198786, -1.2175032975345808,
      -1.2180935675499922, -1.218645089479905, -1.2191570412492372,
      -1.2196286035641246, -1.220058960081388, -1.2204472975773275,
      -1.2207928061158353, -1.2210946792157837, -1.2213521140176751,
      -1.2215643114495189, -1.2217304763919095, -1.22184981784229,
      -1.2219215490783568, -1.2219448878206016, -1.2219190563939475,
      -1.2218432818884712, -1.2217167963191691, -1.2215388367847606,
      -1.2213086456254925, -1.2210254705799319, -1.22068856494071,
      -1.2202971877092137, -1.2198506037491856, -1.2193480839392175,
      -1.2187889053241203, -1.2181723512651379, -1.2174977115889987,
      -1.216764282735767, -1.2159713679054931, -1.2151182772036246,
      -1.2142043277851713, -1.2132288439976027, -1.2121911575224502,
      -1.2110906075156114, -1.2099265407463224, -1.2086983117347925,
      -1.2074052828884758, -1.2060468246369664, -1.2046223155655009,
      -1.2031311425470528, -1.2015727008729922, -1.1999463943823137,
      -1.1982516355894028, -1.1964878458103263, -1.1946544552876432,
      -1.192750903313708, -1.1907766383524612, -1.1887311181596869,
      -1.1866138099017409, -1.1844241902727006, -1.1821617456099693,
      -1.1798259720082878, -1.1774163754321532, -1.1749324718266381,
      -1.172373787226594, -1.1697398578642215, -1.1670302302750106,
      -1.1642444614020266, -1.1613821186985445, -1.1584427802290054,
      -1.1554260347683083, -1.152331481899403, -1.1491587321091945,
      -1.14590740688274, -1.1425771387957351, -1.139167571605276,
      -1.1356783603388976, -1.1321091713818725, -1.1284596825627671,
      -1.1247295832372477, -1.1209185743701335, -1.1170263686156789,
      -1.1130526903960951, -1.1089972759782891, -1.10485987354883,
      -1.1006402432871221, -1.0963381574367941, -1.0919534003752838,
      -1.0874857686816328, -1.0829350712024697, -1.0783011291161884,
      -1.0735837759953113, -1.0687828578670386, -1.0638982332719777,
      -1.058929773321055, -1.0538773617505881, -1.0487408949755519,
      -1.0435202821409932, -1.0382154451716286, -1.0328263188195981,
      -1.0273528507103877, -1.0217950013869088, -1.0161527443517473,
      -1.0104260661075588, -1.0046149661956367, -0.99871945723262445,
      -0.99273956494539572, -0.98667532820408221, -0.98052679905326234,
      -0.97429404274130693, -0.96797713774787209, -0.961576175809565,
      -0.95509126194374383, -0.94852251447049585, -0.94187006503275661,
      -0.93513405861460208, -0.92831465355768483, -0.9214120215758459,
      -0.91442634776787379, -0.90735783062844277, -0.90020668205719823,
      -0.89297312736602241, -0.88565740528446046, -0.87825976796332161,
      -0.870780480976445, -0.86321982332064806, -0.85557808741384378,
      -0.8478555790913449, -0.84005261760033834, -0.83216953559255424,
      -0.82420667911511336, -0.81616440759957043, -0.80804309384914208,
      -0.79984312402413615, -0.79156489762557425, -0.78320882747701992,
      -0.77477533970460966, -0.76626487371528684, -0.75767788217325494,
      -0.74901483097463883, -0.74027619922037025, -0.73146247918728591,
      -0.72257417629746068, -0.7136118090857646, -0.70457590916565527,
      -0.69546702119320425, -0.68628570282936763, -0.67703252470049968,
      -0.66770807035711732, -0.65831293623091525, -0.64884773159004028,
      -0.63931307849262664, -0.62970961173859985, -0.620037978819747,
      -0.61029883986806277, -0.60049286760237874, -0.590620747273273,
      -0.58068317660626789, -0.57068086574332322, -0.56061453718262633,
      -0.55048492571668439, -0.54029277836872835, -0.53003885432741893,
      -0.51972392487988228, -0.50934877334305828, -0.498914194993386,
      -0.48842099699480784, -0.47786999832512261, -0.46726202970067737,
      -0.45659793349940836, -0.44587856368222734, -0.43510478571278038,
      -0.424277476475555, -0.41339752419237114, -0.40246582833723166,
      -0.39148329954956657, -0.38045085954585317, -0.36936944102963493,
      -0.35823998759992975, -0.34706345365804592, -0.33584080431280716,
      -0.32457301528419047, -0.31326107280538062, -0.30190597352325865,
      -0.29050872439731434, -0.27907034259700736, -0.26759185539756181,
      -0.2560743000742175, -0.24451872379494052, -0.23292618351159039,
      -0.22129774584957076, -0.20963448699593584, -0.19793749258599905,
      -0.18620785758842345, -0.17444668618881384, -0.16265509167179987,
      -0.15083419630164741, -0.13898513120137534, -0.12710903623040429,
      -0.11520705986072947, -0.10328035905164268, -0.0913300991229934,
      -0.079357453627013533, -0.0673636042186905, -0.055349740524724404,
      -0.043317060011055994, -0.03126676784898489, -0.019200076779871983,
      -0.007118206978459652, 0.0049776140852120926, 0.01708615178525431,
      0.029206164480771731, 0.041336403658043627, 0.053475614074079206,
      0.0656225339015049, 0.077775894874793541, 0.089934422437822015,
      0.10209683589274229, 0.11426184855015784, 0.12642816788060462,
      0.13859449566731041, 0.15075952816024368, 0.16292195623141825,
      0.1750804655314539, 0.18723373664739806, 0.1993804452617646,
      0.21151926231280485, 0.22364885415599009, 0.23576788272669838,
      0.24787500570408424, 0.25996887667613233, 0.27204814530587007,
      0.284111457498744, 0.29615745557112894, 0.30818477841996361,
      0.32019206169350878, 0.33217793796320738, 0.34414103689662817,
      0.35607998543148822, 0.36799340795073765, 0.379879926458687,
      0.39173816075818052, 0.40356672862877613, 0.41536424600593208,
      0.42712932716118862, 0.43886058488331631, 0.45055663066043228,
      0.46221607486305027, 0.47383752692806008, 0.48541959554362363,
      0.49696088883495748, 0.50846001455100043, 0.51991558025192952,
      0.53132619349753629, 0.54269046203641413, 0.55400699399596065,
      0.56527439807316571, 0.57649128372617564, 0.587656261366608,
      0.59876794255259314, 0.60982494018254074, 0.6208258686895971,
      0.63176934423677555, 0.64265398491273917, 0.65347841092822712,
      0.66424124481308167, 0.67494111161388393, 0.68557663909214472,
      0.696146457923055, 0.70664920189476, 0.71708350810814181,
      0.72744801717708185, 0.73774137342918711, 0.74796222510694477,
      0.75810922456930752, 0.76818102849364522, 0.77817629807808708,
      0.78809369924418271, 0.79793190283989712, 0.80768958484288722,
      0.8173654265640512, 0.82695811485131, 0.83646634229361572,
      0.8458888074251385, 0.85522421492962086, 0.86447127584486438,
      0.87362870776732837, 0.88269523505680769, 0.89166958904116189,
      0.90055050822107063, 0.90933673847478569, 0.9180270332628554,
      0.92662015383278185, 0.93511486942358779, 0.94350995747027355,
      0.951804203808112, 0.95999640287677368, 0.96808535792424011,
      0.97606988121046934, 0.98394879421080306, 0.9917209278190604,
      0.99938512255030332, 1.0069402287432312, 1.0143851067621898,
      1.0217186271987271, 1.0289396710727172, 1.0360471300329575,
      1.0430399065572626, 1.0499169141519837, 1.0566770775509313,
      1.0633193329136756, 1.069842628023183, 1.07624592248275,
      1.0825281879122088, 1.0886884081433683, 1.0947255794146447,
      1.1006387105648729, 1.1064268232262273, 1.1120889520162427,
      1.1176241447288982, 1.1230314625247129, 1.1283099801198293,
      1.1334587859740501, 1.1384769824777772, 1.1433636861378371,
      1.1481180277621401, 1.1527391526431408, 1.1572262207400612,
      1.1615784068598536, 1.1657949008368356, 1.1698749077109967,
      1.1738176479049038, 1.1776223573992004, 1.1812882879066327,
      1.184814707044586, 1.1882008985060828, 1.1914461622292079,
      1.1945498145649236, 1.1975111884432335, 1.2003296335376565,
      1.203004516427981, 1.2055352207612491, 1.2079211474109437,
      1.2101617146343315, 1.2122563582279264, 1.2142045316810401,
      1.2160057063273775, 1.2176593714946322, 1.2191650346520579,
      1.2205222215559706, 1.221730476393132, 1.2227893619220067,
      1.2236984596118159, 1.2244573697793855, 1.2250657117237242,
      1.2255231238583155, 1.2258292638410628, 1.2259838087018782,
      1.22598645496785, 1.2258369187859732, 1.2255349360433891,
      1.225080262485118, 1.2244726738292224, 1.2237119658793869,
      1.2227979546348682, 1.2217304763977777, 1.2205093878776687,
      1.2191345662933861, 1.2176059094721414, 1.2159233359457926,
      1.2140867850442689, 1.2120962169861369, 1.2099516129662451,
      1.2076529752404304, 1.2052003272072518, 1.2025937134867095,
      1.1998331999959218, 1.1969188740217314, 1.1938508442902054,
      1.190629241032988, 1.187254216050494, 1.1837259427718942,
      1.1800446163118747, 1.1762104535241296, 1.1722236930515646,
      1.1680845953731809, 1.1637934428476093, 1.1593505397532624,
      1.1547562123250925, 1.1500108087879, 1.145114699386198, 1.140068276410579,
      1.1348719542205772, 1.1295261692639864, 1.1240313800926243,
      1.1183880673745001, 1.1125967339023828, 1.1066579045987257,
      1.1005721265169466, 1.0943399688390185, 1.0879620228693729,
      1.0814389020250725, 1.0747712418222539, 1.0679596998588072,
      1.061004955793277, 1.0539077113199666, 1.0466686901402393,
      1.0392886379299691, 1.0317683223031739, 1.0241085327717563,
      1.0163100807013947, 1.008373799263528, 1.000300543383446,
      0.99209118968445742, 0.98374663642814375, 0.97526780345065456,
      0.96665563209507077, 0.95791108513981271, 0.9490351467230641,
      0.94002882226323548, 0.9308931383754474, 0.92162914278401964,
      0.91223790423097029, 0.90272051238051942, 0.89307807771958747,
      0.8833117314542942, 0.87342262540245219, 0.86341193188204279,
      0.85328084359569556, 0.84303057351116217, 0.83266235473777239,
      0.82217744039889429, 0.81157710350039469, 0.800862636795107,
      0.79003535264329106, 0.77909658286912653, 0.76804767861321732,
      0.75689001018112578, 0.74562496688794522, 0.7342539568989247,
      0.72277840706613217, 0.71119976276121644, 0.69951948770421846,
      0.68773906378849325, 0.67585999090174131, 0.66388378674315673,
      0.65181198663671247, 0.639646143340612, 0.62738782685290351,
      0.61503862421328859, 0.60260013930115508, 0.59007399262982863,
      0.577461821137081, 0.564765277971925, 0.551986032277707, 0.539125768971519,
      0.52618618851996668, 0.513169006711315, 0.50007595442404784,
      0.48690877739183896, 0.47366923596500715, 0.46035910486845383,
      0.44698017295613146, 0.43353424296206294, 0.42002313124795476,
      0.40644866754742837, 0.39281269470692604, 0.37911706842328713,
      0.36536365697807593, 0.35155434096867239, 0.33769101303617477,
      0.32377557759014275, 0.30980995053023741, 0.29579605896478967,
      0.28173584092633314, 0.26763124508417563, 0.25348423045400137,
      0.23929676610459871, 0.22507083086173429, 0.21080841300923189,
      0.19651150998728195, 0.18218212808806225, 0.16782228214869219,
      0.15343399524160253, 0.13901929836231239, 0.12458023011474649,
      0.11011883639407506, 0.095637170067179048, 0.081137290650753771,
      0.066621263987150209, 0.052091161917963834, 0.037549061955482729,
      0.022997046951979093, 0.0084372047669835741, -0.0061283720674593783,
      -0.0206975866834544, -0.035268338215820309, -0.049838522142446426,
      -0.064406030626406582, -0.0789687528597732, -0.093524575409039759,
      -0.10807138256212349, -0.12260705667685398, -0.13712947853089255,
      -0.15163652767302069, -0.166126082775729, -0.18059602198903216,
      -0.19504422329545487, -0.20946856486608889, -0.22386692541772249,
      -0.23823718457087278, -0.25257722320874387, -0.266884923836975,
      -0.28115817094414869, -0.29539485136295784, -0.30959285463199115,
      -0.32375007335801248, -0.3378644035787432, -0.351933745125981,
      -0.36595600198905059, -0.37992908267846937, -0.39385090058979522,
      -0.40771937436753464, -0.42153242826906584, -0.43528799252850081,
      -0.44898400372038988, -0.46261840512321667, -0.47618914708259663,
      -0.48969418737409065, -0.5031314915655748, -0.5164990333790882,
      -0.52979479505206328, -0.5430167676978821, -0.55616295166565721,
      -0.56923135689920457, -0.58222000329505974, -0.59512692105952936,
      -0.60795015106465533, -0.62068774520303083, -0.63333776674138209,
      -0.64589829067285365, -0.65836740406788452, -0.67074320642365126,
      -0.683023810011938, -0.69520734022540009, -0.70729193592212092,
      -0.719275749768401, -0.73115694857968117, -0.74293371365952943,
      -0.75460424113663516, -0.76616674229968884, -0.77761944393011628,
      -0.78896058863255991, -0.80018843516304283, -0.8113012587547308,
      -0.82229735144123217, -0.83317502237733909, -0.84393259815715083,
      -0.85456842312948278, -0.86508085971053206, -0.87546828869365256,
      -0.885729109556244, -0.89586174076361813, -0.90586462006980684,
      -0.91573620481521734, -0.92547497222108965, -0.93507941968063824,
      -0.94454806504686672, -0.95387944691692816, -0.96307212491299721,
      -0.97212467995956631, -0.98103571455711147, -0.98980385305204843,
      -0.99842774190290351, -1.0069060499426632, -1.0152374686371972,
      -1.0234207123397154, -1.0314545185411919, -1.0393376481166754,
      -1.0470688855674379, -1.0546470392588987, -1.0620709416542502,
      -1.0693394495437423, -1.0764514442695354, -1.0834058319461124,
      -1.0902015436761292, -1.0968375357617026, -1.1033127899110402,
      -1.1096263134403752, -1.1157771394711431, -1.1217643271223636,
      -1.127586961698138, -1.133244154870263, -1.1387350448558504,
      -1.1440587965899605, -1.1492146018931511, -1.1542016796339338,
      -1.1590192758860678, -1.1636666640806415, -1.1681431451529287,
      -1.1724480476839374, -1.1765807280366327, -1.1805405704867924,
      -1.1843269873484441, -1.1879394190938459, -1.1913773344679957,
      -1.1946402305975996, -1.1977276330944873, -1.2006390961534303,
      -1.2033742026443455, -1.2059325641988223, -1.2083138212909816,
      -1.2105176433126064, -1.2125437286425349, -1.2143918047102793,
      -1.21606162805386, -1.2175529843718063, -1.2188656885693372,
      -1.2199995847986627, -1.2209545464934179, -1.2217304763971921,
      -1.2223273065861482, -1.2227449984857064, -1.2229835428812876,
      -1.2230429599231019, -1.2229232991249657, -1.2226246393571392,
      -1.2221470888331882, -1.2214907850908423, -1.220655894966858,
      -1.2196426145658879, -1.2184511692233337, -1.2170818134621983,
      -1.2155348309439349, -1.2138105344132872, -1.2119092656371351,
      -1.2098313953373372, -1.2075773231175924, -1.205147477384312,
      -1.2025423152615178, -1.1997623224997866, -1.196808013379236,
      -1.1936799306065764, -1.1903786452062368, -1.1869047564055912,
      -1.1832588915142881, -1.1794417057977238, -1.1754538823446532,
      -1.171296131928983, -1.1669691928657646, -1.1624738308614087,
      -1.1578108388581341, -1.1529810368727231, -1.1479852718295604,
      -1.142824417388018, -1.137499373764213, -1.132011067547164,
      -1.1263604515093895, -1.1205485044119865, -1.1145762308042118,
      -1.1084446608176266, -1.1021548499548375, -1.0957078788728598,
      -1.0891048531611776, -1.0823469031145136, -1.0754351835003861,
      -1.0683708733214738, -1.0611551755728517, -1.0537893169941428,
      -1.0462745478166509, -1.0386121415055032, -1.0308033944968771,
      -1.0228496259303648, -1.0147521773765156, -1.0065124125596405,
      -0.99813171707592, -0.989611498106869, -0.98095318412825239,
      -0.972158224614484, -0.96322808973857332, -0.954164270067719,
      -0.94496827625456958, -0.93564163872425832, -0.92618590735725992,
      -0.91660265116814044, -0.9068934579802751, -0.89705993409661977,
      -0.88710370396657923, -0.87702640984907521, -0.866829711471877,
      -0.8565152856872692, -0.84608482612413782, -0.83554004283655736,
      -0.82488266194894688, -0.81411442529789124, -0.8032370900706951,
      -0.7922524284407535, -0.78116222719983264, -0.769968287387338,
      -0.75867242391664291, -0.74727646519859592, -0.7357822527622484,
      -0.72419164087293086, -0.712506496147743, -0.70072869716854946,
      -0.68886013409258184, -0.67690270826071886, -0.6648583318035487,
      -0.65272892724531006, -0.64051642710577694, -0.62822277350021727,
      -0.61584991773749165, -0.60339981991639724, -0.59087444852034154,
      -0.57827578001045443, -0.56560579841722847, -0.55286649493078144,
      -0.5400598674898246, -0.52718792036946893, -0.51425266376792855,
      -0.50125611339223874, -0.48820029004308307, -0.47508721919882263,
      -0.46191893059883804, -0.44869745782626225, -0.43542483789023084,
      -0.42210311080771018, -0.40873431918505065, -0.39532050779932204,
      -0.3818637231795538, -0.36836601318797541, -0.3548294266013497,
      -0.34125601269250272, -0.32764782081216648, -0.31400689997118952,
      -0.30033529842327378, -0.28663506324829141, -0.27290823993629615,
      -0.25915687197233889, -0.24538300042217481, -0.23158866351895205,
      -0.217775896251019, -0.20394672995088908, -0.19010319188552249,
      -0.17624730484797696, -0.16238108675055943, -0.14850655021954404,
      -0.13462570219158887, -0.12074054351190776, -0.10685306853432984,
      -0.0929652647233316, -0.079079112258116868, -0.065196583638865921,
      -0.051319643295244854, -0.037450247197247988, -0.023590342468495736,
      -0.0097418670020535791, 0.0040932509211154856, 0.017913093010974032,
      0.031715751344443724, 0.045499328738526489, 0.059261939120440407,
      0.073001707894679427, 0.086716772306907441, 0.10040528180460064,
      0.11406539839436117, 0.1276952969957835, 0.14129316579184251,
      0.15485720657566915, 0.16838563509365814, 0.18187668138481264,
      0.19532859011626411, 0.2087396209148655, 0.22210804869478712,
      0.23543216398103614, 0.24871027322884021, 0.26194069913877982,
      0.27512178096764162, 0.28825187483487813, 0.30132935402462963,
      0.31435260928322128, 0.32732004911207369, 0.34023010005595805,
      0.35308120698650691, 0.36587183338095997, 0.37860046159602734,
      0.39126559313684328, 0.40386574892092714, 0.416399469537102,
      0.42886531549930473, 0.44126186749523438, 0.453587726629763,
      0.46584151466308876, 0.47802187424353715, 0.49012746913498495,
      0.50215698443883694, 0.51410912681051757, 0.52598262467042733,
      0.53777622840930317, 0.54948871058795246, 0.5611188661313109,
      0.57266551251677833, 0.58412748995679387, 0.59550366157560541,
      0.6067929135801996, 0.6179941554253614, 0.62910631997281441,
      0.64012836364441539, 0.65105926656936153, 0.661898032725417,
      0.67264369007406111, 0.68329529068959949, 0.693851910882171,
      0.70431265131464316, 0.71467663711336082, 0.72494301797275251,
      0.73511096825372335, 0.74517968707589755, 0.7551483984036107,
      0.76501635112568933, 0.77478281912898561, 0.78444710136567164,
      0.79400852191425553, 0.80346643003434892, 0.81282020021513812,
      0.82206923221760253, 0.831212951110426, 0.84025080729964663,
      0.84918227655200818, 0.85800686001204418, 0.8667240842128856,
      0.87533350108079022, 0.8838346879334178, 0.89222724747184723,
      0.90051080776636094, 0.90868502223598568, 0.91674956962182885,
      0.92470415395420658, 0.9325485045136005, 0.94028237578542972,
      0.94790554740870947, 0.95541782411855869, 0.96281903568263971,
      0.97010903683150418, 0.977287707182909, 0.98435495116011185,
      0.99131069790418591, 0.99815490118037442, 1.0048875392785455,
      1.0115086149077372, 1.0180181550848844, 1.0244162110177142,
      1.0307028579818904, 1.0368781951924215, 1.0429423456693889,
      1.0488954560980404, 1.0547376966832773, 1.060469260998617,
      1.0660903658296468, 1.0716012510120239, 1.0770021792641085,
      1.0822934360142253, 1.087475329222662, 1.0925481891984286,
      1.097512368410851, 1.1023682412960376, 1.1071162040583209,
      1.1117566744666794, 1.1162900916462473, 1.1207169158649606,
      1.1250376283153996, 1.1292527308919076, 1.1333627459630382,
      1.1373682161394172, 1.1412697040370736, 1.1450677920363328,
      1.1487630820363122, 1.1523561952051298, 1.1558477717258695,
      1.1592384705384102, 1.16252896907716, 1.1657199630048123,
      1.1688121659421644, 1.1718063091941162, 1.1747031414719045,
      1.177503428611665, 1.1802079532894065, 1.1828175147324707,
      1.1853329284275873, 1.187755025825582, 1.1900846540428396,
      1.1923226755596037, 1.1944699679152193, 1.196527423400374,
      1.1984959487464601, 1.2003764648121331, 1.2021699062671516,
      1.2038772212736153, 1.205499371164666, 1.2070373301207533,
      1.2084920848435807, 1.2098646342277886, 1.2111559890304995,
      1.2123671715388087, 1.2134992152353212, 1.2145531644618213,
      1.2155300740811803, 1.2164310091376076, 1.217257044515327,
      1.2180092645957725, 1.2186887629134324, 1.2192966418104063,
      1.2198340120897866, 1.2203019926679728, 1.220701710226004,
      1.2210342988600096, 1.2213008997308994, 1.2215026607133566,
      1.2216407360442565, 1.2217162859706263, 1.2217304763971957,
      1.221684478533694, 1.2215794685419556, 1.2214166271829492,
      1.2211971394638272, 1.2209221942850954, 1.220592984088007,
      1.22021070450226, 1.2197765539941259, 1.2192917335150926,
      1.2187574461511157, 1.2181748967725863, 1.2175452916851084,
      1.2168698382811782, 1.2161497446928855, 1.2153862194456932,
      1.2145804711134338, 1.213733707974582, 1.2128471376699388,
      1.2119219668617751, 1.2109594008945666, 1.2099606434573991,
      1.2089268962481325, 1.2078593586394268, 1.2067592273467149,
      1.2056276960982135, 1.2044659553070658, 1.2032751917457007,
      1.2020565882225056, 1.2008113232608901, 1.1995405707808378,
      1.1982454997830205, 1.1969272740355807, 1.1955870517636424,
      1.1942259853416524, 1.1928452209886271, 1.1914458984663843,
      1.190029150780852, 1.1885961038865258, 1.1871478763941414,
      1.1856855792816723, 1.1842103156086992, 1.1827231802342422,
      1.18122525953812, 1.1797176311459248, 1.1782013636576651,
      1.1766775163801728, 1.1751471390633139, 1.1736112716400968,
      1.1720709439707335, 1.1705271755907258, 1.1689809754630329,
      1.1674333417343923, 1.1658852614958488, 1.1643377105475676,
      1.162791653167965, 1.161248041887242, 1.1597078172653597,
      1.1581719076745194, 1.1566412290862029, 1.1551166848628152,
      1.1535991655539948, 1.1520895486976328, 1.1505886986256484,
      1.1490974662745719, 1.1476166890009774, 1.1461471904018112,
      1.1446897801396541, 1.1432452537729638, 1.1418143925913304,
      1.1403979634557861, 1.1389967186442114, 1.1376113957018503,
      1.1362427172969987, 1.1348913910818699, 1.1335581095586853,
      1.1322435499510017, 1.1309483740803203, 1.129673228247984,
      1.1284187431224055, 1.1271855336316212, 1.1259741988612206,
      1.1247853219576496, 1.1236194700369071, 1.1224771940986584,
      1.1213590289457658, 1.1202654931092597, 1.119197088778757,
      1.1181543017383275, 1.1171376013078225, 1.1161474402896725,
      1.115184254921151, 1.1142484648321049, 1.11334047300816,
      1.1124606657593927, 1.1116094126944669, 1.1107870667002331,
      1.1099939639267709, 1.1092304237778869, 1.1084967489070494,
      1.1077932252187275, 1.1071201218751618, 1.1064776913085144,
      1.1058661692384073, 1.1052857746948104, 1.1047367100462759,
      1.10421916103349, 1.103733296808121, 1.1032792699769329,
      1.1028572166511472, 1.1024672565010212, 1.1021094928156179,
      1.1017840125677176, 1.1014908864838697, 1.1012301691195232,
      1.1010018989392174, 1.1008060984017851, 1.1006427740505336,
      1.1005119166083732, 1.10041350107783, 1.1003474868459193,
      1.1003138177938236, 1.1003124224113425, 1.1003432139160512,
      1.1004060903771222, 1.1005009348437795, 1.100627615478303,
      1.1007859856935507, 1.1009758842949495, 1.1011971356268673,
      1.101449549723357, 1.1017329224631651, 1.102047035728994,
      1.1023916575709081, 1.1027665423738664, 1.1031714310292826,
      1.1036060511105827, 1.1040701170526563, 1.1045633303351794,
      1.1050853796696858, 1.1056359411903887, 1.1062146786486076,
      1.1068212436107929, 1.107455275660028, 1.1081164026009827,
      1.1088042406681844, 1.1095183947376017, 1.1102584585414097,
      1.111024014885883, 1.1118146358723375, 1.1126298831210435,
      1.1134693079980209, 1.1143324518446567, 1.1152188462100352,
      1.1161280130859275, 1.1170594651443408, 1.1180127059775491,
      1.1189872303405213, 1.11998252439566, 1.1209980659597771,
      1.1220333247532033, 1.123087762650955, 1.1241608339358697,
      1.1252519855536287, 1.1263606573695708, 1.1274862824272067,
      1.1286282872083548, 1.1297860918948064, 1.1309591106314292,
      1.1321467517906108, 1.1333484182379676, 1.1345635075992215,
      1.1357914125281461, 1.137031520975508, 1.1382832164588932,
      1.139545878333341, 1.1408188820626861, 1.1421015994915242,
      1.1433933991176997, 1.1446936463652253, 1.1460017038575607,
      1.1473169316911249, 1.1486386877089749, 1.1499663277745522,
      1.1512992060454057, 1.152636675246792, 1.1539780869450729,
      1.1553227918208169, 1.1566701399414956, 1.1580194810337094,
      1.1593701647548444, 1.1607215409640537, 1.1620729599924857,
      1.1634237729126808, 1.1647733318070177, 1.1661209900351532,
      1.1674661025003381, 1.1688080259145368, 1.1701461190622637,
      1.1714797430630335, 1.17280826163236, 1.1741310413412029,
      1.1754474518737692, 1.1767568662836163, 1.1780586612479331,
      1.1793522173199371, 1.1806369191792982, 1.181912155880523,
      1.1831773210991781, 1.1844318133759171, 1.1856750363582016,
      1.186906399039646, 1.1881253159969107, 1.1893312076240536,
      1.1905235003642836, 1.1917016269390175, 1.1928650265741818,
      1.1940131452236746, 1.1951454357899249, 1.1962613583414705,
      1.1973603803274731, 1.198441976789127, 1.1995056305678691,
      1.200550832510332, 1.2015770816699645, 1.2025838855052733,
      1.2035707600745995, 1.204537230227376, 1.2054828297918097,
      1.206407101758908, 1.2073095984628173, 1.2081898817573953,
      1.2090475231889557, 1.2098821041651509, 1.2106932161199178,
      1.2114804606744467, 1.2122434497941068, 1.2129818059412933,
      1.213695162224133, 1.2143831625410151, 1.2150454617208839,
      1.2156817256592578, 1.2162916314499364, 1.216874867512332,
      1.2174311337144137, 1.2179601414911976, 1.2184616139587656,
      1.2189352860237614, 1.2193809044883352, 1.219798228150506,
      1.2201870278999034, 1.2205470868088626, 1.2208782002188421,
      1.2211801758221348, 1.2214528337388493, 1.2216960065891354,
      1.2219095395606376, 1.222093290471135, 1.2222471298263733,
      1.2223709408730632, 1.2224646196470079, 1.2225280750163796,
      1.2225612287201011, 1.2225640154013406, 1.222536382636098,
      1.2224782909568839, 1.222389713871467, 1.2222706378767094,
      1.222121062467465, 1.2219410001405455, 1.2217304763937642,
      1.2214895297200337, 1.2212182115965473, 1.2209165864690368,
      1.2205847317310965, 1.220222737698621, 1.2198307075793171,
      1.2194087574373462, 1.2189570161530654, 1.2184756253779259,
      1.2179647394845066, 1.2174245255117184, 1.2168551631052031,
      1.2162568444529256, 1.2156297742159978, 1.2149741694547651,
      1.2142902595501481, 1.2135782861203039, 1.2128385029326125,
      1.2120711758110159, 1.2112765825387546, 1.2104550127565292,
      1.2096067678561082, 1.2087321608694326, 1.2078315163532625,
      1.2069051702693625, 1.2059534698603203, 1.2049767735209984,
      1.2039754506656803, 1.2029498815909541, 1.2019004573343683,
      1.2008275795289234, 1.1997316602534265, 1.1986131218787832,
      1.1974723969102554, 1.196309927825743, 1.1951261669101614,
      1.193921576085931, 1.1926966267396784, 1.1914517995451719,
      1.1901875842825689, 1.1889044796540311, 1.1876029930957597,
      1.1862836405865231, 1.1849469464527389, 1.1835934431701702,
      1.1822236711622924, 1.1808381785954316, 1.1794375211706905,
      1.1780222619127809, 1.176592970955795, 1.175150225326004,
      1.1736946087217586, 1.1722267112905518, 1.1707471294033158,
      1.1692564654260513, 1.1677553274888364, 1.1662443292523019,
      1.164724089671654, 1.1631952327583244, 1.1616583873393107,
      1.1601141868142919, 1.1585632689106313, 1.157006275436284,
      1.15544385203075, 1.1538766479141263, 1.1523053156343408,
      1.1507305108126602, 1.1491528918875562, 1.1475731198570032,
      1.1459918580193029, 1.1444097717125237, 1.1428275280526221,
      1.1412457956703668, 1.1396652444471138, 1.1380865452495397,
      1.1365103696634409, 1.1349373897266288, 1.1333682776610812,
      1.131803705604381, 1.1302443453405588, 1.1286908680304308,
      1.1271439439415027, 1.1256042421775436, 1.124072430407925,
      1.1225491745967926, 1.121035138732186, 1.1195309845551731,
      1.1180373712891125, 1.116554955369119, 1.1150843901718126,
      1.1136263257454813, 1.1121814085406927, 1.1107502811414858,
      1.1093335819972208, 1.1079319451551648, 1.1065459999939187,
      1.1051763709577747, 1.1038236772920689, 1.1024885327796496,
      1.1011715454785462, 1.0998733174608744, 1.0985944445531624,
      1.0973355160780904, 1.0960971145977787, 1.0948798156587189,
      1.0936841875383922, 1.0925107909937111, 1.0913601790113145,
      1.0902328965598647, 1.0891294803443718, 1.0880504585626523,
      1.086996350664021, 1.0859676671102751, 1.0849649091390408,
      1.0839885685296247, 1.0830391273713569, 1.082117057834586,
      1.0812228219443702, 1.0803568713569349, 1.0795196471389874,
      1.0787115795499707, 1.0779330878273068, 1.0771845799747335,
      1.0764664525537861, 1.075779090478495, 1.0751228668134059,
      1.0744981425749416, 1.0739052665362054, 1.0733445750353048,
      1.0728163917872204, 1.0723210276993411, 1.0718587806906821,
      1.0714299355148795, 1.071034763587023, 1.0706735228143611,
      1.070346457430982, 1.0700537978364935, 1.0697957604387767,
      1.0695725475008804, 1.0693843469920721, 1.0692313324431597,
      1.0691136628060893, 1.0690314823178817, 1.0689849203689776,
      1.0689740913760273, 1.0689990946591548, 1.0690600143237845,
      1.0691569191470365, 1.0692898624687581, 1.06945888208723,
      1.0696640001595752, 1.0699052231069244, 1.0701825415243851,
      1.0704959300958101, 1.0708453475134641, 1.0712307364025575,
      1.0716520232507247, 1.0721091183424687, 1.0726019156985775,
      1.0731302930205755, 1.073694111640217, 1.0742932164740377,
      1.0749274359830208, 1.0755965821373539, 1.0763004503863403,
      1.0770388196334642, 1.0778114522166053, 1.0786180938934788,
      1.0794584738322384, 1.0803323046073172, 1.0812392822004953,
      1.0821790860071805, 1.0831513788479541, 1.0841558069853563,
      1.0851920001459225, 1.0862595715474836, 1.0873581179317113,
      1.0884872196019364, 1.0896464404662169, 1.0908353280856518,
      1.0920534137279525, 1.0933002124262579, 1.0945752230431631,
      1.0958779283400042, 1.0972077950513217, 1.0985642739645438,
      1.099946800004858, 1.1013547923252323, 1.1027876544016044,
      1.1042447741332075, 1.1057255239479835, 1.1072292609131178,
      1.1087553268506134, 1.1103030484579235, 1.1118717374335894,
      1.1134606906078663, 1.1150691900783, 1.1166965033502447,
      1.1183418834822434, 1.1200045692362981, 1.1216837852329344,
      1.1233787421110635, 1.1250886366925941, 1.1268126521517365,
      1.1285499581889724, 1.1302997112096604, 1.1320610545071945,
      1.133833118450718, 1.1356150206772935, 1.1374058662885236,
      1.1392047480515697, 1.1410107466044612, 1.1428229306657316,
      1.1446403572482593, 1.1464620718772716, 1.1482871088124886,
      1.1501144912742993, 1.1519432316739513, 1.1537723318476809,
      1.1556007832947031, 1.1574275674190302, 1.1592516557750485,
      1.1610720103167518, 1.1628875836506221, 1.1646973192920549,
      1.1665001519252631, 1.168295007666599, 1.170080804331225,
      1.1718564517030545, 1.1736208518078881, 1.1753728991896866,
      1.1771114811898984, 1.1788354782297479, 1.180543764095445,
      1.1822352062262151, 1.1839086660050617, 1.1855629990522141,
      1.1871970555211597, 1.1888096803971702, 1.1903997137982782,
      1.1919659912785687, 1.1935073441337607, 1.1950225997089539,
      1.1965105817084634, 1.1979701105076688, 1.1994000034668049,
      1.2007990752465512, 1.202166138125413, 1.2035000023187385,
      1.2047994762993237, 1.2060633671195129, 1.2072904807346718,
      1.2084796223280019, 1.2096295966365578, 1.2107392082783948,
      1.2118072620807623, 1.2128325634092452, 1.2138139184977628,
      1.2147501347793257, 1.2156400212174869, 1.2164823886383609,
      1.217276050063131, 1.2180198210409718, 1.2187125199822675,
      1.2193529684920341, 1.2199399917034845, 1.2204724186116058,
      1.2209490824066724, 1.221368820807611, 1.2217304763951051,
      1.2220328969443544, 1.2222749357574167, 1.2224554519949928,
      1.222573311007606, 1.222627384666076, 1.2226165516911558,
      1.2225396979823056, 1.222395716945448, 1.2221835098196527,
      1.2219019860026505, 1.2215500633750671, 1.2211266686233224,
      1.2206307375610537, 1.2200612154490365, 1.2194170573134504,
      1.2186972282624373, 1.2179007038008638, 1.2170264701431797,
      1.2160735245242904, 1.2150408755083806, 1.2139275432955547,
      1.2127325600262646, 1.2114549700833837, 1.2100938303918825,
      1.2086482107159966, 1.2071171939538385, 1.2054998764292975,
      1.2037953681812468, 1.2020027932498907, 1.2001212899601921,
      1.1981500112023542, 1.196088124709187, 1.1939348133303507,
      1.1916892753033761, 1.1893507245213686, 1.1869183907973511,
      1.1843915201251329, 1.1817693749366893, 1.1790512343558928,
      1.1762363944486178, 1.1733241684690781, 1.1703138871023473,
      1.1672048987030255, 1.1639965695299259, 1.1606882839767545,
      1.1572794447987271, 1.1537694733350088, 1.1501578097269567,
      1.1464439131320998, 1.1426272619337734, 1.138707353946345,
      1.1346837066160251, 1.13055585721714, 1.1263233630438265,
      1.1219858015971493, 1.1175427707674788, 1.1129938890122124,
      1.1083387955286546, 1.1035771504220839, 1.0987086348689739,
      1.0937329512752405, 1.0886498234295485, 1.0834589966515702,
      1.0781602379352335, 1.0727533360868224, 1.0672381018579316,
      1.0616143680732895, 1.0558819897533098, 1.0500408442313987,
      1.0440908312659956, 1.0380318731472498, 1.0318639147983817,
      1.0255869238716147, 1.01920089083873, 1.01270582907614, 1.0061017749445251,
      0.99938878786294361, 0.99256695037745646, 0.98563636822418377,
      0.97859717038680061, 0.97144950914847927, 0.96419356013822777,
      0.95682952237157071, 0.94935761828567478, 0.941778093768792,
      0.93409121818404939, 0.92629728438759829, 0.91839660874109019,
      0.91038953111846443, 0.90227641490707511, 0.89405764700311752,
      0.88573363780137393, 0.87730482117928532, 0.86877165447532179,
      0.86013461846165618, 0.85139421731121434, 0.84255097855899475,
      0.83360545305772615, 0.82455821492791848, 0.81540986150220918,
      0.806161013264089, 0.79681231378102513, 0.78736442963195818,
      0.7778180503291996, 0.76817388823476984, 0.75843267847116236,
      0.74859517882661009, 0.73866216965477549, 0.72863445376899283,
      0.71851285633105688, 0.70829822473453019, 0.69799142848266182,
      0.68759335906091079, 0.67710492980415116, 0.66652707575851411,
      0.65586075353793993, 0.64510694117553369, 0.63426663796964911,
      0.62334086432478641, 0.61233066158740934, 0.60123709187659746,
      0.5900612379096849, 0.578804202822838, 0.56746710998670713,
      0.5560511028171109, 0.54455734458086347, 0.53298701819674243,
      0.52134132603172134, 0.509621489692409, 0.49782874981182756,
      0.48596436583157476, 0.47402961577941438, 0.46202579604228144,
      0.44995422113490519, 0.43781622346397453, 0.4256131530879686,
      0.41334637747266417, 0.4010172812424701, 0.38862726592754515,
      0.37617774970682893, 0.36367016714701367, 0.35110596893755808,
      0.33848662162177695, 0.3258136073240771, 0.31308842347341115,
      0.30031258252305926, 0.28748761166672032, 0.27461505255102686,
      0.2616964609846259, 0.24873340664376525, 0.23572747277452435,
      0.2226802558918124, 0.20959336547511775, 0.19646842366112857,
      0.18330706493330137, 0.1701109358084284, 0.15688169452036946,
      0.14362101070084654, 0.1303305650575636, 0.1170120490496725,
      0.10366716456058594, 0.090297623568322327, 0.076905147813407376,
      0.063491468464448989, 0.05005832578142843, 0.036607468776780117,
      0.023140654874448149, 0.0096596495668591891, -0.0038337739300408364,
      -0.017337835023542487, -0.030850746092741674, -0.04437071283877364,
      -0.057895934636652616, -0.071424604888598739, -0.08495491137880791,
      -0.098485036629557862, -0.11201315825857229, -0.12553744933751049,
      -0.13905607875158751, -0.1525672115601808, -0.16606900935830773,
      -0.17955963063891658, -0.1930372311559988, -0.20649996428822584,
      -0.21994598140321259, -0.23337343222223866, -0.24678046518535085,
      -0.26016522781676177, -0.27352586709043941, -0.28686052979584337,
      -0.30016736290369517, -0.313444513931665, -0.32669013130995278,
      -0.33990236474663343, -0.35307936559268582, -0.36621928720661862,
      -0.379320285318615, -0.392380518394144, -0.40539814799683838,
      -0.41837133915070157, -0.43129826070148258, -0.44417708567709946,
      -0.45700599164709793, -0.46978316108104395, -0.48250678170573558,
      -0.49517504686119612, -0.5077861558552772, -0.520338314316958,
      -0.53282973454808447, -0.54525863587353263, -0.55762324498976135,
      -0.5699217963116322, -0.58215253231739172, -0.59431370389178062,
      -0.60640357066718054, -0.61842040136273446, -0.63036247412130908,
      -0.64222807684428462, -0.65401550752409188, -0.66572307457437185,
      -0.677349097157718, -0.68889190551095347, -0.70034984126782851,
      -0.71172125777906292, -0.72300452042971253, -0.73419800695374382,
      -0.74530010774576494, -0.75630922616982177, -0.76722377886524418,
      -0.77804219604943936, -0.7887629218175477, -0.79938441443890951,
      -0.8099051466503645, -0.82032360594615, -0.83063829486448337,
      -0.84084773127070511, -0.85095044863694047, -0.86094499631820365,
      -0.87082993982488366, -0.88060386109158928, -0.89026535874228163,
      -0.89981304835159137, -0.90924556270234891, -0.91856155203922329,
      -0.92775968431841638, -0.9368386454533838, -0.94579713955651534,
      -0.95463388917675573, -0.96334763553307268, -0.97193713874374943,
      -0.98040117805149085, -0.98873855204422523, -0.9969480788716153,
      -1.0050285964572323, -1.0129789627063328, -1.0207980557092049,
      -1.0284847739400391, -1.0360380364513304, -1.0434567830637158,
      -1.0507399745512265, -1.0578865928219658, -1.0648956410941433,
      -1.0717661440674151, -1.0784971480895447, -1.0850877213183412,
      -1.0915369538788382, -1.0978439580156811, -1.1040078682407242,
      -1.1100278414757996, -1.1159030571906319, -1.1216327175358689,
      -1.1272160474712429, -1.1326522948888218, -1.1379407307313048,
      -1.1430806491054071, -1.1480713673902803, -1.1529122263409435,
      -1.1576025901867553, -1.1621418467248767, -1.1665294074087316,
      -1.1707647074314718, -1.1748472058043815, -1.1787763854303122,
      -1.1825517531720389, -1.186172839915608, -1.1896392006286367,
      -1.192950414413587, -1.1961060845559972, -1.1991058385676614,
      -1.2019493282248044, -1.2046362296012116, -1.2071662430963259,
      -1.2095390934583417, -1.2117545298022872, -1.2138123256230875,
      -1.2157122788036536, -1.2174542116179807, -1.2190379707292758,
      -1.2204634271831374, -1.2217304763957781, -1.2228390381373384,
      -1.2237890565102729, -1.2245804999228682, -1.2252133610578519,
      -1.2256876568361876, -1.2260034283760124, -1.2261607409467716,
      -1.2261596839185751, -1.2260003707067715, -1.2256829387118149,
      -1.2252075492543908, -1.2245743875058888, -1.2237836624141916,
      -1.2228356066248696, -1.2217304763977619, -1.2204685515189975,
      -1.219050135208495, -1.2174755540229667, -1.2157451577544378,
      -1.213859319324387, -1.2118184346734411, -1.209622922646765,
      -1.2072732248751108, -1.2047698056515963, -1.2021131518042532,
      -1.1993037725643854, -1.1963421994307573, -1.1932289860296967,
      -1.1899647079711115, -1.1865499627004872, -1.1829853693469212,
      -1.1792715685672053, -1.1754092223860406, -1.1713990140324002,
      -1.1672416477721153, -1.1629378487367108, -1.1584883627485465,
      -1.1538939561423349, -1.1491554155830392, -1.1442735478802641,
      -1.1392491797991318, -1.1340831578677382, -1.1287763481812247,
      -1.1233296362025234, -1.1177439265598186, -1.112020142840811,
      -1.1061592273838061, -1.10016214106568, -1.0940298630868412,
      -1.0877633907531465, -1.0813637392549198, -1.074831941443074,
      -1.0681690476024253, -1.0613761252222382, -1.0544542587640708,
      -1.0474045494269963, -1.0402281149102057, -1.0329260891731409,
      -1.0254996221931132, -1.0179498797205746, -1.0102780430320146,
      -1.00248530868059, -0.9945728882445547, -0.98654200807351866,
      -0.978393909032638, -0.97012984624474574, -0.96175108883056282,
      -0.95325891964697484, -0.94465463502347047, -0.93593954449682959,
      -0.92711497054408054, -0.91818224831382189, -0.90914272535593965,
      -0.89999776134983867, -0.89074872783117232, -0.881397007917239,
      -0.871943996030976, -0.86239109762376953, -0.85273972889699978,
      -0.84299131652246884, -0.83314729736178383, -0.82320911818468157,
      -0.81317823538645517, -0.80305611470445337, -0.79284423093381617,
      -0.78254406764239992, -0.77215711688504129, -0.76168487891721,
      -0.75112886190803518, -0.74049058165291659, -0.72977156128561238,
      -0.71897333099000371, -0.70809742771153583, -0.69714539486838167,
      -0.68611878206243282, -0.67501914479018421, -0.66384804415350884,
      -0.65260704657043311, -0.64129772348601033, -0.62992165108323861,
      -0.61848040999421783, -0.60697558501149229, -0.5954087647997206,
      -0.58378154160767781, -0.57209551098066214, -0.5603522714734106,
      -0.54855342436347931, -0.53670057336527532, -0.5247953243446607,
      -0.51283928503432874, -0.50083406474986736, -0.48878127410666278,
      -0.47668252473767575, -0.46453942901211159, -0.4523535997550982,
      -0.44012664996833428, -0.42786019255189456, -0.41555584002710594,
      -0.403215204260613, -0.39083989618972537, -0.37843152554900261,
      -0.36599170059820746, -0.35352202785161918, -0.34102411180882114,
      -0.32849955468691827, -0.31594995615436655, -0.30337691306628206,
      -0.29078201920148417, -0.27816686500113241, -0.26553303730909933,
      -0.25288211911415748, -0.24021568929389084, -0.22753532236053792,
      -0.21484258820866348, -0.20213905186482733, -0.18942627323918937,
      -0.17670580687912596, -0.16397920172497055, -0.15124800086776397,
      -0.13851374130922553, -0.12577795372383782, -0.11304216222318235,
      -0.100307884122523, -0.087576629709645151, -0.0748499020160416,
      -0.062129196590477109, -0.04941600127489764, -0.0367117959827638,
      -0.024018052479903827, -0.011336234167765784, 0.0013322041307376915,
      0.013985816382894371, 0.026623165555229679, 0.039242823819971046,
      0.051843372758876488, 0.064423403564370069, 0.076981517238040711,
      0.089516324786365287, 0.10202644741376285, 0.11451051671281057,
      0.12696717485173795, 0.1393950747590855, 0.15179288030551208,
      0.16415926648280343, 0.17649291957993379, 0.18879253735632268,
      0.20105682921209497, 0.21328451635546614, 0.22547433196718547,
      0.237625021361968, 0.249735342146981, 0.26180406437733633,
      0.273829970708572, 0.28581185654608726, 0.29774853019158931,
      0.30963881298642409, 0.32148153945193608, 0.33327555742666148,
      0.34501972820050997, 0.35671292664584736, 0.3683540413454327,
      0.37994197471732538, 0.39147564313659577, 0.40295397705399166,
      0.41437592111142019, 0.42574043425433128, 0.43704648984096922,
      0.44829307574844912, 0.45947919447574531, 0.47060386324347692,
      0.48166611409060284, 0.49266499396792318, 0.50359956482846369,
      0.51446890371470644, 0.5252721028426719, 0.53600826968284065,
      0.54667652703796032, 0.55727601311772068, 0.567805881610231,
      0.57826530175045032, 0.5886534583854256, 0.59896955203644642,
      0.60921279895805891, 0.61938243119398884, 0.62947769662996356,
      0.63949785904341827, 0.64944219815015447, 0.65931000964786834,
      0.66910060525668036, 0.67881331275653756, 0.688447476021616,
      0.69800245505168945, 0.70747762600042485, 0.71687238120073915,
      0.72618612918707759, 0.73541829471478659, 0.74456831877644425,
      0.75363565861527126, 0.76261978773560823, 0.77152019591042376,
      0.78033638918594217, 0.7890678898833664, 0.79771423659772234,
      0.80627498419383048, 0.814749703799456, 0.82313798279558692,
      0.83143942480396582, 0.83965364967176137, 0.84778029345351424,
      0.85581900839033842, 0.86376946288633083, 0.87163134148233889,
      0.87940434482698948, 0.8870881896450673, 0.894682608703237,
      0.9021873507731325, 0.90960218059186193, 0.91692687881989943,
      0.92416124199643612, 0.93130508249218058, 0.93835822845966566,
      0.94532052378102893, 0.95219182801335922, 0.95897201633158013,
      0.96566097946892593, 0.972258623655007, 0.97876487055151928,
      0.98517965718561429, 0.9915029358809252, 0.99773467418633,
      1.0038748548024192, 1.0099234755057414, 1.0158805490708176,
      1.0217461031899879, 1.0275201803910685, 1.0332028379528833,
      1.0387941478187102, 1.0442941965075898, 1.0497030850236502,
      1.0550209287633352, 1.060247857420678, 1.0653840148906004,
      1.0704295591702309, 1.0753846622583567, 1.0802495100529397,
      1.0850243022468118, 1.0897092522215117, 1.0943045869393204,
      1.0988105468335378, 1.1032273856969999, 1.1075553705688659,
      1.1117947816197367, 1.1159459120351061, 1.1200090678971626,
      1.1239845680650162, 1.1278727440533167, 1.1316739399093538,
      1.1353885120886222, 1.1390168293289014, 1.1425592725228833,
      1.1460162345893528, 1.1493881203429797, 1.1526753463627304,
      1.1558783408589368, 1.1589975435390416, 1.1620334054720709,
      1.16498638895183, 1.1678569673588841, 1.1706456250213313,
      1.173352857074391, 1.1759791693188784, 1.1785250780785266,
      1.1809911100562431, 1.18337780218931, 1.1856857015035325,
      1.1879153649664063, 1.190067359339293, 1.1921422610286678,
      1.1941406559364263, 1.1960631393093197, 1.1979103155875135,
      1.1996827982523186, 1.2013812096731111, 1.2030061809534727,
      1.2045583517765739, 1.2060383702498412, 1.2074468927489133,
      1.2087845837609319, 1.2100521157271877, 1.2112501688851496,
      1.2123794311098908, 1.2134405977549694, 1.2144343714927481,
      1.2153614621542206, 1.2162225865683376, 1.2170184684008796,
      1.2177498379928877, 1.2184174321986954, 1.2190219942235685,
      1.2195642734609842, 1.2200450253295856, 1.2204650111098212,
      1.2208249977803014, 1.2211257578539, 1.2213680692136166, 1.221552714948229,
      1.2216804831877695, 1.2217521669388207, 1.2217685639196945,
      1.221730476395479, 1.2216387110130105, 1.2214940786357653,
      1.2212973941787162, 1.2210494764431621, 1.2207511479515669,
      1.2204032347824143, 1.2200065664051163, 1.2195619755149918,
      1.2190702978683312, 1.21853237211758, 1.2179490396466601,
      1.2173211444064413, 1.2166495327503939, 1.215935053270454,
      1.2151785566330888, 1.2143808954156234, 1.2135429239428208,
      1.2126654981237515, 1.2117494752889622, 1.2107957140279753,
      1.2098050740271329, 1.2087784159078006, 1.2077166010649634,
      1.206620491506224, 1.2054909496912221, 1.2043288383715016,
      1.2031350204308444, 1.2019103587260735, 1.2006557159283677,
      1.1993719543650974, 1.19805993586219, 1.1967205215870553,
      1.1953545718920897, 1.1939629461587713, 1.1925465026423587,
      1.1911060983172292, 1.1896425887228617, 1.1881568278104748,
      1.1866496677903482, 1.1851219589798598, 1.1835745496522116,
      1.1820082858859022, 1.1804240114149513, 1.1788225674798827,
      1.177204792679488, 1.1755715228234007, 1.1739235907854679,
      1.1722618263579674, 1.1705870561066658, 1.1689001032267328,
      1.1672017873995435, 1.1654929246503738, 1.1637743272069903,
      1.1620468033591946, 1.1603111573192593, 1.1585681890833761,
      1.1568186942940246, 1.1550634641033539, 1.1533032850375473,
      1.1515389388622079, 1.1497712024487778, 1.1480008476419779,
      1.1462286411283336, 1.1444553443057401, 1.1426817131541309,
      1.1409084981072497, 1.13913644392551, 1.137366289569999,
      1.1355987680776165, 1.1338346064373643, 1.132074525467806,
      1.1303192396956856, 1.1285694572357696, 1.1268258796718729,
      1.1250892019390926, 1.1233601122073118, 1.1216392917658951,
      1.1199274149096827, 1.1182251488262256, 1.1165331534843073,
      1.1148520815237766, 1.1131825781466504, 1.1115252810095666,
      1.1098808201175465, 1.1082498177190996, 1.1066328882026879,
      1.1050306379945563, 1.1034436654579214, 1.1018725607935613,
      1.10031790594182, 1.0987802744859707, 1.0972602315570643,
      1.0957583337401582, 1.0942751289820196, 1.0928111565002641,
      1.0913669466939759, 1.0899430210557821, 1.0885398920854417,
      1.0871580632049003, 1.0857980286748781, 1.0844602735129634,
      1.0831452734132185, 1.0818534946673704, 1.0805853940874857,
      1.0793414189302648, 1.0781220068228556, 1.0769275856902711,
      1.0757585736843949, 1.0746153791145583, 1.0734984003797623,
      1.0724080259024704, 1.0713446340640729, 1.0703085931419327,
      1.0693002612481393, 1.0683199862698267, 1.0673681058112521,
      1.0664449471374595, 1.0655508271196581, 1.0646860521823021,
      1.0638509182518157, 1.0630457107070739, 1.0622707043315549,
      1.0615261632672295, 1.0608123409701697, 1.060129480167902,
      1.0594778128184765, 1.0588575600713162, 1.0582689322297985,
      1.057712128715619, 1.0571873380349048, 1.0566947377461138,
      1.0562344944297322, 1.0558067636597319, 1.0554116899768602,
      1.0550494068636935, 1.0547200367215357, 1.0544236908491116,
      1.0541604694230902, 1.0539304614804148, 1.0537337449025035,
      1.0535703864012445, 1.0534404415068606, 1.053343954557626,
      1.0532809586913956, 1.0532514758390437, 1.0532555167197357,
      1.0532930808380492, 1.0533641564830141, 1.0534687207289717,
      1.0536067394383468, 1.05377816726629, 1.0539829476672029,
      1.0542210129031446, 1.0544922840541531, 1.0547966710304089,
      1.0551340725863654, 1.0555043763367002, 1.0559074587742374,
      1.0563431852897116, 1.0568114101934623, 1.0573119767390531,
      1.0578447171487453, 1.0584094526409242, 1.0590059934594089,
      1.0596341389046782, 1.0602936773669962, 1.060984386361459,
      1.0617060325649323, 1.0624583718549028, 1.0632411493502598,
      1.0640540994539154, 1.0648969458974216, 1.065769401787396,
      1.0666711696539219, 1.0676019415008029, 1.0685613988577216,
      1.0695492128343069, 1.0705650441760761, 1.0716085433222597,
      1.0726793504655283, 1.0737770956135795, 1.0749013986526184,
      1.076051869412691, 1.077228107734888, 1.0784297035404282,
      1.0796562369015685, 1.0809072781143876, 1.0821823877733996,
      1.0834811168480105, 1.084803006760817, 1.0861475894677086,
      1.0875143875398008, 1.0889029142471776, 1.0903126736444373,
      1.091743160658019, 1.0931938611753362, 1.0946642521356673,
      1.0961538016228221, 1.0976619689595768, 1.0991882048038282,
      1.1007319512465241, 1.1022926419112793, 1.1038697020557495,
      1.1054625486746832, 1.1070705906046718, 1.1086932286305902,
      1.1103298555937051, 1.1119798565014281, 1.1136426086387397,
      1.1153174816812057, 1.1170038378096541, 1.1187010318264241,
      1.1204084112732056, 1.122125316550487, 1.1238510810385078,
      1.1255850312198097, 1.1273264868032737, 1.1290747608496872,
      1.1308291598988207, 1.1325889840979535, 1.1343535273318761,
      1.1361220773543452, 1.1378939159209489, 1.1396683189233774,
      1.1414445565251186, 1.14322189329846, 1.1449995883629103,
      1.1467768955249023, 1.1485530634188255, 1.1503273356493537,
      1.1520989509350363, 1.1538671432531273, 1.1556311419856671,
      1.1573901720667497, 1.1591434541309742, 1.16089020466307,
      1.1626296361486419, 1.1643609572260469, 1.1660833728393503,
      1.1677960843923487, 1.1694982899036528, 1.1711891841627555,
      1.1728679588871378, 1.1745338028802992, 1.1761859021907526,
      1.177823440271949, 1.1794455981430612, 1.1810515545506501,
      1.1826404861311761, 1.184211567574297, 1.18576397178697,
      1.1872968700583042, 1.1888094322251208, 1.1903008268382491,
      1.1917702213294492, 1.1932167821790107, 1.1946396750839448,
      1.1960380651267608, 1.197411116944805, 1.1987579949001026,
      1.2000778632497109, 1.2013698863165254, 1.2026332286605166,
      1.2038670552503639, 1.2050705316354671, 1.2062428241182817,
      1.2073830999269686, 1.2084905273883151, 1.2095642761008869,
      1.2106035171084077, 1.2116074230732894, 1.2125751684503292,
      1.2135059296604955, 1.2143988852647993, 1.2152532161382095,
      1.2160681056435809, 1.2168427398055324, 1.2175763074843038,
      1.2182680005494886, 1.2189170140536556, 1.2195225464057975,
      1.2200837995445959, 1.2205999791114388, 1.2210702946231884,
      1.2214939596446315, 1.2218701919606045, 1.2221982137477461,
      1.2224772517458284, 1.2227065374286734, 1.2228853071745605,
      1.2230128024361342, 1.2230882699097763, 1.2231109617043656,
      1.2230801355094358, 1.2229950547626758, 1.2228549888167226,
      1.2226592131052478, 1.2224070093082635, 1.2220976655166342,
      1.221730476395755, 1.2213047433483475, 1.2208197746763685,
      1.2202748857419496, 1.2196693991273795, 1.219002644794057,
      1.2182739602404073, 1.2174826906586922, 1.2166281890907142,
      1.2157098165823659, 1.2147269423369655, 1.2136789438673938,
      1.21256520714694, 1.2113851267588689, 1.2101381060446448,
      1.2088235572507917, 1.2074409016743461, 1.2059895698068841,
      1.2044690014770574, 1.2028786459916445, 1.2012179622750434,
      1.1994864190072076, 1.1976834947599684, 1.1958086781316999,
      1.1938614678803507, 1.1918413730547153, 1.1897479131240214,
      1.1875806181056996, 1.1853390286913736, 1.1830226963710142,
      1.1806311835552066, 1.178164063695553, 1.1756209214030919,
      1.1730013525648284, 1.1703049644581884, 1.16753137586354,
      1.1646802171745829, 1.1617511305067083, 1.1587437698032361,
      1.1556578009394993, 1.1524929018247789, 1.1492487625020336,
      1.1459250852454137, 1.1425215846555008, 1.1390379877523156,
      1.1354740340659748, 1.1318294757250484, 1.1281040775425397,
      1.1242976170995151, 1.1204098848262891, 1.1164406840812091,
      1.1123898312269893, 1.1082571557045222, 1.1040425001042693,
      1.0997457202350309, 1.0953666851902781, 1.0909052774118235,
      1.0863613927509672, 1.0817349405270102, 1.0770258435831441,
      1.072234038339714, 1.0673594748447564, 1.0624021168219526,
      1.0573619417157758, 1.0522389407339963, 1.047033118887416,
      1.0417444950268511, 1.036373101877375, 1.0309189860697434,
      1.0253822081690613, 1.0197628427005927, 1.0140609781728154,
      1.0082767170975584, 1.0024101760073774, 0.99646148546999946,
      0.99043079009995039, 0.9843182485672668, 0.97812403360335176,
      0.97184833200390608, 0.96549134462896968 } ;

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
      0.0, 0.11857747096273985, 0.11236623066845919, 0.10611351784120365,
      0.099820898515268319, 0.093489956440552024, 0.08712229259432161,
      0.080719524685265276, 0.074283286649999447, 0.067815228142195982,
      0.061317014014500626, 0.054790323793412643, 0.048236851147306109,
      0.041658303347767683, 0.035056400724435305, 0.028432876113521022,
      0.021789474300206446, 0.015127951455099736, 0.00845007456494773,
      0.0017576208577974872, -0.0049476227771935444, -0.011663860375100588,
      -0.018389287485523931, -0.025122091767626697, -0.031860453589710569,
      -0.038602546633121154, -0.045346538500271372, -0.052090591326570568,
      -0.058832862396043017, -0.065571504760421367, -0.072304667861494448,
      -0.079030498156491158, -0.085747139746276929, -0.092452735006142178,
      -0.099145425218954558, -0.10582335121045389, -0.11248465398645779,
      -0.11912747537175369, -0.12574995865044497, -0.13235024920752336,
      -0.13892649517143418, -0.14547684805740366, -0.15199946341129497,
      -0.15849250145376076, -0.1649541277244552, -0.1713825137260741,
      -0.17777583756798751, -0.18413228460922759, -0.19045004810059921,
      -0.19672732982567515, -0.20296234074044214, -0.20915330161136172,
      -0.215298443651608, -0.22139600915525293, -0.22744425212915692,
      -0.2334414389223361, -0.23938584885256875, -0.24527577483000851,
      -0.25110952397757286, -0.25688541824787181, -0.26260179503644732,
      -0.26825700779109535, -0.27384942661703449, -0.27937743887770183,
      -0.28483944979094161, -0.29023388302036279, -0.29555918126164565,
      -0.30081380682356712, -0.30599624220352722, -0.31110499065735853,
      -0.31613857676319562, -0.32109554697919196, -0.32597447019486758,
      -0.33077393827587664, -0.33549256660198057, -0.34012899459802393,
      -0.34468188625770174, -0.34914993065991407, -0.35353184247751157,
      -0.35782636247822541, -0.36203225801759009, -0.36614832352366067,
      -0.37017338097333757, -0.37410628036010385, -0.377945900152995,
      -0.38169114774661222, -0.38534095990200412, -0.38889430317823404,
      -0.3923501743544644, -0.39570760084238071, -0.39896564108879207,
      -0.40212338496824196, -0.40517995416546659, -0.40813450254754513,
      -0.4109862165255852, -0.41373431540579375, -0.41637805172978593,
      -0.41891671160398825, -0.42134961501799484, -0.42367611615174294,
      -0.42589560367137147, -0.42800750101363855, -0.43001126665876932,
      -0.43190639439161638, -0.43369241355101296, -0.43536888926721107,
      -0.43693542268729052, -0.43839165118843815, -0.43973724857899671,
      -0.44097192528718654, -0.44209542853740957, -0.44310754251404638,
      -0.44400808851266776, -0.444796925078577, -0.4454739481326121,
      -0.446039091084138, -0.4464923249311657, -0.44683365834753053,
      -0.44706313775708423, -0.44718084739484038, -0.44718690935503363,
      -0.44708148362604183, -0.44686476811214604, -0.446536998642083,
      -0.44609844896437045, -0.44554943072937886, -0.4448902934581323,
      -0.44412142449782116, -0.44324324896402417, -0.44225622966962785,
      -0.44116086704045021, -0.4399576990175702, -0.43864730094637444,
      -0.43723028545233406, -0.4357073023035366, -0.43407903825998967,
      -0.43234621690973224, -0.43050959849178344, -0.42856997970596949,
      -0.42652819350967275, -0.42438510890154779, -0.42214163069226318,
      -0.41979869926232122, -0.41735729030702035, -0.41481841456862967,
      -0.41218311755584169, -0.4094524792505882, -0.40662761380228962,
      -0.40370966920963552, -0.40069982698997608, -0.39759930183642722,
      -0.3944093412627836, -0.39113122523634836, -0.38776626579878209,
      -0.38431580667508947, -0.38078122287085858, -0.37716392025787415,
      -0.37346533514823044, -0.36968693385707807, -0.36583021225413148,
      -0.36189669530408608, -0.35788793659607726, -0.35380551786233833,
      -0.34965104848619966, -0.34542616499959189, -0.34113253057020637,
      -0.33677183447847897, -0.33234579158456429, -0.32785614178546907,
      -0.32330464946252013, -0.31869310291934649, -0.31402331381055654,
      -0.30929711656129172, -0.30451636777785351, -0.29968294564958969,
      -0.29479874934223604, -0.28986569838291731, -0.2848857320370029,
      -0.27986080867702889, -0.27479290514388932, -0.26968401610051468,
      -0.26453615337824538, -0.25935134531612247, -0.25413163609331385,
      -0.24887908505489931, -0.24359576603124003, -0.23828376665116033,
      -0.23294518764917474, -0.22758214216698758, -0.22219675504950948,
      -0.21679116213562008, -0.21136750954392161, -0.20592795295372521,
      -0.20047465688151167, -0.19500979395311394, -0.18953554417187021,
      -0.1840540941829964, -0.17856763653442664, -0.17307836893438039,
      -0.16758849350590346, -0.16210021603864569, -0.156615745238125,
      -0.15113729197274445, -0.14566706851881323, -0.14020728780383612,
      -0.13476016264833587, -0.12932790500646282, -0.12391272520566132,
      -0.1185168311856557, -0.11314242773701565, -0.10779171573957048,
      -0.10246689140093421, -0.097170145495411975, -0.091903662603542768,
      -0.086669620352555946, -0.081470188658000667, -0.0763075289668152,
      -0.071183793502098483, -0.066101124509857084, -0.061061653507982455,
      -0.056067500537729617, -0.051120773417957871, -0.046223567002397929,
      -0.041377962440205904, -0.036586026440066768, -0.031849810538109015,
      -0.027171350369889685, -0.022552664946700628, -0.017995755936468197,
      -0.013502606949487503, -0.0090751828292511, -0.0047154289486303486,
      -0.00042527051165068552, 0.0037933881388838853, 0.0079386642076679642,
      0.012008697126832696, 0.016001649229294174, 0.019915706415278275,
      0.023749078811774876, 0.027500001424686157, 0.031166734783437358,
      0.034747565577810696, 0.0382408072867788, 0.041644800799104584,
      0.044957915025483686, 0.048178547502008576, 0.051305124984736092,
      0.054336104035134392, 0.057269971596203839, 0.060105245559059439,
      0.06284047531976128, 0.065474242326193283, 0.068005160614794585,
      0.070431877336933207, 0.072753073274736735, 0.07496746334618884,
      0.0770737970993004, 0.0790708591951726, 0.080957469879777449,
      0.082732485444271586, 0.084394798673676275, 0.085943339283753084,
      0.087377074345913242, 0.088695008699998024, 0.089896185354773284,
      0.0909796858759892, 0.0919446307618561, 0.0927901798057893,
      0.093515532446288685, 0.094119928103816752, 0.094602646504542531,
      0.094963007990825438, 0.095200373818322553, 0.095314146439596625,
      0.095303769774113783, 0.095168729464525814, 0.094908553119133071,
      0.094522810540426, 0.0940111139396207, 0.093373118137088679,
      0.092608520748607648, 0.091717062357346724, 0.090698526671517066,
      0.089552740667616926, 0.088279574719206222, 0.086878942711156426,
      0.08535080213931423, 0.0836951541955368, 0.081912043838053228,
      0.0800015598471121, 0.07796383486587849, 0.075799045426564127,
      0.073507411961752478, 0.0710891988009078, 0.06854471415205976,
      0.06587431006864547, 0.063078382401514976, 0.06015737073609867,
      0.057111758314745853, 0.05394207194424866, 0.050648881888563868,
      0.047232801746765474, 0.043694488316247837, 0.040034641441218544,
      0.036254003846516059, 0.032353360956802413, 0.0283335407011715,
      0.024195413303234381, 0.0199398910567396, 0.015567928086791527,
      0.011080520096736102, 0.0064787041007919877, 0.0017635581425045621,
      -0.0030637990008941518, -0.0080022081281224122, -0.013050469937401,
      -0.018207345363803806, -0.023471555930318577, -0.02884178411249666,
      -0.0343166737165847, -0.039894830271012705, -0.045574821431122126,
      -0.051355177396997576, -0.05723439134427516, -0.063210919867786208,
      -0.069283183437894524, -0.075449566869378648, -0.081708419802714649,
      -0.088058057197589523, -0.094496759838502753, -0.10102277485227351,
      -0.10763431623730152, -0.11432956540439099, -0.12110667172897654,
      -0.12796375311456021, -0.13489889656717347, -0.14191015878068375,
      -0.14899556673273862, -0.15615311829116596, -0.16338078283061253,
      -0.17067650185923422, -0.1780381896552109, -0.1854637339128925,
      -0.19295099639834407, -0.20049781361408525, -0.20810199747278973,
      -0.21576133597973185, -0.22347359392373883, -0.23123651357642833,
      -0.23904781539949, -0.24690519875977263, -0.254806342651942,
      -0.26274890642846382, -0.2707305305366583, -0.27874883726259425,
      -0.286801431481552, -0.29488590141481863, -0.30299981939254705,
      -0.311140742622429, -0.31930621396391762, -0.32749376270773844,
      -0.33570090536042241, -0.34392514643359906, -0.35216397923777781,
      -0.36041488668034616, -0.36867534206752139, -0.37694280990997231,
      -0.38521474673184508, -0.39348860188291279, -0.401761818353575,
      -0.41003183359242257, -0.41829608032610233, -0.42655198738118333,
      -0.43479698050776172, -0.44302848320451005, -0.45124391754489346,
      -0.45944070500427048, -0.46761626728759764, -0.47576802715744387,
      -0.48389340926204855, -0.49198984096312093, -0.50005475316310866,
      -0.50808558113164981, -0.51607976533092148, -0.52403475223960294,
      -0.53194799517517266, -0.5398169551142552, -0.54763910151073225,
      -0.55541191311134319, -0.56313287876848994, -0.57079949824996967,
      -0.57840928304535189, -0.5859597571687275, -0.59344845795755219,
      -0.60087293686730447, -0.60823076026169187, -0.61551951019812667,
      -0.62273678520820386, -0.62988020107291165, -0.63694739159230718,
      -0.64393600934938933, -0.65084372646790833, -0.65766823536385244,
      -0.664407249490345, -0.67105850407570022, -0.67761975685438691,
      -0.684088788790634, -0.69046340479444335, -0.69674143442975134,
      -0.70292073261450438, -0.70899918031239517, -0.714974685216028,
      -0.72084518242128071, -0.7266086350926152, -0.73226303511912694,
      -0.73780640376108964, -0.74323679228677975, -0.74855228259935813,
      -0.753750987853598, -0.7588310530622342, -0.76379065569173632,
      -0.76862800624729055, -0.77334134884679706, -0.7779289617836771,
      -0.78238915807829545, -0.78672028601781474, -0.79092072968428861,
      -0.79498890947081258, -0.79892328258555567, -0.80272234354350125,
      -0.80638462464571692, -0.80990869644600738, -0.81329316820476483,
      -0.8165366883298828, -0.81963794480456853, -0.82259566560190756,
      -0.82540861908604646, -0.82807561439984023, -0.83059550183885333,
      -0.83296717321155833, -0.83518956218563423, -0.83726164462023078,
      -0.8391824388840845, -0.84095100615939211, -0.84256645073131531,
      -0.8440279202630403, -0.84533460605628052, -0.84648574329714665,
      -0.84748061128729346, -0.84831853366026566, -0.84899887858297529,
      -0.84952105894223584, -0.84988453251629381, -0.85008880213130145,
      -0.85013341580267776, -0.85001796686131, -0.84974209406455592,
      -0.84930548169201092, -0.84870785962601181, -0.84794900341684232,
      -0.84702873433263692, -0.84594691939395372, -0.84470347139301749,
      -0.84329834889762179, -0.84173155623970042, -0.8400031434885693,
      -0.83811320640885179, -0.83606188640311307, -0.83384937043921847,
      -0.83147589096244578, -0.82894172579239678, -0.82624719800473534,
      -0.82339267579779729, -0.82037857234413991, -0.81720534562706315,
      -0.81387349826218292, -0.810383577304113, -0.80673617403833131,
      -0.80293192375830613, -0.79897150552797025, -0.79485564192961822,
      -0.79058509879733629, -0.78616068493604763, -0.78158325182628874,
      -0.77685369331481335, -0.7719729452911489, -0.76694198535021407,
      -0.76176183244112849, -0.756433546502332, -0.75095822808316548,
      -0.74533701795202489, -0.73957109669125609, -0.73366168427892631,
      -0.72761003965761639, -0.72141746029040887, -0.71508528170422081,
      -0.70861487702064685, -0.70200765647448926, -0.69526506692014312,
      -0.68838859132602193, -0.68137974825719838, -0.67424009134645979,
      -0.66697120875395166, -0.65957472261562811, -0.65205228848068975,
      -0.64440559473821668, -0.636636362033214, -0.62874634267226748,
      -0.620737320019033, -0.612611107879776, -0.60436954987917835,
      -0.596014518826649, -0.5875479160733541, -0.57897167086021262,
      -0.57028773965707269, -0.56149810549333856, -0.55260477728025359,
      -0.54360978912511493, -0.534515199637646, -0.52532309122878607,
      -0.51603556940215412, -0.506654762038435, -0.49718281867294023,
      -0.48762190976662967, -0.47797422597081918, -0.46824197738588091,
      -0.45842739281416023, -0.44853271900741887, -0.43856021990904703,
      -0.42851217589133495, -0.41839088298806304, -0.40819865212270212,
      -0.39793780833249626, -0.38761068998870596, -0.37721964801328584,
      -0.36676704509230484, -0.35625525488635124, -0.34568666123825642,
      -0.33506365737836841, -0.32438864512771148, -0.31366403409928495,
      -0.30289224089780126, -0.29207568831816066, -0.28121680454292014,
      -0.27031802233908858, -0.25938177825449682, -0.24841051181406537,
      -0.23740666471622746, -0.22637268002982411, -0.21531100139174242,
      -0.20422407220559649, -0.19311433484172713, -0.18198422983882126,
      -0.17083619510742529, -0.15967266513566217, -0.14849607019739167,
      -0.13730883556315759, -0.126113380714154, -0.11491211855953101,
      -0.10370745465728798, -0.09250178643906444, -0.081297502439085068,
      -0.070096981527549729, -0.058902592148732127, -0.047716691564067659,
      -0.036541625100501768, -0.025379725404371264, -0.014233311701070783,
      -0.003104689060794058, 0.0080038523294123226, 0.019090037886996425,
      0.030151609348414071, 0.041186325476538388, 0.052191962760713972,
      0.0631663161092107, 0.074107199533819557, 0.085012446826362748,
      0.095879912226852909, 0.10670747108308423, 0.11749302050140542,
      0.12823447998844925, 0.13892979208359094, 0.14957692298190045,
      0.16017386314737717, 0.17071862791624387, 0.18120925809008595,
      0.19164382051862164, 0.20202040867189835, 0.21233714320171976,
      0.22259217249208582, 0.23278367319847043, 0.2429098507757308,
      0.25296893999446257, 0.26295920544564333, 0.27287894203333507,
      0.28272647545532792, 0.29250016267151346, 0.30219839235984647,
      0.31181958535972554, 0.32136219510263753, 0.33082470802991215,
      0.34020564399745334, 0.34950355666728672, 0.35871703388580412,
      0.36784469804855319, 0.37688520645148044, 0.3858372516284585,
      0.39469956167502529, 0.4034709005581929, 0.41215006841223811,
      0.4207359018203673, 0.42922727408215305, 0.43762309546666567,
      0.44592231345120437, 0.454123912945551, 0.46222691650167153,
      0.47023038450879556, 0.47813341537381748, 0.48593514568694263,
      0.49363475037255128, 0.50123144282521082, 0.50872447503080021,
      0.51611313767273048, 0.52339676022319215, 0.530574711019441,
      0.53764639732508013, 0.54461126537634019, 0.55146880041332957,
      0.55821852669627536, 0.56486000750673737, 0.57139284513382038,
      0.57781668084538462, 0.58413119484428366, 0.59033610620964949,
      0.59643117282326541, 0.60241619128104484, 0.60829099678967924,
      0.61405546304848369, 0.61970950211651366, 0.62525306426498828,
      0.6306861378151063, 0.636008748961304, 0.64122096158005681,
      0.64632287702426727, 0.651314633903368, 0.65619640784919653,
      0.66096841126775729, 0.66563089307696521, 0.67018413843048874,
      0.67462846842778279, 0.6789642398104565, 0.68319184464507687,
      0.68731170999255209, 0.691324297564213, 0.69523010336474456,
      0.69902965732210054, 0.70272352290455542, 0.70631229672504126,
      0.70979660813293322, 0.71317711879344159, 0.71645452225477846,
      0.71962954350327191, 0.72270293850660239, 0.7256754937453489,
      0.7285480257330168, 0.73132138052474938, 0.733996433214916,
      0.73657408742376584, 0.73905527477336441, 0.74144095435300172,
      0.74373211217430057, 0.7459297606162294, 0.74803493786023711,
      0.75004870731574314, 0.7519721570361908, 0.7538063991259174,
      0.75555256913804336, 0.75721182546365928, 0.75878534871250158,
      0.76027434108540293, 0.76168002573874161, 0.76300364614113991,
      0.76424646542267927, 0.76540976571686858, 0.76649484749563812,
      0.76750302889761757, 0.76843564504995765, 0.76929404738396578,
      0.77007960294482714, 0.770793693695677, 0.77143771581629861,
      0.77201307899673144, 0.77252120572605887, 0.77296353057665046,
      0.77334149948416053, 0.77365656902354052, 0.7739102056813747,
      0.77410388512481143, 0.774239091467378, 0.77431731653197744,
      0.77434005911135539, 0.774308824226318, 0.77422512238201047,
      0.77409046882254251, 0.77390638278425106, 0.7736743867479039,
      0.77339600569013234, 0.773072766334399, 0.77270619640178506,
      0.77229782386191137, 0.77184917618426363, 0.7713617795902572,
      0.77083715830629651, 0.77027683381816181, 0.76968232412699655,
      0.76905514300720146, 0.768396799266537, 0.76770879600870923,
      0.76699262989876016, 0.76624979043153207, 0.7654817592035148,
      0.76469000918836083, 0.763876004016358, 0.76304119725815522,
      0.7621870317130135, 0.761314938701898, 0.76042633736565413,
      0.759522633968594, 0.758605221207743, 0.7576754775280381,
      0.75673476644375859, 0.75578443586644917, 0.754825817439634,
      0.75386022588055979, 0.75288895832926406, 0.75191329370521931,
      0.750934492071818, 0.74995379400896212, 0.74897241999400765,
      0.74799156979133163, 0.74701242185075023, 0.74603613271506442,
      0.745063836436955, 0.74409664400547648, 0.74313564278239475,
      0.74218189594858719, 0.74123644196075422, 0.7403002940186606,
      0.73937443954312354, 0.7384598396649793, 0.737557428725242,
      0.73666811378665642, 0.73579277415686128, 0.73493226092336794,
      0.73408739650054744, 0.7332589741888178, 0.73244775774623772,
      0.73165448097267194, 0.73087984730672284, 0.73012452943560668,
      0.72938916891812522, 0.72867437582093708, 0.72798072836824712,
      0.72730877260511273, 0.72665902207448152, 0.72603195750813887,
      0.7254280265316897, 0.7248476433837131, 0.72429118864923048,
      0.72375900900759782, 0.72325141699496154, 0.72276869078138051,
      0.7223110739627272, 0.721878775367478, 0.72147196887848253,
      0.72109079326981629, 0.72073535205879469, 0.72040571337323844,
      0.72010190983406241, 0.71982393845326, 0.71957176054735328,
      0.71934530166635136, 0.71914445153830475, 0.71896906402945393,
      0.718818957120066, 0.71869391289595685, 0.71859367755575043,
      0.71851796143388558, 0.71846643903940177, 0.71843874911050609,
      0.71843449468492981, 0.71845324318607728, 0.71849452652496648,
      0.71855784121792809, 0.71864264852007842, 0.71874837457451357,
      0.71887441057720625, 0.71902011295757973, 0.719184803574695,
      0.71936776992902285, 0.71956826538974339, 0.7197855094374962,
      0.72001868792254964, 0.72026695333828261, 0.720529425109921,
      0.72080518989844922, 0.72109330191958776, 0.72139278327775935,
      0.7217026243149427, 0.72202178397430017, 0.72234919017845756,
      0.72268374022234916, 0.72302430118047245, 0.72336971032843989,
      0.72371877557868491, 0.72407027593019313, 0.72442296193209621,
      0.72477555616099643, 0.72512675371184021, 0.72547522270220965,
      0.72581960478983154, 0.72615851570315959, 0.72649054578483263,
      0.72681426054783027, 0.72712820124414668, 0.72743088544577894,
      0.72772080763782954, 0.72799643982353346, 0.72825623214098623,
      0.72849861349137679, 0.72872199217848355, 0.72892475655924116,
      0.72910527570512507, 0.7292619000741436, 0.72939296219318339,
      0.7294967773504818, 0.7295716442979765, 0.72961584596329132,
      0.72962765017108577, 0.72960531037354248, 0.72954706638970235,
      0.729451145153411, 0.729315761469578, 0.72913911877851212,
      0.72891940992802429, 0.7286548179530552, 0.72834351686250209,
      0.72798367243300666, 0.72757344300938143, 0.72711098031140553,
      0.72659443024667314, 0.7260219337292263, 0.72539162750364983,
      0.7247016449743312, 0.72395011703959444, 0.72313517293038088,
      0.72225494105317622, 0.72130754983688439, 0.72029112858331024,
      0.719203808320953, 0.71804372266179373, 0.71680900866074881,
      0.71549780767746141, 0.714108266240143, 0.71263853691109857,
      0.7110867791536345, 0.70945116020002108, 0.70772985592017457,
      0.70592105169074082, 0.7040229432642422, 0.70203373763796706,
      0.69995165392224945, 0.697774924207852, 0.69550179443207394,
      0.69313052524327479, 0.69065939286349, 0.68808668994878441,
      0.68541072644703771, 0.68262983045281389, 0.67974234905897946,
      0.67674664920476157, 0.67364111851989472, 0.67042416616454936,
      0.66709422366467985, 0.66364974574250568, 0.66008921114177332,
      0.6564111234474761, 0.65261401189972157, 0.64869643220141171,
      0.64465696731942157, 0.64049422827895819, 0.63620685495076845,
      0.63179351683091411, 0.62725291381276238, 0.62258377695090927,
      0.61778486921670384, 0.61285498624509638, 0.60779295707248082,
      0.60259764486523815, 0.59726794763868629, 0.59180279896613852,
      0.58620116867778149, 0.58046206354907426, 0.57458452797838577,
      0.56856764465359677, 0.56241053520736406, 0.55611236086081117,
      0.54967232305531488, 0.543089664072173, 0.53636366763985655,
      0.52949365952859817, 0.52247900813205128, 0.51531912503577226,
      0.50801346557227367, 0.50056152936241771, 0.49296286084286434,
      0.48521704977941149, 0.47732373176592441, 0.46928258870867634,
      0.46109334929584184, 0.45275578945196793, 0.44426973277716192,
      0.43563505097083949, 0.42685166423977716, 0.41791954169031675,
      0.40883870170451597, 0.39960921230005042, 0.39023119147368313,
      0.38070480752815061, 0.37103027938226596, 0.36120787686409905,
      0.35123792098705442, 0.34112078420870762, 0.33085689067224644,
      0.32044671643038058, 0.30989078965158195, 0.29918969080851937,
      0.28834405284858033, 0.27735456134633762, 0.26622195463789577,
      0.2549470239369358, 0.24353061343244781, 0.2319736203679903,
      0.22027699510243104, 0.20844174115206454, 0.19646891521405585,
      0.18435962717111207, 0.17211504007737416, 0.15973637012539429,
      0.14722488659424726, 0.13458191177865306, 0.12180882089913608,
      0.10890704199314011, 0.0958780557871311, 0.082723395549641587,
      0.069444646925246378, 0.056043447749497211, 0.0425214878447846,
      0.028880508797172022, 0.015122303714212082, 0.00124871696375356,
      -0.012738356106202997, -0.026836969466574712, -0.0410451267251416,
      -0.055360781463307807, -0.069781837591645912, -0.084306149724116819,
      -0.09893152357092172, -0.11365571634989885, -0.12847643721637569,
      -0.14339134771137557, -0.15839806222811303, -0.17349414849660916,
      -0.18867712808639486, -0.20394447692710316, -0.21929362584687684,
      -0.23472196112843297, -0.25022682508267385, -0.26580551663965718,
      -0.28145529195680163, -0.29717336504418224, -0.31295690840669887,
      -0.32880305370301582, -0.34470889242104336, -0.360671476569799,
      -0.376687819387451, -0.39275489606536879, -0.4088696444879466,
      -0.42502896598803452, -0.44122972611770672, -0.45746875543422932,
      -0.47374285030090985, -0.49004877370268274, -0.50638325607612922,
      -0.52274299615374342, -0.539124661822151, -0.55552489099407842,
      -0.57194029249375067, -0.58836744695554133, -0.60480290773551371,
      -0.62124320183565729, -0.63768483084049132, -0.65412427186578692,
      -0.67055797851909948, -0.68698238187181737, -0.70339389144246656,
      -0.71978889619090736, -0.73616376552318852, -0.75251485030669318,
      -0.76883848389529408, -0.785130983164175, -0.8013886495540441,
      -0.8176077701243486, -0.83378461861521824, -0.84991545651775335,
      -0.865996534152387, -0.88202409175490792, -0.89799436056984794,
      -0.91390356395088035, -0.92974791846785876, -0.945523635020169,
      -0.9612269199560306, -0.97685397619736258, -0.99240100436991341,
      -1.0078642039382206, -1.0232397743450896, -1.0385239161551807,
      -1.0537128322023785, -1.0688027287405264, -1.0837898165971775,
      -1.0986703123299963, -1.1134404393853854, -1.1280964292590245,
      -1.1426345226578862, -1.1570509706633618, -1.1713420358951372,
      -1.1855039936754039, -1.1995331331930319, -1.2134257586673203,
      -1.2271781905109338, -1.2407867664916568, -1.25424784289254,
      -1.2675577956700927, -1.2807130216100993, -1.2937099394807072,
      -1.3065449911823519, -1.3192146428941942, -1.3317153862166056,
      -1.3440437393093991, -1.3561962480253522, -1.3681694870386705,
      -1.3799600609679987, -1.3915646054936095, -1.4029797884683606,
      -1.4142023110220734, -1.4252289086589325, -1.43605635234753,
      -1.4466814496031888, -1.4571010455621964, -1.4673120240475541,
      -1.4773113086258891, -1.4870958636551743, -1.4966626953228543,
      -1.5060088526740663, -1.5151314286295376, -1.5240275609928675,
      -1.5326944334467802, -1.5411292765380331, -1.549329368650632,
      -1.5572920369669934, -1.5650146584167186, -1.5724946606126518,
      -1.5797295227738768, -1.5867167766353329, -1.5934540073437065,
      -1.5999388543393007, -1.6061690122235361, -1.6121422316118073,
      -1.61785631997134, -1.62330914244378, -1.6284986226521982,
      -1.6334227434922124, -1.6380795479069505, -1.64246713964555,
      -1.6465836840049262, -1.6504274085545232, -1.6539966038437859,
      -1.6572896240920838, -1.6603048878608206, -1.663040878707484,
      -1.6654961458213793, -1.6676693046408042, -1.6695590374514353,
      -1.6711640939656807, -1.6724832918827814, -1.6735155174294332,
      -1.6742597258807344, -1.6747149420612253, -1.6748802608258346,
      -1.6747548475205307, -1.6743379384224957, -1.6736288411596303,
      -1.6726269351092191, -1.6713316717755873, -1.6697425751465849,
      -1.6678592420287377, -1.6656813423609282, -1.6632086195064468,
      -1.6604408905232959, -1.657378046412604, -1.6540200523450315,
      -1.6503669478650653, -1.6464188470730776, -1.6421759387850594,
      -1.6376384866699349, -1.6328068293643654, -1.627681380564967,
      -1.6222626290978845, -1.6165511389656264, -1.6105475493711341,
      -1.6042525747190304, -1.5976670045939896, -1.590791703716212,
      -1.5836276118739696, -1.5761757438332031, -1.5684371892241677,
      -1.5604131124051046, -1.5521047523029576, -1.5435134222311453,
      -1.5346405096843996, -1.5254874761106925, -1.5160558566603135,
      -1.5063472599120888, -1.4963633675768446, -1.4861059341781298,
      -1.475576786710286, -1.4647778242739242, -1.4537110176888954,
      -1.4423784090848248, -1.430782111469334, -1.418924308274008,
      -1.4068072528782629, -1.3944332681111991, -1.381804745731573,
      -1.3689241458860104, -1.3557939965456189, -1.3424168929211193,
      -1.3287954968566746, -1.3149325362025395, -1.300830804166744,
      -1.2864931586459458, -1.2719225215356489, -1.2571218780199771,
      -1.2420942758411908, -1.2268428245491547, -1.2113706947309559,
      -1.1956811172209032, -1.1797773822911015, -1.163662838822868,
      -1.1473408934591871, -1.1308150097384719, -1.1140887072098695,
      -1.0971655605303616, -1.0800491985439189, -1.062743303343004,
      -1.0452516093126341, -1.0275779021573561, -1.0097260179113645,
      -0.991699841932066, -0.97350330787740336, -0.95514039666722383,
      -0.93661513542899133, -0.91793159642819033, -0.8990938959836855,
      -0.88010619336841467, -0.86097268969570373, -0.84169762679156745,
      -0.82228528605329643, -0.80273998729472451, -0.7830660875784663,
      -0.76326798003552088, -0.7433500926726031, -0.72331688716750064,
      -0.70317285765290272, -0.6829225294890271, -0.66257045802541481,
      -0.64212122735229837, -0.62157944904188678, -0.600949760879991,
      -0.58023682558836631, -0.559445329538132, -0.53857998145471475,
      -0.51764551111467749, -0.49664666803485247, -0.4755882201541779,
      -0.45447495250864811, -0.43331166589976278, -0.41210317555695247,
      -0.39085430979430147, -0.36956990866206818, -0.34825482259338258,
      -0.32691391104654366, -0.30555204114334222, -0.28417408630383978,
      -0.26278492487802319, -0.24138943877477909, -0.21999251208856352,
      -0.19859902972428081, -0.17721387602072308, -0.15584193337305519,
      -0.13448808085475319, -0.11315719283942741, -0.0918541376229793,
      -0.0705837760465039, -0.049350960120410459, -0.0281605316501322,
      -0.0070173208639203871, 0.014073854956877123, 0.035108192844610343,
      0.056080905508761734, 0.076987222695604957, 0.097822392543634867,
      0.11858168293433335, 0.13926038283789918, 0.15985380365342769,
      0.18035728054319949, 0.20076617376058398, 0.22107586997118567,
      0.24128178356679425, 0.26137935797170525, 0.28136406694102178,
      0.3012314158505135, 0.32097694297760893, 0.34059622077313284,
      0.36008485712335664, 0.37943849660198814, 0.39865282171168109,
      0.4177235541146736, 0.43664645585215245, 0.455417330551955,
      0.47403202462426153, 0.49248642844480878, 0.51077647752533006,
      0.52889815367079385, 0.546847486123104, 0.56462055269085221,
      0.58221348086481428, 0.59962244891875238, 0.61684368699527892,
      0.63387347817632156, 0.65070815953791228, 0.66734412318892966,
      0.68377781729349041, 0.70000574707661123, 0.71602447581287554,
      0.731830625797719, 0.74742087930109613, 0.76279197950313593,
      0.7779407314115635, 0.79286400276052116, 0.80755872489055169,
      0.82202189360943012, 0.83625057003355852, 0.85024188140968238,
      0.86399302191661942, 0.87750125344678831, 0.89076390636723479,
      0.90377838025993729, 0.9165421446411488, 0.92905273965953361,
      0.94130777677285848, 0.95330493940305683, 0.96504198356939841,
      0.97651673849961929, 0.9877271072187479, 0.99867106711548226,
      1.0093466704859098, 1.0197520450544042, 1.029885394471511,
      1.0397449987886855, 1.0493292149096867, 1.058636477018529,
      1.0676652969838063, 1.0764142647392771, 1.0848820486405817,
      1.0930673957979706, 1.1009691323849367, 1.1085861639226413,
      1.1159174755400578, 1.1229621322097212, 1.1297192789590138,
      1.1361881410569374, 1.1423680241762662, 1.1482583145310654,
      1.1538584789895043, 1.1591680651619363, 1.1641867014641984,
      1.1689140971561431, 1.1733500423553371, 1.1774944080259595,
      1.1813471459428859, 1.1849082886309668, 1.1881779492795175,
      1.1911563216320491, 1.1938436798512693, 1.1962403783593922,
      1.1983468516538234, 1.2001636140982428, 1.2016912596891938,
      1.20293046179821, 1.2038819728896033, 1.2045466242139615,
      1.2049253254774819, 1.205019064487229, 1.2048289067724427,
      1.2043559951820075, 1.203601549458212, 1.2025668657869462,
      1.201253316324455, 1.1996623487008415, 1.1977954855004318,
      1.1956543237192014, 1.1932405341994254, 1.1905558610417366,
      1.1876021209947765, 1.1843812028226428, 1.1808950666503319,
      1.1771457432873871, 1.1731353335299792, 1.1688660074416291,
      1.1643400036128213, 1.1595596283997329, 1.1545272551423373,
      1.1492453233621249, 1.14371633793971, 1.1379428682725738,
      1.1319275474132382, 1.1256730711881255, 1.1191821972974185,
      1.1124577443961843, 1.1055025911570633, 1.0983196753148539,
      1.0909119926932707, 1.0832825962142092, 1.0754345948898292,
      1.0673711527977989, 1.0590954880400019, 1.0506108716850961,
      1.0419206266952044, 1.0330281268371326, 1.0239367955784597,
      1.0146501049688421, 1.0051715745069096, 0.99550476999311732,
      0.9856533023689219, 0.975620826542682, 0.9654110402026137,
      0.95502768261726, 0.94447453342378374, 0.933755411404545,
      0.9228741732523279, 0.91183471232461732, 0.90064095738734662,
      0.88929687134850688, 0.87780644998204949, 0.86617372064247289,
      0.8544027409705357, 0.84249759759050824, 0.8304624047993685,
      0.81830130324841277, 0.80601845861765, 0.793618060283472,
      0.78110431997999075, 0.76848147045448956, 0.75575376411743644,
      0.74292547168749024, 0.73000088083193826, 0.71698429480300907,
      0.70388003107050867, 0.6906924199512221, 0.67742580323553181,
      0.66408453281168611, 0.65067296928816887, 0.63719548061464071,
      0.62365644070186943, 0.61006022804111815, 0.59641122432343685,
      0.58271381305928849, 0.568972378198993, 0.55519130275442108,
      0.54137496742235192, 0.5275277492100181, 0.51365402006320937,
      0.49975814549742537, 0.48584448323250568, 0.47191738183119408,
      0.45798117934204852, 0.44404020194719523, 0.43009876261528757,
      0.41616115976018042, 0.40223167590571945, 0.3883145763570755,
      0.37441410787906992, 0.36053449738191995, 0.34667995061480711,
      0.33285465086774346, 0.31906275768207554, 0.30530840557013289,
      0.2915957027443763, 0.27792872985648009, 0.26431153874675567,
      0.25074815120430721, 0.23724255773834638, 0.22379871636103815,
      0.21042055138229895, 0.19711195221689787, 0.18387677220428011,
      0.17071882744148875, 0.15764189562954911, 0.14464971493369549,
      0.13174598285780584, 0.11893435513340631, 0.10621844462362562,
      0.0936018202423946, 0.081088005889314418, 0.06868047940047517,
      0.056382671515598948, 0.044197964861812267, 0.032129692954397049,
      0.020181139214827226, 0.0083555360064172524, -0.0033439363121429144,
      -0.014914150315001595, -0.026352032418875904, -0.037654563773959926,
      -0.048818781135765654, -0.059841777717584421, -0.0707207040233232,
      -0.081452768660428276, -0.092035239132668922, -0.10246544261250118,
      -0.11274076669278105, -0.12285866011758345, -0.13281663349190753,
      -0.14261225997003346, -0.15224317592232417, -0.16170708158024483,
      -0.17100174165942961, -0.18012498596057314, -0.1890747099479726,
      -0.19784887530553702, -0.20644551047010212, -0.21486271114187117,
      -0.22309864077183272, -0.23115153102601244, -0.23901968222640713,
      -0.24670146376848207, -0.25419531451508748, -0.26149974316669117,
      -0.26861332860781578, -0.27553472022958059, -0.28226263822824149,
      -0.28879587387965938, -0.29513328978962172, -0.30127382011992504,
      -0.30721647079018954, -0.31296031965532106, -0.31850451665860807,
      -0.3238482839603804, -0.3289909160422404, -0.33393177978681671,
      -0.33867031453303847, -0.34320603210693335, -0.3475385168279469,
      -0.3516674254907915, -0.35559248732285609, -0.35931350391719941,
      -0.36283034914116741, -0.36614296902067434, -0.36925138160020932,
      -0.37215567677862577, -0.37485601612078445, -0.37735263264512775,
      -0.3796458305872637, -0.38173598513967849, -0.383623542167646,
      -0.38530901790147354, -0.386792998605173, -0.38807614022172665,
      -0.38915916799502576, -0.39004287606867277, -0.39072812706176296,
      -0.39121585162182654, -0.39150704795507718, -0.39160278133415094,
      -0.39150418358351124, -0.391212452542706, -0.39072885150767867,
      -0.39005470865032343, -0.38919141641649768, -0.38814043090273165,
      -0.38690327121180978, -0.38548151878750986, -0.38387681672868335,
      -0.38209086908298062, -0.38012544012041971, -0.37798235358708565,
      -0.37566349193921467, -0.3731707955579443, -0.37050626194500247,
      -0.36767194489960625, -0.36466995367688304, -0.36150245212810794,
      -0.35817165782303195, -0.35467984115465823, -0.35102932442672841,
      -0.34722248092428187, -0.34326173396759352, -0.33914955594982094,
      -0.33488846735870448, -0.3304810357826638, -0.32592987490163194,
      -0.32123764346297889, -0.31640704424290078, -0.31144082299360726,
      -0.30634176737668806, -0.3011127058830495, -0.29575650673976328,
      -0.29027607680423195, -0.28467436044604738, -0.27895433841693085,
      -0.27311902670914789, -0.26717147540279995, -0.26111476750238932,
      -0.25495201776304754, -0.24868637150687148, -0.24232100342973073,
      -0.23585911639899693, -0.22930394024259595, -0.22265873052979793,
      -0.21592676734418964, -0.20911135404921904, -0.20221581604676506,
      -0.19524349952917514, -0.18819777022514872, -0.18108201213996492,
      -0.17389962629044325, -0.16665402943509705, -0.15934865279990576,
      -0.15198694080016423, -0.14457234975882713, -0.13710834662180849,
      -0.12959840767068267, -0.1220460172331997, -0.11445466639210197,
      -0.10682785169266823, -0.0991690738494164, -0.0914818364524523,
      -0.083769644673837781, -0.07603600397452448, -0.068284418812204761,
      -0.060518391350578592, -0.052741420170474083, -0.04495699898323758,
      -0.037168615346883677, -0.029379749385401, -0.02159387251167906,
      -0.013814446154502558, -0.0060449204900216991, 0.0017112668218314114,
      0.0094506918955696573, 0.0171699458725678, 0.024865636167269847,
      0.032534387706717433, 0.0401728441630006, 0.047777669178212967,
      0.055345547581450591, 0.062873186597493441, 0.070357317046700729,
      0.077794694535739, 0.085182100638726874, 0.09251634406837704,
      0.099794261836764542, 0.107012720405285, 0.1141686168234331,
      0.12125887985599829, 0.12828047109829735, 0.13523038607905474,
      0.14210565535055988, 0.14890334556571674, 0.15562056054161605,
      0.16225444230928657, 0.16880217214923032, 0.17526097161240919,
      0.18162810352633449, 0.18790087298589134, 0.19407662832858849,
      0.2001527620938732, 0.20612671196619131, 0.21199596170147358,
      0.21775804203672261, 0.22341053158239321, 0.22895105769725185,
      0.23437729734542956, 0.23968697793535448, 0.2448778781402941,
      0.24994782870021337, 0.25489471320468921, 0.25971646885658017,
      0.26441108721622675, 0.26897661492590896, 0.27341115441431135,
      0.2777128645807474, 0.28187996145893152, 0.28591071886005065,
      0.28980346899491338, 0.29355660307497988, 0.29716857189204987,
      0.300637886376421, 0.30396311813330873, 0.30714289995736815,
      0.31017592632512853, 0.31306095386515731, 0.31579680180581748,
      0.31838235240044849, 0.32081655132983339, 0.323098408081798,
      0.32522699630783181, 0.32720145415659918, 0.32902098458421858,
      0.33068485564121464, 0.33219240073603756, 0.333543018875066,
      0.33473617487899465, 0.33577139957555463, 0.33664828996848251,
      0.33736650938268536, 0.33792578758555053, 0.33832592088436231,
      0.338566772199786, 0.33864827111539414, 0.33857041390322257,
      0.33833326352534238, 0.33793694961144088, 0.33738166841243716,
      0.33666768273012831, 0.33579532182289235, 0.33476498128749849,
      0.33357712291703495, 0.33223227453502957, 0.33073102980579777,
      0.32907404802110091, 0.32726205386317431, 0.32529583714420368,
      0.3231762525223591, 0.3209042191944555, 0.31848072056535714,
      0.31590680389425568, 0.31318357991790019, 0.31031222245095291,
      0.30729396796357622, 0.30413011513641014, 0.30082202439308836,
      0.29737111741044525, 0.29377887660658686, 0.29004684460701541,
      0.28617662368895747, 0.2821698752041048, 0.27802831897997593,
      0.27375373270007358, 0.26934795126308231, 0.26481286612129318,
      0.26015042459850141, 0.25536262918761993, 0.25045153682821741,
      0.24541925816424121, 0.24026795678220864, 0.23499984843007654,
      0.22961720021708443, 0.2241223297948452, 0.218517604519968,
      0.21280544059847928, 0.20698830221232667, 0.2010687006283392,
      0.19504919328983383, 0.18893238289126818, 0.18272091643622856,
      0.17641748427906062, 0.17002481915049142, 0.16354569516755885,
      0.156982926828215, 0.15033936799091127, 0.1436179108395351,
      0.13682148483405263, 0.12995305564722931, 0.12301562408775751,
      0.11601222501016456, 0.10894592621194432, 0.1018198273181769,
      0.094637058654120088, 0.087400780106079323, 0.080114179971019051,
      0.072780473795253015, 0.0654029032026329, 0.057984734712635391,
      0.050529258548778433, 0.043039787437713556, 0.035519655399468081,
      0.027972216529223021, 0.020400843771045452, 0.012808927684003768,
      0.0051998752010767035, -0.0024228916186908034, -0.010055936844392738,
      -0.017695811933384882, -0.025339056996856561, -0.032982202070481824,
      -0.0406217683896721, -0.048254269668980235, -0.055876213385255891,
      -0.063484102064090844, -0.071074434569087241, -0.078643707393591541,
      -0.0861884159543033, -0.093705055886467756, -0.10119012434012692,
      -0.10864012127695705, -0.11605155076733316, -0.12342092228709667,
      -0.13074475201362357, -0.13801956412070887, -0.14524189207185634,
      -0.15240827991154873, -0.15951528355395261, -0.16655947206872965,
      -0.17353742896346944, -0.18044575346224184, -0.18728106177993797,
      -0.19403998839186959, -0.20071918729823646, -0.20731533328298915,
      -0.21382512316670585, -0.2202452770529888, -0.22657253956799683,
      -0.23280368109264488, -0.23893549898708952, -0.24496481880705498,
      -0.25088849551154546, -0.25670341466158381, -0.26240649360953722,
      -0.26799468267858734, -0.27346496633200035, -0.27881436433171441,
      -0.28403993288592255, -0.28913876578517234, -0.294107995526647,
      -0.29894479442622279, -0.30364637571789993, -0.30820999464022469,
      -0.3126329495093606, -0.31691258277836515, -0.32104628208241093,
      -0.32503148126944253, -0.3288656614160379, -0.33254635182806963,
      -0.33607113102578068, -0.33943762771298225, -0.34264352173003554,
      -0.34568654499022539, -0.34856448239925486, -0.35127517275752429,
      -0.35381650964484762, -0.3561864422873402, -0.35838297640613503,
      -0.36040417504763339, -0.36224815939504407, -0.36391310956082579,
      -0.36539726535986072, -0.36669892706300755, -0.36781645613080116,
      -0.3687482759270248, -0.36949287241191131, -0.37004879481470709,
      -0.37041465628537895, -0.37058913452520925, -0.37057097239607689,
      -0.37035897850817467, -0.36995202778596648, -0.36934906201219264,
      -0.36854909034967986, -0.367551189840834, -0.36635450588455709,
      -0.36495825269045812, -0.36336171371019554, -0.36156424204575544,
      -0.35956526083452844, -0.35736426361106577, -0.35496081464532259,
      -0.35235454925732307, -0.34954517410806646, -0.34653246746658195,
      -0.34331627945306631, -0.33989653225793109, -0.33627322033671919,
      -0.33244641058081265, -0.32841624246382289, -0.32418292816363631,
      -0.31974675266001518, -0.31510807380775241, -0.31026732238530391,
      -0.305225002118871, -0.29998168968191158, -0.294538034670088,
      -0.28889475955158506, -0.28305265959285414, -0.27701260275976886,
      -0.27077552959419066, -0.26434245306601289, -0.25771445840066337,
      -0.25089270288215149, -0.24387841563168827, -0.23667289736190883,
      -0.22927752010683117, -0.22169372692757455, -0.21392303159388354,
      -0.20596701824165625, -0.19782734100647981, -0.18950572363329188,
      -0.1810039590623243, -0.17232390899140404, -0.16346750341478694,
      -0.15443674013860487, -0.14523368427310013, -0.13586046770183591,
      -0.12631928852797225, -0.11661241049780557, -0.10674216240179135,
      -0.096710937453154122, -0.086521192644339218, -0.076175448081453934,
      -0.0656762862969581, -0.055026351540774177, -0.0442283490500367,
      -0.033285044297734045, -0.022199262220480465, -0.010973886425608648,
      0.00038814162212674752, 0.011883823433981533, 0.023510104350514927,
      0.035263874414561025, 0.047141969263486072, 0.059141171040504509,
      0.071258209324796151, 0.083489762080105723, 0.095832456621474216,
      0.10828287059988545, 0.12083753300446198, 0.13349292518191311,
      0.14624548187286765, 0.15909159226484215, 0.17202760106144363,
      0.18504980956749384, 0.19815447678969911, 0.21133782055258002,
      0.22459601862925346, 0.23792520988669058, 0.25132149544513893,
      0.26478093985132861, 0.27829957226502411, 0.29187338765861903,
      0.30549834802935688, 0.31917038362380246, 0.33288539417415874,
      0.34663925014598163, 0.3604277939970657, 0.37424684144687687,
      0.38809218275625723, 0.40195958401698051, 0.41584478845071693,
      0.42974351771699126, 0.44365147322971243, 0.45756433748188391,
      0.47147777537805785, 0.48538743557402697, 0.49928895182346655,
      0.51317794433098707, 0.52705002111117127, 0.54090077935319181,
      0.55472580679056915, 0.56852068307561576, 0.58228098115809146,
      0.59600226866769035, 0.60968010929988847, 0.62331006420466673,
      0.63688769337771356, 0.65040855705363365, 0.66386821710074906,
      0.67726223841696331, 0.690586190326293, 0.70383564797567955,
      0.71700619373148478, 0.73009341857532317, 0.74309292349875444,
      0.75600032089642344, 0.76881123595709411, 0.7815213080522373,
      0.79412619212167823, 0.80662156005587016, 0.81900310207429916,
      0.83126652809965584, 0.84340756912728287, 0.85542197858943447,
      0.86730553371396124, 0.879054036876944, 0.89066331694886935,
      0.90212923063386241, 0.9134476638015826, 0.9246145328113986,
      0.93562578582827338, 0.94647740413008274, 0.95716540340588141,
      0.96768583504466577, 0.97803478741432059, 0.98820838713014969,
      0.998202800312854, 1.0080142338352704, 1.0176389365576379,
      1.0270732005509704, 1.036313362308082, 1.0453558039419559,
      1.0541969543709537, 1.0628332904906208, 1.0712613383316458,
      1.0794776742035113, 1.0874789258236568, 1.0952617734316201,
      1.1028229508878771, 1.1101592467570178, 1.1172675053748817,
      1.1241446278993668, 1.1307875733444686, 1.137193359597352,
      1.1433590644179996, 1.1492818264212061, 1.1549588460405453,
      1.1603873864740111, 1.1655647746110869, 1.1704884019408162,
      1.1751557254407139, 1.1795642684461676, 1.183711621500025,
      1.1875954431821707, 1.1912134609187326, 1.1945634717707554,
      1.1976433432019689, 1.2004510138255284, 1.2029844941294054,
      1.2052418671801957, 1.2072212893051839, 1.2089209907523513,
      1.2103392763281906, 1.2114745260131088, 1.2123251955541412,
      1.2128898170349378, 1.2131669994226706, 1.2131554290918187,
      1.2128538703245679, 1.2122611657877431, 1.2113762369860537,
      1.210198084691535, 1.2087257893490659, 1.2069585114577781,
      1.2048954919283006, 1.2025360524156814, 1.1998795956278623,
      1.1969256056096835, 1.1936736480022321, 1.1901233702775222,
      1.18627450194839, 1.1821268547535642, 1.1776803228178285,
      1.1729348827872323, 1.1678905939393203, 1.162547598268318,
      1.1569061205452731, 1.1509664683531193, 1.1447290320966208,
      1.138194284987291, 1.131362783003159, 1.1242351648234754,
      1.1168121517384091, 1.1090945475336504, 1.1010832383500706,
      1.0927791925184178, 1.0841834603691283, 1.0752971740173018,
      1.0661215471229011, 1.0566578746262818, 1.0469075324591215,
      1.0368719772308008, 1.0265527458904, 1.0159514553644053,
      1.0050698021701892, 0.99390956200543545, 0.98247258931362735,
      0.97076081682575854, 0.95877625507835607, 0.94652099190800476,
      0.93399719192256636, 0.92120709594919858, 0.90815302045935009,
      0.8948373569710073, 0.8812625714282607, 0.867431203558469,
      0.853345866207172, 0.83900924465102111, 0.82442409588889276,
      0.80959324791143361, 0.79451959894924462, 0.77920611670002493,
      0.76365583753477839, 0.74787186568344866, 0.73185737240020665,
      0.71561559510867845, 0.69914983652726259, 0.68246346377501055,
      0.66555990745821247, 0.64844266073799539, 0.631115278379239,
      0.61358137578116612, 0.59584462798982329, 0.57790876869281049,
      0.55977758919655074, 0.5414549373864852, 0.52294471667043263,
      0.50425088490549363, 0.485377453308843, 0.46632848535275639,
      0.44710809564417, 0.42772044878913962, 0.40816975824266377,
      0.38846028514405329, 0.36859633713830448, 0.34858226718390584,
      0.32842247234733657, 0.30812139258470239, 0.28768350951084493,
      0.26711334515635465, 0.24641546071293358, 0.2255944552672573,
      0.204654964524034, 0.18360165951851404, 0.16243924531879433,
      0.14117245971842848, 0.11980607191971657, 0.0983448812080719,
      0.07679371561788717, 0.055157430590257253, 0.033440907623141336,
      0.011649052914178018, -0.010213204003334413, -0.032140911630795882,
      -0.054129097880694664, -0.0761727714585593, -0.09826692325003869,
      -0.12040652771266237, -0.14258654427188844, -0.16480191872101146,
      -0.18704758462445945, -0.20931846472403159, -0.23160947234774665,
      -0.25391551282079072, -0.27623148487809923, -0.29855228207815676,
      -0.32087279421775061, -0.3431879087469295, -0.36549251218397982,
      -0.38778149152991076, -0.41004973568201131, -0.43229213684604362,
      -0.45450359194661566, -0.476679004035391, -0.49881328369664379,
      -0.5209013504496649, -0.54293813414776659, -0.5649185763733009,
      -0.58683763182833726, -0.60869026972056262, -0.63047147514398838,
      -0.65217625045411065, -0.67379961663691612, -0.69533661467156893,
      -0.71678230688622269, -0.73813177830652477, -0.75938013799650372,
      -0.780522520391391, -0.80155408662198124, -0.8224700258301284,
      -0.84326555647492785, -0.86393592762939675, -0.88447642026701057,
      -0.90488234853783833, -0.9251490610339268, -0.94527194204352794,
      -0.96524641279374246, -0.98506793268127357, -1.0047320004909379,
      -1.0242341556015542, -1.0435699791788073, -1.0627350953548147,
      -1.0817251723940444, -1.1005359238451757, -1.1191631096786012,
      -1.1376025374093064, -1.1558500632047044, -1.1739015929771284,
      -1.1917530834607173, -1.2094005432723423, -1.2268400339562755,
      -1.2440676710122647, -1.2610796249068272, -1.2778721220673805,
      -1.2944414458589422, -1.3107839375431094, -1.3268959972191829,
      -1.3427740847469465, -1.358414720651004, -1.373814487006396,
      -1.3889700283052273, -1.4038780523040624, -1.4185353308518591,
      -1.4329387006982379, -1.4470850642818756, -1.4609713904987223,
      -1.4745947154499466, -1.4879521431693741, -1.5010408463301599,
      -1.513858066930609, -1.52640111695889, -1.5386673790365371,
      -1.5506543070404981, -1.56235942670361, -1.5737803361934015,
      -1.5849147066689584, -1.5957602828158097, -1.606314883358706,
      -1.6165764015520998, -1.6265428056482762, -1.6362121393429634,
      -1.6455825221984315, -1.6546521500438485, -1.6634192953528841,
      -1.6718823075985019, -1.6800396135848195, -1.6878897177559822,
      -1.6954312024820011, -1.7026627283215352, -1.7095830342615153,
      -1.7161909379336158, -1.722485335807546, -1.7284652033611274,
      -1.7341295952271492, -1.7394776453169918, -1.7445085669210334,
      -1.7492216527858626, -1.7536162751682354, -1.7576918858659267,
      -1.761448016225396, -1.7648842771263582, -1.7680003589433213,
      -1.7707960314840789, -1.7732711439052986, -1.7754256246052162,
      -1.7772594810935236, -1.7787727998385616, -1.7799657460918561,
      -1.7808385636901443, -1.7813915748349476, -1.7816251798498519,
      -1.7815398569155576, -1.7811361617828583, -1.7804147274636857,
      -1.7793762639003226, -1.7780215576129532, -1.7763514713256996,
      -1.7743669435712983, -1.7720689882745733, -1.7694586943148871,
      -1.766537225067752, -1.763305817925735, -1.7597657837989436,
      -1.7559185065951728, -1.7517654426799987, -1.747308120316994,
      -1.7425481390882782, -1.7374871692956173, -1.732126951342315,
      -1.7264692950961138, -1.7205160792333509, -1.714269250564578,
      -1.7077308233419419, -1.7009028785485574, -1.6937875631701071,
      -1.6863870894489539, -1.6787037341210453, -1.6707398376358473,
      -1.6624978033596254, -1.6539800967623093, -1.6451892445882805,
      -1.6361278340113317, -1.626798511774096, -1.6172039833122975,
      -1.6073470118640563, -1.5972304175646095, -1.5868570765267167,
      -1.57622991990713, -1.5653519329593666, -1.5542261540731959,
      -1.5428556738010675, -1.5312436338719384, -1.5193932261927068,
      -1.5073076918376516, -1.4949903200262609, -1.4824444470896754,
      -1.4696734554262278, -1.4566807724463053, -1.4434698695070076,
      -1.430044260836832, -1.4164075024508167, -1.4025631910565381,
      -1.388514962951183, -1.3742664929102406, -1.3598214930680028,
      -1.3451837117903915, -1.3303569325403755, -1.3153449727363815,
      -1.3001516826040982, -1.2847809440220139, -1.2692366693610651,
      -1.253522800318746, -1.2376433067481656, -1.2216021854822414,
      -1.2054034591536102, -1.1890511750104529, -1.1725494037287625,
      -1.1559022382213318, -1.1391137924438415, -1.12218820019855,
      -1.1051296139357536, -1.0879422035536293, -1.0706301551966142,
      -1.053197670052898, -1.0356489631512589, -1.0179882621576613,
      -1.0002198061720642, -0.98234784452568658, -0.96437663557921338,
      -0.94631044552221655, -0.92815354717428611, -0.90991021878810807,
      -0.89158474285491263, -0.8731814049127, -0.85470449235755441,
      -0.83615829325840452, -0.8175470951756042, -0.79887518398373714,
      -0.78014684269888224, -0.76136635031086763, -0.74253798062063958,
      -0.72366600108334955, -0.70475467165726768, -0.68580824365899951,
      -0.66683095862536934, -0.64782704718214446, -0.62880072792016706,
      -0.60975620627895732, -0.59069767343839819, -0.57162930521855793,
      -0.55255526098814456, -0.53347968258188938, -0.51440669322702315,
      -0.49534039647942552, -0.47628487516942625, -0.45724419035785069,
      -0.438222380302422, -0.41922345943484779, -0.4002514173489386,
      -0.38131021780000512, -0.36240379771577336, -0.34353606621911675,
      -0.32471090366295607, -0.30593216067741918, -0.28720365722970936,
      -0.26852918169677781, -0.24991248995116588, -0.23135730446019676,
      -0.21286731339874637, -0.19444616977592682, -0.17609749057575219,
      -0.15782485591217965, -0.13963180819858512, -0.12152185133205229,
      -0.10349844989250973, -0.085565028357046546, -0.067724970329566481,
      -0.049981617785932131, -0.032338270334862751, -0.01479818449464243,
      0.002635427014005931, 0.019959395958911885, 0.037170599271034666,
      0.054265959702452737, 0.071242446467712384, 0.088097075868295571,
      0.1048269119001598, 0.12142906684409599, 0.13790070183894898,
      0.15423902743735979, 0.17044130414417932, 0.1865048429371774,
      0.2024270057701531, 0.2182052060582812, 0.23383690914550548,
      0.24931963275411737, 0.26465094741619916, 0.279828476887065,
      0.29484989854047977, 0.30971294374570046, 0.32441539822628851,
      0.33895510240051252, 0.35332995170352549, 0.36753789689107036,
      0.38157694432482636, 0.39544515623931803, 0.40914065099036478,
      0.42266160328512536, 0.43600624439367336, 0.44917286234208315,
      0.46215980208715757, 0.4749654656727107, 0.48758831236742217,
      0.5000268587843838, 0.51227967898226523, 0.52434540454825218,
      0.53622272466267562, 0.54791038614551124, 0.55940719348473,
      0.57071200884657136, 0.58182375206787162, 0.59274140063040981,
      0.60346398961751158, 0.61399061165280622, 0.62432041682143435,
      0.63445261257364827, 0.6443864636109724, 0.65412129175507894,
      0.6636564757993656, 0.67299145134353922, 0.68212571061113758,
      0.69105880225027816, 0.6997903311177236, 0.7083199580463182,
      0.71664739959609347, 0.72477242778909368, 0.73269486982811216,
      0.740414607799493, 0.74793157836018342, 0.75524577240917057,
      0.76235723474355288, 0.76926606369933326, 0.77597241077718937,
      0.7824764802534151, 0.78877852877615939, 0.79487886494726034,
      0.80077784888978032, 0.806475891801534, 0.81197345549476507,
      0.8172710519222115, 0.82236924268979206, 0.82726863855609234,
      0.83196989891893458, 0.83647373128922453, 0.84078089075232409,
      0.84489217941717987, 0.84880844585347281, 0.8525305845169916,
      0.85605953516352618, 0.85939628225148512, 0.86254185433354125,
      0.86549732343751939, 0.86826380443679385, 0.87084245441049168,
      0.87323447199372717, 0.8754410967181433, 0.87746360834305337,
      0.87930332617741824, 0.88096160839296933, 0.88243985132872871,
      0.88373948878721809, 0.88486199132261345, 0.885808865521176,
      0.88658165327418215, 0.887181931043684, 0.88761130912137087,
      0.88787143088079912, 0.88796397202332811, 0.88789063981798688,
      0.8876531723356379, 0.88725333767765391, 0.886692933199454,
      0.88597378472918087, 0.88509774578178357, 0.88406669676884864,
      0.88288254420443868, 0.88154721990722984, 0.8800626801992818,
      0.87843090510170041, 0.87665389752748235, 0.87473368247187533,
      0.87267230620051528, 0.87047183543564022, 0.868134356540692,
      0.86566197470357187, 0.86305681311885762, 0.86032101216929646,
      0.85745672860679167, 0.8544661347332887, 0.85135141758170962,
      0.84811477809734592, 0.8447584303199418, 0.841284600566717,
      0.8376955266167081, 0.83399345689660653, 0.83018064966844518,
      0.82625937221938583, 0.82223190005385638, 0.81810051608838741,
      0.81386750984933043, 0.80953517667379327, 0.80510581691402061,
      0.80058173514552378, 0.79596523937917452, 0.79125864027757031,
      0.78646425037588985, 0.78158438330752267, 0.77662135303472357,
      0.77157747308449431, 0.76645505579001694, 0.76125641153782453,
      0.75598384802096041, 0.75063966949838012, 0.74522617606081809,
      0.7397456629033361, 0.734200419604818, 0.72859272941458664,
      0.72292486854641447, 0.71719910548008992, 0.71141770027079443,
      0.70558290386649958, 0.69969695743353366, 0.69376209169059755,
      0.68778052625137875, 0.68175446897595171, 0.6756861153312026,
      0.66957764776038653, 0.66343123506209289, 0.65724903177868832,
      0.65103317759453, 0.64478579674399084, 0.63850899742957157,
      0.63220487125019043, 0.62587549263980735, 0.61952291831660244,
      0.61314918674274566, 0.60675631759499138, 0.60034631124619331,
      0.59392114825786524, 0.58748278888395444, 0.5810331725858715,
      0.57457421755902349, 0.56810782027079965, 0.56163585501026758,
      0.55516017344959256, 0.54868260421729675, 0.54220495248348954,
      0.53572899955709419, 0.52925650249519651, 0.5227891937246163,
      0.51632878067569332, 0.50987694542844519, 0.50343534437111159,
      0.49700560787114939, 0.49058933995875664, 0.48418811802291717,
      0.47780349252010995, 0.471436986695593, 0.4650900963174085,
      0.45876428942308622, 0.45246100607903683, 0.44618165815276489,
      0.4399276290977514, 0.43370027375120251, 0.42750091814448643,
      0.42133085932639647, 0.41519136519916278, 0.40908367436721071,
      0.40300899599869489, 0.39696850969968572, 0.39096336540113646,
      0.3849946832584385, 0.37906355356364568, 0.37317103667027673,
      0.36731816293066238, 0.36150593264579878, 0.35573531602761682,
      0.35000725317366, 0.34432265405406792, 0.33868239851082155,
      0.33308733626916176, 0.32753828696111176, 0.32203604016103732,
      0.31658135543310617, 0.31117496239064879, 0.3058175607672321,
      0.30050982049940078, 0.29525238182097768, 0.29004585536881117,
      0.28489082229984397, 0.279787834419418, 0.27473741432068433,
      0.26974005553498259, 0.26479622269307529, 0.25990635169712856,
      0.255070849903255, 0.25029009631451393, 0.2455644417842531,
      0.24089420922957516, 0.23627969385485675, 0.23172116338512921,
      0.22721885830914845, 0.22277299213206178, 0.21838375163743184,
      0.21405129715852222, 0.20977576285861602, 0.205557257020249,
      0.20139586234316065, 0.19729163625076687, 0.19324461120503991,
      0.18925479502952855, 0.18532217124040795, 0.18144669938532387,
      0.17762831538988202, 0.173866931911563, 0.17016243870086112,
      0.16651470296950688, 0.16292356976549369, 0.1593888623547898,
      0.15591038260947693, 0.15248791140213608, 0.14912120900628426,
      0.14581001550261652, 0.14255405119091188, 0.13935301700731756,
      0.13620659494686033, 0.13311444849092774, 0.13007622303955793,
      0.12709154634826264, 0.12416002896921564, 0.12128126469656389,
      0.11845483101565592, 0.11568028955596754, 0.11295718654750078,
      0.11028505328044032, 0.10766340656784237, 0.10509174921115713,
      0.1025695704683206, 0.10009634652424587, 0.09767154096345676,
      0.095294605244648639, 0.092964979176983015, 0.090682091397840031,
      0.088445359851879957, 0.086254192271112112, 0.0841079866558325,
      0.082006131756144462, 0.0799480075538847, 0.077932985744711331,
      0.0759604302201653, 0.0740296975494392, 0.0721401374607071,
      0.070291093321734943, 0.06848190261958656, 0.066711897439231643,
      0.064980404940789466, 0.0632867478352733, 0.061630244858553979,
      0.060010211243375994, 0.058425959189229437, 0.056876798329825839,
      0.055362036198037451, 0.05388097868805089, 0.052432930514555692,
      0.051017195668781018, 0.049633077871161335, 0.048279881020460769,
      0.046956909639163436, 0.0456634693149206, 0.044398867137894649,
      0.043162412133815442, 0.041953415692539464, 0.040771191991970268,
      0.039615058417147353, 0.038484335974312833, 0.037378349699834945,
      0.036296429063767455, 0.035237908367906523, 0.03420212713819204,
      0.033188430511269018, 0.032196169615078207, 0.031224701943312116,
      0.03027339172357113, 0.029341610279124075, 0.028428736384060738,
      0.027534156611747851, 0.026657265676456043, 0.025797466767962018,
      0.024954171879088938, 0.024126802125975733, 0.023314788061003011,
      0.022517569978244445, 0.021734598211314904, 0.020965333423527466,
      0.020209246890229238, 0.019465820773230447, 0.018734548387206174,
      0.0180149344580135, 0.017306495372750863, 0.016608759421594121,
      0.015921267031201947, 0.015243570989671607, 0.014575236662993041,
      0.013915842202838535, 0.013264978745727574, 0.012622250603423701,
      0.011987275444516776, 0.01135968446718183, 0.010739122562990144,
      0.010125248471773429, 0.009517734927487087, 0.0089162687950120056,
      0.008320551197899706, 0.0077302976369704735, 0.0071452380997875653,
      0.006565117160971079, 0.0059896940732999115, 0.0054187428496484946,
      0.00485205233566649, 0.0042894262732753874, 0.0037306833549177187,
      0.0031756572686029161, 0.0026241967336972372, 0.0020761655275565727,
      0.0015314425029223089, 0.000989921596150023, 0.00045151182629959985,
      -8.38627149439275E-5, -0.00061626288242067062, -0.0011457345057145352,
      -0.0016723084264442245, -0.0021960005444759956, -0.0027168118731539237,
      -0.0032347286033708733, -0.0037497221765034894, -0.0042617493661415984,
      -0.0047707523685130981, -0.0052766589015943444, -0.0057793823128180488,
      -0.0062788216952444631, -0.006774862012260352, -0.0072673742305517375,
      -0.007756215461432403, -0.00824122911031755, -0.00872224503430874,
      -0.0091990797078032038, -0.0096715363959944955, -0.01013940533620003,
      -0.010602463926875805, -0.011060476924250273, -0.011513196646427026,
      -0.011960363184872674, -0.012401704623167475, -0.012836937262851622,
      -0.01326576585636649, -0.013687883846775023, -0.014102973614341985,
      -0.014510706729664286, -0.014910744213329441, -0.015302736801925676,
      -0.015686325220236164, -0.016061140459535411, -0.016426804061797723,
      -0.016782928409660808, -0.017129117022042312, -0.01746496485520832,
      -0.017790058609167519, -0.0181039770392291, -0.0184062912725229,
      -0.018696565129413423, -0.018974355449532007, -0.019239212422357224,
      -0.019490679922103363, -0.019728295846793684, -0.019951592461323955,
      -0.020160096744360215, -0.020353330738882618, -0.02053081190618173,
      -0.020692053483199649, -0.0208365648429293, -0.020963851857791652,
      -0.021073417265761996, -0.021164761039038249, -0.021237380755146803,
      -0.021290771970201124, -0.021324428594235664, -0.021337843268306414,
      -0.02133050774328054, -0.021301913260080664, -0.02125155093117076,
      -0.021178912123146418, -0.021083488840206152, -0.020964774108311435,
      -0.020822262359877039, -0.020655449818763993, -0.020463834885410939,
      -0.02024691852190795, -0.020004204636790687, -0.019735200469445255,
      -0.019439416973815987, -0.0191163692013563, -0.018765576682934576,
      -0.018386563809513368, -0.017978860211517955, -0.01754200113655488,
      -0.01707552782541269, -0.016578987886081531, -0.016051935665688188,
      -0.015493932620040757, -0.014904547680749058, -0.014283357619604253,
      -0.013629947410114085, -0.01294391058600261, -0.012224849596471826,
      -0.011472376158059072, -0.010686111602948911, -0.009865687223488212,
      -0.0090107446128095126, -0.0081209360013591581, -0.0071959245891468071,
      -0.0062353848735816342, -0.00523900297269414, -0.0042064769436148119,
      -0.0031375170961284726, -0.0020318463011400612, -0.00088920029392436373,
      0.00029067202806309922, 0.0015080083128500288, 0.0027630324673609818,
      0.0040559543766678918, 0.0053869696291879432, 0.0067562592480681638,
      0.0081639894287948711, 0.0096103112832349735, 0.01109536059020555,
      0.012619257552749064, 0.014182106562151464, 0.015783995968965681,
      0.017424997861019587, 0.019105167848638471, 0.020824544857152683,
      0.022583150926784978, 0.024380991020082676, 0.026218052836950723,
      0.028094306637425903, 0.030009705072266579, 0.03196418302148113,
      0.033957657440860656, 0.035990027216638132, 0.038061173028329731,
      0.040170957219877512, 0.042319223679136209, 0.044505797725800711,
      0.046730486007874827, 0.04899307640666839, 0.051293337950506335,
      0.053631020737087143, 0.056005855864655452, 0.058417555371972463,
      0.060865812187180013, 0.063350300085558531, 0.065870673656282019,
      0.068426568278154409, 0.071017600104393785, 0.073643366056491688,
      0.0763034438271662, 0.078997391892440816, 0.081724749532867513,
      0.084485036863907625, 0.087277754875486668, 0.090102385480728853,
      0.092958391573868149, 0.095845217097363988, 0.098762287118172587,
      0.10170900791320414, 0.10468476706394714, 0.10768893356022863,
      0.11072085791309949, 0.11377987227683595, 0.11686529057999812,
      0.11997640866555592, 0.123112504439992, 0.12627283803140926,
      0.1294566519565436, 0.13266317129665189, 0.13589160388225263,
      0.13914114048661064, 0.14241095502796236, 0.14570020478037699,
      0.14900803059321366, 0.15233355711909446, 0.15567589305031093,
      0.15903413136361738, 0.16240734957327857, 0.16579460999235096,
      0.16919496000204848, 0.17260743232913461, 0.17603104533126157,
      0.17946480329008307, 0.1829076967121554, 0.18635870263739823,
      0.18981678495509119, 0.1932808947272634, 0.19674997051934762,
      0.20022293873801011, 0.20369871397601069, 0.2071761993639602,
      0.21065428692887839, 0.21413185795939793, 0.21760778337747244,
      0.22108092411647018, 0.22455013150549979, 0.22801424765983436,
      0.23147210587726297, 0.23492253104026353, 0.23836434002379459,
      0.24179634210859868, 0.24521733939980947, 0.24862612725075939,
      0.25202149469178176, 0.25540222486384545, 0.25876709545689769,
      0.262114879152683, 0.26544434407191531, 0.26875425422561816,
      0.27204336997042411, 0.27531044846771513, 0.27855424414636965,
      0.28177350916897531, 0.28496699390128566, 0.28813344738476454,
      0.29127161781203464, 0.29438025300499904, 0.29745810089551833,
      0.30050391000836868, 0.30351642994635941, 0.30649441187736687,
      0.30943660902312187, 0.31234177714954309, 0.315208675058395,
      0.31803606508013083, 0.32082271356764946, 0.32356739139082613,
      0.32626887443158614, 0.32892594407931164, 0.33153738772642405,
      0.33410199926387268, 0.3366185795764095, 0.33908593703734974,
      0.3415028880027039, 0.34386825730442888, 0.34618087874260589,
      0.34843959557633181, 0.35064326101315124, 0.35279073869678446,
      0.35488090319297405, 0.35691264047325322, 0.35888484839640078,
      0.36079643718742965, 0.36264632991383483, 0.36443346295900392,
      0.36615678649247335, 0.36781526493693267, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, -0.0038997505340175737, 0.0074713542585517628,
      0.018843777753412921, 0.030215339774660982, 0.041583858556551112,
      0.052947151241796331, 0.064303034380870316, 0.075649324432187151,
      0.086983838263030439, 0.098304393651103328, 0.10960880978656984,
      0.1208949077744588, 0.1321605111373009, 0.14340344631786747,
      0.15462154318188348, 0.16581263552058065, 0.17697456155296432,
      0.1881051644276597, 0.19920229272420775, 0.2102638009536818,
      0.22128755005849021, 0.23227140791123774, 0.24321324981251236,
      0.254110958987467, 0.26496242708106782, 0.27576555465187408,
      0.28651825166422523, 0.29721843797869785, 0.30786404384071109,
      0.31845301036714241, 0.32898329003083265, 0.33945284714284507,
      0.34985965833235466, 0.360201713024037, 0.37047701391283244,
      0.38068357743595427, 0.39081943424202065, 0.40088262965717897,
      0.41087122414810306, 0.42078329378173374, 0.43061693068164481,
      0.440370243480908, 0.450041357771336, 0.45962841654898379,
      0.4691295806557873, 0.47854302921721908, 0.48786696007584657,
      0.49709959022067052, 0.506239156212133, 0.51528391460267486,
      0.52423214235273308, 0.53308213724206133, 0.54183221827626593,
      0.55048072608844278, 0.55902602333580964, 0.56746649509122471,
      0.57580054922948187, 0.58402661680828372, 0.5921431524437818,
      0.60014863468058655, 0.60804156635614315, 0.6158204749593742,
      0.623483912983492, 0.631030458272885, 0.6384587143639765,
      0.6457673108199764, 0.652954903559416, 0.66002017517839251,
      0.666961835266422, 0.673778620715825, 0.68046929602454853,
      0.687032653592352, 0.69346751401026785, 0.69977272634325915,
      0.70594716840600169, 0.71198974703170437, 0.71789939833390315,
      0.72367508796115187, 0.72931581134453993, 0.7348205939379695,
      0.74018849145112586, 0.74541859007507494, 0.75051000670042856,
      0.75546188912801371, 0.76027341627199052, 0.76494379835536019,
      0.76947227709781219, 0.77385812589585234, 0.77810064999517214,
      0.7821991866551985, 0.7861531053057913, 0.78996180769603486,
      0.793624728035088, 0.797141333125053, 0.80051112248582323,
      0.80373362847187813, 0.80680841638099188, 0.8097350845548259,
      0.81251326447137506, 0.81514262082924649, 0.81762285162374182,
      0.81995368821472636, 0.82213489538626217, 0.824166271397995,
      0.82604764802826858, 0.82777889060897147, 0.82935989805208776,
      0.83079060286796036, 0.83207097117525031, 0.83320100270259645,
      0.83418073078197019, 0.83501022233372968, 0.8356895778433765,
      0.8362189313300219, 0.83659845030656987, 0.83682833573162863,
      0.83690882195316407, 0.83684017664391153, 0.83662270072856071,
      0.83625672830273579, 0.83574262654379661, 0.8350807956134747,
      0.83427166855238566, 0.83331571116643555, 0.832213421905156,
      0.83096533173200582, 0.82957200398666742, 0.82803403423938315,
      0.82635205013736646, 0.824526711243334, 0.82255870886620142,
      0.82044876588398918, 0.81819763655898992, 0.81580610634524331,
      0.81327499168838013, 0.810605139817879, 0.80779742853180536,
      0.80485276597408284, 0.80177209040436348, 0.79855636996055823,
      0.79520660241409469, 0.79172381491796706, 0.78810906374765044,
      0.78436343403495046, 0.780488039494859, 0.77648402214549461,
      0.77235255202120168, 0.76809482687889163, 0.76371207189770063,
      0.75920553937205171, 0.75457650839820467, 0.74982628455437628,
      0.74495619957452508, 0.73996761101588238, 0.73486190192032907,
      0.72964048046970387, 0.72430477963514173, 0.71885625682053833,
      0.71329639350023522, 0.70762669485102758, 0.70184868937859635,
      0.69596392853846145, 0.68997398635156648, 0.68388045901459349,
      0.6776849645051205, 0.67138914218172341, 0.66499465237913558,
      0.65850317599857233, 0.65191641409333445, 0.64523608744980088,
      0.63846393616392838, 0.63160171921336672, 0.6246512140253121,
      0.6176142160402126, 0.61049253827144212, 0.60328801086106731,
      0.596002480631824, 0.58863781063542131, 0.58119587969730357,
      0.5736785819579836, 0.56608782641108013, 0.55842553643817272,
      0.55069364934061171, 0.54289411586839775, 0.53502889974626566,
      0.52709997719709323, 0.51910933646277058, 0.51105897732264627,
      0.5029509106096921, 0.49478715772450715, 0.48656975014729187,
      0.478300728947925, 0.46998214429427265, 0.46161605495885527,
      0.45320452782401321, 0.44474963738569173, 0.43625346525598357,
      0.42771809966455793, 0.41914563495910667, 0.41053817110494145,
      0.40189781318387197, 0.39322667089249758, 0.38452685804004461,
      0.37580049204587657, 0.3670496934368167, 0.358276585344405,
      0.349483293002229, 0.34067194324345312, 0.33184466399867835,
      0.32300358379426619, 0.3141508312512496, 0.30528853458497118,
      0.29641882110556206, 0.28754381671940732, 0.278665645431712,
      0.26978642885030441, 0.26090828569079549, 0.25203333128323185,
      0.24316367708035297, 0.23430143016759275, 0.22544869277493837,
      0.21660756179077745, 0.20778012827784753, 0.19896847699142206,
      0.19017468589983907, 0.18140082570750965, 0.1726489593805027,
      0.16392114167485228, 0.15521941866767802, 0.14654582729125068,
      0.13790239487011444, 0.12929113866137704, 0.12071406539828217,
      0.11217317083717673, 0.10367043930798234, 0.095207843268280426,
      0.08678734286111818, 0.078410885476641254, 0.070080405317664143,
      0.061797822969273039, 0.053565044972571071, 0.045383963402663693,
      0.037256455450986548, 0.029184383012067883, 0.021169592274834642,
      0.013213913318539633, 0.0053191597134238933, -0.0025128718738121059,
      -0.010280402069624633, -0.017981669178249116, -0.025614929561233152,
      -0.033178458011809214, -0.040670548124002615, -0.048089512656410927,
      -0.055433683890562579, -0.062701413983782484, -0.069891075316478812,
      -0.077001060833790963, -0.084029784381506822, -0.090975681036188777,
      -0.097837207429439049, -0.10461284206622781, -0.11130108563722896,
      -0.11790046132508825, -0.12440951510456949, -0.13082681603651372,
      -0.13715095655555665, -0.14338055275153783, -0.14951424464456567,
      -0.15555069645366121, -0.16148859685895178, -0.16732665925734974,
      -0.1730636220116808, -0.17869824869320586, -0.18422932831750571,
      -0.18965567557367641, -0.1949761310468027, -0.20018956143367306,
      -0.20529485975169492, -0.21029094554098665, -0.21517676505960653,
      -0.21995129147189568, -0.22461352502990659, -0.22916249324788904,
      -0.23359725106981885, -0.23791688102993927, -0.24212049340630121,
      -0.24620722636728784, -0.250176246111105, -0.25402674699822309,
      -0.25775795167676929, -0.26136911120084982, -0.2648595051418019,
      -0.2682284416923752, -0.27147525776382886, -0.27459931907595581,
      -0.27760002024002289, -0.28047678483464988, -0.28322906547460647,
      -0.28585634387256176, -0.28835813089377316, -0.29073396660374318,
      -0.2929834203088465, -0.29510609058994586, -0.29710160532901875,
      -0.29896962172880481, -0.30070982632550347, -0.3023219349945383,
      -0.30380569294941995, -0.30516087473372477, -0.30638728420622874,
      -0.30748475451921431, -0.30845314808999724, -0.30929235656569226,
      -0.31000230078126345, -0.31058293071089349, -0.31103422541270931,
      -0.31135619296690753, -0.3115488704073216, -0.31161232364647451,
      -0.31154664739416071, -0.31135196506961044, -0.31102842870728042,
      -0.3105762188563217, -0.30999554447378153, -0.30928664281159046,
      -0.3084497792973836, -0.30748524740922761, -0.30639336854429644,
      -0.30517449188156631, -0.30382899423858223, -0.30235727992236994,
      -0.30075978057454528, -0.29903695501069261, -0.29718928905408148,
      -0.29521729536378016, -0.29312151325724661, -0.29090250852745619,
      -0.28856087325465046, -0.28609722561276196, -0.28351220967061075,
      -0.28080649518792811, -0.27798077740629579, -0.27503577683507341,
      -0.271972239032393, -0.26879093438129892, -0.26549265786111548,
      -0.26207822881412252, -0.25854849070761854, -0.25490431089145915,
      -0.25114658035115062, -0.24727621345658488, -0.2432941477065009,
      -0.23920134346875813, -0.23499878371651128, -0.2306874737603706,
      -0.22626844097663684, -0.221742734531703, -0.21711142510270764,
      -0.21237560459453111, -0.20753638585322898, -0.20259490237598843,
      -0.1975523080177006, -0.19240977669424467, -0.18716850208257035,
      -0.18182969731767415, -0.17639459468656477, -0.17086444531930609,
      -0.16524051887723479, -0.15952410323844612, -0.15371650418064092,
      -0.14781904506143029, -0.14183306649618457, -0.1357599260335367,
      -0.1296009978286165, -0.12335767231412464, -0.11703135586933072,
      -0.11062347048710031, -0.10413545343903222, -0.09756875693881728,
      -0.090924847803897119, -0.084205207115524566, -0.077411329877324325,
      -0.070544724672435638, -0.063606913319344011, -0.056599430526483155,
      -0.049523823545711179, -0.042381651824745237, -0.0351744866586529,
      -0.027903910840485935, -0.020571518311157416, -0.013178913808644319,
      -0.0057277125166091958, 0.0017804602874630232, 0.009343969584535719,
      0.016961170966595343, 0.024630410989453067, 0.032350027525680225,
      0.040118350117589976, 0.047933700330179747, 0.055794392103947758,
      0.063698732107501349, 0.0716450200898664, 0.079631549232417081,
      0.087656606500351619, 0.09571847299361004, 0.10381542429717969,
      0.11194573083068168, 0.12010765819718268, 0.12829946753113702,
      0.13651941584538096, 0.14476575637711644, 0.15303673893279218,
      0.16133061023181841, 0.1696456142490341, 0.17797999255585806,
      0.18633198466004727, 0.19469982834400071, 0.20308176000152817,
      0.21147601497301907, 0.21988082787894575, 0.22829443295163562,
      0.23671506436524448, 0.24514095656385837, 0.25357034458768124,
      0.262001464397228, 0.27043255319546705, 0.27886184974786177,
      0.28728759470023668, 0.2957080308944251, 0.30412140368163676,
      0.31252596123349385, 0.32091995485066688, 0.32930163926909189,
      0.33766927296368043, 0.3460211184494949, 0.35435544258033613,
      0.36267051684470231, 0.37096461765905364, 0.37923602665836459,
      0.38748303098390541, 0.39570392356820627, 0.403897003417189,
      0.41206057588939082, 0.42019295297227727, 0.4282924535555811,
      0.4363574037016556, 0.44438613691278661, 0.452376994395447,
      0.46032832532145357, 0.46823848708600635, 0.47610584556257163,
      0.48392877535458267, 0.49170566004394645, 0.49943489243631217,
      0.50711487480309625, 0.51474401912022938, 0.52232074730361244,
      0.52984349144126131, 0.5373106940221245, 0.54472080816155244,
      0.55207229782340428, 0.55936363803878952, 0.56659331512141442,
      0.57375982687953841, 0.58086168282451678, 0.58789740437593407,
      0.59486552506331514, 0.60176459072440025, 0.6085931597000005,
      0.61534980302540121, 0.62203310461833961, 0.62864166146353706,
      0.63517408379379292, 0.641628995267636, 0.64800503314355218,
      0.65430084845076664, 0.66051510615660691, 0.66664648533044357,
      0.67269367930421775, 0.67865539582955969, 0.68453035723151534,
      0.690317300558883, 0.69601497773117871, 0.70162215568224018,
      0.70713761650047524, 0.71256015756578484, 0.71788859168316188,
      0.72312174721299183, 0.72825846819806361, 0.733297614487318,
      0.73823806185634711, 0.74307870212466809, 0.7478184432697883,
      0.75245620953808978, 0.7569909415525462, 0.76142159641730922,
      0.7657471478191763, 0.76996658612597069, 0.77407891848185517,
      0.77808316889962037, 0.78197837834994854, 0.78576360484770769,
      0.78943792353528863, 0.79300042676301863, 0.796450224166681,
      0.79978644274217581, 0.80300822691733853, 0.80611473862097049,
      0.80910515734909028, 0.81197868022845665, 0.81473452207737906,
      0.81737191546387467, 0.81989011076116647, 0.82228837620060558,
      0.82456599792200713, 0.82672228002146331, 0.82875654459666048,
      0.83066813178973231, 0.83245639982769382, 0.83412072506047852,
      0.83566050199663255, 0.83707514333669075, 0.83836408000427054,
      0.83952676117493086, 0.84056265430282484, 0.84147124514518212,
      0.842252037784666, 0.84290455464964231, 0.8434283365323817,
      0.84382294260525936, 0.84408795043496443, 0.8442229559947747,
      0.84422757367492285, 0.84410143629109846, 0.84384419509111552,
      0.84345551975979527, 0.842935098422084, 0.84228263764445976,
      0.84149786243465474, 0.84058051623972474, 0.83953036094252442,
      0.83834717685659277, 0.83703076271951171, 0.83558093568475444,
      0.83399753131207566, 0.83228040355645627, 0.83042942475566206,
      0.82844448561643036, 0.82632549519932674, 0.82407238090230683,
      0.82168508844300958, 0.81916358183981763, 0.81650784339172333,
      0.81371787365701276, 0.81079369143082158, 0.80773533372157513,
      0.8045428557263542, 0.80121633080520471, 0.797755850454433,
      0.79416152427889808, 0.79043347996334812, 0.78657186324280759,
      0.7825768378720539, 0.77844858559420715, 0.7741873061084561,
      0.76979321703693726, 0.76526655389080755, 0.76060757003551394,
      0.75581653665529613, 0.75089374271693421, 0.74583949493276769,
      0.74065411772300116, 0.73533795317731776, 0.72989136101581964,
      0.72431471854930374, 0.71860842063890618, 0.71277287965511171,
      0.70680852543615669, 0.70071580524583443, 0.69449518373071339,
      0.68814714287678425, 0.68167218196554924, 0.67507081752955744,
      0.66834358330739363, 0.66149103019815136, 0.65451372621536341,
      0.64741225644042522, 0.64018722297550212, 0.63283924489593413,
      0.62536895820213423, 0.617777015770995, 0.610064087306785,
      0.60223085929156817, 0.59427803493511577, 0.58620633412433132,
      0.57801649337217487, 0.56970926576609449, 0.561285420915955,
      0.55274574490146455, 0.544091040219087, 0.5353221257284495,
      0.52643983659821736, 0.51744502425145544, 0.50833855631043412,
      0.49912131654091141, 0.48979420479584, 0.48035813695852442,
      0.4708140448851883, 0.46116287634695685, 0.45140559497123706,
      0.4415431801824789, 0.43157662714229827, 0.42150694668896421,
      0.41133516527620761, 0.4010623249113589, 0.39068948309277485,
      0.38021771274655836, 0.36964810216252747, 0.358981754929431,
      0.34821978986939361, 0.3373633409715327, 0.32641355732477906,
      0.31537160304983525, 0.30423865723026644, 0.29301591384268894,
      0.28170458168604973, 0.27030588430994784, 0.258821059941993,
      0.24725136141414986, 0.23559805608806952, 0.22386242577935736,
      0.21204576668076167, 0.20014938928423731, 0.18817461830188184,
      0.17612279258568955, 0.16399526504610609, 0.15179340256933849,
      0.13951858593341604, 0.12717220972293733, 0.1147556822425016,
      0.10227042542875839, 0.089717874761087307, 0.077099479170823576,
      0.064416700949039507, 0.051671015652824892, 0.038863912010034113,
      0.0259968918224687, 0.013071469867471555, 8.9173797876859751E-5,
      -0.012948455959699706, -0.026039866308283172, -0.039183491585688457,
      -0.052377753671441554, -0.065621062095523583, -0.078911814148940815,
      -0.092248394996177818, -0.10562917778956554, -0.11905252378560111,
      -0.13251678246324011, -0.14602029164421459, -0.1595613776153994,
      -0.17313835525327387, -0.18674952815049606, -0.20039318874463122,
      -0.21406761844908073, -0.227771087786229, -0.24150185652284653,
      -0.25525817380778093, -0.26903827831197769, -0.28284039837084912,
      -0.29666275212903825, -0.31050354768760058, -0.32436098325362572,
      -0.3382332472923571, -0.35211851868180671, -0.3660149668699294,
      -0.37992075203435116, -0.39383402524470057, -0.40775292862757595,
      -0.42167559553415751, -0.43560015071050934, -0.44952471047057624,
      -0.46344738287192766, -0.47736626789425285, -0.49127945762063957,
      -0.5051850364216478, -0.5190810811422325, -0.53296566129149481,
      -0.54683683923530779, -0.56069267039183579, -0.57453120342996811,
      -0.58835048047066174, -0.60214853729124074, -0.61592340353265462,
      -0.6296731029097028, -0.64339565342426652, -0.65708906758151875,
      -0.67075135260916952, -0.68438051067972328, -0.69797453913578111,
      -0.71153143071837666, -0.7250491737983783, -0.73852575261093023,
      -0.75195914749298221, -0.76534733512385711, -0.77868828876892393,
      -0.79197997852630808, -0.8052203715767049, -0.8184074324362447,
      -0.83153912321244328, -0.84461340386320372, -0.85762823245889619,
      -0.87058156544748488, -0.88347135792270515, -0.89629556389528053,
      -0.90905213656717354, -0.92173902860885493, -0.93435419243957418,
      -0.9468955805106215, -0.95936114559157193, -0.97174884105948811,
      -0.98405662119105808, -0.9962824414576491, -1.0084242588232781,
      -1.0204800320454361, -1.0324477219787818, -1.0443252918816519,
      -1.0561107077253635, -1.0678019385063053, -1.079396956560742,
      -1.0908937378823489, -1.1022902624423978, -1.1135845145126049,
      -1.1247744829905519, -1.1358581617277004, -1.1468335498599029,
      -1.1576986521404187, -1.1684514792753531, -1.1790900482615008,
      -1.1896123827265357, -1.2000165132715082, -1.2103004778155877,
      -1.2204623219430186, -1.2305000992522137, -1.2404118717069577,
      -1.2501957099896519, -1.2598496938565384, -1.2693719124948546,
      -1.2787604648818622, -1.2880134601456767, -1.2971290179278439,
      -1.3061052687476011, -1.3149403543677454, -1.3236324281620586,
      -1.3321796554842089, -1.340580214038062, -1.3488322942493256,
      -1.3569340996384771, -1.3648838471948594, -1.3726797677519116,
      -1.3803201063634274, -1.3878031226807845, -1.3951270913310418,
      -1.4022903022958502, -1.4092910612910705, -1.4161276901470308,
      -1.4227985271893375, -1.4293019276201333, -1.435636263899748,
      -1.4417999261286258, -1.4477913224294543, -1.4536088793293951,
      -1.4592510421423317, -1.4647162753510334, -1.470003062989149,
      -1.4751099090229274, -1.4800353377325723, -1.4847778940931318,
      -1.4893361441548281, -1.4937086754227167, -1.4978940972355932,
      -1.5018910411440216, -1.5056981612874063, -1.5093141347699854,
      -1.5127376620356527, -1.5159674672414942, -1.5190022986299443,
      -1.5218409288994437, -1.524482155573498, -1.5269248013680266,
      -1.5291677145568987, -1.531209769335534, -1.5330498661824743,
      -1.5346869322188035, -1.5361199215653047, -1.5373478156972606,
      -1.5383696237967561, -1.5391843831023915, -1.5397911592562945,
      -1.5401890466482986, -1.5403771687571977, -1.540354678488945,
      -1.5401207585116921, -1.5396746215875519, -1.5390155109009691,
      -1.538142700383577, -1.537055495035448, -1.5357532312425994,
      -1.5342352770906418, -1.5325010326744772, -1.5305499304039063,
      -1.5283814353050427, -1.5259950453174214, -1.5233902915866766,
      -1.5205667387526893, -1.5175239852330806, -1.5142616635019335,
      -1.5107794403636514, -1.5070770172218038, -1.503154130342891,
      -1.4990105511148804, -1.4946460863004114, -1.4900605782845797,
      -1.4852539053171587, -1.4802259817491654, -1.4749767582636697,
      -1.4695062221007138, -1.4638143972762654, -1.4579013447950671,
      -1.451767162857307, -1.4454119870589686, -1.4388359905858019,
      -1.4320393844007704, -1.4250224174248931, -1.4177853767113797,
      -1.4103285876129632, -1.4026524139423022, -1.3947572581254095,
      -1.3866435613479446, -1.3783118036943403, -1.3697625042796164,
      -1.3609962213738225, -1.3520135525189976, -1.342815134638583,
      -1.3334016441391574, -1.3237737970044534, -1.3139323488815511,
      -1.3038780951591515, -1.2936118710378657, -1.2831345515924422,
      -1.2724470518258431, -1.2615503267150863, -1.2504453712488033,
      -1.2391332204564136, -1.22761494942886, -1.2158916733308285,
      -1.2039645474043847, -1.1918347669639666, -1.179503567382671,
      -1.1669722240697595, -1.1542420524393322, -1.1413144078701243,
      -1.1281906856563515, -1.114872320949549, -1.1013607886913739,
      -1.0876576035373084, -1.0737643197712141, -1.0596825312107003,
      -1.0454138711032708, -1.0309600120131757, -1.0163226656989961,
      -1.0015035829818448, -0.986504553604219, -0.97132740607944557,
      -0.95597400753168349, -0.940446263526479, -0.92474611789184391,
      -0.90887555252982188, -0.89283658721854453, -0.8766312794047656,
      -0.86026172398683753, -0.84373005308813309, -0.82703843582091852,
      -0.81018907804066176, -0.79318422209075856, -0.77602614653770874,
      -0.75871716589672678, -0.74125963034780207, -0.72365592544220014,
      -0.705908471799443, -0.68801972479476814, -0.66999217423708846,
      -0.6518283440374697, -0.63353079186814543, -0.61510210881211236,
      -0.59654491900332463, -0.57786187925749632, -0.55905567869359218,
      -0.54012903834601422, -0.52108471076752483, -0.5019254796229603,
      -0.48265415927377453, -0.463273594353463, -0.44378665933391354,
      -0.42419625808276984, -0.40450532341179346, -0.38471681661637475,
      -0.3648337270061846, -0.34485907142707928, -0.32479589377429469,
      -0.304647264497019, -0.28441628009441716, -0.264106062603201,
      -0.24371975907676002, -0.22326054105603416, -0.20273160403213428,
      -0.18213616690084503, -0.16147747140906771, -0.14075878159333419,
      -0.11998338321045382, -0.099154583160434268, -0.07827570890171634,
      -0.057350107858898269, -0.03638114682301552, -0.015372211344503117,
      0.0056732948810722106, 0.026751950634350402, 0.0478603178004994,
      0.068994942004400373, 0.090152353252539313, 0.11132906658153288,
      0.13252158271310568, 0.15372638871541411, 0.17493995867058504,
      0.19615875434832364, 0.21737922588545344, 0.23859781247125711,
      0.25981094303843344, 0.28101503695961738, 0.30220650474919136,
      0.32338174877034254, 0.34453716394714584, 0.36566913848156107,
      0.386774054575152, 0.40784828915541027, 0.42888821460645143,
      0.44989019950402986, 0.47085060935458756, 0.4917658073382557,
      0.51263215505558679, 0.53344601327789776, 0.55420374270099759,
      0.57490170470214941, 0.595536262100111, 0.61610377991802234,
      0.63660062614902391, 0.65702317252437537, 0.67736779528390068,
      0.69763087594860285, 0.71780880209522946, 0.73789796813261277,
      0.7578947760796062, 0.77779563634439364, 0.79759696850504547,
      0.81729520209104234, 0.8368867773656431, 0.856368146108868,
      0.87573577240090783, 0.89498613340575606, 0.9141157201548944,
      0.93312103833077042, 0.9519986090499597, 0.97074496964571133,
      0.98935667444974984, 1.0078302955730893, 1.0261624236856923,
      1.0443496687947311, 1.0623886610212678, 1.0802760513751659,
      1.0980085125279804, 1.1155827395836775, 1.132995450846942,
      1.1502433885888745, 1.167323319809872, 1.1842320369995021,
      1.2009663588931352, 1.2175231312251658, 1.2338992274785623,
      1.2500915496306246, 1.2660970288946405, 1.2819126264573308,
      1.2975353342118059, 1.3129621754858829, 1.3281902057655124,
      1.3432165134131653, 1.3580382203809072, 1.3726524829180429,
      1.3870564922730422, 1.401247475389616, 1.4152226955966989,
      1.4289794532921638, 1.4425150866200598, 1.455826972141165,
      1.4689125254967006, 1.481769202064944, 1.4943944976106185,
      1.5067859489268129, 1.5189411344692714, 1.5308576749828362,
      1.5425332341199007, 1.553965519050629, 1.5651522810648038,
      1.5760913161650747, 1.5867804656514921, 1.5972176166970591,
      1.6074007029141975, 1.6173277049119152, 1.6269966508434999,
      1.6364056169445784, 1.6455527280613795, 1.6544361581689886,
      1.6630541308794917, 1.6714049199397856, 1.6794868497189355,
      1.6872982956848825, 1.6948376848703863, 1.7021034963280111,
      1.7090942615740146, 1.71580856502101, 1.7222450443992181,
      1.7284023911661905, 1.7342793509048631, 1.7398747237097765,
      1.7451873645613512, 1.7502161836880874, 1.7549601469165255,
      1.7594182760088775, 1.7635896489881793, 1.7674734004508668,
      1.7710687218666177, 1.7743748618653918, 1.7773911265115219,
      1.7801168795647564, 1.7825515427281524, 1.7846945958827221,
      1.7865455773087022, 1.788104083893403, 1.7893697713254888,
      1.790342354275642, 1.7910216065635038, 1.7914073613108201,
      1.7914995110807017, 1.791298008002945, 1.790802863885316,
      1.7900141503107556, 1.7889319987204124, 1.7875566004824861,
      1.7858882069467736, 1.7839271294849028, 1.7816737395162014,
      1.7791284685191266, 1.7762918080282559, 1.7731643096167726,
      1.7697465848644154, 1.7660393053108845, 1.7620432023946428,
      1.7577590673771297, 1.7531877512523388, 1.7483301646417566,
      1.7431872776746602, 1.7377601198537642, 1.7320497799062013,
      1.7260574056198588, 1.7197842036650679, 1.7132314394016566,
      1.7064004366713863, 1.6992925775757781, 1.6919093022393679,
      1.6842521085584032, 1.67632255193503, 1.668122244996973,
      1.6596528573027876, 1.6509161150327056, 1.6419138006651113,
      1.6326477526387291, 1.6231198650005536, 1.6133320870395862,
      1.603286422906461, 1.5929849312189868, 1.5824297246537307,
      1.571622969523673, 1.5605668853420345, 1.549263744372366,
      1.5377158711649641, 1.5259256420797294, 1.5138954847955639,
      1.50162787780637, 1.489125349903804, 1.4763904796468708, 1.463425894818454,
      1.4502342718689285, 1.4368183353469575, 1.4231808573175906,
      1.4093246567678093, 1.3952525989996454, 1.3809675950109737,
      1.3664726008641823, 1.3517706170428003, 1.3368646877962598,
      1.3217579004729383, 1.3064533848416284, 1.2909543124015936,
      1.2752638956813762, 1.2593853875265031, 1.2433220803762681,
      1.2270773055297777, 1.2106544324013948, 1.1940568677657917,
      1.177288054992774, 1.1603514732720699, 1.1432506368282533,
      1.1259890941260156, 1.1085704270659529, 1.0909982501710882,
      1.0732762097643118, 1.0554079831369374, 1.0373972777085958,
      1.019247830178668, 1.0009634056694376, 0.98254779686124349,
      0.9640048231197591, 0.94533832961569686, 0.92655218643710813,
      0.9076502876945215, 0.88863655061914437, 0.86951491465434416,
      0.8502893405406482, 0.83096380939451142, 0.81154232178102992,
      0.79202889678091359, 0.7724275710518993, 0.752742397884866,
      0.73297744625489425, 0.71313679986750778, 0.69322455620035117,
      0.67324482554055975, 0.65320173001802539, 0.63309940263488218,
      0.61294198629140062, 0.59273363280858193, 0.572478501947684,
      0.55218076042695452, 0.53184458093582365, 0.51147414114679823,
      0.4910736227253587, 0.470647210338055, 0.45019909065913732,
      0.42973345137592911, 0.40925448019323096, 0.38876636383701463,
      0.36827328705767004, 0.34777943163306574, 0.32728897537172247,
      0.3068060911162892, 0.28633494574769236, 0.26587969919013366,
      0.24544450341725152, 0.22503350145970713, 0.2046508264144562,
      0.1843006004559595, 0.16398693384964858, 0.14371392396783078,
      0.12348565430839153, 0.10330619351648915, 0.083179594409553193,
      0.06310989300581385, 0.043101107556668267, 0.023157237583102938,
      0.0032822629164673128, -0.016519857256136583, -0.036245185341627482,
      -0.055889806285578943, -0.075449828511461731, -0.094921384854262769,
      -0.11430063348819171, -0.13358375884824705, -0.1527669725453692,
      -0.17184651427492112, -0.19081865271828868, -0.2096796864372959,
      -0.22842594476122655, -0.24705378866618505, -0.265559611646565,
      -0.28393984057837313, -0.30219093657419549, -0.32030939582950563,
      -0.33829175046016935, -0.35613456933082871, -0.37383445887397926,
      -0.39138806389949871, -0.4087920683944109, -0.42604319631264348,
      -0.44313821235456957, -0.46007392273610576, -0.47684717594717763,
      -0.49345486349928908, -0.509893920662039, -0.52616132718833719,
      -0.54225410802813345, -0.55816933403046, -0.57390412263357837,
      -0.58945563854304839, -0.60482109439749676, -0.619997751421954,
      -0.6349829200685092, -0.64977396064414361, -0.6643682839255467,
      -0.67876335176074021, -0.692956677657349, -0.70694582735734224,
      -0.72072841939806387, -0.73430212565944153, -0.74766467189715191,
      -0.76081383826164839, -0.77374745980284931, -0.7864634269603904,
      -0.798959686039268, -0.811234239670739, -0.82328514725835933,
      -0.83511052540902, -0.846708548348853, -0.85807744832390431,
      -0.86921551598542546, -0.88012110075970229, -0.8907926112023048,
      -0.90122851533664106, -0.91142734097673084, -0.921387676034086,
      -0.9311081688086521, -0.94058752826364855, -0.94982452428430653,
      -0.95881798792036865, -0.96756681161231706, -0.97606994940122727,
      -0.98432641712223112, -0.99233529258145414, -1.0000957157164871,
      -1.0076068887402174, -1.0148680762680693, -1.021878605428562,
      -1.0286378659571842, -1.0351453102735215, -1.0414004535416421,
      -1.0474028737136907, -1.0531522115567067, -1.0586481706626227,
      -1.0638905174414679, -1.0688790810977453, -1.0736137535900065,
      -1.0780944895736375, -1.0823213063268304, -1.0862942836598091,
      -1.0900135638072952, -1.0934793513042633, -1.0966919128449932,
      -1.0996515771254862, -1.1023587346692632, -1.1048138376366097,
      -1.1070173996172876, -1.1089699954068211, -1.1106722607663615,
      -1.1121248921662448, -1.1133286465132737, -1.1142843408618237,
      -1.1149928521088521, -1.1154551166728695, -1.1156721301569932,
      -1.1156449469961709, -1.1153746800886495, -1.1148625004118198,
      -1.1141096366225296, -1.1131173746419794, -1.1118870572253261,
      -1.1104200835160947, -1.1087179085855516, -1.10678204295714,
      -1.1046140521161405, -1.1022155560046796, -1.0995882285022038,
      -1.0967337968916415, -1.0936540413113049, -1.0903507941927719,
      -1.0868259396848605, -1.0830814130638737, -1.079119200130269,
      -1.0749413365919733, -1.0705499074344307, -1.0659470462776519,
      -1.0611349347203949, -1.0561158016716812, -1.0508919226698372,
      -1.0454656191892571, -1.0398392579350753, -1.034015250125971,
      -1.0279960507652894, -1.0217841579006859, -1.0153821118725357,
      -1.0087924945512865, -1.002017928564007, -0.9950610765103185,
      -0.98792464016797055, -0.98061135968825042, -0.97312401278150151,
      -0.96546541389294183, -0.95763841336904865, -0.94964589661474341,
      -0.94149078324159885, -0.93317602620735185, -0.92470461094693779,
      -0.91607955449529621, -0.9073039046022372, -0.89838073883957237,
      -0.88931316370080959, -0.88010431369364794, -0.87075735042554436,
      -0.86127546168261571, -0.85166186050213388, -0.84191978423888925,
      -0.83205249362570022, -0.82206327182831318, -0.8119554234949975,
      -0.80173227380109124, -0.79139716748878208, -0.78095346790239428,
      -0.77040455601946, -0.759753829477868, -0.7490047015993605,
      -0.73816060040966858, -0.72722496765554168, -0.71620125781900312,
      -0.70509293712908772, -0.69390348257133794, -0.68263638089537226,
      -0.671295127620801, -0.65988322604176064, -0.6484041862304043,
      -0.636861524039563, -0.62525876010493431, -0.61359941884706037,
      -0.60188702747337353, -0.59012511498061615, -0.57831721115791834,
      -0.56646684559081817, -0.55457754666652925, -0.542652840580705,
      -0.530696250346052, -0.51871129480299871, -0.50670148763278333,
      -0.49467033637319768, -0.48262134143728819, -0.47055799513529928,
      -0.4584837807001429, -0.44640217131666438, -0.43431662915501024,
      -0.42223060440834825, -0.41014753433524792, -0.39807084230696965,
      -0.38600393685997036, -0.37395021075386231, -0.36191304003513652,
      -0.34989578310689506, -0.33790177980486136, -0.32593435047995878,
      -0.3139967950877019, -0.30209239228466583, -0.29022439853230314,
      -0.27839604720836292, -0.266610547726161, -0.25487108466198044,
      -0.24318081689081694, -0.23154287673074508, -0.2199603690961548,
      -0.20843637066008106, -0.19697392902588529, -0.18557606190852483,
      -0.17424575632563197, -0.16298596779865704, -0.15179961956429971,
      -0.14068960179642503, -0.12965877083874311, -0.11870994844842198,
      -0.10784592105088164, -0.097069439005961738, -0.08638321588569485,
      -0.075789927763870765, -0.065292212517616022, -0.054892669141158756,
      -0.044593857072010565, -0.034398295529730005, -0.02430846286746946,
      -0.014326795936479661, -0.0044556894637678979, 0.00530250455693497,
      0.014945477460693982, 0.024470964493259195, 0.033876745379099293,
      0.04316064487546499, 0.052320533312302547, 0.061354327117880247,
      0.070259989329971864, 0.079035530092453066, 0.087679007137181131,
      0.096188526251004908, 0.10456224172781109, 0.11279835680544104,
      0.12089512408738265, 0.12885084594910712, 0.13666387492896465,
      0.14433261410349441, 0.15185551744708373, 0.15923109017584397,
      0.16645788907565529, 0.1735345228142455, 0.18045965223725066,
      0.18723199064816876, 0.19385030407213705, 0.20031341150346718,
      0.20662018513686262, 0.21276955058226868, 0.21876048706331974,
      0.22459202759929126, 0.23026325917055959, 0.23577332286749839,
      0.24112141402280296, 0.24630678232719144, 0.25132873192847838,
      0.25618662151398608, 0.26087986437630351, 0.26540792846235028,
      0.26977033640578474, 0.27396666554271454, 0.27799654791075623,
      0.28185967023142589, 0.28555577387589959, 0.28908465481413853,
      0.29244616354745245, 0.29564020502447874, 0.29866673854064957,
      0.30152577762118643, 0.30421738988765545, 0.30674169690814923,
      0.30909887403113934, 0.31128915020307357, 0.31331280776978343,
      0.31517018226176663, 0.31686166216342643, 0.31838768866634681,
      0.3197487554066929, 0.32094540818683781, 0.32197824468128061,
      0.32284791412699021, 0.32355511699826867, 0.32410060466623708,
      0.32448517904306884, 0.32470969221107804, 0.32477504603681712,
      0.32468219177025293, 0.3244321296292304, 0.3240259083692994,
      0.32346462483907479, 0.3227494235212785, 0.32188149605959959,
      0.320862080771537, 0.31969246214738722, 0.31837397033552817,
      0.3169079806141808, 0.31529591284980851, 0.31353923094233849,
      0.31163944225738371, 0.30959809704563857, 0.30741678784965765,
      0.305097148898172, 0.30264085548819175, 0.30004962335503632,
      0.29732520803054141, 0.2944694041896046, 0.29148404498534131,
      0.28837100137298138, 0.28513218142280217, 0.28176952962225882,
      0.27828502616757411, 0.27468068624498876, 0.27095855930191309,
      0.2671207283082086, 0.26316930900783442, 0.25910644916110376,
      0.25493432777777003, 0.2506551543412075, 0.24627116802394022,
      0.24178463689472635, 0.23719785711750252, 0.23251315214238338,
      0.22773287188904118, 0.22285939192265969, 0.21789511262275998,
      0.21284245834514703, 0.20770387657724457, 0.202481837087098,
      0.1971788310662741, 0.19179737026697691, 0.1863399861336284,
      0.18080922892916881, 0.17520766685639658, 0.16953788517457907,
      0.16380248531163688, 0.15800408397218574, 0.15214531224168704,
      0.14622881468702026, 0.14025724845374529, 0.134233282360337,
      0.12815959598967164, 0.12203887877807937, 0.11587382910219868,
      0.10966715336395252, 0.10342156507394351, 0.09713978393351913,
      0.09082453491581835, 0.0844785473460862, 0.078104553981537872,
      0.071705290091050838, 0.065283492535002582, 0.058841898845509416,
      0.052383246307365391, 0.045910271039984005, 0.039425707080596867,
      0.032932285469024505, 0.026432733334294269, 0.019929772983378575,
      0.013426120992369117, 0.0069244873003267149, 0.00042757430612176683,
      -0.00606192403144859, -0.012541323090029761, -0.019007948476224695,
      -0.025459136914039206, -0.031892237128931918, -0.038304610727222618,
      -0.044693633070569776, -0.051056694145260317, -0.057391199426027606,
      -0.063694570734134648, -0.069964247089459183, -0.076197685556320935,
      -0.08239236208276092, -0.088545772333056938, -0.0946554325131652,
      -0.10071888018890041, -0.10673367509651475, -0.11269739994549792,
      -0.11860766121332181, -0.12446208993186889, -0.13025834246533297,
      -0.13599410127931882, -0.14166707570093123, -0.14727500266960192,
      -0.15281564747842494, -0.15828680450577021, -0.16368629793696426,
      -0.16901198247579263, -0.17426174404561262, -0.17943350047987691,
      -0.18452520220182794, -0.18953483289317102, -0.19446041015151871,
      -0.19929998613640046, -0.20405164820363791, -0.20871351952789557,
      -0.21328375971320851, -0.21776056539131194, -0.22214217080756521,
      -0.22642684839433386, -0.23061290933159126, -0.23469870409463553,
      -0.23868262298869838, -0.24256309667032117, -0.24633859665531108,
      -0.25000763581314511, -0.25356876884765256, -0.25702059276384026,
      -0.26036174732071915, -0.26359091546998248, -0.26670682378041621,
      -0.26970824284790518, -0.27259398769091259, -0.27536291813131075,
      -0.278013939160456, -0.28054600129038332, -0.28295810089002649,
      -0.28524928050636045, -0.2874186291703642, -0.28946528268771732,
      -0.29138842391414366, -0.29318728301531305, -0.29486113771123534,
      -0.29640931350506083, -0.29783118389623864, -0.29912617057794133,
      -0.30029374361872629, -0.30133342162837251, -0.30224477190783183,
      -0.30302741058326815, -0.30368100272414222, -0.30420526244530288,
      -0.30459995299306486, -0.30486488681524671, -0.30499992561514694,
      -0.30500498038945578, -0.30488001145008292, -0.30462502842990524,
      -0.30424009027243837, -0.30372530520543012, -0.30308083069839842,
      -0.302306873404128, -0.30140368908413534, -0.30037158251815538,
      -0.29921090739765338, -0.29792206620342321, -0.29650551006728915,
      -0.29496173861799091, -0.29329129981126784, -0.29149478974422172,
      -0.28957285245402453, -0.28752617970101191, -0.28535551073625592,
      -0.283061632053692, -0.2806453771268701, -0.27810762613042306,
      -0.27544930564634057, -0.27267138835514826, -0.26977489271208432,
      -0.26676088260838737, -0.26363046701778936, -0.26038479962835459,
      -0.25702507845975608, -0.25355254546611339, -0.24996848612455108,
      -0.24627422900956597, -0.242471145353373, -0.23856064859234788,
      -0.23454419389973008, -0.23042327770472121, -0.22619943719812752,
      -0.22187424982473652, -0.21744933276254275, -0.21292634238901831,
      -0.20830697373460128, -0.20359295992354565, -0.19878607160234796,
      -0.1938881163558967, -0.18890093811156072, -0.18382641653138476,
      -0.1786664663925884, -0.17342303695655975, -0.16809811132657479,
      -0.16269370579439696, -0.15721186917598406, -0.15165468213654504,
      -0.14602425650509382, -0.14032273457878364, -0.13455228841718764,
      -0.12871511912677427, -0.12281345613581808, -0.11684955645994086,
      -0.11082570395850853, -0.10474420858219, -0.098607405611821436,
      -0.09241765488886329, -0.086177340037695421, -0.079888867679996228,
      -0.0735546666414179, -0.067177187150825726, -0.060758900032409809,
      -0.054302295890806783, -0.04780988428958946, -0.04128419292333714,
      -0.034727766783554659, -0.028143167318696836, -0.021532971588563245,
      -0.014899771413345884, -0.0082461725175679065, -0.0015747936691941217,
      0.00511173418581123, 0.011810768793200605, 0.018519657464188027,
      0.025235737952956579, 0.031956339337564969, 0.038678782904123091,
      0.045400383033817396, 0.052118448092617065, 0.058830281323310557,
      0.06553318173962816, 0.072224445022177758, 0.078901364415883718,
      0.085561231628659071, 0.092201337731062635, 0.098818974056607445,
      0.10541143310248235, 0.11197600943037754, 0.11851000056714744,
      0.12501070790504085, 0.13147543760116392, 0.13790150147597793,
      0.14428621791049143, 0.15062691274186765, 0.15692092015720838,
      0.16316558358520106, 0.16935825658535408, 0.17549630373455666,
      0.1815771015106864, 0.18759803917295834, 0.19355651963882209,
      0.19944996035699805, 0.20527579417652142, 0.21103147021145846,
      0.21671445470098652, 0.2223222318646631, 0.22785230475254148,
      0.23330219608990602, 0.23866944911633481, 0.24395162841886731,
      0.24914632075900667, 0.25425113589324388, 0.2592637073869406,
      0.26418169342127162, 0.26900277759292307, 0.2737246697064209,
      0.2783451065587253, 0.28286185271591546, 0.28727270128169136,
      0.29157547465747768, 0.29576802529387031, 0.29984823643321024,
      0.30381402284303605, 0.30766333154020442, 0.31139414250546421,
      0.31500446938820104, 0.31849236020121469, 0.32185589800526759,
      0.32509320158318122, 0.32820242610332068, 0.33118176377220221,
      0.33402944447606475, 0.33674373641118327, 0.33932294670273239,
      0.34176542201202575, 0.34406954913190746, 0.34623375557014668,
      0.348256510120631, 0.35013632342217194, 0.35187174850481462,
      0.35346138132336491, 0.35490386127808293, 0.35619787172232908,
      0.35734214045698576, 0.3583354402115338, 0.35917658911164785,
      0.3598644511331055, 0.36039793654193064, 0.36077600232059892,
      0.36099765258017658, 0.36106193895828365, 0.36096796100273654,
      0.36071486654074014, 0.3603018520335764, 0.35972816291657633,
      0.3589930939243674, 0.35809598940124565, 0.35703624359656277,
      0.35581330094508168, 0.35442665633217624, 0.352875855343796,
      0.35116049450113251, 0.34928022147989812, 0.34723473531416582,
      0.345023786584672, 0.342647177591562, 0.34010476251151328,
      0.33739644753913334, 0.33452219101269576, 0.33148200352406154,
      0.328275948012805, 0.32490413984452415, 0.32136674687328337,
      0.317663989488151, 0.3137961406438764, 0.30976352587562345,
      0.30556652329781542, 0.30120556358703782, 0.29668112994902218,
      0.29199375806975159, 0.2871440360506371, 0.28213260432781562,
      0.27696015557561632, 0.27162743459416749, 0.26613523818122281,
      0.26048441498820663, 0.25467586536055092, 0.24871054116235636,
      0.24258944558541037, 0.23631363294264932, 0.22988420844611621,
      0.22330232796944957, 0.21656919779500983, 0.20968607434571018,
      0.20265426390159808, 0.19547512230132011, 0.18815005462851811,
      0.18068051488326936, 0.17306800563866642, 0.16531407768260731,
      0.15742032964495878, 0.14938840761017338, 0.14122000471541607,
      0.13291686073444303, 0.1244807616472588, 0.11591353919569163,
      0.10721707042505509, 0.098393277211995839, 0.089444125778704156,
      0.080371626193580833, 0.071177831858528648, 0.061864838983071588,
      0.052434786045366957, 0.04288985324031537, 0.033232261914966615,
      0.023464273991316079, 0.013588191376720266, 0.0036063553620586386,
      -0.0064788539921236676, -0.0166650184813599, -0.026949682394698672,
      -0.037330353163628378, -0.04780450202228638, -0.058369564678813483,
      -0.069022941997607529, -0.079762000692279761, -0.09058407402910057,
      -0.10148646254079909, -0.11246643475040216, -0.12352122790494419,
      -0.13464804871886532, -0.14584407412684888, -0.1571064520458392,
      -0.1684323021460804, -0.17981871663091992, -0.19126276102515039,
      -0.20276147497162655, -0.21431187303599031, -0.22591094551920929,
      -0.23755565927771641, -0.24924295855087733, -0.2609697657956031,
      -0.27273298252782519, -0.28452949017054779, -0.29635615090830553,
      -0.30820980854775315, -0.32008728938406755, -0.33198540307300295,
      -0.34390094350828865, -0.35583068970413695, -0.36777140668259312,
      -0.37971984636540623, -0.39167274847034067, -0.40362684141143573,
      -0.41557884320310379, -0.42752546236776745, -0.43946339884675362,
      -0.45138934491418969, -0.46329998609361589, -0.475192002077092,
      -0.48706206764650684, -0.49890685359677373, -0.5107230276607363,
      -0.522507255435458, -0.53425620130961238, -0.54596652939174273,
      -0.55763490443911434, -0.56925799278688338, -0.5808324632772851,
      -0.59235498818862808, -0.6038222441637906, -0.61523091313795331,
      -0.62657768326528873, -0.63785924984436715, -0.6490723162420271,
      -0.66021359481535558, -0.67127980783159658, -0.68226768838573371,
      -0.693173981315399, -0.70399544411290338, -0.71472884783412072,
      -0.72537097800398365, -0.73591863551825087, -0.7463686375413876,
      -0.75671781840024188, -0.76696303047328684, -0.7771011450751345,
      -0.78712905333612837, -0.79704366707672714, -0.806841919676416,
      -0.81652076693693076, -0.82607718793953921, -0.83550818589612974,
      -0.84481078899385742, -0.85398205123310755, -0.86301905325861239,
      -0.87191890318332022, -0.88067873740496871, -0.889295721415016,
      -0.89776705059971917, -0.90608995103320422, -0.914261680262139,
      -0.92227952808203884, -0.930140817304734, -0.93784290451692642,
      -0.94538318082961748, -0.9527590726181292, -0.95996804225260668,
      -0.96700758881866322, -0.97387524882812748, -0.98056859691959952,
      -0.987085246548575, -0.99342285066709912, -0.99957910239260939,
      -1.005551735665865, -1.0113385258977614, -1.0169372906048386,
      -1.0223458900333515, -1.0275622277716518, -1.0325842513508152,
      -1.0374099528332488, -1.0420373693892147, -1.0464645838610238,
      -1.0506897253147927, -1.0547109695796624, -1.0585265397741908,
      -1.0621347068199443, -1.0655337899420481, -1.0687221571565608,
      -1.071698225744619, -1.0744604627131289, -1.077007385241981,
      -1.0793375611175524, -1.0814496091525274, -1.0833421995917956,
      -1.0850140545043843, -1.0864639481613487, -1.0876907073994455,
      -1.0886932119705695, -1.0894703948768434, -1.0900212426912208,
      -1.0903447958636441, -1.0904401490125444, -1.090306451201716,
      -1.0899429062024237, -1.0893487727407587, -1.0885233647300947,
      -1.0874660514886629, -1.0861762579421634, -1.0846534648113544,
      -1.0828972087846329, -1.0809070826755054, -1.0786827355649315,
      -1.0762238729285767, -1.0735302567488469, -1.0706017056117614,
      -1.0674380947886273, -1.0640393563025057, -1.0604054789794453,
      -1.0565365084845189, -1.0524325473426397, -1.0480937549441545,
      -1.0435203475352703, -1.0387125981932832, -1.0336708367866263,
      -1.0283954499198436, -1.0228868808633997, -1.0171456294684289,
      -1.0111722520664814, -1.0049673613542371, -0.99853162626328729,
      -0.99186577181502378, -0.98497057896068341, -0.97784688440659806,
      -0.97049558042473638, -0.96291761464858094, -0.95511398985443985,
      -0.94708576372822129, -0.93883404861779318, -0.93036001127101875,
      -0.92166487255950058, -0.91274990718816529, -0.9036164433907774,
      -0.89426586261150276, -0.88469959917256713, -0.87491913992814674,
      -0.86492602390465567, -0.85472184192744738, -0.84430823623408124,
      -0.83368690007435342, -0.82285957729708448, -0.81182806192391244,
      -0.80059419771011842, -0.78915987769273188, -0.77752704372594561,
      -0.76569768600406574, -0.75367384257208225, -0.74145759882408113,
      -0.72905108698956056, -0.7164564856078619, -0.70367601899088539,
      -0.6907119566742399, -0.67756661285691255, -0.66424234582978847,
      -0.65074155739304573, -0.63706669226267321, -0.62322023746622834,
      -0.60920472172811879, -0.595022714844477, -0.58067682704786938,
      -0.56616970836201186, -0.55150404794670127, -0.53668257343313275,
      -0.52170805024979128, -0.50658328093912985, -0.49131110446527149,
      -0.47589439551283863, -0.46033606377716968, -0.44463905324619868,
      -0.4288063414740656, -0.41284093884673445, -0.39674588783988296,
      -0.38052426226919756, -0.36417916653330684, -0.34771373484958679,
      -0.331131130483039, -0.31443454496854073, -0.29762719732649195,
      -0.28071233327229733, -0.263693224419837, -0.24657316747905175,
      -0.2293554834480046, -0.21204351679957645, -0.19464063466305026,
      -0.17715022600079963, -0.15957570078026573, -0.14192048914160016,
      -0.1241880405610354, -0.10638182301027516, -0.088505322112225351,
      -0.070562040293172937, -0.052555495931711507, -0.034489222504626924,
      -0.016366767730015844, 0.0018083072921661475, 0.020032428941902908,
      0.038302011942976832, 0.0566134602286521, 0.074963167809030826,
      0.0933475196397715, 0.11176289249192174, 0.13020565582262872,
      0.14867217264666052, 0.167158800408191, 0.18566189185287979,
      0.2041777958999077, 0.22270285851373911, 0.24123342357538652,
      0.25976583375291185, 0.27829643137100718, 0.2968215592793797,
      0.31533756171964805, 0.33384078519066185, 0.35232757931189707,
      0.37079429768474126, 0.38923729875145008, 0.40765294665152219,
      0.42603761207535984, 0.44438767311480121, 0.46269951611053117,
      0.48096953649601659, 0.49919413963773884, 0.51736974167157279,
      0.53549277033507348, 0.55355966579545335, 0.571566881473035,
      0.58951088485991654, 0.607388158333819, 0.625195199966695,
      0.6429285243279923, 0.66058466328240018, 0.67816016678186075,
      0.695651603651578, 0.71305556236990741, 0.73036865184192246,
      0.74758750216645908, 0.76470876539640231, 0.7817291162920974,
      0.7986452530676984, 0.81545389813021119, 0.8321517988110767,
      0.84873572809018916, 0.8652024853120811, 0.88154889689412042,
      0.89777181702660891, 0.91386812836457121, 0.92983474271106881,
      0.94566860169186528, 0.96136667742135951, 0.97692597315956764,
      0.99234352395999248, 1.007616397308237, 1.0227416937513445,
      1.037716547517485, 1.0525381271260406, 1.0672036359878876,
      1.08171031299575, 1.0960554331044783, 1.1102363079011197,
      1.124250286164711, 1.1380947544156403, 1.1517671374544056,
      1.1652648988897627, 1.178585541656088, 1.1917266085198326,
      1.204685682575013, 1.217460387727606, 1.2300483891687766,
      1.2424473938368166, 1.2546551508676913, 1.2666694520341948,
      1.2784881321735113, 1.2901090696031694, 1.3015301865253306,
      1.3127494494192966, 1.3237648694221709, 1.3345745026976144,
      1.3451764507926822, 1.3555688609825982, 1.3657499266034407,
      1.3757178873727405, 1.3854710296978923, 1.3950076869723131,
      1.4043262398593659, 1.4134251165639866, 1.4223027930919665,
      1.4309577934968654, 1.439388690114543, 1.4475941037852846,
      1.4555727040634749, 1.4633232094148214, 1.4708443874011297,
      1.4781350548526173, 1.4851940780276986, 1.4920203727603434,
      1.4986129045949419, 1.5049706889086716, 1.5110927910214345,
      1.5169783262933143, 1.5226264602095982, 1.5280364084534059,
      1.5332074369658537, 1.5381388619939353, 1.542830050125976,
      1.5472804183148263, 1.5514894338887419, 1.5554566145500568,
      1.5591815283616395, 1.5626637937211822, 1.5659030793234197,
      1.5688991041102818, 1.571651637209017, 1.5741604978584234,
      1.5764255553231679, 1.5784467287962933, 1.5802239872899839,
      1.5817573495146426, 1.5830468837463634, 1.5840927076828772,
      1.5848949882880343, 1.5854539416249303, 1.5857698326777234,
      1.5858429751622936, 1.5856737313257281, 1.5852625117348507,
      1.5846097750538031, 1.583716027810796, 1.5825818241541594,
      1.5812077655977428, 1.57959450075584, 1.5777427250676703,
      1.5756531805115983, 1.5733266553091381, 1.5707639836189256,
      1.5679660452207198, 1.5649337651895812, 1.5616681135603465,
      1.5581701049825287, 1.5544407983657276, 1.5504812965157797,
      1.54629274576164, 1.5418763355732552, 1.53723329817048, 1.5323649081232118,
      1.5272724819428685, 1.5219573776653648, 1.5164209944256952,
      1.5106647720243191, 1.5046901904854457, 1.498498769607375,
      1.4920920685050876, 1.4854716851451537, 1.4786392558732038,
      1.471596454934019, 1.4643449939844981, 1.4568866215995517,
      1.4492231227711561, 1.4413563184007119, 1.4332880647848192,
      1.4250202530947067, 1.4165548088493993, 1.4078936913828386,
      1.3990388933051019, 1.3899924399578794, 1.3807563888643732,
      1.3713328291738076, 1.3617238811006942, 1.3519316953589782,
      1.3419584525913761, 1.3318063627938683, 1.3214776647357009,
      1.3109746253749412, 1.3002995392698342, 1.2894547279860775,
      1.278442539500203, 1.2672653475992752, 1.2559255512769787,
      1.2444255741263963, 1.2327678637295136, 1.2209548910437422,
      1.2089891497855505, 1.1968731558113779, 1.184609446496079,
      1.17220058010896, 1.1596491351876759, 1.1469577099100627,
      1.1341289214641863, 1.1211654054166769, 1.1080698150795494,
      1.0948448208757195, 1.0814931097033396, 1.0680173842991221,
      1.0544203626008246, 1.0407047771090983, 1.0268733742487755,
      1.0129289137299011, 0.99887416790848349, 0.98471192114734862,
      0.97044496917705181, 0.95607611845713347, 0.94160818553788539,
      0.92704399642266666, 0.91238638593110133, 0.89763819706313,
      0.88280228036426134, 0.86788149329199327, 0.85287869958368634,
      0.83779676862603236, 0.82263857482613933, 0.80740699698461638,
      0.79210491767053748, 0.77673522259865835, 0.76130080000890954,
      0.74580454004830909, 0.73024933415550308, 0.71463807444804517,
      0.69897365311251936, 0.68325896179766177, 0.66749689101069343,
      0.65169032951684547, 0.63584216374237723, 0.61995527718107313,
      0.60403254980446341, 0.58807685747581662, 0.57209107136804449,
      0.55607805738571181, 0.54004067559114421, 0.52398177963489689,
      0.50790421619056247, 0.49181082439418572, 0.475704435288237,
      0.45958787127037881, 0.44346394554709967, 0.42733546159228419,
      0.41120521261090653, 0.39507598100782482, 0.37895053786196109,
      0.36283164240576937, 0.3467220415102033, 0.33062446917530108,
      0.314541646026381, 0.29847627881602246, 0.28243105993187134,
      0.26640866691041365, 0.25041176195669573, 0.23444299147024661,
      0.21850498557704873, 0.20260035766788925, 0.18673170394295807,
      0.17090160296284854, 0.15511261520611436, 0.13936728263324763,
      0.12366812825737657, 0.10801765572154223, 0.09241834888278691,
      0.07687267140298408, 0.061383066346507753, 0.04595195578487403,
      0.030581740408241354, 0.015274799144007783, 3.3488782389248795E-5,
      -0.015139856390856743, -0.030242924954579614, -0.045273428705229657,
      -0.060229103002608669, -0.075107707108333754, -0.089907024517070111,
      -0.10462486328043755, -0.11925905632350242, -0.13380746175397457,
      -0.14826796316394131, -0.16263846992423481, -0.17691691747129126,
      -0.1911012675865976, -0.20518950866865937, -0.21917965599743422,
      -0.23306975199133403, -0.24685786645663477, -0.26054209682946144,
      -0.27412056841015264, -0.28759143459018405, -0.30095287707153595,
      -0.3142031060785071, -0.32734036056208621, -0.34036290839671324,
      -0.35326904656963176, -0.36605710136267183, -0.37872542852658936,
      -0.39127241344795388, -0.403696471308529, -0.41599604723725331,
      -0.42816961645481544, -0.44021568441083125, -0.45213278691362474,
      -0.46391949025272072, -0.47557439131395457, -0.48709611768738104,
      -0.49848332776784082, -0.50973471084836719, -0.52084898720639616,
      -0.53182490818279538, -0.54266125625384465, -0.55335684509605731,
      -0.56391051964406735, -0.574321156141455, -0.58458766218466285,
      -0.59470897676003875, -0.604684070273971, -0.614511944576293,
      -0.624191632976884, -0.6337222002556262, -0.64310274266567036,
      -0.65233238793015713, -0.661410295232398, -0.67033565519956828,
      -0.67910768988000181, -0.68772565271413943, -0.69618882849918939,
      -0.70449653334752826, -0.71264811463898925, -0.72064295096700937,
      -0.728480452078779, -0.7361600588093975, -0.74368124301015137,
      -0.75104350747097437, -0.75824638583712523, -0.76528944252021391,
      -0.77217227260357646, -0.77889450174215591, -0.78545578605688193,
      -0.79185581202368072, -0.79809429635717744, -0.80417098588912017,
      -0.81008565744171035, -0.81583811769577175, -0.82142820305399367,
      -0.82685577949918443, -0.83212074244771506, -0.83722301659819853,
      -0.842162555775459, -0.84693934276991656, -0.8515533891724546,
      -0.85600473520482656, -0.86029344954573517, -0.86441962915260362,
      -0.86838339907917828, -0.8721849122890224, -0.87582434946497223,
      -0.87930191881465736, -0.88261785587218722, -0.88577242329602368,
      -0.88876591066320076, -0.89159863425992858, -0.89427093686867376,
      -0.89678318755182318, -0.89913578143196649, -0.90132913946895155,
      -0.90336370823374224, -0.90523995967915438, -0.9069583909076373,
      -0.90851952393608193, -0.90992390545779245, -0.91117210660172132,
      -0.91226472268899617, -0.91320237298688234, -0.913985700460217,
      -0.91461537152042616, -0.91509207577219154, -0.91541652575785815,
      -0.9155894566996654, -0.915611626239863, -0.9154838141788264,
      -0.9152068222112193, -0.91478147366032125, -0.91420861321053482,
      -0.91348910663822736, -0.91262384054094747, -0.91161372206507241,
      -0.91045967863201827, -0.90916265766303939, -0.90772362630271064,
      -0.906143571141197, -0.90442349793530807, -0.90256443132852082,
      -0.90056741456992562, -0.89843350923226273, -0.89616379492908149,
      -0.89375936903106479, -0.89122134638164863, -0.88855085901197883,
      -0.88574905585523123, -0.88281710246045619, -0.87975618070590722,
      -0.87656748851201727, -0.87325223955399689, -0.8698116629742102,
      -0.86624700309429914, -0.86255951912719742, -0.85875048488904815,
      -0.85482118851108058, -0.8507729321515638, -0.84660703170781226,
      -0.84232481652836222, -0.83792762912535934, -0.83341682488719282,
      -0.82879377179146707, -0.82405985011830807, -0.81921645216414363,
      -0.81426498195589514, -0.80920685496574, -0.80404349782642781,
      -0.79877634804719788, -0.7934068537304042, -0.78793647328881178,
      -0.782366675163657, -0.77669893754354358, -0.770934748084126,
      -0.76507560362871307, -0.7591230099297922, -0.75307848137150013,
      -0.74694354069311708, -0.74071971871357178, -0.73440855405706174,
      -0.72801159287973816, -0.72153038859756213, -0.71496650161534159,
      -0.70832149905693809, -0.70159695449677661, -0.69479444769254339,
      -0.68791556431926593, -0.68096189570464527, -0.67393503856578008,
      -0.666836594747251, -0.65966817096060992, -0.652431378525308,
      -0.64512783311101751, -0.63775915448150133, -0.63032696623990014,
      -0.62283289557555266, -0.61527857301235023, -0.60766563215861735,
      -0.59999570945856906, -0.59227044394531059, -0.58449147699546478,
      -0.57666045208536376, -0.56877901454889024, -0.56084881133691178,
      -0.55287149077837483, -0.54484870234303961, -0.53678209640584384,
      -0.52867332401298606, -0.52052403664961588, -0.5123358860092474,
      -0.50411052376482379, -0.49584960134149558, -0.48755476969106593,
      -0.47922767906812791, -0.47086997880793358, -0.46248331710590435,
      -0.454069340798891, -0.44562969514810263, -0.4371660236237388,
      -0.42867996769131017, -0.42017316659968279, -0.41164725717076345,
      -0.40310387359092903, -0.39454464720410209, -0.38597120630649928,
      -0.37738517594310178, -0.36878817770573419, -0.36018182953285838,
      -0.351567745510976, -0.34294753567772351, -0.33432280582657459,
      -0.32569515731317716, -0.31706618686334442, -0.30843748638261748,
      -0.29981064276746827, -0.29118723771805904, -0.28256884755263251,
      -0.27395704302343948, -0.26535338913422779, -0.25675944495932213,
      -0.24817676346417517, -0.23960689132752508, -0.23105136876499027,
      -0.22251172935422847, -0.21398949986154941, -0.20548620006999907,
      -0.19700334260894925, -0.1885424327850832, -0.18010496841486306,
      -0.17169243965836647, -0.16330632885460938, -0.15494811035817627,
      -0.14661925037730505, -0.13832120681328408, -0.13005542910124293,
      -0.12182335805226084, -0.11362642569678875, -0.10546605512942771,
      -0.097343660354937037, -0.089260646135596353, -0.081218407839787468,
      -0.073218331291835664, -0.065261792623132517, -0.057350158124434183,
      -0.049484784099415924, -0.041667016719393934, -0.033898191879279393,
      -0.026179635054655842, -0.01851266116006825, -0.010898574408438583,
      -0.0033386681716114641, 0.0041657751579550206, 0.011613484304371868,
      0.019003199244435526, 0.026333671342628678, 0.033603663485019364,
      0.040811950212133769, 0.047957317850714221, 0.0550385646444867,
      0.062054500883810232, 0.069003949034352419, 0.075885743864727184,
      0.0826987325730699, 0.089441774912677269, 0.096113743316565248,
      0.1027135230210991, 0.10924001218858223, 0.11569212202887533,
      0.12206877692006518, 0.12836891452810451, 0.13459148592552142,
      0.14073545570916016, 0.1467998021169328, 0.15278351714363153,
      0.15868560665577475, 0.16450509050550888, 0.17024100264351325,
      0.17589239123101691, 0.181458318750784, 0.18693786211720143,
      0.19233011278537709, 0.19763417685929, 0.20284917519897097,
      0.20797424352673435, 0.21300853253240662, 0.21795120797762896,
      0.22280145079913022, 0.2275584572110611, 0.2322214388063257,
      0.23678962265687353, 0.24126225141307625, 0.24563858340198882,
      0.24991789272467957, 0.25409946935247851, 0.25818261922219365,
      0.26216666433030222, 0.26605094282603703, 0.26983480910345403,
      0.27351763389235728, 0.27709880434818346, 0.28057772414070459,
      0.28395381354170612, 0.28722650951140194, 0.29039526578378927,
      0.293459552950805, 0.29641885854524908, 0.29927268712258615,
      0.30202056034143776, 0.3046620170428922, 0.3071966133285321,
      0.30962392263717353, 0.31194353582032308, 0.314155061216305,
      0.31625812472304626, 0.31825236986950045, 0.3201374578856741,
      0.32191306777127049, 0.32357889636288562, 0.32513465839973765,
      0.32658008658795046, 0.32791493166328722, 0.32913896245240848,
      0.33025196593253137, 0.33125374728953022, 0.33214412997441561,
      0.332922955758218, 0.33359008478514973, 0.33414539562413048,
      0.33458878531858144, 0.334920169434441, 0.33513948210648248,
      0.3352466760827495, 0.33524172276719688, 0.3351246122604965,
      0.33489535339888138, 0.33455397379114604, 0.33410051985364236,
      0.33353505684331264, 0.3328576688887086, 0.33206845901896537,
      0.331167549190688, 0.33015508031277552, 0.32903121226902188,
      0.32779612393864954, 0.32645001321454553, 0.32499309701933532,
      0.32342561131915992, 0.32174781113513407, 0.31995997055253006,
      0.31806238272753812, 0.31605535989167932, 0.31393923335376028,
      0.31171435349939181, 0.30938108978799772, 0.30693983074731318,
      0.30439098396533842, 0.30173497607965089, 0.29897225276420653,
      0.296103278713354, 0.29312853762330232, 0.29004853217077431,
      0.28686378398896917, 0.283574833640751, 0.28018224058900282,
      0.27668658316417855, 0.27308845852898045, 0.26938848264013515,
      0.26558729020725624, 0.26168553464874894, 0.25768388804474568,
      0.25358304108703184, 0.24938370302591339, 0.2450866016140606,
      0.24069248304722746, 0.23620211190188739, 0.23161627106969404,
      0.22693576168879986, 0.22216140307197402, 0.21729403263151295,
      0.21233450580090252, 0.20728369595321824, 0.20214249431625977,
      0.19691180988435036, 0.1915925693268308, 0.1861857168932142,
      0.18069221431493282, 0.17511304070375372, 0.16944919244674383,
      0.16370168309785765, 0.15787154326604097, 0.15195982049990941,
      0.1459675791689618, 0.13989590034129751, 0.13374588165782725,
      0.12751863720301004, 0.12121529737202549, 0.11483700873445858,
      0.10838493389440164, 0.10186025134703663, 0.095264155331661757,
      0.088597855681094281, 0.081862577667608433, 0.075059561845172471,
      0.068190063888220964, 0.061255354426762873, 0.054256718877926352,
      0.047195457273932304, 0.040072884086473859, 0.032890328047492423,
      0.025649131966389641, 0.018350652543674545, 0.010996260180960171,
      0.003587338787510802, -0.0038747144168986003, -0.01138848910259152,
      -0.018952562034189296, -0.026565497278331962, -0.03422584641493423,
      -0.0419321487519399, -0.049682931543589548, -0.057476710212194249,
      -0.065311988573309859, -0.073187259064452559, -0.08110100297717493,
      -0.089051690692598717, -0.097037781920334049, -0.10505772594074472,
      -0.11310996185061045, -0.12119291881204369, -0.1293050163048029,
      -0.13744466438176123, -0.14561026392770374, -0.15380020692132837,
      -0.16201287670037604, -0.17024664822997038, -0.17849988837405098,
      -0.18677095616989303, -0.19505820310565561, -0.20335997340100193,
      -0.21167460429058754, -0.22000042631061267, -0.2283357635881344,
      -0.23667893413333083, -0.24502825013453122, -0.25338201825599427,
      -0.26173853993844914, -0.27009611170224745, -0.27845302545320294,
      -0.2868075687909446, -0.29515802531984148, -0.30350267496236688,
      -0.31183979427488834, -0.32016765676583536, -0.32848453321614779,
      -0.33678869200202177, -0.34507839941977947, -0.35335192001297944,
      -0.36160751690147774, -0.3698434521126282, -0.378057986914333,
      -0.38624938215005183, -0.39441589857560433, -0.40255579719776,
      -0.41066733961447333, -0.4187487883568039, -0.4267984072323604,
      -0.43481446167023374, -0.44279521906736097, -0.4507389491362398,
      -0.45864392425389094, -0.46650841981205393, -0.47433071456848142,
      -0.48210909099930943, -0.48984183565238326, -0.49752723950148048,
      -0.50516359830138891, -0.512749212943671, -0.52028238981312436,
      -0.52776144114482459, -0.53518468538166242, -0.54255044753227533,
      -0.5498570595293637, -0.55710286058820213, -0.56428619756537923,
      -0.57140542531755145, -0.578458907060258, -0.58544501472661925,
      -0.59236212932583587, -0.59920864130148632, -0.60598295088940424,
      -0.612683468475171, -0.619308614951053, -0.62585682207233739,
      -0.63232653281294271, -0.63871620172024279, -0.645024295269025,
      -0.6512492922144153, -0.65738968394379937, -0.66344397482752993,
      -0.6694106825684, -0.67528833854979664, -0.68107548818235153,
      -0.68677069124914381, -0.6923725222492052, -0.69787957073935769,
      -0.70329044167422117, -0.70860375574431245, -0.71381814971217339,
      -0.7189322767463957, -0.72394480675344153, -0.72885442670723011,
      -0.73365984097632964, -0.7383597716486896, -0.74295295885382673,
      -0.74743816108234939, -0.75181415550276665, -0.75607973827542485,
      -0.76023372486356566, -0.76427495034132986, -0.76820226969867833,
      -0.77201455814308273, -0.7757107113979741, -0.77928964599775608,
      -0.7827502995793777, -0.786091631170347, -0.78931262147308012,
      -0.79241227314551432, -0.7953896110779104, -0.79824368266571111,
      -0.80097355807842519, -0.80357833052440808, -0.80605711651148271,
      -0.80840905610328484, -0.810633313171269, -0.81272907564231855,
      -0.8146955557417922, -0.81653199023203193, -0.81823764064617255,
      -0.81981179351720279, -0.82125376060220523, -0.82256287910166992,
      -0.82373851187385139, -0.824780047644023, -0.82568690120863653,
      -0.82645851363423373, -0.82709435245109642, -0.82759391184153741,
      -0.82795671282273642, -0.82818230342413246, -0.82827025885918826,
      -0.8282201816915733, -0.82803170199561782, -0.8277044775110054,
      -0.82723819379165642, -0.826632564348702, -0.8258873307875183,
      -0.82500226293874179, -0.82397715898323654, -0.82281184557090614,
      -0.82150617793336322, -0.82006003999032973, -0.81847334444978681,
      -0.81674603290174874, -0.814878075905697, -0.81286947307154289,
      -0.8107202531341331 } ;

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
      0.0, 0.70352538663857778, 0.70468014035492677, 0.70577257300814855,
      0.70680227768812, 0.70776886323404364, 0.70867195440916686,
      0.709511192070584, 0.7102862333340384, 0.71099675173365351,
      0.71164243737651878, 0.71222299709206072, 0.71273815457612544,
      0.71318765052971123, 0.71357124279227846, 0.71388870646958014,
      0.71413983405594239, 0.71432443555094283, 0.714442338570423,
      0.71449338845177857, 0.71447744835347737, 0.71439439934874871,
      0.71424414051339036, 0.71402658900765559, 0.71374168015216155,
      0.71338936749778181, 0.71296962288947907, 0.71248243652403975,
      0.71192781700166685, 0.7113057913714016, 0.71061640517033775,
      0.70985972245659668, 0.70903582583603375, 0.70814481648264949,
      0.70718681415268336, 0.70616195719236152, 0.70507040253928355,
      0.70391232571743, 0.7026879208257707, 0.70139740052046484,
      0.70004099599064051, 0.69861895692774367, 0.69713155148845207,
      0.695579066251147, 0.69396180616594538, 0.69228009449828887,
      0.69053427276609491, 0.68872470067047464, 0.68685175602002491,
      0.6849158346487032, 0.68291735032730239, 0.68085673466853447,
      0.6787344370257421, 0.676550924385259, 0.67430668125244064,
      0.672002209531386, 0.66963802839838082, 0.66721467416909008,
      0.664732700159528, 0.66219267654084535, 0.65959519018795976,
      0.65694084452208035, 0.65423025934715151, 0.65146407068027434,
      0.64864293057613831, 0.64576750694551621, 0.64283848336787075,
      0.63985655889812443, 0.636822447867646, 0.63373687967951065,
      0.63060059859808981, 0.62741436353303814, 0.624178947817727,
      0.62089513898220261, 0.6175637385207311, 0.61418556165399318,
      0.61076143708601216, 0.60729220675587448, 0.603778725584329,
      0.60022186121533494, 0.59662249375264376, 0.59298151549148859,
      0.58929983064547176, 0.5855783550687288, 0.58181801597346294,
      0.57801975164292962, 0.57418451113996949, 0.57031325401117816,
      0.56640694998680841, 0.5624665786764983, 0.55849312926092454,
      0.5544876001794804, 0.55045099881407644, 0.5463843411691709,
      0.54228865154812744, 0.53816496222601151, 0.53401431311892844,
      0.52983775145001333, 0.52563633141218169, 0.521411113827753,
      0.51716316580505761, 0.51289356039214384, 0.50860337622769825,
      0.50429369718929351, 0.49996561203908785, 0.49562021406708612,
      0.49125860073208949, 0.48688187330045141, 0.48249113648275854,
      0.47808749806856787, 0.47367206855931487, 0.46924596079952197,
      0.46481028960643311, 0.46036617139819735, 0.45591472382073328,
      0.45145706537339675, 0.44699431503358522, 0.44252759188040358,
      0.43805801471752531, 0.43358670169537472, 0.42911476993276421,
      0.42464333513811747, 0.42017351123040714, 0.41570640995994224,
      0.4112431405291358, 0.40678480921338706, 0.40233251898220557,
      0.39788736912071787, 0.39345045485168278, 0.389022866958152,
      0.38460569140690803, 0.38020000897281164, 0.37580689486419344,
      0.37142741834942083, 0.3670626423847731, 0.36271362324375822,
      0.35838141014800134, 0.35406704489984064, 0.34977156151675404,
      0.34549598586776081, 0.34124133531191275, 0.33700861833901929,
      0.33279883421272705, 0.3286129726160853, 0.32445201329972689,
      0.320316925732791, 0.31620866875671488, 0.31212819024201732,
      0.30807642674820795, 0.30405430318693438, 0.30006273248850163,
      0.29610261527187881, 0.29217483951831891, 0.28828028024870944,
      0.284419799204773, 0.28059424453423909, 0.27680445048010066,
      0.2730512370740712, 0.26933540983435844, 0.26565775946786846,
      0.26201906157694693, 0.25842007637077369, 0.25486154838151676,
      0.2513442061853518, 0.2478687621284541, 0.24443591205807064,
      0.24104633505876663, 0.23770069319395681, 0.23439963125281324,
      0.23114377650265194, 0.22793373844689166, 0.22477010858868068,
      0.22165346020028009, 0.21858434809830013, 0.21556330842487012,
      0.21259085843483466, 0.20966749628905848, 0.20679370085392135,
      0.20396993150708403, 0.20119662794960505, 0.19847421002448132,
      0.19580307754169179, 0.1931836101098095, 0.19061616697425707,
      0.18810108686227148, 0.18563868783464305, 0.18322926714429066,
      0.18087310110173807, 0.1785704449475419, 0.17632153273173751,
      0.17412657720034858, 0.17198576968901347, 0.1698992800237803,
      0.16786725642911349, 0.16588982544315722, 0.16396709184029909,
      0.16209913856106795, 0.16028602664941133, 0.15852779519737487,
      0.15682446129722583, 0.15517602000104364, 0.15358244428780415,
      0.15204368503798696, 0.15055967101571682, 0.14913030885846904,
      0.14775548307434566, 0.14643505604694296, 0.14516886804781415,
      0.14395673725654373, 0.1427984597884287, 0.14169380972978035,
      0.14064253918083741, 0.13964437830629625, 0.13869903539344458,
      0.1378061969178988, 0.13696552761693098, 0.13617667057036939,
      0.13543924728906456, 0.13475285781089386, 0.13411708080429097,
      0.13353147367927065, 0.13299557270592735, 0.13250889314037473,
      0.13207092935809708, 0.13168115499467778, 0.13133902309386836,
      0.13104396626295617, 0.13079539683539343, 0.13059270704063894,
      0.13043526918116791, 0.13032243581659669, 0.13025353995487624,
      0.13022789525049411, 0.13024479620962762, 0.13030351840219592,
      0.13040331868073768, 0.1305434354060582, 0.13072308867957655,
      0.1309414805823011, 0.13119779542036411, 0.1314911999770407,
      0.13182084377117487, 0.13218585932193333, 0.13258536241980787,
      0.13301845240378168, 0.13348421244457137, 0.1339817098338639,
      0.13450999627944921, 0.13506810820616319, 0.13565506706254521,
      0.13626987963310913, 0.13691153835613834, 0.13757902164689409,
      0.13827129422614243, 0.1389873074538919, 0.13972599966823473,
      0.14048629652918623, 0.14126711136740938, 0.14206734553771366,
      0.14288588877721628, 0.14372161956804538, 0.14457340550447439,
      0.1454401036643638, 0.14632056098479132, 0.14721361464174867,
      0.14811809243378235, 0.14903281316945105, 0.14995658705847434,
      0.15088821610644582, 0.15182649451297831, 0.15277020907315331,
      0.15371813958214167, 0.15466905924286289, 0.15562173507654647,
      0.15657492833606285, 0.15752739492188519, 0.15847788580054564,
      0.15942514742544467, 0.16036792215987919, 0.16130494870214268,
      0.16223496251256009, 0.16315669624231374, 0.16406888016391724,
      0.16497024260319515, 0.16585951037261998, 0.16673540920586793,
      0.16759666419344171, 0.16844200021921787, 0.16927014239777086,
      0.17007981651232698, 0.1708697494532021, 0.17163866965657298,
      0.17238530754343745, 0.17310839595861224, 0.17380667060962357,
      0.17447887050533817, 0.17512373839419126, 0.17574002120185678,
      0.17632647046821925, 0.17688184278349245, 0.17740490022333852,
      0.17789441078284329, 0.178349148809195, 0.1787678954329221,
      0.17914943899754232, 0.17949257548747916, 0.17979610895409248,
      0.18005885193968707, 0.18027962589934723, 0.18045726162045711,
      0.1805905996397591, 0.18067849065781288, 0.18071979595070775,
      0.18071338777888771, 0.18065814979295453, 0.18055297743630028,
      0.18039677834443693, 0.18018847274088473, 0.1799269938294813,
      0.1796112881829752, 0.17924031612777364, 0.17881305212470744,
      0.17832848514568483, 0.17778561904609808, 0.17718347293286416,
      0.17652108152795859, 0.17579749552732679, 0.17501178195504452,
      0.17416302451260351, 0.1732503239231995, 0.17227279827090927,
      0.17122958333462893, 0.17011983291666333, 0.16894271916585232,
      0.16769743289511388, 0.16638318389330295, 0.16499920123126574,
      0.16354473356199273, 0.16201904941475706, 0.16042143748313628,
      0.15875120690682165, 0.15700768754710681, 0.155190230255964,
      0.15329820713861556, 0.1513310118094974, 0.14928805964153435,
      0.14716878800863428, 0.14497265652131394, 0.14269914725537391,
      0.14034776497354023, 0.13791803733999597, 0.13540951512772281,
      0.13282177241857546, 0.1301544067960298, 0.12740703953051524,
      0.12457931575728398, 0.12167090464673729, 0.11868149956715882,
      0.11561081823978508, 0.11245860288616402, 0.10922462036774506,
      0.10590866231764685, 0.1025105452645572, 0.099030110748715469,
      0.0954672254299401, 0.09182178118764911, 0.088093695212851222,
      0.084282910092054547, 0.0803893938830772, 0.07641314018271525,
      0.072354168186253759, 0.068212522738784184, 0.063988274378318319,
      0.059681519370671912, 0.055292379736104208, 0.050821003267703072,
      0.0462675635415018, 0.041632259918322034, 0.036915317537337691,
      0.032116987301358729, 0.027237545853835615, 0.022277295547585355,
      0.017236564405254937, 0.012115706071518462, 0.0069150997570314732,
      0.0016351501741544983, -0.0037237125355415734, -0.0091610328819561049,
      -0.014676330115314024, -0.020269098323158541, -0.025938806535462072,
      -0.03168489883781278, -0.03750679449264907, -0.043403888068502983,
      -0.049375549577212963, -0.05542112461905449, -0.061539934535756596,
      -0.067731276571345672, -0.0739944240407672, -0.080328626506232653,
      -0.086733109961234733, -0.093207077022170293, -0.099749707127512577,
      -0.10636015674446317, -0.11303755958301537, -0.11978102681737343,
      -0.126589647314634, -0.13346248787067228, -0.14039859345314409,
      -0.14739698745153784, -0.15445667193417417, -0.16157662791209279,
      -0.16875581560971528, -0.1759931747422141, -0.18328762479948768,
      -0.19063806533664668, -0.19804337627091806, -0.2055024181848665,
      -0.21301403263583732, -0.22057704247151347, -0.2281902521514805,
      -0.23585244807470054, -0.24356239891277545, -0.251318855948902,
      -0.2591205534223896, -0.26696620887864053, -0.27485452352446726,
      -0.28278418258863519, -0.29075385568749934, -0.2987621971956258,
      -0.30680784662126581, -0.31488942898656558, -0.32300555521236496,
      -0.3311548225074849, -0.33933581476235086, -0.34754710294683006,
      -0.35578724551214735, -0.36405478879674419, -0.37234826743594868,
      -0.38066620477531549, -0.38900711328749593, -0.39736949499250668,
      -0.405751841881241, -0.41415263634210386, -0.42257035159059753,
      -0.43100345210174718, -0.43945039404518732, -0.447909625722796,
      -0.4563795880087016, -0.46485871479153673, -0.47334543341877078,
      -0.48183816514299638, -0.49033532556999193, -0.498835325108438,
      -0.5073365694211045, -0.51583745987740093, -0.52433639400708765,
      -0.53283176595503923, -0.54132196693687573, -0.54980538569533532,
      -0.55828040895721165, -0.56674542189072064, -0.57519880856313066,
      -0.58363895239851449, -0.59206423663545849, -0.60047304478458674,
      -0.60886376108573059, -0.61723477096461432, -0.62558446148887892,
      -0.63391122182331328, -0.64221344368412214, -0.6504895217920883,
      -0.65873785432448817, -0.66695684336557592, -0.675144895355534,
      -0.68330042153768722, -0.69142183840388516, -0.69950756813785353,
      -0.7075560390564074, -0.71556568604835, -0.7235349510109339,
      -0.7314622832837212, -0.73934614007970945, -0.74718498691357282,
      -0.75497729802689073, -0.762721556810194, -0.77041625622172816,
      -0.77805989920275054, -0.78565099908927216, -0.79318808002006036,
      -0.8006696773408043, -0.80809433800429142, -0.81546062096646188,
      -0.8227670975782263, -0.83001235197289791, -0.83719498144912718,
      -0.84431359684920138, -0.85136682293259569, -0.85835329874465038,
      -0.8652716779802444, -0.87212062934235934, -0.87889883689541159,
      -0.88560500041324008, -0.89223783572162552, -0.89879607503524839,
      -0.90527846728896344, -0.91168377846328619, -0.91801079190399015,
      -0.92425830863570813, -0.93042514766943751, -0.93651014630385643,
      -0.94251216042034336, -0.94843006477162073, -0.95426275326391863,
      -0.96000913923257392, -0.96566815571098175, -0.97123875569281,
      -0.97671991238739131, -0.98211061946822642, -0.98740989131450685,
      -0.99261676324559023, -0.99773029174835337, -1.002749554697361,
      -1.007673651567766, -1.0125017036409012, -1.017232854202474,
      -1.0218662687333344, -1.0264011350927302, -1.0308366636940189,
      -1.0351720876727732, -1.0394066630472392, -1.0435396688710923,
      -1.0475704073784622, -1.0514982041211698, -1.0553224080981567,
      -1.0590423918770635, -1.0626575517079222, -1.0661673076289404,
      -1.0695711035643594, -1.0728684074143395, -1.0760587111368776,
      -1.0791415308217274, -1.0821164067563083, -1.0849829034835954,
      -1.0877406098519837, -1.0903891390571112, -1.0929281286756465,
      -1.0953572406910488, -1.0976761615112798, -1.0998846019784987,
      -1.1019822973707354, -1.1039690073955553, -1.105844516175732,
      -1.10760863222695, -1.1092611884275478, -1.1108020419803311,
      -1.1122310743664852, -1.1135481912916088, -1.1147533226239,
      -1.1158464223245435, -1.1168274683703145, -1.1176964626684593,
      -1.1184534309638827, -1.1190984227386953, -1.1196315111041644,
      -1.1200527926851231, -1.1203623874968902, -1.120560438814759,
      -1.1206471130361091, -1.120622599535209, -1.1204871105107759,
      -1.1202408808263482, -1.1198841678435549, -1.119417251248344,
      -1.1188404328702493, -1.1181540364947704, -1.1173584076689518,
      -1.1164539135002292, -1.1154409424486467, -1.114319904112516,
      -1.1130912290076154, -1.1117553683400152, -1.1103127937726296,
      -1.108763997185584, -1.1071094904305, -1.1053498050788035,
      -1.103485492164141, -1.1015171219190356, -1.099445283505863,
      -1.0972705847422739, -1.094993651821168, -1.0926151290253259,
      -1.0901356784368283, -1.0875559796413632, -1.084876729427549,
      -1.0820986414813896, -1.0792224460759863, -1.0762488897566258,
      -1.0731787350213724, -1.0700127599972888, -1.0667517581124182,
      -1.0633965377636463, -1.059947921980593, -1.0564067480856436,
      -1.0527738673502742, -1.049050144647788, -1.0452364581026163,
      -1.041333698736306, -1.0373427701103455, -1.0332645879659561,
      -1.0291000798610002, -1.0248501848041438, -1.0205158528864156,
      -1.0160980449103036, -1.0115977320165419, -1.0070158953087238,
      -1.002353525475896, -0.99761162241326462, -0.99279119484118561,
      -0.987893259922559, -0.98291884287879883, -0.97786897660451166,
      -0.97274470128103874, -0.967547063989014, -0.96227711832008045,
      -0.95693592398792371, -0.95152454643876128, -0.94604405646144751,
      -0.94049552979734374, -0.9348800467500975, -0.929198691795485,
      -0.92345255319146635, -0.91764272258860546, -0.911770294641004,
      -0.90583636661788713, -0.89984203801601514, -0.89378841017303989,
      -0.88767658588198317, -0.88150766900695221, -0.8752827641002795,
      -0.86900297602118914, -0.8626694095561771, -0.85628316904121871,
      -0.84984535798596439, -0.84335707870006449, -0.836819431921761,
      -0.83023351644889465, -0.82360042877246376, -0.81692126271286924,
      -0.81019710905900122, -0.80342905521028674, -0.7966181848218411,
      -0.78976557745285991, -0.782872308218386, -0.77593944744458154,
      -0.76896806032762877, -0.76195920659640581, -0.75491394017904878,
      -0.74783330887353749, -0.74071835402242425, -0.733570110191826,
      -0.72638960485481341, -0.71917785807930124, -0.71193588222056758,
      -0.70466468161851425, -0.69736525229978663, -0.69003858168486032,
      -0.68268564830020451, -0.6753074214956355, -0.667904861166962,
      -0.66047891748403231, -0.6530305306242743, -0.64556063051183776,
      -0.63807013656243683, -0.63055995743397864, -0.62303099078308666,
      -0.61548412302759026, -0.60792022911508359, -0.60034017229763836,
      -0.592744803912748, -0.58513496317058622, -0.57751147694766125,
      -0.56987515958694457, -0.56222681270453634, -0.55456722500295474,
      -0.54689717209110111, -0.53921741631097919, -0.53152870657123052,
      -0.52383177818753512, -0.51612735272994759, -0.50841613787722284,
      -0.50069882727817738, -0.49297610042013534, -0.48524862250451495,
      -0.47751704432959508, -0.46978200218049315, -0.462044117726416,
      -0.45430399792518578, -0.44656223493511249, -0.43881940603420583,
      -0.43107607354678246, -0.42333278477746938, -0.4155900719526473,
      -0.40784845216932331, -0.40010842735148572, -0.3923704842139093,
      -0.38463509423346037, -0.37690271362787686, -0.36917378334205569,
      -0.36144872904181, -0.35372796111513843, -0.34601187468095762,
      -0.338300849605328, -0.33059525052512539, -0.32289542687917228,
      -0.31520171294679517, -0.307514427893797, -0.29983387582580667,
      -0.29216034584900041, -0.28449411213814479, -0.276835434011947,
      -0.26918455601565972, -0.26154170801091864, -0.25390710527275651,
      -0.24628094859376948, -0.23866342439536267, -0.23105470484605109,
      -0.22345494798674506, -0.2158642978629749, -0.20828288466399389,
      -0.2007108248686956, -0.19314822139828791, -0.18559516377565069,
      -0.178051728291316, -0.17051797817598918, -0.16299396377954517,
      -0.15547972275641725, -0.14797528025730661, -0.14048064912711081,
      -0.13299583010901717, -0.12552081205464222, -0.11805557214015305,
      -0.11060007608825351, -0.10315427839596733, -0.0957181225680957,
      -0.0882915413562736, -0.080874457003497519, -0.073466781494042149,
      -0.06606841680864789, -0.058679255184877932, -0.05129917938252232,
      -0.043928062953952296, -0.036565770519291219, -0.029212158046307446,
      -0.021867073134886617, -0.014530355305977211, -0.0072018362948840786,
      0.00011865965121832245, 0.0074313154716783847, 0.014736320986794615,
      0.022033872588401893, 0.029324172926762981, 0.036607430593878193,
      0.043883859803370812, 0.051153680067068136, 0.058417115868420633,
      0.06567439633290667, 0.072925754895555361, 0.080171428965726543,
      0.087411659589309326, 0.094646691108461162, 0.1018767708190477,
      0.10910214862593405, 0.11632307669626352, 0.12353980911087248,
      0.13075260151401885, 0.137961710761527, 0.14516739456755728,
      0.1523699111501037, 0.15956951887539961, 0.16676647590139221,
      0.17396103982041053, 0.18115346730121423, 0.18834401373056187,
      0.1955329328544568, 0.20272047641923469, 0.20990689381264094,
      0.21709243170505835, 0.22427733369105013, 0.23146183993136565,
      0.23864618679556343, 0.24583060650543279, 0.25301532677934324,
      0.26020057047769607, 0.26738655524963406, 0.27457349318115626,
      0.28176159044481475, 0.28895104695113372, 0.29614205600190679,
      0.30333480394554418, 0.31052946983460772, 0.31772622508569909,
      0.32492523314185423, 0.33212664913759304, 0.33933061956678073,
      0.34653728195345357, 0.35374676452576037, 0.36095918589316472,
      0.36817465472706745, 0.37539326944498475, 0.38261511789843911,
      0.38984027706471019, 0.39706881274257771, 0.4043007792522163,
      0.41153621913936766, 0.41877516288395539, 0.42601762861324788,
      0.43326362181974037, 0.44051313508387113, 0.44776614780171542,
      0.45502262591778775, 0.46228252166308514, 0.46954577329850505,
      0.47681230486374931, 0.48408202593187005, 0.49135483136954877,
      0.498630601103252, 0.50590919989137972, 0.51319047710252164,
      0.52047426649993123, 0.52776038603235464, 0.53504863763129029,
      0.542338807014825, 0.549630663498129, 0.5569239598107234,
      0.56421843192062415, 0.57151379886545828, 0.57880976259065386,
      0.58610600779479738, 0.59340220178224024, 0.60069799432307891,
      0.6079930175205408, 0.61528688568591738, 0.62257919522108418,
      0.62986952450871359, 0.63715743381023293, 0.64444246517163661,
      0.65172414233718012, 0.65900197067105337, 0.66627543708709847,
      0.67354400998661412, 0.68080713920431957, 0.68806425596254184,
      0.69531477283365839, 0.70255808371086248, 0.7097935637872943,
      0.71702056954357518, 0.724238438743797, 0.73144649043999632,
      0.73864402498514714, 0.74583032405471017, 0.75300465067676436,
      0.76016624927074261, 0.7673143456947974, 0.77444814730180744,
      0.78156684300406154, 0.78866960334659952, 0.79575558058925089,
      0.80282390879735088, 0.80987370394115943, 0.81690406400395732,
      0.82391406909884568, 0.83090278159420261, 0.83786924624782988,
      0.844812490349736, 0.85173152387356588, 0.85862533963663523,
      0.8654929134685676, 0.87233320438849016, 0.87914515479075384,
      0.88592769063916954, 0.89267972166968923, 0.899400141601514,
      0.90608782835658619, 0.91274164428739746, 0.919360436413081,
      0.925943036663736, 0.93248826213291147, 0.93899491533820056,
      0.945461784489877, 0.95188764376752222, 0.95827125360453869,
      0.96461136098052025, 0.97090669972136645, 0.97715599080708337,
      0.98335794268718091, 0.98951125160358266, 0.99561460192095419,
      1.001666666464377, 1.0076661068642434, 1.0136115739083023,
      1.0195017079007416, 1.0253351390282088, 1.0311104877326618,
      1.036826365090936, 1.0424813732009302, 1.0480741055742806,
      1.0536031475354122, 1.0590670766268551, 1.064464463020687,
      1.0697938699359864, 1.0750538540621748, 1.0802429659881,
      1.0853597506367458, 1.0904027477054117, 1.0953704921112584,
      1.1002615144420311, 1.105074341411866, 1.1098074963220046,
      1.1144594995262729, 1.1190288689011871, 1.1235141203205314,
      1.1279137681342366, 1.1322263256514324, 1.1364503056274955,
      1.140584220754935, 1.1446265841579693, 1.1485759098906065,
      1.1524307134380889, 1.1561895122215113, 1.1598508261054721,
      1.1634131779085481, 1.1668750939164656, 1.1702351043977606,
      1.1734917441217689, 1.1766435528787662, 1.1796890760020884,
      1.1826268648920331, 1.18545547754139, 1.188173479062397,
      1.1907794422149529, 1.1932719479358953, 1.1956495858691669,
      1.1979109548966782, 1.2000546636696903, 1.2020793311405176,
      1.20398358709438, 1.2057660726811996, 1.2074254409471681,
      1.208960357365886, 1.2103695003688901, 1.2116515618753771,
      1.2128052478209304, 1.2138292786850684, 1.214722390017414,
      1.2154833329623049, 1.2161108747816392, 1.2166037993757812,
      1.2169609078023331, 1.2171810187925765, 1.2172629692653942,
      1.2172056148384889, 1.217007830336706, 1.2166685102972712,
      1.216186569471752, 1.2155609433245602, 1.2147905885278045,
      1.2138744834523085, 1.2128116286546049, 1.2116010473597287,
      1.2102417859396108, 1.2087329143869097, 1.2070735267840795,
      1.2052627417675021, 1.2032997029865031, 1.20118357955708,
      1.1989135665101411, 1.1964888852341153, 1.1939087839117251,
      1.1911725379507712, 1.1882794504087437, 1.1852288524110992,
      1.1820201035630327, 1.178652592354579, 1.1751257365588683,
      1.1714389836233936, 1.1675918110541064, 1.1635837267922087,
      1.1594142695834464, 1.1550830093397939, 1.1505895474933368,
      1.1459335173422331, 1.141114584388585, 1.1361324466680849,
      1.1309868350712877, 1.1256775136563766, 1.120204279953267,
      1.1145669652589363, 1.1087654349238203, 1.10279958862917,
      1.0966693606552189, 1.090374720140056, 1.083915671329063,
      1.0772922538148091, 1.0705045427672879, 1.0635526491543617,
      1.0564367199523381, 1.0491569383465371, 1.0417135239217583,
      1.0341067328425559, 1.0263368580232042, 1.018404229287271,
      1.0103092135167082, 1.0020522147903537, 0.99363367451179,
      0.98505407152643765, 0.97631392222784963, 0.96741378065308858,
      0.95835423856714641, 0.94913592553632131, 0.93975950899049887,
      0.93022569427425772, 0.92053522468677029, 0.91068888151041061,
      0.90068748402805088, 0.89053188952897622, 0.88022299330339138,
      0.86976172862546208, 0.85914906672488156, 0.8483860167468944,
      0.83747362570078243, 0.8264129783967783, 0.81520519737137043,
      0.80385144280100074, 0.79235291240414, 0.78071084133172375,
      0.76892650204595014, 0.75700120418742967, 0.74493629443069909,
      0.73273315632811109, 0.72039321014207969, 0.7079179126657309,
      0.695308757031956, 0.68256727251089755, 0.66969502429588834,
      0.65669361327787779, 0.64356467580836407, 0.63030988345090766,
      0.61693094272120863, 0.60342959481584657, 0.58980761532970449,
      0.57606681396213733, 0.56220903421193258, 0.54823615306113316,
      0.53415008064778946, 0.51995275992768686, 0.50564616632516257,
      0.49123230737302664, 0.47671322234172142, 0.46209098185777775,
      0.44736768751165984, 0.43254547145507216, 0.41762649598785806,
      0.40261295313454293, 0.3875070642106806, 0.37231107937902486,
      0.35702727719572963, 0.34165796414661354, 0.32620547417365359,
      0.31067216819178378, 0.2950604335961684, 0.27937268376002716,
      0.2636113575231972, 0.24777891867148477, 0.23187785540703476,
      0.21591067980978332, 0.19987992729017745, 0.18378815603328405,
      0.16763794643444679, 0.15143190052664604, 0.1351726413997012,
      0.11886281261149947, 0.10250507759136554, 0.086102119035788627,
      0.0696566382966384, 0.053171354762053147, 0.036649005230157933,
      0.020092343275798813, 0.0035041386104678329, -0.013112823564387144,
      -0.029755743210543972, -0.046421806112405539, -0.063108184542504886,
      -0.079812037932890434, -0.096530513552212843, -0.11326074718830492,
      -0.12999986383609144, -0.1467449783905721, -0.16349319634476248,
      -0.18024161449230569, -0.19698732163460231, -0.21372739929223333,
      -0.23045892242048754, -0.24717896012875279, -0.26388457640359025,
      -0.28057283083526413, -0.29724077934750825, -0.31388547493033714,
      -0.33050396837565788, -0.34709330901547092, -0.36365054546245579,
      -0.3801727263527106, -0.39665690109041363, -0.41310012059420348,
      -0.42949943804503066, -0.44585190963529386, -0.46215459531898989,
      -0.4784045595626798, -0.49459887209703979, -0.51073460866876264,
      -0.5268088517925833, -0.54281869150322026, -0.55876122610694767,
      -0.57463356293266332, -0.59043281908211287, -0.60615612217913006,
      -0.62180061111761031, -0.637363436808021, -0.65284176292219431,
      -0.66823276663617681, -0.68353363937093681, -0.69874158753064508,
      -0.71385383323835794, -0.7288676150688389, -0.74378018877829721,
      -0.75858882803082417, -0.77329082512130376, -0.78788349169455019,
      -0.80236415946047845, -0.81673018090505178, -0.83097892999682621,
      -0.845107802888813, -0.85911421861549442, -0.87299561978472862,
      -0.8867494732643687, -0.90037327086332763, -0.913864530006932,
      -0.9272207944062848, -0.9404396347215036, -0.95351864921854168,
      -0.966455464419443, -0.97924773574579627, -0.99189314815518614,
      -1.0043894167704503, -1.0167342875015171, -1.0289255376596527,
      -1.0409609765638945, -1.0528384461394931, -1.0645558215081681,
      -1.0761110115699757, -1.0875019595766049, -1.0987266436959291,
      -1.109783077567611, -1.1206693108495975, -1.1313834297552985,
      -1.1419235575813231, -1.1522878552255427, -1.1624745216953534,
      -1.1724817946059571, -1.1823079506684919, -1.1919513061678533,
      -1.2014102174300625, -1.2106830812789975, -1.219768335482373,
      -1.2286644591867844, -1.237369973341693, -1.2458834411121973,
      -1.2542034682804746, -1.2623287036357236, -1.2702578393525013,
      -1.2779896113573292, -1.2855227996834058, -1.2928562288133671,
      -1.2999887680099202, -1.3069193316342624, -1.313646879452175,
      -1.3201704169276842, -1.3264889955041825, -1.3326017128729133,
      -1.3385077132287226, -1.344206187513002, -1.3496963736437031,
      -1.3549775567323805, -1.3600490692881493, -1.3649102914085081,
      -1.369560650956932, -1.373999623727201, -1.378226733594361,
      -1.3822415526523022, -1.3860437013378608, -1.3896328485414196,
      -1.3930087117039496, -1.3961710569004619, -1.3991196989098147,
      -1.4018545012708563, -1.4043753763248739, -1.4066822852443186,
      -1.4087752380477814, -1.4106542936012221, -1.4123195596054183,
      -1.4137711925696366, -1.4150093977715308, -1.4160344292032496,
      -1.4168465895037723, -1.4174462298774817, -1.4178337499989866,
      -1.4180095979042042, -1.4179742698677396, -1.4177283102665839,
      -1.4172723114301531, -1.4166069134767107, -1.4157328041362305,
      -1.4146507185597061, -1.4133614391149927, -1.4118657951692148,
      -1.4101646628577982, -1.4082589648401935, -1.4061496700423566,
      -1.4038377933860471, -1.4013243955050267, -1.3986105824482435,
      -1.3956975053700615, -1.3925863602076387, -1.3892783873455521,
      -1.3857748712677374, -1.3820771401968719, -1.3781865657212786,
      -1.3741045624094803, -1.3698325874124906, -1.3653721400539829,
      -1.3607247614084288, -1.3558920338673524, -1.3508755806938091,
      -1.3456770655652333, -1.3402981921047683, -1.3347407034012411,
      -1.3290063815179061, -1.3230970469901069, -1.3170145583120043,
      -1.3107608114125195, -1.3043377391206581, -1.2977473106203588,
      -1.290991530895041, -1.2840724401620109, -1.2769921132968889,
      -1.2697526592482546, -1.2623562204426413, -1.2548049721801082,
      -1.2471011220205268, -1.2392469091608089, -1.2312446038032108,
      -1.2230965065149593, -1.2148049475793528, -1.2063722863385506,
      -1.1978009105282457, -1.1890932356044166, -1.1802517040623666,
      -1.1712787847482682, -1.1621769721633892, -1.1529487857612453,
      -1.1435967692378783, -1.1341234898154637, -1.1245315375194966,
      -1.1148235244497307, -1.1050020840451387, -1.0950698703430861,
      -1.0850295572329638, -1.0748838377044792, -1.0646354230908712,
      -1.0542870423072537, -1.0438414410843364, -1.0333013811977321,
      -1.0226696396931192, -1.0119490081074696, -1.0011422916865991,
      -0.99025230859925717, -0.97928188914802528, -0.968233874977235,
      -0.957111118278176, -0.94591648099182069, -0.9346528340093001,
      -0.92332305637041256, -0.91193003446037346, -0.90047666120506487,
      -0.88896583526504469, -0.87740046022854, -0.865783443803688,
      -0.85411769701027418, -0.84240613337119274, -0.83065166810390823,
      -0.81885721731215766, -0.8070256971781109, -0.79516002315528855,
      -0.78326310916244368, -0.77133786677867455, -0.7593872044400175,
      -0.74741402663774126, -0.73542123311862362, -0.72341171808744142,
      -0.71138836941190176, -0.69935406783029019, -0.687311686162051,
      -0.6752640885215595, -0.663214129535316, -0.65116465356281994,
      -0.6391184939213298, -0.62707847211478507, -0.6150473970670991,
      -0.60302806436007028, -0.59102325547614265, -0.57903573704624567,
      -0.56706826010294131, -0.55512355933912838, -0.543204352372484,
      -0.53131333901592648, -0.51945320055426991, -0.50762659902733,
      -0.49583617651967515, -0.48408455445725951, -0.472374332911125,
      -0.46070808990842438, -0.44908838075092627, -0.43751773734126481,
      -0.42599866751708482, -0.41453365439333228, -0.40312515571284785,
      -0.39177560320549659, -0.38048740195601033, -0.36926292978072517,
      -0.35810453661343028, -0.3470145439004898, -0.33599524400542241,
      -0.32504889962313638, -0.31417774320398162, -0.3033839763877883,
      -0.29266976944807971, -0.2820372607466029, -0.27148855619836859,
      -0.26102572874732882, -0.2506508178528814, -0.24036582898732084,
      -0.2301727331444213, -0.22007346635926328, -0.21006992923947193,
      -0.20016398650798672, -0.19035746655751987, -0.18065216101679943,
      -0.17104982432877092, -0.1615521733408315, -0.15216088690726065,
      -0.14287760550392498, -0.13370393085540017, -0.12464142557459225,
      -0.11569161281497599, -0.10685597593555519, -0.098135958178611538,
      -0.089532962360368243, -0.081048350574635733, -0.072683443909522555,
      -0.0644395221772953, -0.056317823657454691, -0.048319544853104385,
      -0.040445840260682958, -0.032697822153096218, -0.025076560376333282,
      -0.017583082159607688, -0.010218371939067245, -0.0029833711951264275,
      0.0041210216965528734, 0.011093951600386662, 0.017934606742468967,
      0.0246422188184348, 0.031216063087553869, 0.037655458453034987,
      0.04395976752854043, 0.050128396690890031, 0.056160796118970666,
      0.062056459818821713, 0.067814925634940487, 0.073435775247779334,
      0.07891863415748078, 0.084263171653853858, 0.089469100772613566,
      0.094536178237920654, 0.09946420439124859, 0.10425302310661788,
      0.10890252169223258, 0.11341263077857491, 0.11778332419300386,
      0.12201461882090253, 0.12610657445345574, 0.1300592936220962,
      0.13387292141970514, 0.13754764530863123, 0.14108369491560666,
      0.14448134181363384, 0.14774089929094683, 0.15086272210710969,
      0.15384720623636577, 0.15669478859832509, 0.15940594677609515,
      0.1619811987219599, 0.16442110245071367, 0.16672625572076807,
      0.16889729570314074, 0.1709348986384657, 0.17283977948212534,
      0.17461269153765172, 0.17625442607851852, 0.17776581195848035,
      0.17914771521056694, 0.18040103863490553, 0.18152672137550138,
      0.18252573848614062, 0.18339910048556024, 0.184147852902041,
      0.18477307580759694, 0.18527588334191461, 0.18565742322622003,
      0.18591887626723544, 0.18606145585139916, 0.18608640742954452,
      0.18599500799219126, 0.18578856553565593, 0.18546841851915477,
      0.18503593531309437, 0.18449251363873923, 0.18383957999945269,
      0.18307858910371139, 0.18221102328009031, 0.18123839188441376,
      0.18016223069930079, 0.1789841013262834, 0.17770559057073351,
      0.17632830981978972, 0.17485389441351598, 0.1732840030094901,
      0.17162031694107077, 0.16986453956952491, 0.16801839563026402,
      0.1660836305734158, 0.16406200989893743, 0.16195531848651712,
      0.15976535992048546, 0.15749395580996217, 0.15514294510448595,
      0.15271418340534648, 0.15020954227286107, 0.1476309085298278,
      0.14498018356139744, 0.14225928261160342, 0.13947013407678055,
      0.13661467879612171, 0.13369486933960958, 0.1307126692935682,
      0.12767005254407165, 0.12456900255845769, 0.1214115116651955,
      0.11819958033232754, 0.11493521644476606, 0.11162043458065768,
      0.10825725528707815, 0.10484770435529289, 0.10139381209583571,
      0.0978976126136433, 0.0943611430834964, 0.090786443026009175,
      0.0871755535844054, 0.08353051680233689, 0.079853374902975907,
      0.076146169569632216, 0.072410941228130216, 0.068649728331189763,
      0.064864566645052982, 0.061057488538596487, 0.057230522275159346,
      0.053385691307339438, 0.049525013574973541, 0.045650500806559483,
      0.041764157824338774, 0.037867981853266487, 0.033963961834125714,
      0.030054077740981837, 0.026140299903231291, 0.022224588332455362,
      0.018308892054315885, 0.014395148445692237, 0.010485282577317222,
      0.0065812065620888746, 0.0026848189093051063, -0.0012019961149738845,
      -0.0050773691212311189, -0.0089394462232469454, -0.01278638965809327,
      -0.016616378399172654, -0.02042760876208826, -0.024218295003155491,
      -0.027986669910345666, -0.031730985386481517, -0.035449513024476562,
      -0.039140544674444493, -0.04280239300247772, -0.046433392040925843,
      -0.050031897729982594, -0.053596288450408307, -0.057124965547212948,
      -0.060616353844134045, -0.0640689021487311, -0.067481083747938889,
      -0.070851396893916577, -0.074178365280041264, -0.077460538506878243,
      -0.0806964925379888, -0.0838848301454252, -0.0870241813447602,
      -0.090113203819534637, -0.093150583334955891, -0.096135034140738013,
      -0.099065299362942436, -0.10194015138470409, -0.10475839221571065,
      -0.10751885385032642, -0.11022039861424082, -0.11286191949954097,
      -0.1154423404880953, -0.11796061686314825, -0.12041573550903228,
      -0.12280671519890238, -0.12513260687040029, -0.12739249388917517,
      -0.12958549230016608, -0.13171075106657962, -0.13376745229648324,
      -0.13575481145696028, -0.13767207757574709, -0.13951853343030185,
      -0.14129349572424921, -0.14299631525115025, -0.14462637704555331,
      -0.14618310052127734, -0.14766593959690405, -0.14907438280843055,
      -0.1504079534090651, -0.1516662094561399, -0.15284874388511135,
      -0.15395518457065732, -0.15498519437483149, -0.15593847118229154,
      -0.15681474792257749, -0.15761379257947661, -0.15833540818744546,
      -0.15897943281512095, -0.15954573953593651, -0.16003423638585684,
      -0.16044486630826393, -0.16077760708601257, -0.16103247126070697,
      -0.16120950603921758, -0.1613087931874963, -0.16133044891172521,
      -0.16127462372685741, -0.16114150231261107, -0.16093130335695974,
      -0.1606442793871998, -0.16028071658865495, -0.15984093461109658,
      -0.15932528636295179, -0.15873415779338026, -0.15806796766231232,
      -0.15732716729853224, -0.15651224034589858, -0.1556237024978131,
      -0.15466210122000812, -0.15362801546180926, -0.15252205535592811,
      -0.15134486190694191, -0.15009710666854711, -0.14877949140973915,
      -0.14739274777000769, -0.14593763690371153, -0.14441494911373734,
      -0.14282550347460138, -0.1411701474451183, -0.13944975647079225,
      -0.13766523357606422, -0.13581750894658423, -0.13390753950164713,
      -0.1319363084569532, -0.12990482487786537, -0.12781412322330651,
      -0.12566526288048846, -0.12345932769062096, -0.12119742546579124,
      -0.11888068749717026, -0.11651026805477144, -0.11408734387886418,
      -0.11161311366332172, -0.10908879753100423, -0.10651563650144215,
      -0.10389489195096629, -0.10122784506548488, -0.098515796286126847,
      -0.095760064747952289, -0.092961987711892749, -0.090122919990186373,
      -0.08724423336546891, -0.084327316003757369, -0.081373571861529159,
      -0.0783844200871016, -0.0753612944165568, -0.072305642564399059,
      -0.069218925609170742, -0.066102617374277972, -0.062958203804201668,
      -0.059787182336362044, -0.056591061268833592, -0.053371359124154222,
      -0.0501296040094496, -0.046867332973123246, -0.043586091358288212,
      -0.040287432153268382, -0.036972915339295448, -0.033644107235712928,
      -0.030302579842909724, -0.026949910183178688, -0.02358767963978195,
      -0.020217473294454724, -0.016840879263557582, -0.013459488033157954,
      -0.010074891793223795, -0.0066886837712370473, -0.0033024575654188593,
      8.2193522197460123E-5, 0.0034636771525654309, 0.006840402616082597,
      0.010210781498485866, 0.013573228345897151, 0.016926161328826558,
      0.020268002904861193, 0.0235971804798132, 0.026912127067110617,
      0.03021128194514635, 0.033493091312385134, 0.036756008939999835,
      0.039998496821754929, 0.043219025820958011, 0.046416076314212594,
      0.04958813883173991, 0.052733714694070739, 0.055851316644833567,
      0.058939469479442105, 0.0619967106694461, 0.065021590982311167,
      0.068012675096425654, 0.070968542211092625, 0.073887786651278015,
      0.076769018466940869, 0.079610864026669961, 0.0824119666054619,
      0.085170986966393733, 0.087886603935989654, 0.090557514973095846,
      0.093182436731015769, 0.09576010561272344, 0.098289278318972023,
      0.10076873238905673, 0.10319726673406723, 0.10557370216242683,
      0.10789688189751598, 0.11016567208721337, 0.11237896230514427,
      0.11453566604346019, 0.11663472119699936, 0.11867509053858383,
      0.1206557621853554, 0.12257575005592351, 0.12443409431817581,
      0.12622986182759838, 0.12796214655592009, 0.12963007000994009,
      0.13123278164037769, 0.13276945924058642, 0.13423930933500525,
      0.1356415675571731, 0.13697549901717851, 0.13824039865842458,
      0.13943559160354585, 0.14056043348935623, 0.14161431079072234,
      0.1425966411332007, 0.14350687359436642, 0.14434448899367175,
      0.14510900017075473, 0.14579995225208672, 0.14641692290584882,
      0.14695952258492678, 0.14742739475796757, 0.14782021612835969,
      0.14813769684108838, 0.14837958067736071, 0.1485456452369277,
      0.14863570210803945, 0.14864959702495173, 0.14858721001291186,
      0.14844845552059274, 0.14823328253987644, 0.14794167471297615,
      0.14757365042681264, 0.14712926289462258, 0.14660860022475874,
      0.14601178547663549, 0.14533897670379364, 0.14459036698406971,
      0.14376618443682518, 0.14286669222724638, 0.14189218855767066,
      0.14084300664595678, 0.13971951469088723, 0.1385221158245907,
      0.13725124805201022, 0.13590738417741446, 0.1344910317179589,
      0.13300273280433367, 0.13144306406851325, 0.12981263651861866,
      0.12811209540095275, 0.12634212004922377, 0.12450342372100635,
      0.12259675342148062, 0.12062288971449671, 0.11858264652103526,
      0.11647687090509444, 0.11430644284708506, 0.11207227500480137,
      0.10977531246202316, 0.10741653246484839, 0.10499694414579856,
      0.10251758823582602, 0.09997953676428066, 0.09738389274693085,
      0.0947317898621456, 0.092024392115333614, 0.089262893491735815,
      0.086448517597694341, 0.083582517290501562, 0.080666174296941215,
      0.077700798820654379, 0.074687729138444, 0.07162833118564764,
      0.068523998130719715, 0.065376149939148351, 0.062186232926837282,
      0.058955719303136617, 0.055686106703610391, 0.052378917712734063,
      0.049035699376671529, 0.045658022706268453, 0.042247482170433226,
      0.03880569518007837, 0.035334301562786052, 0.031834963028349733,
      0.028309362625390105, 0.024759204189213513, 0.021186211781090425,
      0.017592129119142125, 0.013978719001000922, 0.010347762718478704,
      0.0067010594643897858, 0.0030404257317353245, -0.00063230529454080808,
      -0.0043152843530217533, -0.0080066467283449461, -0.011704512880549939,
      -0.015406989081027861, -0.019112168054913142, -0.02281812962966151,
      -0.0265229413896039, -0.030224659336282794, -0.0339213285543325,
      -0.03761098388268927, -0.041291650590909668, -0.044961345060368141,
      -0.048618075470112, -0.052259842487148628, -0.055884639960921356,
      -0.05949045562175298, -0.0630752717830446, -0.066637066046939655,
      -0.070173812013283252, -0.073683479991592277, -0.077164037715820324,
      -0.080613451061675515, -0.084029684766245116, -0.0874107031496964,
      -0.090754470838798409, -0.094058953492030792, -0.09732211852604282,
      -0.10054193584319654, -0.10371637855997828, -0.10684342373601155,
      -0.10992105310343113, -0.11294725379638483, -0.11592001908039107,
      -0.11883734908134008, -0.12169725151387466, -0.12449774240888686,
      -0.12723684683991549, -0.12991259964819959, -0.13252304616610566,
      -0.13506624293872033, -0.13754025844335366, -0.1399431738066963,
      -0.14227308351941442, -0.14452809614789766, -0.14670633504296493,
      -0.14880593904526787, -0.15082506318712158, -0.15276187939058194,
      -0.15461457716148752, -0.15638136427924054, -0.15806046748209521,
      -0.15965013314772458, -0.1611486279688169, -0.16255423962347634,
      -0.16386527744021584, -0.16508007305728797, -0.1661969810761294,
      -0.16721437970872774, -0.16813067141864507, -0.16894428355549812,
      -0.169653668982677, -0.17025730669808822, -0.17075370244768412,
      -0.17114138933160808, -0.17141892840270523, -0.17158490925719827,
      -0.17163795061737094, -0.17157670090596872, -0.17139983881219742,
      -0.17110607384908755, -0.17069414690201248, -0.17016283076821495,
      -0.16951093068710885, -0.16873728486118933, -0.16784076496736827,
      -0.16682027665856192, -0.16567476005532294, -0.16440319022738314,
      -0.16300457766491044, -0.16147796873931397, -0.15982244615344371,
      -0.15803712938102096, -0.15612117509512985, -0.15407377758564136,
      -0.15189416916537613, -0.14958162056492508, -0.14713544131590869,
      -0.14455498012259824, -0.14183962522172575, -0.13898880473036618,
      -0.13600198698176788, -0.13287868084897758, -0.1296184360561855,
      -0.12622084347764462, -0.122685535424033, -0.11901218591621063,
      -0.11520051094621098, -0.11125026872537372, -0.10716125991956373,
      -0.10293332787133509, -0.098566358808966414, -0.094060282042321808,
      -0.089415070145378139, -0.084630739125436977, -0.07970734857888,
      -0.074645001833422042, -0.069443846076814614, -0.064104072471939874,
      -0.058625916258202612, -0.053009656839225455, -0.047255617856772431,
      -0.041364167250868583, -0.035335717306063191, -0.029170724683833693,
      -0.022869690441099738, -0.01643316003478576, -0.0098617233124623227,
      -0.003156014489031328, 0.0036832878905418143, 0.010655461002490763,
      0.017759737809451753, 0.024995307139637823, 0.032361313779959322,
      0.039856858583101507, 0.047480998588520229, 0.055232747157297812,
      0.063111074120928173, 0.071114905943911427, 0.0792431259001396,
      0.087494574263077968, 0.095868048509643811, 0.10436230353776077,
      0.11297605189751611, 0.12170796403588993, 0.130556668554992,
      0.13952075248367363, 0.14859876156255597, 0.15778920054230761,
      0.16709053349512784, 0.17650118413933544, 0.18601953617700925,
      0.19564393364455068, 0.20537268127609162, 0.21520404487960509,
      0.22513625172571841, 0.23516749094899464, 0.24529591396162725,
      0.25551963487944696, 0.26583673096011895, 0.27624524305332904,
      0.28674317606294664, 0.29732849942092665, 0.30799914757290864,
      0.31875302047528542, 0.3295879841036371, 0.34050187097242107,
      0.35149248066568595, 0.36255758037869457, 0.37369490547034,
      0.38490216002612065, 0.39617701743152528, 0.40751712095571524,
      0.4189200843452644, 0.43038349242781437, 0.44190490172543917,
      0.45348184107759371, 0.4651118122734148, 0.47679229069318541,
      0.4885207259587615, 0.50029454259287942, 0.51211114068695307,
      0.52396789657732756, 0.53586216352970772, 0.54779127243159265,
      0.55975253249247947, 0.57174323195162458, 0.58376063879319207,
      0.595802001468561, 0.60786454962549974, 0.61994549484412054,
      0.63204203137928672, 0.64415133690929449, 0.65627057329059,
      0.66839688731830116, 0.68052741149237661, 0.692659264789039,
      0.70478955343738048, 0.71691537170086572, 0.72903380266344631,
      0.741141919020096, 0.75323678387155435, 0.76531545152297453,
      0.77737496828628017, 0.78941237328592817, 0.80142469926796644,
      0.81340897341198282, 0.8253622181457746, 0.83728145196252124,
      0.84916369024017, 0.86100594606278269, 0.87280523104360541,
      0.88455855614964052, 0.896262932527433, 0.90791537232982178,
      0.91951288954342436, 0.93105250081662239, 0.94253122628773689,
      0.9539460904131879, 0.96529412279537807, 0.97657235901008488,
      0.98777784143299918, 0.99890762006530176, 1.00995875335794,
      1.0209283090343648, 1.0318133649114984, 1.0426110097186765,
      1.0533183439143334, 1.0639324805001336, 1.0744505458323284,
      1.08486968043018, 1.0951870397810191, 1.105399795141861,
      1.1155051343372797, 1.1255002625532748, 1.1353824031269313,
      1.1451487983315867, 1.1547967101573262, 1.1643234210865474,
      1.1737262348643034, 1.1830024772632992, 1.1921494968432236,
      1.20116466570422, 1.2100453802342666, 1.2187890618502375,
      1.2273931577324477, 1.2358551415523973, 1.2441725141935613,
      1.2523428044649838, 1.2603635698074545, 1.26823239699205,
      1.2759469028108603, 1.2835047347596751, 1.2909035717124058,
      1.2981411245870653, 1.3052151370031222, 1.3121233859299859,
      1.3188636823264586, 1.3254338717709591, 1.3318318350823495,
      1.3380554889311205, 1.3441027864408148, 1.3499717177794941,
      1.355660310741053, 1.3611666313162123, 1.366488784253046,
      1.3716249136068597, 1.3765732032792444, 1.3813318775461576,
      1.3858992015749012, 1.3902734819297917, 1.3944530670664155,
      1.3984363478143045, 1.4022217578479022, 1.4058077741456732,
      1.4091929174372091, 1.4123757526382374, 1.4153548892733745,
      1.4181289818865024, 1.4206967304386615, 1.4230568806933501,
      1.4252082245890891, 1.4271496005991744, 1.4288798940785079,
      1.4303980375973921, 1.4317030112622058, 1.4327938430228817,
      1.4336696089670613, 1.4343294336008858, 1.4347724901163235,
      1.4349980006449499, 1.4350052364981378, 1.4347935183935632,
      1.4343622166679801, 1.4337107514762086, 1.4328385929762695,
      1.4317452615006339, 1.430430327713514, 1.4288934127542048,
      1.4271341883663782, 1.4251523770133485, 1.422947751979261,
      1.4205201374561638, 1.4178694086169881, 1.4149954916743746,
      1.4118983639253662, 1.4085780537819503, 1.4050346407874552,
      1.4012682556187857, 1.3972790800745369, 1.3930673470489641,
      1.3886333404918423, 1.3839773953542405, 1.3790998975202189,
      1.3740012837244824, 1.3686820414560439, 1.3631427088478965,
      1.3573838745527591, 1.351406177604968, 1.3452103072684962,
      1.3387970028712037, 1.3321670536253905, 1.3253212984346654,
      1.3182606256872169, 1.3109859730355911, 1.3034983271630056,
      1.2957987235362789, 1.2878882461455077, 1.2797680272305032,
      1.2714392469941813, 1.2629031333028551, 1.2541609613736706,
      1.2452140534492273, 1.2360637784594608, 1.2267115516709444,
      1.2171588343236976, 1.2074071332556513, 1.1974580005148432,
      1.1873130329594743, 1.176973871846027, 1.1664422024054737,
      1.1557197534077548, 1.1448082967147115, 1.1337096468215249,
      1.1224256603868872, 1.1109582357519827, 1.0993093124485147,
      1.0874808706958361, 1.0754749308874265, 1.0632935530668119,
      1.0509388363931633, 1.0384129185966564, 1.0257179754238046,
      1.0128562200729665, 0.99982990262018578, 0.98664130943544415,
      0.97329276258970354, 0.959786619252752, 0.9461252710821153,
      0.9323111436031819, 0.91834669558080062, 0.90423441838247709,
      0.88997683533339877, 0.87557650106344087, 0.86103600084644771,
      0.84635794993189983, 0.831544992869188, 0.81659980282474609,
      0.80152508089222452, 0.78632355539589038, 0.77099798118746676,
      0.755551138936716, 0.73998583441584342, 0.72430489777800577,
      0.70851118283019121, 0.69260756630061249, 0.6765969471008384,
      0.66048224558294266, 0.644266402791833, 0.62795237971307338,
      0.61154315651625146, 0.59504173179432152, 0.57845112179904479,
      0.56177435967273459, 0.54501449467657359, 0.528174591415748,
      0.51125772906162, 0.49426700057111295, 0.47720551190359478,
      0.46007638123552985, 0.44288273817302803, 0.42562772296258128,
      0.4083144857002417, 0.39094618553944066, 0.37352598989768343,
      0.35605707366231876, 0.33854261839574223, 0.3209858115400776,
      0.30338984562172744, 0.28575791745593188, 0.2680932273516331,
      0.25039897831680341, 0.23267837526449611, 0.21493462421988652,
      0.19717093152853338, 0.17939050306592147, 0.16159654344879859,
      0.14379225524830488, 0.12598083820518868, 0.10816548844736185,
      0.090349397709976242, 0.072535752558291255, 0.054727733613489073,
      0.036928514781676004, 0.019141262486357731, 0.0013691349045058462,
      -0.01638471879354729, -0.034117159200115113, -0.051825057421891273,
      -0.069505295827230584, -0.087154768788758941, -0.10477038342102409,
      -0.12234906031309722, -0.13988773425589318, -0.15738335496394612,
      -0.17483288779149417, -0.19223331444270791, -0.20958163367581345,
      -0.22687486200093682, -0.24411003437144888, -0.26128420486875042,
      -0.27839444738014396, -0.29543785626969177, -0.31241154704191348,
      -0.32931265699811757, -0.34613834588512349, -0.36288579653635616,
      -0.37955221550496915, -0.39613483368900337, -0.41263090694825039,
      -0.42903771671280594, -0.445352570583081, -0.46157280292111469,
      -0.47769577543305569, -0.49371887774267242, -0.50963952795576972,
      -0.52545517321525681, -0.54116329024691223, -0.55676138589551816,
      -0.5722469976514013, -0.58761769416711251, -0.60287107576421084,
      -0.618004774930029, -0.6330164568042087, -0.64790381965501809,
      -0.66266459534524258, -0.67729654978760623, -0.691797483389545,
      -0.70616523148733179, -0.72039766476937417, -0.73449268968858683,
      -0.7484482488638573, -0.762262321470342, -0.775932923618698,
      -0.789458108723021, -0.802835967857491, -0.816064630101664,
      -0.82914226287427384, -0.84206707225552924, -0.854837303297859,
      -0.86745124032501919, -0.8799072072194748, -0.89220356769812947,
      -0.9043387255761749, -0.91631112501921652, -0.92811925078345514,
      -0.93976162844403244, -0.95123682461144266, -0.962543447135946,
      -0.97368014530008207, -0.98464560999912332, -0.99543857390956525,
      -1.0060578116455654, -1.0165021399033609, -1.0267704175936792,
      -1.0368615459620707, -1.0467744686972495, -1.0565081720273795,
      -1.066061684804394, -1.0754340785762535, -1.0846244676472809,
      -1.0936320091265179, -1.1024559029641419, -1.1110953919759892,
      -1.1195497618562009, -1.1278183411780645, -1.1359005013830015,
      -1.1437956567578762, -1.1515032644005456, -1.1590228241737932,
      -1.1663538786476368, -1.1734960130301237, -1.1804488550866274,
      -1.1872120750477311, -1.1937853855057734, -1.2001685413001044,
      -1.2063613393911634, -1.2123636187233955, -1.2181752600771609,
      -1.2237961859096793, -1.2292263601850715, -1.234465788193674,
      -1.2395145163606081, -1.2443726320438049, -1.2490402633215243,
      -1.2535175787694657, -1.2578047872276241, -1.2619021375569719,
      -1.2658099183860418, -1.2695284578476103, -1.2730581233055136,
      -1.2763993210717632, -1.2795524961140816, -1.2825181317539476,
      -1.2852967493553353, -1.2878889080042204, -1.2902952041790179,
      -1.2925162714120966, -1.2945527799424599, -1.2964054363597877,
      -1.2980749832399521, -1.2995621987721455, -1.3008678963777822,
      -1.3019929243213311, -1.3029381653131875, -1.3037045361047905,
      -1.3042929870761002, -1.3047045018156058, -1.3049400966930331,
      -1.3050008204248817, -1.3048877536329837, -1.3046020083962366,
      -1.304144727795661, -1.3035170854529727, -1.302720285062823,
      -1.3017555599188679, -1.3006241724338752, -1.2993274136539752,
      -1.2978666027673016, -1.2962430866071417, -1.2944582391497939,
      -1.292513461007315, -1.2904101789153104, -1.2881498452159723,
      -1.2857339373365306, -1.2831639572632925, -1.2804414310114682,
      -1.2775679080909423, -1.2745449609681934, -1.2713741845245217,
      -1.2680571955108026, -1.2645956319988951, -1.2609911528299613,
      -1.2572454370597956, -1.2533601834014307, -1.2493371096651484,
      -1.2451779521960982, -1.2408844653097071, -1.2364584207250831,
      -1.2319016069965536, -1.2272158289435628, -1.2224029070791067,
      -1.2174646770368565, -1.2124029889972094, -1.2072197071123838,
      -1.2019167089308196, -1.1964958848209779, -1.1909591373947959,
      -1.18530838093095, -1.1795455407980719, -1.1736725528781888,
      -1.1676913629904428, -1.1616039263153939, -1.1554122068199832,
      -1.1491181766833816, -1.1427238157239075, -1.1362311108271368,
      -1.1296420553754514, -1.1229586486791088, -1.1161828954091022,
      -1.1093168050318933, -1.1023623912462246, -1.0953216714221954,
      -1.088196666042722, -1.0809893981475924, -1.0737018927802187,
      -1.0663361764373203, -1.058894276521626, -1.0513782207978122,
      -1.0437900368517736, -1.0361317515534407, -1.0284053905232435,
      -1.0206129776023889, -1.0127565343271265, -1.004838079407097,
      -0.99685962820795271, -0.98882319223836, -0.98073077864155322,
      -0.97258438969153538, -0.96438602229410342, -0.956137667492816,
      -0.94784130998000693, -0.93949892761303222, -0.93111249093580417,
      -0.92268396270580677, -0.91421529742665464, -0.90570844088634861,
      -0.897165329701339, -0.88858789086650336, -0.87997804131116031,
      -0.87133768746118756, -0.86266872480744883, -0.85397303748048925,
      -0.84525249783175094, -0.83650896602128066, -0.82774428961211211,
      -0.8189603031713738, -0.8101588278782007, -0.80134167113860966,
      -0.79251062620730162, -0.78366747181661278, -0.77481397181256206,
      -0.76595187479817883, -0.75708291378411585, -0.74820880584662119,
      -0.73933125179300774, -0.73045193583456947, -0.72157252526712434,
      -0.71269467015913823, -0.70382000304757775, -0.69495013864148258,
      -0.68608667353330954, -0.67723118591814513, -0.66838523532079053,
      -0.65955036233075048, -0.6507280883452, -0.64191991531994352,
      -0.63312732552838935, -0.62435178132861946, -0.61559472493847545,
      -0.6068575782188369, -0.59814174246496032, -0.5894485982059825,
      -0.58077950501262066, -0.5721358013129807, -0.56351880421661271,
      -0.55492980934670022, -0.54637009068048159, -0.53784090039784049,
      -0.5293434687380778, -0.52087900386490094, -0.51244869173953778,
      -0.50405369600207273, -0.49569515786086438, -0.487374195990167,
      -0.47909190643581179, -0.47084936252899512, -0.46264761480813743,
      -0.45448769094878211, -0.44637059570149534, -0.438297310837724,
      -0.43026879510362553, -0.42228598418176821, -0.41434979066070066,
      -0.40646110401233709, -0.39862079057710909, -0.39082969355682085,
      -0.38308863301520424, -0.3753984058860631, -0.36775978598896436,
      -0.36017352405247482, -0.35264034774476782, -0.34516096171167576,
      -0.33773604762199405, -0.33036626422004323, -0.32305224738542387,
      -0.31579461019982019, -0.30859394302088605, -0.30145081356301628,
      -0.2943657669850307, -0.28733932598461942, -0.28037199089949433,
      -0.27346423981515655, -0.26661652867920693, -0.25982929142208944,
      -0.25310294008415551, -0.24643786494905667, -0.23983443468321375,
      -0.23329299648143403, -0.22681387621843035, -0.22039737860625333,
      -0.21404378735748236, -0.2077533653540517, -0.20152635482169723,
      -0.1953629775098033, -0.18926343487661257, -0.18322790827970298,
      -0.17725655917156252, -0.1713495293001881, -0.16550694091460119,
      -0.1597288969751523, -0.15401548136849338, -0.14836675912713126,
      -0.14278277665339661, -0.1372635619477697, -0.13180912484140445,
      -0.12641945723271564, -0.1210945333279778, -0.11583430988572882,
      -0.11063872646492762, -0.10550770567668759, -0.10044115343950138,
      -0.09543895923781337, -0.090500996383828081, -0.085627122282391929,
      -0.08081717869890151, -0.076070992030009471, -0.071388373577085842,
      -0.066769119822274292, -0.062213012706990478, -0.057719819912809028,
      -0.05328929514451837, -0.048921178415290222, -0.044615196333808511,
      -0.040371062393201852, -0.0361884772617209, -0.032067129074962973,
      -0.028006693729547377, -0.024006835178125366, -0.020067205725575809,
      -0.016187446326265034, -0.012367186882257318, -0.0086060465423220822,
      -0.00490363400166427, -0.0012595478021836387, 0.002326623366819984,
      0.0058553003675966, 0.0093269133127551543, 0.01274190126394753,
      0.016100711930654356, 0.019403801369116958, 0.022651633681570756,
      0.025844680715904927, 0.028983421765837666, 0.032068343271760322,
      0.035099938522334187, 0.038078707357000655, 0.041005155869451221,
      0.043879796112248723, 0.0467031458026573, 0.049475728029804877,
      0.052198070963324877, 0.054870707563508883, 0.057494175293177241,
      0.06006901583127755, 0.062595774788386946, 0.065075001424198475,
      0.0675072483670714, 0.0698930713357771, 0.072233028863544657,
      0.074527682024456213, 0.076777594162359256, 0.078983330622312956,
      0.081145458484733216, 0.083264546302288911, 0.085341163839622147,
      0.087375881816039891, 0.089369271651207532, 0.091321905213947063,
      0.093234354574243256, 0.095107191758490389, 0.096940988508122661,
      0.098736316041647954, 0.10049374482019094, 0.10221384431660849,
      0.10389718278826723, 0.10554432705350975, 0.10715584227193142,
      0.10873229172849197, 0.1102742366215366, 0.11178223585481509,
      0.11325684583350215, 0.11469862026432534, 0.11610810995985191,
      0.11748586264693928, 0.11883242277947989, 0.1201483313554014,
      0.12143412573804774, 0.12269033948193603, 0.12391750216293412,
      0.12511613921293538, 0.12628677175902883, 0.12742991646721827,
      0.12854608539072535, 0.12963578582289884, 0.1306995201547731,
      0.13173778573728728, 0.13275107474820375, 0.13373987406373064,
      0.1347046651349057, 0.13564592386870195, 0.13656412051392797,
      0.13745971955190556, 0.13833317959193078, 0.1391849532715736,
      0.14001548716174159, 0.14082522167660663, 0.14161459098832999,
      0.14238402294659736, 0.14313393900300514, 0.14386475414023384,
      0.14457687680603809, 0.14527070885205751, 0.14594664547738281,
      0.14660507517694263, 0.14724637969461754, 0.1478709339811316,
      0.1484791061566641, 0.1490712574781565, 0.14964774231133224,
      0.15020890810736037, 0.15075509538416096, 0.15128663771232292,
      0.1518038617055758, 0.15230708701583912, 0.15279662633275187,
      0.15327278538769581, 0.15373586296222611, 0.15418615090093513,
      0.15462393412863054, 0.15504949067184376, 0.15546309168459529,
      0.15586500147836677, 0.15625547755626179, 0.15663477065125581,
      0.15700312476851622, 0.15736077723175251, 0.1577079587334726,
      0.15804489338919148, 0.158371798795427, 0.15868888609149231,
      0.15899636002501044, 0.15929441902105368, 0.15958325525488928,
      0.1598630547282392, 0.16013399734897241, 0.16039625701421417,
      0.1606500016967185, 0.1608953935345328, 0.1611325889237826,
      0.16136173861457748, 0.16158298780991912, 0.16179647626755486,
      0.1620023384046948, 0.16220070340550724, 0.1623916953313278,
      0.16257543323347978, 0.16275203126864518, 0.16292159881669971,
      0.16308424060090565, 0.16324005681042209, 0.16338914322499448,
      0.16353159134179282, 0.16366748850426482, 0.16379691803293928,
      0.16391995935810874, 0.16403668815424871, 0.16414717647615745,
      0.16425149289666313, 0.1643497026458447, 0.16444186775166655,
      0.1645280471819312, 0.16460829698746832, 0.164682670446462,
      0.16475121820982705, 0.16481398844754644, 0.16487102699585965,
      0.16492237750524974, 0.16496808158908366, 0.16500817897286246,
      0.16504270764395199, 0.16507170400173179, 0.16509520300804664,
      0.16511323833787844, 0.16512584253015491, 0.16513304713858432,
      0.16513488288243677, 0.16513137979719397, 0.16512256738493683,
      0.16510847476442797, 0.16508913082076238, 0.16506456435452205,
      0.16503480423032213, 0.1649998795246817, 0.16495981967311857,
      0.16491465461637544, 0.16486441494571519, 0.16480913204716555,
      0.16474883824465136, 0.16468356694192354, 0.16461335276319461,
      0.16453823169241322, 0.16445824121106709, 0.16437342043447006,
      0.16428381024641564, 0.16418945343215066, 0.16409039480956242,
      0.16398668135852054, 0.16387836234828679, 0.16376548946292735,
      0.16364811692463677, 0.1635263016149209, 0.16340010319355217,
      0.1632695842152275, 0.16313481024387233, 0.16299584996450123,
      0.16285277529258707, 0.16270566148086973, 0.16255458722352503,
      0.16239963475765035, 0.16224088996200042, 0.16207844245289926,
      0.16191238567729471, 0.16174281700287338, 0.16156983780520023,
      0.16139355355181745, 0.16121407388324868, 0.16103151269087629,
      0.16084598819161061, 0.16065762299933847, 0.16046654419307588,
      0.16027288338180323, 0.1600767767659248, 0.15987836519531429,
      0.15967779422392153, 0.1594752141608789, 0.15927078011809859,
      0.159064652054294, 0.15885699481543664, 0.15864797817157139,
      0.15843777684999602, 0.15822657056477227, 0.15801454404251442,
      0.15780188704448928, 0.15758879438493939, 0.15737546594567126,
      0.15716210668684708, 0.15694892665398574, 0.15673614098115979,
      0.15652396989036443, 0.15631263868706008, 0.15610237775187949,
      0.15589342252848129, 0.15568601350756506, 0.15548039620703188,
      0.15527682114828484, 0.15507554382870264, 0.15487682469023584,
      0.15468092908419651, 0.15448812723218214, 0.15429869418319503,
      0.15411290976695416, 0.15393105854337746, 0.15375342974831308,
      0.15358031723547313, 0.15341201941464822, 0.15324883918614615,
      0.15309108387158271, 0.15293906514093067, 0.15279309893595056,
      0.15265350538998354, 0.1525206087441216, 0.15239473725984221,
      0.15227622312808992, 0.15216540237484508, 0.15206261476325669,
      0.15196820369232808, 0.15188251609222264, 0.15180590231622676,
      0.15173871602940769, 0.15168131409403052, 0.15163405645174166,
      0.15159730600261531, 0.15157142848107721, 0.15155679232876237,
      0.15155376856440825, 0.15156273065072862, 0.15158405435845565,
      0.15161811762751382, 0.15166530042541684, 0.15172598460296405,
      0.15180055374726048, 0.15188939303215848, 0.15199288906616282,
      0.15211142973790465, 0.15224540405915771, 0.15239520200561121,
      0.15256121435532011, 0.15274383252500298, 0.15294344840423746,
      0.15316045418758212, 0.15339524220477121, 0.15364820474900043,
      0.15391973390341224, 0.15421022136583773, 0.15452005827189721,
      0.15484963501650917, 0.15519934107392713, 0.15556956481633075,
      0.15596069333114077, 0.15637311223702008, 0.15680720549875621,
      0.15726335524107421, 0.15774194156139745, 0.15824334234179291,
      0.15876793305999609, 0.15931608659978924, 0.15988817306067668,
      0.16048455956704849, 0.16110561007682997, 0.1617516851898021,
      0.16242314195559854, 0.16312033368151657, 0.16384360974024259,
      0.1645933153775116, 0.165369791519899, 0.16617337458274045,
      0.16700439627831531, 0.16786318342440532, 0.1687500577532523,
      0.16966533572108658, 0.17060932831826295, 0.17158234088011332,
      0.17258467289861656, 0.17361661783496357, 0.17467846293310041,
      0.17577048903439502, 0.17689297039342228, 0.17804617449507076,
      0.17923036187295971, 0.18044578592932214, 0.18169269275643907,
      0.18297132095966659, 0.18428190148220328, 0.18562465743164652,
      0.18699980390845117, 0.18840754783635022, 0.18984808779487208,
      0.1913216138539621, 0.19282830741088533, 0.19436834102944114,
      0.19594187828154996, 0.19754907359139015, 0.19919007208204043,
      0.20086500942483451, 0.20257401169140243, 0.20431719520856334,
      0.20609466641607743, 0.20790652172740662, 0.20975284739346209,
      0.21163371936955447, 0.21354920318546813, 0.21549935381884933,
      0.21748421557192388, 0.21950382195161411, 0.22155819555317693,
      0.22364734794734176, 0.22577127957112492, 0.22792997962226802,
      0.23012342595747778, 0.23235158499445344, 0.23461441161778496,
      0.23691184908879767, 0.23924382895936974, 0.2416102709898483,
      0.24401108307098127, 0.24644616115012416, 0.24891538916154898,
      0.251418638961093, 0.25395577026509281, 0.2565266305936626,
      0.25913105521841129, 0.26176886711458486, 0.26443987691770687,
      0.267143882884755, 0.26988067085992623, 0.27265001424496693,
      0.27545167397420012, 0.27828539849419331, 0.28115092374815687,
      0.28404797316507396, 0.28697625765360335, 0.28993547560077043,
      0.29292531287546841, 0.29594544283684587, 0.29899552634747656,
      0.30207521179149271, 0.30518413509753972, 0.30832191976669904,
      0.31148817690530184, 0.31468250526268521, 0.31790449127388609,
      0.32115370910727975, 0.32442972071720666, 0.32773207590147757,
      0.33106031236392669, 0.33441395578183974, 0.33779251987839387,
      0.34119550649999342, 0.34462240569857266, 0.34807269581882028,
      0.35154584359030394, 0.3550413042245304, 0.35855852151684242,
      0.36209692795324039, 0.36565594482199559, 0.36923498233014063,
      0.37283343972472244, 0.376450705418859, 0.38008615712252924,
      0.38373916197808366, 0.38740907670045033, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, -1.1321754087549754, -1.1321575527431651,
      -1.1320259772738981, -1.1317806800594989, -1.1314216806224147,
      -1.1309490203086243, -1.1303627622960559, -1.1296629915980112,
      -1.1288498150615813, -1.1279233613610502, -1.1268837809862806,
      -1.1257312462260791, -1.1244659511465334, -1.1230881115643214,
      -1.121597965015, -1.11999577071626, -1.1182818095261575,
      -1.1164563838963297, -1.1145198178201907, -1.1124724567761171,
      -1.1103146676656359, -1.1080468387466131, -1.1056693795614634,
      -1.1031827208603857, -1.1005873145196423, -1.0978836334548854,
      -1.0950721715295657, -1.0921534434584146, -1.0891279847060413,
      -1.0859963513806472, -1.0827591201228899, -1.0794168879899053,
      -1.0759702723345292, -1.0724199106797252, -1.0687664605882521,
      -1.0650105995276002, -1.0611530247302208, -1.0571944530490782,
      -1.053135620808558, -1.048977283650758, -1.0447202163772034,
      -1.0403652127860117, -1.0359130855045482, -1.0313646658176103,
      -1.02672080349117, -1.0219823665917256, -1.0171502413012958,
      -1.012225331728096, -1.0072085597129481, -1.0021008646314573,
      -0.99690320319200953, -0.99161654922963061, -0.98624189349575542,
      -0.980780243443959, -0.97523262301169333, -0.969600072398083,
      -0.96388364783783531, -0.958084421371309, -0.95220348061080617,
      -0.94624192850312849, -0.940200883088471, -0.93408147725569168,
      -0.92788485849403057, -0.92161218864132555, -0.91526464362879234,
      -0.90884341322242479, -0.90234970076107912, -0.89578472289130406,
      -0.88914970929898163, -0.88244590243783849, -0.87567455725490084,
      -0.86883694091294961, -0.86193433251005069, -0.85496802279622186,
      -0.8479393138873107, -0.84084951897614557, -0.83369996204103636,
      -0.82649197755169312, -0.81922691017262939, -0.81190611446413075,
      -0.80453095458085744, -0.79710280396815, -0.78962304505611935,
      -0.782093068951591, -0.774514275127983, -0.76688807111318658,
      -0.75921587217553221, -0.75149910100791728, -0.74373918741016809,
      -0.73593756796971954, -0.72809568574068684, -0.72021498992141175,
      -0.71229693553055806, -0.70434298308184184, -0.69635459825746948,
      -0.6883332515803684, -0.68028041808529327, -0.67219757698888172,
      -0.66408621135874579, -0.65594780778168271, -0.64778385603107935,
      -0.63959584873360009, -0.63138528103523606, -0.6231536502667987,
      -0.61490245560894286, -0.60663319775679636, -0.59834737858428855,
      -0.59004650080824639, -0.58173206765235885, -0.57340558251107532,
      -0.5650685486135324, -0.55672246868759079, -0.54836884462405766,
      -0.5400091771411879, -0.53164496544954043, -0.52327770691727193,
      -0.51490889673595575, -0.50654002758700589, -0.49817258930878361,
      -0.48980806856447867, -0.48144794851083783, -0.47309370846782717,
      -0.46474682358931146, -0.45640876453482293, -0.44808099714251332,
      -0.43976498210335696, -0.43146217463669512, -0.42317402416719424,
      -0.41490197400330264, -0.40664746101728128, -0.39841191532688747,
      -0.39019675997879449, -0.38200341063381604, -0.37383327525402071,
      -0.3656877537918089, -0.35756823788102859, -0.34947611053020849,
      -0.34141274581797765, -0.33337950859075355, -0.32537775416276321,
      -0.31740882801848253, -0.30947406551754997, -0.30157479160224354,
      -0.29371232050758056, -0.28588795547411394, -0.27810298846349429,
      -0.27035869987686756, -0.26265635827617728, -0.25499722010843234,
      -0.24738252943301628, -0.23981351765209416, -0.23229140324419123,
      -0.22481739150099619, -0.21739267426746203, -0.21001842968526166,
      -0.20269582193966015, -0.19542600100986215, -0.18821010242289851,
      -0.18104924701110409, -0.17394454067324905, -0.16689707413937757,
      -0.15990792273940993, -0.1529781461755618, -0.14610878829863241,
      -0.1393008768882204, -0.13255542343690738, -0.12587342293846832,
      -0.11925585368015697, -0.11270367703910536, -0.10621783728289713,
      -0.099799261374348511, -0.093448858780550925, -0.087167521286207639,
      -0.0809561228113206, -0.074815519233252373, -0.068746548213217115,
      -0.0627500290272304, -0.056826762401557152, -0.050977530352696067,
      -0.045203096031932274, -0.039504203574493704, -0.033881577953343928,
      -0.028335924837640192, -0.02286793045588903, -0.017478261463827111,
      -0.012167564817055533, -0.0069364676484510463, -0.0017855771503811988,
      0.0032845195382515124, 0.0082732554401185252, 0.013180083842702733,
      0.018004478396646411, 0.022745933209190754, 0.027403962932691331,
      0.031978102848190484, 0.036467908944035787, 0.040872957989530882,
      0.04519284760360355, 0.0494271963184844, 0.053575643638387876,
      0.057637850093180933, 0.061613497287040908, 0.065502287942092813,
      0.069303945937024158, 0.0730182163406713, 0.076644865440582022,
      0.080183680766549081, 0.083634471109116315, 0.086997066533065229,
      0.090271318385880511, 0.093457099301200428, 0.096554303197261923,
      0.099562845270345257, 0.10248266198322871, 0.10531371104866141,
      0.10805597140787165, 0.11070944320411666, 0.11327414775129171,
      0.11575012749761557, 0.11813744598440537, 0.12043618779996143,
      0.12264645852857972, 0.12476838469471517, 0.12680211370231251,
      0.12874781376933359, 0.13060567385749991, 0.13237590359728044,
      0.13405873320814546, 0.135654413414122, 0.13716321535466922,
      0.13858543049091654, 0.13992137050728221, 0.14117136720851575,
      0.14233577241219081, 0.14341495783668493, 0.14440931498468387,
      0.14531925502224288, 0.14614520865344693, 0.14688762599070707,
      0.14754697642072934, 0.14812374846620549, 0.14861844964325741,
      0.14903160631468615, 0.1493637635390648, 0.14961548491572302,
      0.14978735242566577, 0.14987996626847591, 0.14989394469524867,
      0.14982992383760216, 0.14968855753281973, 0.14947051714517046,
      0.149176491383459, 0.14880718611485858, 0.1483633241750808,
      0.14784564517493298, 0.14725490530331964, 0.14659187712674407,
      0.14585734938536377, 0.14505212678565935, 0.14417702978977209,
      0.14323289440157091, 0.14222057194950341, 0.141140928866298,
      0.13999484646556848, 0.13878322071538937, 0.13750696200889945,
      0.1361669949319971, 0.13476425802819092, 0.13329970356066526,
      0.13177429727163054, 0.13018901813901762, 0.12854485813058206,
      0.12684282195548527, 0.12508392681341821, 0.12326920214133141,
      0.12139968935783926, 0.1194764416053693, 0.11750052349011539,
      0.11547301081987238, 0.11339499033981275, 0.11126755946627796,
      0.10909182601865164, 0.10686890794938333, 0.10459993307223464,
      0.10228603878881157, 0.099928371813460357, 0.097528087896591037,
      0.095086351546500192, 0.092604335749764954, 0.090083221690276882,
      0.087524198466985559, 0.0849284628104247, 0.082297218798092472,
      0.0796316775687479, 0.076933057035709976, 0.074202581599212475,
      0.071441481857902847, 0.068650994319536709, 0.065832361110958734,
      0.062986829687423751, 0.06011565254134088, 0.057220086910501462,
      0.054301394485868307, 0.051360841118993819, 0.04839969652913434,
      0.045419234010136991, 0.042420730137161841, 0.039405464473312279,
      0.036374719276243847, 0.033329779204816841, 0.030271931025863768,
      0.027202463321141995, 0.024122666194534664, 0.021033830979568978,
      0.017937249947325616, 0.014834216014795209, 0.011726022453758674,
      0.008613962600250262, 0.0054993295646751875, 0.0023834159426410571,
      -0.00073248647342595216, -0.0038470869818216791, -0.0069590962581905069,
      -0.010067226641181839, -0.013170192417067746, -0.016266710103261438,
      -0.019355498730676275, -0.022435280124860481, -0.025504779185851315,
      -0.028562724166682579, -0.03160784695049413, -0.034638883326172834,
      -0.037654573262483372, -0.040653661180609285, -0.04363489622507264,
      -0.046597032532950194, -0.049538829501352154, -0.052459052053096943,
      -0.055356470900525132, -0.058229862807415357, -0.061078010848925064,
      -0.06389970466952774, -0.066693740738879362, -0.06945892260557196,
      -0.072194061148718, -0.07489797482732527, -0.077569489927406352,
      -0.080207440806777774, -0.0828106701375034, -0.085378029145938131,
      -0.087908377850320671, -0.090400585295877037, -0.09285352978739278,
      -0.09526609911920314, -0.097637190802571036, -0.099965712290401909,
      -0.10225058119926488, -0.10449072552867397, -0.10668508387759351,
      -0.10883260565813728, -0.11093225130641252, -0.11298299249048693,
      -0.11498381231543305, -0.11693370552542773, -0.11883167870286153,
      -0.12067675046444033, -0.1224679516542342, -0.12420432553365891,
      -0.12588492796834688, -0.12750882761189231, -0.12907510608643269,
      -0.13058285816004936, -0.13203119192095972, -0.13341922894846991,
      -0.13474610448068075, -0.13601096757890505, -0.13721298128879406,
      -0.138351322798136, -0.13942518359132294, -0.14043376960045392,
      -0.14137630135306542, -0.14225201411647309, -0.14306015803870109,
      -0.14379999828599321, -0.14447081517688998, -0.14507190431285394,
      -0.14560257670543802, -0.14606215889998425, -0.14644999309583845,
      -0.14676543726307831, -0.1470078652557445, -0.14717666692156361,
      -0.1472712482081644, -0.14729103126577353, -0.14723545454639494,
      -0.14710397289946198, -0.14689605766396224, -0.14661119675703638,
      -0.14624889475904335, -0.14580867299510125, -0.14529006961309465,
      -0.14469263965815496, -0.14401595514361865, -0.14325960511846608,
      -0.14242319573123424, -0.14150635029042846, -0.14050870932142023,
      -0.13942993061985018, -0.13826968930153333, -0.13702767784889036,
      -0.13570360615389032, -0.13429720155754313, -0.13280820888592521,
      -0.13123639048277119, -0.12958152623862787, -0.12784341361659593,
      -0.12602186767466114, -0.12411672108464145, -0.12212782414775206,
      -0.12005504480681752, -0.11789826865513389, -0.11565739894200952,
      -0.11333235657499482, -0.11092308011882107, -0.108429525791069,
      -0.10585166745458671, -0.10318949660666939, -0.10044302236503873,
      -0.097612271450622651, -0.0946972881671738, -0.091698134377737731,
      -0.088614889478006387, -0.085447650366565139, -0.082196531412070922,
      -0.078861664417378574, -0.075443198580642024, -0.071941300453419815,
      -0.068356153895804531, -0.064687960028605843, -0.060936937182619069,
      -0.057103320844994615, -0.0531873636027531, -0.049189335083454078,
      -0.045109521893068577, -0.040948227551064247, -0.036705772422751873,
      -0.032382493648903596, -0.02797874507269138, -0.023494897163961047,
      -0.0189313369408848, -0.014288467889012398, -0.0095667098777617865,
      -0.0047664990743734315, 0.00011171214462989132, 0.0050674552844634721,
      0.010100245825525659, 0.015209583319255454, 0.020394951486354351,
      0.025655818317352849, 0.030991636175475845, 0.036401841901785269,
      0.041885856922552277, 0.047443087358844796, 0.053072924138274705,
      0.058774743108890762, 0.064547905155165411, 0.0703917563160574,
      0.076305627905102827, 0.082288836632512546, 0.088340684729229166,
      0.094460460072914171, 0.10064743631584344, 0.10690087301464929,
      0.11322001576190616, 0.11960409631949317, 0.12605233275373531,
      0.13256392957225288, 0.13913807786251275, 0.14577395543202726,
      0.15247072695018554, 0.15922754409166387, 0.16604354568139634,
      0.17291785784105998, 0.17984959413705531, 0.1868378557299287,
      0.1938817315252252, 0.20098029832571496, 0.20813262098498564,
      0.2153377525623435, 0.22259473447900674, 0.22990259667554924,
      0.23726035777056989, 0.24466702522054504, 0.25212159548084434,
      0.25962305416786507, 0.26717037622226247, 0.27476252607324086,
      0.28239845780387846, 0.29007711531744396, 0.29779743250468743,
      0.30555833341206934, 0.31335873241089407, 0.32119753436732362,
      0.32907363481323609, 0.33698592011790907, 0.34493326766048693,
      0.3529145460032122, 0.36092861506538526, 0.36897432629803495,
      0.37705052285926044, 0.3851560397902225, 0.39328970419175613,
      0.401450335401583, 0.40963674517208482, 0.41784773784862317,
      0.42608211054837558, 0.43433865333965704, 0.44261614942171879,
      0.45091337530497344, 0.45922910099164949, 0.46756209015682593,
      0.47591110032984868, 0.48427488307608008, 0.49265218417898021,
      0.50104174382247824, 0.50944229677363517, 0.51785257256554662,
      0.52627129568049125, 0.53469718573328473, 0.54312895765483427,
      0.551565321875855, 0.56000498451075054, 0.56844664754160912,
      0.57688900900233275, 0.58533076316284571, 0.593770600713386,
      0.60220720894884838, 0.61063927195317791, 0.61906547078377416,
      0.62748448365591025, 0.63589498612713569, 0.64429565128165012,
      0.65268514991464266, 0.66106215071656449, 0.66942532045732939,
      0.67777332417042313, 0.68610482533691819, 0.6944184860693603,
      0.70271296729553112, 0.71098692894205906, 0.71923903011788215,
      0.72746792929753012, 0.73567228450423161, 0.74385075349281571,
      0.75200199393241751, 0.76012466358895958, 0.76821742050740294,
      0.776278923193754, 0.78430783079682831, 0.79230280328974667,
      0.800262501651159, 0.80818558804618634, 0.81607072600707375,
      0.823916580613542, 0.83172181867282913, 0.8394851088994093,
      0.84720512209439147, 0.854880531324582, 0.86251001210119682,
      0.87009224255823314, 0.87762590363047055, 0.88510967923111816,
      0.89254225642907759, 0.89992232562583319, 0.90724858073194992,
      0.91451971934318232, 0.92173444291617757, 0.92889145694377517,
      0.93598947112989328, 0.94302719956399583, 0.9500033608951336,
      0.956916678505559, 0.96376588068389579, 0.9705497007978755,
      0.97726687746662566, 0.98391615473249838, 0.99049628223244768,
      0.99700601536894051, 1.0034441154804026, 1.009809350011188,
      1.0161004926810664, 1.0223163236542365, 1.028455629707844,
      1.0345172044000097, 1.0404998482373526, 1.046402368842017,
      1.0522235811181921, 1.0579623074181117, 1.0636173777075382,
      1.0691876297307255, 1.0746719091748562, 1.0800690698339346,
      1.0853779737721534, 1.0905974914867105, 1.0957265020700746,
      1.1007638933717032, 1.1057085621591936, 1.1105594142788711,
      1.115315364815809, 1.1199753382532629, 1.1245382686315348,
      1.1290030997062295, 1.1333687851059373, 1.1376342884892963,
      1.1417985837014573, 1.1458606549299259, 1.1498194968597908,
      1.1536741148283158, 1.1574235249788958, 1.1610667544143767,
      1.1646028413497098, 1.16803083526396, 1.1713497970516407,
      1.1745587991733666, 1.1776569258058338, 1.1806432729910978,
      1.1835169487851516, 1.1862770734057895, 1.1889227793797548,
      1.191453211689149, 1.1938675279171045, 1.1961648983927038,
      1.1983445063351368, 1.200405547997079, 1.2023472328072977,
      1.2041687835124424, 1.2058694363180471, 1.2074484410286972,
      1.2089050611873693, 1.2102385742139254, 1.2114482715427468,
      1.2125334587594931, 1.2134934557369803, 1.214327596770155,
      1.215035230710152, 1.2156157210974243, 1.2160684462939333,
      1.2163927996143673, 1.2165881894563939, 1.2166540394299155,
      1.2165897884853172, 1.2163948910406885, 1.2160688171080047,
      1.2156110524182413, 1.2150210985454211, 1.2142984730295527,
      1.2134427094984614, 1.2124533577884864, 1.21132998406402,
      1.2100721709358739, 1.2086795175784619, 1.2071516398457545,
      1.2054881703860112, 1.2036887587552518, 1.2017530715294535,
      1.1996807924154478, 1.1974716223605013, 1.1951252796605456,
      1.1926415000670523, 1.19002003689251, 1.1872606611144978,
      1.1843631614783134, 1.1813273445981503, 1.178153035056787,
      1.1748400755037696, 1.1713883267520564, 1.1677976678731081,
      1.1640679962903917, 1.1601992278712743, 1.156191297017281,
      1.1520441567526876, 1.1477577788114279, 1.1433321537222805,
      1.1387672908923145, 1.134063218688562, 1.1292199845178919,
      1.1242376549050634, 1.1191163155689128, 1.113856071496663,
      1.108457047016328, 1.1029193858671644, 1.0972432512681594,
      1.0914288259845186, 1.0854763123921314, 1.0793859325399653,
      1.0731579282103911, 1.066792560977369, 1.0602901122625101,
      1.0536508833889424, 1.0468751956329807, 1.0399633902735512,
      1.032915828639358, 1.025732892153733, 1.0184149823771818,
      1.010962521047543, 1.0033759501177801, 0.99565573179133282,
      0.9878023485550359, 0.97981630320953417, 0.97169811889720414,
      0.96344833912751493, 0.95506752779982973, 0.9465562692235876,
      0.93791516813585885, 0.92914484971622846, 0.92024595959898969,
      0.91121916388259983, 0.90206514913638636, 0.89278462240446288,
      0.88337831120682819, 0.873846963537618, 0.86419134786047447,
      0.85441225310101543, 0.84451048863636813, 0.83448688428173146,
      0.82434229027394734, 0.81407757725205276, 0.80369363623477441,
      0.79319137859495292, 0.78257173603084751, 0.77183566053432162,
      0.76098412435585072, 0.75001811996635759, 0.73893866001581621,
      0.72774677728863024, 0.71644352465572814, 0.7050299750233836,
      0.69350722127869768, 0.68187637623175945, 0.67013857255442255,
      0.65829496271570709, 0.64634671891377249, 0.6342950330044661,
      0.62214111642640668, 0.60988620012259465, 0.59753153445851237,
      0.58507838913670507, 0.57252805310782007, 0.55988183447808981,
      0.54714106041322152, 0.534307077038699, 0.52138124933645613,
      0.5083649610379315, 0.49525961451345935, 0.48206663065799449,
      0.46878744877316425, 0.4554235264456174, 0.44197633942166648,
      0.42844738147820111, 0.41483816428987785, 0.40115021729254818,
      0.38738508754294648, 0.37354433957459166, 0.35962955524992712,
      0.34564233360866958, 0.33158429071236617, 0.31745705948514547,
      0.30326228955068, 0.28900164706531589, 0.27467681454740683,
      0.26028949070282481, 0.24584139024664081, 0.23133424372099309,
      0.21676979730913859, 0.20214981264566537, 0.18747606662290156,
      0.17275035119348853, 0.15797447316915525, 0.14315025401567555,
      0.12827952964400707, 0.11336415019765075, 0.09840597983620325,
      0.0834068965151299, 0.068368791761758335, 0.053293570447511547,
      0.038183150556382252, 0.023039462949673795, 0.00786445112699647,
      -0.0073399290164371661, -0.022571709436210518, -0.037828910188802356,
      -0.053109539685337992, -0.068411594948984591, -0.083733061875982853,
      -0.099071915500266672, -0.1144261202616864, -0.12979363027777838,
      -0.14517238961907236, -0.16056033258791153, -0.17595538400075439,
      -0.19135545947393193, -0.20675846571283837, -0.22216230080451135,
      -0.23756485451357706, -0.25296400858154339, -0.26835763702937204,
      -0.2837436064633404, -0.29911977638411957, -0.31448399949904504,
      -0.3298341220375503, -0.34516798406971849, -0.36048341982790039,
      -0.3757782580313811, -0.3910503222140177, -0.40629743105486377,
      -0.42151739871165395, -0.4367080351571801, -0.45186714651846138,
      -0.4669925354186833, -0.48208200132184864, -0.497133340880093,
      -0.512144348283614, -0.52711281561314594, -0.54203653319496525,
      -0.55691328995832046, -0.57174087379526928, -0.58651707192284908,
      -0.6012396712475313, -0.61590645873188188, -0.63051522176340213,
      -0.64506374852544124, -0.65954982837016962, -0.67397125219350618,
      -0.68832581281196137, -0.70261130534131455, -0.71682552757707729,
      -0.73096628037665179, -0.74503136804314074, -0.75901859871070509,
      -0.77292578473145745, -0.78675074306374049, -0.80049129566178889,
      -0.81414526986666391, -0.82771049879839287, -0.841184821749238,
      -0.85456608457803551, -0.8678521401054986, -0.88104084851041664,
      -0.89413007772670638, -0.907117703841173, -0.92000161149194637,
      -0.93277969426750862, -0.9454498551062035, -0.95801000669617564,
      -0.97045807187564215, -0.98279198403340284, -0.99500968750953089,
      -1.0071091379961374, -1.0190883029381208, -1.0309451619338319,
      -1.0426777071355562, -1.0542839436497269, -1.0657618899367798,
      -1.077109578210554, -1.0883250548371759, -1.0994063807332939,
      -1.1103516317636124, -1.121158899137606, -1.1318262898053413,
      -1.1423519268522953, -1.1527339498931106, -1.1629705154641397,
      -1.1730597974147547, -1.1829999872972661, -1.1927892947553924,
      -1.2024259479111739, -1.2119081937502481, -1.2212342985053748,
      -1.2304025480381189, -1.2394112482186217, -1.248258725303321,
      -1.2569433263105667, -1.2654634193940111, -1.273817394213685,
      -1.2820036623046651, -1.2900206574432402, -1.2978668360104744,
      -1.3055406773530736, -1.313040684141453, -1.3203653827249442,
      -1.327513323483978, -1.3344830811792328, -1.3412732552975735,
      -1.34788247039475, -1.3543093764347121, -1.3605526491254856,
      -1.3666109902514809, -1.3724831280021719, -1.3781678172970238,
      -1.3836638401065962, -1.3889700057697172, -1.3940851513066479,
      -1.3990081417281306, -1.4037378703402379, -1.4082732590449365,
      -1.4126132586362623, -1.4167568490920275, -1.42070303986097,
      -1.4244508701452463, -1.4279994091781918, -1.4313477564972579,
      -1.4344950422120344, -1.4374404272672765, -1.4401831037008479,
      -1.4427222948965022, -1.4450572558314081, -1.4471872733183444,
      -1.4491116662424859, -1.4508297857926835, -1.4523410156871743,
      -1.4536447723936436, -1.454740505343542, -1.455627697140605,
      -1.4563058637634776, -1.456774554762388, -1.4570333534497797,
      -1.4570818770848406, -1.4569197770518556, -1.4565467390323039,
      -1.45596248317065, -1.4551667642337385, -1.4541593717637391,
      -1.4529401302245819, -1.451508899141799, -1.4498655732357291,
      -1.4480100825480191, -1.4459423925613488, -1.4436625043123412,
      -1.4411704544975894, -1.4384663155727415, -1.4355501958445971,
      -1.4324222395561594, -1.4290826269645909, -1.4255315744120247,
      -1.4217693343891773, -1.4177961955917275, -1.4136124829694088,
      -1.4092185577677685, -1.4046148175625603, -1.3998016962867239,
      -1.3947796642499242, -1.3895492281505883, -1.3841109310804394,
      -1.3784653525214678, -1.3726131083353175, -1.3665548507450627,
      -1.3602912683093296, -1.3538230858887674, -1.3471510646048146,
      -1.3402760017907462, -1.3331987309349962, -1.325920121616718,
      -1.3184410794335759, -1.3107625459217516, -1.3028854984681408,
      -1.2948109502147584, -1.2865399499553054, -1.2780735820239175,
      -1.2694129661760856, -1.2605592574617313, -1.2515136460904497,
      -1.242277357288925, -1.2328516511504923, -1.2232378224768929,
      -1.213437200612193, -1.2034511492688957, -1.1932810663462492,
      -1.1829283837407625, -1.1723945671489509, -1.1616811158623193,
      -1.1507895625546092, -1.1397214730613274, -1.1284784461515731,
      -1.1170621132922076, -1.1054741384043658, -1.0937162176123643,
      -1.0817900789850288, -1.0696974822694558, -1.057440218617286,
      -1.0450201103034715, -1.0324390104376306, -1.0196988026679954,
      -1.0068014008780055, -0.99374874887560039, -0.98054282007525573,
      -0.96718561717279439, -0.9536791718130686, -0.940025544250501,
      -0.92622682300261427, -0.9122851244965452, -0.89820259270864056,
      -0.88398139879717852, -0.86962374072829063, -0.855131842895142,
      -0.84050795573043335, -0.82575435531231756, -0.81087334296376845,
      -0.7958672448455012, -0.78073841154251056, -0.76548921764431355,
      -0.75012206131894565, -0.73463936388083939, -0.71904356935262137,
      -0.7033371440209546, -0.68752257598646338, -0.67160237470788786,
      -0.65557907054050635, -0.63945521426895269, -0.62323337663449829,
      -0.60691614785691916, -0.5905061371510113, -0.574005972237902,
      -0.55741829885119321, -0.540745780238105, -0.52399109665567967,
      -0.50715694486216822, -0.49024603760369712, -0.47326110309634872,
      -0.45620488450372138, -0.43908013941012169, -0.42188963928949763,
      -0.40463616897018906, -0.38732252609565959, -0.36995152058130359,
      -0.35252597406744729, -0.33504871936867131, -0.31752259991956394,
      -0.299950469217044, -0.282335190259379, -0.26467963498198793,
      -0.24698668369020407, -0.22925922448909569, -0.21150015271048345,
      -0.19371237033727975, -0.17589878542528581, -0.15806231152256653,
      -0.14020586708656926, -0.12233237489906454, -0.10444476147909917,
      -0.086545956494067211, -0.068638892169049531, -0.050726502694538309,
      -0.03281172363271076, -0.014897491322381981, 0.003013257717241917,
      0.020917587383820491, 0.038812562590078752, 0.056695249862736573,
      0.0745627179420661, 0.092412038381912587, 0.11024028615006676,
      0.12804454022880093, 0.14582188421546827, 0.16356940692296587,
      0.18128420298000414, 0.19896337343092721, 0.21660402633503173,
      0.2342032773651781, 0.25175825040559013, 0.26926607814865905,
      0.28672390269064246, 0.30412887612606176, 0.32147816114073169,
      0.33876893160317922, 0.35599837315437866, 0.37316368379562009,
      0.39026207447438088, 0.40729076966804856, 0.42424700796534076,
      0.44112804264530003, 0.45793114225367837, 0.47465359117662481,
      0.49129269021147043, 0.50784575713450519, 0.52431012726558235,
      0.54068315402943135, 0.55696220951351072, 0.57314468502227311,
      0.589227991627679, 0.60520956071588039, 0.62108684452983953,
      0.63685731670782708, 0.65251847281761177, 0.66806783088623056,
      0.683502931925176, 0.69882134045090383, 0.714020645000464,
      0.72909845864220824, 0.74405241948134848, 0.75888019116030014,
      0.77357946335364014, 0.78814795225758649, 0.80258340107383053,
      0.81688358048762078, 0.83104628913996925, 0.84506935409383988,
      0.85895063129421867, 0.87268800602192864, 0.88627939334105832,
      0.89972273853991169, 0.91301601756534578, 0.92615723745037271,
      0.93914443673492565, 0.95197568587965908, 0.96464908767270463,
      0.9771627776292201, 0.98951492438367306, 1.0017037300747236,
      1.0137274307226107, 1.0255842965989344, 1.0372726325887498,
      1.0487907785448287, 1.0601371096340695, 1.0713100366758646,
      1.0823080064724067, 1.0931295021308056, 1.1037730433769417,
      1.114237186860954, 1.124520526454283, 1.134621693538201,
      1.1445393572837119, 1.1542722249227815, 1.1638190420107959,
      1.1731785926801781, 1.1823496998850882, 1.191331225637156,
      1.2001220712321397, 1.2087211774674842, 1.2171275248506843,
      1.2253401337984262, 1.2333580648263969, 1.2411804187297661,
      1.2488063367542306, 1.2562350007576162, 1.263465633361941,
      1.2704974980959449, 1.2773298995279909, 1.2839621833893384,
      1.2903937366877158, 1.2966239878111763, 1.3026524066221965,
      1.3084785045419811, 1.3141018346249544, 1.3195219916233987,
      1.3247386120422338, 1.3297513741838942, 1.3345599981832996,
      1.3391642460329025, 1.3435639215977986, 1.3477588706208654,
      1.3517489807179708, 1.355534181363192, 1.3591144438640819,
      1.36248978132695, 1.3656602486121976, 1.3686259422796712,
      1.3713870005240711, 1.3739436031004162, 1.3762959712395721,
      1.378444367553866, 1.3803890959328073, 1.3821305014289251,
      1.3836689701337554, 1.385004929044005, 1.3861388459179078,
      1.3870712291218195, 1.3878026274670832, 1.3883336300371991,
      1.3886648660053227, 1.388797004442178, 1.3887307541143654,
      1.3884668632731827, 1.3880061194339464, 1.387349349145911,
      1.3864974177528104, 1.3854512291441057, 1.3842117254969781,
      1.3827798870091375, 1.3811567316225166, 1.3793433147379139,
      1.3773407289206518, 1.375150103597335, 1.3727726047437703,
      1.3702094345641349, 1.3674618311614715, 1.3645310681995857,
      1.3614184545564467, 1.3581253339691615, 1.3546530846706182,
      1.3510031190179013, 1.34717688311255, 1.3431758564127865,
      1.3390015513377793, 1.3346555128640674, 1.3301393181142522,
      1.3254545759380276, 1.3206029264857013, 1.315586040774283,
      1.3104056202462708, 1.3050633963212379, 1.2995611299403429,
      1.2939006111038782, 1.2880836584019757, 1.2821121185385984,
      1.27598786584893, 1.2697128018102937, 1.2632888545467362,
      1.2567179783273983, 1.250002153058787, 1.2431433837711177,
      1.2361437000988282, 1.2290051557554278, 1.2217298280027846,
      1.2143198171150276, 1.206777245837185, 1.1991042588386946,
      1.1913030221619487, 1.1833757226660093, 1.175324567465629,
      1.1671517833657608, 1.1588596162916545, 1.1504503307147305,
      1.1419262090743827, 1.1332895511958292, 1.1245426737042021,
      1.1156879094350154, 1.1067276068411618, 1.0976641293966063,
      1.0884998549969438, 1.0792371753569419, 1.0698784954052731,
      1.0604262326765794, 1.0508828167010236, 1.0412506883914987,
      1.0315322994286544, 1.0217301116439184, 1.0118465964006509,
      1.001884233973622, 0.99184551292696044, 0.98173292949075142,
      0.97154898693644742, 0.96129619495125174, 0.95097706901164969,
      0.94059412975625, 0.93014990235811545, 0.91964691589672143,
      0.90908770272975237, 0.89847479786486972, 0.88781073833163826,
      0.87709806255376244, 0.86633930972182549, 0.85553701916667313,
      0.84469372973362467, 0.83381197915768268, 0.8228943034398879,
      0.81194323622500786, 0.80096130818072608, 0.78995104637847047,
      0.77891497367608764, 0.76785560810249509, 0.75677546224448489,
      0.74567704263586931, 0.73456284914907322, 0.72343537438940531,
      0.7122971030921178, 0.70115051152245322, 0.68999806687879517,
      0.67884222669913408, 0.66768543827096649, 0.65653013804481775,
      0.64537875105150022, 0.63423369032331978, 0.623097356319336,
      0.61197213635486647, 0.60086040403535357, 0.58976451869477842,
      0.57868682483874223, 0.567629651592393, 0.55659531215331337,
      0.54558610324953738, 0.53460430460283614, 0.52365217839741474,
      0.51273196875415106, 0.50184590121053885, 0.49099618220644503,
      0.480184998575847, 0.46941451704466319, 0.45868688373481015,
      0.44800422367463577, 0.43736864031584849, 0.426782215057049,
      0.41624700677403104, 0.405765051356941, 0.39533836125443539,
      0.38496892502495272, 0.37465870689520459, 0.36440964632602646,
      0.35422365758568386, 0.34410262933074864, 0.3340484241946533,
      0.32406287838404291, 0.31414780128300734, 0.30430497506531418,
      0.29453615431474645, 0.28484306565361273, 0.27522740737956736,
      0.26569084911080043, 0.25623503143970738, 0.246861565595115,
      0.23757203311315975, 0.22836798551689258, 0.21925094400470435,
      0.21022239914762633, 0.20128381059561284, 0.1924366067928503,
      0.18368218470218592, 0.17502190953872745, 0.16645711451269368,
      0.15798910058155746, 0.1496191362115743, 0.14134845714871136,
      0.13317826619907566, 0.12510973301885459, 0.11714399391384976,
      0.10928215164862005, 0.10152527526530736, 0.093874399912168449,
      0.086330526681840464, 0.078894622459407773, 0.0715676197802758,
      0.064350416697878679, 0.057243876661270413, 0.050248828402608761,
      0.043366065834545081, 0.036596347957559262, 0.029940398777230023,
      0.023398907231474267, 0.016972527127750447, 0.010661877090249693,
      0.0044675405170402881, -0.0016099344527730607, -0.0075700349619422617,
      -0.013412283447974972, -0.0191362376460861, -0.02474149058217814,
      -0.030227670555898135, -0.035594441113759021, -0.040841501012364653,
      -0.0459685841717447, -0.050975459618847613, -0.055861931421188254,
      -0.060627838610713594, -0.065273055097900712, -0.069797489576113772,
      -0.074201085416303353, -0.078483820552034012, -0.08264570735492574,
      -0.0866867925005382, -0.0906071568247562, -0.094406915170729327,
      -0.098086216226417625, -0.10164524235279775, -0.10508420940280828,
      -0.10840336653108473, -0.11160299599454929, -0.11468341294393587,
      -0.11764496520630993, -0.12048803305867234, -0.12321302899270954,
      -0.125820397470779, -0.12831061467321056, -0.13068418823701042,
      -0.13294165698604818, -0.1350835906528258, -0.1371105895919095,
      -0.13902328448514326, -0.14082233603869534, -0.14250843467209592,
      -0.14408230019931856, -0.14554468150203009, -0.1468963561951237,
      -0.14813813028462106, -0.14927083781807476, -0.15029534052756824,
      -0.15121252746544353, -0.15202331463285523, -0.15272864460129304,
      -0.15332948612716971, -0.1538268337596102, -0.15422170744157276,
      -0.15451515210441552, -0.15470823725604022, -0.15480205656275425,
      -0.15479772742497058, -0.15469639054688489, -0.15449920950026957,
      -0.15420737028251272, -0.15382208086904905, -0.15334457076032387,
      -0.15277609052342014, -0.15211791132851213, -0.15137132448027385,
      -0.15053764094439592, -0.14961819086935668, -0.14861432310360245,
      -0.14752740470828157, -0.14635882046567797, -0.14510997238350989,
      -0.1437822791952508, -0.14237717585660398, -0.1408961130383114,
      -0.13934055661544217, -0.13771198715332097, -0.13601189939026276,
      -0.13424180171725092, -0.13240321565475108, -0.13049767532679749,
      -0.12852672693252837, -0.1264919282153231, -0.12439484792970745,
      -0.12223706530620185, -0.12002016951425377, -0.11774575912344455,
      -0.11541544156311821, -0.11303083258060709, -0.1105935556982158,
      -0.10810524166913345, -0.10556752793243199, -0.10298205806733685,
      -0.10035048124690429, -0.097674451691311018, -0.094955628120889118,
      -0.0921956732090957, -0.08939625303556975, -0.086559036539454792,
      -0.083685694973131858, -0.080777901356570522, -0.077837329932409841,
      -0.074865655621977417, -0.071864553482393873, -0.0688356981649274,
      -0.065780763374768764, -0.062701421332378771, -0.059599342236583017,
      -0.056476193729576976, -0.053333640363987009, -0.050173343072166435,
      -0.0469969586378761, -0.0438061391705111, -0.040602531582039275,
      -0.037387777066789613, -0.034163510584269738, -0.030931360345153047,
      -0.027692947300597456, -0.024449884635040654, -0.021203777262630046,
      -0.017956221327446648, -0.014708803707643242, -0.011463101523683412,
      -0.00822068165079914, -0.0049831002358242775, -0.0017519022185494351,
      0.0014713791422684766, 0.00468522273809106, 0.0078881200748396919,
      0.011078575732065048, 0.01425510781689698, 0.017416248412645,
      0.020560544021919928, 0.023686556004135439, 0.026792861007279446,
      0.029878051393802622, 0.0329407356605239, 0.035979538852410606,
      0.038993102970121582, 0.041980087371190487, 0.044939169164735566,
      0.047869043599571559, 0.050768424445625016, 0.053636044368525614,
      0.056470655297278669, 0.0592710287849022, 0.062035956361929719,
      0.064764249882675179, 0.067454741864157786, 0.070106285817593456,
      0.072717756572354672, 0.075288050592307421, 0.077816086284433567,
      0.080300804299651571, 0.082741167825750125, 0.085136162872353718,
      0.087484798547832615, 0.089786107328090975, 0.092039145317145743,
      0.094242992499435088, 0.096396752983772149, 0.09849955523889467,
      0.10055055232052892, 0.10254892208991642, 0.10449386742373785,
      0.10638461641538467, 0.10822042256751341, 0.11000056497584543,
      0.11172434850414846, 0.11339110395036893, 0.11500018820386126,
      0.11655098439367785, 0.11804290202788335, 0.11947537712385881,
      0.12084787232956209, 0.12215987703571327, 0.12341090747889183,
      0.12460050683550242, 0.12572824530660495, 0.12679372019358756,
      0.12779655596466369, 0.12873640431218342, 0.12961294420075786,
      0.13042588190617621, 0.13117495104512572, 0.13185991259570451,
      0.13248055490874205, 0.13303669370991553, 0.13352817209268963,
      0.13395486050207484, 0.13431665670922896, 0.13461348577691426,
      0.13484530001583075, 0.13501207893185146, 0.13511382916417947,
      0.13515058441445613, 0.13512240536686207, 0.13502937959922692,
      0.13487162148520399, 0.13464927208753008, 0.13436249904243064,
      0.1340114964352023, 0.13359648466702809, 0.13311771031307429,
      0.13257544597191853, 0.13196999010637289, 0.13130166687575107,
      0.1305708259596447, 0.12977784237328358, 0.12892311627452507,
      0.12800707276256351, 0.12703016166840714, 0.12599285733723065,
      0.12489565840264585, 0.12373908755298625, 0.12252369128969259,
      0.1212500396778666, 0.11991872608910205, 0.11853036693665651,
      0.11708560140307708, 0.1155850911603615, 0.1140295200827581,
      0.11241959395229194, 0.11075604015712978, 0.10903960738288587,
      0.10727106529695829, 0.10545120422602464, 0.10358083482679151,
      0.10166078775011056, 0.099691913298583124, 0.097675081077755049,
      0.095611179641035077, 0.093501116128441586, 0.091345815899305849,
      0.08914622215906419, 0.0869032955802255, 0.084618013917708915,
      0.082291371618601075, 0.0799243794265311, 0.077518063980742874,
      0.075073467410041561, 0.072591646921707928, 0.070073674385555548,
      0.067520635913233387, 0.064933631432942812, 0.062313774259690612,
      0.059662190661231795, 0.056980019419829, 0.054268411389999036,
      0.051528529052370868, 0.048761546063801522, 0.045968646803920911,
      0.043151025918225935, 0.0403098878578965, 0.037446446416470949,
      0.0345619242635422, 0.031657552475610189, 0.028734570064292243,
      0.025794223501963046, 0.022837766245074633, 0.019866458255227679,
      0.016881565518222216, 0.013884359561198392, 0.010876116968030508,
      0.0078581188931556717, 0.0048316505739902371, 0.0017980008420560717,
      -0.0012415383669667143, -0.004285672504138506, -0.0073331048989366612,
      -0.010382537251557945, -0.013432670125674312, -0.016482203441487965,
      -0.019529836968927065, -0.022574270820818164, -0.025614205945872041,
      -0.0286483446213289, -0.031675390945093834, -0.034694051327212719,
      -0.037703034980519953, -0.040701054410306789, -0.043686825902821087,
      -0.046659070012513078, -0.049616512047754954, -0.052557882554997659,
      -0.055481917801119, -0.058387360253836784, -0.061272959060045769,
      -0.064137470521900664, -0.066979658570491013, -0.069798295236972646,
      -0.072592161120973636, -0.075360045856165209, -0.078100748572791714,
      -0.0808130783570477, -0.08349585470715272, -0.086147907985956673,
      -0.088768079869921523, -0.091355223794378326, -0.0939082053948635,
      -0.0964259029444183, -0.098907207786704421, -0.10135102476478294,
      -0.10375627264545001, -0.10612188453894161, -0.10844680831390696,
      -0.11073000700752393, -0.11297045923056612, -0.11516715956736522,
      -0.11731911897048465, -0.11942536514997804, -0.12148494295715132,
      -0.12349691476264385, -0.12546036082874251, -0.12737437967579843,
      -0.12923808844261928, -0.13105062324073147, -0.13281113950238727,
      -0.13451881232219642, -0.13617283679229747, -0.13777242833092437,
      -0.1393168230042828, -0.14080527784162986, -0.14223707114342923,
      -0.14361150278252532, -0.14492789449819651, -0.14618559018299482,
      -0.14738395616231365, -0.14852238146654251, -0.14960027809575238,
      -0.15061708127681123, -0.15157224971283764, -0.15246526582493763,
      -0.15329563598610343, -0.1540628907472231, -0.15476658505513646,
      -0.15540629846261633, -0.15598163533026702, -0.15649222502021942,
      -0.15693772208158674, -0.15731780642761173, -0.1576321835044395,
      -0.15788058445146128, -0.15806276625318291, -0.15817851188254373,
      -0.15822763043567134, -0.1582099572579834, -0.15812535406162148,
      -0.15797370903417732, -0.15775493693864814, -0.15746897920459962,
      -0.15711580401052305, -0.15669540635730567, -0.15620780813284632,
      -0.1556530581677443, -0.15503123228205806, -0.15434243332312569,
      -0.1535867911944066, -0.15276446287534073, -0.15187563243223112,
      -0.15092051102010542, -0.14989933687559304, -0.14881237530077868,
      -0.14765991863805233, -0.14644228623596012, -0.1451598244060531,
      -0.14381290637073771, -0.14240193220216382, -0.14092732875213212,
      -0.13938954957307256, -0.13778907483007258, -0.13612641120401911,
      -0.13440209178585688, -0.13261667596199159, -0.13077074929087434,
      -0.12886492337080269, -0.12689983569896746, -0.12487614952179783,
      -0.12279455367662251, -0.12065576242471798, -0.11846051527578154,
      -0.11620957680386493, -0.11390373645484445, -0.11154380834547409,
      -0.10913063105406186, -0.10666506740285883, -0.10414800423221281,
      -0.10158035216653229, -0.098963045372163591, -0.09629704130722766,
      -0.093583320463497238, -0.0908228861003891, -0.088016763971143955,
      -0.085166002041296207, -0.082271670199482824, -0.079334859960700582,
      -0.0763566841620991, -0.073338276651383538, -0.070280791967943193,
      -0.0671854050167624, -0.064053310735260355, -0.060885723753123733,
      -0.057683878045234643, -0.054449026577814544, -0.051182440947879305,
      -0.047885411016107667, -0.044559244533242851, -0.041205266760140823,
      -0.037824820081557256, -0.034419263613818855, -0.030989972806472713,
      -0.027538339038040698, -0.024065769206010411, -0.020573685311168939,
      -0.017063524036399533, -0.013536736320111955, -0.00999478692436405,
      -0.0064391539978588611, -0.0028713286339399277, 0.00070718557630389256,
      0.0042948729956800852, 0.0078902063971312969, 0.011491647424443821,
      0.015097647057298942, 0.018706646080509981, 0.022317075557307081,
      0.025927357306534143, 0.029535904383602651, 0.03314112156508791,
      0.036741405836765488, 0.040335146884990736, 0.043920727591268874,
      0.047496524529834529, 0.051060908468107111, 0.054612244869895729,
      0.058148894401172421, 0.06166921343824211, 0.065171554578224877,
      0.0686542671516297, 0.072115697736882978, 0.075554190676680066,
      0.0789680885959787, 0.082355732921476632, 0.085715464402441821,
      0.089045623632706281, 0.092344551573687358, 0.095610590078270913,
      0.098842082415398116, 0.10203737379518443, 0.10519481189445459,
      0.10831274738247318, 0.11138953444676135, 0.11442353131881652,
      0.11741310079958048, 0.12035661078450204, 0.1232524347880265,
      0.12609895246736302, 0.12889455014535917, 0.13163762133233373,
      0.13432656724670985, 0.13695979733428157, 0.13953572978596757,
      0.14205279205388804, 0.14450942136560457, 0.14690406523638858,
      0.14923518197931779, 0.15150124121310682, 0.15370072436747348,
      0.15583212518588646, 0.1578939502255664, 0.1598847193545922,
      0.16180296624591639, 0.16364723886819044, 0.1654160999732262,
      0.16710812757994203, 0.16872191545466614, 0.1702560735876239,
      0.17170922866548752, 0.17308002453984264, 0.17436712269140442,
      0.17556920268987256, 0.17668496264927336, 0.17771311967863893,
      0.17865241032790688, 0.17950159102889104, 0.18025943853119003,
      0.18092475033289784, 0.18149634510600646, 0.18197306311634071,
      0.18235376663790434, 0.18263734036153559, 0.18282269179771862,
      0.18290875167342988, 0.18289447432292116, 0.18277883807230302,
      0.1825608456177856, 0.18223952439753283, 0.18181392695693466,
      0.1812831313072242, 0.18064624127735612, 0.17990238685897011,
      0.1790507245443988, 0.17809043765758187, 0.17702073667778134,
      0.17584085955602949, 0.1745500720241743, 0.17314766789644892,
      0.17163296936346248, 0.17000532727854178, 0.16826412143629477,
      0.16640876084334863, 0.16443868398116346, 0.16235335906082815,
      0.16015228426977735, 0.15783498801034798, 0.15540102913008683,
      0.15284999714376379, 0.15018151244698269, 0.14739522652136758,
      0.14449082213121328, 0.14146801351158467, 0.1383265465477547,
      0.13506619894597519, 0.13168678039548665, 0.12818813272172042,
      0.12457013003067134, 0.12083267884436501, 0.1169757182273688,
      0.11299921990434775, 0.10890318836858273, 0.10468766098142247,
      0.10035270806265965, 0.095898432971776373, 0.0913249721800215,
      0.086632495333345189, 0.081821205306084319, 0.076891338245469426,
      0.0718431636068656, 0.066676984179753873, 0.061393136104460164,
      0.0559919888796052, 0.050473945360250495, 0.044839441746767676,
      0.03908894756441729, 0.033222965633637414, 0.027242032031022795,
      0.021146716041054586, 0.014937620098545094, 0.0086153797218072974,
      0.002180663436597563, -0.0043658273091847152, -0.011023358239984606,
      -0.017791162356303333, -0.024668440047544073, -0.031654359213999353,
      -0.038748055397942724, -0.045948631923799284, -0.053255160047360917,
      -0.060666679113956075, -0.06818219672563422, -0.075800688917238124,
      -0.083521100341329965, -0.0913423444619714, -0.099263303757252369,
      -0.10728282993054358, -0.11539974413040022, -0.12361283717907466,
      -0.13192086980959564, -0.14032257291126912, -0.14881664778364953,
      -0.15740176639882944, -0.16607657167201006, -0.17483967774025624,
      -0.18368967024941471, -0.19262510664905841, -0.20164451649541071,
      -0.21074640176212728, -0.219929237158951, -0.2291914704580246,
      -0.2385315228278454, -0.24794778917477814, -0.25743863849202,
      -0.26700241421587972, -0.27663743458935469, -0.28634199303283009,
      -0.29611435852187623, -0.30595277597196024, -0.31585546663001624,
      -0.32582062847278515, -0.33584643661175356, -0.34593104370462224,
      -0.35607258037320988, -0.36626915562764228, -0.37651885729669715,
      -0.38681975246426215, -0.39716988791170771, -0.40756729056609692,
      -0.41800996795407941, -0.4284959086613932, -0.43902308279781965,
      -0.44958944246744437, -0.46019292224411, -0.47083143965200613,
      -0.48150289565111765, -0.49220517512752682, -0.50293614738837078,
      -0.51369366666136274, -0.52447557259869548, -0.53527969078520132,
      -0.54610383325066769, -0.5569457989861466, -0.56780337446406548,
      -0.57867433416209735, -0.58955644109057781, -0.60044744732333866,
      -0.61134509453182451, -0.62224711452233894, -0.633151229776302,
      -0.64405515399331492, -0.65495659263693407, -0.66585324348301766,
      -0.67674279717043073, -0.68762293775400829, -0.69849134325965334,
      -0.70934568624134775, -0.72018363433999333, -0.73100285084385141,
      -0.74180099525056076, -0.75257572383045068, -0.76332469019103644,
      -0.77404554584260465, -0.7847359407646749, -0.79539352397318885,
      -0.80601594408828914, -0.81660084990255344, -0.82714589094950353,
      -0.83764871807223629, -0.84810698399203688, -0.85851834387684922,
      -0.86888045590938279, -0.87919098185475664, -0.889447587627527,
      -0.89964794385795233, -0.90978972645727874, -0.9198706171819977,
      -0.92988830419686541, -0.93984048263652464, -0.94972485516562011,
      -0.95953913253723055, -0.96928103414950284, -0.97894828860028871,
      -0.98853863423964916, -0.99804981972019269, -1.0074796045448904,
      -1.0168257596124144, -1.0260860677597785, -1.0352583243021196,
      -1.0443403375695413, -1.0533299294407914, -1.0622249358737355,
      -1.0710232074324277, -1.079722609810615, -1.0883210243516279,
      -1.0968163485644389, -1.1052064966357982, -1.1134893999382955,
      -1.1216630075342282, -1.1297252866751608, -1.1376742232969961,
      -1.1455078225104807, -1.1532241090870123, -1.1608211279395995,
      -1.1682969445988649, -1.1756496456839796, -1.1828773393684102,
      -1.1899781558403291, -1.1969502477576024, -1.2037917906972448,
      -1.2105009835992051, -1.2170760492043748, -1.2235152344867184,
      -1.229816811079439, -1.2359790756950095, -1.2420003505390251,
      -1.2478789837177655, -1.2536133496393367, -1.2592018494083022,
      -1.2646429112137425, -1.2699349907106061, -1.2750765713942673,
      -1.2800661649682095, -1.2849023117047536, -1.2895835807987122,
      -1.2941085707139179, -1.2984759095225176, -1.3026842552369811,
      -1.3067322961347041, -1.3106187510751681, -1.3143423698095578,
      -1.3179019332827797, -1.3212962539278015, -1.3245241759522275,
      -1.3275845756171125, -1.3304763615078392, -1.333198474797108,
      -1.3357498894999087, -1.3381296127204461, -1.3403366848909593,
      -1.3423701800023848, -1.3442292058268013, -1.3459129041316316,
      -1.3474204508855312, -1.3487510564559368, -1.3499039657982232,
      -1.3508784586364511, -1.3516738496356262, -1.3522894885654944,
      -1.3527247604557902, -1.3529790857429425, -1.3530519204081761,
      -1.3529427561070453, -1.352651120290302, -1.3521765763161346,
      -1.35151872355374, -1.3506771974782106, -1.3496516697567267,
      -1.3484418483260598, -1.3470474774613446, -1.3454683378361465,
      -1.3437042465738127, -1.3417550572900863, -1.339620660127026,
      -1.3373009817781845, -1.3347959855050935, -1.3321056711450485,
      -1.3292300751101949, -1.3261692703779391, -1.3229233664727109,
      -1.3194925094390693, -1.3158768818061728, -1.3120767025436919,
      -1.3080922270090956, -1.303923746886406, -1.2995715901164508,
      -1.2950361208185996, -1.2903177392040457, -1.2854168814806866,
      -1.2803340197496058, -1.2750696618932058, -1.2696243514550569,
      -1.2639986675114685, -1.2581932245348835, -1.25220867224906,
      -1.2460456954761774, -1.2397050139758834, -1.233187382276316,
      -1.2264935894971851, -1.2196244591649623, -1.2125808490202583,
      -1.2053636508174077, -1.1979737901163519, -1.1904122260669139,
      -1.1826799511854778, -1.1747779911241636, -1.1667074044326042,
      -1.1584692823123472, -1.1500647483639839, -1.1414949583270735,
      -1.13276109981296, -1.12386439203052, -1.1148060855049859,
      -1.1055874617898491, -1.0962098331720336, -1.086674542370311,
      -1.076982962227113, -1.0671364953938449, -1.0571365740097594,
      -1.0469846593744441, -1.0366822416141321, -1.026230839341826,
      -1.0156319993113769, -1.0048872960655928, -0.99399833157853068,
      -0.98296673489200626, -0.97179416174647715, -0.960482294206343,
      -0.94903284027984725, -0.93744753353363486, -0.92572813270204668,
      -0.91387642129133762, -0.9018942071788757, -0.88978332220743361,
      -0.87754562177466788, -0.86518298441798547, -0.8526973113947951,
      -0.84009052625830372, -0.827364574429031, -0.81452142276207273,
      -0.80156305911024739, -0.78849149188329393, -0.77530874960316543,
      -0.76201688045564642, -0.74861795183823432, -0.73511404990459539,
      -0.72150727910562729, -0.70779976172721892, -0.69399363742487974,
      -0.68009106275535014, -0.6660942107053357, -0.65200527021741739,
      -0.63782644571331781, -0.62355995661468144, -0.60920803686139469,
      -0.59477293442763157, -0.580256910835767, -0.565662240668236,
      -0.55099121107749494, -0.53624612129415472, -0.521429282133536,
      -0.50654301550060088, -0.49158965389353088, -0.47657153990598894,
      -0.4614910257282489, -0.44635047264726679, -0.43115225054581913,
      -0.41589873740089556, -0.40059231878144191, -0.38523538734545909,
      -0.36983034233681145, -0.354379589081678, -0.33888553848483011,
      -0.32335060652587888, -0.30777721375558847, -0.29216778479240341,
      -0.27652474781927244, -0.260850534080898, -0.24514757738159043,
      -0.22941831358377246, -0.21366518010725893, -0.19789061542948538,
      -0.18209705858678116, -0.16628694867675708, -0.15046272436195818,
      -0.13462682337494924, -0.11878168202486022, -0.10292973470552468,
      -0.087073413405390418, -0.071215147219253067, -0.055357361861917795,
      -0.039502479183935714, -0.023652916689502645, -0.0078110870566853105,
      0.0080206023400653526, 0.02383974990482975, 0.039643960292537764,
      0.055430844878620739, 0.071198022225858873, 0.086943118548260048,
      0.10266376817201288, 0.11835761399324442, 0.13402230793265474,
      0.14965551138675703, 0.16525489567578192, 0.18081814248806119,
      0.1963429443208147, 0.21182700491724138, 0.22726803969985021,
      0.2426637761999523, 0.25801195448311726, 0.27331032757069013,
      0.28855666185708229, 0.30374873752293646, 0.31888434894392614,
      0.33396130509521244, 0.34897742995146719, 0.36393056288229719,
      0.37881855904311224, 0.3936392897612806, 0.40839064291753058,
      0.42307052332249578, 0.43767685308838766, 0.45220757199568495,
      0.46666063785473588, 0.48103402686233754, 0.495325733953036,
      0.50953377314528947, 0.52365617788225938, 0.537691001367271,
      0.55163631689388037, 0.56549021817042666, 0.57925081963906377,
      0.59291625678923976, 0.60648468646552589, 0.61995428716973722,
      0.63332325935738842, 0.64658982572827917, 0.65975223151135953,
      0.67280874474363406, 0.68575765654322407, 0.69859728137647981,
      0.71132595731904436, 0.72394204631099246, 0.73644393440582279,
      0.7488300320134339, 0.76109877413692506, 0.77324862060327471,
      0.78527805628785707, 0.79718559133271116, 0.80896976135862342,
      0.82062912767092622, 0.83216227745907545, 0.84356782398986152,
      0.854844406794381, 0.8659906918486574, 0.87700537174791782,
      0.8878871658745201, 0.89863482055952093, 0.9092471092379022,
      0.91972283259734589, 0.93006081872071167, 0.94025992322205609,
      0.95031902937630353, 0.96023704824250022, 0.97001291878069351,
      0.97964560796242, 0.9891341108747872, 0.99847745081821149,
      1.0076746793977418, 1.0167248766080728, 1.025627150912138,
      1.0343806393134141, 1.0429845074218955, 1.0514379495136981,
      1.0597401885844528, 1.0678904763963333, 1.0758880935188855,
      1.0837323493636031, 1.091422582212257, 1.0989581592390667,
      1.1063384765267061, 1.1135629590761227, 1.1206310608102987,
      1.1275422645719024, 1.1342960821148709, 1.1408920540900194,
      1.1473297500245985, 1.153608768295967, 1.1597287360992941,
      1.1656893094094036, 1.1714901729367975, 1.1771310400778348,
      1.1826116528591855, 1.1879317818765598, 1.1930912262277611,
      1.1980898134400977, 1.2029273993922385, 1.2076038682305104,
      1.2121191322797089, 1.2164731319484887, 1.2206658356293323,
      1.224697239593225, 1.2285673678789981, 1.2322762721774696,
      1.2358240317104112, 1.2392107531043632, 1.2424365702594113,
      1.2455016442129492, 1.2484061629984704, 1.2511503414994989,
      1.2537344212986614, 1.2561586705219976, 1.2584233836785694,
      1.2605288814953959, 1.262475510747834, 1.264263644085414,
      1.2658936798532254, 1.267366041908921, 1.2686811794353656,
      1.2698395667490663, 1.2708417031043648, 1.2716881124935422,
      1.2723793434428363, 1.2729159688044978, 1.2732985855449019,
      1.2735278145288291, 1.273604300299958, 1.2735287108576459,
      1.273301737430085, 1.2729240942438829, 1.2723965182901475,
      1.2717197690871622, 1.2708946284396996, 1.2699219001950688,
      1.2688024099959565, 1.2675370050301398, 1.2661265537771442,
      1.264571945751922, 1.2628740912456307, 1.2610339210635604,
      1.259052386260328, 1.2569304578723806, 1.2546691266478729,
      1.2522694027740531, 1.2497323156021449, 1.2470589133698911,
      1.244250262921756, 1.2413074494269185, 1.238231576095099,
      1.2350237638903059, 1.2316851512425893, 1.2282168937578335,
      1.2246201639257357, 1.2208961508259708, 1.217046059832658,
      1.2130711123172095, 1.2089725453496027, 1.2047516113981924,
      1.2004095780280846, 1.1959477275982069, 1.1913673569570915,
      1.1866697771374914, 1.1818563130498618, 1.1769283031748181,
      1.1718870992546142, 1.1667340659837118, 1.1614705806985508,
      1.1560980330665409, 1.1506178247743772, 1.1450313692157446,
      1.139340091178481, 1.1335454265312519, 1.127648821909838,
      1.1216517344030839, 1.11555563123856, 1.10936198946806, 1.103072295652926,
      1.0966880455493384, 1.0902107437935928, 1.0836419035874381,
      1.0769830463835532, 1.0702357015712216, 1.0634014061622596,
      1.0564817044772497, 1.0494781478322057, 1.0423922942256245,
      1.0352257080260989, 1.0279799596604591, 1.0206566253025717,
      1.0132572865628093, 1.0057835301782629, 0.99823694770379112,
      0.99061913520387379, 0.9829316929454488, 0.97517622509166968,
      0.96735433939672211, 0.95946764690171815, 0.95151776163170654,
      0.94350630029391214, 0.935434881977173, 0.92730512785271013,
      0.91911866087619865, 0.91087710549127465, 0.90258208733445777,
      0.89423523294155416, 0.88583816945562366, 0.87739252433651882,
      0.86889992507204461, 0.8603619988907989, 0.85178037247673033,
      0.84315667168545194, 0.83449252126238116, 0.82578954456267162,
      0.81704936327310163, 0.80827359713583047, 0.79946386367413,
      0.79062177792015631, 0.78174895214470075, 0.77284699558907222,
      0.7639175141990493, 0.75496211036101035, 0.74598238264022765,
      0.73697992552136149, 0.72795632915124187, 0.71891317908387731,
      0.7098520560278172, 0.70077453559580072, 0.69168218805683035,
      0.682576578090593, 0.67345926454431626, 0.664331800192079,
      0.65519573149659593, 0.64605259837349549, 0.63690393395809874,
      0.62775126437479223, 0.61859610850891322, 0.609439977781265,
      0.60028437592521655, 0.5911307987664477, 0.58198073400531147,
      0.5728356610019113, 0.563697050563824, 0.55456636473651444,
      0.54544505659652087, 0.53633457004729324, 0.52723633961785432,
      0.518151790264165, 0.509082337173268, 0.50002938557025589,
      0.49099433052796665, 0.48197855677956092, 0.47298343853383751,
      0.46401033929343716, 0.455060611675844, 0.44613559723723267,
      0.43723662629915749, 0.42836501777812563, 0.41952207901799526,
      0.410709105625233, 0.40192738130709338, 0.39317817771259256,
      0.3844627542764395, 0.3757823580657646, 0.367138223629797,
      0.35853157285238246, 0.34996361480737487, 0.34143554561695616,
      0.33294854831278736, 0.32450379270004975, 0.31610243522439258,
      0.30774561884172286, 0.2994344728908751, 0.29117011296915418,
      0.28295364081075053, 0.27478614416798963, 0.26666869669547988,
      0.25860235783704882, 0.25058817271559131, 0.24262717202571013,
      0.23472037192918169, 0.22686877395329658, 0.21907336489194384,
      0.21133511670957436, 0.20365498644790281, 0.19603391613543827,
      0.18847283269976675, 0.18097264788264097, 0.17353425815777668,
      0.16615854465146049, 0.15884637306584592, 0.15159859360499209,
      0.14441604090364221, 0.13729953395865682, 0.1302498760631958,
      0.12326785474352657, 0.11635424169853412, 0.10950979274187664,
      0.10273524774676063, 0.09603133059336634, 0.08939874911888622,
      0.082838195070133833, 0.076350344058764147, 0.069935855519055623,
      0.06359537266824028, 0.057329522469375449, 0.0511389155967358,
      0.045024146403741833, 0.038985792893340851, 0.033024416690876066,
      0.027140563019457317, 0.02133476067770778, 0.015607522020014154,
      0.0099593429391332, 0.0043907028512233728, -0.0010979353167442224,
      -0.006506125137222693, -0.011833436689959238, -0.017079456567558805,
      -0.022243787878696252, -0.02732605024908882, -0.032325879820117004,
      -0.03724292924523856, -0.042076867684133108, -0.046827380794602969,
      -0.051494170722302869, -0.056076956088214, -0.060575471974000657,
      -0.06498946990515464, -0.069318717832026991, -0.073563000108718052,
      -0.077722117469857049, -0.081795887005280149, -0.085784142132657,
      -0.089686732568020608, -0.093503524294283949, -0.097234399527709875,
      -0.1008792566823732, -0.10443801033265267, -0.10791059117369581,
      -0.11129694597997349, -0.11459703756186676, -0.11781084472031736,
      -0.12093836219958837, -0.12397960063810015, -0.1269345865174214,
      -0.12980336210936122, -0.13258598542123487, -0.13528253013928707,
      -0.1378930855703108, -0.14041775658143751, -0.14285666353817242,
      -0.14520994224064085, -0.1474777438580698, -0.1496602348615603,
      -0.15175759695510044, -0.15377002700487633, -0.15569773696690223,
      -0.1575409538129407, -0.15929991945478086, -0.16097489066683759,
      -0.16256613900713424, -0.16407395073664238, -0.16549862673701229,
      -0.16684048242670793, -0.16809984767555614, -0.16927706671772258,
      -0.17037249806312904, -0.17138651440731451, -0.17231950253978889,
      -0.173171863250832, -0.17394401123682182, -0.17463637500402693,
      -0.17524939677096035, -0.1757835323692204, -0.17623925114290545,
      -0.17661703584656713, -0.17691738254171613, -0.17714080049194877,
      -0.1772878120566001, -0.17735895258305157, -0.17735477029762492,
      -0.17727582619508772, -0.17712269392682331, -0.17689595968761865,
      -0.17659622210111744, -0.17622409210394532, -0.1757801928284948,
      -0.17526515948441893, -0.17467963923880653, -0.17402429109507131,
      -0.1732997857705679, -0.172506805572914, -0.17164604427507851,
      -0.1707182069892022, -0.16972401003917867, -0.168664180832019,
      -0.16753945772796236, -0.166350589909415, -0.16509833724866058,
      -0.16378347017439246, -0.16240676953704578, -0.16096902647298955,
      -0.15947104226751746, -0.15791362821671823, -0.15629760548817781,
      -0.15462380498055972, -0.15289306718206652, -0.15110624202777015,
      -0.14926418875584455, -0.14736777576271534, -0.14541788045709164,
      -0.14341538911296114, -0.14136119672148167, -0.13925620684184009,
      -0.13710133145105324, -0.13489749079273064, -0.13264561322481114,
      -0.13034663506628502, -0.12800150044289815, -0.12561116113187148,
      -0.12317657640561364, -0.12069871287448149, -0.11817854432854404,
      -0.11561705157841098, -0.11301522229510055, -0.11037405084898469,
      -0.10769453814778959, -0.10497769147370081, -0.10222452431955362,
      -0.099436056224127017, -0.096613312606566151, -0.093757324599926972,
      -0.090869128883868111, -0.087949767516485061, -0.085000287765318983,
      -0.0820217419375377, -0.0790151872093062, -0.075981685454351841,
      -0.072922303071759439, -0.0698381108129741, -0.0667301836080443,
      -0.063599600391142264, -0.060447443925308368, -0.057274800626513682,
      -0.054082760386992446, -0.050872416397882411, -0.047644864971203182,
      -0.044401205361137987, -0.041142539584708038, -0.037869972241766248,
      -0.034584610334412708, -0.031287563085771665, -0.027979941758201621,
      -0.024662859470924108, -0.021337431017092342, -0.018004772680330329,
      -0.014666002050735021, -0.011322237840386384, -0.0079745996983561027,
      -0.0046242080252451214, -0.0012721837872834525, 0.002080351670026031,
      0.0054322768086745559, 0.0087824700853015, 0.01212981013874111,
      0.015473175977931316, 0.018811447170140647, 0.022143504029549281,
      0.025468227806093657, 0.028784500874626529, 0.032091206924301736,
      0.035387231148218193, 0.038671460433280486, 0.041942783550233259,
      0.045200091343887354, 0.048442276923485718, 0.05166823585320484,
      0.054876866342741908, 0.05806706943799414, 0.061237749211803118,
      0.064387812954700779, 0.067516171365702884, 0.070621738743046072,
      0.073703433174913291, 0.0767601767300711, 0.079790895648425425,
      0.082794520531453, 0.085769986532482467, 0.088716233546812087,
      0.091632206401633817, 0.094516855045695791, 0.097369134738757981,
      0.10018800624073575, 0.10297243600053392, 0.10572139634456204,
      0.10843386566485197, 0.11110882860680571, 0.1137452762565048,
      0.11634220632755952, 0.11889862334749166, 0.12141353884356625,
      0.1238859715281245, 0.1263149474832892, 0.12869950034510708,
      0.13103867148701248, 0.13333151020265155, 0.13557707388799081,
      0.13777442822267613, 0.13992264735066073, 0.14202081405998648,
      0.14406801996178531, 0.14606336566836431, 0.14800596097043178,
      0.1498949250133724, 0.15172938647254938, 0.15350848372764192,
      0.15523136503589985, 0.15689718870437647, 0.15850512326103217,
      0.1600543476247136, 0.161544051273959, 0.16297343441459453,
      0.16434170814610344, 0.16564809462670066, 0.16689182723711271,
      0.16807215074300447, 0.16918832145602852, 0.17023960739345198,
      0.1712252884363431, 0.17214465648625141, 0.17299701562039047,
      0.17378168224522691, 0.17449798524851556, 0.17514526614966913,
      0.17572287924847019, 0.17623019177210603, 0.17666658402041935,
      0.17703144950943378, 0.17732419511301811, 0.17754424120276552,
      0.17769102178592394, 0.17776398464146742, 0.17776259145418197,
      0.17768631794675857, 0.17753465400989835, 0.17730710383031476,
      0.17700318601666179, 0.1766224337233413, 0.17616439477212614,
      0.17562863177159, 0.17501472223430808, 0.17432225869178369,
      0.17355084880706984, 0.17270011548504724, 0.17176969698035208,
      0.17075924700286693, 0.16966843482079724, 0.16849694536127377,
      0.16724447930840572, 0.16591075319887683, 0.16449549951488471,
      0.16299846677453667, 0.16141941961957826, 0.15975813890046281,
      0.15801442175872776, 0.15618808170663404, 0.15427894870405745,
      0.15228686923254642, 0.15021170636664438, 0.14805333984225583,
      0.14581166612222557, 0.14348659845895484, 0.14107806695409272,
      0.13858601861528172, 0.13601041740988767, 0.13335124431572992,
      0.13060849736874125, 0.12778219170759875, 0.12487235961521,
      0.12187905055711605, 0.11880233121672272, 0.11564228552738809,
      0.11239901470127668, 0.10907263725504539, 0.105663289032269,
      0.10217112322257257, 0.098596310377570925, 0.094939038423384955,
      0.091199512669967, 0.087377955816975827, 0.083474607956362856,
      0.079489726571541616, 0.075423586533195849, 0.0712764800916425,
      0.067048716865792488, 0.062740623828671738, 0.058352545289448061,
      0.053884842872047325, 0.04933789549023114, 0.044712099319208928,
      0.040007867763743488, 0.035225631422711429, 0.030365838050171817,
      0.02542895251287295, 0.020415456744209751, 0.015325849694647762,
      0.010160647278564118, 0.004920382317533837, -0.00039439551995281742,
      -0.0057831197823749875, -0.011245207302609465, -0.01678005826898326,
      -0.022387056299882586, -0.0280655685219488, -0.033814945651898756,
      -0.03963452208189025, -0.045523615968491665, -0.051481529325239833,
      -0.057507548118768285, -0.0636009423685191, -0.0697609662500337,
      -0.075986858201781887, -0.08227784103559091, -0.0886331220506036,
      -0.095051893150768854, -0.10153333096590153, -0.10807659697622785,
      -0.11468083764047926, -0.12134518452744797, -0.12806875445108937,
      -0.13485064960901455, -0.14168995772454879, -0.14858575219210551,
      -0.15553709222612136, -0.16254302301329387, -0.16960257586826971,
      -0.17671476839268294, -0.18387860463754047, -0.19109307526895916,
      -0.19835715773716459, -0.20566981644885171, -0.2130300029427008,
      -0.22043665606822702, -0.22788870216777785, -0.23538505526173586,
      -0.24292461723686654, -0.25050627803778075, -0.25812891586155595,
      -0.2657913973552945, -0.27349257781687264, -0.28123130139854874,
      -0.28900640131363631, -0.29681670004606631, -0.30466100956284559,
      -0.31253813152940374, -0.32044685752773538, -0.32838596927735,
      -0.33635423885894677, -0.34435042894085283, -0.35237329300803888,
      -0.3604215755938599, -0.36849401251430669, -0.37658933110483889,
      -0.38470625045970686, -0.39284348167372019, -0.40099972808643164,
      -0.40917368552866162, -0.41736404257140647, -0.42556948077689088,
      -0.43378867495198004, -0.44202029340362997, -0.45026299819655224,
      -0.45851544541290384, -0.46677628541398697, -0.4750441631039341,
      -0.48331771819526964, -0.49159558547639837, -0.49987639508077575,
      -0.50815877275795607, -0.516441340146226, -0.52472271504694978,
      -0.53300151170042065, -0.54127634106327993, -0.54954581108738765,
      -0.5578085270000559, -0.56606309158569523, -0.57430810546864419,
      -0.58254216739732723, -0.59076387452946022, -0.59897182271844307,
      -0.60716460680073137, -0.61534082088419229, -0.62349905863737742,
      -0.63163791357961152, -0.63975597937189177 } ;

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
  DATA_COLLECTION_M->Sizes.checksums[0] = (3187002445U);
  DATA_COLLECTION_M->Sizes.checksums[1] = (388937937U);
  DATA_COLLECTION_M->Sizes.checksums[2] = (2328183639U);
  DATA_COLLECTION_M->Sizes.checksums[3] = (1541979293U);

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
