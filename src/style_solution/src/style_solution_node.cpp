

#include <style_solution/style_solution.h>

////////////////////////////////////////////////////////////////////////////////
int
main (int argc, char** argv)
{
  /**
    * The ros::init() function needs to see argc and argv so that it can perform
    * any ROS arguments and name remapping that were provided at the command line.
    * For programmatic remappings you can use a different version of init() which takes
    * remappings directly, but for most command-line programs, passing argc and argv is
    * the easiest way to do it.  The third argument to init() is the name of the node.
    *
    * You must call one of the versions of ros::init () before using any other
    * part of the ROS system.
    */
  ros::init (argc, argv, "pcl_solution_node");
  
  /**
    * NodeHandle is the main access point to communications with the ROS system.
    * The first NodeHandle constructed will fully initialize this node, and the last
    * NodeHandle destructed will close down the node.
    */
  ros::NodeHandle nh ("~");
  
  // Create a Lab object
  StyleSolution style_solution (nh);

  // Create a ROS subscriber for the input point cloud
  ros::Subscriber sub_one =
    nh.subscribe ("/r200/camera/depth_registered/points",
                  1,
                  &StyleSolution::cloudCallBackOne,
                  &style_solution);
                  
  ros::Subscriber sub_two =
    nh.subscribe ("/r200/camera/depth_registered/points",
                  1,
                  &StyleSolution::cloudCallBackTwo,
                  &style_solution);

  // Loop at 10Hz
  ros::Rate loop_rate (10);

  while (ros::ok ())
  {
    // Testing adding three numbers
    style_solution.findZ (3, 4);
    style_solution.findZBetter (3, 4);

    // ROS Spin
    ros::spinOnce ();
    
    // Sleep
    loop_rate.sleep ();
  }
  
  return (0);
}