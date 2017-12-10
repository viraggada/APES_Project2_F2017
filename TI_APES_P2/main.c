/*****************************************************
 * File: main.c
 * Authors: Virag Gada and Vihanga Bare
 * Description: Source file for APES Project 2
 ****************************************************/

#include "main.h"
#include <tmp102.h>
#include <lsm6ds3.h>

// FreeRTOS includes
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


// Demo Task declarations
void temperatureTask(void *pvParameters);
void pedometerTask(void *pvParameters);

// Main function
int main(void)
{
  // Initialize system clock to 120 MHz
  system_clock_rate_hz = ROM_SysCtlClockFreqSet(
                            (SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |
                             SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480),
                            SYSTEM_CLOCK);
  ASSERT(system_clock_rate_hz == SYSTEM_CLOCK);

  // Initialize the GPIO pins for the Launchpad
  // Use Ethernet
  PinoutSet(true, false);

  // Set up the UART which is connected to the virtual COM port
  UARTStdioConfig(0, 57600, SYSTEM_CLOCK);

  // Create demo tasks
  xTaskCreate(temperatureTask, (const portCHAR *)"Temperature",
             configMINIMAL_STACK_SIZE, NULL, 1, NULL);

  xTaskCreate(pedometerTask, (const portCHAR *)"Pedometer",
             configMINIMAL_STACK_SIZE, NULL, 1, NULL);

  //vTaskStartScheduler();

  setupTMP102();

  double temp;

  readTMP102(&temp);

  char tempVal[10] = {(int)'\0'};

  sprintf(tempVal,"%f",temp);

  UARTprintf("Digital Temperature - %s\n",tempVal);
  return 0;
}


// Task to receive data from the temperature sensor
void temperatureTask(void *pvParameters)
{

}


// Task to receive foot step count from the sensor
void pedometerTask(void *pvParameters)
{

}

/*  ASSERT() Error function
 *  failed ASSERTS() from driverlib/debug.h are executed in this function
 */
void __error__(char *pcFilename, uint32_t ui32Line)
{
    // Place a breakpoint here to capture errors until logging routine is finished
    while (1)
    {
    }
}
