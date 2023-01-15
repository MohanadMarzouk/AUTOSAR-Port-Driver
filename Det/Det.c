/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Det.c
 *
 * Description: Error development tracer
 *
 * Authors: Mohanad Marzouk
 *
 * AUTOSAR Standard Release: 4.3.1
 *
 *******************************************************************************/

/*******************************************************************************
 *                             Included header files                           *
 *******************************************************************************/
#include "Det/inc/Det.h"

uint16 Det_ModuleId = 0;                //Module ID of calling module.
uint8 Det_InstanceId = 0;               //The identifier of the index based instance of a module
uint8 Det_ApiId = 0;                    //ID of API service in which error is detected
uint8 Det_ErrorId = 0;                  //ID of detected development error

Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId)
{
    Std_ReturnType status;

    Det_ModuleId = ModuleId;
    Det_InstanceId = InstanceId;
    Det_ApiId = ApiId;
    Det_ErrorId = ErrorId;

    status = E_OK;
    return status;
}

