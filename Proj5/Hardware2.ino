#include <SD.h>
//#include <CCS811.h>
#include <dht.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>



#define PIN_SPI_CS 4

File myFile;
int myInt = -52;
float myFloat = -12.7;
String myString = "HELLO";
char myCharArray[] = "ArduinoGetStarted.com";
byte myByteArray[] = {'1', '2', '3', '4', '5'};

//CCS811 sensor;
dht DHT;
Adafruit_BMP280 bmp; // use I2C interface
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();

#define DHT11_PIN 7

void setup() {
  Serial.begin(9600);
  /*
  while(sensor.begin() != 0){
            Serial.println("failed to init chip, please check if the chip connection is fine");
            delay(1000);
  }*/
   Serial.println(F("BMP280 Sensortest"));

  unsigned status;
  //status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  status = bmp.begin();
  if (!status) {
    Serial.println(F("Could not find a pressure sensor"));
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  bmp_temp->printSensorDetails();
  
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
      myFile.println("t,temp,hum,pres");
  }

 
    float time = 0.0;
    for (int i = 0; i < 120; i++) {
        sensors_event_t temp_event, pressure_event;
        bmp_temp->getEvent(&temp_event);
        bmp_pressure->getEvent(&pressure_event);
        int chk = DHT.read11(DHT11_PIN);
        
        delay(1000);
        if (DHT.temperature > -48) {
              if (myFile) {
                      myFile.print(time); myFile.print(",");
                      myFile.print(DHT.temperature); myFile.print(",");         //temperature first
                      myFile.print(DHT.humidity); myFile.print(",");          //humidity next
                     // myFile.print(sensor.getCO2PPM()); myFile.print(",");
                      myFile.println(pressure_event.pressure);                //pressure next
                      //myFile.write("\n"); // new line
              
                
                      Serial.print("Temperature = ");
                      Serial.println(DHT.temperature);
                      Serial.print("Humidity = ");
                      Serial.println(DHT.humidity);
                      Serial.print(F("Pressure = "));
                      Serial.print(pressure_event.pressure);
                      Serial.println(" hPa");
                      time = time + 5.0;
          
          delay(300000); //5min is delay(300000)
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

void loop() {
    
}
