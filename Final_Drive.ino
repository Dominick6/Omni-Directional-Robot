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
int RX;
int RY;
int LX;
int LY;
void setup() {
   myservoA.attach(9); // attaches the servo on pin 9 to the servo object
  myservoB.attach(8);
  myservoC.attach(6);
  Serial.begin(57600);

  delay(300);
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
}

void loop() {
  Serial.print("Stick Values");
  Serial.print(val);
  //ps2x.read_gamepad();
  RX = (ps2x.Analog(PSS_RX));
  RY = (ps2x.Analog(PSS_RY));
  LX = (ps2x.Analog(PSS_LX));
  LY = (ps2x.Analog(PSS_LY));
  ps2x.read_gamepad();

  if (RX != 127 || RY != 128){
  Serial.println(ps2x.Analog(PSS_RX), DEC);
  Serial.println(ps2x.Analog(PSS_RY), DEC);
  myservoB.write(map(RX, 0, 255, 1000, 2000));
  myservoB.write(map(RY, 0, 255, 1000, 2000));
  }
  if (LX != 127 || LY != 128){
   Serial.println(ps2x.Analog(PSS_LX), DEC);
   Serial.println(ps2x.Analog(PSS_LY), DEC);
   myservoA.write(map(LX, 0, 255, 1000, 2000));
   myservoC.write(map(LY, 0, 255, 1000, 2000));
  }
  }

