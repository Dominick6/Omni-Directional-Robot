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
int potpin = 0;
int val = analogRead(0);
int pos = 0;
int error = 0;
byte type = 0;
byte vibrate = 0;
bool servospin = false;
Servo myservoA;  // create servo object to control a servo
Servo myservoB;  // create servo object to control a servo
Servo myservoC;  // create servo object to control a servo
void setup() {
  myservoA.attach(9);
  myservoB.attach(8);
  myservoC.attach(6);
  // put your setup code here, to run once:
  Serial.begin(57600);

  delay(300);
  myservoA.write(pos);
  myservoB.write(pos);
  myservoC.write(pos);
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
    Serial.println("Note: Go to www.billporter.inf2o for updates and to report bugs.");
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
  
  if (ps2x.ButtonPressed(PSB_CIRCLE)){ //will be TRUE if button was JUST pressed
    Serial.print(pos);
    myservoA.write(1700);
    myservoB.write(1700);
    myservoC.write(1700);
    Serial.print("circle");
    Serial.println("Circle just pressed");
  }
  if(ps2x.ButtonPressed(PSB_SQUARE)){ //will be TRUE if button was JUST pressed OR released
    Serial.print(pos);
    myservoA.write(1300);
    myservoB.write(1300);
    myservoC.write(1300);
    Serial.print("Square");
    Serial.println("Square just released");
  }
   if(ps2x.Button(PSB_TRIANGLE)){ //will be TRUE if button was JUST pressed OR released
     Serial.print(pos);
     myservoA.write(1500);
     myservoB.write(1500);
     myservoC.write(1500);
     Serial.print("Triangle");
     Serial.println("Triangle pressed");
   }
    if(ps2x.Button(UP_STRUM)){          //will be TRUE as long as button is pressed
      Serial.print(pos);
      myservoA.write(1700);
      Serial.println("Up Strum");
    }
    if(ps2x.Button(DOWN_STRUM)){
      Serial.print(pos);
      myservoB.write(1300);
      Serial.println("DOWN Strum");
     }
      if(ps2x.Button(PSB_R3)){
        val = analogRead(potpin);
        val = map(val, 0, 1023, 0, 179);
        myservoA.write(val);
        Serial.println("R3 pressed");
      }
delay(50);
}

