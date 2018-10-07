#include <RoboCar.h>

RoboCar myCar;

void setup() {
  myCar.init();
}

void loop() {

  fbTest(1, 3000);
  myCar.blinkAll(3, 300);

  fbTest(100, 3000);
  myCar.blinkAll(3, 300);

  myCar.left(30);
  myCar.lightL(HIGH);
  myCar.lightR(LOW);
  fbTest(50, 2000);
  
  myCar.right(30);
  myCar.lightR(HIGH);
  myCar.lightL(LOW);
  fbTest(50, 2000);

  myCar.blinkL(5,100);
  myCar.forward(20);
  myCar.left(10);
  delay(500);
  myCar.forward(60);
  myCar.left(20);
  delay(500);
  myCar.forward(80);
  myCar.left(30);
  delay(500);

  myCar.fullStop();

  myCar.blinkR(5,100);
  myCar.backward(20);
  myCar.right(10);
  delay(500);
  myCar.backward(60);
  myCar.right(20);
  delay(500);
  myCar.backward(80);
  myCar.right(30);
  delay(500);

  myCar.fullStop();
  
  myCar.strait();
  delay(500);
}


void fbTest(int speed, int time) {
  myCar.forward(speed);
  delay(time);
  
  myCar.fullStop();
   
  myCar.backward(speed);
  delay(time);  
  
  myCar.fullStop();
}

