#include <main.h>

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
//Adafruit_ADS1015 ads;     /* Use this for the 12-bit version */
int16_t adc0, adc1, adc2, adc3, results;
float volts0, volts1, volts2, volts3, current;



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
      volts3 =  ads.computeVolts(adc3);
      results = ads.readADC_Differential_2_3();
      
      // // Print data to the serial monitor
      // Serial.println("-----------------------------------------------------------");
      
      //Serial.print("AIN0: "); Serial.print(adc0); Serial.print("  "); Serial.print(volts0); Serial.println("V");
      // Serial.print("AIN1: "); Serial.print(adc1); Serial.print("  "); Serial.print(volts1); Serial.println("V");
      // Serial.print("AIN2: "); Serial.print(adc2); Serial.print("  "); Serial.print(volts2); Serial.println("V");
      // Serial.print("AIN3: "); Serial.print(adc3); Serial.print("  "); Serial.print(volts3); Serial.println("V");
     // Serial.print("Differential: "); Serial.print(results); Serial.print("("); Serial.print(ads.computeVolts(results)); Serial.println("mV)");



      // Send data with comment via UART
      // Serial1.print("AIN0: "); Serial1.print(adc3); Serial.print("  "); Serial1.print(volts0); Serial1.println("V");
      // Serial1.print("AIN1: "); Serial1.print(adc1); Serial.print("  "); Serial1.print(volts1); Serial1.println("V");
      // Serial1.print("AIN2: "); Serial1.print(adc2); Serial.print("  "); Serial1.print(volts2); Serial1.println("V");
      // Serial1.print("AIN3: "); Serial1.print(adc3); Serial.print("  "); Serial1.print(volts3); Serial1.println("V");
      // Serial1.print("Differential: "); Serial1.print(results); Serial1.print("("); Serial1.print(ads.computeVolts(results)); Serial1.println("mV)");
      
      // // Send only raw data with comment via UART
      // Serial1.print(adc0); Serial.print("  "); Serial1.println(volts0);
      // Serial1.print(adc1); Serial.print("  "); Serial1.println(volts1);
      // Serial1.print(adc2); Serial.print("  "); Serial1.println(volts2);
      //Serial1.print(adc3); Serial.print(" Volt: "); Serial1.println(volts3);
      

      /* Please send only Data that is needed  */
      // Serial1.print(results);  Serial.print("  "); Serial1.print(ads.computeVolts(results));
       //Serial1.println(volts0);
      // Serial1.println(volts1);
      Serial1.println(volts3);
      //current = (volts3);

      vTaskDelay(10/portTICK_PERIOD_MS);


    }
}



void setup(void)
{
  Serial.begin(115200);
  Serial.println("Hello!");
  // Start UART communication with the specified baud rate
  Serial1.begin(115200, SERIAL_8N1, UART_RX_PIN, UART_TX_PIN);

 // Serial.println("Getting single-ended readings from AIN0..3");
 // Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");

  xTaskCreate(taskADC, "taskADC", 5000, NULL, 1, NULL);  // Read the ADC values
}


void loop() {
//empty
}