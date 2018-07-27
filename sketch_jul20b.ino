

#include <AFMotor.h>
AF_DCMotor motor2(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
AF_DCMotor motor1(1, MOTOR12_64KHZ); // motor #1
char dataIn = 'S';
char determinant;
char det;
int vel = 0; //Bluetooth Stuff
int whitelight = 13;
int redlight = 10;
int trigpin1 = 12;
int echopin1 = 8;
int trigpin2 = 4;
int echopin2 = 6;
long duration1;
long duration2;
long cm1;
long cm2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // set up Serial library at 9600 bps
  Serial.println("Motor test!");
  motor1.setSpeed(255); // set the speed to 200/255
  motor2.setSpeed(255); // set the speed to 200/255
  pinMode(whitelight, OUTPUT);
  pinMode(redlight, OUTPUT);
  pinMode(trigpin1, OUTPUT);
  pinMode(echopin1, INPUT);
  pinMode(trigpin2, OUTPUT);
  pinMode(echopin2, INPUT)
  ;
}

void loop() {
  // put your main code here, to run repeatedly:

  det = check();
  switch (det) {
    case 'F': // F, move forward
      motor1.run(FORWARD); // turn it on going forward
      motor2.run(FORWARD); // turn it on going forwar

      break;

    case 'B': // B, move back
      motor1.run(BACKWARD); // the other way
      motor2.run(BACKWARD); // the other way
      break;

    case 'L':// L, move wheels left
      motor1.run(FORWARD); // turn it on going forward
      motor2.run(RELEASE); // stopped
      break;

    case 'R': // R, move wheels right
      motor1.run(RELEASE); // stopped
      motor2.run(FORWARD); // turn it on going forward
      break;

    case 'S': // S, stop
      motor1.run(RELEASE); // stopped
      motor2.run(RELEASE); // stopped
      break;

    case 'U': // V, Red light on
      //Serial.println("Red LIght On");
      digitalWrite(redlight, HIGH);
      break;

    case 'u': //v, Red light off
      //Serial.println("Red Light Off");
      digitalWrite(redlight, LOW);
      break;

    case 'W': //W, Front Lights On
      //Serial.println("White LIght On");
      digitalWrite(whitelight, HIGH);
      break;

    case 'w': //w, Front Lights Off
      //Serial.println("White Light Off");
      digitalWrite(whitelight, LOW);
      break;
  }
}
long determining ()
{
  digitalWrite(trigpin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin1, LOW);
  duration1 = pulseIn(echopin1, HIGH);
  cm1 = duration1 * 0.034 / 2;
  digitalWrite(trigpin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin2, LOW);
  duration2 = pulseIn(echopin2, HIGH);
  cm2 = duration1 * 0.034 / 2;

}


//get bluetooth code received from serial port
char check() {
  if (Serial.available() > 0) { // if there is valid data in the serial port
    dataIn = Serial.read();// stores data into a varialbe

    //check the codedigitalWrite(trigPin, LOW);
    if (cm1 < 50)
    { determinant = 'B';
    }
    else if (cm2 < 50)
    { determinant = 'F';
    }
    if (dataIn == 'F') { //Forward
      determinant = 'F';
    }
    else if (dataIn == 'B') { //Backward
      determinant = 'B';
    }
    else if (dataIn == 'L') { //Left
      determinant = 'L';
    }
    else if (dataIn == 'R') { //Right
      determinant = 'R';
    }
    else if (dataIn == 'S') { //Stop
      determinant = 'S';

    }
    else if (dataIn == 'U') { //Red Lights On
      determinant = 'U';
    }
    else if (dataIn == 'u') { //Red Lights Off
      determinant = 'u';
    }
    else if (dataIn == 'W') { //White Lights On
      determinant = 'W';
    }
    else if (dataIn == 'w') { //White Lights Off
      determinant = 'w';
    }
    return determinant;
  }
}

