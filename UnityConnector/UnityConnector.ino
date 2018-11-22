#include <SerialCommand.h>
#include<Wire.h>
#include "pitches.h"
const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int minVal=265;
int maxVal=402;

double x;
double y;
double z;
SerialCommand sCmd;

int clickm[] = {NOTE_B2};
int clickNotes[] = {2};

int blipm[] = {NOTE_B4};
int blipNotes[] = {2};

int breakm[] = {NOTE_E5};
int breakNotes[] = {2};


int playing = 0;
int* melody;
int startup[] = {
  NOTE_E5, NOTE_E5, 0, NOTE_E5, 0, NOTE_C5, NOTE_E5, 0, NOTE_G5, 0, 0, NOTE_G4, 0, 0
};
int* noteDurations;
int startNotes[] = {
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 8, 8, 4
};
int timesup[] = {
  NOTE_C5, 0, 0, NOTE_G4, 0, NOTE_E4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_GS4, NOTE_AS4, NOTE_GS4, NOTE_E4, NOTE_D4, NOTE_E4
};
int timesupNotes[] = {
  8, 8, 8, 8, 4, 4, 6, 6, 6, 6, 6, 6, 8, 8, 2
};
int melodyLength = 14;
float songDelay = 0;
float songMillis = 0;
void playSong(){
  songDelay -= millis() - songMillis;
  songMillis = millis();
  if (playing > melodyLength){
    if (songDelay <= 0){
      noTone(10);
      noTone(11);
    }
    return;
  }
  
  if (songDelay <= 0){
    int noteDuration = 1000 / noteDurations[playing];
    tone(10, melody[playing], noteDuration);
    tone(11, melody[playing], noteDuration);
    songDelay = noteDuration;
    playing++;
  }
  
}
void setup() {
  Serial.begin(9600);
  while (!Serial);

  sCmd.addCommand("CLICK", clickHandler);
  sCmd.addCommand("BLIP", blipHandler);
  sCmd.addCommand("BREAK", breakHandler);
  sCmd.addCommand("CONNECT", connectHandler);
  sCmd.addCommand("TIMEUP", timeupHandler);
  //sCmd.setDefaultHandler(errorHandler);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  melody = startup;
  noteDurations = startNotes;
}

void loop() {
  playSong();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  int xAng = map(AcX,minVal,maxVal,-90,90);
  int yAng = map(AcY,minVal,maxVal,-90,90);
  int zAng = map(AcZ,minVal,maxVal,-90,90);

  x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
  y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
  z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
  Serial.println(z);
  // Your operations here

  if (Serial.available() > 0)
    sCmd.readSerial();

  delay(100);  
}

void clickHandler ()
{
  playing = 0;
  melodyLength = 1;
  melody = clickm;
  noteDurations = clickNotes;
}
void blipHandler ()
{
  playing = 0;
  melodyLength = 1;
  melody = blipm;
  noteDurations = blipNotes;
}
void breakHandler ()
{
  playing = 0;
  melodyLength = 1;
  melody = breakm;
  noteDurations = breakNotes;
}
void connectHandler ()
{
  playing = 0;
  melodyLength = 14;
  melody = startup;
  noteDurations = startNotes;
}
void timeupHandler ()
{
  playing = 0;
  melodyLength = 15;
  melody = timesup;
  noteDurations = timesupNotes;
}

void echoHandler ()
{
  char *arg;
  arg = sCmd.next();
  if (arg != NULL)
    Serial.println(arg);
  else
    Serial.println("nothing to echo");
}
