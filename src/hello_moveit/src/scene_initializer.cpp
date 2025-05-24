#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.h> 
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <shape_msgs/msg/solid_primitive.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <moveit_msgs/msg/collision_object.hpp>
#include <geometric_shapes/mesh_operations.h>
#include <geometric_shapes/shape_operations.h> 
#include <boost/variant/get.hpp> 
#include <tf2/LinearMath/Quaternion.h>

using namespace std::chrono_literals;

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared(
      "scene_initializer", rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true));
  auto logger = node->get_logger();

  /*fixture*/
  moveit_msgs::msg::CollisionObject fixture;
  fixture.header.frame_id ="world";        
  fixture.id = "fixture";
  fixture.operation = fixture.ADD;

  shape_msgs::msg::SolidPrimitive prim_fix;
  prim_fix.type = prim_fix.BOX;
  prim_fix.dimensions = {0.1 ,0.1, 0.2};  

  geometry_msgs::msg::Pose pose_fix{};
  pose_fix.orientation.w = 1.0;
  pose_fix.position.x = 0;
  pose_fix.position.y = -0.36;
  pose_fix.position.z = 0.91;

  fixture.primitives.push_back(prim_fix);
  fixture.primitive_poses.push_back(pose_fix);

  /*table*/
  moveit_msgs::msg::CollisionObject table;
  table.header.frame_id ="world";        
  table.id = "table";
  table.operation = table.ADD;

  shape_msgs::msg::SolidPrimitive primitive;
  primitive.type = primitive.BOX;
  primitive.dimensions = {0.6 ,1.115, 0.81};  

  geometry_msgs::msg::Pose pose;
  pose.orientation.w = 1.0;
  pose.position.x = 0;
  pose.position.y = 0;
  pose.position.z = 0.405;

  table.primitives.push_back(primitive);
  table.primitive_poses.push_back(pose);

  /*mm→m*/
  Eigen::Vector3d scale(0.001, 0.001, 0.001);

  /*conveyor chassis (mesh)*/
  moveit_msgs::msg::CollisionObject chassis;
  chassis.header.frame_id = "world";
  chassis.id = "conveyor_chassis";
  chassis.operation = chassis.ADD;

  shapes::Mesh* mesh_chassis =
      shapes::createMeshFromResource(
        "package://lrmate_200id/models/ConveyorChassis/meshes/ConveyorChassis.stl",
        scale);                                                    

  shapes::ShapeMsg chassis_shape_msg;
  shapes::constructMsgFromShape(mesh_chassis, chassis_shape_msg);
  chassis.meshes.push_back(
      boost::get<shape_msgs::msg::Mesh>(chassis_shape_msg));                     

  geometry_msgs::msg::Pose chassis_pose{};
  chassis_pose.orientation.w = 1.0;
  chassis_pose.position.x = 0.3;
  chassis_pose.position.y = -2.0;
  chassis_pose.position.z = 0.0;

  tf2::Quaternion q1;
  q1.setRPY(1.57, 0, 1.57);  // RPY: Roll, Pitch, Yaw (弧度)
  chassis_pose.orientation.x = q1.x();
  chassis_pose.orientation.y = q1.y();
  chassis_pose.orientation.z = q1.z();
  chassis_pose.orientation.w = q1.w();

  chassis.mesh_poses.push_back(chassis_pose);

  /*belt surface (mesh)
  
  moveit_msgs::msg::CollisionObject belt;
  belt.header.frame_id = "world";
  belt.id = "conveyor_belt";
  belt.operation = belt.ADD;

  shapes::Mesh* mesh_belt =
      shapes::createMeshFromResource(
        "package://lrmate_200id/models/ConveyorChassis/meshes/ConveyorBelt_belt_surface.stl",
        scale);                                                 

  shapes::ShapeMsg belt_shape_msg;
  shapes::constructMsgFromShape(mesh_belt, belt_shape_msg);
  belt.meshes.push_back(
      boost::get<shape_msgs::msg::Mesh>(belt_shape_msg));

  geometry_msgs::msg::Pose belt_pose{};
  belt_pose.orientation.w = 1.0;
  belt_pose.position.x = 0.0;
  belt_pose.position.y = 0.83;
  belt_pose.position.z = 0.05025;

  tf2::Quaternion q2;
  q2.setRPY(1.57, 0 ,0);  // Roll, Pitch, Yaw（弧度）
  tf2::Quaternion q3 = q1 * q2;
  belt_pose.orientation.x = q3.x();
  belt_pose.orientation.y = q3.y();
  belt_pose.orientation.z = q3.z();
  belt_pose.orientation.w = q3.w();

  belt.mesh_poses.push_back(belt_pose);

  */
  /* 送到 PlanningScene */
  moveit::planning_interface::PlanningSceneInterface psi;
  psi.applyCollisionObject(fixture);
  RCLCPP_INFO(logger, "Collision object 'fixture' 已加入場景.");
  psi.applyCollisionObject(table);
  RCLCPP_INFO(logger, "Collision object 'table' 已加入場景.");
  psi.applyCollisionObjects({chassis});
  RCLCPP_INFO(logger, "Collision object 'conveyor' 已加入場景.");
  rclcpp::shutdown();
  return 0;
}
