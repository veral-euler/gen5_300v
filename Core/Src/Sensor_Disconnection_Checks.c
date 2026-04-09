#include "Sensor_Disconnection_Checks.h"

/* Exporting this buffer from main.c */
extern uint16_t adc1_buffer[5];
extern uint16_t injectedVal[2];

uint8_t encoder_ab_error_check(void) {
  /* Checking A and B error based on A and B states and Id and Iq ref vals */
  if (d.A_Pulse == GPIO_PIN_SET && d.B_Pulse == GPIO_PIN_SET && d.A_B_XOR == GPIO_PIN_RESET && fabsf(FOC_MTPA_FWC_FF_Y.Iq) >= 250.0f && fabsf(FOC_MTPA_FWC_FF_Y.Id) >= 250.0f && d.count_diff_at_z >= 60) {
    return !HAL_OK; // A and B pulses are the same, which is an error
  } else if (d.A_Pulse == GPIO_PIN_SET && fabsf(FOC_MTPA_FWC_FF_Y.Iq) >= 250.0f && fabsf(FOC_MTPA_FWC_FF_Y.Id) >= 250.0f && d.count_diff_at_z >= 60) {
    return !HAL_OK; // A pulse is set but B pulse is not, which is an error
  } else if (d.B_Pulse == GPIO_PIN_SET && fabsf(FOC_MTPA_FWC_FF_Y.Iq) >= 250.0f && fabsf(FOC_MTPA_FWC_FF_Y.Id) >= 250.0f && d.count_diff_at_z >= 60) {
    return !HAL_OK; // B pulse is set but A pulse is not, which is an error
  }

  return HAL_OK; // No error
}

uint8_t encoder_z_index_check(void) {
  /* Check for Z index errors based on z_count */
  /* Run at every 20ms*/
  if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7) == GPIO_PIN_SET && d.count_diff_at_z >= 60) {
    return !HAL_OK; // No Z index pulse detected
  }

  if (d.z_count_diff >= 2) {
    return !HAL_OK;
  }

  return HAL_OK; // Z index pulse detected
}

uint8_t encoder_pwm_error_check(void) {
  //TODO: Implement check for encoder PWM signal errors if necessary
  if (d.ICvalue <= 0 || d.Frequency <= 0 || d.Duty < 0 || d.Duty > 100) {
    return !HAL_OK; // Invalid PWM signal detected
  }

  return HAL_OK; // Placeholder return value
}

uint8_t encoder_5v_error_check(void) {
  if (d.A_Pulse == GPIO_PIN_RESET && d.B_Pulse == GPIO_PIN_RESET && d.A_B_XOR == GPIO_PIN_RESET && HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET && fabsf(FOC_MTPA_FWC_FF_Y.Id) >= 250.0f && fabsf(FOC_MTPA_FWC_FF_Y.Iq) >= 250.0f && d.count_diff_at_z >= 60) {
    return !HAL_OK;
  }

  return HAL_OK;
}

uint8_t temp_sensor_disconnection_check(uint16_t temperature_analog_val, uint16_t threshold) {
  /* Check for temperature sensor disconnection based on a threshold */
  if (temperature_analog_val >= threshold) {
    return !HAL_OK; // Sensor disconnection detected
  } else if (temperature_analog_val <= 0) {
    return !HAL_OK; // Sensor disconnection detected
  }

  return HAL_OK; // Sensor is connected
}

#if PROTECTION_MODEL
void Model_Params_Input(void) {
  /* Placeholder for any model parameter updates if necessary */
  // This function can be used to update any parameters in the MCU Protections model based on sensor readings or other conditions

  /* Populating MCU Protections input data structures */
  MCU_Protections_U.I_a = FOC_MTPA_FWC_FF_U.PhaseCurrent[2];
  MCU_Protections_U.I_b = FOC_MTPA_FWC_FF_U.PhaseCurrent[1];
  MCU_Protections_U.I_c = FOC_MTPA_FWC_FF_U.PhaseCurrent[0];
  MCU_Protections_U.MC_Temperature_C = d.Mtc_temp;
  MCU_Protections_U.Motor_Temperature_C = d.Mtr_temp;
  MCU_Protections_U.Bus_Voltage_V = d.Vdc;
  MCU_Protections_U.Aux_Voltage_V = d.Aux_dc;
}

void Model_Output_Flag_Checks(void) {
  /* Placeholder for checking model outputs and setting error flags if necessary */
  // This function can be used to check the outputs of the MCU Protections model and set error flags or take other actions based on those outputs

  /* Checking for error flag and changing the STATE */
  if (MCU_Protections_Y.Aux_Voltage_Flag == OV_Error) {
    er.error_triggered = 1;
    er.aux_voltage_ov_error = 1;
    err = AUX_VOLTAGE_OV_ERROR;
    cS = CONT_ERROR;
  } else if (MCU_Protections_Y.Aux_Voltage_Flag == UV_Error) {
    er.error_triggered = 1;
    er.aux_voltage_uv_error = 1;
    err = AUX_VOLTAGE_UV_ERROR;
    cS = CONT_ERROR;
  } else if (MCU_Protections_Y.Bus_Voltage_Flag == OV_Error) {
    er.error_triggered = 1;
    er.bus_voltage_ov_error = 1;
    err = BUS_VOLTAGE_OV_ERROR;
    cS = CONT_ERROR;
  } else if (MCU_Protections_Y.Bus_Voltage_Flag == UV_Error) {
    er.error_triggered = 1;
    er.bus_voltage_uv_error = 1;
    err = BUS_VOLTAGE_UV_ERROR;
    cS = CONT_ERROR;
  } else if (MCU_Protections_Y.Motor_TempFlag == OT_Error) {
    er.error_triggered = 1;
    er.mtr_temp_ot_error = 1;
    err = MTR_TEMP_OT_ERROR;
    cS = CONT_ERROR;
  } else if (MCU_Protections_Y.MC_TempFlag == OT_Error) {
    er.error_triggered = 1;
    er.mtc_temp_ot_error = 1;
    err = MTC_TEMP_OT_ERROR;
    cS = CONT_ERROR;
  } else if (MCU_Protections_Y.Current_Flag == OC_Error) {
    er.error_triggered = 1;
    er.phase_curr_error = 1;
    err = PHASE_CURR_ERROR;
    cS = CONT_ERROR;
  }
}
#endif

void ADC1_Analog_Val_Update(void) {
  /* Placeholder for updating any analog values from ADC1 if necessary */
  // This function can be used to update any global variables or data structures with the latest analog values read from ADC1

  /* Gathering MTR Temp, CNT Temp, VDC and AUX DC in while loop also throttle voltage */
  d.Mtc_temp = NTC_Read(adc1_buffer[CONTRL_TEMP], MTC_NTC_R25);
  d.mtc_analog_val = adc1_buffer[CONTRL_TEMP];
  d.Mtr_temp = PTC_Read(adc1_buffer[MOTOR_TEMP], MTR_PTC_R25);
  d.mtr_analog_val = adc1_buffer[MOTOR_TEMP];
  d.Vdc = (uint16_t)((float)adc1_buffer[BUS_DC] * BUS_VDC_SCALE);
  d.Aux_dc = (uint16_t)((float)adc1_buffer[AUX_DC] * AUX_VDC_SCALE);
  d.throttle_v = adc1_buffer[THROTTLE] * ADC_TO_V * 2.0f;
  d.thr_v_mv = (adc1_buffer[THROTTLE] * 3297U * 2U) / 65536U;

  #if THR_BASED_THRV
  FOC_MTPA_FWC_FF_U.Throttle_input.Throttle_Inst_Voltage = d.throttle_v;
  #endif

  /* Calculating Irms, Vrms and Throttle_percentage */
  d.irms = sqrtf(FOC_MTPA_FWC_FF_Y.Id * FOC_MTPA_FWC_FF_Y.Id + FOC_MTPA_FWC_FF_Y.Iq * FOC_MTPA_FWC_FF_Y.Iq) / ROOT2;
  d.vrms = sqrtf(FOC_MTPA_FWC_FF_Y.Vq * FOC_MTPA_FWC_FF_Y.Vq + FOC_MTPA_FWC_FF_Y.Vd * FOC_MTPA_FWC_FF_Y.Vd) / ROOT2;
  d.throttle_percent = (uint8_t)((d.irms / MOTOR_PEAK_AC) * 100.0f);
}

uint8_t Initial_Fault_Check(void) {
	if (injectedVal[0] <= CURR_SEN_ANLG_LOW || injectedVal[1] <= CURR_SEN_ANLG_LOW || injectedVal[0] >= CURR_SEN_ANLG_HIGH || injectedVal[1] >= CURR_SEN_ANLG_HIGH) {
		er.curr_sens_error = 1;
    err = CURR_SENS_ERROR;
		er.error_triggered = 1;
	}

	if (d.Vdc >= BUS_DC_OV_LIMIT) {
		er.bus_voltage_ov_error = 1;
    err = BUS_VOLTAGE_OV_ERROR;
		er.error_triggered = 1;
    er.error_c1 |= (1 << 4);
	}

	if (d.Vdc <= BUS_DC_UV_LIMIT) {
		er.bus_voltage_uv_error = 1;
    err = BUS_VOLTAGE_UV_ERROR;
		er.error_triggered = 1;
    er.error_c1 |= (1 << 5);
	}

	if (er.error_triggered) {
		return !HAL_OK;
	} else {
		return HAL_OK;
	}
}

void Sensor_Disconnection_Check(void) {
  #if ENABLE_ENC_ERRORS
  static uint16_t encoder_z_fault_check_count = 0;
  static uint16_t encoder_ab_fault_check_count = 0;
  static uint16_t encoder_5v_fault_check_count = 0;
  encoder_ab_fault_check_count++;
  encoder_z_fault_check_count++;
  encoder_5v_fault_check_count++;

  /* Getting the A and B pulse states getting the A XOR B */
  d.A_Pulse = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15);
  d.B_Pulse = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3);
  d.A_B_XOR = d.A_Pulse ^ d.B_Pulse;

  /* Calculating the diff b/w Curr Z and Prev Z */
  d.z_count_diff = (d.curr_z_count > d.prev_z_count) ? (d.curr_z_count - d.prev_z_count) : (d.prev_z_count - d.curr_z_count);
  /* Storing the prev Z count */
  d.prev_z_count = d.curr_z_count;
  /* Getting the abs diff b/w TIM2_ARR and count at Z ttrig */
  d.count_diff_at_z = (d.count_at_z > (TIM2_ARR + 1)) ? (d.count_at_z - (TIM2_ARR + 1)) : ((TIM2_ARR + 1) - d.count_at_z);

  /* Z disconnection error check */
  if (encoder_z_fault_check_count >= ENCODER_CHECK_MS && d.motor_start == 1) {
    static uint16_t count = 0;

    if (encoder_z_index_check() == !HAL_OK) {
      count++;
    }else {
      if (count <= 0) {
        count = 0;
      } else {
        count--;
      }
    }

    if (count >= ENCODER_FAULT_MAX_COUNT) {
      count = 0;
      er.error_c1 |= (1 << 0);
      er.error_triggered = 1;
      er.z_error = 1;
      err = ENCODER_Z_ERROR;
      cS = CONT_ERROR;
    }

    encoder_z_fault_check_count = 0;
  }

  /* A and B disconnection error check */
  if (encoder_ab_fault_check_count >= ENCODER_CHECK_MS && d.motor_start == 1) {
    static uint16_t count = 0;

    if(encoder_ab_error_check() == !HAL_OK) {
      count++;
    } else {
      if (count <= 0) {
        count = 0;
      } else {
        count--;
      }
    }

    if (count >= ENCODER_FAULT_MAX_COUNT) {
      count = 0;
      er.error_c1 |= (1 << 0);
      er.error_triggered = 1;
      er.a_b_error = 1;
      err = ENCODER_A_B_ERROR;
      cS = CONT_ERROR;
    }

    encoder_ab_fault_check_count = 0;
  }

  if (encoder_5v_fault_check_count >= ENCODER_CHECK_MS && d.motor_start == 1) {
    static uint16_t count = 0;

    if (encoder_5v_error_check() == !HAL_OK) {
      count++;
    } else {
      if (count <= 0) {
        count = 0;
      } else {
        count--;
      }
    }

    if (count >= ENCODER_FAULT_MAX_COUNT) {
      count = 0;
      er.error_c1 |= (1 << 0);
      er.error_triggered = 1;
      er.enc_5v_error = 1;
      err = ENCODER_5V_ERROR;
      cS = CONT_ERROR;
    }
  }
  #endif

  if (temp_sensor_disconnection_check(d.mtc_analog_val, TEMP_SENS_FAULT_COUNT) == !HAL_OK) {
    er.error_triggered = 1;
    er.mtc_temp_disconnection_error = 1;
    err = MTC_TEMP_DISCONNECTION_ERROR;
    cS = CONT_ERROR;
  }

  if (temp_sensor_disconnection_check(d.mtr_analog_val, TEMP_SENS_FAULT_COUNT) == !HAL_OK) {
    er.error_triggered = 1;
    er.error_c2 |= (1 << 1);
    er.mtr_temp_disconnection_error = 1;
    err = MTR_TEMP_DISCONNECTION_ERROR;
    cS = CONT_ERROR;
  }

  disable_drive();
}