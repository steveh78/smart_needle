void svcADC()
{
  static int sum = 0;
  
  ADCvalue = analogRead(FSEN);
  
  if(ADCcnt>=0 && ADCcnt<100)
  {
    sum += ADCvalue;
    //turn_on(RLED);
  }
  else if(ADCcnt==100)
  {
    offset = sum/100;
    sum = 0;
  }
  ADCcnt++;
  InputFin = true;
}

void svcStatus()
{
  byte swStatus = getswStatus();
  if (mode != swStatus && swStatus != 0)
  { 
    mode = swStatus;
  }
  switch(mode)
  {
    case 1:
      Motor_F();
      blink_(BLED);
      Command = 0.0;
      break;
    case 2:
      Motor_S();
      turn_off();
      Command = 0.0;
      break;
    case 3:
      Motor_R();
      blink_(BLED);
      Command = 0.0;
      break;
    case 4:
      Motor_S();
      turn_on(GLED);
      Command = 100.0;
      break;
    default:
      Motor_S();
      turn_off();
      break;
  }
}

void svcSafety()
{
  if ((digitalRead(HOME)==HIGH) && (motorDir == -1))
  {
    mode = 0;
    Command = 0.0;
    EncoderPos = 0;
    ADCcnt = 0;
  }
  else if((CurrentPosition > PITCH) && (motorDir == 1)) 
  {
    mode = 0;
    Command = 200.0;
  }
  /*
  else if(Command == 100.0)
  {
    if(mode == 1)
    {
      error();
    }
  }
  */
}

void error()
{
  Motor_S();
  blink_(RLED);
}

void calc()
{
  if(InputFin==true)
  {
    ReactionForce = (float)(ADCvalue-offset)*ValuePerGram;
    CurrentPosition = (float)(EncoderPos)*PitchPerPulse;
    TimeTick = (float)(ADCcnt)*0.02;
    InputFin = false;
    CalcFin = true;
  }
}

void targetcheck()
{
  float newForce = ReactionForce;
  static float oldForce = 0;
  //static byte CheckCnt = 0;

  if((motorDir == 1) && (CurrentPosition > TargetPosition))
  {
    if(oldForce == 0)
    {
      oldForce = ReactionForce;
    }
    else
    {
      if((oldForce - newForce) > Difference)
      {
        //CheckCnt++;
        mode = 4;
        oldForce = 0;
      }
      else
      {
        oldForce = newForce;
      }
    } 
  }
}

void test()
{
  if(CalcFin==true)
  {
    
    //Serial.print(mode);
    //Serial.print("\t");
    
    Serial.print(ReactionForce);
    Serial.print(" ");
    Serial.print(CurrentPosition);
    Serial.print(" ");
    Serial.print(TimeTick);
    Serial.print(" ");
    Serial.println(Command);
    
    //Serial.println(EncoderPos);
    
    //Serial.print(ReactionForce);
    //Serial.print(" ");
    //Serial.println(CurrentPosition);
    CalcFin=false;
  }
}

void sendData()
{
  if(CalcFin==true)
  {
    txDataBuf[0] = 0x0D;
    txDataBuf[1] = 0x0A;
    memcpy(&(txDataBuf[2]), &ReactionForce, 4);
    memcpy(&(txDataBuf[6]), &CurrentPosition, 4);
    memcpy(&(txDataBuf[10]), &TimeTick, 4);
    memcpy(&(txDataBuf[14]), &Command, 4);
    Serial.write(txDataBuf, 18);
    CalcFin=false;
  }
}
