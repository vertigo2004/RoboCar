#include <RoboCar.h>

RoboCar myCar; // �������� ��'��� RoboCar ��� ��������� ����-�������

int sLine=0;   // ��������� ����� ��� ���������� ����� ������� ��

void setup() {
     Serial.begin(9600); // ����������� ����������� �����
     myCar.init();       // ����������� ������� ������� Arduino Nano �� ������� ����
}                        // ������������ ��������� ������� ���� �� �������������

void loop() {
     sLine=myCar.readLine(); // ������� � ����� sLine �������� ���� ������� ��
     Serial.print(sLine);    // ������� ������� �������� ����� ���������� ���� � ����������� �� ��������� ������
     Serial.print(" ");
     Serial.println(sLine, BIN);
     delay(256);
}
