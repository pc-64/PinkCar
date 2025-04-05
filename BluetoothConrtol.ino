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
      int lValue = analogRead(lPin);
      int rValue = analogRead(rPin);
      char buffer[15];
      snprintf(buffer, 14, "%d,%d", lValue, rValue);
      radio.println(buffer);
   }
}
