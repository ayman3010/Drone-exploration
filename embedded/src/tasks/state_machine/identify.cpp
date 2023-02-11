#include "identify.h"

void identify_blue() {

  for(unsigned int i = 0; i < 3; i++) {
    vTaskDelay(M2T(200));
    ledSet(LED_BLUE_L, true);
    vTaskDelay(M2T(200));
    ledSet(LED_BLUE_L, false);
  }
}

void identify_green() {

  for(unsigned int i = 0; i < 3; i++) {
    vTaskDelay(M2T(200));
    ledSet(LED_GREEN_L, true);
    vTaskDelay(M2T(200));
    ledSet(LED_GREEN_L, false);
  }
}
