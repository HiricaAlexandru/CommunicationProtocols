#define D2 2
#define D3 3
#define D4 4

#define character_duration 500
#define clock_duration character_duration / 2

bool isChangedClock = false;
char result = 0;
int number = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D4, OUTPUT);
  Serial.begin(9600);

  int clockValue = digitalRead(D3);
  while(clockValue == 0){
    clockValue = digitalRead(D3);
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int clockValue = digitalRead(D3);
  

  if(isChangedClock ^ clockValue){
    isChangedClock = clockValue;
    if(clockValue == 1){
      number+=1;
      int messageValue;
      digitalWrite(D4, HIGH);
      messageValue = digitalRead(D2);
      messageValue = messageValue << (number-1);
      result = result+messageValue;
      //result = result << 1;
      //result += messageValue;
      //Serial.print(result);
      
    }else{
      digitalWrite(D4, LOW);
    }
  }
  
  if(number == 8){
    Serial.print(result);
    result = 0;
    number = 0;
  }

}
