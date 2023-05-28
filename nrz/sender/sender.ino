#define D2 2
#define D3 3
#define character_duration 50
#define clock_duration character_duration / 2

inline void break_char_into_byte(const char character) __attribute__((always_inline));
inline void break_string_into_characters(const char* string, uint32_t length) __attribute__((always_inline));

char *stringAnalyze = "Mama si tata!";
int length;

void setup() {
  // put your setup code here, to run once:
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  Serial.begin(9600);
  length = strlen(stringAnalyze);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  int currentBit;
  char character;
  int a =0;
  for(int i = 0;i<length;i++){
    character = stringAnalyze[i];
    for(int j = 0;j<8;j++){
      digitalWrite(D2, HIGH); //clock
      //logic for sending
      currentBit = (character >> j) & 1;
      digitalWrite(D3, currentBit);
      //Serial.print(currentBit);
      delay(clock_duration);
      digitalWrite(D2, LOW);
      delay(clock_duration);
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