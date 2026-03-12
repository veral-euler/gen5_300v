#ifndef __PERIPHERAL_INIT_H_
#define __PERIPHERAL_INIT_H_

#include "main.h"

void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
void MX_GPIO_Init(void);
void MX_DMA_Init(void);
void MX_TIM1_Init(void);
void MX_ADC2_Init(void);
void MX_TIM5_Init(void);
void MX_TIM17_Init(void);
void MX_ADC1_Init(void);
void MX_TIM2_Init(void);
void MX_FDCAN2_Init(void);
void MX_I2C2_Init(void);

#endif /* end __PERIPHERAL_INIT_H_ */