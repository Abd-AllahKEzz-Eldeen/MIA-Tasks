#!usr/bin/env python3
import rospy,odrive
from std_msgs.msg import Float32

if __name__=="__main__":
    rospy.init_node("Subscriber")                                                   #initializing node

    odrv0 = odrive.find_any()                                                       #fine Odrive

    odrv0.axis0.requested_state = AXIS_STATE_FULL_CALIBRATION_SEQUENCE              #calibrating Odrive

    odrv0.axis0.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL                    #setting closed loop mode

    odrv0.axis0.controller.config.control_mode = CONTROL_MODE_POSITION_CONTROL      #setting position control mode


    def set_point(point:Float32):                                                   #function to subscribe the set point
        odrv0.axis0.controller.input_pos = point.data


    subscriber = rospy.Subscriber("/SetPoint",Float32,set_point)                    #initializing topic to subscribe from

    rospy.spin()