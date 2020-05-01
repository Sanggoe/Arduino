#include <DHT.h>
#define DHTPIN 2 // 디지털 1번핀 사용
#define DHTTYPE DHT11 // DHT 11 모델 사용
DHT dht(DHTPIN, DHTTYPE);

char str[40];

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();//습도 읽기
  float t = dht.readTemperature();// 온도 읽기

//  Serial.print("습도: ");
//  Serial.print(h, 1);
//  Serial.print("%, 온도: ");
//  Serial.print(t, 1);
//  Serial.println("도");
  int tmp = (int)t;
  sprintf(str, "$PRINT Tmp: %d'C\r\n", tmp);
  Serial.print("$CLEAR\r\n");
  Serial.print("$GO 1 1\r\n");
  Serial.print(str);
  Serial.print("$CURSOR 1 1\r \n");
  delay(1000);

}
