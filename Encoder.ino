#include <ros.h>
#include <std_msgs/UInt32.h>

//the pins to interrupt

#define pinA PB13
#define pinB PB12

ros::NodeHandle  node_handler;      //inistansiating the node handler

std_msgs::UInt32 counts;            //inistansiating the publisher message
ros::Publisher encoder("Encoder", &counts);   //inistantiating the publisher and the topic name

volatile unsigned long counter=0;

void setup()
{
  pinMode(pinA,INPUT_PULLUP);
  pinMode(pinB,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinA),pin_A,CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinB),pin_B,CHANGE);
  node_handler.initNode();
  node_handler.advertise(encoder);
}

void loop()
{
  counts.data = counter;
  encoder.publish( &counts );
  node_handler.spinOnce();
}

// num of counts calculation

void pin_A()
{
  if(digitalRead(pinA)!=digitalRead(pinB))
    counter++;
  else
    counter--;

}

void pin_B()
{
  if(digitalRead(pinA)==digitalRead(pinB))
    counter++;
  else
    counter--;
}
