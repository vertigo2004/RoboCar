/*   
*/

#include <SPI.h>          // библиотека для работы с шиной SPI
#include "nRF24L01.h"     // библиотека радиомодуля
#include "RF24.h"         // ещё библиотека радиомодуля

#define BUTTON_PIN   7
#define FINISH_PIN1  6
#define FINISH_PIN2  5


#define SERIAL_START '1'
#define SERIAL_RESET '2'
#define SERIAL_STOP1 '3'
#define SERIAL_STOP2 '4'


RF24 radio(9, 10); // "создать" модуль на пинах 9 и 10 Для Уно
//RF24 radio(9,53); // для Меги

byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; //возможные номера труб

byte PAYLOAD = 84;
typedef enum { STANDBY, CLOCK } mode_e;
mode_e mode = STANDBY;

int isFinished1 = false;
int isFinished2 = false;

void setup() {
  Serial.begin(9600); //открываем порт для связи с ПК

  radio.begin(); //активировать модуль
  radio.setAutoAck(1);         //режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0, 15);    //(время между попыткой достучаться, число попыток)
  radio.enableAckPayload();    //разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);     //размер пакета, в байтах

  radio.openWritingPipe(address[0]);   //мы - труба 0, открываем канал для передачи данных
  radio.setChannel(0x60);  //выбираем канал (в котором нет шумов!)

  radio.setPALevel (RF24_PA_MAX); //уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_250KBPS); //скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  //должна быть одинакова на приёмнике и передатчике!
  //при самой низкой скорости имеем самую высокую чувствительность и дальность!!

  radio.powerUp(); //начать работу
  radio.stopListening();  //не слушаем радиоэфир, мы передатчик

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(FINISH_PIN1, INPUT);
  pinMode(FINISH_PIN2, INPUT);
  
}

void loop() {

  
  if (mode == STANDBY && Serial.available() && Serial.read() == SERIAL_START) {
      radio.write(&PAYLOAD, sizeof(PAYLOAD));
      mode = CLOCK;
  }
  
  if (mode == CLOCK) {
    if (!isFinished1 && digitalRead(FINISH_PIN1)) {
      isFinished1 = true;
      Serial.print(SERIAL_STOP1);
    }
    if (!isFinished2 && digitalRead(FINISH_PIN2)) {
      isFinished2 = true;
      Serial.print(SERIAL_STOP2);
    }
    
    if (isFinished1 && isFinished2 || Serial.available() && Serial.read() == SERIAL_RESET) {
      mode = STANDBY;
      isFinished1 = false;
      isFinished2 = false;
    }
  }

}
