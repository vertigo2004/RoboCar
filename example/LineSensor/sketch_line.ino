#include <RoboCar.h>

RoboCar myCar; // Створити об'єкт RoboCar для керування авто-роботом

int sLine=0;   // Оголосити змінну для збереження даних сенсора лінії

void setup() {
     Serial.begin(9600); // Ініціалізація послідовного порта
     myCar.init();       // Ініціалізація задіяних вивводів Arduino Nano та задання кута
}                        // центрального положення передніх коліс за замовчуванням

void loop() {
     sLine=myCar.readLine(); // Зчитати у змінну sLine поточний стан сенсора лінії
     Serial.print(sLine);    // Вивести зчитане значення через послідовний порт в десятковому та двійковому форматі
     Serial.print(" ");
     Serial.println(sLine, BIN);
     delay(256);
}
