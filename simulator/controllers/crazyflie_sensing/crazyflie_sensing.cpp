/* Include the controller definition */
#include "crazyflie_sensing.h"
/* Function definitions for XML parsing */
#include <argos3/core/utility/configuration/argos_configuration.h>
/* 2D vector definition */
#include <argos3/core/utility/math/vector2.h>
/* Logging */
#include <argos3/core/utility/logging/argos_log.h>

const int MINIMUM_DISTANCE_FROM_OBSTACLE = 30;
const int MINIMUM_REST_DISTANCE_FROM_OBSTACLE = 20;
const int MAX_FOWARD_STEPS = 100;


/****************************************/
/****************************************/

CCrazyflieSensing::CCrazyflieSensing() :
   m_pcDistance(NULL),
   m_pcPropellers(NULL),
   m_pcRNG(NULL),
   m_pcRABA(NULL),
   m_pcRABS(NULL),
   m_pcPos(NULL),
   m_pcBattery(NULL),
   m_uiCurrentStep(0) {}

/****************************************/
/****************************************/

void CCrazyflieSensing::Init(TConfigurationNode& t_node) {
   try {
      /*
       * Initialize sensors/actuators
       */
      m_pcDistance   = GetSensor  <CCI_CrazyflieDistanceScannerSensor>("crazyflie_distance_scanner");
      m_pcPropellers = GetActuator  <CCI_QuadRotorPositionActuator>("quadrotor_position");
      /* Get pointers to devices */
      m_pcRABA   = GetActuator<CCI_RangeAndBearingActuator>("range_and_bearing");
      m_pcRABS   = GetSensor  <CCI_RangeAndBearingSensor  >("range_and_bearing");
      try {
         m_pcPos = GetSensor  <CCI_PositioningSensor>("positioning");
      }
      catch(CARGoSException& ex) {}
      try {
         m_pcBattery = GetSensor<CCI_BatterySensor>("battery");
      }
      catch(CARGoSException& ex) {}  
      this->socket_manager.ConnectToServer();
   }
   catch(CARGoSException& ex) {
      THROW_ARGOSEXCEPTION_NESTED("Error initializing the crazyflie sensing controller for robot \"" << GetId() << "\"", ex);
   }
   /*
    * Initialize other stuff
    */
   /* Create a random number generator. We use the 'argos' category so
      that creation, reset, seeding and cleanup are managed by ARGoS. */
   this->socket_manager.current_socket->emit("drone_connect");
   m_pcRNG = CRandom::CreateRNG("argos");
   transition_steps = 0;
   forward_steps = 0;
   m_uiCurrentStep = 0;
   CVector3 trans(0.0f, -0.1f, 0.0f);
   float random_angle_value = ((float) rand()/RAND_MAX )  * 2 * M_PI;
   random_angle.SetValue(random_angle_value);
   current_trajectory = trans;
   trajet = 0;
   Reset();
}

/****************************************/
/****************************************/

std::string enumToString(State state){
   switch(state) {
      case WAIT:
         return "Waiting";
      case TAKEOFF:
         return "Takeoff";
      case EXPLORE:
         return "Exploring";
      case AVOID:
         return "Exploring";
      case LAND:
         return "Landing";
      case RETURN_TO_BASE:
         return "Returning";
      default:
         return "UNKNOWN";
   }
}

void CCrazyflieSensing::set_zone_coordinates(){
   for (int i =0; i < 4; i++){
      zone_coordinates[i] =  this->socket_manager.zone_coordinates[i];
   }
}

void CCrazyflieSensing::ControlStep() {
   current_state = this->socket_manager.current_state;
   set_zone_coordinates();
   zone_specified = this->socket_manager.zone_specified;
   if (current_state == WAIT){
      LOG << "Mission has not started yet" << std::endl;
   }
   else if(current_state == TAKEOFF ){
      if (m_pcBattery->GetReading().AvailableCharge < 0.3){
         LOG << "Battery low cannot start mission" << std::endl;
      }
      else if (!TakeOff()){
         transition_steps++;
         LOG << "transition steps " << transition_steps << std::endl;
         if (transition_steps > 50){
            this->socket_manager.current_state = EXPLORE;
            transition_steps = 0;
         }
      }
      m_cInitialPosition = m_pcPos->GetReading().Position;
   }
   else if (current_state == EXPLORE ){
      if (!LookForObstacle() && in_zone_limit()){
         explore();
         forward_steps++;
         if (returning) LOG << "DONT FORGET RETURNING " << forward_steps << std::endl;
         if (returning && forward_steps > 30){
            forward_steps = 0;
            this->socket_manager.current_state = RETURN_TO_BASE;
         }
         else if (forward_steps >= MAX_FOWARD_STEPS){
            forward_steps = 0;
            changeDirection();
            this->socket_manager.current_state = AVOID;
         }
      }
      else{
         bool obstacles[4] = {false, false, false, false};
         obstacleManeuver(obstacles);
         forward_steps = 0;
         this->socket_manager.current_state = AVOID;
      }
   }
   else if (current_state == RETURN_TO_BASE){
      returning = true;
      CVector3 currentPosition = m_pcPos->GetReading().Position;
      if (!LookForObstacle() && in_zone_limit()){
         if (!returnToBase()){
            current_trajectory = CVector3(m_cInitialPosition.GetX()-currentPosition.GetX(), m_cInitialPosition.GetY() - currentPosition.GetY(), 0).Normalize() * 0.1f;
            LOG << "return coordinates (x,y,z) = (" << current_trajectory.GetX() << ","
            << current_trajectory.GetY() << ","
            << current_trajectory.GetZ() << ")" << std::endl; 
             LOG << "initial coordinates (x,y,z) = (" << m_cInitialPosition.GetX() << ","
            << m_cInitialPosition.GetY() << ","
            << m_cInitialPosition.GetZ() << ")" << std::endl; 
            explore();
         }
         else{
            this->socket_manager.current_socket->emit("end_mission");
            this->socket_manager.current_state = LAND;
         }
      }
      else{
         changeDirection();
         this->socket_manager.current_state = AVOID;
      }
   }
   else if (current_state == LAND){
      transition_steps++;
      if (transition_steps > 100){
        if (!Land()){
            LOG << "The drone is at rest, waiting for the next command" << std::endl;
            this->socket_manager.current_state = WAIT;
            transition_steps = 0;
            returning = false;
         }
      }
       
   }
   else if (current_state == AVOID){
      LOG << "transition steps for avoiding" << transition_steps << std::endl;
      transition_steps++;
      if (transition_steps > 35){
         this->socket_manager.current_state = EXPLORE;
         transition_steps = 0;
      }
   }
   LOG << "Current state is : " << enumToString(current_state) << std::endl;
   // Print current position.
   LOG << "Position (x,y,z) = (" << m_pcPos->GetReading().Position.GetX() << ","
       << m_pcPos->GetReading().Position.GetY() << ","
       << m_pcPos->GetReading().Position.GetZ() << ")" << std::endl; 
   // Print current battery level
   const CCI_BatterySensor::SReading& sBatRead = m_pcBattery->GetReading();
   LOG << "Battery level: " << sBatRead.AvailableCharge  << std::endl;

   if ( sBatRead.AvailableCharge <= 0.3 ){
      if (!returning) this->socket_manager.current_state = RETURN_TO_BASE;
      if (sBatRead.AvailableCharge == 0) this->socket_manager.current_state = LAND;
   }

   CCI_CrazyflieDistanceScannerSensor::TReadingsMap s_dist_read = 
      m_pcDistance->GetReadingsMap();
   auto iterDistRead = s_dist_read.begin();
   if (s_dist_read.size() == 4) {
      LOG << "Right dist: " << (iterDistRead++)->second  << std::endl;
      LOG << "Front dist: "  << (iterDistRead++)->second  << std::endl;
      LOG << "Left dist: "  << (iterDistRead++)->second  << std::endl;
      LOG << "Back dist: " << (iterDistRead++)->second  << std::endl;
   }
   this->setSensorData();
   this->updateState();
   this->updateData();
   m_uiCurrentStep++;
   }

void CCrazyflieSensing::updateState(){
   this->socket_manager.current_socket->emit("update_state", enumToString(current_state));
}

void CCrazyflieSensing::setSensorData(){
   CCI_CrazyflieDistanceScannerSensor::TReadingsMap s_dist_read = 
      m_pcDistance->GetReadingsMap();
   auto iterDistRead = s_dist_read.begin();
   if (s_dist_read.size() == 4) {
      for(int i=0;i<4;i++){
         this->sensor_data[i] = (iterDistRead++)->second;
      }
   }
}


void CCrazyflieSensing::changeDirection(){
   srand ( time(NULL) );
   float random_angle_value =  ( rand() % 2 ) * M_PI + M_PI/2;
   random_angle.SetValue(random_angle_value);
   ApplyMovement(-2 * current_trajectory);
   current_trajectory = current_trajectory.RotateZ(random_angle);
}

void CCrazyflieSensing::explore(){
   ApplyMovement(current_trajectory);
}

/****************************************/
/****************************************/

bool CCrazyflieSensing::TakeOff() {
   CVector3 cPos = m_pcPos->GetReading().Position;
   if(Abs(cPos.GetZ() - 0.40f) < 0.01f) return false;
   cPos.SetZ(0.4f);
   m_pcPropellers->SetAbsolutePosition(cPos);
   return true;
}

float CCrazyflieSensing::distance(float x1, float y1, float x2, float y2)
{
    // Calculating distance
    return sqrt(pow(x2 - x1, 2) +
                pow(y2 - y1, 2) * 1.0f);
}

bool CCrazyflieSensing::returnToBase() {
   CVector3 currentPosition = m_pcPos->GetReading().Position;
   float distanceFromBase = distance( m_cInitialPosition.GetX(),  m_cInitialPosition.GetY(), currentPosition.GetX(), currentPosition.GetY());
   if (distanceFromBase < 0.5f) return true;
   return false;
}


/****************************************/
/****************************************/

bool CCrazyflieSensing::Land() {
   CVector3 cPos = m_pcPos->GetReading().Position;
   if(Abs(cPos.GetZ()) < 0.01f) return false;
   cPos.SetZ(0.0f);
   m_pcPropellers->SetAbsolutePosition(cPos);
   return true;
}


void CCrazyflieSensing::ApplyMovement(CVector3 trans){
   trajet++;
   m_pcPropellers->SetRelativePosition(trans);
}

/****************************************/
/****************************************/

void CCrazyflieSensing::updateData(){
   // emit multiple arguments
   sio::message::list li(GetId());
   CVector3 currentPosition = m_pcPos->GetReading().Position;
   //state
   std::string state_string = enumToString(current_state);
   li.push(sio::string_message::create(state_string));
   //battery 
   // position data
   li.push(sio::double_message::create(currentPosition.GetX()));
   li.push(sio::double_message::create(currentPosition.GetY()));
   li.push(sio::double_message::create(currentPosition.GetZ()));
   // sensor data
   li.push(sio::double_message::create(this->sensor_data[0]));
   li.push(sio::double_message::create(this->sensor_data[2]));
   li.push(sio::double_message::create(this->sensor_data[1]));
   li.push(sio::double_message::create(this->sensor_data[3]));
   li.push(sio::double_message::create(m_pcBattery->GetReading().AvailableCharge));
   li.push(sio::double_message::create(trajet * 0.1f));
   this->socket_manager.current_socket->emit("update_drone_data",li);
}

void CCrazyflieSensing::obstacleManeuver(bool obstacles[]){
   srand ( time(NULL) );
   float random_angle_value = (float) rand()/RAND_MAX * M_PI/2 + M_PI/2;
   int orientation = ((float) rand()/RAND_MAX < 1/2) ? 1 : -1;
   random_angle.SetValue( orientation * random_angle_value);
   ApplyMovement(-2 * current_trajectory);
   current_trajectory = current_trajectory.RotateZ(random_angle);
}

bool CCrazyflieSensing::obstacleDetected(int orientation){
   if (orientation == 0 or orientation == 2) {
      return this->sensor_data[orientation] < MINIMUM_DISTANCE_FROM_OBSTACLE && Abs(current_trajectory.GetY()) > 0.01 && this->sensor_data[orientation] > 0;
   }
   else{
      return this->sensor_data[orientation] < MINIMUM_DISTANCE_FROM_OBSTACLE && Abs(current_trajectory.GetX()) > 0.01 && this->sensor_data[orientation] > 0;
   }
}

bool CCrazyflieSensing::LookForObstacle(){
   bool obstacles[4] = {false, false, false, false};
   bool obstacleExists = false;
   for (int i = 0; i < 4; i++){
      obstacles[i] = obstacleDetected(i);
      if (obstacles[i]) obstacleExists = true;
   }
   return obstacleExists;
}

bool CCrazyflieSensing::in_zone_limit(){
   CVector3 currentPosition = m_pcPos->GetReading().Position;
   if (!zone_specified) return true;
   printf("X position %f \n", currentPosition.GetX());
   printf("X MIN ZONE %f \n", zone_coordinates[0]);
   printf("X MAX ZONE %f \n", zone_coordinates[0] + zone_coordinates[1]);
   if (currentPosition.GetX() - 0.1f <= zone_coordinates[0] || currentPosition.GetX() + 0.1f >= zone_coordinates[0] + zone_coordinates[2]) return false;
   if (currentPosition.GetY() + 0.1f >= zone_coordinates[1] || currentPosition.GetY() - 0.1f <= zone_coordinates[1] - zone_coordinates[3]) return false;
   return true;
}





/****************************************/
/****************************************/

void CCrazyflieSensing::Reset() {
}

/****************************************/
/****************************************/


/*
 * This statement notifies ARGoS of the existence of the controller.
 * It binds the class passed as first argument to the string passed as
 * second argument.
 * The string is then usable in the XML configuration file to refer to
 * this controller.
 * When ARGoS reads that string in the XML file, it knows which controller
 * class to instantiate.
 * See also the XML configuration files for an example of how this is used.
 */
REGISTER_CONTROLLER(CCrazyflieSensing, "crazyflie_sensing_controller")
