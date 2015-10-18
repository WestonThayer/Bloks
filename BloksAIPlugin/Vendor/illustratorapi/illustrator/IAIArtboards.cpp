/*
* Name: IAIArtboards.hpp
* Author: Started by Pushp
* Date: November, 2008
* Purpose: Adobe Illustrator Artboard Suite Wraper implementation
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 2008 Adobe Systems Incorporated.
* All rights reserved.
*
* NOTICE:  Adobe permits you to use, modify, and distribute this file
* in accordance with the terms of the Adobe license agreement
* accompanying it. If you have received this file from a source other
* than Adobe, then your use, modification, or distribution of it
* requires the prior written permission of Adobe.
*
*/

#include "AIArtboard.h"
#include <algorithm>


#ifdef _IAIARTBOARD_SUITE_INCLUDE_H_
#include _IAIARTBOARD_SUITE_INCLUDE_H_
#else
#ifndef _IAIARTBOARD_SUITE_USE_C_LINKAGE_
#define _IAIARTBOARD_SUITE_USE_C_LINKAGE_ 1
#endif
#if _IAIARTBOARD_SUITE_USE_C_LINKAGE_
extern "C"
{
#endif
	/** The plug-in using the ai::ArtboardProperties class is required to provide
	these global suite pointers.  These pointers must be valid prior
	to any call to ai::ArtboardProperties methods.
	*/
	extern AIArtboardSuite* sAIArtboard;

#if _IAIARTBOARD_SUITE_USE_C_LINKAGE_
}
#endif // _IAIARTBOARD_SUITE_USE_C_LINKAGE_

#endif

namespace ai
{
	ArtboardProperties::~ArtboardProperties()
	{
		sAIArtboard->Dispose(*this);	
	}
	ArtboardProperties::ArtboardProperties():fImpl(0)
	{
		sAIArtboard->Init(*this);
	}
	ArtboardProperties::ArtboardProperties(ArtboardRef /*ref*/):fImpl(0)
	{
	}
	ArtboardProperties::ArtboardProperties(const ArtboardProperties& artboard):fImpl(0)
	{
		sAIArtboard->CloneArtboard(*this,artboard);		
	}
	ArtboardProperties& ArtboardProperties::operator=(const ArtboardProperties& object)
	{
		ArtboardProperties temp(object);
		std::swap(this->fImpl,temp.fImpl);
		return *this;
	}
	AIErr ArtboardProperties::GetPosition(AIRealRect& rect) const 
	{
		return sAIArtboard->GetPosition(*this,rect);
	}
	AIErr ArtboardProperties::SetPosition(AIRealRect rect)
	{
		return sAIArtboard->SetPosition(*this,rect);
	}
	AIErr ArtboardProperties::GetName(ai::UnicodeString& name) const
	{
		return sAIArtboard->GetName(*this,name);
	}
	AIErr ArtboardProperties::SetName(const ai::UnicodeString& name)
	{
		return sAIArtboard->SetName(*this,name);
	}
	AIErr ArtboardProperties::IsDefaultName(AIBoolean& isDefault) const
	{
		return sAIArtboard->IsDefaultName(*this, isDefault);
	}
	AIErr ArtboardProperties::SetIsDefaultName(const AIBoolean& isDefault)
	{
		return sAIArtboard->SetIsDefaultName(*this,isDefault);
	}
	AIErr ArtboardProperties::GetPAR(AIReal& par) const
	{
		return sAIArtboard->GetPAR(*this,par);
	}
	AIErr ArtboardProperties::SetPAR(AIReal par)
	{
		return sAIArtboard->SetPAR(*this,par);
	}
	AIErr ArtboardProperties::GetRulerOrigin(AIRealPoint& rulerOrigin) const 
	{
		return sAIArtboard->GetRulerOrigin(*this,rulerOrigin);
	}
	AIErr ArtboardProperties::SetRulerOrigin(const AIRealPoint& rulerOrigin)
	{
		return sAIArtboard->SetRulerOrigin(*this,rulerOrigin);
	}
	AIErr ArtboardProperties::GetShowDisplayMark(DisplayMarkType type,bool& show) const
	{
		AIBoolean temp = show;
		AIErr error =  sAIArtboard->GetShowDisplayMark(*this,type,temp);
		if(kNoErr != error) return error;
		show = !!temp;
		return error;
	}
	AIErr ArtboardProperties::SetShowDisplayMark(DisplayMarkType type,bool show)
	{
		return sAIArtboard->SetShowDisplayMark(*this,type,show);
	}
	ArtboardList::ArtboardList():fImpl(0)
	{
		sAIArtboard->GetArtboardList(*this);
	}


	ArtboardList::~ArtboardList()
	{
		if(fImpl)
			sAIArtboard->ReleaseArtboardList(*this);
	}

	AIErr ArtboardList::AddNew(ArtboardProperties& newArtboard, ArtboardID& index)
	{
		return sAIArtboard->AddNew(*this,newArtboard,index);
	}

	AIErr ArtboardList::Insert(ArtboardProperties& artboard, ArtboardID& index)
	{
		return sAIArtboard->Insert(*this,artboard,index);
	}

	AIErr ArtboardList::Delete(ArtboardID index)
	{
		return sAIArtboard->Delete(*this,index);
	}
	AIErr ArtboardList::GetCount(ArtboardID&index) const
	{
		return sAIArtboard->GetCount(*this,index);
	}
	ArtboardProperties ArtboardList::GetArtboardProperties(ArtboardID index)
	{
		ArtboardProperties object(NULL);
		sAIArtboard->GetArtboardProperties(*this,index,object);
		return object;
	}
	AIErr ArtboardList::GetActive(ArtboardID& index) const
	{
		return sAIArtboard->GetActive(*this,index);
	}
	AIErr ArtboardList::SetActive(ArtboardID index)
	{
		return sAIArtboard->SetActive(*this,index);
	}
	AIErr ArtboardList::Update(ArtboardID index, const ArtboardProperties& artboard)
	{
		return sAIArtboard->Update(*this,index,artboard);
	}
	
	namespace ArtboardUtils
	{
		/** Retrieves the name of the specified artboard. if the index is -1 it gets the name of the active artboard
		@param name [out] A buffer in which to return the name.
		@param isDefault [out] A bool which indicates if the name is default or not.
		@param index [in] The artboard index (-1 if active artboard).
		*/
		AIErr GetArtboardName(ai::UnicodeString& name,bool& isDefault, ArtboardID index )
		{
			AIErr error = kNoErr;
			isDefault = false;
			ArtboardList list;
			if(index == kActiveArtboard)
				error = list.GetActive(index);
			ArtboardProperties artboardProps(list.GetArtboardProperties(index));
			artboardProps.GetName(name);
			AIBoolean isDefaultName = FALSE;
			artboardProps.IsDefaultName(isDefaultName);
			if(name.empty())
			{
				isDefaultName=TRUE;
				const char* abString = "$$$/Artboards/Name/Str=Artboard";
				name = ai::UnicodeString(ZREF(abString));
				char artboardnum[4];
				::sprintf(artboardnum,"%d",index+1);
				name.append(ai::UnicodeString(" "));
				name.append(ai::UnicodeString(artboardnum));
				artboardProps.SetName(name);
				artboardProps.SetIsDefaultName(TRUE);
			}
			isDefault = (isDefaultName == 1);

			return error;
		}
		
		/** Retrieves the index of the artboard with specified name
		@param name [in] The name of the Artboard.
		@param index [out] The artboard index .
		*/
		AIErr GetArtboardIndexByName(const ai::UnicodeString& name, ai::ArtboardID& index)
		{
			AIErr error = kNoErr;
			ArtboardList abList;
			ai::int32 abCount=0;
			error = abList.GetCount(abCount);
			if(error != kNoErr)
				return error;
			ai::UnicodeString abName("");
			ai::ArtboardProperties artboardProps;
			for(index=0;index<abCount;index++)
			{
				artboardProps = abList.GetArtboardProperties(index);
				error = artboardProps.GetName(abName);
				if(error != kNoErr)
					return error;
				if(abName == name)
					return kNoErr;
			}
			return kNotFoundErr;
		}
	}

}

