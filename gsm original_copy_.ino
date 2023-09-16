#include <SoftwareSerial.h>
#include "Adafruit_FONA.h"
#include <dht.h>

#define FONA_RX            2
#define FONA_TX            3
#define FONA_RST           4
#define DHTPIN 7     
#define soundpin A2
const int threshold=30;

#define DHTTYPE DHT11     // DHT 11
#define moisture A0 
dht DHT;
#define FONA_RI_INTERRUPT  0
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
 
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);


char PHONE_1[21] = "+918618018829"; // Enter your Mobile Number
char tempalert[141]= "Temperature increased"  ; 
char soundalert[141]= "Sound detected"  ;
char moisalert[141]= "Moisture detected"  ;
void setup()
{
  Serial.begin(115200);
  Serial.println(F("Initializing....(May take 3 seconds)"));
  delay(5000);
  fonaSS.begin(9600); // if you're using software serial
  if (! fona.begin(fonaSS)) {           // can also try fona.begin(Serial1) 
    Serial.println(F("Couldn't find FONA"));
    while (1);
  }
   fona.print ("AT+CSMP=17,167,0,0\r");
    Serial.println(F("FONA is OK"));

}
void loop(){
 int soundsens=analogRead(soundpin); 
int s=soundsens;
if(s>threshold){
  Serial.println("sound detected");
  make_multi_call();
  send_multi_sms();
}

int chk = DHT.read11(DHTPIN);
  
  if(DHT.temperature>15 )
  {    
     Serial.println("Temperature Alert"); 
     make_multi_call(); 
     send_multi_sms();
   }
  
  
int SensorValue=analogRead(moisture);
Serial.println(SensorValue);
Serial.println("-");
if(SensorValue>370)
{
  Serial.println("Water");
  make_multi_call();
  send_multi_sms();
}
}

void send_multi_sms()
{
  if(PHONE_1 != ""){
    Serial.print("Phone 1: ");
    int soundsens=analogRead(soundpin); 
    int s=soundsens;
    int SensorValue=analogRead(moisture);
    if (s>threshold){
    fona.sendSMS(PHONE_1,soundalert);
    }
    else if(SensorValue>370 ){
      fona.sendSMS(PHONE_1,moisalert);
    }
    else if(DHT.temperature>15 ){
      fona.sendSMS(PHONE_1,tempalert);
    }
  }
   
}
void make_multi_call()
{
  if(PHONE_1 != ""){
    Serial.print("Phone 1: ");
    int soundsens=analogRead(soundpin); 
    int s=soundsens;
    if (s>threshold){
    make_call(PHONE_1);
    delay(10000);
  }
  } 
}

void make_call(String phone)
{
    Serial.println("calling....");
    fona.println("ATD"+phone+";");
    delay(30000); //20 sec delay
    fona.println("ATH");
    delay(1000); //1 sec delay
}

