#include <MPU6050.h>
#include <Wire.h>

MPU6050 yawIMU;
int16_t yaw;

void setup() {
  
  Serial.begin(9600);
  yawIMU.initialize();
  Serial.println(yawIMU.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

}

void loop() {
  yaw = yawIMU.getRotationZ();
  Serial.print(yaw);
}
