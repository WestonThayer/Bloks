/*************************************************************************
*
* ADOBE CONFIDENTIAL
* 
* Copyright 2017 Adobe
* 
* All Rights Reserved.
*
* NOTICE: Adobe permits you to use, modify, and distribute this file in
* accordance with the terms of the Adobe license agreement accompanying
* it. If you have received this file from a source other than Adobe,
* then your use, modification, or distribution of it requires the prior
* written permission of Adobe.
*
**************************************************************************/

#pragma once

/*******************************************************************************
**
**	Imports
**
**/

#include "AITypes.h"
#include "IAIUUID.h"
#include "IAIUnicodeString.h"	

#include "AIHeaderBegin.h"

/*******************************************************************************
**
** Constants
**
*******************************************************************************/

#define kAIUUIDSuite			"AI UUID Suite"
#define kAIUUIDSuiteVersion		AIAPI_VERSION(3)
#define kAIUUIDVersion			kAIUUIDSuiteVersion

/*******************************************************************************
**
**	Suite
**
********************************************************************************/
/** @ingroup Suites
This suite is in an experimental state, it is not completely production-ready.
These functions allow you to interact with the UUID and associated art
\li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
\c #kAIUUIDSuite and \c #kAIUUIDVersion.
@see \c #ai::uuid */
struct AIUUIDSuite {

	/** Retrieves the art object associated with the UUID, if the art
	is in-scope.
	@param _uuid [in] const reference of UUID of art object.
	@param art [out] A buffer in which to return the output as the valid art object,
	or a null pointer if the art object has been deleted or
	moved out of scope.
	This API may fail to provide the correct ArtHandle, if an object's dictionary is acquired 
	but not released after use. (It is not recommended to acquire and hold the dictionary reference 
	for future use)
	*/
	AIAPI AIErr(*GetArtHandle)(const ai::uuid &_uuid, AIArtHandle &art);

	/** Retrieves the UUID associated with the art.
	@param art [in] The art object.
	@param _uuid [out] Reference variable to return the UUID of the art object.
	*/
	AIAPI AIErr(*GetArtUUID)(AIArtHandle art, ai::uuid &_uuid);
	
	/** Retrieves the UnicodeString representation of the UUID.
	@param _uuid [in] Const reference of the UUID from which UnicodeString need to be created.
	@param uStr [out] Reference variable in which to return the UnicodeString representation
	of UUID.
	*/
	AIAPI AIErr(*UUIDToString) (const ai::uuid &_uuid, ai::UnicodeString &uStr);

	/** Retrieves the UUID object by creating it from the UnicodeString.
	@param uStr [in] UnicodeString from which the UUID needs to be created.
	@param _uuid [out] Reference variable in which to return the UUID object created from the
	UnicodeString.
	*/
	AIAPI AIErr(*StringToUUID) (const ai::UnicodeString &uStr, ai::uuid &_uuid);
    
    /** Generates new unique UUID.
	 *@param _uuid [out] Reference variable in which the new generated uuid object is returned*
	 */
    AIAPI AIErr(*GenerateNewUUID) (ai::uuid &_uuid);
};

#include "AIHeaderEnd.h"
