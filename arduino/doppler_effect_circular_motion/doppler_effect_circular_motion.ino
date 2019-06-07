#include <Servo.h>
/**
* The prgram used for running the dopller experiment
*
*/
Servo ESC;     // create servo object to control the ESC

// the speed tanges from 0-180
double incomingSpeed = 1;   // for incoming serial data

// constant values
const int MAX_RPM=9100;
const int MIN_RPM=0;
const int SIGNAL_PIN=9;
const int DEFAULT_SPEED=0;
const int MIN_SPEED=0;
const int HALF_SPEED=90;
const int MAX_SPEED=180;
const int MAX_ALLOWED_VALUE=137;
const double RPM_PER_ROTATION=0.5555555556;


void setup() {
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  
  // Attach the ESC on pin 9
  ESC.attach(SIGNAL_PIN,1000,2000); // (pin, min pulse width, max pulse width in microseconds)
}


void loop() {
  // put your main code here, to run repeatedly:
ESC.write(incomingSpeed);
}
