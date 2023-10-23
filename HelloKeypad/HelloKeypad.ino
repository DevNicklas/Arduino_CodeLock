#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char code[4] {'2', '1', '0', '5'};
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte codeCounter = 0;
char selectedCode[4];

byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad

byte accessLightPin = 10;
byte noAccessLightPin = 11;

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  pinMode(accessLightPin, OUTPUT);
  pinMode(noAccessLightPin, OUTPUT);
  Serial.begin(9600);
}
  
void loop(){
  char key = keypad.getKey();
  
  if (key){
    // Validate code
    if(key == '#'){
      checkCode();
    }

    // Reset selected code and lights the yellow led
    else if(key == '*'){
      resetCode();
    }
    else{
      selectedCode[codeCounter] = key;
      codeCounter++;
    }
  }
}

// Checks whether the code which the user has typed is correct or not
void checkCode()
{
  // All 4 digits matches up, and the user is granted access
  if(selectedCode[0] == code[0], selectedCode[1] == code[1], selectedCode[2] == code[2], selectedCode[3] == code[3]){
      
    // Access is granted and a green light will be lit
    accessGranted();

    // Reset code typed by user
    resetCode();
  }

  // Either one or more digits is wrong, and the user is denied access
  else
  {
    // Access is denied and a red light will be lit
    accessDenied();

    // Reset code typed by user
    resetCode();
  }
}

// The green light will be lit for 5 seconds when the user typed the correct code
void accessGranted(){
  Serial.println("Access is granted");
  digitalWrite(accessLightPin, HIGH);
  delay(5000);
  digitalWrite(accessLightPin, LOW);
}

// The red light will be lit for 5 seconds when the user typed a wrong code
void accessDenied(){
  Serial.println("Access is denied");
  digitalWrite(noAccessLightPin, HIGH);
  delay(5000);
  digitalWrite(noAccessLightPin, LOW);
}

// Resets the code which the user typed
void resetCode(){
  codeCounter = 0;

  // Copys one byte of value to the destination memory block byte by byte
  // This resets the array which contains the code typed by the user
  memset(selectedCode, 0, sizeof(selectedCode));
}