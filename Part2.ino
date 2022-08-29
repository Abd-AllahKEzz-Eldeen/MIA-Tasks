#include "Timer.h"
#include "Event.h"
#include <Wire.h>
#define IMU 0x68
#define PWR 0x6B
#define GYRO 0x1B
#define GYRO_Z 0x47
float angle=0,theta0=0;
Timer Time;
void setup() 
{
  Serial.begin(9600);
  Wire.begin();
  turn_imu();    //turn on the IMU
  Time.every(1,angleCalc);          //calculate the angle every milli second
}

void loop() 
{
  Serial.print("angle of arm 2 = ");
  Serial.println(angle); 
  Time.update();
}

void turn_imu()                      // method to start the communication with IMU
{
  Wire.beginTransmission(IMU);
  Wire.write(PWR);
  Wire.write(0);
  Wire.endTransmission();
}

void turn_gyro()                      //method to start the communication with gyroscope
{
  Wire.beginTransmission(IMU);
  Wire.write(GYRO);
  Wire.write(0x10);             //scale from -1000 degree/sec to 1000 degree/sec
  Wire.endTransmission();
}

int angular_z()                            //method to calculate the angular velocity in yaw angle
{
  turn_gyro();                  //activating the gyroscope
  int gyro_z;
  Wire.beginTransmission(IMU);
  Wire.write(GYRO_Z);
  Wire.endTransmission();
  Wire.requestFrom(IMU,2);
  while(Wire.available()<2);          //the data is two byte intger
  gyro_z=Wire.read()<<8 + Wire.read();     //shifting the first byte the adding the secong to it (adding is more fast than ORing)
  gyro_z=map(gyro_z,-32786,32785,-1000,1000);   //mapping the value
  return(gyro_z);
}

int angular_z_calibration()              //method to calibrate every value with 3000 sample
{
  int gyro_z=0;
  for(int i=0;i<3000;i++)
    gyro_z+=angular_z();
  gyro_z/=3000;
  return(gyro_z);
}

void angleCalc()                                  //method to calculate the angle
{
  angle=theta0+angular_z_calibration()/1000;                 //integrating the angular velocity
  theta0=angle;
}
