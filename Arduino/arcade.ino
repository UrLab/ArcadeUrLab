const int minLedPin =  4;
const int maxLedPin = 13;
int currentMillis = 0;
int nbAnim1 = 0;
int nbAnim2 = 0;
bool Anim1Step = false;
bool Anim2Step = false;
int currentAnim = 1;
int nbAnims = 2;
int currentLed = minLedPin-1;
signed int StartTime = 0;
bool doAnim = true;

void setup(){
  for(int ledPin=minLedPin;ledPin<=maxLedPin;ledPin++){
    pinMode(ledPin, OUTPUT);
  }
  
  StartTime = millis();

  Serial.begin(9600);
}

int anim1(){
  if(currentMillis >= 250){
    currentMillis = 0;
    Anim1Step = !Anim1Step;
    if(Anim1Step){
      
      if(currentLed == maxLedPin){
        currentLed = minLedPin;
      }else{
        currentLed++;
      }
      digitalWrite(currentLed, HIGH);
    }
    if(currentLed - 1 >= minLedPin){
      digitalWrite(currentLed-1, LOW);
    }else{
      digitalWrite(maxLedPin, LOW);
    }
    nbAnim1++;
  }
  return nbAnim1;
}

int anim2(){
  if(currentMillis >= 250){
    currentMillis =  0;
    Anim2Step = !Anim2Step;
    if(Anim2Step){
      for(int current=minLedPin;current<=maxLedPin;current++){
        digitalWrite(current, HIGH);
      }
    }else{
      for(int current=minLedPin;current<=maxLedPin;current++){
        digitalWrite(current, LOW);
      }
      nbAnim2++;
    }
  }
  return nbAnim2;
}

void setAll(bool high){
  for(int current=minLedPin;current<=maxLedPin;current++){
      if(high){
        digitalWrite(current, HIGH);
      }else{
        digitalWrite(current, LOW);
      }
  }
}

void loop(){
  currentMillis += millis() - StartTime;
  StartTime = millis();

  if (Serial.available() > 0) {
    if(Serial.read() == 108){
      doAnim = false;
      currentMillis = 0;
      setAll(true);
    }
  }
  
  if(doAnim){
    if(currentAnim == 1){
      if(anim1() == 20){
        currentAnim = 2;
        nbAnim1 = 0;
      }
    }else{
      if(anim2() == 3){
        currentAnim = 1;
        nbAnim2 = 0;
        currentLed = minLedPin-1;
      }
    }
  }else{
    if(currentMillis > 90000){
      doAnim = true;
      currentLed = minLedPin;
      nbAnim1 = 0;
      nbAnim2 = 0;
      currentMillis = 0;
    }
  }
}
