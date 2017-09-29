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
byte stepMode = 0;
bool dir = TRUE;
unsigned long stepsToTake = 0;
unsigned long stepsTaken = 0;
bool cmdGo = FALSE;
bool motorRun = FALSE;

void getMotorAngle(void)
{
  /* This code will ask the encoder to return the angle of the motor and
      set the currentMotorAngle variable*/
}

void sendMotorAngle(void)
{
  /* This code will send the currentMotorAngle variable to the I2C bus*/
}

void stepMotor(void) {
  /* code */
  digitalWrite(stepPin, HIGH);
  lastStepTime = micros();
  digitalWrite(stepPin, LOW);
}



/* When motorFreeRun is true, the step count will be ignored and the motor
    will step at every increment time

*/
bool motorFreeRun = TRUE;


void motorUpdateState(void)
{
  /* this code will determine if the motor will move or not
      if the current time minus the previous time is > delaytime then stepMotor()
      record the difference and subtract the interval time, then subtract this from
      the next delay time. delayTime = interval-delayDiff
  */
}


//Read Encoder
SPI.beginTransaction(Encoder);
digitalWrite (selectEncoder, LOW);
// reading only, so data sent does not matter
stat = SPI.transfer(0);
val1 = SPI.transfer(0);
val2 = SPI.transfer(0);
digitalWrite (selectEncoder, HIGH);
SPI.endTransaction();

// Send Data to Motor
SPI.beginTransaction(Motor);
digitalWrite (selectMotor, LOW);
SPI.transfer(motorCMD);
digitalWrite (selectMotor, HIGH);
SPI.endTransaction();









void calcAbsolute(uint current, uint next, bool dir) // Move this to Comm Controller
{
  /* This code will calculate how mant steps to take from the current position
      to get to the next position*/
}
