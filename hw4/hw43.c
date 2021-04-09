#include <stdio.h>
#include <wiringPi.h>

#define TRIG_PIN 28
#define ECHO_PIN 29

#define IN1_PIN 1
#define IN2_PIN 4
#define IN3_PIN 5
#define IN4_PIN 6

void initUltrasonic();
void initMotor();
void initDCMotor();
void goForward();
void stopDCMotor();
int getDistance();

int main(void)
{
    if (wiringPiSetup() == -1)
        return 0;

    int distance = 0;
    initUltrasonic();
    initMotor();

    // Run motor
    initDCMotor();
    goForward();

    while (1)
    {
        distance = getDistance();
        printf("distance %dcm\n", distance);

        if (distance < 30)
        {
            stopDCMotor();
            return 0;
        }

        delay(100);
    }

    return 0;
}

void initUltrasonic()
{
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

void initMotor()
{
    pinMode(IN1_PIN, OUTPUT);
    pinMode(IN2_PIN, OUTPUT);
    pinMode(IN3_PIN, OUTPUT);
    pinMode(IN4_PIN, OUTPUT);
}

void initDCMotor()
{
    digitalWrite(IN1_PIN, HIGH);
    digitalWrite(IN2_PIN, HIGH);
    digitalWrite(IN3_PIN, HIGH);
    digitalWrite(IN4_PIN, HIGH);
}

void goForward()
{
    digitalWrite(IN1_PIN, HIGH);
    digitalWrite(IN2_PIN, LOW);
    digitalWrite(IN3_PIN, HIGH);
    digitalWrite(IN4_PIN, LOW);
    printf("Forward\n");
}

void stopDCMotor()
{
    digitalWrite(IN1_PIN, LOW);
    digitalWrite(IN2_PIN, LOW);
    digitalWrite(IN3_PIN, LOW);
    digitalWrite(IN4_PIN, LOW);
    printf("Stop\n");
}

int getDistance()
{
    int start_time = 0, end_time = 0;
    float distance = 0;

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    while (digitalRead(ECHO_PIN) == 0)
        start_time = micros();

    while (digitalRead(ECHO_PIN) == 1)
        end_time = micros();

    distance = (end_time - start_time) / 29. / 2.;

    return (int)distance;
}