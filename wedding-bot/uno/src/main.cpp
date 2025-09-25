#include <Arduino.h>

const uint8_t ENA1 = 3;
const uint8_t IN1 = 2;
const uint8_t IN2 = 4;

const uint8_t PWM_MIN = 0;
const uint8_t PWM_MAX = 255;

/// Get the desired PWM value given a speed from 0.0 to 1.0.
int normalize_speed(float speed);

void setup()
{
    pinMode(IN1, OUTPUT);
    pinMode(ENA1, OUTPUT);
    pinMode(IN2, OUTPUT);
}

void loop()
{
    // the diaphragm pump only runs in the forward direction:
    // IN1 is HIGH and IN2 is LOW for forward
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA1, normalize_speed(0.7));
}

int normalize_speed(float speed)
{
    // clamp the speed
    if (speed > 1.0)
    {
        speed = 1.0;
    }

    if (speed < 0.0)
    {
        speed = 0.0;
    }

    return (int)(speed * (PWM_MAX - PWM_MIN)) + PWM_MIN;
}