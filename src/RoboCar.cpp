#include "RoboCar.h"

RoboCar::RoboCar() {}

void RoboCar::init() {
    init(STRAIGHT);
}

void RoboCar::init(int servoCenter) {
    TCCR2B = TCCR2B & B11111000 | B00000111; // set PWM timer2 30.64Hz
    DDRB = 0;                                // Set pins of Port B (D8-13) as input IR sensor

    if (servoCenter>=MIN_ANGLE && servoCenter<=MAX_ANGLE) straight=servoCenter; else straight=STRAIGHT;

    pinMode(START_PIN, INPUT);

    pinMode(B_1A, OUTPUT);
    pinMode(B_1B, OUTPUT);
    digitalWrite(B_1A, LOW);
    digitalWrite(B_1B, LOW);

    myServo.attach(SERVO_PIN);
    myServo.write(straight);

    pinMode(LEFT_LED, OUTPUT);
    pinMode(RIGHT_LED, OUTPUT);
    digitalWrite(RIGHT_LED, LOW);
    digitalWrite(LEFT_LED, LOW);
    delay(256);
}


//---------------------------------------------- Motor
void RoboCar::halt() {
    digitalWrite(B_1A, LOW);
    digitalWrite(B_1B, LOW); delay(64);
}

void RoboCar::forward(int sp) {

    digitalWrite(B_1A, LOW);
    digitalWrite(B_1B, LOW); delay(32);

    if (sp>0 && sp<100) {
        int varPWM=map(sp, 1, 99, 21, 101);
        digitalWrite(B_1A,LOW);   // direction = forward
        analogWrite(B_1B,varPWM); // PWM Speed 21-min, 101-max
    }
}

void RoboCar::backward(int sp) {

    digitalWrite(B_1A, LOW);
    digitalWrite(B_1B, LOW); 
    delay(32);

    if (sp>0 && sp<100) {
        int varPWM=-map(sp, 1, 99, -232, -192);

        digitalWrite(B_1A,HIGH);  // direction = backward
        analogWrite(B_1B,varPWM); // PWM Speed  232-min, 192-max
      }
}

//---------------------------------------------- Servo
void RoboCar::center() {
    myServo.write(straight);
}

void RoboCar::left(int angle) {
    int actuator = constrain(straight-angle, straight-TURN_ANGLE, straight+TURN_ANGLE);
    myServo.write(actuator); 
}

void RoboCar::right(int angle) {
    int actuator = constrain(straight+angle, straight-TURN_ANGLE, straight+TURN_ANGLE);
    myServo.write(actuator); 
}

//---------------------------------------------- Light
void RoboCar::lightR(int state) {
    digitalWrite(RIGHT_LED, state);
}

void RoboCar::lightL(int state) {
    digitalWrite(LEFT_LED, state);
}

void RoboCar::lightAll(int state) {
    lightR(state);
    lightL(state);
}

void RoboCar::blinkL(int c, int d) {
    lightR(LOW); lightL(LOW);
    for(int i = 0; i < c; i++) {
        lightL(HIGH); delay(d);
        lightL(LOW);  delay(d);
    }
}

void RoboCar::blinkR(int c, int d) {
    lightR(LOW);
    lightL(LOW);
    for(int i = 0; i < c; i++) {
         lightR(HIGH); delay(d);
         lightR(LOW);  delay(d);
    }
}

void RoboCar::blinkAll(int c, int d) {
    lightR(LOW);
    lightL(LOW);
    for(int i = 0; i < c; i++) {
         lightR(HIGH); lightL(HIGH); delay(d);
         lightR(LOW);  lightL(LOW);  delay(d);
    }
}

//---------------------------------------------- Read sensors
int RoboCar::readStart(void) {
    return !digitalRead(START_PIN);
}

int RoboCar::readLine(void) {
    int sensors = PINB;
    return sensors & MASK;
}
