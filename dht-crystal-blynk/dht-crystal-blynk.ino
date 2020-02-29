
//Project Kelompok 3

//import library yang mau dugunakan
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#include <SPI.h>

//definisikan spesifikasi lcd yang digunakan 
LiquidCrystal_I2C lcd(0x3f,16,2);

//autentikasi melalui wifi
char auth[] = "nduCDv3Rp3Xl0TKOtg9KKfojEB2qfqiA";
char ssid[] = "3";
char pass[] = "00000000";

//definisikan dht
#define DHTPIN D7          
#define DHTTYPE DHT11 
#define BLYNK_PRINT Serial
DHT dht(DHTPIN, DHTTYPE);
    
//definisikan variable umum
int velocity = 0;

//kasih output ke virtualPin 4 (V4) dan D5
BLYNK_WRITE(V4) {
  int val = param.asInt();
  analogWrite(D5, val);
  velocity = val;
 } 

BlynkTimer timer;


void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);

}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  lcd.init();
  dht.begin();
  pinMode(D5, OUTPUT);
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();  
  timer.run();
    
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("KELOMPOK 3 ");
  lcd.setCursor(0,1);
  lcd.print("motor :");
  lcd.print(velocity);
  lcd.print(" RPM");
  delay(1000);
}
