#include <RoboCar.h>

RoboCar myCar; // Створити об'єкт RoboCar для керування авто-роботом

void setup() {
     myCar.init(); // Ініціалізація задіяних вивводів Arduino Nano та задання кута
}                  // центрального положення передніх коліс за замовчуванням

void loop() {
     myCar.lightR(HIGH); // Увімкнути ПРАВУ фару
     delay(2000);
     myCar.lightR(LOW);  // Вимкнути ПРАВУ фару
     delay(2000);

     myCar.lightL(HIGH); // Увімкнути ЛІВУ фару
     delay(2000);
     myCar.lightL(LOW);  // Вимкнути ЛІВУ фару
     delay(2000);

     myCar.lightAll(HIGH);  // Увімкнути обидві фари
     delay(2000);
     myCar.lightAll(LOW);   // Вимкнути обидві фари
     delay(2000);

     myCar.blinkR(8,128);   // Проблимати ПРАВОЮ фарою 8 раз з інтевалом 128 мілісекунд
     delay(2000);
     myCar.blinkL(8,128);   // Проблимати ЛІВОЮ фарою 8 раз з інтевалом 128 мілісекунд
     delay(2000);
     myCar.blinkAll(8,128); // Проблимати обома фарами 8 раз з інтевалом 128 мілісекунд
     delay(2000);
}
