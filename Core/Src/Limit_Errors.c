#include "Limit_Errors.h"

uint8_t Over_Current_Phase_Error(float a, float b, float c) {
    volatile float max_curr = fmaxf(a, fmaxf(a, b));
    volatile float min_curr = fminf(a, fminf(a, b));

    static uint16_t error_counter = 0;

    if (max_curr > MAX_PHASE_CURRENT || max_curr < -MAX_PHASE_CURRENT) {
        error_counter++;

        if (error_counter >= 10) {
            error_counter = 0;

            er.error_triggered = 1;
            er.phase_curr_error = 1;
            err = PHASE_CURR_ERROR;
            cS = CONT_ERROR;

            return !HAL_OK;
        }
    } else {
        if (error_counter <= 0) {
            error_counter = 0;
        }

        error_counter--;

        return HAL_OK;
    }
}

uint8_t Over_Current_Id_Iq_Error(float Id, float Iq) {
    static uint16_t error_counter = 0;

    if (FOC_LivGguard_Y.Id > FOC_LivGguard_U.Id_Iq_MTPA_limit.Id_up_limit || FOC_LivGguard_Y.Id < FOC_LivGguard_U.Id_Iq_MTPA_limit.Id_low_limit || FOC_LivGguard_Y.Iq < FOC_LivGguard_U.Id_Iq_MTPA_limit.Iq_low_limit || FOC_LivGguard_Y.Iq > FOC_LivGguard_U.Id_Iq_MTPA_limit.Iq_up_limit) {
        error_counter++;

        if (error_counter >= 10) {
            error_counter = 0;

            er.error_triggered = 1;
            er.id_iq_oc_error = 1;
            err = ID_IQ_OC_ERROR;
            cS = CONT_ERROR;

            return !HAL_OK;
        }
    } else {
        if (error_counter <= 0) {
            error_counter = 0;
        }

        error_counter--;

        return HAL_OK;
    }
}

uint8_t Bus_Voltage_Error(float Bus_DC) {

}

uint8_t Aux_Voltage_Error(float Aux_DC) {
    /* Checking for Aux DC UV Error explicitly */
    if (d.Aux_dc <= 9.5 && d.motor_start == 1) {
        er.error_triggered = 1;
        er.aux_voltage_uv_error = 1;
        err = AUX_VOLTAGE_OV_ERROR;
        cS = CONT_ERROR;

        return !HAL_OK;
    }

    return HAL_OK;
}

void Error_Check(void) {

}