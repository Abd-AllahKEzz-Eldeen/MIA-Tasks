#include <SoftwareSerial.h>
#include <Wire.h>
SoftwareSerial mySerial(2,3);
#define enable 6    // IC enable
#define input1 7    // clockwise pin
#define input2 8    // CCW pin
unsigned int Temp,MSR;
void setup() 
{
  Serial.begin(9600);
  mySerial.begin(9600);
  Wire.begin();
  pinMode(enable,OUTPUT);
  pinMode(input1,OUTPUT);
  pinMode(input2,OUTPUT);
}

void loop()
{
  Wire.requestFrom(8,6);    // receiving at moast 6 bytes (3 digits) from the slave whose adress 8
  
  if(mySerial.available())    // function reads characters (the wrong one)
    MSR=mySerial.read();
  
  if(Wire.available())      // receiving the slave's data
    Temp=Wire.read();
  
  Serial.print(Temp);     // printing temp & moisture & showing them on the plotter
  Serial.print(",");
  Serial.println(MSR);
  delay(1);

   if(Temp<20)        // if temp < 20, rotate CCW
    {
      digitalWrite(enable,HIGH);
      digitalWrite(input1,LOW);
      digitalWrite(input2,HIGH);
    }
   else if(Temp>40)     // if temp > 40, rotate CW
    {
      digitalWrite(enable,HIGH);
      digitalWrite(input1,HIGH);
      digitalWrite(input2,LOW);
    }
   else           // else , stop
    {
      digitalWrite(enable,LOW);
      digitalWrite(input1,LOW);
      digitalWrite(input2,LOW);
    }                 // hint: if the temp is negative or greater than 100, it's the same as it was 0
}
