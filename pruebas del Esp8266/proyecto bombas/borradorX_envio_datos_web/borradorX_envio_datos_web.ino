#include <ESP8266WiFi.h>

const char* ssid = "rola9294";
const char* password = "ROMO1951";

const char* host = "kio4.com"; /***/
const char* nombre = "agus"; 
const char* ciudad = "Roma";
// const char* ciudad = "Grazalema";

void setup()
{
    Serial.begin(115200);
    delay(10);

  // Conecta a la red wifi.
  Serial.println();
  Serial.print("Conectando con ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado con WiFi.");

  // Esta es tu IP
  Serial.print("Esta es tu IP: ");
  Serial.print(WiFi.localIP());
}

void loop()
{
    delay(5000);

    Serial.print("Conectando con "); /***/
    Serial.println(host);  /***/

    // Clase cliente
    WiFiClient client;  /***/
    const int httpPort = 80;  /***/
    if (!client.connect(host, httpPort)) {
        Serial.println("Fallo en la conexión.");
        return;
    } /***/

    // Linea de petición
    String url = "/appinventor/php/respuesta.php";
    url += "?nombre=";
    url += nombre;
    url += "&ciudad=";
    url += ciudad;

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
