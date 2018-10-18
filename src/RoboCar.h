#ifndef RoboCar_h
#define RoboCar_h

#include <Arduino.h>
#include <Servo.h>

#define MASK 0x0F

// ARDUINO PINS
#define START_PIN 2
#define SERVO_PIN 3
#define B_1A 5
#define B_1B 6
#define RIGHT_LED 12
#define LEFT_LED 13
// Line sensors are on pins 8-11

// Stearing wheel control (Servo)
#define STRAIGHT 90
#define MAX_ANGLE 115
#define MIN_ANGLE 75

#define KS_DELAY 50 // KickStart DELAY
#define KS_LIMIT 100
#define KS_SPEED 200
#define MIN_SPEED 70 // ENGINE MINIMUM SPEED PWM IMPULSE

// LINE LED SENSOR VALUES
#define NO_LINE 0
#define CENTER 6
#define LEFT1 4
#define LEFT2 12
#define LEFT3 8
#define RIGHT1 2
#define RIGHT2 3
#define RIGHT3 1
#define ALL_LINE 15

class RoboCar 
{
  public:
    RoboCar();
    void init(int center);
    void init();
    void forward(int);
    void backward(int);
    void fullStop(void);
    void left(int);
    void right(int);
    void toLeft(int);
    void toRight(int);
    void center();
    void lightL(int);
    void lightR(int);
    void lightAll(int);
    void blinkL(int, int);
    void blinkR(int, int);
    void blinkAll(int, int);
    int readStart();
    int readLine(void);

  private:
     int straight = STRAIGHT;
     int direction = 0;
     int speed = 0;
     Servo myServo;
     int kickStart(int);
};

#endif
