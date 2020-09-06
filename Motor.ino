// PINS

/**
   Motors
   first , second are motor pis
   third  PWM
*/
int leftWheelsPins[] =  {13, 12, 11};
int rightWheelsPins[] = {8, 7, 6};
int armPins[] = {7, 8, 9};
int grabberPins[] = {10, 11, 12};

void motorsSetup() {
  // inintialize motors pins as output
  for (int i = 0; i < 3; i++) {
    pinMode(leftWheelsPins[i], OUTPUT);
    pinMode(rightWheelsPins[i], OUTPUT);
    pinMode(armPins[i], OUTPUT);
    pinMode(grabberPins[i], OUTPUT);
  }
  
}
/**
   control the direction of the motor


   motor : refreance for motor ro set direction
   motorDirection : indicator for motor direction takes on of two values
   MOTOR_DIRECTION_FORWARD
   MOTOR_DIRECTION_REVERSE

*/
void motorControl(int motor[] , int motorDirection) {
  switch (motorDirection) {
    case MOTOR_DIRECTION_FORWARD :
      digitalWrite(motor[0] , HIGH);
      digitalWrite(motor[1] , LOW);
      break;
    case MOTOR_DIRECTION_REVERSE :
      digitalWrite(motor[1] , HIGH);
      digitalWrite(motor[0] , LOW);
      break;
      case MOTOR_DIRECTION_STOP :
       digitalWrite(motor[0], LOW);
       digitalWrite(motor[1], LOW);
       break;
  }
}
/**
   base method for control the wheels by provide the speed of
   each side wheels

   WL : Speed for the left side wheels
   WR : Speed for the right side wheels
*/
void wheelsControl(int WL , int WR) {
  analogWrite(leftWheelsPins[2] , WL);
  analogWrite(rightWheelsPins[2] , WR);
}

/**
   control the arm motor
   armDirection : the direction of the arm
   ARM_DIRECTION_UPWARD
   ARM_DIRECTION_DOWNWARD
*/
void armControl(int armDirection) {
  switch (armDirection) {
    case ARM_DIRECTION_UPWARD:
      motorControl(armPins, MOTOR_DIRECTION_FORWARD);
      analogWrite(armPins[2], ARM_SPEED);
      break;
    case ARM_DIRECTION_DOWNWARD:
      motorControl(armPins, MOTOR_DIRECTION_REVERSE);
      analogWrite(armPins[2], ARM_SPEED);
      break;
  }
}
/**
   control the grabber motor
   grabberDirection : the direction of the arm
   GRABBER_DIRECTION_GRAB
   GRABBER_DIRECTION_UNGRAB
*/
void grabberControl(int grabberDirection) {
  switch (grabberDirection) {
    case GRABBER_DIRECTION_GRAB:
      motorControl(grabberPins, MOTOR_DIRECTION_FORWARD);
      analogWrite(grabberPins[2], GRABBER_SPEED);
      break;
    case GRABBER_DIRECTION_UNGRAB:
      motorControl(grabberPins, MOTOR_DIRECTION_REVERSE);
      analogWrite(grabberPins[2], GRABBER_SPEED);
  }
}
/**
   move the robot forward
*/
void moveForward() {
  motorControl(leftWheelsPins, MOTOR_DIRECTION_FORWARD);
  motorControl(rightWheelsPins, MOTOR_DIRECTION_REVERSE);
  wheelsControl(WHEELS_SPEED, WHEELS_SPEED);
}
/**
   move robot backward
*/
void moveBackward() {
  motorControl(leftWheelsPins, MOTOR_DIRECTION_REVERSE);
  motorControl(rightWheelsPins, MOTOR_DIRECTION_FORWARD);
  wheelsControl(WHEELS_SPEED, WHEELS_SPEED);
}
/**
   move robot for the left
   angle : is the angle of the left movement
   ANGLE_SLOW_ONE
   ANGLE_STOP_ONE
   ANGLE_REVERSE_ONE
*/
void moveLeft(int angle) {
  motorControl(leftWheelsPins, MOTOR_DIRECTION_FORWARD);
  motorControl(rightWheelsPins, MOTOR_DIRECTION_REVERSE);
  switch (angle) {
    case ANGLE_SLOW_ONE:
      motorControl(rightWheelsPins, MOTOR_DIRECTION_REVERSE);
      wheelsControl(WHEELS_SPEED, WHEELS_SPEED - .2 * WHEELS_SPEED);
      break;
    case ANGLE_STOP_ONE:
      motorControl(rightWheelsPins, MOTOR_DIRECTION_REVERSE);
      wheelsControl(WHEELS_SPEED, 0);
       break;
    case ANGLE_REVERSE_ONE:
      motorControl(rightWheelsPins, MOTOR_DIRECTION_FORWARD);
      wheelsControl(WHEELS_SPEED, WHEELS_SPEED);
      break;
  }

}
/**
   move robot for the left
   angle : is the angle of the right movement
   ANGLE_SLOW_ONE
   ANGLE_STOP_ONE
   ANGLE_REVERSE_ONE
*/
void moveRight(int angle) {
  motorControl(rightWheelsPins, MOTOR_DIRECTION_REVERSE);
  switch (angle) {
    case ANGLE_SLOW_ONE:
      motorControl(leftWheelsPins, MOTOR_DIRECTION_FORWARD);
      wheelsControl(WHEELS_SPEED - .2 * WHEELS_SPEED, WHEELS_SPEED);
      break;
    case ANGLE_STOP_ONE:
      motorControl(leftWheelsPins, MOTOR_DIRECTION_FORWARD);
      wheelsControl(WHEELS_SPEED, 0);
      break;
    case ANGLE_REVERSE_ONE:
      motorControl(leftWheelsPins, MOTOR_DIRECTION_REVERSE);
      wheelsControl(WHEELS_SPEED, WHEELS_SPEED);
      break;
  }
}

void stopWheels(){
  motorControl(rightWheelsPins, MOTOR_DIRECTION_STOP);
  motorControl(leftWheelsPins, MOTOR_DIRECTION_STOP);
  
}
