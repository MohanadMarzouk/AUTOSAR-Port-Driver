/******************************************************************************
 *
 * Module: Port
 *
 * File Name: main.c
 *
 * Description: a file in which the code will run
 *
 * Authors: Mohanad Marzouk
 *
 *******************************************************************************/

/*******************************************************************************
 *                             Included header files                           *
 *******************************************************************************/
#include "MCAL/inc/Port.h"

int main(void)
{
    Port_Init(&ConfigPtr);
    Port_SetPinDirection((ConfigPtr.portContainer[5].portPin[1].PortPinId), PORT_PIN_OUT);
	return 0;
}
