#include "p2p.h"
#include "transmitter.h"
#define MESSAGE_LENGHT 10

void p2p_callback_handler(P2PPacket *p)
{

  // Parse the data from the other crazyflie and print it
  uint8_t delta_x = abs(log_data.initial_position.x - log_data.position.x);
  uint8_t delta_y = abs(log_data.initial_position.y - log_data.position.y);
  uint16_t distance = sqrt(pow(delta_x, 2) + pow(delta_y, 2));

  uint8_t distance_d2;
  static char msg[MESSAGE_LENGHT + 1];

  memcpy(&msg, &p->data[1], sizeof(char)*MESSAGE_LENGHT);


  distance_d2 = atoi(msg);

  if(distance_d2 < distance)
  {
    ledSet(LED_RED_L, true);
  }
  else
  {
    ledSet(LED_GREEN_L, true); 
  }
}

void send_P2P_packet()
{

  // Initialize the p2p packet 
  static P2PPacket p_reply;
  p_reply.port=0x00;
  
  // Get the current address of the crazyflie and obtain
  //   the last two digits and send it as the first byte
  //   of the payload
  
  uint64_t address = configblockGetRadioAddress();
  uint8_t my_id =(uint8_t)((address) & 0x00000000ff);
  p_reply.data[0]=my_id;

  //Put a string in the payload

  // Set the size, which is the amount of bytes the payload with ID and the string 

  // Register the callback function so that the CF can receive packets as well.

  // while(true)
  // {

    uint8_t delta_x = abs(log_data.initial_position.x - log_data.position.x);
    uint8_t delta_y = abs(log_data.initial_position.y - log_data.position.y);

    int distance = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
    
    char str[10];
    itoa(distance,str,10);
    memcpy(&p_reply.data[1], &str, sizeof(char)*MESSAGE_LENGHT);

  p_reply.size =sizeof(char)*MESSAGE_LENGHT + 1;

  p2pRegisterCB(p2p_callback_handler);

    // Send a message every 2 seconds
    //   Note: if they are sending at the exact same time, there will be message collisions, 
    //    however since the@Chargé.e  j'ai une question par rappy are sending every 2 seconds, and they are not started up at the same
    //    time and their internal clocks are different, there is not really something to worry about

    vTaskDelay(M2T(500));
    radiolinkSendP2PPacketBroadcast(&p_reply);
  // }

  
  
}
