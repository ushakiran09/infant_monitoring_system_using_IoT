#include <SoftwareSerial.h>
#include "SD.h" // enable reading and writing on sd cards
#include "TMRpcm.h" //play  WAV audio files from sd card
#include "SPI.h" //allows to communicate with SPI(serial peripheral interface) devices with arduino as a control device
#define soundpin A2
#define sd 4 // to select pin for sd card
const int threshold=60;  // By www.andprof.com
TMRpcm tmrpcm;
void setup() {
tmrpcm.speakerPin = 9;
Serial.begin(115200);
if (!SD.begin(sd)) {    //see if the card is present and can be initialized
   Serial.println("sd fails"); 
    return;                               //don't do anything more if not
  }
tmrpcm.setVolume(6);    
}
  void play(){
  tmrpcm.stopPlayback();
  tmrpcm.play("1.wav");         //the sound file "1" will play each time the arduino powers up, or is reset
  delay(240000);
tmrpcm.play("2.wav",45); 
delay(240000);

delay(100);
return;
}
void loop()
{
 int soundsens=analogRead(soundpin);
if (soundsens>=threshold) {
     delay(1000);
Serial.println("Sound detected ");
play();
}
}


