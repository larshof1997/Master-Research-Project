/*
 * TRACKING_CONTROL_KPES.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "TRACKING_CONTROL_KPES".
 *
 * Model version              : 1.148
 * Simulink Coder version : 9.0 (R2018b) 24-May-2018
 * C source code generated on : Mon Mar  9 11:36:23 2026
 *
 * Target selection: quarc_windows.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "TRACKING_CONTROL_KPES.h"
#include "TRACKING_CONTROL_KPES_private.h"
#include "TRACKING_CONTROL_KPES_dt.h"

/* Block signals (default storage) */
B_TRACKING_CONTROL_KPES_T TRACKING_CONTROL_KPES_B;

/* Block states (default storage) */
DW_TRACKING_CONTROL_KPES_T TRACKING_CONTROL_KPES_DW;

/* Real-time model */
RT_MODEL_TRACKING_CONTROL_KPE_T TRACKING_CONTROL_KPES_M_;
RT_MODEL_TRACKING_CONTROL_KPE_T *const TRACKING_CONTROL_KPES_M =
  &TRACKING_CONTROL_KPES_M_;

/* Forward declaration for local functions */
static void TRACKING_CONTROL_K_loc_sym_sqrt(const real_T A[4], real_T Asqrt[4]);
static void TRACKING_CONTRO_loc_sylvester22(const real_T A[4], const real_T B[4],
  const real_T C[4], real_T X[4]);

/* Function for MATLAB Function: '<Root>/MATLAB Function' */
static void TRACKING_CONTROL_K_loc_sym_sqrt(const real_T A[4], real_T Asqrt[4])
{
  real_T tr;
  real_T disc;
  real_T sq;
  real_T n2;
  real_T v1_idx_0;
  real_T v1_idx_1;
  real_T v2_idx_0;
  real_T v2_idx_1;

  /* '<S3>:1:196' */
  /* '<S3>:1:197' */
  tr = A[0] + A[3];

  /* '<S3>:1:198' */
  /* '<S3>:1:199' */
  disc = tr * tr - (A[0] * A[3] - A[2] * A[2]) * 4.0;
  if (disc < 0.0) {
    /* '<S3>:1:200' */
    /* '<S3>:1:201' */
    disc = 0.0;
  }

  /* '<S3>:1:203' */
  sq = sqrt(disc);

  /* '<S3>:1:204' */
  disc = (tr + sq) * 0.5;

  /* '<S3>:1:205' */
  tr = (tr - sq) * 0.5;
  if (disc < 1.0E-12) {
    /* '<S3>:1:206' */
    disc = 1.0E-12;
  }

  if (tr < 1.0E-12) {
    /* '<S3>:1:207' */
    tr = 1.0E-12;
  }

  if (fabs(A[2]) > 1.0E-14) {
    /* '<S3>:1:211' */
    /* '<S3>:1:212' */
    v1_idx_0 = disc - A[3];

    /* '<S3>:1:212' */
    v1_idx_1 = A[2];

    /* '<S3>:1:213' */
    v2_idx_0 = tr - A[3];

    /* '<S3>:1:213' */
    v2_idx_1 = A[2];
  } else if (A[0] >= A[3]) {
    /* '<S3>:1:214' */
    /* '<S3>:1:215' */
    v1_idx_0 = 1.0;

    /* '<S3>:1:215' */
    v1_idx_1 = 0.0;

    /* '<S3>:1:216' */
    v2_idx_0 = 0.0;

    /* '<S3>:1:216' */
    v2_idx_1 = 1.0;
  } else {
    /* '<S3>:1:218' */
    v1_idx_0 = 0.0;

    /* '<S3>:1:218' */
    v1_idx_1 = 1.0;

    /* '<S3>:1:219' */
    v2_idx_0 = 1.0;

    /* '<S3>:1:219' */
    v2_idx_1 = 0.0;
  }

  /* '<S3>:1:221' */
  sq = sqrt(v1_idx_0 * v1_idx_0 + v1_idx_1 * v1_idx_1);

  /* '<S3>:1:222' */
  n2 = sqrt(v2_idx_0 * v2_idx_0 + v2_idx_1 * v2_idx_1);

  /* '<S3>:1:223' */
  v1_idx_0 /= sq;

  /* '<S3>:1:223' */
  v1_idx_1 /= sq;

  /* '<S3>:1:224' */
  v2_idx_0 /= n2;

  /* '<S3>:1:224' */
  v2_idx_1 /= n2;

  /* '<S3>:1:225' */
  disc = sqrt(disc);

  /* '<S3>:1:226' */
  tr = sqrt(tr);

  /* '<S3>:1:227' */
  Asqrt[0] = v1_idx_0 * v1_idx_0 * disc + v2_idx_0 * v2_idx_0 * tr;
  Asqrt[2] = v1_idx_0 * v1_idx_1 * disc + v2_idx_0 * v2_idx_1 * tr;
  Asqrt[1] = v1_idx_1 * v1_idx_0 * disc + v2_idx_1 * v2_idx_0 * tr;
  Asqrt[3] = v1_idx_1 * v1_idx_1 * disc + v2_idx_1 * v2_idx_1 * tr;
}

/* Function for MATLAB Function: '<Root>/MATLAB Function' */
static void TRACKING_CONTRO_loc_sylvester22(const real_T A[4], const real_T B[4],
  const real_T C[4], real_T X[4])
{
  real_T Ab[20];
  real_T maxVal;
  int32_T maxRow;
  int32_T col;
  int32_T b_row;
  int32_T b_c;
  real_T x4_idx_2;
  real_T x4_idx_1;
  int32_T maxVal_tmp;
  int32_T maxVal_tmp_0;
  int32_T Ab_tmp;

  /* '<S3>:1:232' */
  /* '<S3>:1:234' */
  /* '<S3>:1:235' */
  /* '<S3>:1:236' */
  /* '<S3>:1:237' */
  /* '<S3>:1:238' */
  /* '<S3>:1:239' */
  /* '<S3>:1:245' */
  Ab[0] = A[0] + B[0];

  /* '<S3>:1:245' */
  Ab[4] = A[2];

  /* '<S3>:1:245' */
  Ab[8] = B[1];

  /* '<S3>:1:245' */
  Ab[12] = 0.0;

  /* '<S3>:1:245' */
  Ab[16] = C[0];

  /* '<S3>:1:246' */
  Ab[1] = A[1];

  /* '<S3>:1:246' */
  Ab[5] = A[3] + B[0];

  /* '<S3>:1:246' */
  Ab[9] = 0.0;

  /* '<S3>:1:246' */
  Ab[13] = B[1];

  /* '<S3>:1:246' */
  Ab[17] = C[1];

  /* '<S3>:1:247' */
  Ab[2] = B[2];

  /* '<S3>:1:247' */
  Ab[6] = 0.0;

  /* '<S3>:1:247' */
  Ab[10] = A[0] + B[3];

  /* '<S3>:1:247' */
  Ab[14] = A[2];

  /* '<S3>:1:247' */
  Ab[18] = C[2];

  /* '<S3>:1:248' */
  Ab[3] = 0.0;

  /* '<S3>:1:248' */
  Ab[7] = B[2];

  /* '<S3>:1:248' */
  Ab[11] = A[1];

  /* '<S3>:1:248' */
  Ab[15] = A[3] + B[3];

  /* '<S3>:1:248' */
  Ab[19] = C[3];

  /* '<S3>:1:249' */
  for (col = 0; col < 3; col++) {
    /* '<S3>:1:249' */
    /* '<S3>:1:250' */
    maxVal_tmp = col << 2;
    maxVal_tmp_0 = maxVal_tmp + col;
    maxVal = fabs(Ab[maxVal_tmp_0]);

    /* '<S3>:1:251' */
    maxRow = col;

    /* '<S3>:1:252' */
    for (b_row = 0; b_row <= 2 - col; b_row++) {
      /* '<S3>:1:252' */
      b_c = (col + b_row) + 1;
      x4_idx_2 = fabs(Ab[maxVal_tmp + b_c]);
      if (x4_idx_2 > maxVal) {
        /* '<S3>:1:253' */
        /* '<S3>:1:254' */
        maxVal = x4_idx_2;

        /* '<S3>:1:255' */
        maxRow = b_c;
      }
    }

    if (maxRow != col) {
      /* '<S3>:1:258' */
      /* '<S3>:1:259' */
      for (b_c = 0; b_c < 5; b_c++) {
        /* '<S3>:1:259' */
        /* '<S3>:1:260' */
        b_row = b_c << 2;
        maxVal = Ab[b_row + col];

        /* '<S3>:1:261' */
        Ab[col + b_row] = Ab[b_row + maxRow];

        /* '<S3>:1:262' */
        Ab[maxRow + b_row] = maxVal;
      }
    }

    /* '<S3>:1:265' */
    for (maxRow = 0; maxRow <= 2 - col; maxRow++) {
      /* '<S3>:1:265' */
      b_c = (col + maxRow) + 1;

      /* '<S3>:1:266' */
      maxVal = Ab[maxVal_tmp + b_c] / Ab[maxVal_tmp_0];

      /* '<S3>:1:267' */
      for (b_row = 0; b_row <= 4 - col; b_row++) {
        /* '<S3>:1:267' */
        /* '<S3>:1:268' */
        Ab_tmp = (col + b_row) << 2;
        Ab[b_c + Ab_tmp] -= Ab[Ab_tmp + col] * maxVal;
      }
    }
  }

  /* '<S3>:1:273' */
  maxVal = Ab[19] / Ab[15];

  /* '<S3>:1:274' */
  x4_idx_2 = (Ab[18] - Ab[14] * maxVal) / Ab[10];

  /* '<S3>:1:275' */
  x4_idx_1 = ((Ab[17] - Ab[9] * x4_idx_2) - Ab[13] * maxVal) / Ab[5];

  /* '<S3>:1:276' */
  /* '<S3>:1:240' */
  X[0] = (((Ab[16] - Ab[4] * x4_idx_1) - Ab[8] * x4_idx_2) - Ab[12] * maxVal) /
    Ab[0];
  X[2] = x4_idx_2;
  X[1] = x4_idx_1;
  X[3] = maxVal;
}

/* Model output function */
void TRACKING_CONTROL_KPES_output(void)
{
  /* local block i/o variables */
  real_T rtb_FromWorkspace1[2];
  real_T rtb_FromWorkspace2[2];
  real_T rtb_PulseGenerator;
  boolean_T rtb_HILReadDigital_o1;
  boolean_T rtb_HILReadDigital_o2;
  boolean_T rtb_HILReadDigital_o3;
  boolean_T rtb_HILReadDigital_o4;
  real_T phi;
  real_T M[4];
  real_T T[4];
  real_T Ti[4];
  real_T dTi_dq2[4];
  int32_T jumpCount;
  real_T c2;
  real_T P11;
  real_T P12;
  real_T P22;
  real_T rtb_ManualSwitch1;
  real_T rtb_ManualSwitch2;
  real_T M_tmp[4];
  real_T S2_tmp[4];
  real_T T_0[4];
  real_T M_tmp_0[4];
  real_T T_1[4];
  int32_T i;
  real_T qd_c_idx_0;
  real_T dqd_c_idx_1;
  real_T ddqd_c_idx_1;
  real_T xp_idx_0;
  real_T xp_idx_1;
  real_T phat_idx_0;
  real_T phat_idx_1;
  real_T col2_1_idx_0;
  real_T col2_1_idx_1;
  real_T pd_idx_1;
  real_T M_tmp_1;
  int32_T M_tmp_tmp;
  real_T qd_c_idx_1_tmp;
  real_T P11_tmp;
  real_T P22_tmp;

  /* S-Function (hil_read_encoder_block): '<Root>/HIL Read Encoder' */

  /* S-Function Block: TRACKING_CONTROL_KPES/HIL Read Encoder (hil_read_encoder_block) */
  {
    t_error result = hil_read_encoder
      (TRACKING_CONTROL_KPES_DW.HILInitialize_Card,
       TRACKING_CONTROL_KPES_P.HILReadEncoder_channels, 2,
       &TRACKING_CONTROL_KPES_DW.HILReadEncoder_Buffer[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(TRACKING_CONTROL_KPES_M, _rt_error_message);
    } else {
      rtb_ManualSwitch1 = TRACKING_CONTROL_KPES_DW.HILReadEncoder_Buffer[0];
      rtb_ManualSwitch2 = TRACKING_CONTROL_KPES_DW.HILReadEncoder_Buffer[1];
    }
  }

  /* UnaryMinus: '<Root>/Unary Minus' incorporates:
   *  Gain: '<Root>/Motor #1 Encoder Calib1'
   */
  TRACKING_CONTROL_KPES_B.UnaryMinus = -(TRACKING_CONTROL_KPES_P.KE_D1 *
    rtb_ManualSwitch1);

  /* UnitDelay: '<Root>/Unit Delay2' */
  TRACKING_CONTROL_KPES_B.UnitDelay2 =
    TRACKING_CONTROL_KPES_DW.UnitDelay2_DSTATE;

  /* UnaryMinus: '<Root>/Unary Minus1' incorporates:
   *  Gain: '<Root>/Motor #2 Encoder Calib1'
   */
  TRACKING_CONTROL_KPES_B.UnaryMinus1 = -(TRACKING_CONTROL_KPES_P.KE_D2 *
    rtb_ManualSwitch2);

  /* UnitDelay: '<Root>/Unit Delay3' */
  TRACKING_CONTROL_KPES_B.UnitDelay3 =
    TRACKING_CONTROL_KPES_DW.UnitDelay3_DSTATE;

  /* FromWorkspace: '<Root>/From Workspace4' */
  {
    real_T *pDataValues = (real_T *)
      TRACKING_CONTROL_KPES_DW.FromWorkspace4_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      TRACKING_CONTROL_KPES_DW.FromWorkspace4_PWORK.TimePtr;
    int_T currTimeIndex =
      TRACKING_CONTROL_KPES_DW.FromWorkspace4_IWORK.PrevIndex;
    real_T t = TRACKING_CONTROL_KPES_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[3099]) {
      currTimeIndex = 3098;
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

    TRACKING_CONTROL_KPES_DW.FromWorkspace4_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&TRACKING_CONTROL_KPES_B.FromWorkspace4[0])[elIdx] =
                pDataValues[currTimeIndex];
              pDataValues += 3100;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&TRACKING_CONTROL_KPES_B.FromWorkspace4[0])[elIdx] =
                pDataValues[currTimeIndex + 1];
              pDataValues += 3100;
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
            (&TRACKING_CONTROL_KPES_B.FromWorkspace4[0])[elIdx] = (real_T)
              rtInterpolate(d1, d2, f1, f2);
            pDataValues += 3100;
          }
        }
      }
    }
  }

  /* FromWorkspace: '<Root>/From Workspace1' */
  {
    real_T *pDataValues = (real_T *)
      TRACKING_CONTROL_KPES_DW.FromWorkspace1_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      TRACKING_CONTROL_KPES_DW.FromWorkspace1_PWORK.TimePtr;
    int_T currTimeIndex =
      TRACKING_CONTROL_KPES_DW.FromWorkspace1_IWORK.PrevIndex;
    real_T t = TRACKING_CONTROL_KPES_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[3099]) {
      currTimeIndex = 3098;
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

    TRACKING_CONTROL_KPES_DW.FromWorkspace1_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&rtb_FromWorkspace1[0])[elIdx] = pDataValues[currTimeIndex];
              pDataValues += 3100;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&rtb_FromWorkspace1[0])[elIdx] = pDataValues[currTimeIndex + 1];
              pDataValues += 3100;
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
            (&rtb_FromWorkspace1[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1,
              f2);
            pDataValues += 3100;
          }
        }
      }
    }
  }

  /* FromWorkspace: '<Root>/From Workspace2' */
  {
    real_T *pDataValues = (real_T *)
      TRACKING_CONTROL_KPES_DW.FromWorkspace2_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      TRACKING_CONTROL_KPES_DW.FromWorkspace2_PWORK.TimePtr;
    int_T currTimeIndex =
      TRACKING_CONTROL_KPES_DW.FromWorkspace2_IWORK.PrevIndex;
    real_T t = TRACKING_CONTROL_KPES_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[3099]) {
      currTimeIndex = 3098;
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

    TRACKING_CONTROL_KPES_DW.FromWorkspace2_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&rtb_FromWorkspace2[0])[elIdx] = pDataValues[currTimeIndex];
              pDataValues += 3100;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&rtb_FromWorkspace2[0])[elIdx] = pDataValues[currTimeIndex + 1];
              pDataValues += 3100;
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
            (&rtb_FromWorkspace2[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1,
              f2);
            pDataValues += 3100;
          }
        }
      }
    }
  }

  /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<Root>/Constant1'
   *  Constant: '<Root>/Constant2'
   *  Constant: '<Root>/Constant3'
   *  Constant: '<Root>/Constant4'
   *  Constant: '<Root>/Constant5'
   *  Constant: '<Root>/Constant6'
   *  Constant: '<Root>/Constant7'
   *  Constant: '<Root>/Constant8'
   *  Constant: '<Root>/Constant9'
   *  SignalConversion: '<Root>/ConcatBufferAtVector Concatenate1In1'
   *  SignalConversion: '<Root>/ConcatBufferAtVector Concatenate1In2'
   *  UnitDelay: '<Root>/Unit Delay'
   *  UnitDelay: '<Root>/Unit Delay1'
   */
  /* MATLAB Function 'MATLAB Function': '<S3>:1' */
  /* '<S3>:1:156' */
  /* '<S3>:1:50' */
  /* '<S3>:1:51' */
  /* '<S3>:1:52' */
  /* '<S3>:1:53' */
  /* '<S3>:1:54' */
  xp_idx_0 = TRACKING_CONTROL_KPES_DW.UnitDelay_DSTATE[0];
  xp_idx_1 = TRACKING_CONTROL_KPES_DW.UnitDelay_DSTATE[1];

  /* '<S3>:1:55' */
  phi = TRACKING_CONTROL_KPES_DW.UnitDelay1_DSTATE;

  /* '<S3>:1:62' */
  /* '<S3>:1:177' */
  c2 = cos(TRACKING_CONTROL_KPES_B.UnaryMinus1);

  /* '<S3>:1:178' */
  M[0] = 2.0 * TRACKING_CONTROL_KPES_P.b_hat * c2 +
    (TRACKING_CONTROL_KPES_P.a1_hat + TRACKING_CONTROL_KPES_P.a2_hat);
  M_tmp_1 = TRACKING_CONTROL_KPES_P.b_hat * c2 + TRACKING_CONTROL_KPES_P.a2_hat;
  M[2] = M_tmp_1;
  M[1] = M_tmp_1;
  M[3] = TRACKING_CONTROL_KPES_P.a2_hat;

  /* '<S3>:1:63' */
  /* '<S3>:1:183' */
  /* '<S3>:1:184' */
  c2 = 1.0 / (M[0] * TRACKING_CONTROL_KPES_P.a2_hat - M_tmp_1 * M_tmp_1);

  /* '<S3>:1:185' */
  /* '<S3>:1:64' */
  Ti[0] = TRACKING_CONTROL_KPES_P.a2_hat * c2;
  Ti[2] = -M_tmp_1 * c2;
  Ti[1] = -M_tmp_1 * c2;
  Ti[3] = M[0] * c2;
  TRACKING_CONTROL_K_loc_sym_sqrt(Ti, T);

  /* '<S3>:1:65' */
  TRACKING_CONTROL_K_loc_sym_sqrt(M, Ti);

  /* '<S3>:1:67' */
  /* '<S3>:1:71' */
  c2 = sin(TRACKING_CONTROL_KPES_B.UnaryMinus1);

  /* '<S3>:1:72' */
  /* '<S3>:1:73' */
  T_0[0] = -2.0 * TRACKING_CONTROL_KPES_P.b_hat * c2;
  phat_idx_0 = -TRACKING_CONTROL_KPES_P.b_hat * c2;
  T_0[2] = phat_idx_0;
  T_0[1] = phat_idx_0;
  T_0[3] = 0.0;
  TRACKING_CONTRO_loc_sylvester22(Ti, Ti, T_0, dTi_dq2);

  /* '<S3>:1:76' */
  phat_idx_0 = TRACKING_CONTROL_KPES_DW.UnitDelay1_DSTATE *
    TRACKING_CONTROL_KPES_B.UnaryMinus +
    TRACKING_CONTROL_KPES_DW.UnitDelay_DSTATE[0];
  phat_idx_1 = TRACKING_CONTROL_KPES_DW.UnitDelay1_DSTATE *
    TRACKING_CONTROL_KPES_B.UnaryMinus1 +
    TRACKING_CONTROL_KPES_DW.UnitDelay_DSTATE[1];

  /* '<S3>:1:79' */
  /* '<S3>:1:282' */
  col2_1_idx_0 = dTi_dq2[0];
  col2_1_idx_1 = dTi_dq2[1];

  /* '<S3>:1:283' */
  /* '<S3>:1:284' */
  P12 = dTi_dq2[1] - dTi_dq2[1];

  /* '<S3>:1:285' */
  /* '<S3>:1:286' */
  /* '<S3>:1:288' */
  /* '<S3>:1:289' */
  M_tmp[0] = 0.0;
  M_tmp[2] = dTi_dq2[2];
  M_tmp[1] = 0.0;
  M_tmp[3] = dTi_dq2[3];

  /* '<S3>:1:290' */
  P22 = dTi_dq2[0];
  for (i = 0; i < 2; i++) {
    T_0[i] = 0.0;
    T_0[i] += T[i] * 0.0;
    c2 = T[i + 2];
    T_0[i] += c2 * P22;
    T_0[i + 2] = 0.0;
    T_0[i + 2] += (0.0 - P22) * T[i];
    T_0[i + 2] += c2 * P12;
    M[i] = 0.0;
    M[i] += T_0[i] * T[0];
    M_tmp_1 = T_0[i + 2];
    M[i] += M_tmp_1 * T[1];
    M_tmp_tmp = i << 1;
    M_tmp_0[M_tmp_tmp] = 0.0 - M_tmp[M_tmp_tmp];
    M[i + 2] = 0.0;
    M[i + 2] += T_0[i] * T[2];
    M[i + 2] += M_tmp_1 * T[3];
    M_tmp_0[1 + M_tmp_tmp] = M_tmp[i + 2] - M_tmp[M_tmp_tmp + 1];
  }

  for (i = 0; i < 2; i++) {
    T_0[i] = 0.0;
    T_0[i] += T[i] * M_tmp_0[0];
    c2 = T[i + 2];
    T_0[i] += c2 * M_tmp_0[1];
    T_0[i + 2] = 0.0;
    T_0[i + 2] += T[i] * M_tmp_0[2];
    T_0[i + 2] += c2 * M_tmp_0[3];
    S2_tmp[i] = 0.0;
    S2_tmp[i] += T_0[i] * T[0];
    P12 = T_0[i + 2];
    S2_tmp[i] += P12 * T[1];
    S2_tmp[i + 2] = 0.0;
    S2_tmp[i + 2] += T_0[i] * T[2];
    S2_tmp[i + 2] += P12 * T[3];
  }

  /* '<S3>:1:291' */
  /* '<S3>:1:292' */
  /* '<S3>:1:82' */
  /* '<S3>:1:83' */
  jumpCount = 0;

  /* '<S3>:1:84' */
  /* '<S3>:1:296' */
  P11 = TRACKING_CONTROL_KPES_DW.UnitDelay1_DSTATE * T[0] - (M[0] * phat_idx_0 +
    M[2] * phat_idx_1);

  /* '<S3>:1:297' */
  P12 = TRACKING_CONTROL_KPES_DW.UnitDelay1_DSTATE * T[2] - ((S2_tmp[0] *
    phat_idx_0 + S2_tmp[2] * phat_idx_1) + (M[1] * phat_idx_0 + M[3] *
    phat_idx_1)) * 0.5;

  /* '<S3>:1:299' */
  P22 = TRACKING_CONTROL_KPES_DW.UnitDelay1_DSTATE * T[3] - (S2_tmp[1] *
    phat_idx_0 + S2_tmp[3] * phat_idx_1);

  /* '<S3>:1:300' */
  c2 = P11 + P22;

  /* '<S3>:1:301' */
  /* '<S3>:1:302' */
  P11 = c2 * c2 - (P11 * P22 - P12 * P12) * 4.0;
  if (P11 < 0.0) {
    /* '<S3>:1:303' */
    P11 = 0.0;
  }

  /* '<S3>:1:304' */
  c2 = (c2 - sqrt(P11)) * 0.5 - TRACKING_CONTROL_KPES_P.kappa;
  while ((c2 <= 0.0) && (jumpCount < 50)) {
    /* '<S3>:1:86' */
    /* '<S3>:1:87' */
    xp_idx_0 -= TRACKING_CONTROL_KPES_P.kappa *
      TRACKING_CONTROL_KPES_B.UnaryMinus;

    /* '<S3>:1:88' */
    xp_idx_1 -= TRACKING_CONTROL_KPES_P.kappa *
      TRACKING_CONTROL_KPES_B.UnaryMinus1;

    /* '<S3>:1:89' */
    phi += TRACKING_CONTROL_KPES_P.kappa;

    /* '<S3>:1:90' */
    phat_idx_0 = phi * TRACKING_CONTROL_KPES_B.UnaryMinus + xp_idx_0;

    /* '<S3>:1:91' */
    phat_idx_1 = phi * TRACKING_CONTROL_KPES_B.UnaryMinus1 + xp_idx_1;

    /* '<S3>:1:92' */
    /* '<S3>:1:282' */
    /* '<S3>:1:283' */
    /* '<S3>:1:284' */
    P12 = col2_1_idx_1 - col2_1_idx_1;

    /* '<S3>:1:285' */
    /* '<S3>:1:286' */
    /* '<S3>:1:288' */
    /* '<S3>:1:289' */
    M_tmp[0] = 0.0;
    M_tmp[2] = dTi_dq2[2];
    M_tmp[1] = 0.0;
    M_tmp[3] = dTi_dq2[3];

    /* '<S3>:1:290' */
    for (i = 0; i < 2; i++) {
      T_0[i] = 0.0;
      T_0[i] += T[i] * 0.0;
      c2 = T[i + 2];
      T_0[i] += c2 * col2_1_idx_0;
      T_0[i + 2] = 0.0;
      T_0[i + 2] += (0.0 - col2_1_idx_0) * T[i];
      T_0[i + 2] += c2 * P12;
      M[i] = 0.0;
      M[i] += T_0[i] * T[0];
      M_tmp_1 = T_0[i + 2];
      M[i] += M_tmp_1 * T[1];
      M_tmp_tmp = i << 1;
      M_tmp_0[M_tmp_tmp] = 0.0 - M_tmp[M_tmp_tmp];
      M[i + 2] = 0.0;
      M[i + 2] += T_0[i] * T[2];
      M[i + 2] += M_tmp_1 * T[3];
      M_tmp_0[1 + M_tmp_tmp] = M_tmp[i + 2] - M_tmp[M_tmp_tmp + 1];
    }

    for (i = 0; i < 2; i++) {
      T_0[i] = 0.0;
      T_0[i] += T[i] * M_tmp_0[0];
      c2 = T[i + 2];
      T_0[i] += c2 * M_tmp_0[1];
      T_0[i + 2] = 0.0;
      T_0[i + 2] += T[i] * M_tmp_0[2];
      T_0[i + 2] += c2 * M_tmp_0[3];
      S2_tmp[i] = 0.0;
      S2_tmp[i] += T_0[i] * T[0];
      P12 = T_0[i + 2];
      S2_tmp[i] += P12 * T[1];
      S2_tmp[i + 2] = 0.0;
      S2_tmp[i + 2] += T_0[i] * T[2];
      S2_tmp[i + 2] += P12 * T[3];
    }

    /* '<S3>:1:291' */
    /* '<S3>:1:292' */
    /* '<S3>:1:93' */
    /* '<S3>:1:296' */
    P11 = phi * T[0] - (M[0] * phat_idx_0 + M[2] * phat_idx_1);

    /* '<S3>:1:297' */
    P12 = phi * T[2] - ((S2_tmp[0] * phat_idx_0 + S2_tmp[2] * phat_idx_1) + (M[1]
      * phat_idx_0 + M[3] * phat_idx_1)) * 0.5;

    /* '<S3>:1:299' */
    P22 = phi * T[3] - (S2_tmp[1] * phat_idx_0 + S2_tmp[3] * phat_idx_1);

    /* '<S3>:1:300' */
    c2 = P11 + P22;

    /* '<S3>:1:301' */
    /* '<S3>:1:302' */
    P11 = c2 * c2 - (P11 * P22 - P12 * P12) * 4.0;
    if (P11 < 0.0) {
      /* '<S3>:1:303' */
      P11 = 0.0;
    }

    /* '<S3>:1:304' */
    c2 = (c2 - sqrt(P11)) * 0.5 - TRACKING_CONTROL_KPES_P.kappa;

    /* '<S3>:1:94' */
    jumpCount++;
  }

  /* '<S3>:1:98' */
  /* '<S3>:1:100' */
  M[2] = dTi_dq2[0] * phat_idx_0 + dTi_dq2[2] * phat_idx_1;
  M[3] = dTi_dq2[1] * phat_idx_0 + dTi_dq2[3] * phat_idx_1;

  /* '<S3>:1:101' */
  /* '<S3>:1:104' */
  P11 = Ti[0] * rtb_FromWorkspace1[0] + Ti[2] * rtb_FromWorkspace1[1];
  pd_idx_1 = Ti[1] * rtb_FromWorkspace1[0] + Ti[3] * rtb_FromWorkspace1[1];

  /* '<S3>:1:106' */
  /* '<S3>:1:107' */
  P12 = phat_idx_0 - P11;
  P22 = phat_idx_1 - pd_idx_1;

  /* '<S3>:1:110' */
  /* '<S3>:1:112' */
  dTi_dq2[2] = dTi_dq2[0] * rtb_FromWorkspace1[0] + dTi_dq2[2] *
    rtb_FromWorkspace1[1];
  dTi_dq2[3] = dTi_dq2[1] * rtb_FromWorkspace1[0] + dTi_dq2[3] *
    rtb_FromWorkspace1[1];

  /* '<S3>:1:115' */
  /* '<S3>:1:116' */
  col2_1_idx_0 = TRACKING_CONTROL_KPES_P.alpha * P12 +
    (TRACKING_CONTROL_KPES_B.UnaryMinus -
     TRACKING_CONTROL_KPES_B.FromWorkspace4[0]);
  ddqd_c_idx_1 = col2_1_idx_0 * TRACKING_CONTROL_KPES_P.Kp[0];
  qd_c_idx_0 = TRACKING_CONTROL_KPES_P.alpha * P22 +
    (TRACKING_CONTROL_KPES_B.UnaryMinus1 -
     TRACKING_CONTROL_KPES_B.FromWorkspace4[1]);
  qd_c_idx_1_tmp = qd_c_idx_0 * TRACKING_CONTROL_KPES_P.Kp[3];

  /* '<S3>:1:117' */
  M_tmp_1 = M[3] - M[3];
  col2_1_idx_1 = M[2];
  for (i = 0; i < 2; i++) {
    T_0[i] = 0.0;
    S2_tmp[i] = 0.0;
    T_0[i] += T[i] * 0.0;
    S2_tmp[i] += T[i] * TRACKING_CONTROL_KPES_P.b1_hat;
    c2 = T[i + 2];
    T_0[i] += c2 * col2_1_idx_1;
    S2_tmp[i] += c2 * 0.0;
    T_0[i + 2] = 0.0;
    S2_tmp[i + 2] = 0.0;
    T_0[i + 2] += (0.0 - col2_1_idx_1) * T[i];
    S2_tmp[i + 2] += T[i] * 0.0;
    T_0[i + 2] += c2 * M_tmp_1;
    S2_tmp[i + 2] += c2 * TRACKING_CONTROL_KPES_P.b2_hat;
    M_tmp_0[i] = 0.0;
    T_1[i] = 0.0;
    M_tmp_0[i] += T_0[i] * T[0];
    T_1[i] += S2_tmp[i] * T[0];
    c2 = T_0[i + 2];
    M_tmp_0[i] += c2 * T[1];
    dqd_c_idx_1 = S2_tmp[i + 2];
    T_1[i] += dqd_c_idx_1 * T[1];
    M_tmp_0[i + 2] = 0.0;
    T_1[i + 2] = 0.0;
    M_tmp_0[i + 2] += T_0[i] * T[2];
    T_1[i + 2] += S2_tmp[i] * T[2];
    M_tmp_0[i + 2] += c2 * T[3];
    T_1[i + 2] += dqd_c_idx_1 * T[3];
  }

  M_tmp_1 = M_tmp_0[0] - T_1[0];
  M[0] = M_tmp_1 - TRACKING_CONTROL_KPES_P.Kd[0];
  M_tmp[0] = M_tmp_1;
  M_tmp_1 = M_tmp_0[1] - T_1[1];
  M[1] = M_tmp_1 - TRACKING_CONTROL_KPES_P.Kd[1];
  M_tmp[1] = M_tmp_1;
  M_tmp_1 = M_tmp_0[2] - T_1[2];
  M[2] = M_tmp_1 - TRACKING_CONTROL_KPES_P.Kd[2];
  M_tmp[2] = M_tmp_1;
  M_tmp_1 = M_tmp_0[3] - T_1[3];

  /* '<S3>:1:118' */
  /* '<S3>:1:122' */
  /* '<S3>:1:123' */
  col2_1_idx_0 = col2_1_idx_0 * (TRACKING_CONTROL_KPES_P.alpha *
    TRACKING_CONTROL_KPES_P.Kp[0]) + P12;
  dqd_c_idx_1 = qd_c_idx_0 * (TRACKING_CONTROL_KPES_P.alpha *
    TRACKING_CONTROL_KPES_P.Kp[3]) + P22;

  /* '<S3>:1:128' */
  /* '<S3>:1:130' */
  qd_c_idx_0 = (ddqd_c_idx_1 + phi * col2_1_idx_0) + -0.0 * dqd_c_idx_1;
  col2_1_idx_1 = (qd_c_idx_1_tmp + -dTi_dq2[2] * col2_1_idx_0) + (phi - dTi_dq2
    [3]) * dqd_c_idx_1;

  /* '<S3>:1:132' */
  col2_1_idx_0 = -T[0] * qd_c_idx_0 - T[2] * col2_1_idx_1;
  col2_1_idx_1 = -T[1] * qd_c_idx_0 - T[3] * col2_1_idx_1;

  /* '<S3>:1:136' */
  /* '<S3>:1:190' */
  /* '<S3>:1:183' */
  /* '<S3>:1:184' */
  c2 = 1.0 / (T[0] * T[3] - T[2] * T[1]);

  /* '<S3>:1:185' */
  /* '<S3>:1:191' */
  TRACKING_CONTROL_KPES_B.VectorConcatenate[2] = T[3] * c2 * -col2_1_idx_0 + -T
    [2] * c2 * -col2_1_idx_1;
  TRACKING_CONTROL_KPES_B.VectorConcatenate[3] = -T[1] * c2 * -col2_1_idx_0 + T
    [0] * c2 * -col2_1_idx_1;

  /* '<S3>:1:140' */
  col2_1_idx_0 = T[0] * phat_idx_0 + T[2] * phat_idx_1;
  col2_1_idx_1 = T[1] * phat_idx_0 + T[3] * phat_idx_1;

  /* '<S3>:1:142' */
  /* '<S3>:1:144' */
  /* '<S3>:1:146' */
  /* '<S3>:1:147' */
  qd_c_idx_0 = ((-(M_tmp[0] * P11 + M_tmp[2] * pd_idx_1) + (0.0 * col2_1_idx_0 +
    dTi_dq2[2] * col2_1_idx_1)) + (Ti[0] * rtb_FromWorkspace2[0] + Ti[2] *
    rtb_FromWorkspace2[1])) + ((((M[0] * ddqd_c_idx_1 + M[2] * qd_c_idx_1_tmp) *
    TRACKING_CONTROL_KPES_P.alpha - T[0] * ddqd_c_idx_1) - T[2] * qd_c_idx_1_tmp)
    - TRACKING_CONTROL_KPES_P.Kd[0] * P12);
  col2_1_idx_1 = ((-(M_tmp[1] * P11 + M_tmp_1 * pd_idx_1) + (0.0 * col2_1_idx_0
    + dTi_dq2[3] * col2_1_idx_1)) + (Ti[1] * rtb_FromWorkspace2[0] + Ti[3] *
    rtb_FromWorkspace2[1])) + (((((M_tmp_1 - TRACKING_CONTROL_KPES_P.Kd[3]) *
    qd_c_idx_1_tmp + M[1] * ddqd_c_idx_1) * TRACKING_CONTROL_KPES_P.alpha - T[1]
    * ddqd_c_idx_1) - T[3] * qd_c_idx_1_tmp) - TRACKING_CONTROL_KPES_P.Kd[3] *
    P22);

  /* '<S3>:1:149' */
  /* '<S3>:1:190' */
  /* '<S3>:1:183' */
  /* '<S3>:1:184' */
  /* '<S3>:1:185' */
  /* '<S3>:1:191' */
  TRACKING_CONTROL_KPES_B.VectorConcatenate[4] = T[3] * c2 * qd_c_idx_0 + -T[2] *
    c2 * col2_1_idx_1;
  TRACKING_CONTROL_KPES_B.VectorConcatenate[5] = -T[1] * c2 * qd_c_idx_0 + T[0] *
    c2 * col2_1_idx_1;

  /* '<S3>:1:152' */
  pd_idx_1 = -TRACKING_CONTROL_KPES_B.VectorConcatenate[2] +
    TRACKING_CONTROL_KPES_B.VectorConcatenate[4];
  ddqd_c_idx_1 = -TRACKING_CONTROL_KPES_B.VectorConcatenate[3] +
    TRACKING_CONTROL_KPES_B.VectorConcatenate[5];

  /* '<S3>:1:155' */
  /* '<S3>:1:308' */
  /* '<S3>:1:320' */
  qd_c_idx_1_tmp = phi * TRACKING_CONTROL_KPES_B.UnaryMinus;
  c2 = qd_c_idx_1_tmp + xp_idx_0;

  /* '<S3>:1:321' */
  P11_tmp = phi * TRACKING_CONTROL_KPES_B.UnaryMinus1;
  P11 = P11_tmp + xp_idx_1;

  /* '<S3>:1:322' */
  M_tmp[0] -= phi * T[0];
  M_tmp[1] -= phi * T[1];
  M_tmp[2] -= phi * T[2];
  M_tmp[3] = M_tmp_1 - phi * T[3];

  /* '<S3>:1:323' */
  M_tmp_1 = pd_idx_1 + TRACKING_CONTROL_KPES_B.VectorConcatenate[2];

  /* '<S3>:1:324' */
  P22_tmp = ddqd_c_idx_1 + TRACKING_CONTROL_KPES_B.VectorConcatenate[3];

  /* '<S3>:1:325' */
  P12 = ((((M_tmp[0] * c2 + M_tmp[2] * P11) - T[0] * 0.0) - T[2] * 0.0) + T[0] *
         M_tmp_1) + T[2] * P22_tmp;
  P22 = ((((M_tmp[1] * c2 + M_tmp[3] * P11) - T[1] * 0.0) - T[3] * 0.0) + T[1] *
         M_tmp_1) + T[3] * P22_tmp;

  /* '<S3>:1:309' */
  /* '<S3>:1:310' */
  /* '<S3>:1:320' */
  c2 = (0.5 * TRACKING_CONTROL_KPES_P.dt * P12 + xp_idx_0) + qd_c_idx_1_tmp;

  /* '<S3>:1:321' */
  P11 = (0.5 * TRACKING_CONTROL_KPES_P.dt * P22 + xp_idx_1) + P11_tmp;

  /* '<S3>:1:322' */
  /* '<S3>:1:323' */
  /* '<S3>:1:324' */
  /* '<S3>:1:325' */
  col2_1_idx_0 = ((((M_tmp[0] * c2 + M_tmp[2] * P11) - T[0] * 0.0) - T[2] * 0.0)
                  + T[0] * M_tmp_1) + T[2] * P22_tmp;
  dqd_c_idx_1 = ((((M_tmp[1] * c2 + M_tmp[3] * P11) - T[1] * 0.0) - T[3] * 0.0)
                 + T[1] * M_tmp_1) + T[3] * P22_tmp;

  /* '<S3>:1:311' */
  /* '<S3>:1:312' */
  /* '<S3>:1:320' */
  c2 = (0.5 * TRACKING_CONTROL_KPES_P.dt * col2_1_idx_0 + xp_idx_0) +
    qd_c_idx_1_tmp;

  /* '<S3>:1:321' */
  P11 = (0.5 * TRACKING_CONTROL_KPES_P.dt * dqd_c_idx_1 + xp_idx_1) + P11_tmp;

  /* '<S3>:1:322' */
  /* '<S3>:1:323' */
  /* '<S3>:1:324' */
  /* '<S3>:1:325' */
  qd_c_idx_0 = ((((M_tmp[0] * c2 + M_tmp[2] * P11) - T[0] * 0.0) - T[2] * 0.0) +
                T[0] * M_tmp_1) + T[2] * P22_tmp;
  col2_1_idx_1 = ((((M_tmp[1] * c2 + M_tmp[3] * P11) - T[1] * 0.0) - T[3] * 0.0)
                  + T[1] * M_tmp_1) + T[3] * P22_tmp;

  /* '<S3>:1:313' */
  /* '<S3>:1:314' */
  /* '<S3>:1:320' */
  c2 = (TRACKING_CONTROL_KPES_P.dt * qd_c_idx_0 + xp_idx_0) + qd_c_idx_1_tmp;

  /* '<S3>:1:321' */
  P11 = (TRACKING_CONTROL_KPES_P.dt * col2_1_idx_1 + xp_idx_1) + P11_tmp;

  /* '<S3>:1:322' */
  /* '<S3>:1:323' */
  /* '<S3>:1:324' */
  /* '<S3>:1:325' */
  /* '<S3>:1:315' */
  /* '<S3>:1:157' */
  /* '<S3>:1:160' */
  TRACKING_CONTROL_KPES_B.VectorConcatenate[0] = Ti[0] * phat_idx_0 + Ti[2] *
    phat_idx_1;
  TRACKING_CONTROL_KPES_B.VectorConcatenate[1] = Ti[1] * phat_idx_0 + Ti[3] *
    phat_idx_1;
  TRACKING_CONTROL_KPES_B.phi_out = phi;
  TRACKING_CONTROL_KPES_B.xp_out[0] = ((((((M_tmp[0] * c2 + M_tmp[2] * P11) - T
    [0] * 0.0) - T[2] * 0.0) + T[0] * M_tmp_1) + T[2] * P22_tmp) + ((2.0 *
    col2_1_idx_0 + P12) + 2.0 * qd_c_idx_0)) * (TRACKING_CONTROL_KPES_P.dt / 6.0)
    + xp_idx_0;
  TRACKING_CONTROL_KPES_B.xp_out[1] = ((((((M_tmp[1] * c2 + M_tmp[3] * P11) - T
    [1] * 0.0) - T[3] * 0.0) + T[1] * M_tmp_1) + T[3] * P22_tmp) + ((2.0 *
    dqd_c_idx_1 + P22) + 2.0 * col2_1_idx_1)) * (TRACKING_CONTROL_KPES_P.dt /
    6.0) + xp_idx_1;

  /* End of MATLAB Function: '<Root>/MATLAB Function' */

  /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn4' */
  TRACKING_CONTROL_KPES_B.VectorConcatenate[6] =
    TRACKING_CONTROL_KPES_B.FromWorkspace4[0];

  /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn5' incorporates:
   *  SignalConversion: '<Root>/ConcatBufferAtVector Concatenate1In1'
   */
  TRACKING_CONTROL_KPES_B.VectorConcatenate[8] =
    TRACKING_CONTROL_KPES_B.UnaryMinus;

  /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn4' */
  TRACKING_CONTROL_KPES_B.VectorConcatenate[7] =
    TRACKING_CONTROL_KPES_B.FromWorkspace4[1];

  /* SignalConversion: '<Root>/ConcatBufferAtVector ConcatenateIn5' incorporates:
   *  SignalConversion: '<Root>/ConcatBufferAtVector Concatenate1In2'
   */
  TRACKING_CONTROL_KPES_B.VectorConcatenate[9] =
    TRACKING_CONTROL_KPES_B.UnaryMinus1;

  /* S-Function (hil_read_encoder_block): '<S4>/HIL Read Encoder' */

  /* S-Function Block: TRACKING_CONTROL_KPES/Torque Control Elbow/HIL Read Encoder (hil_read_encoder_block) */
  {
    t_error result = hil_read_encoder
      (TRACKING_CONTROL_KPES_DW.HILInitialize_Card,
       TRACKING_CONTROL_KPES_P.HILReadEncoder_channels_n, 2,
       &TRACKING_CONTROL_KPES_DW.HILReadEncoder_Buffer_l[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(TRACKING_CONTROL_KPES_M, _rt_error_message);
    } else {
      rtb_ManualSwitch2 = TRACKING_CONTROL_KPES_DW.HILReadEncoder_Buffer_l[0];
      rtb_ManualSwitch1 = TRACKING_CONTROL_KPES_DW.HILReadEncoder_Buffer_l[1];
    }
  }

  /* UnaryMinus: '<S4>/Unary Minus' incorporates:
   *  Gain: '<S4>/Motor #1 Encoder Calib1'
   */
  rtb_ManualSwitch2 = -(TRACKING_CONTROL_KPES_P.KE_D1 * rtb_ManualSwitch2);

  /* SampleTimeMath: '<S17>/TSamp'
   *
   * About '<S17>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  TRACKING_CONTROL_KPES_B.TSamp = rtb_ManualSwitch2 *
    TRACKING_CONTROL_KPES_P.TSamp_WtEt;

  /* UnaryMinus: '<S4>/Unary Minus1' incorporates:
   *  Gain: '<S4>/Motor #2 Encoder Calib1'
   */
  rtb_ManualSwitch1 = -(TRACKING_CONTROL_KPES_P.KE_D2 * rtb_ManualSwitch1);

  /* SampleTimeMath: '<S14>/TSamp'
   *
   * About '<S14>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  TRACKING_CONTROL_KPES_B.TSamp_g = rtb_ManualSwitch1 *
    TRACKING_CONTROL_KPES_P.TSamp_WtEt_p;

  /* Gain: '<S4>/Torque to current ' */
  TRACKING_CONTROL_KPES_B.Torquetocurrent = 1.0 / TRACKING_CONTROL_KPES_P.Kt2 *
    ddqd_c_idx_1;

  /* ManualSwitch: '<S4>/Manual Switch2' incorporates:
   *  Gain: '<S4>/Motor #1 Encoder Calib6'
   *  Gain: '<S4>/Motor #1 Encoder Calib7'
   */
  if (TRACKING_CONTROL_KPES_P.ManualSwitch2_CurrentSetting == 1) {
    c2 = TRACKING_CONTROL_KPES_P.R1 * TRACKING_CONTROL_KPES_B.Torquetocurrent;
  } else {
    c2 = TRACKING_CONTROL_KPES_P.R2 * TRACKING_CONTROL_KPES_B.Torquetocurrent;
  }

  /* End of ManualSwitch: '<S4>/Manual Switch2' */

  /* SampleTimeMath: '<S16>/TSamp'
   *
   * About '<S16>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  TRACKING_CONTROL_KPES_B.TSamp_k = TRACKING_CONTROL_KPES_B.Torquetocurrent *
    TRACKING_CONTROL_KPES_P.TSamp_WtEt_i;

  /* ManualSwitch: '<S4>/Manual Switch1' incorporates:
   *  Gain: '<S4>/Motor #1 Encoder Calib2'
   *  Gain: '<S4>/Motor #1 Encoder Calib5'
   *  Sum: '<S16>/Diff'
   *  UnitDelay: '<S16>/UD'
   */
  if (TRACKING_CONTROL_KPES_P.ManualSwitch1_CurrentSetting == 1) {
    rtb_PulseGenerator = (TRACKING_CONTROL_KPES_B.TSamp_k -
                          TRACKING_CONTROL_KPES_DW.UD_DSTATE_i) *
      TRACKING_CONTROL_KPES_P.L1;
  } else {
    rtb_PulseGenerator = (TRACKING_CONTROL_KPES_B.TSamp_k -
                          TRACKING_CONTROL_KPES_DW.UD_DSTATE_i) *
      TRACKING_CONTROL_KPES_P.L2;
  }

  /* End of ManualSwitch: '<S4>/Manual Switch1' */

  /* S-Function (hil_read_analog_block): '<S4>/HIL Read Analog' */

  /* S-Function Block: TRACKING_CONTROL_KPES/Torque Control Elbow/HIL Read Analog (hil_read_analog_block) */
  {
    t_error result = hil_read_analog(TRACKING_CONTROL_KPES_DW.HILInitialize_Card,
      &TRACKING_CONTROL_KPES_P.HILReadAnalog_channels, 1,
      &TRACKING_CONTROL_KPES_DW.HILReadAnalog_Buffer);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(TRACKING_CONTROL_KPES_M, _rt_error_message);
    }

    TRACKING_CONTROL_KPES_B.Current =
      TRACKING_CONTROL_KPES_DW.HILReadAnalog_Buffer;
  }

  /* Sum: '<S4>/Sum1' */
  TRACKING_CONTROL_KPES_B.Sum1 = TRACKING_CONTROL_KPES_B.Torquetocurrent -
    TRACKING_CONTROL_KPES_B.Current;

  /* SampleTimeMath: '<S15>/TSamp'
   *
   * About '<S15>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  TRACKING_CONTROL_KPES_B.TSamp_e = TRACKING_CONTROL_KPES_B.Sum1 *
    TRACKING_CONTROL_KPES_P.TSamp_WtEt_o;

  /* ManualSwitch: '<S4>/Manual Switch3' incorporates:
   *  Gain: '<S4>/Motor #1 Encoder Calib3'
   *  Gain: '<S4>/Motor #1 Encoder Calib8'
   *  Sum: '<S14>/Diff'
   *  Sum: '<S17>/Diff'
   *  UnitDelay: '<S14>/UD'
   *  UnitDelay: '<S17>/UD'
   */
  if (TRACKING_CONTROL_KPES_P.ManualSwitch3_CurrentSetting == 1) {
    phat_idx_0 = (TRACKING_CONTROL_KPES_B.TSamp -
                  TRACKING_CONTROL_KPES_DW.UD_DSTATE) *
      TRACKING_CONTROL_KPES_P.ke1;
  } else {
    phat_idx_0 = (TRACKING_CONTROL_KPES_B.TSamp_g -
                  TRACKING_CONTROL_KPES_DW.UD_DSTATE_e) *
      TRACKING_CONTROL_KPES_P.ke2;
  }

  /* End of ManualSwitch: '<S4>/Manual Switch3' */

  /* Sum: '<S4>/Add' incorporates:
   *  DiscreteIntegrator: '<S4>/Discrete-Time Integrator'
   *  Gain: '<S4>/Gain'
   *  Gain: '<S4>/Gain1'
   *  Gain: '<S4>/Gain2'
   *  Sum: '<S15>/Diff'
   *  Sum: '<S4>/Add1'
   *  UnitDelay: '<S15>/UD'
   */
  phi = ((TRACKING_CONTROL_KPES_P.kp2 * TRACKING_CONTROL_KPES_B.Sum1 +
          TRACKING_CONTROL_KPES_P.ki1 *
          TRACKING_CONTROL_KPES_DW.DiscreteTimeIntegrator_DSTATE) +
         (TRACKING_CONTROL_KPES_B.TSamp_e - TRACKING_CONTROL_KPES_DW.UD_DSTATE_f)
         * TRACKING_CONTROL_KPES_P.Gain2_Gain) + ((phat_idx_0 + c2) +
    rtb_PulseGenerator);

  /* Saturate: '<S4>/Saturation' */
  xp_idx_0 = -TRACKING_CONTROL_KPES_P.i_sat2 * TRACKING_CONTROL_KPES_P.R2;
  xp_idx_1 = TRACKING_CONTROL_KPES_P.i_sat2 * TRACKING_CONTROL_KPES_P.R2;
  if (phi > xp_idx_1) {
    TRACKING_CONTROL_KPES_B.Saturation = xp_idx_1;
  } else if (phi < xp_idx_0) {
    TRACKING_CONTROL_KPES_B.Saturation = xp_idx_0;
  } else {
    TRACKING_CONTROL_KPES_B.Saturation = phi;
  }

  /* End of Saturate: '<S4>/Saturation' */

  /* S-Function (hil_write_analog_block): '<S4>/HIL Write Analog' */

  /* S-Function Block: TRACKING_CONTROL_KPES/Torque Control Elbow/HIL Write Analog (hil_write_analog_block) */
  {
    t_error result;
    result = hil_write_analog(TRACKING_CONTROL_KPES_DW.HILInitialize_Card,
      &TRACKING_CONTROL_KPES_P.HILWriteAnalog_channels, 1,
      &TRACKING_CONTROL_KPES_B.Saturation);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(TRACKING_CONTROL_KPES_M, _rt_error_message);
    }
  }

  /* SignalConversion: '<S4>/ConcatBufferAtVector ConcatenateIn1' */
  TRACKING_CONTROL_KPES_B.VectorConcatenate_j[0] =
    TRACKING_CONTROL_KPES_B.Torquetocurrent;

  /* SignalConversion: '<S4>/ConcatBufferAtVector ConcatenateIn2' */
  TRACKING_CONTROL_KPES_B.VectorConcatenate_j[1] =
    TRACKING_CONTROL_KPES_B.Current;

  /* SignalConversion: '<S4>/ConcatBufferAtVector ConcatenateIn3' */
  TRACKING_CONTROL_KPES_B.VectorConcatenate_j[2] =
    TRACKING_CONTROL_KPES_B.Saturation;

  /* ManualSwitch: '<S4>/Manual Switch4' */
  if (TRACKING_CONTROL_KPES_P.ManualSwitch4_CurrentSetting == 1) {
    TRACKING_CONTROL_KPES_B.VectorConcatenate_j[3] = rtb_ManualSwitch2;
  } else {
    TRACKING_CONTROL_KPES_B.VectorConcatenate_j[3] = rtb_ManualSwitch1;
  }

  /* End of ManualSwitch: '<S4>/Manual Switch4' */
  /* S-Function (hil_read_encoder_block): '<S5>/HIL Read Encoder' */

  /* S-Function Block: TRACKING_CONTROL_KPES/Torque Control Shoulder/HIL Read Encoder (hil_read_encoder_block) */
  {
    t_error result = hil_read_encoder
      (TRACKING_CONTROL_KPES_DW.HILInitialize_Card,
       TRACKING_CONTROL_KPES_P.HILReadEncoder_channels_l, 2,
       &TRACKING_CONTROL_KPES_DW.HILReadEncoder_Buffer_c[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(TRACKING_CONTROL_KPES_M, _rt_error_message);
    } else {
      rtb_PulseGenerator = TRACKING_CONTROL_KPES_DW.HILReadEncoder_Buffer_c[0];
      c2 = TRACKING_CONTROL_KPES_DW.HILReadEncoder_Buffer_c[1];
    }
  }

  /* UnaryMinus: '<S5>/Unary Minus1' incorporates:
   *  Gain: '<S5>/Motor #1 Encoder Calib1'
   */
  rtb_PulseGenerator = -(TRACKING_CONTROL_KPES_P.KE_D1 * rtb_PulseGenerator);

  /* SampleTimeMath: '<S21>/TSamp'
   *
   * About '<S21>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  TRACKING_CONTROL_KPES_B.TSamp_gy = rtb_PulseGenerator *
    TRACKING_CONTROL_KPES_P.TSamp_WtEt_d;

  /* UnaryMinus: '<S5>/Unary Minus2' incorporates:
   *  Gain: '<S5>/Motor #2 Encoder Calib1'
   */
  c2 = -(TRACKING_CONTROL_KPES_P.KE_D2 * c2);

  /* SampleTimeMath: '<S18>/TSamp'
   *
   * About '<S18>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  TRACKING_CONTROL_KPES_B.TSamp_d = c2 * TRACKING_CONTROL_KPES_P.TSamp_WtEt_m;

  /* Gain: '<S5>/Torque to current ' */
  TRACKING_CONTROL_KPES_B.Torquetocurrent_d = 1.0 / TRACKING_CONTROL_KPES_P.Kt1 *
    pd_idx_1;

  /* ManualSwitch: '<S5>/Manual Switch2' incorporates:
   *  Gain: '<S5>/Motor #1 Encoder Calib6'
   *  Gain: '<S5>/Motor #1 Encoder Calib7'
   */
  if (TRACKING_CONTROL_KPES_P.ManualSwitch2_CurrentSetting_o == 1) {
    rtb_ManualSwitch2 = TRACKING_CONTROL_KPES_P.R1 *
      TRACKING_CONTROL_KPES_B.Torquetocurrent_d;
  } else {
    rtb_ManualSwitch2 = TRACKING_CONTROL_KPES_P.R2 *
      TRACKING_CONTROL_KPES_B.Torquetocurrent_d;
  }

  /* End of ManualSwitch: '<S5>/Manual Switch2' */

  /* SampleTimeMath: '<S20>/TSamp'
   *
   * About '<S20>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  TRACKING_CONTROL_KPES_B.TSamp_dk = TRACKING_CONTROL_KPES_B.Torquetocurrent_d *
    TRACKING_CONTROL_KPES_P.TSamp_WtEt_c;

  /* ManualSwitch: '<S5>/Manual Switch1' incorporates:
   *  Gain: '<S5>/Motor #1 Encoder Calib2'
   *  Gain: '<S5>/Motor #1 Encoder Calib5'
   *  Sum: '<S20>/Diff'
   *  UnitDelay: '<S20>/UD'
   */
  if (TRACKING_CONTROL_KPES_P.ManualSwitch1_CurrentSetting_i == 1) {
    rtb_ManualSwitch1 = (TRACKING_CONTROL_KPES_B.TSamp_dk -
                         TRACKING_CONTROL_KPES_DW.UD_DSTATE_az) *
      TRACKING_CONTROL_KPES_P.L1;
  } else {
    rtb_ManualSwitch1 = (TRACKING_CONTROL_KPES_B.TSamp_dk -
                         TRACKING_CONTROL_KPES_DW.UD_DSTATE_az) *
      TRACKING_CONTROL_KPES_P.L2;
  }

  /* End of ManualSwitch: '<S5>/Manual Switch1' */

  /* S-Function (hil_read_analog_block): '<S5>/HIL Read Analog' */

  /* S-Function Block: TRACKING_CONTROL_KPES/Torque Control Shoulder/HIL Read Analog (hil_read_analog_block) */
  {
    t_error result = hil_read_analog(TRACKING_CONTROL_KPES_DW.HILInitialize_Card,
      &TRACKING_CONTROL_KPES_P.HILReadAnalog_channels_b, 1,
      &TRACKING_CONTROL_KPES_DW.HILReadAnalog_Buffer_g);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(TRACKING_CONTROL_KPES_M, _rt_error_message);
    }

    TRACKING_CONTROL_KPES_B.Current_c =
      TRACKING_CONTROL_KPES_DW.HILReadAnalog_Buffer_g;
  }

  /* Sum: '<S5>/Sum1' */
  TRACKING_CONTROL_KPES_B.Sum1_l = TRACKING_CONTROL_KPES_B.Torquetocurrent_d -
    TRACKING_CONTROL_KPES_B.Current_c;

  /* SampleTimeMath: '<S19>/TSamp'
   *
   * About '<S19>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  TRACKING_CONTROL_KPES_B.TSamp_i = TRACKING_CONTROL_KPES_B.Sum1_l *
    TRACKING_CONTROL_KPES_P.TSamp_WtEt_f;

  /* ManualSwitch: '<S5>/Manual Switch3' incorporates:
   *  Gain: '<S5>/Motor #1 Encoder Calib3'
   *  Gain: '<S5>/Motor #1 Encoder Calib8'
   *  Sum: '<S18>/Diff'
   *  Sum: '<S21>/Diff'
   *  UnitDelay: '<S18>/UD'
   *  UnitDelay: '<S21>/UD'
   */
  if (TRACKING_CONTROL_KPES_P.ManualSwitch3_CurrentSetting_g == 1) {
    phat_idx_0 = (TRACKING_CONTROL_KPES_B.TSamp_gy -
                  TRACKING_CONTROL_KPES_DW.UD_DSTATE_a) *
      TRACKING_CONTROL_KPES_P.ke1;
  } else {
    phat_idx_0 = (TRACKING_CONTROL_KPES_B.TSamp_d -
                  TRACKING_CONTROL_KPES_DW.UD_DSTATE_p) *
      TRACKING_CONTROL_KPES_P.ke2;
  }

  /* End of ManualSwitch: '<S5>/Manual Switch3' */

  /* Sum: '<S5>/Add' incorporates:
   *  DiscreteIntegrator: '<S5>/Discrete-Time Integrator'
   *  Gain: '<S5>/Gain'
   *  Gain: '<S5>/Gain1'
   *  Gain: '<S5>/Gain2'
   *  Sum: '<S19>/Diff'
   *  Sum: '<S5>/Add1'
   *  UnitDelay: '<S19>/UD'
   */
  phi = ((TRACKING_CONTROL_KPES_P.kp1 * TRACKING_CONTROL_KPES_B.Sum1_l +
          TRACKING_CONTROL_KPES_P.ki1 *
          TRACKING_CONTROL_KPES_DW.DiscreteTimeIntegrator_DSTATE_m) +
         (TRACKING_CONTROL_KPES_B.TSamp_i -
          TRACKING_CONTROL_KPES_DW.UD_DSTATE_i4) *
         TRACKING_CONTROL_KPES_P.Gain2_Gain_p) + ((phat_idx_0 +
    rtb_ManualSwitch2) + rtb_ManualSwitch1);

  /* Saturate: '<S5>/Saturation' */
  xp_idx_0 = -TRACKING_CONTROL_KPES_P.i_sat1 * TRACKING_CONTROL_KPES_P.R1;
  xp_idx_1 = TRACKING_CONTROL_KPES_P.i_sat1 * TRACKING_CONTROL_KPES_P.R1;
  if (phi > xp_idx_1) {
    TRACKING_CONTROL_KPES_B.Saturation_h = xp_idx_1;
  } else if (phi < xp_idx_0) {
    TRACKING_CONTROL_KPES_B.Saturation_h = xp_idx_0;
  } else {
    TRACKING_CONTROL_KPES_B.Saturation_h = phi;
  }

  /* End of Saturate: '<S5>/Saturation' */

  /* S-Function (hil_write_analog_block): '<S5>/HIL Write Analog' */

  /* S-Function Block: TRACKING_CONTROL_KPES/Torque Control Shoulder/HIL Write Analog (hil_write_analog_block) */
  {
    t_error result;
    result = hil_write_analog(TRACKING_CONTROL_KPES_DW.HILInitialize_Card,
      &TRACKING_CONTROL_KPES_P.HILWriteAnalog_channels_a, 1,
      &TRACKING_CONTROL_KPES_B.Saturation_h);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(TRACKING_CONTROL_KPES_M, _rt_error_message);
    }
  }

  /* SignalConversion: '<S5>/ConcatBufferAtVector ConcatenateIn1' */
  TRACKING_CONTROL_KPES_B.VectorConcatenate_g[0] =
    TRACKING_CONTROL_KPES_B.Torquetocurrent_d;

  /* SignalConversion: '<S5>/ConcatBufferAtVector ConcatenateIn2' */
  TRACKING_CONTROL_KPES_B.VectorConcatenate_g[1] =
    TRACKING_CONTROL_KPES_B.Current_c;

  /* SignalConversion: '<S5>/ConcatBufferAtVector ConcatenateIn3' */
  TRACKING_CONTROL_KPES_B.VectorConcatenate_g[2] =
    TRACKING_CONTROL_KPES_B.Saturation_h;

  /* ManualSwitch: '<S5>/Manual Switch4' */
  if (TRACKING_CONTROL_KPES_P.ManualSwitch4_CurrentSetting_l == 1) {
    TRACKING_CONTROL_KPES_B.VectorConcatenate_g[3] = rtb_PulseGenerator;
  } else {
    TRACKING_CONTROL_KPES_B.VectorConcatenate_g[3] = c2;
  }

  /* End of ManualSwitch: '<S5>/Manual Switch4' */
  /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
  rtb_PulseGenerator = (TRACKING_CONTROL_KPES_DW.clockTickCounter <
                        TRACKING_CONTROL_KPES_P.PulseGenerator_Duty) &&
    (TRACKING_CONTROL_KPES_DW.clockTickCounter >= 0) ?
    TRACKING_CONTROL_KPES_P.PulseGenerator_Amp : 0.0;
  if (TRACKING_CONTROL_KPES_DW.clockTickCounter >=
      TRACKING_CONTROL_KPES_P.PulseGenerator_Period - 1.0) {
    TRACKING_CONTROL_KPES_DW.clockTickCounter = 0;
  } else {
    TRACKING_CONTROL_KPES_DW.clockTickCounter++;
  }

  /* End of DiscretePulseGenerator: '<Root>/Pulse Generator' */
  /* S-Function (hil_write_digital_timebase_block): '<Root>/HIL Write Digital Timebase' */

  /* S-Function Block: TRACKING_CONTROL_KPES/HIL Write Digital Timebase (hil_write_digital_timebase_block) */
  {
    t_error result;
    TRACKING_CONTROL_KPES_DW.HILWriteDigitalTimebase_Buffer =
      (rtb_PulseGenerator != 0);
    result = hil_task_write_digital
      (TRACKING_CONTROL_KPES_DW.HILWriteDigitalTimebase_Task, 1,
       &TRACKING_CONTROL_KPES_DW.HILWriteDigitalTimebase_Buffer);
    if (TRACKING_CONTROL_KPES_DW.HILWriteDigitalTimebase_Started == false &&
        result >= 0) {
      result = hil_task_start
        (TRACKING_CONTROL_KPES_DW.HILWriteDigitalTimebase_Task, (t_clock)
         TRACKING_CONTROL_KPES_P.HILWriteDigitalTimebase_clock, 100.0, -1);
      TRACKING_CONTROL_KPES_DW.HILWriteDigitalTimebase_Started = (result == 0);
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(TRACKING_CONTROL_KPES_M, _rt_error_message);
    }
  }

  /* S-Function (hil_write_digital_block): '<S1>/HIL Write Digital' incorporates:
   *  Constant: '<S1>/Enable: Active Low'
   *  Constant: '<S1>/Master Enable: Active High'
   */

  /* S-Function Block: TRACKING_CONTROL_KPES/Enable AMPAQ/HIL Write Digital (hil_write_digital_block) */
  {
    t_error result;
    TRACKING_CONTROL_KPES_DW.HILWriteDigital_Buffer[0] =
      (TRACKING_CONTROL_KPES_P.EnableActiveLow_Value[0] != 0);
    TRACKING_CONTROL_KPES_DW.HILWriteDigital_Buffer[1] =
      (TRACKING_CONTROL_KPES_P.EnableActiveLow_Value[1] != 0);
    TRACKING_CONTROL_KPES_DW.HILWriteDigital_Buffer[2] =
      (TRACKING_CONTROL_KPES_P.MasterEnableActiveHigh_Value != 0);
    result = hil_write_digital(TRACKING_CONTROL_KPES_DW.HILInitialize_Card,
      TRACKING_CONTROL_KPES_P.HILWriteDigital_channels, 3,
      &TRACKING_CONTROL_KPES_DW.HILWriteDigital_Buffer[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(TRACKING_CONTROL_KPES_M, _rt_error_message);
    }
  }

  /* S-Function (hil_read_digital_block): '<S1>/HIL Read Digital' */

  /* S-Function Block: TRACKING_CONTROL_KPES/Enable AMPAQ/HIL Read Digital (hil_read_digital_block) */
  {
    t_error result = hil_read_digital
      (TRACKING_CONTROL_KPES_DW.HILInitialize_Card,
       TRACKING_CONTROL_KPES_P.HILReadDigital_channels, 3,
       &TRACKING_CONTROL_KPES_DW.HILReadDigital_Buffer[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(TRACKING_CONTROL_KPES_M, _rt_error_message);
    } else {
      TRACKING_CONTROL_KPES_B.HILReadDigital_o1 =
        TRACKING_CONTROL_KPES_DW.HILReadDigital_Buffer[0];
      TRACKING_CONTROL_KPES_B.HILReadDigital_o2 =
        TRACKING_CONTROL_KPES_DW.HILReadDigital_Buffer[1];
      TRACKING_CONTROL_KPES_B.HILReadDigital_o3 =
        TRACKING_CONTROL_KPES_DW.HILReadDigital_Buffer[2];
    }
  }

  /* S-Function (hil_read_digital_block): '<S2>/HIL Read Digital' */

  /* S-Function Block: TRACKING_CONTROL_KPES/Limit Switches/HIL Read Digital (hil_read_digital_block) */
  {
    t_error result = hil_read_digital
      (TRACKING_CONTROL_KPES_DW.HILInitialize_Card,
       TRACKING_CONTROL_KPES_P.HILReadDigital_channels_p, 4,
       &TRACKING_CONTROL_KPES_DW.HILReadDigital_Buffer_a[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(TRACKING_CONTROL_KPES_M, _rt_error_message);
    } else {
      rtb_HILReadDigital_o1 = TRACKING_CONTROL_KPES_DW.HILReadDigital_Buffer_a[0];
      rtb_HILReadDigital_o2 = TRACKING_CONTROL_KPES_DW.HILReadDigital_Buffer_a[1];
      rtb_HILReadDigital_o3 = TRACKING_CONTROL_KPES_DW.HILReadDigital_Buffer_a[2];
      rtb_HILReadDigital_o4 = TRACKING_CONTROL_KPES_DW.HILReadDigital_Buffer_a[3];
    }
  }

  /* Logic: '<S2>/Logical Operator4' incorporates:
   *  Constant: '<S2>/Constant'
   *  Logic: '<S2>/Logical Operator2'
   */
  TRACKING_CONTROL_KPES_B.LogicalOperator4 =
    ((TRACKING_CONTROL_KPES_P.LIMIT_SWITCHES_ENABLE != 0.0) &&
     (!rtb_HILReadDigital_o1));

  /* Stop: '<S6>/Stop Simulation' incorporates:
   *  Constant: '<S10>/Constant'
   *  RelationalOperator: '<S10>/Compare'
   */
  if (TRACKING_CONTROL_KPES_B.LogicalOperator4 !=
      TRACKING_CONTROL_KPES_P.Constant_Value) {
    rtmSetStopRequested(TRACKING_CONTROL_KPES_M, 1);
  }

  /* End of Stop: '<S6>/Stop Simulation' */

  /* Logic: '<S2>/Logical Operator5' incorporates:
   *  Constant: '<S2>/Constant'
   *  Logic: '<S2>/Logical Operator3'
   */
  TRACKING_CONTROL_KPES_B.LogicalOperator5 =
    ((TRACKING_CONTROL_KPES_P.LIMIT_SWITCHES_ENABLE != 0.0) &&
     (!rtb_HILReadDigital_o2));

  /* Stop: '<S7>/Stop Simulation' incorporates:
   *  Constant: '<S11>/Constant'
   *  RelationalOperator: '<S11>/Compare'
   */
  if (TRACKING_CONTROL_KPES_B.LogicalOperator5 !=
      TRACKING_CONTROL_KPES_P.Constant_Value_o) {
    rtmSetStopRequested(TRACKING_CONTROL_KPES_M, 1);
  }

  /* End of Stop: '<S7>/Stop Simulation' */

  /* Logic: '<S2>/Logical Operator6' incorporates:
   *  Constant: '<S2>/Constant'
   *  Logic: '<S2>/Logical Operator1'
   */
  TRACKING_CONTROL_KPES_B.LogicalOperator6 =
    ((TRACKING_CONTROL_KPES_P.LIMIT_SWITCHES_ENABLE != 0.0) &&
     (!rtb_HILReadDigital_o3));

  /* Stop: '<S8>/Stop Simulation' incorporates:
   *  Constant: '<S12>/Constant'
   *  RelationalOperator: '<S12>/Compare'
   */
  if (TRACKING_CONTROL_KPES_B.LogicalOperator6 !=
      TRACKING_CONTROL_KPES_P.Constant_Value_f) {
    rtmSetStopRequested(TRACKING_CONTROL_KPES_M, 1);
  }

  /* End of Stop: '<S8>/Stop Simulation' */

  /* Logic: '<S2>/Logical Operator7' incorporates:
   *  Constant: '<S2>/Constant'
   *  Logic: '<S2>/Logical Operator'
   */
  TRACKING_CONTROL_KPES_B.LogicalOperator7 =
    ((TRACKING_CONTROL_KPES_P.LIMIT_SWITCHES_ENABLE != 0.0) &&
     (!rtb_HILReadDigital_o4));

  /* Stop: '<S9>/Stop Simulation' incorporates:
   *  Constant: '<S13>/Constant'
   *  RelationalOperator: '<S13>/Compare'
   */
  if (TRACKING_CONTROL_KPES_B.LogicalOperator7 !=
      TRACKING_CONTROL_KPES_P.Constant_Value_d) {
    rtmSetStopRequested(TRACKING_CONTROL_KPES_M, 1);
  }

  /* End of Stop: '<S9>/Stop Simulation' */
}

/* Model update function */
void TRACKING_CONTROL_KPES_update(void)
{
  /* Update for UnitDelay: '<Root>/Unit Delay2' */
  TRACKING_CONTROL_KPES_DW.UnitDelay2_DSTATE =
    TRACKING_CONTROL_KPES_B.FromWorkspace4[0];

  /* Update for UnitDelay: '<Root>/Unit Delay3' */
  TRACKING_CONTROL_KPES_DW.UnitDelay3_DSTATE =
    TRACKING_CONTROL_KPES_B.FromWorkspace4[1];

  /* Update for UnitDelay: '<Root>/Unit Delay' */
  TRACKING_CONTROL_KPES_DW.UnitDelay_DSTATE[0] = TRACKING_CONTROL_KPES_B.xp_out
    [0];
  TRACKING_CONTROL_KPES_DW.UnitDelay_DSTATE[1] = TRACKING_CONTROL_KPES_B.xp_out
    [1];

  /* Update for UnitDelay: '<Root>/Unit Delay1' */
  TRACKING_CONTROL_KPES_DW.UnitDelay1_DSTATE = TRACKING_CONTROL_KPES_B.phi_out;

  /* Update for UnitDelay: '<S17>/UD' */
  TRACKING_CONTROL_KPES_DW.UD_DSTATE = TRACKING_CONTROL_KPES_B.TSamp;

  /* Update for UnitDelay: '<S14>/UD' */
  TRACKING_CONTROL_KPES_DW.UD_DSTATE_e = TRACKING_CONTROL_KPES_B.TSamp_g;

  /* Update for UnitDelay: '<S16>/UD' */
  TRACKING_CONTROL_KPES_DW.UD_DSTATE_i = TRACKING_CONTROL_KPES_B.TSamp_k;

  /* Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator' */
  TRACKING_CONTROL_KPES_DW.DiscreteTimeIntegrator_DSTATE +=
    TRACKING_CONTROL_KPES_P.DiscreteTimeIntegrator_gainval *
    TRACKING_CONTROL_KPES_B.Sum1;

  /* Update for UnitDelay: '<S15>/UD' */
  TRACKING_CONTROL_KPES_DW.UD_DSTATE_f = TRACKING_CONTROL_KPES_B.TSamp_e;

  /* Update for UnitDelay: '<S21>/UD' */
  TRACKING_CONTROL_KPES_DW.UD_DSTATE_a = TRACKING_CONTROL_KPES_B.TSamp_gy;

  /* Update for UnitDelay: '<S18>/UD' */
  TRACKING_CONTROL_KPES_DW.UD_DSTATE_p = TRACKING_CONTROL_KPES_B.TSamp_d;

  /* Update for UnitDelay: '<S20>/UD' */
  TRACKING_CONTROL_KPES_DW.UD_DSTATE_az = TRACKING_CONTROL_KPES_B.TSamp_dk;

  /* Update for DiscreteIntegrator: '<S5>/Discrete-Time Integrator' */
  TRACKING_CONTROL_KPES_DW.DiscreteTimeIntegrator_DSTATE_m +=
    TRACKING_CONTROL_KPES_P.DiscreteTimeIntegrator_gainva_p *
    TRACKING_CONTROL_KPES_B.Sum1_l;

  /* Update for UnitDelay: '<S19>/UD' */
  TRACKING_CONTROL_KPES_DW.UD_DSTATE_i4 = TRACKING_CONTROL_KPES_B.TSamp_i;

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++TRACKING_CONTROL_KPES_M->Timing.clockTick0)) {
    ++TRACKING_CONTROL_KPES_M->Timing.clockTickH0;
  }

  TRACKING_CONTROL_KPES_M->Timing.t[0] =
    TRACKING_CONTROL_KPES_M->Timing.clockTick0 *
    TRACKING_CONTROL_KPES_M->Timing.stepSize0 +
    TRACKING_CONTROL_KPES_M->Timing.clockTickH0 *
    TRACKING_CONTROL_KPES_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void TRACKING_CONTROL_KPES_initialize(void)
{
  /* Start for FromWorkspace: '<Root>/From Workspace4' */
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
      29.97, 29.98, 29.990000000000002, 30.0, 30.01, 30.02, 30.03, 30.04, 30.05,
      30.060000000000002, 30.07, 30.080000000000002, 30.09, 30.1, 30.11, 30.12,
      30.13, 30.14, 30.150000000000002, 30.16, 30.17, 30.18, 30.19, 30.2, 30.21,
      30.22, 30.23, 30.240000000000002, 30.25, 30.26, 30.27, 30.28, 30.29, 30.3,
      30.310000000000002, 30.32, 30.330000000000002, 30.34, 30.35, 30.36, 30.37,
      30.38, 30.39, 30.400000000000002, 30.41, 30.42, 30.43, 30.44, 30.45, 30.46,
      30.47, 30.48, 30.490000000000002, 30.5, 30.51, 30.52, 30.53, 30.54, 30.55,
      30.560000000000002, 30.57, 30.580000000000002, 30.59, 30.6, 30.61, 30.62,
      30.63, 30.64, 30.650000000000002, 30.66, 30.67, 30.68, 30.69, 30.7, 30.71,
      30.72, 30.73, 30.740000000000002, 30.75, 30.76, 30.77, 30.78, 30.79, 30.8,
      30.810000000000002, 30.82, 30.830000000000002, 30.84, 30.85, 30.86, 30.87,
      30.88, 30.89, 30.900000000000002, 30.91, 30.92, 30.93, 30.94, 30.95, 30.96,
      30.970000000000002, 30.98, 30.990000000000002 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, -0.0, 1.722454973790383E-6, 1.3787856922263705E-5,
      4.6555189080934853E-5, 0.00011038762428641554, 0.0002156378156928103,
      0.00037263312436612274, 0.00059166080379578127, 0.0008829531615318953,
      0.0012566727182985505, 0.0017228973850458753, 0.0022916056784875161,
      0.00297266199572447, 0.0037758019685812591, 0.0047106179182757569,
      0.0057865444310092268, 0.0070128440749992445, 0.0083985932793833561,
      0.0099526683952973934, 0.011683731959278172, 0.013600219178956407,
      0.015710324660792169, 0.018021989399362035, 0.02054288804743477,
      0.02328041648577156, 0.0262416797112561, 0.029433480061602305,
      0.032862305794500932, 0.036534320038652542, 0.040455350133694251,
      0.044630877375560242, 0.049066027183323, 0.053765559703044169,
      0.058733860863621735, 0.063974933899052483, 0.06949239135093925,
      0.075289447564461182, 0.0813689116903888, 0.087733181205074409,
      0.094384235959670243, 0.10132363276913635, 0.10855250055088583,
      0.11607153602218898, 0.12388099996471022, 0.13198071406379452,
      0.14037005832934493, 0.14904796910434445, 0.15801293766628147,
      0.16726300942592193, 0.1767957837270594, 0.18660841425004177,
      0.19669761002104041, 0.20705963702818914, 0.21769032044486974,
      0.22858504745957819, 0.23973877071094821, 0.2511460123256602,
      0.26280086855610968, 0.2746970150138564, 0.28682771249403055,
      0.2991858133850227, 0.31176376865694871, 0.32455363542154425,
      0.33754708505531833, 0.35073541187697782, 0.36410954236933096,
      0.37766004493507271, 0.39137714017508246, 0.40525071167708676,
      0.41927031730178543, 0.4334252009528024, 0.44770430481609635,
      0.46209628205376674, 0.47658950993649896, 0.49117210339823247,
      0.505831928995991, 0.52055661925718966, 0.53533358739613857,
      0.55015004238088783, 0.56499300433101007, 0.579849320226388,
      0.59470567990659218, 0.60954863233994772, 0.62436460214096523,
      0.63913990631438389, 0.65386077120371378, 0.66851334962178866,
      0.68308373814054446, 0.69755799451693223, 0.71192215523163271,
      0.72616225311700155, 0.7402643350504976, 0.75421447968967992,
      0.76799881522473679, 0.78160353712442632, 0.79501492585124345,
      0.808219364521617, 0.82120335648694187, 0.83395354281131262,
      0.84645671962189373, 0.858699855307988, 0.87067010754501306,
      0.88235484011978038, 0.89374163953368657, 0.90481833136069167,
      0.91557299633723876, 0.92599398616158224, 0.93606993898036361,
      0.945789794540643, 0.95514280898601811, 0.96411856927591466,
      0.97270700720760583, 0.98089841302103431, 0.98868344856704637,
      0.996053160020216, 1.0029989901180392, 1.0095127899088923,
      1.0155868299918123, 1.0212138112318196, 1.0263868749352121,
      1.0310996124699849, 1.0353460743172707, 1.0391207785404679,
      1.0424187186595175, 1.04523537091859, 1.047566700936275,
      1.0494091697282124, 1.0507597390929573, 1.051615876352759,
      1.0519755584418071, 1.0518372753354053, 1.0512000328144555,
      1.050063354560538, 1.048427283577813, 1.0462923829389126,
      1.0436597358529183, 1.0405309450544826, 1.0369081315140931,
      1.0327939324704274, 1.0281914987867158, 1.023104491633954,
      1.0175370785047746, 1.0114939285627282, 1.0049802073326557,
      0.99800157073876938, 0.99056415849799417, 0.98267458687701237,
      0.97433994082238917, 0.96556776547401835, 0.95636605707303135,
      0.94674325327615616, 0.93681095195073028, 0.92667668148110338,
      0.9163431447022502, 0.90581310315821773, 0.89508937639931618,
      0.88417484125995527, 0.873072431117327, 0.86178513513113886,
      0.85031599746461239, 0.83866811648696893, 0.82684464395762314,
      0.81484878419232454, 0.80268379321147765, 0.790352977870894,
      0.77785969497522167, 0.76520735037431131, 0.75239939804278544,
      0.73943933914307247, 0.72633072107219143, 0.71307713649255888,
      0.69968222234711031, 0.68614965885902512, 0.67248316851635648,
      0.65868651504186437, 0.644763502348365, 0.6307179734799071,
      0.61655380953909533, 0.602274928600883, 0.58788528461316569,
      0.57338886628450558, 0.55878969595932615, 0.544091828480922,
      0.52929935004262652, 0.514416377027493, 0.49944705483684193,
      0.48439555670803758, 0.4692660825218522, 0.45406285759979359,
      0.43879013149175955, 0.42345217675439795, 0.40805328772055405,
      0.39259777926018147, 0.37708998553310291, 0.36153425873401573,
      0.345934967830126, 0.33029649729180854, 0.31462324581668966,
      0.29891962504755509, 0.28319005828448063, 0.2674389791915931,
      0.25167083049886918, 0.23589006269938043, 0.22010113274238824,
      0.20430850272272141, 0.18851663856682266, 0.17273000871590483,
      0.1569530828066236, 0.14119033034968045, 0.12544621940678757,
      0.10972521526640425, 0.094031779118679881, 0.078370366730004665,
      0.06274542711761813, 0.047161401224672966, 0.031622720596199916,
      0.016133806056376876, 0.00069906638754585471, -0.014677102988614216,
      -0.029990321327324487, -0.045236223873940884, -0.060410463173747264,
      -0.075508710377910127, -0.090526656545144857, -0.10546001393870044,
      -0.12030451731822064, -0.13505592522608947, -0.14971002126781474,
      -0.16426261538606418, -0.17870954512792139, -0.1930466769049598,
      -0.2072699072457217, -0.22137516404020072, -0.23535840777591621,
      -0.24921563276517941, -0.2629428683631595, -0.27653618017633586,
      -0.28999167126096353, -0.30330548331113794, -0.316473797836091,
      -0.3294928373263179, -0.34235886640816482, -0.35506819298648939,
      -0.3676171693750267, -0.3800021934140822, -0.39221970957519703,
      -0.40426621005240476, -0.41613823583973869, -0.42783237779462119,
      -0.4393452776867926, -0.45067362923242632, -0.46181417911310069,
      -0.47276372797927629, -0.483519131437957, -0.49407730102420433,
      -0.50443520515618245, -0.51458987007341628, -0.52453838075795778,
      -0.53427788183814318, -0.54380557847464883, -0.55311873722854821,
      -0.56221468691107934, -0.57109081941484174, -0.57974459052614,
      -0.58817352071820872, -0.59637519592504762, -0.60434726829561169,
      -0.61208745692809619, -0.61959354858408, -0.62686339838227567,
      -0.63389493047166046, -0.64068613868375457, -0.6472350871638336,
      -0.65353991098085151, -0.65959881671587506, -0.66541008302882454,
      -0.67097206120333031, -0.67628317566951979, -0.68134192450454678,
      -0.68614687991070789, -0.6906966886709639, -0.6949900725817193,
      -0.69902582886270836, -0.70280283054383952, -0.70632002682887129,
      -0.70957644343578608, -0.71257118291374089, -0.71530342493649046,
      -0.71777242657216567, -0.719977522529321, -0.72191812537915556,
      -0.72359372575382974, -0.725003892520795, -0.72614827293308348,
      -0.72702659275549064, -0.72763865636659886, -0.72798434683660562,
      -0.72806362598091967, -0.72787653438949451, -0.72742319143188316,
      -0.72670379523800666, -0.72571862265462528, -0.72446802917752562,
      -0.72295244885942966, -0.72117239419365253, -0.71912845597353381,
      -0.71682130312767789, -0.71425168253105542, -0.71142041879200735,
      -0.70832841401522439, -0.70497664754075628, -0.70136617565914294,
      -0.69749813130273475, -0.69337372371331107, -0.68899423808607851,
      -0.68436103519017477, -0.67947555096577616, -0.67433929609794707,
      -0.66895385556734666, -0.66332088817794643, -0.65744212606188912,
      -0.65131937416165564, -0.64495450968969137, -0.63834948156566207,
      -0.6315063098315199, -0.62442708504455491, -0.61711396764862414,
      -0.60956918732376342, -0.60179504231437031, -0.59379389873618749,
      -0.58556818986228854, -0.5771204153883065, -0.56845314067712449,
      -0.559568995983275, -0.5504706756572918, -0.54116093733026382,
      -0.53164260107885775, -0.5219185485710589, -0.51199172219292655,
      -0.50186512415661044, -0.49154181558994448, -0.48102491560787841,
      -0.4703176003660714, -0.45942310209692189, -0.44834470812836785,
      -0.43708575988574738, -0.42564965187705722, -0.41403983066192396,
      -0.40225979380461485, -0.39031308881143928, -0.37820331205286156,
      -0.36593410767067885, -0.35350916647062497, -0.34093222480073193,
      -0.32820706341583289, -0.3153375063285549, -0.30232741964717796,
      -0.28918071040072824, -0.27590132535168915, -0.26249324979670757,
      -0.24896050635567896, -0.23530715374960665, -0.22153728556762015,
      -0.20765502902355953, -0.19366454370251149, -0.17957002029771507,
      -0.16537567933823294, -0.15108576990780204, -0.13670456835527436,
      -0.12223637699706769, -0.10768552281203064, -0.09305635612916302,
      -0.078353249308589334, -0.063580595416233177, -0.048742806892602741,
      -0.033844314216125493, -0.018889564561451966, -0.0038830204531797308,
      0.011170841584598024, 0.026267532382451386, 0.04140255148307459,
      0.056571388501588216, 0.071769524488262015, 0.086992433293208521,
      0.10223558293261362, 0.11749443695606762, 0.13276445581454241,
      0.14804109822859818, 0.16331982255635369, 0.17859608816080638,
      0.19386535677603578, 0.20912309387187591, 0.22436477001659968,
      0.23958586223719003, 0.25478185537674813, 0.26994824344862034,
      0.28508053098678876, 0.30017423439211016, 0.31522488327395937,
      0.33022802178685029, 0.34517920996160678, 0.36007402503066149,
      0.37490806274704713, 0.38967693869665765, 0.40437628960338734,
      0.41900177462668092, 0.43354907665112513, 0.44801390356763948,
      0.46239198954588184, 0.47667909629743427, 0.49087101432939112,
      0.50496356418793464, 0.51895259769150259, 0.53283399915316909,
      0.54660368659182845, 0.5602576129318112, 0.57379176719054326,
      0.58720217565388266, 0.60048490303874347, 0.61363605364265,
      0.62665177247985193, 0.63952824640365014, 0.65226170521456284,
      0.66484842275399025, 0.67728471798303524, 0.68956695604613516,
      0.70169154931917188, 0.713654958441726, 0.72545369333315779,
      0.73708431419219012, 0.74854343247968758, 0.75982771188431086,
      0.77093386927075658, 0.78185867561029, 0.7925989568932601,
      0.80315159502334, 0.813513528693191, 0.82368175424130352,
      0.83365332648972335, 0.84342535956242637, 0.852995027684084,
      0.86235956595895913, 0.87151627112972885, 0.880462502315958,
      0.88919568173204144, 0.89771329538435851, 0.906012893747467,
      0.91409209241909839, 0.92194857275378372, 0.92958008247490165,
      0.9369844362649854, 0.94415951633409712, 0.95110327296611208,
      0.95781372504274764, 0.9642889605451952, 0.97052713703319293,
      0.97652648210142123, 0.98228529381307506, 0.98780194111050446,
      0.99307486420280133, 0.99810257493022991, 1.0028836571053981,
      1.0074167668310889, 1.0117006327946556, 1.0157340565389212,
      1.0195159127094975, 1.0230451492784829, 1.0263207877444773,
      1.0293419233088714, 1.0321077250283808, 1.034617435943791,
      1.0368703731848998, 1.0388659280516459, 1.0406035660714161,
      1.0420828270325355, 1.0433033249939683, 1.0442647482712246,
      1.0449668593985266, 1.0454094950672552, 1.0455925660407301,
      1.0455160570453716, 1.0451800266383076, 1.0445846070514917,
      1.043730004012414, 1.0426164965414781, 1.0412444367261517,
      1.0396142494719753, 1.0377264322305462, 1.0355815547045921,
      1.033180258530251, 1.030523256936692, 1.0276113343832241,
      1.0244453461740126, 1.0210262180505891, 1.0173549457622888,
      1.0134325946147975, 1.0092602989969761, 1.0048392618861506,
      1.0001707543320482, 0.995256114919587, 0.99009674921071533,
      0.98469412916550669, 0.9790497925427416, 0.97316534228019025,
      0.96704244585481924, 0.9606828346231846, 0.95408830314222182,
      0.94726070847071453, 0.94020196945167545, 0.93291406597591475,
      0.92539903822705871, 0.91765898590830142, 0.90969606745115983,
      0.90151249920652621, 0.89311055461831312, 0.884492563379982,
      0.87566091057426454, 0.86661803579638574, 0.85736643226109788,
      0.84790864589385739, 0.83824727440646241, 0.82838496635746917,
      0.81832442019775486, 0.80806838330152952, 0.79761965098317344,
      0.78698106550021851, 0.7761555150428594, 0.76514593271032738,
      0.75395529547450257, 0.74258662313112334, 0.73104297723896172,
      0.71932746004735715, 0.7074432134124562, 0.69539341770256069,
      0.68318129069296829, 0.67081008645067464, 0.65828309420935949,
      0.645603637235013, 0.632775071682631, 0.61980078544435968,
      0.60668419698949982, 0.59342875419677865, 0.58003793317927133,
      0.56651523710242613, 0.552864194995554, 0.53908836055723586,
      0.52519131095503746, 0.51117664561995246, 0.49704798503600445,
      0.48280896952541014, 0.46846325802972977, 0.45401452688742522,
      0.43946646860825167, 0.42482279064490813, 0.41008721416234162,
      0.39526347280517787, 0.38035531146365209, 0.36536648503850444,
      0.35030075720523379, 0.3351618991781451, 0.31995368847462519,
      0.30467990768004793, 0.28934434321374708, 0.27395078409646667,
      0.25850302071972342, 0.24300484361749103, 0.22746004224062394,
      0.21187240373443744, 0.19624571171986777, 0.18058374507862027,
      0.16489027674271572, 0.14916907248884012, 0.13342388973793134,
      0.11765847636036519, 0.10187656948719813, 0.086081894327807759,
      0.070278162994387855, 0.05446907333364516, 0.038658307766132653,
      0.022849532133567121, 0.0070463945545532133, -0.0087474757109212362,
      -0.024528469387832236, -0.040292998302943826, -0.056037496491713364,
      -0.071758421294939728, -0.087452254444754157, -0.10311550313963357,
      -0.11874470110804219, -0.13433640966037202, -0.14988721872882649,
      -0.16539374789489769, -0.18085264740412366, -0.19626059916775254,
      -0.21161431775101963, -0.22691055134768987, -0.24214608274056793,
      -0.257317730247641, -0.27242234865355652, -0.2874568301261331,
      -0.30241810511760958, -0.31730314325032494, -0.33210895418656772,
      -0.34683258848228238, -0.361471138424403, -0.37602173885149426,
      -0.39048156795748257, -0.4048478480781908, -0.41911784646044548,
      -0.43328887601350419, -0.44735829604256905, -0.46132351296415236,
      -0.47518198100308118, -0.48893120287091119, -0.50256873042554784,
      -0.51609216531186364, -0.52949915958313232, -0.542787416303064,
      -0.55595469012828513, -0.56899878787107061, -0.5819175690421583,
      -0.5947089463735129, -0.60737088632084069, -0.61990140954574724,
      -0.63229859137737277, -0.644560562253402, -0.65668550814028781,
      -0.66867167093260094, -0.68051734883138137, -0.69222089670140541,
      -0.70378072640724731, -0.71519530712807655, -0.7264631656510927,
      -0.73758288664354388, -0.74855311290324256, -0.7593725455875453,
      -0.77003994442072821, -0.78055412787974365, -0.79091397335828972,
      -0.8011184173092033, -0.81116645536512844, -0.82105714243748218,
      -0.83078959279368092, -0.84036298011266575, -0.84977653751871618,
      -0.85902955759358646, -0.86812139236699093, -0.87705145328547629,
      -0.88581921115971818, -0.8944241960903021, -0.90286599737204565,
      -0.9111442633769341, -0.91925870141572985, -0.92720907757835325,
      -0.93499521655312257, -0.942617001424945, -0.95007437345255963,
      -0.957367331824963, -0.96449593339711659, -0.97146029240507581,
      -0.97826058016066686, -0.98489702472585927, -0.99136991056698354,
      -0.9976795781889396, -1.0038264237495673, -1.0098108986543524,
      -1.0156335091316306, -1.0212948157884916, -1.0267954331475522,
      -1.0321360291648161, -1.037317324728809, -1.0423400931412095,
      -1.0472051595791871, -1.0519134005396631, -1.056465743265746,
      -1.060863165155548, -1.0651066931536524, -1.069197403125457,
      -1.0731364192146584, -1.0769249131841421, -1.0805641037405251,
      -1.0840552558426459, -1.0873996799942582, -1.0905987315212198,
      -1.0936538098334692, -1.0965663576720683, -1.0993378603416242,
      -1.1019698449283801, -1.1044638795042998, -1.1068215723174322,
      -1.1090445709689045, -1.1111345615768466, -1.1130932679275696,
      -1.1149224506143491, -1.1166239061641283, -1.1181994661524914,
      -1.1196509963072505, -1.1209803956009825, -1.1221895953328831,
      -1.1232805582002776, -1.1242552773601591, -1.1251157754810954,
      -1.1258641037859065, -1.1265023410854309, -1.1270325928037925,
      -1.1274569899955242, -1.1277776883549202, -1.1279968672180067,
      -1.1281167285575084, -1.1281394959711823, -1.1280674136639333,
      -1.1279027454240582, -1.1276477735940498, -1.1273047980363184,
      -1.1268761350942413, -1.1263641165489371, -1.125771088572141,
      -1.1250994106755994, -1.1243514546573681, -1.1235296035454165,
      -1.122636250538938, -1.1216737979477625, -1.12064465613028,
      -1.1195512424302594, -1.1183959801129881, -1.1171812973010966,
      -1.1159096259105121, -1.1145834005869102, -1.1132050576430657,
      -1.1117770339975248, -1.110301766114969, -1.1087816889486879,
      -1.1072192348855505, -1.1056168326938651, -1.1039769064745353,
      -1.1023018746158924, -1.1005941487526005, -1.0988561327290216,
      -1.097090221567435, -1.0952988004414863, -1.0934842436552559,
      -1.0916489136283332, -1.0897951598872548, -1.0879253180637154,
      -1.0860417088998879, -1.0841466372612576, -1.0822423911573198,
      -1.0803312407704984, -1.0784154374936703, -1.076497212976639,
      -1.0745787781819043, -1.0726623224500995, -1.0707500125754295,
      -1.0688439918914612, -1.0669463793675884, -1.065059268716539,
      -1.0631847275132222, -1.0613247963252632, -1.0594814878555436,
      -1.05765678609706, -1.0558526455004207, -1.0540709901542893,
      -1.0523137129790712, -1.0505826749341503, -1.0488797042389615,
      -1.0472065956082031, -1.0455651095014429, -1.043956971387433,
      -1.0423838710233715, -1.0408474617493981, -1.0393493597985792,
      -1.0378911436226352, -1.0364743532336607, -1.0351004895620768,
      -1.03377101383107, -1.032487346947714, -1.0312508689110387,
      -1.0300629182372383, -1.0289247914022335, -1.027837742301811,
      -1.0268029817295103, -1.0258216768724822, -1.0248949508254741,
      -1.0240238821231462, -1.0232095042908709, -1.0224528054142019,
      -1.0217547277271417, -1.0211161672193936, -1.0205379732627127,
      -1.0200209482565088, -1.0195658472928328, -1.0191733778408545,
      -1.0188441994509652, -1.0185789234786027, -1.0183781128279001,
      -1.0182422817152561, -1.0181718954529173, -1.018167370252629,
      -1.0182290730494623, -1.0183573213458494, -1.0185523830758925,
      -1.0188144764900144, -1.0191437700599542, -1.0195403824041849,
      -1.0200043822337428, -1.0205357883185153, -1.0211345694739726,
      -1.0218006445683743, -1.0225338825504255, -1.0233341024973786,
      -1.0242010736835643, -1.0251345156693232, -1.0261340984102976,
      -1.0271994423870572, -1.028330118754992, -1.0295256495144278,
      -1.0307855077008934, -1.0321091175954717, -1.03349585495516,
      -1.0349450472631343, -1.0364559739988508, -1.0380278669278662,
      -1.0396599104112616, -1.0413512417345832, -1.0431009514561418,
      -1.0449080837745677, -1.0467716369154694, -1.0486905635370549,
      -1.0506637711545737, -1.0526901225834016, -1.0547684364006245,
      -1.0568974874249331, -1.0590760072146566, -1.0613026845837603,
      -1.0635761661355854, -1.0658950568141616, -1.0682579204728813,
      -1.0706632804603051, -1.0731096202229065, -1.0755953839245134,
      -1.0781189770822239, -1.0806787672185534, -1.0832730845295808,
      -1.0859002225688312, -1.0885584389466598, -1.0912459560448489,
      -1.09396096174618, -1.0967016101786951, -1.0994660224743731,
      -1.1022522875419316, -1.1050584628534876, -1.1078825752447565,
      -1.1107226217285047, -1.1135765703209706, -1.1164423608809126,
      -1.1193179059609828, -1.1222010916711405, -1.1250897785537282,
      -1.1279818024699357, -1.1308749754972891, -1.1337670868378453,
      -1.1366559037367405, -1.1395391724107848, -1.1424146189866962,
      -1.1452799504486895, -1.148132855595021, -1.1509710060031453,
      -1.1537920570031448, -1.1565936486590274, -1.1593734067575714,
      -1.1621289438042999, -1.1648578600262705, -1.1675577443812506,
      -1.1702261755729326, -1.17286072307181, -1.1754589481413049,
      -1.1780184048688105, -1.1805366412012157, -1.1830111999845476,
      -1.1854396200073505, -1.1878194370473778, -1.1901481849212621,
      -1.1924233965366995, -1.1946426049468089, -1.1968033444062531,
      -1.1989031514287074, -1.2009395658453192, -1.2029101318637214,
      -1.2048123991272206, -1.2066439237737683, -1.2084022694942977,
      -1.210085008590049, -1.2116897230284716, -1.2132140054973117,
      -1.2146554604564783, -1.2160117051873172, -1.2172803708388644,
      -1.2184591034707082, -1.219545565092053, -1.2205374346965985,
      -1.2214324092928512, -1.2222282049294586, -1.2229225577151925,
      -1.223513224833199, -1.2239979855491088, -1.2243746422126627,
      -1.2246410212524326, -1.2247949741632851, -1.224834378486207,
      -1.2247571387801122, -1.2245611875852775, -1.2242444863780177,
      -1.223805026516253, -1.2232408301756088, -1.2225499512756619,
      -1.2217304763960304, -1.2207805256819018, -1.2196982537386918,
      -1.2184818505154615, -1.2171295421767894, -1.215639591962715,
      -1.2140103010364707, -1.2122400093196382, -1.2103270963144235,
      -1.2082699819127389, -1.206067127191766, -1.2037170351956832,
      -1.2012182517032801, -1.1985693659811349, -1.1957690115220803,
      -1.1928158667686464, -1.1897086558212207, -1.1864461491306311,
      -1.1830271641748833, -1.1794505661197954, -1.1757152684632461,
      -1.1718202336628059, -1.1677644737464781, -1.1635470509063386,
      -1.1591670780747849, -1.1546237194832225, -1.1499161912029159,
      -1.1450437616678095, -1.1400057521791009, -1.1348015373913616,
      -1.1294305457799885, -1.1238922600898329, -1.118186217764763,
      -1.1123120113580434, -1.1062692889233059, -1.1000577543859857,
      -1.0936771678950221, -1.0871273461547204, -1.0804081627365918,
      -1.07351954837105, -1.0664614912188304, -1.059234037122009,
      -1.0518372898345063, -1.0442714112319682, -1.0365366215009151,
      -1.0286331993070739, -1.0205614819428022, -1.0123218654535286,
      -1.0039148047431374, -0.99534081365821847, -0.9866004650511554,
      -0.97769439082197906, -0.96862328193895064, -0.95938788843784439,
      -0.94998901939990987, -0.94042754290847053, -0.930704385984185,
      -0.920820534498928, -0.91077703306832825, -0.90057498492296251,
      -0.89021555175822109, -0.87969995356287378, -0.86902946842638185,
      -0.85820543232499591, -0.84722923888666413, -0.83610233913486232,
      -0.82482624121135206, -0.81340251007798492, -0.80183276719760643,
      -0.79011869019417147, -0.77826201249213978, -0.76626452293528069,
      -0.75412806538497412, -0.74185453829816106, -0.72944589428501128,
      -0.71690413964651645, -0.704231333892072, -0.69142958923726183,
      -0.67850107008194771, -0.66544799246886954, -0.6522726235228764,
      -0.63897728087102668, -0.62556433204366468, -0.61203619385674124,
      -0.59839533177550919, -0.58464425925984487, -0.57078553709137059,
      -0.55682177268261634, -0.54275561936844874, -0.52858977567995724,
      -0.51432698460109738, -0.49997003280826585, -0.48552174989310726,
      -0.47098500756878209, -0.45636271885997187, -0.44165783727685726,
      -0.42687335597338943, -0.41201230689008278, -0.39707775988167143,
      -0.38207282182983848, -0.36700063574140412, -0.35186437983220242,
      -0.33666726659698587, -0.32141254186567175, -0.30610348384622443,
      -0.29074340215450217, -0.27533563683142886, -0.25988355734774704,
      -0.2443905615967738, -0.22886007487542326, -0.21329554885390242,
      -0.19770046053437743, -0.18207831119899837, -0.16643262534762607,
      -0.150766949625605, -0.13508485174198964, -0.11938991937854215,
      -0.1036857590898973, -0.087975995195291812, -0.072264268662177444,
      -0.056554235982155143, -0.040849568039586004, -0.025153948973273943,
      -0.0094710750316103209, 0.0061953465784453376, 0.021841598848117094,
      0.037463956128936937, 0.053058685299816832, 0.068622046938687009,
      0.084150296498278487, 0.099639685485674423, 0.11508646264516742,
      0.13048687514409812, 0.14583716976119118, 0.16113359407701475,
      0.176372397666144, 0.19154983329062419, 0.20666215809430524,
      0.22170563479765476, 0.23667653289261817, 0.25157112983711039,
      0.26638571224874685, 0.281116577097389, 0.29576003289606656,
      0.31031240088989565, 0.3247700162425774, 0.33912922922002531,
      0.35338640637077734, 0.3675379317026975, 0.38158020785564728,
      0.39550965726963949, 0.4093227233481086, 0.42301587161589077,
      0.43658559087149812, 0.4500283943332789, 0.46334082077908118,
      0.4765194356790004, 0.489560832320851, 0.50246163292790336,
      0.51521848976856643, 0.52782808625756861, 0.54028713804829365,
      0.55259239411585859, 0.56474063783056427, 0.5767286880213438,
      0.58855340002881706, 0.600211666747623, 0.61170041965760591,
      0.62301662984353134, 0.63415730900295708, 0.64511951044190585,
      0.65590033005799919, 0.66649690731067923, 0.67690642617818808,
      0.68712611610099139, 0.697153252911257, 0.70698515974811149,
      0.71661920795831846, 0.72605281798207377, 0.73528346022358193,
      0.74430865590614537, 0.75312597791140456, 0.76173305160248717,
      0.77012755563072921, 0.77830722272569941, 0.78626984046824333,
      0.79401325204626838, 0.80153535699299494, 0.8088341119074155,
      0.81590753115669457, 0.82275368756026823, 0.8293707130553829,
      0.83575679934384683, 0.84191019851974347, 0.84782922367789715,
      0.85351224950286531, 0.85895771283823108, 0.86416411323600584,
      0.86913001348592855, 0.87385404012447854, 0.87833488392340653,
      0.88257130035760789, 0.88656211005216623, 0.89030619920839926,
      0.893802520008752, 0.89705009100038979, 0.90004799745732555,
      0.90279539172098944, 0.90529149351905758, 0.90753559026246444,
      0.9095270373204587, 0.91126525827360683, 0.91274974514464158,
      0.9139800586070691, 0.91495582817144649, 0.91567675234925616,
      0.91614259879431259, 0.91635320442163493, 0.91630847550373751,
      0.91600838774429616, 0.915452986329147, 0.91464238595459368,
      0.913576770833002, 0.9122563946756701, 0.91068158065296045,
      0.90885272133171224, 0.9067702785899292, 0.90443478350876916,
      0.90184683624186324, 0.89900710586199284, 0.89591633018517247,
      0.89257531557218472, 0.88898493670762624, 0.88514613635653094,
      0.881059925098644, 0.87672738104042647, 0.87214964950487972,
      0.86732794269928926, 0.86226353936098754, 0.85695778438125059,
      0.851412088407451, 0.845627927423585, 0.839606842309319,
      0.83335043837769285, 0.82686038489162861, 0.82013841455940362,
      0.8131863230092542, 0.80600596824327031, 0.79859927007078735,
      0.79096820952141778, 0.78311482823796141, 0.77504122784936813,
      0.76674956932395633, 0.758242072303124, 0.74952101441575358,
      0.74058873057354213, 0.73144761224750221, 0.722100106725853,
      0.7125487163535702, 0.70279599775383939, 0.69284456103167591,
      0.682697068959961, 0.67235623614820228, 0.66182482819425748,
      0.65110566081932952, 0.64020159898653439, 0.62911555600328772,
      0.61785049260787517, 0.60640941604047538, 0.59479537909895241,
      0.5830114791797526, 0.57106085730419776, 0.558946697130546,
      0.54667222395212234, 0.53424070368185428, 0.52165544182358814,
      0.50891978243049141, 0.49603710705093573, 0.48301083366218273,
      0.46984441559225876, 0.45654134043035544, 0.44310512892617315,
      0.42953933387851412, 0.41584753901356575, 0.40203335785322059,
      0.38810043257381982, 0.37405243285571066, 0.35989305472402122,
      0.34562601938102205, 0.33125507203050553, 0.31678398069452562,
      0.30221653502297924, 0.287556545096359, 0.27280784022213855,
      0.25797426772517185, 0.24305969173252054, 0.2280679919531382,
      0.21300306245280765, 0.19786881042477422, 0.18266915495645769,
      0.16740802579269598, 0.15208936209592855, 0.13671711120374022,
      0.1212952273842046, 0.10582767058941767, 0.090318405207683458,
      0.074771398814771017, 0.059190620924631315, 0.043580041740065634,
      0.027943630903697753, 0.01228535624975241, -0.0033908174430020421,
      -0.019080929696679461, -0.034781025577649977, -0.050487156937459504,
      -0.0661953836508469, -0.081901774850444725, -0.097602410157752062,
      -0.11329338090992866, -0.1289707913820341, -0.14463076000426389,
      -0.1602694205737753, -0.17588292346068657, -0.19146743680783662,
      -0.2070191477239286, -0.22253426346957236, -0.23800901263590907,
      -0.2534396463153496, -0.26882243926407634, -0.28415369105586136,
      -0.29942972722686478, -0.31464690041094157, -0.32980159146518434,
      -0.34489021058520142, -0.35990919840982055, -0.37485502711481333,
      -0.38972420149529, -0.404513260036357, -0.41921877597172674,
      -0.4338373583298471, -0.44836565296728031, -0.46280034358888811,
      -0.47713815275455973, -0.49137584287206781, -0.50551021717576683,
      -0.51953812069077965, -0.53345644118232571, -0.54726211008991421,
      -0.56095210344602919, -0.57452344277905143, -0.587973196000054,
      -0.60129847827320848, -0.6144964528695, -0.62756433200344941,
      -0.64049937765255571, -0.65329890235921273, -0.66596027001477776,
      -0.67848089662558841, -0.690858251060603, -0.70308985578045957,
      -0.7151732875476855, -0.72710617811782852, -0.7388862149112585,
      -0.750511141665447, -0.76197875906745161, -0.77328692536645882,
      -0.78443355696612183, -0.795416628996524, -0.80623417586557267,
      -0.81688429178963218, -0.82736513130322542, -0.83767490974762926,
      -0.84781190373820869, -0.85777445161032662, -0.86756095384367593,
      -0.87716987346492414, -0.886599736428489, -0.89584913197537075,
      -0.90491671296988541, -0.91380119621421541, -0.92250136274065031,
      -0.93101605808146215, -0.93934419251628332, -0.94748474129694249,
      -0.95543674484966989, -0.96319930895462913, -0.97077160490269221,
      -0.97815286962944015, -0.98534240582632937, -0.992339582029002,
      -0.99914383268273088, -1.0057546581849495, -1.0121716249048953,
      -1.0183943651803475, -1.024422577291487, -1.0302560254118671,
      -1.0358945395365518, -1.0413380153874323, -1.0465864142957726,
      -1.0516397630620422, -1.0564981537930689, -1.0611617437166048,
      -1.0656307549733521, -1.0699054743865632, -1.0739862532092634,
      -1.0778735068492271, -1.0815677145717904, -1.0850694191806318,
      -1.088379226676619, -1.0914978058948668, -1.0944258881201339,
      -1.0971642666807018, -1.0997137965208894, -1.1020753937523637,
      -1.1042500351843954, -1.1062387578332578, -1.1080426584109282,
      -1.1096628927932932, -1.1111006754680395, -1.1123572789624441,
      -1.113434033251266, -1.1143323251449471, -1.1150535976583782,
      -1.1155993493604133, -1.1159711337043903, -1.1161705583399222,
      -1.1161992844061683, -1.1160590258068699, -1.1157515484673965,
      -1.1152786695740866, -1.1146422567961403, -1.1138442274903704,
      -1.1128865478890642, -1.1117712322712707, -1.1105003421178234,
      -1.1090759852503733, -1.1075003149547664, -1.1057755290890614,
      -1.1039038691765348, -1.1018876194839744, -1.0997291060856011,
      -1.097430695912972, -1.0949947957911697, -1.0924238514616593,
      -1.0897203465921537, -1.0868868017738262, -1.0839257735062608,
      -1.0808398531704682, -1.0776316659903702, -1.0743038699831016,
      -1.0708591548985187, -1.0673002411482928, -1.0636298787249547,
      -1.0598508461113163, -1.0559659491806155, -1.0519780200878179,
      -1.0478899161524373, -1.0437045187333043, -1.039424732095668,
      -1.0350534822710487, -1.0305937159102385, -1.026048399129861,
      -1.0214205163529193, -1.0167130691437278, -1.0119290750376568,
      -1.0070715663661021, -1.0021435890770998, -0.99714820155201922,
      -0.99208847341874418, -0.98696748436177173, -0.98178832292966633,
      -0.97655408534026189, -0.97126787428408712, -0.96593279772640717,
      -0.96055196770831053, -0.95512849914730613, -0.94966550863780408,
      -0.9441661132519561, -0.93863342934126948, -0.9330705713394154,
      -0.9274806505666614, -0.921866774036376, -0.9162320432640022,
      -0.91057955307894467, -0.90491239043980676, -0.89923363325335737,
      -0.89354634919771081, -0.88785359455009227, -0.88215841301962694,
      -0.87646383458558352, -0.87077287434145156, -0.865088531345311,
      -0.85941378747687436, -0.85375160630161717, -0.84810493194242109,
      -0.84247668795910058, -0.83686977623624748, -0.8312870758797738,
      -0.82573144212255234, -0.82020570523955383, -0.81471266947284249,
      -0.80925511196686739, -0.80383578171437187, -0.798457398513348,
      -0.79312265193537435, -0.78783420030572859, -0.782594669695639,
      -0.77740665292702171, -0.77227270859008024, -0.76719536007410849,
      -0.762177094611848, -0.75722036233773926, -0.75232757536041339,
      -0.74750110684975668, -0.74274329013886242, -0.73805641784120679,
      -0.733442740983373, -0.72890446815360976, -0.72444376466655946,
      -0.7200627517444359, -0.7157635057149585, -0.71154805722632108,
      -0.707418390479506, -0.70337644247816966, -0.69942410229642382,
      -0.69556321036474278, -0.69179555777426882, -0.68812288559976464,
      -0.68454688424145693, -0.68106919278599876, -0.67769139838681181,
      -0.674415035664, -0.67124158612406948, -0.6681724775996627,
      -0.665209083709512, -0.66235272333880268, -0.65960466014013608,
      -0.656966102055295, -0.6544382008579448, -0.65202205171747374,
      -0.6497186927841232, -0.647529104795544, -0.64545421070494491,
      -0.64349487533095862, -0.64165190502935054, -0.6399260473867121,
      -0.63831799093622044, -0.6368283648955988, -0.6354577389273619,
      -0.63420662292143737, -0.63307546680024873, -0.63206466034633113,
      -0.63117453305254534, -0.6304053539949559, -0.6297573317284082,
      -0.62923061420486337, -0.62882528871451182, -0.62854138184970143,
      -0.62837885949168926, -0.62833762682022831, -0.62841752834600328,
      -0.62861834796588334, -0.62893980904100943, -0.62938157449765564,
      -0.62994324695087145, -0.630624368850841, -0.631424422651914,
      -0.632342831004274, -0.63337895696814717, -0.6345321042505111,
      -0.63580151746420333, -0.6371863824093591, -0.638685826377061,
      -0.64029891847512954, -0.64202466997590379, -0.64386203468593,
      -0.64580990933740767, -0.64786713400126739, -0.650032492521736,
      -0.652304712972247, -0.65468246813251785, -0.65716437598665622,
      -0.65974900024210448, -0.662434850869247, -0.66522038466148548,
      -0.66810400581561025, -0.67108406653223374, -0.67415886763610644,
      -0.67732665921607271, -0.68058564128446219, -0.68393396445568455,
      -0.68736973064377227, -0.69089099377865515, -0.69449576054088014,
      -0.69818199111457, -0.7019475999582977, -0.70579045659364592,
      -0.7097083864111674, -0.71369917149344686, -0.71776055145500084,
      -0.72189022429869754, -0.72608584728840075, -0.73034503783754834,
      -0.734665374413314, -0.73904439745608341, -0.74347961031386967,
      -0.7479684801913844, -0.75250843911338794, -0.75709688490200544,
      -0.76173118216767144, -0.76640866331331226, -0.7711266295514505,
      -0.77588235193385358, -0.78067307239337191, -0.78549600479758086,
      -0.79034833601387366, -0.79522722698561377, -0.80012981381896764,
      -0.80505320888004084, -0.80999450190191657, -0.81495076110120757,
      -0.8199190343037317, -0.8248963500788975, -0.82987971888241718,
      -0.83486613420691036, -0.83985257374002731, -0.84483600052964647,
      -0.84981336415573971, -0.8547816019085126, -0.85973763997235908,
      -0.86467839461524254, -0.86960077338305553, -0.8745016762985578,
      -0.87937799706443376, -0.88422662427006249, -0.88904444260156656,
      -0.89382833405469087, -0.89857517915010365, -0.90328185815066708,
      -0.9079452522802347, -0.91256224494357219, -0.91712972294691208,
      -0.92164457771878128, -0.9261037065305695, -0.9305040137164815,
      -0.93484241189239237, -0.93911582317317566, -0.94332118038808566,
      -0.94745542829372154, -0.95151552478417212, -0.95549844209788626,
      -0.95940116802083264, -0.96322070708553909, -0.96695408176553965,
      -0.97059833366484716, -0.97415052470195973, -0.97760773828805125,
      -0.98096708049884651, -0.98422568123980358, -0.98738069540416606,
      -0.9904293040234583, -0.99336871541003169, -0.99619616629121466,
      -0.998908922934683, -1.0015042822646238, -1.0039795729682917,
      -1.0063321565925685, -1.0085594286301025, -1.0106588195946509,
      -1.0126277960852215, -1.0144638618386359, -1.0161645587701207,
      -1.0177274680015485, -1.0191502108769528, -1.0204304499649437,
      -1.0215658900476605, -1.0225542790958893, -1.0233934092299934,
      -1.0240811176663056, -1.0246152876486159, -1.0249938493644419,
      -1.0252147808457079, -1.0252761088535209, -1.0251759097467168,
      -1.0249123103338307, -1.0244834887082088, -1.0238876750659203,
      -1.0231231525061817, -1.0221882578139745, -1.0210813822246023,
      -1.0198009721698413, -1.0183455300054625, -1.016713614719809,
      -1.0149038426231725, -1.0129148880177179, -1.0107454838476948,
      -1.0083944223296657, -1.0058605555625575, -1.0031427961172372,
      -1.0002401176054598, -0.99715155522789756, -0.9938762063010691,
      -0.99041323076298515, -0.98676185165726, -0.982921355595535,
      -0.97889109319802836, -0.97467047951200247, -0.97025899440803931,
      -0.96565618295389266, -0.96086165576581006, -0.95587508933718013,
      -0.95069622634433348, -0.945324875929394, -0.93976091396005834,
      -0.93400428326617724, -0.92805499385304135, -0.92191312309126039,
      -0.91557881588316514, -0.90905228480564682, -0.902333810229333,
      -0.89542374041406625, -0.88832249158063337, -0.88103054795864977,
      -0.87354846181060242, -0.86587685343201648, -0.85801641112768456,
      -0.8499678911639843, -0.84173211769724809, -0.83330998267821332,
      -0.824702445732532, -0.81591053401735569, -0.80693534205407147,
      -0.79777803153716342, -0.788439831119263, -0.77892203617244127,
      -0.76922600852582379, -0.75935317617953924, -0.74930503299512385,
      -0.73908313836245432, -0.72868911684330262, -0.71812465779158607,
      -0.70739151495045038, -0.69649150602630783, -0.68542651223992124,
      -0.674198477854669, -0.66280940968218882, -0.6512613765654639,
      -0.63955650883957338, -0.62769699777021282, -0.61568509497023038,
      -0.6035231117942903, -0.59121341871185529, -0.57875844465875081,
      -0.56616067636742806, -0.553422657676181, -0.54054698881751972,
      -0.52753632568592768, -0.51439337908525307, -0.50112091395593772,
      -0.48772174858231654, -0.474198753780346, -0.460554852065872,
      -0.44679301680379119, -0.43291627133838279, -0.41892768810507247,
      -0.40483038772388713, -0.3906275380749118, -0.37632235335611119,
      -0.36191809312370682, -0.34741806131549363, -0.33282560525740795,
      -0.31814411465367304, -0.303377020560814, -0.28852779434589149,
      -0.27359994662937331, -0.2585970262128463, -0.2435226189920304,
      -0.2283803468554223, -0.21317386656893039, -0.19790686864685614,
      -0.1825830762095727, -0.16720624382836519, -0.15178015635772307,
      -0.13630862775550545, -0.1207954998913521, -0.10524464134379621,
      -0.08965994618638512, -0.074045332763277655, -0.058404742454695346,
      -0.042742138432678989, -0.027061504407496162, -0.011366843365149648,
      0.0043378237035376355, 0.020048459081938419, 0.035761009614257488,
      0.051471407999330476, 0.067175574091200785, 0.0828694162060371,
      0.098548832434939448, 0.11420971196216156, 0.12984793638837949,
      0.14545938105852266, 0.16103991639370732, 0.17658540922683519,
      0.19209172414144726, 0.20755472481332818, 0.22297027535445821,
      0.23833424165878406, 0.25364249274945572, 0.26889090212703304,
      0.28407534911814081, 0.29919172022423413, 0.31423591046995758,
      0.32920382475062043, 0.34409137917836657, 0.35889450242658555,
      0.37360913707213517, 0.38823124093480554, 0.40275678841372464,
      0.41718177182017152, 0.431502202706319, 0.44571411318951604,
      0.45981355727163775, 0.47379661215306779, 0.487659379540787,
      0.50139798695026783, 0.51500858900061663, 0.528487368702545,
      0.54183053873875708, 0.55503434273630692, 0.56809505653050774,
      0.5810089894199052, 0.593772485411935, 0.6063819244588563,
      0.61883372368348688, 0.63112433859434547, 0.64325026428979148,
      0.65520803665075422, 0.666994233521608, 0.67860547587882114,
      0.690038428986981, 0.70128980354178672, 0.71235635679958986,
      0.72323489369315064, 0.733922267933178, 0.74441538309532307,
      0.75471119369216277, 0.764806706229919, 0.77469898024948047,
      0.78438512935134475, 0.79386232220419184, 0.803127783536716,
      0.81217879511234026, 0.82101269668649568, 0.82962688694617348,
      0.83801882443136133, 0.84618602843807034, 0.85412607990264067,
      0.86183662226701285, 0.86931536232468687, 0.87656007104700251,
      0.88356858438954533, 0.89033880407832822, 0.896868698375506,
      0.90315630282431891, 0.90919972097305468, 0.91499712507773467,
      0.9205467567832698, 0.925846927782882, 0.93089602045553177,
      0.935692488481122, 0.94023485743326207, 0.94452172534939738,
      0.94855176327807977, 0.95232371580318365, 0.95583640154488647,
      0.959088713637229, 0.96207962018208137, 0.96480816467934027,
      0.96727346643321455, 0.96947472093444542, 0.97141120021829952,
      0.97308225319823283, 0.97448730597507227, 0.97562586212160518,
      0.976497502942482, 0.97710188770930217, 0.97743875387081425,
      0.977507917238134, 0.977309272144901, 0.97684279158232146,
      0.9761085273090111, 0.97510660993561227, 0.97383724898412793,
      0.9723007329219403, 0.97049742917047888, 0.96842778408855135,
      0.96609232293028113, 0.9634916497776892, 0.96062644744791248,
      0.95749747737506419, 0.95410557946679142, 0.950451671935518,
      0.946536751104462, 0.94236189118844471, 0.93792824404954633,
      0.93323703892770893, 0.92828958214633472, 0.92308725679293779,
      0.91763152237501577, 0.91192391445117238, 0.90596604423761107,
      0.8997595981901465, 0.89330633756182443, 0.88660809793631534,
      0.87966678873718318, 0.87248439271319489, 0.8650629653998605,
      0.85740463455730964, 0.849511599584701, 0.84138613091138326,
      0.83303056936492714, 0.82444732551628019, 0.81563887900220489,
      0.806607777825255, 0.79735663763147435, 0.78788814096604876,
      0.77820503650715467, 0.76831013827826045, 0.75820632483908168,
      0.74789653845547166, 0.73738378424852247, 0.726671129323151,
      0.71576170187637078, 0.70465869028562811, 0.69336534217746215,
      0.68188496347673988, 0.6702209174367959, 0.65837662365084471,
      0.64635555704487113, 0.6341612468523965, 0.62179727557141318,
      0.60926727790386592, 0.59657493967794328, 0.58372399675358178,
      0.57071823391151888, 0.55756148372626146, 0.54425762542328526,
      0.53081058372086742, 0.51722432765695092, 0.50350286940135514,
      0.48965026305372161, 0.47567060342765943, 0.46156802482137793,
      0.4473466997752637, 0.4330108378167602, 0.41856468419299137,
      0.40401251859157283, 0.38935865384984858, 0.374607434653197,
      0.3597632362226898, 0.34483046299252873, 0.32981354727772971,
      0.31471694793246108, 0.2995451489994897, 0.28430265835112389,
      0.26899400632210413, 0.25362374433497059, 0.23819644351818925,
      0.22271669331760047, 0.20718910010162367, 0.19161828576064169,
      0.17600888630099895, 0.16036555043410147, 0.14469293816108825,
      0.12899571935347945, 0.11327857233027377, 0.097546182431989037,
      0.081803240592079, 0.066054441906178818, 0.050304484199618,
      0.034558066593758568, 0.018819888071535423, 0.0030946460426211631,
      -0.012612965091185119, -0.028298255369990422, -0.043956540708756112,
      -0.059583144328770127, -0.0751733981870467, -0.090722644403306435,
      -0.10622623668405921, -0.12167954174331005, -0.137077940719399,
      -0.15241683058760683, -0.16769162556800554, -0.18289775852809775,
      -0.19803068237982721, -0.21308587147050567, -0.22805882296720884,
      -0.2429450582341425, -0.25774012420262066, -0.27243959473320756,
      -0.28703907196947459, -0.30153418768308121, -0.3159206046096793,
      -0.33019401777519164, -0.344350155812134, -0.35838478226536147,
      -0.3722936968871271, -0.38607273692073391, -0.39971777837252048,
      -0.41322473727179504, -0.42658957091824229, -0.43980827911644482,
      -0.45287690539708025, -0.46579153822447489, -0.47854831219011684,
      -0.49114340919163124, -0.50357305959702248, -0.51583354339369381,
      -0.52792119132189086, -0.53983238599224448, -0.55156356298703679,
      -0.56311121194486158, -0.57447187762826013, -0.58564216097413047,
      -0.59661872012643058, -0.6073982714509647, -0.61797759053184,
      -0.62835351314934029, -0.638522936238935, -0.64848281883098957,
      -0.65823018297101965, -0.66776211462018042, -0.67707576453559093,
      -0.68616834913038594, -0.69503715131307986, -0.70367952130610645,
      -0.712092877443149, -0.72027470694512363, -0.72822256667452157,
      -0.73593408386787962, -0.74340695684615721, -0.75063895570280326,
      -0.7576279229692926, -0.7643717742579581, -0.77086849888183751,
      -0.77711616045147314, -0.78311289744836654, -0.78885692377498184,
      -0.79434652928108052, -0.79958008026631422, -0.80455601995881221,
      -0.80927286896969375, -0.81372922572338324, -0.81792376686352153,
      -0.82185524763445683, -0.82552250223810453, -0.82892444416614941,
      -0.83206006650748054, -0.83492844223070639, -0.83752872444177762,
      -0.839860146616574, -0.84192202280840966, -0.843713747830408,
      -0.84523479741270946, -0.84648472833446053, -0.84746317853055642,
      -0.84816986717312082, -0.84860459472772964, -0.84876724298431472,
      -0.84865777506284035, -0.84827623539368124, -0.84762274967277,
      -0.846697524791546, -0.84550084874170239, -0.84403309049482367,
      -0.84229469985693561, -0.84028620729804859, -0.838008223756748,
      -0.83546144041992343, -0.83264662847771853, -0.82956463885378162,
      -0.8262164019109608, -0.82260292713247807, -0.81872530277879885,
      -0.81458469552024737, -0.81018235004550854, -0.805519588646209,
      -0.80059781077767189, -0.79541849259602748, -0.7899831864718474,
      -0.78429352048044954, -0.77835119786910167, -0.77215799650123662,
      -0.765715768277961, -0.75902643853699725, -0.7520920054292779,
      -0.74491453927343, -0.73749618188835364, -0.72983914590413268,
      -0.7219457140515172, -0.71381823843019321, -0.70545913975616714,
      -0.69687090658841178, -0.68805609453512417, -0.67901732543983373,
      -0.66975728654766775, -0.66027872965195522, -0.650584470221613,
      -0.64067738650951389, -0.6305604186421061, -0.62023656769068725,
      -0.60970889472458478, -0.59898051984656986, -0.58805462121084928,
      -0.57693443402390576, -0.56562324952862431, -0.5541244139719419,
      -0.54244132755641039, -0.53057744337605239, -0.518536266336797,
      -0.50632135206191908, -0.49393630578277525, -0.481384781215322,
      -0.46867047942264467, -0.45579714766396051, -0.44276857823050042,
      -0.4295886072685714, -0.41626111359026174, -0.4027900174721179,
      -0.38917927944224612, -0.37543289905626831, -0.36155491366235587,
      -0.34754939715599442, -0.33342045872471948, -0.31917224158329288,
      -0.30480892169970025, -0.290334706512453, -0.2757538336395623,
      -0.26107056957960117, -0.24628920840528781, -0.23141407045008852,
      -0.21644950098812912, -0.20139986890794817, -0.18626956538050266,
      -0.17106300252185838, -0.1557846120509615, -0.1404388439429701,
      -0.12503016507858752, -0.10956305788978102, -0.094042019002381544,
      -0.078471557875954653, -0.062856195441449977, -0.047200462736980545,
      -0.031508899542197724, -0.015786053011774381, -3.6476308357569209E-5,
      0.015735272764607816, 0.031524633129624835, 0.047327041801102407,
      0.063137935250092328, 0.078952750767360663, 0.0947669278243155,
      0.11057590943142062, 0.12637514349362619, 0.14216008416241704,
      0.15792619318398388, 0.17366894124318152, 0.18938380930279478,
      0.20506628993767481, 0.22071188866335673, 0.23631612525874168,
      0.25187453508243252, 0.26738267038224128, 0.28283610159755562,
      0.29823041865412736, 0.31356123225080229, 0.32882417513789219,
      0.34401490338675583, 0.35912909765016765, 0.37416246441312856,
      0.389110737233634, 0.40396967797320782, 0.41873507801661292,
      0.43340275948044832, 0.44796857641032123, 0.4624284159661306,
      0.47677819959516138, 0.49101388419257042, 0.50513146324898273,
      0.51912696798483182, 0.53299646847101789, 0.54673607473566621,
      0.56034193785659514, 0.573810251039121, 0.58713725067895828,
      0.60031921740984484, 0.6133524771356158, 0.62623340204634315,
      0.63895841161835176, 0.65152397359773484, 0.66392660496709222,
      0.67616287289521915, 0.688229395669479, 0.70012284361058053,
      0.71183993996947059, 0.72337746180607421, 0.73473224084975652,
      0.74590116434104337, 0.75688117585454862, 0.76766927610277669,
      0.77826252372062932, 0.7886580360303419, 0.79885298978666053,
      0.80884462190208084, 0.81863023015193148, 0.82820717385905684,
      0.83757287455801643, 0.84672481663854327, 0.85566054796811608,
      0.86437768049347818, 0.87287389082096134, 0.88114692077545242,
      0.88919457793785739, 0.89701473616092664, 0.90460533606334781,
      0.9119643855019377, 0.91908996002184162, 0.92598020328466069,
      0.93263332747437522, 0.93904761368098066, 0.94522141226176726,
      0.95115314318016742, 0.956841296322103, 0.96228443178973988,
      0.96748118017266282, 0.97243024279638757, 0.97713039194815043,
      0.981580471080002, 0.98577939498915113, 0.98972614997554231,
      0.9934197939766769, 0.99685945667966336, 1.0000443396105325,
      1.002973716200799, 1.0056469318313117, 1.0080634038534391,
      1.0102226215876127, 1.0121241462992545, 1.0137676111521969,
      1.0151527211396107, 1.0162792529925193, 1.0171470550660069,
      1.0177560472031515, 1.018106220576815, 1.018197637509392,
      1.0180304312705748, 1.0176048058533158, 1.0169210357280405,
      1.0159794655752947, 1.0147805099969198, 1.0133246532059181,
      1.0116124486951503, 1.00964451888501, 1.0074215547502643,
      1.004944315426199, 1.0022136277942502, 0.99923038604732128,
      0.99599555123495265, 0.99251015078853788, 0.98877527802681775,
      0.98479209164181725, 0.98056181516544427, 0.97608573641702567,
      0.97136520693191808, 0.9664016413714851, 0.96119651691466779,
      0.95575137263138044, 0.95006780883796726, 0.94414748643501045,
      0.93799212622771821, 0.93160350822918114, 0.924983470946716,
      0.91813391065164329, 0.91105678063274809, 0.90375409043366961,
      0.89622790507457228, 0.88848034425835731, 0.88051358156171255,
      0.87232984361133858, 0.86393140924559619, 0.85532060866195381,
      0.8464998225505207, 0.83747148121395121, 0.82823806367414232,
      0.81880209676594018, 0.80916615421826688, 0.79933285572295465,
      0.78930486599167149, 0.779084893801228, 0.768675691027674,
      0.75808005166944392, 0.74730081086002942, 0.73634084387040188,
      0.72520306510160792, 0.71389042706794259, 0.70240591937093155,
      0.69075256766463444, 0.67893343261251937, 0.66695160883637028,
      0.65481022385750676, 0.64251243703074379, 0.63006143847150275,
      0.6174604479763306, 0.6047127139373436, 0.59182151225084456,
      0.57879014522061312, 0.56562194045614989, 0.55232024976630589,
      0.53888844804868141, 0.52532993217516033, 0.51164811987397352,
      0.49784644860862765, 0.48392837445420983, 0.46989737097127038,
      0.45575692807783974, 0.44151055091983171, 0.42716175874030748,
      0.412714083747936, 0.3981710699850079, 0.3835362721954918,
      0.36881325469334691, 0.35400559023166828, 0.33911685887282572,
      0.3241506468601959, 0.30911054549167793, 0.29400014999544805,
      0.27882305840837446, 0.26358287045734252, 0.24828318644396746,
      0.23292760613297805, 0.21751972764472916, 0.20206314635211625,
      0.18656145378226435, 0.17101823652342324, 0.15543707513735694,
      0.13982154307756603, 0.12417520561374149, 0.10850161876278455,
      0.092804328226679389, 0.077086868337690878, 0.0613527610110185,
      0.045605514705478023, 0.029848623392339846, 0.014085565532730465,
      -0.0016801969360007718, -0.017445219604836026, -0.033206076587999095,
      -0.048959361508157218, -0.064701688471385, -0.08042969303177766,
      -0.096140033145295262, -0.11182939011256141, -0.12749446951042903,
      -0.1431320021118388, -0.15873874479391856, -0.17431148143384811,
      -0.18984702379234814, -0.2053422123844986, -0.22079391733759612,
      -0.23619903923581068, -0.25155450995142065, -0.26685729346239323,
      -0.28210438665596088, -0.29729282011813452, -0.31241965890877277,
      -0.32748200332209321, -0.34247698963232887, -0.35740179082439405,
      -0.37225361730931411, -0.38702971762419669, -0.40172737911663936,
      -0.416343928613269, -0.43087673307237434, -0.44532320022028904,
      -0.45968077917152439, -0.4739469610323962, -0.48811927948797595,
      -0.50219531137230256, -0.51617267722160876, -0.5300490418105388,
      -0.54382211467109376, -0.5574896505943181, -0.57104945011452912,
      -0.58449935997596447, -0.5978372735818186, -0.61106113142550389,
      -0.62416892150408665, -0.63715867971375961, -0.65002849022738884,
      -0.662776485853871, -0.67540084837947423, -0.68789980889088365,
      -0.70027164808004372, -0.7125146965307384, -0.724627334986747,
      -0.736607994601743, -0.74845515717073363, -0.76016735534313506,
      -0.77174317281740379, -0.78318124451726157, -0.79448025674952172,
      -0.80563894734344654, -0.81665610577178516, -0.82753057325336732,
      -0.838261242837401, -0.84884705946943184, -0.859287020039033,
      -0.86958017340929517, -0.87972562042813185, -0.8897225139214473,
      -0.89957005866831685, -0.90926751135816974, -0.91881418053007136,
      -0.928209426494214, -0.93745266123569448, -0.94654334830068687,
      -0.9554810026650622, -0.9642651905856604, -0.97289552943424318,
      -0.98137168751427284, -0.98969338386070582, -0.99786038802279975,
      -1.0058725198302623, -1.0137296491426622, -1.0214316955824703,
      -1.028978628251739, -1.0363704654326291, -1.0436072742719844,
      -1.0506891704500405, -1.0576163178335614, -1.0643889281134675,
      -1.0710072604272276, -1.0774716209662047, -1.0837823625680545,
      -1.0899398842945243, -1.0959446309947478, -1.1017970928543128,
      -1.1074978049302695, -1.1130473466723514, -1.1184463414305754,
      -1.1236954559495225, -1.128795399849468, -1.133746925094621,
      -1.1385508254487502, -1.1432079359183875, -1.1477191321838986,
      -1.152085330018652, -1.1563074846965602, -1.16038659038824,
      -1.1643236795460747, -1.1681198222784355, -1.1717761257133077,
      -1.1752937333516589, -1.1786738244107595, -1.1819176131577835,
      -1.1850263482339414, -1.188001311969457, -1.1908438196896496,
      -1.193555219012435, -1.1961368891375246, -1.1985902401276312,
      -1.2009167121819615, -1.2031177749022934, -1.2051949265519841,
      -1.20714969330814, -1.2089836285073097, -1.2106983118849926,
      -1.2122953488092443, -1.2137763695087354, -1.2151430282955207,
      -1.2163970027828916, -1.2175399930985453, -1.2185737210934655,
      -1.2194999295467739, -1.2203203813668833, -1.2210368587892788,
      -1.2216511625712121, -1.2221651111836613, -1.2225805400008407,
      -1.2228993004876068, -1.2231232593850294, -1.2232542978944962,
      -1.2232943108606358, -1.2232452059533738, -1.2231089028494397,
      -1.2228873324136551, -1.222582435880267, -1.2221961640347074,
      -1.2217304763960308, -1.2211873404003477, -1.2205687305856086,
      -1.2198766277779747, -1.2191130182801384, -1.218279893061867,
      -1.2173792469530726, -1.2164130778397206, -1.2153833858628709,
      -1.214292172621126, -1.2131414403768308, -1.2119331912662392,
      -1.2106694265140132, -1.2093521456522984, -1.207983345744658,
      -1.2065650206151717, -1.2050991600829526, -1.2035877492023721,
      -1.2020327675092646, -1.2004361882733634, -1.1987999777572753,
      -1.1971260944822029, -1.1954164885007175, -1.1936731006768131,
      -1.191897861973523, -1.1900926927482955, -1.1882595020564466,
      -1.1864001869628547, -1.1845166318621971, -1.1826107078079362,
      -1.1806842718502586, -1.1787391663832534, -1.1767772185014957,
      -1.1748002393662791, -1.1728100235817038, -1.1708083485808283,
      -1.168796974022084, -1.1667776411961663, -1.1647520724435694,
      -1.1627219705829943, -1.160689018350765, -1.1586548778514758,
      -1.1566211900200383, -1.1545895740952568, -1.1525616271051617,
      -1.1505389233642132, -1.1485230139825406, -1.146515426387388,
      -1.1445176638568793, -1.1425312050662684, -1.140557503646789,
      -1.1385979877572532, -1.1366540596684924, -1.1347270953608048,
      -1.1328184441344664, -1.1309294282334503, -1.1290613424824549,
      -1.1272154539373174, -1.1253930015489098, -1.1235951958406225,
      -1.1218232185994799, -1.1200782225809975, -1.1183613312278049,
      -1.1166736384021636, -1.1150162081323465, -1.1133900743730196,
      -1.1117962407796151, -1.1102356804967406, -1.1087093359606903,
      -1.1072181187160468, -1.1057629092464212, -1.104344556819342,
      -1.1029638793452929, -1.1016216632509326, -1.1003186633664583,
      -1.099055602827133, -1.0978331729889703, -1.0966520333585215,
      -1.0955128115368, -1.0944161031772528, -1.0933624719577895,
      -1.092352449566814, -1.091386535703204, -1.0904651980902103,
      -1.08958887250318, -1.0887579628111124, -1.0879728410318814,
      -1.0872338474011545, -1.0865412904548375, -1.0858954471250493,
      -1.0852965628494708, -1.0847448516939835, -1.084240496488555,
      -1.0837836489761932, -1.0833744299748982, -1.0830129295525062,
      -1.0826992072142749, -1.0824332921031208, -1.0822151832123525,
      -1.0820448496107691, -1.0819222306800189, -1.0818472363640161,
      -1.0818197474303344, -1.0818396157433621, -1.081906664549112,
      -1.0820206887714869, -1.0821814553198812, -1.0823887034078927,
      -1.0826421448830035, -1.082941464567069, -1.0832863206073848,
      -1.083676344838185, -1.0841111431523662, -1.0845902958832463,
      -1.0851133581961743, -1.0856798604897335, -1.0862893088064529,
      -1.0869411852526611, -1.0876349484273886, -1.088370033860107,
      -1.0891458544569679, -1.0899618009554641, -1.0908172423872144,
      -1.0917115265486297, -1.0926439804792945, -1.0936139109477729,
      -1.0946206049446385, -1.0956633301824747, -1.0967413356025981,
      -1.0978538518883041, -1.0990000919843288, -1.1001792516223323,
      -1.1013905098521428, -1.1026330295784696, -1.1039059581028983,
      -1.1052084276708802, -1.1065395560234552, -1.1078984469534481,
      -1.1092841908659259, -1.1106958653425734, -1.1121325357098208,
      -1.1135932556103847, -1.1150770675779944, -1.1165830036150588,
      -1.1181100857729356, -1.119657326734651, -1.1212237303996941,
      -1.1228082924706755, -1.1244100010415932, -1.1260278371874,
      -1.1276607755546411, -1.1293077849528741, -1.1309678289466099,
      -1.1326398664475079, -1.1343228523065776, -1.136015737906084,
      -1.1377174717509224, -1.1394270000591833, -1.1411432673516564,
      -1.1428652170400013, -1.1445917920133089, -1.1463219352228324,
      -1.1480545902645953, -1.1497887019596209, -1.1515232169315388,
      -1.1532570841813135, -1.1549892556588153, -1.1567186868310326,
      -1.158444337246608, -1.1601651710965148, -1.1618801577705873,
      -1.1635882724096627, -1.1652884964531138, -1.1669798181815252,
      -1.1686612332542494, -1.1703317452416537, -1.171990366151781,
      -1.1736361169512288, -1.1752680280799936, -1.1768851399600813,
      -1.1784865034976415, -1.1800711805784152, -1.1816382445562785,
      -1.1831867807346887, -1.1847158868407905, -1.1862246734920086,
      -1.1877122646548952, -1.189177798096074, -1.1906204258250404,
      -1.1920393145286721, -1.1934336459972075, -1.194802617541582,
      -1.1961454424018703, -1.1974613501467024, -1.1987495870634741,
      -1.2000094165391728, -1.2012401194316724, -1.2024409944313212,
      -1.2036113584126822, -1.2047505467762725, -1.2058579137801402,
      -1.2069328328611741, -1.207974696945963, -1.2089829187511074,
      -1.2099569310728457, -1.2108961870658668, -1.2118001605111908,
      -1.2126683460730205, -1.2135002595444304, -1.2142954380818156,
      -1.2150534404279703, -1.2157738471237445, -1.2164562607081466,
      -1.217100305906839, -1.2177056298089302, -1.2182719020320016,
      -1.2187988148752937, -1.2192860834609922, -1.2197334458635467,
      -1.2201406632269913, -1.2205075198701805, -1.2208338233799523,
      -1.2211194046921239, -1.2213641181603272, -1.2215678416126476,
      -1.2217304763960297, -1.221851947408465, -1.22193220311891,
      -1.2219712155749669, -1.2219689803983078, -1.2219255167678453,
      -1.221840867390666, -1.2217150984607481, -1.2215482996054685,
      -1.2213405838199385, -1.2210920873892017, -1.2208029697983083,
      -1.2204734136303417, -1.220103624452415, -1.2196938306897129,
      -1.2192442834876076, -1.2187552565619486, -1.218227046037563,
      -1.217659970275059, -1.2170543696859886, -1.2164106065364861,
      -1.2157290647394356, -1.2150101496352808, -1.2142542877615752,
      -1.2134619266113633, -1.2126335343805077, -1.2117695997040854,
      -1.2108706313819428, -1.2099371580935681, -1.2089697281023697,
      -1.2079689089495229, -1.2069352871375036, -1.2058694678034547,
      -1.204772074382533, -1.2036437482613731, -1.2024851484218357,
      -1.201296951075207, -1.2000798492869658, -1.1988345525923576,
      -1.1975617866028623, -1.1962622926038065, -1.1949368271432472,
      -1.1935861616123313, -1.1922110818173079, -1.190812387543386,
      -1.1893908921106457, -1.1879474219221606, -1.1864828160045853,
      -1.184997925541357, -1.1834936133987615, -1.1819707536450583,
      -1.1804302310628523, -1.1788729406549938, -1.1772997871441409,
      -1.1757116844662945, -1.1741095552584473, -1.1724943303406474,
      -1.1708669481926601, -1.1692283544254802, -1.1675795012479167,
      -1.1659213469285143, -1.1642548552530283, -1.1625809949776875,
      -1.1609007392785233, -1.1592150651969764, -1.1575249530820648,
      -1.1558313860293115, -1.1541353493167494, -1.152437829838191,
      -1.1507398155340616, -1.1490422948200509, -1.1473462560138081,
      -1.1456526867599601, -1.1439625734537189, -1.1422769006633335,
      -1.1405966505516232, -1.1389228022969038, -1.1372563315135154,
      -1.1355982096722474, -1.1339494035209285, -1.1323108745054125,
      -1.1306835781912621, -1.1290684636863484, -1.1274664730647066,
      -1.125878540791819, -1.1243055931516475, -1.1227485476756738,
      -1.1212083125741874, -1.1196857861701024, -1.1181818563355619,
      -1.1166973999315859, -1.1152332822510154, -1.1137903564650335,
      -1.1123694630734986, -1.1109714293593693, -1.1095970688474379,
      -1.108247180767685, -1.1069225495234412, -1.1056239441646438,
      -1.1043521178664806, -1.1031078074135376, -1.1018917326898454,
      -1.1007045961749689, -1.0995470824464286, -1.098419857688649,
      -1.0973235692087451, -1.0962588449592812, -1.0952262930683219,
      -1.0942265013769605, -1.0932600369845513, -1.0923274458018788,
      -1.0914292521124986, -1.0905659581424119, -1.0897380436383832,
      -1.0889459654550111, -1.0881901571508223, -1.0874710285935796,
      -1.0867889655749892, -1.0861443294350384, -1.0855374566961229,
      -1.0849686587071599, -1.0844382212979053, -1.0839464044436076,
      -1.0834934419402378, -1.0830795410903962, -1.0827048824001257,
      -1.0823696192868055, -1.0820738777981933, -1.0818177563429199,
      -1.0816013254324501, -1.0814246274347499, -1.0812876763397687,
      -1.0811904575368907, -1.0811329276044517, -1.0811150141115329,
      -1.08113661543206, -1.0811976005714004, -1.0812978090055616,
      -1.0814370505330528, -1.0816151051395944, -1.0818317228757188,
      -1.0820866237473659, -1.0823794976196037, -1.0827100041335074,
      -1.0830777726363041, -1.0834824021248719, -1.0839234612026218,
      -1.0844004880498861, -1.08491299040781, -1.08546044557584,
      -1.0860423004228648, -1.0866579714120008, -1.0873068446391374,
      -1.0879882758851909, -1.0887015906821587, -1.0894460843929596,
      -1.0902210223051094, -1.0910256397381686, -1.0918591421650794,
      -1.0927207053472836, -1.0936094754836783, -1.0945245693733781,
      -1.0954650745922607, -1.0964300496832817, -1.0974185243605301,
      -1.0984294997269659, -1.0994619485058532, -1.1005148152857678,
      -1.1015870167791997, -1.1026774420946484, -1.103784953022156,
      -1.1049083843322267, -1.1060465440880405, -1.1071982139708876,
      -1.1083621496187426, -1.1095370809778751, -1.1107217126674245,
      -1.1119147243568168, -1.1131147711559046, -1.1143204840177754,
      -1.1155304701540349, -1.1167433134624918, -1.1179575749671187,
      -1.1191717932701097, -1.1203844850159554, -1.1215941453673461,
      -1.1227992484927831, -1.1239982480657202, -1.1251895777751018,
      -1.1263716518471114, -1.1275428655779787, -1.1287015958776614,
      -1.1298462018242301, -1.1309750252287656, -1.1320863912105925,
      -1.1331786087826381, -1.1342499714467549, -1.1352987577987543,
      -1.1363232321429992, -1.1373216451163011, -1.1382922343209425,
      -1.1392332249665849, -1.1401428305208452, -1.1410192533683163,
      -1.1418606854778024, -1.1426653090775294, -1.1434312973381073,
      -1.14415681506297, -1.1448400193860908, -1.1454790604766993,
      -1.1459464059774003, -1.1461143340306881, -1.1459808342024946,
      -1.1455440712609106, -1.1448023900120039, -1.1437543200153912,
      -1.1423985801695693, -1.1407340831571831, -1.1387599397404791,
      -1.1364754628972564, -1.1338801717877804, -1.1309737955432702,
      -1.1277562768667093, -1.1242277754368912, -1.1203886711068918,
      -1.1162395668882195, -1.1117812917122638, -1.107014902960842,
      -1.101941688757903, -1.0965631700147447, -1.0908811022213944,
      -1.08489747697708, -1.0786145232531001, -1.0720347083816875,
      -1.0651607387648387, -1.0579955602974824, -1.0505423584996307,
      -1.0428045583527314, -1.0347858238356522, -1.0264900571562876,
      -1.0179213976751724, -1.0090842205178463, -0.99998313487332369,
      -0.99062298197632326, -0.98100883277148487, -0.97114598525821616,
      -0.9610399615153562, -0.95069650440526721, -0.9401215739575105,
      -0.929321343432748, -0.91830219506798594, -0.90707071550488094,
      -0.89563369090316713, -0.8839981017420121, -0.87217111731236974,
      -0.860160089904113, -0.84797254869213323, -0.83561619332615067,
      -0.82309888722944613, -0.81042865061230074, -0.79761365320634525,
      -0.784662206726583, -0.77158275706831825, -0.75838387624670878,
      -0.74507425408712347, -0.73166268967497061, -0.71815808257412683,
      -0.70456942382352894, -0.69090578672192271, -0.67717631741124851,
      -0.66339022526944247, -0.6495567731239682, -0.63568526729769881,
      -0.62178504749913166, -0.60786547656934753, -0.59393593009839252,
      -0.58000578592415175, -0.56608441352701933, -0.552181163334043,
      -0.538305355946412, -0.52446627130446577, -0.51067313780463663,
      -0.49693512138287743, -0.483261314579435, -0.46966072559988825,
      -0.45614226738760077, -0.44271474672283578, -0.42938685336385007,
      -0.41616714924546716, -0.40306405775056703, -0.39008585307005533,
      -0.37724064966687049, -0.3645363918595424, -0.35198084354082815,
      -0.33958157804686451, -0.32734596819222256, -0.31528117648608522,
      -0.30339414554475491, -0.29169158871539391, -0.28017998092586283,
      -0.2688655497752368, -0.25775426687938557, -0.24685183948575637,
      -0.23616370237121154, -0.22569501003652212, -0.21545062921072627,
      -0.20543513167832742, -0.1956527874418286, -0.18610755823183192,
      -0.176803091376433, -0.16774271404129723, -0.15892942785129038,
      -0.15036590390412571, -0.14205447818599284, -0.13399714739859572,
      -0.12619556520659841, -0.11865103891382259, -0.11136452657609874,
      -0.10433663455804017, -0.097567615540445879, -0.0910573669844486,
      -0.084805430057900866, -0.078810989028894371, -0.07307287113062938,
      -0.067589546901276845, -0.062359131001739641, -0.0573793835136322,
      -0.05264771171907652, -0.048161172363255685, -0.043916474399989816,
      -0.039909982219887057, -0.036137719359961393, -0.032595372692881916,
      -0.029278297093355329, -0.026181520578408928, -0.023299749917684843,
      -0.02062737670911784, -0.018158483914712469, -0.015886852850421428,
      -0.013805970623449031, -0.011909038009626864, -0.010188977762823563,
      -0.00863844334770249, -0.00724982808645966, -0.006015274709552652,
      -0.0049266852997690179, -0.0039757316183765823, -0.0031538658014733916,
      -0.0024523314140606147, -0.0018621748487766545, -0.0013742570556593194,
      -0.00097926558875558074, -0.00066772695485655157, -0.00043001924912493028,
      -0.00025638506188096246, -0.00013694464033645726, -6.1709288610619563E-5,
      -2.05949889251616E-5, -3.43622646493792E-6, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.9582231684428249E-6,
      -1.5674251071455414E-5, -5.2921267582773956E-5, -0.00012547321155551518,
      -0.00024508706528953404, -0.00042348507063318688, -0.00067233689788138789,
      -0.0010032417928379103, -0.0014277107275800032, -0.00195714858059555,
      -0.0026028363720585397, -0.0033759135800656222, -0.0042873605636760083,
      -0.0053479811185779694, -0.006568385191147422, -0.00795897177656873,
      -0.009529912026552961, -0.011291132592015654, -0.013252299225865327,
      -0.015422800670803491, -0.017811732856749692, -0.020427883432178884,
      -0.023279716653295444, -0.026375358654568158, -0.029722583123712603,
      -0.033328797403735087, -0.037201029044142582, -0.041345912822879333,
      -0.045769678259973037, -0.050478137643260458, -0.055476674585918331,
      -0.060770233134847765, -0.066363307448252654, -0.072259932060013743,
      -0.078463672747692573, -0.084977618020203788, -0.091804371240369526,
      -0.098946043396723388, -0.106404246538054, -0.11418008788328254,
      -0.12227416461834729, -0.13068655939082841, -0.13941683651208062,
      -0.14846403887566834, -0.15782668559989438, -0.16750277040120395,
      -0.17748976070422059, -0.18778459749312459, -0.19838369590804328,
      -0.20928294658905311, -0.22047771776932759, -0.23196285811789544,
      -0.24373270033138145, -0.25578106547302992, -0.26810126805621914,
      -0.28068612186858832, -0.29352794653181807, -0.306618574791022,
      -0.31994936052662587, -0.33351118748055059, -0.34729447868743918,
      -0.36128920660062447, -0.37548490390148936, -0.38987067497983696,
      -0.40443520807188116, -0.41916678804145957, -0.43405330978909679,
      -0.4490822922725739, -0.464240893121726, -0.47951592382925867,
      -0.4948938654984873, -0.51036088512801725, -0.525902852412548,
      -0.541505357038155, -0.55715372644961658, -0.57283304406659086,
      -0.58852816792471985, -0.60422374971703374, -0.61990425421037521,
      -0.63555397901092148, -0.6511570746523021, -0.66669756497923816,
      -0.68215936779912723, -0.69752631577349422, -0.71278217752081807,
      -0.72791067890180727, -0.74289552445786844, -0.757720418973171,
      -0.77236908913044788, -0.78682530523043048, -0.80107290294463,
      -0.81509580507102142, -0.82887804326209957, -0.84240377969469571,
      -0.85565732865094546, -0.8686231779798238, -0.88128601040872789,
      -0.893630724674726, -0.90564245644523467, -0.91730659899810529,
      -0.92860882363136266, -0.93953509977310556, -0.95007171476245178,
      -0.96020529327277948, -0.96992281634893729, -0.9792116400305797,
      -0.9880595135342819, -0.99645459696765015, -1.0043854785492323,
      -1.0118411913086629, -1.0188112292421549, -1.025285562899162,
      -1.0312546543767644, -1.0367094716991425, -1.0416415025602923,
      -1.046042767409008, -1.0499058318560361, -1.0532238183842135,
      -1.0559904173433634, -1.0581998972126847, -1.0598471141143826,
      -1.0609275205633135, -1.0614371734384684, -1.0613727411632055,
      -1.0607315100822283, -1.0595113900244411, -1.0577109190419296,
      -1.0553292673164922, -1.0523662402263019, -1.0488222805664622,
      -1.0446984699184292, -1.0399965291644531, -1.0347188181444364,
      -1.0288683344537968, -1.0224487113821679, -1.0154642149939872,
      -1.0079197403532585, -0.9998208068959975, -0.991173552955096,
      -0.98198472944357063, -0.972261692703361, -0.96201239652806947,
      -0.95124538336921827, -0.93996977473679111, -0.92819526080600612,
      -0.91593208924341274, -0.903191053266559, -0.88998347895259533,
      -0.87632121181227862, -0.86221660264693178, -0.84777545829077827,
      -0.833097582233531, -0.81818674629387633, -0.8030467960400639,
      -0.78768164978459831, -0.77209529755372419, -0.756291800032005,
      -0.74027528748228644, -0.72404995864136656, -0.70762007959168494,
      -0.69098998260936262, -0.674164064988928, -0.6571467878450743,
      -0.639942674891804, -0.62255631119931554, -0.60499234192901241,
      -0.58725547104700038, -0.56935046001646616, -0.55128212646933117,
      -0.533055342857573, -0.5146750350846333, -0.49614618111731695,
      -0.47747380957861607, -0.45866299832187685, -0.43971887298675572,
      -0.42064660553740374, -0.40145141278332797, -0.38213855488338722,
      -0.36271333383338838, -0.34318109193774793, -0.32354721026569128,
      -0.30381710709248133, -0.28399623632614984, -0.264090085920231,
      -0.24410417627299469, -0.22404405861368043, -0.20391531337623631,
      -0.18372354856108375, -0.16347439808541797, -0.14317352012256829,
      -0.12282659543094732, -0.10243932567311453, -0.082017431725491363,
      -0.061566651979268472, -0.041092740633042357, -0.020601465977729272,
      -9.8608674303890531E-5, 0.020410039975080618, 0.040918679762044885,
      0.061421503312442394, 0.081912697831769576, 0.10238644685496218,
      0.1228369320000201, 0.14325833472487676, 0.16364483808697078,
      0.18399062850492431, 0.20428989752176974, 0.22453684356915715,
      0.24472567373195026, 0.26485060551266032, 0.28490586859511624,
      0.30488570660682468, 0.32478437887941553, 0.34459616220661948,
      0.364315352599186, 0.38393626703618194, 0.40345324521207493,
      0.42286065127905281, 0.44215287558398031, 0.46132433639944564,
      0.48036948164830096, 0.4992827906211541, 0.5180587756862185,
      0.53669198399097828, 0.5551769991550819, 0.57350844295393366,
      0.59168097699238731, 0.60968930436802038, 0.62752817132341365,
      0.64519236888689357, 0.66267673450119124, 0.67997615363947639,
      0.69708556140822053, 0.7139999441363567, 0.73071434095020948,
      0.74722384533365638, 0.76352360667300989, 0.7796088317860872,
      0.795474786434972, 0.8111167968219396, 0.82653025106805855,
      0.8417106006739562, 0.856653361962269, 0.87135411750127223,
      0.88580851750923006, 0.90001228123896826, 0.91396119834221357,
      0.92765113021323342, 0.94107801131131608, 0.95423785046164089,
      0.96712673213410538, 0.97974081769965571, 0.99207634666370459,
      1.0041296378762103, 1.0158970907179998, 1.0273751862629286,
      1.0385604884154871, 1.0494496450234476, 1.0600393889651742,
      1.0703265392112273, 1.0803080018598827, 1.0899807711462146,
      1.099341930424389, 1.1083886531228262, 1.1171182036718998,
      1.1255279384038479, 1.1336153064245751, 1.1413778504570535,
      1.1488132076560091, 1.1559191103936173, 1.1626933870159224,
      1.1691339625697212, 1.1752388594996372, 1.1810061983151532,
      1.1864341982273465, 1.1915211777551091, 1.1962655553006292,
      1.2006658496939182, 1.2047206807061972, 1.2084287695319373,
      1.2117889392393908, 1.2148001151894314, 1.2174613254225521,
      1.2197717010138758, 1.2217304763960306, 1.2233369896497757,
      1.2245906827622521, 1.2254911018527612, 1.226037897365966,
      1.2262308242324462, 1.2260697419965194, 1.2255546149112724,
      1.2246855120007574, 1.2234626070893004, 1.2218861787979034,
      1.2199566105077142, 1.2176743902905622, 1.2150401108065612,
      1.2120544691687871, 1.2087182667750724, 1.2050324091069335,
      1.2009979054956954, 1.1966158688558577, 1.1918875153857853,
      1.1868141642357894, 1.1813972371437012, 1.1756382580380333,
      1.1695388526088455, 1.1631007478464357, 1.1563257715479889,
      1.1492158517923374, 1.141773016382974, 1.1339993922594993,
      1.125897204877669, 1.117468777558233, 1.1087165308047653,
      1.0996429815906921, 1.0902507426157313, 1.0805425215319842,
      1.070521120139905, 1.0601894335544118, 1.0495504493413796,
      1.0386072466248077, 1.027362995164919, 1.0158209544074976,
      1.0039844725047467, 0.99185698530799615, 0.97944201533255137,
      0.96674317069503868, 0.953764144023559, 0.94050871134101255,
      0.92698073092194133, 0.9131841421232566, 0.89912296418921833,
      0.88480129503105542, 0.87022330998161546, 0.85539326052543185,
      0.84031547300463494, 0.82499434730109589, 0.80943435549525644,
      0.79364004050204406, 0.77761601468434116, 0.76136695844442692,
      0.74489761879387006, 0.728212807902312, 0.7113174016256294,
      0.69421633801392935, 0.67691461579988066, 0.65941729286785389,
      0.64172948470437652, 0.6238563628303937, 0.60580315321585765,
      0.587575134677141, 0.56917763725781356, 0.55061604059329128,
      0.53189577225990048, 0.51302230610888333, 0.49400116058589749,
      0.47483789703654444, 0.45553811799848754, 0.43610746548071067,
      0.4165516192304769, 0.39687629498855825, 0.37708724273329025,
      0.35719024491404849, 0.337191114674692, 0.31709569406758142,
      0.29690985225873412, 0.27663948372471825, 0.25629050644185475,
      0.23586886006834429, 0.21538050411988224, 0.1948314161393894,
      0.17422758986142803, 0.15357503337192835, 0.13287976726379896,
      0.11214782278905838, 0.091385240008054813, 0.070598065936411991,
      0.049792352690283814, 0.028974155630540954, 0.00814953150647929,
      -0.012675463400320386, -0.033494775131399146, -0.054302353905465339,
      -0.075092155970480079, -0.09585814545318383, -0.11659429620544109,
      -0.13729459364682278, -0.15795303660279791, -0.17856363913795392,
      -0.19912043238363464, -0.21961746635939977, -0.24004881178771126,
      -0.26040856190125539, -0.28069083424230035, -0.30088977245351578,
      -0.32099954805964986, -0.341014362239499, -0.36092844758757664,
      -0.38073606986491931, -0.40043152973844387, -0.42000916450828862,
      -0.43946334982260121, -0.45878850137916116, -0.47797907661333561,
      -0.49702957637177436, -0.51593454657133686, -0.53468857984267337,
      -0.55328631715794474, -0.57172244944215422, -0.58999171916754212,
      -0.6080889219305603, -0.62600890801087727, -0.64374658391192874,
      -0.66129691388250078, -0.67865492141886785, -0.695815690746973,
      -0.71277436828418872, -0.7295261640801719, -0.74606635323636061,
      -0.76239027730363751, -0.77849334565770767, -0.79437103685176025,
      -0.81001889994596432, -0.8254325558133716, -0.84060769842180638,
      -0.85554009609133019, -0.87022559272687117, -0.8846601090256353,
      -0.8988396436588898, -0.91276027442775431, -0.92641815939264,
      -0.93980953797594113, -0.95293073203766587, -0.96577814692362829,
      -0.978348272485908, -0.99063768407520447, -1.0026430435048128,
      -1.0143610999859012, -1.0257886910337735, -1.0369227433448853,
      -1.04776027364427, -1.0582983895031706, -1.0685342901265744,
      -1.0784652671104458, -1.0880887051683885, -1.0974020828275353,
      -1.1064029730934408, -1.1150890440837826, -1.1234580596306687,
      -1.1315078798513731, -1.1392364616873305, -1.1466418594112326,
      -1.1537222251020642, -1.1604758090879579, -1.1669009603567226,
      -1.1729961269339428, -1.1787598562285371, -1.1841907953456827,
      -1.1892876913670163, -1.1940493915980568, -1.1984748437827659,
      -1.2025630962852185, -1.2063132982383207, -1.2097246996595759,
      -1.21279665153386, -1.2155286058632084, -1.2179201156836281,
      -1.2199708350489407, -1.22168051898169, -1.2230490233911588,
      -1.2240763049585439, -1.224762420989336, -1.2251075292330127,
      -1.2251118876700893, -1.2247758542666531, -1.224099886696473,
      -1.2230845420308054, -1.2217304763960306, -1.2200384445992452,
      -1.2180092997219822, -1.2156439926821996, -1.2129435717647215,
      -1.2099091821203127, -1.206542065233581, -1.2028435583598989,
      -1.1988150939315916, -1.1944581989335683, -1.1897744942486788,
      -1.1847656939730173, -1.1794336047014222, -1.1737801247834632,
      -1.1678072435501667, -1.1615170405117832, -1.1549116845268768,
      -1.1479934329430597, -1.1407646307096684, -1.1332277094627217,
      -1.1253851865824849, -1.1172396642239824, -1.1087938283208199,
      -1.1000504475626725, -1.0910123723467966, -1.0816825337039744,
      -1.0720639421992382, -1.0621596868078134, -1.0519729337666464,
      -1.0415069254019547, -1.0307649789332087, -1.0197504852539787,
      -1.008466907690079, -0.99691778073544823, -0.98510670876623907,
      -0.97303736473354474, -0.96071348883525154, -0.948138887167481,
      -0.93531743035609349, -0.92225305216876219, -0.90894974810808671,
      -0.89541157398624549, -0.881642644481719, -0.86764713167855489,
      -0.85342926358873472, -0.83899332265811222, -0.82434364425650886,
      -0.80948461515245362, -0.79442067197312816, -0.77915629965004962,
      -0.76369602985104212, -0.74804443939905463, -0.73220614867836886,
      -0.71618582002875875, -0.6999881561281871, -0.68361789836456277,
      -0.66707982519719045, -0.65037875050841254, -0.63351952194609851,
      -0.61650701925749618, -0.59934615261506985, -0.58204186093490184,
      -0.56459911018821152, -0.54702289170664631, -0.529318220481866,
      -0.51149013346007288, -0.49354368783203656, -0.47548395931923204,
      -0.45731604045669338, -0.43904503887316149, -0.42067607556913295,
      -0.4022142831934114, -0.38366480431875682, -0.36503278971724068,
      -0.34632339663587125, -0.32754178707314247, -0.30869312605704713,
      -0.28978257992519968, -0.27081531460762, -0.25179649391280096,
      -0.23273127781764982, -0.21362482076188047, -0.19448226994745449,
      -0.17530876364365394, -0.15610942949837672, -0.13688938285623473,
      -0.11765372508402105, -0.098407541904138279, -0.0791559017365529,
      -0.059903854049850713, -0.040656427721955074, -0.021418629411060819,
      -0.0021954419373714507, 0.01700817732384742, 0.036187298037298463,
      0.055337018490285869, 0.074452467162336222, 0.093528804281339958,
      0.11256122336562922, 0.13154495275150369, 0.15047525710566811,
      0.16934743892206292, 0.1881568400025895, 0.20689884292122887,
      0.22556887247104432, 0.24416239709359458, 0.26267493029025057,
      0.28110203201498, 0.2994393100480765, 0.31768242135041891,
      0.33582707339777079, 0.35386902549468324, 0.37180409006758652,
      0.38962813393657486, 0.40733707956552906, 0.42492690629010565,
      0.44239365152321797, 0.45973341193759071, 0.47694234462499263,
      0.49401666823177659, 0.51095266407034556, 0.52774667720616952,
      0.54439511752000991, 0.5608944607449794, 0.57724124947814193,
      0.59343209416625575, 0.60946367406541269, 0.62533273817419155,
      0.64103610614008377, 0.6565706691388582, 0.67193339072659852,
      0.68712130766413915, 0.70213153071364243, 0.71696124540704742,
      0.73160771278617065, 0.74606827011420074, 0.76034033155840186,
      0.77442138884376521, 0.78830901187745872, 0.8020008493438473,
      0.81549462926991145, 0.82878815956092722, 0.84187932850619274,
      0.8547661052547002, 0.8674465402605972, 0.87991876569832006,
      0.8921809958472684, 0.904231527445938, 0.91606874001540151,
      0.927691096152071, 0.93909714178965764, 0.9502855064302731,
      0.961254903344626, 0.97200412974128758, 0.98253206690496664,
      0.99283768030381658, 1.0029200196657444, 1.0127782190237484,
      1.0224114967302804, 1.0318191554406835, 1.0410005820657249,
      1.0499552476933074, 1.0586827074793725, 1.0671826005081242,
      1.0754546496216135, 1.083498661218806, 1.0913145250242238,
      1.0989022138262987, 1.1062617831855319, 1.1133933711126371,
      1.1202971977167877, 1.1269735648241486, 1.1334228555668493,
      1.1396455339425851, 1.1456421443450473, 1.1514133110653721,
      1.1569597377648244, 1.1622822069189485, 1.1673815792334097,
      1.172258793031776, 1.176914863615488, 1.1813508825962846,
      1.1855680172013694, 1.1895675095515714, 1.1933506759128192,
      1.1969189059212311, 1.2002736617821108, 1.2034164774431988,
      1.2063489577424753, 1.2090727775308965, 1.2115896807703739,
      1.2139014796073742, 1.2160100534225105, 1.2179173478564711,
      1.2196253738127105, 1.2211362064372451, 1.2224519840760117,
      1.2235749072101303, 1.2245072373695409, 1.2252512960254087,
      1.2258094634617325, 1.2261841776266029, 1.2263779329635436,
      1.2263932792233905, 1.2262328202571817, 1.2258992127905006,
      1.225395165179763, 1.2247234361509123, 1.2238868335210349,
      1.2228882129033352, 1.2217304763960311, 1.2204165712556239,
      1.2189494885550674, 1.2173322618273557, 1.2155679656950316,
      1.2136597144861603, 1.2116106608372852, 1.2094239942838794,
      1.2071029398388777, 1.2046507565597784, 1.2020707361048997,
      1.199366201279306, 1.1965405045709965, 1.1935970266778733,
      1.1905391750260674, 1.1873703822801884, 1.1840941048460503,
      1.1807138213664503, 1.1772330312105728, 1.1736552529575646,
      1.1699840228749128, 1.1662228933921222, 1.1623754315703481,
      1.1584452175685005, 1.1544358431064414, 1.1503509099258393,
      1.1461940282492524, 1.1419688152380472, 1.1376788934497089,
      1.1333278892951488, 1.1289194314965694, 1.1244571495464855,
      1.1199446721684818, 1.115385625780259, 1.1107836329596086,
      1.1061423109138144, 1.101465269953132, 1.096756111968878,
      1.0920184289167092, 1.0872558013056755, 1.0824717966936002,
      1.0776699681893742, 1.0728538529626999, 1.0680269707618744,
      1.0631928224401535, 1.0583548884912535, 1.0535166275945516,
      1.0486814751705136, 1.0438528419469173, 1.0390341125363867,
      1.0342286440257955, 1.0294397645780571, 1.0246707720468184,
      1.0199249326046156, 1.0152054793849554, 1.0105156111388878,
      1.0058584909065358, 1.0012372447040954, 0.99665496022681532,
      0.99211468556841931, 0.98761942795747393, 0.9831721525111643,
      0.978775781006961, 0.97443319067263356, 0.97014721299505668,
      0.96592063254828719, 0.96175618584131972, 0.95765656018598244,
      0.95362439258539033, 0.94966226864336689, 0.945772721495268,
      0.94195823076058816, 0.93822122151776632, 0.93456406330155717,
      0.93098906912337176, 0.92749849451494248, 0.92409453659566865,
      0.92077933316402372, 0.91755496181333074, 0.91442343907228141,
      0.91138671957049144, 0.90844669522942878, 0.90560519447902132,
      0.90286398150022806, 0.90022475549388792, 0.89768914997609217,
      0.89525873210038431, 0.89293500200701836, 0.89071939219954177,
      0.88861326694893528, 0.88661792172553522, 0.88473458265897453,
      0.8829644060263202, 0.8813084777686333, 0.87976781303612817,
      0.87834335576210221, 0.8770359782658077, 0.87584648088442263,
      0.87477559163426577, 0.87382396590137634, 0.87299218616160068,
      0.87228076173028635, 0.87169012854168326, 0.8712206489581461,
      0.87087261160922047, 0.87064623126066276, 0.87054164871348139,
      0.87055893073300639, 0.87069807000805921, 0.87095898514021552,
      0.87134152066319182, 0.871845447092348, 0.87247046100429837,
      0.87321618514660926, 0.87408216857754628, 0.87506788683583459,
      0.87617274214037077, 0.87739606361982181, 0.8787371075720356,
      0.88019505775316575, 0.88176902569642857, 0.8834580510603609,
      0.8852611020064699, 0.88717707560613945, 0.88920479827664667,
      0.89134302624613682, 0.89359044604739013, 0.89594567504019929,
      0.89840726196219134, 0.90097368750785711, 0.9036433649356207,
      0.90641464070271416, 0.90928579512761065, 0.912255043079814,
      0.91532053469671981, 0.91848035612731027, 0.92173253030239688,
      0.92507501773115053, 0.92850571732361009, 0.93202246723887527,
      0.93562304575868338, 0.93930517218604248, 0.94306650776858669,
      0.94690465664633716, 0.95081716682349293, 0.95480153116391686,
      0.95885518840995287, 0.96297552422417165, 0.9671598722537087,
      0.97140551521675411, 0.97570968601083607, 0.980069568842458,
      0.98448230037769557, 0.98894497091330957, 0.99345462556797448,
      0.99800826549313348, 1.0026028491030785, 1.0072352933237809,
      1.0119024748600076, 1.0166012314802566, 1.0213283633190442,
      1.026080634196052, 1.0308547729516282, 1.0356474747982041,
      1.0404554026870505, 1.045275188689903, 1.050103435394969,
      1.0549367173167328, 1.0597715823190874, 1.0646045530512445,
      1.0694321283958763, 1.0742507849289571, 1.079056978390788,
      1.0838471451675937, 1.088617703783189, 1.0933650564001467,
      1.0980855903298803, 1.1027756795511074, 1.1074316862361098,
      1.112049962284217, 1.1166268508619239, 1.1211586879491133,
      1.1256418038907363, 1.1300725249534089, 1.1344471748863427,
      1.1387620764859712, 1.1430135531637642, 1.1471979305165574,
      1.1513115378988474, 1.1553507099964606, 1.1593117884009649,
      1.1631911231842937, 1.1669850744728982, 1.1706900140209087,
      1.1743023267816692, 1.1778184124770428, 1.18123468716393,
      1.184547584797357, 1.18775355878956, 1.1908490835644931,
      1.1938306561071061, 1.1966947975068785, 1.199438054494955,
      1.2020570009743212, 1.2045482395424296, 1.2069084030057071,
      1.209134155885325, 1.2112221959136888, 1.2131692555210569,
      1.2149721033117005, 1.2166275455290807, 1.2181324275094121,
      1.2194836351231082, 1.2206780962035171, 1.2217127819623892,
      1.2225847083915702, 1.2232909376503163, 1.2238285794377251,
      1.2241947923497398, 1.2243867852201937, 1.2244018184453735,
      1.2242372052915731, 1.2238903131851284, 1.2233585649844383,
      1.2226394402334295, 1.2217304763960308, 1.2206292700711028,
      1.2193334781873937, 1.2178408191779917, 1.2161490741338783,
      1.2142560879360362, 1.212159770365723, 1.2098580971924318,
      1.2073491112390968, 1.2046309234241477, 1.2017017137799468,
      1.1985597324472077, 1.195203300645002, 1.1916308116159464,
      1.1878407315461752, 1.1838316004597234, 1.1796020330869494,
      1.1751507197066302, 1.1704764269613712, 1.1655779986460113,
      1.1604543564686467, 1.1551045007839864, 1.149527511298692,
      1.1437225477484454, 1.1376888505463683, 1.1314257414025968,
      1.1249326239146697, 1.118208984128497, 1.1112543910696506,
      1.1040684972447254, 1.0966510391125295, 1.0890018375249215,
      1.08112079813701, 1.0730079117865992, 1.0646632548426185,
      1.056086989522409, 1.0472793641776468, 1.0382407135488072,
      1.0289714589879755, 1.0194721086498844, 1.0097432576510692,
      0.99978558819700347, 0.98959986967713831, 0.97918695872774819,
      0.9685477992624969, 0.95768342247067184, 0.94659494678302547,
      0.93528357780518634, 0.92375060821860844, 0.91199741764902309,
      0.90002547250242193, 0.88783632576853988, 0.87543161679187542,
      0.8628130710102706, 0.84998249966109307, 0.836941799455055,
      0.82369295221777472, 0.81023802449909055, 0.796579167150283,
      0.78271861486925609, 0.76865868571381457, 0.75440178058312823,
      0.73995038266755819, 0.72530705686696306, 0.7104744491776307,
      0.69545528604805262, 0.68025237370365244, 0.66486859744071736,
      0.64930692088970243, 0.63357038524813958, 0.61766210848335557,
      0.60158528450525872, 0.5853431823094104, 0.56893914509068855,
      0.55237658932773781, 0.53565900383857412, 0.51878994880754814,
      0.50177305478404333, 0.48461202165315564, 0.4673106175787341,
      0.44987267791905627, 0.4323021041155507, 0.41460286255482981,
      0.396778983404496, 0.37883455942300404, 0.36077374474402257,
      0.34260075363565329, 0.324319859234921, 0.30593539225795879,
      0.28745173968626081, 0.2688733434295042, 0.25020469896529812,
      0.2314503539563732, 0.21261490684562595, 0.19370300542951085,
      0.1747193454102054, 0.1556686689270908, 0.13655576306798045,
      0.11738545836064918, 0.098162627245084677, 0.078892182527065424,
      0.059579075813522731, 0.040228295930220259, 0.020844867322318716,
      0.0014338484383126238, -0.017999669902080462, -0.037450566155510345,
      -0.056913689717572158, -0.076383862599720409, -0.095855881120030073,
      -0.11532451760715445, -0.13478452211696357, -0.15423062416122746,
      -0.17365753444777776, -0.19305994663156079, -0.21243253907592818,
      -0.23176997662363508, -0.25106691237688067, -0.270317989485772,
      -0.28951784294465716, -0.30866110139563185, -0.32774238893863489,
      -0.3467563269474947, -0.36569753589129744, -0.38456063716045458,
      -0.40334025489680581, -0.42203101782714481, -0.44062756109951084,
      -0.45912452812162635, -0.47751657240080031, -0.49579835938470618,
      -0.51396456830230686, -0.53200989400438292, -0.54992904880292848,
      -0.56771676430880746, -0.58536779326701, -0.60287691138888033,
      -0.62023891918062457, -0.6374486437675122, -0.65450094071306353,
      -0.6713906958326048, -0.68811282700055276, -0.70466228595079061,
      -0.72103406006944326, -0.73722317417946925, -0.75322469231641787,
      -0.76903371949466959, -0.784645403463618, -0.80005493645304715,
      -0.81525755690719026, -0.830248551206759, -0.845023255378354,
      -0.85957705679065921, -0.87390539583677873, -0.88800376760210331,
      -0.90186772351711952, -0.915492872994554, -0.92887488505026539,
      -0.94200948990725253, -0.9548924805822564, -0.96751971445431284,
      -0.97988711481473278, -0.991990672397898, -1.0038264468923379,
      -1.0153905684315123, -1.0266792390637502, -1.0376887342008319,
      -1.048415404044617, -1.0588556749912446, -1.0690060510123407,
      -1.0788631150127377, -1.088423530164216, -1.0976840412147086,
      -1.1066414757725269, -1.1152927455651156, -1.1236348476718334,
      -1.1316648657303161, -1.1393799711159569, -1.1467774240940489,
      -1.1538545749441331, -1.1606088650561659, -1.1670378279980205,
      -1.173139090553954, -1.17891037373362, -1.1843494937512218,
      -1.1894543629744385, -1.1942229908427384, -1.1986534847547121,
      -1.2027440509240872, -1.2064929952040495, -1.2098987238795753,
      -1.2129597444274192, -1.2156746662434661, -1.2180422013371239,
      -1.2200611649924951, -1.2217304763960306, -1.2230491592303923,
      -1.2240163422342833, -1.2246312597279927, -1.2248932521044162,
      -1.2248017662853443, -1.2243563561427941, -1.2235566828851954,
      -1.2224025154082352, -1.2208937306102019, -1.2190303136716547,
      -1.2168123582992554, -1.2142400669336673, -1.2113137509213363,
      -1.2080338306500957, -1.2044008356484586, -1.2004154046485189,
      -1.196078285612389, -1.1913903357221078, -1.1863525213329571,
      -1.1809659178901717, -1.1752317098089866, -1.1691511903180329,
      -1.1627257612660686, -1.155956932892056, -1.1488463235586195,
      -1.141395659448901, -1.1336067742268841, -1.1254816086612442,
      -1.1170222102127758, -1.1082307325855225, -1.09910943524168,
      -1.0896606828803952, -1.07988694488059, -1.0697907947079339,
      -1.059374909286132, -1.0486420683326849, -1.0375951536592778,
      -1.0262371484370179, -1.0145711364266921, -1.0026003011742746,
      -0.990327925171891, -0.977757388984489, -0.96489217034246111,
      -0.95173584320046722, -0.93829207676275317, -0.92456463447521287,
      -0.91055737298452355, -0.896274241064646, -0.88171927851100218,
      -0.866896615002671, -0.85181046893293966, -0.83646514620855128,
      -0.82086503901804586, -0.80501462456951045, -0.78891846379818942,
      -0.77258120004430886, -0.75600755770152261, -0.73920234083642078,
      -0.722170431779508, -0.70491678968809224, -0.68744644908154462,
      -0.66976451834935513, -0.651876178232498, -0.63378668027854268,
      -0.61550134527102818, -0.59702556163356, -0.57836478380917933,
      -0.5595245306154768, -0.54051038357599568, -0.52132798522847368,
      -0.50198303741039429, -0.48248129952248342, -0.4628285867706543,
      -0.44303076838696592, -0.4230937658301972, -0.40302355096657144,
      -0.38282614423126271, -0.36250761277126164, -0.34207406857016903,
      -0.32153166655558818, -0.30088660268966716, -0.28014511204346071,
      -0.25931346685570389, -0.23839797457666106, -0.21740497589763519,
      -0.19634084276687058, -0.17521197639238845, -0.15402480523250545,
      -0.132785782974644, -0.11150138650310271, -0.0901781138564613,
      -0.0688224821753009, -0.047441025640896417, -0.026040293405598158,
      -0.0046268475155047395, 0.016792739173767279, 0.038211885087635677,
      0.059624002028666356, 0.081022497277578875, 0.10240077569845618,
      0.12375224184742861, 0.145070302084167, 0.16634836668543235,
      0.1875798519600444, 0.20875818236450705, 0.22987679261860111,
      0.2509291298202489, 0.27190865555891891, 0.29280884802690144,
      0.3136232041277065, 0.33434524158087875, 0.35496850102258082,
      0.37548654810113835, 0.39589297556695535, 0.41618140535598513,
      0.43634549066614231, 0.45637891802591035, 0.47627540935444534,
      0.49602872401250275, 0.51563266084348, 0.53508106020387225,
      0.55436780598248014, 0.5734868276076398, 0.592432102041857,
      0.61119765576310647, 0.62977756673216034, 0.6481659663452487,
      0.66635704137140539, 0.68434503587385576, 0.70212425311472071,
      0.71968905744246592, 0.73703387616139615, 0.75415320138259345,
      0.77104159185561616, 0.78769367478038721, 0.80410414759857063,
      0.82026777976392906, 0.836179414490946, 0.85183397048116427,
      0.86722644362663248, 0.882351908689883, 0.897205520959822,
      0.91178251788302445, 0.92607822066977208, 0.94008803587438849,
      0.95380745694921054, 0.96723206577175058, 0.98035753414443938,
      0.993179625266478, 1.0056941951772636, 1.017897194170861,
      1.0297846681810792, 1.0413527601365977, 1.0525977112857259,
      1.0635158624902825, 1.0741036554881513, 1.0843576341240877,
      1.0942744455483053, 1.1038508413824211, 1.1130836788523693,
      1.1219699218878441, 1.1305066421879093, 1.1386910202523546,
      1.1465203463784563, 1.1539920216227686, 1.1611035587275975,
      1.1678525830118152, 1.1742368332257009, 1.1802541623694742,
      1.1859025384752357, 1.1911800453520205, 1.1960848832936728,
      1.2006153697493003, 1.204769939956023, 1.2085471475338041,
      1.2119456650421216, 1.2149642844982598, 1.2176019178570283,
      1.2198575974517019, 1.2217304763960306, 1.2232198289471152,
      1.2243250508290402, 1.2250456595170904, 1.2253812944824445,
      1.2253317173972222, 1.2248968122998054, 1.2240765857203102,
      1.2228711667661805, 1.2212808071678034, 1.2193058812841386,
      1.2169468860682926, 1.214204440993047, 1.2110792879363133,
      1.2075722910265403, 1.2036844364480848, 1.1994168322065675,
      1.1947707078542926, 1.189747414175764, 1.1843484228333889,
      1.1785753259734448, 1.1724298357924245, 1.1659137840638523,
      1.1590291216257329, 1.1517779178287355, 1.1441623599452937,
      1.1361847525397852, 1.1278475167999569, 1.1191531898298093,
      1.1101044239041336, 1.1007039856849181, 1.0909547553998791,
      1.0808597259833266, 1.0704220021796536, 1.0596447996097065,
      1.048531443800317, 1.0370853691773037, 1.0253101180222306,
      1.0132093393932693, 1.0007867880104822, 0.98804632310585738,
      0.9749919072384905, 0.96162760507524714, 0.94795758213730585,
      0.9339861035129593, 0.91971753253708555, 0.90515632943770852,
      0.890307049950069, 0.8751743438986459, 0.85976295374755274,
      0.84407771311981517, 0.82812354528596277, 0.81190546162242461,
      0.79542856004021434, 0.77869802338442828, 0.76171911780502777,
      0.74449719109947954, 0.72703767102771943, 0.70934606360003238,
      0.691427951338388, 0.673288991511763, 0.65493491434605167,
      0.63637152120911056, 0.61760468277154834, 0.59864033714385534,
      0.5794844879904173, 0.56014320262112993, 0.54062261006110612,
      0.52092889909921, 0.501068316315982, 0.4810471640916183,
      0.46087179859465666, 0.440548627752003, 0.42008410920098121,
      0.39948474822404445, 0.37875709566685217, 0.35790774584037721,
      0.33694333440770324, 0.31587053625625272, 0.29469606335608078,
      0.27342666260499549, 0.25206911366115814, 0.23063022676388242,
      0.20911684054338014, 0.18753581982013437, 0.16589405339463,
      0.14419845182815927, 0.12245594521545994, 0.10067348094987261,
      0.0788580214818016, 0.057016542071159249, 0.035156028534566952,
      0.013283474988065425, -0.0085941184139584625, -0.030469747742866093,
      -0.052336407562116438, -0.074187093195189735, -0.096014802994254522,
      -0.11781254060887109, -0.13957331725401867, -0.16129015397661295,
      -0.18295608391984525, -0.20456415458455662, -0.22610743008690148,
      -0.24757899341155515, -0.26897194865975027, -0.29027942329133261,
      -0.31149457036017547, -0.33261057074214984, -0.353620635354927,
      -0.37451800736891117, -0.39529596440851922, -0.41594782074310765,
      -0.4364669294668323, -0.45684668466665251, -0.47708052357787545,
      -0.4971619287263937, -0.51708443005699678, -0.53684160704700834,
      -0.55642709080456054, -0.57583456615081008, -0.59505777368538193,
      -0.61409051183438057, -0.63292663888025746, -0.65156007497289126,
      -0.66998480412120065, -0.68819487616458852, -0.70618440872361765,
      -0.7239475891292243, -0.74147867632985165, -0.75877200277585577,
      -0.7758219762805324, -0.79262308185720465, -0.80916988353167485,
      -0.825457026129508, -0.84147923703749372, -0.85723132793873991,
      -0.872708196520787, -0.88790482815617633, -0.90281629755491788,
      -0.91743777038831631, -0.93176450488355156, -0.9457918533885632,
      -0.959515263906634, -0.97293028160022, -0.98603255026347159,
      -0.998817813762989, -1.0112819174462848, -1.0234208095175354,
      -1.0352305423801051, -1.0467072739454146, -1.0578472689077096,
      -1.0686468999842931, -1.0791026491208104, -1.089211108661182,
      -1.0989689824817588, -1.1083730870893558, -1.1174203526827684,
      -1.1261078241774143, -1.134432662192747, -1.1423921440021241,
      -1.1499836644447874, -1.1572047367996388, -1.1640529936205455,
      -1.1705261875328488, -1.1766221919908322, -1.1823390019958753,
      -1.1876747347750476, -1.1926276304199084, -1.197196052485302,
      -1.2013784885479117, -1.2051735507244161, -1.2085799761490428,
      -1.2115966274103485, -1.2142224929470915, -1.2164566874030327,
      -1.2182984519405606, -1.2197471545130032, -1.2208022900955484,
      -1.2214634808746774, -1.2217304763960295, -1.2216031536706657,
      -1.2210815172396519, -1.2201656991969632, -1.2188559591706765,
      -1.2171526842624372, -1.2150563889452393, -1.2125677149195162,
      -1.2096874309275991, -1.2064164325265843, -1.2027557418196744,
      -1.1987065071460914, -1.1942700027296196, -1.1894476282859259,
      -1.1842409085887553, -1.1786514929951375, -1.172681154929752,
      -1.1663317913286371, -1.1596054220423673, -1.1525041891989534,
      -1.1450303565266071, -1.1371863086366267, -1.1289745502666144,
      -1.1203977054842695, -1.1114585168520157, -1.1021598445527334,
      -1.0925046654768693, -1.082496072271218, -1.0721372723496945,
      -1.0614315868664146, -1.0503824496513912, -1.0389934061092259,
      -1.0272681120811304, -1.0152103326706532, -1.0028239410334949,
      -0.99011291713179328, -0.97708134645331146, -0.96373341869589613,
      -0.95007342641770642, -0.93610576365356546, -0.921834924497963,
      -0.90726550165513342, -0.89240218495667567, -0.87724975984722819,
      -0.86181310583866833, -0.84609719493333624, -0.830107090016843,
      -0.81384794322092391, -0.79732499425693126, -0.78054356872046626,
      -0.76350907636774079, -0.74622700936420427, -0.72870294050603379,
      -0.7109425214150602, -0.6929514807076903, -0.67473562213849714,
      -0.65630082271901768, -0.63765303081241553, -0.61879826420460637,
      -0.59974260815250879, -0.58049221341002433, -0.56105329423244454,
      -0.541432126359879, -0.5216350449804138, -0.501668442673658,
      -0.48153876733533729, -0.46125252008363427, -0.44081625314796613,
      -0.42023656774085477, -0.39952011191366749, -0.378673578396828,
      -0.35770370242529786, -0.3366172595500162, -0.3154210634359762,
      -0.29412196364772747, -0.27272684342298203, -0.25124261743508935,
      -0.22967622954508093, -0.20803465054408149, -0.18632487588674529,
      -0.16455392341654634, -0.14272883108363479, -0.1208566546559865,
      -0.098944465424636807, -0.076999347903749876, -0.05502839752624758,
      -0.033038718335825334, -0.011037420675981957, 0.010968381122994253,
      0.032971571058475924, 0.054965033770552035, 0.076941656856920032,
      0.098894333186901662, 0.12081596321376484, 0.14269945728461592,
      0.16453773794713469, 0.18632374225231169, 0.20805042405251956,
      0.22971075629410134, 0.25129773330374772, 0.27280437306789429,
      0.29422371950441994, 0.31554884472586359, 0.33677285129341844,
      0.3578888744610052, 0.378890084408615, 0.39976968846426358,
      0.42052093331375751, 0.44113710719759136, 0.46161154209424005,
      0.48193761588910694, 0.502108754528463, 0.52211843415762482,
      0.54196018324267548, 0.56162758467505414, 0.58111427785829384,
      0.60041396077624165, 0.61952039204207809, 0.6384273929274531,
      0.65712884937106142, 0.67561871396606188, 0.69389100792558889,
      0.71193982302578207, 0.7297593235256824, 0.74734374806334058,
      0.76468741152755082, 0.78178470690456348, 0.79863010709918814,
      0.81521816672968017, 0.83154352389584441, 0.84760090191974391,
      0.86338511105846072, 0.87889105018835, 0.89411370846022875,
      0.90904816692495316, 0.9236896001288597, 0.93803327767858025,
      0.9520745657746098, 0.96580892871326607, 0.97923193035646783,
      0.99233923556885939, 1.0051266116218027, 1.0175899295638307,
      1.0297251655570667, 1.0415284021791642, 1.0529958296903934,
      1.0641237472654159, 1.0749085641893772, 1.0853468010178764,
      1.0954350907005106, 1.1051701796675939, 1.1145489288796462,
      1.1235683148394007, 1.1322254305659463, 1.1405174865307102,
      1.1484418115549466, 1.1559958536684891, 1.1631771809294567,
      1.1699834822046558, 1.1764125679104187, 1.1824623707136628,
      1.1881309461929361, 1.1934164734592061, 1.1983172557362465,
      1.2028317209004098, 1.2069584219795968, 1.2106960376112958,
      1.214043372459529, 1.2169993575905946, 1.2195630508074502,
      1.2217336369426706, 1.2235104281098867, 1.2248928639135923,
      1.2258805116173046, 1.2264730662700112, 1.2266703507908421,
      1.2264723160120092, 1.2258790406799283, 1.224890731414594,
      1.2235077226271978, 1.2217304763960308, 1.2195595823007128,
      1.2169957572148227, 1.2140398450569965, 1.2106928165005848,
      1.2069557686419663, 1.2028299246276544, 1.1983166332403001,
      1.1934173684437597, 1.18813372888736, 1.1824674373695623,
      1.1764203402611848, 1.1699944068883892, 1.163191728875639,
      1.1560145194488696, 1.1484651126990919, 1.1405459628066614,
      1.1322596432265364, 1.123608845834732, 1.1145963800363048,
      1.1052251718351533, 1.0954982628659302, 1.085418809388452,
      1.0749900812448796, 1.0642154607800203, 1.0530984417252138,
      1.0416426280460382, 1.0298517327543044, 1.0177295766847356,
      1.0052800872367422, 0.9925072970816684, 0.97941534283596665,
      0.96600846370081994, 0.9522910000685314, 0.93826739209623589,
      0.9239421782474091, 0.9093199938016342, 0.8944055693331241,
      0.87920372915849909, 0.86371938975441864, 0.8479575581454547,
      0.83192333026285192, 0.81562188927469514, 0.799058503888036,
      0.782238526623538, 0.76516739206317286, 0.7478506150716786,
      0.73029378899223341, 0.71250258381701614, 0.6944827443332191,
      0.67624008824520732, 0.65778050427334667, 0.63910995023019568,
      0.62023445107467423, 0.601160096944903, 0.581893041170277,
      0.56243949826348327, 0.542805741893178, 0.522998102837888,
      0.50302296692186865, 0.48288677293364241, 0.46259601052783927,
      0.44215721811104824, 0.42157698071238181, 0.40086192783951641,
      0.3800187313208066, 0.35905410313425445, 0.33797479322405505,
      0.316787587305439, 0.29549930465847085, 0.27411679591162308,
      0.25264694081575961, 0.23109664600940794, 0.20947284277588138,
      0.18778248479306803, 0.16603254587671795, 0.14423001771779936,
      0.12238190761476517, 0.10049523620149761, 0.078577035171635917,
      0.0566343450000312, 0.034674212662032911, 0.012703689351538011,
      -0.0092701718016858226, -0.03124031801453081, -0.0531996991321432,
      -0.075141269907929881, -0.097057992281187833, -0.11894283765164271,
      -0.14078878915001858, -0.16258884390412409, -0.18433601529953358,
      -0.20602333523416272, -0.22764385636603168, -0.24919065435348409,
      -0.27065683008713209, -0.2920355119127363, -0.31331985784434663,
      -0.33450305776702843, -0.35557833562836993, -0.37653895161808787,
      -0.397378204335045, -0.41808943294096795, -0.43866601930012927,
      -0.45910139010432038, -0.47938901898246189, -0.49952242859413687,
      -0.51949519270630928, -0.53930093825267, -0.55893334737485578,
      -0.57838615944494443, -0.59765317306846022, -0.61672824806739346,
      -0.63560530744251842, -0.65427833931430046, -0.672741398841917,
      -0.69098861011968726, -0.70901416805029638, -0.72681234019419683,
      -0.744377468594693, -0.76170397157801684, -0.77878634552783466,
      -0.79561916663364862, -0.81219709261252315, -0.828514864403606,
      -0.84456730783480016, -0.860349335261207, -0.87585594717471382,
      -0.89108223378424134, -0.90602337656612986, -0.92067464978422053,
      -0.93503142197912092, -0.94908915742613265, -0.96284341756147507,
      -0.97628986237630155, -0.989424251778055, -1.0022424469187476,
      -1.0147404114897793, -1.0269142129828537, -1.0387600239165817,
      -1.0502741230284349, -1.0614528964316585, -1.0722928387367583,
      -1.0827905541372429, -1.0929427574592816, -1.1027462751749602,
      -1.1121980463787906, -1.121295123727204, -1.130034674340741,
      -1.1384139806686573, -1.1464304413156661, -1.1540815718305995,
      -1.1613650054567375, -1.1682784938435766, -1.1748199077198138,
      -1.1809872375273982, -1.1867785940164148, -1.1921922088006345,
      -1.1972264348736044, -1.2018797470851066, -1.2061507425778393,
      -1.2100381411842447, -1.21354078578333, -1.2166576426174365,
      -1.21938780156882, -1.2217304763960306, -1.2236850049300179,
      -1.2252508492298997, -1.2264275956984076, -1.2272149551569722,
      -1.2276127628804527, -1.2276209785915282, -1.2272396864147719,
      -1.2264690947904517, -1.2253095363481203, -1.2237614677400477,
      -1.2218254694345667, -1.21950224546947, -1.2167926231654971,
      -1.213697552800109, -1.2102181072416092, -1.2063554815437958,
      -1.2021109925013169, -1.1974860781658596, -1.1924822973233735,
      -1.187101328932562, -1.1813449715247804, -1.1752151425656292,
      -1.1687138777784316, -1.161843330429871, -1.154605770578037,
      -1.1470035842831421, -1.1390392727812033, -1.1307154516210032,
      -1.1220348497646027, -1.1130003086517171, -1.1036147812283512,
      -1.0938813309399915, -1.0838031306896689, -1.0733834617613454,
      -1.0626257127089547, -1.0515333782114691, -1.0401100578943974,
      -1.0283594551181943, -1.0162853757338772, -1.0038917268063814,
      -0.99118251530604184, -0.97816184676870011, -0.96483392392483414,
      -0.9512030452982263, -0.93727360377464042, -0.92305008514102327,
      -0.90853706659565581, -0.893739215229833, -0.87866128648158681,
      -0.86330812256194278, -0.84768465085423261, -0.83179588228710166,
      -0.81564690968165232, -0.799242906073344, -0.78258912300918348,
      -0.76569088882080949, -0.74855360687411276, -0.731182753795776,
      -0.71358387767757692, -0.69576259625894221, -0.67772459508833327,
      -0.6594756256641352, -0.641021503555665, -0.62236810650494667,
      -0.60352137250981719, -0.58448729788904852, -0.56527193533022246,
      -0.54588139192081075, -0.526321827163279, -0.50659945097484516,
      -0.48672052167252861, -0.46669134394414719, -0.44651826680596379,
      -0.42620768154770344, -0.40576601966552844, -0.38519975078370267,
      -0.36451538056566934, -0.34371944861518305, -0.32281852636820874,
      -0.30181921497623432, -0.28072814318182088, -0.25955196518699963,
      -0.23829735851513098, -0.21697102186714237, -0.19557967297269707,
      -0.17413004643704313, -0.1526288915841765, -0.13108297029720217,
      -0.10949905485643205, -0.087883925775980282, -0.066244369639561471,
      -0.044587176936267695, -0.0229191398968992, -0.001247050331635205,
      0.020422302530217512, 0.042082134197780022, 0.0637256670727128,
      0.085346132599209618, 0.1069367734091014, 0.12849084546146503,
      0.15000162017607102, 0.17146238655979407, 0.19286645332551389,
      0.21420715100272564, 0.23547783403914715, 0.25667188289277987,
      0.27778270611346639, 0.29880374241373525, 0.31972846272778588,
      0.34055037225822682, 0.36126301250990672, 0.3818599633100826,
      0.40233484481437048, 0.4226813194977268, 0.44289309412997435,
      0.4629639217352054, 0.48288760353425275, 0.50265799086992613,
      0.52226898711416769, 0.54171454955660048, 0.5609886912738804,
      0.58008548297924967, 0.598999054851765, 0.6177235983444529,
      0.63625336797109366, 0.6545826830708219, 0.67270592955015784,
      0.69061756160181909, 0.70831210339983852, 0.72578415077051972,
      0.7430283728385112, 0.76003951364768885, 0.77681239375632749,
      0.79334191180589675, 0.809623046063227, 0.82565085593538834,
      0.841420483456988, 0.8569271547492322, 0.87216618145049218,
      0.887132962117854, 0.90182298359922852, 0.91623182237562584,
      0.93035514587317558, 0.9441887137445315, 0.95772837911926478,
      0.97097008982279043, 0.98390988956365621, 0.99654391908865425,
      1.0088684173055165, 1.0208797223728225, 1.0325742727568841,
      1.0439486082551817, 1.0549993709861176, 1.065723306344871,
      1.0761172639249454, 1.0861781984052863, 1.0959031704025965,
      1.105289347288732, 1.1143340039729008, 1.1230345236483823,
      1.1313883985037281, 1.1393932303981211, 1.1470467315007706,
      1.1543467248941708, 1.1612911451410797, 1.1678780388150902,
      1.1741055649946204, 1.1799719957202544, 1.1854757164153509,
      1.1906152262697225, 1.1953891385864623, 1.1997961810917177,
      1.2038351962074441, 1.2075051412870641, 1.21080508881399,
      1.2137342265630522, 1.2162918577247477, 1.2184774009923904,
      1.2202903906121536, 1.2217304763960284, 1.2227974236977825,
      1.2234911133518951, 1.2238115415756883, 1.2237588198345404,
      1.2233331746704579, 1.2225349474940126, 1.2213645943397551,
      1.2198226855853149, 1.2179099056342397, 1.2156270525627879,
      1.2129750377308355, 1.2099548853570137, 1.2065677320583827,
      1.2028148263546994, 1.198697528137632, 1.1942173081050487,
      1.1893757471606419, 1.1841745357791613, 1.1786154733374712,
      1.1727004674117354, 1.166431533040992, 1.1598107919573892,
      1.1528404717834562, 1.1455229051966072, 1.1378605290613075,
      1.1298558835291557, 1.1215116111073107, 1.1128304556954731,
      1.1038152615919534, 1.094468972469107, 1.0847946303184686,
      1.0747953743661016, 1.0644744399584702, 1.053835157419279,
      1.0428809508777017, 1.0316153370683765, 1.0200419241037069,
      1.0081644102188028, 0.99598658248957173, 0.98351231552444718,
      0.9707455701301434, 0.95769039195200567, 0.94435091008933991,
      0.93073133568635658, 0.91683596049907146, 0.90266915543875914,
      0.88823536909249767, 0.8735391262212483, 0.85858502623607247,
      0.84337774165292689, 0.8279220165266914, 0.81222266486495753,
      0.79628456902196754, 0.78011267807351614, 0.76371200617321056,
      0.747087630890697, 0.73024469153241367, 0.71318838744552493,
      0.69592397630552272, 0.67845677238814428, 0.66079214482614668,
      0.64293551585165176, 0.62489235902450191, 0.60666819744733125,
      0.58826860196796282, 0.56969918936972086, 0.55096562055024112,
      0.53207359868944726, 0.51302886740730547, 0.49383720891195287,
      0.47450444213883292, 0.45503642088148233, 0.43543903191461331,
      0.41571819311004921, 0.39587985154618593, 0.37592998161165714,
      0.35587458310381004, 0.33571967932250429, 0.31547131516007715,
      0.295135555187986, 0.27471848174075542, 0.25422619299788829,
      0.23366480106440687, 0.2130404300506239, 0.1923592141517588,
      0.1716272957280317, 0.150850823385974, 0.13003595006138446,
      0.10918883110472274, 0.088315622369519425, 0.067422478304405731,
      0.046515550049394123, 0.025600983536989981, 0.0046849175988792971,
      -0.016226517921368297, -0.037127204048882437, -0.058011034550706289,
      -0.078871917801143207, -0.099703778638576976, -0.12050056021320127,
      -0.14125622582503045, -0.16196476075157221, -0.182620174064772,
      -0.20321650043639197, -0.22374780193139263, -0.24420816978876844,
      -0.26459172618922921, -0.284892626009169, -0.30510505856035752,
      -0.325223249314883, -0.34524146161475555, -0.36515399836558815,
      -0.38495520371392966, -0.40463946470769974, -0.42420121293914304,
      -0.44363492616986766, -0.46293512993747721, -0.48209639914326718,
      -0.50111335962046843, -0.51998068968265221, -0.538693121651779,
      -0.5572454433653975, -0.57563249966256169, -0.59384919384807688,
      -0.611890489134561, -0.629751410061923, -0.64742704389377714,
      -0.6649125419905747, -0.68220312115877491, -0.699294064975845,
      -0.71618072509067621, -0.73285852249900552, -0.74932294879348116,
      -0.76556956738800652, -0.78159401471605294, -0.797392001402593,
      -0.81295931340924754, -0.82829181315243816, -0.8433854405941823,
      -0.85823621430519936, -0.87284023250009235, -0.88719367404429428,
      -0.90129279943253815, -0.9151339517385445, -0.92871355753569151,
      -0.942028127788492, -0.95507425871453888, -0.96784863261676568,
      -0.98034801868583765, -0.99256927377241988, -1.0045093431291594,
      -1.0161652611221794, -1.027534151912022, -1.0386132301037341,
      -1.0493998013660373, -1.0598912630194754, -1.0700851045933604,
      -1.0799789083514122, -1.0895703497860092, -1.0988571980809843,
      -1.1078373165428279, -1.1165086630002643, -1.1248692901721582,
      -1.1329173460036861, -1.1406510739707238, -1.1480688133524555,
      -1.1551689994721734, -1.1619501639063028, -1.1684109346615537,
      -1.1745500363203758, -1.1803662901546215, -1.1858586142074943,
      -1.1910260233438827, -1.1958676292690473, -1.2003826405158269,
      -1.2045703624003987, -1.2084301969466706, -1.2119616427794826,
      -1.2151642949866348, -1.2180378449499623, -1.2205820801455025,
      -1.2227968839130017, -1.224682235194813, -1.2262382082444159,
      -1.2274649723047437, -1.2283627912564548, -1.228932023236371,
      -1.2291731202263017, -1.22908662761245, -1.2286731837156315,
      -1.2279335192925376, -1.2268684570083153, -1.2254789108806423,
      -1.2237658856956761, -1.2217304763960306, -1.2193738674411434,
      -1.2166973321402839, -1.2137022319585262, -1.2103900157959502,
      -1.2067622192404335, -1.2028204637943549, -1.1985664560754969,
      -1.1940019869925247, -1.1891289308953934, -1.183949244701024,
      -1.1784649669946092, -1.1726782171069279, -1.1665911941680518,
      -1.1602061761378191, -1.1535255188134772, -1.1465516548148884,
      -1.1392870925477017, -1.1317344151449236, -1.1238962793872642,
      -1.1157754146027608, -1.1073746215460223, -1.0986967712575979,
      -1.0897448039038742, -1.0805217275979904, -1.0710306172021831,
      -1.0612746131120583, -1.0512569200232091, -1.0409808056807379,
      -1.0304495996120453, -1.0196666918434356, -1.0086355316010511,
      -0.99735962599650485, -0.985842538697872, -0.97408788858635575,
      -0.96209934839931521, -0.94988064335997757, -0.93743554979445964,
      -0.92476789373661628, -0.91188154952111589, -0.89878043836540933,
      -0.88546852694096267, -0.87194982593441583, -0.85822838859907347,
      -0.84430830929731426, -0.83019372203445263, -0.8158887989845407,
      -0.80139774900868621, -0.786724816166342, -0.77187427822025012,
      -0.75685044513536548, -0.7416576575725, -0.72630028537705349,
      -0.71078272606349335, -0.69510940329605253, -0.6792847653661418,
      -0.66331328366716136, -0.647199451167041, -0.63094778087925063,
      -0.6145628043326129, -0.59804907004064223, -0.58141114197079413,
      -0.56465359801419257, -0.54778102845645715, -0.53079803444999518,
      -0.51370922648841955, -0.49651922288351819, -0.479232648245392,
      -0.46185413196618991, -0.44438830670796703, -0.42683980689524637,
      -0.40921326721274787, -0.39151332110874237, -0.37374459930461934,
      -0.35591172831112272, -0.338019328951722, -0.32007201489372139,
      -0.30207439118739388, -0.28403105281387941, -0.26594658324208853,
      -0.24782555299521086, -0.22967251822733795, -0.21149201931047767,
      -0.19328857943269892, -0.17506670320753448, -0.156830875295426,
      -0.13858555903736403, -0.12033519510134305, -0.10208420014203501,
      -0.083836965473982339, -0.065597855758970869, -0.047371207707700369,
      -0.029161328796453445, -0.010972495998936405, 0.0071910454662134082,
      0.025325083371837753, 0.0434254397022647, 0.061487971856509949,
      0.079508573834354557, 0.097483177404809163, 0.11540775325678598,
      0.13327831213148028, 0.15109090593623414, 0.1688416288394739,
      0.18652661834644138, 0.20414205635542365, 0.2216841701940819,
      0.2391492336357082, 0.2565335678949997, 0.27383354260318205,
      0.29104557676206677, 0.30816613967693862, 0.32519175186789717,
      0.34211898595942047, 0.35894446754797604, 0.37566487604735038,
      0.39227694551158321, 0.40877746543515658, 0.42516328153038685,
      0.44143129648170709, 0.45757847067667468, 0.47360182291357422,
      0.48949843108538404, 0.50526543284001035, 0.52090002621652576,
      0.53639947025746326, 0.55176108559675885, 0.56698225502352262,
      0.58206042402126312, 0.59699310128260075, 0.61177785919940075,
      0.62641233432804344, 0.6408942278300318, 0.655221305887622,
      0.66939140009457365, 0.68340240782188211, 0.69725229255848553,
      0.71093908422695962, 0.72446087947403692, 0.7378158419361347,
      0.75100220247970362, 0.76401825941651857, 0.77686237869387875,
      0.78953299405973421, 0.802028607202828, 0.81434778786782713,
      0.82648917394547816, 0.83845147153797484, 0.85023345499945679,
      0.86183396695179981, 0.87325191827574922, 0.8844862880775155,
      0.89553612363096224, 0.90640054029536743, 0.91707872140908042,
      0.92756991815903667, 0.93787344942632334, 0.94798870160801885,
      0.9579151284152726, 0.967652250648061, 0.97719965594646452,
      0.98655699851896861, 0.99572399884774287, 1.0047004433711766,
      1.0134861841439431, 1.0220811384746233, 1.0304852885413363,
      1.038698680985392, 1.0467214264833407, 1.0545536992976468,
      1.0621957368060975, 1.0696478390104094, 1.0769103680241359,
      1.0839837475402363, 1.0908684622785183, 1.0975650574132849,
      1.1040741379814505, 1.11039636827143, 1.1165324711931215,
      1.1224832276292167, 1.1282494757682731, 1.1338321104197742,
      1.1392320823115289, 1.1444503973697528, 1.1494881159821686,
      1.1543463522444437, 1.1590262731903556, 1.1635290980060087,
      1.1678560972284382, 1.1720085919290248, 1.1759879528820436,
      1.1797955997187222, 1.183433000067192, 1.1869016686787344,
      1.1902031665406552, 1.193339099976209, 1.196311119731992,
      1.1991209200531334, 1.2017702377467412, 1.2042608512339532,
      1.206594579591084, 1.2087732815801571, 1.2107988546693418,
      1.212673234043655, 1.2143983916063239, 1.2159763349713129,
      1.2174091064473118, 1.2186987820137476, 1.2198474702891071,
      1.2208573114920942, 1.2217304763960306, 1.2224691652768709,
      1.2230756068553632, 1.2235520572336611, 1.223900798826951,
      1.2241241392904165, 1.2242244104420519, 1.2242039671816936,
      1.2240651864067467, 1.2238104659250419, 1.2234422233652205,
      1.2229628950850968, 1.2223749350784652, 1.2216808138806972,
      1.2208830174736816, 1.2199840461904086, 1.2189864136197124,
      1.217892645511585, 1.2167052786834467, 1.2154268599278542,
      1.2140599449220215, 1.2126070971395948, 1.211070886765109,
      1.2094538896115115, 1.2077586860411926, 1.2059878598909426,
      1.2041439974011836, 1.2022296861499566, 1.2002475139920374,
      1.1982000680035387, 1.1960899334324715, 1.1939196926555942,
      1.1916919241419548, 1.1894092014235393, 1.1870740920733549,
      1.1846891566913831, 1.1822569478987222, 1.1797800093403168,
      1.1772608746966347, 1.1747020667046568, 1.1721060961884986,
      1.1694754611000679, 1.1668126455700505, 1.1641201189696022,
      1.1614003349830786, 1.15865573069207, 1.1558887256711743,
      1.1531017210957313, 1.1502970988618724, 1.14747722071919,
      1.1446444274163134, 1.1418010378597065, 1.1389493482859556,
      1.1360916314478351, 1.1332301358144532, 1.1303670847856875,
      1.127504675921241, 1.1246450801845407, 1.1217904412017163,
      1.1189428745359353, 1.1161044669773168, 1.1132772758486325,
      1.1104633283270633, 1.1076646207821763, 1.1048831181303749,
      1.1021207532059845, 1.0993794261492089, 1.0966610038111004,
      1.0939673191757624, 1.0913001707999341, 1.0886613222701118,
      1.0860525016774121, 1.0834754011102596, 1.0809316761650951,
      1.0784229454752157, 1.0759507902578651, 1.07351675387973,
      1.0711223414408853, 1.06876901937739, 1.0664582150825208,
      1.0641913165468138, 1.0619696720169658, 1.0597945896736434,
      1.057667337328315, 1.0555891421391148, 1.0535611903458064,
      1.0515846270239031, 1.0496605558579373, 1.0477900389339545,
      1.0459740965511948, 1.0442137070530153, 1.0425098066770424,
      1.0408632894245102, 1.0392750069488543, 1.0377457684634386,
      1.0362763406684585, 1.0348674476969659, 1.0335197710799244,
      1.0322339497303341, 1.0310105799462577, 1.0298502154327789,
      1.0287533673427287, 1.0277205043361741, 1.0267520526585132,
      1.0258483962371265, 1.0250098767964602, 1.0242367939913937,
      1.0235294055588655, 1.0228879274875036, 1.0223125342052388,
      1.0218033587846809, 1.0213604931661564, 1.0209839883982346,
      1.0206738548955678, 1.0204300627138854, 1.0202525418419983,
      1.020141182510552, 1.0200958355174445, 1.0201163125695969,
      1.0202023866409919, 1.020353792346659, 1.0205702263324978,
      1.0208513476806398, 1.0211967783301419, 1.0216061035128252,
      1.0220788722039447, 1.022614597587501, 1.0232127575359371,
      1.0238727951039368, 1.0245941190361161, 1.0253761042882497,
      1.0262180925619231, 1.0271193928521347, 1.0280792820077014,
      1.0290970053042023, 1.0301717770290313, 1.0313027810784035,
      1.0324891715659652, 1.0337300734426718, 1.0350245831276861,
      1.0363717691499468, 1.0377706728001175, 1.0392203087925656,
      1.040719665937065, 1.0422677078199369, 1.0438633734942091,
      1.045505578178562, 1.0471932139646705, 1.0489251505325758,
      1.0507002358738253, 1.0525172970219971, 1.0543751407902437,
      1.0562725545155143, 1.0582083068091601, 1.0601811483134871,
      1.0621898124639526, 1.0642330162566589, 1.0663094610207355,
      1.0684178331953225, 1.070556805110698, 1.0727250357733191,
      1.074921171654285, 1.0771438474809205, 1.0793916870311526,
      1.0816633039302108, 1.0839573024494089, 1.0862722783065548,
      1.0886068194676428, 1.0909595069494924, 1.0933289156229538,
      1.0957136150162965, 1.0981121701184278, 1.1005231421816077,
      1.1029450895232435, 1.1053765683264642, 1.1078161334390297,
      1.110262339170331, 1.1127137400860179, 1.1151688917999563,
      1.1176263517631311, 1.1200846800491766, 1.1225424401361441,
      1.1249981996841911, 1.1274505313088157, 1.1298980133493228,
      1.1323392306321611, 1.1347727752287875, 1.1371972472077436,
      1.1396112553806048, 1.1420134180414407, 1.1444023636995269,
      1.1467767318049094, 1.1491351734665534, 1.1514763521627329,
      1.1537989444433834, 1.1561016406240534, 1.1583831454712092,
      1.160642178878533, 1.1628774765339935, 1.165087790577314,
      1.1672718902476045, 1.1694285625208622, 1.1715566127370558,
      1.1736548652165211, 1.1757221638654241, 1.1777573727699489,
      1.1797593767790877, 1.1817270820756436, 1.1836594167352663,
      1.1855553312732852, 1.1874137991790725, 1.1892338174377108,
      1.1910144070387669, 1.1927546134719036, 1.1944535072091802,
      1.1961101841737445, 1.197723766194831, 1.1992934014487482,
      1.2008182648857524, 1.2022975586425901, 1.203730512440536,
      1.2051163839687471, 1.2064544592527864, 1.2077440530081622,
      1.20898450897869, 1.2101752002595985, 1.21131552960518, 1.2124049297208956,
      1.2134428635398, 1.2144288244831472, 1.215362336705117, 1.2162429553214937,
      1.2170702666222735, 1.2178438882680307, 1.2185634694700676,
      1.2192286911541146, 1.2198392661077291, 1.2203949391111006,
      1.2208954870513895, 1.2213407190204706, 1.2217304763960311,
      1.2220646329060578, 1.2223430946766147, 1.2225658002629511,
      1.2227327206638909, 1.2228438593195383, 1.2228992520922568,
      1.222898967230986, 1.2228431053188815, 1.222731799204317,
      1.2225652139152694, 1.2223435465571471, 1.2220670261941136,
      1.2217359137139132, 1.2213505016763555, 1.220911114145403,
      1.2204181065050657, 1.2198718652591003, 1.2192728078146415,
      1.2186213822498408, 1.2179180670656646, 1.217163370921901,
      1.2163578323575335, 1.2155020194956303, 1.2145965297327876,
      1.2136419894133914, 1.2126390534887603, 1.2115884051613173,
      1.2104907555140332, 1.2093468431251932, 1.2081574336687479,
      1.2069233195003939, 1.20564531922956, 1.2043242772775098,
      1.2029610634217425, 1.2015565723268846, 1.2001117230623528,
      1.1986274586068655, 1.19710474534019, 1.1955445725221969,
      1.1939479517595717, 1.1923159164603558, 1.1906495212765758,
      1.1889498415352233, 1.1872179726578, 1.185455029568758, 1.1836621460930039,
      1.1818404743428257, 1.179991184094453, 1.1781154621545487,
      1.1762145117169518, 1.1742895517098526, 1.1723418161338559,
      1.170372553391037, 1.1683830256054648, 1.1663745079353678,
      1.1643482878773239, 1.1623056645627559, 1.1602479480470487,
      1.1581764585916039, 1.1560925259391821, 1.1539974885828204,
      1.1518926930286493, 1.1497794930529941, 1.1476592489540192,
      1.1455333267983379, 1.1434030976628176, 1.141269936872042,
      1.1391352232316627, 1.1370003382580744, 1.1348666654047044,
      1.1327355892852919, 1.1306084948944939, 1.1284867668261713,
      1.1263717884897457, 1.1242649413249004, 1.1221676040150823,
      1.1200811517000815, 1.1180069551880742, 1.1159463801675213,
      1.1139007864192134, 1.1118715270288875, 1.1098599476007061,
      1.1078673854720642, 1.105895168929965, 1.1039446164293865,
      1.1020170358140116, 1.1001137235396348, 1.0982359639006367,
      1.0963850282598764, 1.094562174282355, 1.0927686451729928,
      1.0910056689189003, 1.0892744575364801, 1.0875762063237155,
      1.0859120931179749, 1.0842832775597313, 1.0826909003624692,
      1.0811360825891674, 1.0796199249357576, 1.0781435070217136,
      1.0767078866883331, 1.0753140993048773, 1.0739631570829953,
      1.0726560483996912, 1.0713937371292306, 1.0701771619842424,
      1.0690072358663716, 1.0678848452267933, 1.0668108494368882,
      1.0657860801693804, 1.0648113407902853, 1.0638874057618777,
      1.0630150200571034, 1.0621948985855911, 1.0614277256316407,
      1.0607141543044407, 1.0600548060007773, 1.0594502698805479,
      1.058901102355307, 1.0584078265901109, 1.0579709320189516,
      1.0575908738739885, 1.0572680727288803, 1.0570029140563784,
      1.0567957478004859, 1.0566468879634257, 1.0565566122075185,
      1.0565251614723856, 1.0565527396074896, 1.0566395130203694,
      1.0567856103406803, 1.0569911221002943, 1.0572561004295822,
      1.0575805587701392, 1.0579644716040515, 1.0584077741999234,
      1.0589103623758271, 1.0594720922792737, 1.0600927801844389,
      1.0607722023067194, 1.0615100946347678, 1.062306152780176,
      1.0631600318448635, 1.0640713463063283, 1.0650396699208542,
      1.0660645356447709, 1.0671454355738721, 1.0682818209010545,
      1.0694731018922625, 1.0707186478808453, 1.0720177872803085,
      1.0733698076156148, 1.0747739555729867, 1.0762294370683245,
      1.0777354173342233, 1.0792910210256681, 1.0808953323443282,
      1.0825473951815883, 1.0842462132802104, 1.0859907504146784,
      1.0877799305901923, 1.089612638260302, 1.0914877185631309,
      1.0934039775761923, 1.0953601825896953, 1.0973550623983646,
      1.0993873076116343, 1.1014555709822131, 1.1035584677529222,
      1.1056945760216976, 1.1078624371247163, 1.1100605560375219,
      1.1122874017940427, 1.1145414079233822, 1.1168209729043026,
      1.119124460637215, 1.121450200933604, 1.1237964900226745,
      1.1261615910751428, 1.1285437347439689, 1.1309411197218586,
      1.1333519133154313, 1.135774252035763, 1.1382062422052448,
      1.1406459605804558, 1.1430914549909357, 1.1455407449935739,
      1.1479918225424635, 1.1504426526739904, 1.1528911742068682,
      1.1553353004569975, 1.1577729199667932, 1.1602018972488146,
      1.1626200735434198, 1.1650252675901589, 1.1674152764127013,
      1.169787876116962, 1.172140822702187, 1.1744718528847087,
      1.1767786849340673, 1.1790590195212389, 1.1813105405786288,
      1.1835309161715317, 1.185717799380789, 1.1878688291962658,
      1.1899816314208889, 1.1920538195848462, 1.1940829958696886,
      1.1960667520419697, 1.197871299504631, 1.1993620717441271,
      1.2005356199638211, 1.2013886790863189, 1.2019181747124346,
      1.2021212299567492, 1.2019951721461586, 1.2015375393680789,
      1.2007460868550124, 1.1996187931922004, 1.1981538663353313,
      1.1963497494253772, 1.1942051263877946, 1.1917189273035698,
      1.1888903335398266, 1.1857187826278883, 1.1822039728770319,
      1.1783458677124574, 1.1741446997263296, 1.1696009744309896,
      1.1647154737039962, 1.1594892589148014, 1.1539236737234988,
      1.1480203465423346, 1.1417811926512167, 1.1352084159589333,
      1.1283045104021239, 1.1210722609748291, 1.113514744381638,
      1.1056353293082508, 1.0974376763037128, 1.088925737269075,
      1.0801037545480212, 1.0709762596153471, 1.0615480713599947,
      1.0518242939598035, 1.0418103143458717, 1.0315117992550265,
      1.0209346918695097, 1.0100852080436871, 0.99896983211822521,
      0.98759531232286613, 0.9759686557695193, 0.96409712303822748,
      0.951988222359012, 0.93964970339348219, 0.9270895506206277,
      0.91431597633199779, 0.90133741324199834, 0.88816250671988717,
      0.874800106650534, 0.86125925893176458, 0.84754919661678174,
      0.83367933071070044, 0.81965924063096418, 0.80549866434194162,
      0.791207488174727, 0.77679573634364518, 0.762273560171616,
      0.74765122703714371, 0.73293910905609527, 0.71814767151218317,
      0.703287461050432, 0.68836909364843346, 0.67340324238077376,
      0.65840062499233987, 0.64337199129679123, 0.62832811041677838,
      0.61327975788298617, 0.59823770260939557, 0.58321269376250562,
      0.56821544754265985, 0.55325663389576141, 0.53834686317411928,
      0.52349667276525791, 0.50871651370782278, 0.49401673731390577,
      0.4794075818171733, 0.46489915906648177, 0.45050144128458769,
      0.43622424791173275, 0.42207723255393492, 0.408069870055731,
      0.39421144371720335, 0.3805110326749892, 0.36697749946695718,
      0.3536194778000209, 0.34044536054056168, 0.32746328794658691,
      0.31468113616067378, 0.30210650598245375, 0.28974671193911022,
      0.27760877167209869, 0.2656993956579346, 0.25402497728057022,
      0.24259158327243133, 0.23140494454085389, 0.22047044739610286,
      0.20979312519679269, 0.1993776504279175, 0.18922832722627517,
      0.17934908436740288, 0.16974346872764839, 0.16041463923435534,
      0.1513653613164776, 0.142598001867381, 0.13411452473077609,
      0.12591648672015521, 0.11800503418130745, 0.11038090010677477,
      0.10304440181035709, 0.095995439168984842, 0.089233493438516817,
      0.08275762664916031, 0.076566481585470025, 0.070658282354959773,
      0.065030835548596164, 0.05968153199553617, 0.0546073491136255,
      0.049804853856315667, 0.0452702062557465, 0.040999163560897653,
      0.036987084968787637, 0.033228936945843848, 0.029719299135642103,
      0.026452370848361516, 0.023421978126369977, 0.020621581379507488,
      0.018044283582728898, 0.015682839027898531, 0.013529662620666284,
      0.011576839712480027, 0.009816136456959999, 0.0082390106789946536,
      0.0068366232441192682, 0.0055998499148994137, 0.0045192936802634373,
      0.003585297542935178, 0.0027879577493592268, 0.0021171374457658724,
      0.00156248074329648, 0.0011134271744120958, 0.00075922652212121855,
      0.00048895400291224715, 0.0002915257836415335, 0.00015571481202278421,
      7.01669397865948E-5, 2.3417317026860421E-5, 3.9070357311663938E-6, 0.0 } ;

    TRACKING_CONTROL_KPES_DW.FromWorkspace4_PWORK.TimePtr = (void *)
      pTimeValues0;
    TRACKING_CONTROL_KPES_DW.FromWorkspace4_PWORK.DataPtr = (void *)
      pDataValues0;
    TRACKING_CONTROL_KPES_DW.FromWorkspace4_IWORK.PrevIndex = 0;
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
      29.97, 29.98, 29.990000000000002, 30.0, 30.01, 30.02, 30.03, 30.04, 30.05,
      30.060000000000002, 30.07, 30.080000000000002, 30.09, 30.1, 30.11, 30.12,
      30.13, 30.14, 30.150000000000002, 30.16, 30.17, 30.18, 30.19, 30.2, 30.21,
      30.22, 30.23, 30.240000000000002, 30.25, 30.26, 30.27, 30.28, 30.29, 30.3,
      30.310000000000002, 30.32, 30.330000000000002, 30.34, 30.35, 30.36, 30.37,
      30.38, 30.39, 30.400000000000002, 30.41, 30.42, 30.43, 30.44, 30.45, 30.46,
      30.47, 30.48, 30.490000000000002, 30.5, 30.51, 30.52, 30.53, 30.54, 30.55,
      30.560000000000002, 30.57, 30.580000000000002, 30.59, 30.6, 30.61, 30.62,
      30.63, 30.64, 30.650000000000002, 30.66, 30.67, 30.68, 30.69, 30.7, 30.71,
      30.72, 30.73, 30.740000000000002, 30.75, 30.76, 30.77, 30.78, 30.79, 30.8,
      30.810000000000002, 30.82, 30.830000000000002, 30.84, 30.85, 30.86, 30.87,
      30.88, 30.89, 30.900000000000002, 30.91, 30.92, 30.93, 30.94, 30.95, 30.96,
      30.970000000000002, 30.98, 30.990000000000002 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      -0.0, 8.6122748689519072E-5, 0.00068939284611318466, 0.0022416367053572218,
      0.0048299883682075872, 0.008454131330593766, 0.013112275003985346,
      0.018801149405148532, 0.025516001858288603, 0.033250595725138436,
      0.041997211175698962, 0.051746648009448233, 0.062488230533929677,
      0.074209814504687083, 0.086897796127564264, 0.10053712312139941,
      0.11511130783617556, 0.13060244241870636, 0.14699121601490731,
      0.16425693399474064, 0.18237753918295052, 0.20132963507569968,
      0.22108851102028121, 0.24162816933212986, 0.26292135432047603,
      0.28493958319106621, 0.307653178791537, 0.3310313041622413,
      0.35504199885251153, 0.37965221695966561, 0.40482786684538469,
      0.43053385248143711, 0.45673411637419592, 0.48339168401493632,
      0.51046870980041525, 0.53792652436587529, 0.56572568327043438,
      0.59382601697247717, 0.62218668203066085, 0.65076621346407137,
      0.67952257820310391, 0.70841322956078678, 0.73739516265263072,
      0.76642497069121862, 0.7954589020802767, 0.82445291823173483,
      0.85336275202749567, 0.88214396684682594, 0.91075201607887291,
      0.93914230303889568, 0.967270241205991, 0.99509131469905,
      1.0225611389073677, 1.0496355211914656, 1.0762705215694519,
      1.102422513303922, 1.128048243304099, 1.1531048922580727,
      1.1775501344098094, 1.2013421968960425, 1.2244399185583139,
      1.246802808145907, 1.2683911018260763, 1.2891658199184797,
      1.3090888227716773, 1.3281228657006305, 1.3462316529047584,
      1.3633798902875889, 1.379533337100701, 1.3946588563351474,
      1.4087244637857808, 1.4216993757155447, 1.4335540550482155,
      1.4442602560201288, 1.4537910672232854, 1.4621209529746035,
      1.4692257929478578, 1.4750829200073743, 1.4796711561849072,
      1.482970846743574, 1.4849638922750084, 1.4856337787791039,
      1.4849656056779834, 1.4829461117186513, 1.4795636987218073,
      1.4748084531374259, 1.468672165370237, 1.4611483468415329,
      1.4522322447571776, 1.4419208545544113, 1.4302129300034647,
      1.4171089909432588, 1.4026113286339326, 1.3867240087119579,
      1.3694528717373189, 1.350805531325332, 1.3307913698595342,
      1.30942153178492, 1.2867089144847788, 1.2626681567475917,
      1.2373156248337531, 1.2106693961559656, 1.1827492405896189,
      1.1535765994336744, 1.1231745620455886, 1.0915678401776088,
      1.0587827400445273, 1.0248471321562416, 0.98979041895303954,
      0.95364350028272393, 0.9164387367635799, 0.8782099110793854,
      0.83899218725598168, 0.79882206797202637, 0.757737349959086,
      0.715777077549639, 0.67298149443381028, 0.62939199368865439,
      0.5850510661463687, 0.54000224716999012, 0.49429006190826419,
      0.44795996910292862, 0.40105830352414851, 0.35363221711234261,
      0.3057296189061029, 0.25739911383787484, 0.20868994048112136,
      0.15965190783411284, 0.11033533122732909, 0.060790967442492183,
      0.011069949132314062, -0.038776281367581537, -0.088696038743363209,
      -0.138637461832125, -0.18854858108127132, -0.2383773862447367,
      -0.28807189422149743, -0.33758021694125756, -0.38685062920276148,
      -0.43583163636886596, -0.48447204182366876, -0.53272101409705908,
      -0.58052815356128773, -0.62784355860594443, -0.67461789119794224,
      -0.72080244173307539, -0.7663491930878501, -0.81121088378024941,
      -0.85534107014970029, -0.89869418746789032, -0.94122560989310844,
      -0.97775525611505287, -1.0033285897526381, -1.0233903624240028,
      -1.0431789161442819, -1.0626884151467, -1.0819130949131459,
      -1.1008472640994573, -1.1194853064408197, -1.1378216826357301,
      -1.1558509322084953, -1.1735676753494617, -1.1909666147322184,
      -1.2080425373072734, -1.2247903160715268, -1.2412049118127977,
      -1.2572813748291323, -1.2730148466218105, -1.2884005615619409,
      -1.3034338485296992, -1.3181101325256783, -1.3324249362540552,
      -1.3463738816766868, -1.3599526915376903, -1.3731571908580364,
      -1.385983308399573, -1.3984270780978623, -1.4104846404634817,
      -1.4221522439512011, -1.4334262462964806, -1.4443031158188722,
      -1.4547794326920083, -1.4648518901791794, -1.4745172958349804,
      -1.4837725726714477, -1.4926147602892279, -1.5010410159727692,
      -1.5090486157494851, -1.5166349554121981, -1.5237975515046311,
      -1.5305340422697808, -1.5368421885602737, -1.5427198747108226,
      -1.5481651093725555, -1.5531760263082852, -1.557750885148844,
      -1.5618880721103581, -1.5655861006718161, -1.5688436122126712,
      -1.57165937661045, -1.5740322927980985, -1.5759613892805711,
      -1.577445824610632, -1.5784848878240456, -1.5790779988329493,
      -1.5792247087782776, -1.578924700340828, -1.5781777880099517,
      -1.5769839183112522, -1.5753431699917997, -1.573255754163809,
      -1.5707220144053833, -1.5677424268199778, -1.5643176000530861,
      -1.5604482752665836, -1.5561353260709094, -1.5513797584148032,
      -1.5461827104327017, -1.5405454522495532, -1.5344693857435157,
      -1.527956044266332, -1.5210070923211374, -1.5136243251984607,
      -1.5058096685698783, -1.4975651780395145, -1.488893038653788,
      -1.4797955643694503, -1.4702751974797035, -1.460334507998734,
      -1.4499761930053312, -1.4392030759447798, -1.4280181058900139,
      -1.4164243567620445, -1.4044250265097558, -1.3920234362489334,
      -1.379223029362163, -1.366027370557821, -1.3524401448902006,
      -1.3384651567401029, -1.3241063287563708, -1.309367700758997,
      -1.2942534286036911, -1.2787677830085735, -1.2629151483430927,
      -1.2467000213796393, -1.2301270100085155, -1.2132008319161269,
      -1.1959263132270821, -1.1783083871108202, -1.1603520923526944,
      -1.1420625718902555, -1.1234450713154034, -1.1045049373424978,
      -1.0852476162428144, -1.0656786522464008, -1.045803685911272,
      -1.0256284524605965, -1.0051587800887654, -0.98440058823636589,
      -0.96335988583455179, -0.94204276952025068, -0.92045542182152473,
      -0.898604109314676, -0.87649518075303334, -0.854135065168348,
      -0.83153026994537893, -0.80868737887014808, -0.78561305015242766,
      -0.76231401442341462, -0.73879707270897366, -0.71506909437902211,
      -0.69113701507394421, -0.66700783460865665, -0.64268861485484663,
      -0.61818647760207235, -0.59350860239865078, -0.56866222437276182,
      -0.54365463203476194, -0.51849316506082332, -0.49318521205940447,
      -0.4677382083208555, -0.44215963355057025, -0.41645700958722293,
      -0.39063789810601934, -0.36470989830814615, -0.33868064459732755,
      -0.31255780424347929, -0.28634907503521906, -0.26006218292123884,
      -0.23370487964152734, -0.20728494034949455, -0.18081016122543631,
      -0.15428835708197183, -0.12772735896268694, -0.10113501173478193,
      -0.074519171675768645, -0.047887704055749006, -0.021248480716040668,
      0.0053906223555555358, 0.032021727451825271, 0.05863695757439405,
      0.085228438862892358, 0.11178830302404927, 0.13830868975978367,
      0.16478174919365782, 0.19119964429478833, 0.21755455329872717,
      0.2438386721239246, 0.27004421678353285, 0.29616342579155763,
      0.32218856256254569, 0.34811191780406453, 0.37392581190108487,
      0.39962259729160193, 0.42519466083280183, 0.45063442615680477,
      0.47593435601512762, 0.50108695461139563, 0.52608476992146336,
      0.55092039600001919, 0.57558647527288909, 0.60007570081455242,
      0.62438081860987316, 0.64849462979966355, 0.67240999290858794,
      0.69611982605537293, 0.71961710914477117, 0.74289488603955733,
      0.76594626671270782, 0.7887644293788133, 0.81134262260407,
      0.83367416739403033, 0.85575245925822041, 0.87757097025159192,
      0.89912325099161394, 0.92040293265053907, 0.94140372892172264,
      0.96211943796026655, 0.982543944296581, 1.0026712207224, 1.02249533014908,
      1.0420104274366238, 1.0612107611936765, 1.0800906755478012,
      1.0986446118851518, 1.1168671105587491, 1.1347528125655557,
      1.1522964611911446, 1.1694929036220916, 1.1863370925242591,
      1.20282408758769, 1.2189490570379931, 1.2347072791118012,
      1.2500941434973729, 1.2651051527396309, 1.2797359236088222,
      1.2939821884327163, 1.3078397963913608, 1.3213047147744688,
      1.3343730302010024, 1.3470409498004787, 1.3593048023550753,
      1.3711610394029699, 1.382606236302385, 1.3936370932554007,
      1.4042504362921906, 1.4144432182139577, 1.4242125194956821,
      1.4335555491478957, 1.4424696455366841, 1.450952277162217,
      1.4590010433952645, 1.4666136751720316, 1.4737880356464581,
      1.4805221207993613, 1.4868140600054158, 1.4926621165575042,
      1.4980646881472535, 1.5030203073025314, 1.5075276417815879,
      1.5115854949237935, 1.5151928059568065, 1.5183486502594037,
      1.5210522395810477, 1.5233029222175449, 1.5251001831429198,
      1.5264436440964722, 1.5273330636265603, 1.5277683370905966,
      1.5277494966103748, 1.5272767109840693, 1.5263502855535092,
      1.5249706620282277, 1.5231384182656704, 1.5208542680073873,
      1.518119060571548, 1.5149337805020635, 1.5112995471744561,
      1.5072176143584954, 1.5026893697370385, 1.4977163343824027,
      1.4923001621905256, 1.4864426392719832, 1.4801456832998394,
      1.4734113428170417, 1.4662417965011298, 1.4586393523868559,
      1.4506064470479589, 1.4421456447378662, 1.4332596364897061,
      1.423951239175431, 1.4142233945250489, 1.4040791681056035,
      1.3935217482617521, 1.382554445016261, 1.3711806889320737,
      1.3594040299357693, 1.3472281361036018, 1.3346567924099797,
      1.3216938994383338, 1.3083434720554512, 1.2946096380500369,
      1.2804966367355157, 1.2660088175169766, 1.251150638423647,
      1.2359266646072717, 1.2203415668068036, 1.204400119779514,
      1.1881072006993207, 1.1714677875232309, 1.1544869573264627,
      1.1371698846060112, 1.1195218395534738, 1.1015481862989798,
      1.0832543811251509, 1.0646459706524756, 1.0457285899965696,
      1.0265079608981984, 1.0069898898266365, 0.98718026605611964,
      0.96708505971800907, 0.94671031982665821, 0.92606217228226351,
      0.90514681784992357, 0.88397053011560933, 0.86253965342004313,
      0.84086060077129388, 0.818939851736975, 0.79678395031581961,
      0.77439950279017944, 0.75179317556009972, 0.7289716929597565,
      0.70594183505631769, 0.682710435432541, 0.65928437895416991,
      0.6356705995222498, 0.61187607781128783, 0.58790783899411869,
      0.56377295045417308, 0.53947851948630143, 0.515031690986261,
      0.49043964512984695, 0.46570959504296122, 0.44084878446288661,
      0.41586448539160531, 0.39076399574208481, 0.36555463697809043,
      0.34024375174899929, 0.31483870151941923, 0.28934686419516575,
      0.26377563174598279, 0.23813240782595788, 0.21242460539274208,
      0.18665964432581075, 0.16084494904448421, 0.13498794612761,
      0.10909606193445245, 0.083176720227915751, 0.057237339801531451,
      0.031285332110176478, 0.005328098905821187, -0.020626970121128765,
      -0.046572499693998563, -0.072501131294679264, -0.098405525500675439,
      -0.12427836431311003, -0.15011235347514348, -0.17590022478028253,
      -0.2016347383691651, -0.22730868501475462, -0.25291488839500026,
      -0.278446207351352, -0.30389553813397568, -0.32925581663173847,
      -0.35452002058618276, -0.37968117178958904, -0.40473233826564287,
      -0.42966663643233655, -0.45447723324638706, -0.4791573483281899,
      -0.50370025606665225, -0.5280992877040025, -0.55234783339867366,
      -0.57643934426583454, -0.60036733439613077, -0.624125382850268,
      -0.64770713562985638, -0.67110630762351786, -0.69431668452733331,
      -0.71733212473997232, -0.74014656123081957, -0.762754003380683,
      -0.78514853879496094, -0.8073243350887418, -0.82927564164231615,
      -0.85099679132722572, -0.87248220220244788, -0.89372637917983466,
      -0.914723915658312, -0.93546949512639588, -0.955957892731794,
      -0.97618397681943214, -0.99614271043535407, -1.0158291527969585,
      -1.035238460729093, -1.054365890065573, -1.0732067970156773,
      -1.0917566394945313, -1.1100109784178651, -1.1279654789602263,
      -1.1456159117770162, -1.1629581541882825, -1.1799881913253014,
      -1.1967021172398484, -1.2130961359743673, -1.2291665625942743,
      -1.2449098241804668, -1.2603224607831078, -1.2754011263363934,
      -1.2901425895326371, -1.304543734656588, -1.3186015623790797,
      -1.3323131905114534, -1.3456758547175951, -1.3586869091858376,
      -1.3713438272595428, -1.3836442020258539, -1.3955857468641375,
      -1.4071662959516182, -1.4183838047271466, -1.4292363503137644,
      -1.4397221318992126, -1.4498394710738713, -1.4595868121258855,
      -1.4689627222955339, -1.4779658919864789, -1.486595134934442,
      -1.4948493883337035, -1.5027277129209469, -1.5102292930179324,
      -1.5173534365303953, -1.5240995749048905, -1.530467263043938,
      -1.5364561791790277, -1.5420661247011473, -1.5472970239488151,
      -1.5521489239550073, -1.5566219941527124, -1.5607165260377727,
      -1.5644329327908226, -1.5677717488576355, -1.5707336294890408,
      -1.5733193502391827, -1.57552980642371, -1.5773660125366944,
      -1.5788291016279055, -1.5799203246404772, -1.5806410497080934,
      -1.5809927614127939, -1.5809770600039357, -1.5805956605789355,
      -1.5798503922243814, -1.578743197119306, -1.577276129601163,
      -1.57545135519402, -1.5732711495997587, -1.5707378976520732,
      -1.5678540922347253, -1.5646223331643658, -1.5610453260368868,
      -1.5571258810392479, -1.5528669117263165, -1.5482714337648915,
      -1.5433425636427069, -1.5380835173447633, -1.5324976089968989,
      -1.5265882494774472, -1.520358944997521, -1.513813295649395,
      -1.5069549939246378, -1.4997878232026849, -1.4923156562095574,
      -1.4845424534478726, -1.4764722615979036, -1.4681092118917944,
      -1.4594575184605603, -1.4505214766539458, -1.4413054613348577,
      -1.4318139251481758, -1.4220513967656367, -1.412022479106146,
      -1.4017318475324385, -1.3911842480256362, -1.3803844953379094,
      -1.3693374711233015, -1.3580481220476515, -1.3465214578792526,
      -1.3347625495600486, -1.3227765272576102, -1.3105685784002983,
      -1.2981439456936861, -1.285507925122142, -1.27266586393409,
      -1.2596231586116877, -1.2463852528266306, -1.2329576353827627,
      -1.2193458381457241, -1.2055554339599206, -1.1915920345547035,
      -1.1774612884402487, -1.1631688787932701, -1.1487205213335308,
      -1.1341219621922936, -1.11937897577339, -1.1044973626074672,
      -1.089482947200046, -1.0743415758743053, -1.0590791146099403,
      -1.0437014468780517, -1.0282144714729586, -1.0126241003419572,
      -0.99693625641396511, -0.98115687142764507, -0.96529188375915609,
      -0.94934723625174111, -0.93332887404605536, -0.917242742413757,
      -0.9010947845944709, -0.884890939636342, -0.86863714024130922,
      -0.85233931061639168, -0.83600336433158073, -0.81963520218419128,
      -0.8032407100709742, -0.7868257568696525, -0.7703961923295688,
      -0.75395784497183571, -0.73751652000091839, -0.72107799722786337,
      -0.70464802900562262, -0.68823233817749763, -0.67183661603918743,
      -0.65546652031584784, -0.63912767315400154, -0.62282565912917476,
      -0.60656602327065112, -0.59035426910317856, -0.57419585670697271,
      -0.5580962007960637, -0.54206066881621184, -0.52609457906285251,
      -0.51020319881968068, -0.49439174251889562, -0.47866536992267067,
      -0.46302918432795537, -0.44748823079425581, -0.43204749439530565,
      -0.41671189849543805, -0.40148630305031097, -0.38637550293426348,
      -0.3713842262933279, -0.3565171329251855, -0.34177881268666227,
      -0.32717378392869845, -0.31270649196053879, -0.29838130754242109,
      -0.28420252540775676, -0.27017436281559526, -0.25630095813377568,
      -0.24258636945259643, -0.22903457323024057, -0.21564946297072857,
      -0.20243484793324806, -0.18939445187512011, -0.17653191182794115,
      -0.16385077690711863, -0.15135450715611276, -0.13904647242455004,
      -0.12692995128162615, -0.11500812996475786, -0.10328410136380083,
      -0.091760864040892634, -0.080441321287373968, -0.069328280216769164,
      -0.0584244508942971, -0.047732445504667841, -0.037254777556384414,
      -0.026993861124125516, -0.016952010129412193, -0.0071314376587807,
      0.0024657446787590934, 0.011837527356205779, 0.020982003494172924,
      0.029897369386989253, 0.038581924990422616, 0.047034074369068812,
      0.055252326105016472, 0.063235293666886974, 0.070981695738649278,
      0.078490356509143835, 0.085760205921497676, 0.0927902798826978,
      0.099579720432898436, 0.10612777587515558, 0.11243380086459993,
      0.11849725645814133, 0.12431771012380287, 0.12989483570932381,
      0.13522841337231448, 0.14031832946925946, 0.14516457640483568,
      0.14976725244184905, 0.15412656147092746, 0.15824281274114177,
      0.16211642055076539, 0.16574790389864222, 0.169137886096726,
      0.17228709434352565, 0.17519635925828211, 0.17786661437676868,
      0.18029889560895845, 0.18249434065766124, 0.18445418840005562,
      0.18617977823089224, 0.1876725493683491, 0.18893404012287732,
      0.1899658871283943, 0.19076982453796595, 0.19134768318247861,
      0.19170138969297054, 0.19183296558830518, 0.19174452632697978,
      0.19143828032374541, 0.19091652793190406, 0.19018166039203968,
      0.18923615874611291, 0.18808259271831229, 0.18672361956379288,
      0.1851619828839341, 0.18340051141016281, 0.18144211775615146,
      0.17928979713852555, 0.17694662606746375, 0.17441576100695561,
      0.17170043700548787, 0.16880396629736311, 0.16572973687593381,
      0.16248121103850446, 0.15906192390357293, 0.15547548190173516,
      0.15172556123960265, 0.14781590633814773, 0.14375032824593154,
      0.1395327030279255, 0.13516697012953283, 0.13065713071813978,
      0.126007246001572, 0.12122143552379097, 0.11630387544025225,
      0.11125879677135546, 0.10609048363615874, 0.10080327146644523,
      0.095401545201814028, 0.089889737466799208, 0.084272326730163286,
      0.078553835447216516, 0.072738828186453358, 0.066831909740412351,
      0.060837723221453165, 0.054760948144240207, 0.048606298493992707,
      0.042378520782716325, 0.0360823920933847, 0.029722718112590942,
      0.023304331153249463, 0.016832088167327817, 0.010310868749141775,
      0.0037455731313530104, -0.0028588798272500327, -0.0094975546610200721,
      -0.01616550132150819, -0.022857757208250493, -0.029569349203085259,
      -0.036295295708519186, -0.043030608689428741, -0.049770295716523534,
      -0.056509362011493244, -0.063242812492948733, -0.06996565382264712,
      -0.07667289645021555, -0.0833595566569385, -0.090020658597227993,
      -0.096651236336657981, -0.10324633588669972, -0.10980101723472536,
      -0.11631035636853441, -0.12276944729507062, -0.1291734040521991,
      -0.13551736271333614, -0.14179648338311798, -0.14800595218452783,
      -0.15414098323659803, -0.16019682062054294, -0.16616874033585161,
      -0.1720520522440131, -0.17784210199922981, -0.18353427296638306,
      -0.18912398812436629, -0.19460671195520104, -0.19997795231731824,
      -0.20523326230254429, -0.21036824207657961, -0.21537854070160969,
      -0.22025985794136752, -0.22500794604644528, -0.2296186115200709,
      -0.234087716864779, -0.2384111823071583, -0.24258498750126495,
      -0.24660517321041767, -0.25046784296587887, -0.254169164702006,
      -0.25770537236785013, -0.26107276751389796, -0.2642677208539323,
      -0.26728667380086363, -0.2701261399760182, -0.27278270669231525,
      -0.27525303640965648, -0.27753386816183373, -0.27962201895573341,
      -0.28151438514125204, -0.28320794375085773, -0.28469975381068291,
      -0.28598695762037951, -0.2870667820006173, -0.287936539511397,
      -0.28859362963727436, -0.28903553993976988, -0.28925984717805336,
      -0.28926421839548583, -0.2890464119725516, -0.28860427864695609,
      -0.287935762497788, -0.2870389018952374, -0.28591183041624724,
      -0.2845527777227968, -0.28296007040619681, -0.28113213279411009,
      -0.27906748772131068, -0.27676475726360689, -0.274222663434959,
      -0.27144002884754181, -0.26841577733311434, -0.26514893452797572,
      -0.26163862841862007, -0.25788408985003003, -0.253884652995545,
      -0.24963975578683997, -0.24514894030672207, -0.24041185314151406,
      -0.23542824569558421, -0.23019797446608917, -0.2247210012773441,
      -0.21899739347768699, -0.21302732409493219, -0.20681107195329165,
      -0.20034902175068739, -0.19364166409507191, -0.18668959550234684,
      -0.1794935183538609, -0.17205424081403831, -0.1643726767086941,
      -0.15644984536314133, -0.14828687140032823, -0.139884984500262,
      -0.13124551911930796, -0.12236991416955373, -0.11325971265943277,
      -0.10391656129451698, -0.094342210039912514, -0.084538511643008213,
      -0.074507421117066458, -0.064250995187016366, -0.053771391695807948,
      -0.043070868973183823, -0.032151785166190792, -0.021016597531120954,
      -0.0096678616887226742, 0.0018917691586462352, 0.013659545046474111,
      0.025632620104719051, 0.03780805345122451, 0.050182810120448187,
      0.062753762029556182, 0.075517688978922692, 0.088471279688009052,
      0.10161113286693219, 0.11493375832201359, 0.12843557809511208,
      0.14211292763731825, 0.15596205701593813, 0.16997913215384494,
      0.18416023610236368, 0.1985013703449654, 0.21299845613287804,
      0.22764733585279237, 0.24244377442429982, 0.25738346072739432,
      0.27246200905997436, 0.287674960624435, 0.30301778504298693,
      0.318485881900772, 0.33407458231687492, 0.34977915054179209,
      0.36559478558186531, 0.3815166228494502, 0.39753973583837682,
      0.41365913782337221, 0.42986978358466682, 0.44616657115581332,
      0.46254434359346164, 0.47899789077065957, 0.4955219511907577,
      0.51211121382236258, 0.52876031995558781, 0.545463865076446,
      0.56221640076128487, 0.579012436589489, 0.59584644207286863,
      0.6127128486028941, 0.62960605141420223, 0.646520411563281,
      0.6634502579214715, 0.68038988918347321, 0.69733357588808542,
      0.71427556245206436, 0.73121006921621934, 0.74813129450205729,
      0.76503341667957769, 0.78191059624473369, 0.79875697790559186,
      0.81556669267720583, 0.83233385998325415, 0.84905258976552689,
      0.86571698459912039, 0.88232114181198906, 0.89885915561025687,
      0.91532511920675308, 0.93171312695197561, 0.94801727646862943,
      0.96423167078626248, 0.98035042047714827, 0.99636764579286063,
      1.0122774787982951, 1.0280740655053797, 1.0437515680044585,
      1.0593041665919849, 1.074726061893821, 1.0900114769858125,
      1.1051546595067032, 1.1201498837656272, 1.134991452843894,
      1.1496737006873059, 1.1641909941906974, 1.1785377352733579,
      1.1927083629444584, 1.2066973553582012, 1.2204992318560075,
      1.2341085549981685, 1.2475199325822572, 1.2607280196469886,
      1.2737275204627578, 1.2865131905062441, 1.2990798384195268,
      1.3114223279534767, 1.3235355798921715, 1.3354145739606145,
      1.3470543507143005, 1.3584500134078037, 1.3695967298448477,
      1.3804897342069595, 1.3911243288614559, 1.4014958861459978,
      1.41159985013286, 1.4214317383675981, 1.4309871435846, 1.4402617353995368,
      1.4492512619742191, 1.4579515516568002, 1.4663585145962728,
      1.4744681443290224, 1.4822765193386238, 1.4897798045859318,
      1.4969742530122467, 1.5038562070133974, 1.5104220998818352,
      1.516668457220945, 1.5225918983265661, 1.5281891375379686,
      1.5334569855583755, 1.5383923507398112, 1.5429922403377896,
      1.5472537617327862, 1.5511741236162222, 1.5547506371436022,
      1.5579807170523248, 1.5608618827452361, 1.5633917593374624,
      1.5655680786695629, 1.5673886802818546, 1.5688515123531757,
      1.5699546326046505, 1.5706962091625505, 1.5710745213860262,
      1.5710879606568668, 1.5707350311294659, 1.5700143504439541,
      1.5689246503988177, 1.5674647775859973, 1.5656336939864042,
      1.5634304775246133, 1.5608543225850202, 1.5579045404875369,
      1.5545805599229778, 1.550881927349266, 1.5468083073444796,
      1.5423594829212179, 1.5375353558012208, 1.5323359466458637,
      1.5267613952476728, 1.5208119606805048, 1.5144880214080951,
      1.5077900753514266, 1.5007187399155451, 1.4932747519728131,
      1.4854589678064658, 1.4772723630139633, 1.4687160323660167,
      1.4597911896253624, 1.4504991673255727, 1.4408414165063859,
      1.4308195064099005, 1.4204351241336397, 1.409690074243527,
      1.3985862783471297, 1.3871257746230954, 1.3753107173125934,
      1.3631433761695051, 1.3506261358693155, 1.3377614953790624,
      1.3245520672861033, 1.3110005770885198, 1.2971098624451753,
      1.2828828723857983, 1.2683226664832896, 1.2534324139863873,
      1.2382153929145254, 1.2226749891134487, 1.2068146952741794,
      1.1906381099126648, 1.1741489363139874, 1.1573509814394669,
      1.1402481547954388, 1.1228444672675826, 1.1051440299187489,
      1.0871510527520323, 1.0688698434385968, 1.0503048060094669,
      1.03146043951563, 1.0123413366534655, 0.99295218235602623,
      0.97329775235309579, 0.95338291169813438, 0.93321261326311056,
      0.91279189620351808, 0.8921258843911507, 0.87121978481710849,
      0.85007888596625036, 0.82870855616062988, 0.80711424187572323,
      0.78530146602846529, 0.763275826237529, 0.74104299305730581,
      0.71860870818499656, 0.69597878264265156, 0.67315909493443116,
      0.650155589178944, 0.62697427321804167, 0.60362121670252855,
      0.58010254915610415, 0.55642445801665907, 0.53259318665699062,
      0.50861503238488459, 0.48449634442364531, 0.46024352187390855,
      0.43586301165647695, 0.41136130643799385, 0.38674494253957686,
      0.36202049782926626, 0.33719458959950377, 0.31227387242868221,
      0.28726503602998832, 0.26217480308660673, 0.23700992707375529,
      0.21177719007006054, 0.18648340055712317, 0.16113539120913312,
      0.13574001667310459, 0.11030415134024819, 0.08483468710935485,
      0.059338531143306047, 0.033822603618938907, 0.0082938354712460242,
      -0.017240833866938678, -0.042774458729528474, -0.068300089485119175,
      -0.093810774807239539, -0.11929956394618167, -0.14475950900208231,
      -0.17018366719789654, -0.19556510315156678, -0.220896891147159,
      -0.2461721174033035, -0.27138388233879762, -0.29652530283451822,
      -0.32158951449041256, -0.346569673877319, -0.37145896078269697,
      -0.396250580449123, -0.42093776580523279, -0.44551377968822087,
      -0.46997191705682889, -0.49430550719457561, -0.51850791590194456,
      -0.54257254767683993, -0.56649284788329413, -0.59026230490660947,
      -0.613874452294618, -0.63732287088453488, -0.66060119091447567,
      -0.68370309411867436, -0.70662231580661761, -0.729352646923358,
      -0.75188793609264271, -0.77422209164131328, -0.79634908360249923,
      -0.8182629457002718, -0.83995777731222365, -0.86142774541007894,
      -0.88266708647903458, -0.903670108412588, -0.9244311923844758,
      -0.94494479469662063, -0.96520544860070168, -0.98520776609473548,
      -1.0049464396939425, -1.0244162441736124, -1.043612038285104,
      -1.0625287664436605, -1.0811614603861772, -1.0995052408021135,
      -1.117555318932985, -1.1353069981406414, -1.1527556754461623,
      -1.1698968430361638, -1.1867260897376528, -1.2032391024602482,
      -1.2194316676037968, -1.235299672434613, -1.2508391064267366,
      -1.2660460625681706, -1.2809167386326477, -1.2954474384154617,
      -1.3096345729337604, -1.3234746615912751, -1.3369643333043086,
      -1.3501003275920946, -1.3628794956303993, -1.3752988012647061,
      -1.387355321987326, -1.3990462498755261, -1.4103688924898348,
      -1.4213206737343342, -1.4318991346758152, -1.4421019343248522,
      -1.4519268503763454, -1.4613717799083636, -1.4704347400420656,
      -1.4791138685593879, -1.4874074244809325, -1.495313788601581,
      -1.5028314639855431, -1.5099590764182313, -1.51669537481753,
      -1.5230392316039445, -1.5289896430264898, -1.5345457294478206,
      -1.53970673558623, -1.5444720307160236, -1.5488411088259528,
      -1.5528135887323655, -1.5563892141526403, -1.5595678537353024,
      -1.5623495010467114, -1.5647342745156945, -1.5667224173350232,
      -1.5683142973214876, -1.5695104067322907, -1.5703113620390357,
      -1.5707179036598797, -1.5707308956492945, -1.5703513253452916,
      -1.5695803029742301, -1.5684190612141353, -1.5668689547167951,
      -1.5649314595869543, -1.5626081728210284, -1.5599008117030992,
      -1.5568112131621346, -1.5533413330868202, -1.5494932455990564,
      -1.5452691422888947, -1.5406713314083964, -1.5357022370254843,
      -1.5303643981393189, -1.524660467754043, -1.5185932119160102,
      -1.5121655087130248, -1.5053803472318428, -1.4982408264806277,
      -1.4907501542735053, -1.4829116460770839, -1.4747287238217364,
      -1.4662049146745355, -1.4573438497777096, -1.4481492629520814,
      -1.4386249893640015, -1.4287749641590157, -1.4186032210603852,
      -1.4081138909356217, -1.3973112003278498, -1.3861994699566347,
      -1.3747831131852033, -1.36306663445689, -1.3510546277012714,
      -1.3387517747078812, -1.3261628434723287, -1.3132926865120744,
      -1.3001462391526952, -1.2867285177880792, -1.2730446181111292,
      -1.2590997133188111, -1.2448990522912862, -1.2304479577435841,
      -1.2157518243541536, -1.2008161168684728, -1.18564636817857,
      -1.1702481773808435, -1.15462720780968, -1.1387891850506169,
      -1.122739894933535, -1.1064851815032819, -1.0900309449725654,
      -1.0733831396554323, -1.0565477718826601, -1.0395308978997839,
      -1.0223386217490946, -1.0049770931348891, -0.98745250527338291,
      -0.969771092729897, -0.95193912924067348, -0.93396292552235016,
      -0.91584882706984017, -0.89760321194217219, -0.87923248853818581,
      -0.86074309336235555, -0.84214148878166828, -0.82343416077403453,
      -0.804627616669346, -0.78572838288434876, -0.766743002651132,
      -0.74767803374050035, -0.7285400461818089, -0.709335619978106,
      -0.69007134282009019, -0.67075380779738947, -0.65138961110823568,
      -0.63198534976991694, -0.61254761932959734, -0.59308301157599153,
      -0.57359811225319868, -0.55409949877822251, -0.53459373796105358,
      -0.51508738373050578, -0.49558697486482506, -0.47609903272813797,
      -0.45663005901417225, -0.43718653349793346, -0.41777491179553716,
      -0.3984016231331664, -0.37907306812635355, -0.35979561657024306,
      -0.34057560524144054, -0.32141933571175468, -0.30233307217574867,
      -0.28332303929175567, -0.26439542003775951, -0.24555635358308189,
      -0.22681193317530196, -0.20816820404470526, -0.1896311613266462,
      -0.17120674800177679, -0.15290085285556745, -0.13471930845754551,
      -0.11666788916132846, -0.09875230912514299, -0.080978220355604286,
      -0.063351210773311642, -0.045876802300604959, -0.028560448975446014,
      -0.011407535088903374, 0.0055766266526148323, 0.022386796938589838,
      0.0390178116391611, 0.055464583562810504, 0.071722104185813346,
      0.087785445353807043, 0.10364976095498467, 0.11931028856203817,
      0.13476235104487319, 0.15000135815285462, 0.16502280806558464,
      0.17982228891156757, 0.1943954802543543, 0.2087381545466882,
      0.22284617855012265, 0.23671551472157998, 0.25034222256564131,
      0.26372245995080484, 0.2768524843916601, 0.28972865429462136,
      0.30234743016788368, 0.31470537579453955, 0.32679915936833642,
      0.33862555459258259, 0.35018144174044552, 0.3614638086782051,
      0.37246975184883307, 0.38319647721693684, 0.39364130117489188,
      0.40380165140891683, 0.41367506772569168, 0.42325920283847535,
      0.43255182311279039, 0.44155080927148316, 0.4502541570593917,
      0.4586599778659296, 0.46676649930662739, 0.47457206576313371,
      0.48207513888129855, 0.48927429802786349, 0.49616824070415294,
      0.50275578291779055, 0.50903585951238539, 0.51500752445390308,
      0.52066995107545677, 0.52602243227892531, 0.53106438069274753,
      0.535795328788841, 0.54021492895506329, 0.54432295352533411,
      0.54811929476751342, 0.5516039648267419, 0.5547770956269974,
      0.55763893873036607, 0.5601898651519841, 0.56243036513297184,
      0.56436104787157637, 0.56598264120978448, 0.56729599127937724,
      0.56830206210480949, 0.56900193516321629, 0.569396808904155,
      0.5694879982254496, 0.569276933908781, 0.56876516201363569,
      0.56795434322887239, 0.56684625218470608, 0.5654427767226754,
      0.56374591712584166, 0.56175778530864284, 0.55948060396630139,
      0.5569167056847687, 0.55406853201101014, 0.55093863248550434,
      0.54752966363433353, 0.54384438792354262, 0.53988567267598309,
      0.53565648894983986, 0.53115991038093247, 0.52639911198678069,
      0.52137736893535513, 0.51609805527794694, 0.510564642645672,
      0.50478069891162181, 0.4987498868184721, 0.49247596257169796,
      0.48596277439909624, 0.47921426107755871, 0.4722344504275045,
      0.46502745777447946, 0.45759748437986114, 0.44994881584068797,
      0.44208582045870248, 0.43401294758005732, 0.42573472590571215,
      0.41725576177259432, 0.40858073740757989, 0.3997144091541201,
      0.39066160567135244, 0.38142722610775814, 0.37201623824891467,
      0.36243367664060216, 0.3526846406882706, 0.3427742927322332,
      0.3327078560999468, 0.32249061313712324, 0.31212790321687,
      0.30162512072787839, 0.29098771304300675, 0.280221178468804,
      0.2693310641753639, 0.25832296410954669, 0.24720251689107048,
      0.23597540369108497, 0.22464734609648965, 0.213224103958919,
      0.2017114732292756, 0.19011528377972226, 0.1784413972123135,
      0.16669570465649416, 0.15488412455566866, 0.14301260044292968,
      0.13108709870807425, 0.11911360635566114, 0.10709812875531417,
      0.095046687385171663, 0.08296531756876345, 0.070860066206852243,
      0.058736989504622396, 0.04660215069481987, 0.03446161775809771,
      0.022321461141128682, 0.010187751473656132, -0.0019334427157014357,
      -0.014036057282751667, -0.026114034750305729, -0.038161326588612356,
      -0.050171895493101817, -0.062139717659272169, -0.074058785052129511,
      -0.085923107671650067, -0.097726715811660009, -0.10946366231185622,
      -0.12112802480279976, -0.13271390794239105, -0.14421544564288433,
      -0.15562680328852552, -0.16694217994214577, -0.1781558105400243,
      -0.18926196807519793, -0.20025496576687601, -0.21112915921642111,
      -0.22187894854896639, -0.23249878053907644, -0.2429831507204657,
      -0.25332660547933689, -0.26352374412954577, -0.27356922096905573,
      -0.28345774731814183, -0.29318409353741931, -0.30274309102481611,
      -0.3121296341919555, -0.32133868241779456, -0.33036526198059896,
      -0.33920446796551096, -0.34785146614847551, -0.35630149485540091,
      -0.36454986679575141, -0.37259197087088597, -0.38042327395380304,
      -0.38803932264349356, -0.3954357449900554, -0.40260825219168045,
      -0.40955264026254251, -0.41626479166993069, -0.42274067694254913,
      -0.42897635624567304, -0.434967980926763, -0.44071179502779106,
      -0.44620413676505882, -0.45144143997592329, -0.45642023553098071,
      -0.46113715271418482, -0.46558892056535067, -0.46977236918896326,
      -0.47368443102707614, -0.47732214209608065, -0.48068264318637449,
      -0.48376318102509785, -0.4865611094016557, -0.48907389025462228,
      -0.49129909472136407, -0.49323440414745728, -0.49487761105834693,
      -0.49622662009076673, -0.49727944888450731, -0.49803422893428489,
      -0.49848920640065358, -0.49864274288051685, -0.49849331613672754,
      -0.49803952078563091, -0.49728006894331717, -0.49621379083097888,
      -0.49483963533650754, -0.49315667053483275, -0.49116408416577323,
      -0.48886118406883522, -0.48624739857524507, -0.48332227685665063,
      -0.480085489231429, -0.4765368274268646, -0.472676204798821,
      -0.46850365650656256, -0.46401933964526509, -0.45922353333387878,
      -0.4541166387603835, -0.44869917918288049, -0.44297179988502078,
      -0.43693526809115246, -0.4305904728347168, -0.42393842478467353,
      -0.41698025602730282, -0.40971721980433179, -0.40215069020824468,
      -0.3942821618329645, -0.38611324938264957, -0.37764568723535868,
      -0.36888132896541148, -0.35982214682101155, -0.35047023116021231,
      -0.34082778984434631, -0.33089714758756483, -0.3206807452659845,
      -0.31018113918274243, -0.29940100029328759, -0.288343113387824,
      -0.27701037623257296, -0.2654057986704651, -0.25353250168043667,
      -0.24139371639723642, -0.22899278309050669, -0.21633315010412452,
      -0.20341837275595231, -0.19025211219925581, -0.17683813424496475,
      -0.16318030814563081, -0.14928260534160839, -0.13514909816976517,
      -0.12078395853538906, -0.10619145654726109, -0.091375959116648253,
      -0.0763419285208194, -0.061093920931122508, -0.045636584906817296,
      -0.029974659854604208, -0.014112974453950622, 0.0019435549495569208,
      0.018189925984513466, 0.034621051925399396, 0.051231763395521691,
      0.068016810101358183, 0.084970862597290739, 0.10208851407897064,
      0.11936428220666016, 0.13679261095699571, 0.15436787250159098,
      0.17208436911450387, 0.18993633510456093, 0.2079179387738872,
      0.22602328440261482, 0.24424641425687088, 0.26258131062142925,
      0.28102189785483894, 0.2995620444669897, 0.31819556521954351,
      0.33691622324562737, 0.35571773219046016, 0.37459375837251807,
      0.39353792296159268, 0.41254380417663261, 0.43160493949946177,
      0.45071482790542022, 0.46986693211147235, 0.48905468083563708,
      0.50827147107383985, 0.52751067038931965, 0.54676561921376876,
      0.5660296331608482, 0.58529600535086179, 0.6045580087458553,
      0.62380889849371313, 0.64304191428069235, 0.66225028269162067,
      0.68142721957904284, 0.70056593243499721, 0.71965962277083939,
      0.73870148850156325, 0.75768472633154593, 0.77660253414590918,
      0.79544811340162591, 0.81421467152184079, 0.83289542428856667,
      0.85148359823582076, 0.86997243304290006, 0.88835518392304758,
      0.9066251240096328, 0.92477554674028051, 0.94279976823612788,
      0.96069112967197934, 0.97844299964512249, 0.996048776535018,
      1.0135018908542675, 1.0307958075910837, 1.0479240285434346,
      1.0648800946426344, 1.0816575882637434, 1.0982501355264807,
      1.1146514085819641, 1.130855127886645, 1.1468550644602804,
      1.162645042130797, 1.1782189397625793, 1.1935706934669632,
      1.2086942987961515, 1.2235838129187808, 1.2382333567770007,
      1.2526371172213879, 1.2667893491285158, 1.2806843774954442,
      1.2943165995126957, 1.3076804866133609, 1.3207705864992914,
      1.3335815251468548, 1.3461080087796156, 1.3583448258222564,
      1.3702868488277691, 1.3819290363744896, 1.3932664349359656,
      1.4042941807248126, 1.4150075015080639, 1.4254017183885741,
      1.4354722475602795, 1.4452146020309089, 1.4546243933149743,
      1.463697333091061, 1.4724292348297288, 1.4808160153891092,
      1.4888536965718018, 1.4965384066522911, 1.5038663818671778,
      1.5108339678712324, 1.5174376211550327, 1.5236739104283405,
      1.529539517967917, 1.5350312409245803, 1.5401459925925143,
      1.5448808036427453, 1.5492328233185815, 1.553199320585495,
      1.5567776852483823, 1.5599654290259612, 1.562760186584522,
      1.5651597165299667, 1.5671619023599925, 1.5687647533765006,
      1.5699664055514444, 1.5707651223544368, 1.5711592955360261,
      1.5711474458696364, 1.5707282238471982, 1.5699004103353649,
      1.5686629171869666, 1.5670147878059779, 1.5649551976720355,
      1.5624834548180879, 1.5595990002664246, 1.5563014084156597,
      1.5525903873870301, 1.5484657793246825, 1.5439275606505802,
      1.5389758422728268, 1.5336108697496358, 1.5278330234124815,
      1.5216428184342869, 1.5150409048600866, 1.5080280675908708,
      1.5006052263193475, 1.4927734354204816, 1.4845338837982875,
      1.475887894688461, 1.4668369254107705, 1.4573825670795049,
      1.4475265442683296, 1.4372707146297488, 1.4266170684672561,
      1.4155677282659676, 1.4041249481776175, 1.3922911134572435,
      1.3800687398600313, 1.3674604729915121, 1.3544690876138865,
      1.3410974869070511, 1.3273487016881251, 1.3132258895875606,
      1.2987323341799417, 1.2838714440713879, 1.268646751947357,
      1.2530619135776233, 1.2371207067744847, 1.2208270303152562,
      1.2041849028204634, 1.1871984615908524, 1.1698719614033708,
      1.1522097732686722, 1.134216383148303, 1.1158963906302697,
      1.0972545075682194, 1.0782955566794326, 1.0590244701086442,
      1.0394462879492583, 1.0195661567298171, 0.99938932786590629,
      0.9789211560711355, 0.95816709773558872, 0.93713270926858216,
      0.91582364540744043, 0.89424565748900364, 0.87240459169167983,
      0.85030638724330065, 0.82795707459486045, 0.805362773563984,
      0.78252969144700346, 0.75946412110232631, 0.73617243899949847,
      0.7126611032429383, 0.6889366515663, 0.66500569929804665,
      0.64087493729954847, 0.6165511298774482, 0.59204111267080073,
      0.56735179051066742, 0.542490135257379, 0.51746318361310928,
      0.49227803491200756, 0.46694184888652507, 0.44146184341378014,
      0.41584529224089395, 0.39009952268925235, 0.36423191334034266,
      0.33824989170227637, 0.3121609318597518, 0.28597255210556838,
      0.25969231255666414, 0.23332781275526235, 0.2068866892542531,
      0.18037661318937412, 0.15380528783861352, 0.1271804461686204,
      0.10050984837049129, 0.073801279384851273, 0.04706254641661068,
      0.020301476441592515, -0.006474086295660402, -0.033256282790628686,
      -0.060037241794498486, -0.0868090823354459, -0.1135639162441606,
      -0.14029385068360123, -0.16699099068245649, -0.19364744166945194,
      -0.22025531200989182, -0.24680671554311279, -0.27329377411838995,
      -0.29970862013125682, -0.32604339905605989, -0.35229027197731438,
      -0.37844141811647886, -0.40448903735367553, -0.43042535274579269,
      -0.45624261303679886, -0.48193309516059074, -0.50748910673847736,
      -0.53290298856595886, -0.55816711708828259, -0.58327390687024772,
      -0.60821581305130679, -0.63298533378934563, -0.657575012691572,
      -0.68197744123207682, -0.70618526115603775, -0.73019116686602015,
      -0.75398790779427849, -0.7775682907579905, -0.80092518229633636,
      -0.82405151098871121, -0.84694026975517123, -0.86958451813613136,
      -0.891977384551123, -0.91411206853654625, -0.93598184296032949,
      -0.95758005621600462, -0.97890013438943635, -0.99993558340367072,
      -1.0206799911394611, -1.0411270295279829, -1.061270456616054,
      -1.0811041186074153, -1.1006219518761697, -1.1198179849454555,
      -1.1386863404444356, -1.157221237033337, -1.1754169912947838,
      -1.1932680195962642, -1.2107688399224361, -1.2279140736729239,
      -1.2446984474263343, -1.2611167946735216, -1.2771640575142347,
      -1.2928352883212477, -1.3081256513660435, -1.323030424411709,
      -1.3375450002697304, -1.3516648883165057, -1.3653857159756435,
      -1.3787032301614948, -1.3916132986848149, -1.404111911617214,
      -1.4161951826198167, -1.4278593502309171, -1.4391007791136474,
      -1.449915961259399, -1.4603015171569109, -1.4702541969188223,
      -1.4797708813579706, -1.4888485830334459, -1.4974844472480362,
      -1.5056757530034148, -1.513419913912033, -1.5207144790668916,
      -1.527557133869311, -1.5339457008074253, -1.5398781401957768,
      -1.5453525508685391, -1.550367170828312, -1.5549203778479721,
      -1.559010690031269, -1.5626367663270442, -1.5657974069952905,
      -1.5684915540311346, -1.5707182915407571, -1.5724768460745542,
      -1.5737665869097726, -1.5745870262905446, -1.5749378196230834,
      -1.5748187656210459, -1.5742298064041624, -1.5731710275566244,
      -1.5716426581360605, -1.5696450706306126, -1.5671787808785831,
      -1.5642444479390185, -1.5608428739145628, -1.5569750037268486,
      -1.5526419248506589, -1.5478448670002141, -1.5425852017667478,
      -1.5368644422148714, -1.53068424243036, -1.5240463970245788,
      -1.5169528405911157, -1.509405647120428, -1.5014070293691133,
      -1.4929593381816082, -1.4840650617706228, -1.4747268249532841,
      -1.464947388342728, -1.4547296474937137, -1.4440766320102663,
      -1.4329915046055519, -1.421477560122766, -1.4095382245085215,
      -1.3971770537494357, -1.3843977327686514, -1.3712040742696983,
      -1.3576000175530856, -1.343589627286119, -1.3291770922325175,
      -1.3143667239419263, -1.2991629554015309, -1.2835703396518567,
      -1.2675935483576195, -1.2512373703453084, -1.2345067101031546,
      -1.2174065862434451, -1.1999421299275592, -1.1821185832573218,
      -1.1639412976308798, -1.1454157320609879, -1.1265474514634684,
      -1.107342124908546, -1.0878055238417348, -1.067943520270493,
      -1.0477620849188021, -1.0272672853547713, -1.0064652840824855,
      -0.9853623366042551, -0.963964789459392, -0.942279078228584,
      -0.92031172551029516, -0.89806933887446561, -0.8755586087860443,
      -0.852786306503474, -0.82975928195087689, -0.80648446156864673,
      -0.78296884613781592, -0.75921950858166343, -0.73524359174619758,
      -0.71104830615678483, -0.686640927757757, -0.66202879562725936,
      -0.63721930967576523, -0.61221992832646488, -0.58703816617534355,
      -0.56168159163571074, -0.53615782456663019, -0.51047453388659547,
      -0.48463943516898678, -0.45866028822856153, -0.43254489469139823,
      -0.4063010955536881, -0.37993676872915805, -0.3534598265845737,
      -0.32687821346880785, -0.30019990322785545, -0.27343289671485943,
      -0.24658521929338786, -0.21966491833160709, -0.19268006069170085,
      -0.16563873021499328, -0.13854902520263074, -0.11141905589233038,
      -0.08425694193301593, -0.057070809858662634, -0.029868790559695685,
      -0.0026590167555352053, 0.02455037953167424, 0.051751269503520485,
      0.07893553010674835, 0.10609504655338058, 0.13322171483612094,
      0.16030744423834239, 0.18734415983875774, 0.21432380500938555,
      0.24123834390626334, 0.26807976395147887, 0.29484007830709663,
      0.32151132833783652, 0.34808558606518514, 0.37455495660810545,
      0.40091158061154342, 0.4271476366645246, 0.453255343701929,
      0.47922696339184245, 0.50505480250908585, 0.530731215291236,
      0.55624860577881041, 0.58159943013729865, 0.60677619896065871,
      0.6317714795570496, 0.65657789821198254, 0.68118814243416714,
      0.70559496317837811, 0.72979117704609875, 0.75376966846488147,
      0.77752339184183883, 0.80104537369699069, 0.82432871476752023,
      0.84736659208908971, 0.87015226105216692, 0.89267905742892129,
      0.91494039937284066, 0.936929789393779, 0.95864081630275644,
      0.98006715712208736, 1.0012025789753678, 1.022040940941354,
      1.0425761958760882, 1.062802392205892, 1.0827136756867981,
      1.1023042911332284, 1.1215685841110734, 1.1405010025982174,
      1.1590960986107204, 1.1773485297945003, 1.1952530609806977,
      1.2128045657066913, 1.2299980277011109, 1.2468285423296581,
      1.2632913180065561, 1.2793816775681028, 1.2950950596072401,
      1.3104270197694836, 1.325373232011962, 1.3399294898227034,
      1.35409170740081, 1.3678559207925087, 1.3812182889942966,
      1.3941750950137242, 1.4067227468818495, 1.4188577786351073,
      1.430576851250992, 1.4418767535420236, 1.4527544030069288,
      1.4632068466426236, 1.4732312617137555, 1.4828249564754008,
      1.4919853708579662, 1.5007100771070496, 1.5089967803813555,
      1.5168433193045219, 1.52424766647709, 1.5312079289444467,
      1.5377223486184586, 1.5437893026594869, 1.549407303810332,
      1.5545750006913515, 1.5592911780466117, 1.5635547569487387,
      1.5673647949626461, 1.5707204862603417, 1.5736211616920412,
      1.5760662888188635, 1.5780554718991537, 1.5795884518247632,
      1.5806651060234083, 1.5812854483129466, 1.5814496287111925,
      1.5811579332030317, 1.5804107834655678, 1.5792087365498548,
      1.5775524845176376, 1.5754428540382575, 1.5728808059405786,
      1.5698674347246979, 1.566403968028131, 1.5624917660533768,
      1.5581323209538227, 1.5533272561747371, 1.5480783257561883,
      1.5423874135943367, 1.5362565326623661, 1.5296878241882743,
      1.5226835567977095, 1.515246125613805, 1.5073780513186685,
      1.4990819791733487, 1.49036067800373, 1.4812170391489781,
      1.4716540753620564, 1.4616749196854468, 1.4512828242841451,
      1.4404811592420381, 1.4292734113220211, 1.4176631826910977,
      1.4056541896131003, 1.3932502611015405, 1.380455337541749,
      1.3672734692788915, 1.3537088151727672, 1.3397656411181855,
      1.3254483185362214, 1.3107613228329043, 1.2957092318247128,
      1.2802967241368253, 1.2645285775696116, 1.2484096674370493,
      1.2319449648742415, 1.2151395351193677, 1.1979985357680945,
      1.1805272149996022, 1.1627309097747089, 1.1446150440141176,
      1.1261851267484819, 1.1074467502396281, 1.0884055880866892,
      1.069067393304058, 1.0494379963782832, 1.0295233033015825,
      1.0093292935869684, 0.98886201826356879, 0.96812759784864888,
      0.9471322203042678, 0.9258821389743408, 0.90438367050500168,
      0.88264319274676473, 0.86066714264228128, 0.83846201409872989,
      0.81603435584467487, 0.79339076927372765, 0.77053790627453744,
      0.74748246705056909, 0.72423119792470614, 0.70079088913616416,
      0.67716837262669416, 0.6533705198160128, 0.62940423936961543,
      0.605276474959243, 0.58099420301680049, 0.55656443047863513,
      0.53199419252800162, 0.50729055033239512, 0.48246058877439074,
      0.45751141418073216, 0.43245015205004378, 0.40728394477702357,
      0.38201994937622907, 0.35666533520605986, 0.33122728169278787,
      0.30571297605678877, 0.2801296110389655, 0.25448438263200857,
      0.22878448781505289, 0.20303712229074056, 0.17724947822921711,
      0.15142874201781498, 0.12558209201612147, 0.099716696319809187,
      0.073839710531610661, 0.047958275540406124, 0.022079515312023928,
      -0.0037894653120097129, -0.029641582803803052, -0.055469777126716593,
      -0.0812670139010558, -0.10702628655603569, -0.13274061846883239,
      -0.15840306508847829, -0.18400671604540789, -0.20954469724430605,
      -0.23501017294055793, -0.26039634780066584, -0.28569646894389178,
      -0.31090382796488231, -0.33601176293917728, -0.36101366040675259,
      -0.38590295733603996, -0.41067314306868263, -0.4353177612395106,
      -0.45983041167631949, -0.48420475227703907, -0.50843450086252551,
      -0.53251343700524445, -0.556435403835038, -0.5801943098185115,
      -0.60378413051246538, -0.62719891029147878, -0.65043276405001116,
      -0.67347987887690686, -0.69633451569840843, -0.71899101089869943,
      -0.74144377790880589, -0.76368730876563118, -0.78571617564300322,
      -0.80752503235095363, -0.82910861580583572, -0.850461747469106,
      -0.87157933475379334, -0.892456372400149, -0.91308794381893821,
      -0.93346922240057129, -0.95359547279379264, -0.97346205214929726,
      -0.99306441132961409, -1.0123980960863526, -1.031458748199898,
      -1.0502421065892278, -1.0687440083822504, -1.086960389952125,
      -1.1048872879210982, -1.1225208401229887, -1.1398572865338428,
      -1.1568929701652266, -1.1736243379206341, -1.1900479414132334,
      -1.2061604377506565, -1.2219585902813506, -1.2374392693002265,
      -1.2525994527206863, -1.2674362267079846, -1.281946786274329,
      -1.2961284358363219, -1.3099785897347618, -1.3234947727153894,
      -1.3366746203734521, -1.349515879557307, -1.3620164087354238,
      -1.3741741783266634, -1.3859872709879677, -1.3974538818678932,
      -1.4085723188185346, -1.4193410025719635, -1.4297584668766432,
      -1.4398233585948164, -1.4495344377650103, -1.4588905776222412,
      -1.4678907645830803, -1.4765340981909454, -1.4848197910260914,
      -1.4927471685736506, -1.5003156690574213, -1.5075248432374249,
      -1.5143743541652062, -1.5208639769053087, -1.5269935982203824,
      -1.5327632162182561, -1.538172939961675, -1.5432229890431231,
      -1.5479136931232731, -1.5522454914346837, -1.5562189322454039,
      -1.5598346722928937, -1.563093476180806, -1.5659962157388292,
      -1.5685438693531382, -1.5707375212547172, -1.5725783607830781,
      -1.5740676816106762, -1.5752068809339661, -1.5759974586374115,
      -1.5764410164170646, -1.5765392568783583, -1.5762939825996698,
      -1.5757070951660932, -1.5747805941693285, -1.5735165761810557,
      -1.5719172336955469, -1.5699848540392207, -1.5677218182567219,
      -1.5651305999639029, -1.5622137641745095, -1.5589739661002222,
      -1.5554139499215121, -1.5515365475325571, -1.5473446772624324,
      -1.5428413425656369, -1.5380296306912589, -1.5329127113291603,
      -1.5274938352267731, -1.5217763327870968, -1.5157636126406266,
      -1.5094591601979668, -1.5028665361778368, -1.4959893751150741,
      -1.4888313838492939, -1.4813963399901635, -1.4736880903662939,
      -1.4657105494533875, -1.45746769778678, -1.4489635803510319,
      -1.4402023049575332, -1.4311880406053883, -1.4219250158226087,
      -1.4124175169953481, -1.4026698866814209, -1.3926865219118421,
      -1.3824718724742797, -1.3720304391889941, -1.3613667721717972,
      -1.3504854690823476, -1.3393911733645023, -1.3280885724769991,
      -1.3165823961134306, -1.3048774144125821, -1.2929784361651373,
      -1.2808903070055939, -1.2686179076042963, -1.2561661518506619,
      -1.2435399850285009, -1.2307443819927639, -1.2177843453351915,
      -1.2046649035502546, -1.1913911091991438, -1.1779680370696295,
      -1.1644007823335327, -1.1506944587063495, -1.1368541966059207,
      -1.1228851413092729, -1.1087924511131955, -1.0945812954958676,
      -1.0802568532808152, -1.0658243108032488, -1.051288860081623,
      -1.0366556969931884, -1.0219300194549636, -1.0071170256076283,
      -0.99222191200927135, -0.97724987183614309, -0.96220609308757477,
      -0.94709575680223335, -0.93192403528117629, -0.91669609032366273,
      -0.90141707146840477, -0.88609211424869549, -0.87072633845906766,
      -0.85532484643064, -0.83989272132315007, -0.82443502542621661,
      -0.80895679847783952, -0.79346305599313793, -0.77795878761041648,
      -0.76244895545385893, -0.74693849250795841, -0.73143230101228474,
      -0.71593525087045773, -0.7004521780788624, -0.68498788317136539,
      -0.66954712968332653, -0.654134642636875, -0.63875510704135807,
      -0.62341316641598921, -0.60811342133467916, -0.5928604279894405,
      -0.57765869677599413, -0.56251269090194045, -0.54742682501530748,
      -0.53240546385856535, -0.51745292094463868, -0.50257345725493963,
      -0.48777127996412134, -0.47305054118833467, -0.45841533675743262,
      -0.44386970501315293, -0.42941762563308644, -0.415063018479409,
      -0.40080974247573586, -0.38666159450978221, -0.3726223083616555,
      -0.35869555366117789, -0.34488493487253741, -0.33119399030624036,
      -0.31762619115909951, -0.30418494058368034, -0.29087357278541681,
      -0.27769535214890489, -0.26465347239375558, -0.25175105575981332,
      -0.23899115222185086, -0.22637673873307854, -0.21391071850113585,
      -0.20159592029233439, -0.18943509776628134, -0.17743092884262945,
      -0.16558601509673385, -0.1539028811871434, -0.14238397431382302,
      -0.13103166370781741, -0.11984824015121368, -0.10883591552869563,
      -0.097996822411430137, -0.087333013670889054, -0.0768464621252479,
      -0.066539060216443152, -0.056412619719127345, -0.046468871481423708,
      -0.036709465197271814, -0.027135969209435864, -0.017749870344474884,
      -0.0085525737803184444, 0.00045459705612095196, 0.0092704005598023033,
      0.017893676985936517, 0.02632334845863505, 0.034558418947378135,
      0.042597974211811905, 0.050441181717987248, 0.058087290521115068,
      0.065535631118653084, 0.072785615273508908, 0.079836735805384793,
      0.086688566353289767, 0.09334076110732091, 0.099793054510073309,
      0.10604526092973469, 0.11209727430200561, 0.11794906774434095,
      0.12360069314088215, 0.1290522806970423, 0.13430403846776137,
      0.13935625185631559, 0.14420928308527567, 0.14886357063998196,
      0.15331962868440402, 0.15757804645043841, 0.16163948759946656,
      0.16550468955803052, 0.169174462827896, 0.1726496902694922,
      0.17593132635969647, 0.17902039642588122, 0.18191799585382362,
      0.18462528927204852, 0.18714350971247695, 0.18947395774592662,
      0.1916180005969311, 0.19357707123414528, 0.19535266743814644,
      0.19694635084868381, 0.19835974598960004, 0.19959453927254492,
      0.20065247798099356, 0.20153536923310109, 0.20224507892573781,
      0.20278353065860555, 0.20315270464018753, 0.20335463657592967,
      0.2033914165363403, 0.20326518781095693, 0.20297814574383055,
      0.20253253655218451, 0.20193065613105951, 0.20117484884126111,
      0.20026750628307372, 0.1992110660559509, 0.19800801050451766,
      0.19666086545076375, 0.19517219891483223, 0.1935446198224208,
      0.19178077670130431, 0.18988335636773007, 0.18785508260057826,
      0.18569871480665198, 0.18341704667723022, 0.18101290483474694,
      0.17848914747149827, 0.1758486629812521, 0.17309436858375196,
      0.17022920894170043, 0.16725615477292477, 0.16417820145717341,
      0.16099836763657016, 0.1577196938139547, 0.15434524094624422,
      0.15087808903469269, 0.14732133571346043, 0.14367809483524535,
      0.13995149505641477, 0.13614467842047187, 0.13226079894170947,
      0.12830302118998213, 0.12427451887440365, 0.12017847343057921,
      0.11601807260851718, 0.11179650906343558, 0.10751697895053043,
      0.10318268052194265, 0.098796812729275874, 0.094362573830172,
      0.0898831600012048, 0.085361763954896072, 0.08080157356492762,
      0.0762057704978963, 0.071577528852197342, 0.06692001380526201,
      0.062236380268322608, 0.057529771553289762, 0.052803318045792094,
      0.0480601358895171, 0.043303325682842821, 0.038535971184351078,
      0.033761138031163818, 0.028981872469269816, 0.024201200096119441,
      0.019422124617582154, 0.014647626616682043, 0.00988066233764705,
      0.0051241624842269778, 0.00038103103270349084, -0.00434585593888102,
      -0.00905365140624356, -0.013739538538460066, -0.018400731820289843,
      -0.023034478156110656, -0.027638057958812613, -0.032208786219068551,
      -0.036744013555801376, -0.04124112724907069, -0.04569755225306657,
      -0.050110752190403132, -0.054478230324353318, -0.058797530513933362,
      -0.06306623814638225, -0.0672819810467865, -0.071442430372294224,
      -0.07554530147896471, -0.079588354767858333, -0.083569396512330307,
      -0.087486279658279459, -0.091336904603985955, -0.095119219957164686,
      -0.098831223267206059, -0.10247096173509269, -0.1060365328979818,
      -0.10952608529146934, -0.11293781908653618, -0.11626998670141413,
      -0.1195208933907036, -0.12268889780684714, -0.12577241253777507,
      -0.12876990462053203, -0.13167989602785038, -0.13450096412839516,
      -0.13723174212353653, -0.13987091945626715, -0.14241724219472557,
      -0.1448695133905695, -0.14722659340868119, -0.14948740023370863,
      -0.15165090974706186, -0.15371615597961402, -0.15568223133793135,
      -0.15754828680122682, -0.15931353209495464, -0.16097723583619863,
      -0.16253872565239816, -0.16399738827371019, -0.16535266959844327,
      -0.16660407473169458, -0.16775116799839032, -0.16879357292880842,
      -0.16973097221724492, -0.17056310765496771, -0.17128978003667181,
      -0.17191084904090526, -0.17242623308262683, -0.17283590914155914,
      -0.17313991256432773, -0.17333833683942737, -0.17343133334717745,
      -0.17341911108460015, -0.17330193636382699, -0.17308013248596246,
      -0.17275407938964019, -0.17232421327411462, -0.1717910261989678,
      -0.17115506565739488, -0.17041693412633094, -0.16957728859312932,
      -0.16863684005675311, -0.16759635300643086, -0.16645664487658163,
      -0.1652185854787582, -0.16388309641063653, -0.16245115044262529,
      -0.1609237708823964, -0.15930203091670042, -0.15758705293185463,
      -0.15578000781365295, -0.15388211422560411, -0.15189463786599347,
      -0.14981889070523655, -0.14765623020327781, -0.14540805850726013,
      -0.14307582162990412, -0.14066100860833397, -0.13816515064550022,
      -0.13558982023314248, -0.13293663025602259, -0.13020723308019566,
      -0.12740331962352297, -0.1245266184099174, -0.12157889460742403,
      -0.11856194905049108, -0.11547761724754328, -0.112327768372902,
      -0.10911430424508606, -0.10583915829114558, -0.10250429449666583,
      -0.099111706344137018, -0.0956634157379697, -0.0921614719172534,
      -0.088607950357690535, -0.0850049516619689, -0.081354600439755356,
      -0.077659044176993638, -0.073920452096444739, -0.070141014008819169,
      -0.066322939154729615, -0.06246845503917875, -0.058579806258120815,
      -0.054659253318180057, -0.050709071449529491, -0.046731549412649565,
      -0.042728988299956881, -0.038703700331688955, -0.03465800764804812,
      -0.030594241097171113, -0.026514739018746469, -0.022421846026184737,
      -0.0183179117851266, -0.01420528979086985, -0.010086336144010881,
      -0.0059634083250938051, -0.0018388639698941171, 0.0022849403560787837,
      0.00640565038209098, 0.01052091535486155, 0.014628389259871911,
      0.0187257320404814, 0.022810610813340168, 0.026880701081511433,
      0.030933687943002879, 0.034967267294661784, 0.038979147031437955,
      0.0429670482403654, 0.046928706388217223, 0.05086187250222915,
      0.05476431434448098, 0.058633817578725017, 0.062468186928644975,
      0.066265247327647353, 0.070022845060270622, 0.07373884889302508,
      0.07741115119585984, 0.081037669053376, 0.084616345363898865,
      0.0881451499282445, 0.091622080525868024, 0.095045163978659614,
      0.0984124572022592, 0.1017220482433045, 0.10497205730341187,
      0.10816063774851645, 0.11128597710408321, 0.1143462980348644,
      0.11733985930830998, 0.12026495674350136, 0.12311992414247004,
      0.12590313420517688, 0.12861299942753746, 0.13124797298075533,
      0.133806549573759, 0.13628726629696677, 0.138688703447268,
      0.14100948533311308, 0.14324828106127313, 0.14540380530302688,
      0.14747481904018625, 0.14946013029116684, 0.1513585948149353,
      0.15316911679546291, 0.1548906495032287, 0.15652219593557448,
      0.15806280943497011, 0.15951159428468151, 0.16086770628235614,
      0.16213035328936157, 0.16329879575833428, 0.16437234723717736,
      0.16535037484829782, 0.16623229974442122, 0.16701759754134482,
      0.16770579872525196, 0.16829648903556119, 0.168789309822899,
      0.16918395838324912, 0.16948018826577288, 0.16967780955602724,
      0.16977668913439686, 0.16977675090700611, 0.1696779760126757,
      0.16948040300454409, 0.16918412800446619, 0.16878930483130297,
      0.16829614510478844, 0.16770491832149095, 0.16701595190539509,
      0.16622963123282064, 0.1653463996293438, 0.16436675834175313,
      0.16329126648332651, 0.16212054095320685, 0.16085525632774916,
      0.15949614472647095, 0.15804399565296004, 0.15649965580726621,
      0.15486402887300629, 0.15313807527857265, 0.15132281193127917,
      0.14941931192580132, 0.14742870422732904, 0.14535217332762063,
      0.14319095887584149, 0.14094635528321431, 0.13861971130303702,
      0.13621242958421778, 0.13372596619984087, 0.13116183015206287,
      0.12852158284800896, 0.12580683755531166, 0.12301925883176064,
      0.12016056192844217, 0.11723251217084202, 0.11423692431599373,
      0.11117566188417986, 0.10805063646839538, 0.10486380702116273,
      0.10161717911601552, 0.098312804188529376, 0.094952778754089168,
      0.091539243602636058, 0.08807438297334845, 0.084560423705772464,
      0.080999634370039819, 0.077394324378031842, 0.073746843071577542,
      0.070059578791660637, 0.066334957927062538, 0.062575443943314824,
      0.058783536393926118, 0.054961769910878484, 0.051112713177615655,
      0.047238967883379453, 0.043343167660563231, 0.039427977005602473,
      0.035496090179532792, 0.031550230096622618, 0.027593147194283109,
      0.02362761828715915, 0.01965644540850062, 0.015682454634069809,
      0.011708494892959359, 0.007737436765852158, 0.0037721712678907252,
      -0.00018439138042003871, -0.0041293229933737395, -0.00805967867507657,
      -0.011972498082624383, -0.015864806701637927, -0.01973361713329649,
      -0.023575930388575698, -0.027388737194245533, -0.031169019307076384,
      -0.034913750835020206, -0.038619899568227138, -0.042284428315887204,
      -0.045904296250710443, -0.049476460259413269, -0.052997876297691857,
      -0.056465500752734911, -0.059876291808037718, -0.0632272108136336,
      -0.066515223659503769, -0.069737302151064259, -0.072890425388440372,
      -0.075971581147539727, -0.078977767260448042, -0.081905992998486069,
      -0.0847532804557534, -0.087516665929944976, -0.090193201304724344,
      -0.09277995542912508, -0.095274015495185688, -0.097672488413471509,
      -0.099972502184193429, -0.10217120726615732, -0.10426577794009573,
      -0.10625341366732548, -0.10813134044403103, -0.10989681214781623,
      -0.11154711187892034, -0.11307955329422878, -0.11449148193304581,
      -0.11578027653508649, -0.11694335034937692, -0.11797815243409755,
      -0.11888216894709012, -0.11965292442400999, -0.12028798304793122,
      -0.1207849499065187, -0.12114147223582208, -0.12135524065418882,
      -0.12142399038087881, -0.1213455024418412, -0.12111760486182269,
      -0.12073817384138631, -0.12020513491870756, -0.11951646411593442,
      -0.11867018906956103, -0.11766439014382728, -0.11649720152750147,
      -0.1151668123125751, -0.11367146755521217, -0.11200946931812189,
      -0.11017917769362796, -0.10817901180812059, -0.10600745080581402,
      -0.10366303481222026, -0.10114436587732119, -0.098450108897165531,
      -0.095578992514191261, -0.092529809995136353, -0.089301420086575725,
      -0.085892747847861772, -0.082302785460654587, -0.078530593015248576,
      -0.074575299272029924, -0.070436102399162967, -0.0661122706864706,
      -0.05531932956547421, -0.031763677699437456, -0.0017214112547181781,
      0.02851313848887321, 0.058922209524538006, 0.089487562275955446,
      0.12019049212173262, 0.15101184291041225, 0.18193202145451559,
      0.21293101299633588, 0.24398839763493627, 0.27508336769931951,
      0.30619474605356289, 0.33730100531895346, 0.36838028799081951,
      0.39941042743359706, 0.43036896973140754, 0.46123319636888077,
      0.49198014771805126, 0.522586647304879, 0.55302932682543893,
      0.58328465188324374, 0.6133289484147284, 0.64313842976952906,
      0.67268922441308432, 0.70195740421026664, 0.730919013260416,
      0.75955009723756528, 0.78782673319894314, 0.81572505982220955,
      0.84322130802385742, 0.87029183192208392, 0.89691314009245593,
      0.92306192707617163, 0.94871510509196089, 0.97384983590537566,
      0.998443562806455, 1.0224740426474694, 1.045919377892307,
      1.0687580486257948, 1.0909689444762516, 1.1125313963933752,
      1.1334252082409644, 1.1536306881434668, 1.173128679539895,
      1.1919005918949819, 1.209928431011851, 1.2271948288981411,
      1.2436830731341606, 1.2593771356925234, 1.274261701155071,
      1.2883221942859122, 1.301544806901378, 1.3139165239937414,
      1.3254251490597673, 1.3360593285866993, 1.3458085756498603,
      1.3546632925721125, 1.3626147926102352, 1.3696553206140507,
      1.3757780726240414, 1.3809772143640449, 1.3852478985872125,
      1.3885862812418566, 1.3909895364173466, 1.3924558700369869,
      1.3929845322598187, 1.3925758285686893, 1.3912311295054678,
      1.3889528790303936, 1.3857446014788906, 1.3816109070888,
      1.3765574960794462, 1.3705911612598676, 1.3637197891494881,
      1.35595235959174, 1.3472989438526521, 1.3377707011875635,
      1.3273798738684595, 1.3161397806641804, 1.3040648087703874,
      1.2911704041848546, 1.2774730605256741, 1.2629903063021439,
      1.247740690633921, 1.2317437674303058, 1.2150200780389901,
      1.1975911323734079, 1.1794793885345907, 1.1607082309444228,
      1.14130194700788, 1.1212857023238865, 1.1006855144740451,
      1.0795282254087248, 1.0578414724617351, 1.0356536580242852,
      1.0129939179097569, 0.98989208844490506, 0.9663786723246236,
      0.94248480326980033, 0.91824220952675406, 0.89368317625714944,
      0.86884050685859437, 0.8437474832648949, 0.818437825276517,
      0.79294564896959752, 0.76730542423867309, 0.74155193152499932,
      0.7157202177891363, 0.68984555178265794, 0.66396337867959221,
      0.63810927412726426, 0.61231889777772486, 0.58662794636358684,
      0.56107210638078864, 0.53568700644449829, 0.51050816938224319,
      0.48557096413316642, 0.46091055751883553, 0.43656186595434454,
      0.4125595071684402, 0.38893775200142944, 0.36573047635026484,
      0.3429711133302496, 0.32069260572365621, 0.29892735878353066,
      0.2777071934645603, 0.25706330014862422, 0.23702619293482569,
      0.21762566456317653, 0.19889074203969709, 0.18084964303127726,
      0.16352973309622221, 0.14695748381819831, 0.13115843190749465,
      0.11615713933453456, 0.10197715455880565, 0.0886409749147832,
      0.0761700102158, 0.064584547634826753, 0.053903717920065909,
      0.044145463001054631, 0.035326505040139143, 0.027462316981533105,
      0.020567094648779895, 0.014653730439423963, 0.0097337886635156228,
      0.0058174825705649075, 0.0029136531072841442, 0.0010297494462581018,
      0.00034362264649386037, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      -9.791115842214116E-5, -0.00078371255357277, -0.0025481522207165546,
      -0.0054899480242029831, -0.0096082898853379946, -0.01490059295388357,
      -0.021362491629592674, -0.028987836110236143, -0.037768691484930735,
      -0.047695339387881945, -0.058756282223926773, -0.070938249973503537,
      -0.08422620958087336, -0.09860337692561727, -0.11405123137357186,
      -0.13054953289953936, -0.14807634177027681, -0.16660804077234606,
      -0.18611935996561813, -0.20658340393939167, -0.22797168154421807,
      -0.25025413806876939, -0.27339918982728739, -0.29737376111946345,
      -0.32214332352085762, -0.34767193745834613, -0.37392229602149862,
      -0.40085577095721192, -0.42843246079152236, -0.45661124101905587,
      -0.48534981629726426, -0.51460477457936493, -0.54433164311671567,
      -0.57448494625829838, -0.6050182649719954, -0.63588429800950164,
      -0.66703492463384706, -0.69842126882597932, -0.729993764884223,
      -0.76170222432796564, -0.793495904014673, -0.82532357537729228,
      -0.85713359468666528, -0.88887397424199577, -0.92049245439068728,
      -0.95193657627678008, -0.98315375521631, -1.0140913545960311,
      -1.0446967601911332, -1.0749174547964249, -1.1047010930642147,
      -1.1339955764421155, -1.1627491281026918, -1.1909103677567232,
      -1.2184283862418839, -1.2452528197779189, -1.2713339237799453,
      -1.2966226461216828, -1.3210706997403887, -1.3446306344764281,
      -1.3672559080406643, -1.3889009560036929, -1.409521260702508,
      -1.4290734189606233, -1.4475152085195884, -1.4648056530811453,
      -1.4809050858607966, -1.4957752115557152, -1.5093791666314595,
      -1.5216815778342372, -1.532648618838063, -1.5422480649379275,
      -1.5504493457030324, -1.5572235955068889, -1.5625437018534292,
      -1.5663843514217888, -1.5687220737551619, -1.5695352825221429,
      -1.5688043142827666, -1.5665114646943854, -1.5626410220963436,
      -1.5571792984158326, -1.5501146573412548, -1.541437539712802,
      -1.531140486084541, -1.5192181564156513, -1.505667346852517,
      -1.4904870035681848, -1.4736782336289709, -1.4552443128629731,
      -1.4351906907091185, -1.4135249920295612, -1.3902570158734793,
      -1.3653987311837135, -1.3389642694422932, -1.3109699142564035,
      -1.2814340878891206, -1.2503773347451108, -1.2178223018253376,
      -1.1837937161689485, -1.1483183593063984, -1.1114250387500126,
      -1.0731445565544553, -1.0335096749837178, -0.99255507932427456,
      -0.95031733789001, -0.90683485926722962, -0.86214784685352186,
      -0.8162982507475206, -0.7693297170506368, -0.72128753464613049,
      -0.6722185795249519, -0.62217125673047435, -0.57119543999902767,
      -0.51934240917639274, -0.46666478549327556, -0.41321646478719126,
      -0.35905254876027437, -0.304229274366363, -0.24880394142355855,
      -0.19283483855095912, -0.13638116753144069, -0.079502966204292244,
      -0.022261029994596872, 0.035283167812005765, 0.093067556938219914,
      0.15102955201493615, 0.20910613539744086, 0.26723394078138596,
      0.32534933750150125, 0.38338851539364266, 0.44128757010045666,
      0.49898258869963641, 0.55640973553281414, 0.61350533811342867,
      0.670205972990478, 0.72644855144546816, 0.7821704048994842,
      0.83730936990812277, 0.8918038726213432, 0.94559301258674755,
      0.99861664577505693, 1.0508154667071381, 1.1021310895639171,
      1.1525061281606064, 1.2018842746689173, 1.2502103769723538,
      1.2974305145408693, 1.3434920727140187, 1.388343815283176,
      1.4272876760750162, 1.4559510206700363, 1.4794355998450957,
      1.502539309673355, 1.5252548254638996, 1.5475749243170187,
      1.5694924876296632, 1.5910005035718864, 1.6120920695319216,
      1.6327603945300735, 1.6529988016001957, 1.6728007301378451,
      1.6921597382144145, 1.7110695048561981, 1.7295238322879365,
      1.7475166481395783, 1.7650420076157565, 1.7820940956273108,
      1.7986672288834589, 1.8147558579446594, 1.8303545692348917,
      1.8454580870127979, 1.86006127530086, 1.8741591397720037,
      1.887746829593016, 1.9008196392236536, 1.9133730101713857,
      1.9254025327008244, 1.9369039474969774, 1.9478731472819626,
      1.9583061783848972, 1.9681992422633281, 1.97754869697707,
      1.9863510586125159, 1.9946030026577559, 2.0023013653275257,
      2.0094431448379173, 2.0160255026298324, 2.0220457645409149,
      2.0275014219257712, 2.0323901327235308, 2.0367097224726858,
      2.0404581852727959, 2.0436336846923013, 2.0462345546224485,
      2.0482593000769582, 2.0497065979369213, 2.0505752976404925,
      2.0508644218174368, 2.0505731668680869, 2.0497009034862326,
      2.0482471771259871, 2.0462117084125246, 2.0435943934957272,
      2.0403953043475318, 2.0366146890023762, 2.032252971739946,
      2.027310753211685, 2.0217888105090243, 2.0156880971751567,
      2.0090097431582974, 2.0017550547082164, 1.9939255142149626,
      1.9855227799897384, 1.9765486859885228, 1.9670052414781214,
      1.9568946306444439, 1.9462192121435418, 1.9349815185952672,
      1.92318425601964, 1.9108303032160305, 1.8979227110854213,
      1.8844647018958753, 1.8704596684912074, 1.8559111734431684,
      1.8408229481477674, 1.8251988918652691, 1.8090430707043343,
      1.7923597165513157, 1.7751532259436582, 1.757428158888878,
      1.7391892376291391, 1.7204413453515011, 1.7011895248440141,
      1.681438977099446, 1.6611950598649823, 1.6404632861400188,
      1.6192493226215396, 1.5975589880981065, 1.5753982517926188,
      1.5527732316543239, 1.5296901926008286, 1.5061555447105233,
      1.4821758413658002, 1.4577577773480497, 1.4329081868848002,
      1.4076340416491737, 1.3819424487132568, 1.3558406484551244,
      1.3293360124203724, 1.3024360411394642, 1.2751483619007398,
      1.2474807264799592, 1.2194410088277308, 1.1910372027147609,
      1.1622774193359098, 1.1331698848743621, 1.1037229380259763,
      1.0739450274843567, 1.0438447093889849, 1.0134306447354238,
      0.98271159674936293, 0.95169642822531175, 0.92039409883057843,
      0.88881366237554194, 0.85696426405108472, 0.82485513763376128,
      0.79249560266028074, 0.759895061571702, 0.72706299682818654,
      0.69400896799566225, 0.66074260880519764, 0.62727362418574184,
      0.5936117872715968, 0.5597669363854636, 0.52574897199779658,
      0.49156785366413169, 0.45723359694045357, 0.42275627027840118,
      0.38814599190095633, 0.35341292665967938, 0.31856728287470409,
      0.28361930915807348, 0.24857929122221711, 0.213457548673923,
      0.17826443179499424, 0.14301031831107633, 0.10770561014927783,
      0.072360730185694264, 0.036986118984250159, 0.0015922315276695172,
      -0.033810466058692396, -0.0692114997881021, -0.10460039109859699,
      -0.13996666014269843, -0.17529982907931158, -0.21058942536705796,
      -0.24582498505765193, -0.28099605608875566, -0.31609220157444279,
      -0.35110300309267062, -0.38601806396884258, -0.42082701255380173,
      -0.45551950549551495, -0.49008523100340073, -0.5245139121041954,
      -0.558795309887817, -0.59291922674279562, -0.62687550957989613,
      -0.66065405304281544, -0.69424480270489708, -0.72763775825075871,
      -0.76082297664192233, -0.79379057526523356, -0.82653073506329422,
      -0.85903370364520282, -0.89128979837706745, -0.92328940945167837,
      -0.95502300293537357, -0.98648112379133723, -1.017654398878642,
      -1.0485335399262421, -1.0791093464801755, -1.1093727088230545,
      -1.1393146108655292, -1.1689261330085916, -1.1981984549750468,
      -1.22712285860979, -1.2556907306479006, -1.2838935654495878,
      -1.3117229677012763, -1.3391706550809133, -1.3662284608878263,
      -1.3928883366361178, -1.4191423546100261, -1.4449827103801747,
      -1.4704017252812098, -1.4953918488490578, -1.5199456612167632,
      -1.5440558754688891, -1.5677153399526247, -1.590917040545798,
      -1.6136541028808198, -1.6359197945235171, -1.6577075271057804,
      -1.6790108584120691, -1.6998234944190944, -1.7201392912873972,
      -1.73995225730381, -1.7592565547752446, -1.7780465018729685,
      -1.796316574425902, -1.8140614076626758, -1.8312757979022434,
      -1.8479547041924411, -1.8640932498956111, -1.8796867242204374,
      -1.8947305837001898, -1.9092204536169002, -1.9231521293704534,
      -1.9365215777917302, -1.9493249384005733, -1.9615585246076623,
      -1.9732188248592868, -1.9843025037254423, -1.9948064029299559,
      -2.0047275423233963, -2.0140631207978466, -2.0228105171431121,
      -2.030967290844012, -2.0385311828187413, -2.045500116098578,
      -2.0518721964476971, -2.0576457129227546, -2.0628191383730963,
      -2.0673911298814054, -2.0713605291434507, -2.0747263627872519,
      -2.077487842632364, -2.0796443658885018, -2.081195515293504,
      -2.0821410591902705, -2.0824809515431113, -2.0822153318938739,
      -2.0813445252571996, -2.0798690419540908, -2.0777895773859689,
      -2.075107011748095, -2.0718224096819, -2.0679370198677933,
      -2.0634522745566009, -2.05836978904188, -2.0526913610722453,
      -2.0464189702037836, -2.0395547770928242, -2.0321011227294976,
      -2.0240605276129728, -2.0154356908674291, -2.0062294892992032,
      -1.9964449763963814, -1.9860853812709702, -1.9751541075433159,
      -1.9636547321685074, -1.9515910042079088, -1.9389668435435821,
      -1.9257863395366752, -1.9120537496307008, -1.8977734979001031,
      -1.882950173544907, -1.8675885293303509, -1.8516934799740821,
      -1.8352701004799079, -1.8183236244203427, -1.8008594421667163,
      -1.7828830990683808, -1.7644002935812129, -1.745416875346993,
      -1.7259388432235725, -1.7059723432660041, -1.6855236666599798,
      -1.6645992476086302, -1.6432056611732424, -1.6213496210673153,
      -1.5990379774061712, -1.5762777144128661, -1.5530759480805318,
      -1.5294399237920677, -1.5053770138979616, -1.4808947152532708,
      -1.4560006467152218, -1.4307025466008985, -1.4050082701059807,
      -1.378925786687542, -1.3524631774093097, -1.3256286322512605,
      -1.2984304473843855, -1.2708770224121362, -1.2429768575788356,
      -1.21473855094521, -1.1861707955348082, -1.1572823764480569,
      -1.128082167949231, -1.0985791305247985, -1.0687823079142376,
      -1.0387008241152462, -1.0083438803637816, -0.97772075209068243,
      -0.94684078585445286, -0.91571339625263493, -0.88434806281238676,
      -0.85275432686137387, -0.8209417883795066, -0.78892010283310732,
      -0.75669897799299168, -0.72428817073666985, -0.69169748383624619,
      -0.65893676273293422, -0.62601589229926091, -0.59294479359070806,
      -0.55973342058698128, -0.52639175692397189, -0.49292981261871366,
      -0.45935762078749143, -0.42568523435807654, -0.39192272277772872,
      -0.35808016871787463, -0.32416766477697112, -0.29019531018162231,
      -0.25617320748840228, -0.2221114592866161, -0.18802016490309503,
      -0.15390941711090544, -0.11978929884269575, -0.085669879908858049,
      -0.051561213723440011, -0.017473334037664975, 0.016583748317977216,
      0.050600048680816655, 0.084565611792388334, 0.11847051502211496,
      0.15230487157800934, 0.18605883370242224, 0.21972259585228329,
      0.2532863978630337, 0.28674052809433587, 0.32007532655703014,
      0.35328118802070074, 0.38634856509947846, 0.4192679713165185,
      0.45202998414563056, 0.48462524802755846, 0.51704447736283787,
      0.54927845947769627, 0.58131805756276067, 0.61315421358401268,
      0.64477795116451286, 0.67618037843615963, 0.70735269086040253,
      0.73828617401691576, 0.76897220635919172, 0.79940226193694719,
      0.829567913083232, 0.85946083306551346, 0.88907279870118161,
      0.91839569293488232, 0.94742150737789943, 0.9761423448080716,
      1.0045504216296122, 1.0326380702929112, 1.0603977416718569,
      1.0878220073988207, 1.1149035621565122, 1.1416352259264975,
      1.1680099461919677, 1.1940208000952002, 1.2196609965494025,
      1.2449238783032157, 1.269802923957873, 1.2942917499359086,
      1.3183841124003675, 1.3420739091258636, 1.3653551813183524,
      1.3882221153844978, 1.4106690446492454, 1.4326904510221645,
      1.4542809666112597, 1.4754353752828957, 1.496148614169067,
      1.5164157751202325, 1.5362321061042661, 1.5555930125497137,
      1.5744940586336966, 1.5929309685148281, 1.6108996275090508,
      1.6283960832097613, 1.6454165465498678, 1.6619573928075471,
      1.6780151625545581, 1.6935865625457789, 1.7086684665514693,
      1.7232579161297534, 1.7373521213429537, 1.7509484614127364,
      1.7640444853172326, 1.7766379123287093, 1.7887266324915128,
      1.8003087070420005, 1.8113823687671169, 1.8219460223035666,
      1.8319982443780609, 1.8415377839874616, 1.8505635625187633,
      1.8590746738085757, 1.8670703841443186, 1.8745501322048674,
      1.8815135289411626, 1.8879603573971795, 1.8938905724713977,
      1.8993043006198922, 1.9042018394984641, 1.9085836575460651,
      1.9124503935098074, 1.9158028559112821, 1.9186420224538441,
      1.9209690393710017, 1.9227852207178244, 1.9240920476048633,
      1.9248911673733631, 1.9251843927143339, 1.9249737007299326,
      1.9242612319395358, 1.9230492892291369, 1.9213403367453676,
      1.9191369987335365, 1.9164420583219632, 1.9132584562518438,
      1.9095892895526603, 1.9054378101646907, 1.9008074235082268,
      1.8957016870019008, 1.8901243085279178, 1.8840791448461096,
      1.8775701999583378, 1.8706016234226974, 1.8631777086182424,
      1.8553028909603524, 1.8469817460693114, 1.8382189878912538,
      1.8290194667719022, 1.8193881674847534, 1.8093302072132553,
      1.7988508334908249, 1.7879554220945397, 1.7766494748970858,
      1.7649386176765773, 1.7528285978844829, 1.7403252823742126,
      1.7274346550886932, 1.7141628147093306, 1.7005159722676828,
      1.6865004487196078, 1.6721226724831786, 1.6573891769405289,
      1.642306597906636, 1.6268816710637803, 1.6111212293635007,
      1.5950322003968238, 1.5786216037335881, 1.5618965482332965,
      1.5448642293257018, 1.52753192626408, 1.5099069993522274,
      1.4919968871453793, 1.4738091036263772, 1.4553512353576969,
      1.4366309386115912, 1.4176559364782539, 1.3984340159528108,
      1.3789730250040726, 1.3592808696226655, 1.3393655108540246,
      1.3192349618140338, 1.2988972846886193, 1.2783605877202504,
      1.2576330221810197, 1.2367227793335314, 1.2156380873808712,
      1.1943872084066809, 1.1729784353066737, 1.1514200887127801,
      1.1297205139100781, 1.1078880777484437, 1.0859311655507473,
      1.0638581780170051, 1.0416775281264261, 1.0193976380389098,
      0.99702693599661341, 0.97457385322677859, 0.95204682084673053,
      0.92945426677224252, 0.906804612631215, 0.88410627068240211,
      0.86136764074082006, 0.83859710711202973, 0.815803035534108,
      0.79299377013052919, 0.77017763037461773, 0.74736290806539041,
      0.72455786431693692, 0.70177072656280426, 0.67900968557555552,
      0.65628289250306426, 0.63359845592183794, 0.610964438909913,
      0.58838885613934111, 0.56587967098884273, 0.54344479267882706,
      0.52109207342927455, 0.49882930564136796, 0.47666421910390622,
      0.45460447822543854, 0.43265767929407761, 0.41083134776433045,
      0.3891329355724803, 0.36756981848299014, 0.34614929346458895,
      0.32487857609839327, 0.30376479801821754, 0.28281500438487772,
      0.26203615139493436, 0.24143510382388891, 0.22101863260682353,
      0.20079341245484253, 0.18076601951000745, 0.16094292903870222,
      0.14133051316505779, 0.12193503864425799, 0.1027626646764612,
      0.083819440763923239, 0.065111304609575982, 0.046644080059709027,
      0.028423475090556035, 0.010455079839377879, -0.007255635318092867,
      -0.024703321644491946, -0.041882753870937435, -0.058788831979418456,
      -0.07541658293640334, -0.091761162378854, -0.10781785625019422,
      -0.12358208238556753, -0.13904939204818179, -0.15421547141340675,
      -0.16907614300179313, -0.1836273670597727, -0.19786524288732266,
      -0.21178601011404075, -0.22538604992036781, -0.23866188620505444,
      -0.25161018669890828, -0.26422776402362241, -0.27651157669516568,
      -0.28845873007161954, -0.30006647724643204, -0.31133221988424831,
      -0.32225350900086513, -0.33282804568691304, -0.34305368177388229,
      -0.35292842044429484, -0.36245041678300777, -0.37161797827209564,
      -0.38042956522820953, -0.388883791181091, -0.39697942319534008,
      -0.40471538213306707, -0.41209074285945879, -0.4191047343896171,
      -0.42575673997718794, -0.43204629714492604, -0.43797309765694442,
      -0.44353698743313857, -0.44873796640438735, -0.45357618831133173,
      -0.45805196044367147, -0.46216574332223909, -0.4659181503238396,
      -0.46930994724683095, -0.47234205182110778, -0.47501553316009593,
      -0.47733161115546169, -0.47929165581507194, -0.48089718654502539,
      -0.48214987137500304, -0.48305152612733077, -0.48360411353105459,
      -0.483809742280062, -0.48367066603696229, -0.48318928238172332,
      -0.48236813170635578, -0.48120989605609982, -0.47971739791648949,
      -0.4778935989488633, -0.47574159867208493, -0.47326463309316125,
      -0.47046607328635903, -0.46734942392095036, -0.46391832173963021,
      -0.46017653398603292, -0.45612795678381252, -0.45177661346707937,
      -0.44712665286276, -0.44218234752565311, -0.43694809192650724,
      -0.43142840059518933, -0.42562790621732755, -0.41955135768685708,
      -0.41320361811524647, -0.406589662796478, -0.399714577130786,
      -0.39258355450612353, -0.38520189413891082, -0.37757499887505991,
      -0.36970837295155723, -0.36160761971973593, -0.35327843933074177,
      -0.34472662638516294, -0.33595806754594554, -0.32697873911690245,
      -0.317794704587094, -0.30841211214194392, -0.29883719214263776,
      -0.2890762545735121, -0.27913568646004178, -0.26902194925667605,
      -0.25874157620680011, -0.24830116967518553, -0.23770739845369546,
      -0.22696699504211182, -0.21608675290413976, -0.20507352370033197,
      -0.1939342144980413, -0.18267578496075465, -0.17130524451706519,
      -0.15982964950960529, -0.14825610032655795, -0.13659173851601392,
      -0.12484374388397047, -0.11301933157709906, -0.10112574915231647,
      -0.089170273633256372, -0.077160208554501439, -0.0651028809958723,
      -0.05300563860701326, -0.040875846623136827, -0.02872088487416519,
      -0.016548144786954565, -0.0043650263828188636, 0.00782106472889138,
      0.020002720360457343, 0.032172532756630921, 0.044323097606625395,
      0.056447017055328931, 0.06853690271305761, 0.080585378662390128,
      0.092585084461268313, 0.10452867814122692, 0.11640883919936366,
      0.12821827158324411, 0.13994970666720027, 0.15159590621965136,
      0.16314966535974648, 0.17460381550205503, 0.1859512272889314,
      0.19718481350884251, 0.20829753199987255, 0.21928238853717774,
      0.23013243970312838, 0.24084079574006559, 0.25140062338287439,
      0.26180514867145022, 0.27204765974285805, 0.28212150959950377,
      0.29202011885499712, 0.30173697845546443, 0.3112656523748214,
      0.32059978028386021, 0.32973308019201991, 0.33865935106063771,
      0.34737247538621385, 0.35586642175367206, 0.36413524735836811,
      0.37217310049517355, 0.37997422301474215, 0.38753295274532024,
      0.39484372587899341, 0.40190107932297, 0.408699653012712,
      0.41523419218779994, 0.42149954962913194, 0.427490687856378,
      0.43320268128520334, 0.43863071834298428, 0.44377010354258839,
      0.44861625951391504, 0.45316472899116494, 0.45741117675521115,
      0.46135139153238175, 0.46498128784646536, 0.46829690782379418,
      0.47129442295183904, 0.47397013578977976, 0.47632048162921009,
      0.47834203010757126, 0.48003148677108287, 0.48138569458495623,
      0.482401635395934, 0.48307643134149958, 0.48340734620593218,
      0.48339178672559469, 0.4830273038394553, 0.48231159388559897,
      0.48124249974554972, 0.47981801193184204, 0.47803626962006263,
      0.4758955616276585, 0.47339432733457432, 0.47053115754804758,
      0.46730479531148389, 0.46371413665544847, 0.45975823129067678,
      0.45543628324482416, 0.45074765144062906, 0.44569185021478946,
      0.44026854978032987, 0.434477576628121, 0.42831891387108212,
      0.42179270152932, 0.41489923675413459, 0.40763897399513382,
      0.40001252510588359, 0.39202065939166481, 0.38366430359667286,
      0.37494454183075421, 0.365862615438558, 0.35641992280671314,
      0.34661801911301965, 0.33645861601568855, 0.32594358128150286,
      0.31507493835681416, 0.30385486587731309, 0.29228569711927177,
      0.28036991939244849, 0.26811017337214377, 0.25550925237371397,
      0.24257010156927855, 0.22929581714477498, 0.21568964539909102,
      0.2017549817865992, 0.18749536990058502, 0.17291450040119263,
      0.15801620988558421, 0.14280447970137805, 0.12728343470524123,
      0.11145734196404214, 0.095330609402657168, 0.078907784396355388,
      0.062193552307744586, 0.045192734971178782, 0.027910289123434556,
      0.010351304781686331, -0.0074789964310312766, -0.025575263012254594,
      -0.043932015356741121, -0.062543647584946349, -0.0814044294203748,
      -0.10050850811633918, -0.11984991043185989, -0.13942254465555712,
      -0.15922020267575868, -0.17923656209776107, -0.19946518840777008,
      -0.21989953718022839, -0.24053295633131258, -0.26135868841420939,
      -0.28236987295750571, -0.30355954884700537, -0.32492065674724763,
      -0.346446041563041, -0.36812845494131619, -0.38996055781116146,
      -0.41193492296129663, -0.43404403765466654, -0.45628030627892086,
      -0.47863605303095547, -0.50110352463623675, -0.5236748931012094,
      -0.54634225849769713, -0.56909765177706284, -0.59193303761620064,
      -0.61484031729244415, -0.637811331584939, -0.66083786370500242,
      -0.68391164225097067, -0.70702434418853044, -0.730167597856008,
      -0.75333298599021215, -0.77651204877599567, -0.79969628691613548,
      -0.82287716471958849, -0.84604611320952672, -0.86919453324860363,
      -0.89231379868010785, -0.91539525948350275, -0.938430244946079,
      -0.96141006684533459, -0.98432602264406521, -1.0071693986965662,
      -1.029931473462786, -1.052603520732093, -1.0751768128538404,
      -1.0976426239734973, -1.1199922332741996, -1.1422169282208761,
      -1.1643080078081873, -1.1862567858093507, -1.2080545940241862,
      -1.2296927855273516, -1.2511627379134904, -1.2724558565390316,
      -1.293563577760694, -1.3144773721659455, -1.33518874779825,
      -1.3556892533746157, -1.3759704814917522, -1.3960240718234505,
      -1.415841714306423, -1.4354151523128496, -1.4547361858081604,
      -1.4737966744962754, -1.4925885409455537, -1.5111037736989452,
      -1.5293344303667959, -1.5472726406975332, -1.5649106096289223,
      -1.5822406203173771, -1.5992550371439349, -1.6159463086971491,
      -1.6323069707285436, -1.6483296490836647, -1.6640070626057568,
      -1.6793320260095193, -1.6942974527265759, -1.7088963577196612,
      -1.7231218602653451, -1.7369671867048513, -1.7504256731592074,
      -1.7634907682113607, -1.7761560355527719, -1.7884151565913269,
      -1.8002619330237108, -1.8116902893675759, -1.8226942754551168,
      -1.833268068884601, -1.8434059774328859, -1.8531024414227693,
      -1.862352036048174, -1.8711494736565897, -1.8794896059836486,
      -1.8873674263431575, -1.8947780717710681, -1.9017168251208743,
      -1.9081791171111184, -1.9141605283221221, -1.9196567911448297,
      -1.9246637916792286, -1.9291775715781385, -1.9331943298422996,
      -1.936710424560242, -1.9397223745952508, -1.9422268612198279,
      -1.94422072969119, -1.9457009907746263, -1.9466648222105447,
      -1.9471095701229373, -1.9470327503717437, -1.9464320498467163,
      -1.9453053277036918, -1.9436506165405785, -1.9414661235165354,
      -1.9387502314075624, -1.9355014996037558, -1.9317186650476654,
      -1.927400643106888, -1.9225465283888654, -1.9171555954930328,
      -1.9112272996987576, -1.9047612775930136, -1.8977573476331682,
      -1.8902155106480343, -1.8821359502754582, -1.8735190333345513,
      -1.8643653101352917, -1.854675514724117, -1.8444505650643488,
      -1.8336915631538675, -1.8223997950753661, -1.8105767309838758,
      -1.7982240250311194, -1.7853435152212651, -1.7719372232041164,
      -1.7580073540036809, -1.7435562956807631, -1.7285866189314769,
      -1.7131010766218322, -1.6971026032546661, -1.6805943143744975,
      -1.6635795059093261, -1.64606165344456, -1.6280444114339667,
      -1.6095316123487646, -1.5905272657599092, -1.5710355573599004,
      -1.5510608479189112, -1.5306076721786459, -1.5096807376856247,
      -1.4882849235582181, -1.4664252791950418, -1.444107022921268,
      -1.4213355405721091, -1.3981163840169453, -1.3744552696225614,
      -1.350358076657322, -1.325830845634957, -1.3008797765995783,
      -1.2755112273530427, -1.249731711623846, -1.2235478971792817,
      -1.1969666038801754, -1.1699948016806392, -1.1426396085706414,
      -1.1149082884660004, -1.0868082490433593, -1.0583470395206578,
      -1.0295323483862082, -1.0003720010746777, -0.97087395759369977,
      -0.94104631009848427, -0.91089728041556517, -0.88043521752036658,
      -0.849668594965343, -0.81860600826004293, -0.78725617220619115,
      -0.75562791818665709, -0.72373019140876238, -0.69157204810580186,
      -0.65916265269438135, -0.62651127488942082, -0.59362728677998677,
      -0.56052015986339887, -0.52719946204093937, -0.49367485457584237,
      -0.459956089013649, -0.42605300406741053, -0.39197552246687811,
      -0.35773364777441291, -0.32333746116848938, -0.2887971181945454,
      -0.25412284548524389, -0.21932493745145298, -0.18441375294533774,
      -0.14939971189484971, -0.11429329191262944, -0.0791050248800235,
      -0.04384549350664551, -0.0085253278675813827, 0.026844798081105421,
      0.06225417000744881, 0.097692036727949766, 0.13314761374966444,
      0.16861008682901274, 0.20406861554733027, 0.23951233689937745,
      0.27493036889595956, 0.31031181417858317, 0.34564576364389438,
      0.38092130007884839, 0.41612750180344793, 0.45125344632052372,
      0.48628821397160776, 0.52122089159681861, 0.5560405761985362,
      0.59073637860695, 0.62529742714591219, 0.65971287129885947,
      0.69397188537247223, 0.72806367215770351, 0.76197746658672039,
      0.79570253938285351, 0.82922820070542957, 0.86254380378610507,
      0.89563874855481362, 0.9285024852563859, 0.96112451805452193,
      0.99349440862299643, 1.0256017797228263, 1.0574363187624729,
      1.0889877813427329, 1.1202459947833772, 1.1512008616293115,
      1.1818423631371895, 1.2121605627400758, 1.2421456094891918,
      1.2717877414714114, 1.3010772892011191, 1.3300046789854254,
      1.3585604362627468, 1.3867351889115105, 1.4145196705283716,
      1.4419047236760991, 1.4688813030987826, 1.4954404789030251,
      1.5215734397058838, 1.5472714957447229, 1.572526081952075,
      1.5973287609928561, 1.6216712262601143, 1.6455453048333752,
      1.6689429603944395, 1.6918562961006158, 1.7142775574163114,
      1.7361991348982069, 1.7576135669368929, 1.7785135424523693,
      1.798891903540661, 1.8187416480735297, 1.8380559322491721,
      1.8568280730923172, 1.8750515509040344, 1.8927200116592229,
      1.9098272693501968, 1.9263673082801103, 1.9423342852995542,
      1.9577225319870413, 1.9725265567759169, 1.9867410470228977,
      2.000360871019589, 2.0133810799465883, 2.0257969097655328,
      2.0376037830547276, 2.048797310783717, 2.0593732940251375,
      2.0693277256064175, 2.0786567916982079, 2.0873568733398411,
      2.0954245479032934, 2.1028565904895689, 2.1096499752623821,
      2.1158018767183018, 2.1213096708872676, 2.1261709364701824,
      2.1303834559091803, 2.1339452163899462, 2.1368544107780996,
      2.1391094384851828, 2.1407089062696296, 2.1416516289683174,
      2.1419366301570664, 2.1415631427449995, 2.1405306094972056,
      2.1388386834895368, 2.1364872284923426, 2.1334763192853963,
      2.1298062419002322, 2.1254774937939156, 2.1204907839537803,
      2.114847032927881, 2.1085473727871373, 2.1015931470159348,
      2.0939859103324854, 2.0857274284392386, 2.07681967769891, 2.06726484474376,
      2.0570653260130238, 2.0462237272187704, 2.0347428627423825,
      2.0226257549593911, 2.009875633496125, 1.996495934415017,
      1.9824902993296623, 1.9678625744517761, 1.9526168095685164,
      1.9367572569500471, 1.9202883701884186, 1.9032148029688851,
      1.8855414077733736, 1.8672732345150393, 1.8484155291069866,
      1.8289737319622914, 1.8089534764303914, 1.7883605871658041,
      1.7672010784305459, 1.7454811523338094, 1.7232071970064133,
      1.7003857847108856, 1.6770236698895746, 1.6531277871477588,
      1.6287052491771272, 1.6037633446188035, 1.5783095358617942,
      1.5523514567843564, 1.525896910435969, 1.4989538666593736,
      1.4715304596569729, 1.4436349854975359, 1.4152758995682326,
      1.3864618139719527, 1.3572014948681332, 1.3275038597614701,
      1.2973779747363967, 1.2668330516412356, 1.2358784452190683,
      1.2045236501906995, 1.1727782982868613, 1.14065215523236,
      1.1081551176842632, 1.0752972101212961, 1.0420885816902814,
      1.0085395030077209, 0.97466036291660252, 0.94046166520313257,
      0.90595402527116886, 0.87114816677702123, 0.836054918225544,
      0.8006852095273691, 0.765050068520717, 0.72916061745707417,
      0.69302806945228157, 0.6566637249051267, 0.62007896788296646,
      0.58328526247675283, 0.54629414912732488, 0.50911724092186339,
      0.47176621986399941, 0.43425283311751922, 0.39658888922519964,
      0.35878625430490829, 0.32085684822276195, 0.28281264074533957,
      0.24466564767210952, 0.206427926950119, 0.1681115747706721,
      0.12972872165048221, 0.091291528498762264, 0.0528121826702108,
      0.014302894006589384, -0.024224109131954458, -0.062756583845603675,
      -0.10128227668124928, -0.13978892762534242, -0.17826427410209503,
      -0.21669605497554495, -0.25507201455456319, -0.29337990659894747,
      -0.33160749832534403, -0.36974257441143255, -0.40777294099864952,
      -0.4456864296896163, -0.48347090154018313, -0.521114251045196,
      -0.55860441011597117, -0.59592935204817876, -0.63307709547958557,
      -0.67003570833459636, -0.70679331175585292, -0.74333808402197643,
      -0.77965826444753028, -0.8157421572668585, -0.85157813549881656,
      -0.88715464479110617, -0.92246020724449529, -0.95748342521274443,
      -0.9922129850795981, -1.0266376610112979, -1.0607463186810278,
      -1.0945279189668489, -1.1279715216201653, -1.1610662889042438,
      -1.1938014892016373, -1.2261665005874485, -1.2581508143706224,
      -1.2897440385996104, -1.3209359015305404, -1.351716255059261,
      -1.3820750781144215, -1.4120024800110456, -1.4414887037624418,
      -1.4705241293507261, -1.4990992769531628, -1.5272048101258477,
      -1.55483153894157, -1.5819704230795322, -1.6086125748695621,
      -1.6347492622874564, -1.660371911899704, -1.6854721117592149,
      -1.7100416142474737, -1.7340723388654535, -1.7575563749723953,
      -1.7804859844666112, -1.8028536044135064, -1.824651849616854,
      -1.8458735151324988, -1.8665115787250404, -1.8865592032628011,
      -1.9060097390565929, -1.9248567261363114, -1.9430938964656002,
      -1.9607151760960368, -1.9777146872562468, -1.9940867503796291,
      -2.0098258860661331, -2.0249268169806287, -2.0393844696838155,
      -2.0531939763979707, -2.0663506767064961, -2.0788501191834063,
      -2.0906880629574909, -2.1018604792062692, -2.1123635525809803,
      -2.1221936825627186, -2.1313474847461777, -2.1398217920556988,
      -2.1476136558889456, -2.1547203471874488, -2.1611393574375528,
      -2.1668683995988012, -2.1719054089583567, -2.1762485439141863,
      -2.1798961866829636, -2.1828469439357145, -2.185099647361779,
      -2.1866533541547377, -2.1875073474263176, -2.1876611365466228,
      -2.1871144574079455, -2.1858672726160346, -2.1839197716067567,
      -2.1812723706841139, -2.1779257129882539, -2.1738806683871394,
      -2.1691383332913752, -2.16370003039723, -2.1575673083528577,
      -2.1507419413497812, -2.1432259286422948, -2.1350214939889183,
      -2.1261310850213055, -2.1165573725409068, -2.1063032497376208,
      -2.0953718313381113, -2.0837664526796558, -2.0714906687096848,
      -2.0585482529155152, -2.0449431961772864, -2.0306797055522008,
      -2.0157622029871023, -2.0001953239561092, -1.9839839160307744,
      -1.96713303737823, -1.9496479551901285, -1.931534144040939,
      -1.9127972841783956, -1.8934432597438171, -1.8734781569255743,
      -1.8529082620471988, -1.8317400595849023, -1.8099802301208887,
      -1.7876356482318272, -1.7647133803115809, -1.741220682331456,
      -1.7171649975340741, -1.6925539540674799, -1.667395362557158,
      -1.6416972136152026, -1.615467675290978, -1.5887150904616294,
      -1.5614479741645593, -1.5336750108717176, -1.5054050517065753,
      -1.4766471116070305, -1.4474103664317148, -1.4177041500123746,
      -1.3875379511541515, -1.3569214105828686, -1.3258643178419076,
      -1.2943766081383605, -1.2624683591405763, -1.2301497877273511,
      -1.197431246691042, -1.164323221393984, -1.1308363263802488,
      -1.0969813019439456, -1.0627690106550629, -1.0282104338443758,
      -0.99331666804735, -0.95809892140871034, -0.92256851005050067,
      -0.88673685440294414, -0.85061547549894623, -0.81421599123550692,
      -0.77755011260203777, -0.740629639875684, -0.70346645878785719,
      -0.66607253666051447, -0.62845991851434813, -0.59064072315133809,
      -0.55262713921078244, -0.51443142120166641, -0.47606588551273216,
      -0.43754290640013838, -0.39887491195567754, -0.36007438005655967,
      -0.32115383429662375, -0.28212583990244222, -0.2430029996342172,
      -0.2037979496734609, -0.16452335549852831, -0.12519190774939171,
      -0.085816318083703255, -0.046409315024050969, -0.0069836397994184445,
      0.032447957818882572, 0.071872723685130618, 0.11127790344877224,
      0.15065074672630285, 0.189978511271864, 0.2292484671460327,
      0.26844790088198922, 0.3075641196466038, 0.34658445539624455,
      0.38549626902465151, 0.4242869545027485, 0.4629439430082859,
      0.5014547070432247, 0.53980676453938248, 0.57798768295012615,
      0.61598508332503443, 0.65378664436925038, 0.6913801064841999,
      0.72875327578802329, 0.7658940281163481, 0.80279031299965209,
      0.83943015761787765, 0.87580167072987747, 0.91189304657674453,
      0.9476925687573392, 0.9831886140757905, 1.0183696563587636,
      1.0532242702401942, 1.0877411349150921, 1.1219090378594605,
      1.1557168785130603, 1.1891536719286586, 1.222208552381802,
      1.2548707769430223, 1.2871297290092008, 1.3189749217946514,
      1.3503960017802807, 1.3813827521165629, 1.4119250959872012,
      1.4420130999216325, 1.471636977064398, 1.5007870903952933, 1.5294539559004,
      1.5576282456946311, 1.5853007910910175, 1.6124625856206509,
      1.6391047879956226, 1.6652187250229178, 1.6907958944595596,
      1.7158279678131361, 1.740306793085387, 1.7642243974569278,
      1.7875729899172126, 1.8103449638281919, 1.83253289943367,
      1.8541295663041197, 1.8751279257206055, 1.8955211329953774,
      1.9153025397291432, 1.9344656960032538, 1.9530043525069596,
      1.9709124626015793, 1.9881841843110961, 2.0048138822538681,
      2.0207961295012273, 2.0361257093686014, 2.0507976171390183,
      2.0648070617149763, 2.0781494672013818, 2.0908204744181544,
      2.1028159423406358, 2.1141319494661284, 2.1247647951144817,
      2.1347110006497538, 2.1439673106319512, 2.152530693895101,
      2.1603983445500554, 2.1675676829168284, 2.1740363563768037,
      2.1798022401555714, 2.1848634380280392, 2.189218282949946,
      2.1928653376118779, 2.1958033949195084, 2.198031478396274,
      2.1995488425129373, 2.2003549729410263, 2.2004495867229408,
      2.199832632377936, 2.1985042899222522, 2.1964649708175283,
      2.1937153178422872, 2.1902562048857592, 2.1860887366685393,
      2.1812142483844474, 2.1756343052692895, 2.1693507020895293,
      2.1623654625614543, 2.1546808386896932, 2.1462993100336574,
      2.1372235828985104, 2.1274565894495923, 2.1170014867571258,
      2.1058616557598726, 2.0940407001629637, 2.08154244525717,
      2.0683709366664331, 2.054530439024171, 2.0400254345758224,
      2.0248606217111931, 2.00904091342558, 1.9925714357106641,
      1.9754575258715079, 1.9577047307809599, 1.939318805059417,
      1.9203057091892537, 1.9006716075606127, 1.8804228664492064,
      1.8595660519304789, 1.8381079277260861, 1.8160554529860482,
      1.7934157800047139, 1.7701962518779635, 1.7464044000934582,
      1.7220479420611812, 1.697134778581902, 1.6716729912555734,
      1.6456708398328486, 1.6191367595032213, 1.5920793581308497,
      1.5645074134303383, 1.5364298700884342, 1.5078558368301898,
      1.478794583431579, 1.4492555376813852, 1.4192482822872834,
      1.3887825517343206, 1.35786822909293, 1.3265153427796943,
      1.2947340632667723, 1.26253469974859, 1.2299276967632262,
      1.1969236307664903, 1.1635332066663588, 1.1297672543126098,
      1.0956367249492127, 1.0611526876230464, 1.0263263255566921,
      0.99116893248589633, 0.95569190895679978, 0.91990675859035831,
      0.88382508431486606, 0.84745858456549283, 0.81081904945003513,
      0.77391835688896393, 0.73676846872551727, 0.69938142680834692,
      0.66176934904811657, 0.62394442545036455, 0.58591891412588382,
      0.54770513727708015, 0.50931547716552816, 0.47076237206019506,
      0.4320583121675251, 0.39321583554431111, 0.35424752399661674,
      0.31516599896494585, 0.27598391739601785, 0.23671396760380164,
      0.19736886512183172, 0.1579613485460907, 0.11850417537089517,
      0.07901011782094515, 0.039491958676874668, -3.7512900097348112E-5,
      -0.039565505545692006, -0.079079229870747517, -0.11856590263652741,
      -0.15801275092816372, -0.19740701632425117, -0.23673595906041295,
      -0.27598686218582336, -0.31514703571190023, -0.35420382075151613,
      -0.39314459364653004, -0.43195677008324074, -0.47062780919474473,
      -0.50914521764702214, -0.54749655370988137, -0.58566943130876759,
      -0.62365152405866819, -0.66143056927730226, -0.69899437197587133,
      -0.73633080882737245, -0.77342783211042354, -0.81027347362779345,
      -0.84685584859649088, -0.88316315951159852, -0.91918369997895111,
      -0.954905858518749, -0.99031812233508654, -1.0254090810523704,
      -1.0601674304216107, -1.094581975983312, -1.1286416366991254,
      -1.1623354485454955, -1.1956525680651564, -1.2285822758781357,
      -1.2611139801533879, -1.2932372200388063, -1.324941669042216,
      -1.3562171383717914, -1.3870535802292323, -1.4174410910561455,
      -1.4473699147301153, -1.4768304457142816, -1.5058132321567874,
      -1.5343089789350328, -1.5623085506522527, -1.58980297457837,
      -1.6167834435380124, -1.6432413187408308, -1.6691681325578933,
      -1.6945555912431938, -1.7193955775930059, -1.7436801535470097,
      -1.7674015627328468, -1.7905522329507533, -1.81312477859048,
      -1.835112002993661, -1.8565069007506214, -1.8773026599336617,
      -1.8974926642646732, -1.9170704952199045, -1.9360299340710287,
      -1.9543649638546432, -1.9720697712798083, -1.989138748565509,
      -2.00556649521232, -2.021347819701512, -2.0364777411297514,
      -2.0509514907729169, -2.0647645135762689, -2.0779124695788047,
      -2.0903912352631422, -2.1021969048376223, -2.1133257914408183,
      -2.1237744282792552, -2.133539569690841, -2.1426181921356076,
      -2.1510074951108029, -2.1587049019935742, -2.1657080608170416,
      -2.1720148449582175, -2.1776233537634795, -2.1825319130976859,
      -2.1867390758151344, -2.1902436221565091, -2.1930445600733672,
      -2.1951411254801969, -2.1965327824243159, -2.1972192231859835,
      -2.1972003683034877, -2.1964763665229157, -2.19504759467,
      -2.1929146574522784, -2.1900783871856881, -2.1865398434411953,
      -2.1823003126241156, -2.1773613074757967, -2.1717245665019775,
      -2.1653920533249509, -2.1583659559661146, -2.1506486860550664,
      -2.1422428779626563, -2.1331513878607722, -2.1233772927142747,
      -2.1129238892012103, -2.1017946925530167, -2.0899934353337981,
      -2.0775240661440484, -2.0643907482542576, -2.0505978581676652,
      -2.0361499841166744, -2.0210519244908673, -2.0053086861920564,
      -1.9889254829266991, -1.9719077334273669, -1.9542610596137628,
      -1.9359912846802632, -1.9171044311224925, -1.8976067187029504,
      -1.8775045623450566, -1.8568045699699671, -1.8355135402693792,
      -1.813638460419009, -1.7911865037255164, -1.768165027219869,
      -1.7445815691910376, -1.7204438466571192, -1.6957597527816255,
      -1.6705373542341637, -1.6447848884979039, -1.6185107611138849,
      -1.5917235428800864, -1.5644319669957163, -1.5366449261517474,
      -1.5083714695708339, -1.4796207999989912, -1.4504022706495843,
      -1.4207253820953836, -1.3905997791177367, -1.3600352475084745,
      -1.3290417108290271, -1.2976292271223322, -1.2658079855862419,
      -1.2335883032053281, -1.2009806213399321, -1.1679955022790871,
      -1.1346436257538637, -1.1009357854161919, -1.0668828852792416,
      -1.0324959361261874, -0.9977860518858841, -0.96276444597547084,
      -0.92744242761221041, -0.89183139809738066, -0.8559428470726842,
      -0.8197883487462706, -0.78337955809712478, -0.74672820705358667,
      -0.70984610064887388, -0.67274511315383079, -0.63543718419109241,
      -0.59793431483006365, -0.56024856366172615, -0.52239204285948748,
      -0.48437691422361573, -0.44621538521175513, -0.40791970495691371,
      -0.3695021602745453, -0.33097507165959644, -0.29235078927445241,
      -0.253641688929712, -0.21486016805989841, -0.17601864169345768,
      -0.13712953841949219, -0.098205296353628277, -0.059258359102255673,
      -0.020301171727799428, 0.018653823284043147, 0.057594190053813381,
      0.0965075033325789, 0.13538135252020589, 0.1742033456776852,
      0.21296111352889124, 0.25164231345348714, 0.29023463346805117,
      0.32872579619440268, 0.36710356281567053, 0.4053557370145488,
      0.44347016889681845, 0.4814347588971804, 0.51923746166488982,
      0.55686628992967024, 0.59430931834665457, 0.63155468731745057,
      0.66859060678780657, 0.70540536001974352, 0.74198730733646046,
      0.77832488984170267, 0.81440663310696282, 0.8502211508300509,
      0.88575714846432452, 0.92100342681259184, 0.95594888558629787,
      0.9905825269339591, 1.0248934589323295, 1.0588708990357358,
      1.0925041774938371, 1.1257827407278893, 1.1586961546637655,
      1.1912341080260322, 1.2233864155906697, 1.2551430213917958,
      1.2864940018838631, 1.3174295690604134, 1.3479400735237188,
      1.3780160075097152, 1.4076480078601816, 1.4368268589492612,
      1.4655434955595439, 1.4937890057032162, 1.5215546333945442,
      1.548831781367743, 1.5756120137420895, 1.6018870586290488,
      1.6276488106879163, 1.6528893336234771, 1.6776008626267627,
      1.7017758067535722, 1.7254067512514037, 1.7484864598268297,
      1.7710078768417281, 1.7929641294622205, 1.8143485297403892,
      1.8351545766334523, 1.855375957959466, 1.8750065522924309,
      1.8940404307949481, 1.9124718589794374, 1.9302952984119293,
      1.9475054083472136, 1.9640970472983219, 1.9800652745375631,
      1.995405351534941, 2.0101127433282833, 2.0241831198218705,
      2.037612357021811, 2.0503965382000824, 2.0625319549929988,
      2.0740151084260248, 2.0848427098730751, 2.0950116819474816,
      2.1045191593194379, 2.1133624894617791, 2.1215392333341634,
      2.1290471659929087, 2.135884277121741, 2.1420487715050074,
      2.1475390694260743, 2.1523538069920938, 2.1564918363872687,
      2.1599522260611406, 2.1627342608435751, 2.1648374419852909,
      2.1662614871331596, 2.1670063302316707, 2.1670721213558819,
      2.1664592264708076, 2.16516822712481, 2.1631999200715257,
      2.1605553168190927, 2.1572356431128163, 2.1532423383485266,
      2.148577054916498, 2.1432416574721889, 2.1372382221466242,
      2.1305690356817086, 2.1232365945027567, 2.1152436037160069,
      2.10659297604744, 2.0972878307160188, 2.0873314922246227,
      2.0767274891060863, 2.0654795525928327, 2.0535916152232319,
      2.0410678093822541, 2.0279124657802368, 2.0141301118739725,
      1.9997254702136074, 1.9847034567360791, 1.969069178995789,
      1.9528279343337589, 1.9359852079856767, 1.9185466711325003,
      1.9005181788942687, 1.8819057682598672, 1.8627156559664746,
      1.8429542363184896, 1.8226280789532479, 1.8017439265498976,
      1.7803086924840719, 1.7583294584350693, 1.7358134719336709,
      1.7127681438584927, 1.6892010458905506, 1.6651199079104306,
      1.64053261534501, 1.6154472064746139, 1.5898718696880871,
      1.5638149406922264, 1.5372848996752393, 1.5102903684311209,
      1.4828401074368485, 1.4549430128883658, 1.4266081136973834,
      1.3978445684453131, 1.3686616623044892, 1.3390688039129748,
      1.3090755222195996, 1.2786914632932185, 1.2479263870928172,
      1.2167901642084404, 1.1852927725684057, 1.1534442941179803,
      1.1212549114617016, 1.0887349044844907, 1.0558946469414134,
      1.0227446030207861, 0.98929532388257635, 0.95555744417213428,
      0.92154167851523383, 0.88725881798253581, 0.8527197265413804,
      0.81793533748695879, 0.78291664985214449, 0.74767472480249886,
      0.71222068201546718, 0.67656569604598649, 0.640720992676935,
      0.60469784525821924, 0.56850757103653715, 0.53216152747341838,
      0.49567110855558372, 0.45904774109977042, 0.42230288104909486,
      0.3854480097672594, 0.3484946303273081, 0.3114542637994111,
      0.27433844553788639, 0.23715872146691747, 0.19992664437030055,
      0.162653770181901, 0.12535165428144968, 0.088031847793336934,
      0.050705893895278534, 0.013385324132264849, -0.023918345261520434,
      -0.061193617026390673, -0.0984290165351419, -0.1356130954348862,
      -0.17273443527577129, -0.20978165112635508, -0.24674339517021773,
      -0.28360836028866748, -0.32036528362264355, -0.3570029501157222,
      -0.39351019603754706, -0.42987591248254492, -0.466089048849515,
      -0.50213861629437817, -0.5380136911584501, -0.57370341837130856,
      -0.60919701482397193, -0.64448377271732182, -0.6795530628768065,
      -0.714394338039119, -0.74899713610744811, -0.783351083372591,
      -0.81744589769985965, -0.85127139168399435, -0.88481747576788172,
      -0.91807416131832476, -0.95103156367426311, -0.9836799051502908,
      -1.016009517999938, -1.0480108473411522, -1.0796744540384493,
      -1.1109910175451503, -1.1419513386995641, -1.1725463424787115,
      -1.2027670807067825, -1.2326047347178055, -1.2620506179714432,
      -1.2910961786221029, -1.3197330020402025, -1.347952813282244,
      -1.3757474795134521, -1.4031090123799017, -1.4300295703287196,
      -1.4565014608755733, -1.4825171428212918, -1.5080692284161024,
      -1.5331504854690863, -1.5577538393985013, -1.5818723752359456,
      -1.6054993395721038, -1.6286281424378837, -1.6512523591409942,
      -1.67336573203988, -1.6949621722586379, -1.7160357613445842,
      -1.7365807528690695, -1.7565915739688396, -1.7760628268243484,
      -1.7949892900822766, -1.8133659202160644, -1.8311878528269934,
      -1.8484504038805587, -1.8651490708861249, -1.8812795340137203,
      -1.8968376571464862, -1.91181948887476, -1.9262212634236686,
      -1.9400394015235687, -1.9532705112110222, -1.9659113885716981,
      -1.9779590184214106, -1.9894105749196458, -2.0002634221188376,
      -2.0105151144573279, -2.0201633971866877, -2.0292062067259575,
      -2.03764167096613, -2.0454681095049296, -2.0526840338174708,
      -2.0592881473632634, -2.0652793456324479, -2.0706567161296539,
      -2.0754195382889158, -2.0795672833324064, -2.0830996140626072,
      -2.0860163845932966, -2.0883176400158954, -2.09000361600631,
      -2.0910747383708319, -2.0915316225254146, -2.0913750729179585,
      -2.0906060823881312, -2.0892258314669441, -2.0872356876130831,
      -2.0846372043935788, -2.0814321206029476, -2.0776223593227177,
      -2.0732100269185909, -2.0681974119867537, -2.0625869842410323,
      -2.0563813933310757, -2.0495834676188673, -2.0421962128918731,
      -2.0342228110200704, -2.0256666185564587, -2.0165311652857438,
      -2.0068201527199441, -1.9965374525349453, -1.9856871049587479,
      -1.9742733171056215, -1.9623004612607104, -1.9497730731084377,
      -1.93669584991675, -1.9230736486700173, -1.9089114841492629,
      -1.8942145269692916, -1.8789881015655663, -1.8632376841373042,
      -1.8469689005391758, -1.8301875241340084, -1.8128994736000046,
      -1.7951108106923457, -1.7768277379608446, -1.7580565964323085,
      -1.7388038632499252, -1.719076149263552, -1.6988801965951013,
      -1.6782228761580611, -1.6571111851402829, -1.6355522444500852,
      -1.6135532961286236, -1.5911217007293594, -1.5682649346594848,
      -1.5449905874922893, -1.5213063592467704, -1.4972200576380921,
      -1.4727395952955338, -1.4478729869547766, -1.4226283466223204,
      -1.397013884712293, -1.3710379051576975, -1.3447088024974028,
      -1.3180350589423966, -1.2910252414137122, -1.2636879985649654,
      -1.2360320577827364, -1.2080662221661134, -1.1797993674880021,
      -1.1512404391429509, -1.1223984490777568, -1.0932824727007862,
      -1.0639016457870913, -1.0342651613661766, -1.0043822665968585,
      -0.974262259632462, -0.94391448647862319, -0.91334833784095515,
      -0.88257324596386433, -0.85159868146653261, -0.82043415017110743,
      -0.78908918992829946, -0.75757336743848491, -0.725896275072495,
      -0.69406752769238056, -0.66209675946890734, -0.62999362070366394,
      -0.59776777465340325, -0.56542889435593591, -0.53298665946307522,
      -0.50045075307766318, -0.46783085859721685, -0.43513665656757888,
      -0.40237782154219665, -0.369564018954136, -0.3367049019982154,
      -0.30381010852398954, -0.270889257943391, -0.23795194815197604,
      -0.20500775246552908, -0.17206621657071353, -0.13913685549653851,
      -0.10622915060194642, -0.073352546581350792, -0.040516448492345675,
      -0.0077302188039475844, 0.024996825533508106, 0.057655415995617861,
      0.090236335365813922, 0.12273042059476587, 0.1551285656319325,
      0.18742172423058934, 0.21960091272664098, 0.25165721278734271,
      0.28358177413086488, 0.31536581721669071, 0.34700063590464475,
      0.378477600079771, 0.40978815824683529, 0.4409238400914427,
      0.47187625900518732, 0.50263711457504379, 0.53319819503921972,
      0.5635513797048195, 0.59368864132788457, 0.62360204845545386,
      0.65328376772874341, 0.68272606614654741, 0.7119213132886657,
      0.74086198349825794, 0.76954065802188865, 0.79795002710815777,
      0.82608289206211427, 0.85393216725816057, 0.881490882107424,
      0.90875218298023475, 0.93570933508457577, 0.96235572429662464,
      0.98868485894871738, 1.0146903715660398, 1.0403660205582144,
      1.065705691865138, 1.0907034005497318, 1.1153532923465619,
      1.1396496451587796, 1.1635868705074797, 1.1871595149278633,
      1.2103622613189349, 1.2331899302428047, 1.2556374811680917,
      1.2777000136672152, 1.2993727685603751, 1.3206511290076888,
      1.3415306215494651, 1.3620069170944895, 1.3820758318551081,
      1.4017333282310718, 1.4209755156387085, 1.4397986512883516,
      1.4581991409099637, 1.4761735394215738, 1.49371855154886,
      1.5108310323875374, 1.5275079879156321, 1.5437465754503661,
      1.5595441040500813, 1.5748980348676114, 1.5898059814445926,
      1.6042657099550726, 1.6182751393952834, 1.6318323417214413,
      1.6449355419304552, 1.6575831180909737, 1.6697736013225184,
      1.6815056757168847, 1.6927781782099056, 1.7035900984019168,
      1.7139405783238864, 1.7238289121511066, 1.7332545458664508,
      1.7422170768712868, 1.7507162535472145, 1.7587519747609957,
      1.7663242893252373, 1.7734333954064641, 1.7800796398807044,
      1.7862635176449058, 1.7919856708701047, 1.7972468882164438,
      1.8020481039921372, 1.8063903972653057, 1.8102749909334661,
      1.8137032507375679, 1.8166766842366981, 1.819196939731667,
      1.8212658051471986, 1.8228852068636849, 1.8240572085085616,
      1.8247840097041863, 1.8250679447664897, 1.8249114813680745,
      1.824317219153246, 1.8232878883141375, 1.8218263481255863,
      1.8199355854382371, 1.8176187131333814, 1.8148789685387465,
      1.8117197118026032, 1.8081444242336484, 1.8041567066045312,
      1.7997602774146793, 1.7949589711216096, 1.789756736333594,
      1.7841576339724461, 1.778165835399719, 1.7717856205103997,
      1.765021375797525, 1.7578775923820635, 1.7503588640142647,
      1.7424698850456177, 1.7342154483737293, 1.7256004433533902,
      1.7166298536878655, 1.7073087552915565, 1.6976423141241288,
      1.6876357840039795, 1.6772945043962333, 1.6666238981803938,
      1.6556294693903453, 1.6443168009402171, 1.6326915523275602,
      1.6207594573144259, 1.6085263215933907, 1.5959980204355024,
      1.5831804963218403, 1.5700797565568403, 1.5567018708726785,
      1.5430529690116874, 1.5291392383030005, 1.5149669212252459,
      1.5005423129539384, 1.4858717589069133, 1.470961652272166,
      1.4558184315315836, 1.4404485779787004, 1.4248586132271228,
      1.4090550967130377, 1.3930446231956237, 1.3768338202539048,
      1.3604293457775987, 1.3438378854587827, 1.3270661502831274,
      1.3101208740192218, 1.2930088107087843, 1.2757367321608086,
      1.2583114254474883, 1.2407396904046728, 1.223028337132535,
      1.2051841835074109, 1.187214052698957, 1.1691247706910661,
      1.1509231638146455, 1.1326160562858087, 1.1142102677606751,
      1.0957126108926196, 1.0771298889059318, 1.0584688931834845,
      1.0397364008621679, 1.0209391724491308, 1.0020839494473066,
      0.98317745200213069, 0.96422637655961652, 0.94523739354539849,
      0.9262171450639376, 0.90717224261041829, 0.88810926481002983,
      0.86903475517220174, 0.84995521986967615, 0.8308771255384495,
      0.81180689710023746, 0.79275091561275568, 0.77371551613785716,
      0.75470698563814775, 0.73573156090193559, 0.716795426491361,
      0.69790471271901267, 0.6790654936524454, 0.66028378514662334,
      0.64156554290726564, 0.62291666058356343, 0.60434296788935038,
      0.58585022875759085, 0.567444139527885, 0.54913032716280619,
      0.53091434749885114, 0.51280168353199351, 0.49479774373455354,
      0.47690786040935812, 0.45913728807825827, 0.44149120190414115,
      0.42397469615081745, 0.4065927826802071, 0.38935038948487433,
      0.37225235925742689, 0.35530344800061764, 0.33850832367316619,
      0.32187156487373936, 0.30539765956684822, 0.28909100384622638,
      0.27295590073746517, 0.25699655904094931, 0.24121709221714374,
      0.22562151731019756, 0.21021375391289568, 0.19499762317490149,
      0.1799768468491097, 0.16515504638289566, 0.150535742049399,
      0.13612235212173987, 0.1219181920897459, 0.10792647391733254,
      0.094150305346176535, 0.080592689238835946, 0.067256522966631413,
      0.054144597839512795, 0.041259598579391536, 0.0286041028377659,
      0.016180580755043372, 0.003991394563851532, -0.007961201765260998,
      -0.019675062832580779, -0.031148152076310828, -0.04237854199725756,
      -0.053364414337765426, -0.064104060219984077, -0.07459588023916941,
      -0.0848383845144314, -0.094830192698460519, -0.10457003394117816,
      -0.11405674681328713, -0.12328927918654738, -0.13226668807126146,
      -0.1409881394129705, -0.14945290784562956, -0.15766037640414265,
      -0.16561003619582146, -0.17330148602844689, -0.180734432000455,
      -0.18790868704930253, -0.19482417045731254, -0.20148090732089882,
      -0.20787902797826466, -0.2140187673972328, -0.21990046452583981,
      -0.22552456160274606, -0.23089160342999951, -0.23600223660781797,
      -0.24085720873164254, -0.24545736755331973, -0.24980366010438049,
      -0.25389713178295886, -0.25773892540680848, -0.26133028022944926,
      -0.26467253092241083, -0.26776710652329244, -0.27061552934860034,
      -0.27321941387661891, -0.27558046559522131, -0.27770047981693952,
      -0.27958134046505229, -0.28122501882707529, -0.28263357227795211,
      -0.28380914297417342, -0.28475395651789742, -0.2854703205935788,
      -0.28596062357512719, -0.28622733310733584, -0.28627299466061407,
      -0.28610023005734619, -0.28571173597624122, -0.28511028243027364,
      -0.2842987112199829, -0.28327993436514981, -0.28205693251268138,
      -0.280632753322813, -0.27901050983437725, -0.27719337880959849,
      -0.27518459905830384, -0.27298746974420723, -0.27060534867233166,
      -0.26804165055832069, -0.26529984528253514, -0.26238345612610853,
      -0.259296057992614, -0.25604127561580808, -0.25262278175220404,
      -0.24904429536150549, -0.24530957977429402, -0.24142244084899803,
      -0.23738672511699982, -0.23320631791822696, -0.228885141528776,
      -0.22442715327775564, -0.21983634365852403, -0.21511673443254567,
      -0.21027237672643254, -0.20530734912543197, -0.20022575576059004,
      -0.19503172439346156, -0.18972940449743364, -0.18432296533709597,
      -0.17881659404696373, -0.17321449370762224, -0.16752088142525737,
      -0.16173998640940723, -0.1558760480535859, -0.14993331401979323,
      -0.14391603832363573, -0.13782847942670778, -0.13167489833157014,
      -0.12545955668334097, -0.11918671487776399, -0.11286063017645027,
      -0.10648555483024019, -0.10006573421077683, -0.093605404952381344,
      -0.087108793102639012, -0.080580112286645134, -0.074023561879734051,
      -0.067443325194506465, -0.060843567681335885, -0.054228435141136004,
      -0.047602051954121941, -0.040968519322316141, -0.034331913529429166,
      -0.027696284217455625, -0.021065652678476269, -0.014444010166670159,
      -0.0078353162276891264, -0.0012434970477537542, 0.0053275561773703543,
      0.011873988853106341, 0.018391984575294843, 0.024877766699039048,
      0.031327599882197785, 0.037737791609272181, 0.044104693690139966,
      0.0504247037337879, 0.056694266599622942, 0.0629098758217941,
      0.06906807500895043, 0.0751654592156308, 0.081198676290352226,
      0.087164428194254823, 0.093059472288916409, 0.098880622603383261,
      0.10462475106649773, 0.110288788710058, 0.11586972684669819,
      0.12136461821341796, 0.12677057808602415, 0.13208478536375359,
      0.13730448362157269, 0.14242698213094176, 0.14744965684737912,
      0.1523699513685727, 0.15718537785720857, 0.16189351793125872,
      0.1664920235230718, 0.17097861770066328, 0.17535109545774683,
      0.17960732447106881, 0.18374524582092491, 0.18776287467586039,
      0.19165830094582245, 0.1954296898986449, 0.1990752827395936,
      0.20259339715859459, 0.20598242783915083, 0.20924084693318304,
      0.21236720449812516, 0.21536012889983761, 0.2182183271793583,
      0.22094058538007416, 0.22352576884338482, 0.22597282246447989,
      0.22828077091281915, 0.23044871881720488, 0.23247585091170028,
      0.23436143214688399, 0.236104807765552, 0.23770540334020993,
      0.23916272477370559, 0.24047635826556737, 0.24164597024075138,
      0.24267130724283065, 0.24355219578931461, 0.24428854219334351,
      0.24488033234941164, 0.24532763148126768, 0.24563058385566575,
      0.24578941246097874, 0.24580441865065775, 0.24567598175073116,
      0.24540455863358257, 0.24499068325659035, 0.24443496616727811,
      0.24373809397323884, 0.24290082877912975, 0.2419240075908709,
      0.24080854168481836, 0.2395554159461073, 0.23816568817343572,
      0.23664048835133017, 0.2349810178911832, 0.23318854884150583,
      0.23126442306602929, 0.22921005139129802, 0.22702691272398695,
      0.22471655313917965, 0.22228058493905442, 0.21972068568055139,
      0.21703859717741489, 0.21423612447257115, 0.21131513478294567,
      0.20827755641841694, 0.205125377671357, 0.20186064568318715,
      0.19848546528474098, 0.19500199780893429, 0.19141245988208286,
      0.18771912219031472, 0.18392430822128772, 0.18003039298472406,
      0.17603980170964137, 0.1719550085206365, 0.16777853509204824,
      0.16351294928254395, 0.15916086375018851, 0.15472493454607214,
      0.15020785969210068, 0.14561237773918245, 0.14094126630785098,
      0.13619734061252345, 0.13138345197073631, 0.1265024862951796,
      0.12155736257181397, 0.11655103132451021, 0.11148647306486141,
      0.10636669673099956, 0.10119473811257766, 0.095973658265831582,
      0.090706541917331115, 0.085396495857827534, 0.080046647326849671,
      0.0746601423897058, 0.069240144304196033, 0.06378983188307788,
      0.058312397849304, 0.052811047183022333, 0.047288995468490018,
      0.041749467232078175, 0.036195694279362527, 0.030630914029184483,
      0.025058367844666397, 0.019481299363810906, 0.013902952829359124,
      0.0083265714182935817, 0.0027553955723847476, -0.0028073386687639309,
      -0.0083584013334527373, -0.013894570180606211, -0.019412632358495743,
      -0.024909386057792558, -0.030381642161692684, -0.035826225887903504,
      -0.041239978425504857, -0.04661975856449329, -0.051962444315135636,
      -0.0572649345212074, -0.062524150462973882, -0.067737037448846515,
      -0.072900566396995492, -0.07801173540655959, -0.083067571313534927,
      -0.088065131237277772, -0.093001504111946728, -0.097873812201367677,
      -0.10267921260370902, -0.10741489873635997, -0.11207810180620353,
      -0.11666609226426398, -0.12117618123997068, -0.12560572195940134,
      -0.12995211114418448, -0.13421279039087805, -0.13838524753126152,
      -0.14246701796948616, -0.14645568600096004, -0.15034888610814576,
      -0.15414430423343112, -0.15783967903088866, -0.16143280309205765,
      -0.16492152414980052, -0.16830374625662972, -0.17157743093878886,
      -0.17474059832326788, -0.17779132823981073, -0.18072776129662124,
      -0.18354809992754798, -0.18625060941382252, -0.1888336188750657,
      -0.19129552223480636, -0.19363477915479846, -0.19584991594078643,
      -0.19793952641955914, -0.199902272783463, -0.20173688640704887,
      -0.20344216863060083, -0.20501699151373023, -0.20646029855760248,
      -0.20777110539333288, -0.20894850043918112, -0.20999164552664598,
      -0.21089977649131791, -0.21167220373151005, -0.21230831273277861,
      -0.21280756456008473, -0.21316949631479576, -0.2133937215577465,
      -0.21347993069838378, -0.21342789134792162, -0.21323744863912986,
      -0.21290852551052908, -0.21244112295603532, -0.21183532023737481,
      -0.2110912750635508, -0.21020922373317544, -0.20918948124095008,
      -0.20803244135040755, -0.20673857662801162, -0.20530843844304586,
      -0.20374265693169791, -0.2020419409253725, -0.20020707784113223,
      -0.19823893353705802, -0.19613845213389133, -0.1939066557976751,
      -0.19154464448758865, -0.18905359566874627, -0.18643476398792333,
      -0.1836894809140556, -0.18081915434418447, -0.1778252681727415,
      -0.17470938182563661, -0.17147312975924012, -0.16811822092526543,
      -0.16464643819921537, -0.16105963777528831, -0.1573597485281997,
      -0.15354877133555253, -0.14962877837269337, -0.14560191237123243,
      -0.14147038584181618, -0.13723648026689197, -0.13290254525930861,
      -0.12847099768823753, -0.12394432077244263, -0.11932506314295242,
      -0.11461583787243808, -0.10981932147417174, -0.10493825287064774,
      -0.09997543233014819, -0.0949337203751364, -0.089816036659098014,
      -0.084625358814329338, -0.079364721273121691, -0.07403721405752231,
      -0.068645981543170934, -0.063194221194641478, -0.057685182273515941,
      -0.0521221645218517, -0.046508516817768013, -0.040847635806119144,
      -0.035142964503565771, -0.029397990880504054, -0.023616246419722545,
      -0.017801304647635897, -0.011956779648370197, -0.006086324552001662,
      -0.00019363000144379384, 0.0057175773991892222, 0.011643536659533797,
      0.0175804539962469, 0.023524504445090119, 0.029471833492245653,
      0.035418558723466421, 0.04136077148920813, 0.047294538588783415,
      0.053215903967519539, 0.059120890430587478, 0.065005501372273733,
      0.07086572251644592, 0.076697523672832307, 0.082496860504789979,
      0.088259676307613444, 0.093981903799535749, 0.0996594669221328,
      0.10528828265089721, 0.1108642628141833, 0.11638331591950336,
      0.12184134898954017, 0.12723426940230148, 0.13255798673848246,
      0.13780841463391386, 0.14298147263548694, 0.14807308806183178,
      0.15307919786718188, 0.15799575050524986, 0.16281870779598315,
      0.16754404679411386, 0.17216776165451064, 0.17668586549909704,
      0.18109439228118193, 0.185389398646933, 0.18956696579452276,
      0.19362320132818883, 0.19755424110861486, 0.20135625109695562,
      0.20502542919243352, 0.20855800706440109, 0.21195025197422898,
      0.21519846858971028, 0.21829900079121578, 0.22124823346632488,
      0.22404259429298184, 0.22667855551299837, 0.22915263569164779,
      0.23146140146507671, 0.2336014692729754, 0.23556950707694316,
      0.2373622360647249, 0.23897643233579635, 0.2404089285731266,
      0.24165661569518046, 0.24271644449068114, 0.24358542723464346,
      0.24426063928454889, 0.2447392206559148, 0.24501837757639444,
      0.24509538402082665, 0.24496758322019641, 0.24463238915036178,
      0.2440872879962582, 0.24332983959086082, 0.2423576788313338,
      0.24116851706721912, 0.23976014346407903, 0.23813042634016021,
      0.23627731447429193, 0.2341988383872973, 0.23189311159402198,
      0.22935833182651733, 0.22659278222807927, 0.22359483251464451,
      0.22036294010801452, 0.21689565123670837, 0.21319160200499632,
      0.20924951942902673, 0.20506822243995373, 0.20064662285617524,
      0.18941518174712527, 0.16476598510787663, 0.13321602295950646,
      0.10133036710958881, 0.069127737430675712, 0.036627543521511145,
      0.0038498716862012936, -0.029184529433513084, -0.0624542645573114,
      -0.0959373087939273, -0.12961102598405827, -0.16345218834116565,
      -0.19743699737683618, -0.23154110609037654, -0.26573964239835779,
      -0.3000072337840784, -0.33431803313974262, -0.36864574577155318,
      -0.40296365753512448, -0.43724466407339779, -0.47146130111668133,
      -0.50558577580942476, -0.53958999902488136, -0.5734456186232465,
      -0.60712405361411836, -0.64059652917008136, -0.6738341124546553,
      -0.70680774920522227, -0.7394883010243094, -0.77184658332893319,
      -0.803853403896134, -0.83547960195880622, -0.86669608778459817,
      -0.89747388268641393, -0.9277841594013434, -0.95759828277720382,
      -0.98688785070617391, -1.015624735238873, -1.0437811238181216,
      -1.0713295605668018, -1.0982429875642474, -1.124494786041071,
      -1.15005881743532, -1.1749094642319575, -1.1990216705253887,
      -1.2223709822372901, -1.2449335869192435, -1.2666863530742472,
      -1.2876068689312667, -1.3076734806055592, -1.3268653295732462,
      -1.345162389406158, -1.3625455016876411, -1.3789964110532364,
      -1.3944977992909078, -1.4090333184377208, -1.422587622811891,
      -1.4351463999148524, -1.4466964001555813, -1.4572254653251049,
      -1.4667225557760657, -1.4751777762480582, -1.4825824002831927,
      -1.4889288931875173, -1.494210933482681, -1.4984234328047117,
      -1.5015625541991582, -1.5036257287781061, -1.5046116706902855,
      -1.5045203903691726, -1.5033532060240593, -1.5011127533368183,
      -1.4978029933372425, -1.4934292184267948, -1.4879980565252067,
      -1.4815174733148566, -1.4739967725676382, -1.4654465945325053,
      -1.4558789123712312, -1.4453070266293113, -1.4337455577372267,
      -1.4212104365326685, -1.407718892800119, -1.3932894418366084,
      -1.3779418690371181, -1.3616972125123374, -1.3445777437484439,
      -1.3266069463198031, -1.3078094926717272, -1.2882112189941937,
      -1.2678390982066849, -1.2467212110782044, -1.2248867155177796,
      -1.2023658140588067, -1.1791897195764485, -1.1553906192751884,
      -1.1310016369858404, -1.1060567938164469, -1.0805909672028911,
      -1.0546398484092905, -1.028239898525898, -1.0014283030257523,
      -0.97424292493135944, -0.94672225665239718, -0.91890537055855936,
      -0.89083186834857753, -0.86254182928509371, -0.83407575736130757,
      -0.80547452747344928, -0.77677933066903826, -0.74803161854753375,
      -0.71927304688951188, -0.69054541859202856, -0.66189062599124071,
      -0.63335059265224058, -0.60496721471003978, -0.57678230184370538,
      -0.54883751797119185, -0.52117432174854439, -0.49383390696103568,
      -0.4668571428939598, -0.44028451477091013, -0.41415606434795205,
      -0.3885113307526295, -0.36338929165728445, -0.33882830487412385,
      -0.31486605046361305, -0.29153947344270759, -0.26888472718205969,
      -0.24693711758045309, -0.22573104810309541, -0.2052999657709296,
      -0.18567630818531819, -0.16689145167427222, -0.14897566064203971,
      -0.13195803820476482, -0.11586647819279401, -0.10072761859821393,
      -0.086566796545212377, -0.073408004858453807, -0.061273850303138651,
      -0.050185513567689896, -0.040162711058763921, -0.0312236585749931,
      -0.023385036923984751, -0.0166619595444735, -0.011067942192745204,
      -0.00661487474979633, -0.0033129952027714906, -0.0011708658513430461,
      -0.00039070357311671712 } ;

    TRACKING_CONTROL_KPES_DW.FromWorkspace1_PWORK.TimePtr = (void *)
      pTimeValues0;
    TRACKING_CONTROL_KPES_DW.FromWorkspace1_PWORK.DataPtr = (void *)
      pDataValues0;
    TRACKING_CONTROL_KPES_DW.FromWorkspace1_IWORK.PrevIndex = 0;
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
      29.97, 29.98, 29.990000000000002, 30.0, 30.01, 30.02, 30.03, 30.04, 30.05,
      30.060000000000002, 30.07, 30.080000000000002, 30.09, 30.1, 30.11, 30.12,
      30.13, 30.14, 30.150000000000002, 30.16, 30.17, 30.18, 30.19, 30.2, 30.21,
      30.22, 30.23, 30.240000000000002, 30.25, 30.26, 30.27, 30.28, 30.29, 30.3,
      30.310000000000002, 30.32, 30.330000000000002, 30.34, 30.35, 30.36, 30.37,
      30.38, 30.39, 30.400000000000002, 30.41, 30.42, 30.43, 30.44, 30.45, 30.46,
      30.47, 30.48, 30.490000000000002, 30.5, 30.51, 30.52, 30.53, 30.54, 30.55,
      30.560000000000002, 30.57, 30.580000000000002, 30.59, 30.6, 30.61, 30.62,
      30.63, 30.64, 30.650000000000002, 30.66, 30.67, 30.68, 30.69, 30.7, 30.71,
      30.72, 30.73, 30.740000000000002, 30.75, 30.76, 30.77, 30.78, 30.79, 30.8,
      30.810000000000002, 30.82, 30.830000000000002, 30.84, 30.85, 30.86, 30.87,
      30.88, 30.89, 30.900000000000002, 30.91, 30.92, 30.93, 30.94, 30.95, 30.96,
      30.970000000000002, 30.98, 30.990000000000002 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0,
      0.00430613743447595, 0.0344696423056592, 0.10777569783338505,
      0.20702977610471995, 0.31062473126182694, 0.41411433178888762,
      0.51735090372773784, 0.62018634271516226, 0.72247231599949457,
      0.82406046587051718, 0.924802614215489, 1.0245509679115348,
      1.1231583247619414, 1.2204782796817282, 1.3163654308356152,
      1.410675585430579, 1.5032659648653628, 1.593995408936586,
      1.6827245788017127, 1.7693161584021593, 1.8536350540479498,
      1.9355485918665327, 2.0149267128215071, 2.0916421650097394,
      2.1655706929468161, 2.2365912235530452, 2.3045860485587522,
      2.3694410030487258, 2.4310456398712135, 2.4892933996436555,
      2.5440817760885723, 2.5953124764405593, 2.6428915766749581,
      2.6867296713109643, 2.7267420175469463, 2.7628486735009536,
      2.7949746303300911, 2.8230499380113212, 2.847009824579708,
      2.86679480862215, 2.8823508048358, 2.89362922247637, 2.9005870565215894,
      2.9031869713822962, 2.9013973770258081, 2.8951924973609464,
      2.8845524307545531, 2.8694632025688591, 2.8499168096034841,
      2.8259112563559037, 2.7974505830077132, 2.7645448850688288,
      2.72721032462078, 2.68546913310421, 2.6393496056228183, 2.5888860867323538,
      2.5341189477075288, 2.4750945552855153, 2.411865231898489,
      2.3444892074252244, 2.2730305624932257, 2.1975591633881169,
      2.1181505886286294, 2.0348860472800472, 1.9478522891075416,
      1.8571415066540571, 1.762851229347935, 1.6650842097971468,
      1.5639483023779253, 1.459556334253985, 1.3520259690198644,
      1.2414795631217379, 1.1280440152292004, 1.0118506087534942,
      0.89303484772373853, 0.77173628622861856, 0.64809835163853691,
      0.52226816185246783, 0.39439633680998754, 0.26463680450505822,
      0.13314660177649029, 8.5670148752825444E-5, -0.13438335302262672,
      -0.27009534780880728, -0.40688292906126927, -0.54457666757851086,
      -0.68300531479464854, -0.82199603065297089, -0.96137461435608,
      -1.1009657376856432, -1.2405931805576242, -1.3800800684766219,
      -1.5192491115650619, -1.6579228448306822, -1.7959238693312936,
      -1.9330750938892343, -2.0691999770205953, -2.2041227687377689,
      -2.3376687518664152, -2.4696644825512792, -2.5999380295812746,
      -2.7283192122067068, -2.854639836114556, -2.978733927201513,
      -3.100437962803348, -3.2195911000530626, -3.3360354010683571,
      -3.4496160545743861, -3.5601815936758787, -3.6675841094729789,
      -3.7716794601669235, -3.8723274753799073, -3.9693921553679479,
      -4.0627418648447788, -4.1522495211193631, -4.2377927762637846,
      -4.3192541930492281, -4.3965214143720752, -4.4694873259332093,
      -4.5380502119052215, -4.6021139033530707, -4.66158791920578,
      -4.7163875995292965, -4.7664342309022762, -4.8116551637233842,
      -4.8519839212490723, -4.887360300188095, -4.917730462689609,
      -4.9430470195810283, -4.9632691047507471, -4.9783624405036822,
      -4.9882993937839695, -4.9930590232271683, -4.9926271168954006,
      -4.9869962206305809, -4.9761656570113013, -4.9601415348260387,
      -4.9389367490631981, -4.9125709713804158, -4.88107063104536,
      -4.8444688864096515, -4.8028055868809441, -4.7561272254442635,
      -4.7044868818327217, -4.6479441563565445, -4.5865650944953886,
      -4.5204221023586966, -4.4495938530925052, -4.3741651843820408,
      -4.2942269871704033, -3.9530534323581246, -3.1051489929764782,
      -2.2817553154474957, -1.992516319582192, -1.9649026361348558,
      -1.9367089384431972, -1.9079424476379077, -1.8786105763836862,
      -1.8487209268136391, -1.8182812883837813, -1.7872996356865773,
      -1.7557841261861535, -1.7237430978905828, -1.6911850669654156,
      -1.6581187252762126, -1.6245529378802734, -1.5904967404506407,
      -1.5559593366404321, -1.5209500953944342, -1.485478548186868,
      -1.4495543862177982, -1.4131874575504231, -1.376387764181751,
      -1.3391654590674806, -1.301530843094133, -1.2634943619912897,
      -1.2250666031954338, -1.1862582926669407, -1.1470802916499478,
      -1.1075435933835522, -1.0676593197763808, -1.027438718015383,
      -0.98689315714860415, -0.9460341246134143, -0.904873222712376,
      -0.86342216506607372, -0.82169277301286014, -0.7796969719714435,
      -0.73744678775730033, -0.69495434287913871, -0.65223185278212525,
      -0.60929162205208776, -0.56614604061409, -0.52280757987312976,
      -0.47928878881442438, -0.43560229010364232, -0.39176077614860827,
      -0.34777700511565668, -0.30366379693169659, -0.25943402927136572,
      -0.21510063350604883, -0.17067659062667259, -0.12617492717372769,
      -0.0816087111158658, -0.036991047711598633, 0.0076649246060655971,
      0.052346038416295433, 0.097039101478790718, 0.14173090090760257,
      0.18640820737215719, 0.23105777932081997, 0.27566636719156246,
      0.32022071761486054, 0.36470757766970918, 0.40911369910883139,
      0.45342584258901658, 0.4976307819103849, 0.54171530826250214,
      0.58566623445930277, 0.62947039916105785, 0.67311467111891232,
      0.71658595339356634, 0.75987118756295424, 0.8029573579473086,
      0.84583149580451578, 0.88848068350321141, 0.93089205870422387,
      0.97305281853581249, 1.0149502237186128, 1.0565716026977081,
      1.0979043557658654, 1.1389359591367654, 1.1796539690129049,
      1.2200460256555783, 1.2600998573796363, 1.2998032845556218,
      1.33914422359812, 1.3781106908859018, 1.4166908066914883,
      1.4548727990552943, 1.4926450076339846, 1.5299958875211725,
      1.5669140130299173, 1.6033880814467092, 1.6394069167288567,
      1.6749594731756174, 1.7100348390716709, 1.7446222402653351,
      1.7787110437193816, 1.8122907610282331, 1.8453510518645506,
      1.8778817273878849, 1.9098727536294473, 1.9413142548048472,
      1.9721965165771165, 2.0025099892902114, 2.0322452911253324,
      2.06139321121153, 2.0899447127107229, 2.1178909358057587,
      2.1452232006513507, 2.1719330102787295, 2.1980120534245677,
      2.2234522073163991, 2.2482455403827188, 2.2723843149099956,
      2.2958609896475615, 2.3186682223366706, 2.340798872172698,
      2.3622460022196234, 2.3830028817514703, 2.403062988518271,
      2.4224200109548768, 2.4410678503292127, 2.4590006228097905,
      2.4762126614655244, 2.4926985181944397, 2.5084529655969221,
      2.5234709987678716, 2.5377478369983892, 2.5512789254417085,
      2.5640599366816264, 2.5760867722275433, 2.5873555639538939,
      2.5978626754345875, 2.6076047032333411, 2.6165784781054224,
      2.6247810661120203, 2.6322097696845836, 2.6388621285872125,
      2.6447359208045493, 2.6498291633761331, 2.6541401131374656,
      2.6576672673594928, 2.6604093643459126, 2.6623653839516437,
      2.6635345479863961, 2.6639163205652245, 2.6635104083932948,
      2.6623167609419234, 2.6603355705534111, 2.6575672724826997,
      2.654012544844504, 2.6496723084804841, 2.64454772675029,
      2.6386402052534064, 2.6319513914567523, 2.6244831742403405,
      2.6162376833817076, 2.6072172889506975, 2.5974246006252848,
      2.5868624669268994, 2.575533974376925, 2.5634424465859027,
      2.5505914432600827, 2.5369847591162311, 2.5226264227295969,
      2.50752069531684, 2.4916720694311203, 2.4750852675712292,
      2.4577652407267139, 2.4397171668492557, 2.4209464492555006,
      2.4014587149356839, 2.38125981278552, 2.3603558118092121,
      2.3387529992091665, 2.3164578783967791, 2.2934771669628473,
      2.2698177945681559, 2.2454869007607994, 2.2204918327074705,
      2.1948401428781263, 2.168539586669723, 2.1415981199473082,
      2.1140238965053859, 2.0858252654864184, 2.0570107687429613,
      2.0275891381067157, 1.9975692926249049, 1.966960335711142,
      1.9357715522298671, 1.9040124055589154, 1.8716925345737223,
      1.83882175054735, 1.8054100340202324, 1.7714675316198125,
      1.7370045528267528, 1.7020315666556869, 1.6665591982799621,
      1.6305982256867317, 1.5941595762055192, 1.5572543229689568,
      1.5198936813915145, 1.4820890055724938, 1.4438517846542376,
      1.4051936391269013, 1.3661263170876528, 1.3266616904821065,
      1.2868117513004687, 1.2465886077036181, 1.2060044801245819,
      1.1650716973655078, 1.123802692621569, 1.082209999490255,
      1.0403062479278229, 0.99810416017459458, 0.95561654669692275,
      0.91285630205008128, 0.86983640071604185, 0.82656989292903649,
      0.783069900490746, 0.73934961255966392, 0.69542228136647066,
      0.6513012179479, 0.60699978790716058, 0.56253140709186888,
      0.51790953725134781, 0.4731476817167336, 0.4282593810631099,
      0.38325820876091937, 0.33815776678050352, 0.29297168121206824,
      0.24771359790706743, 0.20239717809360047, 0.15703609394635745,
      0.11164402418202506, 0.066234649706221921, 0.020821649190728042,
      -0.024581305326364919, -0.0699605528432829, -0.11530244779207856,
      -0.16059336439194002, -0.20581970104201566, -0.25096788470611564,
      -0.29602437526619696, -0.34097566985460021, -0.38580830717839465,
      -0.43050887187087278, -0.47506399880464689, -0.51946037732565342,
      -0.56368475552096375, -0.60772394453429679, -0.65156482274708882,
      -0.69519433993549351, -0.73859952150926955, -0.78176747265852742,
      -0.82468538244950351, -0.8673405279126597, -0.90972027812174072,
      -0.95181209823284063, -0.99360355349139462, -1.0350823131648588,
      -1.0762361544671479, -1.1170529664838966, -1.1575207540245613,
      -1.1976276414236187, -1.2373618762895042, -1.2767118332633702,
      -1.3156660177263941, -1.3542130694148735, -1.3923417659968038,
      -1.4300410266529842, -1.4672999155934001, -1.504107645485274,
      -1.5404535808422044, -1.5763272413878506, -1.6117183053741062,
      -1.6466166128141908, -1.6810121686429393, -1.7148951458609445,
      -1.7482558886494011, -1.7810849153516097, -1.813372921416184,
      -1.8451107823251673, -1.8762895564290238, -1.9069004877138991,
      -1.9369350084966954, -1.9663847421039802, -1.9952415054313259,
      -2.0234973114730246, -2.0511443717873217, -2.0781750988367764,
      -2.1045821083326604, -2.1303582214939727, -2.1554964672158188,
      -2.1799900841534514, -2.2038325227736624, -2.2270174473397284,
      -2.2495387377860423, -2.2713904915211955, -2.2925670251890486,
      -2.3130628763607239, -2.3328728051074386, -2.3519917955146075,
      -2.3704150571440494, -2.3881380264065, -2.4051563678557888,
      -2.4214659753909147, -2.4370629733955478, -2.4519437178226675,
      -2.4661047971650416, -2.4795430333480697, -2.4922554825678489,
      -2.5042394360400322, -2.5154924206756859, -2.52601219965433,
      -2.5357967729336139, -2.5448443776916179, -2.5531534886717631,
      -2.5607228184604485, -2.5675513176620903, -2.5736381750072965,
      -2.5789828174128338, -2.5835849099100927, -2.5874443555016429,
      -2.5905612949846528, -2.59293610664599, -2.594569405887019,
      -2.5954620447855685, -2.5956151115652024, -2.5950299299909276,
      -2.59370805867758, -2.5916512903338988, -2.5888616509214786,
      -2.5853413987233425, -2.58109302335868, -2.5761192447011356,
      -2.5704230117236597, -2.564007501291699, -2.5568761168298098,
      -2.5490324869488257, -2.5404804640193777, -2.5312241226102952,
      -2.5212677578924705, -2.5106158839730588, -2.4992732321374285,
      -2.4872447490371523, -2.4745355947926106, -2.4611511410133122,
      -2.4470969687906816, -2.4323788666010144, -2.4170028280915465,
      -2.4009750498729066, -2.3843019292217225, -2.3669900616862258,
      -2.34904623866244, -2.3304774448738961, -2.3112908558227723,
      -2.29149383517426, -2.2710939320354813, -2.2500988782071167,
      -2.2285165854029874, -2.20635514236771, -2.1836228119241459,
      -2.1603280280066324, -2.1364793926304926, -2.1120856727932518,
      -2.0871557973280126, -2.0616988536740513, -2.0357240846518567,
      -2.009240885178047, -1.9822587988762728, -1.9547875146869003,
      -1.9268368634307664, -1.8984168143292584, -1.8695374714478699,
      -1.8402090701093463, -1.8104419732847874, -1.7802466679575903,
      -1.749633761402773, -1.7186139774142231, -1.6871981525783313,
      -1.6553972324533281, -1.623222267721254, -1.59068441030494,
      -1.5577949094417121, -1.5245651077963598, -1.4910064374764265,
      -1.4571304160096994, -1.4229486423221609, -1.3884727927432967,
      -1.3537146169258008, -1.3186859337191799, -1.2833986270973579,
      -1.2478646420008443, -1.2120959802297584, -1.1761046962881889,
      -1.1399028931504309, -1.1035027181073311, -1.0669163586033208,
      -1.0301560380053238, -0.99323401133362055, -0.95616256108314968,
      -0.91895399302968928, -0.88162063194538087, -0.84417481736121225,
      -0.80662889932526294, -0.76899523421146121, -0.73128618047240668,
      -0.69351409434788636, -0.65569132567714639, -0.61783021370687352,
      -0.57994308286045448, -0.54204223848935829, -0.50413996269300621,
      -0.46624851019487651, -0.42838010413827976, -0.39054693190550205,
      -0.35276114099313266, -0.31503483491091672, -0.27738006907736573,
      -0.23980884673345249, -0.20233311487558114, -0.16496476020977721,
      -0.12771560518914088, -0.090597404009393881, -0.053621838615834791,
      -0.016800514792114998, 0.019855041692918164, 0.056333388977712708,
      0.092623172981474239, 0.12871313116092073, 0.16459209626430787,
      0.20024900007021376, 0.23567287709733165, 0.27085286825167554,
      0.30577822438537333, 0.34043830989191382, 0.37482260625588926,
      0.40892071552852444, 0.44272236371782736, 0.47621740418048913,
      0.50939582100639691, 0.54224773229038925, 0.57476339336581916,
      0.60693319996890838, 0.63874769140259324, 0.670197553644143,
      0.7012736223355226, 0.73196688575403634, 0.76226848774059619,
      0.79216973058267415, 0.82166207780392608, 0.85073715686718321,
      0.87938676189241083, 0.907602856285107, 0.9353775752885185,
      0.96270322846106871, 0.98957230210147062, 1.015977461659888,
      1.0419115540255097, 1.0673676097264777, 1.0923388451167106,
      1.1168186645128717, 1.1408006622024702, 1.1642786243801688,
      1.1872465310821454, 1.2096985579874873, 1.2316290781961774,
      1.2530326639078426, 1.2739040879798318, 1.2942383255226819,
      1.3140305553729388, 1.3332761614462791, 1.3519707340453557,
      1.3701100711420739, 1.3876901795509946, 1.4047072759836265,
      1.4211577880717, 1.4370383553358625, 1.4523458300487955,
      1.4670772780070653, 1.4812299792413479, 1.4948014286671685,
      1.5077893366580593, 1.5201916295053177, 1.5320064498127166,
      1.5432321568490481, 1.5538673268046894, 1.5639107529497098,
      1.5733614457156377, 1.5822186327404846, 1.5904817587951614,
      1.5981504856549997, 1.6052246918992383, 1.6117044725792573,
      1.617590138870713, 1.6228822176580462, 1.6275814509975519,
      1.6316887954864594, 1.6352054216099821, 1.6381327130302892,
      1.6404722657269737, 1.642225887070305, 1.6433955948908017,
      1.6439836164324826, 1.6439923871986524, 1.6434245497648232,
      1.642282952518249, 1.6405706483217217, 1.638290893082524,
      1.6354471442593292, 1.6320430593336166, 1.6280824941674834,
      1.6235695012998443, 1.6185083281839552, 1.6129034153557775,
      1.6067593945380061, 1.6000810866605228, 1.5928734998265921,
      1.5851418271978783, 1.5768914448504643, 1.5681279095469762,
      1.5588569564207759, 1.5490844966325188, 1.5388166149408526,
      1.528059567249699, 1.5168197780587607, 1.5051038378491852,
      1.4929185004538648, 1.4802706803332475, 1.4671674498243839,
      1.453616036306205, 1.4396238193138344, 1.4251983276390687,
      1.4103472363413216, 1.3950783636990836, 1.3793996681499097,
      1.3633192451767242, 1.3468453240934217, 1.3299862648496537,
      1.3127505547803926, 1.2951468052653159, 1.277183748400101,
      1.2588702335914461, 1.2402152241284563, 1.2212277937243021,
      1.2019171229895813, 1.1822924958912915, 1.1623632961932859,
      1.1421390038213672, 1.1216291912061973, 1.1008435196537691,
      1.0797917356049933, 1.0584836668956568, 1.0369292190271384,
      1.0151383713486326, 0.9931211732672619, 0.97088774040858494,
      0.94844825074934414, 0.925812940770629, 0.90299210153911269,
      0.8799960748125033, 0.85683524910399622, 0.83352005572971055,
      0.81006096489092538, 0.78646848168165706, 0.76275314211285927,
      0.7389255091424356, 0.71499616867764959, 0.69097572556999132,
      0.66687479962290364, 0.64270402158508855, 0.61847402914930039,
      0.59419546296015946, 0.56987896255913628, 0.545535162425592,
      0.52117468799674727, 0.49680815162602676, 0.47244614862948958,
      0.44809925330459838, 0.42377801496464518, 0.399492953991905,
      0.37525455787503043, 0.35107327729803822, 0.3269595222441497,
      0.3029236580777851, 0.27897600166215714, 0.25512681753382244,
      0.23138631404463283, 0.20776463955486268, 0.18427187866155414,
      0.16091804841467727, 0.13771309459925679, 0.11466688800225225,
      0.091789220754425666, 0.069089802704217024, 0.046578257750230383,
      0.024264120291329034, 0.0021568317004617048, -0.019734263227988855,
      -0.041399919753786811, -0.0628309965852821, -0.084018459289551692,
      -0.10495338368637171, -0.12562695911600408, -0.14603049171891291,
      -0.16615540768150716, -0.18599325638913569, -0.20553571358186717,
      -0.22477458443437023, -0.24370180657848092, -0.26230945309879966,
      -0.28058973547963095, -0.29853500647770925, -0.31613776294293883,
      -0.33339064861805118, -0.35028645683847282, -0.36681813319848927,
      -0.38297877817934556, -0.39876164968356431, -0.41416016551112012,
      -0.42916790581994463, -0.44377861548929559, -0.4579862063980506,
      -0.47178475971745049, -0.48516852806599819, -0.498131937621742,
      -0.51066959020464131, -0.52277626524552256, -0.53444692171724684,
      -0.54567669998231272, -0.556460923582549, -0.56679510097914665,
      -0.57667492718550861, -0.58609628534016867, -0.59505524824996947,
      -0.60354807980862013, -0.6115712363730359, -0.61912136807620732,
      -0.62619532003041367, -0.63279013350628266, -0.63890304700677547,
      -0.64453149726311276, -0.64967312020534052, -0.6543257517987543,
      -0.65848742881960443, -0.66215638961866818, -0.66533107471292208,
      -0.66801012736153531, -0.67019239407886766, -0.671876925013449,
      -0.67306297431712869, -0.673750000400172, -0.67393766610323957,
      -0.67362583882127425, -0.67281459055770809, -0.67150419786335513,
      -0.66969514171458355, -0.66738810735063636, -0.66458398398592888,
      -0.66128386447354182, -0.65748904490338322, -0.65320102409174852,
      -0.64842150301727675, -0.64315238418324783, -0.63739577091328947,
      -0.63115396654595768, -0.62442947355954237, -0.61722499267396058,
      -0.60954342180076837, -0.60138785496269165, -0.59276158117352051,
      -0.58366808316892282, -0.57411103611851011, -0.56409430625683576,
      -0.55362194944091125, -0.5426982096475611, -0.53132751736712658,
      -0.51951448796307975, -0.5072639199532808, -0.49458079323940557,
      -0.48147026724178948, -0.4679376789351794, -0.45398854091669572,
      -0.43962853935434004, -0.42486353182426873, -0.40969954516297713,
      -0.39414277323070462, -0.37819957457942532, -0.36187647009857044,
      -0.34518014059460495, -0.3281174243041155, -0.31069531434826225,
      -0.29292095610427527, -0.27480164457258682, -0.25634482168191963,
      -0.23755807347592922, -0.21844912730385102, -0.19902584897091993,
      -0.17929623975621972, -0.15926843347154668, -0.13895069347607986,
      -0.11835140949671175, -0.097479094550877859, -0.076342381832854536,
      -0.054950021418643864, -0.03331087703895079, -0.011433922785797601,
      0.010671760275088543, 0.032996987426484596, 0.0555324737381753,
      0.078268837585936391, 0.10119660407704116, 0.12430620862203244,
      0.14758800050252466, 0.1710322464343392, 0.19462913424431041,
      0.21836877652514544, 0.24224121431756815, 0.26623642080325927,
      0.29034430509223891, 0.31455471597831136, 0.33885744572472065,
      0.36324223389729232, 0.38769877115376045, 0.41221670315951159,
      0.436785634441118, 0.46139513226626455, 0.4860347305569036,
      0.51069393377125549, 0.53536222091201713, 0.560029049420121,
      0.58468385912060772, 0.60931607621977957, 0.63391511721219729,
      0.65847039291094256, 0.68297131241704179, 0.70740728706056555,
      0.73176773441544252, 0.75604208225835634, 0.78021977254486563,
      0.80429026541831061, 0.828243043143911, 0.8520676140509561,
      0.87575351653543165, 0.89929032299377853, 0.92266764375185684,
      0.945875130976033, 0.9689024825754593, 0.9917394461423239,
      1.014375822799614, 1.0368014710628555, 1.0590063106915557,
      1.0809803264808808, 1.1027135721031669, 1.1241961738734298,
      1.1454183344883839, 1.1663703367598641, 1.1870425473036661,
      1.2074254202374384, 1.2275095007863739, 1.2472854289166102,
      1.2667439429237521, 1.2858758829226709, 1.3046721944005024,
      1.3231239317002552, 1.3412222614090232, 1.3589584657651412,
      1.3763239460412096, 1.3933102258263641, 1.4099089543213077,
      1.4261119095560533, 1.441911001525749, 1.4572982753913797,
      1.47226591457112, 1.486806243730129, 1.500911731783626, 1.5145749948519309,
      1.5277887991506609, 1.5405460638168829, 1.5528398636944327,
      1.5646634320510389, 1.5760101632495529, 1.5868736153829393,
      1.5972475128254675, 1.607125748695992, 1.6165023873145346,
      1.6253716666220899, 1.6337280004397756, 1.6415659807423477,
      1.6488803798648384, 1.6556661525851855, 1.6619184382413932,
      1.6676325627040562, 1.6728040402848889, 1.6774285756521869,
      1.6815020655792237, 1.6850206006702921, 1.6879804670667158,
      1.6903781480193807, 1.6922103253634995, 1.6934738810094963,
      1.6941658983305818, 1.6942836634295939, 1.693824666406732,
      1.6927866024996825, 1.6911673731679537, 1.6889650871338562,
      1.6861780613007442, 1.6828048216234932, 1.6788441038830015,
      1.6742948544160887, 1.6691562307933472, 1.6634276023231442,
      1.6571085505568592, 1.6501988697382359, 1.6426985670859724,
      1.6346078630937073, 1.6259271917142339, 1.616657200425976,
      1.6067987503299417, 1.5963529160573759, 1.585320985625988,
      1.5737044603082009, 1.5615050543302922, 1.5487246944681619,
      1.5353655196912748, 1.5214298806440067, 1.5069203389907682,
      1.4918396668595719, 1.4761908460839672, 1.4599770673401991,
      1.443201729302632, 1.4258684376880797, 1.4079810042420697,
      1.3895434455773632, 1.3705599819983942, 1.3510350363125156,
      1.3309732324410302, 1.3103793940250577, 1.2892585429628065,
      1.2676158978384748, 1.2454568723615436, 1.222787073632154,
      1.1996123003569148, 1.1759385411064722, 1.1517719723594857,
      1.127118956527386, 1.1019860399578154, 1.0763799508304313,
      1.0503075969519384, 1.0237760635701341, 0.99679261107994344,
      0.96936467258702375, 0.9414998515969587, 0.91320591948097218,
      0.884490812863189, 0.85536263110270339, 0.82582963361112582,
      0.795900237117499, 0.76558301284542052, 0.734886683681162,
      0.70382012137329253, 0.67239234347943644, 0.64061251037739442,
      0.60848992223655662, 0.57603401585119129, 0.54325436159043616,
      0.51016066009209493, 0.47676273897071425, 0.44307054964875914,
      0.40909416392163928, 0.37484377054080831, 0.34032967180513579,
      0.30556228008170133, 0.27055211425688919, 0.23530979621632719,
      0.19984604721959603, 0.16417168418063971, 0.12829761613979693,
      0.092234840468743168, 0.055994439068786178, 0.019587574715818484,
      -0.01697451282801668, -0.053680510645633658, -0.09051903653240434,
      -0.12747864289784078, -0.16454782062067869, -0.20171500306920706,
      -0.23896857006920302, -0.2762968518538248, -0.31368813310212573,
      -0.35113065691352158, -0.38861262892488518, -0.42612222140241207,
      -0.46364757716294991, -0.50117681376772261, -0.53869802767740926,
      -0.57619929826795546, -0.613668691978899, -0.65109426645392487,
      -0.6884640746274574, -0.725766168930626, -0.76298860545397873,
      -0.80011944794251044, -0.83714677202247467, -0.87405866943006316,
      -0.910843252022217, -0.94748865594884513, -0.98398304578354323,
      -1.0203146186372392, -1.0564716083186989, -1.0924422893255248,
      -1.1282149810216042, -1.1637780517268408, -1.1991199226795402,
      -1.2342290721639211, -1.2690940395220482, -1.3037034291605196,
      -1.338045914527159, -1.3721102420464275, -1.4058852351361029,
      -1.4393597980943169, -1.4725229199705849, -1.5053636784382418,
      -1.5378712436469595, -1.5700348820171957, -1.6018439600390872,
      -1.6332879480096334, -1.6643564236599317, -1.6950390759274654,
      -1.7253257085942533, -1.7552062438345324, -1.7846707257775531,
      -1.813709324007484, -1.8423123371281469, -1.8704701961483838,
      -1.8981734678001088, -1.9254128579802265, -1.9521792150185262,
      -1.9784635328946343, -2.0042569544993043, -2.0295507747306782,
      -2.0543364435978542, -2.0786055693205241, -2.1023499212450618,
      -2.1255614328239756, -2.1482322045264026, -2.1703545066082759,
      -2.1919207819097588, -2.2129236485578248, -2.2333559026264709,
      -2.2532105207327606, -2.2724806625283187, -2.2911596731854265,
      -2.3092410858195236, -2.3267186238208222, -2.3435862030969257,
      -2.3598379342935241, -2.3754681249555158, -2.3904712815885629,
      -2.4048421116673171, -2.4185755255488539, -2.4316666383584695,
      -2.4441107717957871, -2.4559034558450565, -2.4670404304364317,
      -2.4775176470034874, -2.4873312700290349, -2.4964776784758258,
      -2.5049534671038272, -2.5127554478117049, -2.5198806508273632,
      -2.5263263258316595, -2.5320899430464254, -2.5371691942007577,
      -2.5415619934440747, -2.5452664781875414, -2.5482810098471615,
      -2.5506041745208514, -2.5522347836030552, -2.5531718742939336,
      -2.553414710038779, -2.5529627809090791, -2.5518158038853809,
      -2.5499737230529527, -2.5474367097421933, -2.544205162585798,
      -2.5402797074742773, -2.5356611974631766, -2.53035071258689,
      -2.5243495595819851, -2.5176592715605661, -2.5102816075805778,
      -2.5022185521400933, -2.4934723146142734, -2.4840453285902511,
      -2.4739402511268436, -2.4631599619549469, -2.4517075625798572,
      -2.4395863753175724, -2.4267999422556197, -2.4133520241132675,
      -2.3992465990675296, -2.3844878614885276, -2.3690802205662447,
      -2.3530282988963203, -2.3363369309929327, -2.3190111617070235,
      -2.3010562446069418, -2.2824776402340277, -2.2632810143013034,
      -2.2434722358978121, -2.2230573754928735, -2.2020427029479732,
      -2.1804346854862677, -2.1582399854904026, -2.135465458340402,
      -2.11211815012531, -2.0882052952721053, -2.063734314201676,
      -2.0387128108113375, -2.0131485699057858, -1.9870495546620828,
      -1.9604239039438893, -1.9332799295579433, -1.9056261135022725,
      -1.877471105053703, -1.8488237179226934, -1.8196929273404272,
      -1.7900878669264313, -1.7600178256589036, -1.7294922447761576,
      -1.6985207145745613, -1.6671129712041084, -1.6352788933070912,
      -1.6030284987182739, -1.5703719411470198, -1.5373195066779139,
      -1.5038816102955863, -1.4700687923645852, -1.4358917150556678,
      -1.4013611587905759, -1.3664880185273198, -1.3312833000410036,
      -1.2957581163045626, -1.2599236836305974, -1.2237913178463604,
      -1.1873724305410258, -1.1506785251254614, -1.1137211929403337,
      -1.0765121092989489, -1.0390630295259218, -1.0013857850265309,
      -0.96349227917559122, -0.92539448328603258, -0.88710443255123006,
      -0.84863422194336324, -0.80999600210967593, -0.77120197523047673,
      -0.73226439083246608, -0.69319554159935992, -0.65400775928567145,
      -0.61471341044799988, -0.57532489219381922, -0.53585462798702055,
      -0.49631506341015713, -0.45671866198611327, -0.41707790081706958,
      -0.37740526633438215, -0.33771325014684994, -0.29801434470356292,
      -0.25832103901960995, -0.21864581441559028, -0.17900114028966232,
      -0.13939946986336774, -0.099853235877393948, -0.060374846379453069,
      -0.020976680512941218, 0.018328915729404597, 0.057529633753218408,
      0.0966132065578183, 0.13556741287175389, 0.17438008135905275,
      0.21303909478832211, 0.251532394192738, 0.2898479829446971,
      0.32797393081395876, 0.36589837815391385, 0.40360953989628551,
      0.44109570953301086, 0.47834526317053117, 0.51534666345384028,
      0.55208846357202734, 0.58855931116545, 0.62474795205092137,
      0.66064323420838311, 0.69623411161986826, 0.73150964791688811,
      0.76645902017720668, 0.80107152258839387, 0.83533657012736429,
      0.86924370220135738, 0.9027825861227271, 0.93594302068542357,
      0.96871493965330191, 1.0010884151808388, 1.0330536611697247,
      1.0646010366267893, 1.0957210489492757, 1.1264043571322508,
      1.1566417749872573, 1.1864242741966211, 1.215742987450467,
      1.24458921144716, 1.272954409790366, 1.300830215981702, 1.3282084361996729,
      1.3550810520782082, 1.3814402234634333, 1.4072782909921833,
      1.4325877787613823, 1.4573613968566579, 1.4815920437555956,
      1.5052728087792111, 1.5283969743813597, 1.5509580184443992,
      1.5729496165113657, 1.5943656438072835, 1.6152001773667835,
      1.6354474980485161, 1.655102092392515, 1.6741586544952971,
      1.6926120877824551, 1.7104575066781602, 1.7276902382446224,
      1.7443058237856228, 1.760300020249643, 1.7756688016355093,
      1.7904083603773817, 1.8045151085417039, 1.8179856790089377,
      1.8308169265825942, 1.8430059289907075, 1.854549987825916,
      1.8654466294160907, 1.8756936056161533, 1.8852888944843285,
      1.8942307009107389, 1.9025174571924615, 1.9101478234660283,
      1.9171206881195872, 1.9234351680859763, 1.9290906090358684,
      1.9340865855927671, 1.9384229013736678, 1.9420995889319583,
      1.9451169096963121, 1.9474753538199745, 1.9491756398883191,
      1.950218714607123, 1.9506057523858782, 1.9503381548114678,
      1.9494175501184319, 1.9478457925326818, 1.945624961510267,
      1.9427573609317959, 1.9392455182382218, 1.93509218345905,
      1.9303003281462083, 1.9248731442456917, 1.9188140429244598,
      1.9121266532846339, 1.9048148209999911, 1.8968826068994986,
      1.8883342854335616, 1.8791743431227506, 1.8694074769188713,
      1.8590385924328274, 1.848072802146463, 1.8365154235539767,
      1.8243719772116029, 1.8116481847119883, 1.7983499666201643,
      1.7844834402860883, 1.770054917591448, 1.7550709027500038,
      1.7395380898933184, 1.723463360585116, 1.7068537814030789,
      1.6897166013746967, 1.672059249327349, 1.6538893312109217,
      1.6352146273325019, 1.6160430895498614, 1.5963828384586,
      1.5762421604115897, 1.5556295044944592, 1.5345534795408553,
      1.5130228510356047, 1.4910465379355469, 1.4686336094383836,
      1.4457932817560626, 1.4225349147884478, 1.3988680087446186,
      1.3748022007759626, 1.3503472614612722, 1.3255130913009676,
      1.3003097171908533, 1.2747472888110927, 1.2488360749958256,
      1.2225864600226632, 1.1960089399021772, 1.1691141186054799,
      1.1419127042811499, 1.1144155054194014, 1.08663342693661,
      1.0585774663028686, 1.03025870959893, 1.0016883275400115,
      0.97287757147794662, 0.94383776935495556, 0.91458032165041014,
      0.88511669733008447, 0.85545842972234043, 0.82561711236172874,
      0.79560439486015166, 0.76543197873357416, 0.73511161323650442,
      0.70465509114273461, 0.67407424449636755, 0.64338094041163629,
      0.6125870768056394, 0.58170457815358145, 0.55074539125107458,
      0.51972148086450276, 0.48864482549579247, 0.45752741311579781,
      0.42638123682466689, 0.395218290622515, 0.36405056507039735,
      0.33289004297420588, 0.30174869518118835, 0.270638476249317,
      0.23957132013029359, 0.20855913597961795, 0.17761380384063541,
      0.14674717039004673, 0.11597104475125322, 0.08529719419195407,
      0.054737339967272008, 0.024303153111663891, -0.0059937497687013895,
      -0.036141810590695982, -0.066129533995430728, -0.095945491446482831,
      -0.12557832530985236, -0.15501675294322445, -0.18424957070163178,
      -0.21326565797699873, -0.2420539811936909, -0.27060359776456844,
      -0.29890365996322416, -0.32694341883383748, -0.35471222809809388,
      -0.38219954791753036, -0.40939494868514653, -0.43628811475250157,
      -0.46286884815292734, -0.489127072278877, -0.51505283544169822,
      -0.54063631448416682, -0.565867818316269, -0.590737791360009,
      -0.61523681699620558, -0.63935562096874965, -0.66308507470691747,
      -0.68641619857960157, -0.7093401651539778, -0.73184830238218379,
      -0.75393209668959071, -0.77558319605794945, -0.79679341303154938,
      -0.817554727649534, -0.83785929037309315, -0.85769942490655549,
      -0.87706763092373, -0.89595658681139134, -0.91435915231811726,
      -0.93226837112190863, -0.94967747335781916, -0.96657987803222389,
      -0.9829691954183819, -0.9988392294161228, -1.0141839797555197,
      -1.0289976441538615, -1.0432746204622645, -1.0570095086931854,
      -1.070197112953742, -1.0828324433821654, -1.0949107179627919,
      -1.1064273642145963, -1.1173780209231101, -1.1277585397290657,
      -1.1375649866083226, -1.1467936433607269, -1.1554410089598617,
      -1.1635038008481298, -1.1709789561613255, -1.1778636328321626,
      -1.1841552106782494, -1.189851292379746, -1.1949497043634527,
      -1.1994484976380295, -1.2033459485244993, -1.206640559327562,
      -1.2093310589159967, -1.211416403206971, -1.2128957756015368,
      -1.2137685873262603, -1.2140344776845853, -1.2136933142221049,
      -1.2127451928415318, -1.2111904378204157, -1.2090296017302404,
      -1.2062634652929529, -1.2028930371397233, -1.1989195535330162,
      -1.19434447795141, -1.1891695006189202, -1.18339653797655,
      -1.1770277320103328, -1.1700654495570124, -1.1625122815266626,
      -1.1543710420041504, -1.145644767306748, -1.1363367149630965,
      -1.1264503625749631, -1.1159894066526317, -1.1049577613426091,
      -1.0933595570611823, -1.0811991391045419, -1.068481066132694,
      -1.0552101085748939, -1.0413912470130446, -1.0270296704540254,
      -1.0121307744859636, -0.99670015942982426, -0.980743628418113,
      -0.96426718533373479, -0.9472770327268295, -0.92977956964894237,
      -0.91178138943219245, -0.89328927738583885, -0.87431020839384621,
      -0.85485134449436406, -0.83492003236381285, -0.81452380077427011,
      -0.79367035790259854, -0.77236758863039578, -0.75062355181263407,
      -0.72844647740936019, -0.70584476362437043, -0.68282697391252656,
      -0.659401834000228, -0.63557822878713111, -0.6113651992107052,
      -0.58677193910591374, -0.56180779191480434, -0.53648224740662254,
      -0.51080493829610529, -0.48478563691300075, -0.45843425171850782,
      -0.43176082373893121, -0.40477552308628179, -0.37748864535587762,
      -0.34991060796492524, -0.32205194645086721, -0.29392331076406669,
      -0.26553546147622686, -0.23689926598538152, -0.20802569464175469,
      -0.17892581684914691, -0.14961079716547573, -0.12009189130802156,
      -0.090380442175909945, -0.060487875807314809, -0.030425697311598592,
      -0.00020548680369770084, 0.030161104744292625, 0.060662359670519875,
      0.091286497732603056, 0.1220216803404837, 0.15285601480730984,
      0.18377755853671965, 0.21477432329988125, 0.24583427952636946,
      0.27694536060923514, 0.30809546719080916, 0.33927247148930917,
      0.37046422163040893, 0.40165854601511031, 0.4328432576778044,
      0.46400615863419914, 0.49513504424409049, 0.52621770754983188,
      0.55724194376814773, 0.588195554586414, 0.61906635251521225,
      0.64984216532396055, 0.68051084037071341, 0.71106024901710219,
      0.741478290952923, 0.77175289856838114, 0.80187204127963,
      0.83182372988030828, 0.86159602086192277, 0.89117702071737592,
      0.92055489025997828, 0.94971784883328214, 0.97865417863239468,
      1.0073522289179329, 1.0358004202411424, 1.0639872486348683,
      1.0919012897459457, 1.1195312030357552, 1.1468657358679686,
      1.1738937276068395, 1.2006041136614596, 1.2269859294965253,
      1.2530283146553993, 1.278720516727746, 1.3040518952434632,
      1.3290119255494066, 1.3535902026812787, 1.3777764451678474,
      1.4015604987933119, 1.4249323403109968, 1.4478820811252349,
      1.4703999709368107, 1.4924764013221159, 1.5141019092763195,
      1.5352671807001381, 1.5559630538259481, 1.5761805226433674,
      1.5959107402080903, 1.615145021922952, 1.6338748487921586,
      1.6520918705504464, 1.669787908797975, 1.6869549600884883,
      1.7035851988806592, 1.719670980468508, 1.7352048439012906,
      1.7501795147465782, 1.7645879078751316, 1.7784231301485351,
      1.791678482969205, 1.8043474649027331, 1.8164237741492226,
      1.8279013109407605, 1.8387741798984423, 1.849036692277733,
      1.8586833682352679, 1.8677089389319232, 1.8761083485458725,
      1.8838767563445753, 1.8910095385566665, 1.8975022902057674,
      1.9033508268934951, 1.9085511864394213, 1.9130996306002297,
      1.9169926465108837, 1.9202269481184162, 1.9227994776841695,
      1.9247074069964865, 1.9259481385764687, 1.9265193068546926,
      1.9264187792503962, 1.9256446571426078, 1.9241952767415516,
      1.9220692098954184, 1.9192652649175654, 1.9157824871688676,
      1.9116201595898683, 1.9067778033283429, 1.9012551780353677,
      1.8950522822170004, 1.8881693535040391, 1.8806068687966206,
      1.8723655443470777, 1.8634463356990381, 1.8538504377167093,
      1.84357928436138, 1.8326345483366759, 1.8210181408616855,
      1.8087322113244713, 1.7957791465849797, 1.7821615704497686,
      1.7678823431519708, 1.7529445604572853, 1.7373515528033217,
      1.7211068844583932, 1.7042143525775741, 1.686677986015475,
      1.6685020441920495, 1.6496910159110718, 1.630249618008252,
      1.6101827939158497, 1.5894957122076343, 1.5681937651149782,
      1.5462825668083431, 1.5237679516783735, 1.5006559725909128,
      1.4769528990424923, 1.4526652151303863, 1.4277996175757839,
      1.402363013702842, 1.376362519209025, 1.349805455895865,
      1.3226993493298094, 1.2950519266744926, 1.2668711140162374,
      1.2381650337701042, 1.2089420024077016, 1.1792105276116878,
      1.1489793054098496, 1.1182572175161736, 1.0870533286049375,
      1.0553768831880974, 1.02323730261062, 0.99064418211676109,
      0.95760728773476123, 0.92413655300762365, 0.89024207573774283,
      0.85593411490243065, 0.82122308710366831, 0.78611956315897047,
      0.75063426476881734, 0.71477806094707852, 0.67856196439275762,
      0.641997127855423, 0.60509484064422869, 0.56786652481200062,
      0.53032373122987608, 0.492478135908258, 0.45434153630328883,
      0.41592584713749714, 0.37724309649005111, 0.33830542202331781,
      0.29912506680698864, 0.25971437520027618, 0.22008578877353216,
      0.18025184232669905, 0.1402251595725964, 0.10001844889679469,
      0.059644499229084706, 0.019116175759981553, -0.021553584441392118,
      -0.0623517767135775, -0.10326533301158401, -0.14428112646935085,
      -0.18538597574652582, -0.22656664939450438, -0.26780987028055,
      -0.30910232012141931, -0.35043064396973106, -0.39178145454886459,
      -0.43314133682250489, -0.47449685259279739, -0.51583454504723336,
      -0.55714094301717765, -0.59840256576745465, -0.63960592761976,
      -0.68073754217082072, -0.72178392703697181, -0.76273160851947863,
      -0.80356712605301239, -0.84427703660104458, -0.88484791937587182,
      -0.92526638044766429, -0.96551905712206454, -1.0055926224878269,
      -1.045473790053697, -1.0851493181890834, -1.1246060144819565,
      -1.1638307404362251, -1.2028104158791193, -1.2415320232865998,
      -1.2799826123072673, -1.3181493042230767, -1.3560192962880979,
      -1.3935798659745555, -1.4308183754092012, -1.4677222758086674,
      -1.5042791116292684, -1.5404765246879872, -1.5763022586436473,
      -1.6117441631183904, -1.6467901977010997, -1.681428436220225,
      -1.7156470708546678, -1.7494344161090454, -1.782778912753429,
      -1.8156691319201665, -1.8480937790038896, -1.8800416975418965,
      -1.9115018729788011, -1.9424634365087536, -1.9729156689413971,
      -2.0028480041676437, -2.0322500329341233, -2.0611115065155556,
      -2.0894223401277112, -2.11717261640746, -2.1443525889789719,
      -2.1709526857880763, -2.1969635122851963, -2.2223758548410162,
      -2.2471806839658806, -2.2713691573928982, -2.2949326230825262,
      -2.3178626223752992, -2.3401508929694503, -2.3617893716599729,
      -2.3827701972446333, -2.4030857133376284, -2.4227284710299739,
      -2.4416912314374395, -2.4599669683390917, -2.4775488706706996,
      -2.4944303448779603, -2.5106050172686252, -2.5260667363292644,
      -2.540809574911425, -2.5548278322816103, -2.5681160362264444,
      -2.5806689450271612, -2.5924815493488542, -2.6035490740295986,
      -2.6138669798354552, -2.623430965154439, -2.6322369675153574,
      -2.6402811651206082, -2.6475599782944679, -2.6540700707820357,
      -2.6598083510372703, -2.6647719734061686, -2.6689583391885132,
      -2.6723650976940876, -2.6749901471629953, -2.676831635613611,
      -2.6778879616111171, -2.6781577749419614, -2.6776399772409181,
      -2.6763337224826871, -2.6742384174078233, -2.6713537219148513,
      -2.6676795492925924, -2.6632160663718234, -2.657963693683099,
      -2.6519231054249635, -2.6450952294067882, -2.6374812468835529,
      -2.6290825923029342, -2.6199009530210042, -2.6099382688181127,
      -2.5991967314657471, -2.5876787841562217, -2.5753871207399577,
      -2.5623246850839796, -2.5484946702680076, -2.533900517490316,
      -2.5185459152144967, -2.5024347981512629, -2.4855713459549484,
      -2.4679599820133151, -2.4496053721366118, -2.4305124232233375,
      -2.4106862816972177, -2.3901323319116634, -2.368856194598568,
      -2.3468637251029434, -2.3241610115360851, -2.3007543729417925,
      -2.2766503573710559, -2.2518557397976351, -2.2263775200203968,
      -2.2002229204603734, -2.1733993839729644, -2.1459145714553887,
      -2.1177763593833507, -2.08899283750128, -2.0595723062156508,
      -2.0295232738296907, -1.9988544539716639, -1.9675747630054785,
      -1.9356933169020509, -1.9032194284133348, -1.8701626043941166,
      -1.8365325425174497, -1.8023391281463959, -1.7675924313826519,
      -1.7323027038330254, -1.6964803751949449, -1.6601360500296216,
      -1.623280504395054, -1.585924682386342, -1.5480796925904758,
      -1.509756804523098, -1.4709674451843771, -1.4317231952398617,
      -1.3920357852954357, -1.3519170922494839, -1.311379135458596,
      -1.2704340727859913, -1.2290941967501174, -1.1873719306851802,
      -1.1452798246915608, -1.1028305514241179, -1.0600369021631977,
      -1.0169117829710048, -0.97346821005300643, -0.92971930573120021,
      -0.885678294503297, -0.84135849849846367, -0.79677333319985755,
      -0.75193630317385507, -0.70686099786391576, -0.66156108702669936,
      -0.61605031632319485, -0.57034250305569967, -0.5244515316267685,
      -0.478391348971662, -0.43217596014786064, -0.38581942395361213,
      -0.33933584820107943, -0.29273938520447551, -0.24604422727333955,
      -0.199264602170983, -0.15241476845077365, -0.10550901079952271,
      -0.058561635665545092, -0.0115869665250681, 0.035400660946050745,
      0.082386903221078431, 0.12935741340507542, 0.17629784630059195,
      0.22319386287387641, 0.27003113457971262, 0.31679534820102229,
      0.3634722106085031, 0.41004745319520347, 0.45650683633173678,
      0.50283615419556249, 0.5490212392670476, 0.595047966819408,
      0.64090225951464441, 0.68657009196222774, 0.73203749520755379,
      0.77729056110013561, 0.82231544694100855, 0.8670983799243891,
      0.91162566141622381, 0.955883671394762, 0.999858872978542,
      1.043537816623108, 1.0869071444081122, 1.1299535943750345,
      1.1726640048515453, 1.2150253186665443, 1.2570245869933083,
      1.2986489739868989, 1.3398857607783208, 1.3807223491789939,
      1.421146266028436, 1.4611451672096631, 1.5007068415493583,
      1.5398192145035123, 1.5784703521956049, 1.6166484653271667,
      1.6543419127232804, 1.6915392050931981, 1.728229008779806,
      1.7644001493062043, 1.8000416148340077, 1.8351425598167328,
      1.8696923083702819, 1.9036803576221357, 1.9370963810867194,
      1.9699302319026921, 2.0021719461466785, 2.0338117457861284,
      2.0648400418158737, 2.0952474375258547, 2.1250247311547188,
      2.1541629187832165, 2.1826531974548891, 2.2104869677059686,
      2.2376558362125909, 2.2641516185496298, 2.2899663417584191,
      2.3150922467414121, 2.3395217906530985, 2.3632476493492152,
      2.3862627195805444, 2.4085601212439816, 2.4301331994220816,
      2.4509755264763258, 2.47108090409964, 2.490443365039777,
      2.5090571750211379, 2.5269168345373121, 2.5440170804357218,
      2.5603528874558181, 2.5759194698822259, 2.5907122829017522,
      2.6047270238794829, 2.6179596337437276, 2.6304062981120651,
      2.6420634484557763, 2.6529277630170949, 2.6629961678359693,
      2.6722658376974784, 2.6807341967234364, 2.6883989191626743,
      2.6952579300844079, 2.7013094058307479, 2.7065517744535632,
      2.7109837161332031, 2.714604163480316, 2.7174123016834453,
      2.71940756866607, 2.7205896551564295, 2.7209585045685545,
      2.7205143129528424, 2.7192575287537633, 2.71718885249258,
      2.7143092364686874, 2.7106198842481488, 2.7061222501318976,
      2.7008180385522156, 2.694709203375337, 2.6877979471047229,
      2.680086720041722, 2.6715782193179396, 2.6622753879040091,
      2.6521814135135031, 2.6412997273179704, 2.6296340028210134,
      2.6171881545193347, 2.6039663363659482, 2.5899729403578982,
      2.5752125949697331, 2.5596901634862825, 2.5434107423027341,
      2.5263796590924685, 2.5086024709876011, 2.4900849625662445,
      2.47083314385593, 2.4508532483198309, 2.430151730596632,
      2.4087352643247915, 2.3866107397870548, 2.3637852616055115,
      2.34026614628412, 2.3160609196050004, 2.291177314232383,
      2.2656232669916272, 2.2394069160337349, 2.2125365982429339,
      2.1850208464954473, 2.156868386415463, 2.1280881336306132,
      2.0986891909633769, 2.0686808450360634, 2.0380725632269439,
      2.0068739905355386, 1.97509494636686, 1.9427454212138067,
      1.9098355732491534, 1.8763757249823887, 1.8423763598141856,
      1.8078481184989057, 1.7728017956095843, 1.7372483360206952,
      1.701198831148379, 1.6646645152720025, 1.6276567619222706,
      1.5901870800342339, 1.5522671100690719, 1.5139086202361252,
      1.4751235026610225, 1.4359237694424349, 1.3963215484902944,
      1.3563290796743521, 1.3159587110605662, 1.2752228943776749,
      1.2341341810691837, 1.1927052184571494, 1.1509487453458389,
      1.1088775877968651, 1.066504655030021, 1.0238429353413565,
      0.98090549163888241, 0.93770545721038934, 0.89425603158246014,
      0.85057047616948356, 0.80666210987362985, 0.76254430478674373,
      0.71823048199625572, 0.67373410706843873, 0.62906868575191166,
      0.58424775959368258, 0.53928490159324038, 0.49419371181399441,
      0.44898781286937095, 0.40368084580173241, 0.35828646558015642,
      0.31281833646976231, 0.26729012792609547, 0.22171551035558987,
      0.17610815029498836, 0.13048170621272892, 0.084849824409174018,
      0.039226134389215024, -0.0063757554957467851, -0.051942262281235996,
      -0.0974598326588437, -0.14291494739651384, -0.18829412557983927,
      -0.23358392885295895, -0.27877096567798282, -0.32384189562238563,
      -0.36878343356606347, -0.41358235371542257, -0.45822549393199496,
      -0.502699759881641, -0.54699212902003025, -0.59108965469112518,
      -0.6349794703031344, -0.67864879323284222, -0.72208492872348085,
      -0.76527527395206485, -0.80820732202283085, -0.850868665746947,
      -0.89324700121839373, -0.9353301320836982, -0.97710597317658276,
      -1.0185625538955851, -1.0596880221704579, -1.1004706481062234,
      -1.1408988275470455, -1.1809610854460668, -1.2206460794778866,
      -1.2599426035673684, -1.2988395911324779, -1.3373261184491176,
      -1.3753914080353273, -1.4130248318273222, -1.4502159142640945,
      -1.4869543355754617, -1.523229934803711, -1.5590327127550929,
      -1.5943528349888332, -1.6291806347685358, -1.6635066158841161,
      -1.6973214553073908, -1.7306160059883093, -1.763381299669313,
      -1.7956085492742684, -1.8272891513110654, -1.8584146887245141,
      -1.8889769330896768, -1.9189678467785485, -1.9483795854203427,
      -1.977204500123817, -2.0054351395657792, -2.0330642519007283,
      -2.0600847869160215, -2.0864898979647233, -2.1122729437154493,
      -2.1374274899633519, -2.1619473113788494, -2.1858263931360664,
      -2.2090589324017889, -2.2316393398803678, -2.25356224124976,
      -2.27482247850692, -2.2954151111579768, -2.3153354174916148,
      -2.3345788957202962, -2.3531412649006489, -2.371018466007619,
      -2.3882066628539875, -2.4047022428385425, -2.4205018176403681,
      -2.4356022240304438, -2.4500005244399961, -2.463694007312053,
      -2.4766801876805968, -2.4889568075832011, -2.5005218362174015,
      -2.5113734701854833, -2.5215101336907892, -2.5309304785477895,
      -2.5396333841721144, -2.5476179574636091, -2.5548835326911727,
      -2.5614296712390647, -2.5672561611956848, -2.5723630170634553,
      -2.5767504792913867, -2.5804190136463339, -2.5833693106548368,
      -2.5856022849003448, -2.5871190742255958, -2.5879210389702081,
      -2.5880097609793919, -2.587387042620847, -2.586054905791404,
      -2.58401559073494, -2.5812715548626923, -2.5778254714660096,
      -2.5736802283888847, -2.5688389266221847, -2.5633048788288293,
      -2.5570816077914427, -2.5501728447575562, -2.5425825278180438,
      -2.5343148001662965, -2.5253740082108771, -2.515764699764329,
      -2.5054916220935675, -2.494559719843187, -2.4829741330965551,
      -2.4707401951735846, -2.457863430381459, -2.4443495518764755,
      -2.4302044593103522, -2.41543423641032, -2.4000451486256749,
      -2.3840436406634034, -2.3674363338714204, -2.3502300236484142,
      -2.3324316768773388, -2.3140484292710419, -2.2950875824199124,
      -2.2755566010896775, -2.255463110519921, -2.234814893346635,
      -2.2136198867099139, -2.1918861792661692, -2.1696220081416713,
      -2.1468357559076625, -2.1235359473975493, -2.0997312465521949,
      -2.0754304532572876, -2.0506425000211594, -2.0253764487427648,
      -1.9996414874363415, -1.9734469267911146, -1.9468021968524605,
      -1.9197168435142373, -1.8922005251438017, -1.8642630091176569,
      -1.8359141681448978, -1.8071639769424326, -1.7780225085432246,
      -1.7484999306372635, -1.7186065021119334, -1.6883525693393044,
      -1.657748562400376, -1.6268049915011531, -1.59553244340589,
      -1.5639415774785337, -1.5320431219668189, -1.4998478703879368,
      -1.4673666776821672, -1.4346104564168933, -1.4015901730214193,
      -1.3683168439534057, -1.3348015319345437, -1.3010553420959081,
      -1.2670894180986152, -1.2329149384678479, -1.1985431126272184,
      -1.1639851770613066, -1.1292523915283699, -1.0943560352035375,
      -1.0593074029054521, -1.024117801142665, -0.98879854441837778,
      -0.95336095137126076, -0.91781634090351849, -0.88217602843522969,
      -0.846451322150422, -0.81065351913527994, -0.77479390156651162,
      -0.7388837331887268, -0.70293425538925758, -0.66695668339420733,
      -0.63096220275882475, -0.59496196564737969, -0.55896708706464426,
      -0.5229886412432676, -0.48703765807991334, -0.45112511957804263,
      -0.41526195610654731, -0.37945904291050969, -0.34372719677011232,
      -0.30807717229677889, -0.27251965861656752, -0.23706527579440645,
      -0.2017245714970016, -0.1665080177979541, -0.1314260075444024,
      -0.096488851336764381, -0.061706774154925079, -0.02708991204734059,
      0.0073516908697392374, 0.041608085613247407, 0.075669421517067736,
      0.10952594925187864, 0.1431680236890806, 0.17658610709175115,
      0.20977077194125784, 0.24271270376589565, 0.27540270411062251,
      0.3078316931840418, 0.33999071264982045, 0.37187092838326347,
      0.40346363295399063, 0.43476024834602039, 0.46575232855868726,
      0.49643156182383968, 0.52678977322430109, 0.55681892710308833,
      0.58651112930733362, 0.6158586294565136, 0.64485382313950446,
      0.67348925414464678, 0.7017576164271605, 0.72965175624554623,
      0.75716467415001765, 0.78428952683881625, 0.81101962897556867,
      0.8373484551177991, 0.86326964146235707, 0.88877698728219945,
      0.91386445674624672, 0.93852618050202841, 0.96275645705940882,
      0.986549754175149, 1.0099007103570805, 1.0328041361424176,
      1.055255015124146, 1.0772485053323517, 1.0987799403647702,
      1.1198448302674486, 1.1404388625536075, 1.1605579032208737,
      1.1801979974144825, 1.1993553703494342, 1.2180264280420776,
      1.2362077577466255, 1.2538961287897932, 1.2710884928949278,
      1.2877819846654979, 1.3039739221254953, 1.319661806802414,
      1.3348433240310453, 1.3495163432805835, 1.363678918164031,
      1.3773292863806312, 1.3904658698538592, 1.403087274636291,
      1.4151922906702943, 1.4267798916187893, 1.4378492346309697,
      1.4483996599596403, 1.458430690503052, 1.4679420313330007,
      1.4769335692780365, 1.4854053722846468, 1.4933576885742912,
      1.500790946084861, 1.5077057516952517, 1.514102890319956,
      1.5199833239285634, 1.5253481906386082, 1.5301988037483942,
      1.5345366504668883, 1.5383633909028078, 1.5416808567959124,
      1.5444910502212024, 1.5467961422652856, 1.5485984716539667,
      1.5499005433711852, 1.550705026963983, 1.5510147551229367,
      1.550832722078743, 1.550162081875067, 1.5490061466708747,
      1.5473683849546502, 1.5452524197768265, 1.54266202672455,
      1.5396011320984555, 1.5360738110443244, 1.5320842853339782,
      1.5276369213274681, 1.522736227934284, 1.5173868543747653,
      1.5115935880343645, 1.505361352168787, 1.498695203533472,
      1.4916003301813181, 1.4840820490258988, 1.4761458033302792,
      1.4677971603344671, 1.4590418087591184, 1.4498855562170825,
      1.4403343266872262, 1.4303941578675594, 1.4200711984813705,
      1.4093717057040485, 1.3983020424302459, 1.386868674455934,
      1.3750781677466615, 1.3629371856719237, 1.3504524861280298,
      1.3376309186841635, 1.3244794217388005, 1.3110050195830893,
      1.2972148194546063, 1.2831160085952638, 1.2687158513367665,
      1.254021686035554, 1.2390409220372336, 1.2237810367427517,
      1.2082495724852726, 1.1924541334774001, 1.1764023827743275,
      1.1601020391455661, 1.1435608739663241, 1.1267867081304912,
      1.1097874089559152, 1.0925708869892001, 1.0751450928903519,
      1.0575180143091345, 1.0396976727223173, 1.0216921203060496,
      1.0035094367509936, 0.98515772609262253, 0.96664511359941285,
      0.94797974263986673, 0.92916977145589075, 0.91022337002981124,
      0.89114871700605647, 0.87195399649079686, 0.85264739494165553,
      0.83323709807209867, 0.81373128765871561, 0.79413813853047255,
      0.77446581546517468, 0.754722470033308, 0.7349162376197077,
      0.71505523433660068, 0.69514755398905781, 0.67520126509682032,
      0.65522440783919111, 0.63522499112058994, 0.61521098959662823,
      0.59519034073032573, 0.57517094194383922, 0.55516064763507933,
      0.53516726634397249, 0.5151985579636752, 0.49526223087563742,
      0.47536593918332859, 0.45551727995642721, 0.43572379052283183,
      0.41599294575313583, 0.39633215537961408, 0.37674876142148012,
      0.3572500355730916, 0.33784317659003055, 0.31853530781940104,
      0.29933347470636418, 0.28024464230837115, 0.26127569293267205,
      0.24243342369391035, 0.2237245442227121, 0.20515567441093696,
      0.18673334206077122, 0.16846398072693028, 0.15035392757265656,
      0.13240942119305826, 0.1146365995696782, 0.097041498027810438,
      0.079630047237214424, 0.062408071275224464, 0.045381285722486807,
      0.028555295866201622, 0.011935594807638538, -0.0044724382486372848,
      -0.020663539625487722, -0.036632562938621833, -0.052374480638553163,
      -0.067884385546171433, -0.083157492399291544, -0.098189139265512246,
      -0.112974788927785, -0.12751003025936036, -0.14179057948427468,
      -0.15581228141715087, -0.16957111067639974, -0.18306317273454029,
      -0.19628470503630649, -0.20923207805390895, -0.22190179616740691,
      -0.23429049859521545, -0.24639496028660249, -0.25821209267474771,
      -0.26973894438732127, -0.28097270197758917, -0.29191069054136581,
      -0.30255037422635778, -0.31288935681768154, -0.322925382160942,
      -0.33265633451630433, -0.34208023896310813, -0.35119526163919695,
      -0.3599997099723744, -0.36849203285229071, -0.37667082073868208,
      -0.3845348057352731, -0.39208286152442573, -0.39931400336529982,
      -0.4062273879701549, -0.41282231329433211, -0.41909821835719024,
      -0.42505468289934656, -0.43069142707465535, -0.43600831106273719,
      -0.44100533458854185, -0.44568263640348382, -0.45004049376380628,
      -0.45407932181386884, -0.4577996728499984, -0.46120223563652374,
      -0.46428783463172435, -0.46705742919374665, -0.46951211259853903,
      -0.47165311112653574, -0.47348178318864304, -0.47499961814747382,
      -0.47620823525831135, -0.4771093825839603, -0.4777049357540733,
      -0.477996896752229, -0.47798739258439327, -0.47767867397179525,
      -0.47707311399676544, -0.47617320662276341, -0.47498156524718804,
      -0.47350092115540993, -0.47173412194736264, -0.46968412997896236,
      -0.46735402070232407, -0.46474698088253946, -0.46186630692606634,
      -0.45871540314790454, -0.45529777984944786, -0.45161705150011655,
      -0.44767693486326926, -0.44348124706663156, -0.43903390356434674,
      -0.4343389161764436, -0.42940039110145578, -0.42422252664266574,
      -0.41880961129560762, -0.41316602160891952, -0.40729621977821406,
      -0.4012047516682884, -0.39489624452106475, -0.38837540458279068,
      -0.38164701494420167, -0.37471593316101315, -0.36758708889640829,
      -0.3602654815387949, -0.35275617781884, -0.34506430942772603,
      -0.33719507049724634, -0.32915371520837811, -0.3209455552716573,
      -0.312575957353525, -0.30405034068425135, -0.29537417450377151,
      -0.28655297539316227, -0.27759230478431357, -0.26849776639360518,
      -0.25927500355945737, -0.24992969671507859, -0.24046756069778616,
      -0.23089434215696139, -0.22121581691903813, -0.21143778729527418,
      -0.20156607954347913, -0.19160654108064382, -0.18156503785116793,
      -0.17144745174859455, -0.16125967787215095, -0.15100762187558087,
      -0.14069719730225883, -0.13033432289922264, -0.11992491999735488,
      -0.10947490985569419, -0.098990210942732249, -0.088476736307966319,
      -0.077940390971345808, -0.067387069296866733, -0.056822652297752567,
      -0.046253005032694958, -0.035683974085045575, -0.025121384893412292,
      -0.014571039142486119, -0.0040387122586389183, 0.0064698491675220116,
      0.0169489299318846, 0.027392848709340584, 0.037795960592392736,
      0.048152659533620329, 0.058457380835988254, 0.06870460363184458,
      0.078888853213280055, 0.08900470347889318, 0.099046779334907353,
      0.10900975900857655, 0.11888837638363546, 0.12867742329725759,
      0.13837175180664868, 0.14796627641200971, 0.15745597629624661,
      0.16683589752709221, 0.17610115515237737, 0.18524693531249711,
      0.19426849738297805, 0.20316117601838229, 0.21192038313578751,
      0.22054160989882551, 0.22902042866868938, 0.237352494946313,
      0.24553354922015649, 0.25355941875958005, 0.26142601947388711,
      0.26912935764734652, 0.27666553162498697, 0.28403073351391928,
      0.291221250804953, 0.29823346797132205, 0.30506386799404411,
      0.31170903387940568, 0.318165650122868, 0.32443050408782759,
      0.33050048742101845, 0.3363725973504354, 0.34204393793481369,
      0.34751172134418795, 0.35277326901396583, 0.3578260127642327,
      0.36266749589670222, 0.36729537424877118, 0.37170741716553879,
      0.37590150840873149, 0.37987564708576427, 0.38362794848202914,
      0.38715664483044832, 0.39046008604987359, 0.39353674042957454,
      0.39638519527653304, 0.399004157478639, 0.401392454048039,
      0.40354903259544667, 0.40547296172590075, 0.40716343146509121,
      0.4086197535493275, 0.40984136168092944, 0.41082781176575311,
      0.41157878205579462, 0.41209407328881109, 0.41237360870584694,
      0.41241743405863829, 0.41222571759926363, 0.41179874993914711,
      0.41113694388905536, 0.41024083428092845, 0.40911107767342159,
      0.40774845205151028, 0.40615385648314417, 0.40432831065752617,
      0.40227295442176242, 0.39998904728518941, 0.39747796783890127,
      0.39474121309319582, 0.39178039781319618, 0.38859725382480165,
      0.385193629208208, 0.38157148744612496, 0.37773290658129038,
      0.37368007826889432, 0.36941530677946877, 0.36494100801748919,
      0.36025970840195892, 0.3553740437434324, 0.35028675809846543,
      0.345000702520763, 0.33951883381956621, 0.33384421323225127,
      0.32798000505764041, 0.32192947526060439, 0.31569599003351745,
      0.30928301431740435, 0.302694110211345, 0.29593293543185439,
      0.28900324170800923, 0.2819088730837816, 0.27465376425337656,
      0.26724193877888086, 0.25967750731108324, 0.25196466581057769,
      0.24410769367545457, 0.23611095180732042, 0.22797888070026154,
      0.21971599849569448, 0.21132689894566048, 0.20281624940700227,
      0.19418878873742207, 0.18544932521480767, 0.17660273441467383,
      0.16765395700558208, 0.15860799658707408, 0.14946991745535446,
      0.14024484236930418, 0.13093795023400581, 0.12155447379890975,
      0.11209969739077226, 0.10257895449817891, 0.092997625362194788,
      0.083361134652352009, 0.073674949041538554, 0.063944574710819685,
      0.05417555488235308, 0.044373467384389853, 0.034543922143694852,
      0.024692558638906265, 0.014825043431199485, 0.0049470675489439123,
      -0.004935656086058165, -0.014817395123101523, -0.024692400410475907,
      -0.034554908662056585, -0.044399144983880978, -0.054219325490602092,
      -0.064009659969668758, -0.073764354433517212, -0.083477613802565964,
      -0.093143644553377633, -0.102756657300867, -0.11231086942731607,
      -0.12180050777886985, -0.13121981133677493, -0.14056303373945916,
      -0.14982444596023978, -0.15899833899769072, -0.16807902643468178,
      -0.17706084708636011, -0.18593816763857027, -0.19470538519747596,
      -0.2033569299090392, -0.21188726757438195, -0.22029090222032058,
      -0.22856237864022844, -0.23669628494983141, -0.24468725515981277,
      -0.252529971607751, -0.26021916759160074, -0.26774962983751849,
      -0.27511620081242211, -0.28231378134348067, -0.28933733304593723,
      -0.29618188062242806, -0.30284251433311421, -0.30931439237992414,
      -0.3155927431508635, -0.3216728676190001, -0.32755014163161639,
      -0.33322001809632462, -0.33867802929467311, -0.34391978903704323,
      -0.34894099484318714, -0.35373743016543907, -0.35830496638703874,
      -0.36263956492305716, -0.36673727931856809, -0.37059425722575812,
      -0.37420674241729868, -0.37757107665682904, -0.38068370162182508,
      -0.3835411608155313, -0.3861401013749598, -0.38847727585262948,
      -0.39054954388878793, -0.39235387405153027, -0.39388734544900111,
      -0.39514714926249261, -0.39613059047318183, -0.39683508928913291,
      -0.39725818265447554, -0.39739752577707155, -0.39725089341089104,
      -0.3968161812533697, -0.39609140731361825, -0.39507471306323166,
      -0.393764364732835, -0.3921587544625405, -0.39025640132807615,
      -0.38805595253361364, -0.38555618434682826, -0.38275600304746027,
      -0.37965444592504244, -0.37625068203874168, -0.37254401305754564,
      -0.36853387404335775, -0.36421983412417297, -0.35960159717631091,
      -0.35467900234907823, -0.34945202466602748, -0.34392077551730044,
      -0.3380855030449415, -0.33194659257330961, -0.32550456687154006,
      -0.3187600864468369, -0.31171394982378003, -0.30436709360039,
      -0.29672059254732341, -0.2887756597652224, -0.28053364657295132,
      -0.2719960424485533, -0.26316447495901085, -0.25404070952307262,
      -0.24462664921732666, -0.23492433445039207, -0.22493594263425531,
      -0.21466378779511949, -0.20411032005841231, -0.19327812519676907,
      -0.18216992402454141, -0.17078857174446949, -0.15913705732063096,
      -0.14721850270627662, -0.13503616204288843, -0.12259342081653606,
      -0.10989379495055544, -0.096940929885662427, -0.083738599495623553,
      -0.070290705042056034, -0.056601274125436626, -0.042674459394544333,
      -0.028514537383506674, -0.014125907252836602, 0.00048691061738096613,
      0.015319275952806514, 0.030366430022744872, 0.045623497155757309,
      0.061085486272596023, 0.076747292457327976, 0.092603698605359,
      0.10864937710296127, 0.12487889156261162, 0.1412866986144681,
      0.15786714972266375, 0.17461449307921384, 0.19152287550006911,
      0.20858634439070184, 0.22579884979502107, 0.24315424642464659,
      0.26064629575269593, 0.27826866815650231, 0.2960149451014652,
      0.31387862138078348, 0.33185310736373608, 0.34993173129606436,
      0.36810774163066767, 0.3863743094312414, 0.40472453080428905,
      0.42315142927789989, 0.755838641684454, 1.7174296493516938,
      2.679895915537859, 3.0138408094155977, 3.0321810389628738,
      3.0487211893541768, 3.0634141298592517, 3.0762140317229059,
      3.0870764666392145, 3.0959585042962474, 3.1028188090211, 3.107617735149248,
      3.1103174209313975, 3.1108818809817635, 3.1092770968628969,
      3.1054711057316946, 3.0994340870294672, 3.0911384467642513,
      3.0805588993322521, 3.0676725467999781, 3.0524589553694481,
      3.0349002289183007, 3.0149810794645382, 2.99268889431433,
      2.9680137999173319, 2.9409487220369419, 2.9114894423666446,
      2.8796346513649933, 2.845385996926419, 2.8087481292322733,
      2.769728741245773, 2.7283386049932923, 2.6845916034299826,
      2.6385047577044416, 2.5900982499753029, 2.5393954414602558,
      2.4864228857247568, 2.4312103371047407, 2.3737907542926546,
      2.3142002989163184, 2.2524783291968751, 2.1886673883790642,
      2.1228131882356847, 2.0549645875046259, 1.985173564946572,
      1.9134951875757942, 1.8399875735978404, 1.7647118501580004,
      1.6877321061155164, 1.6091153397188622, 1.5289314010455517,
      1.4472529296694712, 1.3641552873153786, 1.2797164853914851,
      1.1940171079194906, 1.1071402296479196, 1.0191713295044942,
      0.9301981992706797, 0.84031084801876166, 0.749601402096927,
      0.65816400069032288, 0.56609468749971958, 0.47349129815856716,
      0.3804533438905936, 0.28708189150670804, 0.19347943975648624,
      0.0997497921236067, 0.0059979265851218986, -0.0876701377175456,
      -0.18114747691479302, -0.27432640132886738, -0.36709859707968145,
      -0.45935526997222675, -0.55098729144663694, -0.64188534649780538,
      -0.731940083406395, -0.82104226484181564, -0.90908292020884518,
      -0.99595349920965537, -1.0815460261691787, -1.1657532549036258,
      -1.2484688239660915, -1.329587412235695, -1.4090048941355648,
      -1.4866184945876866, -1.5623269435919407, -1.6360306297465781,
      -1.7076317528449323, -1.777034475220012, -1.844145071449294,
      -1.9088720763352343, -1.971126431026857, -2.0308216266917909,
      -2.0878738457581258, -2.1422021006155436, -2.1937283692220277,
      -2.2423777275989578, -2.2880784789690565, -2.3307622792567146,
      -2.3703642587548659, -2.4068231398935285, -2.4400813506325969,
      -2.4700851334080371, -2.49678464961278, -2.5201340791039231,
      -2.5400917147649236, -2.556620051891795, -2.5696858722299645,
      -2.5792603224768946, -2.585318987117124, -2.58784195547726,
      -2.5868138827697393, -2.5822240450934224, -2.5740663881839261,
      -2.5623395698468654, -2.5470469959540289, -2.5281968499273262,
      -2.5058021155666474, -2.479880593170436, -2.450454908941146,
      -2.4175525175198183, -2.381205697645806, -2.3414515409088175,
      -2.2983319335590409, -2.25189353133008, -2.202187727335994,
      -2.1492706129548416, -2.0932029317453669, -2.0340500264867738,
      -1.9718817792724266, -1.9067725447564705, -1.8388010765946758,
      -1.7680504471737817, -1.6946079606539834, -1.618565059436412,
      -1.5400172241832206, -1.4590638674344811, -1.375808220987597,
      -1.2903572171503104, -1.2028213639978482, -1.1133146147865305,
      -1.0219542316886279, -0.92886064399635815, -0.83415730097609408,
      -0.7379705195679781, -0.64042932710547074, -0.54166529926322515,
      -0.44181239344288376, -0.34100677781158123, -0.23938665621534541,
      -0.12850152303951695, -0.068612679976437788, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, -0.0048955579211070535, -0.039185627678638466,
      -0.12251205311472055, -0.23531177353151045, -0.35300688323107171,
      -0.47053224648402892, -0.58771008721273343, -0.704362157817628,
      -0.82030999276690231, -0.93537516388228925, -1.0493795369498009,
      -1.1621455292810785, -1.2734963678473281, -1.3832563476056854,
      -1.4912510896349236, -1.5973077986961206, -1.7012555198352652,
      -1.8029253936403338, -1.9021509097670639, -1.9987681583522789,
      -2.0926160789299955, -2.183536706468884, -2.2713754141534643,
      -2.3559811525347008, -2.4372066846785092, -2.5149088169441312,
      -2.5889486250320481, -2.6591916749432873, -2.7255082385011846,
      -2.7877735030921951, -2.8458677752870924, -2.8996766780154504,
      -2.9490913409725681, -2.9940085839466697, -3.0343310927639839,
      -3.06996758756016, -3.1008329830925803, -3.1268485408238815,
      -3.1479420125187922, -3.1640477750993128, -3.1751069565225323,
      -3.1810675524663647, -3.1818845335996131, -3.1775199432351715,
      -3.1679429852010972, -3.1531301017392126, -3.1330650412811329,
      -3.1077389159625461, -3.0771502487411588, -3.0413050100196877,
      -3.0002166436540718, -2.9539060822845271, -2.9024017519238527,
      -2.8457395657303848, -2.7839629069596, -2.7171226010597826,
      -2.6452768769030666, -2.5684913171881907, -2.4868387980221707,
      -2.4003994177372623, -2.3092604150137785, -2.2135160763632404,
      -2.1132676330921845, -2.0086231478465204, -1.8996973908540142,
      -1.7866117060260962, -1.6694938670604291, -1.5484779237285131,
      -1.4237040385331454, -1.295318313926096, -1.1634726103301729,
      -1.0283243551845169, -0.89003634324846737, -0.748776528448069,
      -0.60471780751983839, -0.45803779574499176, -0.30891859508663772,
      -0.15754655501770673, -0.0041120263802318889, 0.15119089138787553,
      0.30816460932114847, 0.46660831392764074, 0.62631823775444129,
      0.78708793515153075, 0.94870856283568639, 1.1109691648575328,
      1.2736569616011983, 1.4365576423733248, 1.5994556611773056,
      1.7621345352605828, 1.9243771459926156, 2.0859660416706163,
      2.246683741781986, 2.4063130422923829, 2.5646373215593021,
      2.7214408463654949, 2.8765090776586262, 3.0296289755646328,
      3.1805893031891492, 3.3291809288081144, 3.4751971259469188,
      3.618433870946788, 3.75869013759715, 3.8957681883147375,
      4.0294738615091221, 4.1596168546853844, 4.2860110028522431,
      4.4084745518244057, 4.5268304259854464, 4.6409064901442489,
      4.750535805069501, 4.8555568762842407, 4.9558138957828026,
      5.0511569762962072, 5.1414423777040765, 5.2265327252876,
      5.3062972194600695, 5.3806118366500542, 5.4493595210414085,
      5.5124303668357859, 5.5697217907701884, 5.6211386946058877,
      5.6665936173333389, 5.7060068768421868, 5.739306700814895,
      5.7664293466408338, 5.7873192101465136, 5.801928922961042,
      5.8102194383224859, 5.8121601052030147, 5.80772873061283,
      5.7969116299478944, 5.7797036652996825, 5.7561082716178689,
      5.7261374706896078, 5.6898118728831886, 5.64716066660197,
      5.5982215954503038, 5.5430409231327253, 5.481673386092945,
      5.4141821339312344, 5.3406386576856821, 5.2611227060195231,
      5.1757221894430057, 5.084533072673409, 4.9876592552500059,
      4.8852124405873676, 4.7773119935975954, 4.66408478708324,
      4.5456650371153273, 4.189780168049869, 3.3803602693430159,
      2.607396188503972, 2.329414450165932, 2.2909612809401936,
      2.2517807321831818, 2.2118831082882289, 2.1712789627433819,
      2.12997909511292, 2.0879945479093536, 2.0453366034137037,
      2.0020167803885807, 1.9580468307109338, 1.9134387359176479,
      1.8682047036761003, 1.8223571641690068, 1.7759087663909974,
      1.7288723743866237, 1.6812610633851184, 1.63308811586743,
      1.5843670175716404, 1.5351114534069219, 1.4853353032984171,
      1.4350526379602866, 1.3842777146077943, 1.3330249725824961,
      1.2813090289184859, 1.2291446738585388, 1.1765468662795808,
      1.1235307290569088, 1.0701115443959899, 1.016304749068297,
      0.96212592960863619, 0.90759081745939085, 0.85271528403429919,
      0.7975153357504865, 0.74200710900806865, 0.68620686511533469,
      0.63013098514987875, 0.573795964796941, 0.51721840913079253,
      0.4604150273457282, 0.40340262746325595, 0.34619811098077735,
      0.2888184674826319, 0.23128076923284427, 0.17360216572364068,
      0.11579987817671435, 0.057891194025771982, -0.00010653862028142659,
      -0.058175916560210213, -0.11629948710498707, -0.17445975368539629,
      -0.23263918151299448, -0.29082020324964181, -0.34898522466755255,
      -0.40711663037928908, -0.46519678953456062, -0.52320806154609878,
      -0.58113280182641114, -0.63895336753634291, -0.69665212334701843,
      -0.75421144716674093, -0.81161373592389885, -0.86884141132198478,
      -0.92587692558084778, -0.98270276720394589, -1.0393014667289804,
      -1.0956556024588329, -1.1517478061950903, -1.207560768961834,
      -1.2630772467109297, -1.3182800660077587, -1.3731521297106963,
      -1.4276764226353476, -1.4818360171719989, -1.5356140788949633,
      -1.58899387217165, -1.6419587656976693, -1.6944922380338052,
      -1.7465778831218788, -1.7981994157259524, -1.8493406768688476,
      -1.8999856392562924, -1.9501184126027509, -1.9997232489515886,
      -2.0487845479713589, -2.09728686217213, -2.1452149020956139,
      -2.1925535414460389, -2.239287822189127, -2.2854029595895087,
      -2.33088434719003, -2.3757175617514203, -2.4198883681236771,
      -2.4633827240499984, -2.5061867849437958, -2.5482869085771664,
      -2.5896696597024627, -2.6303218146442187, -2.6702303657830084,
      -2.7093825259816273, -2.747765732975247, -2.7853676536504475,
      -2.8221761882599146, -2.8581794745910467, -2.8933658920199363,
      -2.9277240654966703, -2.9612428695003321, -2.9939114318495692,
      -3.0257191374466448, -3.0566556319810951, -3.0867108255055982,
      -3.1158748959392217, -3.144138292488488, -3.1714917389746828,
      -3.19792623708903, -3.2234330695401963, -3.2480038031029639,
      -3.2716302916047071, -3.2943046788019816, -3.3160194011494419,
      -3.3367671904960177, -3.3565410766800388, -3.3753343900139092,
      -3.3931407636900084, -3.4099541360665921, -3.4257687528671474,
      -3.4405791692865226, -3.4543802519748588, -3.4671671809360869,
      -3.478935451312609, -3.4896808750802917, -3.4993995826244237,
      -3.5080880242075212, -3.5157429713611408, -3.5223615181423304,
      -3.527941082285817, -3.5324794062691, -3.5359745582513811,
      -3.5384249329012341, -3.5398292521471251, -3.5401865657885776,
      -3.5394962519952267, -3.5377580177298138, -3.534971899035726,
      -3.5311382612179738, -3.526257798917015, -3.5203315360848819,
      -3.5133608258395395, -3.5053473501958226, -3.4962931197199092,
      -3.4862004730564751, -3.4750720763336926, -3.4629109224800243,
      -3.4497203304339426, -3.4355039442207342, -3.4202657319300842,
      -3.4040099846040288, -3.3867413150010628, -3.36846465624997,
      -3.3491852603970864, -3.3289086968513337, -3.3076408507238124,
      -3.2853879210685184, -3.2621564189983876, -3.2379531656887308,
      -3.2127852903238461, -3.1866602279152318, -3.1595857169828703,
      -3.1315697971634862, -3.1026208067453092, -3.0727473800766081,
      -3.04195844484055, -3.0102632192677476, -2.9776712092769189,
      -2.9441922054758138, -2.9098362800598516, -2.874613783642749,
      -2.83853534198995, -2.801611852668719, -2.7638544815662107,
      -2.7252746593275616, -2.6858840777602828, -2.6456946861099282,
      -2.604718687202785, -2.5629685335592391, -2.5204569234442125,
      -2.4771967967777226, -2.433201330991507, -2.3884839367930182,
      -2.3430582538454923, -2.2969381464098038, -2.2501376988859048,
      -2.2026712112479796, -2.1545531944276455, -2.1057983656657457,
      -2.0564216437663565, -2.006438144235732, -1.9558631743924111,
      -1.9047122284579683, -1.853000982532828, -1.80074528948532,
      -1.747961173817107, -1.6946648264883042, -1.640872599668348,
      -1.5866010013997756, -1.5318666902289662, -1.4766864698231723,
      -1.4210772835131507, -1.3650562087414682, -1.3086404515060215,
      -1.2518473407966346, -1.1946943229356999, -1.13719895588897,
      -1.0793789035334318, -1.0212519298977258, -0.96283589339455189,
      -0.90414874098576758, -0.84520850230825051, -0.78603328378147885,
      -0.72664126272831586, -0.667050681447774, -0.60727984120881584,
      -0.54734709626996836, -0.487270847932552, -0.42706953851771157,
      -0.36676164529231542, -0.30636567444566987, -0.24590015506250032,
      -0.18538363305699707, -0.12483466508843288, -0.064271812480366772,
      -0.0037136351801692852, 0.056821314295584034, 0.11731449698914882,
      0.17774739356153749, 0.23810151029979806, 0.29835838520345187,
      0.35849959401507431, 0.41850675626494838, 0.47836154129566788,
      0.53804567421779115, 0.59754094190481455, 0.65682919897103875,
      0.71589237371431491, 0.77471247399258358, 0.83327159310340482,
      0.89155191568846159, 0.94953572355240623, 1.0072054014116698,
      1.0645434426532516, 1.1215324551231161, 1.1781551667703811,
      1.2343944312462927, 1.2902332335616475, 1.3456546956440296,
      1.4006420818286367, 1.4551788042897229, 1.5092484284875736,
      1.5628346785412111, 1.6159214425221846, 1.6684927776870051,
      1.720532915659615, 1.7720262675980516, 1.8229574292751316,
      1.8733111860694329, 1.9230725178820596, 1.9722266040493974,
      2.0207588281795896, 2.0686547828687392, 2.1159002743369135,
      2.1624813270656964, 2.2083841883535116, 2.2535953327225058,
      2.2981014662820143, 2.341889531039866, 2.3849467091284553, 2.4272604269399,
      2.4688183591370456, 2.5096084326185575, 2.5496188304619936,
      2.5888379956678804, 2.6272546348336094, 2.6648577218140117,
      2.7016365012461452, 2.7375804919562734, 2.7726794902775556,
      2.8069235733463693, 2.8403031022013034, 2.87280872485759,
      2.9044313792789218, 2.9351622961629813, 2.9649930017496033,
      2.9939153204775444, 3.0219213775228604, 3.0490036012282546,
      3.0751547254663683, 3.1003677919023036, 3.1246361521033714,
      3.14795346956312, 3.170313721643935, 3.1917112014132538,
      3.2121405193258141, 3.2315966048219424, 3.2500747078371997,
      3.2675704001867056, 3.2840795768493338, 3.2995984571113781,
      3.3141235856139053, 3.327651833336732, 3.3401803984134522,
      3.3517068068240943, 3.3622289130319278, 3.3717449004880575,
      3.3802532820100173, 3.387752900037952, 3.3942429268126881,
      3.3997228644283637, 3.4041925447502317, 3.4076521292654349,
      3.4101021087856056, 3.4115433030198856, 3.4119768601022908,
      3.4114042559628595, 3.4098272935597262, 3.407248102070783,
      3.4036691359240026, 3.3990931737206287, 3.3935233170649881,
      3.3869629892809723, 3.3794159340152858, 3.3708862137137694,
      3.3613782080306445, 3.3508966121025514, 3.3394464346997448,
      3.3270329963183145, 3.3136619271224865, 3.299339164790958,
      3.2840709523075291, 3.2678638355519229, 3.2507246608604352,
      3.2326605725069593, 3.2136790099960657, 3.1937877053157466,
      3.1729946800876774, 3.1513082426074153, 3.1287369847944113,
      3.1052897790377347, 3.080975774939525, 3.0558043960016366,
      3.0297853362019422, 3.0029285564282442, 2.9752442808975457,
      2.9467429934685057, 2.9174354338358235, 2.8873325936593974,
      2.8564457125856979, 2.8247862742420407, 2.79236600211217,
      2.7591968552954125, 2.7252910242328259, 2.6906609263838939,
      2.6553192017727154, 2.619278708435075, 2.5825525178717941,
      2.5451539104008312, 2.507096370423576, 2.4683935816345857,
      2.4290594221246682, 2.3891079594978004, 2.3485534458992987,
      2.3074103129316592, 2.2656931665445943, 2.2234167818833837,
      2.1805960981007644, 2.1372462130365095, 2.0933823778903142,
      2.0490199918668841, 2.0041745967599982, 1.9588618714740149,
      1.913097626471483, 1.8668977982557575, 1.8202784437677477,
      1.7732557347466185, 1.72584595204081, 1.678065479889326,
      1.6299308002345483, 1.5814584869115547, 1.5326651998455267,
      1.4835676791987589, 1.4341827395742497, 1.3845272641491786,
      1.334618198713913, 1.284472545798613, 1.2341073587140357,
      1.183539735664588, 1.1327868137801804, 1.0818657630782795,
      1.0307937805472231, 0.97958808419477, 0.92826590703509815,
      0.87684449105568585, 0.8253410812777815, 0.7737729198146025,
      0.722157239842186, 0.67051125961558722, 0.61885217651176594,
      0.56719716113564733, 0.515563351353309, 0.46396784630863314,
      0.41242770056717271, 0.360959918260858, 0.30958144720182718,
      0.25830917298597617, 0.20715991319902202, 0.1561504116930823,
      0.10529733277693468, 0.054617255473531204, 0.0041266678284745,
      -0.046158038739908411, -0.096220575039786926, -0.14604475970840464,
      -0.19561452478001443, -0.24491392117022526, -0.29392712408464267,
      -0.34263843846514025, -0.39103230435764341, -0.4390933022216808,
      -0.48680615813950706, -0.53415574901544016, -0.58112710778954513,
      -0.62770542847901079, -0.67387607117062365, -0.7196245670047563,
      -0.764936623117234, -0.80979812744656543, -0.85419515345494679,
      -0.89811396487044093, -0.941541020324999, -0.98446297793236426,
      -1.0268666996964491, -1.0687392559358029, -1.1100679296869276,
      -1.1508402208980928, -1.1910438506301722, -1.2306667651182641,
      -1.2696971397894536, -1.3081233832440673, -1.3459341410505485,
      -1.3831182994861708, -1.4196649892251783, -1.4555635889539118,
      -1.4908037288271598, -1.52537529383746, -1.5592684271567321,
      -1.59247353334779, -1.6249812814956646, -1.6567826081764012,
      -1.6878687203942753, -1.7182310984607809, -1.7478614986737568,
      -1.7767519559350788, -1.8048947862924685, -1.8322825893840731,
      -1.8589082507393391, -1.8847649439721905, -1.90984613293906,
      -1.9341455737090227, -1.9576573165072211, -1.9803757075024442,
      -2.0022953904316281, -2.0234113082702154, -2.043718704689121,
      -2.0632131253800252, -2.0818904193359966, -2.0997467400073759,
      -2.1167785463424749, -2.1329826037099218, -2.1483559846950842,
      -2.1628960698297286, -2.1766005482167725, -2.1894674179665863,
      -2.2014949865719751, -2.212681871216009, -2.2230269989047131,
      -2.232529606490683, -2.2411892406066092, -2.2490057574940918,
      -2.2559793227267511, -2.2621104107758234, -2.2673998044920691,
      -2.2718485945197973, -2.2754581785185666, -2.2782302603355484,
      -2.2801668490750755, -2.2812702579745645, -2.2815431032568863,
      -2.2809883028839879, -2.2796090751293558, -2.2774089370691182,
      -2.2743917029869474, -2.2705614826858262, -2.26592267965761,
      -2.26047998912489, -2.2542383960534629, -2.2472031730256505,
      -2.2393798779784566, -2.2307743518730025, -2.2213927162683653,
      -2.21124137079642, -2.2003269904914773, -2.1886565230554513,
      -2.1762371860798155, -2.1630764640669655, -2.1491821053946132,
      -2.1345621192298889, -2.1192247723186153, -2.1031785856757286,
      -2.0864323311641111, -2.0689950280494847, -2.0508759394055853,
      -2.0320845684522721, -2.0126306548407573, -1.992524170807058,
      -1.9717753172475252, -1.9503945197221666, -1.9283924244297852,
      -1.9057798940167781, -1.8825680033443009, -1.8587680352106677,
      -1.8343914759509548, -1.8094500110165961, -1.7839555204324831,
      -1.7579200741934506, -1.7313559276421884, -1.7042755167463619,
      -1.676691453273331, -1.6486165199717391, -1.6200636656895064,
      -1.5910460003357108, -1.5615767898994117, -1.5316694513919253,
      -1.5013375476805326, -1.470594782318329, -1.4394549942765069,
      -1.4079321527134323, -1.3760403516522262, -1.3437938045506534,
      -1.311206838927051, -1.278293890928426, -1.2450694998128968,
      -1.2115483023998821, -1.1777450275632382, -1.1436744906313612,
      -1.1093515877216784, -1.0747912901332597, -1.04000863865088,
      -1.0050187378691113, -0.96983675045629447, -0.93447789139005966,
      -0.89895742226002751, -0.86329064544971024, -0.82749289835654483,
      -0.79157954759881988, -0.75556598320595192, -0.71946761282751659,
      -0.6832998558864718, -0.647078137765461, -0.61081788398783721,
      -0.574534514410588, -0.53824343737210989, -0.50196004390966842,
      -0.46569970196421612, -0.429477750545377, -0.39330949400841481,
      -0.35721019622960076, -0.32119507486341586, -0.28527929566322957,
      -0.24947796671767866, -0.21380613274880511, -0.17827876947818891,
      -0.142910777996558, -0.10771697911527107, -0.0727121078025793,
      -0.037910807636563321, -0.0033276252953848813, 0.031022994916932847,
      0.065126716530326811, 0.098969316281177111, 0.13253668949331782,
      0.16581485536182958, 0.19878996222023196, 0.23144829278510742,
      0.26377626928630055, 0.29576045861052447, 0.32738757733641888,
      0.3586444967458795, 0.38951824779089317, 0.41999602594768654,
      0.450065196052636, 0.47971329707132326, 0.50892804681264814,
      0.53769734652315249, 0.56600928545894669, 0.593852145416625,
      0.62121440510406678, 0.64808474451896736, 0.67445204922303759,
      0.70030541451773887, 0.725634149593775, 0.75042778155313061,
      0.77467605936762707, 0.798368957766216, 0.82149668104079066,
      0.84404966672866755, 0.86601858923982988, 0.88739436341304323,
      0.908168147942595, 0.928331348747864, 0.947875622222749,
      0.96679287842161132, 0.98507528412982037, 1.0027152658418239,
      1.0197055126621053, 1.0360389790745479, 1.0517088876552549,
      1.0667087316537085, 1.0810322774777121, 1.0946735670889187,
      1.1076269203049467, 1.1198869369788897, 1.1314484990488294,
      1.1423067725574922, 1.1524572095253867, 1.1618955496795935,
      1.1706178221292949, 1.1786203469456631, 1.1858997365827257,
      1.19245289719216, 1.198277029890777, 1.2033696318692291,
      1.2077284973744347, 1.2113517186367997, 1.2142376866423215,
      1.2163850918090311, 1.2177929245673422, 1.2184604757923232,
      1.2183873371638363, 1.217573401387003, 1.2160188623084285,
      1.2137242149349263, 1.2106902553216365, 1.2069180803529784,
      1.202409087410454, 1.1971649739418651, 1.191187736904793,
      1.184479672100885, 1.1770433733918555, 1.168881731820387,
      1.159997934627335, 1.1503954641201062, 1.140078096459169,
      1.1290499003393979, 1.1173152355470815, 1.104878751416785,
      1.0917453851628147, 1.0779203601444154, 1.063409183987323,
      1.0482176465691606, 1.0323518179991134, 1.0158180464026996,
      0.998622955606975, 0.9807734427980539, 0.96227667599123434,
      0.94314009141980915, 0.92337139085994524, 0.90297853883889423,
      0.88196975970963754, 0.86035353465165909, 0.83813859860773066,
      0.81533393707509194, 0.791948782818719, 0.76799261250735074,
      0.7434751432125789, 0.71840632888250244, 0.69279635668588235,
      0.66665564324145332, 0.639994830821011, 0.61282478342891611,
      0.58515658280358229, 0.55700152433032579, 0.52837111286926375,
      0.49927705854654847, 0.46973127242879603, 0.43974586206477567,
      0.40933312706084896, 0.37850555456271889, 0.34727581457062912,
      0.31565675526869069, 0.28366139829928466, 0.25130293386855779,
      0.21859471588957979, 0.18555025709362652, 0.15218322386923805,
      0.11850743124255911, 0.0845368378271695, 0.0502855404999097,
      0.015767769204755647, -0.019002118323844092, -0.054009641999787125,
      -0.089240204695272912, -0.12467909768783805, -0.16031150627435828,
      -0.19612251520918086, -0.23209711427442042, -0.26822020398055163,
      -0.30447660115452785, -0.34085104462996291, -0.3773282010403301,
      -0.41389267053118778, -0.45052899250239548, -0.48722165150174507,
      -0.523955083014971, -0.56071367933343641, -0.5974817954624001,
      -0.63424375494006113, -0.67098385584739062, -0.70768637670926227,
      -0.7443355824125, -0.7809157301734676, -0.81741107546055369,
      -0.85380587804554808, -0.89008440790576082, -0.92623095120207311,
      -0.96222981627693938, -0.99806533955116217, -1.0337218915757698,
      -1.0691838829437423, -1.1044357702095122, -1.1394620618771438,
      -1.174247324243255, -1.208776187356426, -1.2430333509367524,
      -1.2770035901431747, -1.3106717614468608, -1.344022808509405,
      -1.3770417679088183, -1.4097137749253303, -1.4420240692703592,
      -1.4739580007500719, -1.5055010349907612, -1.5366387590171817,
      -1.5673568868666898, -1.5976412651290952, -1.6274778783843722,
      -1.6568528547456645, -1.6857524712588663, -1.7141631592155382,
      -1.7420715094746595, -1.7694642777233294, -1.7963283896969251,
      -1.8226509462853693, -1.8484192286346273, -1.8736207031817242,
      -1.8982430265696821, -1.922274050574295, -1.9457018269609381,
      -1.9685146121949815, -1.990700872110063, -2.0122492866004347,
      -2.0331487541234097, -2.0533883961771688, -2.0729575616990941,
      -2.0918458313097008, -2.1100430216398438, -2.1275391894871412,
      -2.1443246358018264, -2.1603899097032819, -2.1757258124058767,
      -2.1903234009990693, -2.204173992175301, -2.2172691658812584,
      -2.2296007688144939, -2.2411609178658427, -2.2519420035127449,
      -2.2619366930728662, -2.2711379337925184, -2.2795389559252239,
      -2.2871332757691141, -2.2939146984369652, -2.2998773206279624,
      -2.3050155333016344, -2.3093240241764503, -2.3127977802517123,
      -2.3154320900839291, -2.3172225459994307, -2.3181650462962162,
      -2.3182557971796909, -2.3174913146696112, -2.3158684264508063,
      -2.3133842735291061, -2.3100363117450056, -2.3058223132984,
      -2.3007403680914362, -2.2947888848993614, -2.2879665925616286,
      -2.2802725409360889, -2.2717061017763869, -2.262266969552766,
      -2.2519551620702662, -2.2407710210178107, -2.2287152123687863,
      -2.2157887266994329, -2.201992879423778, -2.1873293107999925,
      -2.1717999859000932, -2.1554071944652544, -2.1381535505840445,
      -2.1200419923600347, -2.1010757813455543, -2.0812585018778473,
      -2.0605940604335511, -2.03908668467515, -2.0167409224417829,
      -1.9935616407335857, -1.9695540244699969, -1.9447235750869123,
      -1.9190761091711621, -1.8926177568695357, -1.8653549601335315,
      -1.837294471062151, -1.8084433499294392, -1.7788089631063533,
      -1.7483989809922313, -1.7172213757506694, -1.6852844189884837,
      -1.6525966792303222, -1.619167019325819, -1.5850045938606954,
      -1.5501188462927582, -1.5145195060409888, -1.4782165855071288,
      -1.4412203769384875, -1.4035414492594096, -1.3651906446930229,
      -1.3261790753255014, -1.2865181196782536, -1.2462194189983333,
      -1.2052948735469728, -1.1637566388124769, -1.1216171215703192,
      -1.0788889758512785, -1.0355850988883886, -0.99171862690834411,
      -0.94730293076442451, -0.9023516116910405, -0.85687849677374583,
      -0.81089763432840645, -0.76442328937099091, -0.717469938885855,
      -0.67005226700247367, -0.622185160062352, -0.57388370168557468,
      -0.525163167855336, -0.47603902166545214, -0.42652690815355521,
      -0.37664264910518247, -0.32640223764756754, -0.27582183297927637,
      -0.22491775479694534, -0.17370647773992479, -0.12220462596773934,
      -0.070428967415549326, -0.018396408059951189, 0.033876013811052375,
      0.086371133402598124, 0.13907166530689205, 0.19196020935780914,
      0.24501925665078594, 0.29823119563898243, 0.351578317994857,
      0.40504282484340215, 0.45860683294001037, 0.51225238069276791,
      0.565961434505403, 0.61971589500091884, 0.67349760327942609,
      0.72728834724898217, 0.78106986788551436, 0.834823865674168,
      0.88853200700834367, 0.942175930521736, 0.99573725354716769,
      1.0491975785124021, 1.1025384994490606, 1.1557416084996077,
      1.2087885022123581, 1.2616607881305633, 1.3143400913501804,
      1.366808060879239, 1.4190463761676955, 1.4710367536102311,
      1.5227609529464419, 1.5742007838404339, 1.6253381123667712,
      1.6761548672670348, 1.7266330464969095, 1.7767547237680084,
      1.8265020547898081, 1.8758572837029153, 1.9248027494430808,
      1.973320892049768, 2.0213942590627685, 2.0690055116643675,
      2.1161374310214374, 2.16277292452919, 2.2088950318475491,
      2.2544869311466855, 2.2995319452159824, 2.3440135474772279,
      2.3879153679812148, 2.43122119938027, 2.4739150028872365,
      2.5159809140957705, 2.5574032487866707, 2.5981665086881045,
      2.6382553871835865, 2.6776547749319448, 2.7163497654765165,
      2.7543256607319964, 2.7915679763641661, 2.8280624472671927,
      2.8637950328576132, 2.898751922299065, 2.9329195396254852,
      2.966284548809472, 2.9988338589065275, 3.0305546289059495,
      3.0614342725111752, 3.0914604630162481, 3.1206211379576576,
      3.148904503669359, 3.1762990398715063, 3.2027935040425453,
      3.2283769357188339, 3.2530386608191213, 3.2767682957197986,
      3.2995557513011677, 3.321391236952441, 3.3422652643778963,
      3.3621686513645912, 3.3810925254213635, 3.3990283273383142,
      3.4159678146499539, 3.4319030649195095, 3.4468264789934491,
      3.4607307841623487, 3.4736090371546946, 3.4854546269953817,
      3.496261277830238, 3.5060230516351787, 3.5147343507410738,
      3.522389920299271, 3.528984850622181, 3.534514579387622,
      3.5389748937515852, 3.5423619323422928, 3.5446721871108569,
      3.5459025050529092, 3.5460500898830523, 3.5451125035183111,
      3.54308766743154, 3.5399738639603613, 3.5357697373968158,
      3.5304742950133363, 3.5240869079777526, 3.5166073120835293,
      3.5080356084077549, 3.4983722638148191, 3.4876181113464959,
      3.4757743505066458, 3.4628425473688735, 3.4488246345955447,
      3.4337229113280752, 3.4175400429422749, 3.4002790607121782,
      3.3819433612572718, 3.3625367059355309, 3.342063220162649,
      3.3205273924692733, 3.2979340735141118, 3.274288474985485,
      3.2495961683305956, 3.2238630834150004, 3.197095506973608,
      3.1693000809953973, 3.14048380104528, 3.1106540143289947,
      3.079818417690682, 3.0479850555382808, 3.0151623176001818,
      2.9813589365665791, 2.9465839855961637, 2.9108468757007633,
      2.874157353081447, 2.8365254963043145, 2.7979617132812979,
      2.7584767382294904, 2.71808162852061, 2.6767877613463567,
      2.6346068303548797, 2.5915508420847138, 2.5476321123096155,
      2.502863262406716, 2.4572572154020169, 2.4108271920260065,
      2.3635867067163088, 2.3155495633620786, 2.266729851093443,
      2.2171419398794026, 2.16680047602912, 2.1157203777081643, 2.06391683018845,
      2.0114052810580638, 1.9582014354255968, 1.9043212509394187,
      1.8497809327429922, 1.794596928345161, 1.7387859223081541,
      1.6823648310444055, 1.6253507974679073, 1.5677611853465836,
      1.5096135738181682, 1.4509257517928507, 1.3917157121836352,
      1.3320016461844431, 1.2718019372971041, 1.2111351554069874,
      1.1500200509092307, 1.0884755485205186, 1.0265207411350505,
      0.96417488365354409, 0.90145738667119757, 0.83838781025421416,
      0.77498585748633542, 0.711271367954451, 0.64726431143665986,
      0.58298478124429032, 0.51845298759404246, 0.4536892510956444,
      0.38871399598819628, 0.32354774344594034, 0.25821110476181219,
      0.19272477457650672, 0.12710952415673488, 0.061386194371838766,
      -0.0044243111658960168, -0.070301032993037971, -0.13622296277313886,
      -0.20216905024315487, -0.26811821020700644, -0.33404932960550104,
      -0.39994127457404238, -0.46577289732260158, -0.53152304330174061,
      -0.59717055833216237, -0.6626942955973244, -0.72807312273261315,
      -0.79328592883475468, -0.85831163167871849, -0.92312918477394945,
      -0.987717584294322, -1.0520558762495027, -1.1161231635320916,
      -1.179898612968991, -1.2433614623129017, -1.3064910272186154,
      -1.3692667083230434, -1.4316679981620755, -1.4936744880573267,
      -1.5552658750864865, -1.6164219690049231, -1.6771226990581336,
      -1.7373481207522838, -1.7970784226923271, -1.8562939333192277,
      -1.914975127637268, -1.9731026338298017, -2.0306572398244058,
      -2.0876198999923212, -2.143971741599783, -2.199694071206673,
      -2.2547683811462362, -2.3091763558417795, -2.3628998781561843,
      -2.4159210356224219, -2.4682221264478135, -2.5197856657667033,
      -2.570594391722413, -2.6206312712913187, -2.6698795062491967,
      -2.7183225389496188, -2.7659440580916983, -2.812728004437075,
      -2.8586585762792214, -2.9037202350050313, -2.9478977105241904,
      -2.9911760065868904, -3.0335404060117903, -3.0749764758664857,
      -3.1154700725265942, -3.1550073466101369, -3.1935747479170398,
      -3.2311590301299731, -3.2677472555532692, -3.3033267996991618,
      -3.3378853556788313, -3.3714109386840159, -3.4038918902291861,
      -3.4353168822714508, -3.465674921305641, -3.494955352281317,
      -3.5231478624826815, -3.550242485241426, -3.5762296035148231,
      -3.6010999534218482, -3.6248446275971289, -3.6474550784655095,
      -3.6689231214187719, -3.6892409377821576, -3.7084010777445511,
      -3.7263964631663526, -3.7432203902172883, -3.7588665319400691,
      -3.773328940630627, -3.7866020501216289, -3.7986806779781794,
      -3.8095600275327026, -3.8192356897611104, -3.8277036450719528,
      -3.8349602649819206, -3.8410023135955735, -3.8458269490136527,
      -3.8494317246083845, -3.851814590108003, -3.852973892609735,
      -3.8529083774648236, -3.8516171889870194, -3.8490998710423692,
      -3.8453563675102083, -3.84038702262349, -3.8341925811698672,
      -3.826774188538784, -3.8181333906243351, -3.8082721336653558,
      -3.7971927639092691, -3.7848980270767609, -3.7713910677790672,
      -3.7566754287894821, -3.7407550501492159, -3.7236342681804686,
      -3.7053178143206296, -3.6858108138134456, -3.6651187843690818,
      -3.643247634583946, -3.6202036622441809, -3.5959935525643907,
      -3.5706243762124594, -3.5441035872836975, -3.5164390210816756,
      -3.4876388917552146, -3.4577117899277492, -3.4266666800715559,
      -3.3945128977776187, -3.3612601469569507, -3.3269184968698173,
      -3.2914983790733765, -3.2550105841600141, -3.2174662584493214,
      -3.1788769006081643, -3.1392543579959691, -3.0986108229825944,
      -3.0569588291941217, -3.0143112475892941, -2.9706812824010744,
      -2.9260824669838281, -2.8805286595358579, -2.834034038756144,
      -2.7866130994204137, -2.7382806476842796, -2.6890517963996681,
      -2.6389419603962692, -2.5879668515071503, -2.5361424735877502,
      -2.4834851173883168, -2.430011355311986, -2.3757380362461284,
      -2.3206822800579334, -2.2648614720556055, -2.2082932575121865,
      -2.1509955359496638, -2.0929864554091768, -2.0342844065149817,
      -1.9749080165776678, -1.9148761436755555, -1.8542078704504035,
      -1.7929224979863094, -1.7310395395323677, -1.6685787141796493,
      -1.6055599404943508, -1.542003330049875, -1.4779291808840191,
      -1.413357970867132, -1.3483103511340586, -1.2828071392718072,
      -1.2168693125497658, -1.1505180011431659, -1.083774481174494,
      -1.016660167822401, -0.94919660825980834, -0.88140547464902952,
      -0.81330855713840977, -0.74492775658751487, -0.67628507743037525,
      -0.60740262056763383, -0.53830257604020637, -0.46900721576922544,
      -0.39953888623031697, -0.32992000107641845, -0.26017303394077484,
      -0.19032051095116259, -0.12038500322693303, -0.050389119594252928,
      0.019644500918603456, 0.089693196529407576, 0.15973429005943263,
      0.22974509659601908, 0.29970293092514505, 0.36958511484873291,
      0.43936898484394465, 0.50903189949548211, 0.57855124692588589,
      0.64790445237245242, 0.71706898552809806, 0.78602236804309578,
      0.85474218104947974, 0.92320607240059271, 0.99139176418425623,
      1.0592770601397965, 1.1268398528982777, 1.1940581314213528,
      1.2609099882069412, 1.3273736266198313, 1.3934273681657525,
      1.459049659509235, 1.5242190798046109, 1.5889143478164287,
      1.6531143288939918, 1.7167980420323337, 1.7799446668645904,
      1.8425335505865204, 1.9045442148559679, 1.9659563626411056,
      2.0267498848309571, 2.0869048670336454, 2.1464015963155516,
      2.205220567653801, 2.2633424904654404, 2.3207482950184031,
      2.377419138875176, 2.4333364131988575, 2.4884817488458584,
      2.5428370226139183, 2.5963843633090566, 2.6491061576787165,
      2.7009850563209947, 2.7520039794954019, 2.802146122899007,
      2.8513949632344158, 2.8997342637430874, 2.94714807973286,
      2.9936207638782326, 3.0391369714753629, 3.0836816656122581,
      3.127240122225472, 3.169797935066351, 3.2113410205502566,
      3.2518556224767874, 3.2913283166684217, 3.3297460155397296,
      3.3670959725019931, 3.403365786259366, 3.4385434049785624,
      3.4726171303854123, 3.5055756217830378, 3.5374078998425404,
      3.5681033502883857, 3.5976517275777988, 3.6260431583719384,
      3.6532681448455007, 3.6793175679912258, 3.7041826907087789,
      3.7278551607582235, 3.7503270136755331, 3.7715906754588997,
      3.7916389651783651, 3.8104650974836654, 3.8280626849025956,
      3.8444257400764834, 3.8595486778524704, 3.8734263171786738,
      3.8860538829527722, 3.8974270077059558, 3.9075417331204108,
      3.9163945114491492, 3.9239822067845282, 3.9303020962035435,
      3.9353518707413366, 3.9391296362667712, 3.9416339142139742,
      3.9428636421467607, 3.9428181742275372, 3.9414972814945672,
      3.9389011520586958, 3.9350303911546716, 3.9298860209865758,
      3.9234694805059966, 3.9157826250282906, 3.9068277257128496,
      3.8966074689024688, 3.8851249553252805, 3.8723836991818019,
      3.8583876270238919, 3.843141076554911, 3.8266487953448141,
      3.8089159392823406, 3.7899480709562923, 3.7697511579583534,
      3.7483315709387255, 3.7256960816074898, 3.7018518605815189,
      3.6768064750765554, 3.6505678865113467, 3.6231444479430994,
      3.5945449013728443, 3.5647783749523749, 3.5338543800712974,
      3.5017828082202578, 3.4685739278164944, 3.4342383809630852,
      3.3987871798984828, 3.3622317034599773, 3.3245836934371598,
      3.2858552507182539, 3.2460588313700049, 3.2052072425815221,
      3.1633136385535052, 3.1203915160956441, 3.0764547103460873,
      3.0315173902535446, 2.9855940538599048, 2.9386995236831042,
      2.8908489418001566, 2.8420577649669481, 2.7923417595309403,
      2.7417169963005628, 2.690199845230314, 2.6378069701133997,
      2.5845553231969016, 2.5304621395109677, 2.4755449312914264,
      2.4198214821896395, 2.3633098415909073, 2.3060283185632517,
      2.2479954758229206, 2.1892301237964396, 2.1297513143468181,
      2.0695783345629266, 2.0087307004269288, 1.947228150393862,
      1.8850906388908586, 1.8223383299159883, 1.758991590206864,
      1.69507098261448, 1.6305972595065958, 1.5655913557366952,
      1.500074381889581, 1.4340676173187767, 1.3675925031182048,
      1.3006706351589348, 1.2333237569625082, 1.1655737523987213,
      1.0974426386923153, 1.0289525591812951, 0.96012577587349757,
      0.89098466226737683, 0.82155169590522692, 0.75184945108625512,
      0.68190059133742886, 0.61172786193716322, 0.54135408256178508,
      0.470802139718739, 0.40009497919194248, 0.32925559847812458,
      0.25830703921981274, 0.18727237967144772, 0.11617472723759863,
      0.04503721050017713, -0.026117028154515887, -0.097264840034429881,
      -0.16838307802038791, -0.23944860399825418, -0.31043829658846217,
      -0.38132905868740441, -0.45209782506559903, -0.52272156996241037,
      -0.59317731474592006, -0.66344213539177044, -0.73349316999182135,
      -0.80330762638986575, -0.87286278955915542, -0.94213602920327555,
      -1.0111048070690716, -1.0797466844860057, -1.1480393297081304,
      -1.2159605251351551, -1.2834881748265576, -1.350600311649981,
      -1.4172751045305656, -1.483490865648927, -1.5492260575121428,
      -1.6144593000261971, -1.6791693777036512, -1.7433352464852485,
      -1.8069360406045838, -1.869951079585348, -1.9323598749402562,
      -1.9941421370024062, -2.0552777815067365, -2.1157469361560608,
      -2.1755299472211926, -2.2346073860686575, -2.292960055404285,
      -2.3505689955628353, -2.4074154908391669, -2.4634810755778638,
      -2.51874754028044, -2.5731969374522685, -2.6268115876176616,
      -2.6795740851000023, -2.731467303644211, -2.782474402120831,
      -2.8325788300074866, -2.8817643328428235, -2.9300149574402927,
      -2.9773150572148435, -3.0236492973527533, -3.0690026597177331,
      -3.1133604477313832, -3.1567082913079534, -3.1990321515552829,
      -3.2403183251773742, -3.2805534491050534, -3.3197245048428496,
      -3.3578188226940968, -3.3948240858573788, -3.4307283344782458,
      -3.4655199696261034, -3.4991877568575771, -3.5317208299946921,
      -3.563108694776977, -3.5933412320967628, -3.6224087012427075,
      -3.650301743241624, -3.6770113838265233, -3.7025290362259722,
      -3.72684650403093, -3.7499559838701146, -3.7718500678991989,
      -3.7925217461117189, -3.8119644086643012, -3.830171848017184,
      -3.8471382608443365, -3.8628582499002353, -3.87732682579428,
      -3.890539408545501, -3.9024918289683463, -3.9131803300300279,
      -3.9226015680565971, -3.9307526137093904, -3.9376309528856313,
      -3.9432344875469116, -3.9475615362573619, -3.9506108347011093,
      -3.9523815360522092, -3.9528732111284182, -3.9520858485325929,
      -3.9500198545411531, -3.9466760528708944, -3.942055684386272,
      -3.9361604066125455, -3.9289922930786929, -3.9205538325744476,
      -3.9108479282847219, -3.8998778967315739, -3.8876474665863134,
      -3.874160777410129, -3.8594223781891523, -3.8434372257569143,
      -3.8262106830873539, -3.8077485174394221, -3.7880568984268144,
      -3.7671423958602372, -3.7450119775029242, -3.72167300672769,
      -3.6971332400211288, -3.6714008243034453, -3.644484294190331,
      -3.6163925691230885, -3.5871349503576, -3.5567211178068474,
      -3.5251611266811453, -3.49246540432566, -3.458644746547153,
      -3.4237103138758114, -3.3876736281092503, -3.3505465683016205,
      -3.3123413666320807, -3.2730706044116462, -3.2327472080335951,
      -3.191384444441471, -3.1489959166487633, -3.1055955593508817,
      -3.0611976342177702, -3.0158167250442158, -2.9694677329068688,
      -2.9221658713336662, -2.8739266610376237, -2.8247659247728234,
      -2.7746997821669153, -2.7237446442880424, -2.6719172081230993,
      -2.6192344509941017, -2.5657136251182036, -2.5113722517556818,
      -2.4562281151908474, -2.4002992569920956, -2.3436039701868139,
      -2.2861607928817129, -2.2279885021454313, -2.1691061080071146,
      -2.1095328470000845, -2.049288175702634, -1.9883917643121787,
      -1.9268634903178172, -1.8647234317369763, -1.8019918604386966,
      -1.7386892355433263, -1.67483619662562, -1.6104535568001854,
      -1.5455622958716049, -1.4801835535702783, -1.4143386223259027,
      -1.3480489402941778, -1.2813360843436923, -1.2142217629409073,
      -1.1467278088838317, -1.0788761720816673, -1.0106889125011558,
      -0.94218819281763688, -0.87339627099811334, -0.80433549289835082,
      -0.735028285311819, -0.66549714823217787, -0.59576464732190737,
      -0.52585340697343119, -0.45578610258275448, -0.38558545294116997,
      -0.31527421291164931, -0.24487516618439364, -0.17441111754743871,
      -0.1039048852893136, -0.033379293958591565, 0.037142833153392632,
      0.10763868167438469, 0.17808545353186592, 0.24846037421560305,
      0.31874070055416104, 0.38890372807856594, 0.45892679826994165,
      0.528787306106915, 0.5984627075423038, 0.66793052679316212,
      0.73716836349423853, 0.80615390017292954, 0.87486490971473074,
      0.94327926241910343, 1.0113749329779349, 1.0791300080629238,
      1.1465226933706352, 1.213531320448439, 1.2801343539770522,
      1.3463103988191902, 1.4120382068791928, 1.477296683839922,
      1.542064896230932, 1.6063220782081598, 1.6700476382345086,
      1.7332211656468512, 1.7958224373552261, 1.8578314245635559,
      1.9192282988656792, 1.9799934388718388, 2.0401074366488445,
      2.0995511037839147, 2.1583054775479522, 2.2163518271931886,
      2.2736716599570479, 2.3302467267239888, 2.3860590281375393,
      2.4410908204706558, 2.4953246211478297, 2.5487432141856794,
      2.6013296560139954, 2.6530672808909315, 2.7039397059084891,
      2.75393083641701, 2.8030248712441796, 2.8512063076378711,
      2.8984599460625433, 2.9447708951804445, 2.9901245765919113,
      3.034506729345519, 3.0779034144355446, 3.1203010193071812,
      3.1616862621393302, 3.2020461958502739, 3.2413682123155567,
      3.2796400463115365, 3.3168497793034919, 3.3529858431448338,
      3.3880370237311777, 3.4219924645002959, 3.4548416696679478,
      3.4865745075359023, 3.5171812136837595, 3.5466523939045849,
      3.5749790269757518, 3.6021524675555794, 3.628164448778048,
      3.6530070846342744, 3.6766728724126234, 3.6991546949878731,
      3.720445822889153, 3.7405399161884367, 3.759431026468393,
      3.777113598528218, 3.7935824719056019, 3.8088328823866986,
      3.8228604633351826, 3.8356612468605733, 3.8472316648659453,
      3.8575685500047268, 3.8666691364936172, 3.8745310607277825,
      3.881152361812799, 3.886531482020394, 3.8906672669915534,
      3.8935589658619087, 3.8952062312915254, 3.895609119315024,
      3.8947680890807237, 3.8926840024261793, 3.8893581233197079,
      3.8847921172553974, 3.8789880504343506, 3.8719483887901798,
      3.863675996958079, 3.8541741370458587, 3.8434464673810496,
      3.8314970410073879, 3.8183303040567993, 3.8039510941316612,
      3.7883646384036491, 3.7715765516245723, 3.7535928340883173,
      3.7344198693890958, 3.7140644220576795, 3.6925336351140703,
      3.6698350274327725, 3.6459764910980352, 3.6209662885251954,
      3.5948130494174881, 3.5675257678681609, 3.5391137991271227,
      3.5095868560987422, 3.4789550060684369, 3.4472286673010442,
      3.4144186050889096, 3.3805359280754508, 3.3455920846077452,
      3.3095988584964915, 3.2725683649072166, 3.23451304634528,
      3.1954456682882451, 3.1553793146597346, 3.1143273834303948,
      3.072303581992851, 3.0293219224651535, 2.9853967168232045,
      2.940542571977363, 2.8947743849681746, 2.8481073376978081,
      2.8005568917495789, 2.7521387832264019, 2.7028690173773207,
      2.6527638630653447, 2.6018398472913984, 2.5501137497214708,
      2.49760259694237, 2.4443236565048063, 2.3902944312321051, 2.33553265366251,
      2.2800562795162667, 2.2238834817695872, 2.1670326449330997,
      2.1095223585616334, 2.051371410953883, 1.9925987829489713,
      1.933223641774148, 1.8732653343503669, 1.8127433808487745,
      1.7516774683888499, 1.6900874443196683, 1.6279933095175072,
      1.5654152118309894, 1.5023734395360409, 1.4388884143465037,
      1.3749806846761707, 1.3106709189106227, 1.2459798985594173,
      1.1809285112971442, 1.1155377440038377, 1.0498286760728617,
      0.983822472318162, 0.91754037571489544, 0.85100370073629283,
      0.78423382655635709, 0.71725218937889612, 0.65008027560495008,
      0.58273961521667772, 0.51525177435433045, 0.44763834805972968,
      0.37992095345234767, 0.31212122281532695, 0.2442607962075235,
      0.17636131447919554, 0.10844441231898881, 0.040531711136116734,
      -0.027355188043154982, -0.0951947115535943, -0.16296531996409583,
      -0.23064551528587043, -0.29821384793542238, -0.36564892352831335,
      -0.43292940981592787, -0.50003404381689887, -0.56694163849370194,
      -0.63363108952402514, -0.70008138219338867, -0.76627159828510061,
      -0.83218092276586386, -0.89778864999926888, -0.96307419114087633,
      -1.0280170804966458, -1.0925969815895231, -1.1567936941427461,
      -1.2205871605289558, -1.2839574721497822, -1.346884875414107,
      -1.4093497783315, -1.4713327568944421, -1.5328145608909487,
      -1.5937761201160423, -1.6541985505056498, -1.7140631600629652,
      -1.7733514545704421, -1.8320451436316945, -1.8901261463894079,
      -1.94757659706892, -2.0043788506613796, -2.0605154884296479,
      -2.1159693234588448, -2.1707234057414611, -2.2247610275200977,
      -2.2780657288288748, -2.3306213021560604, -2.382411797402733,
      -2.4334215272770874, -2.4836350717908879, -2.5330372828461942,
      -2.5816132891194328, -2.6293485006424482, -2.6762286130553328,
      -2.7222396119195995, -2.7673677771378116, -2.8115996869728144,
      -2.8549222221526946, -2.8973225696447731, -2.93878822661698,
      -2.9793070042445438, -3.0188670309878796, -3.0574567563391817,
      -3.0950649542384183, -3.1316807262206425, -3.167293504523073,
      -3.2018930553352716, -3.2354694816745488, -3.26801322601448,
      -3.2995150731853031, -3.3299661529419256, -3.3593579424326609,
      -3.3876822683665964, -3.4149313094799965, -3.4410975986927452,
      -3.4661740247789248, -3.49015383446187, -3.5130306342230715,
      -3.5347983918339407, -3.5554514378256945, -3.5749844669266824,
      -3.5933925393878008, -3.6106710820199721, -3.62681588924012,
      -3.6418231240477494, -3.6556893186824757, -3.6684113753245211,
      -3.6799865666256295, -3.6904125360887612, -3.6996872983924938,
      -3.7078092394711644, -3.7147771166247612, -3.7205900583793712,
      -3.7252475642509029, -3.7287495044426233, -3.7310961194282828,
      -3.7322880193086365, -3.7323261830530203, -3.7312119578400282,
      -3.7289470579328552, -3.7255335636811524, -3.7209739204248558,
      -3.7152709370315486, -3.708427784573523, -3.7004479947224014,
      -3.6913354581156987, -3.6810944226207152, -3.6697294913528138,
      -3.6572456207452535, -3.6436481183412139, -3.6289426405984755,
      -3.6131351905917395, -3.5962321154468309, -3.57824010384596,
      -3.559166183276167, -3.5390177173007387, -3.5178024026418035,
      -3.4955282660899334, -3.4722036615321548, -3.4478372666736714,
      -3.4224380796206497, -3.396015415570242, -3.3685789034005773,
      -3.3401384817165916, -3.31070439531914, -3.2802871915983722,
      -3.2488977162838131, -3.2165471095431406, -3.1832468019256335,
      -3.1490085101999692, -3.1138442330558065, -3.0777662466775788,
      -3.0407871003609848, -3.0029196119547659, -2.9641768632331,
      -2.9245721952149317, -2.8841192034380239, -2.8428317330071167,
      -2.8007238736620428, -2.7578099548829424, -2.7141045407634312,
      -2.6696224247836366, -2.6243786246286653, -2.5783883770265077,
      -2.5316671323897797, -2.4842305491200007, -2.4360944883430178,
      -2.38727500867975, -2.3377883600969538, -2.2876509784445709,
      -2.2368794800998657, -2.1854906558822296, -2.1335014652352555,
      -2.0809290305216277, -2.02779063121281, -1.9741036977639825,
      -1.9198858056715502, -1.8651546695858399, -1.8099281372358775,
      -1.7542241832247547, -1.6980609029566136, -1.6414565066581139,
      -1.5844293130180991, -1.5269977430517445, -1.469180313859151,
      -1.4109956324404671, -1.3524623893677101, -1.293599352406499,
      -1.2344253605194464, -1.1749593173974089, -1.1152201848713699,
      -1.0552269768841274, -0.99499875339235089, -0.93455461343150181,
      -0.87391368897213528, -0.81309513894862251, -0.75211814256705356,
      -0.691001892916702, -0.62976559074886762, -0.56842843831953582,
      -0.50700963282340716, -0.4455283601375562, -0.38400378868458079,
      -0.32245506304452021, -0.26090129766441206, -0.19936157065066221,
      -0.13785491774682984, -0.076400325955240891, -0.015016727356329402,
      0.046277006864171452, 0.10746207255072589, 0.16851973875240758,
      0.22943135366826839, 0.29017835050678181, 0.3507422535430646,
      0.41110468421784219, 0.47124736679820983, 0.53115213387784932,
      0.59080093278390955, 0.65017583110826, 0.70925902196014423,
      0.76803282993986277, 0.82647971677074039, 0.88458228671634775,
      0.94232329182575081, 0.99968563753994788, 1.0566523880596437,
      1.1132067714662146, 1.1693321849018972, 1.2250121998592141,
      1.2802305671980536, 1.3349712219210503, 1.3892182883743793,
      1.4429560850360588, 1.4961691291848642, 1.5488421415994045,
      1.6009600513195563, 1.6525080001648227, 1.7034713469585991,
      1.7538356720831745, 1.8035867819580382, 1.8527107130018989,
      1.9011937355456725, 1.9490223584378656, 1.9961833327412397,
      2.0426636552745894, 2.088450572740963, 2.133531585398841,
      2.1778944505830089, 2.2215271860363348, 2.2644180734569903,
      2.3065556618531438, 2.3479287706357712, 2.3885264927099148,
      2.4283381975618821, 2.467353534165825, 2.5055624336607218,
      2.5429551121242331, 2.5795220732307409, 2.6152541107445697,
      2.6501423107651032, 2.6841780541845845, 2.7173530188716177,
      2.74965918154885, 2.78108881994266, 2.8116345147367761, 2.8412891511581821,
      2.8700459205118167, 2.8978983221083006, 2.9248401645333333,
      2.9508655667305392, 2.9759689595117069, 3.0001450866857935,
      3.0233890059118287, 3.0456960895754097, 3.0670620257380086,
      3.0874828187206442, 3.1069547896379111, 3.1254745769117243,
      3.1430391366311929, 3.1596457427902909, 3.1752919873052852,
      3.1899757801794508, 3.20369534943533, 3.2164492407752729,
      3.2282363173864703, 3.2390557595164706, 3.2489070639137054,
      3.2577900432929878, 3.2657048255042844, 3.2726518527510797,
      3.2786318806722146, 3.2836459771985491, 3.2876955215073922,
      3.2907822027412887, 3.2929080186007451, 3.2940752738931676,
      3.2942865790631961, 3.2935448484495984, 3.2918532984384257,
      3.289215445759456, 3.2856351054795234, 3.28111638887023,
      3.2756637012927583, 3.2692817399783416, 3.26197549161536,
      3.2537502299574692, 3.2446115133059981, 3.2345651817906678,
      3.2236173547354925, 3.2117744278377369, 3.1990430702112636,
      3.1854302214674681, 3.1709430886890608, 3.155589143154081,
      3.139376117109594, 3.1223120005836518, 3.104405037917116, 3.08566372418012,
      3.0660968017016859, 3.0457132564888507, 3.0245223144333067,
      3.002533437531782, 2.9797563200430059, 2.95620088455474,
      2.9318772779961768, 2.906795867585072, 2.8809672366612085,
      2.8544021804950526, 2.8271117020113414, 2.7991070075002, 2.770399502265545,
      2.7410007861037675, 2.7109226488571649, 2.6801770658195516,
      2.6487761932071372, 2.6167323634708142, 2.5840580804749043,
      2.5507660149549625, 2.5168689995759257, 2.4823800240712486,
      2.4473122304524439, 2.4116789080455119, 2.375493488454234,
      2.33876954057281, 2.3015207657471159, 2.26376099245789, 2.2255041712205745,
      2.1867643696142158, 2.1475557670237246, 2.1078926494545462,
      2.0677894043397136, 2.0272605152821908, 1.9863205568291555,
      1.9449841891800628, 1.9032661528640322, 1.8611812635628009,
      1.8187444066611491, 1.7759705319445374, 1.732874648298214,
      1.6894718183386419, 1.6457771531414718, 1.6018058067224903,
      1.5575729708622976, 1.5130938697256002, 1.4683837543730907,
      1.4234578975345717, 1.3783315883182223, 1.3330201267586168,
      1.2875388184766465, 1.2419029696031856, 1.1961278812955756,
      1.1502288443693853, 1.1042211342516275, 1.0581200056990596,
      1.0119406874595109, 0.96569837712807027, 0.91940823600903132,
      0.87308538403820446, 0.8267448944854604, 0.7804017889011583,
      0.73407103227343573, 0.68776752777336769, 0.64150611192198526,
      0.59530154947003022, 0.549168528576916, 0.50312165610163462,
      0.45717545244310243, 0.4113443470664534, 0.36564267361311686,
      0.32008466516160866, 0.2746844497049597, 0.22945604552498688,
      0.18441335660090269, 0.13957016806815123, 0.094940142025070423,
      0.050536812896407844, 0.0063735831944079753, -0.037536280662187858,
      -0.081179652696851748, -0.12454355138298555, -0.16761514379499287,
      -0.21038174961024897, -0.25283084497453295, -0.29495006653891892,
      -0.33672721525491328, -0.378150259903606, -0.41920734094846651,
      -0.45988677414600693, -0.50017705405427337, -0.54006685745818839,
      -0.57954504669376472, -0.618600673102334, -0.65722298010970914,
      -0.69540140641682169, -0.73312558916303516, -0.77038536682230685,
      -0.80717078202664094, -0.84347208461139211, -0.87927973429321116,
      -0.914584403091709, -0.94937697818685352, -0.98364856437886827,
      -1.0173904863947976, -1.0505942911791211, -1.0832517502944237,
      -1.1153548620088565, -1.1468958531392759, -1.1778671812895853,
      -1.2082615367085028, -1.2380718439462022, -1.2672912635775462,
      -1.2959131939331345, -1.3239312724578829, -1.3513393772576721,
      -1.3781316284839322, -1.4043023893221063, -1.4298462674531358,
      -1.4547581159166634, -1.4790330340886486, -1.5026663687665129,
      -1.5256537146733131, -1.5479909152227989, -1.5696740632831665,
      -1.5906995015749887, -1.6110638229566832, -1.6307638709012877,
      -1.6497967397561393, -1.668159774723601, -1.685850571977779,
      -1.7028669787171908, -1.7192070929206971, -1.7348692630648348,
      -1.7498520878068287, -1.7641544157477027, -1.7777753448631353,
      -1.79071422167894, -1.8029706408172748, -1.8145444442152876,
      -1.8254357202629079, -1.8356448026985608, -1.8451722696594957,
      -1.8540189427372074, -1.8621858854567972, -1.8696744021882326,
      -1.8764860367177238, -1.8826225707431046, -1.88808602234971,
      -1.8928786443845451, -1.8970029228366507, -1.9004615747839864,
      -1.9032575467490505, -1.905394012695429, -1.9068743719108678,
      -1.9077022470173859, -1.9078814816876528, -1.9074161384719752,
      -1.9063104962847317, -1.9045690481190554, -1.9021964987304369,
      -1.8991977617961191, -1.8955779573393798, -1.8913424091461866,
      -1.8864966419454836, -1.8810463786195066, -1.8749975372590277,
      -1.868356228153035, -1.8611287508958028, -1.8533215912986685,
      -1.8449414180733097, -1.8359950797392723, -1.8264896014517307,
      -1.8164321815403497, -1.8058301882149181, -1.794691156131808,
      -1.7830227828148018, -1.7708329252608861, -1.758129596372078,
      -1.7449209611967398, -1.7312153332968858, -1.7170211711390471,
      -1.7023470742128706, -1.6872017792130709, -1.6715941563439496,
      -1.6555332053159335, -1.6390280513756839, -1.6220879414691871,
      -1.6047222402638877, -1.5869404260158235, -1.5687520865376212,
      -1.5501669152124362, -1.5311947067648359, -1.5118453531893314,
      -1.4921288396003234, -1.4720552399855655, -1.4516347130578204,
      -1.4308774979826862, -1.4097939102201462, -1.3883943371784979,
      -1.3666892339248586, -1.3446891189772847, -1.3224045699661857,
      -1.2998462193620215, -1.2770247500873719, -1.2539508912172121,
      -1.2306354136957447, -1.2070891260152443, -1.1833228698216409,
      -1.1593475155525161, -1.1351739582338634, -1.1108131130727537,
      -1.0862759111363489, -1.0615732950702219, -1.0367162147222042,
      -1.011715622964577, -0.98658247133735866, -0.96132770574135118,
      -0.935962262268481, -0.91049706289873589, -0.88494301132117525,
      -0.85931098871842326, -0.83361184955862533, -0.80785641750946857,
      -0.78205548121522839, -0.75621979023169306, -0.73036005104279744,
      -0.70448692284289216, -0.67861101357982934, -0.65274287604761982,
      -0.626893003816601, -0.60107182737877018, -0.57528971027567521,
      -0.54955694520799692, -0.52388375025360656, -0.49828026508216222,
      -0.47275654727509842, -0.44732256863690684, -0.42198821148196547,
      -0.3967632651213378, -0.371657422324528, -0.34668027578012478,
      -0.32184131469216581, -0.29714992130948159, -0.27261536766632927,
      -0.24824681233105414, -0.22405329701603505, -0.20004374349155291,
      -0.17622695050676115, -0.15261159064499422, -0.12920620735490937,
      -0.10601921199726809, -0.083058880970270477, -0.060333352861489838,
      -0.037850625687852718, -0.015618554274341225, 0.0063551524994821772,
      0.028062934218642852, 0.049497381353628633, 0.070651237812917447,
      0.091517403256193577, 0.11208893536507852, 0.13235905211684279,
      0.15232113391520966, 0.17196872566069918, 0.19129553880367486,
      0.21029545326956728, 0.22896251929861378, 0.24729095929433259,
      0.26527516948983154, 0.28290972161061406, 0.30018936449606265,
      0.31710902551502895, 0.33366381202044659, 0.34984901271513708,
      0.36566009889550888, 0.38109272562538132, 0.39614273286471835,
      0.41080614653856196, 0.42507917941119955, 0.43895823202349743,
      0.4524398935126086, 0.46552094226050855, 0.47819834660458493,
      0.49046926535569541, 0.50233104829213548, 0.51378123659853159,
      0.52481756315783124, 0.535437952818291, 0.54564052252341,
      0.55542358147369841, 0.56478563108533031, 0.57372536491076243,
      0.58224166858358561, 0.5903336194807125, 0.59800048649752158,
      0.60524172965428547, 0.61205699960329207, 0.61844613716824415,
      0.62440917269032126, 0.62994632534454809, 0.63505800237620325,
      0.63974479828368591, 0.6440074938929562, 0.64784705540690468,
      0.65126463328670869, 0.654261561145262, 0.65683935460694742,
      0.65899970991992241, 0.66074450266853713, 0.66207578636071129,
      0.66299579094100725, 0.66350692123465294, 0.66361175524304,
      0.6633130425475412, 0.66261370253928742, 0.66151682253937127,
      0.66002565594583429, 0.65814362025298812, 0.65587429504301875,
      0.65322141989623828, 0.65018889229664922, 0.64678076534516082,
      0.64300124551155613, 0.63885469039712273, 0.6343456062257995,
      0.62947864547416221, 0.6242586044003231, 0.61869042046638767,
      0.61277916969184809, 0.606530064069995, 0.59994844893121413,
      0.59303979992822176, 0.58580972045643442, 0.57826393887907823,
      0.570408305333749, 0.56224878901003517, 0.55379147516800986,
      0.54504256196630985, 0.536008357516698, 0.52669527677743788,
      0.51710983835941959, 0.50725866129033259, 0.49714846188155754,
      0.48678605049148266, 0.47617832813431116, 0.46533228329317133,
      0.45425498847023732, 0.44295359673368218, 0.43143533852028576,
      0.41970751815891333, 0.40777751023958791, 0.39565275624488538,
      0.38334076113923349, 0.37084908968856534, 0.35818536299742859,
      0.34535725497786873, 0.33237248872942954, 0.31923883294872324,
      0.3059640983327348, 0.2925561340616632, 0.27902282401183376,
      0.26537208320133188, 0.25161185422029175, 0.23775010347167921,
      0.22379481763625453, 0.20975399994406121, 0.19563566648395925,
      0.18144784269259026, 0.16719855966630054, 0.15289585040768236,
      0.13854774626787542, 0.12416227335229195, 0.10974744886314647,
      0.095311277428163726, 0.080861747525644623, 0.066406828004853008,
      0.051954464396209987, 0.037512575312705874, 0.023089048985553355,
      0.0086917397495986665, -0.005671535512379154, -0.019993000853759251,
      -0.034264924707041351, -0.048479623315223964, -0.0626294641675767,
      -0.076706869407419914, -0.0907043191183987, -0.10461435471557175,
      -0.11842958223816183, -0.13214267556913437, -0.14574637973885951,
      -0.15923351411262976, -0.17259697549122052, -0.18582974125769933,
      -0.1989248725103949, -0.21187551710212146, -0.22467491260592312,
      -0.2373163892465894, -0.2497933729314184, -0.26209938808198224,
      -0.274228060399018, -0.2861731197234671, -0.29792840270771664,
      -0.30948785557944025, -0.3208455367614394, -0.33199561933080779,
      -0.34293239371265033, -0.35365027013291367, -0.36414378093098609,
      -0.37440758303976496, -0.38443646027954126, -0.39422532558232587,
      -0.40376922320438685, -0.41306333087959207, -0.42210296190463636,
      -0.43088356709299558, -0.43940073682359992, -0.44765020290440088,
      -0.45562784034449411, -0.46332966921249513, -0.47075185633296024,
      -0.47789071685574358, -0.48474271586711665, -0.49130446994612725,
      -0.49757274853348016, -0.50354447534763891, -0.50921672967554321,
      -0.51458674761419843, -0.51965192325841014, -0.52440980976224538,
      -0.52885812040021374, -0.53299472952408355, -0.53681767340609843,
      -0.54032515113269342, -0.54351552533140735, -0.54638732274461344,
      -0.54893923500278907, -0.55117011904071067, -0.55307899754712153,
      -0.55466505945638633, -0.55592766014469641, -0.55686632173481831,
      -0.55748073326869074, -0.55777075076537552, -0.55773639727587809,
      -0.5573778628487307, -0.5566955043528875, -0.55568984529178744,
      -0.55436157559212584, -0.55271155125216209, -0.55074079385932906,
      -0.54845049015985881, -0.5458419915055589, -0.54291681319062024,
      -0.53967663382940489, -0.53612329448155038, -0.53225879783571683,
      -0.5280853073919235, -0.523605146381967, -0.5188207967010916,
      -0.51373489788566473, -0.50835024582698263, -0.50266979153591984,
      -0.49669663992051244, -0.4904340482045057, -0.48388542458812484,
      -0.47705432674962472, -0.46994446012473573, -0.46255967639521073,
      -0.45490397168836683, -0.44698148475687727, -0.43879649521069947,
      -0.43035342157376827, -0.42165681935386123, -0.41271137893041421,
      -0.40352192348493438, -0.39409340693298828, -0.38443091162356213,
      -0.37453964613715329, -0.36442494293126981, -0.35409225594560034,
      -0.34354715822861076, -0.33279533944942391, -0.32184260333191489,
      -0.31069486505110011, -0.29935814866767441, -0.28783858438686866,
      -0.27614240586006955, -0.2642759473758447, -0.25224564104919783,
      -0.24005801398664328, -0.22771968529900835, -0.21523736323803874,
      -0.20261784213383305, -0.1898679993744905, -0.17699479235689475,
      -0.16400525533407168, -0.15090649635005893, -0.1377056939801351,
      -0.12441009407893459, -0.11102700666565755, -0.097563802606841915,
      -0.084027910243205231, -0.070426812073036527, -0.056768041428725276,
      -0.04305917910085813, -0.02930784988308878, -0.01552171917940137,
      -0.0017084895087560534, 0.012124102962696429, 0.025968291869627458,
      0.039816284154727835, 0.053660263657714681, 0.067492394624215357,
      0.081304825209970247, 0.095089691130038151, 0.10883911913839676,
      0.1225452306469253, 0.13620014536808736, 0.14979598481568893,
      0.16332487588367126, 0.17677895452828762, 0.19015036941569471,
      0.20343128536204919, 0.21661388696915018, 0.22969038231513905,
      0.24265300644644677, 0.25549402498327145, 0.26820573773453943,
      0.28078048218689916, 0.29321063706571132, 0.30548862592739934,
      0.31760692067507573, 0.329558045018566, 0.3413345780012445,
      0.35292915749886361, 0.3643344835507914, 0.375543321986797,
      0.38654850777525623, 0.39734294821601335, 0.40791962654386821,
      0.41827160521703188, 0.42839202912538732, 0.43827412893273177,
      0.44791122434330849, 0.4572967272642649, 0.46642414500023777,
      0.47528708343895981, 0.48387925008952704, 0.4921944572011881,
      0.50022662477557822, 0.50796978355251965, 0.51541807804036377,
      0.52256576929882725, 0.52940723784026866, 0.53593698649754928,
      0.54214964314405312, 0.54803996348276129, 0.5536028336395008,
      0.55883327278740835, 0.56372643578663983, 0.56827761571012414,
      0.57248224628076672, 0.57633590419207115, 0.57983431164342025,
      0.5829733385676299, 0.5857490047817242, 0.58815748234633269,
      0.59019509755955679, 0.59185833304889213, 0.5931438298528966,
      0.59404838927782877, 0.59456897479984472, 0.59470271391882779,
      0.59444689984813648, 0.59379899326586238, 0.592756623915583,
      0.59131759209021573, 0.5894798702377223, 0.58724160429283034,
      0.58460111502794121, 0.58155689941721533, 0.57810763173906909,
      0.57425216473730079, 0.56998953072598013, 0.565318942568085,
      0.56023979460253659, 0.55475166343031956, 0.54885430876775809,
      0.54254767413991745, 0.53583188744712562, 0.52870726158063008,
      0.52117429485023514, 0.51323367139590725, 0.50488626158475791,
      0.49613312217091454, 0.48697549644007365, 0.47741481444312539,
      0.46745269292638475, 0.45709093524916872, 0.44633153133357395,
      0.43517665739180683, 0.42362867566705031, 0.41169013406280086,
      0.39936376570454263, 0.38665248843834782, 0.37355940419094114,
      0.36008779837228072, 0.34624113908978033, 0.332023076265467,
      0.31743744084934672, 0.30248824383073641, 0.28717967508830933,
      0.27151610233363183, 0.2555020699333026, 0.23914229760392214,
      0.22244167906638526, 0.20540528059332674, 0.1880383395874789,
      0.17034626294266333, 0.15233462542008822, 0.13400916796920828,
      0.11537579587770908, 0.096440576973152281, 0.077209739693389054,
      0.0576896710635681, 0.037886914592278581, 0.017808168245592549,
      -0.0025397178099018634, -0.023149743523239442, -0.04401476119691116,
      -0.065127477975049364, -0.086480458246221872, -0.10806612618208764,
      -0.12987676836274109, -0.15190453635294857, -0.17414144948935906,
      -0.19657939764314988, -0.21921014401346292, -0.24202532803900378,
      -0.26501646829714132, -0.28817496559364669, -0.31149210600324412,
      -0.3349590638968144, -0.35856690515091788, -0.38230659038409037,
      -0.40616897825213777, -0.43014482864250714, -0.78265203464144006,
      -1.7940318874149688, -2.809957939381, -3.1717808999144581,
      -3.2044142764416059, -3.2351411794039522, -3.2638932872232105,
      -3.2906036477512814, -3.3152068121757057, -3.3376389680207819,
      -3.3578380713374152, -3.3757439773619895, -3.3912985696389675,
      -3.4044458874606169, -3.4151322510761535, -3.4233063846845577,
      -3.4289195370693148, -3.431925599373812, -3.4322812197691657,
      -3.4299459150923037, -3.4248821790779158, -3.4170555868014216,
      -3.406434895410074, -3.3929921406911592, -3.3767027294613223,
      -3.3575455273418147, -3.3355029420269178, -3.3105610017571157,
      -3.2827094284827751, -3.2519417061856153, -3.2182551435912994,
      -3.181650931493154, -3.1421341944232744, -3.0997140363804516,
      -3.0544035808373269, -3.0062200045395588, -2.9551845652415882,
      -2.9013226230835194, -2.8446636555974454, -2.7852412663965027,
      -2.7230931873058655, -2.6582612737135149, -2.5907914935536787,
      -2.5207339095443797, -2.4481426545034903, -2.3730759002666808,
      -2.2955958196927906, -2.2157685418478983, -2.1336641006012078,
      -2.0493563765652829, -1.962923032099015, -1.874445440029977,
      -1.7840086057197826, -1.6917010823539607, -1.5976148801633678,
      -1.5018453692242515, -1.4044911760489411, -1.3056540738566047,
      -1.205438867184542, -1.1039532705126489, -1.0013077810242401,
      -0.89761554614768668, -0.792992225356365, -0.68755584697296834,
      -0.581426659974428, -0.47472698085964454, -0.36758103582386853,
      -0.260114798669725, -0.15245582455636666, -0.044733079553328343,
      0.062923233311308571, 0.17038185161772165, 0.27751063434084439,
      0.38417674550118286, 0.4902468406017168, 0.59558725559692038,
      0.70006419787843988, 0.80354393911758515, 0.90589300982036591,
      1.0069783951597182, 1.1066677317002518, 1.2048295048319506,
      1.3013332468554129, 1.3960497348030363, 1.4888511881500739,
      1.5796114662135823, 1.6682062644337492, 1.7545133096267524,
      1.8384125538358722, 1.9197863662805146, 1.9985197232518,
      2.0745003957995056, 2.1476191344453124, 2.2177698509699333,
      2.284849797066606, 2.3487597391809669, 2.4094041295304529,
      2.466691272937124, 2.5205334891475233, 2.5708472703574214,
      2.6175534338497068, 2.6605772691769682, 2.6998486797269869,
      2.735302318667812, 2.766877718640063, 2.7945194151910422,
      2.8181770636728425, 2.8378055493635586, 2.8533650905822823,
      2.8648213346135267, 2.8721454462958373, 2.8753141889763802,
      2.8743099977753208, 2.8691210449136197, 2.85974129698946,
      2.8461705640596016, 2.8284145404268206, 2.8064848369424564,
      2.7803990047581086, 2.7501805505078667, 2.7158589427292874,
      2.6774696095063351, 2.6350539273004436, 2.5886592009140865,
      2.538338634532983, 2.4841512939253354, 2.4261620596836222,
      2.3644415715708638, 2.2990661640777166, 2.2301177931127727,
      2.15768395394826, 2.081857590475849, 2.0027369958889039, 1.92042570483291,
      1.8350323771639632, 1.7466706734754074, 1.65545912246232,
      1.5615209803275778, 1.4649840823791129, 1.3659806869880351,
      1.2646473121034887, 1.1611245645382202, 1.0555569622187591,
      0.94809274963486, 0.83888370673897639, 0.72808495152599539,
      0.61585473656199052, 0.50235423973378013, 0.38774734949869394,
      0.27220044492267004, 0.14611458148274178, 0.078016227822648415 } ;

    TRACKING_CONTROL_KPES_DW.FromWorkspace2_PWORK.TimePtr = (void *)
      pTimeValues0;
    TRACKING_CONTROL_KPES_DW.FromWorkspace2_PWORK.DataPtr = (void *)
      pDataValues0;
    TRACKING_CONTROL_KPES_DW.FromWorkspace2_IWORK.PrevIndex = 0;
  }

  /* Start for DiscretePulseGenerator: '<Root>/Pulse Generator' */
  TRACKING_CONTROL_KPES_DW.clockTickCounter = 0;

  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: TRACKING_CONTROL_KPES/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8", "0", &TRACKING_CONTROL_KPES_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(TRACKING_CONTROL_KPES_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options
      (TRACKING_CONTROL_KPES_DW.HILInitialize_Card, " ", 2);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(TRACKING_CONTROL_KPES_M, _rt_error_message);
      return;
    }

    if ((TRACKING_CONTROL_KPES_P.HILInitialize_CKPStart && !is_switching) ||
        (TRACKING_CONTROL_KPES_P.HILInitialize_CKPEnter && is_switching)) {
      result = hil_set_clock_mode(TRACKING_CONTROL_KPES_DW.HILInitialize_Card,
        (t_clock *) TRACKING_CONTROL_KPES_P.HILInitialize_CKChannels, 2U,
        (t_clock_mode *) TRACKING_CONTROL_KPES_P.HILInitialize_CKModes);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(TRACKING_CONTROL_KPES_M, _rt_error_message);
        return;
      }
    }

    result = hil_watchdog_clear(TRACKING_CONTROL_KPES_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(TRACKING_CONTROL_KPES_M, _rt_error_message);
      return;
    }

    if ((TRACKING_CONTROL_KPES_P.HILInitialize_AIPStart && !is_switching) ||
        (TRACKING_CONTROL_KPES_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums =
          &TRACKING_CONTROL_KPES_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (TRACKING_CONTROL_KPES_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums =
          &TRACKING_CONTROL_KPES_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = TRACKING_CONTROL_KPES_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges
        (TRACKING_CONTROL_KPES_DW.HILInitialize_Card,
         TRACKING_CONTROL_KPES_P.HILInitialize_AIChannels, 8U,
         &TRACKING_CONTROL_KPES_DW.HILInitialize_AIMinimums[0],
         &TRACKING_CONTROL_KPES_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(TRACKING_CONTROL_KPES_M, _rt_error_message);
        return;
      }
    }

    if ((TRACKING_CONTROL_KPES_P.HILInitialize_AOPStart && !is_switching) ||
        (TRACKING_CONTROL_KPES_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums =
          &TRACKING_CONTROL_KPES_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (TRACKING_CONTROL_KPES_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums =
          &TRACKING_CONTROL_KPES_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = TRACKING_CONTROL_KPES_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges
        (TRACKING_CONTROL_KPES_DW.HILInitialize_Card,
         TRACKING_CONTROL_KPES_P.HILInitialize_AOChannels, 8U,
         &TRACKING_CONTROL_KPES_DW.HILInitialize_AOMinimums[0],
         &TRACKING_CONTROL_KPES_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(TRACKING_CONTROL_KPES_M, _rt_error_message);
        return;
      }
    }

    if ((TRACKING_CONTROL_KPES_P.HILInitialize_AOStart && !is_switching) ||
        (TRACKING_CONTROL_KPES_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &TRACKING_CONTROL_KPES_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = TRACKING_CONTROL_KPES_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(TRACKING_CONTROL_KPES_DW.HILInitialize_Card,
        TRACKING_CONTROL_KPES_P.HILInitialize_AOChannels, 8U,
        &TRACKING_CONTROL_KPES_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(TRACKING_CONTROL_KPES_M, _rt_error_message);
        return;
      }
    }

    if (TRACKING_CONTROL_KPES_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &TRACKING_CONTROL_KPES_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = TRACKING_CONTROL_KPES_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (TRACKING_CONTROL_KPES_DW.HILInitialize_Card,
         TRACKING_CONTROL_KPES_P.HILInitialize_AOChannels, 8U,
         &TRACKING_CONTROL_KPES_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(TRACKING_CONTROL_KPES_M, _rt_error_message);
        return;
      }
    }

    result = hil_set_digital_directions
      (TRACKING_CONTROL_KPES_DW.HILInitialize_Card,
       TRACKING_CONTROL_KPES_P.HILInitialize_DIChannels, 8U,
       TRACKING_CONTROL_KPES_P.HILInitialize_DOChannels, 9U);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(TRACKING_CONTROL_KPES_M, _rt_error_message);
      return;
    }

    if ((TRACKING_CONTROL_KPES_P.HILInitialize_DOStart && !is_switching) ||
        (TRACKING_CONTROL_KPES_P.HILInitialize_DOEnter && is_switching)) {
      {
        int_T i1;
        boolean_T *dw_DOBits = &TRACKING_CONTROL_KPES_DW.HILInitialize_DOBits[0];
        for (i1=0; i1 < 9; i1++) {
          dw_DOBits[i1] = TRACKING_CONTROL_KPES_P.HILInitialize_DOInitial;
        }
      }

      result = hil_write_digital(TRACKING_CONTROL_KPES_DW.HILInitialize_Card,
        TRACKING_CONTROL_KPES_P.HILInitialize_DOChannels, 9U, (t_boolean *)
        &TRACKING_CONTROL_KPES_DW.HILInitialize_DOBits[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(TRACKING_CONTROL_KPES_M, _rt_error_message);
        return;
      }
    }

    if (TRACKING_CONTROL_KPES_P.HILInitialize_DOReset) {
      {
        int_T i1;
        int32_T *dw_DOStates = &TRACKING_CONTROL_KPES_DW.HILInitialize_DOStates
          [0];
        for (i1=0; i1 < 9; i1++) {
          dw_DOStates[i1] = TRACKING_CONTROL_KPES_P.HILInitialize_DOWatchdog;
        }
      }

      result = hil_watchdog_set_digital_expiration_state
        (TRACKING_CONTROL_KPES_DW.HILInitialize_Card,
         TRACKING_CONTROL_KPES_P.HILInitialize_DOChannels, 9U, (const
          t_digital_state *) &TRACKING_CONTROL_KPES_DW.HILInitialize_DOStates[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(TRACKING_CONTROL_KPES_M, _rt_error_message);
        return;
      }
    }

    if ((TRACKING_CONTROL_KPES_P.HILInitialize_EIPStart && !is_switching) ||
        (TRACKING_CONTROL_KPES_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &TRACKING_CONTROL_KPES_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] =
            TRACKING_CONTROL_KPES_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (TRACKING_CONTROL_KPES_DW.HILInitialize_Card,
         TRACKING_CONTROL_KPES_P.HILInitialize_EIChannels, 8U,
         (t_encoder_quadrature_mode *)
         &TRACKING_CONTROL_KPES_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(TRACKING_CONTROL_KPES_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_FilterFrequency =
          &TRACKING_CONTROL_KPES_DW.HILInitialize_FilterFrequency[0];
        for (i1=0; i1 < 8; i1++) {
          dw_FilterFrequency[i1] =
            TRACKING_CONTROL_KPES_P.HILInitialize_EIFrequency;
        }
      }

      result = hil_set_encoder_filter_frequency
        (TRACKING_CONTROL_KPES_DW.HILInitialize_Card,
         TRACKING_CONTROL_KPES_P.HILInitialize_EIChannels, 8U,
         &TRACKING_CONTROL_KPES_DW.HILInitialize_FilterFrequency[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(TRACKING_CONTROL_KPES_M, _rt_error_message);
        return;
      }
    }

    if ((TRACKING_CONTROL_KPES_P.HILInitialize_EIStart && !is_switching) ||
        (TRACKING_CONTROL_KPES_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &TRACKING_CONTROL_KPES_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] =
            TRACKING_CONTROL_KPES_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts
        (TRACKING_CONTROL_KPES_DW.HILInitialize_Card,
         TRACKING_CONTROL_KPES_P.HILInitialize_EIChannels, 8U,
         &TRACKING_CONTROL_KPES_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(TRACKING_CONTROL_KPES_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_write_digital_timebase_block): '<Root>/HIL Write Digital Timebase' */

  /* S-Function Block: TRACKING_CONTROL_KPES/HIL Write Digital Timebase (hil_write_digital_timebase_block) */
  {
    t_error result;
    TRACKING_CONTROL_KPES_DW.HILWriteDigitalTimebase_Started = false;
    result = hil_task_create_digital_writer
      (TRACKING_CONTROL_KPES_DW.HILInitialize_Card,
       TRACKING_CONTROL_KPES_P.HILWriteDigitalTimebase_samples,
       &TRACKING_CONTROL_KPES_P.HILWriteDigitalTimebase_channel, 1,
       &TRACKING_CONTROL_KPES_DW.HILWriteDigitalTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(TRACKING_CONTROL_KPES_M, _rt_error_message);
    }
  }

  /* InitializeConditions for UnitDelay: '<Root>/Unit Delay2' */
  TRACKING_CONTROL_KPES_DW.UnitDelay2_DSTATE =
    TRACKING_CONTROL_KPES_P.UnitDelay2_InitialCondition;

  /* InitializeConditions for UnitDelay: '<Root>/Unit Delay3' */
  TRACKING_CONTROL_KPES_DW.UnitDelay3_DSTATE =
    TRACKING_CONTROL_KPES_P.UnitDelay3_InitialCondition;

  /* InitializeConditions for UnitDelay: '<Root>/Unit Delay' */
  TRACKING_CONTROL_KPES_DW.UnitDelay_DSTATE[0] =
    TRACKING_CONTROL_KPES_P.UnitDelay_InitialCondition;
  TRACKING_CONTROL_KPES_DW.UnitDelay_DSTATE[1] =
    TRACKING_CONTROL_KPES_P.UnitDelay_InitialCondition;

  /* InitializeConditions for UnitDelay: '<Root>/Unit Delay1' */
  TRACKING_CONTROL_KPES_DW.UnitDelay1_DSTATE =
    TRACKING_CONTROL_KPES_P.UnitDelay1_InitialCondition;

  /* InitializeConditions for UnitDelay: '<S17>/UD' */
  TRACKING_CONTROL_KPES_DW.UD_DSTATE =
    TRACKING_CONTROL_KPES_P.DiscreteDerivative3_ICPrevScale;

  /* InitializeConditions for UnitDelay: '<S14>/UD' */
  TRACKING_CONTROL_KPES_DW.UD_DSTATE_e =
    TRACKING_CONTROL_KPES_P.DiscreteDerivative_ICPrevScaled;

  /* InitializeConditions for UnitDelay: '<S16>/UD' */
  TRACKING_CONTROL_KPES_DW.UD_DSTATE_i =
    TRACKING_CONTROL_KPES_P.DiscreteDerivative2_ICPrevScale;

  /* InitializeConditions for DiscreteIntegrator: '<S4>/Discrete-Time Integrator' */
  TRACKING_CONTROL_KPES_DW.DiscreteTimeIntegrator_DSTATE =
    TRACKING_CONTROL_KPES_P.DiscreteTimeIntegrator_IC;

  /* InitializeConditions for UnitDelay: '<S15>/UD' */
  TRACKING_CONTROL_KPES_DW.UD_DSTATE_f =
    TRACKING_CONTROL_KPES_P.DiscreteDerivative1_ICPrevScale;

  /* InitializeConditions for UnitDelay: '<S21>/UD' */
  TRACKING_CONTROL_KPES_DW.UD_DSTATE_a =
    TRACKING_CONTROL_KPES_P.DiscreteDerivative3_ICPrevSca_k;

  /* InitializeConditions for UnitDelay: '<S18>/UD' */
  TRACKING_CONTROL_KPES_DW.UD_DSTATE_p =
    TRACKING_CONTROL_KPES_P.DiscreteDerivative_ICPrevScal_n;

  /* InitializeConditions for UnitDelay: '<S20>/UD' */
  TRACKING_CONTROL_KPES_DW.UD_DSTATE_az =
    TRACKING_CONTROL_KPES_P.DiscreteDerivative2_ICPrevSca_b;

  /* InitializeConditions for DiscreteIntegrator: '<S5>/Discrete-Time Integrator' */
  TRACKING_CONTROL_KPES_DW.DiscreteTimeIntegrator_DSTATE_m =
    TRACKING_CONTROL_KPES_P.DiscreteTimeIntegrator_IC_m;

  /* InitializeConditions for UnitDelay: '<S19>/UD' */
  TRACKING_CONTROL_KPES_DW.UD_DSTATE_i4 =
    TRACKING_CONTROL_KPES_P.DiscreteDerivative1_ICPrevSca_n;
}

/* Model terminate function */
void TRACKING_CONTROL_KPES_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: TRACKING_CONTROL_KPES/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_digital_outputs = 0;
    hil_task_stop_all(TRACKING_CONTROL_KPES_DW.HILInitialize_Card);
    hil_monitor_stop_all(TRACKING_CONTROL_KPES_DW.HILInitialize_Card);
    is_switching = false;
    if ((TRACKING_CONTROL_KPES_P.HILInitialize_AOTerminate && !is_switching) ||
        (TRACKING_CONTROL_KPES_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &TRACKING_CONTROL_KPES_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = TRACKING_CONTROL_KPES_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((TRACKING_CONTROL_KPES_P.HILInitialize_DOTerminate && !is_switching) ||
        (TRACKING_CONTROL_KPES_P.HILInitialize_DOExit && is_switching)) {
      {
        int_T i1;
        boolean_T *dw_DOBits = &TRACKING_CONTROL_KPES_DW.HILInitialize_DOBits[0];
        for (i1=0; i1 < 9; i1++) {
          dw_DOBits[i1] = TRACKING_CONTROL_KPES_P.HILInitialize_DOFinal;
        }
      }

      num_final_digital_outputs = 9U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_digital_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(TRACKING_CONTROL_KPES_DW.HILInitialize_Card
                         , TRACKING_CONTROL_KPES_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , NULL, 0
                         , TRACKING_CONTROL_KPES_P.HILInitialize_DOChannels,
                         num_final_digital_outputs
                         , NULL, 0
                         , &TRACKING_CONTROL_KPES_DW.HILInitialize_AOVoltages[0]
                         , NULL
                         , (t_boolean *)
                         &TRACKING_CONTROL_KPES_DW.HILInitialize_DOBits[0]
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog
            (TRACKING_CONTROL_KPES_DW.HILInitialize_Card,
             TRACKING_CONTROL_KPES_P.HILInitialize_AOChannels,
             num_final_analog_outputs,
             &TRACKING_CONTROL_KPES_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_digital_outputs > 0) {
          local_result = hil_write_digital
            (TRACKING_CONTROL_KPES_DW.HILInitialize_Card,
             TRACKING_CONTROL_KPES_P.HILInitialize_DOChannels,
             num_final_digital_outputs, (t_boolean *)
             &TRACKING_CONTROL_KPES_DW.HILInitialize_DOBits[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(TRACKING_CONTROL_KPES_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(TRACKING_CONTROL_KPES_DW.HILInitialize_Card);
    hil_monitor_delete_all(TRACKING_CONTROL_KPES_DW.HILInitialize_Card);
    hil_close(TRACKING_CONTROL_KPES_DW.HILInitialize_Card);
    TRACKING_CONTROL_KPES_DW.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  TRACKING_CONTROL_KPES_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  TRACKING_CONTROL_KPES_update();
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
  TRACKING_CONTROL_KPES_initialize();
}

void MdlTerminate(void)
{
  TRACKING_CONTROL_KPES_terminate();
}

/* Registration function */
RT_MODEL_TRACKING_CONTROL_KPE_T *TRACKING_CONTROL_KPES(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)TRACKING_CONTROL_KPES_M, 0,
                sizeof(RT_MODEL_TRACKING_CONTROL_KPE_T));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = TRACKING_CONTROL_KPES_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    TRACKING_CONTROL_KPES_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    TRACKING_CONTROL_KPES_M->Timing.sampleTimes =
      (&TRACKING_CONTROL_KPES_M->Timing.sampleTimesArray[0]);
    TRACKING_CONTROL_KPES_M->Timing.offsetTimes =
      (&TRACKING_CONTROL_KPES_M->Timing.offsetTimesArray[0]);

    /* task periods */
    TRACKING_CONTROL_KPES_M->Timing.sampleTimes[0] = (0.01);

    /* task offsets */
    TRACKING_CONTROL_KPES_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(TRACKING_CONTROL_KPES_M, &TRACKING_CONTROL_KPES_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = TRACKING_CONTROL_KPES_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    TRACKING_CONTROL_KPES_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(TRACKING_CONTROL_KPES_M, 31.0);
  TRACKING_CONTROL_KPES_M->Timing.stepSize0 = 0.01;

  /* External mode info */
  TRACKING_CONTROL_KPES_M->Sizes.checksums[0] = (554841894U);
  TRACKING_CONTROL_KPES_M->Sizes.checksums[1] = (3211381537U);
  TRACKING_CONTROL_KPES_M->Sizes.checksums[2] = (1727970566U);
  TRACKING_CONTROL_KPES_M->Sizes.checksums[3] = (3173861023U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[14];
    TRACKING_CONTROL_KPES_M->extModeInfo = (&rt_ExtModeInfo);
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
    rteiSetModelMappingInfoPtr(TRACKING_CONTROL_KPES_M->extModeInfo,
      &TRACKING_CONTROL_KPES_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(TRACKING_CONTROL_KPES_M->extModeInfo,
                        TRACKING_CONTROL_KPES_M->Sizes.checksums);
    rteiSetTPtr(TRACKING_CONTROL_KPES_M->extModeInfo, rtmGetTPtr
                (TRACKING_CONTROL_KPES_M));
  }

  TRACKING_CONTROL_KPES_M->solverInfoPtr = (&TRACKING_CONTROL_KPES_M->solverInfo);
  TRACKING_CONTROL_KPES_M->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&TRACKING_CONTROL_KPES_M->solverInfo, 0.01);
  rtsiSetSolverMode(&TRACKING_CONTROL_KPES_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  TRACKING_CONTROL_KPES_M->blockIO = ((void *) &TRACKING_CONTROL_KPES_B);
  (void) memset(((void *) &TRACKING_CONTROL_KPES_B), 0,
                sizeof(B_TRACKING_CONTROL_KPES_T));

  {
    int32_T i;
    for (i = 0; i < 10; i++) {
      TRACKING_CONTROL_KPES_B.VectorConcatenate[i] = 0.0;
    }

    TRACKING_CONTROL_KPES_B.UnaryMinus = 0.0;
    TRACKING_CONTROL_KPES_B.UnitDelay2 = 0.0;
    TRACKING_CONTROL_KPES_B.UnaryMinus1 = 0.0;
    TRACKING_CONTROL_KPES_B.UnitDelay3 = 0.0;
    TRACKING_CONTROL_KPES_B.FromWorkspace4[0] = 0.0;
    TRACKING_CONTROL_KPES_B.FromWorkspace4[1] = 0.0;
    TRACKING_CONTROL_KPES_B.TSamp = 0.0;
    TRACKING_CONTROL_KPES_B.TSamp_g = 0.0;
    TRACKING_CONTROL_KPES_B.Torquetocurrent = 0.0;
    TRACKING_CONTROL_KPES_B.TSamp_k = 0.0;
    TRACKING_CONTROL_KPES_B.Current = 0.0;
    TRACKING_CONTROL_KPES_B.Sum1 = 0.0;
    TRACKING_CONTROL_KPES_B.TSamp_e = 0.0;
    TRACKING_CONTROL_KPES_B.Saturation = 0.0;
    TRACKING_CONTROL_KPES_B.VectorConcatenate_j[0] = 0.0;
    TRACKING_CONTROL_KPES_B.VectorConcatenate_j[1] = 0.0;
    TRACKING_CONTROL_KPES_B.VectorConcatenate_j[2] = 0.0;
    TRACKING_CONTROL_KPES_B.VectorConcatenate_j[3] = 0.0;
    TRACKING_CONTROL_KPES_B.TSamp_gy = 0.0;
    TRACKING_CONTROL_KPES_B.TSamp_d = 0.0;
    TRACKING_CONTROL_KPES_B.Torquetocurrent_d = 0.0;
    TRACKING_CONTROL_KPES_B.TSamp_dk = 0.0;
    TRACKING_CONTROL_KPES_B.Current_c = 0.0;
    TRACKING_CONTROL_KPES_B.Sum1_l = 0.0;
    TRACKING_CONTROL_KPES_B.TSamp_i = 0.0;
    TRACKING_CONTROL_KPES_B.Saturation_h = 0.0;
    TRACKING_CONTROL_KPES_B.VectorConcatenate_g[0] = 0.0;
    TRACKING_CONTROL_KPES_B.VectorConcatenate_g[1] = 0.0;
    TRACKING_CONTROL_KPES_B.VectorConcatenate_g[2] = 0.0;
    TRACKING_CONTROL_KPES_B.VectorConcatenate_g[3] = 0.0;
    TRACKING_CONTROL_KPES_B.HILReadDigital_o1 = 0.0;
    TRACKING_CONTROL_KPES_B.HILReadDigital_o2 = 0.0;
    TRACKING_CONTROL_KPES_B.HILReadDigital_o3 = 0.0;
    TRACKING_CONTROL_KPES_B.phi_out = 0.0;
    TRACKING_CONTROL_KPES_B.xp_out[0] = 0.0;
    TRACKING_CONTROL_KPES_B.xp_out[1] = 0.0;
  }

  /* parameters */
  TRACKING_CONTROL_KPES_M->defaultParam = ((real_T *)&TRACKING_CONTROL_KPES_P);

  /* states (dwork) */
  TRACKING_CONTROL_KPES_M->dwork = ((void *) &TRACKING_CONTROL_KPES_DW);
  (void) memset((void *)&TRACKING_CONTROL_KPES_DW, 0,
                sizeof(DW_TRACKING_CONTROL_KPES_T));
  TRACKING_CONTROL_KPES_DW.UnitDelay2_DSTATE = 0.0;
  TRACKING_CONTROL_KPES_DW.UnitDelay3_DSTATE = 0.0;
  TRACKING_CONTROL_KPES_DW.UnitDelay_DSTATE[0] = 0.0;
  TRACKING_CONTROL_KPES_DW.UnitDelay_DSTATE[1] = 0.0;
  TRACKING_CONTROL_KPES_DW.UnitDelay1_DSTATE = 0.0;
  TRACKING_CONTROL_KPES_DW.UD_DSTATE = 0.0;
  TRACKING_CONTROL_KPES_DW.UD_DSTATE_e = 0.0;
  TRACKING_CONTROL_KPES_DW.UD_DSTATE_i = 0.0;
  TRACKING_CONTROL_KPES_DW.DiscreteTimeIntegrator_DSTATE = 0.0;
  TRACKING_CONTROL_KPES_DW.UD_DSTATE_f = 0.0;
  TRACKING_CONTROL_KPES_DW.UD_DSTATE_a = 0.0;
  TRACKING_CONTROL_KPES_DW.UD_DSTATE_p = 0.0;
  TRACKING_CONTROL_KPES_DW.UD_DSTATE_az = 0.0;
  TRACKING_CONTROL_KPES_DW.DiscreteTimeIntegrator_DSTATE_m = 0.0;
  TRACKING_CONTROL_KPES_DW.UD_DSTATE_i4 = 0.0;
  TRACKING_CONTROL_KPES_DW.HILReadAnalog_Buffer = 0.0;
  TRACKING_CONTROL_KPES_DW.HILReadAnalog_Buffer_g = 0.0;

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      TRACKING_CONTROL_KPES_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      TRACKING_CONTROL_KPES_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      TRACKING_CONTROL_KPES_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      TRACKING_CONTROL_KPES_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      TRACKING_CONTROL_KPES_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      TRACKING_CONTROL_KPES_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    TRACKING_CONTROL_KPES_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 17;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  TRACKING_CONTROL_KPES_M->Sizes.numContStates = (0);/* Number of continuous states */
  TRACKING_CONTROL_KPES_M->Sizes.numY = (0);/* Number of model outputs */
  TRACKING_CONTROL_KPES_M->Sizes.numU = (0);/* Number of model inputs */
  TRACKING_CONTROL_KPES_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  TRACKING_CONTROL_KPES_M->Sizes.numSampTimes = (1);/* Number of sample times */
  TRACKING_CONTROL_KPES_M->Sizes.numBlocks = (171);/* Number of blocks */
  TRACKING_CONTROL_KPES_M->Sizes.numBlockIO = (33);/* Number of block outputs */
  TRACKING_CONTROL_KPES_M->Sizes.numBlockPrms = (214);/* Sum of parameter "widths" */
  return TRACKING_CONTROL_KPES_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
