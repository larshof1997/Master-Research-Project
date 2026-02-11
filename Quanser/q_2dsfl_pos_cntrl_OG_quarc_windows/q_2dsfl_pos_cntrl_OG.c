/*
 * q_2dsfl_pos_cntrl_OG.c
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

#include "q_2dsfl_pos_cntrl_OG.h"
#include "q_2dsfl_pos_cntrl_OG_private.h"
#include "q_2dsfl_pos_cntrl_OG_dt.h"

/* Block signals (default storage) */
B_q_2dsfl_pos_cntrl_OG_T q_2dsfl_pos_cntrl_OG_B;

/* Continuous states */
X_q_2dsfl_pos_cntrl_OG_T q_2dsfl_pos_cntrl_OG_X;

/* Block states (default storage) */
DW_q_2dsfl_pos_cntrl_OG_T q_2dsfl_pos_cntrl_OG_DW;

/* Real-time model */
RT_MODEL_q_2dsfl_pos_cntrl_OG_T q_2dsfl_pos_cntrl_OG_M_;
RT_MODEL_q_2dsfl_pos_cntrl_OG_T *const q_2dsfl_pos_cntrl_OG_M =
  &q_2dsfl_pos_cntrl_OG_M_;

/*
 * Time delay interpolation routine
 *
 * The linear interpolation is performed using the formula:
 *
 *          (t2 - tMinusDelay)         (tMinusDelay - t1)
 * u(t)  =  ----------------- * u1  +  ------------------- * u2
 *              (t2 - t1)                  (t2 - t1)
 */
real_T rt_TDelayInterpolate(
  real_T tMinusDelay,                  /* tMinusDelay = currentSimTime - delay */
  real_T tStart,
  real_T *tBuf,
  real_T *uBuf,
  int_T bufSz,
  int_T *lastIdx,
  int_T oldestIdx,
  int_T newIdx,
  real_T initOutput,
  boolean_T discrete,
  boolean_T minorStepAndTAtLastMajorOutput)
{
  int_T i;
  real_T yout, t1, t2, u1, u2;

  /*
   * If there is only one data point in the buffer, this data point must be
   * the t= 0 and tMinusDelay > t0, it ask for something unknown. The best
   * guess if initial output as well
   */
  if ((newIdx == 0) && (oldestIdx ==0 ) && (tMinusDelay > tStart))
    return initOutput;

  /*
   * If tMinusDelay is less than zero, should output initial value
   */
  if (tMinusDelay <= tStart)
    return initOutput;

  /* For fixed buffer extrapolation:
   * if tMinusDelay is small than the time at oldestIdx, if discrete, output
   * tailptr value,  else use tailptr and tailptr+1 value to extrapolate
   * It is also for fixed buffer. Note: The same condition can happen for transport delay block where
   * use tStart and and t[tail] other than using t[tail] and t[tail+1].
   * See below
   */
  if ((tMinusDelay <= tBuf[oldestIdx] ) ) {
    if (discrete) {
      return(uBuf[oldestIdx]);
    } else {
      int_T tempIdx= oldestIdx + 1;
      if (oldestIdx == bufSz-1)
        tempIdx = 0;
      t1= tBuf[oldestIdx];
      t2= tBuf[tempIdx];
      u1= uBuf[oldestIdx];
      u2= uBuf[tempIdx];
      if (t2 == t1) {
        if (tMinusDelay >= t2) {
          yout = u2;
        } else {
          yout = u1;
        }
      } else {
        real_T f1 = (t2-tMinusDelay) / (t2-t1);
        real_T f2 = 1.0 - f1;

        /*
         * Use Lagrange's interpolation formula.  Exact outputs at t1, t2.
         */
        yout = f1*u1 + f2*u2;
      }

      return yout;
    }
  }

  /*
   * When block does not have direct feedthrough, we use the table of
   * values to extrapolate off the end of the table for delays that are less
   * than 0 (less then step size).  This is not completely accurate.  The
   * chain of events is as follows for a given time t.  Major output - look
   * in table.  Update - add entry to table.  Now, if we call the output at
   * time t again, there is a new entry in the table. For very small delays,
   * this means that we will have a different answer from the previous call
   * to the output fcn at the same time t.  The following code prevents this
   * from happening.
   */
  if (minorStepAndTAtLastMajorOutput) {
    /* pretend that the new entry has not been added to table */
    if (newIdx != 0) {
      if (*lastIdx == newIdx) {
        (*lastIdx)--;
      }

      newIdx--;
    } else {
      if (*lastIdx == newIdx) {
        *lastIdx = bufSz-1;
      }

      newIdx = bufSz - 1;
    }
  }

  i = *lastIdx;
  if (tBuf[i] < tMinusDelay) {
    /* Look forward starting at last index */
    while (tBuf[i] < tMinusDelay) {
      /* May occur if the delay is less than step-size - extrapolate */
      if (i == newIdx)
        break;
      i = ( i < (bufSz-1) ) ? (i+1) : 0;/* move through buffer */
    }
  } else {
    /*
     * Look backwards starting at last index which can happen when the
     * delay time increases.
     */
    while (tBuf[i] >= tMinusDelay) {
      /*
       * Due to the entry condition at top of function, we
       * should never hit the end.
       */
      i = (i > 0) ? i-1 : (bufSz-1);   /* move through buffer */
    }

    i = ( i < (bufSz-1) ) ? (i+1) : 0;
  }

  *lastIdx = i;
  if (discrete) {
    /*
     * tempEps = 128 * eps;
     * localEps = max(tempEps, tempEps*fabs(tBuf[i]))/2;
     */
    double tempEps = (DBL_EPSILON) * 128.0;
    double localEps = tempEps * fabs(tBuf[i]);
    if (tempEps > localEps) {
      localEps = tempEps;
    }

    localEps = localEps / 2.0;
    if (tMinusDelay >= (tBuf[i] - localEps)) {
      yout = uBuf[i];
    } else {
      if (i == 0) {
        yout = uBuf[bufSz-1];
      } else {
        yout = uBuf[i-1];
      }
    }
  } else {
    if (i == 0) {
      t1 = tBuf[bufSz-1];
      u1 = uBuf[bufSz-1];
    } else {
      t1 = tBuf[i-1];
      u1 = uBuf[i-1];
    }

    t2 = tBuf[i];
    u2 = uBuf[i];
    if (t2 == t1) {
      if (tMinusDelay >= t2) {
        yout = u2;
      } else {
        yout = u1;
      }
    } else {
      real_T f1 = (t2-tMinusDelay) / (t2-t1);
      real_T f2 = 1.0 - f1;

      /*
       * Use Lagrange's interpolation formula.  Exact outputs at t1, t2.
       */
      yout = f1*u1 + f2*u2;
    }
  }

  return(yout);
}

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 12;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  q_2dsfl_pos_cntrl_OG_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/*
 * System initialize for atomic system:
 *    '<S1>/Bias Removal'
 *    '<S2>/Bias Removal'
 */
void q_2dsfl_pos_cn_BiasRemoval_Init(B_BiasRemoval_q_2dsfl_pos_cnt_T *localB,
  DW_BiasRemoval_q_2dsfl_pos_cn_T *localDW, P_BiasRemoval_q_2dsfl_pos_cnt_T
  *localP)
{
  /* SystemInitialize for Enabled SubSystem: '<S9>/Enabled Moving Average' */
  /* InitializeConditions for UnitDelay: '<S16>/Unit Delay' */
  localDW->UnitDelay_DSTATE = localP->UnitDelay_InitialCondition;

  /* InitializeConditions for UnitDelay: '<S12>/Sum( k=1,n-1, x(k) )' */
  localDW->Sumk1n1xk_DSTATE = localP->Sumk1n1xk_InitialCondition;

  /* End of SystemInitialize for SubSystem: '<S9>/Enabled Moving Average' */

  /* SystemInitialize for IfAction SubSystem: '<S9>/Switch Case Action Subsystem' */
  /* SystemInitialize for Outport: '<S13>/zero' */
  localB->Constant = localP->zero_Y0;

  /* End of SystemInitialize for SubSystem: '<S9>/Switch Case Action Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S9>/Switch Case Action Subsystem1' */
  /* SystemInitialize for Outport: '<S14>/Vbiased' */
  localB->Vin = localP->Vbiased_Y0;

  /* End of SystemInitialize for SubSystem: '<S9>/Switch Case Action Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S9>/Switch Case Action Subsystem2' */
  /* SystemInitialize for Outport: '<S15>/Vunbiased' */
  localB->VVavg = localP->Vunbiased_Y0;

  /* End of SystemInitialize for SubSystem: '<S9>/Switch Case Action Subsystem2' */
}

/*
 * Start for atomic system:
 *    '<S1>/Bias Removal'
 *    '<S2>/Bias Removal'
 */
void q_2dsfl_pos_c_BiasRemoval_Start(DW_BiasRemoval_q_2dsfl_pos_cn_T *localDW)
{
  /* Start for Enabled SubSystem: '<S9>/Enabled Moving Average' */
  localDW->EnabledMovingAverage_MODE = false;

  /* End of Start for SubSystem: '<S9>/Enabled Moving Average' */

  /* Start for SwitchCase: '<S9>/Switch Case' */
  localDW->SwitchCase_ActiveSubsystem = -1;
}

/*
 * Outputs for atomic system:
 *    '<S1>/Bias Removal'
 *    '<S2>/Bias Removal'
 */
void q_2dsfl_pos_cntrl_O_BiasRemoval(RT_MODEL_q_2dsfl_pos_cntrl_OG_T * const
  q_2dsfl_pos_cntrl_OG_M, real_T rtu_V, B_BiasRemoval_q_2dsfl_pos_cnt_T *localB,
  DW_BiasRemoval_q_2dsfl_pos_cn_T *localDW, P_BiasRemoval_q_2dsfl_pos_cnt_T
  *localP, real_T rtp_switch_id, real_T rtp_start_time, real_T rtp_end_time)
{
  real_T rtb_Stepend_time;
  int8_T rtPrevAction;
  int8_T rtAction;
  real_T rtb_Sum;
  real_T tmp;

  /* Step: '<S9>/Step: end_time' incorporates:
   *  Step: '<S9>/Step: start_time'
   */
  tmp = q_2dsfl_pos_cntrl_OG_M->Timing.t[1];
  if (tmp < rtp_end_time) {
    rtb_Stepend_time = localP->Stepend_time_Y0;
  } else {
    rtb_Stepend_time = localP->Stepend_time_YFinal;
  }

  /* End of Step: '<S9>/Step: end_time' */

  /* Step: '<S9>/Step: start_time' */
  if (tmp < rtp_start_time) {
    tmp = localP->Stepstart_time_Y0;
  } else {
    tmp = localP->Stepstart_time_YFinal;
  }

  /* Outputs for Enabled SubSystem: '<S9>/Enabled Moving Average' incorporates:
   *  EnablePort: '<S12>/Enable'
   */
  /* Logic: '<S9>/Logical Operator' incorporates:
   *  Logic: '<S9>/Logical Operator1'
   */
  if ((tmp != 0.0) && (!(rtb_Stepend_time != 0.0))) {
    if (!localDW->EnabledMovingAverage_MODE) {
      /* InitializeConditions for UnitDelay: '<S16>/Unit Delay' */
      localDW->UnitDelay_DSTATE = localP->UnitDelay_InitialCondition;

      /* InitializeConditions for UnitDelay: '<S12>/Sum( k=1,n-1, x(k) )' */
      localDW->Sumk1n1xk_DSTATE = localP->Sumk1n1xk_InitialCondition;
      localDW->EnabledMovingAverage_MODE = true;
    }

    /* Sum: '<S16>/Count' incorporates:
     *  Constant: '<S16>/unity'
     *  UnitDelay: '<S16>/Unit Delay'
     */
    localB->Count = localP->unity_Value + localDW->UnitDelay_DSTATE;

    /* Sum: '<S12>/Sum' incorporates:
     *  UnitDelay: '<S12>/Sum( k=1,n-1, x(k) )'
     */
    localB->Sum = rtu_V + localDW->Sumk1n1xk_DSTATE;

    /* Product: '<S12>/div' */
    localB->div = localB->Sum / localB->Count;
    srUpdateBC(localDW->EnabledMovingAverage_SubsysRanB);
  } else {
    if (localDW->EnabledMovingAverage_MODE) {
      localDW->EnabledMovingAverage_MODE = false;
    }
  }

  /* End of Logic: '<S9>/Logical Operator' */
  /* End of Outputs for SubSystem: '<S9>/Enabled Moving Average' */

  /* Sum: '<S9>/Sum' */
  rtb_Sum = rtu_V - localB->div;

  /* SwitchCase: '<S9>/Switch Case' incorporates:
   *  Constant: '<S13>/Constant'
   *  Constant: '<S9>/Constant'
   *  Inport: '<S14>/Vin'
   *  Inport: '<S15>/V-Vavg'
   */
  rtPrevAction = localDW->SwitchCase_ActiveSubsystem;
  rtAction = -1;
  if (rtp_switch_id < 0.0) {
    tmp = ceil(rtp_switch_id);
  } else {
    tmp = floor(rtp_switch_id);
  }

  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 4.294967296E+9);
  }

  switch (tmp < 0.0 ? -(int32_T)(uint32_T)-tmp : (int32_T)(uint32_T)tmp) {
   case 1:
    rtAction = 0;
    break;

   case 2:
    rtAction = 1;
    break;

   case 3:
    rtAction = 2;
    break;
  }

  localDW->SwitchCase_ActiveSubsystem = rtAction;
  if (rtPrevAction != rtAction) {
    switch (rtPrevAction) {
     case 0:
      /* Disable for Outport: '<S13>/zero' */
      localB->Constant = localP->zero_Y0;
      break;

     case 1:
      /* Disable for Outport: '<S14>/Vbiased' */
      localB->Vin = localP->Vbiased_Y0;
      break;

     case 2:
      /* Disable for Outport: '<S15>/Vunbiased' */
      localB->VVavg = localP->Vunbiased_Y0;
      break;
    }
  }

  switch (rtAction) {
   case 0:
    /* Outputs for IfAction SubSystem: '<S9>/Switch Case Action Subsystem' incorporates:
     *  ActionPort: '<S13>/Action Port'
     */
    localB->Constant = localP->Constant_Value;
    srUpdateBC(localDW->SwitchCaseActionSubsystem_Subsy);

    /* End of Outputs for SubSystem: '<S9>/Switch Case Action Subsystem' */
    break;

   case 1:
    /* Outputs for IfAction SubSystem: '<S9>/Switch Case Action Subsystem1' incorporates:
     *  ActionPort: '<S14>/Action Port'
     */
    localB->Vin = rtu_V;
    srUpdateBC(localDW->SwitchCaseActionSubsystem1_Subs);

    /* End of Outputs for SubSystem: '<S9>/Switch Case Action Subsystem1' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S9>/Switch Case Action Subsystem2' incorporates:
     *  ActionPort: '<S15>/Action Port'
     */
    localB->VVavg = rtb_Sum;
    srUpdateBC(localDW->SwitchCaseActionSubsystem2_Subs);

    /* End of Outputs for SubSystem: '<S9>/Switch Case Action Subsystem2' */
    break;
  }

  /* End of SwitchCase: '<S9>/Switch Case' */

  /* Switch: '<S9>/Switch' incorporates:
   *  Logic: '<S9>/Logical Operator2'
   *  Sum: '<S9>/Sum1'
   */
  if (!(rtb_Stepend_time != 0.0)) {
    localB->Switch = (localB->Constant + localB->Vin) + localB->VVavg;
  } else {
    localB->Switch = rtb_Sum;
  }

  /* End of Switch: '<S9>/Switch' */
}

/*
 * Update for atomic system:
 *    '<S1>/Bias Removal'
 *    '<S2>/Bias Removal'
 */
void q_2dsfl_pos__BiasRemoval_Update(B_BiasRemoval_q_2dsfl_pos_cnt_T *localB,
  DW_BiasRemoval_q_2dsfl_pos_cn_T *localDW)
{
  /* Update for Enabled SubSystem: '<S9>/Enabled Moving Average' incorporates:
   *  EnablePort: '<S12>/Enable'
   */
  if (localDW->EnabledMovingAverage_MODE) {
    /* Update for UnitDelay: '<S16>/Unit Delay' */
    localDW->UnitDelay_DSTATE = localB->Count;

    /* Update for UnitDelay: '<S12>/Sum( k=1,n-1, x(k) )' */
    localDW->Sumk1n1xk_DSTATE = localB->Sum;
  }

  /* End of Update for SubSystem: '<S9>/Enabled Moving Average' */
}

/* Model output function */
void q_2dsfl_pos_cntrl_OG_output(void)
{
  /* local block i/o variables */
  real_T rtb_SquareWave1;
  real_T rtb_HILReadAnalog_o2;
  real_T rtb_HILReadAnalog_o1;
  boolean_T rtb_HILReadDigital_o1;
  boolean_T rtb_HILReadDigital_o2;
  boolean_T rtb_HILReadDigital_o3;
  boolean_T rtb_HILReadDigital_o4;
  real_T rtb_DerivativeFilter2;
  real_T rtb_Sum1_idx_1;
  real_T rtb_Sum1_idx_2;
  real_T rtb_Sum1_idx_3;
  real_T rtb_Gain_tmp;
  if (rtmIsMajorTimeStep(q_2dsfl_pos_cntrl_OG_M)) {
    /* set solver stop time */
    if (!(q_2dsfl_pos_cntrl_OG_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&q_2dsfl_pos_cntrl_OG_M->solverInfo,
                            ((q_2dsfl_pos_cntrl_OG_M->Timing.clockTickH0 + 1) *
        q_2dsfl_pos_cntrl_OG_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&q_2dsfl_pos_cntrl_OG_M->solverInfo,
                            ((q_2dsfl_pos_cntrl_OG_M->Timing.clockTick0 + 1) *
        q_2dsfl_pos_cntrl_OG_M->Timing.stepSize0 +
        q_2dsfl_pos_cntrl_OG_M->Timing.clockTickH0 *
        q_2dsfl_pos_cntrl_OG_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(q_2dsfl_pos_cntrl_OG_M)) {
    q_2dsfl_pos_cntrl_OG_M->Timing.t[0] = rtsiGetT
      (&q_2dsfl_pos_cntrl_OG_M->solverInfo);
  }

  /* Reset subsysRan breadcrumbs */
  srClearBC(q_2dsfl_pos_cntrl_OG_DW.BiasRemoval.EnabledMovingAverage_SubsysRanB);

  /* Reset subsysRan breadcrumbs */
  srClearBC(q_2dsfl_pos_cntrl_OG_DW.BiasRemoval.SwitchCaseActionSubsystem_Subsy);

  /* Reset subsysRan breadcrumbs */
  srClearBC(q_2dsfl_pos_cntrl_OG_DW.BiasRemoval.SwitchCaseActionSubsystem1_Subs);

  /* Reset subsysRan breadcrumbs */
  srClearBC(q_2dsfl_pos_cntrl_OG_DW.BiasRemoval.SwitchCaseActionSubsystem2_Subs);

  /* Reset subsysRan breadcrumbs */
  srClearBC(q_2dsfl_pos_cntrl_OG_DW.PositionWatchdog_SubsysRanBC_c);

  /* Reset subsysRan breadcrumbs */
  srClearBC(q_2dsfl_pos_cntrl_OG_DW.PositionWatchdog_SubsysRanBC);
  if (rtmIsMajorTimeStep(q_2dsfl_pos_cntrl_OG_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S1>/HIL Read Encoder Timebase' */

    /* S-Function Block: q_2dsfl_pos_cntrl_OG/1st Stage: 2-DOF SFL Robot: Actual Plant/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder
        (q_2dsfl_pos_cntrl_OG_DW.HILReadEncoderTimebase_Task, 1,
         &q_2dsfl_pos_cntrl_OG_DW.HILReadEncoderTimebase_Buffer);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_pos_cntrl_OG_M, _rt_error_message);
      } else {
        rtb_HILReadAnalog_o2 =
          q_2dsfl_pos_cntrl_OG_DW.HILReadEncoderTimebase_Buffer;
      }
    }
  }

  /* S-Function (continuous_sigmoid_block): '<S7>/Continuous Sigmoid' */
  /* S-Function Block: q_2dsfl_pos_cntrl_OG/Stage 1 Setpoint/Continuous Sigmoid (continuous_sigmoid_block) */
  {
    if (rtmIsMajorTimeStep(q_2dsfl_pos_cntrl_OG_M)) {
      {
        /* Determine the correct step size for the output ports */

        /*  Check if the target position has changed or if it is the first
           simulation step, in which case we need to compute the initial
           trajectory. */
        if (q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Flag == 1 ||
            q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.Time == 0) {
          /*  Read the new position and reset the flag */
          q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_XD]
            = q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.Target;
          q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Flag = 0;

          /*  Calculate a single step using the new trajectory to account for the target
             change that occured at the previous sample (i.e., there is a one sample delay
             between the point where the target position changes and the trajectory changes
             based on the new target)    */
          if (q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.Time == 0) {
            /*  Do not update the trajectory since we are at time 0 in simulation
               (leave t = 0)   */
          } else {
            /*  Set the relative time to one step size so that a single step
               is computed for the new trajectory  */

            /*  Set the default values in sigmoid_parameters to the trajectory
               state at the last time step.    */
            q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_X0]
              = q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.PPos;
            q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_V0]
              = q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.PVel;
            q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.Time = 0.002;
          }

          /*  Calculate the new trajectory    */
          sigmoid_calculate_trajectory
            (&q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[0], 0,
             q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_X0],
             q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_V0],
             q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.MAcc,
             q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.MVel);
        }

        /* Mark the target as not reached */
        q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid_o4 = 0;
        if (q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.Time <
            q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_T1])
        {
          q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid_o3 =
            q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_AP];
          q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid_o2 =
            q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_V0]
            + q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_AP]
            * q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.Time;
          q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid_o1 =
            q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_X0]
            + (q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_V0]
               + 0.5 *
               q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_AP]
               * q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.Time) *
            q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.Time;
        } else if (q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.Time <
                   q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_T2])
        {
          q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid_o3 = 0;
          q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid_o2 =
            q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_VP];
          q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid_o1 =
            q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_X1]
            + q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_VP]
            * (q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.Time -
               q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_T1]);
        } else if (q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.Time <
                   q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_T3])
        {
          q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid_o3 =
            -q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_AP];
          q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid_o2 =
            q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_VP]
            - q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_AP]
            * (q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.Time -
               q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_T2]);
          q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid_o1 =
            q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_X2]
            + (q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_VP]
               - 0.5 *
               q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_AP]
               * (q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.Time -
                  q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_T2]))
            * (q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.Time -
               q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_T2]);
        } else {
          q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid_o3 = 0;
          q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid_o2 = 0;
          q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid_o1 =
            q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_XD];/* always attainable */

          /* Mark the target as reached after the hold-off period */
          if ((q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.Time -
               q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_T3])
              >=
              q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_HOLD_OFF])
            q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid_o4 = 1;/* Assert Done signal */
        }

        /*  Save the current position/velocity to be used next time step (possibly) */
        q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.PPos =
          q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid_o1;
        q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.PVel =
          q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid_o2;

        /*  Increment the relative time RWork to the NEXT time step */
        q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.Time += 0.002;
      }
    }
  }

  if (rtmIsMajorTimeStep(q_2dsfl_pos_cntrl_OG_M)) {
    /* Gain: '<S7>/[ 1; 1; 0; 0 ]' */
    q_2dsfl_pos_cntrl_OG_B.u100[0] = q_2dsfl_pos_cntrl_OG_P.u100_Gain[0] *
      q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid_o1;
    q_2dsfl_pos_cntrl_OG_B.u100[1] = q_2dsfl_pos_cntrl_OG_P.u100_Gain[1] *
      q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid_o1;
    q_2dsfl_pos_cntrl_OG_B.u100[2] = q_2dsfl_pos_cntrl_OG_P.u100_Gain[2] *
      q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid_o1;
    q_2dsfl_pos_cntrl_OG_B.u100[3] = q_2dsfl_pos_cntrl_OG_P.u100_Gain[3] *
      q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid_o1;

    /* Gain: '<S1>/Motor #1 Encoder Calib' */
    q_2dsfl_pos_cntrl_OG_B.Motor1EncoderCalib = q_2dsfl_pos_cntrl_OG_P.KE_D1 *
      rtb_HILReadAnalog_o2;

    /* Gain: '<S41>/Gain' */
    q_2dsfl_pos_cntrl_OG_B.Gain[0] = q_2dsfl_pos_cntrl_OG_P.Gain_Gain *
      q_2dsfl_pos_cntrl_OG_B.u100[0];
    q_2dsfl_pos_cntrl_OG_B.Gain[1] = q_2dsfl_pos_cntrl_OG_P.Gain_Gain *
      q_2dsfl_pos_cntrl_OG_B.Motor1EncoderCalib;
  }

  /* TransferFcn: '<S1>/Filter3' */
  rtb_DerivativeFilter2 = q_2dsfl_pos_cntrl_OG_P.Filter3_C[0] *
    q_2dsfl_pos_cntrl_OG_X.Filter3_CSTATE[0] + q_2dsfl_pos_cntrl_OG_P.Filter3_C
    [1] * q_2dsfl_pos_cntrl_OG_X.Filter3_CSTATE[1];

  /* Gain: '<S42>/Gain' */
  q_2dsfl_pos_cntrl_OG_B.Gain_n[0] = q_2dsfl_pos_cntrl_OG_P.Gain_Gain_o *
    q_2dsfl_pos_cntrl_OG_B.u100[1];
  q_2dsfl_pos_cntrl_OG_B.Gain_n[1] = q_2dsfl_pos_cntrl_OG_P.Gain_Gain_o *
    rtb_DerivativeFilter2;
  if (rtmIsMajorTimeStep(q_2dsfl_pos_cntrl_OG_M)) {
    /* ManualSwitch: '<Root>/Manual Switch1' incorporates:
     *  Constant: '<Root>/Cnstant1'
     *  Constant: '<Root>/Constant2'
     */
    if (q_2dsfl_pos_cntrl_OG_P.ManualSwitch1_CurrentSetting == 1) {
      q_2dsfl_pos_cntrl_OG_B.ManualSwitch1[0] =
        q_2dsfl_pos_cntrl_OG_P.Constant2_Value[0];
      q_2dsfl_pos_cntrl_OG_B.ManualSwitch1[1] =
        q_2dsfl_pos_cntrl_OG_P.Constant2_Value[1];
      q_2dsfl_pos_cntrl_OG_B.ManualSwitch1[2] =
        q_2dsfl_pos_cntrl_OG_P.Constant2_Value[2];
      q_2dsfl_pos_cntrl_OG_B.ManualSwitch1[3] =
        q_2dsfl_pos_cntrl_OG_P.Constant2_Value[3];
    } else {
      q_2dsfl_pos_cntrl_OG_B.ManualSwitch1[0] =
        q_2dsfl_pos_cntrl_OG_P.Cnstant1_Value[0];
      q_2dsfl_pos_cntrl_OG_B.ManualSwitch1[1] =
        q_2dsfl_pos_cntrl_OG_P.Cnstant1_Value[1];
      q_2dsfl_pos_cntrl_OG_B.ManualSwitch1[2] =
        q_2dsfl_pos_cntrl_OG_P.Cnstant1_Value[2];
      q_2dsfl_pos_cntrl_OG_B.ManualSwitch1[3] =
        q_2dsfl_pos_cntrl_OG_P.Cnstant1_Value[3];
    }

    /* End of ManualSwitch: '<Root>/Manual Switch1' */
  }

  /* TransferFcn: '<S1>/Derivative Filter2' */
  rtb_SquareWave1 = 0.0;
  rtb_SquareWave1 += q_2dsfl_pos_cntrl_OG_P.DerivativeFilter2_C[0] *
    q_2dsfl_pos_cntrl_OG_X.DerivativeFilter2_CSTATE[0];
  rtb_SquareWave1 += q_2dsfl_pos_cntrl_OG_P.DerivativeFilter2_C[1] *
    q_2dsfl_pos_cntrl_OG_X.DerivativeFilter2_CSTATE[1];

  /* Gain: '<Root>/LQR Gain 1' incorporates:
   *  Product: '<Root>/Product'
   *  Sum: '<Root>/Sum3'
   *  TransferFcn: '<S1>/Derivative Filter1'
   */
  rtb_SquareWave1 = ((q_2dsfl_pos_cntrl_OG_B.u100[2] -
                      (q_2dsfl_pos_cntrl_OG_P.DerivativeFilter1_C[0] *
                       q_2dsfl_pos_cntrl_OG_X.DerivativeFilter1_CSTATE[0] +
                       q_2dsfl_pos_cntrl_OG_P.DerivativeFilter1_C[1] *
                       q_2dsfl_pos_cntrl_OG_X.DerivativeFilter1_CSTATE[1]) *
                      q_2dsfl_pos_cntrl_OG_B.ManualSwitch1[2]) *
                     q_2dsfl_pos_cntrl_OG_P.K1[2] +
                     ((q_2dsfl_pos_cntrl_OG_B.u100[0] -
                       q_2dsfl_pos_cntrl_OG_B.Motor1EncoderCalib *
                       q_2dsfl_pos_cntrl_OG_B.ManualSwitch1[0]) *
                      q_2dsfl_pos_cntrl_OG_P.K1[0] +
                      (q_2dsfl_pos_cntrl_OG_B.u100[1] - rtb_DerivativeFilter2 *
                       q_2dsfl_pos_cntrl_OG_B.ManualSwitch1[1]) *
                      q_2dsfl_pos_cntrl_OG_P.K1[1])) +
    (q_2dsfl_pos_cntrl_OG_B.u100[3] - rtb_SquareWave1 *
     q_2dsfl_pos_cntrl_OG_B.ManualSwitch1[3]) * q_2dsfl_pos_cntrl_OG_P.K1[3];

  /* Saturate: '<Root>/Im_r1: Saturation' */
  if (rtb_SquareWave1 > q_2dsfl_pos_cntrl_OG_P.Im_r1Saturation_UpperSat) {
    q_2dsfl_pos_cntrl_OG_B.Im_r1Saturation =
      q_2dsfl_pos_cntrl_OG_P.Im_r1Saturation_UpperSat;
  } else if (rtb_SquareWave1 < q_2dsfl_pos_cntrl_OG_P.Im_r1Saturation_LowerSat)
  {
    q_2dsfl_pos_cntrl_OG_B.Im_r1Saturation =
      q_2dsfl_pos_cntrl_OG_P.Im_r1Saturation_LowerSat;
  } else {
    q_2dsfl_pos_cntrl_OG_B.Im_r1Saturation = rtb_SquareWave1;
  }

  /* End of Saturate: '<Root>/Im_r1: Saturation' */
  if (rtmIsMajorTimeStep(q_2dsfl_pos_cntrl_OG_M)) {
    /* S-Function (hil_read_analog_block): '<S1>/HIL Read Analog' */

    /* S-Function Block: q_2dsfl_pos_cntrl_OG/1st Stage: 2-DOF SFL Robot: Actual Plant/HIL Read Analog (hil_read_analog_block) */
    {
      t_error result = hil_read_analog
        (q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card,
         q_2dsfl_pos_cntrl_OG_P.HILReadAnalog_channels, 2,
         &q_2dsfl_pos_cntrl_OG_DW.HILReadAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_pos_cntrl_OG_M, _rt_error_message);
      }

      rtb_HILReadAnalog_o2 = q_2dsfl_pos_cntrl_OG_DW.HILReadAnalog_Buffer[0];
      rtb_HILReadAnalog_o1 = q_2dsfl_pos_cntrl_OG_DW.HILReadAnalog_Buffer[1];
    }

    /* Gain: '<S1>/Volts to Amps' */
    q_2dsfl_pos_cntrl_OG_B.VoltstoAmps = q_2dsfl_pos_cntrl_OG_P.VoltstoAmps_Gain
      * rtb_HILReadAnalog_o1;
  }

  /* Gain: '<S1>/Amps to Volts' incorporates:
   *  UnaryMinus: '<S1>/positive dir: CCW'
   */
  q_2dsfl_pos_cntrl_OG_B.AmpstoVolts = q_2dsfl_pos_cntrl_OG_P.AmpstoVolts_Gain *
    -q_2dsfl_pos_cntrl_OG_B.Im_r1Saturation;

  /* Outputs for Enabled SubSystem: '<S1>/Position Watchdog' incorporates:
   *  EnablePort: '<S10>/Enable'
   */
  if (rtmIsMajorTimeStep(q_2dsfl_pos_cntrl_OG_M)) {
    /* S-Function (hil_write_analog_block): '<S1>/HIL Write Analog' */

    /* S-Function Block: q_2dsfl_pos_cntrl_OG/1st Stage: 2-DOF SFL Robot: Actual Plant/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      result = hil_write_analog(q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card,
        &q_2dsfl_pos_cntrl_OG_P.HILWriteAnalog_channels, 1,
        &q_2dsfl_pos_cntrl_OG_B.AmpstoVolts);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_pos_cntrl_OG_M, _rt_error_message);
      }
    }

    if (rtmIsMajorTimeStep(q_2dsfl_pos_cntrl_OG_M)) {
      /* Constant: '<S1>/Constant' */
      if (q_2dsfl_pos_cntrl_OG_P.DTH1_LIM_ENABLE > 0.0) {
        if (!q_2dsfl_pos_cntrl_OG_DW.PositionWatchdog_MODE_l) {
          q_2dsfl_pos_cntrl_OG_DW.PositionWatchdog_MODE_l = true;
        }
      } else {
        if (q_2dsfl_pos_cntrl_OG_DW.PositionWatchdog_MODE_l) {
          q_2dsfl_pos_cntrl_OG_DW.PositionWatchdog_MODE_l = false;
        }
      }

      /* End of Constant: '<S1>/Constant' */
    }
  }

  /* End of Outputs for SubSystem: '<S1>/Position Watchdog' */

  /* Gain: '<S11>/Gain' */
  rtb_DerivativeFilter2 *= q_2dsfl_pos_cntrl_OG_P.Gain_Gain_e;

  /* Outputs for Enabled SubSystem: '<S1>/Position Watchdog' incorporates:
   *  EnablePort: '<S10>/Enable'
   */
  if (q_2dsfl_pos_cntrl_OG_DW.PositionWatchdog_MODE_l) {
    /* RelationalOperator: '<S10>/Check Maximum Allowed Position' incorporates:
     *  Constant: '<S10>/X MAX'
     */
    q_2dsfl_pos_cntrl_OG_B.CheckMaximumAllowedPosition_c =
      (q_2dsfl_pos_cntrl_OG_P.DTH2_MAX < rtb_DerivativeFilter2);

    /* RelationalOperator: '<S19>/Compare' incorporates:
     *  Constant: '<S19>/Constant'
     */
    q_2dsfl_pos_cntrl_OG_B.Compare_c =
      (q_2dsfl_pos_cntrl_OG_B.CheckMaximumAllowedPosition_c !=
       q_2dsfl_pos_cntrl_OG_P.Constant_Value);

    /* Stop: '<S17>/Stop Simulation' */
    if (rtmIsMajorTimeStep(q_2dsfl_pos_cntrl_OG_M) &&
        q_2dsfl_pos_cntrl_OG_B.Compare_c) {
      rtmSetStopRequested(q_2dsfl_pos_cntrl_OG_M, 1);
    }

    /* End of Stop: '<S17>/Stop Simulation' */

    /* RelationalOperator: '<S10>/Check Minimum Allowed Position' incorporates:
     *  Constant: '<S10>/X IN'
     */
    q_2dsfl_pos_cntrl_OG_B.CheckMinimumAllowedPosition_a =
      (rtb_DerivativeFilter2 < q_2dsfl_pos_cntrl_OG_P.DTH2_MIN);

    /* RelationalOperator: '<S20>/Compare' incorporates:
     *  Constant: '<S20>/Constant'
     */
    q_2dsfl_pos_cntrl_OG_B.Compare_e =
      (q_2dsfl_pos_cntrl_OG_B.CheckMinimumAllowedPosition_a !=
       q_2dsfl_pos_cntrl_OG_P.Constant_Value_a);

    /* Stop: '<S18>/Stop Simulation' */
    if (rtmIsMajorTimeStep(q_2dsfl_pos_cntrl_OG_M) &&
        q_2dsfl_pos_cntrl_OG_B.Compare_e) {
      rtmSetStopRequested(q_2dsfl_pos_cntrl_OG_M, 1);
    }

    /* End of Stop: '<S18>/Stop Simulation' */
    if (rtmIsMajorTimeStep(q_2dsfl_pos_cntrl_OG_M)) {
      srUpdateBC(q_2dsfl_pos_cntrl_OG_DW.PositionWatchdog_SubsysRanBC_c);
    }
  }

  /* End of Outputs for SubSystem: '<S1>/Position Watchdog' */
  if (rtmIsMajorTimeStep(q_2dsfl_pos_cntrl_OG_M)) {
    /* UnaryMinus: '<S1>/positive  CCW' */
    q_2dsfl_pos_cntrl_OG_B.positiveCCW = -rtb_HILReadAnalog_o2;

    /* Outputs for Atomic SubSystem: '<S1>/Bias Removal' */
    q_2dsfl_pos_cntrl_O_BiasRemoval(q_2dsfl_pos_cntrl_OG_M,
      q_2dsfl_pos_cntrl_OG_B.positiveCCW, &q_2dsfl_pos_cntrl_OG_B.BiasRemoval,
      &q_2dsfl_pos_cntrl_OG_DW.BiasRemoval, &q_2dsfl_pos_cntrl_OG_P.BiasRemoval,
      q_2dsfl_pos_cntrl_OG_P.BiasRemoval_switch_id,
      q_2dsfl_pos_cntrl_OG_P.BiasRemoval_start_time,
      q_2dsfl_pos_cntrl_OG_P.BiasRemoval_end_time);

    /* End of Outputs for SubSystem: '<S1>/Bias Removal' */

    /* Gain: '<S1>/Strain to Deflection' incorporates:
     *  Gain: '<S1>/Volts to Base Strain'
     */
    q_2dsfl_pos_cntrl_OG_B.StraintoDeflection =
      q_2dsfl_pos_cntrl_OG_P.K1_strain_b *
      q_2dsfl_pos_cntrl_OG_B.BiasRemoval.Switch *
      q_2dsfl_pos_cntrl_OG_P.K1_defl_b;
  }

  /* SignalGenerator: '<S7>/Square Wave' incorporates:
   *  SignalGenerator: '<S8>/Square Wave1'
   */
  rtb_Gain_tmp = q_2dsfl_pos_cntrl_OG_M->Timing.t[0];
  rtb_DerivativeFilter2 = q_2dsfl_pos_cntrl_OG_P.SquareWave_Frequency *
    rtb_Gain_tmp;
  if (rtb_DerivativeFilter2 - floor(rtb_DerivativeFilter2) >= 0.5) {
    rtb_SquareWave1 = q_2dsfl_pos_cntrl_OG_P.SquareWave_Amplitude;
  } else {
    rtb_SquareWave1 = -q_2dsfl_pos_cntrl_OG_P.SquareWave_Amplitude;
  }

  /* End of SignalGenerator: '<S7>/Square Wave' */

  /* Gain: '<S45>/Gain1' incorporates:
   *  Gain: '<S7>/Amplitude (deg)'
   */
  q_2dsfl_pos_cntrl_OG_B.Gain1 = q_2dsfl_pos_cntrl_OG_P.Amplitudedeg_Gain *
    rtb_SquareWave1 * q_2dsfl_pos_cntrl_OG_P.Gain1_Gain;

  /* TransportDelay: '<S8>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)
      &q_2dsfl_pos_cntrl_OG_DW.TransportDelay_PWORK.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &q_2dsfl_pos_cntrl_OG_DW.TransportDelay_PWORK.TUbufferPtrs[1];
    real_T simTime = q_2dsfl_pos_cntrl_OG_M->Timing.t[0];
    real_T tMinusDelay = simTime - q_2dsfl_pos_cntrl_OG_P.TransportDelay_Delay;
    rtb_SquareWave1 = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      q_2dsfl_pos_cntrl_OG_DW.TransportDelay_IWORK.CircularBufSize,
      &q_2dsfl_pos_cntrl_OG_DW.TransportDelay_IWORK.Last,
      q_2dsfl_pos_cntrl_OG_DW.TransportDelay_IWORK.Tail,
      q_2dsfl_pos_cntrl_OG_DW.TransportDelay_IWORK.Head,
      q_2dsfl_pos_cntrl_OG_P.TransportDelay_InitOutput,
      1,
      0);
  }

  /* Gain: '<S8>/[ 1; 1; 0; 0 ]1' */
  rtb_DerivativeFilter2 = q_2dsfl_pos_cntrl_OG_P.u1001_Gain[0] * rtb_SquareWave1;
  rtb_Sum1_idx_1 = q_2dsfl_pos_cntrl_OG_P.u1001_Gain[1] * rtb_SquareWave1;
  rtb_Sum1_idx_2 = q_2dsfl_pos_cntrl_OG_P.u1001_Gain[2] * rtb_SquareWave1;
  rtb_Sum1_idx_3 = q_2dsfl_pos_cntrl_OG_P.u1001_Gain[3] * rtb_SquareWave1;
  if (rtmIsMajorTimeStep(q_2dsfl_pos_cntrl_OG_M)) {
    /* S-Function (hil_read_encoder_block): '<S2>/HIL Read Encoder' */

    /* S-Function Block: q_2dsfl_pos_cntrl_OG/2nd Stage: 2-DOF SFL Robot: Actual Plant/HIL Read Encoder (hil_read_encoder_block) */
    {
      t_error result = hil_read_encoder
        (q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card,
         &q_2dsfl_pos_cntrl_OG_P.HILReadEncoder_channels, 1,
         &q_2dsfl_pos_cntrl_OG_DW.HILReadEncoder_Buffer);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_pos_cntrl_OG_M, _rt_error_message);
      } else {
        rtb_HILReadAnalog_o1 = q_2dsfl_pos_cntrl_OG_DW.HILReadEncoder_Buffer;
      }
    }

    /* Gain: '<S2>/Motor #2 Encoder Calib' */
    q_2dsfl_pos_cntrl_OG_B.Motor2EncoderCalib = q_2dsfl_pos_cntrl_OG_P.KE_D2 *
      rtb_HILReadAnalog_o1;
  }

  /* Gain: '<S43>/Gain' */
  q_2dsfl_pos_cntrl_OG_B.Gain_m[0] = q_2dsfl_pos_cntrl_OG_P.Gain_Gain_g *
    rtb_DerivativeFilter2;
  q_2dsfl_pos_cntrl_OG_B.Gain_m[1] = q_2dsfl_pos_cntrl_OG_P.Gain_Gain_g *
    q_2dsfl_pos_cntrl_OG_B.Motor2EncoderCalib;
  if (rtmIsMajorTimeStep(q_2dsfl_pos_cntrl_OG_M)) {
  }

  /* TransferFcn: '<S2>/Derivative Filter3' */
  rtb_SquareWave1 = 0.0;
  rtb_SquareWave1 += q_2dsfl_pos_cntrl_OG_P.DerivativeFilter3_C[0] *
    q_2dsfl_pos_cntrl_OG_X.DerivativeFilter3_CSTATE[0];
  rtb_SquareWave1 += q_2dsfl_pos_cntrl_OG_P.DerivativeFilter3_C[1] *
    q_2dsfl_pos_cntrl_OG_X.DerivativeFilter3_CSTATE[1];

  /* Gain: '<S44>/Gain' */
  q_2dsfl_pos_cntrl_OG_B.Gain_b[0] = q_2dsfl_pos_cntrl_OG_P.Gain_Gain_k *
    rtb_Sum1_idx_1;
  q_2dsfl_pos_cntrl_OG_B.Gain_b[1] = q_2dsfl_pos_cntrl_OG_P.Gain_Gain_k *
    rtb_SquareWave1;
  if (rtmIsMajorTimeStep(q_2dsfl_pos_cntrl_OG_M)) {
    /* S-Function (hil_read_analog_block): '<S2>/HIL Read Analog' */

    /* S-Function Block: q_2dsfl_pos_cntrl_OG/2nd Stage: 2-DOF SFL Robot: Actual Plant/HIL Read Analog (hil_read_analog_block) */
    {
      t_error result = hil_read_analog
        (q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card,
         q_2dsfl_pos_cntrl_OG_P.HILReadAnalog_channels_a, 2,
         &q_2dsfl_pos_cntrl_OG_DW.HILReadAnalog_Buffer_p[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_pos_cntrl_OG_M, _rt_error_message);
      }

      rtb_HILReadAnalog_o1 = q_2dsfl_pos_cntrl_OG_DW.HILReadAnalog_Buffer_p[0];
      rtb_HILReadAnalog_o2 = q_2dsfl_pos_cntrl_OG_DW.HILReadAnalog_Buffer_p[1];
    }

    /* UnaryMinus: '<S2>/positive  CCW' */
    q_2dsfl_pos_cntrl_OG_B.positiveCCW_h = -rtb_HILReadAnalog_o1;

    /* Outputs for Atomic SubSystem: '<S2>/Bias Removal' */
    q_2dsfl_pos_cntrl_O_BiasRemoval(q_2dsfl_pos_cntrl_OG_M,
      q_2dsfl_pos_cntrl_OG_B.positiveCCW_h,
      &q_2dsfl_pos_cntrl_OG_B.BiasRemoval_m,
      &q_2dsfl_pos_cntrl_OG_DW.BiasRemoval_m,
      &q_2dsfl_pos_cntrl_OG_P.BiasRemoval_m,
      q_2dsfl_pos_cntrl_OG_P.BiasRemoval_switch_id_n,
      q_2dsfl_pos_cntrl_OG_P.BiasRemoval_start_time_l,
      q_2dsfl_pos_cntrl_OG_P.BiasRemoval_end_time_g);

    /* End of Outputs for SubSystem: '<S2>/Bias Removal' */

    /* Gain: '<S2>/Volts to Strain' */
    q_2dsfl_pos_cntrl_OG_B.VoltstoStrain = q_2dsfl_pos_cntrl_OG_P.K2_strain_b *
      q_2dsfl_pos_cntrl_OG_B.BiasRemoval_m.Switch;

    /* ManualSwitch: '<Root>/Manual Switch2' incorporates:
     *  Constant: '<Root>/Cnstant2'
     *  Constant: '<Root>/Constant1'
     */
    if (q_2dsfl_pos_cntrl_OG_P.ManualSwitch2_CurrentSetting == 1) {
      q_2dsfl_pos_cntrl_OG_B.ManualSwitch2[0] =
        q_2dsfl_pos_cntrl_OG_P.Constant1_Value[0];
      q_2dsfl_pos_cntrl_OG_B.ManualSwitch2[1] =
        q_2dsfl_pos_cntrl_OG_P.Constant1_Value[1];
      q_2dsfl_pos_cntrl_OG_B.ManualSwitch2[2] =
        q_2dsfl_pos_cntrl_OG_P.Constant1_Value[2];
      q_2dsfl_pos_cntrl_OG_B.ManualSwitch2[3] =
        q_2dsfl_pos_cntrl_OG_P.Constant1_Value[3];
    } else {
      q_2dsfl_pos_cntrl_OG_B.ManualSwitch2[0] =
        q_2dsfl_pos_cntrl_OG_P.Cnstant2_Value[0];
      q_2dsfl_pos_cntrl_OG_B.ManualSwitch2[1] =
        q_2dsfl_pos_cntrl_OG_P.Cnstant2_Value[1];
      q_2dsfl_pos_cntrl_OG_B.ManualSwitch2[2] =
        q_2dsfl_pos_cntrl_OG_P.Cnstant2_Value[2];
      q_2dsfl_pos_cntrl_OG_B.ManualSwitch2[3] =
        q_2dsfl_pos_cntrl_OG_P.Cnstant2_Value[3];
    }

    /* End of ManualSwitch: '<Root>/Manual Switch2' */
  }

  /* Gain: '<Root>/LQR Gain 2' incorporates:
   *  Product: '<Root>/Product1'
   *  Sum: '<Root>/Sum1'
   *  TransferFcn: '<S2>/Derivative Filter1'
   *  TransferFcn: '<S2>/Derivative Filter2'
   */
  rtb_DerivativeFilter2 = ((rtb_Sum1_idx_2 -
    (q_2dsfl_pos_cntrl_OG_P.DerivativeFilter1_C_l[0] *
     q_2dsfl_pos_cntrl_OG_X.DerivativeFilter1_CSTATE_n[0] +
     q_2dsfl_pos_cntrl_OG_P.DerivativeFilter1_C_l[1] *
     q_2dsfl_pos_cntrl_OG_X.DerivativeFilter1_CSTATE_n[1]) *
    q_2dsfl_pos_cntrl_OG_B.ManualSwitch2[2]) * q_2dsfl_pos_cntrl_OG_P.K2[2] +
    ((rtb_DerivativeFilter2 - q_2dsfl_pos_cntrl_OG_B.Motor2EncoderCalib *
      q_2dsfl_pos_cntrl_OG_B.ManualSwitch2[0]) * q_2dsfl_pos_cntrl_OG_P.K2[0] +
     (rtb_Sum1_idx_1 - rtb_SquareWave1 * q_2dsfl_pos_cntrl_OG_B.ManualSwitch2[1])
     * q_2dsfl_pos_cntrl_OG_P.K2[1])) + (rtb_Sum1_idx_3 -
    (q_2dsfl_pos_cntrl_OG_P.DerivativeFilter2_C_g[0] *
     q_2dsfl_pos_cntrl_OG_X.DerivativeFilter2_CSTATE_p[0] +
     q_2dsfl_pos_cntrl_OG_P.DerivativeFilter2_C_g[1] *
     q_2dsfl_pos_cntrl_OG_X.DerivativeFilter2_CSTATE_p[1]) *
    q_2dsfl_pos_cntrl_OG_B.ManualSwitch2[3]) * q_2dsfl_pos_cntrl_OG_P.K2[3];

  /* Saturate: '<Root>/Im_r2: Saturation' incorporates:
   *  Gain: '<Root>/LQR Gain 2'
   */
  if (rtb_DerivativeFilter2 > q_2dsfl_pos_cntrl_OG_P.Im_r2Saturation_UpperSat) {
    q_2dsfl_pos_cntrl_OG_B.Im_r2Saturation =
      q_2dsfl_pos_cntrl_OG_P.Im_r2Saturation_UpperSat;
  } else if (rtb_DerivativeFilter2 <
             q_2dsfl_pos_cntrl_OG_P.Im_r2Saturation_LowerSat) {
    q_2dsfl_pos_cntrl_OG_B.Im_r2Saturation =
      q_2dsfl_pos_cntrl_OG_P.Im_r2Saturation_LowerSat;
  } else {
    q_2dsfl_pos_cntrl_OG_B.Im_r2Saturation = rtb_DerivativeFilter2;
  }

  /* End of Saturate: '<Root>/Im_r2: Saturation' */
  if (rtmIsMajorTimeStep(q_2dsfl_pos_cntrl_OG_M)) {
    /* Gain: '<S2>/Volts to Amps' */
    q_2dsfl_pos_cntrl_OG_B.VoltstoAmps_i =
      q_2dsfl_pos_cntrl_OG_P.VoltstoAmps_Gain_p * rtb_HILReadAnalog_o2;
  }

  /* Gain: '<S2>/Amps to Volts' incorporates:
   *  UnaryMinus: '<S2>/positive dir: CCW'
   */
  q_2dsfl_pos_cntrl_OG_B.AmpstoVolts_g =
    q_2dsfl_pos_cntrl_OG_P.AmpstoVolts_Gain_j *
    -q_2dsfl_pos_cntrl_OG_B.Im_r2Saturation;

  /* Outputs for Enabled SubSystem: '<S2>/Position Watchdog' incorporates:
   *  EnablePort: '<S22>/Enable'
   */
  if (rtmIsMajorTimeStep(q_2dsfl_pos_cntrl_OG_M)) {
    /* S-Function (hil_write_analog_block): '<S2>/HIL Write Analog' */

    /* S-Function Block: q_2dsfl_pos_cntrl_OG/2nd Stage: 2-DOF SFL Robot: Actual Plant/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      result = hil_write_analog(q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card,
        &q_2dsfl_pos_cntrl_OG_P.HILWriteAnalog_channels_e, 1,
        &q_2dsfl_pos_cntrl_OG_B.AmpstoVolts_g);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_pos_cntrl_OG_M, _rt_error_message);
      }
    }

    if (rtmIsMajorTimeStep(q_2dsfl_pos_cntrl_OG_M)) {
      /* Constant: '<S2>/Constant' */
      if (q_2dsfl_pos_cntrl_OG_P.DTH2_LIM_ENABLE > 0.0) {
        if (!q_2dsfl_pos_cntrl_OG_DW.PositionWatchdog_MODE) {
          q_2dsfl_pos_cntrl_OG_DW.PositionWatchdog_MODE = true;
        }
      } else {
        if (q_2dsfl_pos_cntrl_OG_DW.PositionWatchdog_MODE) {
          q_2dsfl_pos_cntrl_OG_DW.PositionWatchdog_MODE = false;
        }
      }

      /* End of Constant: '<S2>/Constant' */
    }
  }

  /* End of Outputs for SubSystem: '<S2>/Position Watchdog' */

  /* Gain: '<S23>/Gain' */
  rtb_DerivativeFilter2 = q_2dsfl_pos_cntrl_OG_P.Gain_Gain_n * rtb_SquareWave1;

  /* Outputs for Enabled SubSystem: '<S2>/Position Watchdog' incorporates:
   *  EnablePort: '<S22>/Enable'
   */
  if (q_2dsfl_pos_cntrl_OG_DW.PositionWatchdog_MODE) {
    /* RelationalOperator: '<S22>/Check Maximum Allowed Position' incorporates:
     *  Constant: '<S22>/X MAX'
     */
    q_2dsfl_pos_cntrl_OG_B.CheckMaximumAllowedPosition =
      (q_2dsfl_pos_cntrl_OG_P.DTH2_MAX < rtb_DerivativeFilter2);

    /* RelationalOperator: '<S31>/Compare' incorporates:
     *  Constant: '<S31>/Constant'
     */
    q_2dsfl_pos_cntrl_OG_B.Compare =
      (q_2dsfl_pos_cntrl_OG_B.CheckMaximumAllowedPosition !=
       q_2dsfl_pos_cntrl_OG_P.Constant_Value_p);

    /* Stop: '<S29>/Stop Simulation' */
    if (rtmIsMajorTimeStep(q_2dsfl_pos_cntrl_OG_M) &&
        q_2dsfl_pos_cntrl_OG_B.Compare) {
      rtmSetStopRequested(q_2dsfl_pos_cntrl_OG_M, 1);
    }

    /* End of Stop: '<S29>/Stop Simulation' */

    /* RelationalOperator: '<S22>/Check Minimum Allowed Position' incorporates:
     *  Constant: '<S22>/X IN'
     */
    q_2dsfl_pos_cntrl_OG_B.CheckMinimumAllowedPosition = (rtb_DerivativeFilter2 <
      q_2dsfl_pos_cntrl_OG_P.DTH2_MIN);

    /* RelationalOperator: '<S32>/Compare' incorporates:
     *  Constant: '<S32>/Constant'
     */
    q_2dsfl_pos_cntrl_OG_B.Compare_j =
      (q_2dsfl_pos_cntrl_OG_B.CheckMinimumAllowedPosition !=
       q_2dsfl_pos_cntrl_OG_P.Constant_Value_f);

    /* Stop: '<S30>/Stop Simulation' */
    if (rtmIsMajorTimeStep(q_2dsfl_pos_cntrl_OG_M) &&
        q_2dsfl_pos_cntrl_OG_B.Compare_j) {
      rtmSetStopRequested(q_2dsfl_pos_cntrl_OG_M, 1);
    }

    /* End of Stop: '<S30>/Stop Simulation' */
    if (rtmIsMajorTimeStep(q_2dsfl_pos_cntrl_OG_M)) {
      srUpdateBC(q_2dsfl_pos_cntrl_OG_DW.PositionWatchdog_SubsysRanBC);
    }
  }

  /* End of Outputs for SubSystem: '<S2>/Position Watchdog' */
  if (rtmIsMajorTimeStep(q_2dsfl_pos_cntrl_OG_M)) {
    /* Gain: '<S2>/Strain to Deflection' */
    q_2dsfl_pos_cntrl_OG_B.StraintoDeflection_i =
      q_2dsfl_pos_cntrl_OG_P.K2_defl_b * q_2dsfl_pos_cntrl_OG_B.VoltstoStrain;
  }

  /* SignalGenerator: '<S8>/Square Wave1' */
  rtb_DerivativeFilter2 = q_2dsfl_pos_cntrl_OG_P.SquareWave1_Frequency *
    rtb_Gain_tmp;
  if (rtb_DerivativeFilter2 - floor(rtb_DerivativeFilter2) >= 0.5) {
    rtb_SquareWave1 = q_2dsfl_pos_cntrl_OG_P.SquareWave1_Amplitude;
  } else {
    rtb_SquareWave1 = -q_2dsfl_pos_cntrl_OG_P.SquareWave1_Amplitude;
  }

  /* S-Function (continuous_sigmoid_block): '<S8>/Continuous Sigmoid1' */
  /* S-Function Block: q_2dsfl_pos_cntrl_OG/Stage 2 Setpoint/Continuous Sigmoid1 (continuous_sigmoid_block) */
  {
    if (rtmIsMajorTimeStep(q_2dsfl_pos_cntrl_OG_M)) {
      {
        /* Determine the correct step size for the output ports */

        /*  Check if the target position has changed or if it is the first
           simulation step, in which case we need to compute the initial
           trajectory. */
        if (q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Flag == 1 ||
            q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.Time == 0) {
          /*  Read the new position and reset the flag */
          q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_XD]
            = q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.Target;
          q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Flag = 0;

          /*  Calculate a single step using the new trajectory to account for the target
             change that occured at the previous sample (i.e., there is a one sample delay
             between the point where the target position changes and the trajectory changes
             based on the new target)    */
          if (q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.Time == 0) {
            /*  Do not update the trajectory since we are at time 0 in simulation
               (leave t = 0)   */
          } else {
            /*  Set the relative time to one step size so that a single step
               is computed for the new trajectory  */

            /*  Set the default values in sigmoid_parameters to the trajectory
               state at the last time step.    */
            q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_X0]
              = q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.PPos;
            q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_V0]
              = q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.PVel;
            q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.Time = 0.002;
          }

          /*  Calculate the new trajectory    */
          sigmoid_calculate_trajectory
            (&q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[0], 0,
             q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_X0],
             q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_V0],
             q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.MAcc,
             q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.MVel);
        }

        /* Mark the target as not reached */
        q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid1_o4 = 0;
        if (q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.Time <
            q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_T1])
        {
          q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid1_o3 =
            q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_AP];
          q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid1_o2 =
            q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_V0]
            + q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_AP]
            * q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.Time;
          q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid1_o1 =
            q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_X0]
            + (q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_V0]
               + 0.5 *
               q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_AP]
               * q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.Time) *
            q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.Time;
        } else if (q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.Time <
                   q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_T2])
        {
          q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid1_o3 = 0;
          q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid1_o2 =
            q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_VP];
          q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid1_o1 =
            q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_X1]
            + q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_VP]
            * (q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.Time -
               q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_T1]);
        } else if (q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.Time <
                   q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_T3])
        {
          q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid1_o3 =
            -q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_AP];
          q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid1_o2 =
            q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_VP]
            - q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_AP]
            * (q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.Time -
               q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_T2]);
          q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid1_o1 =
            q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_X2]
            + (q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_VP]
               - 0.5 *
               q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_AP]
               * (q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.Time -
                  q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_T2]))
            * (q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.Time -
               q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_T2]);
        } else {
          q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid1_o3 = 0;
          q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid1_o2 = 0;
          q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid1_o1 =
            q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_XD];/* always attainable */

          /* Mark the target as reached after the hold-off period */
          if ((q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.Time -
               q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_T3])
              >=
              q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_HOLD_OFF])
            q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid1_o4 = 1;/* Assert Done signal */
        }

        /*  Save the current position/velocity to be used next time step (possibly) */
        q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.PPos =
          q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid1_o1;
        q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.PVel =
          q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid1_o2;

        /*  Increment the relative time RWork to the NEXT time step */
        q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.Time += 0.002;
      }
    }
  }

  /* Gain: '<S46>/Gain1' incorporates:
   *  Gain: '<S8>/Amplitude (deg)1'
   */
  q_2dsfl_pos_cntrl_OG_B.Gain1_o = q_2dsfl_pos_cntrl_OG_P.Amplitudedeg1_Gain *
    rtb_SquareWave1 * q_2dsfl_pos_cntrl_OG_P.Gain1_Gain_j;
  if (rtmIsMajorTimeStep(q_2dsfl_pos_cntrl_OG_M)) {
    /* S-Function (hil_write_digital_block): '<S3>/HIL Write Digital' incorporates:
     *  Constant: '<S3>/Enable: Active Low'
     *  Constant: '<S3>/Master Enable: Active High'
     */

    /* S-Function Block: q_2dsfl_pos_cntrl_OG/Enable AMPAQ/HIL Write Digital (hil_write_digital_block) */
    {
      t_error result;
      q_2dsfl_pos_cntrl_OG_DW.HILWriteDigital_Buffer[0] =
        (q_2dsfl_pos_cntrl_OG_P.EnableActiveLow_Value[0] != 0);
      q_2dsfl_pos_cntrl_OG_DW.HILWriteDigital_Buffer[1] =
        (q_2dsfl_pos_cntrl_OG_P.EnableActiveLow_Value[1] != 0);
      q_2dsfl_pos_cntrl_OG_DW.HILWriteDigital_Buffer[2] =
        (q_2dsfl_pos_cntrl_OG_P.MasterEnableActiveHigh_Value != 0);
      result = hil_write_digital(q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card,
        q_2dsfl_pos_cntrl_OG_P.HILWriteDigital_channels, 3,
        &q_2dsfl_pos_cntrl_OG_DW.HILWriteDigital_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_pos_cntrl_OG_M, _rt_error_message);
      }
    }

    /* S-Function (hil_read_digital_block): '<S4>/HIL Read Digital' */

    /* S-Function Block: q_2dsfl_pos_cntrl_OG/Limit Switches/HIL Read Digital (hil_read_digital_block) */
    {
      t_error result = hil_read_digital
        (q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card,
         q_2dsfl_pos_cntrl_OG_P.HILReadDigital_channels, 4,
         &q_2dsfl_pos_cntrl_OG_DW.HILReadDigital_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_pos_cntrl_OG_M, _rt_error_message);
      } else {
        rtb_HILReadDigital_o1 = q_2dsfl_pos_cntrl_OG_DW.HILReadDigital_Buffer[0];
        rtb_HILReadDigital_o2 = q_2dsfl_pos_cntrl_OG_DW.HILReadDigital_Buffer[1];
        rtb_HILReadDigital_o3 = q_2dsfl_pos_cntrl_OG_DW.HILReadDigital_Buffer[2];
        rtb_HILReadDigital_o4 = q_2dsfl_pos_cntrl_OG_DW.HILReadDigital_Buffer[3];
      }
    }

    /* Logic: '<S4>/Logical Operator4' incorporates:
     *  Constant: '<S4>/Constant'
     *  Logic: '<S4>/Logical Operator2'
     */
    q_2dsfl_pos_cntrl_OG_B.LogicalOperator4 =
      ((q_2dsfl_pos_cntrl_OG_P.LIMIT_SWITCHES_ENABLE != 0.0) &&
       (!rtb_HILReadDigital_o1));

    /* Stop: '<S33>/Stop Simulation' incorporates:
     *  Constant: '<S37>/Constant'
     *  RelationalOperator: '<S37>/Compare'
     */
    if (q_2dsfl_pos_cntrl_OG_B.LogicalOperator4 !=
        q_2dsfl_pos_cntrl_OG_P.Constant_Value_g) {
      rtmSetStopRequested(q_2dsfl_pos_cntrl_OG_M, 1);
    }

    /* End of Stop: '<S33>/Stop Simulation' */

    /* Logic: '<S4>/Logical Operator5' incorporates:
     *  Constant: '<S4>/Constant'
     *  Logic: '<S4>/Logical Operator3'
     */
    q_2dsfl_pos_cntrl_OG_B.LogicalOperator5 =
      ((q_2dsfl_pos_cntrl_OG_P.LIMIT_SWITCHES_ENABLE != 0.0) &&
       (!rtb_HILReadDigital_o2));

    /* Stop: '<S34>/Stop Simulation' incorporates:
     *  Constant: '<S38>/Constant'
     *  RelationalOperator: '<S38>/Compare'
     */
    if (q_2dsfl_pos_cntrl_OG_B.LogicalOperator5 !=
        q_2dsfl_pos_cntrl_OG_P.Constant_Value_fj) {
      rtmSetStopRequested(q_2dsfl_pos_cntrl_OG_M, 1);
    }

    /* End of Stop: '<S34>/Stop Simulation' */

    /* Logic: '<S4>/Logical Operator6' incorporates:
     *  Constant: '<S4>/Constant'
     *  Logic: '<S4>/Logical Operator1'
     */
    q_2dsfl_pos_cntrl_OG_B.LogicalOperator6 =
      ((q_2dsfl_pos_cntrl_OG_P.LIMIT_SWITCHES_ENABLE != 0.0) &&
       (!rtb_HILReadDigital_o3));

    /* Stop: '<S35>/Stop Simulation' incorporates:
     *  Constant: '<S39>/Constant'
     *  RelationalOperator: '<S39>/Compare'
     */
    if (q_2dsfl_pos_cntrl_OG_B.LogicalOperator6 !=
        q_2dsfl_pos_cntrl_OG_P.Constant_Value_k) {
      rtmSetStopRequested(q_2dsfl_pos_cntrl_OG_M, 1);
    }

    /* End of Stop: '<S35>/Stop Simulation' */

    /* Logic: '<S4>/Logical Operator7' incorporates:
     *  Constant: '<S4>/Constant'
     *  Logic: '<S4>/Logical Operator'
     */
    q_2dsfl_pos_cntrl_OG_B.LogicalOperator7 =
      ((q_2dsfl_pos_cntrl_OG_P.LIMIT_SWITCHES_ENABLE != 0.0) &&
       (!rtb_HILReadDigital_o4));

    /* Stop: '<S36>/Stop Simulation' incorporates:
     *  Constant: '<S40>/Constant'
     *  RelationalOperator: '<S40>/Compare'
     */
    if (q_2dsfl_pos_cntrl_OG_B.LogicalOperator7 !=
        q_2dsfl_pos_cntrl_OG_P.Constant_Value_ks) {
      rtmSetStopRequested(q_2dsfl_pos_cntrl_OG_M, 1);
    }

    /* End of Stop: '<S36>/Stop Simulation' */
  }
}

/* Model update function */
void q_2dsfl_pos_cntrl_OG_update(void)
{
  /* Update for S-Function (continuous_sigmoid_block): '<S7>/Continuous Sigmoid' */
  if (1) {
    {
      if (q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.Target !=
          q_2dsfl_pos_cntrl_OG_B.Gain1) {
        q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.Target =
          q_2dsfl_pos_cntrl_OG_B.Gain1;
        q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Flag = 1;
      }

      if (q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid_VMax !=
          q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.MVel) {
        q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.MVel =
          q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid_VMax;
        q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Flag = 1;
      }

      if (q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid_AMax !=
          q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.MAcc) {
        q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.MAcc =
          q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid_AMax;
        q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Flag = 1;
      }
    }
  }

  if (rtmIsMajorTimeStep(q_2dsfl_pos_cntrl_OG_M)) {
    /* Update for Atomic SubSystem: '<S1>/Bias Removal' */
    q_2dsfl_pos__BiasRemoval_Update(&q_2dsfl_pos_cntrl_OG_B.BiasRemoval,
      &q_2dsfl_pos_cntrl_OG_DW.BiasRemoval);

    /* End of Update for SubSystem: '<S1>/Bias Removal' */
  }

  /* Update for TransportDelay: '<S8>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)
      &q_2dsfl_pos_cntrl_OG_DW.TransportDelay_PWORK.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)
      &q_2dsfl_pos_cntrl_OG_DW.TransportDelay_PWORK.TUbufferPtrs[1];
    real_T simTime = q_2dsfl_pos_cntrl_OG_M->Timing.t[0];
    q_2dsfl_pos_cntrl_OG_DW.TransportDelay_IWORK.Head =
      ((q_2dsfl_pos_cntrl_OG_DW.TransportDelay_IWORK.Head <
        (q_2dsfl_pos_cntrl_OG_DW.TransportDelay_IWORK.CircularBufSize-1)) ?
       (q_2dsfl_pos_cntrl_OG_DW.TransportDelay_IWORK.Head+1) : 0);
    if (q_2dsfl_pos_cntrl_OG_DW.TransportDelay_IWORK.Head ==
        q_2dsfl_pos_cntrl_OG_DW.TransportDelay_IWORK.Tail) {
      q_2dsfl_pos_cntrl_OG_DW.TransportDelay_IWORK.Tail =
        ((q_2dsfl_pos_cntrl_OG_DW.TransportDelay_IWORK.Tail <
          (q_2dsfl_pos_cntrl_OG_DW.TransportDelay_IWORK.CircularBufSize-1)) ?
         (q_2dsfl_pos_cntrl_OG_DW.TransportDelay_IWORK.Tail+1) : 0);
    }

    (*tBuffer)[q_2dsfl_pos_cntrl_OG_DW.TransportDelay_IWORK.Head] = simTime;
    (*uBuffer)[q_2dsfl_pos_cntrl_OG_DW.TransportDelay_IWORK.Head] =
      q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid1_o1;
  }

  if (rtmIsMajorTimeStep(q_2dsfl_pos_cntrl_OG_M)) {
    /* Update for Atomic SubSystem: '<S2>/Bias Removal' */
    q_2dsfl_pos__BiasRemoval_Update(&q_2dsfl_pos_cntrl_OG_B.BiasRemoval_m,
      &q_2dsfl_pos_cntrl_OG_DW.BiasRemoval_m);

    /* End of Update for SubSystem: '<S2>/Bias Removal' */
  }

  /* Update for S-Function (continuous_sigmoid_block): '<S8>/Continuous Sigmoid1' */
  if (1) {
    {
      if (q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.Target !=
          q_2dsfl_pos_cntrl_OG_B.Gain1_o) {
        q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.Target =
          q_2dsfl_pos_cntrl_OG_B.Gain1_o;
        q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Flag = 1;
      }

      if (q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid1_VMax !=
          q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.MVel) {
        q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.MVel =
          q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid1_VMax;
        q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Flag = 1;
      }

      if (q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid1_AMax !=
          q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.MAcc) {
        q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.MAcc =
          q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid1_AMax;
        q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Flag = 1;
      }
    }
  }

  if (rtmIsMajorTimeStep(q_2dsfl_pos_cntrl_OG_M)) {
    rt_ertODEUpdateContinuousStates(&q_2dsfl_pos_cntrl_OG_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++q_2dsfl_pos_cntrl_OG_M->Timing.clockTick0)) {
    ++q_2dsfl_pos_cntrl_OG_M->Timing.clockTickH0;
  }

  q_2dsfl_pos_cntrl_OG_M->Timing.t[0] = rtsiGetSolverStopTime
    (&q_2dsfl_pos_cntrl_OG_M->solverInfo);

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
    if (!(++q_2dsfl_pos_cntrl_OG_M->Timing.clockTick1)) {
      ++q_2dsfl_pos_cntrl_OG_M->Timing.clockTickH1;
    }

    q_2dsfl_pos_cntrl_OG_M->Timing.t[1] =
      q_2dsfl_pos_cntrl_OG_M->Timing.clockTick1 *
      q_2dsfl_pos_cntrl_OG_M->Timing.stepSize1 +
      q_2dsfl_pos_cntrl_OG_M->Timing.clockTickH1 *
      q_2dsfl_pos_cntrl_OG_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void q_2dsfl_pos_cntrl_OG_derivatives(void)
{
  XDot_q_2dsfl_pos_cntrl_OG_T *_rtXdot;
  _rtXdot = ((XDot_q_2dsfl_pos_cntrl_OG_T *) q_2dsfl_pos_cntrl_OG_M->derivs);

  /* Derivatives for TransferFcn: '<S1>/Filter3' */
  _rtXdot->Filter3_CSTATE[0] = 0.0;
  _rtXdot->Filter3_CSTATE[0] += q_2dsfl_pos_cntrl_OG_P.Filter3_A[0] *
    q_2dsfl_pos_cntrl_OG_X.Filter3_CSTATE[0];
  _rtXdot->Filter3_CSTATE[1] = 0.0;
  _rtXdot->Filter3_CSTATE[0] += q_2dsfl_pos_cntrl_OG_P.Filter3_A[1] *
    q_2dsfl_pos_cntrl_OG_X.Filter3_CSTATE[1];
  _rtXdot->Filter3_CSTATE[1] += q_2dsfl_pos_cntrl_OG_X.Filter3_CSTATE[0];
  _rtXdot->Filter3_CSTATE[0] += q_2dsfl_pos_cntrl_OG_B.StraintoDeflection;

  /* Derivatives for TransferFcn: '<S1>/Derivative Filter1' */
  _rtXdot->DerivativeFilter1_CSTATE[0] = 0.0;
  _rtXdot->DerivativeFilter1_CSTATE[0] +=
    q_2dsfl_pos_cntrl_OG_P.DerivativeFilter1_A[0] *
    q_2dsfl_pos_cntrl_OG_X.DerivativeFilter1_CSTATE[0];
  _rtXdot->DerivativeFilter1_CSTATE[1] = 0.0;
  _rtXdot->DerivativeFilter1_CSTATE[0] +=
    q_2dsfl_pos_cntrl_OG_P.DerivativeFilter1_A[1] *
    q_2dsfl_pos_cntrl_OG_X.DerivativeFilter1_CSTATE[1];
  _rtXdot->DerivativeFilter1_CSTATE[1] +=
    q_2dsfl_pos_cntrl_OG_X.DerivativeFilter1_CSTATE[0];
  _rtXdot->DerivativeFilter1_CSTATE[0] +=
    q_2dsfl_pos_cntrl_OG_B.Motor1EncoderCalib;

  /* Derivatives for TransferFcn: '<S1>/Derivative Filter2' */
  _rtXdot->DerivativeFilter2_CSTATE[0] = 0.0;
  _rtXdot->DerivativeFilter2_CSTATE[0] +=
    q_2dsfl_pos_cntrl_OG_P.DerivativeFilter2_A[0] *
    q_2dsfl_pos_cntrl_OG_X.DerivativeFilter2_CSTATE[0];
  _rtXdot->DerivativeFilter2_CSTATE[1] = 0.0;
  _rtXdot->DerivativeFilter2_CSTATE[0] +=
    q_2dsfl_pos_cntrl_OG_P.DerivativeFilter2_A[1] *
    q_2dsfl_pos_cntrl_OG_X.DerivativeFilter2_CSTATE[1];
  _rtXdot->DerivativeFilter2_CSTATE[1] +=
    q_2dsfl_pos_cntrl_OG_X.DerivativeFilter2_CSTATE[0];
  _rtXdot->DerivativeFilter2_CSTATE[0] +=
    q_2dsfl_pos_cntrl_OG_B.StraintoDeflection;

  /* Derivatives for TransferFcn: '<S2>/Derivative Filter3' */
  _rtXdot->DerivativeFilter3_CSTATE[0] = 0.0;
  _rtXdot->DerivativeFilter3_CSTATE[0] +=
    q_2dsfl_pos_cntrl_OG_P.DerivativeFilter3_A[0] *
    q_2dsfl_pos_cntrl_OG_X.DerivativeFilter3_CSTATE[0];
  _rtXdot->DerivativeFilter3_CSTATE[1] = 0.0;
  _rtXdot->DerivativeFilter3_CSTATE[0] +=
    q_2dsfl_pos_cntrl_OG_P.DerivativeFilter3_A[1] *
    q_2dsfl_pos_cntrl_OG_X.DerivativeFilter3_CSTATE[1];
  _rtXdot->DerivativeFilter3_CSTATE[1] +=
    q_2dsfl_pos_cntrl_OG_X.DerivativeFilter3_CSTATE[0];
  _rtXdot->DerivativeFilter3_CSTATE[0] +=
    q_2dsfl_pos_cntrl_OG_B.StraintoDeflection_i;

  /* Derivatives for TransferFcn: '<S2>/Derivative Filter1' */
  _rtXdot->DerivativeFilter1_CSTATE_n[0] = 0.0;
  _rtXdot->DerivativeFilter1_CSTATE_n[0] +=
    q_2dsfl_pos_cntrl_OG_P.DerivativeFilter1_A_c[0] *
    q_2dsfl_pos_cntrl_OG_X.DerivativeFilter1_CSTATE_n[0];
  _rtXdot->DerivativeFilter1_CSTATE_n[1] = 0.0;
  _rtXdot->DerivativeFilter1_CSTATE_n[0] +=
    q_2dsfl_pos_cntrl_OG_P.DerivativeFilter1_A_c[1] *
    q_2dsfl_pos_cntrl_OG_X.DerivativeFilter1_CSTATE_n[1];
  _rtXdot->DerivativeFilter1_CSTATE_n[1] +=
    q_2dsfl_pos_cntrl_OG_X.DerivativeFilter1_CSTATE_n[0];
  _rtXdot->DerivativeFilter1_CSTATE_n[0] +=
    q_2dsfl_pos_cntrl_OG_B.Motor2EncoderCalib;

  /* Derivatives for TransferFcn: '<S2>/Derivative Filter2' */
  _rtXdot->DerivativeFilter2_CSTATE_p[0] = 0.0;
  _rtXdot->DerivativeFilter2_CSTATE_p[0] +=
    q_2dsfl_pos_cntrl_OG_P.DerivativeFilter2_A_m[0] *
    q_2dsfl_pos_cntrl_OG_X.DerivativeFilter2_CSTATE_p[0];
  _rtXdot->DerivativeFilter2_CSTATE_p[1] = 0.0;
  _rtXdot->DerivativeFilter2_CSTATE_p[0] +=
    q_2dsfl_pos_cntrl_OG_P.DerivativeFilter2_A_m[1] *
    q_2dsfl_pos_cntrl_OG_X.DerivativeFilter2_CSTATE_p[1];
  _rtXdot->DerivativeFilter2_CSTATE_p[1] +=
    q_2dsfl_pos_cntrl_OG_X.DerivativeFilter2_CSTATE_p[0];
  _rtXdot->DerivativeFilter2_CSTATE_p[0] +=
    q_2dsfl_pos_cntrl_OG_B.StraintoDeflection_i;
}

/* Model initialize function */
void q_2dsfl_pos_cntrl_OG_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: q_2dsfl_pos_cntrl_OG/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8", "0", &q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_2dsfl_pos_cntrl_OG_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options
      (q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card,
       "d0=digital;d1=digital;led=auto;update_rate=normal;decimation=1", 63);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_2dsfl_pos_cntrl_OG_M, _rt_error_message);
      return;
    }

    if ((q_2dsfl_pos_cntrl_OG_P.HILInitialize_CKPStart && !is_switching) ||
        (q_2dsfl_pos_cntrl_OG_P.HILInitialize_CKPEnter && is_switching)) {
      result = hil_set_clock_mode(q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card,
        (t_clock *) q_2dsfl_pos_cntrl_OG_P.HILInitialize_CKChannels, 2U,
        (t_clock_mode *) q_2dsfl_pos_cntrl_OG_P.HILInitialize_CKModes);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_pos_cntrl_OG_M, _rt_error_message);
        return;
      }
    }

    result = hil_watchdog_clear(q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_2dsfl_pos_cntrl_OG_M, _rt_error_message);
      return;
    }

    if ((q_2dsfl_pos_cntrl_OG_P.HILInitialize_AIPStart && !is_switching) ||
        (q_2dsfl_pos_cntrl_OG_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums =
          &q_2dsfl_pos_cntrl_OG_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (q_2dsfl_pos_cntrl_OG_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums =
          &q_2dsfl_pos_cntrl_OG_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = q_2dsfl_pos_cntrl_OG_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges
        (q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card,
         q_2dsfl_pos_cntrl_OG_P.HILInitialize_AIChannels, 8U,
         &q_2dsfl_pos_cntrl_OG_DW.HILInitialize_AIMinimums[0],
         &q_2dsfl_pos_cntrl_OG_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_pos_cntrl_OG_M, _rt_error_message);
        return;
      }
    }

    if ((q_2dsfl_pos_cntrl_OG_P.HILInitialize_AOPStart && !is_switching) ||
        (q_2dsfl_pos_cntrl_OG_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums =
          &q_2dsfl_pos_cntrl_OG_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (q_2dsfl_pos_cntrl_OG_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums =
          &q_2dsfl_pos_cntrl_OG_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = q_2dsfl_pos_cntrl_OG_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges
        (q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card,
         q_2dsfl_pos_cntrl_OG_P.HILInitialize_AOChannels, 8U,
         &q_2dsfl_pos_cntrl_OG_DW.HILInitialize_AOMinimums[0],
         &q_2dsfl_pos_cntrl_OG_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_pos_cntrl_OG_M, _rt_error_message);
        return;
      }
    }

    if ((q_2dsfl_pos_cntrl_OG_P.HILInitialize_AOStart && !is_switching) ||
        (q_2dsfl_pos_cntrl_OG_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &q_2dsfl_pos_cntrl_OG_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = q_2dsfl_pos_cntrl_OG_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card,
        q_2dsfl_pos_cntrl_OG_P.HILInitialize_AOChannels, 8U,
        &q_2dsfl_pos_cntrl_OG_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_pos_cntrl_OG_M, _rt_error_message);
        return;
      }
    }

    if (q_2dsfl_pos_cntrl_OG_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &q_2dsfl_pos_cntrl_OG_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = q_2dsfl_pos_cntrl_OG_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card,
         q_2dsfl_pos_cntrl_OG_P.HILInitialize_AOChannels, 8U,
         &q_2dsfl_pos_cntrl_OG_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_pos_cntrl_OG_M, _rt_error_message);
        return;
      }
    }

    result = hil_set_digital_directions
      (q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card,
       q_2dsfl_pos_cntrl_OG_P.HILInitialize_DIChannels, 24U,
       q_2dsfl_pos_cntrl_OG_P.HILInitialize_DOChannels, 8U);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_2dsfl_pos_cntrl_OG_M, _rt_error_message);
      return;
    }

    if ((q_2dsfl_pos_cntrl_OG_P.HILInitialize_DOStart && !is_switching) ||
        (q_2dsfl_pos_cntrl_OG_P.HILInitialize_DOEnter && is_switching)) {
      {
        int_T i1;
        boolean_T *dw_DOBits = &q_2dsfl_pos_cntrl_OG_DW.HILInitialize_DOBits[0];
        for (i1=0; i1 < 8; i1++) {
          dw_DOBits[i1] = q_2dsfl_pos_cntrl_OG_P.HILInitialize_DOInitial;
        }
      }

      result = hil_write_digital(q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card,
        q_2dsfl_pos_cntrl_OG_P.HILInitialize_DOChannels, 8U, (t_boolean *)
        &q_2dsfl_pos_cntrl_OG_DW.HILInitialize_DOBits[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_pos_cntrl_OG_M, _rt_error_message);
        return;
      }
    }

    if (q_2dsfl_pos_cntrl_OG_P.HILInitialize_DOReset) {
      {
        int_T i1;
        int32_T *dw_DOStates = &q_2dsfl_pos_cntrl_OG_DW.HILInitialize_DOStates[0];
        for (i1=0; i1 < 8; i1++) {
          dw_DOStates[i1] = q_2dsfl_pos_cntrl_OG_P.HILInitialize_DOWatchdog;
        }
      }

      result = hil_watchdog_set_digital_expiration_state
        (q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card,
         q_2dsfl_pos_cntrl_OG_P.HILInitialize_DOChannels, 8U, (const
          t_digital_state *) &q_2dsfl_pos_cntrl_OG_DW.HILInitialize_DOStates[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_pos_cntrl_OG_M, _rt_error_message);
        return;
      }
    }

    if ((q_2dsfl_pos_cntrl_OG_P.HILInitialize_EIPStart && !is_switching) ||
        (q_2dsfl_pos_cntrl_OG_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &q_2dsfl_pos_cntrl_OG_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] =
            q_2dsfl_pos_cntrl_OG_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card,
         q_2dsfl_pos_cntrl_OG_P.HILInitialize_EIChannels, 8U,
         (t_encoder_quadrature_mode *)
         &q_2dsfl_pos_cntrl_OG_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_pos_cntrl_OG_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_FilterFrequency =
          &q_2dsfl_pos_cntrl_OG_DW.HILInitialize_FilterFrequency[0];
        for (i1=0; i1 < 8; i1++) {
          dw_FilterFrequency[i1] =
            q_2dsfl_pos_cntrl_OG_P.HILInitialize_EIFrequency;
        }
      }

      result = hil_set_encoder_filter_frequency
        (q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card,
         q_2dsfl_pos_cntrl_OG_P.HILInitialize_EIChannels, 8U,
         &q_2dsfl_pos_cntrl_OG_DW.HILInitialize_FilterFrequency[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_pos_cntrl_OG_M, _rt_error_message);
        return;
      }
    }

    if ((q_2dsfl_pos_cntrl_OG_P.HILInitialize_EIStart && !is_switching) ||
        (q_2dsfl_pos_cntrl_OG_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &q_2dsfl_pos_cntrl_OG_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] =
            q_2dsfl_pos_cntrl_OG_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card,
        q_2dsfl_pos_cntrl_OG_P.HILInitialize_EIChannels, 8U,
        &q_2dsfl_pos_cntrl_OG_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_pos_cntrl_OG_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S1>/HIL Read Encoder Timebase' */

  /* S-Function Block: q_2dsfl_pos_cntrl_OG/1st Stage: 2-DOF SFL Robot: Actual Plant/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader
      (q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card,
       q_2dsfl_pos_cntrl_OG_P.HILReadEncoderTimebase_samples_,
       &q_2dsfl_pos_cntrl_OG_P.HILReadEncoderTimebase_channels, 1,
       &q_2dsfl_pos_cntrl_OG_DW.HILReadEncoderTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_2dsfl_pos_cntrl_OG_M, _rt_error_message);
    }
  }

  /* Start for S-Function (continuous_sigmoid_block): '<S7>/Continuous Sigmoid' */

  /* S-Function Block: q_2dsfl_pos_cntrl_OG/Stage 1 Setpoint/Continuous Sigmoid (continuous_sigmoid_block) */
  {
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_T1] = 0;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_T2] = 0;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_T3] = 0;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_X0] =
      q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid_XI;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_X1] =
      q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid_XI;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_X2] =
      q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid_XI;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_XD] =
      q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid_XI;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_V0] =
      q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid_VI;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_VP] = 0;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_AP] = 0;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[SIGMOID_PARAMETER_HOLD_OFF]
      = q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid_Hold;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.Time = 0;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.Target =
      q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid_XI;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.PPos =
      q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid_XI;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.PVel =
      q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid_VI;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Flag = 0;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.MVel =
      q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid_VMax;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.MAcc =
      q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid_AMax;
  }

  /* Start for Enabled SubSystem: '<S1>/Position Watchdog' */
  q_2dsfl_pos_cntrl_OG_DW.PositionWatchdog_MODE_l = false;

  /* End of Start for SubSystem: '<S1>/Position Watchdog' */

  /* Start for Atomic SubSystem: '<S1>/Bias Removal' */
  q_2dsfl_pos_c_BiasRemoval_Start(&q_2dsfl_pos_cntrl_OG_DW.BiasRemoval);

  /* End of Start for SubSystem: '<S1>/Bias Removal' */

  /* Start for TransportDelay: '<S8>/Transport Delay' */
  {
    real_T *pBuffer =
      &q_2dsfl_pos_cntrl_OG_DW.TransportDelay_RWORK.TUbufferArea[0];
    q_2dsfl_pos_cntrl_OG_DW.TransportDelay_IWORK.Tail = 0;
    q_2dsfl_pos_cntrl_OG_DW.TransportDelay_IWORK.Head = 0;
    q_2dsfl_pos_cntrl_OG_DW.TransportDelay_IWORK.Last = 0;
    q_2dsfl_pos_cntrl_OG_DW.TransportDelay_IWORK.CircularBufSize = 5000;
    pBuffer[0] = q_2dsfl_pos_cntrl_OG_P.TransportDelay_InitOutput;
    pBuffer[5000] = q_2dsfl_pos_cntrl_OG_M->Timing.t[0];
    q_2dsfl_pos_cntrl_OG_DW.TransportDelay_PWORK.TUbufferPtrs[0] = (void *)
      &pBuffer[0];
    q_2dsfl_pos_cntrl_OG_DW.TransportDelay_PWORK.TUbufferPtrs[1] = (void *)
      &pBuffer[5000];
  }

  /* Start for Atomic SubSystem: '<S2>/Bias Removal' */
  q_2dsfl_pos_c_BiasRemoval_Start(&q_2dsfl_pos_cntrl_OG_DW.BiasRemoval_m);

  /* End of Start for SubSystem: '<S2>/Bias Removal' */

  /* Start for Enabled SubSystem: '<S2>/Position Watchdog' */
  q_2dsfl_pos_cntrl_OG_DW.PositionWatchdog_MODE = false;

  /* End of Start for SubSystem: '<S2>/Position Watchdog' */
  /* Start for S-Function (continuous_sigmoid_block): '<S8>/Continuous Sigmoid1' */

  /* S-Function Block: q_2dsfl_pos_cntrl_OG/Stage 2 Setpoint/Continuous Sigmoid1 (continuous_sigmoid_block) */
  {
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_T1] = 0;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_T2] = 0;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_T3] = 0;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_X0] =
      q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid1_XI;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_X1] =
      q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid1_XI;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_X2] =
      q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid1_XI;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_XD] =
      q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid1_XI;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_V0] =
      q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid1_VI;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_VP] = 0;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_AP] = 0;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[SIGMOID_PARAMETER_HOLD_OFF]
      = q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid1_Hold;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.Time = 0;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.Target =
      q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid1_XI;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.PPos =
      q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid1_XI;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.PVel =
      q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid1_VI;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Flag = 0;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.MVel =
      q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid1_VMax;
    q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.MAcc =
      q_2dsfl_pos_cntrl_OG_P.ContinuousSigmoid1_AMax;
  }

  /* InitializeConditions for TransferFcn: '<S1>/Filter3' */
  q_2dsfl_pos_cntrl_OG_X.Filter3_CSTATE[0] = 0.0;

  /* InitializeConditions for TransferFcn: '<S1>/Derivative Filter1' */
  q_2dsfl_pos_cntrl_OG_X.DerivativeFilter1_CSTATE[0] = 0.0;

  /* InitializeConditions for TransferFcn: '<S1>/Derivative Filter2' */
  q_2dsfl_pos_cntrl_OG_X.DerivativeFilter2_CSTATE[0] = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Derivative Filter3' */
  q_2dsfl_pos_cntrl_OG_X.DerivativeFilter3_CSTATE[0] = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Derivative Filter1' */
  q_2dsfl_pos_cntrl_OG_X.DerivativeFilter1_CSTATE_n[0] = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Derivative Filter2' */
  q_2dsfl_pos_cntrl_OG_X.DerivativeFilter2_CSTATE_p[0] = 0.0;

  /* InitializeConditions for TransferFcn: '<S1>/Filter3' */
  q_2dsfl_pos_cntrl_OG_X.Filter3_CSTATE[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S1>/Derivative Filter1' */
  q_2dsfl_pos_cntrl_OG_X.DerivativeFilter1_CSTATE[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S1>/Derivative Filter2' */
  q_2dsfl_pos_cntrl_OG_X.DerivativeFilter2_CSTATE[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Derivative Filter3' */
  q_2dsfl_pos_cntrl_OG_X.DerivativeFilter3_CSTATE[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Derivative Filter1' */
  q_2dsfl_pos_cntrl_OG_X.DerivativeFilter1_CSTATE_n[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Derivative Filter2' */
  q_2dsfl_pos_cntrl_OG_X.DerivativeFilter2_CSTATE_p[1] = 0.0;

  /* SystemInitialize for Atomic SubSystem: '<S1>/Bias Removal' */
  q_2dsfl_pos_cn_BiasRemoval_Init(&q_2dsfl_pos_cntrl_OG_B.BiasRemoval,
    &q_2dsfl_pos_cntrl_OG_DW.BiasRemoval, &q_2dsfl_pos_cntrl_OG_P.BiasRemoval);

  /* End of SystemInitialize for SubSystem: '<S1>/Bias Removal' */

  /* SystemInitialize for Atomic SubSystem: '<S2>/Bias Removal' */
  q_2dsfl_pos_cn_BiasRemoval_Init(&q_2dsfl_pos_cntrl_OG_B.BiasRemoval_m,
    &q_2dsfl_pos_cntrl_OG_DW.BiasRemoval_m,
    &q_2dsfl_pos_cntrl_OG_P.BiasRemoval_m);

  /* End of SystemInitialize for SubSystem: '<S2>/Bias Removal' */
}

/* Model terminate function */
void q_2dsfl_pos_cntrl_OG_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: q_2dsfl_pos_cntrl_OG/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_digital_outputs = 0;
    hil_task_stop_all(q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card);
    hil_monitor_stop_all(q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card);
    is_switching = false;
    if ((q_2dsfl_pos_cntrl_OG_P.HILInitialize_AOTerminate && !is_switching) ||
        (q_2dsfl_pos_cntrl_OG_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &q_2dsfl_pos_cntrl_OG_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = q_2dsfl_pos_cntrl_OG_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((q_2dsfl_pos_cntrl_OG_P.HILInitialize_DOTerminate && !is_switching) ||
        (q_2dsfl_pos_cntrl_OG_P.HILInitialize_DOExit && is_switching)) {
      {
        int_T i1;
        boolean_T *dw_DOBits = &q_2dsfl_pos_cntrl_OG_DW.HILInitialize_DOBits[0];
        for (i1=0; i1 < 8; i1++) {
          dw_DOBits[i1] = q_2dsfl_pos_cntrl_OG_P.HILInitialize_DOFinal;
        }
      }

      num_final_digital_outputs = 8U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_digital_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card
                         , q_2dsfl_pos_cntrl_OG_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , NULL, 0
                         , q_2dsfl_pos_cntrl_OG_P.HILInitialize_DOChannels,
                         num_final_digital_outputs
                         , NULL, 0
                         , &q_2dsfl_pos_cntrl_OG_DW.HILInitialize_AOVoltages[0]
                         , NULL
                         , (t_boolean *)
                         &q_2dsfl_pos_cntrl_OG_DW.HILInitialize_DOBits[0]
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog
            (q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card,
             q_2dsfl_pos_cntrl_OG_P.HILInitialize_AOChannels,
             num_final_analog_outputs,
             &q_2dsfl_pos_cntrl_OG_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_digital_outputs > 0) {
          local_result = hil_write_digital
            (q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card,
             q_2dsfl_pos_cntrl_OG_P.HILInitialize_DOChannels,
             num_final_digital_outputs, (t_boolean *)
             &q_2dsfl_pos_cntrl_OG_DW.HILInitialize_DOBits[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(q_2dsfl_pos_cntrl_OG_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card);
    hil_monitor_delete_all(q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card);
    hil_close(q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card);
    q_2dsfl_pos_cntrl_OG_DW.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  q_2dsfl_pos_cntrl_OG_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  q_2dsfl_pos_cntrl_OG_update();
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
  q_2dsfl_pos_cntrl_OG_initialize();
}

void MdlTerminate(void)
{
  q_2dsfl_pos_cntrl_OG_terminate();
}

/* Registration function */
RT_MODEL_q_2dsfl_pos_cntrl_OG_T *q_2dsfl_pos_cntrl_OG(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)q_2dsfl_pos_cntrl_OG_M, 0,
                sizeof(RT_MODEL_q_2dsfl_pos_cntrl_OG_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&q_2dsfl_pos_cntrl_OG_M->solverInfo,
                          &q_2dsfl_pos_cntrl_OG_M->Timing.simTimeStep);
    rtsiSetTPtr(&q_2dsfl_pos_cntrl_OG_M->solverInfo, &rtmGetTPtr
                (q_2dsfl_pos_cntrl_OG_M));
    rtsiSetStepSizePtr(&q_2dsfl_pos_cntrl_OG_M->solverInfo,
                       &q_2dsfl_pos_cntrl_OG_M->Timing.stepSize0);
    rtsiSetdXPtr(&q_2dsfl_pos_cntrl_OG_M->solverInfo,
                 &q_2dsfl_pos_cntrl_OG_M->derivs);
    rtsiSetContStatesPtr(&q_2dsfl_pos_cntrl_OG_M->solverInfo, (real_T **)
                         &q_2dsfl_pos_cntrl_OG_M->contStates);
    rtsiSetNumContStatesPtr(&q_2dsfl_pos_cntrl_OG_M->solverInfo,
      &q_2dsfl_pos_cntrl_OG_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&q_2dsfl_pos_cntrl_OG_M->solverInfo,
      &q_2dsfl_pos_cntrl_OG_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&q_2dsfl_pos_cntrl_OG_M->solverInfo,
      &q_2dsfl_pos_cntrl_OG_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&q_2dsfl_pos_cntrl_OG_M->solverInfo,
      &q_2dsfl_pos_cntrl_OG_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&q_2dsfl_pos_cntrl_OG_M->solverInfo,
                          (&rtmGetErrorStatus(q_2dsfl_pos_cntrl_OG_M)));
    rtsiSetRTModelPtr(&q_2dsfl_pos_cntrl_OG_M->solverInfo,
                      q_2dsfl_pos_cntrl_OG_M);
  }

  rtsiSetSimTimeStep(&q_2dsfl_pos_cntrl_OG_M->solverInfo, MAJOR_TIME_STEP);
  q_2dsfl_pos_cntrl_OG_M->intgData.f[0] = q_2dsfl_pos_cntrl_OG_M->odeF[0];
  q_2dsfl_pos_cntrl_OG_M->contStates = ((real_T *) &q_2dsfl_pos_cntrl_OG_X);
  rtsiSetSolverData(&q_2dsfl_pos_cntrl_OG_M->solverInfo, (void *)
                    &q_2dsfl_pos_cntrl_OG_M->intgData);
  rtsiSetSolverName(&q_2dsfl_pos_cntrl_OG_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = q_2dsfl_pos_cntrl_OG_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    q_2dsfl_pos_cntrl_OG_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    q_2dsfl_pos_cntrl_OG_M->Timing.sampleTimes =
      (&q_2dsfl_pos_cntrl_OG_M->Timing.sampleTimesArray[0]);
    q_2dsfl_pos_cntrl_OG_M->Timing.offsetTimes =
      (&q_2dsfl_pos_cntrl_OG_M->Timing.offsetTimesArray[0]);

    /* task periods */
    q_2dsfl_pos_cntrl_OG_M->Timing.sampleTimes[0] = (0.0);
    q_2dsfl_pos_cntrl_OG_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    q_2dsfl_pos_cntrl_OG_M->Timing.offsetTimes[0] = (0.0);
    q_2dsfl_pos_cntrl_OG_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(q_2dsfl_pos_cntrl_OG_M, &q_2dsfl_pos_cntrl_OG_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = q_2dsfl_pos_cntrl_OG_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    q_2dsfl_pos_cntrl_OG_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(q_2dsfl_pos_cntrl_OG_M, -1);
  q_2dsfl_pos_cntrl_OG_M->Timing.stepSize0 = 0.002;
  q_2dsfl_pos_cntrl_OG_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  q_2dsfl_pos_cntrl_OG_M->Sizes.checksums[0] = (2140628558U);
  q_2dsfl_pos_cntrl_OG_M->Sizes.checksums[1] = (376027466U);
  q_2dsfl_pos_cntrl_OG_M->Sizes.checksums[2] = (2171722187U);
  q_2dsfl_pos_cntrl_OG_M->Sizes.checksums[3] = (3706319149U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[17];
    q_2dsfl_pos_cntrl_OG_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = (sysRanDType *)
      &q_2dsfl_pos_cntrl_OG_DW.BiasRemoval.EnabledMovingAverage_SubsysRanB;
    systemRan[6] = (sysRanDType *)
      &q_2dsfl_pos_cntrl_OG_DW.BiasRemoval.SwitchCaseActionSubsystem_Subsy;
    systemRan[7] = (sysRanDType *)
      &q_2dsfl_pos_cntrl_OG_DW.BiasRemoval.SwitchCaseActionSubsystem1_Subs;
    systemRan[8] = (sysRanDType *)
      &q_2dsfl_pos_cntrl_OG_DW.BiasRemoval.SwitchCaseActionSubsystem2_Subs;
    systemRan[9] = &rtAlwaysEnabled;
    systemRan[10] = (sysRanDType *)
      &q_2dsfl_pos_cntrl_OG_DW.PositionWatchdog_SubsysRanBC_c;
    systemRan[11] = (sysRanDType *)
      &q_2dsfl_pos_cntrl_OG_DW.BiasRemoval_m.EnabledMovingAverage_SubsysRanB;
    systemRan[12] = (sysRanDType *)
      &q_2dsfl_pos_cntrl_OG_DW.BiasRemoval_m.SwitchCaseActionSubsystem_Subsy;
    systemRan[13] = (sysRanDType *)
      &q_2dsfl_pos_cntrl_OG_DW.BiasRemoval_m.SwitchCaseActionSubsystem1_Subs;
    systemRan[14] = (sysRanDType *)
      &q_2dsfl_pos_cntrl_OG_DW.BiasRemoval_m.SwitchCaseActionSubsystem2_Subs;
    systemRan[15] = &rtAlwaysEnabled;
    systemRan[16] = (sysRanDType *)
      &q_2dsfl_pos_cntrl_OG_DW.PositionWatchdog_SubsysRanBC;
    rteiSetModelMappingInfoPtr(q_2dsfl_pos_cntrl_OG_M->extModeInfo,
      &q_2dsfl_pos_cntrl_OG_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(q_2dsfl_pos_cntrl_OG_M->extModeInfo,
                        q_2dsfl_pos_cntrl_OG_M->Sizes.checksums);
    rteiSetTPtr(q_2dsfl_pos_cntrl_OG_M->extModeInfo, rtmGetTPtr
                (q_2dsfl_pos_cntrl_OG_M));
  }

  q_2dsfl_pos_cntrl_OG_M->solverInfoPtr = (&q_2dsfl_pos_cntrl_OG_M->solverInfo);
  q_2dsfl_pos_cntrl_OG_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&q_2dsfl_pos_cntrl_OG_M->solverInfo, 0.002);
  rtsiSetSolverMode(&q_2dsfl_pos_cntrl_OG_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  q_2dsfl_pos_cntrl_OG_M->blockIO = ((void *) &q_2dsfl_pos_cntrl_OG_B);
  (void) memset(((void *) &q_2dsfl_pos_cntrl_OG_B), 0,
                sizeof(B_q_2dsfl_pos_cntrl_OG_T));

  {
    q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid_o1 = 0.0;
    q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid_o2 = 0.0;
    q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid_o3 = 0.0;
    q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid_o4 = 0.0;
    q_2dsfl_pos_cntrl_OG_B.u100[0] = 0.0;
    q_2dsfl_pos_cntrl_OG_B.u100[1] = 0.0;
    q_2dsfl_pos_cntrl_OG_B.u100[2] = 0.0;
    q_2dsfl_pos_cntrl_OG_B.u100[3] = 0.0;
    q_2dsfl_pos_cntrl_OG_B.Motor1EncoderCalib = 0.0;
    q_2dsfl_pos_cntrl_OG_B.Gain[0] = 0.0;
    q_2dsfl_pos_cntrl_OG_B.Gain[1] = 0.0;
    q_2dsfl_pos_cntrl_OG_B.Gain_n[0] = 0.0;
    q_2dsfl_pos_cntrl_OG_B.Gain_n[1] = 0.0;
    q_2dsfl_pos_cntrl_OG_B.ManualSwitch1[0] = 0.0;
    q_2dsfl_pos_cntrl_OG_B.ManualSwitch1[1] = 0.0;
    q_2dsfl_pos_cntrl_OG_B.ManualSwitch1[2] = 0.0;
    q_2dsfl_pos_cntrl_OG_B.ManualSwitch1[3] = 0.0;
    q_2dsfl_pos_cntrl_OG_B.Im_r1Saturation = 0.0;
    q_2dsfl_pos_cntrl_OG_B.VoltstoAmps = 0.0;
    q_2dsfl_pos_cntrl_OG_B.AmpstoVolts = 0.0;
    q_2dsfl_pos_cntrl_OG_B.positiveCCW = 0.0;
    q_2dsfl_pos_cntrl_OG_B.StraintoDeflection = 0.0;
    q_2dsfl_pos_cntrl_OG_B.Gain1 = 0.0;
    q_2dsfl_pos_cntrl_OG_B.Motor2EncoderCalib = 0.0;
    q_2dsfl_pos_cntrl_OG_B.Gain_m[0] = 0.0;
    q_2dsfl_pos_cntrl_OG_B.Gain_m[1] = 0.0;
    q_2dsfl_pos_cntrl_OG_B.Gain_b[0] = 0.0;
    q_2dsfl_pos_cntrl_OG_B.Gain_b[1] = 0.0;
    q_2dsfl_pos_cntrl_OG_B.positiveCCW_h = 0.0;
    q_2dsfl_pos_cntrl_OG_B.VoltstoStrain = 0.0;
    q_2dsfl_pos_cntrl_OG_B.ManualSwitch2[0] = 0.0;
    q_2dsfl_pos_cntrl_OG_B.ManualSwitch2[1] = 0.0;
    q_2dsfl_pos_cntrl_OG_B.ManualSwitch2[2] = 0.0;
    q_2dsfl_pos_cntrl_OG_B.ManualSwitch2[3] = 0.0;
    q_2dsfl_pos_cntrl_OG_B.Im_r2Saturation = 0.0;
    q_2dsfl_pos_cntrl_OG_B.VoltstoAmps_i = 0.0;
    q_2dsfl_pos_cntrl_OG_B.AmpstoVolts_g = 0.0;
    q_2dsfl_pos_cntrl_OG_B.StraintoDeflection_i = 0.0;
    q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid1_o1 = 0.0;
    q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid1_o2 = 0.0;
    q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid1_o3 = 0.0;
    q_2dsfl_pos_cntrl_OG_B.ContinuousSigmoid1_o4 = 0.0;
    q_2dsfl_pos_cntrl_OG_B.Gain1_o = 0.0;
    q_2dsfl_pos_cntrl_OG_B.BiasRemoval_m.Switch = 0.0;
    q_2dsfl_pos_cntrl_OG_B.BiasRemoval_m.VVavg = 0.0;
    q_2dsfl_pos_cntrl_OG_B.BiasRemoval_m.Vin = 0.0;
    q_2dsfl_pos_cntrl_OG_B.BiasRemoval_m.Constant = 0.0;
    q_2dsfl_pos_cntrl_OG_B.BiasRemoval_m.Count = 0.0;
    q_2dsfl_pos_cntrl_OG_B.BiasRemoval_m.Sum = 0.0;
    q_2dsfl_pos_cntrl_OG_B.BiasRemoval_m.div = 0.0;
    q_2dsfl_pos_cntrl_OG_B.BiasRemoval.Switch = 0.0;
    q_2dsfl_pos_cntrl_OG_B.BiasRemoval.VVavg = 0.0;
    q_2dsfl_pos_cntrl_OG_B.BiasRemoval.Vin = 0.0;
    q_2dsfl_pos_cntrl_OG_B.BiasRemoval.Constant = 0.0;
    q_2dsfl_pos_cntrl_OG_B.BiasRemoval.Count = 0.0;
    q_2dsfl_pos_cntrl_OG_B.BiasRemoval.Sum = 0.0;
    q_2dsfl_pos_cntrl_OG_B.BiasRemoval.div = 0.0;
  }

  /* parameters */
  q_2dsfl_pos_cntrl_OG_M->defaultParam = ((real_T *)&q_2dsfl_pos_cntrl_OG_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &q_2dsfl_pos_cntrl_OG_X;
    q_2dsfl_pos_cntrl_OG_M->contStates = (x);
    (void) memset((void *)&q_2dsfl_pos_cntrl_OG_X, 0,
                  sizeof(X_q_2dsfl_pos_cntrl_OG_T));
  }

  /* states (dwork) */
  q_2dsfl_pos_cntrl_OG_M->dwork = ((void *) &q_2dsfl_pos_cntrl_OG_DW);
  (void) memset((void *)&q_2dsfl_pos_cntrl_OG_DW, 0,
                sizeof(DW_q_2dsfl_pos_cntrl_OG_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      q_2dsfl_pos_cntrl_OG_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      q_2dsfl_pos_cntrl_OG_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      q_2dsfl_pos_cntrl_OG_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      q_2dsfl_pos_cntrl_OG_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      q_2dsfl_pos_cntrl_OG_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      q_2dsfl_pos_cntrl_OG_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 11; i++) {
      q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_Sigmoid[i] = 0.0;
    }
  }

  q_2dsfl_pos_cntrl_OG_DW.HILReadAnalog_Buffer[0] = 0.0;
  q_2dsfl_pos_cntrl_OG_DW.HILReadAnalog_Buffer[1] = 0.0;
  q_2dsfl_pos_cntrl_OG_DW.HILReadAnalog_Buffer_p[0] = 0.0;
  q_2dsfl_pos_cntrl_OG_DW.HILReadAnalog_Buffer_p[1] = 0.0;

  {
    int32_T i;
    for (i = 0; i < 11; i++) {
      q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_Sigmoid[i] = 0.0;
    }
  }

  q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.Time = 0.0;
  q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.Target = 0.0;
  q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.PPos = 0.0;
  q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.PVel = 0.0;
  q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.MVel = 0.0;
  q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid_RWORK.MAcc = 0.0;
  q_2dsfl_pos_cntrl_OG_DW.TransportDelay_RWORK.modelTStart = 0.0;

  {
    int32_T i;
    for (i = 0; i < 10000; i++) {
      q_2dsfl_pos_cntrl_OG_DW.TransportDelay_RWORK.TUbufferArea[i] = 0.0;
    }
  }

  q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.Time = 0.0;
  q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.Target = 0.0;
  q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.PPos = 0.0;
  q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.PVel = 0.0;
  q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.MVel = 0.0;
  q_2dsfl_pos_cntrl_OG_DW.ContinuousSigmoid1_RWORK.MAcc = 0.0;
  q_2dsfl_pos_cntrl_OG_DW.BiasRemoval_m.UnitDelay_DSTATE = 0.0;
  q_2dsfl_pos_cntrl_OG_DW.BiasRemoval_m.Sumk1n1xk_DSTATE = 0.0;
  q_2dsfl_pos_cntrl_OG_DW.BiasRemoval.UnitDelay_DSTATE = 0.0;
  q_2dsfl_pos_cntrl_OG_DW.BiasRemoval.Sumk1n1xk_DSTATE = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    q_2dsfl_pos_cntrl_OG_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 17;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  q_2dsfl_pos_cntrl_OG_M->Sizes.numContStates = (12);/* Number of continuous states */
  q_2dsfl_pos_cntrl_OG_M->Sizes.numPeriodicContStates = (0);/* Number of periodic continuous states */
  q_2dsfl_pos_cntrl_OG_M->Sizes.numY = (0);/* Number of model outputs */
  q_2dsfl_pos_cntrl_OG_M->Sizes.numU = (0);/* Number of model inputs */
  q_2dsfl_pos_cntrl_OG_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  q_2dsfl_pos_cntrl_OG_M->Sizes.numSampTimes = (2);/* Number of sample times */
  q_2dsfl_pos_cntrl_OG_M->Sizes.numBlocks = (153);/* Number of blocks */
  q_2dsfl_pos_cntrl_OG_M->Sizes.numBlockIO = (58);/* Number of block outputs */
  q_2dsfl_pos_cntrl_OG_M->Sizes.numBlockPrms = (289);/* Sum of parameter "widths" */
  return q_2dsfl_pos_cntrl_OG_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
