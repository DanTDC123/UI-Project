#include <AccelStepper.h>
#include <PS2X_lib.h>
#include <Servo.h>     

#define HALFSTEP 8

// Motor pin definitions
#define motor1Pin1  2     // IN1 on the ULN2003 driver 1
#define motor1Pin2  3     // IN2 on the ULN2003 driver 1
#define motor1Pin3  4     // IN3 on the ULN2003 driver 1
#define motor1Pin4  5     // IN4 on the ULN2003 driver 1

#define motor2Pin1  6     // IN1 on the ULN2003 driver 1
#define motor2Pin2  7     // IN2 on the ULN2003 driver 1
#define motor2Pin3  8     // IN3 on the ULN2003 driver 1
#define motor2Pin4  9     // IN4 on the ULN2003 driver 1

#define motor3Pin1  10     // IN1 on the ULN2003 driver 1
#define motor3Pin2  11     // IN2 on the ULN2003 driver 1
#define motor3Pin3  12     // IN3 on the ULN2003 driver 1
#define motor3Pin4  13     // IN4 on the ULN2003 driver 1

AccelStepper stepper1(HALFSTEP, motor1Pin1, motor1Pin3, motor1Pin2, motor1Pin4);
AccelStepper stepper2(HALFSTEP, motor2Pin1, motor2Pin3, motor2Pin2, motor2Pin4);
AccelStepper stepper3(HALFSTEP, motor3Pin1, motor3Pin3, motor3Pin2, motor3Pin4);

Servo servo1; 
Servo servo2; 
Servo servo3; 
int pos = 0;

PS2X ps2x;

int error = 0;

byte type = 0;

byte vibrate = 0;

void setup() {
 
  stepper1.setMaxSpeed(3000.0);
  stepper1.setAcceleration(1000.0);
  stepper1.setSpeed(3000);
  stepper1.setCurrentPosition(0);
  

  stepper2.setMaxSpeed(3000.0);
  stepper2.setAcceleration(1000.0);
  stepper2.setSpeed(3000);
  stepper2.setCurrentPosition(0);

  stepper3.setMaxSpeed(3000.0);
  stepper3.setAcceleration(1000.0);
  stepper3.setSpeed(3000);
  stepper3.setCurrentPosition(0);

  servo1.attach(42);
  servo2.attach(44);
  servo3.attach(46);

  Serial.begin(9600);   

  do
  {
    //GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error

    error = ps2x.config_gamepad(52, 50, 53, 51, false, false);

  } while(error !=0 ); 

  Serial.print("Found Controller, configured successful ");

  type = ps2x.readType();
}

void loop() {

  stepper2.run();
  stepper3.run();

  ps2x.read_gamepad(false, vibrate);

    if(ps2x.Button(PSB_START))        
      Serial.println("START");

    if(ps2x.Button(PSB_SELECT))

      Serial.println("SELECT"); 

    if(ps2x.Button(PSB_PAD_UP)){
      servo2.write(0);
      servo2.write(60);
      Serial.println(servo2.read());
      delay(100);
      Serial.println("UP");}


    if(ps2x.Button(PSB_PAD_RIGHT)){      
      servo1.write(0);
      servo1.write(60);
      Serial.println(servo1.read());
      delay(100);
      Serial.println("RIGHT");}

    if(ps2x.Button(PSB_PAD_LEFT)){
      servo1.write(180);
      servo1.write(120);
      Serial.println(servo1.read());
      delay(100);
      Serial.println("LEFT");}

    if(ps2x.Button(PSB_PAD_DOWN)){
      servo2.write(180);
      servo2.write(120);
      Serial.println(servo2.read());
      delay(100);
      Serial.println("DOWN");}

    if(ps2x.Button(PSB_L3))

        Serial.println("L3 pressed");

    if(ps2x.Button(PSB_R3))

        Serial.println("R3 pressed");

    if(ps2x.Button(PSB_L2))

        Serial.println("L2 pressed");

    if(ps2x.Button(PSB_R2))

        Serial.println("R2 pressed");

    if(ps2x.ButtonPressed(PSB_TRIANGLE)){
      stepper1.runToNewPosition(stepper1.currentPosition() + 800);
      Serial.println(stepper1.currentPosition());
      Serial.println("UP");
      Serial.println("TRANGLE");  }     

    if(ps2x.ButtonPressed(PSB_CIRCLE)){
      stepper3.runToNewPosition(stepper3.currentPosition() - 800);
      Serial.println(stepper3.currentPosition());
      Serial.println("O");
    }              

    if(ps2x.NewButtonState(PSB_CROSS)){              
      stepper1.runToNewPosition(stepper1.currentPosition() - 400);
      Serial.println(stepper1.currentPosition());
      Serial.println("DOWN");
      Serial.println("X");}

    if(ps2x.ButtonReleased(PSB_SQUARE)){
      stepper3.runToNewPosition(stepper3.currentPosition() + 800);
      Serial.println(stepper3.currentPosition());
        Serial.println("Square");}   
    
    if(ps2x.Analog(PSS_LY) > 135){
      //Range value pada stick adalah 0~255
      //Kedudukan stick pada value 127,anda boleh tukarkan value yang anda mahu
      servo3.write(180);
      servo3.write(120);
      Serial.println(servo3.read());
      delay(100);
      Serial.println("Square");
     }
     
     if(ps2x.Analog(PSS_LY) < 120 ){
      //Range value pada stick adalah 0~255
      //Kedudukan stick pada value 127,anda boleh tukarkan value yang anda mahu
      servo3.write(0);
      servo3.write(60);
      Serial.println(servo3.read());
      delay(100);
      Serial.println("O");
     }
    if(ps2x.Analog(PSS_RX) > 135){
      stepper2.runToNewPosition(stepper2.currentPosition() - 800);
      Serial.println(stepper2.currentPosition());
      Serial.println("RIGHT");
     }
    if(ps2x.Analog(PSS_RX) < 120 ){
      stepper2.runToNewPosition(stepper2.currentPosition() + 800);
      Serial.println(stepper2.currentPosition());
      Serial.println("LEFT");
     }
    if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1))

    {

      Serial.print("Stick Values:");

      Serial.print(ps2x.Analog(PSS_LY), DEC);

      Serial.print(",");

      Serial.print(ps2x.Analog(PSS_LX), DEC);

      Serial.print(",");

      Serial.print(ps2x.Analog(PSS_RY), DEC);

      Serial.print(",");

      Serial.println(ps2x.Analog(PSS_RX), DEC);

    }
  }    

