/*A4979 Code*/
/*
Testing needs to be done to see how the Mode Step (MS) pins respond when the serial registers are set differently

Initialization Requires a 1mS wake up time from Hardware or Software Enable. Hardware Enable must be set low for Software Enable to work
should include reading the Fault 0 register to see if there has been a Power On Reset - This Register gets reset when read.
Should include reading the Fault Register 1 to get the current Step Angle (possibly set the current step angle to match the encoders reported
  position so that no jump occurs when enabling the motor)


Register Table
Write operations use 16-bit words
Bits 15 & 14 select the register to write to
15 | 14
 0 |  0 - Config Register 0
 0 |  1 - Config Register 1
 1 |  0 - Run Register
 1 |  1 - Phase Table Load Register

Config Register 0 Bits 13-0
 SYR = 1 - This sets the use of synchronous rectification and improves power dissipation
 MS1 = 0 - Stepping Mode Selector 1
 MS0 = 0 - Stepping Mode Selector 0
 MXI1 = 1 - Phase Current Percentage 1
 MXI0 = 1 - Phase Current Percentage 0
 PFD2 = 1 - Mixed Decay Fast Decay Time 2
 PFD1 = 0 - Mixed Decay Fast Decay Time 1
 PFD0 = 0 - Mixed Decay Fast Decay Time 0
 TBK1 = 0 - Blank Time 1
 TBK0 = 1 - Blank Time 0
 TOF2 = 0 - Off Time 2 (Fixed Off Time) - FRQ2 (Fixed Frequency Mode)
 TOF1 = 0 - Off Time 1 (Fixed Off Time) - FRQ1 (Fixed Frequency Mode)
 TOF0 = 0 - Off Time 0 (Fixed Off Time) - FRQ0 (Fixed Frequency Mode)
 PWM = 0 - PWM Mode (0 = Fixed Off Time)

Config Register 1 Bits 13-0
  OSC = 0 - Set Oscillator Internal(0) or External(1)
  TSC1 = 1 - Overcurrent Fault Delay Time
  TSC0 = 0
  Bits 10-6 are not used
  CD3 = 1 - Count Difference for Stall Detection
  CD2 = 0
  CD1 = 0
  CD0 = 0
  DIAG1 = 0 - Select DIAG Output Function
  DIAG0 = 0

Run Register Bits 13-0
  EN = 0 - Software Output Disable (Hardware Enable must be low)
  OL1 = 0 - Open Load Current Threshold
  OL0 = 1
  HLR = 0 - High or Low side Recirculation for Slow Decay and Brake
  SLEW = 1 - Slew Rate Control Enable
  BRK = 0 - Brake Enable
  DCY1 = 1 - Decay Mode
  DCY0 = 0
  SC5 = 0 - Step Change Number (2's Complement)
  SC4 = 0
  SC3 = 0
  SC2 = 0
  SC1 = 0
  SC0 = 0

Read Operations use a 16-bit Word
Table Load Register Bits 15-0
  Bits 15 & 14 are always high
  Bits 13 - 7 are always low
  PTP - Parity Bit
  Bits 5 - 0 are Step Angle Value (Can be 0-63)

Fault Register 0 Bits 15-0 Register set to all 1's at power up but set to all 0's on each successful serial read
  FF - Fault Flag
  TW1 - Temp Diagnostic
  TW0
  Bit 12 Not Used
  UV - Under Voltage
  ST - Stall Detected
  OLB - Open Load detected on coil B
  OLA - Open Load detected on coil A
  BML - Overcurrent detected on BM Low Side
  BMH - Overcurrent detected on BM High Side
  BPL - Overcurrent detected on BP Low Side
  BPH - Overcurrent detected on BP High Side
  AML - Overcurrent detected on AM Low Side
  AMH - Overcurrent detected on AM High Side
  APL - Overcurrent detected on AP Low Side
  APH - Overcurrent detected on AP High Side

Fault Register 1 Bits 15-0
  FF - Fault Flag
  TW1 - Temp Diagnostic
  TW0
  Bit 12 Not Used
  UV - Under Voltage
  ST - Stall Detected
  OLB - Open Load detected on coil B
  OLA - Open Load detected on coil A
  Bits 7 & 6 Not Used
  SA5 - Current Step Angle Number
  SA4
  SA3
  SA2
  SA1
  SA0

*/
