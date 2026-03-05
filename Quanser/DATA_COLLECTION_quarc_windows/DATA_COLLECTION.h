/*
 * DATA_COLLECTION.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "DATA_COLLECTION".
 *
 * Model version              : 1.119
 * Simulink Coder version : 9.0 (R2018b) 24-May-2018
 * C source code generated on : Thu Mar  5 12:38:24 2026
 *
 * Target selection: quarc_windows.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_DATA_COLLECTION_h_
#define RTW_HEADER_DATA_COLLECTION_h_
#include <math.h>
#include <string.h>
#ifndef DATA_COLLECTION_COMMON_INCLUDES_
# define DATA_COLLECTION_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "dt_info.h"
#include "ext_work.h"
#include "hil.h"
#include "quanser_messages.h"
#include "quanser_extern.h"
#endif                                 /* DATA_COLLECTION_COMMON_INCLUDES_ */

#include "DATA_COLLECTION_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetBlockIO
# define rtmGetBlockIO(rtm)            ((rtm)->blockIO)
#endif

#ifndef rtmSetBlockIO
# define rtmSetBlockIO(rtm, val)       ((rtm)->blockIO = (val))
#endif

#ifndef rtmGetChecksums
# define rtmGetChecksums(rtm)          ((rtm)->Sizes.checksums)
#endif

#ifndef rtmSetChecksums
# define rtmSetChecksums(rtm, val)     ((rtm)->Sizes.checksums = (val))
#endif

#ifndef rtmGetConstBlockIO
# define rtmGetConstBlockIO(rtm)       ((rtm)->constBlockIO)
#endif

#ifndef rtmSetConstBlockIO
# define rtmSetConstBlockIO(rtm, val)  ((rtm)->constBlockIO = (val))
#endif

#ifndef rtmGetContStateDisabled
# define rtmGetContStateDisabled(rtm)  ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
# define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
# define rtmGetContStates(rtm)         ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
# define rtmSetContStates(rtm, val)    ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
# define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
# define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetCtrlRateMdlRefTiming
# define rtmGetCtrlRateMdlRefTiming(rtm) ()
#endif

#ifndef rtmSetCtrlRateMdlRefTiming
# define rtmSetCtrlRateMdlRefTiming(rtm, val) ()
#endif

#ifndef rtmGetCtrlRateMdlRefTimingPtr
# define rtmGetCtrlRateMdlRefTimingPtr(rtm) ()
#endif

#ifndef rtmSetCtrlRateMdlRefTimingPtr
# define rtmSetCtrlRateMdlRefTimingPtr(rtm, val) ()
#endif

#ifndef rtmGetCtrlRateNumTicksToNextHit
# define rtmGetCtrlRateNumTicksToNextHit(rtm) ()
#endif

#ifndef rtmSetCtrlRateNumTicksToNextHit
# define rtmSetCtrlRateNumTicksToNextHit(rtm, val) ()
#endif

#ifndef rtmGetDataMapInfo
# define rtmGetDataMapInfo(rtm)        ()
#endif

#ifndef rtmSetDataMapInfo
# define rtmSetDataMapInfo(rtm, val)   ()
#endif

#ifndef rtmGetDefaultParam
# define rtmGetDefaultParam(rtm)       ((rtm)->defaultParam)
#endif

#ifndef rtmSetDefaultParam
# define rtmSetDefaultParam(rtm, val)  ((rtm)->defaultParam = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
# define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
# define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetDirectFeedThrough
# define rtmGetDirectFeedThrough(rtm)  ((rtm)->Sizes.sysDirFeedThru)
#endif

#ifndef rtmSetDirectFeedThrough
# define rtmSetDirectFeedThrough(rtm, val) ((rtm)->Sizes.sysDirFeedThru = (val))
#endif

#ifndef rtmGetErrorStatusFlag
# define rtmGetErrorStatusFlag(rtm)    ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatusFlag
# define rtmSetErrorStatusFlag(rtm, val) ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmSetFinalTime
# define rtmSetFinalTime(rtm, val)     ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmGetFirstInitCondFlag
# define rtmGetFirstInitCondFlag(rtm)  ()
#endif

#ifndef rtmSetFirstInitCondFlag
# define rtmSetFirstInitCondFlag(rtm, val) ()
#endif

#ifndef rtmGetIntgData
# define rtmGetIntgData(rtm)           ()
#endif

#ifndef rtmSetIntgData
# define rtmSetIntgData(rtm, val)      ()
#endif

#ifndef rtmGetMdlRefGlobalTID
# define rtmGetMdlRefGlobalTID(rtm)    ()
#endif

#ifndef rtmSetMdlRefGlobalTID
# define rtmSetMdlRefGlobalTID(rtm, val) ()
#endif

#ifndef rtmGetMdlRefTriggerTID
# define rtmGetMdlRefTriggerTID(rtm)   ()
#endif

#ifndef rtmSetMdlRefTriggerTID
# define rtmSetMdlRefTriggerTID(rtm, val) ()
#endif

#ifndef rtmGetModelMappingInfo
# define rtmGetModelMappingInfo(rtm)   ((rtm)->SpecialInfo.mappingInfo)
#endif

#ifndef rtmSetModelMappingInfo
# define rtmSetModelMappingInfo(rtm, val) ((rtm)->SpecialInfo.mappingInfo = (val))
#endif

#ifndef rtmGetModelName
# define rtmGetModelName(rtm)          ((rtm)->modelName)
#endif

#ifndef rtmSetModelName
# define rtmSetModelName(rtm, val)     ((rtm)->modelName = (val))
#endif

#ifndef rtmGetNonInlinedSFcns
# define rtmGetNonInlinedSFcns(rtm)    ()
#endif

#ifndef rtmSetNonInlinedSFcns
# define rtmSetNonInlinedSFcns(rtm, val) ()
#endif

#ifndef rtmGetNumBlockIO
# define rtmGetNumBlockIO(rtm)         ((rtm)->Sizes.numBlockIO)
#endif

#ifndef rtmSetNumBlockIO
# define rtmSetNumBlockIO(rtm, val)    ((rtm)->Sizes.numBlockIO = (val))
#endif

#ifndef rtmGetNumBlockParams
# define rtmGetNumBlockParams(rtm)     ((rtm)->Sizes.numBlockPrms)
#endif

#ifndef rtmSetNumBlockParams
# define rtmSetNumBlockParams(rtm, val) ((rtm)->Sizes.numBlockPrms = (val))
#endif

#ifndef rtmGetNumBlocks
# define rtmGetNumBlocks(rtm)          ((rtm)->Sizes.numBlocks)
#endif

#ifndef rtmSetNumBlocks
# define rtmSetNumBlocks(rtm, val)     ((rtm)->Sizes.numBlocks = (val))
#endif

#ifndef rtmGetNumContStates
# define rtmGetNumContStates(rtm)      ((rtm)->Sizes.numContStates)
#endif

#ifndef rtmSetNumContStates
# define rtmSetNumContStates(rtm, val) ((rtm)->Sizes.numContStates = (val))
#endif

#ifndef rtmGetNumDWork
# define rtmGetNumDWork(rtm)           ((rtm)->Sizes.numDwork)
#endif

#ifndef rtmSetNumDWork
# define rtmSetNumDWork(rtm, val)      ((rtm)->Sizes.numDwork = (val))
#endif

#ifndef rtmGetNumInputPorts
# define rtmGetNumInputPorts(rtm)      ((rtm)->Sizes.numIports)
#endif

#ifndef rtmSetNumInputPorts
# define rtmSetNumInputPorts(rtm, val) ((rtm)->Sizes.numIports = (val))
#endif

#ifndef rtmGetNumNonSampledZCs
# define rtmGetNumNonSampledZCs(rtm)   ((rtm)->Sizes.numNonSampZCs)
#endif

#ifndef rtmSetNumNonSampledZCs
# define rtmSetNumNonSampledZCs(rtm, val) ((rtm)->Sizes.numNonSampZCs = (val))
#endif

#ifndef rtmGetNumOutputPorts
# define rtmGetNumOutputPorts(rtm)     ((rtm)->Sizes.numOports)
#endif

#ifndef rtmSetNumOutputPorts
# define rtmSetNumOutputPorts(rtm, val) ((rtm)->Sizes.numOports = (val))
#endif

#ifndef rtmGetNumPeriodicContStates
# define rtmGetNumPeriodicContStates(rtm) ((rtm)->Sizes.numPeriodicContStates)
#endif

#ifndef rtmSetNumPeriodicContStates
# define rtmSetNumPeriodicContStates(rtm, val) ((rtm)->Sizes.numPeriodicContStates = (val))
#endif

#ifndef rtmGetNumSFcnParams
# define rtmGetNumSFcnParams(rtm)      ((rtm)->Sizes.numSFcnPrms)
#endif

#ifndef rtmSetNumSFcnParams
# define rtmSetNumSFcnParams(rtm, val) ((rtm)->Sizes.numSFcnPrms = (val))
#endif

#ifndef rtmGetNumSFunctions
# define rtmGetNumSFunctions(rtm)      ((rtm)->Sizes.numSFcns)
#endif

#ifndef rtmSetNumSFunctions
# define rtmSetNumSFunctions(rtm, val) ((rtm)->Sizes.numSFcns = (val))
#endif

#ifndef rtmGetNumSampleTimes
# define rtmGetNumSampleTimes(rtm)     ((rtm)->Sizes.numSampTimes)
#endif

#ifndef rtmSetNumSampleTimes
# define rtmSetNumSampleTimes(rtm, val) ((rtm)->Sizes.numSampTimes = (val))
#endif

#ifndef rtmGetNumU
# define rtmGetNumU(rtm)               ((rtm)->Sizes.numU)
#endif

#ifndef rtmSetNumU
# define rtmSetNumU(rtm, val)          ((rtm)->Sizes.numU = (val))
#endif

#ifndef rtmGetNumY
# define rtmGetNumY(rtm)               ((rtm)->Sizes.numY)
#endif

#ifndef rtmSetNumY
# define rtmSetNumY(rtm, val)          ((rtm)->Sizes.numY = (val))
#endif

#ifndef rtmGetOdeF
# define rtmGetOdeF(rtm)               ()
#endif

#ifndef rtmSetOdeF
# define rtmSetOdeF(rtm, val)          ()
#endif

#ifndef rtmGetOdeY
# define rtmGetOdeY(rtm)               ()
#endif

#ifndef rtmSetOdeY
# define rtmSetOdeY(rtm, val)          ()
#endif

#ifndef rtmGetOffsetTimeArray
# define rtmGetOffsetTimeArray(rtm)    ((rtm)->Timing.offsetTimesArray)
#endif

#ifndef rtmSetOffsetTimeArray
# define rtmSetOffsetTimeArray(rtm, val) ((rtm)->Timing.offsetTimesArray = (val))
#endif

#ifndef rtmGetOffsetTimePtr
# define rtmGetOffsetTimePtr(rtm)      ((rtm)->Timing.offsetTimes)
#endif

#ifndef rtmSetOffsetTimePtr
# define rtmSetOffsetTimePtr(rtm, val) ((rtm)->Timing.offsetTimes = (val))
#endif

#ifndef rtmGetOptions
# define rtmGetOptions(rtm)            ((rtm)->Sizes.options)
#endif

#ifndef rtmSetOptions
# define rtmSetOptions(rtm, val)       ((rtm)->Sizes.options = (val))
#endif

#ifndef rtmGetParamIsMalloced
# define rtmGetParamIsMalloced(rtm)    ()
#endif

#ifndef rtmSetParamIsMalloced
# define rtmSetParamIsMalloced(rtm, val) ()
#endif

#ifndef rtmGetPath
# define rtmGetPath(rtm)               ((rtm)->path)
#endif

#ifndef rtmSetPath
# define rtmSetPath(rtm, val)          ((rtm)->path = (val))
#endif

#ifndef rtmGetPerTaskSampleHits
# define rtmGetPerTaskSampleHits(rtm)  ()
#endif

#ifndef rtmSetPerTaskSampleHits
# define rtmSetPerTaskSampleHits(rtm, val) ()
#endif

#ifndef rtmGetPerTaskSampleHitsArray
# define rtmGetPerTaskSampleHitsArray(rtm) ((rtm)->Timing.perTaskSampleHitsArray)
#endif

#ifndef rtmSetPerTaskSampleHitsArray
# define rtmSetPerTaskSampleHitsArray(rtm, val) ((rtm)->Timing.perTaskSampleHitsArray = (val))
#endif

#ifndef rtmGetPerTaskSampleHitsPtr
# define rtmGetPerTaskSampleHitsPtr(rtm) ((rtm)->Timing.perTaskSampleHits)
#endif

#ifndef rtmSetPerTaskSampleHitsPtr
# define rtmSetPerTaskSampleHitsPtr(rtm, val) ((rtm)->Timing.perTaskSampleHits = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
# define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
# define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
# define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
# define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetPrevZCSigState
# define rtmGetPrevZCSigState(rtm)     ((rtm)->prevZCSigState)
#endif

#ifndef rtmSetPrevZCSigState
# define rtmSetPrevZCSigState(rtm, val) ((rtm)->prevZCSigState = (val))
#endif

#ifndef rtmGetRTWExtModeInfo
# define rtmGetRTWExtModeInfo(rtm)     ((rtm)->extModeInfo)
#endif

#ifndef rtmSetRTWExtModeInfo
# define rtmSetRTWExtModeInfo(rtm, val) ((rtm)->extModeInfo = (val))
#endif

#ifndef rtmGetRTWGeneratedSFcn
# define rtmGetRTWGeneratedSFcn(rtm)   ((rtm)->Sizes.rtwGenSfcn)
#endif

#ifndef rtmSetRTWGeneratedSFcn
# define rtmSetRTWGeneratedSFcn(rtm, val) ((rtm)->Sizes.rtwGenSfcn = (val))
#endif

#ifndef rtmGetRTWLogInfo
# define rtmGetRTWLogInfo(rtm)         ()
#endif

#ifndef rtmSetRTWLogInfo
# define rtmSetRTWLogInfo(rtm, val)    ()
#endif

#ifndef rtmGetRTWRTModelMethodsInfo
# define rtmGetRTWRTModelMethodsInfo(rtm) ()
#endif

#ifndef rtmSetRTWRTModelMethodsInfo
# define rtmSetRTWRTModelMethodsInfo(rtm, val) ()
#endif

#ifndef rtmGetRTWSfcnInfo
# define rtmGetRTWSfcnInfo(rtm)        ((rtm)->sfcnInfo)
#endif

#ifndef rtmSetRTWSfcnInfo
# define rtmSetRTWSfcnInfo(rtm, val)   ((rtm)->sfcnInfo = (val))
#endif

#ifndef rtmGetRTWSolverInfo
# define rtmGetRTWSolverInfo(rtm)      ((rtm)->solverInfo)
#endif

#ifndef rtmSetRTWSolverInfo
# define rtmSetRTWSolverInfo(rtm, val) ((rtm)->solverInfo = (val))
#endif

#ifndef rtmGetRTWSolverInfoPtr
# define rtmGetRTWSolverInfoPtr(rtm)   ((rtm)->solverInfoPtr)
#endif

#ifndef rtmSetRTWSolverInfoPtr
# define rtmSetRTWSolverInfoPtr(rtm, val) ((rtm)->solverInfoPtr = (val))
#endif

#ifndef rtmGetReservedForXPC
# define rtmGetReservedForXPC(rtm)     ((rtm)->SpecialInfo.xpcData)
#endif

#ifndef rtmSetReservedForXPC
# define rtmSetReservedForXPC(rtm, val) ((rtm)->SpecialInfo.xpcData = (val))
#endif

#ifndef rtmGetRootDWork
# define rtmGetRootDWork(rtm)          ((rtm)->dwork)
#endif

#ifndef rtmSetRootDWork
# define rtmSetRootDWork(rtm, val)     ((rtm)->dwork = (val))
#endif

#ifndef rtmGetSFunctions
# define rtmGetSFunctions(rtm)         ((rtm)->childSfunctions)
#endif

#ifndef rtmSetSFunctions
# define rtmSetSFunctions(rtm, val)    ((rtm)->childSfunctions = (val))
#endif

#ifndef rtmGetSampleHitArray
# define rtmGetSampleHitArray(rtm)     ((rtm)->Timing.sampleHitArray)
#endif

#ifndef rtmSetSampleHitArray
# define rtmSetSampleHitArray(rtm, val) ((rtm)->Timing.sampleHitArray = (val))
#endif

#ifndef rtmGetSampleHitPtr
# define rtmGetSampleHitPtr(rtm)       ((rtm)->Timing.sampleHits)
#endif

#ifndef rtmSetSampleHitPtr
# define rtmSetSampleHitPtr(rtm, val)  ((rtm)->Timing.sampleHits = (val))
#endif

#ifndef rtmGetSampleTimeArray
# define rtmGetSampleTimeArray(rtm)    ((rtm)->Timing.sampleTimesArray)
#endif

#ifndef rtmSetSampleTimeArray
# define rtmSetSampleTimeArray(rtm, val) ((rtm)->Timing.sampleTimesArray = (val))
#endif

#ifndef rtmGetSampleTimePtr
# define rtmGetSampleTimePtr(rtm)      ((rtm)->Timing.sampleTimes)
#endif

#ifndef rtmSetSampleTimePtr
# define rtmSetSampleTimePtr(rtm, val) ((rtm)->Timing.sampleTimes = (val))
#endif

#ifndef rtmGetSampleTimeTaskIDArray
# define rtmGetSampleTimeTaskIDArray(rtm) ((rtm)->Timing.sampleTimeTaskIDArray)
#endif

#ifndef rtmSetSampleTimeTaskIDArray
# define rtmSetSampleTimeTaskIDArray(rtm, val) ((rtm)->Timing.sampleTimeTaskIDArray = (val))
#endif

#ifndef rtmGetSampleTimeTaskIDPtr
# define rtmGetSampleTimeTaskIDPtr(rtm) ((rtm)->Timing.sampleTimeTaskIDPtr)
#endif

#ifndef rtmSetSampleTimeTaskIDPtr
# define rtmSetSampleTimeTaskIDPtr(rtm, val) ((rtm)->Timing.sampleTimeTaskIDPtr = (val))
#endif

#ifndef rtmGetSelf
# define rtmGetSelf(rtm)               ()
#endif

#ifndef rtmSetSelf
# define rtmSetSelf(rtm, val)          ()
#endif

#ifndef rtmGetSimMode
# define rtmGetSimMode(rtm)            ((rtm)->simMode)
#endif

#ifndef rtmSetSimMode
# define rtmSetSimMode(rtm, val)       ((rtm)->simMode = (val))
#endif

#ifndef rtmGetSimTimeStep
# define rtmGetSimTimeStep(rtm)        ((rtm)->Timing.simTimeStep)
#endif

#ifndef rtmSetSimTimeStep
# define rtmSetSimTimeStep(rtm, val)   ((rtm)->Timing.simTimeStep = (val))
#endif

#ifndef rtmGetStartTime
# define rtmGetStartTime(rtm)          ((rtm)->Timing.tStart)
#endif

#ifndef rtmSetStartTime
# define rtmSetStartTime(rtm, val)     ((rtm)->Timing.tStart = (val))
#endif

#ifndef rtmGetStepSize
# define rtmGetStepSize(rtm)           ((rtm)->Timing.stepSize)
#endif

#ifndef rtmSetStepSize
# define rtmSetStepSize(rtm, val)      ((rtm)->Timing.stepSize = (val))
#endif

#ifndef rtmGetStopRequestedFlag
# define rtmGetStopRequestedFlag(rtm)  ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequestedFlag
# define rtmSetStopRequestedFlag(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetTaskCounters
# define rtmGetTaskCounters(rtm)       ()
#endif

#ifndef rtmSetTaskCounters
# define rtmSetTaskCounters(rtm, val)  ()
#endif

#ifndef rtmGetTaskTimeArray
# define rtmGetTaskTimeArray(rtm)      ((rtm)->Timing.tArray)
#endif

#ifndef rtmSetTaskTimeArray
# define rtmSetTaskTimeArray(rtm, val) ((rtm)->Timing.tArray = (val))
#endif

#ifndef rtmGetTimePtr
# define rtmGetTimePtr(rtm)            ((rtm)->Timing.t)
#endif

#ifndef rtmSetTimePtr
# define rtmSetTimePtr(rtm, val)       ((rtm)->Timing.t = (val))
#endif

#ifndef rtmGetTimingData
# define rtmGetTimingData(rtm)         ((rtm)->Timing.timingData)
#endif

#ifndef rtmSetTimingData
# define rtmSetTimingData(rtm, val)    ((rtm)->Timing.timingData = (val))
#endif

#ifndef rtmGetU
# define rtmGetU(rtm)                  ((rtm)->inputs)
#endif

#ifndef rtmSetU
# define rtmSetU(rtm, val)             ((rtm)->inputs = (val))
#endif

#ifndef rtmGetVarNextHitTimesListPtr
# define rtmGetVarNextHitTimesListPtr(rtm) ((rtm)->Timing.varNextHitTimesList)
#endif

#ifndef rtmSetVarNextHitTimesListPtr
# define rtmSetVarNextHitTimesListPtr(rtm, val) ((rtm)->Timing.varNextHitTimesList = (val))
#endif

#ifndef rtmGetY
# define rtmGetY(rtm)                  ((rtm)->outputs)
#endif

#ifndef rtmSetY
# define rtmSetY(rtm, val)             ((rtm)->outputs = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
# define rtmGetZCCacheNeedsReset(rtm)  ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
# define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetZCSignalValues
# define rtmGetZCSignalValues(rtm)     ((rtm)->zcSignalValues)
#endif

#ifndef rtmSetZCSignalValues
# define rtmSetZCSignalValues(rtm, val) ((rtm)->zcSignalValues = (val))
#endif

#ifndef rtmGet_TimeOfLastOutput
# define rtmGet_TimeOfLastOutput(rtm)  ((rtm)->Timing.timeOfLastOutput)
#endif

#ifndef rtmSet_TimeOfLastOutput
# define rtmSet_TimeOfLastOutput(rtm, val) ((rtm)->Timing.timeOfLastOutput = (val))
#endif

#ifndef rtmGetdX
# define rtmGetdX(rtm)                 ((rtm)->derivs)
#endif

#ifndef rtmSetdX
# define rtmSetdX(rtm, val)            ((rtm)->derivs = (val))
#endif

#ifndef rtmGettimingBridge
# define rtmGettimingBridge(rtm)       ()
#endif

#ifndef rtmSettimingBridge
# define rtmSettimingBridge(rtm, val)  ()
#endif

#ifndef rtmGetChecksumVal
# define rtmGetChecksumVal(rtm, idx)   ((rtm)->Sizes.checksums[idx])
#endif

#ifndef rtmSetChecksumVal
# define rtmSetChecksumVal(rtm, idx, val) ((rtm)->Sizes.checksums[idx] = (val))
#endif

#ifndef rtmGetDWork
# define rtmGetDWork(rtm, idx)         ((rtm)->dwork[idx])
#endif

#ifndef rtmSetDWork
# define rtmSetDWork(rtm, idx, val)    ((rtm)->dwork[idx] = (val))
#endif

#ifndef rtmGetOffsetTime
# define rtmGetOffsetTime(rtm, idx)    ((rtm)->Timing.offsetTimes[idx])
#endif

#ifndef rtmSetOffsetTime
# define rtmSetOffsetTime(rtm, idx, val) ((rtm)->Timing.offsetTimes[idx] = (val))
#endif

#ifndef rtmGetSFunction
# define rtmGetSFunction(rtm, idx)     ((rtm)->childSfunctions[idx])
#endif

#ifndef rtmSetSFunction
# define rtmSetSFunction(rtm, idx, val) ((rtm)->childSfunctions[idx] = (val))
#endif

#ifndef rtmGetSampleTime
# define rtmGetSampleTime(rtm, idx)    ((rtm)->Timing.sampleTimes[idx])
#endif

#ifndef rtmSetSampleTime
# define rtmSetSampleTime(rtm, idx, val) ((rtm)->Timing.sampleTimes[idx] = (val))
#endif

#ifndef rtmGetSampleTimeTaskID
# define rtmGetSampleTimeTaskID(rtm, idx) ((rtm)->Timing.sampleTimeTaskIDPtr[idx])
#endif

#ifndef rtmSetSampleTimeTaskID
# define rtmSetSampleTimeTaskID(rtm, idx, val) ((rtm)->Timing.sampleTimeTaskIDPtr[idx] = (val))
#endif

#ifndef rtmGetVarNextHitTimeList
# define rtmGetVarNextHitTimeList(rtm, idx) ((rtm)->Timing.varNextHitTimesList[idx])
#endif

#ifndef rtmSetVarNextHitTimeList
# define rtmSetVarNextHitTimeList(rtm, idx, val) ((rtm)->Timing.varNextHitTimesList[idx] = (val))
#endif

#ifndef rtmIsContinuousTask
# define rtmIsContinuousTask(rtm, tid) 0
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmIsSampleHit
# define rtmIsSampleHit(rtm, sti, tid) ((rtm)->Timing.sampleHits[(rtm)->Timing.sampleTimeTaskIDPtr[sti]])
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmSetT
# define rtmSetT(rtm, val)                                       /* Do Nothing */
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

#ifndef rtmSetTFinal
# define rtmSetTFinal(rtm, val)        ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

#ifndef rtmSetTPtr
# define rtmSetTPtr(rtm, val)          ((rtm)->Timing.t = (val))
#endif

#ifndef rtmGetTStart
# define rtmGetTStart(rtm)             ((rtm)->Timing.tStart)
#endif

#ifndef rtmSetTStart
# define rtmSetTStart(rtm, val)        ((rtm)->Timing.tStart = (val))
#endif

#ifndef rtmGetTaskTime
# define rtmGetTaskTime(rtm, sti)      (rtmGetTPtr((rtm))[(rtm)->Timing.sampleTimeTaskIDPtr[sti]])
#endif

#ifndef rtmSetTaskTime
# define rtmSetTaskTime(rtm, sti, val) (rtmGetTPtr((rtm))[sti] = (val))
#endif

#ifndef rtmGetTimeOfLastOutput
# define rtmGetTimeOfLastOutput(rtm)   ((rtm)->Timing.timeOfLastOutput)
#endif

#ifdef rtmGetRTWSolverInfo
#undef rtmGetRTWSolverInfo
#endif

#define rtmGetRTWSolverInfo(rtm)       &((rtm)->solverInfo)

/* Definition for use in the target main file */
#define DATA_COLLECTION_rtModel        RT_MODEL_DATA_COLLECTION_T

/* Block signals (default storage) */
typedef struct {
  real_T TSamp;                        /* '<S20>/TSamp' */
  real_T TSamp_d;                      /* '<S17>/TSamp' */
  real_T VectorConcatenate1[2];        /* '<Root>/Vector Concatenate1' */
  real_T Sum2[2];                      /* '<Root>/Sum2' */
  real_T TSamp_i[2];                   /* '<S1>/TSamp' */
  real_T FromWorkspace3[2];            /* '<Root>/From Workspace3' */
  real_T FromWorkspace1[2];            /* '<Root>/From Workspace1' */
  real_T Torquetocurrent;              /* '<S7>/Torque to current ' */
  real_T TSamp_f;                      /* '<S19>/TSamp' */
  real_T Current;                      /* '<S7>/HIL Read Analog' */
  real_T Sum1;                         /* '<S7>/Sum1' */
  real_T TSamp_p;                      /* '<S18>/TSamp' */
  real_T Saturation;                   /* '<S7>/Saturation' */
  real_T VectorConcatenate[4];         /* '<S7>/Vector Concatenate' */
  real_T TSamp_g;                      /* '<S24>/TSamp' */
  real_T TSamp_b;                      /* '<S21>/TSamp' */
  real_T Torquetocurrent_k;            /* '<S8>/Torque to current ' */
  real_T TSamp_j;                      /* '<S23>/TSamp' */
  real_T Current_b;                    /* '<S8>/HIL Read Analog' */
  real_T Sum1_d;                       /* '<S8>/Sum1' */
  real_T TSamp_bl;                     /* '<S22>/TSamp' */
  real_T Saturation_m;                 /* '<S8>/Saturation' */
  real_T VectorConcatenate_d[4];       /* '<S8>/Vector Concatenate' */
  real_T UnitDelay2[2];                /* '<Root>/Unit Delay2' */
  real_T HILReadDigital_o1;            /* '<S2>/HIL Read Digital' */
  real_T HILReadDigital_o2;            /* '<S2>/HIL Read Digital' */
  real_T HILReadDigital_o3;            /* '<S2>/HIL Read Digital' */
  boolean_T LogicalOperator4;          /* '<S3>/Logical Operator4' */
  boolean_T LogicalOperator5;          /* '<S3>/Logical Operator5' */
  boolean_T LogicalOperator6;          /* '<S3>/Logical Operator6' */
  boolean_T LogicalOperator7;          /* '<S3>/Logical Operator7' */
} B_DATA_COLLECTION_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T UD_DSTATE;                    /* '<S20>/UD' */
  real_T UD_DSTATE_g;                  /* '<S17>/UD' */
  real_T UnitDelay_DSTATE[2];          /* '<Root>/Unit Delay' */
  real_T DiscreteTimeIntegrator_DSTATE[2];/* '<Root>/Discrete-Time Integrator' */
  real_T UD_DSTATE_e[2];               /* '<S1>/UD' */
  real_T UnitDelay1_DSTATE[2];         /* '<Root>/Unit Delay1' */
  real_T UD_DSTATE_g1;                 /* '<S19>/UD' */
  real_T DiscreteTimeIntegrator_DSTATE_p;/* '<S7>/Discrete-Time Integrator' */
  real_T UD_DSTATE_j;                  /* '<S18>/UD' */
  real_T UD_DSTATE_h;                  /* '<S24>/UD' */
  real_T UD_DSTATE_i;                  /* '<S21>/UD' */
  real_T UD_DSTATE_er;                 /* '<S23>/UD' */
  real_T DiscreteTimeIntegrator_DSTATE_a;/* '<S8>/Discrete-Time Integrator' */
  real_T UD_DSTATE_d;                  /* '<S22>/UD' */
  real_T UnitDelay2_DSTATE[2];         /* '<Root>/Unit Delay2' */
  real_T HILReadAnalog_Buffer;         /* '<S7>/HIL Read Analog' */
  real_T HILReadAnalog_Buffer_n;       /* '<S8>/HIL Read Analog' */
  real_T HILInitialize_AIMinimums[8];  /* '<Root>/HIL Initialize' */
  real_T HILInitialize_AIMaximums[8];  /* '<Root>/HIL Initialize' */
  real_T HILInitialize_AOMinimums[8];  /* '<Root>/HIL Initialize' */
  real_T HILInitialize_AOMaximums[8];  /* '<Root>/HIL Initialize' */
  real_T HILInitialize_AOVoltages[8];  /* '<Root>/HIL Initialize' */
  real_T HILInitialize_FilterFrequency[8];/* '<Root>/HIL Initialize' */
  t_card HILInitialize_Card;           /* '<Root>/HIL Initialize' */
  t_task HILWriteDigitalTimebase_Task; /* '<Root>/HIL Write Digital Timebase' */
  void *HILReadEncoder_PWORK;          /* '<S7>/HIL Read Encoder' */
  void *HILReadEncoder_PWORK_g;        /* '<Root>/HIL Read Encoder' */
  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } FromWorkspace3_PWORK;              /* '<Root>/From Workspace3' */

  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } FromWorkspace2_PWORK;              /* '<Root>/From Workspace2' */

  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } FromWorkspace1_PWORK;              /* '<Root>/From Workspace1' */

  void *HILReadAnalog_PWORK;           /* '<S7>/HIL Read Analog' */
  void *HILWriteAnalog_PWORK;          /* '<S7>/HIL Write Analog' */
  struct {
    void *LoggedData[2];
  } Ielbow_PWORK;                      /* '<S7>/I elbow' */

  struct {
    void *LoggedData;
  } ToWorkspace_PWORK;                 /* '<S7>/To Workspace' */

  struct {
    void *LoggedData;
  } Velbow_PWORK;                      /* '<S7>/V elbow' */

  void *HILReadEncoder_PWORK_k;        /* '<S8>/HIL Read Encoder' */
  void *HILReadAnalog_PWORK_a;         /* '<S8>/HIL Read Analog' */
  void *HILWriteAnalog_PWORK_g;        /* '<S8>/HIL Write Analog' */
  struct {
    void *LoggedData[2];
  } Ishoulder1_PWORK;                  /* '<S8>/I shoulder1' */

  struct {
    void *LoggedData;
  } ToWorkspace_PWORK_l;               /* '<S8>/To Workspace' */

  struct {
    void *LoggedData;
  } Vshoulder_PWORK;                   /* '<S8>/V shoulder' */

  struct {
    void *LoggedData[2];
  } theta1_PWORK;                      /* '<Root>/theta1' */

  struct {
    void *LoggedData[2];
  } theta2_PWORK;                      /* '<Root>/theta2' */

  void *HILWriteDigital_PWORK;         /* '<S2>/HIL Write Digital' */
  void *HILReadDigital_PWORK;          /* '<S2>/HIL Read Digital' */
  void *HILReadDigital_PWORK_h;        /* '<S3>/HIL Read Digital' */
  int32_T HILReadEncoder_Buffer[2];    /* '<S7>/HIL Read Encoder' */
  int32_T HILReadEncoder_Buffer_a[2];  /* '<Root>/HIL Read Encoder' */
  int32_T HILReadEncoder_Buffer_d[2];  /* '<S8>/HIL Read Encoder' */
  int32_T clockTickCounter;            /* '<Root>/Pulse Generator' */
  int32_T HILInitialize_DOStates[9];   /* '<Root>/HIL Initialize' */
  int32_T HILInitialize_QuadratureModes[8];/* '<Root>/HIL Initialize' */
  int32_T HILInitialize_InitialEICounts[8];/* '<Root>/HIL Initialize' */
  struct {
    int_T PrevIndex;
  } FromWorkspace3_IWORK;              /* '<Root>/From Workspace3' */

  struct {
    int_T PrevIndex;
  } FromWorkspace2_IWORK;              /* '<Root>/From Workspace2' */

  struct {
    int_T PrevIndex;
  } FromWorkspace1_IWORK;              /* '<Root>/From Workspace1' */

  boolean_T HILInitialize_DOBits[9];   /* '<Root>/HIL Initialize' */
  boolean_T HILWriteDigitalTimebase_Started;/* '<Root>/HIL Write Digital Timebase' */
  t_boolean HILWriteDigitalTimebase_Buffer;/* '<Root>/HIL Write Digital Timebase' */
  t_boolean HILWriteDigital_Buffer[3]; /* '<S2>/HIL Write Digital' */
  t_boolean HILReadDigital_Buffer[3];  /* '<S2>/HIL Read Digital' */
  t_boolean HILReadDigital_Buffer_g[4];/* '<S3>/HIL Read Digital' */
} DW_DATA_COLLECTION_T;

/* Backward compatible GRT Identifiers */
#define rtB                            DATA_COLLECTION_B
#define BlockIO                        B_DATA_COLLECTION_T
#define rtP                            DATA_COLLECTION_P
#define Parameters                     P_DATA_COLLECTION_T
#define rtDWork                        DATA_COLLECTION_DW
#define D_Work                         DW_DATA_COLLECTION_T

/* Parameters (default storage) */
struct P_DATA_COLLECTION_T_ {
  real_T KE_D1;                        /* Variable: KE_D1
                                        * Referenced by:
                                        *   '<Root>/Motor #1 Encoder Calib1'
                                        *   '<S7>/Motor #1 Encoder Calib1'
                                        *   '<S8>/Motor #1 Encoder Calib1'
                                        */
  real_T KE_D2;                        /* Variable: KE_D2
                                        * Referenced by:
                                        *   '<Root>/Motor #2 Encoder Calib1'
                                        *   '<S7>/Motor #2 Encoder Calib1'
                                        *   '<S8>/Motor #2 Encoder Calib1'
                                        */
  real_T Kt1;                          /* Variable: Kt1
                                        * Referenced by: '<S8>/Torque to current '
                                        */
  real_T Kt2;                          /* Variable: Kt2
                                        * Referenced by: '<S7>/Torque to current '
                                        */
  real_T L1;                           /* Variable: L1
                                        * Referenced by:
                                        *   '<S7>/Motor #1 Encoder Calib2'
                                        *   '<S8>/Motor #1 Encoder Calib2'
                                        */
  real_T L2;                           /* Variable: L2
                                        * Referenced by:
                                        *   '<S7>/Motor #1 Encoder Calib5'
                                        *   '<S8>/Motor #1 Encoder Calib5'
                                        */
  real_T LIMIT_SWITCHES_ENABLE;        /* Variable: LIMIT_SWITCHES_ENABLE
                                        * Referenced by: '<S3>/Constant'
                                        */
  real_T R1;                           /* Variable: R1
                                        * Referenced by:
                                        *   '<S7>/Motor #1 Encoder Calib6'
                                        *   '<S8>/Motor #1 Encoder Calib6'
                                        *   '<S8>/Saturation'
                                        */
  real_T R2;                           /* Variable: R2
                                        * Referenced by:
                                        *   '<S7>/Motor #1 Encoder Calib7'
                                        *   '<S7>/Saturation'
                                        *   '<S8>/Motor #1 Encoder Calib7'
                                        */
  real_T a1_hat;                       /* Variable: a1_hat
                                        * Referenced by: '<Root>/Constant'
                                        */
  real_T a2_hat;                       /* Variable: a2_hat
                                        * Referenced by: '<Root>/Constant1'
                                        */
  real_T b1_hat;                       /* Variable: b1_hat
                                        * Referenced by: '<Root>/Constant5'
                                        */
  real_T b2_hat;                       /* Variable: b2_hat
                                        * Referenced by: '<Root>/Constant4'
                                        */
  real_T b_hat;                        /* Variable: b_hat
                                        * Referenced by:
                                        *   '<Root>/Constant2'
                                        *   '<Root>/Constant3'
                                        */
  real_T fc1_hat;                      /* Variable: fc1_hat
                                        * Referenced by: '<Root>/Constant7'
                                        */
  real_T fc2_hat;                      /* Variable: fc2_hat
                                        * Referenced by: '<Root>/Constant8'
                                        */
  real_T i_sat1;                       /* Variable: i_sat1
                                        * Referenced by: '<S8>/Saturation'
                                        */
  real_T i_sat2;                       /* Variable: i_sat2
                                        * Referenced by: '<S7>/Saturation'
                                        */
  real_T ke1;                          /* Variable: ke1
                                        * Referenced by:
                                        *   '<S7>/Motor #1 Encoder Calib3'
                                        *   '<S8>/Motor #1 Encoder Calib3'
                                        */
  real_T ke2;                          /* Variable: ke2
                                        * Referenced by:
                                        *   '<S7>/Motor #1 Encoder Calib8'
                                        *   '<S8>/Motor #1 Encoder Calib8'
                                        */
  real_T ki1;                          /* Variable: ki1
                                        * Referenced by:
                                        *   '<S7>/Gain1'
                                        *   '<S8>/Gain1'
                                        */
  real_T ki_traj[4];                   /* Variable: ki_traj
                                        * Referenced by: '<Root>/Gain1'
                                        */
  real_T kp1;                          /* Variable: kp1
                                        * Referenced by: '<S8>/Gain'
                                        */
  real_T kp2;                          /* Variable: kp2
                                        * Referenced by: '<S7>/Gain'
                                        */
  real_T v_eps_hat;                    /* Variable: v_eps_hat
                                        * Referenced by: '<Root>/Constant6'
                                        */
  real_T DiscreteDerivative3_ICPrevScale;/* Mask Parameter: DiscreteDerivative3_ICPrevScale
                                          * Referenced by: '<S20>/UD'
                                          */
  real_T DiscreteDerivative_ICPrevScaled;/* Mask Parameter: DiscreteDerivative_ICPrevScaled
                                          * Referenced by: '<S17>/UD'
                                          */
  real_T DiscreteDerivative_ICPrevScal_k;/* Mask Parameter: DiscreteDerivative_ICPrevScal_k
                                          * Referenced by: '<S1>/UD'
                                          */
  real_T DiscreteDerivative2_ICPrevScale;/* Mask Parameter: DiscreteDerivative2_ICPrevScale
                                          * Referenced by: '<S19>/UD'
                                          */
  real_T DiscreteDerivative1_ICPrevScale;/* Mask Parameter: DiscreteDerivative1_ICPrevScale
                                          * Referenced by: '<S18>/UD'
                                          */
  real_T DiscreteDerivative3_ICPrevSca_i;/* Mask Parameter: DiscreteDerivative3_ICPrevSca_i
                                          * Referenced by: '<S24>/UD'
                                          */
  real_T DiscreteDerivative_ICPrevScal_l;/* Mask Parameter: DiscreteDerivative_ICPrevScal_l
                                          * Referenced by: '<S21>/UD'
                                          */
  real_T DiscreteDerivative2_ICPrevSca_n;/* Mask Parameter: DiscreteDerivative2_ICPrevSca_n
                                          * Referenced by: '<S23>/UD'
                                          */
  real_T DiscreteDerivative1_ICPrevSca_c;/* Mask Parameter: DiscreteDerivative1_ICPrevSca_c
                                          * Referenced by: '<S22>/UD'
                                          */
  int32_T HILWriteDigitalTimebase_clock;/* Mask Parameter: HILWriteDigitalTimebase_clock
                                         * Referenced by: '<Root>/HIL Write Digital Timebase'
                                         */
  uint32_T HILReadEncoder_channels[2]; /* Mask Parameter: HILReadEncoder_channels
                                        * Referenced by: '<S7>/HIL Read Encoder'
                                        */
  uint32_T HILReadEncoder_channels_d[2];/* Mask Parameter: HILReadEncoder_channels_d
                                         * Referenced by: '<Root>/HIL Read Encoder'
                                         */
  uint32_T HILReadAnalog_channels;     /* Mask Parameter: HILReadAnalog_channels
                                        * Referenced by: '<S7>/HIL Read Analog'
                                        */
  uint32_T HILWriteAnalog_channels;    /* Mask Parameter: HILWriteAnalog_channels
                                        * Referenced by: '<S7>/HIL Write Analog'
                                        */
  uint32_T HILReadEncoder_channels_g[2];/* Mask Parameter: HILReadEncoder_channels_g
                                         * Referenced by: '<S8>/HIL Read Encoder'
                                         */
  uint32_T HILReadAnalog_channels_e;   /* Mask Parameter: HILReadAnalog_channels_e
                                        * Referenced by: '<S8>/HIL Read Analog'
                                        */
  uint32_T HILWriteAnalog_channels_h;  /* Mask Parameter: HILWriteAnalog_channels_h
                                        * Referenced by: '<S8>/HIL Write Analog'
                                        */
  uint32_T HILWriteDigitalTimebase_channel;/* Mask Parameter: HILWriteDigitalTimebase_channel
                                            * Referenced by: '<Root>/HIL Write Digital Timebase'
                                            */
  uint32_T HILWriteDigital_channels[3];/* Mask Parameter: HILWriteDigital_channels
                                        * Referenced by: '<S2>/HIL Write Digital'
                                        */
  uint32_T HILReadDigital_channels[3]; /* Mask Parameter: HILReadDigital_channels
                                        * Referenced by: '<S2>/HIL Read Digital'
                                        */
  uint32_T HILReadDigital_channels_j[4];/* Mask Parameter: HILReadDigital_channels_j
                                         * Referenced by: '<S3>/HIL Read Digital'
                                         */
  uint32_T HILWriteDigitalTimebase_samples;/* Mask Parameter: HILWriteDigitalTimebase_samples
                                            * Referenced by: '<Root>/HIL Write Digital Timebase'
                                            */
  int8_T StopwithMessage_message_icon; /* Mask Parameter: StopwithMessage_message_icon
                                        * Referenced by: '<S9>/Show Message on Host'
                                        */
  int8_T StopwithMessage1_message_icon;/* Mask Parameter: StopwithMessage1_message_icon
                                        * Referenced by: '<S10>/Show Message on Host'
                                        */
  int8_T StopwithMessage2_message_icon;/* Mask Parameter: StopwithMessage2_message_icon
                                        * Referenced by: '<S11>/Show Message on Host'
                                        */
  int8_T StopwithMessage3_message_icon;/* Mask Parameter: StopwithMessage3_message_icon
                                        * Referenced by: '<S12>/Show Message on Host'
                                        */
  real_T Constant10_Value;             /* Expression: 0
                                        * Referenced by: '<Root>/Constant10'
                                        */
  real_T Constant9_Value;              /* Expression: 0
                                        * Referenced by: '<Root>/Constant9'
                                        */
  real_T TSamp_WtEt;                   /* Computed Parameter: TSamp_WtEt
                                        * Referenced by: '<S20>/TSamp'
                                        */
  real_T TSamp_WtEt_p;                 /* Computed Parameter: TSamp_WtEt_p
                                        * Referenced by: '<S17>/TSamp'
                                        */
  real_T UnitDelay_InitialCondition;   /* Expression: 0
                                        * Referenced by: '<Root>/Unit Delay'
                                        */
  real_T Gain_Gain[2];                 /* Expression: [4; 2]
                                        * Referenced by: '<Root>/Gain'
                                        */
  real_T DiscreteTimeIntegrator_gainval;/* Computed Parameter: DiscreteTimeIntegrator_gainval
                                         * Referenced by: '<Root>/Discrete-Time Integrator'
                                         */
  real_T DiscreteTimeIntegrator_IC;    /* Expression: 0
                                        * Referenced by: '<Root>/Discrete-Time Integrator'
                                        */
  real_T TSamp_WtEt_e;                 /* Computed Parameter: TSamp_WtEt_e
                                        * Referenced by: '<S1>/TSamp'
                                        */
  real_T UnitDelay1_InitialCondition;  /* Expression: 0
                                        * Referenced by: '<Root>/Unit Delay1'
                                        */
  real_T Gain2_Gain[2];                /* Expression: [0.3; 0.02]
                                        * Referenced by: '<Root>/Gain2'
                                        */
  real_T TSamp_WtEt_ei;                /* Computed Parameter: TSamp_WtEt_ei
                                        * Referenced by: '<S19>/TSamp'
                                        */
  real_T DiscreteTimeIntegrator_gainva_p;/* Computed Parameter: DiscreteTimeIntegrator_gainva_p
                                          * Referenced by: '<S7>/Discrete-Time Integrator'
                                          */
  real_T DiscreteTimeIntegrator_IC_i;  /* Expression: 0
                                        * Referenced by: '<S7>/Discrete-Time Integrator'
                                        */
  real_T TSamp_WtEt_a;                 /* Computed Parameter: TSamp_WtEt_a
                                        * Referenced by: '<S18>/TSamp'
                                        */
  real_T Gain2_Gain_c;                 /* Expression: 0
                                        * Referenced by: '<S7>/Gain2'
                                        */
  real_T TSamp_WtEt_h;                 /* Computed Parameter: TSamp_WtEt_h
                                        * Referenced by: '<S24>/TSamp'
                                        */
  real_T TSamp_WtEt_l;                 /* Computed Parameter: TSamp_WtEt_l
                                        * Referenced by: '<S21>/TSamp'
                                        */
  real_T TSamp_WtEt_g;                 /* Computed Parameter: TSamp_WtEt_g
                                        * Referenced by: '<S23>/TSamp'
                                        */
  real_T DiscreteTimeIntegrator_gainva_k;/* Computed Parameter: DiscreteTimeIntegrator_gainva_k
                                          * Referenced by: '<S8>/Discrete-Time Integrator'
                                          */
  real_T DiscreteTimeIntegrator_IC_l;  /* Expression: 0
                                        * Referenced by: '<S8>/Discrete-Time Integrator'
                                        */
  real_T TSamp_WtEt_pz;                /* Computed Parameter: TSamp_WtEt_pz
                                        * Referenced by: '<S22>/TSamp'
                                        */
  real_T Gain2_Gain_l;                 /* Expression: 0
                                        * Referenced by: '<S8>/Gain2'
                                        */
  real_T UnitDelay2_InitialCondition;  /* Expression: 0
                                        * Referenced by: '<Root>/Unit Delay2'
                                        */
  real_T PulseGenerator_Amp;           /* Expression: 1
                                        * Referenced by: '<Root>/Pulse Generator'
                                        */
  real_T PulseGenerator_Period;        /* Computed Parameter: PulseGenerator_Period
                                        * Referenced by: '<Root>/Pulse Generator'
                                        */
  real_T PulseGenerator_Duty;          /* Computed Parameter: PulseGenerator_Duty
                                        * Referenced by: '<Root>/Pulse Generator'
                                        */
  real_T PulseGenerator_PhaseDelay;    /* Expression: 0
                                        * Referenced by: '<Root>/Pulse Generator'
                                        */
  real_T HILInitialize_OOTerminate;    /* Expression: set_other_outputs_at_terminate
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  real_T HILInitialize_OOExit;         /* Expression: set_other_outputs_at_switch_out
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  real_T HILInitialize_OOStart;        /* Expression: set_other_outputs_at_start
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  real_T HILInitialize_OOEnter;        /* Expression: set_other_outputs_at_switch_in
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  real_T HILInitialize_AOFinal;        /* Expression: final_analog_outputs
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  real_T HILInitialize_POFinal;        /* Expression: final_pwm_outputs
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  real_T HILInitialize_AIHigh;         /* Expression: analog_input_maximums
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  real_T HILInitialize_AILow;          /* Expression: analog_input_minimums
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  real_T HILInitialize_AOHigh;         /* Expression: analog_output_maximums
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  real_T HILInitialize_AOLow;          /* Expression: analog_output_minimums
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  real_T HILInitialize_AOInitial;      /* Expression: initial_analog_outputs
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  real_T HILInitialize_AOWatchdog;     /* Expression: watchdog_analog_outputs
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  real_T HILInitialize_EIFrequency;    /* Expression: encoder_filter_frequency
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  real_T HILInitialize_POFrequency;    /* Expression: pwm_frequency
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  real_T HILInitialize_POInitial;      /* Expression: initial_pwm_outputs
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  real_T EnableActiveLow_Value[2];     /* Expression: [ 0 0 ]
                                        * Referenced by: '<S2>/Enable: Active Low'
                                        */
  real_T MasterEnableActiveHigh_Value; /* Expression: 1
                                        * Referenced by: '<S2>/Master Enable: Active High'
                                        */
  int32_T HILInitialize_CKChannels[2]; /* Computed Parameter: HILInitialize_CKChannels
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  int32_T HILInitialize_CKModes[2];    /* Computed Parameter: HILInitialize_CKModes
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  int32_T HILInitialize_DOWatchdog;    /* Computed Parameter: HILInitialize_DOWatchdog
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  int32_T HILInitialize_EIInitial;     /* Computed Parameter: HILInitialize_EIInitial
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  int32_T HILInitialize_POModes;       /* Computed Parameter: HILInitialize_POModes
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  uint32_T HILInitialize_AIChannels[8];/* Computed Parameter: HILInitialize_AIChannels
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  uint32_T HILInitialize_AOChannels[8];/* Computed Parameter: HILInitialize_AOChannels
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  uint32_T HILInitialize_DIChannels[8];/* Computed Parameter: HILInitialize_DIChannels
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  uint32_T HILInitialize_DOChannels[9];/* Computed Parameter: HILInitialize_DOChannels
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  uint32_T HILInitialize_EIChannels[8];/* Computed Parameter: HILInitialize_EIChannels
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  uint32_T HILInitialize_EIQuadrature; /* Computed Parameter: HILInitialize_EIQuadrature
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILReadEncoder_Active;     /* Computed Parameter: HILReadEncoder_Active
                                        * Referenced by: '<S7>/HIL Read Encoder'
                                        */
  boolean_T HILReadEncoder_Active_a;   /* Computed Parameter: HILReadEncoder_Active_a
                                        * Referenced by: '<Root>/HIL Read Encoder'
                                        */
  boolean_T HILReadAnalog_Active;      /* Computed Parameter: HILReadAnalog_Active
                                        * Referenced by: '<S7>/HIL Read Analog'
                                        */
  boolean_T HILWriteAnalog_Active;     /* Computed Parameter: HILWriteAnalog_Active
                                        * Referenced by: '<S7>/HIL Write Analog'
                                        */
  boolean_T HILReadEncoder_Active_j;   /* Computed Parameter: HILReadEncoder_Active_j
                                        * Referenced by: '<S8>/HIL Read Encoder'
                                        */
  boolean_T HILReadAnalog_Active_l;    /* Computed Parameter: HILReadAnalog_Active_l
                                        * Referenced by: '<S8>/HIL Read Analog'
                                        */
  boolean_T HILWriteAnalog_Active_l;   /* Computed Parameter: HILWriteAnalog_Active_l
                                        * Referenced by: '<S8>/HIL Write Analog'
                                        */
  boolean_T HILInitialize_Active;      /* Computed Parameter: HILInitialize_Active
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_AOTerminate; /* Computed Parameter: HILInitialize_AOTerminate
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_AOExit;      /* Computed Parameter: HILInitialize_AOExit
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_DOTerminate; /* Computed Parameter: HILInitialize_DOTerminate
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_DOExit;      /* Computed Parameter: HILInitialize_DOExit
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_POTerminate; /* Computed Parameter: HILInitialize_POTerminate
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_POExit;      /* Computed Parameter: HILInitialize_POExit
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_CKPStart;    /* Computed Parameter: HILInitialize_CKPStart
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_CKPEnter;    /* Computed Parameter: HILInitialize_CKPEnter
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_CKStart;     /* Computed Parameter: HILInitialize_CKStart
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_CKEnter;     /* Computed Parameter: HILInitialize_CKEnter
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_AIPStart;    /* Computed Parameter: HILInitialize_AIPStart
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_AIPEnter;    /* Computed Parameter: HILInitialize_AIPEnter
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_AOPStart;    /* Computed Parameter: HILInitialize_AOPStart
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_AOPEnter;    /* Computed Parameter: HILInitialize_AOPEnter
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_AOStart;     /* Computed Parameter: HILInitialize_AOStart
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_AOEnter;     /* Computed Parameter: HILInitialize_AOEnter
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_AOReset;     /* Computed Parameter: HILInitialize_AOReset
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_DOPStart;    /* Computed Parameter: HILInitialize_DOPStart
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_DOPEnter;    /* Computed Parameter: HILInitialize_DOPEnter
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_DOStart;     /* Computed Parameter: HILInitialize_DOStart
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_DOEnter;     /* Computed Parameter: HILInitialize_DOEnter
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_DOReset;     /* Computed Parameter: HILInitialize_DOReset
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_EIPStart;    /* Computed Parameter: HILInitialize_EIPStart
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_EIPEnter;    /* Computed Parameter: HILInitialize_EIPEnter
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_EIStart;     /* Computed Parameter: HILInitialize_EIStart
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_EIEnter;     /* Computed Parameter: HILInitialize_EIEnter
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_POPStart;    /* Computed Parameter: HILInitialize_POPStart
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_POPEnter;    /* Computed Parameter: HILInitialize_POPEnter
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_POStart;     /* Computed Parameter: HILInitialize_POStart
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_POEnter;     /* Computed Parameter: HILInitialize_POEnter
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_POReset;     /* Computed Parameter: HILInitialize_POReset
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_OOReset;     /* Computed Parameter: HILInitialize_OOReset
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_DOFinal;     /* Computed Parameter: HILInitialize_DOFinal
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILInitialize_DOInitial;   /* Computed Parameter: HILInitialize_DOInitial
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  boolean_T HILWriteDigitalTimebase_Active;/* Computed Parameter: HILWriteDigitalTimebase_Active
                                            * Referenced by: '<Root>/HIL Write Digital Timebase'
                                            */
  boolean_T HILWriteDigital_Active;    /* Computed Parameter: HILWriteDigital_Active
                                        * Referenced by: '<S2>/HIL Write Digital'
                                        */
  boolean_T HILReadDigital_Active;     /* Computed Parameter: HILReadDigital_Active
                                        * Referenced by: '<S2>/HIL Read Digital'
                                        */
  boolean_T HILReadDigital_Active_c;   /* Computed Parameter: HILReadDigital_Active_c
                                        * Referenced by: '<S3>/HIL Read Digital'
                                        */
  boolean_T Constant_Value;            /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S13>/Constant'
                                        */
  boolean_T Constant_Value_h;          /* Computed Parameter: Constant_Value_h
                                        * Referenced by: '<S14>/Constant'
                                        */
  boolean_T Constant_Value_m;          /* Computed Parameter: Constant_Value_m
                                        * Referenced by: '<S15>/Constant'
                                        */
  boolean_T Constant_Value_i;          /* Computed Parameter: Constant_Value_i
                                        * Referenced by: '<S16>/Constant'
                                        */
  uint8_T ManualSwitch3_CurrentSetting;/* Computed Parameter: ManualSwitch3_CurrentSetting
                                        * Referenced by: '<S7>/Manual Switch3'
                                        */
  uint8_T ManualSwitch1_CurrentSetting;/* Computed Parameter: ManualSwitch1_CurrentSetting
                                        * Referenced by: '<Root>/Manual Switch1'
                                        */
  uint8_T ManualSwitch2_CurrentSetting;/* Computed Parameter: ManualSwitch2_CurrentSetting
                                        * Referenced by: '<S7>/Manual Switch2'
                                        */
  uint8_T ManualSwitch1_CurrentSetting_o;/* Computed Parameter: ManualSwitch1_CurrentSetting_o
                                          * Referenced by: '<S7>/Manual Switch1'
                                          */
  uint8_T ManualSwitch4_CurrentSetting;/* Computed Parameter: ManualSwitch4_CurrentSetting
                                        * Referenced by: '<S7>/Manual Switch4'
                                        */
  uint8_T ManualSwitch3_CurrentSetting_n;/* Computed Parameter: ManualSwitch3_CurrentSetting_n
                                          * Referenced by: '<S8>/Manual Switch3'
                                          */
  uint8_T ManualSwitch2_CurrentSetting_b;/* Computed Parameter: ManualSwitch2_CurrentSetting_b
                                          * Referenced by: '<Root>/Manual Switch2'
                                          */
  uint8_T ManualSwitch2_CurrentSetting_j;/* Computed Parameter: ManualSwitch2_CurrentSetting_j
                                          * Referenced by: '<S8>/Manual Switch2'
                                          */
  uint8_T ManualSwitch1_CurrentSetting_k;/* Computed Parameter: ManualSwitch1_CurrentSetting_k
                                          * Referenced by: '<S8>/Manual Switch1'
                                          */
  uint8_T ManualSwitch4_CurrentSetting_i;/* Computed Parameter: ManualSwitch4_CurrentSetting_i
                                          * Referenced by: '<S8>/Manual Switch4'
                                          */
};

/* Real-time Model Data Structure */
struct tag_RTM_DATA_COLLECTION_T {
  const char_T *path;
  const char_T *modelName;
  struct SimStruct_tag * *childSfunctions;
  const char_T *errorStatus;
  SS_SimMode simMode;
  RTWExtModeInfo *extModeInfo;
  RTWSolverInfo solverInfo;
  RTWSolverInfo *solverInfoPtr;
  void *sfcnInfo;
  void *blockIO;
  const void *constBlockIO;
  void *defaultParam;
  ZCSigState *prevZCSigState;
  real_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  void *zcSignalValues;
  void *inputs;
  void *outputs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  void *dwork;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
    uint32_T options;
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numU;
    int_T numY;
    int_T numSampTimes;
    int_T numBlocks;
    int_T numBlockIO;
    int_T numBlockPrms;
    int_T numDwork;
    int_T numSFcnPrms;
    int_T numSFcns;
    int_T numIports;
    int_T numOports;
    int_T numNonSampZCs;
    int_T sysDirFeedThru;
    int_T rtwGenSfcn;
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
    void *xpcData;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T stepSize;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    time_T tStart;
    time_T tFinal;
    time_T timeOfLastOutput;
    void *timingData;
    real_T *varNextHitTimesList;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *sampleTimes;
    time_T *offsetTimes;
    int_T *sampleTimeTaskIDPtr;
    int_T *sampleHits;
    int_T *perTaskSampleHits;
    time_T *t;
    time_T sampleTimesArray[1];
    time_T offsetTimesArray[1];
    int_T sampleTimeTaskIDArray[1];
    int_T sampleHitArray[1];
    int_T perTaskSampleHitsArray[1];
    time_T tArray[1];
  } Timing;
};

/* Block parameters (default storage) */
extern P_DATA_COLLECTION_T DATA_COLLECTION_P;

/* Block signals (default storage) */
extern B_DATA_COLLECTION_T DATA_COLLECTION_B;

/* Block states (default storage) */
extern DW_DATA_COLLECTION_T DATA_COLLECTION_DW;

/* Model entry point functions */
extern void DATA_COLLECTION_initialize(void);
extern void DATA_COLLECTION_output(void);
extern void DATA_COLLECTION_update(void);
extern void DATA_COLLECTION_terminate(void);

/*====================*
 * External functions *
 *====================*/
extern DATA_COLLECTION_rtModel *DATA_COLLECTION(void);
extern void MdlInitializeSizes(void);
extern void MdlInitializeSampleTimes(void);
extern void MdlInitialize(void);
extern void MdlStart(void);
extern void MdlOutputs(int_T tid);
extern void MdlUpdate(int_T tid);
extern void MdlTerminate(void);

/* Real-time Model object */
extern RT_MODEL_DATA_COLLECTION_T *const DATA_COLLECTION_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'DATA_COLLECTION'
 * '<S1>'   : 'DATA_COLLECTION/Discrete Derivative'
 * '<S2>'   : 'DATA_COLLECTION/Enable AMPAQ'
 * '<S3>'   : 'DATA_COLLECTION/Limit Switches'
 * '<S4>'   : 'DATA_COLLECTION/MATLAB Function'
 * '<S5>'   : 'DATA_COLLECTION/MATLAB Function1'
 * '<S6>'   : 'DATA_COLLECTION/MATLAB Function2'
 * '<S7>'   : 'DATA_COLLECTION/Torque Control Elbow'
 * '<S8>'   : 'DATA_COLLECTION/Torque Control Shoulder'
 * '<S9>'   : 'DATA_COLLECTION/Limit Switches/Stop with Message'
 * '<S10>'  : 'DATA_COLLECTION/Limit Switches/Stop with Message1'
 * '<S11>'  : 'DATA_COLLECTION/Limit Switches/Stop with Message2'
 * '<S12>'  : 'DATA_COLLECTION/Limit Switches/Stop with Message3'
 * '<S13>'  : 'DATA_COLLECTION/Limit Switches/Stop with Message/Compare'
 * '<S14>'  : 'DATA_COLLECTION/Limit Switches/Stop with Message1/Compare'
 * '<S15>'  : 'DATA_COLLECTION/Limit Switches/Stop with Message2/Compare'
 * '<S16>'  : 'DATA_COLLECTION/Limit Switches/Stop with Message3/Compare'
 * '<S17>'  : 'DATA_COLLECTION/Torque Control Elbow/Discrete Derivative'
 * '<S18>'  : 'DATA_COLLECTION/Torque Control Elbow/Discrete Derivative1'
 * '<S19>'  : 'DATA_COLLECTION/Torque Control Elbow/Discrete Derivative2'
 * '<S20>'  : 'DATA_COLLECTION/Torque Control Elbow/Discrete Derivative3'
 * '<S21>'  : 'DATA_COLLECTION/Torque Control Shoulder/Discrete Derivative'
 * '<S22>'  : 'DATA_COLLECTION/Torque Control Shoulder/Discrete Derivative1'
 * '<S23>'  : 'DATA_COLLECTION/Torque Control Shoulder/Discrete Derivative2'
 * '<S24>'  : 'DATA_COLLECTION/Torque Control Shoulder/Discrete Derivative3'
 */
#endif                                 /* RTW_HEADER_DATA_COLLECTION_h_ */
