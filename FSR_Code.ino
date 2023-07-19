#include <Joystick.h>
#include <EEPROM.h>



//Define pins for FSRs and LEDs, adjust based on your board design/wiring diagram

int LF = A3; //left fsr
int UF = A2;
int DF = A1;
int RF = A0;

int LL = 0; //left LED
int UL = 1;
int DL = 2;
int RL = 3;

//These are default thresholds, they don't matter too much as the board will load the thresholds from EEPROM on boot

int Lt = 300; //left threshold
int Ut = 300;
int Dt = 300;
int Rt = 300;

String readingTemp;

const byte numChars = 32;
char receivedChars[numChars];

bool newData = false;

Joystick_ Joystick(0x15, JOYSTICK_TYPE_GAMEPAD, 4, 0, false, false, false, false, false, false, false, false, false, false, false);

const bool initAutoSendState = true;

unsigned long lastWriteTime = 0;

void setup() {
  // put your setup code here, to run once:

  //Code to open the Serial COM port and load thresholds from EEPROM
  Serial.begin(9600, SERIAL_8N1);

  EEPROM.get(0, Lt);
  EEPROM.get(2, Ut);
  EEPROM.get(4, Dt);
  EEPROM.get(6, Rt);
  
Joystick.begin();
  
pinMode(LL, OUTPUT); //left led
pinMode(UL, OUTPUT); //up led
pinMode(DL, OUTPUT); //down led
pinMode(RL, OUTPUT); //right led

pinMode(LF, INPUT);
pinMode(UF, INPUT);
pinMode(DF, INPUT);
pinMode(RF, INPUT);

}

//function to recieve strings from DanceApp

void receiveString(){
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (rc != endMarker){
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
          ndx = numChars - 1;
      }
    }
    else{
        receivedChars[ndx] = '\0';
        ndx = 0;
        newData = true;
    }
  }
}

//function to loop over the recieved string and allocate the values as new threshold values
//also supports saving new thresholds to EEPROM for retrieval when the "apply" button is pressed.
void newThresh(){

    for (int i = 0; i <= sizeof(receivedChars); i++){
      if(isDigit(receivedChars[i])){
        readingTemp += (receivedChars[i]);
      }
    if (isAlpha(receivedChars[i])){
      if (receivedChars[i] == 'L')
        Lt = readingTemp.toInt();
      else if (receivedChars[i] == 'U')
        Ut = readingTemp.toInt();     
      else if (receivedChars[i] == 'D')
        Dt = readingTemp.toInt();
      else if (receivedChars[i] == 'R')
        Rt = readingTemp.toInt();
      else if (receivedChars[i] == 'S'){
        Serial.println("Saving...");
        delay(1000);
          EEPROM.put(0, Lt);
          EEPROM.put(2, Ut);
          EEPROM.put(4, Dt);
          EEPROM.put(6, Rt);

          Serial.println("Saving successful!");
          delay(1000);
      }
      readingTemp = "";
      }
    
    }
    
    newData = false;
  }


void loop() {
  // put your main code here, to run repeatedly:

  receiveString();
  newThresh();

  
  int Lvalue = analogRead(LF);
  String Lout = String(Lvalue);
  //Serial.print(Lvalue);
  //Serial.print("L");
  if (Lvalue > Lt) { // if the current value is higher than the set threshold
    digitalWrite(LL, HIGH);
      Joystick.setButton (0, 1);
    } else {
  digitalWrite(LL, LOW);
    Joystick.setButton (0, 0);
  }

  int Uvalue = analogRead(UF);
  String Uout = String(Uvalue);
  //Serial.print(Uvalue);
  //Serial.print("U");
  if (Uvalue > Ut) {
    digitalWrite(UL, HIGH);
    Joystick.setButton (1, 1);
  } else {
  digitalWrite(UL, LOW);
  Joystick.setButton (1, 0);
  }

  int Dvalue = analogRead(DF);
  String Dout = String(Dvalue);
  //Serial.print(Dvalue);
  //Serial.print("D");
  if (Dvalue > Dt) {
    digitalWrite(DL, HIGH);
    Joystick.setButton (2, 1);
  } else {
  digitalWrite(DL, LOW);
  Joystick.setButton (2, 0);
  }

  int Rvalue = analogRead(RF);
  String Rout = String(Rvalue);
  //Serial.print(Rvalue);
  if (Rvalue > Rt){
    digitalWrite(RL, HIGH);
    Joystick.setButton (3, 1);
   } else {
    digitalWrite(RL, LOW);
    Joystick.setButton (3, 0);
  }

  String Output = Lout;
  Output += "L";
  Output += Uout;
  Output += "U";
  Output += Dout;
  Output += "D";
  Output += Rout;
  Output += "R";

// timer for sending the string of current values to DanceApp
// if data is sent too quickly DanceApp can't keep up
//this doesn't affect gameplay as the joystick buttons aren't updated based on this timer
  if(millis() - lastWriteTime >= 100) {
      Serial.println(Output);
      lastWriteTime = millis();
  }
  

}
