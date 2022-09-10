// Arduino Temperature Logger with several DS18S20 in combination with a Windows C# program
// Created by astro_alex 
// Email: astroalex@gmx.de
// Use on own risk without any warranty

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 3              // Arduino Pin on which the DS18S20 are installed
#define TEMPERATURE_PRECISION 12    // 


// Setup a OneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass OneWire reference to Dallas Temperature
DallasTemperature sensors(&oneWire);

String cmd; // takes the command send from Serial-Port

// enter here the individual device addresses sensor by sensor
// run the Test sketch of the Dallas temperature libary first and note the indivudual addresses
DeviceAddress sensor1 = { 0x28, 0xF9, 0x91, 0x49, 0xF6, 0xFA, 0x3C, 0xCC };
DeviceAddress sensor2 = { 0x28, 0x25, 0x8D, 0x49, 0xF6, 0x6B, 0x3C, 0x2F };
DeviceAddress sensor3 = { 0x28, 0x25, 0x8D, 0x49, 0xF6, 0x6B, 0x3C, 0x2F };
DeviceAddress sensor4 = { 0x28, 0x25, 0x8D, 0x49, 0xF6, 0x6B, 0x3C, 0x2F };
DeviceAddress sensor5 = { 0x28, 0x25, 0x8D, 0x49, 0xF6, 0x6B, 0x3C, 0x2F };
DeviceAddress sensor6 = { 0x28, 0x25, 0x8D, 0x49, 0xF6, 0x6B, 0x3C, 0x2F };

void setup() {
  Serial.begin(9600); //start serial

  sensors.begin();
  
  sensors.setResolution(sensor1, TEMPERATURE_PRECISION); //12-bit
  sensors.setResolution(sensor2, TEMPERATURE_PRECISION); //12-bit
//  sensors.setResolution(sensor3, TEMPERATURE_PRECISION); //12-bit
//  sensors.setResolution(sensor4, TEMPERATURE_PRECISION); //12-bit
//  sensors.setResolution(sensor5, TEMPERATURE_PRECISION); //12-bit
//  sensors.setResolution(sensor6, TEMPERATURE_PRECISION); //12-bit  
}

void loop() {
      
  if(Serial.available() > 0){
      
      cmd = Serial.readStringUntil('#');

      if(cmd == "C"){ // Check if a an Arduino Temperature Logger is connected
        Serial.print("T#");
      }

      if(cmd == "R") { // Temperature Reading command sent 

        sensors.requestTemperatures();
  
        String tSensor1, tSensor2, tSensor3, tSensor4, tSensor5, tSensor6;

        // Read temperature, device by device
        tSensor1 = String(sensors.getTempC(sensor1));      
        tSensor2 = String(sensors.getTempC(sensor2)); 
        tSensor3 = String(sensors.getTempC(sensor3)); 
        tSensor4 = String(sensors.getTempC(sensor4)); 
        tSensor5 = String(sensors.getTempC(sensor5)); 
        tSensor6 = String(sensors.getTempC(sensor6)); 

        // if no sensor conncected replace reading by ""
        tSensor1 == "-127.00" ? "" : tSensor1;
        tSensor2 == "-127.00" ? "" : tSensor2;
        tSensor3 == "-127.00" ? "" : tSensor3;
        tSensor4 == "-127.00" ? "" : tSensor4;
        tSensor5 == "-127.00" ? "" : tSensor5;
        tSensor6 == "-127.00" ? "" : tSensor6;

        // replace . in temperature readings with comma
        tSensor1.replace(".",",");
        tSensor2.replace(".",",");
        tSensor3.replace(".",",");
        tSensor4.replace(".",",");
        tSensor5.replace(".",",");
        tSensor6.replace(".",",");
        
        // build combined string, temperature readings separated by semicolon
        String serialString = tSensor1 + ";" + tSensor2 + ";" + tSensor3 + ";" + tSensor4 + ";" + tSensor5 + ";" + tSensor6 + "#";

        // send string to serial
        Serial.print(serialString);
        
      }
  }
  
}
