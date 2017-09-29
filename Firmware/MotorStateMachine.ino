/*
Motor State Machine

Possible states of Machine are
      STATE_IDLE - No movement is taking place
      STATE_CCW - Motor will operate in Counter Clock-Wise direction
      STATE_CW - Motor will operate in Clock-Wise direction
      STATE_RUN - Motor is running in continuous mode
      STATE_STEP - Motor is taking a specific number of steps

*/

typedef enum { STATE_IDLE, STATE_CW, STATE_CCW, STATE_RUN, STATE_STEP } state;

state currentState = STATE_IDLE;

void setup() {
  /* code */
}
void motorRun(/* arguments */) {
  /* code */
}
void motorStep(/* arguments */) {
  /* code */
}
