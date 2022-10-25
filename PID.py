#!/usr/bin/env python3
import rospy
from std_msgs.msg import Float32

if __name__ == "__main__":
    rospy.init_node("set_point")    #initialization the node

    publisher = rospy.Publisher("/velocity",Float32,queue_size=10)

    while not rospy.is_shutdown():
        RPM = float(input())        #enter set point
        publisher.publish(RPM)      #publishing set point