#include "radioNode.h"

#define SPI_MOSI      23
#define SPI_MISO      19
#define SPI_SCK       18
#define VS1053_CS     2
#define VS1053_DCS    4
#define VS1053_DREQ   36

VS1053 mp3(VS1053_CS, VS1053_DCS, VS1053_DREQ);

radioNode::radioNode(const char* id, const char* name, const char* type) : HomieNode(id, name, type){
  defaultVolume = new HomieSetting<long>("volume", "Setting the volume level (range:0-21 default:0)");
}

bool radioNode::handleInput(const HomieRange& range, const String& property, const String& value){
  if(property == "volume"){
    if((uint8_t)value.toInt() >= 0 && (uint8_t)value.toInt() <= 21){
      volume = (uint8_t)value.toInt();
      setProperty("volume").send(String(volume));
      mp3.setVolume(volume);
    }
  }

  if(property == "station"){
      setProperty("station").send(String(value.c_str()));
      mp3.connecttohost(value.c_str());
  }
  return true;
}

void radioNode::radioSetup(){
    defaultVolume->setDefaultValue(0).setValidator([](float candidateVolume) {
    return (candidateVolume >= 0) && (candidateVolume <= 21);
  });
}

void radioNode::setup(){
    SPI.begin();
    mp3.begin();
        uint8_t u8_tone[4];
        u8_tone[0] = 0;  // Treble Gain set (0...15)
        u8_tone[1] = 14; // Treble Freq set (0...14)
        u8_tone[2] = 15; // Bass Gain set   (0...15)
        u8_tone[3] = 13; // Bass Freq set   (0...13)
    mp3.setTone(u8_tone);
    advertise("volume").setRetained(true).setFormat("0-21").settable();
    advertise("station").setRetained(true).setFormat("String").settable();
}

void radioNode::loop(){
    mp3.loop();
}

void vs1053_showstreamtitle(const char *info){
  Homie.getLogger() << "🔶 Title: " << info << endl;
}

void radioNode::say(const char *proffer, const char *lang){
    mp3.connecttospeech(proffer, lang);
}
/*
// optional
void vs1053_info(const char *info){
    Serial.print("info        "); Serial.println(info);
}
void vs1053_id3data(const char *info){  //id3 metadata
    Serial.print("id3data     ");Serial.println(info);
}
void vs1053_eof_mp3(const char *info){  //end of file
    Serial.print("eof_mp3     ");Serial.println(info);
}
void vs1053_showstation(const char *info){
    Serial.print("station     ");Serial.println(info);
}
void vs1053_showstreaminfo(const char *info){
    Serial.print("streaminfo  ");Serial.println(info);
}
void vs1053_bitrate(const char *info){
    Serial.print("bitrate     ");Serial.println(info);
}
void vs1053_commercial(const char *info){  //duration in sec
    Serial.print("commercial  ");Serial.println(info);
}
void vs1053_icyurl(const char *info){  //homepage
    Serial.print("icyurl      ");Serial.println(info);
}
void vs1053_lasthost(const char *info){  //stream URL played
    Serial.print("lasthost    ");Serial.println(info);
}
void vs1053_eof_speech(const char *info){
    Serial.print("eof_speech  ");Serial.println(info);
}
*/
