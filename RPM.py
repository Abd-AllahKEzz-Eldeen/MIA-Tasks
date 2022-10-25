#!/usr/bin/env python3
import rospy
from std_msgs.msg import Int32

if __name__ == "__main__":
    rospy.init_node("RPM_subscriber")   #initalization the node

    def RPM(msg:Int32):                 #callback function
        rospy.loginfo(msg.data)

    subscriber = rospy.Subscriber("/RPM",Int32,callback=RPM)

    rospy.spin()