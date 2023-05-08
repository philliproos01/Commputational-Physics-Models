#include <SD.h>
#include <CCS811.h>
#include <dht.h>

#define PIN_SPI_CS 4

File myFile;
int myInt = -52;
float myFloat = -12.7;
String myString = "HELLO";
char myCharArray[] = "ArduinoGetStarted.com";
byte myByteArray[] = {'1', '2', '3', '4', '5'};

CCS811 sensor;
dht DHT;

#define DHT11_PIN 7

void setup() {
  Serial.begin(9600);
  while(sensor.begin() != 0){
            Serial.println("failed to init chip, please check if the chip connection is fine");
            delay(1000);
  }

  if (!SD.begin(PIN_SPI_CS)) {
      Serial.println(F("SD CARD FAILED, OR NOT PRESENT!"));
      while (1); // don't do anything more:
  }

  Serial.println(F("SD CARD INITIALIZED."));
  Serial.println(F("--------------------"));
  SD.remove("arduino.txt"); // delete the file if existed

  // create new file by opening file for writing
  myFile = SD.open("arduino.txt", FILE_WRITE);
  if (myFile) {
      myFile.print("t,temp,hum,pres,ppm,tvoc");
  }
  
}

void loop() {
    int chk = DHT.read11(DHT11_PIN);
    float time = 0.0;
    for (int i = 0; i < 10; i++) {
        time = time + 0.1;
        if (myFile) {
                myFile.print(time); myFile.print(",");
                myFile.print(DHT.temperature); myFile.print(",");
                myFile.print(DHT.humidity); myFile.print(",");
                myFile.print("PRESSURE"); myFile.print(",");
                myFile.print(sensor.getCO2PPM()); myFile.print(",");
                myFile.println(sensor.getTVOCPPB());
                //myFile.write("\n"); // new line
        
          if (DHT.temperature > -48) {
                Serial.print("Temperature = ");
                Serial.println(DHT.temperature);
                Serial.print("Humidity = ");
                Serial.println(DHT.humidity);
          }
          delay(1000);
          if(sensor.checkDataReady() == true){
                Serial.print("CO2: ");
                Serial.print(sensor.getCO2PPM());
                Serial.print("ppm, TVOC: ");
                Serial.print(sensor.getTVOCPPB());
                Serial.println("ppb");
          } else {
                Serial.println("Data is not ready!");
          }
          delay(1000); //5min is delay(300000)
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
