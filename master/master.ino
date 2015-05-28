#include <Wire.h>


// setup motors
int motorOutputs[] = {
  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,
  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,
  3
};
int motorCount = 25;


// setup modes
String mode = "always";
#define gustButton 23
#define alwaysButton 24


// setup the input pinwheel
bool lastHallEffectReading = 0;
#define hallEffectSensor 22
int motorSpeed = 0;


void setup()
{
  Wire.begin();

  pinMode(hallEffectSensor,      INPUT);
  pinMode(gustButton,            INPUT);
  pinMode(alwaysButton,          INPUT);
}

byte x = 0;


void loop()
{
  Wire.beginTransmission(4);

  // change modes?
  bool modeChange = false;
  String newMode = mode;
  if(digitalRead(gustButton))     newMode = "blow";
  if(digitalRead(alwaysButton))   newMode = "always";
  if(mode != newMode) modeChange = true;
  mode = newMode;


  // blow mode
  if(mode == "gust"){
    // is the pinwheel turning?  
    if(lastHallEffectReading != digitalRead(hallEffectSensor)){
      lastHallEffectReading = digitalRead(hallEffectSensor);
      motorSpeed += 30;
      if(motorSpeed >= 255) motorSpeed = 255;
    }
    
    // continuously slow the pinwheel down
    if(motorSpeed > 0){
      motorSpeed -= .01;
    }
  }
  

  if(mode == "always" && modeChange == true){
    // loop over all the motors and write to the appropriate arduino
    for(int i=0; i<motorCount; i++){
      // write to first arduino
      if(i < 11){
        digitalWrite(motorOutputs[i], 255);
      } else if(i > 11){
        Wire.write("1:");
        Wire.write(motorOutputs[i]);
        Wire.write(":255");
      } else if(i > 24){
        Wire.write("2:");
        Wire.write(motorOutputs[i]);
        Wire.write(":255");        
      }
    }
  }

  Wire.endTransmission();
}

