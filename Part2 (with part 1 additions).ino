#include "Timer.h"
#include "Event.h"
#include <Wire.h>
#define sw 7
#define CW1 8
#define CCW1 9
#define CW2 10
#define CCW2 11
#define IMU 0x68
#define PWR 0x6B
#define GYRO 0x1B
#define GYRO_Z 0x47
float angle2=0,theta0=0;
Timer Time;
void setup() 
{
  Serial.begin(9600);
  Wire.begin();
  turn_imu();
  pinMode(sw,INPUT_PULLUP);
  pinMode(CW1,OUTPUT);
  pinMode(CCW1,OUTPUT);
  pinMode(CW2,OUTPUT);
  pinMode(CCW2,OUTPUT);
  Time.every(1,angleCalc);
}

void loop() 
{
  
  if(!digitalRead(sw))
    {
      if(angle2<90)
        {
          digitalWrite(CW2,HIGH);
          digitalWrite(CCW2,LOW);
        }
      else
        {
          digitalWrite(CW2,LOW);
          digitalWrite(CCW2,LOW);
        }
    }
  else
    {
      if(angle2>0)
        {
          digitalWrite(CW2,LOW);
          digitalWrite(CCW2,HIGH);
        }
      else
        {
          digitalWrite(CW2,LOW);
          digitalWrite(CCW2,LOW);
        }
    }
  Serial.print("angle of arm 2 = ");
  Serial.println(angle2); 
  Time.update();
}

void turn_imu()
{
  Wire.beginTransmission(IMU);
  Wire.write(PWR);
  Wire.write(0);
  Wire.endTransmission();
}

void turn_gyro()
{
  Wire.beginTransmission(IMU);
  Wire.write(GYRO);
  Wire.write(0x10);
  Wire.endTransmission();
}

int angular_z()
{
  turn_gyro();
  int gyro_z;
  Wire.beginTransmission(IMU);
  Wire.write(GYRO_Z);
  Wire.endTransmission();
  Wire.requestFrom(IMU,2);
  while(Wire.available()<2);
  gyro_z=Wire.read()<<8 + Wire.read();
  gyro_z=map(gyro_z,-32786,32785,-1000,1000);
  return(gyro_z);
}

int angular_z_calibration()
{
  int gyro_z=0;
  for(int i=0;i<3000;i++)
    gyro_z+=angular_z();
  gyro_z/=3000;
  return(gyro_z);
}

void angleCalc()
{
  angle2=theta0+angular_z_calibration()/1000;
  theta0=angle2;
}
