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

#ifndef TSC_DIST
	#define TSC_CORE_ASSERT(x, ...) {if (!(x)) {TSC_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define TSC_ASSERT(x, ...) {if (!(x)) {TSC_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define TSC_CORE_ASSERT(x, ...)
	#define TSC_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
