#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);


// the setup function runs once when you press reset or power the board
void setup() {
  lcd.begin(16,2);
  lcd.print("DO HYEON WOO");
}

// the loop function runs over and over again forever
void loop() {
  for(int position=0; position<16; position++){
    lcd.scrollDisplayLeft();
    delay(150);
  }
}
