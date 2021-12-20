#include <ESP8266WiFi.h>
// Sustituir con datos de vuestra red
const char* ssid     = "rola9294";
const char* password = "ROMO1951"; 

#define red 12
#define green 14
void setup()
{
  pinMode(red,OUTPUT); //"please STAND BY" for connection status indicator 
  pinMode(green,OUTPUT); // ESP8266 Connected!
  Serial.begin(115200); //or you can also use 9600
  delay(10);
  
  WiFi.mode(WIFI_STA); //wifi command
  WiFi.begin(ssid, password); //wifi command
  Serial.print("Conectando a:\t");
  Serial.println(ssid); 
  // Esperar a que nos conectemos
  while (WiFi.status() != WL_CONNECTED) //wifi 
  {
    delay(200); 
    Serial.print('.');
  }
  // Mostrar mensaje de exito y dirección IP asignada
  Serial.println();
  Serial.print("Conectado a:\t");
  Serial.println(WiFi.SSID()); 
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
}
void loop() 
{
 if(WiFi.status() == true)
 {
  digitalWrite(green,HIGH);
  digitalWrite(red,LOW);
  }
  else
  {
    digitalWrite(red,HIGH);
    digitalWrite(green,LOW);
    }
 }
