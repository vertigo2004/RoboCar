#include "RoboCar.h"


RoboCar myCar;

int oldState = 0;
int state = 0;


void setup() {
  Serial.begin(9600);
  myCar.init();
//  myCar.strait();
Serial.println(MIN_PULSE_WIDTH);
Serial.println(MAX_PULSE_WIDTH);
}

String s;
int a = 30;

void loop() {

    state = (state + 1) % 4;    
    Serial.println(state%4);
    switch (state % 4) {
      case 0:
        myCar.lightL(HIGH);
        myCar.lightR(HIGH);
        myCar.strait();

        break;

      case 1:
        myCar.lightL(HIGH);
        myCar.lightR(LOW);
        myCar.left(a);
                blinkL(300);
        break;
    
      case 2:
        myCar.lightL(HIGH);
        myCar.lightR(HIGH);
        myCar.strait();
        break;
        
      case 3:
        myCar.lightR(HIGH);
        myCar.lightL(LOW);        
        myCar.right(a);
        break;
    }
    delay(1000);
 // for (int i=1;i<1000000;i++);

}

void blinkL(int d) {
  for (int i = 0; i < 3; i++) {
    myCar.lightL(HIGH);
    delay(d);
    myCar.lightL(LOW);
    delay(d);
  }
  
  myCar.lightL(HIGH);
}



