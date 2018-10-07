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
#define STRAIGHT 83
#define MAX_ANGLE 115
#define MIN_ANGLE 75

#define EPD 30 // ENGINE PUSH DELAY
#define MIN_SPEED 135 // ENGINE MINIMUM SPEED IMPULS

// LINE LED SENSOR VALUES
#define NO_LINE 0
#define CENTER 6
#define LEFT1 2
#define LEFT2 3
#define LEFT3 1
#define RIGHT1 4
#define RIGHT2 12
#define RIGHT3 8

class RoboCar 
{
  public:
    RoboCar();
    void init();
    void forward(int);
    void backward(int);
    void fullStop(void);
    int readLine(void);
    void left(int);
    void right(int);
    void toLeft(int);
    void toRight(int);
    void strait();
    void lightL(int);
    void lightR(int);
    void blinkL(int, int);
    void blinkR(int, int);
    void blinkAll(int, int);
    int startStop();

  private:
     Servo myServo;
};

#endif
