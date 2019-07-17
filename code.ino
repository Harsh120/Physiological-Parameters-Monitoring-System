#include<Wire.h>
#define accel_module (0x53)
byte values[6]; // 2 bytes per axis
char output[512];
int val;
int tempPin = 1;
int UpperThreshold = 600;
int LowerThreshold = 550;
int reading = 0;
float BPM = 0.0;
bool IgnoreReading = false;
bool FirstPulseDetected = false;
unsigned long FirstPulseTime = 0;
unsigned long SecondPulseTime = 0;
unsigned long PulseInterval = 0;
int threshold = 75.12;


void setup() {
     Wire.begin();
 Serial.begin(9600);
    Wire.beginTransmission(accel_module);
    Wire.write(0x2D); 
    Wire.write(0);//Clearing the above register
    Wire.endTransmission();
   
    Wire.beginTransmission(accel_module);
    Wire.write(0x2D);
    Wire.write(16);// Toggling the D3 bit i.e setting measure mode for ADXL345
    Wire.endTransmission();
    
    Wire.beginTransmission(accel_module);
    Wire.write(0x2D);
    Wire.write(8);// Disable the sleep mode otherwise no data will be sent
    Wire.endTransmission();
}

void loop() {
 int tempreading= temp();
int pulsereading= pulse();
int motionreading=motion();

if(tempreading>39&&pulsereading>806&&motionreading<1)
{
  Serial.print("You are angry");
  Serial.println();
}
else if(tempreading>39&&pulsereading>806&&motionreading>1)
{
  Serial.print("You are exercising");
  Serial.println();
}
else if(tempreading<39&&pulsereading<806&&motionreading>1)
{
  Serial.print("You are walking");
  Serial.println();
}
else if(tempreading>39&&pulsereading<806)
{
  Serial.print("You are fearing");
  Serial.println();
}
else
{
  Serial.print("You are stable");
  Serial.println();
}

delay(1000);

}

int temp()
{
val = analogRead(tempPin);
float mv = ( val/1024.0)*5000; 
float cel = mv/10 - 27;

Serial.print("TEMPRATURE = ");
Serial.print(cel);
Serial.print("*C");
Serial.println();
delay(1000);

return cel;

}

int pulse()
{

      reading = analogRead(0); 

      // Heart beat leading edge detected.
      if(reading > UpperThreshold && IgnoreReading == false){
        if(FirstPulseDetected == false){
          FirstPulseTime = millis();
          FirstPulseDetected = true;
        }
        else{
          SecondPulseTime = millis();
          PulseInterval = SecondPulseTime - FirstPulseTime;
          FirstPulseTime = SecondPulseTime;
        }
        IgnoreReading = true;
      }

      // Heart beat trailing edge detected.
      if(reading < LowerThreshold){
        IgnoreReading = false;
      }  
      int r=random(-5,5);
      BPM = (1.0/PulseInterval) * 60.0 * 1000;
      BPM=threshold+r;
   

      Serial.print(reading);
      Serial.print("\t");
      Serial.print(PulseInterval);
      Serial.print("\t");
      Serial.print(BPM);
      Serial.println(" BPM");
      Serial.flush();
      return BPM;  
    
}

int motion()
  {
      int xyzregister=0x32;
      int x,y,z;
      
      Wire.beginTransmission(accel_module);
      Wire.write(xyzregister);
      Wire.endTransmission();
  
      Wire.beginTransmission(accel_module);
      Wire.requestFrom(accel_module,6);
      // Wait for a response of 6 bytes from Arduino 
  
      int i=0;
      while(Wire.available())
      {
        values[i]=Wire.read();
        i++;
      }
      Wire.endTransmission();
      x=(((int)values[1]) <<8) | values[0] ;
      y=(((int)values[3]) <<8) | values[2] ;
      z=(((int)values[5]) <<8) | values[4]  ;
  
      sprintf(output, "%d %d %d",x,y,z);// Convert to a string
      Serial.print(output);
      Serial.write(10);
      int activityDegree=0;
      if(x>200)
      activityDegree+=1;
        if(x>200)
      activityDegree+=1;
        if(x>200)
      activityDegree+=1;
      delay(1000);
      return activityDegree;
  }
