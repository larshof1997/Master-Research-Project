/*
 * DATA_COLLECTION.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "DATA_COLLECTION".
 *
 * Model version              : 1.118
 * Simulink Coder version : 9.0 (R2018b) 24-May-2018
 * C source code generated on : Wed Mar  4 16:31:09 2026
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
    } else if (t >= pTimeValues[2599]) {
      currTimeIndex = 2598;
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
              pDataValues += 2600;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&DATA_COLLECTION_B.FromWorkspace3[0])[elIdx] =
                pDataValues[currTimeIndex + 1];
              pDataValues += 2600;
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
            pDataValues += 2600;
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
    } else if (t >= pTimeValues[2599]) {
      currTimeIndex = 2598;
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
              pDataValues += 2600;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&rtb_Product1[0])[elIdx] = pDataValues[currTimeIndex + 1];
              pDataValues += 2600;
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
            pDataValues += 2600;
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
    } else if (t >= pTimeValues[2599]) {
      currTimeIndex = 2598;
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
              pDataValues += 2600;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&DATA_COLLECTION_B.FromWorkspace1[0])[elIdx] =
                pDataValues[currTimeIndex + 1];
              pDataValues += 2600;
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
            pDataValues += 2600;
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
      25.97, 25.98, 25.990000000000002 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, -1.3877787807814457E-17, 0.011957698311787439, 0.023928791614416384,
      0.0359118002006918, 0.047905230622349304, 0.059907575924623327,
      0.071917315886291022, 0.083932917265154713, 0.095952834048923075,
      0.10797550771144369, 0.11999936747424655, 0.1320228305733506,
      0.14404430253128242, 0.15606217743425482, 0.16807483821445773,
      0.18008065693740005, 0.19207799509424922, 0.20406520389910629,
      0.21604062459115947, 0.22800258874164941, 0.23994941856558244,
      0.25187942723812462, 0.26379091921560976, 0.27568219056108723,
      0.28755152927433919, 0.29939721562629218, 0.31121752249774681,
      0.32301071572234891, 0.3347750544337163, 0.3465087914166487,
      0.3582101734623292, 0.36987744172743742, 0.38150883209708075,
      0.39310257555146622, 0.40465689853620868, 0.41617002333619513,
      0.42764016845290553, 0.43906554898509448, 0.45044437701274159,
      0.46177486198416734, 0.47305521110621651, 0.48428362973740929,
      0.49545832178395394, 0.50657749009852093, 0.5176393368816693,
      0.52864206408581793, 0.53958387382166062, 0.55046296876690437,
      0.56127755257722711, 0.57202583029934306, 0.582706008786059,
      0.59331629711320721, 0.60385490699834321, 0.61432005322108829,
      0.62470995404499785, 0.63502283164084128, 0.64525691251117046,
      0.65541042791605475, 0.66548161429986519, 0.675468713718983,
      0.68536997427030533, 0.69518365052043141, 0.70490800393540032,
      0.71454130331085153, 0.72408182520248865, 0.73352785435671586,
      0.7428776841413155, 0.7521296169760483, 0.76128196476303833,
      0.77033304931681956, 0.77928120279390978, 0.78812476812178767,
      0.79686209942713693, 0.80549156246323061, 0.81401153503632473,
      0.82242040743092715, 0.83071658283381433, 0.83889847775666215,
      0.84696452245715981, 0.854913161358477, 0.86274285346695045,
      0.87045207278785952, 0.87803930873916092, 0.88550306656304811,
      0.89284186773520968, 0.900054250371647, 0.90713876963293616,
      0.91409399812578207, 0.92091852630175819, 0.927610962853084,
      0.93416993510532376, 0.940594089406871, 0.94688209151509217,
      0.95303262697900626, 0.95904440151836712, 0.96491614139902893,
      0.97064659380446638, 0.97623452720332149, 0.98167873171286346,
      0.98697801945822794, 0.99213122492732153, 0.99713720532126393,
      1.0019948409002541, 1.0067030353247401, 1.0112607159917684,
      1.0156668343664059, 1.0199203663081098, 1.0240203123919396,
      1.0279656982244896, 1.0317555747544358, 1.0353890185775851,
      1.0388651322363165, 1.0421830445133078, 1.0453419107194415,
      1.0483409129757844, 1.0511792604895362, 1.0538561898238497,
      1.0563709651614179, 1.0587228785617309, 1.0609112502119071,
      1.0629354286710033, 1.0647947911077054, 1.0664887435313188,
      1.0680167210159563, 1.069378187917845, 1.0705726380856613,
      1.0715995950638117, 1.0724586122885755, 1.0731492732770334,
      1.0736711918086983, 1.0740240120997764, 1.0742074089699816,
      1.074221088001837, 1.0740647856923833, 1.0737382695972386,
      1.0732413384669364, 1.0725738223754797, 1.0717355828410533,
      1.0707265129388335, 1.0695465374058386, 1.0681956127377679,
      1.0666737272777749, 1.0649809012971314, 1.0631171870677247,
      1.0610826689263577, 1.0588774633307978, 1.0565017189075427,
      1.0539556164912585, 1.0512393691558695, 1.0483532222372463,
      1.0452974533474884, 1.042072372380749, 1.0386783215105992,
      1.0351156751788935, 1.031384840076129, 1.0274862551132733,
      1.023420391385055, 1.0191877521246977, 1.0147888726500942,
      1.010224320301413, 1.0054946943701342, 1.0006006260195126,
      0.99554277819647341, 0.99032184553494074, 0.9849385542506085,
      0.97939366202716527, 0.97368795789398266, 0.9678222620952851,
      0.9617974259508173, 0.95561433170802812, 0.94927389238580462,
      0.94277705160976566, 0.93612478343915972, 0.92931809218538741,
      0.92235801222218938, 0.91524560778753383, 0.90798197277724135,
      0.90056823053039481, 0.89300553360657176, 0.88529506355495391,
      0.87743803067535642, 0.86943567377123876, 0.86128925989474137,
      0.85300008408381656, 0.84456946909150687, 0.8359987651074372,
      0.82728934947158561, 0.818442626380399, 0.80946002658532934,
      0.80034300708385686, 0.79109305080308079, 0.78171166627595357,
      0.77220038731023966, 0.76256077265028122, 0.75279440563165634,
      0.74290289382881847, 0.732887868695804, 0.72275098520010528,
      0.71249392144979617, 0.70211837831401813, 0.6916260790369122,
      0.68101876884511237, 0.67029821454889016, 0.65946620413706925,
      0.64852454636580725, 0.63747507034136064, 0.62631962509694183,
      0.6150600791637868, 0.60369832013654046, 0.59223625423308979,
      0.58067580584895184, 0.56901891710635089, 0.557267547398095,
      0.54542367292639349, 0.53348928623672187, 0.52146639574688991,
      0.509357025271411, 0.49716321354133952, 0.48488701371968057,
      0.4725304929125283, 0.46009573167605472, 0.44758482351950357,
      0.43499987440431104, 0.42234300223951216, 0.40961633637356093,
      0.39682201708272041, 0.38396219505615775, 0.37103903087790213,
      0.3580546945057983, 0.34501136474762356, 0.33191122873449858,
      0.31875648139176121, 0.30554932490743963, 0.29229196819848946,
      0.27898662637494509, 0.26563552020213488, 0.25224087556112784,
      0.23880492290755093, 0.22532989672895562, 0.21181803500086724,
      0.19827157864170311, 0.18469277096668421, 0.17108385714094115,
      0.15744708363193052, 0.14378469766136245, 0.13009894665676466,
      0.1163920777028766, 0.10266633699300197, 0.0889239692805148,
      0.075167217330647962, 0.061398321372755846, 0.047619518553185421,
      0.033833042388942233, 0.020041122222291638, 0.0062459826764747067,
      -0.0075501568873163546, -0.0213450829115246, -0.035136588182233877,
      -0.048922472367418847, -0.062700542553282779, -0.076468613778532521,
      -0.090224509566414535, -0.10396606245437162, -0.11769111452114327,
      -0.13139751791117427, -0.14508313535614839, -0.15874584069351932,
      -0.17238351938185564, -0.18599406901287091, -0.19957539981996592,
      -0.21312543518314012, -0.22664211213011753, -0.24012338183354118,
      -0.253567210104076, -0.266971577879286, -0.2803344817081227,
      -0.29365393423089531, -0.3069279646545654, -0.32015461922322708,
      -0.33333196168363072, -0.34645807374561383, -0.35953105553728831,
      -0.37254902605486273, -0.38551012360694903, -0.39841250625322461,
      -0.41125435223732565, -0.42403386041382241, -0.43674925066916714,
      -0.44939876433646891, -0.46198066460398668, -0.47449323691720108,
      -0.48693478937435808, -0.49930365311534919, -0.51159818270382551,
      -0.52381675650241621, -0.535957777040949, -0.5480196713775527,
      -0.56000089145253706, -0.57189991443493771, -0.58371524306162981,
      -0.59544540596889728, -0.60708895801636364, -0.61864448060318222,
      -0.630110581976398, -0.64148589753137186, -0.65276909010419626,
      -0.66395885025599277, -0.67505389654902759, -0.68605297581453639,
      -0.69695486341220536, -0.7077583634812008, -0.71846230918269649,
      -0.72906556293381131, -0.73956701663288749, -0.74996559187605094,
      -0.76026024016497329, -0.77044994310578818, -0.78053371259909177,
      -0.79051059102097709, -0.80037965139503786, -0.81013999755531085,
      -0.81979076430007658, -0.82933111753650823, -0.83876025441609559,
      -0.8480774034608255, -0.85728182468006386, -0.86637280967812558,
      -0.87534968175247652, -0.88421179598256361, -0.892958539309225,
      -0.90158933060468172, -0.910103620733062, -0.91850089260147438,
      -0.9267806612015852, -0.934942473641712, -0.94298590916941749,
      -0.95091057918459032, -0.95871612724303013, -0.96640222905051776,
      -0.97396859244739276, -0.981414957383627, -0.98874109588442682,
      -0.99594681200635, -1.0030319417839817, -1.0099963531671641,
      -1.01683994594882, -1.0235626516833818, -1.0301644335958657,
      -1.0366452864816114, -1.0430052365967288, -1.0492443415392836,
      -1.0553626901212656, -1.0613604022313778, -1.0672376286886966,
      -1.0729945510872465, -1.0786313816315463, -1.0841483629631727,
      -1.089545767978408, -1.0948238996370243, -1.0999830907622692,
      -1.1050237038321182, -1.1099461307618612, -1.1147507926780982,
      -1.1194381396842061, -1.1240086506173703, -1.1284628327972408,
      -1.132801221766311, -1.1370243810220926, -1.141132901741176,
      -1.145127402495266, -1.1490085289592884, -1.152776953611651,
      -1.1564333754267708, -1.159978519559947, -1.1634131370247067,
      -1.1667380043627023, -1.1699539233062779, -1.1730617204338236,
      -1.1760622468180053, -1.1789563776670016, -1.1817450119588586,
      -1.1844290720690771, -1.1870095033915495, -1.1894872739529816,
      -1.1918633740208993, -1.1941388157053963, -1.196314632554718,
      -1.1983918791448389, -1.2003716306631491, -1.2022549824863842,
      -1.2040430497529429, -1.2057369669297204, -1.2073378873735967,
      -1.2088469828877277, -1.2102654432727677, -1.2115944758731843,
      -1.2128353051187928, -1.2139891720616669, -1.2150573339085766,
      -1.2160410635490861, -1.2169416490794869, -1.2177603933226919,
      -1.2184986133442677, -1.2191576399647379, -1.21973881726833,
      -1.2202435021083113, -1.2206730636090788, -1.2210288826651543,
      -1.2213123514372515, -1.2215248728455697, -1.2216678600604811,
      -1.2217427359907655, -1.2217509327695637, -1.2216938912382076,
      -1.2215730604280948, -1.2213898970407633, -1.22114586492635,
      -1.2208424345605766, -1.2204810825204393, -1.2200632909587761,
      -1.219590547077863, -1.219064342602219, -1.2184861732507715,
      -1.2178575382085757, -1.2171799395982215, -1.2164548819511269,
      -1.2156838716788563, -1.2148684165446602, -1.2140100251353771,
      -1.2131102063338848, -1.2121704687922472, -1.2111923204057484,
      -1.2101772677879565, -1.2091268157469968, -1.2080424667631919,
      -1.2069257204682426, -1.2057780731260999, -1.2046010171157044,
      -1.2033960404157538, -1.2021646260916488, -1.2009082517847962,
      -1.1996283892044148, -1.1983265036220165, -1.1970040533687081,
      -1.1956624893354826, -1.1943032544766519, -1.192927783316573,
      -1.1915375014598333, -1.1901338251050353, -1.1887181605623378,
      -1.187291903774913, -1.1858564398444513, -1.18441314256088,
      -1.1829633739364269, -1.1815084837441918, -1.180049809061348,
      -1.1785886738171334, -1.1771263883457685, -1.1756642489444318,
      -1.1742035374364368, -1.1727455207397475, -1.1712914504409637,
      -1.1698425623749016, -1.1684000762099156, -1.1669651950390705,
      -1.1655391049773058, -1.16412297476471, -1.1627179553760219,
      -1.1613251796364912, -1.1599457618442066, -1.158580797399009,
      -1.1572313624381079, -1.1558985134785087, -1.154583287066361,
      -1.1532866994333357, -1.1520097461601324, -1.1507534018472285,
      -1.1495186197929574, -1.1483063316790216, -1.1471174472635375,
      -1.1459528540816974, -1.1448134171541411, -1.143699978703137,
      -1.1426133578766315, -1.1415543504802776, -1.1405237287175096,
      -1.1395222409377357, -1.1385506113927322, -1.1376095400013144,
      -1.1366997021223406, -1.1358217483361284, -1.1349763042343408,
      -1.1341639702184048, -1.1333853213065221, -1.1326409069493257,
      -1.1319312508542392, -1.13125685081858, -1.1306181785714684,
      -1.1300156796245688, -1.1294497731317248, -1.1289208517575071,
      -1.1284292815547254, -1.1279754018509285, -1.1275595251439274,
      -1.1271819370063652, -1.1268428959993615, -1.1265426335952491,
      -1.1262813541094259, -1.1260592346413323, -1.1258764250245712,
      -1.1257330477861802, -1.1256291981150572, -1.1255649438395523,
      -1.12554032541422, -1.125555355915731, -1.1256100210479409,
      -1.1257042791561116, -1.1258380612502579, -1.1260112710376333,
      -1.1262237849643131, -1.1264754522658658, -1.1267660950271015,
      -1.1270955082508438, -1.1274634599357325, -1.1278696911629946,
      -1.1283139161921749, -1.1287958225657697, -1.1293150712227453,
      -1.1298712966208744, -1.1304641068678687, -1.1310930838612503,
      -1.1317577834369055, -1.1324577355262815, -1.1331924443221593,
      -1.1339613884529531, -1.1347640211654633, -1.1355997705160359,
      -1.1364680395700477, -1.1373682066096549, -1.1382996253497333,
      -1.1392616251619385, -1.140253511306802, -1.1412745651737939,
      -1.1423240445292633, -1.1434011837721794, -1.144505194197579,
      -1.1456352642676402, -1.1467905598902874, -1.1479702247052312,
      -1.1491733803773574, -1.1503991268973541, -1.1516465428894931,
      -1.1529146859264476, -1.1542025928510526, -1.1555092801048994,
      -1.156833744063654, -1.1581749613789887, -1.159531889327019,
      -1.160903466163129, -1.1622886114830635, -1.1636862265901811,
      -1.1650951948687378, -1.1665143821630828, -1.1679426371626438,
      -1.1693787917925806, -1.1708216616099691, -1.1722700462053994,
      -1.1737227296098494, -1.1751784807067103, -1.1766360536488256,
      -1.1780941882804048, -1.179551610563691, -1.181007033010226,
      -1.1824591551165959, -1.1839066638044913, -1.1853482338649688,
      -1.1867825284067528, -1.1882081993084375, -1.1896238876744558,
      -1.1910282242946522, -1.1924198301073285, -1.1937973166656071,
      -1.1951592866069674, -1.1965043341258017, -1.1978310454488477,
      -1.1991379993133409, -1.2004237674477387, -1.2016869150548666,
      -1.2029260012973255, -1.2041395797850192, -1.2053261990646396,
      -1.2064844031109598, -1.2076127318197776, -1.2087097215023594,
      -1.2097739053812295, -1.2108038140871384, -1.2117979761570739,
      -1.212754918533147, -1.2136731670621914, -1.2145512469959427,
      -1.215387683491616, -1.2161810021127466, -1.2169297293301244,
      -1.2176323930226784, -1.218287522978146, -1.2188936513933795,
      -1.2194493133741295, -1.2199530474341607, -1.2204033959935316,
      -1.2207989058758988, -1.2211381288046865, -1.2214196218979689,
      -1.2216419481619143, -1.2218036769826441, -1.2219033846163476,
      -1.2219396546775116, -1.2219110786251144, -1.2218162562466264,
      -1.2216537961396923, -1.2214223161913171, -1.2211204440544459,
      -1.2207468176217606, -1.2203000854965769, -1.2197789074606824,
      -1.21918195493898, -1.2185079114608006, -1.2177554731177427,
      -1.2169233490179017, -1.2160102617363528, -1.2150149477617551,
      -1.213936157938944, -1.2127726579073763, -1.211523228535299,
      -1.2101866663495164, -1.2087617839606275, -1.2072474104836022,
      -1.2056423919535768, -1.2039455917367519, -1.2021558909362575,
      -1.2002721887928836, -1.198293403080543, -1.1962184704963656,
      -1.1940463470452969, -1.1917760084191018, -1.18940645036965,
      -1.1869366890763919, -1.1843657615079035, -1.1816927257774046,
      -1.1789166614921429, -1.1760366700965612, -1.173051875209115,
      -1.1699614229526842, -1.1667644822784611, -1.1634602452832259,
      -1.1600479275199291, -1.1565267683014855, -1.1528960309977012,
      -1.1491550033252436, -1.1453029976305797, -1.1413393511658034,
      -1.13726342635728, -1.1330746110670202, -1.1287723188467307,
      -1.124355989184463, -1.1198250877437927, -1.1151791065954721,
      -1.1104175644414835, -1.1055400068314511, -1.1005460063713379,
      -1.0954351629243779, -1.0902071038042029, -1.0848614839600992,
      -1.0793979861543535, -1.073816321131646, -1.0681162277804512,
      -1.0622974732863939, -1.056359853277538, -1.0503031919615664,
      -1.0441273422548254, -1.0378321859031963, -1.0314176335947725,
      -1.0248836250643212, -1.0182301291895024, -1.0114571440788276,
      -1.0045646971513387, -0.99755284520800447, -0.99042167449481089,
      -0.98317130075753589, -0.97580186928821466, -0.96831355496327665,
      -0.96070656227336948, -0.95298112534484847, -0.94513750795295726,
      -0.93717600352669517, -0.92909693514538, -0.92090065552692046,
      -0.9125875470078052, -0.90415802151483793, -0.89561252052862272,
      -0.88695151503882752, -0.87817550549124768, -0.86928502172670052,
      -0.860280622911766, -0.85116289746142271, -0.84193246295359214,
      -0.83258996603564517, -0.8231360823228927, -0.81357151628911306,
      -0.80389700114914908, -0.79411329873362557, -0.78422119935583068,
      -0.77422152167081371, -0.7641151125267428, -0.75390284680858766,
      -0.74358562727417321, -0.7331643843826694, -0.72264007611556691,
      -0.71201368779021579, -0.70128623186597627, -0.69045874774305527,
      -0.67953230155410571, -0.6685079859486307, -0.65738691987030218,
      -0.64617024832723657, -0.63485914215532779, -0.623454797774691,
      -0.61195843693932162, -0.60037130648003256, -0.58869467804077158,
      -0.57692984780837275, -0.56507813623586944, -0.5531408877594266,
      -0.54111947050900244, -0.52901527601280318, -0.51682971889566809,
      -0.50456423657144023, -0.49222028892944153, -0.47979935801513629,
      -0.46730294770510089, -0.45473258337638262, -0.44208981157036464,
      -0.42937619965122414, -0.41659333545910915, -0.40374282695812508,
      -0.390826301879244, -0.37784540735825339, -0.36480180956882929,
      -0.3516971933508824, -0.33853326183425381, -0.32531173605790487,
      -0.31203435458468187, -0.29870287311180693, -0.28531906407718266,
      -0.27188471626164445, -0.25840163438727348, -0.24487163871188444,
      -0.23129656461981674, -0.2176782622091501, -0.20401859587544774,
      -0.19031944389217531, -0.17658269798789869, -0.16281026292039508,
      -0.1490040560477906, -0.13516600689685782, -0.12129805672859348,
      -0.10740215810120605, -0.093480274430626287, -0.079534379548682227,
      -0.065566457259055522, -0.051578500891149237, -0.037572512851988836,
      -0.023550504176288296, -0.0095144940748055351, 0.0045334905188825977,
      0.018591415403060581, 0.032657239563891577, 0.046728915632624754,
      0.060804390343882325, 0.074881604994893131, 0.08895849590554876,
      0.1030329948791497, 0.11710302966372163, 0.13116652441376642,
      0.14522140015234158, 0.15926557523331539, 0.17329696580369086,
      0.18731348626586702, 0.20131304973972575, 0.21529356852438949,
      0.22925295455956402, 0.24318911988631003, 0.257099977107155,
      0.27098343984538537, 0.28483742320343247, 0.29865984422020214,
      0.31244862232726212, 0.32620167980372833, 0.33991694222977109,
      0.35359233893858932, 0.36722580346675765, 0.38081527400283577,
      0.3943586938340975, 0.40785401179129233, 0.42129918269131972,
      0.43469216777769348, 0.44803093515869497, 0.46131346024311731,
      0.47453772617346046, 0.48770172425649994, 0.50080345439110407,
      0.51384092549320726, 0.52681215591782582, 0.53971517387802,
      0.55254801786068741, 0.56530873703912055, 0.57799539168218272,
      0.590606053560045, 0.60313880634636641, 0.61559174601682776,
      0.627962981243932, 0.64025063378796587, 0.6524528388840467,
      0.664567745625152, 0.67659351734106055, 0.6885283319731007,
      0.70037038244463223, 0.7121178770271791, 0.72376903970212736,
      0.7353221105179093, 0.74677534594260253, 0.75812701921184567,
      0.76937542067204112, 0.78051885811870925, 0.79155565712997755,
      0.80248416139510159, 0.81330273303796774, 0.82400975293550016,
      0.83460362103091212, 0.84508275664172927, 0.85544559876255477,
      0.8656906063624662, 0.87581625867703583, 0.88582105549487944,
      0.89570351743870968, 0.90546218624082087, 0.91509562501296682,
      0.9246024185105749, 0.933981173391246, 0.94323051846752248,
      0.95234910495383518, 0.96133560670762985, 0.97018872046460392,
      0.97890716606803962, 0.98748968669217285, 0.995935049059591,
      1.0042420436525925, 1.0124094849185203, 1.0204362114690015,
      1.0283210862730865, 1.0360629968442592, 1.0436608554212985,
      1.0511135991429541, 1.0584201902164445, 1.0655796160797191,
      1.0725908895575276, 1.0794530490112113, 1.0861651584822645,
      1.0927263078296208, 1.0991356128606657, 1.1053922154559743,
      1.1114952836877625, 1.117444011932035, 1.1232376209744688,
      1.1288753581099822, 1.1343564972360265, 1.1396803389395913,
      1.1448462105779253, 1.1498534663529922, 1.1547014873796539,
      1.159389681747607, 1.1639174845770679, 1.1682843580682443,
      1.1724897915445804, 1.1765333014898152, 1.1804144315788552,
      1.1841327527025034, 1.187687862986039, 1.191079387801695,
      1.1943069797750443, 1.1973703187853288, 1.2002691119597557,
      1.203003093661787, 1.2055720254734645, 1.2079756961717885,
      1.2102139216991943, 1.2122865451281606, 1.2141934366199811,
      1.2159344933777427, 1.2175096395935454, 1.2189188263900137,
      1.2201620317561241, 1.2212392604774174, 1.2221505440606151,
      1.2228959406527018, 1.2234755349545161, 1.2238894381288989,
      1.2241377877034465, 1.2242207474679261, 1.2241385073663944,
      1.2238912833840829, 1.223479317429103, 1.2229028772090158,
      1.2221622561023371, 1.2212577730250262, 1.2201897722920159,
      1.2189586234738545, 1.2175647212485035, 1.2160084852483604,
      1.21429035990258, 1.2124108142747327, 1.2103703418958829,
      1.2081694605931517, 1.205808712313813, 1.2032886629450092,
      1.2006099021291454, 1.19777304307502, 1.1947787223647819,
      1.1916275997567634, 1.1883203579842674, 1.1848577025503806,
      1.1812403615188831, 1.1774690853013143, 1.1735446464402932,
      1.1694678393891367, 1.1652394802878692, 1.1608604067356905,
      1.1563314775599702, 1.151653572581858, 1.146827592378568,
      1.1418544580424221, 1.1367351109367307, 1.1314705124485762,
      1.1260616437385822, 1.120509505487749, 1.1148151176414189,
      1.1089795191504679, 1.1030037677097808, 1.0968889394940931,
      1.090636128891294, 1.08424644823324, 1.0777210275241751,
      1.0710610141668362, 1.0642675726863116, 1.0573418844517295,
      1.0502851473958743, 1.0430985757327815, 1.0357833996734047,
      1.0283408651394339, 1.020772233475328, 1.0130787811586623,
      1.0052617995088422, 0.99732259439427662, 0.989262485938091,
      0.98108280822244109, 0.97278490899151371, 0.96437014935329435,
      0.9558399034801689, 0.947195558308443, 0.93843851323684713,
      0.92957017982410561, 0.9205919814856468, 0.91150535318953174,
      0.90231174115165358, 0.89301260253031634, 0.88360940512023289,
      0.8741036270460425, 0.86449675645539736, 0.8547902912116947,
      0.84498573858655035, 0.83508461495203978, 0.82508844547282445,
      0.8149987637981867, 0.80481711175408233, 0.79454503903526086,
      0.784184102897513, 0.773735867850131, 0.76320190534864008,
      0.75258379348785764, 0.7418831166953691, 0.73110146542545573,
      0.72024043585356368, 0.70930162957135934, 0.69828665328245065,
      0.68719711849881593, 0.67603464123802159, 0.66480084172127329,
      0.65349734407237381, 0.64212577601762766, 0.63068776858677444,
      0.61918495581498845, 0.60761897444601409, 0.59599146363648037,
      0.58430406466146578, 0.57255842062134765, 0.56075617615000561,
      0.54889897712443536, 0.53698847037579189, 0.52502630340195477,
      0.513014124081644, 0.50095358039013294, 0.48884632011661167,
      0.47669399058325707, 0.46449823836603066, 0.45226070901729132,
      0.43998304679021244, 0.42766689436510014, 0.415313892577626,
      0.40292568014902058, 0.39050389341827341, 0.37805016607638037,
      0.36556612890266943, 0.35305340950325814, 0.34051363205165985,
      0.32794841703159433, 0.31535938098203264, 0.30274813624450564,
      0.29011629071271022, 0.27746544758446229, 0.26479720511600568,
      0.25211315637871912, 0.23941488901826716, 0.22670398501618141,
      0.21398202045395612, 0.20125056527964211, 0.18851118307698425,
      0.17576543083713153, 0.16301485873293253, 0.15026100989584845,
      0.13750542019551562, 0.12474961802195192, 0.11199512407045985,
      0.099243451129235355, 0.086496103869689991, 0.073754578639528418,
      0.061020363258580124, 0.048294936817406306, 0.035579769478720949,
      0.022876322281595373, 0.010186046948508446, -0.0024896143047656825,
      -0.015149228956425294, -0.027791374363032282, -0.040414637941033935,
      -0.053017617345394188, -0.065598920645324188, -0.07815716649710297,
      -0.090690984313994374, -0.1031990144332235, -0.11567990828002966,
      -0.12813232852878431, -0.14055494926115725, -0.15294645612134308,
      -0.16530554646833057, -0.17763092952520665, -0.18992132652552896,
      -0.20217547085670348, -0.21439210820042098, -0.22656999667012359,
      -0.23870790694550403, -0.25080462240404611, -0.26285893924960341,
      -0.27486966663800733, -0.286835626799732, -0.29875565515958824,
      -0.31062860045347335, -0.3224533248421716, -0.33422870402220761,
      -0.3459536273337625, -0.35762699786565871, -0.36924773255741489,
      -0.380814762298375, -0.39232703202394048, -0.40378350080887859,
      -0.41518314195774436, -0.42652494309240624, -0.43780790623669841,
      -0.44903104789819942, -0.46019339914714924, -0.47129400569251634,
      -0.48233192795523222, -0.4933062411385864, -0.50421603529581482,
      -0.5150604153948779, -0.52583850138044763, -0.53654942823312035,
      -0.54719234602585476, -0.55776641997765652, -0.5682708305045403,
      -0.57870477326774394, -0.58906745921924764, -0.59935811464458644,
      -0.60957598120299084, -0.61972031596485433, -0.62979039144655369,
      -0.63978549564263287, -0.649704932055369, -0.65954801972173482,
      -0.669314093237774, -0.67900250278041108, -0.68861261412670061,
      -0.69814380867055037, -0.70759548343691658, -0.71696705109350412,
      -0.72625793995997756, -0.73546759401471706, -0.74459547289911221,
      -0.75364105191943587, -0.76260382204630117, -0.77148328991172654,
      -0.78027897780382716, -0.788990423659146, -0.79761718105264467,
      -0.80615881918538612, -0.81461492286990211, -0.82298509251329344,
      -0.83126894409804708, -0.83946610916062769, -0.847576234767839,
      -0.85559898349097208, -0.86353403337777779, -0.87138107792225339,
      -0.87913982603230545, -0.88681000199526339, -0.89439134544128784,
      -0.90188361130468853, -0.90928656978317213, -0.9166000062950338,
      -0.92382372143431579, -0.930957530923948, -0.93800126556690533,
      -0.94495477119537052, -0.95181790861795512, -0.95859055356497114,
      -0.96527259663179421, -0.97186394322031433, -0.97836451347851339,
      -0.98477424223817578, -0.99109307895076315, -0.99732098762145416,
      -1.0034579467413818, -1.0095039492180846, -1.0154590023041905,
      -1.0213231275243435, -1.0270963606004033, -1.0327787513749336,
      -1.0383703637329862, -1.0438712755222193, -1.0492815784713496,
      -1.0546013781069641, -1.0598307936687101, -1.064969958022884,
      -1.0700190175744226, -1.0749781321773475, -1.07984747504362,
      -1.0846272326505051, -1.0893176046463904, -1.0939188037551149,
      -1.098431055678821, -1.1028545989993297, -1.1071896850780842,
      -1.1114365779546556, -1.1155955542438298, -1.1196669030313169,
      -1.1236509257680607, -1.1275479361632041, -1.1313582600756955,
      -1.1350822354045775, -1.1387202119779587, -1.1422725514406888,
      -1.1457396271407612, -1.1491218240144478, -1.1524195384701916,
      -1.1556331782712663, -1.1587631624172303, -1.1618099210241737,
      -1.1647738952037927, -1.1676555369412986, -1.1704553089721732,
      -1.1731736846577989, -1.1758111478599704, -1.1783681928143026,
      -1.1808453240025611, -1.183243056023918, -1.1855619134651616,
      -1.1878024307698642, -1.1899651521065375, -1.1920506312357702,
      -1.1940594313763937, -1.1959921250706647, -1.1978492940484904,
      -1.1996315290907227, -1.2013394298915148, -1.2029736049197786,
      -1.2045346712797489, -1.206023254570662, -1.2074399887455842,
      -1.2087855159693892, -1.2100604864759097, -1.2112655584242731,
      -1.2124013977544446, -1.2134686780419897, -1.2144680803520684,
      -1.215400293092689, -1.2162660118672257, -1.2170659393262213,
      -1.2178007850184966, -1.2184712652415735, -1.2190781028914333,
      -1.2196220273116347, -1.2201037741417882, -1.2205240851654269,
      -1.2208837081572748, -1.22118339672994, -1.2214239101800346,
      -1.2216060133337683, -1.2217304763919903, -1.2217980747747428,
      -1.2218095889653091, -1.2217658043537902, -1.2216675110802295,
      -1.2215155038772887, -1.2213105819125152, -1.221053548630201,
      -1.2207452115928576, -1.2203863823223313, -1.219977876140568,
      -1.2195205120100521, -1.2190151123739401, -1.2184625029959035,
      -1.2178635127997035, -1.2172189737085157, -1.2165297204840257,
      -1.2157965905653152, -1.2150204239075582, -1.2142020628205481,
      -1.2133423518070749, -1.2124421374011756, -1.2115022680062764,
      -1.2105235937332484, -1.2095069662383975, -1.2084532385614115,
      -1.2073632649632822, -1.2062379007642299, -1.2050780021816472,
      -1.203884426168085, -1.2026580302493035, -1.2013996723624158,
      -1.2001102106941335, -1.1987905035191517, -1.1974414090386896,
      -1.1960637852192053, -1.1946584896313195, -1.1932263792889612,
      -1.1917683104887611, -1.1902851386497262, -1.1887777181532031,
      -1.1872469021831689, -1.1856935425668649, -1.1841184896158026,
      -1.1825225919671647, -1.1809066964256285, -1.1792716478056269,
      -1.1776182887740898, -1.1759474596936785, -1.1742599984665338,
      -1.172556740378583, -1.1708385179444103, -1.1691061607527335,
      -1.1673604953124987, -1.1656023448996324, -1.1638325294044636,
      -1.1620518651798621, -1.1602611648900951, -1.1584612373604466,
      -1.1566528874276225, -1.1548369157909679, -1.153014118864514,
      -1.1511852886299041, -1.1493512124902037, -1.1475126731246297,
      -1.1456704483442346, -1.1438253109485605, -1.1419780285832966,
      -1.1401293635989702, -1.1382800729106914, -1.1364309078589854,
      -1.1345826140717443, -1.1327359313273122, -1.1308915934187418,
      -1.129050328019253, -1.1272128565489139, -1.1253798940425719,
      -1.1235521490190732, -1.121730323351785, -1.1199151121404554,
      -1.1181072035844428, -1.1163072788573352, -1.1145160119829842,
      -1.1127340697130017, -1.1109621114057113, -1.1092007889066275,
      -1.1074507464304448, -1.1057126204445971, -1.1039870395544011,
      -1.1022746243898065, -1.1005759874937975, -1.0988917332124482,
      -1.097222457586682, -1.095568748245749, -1.0939311843024482,
      -1.0923103362501223, -1.0907067658614618, -1.0891210260891206,
      -1.0875536609681937, -1.0860052055205709, -1.0844761856611875,
      -1.0829671181062088, -1.081478510283167, -1.0800108602430691,
      -1.0785646565745173, -1.0771403783198481, -1.0757384948933224,
      -1.0743594660013913, -1.0730037415650573, -1.0716717616443585,
      -1.0703639563649923, -1.0690807458471037, -1.067822540136264,
      -1.0665897391366579, -1.0653827325464977, -1.0642018997956921,
      -1.0630476099857826, -1.0619202218321766, -1.0608200836086872,
      -1.0597475330944104, -1.0587028975229438, -1.0576864935339791,
      -1.0566986271272811, -1.0557395936190679, -1.0548096776008142,
      -1.0539091529004905, -1.0530382825462583, -1.0521973187326359,
      -1.0513865027891414, -1.0506060651514479, -1.0498562253350376,
      -1.0491371919113959, -1.0484491624867378, -1.0477923236832876,
      -1.0471668511231262, -1.046572909414617, -1.0460106521414041,
      -1.0454802218540273, -1.0449817500641305, -1.0445153572412893,
      -1.0440811528124598, -1.0436792351640662, -1.0433096916467186,
      -1.0429725985825837, -1.0426680212753994, -1.0423960140231505,
      -1.042156620133408, -1.0419498719413232, -1.0417757908302991,
      -1.0416343872553295, -1.0415256607690091, -1.0414496000502187,
      -1.0414061829354817, -1.0413953764529991, -1.0414171368593521,
      -1.0414714096788766, -1.0415581297457119, -1.0416772212485053,
      -1.0418285977777866, -1.0420121623759953, -1.0422278075901583,
      -1.0424754155272191, -1.0427548579119976, -1.0430659961477886,
      -1.0434086813795775, -1.0437827545598706, -1.0441880465171336,
      -1.0446243780268163, -1.0450915598849659, -1.0455893929844027,
      -1.0461176683934605, -1.0466761674372613, -1.047264661781528,
      -1.0478829135189009, -1.0485306752577586, -1.0492076902135152,
      -1.0499136923023829, -1.0506484062375772, -1.051411547627948,
      -1.0522028230790186, -1.0530219302964052, -1.0538685581916034,
      -1.0547423869901151, -1.0556430883418937, -1.0565703254340819,
      -1.0575237531060271, -1.0585030179665271, -1.0595077585133117,
      -1.060537605254706, -1.0615921808334599, -1.0626711001527149,
      -1.0637739705040832, -1.064900391697793, -1.0660499561948955,
      -1.0672222492414762, -1.0684168490048553, -1.069633326711745,
      -1.0708712467883132, -1.0721301670021441, -1.0734096386060428,
      -1.0747092064836514, -1.0760284092968511, -1.0773667796349,
      -1.0787238441652798, -1.0800991237862025, -1.0814921337807528,
      -1.0829023839726133, -1.0843293788833388, -1.0857726178911424,
      -1.0872315953911436, -1.0887058009570452, -1.0901947195041883,
      -1.0916978314539558, -1.0932146128994604, -1.0947445357724952,
      -1.0962870680116885, -1.0978416737318191, -1.0994078133942506,
      -1.1009849439784405, -1.1025725191544637, -1.1041699894565267,
      -1.1057768024573995, -1.107392402943735, -1.1090162330922231,
      -1.1106477326465232, -1.1122863390949416, -1.1139314878487809,
      -1.1155826124213388, -1.1172391446074821, -1.1189005146637558,
      -1.1205661514889838, -1.1222354828052881, -1.1239079353394978,
      -1.1255829350048807, -1.1272599070831526, -1.1289382764067071,
      -1.1306174675410203, -1.1322969049671652, -1.1339760132643903,
      -1.1356542172927186, -1.1373309423754878, -1.139005614481805,
      -1.1406776604088427, -1.1423465079639317, -1.144011586146396,
      -1.1456723253290704, -1.1473281574394518, -1.1489785161404253,
      -1.1506228370105143, -1.1522605577235983, -1.1538911182280494,
      -1.1555139609252134, -1.1571285308472123, -1.1587342758339902,
      -1.1603306467095456, -1.1619170974573292, -1.1634930853946948,
      -1.165058071346418, -1.166611519817176, -1.1681528991629508,
      -1.1696816817613158, -1.1711973441805317, -1.1726993673474162,
      -1.1741872367139188, -1.175660442422362, -1.1771184794692877,
      -1.1785608478678586, -1.1799870528087639, -1.1813966048195828,
      -1.1827890199225408, -1.1841638197906244, -1.1855205319019877,
      -1.1868586896926245, -1.1881778327072228, -1.1894775067481889,
      -1.1907572640227577, -1.1920166632881741, -1.1932552699948737,
      -1.1944726564276227, -1.1956684018445762, -1.196842092614206,
      -1.1979933223500372, -1.1991216920431826, -1.200226810192599,
      -1.2013082929330241, -1.2023657641605814, -1.2033988556559703,
      -1.2044072072052232, -1.2053904667179951, -1.2063482903433131,
      -1.2072803425827836, -1.2081862964011989, -1.2090658333344988,
      -1.2099186435950717, -1.2107444261743305, -1.2115428889425588,
      -1.2123137487459648, -1.2130567315009217, -1.2137715722853608,
      -1.2144580154272859, -1.2151158145903695, -1.2157447328566073,
      -1.2163445428060029, -1.21691502659324, -1.2174559760213364,
      -1.2179671926122257, -1.2184484876742669, -1.2188996823666425,
      -1.2193206077606091, -1.2197111048976093, -1.2200710248441937,
      -1.22040022874374, -1.2206985878649546, -1.2209659836471354,
      -1.2212023077421641, -1.2214074620532396, -1.2215813587702951,
      -1.2217239204021304, -1.2218350798052029, -1.2219147802090964,
      -1.2219629752386292, -1.2219796289326201, -1.2219647157592626,
      -1.2219182206281491, -1.2218401388988838, -1.2217304763863173,
      -1.2215892493623914, -1.2214164845545579, -1.2212122191408135,
      -1.2209765007413258, -1.2207093874066348, -1.2204109476024647,
      -1.2200812601911186, -1.2197204144094691, -1.2193285098435545,
      -1.218905656399764, -1.2184519742726505, -1.2179675939093442,
      -1.2174526559705972, -1.2169073112884612, -1.216331720820609,
      -1.215726055601303, -1.2150904966890457, -1.2144252351108948,
      -1.2137304718034891, -1.2130064175507782, -1.2122532929184788,
      -1.2114713281852871, -1.210660763270853, -1.2098218476605356,
      -1.2089548403269754, -1.2080600096485, -1.2071376333243682,
      -1.2061879982869186, -1.2052114006105976, -1.2042081454179412,
      -1.2031785467825047, -1.20212292762879, -1.2010416196291827,
      -1.1999349630979588, -1.1988033068823516, -1.1976470082507527,
      -1.196466432778057, -1.195261954228199, -1.1940339544339051,
      -1.1927828231737114, -1.1915089580462761, -1.1902127643420373,
      -1.1888946549122408, -1.187555050035382, -1.1861943772811323,
      -1.1848130713717455, -1.183411574041016, -1.1819903338908444,
      -1.1805498062454327, -1.1790904530031618, -1.177612742486206,
      -1.1761171492879232, -1.1746041541180845, -1.1730742436459858,
      -1.1715279103414675, -1.1699656523139377, -1.1683879731494298,
      -1.1667953817457339, -1.1651883921456743, -1.1635675233685894,
      -1.1619332992400564, -1.1602862482199063, -1.1586269032286391,
      -1.15695580147221, -1.1552734842653398, -1.1535804968533139,
      -1.1518773882324158, -1.1501647109689788, -1.148443021017183,
      -1.1467128775355904, -1.1449748427025437, -1.143229481530448,
      -1.1414773616789933, -1.1397190532674233, -1.1379551286858705,
      -1.1361861624058411, -1.1344127307898901, -1.132635411900591,
      -1.1308547853088318, -1.1290714319015027, -1.1272859336886585,
      -1.1254988736101958, -1.1237108353421468, -1.1219224031025985,
      -1.1201341614573752, -1.1183466951254692, -1.1165605887843713,
      -1.1147764268752745, -1.1129947934083078, -1.1112162717677978,
      -1.1094414445176513, -1.1076708932069375, -1.1059051981757047,
      -1.104144938361129, -1.1023906911040235, -1.100643031955826,
      -1.0989025344860794, -1.0971697700905114, -1.0954453077997293,
      -1.0937297140886586, -1.0920235526867519, -1.090327384389016,
      -1.0886417668679844, -1.0869672544866182, -1.085304398112277,
      -1.0836537449317687, -1.0820158382675726, -1.080391217395281,
      -1.0787804173623354, -1.0771839688081031, -1.0756023977853875,
      -1.074036225583394, -1.0724859685522343, -1.0709521379290445,
      -1.0694352396657323, -1.0679357742584692, -1.0664542365789342,
      -1.0649911157074115, -1.0635468947677569, -1.0621220507643447,
      -1.060717054420991, -1.0593323700219537, -1.0579684552550457,
      -1.0566257610569187, -1.0553047314605866, -1.0540058034451998,
      -1.0527294067881758, -1.0514759639197, -1.0502458897796676,
      -1.0490395916771094, -1.0478574691521265, -1.0466999138404531,
      -1.0455673093405993, -1.0444600310837049, -1.043378446206088,
      -1.0423229134245855, -1.04129378291467, -1.0402913961914566,
      -1.0393160859935662, -1.0383681761699566, -1.0374479815697084,
      -1.0365558079348254, -1.035691951796097, -1.0348567003720452,
      -1.0340503314709817, -1.0332731133962429, -1.032525304854619,
      -1.0318071548679748, -1.031118902688166, -1.0304607777152253,
      -1.0298329994188498, -1.0292357772632648, -1.0286693106354177,
      -1.0281337887766036, -1.0276293907174787, -1.027156285216551,
      -1.0267146307020945, -1.026304575217595, -1.0259262563706626,
      -1.025579801285486, -1.0252653265588321, -1.0249829382195885,
      -1.0247327316918897, -1.0245147917618171, -1.0243291925477074,
      -1.0241759974740603, -1.0240552592490657, -1.0239670198457644,
      -1.02391131048682, -1.023888151632965, -1.0238975529750491,
      -1.0239395134297689, -1.0240140211390207, -1.0241210534729248,
      -1.0242605770364714, -1.0244325476798395, -1.0246369105123403,
      -1.024873599920012, -1.0251425395868372, -1.0254436425195925,
      -1.0257768110763126, -1.0261419369983675, -1.026538901446129,
      -1.0269675750382268, -1.0274278178943788, -1.0279194796817708,
      -1.0284423996649825, -1.0289964067594353, -1.0295813195883421,
      -1.0301969465431566, -1.0308430858474587, -1.0315195256243188,
      -1.0322260439670434, -1.0329624090133489, -1.0337283790228775,
      -1.0345237024580718, -1.035348118068353, -1.0362013549775861,
      -1.0370831327747994, -1.037993161608125, -1.038931142281927,
      -1.0398967663570851, -1.040889716254398, -1.0419096653610733,
      -1.0429562781402555, -1.0440292102435722, -1.0451281086266413,
      -1.046252611667509, -1.0474023492879749, -1.0485769430777578,
      -1.0497760064214652, -1.0509991446283187, -1.0522459550645837,
      -1.0535160272886743, -1.0548089431888581, -1.0561242771235479,
      -1.0574615960640958, -1.0588204597400643, -1.0602004207869129,
      -1.0616010248960512, -1.0630218109672009, -1.0644623112630243,
      -1.0659220515659478, -1.0674005513371481, -1.0688973238776167,
      -1.0704118764912756, -1.0719437106500684, -1.0734923221609649,
      -1.0750572013348478, -1.07663783315718, -1.0782336974604387,
      -1.079844269098214, -1.0814690181209414, -1.0831074099531917,
      -1.084758905572458, -1.0864229616893764, -1.088099030929323,
      -1.0897865620153198, -1.0914849999521767, -1.0931937862118244,
      -1.0949123589197503, -1.0966401530424956, -1.0983766005761235,
      -1.1001211307356118, -1.1018731701450992, -1.1036321430289042,
      -1.1053974714032773, -1.1071685752687843, -1.1089448728032911,
      -1.1107257805554496, -1.1125107136386387, -1.1142990859252835,
      -1.116090310241481, -1.117883798561879, -1.1196789622047207,
      -1.1214752120270028, -1.1232719586196731, -1.1250686125027931,
      -1.1268645843206107, -1.12865928503647, -1.1304521261274716,
      -1.1322425197788577, -1.1340298790780072, -1.1358136182080107,
      -1.1375931526407272, -1.1393678993292871, -1.14113727689995,
      -1.142900705843257, -1.1446576087044158, -1.1464074102728585,
      -1.1481495377708841, -1.1498834210413444, -1.1516084927342958,
      -1.1533241884925596, -1.155029947136113, -1.1567252108452712,
      -1.1584094253425663, -1.1600820400733016, -1.1617425083846649,
      -1.1633902877033997, -1.1650248397119207, -1.1666456305228552,
      -1.1682521308519089, -1.1698438161890472, -1.1714201669678841,
      -1.172980668733256, -1.174524812306901, -1.1760520939512114,
      -1.1775620155309743, -1.1790540846730739, -1.180527814924077,
      -1.1819827259056741, -1.1834183434678978, -1.1848341998400802,
      -1.1862298337795127, -1.1876047907177303, -1.188958622904374,
      -1.1902908895486302, -1.1916011569581193, -1.1928889986752766,
      -1.1941539956111009, -1.1953957361762844, -1.1966138164096447,
      -1.1978078401038492, -1.1989774189283418, -1.2001221725495057,
      -1.2012417287479382, -1.2023357235328673, -1.2034038012536485,
      -1.2044456147082874, -1.2054608252489909, -1.2064491028846858,
      -1.2074101263804851, -1.2083435833540637, -1.2092491703689148,
      -1.2101265930244796, -1.2109755660430657, -1.2117958133536131,
      -1.2125870681721951, -1.2133490730792942, -1.2140815800937916,
      -1.2147843507436826, -1.2154571561334488, -1.2160997770081374,
      -1.2167120038140484, -1.217293636756078, -1.2178444858516877,
      -1.2183643709814485, -1.2188531219362042, -1.2193105784607918,
      -1.219736590294352, -1.2201310172071655, -1.2204937290340907,
      -1.2208246057045045, -1.2211235372687874, -1.2213904239213815,
      -1.2216251760203289, -1.2218277141033869, -1.2219979689006517,
      -1.2221358813437189, -1.2222414025713813, -1.2223144939318755,
      -1.2223551269816464, -1.2223632834806955, -1.2223389553844648,
      -1.2222821448322911, -1.2221928641324467, -1.2220711357437475,
      -1.2219169922537931, -1.2217304763537871, -1.2215116408100153,
      -1.2212605484319412, -1.2209772720369971, -1.2206618944120204,
      -1.2203145082714224, -1.2199352162120585, -1.2195241306648552,
      -1.2190813738431923, -1.2186070776880853, -1.2181013838101902,
      -1.2175644434286377, -1.2169964173067511, -1.2163974756846674,
      -1.2157677982088675, -1.2151075738587083, -1.2144170008699064,
      -1.2136962866550862, -1.212945647721358, -1.21216530958503,
      -1.2113555066834023, -1.2105164822838033, -1.2096484883897627,
      -1.2087517856444907, -1.2078266432316103, -1.2068733387732338,
      -1.205892158225419, -1.2048833957710308, -1.2038473537100598,
      -1.2027843423474589, -1.2016946798785244, -1.2005786922718551,
      -1.1994367131499921, -1.1982690836677257, -1.1970761523881337,
      -1.1958582751564468, -1.1946158149717059, -1.1933491418563666,
      -1.1920586327237896, -1.19074467124378, -1.1894076477061259,
      -1.188047958882287, -1.1866660078851887, -1.1852622040272882,
      -1.1838369626768446, -1.1823907051125591, -1.180923858376568,
      -1.1794368551258771, -1.1779301334823, -1.176404136880933,
      -1.174859313917245, -1.173296118192835, -1.1717150081599184,
      -1.1701164469645937, -1.1685009022889532, -1.1668688461921224,
      -1.1652207549502178, -1.1635571088953904, -1.161878392253892,
      -1.160185092983351, -1.158477702609209, -1.1567567160604562,
      -1.1550226315046825, -1.1532759501825212, -1.1515171762415652,
      -1.1497468165697717, -1.1479653806284689, -1.1461733802849794,
      -1.1443713296449667, -1.1425597448845148, -1.1407391440820671,
      -1.1389100470502178, -1.1370729751674664, -1.1352284512099802,
      -1.1333769991833984, -1.1315191441548176, -1.1296554120849083,
      -1.1277863296603212, -1.1259124241263827, -1.1240342231201728,
      -1.1221522545040108, -1.1202670461994597, -1.1183791260218519,
      -1.1164890215154266, -1.114597259789138, -1.1127043673531638,
      -1.1108108699562205, -1.1089172924236905, -1.1070241584966418,
      -1.1051319906718025, -1.1032413100425305, -1.1013526361408317,
      -1.0994664867805066, -1.0975833779014439, -1.09570382341513,
      -1.0938283350514335, -1.0919574222066977, -1.0900915917932217,
      -1.0882313480901411, -1.0863771925957888, -1.0845296238815738,
      -1.0826891374474095, -1.0808562255787866, -1.0790313772054745,
      -1.0772150777619405, -1.0754078090495196, -1.0736100491003711,
      -1.0718222720432686, -1.0700449479712886, -1.0682785428113852,
      -1.0665235181959547, -1.0647803313363819, -1.0630494348986235,
      -1.0613312768808758, -1.0596263004933508, -1.0579349440401915,
      -1.0562576408035762, -1.0545948189300369, -1.0529469013190165,
      -1.0513143055137275, -1.0496974435942903, -1.0480967220732325,
      -1.0465125417933492, -1.0449452978279534, -1.0433953793835529,
      -1.0418631697049778, -1.040349045982965, -1.0388533792642443,
      -1.0373765343641486, -1.0359188697817299, -1.0344807376174772,
      -1.0330624834935631, -1.0316644464767124, -1.0302869590036667,
      -1.0289303468092621, -1.0275949288571735, -1.0262810172732739,
      -1.0249889172816835, -1.023718927143471, -1.0224713380980484,
      -1.0212464343072443, -1.0200444928020918, -1.0188657834322992,
      -1.0177105688184418, -1.0165791043068562, -1.0154716379272524,
      -1.0143884103530392, -1.0133296548643689, -1.0122955973138892,
      -1.0112864560952066, -1.0103024421140618, -1.0093437587622145,
      -1.0084106018940087, -1.0075031598056539, -1.0066216132171641,
      -1.0057661352569962, -1.004936891449328, -1.0041340397040184,
      -1.0033577303091827, -1.0026081059264083, -1.0018853015885854,
      -1.00118944470033, -1.0005206550409871, -0.99987904477020817,
      -0.99926471843605991, -0.99867777298566673, -0.99811829777835681,
      -0.99758637460128341, -0.99708207768752055, -0.99660547373657937,
      -0.99615662193734633, -0.995735573993404, -0.995342374150705,
      -0.9949770592275915, -0.9946396586471008, -0.99433019447155868,
      -0.99404868143940761, -0.99379512700424777, -0.99356953137606219,
      -0.99337188756458439, -0.99320218142478534, -0.99306039170443061,
      -0.99294649009369, -0.99286044127674677, -0.99280220298538424,
      -0.99277172605450248, -0.99276895447952807, -0.9927938254756814,
      -0.9928462695390613, -0.99292621050950258, -0.99303356563516687,
      -0.99316824563883355, -0.99333015478583409, -0.99351919095359642,
      -0.99373524570275462, -0.99397820434977879, -0.99424794604108313,
      -0.9945443438285595, -0.99486726474650444, -0.99521656988987728,
      -0.99559211449386131, -0.99599374801466489, -0.9964213142115228,
      -0.996874651229856, -0.99735359168552806, -0.99785796275015926,
      -0.99838758623745627, -0.99894227869048968, -0.99952185146988959,
      -1.0001261108429007, -1.0007548580732428, -1.0014078895117469,
      -1.0020849966876861, -1.0027859664007825, -1.0035105808138225,
      -1.0042586175458323, -1.0050298497657644, -1.0058240462866535,
      -1.0066409716601754, -1.0074803862715733, -1.0083420464348951,
      -1.0092257044884867, -1.0101311088907052, -1.0110580043157875,
      -1.0120061317498323, -1.0129752285868436, -1.0139650287247899,
      -1.0149752626616217, -1.0160056575912091, -1.0170559374991404,
      -1.018125823258339, -1.0192150327244511, -1.0203232808309541,
      -1.0214502796839338, -1.0225957386564943, -1.0237593644827443,
      -1.0249408613513147, -1.0261399309983652, -1.0273562728000347,
      -1.0285895838642822, -1.0298395591220821, -1.0311058914179325,
      -1.0323882715996164, -1.0336863886071943, -1.0349999295611727,
      -1.0363285798498061, -1.0376720232154948, -1.0390299418402487,
      -1.0404020164301484, -1.0417879262988001, -1.0431873494497121,
      -1.0445999626575857, -1.0460254415484553, -1.0474634606786668,
      -1.0489136936126395, -1.0503758129993799, -1.051849490647732,
      -1.0533343976002973, -1.0548302042060285, -1.0563365801914371,
      -1.0578531947303953, -1.0593797165125125, -1.0609158138100319,
      -1.0624611545432474, -1.0640154063443965, -1.0655782366200062,
      -1.0671493126116665, -1.068728301455216, -1.070314870238305,
      -1.0719086860563098, -1.0735094160666072, -1.0751167275411386,
      -1.0767302879172977, -1.0783497648470821, -1.0799748262445195,
      -1.0816051403313294, -1.0832403756808306, -1.0848802012600554,
      -1.086524286470073, -1.0881723011845095, -1.0898239157862402,
      -1.0914788012022725, -1.093136628936771, -1.0947970711022554,
      -1.0964598004489423, -1.0981244903922307, -1.0997908150383329,
      -1.1014584492080366, -1.1031270684586094, -1.1047963491038284,
      -1.106465968232154, -1.1081356037230377, -1.1098049342613638,
      -1.1114736393500375, -1.1131413993207175, -1.1148078953427047,
      -1.1164728094299876, -1.118135824446461, -1.1197966241093049,
      -1.1214548929905785, -1.1231103165169833, -1.124762580967861,
      -1.1264113734713987, -1.1280563819990848, -1.1296972953584146,
      -1.1313338031838649, -1.1329655959261697, -1.1345923648398875,
      -1.1362138019693118, -1.1378296001327255, -1.1394394529050229,
      -1.1410430545987362, -1.142640100243469, -1.1442302855637838,
      -1.1458133069555549, -1.1473888614608183, -1.1489566467411472,
      -1.1505163610495812, -1.1520677032011422, -1.1536103725419622,
      -1.1551440689170616, -1.1566684926367996, -1.1581833444420475,
      -1.1596883254681016, -1.161183137207388, -1.1626674814709752,
      -1.1641410603489484, -1.1656035761696864, -1.1670547314580517,
      -1.1684942288925748, -1.169921771261631, -1.1713370614186847,
      -1.1727398022366193, -1.1741296965612069, -1.1755064471637664,
      -1.1768697566930242, -1.17821932762627, -1.1795548622198002,
      -1.1808760624587358, -1.1821826300062415, -1.1834742661521889,
      -1.1847506717613281, -1.1860115472209987, -1.1872565923884328,
      -1.1884855065377116, -1.1896979883064005, -1.1908937356419331,
      -1.1920724457477896, -1.1932338150295037, -1.19437753904058,
      -1.1955033124283352, -1.1966108288797508, -1.1976997810673595,
      -1.1987698605952368, -1.1998207579451372, -1.2008521624228352,
      -1.2018637621047188, -1.2028552437846953, -1.2038262929214427,
      -1.2047765935860952, -1.2057058284103688, -1.2066136785352251,
      -1.207499823560096, -1.2083639414927319, -1.2092057086997294,
      -1.2100247998577882, -1.2108208879057467, -1.2115936439974562,
      -1.2123427374555391, -1.2130678357260871, -1.2137686043343519,
      -1.2144447068414732, -1.2150958048023179, -1.2157215577244369,
      -1.2163216230282541, -1.2168956560084678, -1.2174433097967794,
      -1.2179642353259543, -1.2184580812952832, -1.2189244941374953,
      -1.2193631179871591, -1.2197735946506361, -1.2201555635776158,
      -1.2205086618343004, -1.2208325240782649, -1.2211267825350574,
      -1.221391066976564, -1.2216250047012105, -1.2218282205160163,
      -1.2220003367205656, -1.2221409730929256, -1.2222497468775624,
      -1.2223262727752853, -1.2223701629352761, -1.2223810269492217,
      -1.2223584718476159, -1.2223021020982321, -1.222211519606847,
      -1.2220863237202126, -1.2219261112313367, -1.2217304763870971,
      -1.2214990108982213, -1.2212313039516716, -1.2209269422254525,
      -1.2205855099058924, -1.2202065887074114, -1.2197897578948029,
      -1.219334594308072, -1.2188406723898451, -1.2183075642153696,
      -1.2177348395251486, -1.2171220657602062, -1.2164688081000348,
      -1.2157746295032104, -1.2150390907507331, -1.2142617504920747,
      -1.2134421652939793, -1.2125798896920115, -1.2116744762448775,
      -1.2107254755915327, -1.2097324365110742, -1.2086949059854533,
      -1.2076124292649864, -1.2064845499366981, -1.2053108099954908,
      -1.2040907499181408, -1.2028239087401431, -1.2015098241353843,
      -1.2001480324986633, -1.198738069031045, -1.1972794678280605,
      -1.1957717619707349, -1.1942144836194484, -1.1926071641106222,
      -1.1909493340562183, -1.1892405234460508, -1.1874802617528915,
      -1.1856680780403663, -1.1838035010736185, -1.1818860594327354,
      -1.1799152816289142, -1.1778906962233564, -1.1758118319488648,
      -1.1736782178341272, -1.1714893833306685, -1.1692448584424366,
      -1.1669441738580137, -1.1645868610854069, -1.1621724525894166,
      -1.1597004819315235, -1.1571704839122972, -1.1545819947162588,
      -1.1519345520591955, -1.1492276953378779, -1.1464609657821436,
      -1.1436339066093182, -1.1407460631809181, -1.1377969831616255,
      -1.1347862166804523, -1.1317133164940991, -1.1285778381524132,
      -1.1253793401659506, -1.1221173841755534, -1.1187915351239184,
      -1.1154013614291143, -1.1119464351599579, -1.1084263322132539,
      -1.1048406324927884, -1.1011889200900729, -1.0974707834667448,
      -1.0936858156385796, -1.0898336143610756, -1.0859137823165186,
      -1.0819259273025001, -1.0778696624217903, -1.0737446062735525,
      -1.0695503831457827, -1.065286623208944, -1.0609529627107321,
      -1.0565490441718655, -1.0520745165828993, -1.047529035601918,
      -1.042912263753105, -1.0382238706260762, -1.0334635330759074,
      -1.0286309354238272, -1.0237257696584268, -1.018747735637402,
      -1.0136965412896588, -1.0085719028177982, -1.00337354490082,
      -0.998101200897044, -0.99275461304710511, -0.98733353267699742,
      -0.98183772040103956, -0.97626694632473887, -0.97062099024740045,
      -0.96489964186448729, -0.95910270096955519, -0.95322997765577533,
      -0.94728129251687376, -0.9412564768474887, -0.93515537284277206,
      -0.92897783379725474, -0.92272372430277871, -0.91639292044552989,
      -0.90998531000196237, -0.90350079263366057, -0.89693928008092227,
      -0.89030069635509546, -0.88358497792950086, -0.87679207392887615,
      -0.86992194631730346, -0.86297457008444345, -0.855949933430088,
      -0.84884803794685582, -0.84166889880103513, -0.83441254491138861,
      -0.82707901912594184, -0.81966837839657369, -0.812180693951377,
      -0.80461605146471582, -0.796974551224826, -0.78925630829897531,
      -0.78146145269598744, -0.77359012952615513, -0.76564249915837213,
      -0.75761873737443119, -0.74951903552045673, -0.74134360065527183,
      -0.73309265569576876, -0.72476643955904974, -0.71636520730137476,
      -0.7078892302538, -0.69933879615436934, -0.690714209276901,
      -0.68201579055615635, -0.67324387770943872, -0.66439882535443662,
      -0.6554810051233384, -0.64649080577303941, -0.63742863329147748,
      -0.62829491099992474, -0.61909007965122242, -0.6098145975239,
      -0.60046894051202759, -0.59105360221086123, -0.58156909399806367,
      -0.5720159451105904, -0.56239470271702263, -0.5527059319854295,
      -0.54295021614657746, -0.5331281565524767, -0.52324037273024571,
      -0.51328750243112931, -0.50327020167473746, -0.49318914478832532,
      -0.48304502444118314, -0.47283855167395739, -0.46257045592297513,
      -0.45224148503942108, -0.44185240530335462, -0.43140400143257018,
      -0.42089707658614095, -0.4103324523627383, -0.39971096879354573,
      -0.38903348432987078, -0.3783008758252619, -0.36751403851224534,
      -0.35667388597351457, -0.34578135010762012, -0.33483738108912886,
      -0.32384294732313007, -0.31279903539420484, -0.30170665000967695,
      -0.29056681393725992, -0.27938056793697763, -0.2681489706873571,
      -0.25687309870594877, -0.24555404626401484, -0.23419292529553076,
      -0.22279086530033407, -0.2113490132415502, -0.19986853343714164,
      -0.18835060744571991, -0.17679643394648881, -0.16520722861336543,
      -0.15358422398333507, -0.14192866931889581, -0.13024183046477095,
      -0.1185249896987174, -0.10677944557659619, -0.09500651277159658,
      -0.083207521907656679, -0.071383819387154226, -0.059536767212756941,
      -0.047667742803598881, -0.035778138805636441, -0.023869362896385596,
      -0.011942837583871484, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      1.5612511283791264E-17, -0.014100687876634394, -0.028219722487202548,
      -0.042355061448752465, -0.056504647702735167, -0.070666409907937322,
      -0.08483826283858574, -0.099018107787539389, -0.11320383297448605,
      -0.12739331395905351, -0.14158441405874927, -0.15577498477164015,
      -0.16996286620367682, -0.18414588750057312, -0.19832186728414339,
      -0.21248861409300268, -0.22664392682753437, -0.24078559519901879,
      -0.25491140018283209, -0.269019114475605, -0.28310650295624062,
      -0.29717132315068984, -0.3112113257003703, -0.32522425483412831,
      -0.3392078488436322, -0.35315984056208449, -0.36707795784614428,
      -0.38095992406094586, -0.39480345856809929, -0.40860627721655607,
      -0.42236609283622861, -0.43608061573423706, -0.44974755419367479,
      -0.46336461497476339, -0.47692950381828442, -0.49043992595115893,
      -0.50389358659405625, -0.51728819147090677, -0.530621447320195,
      -0.54389106240790341, -0.55709474704198614, -0.57023021408823926,
      -0.58329517948744425, -0.596287362773654, -0.60920448759348733,
      -0.62204428222631181, -0.63480448010516921, -0.647482820338327,
      -0.66007704823131375, -0.67258491580930579, -0.685004182339738,
      -0.69733261485499687, -0.70956798867506943, -0.72170808793000363,
      -0.73375070608205617, -0.74569364644738034, -0.75753472271712841,
      -0.76927175947782545, -0.7809025927308807, -0.79242507041109989,
      -0.80383705290406149, -0.81513641356221822, -0.82632103921959088,
      -0.83738883070491255, -0.84833770335308878, -0.8591655875148374,
      -0.86987042906436729, -0.88045018990496438, -0.89090284847234191,
      -0.90122640023562417, -0.911418858195823, -0.92147825338167233,
      -0.93140263534268886, -0.94119007263931154, -0.950838653330001,
      -0.96034648545514967, -0.9697116975176775, -0.97893243896017523,
      -0.98800688063845987, -0.99693321529141787, -1.005709658006994,
      -1.014334446684199, -1.0228058424910074, -1.0311221303180089,
      -1.039281619227693, -1.0472826428992237, -1.0551235600685978,
      -1.0628027549640362, -1.0703186377365015, -1.0776696448852041,
      -1.0848542396779801, -1.0918709125664148, -1.0987181815955882,
      -1.1053945928083257, -1.111898720643832, -1.1182291683305861,
      -1.1243845682733877, -1.1303635824344322, -1.1361649027083003,
      -1.1417872512907494, -1.1472293810412, -1.1524900758387939,
      -1.1575681509319227, -1.162462453281123, -1.1671718618952209,
      -1.1716952881606248, -1.17603167616367, -1.1801800030059011,
      -1.184139279112201, -1.1879085485316634, -1.1914868892311163,
      -1.1948734133811925, -1.1980672676348623, -1.2010676333983346,
      -1.2038737270942315, -1.2064848004169557, -1.2089001405801563,
      -1.2111190705562174, -1.2131409493076781, -1.2149651720105126,
      -1.2165911702691805, -1.2180184123233848, -1.2192464032464492,
      -1.2202746851352522, -1.2211028372916417, -1.2217304763952668,
      -1.2221572566677561, -1.2223828700281791, -1.2224070462397347,
      -1.2222295530475977, -1.2218501963078738, -1.2212688201076058,
      -1.2204853068757746, -1.2194995774852502, -1.2183115913456404,
      -1.2169213464869926, -1.2153288796343056, -1.2135342662728088,
      -1.2115376207039721, -1.2093390960922079, -1.2069388845022317,
      -1.2043372169270536, -1.2015343633065638, -1.1985306325366931,
      -1.1953263724691194, -1.1919219699015018, -1.1883178505582215,
      -1.1845144790616098, -1.1805123588936588, -1.1763120323481895,
      -1.1719140804734802, -1.1673191230053435, -1.1625278182906464,
      -1.1575408632012769, -1.1523589930385538, -1.1469829814280874,
      -1.1414136402050938, -1.1356518192901752, -1.1296984065555755,
      -1.1235543276819266, -1.117220546005502, -1.1106980623559968,
      -1.1039879148848553, -1.0970911788841753, -1.0900089665962094,
      -1.0827424270134989, -1.0752927456696695, -1.0676611444209259,
      -1.0598488812182825, -1.0518572498705674, -1.043687579798251,
      -1.0353412357781322, -1.0268196176789413, -1.0181241601879041,
      -1.0092563325283244, -1.0002176381682346, -0.99100961452017933,
      -0.98163383263218884, -0.97209189687000708, -0.9623854445906399,
      -0.95251614580728938, -0.94248570284575106, -0.93229584999234028,
      -0.92194835313342949, -0.91144500938666784, -0.90078764672397227,
      -0.8899781235863663, -0.87901832849075257, -0.86791017962871164,
      -0.85665562445741206, -0.84525663928272587, -0.833715228834645,
      -0.82203342583509609, -0.81021329055825009, -0.79825691038343083,
      -0.78616639934072763, -0.77394389764941185, -0.76159157124927523,
      -0.74911161132498816, -0.73650623382360392, -0.72377767896530931,
      -0.71092821074755341, -0.69796011644265554, -0.684875706089031,
      -0.67167731197614522, -0.658367288123322, -0.64494800975253885,
      -0.6314218727553339, -0.61779129315394832, -0.60405870655685134,
      -0.59022656760876346, -0.57629734943533228, -0.56227354308257871,
      -0.54815765695127383, -0.53395221622636235, -0.51965976230160438,
      -0.50528285219954583, -0.49082405798699896, -0.47628596618614488,
      -0.46167117718143447, -0.44698230462241884, -0.43222197482267449,
      -0.41739282615496121, -0.4024975084427817, -0.38753868234848393,
      -0.3725190187580768, -0.3574411981629, -0.34230791003832561,
      -0.32712185221963275, -0.311885730275232, -0.29660225687738756,
      -0.281274151170615, -0.26590413813790059, -0.25049494796492278,
      -0.23504931540243493, -0.21956997912696957, -0.2040596811000463,
      -0.18852116592603113, -0.17295718020883746, -0.15737047190761519,
      -0.14176378969162193, -0.12613988229441769, -0.11050149786758716,
      -0.094851383334124323, -0.079192283741687089, -0.063526941615856869,
      -0.047858096313614054, -0.032188483377161591, -0.016520833888304755,
      -0.00085787382353209364, 0.014797676590008572, 0.030443103517486678,
      0.046075700158123845, 0.061692767385535981, 0.077291614386490584,
      0.092869559297924467, 0.10842392984203376, 0.1239520639592786,
      0.13945131043912182, 0.154919029548329, 0.17035259365667341,
      0.185749387859852, 0.20110681059946919, 0.21642227427989341,
      0.23169320588184245, 0.24691704757250474, 0.26209125731205363,
      0.27721330945636513, 0.29228069535579426, 0.30729092394982871,
      0.32224152235746306, 0.33713003646313122, 0.35195403149803306,
      0.36671109261669277, 0.38139882546859183, 0.39601485676471349,
      0.41055683483884786, 0.42502243020349478, 0.43940933610021088,
      0.45371526904424664, 0.46793796936332555, 0.48207520173040458,
      0.49612475569027881, 0.5100844461798687, 0.52395211404205011,
      0.53772562653288947, 0.551402877822121, 0.56498178948674749,
      0.57846031099760076, 0.59183642019874794, 0.60510812377958523,
      0.61827345773950015, 0.63133048784495871, 0.64427731007889577,
      0.657112051082269, 0.66983286858766322, 0.68243795184480571,
      0.69492552203788183, 0.70729383269452106, 0.71954117008634133,
      0.731665853620934, 0.74366623622517192, 0.75554070471972878,
      0.76728768018471383, 0.77890561831628768, 0.79039300977418581,
      0.80174838052001818, 0.812970292146272, 0.82405734219589377,
      0.835008164472382, 0.84582142934027449, 0.85649584401595391,
      0.8670301528486859, 0.87742313759179225, 0.88767361766389408,
      0.89778045040012855, 0.9077425312932772, 0.917558794224722,
      0.92722821168516412, 0.93674979498503208, 0.94612259445451952,
      0.95534569963318139, 0.96441823944904093, 0.97333938238713658,
      0.98210833664746755, 0.99072435029227346, 0.9991867113826175,
      1.0074947481042047, 1.0156478288824196, 1.0236453624865156,
      1.0314867981229496, 1.0391716255177954, 1.0466993749882418,
      1.0540696175031126, 1.0612819647324132, 1.0683360690858643,
      1.0752316237404127, 1.0819683626567023, 1.0885460605844908,
      1.0949645330570115, 1.1012236363742605, 1.107323267575226,
      1.1132633643990328, 1.1190439052350427, 1.1246649090618752,
      1.1301264353753984, 1.1354285841056693, 1.1405714955228681,
      1.14555535013222, 1.1503803685579508, 1.1550468114162806,
      1.1595549791775011, 1.1639052120171549, 1.1680978896563643,
      1.1721334311913354, 1.1760122949120864, 1.1797349781104416,
      1.1833020168773387, 1.1867139858895002, 1.1899714981855198,
      1.1930752049314239, 1.1960257951757631, 1.1988239955943047,
      1.2014705702243769, 1.2039663201889483, 1.206312083410507,
      1.2085087343148131, 1.2105571835246018, 1.2124583775433249,
      1.2142132984289993, 1.2158229634582634, 1.2172884247807245,
      1.2186107690636807, 1.2197911171273308, 1.2208306235705488,
      1.2217304763873376, 1.2224918965740603, 1.2231161377275515,
      1.2236044856342212, 1.223958257850263, 1.2241788032730727,
      1.2242675017040066, 1.224225763402581, 1.2240550286322531,
      1.2237567671978897, 1.2233324779750665, 1.2227836884313088,
      1.2221119541394223, 1.2213188582830354, 1.220406011154495,
      1.2193750496452493, 1.2182276367288647, 1.2169654609368121,
      1.2155902358271737, 1.2141036994464109, 1.2125076137843487,
      1.2108037642225267, 1.2089939589760641, 1.2070800285292023,
      1.2050638250646724, 1.2029472218870607, 1.2007321128403186,
      1.1984204117195845, 1.1960140516774895, 1.1935149846251014,
      1.1909251806276855, 1.1882466272954397, 1.1854813291693891,
      1.1826313071026009, 1.1796985976369, 1.1766852523752611,
      1.1735933373500431, 1.1704249323872684, 1.1671821304670966,
      1.1638670370806963, 1.1604817695836862, 1.1570284565463314,
      1.1535092371006779, 1.1499262602848117, 1.1462816843844288,
      1.142577676271902, 1.1388164107430316, 1.1350000698516698,
      1.1311308422424136, 1.1272109224815436, 1.123242510386413,
      1.1192278103534674, 1.1151690306850988, 1.1110683829155144,
      1.1069280811358206, 1.102750341318512, 1.0985373806415633,
      1.0942914168123123, 1.0900146673913316, 1.0857093491164806,
      1.0813776772273371, 1.0770218647902001, 1.0726441220238474,
      1.0682466556262682, 1.0638316681025362, 1.0594013570940342,
      1.0549579147092227, 1.0505035268561334, 1.0460403725768024,
      1.0415706233838105, 1.0370964425991431, 1.0326199846955524,
      1.0281433946406089, 1.0236688072436444, 1.0191983465057644,
      1.0147341249731243, 1.0102782430936594, 1.0058327885774474,
      1.0013998357609049, 0.99698144497498264, 0.99257966191756486,
      0.98819651703023725, 0.98383402487962468, 0.97949418354345874,
      0.97517897400156983, 0.97089035953198177, 0.96663028511227223,
      0.96240067682639174, 0.95820344127710444, 0.95404046500422424,
      0.94991361390882578, 0.94582473268358547, 0.9417756442494315,
      0.93776814919866758, 0.93380402524472816, 0.92988502667873751,
      0.92601288383301883, 0.92218930255172848, 0.91841596366876421,
      0.91469452249309768, 0.91102660830168869, 0.90741382384013658,
      0.90385774483120884, 0.90035991949139371, 0.896921868055628,
      0.89354508231033347, 0.89023102513490815, 0.88698113005180457,
      0.88379680078532619, 0.88067941082929191, 0.87763030302367,
      0.87465078914033656, 0.87174214947806417, 0.86890563246686892,
      0.86614245428184056, 0.86345379846655856, 0.86084081556622716,
      0.8583046227706207, 0.85584630356695968, 0.853466907402824,
      0.85116744935919819, 0.84894890983375249, 0.84681223423445884,
      0.844758332683633, 0.84278807973249459, 0.84090231408633054,
      0.839101838340354, 0.83738741872632749, 0.835759784870049,
      0.83421962955975415, 0.8327676085255229, 0.83140434022975507,
      0.83013040566877894, 0.828946348185661, 0.82785267329426981,
      0.82684984851465437, 0.82593830321979533, 0.82511842849376693,
      0.82439057700136653, 0.8237550628692506, 0.82321216157862076,
      0.8227621098694895, 0.822405105656569, 0.82214130795680307,
      0.82197083682857575, 0.82189377332261437, 0.82191015944461709,
      0.82201999812960369, 0.82222325322802259, 0.822519849503608,
      0.8229096726430013, 0.82339256927713933, 0.82396834701440558,
      0.82463677448553951, 0.82539758140030417, 0.82625045861589175,
      0.82719505821705508, 0.82823099360795549, 0.82935783961569143,
      0.83057513260549287, 0.83188237060755921, 0.83327901345548516,
      0.83476448293627326, 0.83633816295186469, 0.83799939969216652,
      0.83974750181951929, 0.841581740664563, 0.84350135043344421,
      0.84550552842631688, 0.84759343526706687, 0.84976419514421409,
      0.85201689606290942, 0.85435059010797465, 0.8567642937179013,
      0.85925698796974148, 0.86182761887481085, 0.86447509768511965,
      0.86719830121044883, 0.86999607214598818, 0.872867219410441,
      0.87581051849449842, 0.87882471181959809, 0.88190850910685537,
      0.885060587756071, 0.88827959323470951, 0.8915641394767323,
      0.89491280929118378, 0.8983241547804115, 0.901796697767799,
      0.90532893023489935, 0.90891931476783561, 0.912566285012855,
      0.91626824614089686, 0.92002357532105061, 0.92383062220276679,
      0.92768770940668044, 0.93159313302392, 0.93554516312374691,
      0.93954204426938925, 0.94358199604191828, 0.94766321357202388,
      0.951783868079537, 0.95594210742053709, 0.96013605664190194,
      0.96436381854312958, 0.96862347424527973, 0.97291308376686925,
      0.97723068660655776, 0.981574302332452, 0.98594193117787221,
      0.99033155464339784, 0.994741136105019, 0.99916862142823915,
      1.0036119395879248, 1.0080690032937423, 1.0125377096210033,
      1.0170159406467199, 1.0215015640907168, 1.0259924339615758,
      1.0304863912072724, 1.034981264370272, 1.0394748702469361,
      1.0439650145510238, 1.0484494925811003, 1.0529260898916768,
      1.0573925829678634, 1.0618467399033589, 1.0662863210815734,
      1.0707090798596928, 1.0751127632554769, 1.0794951126366055,
      1.083853864412365, 1.0881867507274736, 1.0924915001578559,
      1.09676583840815, 1.101007489010756, 1.1052141740262225, 1.10938361474476,
      1.1135135323886882, 1.1176016488156071, 1.1216456872220868,
      1.1256433728476845, 1.1295924336790577, 1.1334906011540056,
      1.1373356108651951, 1.1411252032634014, 1.144857124360035,
      1.1485291264287645, 1.1521389687060222, 1.1556844180901944,
      1.1591632498392921, 1.162573248266898, 1.1659122074361858,
      1.1691779318518116, 1.1723682371494775, 1.1754809507829633,
      1.1785139127084256, 1.1814649760657681, 1.1843320078568818,
      1.1871128896205623, 1.1898055181038947, 1.1924078059299239,
      1.194917682261414, 1.1973330934604889, 1.1996520037439795,
      1.2018723958342747, 1.2039922716054914, 1.2060096527247708,
      1.2079225812885126, 1.2097291204533716, 1.2114273550618122,
      1.2130153922620643, 1.2144913621222688, 1.2158534182386589,
      1.2170997383375883, 1.218228524871221, 1.2192380056067278,
      1.2201264342088038, 1.2208920908153325, 1.2215332826060394,
      1.2220483443639618, 1.2224356390295703, 1.2226935582473752,
      1.2228205229048719, 1.2228149836636433, 1.2226754214824898,
      1.2224003481324088, 1.2219883067032922, 1.2214378721021744,
      1.2207476515429037, 1.2199162850270735, 1.2189424458160873,
      1.2178248408942072, 1.2165622114224608, 1.2151533331832527,
      1.21359701701558, 1.211892109240692, 1.2100374920780845,
      1.2080320840517096, 1.2058748403862678, 1.2035647533934759,
      1.201100852848185, 1.1984822063542575, 1.1957079197000662,
      1.1927771372035365, 1.1896890420466091, 1.1864428565990415,
      1.1830378427314339, 1.179473302117402, 1.1757485765247924,
      1.1718630480958683, 1.1678161396163722, 1.1636073147733819,
      1.1592360784018929, 1.1547019767200475, 1.1500045975529412,
      1.1451435705449302, 1.140118567360394, 1.1349293018728732,
      1.1295755303425403, 1.124057051581937, 1.118373707109936,
      1.1125253812938747, 1.106512001479822, 1.1003335381109327,
      1.0939900048338524, 1.087481458593148, 1.0808079997137168,
      1.0739697719711707, 1.066966962650145, 1.0597998025905404,
      1.0524685662216564, 1.044973571584223, 1.0373151803403096,
      1.0294937977711085, 1.0215098727625953, 1.0133638977790618,
      1.0050564088245233, 0.99658798539202254, 0.98795925040082244,
      0.97917087012152293, 0.97022355408910177, 0.96111805500391667,
      0.95185516862068531, 0.94243573362547428, 0.93286063150073761,
      0.92313078637842017, 0.91324716488119084, 0.9032107759518313,
      0.89302267067083463, 0.88268394206225287, 0.87219572488786434,
      0.86155919542969717, 0.85077557126099013, 0.83984611100562445,
      0.82877211408612661, 0.8175549204602881, 0.80619591034648719,
      0.7946965039377718, 0.78305816110481052, 0.77128238108776948,
      0.75937070217721436, 0.74732470138411411, 0.73514599409905623,
      0.72283623374074957, 0.71039711139393336, 0.69783035543676231,
      0.68513773115781, 0.67232104036277007, 0.65938212097097115,
      0.6463228466018327, 0.63314512615134677, 0.61985090335874293,
      0.60644215636342069, 0.5929208972523089, 0.57928917159773929,
      0.56554905798600286, 0.55170266753669306, 0.53775214341298561,
      0.523699660322985, 0.50954742401227771, 0.49529767074783887,
      0.48095266679343984, 0.46651470787668203, 0.45198611864784083,
      0.43736925213064043, 0.42266648916513611, 0.40788023784283883,
      0.3930129329342622, 0.37806703530903474, 0.36304503134875388,
      0.34794943235273007, 0.332782773936803, 0.31754761542539262,
      0.30224653923695161, 0.28688215026299591, 0.27145707524088303,
      0.25597396212051915, 0.2404354794251683, 0.22484431560654655,
      0.20920317839436794, 0.1935147941405469, 0.17778190715822009,
      0.1620072790557866, 0.14619368806613664, 0.130343928371276,
      0.11446080942251553, 0.098547155256436744, 0.082605803806792749,
      0.0666396062125714, 0.0506514261223923, 0.034644138995441089,
      0.018620631399115482, 0.0025838003036176994, -0.01346344762635188,
      -0.029518196742570044, -0.045577523126771519, -0.06163849530639548,
      -0.077698174972438389, -0.093753617699177713, -0.10980187366561112,
      -0.125839988378359, -0.14186500339587729, -0.15787395705374432,
      -0.17386388519083851, -0.18983182187621736, -0.20577480013646202,
      -0.22168985268331898, -0.23757401264142577, -0.25342431427591677,
      -0.26923779371970635, -0.28501148970027262, -0.30074244426570457,
      -0.31642770350983945, -0.33206431829628225, -0.3476493449811115,
      -0.36317984613406684, -0.37865289125803075, -0.39406555750658417,
      -0.40941493039948729, -0.4246981045358264, -0.43991218430468249,
      -0.45505428459310659, -0.47012153149120506, -0.48511106299415846,
      -0.50002002970096338, -0.51484559550972586, -0.529584938309298,
      -0.54423525066709522, -0.55879374051288033, -0.57325763181834577,
      -0.58762416527230865, -0.60189059895133079, -0.616054208985587,
      -0.63011229021980486, -0.64406215686907464, -0.65790114316941262,
      -0.67162660402281749, -0.685235915636722, -0.69872647615762751,
      -0.71209570629876706, -0.72534104996162574, -0.73845997485115311,
      -0.751449973084495, -0.76430856179311346, -0.77703328371809166,
      -0.78962170779850094, -0.80207142975265355, -0.81438007265210377,
      -0.82654528748823486, -0.83856475373128736, -0.85043617988168541,
      -0.86215730401349933, -0.87372589430994407, -0.88513974959071828,
      -0.89639669983109682, -0.907494606672605, -0.91843136392517244,
      -0.92920489806061635, -0.93981316869734, -0.95025416907610527,
      -0.96052592652679258, -0.97062650292598662, -0.98055399514529906,
      -0.99030653549030945, -0.99988229213001623, -1.0092794695166754,
      -1.0184963087959498, -1.0275310882072293, -1.0363821234740744,
      -1.0450477681846269, -1.0535264141619474, -1.0618164918241546,
      -1.0699164705342983, -1.0778248589398729, -1.0855402053019017,
      -1.0930610978134834, -1.1003861649077811, -1.1075140755553243,
      -1.1144435395505872, -1.1211733077877741, -1.1277021725257448,
      -1.1340289676420208, -1.14015256887582, -1.1460718940600658,
      -1.1517859033423137, -1.1572935993945672, -1.1625940276119187,
      -1.1676862762999891, -1.1725694768511228, -1.1772428039093126,
      -1.1817054755238117, -1.1859567532914186, -1.1899959424874023,
      -1.1938223921850555, -1.1974354953638471, -1.2008346890061716,
      -1.2040194541826814, -1.2069893161261867, -1.2097438442941328,
      -1.2122826524196433, -1.2146053985511334, -1.2167117850805045,
      -1.2186015587599197, -1.220274510707184, -1.2217304763997314,
      -1.2229693356572475, -1.2239910126129474, -1.224795475673528,
      -1.2253827374678306, -1.2257528547842416, -1.2259059284968625,
      -1.225842103480494, -1.2255615685144707, -1.2250645561753821,
      -1.2243513427187507, -1.2234222479496888, -1.222277635082603,
      -1.2209179105900021, -1.2193435240404602, -1.2175549679258075,
      -1.2155527774776016, -1.213337530472955, -1.2109098470297917,
      -1.2082703893915994, -1.2054198617017557, -1.20235900976752,
      -1.1990886208137446, -1.1956095232264263, -1.1919225862861602,
      -1.1880287198915938, -1.1839288742729785, -1.179624039695907,
      -1.175115246155344, -1.1704035630600418, -1.165490098907457,
      -1.1603760009492496, -1.1550624548475128, -1.1495506843218035,
      -1.1438419507871158, -1.1379375529828977, -1.1318388265932373,
      -1.1255471438583329, -1.1190639131773825, -1.1123905787029906,
      -1.105528619927258, -1.0984795512596484, -1.0912449215967812,
      -1.0838263138842883, -1.0762253446708505, -1.0684436636545727,
      -1.060482953221829, -1.0523449279787032, -1.0440313342752028,
      -1.0355439497223571, -1.0268845827023625, -1.018055071871925,
      -1.0090572856589428, -0.99989312175267864, -0.99056450658758977,
      -0.981073394820953, -0.97142176880444742, -0.9616116380498575,
      -0.9516450386890456, -0.94152403292836562, -0.93125070849766578,
      -0.920827178094054, -0.9102555788205865, -0.8995380716200444,
      -0.88867684070395714, -0.877674092977052, -0.86653205745729289,
      -0.85525298469167421, -0.84383914616794009, -0.832292833722402,
      -0.82061635894402163, -0.80881205257494981, -0.796882263907648,
      -0.78482936017882665, -0.77265572596032106, -0.76036376254711813,
      -0.74795588734268148, -0.7354345332417539, -0.72280214801083975,
      -0.71006119366649667, -0.697214145851662, -0.68426349321014013,
      -0.67121173675947, -0.65806138926232849, -0.644814974596641,
      -0.63147502712458947, -0.6180440910606867, -0.60452471983908607,
      -0.5909194754803252, -0.57723092795764352, -0.56346165456308539,
      -0.54961423927353548, -0.53569127211688572, -0.52169534853847688,
      -0.50762906876802338, -0.493495037187165, -0.47929586169783783,
      -0.465034153091618, -0.45071252442022641, -0.43633359036735686,
      -0.42189996662199786, -0.40741426925340929, -0.39287911408794068,
      -0.37829711608783284, -0.36367088873218711, -0.34900304340027377,
      -0.33429618875730216, -0.31955293014286668, -0.30477586896220393,
      -0.28996760208041711, -0.27513072121983434, -0.26026781236066515,
      -0.24538145514508786, -0.23047422228496706, -0.21554867897328717,
      -0.20060738229952163, -0.18565288066905214, -0.17068771322678633,
      -0.15571440928513414, -0.14073548775648315, -0.12575345659031054,
      -0.11077081221508615, -0.095790038985091835, -0.080813608632308062,
      -0.065843979723501728, -0.050883597122647166, -0.035934891458805747,
      -0.021000278599620344, -0.0060821591305226935, 0.0088170821602051239,
      0.023695076790371271, 0.038549473086747846, 0.053377936681686555,
      0.068178151003415163, 0.082947817759871, 0.097684657415959261,
      0.11238640966413369, 0.12705083388818364, 0.14167570962010775,
      0.15625883699000589, 0.17079803716884343, 0.18529115280400932,
      0.19973604844757609, 0.21413061097714636, 0.22847275000921077,
      0.24276039830492122, 0.25699151216817356, 0.27116407183595509,
      0.28527608186082914, 0.29932557148549693, 0.31331059500936748,
      0.3272292321470352, 0.341079588378616, 0.3548597952918594,
      0.36856801091596919, 0.38220242004706234, 0.39576123456523193,
      0.40924269374310718, 0.42264506454589357, 0.43596664192282086,
      0.44920574908994709, 0.46236073780427556, 0.47542998862913449,
      0.48841191119076305, 0.50130494442610607, 0.51410755682171294,
      0.52681824664376209, 0.53943554215914979, 0.55195800184761834,
      0.56438421460489818, 0.57671279993684232, 0.588942408144515,
      0.60107172050024416, 0.61309944941458572, 0.62502433859421647,
      0.63684516319072748, 0.64856072994031133, 0.66016987729434218,
      0.6716714755408445, 0.68306442691684421, 0.694347665711607,
      0.7055201583607833, 0.71658090353143955, 0.72752893219800785,
      0.738363307709159, 0.74908312584561754, 0.75968751486893227,
      0.7701756355612257, 0.7805466812559454, 0.79079987785965,
      0.80093448386483868, 0.810949790353882, 0.82084512099406459,
      0.83061983202378631, 0.84027331222996515, 0.84980498291667206,
      0.85921429786503767, 0.8685007432845071, 0.87766383775544832,
      0.88670313216319652, 0.89561820962356919, 0.90440868539992536,
      0.913074206811805, 0.92161445313522872, 0.93002913549470756,
      0.93831799674703, 0.94648081135689666, 0.95451738526446572,
      0.96242755574489125, 0.97021119125990729, 0.97786819130156155,
      0.98539848622814574, 0.99280203709242631, 1.0000788354622407,
      1.0072289032335608, 1.0142522924360824, 1.0211490850314555,
      1.0279193927042258, 1.0345633566455896, 1.0410811473300459,
      1.0474729642850515, 1.0537390358537571, 1.0598796189509536,
      1.0658949988122923, 1.0717854887369103, 1.0775514298235367,
      1.0831931907002124, 1.088711167247717, 1.094105782316797,
      1.0993774854393343, 1.1045267525335292, 1.1095540856032511,
      1.1144600124316348, 1.1192450862690486, 1.1239098855155634,
      1.1284550133980176, 1.1328810976418173, 1.1371887901375712,
      1.1413787666026951, 1.1454517262381079, 1.1494083913801241,
      1.1532495071476954, 1.156975841085093, 1.1605881828001894,
      1.1640873435984318, 1.1674741561126629, 1.1707494739289053,
      1.1739141712082335, 1.1769691423048709, 1.1799153013806361,
      1.1827535820158719, 1.1854849368169913, 1.1881103370207606,
      1.1906307720954674, 1.1930472493390882, 1.1953607934746093,
      1.1975724462426149, 1.1996832659912866, 1.2016943272639447,
      1.2036067203842633, 1.2054215510393076, 1.2071399398604961,
      1.2087630220026675, 1.2102919467213304, 1.2117278769482935,
      1.2130719888657542, 1.2143254714790155, 1.2154895261879539,
      1.2165653663573626, 1.2175542168863278, 1.2184573137767496,
      1.2192759037011458, 1.220011243569884, 1.2206646000979535,
      1.2212372493714316, 1.2217304764137606, 1.2221455747519683,
      1.2224838459829739, 1.2227465993400919, 1.2229351512598821,
      1.2230508249494623, 1.2230949499544124, 1.2230688617274061,
      1.2229739011976866, 1.222811414341523, 1.2225827517537593,
      1.2222892682205941, 1.2219323222937042, 1.221513275865842,
      1.2210334937480218, 1.2204943432484183, 1.2198971937531016,
      1.2192434163087127, 1.21853438320722, 1.2177714675728466,
      1.2169560429513055, 1.2160894829014417, 1.2151731605894007,
      1.2142084483854354, 1.2131967174634561, 1.2121393374034377,
      1.2110376757967882, 1.2098930978547844, 1.2087069660201828,
      1.2074806395821027, 1.2062154742942903, 1.2049128219968548,
      1.203574030241588, 1.2022004419209491, 1.2007933949008252,
      1.1993542216571436, 1.1978842489164534, 1.1963847973005384,
      1.1948571809751725, 1.1933027073030904, 1.1917226765012723,
      1.1901183813026106, 1.1884911066220589, 1.1868421292273228,
      1.1851727174141926, 1.1834841306865787, 1.181777619441329,
      1.1800544246579063, 1.1783157775929896, 1.1765628994800748,
      1.174797001234134, 1.1730192831614104, 1.1712309346744059,
      1.1694331340121136, 1.1676270479655826, 1.1658138316088331,
      1.1639946280352198, 1.1621705680992644, 1.1603427701640252,
      1.1585123398540507, 1.1566803698139678, 1.1548479394727384,
      1.1530161148136455, 1.1511859481500419, 1.1493584779068937,
      1.1475347284081734, 1.145715709670124, 1.1439024172004346,
      1.1420958318033583, 1.1402969193907975, 1.1385066307993954,
      1.1367259016136426, 1.1349556519950383, 1.1331967865173191,
      1.1314501940077715, 1.129716747394659, 1.1279973035607622,
      1.1262927032030594, 1.124603770698547, 1.1229313139762223,
      1.1212761243952187, 1.1196389766291186, 1.1180206285564285,
      1.1164218211572272, 1.1148432784159925, 1.1132857072305817,
      1.1117497973273869, 1.1102362211826415, 1.1087456339498758,
      1.1072786733935089, 1.1058359598285623, 1.1044180960664873,
      1.1030256673670848, 1.1016592413964965, 1.1003193681912549,
      1.0990065801283626, 1.0977213919013811, 1.0964643005025039,
      1.0952357852105843, 1.0940363075850827, 1.0928663114659183,
      1.0917262229791753, 1.0906164505486351, 1.0895373849131056,
      1.0884893991494922, 1.0874728487015879, 1.0864880714145326,
      1.0855353875748992, 1.0846150999563564, 1.0837274938708756,
      1.0828728372254197, 1.082051380584073, 1.0812633572355521,
      1.0805089832660586, 1.0797884576374044, 1.0791019622703619,
      1.0784496621331865, 1.0778317053352406, 1.0772482232256648,
      1.0766993304970436, 1.076185125293986, 1.0757056893265697,
      1.0752610879885836, 1.0748513704804885, 1.074476569937044,
      1.0741367035595279, 1.0738317727524702, 1.0735617632648407,
      1.073326645335607, 1.0731263738436037, 1.0729608884616226,
      1.0728301138146581, 1.0727339596422245, 1.0726723209646774,
      1.0726450782534411, 1.0726520976050935, 1.072693230919193,
      1.0727683160797876, 1.0728771771405214, 1.0730196245132473,
      1.073195455160076, 1.0734044527887567, 1.0736463880513221,
      1.0739210187459078, 1.0742280900216481, 1.0745673345865758,
      1.0749384729184377, 1.0753412134783114, 1.0757752529269797,
      1.0762402763439296, 1.0767359574489186, 1.0772619588259897,
      1.0778179321498722, 1.0784035184146532, 1.0790183481646487,
      1.0796620417273701, 1.0803342094484898, 1.0810344519287296,
      1.0817623602625737, 1.0825175162786986, 1.0832994927820565,
      1.0841078537974851, 1.0849421548147848, 1.085801943035144,
      1.0866867576188346, 1.08759612993408, 1.0885295838070004,
      1.0894866357725461, 1.0904667953263332, 1.0914695651772681,
      1.0924944415008913, 1.0935409141933368, 1.0946084671258178,
      1.0956965783995449, 1.0968047206009954, 1.0979323610574194,
      1.099078962092525, 1.1002439812822233, 1.1014268717103604,
      1.102627082224342, 1.1038440576905582, 1.1050772392495256,
      1.1063260645706574, 1.1075899681065775, 1.1088683813468756,
      1.1101607330712437, 1.1114664496018867, 1.1127849550551341,
      1.11411567159216, 1.1154580196687367, 1.1168114182839362,
      1.1181752852276898, 1.1195490373271451, 1.1209320906917102,
      1.1223238609567376, 1.1237237635257411, 1.1251312138110932,
      1.1265456274731009, 1.1279664206574094, 1.12939301023064,
      1.1308248140141886, 1.1322612510161347, 1.1337017416611566,
      1.135145708018404, 1.1365925740272529, 1.1380417657208695,
      1.139492711447522, 1.1409448420895698, 1.1423975912800637,
      1.1438503956168984, 1.1453026948744454, 1.1467539322126155,
      1.1482035543832805, 1.149651011934, 1.151095759408989, 1.1525372555472824,
      1.1539749634780248, 1.1554083509128394, 1.1568368903352246,
      1.158260059186921, 1.1596773400511997, 1.1610882208330291,
      1.1624921949360603, 1.1638887614363944, 1.1652774252530818,
      1.1666576973153171, 1.168029094726267, 1.1693911409235247,
      1.1707433658361086, 1.1720853060380048, 1.1734165048981959,
      1.1747365127271434, 1.1760448869196924, 1.1773411920943726,
      1.1786250002290424, 1.1798958907928758, 1.1811534508746415,
      1.1823972753072582, 1.1836269667885919, 1.1848421359984846,
      1.1860424017119795, 1.1872273909087292, 1.1883967388785566,
      1.1895500893231725, 1.1906870944540051, 1.1918074150861466,
      1.1929107207284, 1.1939966896693972, 1.1950650090598118,
      1.1961153749906135, 1.1971474925673964, 1.1981610759807482,
      1.1991558485726681, 1.2001315428990218, 1.2010879007880408,
      1.2020246733948561, 1.202941621252076, 1.203838514316395,
      1.2047151320112612, 1.2055712632655788, 1.2064067065484838,
      1.2072212699001579, 1.2080147709587459, 1.2087870369833305,
      1.2095379048730142, 1.2102672211821093, 1.2109748421314461,
      1.2116606336158207, 1.2123244712076013, 1.2129662401565016,
      1.2135858353855584, 1.2141831614833127, 1.2147581326922352,
      1.2153106728934082, 1.2158407155874966, 1.216348203872027,
      1.216833090415006, 1.2172953374249065, 1.2177349166170515,
      1.2181518091764194, 1.2185460057169195, 1.2189175062371504,
      1.2192663200726888, 1.219592465844936, 1.219895971406576, 1.22017687378365,
      1.2204352191143255, 1.2206710625843593, 1.2208844683593327,
      1.2210755095136716, 1.2212442679565128, 1.2213908343544428,
      1.2215153080511769, 1.2216177969841959, 1.2216984175984138,
      1.221757294756902, 1.2217945616487345, 1.2218103596939849,
      1.221804838445951, 1.2217781554906251, 1.221730476343496,
      1.2216619743437005, 1.2215728305456011, 1.2214632336078435,
      1.2213333796799204, 1.2211834722863435, 1.2210137222084261,
      1.2208243473637732, 1.2206155726835251, 1.2203876299873917,
      1.2201407578565659, 1.2198752015045546, 1.2195912126459931,
      1.2192890493634967, 1.2189689759726237, 1.2186312628849865,
      1.2182761864695955, 1.2179040289124812, 1.2175150780746649,
      1.2171096273485327, 1.2166879755126783, 1.2162504265852787,
      1.2157972896760667, 1.2153288788369534, 1.2148455129113784,
      1.2143475153824346, 1.2138352142198507, 1.2133089417258793,
      1.212769034380158, 1.2122158326836108, 1.2116496810014565,
      1.2110709274053801, 1.2104799235149333, 1.2098770243382386,
      1.2092625881120453, 1.2086369761412104, 1.2080005526376747,
      1.2073536845589814, 1.2066967414464191, 1.2060300952628364,
      1.2053541202302078, 1.2046691926670063, 1.2039756908254355,
      1.2032739947286164, 1.2025644860077433, 1.2018475477393269,
      1.2011235642825409, 1.2003929211167561, 1.1996560046793225,
      1.1989132022036602, 1.1981649015577129, 1.1974114910828284,
      1.1966533594331452, 1.1958908954154992, 1.1951244878299667,
      1.1943545253110566, 1.1935813961696358, 1.1928054882356416,
      1.1920271887016194, 1.1912468839671815, 1.1904649594844061,
      1.1896817996042433, 1.188897787424001, 1.188113304635936,
      1.1873287313770313, 1.1865444460799928, 1.1857608253255274,
      1.1849782436959584, 1.1841970736302152, 1.1834176852802671,
      1.1826404463690325, 1.1818657220498285, 1.1810938747673909,
      1.1803252641205348, 1.179560246726485, 1.178799176086923,
      1.1780424024558169, 1.1772902727090386, 1.1765431302158553,
      1.1758013147123156, 1.1750651621765567, 1.174335004706117,
      1.173611170397252, 1.172893983226307, 1.1721837629332035,
      1.1714808249070399, 1.1707854800738764, 1.1700980347867174,
      1.1694187907177427, 1.1687480447528045, 1.1680860888882363,
      1.1674332101299896, 1.1667896903951573, 1.1661558064158721,
      1.1655318296456494, 1.1649180261681749, 1.1643146566085711,
      1.1637219760471751, 1.1631402339358461, 1.1625696740168154,
      1.162010534244124, 1.1614630467076574, 1.1609274375597829,
      1.1604039269446442, 1.1598927289300911, 1.1593940514422898,
      1.1589080962030238, 1.1584350586696885, 1.1579751279780059,
      1.1575284868874762, 1.1570953117295506, 1.1566757723585728,
      1.1562700321054804, 1.1558782477342611, 1.1555005694012059,
      1.155137140616924, 1.1547880982111642, 1.1544535723004208,
      1.1541336862583387, 1.1538285566889013, 1.153538293402449,
      1.1532629993944647, 1.15300277082717, 1.1527576970139177,
      1.1525278604063842, 1.1523133365845319, 1.1521141942493693,
      1.1519304952184755, 1.1517622944243078, 1.1516096399152702,
      1.1514725728595154, 1.1513511275514989, 1.1512453314212758,
      1.1511552050464928, 1.1510807621670982, 1.1510220097027384,
      1.1509789477728316, 1.1509515697192829, 1.1509398621318787,
      1.1509438048762513, 1.1509633711245044, 1.1509985273883663,
      1.1510492335549576, 1.1511154429250523, 1.1511971022539005,
      1.1512941517945112, 1.1514065253434291, 1.1515341502889456,
      1.1516769476617212, 1.1518348321878142, 1.1520077123440677,
      1.1521954904158347, 1.1523980625569932, 1.1526153188522548,
      1.1528471433817176, 1.1530934142876141, 1.1533540038432624,
      1.1536287785241386, 1.1539175990810915, 1.1542203206156041,
      1.1545367926571342, 1.1548668592424147, 1.1552103589967828,
      1.1555671252173796, 1.155936985958298, 1.1563197641175536,
      1.1567152775258847, 1.1571233390373346, 1.1575437566215598,
      1.1579763334578441, 1.1584208680307577, 1.1588771542274448,
      1.1593449814364634, 1.1598241346481812, 1.1603143945566148,
      1.1608155376627418, 1.1613273363792129, 1.1618495591363827,
      1.1623819704896987, 1.1629243312282871, 1.1634763984848195,
      1.1640379258465068, 1.1646086634672383, 1.1651883581807845,
      1.1657767536150418, 1.1663735903072476, 1.166978605820147,
      1.167591534859032, 1.1682121093896234, 1.1688400587567618,
      1.1694751098038076, 1.1701169869927781, 1.1707654125250897,
      1.1714201064629342, 1.1720807868511689, 1.1727471698397438,
      1.1734189698065536, 1.1740958994806909, 1.1747776700660706,
      1.1754639913653417, 1.1761545719040694, 1.1768491190551023,
      1.1775473391631124, 1.1782489376692376, 1.1789536192357855,
      1.1796610878709484, 1.1803710470534652, 1.1810831998572209,
      1.1817972490756861, 1.1825128973461982, 1.1832298472739811,
      1.1839478015559206, 1.1846664631039661, 1.1853855351682165,
      1.1861047214595253, 1.1868237262716803, 1.1875422546030507,
      1.188260012277667, 1.1889767060657042, 1.1896920438033141,
      1.1904057345117423, 1.1911174885157161, 1.191827017561051,
      1.1925340349313975, 1.1932382555641405, 1.1939393961653693,
      1.1946371753238689, 1.1953313136241486, 1.1960215337583671,
      1.1967075606372268, 1.1973891214996852, 1.1980659460215519,
      1.1987377664228169, 1.1994043175737898, 1.2000653370998973,
      1.2007205654851929, 1.2013697461744839, 1.2020126256740613,
      1.2026489536509954, 1.2032784830309529, 1.203900970094508,
      1.2045161745719088, 1.2051238597362681, 1.2057237924951454,
      1.2063157434804688, 1.2068994871368157, 1.2074748018079438,
      1.2080414698216257, 1.2085992775726819, 1.2091480156042453,
      1.2096874786871756, 1.2102174658976415, 1.2107377806928157,
      1.2112482309846615, 1.2117486292117903, 1.2122387924093652,
      1.2127185422770217, 1.2131877052447924, 1.2136461125369946,
      1.2140936002340843, 1.2145300093324363, 1.2149551858020378,
      1.2153689806420758, 1.2157712499344051, 1.2161618548948625,
      1.2165406619224439, 1.216907542646281, 1.2172623739704556,
      1.2176050381165882, 1.2179354226642278, 1.2182534205890039,
      1.2185589302985442, 1.2188518556661383, 1.2191321060621443,
      1.2193995963831237, 1.2196542470787004, 1.2198959841761425,
      1.220124739302642, 1.2203404497053074, 1.2205430582688546,
      1.2207325135309943, 1.2209087696955114, 1.2210717866430367,
      1.2212215299395133, 1.2213579708423468, 1.2214810863042522,
      1.2215908589747915, 1.2216872771996061, 1.2217703350173499,
      1.2218400321543263, 1.2218963740168267, 1.2219393716811904,
      1.2219690418815805, 1.22198540699549, 1.221988495026985,
      1.2219783395876915, 1.221954979875538, 1.221918460651269,
      1.221868832212734, 1.221806150366967, 1.2217304764000727,
      1.221641877044934, 1.2215404244467469, 1.2214261961264086,
      1.2212992749417735, 1.221159749046794, 1.2210077118485538,
      1.2208432619622354, 1.2206665031640183, 1.2204775443419407,
      1.2202764994447464, 1.2200634874287311, 1.2198386322026153,
      1.2196020625704747, 1.2193539121727308, 1.219094319425259,
      1.2188234274565972, 1.2185413840433321, 1.2182483415436347,
      1.2179444568290239, 1.2176298912143448, 1.2173048103860249,
      1.2169693843286038, 1.2166237872495973, 1.2162681975027045,
      1.2159027975094017, 1.2155277736789483, 1.2151433163268412,
      1.2147496195917424, 1.2143468813509288, 1.2139353031342817,
      1.213515090036857, 1.213086450630074, 1.2126495968715607,
      1.2122047440136685, 1.2117521105107374, 1.2112919179250909,
      1.210824390831863, 1.2103497567226218, 1.2098682459079091,
      1.209380091418647, 1.208885528906539, 1.2083847965434271,
      1.2078781349196979, 1.2073657869417513, 1.2068479977285773,
      1.2063250145074955, 1.2057970865090624, 1.2052644648612389,
      1.2047274024828112, 1.2041861539761292, 1.2036409755192268,
      1.2030921247572879, 1.2025398606936284, 1.2019844435800848,
      1.2014261348069961, 1.2008651967927051, 1.2003018928727103,
      1.1997364871884375, 1.1991692445757538, 1.1986004304531745,
      1.1980303107099011, 1.1974591515936512, 1.1968872195983919,
      1.1963147813519615, 1.1957421035036737, 1.1951694526119132,
      1.1945970950317755, 1.1940252968028087, 1.1934543235368691,
      1.1928844403061742, 1.1923159115315827, 1.1917490008710818,
      1.1911839711086689, 1.190621084043499, 1.190060600379488,
      1.1895027796153097, 1.1889478799348909, 1.1883961580984148,
      1.1878478693339107, 1.1873032672293995, 1.1867626036257506,
      1.1862261285101634, 1.1856940899104171, 1.1851667337898821,
      1.1846443039433234, 1.1841270418935816, 1.1836151867891249,
      1.1831089753025383, 1.1826086415299841, 1.182114416891662,
      1.18162653003334, 1.1811452067289272, 1.1806706697842237,
      1.1802031389417913, 1.1797428307870361, 1.1792899586555243,
      1.1788447325415792, 1.178407359008157, 1.1779780410981042,
      1.1775569782467528, 1.1771443661959364, 1.176740396909485,
      1.1763452584901357, 1.1759591350980099, 1.1755822068705934,
      1.1752146498443208, 1.174856635877729, 1.1745083325762884,
      1.1741699032188679, 1.1738415066858909, 1.1735232973892498,
      1.1732154252039251, 1.1729180354014173, 1.1726312685849678,
      1.1723552606266121, 1.1720901426060848, 1.1718360407516273,
      1.1715930763826592, 1.1713613658544226, 1.17114102050455,
      1.1709321466016045, 1.1707348452956334, 1.1705492125707082,
      1.1703753391995295, 1.1702133107000559, 1.170063207294231,
      1.1699251038687724, 1.1697990699380925, 1.1696851696093207,
      1.1695834615494745, 1.1694939989547777, 1.1694168295221492,
      1.1693519954228568, 1.1692995332783767, 1.1692594741384488,
      1.1692318434613393, 1.169216661096333, 1.1692139412684559,
      1.169223692565422, 1.1692459179268586, 1.1692806146357464,
      1.1693277743121497, 1.169387382909187, 1.1694594207112921,
      1.1695438623347121, 1.1696406767303287, 1.1697498271886972,
      1.16987127134741, 1.1700049612007035, 1.1701508431113534, 1.17030885782484,
      1.1704789404857885, 1.1706610206566634, 1.1708550223387428,
      1.1710608639953339, 1.1712784585772502, 1.1715077135505294,
      1.1717485309263993, 1.1720008072934451, 1.1722644338520387,
      1.1725392964509278, 1.17282527562608, 1.1731222466416551,
      1.1734300795332115, 1.1737486391530185, 1.174077785217567,
      1.174417372357162, 1.1747672501676916, 1.1751272632644365,
      1.1754972513380111, 1.1758770492123372, 1.1762664869046844,
      1.1766653896877319, 1.1770735781536357, 1.1774908682800826,
      1.1779170714983087, 1.1783519947630658, 1.17879544062449,
      1.1792472073018816, 1.1797070887593546, 1.1801748747833092,
      1.1806503510617568, 1.1811332992653947, 1.1816234971304902,
      1.1821207185434608, 1.1826247336271902, 1.1831353088289995,
      1.1836522070102773, 1.1841751875377298, 1.1847040063762053,
      1.1852384161830729, 1.1857781664041327, 1.1863230033709986,
      1.1868726703999324, 1.1874269078921205, 1.1879854534353023,
      1.1885480419067656, 1.1891144055776508, 1.1896842742185152,
      1.1902573752061647, 1.1908334336316533, 1.191412172409466,
      1.1919933123878106, 1.1925765724600075, 1.1931616696769023,
      1.1937483193603073, 1.194336235217387, 1.1949251294559728,
      1.1955147129007637, 1.196104695110346, 1.1966947844950431,
      1.1972846884354862, 1.1978741134019146, 1.1984627650741408,
      1.1990503484621415, 1.1996365680272143, 1.2002211278037003,
      1.2008037315211681, 1.20138408272706, 1.2019618849097473,
      1.2025368416219093, 1.2031086566042732, 1.203677033909575,
      1.2042416780267671, 1.204802294005384, 1.2053585875800348, 1.205910265295,
      1.2064570346288244, 1.2069986041189316, 1.2075346834861567,
      1.2080649837591826, 1.2085892173988173, 1.2091070984220802,
      1.2096183425260292, 1.2101226672113059, 1.2106197919053221,
      1.2111094380850707, 1.2115913293994987, 1.2120651917913963,
      1.2125307536187544, 1.2129877457755365, 1.2134359018118526,
      1.2138749580534243, 1.2143046537203703, 1.2147247310452094,
      1.2151349353900387, 1.2155350153628945, 1.2159247229331642,
      1.2163038135460873, 1.2166720462362428, 1.2170291837399991,
      1.2173749926068824, 1.2177092433098184, 1.2180317103541771,
      1.2183421723856429, 1.2186404122967673, 1.2189262173322639,
      1.2191993791929197, 1.2194596941381162, 1.2197069630869448,
      1.2199409917177966, 1.2201615905664696, 1.2203685751226963,
      1.2205617659250676, 1.220740988654317, 1.2209060742249178,
      1.2210568588749624, 1.2211931842542654, 1.221314897510672,
      1.2214218513745265, 1.2215139042412546, 1.2215909202520434,
      1.221652769372553, 1.2216993274696444, 1.221730476386083,
      1.2217461040131929, 1.2217461043613917, 1.2217303776286248,
      1.2216988302666161, 1.2216513750449451, 1.2215879311128701,
      1.2215084240589331, 1.2214127859682395, 1.2213009554774392,
      1.2211728778273627, 1.2210285049132688, 1.220867795332701,
      1.220690714430912, 1.220497234343821, 1.2202873340385052,
      1.2200609993511737, 1.2198182230226047, 1.2195590047310483,
      1.2192833511225316, 1.2189912758385795, 1.2186827995413119,
      1.2183579499358876, 1.2180167617903253, 1.2176592769526036,
      1.2172855443651025, 1.2168956200763157, 1.2164895672498328,
      1.2160674561705966, 1.215629364248388, 1.2151753760185522,
      1.2147055831399385, 1.2142200843900466, 1.2137189856573716,
      1.2132023999309371, 1.2126704472870062, 1.2121232548729632,
      1.2115609568883527, 1.2109836945630894, 1.210391616132809,
      1.209784876811375, 1.2091636387605291, 1.2085280710566844,
      1.2078783496548622, 1.2072146573497746, 1.2065371837340402,
      1.205846125153555, 1.2051416846600065, 1.2044240719605395,
      1.2036935033645697, 1.2029502017277751, 1.2021943963932427,
      1.2014263231297846, 1.2006462240674594, 1.1998543476302621,
      1.199050948466033, 1.1982362873735748, 1.197410631227001,
      1.1965742528973218, 1.1957274311712816, 1.1948704506674728,
      1.194003601749734, 1.1931271804378456, 1.1922414883155561,
      1.1913468324359435, 1.1904435252241352, 1.1895318843774141,
      1.1886122327627264, 1.1876848983116164, 1.1867502139126094,
      1.1858085173010724, 1.1848601509465719, 1.1839054619377642,
      1.1829448018648396, 1.1819785266995402, 1.1810069966728083,
      1.1800305761500618, 1.1790496335041516, 1.178064540986026,
      1.1770756745931295, 1.17608341393558, 1.1750881421001484, 1.17409024551209,
      1.173090113794846, 1.1720881396276663, 1.1710847186011935,
      1.1700802490710276, 1.1690751320093415, 1.1680697708545547,
      1.1670645713591343, 1.1660599414355495, 1.1650562910004285,
      1.1640540318169552, 1.1630535773355666, 1.1620553425329696,
      1.1610597437495522, 1.1600671985252076, 1.1590781254336486,
      1.1580929439152305, 1.1571120741083496, 1.15613593667947,
      1.1551649526518057, 1.1541995432327381, 1.1532401296400034,
      1.1522871329266935, 1.1513409738051541, 1.1504020724697928,
      1.1494708484188878, 1.1485477202754277, 1.1476331056070435,
      1.1467274207450942, 1.1458310806029555, 1.1449444984935702,
      1.1440680859463133, 1.1432022525232401, 1.1423474056347653,
      1.1415039503548257, 1.1406722892356067, 1.1398528221218742,
      1.1390459459649678, 1.138252054636532, 1.1374715387420431,
      1.136704785434161, 1.1359521782260289, 1.1352140968045081,
      1.134490916843472, 1.1337830098171933, 1.133090742813869,
      1.1324144783493941, 1.1317545741813935, 1.1311113831236119,
      1.1304852528607137, 1.1298765257635419, 1.1292855387049232,
      1.128712622876062, 1.1281581036036039, 1.1276223001674173,
      1.1271055256191631, 1.1266080866017232, 1.126130283169533, 1.1256724086099,
      1.1252347492653709, 1.1248175843571886, 1.1244211858099356,
      1.1240458180773991, 1.1236917379697384, 1.1233591944820145,
      1.1230484286241367, 1.1227596732522946, 1.1224931529019537,
      1.1222490836224401, 1.1220276728132215, 1.1218291190619063,
      1.121653611984055, 1.1215013320648484, 1.1213724505026659,
      1.1212671290546705, 1.1211855198844087, 1.1211277654115406,
      1.1210939981637196, 1.1210843406306947, 1.1210989051207114,
      1.1211377936192366, 1.121201097650091, 1.1212888981390525,
      1.1214012652799519, 1.1215382584033713, 1.1216999258479365,
      1.1218863048343315, 1.1220974213420372, 1.1223332899888538,
      1.1225939139133074, 1.1228792846599229, 1.1231893820674812,
      1.1235241741602777, 1.1238836170424349, 1.1242676547953356,
      1.1246762193782232, 1.1251092305319932, 1.1255665956862768,
      1.1260482098698028, 1.1265539556241382, 1.1270837029208198,
      1.127637309081938, 1.1282146187042206, 1.1288154635866365,
      1.1294396626616072, 1.1300870219298096, 1.1307573343986705,
      1.1314503800245577, 1.1321659256587013, 1.1329037249969227,
      1.1336635185331716, 1.1344450335169118, 1.1352479839144247,
      1.1360720703740148, 1.1369169801951955, 1.1377823873018669,
      1.1386679522195056, 1.1395733220564352, 1.1404981304891586,
      1.1414419977518264, 1.1424045306298345, 1.1433853224575921,
      1.1443839531204905, 1.1453999890610775, 1.1464329832894835,
      1.1474824753981097, 1.1485479915805814, 1.1496290446550317,
      1.1507251340916804, 1.1518357460447619, 1.1529603533888086,
      1.1540984157592913, 1.15524937959765, 1.1564126782007103,
      1.1575877317745076, 1.1587739474925305, 1.1599707195583653,
      1.161177429272793, 1.1623934451053055, 1.163618122770063,
      1.1648508053063011, 1.1660908231631633, 1.167337494289008,
      1.16859012422512, 1.1698480062038941, 1.1711104212514509,
      1.1723766382946699, 1.1736459142726714, 1.1749174942527021,
      1.176190611550439, 1.1774644878546925, 1.1787383333565009,
      1.1800113468825997, 1.1812827160332577, 1.1825516173244461,
      1.1838172163343677, 1.1850786678542569, 1.1863351160435172,
      1.187585694589095, 1.1888295268691238, 1.1900657261207823,
      1.1912933956123688, 1.1925116288195277, 1.1937195096056521,
      1.1949161124063787, 1.1961005024181872, 1.1972717357910496,
      1.1984288598251043, 1.1995709131713217, 1.2006969260361198,
      1.2018059203898996, 1.2028969101794544, 1.2039689015442263,
      1.2050208930363504, 1.2060518758444667, 1.2070608340212277,
      1.2080467447144938, 1.2090085784021323, 1.2099452991304027,
      1.2108558647558603, 1.2117392271907397, 1.2125943326517619,
      1.213420121912312, 1.2142155305579383, 1.214979489245114,
      1.2157109239632085, 1.2164087562996064, 1.2170719037079234,
      1.217699279779253, 1.2182897945163835, 1.2188423546109335,
      1.2193558637233217, 1.2198292227655358, 1.2202613301866083,
      1.2206510822607486, 1.220997373378061, 1.2212990963377768,
      1.2215551426439359, 1.2217644028034409, 1.2219257666264229,
      1.2220381235288311, 1.222100362837188, 1.2221113740954279,
      1.2220700473737409, 1.2219752735793539, 1.2218259447691679,
      1.2216209544641627, 1.2213591979655176, 1.221039572672332,
      1.2206609784008959, 1.2202223177054146, 1.2197224962000981,
      1.2191604228825565, 1.2185350104583916, 1.2178451756669084,
      1.2170898396078749, 1.2162679280692223, 1.2153783718556119,
      1.2144201071177845, 1.2133920756825856, 1.2122932253836076,
      1.211122510392326, 1.2098788915496699, 1.2085613366979171,
      1.2071688210128255, 1.2057003273359279, 1.2041548465068579,
      1.2025313776956752, 1.2008289287350287, 1.1990465164521209,
      1.1971831670003505, 1.1952379161905422, 1.1932098098216914,
      1.191097904011085, 1.1889012655237581, 1.1866189721011471,
      1.1842501127888687, 1.1817937882635243, 1.1792491111584236,
      1.1766152063881499, 1.1738912114718583, 1.1710762768552192,
      1.1681695662308913, 1.165170256857474, 1.1620775398767771,
      1.1588906206293754, 1.1556087189683206, 1.1522310695708951,
      1.1487569222483807, 1.145185542253653, 1.1415162105865964,
      1.1377482242971813, 1.1338808967861254, 1.1299135581030797,
      1.1258455552421733, 1.1216762524349064, 1.1174050314402202,
      1.1130312918317093, 1.1085544512818524, 1.1039739458431679,
      1.0992892302262267, 1.0944997780744092, 1.0896050822352956,
      1.08460465502868, 1.0794980285109883, 1.0742847547361569,
      1.0689644060127497, 1.0635365751573214, 1.0580008757438897,
      1.0523569423494554, 1.0466044307954387, 1.040743018385031,
      1.0347724041362658, 1.028692309010848, 1.0225024761385273,
      1.0162026710370682, 1.0097926818276048, 1.0032723194454134,
      0.99664141784594729, 0.9898998342060672, 0.98304744912045361,
      0.97608416679300725, 0.96900991522328539, 0.96182464638779652,
      0.95452833641617529, 0.94712098576205361, 0.93960261936868716,
      0.93197328682914193, 0.92423306254105286, 0.9163820458558759,
      0.908420361222515, 0.90034815832535076, 0.892165612216489,
      0.88387292344230028, 0.87547031816406784, 0.86695804827274092,
      0.85833639149777763, 0.849605651509894, 0.840766158017828,
      0.83181826685889748, 0.82276236008342885, 0.81359884603296229,
      0.80432815941211866, 0.79495076135421394, 0.78546713948043023,
      0.77587780795261629, 0.7661833075195833, 0.75638420555693386,
      0.746481096100296, 0.73647459987202191, 0.726365364301216,
      0.71615406353712441, 0.705841398455849, 0.69542809666027949,
      0.68491491247334746, 0.67430262692440446, 0.6635920477288767,
      0.65278400926099756, 0.64187937251975369, 0.63087902508789406,
      0.61978388108403726, 0.60859488110790438, 0.5973129921785435,
      0.58593920766566965, 0.57447454721397029, 0.562920056660502,
      0.55127680794503142, 0.53954589901344563, 0.5277284537141238,
      0.51582562168730051, 0.50383857824747336, 0.49176852425873835,
      0.4796166860031929, 0.46738431504226979, 0.45507268807116025,
      0.44268310676616551, 0.430216897625156, 0.41767541180100792,
      0.40506002492811272, 0.39237213694198947, 0.37961317189190236,
      0.36678457774667689, 0.35388782619355358, 0.34092441243026628,
      0.32789585495025664, 0.31480369532107516, 0.30164949795608059,
      0.28843484987931522, 0.27516136048376261, 0.26183066128286114,
      0.24844440565546214, 0.23500426858411308, 0.22151194638687693,
      0.20796915644258318, 0.19437763690961493, 0.18073914643834793,
      0.16705546387712406, 0.15332838797200773, 0.13955973706018585,
      0.1257513487572387, 0.11190507963821383, 0.098022804912592826,
      0.084106418093285742, 0.070157830659568016, 0.056178971714201234,
      0.042171787634610047, 0.028138241718394876, 0.014080313823024387 } ;

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
      25.97, 25.98, 25.990000000000002 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.14861910779009135, 0.13396155080060912, 0.11916428796590062,
      0.10422960984797872, 0.0891598621501615, 0.073957445348745987,
      0.058624814304056388, 0.043164477850914734, 0.027578998368583019,
      0.011870991330243968, -0.0039568751679152636, -0.019901880897938012,
      -0.035961254011567384, -0.052132171571858621, -0.06841176010483363,
      -0.084797096171070729, -0.10128520695711757, -0.11787307088659771,
      -0.13455761825088947, -0.15133573185923191, -0.16820424770811668,
      -0.18515995566981044, -0.20219960019985217, -0.21931988106335013,
      -0.236517454079911, -0.25378893188701312, -0.27113088472163782,
      -0.28853984121995918, -0.3060122892348896, -0.32354467667126907,
      -0.3411334123384806, -0.35877486682026383, -0.3764653733614981,
      -0.39420122877171226, -0.41197869434507817, -0.42979399679662977,
      -0.44764332921445638, -0.46552285202759536, -0.4834286939893564,
      -0.50135695317579776, -0.51930369799906662, -0.53726496823531555,
      -0.555236776066893, -0.57321510713850554, -0.5911959216270446,
      -0.6091751553247533, -0.62714872073542494, -0.64511250818329091,
      -0.66306238693427588, -0.6809942063292781, -0.6989037969291283,
      -0.71678697167088246, -0.734639527035093, -0.75245724422369442,
      -0.77023589034814677, -0.78797121962746253, -0.8056589745957452,
      -0.82329488731885836, -0.8408746806198486, -0.85839406931273132,
      -0.875848761444243, -0.89323445954317882, -0.91054686187690292,
      -0.927781663714632, -0.9449345585970933, -0.96200123961213579,
      -0.97897740067588834, -0.99585873781904644, -1.0126409504778686,
      -1.0293197427894569, -1.0458908248909013, -1.062349914221856,
      -1.0786927368301167, -1.0949150286797713, -1.1110125369614841,
      -1.126981021404474, -1.14281625558976, -1.1585140282642177,
      -1.1740701446550172, -1.1894804277839881, -1.2047407197814817,
      -1.2198468831992626, -1.2347948023220097, -1.2495803844769502,
      -1.2641995613412049, -1.2786482902463756, -1.2929225554799386,
      -1.3070183695829865, -1.3209317746438765, -1.3346588435873292,
      -1.3481956814585339, -1.3615384267018118, -1.3746832524333856,
      -1.3876263677078138, -1.4003640187776403, -1.4128924903458193,
      -1.4252081068104641, -1.4373072335014851, -1.4491862779086784,
      -1.4608416909008135, -1.472269967935304, -1.4834676502580058,
      -1.4944313260927284, -1.5051576318200155, -1.5156432531447794,
      -1.5258849262523566, -1.5358794389525672, -1.5456236318113581,
      -1.5551143992696157, -1.5643486907487383, -1.5733235117425521,
      -1.5820359248951783, -1.5904830510644388, -1.5986620703704137,
      -1.6065702232287464, -1.6142048113683234, -1.6215631988329255,
      -1.628642812966494, -1.6354411453816113, -1.6419557529108522,
      -1.6481842585406168, -1.6541243523271065, -1.6597737922940716,
      -1.6651304053119964, -1.6701920879583612, -1.6749568073586618,
      -1.6794226020078402, -1.6835875825718096, -1.6874499326687464,
      -1.6910079096298429, -1.6942598452392046, -1.6972041464526013,
      -1.6998392960947668, -1.7021638535349692, -1.7041764553405625,
      -1.7058758159082503, -1.7072607280727943, -1.7083300636929044,
      -1.709082774214062, -1.7095178912080247, -1.7096345268887854,
      -1.7094318746047397, -1.7089092093068532, -1.7080658879926069,
      -1.7069013501255106, -1.7054151180299928, -1.7036067972614668,
      -1.7014760769513975, -1.6990227301271856, -1.6962466140067125,
      -1.6931476702673727, -1.689725925289459, -1.685981490373748,
      -1.681914561933153, -1.6775254216583257, -1.6728144366570832,
      -1.6677820595675585, -1.6624288286449695, -1.6567553678219227,
      -1.6507623867421644, -1.6444506807677097, -1.6378211309592905,
      -1.6308747040300549, -1.6236124522724864, -1.6160355134584978,
      -1.6081451107126759, -1.5999425523586541, -1.5914292317386118,
      -1.5826066270058878, -1.5734763008907311, -1.5640399004391943,
      -1.5542991567252016, -1.5442558845358323, -1.5339119820298566,
      -1.5232694303695822, -1.5123302933260789, -1.5010967168578455,
      -1.4895709286630106, -1.477755237705149, -1.4656520337128243,
      -1.4532637866529523, -1.4405930461781227, -1.4276424410479858,
      -1.4144146785248588, -1.4009125437436822, -1.3871388990564915,
      -1.3730966833515612, -1.3587889113473921, -1.3442186728617314,
      -1.3293891320557998, -1.3143035266539427, -1.2989651671388944,
      -1.2833774359228824, -1.2675437864947909, -1.2514677425436185,
      -1.2351528970584678, -1.2186029114053167, -1.2018215143808346,
      -1.1848125012434954, -1.167579732722279, -1.1501271340032264,
      -1.1324586936941492, -1.1145784627677844, -1.0964905534837013,
      -1.0781991382892786, -1.0597084487000588, -1.0410227741598239,
      -1.0221464608807174, -1.0030839106637521, -0.98383957970006819,
      -0.96441797735327572, -0.94482366492326975, -0.92506125439186437,
      -0.90513540715064467, -0.88505083271139728, -0.86481228739953542,
      -0.84442457303088325, -0.82389253557225861, -0.80322106378622338,
      -0.78241508786045055, -0.76147957802210087, -0.74041954313765745,
      -0.7192400292986264, -0.6979461183935638, -0.67654292666684734,
      -0.65503560326466292, -0.63342932876863345, -0.611729313717571,
      -0.58994079711778746, -0.56806904494245858, -0.54611934862047828,
      -0.524097023515313, -0.50200740739429539, -0.47985585888887583,
      -0.45764775594629314, -0.43538849427315846, -0.41308348577145637,
      -0.39073815696743575, -0.3683579474339187, -0.34594830820649547,
      -0.3235147001941458, -0.30106259258475149, -0.27859746124605866,
      -0.25612478712254472, -0.2336500546287609, -0.21117875003960845,
      -0.18871635987811991, -0.16626836930121275, -0.14384026048397741,
      -0.12143751100298557, -0.099065592219170162, -0.076729967660767881,
      -0.054436091406881493, -0.032189406472149039, -0.0099953431930759531,
      0.01214068238347283, 0.034213270109078785, 0.0562170373393625,
      0.078146620535839276, 0.099996676863502748, 0.1217618857836447,
      0.14343695064135137, 0.16501660024720194, 0.1864955904526083,
      0.20786870571832203, 0.22913076067555505, 0.25027660167924071,
      0.27130110835288712, 0.29219919512455211, 0.31296581275340496,
      0.33359594984638957, 0.35408463436448157, 0.37442693511805075,
      0.39461796325082349, 0.41465287371196741, 0.43452686671579871,
      0.45423518918864481, 0.47377313620236694, 0.49313605239408048,
      0.51231933337158919, 0.53131842710408428, 0.55012883529762369,
      0.56874611475495629, 0.58716587871922221, 0.60538379820108479,
      0.623395603288863, 0.6411970844412056, 0.65878409376189861,
      0.676152546256358, 0.69329842106940476, 0.710217762703895,
      0.7269066822198057, 0.74336135841336248, 0.75957803897582743,
      0.77555304163154137, 0.79128275525485292, 0.80676364096554454,
      0.82199223320239545, 0.8369651407745099, 0.85167904789006788,
      0.86613071516213325, 0.88031698059119667, 0.89423476052410011,
      0.90788105058904, 0.92125292660630587, 0.93434754547446752,
      0.9471621460316868, 0.95969404989188378, 0.9719406622554414,
      0.98389947269420552, 0.99556805591047537, 1.0069440724697509,
      1.0180252695069725, 1.0288094814060049, 1.0392946304521449,
      1.0494787274574082, 1.059359872358395, 1.0689362547865111,
      1.0782061546103587, 1.0871679424500935, 1.0958200801635782,
      1.1041611213041509, 1.112189711549856, 1.1199045891039727,
      1.1273045850667089, 1.1343886237779164, 1.1411557231307117,
      1.1476049948558749, 1.1537356447769394, 1.1595469730358554,
      1.1650383742891606, 1.1702093378745633, 1.1750594479478904,
      1.1795883835903247, 1.1837959188859, 1.1876819229692048, 1.191246360043277,
      1.194489289367664, 1.1974108652166442, 1.2000113368076175,
      1.2022910481996605, 1.2042504381622932, 1.2058900400144612,
      1.2072104814338012, 1.20821248423622, 1.2088968641258648,
      1.2092645304155432, 1.2093164857176848, 1.2090538256059278,
      1.2084777382474334, 1.207589504006038, 1.2063904950163689,
      1.204882174729041, 1.2030660974270853, 1.2009439077137529,
      1.1985173399718527, 1.1957882177947932, 1.1927584533895008,
      1.1894300469514079, 1.1858050860116995, 1.1818857447570312,
      1.1776742833219234, 1.1731730470540642, 1.1683844657527465,
      1.1633110528806849, 1.1579554047494613, 1.1523201996788552,
      1.1464081971303308, 1.1402222368149548, 1.1337652377760294,
      1.1270401974467317, 1.1200501906830689, 1.1127983687724434,
      1.1052879584181672, 1.0975222607002268, 1.0895046500126546,
      1.0812385729778304, 1.0727275473380748, 1.0639751608248817,
      1.0549850700061623, 1.0457609991118624, 1.0363067388383402,
      1.0266261451318843, 1.0167231379517696, 1.0066017000132388,
      0.99626587551083412, 0.98571976882247236, 0.97496754319469314,
      0.96401341940950624, 0.952861674433256, 0.94151664004796021,
      0.92998270146554451, 0.9182642959254409, 0.90636591127598376,
      0.89429208454008324, 0.88204740046562158, 0.869636490061059,
      0.85706402911670532, 0.84433473671215564, 0.83145337371035222,
      0.81842474123878506, 0.80525367915829826, 0.79194506452001467,
      0.77850381001087909, 0.76493486238830688, 0.75124320090446861,
      0.73743383572070131, 0.72351180631257883, 0.70948217986613171,
      0.69535004966576819, 0.68112053347439327, 0.6667987719062638,
      0.652389926793103, 0.63789917954399844, 0.62333172949962656,
      0.60869279228132445, 0.59398759813555713, 0.57922139027429176,
      0.564399423211851, 0.54952696109875, 0.53460927605308428,
      0.51965164648997764, 0.504659355449665, 0.48963768892472109,
      0.4745919341870013, 0.45952737811480227, 0.44444930552082007,
      0.42936299748142104, 0.4142737296677772, 0.39918677067938807,
      0.38410738038055192, 0.36904080824029978, 0.35399229167634805,
      0.33896705440357661, 0.3239703047875937, 0.30900723420389992,
      0.29408301540318693, 0.27920280088328547, 0.2643717212683061,
      0.24959488369547503, 0.23487737021019117, 0.22022423616982867,
      0.20564050865676983, 0.19113118490121295, 0.17670123071423216,
      0.16235557893161229, 0.14809912786893348, 0.1339367397884248,
      0.1198732393780608, 0.10591341224339598, 0.092062003412605481,
      0.078323715855226878, 0.064703209015062435, 0.051205097357716722,
      0.037833948933220091, 0.02459428395421151, 0.011490573390120301,
      -0.0014727624222015123, -0.014291355150959084, -0.026960889824573064,
      -0.039477106169077139, -0.051835799927342968, -0.0640328241597231,
      -0.076064090525673062, -0.087925570545984752, -0.099613296845203925,
      -0.11112336437386183, -0.12245193161013004, -0.13359522174051719,
      -0.1445495238192516, -0.15531119390596682, -0.16587665618136566,
      -0.17624240404048258, -0.18640500116322889, -0.1963610825618769,
      -0.20610735560516727, -0.21564060101871438, -0.22495767386140528,
      -0.23405550447749687, -0.24293109942411437, -0.25158154237386687,
      -0.2600039949923113, -0.26819569778998364, -0.27615397094876581,
      -0.28387621512230721, -0.29135991221028223, -0.29860262610624461,
      -0.30560200341885591, -0.31235577416627475, -0.31886175244349724,
      -0.325117837062464, -0.33112201216472792, -0.33687234780652919,
      -0.34236700051608654, -0.34760421382295992, -0.35258231875932577,
      -0.35729973433303208, -0.36175496797229867, -0.36594661594193612,
      -0.36987336373097851, -0.37353398641162783, -0.37692734896940439,
      -0.3800524066044404, -0.38290820500381706, -0.38549388058490908,
      -0.38780866070965336, -0.38985186386972132, -0.39162289984254073,
      -0.39312126981815176, -0.39434656649687705, -0.39529847415779945,
      -0.395976768698048, -0.3963813176429114, -0.39651208012679151,
      -0.3963691068450369, -0.39595253997668972, -0.39526261307820654,
      -0.39429965094820285, -0.39306406946329575, -0.39155637538512655,
      -0.38977716613864627, -0.38772712956176453, -0.3854070436264696,
      -0.38281777613153506, -0.37996028436693913, -0.37683561475012839,
      -0.3734449024342783, -0.36978937088869029, -0.36587033145150349,
      -0.36168918285487439, -0.35724741072282085, -0.35254658704190517,
      -0.347588369604967, -0.34237450142809622, -0.33690681014107482,
      -0.33118720735150303, -0.32521768798284323, -0.31900032958661928,
      -0.31253729162902277, -0.30583081475218038, -0.2988832200103429,
      -0.29169690808127946, -0.28427435845313626, -0.27661812858707319,
      -0.26873085305595079, -0.26061524265938429, -0.25227408351546826,
      -0.24371023612949277, -0.23492663443997275, -0.22592628484232735,
      -0.21671226519053594, -0.20728772377713545, -0.19765587829188924,
      -0.18782001475950702, -0.17778348645676256, -0.16754971280939382,
      -0.15712217826915581, -0.14650443117141487, -0.13570008257366695,
      -0.12471280507538153, -0.11354633161956998, -0.10220445427648674,
      -0.090691023009865437, -0.079009944426120179, -0.0671651805069265,
      -0.055160747325608932, -0.043000713747771424, -0.030689200116594279,
      -0.018230376923254316, -0.0056284634629040391, 0.0071122735233363783,
      0.019987521219937472, 0.0329929221215864, 0.0461240754304388,
      0.059376538465523043, 0.0727458280838481, 0.08622742211271367,
      0.099816760792777542, 0.11350924823138533, 0.12730025386570179,
      0.1411851139351426, 0.15515913296263611, 0.16921758524422403,
      0.1833557163465187, 0.197568744611518, 0.21185186266829781,
      0.22620023895107205, 0.24060901922315547, 0.25507332810629735,
      0.26958827061491852, 0.28414893369474226, 0.29875038776531693,
      0.3133876882659507, 0.328055877204532, 0.34274998470876689,
      0.35746503057929985, 0.37219602584426392, 0.3869379743147186,
      0.40168587414049961, 0.41643471936598364, 0.43117950148526757,
      0.44591521099626524, 0.46063683895323149, 0.47533937851721364,
      0.49001782650396009, 0.50466718492876073, 0.519282462547769,
      0.53385867639528906, 0.54839085331656967, 0.56287403149560666,
      0.57730326197747872, 0.59167361018474229, 0.60598015742741929,
      0.62021800240609193, 0.63438226270764686, 0.64846807629319925,
      0.66247060297775706, 0.67638502590112282, 0.69020655298963329,
      0.70393041840824433, 0.717551884002538, 0.73106624073020987,
      0.74446881008158616, 0.75775494548875055, 0.770920033722837,
      0.78395949627909589, 0.7968687907492733, 0.80964341218091618,
      0.82227889442319224, 0.83477081145881193, 0.84711477872166485,
      0.859306454399761, 0.871341540723108, 0.883215785236135,
      0.89492498205428206, 0.90646497310439433, 0.91783164934854455,
      0.92902095199094847, 0.94002887366758958, 0.95085145961823991,
      0.96148480884050935, 0.97192507522562321, 0.98216846867556906,
      0.99221125620131345, 1.0020497630017791, 1.0116803735232596,
      1.021099532498998, 1.0303037459686133, 1.0392895822771091,
      1.0480536730531829, 1.0565927141665605, 1.0649034666641055,
      1.0729827576844388, 1.0808274813508258, 1.0884345996420957,
      1.0958011432413528, 1.1029242123622729, 1.1098009775527387,
      1.1164286804756467, 1.1228046346666476, 1.1289262262686548,
      1.134790914742922, 1.1403962335565199, 1.1457397908460465,
      1.1508192700574018, 1.1556324305614869, 1.1601771082456769,
      1.164451216080933, 1.1684527446644348, 1.1721797627375943,
      1.175630417679371, 1.1788029359747596, 1.1816956236583682,
      1.1843068667330057, 1.1866351315631891, 1.188678965243519,
      1.1904369959418428, 1.1919079332171734, 1.1930905683123048,
      1.1939837744211035, 1.1945865069304324, 1.1948978036367031,
      1.1949167849370406, 1.1946426539950596, 1.1940746968812559,
      1.1932122826880303, 1.1920548636193717, 1.1906019750552239,
      1.1888532355905754, 1.1868083470493287, 1.1844670944729951,
      1.1818293460842806, 1.1788950532256379, 1.1756642502728625,
      1.1721370545238212, 1.1683136660624038, 1.1641943675978073,
      1.1597795242792608, 1.1550695834863125, 1.1500650745947989,
      1.1447666087186337, 1.1391748784275662, 1.1332906574410386,
      1.1271148002983209, 1.1206482420050674, 1.1138919976564816,
      1.1068471620372549, 1.0995149091984728, 1.091896492011676,
      1.0839932417002773, 1.0758065673485382, 1.067337955388322,
      1.0585889690638333, 1.0495612478745859, 1.0402565069968077,
      1.0306765366835489, 1.0208232016437091, 1.0106984404002628,
      1.0003042646279143, 0.989642758470462, 0.97871607783814218,
      0.96752644968520318, 0.95607617126802258, 0.94436760938402842,
      0.93240319959173423, 0.92018544541215586, 0.90771691751194861,
      0.89500025286853979, 0.88203815391759222, 0.86883338768308449,
      0.85538878489036574, 0.841707239062482, 0.82779170560012239,
      0.81364520084549341, 0.79927080113049609, 0.784671641809523,
      0.76985091627722335, 0.75481187497159286, 0.73955782436274287,
      0.72409212592769967, 0.70841819511160542, 0.69253950027566114,
      0.67645956163221421, 0.66018195016733039, 0.64371028655123352,
      0.62704824003700255, 0.61019952734786742, 0.59316791155353465,
      0.57595720093587521, 0.55857124784440859, 0.54101394754191878,
      0.52328923704064034, 0.50540109392937094, 0.48735353519192121,
      0.4691506160172883, 0.45079642860194641, 0.43229510094466056,
      0.41365079563421869, 0.39486770863046228, 0.37595006803904585,
      0.35690213288030115, 0.33772819185262193, 0.31843256209075382,
      0.29901958791940664, 0.27949363960258095, 0.25985911208901941,
      0.24012042375416429, 0.22028201513904477, 0.20034834768648394,
      0.18032390247502333, 0.16021317895096587, 0.14002069365893713,
      0.11975097897135806, 0.099408581817234248, 0.07899806241064708,
      0.058523992979334832, 0.037990956493777289, 0.017403545397152304,
      -0.0032336396634314313, -0.023915991104058287, -0.044638895669075612,
      -0.0653977356937511, -0.0861878903641153, -0.10700473697364235,
      -0.12784365217635985, -0.14870001323603046, -0.16956919927103659,
      -0.19044659249461315, -0.21132757945002531, -0.23220755224037565,
      -0.253081909752645, -0.27394605887565648, -0.29479541571155354,
      -0.31562540678050122, -0.33643147021821718, -0.357209056966047,
      -0.37795363195318493, -0.39866067527076426, -0.41932568333744791,
      -0.43994417005620889, -0.46051166796200704, -0.48102372935998955,
      -0.50147592745395464, -0.52186385746475228, -0.54218313773831162,
      -0.56242941084300557, -0.58259834465607774, -0.60268563343880333,
      -0.62268699890013413, -0.64259819124853634, -0.662414990231754,
      -0.6821332061642178, -0.70174868094185883, -0.721257289044029,
      -0.74065493852234421, -0.75993757197612166, -0.77910116751423253,
      -0.7981417397031082, -0.81705534050066664, -0.835838060175952,
      -0.854486028214248, -0.87299541420747073, -0.891362428729609,
      -0.90958332419705124, -0.92765439571355635, -0.94557198189970548,
      -0.96333246570665576, -0.98093227521399484, -0.99836788441154956,
      -1.0156358139649695, -1.0327326319649066, -1.049654954659712,
      -1.0663994471713851, -1.0829628241947424, -1.0993418506796087,
      -1.115533342495926, -1.13153416708165, -1.1473412440733211,
      -1.162951545919183, -1.1783620984747969, -1.1935699815809766,
      -1.2085723296240209, -1.2233663320781134, -1.237949234029845,
      -1.2523183366847559, -1.2664709978558593, -1.2804046324340621,
      -1.2941167128404352, -1.3076047694603166, -1.3208663910591469,
      -1.3338992251800612, -1.3467009785231612, -1.3592694173064843,
      -1.3716023676086229, -1.383697715693007, -1.395553408313811,
      -1.4071674530035467, -1.418537918342277, -1.4296629342085232,
      -1.44054069201185, -1.4511694449071753, -1.4615475079908191,
      -1.471673258478349, -1.48154513586423, -1.4911616420633895,
      -1.5005213415346716, -1.5096228613863159, -1.5184648914634742,
      -1.5270461844178618, -1.5353655557596195, -1.543421883891462,
      -1.5512141101251848, -1.5587412386806765, -1.566002336667466,
      -1.5729965340489491, -1.5797230235894062, -1.5861810607838973,
      -1.5923699637711828, -1.5982891132297685, -1.6039379522572252,
      -1.6093159862328943, -1.6144227826641437, -1.6192579710162873,
      -1.6238212425263452, -1.6281123500007613, -1.6321311075972793,
      -1.6358773905910919, -1.6393511351254559, -1.6425523379469396,
      -1.6454810561254667, -1.6481374067593315, -1.6505215666653874,
      -1.6526337720545643, -1.6544743181929205, -1.6560435590484275,
      -1.6573419069236603, -1.6583698320746161, -1.6591278623158485,
      -1.6596165826121274, -1.6598366346568403, -1.6597887164373315,
      -1.65947358178741, -1.6588920399272382, -1.6580449549908161,
      -1.6569332455412893, -1.655557884074319, -1.6539198965097104,
      -1.6520203616715707, -1.6498604107571977, -1.6474412267949448,
      -1.6447640440913154, -1.6418301476675017, -1.6386408726856159,
      -1.635197603864879, -1.6315017748879754, -1.6275548677978551,
      -1.6233584123852078, -1.6189139855668639, -1.6142232107553898,
      -1.6092877572201019, -1.6041093394397699, -1.5986897164472742,
      -1.5930306911664369, -1.5871341097413205, -1.5810018608582337,
      -1.574635875060695, -1.568038124057634, -1.5612106200250604,
      -1.5541554149014818, -1.5468745996773263, -1.5393703036786202,
      -1.5316446938451687, -1.5236999740035475, -1.5155383841350989,
      -1.5071621996392417, -1.4985737305923279, -1.4897753210023092,
      -1.4807693480594766, -1.4715582213835283, -1.4621443822672036,
      -1.4525303029167755, -1.4427184856896169, -1.4327114623291217,
      -1.4225117931972213, -1.4121220665047425, -1.4015448975398745,
      -1.3907829278949784, -1.3798388246919826, -1.3687152798066329,
      -1.3574150090918187, -1.345940751600224, -1.3342952688065508,
      -1.322481343829552, -1.3105017806540953, -1.2983594033535228,
      -1.2860570553125139, -1.2735975984506882, -1.2609839124471924,
      -1.2482188939664707, -1.2353054558854784, -1.2222465265225213,
      -1.2090450488679703, -1.1957039798170612, -1.1822262894049864,
      -1.1686149600444886, -1.154872985766181, -1.141003371461792,
      -1.1270091321305322, -1.1128932921287937, -1.0986588844233696,
      -1.0843089498483955, -1.069846536366224, -1.0552746983323562,
      -1.0405964957647065, -1.0258149936173027, -1.0109332610586625,
      -0.99595437075497062, -0.98088139815826225, -0.96571742079978073,
      -0.95046551758864761, -0.935128768116061, -0.9197102519651027,
      -0.90421304802639058, -0.888640233819682, -0.87299488482157883,
      -0.85728007379949778, -0.84149887015203584, -0.82565433925585685,
      -0.80974954181927061, -0.793787533242581, -0.77777136298538085,
      -0.76170407394088557, -0.745588701817437, -0.72942827452728309,
      -0.713225811582766, -0.69698432349999373, -0.68070681121014087,
      -0.66439626547843089, -0.64805566633093836, -0.6316879824892877,
      -0.61529617081333154, -0.5988831757518992, -0.58245192880170293,
      -0.56600534797446467, -0.54954633727235513, -0.53307778617181023,
      -0.51660256911576408, -0.500123545014408, -0.48364355675450355,
      -0.46716543071730654, -0.45069197630515989, -0.43422598547680535,
      -0.41777023229143978, -0.40132747246159695, -0.38490044291482572,
      -0.3684918613642662, -0.35210442588810936, -0.33574081451797566,
      -0.31940368483624609, -0.303095673582346, -0.28681939626800812,
      -0.27057744680152879, -0.25437239712100596, -0.23820679683659007,
      -0.22208317288172877, -0.20600402917341121, -0.18997184628140018,
      -0.17398908110645622, -0.15805816656752175, -0.14218151129786383,
      -0.12636149935016217, -0.11060048991048614, -0.094900817021187883,
      -0.079264789312639333, -0.06369468974380374, -0.048192775351600006,
      -0.032761277009023475, -0.017402399191987633, -0.0021183197548449153,
      0.013088810285481896, 0.028216866956768998, 0.043263753530236738,
      0.058227400710824079, 0.073105766819039075, 0.087896837964450664,
      0.10259862821088561, 0.11720917973337527, 0.13172656296695853,
      0.14614887674736135, 0.16047424844365846, 0.17470083408297549,
      0.18882681846730837, 0.20285041528254036, 0.2167698671997324,
      0.23058344596877164, 0.24428945250445108, 0.25788621696508762,
      0.27137209882373714, 0.28474548693211432, 0.29800479957730164,
      0.31114848453133837, 0.32417501909378338, 0.33708291012735059,
      0.34987069408669369, 0.36253693704048384, 0.37508023468681667,
      0.38749921236209806, 0.39979252504348761, 0.41195885734500676,
      0.4239969235074143, 0.4359054673819569, 0.44768326240809131,
      0.45932911158529638, 0.47084184743907043, 0.48222033198122816,
      0.49346345666460384, 0.50457014233226916, 0.5155393391613734,
      0.52637002660171972, 0.53706121330918677, 0.54761193707409439,
      0.55802126474465585, 0.56828829214558652, 0.5784121439920098,
      0.5883919737987614, 0.598226963785204, 0.60791632477566471,
      0.61745929609560479, 0.62685514546363441, 0.63610316887948659,
      0.64520269050805268, 0.65415306255959926, 0.66295366516627086,
      0.67160390625498856, 0.68010322141685875, 0.68845107377319648,
      0.69664695383826281, 0.70469037937885293, 0.712580895270805,
      0.72031807335256126, 0.72790151227587541, 0.73533083735377991,
      0.74260570040590368, 0.74972577960126008, 0.75669077929859074,
      0.76350042988437683, 0.7701544876086136, 0.77665273441844385,
      0.78299497778976068, 0.789181050556857, 0.79521081074023181,
      0.80108414137264317, 0.80680095032349419, 0.81236117012165454,
      0.81776475777680235, 0.82301169459936752, 0.828101986019175,
      0.833035661402872, 0.83781277387021347, 0.84243340010930012,
      0.84689764019084479, 0.85120561738153921, 0.855357477956624,
      0.85935339101170016, 0.86319354827389638, 0.86687816391242645,
      0.87040747434863686, 0.87378173806561243, 0.87700123541738007,
      0.88006626843781155, 0.88297716064925758, 0.88573425687100815,
      0.88833792302760894, 0.89078854595710755, 0.89308653321928533,
      0.89523231290392558, 0.89722633343917713, 0.89906906340005333,
      0.90076099131712739, 0.90230262548546269, 0.90369449377382383,
      0.90493714343422149, 0.90603114091181547, 0.906977071655233,
      0.90777553992731908, 0.90842716861637529, 0.9089325990479139,
      0.90929249079694408, 0.9095075215008448, 0.909578386672825,
      0.90950579951602628, 0.909290490738266, 0.90893320836745506,
      0.90843471756770966, 0.90779580045617181, 0.9070172559205617,
      0.90609989943746472, 0.90504456289137791, 0.9038520943945163,
      0.90252335810739315, 0.90105923406018784, 0.899460617974887,
      0.89772842108822637, 0.89586356997541161, 0.893867006374641,
      0.8917396870124118, 0.88948258342960951, 0.88709668180838452,
      0.88458298279979153, 0.881942501352208, 0.87917626654049874,
      0.87628532139592652, 0.87327072273679374, 0.87013354099979923,
      0.86687486007210113, 0.86349577712405445, 0.85999740244262146,
      0.85638085926541807, 0.85264728361538633, 0.84879782413607,
      0.84483364192746024, 0.84075591038239661, 0.83656581502347926,
      0.83226455334049942, 0.8278533346283159, 0.82333337982517785,
      0.81870592135145526, 0.81397220294873529, 0.809133479519274,
      0.8041910169657388, 0.79914609203123388, 0.793999992139561,
      0.78875401523567579, 0.78340946962631564, 0.77796767382074272,
      0.772429956371584, 0.76679765571570491, 0.76107212001510827,
      0.75525470699778319, 0.74934678379849073, 0.74334972679943034,
      0.73726492147074663, 0.7310937622108451, 0.72483765218645646,
      0.71849800317242685, 0.71207623539116593, 0.705573777351737,
      0.69899206568853067, 0.69233254499947694, 0.685596667683757,
      0.67878589377897436, 0.6719016907977321, 0.6649455335635841,
      0.65791890404630815, 0.65082329119646243, 0.64366019077917946,
      0.63643110520715884, 0.62913754337281369, 0.62178102047952954,
      0.61436305787199175, 0.60688518286554494, 0.5993489285745438,
      0.591755833739644, 0.58410744255401159, 0.57640530448839866,
      0.56865097411504939, 0.56084601093040576, 0.552991979176565,
      0.54509044766146, 0.53714298957773532, 0.52915118232025538,
      0.521116607302245, 0.51304084977002051, 0.50492549861626057,
      0.49677214619181065, 0.48858238811597654, 0.48035782308528763,
      0.47210005268069466, 0.46381068117318847, 0.45549131532778775,
      0.44714356420591117, 0.43876903896607827, 0.43036935266293452,
      0.42194612004457516, 0.41350095734815112, 0.40503548209373919,
      0.39655131287646744, 0.38805006915686058, 0.37953337104942253,
      0.37100283910942378, 0.36246009411788371, 0.35390675686476203,
      0.34534444793031882, 0.33677478746466682, 0.32819939496549766,
      0.31961988905398375, 0.31103788724886128, 0.30245500573868334,
      0.2938728591522613, 0.28529306032728946, 0.27671722007715893,
      0.2681469469559819, 0.25958384702181858, 0.25102952359813008,
      0.24248557703348159, 0.23395360445947044, 0.22543519954695646,
      0.2169319522605615, 0.2084454486114895, 0.19997727040867624,
      0.19152899500830156, 0.1831021950616824, 0.17469843826158468,
      0.16631928708697913, 0.15796629854626532, 0.14964102391901948,
      0.14134500849627576, 0.13307979131940151, 0.12484690491759251,
      0.11664787504402618, 0.10848422041073474, 0.10035745242223026,
      0.092269074907914556, 0.084220583853359232, 0.076213467130467449,
      0.068249204226601745, 0.060329265972706408, 0.052455114270495651,
      0.044628201818761676, 0.0368499718388611, 0.029121857799434658,
      0.021445283140439309, 0.013821660996542695, 0.0062523939199411183,
      -0.0012611263973058839, -0.0087175194013863755, -0.016115415955195111,
      -0.023453458617085116, -0.030730301919832975, -0.03794461264974,
      -0.045095070125792641, -0.052180366478806778, -0.05919920693047076,
      -0.0661503100722127, -0.073032408143806682, -0.079844247311625122,
      -0.086584587946463676, -0.093252204900854063, -0.099845887785759146,
      -0.1063644412465872, -0.11280668523840015, -0.11917145530026055,
      -0.1254576028286116, -0.13166399534957846, -0.137789516790126,
      -0.14383306774795346, -0.14979356576004893, -0.15566994556979163,
      -0.16146115939250361, -0.16716617717936638, -0.17278398687959368,
      -0.17831359470074404, -0.18375402536710755, -0.18910432237604008,
      -0.19436354825213298, -0.19953078479914876, -0.20460513334959018,
      -0.20958571501181014, -0.21447167091456593, -0.2192621624488881,
      -0.22395637150718731, -0.22855350071948782, -0.23305277368666022,
      -0.237453435210582, -0.24175475152109063, -0.24595601049963933,
      -0.25005652189956007, -0.25405561756279205, -0.25795265163301512,
      -0.26174700076504775, -0.26543806433042894, -0.26902526461906034,
      -0.27250804703682513, -0.27588588029904954, -0.27915825661974347,
      -0.28232469189648135, -0.28538472589084063, -0.28833792240429479,
      -0.29118386944944913, -0.2939221794165266, -0.29655248923501976,
      -0.29907446053036874, -0.301487779775609, -0.30379215843788243,
      -0.30598733311968157, -0.30807306569479936, -0.31004914343881268,
      -0.31191537915407286, -0.31367161128907278, -0.31531770405211412,
      -0.31685354751918288, -0.31827905773595561, -0.31959417681382357,
      -0.32079887301988974, -0.32189314086081566, -0.3228770011604693,
      -0.3237505011312739, -0.32451371443918137, -0.3251667412622013,
      -0.32570970834241753, -0.32614276903139028, -0.32646610332890491,
      -0.32667991791498424, -0.3267844461750915, -0.32677994821847189,
      -0.32666671088955862, -0.32644504777238675, -0.32611529918795978,
      -0.32567783218450119, -0.325133040520549, -0.32448134464083528,
      -0.32372319164489061, -0.32285905524835135, -0.32188943573689438,
      -0.32081485991277869, -0.31963588103394525, -0.3183530787456299,
      -0.31696705900446576, -0.31547845399504365, -0.313887922038881,
      -0.31219614749579189, -0.31040384065762583, -0.30851173763434986,
      -0.30652060023245908, -0.30443121582569344, -0.30224439721805241,
      -0.29996098249909253, -0.29758183489149592, -0.29510784259091449,
      -0.29253991859807621, -0.28987900054315408, -0.28712605050241025,
      -0.28428205480710789, -0.28134802384471147, -0.27832499185237924,
      -0.27521401670276058, -0.27201617968212732, -0.26873258526084587,
      -0.26536436085622078, -0.26191265658773716, -0.25837864502472729,
      -0.25476352092649568, -0.2510685009749406, -0.247294823499704,
      -0.24344374819590309, -0.23951655583447246, -0.23551454796517327,
      -0.23143904661233083, -0.22729139396333153, -0.2230729520499494,
      -0.21878510242256416, -0.2144292458173247, -0.21000680181633891,
      -0.20551920850093172, -0.2009679220980721, -0.1963544166200315,
      -0.19168018349734672, -0.1869467312051746, -0.18215558488312086,
      -0.17730828594862982, -0.17240639170402067, -0.16745147493727458,
      -0.16244512351664445, -0.15738893997921319, -0.15228454111348638,
      -0.1471335575361131, -0.14193763326287437, -0.13669842527400783,
      -0.13141760307400843, -0.12609684824601639, -0.12073785400089002,
      -0.11534232472111283, -0.10991197549963458, -0.10444853167378054,
      -0.098953728354358061, -0.093429309950080808, -0.0878770296874557,
      -0.082298649126262974, -0.076695937670754638, -0.071070672076733121,
      -0.0654246359546321, -0.059759619268756364, -0.054077417832816888,
      -0.048379832801919737, -0.04266867016115064, -0.036945740210903633,
      -0.031212857049137566, -0.025471838050666912, -0.019724503343693606,
      -0.013972675283704938, -0.008218177924926795, -0.0024628364894701271,
      0.0032915231656437116, 0.0090430750834198381, 0.014789993743626995,
      0.020530454601154158, 0.026262634625819986, 0.03198471284346302,
      0.037694870878139136, 0.043391293495247174, 0.049072169145415068,
      0.054735690508955132, 0.060380055040722275, 0.066003465515192844,
      0.0716041305715773, 0.077180265258795941, 0.08273009158012247,
      0.088251839037321644, 0.093743745174106316, 0.0992040561186991,
      0.10463102712535577, 0.11002292311461716, 0.11537801921216125,
      0.12069460128601879, 0.12597096648198591, 0.1312054237570596,
      0.13639629441068829, 0.14154191261366977, 0.14664062593449223,
      0.15169079586295503, 0.15669079833085442, 0.16163902422957638,
      0.16653387992439608, 0.17137378776530021, 0.17615718659415397,
      0.18088253224801906, 0.185548298058447, 0.19015297534657144,
      0.19469507391379681, 0.19917312252792879, 0.2035856694045366,
      0.2079312826834033, 0.21220855089986038, 0.21641608345082872,
      0.22055251105541424, 0.22461648620985813, 0.2286066836366864,
      0.2325218007278736, 0.23636055798186836, 0.24012169943428868,
      0.24380399308214429, 0.24740623130140577, 0.25092723125776206,
      0.25436583531041174, 0.25772091140870146, 0.26099135348150315,
      0.26417608181912877, 0.26727404344764311, 0.27028421249544371,
      0.27320559055192178, 0.27603720701809908, 0.27877811944906744,
      0.28142741388808878, 0.28398420519224576, 0.28644763734946921,
      0.28881688378683695, 0.29109114766999583, 0.29326966219359296,
      0.29535169086256885, 0.29733652776421815, 0.29922349783087354,
      0.30101195709311013, 0.3027012929233564, 0.30429092426978177,
      0.30578030188038885, 0.30716890851717693, 0.308456259160277,
      0.30964190120198176, 0.31072541463055386, 0.31170641220373307,
      0.31258453961185684, 0.31335947563049216, 0.31403093226252626,
      0.31459865486961458, 0.31506242229292736, 0.31542204696311682,
      0.31567737499944815, 0.31582828629801163, 0.31587469460899553,
      0.31581654760291467, 0.31565382692579047, 0.31538654824320855,
      0.3150147612732081, 0.31453854980799006, 0.31395803172438208,
      0.3132733589830331, 0.31248471761632757, 0.31159232770497486,
      0.31059644334326519, 0.30949735259298145, 0.30829537742593582,
      0.3069908736551511, 0.30558423085465913, 0.3040758722679372,
      0.30246625470497179, 0.3007558684279702, 0.29894523702571835,
      0.29703491727663245, 0.29502549900048558, 0.2929176048988677,
      0.290711890384399, 0.28840904339871648, 0.28600978421930057,
      0.28351486525515818, 0.2809250708314186, 0.27824121696289872,
      0.27546415111668454, 0.27259475196378635, 0.26963392911994355,
      0.26658262287562545, 0.263441803915321, 0.26021247302617745,
      0.25689566079607573, 0.25349242730121807, 0.250003861783329,
      0.24643108231653893, 0.24277523546406771, 0.23903749592480078,
      0.23521906616984511, 0.23132117606920508, 0.22734508250864516,
      0.22329206899689946, 0.21916344526331552, 0.21496054684606347,
      0.21068473467103654, 0.20633739462157974, 0.20191993709916656,
      0.19743379657516286, 0.19288043113383146, 0.18826132200670878,
      0.1835779730984973, 0.17883191050463862, 0.17402468202070329,
      0.16915785664377078, 0.16423302406596282, 0.15925179416026172,
      0.1542157964588112, 0.14912667962387802, 0.14398611091160976,
      0.13879577562878556, 0.13355737658275083, 0.12827263352470461,
      0.12294328258650034, 0.11757107571120395, 0.11215778007753366,
      0.10670517751844158, 0.10121506393394761, 0.095689248698524992,
      0.090129554063135081, 0.084537814552203161, 0.078915876355657583,
      0.073265596716304032, 0.067588843312733238, 0.061887493637899,
      0.056163434373692978, 0.05041856076165932, 0.044654775970070337,
      0.0388739904575873, 0.033078121333742161, 0.027269091716455376,
      0.021448830086779141, 0.015619269641125644, 0.0097823476412052246,
      0.00394000476189095, -0.0019058155627952184, -0.0077531677952621531,
      -0.013600104951373551, -0.019444679258575431, -0.025284942815009259,
      -0.031118948249265144, -0.03694474938063412, -0.042760401879585033,
      -0.048563963928229079, -0.054353496880542, -0.060127065922132336,
      -0.065882740729304293, -0.07161859612716362, -0.07733271274654932,
      -0.083023177679579285, -0.088688085133538569, -0.094325537082888461,
      -0.099933643919155657, -0.10551052509851749, -0.11105430978675332,
      -0.11656313750144527, -0.12203515875108778, -0.12746853567097366,
      -0.13286144265553634, -0.138212066986996, -0.14351860946004066,
      -0.1487792850023191, -0.15399232329051366, -0.15915596936181003,
      -0.16426848422049936, -0.16932814543948249, -0.17433324775651354,
      -0.17928210366490044, -0.18417304399850132, -0.18900441851074326,
      -0.19377459644752221, -0.19848196711370641, -0.20312494043307142,
      -0.20770194750145385, -0.21221144113293083, -0.2166518963987944,
      -0.22102181115913219, -0.225319706586847, -0.2295441276838894,
      -0.23369364378951016, -0.23776684908035356, -0.24176236306221383,
      -0.24567883105327254, -0.24951492465858827, -0.25326934223574821,
      -0.25694080935141106, -0.26052807922866006, -0.26402993318491291,
      -0.26744518106031306, -0.27077266163634223, -0.27401124304459529,
      -0.277159823165479, -0.28021733001674537, -0.28318272213167356,
      -0.28605498892676873, -0.28883315105883989, -0.29151626077133758,
      -0.29410340222977305, -0.29659369184612305, -0.29898627859211746,
      -0.30128034430122957, -0.30347510395929078, -0.30556980598363931,
      -0.30756373249062186, -0.30945619955142922, -0.31124655743609453,
      -0.31293419084561996, -0.31451851913206863, -0.31599899650662533,
      -0.31737511223544185, -0.31864639082328594, -0.31981239218484681,
      -0.32087271180365884, -0.32182698087858619, -0.32267486645779236,
      -0.32341607156013197, -0.32405033528394883, -0.3245774329031883,
      -0.32499717595082056, -0.32530941228950383, -0.32551402616950209,
      -0.32561093827375842, -0.32560010575018883, -0.32548152223108984,
      -0.32525521783972172, -0.32492125918399983, -0.32447974933734158,
      -0.323930827806615, -0.323274670487247, -0.3225114896054615,
      -0.32164153364769149, -0.32066508727716292, -0.319582471237689,
      -0.31839404224469248, -0.31710019286350993, -0.31570135137499156,
      -0.31419798162845541, -0.31259058288204877, -0.31087968963055013,
      -0.30906587142069175, -0.30714973265405709, -0.30513191237759713,
      -0.303013084061896, -0.30079395536718012, -0.29847526789724088,
      -0.296057796941275, -0.29354235120379113, -0.29092977252264546,
      -0.28822093557532069, -0.28541674757354663, -0.282518147946361,
      -0.27952610801174438, -0.27644163063692084, -0.27326574988746583,
      -0.26999953066533594, -0.26664406833594262, -0.2632004883444285,
      -0.25966994582124575, -0.25605362517722075, -0.25235273968821564,
      -0.24856853106954885, -0.24470226904033504, -0.24075525087789565,
      -0.23672880096239357, -0.23262427031186317, -0.22844303610781752,
      -0.2241865012115688, -0.219856093671485, -0.21545326622130789,
      -0.21097949576977451, -0.20643628288167246, -0.20182515125054257,
      -0.19714764716324151, -0.19240533895650797, -0.18759981646578661,
      -0.18273269046646354, -0.17780559210775912, -0.17282017233944813,
      -0.16777810133163429, -0.16268106788780598, -0.15753077885134939,
      -0.15232895850578457, -0.14707734796888902, -0.14177770458099409,
      -0.13643180128762067, -0.13104142601670668, -0.12560838105066874,
      -0.12013448239350606, -0.11462155913318112, -0.10907145279951441,
      -0.10348601671785085, -0.09786711535868825, -0.092216623683566062,
      -0.086536426487389656, -0.080828417737502128, -0.075094499909682685,
      -0.069336583321357184, -0.063556585462258716, -0.057756430322765076,
      -0.051938047720199859, -0.046103372623286315, -0.040254344475073575,
      -0.0343929065145307, -0.028521005097066218, -0.022640589014271024,
      -0.016753608813050144, -0.010862016114492293, -0.0049677629326317571,
      0.00092719900655058307, 0.0068209189457262495, 0.012711447776096896,
      0.01859683871634802, 0.024475147990384812, 0.030344435503648858,
      0.036202765517723813, 0.042048207323008749, 0.047878835909191148,
      0.053692732633295708, 0.059487985885041512, 0.06526269174926036,
      0.071014954665163624, 0.076742888082184657, 0.082444615112151287,
      0.088118269177585723, 0.093761994655837927, 0.099373947518880887,
      0.10495229596845852, 0.11049522106643792, 0.11600091736003762,
      0.12146759350180091, 0.12689347286399308, 0.13227679414728269,
      0.13761581198341657, 0.14290879753170471, 0.14815403906907576,
      0.15334984257352491, 0.15849453230067173, 0.16358645135329108,
      0.16862396224355397, 0.17360544744782846, 0.1785293099537501,
      0.18339397379947622, 0.18819788460482467, 0.1929395100941739,
      0.19761734061089498, 0.2022298896231372, 0.20677569422081105,
      0.2112533156035506, 0.21566133955947292, 0.21999837693463348,
      0.22426306409290941, 0.22845406336622143, 0.23257006349489029,
      0.2366097800579941, 0.2405719558935403, 0.24445536150836938,
      0.2482587954775306, 0.2519810848331307, 0.25562108544237316,
      0.25917768237476863, 0.26264979025833785, 0.26603635362465583,
      0.26933634724267869, 0.27254877644117959, 0.27567267741972939,
      0.27870711754807, 0.28165119565380031, 0.28450404229830034,
      0.28726482004071441, 0.28993272369003387, 0.29250698054506907,
      0.29498685062230451, 0.29737162687154095, 0.299660635379256,
      0.30185323555959659, 0.3039488203330053, 0.3059468162923209,
      0.30784668385640024, 0.3096479174111873, 0.31135004543812084,
      0.31295263062996687, 0.31445526999391232, 0.31585759494202142,
      0.31715927136889682, 0.31835999971667206, 0.31945951502720737,
      0.32045758698151561, 0.32135401992647972, 0.3221486528887535,
      0.32284135957594362, 0.32343204836504835, 0.32392066227816652,
      0.3243071789455077, 0.32459161055576025, 0.32477400379376442,
      0.32485443976564859, 0.32483303391136109, 0.32470993590470459,
      0.32448532954092835, 0.32415943261187463, 0.32373249676884325,
      0.32320480737312096, 0.32257668333435963, 0.32184847693678348,
      0.32102057365338565, 0.32009339194813691, 0.3190673830663342,
      0.3179430308131716, 0.3167208513206371, 0.3154013928028187,
      0.31398523529976236, 0.3124729904099684, 0.31086530101164334,
      0.30916284097285496, 0.30736631485067584, 0.30547645757946729,
      0.30349403414846576, 0.30141983926873472, 0.29925469702970986,
      0.29699946054541182, 0.29465501159054153, 0.2922222602265287,
      0.28970214441781061, 0.28709562963836122, 0.28440370846876378,
      0.28162740018390409, 0.27876775033150847, 0.27582583030168706,
      0.27280273688765844, 0.26969959183783526, 0.26651754139946904,
      0.2632577558540462, 0.2599214290445851, 0.25650977789510954,
      0.25302404192241823, 0.24946548274037722, 0.24583538355698187,
      0.24213504866431057, 0.2383658029216863, 0.23452899123212456,
      0.230625978012437, 0.22665814665705605, 0.22262689899593127,
      0.21853365474659434, 0.2143798509607549, 0.2101669414655066,
      0.20589639629948608, 0.20156970114415629, 0.19718835675044294,
      0.19275387836100932, 0.18826779512832342, 0.18373164952882914,
      0.17914699677340329, 0.17451540421436784, 0.16983845074928541,
      0.16511772622177628, 0.16035483081962215, 0.15555137447033462,
      0.15070897623453489, 0.14582926369726951, 0.14091387235761449,
      0.13596444501673277, 0.13098263116468423, 0.1259700863661935,
      0.1209284716456345, 0.11585945287151733, 0.11076470014064045,
      0.1056458871622378, 0.10050469064230302, 0.0953427896683855,
      0.090161865095053556, 0.084963598930317769, 0.079749673723227846,
      0.074521771952878582, 0.069281575419108912, 0.064030764635062951,
      0.058771018221958682, 0.053504012306185636, 0.0482314199190495,
      0.042954910399379972, 0.03767614879921953, 0.032396795292845018,
      0.027118504589353158, 0.021842925349032854, 0.016571699603747617,
      0.011306462181574682, 0.0060488401358893759, 0.000800452179186166,
      -0.0044370918782354746, -0.0096621916844424824, -0.014873256896670052,
      -0.020068707726603491, -0.025246975479860961, -0.030406503089507847,
      -0.03554574564339287, -0.040663170905088933, -0.045757259828256985,
      -0.050826507064229032, -0.055869421462593508, -0.060884526564637192,
      -0.06587036108942225, -0.070825479412312028, -0.075748452035806657,
      -0.0806378660524367, -0.085492325599619126, -0.090310452306252412,
      -0.095090885730896343, -0.099832283791399093, -0.10453332318576071,
      -0.10919269980412552, -0.11380912913172159, -0.11838134664261682,
      -0.12290810818413664, -0.12738819035180166, -0.1318203908546676,
      -0.13620352887089521, -0.14053644539348498, -0.14481800356599023,
      -0.149047089008125, -0.15322261013115587, -0.1573434984429247,
      -0.16140870884246528, -0.16541721990404928, -0.16936803415059615,
      -0.17326017831635007, -0.17709270359874266, -0.18086468589932325,
      -0.18457522605374976, -0.18822345005067884, -0.19180850923955733,
      -0.1953295805272291, -0.19878586656325825, -0.20217659591399903,
      -0.20550102322526412, -0.20875842937362904, -0.211948121606305,
      -0.21506943366949771, -0.21812172592531426, -0.22110438545710692,
      -0.22401682616329527, -0.22685848883961418, -0.22962884124979116,
      -0.23232737818464827, -0.23495362150962648, -0.23750712020073189,
      -0.23998745036894209, -0.24239421527302277, -0.24472704532086409,
      -0.24698559805926296, -0.24916955815227554, -0.25127863734810019,
      -0.25331257443457178, -0.25527113518328354, -0.257154112282433,
      -0.25896132525836268, -0.26069262038596325, -0.26234787058788422,
      -0.26392697532273829, -0.26542986046225781, -0.26685647815757518,
      -0.26820680669466668, -0.26948085033902713, -0.27067863916970808,
      -0.27180022890281236, -0.27284570070448155, -0.27381516099359893,
      -0.27470874123417433, -0.27552659771766475, -0.27626891133523823,
      -0.2769358873401685, -0.27752775510046168, -0.27804476784184406,
      -0.27848720238125729, -0.27885535885100654, -0.27914956041365596,
      -0.279370152967904, -0.27951750484549076, -0.27959200649937133,
      -0.27959407018328442, -0.27952412962284279, -0.27938263967839005,
      -0.27917007599971044, -0.27888693467280712, -0.27853373185894931,
      -0.27811100342607886, -0.27761930457287809, -0.27705920944556256,
      -0.27643131074770028, -0.27573621934315928, -0.27497456385242391,
      -0.27414699024246658, -0.27325416141039005, -0.27229675676099713,
      -0.27127547177856026, -0.27019101759292946, -0.26904412054023918,
      -0.26783552171842029, -0.26656597653768727, -0.26523625426628561,
      -0.26384713757165512, -0.26239942205727618, -0.26089391579539872,
      -0.25933143885586962, -0.25771282283132046, -0.25603891035889254,
      -0.25431055463877794, -0.25252861894977086, -0.25069397616207462,
      -0.2488075082476052, -0.24687010578799967, -0.24488266748059223,
      -0.24284609964257811, -0.24076131571359885, -0.23862923575700273,
      -0.23645078595998914, -0.23422689813290537, -0.23195850920791644,
      -0.22964656073727896, -0.22729199839148712, -0.22489577145749828,
      -0.22245883233728189, -0.21998213604695274, -0.21746663971669017,
      -0.21491330209172549, -0.21232308303458075, -0.20969694302884423,
      -0.20703584268469033, -0.20434074224638452, -0.20161260110200471,
      -0.19885237729563204, -0.19606102704220443, -0.19323950424530309,
      -0.19038876001807226, -0.18750974220750793, -0.18460339492236577,
      -0.18167065806486452, -0.17871246686645076, -0.17572975142782571,
      -0.17272343626346184, -0.1696944398508041, -0.16664367418442111,
      -0.16357204433525238, -0.16048044801521655, -0.15736977514736133,
      -0.15424090744175972, -0.15109471797738946, -0.14793207079012075,
      -0.14475382046712276, -0.14156081174774754, -0.13835387913121691,
      -0.13513384649119733, -0.13190152669750843, -0.12865772124512148,
      -0.12540321989063255, -0.12213880029639086, -0.11886522768244107,
      -0.11558325448647645, -0.112293620031924, -0.10899705020436987,
      -0.10569425713644449, -0.10238593890133751, -0.0990727792151154,
      -0.095755447147924611, -0.0924345968443016, -0.0891108672526534,
      -0.085784881864107543, -0.0824572484607907, -0.079128558873750171,
      -0.07579938875054032, -0.072470297332667, -0.069141827242968051,
      -0.065814504283025738, -0.062488837240759487, -0.059165317708244652,
      -0.055844419909878845, -0.052526600540985707, -0.049212298616933159,
      -0.0459019353328268, -0.042595913933907409, -0.039294619596654534,
      -0.035998419320704828, -0.032707661831641061, -0.029422677494665983,
      -0.026143778239291149, -0.022871257494987973, -0.019605390137918205,
      -0.016346432448739429, -0.013094622081513491, -0.0098501780437739161,
      -0.0066133006877231171, -0.0033841717126281978, -0.00016295417836653669,
      0.0030502074698322834, 0.0062551873654684564, 0.0094518781736786239,
      0.012640191032984111, 0.015820055485903289, 0.018991419398436793,
      0.022154248868468673, 0.025308528123088481, 0.028454259404935039,
      0.03159146284751041, 0.034720176339617326, 0.037840455378885057,
      0.040952372914502794, 0.044056019179198713, 0.047151501510520555,
      0.050238944161549143, 0.053318488101034373, 0.056390290803131987,
      0.059454526026774229, 0.062511383584757912, 0.065561069102724717,
      0.068603803768030713, 0.071639824068713082, 0.07466938152261543,
      0.077692742396781, 0.080710187417296964, 0.083722011469628932,
      0.0867285232896797, 0.089730045145630433, 0.0927269125107311,
      0.09571947372721315, 0.09870808966143281, 0.10169313335042715,
      0.10467498964005423, 0.10765405481483004, 0.11063073621968747,
      0.11360545187381982, 0.11657863007672464, 0.11955070900673972,
      0.12252213631212998, 0.12549336869503061, 0.12846487148833668,
      0.13143711822581194, 0.13441059020559049, 0.1373857760472309,
      0.14036317124262621, 0.14334327770085964, 0.14632660328733357,
      0.14931366135730828, 0.15230497028409998, 0.15530105298215954,
      0.15830243642527059, 0.16130965116004337, 0.16432323081501743,
      0.16734371160552569, 0.17037163183460435, 0.17340753139019113,
      0.17645195123879343, 0.17950543291597088, 0.18256851801375651,
      0.18564174766538646, 0.188725662027476, 0.19182079975999028,
      0.1949276975041738, 0.19804688935878212, 0.20117890635478602,
      0.20432427592887786, 0.20748352139598042, 0.21065716142108265,
      0.21384570949057782, 0.21704967338346187, 0.22026955464258022,
      0.22350584804622209, 0.22675904108032269, 0.23002961341153269,
      0.23331803636141546, 0.23662477238207313, 0.23995027453339474,
      0.24329498596227417, 0.24665933938402576, 0.25004375656622735,
      0.25344864781535126, 0.256874411466329, 0.26032143337543695,
      0.26379008641664992, 0.26728072998182006, 0.27079370948490411,
      0.27432935587046969, 0.27788798512681562, 0.28146989780389259,
      0.28507537853633019, 0.28870469557180062, 0.29235810030498205,
      0.29603582681738516, 0.29973809142328911, 0.30346509222198925,
      0.30721700865673007, 0.31099400108038727, 0.31479621032833777,
      0.31862375729857934, 0.32247674253949166, 0.32635524584534209,
      0.33025932585989337, 0.33418901968822295, 0.33814434251709879,
      0.34212528724402747, 0.34613182411529669, 0.35016390037313583,
      0.35422143991229949, 0.35830434294621011, 0.36241248568291484,
      0.36654572001106062, 0.37070387319603942, 0.37488674758658236,
      0.37909412033191137, 0.38332574310971063, 0.38758134186504245,
      0.39186061656043886, 0.39616324093731858, 0.40048886228889669,
      0.40483710124478789, 0.40920755156742217, 0.41359977996048608,
      0.41801332588947876, 0.42244770141460924, 0.42690239103609873,
      0.43137685155210836, 0.43587051192935639, 0.4403827731866069,
      0.44491300829113645, 0.44946056206827895, 0.45402475112421203,
      0.458604863782042, 0.46320016003131764, 0.46780987149109082,
      0.47243320138655981, 0.47706932453945716, 0.48171738737218855,
      0.48637650792587328, 0.49104577589228376, 0.49572425265982356,
      0.50041097137352886, 0.50510493700920922, 0.50980512646174891,
      0.51451048864758941, 0.51921994462148158, 0.52393238770747852,
      0.52864668364424572, 0.53336167074465979, 0.53807616006975234,
      0.54278893561695607, 0.54749875452271179, 0.55220434727935808,
      0.55690441796636092, 0.56159764449582938, 0.56628267887226813,
      0.57095814746661089, 0.57562265130440093, 0.58027476636816955,
      0.58491304391388621, 0.589536010801465, 0.59414216983927859,
      0.59873000014254463, 0.60329795750561033, 0.60784447478795278,
      0.61236796231388424, 0.61686680828583063, 0.62133937921109494,
      0.62578402034200831, 0.63019905612934046, 0.634582790688864,
      0.638933508280958, 0.64324947380309794, 0.64752893329511907,
      0.65177011445710931, 0.65597122717975931, 0.66013046408707254,
      0.66424600109120235, 0.66831599795932783, 0.67233859889234826,
      0.67631193311522064, 0.68023411547881674, 0.68410324707302139,
      0.68791741585096844, 0.69167469726416353, 0.69537315490829654,
      0.6990108411795819, 0.702585797941331, 0.70609605720061452,
      0.70953964179476137, 0.71291456608745307, 0.71621883667420838,
      0.71945045309699762, 0.7226074085677503, 0.72568769070052142,
      0.72868928225204066, 0.731610161870412, 0.73444830485168988,
      0.73720168390404861, 0.73986826991933863, 0.74244603275165766,
      0.74493294200276916, 0.747326967813994, 0.7496260816643221,
      0.75182825717451984, 0.75393147091678347, 0.755933703229847,
      0.75783293903903992, 0.75962716868116575, 0.76131438873376167,
      0.76289260284853055, 0.764359822588552, 0.76571406826902477,
      0.7669533698011699, 0.76807576753901319, 0.76907931312868416,
      0.76996207035996056, 0.77072211601967044, 0.77135754074665619,
      0.77186644988798558, 0.77224696435600881, 0.77249722148601874,
      0.77261537589409479, 0.77259960033482988, 0.77244808655861652,
      0.77215904616810715, 0.77173071147352768, 0.77116133634653172,
      0.7704491970721804, 0.7695925931987746, 0.76858984838515709,
      0.76743931124511811, 0.76613935618863072, 0.76468838425947283,
      0.76308482396898181, 0.76132713212552749, 0.75941379465936965,
      0.75734332744261368, 0.75511427710380652, 0.75272522183695589,
      0.75017477220452322, 0.74746157193407681, 0.74458429870835674,
      0.74154166494820006, 0.73833241858824339, 0.73495534384484629,
      0.73140926197603329, 0.72769303203305469, 0.72380555160326687,
      0.71974575754397607, 0.71551262670693816, 0.71110517665316586,
      0.70652246635773419, 0.70176359690427181, 0.69682771216877115,
      0.69171399949248835, 0.6864216903435002, 0.68095006096675037,
      0.67529843302211678, 0.66946617421036325, 0.66345269888653724,
      0.65725746866057433, 0.6508799929848611, 0.64431982972835455,
      0.6375765857370933, 0.63064991738072229, 0.6235395310848314,
      0.616245183848761, 0.60876668374868748, 0.60110389042563939,
      0.59325671555824488, 0.58522512331995424, 0.577009130820434,
      0.56860880853097551, 0.56002428069356081, 0.551255725713506,
      0.54230337653526728, 0.533167521001393, 0.52384850219419044,
      0.514346718760072, 0.50466262521629668, 0.49479673223985732,
      0.48474960693845331, 0.47452187310320149, 0.46411421144304515,
      0.45352735980058612, 0.44276211334918653, 0.43181932477125862,
      0.42069990441743238, 0.40940482044662252, 0.397935098946687,
      0.38629182403569273, 0.3744761379435011, 0.36248924107371416,
      0.35033239204571559, 0.33800690771677028, 0.32551416318411946,
      0.31285559176683853, 0.30003268496755076, 0.28704699241372111,
      0.27390012177864187, 0.26059373868189684, 0.24712956656929552,
      0.23350938657229198, 0.21973503734668959, 0.20580841489078189,
      0.19173147234269877, 0.17750621975714576, 0.16313472386130268, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.20375340803861139,
      -0.18347989266064316, -0.16305574006649481, -0.14248482712239913,
      -0.12177108322605293, -0.1009184894905128, -0.079931077911136489,
      -0.05881293051573204, -0.037568178498097508, -0.016201001335132692,
      0.0052843741122899184, 0.026883674514501254, 0.048592581004062566,
      0.070406730122433689, 0.092321714782082981, 0.11433308524381722,
      0.13643635010911653, 0.15862697732724945, 0.18090039521694051,
      0.20325199350235545, 0.22567712436316475, 0.24817110349844415,
      0.2707292112041646, 0.29334669346401177, 0.31601876305329119,
      0.33874060065564127, 0.36150735599230072, 0.38431414896365046,
      0.40715607080276017, 0.43002818524065539, 0.45292552968302646,
      0.47584311639808347, 0.49877593371527357, 0.52171894723455681,
      0.54466710104594507, 0.56761531895899575, 0.59055850574195723,
      0.61349154837024744, 0.63640931728395556, 0.65930666765404722,
      0.68217844065694366, 0.70501946475715993, 0.72782455699766124,
      0.7505885242976148, 0.77330616475719127, 0.79597226896908424,
      0.81858162133640355, 0.84112900139659574, 0.86360918515104312,
      0.88601694639999606, 0.90834705808247929, 0.93059429362081891,
      0.95275342826943121, 0.97481924046751511, 0.99678651319527956,
      1.0186500353333467, 1.0404046030249638, 1.0620450210406431,
      1.0835661041448799, 1.1049626784645539, 1.1262295828586528,
      1.1473616702889415, 1.1683538091911894, 1.1892008848465914,
      1.209897800752989, 1.23043947999552, 1.2508208666163094,
      1.2710369269828188, 1.2910826511544724, 1.310953054247173,
      1.3306431777953216, 1.35014809111096, 1.3694628926396419,
      1.3885827113126512, 1.4075027078951865, 1.4262180763301069,
      1.4447240450768748, 1.463015878445294, 1.48108887792366,
      1.4989383835009429, 1.5165597749826087, 1.5339484732996984,
      1.5510999418107871, 1.5680096875964245, 1.5846732627456943,
      1.6010862656344942, 1.6172443421951666, 1.6331431871771007,
      1.6487785453979233, 1.6641462129849112, 1.6792420386062434,
      1.6940619246917241, 1.708601828642613, 1.7228577640301779,
      1.7368258017826224, 1.7505020713600141, 1.763882761916852,
      1.7769641234519185, 1.7897424679450569, 1.8022141704805177,
      1.8143756703565301, 1.8262234721807431, 1.8377541469511935,
      1.8489643331224637, 1.8598507376566773, 1.8704101370590167,
      1.8806393783974098, 1.8905353803060743, 1.90009513397258,
      1.909315704108125, 1.9181942299006902, 1.9267279259507724,
      1.9349140831893805, 1.9427500697779923, 1.9502333319901688,
      1.9573613950745314, 1.9641318640988088, 1.9705424247746701,
      1.9765908442630522, 1.9822749719597168, 1.9875927402607509,
      1.9925421653077511, 1.997121347712427, 2.001328473260362,
      2.0051618135936842, 2.0086197268723955, 2.0117006584141186,
      2.0144031413120285, 2.0167257970307317, 2.018667335979869,
      2.0202265580652319, 2.0214023532171588, 2.0221937018960259,
      2.0225996755746185, 2.0226194371971831, 2.02225224161498,
      2.0214974359981537, 2.02035446022373, 2.0188228472395862,
      2.0169022234042182, 2.0145923088021522, 2.0118929175348468,
      2.0088039579869363, 2.0053254330676964, 2.0014574404275711,
      1.9972001726496598, 1.9925539174160365, 1.9875190576487922,
      1.9820960716256959, 1.97628553307038, 1.970088111216953,
      1.9635045708489647, 1.956535772312644, 1.9491826715043399,
      1.9414463198321068, 1.9333278641513747, 1.9248285466746691,
      1.915949704855322, 1.9066927712451627, 1.8970592733261478,
      1.8870508333159162, 1.8766691679472705, 1.8659160882215611,
      1.8547934991359973, 1.8433033993848882, 1.831447881034832,
      1.8192291291738871, 1.8066494215347533, 1.7937111280920122,
      1.7804167106334685, 1.7667687223056585, 1.7527698071335831,
      1.7384226995147434, 1.7237302236875529, 1.7086952931742256,
      1.6933209101982176, 1.6776101650763389, 1.6615662355856453,
      1.6451923863052162, 1.6284919679329588, 1.6114684165775564,
      1.5941252530257177, 1.5764660819848562, 1.5584945913013717,
      1.5402145511546821, 1.5216298132271884, 1.5027443098503375,
      1.4835620531269751, 1.46408713403018, 1.4443237214787714, 1.42427606138971,
      1.4039484757075835, 1.3833453614114226, 1.3624711894990524,
      1.3413305039492285, 1.3199279206617911, 1.2982681263760871,
      1.2763558775679198, 1.2541959993252736, 1.2317933842031055,
      1.2091529910574534, 1.1862798438591622, 1.1631790304875025,
      1.1398557015039856, 1.1163150689066734, 1.0925624048652822,
      1.0686030404374109, 1.0444423642661973, 1.0200858212597335,
      0.99553891125257976, 0.97080718764969731, 0.94589625605316685,
      0.92081177287201488, 0.89555944391553366, 0.87014502297041707,
      0.84457431036212682, 0.81885315150080351, 0.79298743541215722,
      0.76698309325366631, 0.74084609681651636, 0.71458245701363321,
      0.68819822235423955, 0.66169947740530655, 0.6350923412403352,
      0.60838296587584839, 0.58157753469604123, 0.55468226086597483,
      0.52770338573377107, 0.50064717722220187, 0.47351992821013988,
      0.44632795490427, 0.41907759520154042, 0.39177520704275109,
      0.36442716675776848, 0.33703986740279313, 0.30961971709013,
      0.282173137310938, 0.25470656125139407, 0.22722643210275389,
      0.19973920136575579, 0.17225132714986024, 0.14476927246775623,
      0.11729950352565711, 0.0898484880098066, 0.062422693369720783,
      0.035028585098599144, 0.0076726250114327321, -0.019638730478760122,
      -0.046899032086038725, -0.074101839377542528, -0.10124072249986441,
      -0.12830926390535383, -0.15530106007781128, -0.18220972325713397,
      -0.20902888316237855, -0.23575218871279224, -0.26237330974628137,
      -0.28888593873486335, -0.31528379249658778, -0.34156061390343634,
      -0.36771017358473207, -0.39372627162553364, -0.41960273925956437,
      -0.44533344055614277, -0.47091227410067565, -0.49633317466817373,
      -0.52159011488935236, -0.54667710690878879, -0.57158820403469224,
      -0.59631750237976777, -0.62085914249272, -0.64520731097990092,
      -0.66935624211664169, -0.69330021944776832, -0.71703357737685747,
      -0.7405507027437348, -0.76384603638977355, -0.78691407471050545,
      -0.80974937119509827, -0.83234653795222568, -0.85470024722189342,
      -0.87680523287274137, -0.8986562918844011, -0.92024828581443807,
      -0.94157614224944586, -0.96263485623986478, -0.98341949171806009,
      -1.0039251828992701, -1.0241471356649494, -1.0440806289281344,
      -1.0637210159803696, -1.0830637258198172, -1.1021042644601091,
      -1.1208382162195676, -1.1392612449903703, -1.1573690954872864,
      -1.1751575944755799, -1.1926226519777086, -1.2097602624584287,
      -1.226566505987952, -1.2430375493827652, -1.259169647323775,
      -1.2749591434514018, -1.2904024714372979, -1.3054961560323242,
      -1.3202368140904686, -1.3346211555683596, -1.3486459845000764,
      -1.3623081999469038, -1.3756047969217653, -1.3885328672879911,
      -1.401089600632152, -1.4132722851106647, -1.4250783082698748,
      -1.4365051578393651, -1.4475504224982008, -1.4582117926138658,
      -1.4684870609536336, -1.4783741233681291, -1.4878709794468419,
      -1.496975733145371, -1.505686593384163, -1.5140018746185582,
      -1.5219199973799025, -1.5294394887875695, -1.5365589830316657,
      -1.5432772218262707, -1.5495930548330115, -1.5555054400548338,
      -1.5610134441997952, -1.5661162430147431, -1.5708131215887322,
      -1.5751034746260646, -1.5789868066888146, -1.582462732408739,
      -1.585530976668466, -1.5881913747518586, -1.5904438724634884,
      -1.5922885262171151, -1.5937255030931292, -1.5947550808648774,
      -1.5953776479938402, -1.5955937035936041, -1.595403857362607,
      -1.5948088294856293, -1.5938094505040157, -1.5924066611546304,
      -1.5906015121775408, -1.5883951640924474, -1.585788886943887,
      -1.5827840600152292, -1.5793821715115244, -1.5755848182112386,
      -1.5713937050869389, -1.5668106448950039, -1.5618375577344286,
      -1.5564764705748193, -1.550729516753663, -1.5445989354429912,
      -1.538087071085539, -1.5311963728005313, -1.5239293937592275,
      -1.516288790530361, -1.5082773223956303, -1.4998978506354004,
      -1.491153337784781, -1.4820468468602577, -1.472581540557065,
      -1.4627606804174991, -1.4525876259703694, -1.4420658338417991,
      -1.4311988568376115, -1.4199903429975049, -1.4084440346212905,
      -1.3965637672674012, -1.3843534687239654, -1.3718171579526741,
      -1.3589589440057461, -1.3457830249162432, -1.332293686562052,
      -1.318495301503799, -1.3043923277970357, -1.2899893077789779,
      -1.2752908668301466, -1.2603017121112106, -1.2450266312753961,
      -1.2294704911567877, -1.2136382364348746, -1.1975348882757162,
      -1.1811655429500667, -1.1645353704288617, -1.1476496129564207,
      -1.1305135836017828, -1.1131326647885285, -1.0955123068035397,
      -1.0776580262850608, -1.05957540469051, -1.04127008674443,
      -1.0227477788670456, -1.0040142475838127, -0.98507531791645109,
      -0.96593687175586262, -0.946604846217412, -0.92708523197902748,
      -0.90738407160256263, -0.88750745783892182, -0.86746153191738729,
      -0.84725248181966506, -0.8268865405390925, -0.80636998432553375,
      -0.78570913091643668, -0.7649103377545533, -0.7439800001928375,
      -0.72292454968700248, -0.70175045197628272, -0.68046420525289064,
      -0.65907233832070855, -0.63758140874370783, -0.615998000984665,
      -0.59432872453466778, -0.57258021203397969, -0.55075911738475247,
      -0.52887211385618516, -0.50692589218262674, -0.48492715865519886,
      -0.4628826332074526, -0.44079904749564658, -0.41868314297418213,
      -0.39654166896675214, -0.37438138073374666, -0.35220903753650284,
      -0.33003140069893655, -0.30785523166713147, -0.28568729006742288,
      -0.26353433176357582, -0.2414031069135969, -0.2193003580267594,
      -0.19723281802138121, -0.17520720828396763, -0.15323023673023672,
      -0.13130859586862573, -0.10944896086684386, -0.087657987622002553,
      -0.065942310834942924, -0.0443085420892772, -0.022763267935744583,
      -0.0013130479824089505, 0.020035587008705114, 0.041276137017998878,
      0.0624021346571402, 0.083407147049811781, 0.104284777703798,
      0.12502866837386367, 0.14563250091486765, 0.16608999912458189,
      0.18639493057563733, 0.20654110843608031, 0.22652239327798351,
      0.24633269487358031, 0.26596597397838967, 0.28541624410078564,
      0.30467757325749523, 0.32374408571451829, 0.34260996371289831,
      0.36126944917888659, 0.37971684541793976, 0.39794651879207271,
      0.41595290038005478, 0.43373048761993882, 0.45127384593345377,
      0.468577610331732, 0.48563648700194406, 0.50244525487430036,
      0.51899876716899218, 0.53529195292257692, 0.551319818493367,
      0.56707744904534285, 0.58256001001015445, 0.59776274852676281,
      0.61268099485828653, 0.62731016378561377, 0.64164575597736406,
      0.65568335933576094, 0.66941865031804648, 0.682847395232975,
      0.69596545151203693, 0.7087687689549903, 0.72125339094934038,
      0.73341545566337119, 0.745251197212368, 0.75675694679767747,
      0.7679291338182338, 0.77876428695423094, 0.78925903522257934,
      0.79941010900383114, 0.80921434104024637, 0.81866866740469879,
      0.82777012844010234, 0.83651586966907032, 0.84490314267351729,
      0.85292930594393446, 0.8605918256980496, 0.86788827666863233,
      0.87481634286017362, 0.88137381827421568, 0.887558607603079,
      0.89336872689177871, 0.89880230416790352, 0.90385758003925853,
      0.908532908259071, 0.91282675625857523, 0.91673770564679624,
      0.92026445267736845, 0.92340580868222533, 0.92616070047201915,
      0.92852817070312532, 0.93050737821110607, 0.9320975983105142,
      0.93329822306092947, 0.93410876149912259, 0.93452883983726642,
      0.93455820162710823, 0.9341967078900395, 0.933444337212998,
      0.9323011858101603, 0.93076746755038409, 0.92884351395036624,
      0.9265297741335089, 0.92382681475447481, 0.92073531988944113,
      0.91725609089206372, 0.91339004621516773, 0.90913822119820764,
      0.90450176782052982, 0.89948195442049839, 0.89408016538053992,
      0.8882979007781947, 0.88213677600323448, 0.87559852134096861,
      0.86868498152181861, 0.8613981152372896, 0.8537399946224612,
      0.84571280470512022, 0.83731884282169566, 0.8285605180001443,
      0.81944035030993922, 0.80996097017935809, 0.80012511768023009,
      0.78993564178035669, 0.77939549956379639, 0.768507755419226,
      0.75727558019661212, 0.74570225033241089, 0.73379114694355418,
      0.721545754890448, 0.70896966180927767, 0.69606655711385534,
      0.6828402309673165, 0.66929457322393071, 0.65543357234134,
      0.64126131426352662, 0.62678198127482254, 0.61199985082528019,
      0.59691929432774848, 0.58154477592698439, 0.56588085124116028,
      0.5499321660761114, 0.53370345511269868, 0.51719954056765649,
      0.50042533082831864, 0.48338581906160161, 0.46608608179763372,
      0.44853127748846716, 0.43072664504225477, 0.41267750233334205,
      0.39438924468865832, 0.37586734335090061, 0.35711734391890548,
      0.33814486476568439, 0.318955595434565, 0.29955529501391071,
      0.27994979049088886, 0.26014497508475565, 0.24014680656014636,
      0.21996130552086052, 0.19959455368462617, 0.17905269213937502,
      0.15834191958147681, 0.137468490536513, 0.1164387135630571,
      0.095258949440000878, 0.0739356093379718, 0.0524751529753245,
      0.030884086759313784, 0.0091689619129197361, -0.012663627412060542,
      -0.034607046035175233, -0.056654619660117957, -0.078799636799631714,
      -0.10103535071196404, -0.12335498134829093, -0.14575171731054803,
      -0.16821871781908795, -0.19074911468959377, -0.2133360143186864,
      -0.23597249967759848, -0.25865163231338439, -0.28136645435703261,
      -0.30410999053793114, -0.32687525020407127, -0.34965522934739207,
      -0.37244291263369156, -0.39523127543649861, -0.41801328587430481,
      -0.44078190685055596, -0.46353009809580492, -0.48625081821145694,
      -0.50893702671443164, -0.53158168608222722, -0.55417776379772032,
      -0.5767182343931303, -0.5991960814925481, -0.62160429985240762,
      -0.64393589739932422, -0.66618389726466165, -0.68834133981529533,
      -0.7104012846798945, -0.73235681277017739, -0.75420102829653113,
      -0.77592706077740048, -0.79752806704185575, -0.81899723322473728,
      -0.840327776753804, -0.86151294832830128, -0.88254603388834518,
      -0.90342035657456377, -0.92412927867739247, -0.944666203575491,
      -0.96502457766265171, -0.98519789226268617, -1.005179685531677,
      -1.0249635443470857, -1.0445431061831074, -1.0639120609717458,
      -1.0830641529490652, -1.1019931824860485, -1.1206930079035577,
      -1.1391575472708195, -1.1573807801869389, -1.1753567495448975,
      -1.1930795632775228, -1.210543396084913, -1.2277424911427972,
      -1.2446711617913426, -1.261323793203905, -1.2776948440352185,
      -1.2937788480485652, -1.3095704157214, -1.3250642358290223,
      -1.3402550770057544, -1.3551377892832253, -1.3697073056052735,
      -1.383958643319033, -1.3978869056417658, -1.411487283103,
      -1.4247550549615553, -1.4376855905970414, -1.4502743508754079,
      -1.4625168894881613, -1.4744088542648306, -1.4859459884583246,
      -1.4971241320027804, -1.5079392227435409, -1.5183872976389063,
      -1.528464493933291, -1.5381670503014631, -1.5474913079635084,
      -1.5564337117702107, -1.5649908112585131, -1.5731592616767718,
      -1.5809358249794823, -1.5883173707911973, -1.5953008773393524,
      -1.6018834323557332, -1.6080622339463069, -1.6138345914291803,
      -1.6191979261404268, -1.624149772207564, -1.6286877772904351,
      -1.6328097032893054, -1.636513427019942, -1.6397969408555069,
      -1.6426583533350589, -1.6450958897384982, -1.6471078926277885,
      -1.6486928223542945, -1.6498492575321049, -1.6505758954771872,
      -1.6508715526122621, -1.6507351648372843, -1.6501657878654126,
      -1.649162597524398, -1.6477248900232784, -1.645852082184335,
      -1.6435437116402274, -1.6407994369962655, -1.6376190379577742,
      -1.6340024154225186, -1.6299495915381708, -1.6254607097248068,
      -1.6205360346624338, -1.6151759522435627, -1.6093809694908334,
      -1.6031517144397469, -1.5964889359865204, -1.5893935037011433,
      -1.5818664076056743, -1.5739087579178666, -1.5655217847602014,
      -1.5567068378344211, -1.5474653860616725, -1.5377990171883611,
      -1.5277094373578581, -1.5171984706481825, -1.5062680585758108,
      -1.4949202595657589, -1.4831572483881166, -1.4709813155611904,
      -1.4583948667214663, -1.4454004219605494, -1.4320006151293256,
      -1.4181981931095298, -1.4039960150529642, -1.3893970515885754,
      -1.3744043839976685, -1.359021203357482, -1.3432508096533931,
      -1.3270966108600317, -1.310562121991574, -1.2936509641215077,
      -1.2763668633721859, -1.2587136498744278, -1.2406952566975464,
      -1.222315718750081, -1.20357917165158, -1.1844898505758,
      -1.1650520890656186, -1.145270317820088, -1.1251490634539287,
      -1.104692947229905, -1.0839066837643914, -1.0627950797065917,
      -1.0413630323917649, -1.0196155284688779, -0.997557642503101,
      -0.97519453555355406, -0.95253145372675418, -0.929573726706188,
      -0.906326766258427, -0.88279606471628658, -0.858987193439436,
      -0.834905801252957, -0.81055761286428163, -0.78594842725902547,
      -0.76108411607616788, -0.73597062196308016, -0.71061395691087925,
      -0.68502020057062363, -0.65919549855084691, -0.63314606069693158,
      -0.60687815935284561, -0.58039812760575649, -0.55371235751404391,
      -0.5268272983192539, -0.49974945464250986, -0.47248538466591733,
      -0.44504169829952483, -0.41742505533435947, -0.38964216358212012,
      -0.36169977700202766, -0.33360469381545593, -0.30536375460884108,
      -0.27698384042549151, -0.24847187084679118, -0.21983480206343911,
      -0.19107962493725575, -0.16221336305413717, -0.13324307076871988,
      -0.10417583124137324, -0.075018754468054533, -0.045778975303649591,
      -0.016463651479322314, 0.012920038385454235, 0.042364896775691732,
      0.071863709277832685, 0.1014092465803548, 0.13099426647734513,
      0.16061151587453851, 0.19025373279717847, 0.21991364839912309,
      0.24958398897264863, 0.2792574779582811, 0.30892683795414055,
      0.33858479272417835, 0.3682240692047144, 0.39783739950869451,
      0.42741752292711382, 0.45695718792696255, 0.48644915414515505,
      0.51588619437785088, 0.545261096564594, 0.57456666576667337,
      0.60379572613916455, 0.63294112289602222, 0.66199572426775632,
      0.69095242345099217, 0.719804140549461, 0.74854382450580514,
      0.77716445502364706, 0.80565904447938808, 0.83402063982315322,
      0.8622423244683719, 0.89031722016940529, 0.91823848888674886,
      0.94599933463919783, 0.97359300534249515, 1.0010127946339276,
      1.028252043682335, 1.0553041429830279, 1.0821625341371106,
      1.1088207116146478, 1.1352722245012974, 1.1615106782277476,
      1.1875297362816124, 1.2133231219012153, 1.2388846197508241,
      1.2642080775768483, 1.2892874078445347, 1.3141165893546873,
      1.3386896688400143, 1.3630007625405685, 1.3870440577579179,
      1.4108138143875579, 1.4343043664291846, 1.4575101234743721,
      1.4804255721712698, 1.5030452776658925, 1.5253638850196092,
      1.5473761206024794, 1.569076793461986, 1.5904607966668509,
      1.6115231086255264, 1.6322587943790379, 1.6526630068677957,
      1.6727309881720629, 1.6924580707257044, 1.7118396785029575,
      1.7308713281778356, 1.7495486302558938, 1.7678672901780603,
      1.7858231093962291, 1.803411986420326, 1.8206299178366039,
      1.8374729992968482, 1.8539374264783219, 1.8700194960141052,
      1.8857156063936689, 1.9010222588334111, 1.9159360581169609,
      1.9304537134050275, 1.944572039014606, 1.9582879551673147,
      1.971598488706755, 1.9845007737846396, 1.9969920525155775,
      2.0090696756003541, 2.0207311029175536, 2.0319739040834057,
      2.0427957589797137, 2.0531944582497754, 2.063167903762162,
      2.0727141090422987, 2.0818311996717274, 2.0905174136549998,
      2.0987711017541208, 2.1065907277905089, 2.1139748689144033,
      2.1209222158417016, 2.1274315730581881, 2.1335018589911643,
      2.1391321061484292, 2.144321461224671, 2.149069185175235,
      2.153374653257317, 2.1572373550386197, 2.1606568943734921,
      2.1636329893466346, 2.1661654721844052, 2.1682542891338206,
      2.1698995003093247, 2.1711012795074112, 2.171859913989215,
      2.1721758042311761, 2.1720494636438903, 2.1714815182592875,
      2.1704727063862728, 2.1690238782349702, 2.167135995509744,
      2.1648101309711509, 2.1620474679669917, 2.1588492999326836,
      2.1552170298610958, 2.1511521697420912, 2.1466563399719711,
      2.1417312687330421, 2.1363787913435375, 2.1306008495781334,
      2.1243994909592891, 2.1177768680197104, 2.11073523753613,
      2.103276959734742, 2.0954044974685417, 2.0871204153668366,
      2.0784273789572776, 2.0693281537606603, 2.0598256043588377,
      2.0499226934360646, 2.0396224807940655, 2.0289281223412154,
      2.017842869056123, 2.0063700659259989, 1.9945131508601248,
      1.9822756535788517, 1.9696611944784179, 1.9566734834720247,
      1.9433163188075162, 1.9295935858620636, 1.9155092559142493,
      1.9010673848939665, 1.8862721121104935, 1.8711276589592238,
      1.8556383276074067, 1.8398084996593771, 1.8236426348016643,
      1.8071452694284293, 1.7903210152476845, 1.7731745578687197,
      1.7557106553711943, 1.7379341368563592, 1.7198499009808572,
      1.7014629144735649, 1.6827782106359559, 1.6638008878264607,
      1.6445361079292697, 1.6249890948081092, 1.605165132745431,
      1.5850695648675268, 1.5647077915560577, 1.5440852688464806,
      1.5232075068138953, 1.5020800679467743, 1.4807085655091223,
      1.459098661891538, 1.4372560669517136, 1.4151865363448428,
      1.3928958698444993, 1.3703899096544789, 1.3476745387121098,
      1.3247556789835682, 1.3016392897517097, 1.2783313658969331,
      1.2548379361716446, 1.2311650614687393, 1.2073188330847593,
      1.1833053709781385, 1.1591308220231487, 1.1348013582599985,
      1.1103231751416545, 1.0857024897779117, 1.0609455391772, 1.036058578486728,
      1.0110478792313755, 0.98591972755197366, 0.96068042244343355,
      0.93533627399324171, 0.90989360162088817, 0.88435873231869866,
      0.85873799889461067, 0.83303773821743221, 0.80726428946504,
      0.78142399237609794, 0.75552318550575759, 0.72956820448587922,
      0.70356538029024818, 0.67752103750534121, 0.651441492607079,
      0.62533305224413216, 0.59920201152820352, 0.57305465233184094,
      0.54689724159424791, 0.52073602963556209, 0.49457724848009754,
      0.46842711018903971, 0.44229180520303479, 0.41617750069518195,
      0.39009033893488632, 0.36403643566298333, 0.33802187847866988,
      0.31205272523865885, 0.28613500246898632, 0.26027470378994183,
      0.23447778835456035, 0.20875017930107476, 0.18309776221983354,
      0.15752638363499039, 0.13204184950149606, 0.10664992371774362,
      0.081356326654277916, 0.056166733698988114, 0.031086773819164484,
      0.0061220281408040783, -0.018721971454432648, -0.043439743714269397,
      -0.068025859382465192, -0.092474942546721853, -0.11678167196749024,
      -0.14094078238733118, -0.16494706582046226, -0.18879537282218944,
      -0.2124806137378763, -0.23599775993110361, -0.25934184499078033,
      -0.282507965916792, -0.305491284283975, -0.32828702738407972,
      -0.35089048934544154, -0.37329703223009447, -0.39550208710804091,
      -0.41750115510841035, -0.43928980844729049, -0.46086369143192929,
      -0.48221852144109345, -0.50335008988136409, -0.52425426311911938,
      -0.544926983388004, -0.56536426967168174, -0.58556221856163493,
      -0.60551700508988837, -0.62522488353639816, -0.64468218821097534,
      -0.66388533420956908, -0.68283081814474, -0.70151521885018542,
      -0.71993519805916628, -0.73808750105670606, -0.75596895730542446,
      -0.77357648104492061, -0.79090707186455078, -0.80795781524954047,
      -0.82472588310031658, -0.84120853422498654, -0.85740311480488574,
      -0.87330705883312953, -0.888917888526095, -0.90423321470783435,
      -0.91925073716730432, -0.93396824498844011, -0.94838361685302319,
      -0.96249482131633235, -0.97629991705557029, -0.98979705309107346,
      -1.0029844689803045, -1.0158604949846552, -1.028423552209079,
      -1.0406721527145963, -1.0526048996037085, -1.0642204870787764,
      -1.0755177004734213, -1.0864954162570197, -1.0971526020123596,
      -1.1074883163865519, -1.1175017090152946, -1.1271920204205668,
      -1.1365585818818817, -1.1456008152812145, -1.1543182329217156,
      -1.1627104373203541, -1.1707771209746261, -1.1785180661034695,
      -1.1859331443625591, -1.1930223165341185, -1.19978563219144,
      -1.2062232293382804, -1.2123353340233152, -1.218122259929856,
      -1.2235844079410148, -1.2287222656805243, -1.2335364070294421,
      -1.2380274916189447, -1.2421962642994353, -1.2460435545862121,
      -1.2495702760819352, -1.2527774258761191, -1.2556660839219451,
      -1.2582374123906082, -1.2604926550034989, -1.2624331363424686,
      -1.264060261138469, -1.2653755135388627, -1.2663804563536616,
      -1.2670767302810177, -1.2674660531122632, -1.2675502189167855,
      -1.2673310972070919, -1.2668106320843389, -1.2659908413646723,
      -1.2648738156866972, -1.263461717600433, -1.2617567806380507,
      -1.2597613083667731, -1.2574776734242712, -1.2549083165368942,
      -1.2520557455211276, -1.2489225342685943, -1.2455113217150005,
      -1.2418248107933656, -1.2378657673719284, -1.2336370191771135,
      -1.2291414547019022, -1.2243820221000288, -1.2193617280663613,
      -1.2140836367038847, -1.2085508683776476, -1.2027665985560934,
      -1.1967340566401632, -1.1904565247805647, -1.1839373366836419,
      -1.1771798764062065, -1.1701875771397789, -1.1629639199846245,
      -1.1555124327140021, -1.14783668852907, -1.1399403048048067,
      -1.1318269418274185, -1.1235003015236233, -1.1149641261822325,
      -1.1062221971684889, -1.0972783336315153, -1.088136391205363,
      -1.0788002607040406, -1.0692738668109871, -1.0595611667633698,
      -1.0496661490316677, -1.0395928319949543, -1.0293452626122905,
      -1.0189275150907082, -1.0083436895501172, -0.9975979106856554,
      -0.98669432642785371, -0.975637106601039, -0.96443044158044089,
      -0.9530785409483693, -0.941585632149924, -0.92995595914863993,
      -0.91819378108249661, -0.90630337092069391, -0.894289014121632,
      -0.88215500729249186, -0.86990565685082943, -0.85754527768861966,
      -0.84507819183911681, -0.83250872714698387, -0.81984121594204606,
      -0.807079993717111, -0.79422939781024759, -0.78129376609189549,
      -0.76827743565722373, -0.75518474152412463, -0.74202001533721085,
      -0.72878758407824418, -0.71549176878333132, -0.70213688326727919,
      -0.68872723285549731, -0.6752671131238156, -0.66176080864656184,
      -0.64821259175329027, -0.63462672129450648, -0.62100744141673392,
      -0.6073589803473215, -0.5936855491892522, -0.57999134072638714,
      -0.56628052823943054, -0.552557264332949, -0.53882567977381124,
      -0.5250898823413257, -0.51135395568942932, -0.49762195822122784,
      -0.48389792197619896, -0.47018585153036752, -0.4564897229097461,
      -0.44281348251733627, -0.42916104607398081, -0.41553629757336025,
      -0.4019430882513797, -0.38838523557027538, -0.37486652221762995,
      -0.36139069512062927, -0.34796146447578841, -0.33458250279437707,
      -0.3212574439638215, -0.30798988232529961, -0.29478337176776293,
      -0.28164142483862464, -0.26856751187131861, -0.25556506012994051,
      -0.242637452971198, -0.22978802902384554, -0.2170200813858246,
      -0.20433685683927172, -0.19174155508359086, -0.17923732798676664,
      -0.16682727885508697, -0.15451446172141542, -0.14230188065220914,
      -0.13019248907339925, -0.11818918911528448, -0.10629483097658662,
      -0.094512212307775234, -0.082844077613800943, -0.071293117676359985,
      -0.059861968995758991, -0.048553213252533235, -0.037369376788895382,
      -0.026312930110081588, -0.015386287405708653, -0.0045918060912008354,
      0.0060682136306416945, 0.016591529187870543, 0.026975956037348439,
      0.037219368042422388, 0.04731969783022541, 0.057274937128605832,
      0.067083137082642366, 0.0767424085507246, 0.086250922380186848,
      0.095606909662488332, 0.10480866196792454, 0.11385453155990764,
      0.12274293158878756, 0.13147233626525912, 0.140041281013384,
      0.14844836260322214, 0.15669223926316825, 0.16477163077198684,
      0.17268531853062405, 0.18043214561385243, 0.18801101680180146,
      0.19542089859145317, 0.20266081918817871, 0.20972986847739289,
      0.21662719797643162, 0.22335202076672306, 0.22990361140637636,
      0.23628130582328688, 0.24248450118885681, 0.24851265577249415,
      0.25436528877695641, 0.2600419801547183, 0.26554237040547107,
      0.27086616035491962, 0.27601311091500091, 0.28098304282569825,
      0.28577583637859721, 0.29039143112235477, 0.29482982555025378,
      0.29909107677000529, 0.30317530015599953, 0.30708266898417164,
      0.310813414049679, 0.31436782326760487, 0.31774624125685152,
      0.32094906890746, 0.32397676293155231, 0.32682983539811911,
      0.32950885325186124, 0.33201443781631551, 0.3343472642814953,
      0.33650806117626825, 0.338497609825726, 0.34031674379376825,
      0.34196634831114692, 0.3434473596892384, 0.34476076471976563,
      0.34590760006076615, 0.34688895160902106, 0.34770595385924363,
      0.34835978925027478, 0.34885168749855744, 0.34918292491918496,
      0.349354823734761, 0.34936875137238332, 0.34922611974901352,
      0.34892838454553859, 0.34847704446978839, 0.34787364050881514,
      0.34711975517072324, 0.34621701171633762, 0.34516707338103381,
      0.34397164258698854, 0.34263246014619775, 0.34115130445452008,
      0.3395299906770855, 0.33777036992537912, 0.33587432842627146,
      0.33384378668335113, 0.3316806986308245, 0.32938705078035813,
      0.32696486136111291, 0.32441617945332335, 0.32174308411573388,
      0.31894768350720654, 0.31603211400279768, 0.31299853930468213,
      0.30984914954816439, 0.30658616040315606, 0.30321181217141241,
      0.29972836887987059, 0.29613811737037543, 0.29244336638615176,
      0.28864644565530889, 0.28474970497171825, 0.28075551327359949,
      0.27666625772008091, 0.27248434276611011, 0.2682121892360057,
      0.26385223339595615, 0.25940692602582949, 0.25487873149054374,
      0.2502701268113674, 0.2455836007374344, 0.24082165281780032,
      0.23598679247433899, 0.23108153807579934, 0.22610841601331944,
      0.22106995977771282, 0.21596870903883672, 0.21080720872732223,
      0.2055880081189963, 0.20031365992226796, 0.19498671936878426,
      0.18960974330767905, 0.18418528930364392, 0.17871591473917081,
      0.17320417592122844, 0.16765262719263849, 0.16206382004848632,
      0.15644030225778294, 0.15078461699069529, 0.14509930195160206,
      0.13938688851826114, 0.13364990088732737, 0.12789085522651569,
      0.12211225883364385, 0.11631660930283105, 0.11050639369810661,
      0.10468408773465462, 0.098852154967976363, 0.0930130459911874,
      0.0871691976406942, 0.081323032210509821, 0.075476956675398527,
      0.069633361923108178, 0.063794621995916373, 0.057963093341685666,
      0.05214111407466606, 0.046331003246253125, 0.040535060125900274,
      0.034755563492394587, 0.028994770935703525, 0.023254918169567568,
      0.017538218355052197, 0.011846861435224891, 0.0061830134811519874,
      0.00054881604938884776, -0.0050536144488664766, -0.0106221873667844,
      -0.016154838428926011, -0.021649530326107509, -0.027104253297950819,
      -0.032517025702986986, -0.037885894576159436, -0.043208936173583463,
      -0.048484256504431035, -0.053709991849820712, -0.058884309268573465,
      -0.064005407089725658, -0.0690715153916816, -0.074080896467896257,
      -0.0790318452789819, -0.083922689891142127, -0.088751791900843841,
      -0.0935175468456233, -0.098218384600961148, -0.10285276976313022,
      -0.10741920201795455, -0.11191621649540873, -0.11634238410998636,
      -0.12069631188678977, -0.12497664327328317, -0.12918205843665764,
      -0.1333112745467705, -0.13736304604462005, -0.14133616489632309,
      -0.14522946083256258, -0.14904180157349031, -0.15277209303906272,
      -0.1564192795448105, -0.15998234398299765, -0.16346030798921854,
      -0.16685223209440114, -0.17015721586223284, -0.17337439801203061,
      -0.17650295652705117, -0.17954210874830018, -0.18249111145383159,
      -0.18534926092359058, -0.18811589298983072, -0.19079038307315532,
      -0.19337214620422069, -0.19586063703115419, -0.19825534981275894,
      -0.20055581839754, -0.2027616161886473, -0.20487235609478727,
      -0.20688769046717226, -0.20880731102263009, -0.21063094875288757,
      -0.21235837382018802, -0.21398939543929471, -0.21552386174598159,
      -0.2169616596521359, -0.21830271468755141, -0.21954699082853701,
      -0.22069449031346228, -0.22174525344533405, -0.22269935838156263,
      -0.22355692091101254, -0.22431809421848528, -0.2249830686367616,
      -0.22555207138635808, -0.22602536630311099, -0.22640325355376334,
      -0.22668606933968877, -0.22687418558890077, -0.22696800963652722,
      -0.22696798389389422, -0.22687458550636136, -0.22668832600013231,
      -0.22640975091814886, -0.22603943944529331, -0.22557800402303529,
      -0.22502608995372714, -0.22438437499472705, -0.2236535689425164,
      -0.22283441320703712, -0.22192768037639976, -0.22093417377218105,
      -0.21985472699549152, -0.21869020346403684, -0.21744149594033993,
      -0.21610952605135236, -0.21469524379965294, -0.21319962706643802,
      -0.21162368110652063, -0.2099684380355448, -0.20823495630963107,
      -0.20642432019767112, -0.20453763924647678, -0.20257604773903481,
      -0.2005407041460435, -0.19843279057099283, -0.19625351218897993,
      -0.1940040966795239, -0.19168579365356692, -0.18929987407490922,
      -0.1868476296763123, -0.18433037237047775, -0.18174943365617136,
      -0.17910616401967461, -0.17640193233184681, -0.17363812524098182,
      -0.17081614656173164, -0.16793741666032749, -0.16500337183630587,
      -0.16201546370100361, -0.15897515855304462, -0.15588393675104747,
      -0.1527432920838267, -0.1495547311382614, -0.14631977266512869,
      -0.14303994694308833, -0.13971679514110419, -0.13635186867949034,
      -0.13294672858984075, -0.12950294487408337, -0.12602209586286403,
      -0.12250576757354643, -0.11895555306798578, -0.11537305181038182,
      -0.11175986902539749, -0.10811761505677997, -0.1044479047267405,
      -0.10075235669627809, -0.0970325928267134, -0.093290237542622584,
      -0.089526917196440223, -0.08574425943490939, -0.081943892567625493,
      -0.078127444937895058, -0.074296544296105146, -0.070452817175863255,
      -0.066597888273074, -0.0627333798281984, -0.058860911011898019,
      -0.054982097314262096, -0.051098549937858818, -0.047211875194770839,
      -0.043323673907856242, -0.0394355408164128, -0.035549063986452675,
      -0.03166582422579501, -0.027787394504149396, -0.023915339378397696,
      -0.020051214423245381, -0.016196565667469506, -0.012352929035895889,
      -0.0085218297973167, -0.0047047820185281627, -0.00090328802464576669,
      0.0028811621341009522, 0.0066470912089573592, 0.010393035272428394,
      0.014117544231092405, 0.017819182331301725, 0.021496528657585695,
      0.025148177623628643, 0.028772739455645985, 0.032368840668036379,
      0.035935124531130277, 0.039470251530929729, 0.042972899820674121,
      0.046441765664102339, 0.049875563870299525, 0.053273028219959044,
      0.056632911882973348, 0.059953987827218239, 0.063235049218403061,
      0.0664749098108913, 0.06967240432935945, 0.072826388841204612,
      0.075935741119590852, 0.078999360997030588, 0.082016170709416011,
      0.084985115230386349, 0.087905162595970171, 0.090775304219395572,
      0.093594555196008511, 0.09636195459818403, 0.099076565760210109,
      0.10173747655302771, 0.10434379964878127, 0.10689467277512849,
      0.10938925895922048, 0.111826746761327, 0.11420635049804786,
      0.11652731045505037, 0.11878889308931029, 0.12099039122080626,
      0.12313112421363039, 0.12521043814649613, 0.12722770597260305,
      0.12918232766884302, 0.13107373037432271, 0.13290136851819984,
      0.13466472393679479, 0.13636330598000912, 0.13799665160700939,
      0.13956432547119185, 0.14106591999444593, 0.14250105543068803,
      0.14386937991872381, 0.14517056952440838, 0.14640432827215238,
      0.14757038816578974, 0.14866850919883584, 0.14969847935414451,
      0.15066011459303474, 0.1515532588339058, 0.15237778392036419,
      0.15313358957893508, 0.15382060336639825, 0.1544387806067932,
      0.15498810431816187, 0.15546858512906597, 0.15588026118495732,
      0.15622319804447932, 0.15649748856574264, 0.15670325278265407,
      0.15684063777139057, 0.1569098175070803, 0.15691099271078035,
      0.15684439068683392, 0.15671026515071471, 0.15650889604739285,
      0.15624058936041535, 0.15590567691168081, 0.15550451615213295,
      0.15503748994335209, 0.15450500633028139, 0.15390749830506392,
      0.1532454235622259, 0.15251926424523213, 0.15172952668458084,
      0.15087674112754138, 0.14996146145966649, 0.14898426491818784,
      0.14794575179744132, 0.14684654514646034, 0.14568729045884454,
      0.1444686553550466, 0.14319132925725125, 0.14185602305692577,
      0.14046346877525218, 0.13901441921650723, 0.13750964761463447,
      0.13594994727304791, 0.13433613119794602, 0.13266903172512937,
      0.13094950014065265, 0.12917840629532412, 0.12735663821328944,
      0.12548510169483629, 0.12356471991358005, 0.12159643300819804,
      0.11958119766888221, 0.11751998671866662, 0.11541378868979575,
      0.11326360739532468, 0.11107046149607186, 0.10883538406317696,
      0.10655942213636015, 0.10424363627806302, 0.1018891001237236,
      0.099496899928235391, 0.097068134108919971, 0.094603912785019242,
      0.092105357314032424, 0.0895735998249864, 0.087009782748871389,
      0.08441505834637307, 0.081790588233134648, 0.079137542902669028,
      0.0764571012471741, 0.073750450076363952, 0.071018783634533331,
      0.068263303116046711, 0.065485216179387032, 0.0626857364600152,
      0.0598660830821504, 0.057027480169717051, 0.054171156356569786,
      0.051298344296249812, 0.0484102801714241, 0.045508203203156072,
      0.042593355160247495, 0.039666979868771379, 0.036730322722041006,
      0.03378463019113058, 0.030831149336162295, 0.027871127318529212,
      0.024905810914218375, 0.021936446028449526, 0.018964277211737469,
      0.015990547177633305, 0.013016496322217783, 0.010043362245642104,
      0.0070723792757593842, 0.0041047779941407875, 0.001141784764501573,
      -0.0018153787361332926, -0.00476549598349825, -0.0077073560691492959,
      -0.010639754160370468, -0.013561491956777763, -0.016471378143460745,
      -0.019368228840464997, -0.022250868048522075, -0.02511812809081912,
      -0.027968850050677944, -0.030801884204992948, -0.033616090453277618,
      -0.03641033874213908, -0.0391835094851249, -0.0419344939776674,
      -0.044662194807116994, -0.047365526257602993, -0.050043414709718306,
      -0.0526947990347309, -0.055318630983365466, -0.05791387556886482,
      -0.060479511444314779, -0.063014531274053348, -0.065517942099050611,
      -0.06798876569614265, -0.070426038931004173, -0.072828814104722389,
      -0.075196159293884485, -0.077527158684055048, -0.079820912896540308,
      -0.082076539308299543, -0.084293172364985666, -0.086469963886885867,
      -0.088606083367806537, -0.090700718266677749, -0.092753074291887477,
      -0.094762375678170779, -0.096727865456047987, -0.0986488057136586,
      -0.10052447785095164, -0.10235418282613036, -0.10413724139429503,
      -0.10587299433819591, -0.10756080269104147, -0.10920004795126877,
      -0.11079013228924667, -0.11233047874582611, -0.11382053142268633,
      -0.11525975566442954, -0.11664763823235774, -0.11798368746988942,
      -0.11926743345959348, -0.12049842817173827, -0.12167624560439975,
      -0.12280048191499854, -0.12387075554332191, -0.12488670732593278,
      -0.12584800060197654, -0.12675432131034439, -0.12760537807817735,
      -0.12840090230069551, -0.12914064821233279, -0.12982439294916742,
      -0.13045193660263876, -0.13102310226454683, -0.1315377360633293,
      -0.13199570719161716, -0.13239690792507805, -0.13274125363253686,
      -0.13302868277741164, -0.13325915691044793, -0.13343266065378778,
      -0.1335492016763826, -0.13360881066077274, -0.13361154126126584,
      -0.13355747005352839, -0.13344669647563373, -0.13327934276059528,
      -0.13305555386041723, -0.13277549736171351, -0.13243936339292486,
      -0.13204736452318827, -0.131599735652903, -0.13109673389604548,
      -0.13053863845428576, -0.12992575048296653, -0.12925839294899388,
      -0.12853691048071755, -0.12776166920984994, -0.126933056605499,
      -0.12605148130039059, -0.12511737290933883, -0.12413118184005563,
      -0.12309337909636263, -0.12200445607390417, -0.12086492434841856,
      -0.11967531545668612, -0.11843618067021081, -0.11714809076174636,
      -0.11581163576474986, -0.11442742472586054, -0.11299608545050822,
      -0.11151826424173535, -0.10999462563234966, -0.10842585211050478,
      -0.10681264383881732, -0.1051557183671168, -0.10345581033897708,
      -0.10171367119208105, -0.099930068852587262, -0.098105787423592758,
      -0.0962416268678062, -0.094338402684561659, -0.092396945581290843,
      -0.090418101139570856, -0.088402729475895087, -0.086351704897266207,
      -0.084265915551755027, -0.082146263074161868, -0.079993662226902629,
      -0.0778090405362389, -0.075593337924037662, -0.073347506335126739,
      -0.071072509360451952, -0.068769321856107457, -0.0664389295584665,
      -0.064082328695437465, -0.061700525594123631, -0.059294536284905233,
      -0.056865386102169943, -0.054414109281819278, -0.051941748555660722,
      -0.049449354742910873, -0.046937986338848964, -0.044408709100901639,
      -0.041862595632178354, -0.039300724962704647, -0.03672418212849092,
      -0.034134057748480481, -0.031531447599757234, -0.028917452190872939,
      -0.026293176333737747, -0.023659728714001335, -0.021018221460218353,
      -0.01836976971187311, -0.015715491186499224, -0.013056505745930917,
      -0.010393934961992791, -0.0077289016816258563, -0.0050625295917495622,
      -0.0023959427838941838, 0.0002697346811528431, 0.0029333792085630764,
      0.00559386810443141, 0.0082500800102303026, 0.010900895336737555,
      0.013545196697149944, 0.016181869339282888, 0.018809801576794405,
      0.021427885219063234, 0.024035015999806411, 0.026630094004110129,
      0.029212024093810983, 0.031779716331066063, 0.034332086399928165,
      0.036868056025780617, 0.039386553392564833, 0.041886513557501677,
      0.044366878863324771, 0.046826599347752976, 0.049264633150103335,
      0.051679946914952868, 0.054071516192582672, 0.0564383258362082,
      0.058779370395736177, 0.061093654507957312, 0.063380193283089886,
      0.065638012687381592, 0.067866149921875563, 0.070063653796925945,
      0.072229585102562791, 0.074363016974476309, 0.076463035255452727,
      0.078528738852239877, 0.080559240087627659, 0.082553665047629551,
      0.084511153923720619, 0.086430861349908128, 0.088311956734545755,
      0.09015362458685601, 0.091955064837894326, 0.093715493156003249,
      0.095434141256488081, 0.097110257205568359, 0.0987431057183271,
      0.10033196845068303, 0.10187614428526015, 0.10337494961094848,
      0.10482771859620768, 0.10623380345592874, 0.10759257471174002,
      0.10890342144575009, 0.11016575154755651, 0.11137899195444154,
      0.11254258888475463, 0.1136560080642495, 0.11471873494544305,
      0.11573027491981895, 0.11669015352281784, 0.11759791663160467,
      0.11845313065541659, 0.11925538271856942, 0.12000428083591561,
      0.12069945408080543, 0.12134055274540698, 0.12192724849336696,
      0.12245923450476065, 0.12293622561324025, 0.12335795843535405,
      0.12372419149201416, 0.12403470532199526, 0.12428930258749887,
      0.12448780817169548, 0.12463006926819792, 0.12471595546248448,
      0.12474535880518635, 0.12471819387720788, 0.1246343978467192,
      0.12449393051789014, 0.12429677437145945, 0.12404293459700613,
      0.12373243911701713, 0.12336533860262749, 0.12294170648112618,
      0.12246163893513308, 0.12192525489350092, 0.12133269601390489,
      0.12068412665713943, 0.1199797338530999, 0.1192197272585012,
      0.11840433910628155, 0.11753382414674721, 0.11660845958045926,
      0.11562854498286892, 0.11459440222072446, 0.11350637536029985,
      0.11236483056740081, 0.11117015599927461, 0.10992276168833641,
      0.10862307941787477, 0.10727156258963745, 0.1058686860834564,
      0.10441494610885786, 0.10291086004877581, 0.10135696629534101,
      0.099753824077876627, 0.098102013283065156, 0.09640213426742178,
      0.094654807662065285, 0.092860674169884944, 0.091020394355146084,
      0.089134648425611251, 0.087204136007234451, 0.085229575911487249,
      0.083211705895427063, 0.081151282414529041, 0.07904908036839331,
      0.076905892839404716, 0.074722530824398378, 0.072499822959464555,
      0.070238615237907309, 0.067939770721527057, 0.0656041692452427,
      0.06323270711520175, 0.060826296800439786, 0.058385866618194643,
      0.055912360412983308, 0.053406737229532722, 0.0508699709796651,
      0.048303050103264966, 0.04570697722340053, 0.043082768795734194,
      0.04043145475233173, 0.037754078139964314, 0.035051694753057333,
      0.032325372761346768, 0.029576192332418122, 0.026805245249208534,
      0.024013634522609059, 0.021202473999315422, 0.018372887964985984,
      0.015526010742921079, 0.012662986288318995, 0.0097849677782789052,
      0.0068931171976849975, 0.00398860492105714, 0.0010726092905948142,
      -0.0018536838095621067, -0.00478908138262496, -0.0077323837519033267,
      -0.010682384996874933, -0.013637873392402806, -0.01659763185098892,
      -0.019560438367921359, -0.022525066469112107, -0.025490285661581825,
      -0.028454861886356715, -0.0314175579736327, -0.034377134100163111,
      -0.037332348248545255, -0.040281956668437854, -0.043224714339416118,
      -0.046159375435370131, -0.049084693790346107, -0.051999423365534952,
      -0.054902318717428775, -0.05779213546683723, -0.060667630768697994,
      -0.063527563782516422, -0.066370696143223162, -0.069195792432390352,
      -0.072001620649539064, -0.074786952683442348, -0.077550564783298553,
      -0.0802912380295227, -0.083007758804096166, -0.0856989192602495,
      -0.0883635177913265, -0.091000359498752126, -0.093608256658793215,
      -0.0961860291881355, -0.0987325051079692, -0.10124652100648179,
      -0.10372692249966013, -0.10617256469012497, -0.10858231262393242,
      -0.11095504174518159, -0.11328963834818659, -0.11558500002721141,
      -0.11784003612343469, -0.12005366816912535, -0.1222248303288347,
      -0.12435246983740829, -0.1264355474347526, -0.12847303779711888,
      -0.13046392996478409, -0.13240722776604677, -0.13430195023723973,
      -0.13614713203878515, -0.13794182386700937, -0.13968509286162051,
      -0.14137602300875582, -0.14301371553933956, -0.14459728932274135,
      -0.14612588125548509, -0.14759864664490133, -0.14901475958767,
      -0.15037341334292703, -0.15167382070004015, -0.15291521434068239,
      -0.15409684719524894, -0.15521799279339152, -0.15627794560858871,
      -0.15727602139655866, -0.15821155752750019, -0.1590839133118887,
      -0.15989247031986747, -0.16063663269394612, -0.1613158274550511,
      -0.16192950480167406, -0.16247713840206374, -0.16295822567938018,
      -0.16337228808962556, -0.16371887139226382, -0.16399754591351223,
      -0.1642079068020024, -0.1643495742769569, -0.16442219386853918,
      -0.16442543665045226, -0.16435899946460955, -0.16422260513778214,
      -0.16401600269017666, -0.16373896753579817, -0.1633913016745201,
      -0.16297283387585318, -0.16248341985417758, -0.16192294243553168,
      -0.16129131171574251, -0.16058846520986897, -0.15981436799294174,
      -0.15896901283180903, -0.15805242030813829, -0.15706463893244577,
      -0.15600574524906063, -0.15487584393208134, -0.15367506787210566,
      -0.15240357825384521, -0.15106156462441395, -0.14964924495236476,
      -0.14816686567737197, -0.14661470175051217, -0.14499305666510845,
      -0.14330226247813, -0.14154267982204183, -0.1397146979071667,
      -0.1378187345144351, -0.135855235978538, -0.13382467716150104,
      -0.1317275614165519, -0.12956442054238859, -0.12733581472770988,
      -0.12504233248610069, -0.12268459058120122, -0.12026323394214478,
      -0.11777893556933275, -0.11523239643044399, -0.11262434534676738,
      -0.10995553886981693, -0.1072267611482438, -0.10443882378507272,
      -0.10159256568524705, -0.098688852893531451, -0.095728578422770369,
      -0.09271266207253244, -0.08964205023816206, -0.086517715710286033,
      -0.083340657464759535, -0.080111900443162257, -0.07683249532379223,
      -0.073503518283276434, -0.070126070748803684, -0.066701279141009914,
      -0.063230294607625581, -0.05971429274785367, -0.056154473327631169,
      -0.052552059985727678, -0.048908299930841545, -0.045224463629682368,
      -0.041501844486145134, -0.037741758511645004, -0.033945543986660651,
      -0.030114561113603361, -0.026250191661033387, -0.022353838599379339,
      -0.018426925728167273, -0.014470897294890483, -0.010487217605630345,
      -0.006477370627443621, -0.0024428595827084565, 0.0016147934645529549,
      0.0056940480302277441, 0.00979334563946177, 0.013911110263671866,
      0.018045748765164418, 0.022195651349162654, 0.026359192023246616,
      0.030534729063953589, 0.034720605490557957, 0.038915149545778044,
      0.043116675183395896, 0.04732348256259955, 0.051533858548920675,
      0.055746077221679367, 0.0599584003877672, 0.06416907810160799,
      0.068376349191250324, 0.072578441790327825, 0.076773573875863657,
      0.080959953811676783, 0.085135780897299146, 0.0892992459222577,
      0.093448531725526029, 0.09758181376003143, 0.10169726066205606,
      0.10579303482535424, 0.1098672929798591, 0.11391818677477626,
      0.11794386336595397, 0.12194246600732342, 0.12591213464623335,
      0.12985100652258097, 0.13375721677148664, 0.1376288990293717,
      0.14146418604331984, 0.14526121028341812, 0.14901810455807568,
      0.15273300263197509, 0.156404039846568, 0.16002935374297458,
      0.16360708468695384, 0.16713537649594881, 0.17061237706787502,
      0.17403623901153134, 0.17740512027847552, 0.18071718479608462,
      0.18397060310173241, 0.18716355297777248, 0.19029422008722746,
      0.19336079860996228, 0.19636149187912949, 0.19929451301773987,
      0.20215808557512477, 0.20495044416308525, 0.20766983509162476,
      0.21031451700392639, 0.21288276151052563, 0.21537285382237847,
      0.21778309338265037, 0.22011179449709495, 0.22235728696273793,
      0.22451791669469828, 0.22659204635100563, 0.22857805595510181,
      0.23047434351597221, 0.23227932564556372, 0.23399143817340343,
      0.23560913675818665, 0.23713089749608612, 0.23855521752569298,
      0.23988061562928006, 0.24110563283025824, 0.24222883298664671,
      0.24324880338026844, 0.24416415530160698, 0.24497352463002237,
      0.24567557240915722, 0.24626898541743059, 0.24675247673325015,
      0.24712478629497339, 0.24738468145520515, 0.24753095752939752,
      0.2475624383385438, 0.24747797674567554, 0.24727645518613017,
      0.24695678619127615, 0.24651791290556613, 0.24595880959676747,
      0.245278482159127, 0.2444759686093011, 0.24355033957495187,
      0.24250069877569058, 0.24132618349635418, 0.24002596505229187,
      0.2385992492466236, 0.23704527681919488, 0.23536332388709813,
      0.23355270237665657, 0.23161276044655926, 0.22954288290217456,
      0.22734249160070125, 0.2250110458471089, 0.22254804278070289,
      0.21995301775210763, 0.21722554469054925, 0.21436523646133027,
      0.21137174521323521, 0.20824476271586106, 0.20498402068662086,
      0.20158929110731805, 0.1980603865302093, 0.19439716037328642,
      0.19059950720481994, 0.1866673630168586, 0.18260070548770524,
      0.17839955423314102, 0.17406397104635035, 0.16959406012635669,
      0.16498996829493368, 0.1602518852017924, 0.15538004351803616,
      0.15037471911764239, 0.14523623124703466, 0.13996494268247572,
      0.13456125987530865, 0.12902563308488951, 0.12335855649914362,
      0.11756056834264209, 0.11163225097214274, 0.10557423095944686,
      0.099387179161607622, 0.093071810778304884, 0.086628885396344169,
      0.080059207021297457, 0.073363624096056387, 0.066543029506432871,
      0.05959836057354416, 0.052530599033139377, 0.045340771001638053,
      0.038029946928914593, 0.03059924153783819, 0.023049813750390447,
      0.015382866600474165, 0.0075996471332655247, -0.00029855370883778709,
      -0.0083104012137393268, -0.016434517040665356, -0.024669479374663392,
      -0.033013823094583353, -0.041466039954662234, -0.050024578779517312,
      -0.058687845672774339, -0.067454204239127735, -0.076321975819979168,
      -0.085289439742526008, -0.094354833582394965, -0.10351635343967866,
      -0.11277215422850076, -0.12212034997990671, -0.13155901415824156,
      -0.1410861799907947, -0.15069984081083843, -0.16039795041387711,
      -0.17017842342716177, -0.18003913569238711, -0.18997792466146168,
      -0.19999258980541568, -0.21008089303623279, -0.22024055914169283,
      -0.2304692762330077, -0.24076469620529567, -0.25112443521076605,
      -0.26154607414448827, -0.27202715914277031, -0.28256520209392061,
      -0.29315768116143615, -0.30380204131938093, -0.31449569489999424,
      -0.32523602215327929, -0.33602037181860789, -0.34684606170807641,
      -0.35771037930163474, -0.3686105823537848, -0.37954389951171541,
      -0.39050753094482932, -0.40149864898541276, -0.4125143987804078,
      -0.42355189895410589, -0.43460824228160289, -0.44568049637293095,
      -0.45676570436760511, -0.46786088563958605, -0.47896303651231409,
      -0.49006913098385529, -0.50117612146179213, -0.51228093950784681,
      -0.52338049659201336, -0.53447168485595431, -0.54555137788561325,
      -0.55661643149273932, -0.56766368450522575, -0.578689959566007,
      -0.58969206394038431, -0.60066679033151271, -0.61161091770395,
      -0.6225212121149255, -0.63339442755328179, -0.64422730678578433,
      -0.65501658221055481, -0.665758976717575, -0.67645120455581931,
      -0.68708997220703572, -0.69767197926573532, -0.70819391932531184,
      -0.71865248087005174, -0.72904434817267061, -0.73936620219737226,
      -0.74961472150795339, -0.75978658318090719, -0.7698784637231787,
      -0.77988703999435927, -0.78980899013311168, -0.799640994487507,
      -0.80937973654908346, -0.81902190389037421, -0.82856418910561047,
      -0.8380032907543884, -0.84733591430804245, -0.85655877309839368,
      -0.86566858926877688, -0.87466209472685941, -0.88353603209921616,
      -0.89228715568724626, -0.90091223242417828, -0.90940804283302368,
      -0.91777138198501529, -0.92599906045843128, -0.93408790529744823,
      -0.94203476097074124, -0.94983649032965478, -0.95748997556552684,
      -0.96499211916601046, -0.972339844870078, -0.97953009862140761,
      -0.98655984951991382, -0.99342609077113, -1.000125840633145,
      -1.0066561433608638, -1.0130140701472574, -1.0191967200613743,
      -1.0252012209828083, -1.03102473053231, -1.0366644369983886,
      -1.0421175602594202, -1.0473813527012241, -1.0524531001296153,
      -1.0573301226777658, -1.0620097757081526, -1.0664894507086029,
      -1.0707665761824527, -1.0748386185322614, -1.0787030829370097,
      -1.0823575142224078, -1.0857994977240724, -1.0890266601432723,
      -1.0920366703950286, -1.0948272404482173, -1.0973961261575025,
      -1.0997411280867202, -1.1018600923235708, -1.1037509112852482,
      -1.1054115245147829, -1.1068399194678908, -1.1080341322899461,
      -1.1089922485829613, -1.1097124041622046, -1.1101927858022422,
      -1.1104316319721939, -1.1104272335598864, -1.1101779345846641,
      -1.1096821328986948, -1.1089382808763852, -1.1079448860918126,
      -1.106700511983828, -1.1052037785086248, -1.1034533627795968,
      -1.1014479996941389, -1.0991864825472988, -1.09666766363194,
      -1.0938904548252384, -1.0908538281613549, -1.0875568163899225,
      -1.0839985135203158, -1.0801780753513328, -1.0760947199861572,
      -1.0717477283324794, -1.0671364445873419, -1.0622602767068208,
      -1.0571186968600843, -1.0517112418677954, -1.0460375136246347,
      -1.0400971795057412, -1.033889972756922, -1.0274156928684544,
      -1.0206742059322804, -1.013665444982488, -1.0063894103188757,
      -0.99884616981342, -0.99103585919960624, -0.98295868234429407,
      -0.97461491150219037, -0.96600488755256786, -0.95712902021830926,
      -0.94798778826697339, -0.93858173969383463, -0.92891149188682764,
      -0.9189777317731479, -0.9087812159475348, -0.89832277078202516,
      -0.88760329251716164, -0.87662374733447412, -0.86538517141024085,
      -0.853888670950341, -0.84213542220618487, -0.83012667147165042,
      -0.8178637350608815, -0.80534799926699907, -0.79258092030151006,
      -0.77956402421455628, -0.76629890679572144, -0.75278723345559617,
      -0.73903073908782935, -0.72503122791180163, -0.71079057329585293,
      -0.69631071756092788, -0.68159367176482877, -0.66664151546683714,
      -0.65145639647289888, -0.63604053056123233, -0.62039620118838867,
      -0.60452575917588425, -0.58843162237721758, -0.57211627532552045,
      -0.55558226886165119, -0.53883221974297246, -0.52186881023263487,
      -0.50469478766963116, -0.48731296401948582, -0.46972621540570519,
      -0.45193748162213676, -0.43394976562609483, -0.41576613301257831,
      -0.39738971146940272, -0.3788236902135671, -0.36007131940876425,
      -0.34113590956418738, -0.32202083091482325, -0.3027295127831427,
      -0.28326544292253486, -0.26363216684235052, -0.24383328711495353,
      -0.22387246266460098 } ;

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
      25.97, 25.98, 25.990000000000002 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 1.1950511061897453, 1.1964641268440197, 1.1977298715134412,
      1.1988469545462668, 1.1998140134723816, 1.2006297095528822,
      1.2012927283258816, 1.201801780148319, 1.2021556007335694,
      1.2023529516846563, 1.2023926210228488, 1.2022734237114556,
      1.2019942021746013, 1.2015538268107873, 1.2009511965010369,
      1.2001852391114263, 1.1992549119897975, 1.1981592024564578,
      1.1968971282886733, 1.1954677381987582, 1.1938701123055617,
      1.192103362599173, 1.1901666333986387, 1.1880591018025148,
      1.185779978132063, 1.1833285063669035, 1.180703964572942,
      1.1779056653223934, 1.1749329561057154, 1.1717852197352796,
      1.1684618747406064, 1.1649623757549792, 1.1612862138932873,
      1.1574329171209063, 1.153402050613467, 1.1491932171073409,
      1.1448060572406846, 1.1402402498848812, 1.1354955124662285,
      1.1305716012777154, 1.1254683117807409, 1.1201854788966248,
      1.114722977287768, 1.1090807216283234, 1.1032586668642321,
      1.0972568084624976, 1.0910751826495626, 1.0847138666386587,
      1.0781729788460057, 1.0714526790957395, 1.0645531688134457,
      1.0574746912081885, 1.0502175314429221, 1.0427820167931732,
      1.035168516793896, 1.0273774433743956, 1.0194092509812203,
      1.0112644366889374, 1.0029435402986935, 0.994447144424482,
      0.98577587456703031, 0.97693039917523228, 0.96791142969505106,
      0.95871972060582211, 0.949356069443892, 0.93982131681353,
      0.93011634638505525, 0.920242084880126, 0.91019950204414435,
      0.89998961060572613, 0.88961346622320037, 0.87907216741809946,
      0.86836685549560721, 0.85749871445193981, 0.84646897086863149,
      0.83527889379371156, 0.82392979460975313, 0.81242302688878365,
      0.80075998623405764, 0.7889421101086791, 0.77697087765108519,
      0.76484780947739661, 0.75257446747064383, 0.740152454556888,
      0.72758341446825781, 0.714869031492923, 0.7020110302120417,
      0.68901117522370892, 0.67587127085394871, 0.6625931608547917,
      0.6491787280894874, 0.6356298942049, 0.62194861929115, 0.60813690152855593,
      0.594196776821948, 0.58013031842241936, 0.56593963653659174,
      0.55162687792347354, 0.53719422547899476, 0.52264389780830445,
      0.507978148785925, 0.49319926710385775, 0.47830957580774247,
      0.46331143182117512, 0.448207225458293, 0.4329993799247398,
      0.41769035080713213, 0.40228262555114591, 0.38677872292834925,
      0.37118119249191439, 0.35549261402134241, 0.33971559695633574,
      0.32385277981996824, 0.307906829631291, 0.29188044130753166,
      0.2757763370560361, 0.25959726575611558, 0.24334600233095594,
      0.22702534710976077, 0.21063812518029384, 0.19418718573199439,
      0.17767540138984456, 0.16110566753916722, 0.14448090164153865,
      0.12780404254200467, 0.11107804976778846, 0.0943059028186877,
      0.077490600449355115, 0.060635159943665418, 0.043742616381372376,
      0.026816021897260511, 0.0098584449330050283, -0.0071270305180488464,
      -0.024137305672972689, -0.041169267727984765, -0.058219790633608562,
      -0.0752857358760253, -0.092363953264406329, -0.10945128172398361,
      -0.12654455009463644, -0.14364057793475177, -0.16073617633012835,
      -0.1778281487076836, -0.19491329165371435, -0.21198839573648581,
      -0.2290502463328819, -0.24609562445888897, -0.26312130760365071,
      -0.28012407056684824, -0.29710068629915554, -0.31404792674550791,
      -0.33096256369093852, -0.3478413696087137, -0.36468111851052137,
      -0.38147858679843838, -0.39823055411842945, -0.41493380421510578,
      -0.43158512578748359, -0.44818131334547984, -0.46471916806687535,
      -0.48119549865448535, -0.49760712219326558, -0.51395086500709231,
      -0.530223563514941, -0.5464220650862035, -0.56254322889487107,
      -0.57858392677231607, -0.59454104405840014, -0.61041148045064786,
      -0.62619215085120761, -0.64187998621133779, -0.65747193437314833,
      -0.67296496090832669, -0.68835604995358657, -0.70364220504256392,
      -0.71882044993390193, -0.73388782943525377, -0.74884141022294037,
      -0.76367828165699647, -0.778395556591346, -0.79299037217884016,
      -0.80745989067089841, -0.82180130021149533, -0.83601181562522875,
      -0.850088679199219, -0.86402916145857822, -0.87783056193519715,
      -0.89149020992960049, -0.90500546526561265, -0.91837371903759357,
      -0.93159239434999086, -0.94465894704896936, -0.95757086644586786,
      -0.97032567603225284, -0.98292093418631976, -0.9953542348704143,
      -1.0076232083194363, -1.0197255217198977, -1.0316588798794022,
      -1.0434210258863261, -1.0550097417594746, -1.0664228490874945,
      -1.0776582096578236, -1.08871372607497, -1.0995873423678995,
      -1.1102770445863357, -1.1207808613857559, -1.1310968646008928,
      -1.1412231698075339, -1.1511579368724367, -1.1608993704911543,
      -1.1704457207135934, -1.1797952834571246, -1.1889464010070512,
      -1.1978974625042755, -1.2066469044199819, -1.2151932110171715,
      -1.2235349147988781, -1.2316705969429222, -1.2395988877230208,
      -1.247318466916129, -1.2548280641958396, -1.2621264595117225,
      -1.2692124834544418, -1.2760850176065326, -1.2827429948787006,
      -1.2891853998315179, -1.2954112689823933, -1.30141969109771,
      -1.307209807470002, -1.3127808121800781, -1.3181319523439783,
      -1.3232625283446793, -1.3281718940484364, -1.3328594570056926,
      -1.3373246786364608, -1.3415670744001025, -1.3455862139494326,
      -1.3493817212690788, -1.3529532747980342, -1.3563006075363393,
      -1.3594235071358514, -1.362321815975039, -1.364995431217771,
      -1.3674443048560492, -1.3696684437366673, -1.3716679095717519,
      -1.3734428189331762, -1.3749933432308192, -1.376319708674667,
      -1.3774221962207398, -1.3783011415008519, -1.3789569347361998,
      -1.3793900206347955, -1.3796008982727497, -1.3795901209594319,
      -1.3793582960865285, -1.3789060849610244, -1.3782342026221539,
      -1.3773434176423476, -1.3762345519122297, -1.3749084804097125,
      -1.3733661309532468, -1.3716084839392821, -1.3696365720640127,
      -1.3674514800294688, -1.365054344234043, -1.3624463524475183,
      -1.3596287434706957, -1.3566028067797087, -1.3533698821551197,
      -1.3499313592959026, -1.3462886774184157, -1.3424433248404788,
      -1.3383968385506679, -1.3341508037629539, -1.3297068534568046,
      -1.3250666679028862, -1.3202319741744943, -1.3152045456448695,
      -1.3099862014705168, -1.3045788060607064, -1.2989842685332902,
      -1.2932045421570029, -1.2872416237804114, -1.2810975532476694,
      -1.2747744128012688, -1.2682743264719403, -1.2615994594559119,
      -1.2547520174796798, -1.2477342461525138, -1.2405484303068572,
      -1.2331968933268478, -1.225681996465142, -1.2180061381482592,
      -1.2101717532706469, -1.2021813124776848, -1.1940373214378457,
      -1.1857423201042303, -1.1772988819657004, -1.16870961328784,
      -1.159977152343973, -1.1511041686364789, -1.1420933621086284,
      -1.1329474623471996, -1.1236692277761038, -1.1142614448412775,
      -1.104726927187081, -1.0950685148244705, -1.0852890732911815,
      -1.0753914928042019, -1.065378687404781, -1.0552535940962415,
      -1.0450191719748694, -1.0346784013541346, -1.0242342828825326,
      -1.0136898366553002, -1.003048101320301, -0.99231213317833522,
      -0.98148500527817883, -0.97056980650660929, -0.95956964067371964,
      -0.9484876255937903, -0.93732689216201692, -0.92609058342737549,
      -0.91478185366191644, -0.90340386742677237, -0.8919597986351826,
      -0.8804528296128149, -0.86888615015568627, -0.85726295658597074,
      -0.8455864508059987, -0.83385983935073371, -0.8220863324390334,
      -0.810269143023979, -0.79841148584258659, -0.7865165764651878,
      -0.7745876303447774, -0.76262786186663556, -0.7506404833985092,
      -0.73862870434167027, -0.72659573018312051, -0.71454476154927693,
      -0.7024789932614004, -0.69040161339309, -0.67831580233012034,
      -0.6662247318329394, -0.654131564102097, -0.64203945084692027,
      -0.6299515323577124, -0.61787093658177883, -0.60580077820356559,
      -0.59374415772920286, -0.58170416057573626, -0.56968385616534178,
      -0.557686297024802, -0.54571451789053482, -0.53377153481944428,
      -0.5218603443058919, -0.50998392240505042, -0.49814522386292426,
      -0.48634718125331278, -0.47459270412197929, -0.46288467813830647,
      -0.45122596425469896, -0.43961939787400206, -0.42806778802519058,
      -0.41657391654760167, -0.40514053728395505, -0.39377037528242465,
      -0.38246612600800506, -0.37123045456343062, -0.36006599491988012,
      -0.348975349157725, -0.33796108671754183, -0.32702574366164472,
      -0.31617182194634907, -0.30540178870521495, -0.29471807554348095,
      -0.28412307784392049, -0.27361915408432858, -0.2632086251668645,
      -0.25289377375945088, -0.24267684364944542, -0.23256003910977491,
      -0.22254552427774754, -0.2126354225467196, -0.20283181597082217,
      -0.19313674468292652, -0.18355220632602687, -0.17408015549822856,
      -0.1647225032115055, -0.15548111636439998, -0.14635781722882538,
      -0.13735438295113805, -0.12847254506762579, -0.11971398903456865,
      -0.11108035377301384, -0.10257323122841136, -0.094194165945235608,
      -0.085944654656740574, -0.077826145889955747, -0.0698400395860599,
      -0.061987686736243733, -0.054270389033164723, -0.046689398538116572,
      -0.039245917363998642, -0.031941097374195732, -0.024776039897441884,
      -0.017751795458773298, -0.010869363526635659, -0.0041296922762316113,
      0.0024663216308308672, 0.0089178332505177732, 0.015224049543917456,
      0.02138422954830585, 0.027397684531678554, 0.0332637781307092,
      0.038981926472089527, 0.04455159827722581, 0.049972314950256287,
      0.055243650649381637, 0.060365232341470482, 0.065336739839950808,
      0.070157905825966232, 0.074828515852805422, 0.079348408333604639,
      0.083717474512337978, 0.08793565841810487, 0.092002956802748032,
      0.095919419061812936, 0.09968514713889351, 0.1033002954133958,
      0.10676507057176327, 0.11007973146221112, 0.11324458893302561,
      0.11626000565448306, 0.11912639592445606, 0.12184422545777474,
      0.12441401115941697, 0.12683632088160832, 0.12911177316491268,
      0.13124103696341277, 0.13322483135406393, 0.1350639252303299,
      0.13675913698019915, 0.1383113341487012, 0.1397214330850266,
      0.14099039857437973, 0.14211924345468235, 0.143109028218267,
      0.14396086059868235, 0.14467589514276025, 0.14525533276808389,
      0.14570042030600616, 0.14601245003037161, 0.14619275917209951,
      0.14624272941979166, 0.14616378640652974, 0.14595739918303413,
      0.14562507967735963, 0.14516838214130889, 0.14458890258374354,
      0.14388827819098746, 0.14306818673450528, 0.14213034596606333,
      0.141076513000562, 0.13990848368675088, 0.1386280919660314,
      0.1372372092195579, 0.13573774360385576, 0.13413163937516728,
      0.13242087620275891, 0.13060746847140475, 0.12869346457328132,
      0.12668094618950304, 0.12457202756153662, 0.12236885475273011,
      0.12007360490019899, 0.11768848545731378, 0.11521573342703918,
      0.11265761458636819, 0.1100164227021148, 0.10729447873830678,
      0.10449413005545129, 0.10161774960192319, 0.098667735097743167,
      0.09564650821101095, 0.0925565137272591, 0.089400218711999851,
      0.086180111666731313, 0.082898701678685557, 0.079558517564580017,
      0.07616210700866341, 0.072712035695323543, 0.069210886436547561,
      0.065661258294504143, 0.062065765699539713, 0.058427037563870778,
      0.054747716391256945, 0.051030457382936593, 0.047277927540125074,
      0.043492804763345647, 0.039677776948903114, 0.0358355410827691,
      0.031968802332185381, 0.02808027313526805, 0.024172672288905454,
      0.020248724035243026, 0.016311157147041525, 0.012362704012211345,
      0.0084060997178021651, 0.0044440811337476127, 0.00047938599665475756,
      -0.0034852480060708069, -0.0074470841514708563, -0.011403387595365647,
      -0.015351426285476415, -0.019288471873047913, -0.023211800622690605,
      -0.02711869432014314, -0.031006441177680213, -0.034872336736869188,
      -0.038713684768400342, -0.042527798168697929, -0.046311999853038466,
      -0.050063623644890476, -0.053780015161194419, -0.057458532693314607,
      -0.061096548083371525, -0.064691447595697935, -0.068240632783131056,
      -0.0717415213478798, -0.075191547996695307, -0.078588165290076256,
      -0.08192884448525059, -0.085211076372661523, -0.088432372105713544,
      -0.0915902640235028, -0.0946823064662946, -0.0977060765834828,
      -0.10065917513378725, -0.10353922727744716, -0.10634388336015527,
      -0.10907081968850188, -0.11171773929668725, -0.11428237270426592,
      -0.11676247866469666, -0.1191558449044598, -0.12146028885252921,
      -0.12367365835996583, -0.12579383240942327, -0.12781872181434284,
      -0.12974626990763088, -0.13157445321961461, -0.13330128214505912,
      -0.13492480159906148, -0.13644309166161445, -0.13785426821065105,
      -0.13915648354338106, -0.14034792698573081, -0.14142682548971505,
      -0.14239144421855471, -0.14324008711936909, -0.14397109748328207,
      -0.14458285849276778, -0.14507379375608581, -0.1454423678286399,
      -0.14568708672112057, -0.1458064983942764, -0.14579919324017318,
      -0.14566380454980965, -0.1453990089669468, -0.14500352692803314,
      -0.14447612308808816, -0.14381560673244195, -0.14302083217419975,
      -0.14209069913733505, -0.14102415312529687, -0.1398201857750333,
      -0.13847783519634133, -0.13699618629644453, -0.13537437108971614,
      -0.13361156899246651, -0.13170700710271949, -0.12965996046490824,
      -0.1274697523194146, -0.12513575433690638, -0.12265738683740265,
      -0.12003411899402142, -0.11726546902136414, -0.1143510043484927,
      -0.11129034177646518, -0.10808314762039402, -0.10472913783600812,
      -0.10122807813068962, -0.097579784058972219, -0.09378412110249057,
      -0.089841004734370566, -0.085750400468064425, -0.081512323890627514,
      -0.077126840680449088, -0.072594066609449448, -0.067914167529766659,
      -0.063087359344940835, -0.058113907965643238, -0.052994129249971149,
      -0.0477283889283496, -0.042317102513079762, -0.03676073519258842,
      -0.03105980171042183, -0.02521486622905228, -0.01922654217854174,
      -0.013095492090149579, -0.0068224274149403866, -0.00040810832747811485,
      0.0061466564853277575, 0.012841010050118673, 0.01967404734765188,
      0.026644815567936138, 0.033752314379834336, 0.040995496215038729,
      0.048373266566301532, 0.055884484299818835, 0.0635279619816415,
      0.071302466218004928, 0.0792067180094408, 0.087239393118550668,
      0.0953991224513021, 0.10368449245171968, 0.11209404550981826,
      0.12062628038264368, 0.12927965262826296, 0.13805257505256341,
      0.1469434181686898, 0.15595051066897342, 0.16507213990917541,
      0.17430655240489029, 0.18365195433992959, 0.19310651208651577,
      0.20266835273710115, 0.212335564647645, 0.22210619799214992,
      0.23197826532827587, 0.24194974217384224, 0.25201856759401653,
      0.26218264479900905, 0.27243984175205244, 0.28278799178748004,
      0.29322489423868275, 0.30374831507575856, 0.31435598755261684,
      0.32504561286334033, 0.33581486080758582, 0.34666137046480511,
      0.35758275087706171, 0.36857658174022356, 0.37964041410330418,
      0.39077177107573313, 0.4019681485423095, 0.41322701588562283,
      0.42454581671569985, 0.435921969606648, 0.44735286884004866,
      0.45883588515487267, 0.47036836650367092, 0.48194763881480396,
      0.49357100676046234, 0.50523575453023373, 0.51693914660997875,
      0.52867842856575753, 0.54045082783257226, 0.55225355450766067,
      0.564083802148114, 0.57593874857253657, 0.58781555666653618,
      0.59971137519175577, 0.61162333959822057, 0.6235485728397272,
      0.635484186192045, 0.64742728007365935, 0.65937494486879933,
      0.67132426175251136, 0.68327230351751966, 0.69521613540261429,
      0.707152815922313, 0.71907939769754836, 0.73099292828713514,
      0.74289045101973561, 0.75476900582611139, 0.76662563007136331,
      0.77845735938696026, 0.790261228502256, 0.80203427207527811,
      0.8137735255225278, 0.8254760258475331, 0.83713881246793775,
      0.8487589280408393, 0.860333419286164, 0.8718593378078211,
      0.88333374091239314, 0.8947536924251267, 0.9061162635029798,
      0.91741853344448643, 0.92865759049621177, 0.93983053265554828,
      0.9509344684696317, 0.96196651783013687, 0.97292381276373463,
      0.98380349821796953, 0.99460273284234524, 1.0053186897643782,
      1.0159485573604241, 1.0264895400210299, 1.0369388589106117,
      1.0472937527212411, 1.057551478420325, 1.0677093119919745,
      1.0777645491718484, 1.087714506175276, 1.0975565204184479,
      1.1072879512324909, 1.1169061805702105, 1.1264086137053213,
      1.1357926799239784, 1.1450558332084042, 1.1541955529124506,
      1.1632093444288929, 1.172094739848287, 1.1808492986092212,
      1.189470608139777, 1.1979562844900367, 1.2063039729554734,
      1.2145113486910648, 1.2225761173159568, 1.2304960155085398,
      1.2382688115917717, 1.2458923061086136, 1.2533643323874142,
      1.2606827570971182, 1.267845480792152, 1.274850438446856,
      1.2816955999793307, 1.2883789707645739, 1.2948985921367757,
      1.301252541880664, 1.3074389347117825, 1.31345592274558,
      1.3193016959552131, 1.3249744826179506, 1.330472549750092,
      1.3357942035302841, 1.3409377897111607, 1.3459016940192055,
      1.3506843425427628, 1.3552842021081042, 1.3596997806434858,
      1.3639296275311124, 1.3679723339469538, 1.3718265331883281,
      1.3754909009892131, 1.3789641558232109, 1.3822450591941293,
      1.3853324159141125, 1.3882250743692908, 1.3909219267729052,
      1.3934219094058697, 1.3957240028447322, 1.3978272321770109,
      1.3997306672038909, 1.4014334226302363, 1.4029346582419249,
      1.4042335790704792, 1.4053294355449872, 1.4062215236313143,
      1.4069091849585915, 1.4073918069330007, 1.4076688228388512,
      1.4077397119269597, 1.4076039994903529, 1.4072612569273071,
      1.4067111017917555, 1.40595319783107, 1.4049872550112723,
      1.4038130295296878, 1.4024303238150944, 1.4008389865153936,
      1.3990389124728593, 1.3970300426870126, 1.3948123642651633,
      1.3923859103606879, 1.3897507600990979, 1.3869070384919562,
      1.3838549163387142, 1.3805946101165403, 1.3771263818582036,
      1.3734505390181058, 1.3695674343265192, 1.365477465632136,
      1.3611810757330014, 1.3566787521959187, 1.3519710271644421,
      1.3470584771555134, 1.3419417228448767, 1.3366214288413654,
      1.331098303450152, 1.325373098425076, 1.3194466087101817,
      1.3133196721705387, 1.3069931693125041, 1.3004680229935159,
      1.2937451981215482, 1.2868257013443665, 1.2797105807286926,
      1.2724009254294046, 1.2648978653489402, 1.2572025707869863,
      1.2493162520806407, 1.241240159235153, 1.2329755815453931,
      1.2245238472082129, 1.2158863229258112, 1.2070644135002822,
      1.1980595614194776, 1.1888732464343468, 1.179506985127901,
      1.1699623304759654, 1.1602408713998682, 1.1503442323112374,
      1.140274072649053, 1.1300320864091336, 1.1196200016662021,
      1.1090395800887252, 1.0982926164466542, 1.0873809381122828,
      1.0763064045543544, 1.0650709068256006, 1.0536763670439016,
      1.0421247378672196, 1.0304180019624836, 1.0185581714686174,
      1.0065472874538635, 0.99438741936761244, 0.98208066448687892,
      0.96962914735762917, 0.95703501923113954, 0.94430045749554548,
      0.93142766510280228, 0.91841886999117939, 0.9052763245035319,
      0.89200230480149656, 0.87859911027580428, 0.86506906295288466,
      0.8514145068979655, 0.83763780761482409, 0.82374135144240213,
      0.80972754494843568, 0.7955988143203131, 0.78135760475333538,
      0.76700637983654829, 0.75254762093634231, 0.73798382657801254,
      0.7233175118254308, 0.70855120765905133, 0.69368746035238582,
      0.678728830847172, 0.66367789412739542, 0.6485372385923398,
      0.6333094654288538, 0.61799718798301428, 0.60260303113134994,
      0.58712963065183288, 0.57157963259476152, 0.55595569265376632,
      0.54026047553707524, 0.52449665433922865, 0.5086669099134018,
      0.49277393024452359, 0.47682040982334445, 0.46080904902161768,
      0.44474255346860603, 0.4286236334289929, 0.41245500318245137,
      0.39623938040498285, 0.37997948555219418, 0.36367804124468522,
      0.34733777165568847, 0.33096140190112711, 0.31455165743225616,
      0.29811126343100236, 0.28164294420819891, 0.26514942260484126,
      0.24863341939651012, 0.23209765270110941, 0.21554483739007693,
      0.19897768450317965, 0.18239890066707815, 0.16581118751773738,
      0.14921724112688151, 0.1326197514325887, 0.11602140167416493,
      0.099424867831431771, 0.08283281806855286, 0.06624791218252285,
      0.049672801056437871, 0.033110126117689681, 0.016562518801156098,
      3.2600017560169281E-5, -0.016477020372927996, -0.032963744081725629,
      -0.049424984907387129, -0.065858169245579468, -0.082260736593371769,
      -0.09863014004772315, -0.1149638467981082, -0.13125933861313313,
      -0.14751411232108619, -0.16372568028431761, -0.179891570867351,
      -0.19600932889865563, -0.21207651612598755, -0.22809071166520187,
      -0.24404951244250181, -0.25995053362998893, -0.2757914090744838,
      -0.291569791719531, -0.30728335402051549, -0.32292978835283292,
      -0.33850680741304051, -0.35401214461293645, -0.36944355446649374,
      -0.38479881296962687, -0.40007571797268537, -0.41527208954567257,
      -0.4303857703361097, -0.44541462591951647, -0.46035654514245794,
      -0.47520944045811814, -0.48997124825435284, -0.504639929174219,
      -0.51921346842889926, -0.53368987610303265, -0.54806718745240024,
      -0.56234346319394923, -0.57651678978813348, -0.59058527971354924,
      -0.60454707173383015, -0.61840033115683635, -0.632143250086063,
      -0.64577404766429269, -0.6592909703094848, -0.67269229194288471,
      -0.68597631420935257, -0.69914136668991522, -0.71218580710654067,
      -0.725108021519127, -0.73790642451474808, -0.75057945938911308,
      -0.76312559832029836, -0.77554334253472557, -0.78783122246543713,
      -0.79998779790265884, -0.81201165813668463, -0.82390142209308992,
      -0.83565573846033148, -0.84727328580971317, -0.85875277270777706,
      -0.87009293782115149, -0.88129255001386264, -0.89235040843717406,
      -0.903265342611975, -0.91403621250374312, -0.92466190859016439,
      -0.93514135192139558, -0.94547349417305737, -0.95565731769198181,
      -0.96569183553476978, -0.975576091499206, -0.9853091601485755,
      -0.99489014682895194, -1.00431818767948, -1.0135924496357551,
      -1.022712130426308, -1.0316764585622831, -1.0404846933203646,
      -1.0491361247190092, -1.0576300734880488, -1.0659658910317407,
      -1.0741429593852896, -1.0821606911649853, -1.0900185295119358,
      -1.0977159480295331, -1.10525245071469, -1.1126275718829262,
      -1.119840876087387, -1.126891958031853, -1.1337804424778273,
      -1.1405059841457761, -1.147068267610599, -1.1534670071913991,
      -1.1597019468356495, -1.1657728599978194, -1.1716795495125565,
      -1.1774218474624869, -1.1829996150407438, -1.1884127424082769,
      -1.1936611485460542, -1.1987447811022216, -1.2036636162343144,
      -1.2084176584466071, -1.2130069404226824, -1.2174315228533119,
      -1.2216914942597339, -1.2257869708124129, -1.229718096145378,
      -1.2334850411662119, -1.2370880038618053, -1.2405272090999333,
      -1.243802908426775, -1.2469153798604429, -1.2498649276806217,
      -1.2526518822144042, -1.2552765996184194, -1.257739461657331,
      -1.2600408754788068, -1.2621812733850486, -1.2641611126009598,
      -1.2659808750390646, -1.2676410670612408, -1.2691422192373767,
      -1.2704848861010347, -1.2716696459022012, -1.2726971003572356,
      -1.2735678743960799, -1.2742826159068341, -1.2748419954777852,
      -1.2752467061369654, -1.2754974630893421, -1.2755950034517192,
      -1.275540085985434, -1.2753334908269343, -1.2749760192163393,
      -1.2744684932240407, -1.2738117554754516, -1.2730066688739761,
      -1.2720541163222834, -1.2709550004419772, -1.269710243291734,
      -1.268320786083986, -1.266787588900252, -1.2651116304051673,
      -1.2632939075593179, -1.2613354353309387, -1.2592372464065584,
      -1.2570003909006784, -1.2546259360645435, -1.2521149659940964,
      -1.2494685813371791, -1.2466878990000609, -1.2437740518533578,
      -1.2407281884374326, -1.2375514726673207, -1.2342450835372736,
      -1.2308102148249782, -1.2272480747955179, -1.2235598859051535,
      -1.2197468845049786, -1.2158103205445172, -1.2117514572753343,
      -1.207571570954705, -1.2032719505494325, -1.1988538974398448,
      -1.1943187251240479, -1.1896677589224935, -1.18490233568291,
      -1.1800238034856636, -1.1750335213495964, -1.1699328589384,
      -1.164723196267577, -1.1594059234120448, -1.1539824402144292,
      -1.1484541559940966, -1.1428224892569789, -1.1370888674062343,
      -1.1312547264537938, -1.1253215107328383, -1.119290672611243,
      -1.1131636722060481, -1.10694197709898, -1.1006270620530794,
      -1.0942204087304643, -1.087723505411277, -1.0811378467138439,
      -1.0744649333160863, -1.0677062716782262, -1.0608633737668092,
      -1.0539377567800936, -1.0469309428748053, -1.0398444588943412,
      -1.0326798360984022, -1.0254386098941135, -1.0181223195686486,
      -1.0107325080233855, -1.0032707215096301, -0.99573850936591191,
      -0.98813742375690317, -0.98046901941395215, -0.972734853377283,
      -0.96493648473986282, -0.9570754743929667, -0.94915338477345046,
      -0.94117177961275877, -0.933132223687675, -0.92503628257284976,
      -0.91688552239508558, -0.90868150958943628, -0.900425810657101,
      -0.89211999192514546, -0.88376561930805042, -0.87536425807110041,
      -0.86691747259563223, -0.85842682614614174, -0.84989388063925586,
      -0.841320196414592, -0.832707332007493, -0.82405684392366607,
      -0.81537028641570408, -0.80664921126152089, -0.797895167544685,
      -0.78910970143666392, -0.78029435598099017, -0.77145067087932317,
      -0.76258018227944446, -0.75368442256516355, -0.74476492014814177,
      -0.73582319926163009, -0.72686077975613306, -0.71787917689697678,
      -0.7088799011638055, -0.69986445805197173, -0.69083434787585041,
      -0.68179106557405467, -0.67273610051655541, -0.66367093631369134,
      -0.6545970506270915, -0.64551591498246874, -0.636428994584315,
      -0.62733774813245935, -0.6182436276405131, -0.60914807825618111,
      -0.60005253808343118, -0.590958438006522, -0.58186720151588023,
      -0.5727802445358201, -0.56369897525409374, -0.55462479395328479,
      -0.54555909284399773, -0.536503255899882, -0.52745865869445618,
      -0.518426668239723, -0.5094086428265856, -0.50040593186703874,
      -0.49141987573812984, -0.48245180562771095, -0.47350304338191412,
      -0.46457490135440271, -0.45566868225736151, -0.44678567901421307,
      -0.4379271746140736, -0.42909444196791752, -0.420288743766459,
      -0.411511332339747, -0.40276344951843607, -0.39404632649676558,
      -0.38536118369721811, -0.3767092306368493, -0.36809166579528785,
      -0.35950967648440352, -0.35096443871962474, -0.3424571170929106,
      -0.33398886464736688, -0.32556082275349746, -0.31717412098709469,
      -0.30882987700875369, -0.30052919644500969, -0.29227317277109977,
      -0.28406288719533296, -0.27589940854507239, -0.26778379315433504,
      -0.25971708475297206, -0.25170031435747686, -0.24373450016337389,
      -0.23582064743921102, -0.2279597484221455, -0.22015278221512188,
      -0.21240071468564081, -0.20470449836612659, -0.19706507235587267,
      -0.18948336222459197, -0.18196027991755143, -0.17449672366229807,
      -0.1670935778769867, -0.15975171308029523, -0.15247198580294008,
      -0.14525523850080202, -0.13810229946963645, -0.13101398276140888,
      -0.12399108810223311, -0.11703440081192495, -0.11014469172518129,
      -0.10332271711437759, -0.0965692186140023, -0.089884923146726331,
      -0.083270542851117138, -0.076726775010999865, -0.070254301986484788,
      -0.063853791146652072, -0.057525894803917142, -0.05127125015007522,
      -0.045090479194038177, -0.03898418870127416, -0.032952970134966245,
      -0.026997399598869598, -0.021118037781928917, -0.015315429904622646,
      -0.0095901056670672016, -0.0039425791988872624, 0.0016266509891358083,
      0.0071171020516204025, 0.012528306853337008, 0.017859814012148659,
      0.0231111879401137, 0.028282008882740323, 0.033371872956390866,
      0.038380392183800863, 0.043307194527713727, 0.048151923922616406,
      0.052914240304541227, 0.05759381963894427, 0.062190353946624394,
      0.066703551327678315, 0.071133135983471291, 0.075478848236600643,
      0.0797404445488474, 0.083917697537089483, 0.088010395987164536,
      0.092018344865658755, 0.095941365329613421, 0.0997792947341209,
      0.10353198663780104, 0.10719931080613612, 0.11078115321264284,
      0.11427741603787403, 0.11768801766621834, 0.12101289268048651,
      0.12425199185427577, 0.12740528214206825, 0.13047274666707553,
      0.13345438470678742, 0.13635021167621744, 0.13916025910883315,
      0.14188457463513443, 0.14452322195887934, 0.14707628083093682,
      0.14954384702073037, 0.15192603228529267, 0.15422296433586991,
      0.15643478680209147, 0.15856165919367238, 0.16060375685963707,
      0.16256127094504313, 0.1644344083451994, 0.1662233916573454,
      0.16792845912979093, 0.16954986460850086, 0.17108787748109283,
      0.1725427826182567, 0.17391488031256175, 0.17520448621464776,
      0.17641193126678961, 0.17753756163380807, 0.17858173863132903,
      0.179544838651372, 0.18042725308525462, 0.18122938824380919,
      0.18195166527488896, 0.18259452007816668, 0.18315840321720472,
      0.18364377982879798, 0.18405112952956965, 0.18438094631982405,
      0.18463373848463838, 0.18481002849219269, 0.18491035288933352,
      0.18493526219436004, 0.18488532078703296, 0.18476110679579971,
      0.18456321198223263, 0.18429224162268298, 0.18394881438713789,
      0.18353356221529138, 0.18304713018982049, 0.18249017640687204,
      0.18186337184376028, 0.18116740022387551, 0.18040295787880842,
      0.1795707536076952, 0.17867150853378688, 0.17770595595824715,
      0.17667484121118648, 0.17557892149994381, 0.17441896575461419,
      0.17319575447084257, 0.17191007954988846, 0.17056274413597128,
      0.16915456245091054, 0.16768635962607636, 0.16615897153165865,
      0.16457324460327449, 0.16293003566592781, 0.16123021175533842,
      0.15947464993665666, 0.15766423712059141, 0.15579986987695366,
      0.1538824542456558, 0.15191290554517789, 0.14989214817852536,
      0.14782111543670515, 0.14570074929973928, 0.1435320002352532,
      0.14131582699465214, 0.13905319640692571, 0.13674508317010212,
      0.13439246964038459, 0.1319963456190075, 0.12955770813683287,
      0.1270775612367312, 0.12455691575377538, 0.12199678909328626,
      0.11939820500676601, 0.11676219336575376, 0.11408978993364857,
      0.11138203613553246, 0.10863997882604182, 0.1058646700553216,
      0.10305716683311159, 0.10021853089100449, 0.097349828442921463,
      0.09445212994385474, 0.091526509846919513, 0.088574046358763564,
      0.085595821193390445, 0.082592919324434119, 0.079566428735947756,
      0.076517440171752868, 0.073447046883398537, 0.070356344376796276,
      0.0672464301575677, 0.064118403475177943, 0.060973365065900217,
      0.057812416894674881, 0.054636661895914262, 0.051447203713325132,
      0.048245146438792713, 0.045031594350401771, 0.041807651649646588,
      0.038574422197894871, 0.035333009252176015, 0.03208451520034597,
      0.028830041295698376, 0.025570687391096046, 0.022307551672672697,
      0.0190417303931893, 0.015774317605096094, 0.012506404893381146,
      0.0092390811082720889, 0.0059734320978550096, 0.0027105404406848055,
      -0.00054851482153979447, -0.0038026584511710593, -0.0070508192816028728,
      -0.010291930483976378, -0.01352492983354639, -0.016748759975614216,
      -0.019962368690968554, -0.023164709160754915, -0.02635474023069307,
      -0.029531426674576956, -0.032693739456984068, -0.035840655995096393,
      -0.038971160419590409, -0.042084243834493149, -0.045178904575936818,
      -0.048254148469743331, -0.051308989087744269, -0.0543424480027779,
      -0.057353555042275184, -0.060341348540356804, -0.063304875588371751,
      -0.066243192283796964, -0.069155363977409914, -0.0720404655186789,
      -0.074897581499270324, -0.077725806494613275, -0.08052424530343788,
      -0.083292013185203045, -0.086028236095347363, -0.088732050918292962,
      -0.091402605698097536, -0.094039059866710129, -0.0966405844697382,
      -0.099206362389650748, -0.1017355885663512, -0.10422747021503062,
      -0.10668122704124183, -0.10909609145311444, -0.1114713087706304,
      -0.11380613743189832, -0.11609984919635088, -0.11835172934478252,
      -0.12056107687617137, -0.12272720470121318, -0.12484943983247608,
      -0.12692712357114241, -0.12895961169022818, -0.13094627461425043,
      -0.13288649759525198, -0.13477968088511447, -0.13662523990411377,
      -0.13842260540563706, -0.14017122363699808, -0.1418705564963007,
      -0.14352008168526786, -0.14511929285799427, -0.14666769976555508,
      -0.14816482839640377, -0.14961022111251654, -0.1510034367812168,
      -0.15234405090261854, -0.15363165573264512, -0.15486586040157316,
      -0.15604629102802328, -0.15717259082838417, -0.1582444202215833,
      -0.15926145692918142, -0.16022339607074032, -0.16112995025439636,
      -0.16198084966262266, -0.16277584213312357, -0.16351469323481374,
      -0.16419718633885791, -0.16482312268471105, -0.16539232144113958,
      -0.16590461976218079, -0.16635987283800002, -0.16675795394061696,
      -0.16709875446448147, -0.16738218396183896, -0.16760817017288562,
      -0.16777665905068, -0.16788761478076658, -0.16794101979551879,
      -0.16793687478314726, -0.16787519869137871, -0.16775602872577833,
      -0.16757942034268375, -0.16734544723675973, -0.16705420132314591,
      -0.16670579271418315, -0.16630034969071728, -0.16583801866797104,
      -0.16531896415596214, -0.1647433687144893, -0.16411143290265784,
      -0.16342337522295769, -0.16267943205989574, -0.16187985761316875,
      -0.1610249238254004, -0.16011492030444369, -0.15915015424023926,
      -0.15813095031626961, -0.15705765061559102, -0.15593061452147644,
      -0.15475021861267968, -0.15351685655332853, -0.1522309389774808,
      -0.1508928933683556, -0.14950316393225829, -0.14806221146723658,
      -0.14657051322648137, -0.14502856277650805, -0.14343686985014747,
      -0.1417959601943731, -0.14010637541300514, -0.13836867280432855,
      -0.13658342519364969, -0.13475122076084445, -0.13287266286294092,
      -0.13094836985175665, -0.12897897488666937, -0.12696512574253738,
      -0.12490748461283741, -0.1228067279080621, -0.12066354604942804,
      -0.1184786432579531, -0.11625273733895733, -0.1139865594620347,
      -0.11168085393657615, -0.10933637798288282, -0.10695390149893963,
      -0.10453420682292094, -0.10207808849148059, -0.099586352993902144,
      -0.09705981852218025, -0.094499314717094732, -0.091905682410353365,
      -0.0892797733628858, -0.086622449999345874, -0.083934585138919646,
      -0.081217061722498568, -0.078470772536310879, -0.075696619932085124,
      -0.07289551554383833, -0.070068380001345, -0.067216142640421167,
      -0.0643397412100598, -0.061440121576535049, -0.058518237424559437,
      -0.055575049955576508, -0.052611527583292891, -0.049628645626530396,
      -0.046627385999505278, -0.043608736899616814, -0.040573692492851386,
      -0.037523252596897712, -0.034458422362069467, -0.031380211950134844,
      -0.028289636211156981, -0.025187714358445877, -0.022075469641722356,
      -0.018953929018597639, -0.015824122824475831, -0.012687084440984847,
      -0.0095438499630303014, -0.0063954578646043259, -0.0032429486634253969,
      -8.7364584540172707E-5, 0.0030702507770101889, 0.0062288527943589987,
      0.0093873961476913549, 0.012544835163733663, 0.015700124155738494,
      0.018852217763853485, 0.022000071295764489, 0.025142641067498053,
      0.0282788847442743, 0.031407761681291925, 0.0345282332643396,
      0.0376392632501158, 0.040739818106141627, 0.043828867350159145,
      0.046905383888894918, 0.049968344356087019, 0.05301672944963827,
      0.056049524267808522, 0.059065718644321467, 0.062064307482262882,
      0.065044291086674824, 0.068004675495718148, 0.070944472810298,
      0.073862701522037638, 0.0767583868394901, 0.079630561012463963,
      0.0824782636543801, 0.085300542062513418, 0.088096451536031378,
      0.090865055691712188, 0.0936054267772374, 0.096316645981942811,
      0.098997803744924021, 0.10164800006039015, 0.10426634478015612,
      0.10685195791316696, 0.10940396992195367, 0.11192152201591044,
      0.1144037664412923, 0.11684986676782966, 0.11925899817186486,
      0.12163034771589573, 0.12396311462444183, 0.12625651055612264,
      0.12850975987186358, 0.13072209989911909, 0.1328927811920298,
      0.13502106778740869, 0.13710623745647801, 0.13914758195225493,
      0.14114440725249877, 0.14309603379812857, 0.14500179672703672,
      0.14686104610319325, 0.14867314714097657, 0.15043748042462979,
      0.1521534421227802, 0.15382044419792723, 0.15543791461082285,
      0.15700529751968767, 0.15852205347415541, 0.15998765960390249,
      0.16140160980187368, 0.1627634149020506, 0.16407260285166847,
      0.1653287188778538, 0.16653132564858258, 0.1676800034279215,
      0.16877435022548462, 0.169813981940042, 0.17079853249722987,
      0.17172765398131598, 0.17260101676094536, 0.17341830960884527,
      0.17417923981542219, 0.17488353329620127, 0.17553093469308539,
      0.17612120746937687, 0.17665413399851837, 0.177129515646534,
      0.17754717284811111, 0.17790694517631431, 0.17820869140587936,
      0.17845228957007719, 0.17863763701110891, 0.1787646504240068,
      0.17883326589402915, 0.17884343892752658, 0.17879514447625344,
      0.1786883769551211, 0.17852315025337434, 0.17829949773917794,
      0.17801747225761358, 0.1776771461220748, 0.17727861109905418,
      0.17682197838633623, 0.17630737858457018, 0.17573496166226021,
      0.17510489691414832, 0.1744173729130174, 0.17367259745491709,
      0.17287079749783096, 0.17201221909378606, 0.17109712731444462,
      0.17012580617017975, 0.1690985585226627, 0.16801570599099594,
      0.16687758885139409, 0.16568456593047615, 0.16443701449216769,
      0.16313533011827283, 0.1617799265827346, 0.16037123571963144,
      0.15890970728494241, 0.15739580881213838, 0.15583002546162966,
      0.15421285986411787, 0.15254483195792529, 0.15082647882030825,
      0.14905835449286228, 0.14724102980102871, 0.14537509216779618,
      0.14346114542162774, 0.14149980959870498, 0.13949172073952826,
      0.13743753067996034, 0.13533790683676361, 0.13319353198771883,
      0.13100510404639462, 0.12877333583162628, 0.12649895483179946,
      0.12418270296401336, 0.12182533632820422, 0.11942762495630402,
      0.11699035255651714, 0.11451431625283043, 0.11200032631979634,
      0.1094492059127275, 0.10686179079335065, 0.10423892905105951,
      0.10158148081980478, 0.098890317990779547, 0.096166323920943014,
      0.093410393137526887, 0.0906234310385906, 0.087806353589745229,
      0.084960087017159708, 0.082085567496930245, 0.079183740840930772,
      0.07625556217926413, 0.07330199563942448, 0.07032401402222993,
      0.067322598474722467, 0.064298738160090518, 0.061253429924726474,
      0.058187677962581161, 0.055102493476868242, 0.05199889433929962,
      0.048877904746914023, 0.045740554876671176, 0.042587880537873407,
      0.039420922822606022, 0.036240727754238339, 0.033048345934180524,
      0.029844832186984048, 0.026631245203903274, 0.023408647185061089,
      0.020178103480346279, 0.016940682229140275, 0.013697453999045275,
      0.010449491423684339, 0.0071978688397679718, 0.0039436619234719684,
      0.00068794732634929042, -0.0025681976891890638, -0.0058236956146144282,
      -0.0090774690601835711, -0.012328441119809451, -0.015575535735844678,
      -0.018817678063565567, -0.022053794835311193, -0.025282814724074416,
      -0.028503668706481217, -0.031715290424975735, -0.034916616549130988,
      -0.03810658713590305, -0.041284145988761435, -0.044448241015528328,
      -0.047597824584800733, -0.050731853880851108, -0.05384929125686317,
      -0.056949104586391748, -0.060030267612905017, -0.063091760297282445,
      -0.066132569163193766, -0.069151687640151477, -0.072148116404209622,
      -0.075120863716096054, -0.078068945756749344, -0.080991386960045181,
      -0.0838872203426993, -0.086755487831123024, -0.089595240585208263,
      -0.092405539318856339, -0.095185454617176687, -0.0979340672502523,
      -0.1006504684832982, -0.10333376038319153, -0.10598305612117814,
      -0.10859748027171978, -0.11117616910732625, -0.11371827088928704,
      -0.11622294615421322, -0.11868936799624732, -0.12111672234489843,
      -0.12350420823833548, -0.12585103809212145, -0.12815643796320703,
      -0.13041964780917176, -0.13263992174255074, -0.13481652828021573,
      -0.13694875058767808, -0.13903588671825268, -0.14107724984699105,
      -0.14307216849929189, -0.1450199867741363, -0.14692006456181619,
      -0.14877177775615913, -0.15057451846108005, -0.15232769519147693,
      -0.15403073306833392, -0.15568307400798581, -0.15728417690551011,
      -0.15883351781211164, -0.16033059010651815, -0.1617749046602531,
      -0.16316598999678944, -0.16450339244448531, -0.16578667628328117,
      -0.16701542388507498, -0.16818923584775763, -0.16930773112285169,
      -0.17037054713668404, -0.17137733990511725, -0.17232778414171135,
      -0.17322157335936486, -0.17405841996533375, -0.17483805534965216,
      -0.17556022996686271, -0.17622471341111806, -0.17683129448452573,
      -0.17737978125879073, -0.17787000113011908, -0.17830180086733222,
      -0.17867504665323214, -0.17898962411916242, -0.17924543837276063,
      -0.17944241401893263, -0.17958049517398789, -0.17965964547297777,
      -0.17967984807022225, -0.17964110563302998, -0.17954344032859626,
      -0.17938689380414335, -0.17917152716023288, -0.17889742091735525,
      -0.178564674975715, -0.17817340856832936, -0.17772376020736044,
      -0.17721588762379969, -0.17664996770045743, -0.17602619639831921,
      -0.17534478867630104, -0.17460597840441866, -0.17381001827042736,
      -0.17295717967994234, -0.17204775265012057, -0.17108204569690197,
      -0.17006038571588133, -0.168983117856871, -0.1678506053921357,
      -0.16666322957847804, -0.16542138951306848, -0.16412550198323045,
      -0.16277600131011577, -0.16137333918642444, -0.1599179845081527,
      -0.15841042320051602, -0.15685115803803337, -0.15524070845890703,
      -0.15357961037372839, -0.15186841596860295, -0.15010769350277206,
      -0.14829802710079271, -0.14644001653937261, -0.1445342770289286,
      -0.14258143898996875, -0.14058214782435235, -0.13853706368156449,
      -0.13644686122005087, -0.13431222936370071, -0.13213387105363394,
      -0.1299125029952844, -0.12764885540099116, -0.12534367172809016,
      -0.12299770841267413, -0.12061173459909619, -0.11818653186532561,
      -0.11572289394424434, -0.11322162644102367, -0.11068354654664705,
      -0.10810948274771619, -0.10550027453263888, -0.10285677209430159,
      -0.10017983602936818, -0.0974703370342762, -0.0947291555980739,
      -0.091957181692212342, -0.08915531445738123, -0.086324461887562154,
      -0.083465540511338587, -0.080579475070666248, -0.077667198197153828,
      -0.074729650086018312, -0.071767778167817653, -0.068782536778095343,
      -0.065774886825046425, -0.062745795455334208, -0.05969623571819245,
      -0.056627186227914204, -0.053539630824883395, -0.050434558235251,
      -0.047312961729383679, -0.044175838779233721, -0.041024190714724379,
      -0.037859022379302727, -0.034681341784787226, -0.031492159765609866,
      -0.028292489632615068, -0.025083346826530791, -0.021865748571215954,
      -0.018640713526858071, -0.015409261443206652, -0.012172412812988368,
      -0.0089311885256356111, -0.0056866095214361534, -0.0024396964462528106,
      0.00080853069307074144, 0.0040570528725031724, 0.0073048523936655521,
      0.01055091322562815, 0.013794221345503108, 0.017033765077740418,
      0.020268535431978416, 0.023497526439351074, 0.026719735487115336,
      0.029934163651466762, 0.033139816028466641, 0.036335702062890787,
      0.0395208358749636, 0.042694236584792794, 0.045854928634421206,
      0.049001942107389507, 0.052134313045652726, 0.055251083763785111,
      0.058351303160340789, 0.061434027026255292, 0.0644983183501835,
      0.067543247620676289, 0.070567893125059636, 0.0735713412449617,
      0.076552686748319929, 0.079511033077824034, 0.0824454926356655,
      0.08535518706448221, 0.088239247524440761, 0.091096814966316525,
      0.093927040400511488, 0.096729085161898376, 0.099502121170394309,
      0.10224533118721189, 0.10495790906664053, 0.10763906000333628,
      0.11028800077498743, 0.11290395998030497, 0.1154861782722357,
      0.11803390858634216, 0.12054641636425321, 0.12302297977213517,
      0.12546288991407584, 0.127865451040361, 0.13022998075051939,
      0.13255581019112744, 0.13484228424826739, 0.13708876173459464,
      0.139294615570965, 0.14145923296254229, 0.14358201556934738,
      0.1456623796712114, 0.1476997563270312, 0.14969359152835587,
      0.15164334634717655, 0.15354849707795121, 0.15540853537377292,
      0.15722296837666, 0.15899131884194445, 0.16071312525671061,
      0.16238794195223896, 0.16401533921048161, 0.16559490336446073,
      0.16712623689265205, 0.16860895850726693, 0.17004270323644488,
      0.17142712250033831, 0.1727618841810683, 0.17404667268653695,
      0.17528118900811321, 0.17646515077213437, 0.177598292285286,
      0.17868036457379033, 0.17971113541646083, 0.18069038937159415,
      0.18161792779770239, 0.18249356886813017, 0.18331714757950951,
      0.18408851575412422, 0.18480754203616542, 0.18547411188188223,
      0.186088127543713, 0.18664950804832409, 0.18715818916867505,
      0.18761412339007272, 0.18801727987027128, 0.18836764439364362,
      0.18866521931947638, 0.18891002352437825, 0.18910209233890696,
      0.18924147747839384, 0.18932824696805389, 0.18936248506239875,
      0.18934429215901916, 0.18927378470678327, 0.18915109510848233,
      0.18897637161802405, 0.18874977823216621, 0.18847149457692053,
      0.18814171578863587, 0.18776065238982631, 0.18732853015985143,
      0.18684559000046352, 0.1863120877963243, 0.18572829427055221,
      0.18509449483536289, 0.18441098943789627, 0.18367809240129165,
      0.18289613226109669, 0.18206545159708432, 0.18118640686056517,
      0.1802593681972722, 0.17928471926591535, 0.17826285705246331,
      0.1771941916802971, 0.17607914621623949, 0.1749181564726468,
      0.17371167080559019, 0.17246014990922356, 0.17116406660648831,
      0.16982390563617683, 0.16844016343651003, 0.16701334792530445,
      0.16554397827682504, 0.16403258469543952, 0.16247970818617227,
      0.16088590032225203, 0.15925172300977639, 0.15757774824957996,
      0.15586455789641984, 0.15411274341560832, 0.15232290563715273,
      0.15049565450757016, 0.14863160883942092, 0.14673139605875796,
      0.14479565195049554, 0.14282502040192963, 0.14082015314441199,
      0.13878170949336255, 0.13671035608671422, 0.13460676662188814,
      0.13247162159144354, 0.130305608017491, 0.12810941918499671,
      0.12588375437408916, 0.12362931859149465, 0.12134682230118868,
      0.11903698115442446, 0.11670051571920693, 0.1143381512093582,
      0.11195061721328672, 0.10953864742254439, 0.10710297936036214,
      0.10464435411017123, 0.10216351604433715, 0.099661212553122561,
      0.097138193774071221, 0.094595212321880326, 0.092033023018885746,
      0.089452382626280885, 0.086854049576173181, 0.084238783704597309,
      0.081607345985575619, 0.078960498266379242, 0.076299003004047877,
      0.073623623003308422, 0.070935121156000036, 0.068234260182089168,
      0.065521802372424984, 0.0627985093332762, 0.06006514173282626,
      0.057322459049657375, 0.054571219323401372, 0.051812178907565835,
      0.049046092224749739, 0.046273711524228441, 0.043495786642090736,
      0.040713064763990212, 0.037926290190591766, 0.035136204105853122,
      0.032343544348171868, 0.029549045184540448, 0.02675343708776301,
      0.02395744651684012, 0.02116179570059544, 0.018367202424638962,
      0.015574379821744477, 0.01278403616570252, 0.00999687466876846,
      0.0072135932827362276, 0.0044348845037539275, 0.0016614351809199623,
      -0.0011060736712391467, -0.0038669670563724196, -0.0066205761758867665,
      -0.00936623860447476, -0.012103298461495202, -0.014831106578171341,
      -0.017549020660533876, -0.020256405448042095, -0.02295263286786027,
      -0.025637082184693363, -0.028309140146159525, -0.0309682011236564,
      -0.033613667248635369, -0.036244948544303435, -0.038861463052625236,
      -0.041462636956672794, -0.044047904698232221, -0.046616709090633951,
      -0.049168501426796615, -0.05170274158244588, -0.054218898114452019,
      -0.056716448354309217, -0.059194878496686615, -0.061653683683061587,
      -0.064092368080403611, -0.066510444954874237, -0.068907436740570163,
      -0.0712828751032564, -0.073636300999100845, -0.075967264728406661,
      -0.078275325984314623, -0.080560053896500117, -0.082821027069839778,
      -0.085057833618072481, -0.087270071192448881, -0.08945734700536434,
      -0.091619277849009736, -0.093755490109024051, -0.095865619773192259,
      -0.097949312435181346, -0.10000622329333284, -0.10203601714456996,
      -0.10403836837337108, -0.10601296093591614, -0.10795948833938057,
      -0.10987765361641753, -0.1117671692948789, -0.11362775736278688,
      -0.1154591492286042, -0.11726108567685123, -0.11903331681908819,
      -0.12077560204032507, -0.12248770994091569, -0.12416941827393159,
      -0.12582051387814605, -0.12744079260660079, -0.12903005925086913,
      -0.13058812746104667, -0.13211481966151353, -0.13360996696256813,
      -0.13507340906795939, -0.13650499417839279, -0.13790457889110255,
      -0.13927202809549502, -0.14060721486501221, -0.14191002034522204,
      -0.14318033363825169, -0.14441805168361718, -0.14562307913553324,
      -0.14679532823678332, -0.14793471868922875, -0.14904117752104051,
      -0.150114638950743, -0.1511550442481413, -0.15216234159222686,
      -0.15313648592616558, -0.15407743880941926, -0.15498516826714237,
      -0.15585964863689417, -0.15670086041281373, -0.15750879008729715,
      -0.15828342999032449, -0.159024778126506, -0.15973283800994156,
      -0.1604076184970212, -0.16104913361723838, -0.16165740240213211,
      -0.16223244871246498, -0.16277430106372687, -0.16328299245008079,
      -0.1637585601668593, -0.16420104563169463, -0.16461049420442964,
      -0.16498695500586363, -0.16533048073550624, -0.16564112748838486,
      -0.16591895457105982, -0.16616402431693578, -0.16637640190098432,
      -0.16655615515399028, -0.1667033543764371, -0.16681807215212474,
      -0.16690038316165753, -0.1669503639958877, -0.16696809296944795,
      -0.16695364993447276, -0.1669071160946187, -0.16682857381950772,
      -0.16671810645968732, -0.16657579816223853, -0.16640173368712968,
      -0.1661959982244266, -0.16595867721248025, -0.16568985615719539,
      -0.16538962045248529, -0.1650580552020364, -0.16469524504247551,
      -0.16430127396805821, -0.16387622515698891, -0.16342018079946502,
      -0.16293322192757026, -0.16241542824710703, -0.16186687797148386,
      -0.16128764765775647, -0.16067781204492446, -0.16003744389459068,
      -0.159366613834079, -0.15866539020211529, -0.1579338388971665,
      -0.15717202322853466, -0.15638000377031647, -0.15555783821828889,
      -0.15470558124986766, -0.15382328438717646, -0.15291099586335452,
      -0.15196876049218191, -0.15099661954110377, -0.14999461060774952,
      -0.14896276750003068, -0.1479011201198937, -0.14680969435082011,
      -0.14568851194914467, -0.144537590439279, -0.1433569430129058,
      -0.14214657843223238, -0.140906500937364, -0.13963671015787474,
      -0.13833720102864583, -0.13700796371003116, -0.13564898351242521,
      -0.13426024082528709, -0.13284171105069181, -0.13139336454145262,
      -0.12991516654389076, -0.12840707714528854, -0.12686905122608935,
      -0.12530103841689189, -0.12370298306028732, -0.12207482417757795,
      -0.12041649544043366, -0.11872792514751548, -0.11700903620610653,
      -0.11525974611879837, -0.11347996697524182, -0.11166960544902488,
      -0.10982856279967881, -0.10795673487984997, -0.10605401214767032,
      -0.10412027968432863, -0.10215541721687788, -0.10015929914628288,
      -0.098131794580730153, -0.0960727673742121, -0.093982076170375281,
      -0.091859574451674489, -0.089705110593792978, -0.0875185279253664,
      -0.08529966479298294, -0.08304835463147181, -0.080764426039458215,
      -0.07844770286019366, -0.076098004267617744, -0.0737151448576803,
      -0.071298934744865719, -0.068849179663909049, -0.066365681076710134,
      -0.063848236284364729, -0.061296638544344445, -0.058710677192735455,
      -0.056090137771561993, -0.0534348021611029, -0.050744448717191526,
      -0.048018852413467886, -0.045257784988497932, -0.042461015097760332,
      -0.0396283084704149, -0.036759428070816849, -0.033854134264728608,
      -0.030912184990147751, -0.027933335932712217, -0.024917340705632909,
      -0.021863951034031395, -0.018772916943698911, -0.01564398695412747,
      -0.012476908275797463, -0.0092714270116145, -0.0060272883624409024,
      -0.0027442368366180914, 0.00057798353657098622, 0.0039396289896245357,
      0.007340955795756457, 0.010782220044208729, 0.014263677411946035,
      0.017785582931906962, 0.021348190757843076, 0.02495175392587573,
      0.028596524112875388, 0.0322827513917226, 0.036010683983614844,
      0.039780568007466537, 0.043592647226554523, 0.047447162792474552,
      0.051344352986568864, 0.055284452958893587, 0.059267694464859952,
      0.063294305599671974, 0.0673645105306513, 0.071478529227615051,
      0.075636577191358884, 0.0798388651804538, 0.084085598936384454,
      0.088376978907249437, 0.092713199970071519, 0.097094451151886474,
      0.10152091534975452, 0.10599276904975495, 0.11051018204518875,
      0.11507331715405986, 0.11968232993595344, 0.12433736840854223,
      0.12903857276371825, 0.13378607508361973, 0.138579999056593,
      0.14342045969328313, 0.14830756304296444, 0.15324140591027194,
      0.15822207557244641, 0.16324964949726908, 0.16832419506179677,
      0.17344576927204394, 0.17861441848379006, 0.1838301781245788,
      0.18909307241715556, 0.19440311410437017, 0.19976030417580459,
      0.20516463159615791, 0.21061607303563287, 0.21611459260238519,
      0.22166014157722941, 0.22725265815073273, 0.23289206716281716,
      0.23857827984505375, 0.24431119356574335, 0.25009069157797642,
      0.25591664277075954, 0.26178890142339956, 0.26770730696325551,
      0.27367168372699424, 0.27968184072552144, 0.28573757141267409,
      0.29183865345788385, 0.29798484852284884, 0.30417590204247308,
      0.31041154301006829, 0.31669148376709327, 0.32301541979743476,
      0.32938302952646076, 0.33579397412491629, 0.34224789731779415,
      0.34874442519836324, 0.35528316604739008, 0.36186371015776442,
      0.36848562966458437, 0.37514847838086524, 0.38185179163898453,
      0.3885950861379418, 0.3953778597966206, 0.40219959161307989,
      0.40905974153008279, 0.41595775030687021, 0.4228930393973796,
      0.4298650108349642, 0.43687304712370117, 0.44391651113646791,
      0.4509947460197713, 0.45810707510555404, 0.4652528018299541,
      0.47243120965919527, 0.479641562022676, 0.48688310225329645,
      0.49415505353520539, 0.50145661885893245, 0.50878698098411046,
      0.51614530240973833, 0.52353072535218292, 0.53094237173087677,
      0.53837934316188518, 0.54584072095931657, 0.55332556614472428,
      0.56083291946447478, 0.56836180141523618, 0.57591121227753694,
      0.58348013215755157, 0.59106752103706706, 0.59867231883175787,
      0.60629344545773689, 0.61392980090650673, 0.62158026532824273,
      0.62924369912356526, 0.63691894304369734, 0.644604818299169,
      0.65230012667696557, 0.66000365066625721, 0.66771415359261832,
      0.6754303797608413, 0.683151054606309, 0.69087488485491477,
      0.69860055869160753, 0.7063267459374607, 0.71405209823537419,
      0.72177524924428449, 0.72949481484199374, 0.73720939333649338,
      0.74491756568584855, 0.75261789572659366, 0.76030893041058323,
      0.76798920005034255, 0.7756572185728049, 0.78331148378148763,
      0.79095047762698067, 0.79857266648578729, 0.80617650144742248,
      0.81376041860972226, 0.82132283938236073, 0.82886217079844038,
      0.83637680583419349, 0.84386512373663136, 0.85132549035916449,
      0.85875625850507242, 0.866155768278764, 0.87352234744477575,
      0.88085431179437612, 0.88814996551976777, 0.89540760159571775,
      0.90262550216862358, 0.90980193895281736, 0.91693517363410393,
      0.92402345828039567, 0.93106503575931066, 0.9380581401627115,
      0.94500099723798092, 0.95189182482600909, 0.958728833305711,
      0.96551022604500247, 0.97223419985808124, 0.978898945468919,
      0.98550264798082154, 0.99204348735191661, 0.99851963887647421,
      1.0049292736718656, 1.0112705591711044, 1.0175416596207294,
      1.0237407365839901, 1.0298659494490965, 1.0359154559424384,
      1.0418874126466287, 1.0477799755231521, 1.053591300439559,
      1.0593195437009519, 1.0649628625856677, 1.0705194158849567,
      1.0759873644465108, 1.0813648717216715, 1.0866501043161194,
      1.0918412325439233, 1.0969364309847156, 1.1019338790438706,
      1.1068317615154637, 1.1116282691478678, 1.1163215992117643,
      1.1209099560704181, 1.1253915517520228, 1.1297646065239053,
      1.1340273494684379, 1.138178019060426, 1.1422148637458245,
      1.1461361425215331, 1.149940125516137, 1.1536250945713442,
      1.1571893438239456, 1.1606311802881155, 1.1639489244377996,
      1.1671409107890507, 1.1702054884820714, 1.17314102186277,
      1.1759458910636356, 1.178618492583712, 1.1811572398674783,
      1.1835605638824258, 1.1858269136951238, 1.187954757045574,
      1.1899425809196409, 1.1917888921193398, 1.1934922178308154, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.4090837461962593,
      -1.4110200398321171, -1.4127528419194924, -1.4142806654264433,
      -1.4156020623530199, -1.4167156242525132, -1.417619982744458,
      -1.4183138100192194, -1.4187958193340002, -1.4190647655000983,
      -1.4191194453612577, -1.4189586982629434, -1.4185814065123885,
      -1.4179864958292518, -1.41717293578673, -1.4161397402429738,
      -1.4148859677626575, -1.4134107220285455, -1.4117131522429189,
      -1.4097924535187158, -1.4076478672602337, -1.4052786815332703,
      -1.4026842314245509, -1.3998638993903167, -1.39681711559394,
      -1.3935433582324332, -1.3900421538517322, -1.3863130776506194,
      -1.3823557537731777, -1.3781698555896433, -1.3737551059655564,
      -1.3691112775190803, -1.3642381928663954, -1.3591357248550449,
      -1.3538037967851437, -1.3482423826183374, -1.34245150717442,
      -1.3364312463155101, -1.3301817271177006, -1.3237031280300879,
      -1.3169956790210975, -1.3100596617120221, -1.3028954094976954,
      -1.2955033076542239, -1.28788379343371, -1.2800373561458844,
      -1.2719645372266026, -1.2636659302931208, -1.2551421811861121,
      -1.2463939879983557, -1.2374221010900537, -1.2282273230907237,
      -1.218810508887624, -1.2091725656006744, -1.19931445254383,
      -1.189237181172875, -1.1789418150196098, -1.168429469612406,
      -1.1577013123830977, -1.1467585625602046, -1.1356024910484592,
      -1.1242344202946304, -1.1126557241396455, -1.1008678276569868,
      -1.0888722069773864, -1.0766703890998022, -1.0642639516886958,
      -1.0516545228576224, -1.0388437809391398, -1.025833454241065,
      -1.0126253207890974, -0.99922120805583758, -0.98562299267622266,
      -0.971832600149434, -0.957852004527291, -0.94368322808919081,
      -0.92932834100363271, -0.914789460976379, -0.900068752885305,
      -0.88516842840200016, -0.87009074560017441, -0.854838008550944,
      -0.83941256690505861, -0.82381681546214747, -0.8080531937270613,
      -0.79212418545338625, -0.77603231817422269, -0.75978016272030835,
      -0.74337033272558539, -0.72680548412030077, -0.71008831461174615,
      -0.69322156315273686, -0.676208009397935, -0.65905047314813536,
      -0.64175181378261892, -0.62431492967969937, -0.60674275762558127,
      -0.58903827221165528, -0.57120448522036082, -0.55324444499974812,
      -0.53516123582687236, -0.516957977260167, -0.49863782348093205,
      -0.48020396262408593, -0.46165961609833361, -0.44300803789589926,
      -0.42425251389198476, -0.40539636113411159, -0.38644292712150669,
      -0.36739558907470526, -0.34825775319553359, -0.32903285391764775,
      -0.30972435314780439, -0.29033573949803959, -0.27087052750894131,
      -0.251332256864198, -0.231724491596612, -0.21205081928576708,
      -0.19231485024754763, -0.17252021671570084, -0.152670572015644,
      -0.1327695897307184, -0.11282096286109418, -0.092828402975532173,
      -0.072795639356215663, -0.052726418136858293, -0.032624501434310706,
      -0.012493666473874617, 0.0076622952914496174, 0.02783957906756385,
      0.048034367611497909, 0.068242832129031122, 0.08846113317748476,
      0.10868542157345372, 0.12891183930524472, 0.14913652044979017,
      0.16935559209379453, 0.18956517525888633, 0.20976138583052423,
      0.22994033549042636, 0.25009813265227321, 0.27023088340044193,
      0.29033469243153126, 0.31040566399841585, 0.33043990285660046,
      0.35043351521260813, 0.37038260967415865, 0.39028329820188812,
      0.410131697062343, 0.42992392778201521, 0.44965611810214,
      0.46932440293402067, 0.48892492531460768, 0.50845383736208749,
      0.52790730123120921, 0.54728149006810578, 0.56657258896433427,
      0.58577679590989018, 0.60489032274492338, 0.623909396109904,
      0.64283025839397379, 0.66164916868121981, 0.68036240369461765,
      0.69896625873737361, 0.7174570486314108, 0.73583110865273893,
      0.75408479546344354, 0.77221448804003956, 0.79021658859792454,
      0.8080875235116759, 0.82582374423093174, 0.84342172819159966,
      0.86087797972213143, 0.87818903094461265, 0.89535144267040612,
      0.9123618052900998, 0.9292167396575, 0.94591289796741918,
      0.962446964627011, 0.97881565712039309, 0.99501572686631734,
      1.0110439600686316, 1.0268971785592973, 1.042572240633705,
      1.0580660418780574, 1.0733755159885678, 1.0884976355822398,
      1.1034294129989892, 1.1181679010948735, 1.1327101940261886,
      1.1470534280242091, 1.1611947821603352, 1.1751314791014225,
      1.1888607858550668, 1.2023800145046206, 1.2156865229337215,
      1.2287777155401132, 1.2416510439385444, 1.2543040076525267,
      1.266734154794751, 1.2789390827359421, 1.2909164387619572,
      1.3026639207189155, 1.3141792776461745, 1.3254603103969302,
      1.3365048722462836, 1.347310869486549, 1.3578762620096356,
      1.3681990638763188, 1.3782773438722089, 1.3881092260502517,
      1.3976928902595787, 1.4070265726605435, 1.41610856622577,
      1.4249372212270546, 1.4335109457079582, 1.4418282059419405,
      1.4498875268758684, 1.4576874925587695, 1.4652267465556661,
      1.4725039923463696, 1.4795179937090768, 1.4862675750886551,
      1.492751621949469, 1.4989690811126442, 1.5049189610776257,
      1.5106003323279331, 1.5160123276209856, 1.5211541422619037,
      1.526025034361169, 1.5306243250760507, 1.5349513988357044,
      1.5390057035498517, 1.542786750800947, 1.5462941160197672,
      1.5495274386443243, 1.5524864222620482, 1.5551708347351629,
      1.5575805083091889, 1.5597153397045227, 1.5615752901910294,
      1.5631603856456109, 1.5644707165926868, 1.5655064382275712,
      1.5662677704226862, 1.566754997716604, 1.5669684692858714,
      1.5669085988996145, 1.56657586485689, 1.5659708099067882,
      1.5650940411512702, 1.5639462299307398, 1.5625281116923577,
      1.5608404858411027, 1.5588842155735949, 1.556660227694695,
      1.5541695124169106, 1.5514131231426245, 1.5483921762291977,
      1.54510785073696, 1.5415613881601535, 1.5377540921408617,
      1.5336873281659804, 1.5293625232472967, 1.5247811655847194,
      1.5199448042127468, 1.5148550486302341, 1.509513568413539,
      1.5039220928131267, 1.4980824103337191, 1.4919963682980886,
      1.4856658723945806, 1.4790928862084671, 1.4722794307372511,
      1.4652275838900115, 1.4579394799709213, 1.450417309147046,
      1.4426633169005543, 1.4346798034654695, 1.4264691232490916,
      1.4180336842382302, 1.409375947390396, 1.400498426010083,
      1.3914036851103166, 1.3820943407596069, 1.3725730594144634,
      1.3628425572376597, 1.3529055994023889, 1.3427649993825073,
      1.332423618229029, 1.3218843638330597, 1.3111501901753551,
      1.3002240965626954, 1.2891091268512642, 1.2778083686572463,
      1.2663249525548201, 1.2546620512617808, 1.2428228788129785,
      1.2308106897218094, 1.218628778129953, 1.2062804769455964,
      1.1937691569703615, 1.1810982260151688, 1.1682711280052593,
      1.1552913420746265, 1.142162381650081, 1.1288877935252046,
      1.1154711569244262, 1.1019160825574812, 1.0882262116644905,
      1.074405215051933, 1.0604567921197565, 1.0463846698798858,
      1.0321926019664061, 1.017884367637671, 1.0034637707706202,
      0.98893463884756183, 0.97430082193571632, 0.95956619165976753,
      0.94473464016773645, 0.92981007909042734, 0.91479643849475412,
      0.89969766583121236, 0.88451772487580371, 0.86926059466669015,
      0.85393026843587827, 0.83853075253621689, 0.82306606536401739,
      0.80754023627758442, 0.79195730451195934, 0.7763213180901718,
      0.76063633273131448, 0.744906410755726, 0.72913561998760523,
      0.71332803265534339, 0.69748772428989858, 0.681618772621509,
      0.6657252564750572, 0.64981125466439627, 0.63388084488593965,
      0.61793810261184678, 0.60198709998308009, 0.58603190470268829,
      0.57007657892958719, 0.55412517817318518, 0.53818175018913461,
      0.52225033387655351, 0.50633495817699858, 0.49043964097553233,
      0.4745683880041664, 0.45872519174802473, 0.44291403035450921,
      0.42713886654580419, 0.41140364653500772, 0.39571229894621862,
      0.3800687337388779, 0.36447684113667916, 0.34894049056134646,
      0.33346352957160186, 0.31804978280760754, 0.30270305094121058,
      0.28742710963227353, 0.27222570849139782, 0.25710257004935311,
      0.24206138873348781, 0.22710582985144412, 0.21223952858244766,
      0.19746608897648502, 0.18278908296164864, 0.16821204935994907,
      0.15373849291186617, 0.13937188330994693, 0.12511565424170737,
      0.11097320244214626, 0.096947886756121968, 0.083043027210894169,
      0.069261904099079577, 0.055607757072313427, 0.042083784245867062,
      0.028693141314502037, 0.01543894067980634, 0.0023242505892863436,
      -0.0106479057125364, -0.023474550820770049, -0.036152753994294705,
      -0.04867963196714005, -0.061052349746876539, -0.0732681213997662,
      -0.085324210822438212, -0.097217932499869236, -0.10894665224942325,
      -0.1205077879507397, -0.13189881026123851, -0.14311724331703923,
      -0.15416066541906362, -0.16502670970412942, -0.17571306480081492,
      -0.18621747546991241, -0.19653774322925391, -0.2066717269627342,
      -0.21661734351333062, -0.22637256825994889, -0.23593543567790376,
      -0.2453040398828662, -0.25447653515811369, -0.26345113646490642,
      -0.2722261199358379, -0.28079982335099907, -0.28917064659681485,
      -0.29733705210739381, -0.30529756528826174, -0.3130507749223348,
      -0.32059533355800857, -0.32792995787923473, -0.33505342905745944,
      -0.34196459308531696, -0.34866236109195908, -0.3551457096399262,
      -0.3614136810034454, -0.36746538342807761, -0.3732999913716073,
      -0.37891674572610973, -0.38431495402109705, -0.38949399060768836,
      -0.39445329682372104, -0.3991923811397553, -0.40371081928590108,
      -0.40800825435942828, -0.41208439691310522, -0.41593902502423341,
      -0.41957198434433679, -0.42298318812948227, -0.42617261725120348,
      -0.42914032018801657, -0.43188641299750552, -0.43441107926898404,
      -0.4367145700567206, -0.43879720379373882, -0.44065936618620466,
      -0.4423015100884089, -0.44372415535837673, -0.44492788869412236,
      -0.44591336345059168, -0.44668129943732332, -0.44723248269687704,
      -0.44756776526407666, -0.44768806490613089, -0.44759436484368131,
      -0.4472877134528554, -0.44676922394839019, -0.44604007404791013,
      -0.4451015056174395, -0.44395482429823641, -0.44260139911505264,
      -0.44104266206590736, -0.43928010769348969, -0.43731529263829727,
      -0.43514983517362987, -0.43278541472255694, -0.43022377135698947,
      -0.42746670527898695, -0.4245160762844426, -0.421373803209278,
      -0.41804186335831339, -0.41452229191694834, -0.41081718134583156,
      -0.4069286807586634, -0.40285899528331742, -0.39861038540644378,
      -0.39418516630173855, -0.38958570714206747, -0.38481443039561414,
      -0.37987381110627583, -0.37476637615847741, -0.36949470352662467,
      -0.36406142150939236, -0.35846920794907228, -0.3527207894361879,
      -0.34681894049959938, -0.34076648278232746, -0.33456628420332474,
      -0.328221258105426, -0.32173436238972813, -0.31510859863661583,
      -0.30834701121371666, -0.3014526863710057, -0.29442875132332846,
      -0.28727837332059969, -0.28000475870593761, -0.27261115196200414,
      -0.26510083474581336, -0.257477124912297, -0.24974337552687961,
      -0.24190297386736828, -0.23395934041542574, -0.22591592783792197,
      -0.21777621995844682, -0.20954373071927915, -0.20122200313411681,
      -0.19281460823185825, -0.18432514399173033, -0.17575723427009216,
      -0.16711452771918944, -0.15840069669820486, -0.14961943617687748,
      -0.14077446263204402, -0.13186951293739238, -0.12290834324675923,
      -0.11389472787128965, -0.10483245815077784, -0.095725341319528923,
      -0.086577199367048885, -0.077391867893905369, -0.068173194963085992,
      -0.058925039947183643, -0.049651272371749919, -0.040355770755140685,
      -0.031042421445195176, -0.021715117453091945, -0.012377757284703896,
      -0.0030342437698143224, 0.0063115171104941442, 0.015655617397907905,
      0.024994148332091841, 0.034323201526676068, 0.043638870145699116,
      0.052937250080148254, 0.062214441124257447, 0.071466548151230616,
      0.080689682288028891, 0.089879962088899881, 0.099033514707284942,
      0.10814647706577635, 0.11721499702378387, 0.12623523454255081,
      0.13520336284720516, 0.14411556958547417, 0.15296805798276009,
      0.161757047993198, 0.17047877744639314, 0.17912950318947859,
      0.1877055022241611, 0.19620307283843968, 0.20461853573263258,
      0.21294823513940825, 0.22118853993747772, 0.2293358447586222,
      0.23738657108773586, 0.24533716835554492, 0.25318411502369803,
      0.2609239196618981, 0.26855312201675646, 0.27606829407206024,
      0.2834660411001283, 0.29074300270396347, 0.29789585384986833,
      0.30492130589024069, 0.3118161075762314, 0.318577046059974,
      0.32520094788608034, 0.33168467997211237, 0.33802515057774046,
      0.34421931026229841, 0.35026415283044815, 0.35615671626567824,
      0.36189408365135012, 0.36747338407902891, 0.3728917935438178,
      0.37814653582643554, 0.38323488336177008, 0.38815415809364817,
      0.39290173231557496, 0.39747502949717634, 0.40187152509611324,
      0.4060887473552065, 0.4101242780845587, 0.41397575342840759,
      0.41764086461650962, 0.42111735869980704, 0.42440303927016942,
      0.42749576716398846, 0.43039346114941357, 0.43309409859702408,
      0.4355957161337316, 0.43789641027972037, 0.43999433806822885,
      0.441887717647982, 0.44357482886810373, 0.4450540138453174,
      0.4463236775132699, 0.44738228815381409, 0.44822837791007891,
      0.44886054328118341, 0.44927744559842786, 0.44947781148283183,
      0.44946043328386553, 0.44922416949925026, 0.44876794517569019,
      0.44809075229041551, 0.44719165011342032, 0.44606976555027922,
      0.4447242934654369, 0.44315449698586906, 0.44135970778502381,
      0.43933932634694561, 0.43709282221050366, 0.43461973419364675,
      0.43191967059760938, 0.42899230939100613, 0.42583739837374951,
      0.42245475532074184, 0.41884426810529218, 0.4150058948022074,
      0.41093966377053315, 0.40664567371590665, 0.40212409373249997,
      0.39737516332452488, 0.39239919240730869, 0.3871965612879098,
      0.381767720625288, 0.3761131913700323, 0.37023356468364904,
      0.36412950183744347, 0.35780173409099991, 0.3512510625503103,
      0.34447835800556315, 0.33748456074865651, 0.33027068037046825,
      0.32283779553794451, 0.31518705375105743, 0.3073196710797077,
      0.2992369318806356, 0.29094018849442216, 0.28243086092265712,
      0.27371043648537147, 0.26478046945881967, 0.25564258069372364,
      0.24629845721406751, 0.23674985179657651, 0.22699858253097485,
      0.21704653236117211, 0.2068956486074757, 0.19654794246999135,
      0.18600548851333937, 0.17527042413283137, 0.164344949002265,
      0.15323132450348129, 0.14193187313786482, 0.13044897791993434,
      0.11878508175321272, 0.10694268678854013, 0.094924353765022326,
      0.082732701333803171, 0.070370405364845817, 0.057840198236927813,
      0.045144868111051485, 0.032287258187473196, 0.019270265946580968,
      0.0060968423738033354, -0.0072300088311852443, -0.020707232060768112,
      -0.03433172062095316, -0.048100317567970279, -0.062009816559661389,
      -0.076056962721409188, -0.090238453526366391, -0.10455093968973123,
      -0.11899102607680183, -0.13355527262456002, -0.14824019527650861,
      -0.16304226693050333, -0.17795791839929859, -0.19298353938353308,
      -0.208115479456876, -0.2233500490630384, -0.23868352052439287,
      -0.25411212906186481, -0.269632073825847, -0.28523951893779653,
      -0.30093059454225918, -0.31670139786898144, -0.33254799430481219,
      -0.34846641847509374, -0.3644526753342287, -0.38050274126509753,
      -0.39661256518701726, -0.41277806967191066, -0.428995152068396,
      -0.44525968563341883, -0.46156752067115603, -0.47791448567880496,
      -0.494296388498996, -0.51070901747842323, -0.52714814263241117,
      -0.54360951681505931, -0.56008887689461773, -0.57658194493379222,
      -0.59308442937458294, -0.60959202622736053, -0.62610042026381518,
      -0.64260528621343582, -0.65910228996318232, -0.67558708975998916,
      -0.69205533741576575, -0.70850267951455015, -0.72492475862144756,
      -0.74131721449302745, -0.75767568528880758, -0.77399580878350516,
      -0.79027322357966667, -0.80650357032037046, -0.82268249290160267,
      -0.83880563968401478, -0.85486866470366141, -0.87086722888139423,
      -0.88679700123056737, -0.90265366006269365, -0.91843289419071561,
      -0.9341304041295313, -0.94974190329344665, -0.96526311919019414,
      -0.98068979461118833, -0.99601768881766584, -1.0112425787223658,
      -1.02636026006643, -1.0413665485911621, -1.0562572812043245,
      -1.0710283171406363, -1.0856755391161221, -1.1001948544760209,
      -1.1145821963358726, -1.1288335247155048, -1.1429448276655541,
      -1.1569121223862413, -1.1707314563380367, -1.1843989083439301,
      -1.1979105896829751, -1.2112626451748063, -1.2244512542548067,
      -1.2374726320396277, -1.2503230303827502, -1.262998738919805,
      -1.2754960861033244, -1.2878114402266621, -1.2999412104367618,
      -1.3118818477355068, -1.3236298459693669, -1.3351817428070429,
      -1.3465341207048507, -1.3576836078595569, -1.3686268791484171,
      -1.3793606570561265, -1.3898817125884344, -1.4001868661721661,
      -1.4102729885413916, -1.4201370016094987, -1.4297758793269195,
      -1.4391866485242677, -1.4483663897406662, -1.4573122380370069,
      -1.4660213837939355, -1.4744910734943319, -1.4827186104900669,
      -1.4907013557528226, -1.4984367286087663, -1.5059222074568739,
      -1.5131553304707117, -1.5201336962834684, -1.5268549646560554,
      -1.533316857128094, -1.5395171576516107, -1.545453713207255,
      -1.5511244344028894, -1.5565272960543723, -1.5616603377483835,
      -1.566521664387142, -1.5711094467148596, -1.5754219218258005,
      -1.5794573936537954, -1.5832142334430988, -1.5866908802004405,
      -1.5898858411281791, -1.5927976920384128, -1.5954250777479702,
      -1.5977667124541475, -1.5998213800911267, -1.6015879346669508,
      -1.6030653005810005, -1.6042524729218703, -1.6051485177455795,
      -1.6057525723340529, -1.6060638454337979, -1.6060816174747377,
      -1.6058052407691266, -1.6052341396905292, -1.604367810832803,
      -1.6032058231490636, -1.6017478180706017, -1.5999935096057245,
      -1.5979426844185207, -1.5955952018875201, -1.5929509941442663,
      -1.5900100660917837, -1.5867724954029563, -1.5832384324988391,
      -1.5794081005069143, -1.5752817951993041, -1.5708598849110089,
      -1.5661428104381661, -1.5611310849164064, -1.555825293679332,
      -1.5502260940971853, -1.5443342153957689, -1.538150458455678,
      -1.5316756955919069, -1.5249108703139413, -1.5178569970663747,
      -1.5105151609501763, -1.5028865174246848, -1.4949722919904198,
      -1.4867737798528542, -1.4782923455672112, -1.4695294226644342,
      -1.4604865132584419, -1.4511651876347937, -1.4415670838209032,
      -1.4316939071379322, -1.4215474297345159, -1.4111294901024567,
      -1.4004419925745502, -1.3894869068047038, -1.378266267230488,
      -1.3667821725183302, -1.3550367849914817, -1.3430323300409703,
      -1.3307710955197007, -1.3182554311198913, -1.3054877477340605,
      -1.2924705167997388, -1.2792062696281064, -1.2656975967167849,
      -1.2519471470469727, -1.2379576273651534, -1.2237318014495822,
      -1.2092724893617874, -1.1945825666833119, -1.1796649637379142,
      -1.1645226647994955, -1.1491587072859448, -1.1335761809391949,
      -1.117778226991704, -1.101768037319639, -1.0855488535829787,
      -1.0691239663528449, -1.0524967142262749, -1.0356704829287413,
      -1.0186487044046502, -1.001434855896117, -0.98403245901029857,
      -0.96644507877552255, -0.94867632268653623, -0.93072983973914281,
      -0.912609319454494, -0.89431849089337567, -0.87586112166070529,
      -0.85724101690061383, -0.83846201828235833, -0.81952800297738138,
      -0.80044288262780972, -0.7812106023067128, -0.76183513947040327,
      -0.74232050290312124, -0.72267073165435836, -0.70288989396918866,
      -0.68298208621188783, -0.66295143178316329, -0.64280208003130046,
      -0.62253820515756852, -0.60216400511617374, -0.58168370050908558,
      -0.56110153347610647, -0.54042176658040153, -0.51964868168992251,
      -0.4987865788549844, -0.47783977518233289, -0.45681260370603732,
      -0.43570941225551751, -0.41453456232104374, -0.39329242791704394,
      -0.37198739444350221, -0.3506238575458287, -0.32920622197349952,
      -0.30773890043778923, -0.28622631246892571, -0.26467288327301219,
      -0.2430830425889986, -0.22146122354609468, -0.19981186152185429,
      -0.17813939300135395, -0.15644825443772317, -0.13474288111436755,
      -0.11302770600921022, -0.09130715866126507, -0.0695856640398652,
      -0.0478676414168518, -0.02615750324207252, -0.0044596540224436654,
      0.01722151079504, 0.03888160593608448, 0.060516257407344391,
      0.082121103599817072, 0.10369179638709543, 0.12522400221817032,
      0.14671340320445858, 0.16815569820080881, 0.18954660388012218,
      0.21088185580134156, 0.23215720947050345, 0.25336844139454207,
      0.2745113501275892, 0.29558175730947123, 0.31657550869609469,
      0.33748847518151087, 0.35831655381129396, 0.37905566878702529,
      0.39970177246158889, 0.4202508463250067, 0.44069890198056572,
      0.46104198211095432, 0.48127616143417312, 0.50139754764893674,
      0.521402282369371, 0.54128654204867843, 0.56104653889160361,
      0.58067852175541179, 0.60017877703916844, 0.61954362956107956,
      0.63876944342366471, 0.65785262286652724, 0.67678961310654528,
      0.6955769011652021, 0.7142110166829001, 0.73268853272001977,
      0.75100606654453161, 0.76916028040596551, 0.78714788229553367,
      0.804965626692209, 0.82261031529461914, 0.84007879773851146,
      0.85736797229964667, 0.87447478658195787, 0.8913962381907875,
      0.90812937539104521, 0.924671297750137, 0.94101915676550651,
      0.95717015647662529, 0.97312155406133571, 0.98887066041634475,
      1.0044148407217903, 1.0197515149897067, 1.0348781585963105,
      1.0497923027979481, 1.0644915352306215, 1.0789735003929519,
      1.0932359001125298, 1.1072764939954891, 1.1210930998592594,
      1.1346835941483988, 1.1480459123334013, 1.1611780492924371,
      1.1740780596759315, 1.1867440582539048, 1.1991742202460598,
      1.2113667816344911, 1.2233200394590222, 1.2350323520950959,
      1.2465021395141878, 1.2577278835267041, 1.2687081280073254,
      1.2794414791027922, 1.2899266054220855, 1.3001622382090194,
      1.3101471714972042, 1.3198802622473962, 1.3293604304672306,
      1.3385866593133449, 1.3475579951759011, 1.3562735477455292,
      1.3647324900626954, 1.3729340585495646, 1.3808775530243387,
      1.3885623366981399, 1.3959878361544733, 1.4031535413113145,
      1.410059005365881, 1.4167038447221358, 1.4230877389010894,
      1.4292104304339797, 1.4350717247383784, 1.4406714899773254,
      1.4460096569015588, 1.4510862186749318, 1.4559012306831116,
      1.4604548103256485, 1.4647471367915328, 1.468778450818325,
      1.4725490544349862, 1.4760593106885151, 1.4793096433545221,
      1.4823005366318458, 1.4850325348213662, 1.4875062419891256,
      1.4897223216139035, 1.4916814962193954, 1.4933845469911289,
      1.4948323133782722, 1.4960256926804949, 1.4969656396200268,
      1.4976531658990988, 1.4980893397429074, 1.4982752854282928,
      1.498212182798293, 1.4979012667627656, 1.4973438267852401,
      1.4965412063562042, 1.4954948024530055, 1.4942060649865556,
      1.4926764962350523, 1.4909076502648941, 1.4889011323390078,
      1.4866585983127925, 1.4841817540178777, 1.4814723546339306,
      1.4785322040487063, 1.4753631542065677, 1.4719671044457032,
      1.4683460008242504, 1.4645018354355737, 1.4604366457129117,
      1.4561525137236222, 1.4516515654532673, 1.4469359700797937,
      1.4420079392380041, 1.4368697262746042, 1.4315236254940473,
      1.4259719713954189, 1.4202171379006403, 1.4142615375741965,
      1.4081076208346741, 1.401757875158353, 1.3952148242751, 1.3884810273568422,
      1.3815590781988494, 1.37445160439411, 1.3671612665010562,
      1.359690757204892, 1.3520428004727956, 1.34422015070327,
      1.3362255918698902, 1.3280619366597182, 1.3197320256066791,
      1.3112387262201246, 1.3025849321088876, 1.293773562101092,
      1.2848075593599568, 1.2756898904959308, 1.2664235446753602,
      1.2570115327260032, 1.2474568862396525, 1.2377626566721298,
      1.2279319144409455, 1.2179677480208733, 1.2078732630377176,
      1.1976515813605537, 1.1873058401927152, 1.1768391911617728,
      1.1662547994088133, 1.1555558426772585, 1.144745510401507,
      1.1338270027956632, 1.1228035299426382, 1.1116783108838486,
      1.1004545727098296, 1.0891355496519863, 1.0777244821757792,
      1.0662246160755822, 1.0546392015714825, 1.0429714924082916,
      1.031224744957012, 1.0194022173190247, 1.0075071684332524,
      0.99554285718654922, 0.98351254152757572, 0.971419477584395,
      0.95926691878606007, 0.947058114988418, 0.93479631160439536,
      0.922484748738972, 0.91012666032914058, 0.89772527328903085,
      0.88528380666047368, 0.87280547076922133, 0.86029346638704884,
      0.84775098389999548, 0.8351812024829276, 0.82258728928068636,
      0.80997239859601022, 0.79733967108447212, 0.78469223295663382,
      0.77203319518763491, 0.75936565273441847, 0.746692683760811,
      0.7340173488706434, 0.72134269034914167, 0.708671731412736,
      0.69600747546753727, 0.683352905376628, 0.67071098273638452,
      0.65808464716198856, 0.64547681558232806, 0.63289038154445443,
      0.62032821452777887, 0.607793159268153, 0.5952880350920412,
      0.58281563526089786, 0.57037872632596176, 0.55798004749357077,
      0.54562231000118655, 0.53330819650425931, 0.52104036047407376,
      0.508821425606741, 0.49665398524342774, 0.48454060180199926,
      0.47248380622018504, 0.46048609741038726, 0.44854994172625662,
      0.43667777244116157, 0.42487198923864294, 0.41313495771498854,
      0.40146900889399623, 0.38987643875406258, 0.37835950776767241,
      0.36692044045338279, 0.35556142494038251, 0.34428461254574066,
      0.33309211736437527, 0.32198601587186676, 0.31096834654013739,
      0.30004110946610979, 0.28920626601337746, 0.27846573846695255,
      0.267821409701144, 0.25727512286062182, 0.24682868105470326,
      0.23648384706490164, 0.22624234306579746, 0.21610585035921534,
      0.20607600912179033, 0.19615441816591292, 0.18634263471408025,
      0.1766421741866725, 0.16705451000316379, 0.15758107339676181,
      0.1482232532425253, 0.13898239589887576, 0.12985980506258213,
      0.12085674163715875, 0.11197442361467309, 0.10321402597095848,
      0.09457668057418582, 0.086063476106787842, 0.077675458000708783,
      0.069413628385909074, 0.061278946052139627, 0.053272326423899334,
      0.045394641548553993, 0.037646720097552322, 0.030029347380695633,
      0.022543265373397327, 0.0151891727568651, 0.0079677249711507,
      0.0008795342809917988, -0.006074830145626273, -0.012894842146273854,
      -0.019580018460310704, -0.026129918612649079, -0.032544144785125573,
      -0.03882234167557997, -0.044964196344725184, -0.050969438050932632,
      -0.056837838072994654, -0.062569209521011068, -0.068163407135478443,
      -0.0736203270747153, -0.078939906690723469, -0.084122124293616166,
      -0.089166998904720532, -0.094074589998502364, -0.0988449972334139,
      -0.10347836017181804, -0.10797485798911273, -0.11233470917218788,
      -0.11655817120737434, -0.12064554025800368, -0.12459715083173589,
      -0.12841337543781159, -0.13209462423435606, -0.13564134466591798,
      -0.13905402109137444, -0.14233317440236914, -0.14547936163245298,
      -0.14849317555707253, -0.15137524428459279, -0.15412623083850222,
      -0.15674683273098372, -0.159237781528014, -0.16159984240617215,
      -0.16383381370133462, -0.16594052644942453, -0.16792084391940407,
      -0.16977566113869, -0.1715059044111662, -0.1731125308280031,
      -0.17459652777143581, -0.17595891241171577, -0.17720073119741073,
      -0.17832305933925788, -0.17932700028774681, -0.18021368520463235,
      -0.18098427242857706, -0.18163994693510696, -0.18218191979109788,
      -0.18261142760395985, -0.18292973196574891, -0.18313811889238593,
      -0.18323789825818734, -0.18323040322592182, -0.18311698967257048,
      -0.18289903561101425, -0.18257794060783569, -0.18215512519745666,
      -0.18163203029279729, -0.181010116592667, -0.18029086398609775,
      -0.17947577095380954, -0.17856635396703735, -0.17756414688389277,
      -0.17647070034348875, -0.17528758115802376, -0.17401637170302334,
      -0.17265866930596302, -0.1712160856334457, -0.16969024607717004,
      -0.16808278913886762, -0.16639536581441811, -0.16462963897736166,
      -0.16278728276198187, -0.16086998194617616, -0.158879431334317,
      -0.15681733514028684, -0.15468540637091024, -0.15248536620995135,
      -0.15021894340289629, -0.14788787364270489, -0.14549389895672438,
      -0.14303876709497135, -0.1405242309199552, -0.13795204779824954,
      -0.13532397899398782, -0.13264178906448759, -0.12990724525816819,
      -0.12712211691496866, -0.12428817486943156, -0.12140719085664356,
      -0.11848093692121667, -0.1155111848294733, -0.11249970548502902,
      -0.10944826834793778, -0.10635864085756869, -0.10323258785940316,
      -0.10007187103589711, -0.096878248341597528, -0.093653473442655108,
      -0.0903992951609224, -0.087117456922777364, -0.083809696212834656,
      -0.080477744032709131, -0.077123324364972878, -0.073748153642472086,
      -0.070353940223136971, -0.066942383870441, -0.063515175239654373,
      -0.060073995370023336, -0.056620515183028922, -0.053156394986850125,
      -0.049683283987168841, -0.046202819804449478, -0.042716627997816892,
      -0.039226321595670577, -0.035733500633139091, -0.032239751696512352,
      -0.028746647474758483, -0.025255746318247094, -0.021768591804786203,
      -0.018286712313081967, -0.014811620603728266, -0.011344813407829887,
      -0.007887771023358435, -0.00444195691933777, -0.0010088173479510633,
      0.00241021903533068, 0.0058137415435252516, 0.0092003578217227412,
      0.012568694202400379, 0.015917396052388129, 0.019245128111415526,
      0.022550574822153936, 0.02583244065169887, 0.029089450404416836,
      0.03232034952609919, 0.035523904399359339, 0.03869890263022141,
      0.041844153325833792, 0.0449584873632827, 0.048040757649431262,
      0.05108983937175389, 0.054104630240125358, 0.057084050719523736,
      0.060027044253617705, 0.062932577479195215, 0.065799640431421544,
      0.06862724673989043, 0.071414433815453288, 0.07416026302780454,
      0.076863819873806388, 0.079524214136545632, 0.082140580035115582,
      0.08471207636510561, 0.08723788662981119, 0.089717219162151141,
      0.092149307237310643, 0.094533409176100286, 0.096868808439055279,
      0.099154813711280917, 0.10139075897805831, 0.10357600359123983,
      0.10570993232644274, 0.1077919554310813, 0.10982150866324816,
      0.11179805332149144, 0.11372107626551885, 0.11559008992785541,
      0.11740463231650933, 0.11916426700867913, 0.12086858313554855,
      0.12251719535822761, 0.12410974383487439, 0.12564589417906977,
      0.12712533740948512, 0.12854778989091903, 0.12991299326675024,
      0.13122071438288438, 0.13247074520325236, 0.13366290271693396,
      0.13479702883698946, 0.1358729902910511, 0.13689067850377842,
      0.13785000947123985, 0.1387509236273064, 0.1395933857021566,
      0.14037738457295412, 0.14110293310681324, 0.1417700679961226,
      0.14237884958634467, 0.14292936169636469, 0.14342171143149809,
      0.14385602898926084, 0.14423246745799387, 0.14455120260846208,
      0.14481243267851535, 0.1450163781509376, 0.14516328152458455,
      0.14525340707891912, 0.14528704063207598, 0.14526448929254768,
      0.14518608120462953, 0.14505216528772882, 0.14486311096966265,
      0.14461930791408156, 0.14432116574211268, 0.14396911374837568,
      0.14356360061148202, 0.14310509409915598, 0.14259408076809765,
      0.14203106565872278, 0.14141657198491331, 0.14075114081890511,
      0.14003533077146146, 0.13926971766744234, 0.13845489421693666,
      0.13759146968206643, 0.13668006953961917, 0.13572133513964355,
      0.13471592336014213, 0.13366450625800985, 0.13256777071635165,
      0.13142641808832434, 0.13024116383765758, 0.12901273717596951,
      0.12774188069704789, 0.12642935000822275, 0.12507591335898927,
      0.12368235126701319, 0.12224945614166859, 0.12077803190525817,
      0.11926889361205011, 0.11772286706529569, 0.11614078843235001,
      0.11452350385806358, 0.11287186907657426, 0.11118674902165174,
      0.10946901743575152, 0.10771955647789902, 0.1059392563305727,
      0.1041290148057097, 0.1022897369500094, 0.10042233464964774,
      0.0985277262345572, 0.09660683608242826, 0.09466059422255535,
      0.092689935939687509, 0.09069580137801693, 0.088679135145438848,
      0.086640885918244148, 0.084582006046363872, 0.082503451159321242,
      0.080406179773013745, 0.07829115289747865, 0.076159333645762925,
      0.0740116868440429, 0.071849178643135447, 0.069672776131507241,
      0.067483446949950288, 0.065282158908021248, 0.063069879602397891,
      0.060847576037280776, 0.058616214246944069, 0.056376758920594655,
      0.0541301730296377, 0.051877417457489632, 0.049619450632056111,
      0.04735722816098549, 0.045091702469833808, 0.042823822443248824,
      0.040554533069292777, 0.038284775087011433, 0.036015484637383549,
      0.033747592917727345, 0.031482025839705365, 0.0292197036910287,
      0.026961540800948015, 0.024708445209664257, 0.022461318341733962,
      0.020221054683592837, 0.017988541465291094, 0.015764658346517624,
      0.01355027710703972, 0.011346261341628763, 0.0091534661595732321,
      0.0069727378888622474, 0.00480491378513686, 0.0026508217454759659,
      0.00051128002712402636, -0.0016129030287784958, -0.003720929268376195,
      -0.0058120109911053352, -0.00788537121047223, -0.0099402439095127582,
      -0.011975874290860639, -0.013991519021382758, -0.015986446471278292,
      -0.017959936947611849, -0.019911282922196159, -0.021839789253774868,
      -0.023744773404450553, -0.025625565650297732, -0.027481509286109762,
      -0.029311960824235667, -0.031116290187449394, -0.032893880895815665,
      -0.034644130247502306, -0.036366449493501707, -0.038060264006225232,
      -0.039725013441931328, -0.041360151896948832, -0.042965148057679967,
      -0.044539485344338083, -0.046082662048395631, -0.047594191463735606,
      -0.049073602011455129, -0.0505204373583314, -0.051934256528911239,
      -0.053314634011219941, -0.0546611598560772, -0.055973439770004657,
      -0.057251095201718817, -0.058493763422217356, -0.0597010975984248,
      -0.060872766860430583, -0.062008456362306133, -0.063107867336495871,
      -0.064170717141809538, -0.065196739305006773, -0.066185683555987515,
      -0.067137315856612062, -0.068051418423156235, -0.068927789742416368,
      -0.069766244581498452, -0.070566613991294, -0.071328745303684618,
      -0.07205250212249191, -0.0727377643082003, -0.073384427956486073,
      -0.073992405370599978, -0.074561625027596043, -0.075092031538499027,
      -0.075583585602407757, -0.076036263954591246, -0.076450059308625487,
      -0.076824980292598433, -0.077161051379456336, -0.077458312811512831,
      -0.077716820519190641, -0.077936646034043322, -0.078117876396109759,
      -0.078260614055657624, -0.07836497676938195, -0.078431097491108784,
      -0.078459124257067137, -0.078449220065808262, -0.078401562752811738,
      -0.078316344859870449, -0.078193773499304411, -0.07803407021309057,
      -0.077837470826960936, -0.077604225299563581, -0.0773345975667461,
      -0.077028865381045544, -0.076687320146462692, -0.076310266748596756,
      -0.075898023380223334, -0.075450921362398879, -0.074969304961173558,
      -0.0744535312000024, -0.0739039696679298, -0.073321002323649492,
      -0.0727050232955177, -0.0720564386776082, -0.071375666321918191,
      -0.0706631356267882, -0.069919287321656309, -0.069144573248220945,
      -0.068339456138124408, -0.0675044093872329, -0.066639916826632062,
      -0.065746472490419941, -0.0648245803803989, -0.063874754227777039,
      -0.06289751725196166, -0.061893401916559163, -0.06086294968267484,
      -0.059806710759626923, -0.058725243853151747, -0.057619115911243794,
      -0.056488901867694633, -0.0553351843834577, -0.054158553585933293,
      -0.052959606806296612, -0.051738948314947589, -0.050497189055209717,
      -0.049234946375375621, -0.04795284375920808, -0.046651510554999651,
      -0.045331581703304938, -0.043993697463443442, -0.042638503138889207,
      -0.041266648801642269, -0.039878789015710361, -0.038475582559780376,
      -0.037057692149210814, -0.0356257841574315, -0.034180528336883877,
      -0.032722597539577992, -0.031252667437397408, -0.029771416242242107,
      -0.028279524426122863, -0.026777674441318507, -0.02526655044069016,
      -0.023746837998253043, -0.022219223830135758, -0.020684395515997721,
      -0.019143041221041539, -0.017595849418693108, -0.016043508614069994,
      -0.014486707068341506, -0.012926132524060078, -0.011362471931598978,
      -0.0097964111767638133, -0.00822863480969658, -0.0066598257751525163,
      -0.0050906651442814014, -0.0035218318479622104, -0.0019540024118327231,
      -0.0003878506930662072, 0.0011759523809658536, 0.0027367390720890285,
      0.0042938450886722025, 0.0058466098408360874, 0.0073943766934198747,
      0.0089364932166553276, 0.010472311434412671, 0.012001188069966466,
      0.013522484789180252, 0.015035568441041839, 0.016539811295433721,
      0.01803459127809591, 0.019519292202672373, 0.020993303999782907,
      0.02245602294301972, 0.02390685187181615, 0.025345200411089459,
      0.026770485187606149, 0.028182130042980678, 0.029579566243249925,
      0.030962232684936114, 0.032329576097554144, 0.0336810512424717,
      0.035016121108081624, 0.036334257101205941, 0.037634939234673079,
      0.038917656311014737, 0.040181906102220721, 0.041427195525483781,
      0.042653040814905674, 0.043858967689075268, 0.045044511514500632,
      0.046209217464821539, 0.047352640675762343, 0.0484743463957779,
      0.049573910132352544, 0.050650917793892108, 0.051704965827187963,
      0.052735661350398214, 0.053742622281508015, 0.054725477462250073,
      0.055683866777422188, 0.056617441269595753, 0.057525863249164429,
      0.058408806399714144, 0.059265955878681449, 0.060097008413285274,
      0.06090167239168677, 0.061679667949374975, 0.062430727050754205,
      0.063154593565894049, 0.063851023342470378, 0.064519784272823275,
      0.065160656356172131, 0.065773431755939138, 0.06635791485219901,
      0.066913922289219038, 0.067441283018114445, 0.0679398383345907,
      0.068409441911780527, 0.068849959828177154, 0.06926127059065125,
      0.0696432651525816, 0.069995846927077929, 0.07031893179531247,
      0.070612448109970152, 0.0708763366938249, 0.071110550833466471,
      0.071315056268160648, 0.071489831173900079, 0.071634866142619727,
      0.0717501641566387, 0.071835740558304634, 0.071891623014916473,
      0.07191785147888112, 0.071914478143207686, 0.071881567392294565,
      0.071819195748085665, 0.071727451811617965, 0.071606436199970966,
      0.071456261478674052, 0.07127705208960837, 0.071068944274421286,
      0.070832085993498772, 0.070566636840566577, 0.070272767952906143,
      0.069950661917268342, 0.069600512671535747, 0.069222525402122537,
      0.068816916437256029, 0.068383913136078237, 0.067923753773720563,
      0.067436687422308073, 0.066922973828047627, 0.066382883284343358,
      0.065816696501104957, 0.0652247044702225, 0.064607208327302129,
      0.063964519209728524, 0.063296958111092025, 0.062604855732061676,
      0.061888552327761352, 0.061148397551705085, 0.060384750296375148,
      0.059597978530477956, 0.058788459133009417, 0.057956577724092094,
      0.057102728492788309, 0.056227314021820726, 0.055330745109402057,
      0.054413440588125223, 0.053475827141113166, 0.052518339115373312,
      0.051541418332539279, 0.050545513897009821, 0.04953108200159468,
      0.04849858573073481, 0.047448494861373404, 0.046381285661549441,
      0.045297440686823807, 0.044197448574584165, 0.043081803836318079,
      0.0419510066479612, 0.040805562638361506, 0.039645982675979984,
      0.038472782653898308, 0.037286483273174693, 0.036087609824746437,
      0.034876691969800346, 0.033654263518871907, 0.032420862209595863,
      0.031177029483326534, 0.02992331026061245, 0.028660252715699552,
      0.027388408050069819, 0.026108330265157423, 0.024820575934305995,
      0.023525703974045839, 0.022224275414822105, 0.020916853171190505,
      0.019604001811636421, 0.018286287328057683, 0.01696427690501897,
      0.0156385386888739, 0.014309641556808078, 0.012978154885930078,
      0.011644648322459605, 0.010309691551147433, 0.0089738540649453649,
      0.0076377049350905861, 0.0063018125816204458, 0.0049667445444540638,
      0.0036330672550915974, 0.0023013458090419435, 0.000972143739049241,
      -0.00035397721079797207, -0.0016764573099908022, -0.0029947390654596487,
      -0.0043082674443052247, -0.0056164900953239137, -0.0069188575692020228,
      -0.0082148235373689787, -0.0095038450093484737, -0.010785382548603482,
      -0.012058900486748098, -0.013323867136045543, -0.014579755000158921,
      -0.015826040983017136, -0.01706220659577945, -0.01828773816177123,
      -0.019502127019361333, -0.020704869722660061, -0.021895468240012907,
      -0.023073430150184818, -0.024238268836171278, -0.025389503676587537,
      -0.026526660234512337, -0.027649270443794734, -0.02875687279268441,
      -0.029849012504771032, -0.030925241717127613, -0.031985119655647674,
      -0.033028212807419237, -0.034054095090198716, -0.035062348018820765,
      -0.036052560868522363, -0.037024330835142581, -0.037977263192098307,
      -0.038910971444113804, -0.039825077477647075, -0.040719211707923107,
      -0.0415930132225764, -0.042446129921812792, -0.043278218655047551,
      -0.044088945353978448, -0.04487798516206256, -0.045645022560294811,
      -0.046389751489326711, -0.047111875467793073, -0.047811107706895631,
      -0.048487171221105754, -0.049139798935057336, -0.049768733786476928,
      -0.050373728825212558, -0.050954547308273493, -0.05151096279085296,
      -0.052042759213325691, -0.052549730984157647, -0.053031683058738573,
      -0.053488431014061547, -0.053919801119272526, -0.054325630402037514,
      -0.054705766710689843, -0.055060068772213949, -0.055388406245905172,
      -0.055690659772862805, -0.055966721021132322, -0.056216492726613658,
      -0.056439888729629975, -0.056636834007215774, -0.056807264701040472,
      -0.056951128141039122, -0.057068382864672758, -0.057158998631863224,
      -0.057222956435561315, -0.057260248507974836, -0.057270878322434118,
      -0.057254860590911193, -0.057212221257183775, -0.057142997485651228,
      -0.057047237645819954, -0.056925001292431776, -0.056776359141278973,
      -0.056601393040716312, -0.056400195938829278, -0.0561728718463562,
      -0.055919535795286683, -0.055640313793234468, -0.055335342773543142,
      -0.055004770541179367, -0.054648755714405146, -0.054267467662290347,
      -0.053861086438036589, -0.053429802708192045, -0.052973817677741973,
      -0.052493343011122288, -0.051988600749186979, -0.051459823222147219,
      -0.050907252958526751, -0.050331142590158057, -0.049731754753266043,
      -0.049109361985662077, -0.048464246620089059, -0.04779670067377096,
      -0.047107025734181386, -0.046395532841102594, -0.045662542364986916,
      -0.044908383881700424, -0.044133396043650006, -0.043337926447389749,
      -0.042522331497716372, -0.041686976268321081, -0.040832234359049049,
      -0.039958487749806343, -0.039066126651179769, -0.038155549351822186,
      -0.037227162062648242, -0.036281378757910356, -0.035318621013206236,
      -0.034339317840469667, -0.03334390552002256, -0.032332827429728241,
      -0.031306533871321471, -0.030265481893981989, -0.029210135115183236,
      -0.028140963538938826, -0.027058443371445744, -0.025963056834247794,
      -0.024855291974952787, -0.023735642475580465, -0.022604607458619076,
      -0.021462691290840295, -0.020310403384971261, -0.019148257999274703,
      -0.017976774035109624, -0.016796474832561067, -0.015607887964192359,
      -0.014411545027015466, -0.013207981432740079, -0.011997736196373895,
      -0.010781351723277377, -0.0095593735947031022, -0.0083323503519456,
      -0.0071008332791595965, -0.0058653761849025805, -0.004626535182533,
      -0.0033848684694820575, -0.0021409361055326091, -0.00089529979016165356,
      0.00035147736099301954, 0.0015988310404134592, 0.0028461959736847484,
      0.0040930061451007185, 0.0053386950237716948, 0.0065826957902088666,
      0.0078244415632488587, 0.0090633656272702829, 0.010298901659612943,
      0.011530483958104028, 0.012757547668624983, 0.013979529012629898,
      0.015195865514513412, 0.016405996228798708, 0.017609361966984559,
      0.018805405524047893, 0.019993571904460682, 0.021173308547655346,
      0.022344065552887444, 0.0235052959033514, 0.024656455689527335,
      0.025797004331648284, 0.026926404801182077, 0.028044123841316996,
      0.029149632186274858, 0.030242404779480727, 0.031321920990387025,
      0.0323876648299772, 0.033439125164809257, 0.034475795929535744,
      0.035497176337823635, 0.036502771091600744, 0.037492090588516117,
      0.038464651127606934, 0.039419975113002312, 0.040357591255682695,
      0.0412770347731424, 0.042177847586912315, 0.043059578517891182,
      0.043921783479362632, 0.044764025667642607, 0.045585875750339566,
      0.046386912052028877, 0.047166720737438231, 0.047924895991905705,
      0.048661040199164805, 0.049374764116341847, 0.050065687046076737,
      0.050733437005741393, 0.051377650893673792, 0.0519979746523361,
      0.052594063428399264, 0.053165581729601452, 0.053712203578410445,
      0.054233612662356739, 0.054729502481006158, 0.05519957648954029,
      0.055643548238817661, 0.056061141511943441, 0.056452090457220196,
      0.056816139717452752, 0.057153044555599455, 0.057462570976599743,
      0.057744495845483773, 0.057998607001569495, 0.05822470336878724,
      0.058422595062067859, 0.058592103489724837, 0.058733061451793377,
      0.058845313234327318, 0.058928714699525812, 0.058983133371742928,
      0.059008448519262763, 0.059004551231863274, 0.058971344494086593,
      0.058908743254196594, 0.058816674488818742, 0.058695077263161276,
      0.058543902786878536, 0.058363114465453142, 0.05815268794712735,
      0.057912611165368777, 0.057642884376776074, 0.057343520194471614,
      0.057014543616929057, 0.056655992052203244, 0.0562679153375771,
      0.0558503757545739, 0.055403448039334696, 0.054927219388350768,
      0.054421789459526949, 0.0538872703685686, 0.053323786680690717,
      0.052731475397612748, 0.052110485939886278, 0.051460980124467169,
      0.050783132137638118, 0.0500771285031605, 0.049343168045742854,
      0.048581461849808646, 0.047792233213512308, 0.046975717598097405,
      0.046132162572518835, 0.045261827753388321, 0.044364984740234419,
      0.043441917046085736, 0.042492920023394054, 0.041518300785306723,
      0.040518378122309781, 0.039493482414247646, 0.038443955537763079,
      0.03737015076912361, 0.036272432682533294, 0.03515117704387,
      0.034006770699954392, 0.032839611463288954, 0.031650107992390285,
      0.03043867966764785, 0.029205756462818352, 0.02795177881215094,
      0.02667719747316891, 0.025382473385167907, 0.024068077523451147,
      0.022734490749349329, 0.021382203656053939, 0.020011716410311946,
      0.018623538590030714, 0.017218189017819845, 0.015796195590537548,
      0.014358095104860889, 0.012904433078964286, 0.011435763570315888,
      0.0099526489896837184, 0.0084556599113578337, 0.0069453748796966929,
      0.0054223802119954126, 0.0038872697977910663, 0.0023406448946056949,
      0.0007831139202318484, -0.00078470775840678957, -0.0023621980397378578,
      -0.0039487283053275622, -0.0055436636408806427, -0.0071463630604042469,
      -0.0087561797334740812, -0.010372461215515581, -0.011994549681045588,
      -0.013621782159809722, -0.015253490775710744, -0.016889002988513063,
      -0.0185276418381926, -0.020168726191888173, -0.021811570993373813,
      -0.023455487514979122, -0.025099783611850272, -0.026743763978541498,
      -0.028386730407761969, -0.030027982051293537, -0.031666815682923038,
      -0.033302525963346472, -0.034934405706961408, -0.036561746150440382,
      -0.038183837223024375, -0.039799967818433916, -0.041409426068324283,
      -0.04301149961718545, -0.044605475898610962, -0.046190642412840793,
      -0.047766287005485353, -0.049331698147340425, -0.050886165215220332,
      -0.052428978773694034, -0.053959430857647719, -0.055476815255575851,
      -0.05698042779349706, -0.058469566619444593, -0.059943532488369089,
      -0.061401629047419026, -0.0628431631214896, -0.064267444998908685,
      -0.065673788717226761, -0.067061512348954744, -0.068429938287201356,
      -0.069778393531089042, -0.071106209970844117, -0.072412724672503148,
      -0.073697280162077619, -0.074959224709159666, -0.076197912609792,
      -0.0774127044685506, -0.07860296747974535, -0.0797680757076233,
      -0.080907410365458718, -0.0820203600935146, -0.083106321235656241,
      -0.084164698114637782, -0.085194903305887984, -0.086196357909708088,
      -0.08716849182185199, -0.088110744002276462, -0.089022562742086267,
      -0.089903405928484975, -0.090752741307682766, -0.091570046745668418,
      -0.092354810486720423, -0.093106531409599291, -0.093824719281295516,
      -0.094508895008251437, -0.095158590884981575, -0.095773350839963883,
      -0.096352730678748513, -0.0968962983241586, -0.097403634053502219,
      -0.097874330732740558, -0.098307994047443975, -0.098704242730549716,
      -0.099062708786739367, -0.099383037713392977, -0.099664888718055816,
      -0.099907934932270445, -0.10011186362173946, -0.10027637639273138,
      -0.10040118939459933, -0.1004860335184052, -0.10053065459150073,
      -0.10053481356800557, -0.10049828671514927, -0.10042086579530532,
      -0.10030235824373966, -0.10014258734192472, -0.099941392386364167,
      -0.099698628852893156, -0.0994141685563153, -0.099087899805349627,
      -0.098719727552822281, -0.09830957354096298, -0.097857376441871952,
      -0.097363091992932874, -0.09682669312723928, -0.096248170098882341,
      -0.095627530603078478, -0.094964799891077173, -0.094260020879760112,
      -0.093513254255911671, -0.092724578575067648, -0.091894090354900967,
      -0.091021904163105918, -0.090108152699707358, -0.089152986873733728,
      -0.088156575874254864, -0.0871191072356592, -0.086040786897213561,
      -0.0849218392567625, -0.083762507218628074, -0.082563052235575224,
      -0.081323754344855087, -0.080044912198290838, -0.0787268430863293,
      -0.077369882956065839, -0.075974386423190821, -0.0745407267778164,
      -0.073069295984178384, -0.071560504674165984, -0.070014782134648568,
      -0.068432576288611241, -0.066814353670013968, -0.065160599392440427,
      -0.063471817111409784, -0.061748528980438207, -0.059991275600766433,
      -0.058200615964767784, -0.056377127393021233, -0.054521405465040675,
      -0.052634063943635116, -0.050715734692936436, -0.0487670675900356,
      -0.046788730430279805, -0.044781408826180515, -0.042745806099975733,
      -0.040682643169821495, -0.038592658429636953, -0.036476607622605309,
      -0.034335263708323849, -0.032169416723648196, -0.029979873637211118,
      -0.027767458197659863, -0.025533010775595593, -0.023277388199279984,
      -0.021001463584081646, -0.018706126155722067, -0.016392281067335548,
      -0.01406084921035345, -0.01171276701928174, -0.0093489862703506864,
      -0.0069704738741246768, -0.0045782116620618043, -0.0021731961670850282,
      0.00024356160179225556, 0.0026710363907712286, 0.0051081889384246111,
      0.0075539662186969846, 0.010007301689667599, 0.012467115548053449,
      0.014932314989390405, 0.017401794473825463, 0.019874435997510403,
      0.022349109369475383, 0.02482467249398803, 0.027299971658286713,
      0.029773841825668442, 0.032245106933823584, 0.034712580198399151,
      0.03717506442167777, 0.039631352306336028, 0.042080226774196247,
      0.044520461289896812, 0.0469508201894162, 0.049370059013362153,
      0.051776924844962213, 0.054170156652654983, 0.0565484856372244,
      0.05891063558337778, 0.0612553232156795, 0.063581258558773182,
      0.065887145301778832, 0.068171681166798989, 0.070433558281414774,
      0.072671463555118526, 0.074884079059535244, 0.077070082412390828,
      0.0792281471650907, 0.081356943193818948, 0.083455137094084322,
      0.085521392578556538, 0.087554370878142149, 0.08955273114616974,
      0.091515130865574834, 0.09344022625899305, 0.095326672701640858,
      0.097173125136867086, 0.098978238494290716, 0.10074066811037695,
      0.10245907015136929, 0.10413210203844127, 0.10575842287494977,
      0.10733669387570834, 0.10886557879810256, 0.11034374437498869,
      0.11176986074921082, 0.1131426019096286, 0.11446064612855877,
      0.11572267640044924, 0.11692738088173353, 0.11807345333167618,
      0.11915959355411572, 0.12018450783998637, 0.1211469094104646,
      0.12204551886062145, 0.12287906460347681, 0.12364628331427559,
      0.12434592037491354, 0.12497673031832517, 0.12553747727275974,
      0.12602693540575874, 0.12644388936773543, 0.12678713473502992,
      0.1270554784522705, 0.12724773927393887, 0.12736274820501164,
      0.12739934894049182, 0.1273563983037759, 0.1272327666836483,
      0.12702733846979397, 0.12673901248674352, 0.12636670242599862,
      0.12590933727635181, 0.12536586175212536, 0.12473523671929115,
      0.12401643961929298, 0.12320846489044653, 0.12231032438677512,
      0.12132104779416537, 0.12023968304366776, 0.11906529672187964,
      0.11779697447817583, 0.11643382142876545, 0.11497496255734202,
      0.11341954311225345, 0.11176672900005491, 0.11001570717527179,
      0.10816568602630502, 0.10621589575728604, 0.10416558876578332,
      0.10201404001623562, 0.099760547408971473, 0.097404432144667735,
      0.09494503908417086, 0.092381737103496273, 0.089713919443925622,
      0.086941004057051616, 0.084062433944638332, 0.081077677493228223,
      0.0779862288032772, 0.074787608012816614, 0.071481361615402778,
      0.068067062772325368, 0.064544311618925113, 0.060912735564863624,
      0.057171989588329822, 0.053321756523956453, 0.049361747344388876,
      0.045291701435453052, 0.041111386864647367, 0.036820600643059594,
      0.032419168980418037, 0.027906947533283967, 0.02328382164624717,
      0.018549706586008997, 0.013704547768270429, 0.0087483209773268761,
      0.0036810325782426793, -0.0014972802784404202, -0.0067865494595915829,
      -0.012186675660086882, -0.017697528221115748, -0.02331894495642332,
      -0.029050731986422239, -0.034892663580406574, -0.040844482006814321,
      -0.046905897391742148, -0.05307658758569736, -0.059356198038713094,
      -0.065744341683895757, -0.072240598829459254, -0.078844517059341077,
      -0.08555561114244413, -0.092373362950600085, -0.099297221385278814,
      -0.10632660231315195, -0.11346088851053665, -0.12069942961678007,
      -0.12804154209666457, -0.13548650921184441, -0.14303358100142791,
      -0.15068197427165395, -0.15843087259484567, -0.16627942631752252,
      -0.17422675257787631, -0.18227193533250866, -0.19041402539256155,
      -0.19865204046923307, -0.20698496522868573, -0.21541175135646234,
      -0.22393131763132171, -0.2325425500086119, -0.24124430171313593,
      -0.25003539334156744, -0.25891461297443547, -0.26788071629763083,
      -0.27693242673354224, -0.28606843558171191, -0.29528740216915106,
      -0.30458795401016719, -0.31396868697583713, -0.32342816547305181,
      -0.33296492263309829, -0.34257746050988297, -0.3522642502876297,
      -0.36202373249820136, -0.37185431724787404, -0.38175438445365839,
      -0.39172228408911069, -0.40175633643954678, -0.41185483236675918,
      -0.42201603358304945, -0.43223817293470562, -0.44251945469472476,
      -0.45285805486489711, -0.46325212148706368, -0.47369977496364052,
      -0.48419910838722879, -0.49474818787938424, -0.50534505293837784,
      -0.51598771679600108, -0.52667416678325008, -0.53740236470492719,
      -0.54817024722300567, -0.55897572624876912, -0.56981668934357821,
      -0.58069100012828545, -0.59159649870110076, -0.6025310020639798,
      -0.61349230455728443, -0.62447817830280483, -0.63548637365489613,
      -0.6465146196597894, -0.65756062452284059, -0.668622076083753,
      -0.6796966422996, -0.69078197173554168, -0.70187569406321759,
      -0.712975420566577, -0.72407874465520283, -0.735183242384843,
      -0.74628647298520956, -0.75738597939478036, -0.76847928880259575,
      -0.77956391319689167, -0.79063734992040646, -0.80169708223232672,
      -0.81274057987664561, -0.82376529965690826, -0.83476868601710452,
      -0.84574817162867122, -0.85670117798342138, -0.86762511599223957,
      -0.87851738658948353, -0.88937538134284289, -0.90019648306863254,
      -0.91097806645223711, -0.9217174986736949, -0.93241214003816653,
      -0.943059344611187, -0.95365646085856459, -0.96420083229067255,
      -0.97468979811114209, -0.98512069386959411, -0.99549085211846133,
      -1.0057976030735374, -1.0160382752782322, -1.0262101962713284,
      -1.0363106932579953, -1.0463370937840257, -1.0562867264129987,
      -1.0661569214062807, -1.0759450114056366, -1.0856483321183168,
      -1.0952642230044027, -1.1047900279662675, -1.1142230960399586,
      -1.123560782088302, -1.1328004474955986, -1.1419394608636391,
      -1.1509751987089865, -1.1599050461611771, -1.1687263976618236,
      -1.1774366576642836, -1.1860332413337937, -1.1945135752478937,
      -1.2028750980968357, -1.2111152613839606, -1.2192315301256742,
      -1.2272213835509689, -1.2350823158002202, -1.2428118366230845,
      -1.2504074720753406, -1.2578667652144011, -1.2651872767933863,
      -1.2723665859535094, -1.279402290914603, -1.2862920096635768,
      -1.2930333806406433, -1.299624063423044, -1.3060617394061891,
      -1.3123441124819129, -1.3184689097137074, -1.324433882008734,
      -1.3302368047863737, -1.335875478643211, -1.3413477300141459,
      -1.3466514118295341, -1.3517844041681115, -1.3567446149055074,
      -1.361529980358211, -1.3661384659227045, -1.3705680667096529,
      -1.3748168081729355, -1.3788827467333029, -1.3827639703965087,
      -1.3864585993657057, -1.3899647866479152, -1.3932807186544085,
      -1.3964046157947783, -1.3993347330645551, -1.4020693606261565,
      -1.4046068243829839, -1.4069454865465325 } ;

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
    result = hil_set_card_specific_options(DATA_COLLECTION_DW.HILInitialize_Card,
      " ", 2);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(DATA_COLLECTION_M, _rt_error_message);
      return;
    }

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

  rtmSetTFinal(DATA_COLLECTION_M, 26.0);
  DATA_COLLECTION_M->Timing.stepSize0 = 0.01;

  /* External mode info */
  DATA_COLLECTION_M->Sizes.checksums[0] = (2046208367U);
  DATA_COLLECTION_M->Sizes.checksums[1] = (4212344650U);
  DATA_COLLECTION_M->Sizes.checksums[2] = (1544226929U);
  DATA_COLLECTION_M->Sizes.checksums[3] = (1435153757U);

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
