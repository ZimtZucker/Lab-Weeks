#include <Servo.h> 

const int SERVO_OUTPUT_PIN1 = 9;
const int SERVO_OUTPUT_PIN2 = 10;
const int SERVO_OUTPUT_PIN3 = 11;
const int SERVO_OUTPUT_PIN4 = 6;
const int SERVO_OUTPUT_PIN5 = 5;
const int SERVO_OUTPUT_PIN6 = 3;

const int MAX_ANALOG_VAL = 1023;
const int MIN_SERVO_ANGLE = 0;
const int MAX_SERVO_ANGLE = 180;

Servo servo1; 
Servo servo2; 
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
int serialServoAngle1 = -1;
int serialServoAngle2 = -1;
int serialServoAngle3 = -1;
int serialServoAngle4 = -1;
int serialServoAngle5 = -1;
int serialServoAngle6 = -1;
int serialServoAngle = -1;
 
void setup() 
{ 
  Serial.begin(115200);
  servo1.attach(SERVO_OUTPUT_PIN1);
  servo2.attach(SERVO_OUTPUT_PIN2);
  servo3.attach(SERVO_OUTPUT_PIN3);
  servo4.attach(SERVO_OUTPUT_PIN4);
  servo5.attach(SERVO_OUTPUT_PIN5);
  servo6.attach(SERVO_OUTPUT_PIN6);
} 
 
void loop() 
{ 
  // Check if serial data exists, if so read it in
  if(Serial.available() > 0){
    // Read data off the serial port until we get to the endline delimiter ('\n')
    // Store all of this data into a string
    String rcvdSerialData = Serial.readStringUntil('\n'); 

    // We accept either integers between 0 and 180 or floats. Floats must have a period to be recognized
    int indexOfDecimal = rcvdSerialData.indexOf('.');
    if(indexOfDecimal != -1){
      float serialServoAngleF = rcvdSerialData.toFloat();
      serialServoAngle1 = MIN_SERVO_ANGLE + (int)(serialServoAngleF * (MAX_SERVO_ANGLE - MIN_SERVO_ANGLE));
      serialServoAngle2 = serialServoAngle1;  // Set both servos to the same angle
      serialServoAngle3 = serialServoAngle1;  // Set all servos to the same angle
      serialServoAngle4 = serialServoAngle1;  // Set all servos to the same angle
      serialServoAngle5 = serialServoAngle1;  // Set all servos to the same angle
      serialServoAngle6 = serialServoAngle1;  // Set all servos to the same angle
    }else{
      serialServoAngle1 = rcvdSerialData.toInt();
      serialServoAngle2 = serialServoAngle1;  // Set both servos to the same angle
      serialServoAngle3 = serialServoAngle1;  // Set all servos to the same angle
      serialServoAngle4 = serialServoAngle1;  // Set all servos to the same angle
      serialServoAngle5 = serialServoAngle1;  // Set all servos to the same angle
      serialServoAngle6 = serialServoAngle1;  // Set all servos to the same angle
    }

    serialServoAngle1 = constrain(serialServoAngle1, MIN_SERVO_ANGLE, MAX_SERVO_ANGLE);
    serialServoAngle2 = constrain(serialServoAngle2, MIN_SERVO_ANGLE, MAX_SERVO_ANGLE);
    serialServoAngle3 = constrain(serialServoAngle3, MIN_SERVO_ANGLE, MAX_SERVO_ANGLE);
    serialServoAngle4 = constrain(serialServoAngle4, MIN_SERVO_ANGLE, MAX_SERVO_ANGLE);
    serialServoAngle5 = constrain(serialServoAngle5, MIN_SERVO_ANGLE, MAX_SERVO_ANGLE);
    serialServoAngle6 = constrain(serialServoAngle6, MIN_SERVO_ANGLE, MAX_SERVO_ANGLE);

    delay(1000);
    // Echo back data
    Serial.print("# Arduino Received: '");
    Serial.print(rcvdSerialData);
    Serial.print("' Converted to: ");
    Serial.println(serialServoAngle1);

    // Set new servo angles
    servo1.write(serialServoAngle1);
    servo2.write(serialServoAngle2);
    servo3.write(serialServoAngle3);
    servo4.write(serialServoAngle4);
    servo5.write(serialServoAngle5);
    servo6.write(serialServoAngle6);
  }
}



