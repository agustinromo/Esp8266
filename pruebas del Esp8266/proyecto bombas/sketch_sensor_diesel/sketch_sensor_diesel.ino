#include <ESP8266WiFi.h>

const char* ssid     = "TS_RRHH";
const char* password = "TsAdmin2020"; 
const char* host = "controlcombustible.com.mx"; /***/
//indicator leds
#define red 12 //D6
#define green 14 //D5
//sensor components
#define Trigger 5 //D1 
#define Echo 4 //D2

long t;
long d; 

void setup()
{
  pinMode(red,OUTPUT); //"please STAND BY" for connection status indicator 
  pinMode(green,OUTPUT); // ESP8266 Connected!
   //pinMode(Echo,INPUT);
  pinMode(Trigger,OUTPUT);
  digitalWrite(Trigger,LOW);//Initializing Trigger in 0
  Serial.begin(115200); //or you can also use 9600
  delay(10);
  
  WiFi.mode(WIFI_STA); //wifi command
  WiFi.begin(ssid, password); //wifi command
  Serial.print("Conectando a:\t");
  Serial.println(ssid); 
  
  while (WiFi.status() != WL_CONNECTED) //wifi 
  {
    delay(200); 
    Serial.print('.');
  }
  //Success connection messages 
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
  digitalWrite(green,HIGH); //ESP8266 WiFi connected
  digitalWrite(red,LOW);
  }
  else
  {
    digitalWrite(red,HIGH); //Waiting for WiFi connection
    digitalWrite(green,LOW);
    }

    digitalRead(Echo)==HIGH; //this crap works better than INPUT

    digitalWrite(Trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trigger, LOW);

    t = pulseIn(Echo, HIGH);
    d = t/59;

    //respuesta(); //ignore this
    
    delay(5000);

    Serial.print("Conectando con "); 
    Serial.println(host);  

    // Client class
    WiFiClient client;  
    const int httpPort = 80;  
    if (!client.connect(host, httpPort)) {
        Serial.println("Fallo en la conexión.");
        return;
    } 

    String url = "/public/tanques/views/_presentador.php?xaction=set_sensor_tanque&tanque=4&lectura="+String(d)+"cm";/***/
    Serial.println(url);

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Rebasado 5 segundos.");
            client.stop();
            return;
        }
    }

    
    while(client.available()) {
        String lineas = client.readStringUntil('\r');
        Serial.print(lineas);
    }

    Serial.println();
    Serial.println("Conexión cerrada."); 
    
 }
 /* void respuesta()
    {
      Serial.print("Distancia ");
      Serial.print(d);
      Serial.println();
      delay(2000);
      }*/ 
