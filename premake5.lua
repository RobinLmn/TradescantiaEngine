workspace "TradescantiaEngine"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "TradescantiaEngine/ThirdParty/GLFW/include"
IncludeDir["glad"] = "TradescantiaEngine/ThirdParty/glad/include"
IncludeDir["ImGui"] = "TradescantiaEngine/ThirdParty/ImGui"
IncludeDir["glm"] = "TradescantiaEngine/ThirdParty/glm"

include "TradescantiaEngine/ThirdParty/GLFW"
include "TradescantiaEngine/ThirdParty/glad"
include "TradescantiaEngine/ThirdParty/ImGui"

project "TradescantiaEngine"
	location "TradescantiaEngine"
	kind "StaticLib"
	cppdialect "C++17"
	language "C++"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "tscpch.h"
	pchsource "TradescantiaEngine/Source/tscpch.cpp"

	files
	{
		"TradescantiaEngine/Source/**.h",
		"TradescantiaEngine/Source/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	includedirs
	{
		"TradescantiaEngine/ThirdParty/spdlog/include",
		"TradescantiaEngine/Source",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"glad",
		"GLFW",
		"opengl32.lib",
		"ImGui"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	filter "system:windows"
		systemversion "10.0"

		defines
		{
			"TSC_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "TSC_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "TSC_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "TSC_DIST"
		runtime "Release"
		optimize "on"

project "Playground"
	location "Playground"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"Playground/Source/**.h",
		"Playground/Source/**.cpp",
	}

	includedirs
	{
		"TradescantiaEngine/ThirdParty/spdlog/include",
		"TradescantiaEngine/ThirdParty",
		"TradescantiaEngine/Source",
		"%{IncludeDir.glm}",
	}

	links
	{
		"TradescantiaEngine"
	}

	filter "system:windows"
		systemversion "10.0"

		defines
		{
			"TSC_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "TSC_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "TSC_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "TSC_DIST"
		runtime "Release"
		optimize "on"