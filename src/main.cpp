#include <Arduino.h>
#include <Adafruit_ADS1X15.h>
#include <SPI.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


//Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
Adafruit_ADS1015 ads;     /* Use this for the 12-bit version */
int16_t adc0, adc1, adc2, adc3, results;
float volts0, volts1, volts2, volts3;
float multiplier = 0.0001875F; /* ADS1115  @ +/- 6.144V gain (16-bit results) */



void taskADC(void *pvParameters)
{
  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }

  while(true)
    {
      adc0 = ads.readADC_SingleEnded(0);
      adc1 = ads.readADC_SingleEnded(1);
      adc2 = ads.readADC_SingleEnded(2);
      adc3 = ads.readADC_SingleEnded(3);

      volts0 = ads.computeVolts(adc0);
      volts1 = ads.computeVolts(adc1);
      volts2 = ads.computeVolts(adc2);
      volts3 = ads.computeVolts(adc3);
      results = ads.readADC_Differential_2_3();
      

      Serial.println("-----------------------------------------------------------");
      
      Serial.print("AIN0: "); Serial.print(adc3); Serial.print("  "); Serial.print(volts0); Serial.println("V");
      Serial.print("AIN1: "); Serial.print(adc1); Serial.print("  "); Serial.print(volts1); Serial.println("V");
      Serial.print("AIN2: "); Serial.print(adc2); Serial.print("  "); Serial.print(volts2); Serial.println("V");
      Serial.print("AIN3: "); Serial.print(adc3); Serial.print("  "); Serial.print(volts3); Serial.println("V");
      Serial.print("Differential: "); Serial.print(results); Serial.print("("); Serial.print(ads.computeVolts(results)); Serial.println("mV)");

      vTaskDelay(1000/portTICK_PERIOD_MS);


    }
}



void setup(void)
{
  Serial.begin(115200);
  Serial.println("Hello!");

  Serial.println("Getting single-ended readings from AIN0..3");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");

  xTaskCreate(taskADC, "taskADC", 5000, NULL, 1, NULL);  // Read the ADC values
}


void loop() {
  //empty
}