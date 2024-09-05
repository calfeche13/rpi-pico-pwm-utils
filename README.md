# Rasberry PI Pico PWM Utils

PWM Utils for the RP2040.

## Motivation

This module was developed as part of a personal project for a custom 3D printer bed leveling system. The PWM Utils includes a PWM-to-angle conversion feature, which is necessary because the 3D printer sends a PWM signal to control the servo motor of the auto bed leveling sensor, specifying its current state. The PWM Utils reads the PWM signal from the 3D printer, interprets it, and determines whether the auto bed leveling process has commenced.

## Want to Support Me?

If you want me to continue making useful apps like this please support me through the links below :)

<a href="https://paypal.me/ChosenAlfeche"
    arget="_blank">
    <img src="READMEFILES/paypal.png"
        alt="Buy Me A Coffee"
        style="padding-right: 24px; height: 59px !important;width: 224px !important;" />
</a>

<a href="https://buymeacoffee.com/calfeche"
    target="_blank">
    <img src="READMEFILES/buy_me_a_coffee.png"
        alt="Buy Me A Coffee"
        style="padding-left: 8px; height: 73px !important;width: 224px !important;" />
</a>

## Functions
Sets the PWM configuration.
```c++
uint pwm_set_config(uint gpio, uint clkdiv_mode, uint clkdiv);
```

Measures the value.
```c++
int pwm_util_get_measured_value(uint slice_num, int measure_time_ms);
```

Converts the measured value into frequency.
```c++
int pwm_util_measure_frequency(uint gpio);
```

Converts the measured value into duty cycle.
```c++
float pwm_util_measure_duty_cycle(uint gpio);
```

Converts the measured value into pulse width.
```c++
float pwm_util_measure_pulse_width(uint gpio);
```

Converts the measured value into the angle in degress.
```c++
int pwm_util_get_degrees(uint gpio);
```