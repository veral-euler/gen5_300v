#include "Sensor_Disconnection_Checks.h"

uint8_t encoder_ab_error_check(void) {
  /* Check for encoder errors based on count_diff */
  if (d.count_diff_at_z > ENCODER_ERROR_THRESHOLD) {
    return !HAL_OK; // Error detected
  }

  if (d.A_Pulse == GPIO_PIN_SET && d.B_Pulse == GPIO_PIN_SET && d.A_B_XOR == GPIO_PIN_RESET && fabsf(FOC_LivGguard_Y.Iq_ref) >= 250.0f && fabsf(FOC_LivGguard_Y.Id_ref) >= 250.0f) {
    return !HAL_OK; // A and B pulses are the same, which is an error
  } else if (d.A_Pulse == GPIO_PIN_SET && fabsf(FOC_LivGguard_Y.Iq_ref) >= 250.0f && fabsf(FOC_LivGguard_Y.Id_ref) >= 250.0f) {
    return !HAL_OK; // A pulse is set but B pulse is not, which is an error
  } else if (d.B_Pulse == GPIO_PIN_SET && fabsf(FOC_LivGguard_Y.Iq_ref) >= 250.0f && fabsf(FOC_LivGguard_Y.Id_ref) >= 250.0f) {
    return !HAL_OK; // B pulse is set but A pulse is not, which is an error
  }

  return HAL_OK; // No error
}

uint8_t encoder_z_index_check(void) {
  /* Check for Z index errors based on z_count */
  /* Run at every 100ms, assuming 100RPM */
  if (d.z_count_diff >= 2) {
    return !HAL_OK; // No Z index pulse detected
  }

  return HAL_OK; // Z index pulse detected
}

uint8_t temp_sensor_disconnection_check(uint16_t temperature, uint16_t threshold) {
  /* Check for temperature sensor disconnection based on a threshold */
  if (temperature >= threshold) {
    return !HAL_OK; // Sensor disconnection detected
  } else if (temperature <= 0) {
    return !HAL_OK; // Sensor disconnection detected
  }

  return HAL_OK; // Sensor is connected
}

void Sensor_Disconnection_Check(void) {
  static uint16_t encoder_z_fault_check_count = 0;
  static uint16_t encoder_ab_fault_check_count = 0;
  encoder_ab_fault_check_count++;
  encoder_z_fault_check_count++;

  /* Z disconnection error check */
  if (encoder_z_fault_check_count >= ENCODER_CHECK_MS && d.motor_start == 1) {
    static uint16_t count = 0;

    if (encoder_z_index_check() == !HAL_OK) {
      count++;
    }

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
      er.error_triggered = 1;
      er.a_b_error = 1;
      err = ENCODER_A_B_ERROR;
      cS = CONT_ERROR;
    }

    encoder_ab_fault_check_count = 0;
  }

  if (temp_sensor_disconnection_check(d.Mtc_temp, TEMP_SENS_FAULT_COUNT) == !HAL_OK) {
    er.error_triggered = 1;
    er.mtc_temp_disconnection_error = 1;
    err = MTC_TEMP_DISCONNECTION_ERROR;
    cS = CONT_ERROR;
  }

  if (temp_sensor_disconnection_check(d.Mtr_temp, TEMP_SENS_FAULT_COUNT) == !HAL_OK) {
    er.error_triggered = 1;
    er.mtr_temp_disconnection_error = 1;
    err = MTR_TEMP_DISCONNECTION_ERROR;
    cS = CONT_ERROR;
  }
}