#include "radioNode.h"

#define I2S_DOUT 25
#define I2S_BCLK 27
#define I2S_LRC 26

Audio audio;
const char *info;

radioNode::radioNode(const char* id, const char* name, const char* type) : HomieNode(id, name, type){
  defaultVolume = new HomieSetting<long>("volume", "Setting the volume level (range:0-21 default:0)");
}

bool radioNode::handleInput(const HomieRange& range, const String& property, const String& value){
  if(property == "volume"){
    if((uint8_t)value.toInt() >= 0 && (uint8_t)value.toInt() <= 21){
      volume = (uint8_t)value.toInt();
      setProperty("volume").send(String(volume));
      audio.setVolume(volume);
    }
  }

  if(property == "station"){
      setProperty("station").send(String(value.c_str()));
      audio.connecttohost(value.c_str());
  }
  return true;
}

void radioNode::radioSetup(){
    defaultVolume->setDefaultValue(0).setValidator([](float candidateVolume) {
    return (candidateVolume >= 0) && (candidateVolume <= 21);
  });
}

void radioNode::setup(){
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    advertise("volume").setRetained(true).setFormat("0-21").settable();
    advertise("station").setRetained(true).setFormat("String").settable();
    advertise("info").setRetained(false).settable();
}

void radioNode::loop(){
    audio.loop();
    //sendStreamInfo();
}

void radioNode::sendStreamInfo(){
   setProperty("info").send(String(info).c_str());
}

void audio_showstreamtitle(const char *info){
  Homie.getLogger() << "🔶 Title: " << info << endl;
  Serial.print("Title  "); Serial.println(info);
  //nfo = const_cast<char*>(info);
  //radioNode::sendStreamInfo();
  //setProperty("info").send(String(info));
}

/*
// optional
void audio_info(const char *info){
    Serial.print("info        "); Serial.println(info);
}
void audio_id3data(const char *info){  //id3 metadata
    Serial.print("id3data     ");Serial.println(info);
}
void audio_eof_mp3(const char *info){  //end of file
    Serial.print("eof_mp3     ");Serial.println(info);
}
void audio_showstation(const char *info){
    Serial.print("station     ");Serial.println(info);
}
void audio_showstreaminfo(const char *info){
    Serial.print("streaminfo  ");Serial.println(info);
}
void audio_bitrate(const char *info){
    Serial.print("bitrate     ");Serial.println(info);
}
void audio_commercial(const char *info){  //duration in sec
    Serial.print("commercial  ");Serial.println(info);
}
void audio_icyurl(const char *info){  //homepage
    Serial.print("icyurl      ");Serial.println(info);
}
void audio_lasthost(const char *info){  //stream URL played
    Serial.print("lasthost    ");Serial.println(info);
}
void audio_eof_speech(const char *info){
    Serial.print("eof_speech  ");Serial.println(info);
}
*/
