
#ifndef PWM_UTILS_H_20221001
#define PWM_UTILS_H_20220101

#include "hardware/pwm.h"
#include "hardware/clocks.h"

#define PWM_FREQ_MEASURE_TIME_MS 100
#define ONE_SECOND_IN_MILLIS 1000

// redefine this to adjust the min and max duty cycle of your input
// to get the min and max simply use pwm_util_get_degrees and use the values for 0 and 180 degrees angle respectively
#define PWM_MIN_DUTY_CYCLE 0.027240
#define PWM_MAX_DUTY_CYCLE 0.120040

uint pwm_set_config(uint gpio, uint clkdiv_mode, uint clkdiv);

int pwm_util_get_measured_value(uint slice_num, int measure_time_ms);

int pwm_util_measure_frequency(uint gpio);

float pwm_util_measure_duty_cycle(uint gpio);

float pwm_util_measure_pulse_width(uint gpio);

int pwm_util_get_degrees(uint gpio);

#endif