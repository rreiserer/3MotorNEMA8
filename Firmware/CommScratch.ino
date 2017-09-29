//Functions


void loop() {
  int i=0;

  if (Serial1.available()) {
    delay(100); //allows all serial sent to be received together
    while(Serial1.available() && i<4) {
      str[i++] = Serial1.read();
    }
    str[i++]='\0';
  }

  if(i>0) {
    Serial.println(str,4);
  }
}

void calcMode(int) // Move to Comm Controller
{
  /* This code will calculate the stepping mode based on the RPM value sent from
      the main controller. This code should be called as soon as an rpm change
      request comes in.*/
}

void calcRPM(int) // Move to Comm Controller
{
  /* This code will calculate the step interval from an RPM value*/
}

void calcRPH(int) // Move to Comm Controller
{
  /* This code will calculate the step interval from an RPH value
    step inteval = RPH
    3600RPH = 60RPM = 1RPS = 200 steps per second in whole stepping 5000us
                            400 Half step 2500us
                            800 quarter step 1250us
                            3200 microstep 312.5us
              /60     /60     *(mode)
  */
}

void stepMode(byte modeNum)
{
  /* Set MS0 & MS1 Stepping Mode */
  /* 0 = Whole Steps */
  /* 1 = Half Steps */
  /* 2 = Quarter Steps */
  /* 3 = Sixteenth Steps */
  /* Write to bits 11 & 12 of Config Register 0 */
}

bool parityInt(int16_t wordIn)
{
  bool parityBit = 0;// Parity should be set to zero at the beginning for even parity
  // Loop through each bit and toggle the parity bit on every 1
  for (int8_t i = 0; i < 15; i++)
  {
    if (wordIn>>i&0x0001)
    {
      parityBit =^ 0x0001;
    }
    else
    {
      /* do nothing */
    }
  }
}

/* Code to decide what to do with the incomming I2C command*/
void cmdParse (void)
{
  switch (*cmdBytes) { // *cmdBytes should be the same as cmdBytes[0]
    case A: //Comm??
      // Absolute Angle Move
      //
      // Call getMotorAngle(), calculate steps to new position
      // Call stepMotor()
      // Return ack()
    break;
    case R: //Comm??
      // Relaive Angle Move
      // Current motor angle is not needed? Calculate number of steps, Call stepMotor() Return ack()
    break;
    case I:
      // Interval Step Time in micros
      // Change the variable for step interval time
    break;
    case S:
      // Steps to Take
      // Change the steps Variable
    break;
    case D:
      // Direction of Motor Rotation
      // Change the direction variable
    break;
    case V: //Comm??
      // Velocity (RPH)
      // calculate step interval time from RPH and change step interval variable
    break;
    case P:
      // Position Feedback
      // Read the currentPosition from the encoder and return value on I2C
    break;
    case M:
      // Set Stepping Mode
      // Change DIO pins to reflect requested mode 0-3 0=full step, 1=halfstep, 2 = quarterstep, 3 = microstep
    break;
    case G: //Comm??
      // Go with previously saved values on Specified Motor (0 Starts All)
      // May not need... Could be handled at Comm Controller level
    break;
    case H: //Comm??
      // Halt Specified Motor (0 Halts All)
      // this requires that all command routines are non blocking... this should set all motors
      // running status bit to FALSE
    break;
    case L: //Comm??
      // Logging Interval and Start logging zero value stops logging
      // this should be handles from Comm Controller since the Motor controllers don't have access to the SD Card
    break;
    case a: // lower case letters only set the variable (no motion) Use "G" to run
      // Absolute Angle
    break;
    case r:
      // Relaive Angle
    break;
    case i:
      // Interval Step Time in micros
    break;
    case s:
      // Steps to Take
    break;
    case d:
      // Direction of Motor Rotation
    break;
    case v:
      // Velocity (RPH)
    break;
    case l;
      // Logging Interval
    break;
    default:
    // Command error
  }case
}
