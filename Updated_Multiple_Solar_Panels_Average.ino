#include <SD.h>
#include <SPI.h>

File myFile;

#define NUM 10
float Voltage = 0;
float k =0.00428;
const int pinCS = 4;
int sum = 0;
unsigned char sample_count =0;
float voltage =0.0;
void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
}


void loop() {
  while (sample_count < NUM){
    sum += analogRead(A2);
    sample_count++;
    delay (100);
  }

Voltage = ((float)sum / (float)NUM)*k; //// ch 

Serial.print (Voltage);
sample_count =0;
sum =0;

 // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("solar.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to solar.txt...");
    myFile.println(Voltage);
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}
  
//}

//void setup() {
//Serial.begin(9600); }
//void loop() {
//int v = analogRead(0);
//Serial.print(v);
//Serial.print(' ');
//delay(900);
//}
