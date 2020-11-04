#include <Timer.h>
#define EncoderPin_A PB0
#define EncoderPin_B PB1
volatile long int EncoderOutput=0;
int velocity=0;
int ppr=600; //assumed value for pulse per rotation 

Timer EncTimer;
void setup() {
  pinMode(EncoderPin_A,INPUT_PULLUP);
  pinMode(EncoderPin_B,INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(EncoderPin_A, readEncoder, RISING);      //when a new pulse is received
  EncTimer.every(1000,calculateVelocity);     //calculate speed every 1 sec

}

void loop() {
  Serial.print(velocity);
  EncTimer.update();

}
void readEncoder(){  //increment number of pulses
  if(digitalRead(EncoderPin_A)==digitalRead(EncoderPin_B)){    //encoder is rotating CW (velocity is positive)
  EncoderOutput++;}
  else {
  EncoderOutput--; }      //encoder is rotating CCW (velocity is negative)
}
void calculateVelocity(){
  velocity=(EncoderOutput*60/ppr);   //RPM
  EncoderOutput=0;        //reset number of pulses
}
