#include <SD.h>

const int xpin = A3;                  // x-axis of the accelerometer
const int ypin = A2;                  // y-axis
const int zpin = A1;                  // z-axis (only on 3-axis models)

//these pins can not be changed 2/3 are special pins
int encoderPin1 = 2; // GREEN
int encoderPin2 = 3; // WHITE

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;
float StartTime = 0;
int lastMSB = 0;
int lastLSB = 0;
volatile long ElapsedTime = 0;

int id = 1;
float X,Y,Z,Ypast = 0;


void setup() {
  // initialize the serial communications:
  Serial.begin(9600);
  pinMode(xpin, INPUT);
  pinMode(ypin, INPUT);
  pinMode(zpin, INPUT);
  pinMode(encoderPin1, INPUT);
  pinMode(encoderPin2, INPUT);

  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on

  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3)
  unsigned long StartTime = micros();


  attachInterrupt(0, updateEncoder, CHANGE);
  attachInterrupt(1, updateEncoder, CHANGE);
  // SD card setup

  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  else {
    Serial.println("initialization done.");
  }


  File sensorData = SD.open("test4.csv", FILE_WRITE);
  if (sensorData)
  {
    sensorData.println(", , , , ,");
    String header = "ID, X, Y, Z, Dist";
    sensorData.println(header);
    sensorData.close();
    Serial.println(header);
  }
  else {
    Serial.println("Error opening to file !");
  }
}

void loop() {

  Serial.print(id);
  Serial.print("\t");


  // print the sensor values:
   X = (analogRead(xpin) - 330) * 9.8 / 60;
    Serial.print(X);
    Serial.print("\t");
  
  
   Y = (analogRead(ypin) - 330) * 9.8 / 60;
    Serial.print(Y);
    Serial.print("\t");
  
    Z = (analogRead(zpin) - 270) * 9.8 / 60;
    Serial.print(Z);
    Serial.print("\t");
  
  
  // delay before next reading:
  float Ydisp = encoderValue * 5.0 / 1440.0;
  Serial.print(Ydisp);
  Serial.print("\t");

//  float VelocityY = (Ydisp - Ypast) * 1000000.0 / ElapsedTime ;
//  Serial.print(VelocityY);
//  Serial.print("\t");

  String  dataString = String(id) + "," + String(X) + "," + String(Y) + "," + String(Z) + "," + String(Ydisp);
  //  Serial.print("\t");

  File sensorData = SD.open("test4.csv", FILE_WRITE);
  if (sensorData)
  { sensorData.println(dataString);
    Serial.println(dataString);
    sensorData.close(); // close the file
  }
  else {
    Serial.println("Error writing to file !");
  }

  id++;
  Ypast = Ydisp;
  delay(100);

}



void updateEncoder()
{
  unsigned long CurrentTime = micros();
  ElapsedTime = CurrentTime - StartTime;
  StartTime = CurrentTime;

  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit

  int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;
  //  Serial.println(ElapsedTime);
  lastEncoded = encoded; //store this value for next time
}

