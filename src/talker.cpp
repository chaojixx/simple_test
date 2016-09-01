#include <ros/ros.h>
#include <ros/transport_hints.h>
#include <tf/transform_datatypes.h>
#include <sstream>
#include <pthread.h>
#include "AutoCircle.h"

using namespace raven_2;
using namespace std;


int main(int argc, char **argv)
{
	
	if(!init_process(argc,argv))
		exit(1);
  	
	pthread_create(&console_thread,NULL,console_process,NULL);
	pthread_create(&ros_thread,NULL,ros_process,NULL);
	
	ros::spin();

	pthread_join(console_thread,NULL);
	pthread_join(ros_thread,NULL);
	finalWords();

  	exit(1);
}