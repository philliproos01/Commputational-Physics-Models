
/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-write-variable-to-sd-card
 */

#include <SD.h>
#include "I2Cdev.h"
#include "MPU6050.h"
 
// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;
 
int16_t ax, ay, az;
int16_t gx, gy, gz;

#define PIN_SPI_CS 4

File myFile;
int myInt = -52;
float myFloat = -12.7;
String myString = "HELLO";
char myCharArray[] = "ArduinoGetStarted.com";
byte myByteArray[] = {'1', '2', '3', '4', '5'};

void setup() {
  Serial.begin(9600);

    if (!SD.begin(PIN_SPI_CS)) {
    Serial.println(F("SD CARD FAILED, OR NOT PRESENT!"));
    while (1); // don't do anything more:
  }

  Serial.println(F("SD CARD INITIALIZED."));
  Serial.println(F("--------------------"));
  SD.remove("arduino.txt"); // delete the file if existed

  // create new file by opening file for writing
  myFile = SD.open("arduino.txt", FILE_WRITE);

  //Serial.begin(38400);
  Wire.begin();
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  if (myFile) {
    myFile.print("t,ax,ay,az,gx,gy,gz");
  }
  
}

void loop() {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    float time = 0.0;
    for (int i = 0; i < 100; i++) {
    if (myFile) {
      accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
      time = time + 0.1;
      //myFile.print("a/g:\t");
      myFile.print(time); myFile.print(",");
      myFile.print(ax); myFile.print(",");
      myFile.print(ay); myFile.print(",");
      myFile.print(az); myFile.print(",");
      myFile.print(gx); myFile.print(",");
      myFile.print(gy); myFile.print(",");
      myFile.println(gz);
      Serial.print("a/g:\t");
      Serial.print(ax); Serial.print("\t");
      Serial.print(ay); Serial.print("\t");
      Serial.print(az); Serial.print("\t");
      Serial.print(gx); Serial.print("\t");
      Serial.print(gy); Serial.print("\t");
      Serial.println(gz);
     // myFile.write("\n"); // new line
    
/*
    for (int i = 0; i < 5; i++) {
      myFile.write(myByteArray[i]); // new line

      if (i < 4)
        myFile.write(","); // comma
    }
    myFile.write("\n"); // new line
*/
    
  } else {
    Serial.println(F("SD Card: error on opening file arduino.txt WRITE"));
  }
  }
  myFile.close();
  // open file for reading
  myFile = SD.open("arduino.txt", FILE_READ);
  if (myFile) {
    while (myFile.available()) {
      char ch = myFile.read(); // read characters one by one from Micro SD Card
      Serial.print(ch); // print the character to Serial Monitor
    }
    myFile.close();
  } else {
    Serial.print(F("SD Card: error on opening file arduino.txt"));
  }

}
