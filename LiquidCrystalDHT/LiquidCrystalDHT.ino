 #include <LiquidCrystal_I2C.h>
 #include "DHT.h"

 #define DHTPIN D4
 #define DHTTYPE DHT11

 DHT dht(DHTPIN, DHTTYPE);
 LiquidCrystal_I2C lcd(0x3f,16,2);

 void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();
  lcd.init();
 }

void loop() 
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("TEMP: ");
  lcd.print(t,DEC);
  lcd.setCursor(0,1);
  lcd.print("HUMIDITY: ");
  lcd.print(h,DEC);
  delay(1000);
}
