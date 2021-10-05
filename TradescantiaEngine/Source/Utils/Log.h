#pragma once
#include "Core/Core.h"
#include "spdlog/spdlog.h"

namespace TradescantiaEngine
{
	class TSC_API Log
	{
	public:
		static void Init();

		static std::shared_ptr < spdlog::logger > coreLogger;
		static std::shared_ptr < spdlog::logger > clientLogger;
	};
}

#define TSC_CORE_FATAL(...)    ::TradescantiaEngine::Log::coreLogger->fatal(__VA_ARGS__)
#define TSC_CORE_ERROR(...)    ::TradescantiaEngine::Log::coreLogger->error(__VA_ARGS__)
#define TSC_CORE_WARN(...)     ::TradescantiaEngine::Log::coreLogger->warn(__VA_ARGS__)
#define TSC_CORE_INFO(...)     ::TradescantiaEngine::Log::coreLogger->info(__VA_ARGS__)
#define TSC_CORE_TRACE(...)    ::TradescantiaEngine::Log::coreLogger->trace(__VA_ARGS__)

#define TSC_FATAL(...)         ::TradescantiaEngine::Log::clientLogger->fatal(__VA_ARGS__)
#define TSC_ERROR(...)         ::TradescantiaEngine::Log::clientLogger->error(__VA_ARGS__)
#define TSC_WARN(...)          ::TradescantiaEngine::Log::clientLogger->warn(__VA_ARGS__)
#define TSC_INFO(...)          ::TradescantiaEngine::Log::clientLogger->info(__VA_ARGS__)
#define TSC_TRACE(...)         ::TradescantiaEngine::Log::clientLogger->trace(__VA_ARGS__)