// библиотека для работы программного Serial
#include <SoftwareSerial.h>
     
// создаём объект для работы с программным Serial
// и передаём ему пины TX и RX
SoftwareSerial mySerial(8, 9);
     
// serial-порт к которому подключён Wi-Fi модуль
#define WIFI_SERIAL    mySerial

int const temperature = A0;
int const gas = A1;
int LED_GREEN = 4;
int LED_ORANGE = 3;
int LED_RED = 2;
     
void setup()
{
  // открываем последовательный порт для мониторинга действий в программе
  // и передаём скорость 9600 бод
  Serial.begin(9600);
  while (!Serial) {
  // ждём, пока не откроется монитор последовательного порта
  // для того, чтобы отследить все события в программе
  }
  Serial.print("Serial init OK\r\n");
  // открываем Serial-соединение с Wi-Fi модулем на скорости 115200 бод
  WIFI_SERIAL.begin(115200);
  
  pinMode(gas, INPUT);
  pinMode(temperature, INPUT);
  // порты лампочек
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_ORANGE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
}
     
void loop()
{
  // если приходят данные из Wi-Fi модуля - отправим их в порт компьютера
  if (WIFI_SERIAL.available()) {
  	Serial.write(WIFI_SERIAL.read());
  }
  // если приходят данные из компьютера - отправим их в Wi-Fi модуль
  if (Serial.available()) {
  	WIFI_SERIAL.write(Serial.read());
  }
      
  //датчик температуры
  float voltage = (analogRead(temperature)*5.0)/1024.0;
  //Serial.print("Voltage: ");
  //Serial.println(voltage);
  float C = (voltage - 0.5)*100.0;
  //Serial.print("C: ");
  //Serial.println(C);
  //float F = (C*9.0)/5.0 + 32;
  //Serial.print("F: ");
  //Serial.println(F);
      
  //датчик газа
  
  int co = analogRead(gas);
  co = map(co, 300, 750, 0, 100);
  //Serial.print("gas: ");
  //Serial.println(co);
  //лампочки    
  if(co > 70 && C <= 26.0 && C > 18.0){
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_ORANGE, LOW);
    Serial.println("Okay");
  }
  else if(co > 40 && co <= 70 && co >= 30 && C <= 26.0 && C > 20.0){
    digitalWrite(LED_ORANGE, HIGH);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);
    Serial.print("gas: ");
    Serial.println(co);
  }
  else if(co > 70 && C <= 30.0 && C > 26.0){
    digitalWrite(LED_ORANGE, HIGH);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);
    Serial.print("temperature(C): ");
    Serial.println(C);
  }
  else if(co > 70 && C <= 20.0 && C > 18.0){
    digitalWrite(LED_ORANGE, HIGH);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);
    Serial.print("temperature(C): ");
    Serial.println(C);
  }
  else if(co <= 40 && C <= 26.0 && C > 20.0){
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_ORANGE, LOW);
    Serial.print("gas: ");
    Serial.println(co);
  }
  else if(co > 70 && C > 30.0){
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_ORANGE, LOW);
    Serial.print("temperature(C): ");
    Serial.println(C);
  }
  else if(co > 70 && C <= 18){
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_ORANGE, LOW);
    Serial.print("temperature(C): ");
    Serial.println(C);
  }
  
  delay(250);
}

