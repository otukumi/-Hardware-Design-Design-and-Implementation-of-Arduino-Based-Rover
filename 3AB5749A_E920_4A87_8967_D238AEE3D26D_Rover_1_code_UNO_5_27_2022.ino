//  Change the values below to change Rover Speed
//  Speed range values are 0 to 255 Fast

// +++++ Forward & Reverse sppeds +++++
const int MotorSpeed1 = 125;  // Change values to set
const int MotorSpeed2 = 125;  // motor speed

// +++++ Right & Left Turn Speeds
const int MotorSpeedTurn1 = 85;  // Change values to set
const int MotorSpeedTurn2 = 85;  // motor speed

/*     Rover Control Application
       STEM Teacher Coding and Robotics Workshop
       Virginia State University
       March 2020
       Dr. Walt Deal Dr. Steve Hsuing  Dr. Feng Jao
       Old Dominion Univesity and Ohio Northern University
       Norfolk, Virginia

      This code is used with the Arduino
      FunduMoto L298N motor Shield with
      buzzer on Pin4 and Bluetooth transceiver
      socket. Other motor drivers may be used -
      Note changes in L298 pin assignments
      for pwm motor control.

      Android Smart Phone Application ArduinoRC
      See: https://arduinorc.en.aptoide.com/
      Alternately See Google Play

      Motor Pins
      Pin 10 = MotorRight1 Motor Speed
      Pin 12 = MotorRight2 Motor Direction
      Pin 11 = MotorRight1 Motor Speed
      Pin 13 = MotorRight2 Motor Direction

      Note: Battery type/voltage affects
      speed and power! Recommend using three
      18650 LiPo batteries. Change PWM values
      to suit battery type and desired speed.
      Note: PWM using analogWrite() will only
      work on pins 3, 5, 6, 9, 10 and 11.
              ++++++++++++++
    Must REMOVE Bluetooth Transciever when programming!
    Remove and Replace with power OFF!
              ++++++++++++++
    Stepper and Limit Switch Pins
    Three control pins are used on the DRV 8825 driver
    board - Enable, Step and Direction. The enable pin is
    used to turn off driver board to reduce current drain
    on batteries and prevent overheating of stepper motors.

    Pins A0 and A1 disable and enable stepper motord
    Pins A2 and A3 Top Stepper1 Limit Switch
    Pins 2 and 3 Bottom Stepper Limit Switch
    Pins A4 and A5 Stepper1 step and direction
    Pins 6 and 7 Stepper2 step and direction
    Key Function definitions
    Rover Motors
    U = forward D = reverse R = right turn L = left Turn
    Camera motion
    u = up d = down l = camera left r = camera right
*/

int MotorRight1 = 10;
int MotorRight2 = 12;
int MotorLeft1 = 11;
int MotorLeft2 = 13;

void setup()
{
  //  Set Up Serial Connection
  Serial.begin(9600);

  //  Rover Motor control setup
  pinMode(MotorRight1, OUTPUT); // Other L298 boards may use pin  5 (PWM)
  pinMode(MotorRight2, OUTPUT); // pin  6 (PWM)
  pinMode(MotorLeft1, OUTPUT); // pin  10 (PWM)
  pinMode(MotorLeft2, OUTPUT); // pin  11 (PWM)
  Serial.println("Rover Controller Check"); // added to check key strokes

  //  Top Stepper controls the Camera: Limit: A2 up, A3 Dn, Dir A4, Step A5
  //  Enable and Disable Controls of the Stepper Drivers
  pinMode(A0, OUTPUT); // Enalbe/Disable on top stepper
  pinMode(A1, OUTPUT); // Enalbe/Disable on base stepper
  digitalWrite(A0, HIGH); //Disable top stepper
  digitalWrite(A1, HIGH); //Disable base stepper

  pinMode(A4, OUTPUT); // Stepper 2
  pinMode(A5, OUTPUT);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);

  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  digitalRead(A2);
  digitalRead(A3);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);

  //  Base stepper controls the Base: Limit: D2 Left, D3 Right, Dir D6, Step D7
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);

  pinMode(2, INPUT);
  pinMode(3, INPUT);
  digitalRead(2);
  digitalRead(3);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
}

//  Rover DC Motor Drive Control Functions
void go()// Rover goes forward
{
  //  Analog is for PWM speed control
  //  Digital pin controls direction
  analogWrite(MotorRight1, MotorSpeed1); // Sets motor speed
  digitalWrite(MotorRight2, HIGH);       // Sets direction
  analogWrite(MotorLeft1, MotorSpeed2);
  digitalWrite(MotorLeft2, HIGH);
}

void right() // Rover turns left
{
  analogWrite(MotorRight1, MotorSpeedTurn1);
  digitalWrite(MotorRight2, HIGH);
  analogWrite(MotorLeft1, MotorSpeedTurn2);
  digitalWrite(MotorLeft2, LOW);
}

void left() // Rover turns right
{
  analogWrite(MotorRight1, MotorSpeedTurn1);
  digitalWrite(MotorRight2, LOW);
  analogWrite(MotorLeft1, MotorSpeedTurn2);
  digitalWrite(MotorLeft2, HIGH);
}

void stop() // Rover stops
{
  analogWrite(MotorRight1, 0);
  digitalWrite(MotorRight2, LOW);
  analogWrite(MotorLeft1, 0);
  digitalWrite(MotorLeft2, LOW);
}

void back() // Rover goes backwards
{
  digitalWrite(MotorRight2, LOW);
  analogWrite(MotorRight1, MotorSpeed1); //120
  digitalWrite(MotorLeft2, LOW);
  analogWrite(MotorLeft1, MotorSpeed2); //120
}

//  Turn Camera Base: Base Stepper trun left with D3 input/limit switch sensor
void base_left()  //Stepper 2
{
  digitalWrite(A1, LOW);      //Enable base stepper
  for (int i = 0; i <= 200; i++)
  {
    digitalWrite(6, HIGH);  // add this for stepper direction
    digitalWrite(7, HIGH);
    delay(1);
    digitalWrite(7, LOW);
    delay(1);
  }
  digitalWrite(A1, HIGH);     //Disable base stepper
}

//  Turn Camera Base: Base Stepper turn right with D2/limit switch input sensor
void base_right() //Stepper 2
{
  digitalWrite(A1, LOW);      //Enable base stepper
  for (int i = 0; i <= 200; i++)
  {
    digitalWrite(6, LOW);   // add this for stepper direction
    digitalWrite(7, HIGH);
    delay(1);
    digitalWrite(7, LOW);
    delay(1);
  }
  digitalWrite(A1, HIGH);     //Disable base stepper
}

void base_right_hm()  //Fine turn the Stepper 2 on the base home position
{
  digitalWrite(A1, LOW);      //Enable base stepper
  for (int i = 0; i <= 165; i++)
  {
    digitalWrite(6, LOW);   // add this for stepper direction
    digitalWrite(7, HIGH);
    delay(1);
    digitalWrite(7, LOW);
    delay(1);
  }
  digitalWrite(A1, HIGH);     //Disable base stepper
}

//Turn Camera Up: Top Stepper turn up with A2 input/limit switch sensor
void camera_up() // Stepper 1
{
  digitalWrite(A0, LOW);     //Enable top stepper
  digitalWrite(A4, HIGH);    // add this for stepper direction
  for (int i = 0; i <= 100; i++)
  {
    digitalWrite(A5, HIGH);
    delay(1);
    digitalWrite(A5, LOW);
    delay(1);
  }
  digitalWrite(A0, HIGH);   //Disable top stepper
}


//  Turn Camera DN: Top Stepper turn down with A3 input/limit switch sensor
void camera_dn() // Stepper 1
{
  digitalWrite(A0, LOW);    //Enable top stepper
  digitalWrite(A4, LOW);    // add this for stepper direction
  for (int i = 0; i <= 100; i++)
  {
    digitalWrite(A5, HIGH);
    delay(1);
    digitalWrite(A5, LOW);
    delay(1);
  }
  digitalWrite(A0, HIGH);   //Disable top stepper
}

void camera_dn_hm() // Fine tune the on Steppe1 for camera home position
{
  digitalWrite(A0, LOW);    //Enable top stepper
  digitalWrite(A4, LOW);    // add this for stepper direction
  for (int i = 0; i <= 80; i++)
  {
    digitalWrite(A5, HIGH);
    delay(1);
    digitalWrite(A5, LOW);
    delay(1);
  }
  digitalWrite(A0, HIGH);   //Disable top stepper
}

//Top Camera Home
void camera_home()
{
  if (digitalRead(A3) == HIGH)
  {
    while (digitalRead(A3) == HIGH)
    {
      camera_dn();
      delay(10);
    }
  }
  if (digitalRead(A2) == HIGH)
  {
    while (digitalRead(A2) == HIGH)
    {
      camera_up();
      delay(10);
    }
  }

  for (int i = 0; i <= 2; i++)
  {
    camera_dn_hm();
    delay(10);
  }
}

//Base Stepper Home
void base_home()
{
  if (digitalRead(3) == HIGH)
  {
    while (digitalRead(3) == HIGH)
    {
      base_right();
      delay(10);
    }
  }
  if (digitalRead(2) == HIGH)
  {
    while (digitalRead(2) == HIGH)
    {
      base_left();
      delay(10);
    }
  }

  for (int i = 0; i <= 2; i++)
  {
    base_right_hm();
    delay(10);
  }
}

void go_home()  //move base home first on Stepper 2, then camera home second on Stepper1
{
  base_home();
  camera_home();
}

void loop() //The main control loops
{
  // Added for remote control apk
  char val = Serial.read();
  //  Serial.write(val);

  switch (val)
  {
    //  Controls for camera position - up - down - left - right
    case 'h':       //'h' stands for home position
      go_home();
      Serial.println("h key pressed");  //Display key press on pc Arduino monitor screen
      val = 0;
      break;
    case 'd':       //'u' moves camera up position
      camera_up();
      val = 0;
      break;
    case 'u':        //'d' moves camera down position
      camera_dn();
      val = 0;
      break;
    case 'l':      //'l' moves camera left position
      base_left();
      val = 0;
      break;
    case 'r':       //'r' moves camera right position
      base_right();
      val = 0;
      break;

    //  Control of the Rover DC Motors
    case 'U':       //'U' Rover goes forward
      go();
      val = 0;
      break;
    case 'L':       //'L' Rover turns left position
      left();
      val = 0;
      break;
    case 'R':       //'R' Rover turns right position
      right();
      val = 0;
      break;
    case 'D':       //'D' Rover goes backward
      back();
      val = 0;
      break;
    case 'S':       //'S' Stop Rover
      stop();
      val = 0;
      break;
    default:
      digitalWrite(A0, HIGH); //Disable top stepper
      digitalWrite(A1, HIGH); //Disable base stepper
      delay(500);
      break;
  }

}
