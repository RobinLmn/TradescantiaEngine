#pragma once

#ifdef TSC_PLATFORM_WINDOWS
	#ifdef TSC_BUILD_DLL
		#define TSC_API __declspec(dllexport)	
	#else
		#define TSC_API __declspec(dllimport)
	#endif
#else
	#error Tradescantia only supports Windows.
#endif