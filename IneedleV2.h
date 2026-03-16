#include <TimerOne.h>

#define EncoderCH1    2
#define EncoderCH2    3

#define M1    5
#define M2    6

#define SPD0		7
#define SPD1		8
#define SPD2		9
#define SPD3		10

#define RLED    13
#define GLED    12
#define BLED    11

#define FSEN		A2
#define HOME    A3

#define PRIOD_US	50000

#define ValuePerGram    2.56
#define ReductionRatio  29
#define PulsePerTurn    ReductionRatio*12
#define PitchPerTurn    0.7
#define PITCH           60.0

#define TargetPosition 30.0
#define Difference 55.0

union DataConv {
  float  flt;
  byte  byt[4];
} tmpDataUnion;
