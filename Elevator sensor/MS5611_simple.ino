/*
  MS5611 Barometric Pressure & Temperature Sensor. Simple Example
  Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/czujnik-cisnienia-i-temperatury-ms5611.html
  GIT: https://github.com/jarzebski/Arduino-MS5611
  Web: http://www.jarzebski.pl
  (c) 2014 by Korneliusz Jarzebski
*/

#include <Wire.h>
#include <MS5611.h>
#include <SoftwareSerial.h>
#include <MP3.h>

/** define mp3 class */
MP3 mp3;

MS5611 ms5611;

double referencePressure;

void setup() 
{
  Serial.begin(9600);
  //mp3 setting
  mp3.begin(MP3_SOFTWARE_SERIAL);
  mp3.volume(0x1F);
  mp3.set_mode(MP3::SINGLE);
  mp3.play_sd(0x0000);
  mp3.pause();
  // Initialize MS5611 sensor
  Serial.println("Initialize MS5611 Sensor");

  while(!ms5611.begin())
  {
    Serial.println("Could not find a valid MS5611 sensor, check wiring!");
    delay(500);
  }
  Serial.println("READ");
  // Get reference pressure for relative altitude
  referencePressure = ms5611.readPressure();

  // Check settings
  checkSettings();
}

void checkSettings()
{
  Serial.print("Oversampling: ");
  Serial.println(ms5611.getOversampling());
}

void loop()
{
   playmp3();
        
  // Read raw values
  uint32_t rawTemp = ms5611.readRawTemperature();
  uint32_t rawPressure = ms5611.readRawPressure();

  // Read true temperature & Pressure
  double realTemperature = ms5611.readTemperature();
  long realPressure = ms5611.readPressure();

  // Calculate altitude
  float absoluteAltitude = ms5611.getAltitude(realPressure);
  float relativeAltitude = ms5611.getAltitude(realPressure, referencePressure);

  Serial.println("--");
/**
  Serial.print(" rawTemp = ");
  Serial.print(rawTemp);
  Serial.print(", realTemp = ");
  Serial.print(realTemperature);
  Serial.println(" *C");


  Serial.print(" rawPressure = ");
  Serial.print(rawPressure);
  Serial.print(", realPressure = ");
  Serial.print(realPressure);
  Serial.println(" Pa");
*/

  Serial.print(" absoluteAltitude = ");
  Serial.print(absoluteAltitude);
  
  Serial.print(" m, relativeAltitude = ");
  Serial.print(relativeAltitude);    
  Serial.println(" m");

  delay(1000);
}
void playmp3(){

    delay(5000);
	mp3.pause();
	delay(5000);
	mp3.pause();
}

