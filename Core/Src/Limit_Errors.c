#include "Limit_Errors.h"

uint8_t Over_Current_Phase_Error(float a, float b, float c) {
    volatile float max_curr = fmaxf(a, fmaxf(b, c));
    volatile float min_curr = fminf(a, fminf(b, c));

    static uint16_t error_counter = 0;

    if (max_curr > MAX_PHASE_CURRENT || min_curr < -MAX_PHASE_CURRENT) {
        error_counter++;

        if (error_counter >= PHASE_OC_COUNT) {
            error_counter = 0;
            d.error_c2 |= (1 << 3);
            return !HAL_OK;
        }
    } else {
        if (error_counter <= 0) {
            error_counter = 0;
        } else {
            error_counter--;
        }
    }

    return HAL_OK;
}

uint8_t Over_Current_Id_Iq_Error(float Id, float Iq) {
    static uint16_t error_counter = 0;

    if (Id > FOC_MTPA_FF_U.Id_Iq_MTPA_limit.Id_up_limit || Id < FOC_MTPA_FF_U.Id_Iq_MTPA_limit.Id_low_limit || Iq < FOC_MTPA_FF_U.Id_Iq_MTPA_limit.Iq_low_limit || Iq > FOC_MTPA_FF_U.Id_Iq_MTPA_limit.Iq_up_limit) {
        error_counter++;

        if (error_counter >= ID_IQ_OC_COUNT) {
            error_counter = 0;
            d.error_c2 |= (1 << 4);
            return !HAL_OK;
        }
    } else {
        if (error_counter <= 0) {
            error_counter = 0;
        } else {
            error_counter--;
        }
    }

    return HAL_OK;
}

uint8_t Bus_Voltage_Error(float Bus_DC) {
    static uint16_t error_counter_ov = 0;
    static uint16_t error_counter_uv = 0;

    if (Bus_DC >= BUS_DC_OV_LIMIT) {
        error_counter_ov++;

        if (error_counter_ov >= BUS_DC_OV_COUNT) {
            error_counter_ov = 0;
            d.error_c1 |= (1 << 4);
            return (uint8_t)1;
        }
    } else {
        if (error_counter_ov <= 0) {
            error_counter_ov = 0;
        } else {
            error_counter_ov--;
        }
    }

    if (Bus_DC <= BUS_DC_UV_LIMIT) {
        error_counter_uv++;

        if (error_counter_uv >= BUS_DC_UV_COUNT) {
            error_counter_uv = 0;
            d.error_c1 |= (1 << 5);
            return (uint8_t)2;
        }
    } else {
        if (error_counter_uv <= 0) {
            error_counter_uv = 0;
        } else {
            error_counter_uv--;
        }
    }

    return HAL_OK;
}

uint8_t Aux_Voltage_Error(float Aux_DC) {
    /* Checking for Aux DC UV Error explicitly */
    if (Aux_DC <= AUX_UV_LIMIT && d.motor_start == 1) {
        d.error_c3 |= (1 << 1);
        return !HAL_OK;
    } else {
        return HAL_OK;
    }
}

uint8_t Mtr_OT_Error(float motor_temp) {
    if (motor_temp >= MOTOR_TEMP_OT_LIMIT) {
        d.error_c1 |= (1 << 3);
        return !HAL_OK;
    } else {
        return HAL_OK;
    }
}

uint8_t Mtc_OT_Error(float controller_temp) {
    if (controller_temp >= CONTRL_TEMP_OT_LIMIT) {
        return !HAL_OK;
    } else {
        return HAL_OK;
    }
}

void Error_Check(void) {
    if (Over_Current_Phase_Error(FOC_MTPA_FF_U.PhaseCurrent[0], FOC_MTPA_FF_U.PhaseCurrent[1], FOC_MTPA_FF_U.PhaseCurrent[2]) == !HAL_OK) {
        er.error_triggered = 1;
        er.phase_curr_error = 1;
        err = PHASE_CURR_ERROR;
        cS = CONT_ERROR;
    }

    if (Over_Current_Id_Iq_Error(FOC_MTPA_FF_Y.Id, FOC_MTPA_FF_Y.Iq) == !HAL_OK) {
        er.error_triggered = 1;
        er.id_iq_oc_error = 1;
        err = ID_IQ_OC_ERROR;
        cS = CONT_ERROR;
    }

    if (Bus_Voltage_Error(d.Vdc) == 1) {
        er.error_triggered = 1;
        er.bus_voltage_ov_error = 1;
        err = BUS_VOLTAGE_OV_ERROR;
        cS = CONT_ERROR;
    }

    if (Bus_Voltage_Error(d.Vdc) == 2) {
        er.error_triggered = 1;
        er.bus_voltage_uv_error = 1;
        err = BUS_VOLTAGE_UV_ERROR;
        cS = CONT_ERROR;
    }

    if (Aux_Voltage_Error(d.Aux_dc) == !HAL_OK) {
        er.error_triggered = 1;
        er.aux_voltage_uv_error = 1;
        err = AUX_VOLTAGE_UV_ERROR;
        cS = CONT_ERROR;
    }

    if (Mtr_OT_Error(d.Mtr_temp) == !HAL_OK) {
        er.error_triggered = 1;
        er.mtr_temp_ot_error = 1;
        err = MTR_TEMP_OT_ERROR;
        cS = CONT_ERROR;
    }

    if (Mtc_OT_Error(d.Mtc_temp) == !HAL_OK) {
        er.error_triggered = 1;
        er.mtc_temp_ot_error = 1;
        err = MTC_TEMP_OT_ERROR;
        cS = CONT_ERROR;
    }

    disable_drive();
}