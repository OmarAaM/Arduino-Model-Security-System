#include <Servo.h>
#include <LedControl.h>
int sservoPin = 10;
int mservoPin = 11;
int DIN = 8;
int CLK = 12;
int CS = 9;
int position = 25;
int trigPin = 7;
int echoPin = 6;
int speedPin = 3;
int dirPin1 = 2;
int dirPin2 = 4;
int mspeed = 200;
int pingTime;
float inches;
int rotationStat = 0;
float distance;
float distance1;
Servo sservo;
Servo mservo;

float getDistance() {
  float readings[7];
  for (int i = 0; i < 7; i++) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(10);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    pingTime = pulseIn(echoPin, HIGH, 30000);
    readings[i] = (343.0 / 25400.0) * (pingTime / 2.0);

    delay(60); 
  }
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      if (readings[j] > readings[j+1]) {
        float temp = readings[j];
        readings[j] = readings[j+1];
        readings[j+1] = temp;
      }
    }
  }
  distance = readings[3];
  Serial.println(distance);
  return distance; 
  }
byte lefty[8] =
{
  B00000000,
  B00000000,
  B00000000,
  B10000000,
  B11000000,
  B01100000,
  B00110000,
  B00011000
};
byte lefty1[8] =
{
  B00000000,
  B10000000,
  B11000000,
  B01100000,
  B00110000,
  B00011000,
  B00000000,
  B00000000
};
byte lefty2[8] =
{
  B01100000,
  B00110000,
  B00011000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};
byte middy[8] =
{
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000
};
byte righty2[8] =
{
  B00000110,
  B00001100,
  B00011000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};
byte righty1[8] =
{
  B00000000,
  B00000001,
  B00000011,
  B00000110,
  B00001100,
  B00011000,
  B00000000,
  B00000000
};
byte righty[8] =
{
  B00000000,
  B00000000,
  B00000000,
  B00000001,
  B00000011,
  B00000110,
  B00001100,
  B00011000
};
LedControl lc = LedControl(DIN, CLK, CS, 1);
void setup() {
  // put your setup code here, to run once:
sservo.attach(sservoPin);
mservo.attach(mservoPin);
Serial.begin(9600);
lc.shutdown(0, false);
lc.setIntensity(0, 12);
lc.clearDisplay(0);
pinMode(trigPin,OUTPUT);
pinMode(echoPin, INPUT);
pinMode(speedPin,OUTPUT);
pinMode(dirPin1,OUTPUT);
pinMode(dirPin2,OUTPUT);
digitalWrite(dirPin1,HIGH);
digitalWrite(dirPin2,LOW);
sservo.write(position);
mservo.write(position);
delay(200);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);

  if(position == 145){
    rotationStat = 1;
  }
  else if (position == 25){
    rotationStat = 0;
  }
  if(rotationStat == 0){
    position = position + 5;
  }
  else if (rotationStat == 1){
    position = position - 5;
  }
  if(position >= 85){
    sservo.write(position);
  mservo.write(position + 10);
  }
  else{
    sservo.write(position);
  mservo.write(position + 5);
  }
  distance1 = getDistance();
  while(distance1 <= 12 && distance1 > 0){
    analogWrite(speedPin,mspeed);
    if(position <= 45){
      lc.clearDisplay(0);
for (int row = 0; row < 8; row++)
  {
    lc.setRow(0, row, lefty[row]);
  }
    }
  else if(position <=65){
    lc.clearDisplay(0);
for (int row = 0; row < 8; row++)
  {
    lc.setRow(0, row, lefty1[row]);
  }
  }
  else if(position <= 79){
    lc.clearDisplay(0);
for (int row = 0; row < 8; row++)
  {
    lc.setRow(0, row, lefty2[row]);
  }
  }
  else if (position <= 90){
    lc.clearDisplay(0);
for (int row = 0; row < 8; row++)
  {
    lc.setRow(0, row, middy[row]);
  }
  }
  else if(position <= 105){
    lc.clearDisplay(0);
for (int row = 0; row < 8; row++)
  {
    lc.setRow(0, row, righty2[row]);
  }
  }
  else if (position <= 125){
    lc.clearDisplay(0);
for (int row = 0; row < 8; row++)
  {
    lc.setRow(0, row, righty1[row]);
  }
  }
  else if (position <= 145){
    lc.clearDisplay(0);
for (int row = 0; row < 8; row++)
  {
    lc.setRow(0, row, righty[row]);
  }
  }
  distance1 = getDistance();
  }
lc.clearDisplay(0);
analogWrite(speedPin,0);





  
}
