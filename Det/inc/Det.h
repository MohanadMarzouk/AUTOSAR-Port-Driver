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

#ifndef DET_H_
#define DET_H_

/*******************************************************************************
 *                             Included header files                           *
 *******************************************************************************/
#include "Common/Std_Types.h"

//*****************************************************************************
//
//  Functions' Prototypes
//
//*****************************************************************************

Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);


#endif /* DET_H_ */
