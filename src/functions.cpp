#include "functions.h"
functions::functions()
{
	gtime = 0;
}

void functions::init_ros(int argc, char **argv)
{
	ros::init(argc,argv,"simple_test");
	ros::NodeHandle n;

	pub_automove = n.advertise<raven_2::raven_automove>("raven_automove",1);
	ros::Subscriber t = n.subscribe("ravenstate",1000,&functions::Callback,this);
	ros::spin();
}

void functions::publish_automove(tf::Vector3 pos_incr, int id) 
{
	raven_2::raven_automove rauto;
	rauto.hdr.stamp = rauto.hdr.stamp.now();
//      rauto.del_pos[0] = (int)pos_incr.x();
//	rauto.del_pos[1] = (int)pos_incr.y();
//	rauto.del_pos[2] = (int)pos_incr.z();


	tf::Vector3 zero(0,0,0);
	TF_INCR[0].setOrigin(pos_incr);
	TF_INCR[1].setOrigin(zero);
		
	tf::Quaternion Delta_Ori(0,0,0,1);
	TF_INCR[0].setRotation(Delta_Ori); 
	TF_INCR[1].setRotation(Delta_Ori); 

	tf::transformTFToMsg(TF_INCR[0], rauto.tf_incr[0]);   //tf_incr
	tf::transformTFToMsg(TF_INCR[1], rauto.tf_incr[1]);

	pub_automove.publish(rauto);

}


void functions::Callback(raven_2::raven_state msg)
{
	if(msg.runlevel>2)
	{
		gtime++;

		int x = msg.pos[0];
		int y = msg.pos[1];
		int z = msg.pos[2];    
		current_pos.setValue(x,y,z);

		if(gtime==1) 
		{
			increment.setValue(0,0,-5000);
			last_pos = current_pos;
			des_pos = current_pos+increment;
                        //ROS_INFO("distance start%f",(des_pos-current_pos).length());
		}
		else
		{
			tf::Vector3 pos_inc = des_pos-current_pos;
			double distance = pos_inc.length();
			if(distance>1000)
			{
			    tf::Vector3 inc = distance < maxin? pos_inc:pos_inc*maxin/distance;
			    publish_automove(inc,0);
                           // ROS_INFO("dest %f,%f,%f",des_pos.x(),des_pos.y(),des_pos.z());
			   //ROS_INFO("current_pos %f,%f,%f",current_pos.x(),current_pos.y(),current_pos.z());
			}

                        //if(gtime%1000==0) ROS_INFO("distance %f",distance);
		}
	}
}
