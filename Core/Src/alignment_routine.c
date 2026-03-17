#include "alignment_routine.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim5;

void Motor_Alignment_Routine(void)
{
// Placeholder for motor alignment routine implementation
    if (cS == ANGLE_CALIB) {
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
        while (d.start_alignment == 1 && d.end_alignment == 0) {
            static uint8_t count = 0;
            count++;

            HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
            HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
            HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);

            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);

            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, ALIGN_DUTY);
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, ALIGN_DUTY);
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, ALIGN_DUTY);

            HAL_Delay(40);

            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);

            HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
            HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);
            HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);

            if (count >= 5) {
                d.start_alignment = 0;
                d.end_alignment = 1;
                d.count_at_alignment = __HAL_TIM_GET_COUNTER(&htim2);
                d.Angle_From_Duty = (100.0f - d.Duty) * 0.01f * 2.0f * M_PI - HIGH_PULSE16_ERROR;
                d.Angle_From_Duty = fmodf(d.Angle_From_Duty, TWO_PI);
                d.Count_From_Duty = (uint16_t)((d.Angle_From_Duty / TWO_PI) * (TIM2_ARR + 1));
                d.offset_angle_elec = d.Angle_From_Duty * POLEPAIRS;
                d.offset_angle_elec = fmodf(d.offset_angle_elec, TWO_PI);
                HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
                HAL_TIM_IC_Stop_IT(&htim5, TIM_CHANNEL_1);
                HAL_TIM_IC_Stop_IT(&htim5, TIM_CHANNEL_2);
                HAL_TIM_IC_DeInit(&htim5);
                HAL_TIM_Base_MspDeInit(&htim5);
                cS = ANGLE_OFFSET_STORE;
            }
        }
    }
}