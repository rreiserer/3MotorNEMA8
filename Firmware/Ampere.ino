/*
    Notes from DRIP Firmware
    GUI input comes in 16 byte packets with syntax:
      [1: delimiter],[2: command-id],[3: controller-id],[4: device (pump/valve)-id],[5-6: command],[7-10: startTime][11-14: duration],[15: checksum],[16: newline]

Includes from DRIP (maybe just parts)
  Config.h
  SharedEnum.h
  Structures.h
  SerialBuffer.h

Includes from Arduino
  Streaming.h
  Wire.h
  twi.j ??


*/

// Programming from DRIP
#define SERIAL_BUFFER_SIZE 128
#define PACKET_SIZE 16

typedef struct command_t
{

    uint8_t commandType;//1//CommandType
    uint8_t targetControllerID;//2
    uint8_t targetDeviceID;//3
    int16_t value;//4 and 5
    int32_t startTime;//6,7,8,9
    int32_t duration;//10,11,12,13

    command_t(
    CommandType t = Help_T,
    uint8_t c = 0,
    uint8_t d = 0,
    int16_t v = 0,
    int32_t ts = 0,
    int32_t td = 0
    ):
        commandType(t),
        targetControllerID(c),
        targetDeviceID(d),
        value(v),
        startTime(ts),
        duration(td)
    {}
}Command;

typedef struct commandPacket_t
{
  //int8_t data[SERIAL_BUFFER_SIZE];
  char data[SERIAL_BUFFER_SIZE];
}CommandPacket;

typedef struct feedback_t
{
  uint8_t feedbackType;//1 // FeedbackType
  uint8_t controllerID;//2
  uint8_t deviceID;//3
  int16_t value;//4 and 5
  int32_t t1;//6 7 8 9
  int32_t t2;//10 11 12 13
  uint8_t cq;//14

  feedback_t(
  FeedbackType s = CurrentPosition_T,
  uint8_t c = 0,
  uint8_t d = 0,
  int16_t v = 0,
  int32_t e1 = 0,
  int32_t e2 = 0,
  uint8_t q = 0):
        feedbackType(s),
        controllerID(c),
        deviceID(d),
        value(v),
        t1(e1),
        t2(e2),
        cq(q){}
}Feedback;

typedef struct feedbackPacket_t
{
  int8_t data[PACKET_SIZE];//using uint8_t b/c guaranteed 8-bit
}FeedbackPacket;

typedef struct calibrationPoint_t
{
    int16_t rpm; //RPM*100 Everything in the RPM register is multiplied by 100 for fixed-point division. Resolution: 0.01 RPM
    int16_t sps; //Steps per second
    int32_t qv; //uL/min*10 Everything in qv register is multiplied by 10 for fixed-point division. Resolution: 0.1uL/min

    calibrationPoint_t(int16_t r=0, int16_t s=0, int32_t q=0):
    rpm(r),
    sps(s),
    qv(q){}

}CalibrationPoint;
