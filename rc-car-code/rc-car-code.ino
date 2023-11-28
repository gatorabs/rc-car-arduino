


//CÓDIGO COM DOIS MOTORES DC
#include <AFMotor.h>


int startedSpeed = 0;
int timeStarted = millis();

AF_DCMotor m1(1);
AF_DCMotor m2(2);


void setup() {

  Serial.begin(9600);
  
  m1.setSpeed(0);
  m2.setSpeed(0);

  Serial.println("Simple CAR-DC-CODE");
  delay(500);
  Serial.println("Created by GABS");
  delay(1000);

  helplSMenu();
  
}


void loop() {
  
  //helplSMenu();
  updateSerial();

}

void updateSerial(){
  if(Serial.available() > 0){
    byte incomingByte = Serial.read();
    switch(incomingByte){
      case 'F':
      
            Serial.println("Moving Forward - F");
            linearSpeedFB('f');
      case 'B':
      
            Serial.println("Moving Backward - B");
            linearSpeedFB('b');

      case 'R':

            Serial.println("Moving Right Side - R");
            linearSpeedRL('r');

      case 'L':

            Serial.println("Moving Left Side - L");
            linearSpeedRL('l');
            
      case 'J':

            Serial.println("Moving Axle Right Side - J");
            axleRotation('r');

      case 'K':

            Serial.println("Moving Axle Left Side - K");
            axleRotation('l');
      
      case '!':
        break;
    }

    
  }
}
void linearSpeedFB(char side){
  for(byte i = 0; i < 255; i = i + 10){

    m1.setSpeed(i);
    m2.setSpeed(i);

    if(side == 'f'){
      m1.run(FORWARD);
      m2.run(FORWARD);
      
    }else if(side == 'b'){
      m1.run(BACKWARD);
      m2.run(BACKWARD);
      
    }else{
      m1.run(RELEASE);
      m2.run(RELEASE);
      
    }
  }
}


void linearSpeedRL(char side){

  int counter1 = 0;
  int counter2 = 0;
  
  for(byte i = 0; i < 26; i++){
    
    if(counter1 < 120){
      
      counter1 = counter1 + 10;
      
    }else if(counter1 > 120){
      
      counter1 = 120;
      
    }
    
    if(counter2 < 255){
      
      counter2 = counter2 + 10;
      
    }else if(counter2 > 255){
      
      counter2 = 255;
      
    }
    
    
    if(side == 'r'){
      m1.setSpeed(counter1);
      m2.setSpeed(counter2);
      m1.run(FORWARD);
      m2.run(FORWARD);
      
    }else if(side == 'l'){
      m1.setSpeed(counter2);
      m2.setSpeed(counter1);
      m1.run(FORWARD);
      m2.run(FORWARD);
      
    }else{
      m1.run(RELEASE);
      m2.run(RELEASE);
      
    }
  }
}


void axleRotation(char side){
  if(side == 'r'){
    m2.run(RELEASE);
    m1.setSpeed(255);
    m1.run(FORWARD);
    
  }
  if(side == 'l'){
    m1.run(RELEASE);
    m2.setSpeed(255);
    m2.run(FORWARD);
    
  }else{
    m1.run(RELEASE);
    m2.run(RELEASE);
  }
}


void helplSMenu(){
  Serial.println("USE:");
  Serial.println("F for Forward");
  Serial.println("B for Backward");
  Serial.println("R for Right Side");
  Serial.println("L for Left Side");
  Serial.println("J for Axle Right Side");
  Serial.println("K for Axle Left Side");
  
}
