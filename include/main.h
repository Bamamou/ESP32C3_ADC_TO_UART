/******************************************************************************
 * main.h
 * Header for the main file
 *****************************************************************************/
#ifndef __MAIN_H__
#define __MAIN_H__

#include <Arduino.h>
#include <Adafruit_ADS1X15.h>
#include <SPI.h>


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "global_Constants.h"

//UART
#include <HardwareSerial.h>


void taskADC(void *pvParameters);

#endif