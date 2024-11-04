/******************************************************************************
 * global_Constants.h
 * Constants that will be used in the whole project
 *****************************************************************************/
#ifndef __GLOBAL_CONSTANTS_H__
#define __GLOBAL_CONSTANTS_H__

#include <Arduino.h>

// Use in external ESP32c3
// #define UART_RX_PIN 20     // GPIO for UART RX 
// #define UART_TX_PIN 21    // GPIO for UART TX 

// Use in ESP32c3+ADS1115 pcb
#define UART_TX_PIN 0     // GPIO for UART TX 
#define UART_RX_PIN 1    // GPIO for UART RX 

#define SERIAL_PORT Serial1
#define BAUD_RATE 115200


/* #endregion */
#endif
