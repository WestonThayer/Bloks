/***********************************************************************/
/*                                                                     */
/* SPRuntmeV6.h                                                          */
/*                                                                     */
/* ADOBE SYSTEMS INCORPORATED                                          */
/* Copyright 1995-2007 Adobe Systems Incorporated.                     */
/* All Rights Reserved.                                                */
/*                                                                     */
/* NOTICE:  Adobe permits you to use, modify, and distribute this file */
/* in accordance with the terms of the Adobe license agreement         */
/* accompanying it. If you have received this file from a source other */
/* than Adobe, then your use, modification, or distribution of it      */
/* requires the prior written permission of Adobe.                     */
/*                                                                     */
/* Patents Pending                                                     */
/*                                                                     */
/*                                                                     */
/***********************************************************************/

#pragma once


/*******************************************************************************
 **
 **    Imports
 **
 **/

#include "SPRuntme.h"

#include "SPHeaderBegin.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    
    /*******************************************************************************
     **
     **    Constants
     **
     **/
    
#define kSPRuntimeSuiteV6                       kSPRuntimeSuite
#define kSPRuntimeSuiteVersion5                 5

    /*******************************************************************************
     **
     **    Types
     **
     **/
    

    /** Callback procedures provided to PICA by the application.
     Plug-ins do not use these, except for adapters, which
     call the initialization and termination procedures.
     @see \c #SPRuntimeSuite::GetRuntimeHostFileSpec() */
    typedef struct SPHostProcsV5 {
        
        void *hostData;
        
        SPAllocateProc extAllocate;
        SPFreeProc extFree;
        SPReallocateProc extReallocate;
        
        SPAllocateProc intAllocate;
        SPFreeProc intFree;
        SPReallocateProc intReallocate;
        /** Plug-in initialization procedure */
        SPStartupNotifyProc startupNotify;
        /** Plug-in termination procedure */
        SPShutdownNotifyProc shutdownNotify;
        
        SPAssertTrapProc assertTrap;
        SPThrowTrapProc throwTrap;
        SPDebugTrapProc debugTrap;
        
        SPAllocateStringPoolProc allocateStringPool;
        SPFreeStringPoolProc freeStringPool;
        SPMakeWStringProc makeWString;
        SPStringPoolRef appStringPool;
        
        SPFilterEventProc filterEvent;
        SPAddPluginsProc overrideAddPlugins;
        SPOverrideStartupProc overridePluginStartup;
        
#ifdef WIN_ENV
        SPResolveLinkProc resolveLink;
#endif
        
        GetNativePluginAccessProc getPluginAccess;
        
#ifdef MAC_ENV
        // enable second-chance plugin loading for success-critical situations
        MemoryIsCriticalProc memoryIsCritical;
#endif
        
        SPAllocateProc extSubAllocate; //alternate allocation mechanism: Suballocation
        SPFreeProc extSubFree;
        SPReallocateProc extSubReallocate;
        
        //Do not insert in the middle as Photoshop Adapter's SPRuntime interface's order will become different
#ifdef WIN_ENV
        SPResolveLinkProcW resolveLinkW;
#endif
        SPWideCharToPlatform wideCharToPlatform;
        SPPlatformToWideChar platformToWideChar;
#if SPPerfLoggingEnabled
        SPPerfLogTimerStart startPerflog;
        SPPerfLogTimerPause pausePerfLogTimer;
        SPPerfLogTimerPlay playPerfLogTimer;
        SPPerfLogPut putPerfLog;
        SPPerfLogPutWithGivenTime putPerfLogWithGivenTime;
        SPGetElapsedMicroSeconds getElapsedMicroSeconds;
        SPPerfLogTimerDestroy clearHostLogData;
#endif
    } SPHostProcsV5;
    
    /*******************************************************************************
     **
     **    Suite
     **
     **/
    /** @ingroup Suites
     This suite allows you to obtain specific references to the
     PICA global lists and string pool.
     
     \li Acquire this suite using \c #SPBasicSuite::AcquireSuite() with the constants
     \c #kSPRuntimeSuite and \c #kSPRuntimeSuiteVersion.
     */
    typedef struct SPRuntimeSuiteV6 {
        /** Retrieves the PICA global string pool.
         @param stringPool [out] A buffer in which to return the string-pool object.
         @see \c #SPStringsSuite
         */
        SPAPI SPErr (*GetRuntimeStringPool)( SPStringPoolRef *stringPool );
        /** Retrieves the PICA global suite list.
         @param suiteList [out] A buffer in which to return the list object.
         @see \c #SPSuitesSuite
         */
        SPAPI SPErr (*GetRuntimeSuiteList)( SPSuiteListRef *suiteList );
        /** Retrieves the PICA global file list.
         @param fileList [out] A buffer in which to return the list object.
         @see \c #SPFilesSuite
         */
        SPAPI SPErr (*GetRuntimeFileList)( SPFileListRef *fileList );
        /** Retrieves the PICA global plug-in list.
         @param pluginList [out] A buffer in which to return the list object.
         @see \c #SPPluginsSuite
         */
        SPAPI SPErr (*GetRuntimePluginList)( SPPluginListRef *pluginList );
        /** Retrieves the PICA global adapter list.
         @param adapterList [out] A buffer in which to return the list object.
         @see \c #SPAdaptersSuite
         */
        SPAPI SPErr (*GetRuntimeAdapterList)( SPAdapterListRef *adapterList );
        /** Retrieves the block of function pointers supplied to PICA by the
         application, which contains memory management routines, notification routines,
         exception handling, and string pool routines.
         
         A plug-in does not normally call the host functions directly; you
         can use the PICA suite functions for most operations. An adapter, however,
         uses the host functions for start-up and shut-down notification.
         @param hostProcs [out] A buffer in which to return a pointer to the
         block of function pointers.
         */
        SPAPI SPErr (*GetRuntimeHostProcs)( SPHostProcsV5 **hostProcs );
        /** Retrieves the location of the application's plug-in folder.
         @param pluginFolder [out] A buffer in which to return the
         file specification for the directory that contains plug-ins.
         */
        SPAPI SPErr (*GetRuntimePluginsFolder)( SPPlatformFileReference *pluginFolder );
        /** Retrieves the location of the application's executable file.
         @param hostFileSpec [out] A buffer in which to return the
         file specification for the application's executable file.
         */
        SPAPI SPErr (*GetRuntimeHostFileRef)( SPPlatformFileReference *hostFileSpec );
    } SPRuntimeSuiteV6;
    
    /** Internal */
    SPAPI SPErr SPGetRuntimeHostProcs_v5(SPHostProcsV5 **hostProcs );
#ifdef __cplusplus
}
#endif

#include "SPHeaderEnd.h"


