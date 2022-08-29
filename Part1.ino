#include "Timer.h"
#include "Event.h"
#define a1 2
#define b1 4
#define a2 3
#define b2 6
#define sw 7
#define CW1 8
#define CCW1 9
#define CW2 10
#define CCW2 11
unsigned int counter1=0,counter2=0;
float angle1=0,angle2=0;
Timer Time;
void setup() 
{
  Serial.begin(9600);
  pinMode(a1,INPUT_PULLUP);
  pinMode(b1,INPUT_PULLUP);
  pinMode(a2,INPUT_PULLUP);
  pinMode(b2,INPUT_PULLUP);  
  pinMode(sw,INPUT_PULLUP);
  pinMode(CW1,OUTPUT);
  pinMode(CCW1,OUTPUT);
  pinMode(CW2,OUTPUT);
  pinMode(CCW2,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(a1),Pin_a1,CHANGE);     //interrupt on channel a for motor1 pin
  //attachInterrupt(digitalPinToInterrupt(b1),Pin_b1,CHANGE);   arduino uno has only 2 interrupt pins
  attachInterrupt(digitalPinToInterrupt(a2),Pin_a2,CHANGE);     //interrupt on channel b for motor2 pin
  //attachInterrupt(digitalPinToInterrupt(b2),Pin_b2,CHANGE);    arduino uno has only 2 interrupt pins
  while(angle1<60)          // angle have to be 60 then doen't change again
    {
      digitalWrite(CW1,HIGH);
      digitalWrite(CCW1,LOW);
    }
  digitalWrite(CW1,LOW);
  Time.every(1,angleCalc);       //calculate the angles every milli second
}

void loop() 
{
  if(!digitalRead(sw))             //if the switch is closed
    {
      if(angle2<90)              // go to angle 90
        {
          digitalWrite(CW2,HIGH);
          digitalWrite(CCW2,LOW);
        }
      else                       // then stop
        {
          digitalWrite(CW2,LOW);
          digitalWrite(CCW2,LOW);
        }
    }
  else                          //if the swith is opened
    {
      if(angle2>0)              // go to angle 0
        {
          digitalWrite(CW2,LOW);
          digitalWrite(CCW2,HIGH);
        }
      else                     //then stop
        {
          digitalWrite(CW2,LOW);
          digitalWrite(CCW2,LOW);
        }
    }
  Serial.print("angle of arm 1 = ");
  Serial.println(angle1);  
  Serial.print("angle of arm 2 = ");
  Serial.println(angle2); 
  Time.update();
}

void angleCalc()
{
  angle1=counter1*360/1200;               //2400 instead of 1200 if we use the 4 interrupts
  angle2=counter2*360/1200;
}

void Pin_a1()    // num of counters calculation
{
  if(digitalRead(a1)!=digitalRead(b1))
    counter1++;
  else
    counter1--;  

}

// not used
/*void Pin_b1()
{
  if(digitalRead(a1)==digitalRead(b1))
    counter1++;
  else
    counter1--;
}*/

void Pin_a2()
{
  if(digitalRead(a2)!=digitalRead(b2))
    counter2++;
  else
    counter2--;  

}

// not used
/*void Pin_b2()
{
  if(digitalRead(a2)==digitalRead(b2))
    counter2++;
  else
    counter2--;
}*/
