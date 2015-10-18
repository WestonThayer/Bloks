#pragma once
#ifndef _IAI_ARTBOARDS_
#define _IAI_ARTBOARDS_

/*
* Name: IAIArtboards.hpp
* Author: Started by Pushp
* Date: November, 2008
* Purpose: Adobe Illustrator Artboard Interfaces
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 2009 Adobe Systems Incorporated.
* All rights reserved.
*
* NOTICE:  Adobe permits you to use, modify, and distribute this file
* in accordance with the terms of the Adobe license agreement
* accompanying it. If you have received this file from a source other
* than Adobe, then your use, modification, or distribution of it
* requires the prior written permission of Adobe.
*
*/
#include "AITypes.h"
#include "IAIUnicodeString.h"
class CAIArtboardProperties;
class CAIArtboardList;

/** Constant for maximum number of artboard that can be defined. */
#define kAIMAX_ARTBOARD_LIMIT				100
/** @ingroup Errors
	@see ArtboardProperties */
#define kAICantDeleteLastArtboardErr		'CDLC'
/** @ingroup Errors
	@see ArtboardProperties */
#define kAIExceededMaxArtboardLimitErr		'EMxL'
/** @ingroup Errors
	@see ArtboardProperties */
#define kNotFoundErr		'!FND'

#define kActiveArtboard -1

namespace ai
{
	/** Artboard identifier. */
	typedef ai::int32 ArtboardID;
	/** Artboard object. */
	typedef CAIArtboardProperties* ArtboardRef;
	/** Artboard list object. */
	typedef CAIArtboardList* ArtboardListRef;

	/** The \c ArtboardProperties object encapsulates all the attributes associated with
	an artboard. These are not live objects but a snapshot at any given time.
	To update an object, you must call \c ai::ArtboardList::Update.
	*/
	class ArtboardProperties
	{
	public:
		/** Types of artboard display marks and annotations. */
		typedef enum
		{
			kNone = 0,
			kCenter = 1,
			kCrossHair = 1<<1,
			kSafeAreas = 1<<2
		} DisplayMarkType;

		/** Default constructor */
		ArtboardProperties();

		/** Copy Constructor */
		ArtboardProperties(const ArtboardProperties&);

		/** Destructor */
		~ArtboardProperties();
		/** Assignment operator */
		ArtboardProperties& operator=(const ArtboardProperties&);

		/** Checks for a valid object, Invalid objects return an error on
		every operation.
		@return True if this object is valid. */
		bool IsValid() const
		{
			return fImpl != NULL;
		}

		/** Retrieves the position and bounds of this artboard.
		@param value [out] A buffer in which to return the value.
		*/
		AIErr GetPosition(AIRealRect& value) const;

		/** Modifies the position and bounds of this artboard. Call \c ai::ArtboardList::Update()
		with this object to make the change.
		@param value The new position and bounds value.
		*/
		AIErr SetPosition(AIRealRect value);

		/** Retrieves the pixel aspect ratio of the artboard ruler.
		@param value [out] A buffer in which to return the value.
		*/
		AIErr GetPAR(AIReal& value) const;

		/** Modifies the pixel aspect ratio of the artboard ruler. Call \c ai::ArtboardList::Update()
		with this object to make the change in the artboard
		@param value The new value.
		*/
		AIErr SetPAR(AIReal value);

		/** Reports whether a particular type of annotation is shown or hidden.
		@param mark The type of annotation.
		@param show [out] A buffer in which to return true if the mark is shown, false if hidden.
		*/
		AIErr GetShowDisplayMark(DisplayMarkType mark, bool& show) const;

		/** Shows or hides a particular type of annotation.
		@param mark The type of annotation.
		@param show True to show, false to hide.
		*/
		AIErr SetShowDisplayMark(DisplayMarkType mark,bool show);

		/** Retrieves the name associated with this artboard.
		@param name [out] A buffer in which to return the name.
		*/
		AIErr GetName(ai::UnicodeString& name) const;

		/** Sets the name associated with this artboard.
		@param name The new name.
		*/
		AIErr SetName(const ai::UnicodeString& name);

		/** Retrieves the ruler origin of the artboard.	Ruler origin is relative to left-bottom corner of the artboard
		@param rulerOrigin [out] A buffer in which to return the ruler origin.
		*/
		AIErr GetRulerOrigin(AIRealPoint& rulerOrigin) const;

		/** Sets the ruler origin of the artboard. Ruler origin is relative to left-bottom corner of the artboard
		@param rulerOrigin The new ruler origin.
		*/
		AIErr SetRulerOrigin(const AIRealPoint& rulerOrigin);

		/** Reports whether this artboard has an application-generated name.  This affects the file name of the artboard if it is saved
		as part of an export-to-JPEG operation.
		@param isDefault [out] A buffer in which to return true if the name is generated, false if it has been explicitly set.
		*/
		AIErr IsDefaultName(AIBoolean& isDefault) const;

		/** Internal. Do not use. */
		AIErr SetIsDefaultName(const AIBoolean& isDefault);

	public: // internal use public interface
		ArtboardProperties(const ArtboardRef ref);
		void deleteImpl();
	private:
		friend class ArtboardList;
		ArtboardRef fImpl;
	};

	/** The \c ArtboardList object is the interface to the set of artboards associated
	with a document. It encapsulate all artboard operations.
	*/
	class ArtboardList
	{
	public:
		/* Constructs an ArtboardList object for the current document*/
		ArtboardList();

		/** Destructor */
		~ArtboardList();
		/** Checks for a valid object, Invalid objects return an error on
		every operation.
		@return True if this object is valid.
		*/
		bool IsValid() const
		{
			return fImpl != NULL;
		}

		/** Adds a new artboard to the document and reports its index position in this artboard list.
		@param newArtboard The new artboard's properties.
		@param index [out] A buffer in which to return the 0-based index position of the new artboard.
		@return The error \c #kAIExceededMaxArtboardLimitErr if the number of artboards exceeds  \c #kAIMAX_ARTBOARD_LIMIT.
		*/

		AIErr AddNew(ArtboardProperties& newArtboard, ArtboardID& index);

		/** Inserts a new artboard to the document at the specified location.
		@param artboard The new artboard's properties.
		@param index 0-based index position of the new artboard.
		@return The error \c #kAIExceededMaxArtboardLimitErr if the number of artboards exceeds  \c #kAIMAX_ARTBOARD_LIMIT.
		*/

		AIErr Insert(ArtboardProperties& artboard, ArtboardID& index);

		/** Deletes an artboard from the document list, makes the next one in the list active.
		@param index The 0-based index position of the artboard to delete.
		@return The error \c #kAICantDeleteLastArtboardErr if this is the last artboard in the list.
		*/
		AIErr Delete(ArtboardID index);
		/** Retrieves the number of artboards defined in the artboard list.
		@param count [out] A buffer in which to return the number of artboards.
		*/
		AIErr GetCount(ArtboardID& count) const;

		/** Retrieves the properties of an artboard. Use with \c #GetCount() and \c #Update()
		to modify an artboard without changing which artboard is active in the document.
		@param index The 0-based index position of the artboard in the artboard list..
		@return The artboard properties object. On error returns an invalid object.
		*/
		ArtboardProperties GetArtboardProperties(ArtboardID index);

		/** Updates the properties of an artboard. Use with \c #GetCount() and \c #GetArtboardProperties()
		to modify an artboard without changing which artboard is active in the document.
		@param index The 0-based index position of the artboard in the document list.
		@param artboard The object containing the new artboard properties.
		*/
		AIErr Update(ArtboardID index, const ArtboardProperties& artboard);

		/** Retrieves the index position of the active artboard in the document's list.
		@param index [out] A buffer in which to return the 0-based index, or -1 if there are
		no artboards in the current document.
		*/
		AIErr GetActive(ArtboardID& index) const;

		/** Makes a specific artboard active, and makes it current in the iteration order.
		@param index The 0-based index position of the artboard in the document list.
		*/
		AIErr SetActive(ArtboardID index);

	public: // internal use public interface
		ArtboardList(const ArtboardList&);
		ArtboardList& operator=(const ArtboardList&);
		ArtboardList(ArtboardListRef);
		void deleteImpl();

	private:
		ArtboardListRef fImpl;
	};

	/** The \c ArtboardUtils object is a collection of utility functions for common operations.
	*/
	namespace ArtboardUtils
	{
		/** Retrieves the number of artboards defined in the artboard list of the current document.
		@param count [out] A buffer in which to return the number of artboards.
		*/
		inline AIErr GetCount(ArtboardID& count)
		{
			ArtboardList list;
			return list.GetCount(count);
		}
		/** Retrieves the position and bounds of an artboard.
		@param index The 0-based index position of the artboard in the document list.
		@param rect [out] A buffer in which to return the value.
		*/
		inline AIErr GetPosition(ArtboardID index,AIRealRect& rect)
		{
			ArtboardList list;
			ArtboardProperties artboard(list.GetArtboardProperties(index));
			if(!artboard.IsValid()) return kBadParameterErr;
			return artboard.GetPosition(rect);
		}
		/** Retrieves the position and bounds of the currently active artboard.
		@param rect [out] A buffer in which to return the value.
		*/
		inline AIErr GetActiveArtboardPosition(AIRealRect& rect)
		{
			AIErr error = kNoErr;
			ArtboardList list;
			ArtboardID index;
			error = list.GetActive(index);
			GetPosition(index,rect);
			return error;
		}
		/** Retrieves the index of the currently active artboard.
		@param index [out] A buffer in which to return the value.
		*/
		inline AIErr GetActiveArtboardIndex(ArtboardID& index)
		{
			AIErr error = kNoErr;
			ArtboardList list;
			error = list.GetActive(index);
			return error;
		}
		/** Retrieves the name of the specified artboard.
		@param name [out] A buffer in which to return the name.
		@param isDefault [out] True if the name is the default name.
		@param index [in] The 0-based position index of the artboard, or -1 to get the active artboard.
		*/
		AIErr GetArtboardName(ai::UnicodeString& name,bool& isDefault, ArtboardID index = kActiveArtboard);

		/** Retrieves the index of the artboard with specified name
		@param name [in] The name of the Artboard.
		@param index [out] The artboard index .
		*/
		AIErr GetArtboardIndexByName(const ai::UnicodeString& name, ai::ArtboardID& index);
	}
}

#endif //_IAI_ARTBOARDS_