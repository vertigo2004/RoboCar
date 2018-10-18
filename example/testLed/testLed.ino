#include <RoboCar.h>

RoboCar car;

void setup() {
  car.init(84);
}

int state = 0;
int a = 0;
int prev = 0;

void loop() {
  a = car.readStart();
  
  if (a && prev != a) {
    //car.lightAll(HIGH);
    switch(state) {
      case 0:
        car.blinkL(4, 100);
        break;
      case 1:
        car.blinkR(4, 100);
        break;
      case 2:
        car.blinkAll(4, 100);
        break;
    }
    state = (state+1) % 3;
  } else {
    car.lightAll(LOW);
  }
  prev = a;
}


