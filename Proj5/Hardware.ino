/*
  ReadAnalogVoltage

  Reads an analog input on pin 0, converts it to voltage, and prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/ReadAnalogVoltage
*/
#include <CCS811.h>
#include <dht.h>
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

dht DHT;

#define DHT11_PIN 7

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//CCS811 sensor(&Wire, /*IIC_ADDRESS=*/0x5A);
CCS811 sensor;

// the setup routine runs once when you press reset:
void setup() {
      // initialize serial communication at 9600 bits per second:
      Serial.begin(9600);
      lcd.begin(16, 2);
      // Print a message to the LCD.
      //lcd.print("VOLTAGE READOUT");
      Serial.begin(9600);
      
      pinMode(13, OUTPUT);   
      while(sensor.begin() != 0){
            Serial.println("failed to init chip, please check if the chip connection is fine");
            delay(1000);
      }
}

// the loop routine runs over and over again forever:
void loop() {
      // read the input on analog pin 0:
      int chk = DHT.read11(DHT11_PIN);
      Serial.print("Temperature = ");
      Serial.println(DHT.temperature);
      Serial.print("Humidity = ");
      Serial.println(DHT.humidity);
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
      sensor.writeBaseLine(0x847B);
      int sensorValue = analogRead(A0);
      digitalWrite(13, HIGH);
      
      // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
      float voltage = sensorValue * (5.0 / 1023.0);
      // print out the value you read:
      lcd.setCursor(0, 0);
      lcd.print("Voltage: ");
      lcd.print((voltage));
      lcd.print("   ");
      lcd.setCursor(0, 1);
      if (DHT.humidity > -48) {
          lcd.print("Humidity: ");
          lcd.print(DHT.humidity);
          lcd.print("%");
      }
      
      
      delay(1000);
      Serial.println(voltage);
      lcd.setCursor(0, 1);
    
      if (DHT.temperature > -48) {
          lcd.print("Temp: ");
          lcd.print(DHT.temperature);
          lcd.print((char)223);
          lcd.print("C   ");
      }
      
      delay(1000);
      
      lcd.setCursor(0, 1);
      if(sensor.checkDataReady() == true){
          lcd.print("CO2: ");
          lcd.print(sensor.getCO2PPM());
          lcd.print("ppm    ");
          lcd.setCursor(0, 0);
          lcd.print("TVOC: ");
          lcd.print(sensor.getTVOCPPB());
          lcd.println("ppb      ");
      } else {
          lcd.println("Data is not ready!");
      }
      sensor.writeBaseLine(0x847B);
      // print the number of seconds since reset:
      //lcd.print("Time Reset: " + (millis() / 1000) + "  Voltage: " + sensorValue);
}
