

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
char auth[] = "0UAyLTeeDOp2OWWD1E8UrjPRkcwXF-YI"; //"nduCDv3Rp3Xl0TKOtg9KKfojEB2qfqiA"; //nyambung blynk di hp dawud    //"0UAyLTeeDOp2OWWD1E8UrjPRkcwXF-YI"; //nyambung blynk di memu
char ssid[] = "3";
char pass[] = "00000000";

//autentikasi melalui wifi(hanya untuk wifi-check)
//samakan aja sama yang atas
const char* ssid1     = "3";         
const char* password1 = "00000000";     


//definisikan dht
#define DHTPIN D3          
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



void setup() {
 //wifi-check
  Serial.begin(9600);         
  delay(10);
  Serial.println('\n'); 
  WiFi.begin(ssid1, password1);             
  Serial.print("Connecting to ");
  Serial.print(ssid1); Serial.println(" ...");
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { 
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }
  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());        
  

  //group3-project
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
  lcd.print("touched by fu");
  lcd.setCursor(0,1);
  lcd.print("speed :");
  lcd.print(velocity);
  lcd.print(" RPM");
  delay(1000);
}
