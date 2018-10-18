#include <RoboCar.h>

RoboCar car;

void setup() {
  car.init();
}

void loop() {
  
  a = car.readLine();
  
  switch(a) {
    case CENTER:
      car.lightAll(HIGH);
    break;

    case NO_LINE:
      car.lightAll(LOW);
    break;

    case ALL_LINE:
      car.blinkAll(2, 500);
    break;
    
    case LEFT1:
      car.lightAll(LOW);
      car.blinkL(3,300);
    break;
    case LEFT2:
      car.lightAll(LOW);
      car.blinkL(4,200);
    break;
    case LEFT3:
      car.blinkL(5,100);
    break;
    
    case RIGHT1:
      car.blinkR(3,300);
    break;
    case RIGHT2:
      car.blinkR(4,200);
    break;
    case RIGHT3:
      car.blinkR(5,100);
    break;
  }
}


