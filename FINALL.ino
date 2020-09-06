#define LEFT_SPEED 110
#define RIGHT_SPEED 130
#define ARM_SPEED 150
#define GRABBER_SPEED 150

#define trig_f 20 // trigger pin for forward ultrasonic
#define echo_f 18  // echo pins for forward ultrasonic 

#define trig_l 31   // trigger pin for right ultrasonic
#define echo_l 33 // echo pins for right ultrasonic 

#define trig_r 41 // trigger pin for left ultrasonic
#define echo_r 37 // echo pins for left ultrasonic 

int forwardDistance = 0;       // receive the pulse for forward ultrasonic
int leftDistance = 0;       // receive the pulse for right ultrasonic
int rightDistance = 0;       // receive the pulse for left ultrasonic

int mr1 = 32;   // motor left  pin 12 -> IN3
int mr2 = 30;   // motor left  pin 13 -> IN4
int pmwr = 13;  // motor left  Pulse Width Modulation -> EN2
//----------------------

int ml1 = 36;  // motor right pin 8 -> IN1
int ml2 = 38; // motor right pin 9 -> IN2
int pmwl = 12; // motor right Pulse Width Modulation -> EN1
// -----------------------
int arm1 = 42;
int arm2 = 8;
int pwmArm = 11;
// -----------------------
int grab1 = 48;
int grab2 = 9;
int pwmGrab = 10;
char bluetoothdata;
int addSpeed ;
bool manual;
bool arm;
int distance(int trig, int echo) { //this function  for forward ultrasonic
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  int dur = pulseIn(echo, HIGH); //receive the pulse in echo pin
  return dur * 0.034 / 2; // the equation for calculating the sound speed
}
void setup()
{
  Serial3.begin(9600);
  Serial.begin(9600);
  manual = true;
  arm = false;
  addSpeed = 0;

  pinMode(trig_f, OUTPUT);
  pinMode(echo_f, INPUT);

  pinMode(trig_r, OUTPUT);
  pinMode(echo_r, INPUT);

  pinMode(trig_l, OUTPUT);
  pinMode(echo_l, INPUT);
}
void loop()
{



  forwardDistance = distance(trig_f, echo_f);
  Serial.print("forward = ");
  Serial.println(forwardDistance);
  //  leftDistance = distance(trig_l, echo_l);
  //rightDistance = distance(trig_r, echo_r);


  if (forwardDistance < 50) {
    wheelsControl(0, 0);
  } else {


    if (Serial3.available()) {
      bluetoothdata = Serial3.read();
      if (bluetoothdata == 'V') {
        manual = false;
        wheelsControl(0, 0);//stop speed when convert the manwal to auto
      } else if (bluetoothdata == 'v') {
        manual = true;
        wheelsControl(0, 0);
      } if (bluetoothdata == 'U') {
        addSpeed = 50;
      } else if (bluetoothdata == 'u') {
        addSpeed = 0;
      } else if (bluetoothdata == 'X'  && manual) {
        arm = true;
        wheelsControl(0, 0);
      } else if (bluetoothdata == 'x'  && manual) {
        arm = false;
        wheelsControl(0, 0);
      }
      Serial.println(bluetoothdata);
    }
    if (!manual) {

      //Serial.println("auto");
    } else {
      //Serial.println("manual");
      if (!arm) {
        manualControl(bluetoothdata);
      } else {
        armGrabControl(bluetoothdata);
      }
    }
  }
}
void wheelsControl(int ML , int MR) {
  // MOTOR LEFT CONTROL DIRECTION
  if ( ML < 0 ) {
    digitalWrite(ml1, 0);
    digitalWrite(ml2, 1);
    analogWrite(pmwl, -ML - addSpeed);
  } else {
    digitalWrite(ml1, 1);
    digitalWrite(ml2, 0);
    analogWrite(pmwl, ML + addSpeed);
  }
  // MOTOR RIGHT CONTROL DIRECTION
  if ( MR < 0 ) {
    digitalWrite(mr1, 0);
    digitalWrite(mr2, 1);
    analogWrite(pmwr, -MR - addSpeed);
  } else {
    digitalWrite(mr1, 1);
    digitalWrite(mr2, 0);
    analogWrite(pmwr, MR + addSpeed);
  }
}

void armControl(int s) {
  if (s < 0 ) {
    digitalWrite(arm1, 0);
    digitalWrite(arm2, 1);
    analogWrite(pwmArm, -s);
  } else {
    digitalWrite(arm1, 1);
    digitalWrite(arm2, 0);
    analogWrite(pwmArm, s);
  }
}

void grabControl(int s) {
  if (s < 0) {
    digitalWrite(grab1, 0);
    digitalWrite(grab2, 1);
    analogWrite(pwmGrab, -s);
  } else {
    digitalWrite(grab1, 1);
    digitalWrite(grab2, 0);
    analogWrite(pwmGrab, s);
  }
}
void manualControl(char dataRecived) {
  switch (dataRecived) {
    case 'F':
      // move forward
      wheelsControl(LEFT_SPEED - 20, RIGHT_SPEED -  20);
      break;
    case 'L':
      // move Left
      wheelsControl(-LEFT_SPEED - 30, RIGHT_SPEED + 30);
      break;
    case 'R':
      // move right
      wheelsControl(LEFT_SPEED + 30, - RIGHT_SPEED - 30);
      break;
    case 'B':
      // move backward
      wheelsControl(- LEFT_SPEED, - RIGHT_SPEED);
      break;
    case '0':
      // stop
      wheelsControl(0, 0);
      break;
    case 'S':
      wheelsControl(0, 0);
      break;
    case 'o':
      wheelsControl(0, 0);
      break;
  }
}
void armGrabControl(char dataRecived) {
  switch (dataRecived) {
    case 'F':
      // arm up
      armControl(ARM_SPEED);
      break;
    case 'B':
      // arm down
      armControl(-ARM_SPEED);
      break;
    case 'R':
      // grabber close
      grabControl(GRABBER_SPEED);
      break;
    case 'L':
      // grabber open
      grabControl(- GRABBER_SPEED);
      break;
    case 'S' :
      armControl(0);
      grabControl(0);
      break;
  }
}
void changeMode(char dataRecived) {
  switch (dataRecived) {
    case 'A' :
      manual = false;
      break;
    case 'N' :
      manual = false;
      break;
    case 'M':
      manual = true;
      break;
    case 'C':
      manual = true;
      break;
  }
}


