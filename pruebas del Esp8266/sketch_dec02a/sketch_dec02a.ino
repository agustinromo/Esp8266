ADC_MODE(ADC_VCC);

// Librerias necesarias
//#include <OneWire.h>
//#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
 
#define DS18B20 D5 //DS18B20 esta conectado al pin GPIO D5 del NodeMCU

String apiKey = "xxxxxx";     //  Poner la apikey que te da ThingSpeak
const char* ssid =  "yyyyyy";  // Poner el nombre de tu red wi-fi
const char* pass =  "zzzzzz"; // Poner la contraseña de tu red wi-fi
const char* server = "api.thingspeak.com";// El servidor de Thingspeak, esto NO se modifica

// Defino variables numericas
float temp;// Variable para la temperatura leida
int veces;// Variable para los intentos de subir el dato de temperatura a la nube; para que en caso de apagón, no se gaste toda la batería intentando e intentando subir el dato.
 
OneWire ourWire(DS18B20);// Se declara un objeto para la libreria
DallasTemperature sensor(&ourWire);// Se declara un objeto para la otra libreria
WiFiClient client;// Se define el cliente wi-fi
 
void setup() {
   pinMode(D0, WAKEUP_PULLUP);//
   delay(1000);// Esperamos 1 segundo
   sensor.begin();// Inicializa el sensor de T
   WiFi.begin(ssid, pass);// Inicializa la comunicación por wi-fi
   while (WiFi.status() != WL_CONNECTED) // Si no se logra conectar, repetira el intento de conectarse tantas "veces" como se puso en dicha variable
     {
            delay(100);
            ++veces;
            if (veces>50) ESP.deepSleep(300e6);// Luego de 50 intentos se va a dormir para ahorrar energia, esto sirve para prevenir que si hay un apagón y el router se apago el no siga gastando energia intentando conectarse
     }}
 
void loop() {
   sensor.requestTemperatures();    // Le pide el valor de temperatura al sensor
   temp = sensor.getTempCByIndex(0);// Lee el valor de temperatura del sensor
   int vcc = ESP.getVcc();          // Mide el voltaje a la entrada de la alimentacion del ESP8266 para evaluar cuanta carga le queda a la batería
   float vccVolt=1.105*vcc/1000;    // Ese factor empírico lo ajusté hasta que la medida se pareció a lo que indicaba el tester. No se por qué no indica el voltaje correcto
   if (client.connect(server,80))   // "184.106.153.149" or api.thingspeak.com
      {  
       String sendData = apiKey+"&field1="+String(temp)+"&field2="+String(vccVolt)+"\r\n\r\n"; // En field 1 va la temperatura y en field 2 va el voltaje

       // Estableciendo conexion con Thingspeak
       client.print("POST /update HTTP/1.1\n");
       client.print("Host: api.thingspeak.com\n");
       client.print("Connection: close\n");
       client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
       client.print("Content-Type: application/x-www-form-urlencoded\n");
       client.print("Content-Length: ");
       client.print(sendData.length());
       client.print("\n\n");
       client.print(sendData);
      }
      client.stop();
      ESP.deepSleep(60e6);// microsegundos hasta la proxima medida el modulo se pone a dormir para ahorrar energia
      }
