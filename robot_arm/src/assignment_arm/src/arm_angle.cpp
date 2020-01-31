#include <functional>
#include <boost/bind.hpp>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>
#include <gazebo/common/Plugin.hh>
#include <ignition/math/Vector3.hh>

#include <assignment_arm/arm_angle.h>


#include "ros/ros.h"
#include "ros/callback_queue.h"
#include "ros/subscribe_options.h"
#include <stdio.h>
#include <thread>
#include <cstdlib>
#include <math.h>

namespace gazebo
{
  class ArmAngles : public ModelPlugin
  {
    // Pointer to the update event connection
    private: event::ConnectionPtr updateConnection;

    // Pointer to the model
    private: physics::ModelPtr model;

     private: physics::JointControllerPtr jointController;

        private: common::PID pid;

      private: std::unique_ptr<ros::NodeHandle> rosNode;
                
        private: ros::Subscriber    rosSub;
        private: ros::CallbackQueue rosQueue;
        private: std::thread        rosQueueThread;
        
        private:std::thread rosDataPublishThread;
        private:ros::Publisher data_pub;

    public: void Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/)
    {
      // Store the pointer to the model
      this->model = _parent;

       if (!ros::isInitialized())
            {
                int argc = 0;
                char **argv = NULL;
                ros::init(argc, argv, "gazebo_client", ros::init_options::NoSigintHandler);
            }


      this->pid = common::PID(1, 0.1, 0.01);

      this->rosNode.reset(new ros::NodeHandle("gazebo_client"));

      this->jointController = this->model->GetJointController();
      this->jointController->Reset();
      this->jointController->AddJoint(model->GetJoint("base_main"));
      this->jointController->AddJoint(model->GetJoint("arm_hinge"));
      this->jointController->AddJoint(model->GetJoint("hand_arm"));

       this->rosNode.reset(new ros::NodeHandle("gazebo_client"));
        this->rosNode->setCallbackQueue(&(this->rosQueue));

       ros::SubscribeOptions so =
  ros::SubscribeOptions::create<assignment_arm::arm_angle>(
      "/arm_joint_angles",
      1,
      boost::bind(&ArmAngles::OnRosMsg, this, _1),
      ros::VoidPtr(),
      &this->rosQueue);
    this->rosSub = this->rosNode->subscribe(so);

  this->rosQueueThread =
  std::thread(std::bind(&ArmAngles::QueueThread, this));
            
    }


    private: void QueueThread()
  {
    static const double timeout = 0.01;
    while (this->rosNode->ok())
    {
      this->rosQueue.callAvailable(ros::WallDuration(timeout));
    }
  }

    public: void OnRosMsg(const assignment_arm::arm_angle::ConstPtr &_msg){
        this.SetArmAngle("base_main",_msg->base_main);
        this.SetArmAngle("base_main",_msg->arm_hinge);
        this.SetArmAngle("base_main",_msg->hand_arm);
    }

    public: void OnUpdate()
    {
      // Apply a small linear velocity to the model.
      this->model->SetLinearVel(ignition::math::Vector3d(.3, 0, 0));
    }

    private: void SetArmAngle(std::string joint_name, float degree)
        {
            float rad = M_PI * degree / 180;
            std::string name = this->model->GetJoint(joint_name)->GetScopedName();
            this->jointController->SetPositionPID(name, pid);
            this->jointController->SetPositionTarget(name, rad);
            this->jointController->Update();
        }

  };

  // Register this plugin with the simulator
  GZ_REGISTER_MODEL_PLUGIN(ArmAngles)
}