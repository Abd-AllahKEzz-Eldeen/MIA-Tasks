#!/usr/bin/env python3
import rospy
from std_msgs.msg import Float32

estimate_value = 0

estimate_error = 0

measured_error = 0

def yaw_angle(angle : Float32):
    kalman_gain = estimate_error / (estimate_error + measured_error)

    estimate_value0 = estimate_value
    estimate_value = estimate_value0 + kalman_gain(angle - estimate_value0)

    estimate_error0 = estimate_error
    estimate_error = estimate_error0 * (1 - kalman_gain)

    publisher.publish(estimate_value)

if __name__ == "__main__":
    rospy.init_node("Kalman")

    publisher = rospy.Publisher("/Kalman_IMU", Float32, queue_size = 10)

    subscriber = rospy.Subscriber("/IMU", Float32, callback = yaw_angle)

    rospy.spin()