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

void setup()

{

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

  // if (stepper1.distanceToGo() == 0) {
    
  // }

  // if (stepper2.distanceToGo() == 0) {
  //   stepper2.moveTo(-stepper2.currentPosition());
  // }
  // if (stepper3.distanceToGo() == 0) {
  //   stepper3.moveTo(-stepper3.currentPosition());
  // }

  Serial.begin(9600);   

  do
  {
    //GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error

    error = ps2x.config_gamepad(52, 50, 53, 51, false, false);

  } while(error !=0 ); 

  Serial.print("Found Controller, configured successful ");

  type = ps2x.readType();

}

void loop()
{

  ps2x.read_gamepad(false, vibrate);

    if(ps2x.Button(PSB_START))        

      Serial.println("START");

    if(ps2x.Button(PSB_SELECT))

      Serial.println("SELECT"); 

    /////Shoulder
    if(ps2x.Button(PSB_PAD_UP)){
      // stepper1.moveTo(20000);
      // stepper1.runSpeedToPosition();
      // stepper1.run();
      stepper1.runToNewPosition(stepper1.currentPosition() + 800);
      Serial.println(stepper1.currentPosition());
      Serial.println("UP");}

    if(ps2x.Button(PSB_PAD_DOWN)){
      // stepper1.moveTo(-20000);
      // stepper1.runSpeedToPosition();
      // stepper1.run();
      stepper1.runToNewPosition(stepper1.currentPosition() - 800);
      Serial.println(stepper1.currentPosition());
      Serial.println("DOWN");
      }
    //////////

      
    // Base
    if(ps2x.Button(PSB_PAD_RIGHT)){
      stepper2.runToNewPosition(stepper2.currentPosition() - 800);
      Serial.println(stepper2.currentPosition());
      Serial.println("RIGHT");
    }
    if(ps2x.Button(PSB_PAD_LEFT)){
      stepper2.runToNewPosition(stepper2.currentPosition() + 800);
      Serial.println(stepper2.currentPosition());
      Serial.println("LEFT");}
    //////

    if(ps2x.Button(PSB_L3))

        Serial.println("L3 pressed");

    if(ps2x.Button(PSB_R3))

        Serial.println("R3 pressed");

    if(ps2x.Button(PSB_L2))

        Serial.println("L2 pressed");

    if(ps2x.Button(PSB_R2))

        Serial.println("R2 pressed");

    if(ps2x.ButtonPressed(PSB_TRIANGLE))
{
        servo2.write(0);
     servo2.write(30);
     Serial.println(servo2.read());
     delay(100);
        Serial.println("TRANGLE");  }     

    if(ps2x.ButtonPressed(PSB_CIRCLE))              
{
        servo3.write(0);
     servo3.write(30);
     Serial.println(servo3.read());
     delay(100);
      Serial.println("O");}

    if(ps2x.NewButtonState(PSB_CROSS))              
 {servo2.write(180);
     servo2.write(150);
     Serial.println(servo2.read());
     delay(100);
      Serial.println("X");}

    if(ps2x.ButtonReleased(PSB_SQUARE))             
{servo3.write(180);
     servo3.write(150);
     Serial.println(servo3.read());
     delay(100);
      Serial.println("Square");}   

    //STICK KIRI
    if(ps2x.Analog(PSS_LY) > 130){
      //Range value pada stick adalah 0~255
      //Kedudukan stick pada value 127,anda boleh tukarkan value yang anda mahu
    
      stepper3.runToNewPosition(stepper3.currentPosition() + 800);
      Serial.println(stepper3.currentPosition());
       Serial.println("KE BAWAH");
     }
     
     if(ps2x.Analog(PSS_LY) < 125 ){
      //Range value pada stick adalah 0~255
      //Kedudukan stick pada value 127,anda boleh tukarkan value yang anda mahu
     stepper3.runToNewPosition(stepper3.currentPosition() - 800);
      Serial.println(stepper3.currentPosition());
       Serial.println("KE BAWAH");
     Serial.println("KE ATAS");
  
     }
     if(ps2x.Analog(PSS_LX) > 130 ){
      //Range value pada stick adalah 0~255
      //Kedudukan stick pada value 127,anda boleh tukarkan value yang anda mahu
     Serial.println("KE KANAN");
  
  
     }
     if(ps2x.Analog(PSS_LX) < 125){
      //Range value pada stick adalah 0~255
      //Kedudukan stick pada value 127,anda boleh tukarkan value yang anda mahu
     Serial.println("KE KIRI");
  
     }

    //STICK KANAN
     if(ps2x.Analog(PSS_RY) > 130){
      //Range value pada stick adalah 0~255
      //Kedudukan stick pada value 127,anda boleh tukarkan value yang anda mahu
      
      
     
     Serial.println("KE BAWAH");

     }
     
     if(ps2x.Analog(PSS_RY) < 125 ){
      //Range value pada stick adalah 0~255
      //Kedudukan stick pada value 127,anda boleh tukarkan value yang anda mahu
     
     
     Serial.println("KE ATAS");
  
     }
     if(ps2x.Analog(PSS_RX) > 130){
      //Range value pada stick adalah 0~255
      //Kedudukan stick pada value 127
     servo1.write(0);
     servo1.write(30);
     Serial.println(servo1.read());
     delay(100);
     Serial.println("KE KANAN");
  
  
     }
     if(ps2x.Analog(PSS_RX) < 125 ){
      //Range value pada stick adalah 0~255
      //Kedudukan stick pada value 127,anda boleh tukarkan value yang anda mahu
     servo1.write(180);
     servo1.write(150);
     Serial.println(servo1.read());
     delay(100);
     Serial.println("KE KIRI");
  
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