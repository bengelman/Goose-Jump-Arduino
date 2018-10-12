

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
    String getRandomPrompt();
  private:
    
    String prompts[100];
};
String promptWaterloo[] = {"Mr Goose", ""};
Theme* themes[] = {new Theme("Waterloo", promptWaterloo, 2)};
String Theme::getRandomPrompt(){
  return prompts[rand() % size];
}

void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
