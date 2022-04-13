#include "IllustratorSDK.h"
#include "BloksAIPluginSuites.h"

// Suite externs
extern "C"
{
	SPBlocksSuite* sSPBlocks = NULL;
	AIUnicodeStringSuite* sAIUnicodeString = NULL;
	AIStringFormatUtilsSuite* sAIStringFormatUtils = NULL;
}

// Import suites
ImportSuite gImportSuites[] =
{
	kSPBlocksSuite, kSPBlocksSuiteVersion, &sSPBlocks,
	kAIUnicodeStringSuite, kAIUnicodeStringVersion, &sAIUnicodeString,
	kAIStringFormatUtilsSuite, kAIStringFormatUtilsSuiteVersion, &sAIStringFormatUtils,
	nullptr, 0, nullptr
};
