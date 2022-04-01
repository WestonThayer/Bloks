/*************************************************************************
 *
 * ADOBE CONFIDENTIAL
 *
 * Copyright 2020 Adobe
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

#include "IAIAutoBuffer.h"
#include "IAIUnicodeString.h"

#include "AIHeaderBegin.h"

#define kAICloudDocumentSuite                  "AI Cloud Document Suite"
#define kAICloudDocumentSuiteVersion           AIAPI_VERSION(1)
#define kAICloudDocumentVersion                kAICloudDocumentSuiteVersion


typedef struct _t_AICloudRecentsBookmark* AICloudRecentsBookmarkHandle;


struct AICloudDocumentSuite
{
    /** Saves the currently open document to cloud.
            @param cloudPath The relative path to save the document.
                             Could simply be the name of the document.
        */
    AIAPI AIErr (*SaveToCloud) ( const ai::UnicodeString& cloudPath );
    
    /** Saves the currently open cloud document if it is dirty, to its existing location.*/
    AIAPI AIErr (*SaveCurrentDocument) ();
    
    /** Opens a cloud document present at the specified path.
            @param cloudAssetRef The path of the cloud document to be opened.
            @param outDocument [out] A buffer in which to return the document reference.
        */
    AIAPI AIErr (*OpenCloudDocument) ( const ai::UnicodeString& cloudAssetRef, AIDocumentHandle& outDocument );
    
    /** Deletes the cloud document present at the specified path.
            @param cloudAssetRef The path of the cloud document to be deleted.
        */
    AIAPI AIErr (*DeleteCloudDocument) ( const ai::UnicodeString& cloudAssetRef );
    
    /** Gets the path to the currently open cloud document.
            @param cloudAssetRef [out] The buffer in which to return the cloud path.
        */
    AIAPI AIErr (*GetCloudDocumentAssetRef) ( ai::UnicodeString& cloudAssetRef );
    
    /** Gets the cloud paths to the n most recently saved cloud documents.
            @param numRecentDocuments The number of recent documents for which the cloud path is to be fetched.
                   Not more than 100 recent documents could be fetched at a time.
            @param cloudAssetRefs [out] The list of the requested cloud paths.
            @param queryBookmark [out] Reference to the data that is to be preserved and passed in the call to GetNextNRecentCloudDocuments.
        */
    AIAPI AIErr (*GetFirstNRecentCloudDocuments) ( ai::uint32 numRecentDocuments, ai::AutoBuffer<ai::UnicodeString>& cloudAssetRefs, AICloudRecentsBookmarkHandle& queryBookmark );
    
    /** Gets the cloud paths to the next n recently saved cloud documents when the API GetFirstNRecentCloudDocuments has been called once.
        This API could be used in an iterative fashion to access the next n recent documents.
            @param numRecentDocuments The number of recent documents for which the cloud path is to be fetched.
            @param cloudAssetRefs [out] The list of the requested cloud paths.
                   Not more than 100 recent documents could be fetched at a time.
            @param queryBookmarkIn Reference to the data that was fetched from the call to GetFirstNRecentCloudDocuments
                   or from the previous call to GetNextNRecentCloudDocuments.
            @param queryBookmarkOut [out] Reference to the data that is to be preserved for the next call to GetNextNRecentCloudDocuments.

        Example:

        ai::AutoBuffer<ai::UnicodeString> recentDocRefs;
        AICloudRecentsBookmarkHandle reqHandleIn = nullptr, reqHandleOut = nullptr;
     
        //Here we are fetching 10 recent documents, but we can fetch any number less than 100
        error = sAICloudDocument->GetFirstNRecentCloudDocuments(10, recentDocRefs, reqHandleOut);

        //Get next set of recent documents
        while(reqHandleOut)
        {
            reqHandleIn = reqHandleOut;
            error = sAICloudDocument->GetNextNRecentCloudDocuments(10, recentDocRefs, reqHandleIn, reqHandleOut);
            //Always dispose the AICloudRecentsBookmarkHandle after it has been used
            sAICloudDocument->DisposeRecentBookmarkHandle(reqHandleIn);

            //Work with the recent document refs
        }
        */
    AIAPI AIErr (*GetNextNRecentCloudDocuments) ( ai::uint32 numRecentDocuments, ai::AutoBuffer<ai::UnicodeString>& cloudAssetRefs, AICloudRecentsBookmarkHandle queryBookmarkIn, AICloudRecentsBookmarkHandle& queryBookmarkOut );
    
    /** Disposes the bookmark handle that was fetched from the call to GetCloudDocumentAssetRef or GetFirstNRecentCloudDocuments.
        Should be called when no more recent documents are to be fetched by the user.
            @param queryBookmark Reference to the data that was fetched from GetCloudDocumentAssetRef or GetFirstNRecentCloudDocuments
                   and is to be disposed.
        */
    AIAPI AIErr (*DisposeRecentBookmarkHandle) (AICloudRecentsBookmarkHandle queryBookmark);

};

#include "AIHeaderEnd.h"
