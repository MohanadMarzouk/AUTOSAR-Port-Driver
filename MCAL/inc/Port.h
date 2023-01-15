/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Functions definition of Port module
 *
 * Authors: Mohanad Marzouk
 *
 * AUTOSAR Standard Release: 4.3.1
 *
 *******************************************************************************/
#ifndef PORT_H_
#define PORT_H_
/*******************************************************************************
 *                             Included header files                           *
 *******************************************************************************/
#include "Common/Std_Types.h"
#include "MCAL/inc/Port_Types.h"
#include "Config/Port_Lcfg.h"
#include "Common/tm4c123gh6pm.h"
#include "Common/Common_Macros.h"
#include "Config/Port_Cfg.h"
#include "Det/inc/Det.h"
//*****************************************************************************
//
//                      DET ERROR Codes
//
//*****************************************************************************
#define PORT_E_PARAM_PIN                    (0x0A)
#define PORT_E_DIRECTION_UNCHANGEABLE       (0x0B)
#define PORT_E_INIT_FAILED                  (0x0C)
#define PORT_E_PARAM_INVALID_MODE           (0x0D)
#define PORT_E_MODE_UNCHANGEABLE            (0x0E)
#define PORT_E_UNINIT                       (0x0F)
#define PORT_E_PARAM_POINTER                (0x10)


//*****************************************************************************
//
//                      Service IDs
//
//*****************************************************************************
#define Port_Init_Service_ID                        (0x00)
#define Port_SetPinDirection_Service_ID             (0x01)
#define Port_RefreshPortDirection_Service_ID        (0x02)
#define Port_GetVersionInfo_Service_ID              (0x03)
#define Port_SetPinMode_Service_ID                  (0x04)

//*****************************************************************************
//
//                      Module Version
//
//*****************************************************************************
#define Port_SW_Major_Version            (1)
#define Port_SW_Minor_Version            (0)
#define Port_SW_Patch_Version            (0)
#define Port_Module_ID                   (1)
#define Port_Instance_ID                 (0)
#define vendorID                         (0702)  /*random no.*/

//*****************************************************************************
//
//                      GPIO OFFSETS
//
//*****************************************************************************
#define GPIO_IS_Offset         (0x404)
#define GPIO_DATA_Offset       (0x3FC)
#define GPIO_DIR_Offset        (0x400)
#define GPIO_IBE_Offset        (0x408)
#define GPIO_IEV_Offset        (0x40C)
#define GPIO_IM_Offset         (0x410)
#define GPIO_RIS_Offset        (0x414)
#define GPIO_MIS_Offset        (0x418)
#define GPIO_ICR_Offset        (0x41C)
#define GPIO_AFSEL_Offset      (0x420)
#define GPIO_DR2R_Offset       (0x500)
#define GPIO_DR4R_Offset       (0x504)
#define GPIO_DR8R_Offset       (0x508)
#define GPIO_ODR_Offset        (0x50C)
#define GPIO_PUR_Offset        (0x510)
#define GPIO_PDR_Offset        (0x514)
#define GPIO_SLR_Offset        (0x518)
#define GPIO_DEN_Offset        (0x51C)
#define GPIO_LOCK_Offset       (0x520)
#define GPIO_CR_Offset         (0x524)
#define GPIO_AMSEL_Offset      (0x528)
#define GPIO_PCTL_Offset       (0x52C)
#define GPIO_ADCCTL_Offset     (0x530)
#define GPIO_DMACTL_Offset     (0x534)

/*******************************************************************************
 *                        Local Macros                                         *
 *******************************************************************************/
#define PORT_INITIALIZED    1
#define PORT_UNINITIALIZED  0

#define Unlock_Encoding     0x4C4F434B
static uint8 PORT_STATUS = PORT_UNINITIALIZED ;

/*******************************************************************************
 *                        Functions' Definitions                               *
 *******************************************************************************/
void Port_Init(const struct Port_ConfigType* ConfigPtr);
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);
void Port_RefreshPortDirection(void);
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);
void Port_GetVersionInfo(struct Std_VersionInfoType* versioninfo);


#endif /* PORT_H_ */
