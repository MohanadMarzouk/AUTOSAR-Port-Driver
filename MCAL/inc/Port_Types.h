/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Types.h
 *
 * Description: Type Definitions and Included Containers of Port Module
 *
 * Authors: Mohanad Marzouk
 *
 * AUTOSAR Standard Release: 4.3.1
 *
 *******************************************************************************/
#ifndef PORT_TYPES_H_
#define PORT_TYPES_H_

/*******************************************************************************
 *                             Included header files                           *
 *******************************************************************************/
#include "Common/Platform_Types.h"

/*
 * [SWS_Port_00073] The type Port_ConfigType is a type for the external data structure containing the initialization data for the PORT Driver.
 */
#define Port_ConfigType    PortConfigSet    //Type of the external data structure containing the initialization data for this module.

#define PORT_PIN_SIZE       8
#define PORT_CONTAINER_SIZE 6

/*
 * SWS_Port_00013] The type Port_PinType shall be used for the symbolic name of a Port Pin.
  [SWS_Port_00219] The type Port_PinType shall be uint8, uint16 or uint32 based on the specific MCU platform.
 */
typedef uint8 Port_PinType;             // Data type for the symbolic name of a port pin.

/*
 * [SWS_Port_00124] A port pin shall be configurable with a number of port pin modes (type Port_PinModeType).
   [SWS_Port_00212] The type Port_PinModeType shall be used with the function call Port_SetPinMode
 */
typedef uint8 Port_PinModeType;         // Different port pin modes.

/*
 * [SWS_Port_00207] These symbolic names for the individual port pins (e.g. PORT_A_PIN_0) shall be defined in the configuration tool.
 */
typedef enum
{
    //from pin0>> to PIn47
        PORT_A_PIN_0,
        PORT_A_PIN_1,
        PORT_A_PIN_2,
        PORT_A_PIN_3,
        PORT_A_PIN_4,
        PORT_A_PIN_5,
        PORT_A_PIN_6,
        PORT_A_PIN_7,
        /*
         * PORTB
         */
        PORT_B_PIN_0,
        PORT_B_PIN_1,
        PORT_B_PIN_2,
        PORT_B_PIN_3,
        PORT_B_PIN_4,
        PORT_B_PIN_5,
        PORT_B_PIN_6,
        PORT_B_PIN_7,
        /*
         * PORTC
         */
        PORT_C_PIN_0,
        PORT_C_PIN_1,
        PORT_C_PIN_2,
        PORT_C_PIN_3,
        PORT_C_PIN_4,
        PORT_C_PIN_5,
        PORT_C_PIN_6,
        PORT_C_PIN_7,
        /*
         * PORTD
         */
        PORT_D_PIN_0,
        PORT_D_PIN_1,
        PORT_D_PIN_2,
        PORT_D_PIN_3,
        PORT_D_PIN_4,
        PORT_D_PIN_5,
        PORT_D_PIN_6,
        PORT_D_PIN_7,
        /*
         * PORTE
         */
        PORT_E_PIN_0,
        PORT_E_PIN_1,
        PORT_E_PIN_2,
        PORT_E_PIN_3,
        PORT_E_PIN_4,
        PORT_E_PIN_5,
        /*
         * PORTF
         */
        PORT_F_PIN_0 = 40,
        PORT_F_PIN_1,
        PORT_F_PIN_2,
        PORT_F_PIN_3,
        PORT_F_PIN_4
}Pin_Num;

/*******************************************************************************
 *                       Pin Direction Types                                   *
 *******************************************************************************/

/*[SWS_Port_00046] The type Port_PinDirectionType is a type for defining the direction of a Port Pin.
  [SWS_Port_00220] The type Port_PinDirectionType shall be of enumeration type having range as PORT_PIN_IN and PORT_PIN_OUT.
*/
typedef enum
{
    PORT_PIN_IN,
    PORT_PIN_OUT
}Port_PinDirectionType;

/*******************************************************************************
 *                        Pin Modes supported by TM4C MCU                      *
 *******************************************************************************/

/*
 * Port pin mode from mode list.
 * ECUC_Port_00130
 */
typedef enum
{
    PORT_PIN_MODE_DIO = 1,
    PORT_PIN_MODE_GPT,
    PORT_PIN_MODE_DIO_WD,
    PORT_PIN_MODE_UART_M1, /*First Pin Supporting UART in data sheet*/
    PORT_PIN_MODE_UART_M2, /*Second Pin Supporting UART in data sheet*/
    PORT_PIN_MODE_UART_M3, /*Third Pin Supporting UART in data sheet*/
    PORT_PIN_MODE_SSI_M1,  /*First Pin Supporting SSI in data sheet*/
    PORT_PIN_MODE_SSI_M2,  /*Second Pin Supporting SSI in data sheet*/
    PORT_PIN_MODE_I2C,
    PORT_PIN_MODE_CAN,
    PORT_PIN_MODE_USB_TTL,
    PORT_PIN_MODE_PWM_M1,  /*First Pin Supporting PWM in data sheet*/
    PORT_PIN_MODE_PWM_M2,  /*Second Pin Supporting PWM in data sheet*/
    PORT_PIN_MODE_QEI,
    PORT_PIN_MODE_ADC,
    PORT_PIN_MODE_USB_ANALOG,
    PORT_PIN_MODE_AC,
}PortPinInitialMode,PortPinMode;

/*
 * Port Pin Level value from Port pin list.
 * ECUC_Port_00129
 */
typedef enum
{    PORT_PIN_LEVEL_LOW,
    PORT_PIN_LEVEL_HIGH
}PortPinLevelValue;

/*******************************************************************************
 *******************************************************************************
 *        PortPin:  sub-container for     PortContainer                        *
 *******************************************************************************
 *******************************************************************************/
struct PortPin
{
    Port_PinDirectionType   PinDirection;
    EcucBooleanParamDef     PortPinDirectionChangeable;
    EcucIntegerParamDef     PortPinId;
    PortPinInitialMode      PinInitialMode;
    PortPinLevelValue       PinLevelValue;
    PortPinMode             PinMode;
    EcucBooleanParamDef     PortPinModeChangeable;
};

/*******************************************************************************
 *******************************************************************************
 *        PortContainer:  sub-container for     PortConfigSet                  *
 *******************************************************************************
 *******************************************************************************/
struct PortContainer
{
    EcucIntegerParamDef            PortNumberOfPortPins;
    struct PortPin                 portPin[PORT_PIN_SIZE];

};

/*******************************************************************************
 *******************************************************************************
 *                   PortConfigSet Container                                   *
 *******************************************************************************
 *******************************************************************************/
struct PortConfigSet
{
    struct PortContainer   portContainer[PORT_CONTAINER_SIZE];
};
#endif /* PORT_TYPES_H_ */
