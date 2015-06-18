#include "io.h"

#include "hw_types.h"
#include "hw_memmap.h"

#include "pin.h"
#include "rom.h"
#include "rom_map.h"
#include "utils.h"
#include "prcm.h"
#include "gpio.h"



// GPIO
#define        GREEN_GP                11   // (PIN_02) green


// PORT _ A0,A1,A2,A3 = (GPIO / 8)
#define        GREEN_PORT           GPIOA1_BASE   // 11/ 8 = 1


//  PIN _ 1,2,3,4,5,6,7,,,, = 1 << (GPIO % 8)
#define        GREEN_PIN     (1<< (GREEN_GP%8))




void RelayOn()
{
    GPIOPinWrite(GREEN_PORT, GREEN_PIN,GREEN_PIN);
}


 void RelayOff()
{
    GPIOPinWrite(GREEN_PORT, GREEN_PIN,0x00);
}

 unsigned char RelayState()
 {
	 long lGPIOStatus;

	 lGPIOStatus = MAP_GPIOPinRead(GREEN_PORT,GREEN_PIN);
	 return(lGPIOStatus >> (GREEN_GP % 8));
 }
