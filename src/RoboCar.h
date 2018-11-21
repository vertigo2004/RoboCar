#ifndef RoboCar_h
#define RoboCar_h

#include <Arduino.h>
#include <Servo.h>

#define MASK 0x0F

// Arduino NANO pins
#define RIGHT_LED 12
#define LEFT_LED 13
#define START_PIN 2
#define SERVO_PIN 5
#define B_1A 4
#define B_1B 3
// Line IR sensors are on pins 8, 9, 10, 11

// Stearing wheel control (Servo)
#define MAX_ANGLE 120
#define MIN_ANGLE 70
#define STRAIGHT 90
#define TURN_ANGLE 24

// Line IR sensor values
#define NO_LINE 0
#define CENTER 6
#define LEFT1 4
#define LEFT2 12
#define LEFT3 8
#define RIGHT1 2
#define RIGHT2 3
#define RIGHT3 1
#define ALL_LINE 15

class RoboCar {
    public:
        RoboCar();
        void init(int);
        void init();
        void halt(void);
        void forward(int);
        void backward(int);
        void center(void);
        void left(int);
        void right(int);
        void lightL(int);
        void lightR(int);
        void lightAll(int);
        void blinkL(int, int);
        void blinkR(int, int);
        void blinkAll(int, int);
        int readStart(void);
        int readLine(void);

    private:
        int straight = STRAIGHT;
        Servo myServo;
};
#endif
