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
char buffer[200];

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

bool getBitValue(char* buffer)
{
  int clockValue = digitalRead(D7);

  if(isChangedClock != clockValue){
    //if the clock is up then we will read the value of the incoming bit

    isChangedClock = clockValue;
    if(clockValue == 1){
      number+=1;
      int messageValue;
      digitalWrite(D4, HIGH); //the light that indicates the receiver clock turns on
      messageValue = digitalRead(D2);

      if(number <= 7 && messageValue == 1){
        //calculating the parity, represents the bit number 8
        parityCalculated = parityCalculated ^ messageValue;
      }
      //calculating the result
      messageValue = messageValue << (number-1);
      result = result+messageValue;
      
    }else{
      digitalWrite(D4, LOW);
    }
  }

  if(number == 8){
    parityGot = result & 128; //getting the got parity

    result -= parityGot; //eliminating the parity from the got message

    if((parityCalculated == 1 && parityGot>0) || (parityGot == parityCalculated)){
      buffer[currentIndex++] = result;
    }
    else{
      buffer[currentIndex++] = result;
    }
    result = 0;
    number = 0;
    parityCalculated = false;

    if(buffer[currentIndex-1] == NULL){
      currentIndex = 0;
      return true;
    }
  }

  return false;
}

void loop() {
  // put your main code here, to run repeatedly:
  bool finished = getBitValue(buffer);
  if(finished == true){
    Serial.println(buffer[0]);
    Serial.println(buffer);
    currentIndex = 0;
  }


}


