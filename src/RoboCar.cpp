#include "RoboCar.h"

RoboCar::RoboCar() {
  
}

void RoboCar::init() {
  DDRB = 0; // Set pins of Port B (D8-13) to input

  pinMode(B_1A, OUTPUT);
  pinMode(B_1B, OUTPUT);
  digitalWrite(B_1A, LOW);
  digitalWrite(B_1B, LOW);
  
  pinMode(START_PIN, INPUT);

  myServo.attach(SERVO_PIN);
  myServo.write(STRAIGHT);
  

  pinMode(LEFT_LED, OUTPUT);
  pinMode(RIGHT_LED, OUTPUT);
  digitalWrite(RIGHT_LED, LOW);
  digitalWrite(LEFT_LED, LOW);
  Serial.println("Init");
  delay(1000);
}

void RoboCar::forward(int sp) {
  if (sp < 0) {
    backward(-sp);
    return;
  } else if (sp == 0) {
      fullStop();
      return;
  } else {
      digitalWrite(B_1B, LOW);
      digitalWrite(B_1A, HIGH);
      if (sp < 100) {
        delay(EPD);
        analogWrite(B_1A, MIN_SPEED + sp);
      }
  }
}

void RoboCar::backward(int sp) {
  if (sp < 0) {
    forward(-sp);
    return;
  } else if (sp == 0) {
      fullStop();
      return;
  } else {
      digitalWrite(B_1B, HIGH);
      digitalWrite(B_1A, LOW);
      if (sp < 100) {
        delay(EPD);
        analogWrite(B_1B, MIN_SPEED + sp);
    }
  }
}

void RoboCar::fullStop() {
  Serial.println("Stop");
  digitalWrite(B_1A, LOW);
  digitalWrite(B_1B, LOW);
  delay(300);
}

int RoboCar::readLine(void) {
  Serial.println("Readline");
  return ~PINB & MASK;
}

void RoboCar::left(int angle) {
  int actuator = constrain(STRAIGHT - angle, -MAX_ANGLE, MAX_ANGLE);
  myServo.write(actuator);
}
void RoboCar::right(int angle) {
  int actuator = constrain(STRAIGHT + angle, -MAX_ANGLE, MAX_ANGLE);
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

void RoboCar::strait() {
  myServo.write(STRAIGHT);  

}

void RoboCar::lightR(int state) {
  digitalWrite(RIGHT_LED, state);
}

void RoboCar::lightL(int state) {
  digitalWrite(LEFT_LED, state);  
}
 
int RoboCar::startStop() {
  return digitalRead(START_PIN);
}

void RoboCar::blinkL(int c, int d) {
  for (int i = 0; i < c; i++) {
    lightL(HIGH);
    delay(d);
    lightL(LOW);
    delay(d);
  }
}

void RoboCar::blinkR(int c, int d) {
  for (int i = 0; i < c; i++) {
    lightR(HIGH);
    delay(d);
    lightR(LOW);
    delay(d);
  }
}

void RoboCar::blinkAll(int c, int d) {
  for (int i = 0; i < c; i++) {
    lightR(HIGH);
    lightL(HIGH);
    delay(d);
    lightR(LOW);
    lightL(LOW);
    delay(d);
  }
}



