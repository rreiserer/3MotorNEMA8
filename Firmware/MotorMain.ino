/*Firmware for Motor uController
  ATmega8A Tartget

  Pin Configurations are defined in MotorOne, MotorTwo, and MotorThree files

  Rx and Tx of the UART should be set to inputs to prevent interference with other communications
  it should be possible to tell the Motor Controllers to turn on the Rx and Tx on the UART if serial
  communications are required.

  First pass should utilize SPI Bus for setup but Step pin will be used to advance
    motor position. Most pins will be set during setup and not changed.

  uC's get standard Arduino Bootloader

  Master sends a command letter and four bytes to make an unsigned long
  Slave sends a response and an acknowledge character ($)
  Master master sends command value to Slave
  Slave responds with Value acknowledge character (#)
  Slave responds with completion Character (@)

  Command list for Motor uCs: A (0 - 3599)     Absolute Angle (int)
                              R (-32,768 - 32,767)  Relative Angle (int)
                              I (0-4,294,967,295) Step Interval in micros (ULong)
                              S (0-4,294,967,295) Steps to take (ULong)
                              D (0-1) Motor Direction (bool)
                              V (-32,768 - 32,767)  Velocity (RPH) (int) // Could be used for angle speed
                              v (-32,768 - 32,767) Velocity (RPH) Speed to use for other commands
                              P Return Current Position Absolute Angle (int)
                              M Return Stepping Mode (byte)
                              G Go with last value
                              H (0-3) Halt the numbered device or all devices if zero
                              use lower case to setup parameters but not act on them

  Step pulses should be about 10uS

      Functions
        Setup Encoder
        Check current position
        Setup Motor
        Move Motor to New Position
          Calls check Current Position
          Calls Setup Motor
          Sends Step Pulses at set Interval
          Calls Check Position
          Compares current position to desired position
        Rotate Motor at a Set Speed

  SPI Data can be gathered at maximum speed at all times and the current state of the variables can be passed
    back to the Master when a request comes in.

  Set Global Variables outside of Functions
*/
#include <SPI.h> // Required to communicate with Stepper Driver and Encoder
#include <Wire.h> // Required to communicate with Comm Controller

/*Include Motor Pin Setup Code*/
#include "MotorOne" // Or MotorTwo Or MotorThree

/* Motor Global Variables */
int16_t inBytes[10]; //??
byte cmdBytes[5]; // Commands are five bytes. First byte is Command, next four are data (unsigned long)
byte bytesRead = 5;
bool cmdNew = FALSE; // use to indicate that a new command is ready ??
bool cmdDone = FALSE; // use to indicate the a command is being processed ??
bool cndBusy = FALSE; // use to indicate that a command is in progress
int ss = selectMotor;
unsigned long interval = 2000; // default to 75 RPM in Half Step Mode
unsigned long adjInterval = 2000;
unsigned long lastStepTime = 0;
byte stepMode = 1;
bool dir = TRUE;
unsigned long stepsToTake = 0;
unsigned long stepsTaken = 0;
bool cmdGo = FALSE;
bool motorRun = FALSE;

void setup()
{
  //Serial.begin(115200); RX & TX should be High Z once program starts (Maybe used later)
  // the serial pins are both set to inputs in the motor include SPISettings settingsA(2000000, MSBFIRST, SPI_MODE1);
  SPISettings Motor(4000000, MSBFIRST, SPI_MODE3);
  SPISettings Encoder(4000000, MSBFIRST, SPI_MODE1);
  Wire.begin(motorNum);
  SPI.begin(); // Initialize SPI pins

  Wire.onReceive(receiveEvent); //Register Function to run each time I2C Master sends a byte
  Wire.onRequest(requestEvent); //Register Function to run each time I2C Master requests a byte
  /*Initial release will set up the motor driver through th IO pins*/
  setupMotor(stepMode, dir);

  /* Need Function to setup the encoder over SPI
    requirements:
      Read Diagnostics Register
      */
  /* Need Function to set up motor controller SPI*/
  /* Check encoder position, move motor to zero position, reset motor driver and enable Output
     this position should be zero if flat is always ground in the same position*/
  /* Need Function to test the torque requirements and set reference voltage - Compare to last run?*/
  /* Track the changes in torque requirements as a break-in and wear out indicator*/


}

void loop() // Main Loop
{
  /* Check to see if any new commands have been issued */
  /* Read the encoder*/
  /* Step the motor? */
  /* Set the reference voltage for current control - ongoing tests? */

  if(cmdNew)
  {
    cmdBusy = TRUE;
    cmdNew = FALSE;
    cmdParse();
  }
  cmdStatus();
  motorUpdate();

}

void motorUpdate(void)
{
  /* Check to see if the motor needs to be updated
      this will depend on the status of several variables
      check the step clock... this should just run all the time at the setting of the interval
      if motorRun = TRUE then take a step*/

  if(micros()-lastStepTime>=adjInterval)
  {

    if(motorRun)
    {
      stepMotor();
    }
    else
    {
      adjInterval = interval-(micros()-lastStepTime-interval);
      lastStepTime = micros();
    }
  }
  // stepTimer = millis();

}

void stepMotor(void)
{
  /* code */
  digitalWrite(stepPin, HIGH);
  adjInterval = interval-(micros()-lastStepTime-interval);
  lastStepTime = micros();

  digitalWrite(stepPin, LOW);
}

void cmdStatus(void)
{
  /* for a run command the status will only change when a stop running command is issued
      for a number of steps command a count must be tracked and the motorRun made FALSE at the end of the count
      when the command is done the cmdBusy is made FALSE and the cmdDone made TRUE*/
  if (stepsTaken>=stepsToTake)
  {
    motorRun = FALSE;
  }

}

unsigned long readEncoder(void)
{
  /* Request angle value from Encoder - This will be an SPI call
  */
  unsigned long encoderAngle;
  SPI.beginTransaction(Encoder);
  digitalWrite (selectEncoder, LOW);
  byte val1 = SPI.transfer(0xFF);
  byte val2 = SPI.transfer(0xFF);
  digitalWrite (selectEncoder, HIGH);
  SPI.endTransaction();
  encoderAngle = ((val1<<8)|val2)&0x3FFF;
  return encoderAngle;

}

// Below are functions for setup and the main loop
void receiveEvent(void) // Function to handle a request from the I2C Master
{
  /* code */
  cmdNew = TRUE;
  if(0<Wire.available()) // Read 5 bytes into the command array and exit
  {
    for(i=0;i<bytesRead;i++)
    {
      cmdBytes[i]=Wire.read();
    }
  }
}

unsigned long cmdVar(void)
{
  /* code */
  unsigned long cmdVal = cmdBytes[1];
  cmdVal = (cmdVal << 8) + cmdBytes[2];
  cmdVal = (cmdVal << 8) + cmdBytes[3];
  cmdVal = (cmdVal << 8) + cmdBytes[4];
  return cmdVal
}

/* Code to decide what to do with the incomming I2C command*/
void cmdParse (void)
{
  switch (*cmdBytes) { // *cmdBytes should be the same as cmdBytes[0]
    case 'I':
      // Interval Step Time in micros
      // Change the variable for step interval time
      interval = cmdVar();
    break;
    case 'S':
      // Steps to Take
      // Change the steps Variable
      stepToTake = cmdVar();
    break;
    case 'D':
      // Direction of Motor Rotation
      // Change the direction variable
      dir = cmdVar();
    break;
    case 'P':
      // Position Feedback
      // Read the currentPosition from the encoder and return value on I2C
      readEncoder();

    break;
    case 'M':
      // Set Stepping Mode
      // Change DIO pins to reflect requested mode 0-3 0=full step, 1=halfstep, 2 = quarterstep, 3 = microstep
      stepMode = cmdVar();
    break;
    case 'G':
      // Start motor
      motorRun = TRUE;
    break;
    case 'H':
      // Halt Motor
      motorRun = FALSE;
    break;
    default:
    // Command error
  }case
}


int16_t requestEvent(void)
{
  // Code to send data when master makes a request
  // Currently the only thing to request is the position
  unsigned long motorAngle = readEncoder();
  byte val1 = motorAngle >> 8;
  byte val2 = motorAngle & 0x00FF;
  Wire.write(val1);
  Wire.write(val2);
}

void setupMotor(byte newMode, bool newDir)
{
  /* code */
  digitalWrite(dirPin, NewDir);

  if(newMode & 0x01)
  {
    digitalWrite(modePin0, HIGH);
  }
  else
  {
    digitalWrite(modepin0, LOW);
  }

  if((newMode>>1) & 0x01)
  {
    digitalWrite(modePin1, HIGH);
  }
  else
  {
    digitalWrite(modepin1, LOW);
  }

}
