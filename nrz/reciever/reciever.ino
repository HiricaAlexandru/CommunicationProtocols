#define D2 2 //message pin
#define D7 7 // clock pin
#define D4 4 // debug clock pin
#define D5 5 // sync pin

bool isChangedClock = false;
bool isChangedSync = false;
char result = 0;
int number = 0;
int parityGot, parityCalculated = false;
int currentIndex = 0;
char buffer[200];

inline bool getBitValue(char* buffer) __attribute__((always_inline));

void setup() {
  // put your setup code here, to run once:
  pinMode(D2, INPUT);
  pinMode(D7, INPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, INPUT);

  Serial.begin(9600);

  int clockValue = digitalRead(D7);
  while(clockValue == 0){
    clockValue = digitalRead(D7);
  }
  
}

bool getBitValue(char* buffer)
{
  int clockValue = digitalRead(D7);
  bool syncValue = digitalRead(D5);

  //isChangedSync = isChangedSync ^ syncValue;

  //if(isChangedSync && syncValue == true){
  //  number = 0;
  //  parityCalculated = 0;
  //  result = 0;
  //}

  if(isChangedSync != syncValue){
    isChangedSync = syncValue;

    if(syncValue == true){
      number = 0;
      parityCalculated = 0;
      result = 0;
    }
  }

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
      //parityGot could be 0 and 128
      buffer[currentIndex++] = result;
    }
    else{
      buffer[currentIndex++] = '?';
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
    Serial.println(buffer);
    currentIndex = 0;
  }


}


