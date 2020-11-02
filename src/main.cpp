/*
http://tophits.radiomonster.fm/320.mp
https://icecast.omroepvenray.nl/lov.mp3
http://stream.radiofontan.ru:8000/radiofontan
*/

#include <Homie.h>
#include "radioNode.h"

#define BRAND     "TSR"
#define FM_NAME   "The Smart Radio"
#define FM_VER    "0.0.1"

radioNode RadioNode("radio", "network", "WiFi");

void setup() {
  Serial.begin(115200);
  Serial << endl << endl;
  Homie_setBrand(BRAND);
  Homie_setFirmware(FM_NAME, FM_VER);

  RadioNode.radioSetup();

  Homie.disableLedFeedback();
  Homie.disableResetTrigger();

  Homie.setup();
  RadioNode.say("お待たせしました。", "ja");
}

void loop() {
  Homie.loop();
}
