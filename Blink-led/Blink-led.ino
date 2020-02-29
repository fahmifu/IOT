
//1st project 

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, LOW);   

  delay(1000);                      
  digitalWrite(LED_BUILTIN, HIGH);  
  delay(2000);                      
}
