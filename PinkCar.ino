#include <SoftwareSerial.h>
#define NumOfPwmPins 2
#define LFA 9
#define LFB 10
#define RFA 7
#define RFB 8
#define LRA 5
#define LRB 6
#define RRA 3
#define RRB 4
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
      
      execut(atoi(cache));
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


void execut(int command)
{
int lSpin = (command/100)-32 ;
int rSpin = (command%100)-32 ;
lSpin = lSpin /10 * 10;
rSpin = rSpin /10 * 10;
if (rSpin) {
if (rSpin > 0 ) {
SpinUp(RFA, LOW, RFB, rSpin);
SpinUp(RRA, LOW, RRB, rSpin);
 
} else {
SpinUp(RFA, abs(rSpin), RFB, LOW);
SpinUp(RRA, abs(rSpin), RRB, LOW);
};
}
else {
SpinUp(RFA, LOW, RFB, LOW);
SpinUp(RRA, LOW, RRB, LOW);
}
if (lSpin) {
 
if (lSpin > 0 ) {
SpinUp(LFA, LOW, LFB, lSpin );
SpinUp(LRA, LOW, LRB, lSpin);
 
} else {
SpinUp(LFA, abs(lSpin), LFB, LOW);
SpinUp(LRA, abs(lSpin), LRB, LOW);
 
};
} else {
 
SpinUp(LFA, LOW, LFB, LOW);
SpinUp(LRA, LOW, LRB, LOW);
}
 
}
 
void SpinUp(int in1, int val1, int in2 , int val2 )
{
digitalWrite(in1, val1);
digitalWrite(in2, val2);
}
void execut2()
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

