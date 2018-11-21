
#include "pitches.h"
#include<Wire.h>
//#include <Scheduler.h>

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int minVal=265;
int maxVal=402;

double x;
double y;
double z;
bool gyroTriggered = true;

enum GameState{
  CALIBRATE, SELECT, PLAY, END
};
float songMillis = 0;

GameState state = CALIBRATE;
int score = 0;
float timer = 0;
int theme = 0;
int prompt = 0;
String promptName = "";
int themeNum = 3;
float initialZ = 0;
float lastMillis = 0;

int click[] = {NOTE_B3};
int clickNotes[] = {2};


int playing = 0;
int* melody;
int startup[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
int* noteDurations;
int startNotes[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
int melodyLength = 8;
float songTime = 0;
void playSong(){
  if (playing > melodyLength){
    noTone(10);
    noTone(11);
    return;
  }
  songTime += millis() - songMillis;
  songMillis = millis();
  if (((int)(songTime / 1000)) == playing){
    int noteDuration = 1000 / noteDurations[playing];
    tone(10, melody[playing], noteDuration);
    tone(11, melody[playing], noteDuration);
    playing++;
  }
  
}

void setup() {
  melody = startup;
  noteDurations = startNotes;
  songMillis = millis();
  //tone(10, 147, 125);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
  // put your setup code here, to run once:
  timer = 10000;
  
}
void loop() {
  readGyro();
  playSong();
  if (timer > 0){
    timer -= (millis() - lastMillis);
  }
  lastMillis = millis();
  if (state == CALIBRATE){
    displayText("Calibrating...");
    if (timer <= 0){
      Serial.println("Set position: ");
      initialZ = z;
      Serial.println(initialZ);
      
      state = SELECT;
    }
    
  }
  if (state == SELECT){
    displayText(theme == 0 ? "Waterloo Memes" : (theme == 1 ? "Movies" : "Impressions"));
    if (timer <= 0){
      timer = 1000;
      theme++;
      theme %= themeNum;
    }
    if (gyro()){
      
      if (theme == 0){
        String promptWaterloo[] = {"Mr Goose", "SYDE", "LOO! LOO! LOO!", "WEEF TAs", "Join the Slack", "Hell week", "Ideas Clinic", "Cindy?", "Baklava", "Edcom", "Bo Peng", "AIF", "Side projects", "Schulich Leaders", "The Arts Faculty"};
        
        promptName = promptWaterloo[rand() % 15];
      }
      else if (theme == 1){
        String promptMovies[] = {"Mean Girls", "Shrek 2", "The Incredibles", "The Godfather", "Kill Bill", "Pulp Fiction", "Pitch Perfect", "21 Jump Street", "Titanic", "La la Land", "Breakfast Club", "Clueless", "Stand By Me", "Casablanca", "Cinderella"};
        
        promptName = promptMovies[rand() % 15];
      }
      else{
        String promptImpressions[] = {"Irish", "Hitler", "Soviet Russia", "CS GO player", "Texan", "Donald Trump", "Chris Walken", "Shrek", "French", "Newfoundland", "Valley Girl", "Surfer", "Obama", "Tyler Perry", "Edna Mode"};
        promptName = promptImpressions[rand() % 15];
      }
      timer = 60000;
      state = PLAY;
    }
  }
  if (state == PLAY){
    displayText(promptName);
    if (gyro()){
      
      score++;
      if (theme == 0){
        String promptWaterloo[] = {"Mr Goose", "SYDE", "LOO! LOO! LOO!", "WEEF TAs", "Join the Slack", "Hell week", "Ideas Clinic", "Cindy?", "Baklava", "Edcom", "Bo Peng", "AIF", "Side projects", "Schulich Leaders", "The Arts Faculty"};
        
        promptName = promptWaterloo[rand() % 15];
      }
      else if (theme == 1){
        String promptMovies[] = {"Mean Girls", "Shrek 2", "The Incredibles", "The Godfather", "Kill Bill", "Pulp Fiction", "Pitch Perfect", "21 Jump Street", "Titanic", "La la Land", "Breakfast Club", "Clueless", "Stand By Me", "Casablanca", "Cinderella"};
        
        promptName = promptMovies[rand() % 15];
      }
      else{
        String promptImpressions[] = {"Irish", "Hitler", "Soviet Russia", "CS GO player", "Texan", "Donald Trump", "Chris Walken", "Shrek", "French", "Newfoundland", "Valley Girl", "Surfer", "Obama", "Tyler Perry", "Edna Mode"};
        promptName = promptImpressions[rand() % 15];
      }
      
    }
    if (timer <= 0){
      state = END;
      timer = 5000;
      
    }
  }
  if (state == END){
    displayText("Score: " + score);
    if (timer <= 0){
      state = SELECT;
      timer = 1000;
    }
  }
  
  
}
void displayText(String toDisplay){
  
}
void readGyro(){
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

}

bool gyro(){
  
  bool flipped = diff(initialZ, z) > 100;
  bool trigger = flipped && !gyroTriggered;
  if (flipped)gyroTriggered = true;
  if (diff(initialZ, z) < 50 && gyroTriggered){
    gyroTriggered = false;
    Serial.print("Untriggered: ");
    Serial.println(z);
  }
  if (trigger){
    Serial.print("GYRO TRIGGERED: ");
    Serial.println(z);
  }
  
  return trigger;
}
double abss(double in){
  return in < 0 ? -in : in;
}
double diff(double one, double two){
  return mini(one - two, mini(one - two + 360, one - two + 360));
}
double mini(double one, double two){
  return abss(one) > abss(two) ? abss(two) : abss(one);
}
