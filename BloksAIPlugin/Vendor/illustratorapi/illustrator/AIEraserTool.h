//========================================================================================
//
//  ADOBE CONFIDENTIAL
//
//  File: AIEraserTool.h
//
//  Copyright 2016 Adobe Systems Incorporated
//  All Rights Reserved.
//
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//
//========================================================================================

#ifndef __AIEraserTool__
#define __AIEraserTool__

#include "AITypes.h"

#include "AIHeaderBegin.h"

/*******************************************************************************
 **
 ** Constants
 **
 **/

#define kAIEraserToolSuite					"AI Eraser Tool Suite"
#define kAIEraserToolSuiteVersion2			AIAPI_VERSION(2)
#define kAIEraserToolSuiteVersion			kAIEraserToolSuiteVersion2
#define kAIEraserToolVersion				kAIEraserToolSuiteVersion

struct AIEraserToolSuite
{
    /*Erases the art under the given panPoints like an eraser  */
    AIErr (*Erase)(const AIRealPoint* panPoints, const size_t count);
    /* Sets the diameter for the eraser based on the value provided. */
    AIErr (*SetDiameter)(const AIReal diameter);
};

#include "AIHeaderEnd.h"

#endif	// __AIEraserTool__
