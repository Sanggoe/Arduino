void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("$CLEAR\r\n");
  Serial.print("$GO 1 1\r\n");
  Serial.print("$PRINT 2016301035\r\n");
  Serial.print("$GO 2 1\r\n");
  Serial.print("$PRINT PARK SANG MIN\r\n");
  Serial.print("$CURSOR 1 1\r \n");
  delay(1000);
}
