///////////////TTR Pin Assign///////////////////
const int irSensorPin1 = A2; // right most
const int irSensorPin2 = A3; // right
const int irSensorPin3 = A4; // center
const int irSensorPin5 = A5; // left most
const int irSensorPin4 = A6; // left 
const int threshold = 950; // Adjust this threshold based on your sensor and environment, My TTR gave 90 and 990 so i set it at 950 
//////////////////Ultrasound Sensor////////////////////////
const int trigPin = 3; //  TRIGGER pin of the sensor to digital pin 2
const int echoPin = A1; //  ECHO pin of the sensor to digital pin 3
//////////////////Motor Driver pin Assign//////////////////////////
const int in1 = 5;     // right motor forward
const int in2 = 6;     // right motor backward
const int in3 = 12;     // left motor forward
const int in4 = 13;     // left motor backward
////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(irSensorPin1, INPUT);
    pinMode(irSensorPin2, INPUT);
    pinMode(irSensorPin3, INPUT);
    pinMode(irSensorPin4, INPUT);
    pinMode(irSensorPin5, INPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);

}

void loop() {
  int sensorValue1 = analogRead(irSensorPin1);
  int sensorValue2 = analogRead(irSensorPin2);
  int sensorValue3 = analogRead(irSensorPin3);
  int sensorValue4 = analogRead(irSensorPin4);
  int sensorValue5 = analogRead(irSensorPin5);
  // Make a binary decision of 0 or 1 based on the threshold
  int binaryValue1 = (sensorValue1 > threshold) ? 1 : 0;
  int binaryValue2 = (sensorValue2 > threshold) ? 1 : 0;
  int binaryValue3 = (sensorValue3 > threshold) ? 1 : 0;
  int binaryValue4 = (sensorValue4 > threshold) ? 1 : 0;
  int binaryValue5 = (sensorValue5 > threshold) ? 1 : 0;
  ////////////////Ultrasound Sensor Value ///////////////////////
  unsigned long duration;
  float distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, 0);
  duration = pulseIn (echoPin, HIGH);
  distance = (duration / 2.0) / 29.0;
  Serial.print(distance);
  Serial.println(" cm");
  ////////////////////////Working Conditions/////////////////////////
   if(distance <= 10) /////////////Obstacle, turn back
  {
      TurnBack();
      Serial.println("Turn Back");
  }
else //////////Normal, now line following 
{
  if (binaryValue1 == 0 && binaryValue2 == 1 && binaryValue3 == 1 && binaryValue4 == 1 &&  binaryValue5 == 0 ) ///////////////center3
  {
      forward();
      Serial.println("Forward");
  }
  if (binaryValue1 == 1 && binaryValue2 == 1 && binaryValue3 == 1 && binaryValue4 == 1  &&  binaryValue5 == 1 ) ///////////////all
  {
      stop();
      Serial.println("Stop");
  }
  if (binaryValue1 == 0 && binaryValue2 == 0 && binaryValue3 == 0 && binaryValue4 == 0  &&  binaryValue5 == 0 ) ///////////////nothing
  {
      stop();
      Serial.println("stop");
  }
 if (binaryValue1 == 0 && binaryValue2 == 0 && binaryValue3 == 1 && binaryValue4 == 0  &&  binaryValue5 == 0 ) //////////////////////center
  {
      forward();
      Serial.println("forward");
  }
  if (binaryValue1 == 0 && binaryValue2 == 0 && binaryValue3 == 0 && binaryValue4 == 0  &&  binaryValue5 == 1 ) ///////////////////////////////left most
  {
      right();
      Serial.println("Right");
  }
  if (binaryValue1 == 0 && binaryValue2 == 0 && binaryValue3 == 0 && binaryValue4 == 1  &&  binaryValue5 == 0 ) ///////////////////////////////left 
  {
      right();
      Serial.println("right");
  }
   if (binaryValue1 == 0 && binaryValue2 == 0 && binaryValue3 == 0 && binaryValue4 == 1  &&  binaryValue5 == 1 ) ///////////////////////// both left
  {
      right();
      Serial.println("RIGHT");
  }
 if  (binaryValue1 == 1 && binaryValue2 == 0 && binaryValue3 == 0 && binaryValue4 == 0  &&  binaryValue5 == 0 ) ///////////////////////////////////right most
  {
      left();
      Serial.println("Left");
  }
 if  (binaryValue1 == 0 && binaryValue2 == 1 && binaryValue3 == 0 && binaryValue4 == 0  &&  binaryValue5 == 0 ) ///////////////////////////////////right most
  {
      left();
      Serial.println("left");
  }
 if (binaryValue1 == 1 && binaryValue2 == 1 && binaryValue3 == 0 && binaryValue4 == 0  &&  binaryValue5 == 0 ) //////////////////// both right
  {
      left();
      Serial.println("LEFT");
  }
Serial.println(binaryValue1);
Serial.println(binaryValue2);
Serial.println(binaryValue3);
Serial.println(binaryValue4);
Serial.println(binaryValue5);
Serial.println("ha_alif");
delay(100);
}
//////////////////////////////////////////////////////////
}
void forward()
{
     analogWrite(in1, 128); // PWM value, range 0-255
     analogWrite(in2, 0);
     analogWrite(in3, 128); // PWM value, range 0-255
     analogWrite(in4, 0);
}
void stop()
{
     analogWrite(in1, 0); // PWM value, range 0-255
     analogWrite(in2, 0);
     analogWrite(in3, 0); // PWM value, range 0-255
     analogWrite(in4, 0);
}
void left()
{
     analogWrite(in1, 255); // PWM value, range 0-255
     analogWrite(in2, 0);
     analogWrite(in3, 0); // PWM value, range 0-255
     analogWrite(in4, 255);
}
void right()
{
     analogWrite(in1, 0); // PWM value, range 0-255
     analogWrite(in2, 255);
     analogWrite(in3, 255); // PWM value, range 0-255
     analogWrite(in4, 0);
}
void TurnBack ()
{
     analogWrite(in1, 255); // PWM value, range 0-255
     analogWrite(in2, 0);
     analogWrite(in3, 0); // PWM value, range 0-255
     analogWrite(in4, 255);
     delay(150);
     analogWrite(in1, 128); // PWM value, range 0-255
     analogWrite(in2, 0);
     analogWrite(in3, 128); // PWM value, range 0-255
     analogWrite(in4, 0);
}