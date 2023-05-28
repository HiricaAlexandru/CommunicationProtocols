#define D2 2
#define D7 7
#define D4 4

#define character_duration 500
#define clock_duration character_duration / 2

bool isChangedClock = false;
char result = 0;
int number = 0;
int parityGot, parityCalculated = false;
int currentIndex = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(D2, INPUT);
  pinMode(D7, INPUT);
  pinMode(D4, OUTPUT);
  Serial.begin(9600);

  int clockValue = digitalRead(D7);
  while(clockValue == 0){
    clockValue = digitalRead(D7);
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int clockValue = digitalRead(D7);
  if(isChangedClock != clockValue){
    isChangedClock = clockValue;
    if(clockValue == 1){
      number+=1;
      int messageValue;
      digitalWrite(D4, HIGH);
      messageValue = digitalRead(D2);

      if(number <= 7 && messageValue == 1){
        parityCalculated = parityCalculated ^ messageValue;
      }
      messageValue = messageValue << (number-1);
      result = result+messageValue;
      
    }else{
      digitalWrite(D4, LOW);
    }
  }
  currentIndex += 1;

  if(number == 8){
    parityGot = result & 128;

    result -= parityGot;

    if((parityCalculated == 1 && parityGot>0) || (parityGot == parityCalculated)){
      Serial.print(result);
    }
    else
      Serial.print("?");

    result = 0;
    number = 0;
    parityCalculated = false;
  }

}
