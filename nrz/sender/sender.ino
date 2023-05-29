#define D2 2
#define D3 3
#define D4 4
#define character_duration 28//32 are pierderi de informatii
#define clock_duration character_duration / 2

inline void break_char_into_byte(const char character) __attribute__((always_inline));
inline void break_string_into_characters(const char* string, uint32_t length) __attribute__((always_inline));

void setup() {
  // put your setup code here, to run once:
  pinMode(D2, OUTPUT); //message pin
  pinMode(D3, OUTPUT); //clock pin
  pinMode(D4, OUTPUT); //sync pin
  Serial.begin(9600);
  
}

void sendString(char* message)
{
  // the clock will stay on for clock_duration microseconds
  // the character will be sent over character_duration microseconds 
  // the sync will stay on for clock_duration microseconds

  int currentBit, length, i, j;
  char character;
  bool charParity; //if the number of ones is odd then the parity will be true
  int a = 0;
  length = strlen(message);

  for(i = 0;i<=length;i++){

    digitalWrite(D4, HIGH);
    character = message[i];
    charParity = false;

    for(j = 0;j<8;j++){
      digitalWrite(D2, HIGH); //clock

      //logic for sending
      currentBit = (character >> j) & 1;
      if(currentBit == 1){
        charParity = charParity ^ currentBit;
      }

      if(j == 7){
        digitalWrite(D3, charParity);
        //Serial.print(charParity);
      }else{
        digitalWrite(D3, currentBit);
        //Serial.print(currentBit);
      }

      //delay to switch the clock and refresh the message
      delayMicroseconds(clock_duration);
      //delay(clock_duration);
      digitalWrite(D2, LOW);
      //delay(clock_duration);
      delayMicroseconds(clock_duration);
      digitalWrite(D4, LOW); //disabling the sync pin because it resetted the string in the receiver
    }
  }
  //after each transmission, 100 microseconds pause
  delayMicroseconds(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  sendString("Hello tata, bine te-am gasit sunt happy azi!");
  //delay(1);
  sendString("Hello mama!");
  //delay(4000);
  sendString("Bubu honey");
  //delay(1);  
}
