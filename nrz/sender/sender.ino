#define D2 2
#define D3 3
#define character_duration 100
#define clock_duration character_duration / 2

inline void break_char_into_byte(const char character) __attribute__((always_inline));
inline void break_string_into_characters(const char* string, uint32_t length) __attribute__((always_inline));

char *stringAnalyze = "Hello world!";
int length;

void setup() {
  // put your setup code here, to run once:
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  Serial.begin(9600);
  length = strlen(stringAnalyze);
  delay(10000);
}

void loop() {
  // put your main code here, to run repeatedly:
  int currentBit;
  char character;
  bool charParity; //if the number of ones is odd then the parity will be true
  int a =0;
  for(int i = 0;i<length;i++){
    character = stringAnalyze[i];
    charParity = false;
    for(int j = 0;j<8;j++){
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

      
      delayMicroseconds(clock_duration);
      //delay(clock_duration);
      digitalWrite(D2, LOW);
      //delay(clock_duration);
      delayMicroseconds(clock_duration);
    }
    
  }
  //Serial.print("END");

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