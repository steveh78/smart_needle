byte getswStatus()
{
  if(digitalRead(SPD1)==LOW)
  { return 1; }
  else if(digitalRead(SPD2)==LOW)
  { return 2; }
  else if(digitalRead(SPD3)==LOW)
  { return 3; }
  else
  { return 0; }
}

void doEncoderA(){
  EncoderPos += (digitalRead(EncoderCH1)==digitalRead(EncoderCH2))?-1:1;
}

void doEncoderB(){
  EncoderPos += (digitalRead(EncoderCH1)==digitalRead(EncoderCH2))?1:-1;
}

void Motor_R(){
  digitalWrite(M1, HIGH);
  digitalWrite(M2, LOW);
  motorDir=-1;
}

void Motor_F(){
  digitalWrite(M1, LOW);
  digitalWrite(M2, HIGH);
  motorDir=1;
}

void Motor_S(){
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  motorDir=0;
}

void turn_off(){
  digitalWrite(BLED, HIGH);
  digitalWrite(GLED, HIGH);
  digitalWrite(RLED, HIGH);
}

void turn_on(int LED){
  if(LED==11){
    digitalWrite(BLED, LOW);
    digitalWrite(GLED, HIGH);
    digitalWrite(RLED, HIGH);
  }
  else if(LED==12){
    digitalWrite(BLED, HIGH);
    digitalWrite(GLED, LOW);
    digitalWrite(RLED, HIGH);
  }
  else if(LED==13){
    digitalWrite(BLED, HIGH);
    digitalWrite(GLED, HIGH);
    digitalWrite(RLED, LOW);
  }
  else {
    turn_off();
  }
}

void blink_(int LED){
  static bool toggle = 0;
  if(SysCnt%10000==0)
  {
    toggle ^= 1;
  }
  if(LED==11){
    digitalWrite(BLED, toggle);
    digitalWrite(GLED, HIGH);
    digitalWrite(RLED, HIGH);
  }
  else if(LED==12){
    digitalWrite(BLED, HIGH);
    digitalWrite(GLED, toggle);
    digitalWrite(RLED, HIGH);
  }
  else if(LED==13){
    digitalWrite(BLED, HIGH);
    digitalWrite(GLED, HIGH);
    digitalWrite(RLED, toggle);
  }
  else {
    turn_off();
  }
}
