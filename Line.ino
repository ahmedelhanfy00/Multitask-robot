int irSensors[]  = {A0 , A1 , A2 , A3 , A4 };

int irReads[5];
int irControl = 0;

void lineControl() {
  readIrSensors();
  convertIrSensors();
  //forward
  if (irControl == 100) {
    moveForward();
  }
  //right carve slow
  else if (irControl == 10 || irControl == 110) {
    moveRight(ANGLE_SLOW_ONE);
  }
  // right stop
  else if (irControl == 11) {
    moveRight(ANGLE_STOP_ONE);
  }
  //right reverse
  else if (irControl == 1 || irControl == 111 || irControl == 1111) {
    moveRight(ANGLE_REVERSE_ONE);
  }
  //left carve slow
  else if (irControl == 1000 || irControl == 1100) {
    moveLeft(ANGLE_SLOW_ONE);

  }
  //left stop
  else if (irControl == 11000) {
    moveLeft(ANGLE_STOP_ONE);

  }
  //left reverse
  else if (irControl == 10000 || irControl == 11100 || irControl == 11110) {
    moveLeft(ANGLE_REVERSE_ONE);

  }
}

void readIrSensors() {
  for (int i = 0 ; i < 5 ; i++) {
    irReads[i] = analogRead(irSensors[i]);
  }
}

void convertIrSensors() {

  for (int i = 0; i < 5; i++) {
    if (irReads[i] > IR_LIMIT)
      irReads[i] = 1;
    else
      irReads[i] = 0;
  }
  irControl = irReads[0] * 1 + irReads[1] * 10  + irReads[2] * 100 + irReads[3] * 1000 + irReads[4] * 10000 ;
}

void printIrSerial() {
  for (int i = 0 ; i < 5 ; i++) {
    Serial.print("S");
    Serial.print(i);
    Serial.print(" = ");
    Serial.print(irReads[i]);
    Serial.print(" ");
  }
  Serial.println();

}
