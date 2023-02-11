
#include "start.h"
#include "data.h"
#include "math.h"
#include "identify.h"
#include "sensor_module.h"
#include "p2p.h"

#define MAX(a,b) ((a>b)?a:b)
#define MIN(a,b) ((a<b)?a:b)

extern SensorModule sensor;
extern bool P2P;

static int direction_counter = 0;
int turnDirection = 0;
float yaw_rate_comp = 0.0f;
float velocity_front = 0.0f;
float velocity_side = 0.0f;
  
static const float vel_max = 1.0f;
static const uint16_t radius = 325;
// static float factor = vel_max / radius;

void setHoverSetpoint(setpoint_t *setpoint, float x, float y, float z, float yawrate)
{
  setpoint->mode.z = modeAbs;
  setpoint->position.z = z;
  setpoint->mode.x = modeVelocity;
  setpoint->mode.y = modeVelocity;
  setpoint->velocity.x = x;
  setpoint->velocity.y = y;

  setpoint->mode.yaw = modeVelocity;
  setpoint->attitudeRate.yaw = yawrate;
}

void start_mission() 
{

  if(P2P)
  {
    void send_P2P_packet();
  }  

  static const float height_sp = 0.3f;

  static setpoint_t setpoint;

  __attribute__((__unused__)) paramVarId_t idPositioningDeck = paramGetVarId("deck", "bcFlow2");
  __attribute__((__unused__)) paramVarId_t idMultiranger = paramGetVarId("deck", "bcMultiranger");

  // uint8_t multirangerInit = paramGetUint(idMultiranger);
  // uint8_t positioningDeckInit = paramGetUint(idPositioningDeck);
  
  // We read the current position as the start position of the drone
  __attribute__((__unused__)) float startPosX = log_data.position.x;
  __attribute__((__unused__)) float startPosY = log_data.position.y;

  uint16_t left = sensor.get_left_distance();
  uint16_t right = sensor.get_right_distance();
  uint16_t front = sensor.get_front_distance();
  uint16_t back = sensor.get_back_distance();

  uint16_t left_o = radius - MIN(left, radius);
  uint16_t right_o = radius - MIN(right, radius);
  uint16_t front_o = radius - MIN(front, radius);
  uint16_t back_o = radius - MIN(back, radius);

  // float yaw_rate_comp = 0.0f;
  // float velocity_front = 0.0f;
  // float velocity_side = 0.0f;
  
  vTaskDelay(M2T(100));
  
  if (front_o != 0) {
    velocity_front = -0.3f;
    velocity_side = 0.0f;
    yaw_rate_comp = 0.0f;
    setHoverSetpoint(&setpoint, velocity_front, velocity_side, height_sp, yaw_rate_comp);
    commanderSetSetpoint(&setpoint, 3);
    vTaskDelay(M2T(750));
    
    velocity_front = 0.0f;
    if(direction_counter > 5)
    {
      turnDirection = rand()%2;
      direction_counter = 0;
    }

    if(left_o == 0 && right_o ==0 )
    {
      if(turnDirection == 1){
        
        velocity_side = 0.2f;

      }else 
      {
        velocity_side = -0.2f;
      }

      setHoverSetpoint(&setpoint, velocity_front, velocity_side, height_sp, yaw_rate_comp);
      commanderSetSetpoint(&setpoint, 3);
      vTaskDelay(M2T(750));
    }
    else if(left_o != 0 && right_o == 0)
    {
      velocity_side = -0.2f;
      setHoverSetpoint(&setpoint, velocity_front, velocity_side, height_sp, yaw_rate_comp);
      commanderSetSetpoint(&setpoint, 3);
      vTaskDelay(M2T(750));

    }
    else if(right_o != 0 && left_o == 0)
    {
      velocity_side = 0.2f;
      setHoverSetpoint(&setpoint, velocity_front, velocity_side, height_sp, yaw_rate_comp);
      commanderSetSetpoint(&setpoint, 3);
      vTaskDelay(M2T(750));
    }
    else if(right_o != 0 && left_o != 0)
    {

      velocity_front = -0.3f;
      velocity_side = 0.0f;
      yaw_rate_comp = 0.0f;
      setHoverSetpoint(&setpoint, velocity_front, velocity_side, height_sp, yaw_rate_comp);
      commanderSetSetpoint(&setpoint, 3);
      vTaskDelay(M2T(750));
    }
    direction_counter++;
  }
  else if(right_o != 0)
  {
    velocity_front = 0.0f; 
    velocity_side = 0.2f;
    setHoverSetpoint(&setpoint, velocity_front, velocity_side, height_sp, yaw_rate_comp);
    commanderSetSetpoint(&setpoint, 3);
    vTaskDelay(M2T(750));

  }
  else if(left_o != 0)
  {
    velocity_front = 0.0f; 
    velocity_side = -0.2f;
    setHoverSetpoint(&setpoint, velocity_front, velocity_side, height_sp, yaw_rate_comp);
    commanderSetSetpoint(&setpoint, 3);
    vTaskDelay(M2T(750));
    
  }
  else if(back_o != 0)
  {
    velocity_front = 0.2f; 
    velocity_side = 0.0f;
    setHoverSetpoint(&setpoint, velocity_front, velocity_side, height_sp, yaw_rate_comp);
    commanderSetSetpoint(&setpoint, 3);
    vTaskDelay(M2T(750));
    
  }
  else 
  {
    velocity_front = 0.3f; 
    velocity_side = 0.0f;
    setHoverSetpoint(&setpoint, velocity_front, velocity_side, height_sp, yaw_rate_comp);
    commanderSetSetpoint(&setpoint, 3);
    vTaskDelay(M2T(500));
  }
}

void end_mission() 
{
  static setpoint_t setpoint;

  setHoverSetpoint(&setpoint, 0, 0, 0.15, 0);
  commanderSetSetpoint(&setpoint, 3);
  vTaskDelay(M2T(100));

  memset(&setpoint, 0, sizeof(setpoint_t));
  commanderSetSetpoint(&setpoint, 3);

}

