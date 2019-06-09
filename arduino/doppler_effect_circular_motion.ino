#include <Servo.h>
#include "timeObj.h"

/**
* 
* Description- The program is  used for running the doppler experiment setup.
* The progams suites a  brushless motor that takes 4 cell Lipo battey as 
* voltage source and goes up to 9100 RPM.Also each test takes 30 seconds
*
* Authers - Ariel Zilbershtein and kfir Haeman
*
*/


// create a  servo object to control the ESC
Servo ESC;     

// A 30 sec. timer for the motor
timeObj motorTimer(30000); 

// marker whenever the motor is running   and whenever the given speed is valid
boolean motorRunning = false;
boolean validSpeed=false;

 // The speed the motor should spin
double incomingSpeed = 1;  

// constant values regrading the motor capabilties
const int MAX_RPM=9100;
const int MIN_RPM=0;
const int MAX_ALLOWED_SPEED=1761.111111; // exceding this value would burn the motor


//  const values regarding  the speed capablilites of the arduino
const int MIN_SPEED=1000;
const int HALF_SPEED=1500;
const int MAX_SPEED=2000;
const int SIGNAL_PIN=9;


/**
* 
* Description- checks whenever the privided speed does not exceed the motor capabilties 
* The first parameter - represent a given speed that the motor should turn
*/
void checkIncomingSpeed(int speed){

  if((speed>=MIN_SPEED) &&(speed<MAX_ALLOWED_SPEED)){
    incomingSpeed=speed;
    validSpeed=true;
  }else{
    validSpeed=false;    
  }
  
}

// A routine to turn on the motor.
void motorOn(void) {
  
  // *** Do your stuff to turn on the motor ***
  motorTimer.start();   // Start the timer
  motorRunning = true;   // Let the world know the motor is runnin'!
}



/**
* 
* Description- A routine to turn the motor off.
*/
void motorOff(void) {
   motorRunning  = false;  
}

/**
* 
* Description- Checks whenever the motor running duration is up
*/

void checkMotor(void) {   
  
 // IF the motor's running..
  if (motorRunning) {             

    // And IF the time has run out..       
     if (motorTimer.ding()) {     

      // Shut off the motor.
        motorOff();                         
     }
  }
}

void setup() {
  
  // opens serial port, sets data rate to 9600 bps
  Serial.begin(9600);     
  
  // Attach the ESC on pin 9
  ESC.attach(SIGNAL_PIN,1000,2000); // (pin, min pulse width, max pulse width in microseconds)

  checkIncomingSpeed(incomingSpeed);
  
  if(validSpeed){
    motorOn();  

    // waits for 10 seconds before starting the program for safety purpouses
    delay(10000);
  
  }else{
    
    Serial.print("Invalid speed was provided");
  }
}

void loop() {
  checkMotor();

  if(motorRunning){
    ESC.writeMicroseconds(incomingSpeed);
  }
}
