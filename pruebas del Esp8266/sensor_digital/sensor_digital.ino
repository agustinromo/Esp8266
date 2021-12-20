ADC_MODE(ADC_VCC);

#include <ESP8266WiFi.h>
int pin = 2;
void setup()
{
  //pinMode(opto,INPUT); 
  Serial.begin(115200);
  }
  void loop()
  {
    if(digitalRead(pin)==HIGH)
    {
      Serial.println("OK");
      delay(850);
      }
      else
      {
        Serial.println("NADA");
        delay(850);
        }
    }
  
