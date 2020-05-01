/*  DHT11 온습도 센서 값을 읽어 시리얼 모니터 창으로 나타내기 */
#include <DHT.h>  // DHT.h 헤더파일을 라이브러리에 추가 한다
#define DHTPIN 2  // 온·습도 데이터 핀 설정
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#include <LiquidCrystal.h>

void setup() {
  Serial.begin(9600);
}
void loop() {
  delay(2000);                      // 센싱을 위한 시간 지연 값을 준다.
  
  Serial.print("Humidity (%): ");
  Serial.println(dht.readHumidity());
  
  Serial.print("Temperature (C): ");
  Serial.println(dht.readTemperature());
}
