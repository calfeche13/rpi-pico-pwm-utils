#include <math.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "../include/pwm_utils.h"

/**
 * updates the config then return the slice_num
 * @input gpio is the rpi pico gp pin
 * @input clkdiv_mode is the clock divide mode see https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__pwm.html#ga0a00197703c8606641488cfff3f660e6 for more details
 * @input clkdiv is the number to divide the frequency into separate groups where each group will only count as 1 when clkdiv_mode is satisfied
 */
uint pwm_set_config(uint gpio, uint clkdiv_mode, uint clkdiv) {
  // Only the PWM B pins can be used as inputs.
  assert(pwm_gpio_to_channel(gpio) == PWM_CHAN_B);
  uint slice_num = pwm_gpio_to_slice_num(gpio);

  // Count once for every 100 cycles the PWM B input is high
  pwm_config cfg = pwm_get_default_config();
  pwm_config_set_clkdiv_mode(&cfg, clkdiv_mode);
  pwm_config_set_clkdiv(&cfg, clkdiv);
  pwm_init(slice_num, &cfg, false);
  gpio_set_function(gpio, GPIO_FUNC_PWM);

  return slice_num;
}

/**
 * sets the counter to 0 then starts and stop the pwm with a pause in between the returns the counter depending on what the mode and div is used in the configuration
 */
int pwm_util_get_measured_value(uint slice_num, int measure_time_ms) {
  pwm_set_counter(slice_num, 0);
  // enable pwm then pause for some time then disable it again
  pwm_set_enabled(slice_num, true);
  sleep_ms(measure_time_ms);
  pwm_set_enabled(slice_num, false);
  // read the counter
  return pwm_get_counter(slice_num);
}

/**
 * measures the frequency of the pwm signal
 */
int pwm_util_measure_frequency(uint gpio) {
  uint slice_num = pwm_set_config(gpio, PWM_DIV_B_RISING, 1);
  return pwm_util_get_measured_value(slice_num, PWM_FREQ_MEASURE_TIME_MS) * (ONE_SECOND_IN_MILLIS / PWM_FREQ_MEASURE_TIME_MS);
}

/**
 * measures the duty cycle of the pwm signal
 * @return the duty cycle in decimal form
 */
float pwm_util_measure_duty_cycle(uint gpio) {
  uint slice_num = pwm_set_config(gpio, PWM_DIV_B_HIGH, PWM_FREQ_MEASURE_TIME_MS);
  int counter_val = pwm_util_get_measured_value(slice_num, 20);
  float counting_rate = clock_get_hz(clk_sys) / PWM_FREQ_MEASURE_TIME_MS;
  float max_possible_count = counting_rate * ((float) 20/ (float) ONE_SECOND_IN_MILLIS);
  return (float) counter_val / max_possible_count;
}

float pwm_util_measure_pulse_width(uint gpio) {
  float duty_cycle = pwm_util_measure_duty_cycle(gpio);
  int frequency = pwm_util_measure_frequency(gpio);
  if (frequency == 0) {
    return 0;
  }

  return (ONE_SECOND_IN_MILLIS / (float) frequency) * duty_cycle;
}

/**
 * this treats the pwm signal as a servo input.
 * will calculate and retrieve the angle ment for the servo given the pwm signal.
 */
int pwm_util_get_degrees(uint gpio) {
  float duty_cycle = pwm_util_measure_duty_cycle(gpio);
  int freq = pwm_util_measure_frequency(gpio);
  float degrees = (((float) duty_cycle - PWM_MIN_DUTY_CYCLE) / (PWM_MAX_DUTY_CYCLE - PWM_MIN_DUTY_CYCLE)) * 180;
  return fmax(fmin(round(degrees), 180), 0);
}