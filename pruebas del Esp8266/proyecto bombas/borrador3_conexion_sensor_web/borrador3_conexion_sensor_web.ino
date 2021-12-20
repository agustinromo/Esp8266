#include <ESP8266WiFi.h>
// Sustituir con datos de vuestra red
const char* ssid     = "TS_RRHH";
const char* password = "TsAdmin2020"; 

const char* host = "controlcombustible.com.mx"; /***/
const char* nombre = "agus"; 
//const char* ciudad = "Roma"; 

#define red 12 //D6
#define green 14 //D5

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
  digitalWrite(Trigger,LOW);
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

    digitalRead(Echo)==HIGH; //this crap works better than INPUT

    digitalWrite(Trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trigger, LOW);

    t = pulseIn(Echo, HIGH);
    d = t/59;

    respuesta();

    
    delay(5000);

    Serial.print("Conectando con "); 
    Serial.println(host);  

    // Clase cliente
    WiFiClient client;  
    const int httpPort = 80;  
    if (!client.connect(host, httpPort)) {
        Serial.println("Fallo en la conexión.");
        return;
    } 


    String url = "/public/tanques/views/_presentador.php?xaction=set_sensor_tanque&tanque=4&lectura="+String(d)+"cm";/***/
   /* url += "?nombre=";
    url += nombre;
    url += "&ciudad=";
    url += d; */

    Serial.println(url);


     // Esto es lo que se enviará al servidor.
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


    
    // Lee todas las líneas que ha enviado el servidor.
    while(client.available()) {
        String lineas = client.readStringUntil('\r');
        Serial.print(lineas);
    }

    Serial.println();
    Serial.println("Conexión cerrada.");

    
    
 }
  void respuesta()
    {
      Serial.print("Distancia ");
      Serial.print(d);
      Serial.println();
      delay(2000);
      }
