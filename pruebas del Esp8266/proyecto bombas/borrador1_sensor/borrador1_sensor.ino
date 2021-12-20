#define Trigger 5 //D1 
#define Echo 4 //D2

long t;
long d; 

void setup()
{
  Serial.begin(115200);
  //pinMode(Echo,INPUT);
  pinMode(Trigger,OUTPUT);
  digitalWrite(Trigger,LOW);
  }
  void loop()
  {
    digitalRead(Echo)==HIGH; //this crap works better than INPUT

    digitalWrite(Trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trigger, LOW);

    t = pulseIn(Echo, HIGH);
    d = t/59;

    respuesta();
    }

    void respuesta()
    {
      Serial.print("Distancia ");
      Serial.print(d);
      Serial.println();
      delay(2000);
      }
