/*************************************************************************
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 * Copyright 2005 Adobe
 * All Rights Reserved.
 *
 * NOTICE: All information contained herein is, and remains
 * the property of Adobe and its suppliers, if any. The intellectual
 * and technical concepts contained herein are proprietary to Adobe
 * and its suppliers and are protected by all applicable intellectual
 * property laws, including trade secret and copyright laws.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Adobe.
 **************************************************************************/

#pragma once
#include    "SPBasic.h"
#include    "AITypes.h"

#ifdef STATIC_LINKED_PLUGIN
#include <string>
#include <set>
#endif

#ifndef NDEBUG
#define AUTO_SUITE_LOG_DEBUG(...) \
{ \
fprintf(__VA_ARGS__); \
}
#else
#define AUTO_SUITE_LOG_DEBUG(...)
#endif

namespace ai {
// start of namespace ai

//--------------------------------------------------------------------------------
// The AutoSuite class together with the template SuitePtr class provides
// automatic acquisition and releasing of suite pointers. To use these classes
// a plugin must do the following:
//
// 1. declare the following globals somewhere, they provide the head of the
//         list of suites acquired and a pointer to the SPBasicSuite needed to
//        acquire suites.
//        SPBasicSuite* ai::AutoSuite::sSPBasic;
//		  
//		  ai::AutoSuite* & ai::AutoSuite::GetHead()
//		  {
//		 	 static ai::AutoSuite* headPtr = nullptr;
//		  	 return headPtr;
//		  }
//
// 2. call ai::AutoSuite::Load(message->d.basic) on Startup and Reload. This
//        supplies the SPBasicSuite which is needed to acquire additional suites.
//
// 3. call ai::AutoSuite::LoadRequired(message->d.basic) on Startup and Reload.
//    This supplies the SPBasicSuite which is needed to acquire additional suites.
//    It will return kNoErr if all required suites are acquired or it will return
//	  kSPSuiteNotFoundError if any of the required suite is not acquired.
//
// 4. call ai::AutoSuite::Unload() on Unload and Shutdown. This releases all
//        suites the plugin has acquired.
//
// To declare and use an optional auto suite pointer in a particular source file
// write code such as that which follows. This suite will be acquired only when
// its being used in the code flow. If a suite cannot be acquired an exception
// will be thrown.
//
//    #include "AutoSuite.h"
//    #include "AIArt.h"
//
//    use_suite_optional(AIArt)
//
//    int myPathMaker (AIArtHandle* path)
//    {
//      if(sAIArt)     // "if check" for checking that suite can be acquired
//		{
//			sAIArt->NewArt(kPathArt, kPlaceAboveAll, 0, path); // if it used wihout "if check", it will throw an exeption if the suite cannot be acquired
//		}
//    }
//
//
// To declare and use a required auto suite pointer in a particular source file
//	write code such as that which follows. All the required suites are acquired
//	when LoadRequired() is called (at plugin start). If a suite cannot be 
//	acquired then plugin will fail to start.
//
//
//    #include "AutoSuite.h"
//    #include "AIArt.h"
//
//    use_suite_required(AIArt)
//
//    int myPathMaker (AIArtHandle* path)
//    {
//        sAIArt->NewArt(kPathArt, kPlaceAboveAll, 0, path);
//    }
//
// The following code fragment illustrates the use of a SuiteContext. The
// constructor of the context remembers which suites were acquired at that
// time. Its destructor releases all suites acquired since it was constructed.
// The overhead for doing this is trivial.
//
//    int myFunction ()
//    {
//        ai::SuiteContext mycontext;
//        ... lots of code ...
//    }
//--------------------------------------------------------------------------------

class AutoSuite {
	friend class SuiteContext;
public:

	AutoSuite(const char* name, ai::int32 version, AIBool8 required) :
		fName(name), fVersion(version), fRequired(required)
	{
		if (fRequired)
			Push(this);
	}

	// initialize AutoSuite mechanism on startup or reload specifying the
	// address of the SPBasicSuite
	static void Load(SPBasicSuite* basic)
	{
		sSPBasic = basic;
	}
	
	// initialize AutoSuite mechanism on startup or reload specifying the
	// address of the SPBasicSuite and acquire the required suites
	static AIErr LoadRequired(SPBasicSuite* basic)
	{
#ifndef STATIC_LINKED_PLUGIN
		Load(basic);
		AutoSuite* node = GetHead();
		while (node)
		{
			if (node->fRequired)
			{ 
				if (!node->SuiteExists())
				{
					ReleaseRequired(node);
					return kSPSuiteNotFoundError;
				}
			}
			node = node->fNext;
		}
#endif
		return kNoErr;
	}

#ifdef STATIC_LINKED_PLUGIN
	static AIErr LoadRequiredStatic(SPBasicSuite* basic, const std::set<std::string>& allowlist={})
	{
		Load(basic);
		AutoSuite* node = GetHead();
		while (node)
		{
			if (node->fRequired)
			{ 
				if (!node->SuiteExists())
				{
					if (auto it = allowlist.find(node->fName) == allowlist.end())
					{
						AUTO_SUITE_LOG_DEBUG(stderr, "\t Suite %s is required, but absent from allowlist.\n", node->fName);
						ReleaseRequired(node);
						return kSPSuiteNotFoundError;
					}
					else
					{
						AUTO_SUITE_LOG_DEBUG(stderr, "\t Suite %s is required and in allowlist.\n", node->fName);
					}
				}
			}
			node = node->fNext;
		}
		return kNoErr;
	}
#endif

	// on unload or shutdown releases all suites
	static void Unload(AutoSuite* contextHead = nullptr)
	{
		AutoSuite* &headPtr = GetHead();
		while (headPtr != contextHead)
		{
			headPtr->Release();
			headPtr = headPtr->fNext;
		}
	}

	// acquire the suite pointer
	const void* Acquire()
	{
		if (!fSuite && sSPBasic)
		{
			SPErr error = sSPBasic->AcquireSuite(Name(), Version(), &fSuite);
			if (error)
				throw ai::Error(error);
			if (!fRequired)
				Push(this);
		}
		return fSuite;
	}

	// acquire the suite pointer // no throw
	const void* AcquireNoExept() AINOEXCEPT
	{
		if (!fSuite && sSPBasic)
		{
			SPErr error = sSPBasic->AcquireSuite(Name(), Version(), &fSuite);
			if (error)
				fSuite = nullptr;
			else if (!fRequired)
				Push(this);
		}
		return fSuite;
	}

	// release the suite pointer
	void Release()
	{
		if (fSuite && sSPBasic)
		{
			sSPBasic->ReleaseSuite(Name(), Version());
			fSuite = nullptr;
		}
	}

	// does the suite exist?
	AIBool8 SuiteExists()
	{
		AcquireNoExept();
		return fSuite != nullptr;
	}

private:
	// globals needed by the mechanism
	static SPBasicSuite* sSPBasic;

	// returns the Head pointer to suite list
	static AutoSuite* &GetHead();

	// adds the suite to the list of those acquired
	static void Push(AutoSuite* suite)
	{
		AutoSuite* &headPtr = GetHead();
		suite->fNext = headPtr;
		headPtr = suite;
	}

	// Used to release acquired suites if the Load Fails
	// its similar to Unload but does no modify the orignal Head Pointer
	static void ReleaseRequired(AutoSuite* contextHead = nullptr)
	{
		AutoSuite* headPtr = GetHead();
		while (headPtr != contextHead)
		{
			if(headPtr->fRequired)
				headPtr->Release();

			headPtr = headPtr->fNext;
		}
	}

	// subclass must define the suite name and version
	const char* Name() const { return fName; }
	ai::int32 Version() const { return fVersion; }

	AutoSuite(const AutoSuite&);
	AutoSuite & operator =(const AutoSuite&);

	AutoSuite* fNext = nullptr;        // pointer to next suite in chain
	const void* fSuite = nullptr;            // the suite pointer itself
	const char* fName = nullptr;
	const ai::int32 fVersion = 0;
	AIBool8 fRequired = false;
};



// a SuiteContext can be used to ensure that all suites acquired within the
// context are released on exit
class SuiteContext {
public:
	SuiteContext() : fHead(AutoSuite::GetHead()) {}
	~SuiteContext() { AutoSuite::Unload(fHead); }

private:
	SuiteContext(const SuiteContext&);
	SuiteContext& operator =(const SuiteContext&);
	AutoSuite* fHead;
};


// an actual smart suite pointer
template <class suite, AIBool8 required = false> class Suite {
public:
	Suite()
	{
		Ptr();
	}

	bool operator !() { return !Exists(); }

	operator bool() { return (Exists() != false); }

	AIBoolean Exists() AINOEXCEPT
	{ 
		return Ptr().SuiteExists(); 
	} 

	const typename suite::methods* operator-> ()
	{
		return static_cast<const typename suite::methods*>(Ptr().Acquire());
	}

private:
	AutoSuite& Ptr()
	{
		static AutoSuite sSuitePtr(suite::name(), suite::version, required);
		return sSuitePtr;
	}
};

#ifdef AI_HAS_NULLPTR
template <class suite, AIBool8 required>
inline bool operator==(Suite<suite,required> suitePtr, std::nullptr_t)
{
	return !suitePtr;
}

template <class suite,AIBool8 required>
inline bool operator==(std::nullptr_t, Suite<suite,required> suitePtr)
{
	return (suitePtr == nullptr);
}

template <class suite,AIBool8 required>
inline bool operator!=(Suite<suite, required> suitePtr, std::nullptr_t)
{
	return !(suitePtr == nullptr);
}

template <class suite, AIBool8 required>
inline bool operator!=(std::nullptr_t, Suite<suite, required> suitePtr)
{
	return (suitePtr != nullptr);
}
#endif // AI_HAS_NULLPTR

// end of namespace ai
}


//--------------------------------------------------------------------------------
// the following macros are used to declare a non-ADM suite pointer.
//--------------------------------------------------------------------------------

#ifdef STATIC_LINKED_PLUGIN
	#define suite_namespace_name		PLUGIN_PROJECT_NAME
	#define plugin_namespace_begin 		namespace PLUGIN_PROJECT_NAME { 
	#define plugin_namespace_end   		} 
	#define plugin_namespace_use(x)		using PLUGIN_PROJECT_NAME::x
#else
	#define suite_namespace_name	ai
	#define plugin_namespace_begin 
	#define plugin_namespace_end
	#define plugin_namespace_use(x)
#endif

#define declare_suite(suite) \
	namespace suite_namespace_name { \
		class S##suite { \
		public: \
			typedef suite##Suite methods; \
			enum {version = k##suite##SuiteVersion}; \
			static const char* name () {return k##suite##Suite;}; \
		}; \
	}
#define define_suite(suite) static ai::Suite<suite_namespace_name::S##suite,false> s##suite;
#define use_suite(suite) declare_suite(suite) define_suite(suite)

#define use_suite_optional(suite) use_suite(suite)

#define define_suite_required(suite) static ai::Suite<suite_namespace_name::S##suite,true> s##suite;
#define use_suite_required(suite) declare_suite(suite) define_suite_required(suite)

#define extern_declare_suite(suite) declare_suite(suite) \
	plugin_namespace_begin \
		extern ai::Suite<suite_namespace_name::S##suite> s##suite; \
	plugin_namespace_end \
	plugin_namespace_use(s##suite);

#define extern_define_suite(suite) \
	plugin_namespace_begin \
		ai::Suite<suite_namespace_name::S##suite,false> s##suite; \
	plugin_namespace_end \
	plugin_namespace_use(s##suite);

#define extern_declare_suite_optional(suite) extern_declare_suite(suite)
#define extern_define_suite_optional(suite) extern_define_suite(suite)

#define extern_declare_suite_required(suite) declare_suite(suite) \
	plugin_namespace_begin \
		extern ai::Suite<suite_namespace_name::S##suite, true> s##suite; \
	plugin_namespace_end \
	plugin_namespace_use(s##suite);

#define extern_define_suite_required(suite) \
	plugin_namespace_begin \
		ai::Suite<suite_namespace_name::S##suite,true> s##suite; \
	plugin_namespace_end \
	plugin_namespace_use(s##suite);


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

