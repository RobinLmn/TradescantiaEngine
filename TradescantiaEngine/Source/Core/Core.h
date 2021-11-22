#pragma once

#ifdef TSC_PLATFORM_WINDOWS
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
#define TSC_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
