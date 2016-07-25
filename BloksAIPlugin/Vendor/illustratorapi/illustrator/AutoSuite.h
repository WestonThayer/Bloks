#ifndef _AUTOSUITE_H_
#define _AUTOSUITE_H_

/*
 *        Name:	AutoSuite.h
 *     Purpose:	
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2005-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */

#include	"SPBasic.h"
#include	"AITypes.h"


namespace ai {
// start of namespace ai

//--------------------------------------------------------------------------------
// The AutoSuite class together with the template SuitePtr class provides
// automatic acquisition and releasing of suite pointers. To use these classes
// a plugin must do the following:
//
// 1. declare the following globals somewhere, they provide the head of the
// 		list of suites acquired and a pointer to the SPBasicSuite needed to
//		acquire suites.
//		ai::AutoSuite* ai::AutoSuite::sHead;
//		SPBasicSuite* ai::AutoSuite::sSPBasic;
//
// 2. call ai::AutoSuite::Load(message->d.basic) on Startup and Reload. This
//		supplies the SPBasicSuite which is needed to acquire additional suites.
//
// 3. call ai::AutoSuite::Unload() on Unload and Shutdown. This releases all
//		suites the plugin has acquired.
//
// To declare and use an auto suite pointer in a particular source file write
// code such as that which follows. If a suite cannot be acquired an exception
// will be thrown.
//
//	#include "AutoSuite.h"
//	#include "AIArt.h"
//
//	use_suite(AIArt)
//
//	int myPathMaker (AIArtHandle* path)
//	{
//		sAIArt->NewArt(kPathArt, kPlaceAboveAll, 0, path);
//	}
//
// The following code fragment illustrates the use of a SuiteContext. The
// constructor of the context remembers which suites were acquired at that
// time. Its destructor releases all suites acquired since it was constructed.
// The overhead for doing this is trivial.
//
//	int myFunction ()
//	{
//		ai::SuiteContext mycontext;
//		... lots of code ...
//	}
//--------------------------------------------------------------------------------

class AutoSuite {
	friend class SuiteContext;
public:
	// initialize AutoSuite mechanism on startup or reload specifying the
	// address of the SPBasicSuite
	static void Load (SPBasicSuite* basic)
		{
			sSPBasic = basic;
			sHead = 0;
		}
	// on unload or shutdown releases all suites
	static void Unload (AutoSuite* contextHead = 0)
		{
			while (sHead != contextHead)
			{
				sHead->Release();
				sHead = sHead->fNext;
			}
		}

	// the constructor initializes the pointer to the next suite in
	// the list of suites allocated and the pointer to the suite itself.
	AutoSuite () : fNext(0), fSuite(0)
		{}

	// acquire the suite pointer
	const void* Acquire ()
		{
			if (!fSuite)
			{
				SPErr error = sSPBasic->AcquireSuite(Name(), Version(), &fSuite);
				if (error)
					throw ai::Error(error);
				Push(this);
			} 
			return fSuite;
		}
	
	// release the suite pointer
	void Release ()
		{
			if (fSuite)
				sSPBasic->ReleaseSuite(Name(), Version());
			fSuite = 0;
		}

	// does the suite exist?
	AIBoolean SuiteExists ()
		{
			try
			{
				Acquire();
			}
			catch (ai::Error&)
			{
			}
			return fSuite != 0;
		}

protected:
	// globals needed by the mechanism
	static SPBasicSuite* sSPBasic;
	static AutoSuite* sHead;

	// adds the suite to the list of those acquired
	static void Push (AutoSuite* suite)
		{suite->fNext = sHead; sHead = suite;}

	// subclass must define the suite name and version
	virtual const char* Name () = 0;
	virtual ai::int32 Version () = 0;

	virtual ~AutoSuite() {} ;
	AutoSuite(const AutoSuite&);
	AutoSuite & operator =(const AutoSuite&);
	
	AutoSuite* fNext;		// pointer to next suite in chain
	const void* fSuite;			// the suite pointer itself
};


// a SuiteContext can be used to ensure that all suites acquired within the
// context are released on exit
class SuiteContext {
public:
	SuiteContext () : fHead(AutoSuite::sHead)
		{}
	~SuiteContext ()
		{
			AutoSuite::Unload(fHead);
		}

private:
	SuiteContext(const SuiteContext&);
	SuiteContext& operator =(const SuiteContext&);
	AutoSuite* fHead;
};


template <class suite> class SuitePtr : public AutoSuite {
protected:
	const char* Name () {return suite::name();}
	ai::int32 Version () {return suite::version;}
};

// an actual smart suite pointer
template <class suite> class Suite {
public:
	bool operator !()
	{
		return !Exists();	
	}

	AIBoolean Exists ()
		{return Ptr().SuiteExists();}

	const typename suite::methods* operator-> ()
		{return static_cast<const typename suite::methods*>(Ptr().Acquire());}

private:
	SuitePtr<suite>& Ptr ()
		{static SuitePtr<suite> sSuitePtr; return sSuitePtr;}
};


// end of namespace ai
}


//--------------------------------------------------------------------------------
// the following macros are used to declare a non-ADM suite pointer.
//--------------------------------------------------------------------------------

#define declare_suite(suite) \
	namespace ai { \
		class S##suite { \
		public: \
			typedef suite##Suite methods; \
			enum {version = k##suite##SuiteVersion}; \
			static const char* name () {return k##suite##Suite;}; \
		}; \
	}
#define define_suite(suite) static ai::Suite<ai::S##suite> s##suite;
#define use_suite(suite) declare_suite(suite) define_suite(suite)

#define extern_declare_suite(suite) declare_suite(suite) extern ai::Suite<ai::S##suite> s##suite;
#define extern_define_suite(suite) ai::Suite<ai::S##suite> s##suite;

//--------------------------------------------------------------------------------
// the following macros are used to declare an ADM suite pointer. the suite
// version is needed in addition to its name.
//--------------------------------------------------------------------------------

#define declare_adm_suite(suite, vers) \
	namespace ai { \
		class S##suite##vers { \
		public: \
			typedef suite##Suite##vers methods; \
			enum {version = k##suite##SuiteVersion##vers}; \
			static const char* name () {return k##suite##Suite;}; \
		}; \
	}
#define define_adm_suite(suite, vers) static ai::Suite<ai::S##suite##vers> s##suite;
#define use_adm_suite(suite, vers) declare_adm_suite(suite, vers) define_adm_suite(suite, vers)
#define extern_declare_adm_suite(suite, vers) declare_adm_suite(suite, vers) extern ai::Suite<ai::S##suite##vers> s##suite;
#define extern_define_adm_suite(suite, vers) ai::Suite<ai::S##suite##vers> s##suite;


#endif
