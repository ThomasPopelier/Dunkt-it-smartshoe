#include <SoftwareSerial.h>
#include "Arduino.h"

//toewijzen RX en TX van Bluetoothmodule 
SoftwareSerial mySerial(0, 1); // RX, TX


//toewijzen LED's 
int led1 = 12;   
int led2 = 11;
int led3 = 10;
int led4 = 9;
int led5 = 8;
int el = 5;

//ontvangen signaal = teller. 
int teller = 0;


//opzetten timer1 (verzenden data)
unsigned long timeOfLastLedEvent = 0;
int interval= 250; // interval in ms





//nodig voor bluetooth
char chByte = 0;  // incoming serial byte
String strInput = "";    // buffer for incoming packet
String strCompare = "y";

// MPU-6050 Short Example Sketch
// By Arduino User JohnChi
// August 17, 2014
// Public Domain
#include<Wire.h>
const int MPU=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ; // uitlezen waarden gyroscoop & accelerometer



void setup() {
  
 
  
 // declare pin 9 to be an output:
 pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
   pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
     pinMode(led5, OUTPUT);
       pinMode(el,OUTPUT);

 // Wire library voor  waarden gyroscoop & accelerometer
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

 // initialize serial: (serial voor verzenden en ontvangen.)
 mySerial.begin(9600);
 
  Serial.begin(9600);
}





// the loop routine runs over and over again forever:
void loop() {

 while (mySerial.available() > 0)
 {
   
   
  unsigned long currentMillis = millis(); //currentMillis == tijd
 
  
  // get incoming byte:
  chByte = mySerial.read();
  
  if (chByte == 'y' && currentMillis - timeOfLastLedEvent > interval)
  {
  teller ++;
  
  timeOfLastLedEvent = currentMillis;
  
   //Serial.print(" Bluetoothchizzle ");
  
    
   }
 if (chByte== 'n' && currentMillis - timeOfLastLedEvent > interval){
  teller--;
 timeOfLastLedEvent = currentMillis;
 }
 

  

  
   mySerial.println(chByte); // controle ontvangen signaal bluetooth
  
   
 }

 if (teller == 0){
   
   digitalWrite(led1,LOW);
   digitalWrite(led2,LOW);
   digitalWrite(led3,LOW);
   digitalWrite(led4,LOW);
   digitalWrite(led5,LOW);
   digitalWrite(el,LOW);
 }
   
  if (teller == 1){
   leds(1);
   digitalWrite(el,HIGH);
 }
 if (teller == 2){
  leds(2);
  digitalWrite(el,LOW);
 }
 if (teller == 3){
   leds(3);
   digitalWrite(el,HIGH);
 }
 if (teller == 4){
   leds(4);
   digitalWrite(el,LOW);
 }
 
  if (teller == 5){
   leds(5);
   digitalWrite(el,HIGH);
 }
 if (teller == 6){
   leds(6);
   digitalWrite(el,LOW);
 }
  if (teller == 7){
   leds(7);
 }
 if (teller == 8){
   leds(8);
 }
 
 if (teller == 9){
   leds(9);
 }
senddata ();
}


/**********************************************************
***********************************************************
                      Stop hoofdprogramma
***********************************************************
***********************************************************/


/**********************************************************
                      Programma LEDS
***********************************************************/



//opzetten timer2 (Rollen LED's)
  long interval1  = 500;

  
  int ledState =LOW;

unsigned long timeOfLastLedEvent2 = 0;
long previousMillis = 0;  

void leds(int a){
 
  
  unsigned long currentMillis1 = millis();
 
  if(currentMillis1 - previousMillis > interval1/a) {

    digitalWrite(led1,HIGH);
   digitalWrite(led2,LOW);
   digitalWrite(led3,LOW);
   digitalWrite(led4,LOW);
   digitalWrite(led5,LOW);
    
  }
  if(currentMillis1 - previousMillis > 2*(interval1/a)) {

    digitalWrite(led1,LOW);
   digitalWrite(led2,HIGH);
   digitalWrite(led3,LOW);
   digitalWrite(led4,LOW);
   digitalWrite(led5,LOW);
    
  }
  if(currentMillis1 - previousMillis > 3*(interval1/a)) {
 
    digitalWrite(led1,LOW);
   digitalWrite(led2,LOW);
   digitalWrite(led3,HIGH);
   digitalWrite(led4,LOW);
   digitalWrite(led5,LOW);
   
  }
  if(currentMillis1 - previousMillis > 4*(interval1/a)) {
   
   digitalWrite(led1,LOW);
   digitalWrite(led2,LOW);
   digitalWrite(led3,LOW);
   digitalWrite(led4,HIGH);
   digitalWrite(led5,LOW);
 
  }
  if(currentMillis1 - previousMillis > 5*(interval1/a)) {

  digitalWrite(led1,LOW);
   digitalWrite(led2,LOW);
   digitalWrite(led3,LOW);
   digitalWrite(led4,LOW);
   digitalWrite(led5,HIGH);

   previousMillis = currentMillis1;   

  }
  
}

/**********************************************************
                Programma Gyro & accelerometer
***********************************************************/

long intervalSend=3000;

unsigned long timeOfLastSend = 0;
long previousMillisSend = 0;  

int  vorigewaardeGyro =0;
int  vorigewaardeAcc = 0;


void senddata (){
  
unsigned long currentMillisSend = millis();  
  
  if(currentMillisSend - previousMillisSend > intervalSend) {
 //uitlezen signalen accelerometer & gyroscoop    
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
 // Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  
  //uitzetten waarde gyroscoop 
 int metingGyro  = (abs(GyX)+abs(GyY)+abs(GyY))/3 - 1400;
 int metingAcc   = (abs(AcX)+abs(AcY)+abs(AcY))/3 - 300;
   
 int  waardeGyro = metingGyro - vorigewaardeGyro;
 int  waardeAcc   =metingAcc - vorigewaardeAcc;  

 if (abs(waardeGyro) >5000){
  Serial.print ("G");
 }
 if (abs(waardeAcc) > 5000){
 Serial.print ("A"); 
 }
 
 
 metingGyro = vorigewaardeGyro;
 metingAcc = vorigewaardeAcc;
 
  previousMillisSend = currentMillisSend;
 
  }
  
  
 
}
