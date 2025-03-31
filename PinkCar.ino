#include <SoftwareSerial.h>
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
 

int lValue = 0;
int rValue = 0;

const byte cacheSize = 32;
char cache[cacheSize];  

boolean ready = false;

SoftwareSerial radio(12, 13);

void setup()
{

  pinMode(LFA, OUTPUT); 
  pinMode(LFB, OUTPUT);
  pinMode(RFA, OUTPUT);
  pinMode(RFB, OUTPUT);
  pinMode(LRA, OUTPUT);
  pinMode(LRB, OUTPUT);
  pinMode(RRA, OUTPUT);
  pinMode(RRB, OUTPUT);
   
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
 
 
 
 
 
  if (lSpin > 0 ) {
 lForward(lSpin);  
  
  }else {
lBackward (lSpin*(-1));  
  };

 if (rSpin > 0 ) {
 rForward(rSpin);  
  
  }else {
rBackward (rSpin*(-1));  
  };
 
 
}

void lForward(int speed )
{
  analogWrite(LFA, 0);
  analogWrite(LFB, speed);
  analogWrite(LRA, 0);
  analogWrite(LRB, speed);
}
void lBackward(int speed )
{
  analogWrite(LFA, speed);
  analogWrite(LFB, 0);
  analogWrite(LRA, speed);
  analogWrite(LRB, 0);
}

void rForward(int speed )
{
  analogWrite(RFA, 0);
  analogWrite(RFB, speed);
  analogWrite(RRA, 0);
  analogWrite(RRB, speed);
}
void rBackward(int speed )
{
  analogWrite(RFA, speed);
  analogWrite(RFB, 0);
  analogWrite(RRA, speed);
  analogWrite(RRB, 0);
}

