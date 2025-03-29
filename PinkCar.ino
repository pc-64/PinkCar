#include <SoftwareSerial.h>
#include <MX1508.h>
#define NumOfPwmPins 2
#define LFA 9
#define LFB 10
#define RFA 7
#define RFB 8
#define LRA 5
#define LRB 6
#define RRA 4
#define RRB 3
#define MIN_MAX 255   
 
MX1508 lFront(LFA,LFB, SLOW_DECAY, NumOfPwmPins);
MX1508 rFront (RFA,RFB, SLOW_DECAY, NumOfPwmPins);
MX1508 lRear(LRA,LRB, SLOW_DECAY, NumOfPwmPins);
MX1508 rRear(RRA,RRB, SLOW_DECAY, NumOfPwmPins);

int lValue = 0;
int rValue = 0;

const byte cacheSize = 32;
char cache[cacheSize];  

boolean ready = false;

SoftwareSerial radio(12, 13);

void setup()
{
   
   radio.begin(9600);
}

void loop()
{
 fetch();
   
   if (ready)
   {
      parser();
      execut();
      ready = false;
   }
}

void fetch()
{
   static byte pointer = 0;
   char termination = '\n';
   char rc;

   while (radio.available() > 0 && ready == false)
   {
      rc = radio.read();

      if (rc != termination)
      {
         cache[pointer] = rc;
         pointer++;
         if (pointer >= cacheSize)
         {
            pointer = cacheSize - 1;
         }
      }
      else
      {
         cache[pointer] = '\0'; 
         pointer = 0;
         ready = true;
      }
   }
}

void parser()
{
   char *strings[2]; 
   char *ptr = NULL; byte index = 0;
   ptr = strtok(cache, ","); 
   while (ptr != NULL)
   {
      strings[index] = ptr;
      index++;
      ptr = strtok(NULL, ",");
   }

   lValue = atoi(strings[0]);
   rValue = atoi(strings[1]);   
}

void execut()
{
  int lSpin = map((lValue), 0, 1024, -MIN_MAX , MIN_MAX ); // limit for  rSpin > MIN_MAX
  int rSpin = map((rValue), 0, 1024, -MIN_MAX, MIN_MAX);     // limit for  rSpin > MIN_MAX

  lFront.motorGo(lSpin);  
  lRear.motorGo(lSpin);    
  rFront.motorGo(rSpin);  
  rRear.motorGo(rSpin);  
}


