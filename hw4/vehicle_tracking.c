/**
 * Improved version of vehicle tracking & keep distance
 */
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define TRIG_PIN 28
#define ECHO_PIN 29

#define IN1_PIN 1
#define IN2_PIN 4
#define IN3_PIN 5
#define IN4_PIN 6

#define MAX_SPEED 100
#define LOW_SPEED 30
#define MIN_SPEED 0
#define NORMAL_SPEED 65
#define NORMAL_DISTANCE 50

void initUltrasonic();
void initDCMotor();
void goForward(int);
void stopDCMotor();
int getDistance();
void runTheCar(int);
int min(int, int);
int max(int, int);

int main(void)
{
    if (wiringPiSetup() == -1)
        return 0;

    int distance = 0;

    // Init
    initUltrasonic();
    initDCMotor();

    // stopDCMotor();
    // return 0;

    // Go forward
    goForward(50);

    while (1)
    {
        distance = getDistance();
        printf("distance %dcm\n", distance);

        runTheCar(distance);

        delay(100);
    }

    // Stop the Car
    stopDCMotor();
    return 0;
}

void runTheCar(int distance)
{
    // Stop the car
    if (distance < 20)
        stopDCMotor();

    // Slow down
    else if (distance >= 20 && distance < 45)
        goForward(distance * 1.5); // map distance [20, 45] to speed [30, 65]

    // Normal speed
    else if (distance >= 45 && distance < 55)
        goForward(NORMAL_SPEED);

    // Go faster
    else
        goForward(distance * 1.2); // map distance >= 55 to speed [65, 100]
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

void goForward(int speed)
{
    // Limit the speed between LOW_SPEED/MAX_SPEED
    speed = min(max(speed, LOW_SPEED), MAX_SPEED);

    softPwmWrite(IN1_PIN, speed);
    softPwmWrite(IN2_PIN, MIN_SPEED);
    softPwmWrite(IN3_PIN, speed);
    softPwmWrite(IN4_PIN, MIN_SPEED);
    printf("Forward with speed %d\n", speed);
}

void stopDCMotor()
{
    softPwmWrite(IN1_PIN, LOW);
    softPwmWrite(IN2_PIN, LOW);
    softPwmWrite(IN3_PIN, LOW);
    softPwmWrite(IN4_PIN, LOW);
    printf("Stop\n");
}

int min(int x, int y)
{
    return (x < y) ? x : y;
}

int max(int x, int y)
{
    return (x > y) ? x : y;
}