
#include <AFMotor.h>
AF_DCMotor motor2(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
AF_DCMotor motor1(1, MOTOR12_64KHZ); // motor #1
char dataIn = 'S';
char determinant;
char det;
int vel = 0; //Bluetooth Stuff
int whitelight = 13;
int redlight = 10;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); // set up Serial library at 9600 bps
Serial.println("Motor test!");
motor1.setSpeed(255); // set the speed to 200/255
motor2.setSpeed(255); // set the speed to 200/255
pinMode(whitelight, OUTPUT);
pinMode(redlight, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  
  //serial code analysis
  det = check();
  switch (det){
    case 'F': // F, move forward
    motor1.run(FORWARD); // turn it on going forward
    motor2.run(FORWARD); // turn it on going forward

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

//get bluetooth code received from serial port
char check(){
  if (Serial.available() > 0){// if there is valid data in the serial port
    dataIn = Serial.read();// stores data into a varialbe
    
    //check the code
    if (dataIn == 'F'){//Forward
      determinant = 'F';
    }
    else if (dataIn == 'B'){//Backward
      determinant = 'B';
    }
    else if (dataIn == 'L'){//Left
      determinant = 'L';
    }
    else if (dataIn == 'R'){//Right
      determinant = 'R';
    }
    else if (dataIn == 'S'){//Stop
      determinant = 'S';
    
    }
    else if (dataIn == 'U'){//Red Lights On
      determinant = 'U';
    }
    else if (dataIn == 'u'){//Red Lights Off
      determinant = 'u';
    }
    else if (dataIn == 'W'){//White Lights On
      determinant = 'W';
    }
    else if (dataIn == 'w'){//White Lights Off
      determinant = 'w';
    }
  return determinant;
}
}
