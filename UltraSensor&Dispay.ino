#include "TM1637.h"

#define CLK 3
#define DIO 2

TM1637 tm1637(CLK, DIO);

// Ultra Sensor

#define PIN_TRIG 7
#define PIN_ECHO 5

long duration, cm;

void setup(){
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  Serial.begin(9600);

  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);
}

void loop(){
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH);
  
  // Выставив высокий уровень сигнала, ждем около 10 микросекунд. В этот момент датчик будет посылать сигналы с частотой 40 КГц.
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  
  //  Время задержки акустического сигнала на эхолокаторе.
  duration = pulseIn(PIN_ECHO, HIGH);
  
  // Теперь осталось преобразовать время в расстояние
  cm = (duration / 2) / 29;
  
  // Display

  char c1 = 0;
  char c2 = 0;
  char c3 = 0;

  if(cm >= 100){
    c1 = cm / 100;
    c2 = cm % 100 / 10;
    c3 = cm % 100 % 10;
  } else {
    c1 = cm / 10;
    c2 = cm % 10;
    c3 = 'c';
  }

  int8_t DispMSG[] = {c1, c2, c3, 'c'};

  Serial.println(cm);
 
  tm1637.point(false);

  tm1637.display(DispMSG);

  delay(1000);
}
