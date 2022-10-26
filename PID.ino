#include <ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int32.h>

//encoder pins
#define pinA PB13
#define pinB PB12

//cytron pins
#define cytron_direction PB0
#define cytron_PWM PB1

volatile long counter=0;                   //counter to calculate #revolutions
long counter0=0,dcounter=0;                //variables to calculate change in counters to calculate the RPM
float set_point=0;                         //set point to be acheived
float Kp=10,Ki=7,Kd=1;                     //PID constants
float error=0,prev_error=0,total_error=0;  //error variables
double dtime=1e-6,time0;                        //variables to calculate time differential element
long RPM=0;                                //value of RPM (initially = 0)
float PID=0;                               //value of PID (initially = 0)

ros::NodeHandle node_handler_publisher;                
ros::NodeHandle node_handler_subscriber;

std_msgs::Int32 motor_RPM;
ros::Publisher publisher("RPM", &motor_RPM);


//function to subscribe the required set point
void required_velocity(const std_msgs:: Float32& velocity)
{
  set_point = velocity.data;
}

ros::Subscriber<std_msgs::Float32> subscriber("velocity", &required_velocity);      //subscribe to a velocity topic

void setup() 
{
  Serial.begin(115200);

  //initializing the publisher node
  node_handler_publisher.initNode();
  node_handler_publisher.advertise(publisher);

  //initializing the subscriber node
  node_handler_subscriber.initNode();
  node_handler_subscriber.subscribe(subscriber);

  //receiving encoder pins signals
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);

  //cytron pins modes
  pinMode(cytron_direction, OUTPUT);
  pinMode(cytron_PWM, PWM);

  //Attaching inturrupt to encoder pins
  attachInterrupt(digitalPinToInterrupt(pinA),pin_A,CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinB),pin_B,CHANGE);
 
}

void loop() 
{
  time0 = millis();

  PIDRoutine();                 //calculating PID

  if(PID>0)
  {
    digitalWrite(cytron_direction,HIGH);
    pwmWrite(cytron_PWM,PID);
  }
  else if(PID<0)
  {
    digitalWrite(cytron_direction,LOW);
    pwmWrite(cytron_PWM,PID);
  }

  //publishing the RPM to the RPM topic
  motor_RPM.data=RPM;
  publisher.publish(&motor_RPM);

  //Don't kill the nodes
  node_handler_publisher.spinOnce();
  node_handler_subscriber.spinOnce();
  
  dtime=millis()-time0;       //the differential element of time
}


void pin_A()                      //pin A calculating #counts
{
  if(digitalRead(pinA)!=digitalRead(pinB))
    counter++;
  else
    counter--;

}

void pin_B()                      //pin B calculating #counts
{
  if(digitalRead(pinA)==digitalRead(pinB))
    counter++;
  else
    counter--;
}

void RPMCalc()                    //method to calculate the RPM
{
  dcounter = counter - counter0;
  counter0 = counter;
  RPM = dcounter*60000/(540*dtime);             //counter/540= #revolutions  dtime/60000 = minute
}

void PIDRoutine()                 //method to calculate the PID
{
  RPMCalc();                                                // calculating the RPM

  error = set_point - RPM;                                   //calculating the error

  total_error += error*dtime;                                // integrating error with respect to time

  float derror = error - prev_error;                         //differentiating the error with respect to time

  PID = Kp*error + Ki*total_error + Kd*derror/dtime;         // calculating the PID
  
  //PID = map(PID,0,PID_max,0,65535);                                we could map the PID in the voltage levels for PWM from 0 to PID(max)
  // PID = Kp*e(t) + Ki*integral(e(t)*dt) + Kd*de(t)/dt
  // PID(max) -> dPID(t)/dt = 0
  // dPID(t)/dt = Kd*e'' + Kp*e' + Ki*e = 0                       (Second order Homo. Diff. Eqn)
  // e(t)|PID max = c1*exp(-Kp+sqrt(Kp*Kp-4*Kd*Ki)) + c2*exp(-Kp-sqrt(Kp*Kp-4*Kd*Ki))  (solving DE)
 
  prev_error = error;
}
