/**
 * Capstone Design HW #3
 * Team Name: Turin
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

void initDCMotor();
void goForward();
void goBackward();
void goLeft();
void goRight();
void stopDCMotor();
void smoothLeft();
void smoothRight();
void moveTheCar();

int cntr = 1;

int main(void)
{
	if (wiringPiSetup() == -1)
		return 0;

	pinMode(IN1_PIN, OUTPUT);
	pinMode(IN2_PIN, OUTPUT);
	pinMode(IN3_PIN, OUTPUT);
	pinMode(IN4_PIN, OUTPUT);
	initDCMotor();

	moveTheCar();

	stopDCMotor();
	return 0;
}

void moveTheCar()
{
	// Go forward for 2 sec.
	goForward();
	delay(2000);

	// Turn left
	goLeft();
	delay(950);

	// and go forward for 2 sec
	goForward();
	delay(2000);

	// and stop
	stopDCMotor();
	delay(500);

	// Go back for 2 sec
	goBackward();
	delay(2000);

	// Turn right and go forward for 2 sec and stop
	goRight();
	delay(800);

	goForward();
	delay(2000);

	stopDCMotor();
	delay(500);

	// Go forward for 2 sec then make left point turn and stop
	goForward();
	delay(2000);

	goLeft();
	delay(3600);

	stopDCMotor();
	delay(500);

	// Go back for 2 sec then make right smooth turn and stop
	goBackward();
	delay(2000);

	smoothRight();
	delay(2000);

	stopDCMotor();
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

void goBackward()
{
	digitalWrite(IN1_PIN, LOW);
	digitalWrite(IN2_PIN, HIGH);
	digitalWrite(IN3_PIN, LOW);
	digitalWrite(IN4_PIN, HIGH);
	printf("Backward\n");
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

void stopDCMotor()
{
	digitalWrite(IN1_PIN, LOW);
	digitalWrite(IN2_PIN, LOW);
	digitalWrite(IN3_PIN, LOW);
	digitalWrite(IN4_PIN, LOW);
	printf("Stop\n");
}

void smoothLeft()
{
	softPwmWrite(IN1_PIN, MAX_SPEED / 8);
	softPwmWrite(IN4_PIN, MIN_SPEED);
	softPwmWrite(IN3_PIN, MAX_SPEED);
	softPwmWrite(IN4_PIN, MIN_SPEED);
	printf("Smooth Left\n");
}

void smoothRight()
{
	softPwmWrite(IN1_PIN, MAX_SPEED);
	softPwmWrite(IN4_PIN, MIN_SPEED);
	softPwmWrite(IN3_PIN, MAX_SPEED / 8);
	softPwmWrite(IN4_PIN, MIN_SPEED);
	printf("Smooth Right\n");
}
