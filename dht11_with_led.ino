#include "DHT.h" 
#include "TM1637.h"
 
#define DHTPIN 8
#define CLK 11
#define DIO 13  
  
// задаем тип подключаемого датчика
#define DHTTYPE DHT11   
 
// обьявляем обьект dht с параметрами
DHT dht(DHTPIN, DHTTYPE);
TM1637 tm1637(CLK, DIO);
 
void setup() {
  Serial.begin(9600);
  tm1637.init();
  /*
     BRIGHT_TYPICAL = 2 Средний
     BRIGHT_DARKEST = 0 Тёмный
     BRIGHTEST = 7      Яркий
  */
  tm1637.set(BRIGHT_TYPICAL);
  dht.begin(); // запускаем датчик
}
 
void loop() {

  int h = dht.readHumidity(); 
  int t = dht.readTemperature();

  char t1 = t / 10;
  char t2 = t % 10;
  
  char h1 = h / 10;
  char h2 = h % 10;

  int8_t DispMSG[] = {t1, t2, h1, h2};
 
  tm1637.point(true);

  tm1637.display(DispMSG);

  delay(10000);
}
