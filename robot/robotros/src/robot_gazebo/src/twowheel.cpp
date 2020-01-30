#include <functional>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <ignition/math/Vector3.hh>

namespace gazebo
{
  class TwoWheel : public ModelPlugin
  {
    public:
        float change = 0.0001;
        float turn = 0;

    public: void Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/)
    {
      printf("Loaded plugin\n");

      // Store the pointer to the model
      this->model = _parent;

      // Listen to the update event. This event is broadcast every
      // simulation iteration.
      this->updateConnection = event::Events::ConnectWorldUpdateBegin(
          std::bind(&TwoWheel::OnUpdate, this));
    }

    // Called by the world update start event
    public: void OnUpdate()
    {
      // Apply a small linear velocity to the model.
      //this->model->SetLinearVel(ignition::math::Vector3d(.3, 0, 0));

      turn = turn + change;

      if (turn >= 1 || turn <= 0) {
          change = change * -1;
	  if (turn > 1) {
		turn = 1;
	  }
	  if (turn < 0) {turn = 0;}
      }

      this->model->GetJoint("left_wheel_hinge")->SetVelocity(0, -2 - turn);
      this->model->GetJoint("right_wheel_hinge")->SetVelocity(0, turn - 3);
    }

    // Pointer to the model
    private: physics::ModelPtr model;

    // Pointer to the update event connection
    private: event::ConnectionPtr updateConnection;
  };

  // Register this plugin with the simulator
  GZ_REGISTER_MODEL_PLUGIN(TwoWheel)
}
