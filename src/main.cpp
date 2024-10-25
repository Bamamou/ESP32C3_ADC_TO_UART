#include <main.h>

Adafruit_ADS1115 ads;         /* Use this for the 16-bit version */
//Adafruit_ADS1015 ads;       /* Use this for the 12-bit version */
int16_t adc3;                 //Raw data from ADC
float volts3;                 //Voltage values from ADC

const double lowThres=0.8, upThres=4.5; //Lower and upper threshold for the Throttle

int numRead=10;               //Number of readings for averaging
float avgVal[10];             //Array of raw readings
float sum=0.0;            
float filteredThrottle=0.0;   //Filtered Throttle signal


void taskADC(void *pvParameters)
{
  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }

  while(true)
    {
      //ADS1115 reading
      adc3 = ads.readADC_SingleEnded(3);
      volts3 = ads.computeVolts(adc3);

      //Averaging 10 readings to filter out noise
      sum=0;
      for(int i=0; i<numRead; i++){
        avgVal[i]=volts3;
        sum+=avgVal[i];
      }
      filteredThrottle=sum/numRead;

      //Conditionals for sending throttle values
      if(filteredThrottle>=lowThres && filteredThrottle<=upThres){
        // Serial.print("AIN3: "); Serial.print(adc3); Serial.print("  "); Serial.print(volts3); Serial.println("V");
        // Serial.print("Filtered AIN3: "); Serial.print(filteredThrottle); Serial.println("V");
        
        // Send only raw data with comment via UART
        SERIAL_PORT.print(filteredThrottle);
      } 
      else{
        // Serial.println("Throttle Disconnected")

        // Send only raw data with comment via UART
        SERIAL_PORT.print("Throttle Disconnected");
      }

      vTaskDelay(10/portTICK_PERIOD_MS);
    }
}



void setup(void)
{
  Serial.begin(115200);

  // Start UART communication with the specified baud rate
  SERIAL_PORT.begin(115200, SERIAL_8N1, UART_RX_PIN, UART_TX_PIN);

  //Empty array to storage unfiltered values
  for (int i = 0; i < numRead; i++) {
    avgVal[i] = 0;
  }

  xTaskCreate(taskADC, "taskADC", 5000, NULL, 1, NULL);  // Read the ADC values
}


void loop() {
//empty
}