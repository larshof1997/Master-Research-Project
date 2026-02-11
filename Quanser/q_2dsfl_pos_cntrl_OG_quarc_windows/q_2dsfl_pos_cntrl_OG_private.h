/*
 * q_2dsfl_pos_cntrl_OG_private.h
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

#ifndef RTW_HEADER_q_2dsfl_pos_cntrl_OG_private_h_
#define RTW_HEADER_q_2dsfl_pos_cntrl_OG_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "zero_crossing_types.h"
#include "q_2dsfl_pos_cntrl_OG.h"

/* A global buffer for storing error messages (defined in quanser_common library) */
EXTERN char _rt_error_message[512];
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
  ;
extern void q_2dsfl_pos_cn_BiasRemoval_Init(B_BiasRemoval_q_2dsfl_pos_cnt_T
  *localB, DW_BiasRemoval_q_2dsfl_pos_cn_T *localDW,
  P_BiasRemoval_q_2dsfl_pos_cnt_T *localP);
extern void q_2dsfl_pos_c_BiasRemoval_Start(DW_BiasRemoval_q_2dsfl_pos_cn_T
  *localDW);
extern void q_2dsfl_pos__BiasRemoval_Update(B_BiasRemoval_q_2dsfl_pos_cnt_T
  *localB, DW_BiasRemoval_q_2dsfl_pos_cn_T *localDW);
extern void q_2dsfl_pos_cntrl_O_BiasRemoval(RT_MODEL_q_2dsfl_pos_cntrl_OG_T *
  const q_2dsfl_pos_cntrl_OG_M, real_T rtu_V, B_BiasRemoval_q_2dsfl_pos_cnt_T
  *localB, DW_BiasRemoval_q_2dsfl_pos_cn_T *localDW,
  P_BiasRemoval_q_2dsfl_pos_cnt_T *localP, real_T rtp_switch_id, real_T
  rtp_start_time, real_T rtp_end_time);

/* private model entry point functions */
extern void q_2dsfl_pos_cntrl_OG_derivatives(void);

#endif                                 /* RTW_HEADER_q_2dsfl_pos_cntrl_OG_private_h_ */
