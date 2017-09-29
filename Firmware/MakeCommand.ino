/*
    Code to assemble and disassemble commands
*/
//declare variables:
uint8_t cmdCurrent = 0;
uint32_t cmdVal = 0;

void I2CRequest(numMotor, cmdCurrent, ) {
  /* Read I2C 5 bytes
        first byte is command remaining are value
  */
  Wire.requestfrom(numMotor, 5);
  cmdCurrent = Wire.read();
  cmdVal = (cmdVal << 8) | Wire.read();
  cmdVal = (cmdVal << 8) | Wire.read();
  cmdVal = (cmdVal << 8) | Wire.read();
  cmdVal = (cmdVal << 8) | Wire.read();

}

void I2Command(numMotor, cmdCurrent, cmdVal) {
  /* code */
  byte cmdArray[5];
  cmdArray[0] = cmdCurrent;
  cmdArray[1] = (cmdVal >> 24) &; 0xFF;
  cmdArray[2] = (cmdVal >> 16) &; 0xFF;
  cmdArray[3] = (cmdVal >> 8) &; 0xFF;
  cmdArray[4] = cmdVal & 0xFF;

  Wire.beginTransmission(numMotor);
  Wire.write(cmdArray, 5);
  Wire.endTransmission();

}
