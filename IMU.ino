#include "MPU6050_6Axis_MotionApps20.h"
#include <Wire.h>
#define INTERRUPT_PIN 2

MPU6050 mpu;

bool dmpReady = false;  
uint8_t mpuIntStatus;   
uint8_t devStatus;      
uint8_t fifoBuffer[64]; 
volatile bool mpuInterrupt = false;

VectorFloat gravity;
Quaternion q;
float ypr[3]; 

void setup() {
  Wire.begin();
  Wire.setClock(400000);
  Serial.begin(115200);
  mpu.initialize();
  mpu.testConnection();
  devStatus = mpu.dmpInitialize();
  mpu.setZGyroOffset(-85);
  
  if (devStatus == 0) {
        mpu.CalibrateGyro(6);
        mpu.setDMPEnabled(true);
        attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();
        dmpReady = true;
  }
}

void loop() {
   if (dmpReady){
    if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)){     
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetGravity(&gravity, &q);
      mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
      Serial.print(ypr[0] * 180/M_PI);
      }
   }
}

void dmpDataReady() {
mpuInterrupt = true;
}
