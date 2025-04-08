#include <SoftwareSerial.h>

const byte lPin = A0;
const byte rPin = A1;

SoftwareSerial radio(12, 13);

void setup()
{
   radio.begin(9600);
}

void loop()
{
   static unsigned long timer = 0;
   unsigned long interval = 250;
   if (millis() - timer >= interval)
   {
       timer = millis();

       int lValue;
       int rValue;
       int command2;
       lValue = (analogRead(lPin)+1)/16 ;
       rValue = (analogRead(rPin)+1)/16;
       command2 = rValue + (lValue ) * 100;
      char buffer[15];
      snprintf(buffer, 14, "%d", command2);
      radio.println(buffer);
   }
}
