#include <main.h>

void setup(void)
{
  task_ADC.runInCore0(taskADC, "ADC", 3000, 10, 0);  // Read the ADC values
}


void loop() {
//empty
}