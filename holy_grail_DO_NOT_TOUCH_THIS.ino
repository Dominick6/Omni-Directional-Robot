#include <PS2X_lib.h>

#define PS2_DAT        13  //14    
#define PS2_CMD        11  //15
#define PS2_SEL        10  //16
#define PS2_CLK        12  //17

//#define pressures   true
#define pressures   false
//#define rumble      true
#define rumble      false

PS2X ps2x;

#include <Servo.h>
int pos = 0;
int error = 0;
byte type = 0;
byte vibrate = 0;
Servo myservo;  // create servo object to control a servo
void setup() {
  // put your setup code here, to run once:
  myservo.attach(9);
  Serial.begin(57600);

  delay(300);
  myservo.write(pos);
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

  if (error == 0) {
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
    if (pressures)
      Serial.println("true ");
    else
      Serial.println("false");
    Serial.print("rumble = ");
    if (rumble)
      Serial.println("true)");
    else
      Serial.println("false");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  }
  else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  //  Serial.print(ps2x.Analog(1), HEX);

  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.print("Unknown Controller type found ");
      break;
    case 1:
      Serial.print("DualShock Controller found ");
      break;
    case 2:
      Serial.print("GuitarHero Controller found ");
      break;
    case 3:
      Serial.print("Wireless Sony DualShock Controller found ");
      break;
  }
}


void loop() {
  // put your main code here, to run repeatedly:
  if(error == 1) //skip loop if no controller found
    return; 

    ps2x.read_gamepad(false, vibrate);
  
  if (ps2x.ButtonPressed(PSB_CIRCLE)){//will be TRUE if button was JUST pressed
    Serial.print(pos);
    myservo.write(pos+20);
    Serial.print("circle");
    Serial.println("Circle just pressed");
  }

delay(50);
}

