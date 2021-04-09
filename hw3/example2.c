/**
 * Example 2: (PWM) Smooth Turn
 */

#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define IN1_PIN 1
#define IN2_PIN 4
#define IN3_PIN 5
#define IN4_PIN 6

#define MAX_SPEED 50
#define MIN_SPEED 0

void initDCMotor()
{
    pinMode(IN1_PIN, SOFT_PWM_OUTPUT);
    pinMode(IN4_PIN, SOFT_PWM_OUTPUT);
    pinMode(IN5_PIN, SOFT_PWM_OUTPUT);
    pinMode(IN6_PIN, SOFT_PWM_OUTPUT);
    softPwmCreate(IN1_PIN, MIN_SPEED, MAX_SPEED);
    softPwmCreate(IN4_PIN, MIN_SPEED, MAX_SPEED);
    softPwmCreate(IN5_PIN, MIN_SPEED, MAX_SPEED);
    softPwmCreate(IN6_PIN, MIN_SPEED, MAX_SPEED);
}

void smoothLeft()
{
    softPwmWrite(IN1_PIN, MAX_SPEED / 8);
    softPwmWrite(IN4_PIN, MIN_SPEED);
    softPwmWrite(IN5_PIN, MAX_SPEED);
    softPwmWrite(IN6_PIN, MIN_SPEED);
}

void smoothRight()
{
    softPwmWrite(IN1_PIN, MAX_SPEED);
    softPwmWrite(IN4_PIN, MIN_SPEED);
    softPwmWrite(IN5_PIN, MAX_SPEED / 8);
    softPwmWrite(IN6_PIN, MIN_SPEED);
}
