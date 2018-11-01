

  // Raisbeck Aviation High School Intro to Aero P4. 
  // Magnetometer and Solar cell sensor module  
  
  // 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // http://www.magnetic-declination.com/

const int switchpin=9;
int switchstate=0;
#include <SPI.h>
#include <SD.h>
const int chipSelect = 4;

#define NUM_SAMPLES 10

int sum = 0;                    // sum of samples taken
unsigned char sample_count = 0; // current sample number
float voltage = 0.0;            // calculated voltage

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

void setup() {
   pinMode(switchpin, INPUT); 
   
  Serial.begin(9600);
  Serial.println("HMC5883 Magnetometer Test"); Serial.println("");
  Serial.print("Initializing SD card...");
  
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    //while (1);
  }
  Serial.println("card initialized.");


  if(!mag.begin())
  {
    Serial.println("Sensor not detected");
    //while(1);
  }
}


void loop(void) {
  switchstate=digitalRead(switchpin);
  Serial.println(switchstate);
  if(switchstate==HIGH) {
    // Magnetic sensor
    sensors_event_t event; 
    mag.getEvent(&event);
   
    Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
    Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
    Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");
  
    float heading = atan2(event.magnetic.y, event.magnetic.x);
  
    float declinationAngle = 0.261;
    heading += declinationAngle;
    
    if(heading < 0)
      heading += 2*PI;
      
    if(heading > 2*PI)
      heading -= 2*PI;
     
    float headingDegrees = heading * 180/M_PI; 
    //Serial.print("Heading (degrees): "); Serial.println(headingDegrees);
    
  }
  
  //solar
    // take a number of analog samples and add them up
    while (sample_count < NUM_SAMPLES) {
        sum += analogRead(A2);
        sample_count++;
        delay(10);
    }
    
    // calculate the voltage
    // use 5.0 for a 5.0V ADC reference voltage
    // 5.015V is the calibrated reference voltage
    voltage = ((float)sum / (float)NUM_SAMPLES * 5.015) / 1024.0;
    Serial.print(voltage);
    Serial.println (" V");
    sample_count = 0;
    sum = 0;

  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println("xxxxxxxxxxxx");
    dataFile.close();
    // print to the serial port too:
    Serial.println("logging data");
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }

  
  delay(500);
}
