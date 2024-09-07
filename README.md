# ADS1115 ADC ESP32-C3
A simple ADC librairy for ADSS1115 from TI using an ESP32-C3.<br>
The ADC value is covetered into voltage and send to another microcontroller via UART on Serial1. The whole code is based the vanilla freeRTOS of espressif.<br>

## Pin layout
This is how the ESP32 should be connected to the ADS1115 I2C based chip


| ESP32 | ADS1115 |
| ------------- | ------------- |
| 5V         |  VCC   |
| GND        |  GND   |
| GPIO4      |   A0   |
| GPIO3      |   A3   |
| GPIO2      |   A2   |
| GPIO1      |   A1   |
| SDA (GPIO8)|   SDA  |
|SCL(GPIO9)  |   SCL  |
