#include "RoboCar.h"

RoboCar::RoboCar() {

}

void RoboCar::init() {
  init(STRAIGHT);
}

void RoboCar::init(int servoCenter) {

  straight = servoCenter;
  speed = 0;
  DDRB = 0; // Set pins of Port B (D8-13) to input

  pinMode(B_1A, OUTPUT);
  pinMode(B_1B, OUTPUT);
  digitalWrite(B_1A, LOW);
  digitalWrite(B_1B, LOW);

  pinMode(START_PIN, INPUT);

  myServo.attach(SERVO_PIN);
  myServo.write(straight);

  pinMode(LEFT_LED, OUTPUT);
  pinMode(RIGHT_LED, OUTPUT);
  digitalWrite(RIGHT_LED, LOW);
  digitalWrite(LEFT_LED, LOW);
  delay(1000);
}

void RoboCar::forward(int sp) {
  direction = 1;

//  digitalWrite(B_1A, LOW);
//  digitalWrite(B_1B, LOW);
  if (sp < 0) {
    backward(-sp);
    return;
  } else if (sp == 0) {
    fullStop();
    return;
  } else if (sp >= 100) {
    digitalWrite(B_1B, LOW);
    digitalWrite(B_1A, HIGH);
    speed = 100;
  } else {
    int actuator = kickStart(map(sp, 1, 99, MIN_SPEED, 254));
    digitalWrite( B_1A, HIGH ); // direction = forward
    analogWrite( B_1B, 255 - actuator ); // PWM Speed
    speed = sp;
  }
}

int RoboCar::kickStart(int a) {

  int turnKick = 0;
  if (speed == 0 && a < KS_LIMIT) {
    turnKick = abs(90 - myServo.read());
    if (direction > 0) {
      digitalWrite( B_1A, HIGH ); // direction = forward
      analogWrite( B_1B, 255 - KS_SPEED ); // PWM Speed
    }
    if (direction < 0) {
      digitalWrite( B_1A, LOW ); // direction = backward
      analogWrite( B_1B, KS_SPEED ); // PWM Speed
    }
    delay(KS_DELAY);
  }
  return a + turnKick;
}

void RoboCar::backward(int sp) {
  direction = -1;
  digitalWrite(B_1A, LOW);
  digitalWrite(B_1B, LOW);
  if (sp < 0) {
    forward(-sp);
    return;
  } else if (sp == 0) {
      fullStop();
      return;
  } else if (sp >= 100) {
      digitalWrite(B_1B, HIGH);
      digitalWrite(B_1A, LOW);
    speed = 100;
  } else {
    int actuator = kickStart(map(sp, 1, 99, MIN_SPEED, 254));
    digitalWrite( B_1A, LOW ); // direction = backward
    analogWrite( B_1B, actuator ); // PWM Speed
    speed = -sp;
  }
}

void RoboCar::fullStop() {
  direction = 0;
  speed = 0;
  digitalWrite(B_1A, LOW);
  digitalWrite(B_1B, LOW);
  delay(300);
}

int RoboCar::readLine(void) {
  int sensors = PINB;
  return ~sensors & MASK;
}

void RoboCar::left(int angle) {
  int actuator = constrain(straight - angle, -MAX_ANGLE, MAX_ANGLE);
  myServo.write(actuator);
}
void RoboCar::right(int angle) {
  int actuator = constrain(straight + angle, -MAX_ANGLE, MAX_ANGLE);
  myServo.write(actuator);
}

void RoboCar::toLeft(int angle) {
  int prev = myServo.read();
  int actuator = constrain(prev - angle, -MAX_ANGLE, MAX_ANGLE);
  myServo.write(actuator);
}

void RoboCar::toRight(int angle) {
  int prev = myServo.read();
  int actuator = constrain(prev + angle, -MAX_ANGLE, MAX_ANGLE);
  myServo.write(actuator);
}

void RoboCar::center() {
  myServo.write(straight);
}

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

int RoboCar::readStart() {
  return !digitalRead(START_PIN);
}

void RoboCar::blinkL(int c, int d) {
    lightR(LOW);
    lightL(LOW);
  for (int i = 0; i < c; i++) {
    lightL(HIGH);
    delay(d);
    lightL(LOW);
    delay(d);
  }
}

void RoboCar::blinkR(int c, int d) {
    lightR(LOW);
    lightL(LOW);
  for (int i = 0; i < c; i++) {
    lightR(HIGH);
    delay(d);
    lightR(LOW);
    delay(d);
  }
}

void RoboCar::blinkAll(int c, int d) {
    lightR(LOW);
    lightL(LOW);
  for (int i = 0; i < c; i++) {
    lightR(HIGH);
    lightL(HIGH);
    delay(d);
    lightR(LOW);
    lightL(LOW);
    delay(d);
  }
}



