/******************************************************************************
 * taks_ADC.h
 * Header for task_SaveToMemories.cpp
 *****************************************************************************/
#ifndef __task_ADC_H__
#define __task_ADC_H__

#include <Arduino.h>
#include <Adafruit_ADS1X15.h>
#include "global_Constants.h"
#include "global_Variables.h"

void taskADC(void *pvParameters);
void sendData(float);
float conditioning();
uint8_t computeChecksum(uint8_t* , size_t);

#endif