/*   Данный скетч делает следующее: передатчик (TX) отправляет массив
 *   данных, который генерируется согласно показаниям с кнопки и с 
 *   двух потенциомтеров. Приёмник (RX) получает массив, и записывает
 *   данные на реле, сервомашинку и генерирует ШИМ сигнал на транзистор.
    by AlexGyver 2016
*/

#include <SPI.h>          // библиотека для работы с шиной SPI
#include "nRF24L01.h"     // библиотека радиомодуля
#include "RF24.h"         // ещё библиотека радиомодуля

#define BUTTON_PIN  7
#define FINISH_PIN1  6
#define FINISH_PIN2  5


#define SERIAL_START 1
#define SERIAL_RESET 2
#define SERIAL_STOP1 3
#define SERIAL_STOP2 4



RF24 radio(9, 10); // "создать" модуль на пинах 9 и 10 Для Уно
//RF24 radio(9,53); // для Меги

byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; //возможные номера труб

byte PAYLOAD = 84;
typedef enum { STANDBY, CLOCK } mode_e;
mode_e mode = STANDBY;

long startTime;
long trackTime1 = 0;
long trackTime2 = 0;

int track1 = 0;
int track2 = 0;

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

  Serial.println("READY TO RACE!");
}

void loop() {
  if (mode == STANDBY && !digitalRead(BUTTON_PIN)) {
      radio.write(&PAYLOAD, sizeof(PAYLOAD));
      startTime = millis();
      mode = CLOCK;
      Serial.println("START!");
      delay(1000);
  }
  if (mode == CLOCK) {
    if (!track1 && digitalRead(FINISH_PIN1)) {
      trackTime1 = millis() - startTime;
      track1 = 1;
      Serial.print("First Track Time:");
      Serial.println(trackTime1 / 1000.);
    }
    if (!track2 && digitalRead(FINISH_PIN2)) {
      track2 = 1;
      trackTime2 = millis() - startTime;
      Serial.print("Second Track Time:");
      Serial.println(trackTime2 / 1000.);
    }
    if (track1 && track2) {
      mode = STANDBY;
      track1 = 0;
      track2 = 0;
      Serial.print("Race is OVER!");
      Serial.print("The winner is Track #");
      if (trackTime1 < trackTime2) {
        Serial.println("ONE!");
      } else {
        Serial.println("TWO!");
      }
      Serial.println("\r\n");
      Serial.println("READY TO RACE!");
    }
  }

}
