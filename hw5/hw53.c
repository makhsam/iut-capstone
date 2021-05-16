/**
 * Task 3. Trace the line
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

#define MIN_SPEED 0
#define MAX_SPEED 100
#define CAR_SPEED 30

#define BLACK_FIELD 1
#define WHITE_FIELD 0

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

void goLeft()
{
    digitalWrite(IN1_PIN, LOW);
    digitalWrite(IN2_PIN, HIGH);
    digitalWrite(IN3_PIN, HIGH);
    digitalWrite(IN4_PIN, LOW);
    printf("Left\n");
}

void goRight()
{
    digitalWrite(IN1_PIN, HIGH);
    digitalWrite(IN2_PIN, LOW);
    digitalWrite(IN3_PIN, LOW);
    digitalWrite(IN4_PIN, HIGH);
    printf("Right\n");
}

void smoothLeft()
{
    softPwmWrite(IN1_PIN, MAX_SPEED / 8);
    softPwmWrite(IN2_PIN, MIN_SPEED);
    softPwmWrite(IN3_PIN, MAX_SPEED);
    softPwmWrite(IN4_PIN, MIN_SPEED);
    printf("Smooth left\n");
}

void smoothRight()
{
    softPwmWrite(IN1_PIN, MAX_SPEED);
    softPwmWrite(IN2_PIN, MIN_SPEED);
    softPwmWrite(IN3_PIN, MAX_SPEED / 8);
    softPwmWrite(IN4_PIN, MIN_SPEED);
    printf("Smooth right\n");
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

    initLineTracer();
    initDCMotor();

    // Run the car
    goForward();

    while (1)
    {
        leftTracer = digitalRead(LEFT_TRACER_PIN);
        rightTracer = digitalRead(RIGHT_TRACER_PIN);

        if (leftTracer == WHITE_FIELD && rightTracer == BLACK_FIELD)
        {
            printf("Turn right command\n");
            goRight();
            // smoothRight();
        }
        else if (leftTracer == BLACK_FIELD && rightTracer == WHITE_FIELD)
        {
            printf("Turn left command\n");
            goLeft();
            // smoothLeft();
        }
        else if (leftTracer == WHITE_FIELD && rightTracer == WHITE_FIELD)
        {
            printf("Go forward command\n");
            goForward();
        }
        else if (leftTracer == BLACK_FIELD && rightTracer == BLACK_FIELD)
        {
            printf("Finish command\n");
            stopDCMotor();
        }

        delay(50);
    }

    stopDCMotor();
    return 0;
}
