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

/**
 * Ultrasonic sensor functions
 */
void initUltrasonic()
{
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    // TRIG_PIN must start LOW
    digitalWrite(TRIG_PIN, LOW);
    delay(500);
}

int getDistance()
{
    int start_time = 0, end_time = 0;
    float distance = 0;

    // Send trigger pulse
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Wait for echo start
    while (digitalRead(ECHO_PIN) == 0)
        start_time = micros(); // Saves the last known time of LOW pulse

    // Wait for echo end
    while (digitalRead(ECHO_PIN) == 1)
        end_time = micros(); // Saves the last known time of HIGH pulse

    // Get distance in cm
    distance = (end_time - start_time) / 29. / 2.;

    return (int)distance;
}

/**
 * DC Motor functions
 */
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