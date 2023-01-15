/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Functions declaration of Port module
 *
 * Authors: Mohanad Marzouk
 *
 * AUTOSAR Standard Release: 4.3.1
 *
 *******************************************************************************/

/*******************************************************************************
 *                             Included header files                           *
 *******************************************************************************/
#include "MCAL/inc/Port.h"

/*******************************************************************************
 *                        Static variables deceleration                        *
 *******************************************************************************/
static uint32   GPIO_BASE_ADDRESS[6]   =        {0x40004000,            //Port A base
                                                 0x40005000,            //Port B base
                                                 0x40006000,            //Port C base
                                                 0x40007000,            //Port D base
                                                 0x40024000,            //Port E base
                                                 0x40025000};           //Port F base

static volatile uint8 PORT_MODE [13][6] =
{
                             //A,B,C,D,E,F
                              {0,7,7,0,0,7}, // GPT Encoding
                              {0,0,7,7,0,0}, // WD Encoding
                              {1,1,1,1,1,1}, // UART_M1 Encoding
                              {0,0,2,0,0,0}, // UART_M2 Encoding
                              {0,0,8,0,0,0}, // UART_M3 Encoding
                              {2,2,0,1,0,2}, // SSI_M1 Encoding
                              {0,0,0,2,0,0}, // SSI_M2 Encoding
                              {3,3,0,3,3,0}, // I2C Encoding
                              {8,8,0,0,8,3}, // CAN Encoding
                              {0,0,8,8,0,8}, // USB_TTL Encoding
                              {5,4,4,4,4,4}, // PWM_M1 Encoding
                              {0,0,0,5,5,5}, // PWM_M2 Encoding
                              {0,0,6,6,0,6}, //QEI Encoding
};


/*******************************************************************************
 *                         DIO API's Declaration                        *
 *******************************************************************************/

/************************************************************************************
 * Service Name: Port_Init
 * Service ID: 0x00
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): ConfigPtr
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initializes the Port Driver module.
 ************************************************************************************/

void Port_Init(const struct Port_ConfigType* ConfigPtr)
{
    if(ConfigPtr == NULL_PTR)
    {
#if PortDevErrorDetect
        Det_ReportError(Port_Module_ID, Port_Instance_ID, Port_Init_Service_ID, PORT_E_PARAM_POINTER);
#endif
    }
    else
    {
        uint8 Port_Index;                       /*save port index*/
        uint8 Pin_Index;                        /*save pin index*/
        volatile uint32 Port_Base_Address;      /*save variable base address*/
        uint8 PIN_INITIAL_MODE;                 /*save the pin initial mode as per the config struct*/
        uint8 PORT_MODE_ENCODING;               /*store the mode encoding of a specified pin*/
        uint8 PIN_DIRECTION;                    /*save pin direction as per the config struct*/
        uint8 PIN_LEVEL_VALUE;                  /*save pin level value as per the congig struct*/

        SYSCTL_RCGCGPIO_R |= 0x3F;              /*enable clock to all ports*/

        for(Port_Index = 0; Port_Index < PORT_CONTAINER_SIZE; Port_Index++)     /*loop over all  ports*/
        {
            Port_Base_Address = (GPIO_BASE_ADDRESS[Port_Index]);                /*get the port base address from the addresses array*/

            for(Pin_Index = 0; Pin_Index < PORT_PIN_SIZE; Pin_Index++)          /*loop over all pins*/
            {
                /*Save Port Initial Mode*/

                PIN_INITIAL_MODE = ConfigPtr->portContainer[Port_Index].portPin[Pin_Index].PinInitialMode;

                /*check if pin is configured in the config strcut*/
                if(PIN_INITIAL_MODE != 0)
                {
                    /*Save Pin Direction*/

                    PIN_DIRECTION = ConfigPtr->portContainer[Port_Index].portPin[Pin_Index].PinDirection;

                    /*Save Pin Level Value*/

                    PIN_LEVEL_VALUE = ConfigPtr->portContainer[Port_Index].portPin[Pin_Index].PinLevelValue;

                    /*If pin is configured ADC OR USB_ANALOG OR ANALOG COMP*/

                    if((PIN_INITIAL_MODE == PORT_PIN_MODE_ADC) || (PIN_INITIAL_MODE == PORT_PIN_MODE_USB_ANALOG) || (PIN_INITIAL_MODE == PORT_PIN_MODE_AC))
                    {
                        CLEAR_BIT(*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_DEN_Offset)) , Pin_Index);
                        SET_BIT(*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_AMSEL_Offset)), Pin_Index);
                        SET_BIT(*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_AFSEL_Offset)), Pin_Index);
                    }

                    /*If pin is configured DIO*/

                    else if(PIN_INITIAL_MODE == PORT_PIN_MODE_DIO)
                    {
                        /*check if pin is special according to the data sheet*/

                        if(((Pin_Index == 7) && (Port_Index== 3)) || ((Pin_Index == 0) && (Port_Index== 5))) /* PD7 or PF0 */
                        {
                            /*Unlock to write in the CR*/
                            *((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_LOCK_Offset )) = Unlock_Encoding;
                            SET_BIT(*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_CR_Offset)) , Pin_Index);
                        }

                        /*for pin to work as DIO
                         * the pin has to go through the following:
                         */

                        SET_BIT(*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_DEN_Offset)) , Pin_Index);            /*enable digital function for the pin*/
                        CLEAR_BIT(*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_AFSEL_Offset)) , Pin_Index);        /*clear AFSEL register*/
                        CLEAR_BIT(*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_AMSEL_Offset)) , Pin_Index);        /*clear AMSEL register*/
                        CLEAR_BIT(*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_PCTL_Offset)) , Pin_Index);         /*clear PCTL register*/
                    }

                    /*If configured anything other than DIO*/
                    else
                    {
                        /* for pin to work as any mode other than DIO
                         * pin must go through the following:
                         */
                        PORT_MODE_ENCODING = PORT_MODE[PIN_INITIAL_MODE - 2][Port_Index];                                                               /*save mode encoding according to the mapping of modes by the 2D array*/
                        SET_BIT(*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_DEN_Offset)) , Pin_Index);                            /*enable digital function for the pin*/
                        SET_BIT(*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_AFSEL_Offset)) , Pin_Index);                          /*set AFSEL register*/
                        CLEAR_BIT(*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_AMSEL_Offset)) , Pin_Index);                        /*clear AMSEL register*/
                        (*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_PCTL_Offset)) &= ~ (0xF<<(4*Pin_Index)));                    /*clear the pin before writing to the PCTL register*/
                        (*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_PCTL_Offset)) |= PORT_MODE_ENCODING << (4*Pin_Index));       /*write the mode encoding to the PCTL register*/
                    }

                    /*Check Pin Direction*/

                    if(PIN_DIRECTION == PORT_PIN_OUT)           /*Pin direction is OUTPUT*/
                    {
                        SET_BIT(*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_DIR_Offset)) , Pin_Index);
                    }
                    else            /*Pin direction is INPUT*/
                    {

                        CLEAR_BIT(*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_DIR_Offset)) , Pin_Index);
                    }

                    /*Check Pin Level Value*/

                    if(PIN_LEVEL_VALUE == PORT_PIN_LEVEL_HIGH)      /*Pin Level is HIGH*/
                    {
                        SET_BIT(*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_DATA_Offset)) , Pin_Index);
                    }
                    else            /*Pin Level is LOW*/
                    {
                        CLEAR_BIT(*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_DATA_Offset)) , Pin_Index);
                    }
                }
            }
        }
        /*
         * port has been successfully initialized
         */
        PORT_STATUS = PORT_INITIALIZED;
    }
}

/************************************************************************************
 * Service Name: Port_SetPinDirection
 * Service ID: 0x01
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Pin, Direction
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Sets the port pin direction
 ************************************************************************************/
#if PortSetPinDirectionApi
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{
    /*check if port is initialized*/
    if (PORT_STATUS != PORT_INITIALIZED)
    {
#if PortDevErrorDetect
        Det_ReportError(Port_Module_ID, Port_Instance_ID, Port_SetPinDirection_Service_ID, PORT_E_UNINIT);
#endif
    }
    /*port is initialized
      check the input pin is within the MCU pins
     */
    else if(Pin > 44)
    {
#if PortDevErrorDetect
        Det_ReportError(Port_Module_ID, Port_Instance_ID, Port_SetPinDirection_Service_ID, PORT_E_PARAM_PIN);
#endif
        /*return without setting direction*/
    }

    else
    {
        /*start of service*/

        uint8 Port_Index = Pin / 8;             /*save port index*/
        uint8 Pin_Index = Pin % 8;              /*save pin index*/
        EcucBooleanParamDef Direction_Status = ConfigPtr.portContainer[Port_Index].portPin[Pin_Index].PortPinDirectionChangeable;       /*save whether the direction is changeable on a port pin during runtime or not */

        if(Direction_Status)            /*direction is changeable on a port pin during runtime.*/
        {
            /*if direction is set to output, set it as input*/
            if(Direction == PORT_PIN_OUT)
            {
                SET_BIT(*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_DIR_Offset)), Pin_Index);
            }

            /*if direction is set to input, set it as output*/
            else
            {
                CLEAR_BIT(*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_DIR_Offset)), Pin_Index);
            }
        }
    }
}
#endif

/************************************************************************************
 * Service Name: Port_SetPinMode
 * Service ID: 0x04
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): Pin, Mode
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Sets the port pin mode
 ************************************************************************************/
#if PortSetPinModeApi
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{
    /*check if port is initialized*/
    if (PORT_STATUS != PORT_INITIALIZED)
    {
#if PortDevErrorDetect
        Det_ReportError(Port_Module_ID, Port_Instance_ID, Port_SetPinMode_Service_ID, PORT_E_UNINIT);
#endif
    }
    /*port is initialized
      check the input pin is within the MCU pins
     */
    else if(Pin > 44)
    {
#if PortDevErrorDetect
        Det_ReportError(Port_Module_ID, Port_Instance_ID, Port_SetPinMode_Service_ID, PORT_E_PARAM_PIN);
#endif
        /*return without setting mode*/
    }
    else
    {
        /*start of service*/

        uint8 Port_Index = Pin / 8;         /*save for port index*/
        uint8 Pin_Index = Pin % 8;          /*save for pin index*/
        EcucBooleanParamDef Mode_Status = ConfigPtr.portContainer[Port_Index].portPin[Pin_Index].PortPinModeChangeable; /*save whether the mode is changeable on a port pin during runtime or not */
        uint8 PORT_MODE_ENCODING;
        if(Mode_Status)
        {
            /*check if pin is configured in the config strcut*/
            if(Mode != 0)
            {
                /*If pin is configured ADC OR USB_ANALOG OR ANALOG COMP*/

                if((Mode == PORT_PIN_MODE_ADC) || (Mode == PORT_PIN_MODE_USB_ANALOG) || (Mode == PORT_PIN_MODE_AC))
                {
                    CLEAR_BIT(*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_DEN_Offset)) , Pin_Index);
                    SET_BIT(*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_AMSEL_Offset)), Pin_Index);
                    SET_BIT(*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_AFSEL_Offset)), Pin_Index);
                }

                /*If pin is configured DIO*/

                else if(Mode == PORT_PIN_MODE_DIO)
                {
                    /*check if pin is special according to the data sheet*/

                    if(((Pin_Index == 7) && (Port_Index== 3)) || ((Pin_Index == 0) && (Port_Index== 5))) /* PD7 or PF0 */
                    {
                        /*Unlock to write in the CR*/
                        *((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_LOCK_Offset )) = Unlock_Encoding;
                        SET_BIT(*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_CR_Offset)) , Pin_Index);
                    }

                    /*for pin to work as DIO
                     * the pin has to go through the following:
                     */
                    SET_BIT(*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_DEN_Offset)) , Pin_Index);            /*enable digital function for the pin*/
                    CLEAR_BIT(*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_AFSEL_Offset)) , Pin_Index);        /*clear AFSEL register*/
                    CLEAR_BIT(*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_AMSEL_Offset)) , Pin_Index);        /*clear AMSEL register*/
                    CLEAR_BIT(*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_PCTL_Offset)) , Pin_Index);         /*clear PCTL register*/
                }

                /*If configured anything other than DIO*/
                else
                {
                    /* for pin to work as any mode other than DIO
                     * pin must go through the following:
                     */
                    PORT_MODE_ENCODING = PORT_MODE[Mode - 2][Port_Index];                                                               /*save mode encoding according to the mapping of modes by the 2D array*/
                    SET_BIT(*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_DEN_Offset)) , Pin_Index);                            /*enable digital function for the pin*/
                    SET_BIT(*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_AFSEL_Offset)) , Pin_Index);                          /*set AFSEL register*/
                    CLEAR_BIT(*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_AMSEL_Offset)) , Pin_Index);                        /*clear AMSEL register*/
                    (*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_PCTL_Offset)) &= ~ (0xF<<(4*Pin_Index)));                    /*clear the pin before writing to the PCTL register*/
                    (*((volatile unsigned long *)(GPIO_BASE_ADDRESS[Port_Index] + GPIO_PCTL_Offset)) |= PORT_MODE_ENCODING << (4*Pin_Index));       /*write the mode encoding to the PCTL register*/
                }
            }
        }
    }
}
#endif

/************************************************************************************
 * Service Name: Port_GetVersionInfo
 * Service ID: 0x03
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): versioninfo
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Returns the version information of this module.
 ************************************************************************************/
#if PortVersionInfoApi == STD_ON
void Port_GetVersionInfo(struct Std_VersionInfoType* versioninfo)
{
    if(versioninfo == NULL_PTR)
    {
#if PortDevErrorDetect
        Det_ReportError(Port_Module_ID, Port_Instance_ID, Port_GetVersionInfo_Service_ID, PORT_E_PARAM_POINTER);
#endif
    }
    else
    {
        versioninfo->moduleID = vendorID;
        versioninfo->moduleID = Port_Module_ID;
        versioninfo->sw_major_version = Port_SW_Major_Version;
        versioninfo->sw_minor_version = Port_SW_Minor_Version;
        versioninfo->sw_patch_version = Port_SW_Patch_Version;
    }
}
#endif
