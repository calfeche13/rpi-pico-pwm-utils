/**
 * This is used to test the functionalities of PWM utils
 * 
 * @author Chosen Realm Alfeche
 * @since 2022-10-01
 */
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "./include/pwm_utils.h"

int main() {

  int pwmMeasurePin = 1;

  stdio_init_all();

  while(true) {
    printf("freq: %d\n", pwm_util_measure_frequency(pwmMeasurePin));
    printf("duty cycle: %f\n", pwm_util_measure_duty_cycle(pwmMeasurePin));
    printf("pulse width: %f\n", pwm_util_measure_pulse_width(pwmMeasurePin));
    printf("cnt: %d\n", pwm_util_get_degrees(pwmMeasurePin));
    sleep_ms(1000);
  }
}