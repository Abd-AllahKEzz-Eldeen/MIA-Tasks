#include "Timer.h"
#include "Event.h"
#include <Wire.h>
#define motor_direction 2
#define motor_speed 3
#define IMU 0x68
#define PWR 0x6B
#define GYRO 0x1B
#define GYRO_Z 0x47
float angle=0,theta0=0,set_point=0;
float Kp=10,Ki=7,Kd=1;
float error=0,prev_error=0,total_error=0;
double dtime = 0.0005;
float PID=0;
Timer Time;
void setup() 
{
  Serial.begin(9600);
  Wire.begin();
  pinMode(motor_direction,OUTPUT);
  pinMode(motor_speed,OUTPUT);
  turn_imu();    //turn on the IMU
  Time.every(0.5,PIDRoutine);         //making the PID calculations  every 500uS  -> So, dtime=500uS  (We don't have to calculate dtime)
}

void loop() 
{
  if(Serial.available()==3)                           //reading the target from serial monitor in range 0->360
    set_point = (Serial.read()-'0')*100 + (Serial.read()-'0')*10 + (Serial.read()-'0');
  else if(Serial.available()==2)
    set_point = (Serial.read()-'0')*10 + (Serial.read()-'0');
  else if(Serial.available())
    set_point = (Serial.read()-'0');
    
  if(angle<set_point)                     //if angle < targer -> go CW with PID speed
  {
    digitalWrite(motor_direction,HIGH);
    analogWrite(motor_speed,PID);                
  }
  else if(angle>set_point)               //if angle > target -> go CCW with PID speed
  {
    digitalWrite(motor_direction,LOW);
    analogWrite(motor_speed,PID);
  }
  else                                  //if angle = target -> stop
  {
   digitalWrite(motor_direction,HIGH);
   analogWrite(motor_speed,0);
  }                      
  
  Serial.print("angle of camera = ");
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

void angleCalc()
{
    angle+=theta0+angular_z_calibration()*dtime;               //integrating the angular velocity to get the angle
    theta0=angle;
}

void PIDRoutine()
{
  angleCalc();

  error = set_point - angle;                                 //calculating the error

  total_error += error*dtime;                                // integrating error with respect to time

  float derror = error - prev_error;                         //differentiating the error with respect to time

  PID = abs(Kp*error + Ki*total_error + Kd*derror/dtime);         // calculating the PID
  
  //PID = map(PID,0,PID_max,0,255);                                we could map the PID in the voltage levels for PWM from 0 to PID(max)
  // PID = Kp*e(t) + Ki*integral(e(t)*dt) + Kd*de(t)/dt
  // PID(max) -> dPID(t)/dt = 0
  // dPID(t)/dt = Kd*e'' + Kp*e' + Ki*e = 0                       (Second order Homo. Diff. Eqn)
  // e(t)|PID max = c1*exp(-Kp+sqrt(Kp*Kp-4*Kd*Ki)) + c2*exp(-Kp-sqrt(Kp*Kp-4*Kd*Ki))  (solving DE)
 
  prev_error = error;
}
