/*
http://tophits.radiomonster.fm/320.mp
https://icecast.omroepvenray.nl/lov.mp3
http://stream.radiofontan.ru:8000/radiofontan
http://pool.anison.fm:9000/AniSonFM(320)?nocache=0.98
http://musicbird.leanstream.co/JCB110-MP3  #FMみっきぃ
http://musicbird.leanstream.co/JCB068-MP3  #ウメダfm Be Happy!
https://icecast-zvezda.mediacdn.ru/radio/zvezda/zvezda_128
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
  Homie.setup();
}

void loop() {
  Homie.loop();
}
