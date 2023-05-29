#define D2 2
#define D3 3
#define character_duration 50//320
#define clock_duration character_duration / 2

inline void break_char_into_byte(const char character) __attribute__((always_inline));
inline void break_string_into_characters(const char* string, uint32_t length) __attribute__((always_inline));

char *stringAnalyze = "Hello world!";

void setup() {
  // put your setup code here, to run once:
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  Serial.begin(9600);
  
  delay(10000);
}

void sendString(char* message)
{
  int currentBit, length, i, j;
  char character;
  bool charParity; //if the number of ones is odd then the parity will be true
  int a = 0;
  length = strlen(message);

  for(i = 0;i<=length;i++){
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

      //delayMicroseconds(clock_duration);
      delay(clock_duration);
      digitalWrite(D2, LOW);
      delay(clock_duration);
      //delayMicroseconds(clock_duration);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  sendString(stringAnalyze);
  delay(4000);
  sendString("Bubu honey");
}

void break_char_into_byte(const char character) 
{
  uint8_t currentChar, i;

  for(i = 0; i<8;i++){
    currentChar = (character >> i) & 1;
    Serial.print(currentChar);
  }
}

void break_string_into_characters(const char* string, uint32_t length)
{
  uint32_t i;
  for(i = 0; i < length; i++)
  {
    break_char_into_byte(string[i]);
  }
}