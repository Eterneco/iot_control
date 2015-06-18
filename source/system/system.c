#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// simplelink includes
#include "device.h"

// driverlib includes
#include "hw_memmap.h"
#include "hw_types.h"
#include "hw_ints.h"
#include "interrupt.h"
#include "prcm.h"
#include "rom.h"
#include "rom_map.h"
#include "pin.h"
#include "timer.h"
#include "utils.h"
#include "pin_mux_config.h"
#include "system.h"


//Free_rtos/ti-rtos includes
#include "osi.h"


// common interface includes
#ifndef NOTERM
#include "uart_if.h"
#endif
#include "gpio.h"
#include "gpio_if.h"
#include "uartA0.h"
#include "time.h"
#include "network_if.h"
#include "udma_if.h"

#include "common.h"
#include "network.h"
#include "smartconfig.h"


#define SLEEP_TIME              8000000
#define SPAWN_TASK_PRIORITY     9
#define OSI_STACK_SIZE          6000


// GLOBAL VARIABLES -- Start
cInt8          	acSendBuff[TX_BUFF_SIZE];	 // 1024
cInt8          	acRecvbuff[RX_BUFF_SIZE]; 	 // 1024
SlSecParams_t 	SecurityParams = {0};  		 // AP Security Parameters




/********************************************************************************
                          Server
********************************************************************************/


void HTTPServerTask()
{
    long lRetVal = -1;
    InitializeAppVariables();

    //
    // Following function configure the device to default state by cleaning
    // the persistent settings stored in NVMEM (viz. connection profiles &
    // policies, power policy etc)
    //
    // Applications may choose to skip this step if the developer is sure
    // that the device is in its default state at start of applicaton
    //
    // Note that all profiles and persistent settings that were done on the
    // device will be lost
    //
    lRetVal = ConfigureSimpleLinkToDefaultState();
    if(lRetVal < 0)
    {
        if (DEVICE_NOT_IN_STATION_MODE == lRetVal)
        	DBG_PRINT("Failed to configure the device in its default state\n\r");
        	LOOP_FOREVER();
    }

    DBG_PRINT("Device is configured in default state \n\r");


    //Read Device Mode Configuration
    ReadDeviceConfiguration();

    //Connect to Network
    lRetVal = ConnectToNetwork();

    //Stop Internal HTTP Server
    lRetVal = sl_NetAppStop(SL_NET_APP_HTTP_SERVER_ID);
    if(lRetVal < 0)
    {
        DBG_PRINT("Error [%d] \n\r",lRetVal);
        LOOP_FOREVER();
    }

    //Start Internal HTTP Server
    lRetVal = sl_NetAppStart(SL_NET_APP_HTTP_SERVER_ID);
    if(lRetVal < 0)
    {
    	DBG_PRINT("Error [%d] \n\r",lRetVal);
    	LOOP_FOREVER();
    }

    //Handle Async Events
    while(1)
    {

    }
}


//--------------------------------------------------------------------------------

void SystemTaskManager(void *pvParameters)
{

    while(1)
    {
    		HTTPServerTask();
    }

}

void SystemTaskCreate()
{
    // Initializing DMA
    UDMAInit();


    // Start the SimpleLink Host
    //
    VStartSimpleLinkSpawnTask(SPAWN_TASK_PRIORITY);

    //
    // Start the GetWeather task
    //
    osi_TaskCreate(SystemTaskManager,
                    (const signed char *)"system",
                    OSI_STACK_SIZE,
                    NULL,
                    1,
                    NULL );

}
