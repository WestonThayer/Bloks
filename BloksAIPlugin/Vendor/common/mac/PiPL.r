//========================================================================================
//  
//  $File$
//
//  $Revision$
//
//  Copyright 1987 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#ifndef __PIPL_r__		// Only include this once.
#define __PIPL_r__


//-------------------------------------------------------------------------------
//	Definitions -- Version and include information
//-------------------------------------------------------------------------------

// Version of Plug In Properties Template described in this file:
#ifndef kPIPropertiesVersion
	#define kPIPropertiesVersion 0
#endif 

//-------------------------------------------------------------------------------
//	PiPL resource template
//-------------------------------------------------------------------------------

type 'PiPL'
	{
	longint = kPIPropertiesVersion;
	longint = $$CountOf(properties);
	array properties
		{
		switch
			{
			//-------------------------------------------------------------------
			// Illustrator/SweetPea PiPL properties
			//-------------------------------------------------------------------

			case ADBEKind:
				longint = 'ADBE';		// SweetPea/Illustrator host.
				key longint = 'kind';
				longint = 0;			// Index.
				longint = 4;			// Length.
				literal longint PIPiPLTypes;	// Version.
				
			case InterfaceVersion:
				longint = 'ADBE';		// SweetPea/Illustrator host.
				key longint = 'ivrs';
				longint = 0;			// Index.
				longint = 4;			// Length.
				longint;				// Version.
				
			case ADBECodeCarbon:
				longint = 'ADBE';
				key longint = 'ppcb';
				longint = 0;
				#if DeRez
					fill long;
				#else
					longint = (ADBEppcbEnd[$$ArrayIndex(properties)] - ADBEppcbStart[$$ArrayIndex(properties)]) / 8;
				#endif
			  ADBEppcbStart:
				longint;
				longint;
				pstring;
			  ADBEppcbEnd:
				align long;

			case ADBECodeMachO:
				longint = 'ADBE';
				key longint = 'mach';
				longint = 0;
				#if DeRez
					fill long;
				#else
					longint = (ADBEmachEnd[$$ArrayIndex(properties)] - ADBEmachStart[$$ArrayIndex(properties)]) / 8;
				#endif
			  ADBEmachStart:
				pstring;
			  ADBEmachEnd:
				align long;
			
			case ADBECodeMacIntel32:
				longint = 'ADBE';
				key longint = 'mi32';
				longint = 0;
				#if DeRez
					fill long;
				#else
					longint = (ADBEmi32End[$$ArrayIndex(properties)] - ADBEmi32Start[$$ArrayIndex(properties)]) / 8;
				#endif
			  ADBEmi32Start:
				pstring;
			  ADBEmi32End:
				align long;

			case SP_STSP:
				longint = 'ADBE';		// SweetPea/Illustrator host.
				key longint = 'StsP';
				longint = 0;			// Index.
				longint = 4;			// Length.
				longint;
					
			case InternalName:
				longint = 'ADBE';		// SweetPea/Illustrator host.
				key longint = 'pinm';
				longint = 0;			// Index.
				#if DeRez
					fill long;
				#else
					longint = (plugInNameEnd[$$ArrayIndex(properties)] -
							   plugInNameStart[$$ArrayIndex(properties)]) / 8;
				#endif
				plugInNameStart:
					cstring;
				plugInNameEnd:
					align long;

			case BuildVersion:
				longint = 'ADBE';		// SweetPea/Illustrator host.
				key longint = 'bvrs';
				longint = 0;			// Index.
				longint = 4;			// Length.
				longint;				// Version.
				
			case ADBEVersion:
				longint = 'ADBE';
				key longint = 'vers';
				longint = 0;
				longint = 4;
				longint;

			case ADBECategory:
				longint = 'ADBE';
				key longint = 'catg';
				longint = 0;
				#if DeRez
					fill long;
				#else
					longint = (ADBEcatgEnd[$$ArrayIndex(properties)] - ADBEcatgStart[$$ArrayIndex(properties)]) / 8;
				#endif
			  ADBEcatgStart:
				pstring
					// Use Help category to put automation plug-ins in the "Help" menu:
					PSHelpMenu = "**Help**",
					
					// Use Hidden category to keep plug-ins out of menus.
					// WARNING: The only way to access a hidden plug-in is
					// by calling it by its event ID from the Play callback!
					PSHidden = "**Hidden**",
					
					// Use Copyright-Checker category to detect copyrights on first-opened files:
					PSCopyrightChecker = "**Copyright-Checker**";
					
			  ADBEcatgEnd:
				align long;

			case ADBEName:
				longint = 'ADBE';
				key longint = 'name';
				longint = 0;
				#if DeRez
					fill long;
				#else
					longint = (ADBEnameEnd[$$ArrayIndex(properties)] - ADBEnameStart[$$ArrayIndex(properties)]) / 8;
				#endif
			  ADBEnameStart:
				pstring;
			  ADBEnameEnd:
				align long;

			case AdapterVersion:
				longint = 'ADBE';		// SweetPea/Illustrator host.
				key longint = 'adpt';
				longint = 0;			// Index.
				longint = 4;			// Length.
				longint;				// Version.
			
			case Imports:
				longint = 'ADBE';		// SweetPea/Illustrator host.
				key longint = 'impt';
				longint = 0;			// Index.
				#if DeRez
					fill long;
				#else
					longint = (importsEnd[$$ArrayIndex(properties)] - 
							   importsStart[$$ArrayIndex(properties)]) / 8;
				#endif
				importsStart:
					longint = $$CountOf(ImportSuites);
					wide array ImportSuites
					{  
						isuitesStart:
							// Length (including this long):
							#if DeRez
								fill long;
							#else
								longint = ((isuitesEnd[$$ArrayIndex(properties), $$ArrayIndex(ImportSuites)] - 
											isuitesStart[$$ArrayIndex(properties), $$ArrayIndex(ImportSuites)]) / 8);
							#endif

							cstring;
							align long;
							longint;			// Suite version.
						isuitesEnd:
					};
				importsEnd:
								
			case Exports:
				longint = 'ADBE';		// SweetPea/Illustrator host.
				key longint = 'expt';
				longint = 0;			// Index.
				#if DeRez
					fill long;
				#else
					longint = (exportsEnd[$$ArrayIndex(properties)] - 
							   exportsStart[$$ArrayIndex(properties)]) / 8;
				#endif
				exportsStart:
					longint = $$CountOf(ExportSuites);
					wide array ExportSuites
					{  
						esuitesStart:
							// Length (including this long):
							#if DeRez
								fill long;
							#else
								longint = ((esuitesEnd[$$ArrayIndex(properties), $$ArrayIndex(ExportSuites)] - 
											esuitesStart[$$ArrayIndex(properties), $$ArrayIndex(ExportSuites)]) / 8);
							#endif

							cstring;
							align long;
							longint;			// Suite version.
						esuitesEnd:
					};
				exportsEnd:
			
					
			case Messages:
				longint = 'ADBE';		// SweetPea/Illustrator host
				key longint = 'AcpM';
				longint = 0;			// Index.
				longint = 4;			// Length.
				fill bit[28];			// Reserved.
				
				boolean startupRequired, noStartupRequired;
				boolean doesNotPurgeCache, purgeCache;
				boolean shutdownRequired, noShutdownRequired;	// Default is to give shutdown msg.
				boolean doNotAcceptProperty, acceptProperty;
				
			};
		};
	};

#undef PIPiPLTypes

//-------------------------------------------------------------------------------

#endif // PIPL.r
