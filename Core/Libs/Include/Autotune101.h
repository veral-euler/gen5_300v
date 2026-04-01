//**********************************************************************************************************************
//* Module name: Autotune.h
//*
//* Copyright 2026 C-Electric Automotive Drive as an unpublished work.
//* All Rights Reserved.
//*
//* The information contained herein is confidential
//* property of C-Electric Automotive Drive. The use, copying, transfer
//* or disclosure of such information is prohibited except by
//* express written agreement with Company.
//*
//* History:- Added rpm reference and closed loop open loop.
//            Added transistion neutral tmo
//*
//* First written on 19/03/2026 by  Pratheesh S
//*
//* Module Description:
//* Header file for Autotune
//**********************************************************************************************************************

#ifndef AUTOTUNE101_H_
#define AUTOTUNE101_H_

#include "main.h"

//Configuration Parameters
#define AO_SET_TIME             2000
#define AUTOTUNE_FREERUNCOUNT	10000
#define RATED_TUNING_RPM		825
#define AUTOTUN_SPEED_RAMP_TIME	1
#define AUTOTUNE_SPEED_RAMP		10
#define MAX_ITERATION			6
#define MAX_VD				    (float)(-0.51)
#define MIN_VD				    (float)(-2.0)
#define TUNING_CALC_RPM			(RATED_TUNING_RPM-100)
#define	ALIGNEMENT_TMO           615
#define AVERAGE_SAMPLE           128
#define AUTO_TUNING_IDREF        (float)55.0
#define AUTOTUNE_ANGLE_INCREMENT (float)0.001
#define AUTOTUNE_IDREF_INCREMENT (float)0.02
#define ANGLE_RAD_360            (float)TWO_PI
#define MOTOR_POLE_PAIRS		 POLEPAIRS//Motor pole pairs
#define	OFFSET_NEGATE			-1
#define AUTOTUNESTATE_CHANGE_TMO	2000
#define VD_VQ_AVERAGE_COUNT			256

typedef enum{
    NORMAL_RUN,
    ANGLE_AUTOTUNE,
    ANGLE_AUTOTUNE_FREERUN
}State;

typedef enum{
    PHASE_ALIGN,
    PHASE_RAW_OFFSET_CALC,
    PHASE_ANGLE_OFFSET_CALIB_POSITIVE,
    PHASE_ANGLE_OFFSET_CALIB_NEGATIVE,
    RAW_OFFSET_CLEAR
}ATA_State;

typedef enum{
    Motor_Forward,
    Motor_Reverse,
    Motor_Neutral
}ATA_Direction;

typedef enum{
    Open_Loop,
    Closed_Loop
}ATA_Loop;

typedef struct
{
	float f_idSetRef;
	float f_IdRefIncrementValue;
	float f_CalibElectricalAngleInc;
	float F_MaxVd;
	float F_MinVd;
	float f_Electrical360Rad;
	uint8_t u8_MOTOR_POLE_PAIRS;
	uint16_t u16_AO_Set_Time;
	uint16_t u16FreeRunTmo;
	float f_Autotune_RPM_Set_Ref;
	uint16_t u16StateChangeTMO;
	uint16_t u16_AUTOTUN_SPEED_RAMP_TIME;
	uint16_t u16_AUTOTUNE_SPEED_RAMP;
	uint16_t u16_MAX_ITERATION;
	uint16_t u16_TUNING_CALC_RPM;
	uint16_t u16_ALIGNEMENT_TMO;
	uint16_t u16_AVERAGE_SAMPLE;
	uint16_t u16_VD_VQ_AVERAGE_COUNT;
}tag_AutotuneConfig;
typedef struct
{
	float f_Idref;
	float f_Iqref;
	float f_Electricalangle;
    float f_Initial_offset;
    float f_Offset_CW;
    float f_Offset_CCW;
    float f_MotorRpmRef;
    uint8_t AutotuneCompleteflag;
    uint8_t u8NegationFlag;
    ATA_Loop MotorloopStatus;
    ATA_Direction CalibrationDirection;
} tag_AngleAutoTuneOutputParam;

typedef struct
{
    float f_Pwmangle;
    float f_Vq;
    float f_Vd;
    float f_MotorRpm;
    State AutotuneFlag;
} tag_AngleAutoTuneInputParam;

typedef struct
{
    float f_VdAvg;
    float f_VqAvg;
    float f_AngleCalibrationOffset;
    float f_Vddiff;
    uint8_t u8FreeRunIteration;
    uint8_t u8AngleCalibrationCompleteFlag;
} tag_AngleAutoTuneDebugParam;


extern uint8_t u8FreeRunIteration,u8AngleCalibrationCompleteFlag,u8AngleAutotuningPhase;
extern uint16_t u16FreeRunTmo,u16StateChangeTM0;
extern float f_MaxVd,f_MinVd;

extern tag_AngleAutoTuneDebugParam TagAutotuneDebug;
extern tag_AngleAutoTuneOutputParam TagAutotuneOutput;
extern tag_AngleAutoTuneInputParam TagAutotuneInput;
extern tag_AutotuneConfig AutotuneConfig;

void AngleAutotuningRoutine(tag_AngleAutoTuneInputParam *t_InputParamPtr,tag_AngleAutoTuneOutputParam *t_OutputParamPtr,tag_AngleAutoTuneDebugParam *t_DebugParamPtr);
void AutotuneInit (tag_AutotuneConfig *ptr);
void AutotuneRawOffsetCalc (tag_AngleAutoTuneOutputParam *t_OutputParamPtr);
void AutotuneAngleCalibration (tag_AngleAutoTuneInputParam *t_InputParamPtr,tag_AngleAutoTuneOutputParam *t_OutputParamPtr,tag_AngleAutoTuneDebugParam *t_DebugParamPtr);

#endif /* AUTOTUNE102_H_ */

