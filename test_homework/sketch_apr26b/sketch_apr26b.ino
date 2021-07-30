#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
    lcd.begin(16, 2);
    lcd.print("Park sangmin");
}

void loop() {
  
  for(int position=0; position<16; position++) {
    lcd.scrollDisplayLeft();
    delay(150);
  }
}
