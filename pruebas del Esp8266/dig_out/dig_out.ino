//#define led 0 //D3 
           // 2 //D4 
#define led 4 //D2
           // 5 //D1
// y así sucesivamente. Ver esquema
void setup()
{
  pinMode(led,OUTPUT);
  }
  void loop()
  {
    digitalWrite(led,HIGH);
    delay(300);
    digitalWrite(led,LOW);
    delay(300);
    }
