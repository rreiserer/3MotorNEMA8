/* Target Atmel32U4 Command Controller */

/*
  Monitor serial port for commands from computer and issue commands to the
  individual motor controllers over I2C. Check SD card for programming instructions
  and log motor conditions to the SD card.

  List command set to respond to:
  SetControllerVerbose
  RunRPM - Calculate Step interval and start motor
  MoveTo - Get encoder position, calculate number of steps and take steps
  Start - start motors with previous settings
  Pause - stop motors
  Stop - stop motors
  SetControllerName - Set stored Vairable
  ControllerStatus - Send Command Status
  SetDeviceType - Set stored Vairable
  GetDeviceType - return stored variable
  DeviceStatus -
  ReadCalibrationPoint - return zero
  SetCalibrationPoint - do nothing
  FindZero - Move to zero
  SetDeviceName - Set stored Vairable
  GetDeviceName - return stored variable
  Trigger - do nothing
  FirmwareCheck - return stored variable
  GetControllerName?  It’s not used in AMPERE, so maybe it’s getting its name from feedback.

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

    I2C Command Structure:      Send 5 bytes
                                1 - Command Code
                                2-5 - Command Value
                                Receive 4 bytes


*/
#include <Wire.h> // Used for I2C communication with Motor uCs
#include <SPI>    // Used for SPI communications with SD Cards
#include <SD.h>   // Used for SD Card specific commands

byte cmdCurrent = ""; //Current Command Leter
Ulong cmdVal = 0; // Current Command Value - may be set to cmdCurrent to send command letters

void setup() {

  /*Need to set up pins*/

  Serial.begin(115200); // Initialize  Serial Communications
  Wire.begin(); // Initialize I2C Bus as Master

  /* code */
}

void loop(/* arguments */) {
  /* code */
}

void serialCheck(/* arguments */) {
  /*  Check the serial port for incomming bytes and assemble command string (cmdBytes[])
      calculate a checksum and return on serial port.
  */
  int i = 0;

  if (Serial.available())
  {
    // cmdSet = TRUE;
    cmdByte[i++] = Serial.read();
  }
}

void sendI2C(int addr) {
  /* code */
  Wire.beginTransmission(addr);
  Wire.write(cmdVal);
  Wire.endTransmission();
}

void initSDCard()
{
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
Serial.println("card initialized.");
}

void buildLogString(/* arguments */)
{
  /* code */
String dataString = "";

// read three sensors and append to the string: Change to setup encoder positions

for (int analogPin = 0; analogPin < 3; analogPin++)
{
  int sensor = analogRead(analogPin);
  dataString += String(sensor);
  if (analogPin < 2)
  {
    dataString += ",";
  }
 }
}

// open the file. note that only one file can be open at a time,
// so you have to close this one before opening another.
File dataFile = SD.open("datalog.txt", FILE_WRITE);

// if the file is available, write to it:
if (dataFile) {
  dataFile.println(dataString);
  dataFile.close();
  // print to the serial port too:
  Serial.println(dataString);
}
// if the file isn't open, inform Ampere?
else {
  Serial.println("error opening datalog.txt");
}

// Command Functions

uint getMotorAngle(int num)
{
  /* This function will request the angle from the encoder and return the value as an unsigned integer that
      represents the angle in 100ths of a degree*/
}

long calcSteps(int num) {
  /* code */
}

void moveSteps(/* arguments */) {
  /* code */
}

void moveSpeed(/* arguments */) {
  /* code */
}

void name(/* arguments */) {
  /* code */
}
