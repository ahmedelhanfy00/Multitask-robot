#define trig_f 20 // trigger pin for forward ultrasonic
#define echo_f 18  // echo pins for forward ultrasonic 

#define trig_l 31   // trigger pin for right ultrasonic
#define echo_l 33 // echo pins for right ultrasonic 

#define trig_r 41 // trigger pin for left ultrasonic
#define echo_r 37 // echo pins for left ultrasonic 
#define MOTOR_DIRECTION_FORWARD 101
#define MOTOR_DIRECTION_REVERSE 102
#define MOTOR_DIRECTION_STOP 103
#define SIDE_LIMIT 20
#define FORWARD_LIMIT 25
#define MAX_LIMIT 200
#define LEFT_SPEED 90
#define RIGHT_SPEED 110
int forwardDistance = 0;       // receive the pulse for forward ultrasonic
int leftDistance = 0;       // receive the pulse for right ultrasonic
int rightDistance = 0;       // receive the pulse for left ultrasonic
//int leftWheelsPins[] =  {32, 30, 13};
//int rightWheelsPins[] = {38, 36, 12};
int mr1 = 32;   // motor left  pin 12 -> IN3
int mr2 = 30;   // motor left  pin 13 -> IN4
int pmwr = 13;  // motor left  Pulse Width Modulation -> EN2
//----------------------

int ml1 = 36;  // motor right pin 8 -> IN1
int ml2 = 38; // motor right pin 9 -> IN2
int pmwl = 12; // motor right Pulse Width Modulation -> EN1

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //// the status for pins ////

  pinMode(trig_f, OUTPUT);
  pinMode(echo_f, INPUT);

  pinMode(trig_r, OUTPUT);
  pinMode(echo_r, INPUT);

  pinMode(trig_l, OUTPUT);
  pinMode(echo_l, INPUT);
  pinMode (mr1, OUTPUT);
  pinMode (mr2, OUTPUT);
  pinMode (ml1, OUTPUT);
  pinMode (ml2, OUTPUT);
}

void loop() {
  //  wheelsControl(100, -100);
  // wheelsControl(LEFT_SPEED, RIGHT_SPEED);
  forwardDistance = distance(trig_f, echo_f);

  Serial.print("Left :");
    Serial.print(leftDistance);
    Serial.print("     forward :");
    Serial.print(forwardDistance);
    Serial.print("     right :");
    Serial.println(rightDistance);

  if (forwardDistance > FORWARD_LIMIT) {
    wheelsControl(LEFT_SPEED - 20, RIGHT_SPEED - 20);
  } else {
    wheelsControl(0, 0);
    leftDistance = distance(trig_l, echo_l);
    rightDistance = distance(trig_r, echo_r);
    
    if (leftDistance > 20) {
      //left
      while (forwardDistance < FORWARD_LIMIT || forwardDistance > 90) {
        forwardDistance = distance(trig_f, echo_f);
        wheelsControl( -LEFT_SPEED - 50, RIGHT_SPEED + 80);
      }

    }  else if (forwardDistance <= FORWARD_LIMIT && leftDistance <= 35  && rightDistance > 35) {
      //right
      while (forwardDistance < FORWARD_LIMIT || forwardDistance > 90) {
        forwardDistance = distance(trig_f, echo_f);
        wheelsControl(LEFT_SPEED + 80, - RIGHT_SPEED - 70);
      }
    }
  }
}


int distance(int trig, int echo) { //this function  for forward ultrasonic
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  int dur = pulseIn(echo, HIGH); //receive the pulse in echo pin
  return dur * 0.034 / 2; // the equation for calculating the sound speed
}

// PINS
/**
   base method for control the wheels by provide the speed of
   each side wheels

   WL : Speed for the left side wheels
   WR : Speed for the right side wheels
*/
void wheelsControl(int ML , int MR) {
  // MOTOR LEFT CONTROL DIRECTION
  if ( ML < 0 ) {
    digitalWrite(ml1, 0);
    digitalWrite(ml2, 1);
    analogWrite(pmwl, -ML);
  } else {
    digitalWrite(ml1, 1);
    digitalWrite(ml2, 0);
    analogWrite(pmwl, ML);
  }
  // MOTOR RIGHT CONTROL DIRECTION
  if ( MR < 0 ) {
    digitalWrite(mr1, 0);
    digitalWrite(mr2, 1);
    analogWrite(pmwr, -MR);
  } else {
    digitalWrite(mr1, 1);
    digitalWrite(mr2, 0);
    analogWrite(pmwr, MR);
  }
}
