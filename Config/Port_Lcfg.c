/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Lcfg.c
 *
 * Description: Link-Time Configurations
 *
 * Authors: Mohanad Marzouk
 *
 *******************************************************************************/

/*******************************************************************************
 *                             Included header files                           *
 *******************************************************************************/
#include "Config/Port_Lcfg.h"
#include "MCAL/inc/Port_Types.h"
#include "Common/Std_Types.h"

/*******************************************************************************
 *                             Configurations Structure                        *
 *******************************************************************************/
struct Port_ConfigType ConfigPtr =
{
 .portContainer[0] =
 {
  .PortNumberOfPortPins = 2,
  .portPin[0] =
  {
   .PinDirection = PORT_PIN_IN,
   .PortPinDirectionChangeable = TRUE,
   .PortPinId = 0,
   .PinInitialMode = PORT_PIN_MODE_CAN,
   .PinLevelValue = PORT_PIN_LEVEL_LOW,
   .PinMode = PORT_PIN_MODE_CAN,
   .PortPinModeChangeable = FALSE
  },
  .portPin[1] =
  {
   .PinDirection = PORT_PIN_IN,
   .PortPinDirectionChangeable = TRUE,
   .PortPinId = 0,
   .PinInitialMode = PORT_PIN_MODE_CAN,
   .PinLevelValue = PORT_PIN_LEVEL_LOW,
   .PinMode = PORT_PIN_MODE_CAN,
   .PortPinModeChangeable = FALSE
  },
 },
 .portContainer[5] =
 {
  .PortNumberOfPortPins = 2,
  .portPin[1] =
  {
   .PinDirection = PORT_PIN_OUT,
   .PortPinDirectionChangeable = TRUE,
   .PortPinId = PORT_F_PIN_1,
   .PinInitialMode = PORT_PIN_MODE_DIO,
   .PinLevelValue = PORT_PIN_LEVEL_HIGH,
   .PinMode = PORT_PIN_MODE_UART_M1,
   .PortPinModeChangeable = TRUE
  },
 }
};
