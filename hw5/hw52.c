/**
 * IR tracing sensor
 * 
 * 1. Go straight until it detect the 2nd black belt
 * 2. Stop
 */

#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define LEFT_TRACER_PIN 10
#define RIGHT_TRACER_PIN 11

#define IN1_PIN 1
#define IN2_PIN 4
#define IN3_PIN 5
#define IN4_PIN 6

#define MAX_SPEED 100
#define MIN_SPEED 0
#define CAR_SPEED 30

void initLineTracer()
{
    pinMode(LEFT_TRACER_PIN, INPUT);
    pinMode(RIGHT_TRACER_PIN, INPUT);
}

void initDCMotor()
{
    pinMode(IN1_PIN, SOFT_PWM_OUTPUT);
    pinMode(IN2_PIN, SOFT_PWM_OUTPUT);
    pinMode(IN3_PIN, SOFT_PWM_OUTPUT);
    pinMode(IN4_PIN, SOFT_PWM_OUTPUT);

    softPwmCreate(IN1_PIN, MIN_SPEED, MAX_SPEED);
    softPwmCreate(IN2_PIN, MIN_SPEED, MAX_SPEED);
    softPwmCreate(IN3_PIN, MIN_SPEED, MAX_SPEED);
    softPwmCreate(IN4_PIN, MIN_SPEED, MAX_SPEED);
}

void goForward()
{
    softPwmWrite(IN1_PIN, CAR_SPEED);
    softPwmWrite(IN2_PIN, MIN_SPEED);
    softPwmWrite(IN3_PIN, CAR_SPEED);
    softPwmWrite(IN4_PIN, MIN_SPEED);
    printf("Forward with speed %d\n", CAR_SPEED);
}

void stopDCMotor()
{
    digitalWrite(IN1_PIN, LOW);
    digitalWrite(IN2_PIN, LOW);
    digitalWrite(IN3_PIN, LOW);
    digitalWrite(IN4_PIN, LOW);
    printf("Stop\n");
}

int main(void)
{
    if (wiringPiSetup() == -1)
        return 0;

    int leftTracer, rightTracer;
    int prevState = 0, currentState = 0;
    int counter = 0;

    initLineTracer();
    initDCMotor();

    // Run motor
    goForward();

    while (1)
    {
        leftTracer = digitalRead(LEFT_TRACER_PIN);
        rightTracer = digitalRead(RIGHT_TRACER_PIN);

        if (rightTracer == 0 && leftTracer == 0)
        {
            prevState = currentState;
            currentState = 0;
            printf("Car in white field\n");
        }
        else if (rightTracer == 1 && leftTracer == 1)
        {
            prevState = currentState;
            currentState = 1;
            printf("Car in black field\n");
        }

        // Car crossed the line
        if (prevState == 1 && currentState == 0)
        {
            counter++;
            printf("Crossed the line %d times\n", counter);
        }

        if (counter >= 2)
        {
            stopDCMotor();
            return 0;
        }

        delay(10);
    }

    stopDCMotor();
    return 0;
}
