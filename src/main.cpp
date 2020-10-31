#include <Homie.h>
#include "radioNode.h"

#define BRAND     "TSR"
#define FM_NAME   "The Smart Radio"
#define FM_VER    "0.0.1"

WiFiUDP ntpUDP;
radioNode RadioNode("radio", "online", "WiFi");

void setup() {
  Serial.begin(115200);
  Serial << endl << endl;
  Homie_setBrand(BRAND);
  Homie_setFirmware(FM_NAME, FM_VER);
  RadioNode.radioSetup();
  Homie.setup();
}

void loop() {
  Homie.loop();
}
