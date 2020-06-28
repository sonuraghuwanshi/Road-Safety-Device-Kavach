#include <SoftwareSerial.h>
#include "TFMini.h"
#include <LiquidCrystal.h>
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

SoftwareSerial mySerial(10, 11);
TFMini tfmini;
int sensorPin = A0;
int sensorValue=0;

void setup() 
{
  lcd.begin(16, 2);
  Serial.begin(115200);
  while (!Serial);     
  Serial.println ("Initializing...");
  mySerial.begin(TFMINI_BAUDRATE);
  tfmini.begin(&mySerial); 
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);   
}
void loop() 
{
  //lidar module
  uint16_t dist = tfmini.getDistance();
  Serial.print(dist);
  Serial.print(" cm \n");
  if(dist<75)
  {
    lcd.setCursor(0,1);
    lcd.print("Don't Overtake");
  }
  else
  {
    lcd.setCursor(0,1);
    lcd.print("Overtake           ");
  }
  
  // ldr module
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  if(sensorValue<500)
  {
    digitalWrite(9,LOW);
    digitalWrite(8,HIGH);
  }
  else
  {
    digitalWrite(8,LOW);
    digitalWrite(9,HIGH);
  }
}
