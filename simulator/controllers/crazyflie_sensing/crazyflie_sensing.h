/*
 * AUTHORS: Carlo Pinciroli <cpinciro@ulb.ac.be>
 *          Pierre-Yves Lajoie <lajoie.py@gmail.com>
 *
 * An example crazyflie drones sensing.
 *
 * This controller is meant to be used with the XML file:
 *    experiments/foraging.argos
 */

#ifndef CRAZYFLIE_SENSING_H
#define CRAZYFLIE_SENSING_H

/*
 * Include some necessary headers.
 */
/* Definition of the CCI_Controller class. */
#include <argos3/core/control_interface/ci_controller.h>
/* Definition of the crazyflie distance sensor */
#include <argos3/plugins/robots/crazyflie/control_interface/ci_crazyflie_distance_scanner_sensor.h>
/* Definition of the crazyflie position actuator */
#include <argos3/plugins/robots/generic/control_interface/ci_quadrotor_position_actuator.h>
/* Definition of the crazyflie position sensor */
#include <argos3/plugins/robots/generic/control_interface/ci_positioning_sensor.h>
/* Definition of the crazyflie range and bearing actuator */
#include <argos3/plugins/robots/generic/control_interface/ci_range_and_bearing_actuator.h>
/* Definition of the crazyflie range and bearing sensor */
#include <argos3/plugins/robots/generic/control_interface/ci_range_and_bearing_sensor.h>
/* Definition of the crazyflie battery sensor */
#include <argos3/plugins/robots/generic/control_interface/ci_battery_sensor.h>
/* Definitions for random number generation */
#include <argos3/core/utility/math/rng.h>
#include <time.h>
#include "socket_manager.h"


enum direction {
   Right, Left, Front, Back
};

/*
 * All the ARGoS stuff in the 'argos' namespace.
 * With this statement, you save typing argos:: every time.
 */
using namespace argos;
/*
 * A controller is simply an implementation of the CCI_Controller class.
 */
class CCrazyflieSensing : public CCI_Controller {

public:

   /* Class constructor. */
   CCrazyflieSensing();
   /* Class destructor. */
   virtual ~CCrazyflieSensing() {}

   /*
    * This function initializes the controller.
    * The 't_node' variable points to the <parameters> section in the XML
    * file in the <controllers><footbot_foraging_controller> section.
    */
   virtual void Init(TConfigurationNode& t_node);

   /*
    * This function is called once every time step.
    * The length of the time step is set in the XML file.
    */
   virtual void ControlStep();
   void obstacleManeuver();
   /*
    * This function resets the controller to its state right after the
    * Init().
    * It is called when you press the reset button in the GUI.
    */
   virtual void Reset();

   /*
    * Called to cleanup what done by Init() when the experiment finishes.
    * In this example controller there is no need for clean anything up,
    * so the function could have been omitted. It's here just for
    * completeness.
    */
   virtual void Destroy() {}

   /*
    * This function lifts the drone from the ground
    */
   bool TakeOff();

   /*
    * This function returns the drone to the ground
    */
   bool Land();

   void updateData();

   void updateState();
   void explore();
   void setSensorData();
   void ApplyMovement(CVector3 trans);
   bool LookForObstacle();
   void Move(direction direct, CVector3 *trans, float step);
   void obstacleManeuver(bool obstacles[]);
   bool obstacleDetected(int orientation);
   void changeDirection();
   float distance(float x1, float y1, float x2, float y2);
   bool returnToBase();
   bool in_zone_limit();
   void set_zone_coordinates();


private:

   /* Pointer to the crazyflie distance sensor */
   CCI_CrazyflieDistanceScannerSensor* m_pcDistance;

    /* Pointer to the position actuator */
   CCI_QuadRotorPositionActuator* m_pcPropellers;
   
   /* Pointer to the range and bearing actuator */
   CCI_RangeAndBearingActuator*  m_pcRABA;

   /* Pointer to the range and bearing sensor */
   CCI_RangeAndBearingSensor* m_pcRABS;

   /* Pointer to the positioning sensor */
   CCI_PositioningSensor* m_pcPos;

   /* Pointer to the battery sensor */
   CCI_BatterySensor* m_pcBattery;

   /* The random number generator */
   CRandom::CRNG* m_pcRNG;

   double sensor_data[4];

   /* Current step */
   uint m_uiCurrentStep;
    
   /* Initial Position */ 
   CVector3 m_cInitialPosition;
   float zone_coordinates[4] = {0.0, 0.0, 0.0, 0.0};
   bool zone_specified;
   State current_state;
   int transition_steps = 0;
   bool returning = false;
   int forward_steps = 0;
   SocketManager socket_manager;
   CRadians random_angle;
   int next_direction = 0;
   int trajet = 0;
   CVector3 current_trajectory = CVector3(0.0f, 0.1f, 0.0f);
};

#endif
