# simple_test
this is a RAVEN simple testing software to validate if RAVEN is working properly when given teleoperation commands.
Here we have a publish function : publish to ravenstate ROS topic
         and a callback function : subscribe to raven_automove ROS topic

The ravenstate topic is updated at 1000 Hz from the main RAVEN software, and everytime we receive new ravenstate, 
the callback function is automatically executed. Inside the callback function, there is the publish function to 
compute motion commands according to current ravenstate, then sends out the command to raven_automove topic.

So both the publishing and subscribing process is performed at 1000 Hz.
This is the simple version of remote command sending that serves as a quick way to test if RAVEN is functioning normal.
