int count=0;
char str[40];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sprintf(str, "$PRINT COUNT : %d \r\n", count++);
  Serial.print("$CLEAR\r\n");
  Serial.print("$GO 1 1\r\n");
  Serial.print("$PRINT PARK SANG MIN\r\n");
  Serial.print("$GO 2 1\r\n");
  Serial.print(str);
  Serial.print("$CURSOR 1 1\r \n");
  delay(1000);
}
