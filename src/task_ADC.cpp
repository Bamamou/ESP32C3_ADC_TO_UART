#include <task_ADC.h>

Adafruit_ADS1115 ads;         /* Use this for the 16-bit version */

int16_t adc3;                 //Raw data from ADC
float volts3;                 //Voltage values from ADC

const float lowThres=0.8, upThres=4.5; //Lower and upper threshold for the Throttle

int numRead=10;               //Number of readings for averaging
float avgVal[10];             //Array of raw readings
float sum=0.0;            
float filteredThrottle=0.0;   //Filtered Throttle signal
const int scaleFactor=100;    //Scale factor to send 2 decimal points

const uint8_t HEADER = 0xAA;  // Header byte
const uint8_t FOOTER = 0xBB;  // Footer byte


void taskADC(void *pvParameters)
{
  Serial.begin(115200);

  // Start UART communication with the specified baud rate
  SERIAL_PORT.begin(115200, SERIAL_8N1, UART_RX_PIN, UART_TX_PIN);

  //Empty array to storage unfiltered values
  for (int i = 0; i < numRead; i++) {
    avgVal[i] = 0;
  }

  if (!ads.begin()) {
    // Serial.println("Failed to initialize ADS.");
    while (1);
  }

  while(true)
    {
      filteredThrottle=conditioning();

      //Conditionals for sending throttle values
      if(filteredThrottle>=lowThres && filteredThrottle<=upThres){
        // Serial.print("AIN3: "); Serial.print(adc3); Serial.print("  "); Serial.print(volts3); Serial.println("V");
        // Serial.print("Filtered AIN3: "); Serial.print(filteredThrottle); Serial.println("V");
        
        // Send only packet via UART
        // SERIAL_PORT.print(filteredThrottle);
        sendData(filteredThrottle);

      } 
      else{
        // Serial.println("Throttle Disconnected");

        // Send only raw data with comment via UART
        // sendData(0);
        SERIAL_PORT.print("Throttle Disconnected");
      }

      vTaskDelay(task_ADC.getInterval()/portTICK_PERIOD_MS);
    }
}

float conditioning(){
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
      return filteredThrottle;
}

void sendData(float value) {
  // Encode the floating-point value to a fixed-point integer
  int encodedValue = static_cast<int>(value * scaleFactor);

  // Split the encoded value into two bytes
  uint8_t bytes[2];
  bytes[0] = encodedValue >> 8; // Most significant byte (MSB)
  bytes[1] = encodedValue & 0xFF;        // Least significant byte (LSB)

  uint8_t packet[5] = {HEADER, bytes[0], bytes[1], computeChecksum(packet + 1, 3), FOOTER };

  // Send the packet using a for loop
  Serial.print("Sending packet: ");
  for (int i = 0; i < 5; i++) {
    Serial.printf("%02X ", packet[i]);
    SERIAL_PORT.write(packet[i]);
  }
  Serial.println();
}

uint8_t computeChecksum(uint8_t* data, size_t length) {
  uint8_t crc = 0;
  for (size_t i = 0; i < length; ++i) {
    crc ^= data[i];
  }
  return crc;
}