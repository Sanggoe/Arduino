int Thermistor = A0;
void setup()
{
    Serial.begin(9600);
}

void loop() 
{
  int val = analogRead(Thermistor);
  float volt = val*5.0/2014.0;
  float RES = ((50000)/volt) - 10000;
  float kT = 1/((1/(273.15 + 25)) + (1/4200.0) * log(RES/10000));
  float cT = kT - 273.15;

  Serial.print("Temp: ");
  Serial.print(-cT);
  Serial.println();
  delay(500);
}
