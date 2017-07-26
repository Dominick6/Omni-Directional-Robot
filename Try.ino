#include <PS2X_lib.h>

#define PS2_DAT     13  //14
#define PS2_CMD     11  //15
#define PS2_SEL     10  //16
#define PS2_CLK     12  //17

//#define pressures   true
#define pressures   false
//#define rumble      true
#define rumble      false

PS2X ps2x;
#include <Servo.h>
Servo myservoA; // create servo object to control a servo
Servo myservoB;
Servo myservoC;
int val = 10; // variable to read the value from the  
int error = 0;
int pos = 0;
void setup() {
  myservoA.attach(9); // attaches the servo on pin 9 to the servo object
  myservoB.attach(8);
  myservoC.attach(6);
  Serial.begin(57600);
  
  delay(300);
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  myservoA.write(pos);
  myservoB.write(pos);
  myservoC.write(pos);
}
void loop() {
  /* You must Read Gamepad to get new values and set vibration values
     ps2x.read_gamepad(small motor on/off, larger motor strenght from 0-255)
     if you don't enable the rumble, use ps2x.read_gamepad(); with no values
     You should call this at least once a second
   */
   ps2x.read_gamepad();  
if(ps2x.Button(PSB_L3) || ps2x.Button(PSB_R3)) { //print stick values if either is TRUE
  val = map(val, 0, 1023, 0, 179);  // scale it to use it with
   // the servo (value between 0 and
   // 180)
   myservoA.write(val);    // sets the servo position according
   // to the scaled value
   myservoB.write(val);
   myservoC.write(val);
   Serial.print("Stick Values:");
   Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
   Serial.print(",");
   Serial.print(ps2x.Analog(PSS_LX), DEC); 
   Serial.print(",");
   Serial.print(ps2x.Analog(PSS_RY), DEC); 
   Serial.print(",");
   Serial.println(ps2x.Analog(PSS_RX), DEC); 
   Serial.print(val);
   myservoA.write(ps2x.Analog(PSS_RX));
   myservoB.write(ps2x.Analog(PSS_LX));
   myservoC.write(ps2x.Analog(PSS_LY));
   myservoC.write(ps2x.Analog(PSS_RY));
   delay(15);       // waits for the servo to get there
}
}

