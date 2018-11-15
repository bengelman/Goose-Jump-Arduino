

class Theme{
  public:
   
    Theme(String name, String promptSet[], int length){
      title = name;
      size = length;
      for (int i = 0; i < length; i++){
        prompts[i] = promptSet[i];
      }
    }
    int size;
    String title; 
    int getRandomPrompt();
    String prompts[100];
  private:
    
    
};
enum GameState{
  SELECT, PLAY, END
};
GameState state = SELECT;
int score = 0;
float timer = 0;
int theme = 0;
int prompt = 0;
String promptWaterloo[] = {"Mr Goose", "SYDE"};
String promptMovies[] = {"Whiplash", "Grease"};
int themeNum = 1;
Theme themes[] = {
  Theme("Waterloo Memes", promptWaterloo, 2),
  Theme("Movies", promptMovies, 2);
};
int Theme::getRandomPrompt(){
  rand() % Theme::size;
}

void setup() {
  // put your setup code here, to run once:
  
}
float lastMillis = 0;
void loop() {
  if (timer > 0){
    timer -= (millis() - lastMillis);
  }
  lastMillis = millis();
  if (state == SELECT){
    displayText(themes[theme].title);
    if (timer <= 0){
      timer = 1000;
      theme++;
      theme %= themeNum;
    }
    if (gyro()){
      timer = 60000;
      state = PLAY;
    }
  }
  if (state == PLAY){
    displayText(themes[theme].prompts[prompt]);
    if (gyro()){
      score++;
      prompt = themes[theme].getRandomPrompt();
    }
    if (timer <= 0){
      state = END;
      timer = 5000;
    }
    if (state == END){
      displayText("Score: " + score);
      if (timer <= 0){
        state = SELECT;
        timer = 1000;
      }
    }
  }
  // put your main code here, to run repeatedly:
  
}
void displayText(String toDisplay){
  
}

bool gyro(){
  return false;
}
