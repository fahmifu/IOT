
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f,16,2);

void setup() {
  // put your setup code here, to run once:
  lcd.init()
}

void loop() {
  // put your main code here, to run repeatedly:
lcd.clear();
lcd.backlight();
lcd.setCursor(0,0);
lcd.print("Assalamualaikum");
lcd.setCursor(0,1);
lcd.print("from IOT dev");
delay(5000);
}
