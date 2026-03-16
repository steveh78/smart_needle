#include "IneedleV2.h"

byte mode = 0;
int motorDir=0;

byte SysStatus=0;
long SysCnt=0;

boolean InputFin = false;
boolean CalcFin = false;

int ADCvalue;
long ADCcnt = 0;
int offset = 212;
float ReactionForce = 0.0;

int EncoderPos = 0;
const float PitchPerPulse = 0.7/348.0;
float CurrentPosition = 0.0;

float TimeTick = 0.0;
float Command = 0.0;

byte txDataBuf[18]={0};

void setup() {
	Serial.begin(115200);

	noInterrupts();
  pinMode(M1,OUTPUT);
  pinMode(M2,OUTPUT);
  pinMode(EncoderCH1, INPUT_PULLUP);
  pinMode(EncoderCH2, INPUT_PULLUP);
//pinMode( SPD0,	INPUT_PULLUP);
	pinMode( SPD1,	INPUT_PULLUP);
	pinMode( SPD2,	INPUT_PULLUP);
	pinMode( SPD3,	INPUT_PULLUP);
	pinMode( RLED,	OUTPUT);
	pinMode( GLED,	OUTPUT);
	pinMode( BLED,	OUTPUT);
  pinMode( FSEN,  INPUT); 
  pinMode( HOME,  INPUT); 

	Timer1.initialize(PRIOD_US);
	Timer1.attachInterrupt(svcADC);
	Timer1.start();

	attachInterrupt(0, doEncoderA, CHANGE);
	attachInterrupt(1, doEncoderB, CHANGE);

	interrupts();

  mode = 3;
  //turn_off();
	//motorDir=0;
	SysStatus = 0;
}

void loop() {
  svcStatus();
  calc();
  svcSafety();
  targetcheck();
	test();
  //sendData();
	SysCnt++;
}
