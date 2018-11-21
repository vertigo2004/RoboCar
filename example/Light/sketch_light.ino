#include <RoboCar.h>

RoboCar myCar; // �������� ��'��� RoboCar ��� ��������� ����-�������

void setup() {
     myCar.init(); // ����������� ������� ������� Arduino Nano �� ������� ����
}                  // ������������ ��������� ������� ���� �� �������������

void loop() {
     myCar.lightR(HIGH); // �������� ����� ����
     delay(2000);
     myCar.lightR(LOW);  // �������� ����� ����
     delay(2000);

     myCar.lightL(HIGH); // �������� ˲�� ����
     delay(2000);
     myCar.lightL(LOW);  // �������� ˲�� ����
     delay(2000);

     myCar.lightAll(HIGH);  // �������� ����� ����
     delay(2000);
     myCar.lightAll(LOW);   // �������� ����� ����
     delay(2000);

     myCar.blinkR(8,128);   // ���������� ������ ����� 8 ��� � ��������� 128 ��������
     delay(2000);
     myCar.blinkL(8,128);   // ���������� ˲��� ����� 8 ��� � ��������� 128 ��������
     delay(2000);
     myCar.blinkAll(8,128); // ���������� ����� ������ 8 ��� � ��������� 128 ��������
     delay(2000);
}
