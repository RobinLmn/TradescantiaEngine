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

include "TradescantiaEngine/ThirdParty/GLFW"

project "TradescantiaEngine"
	location "TradescantiaEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "tscpch.h"
	pchsource "TradescantiaEngine/Source/tscpch.cpp"

	files
	{
		"TradescantiaEngine/Source/**.h",
		"TradescantiaEngine/Source/**.cpp",
	}

	includedirs
	{
		"TradescantiaEngine/ThirdParty/spdlog/include",
		"TradescantiaEngine/Source",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "on"
		systemversion "10.0"

		defines
		{
			"TSC_PLATFORM_WINDOWS",
			"TSC_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Playground")
		}

	filter "configurations:Debug"
		defines "TSC_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "TSC_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "TSC_DIST"
		symbols "On"

project "Playground"
	location "Playground"
	kind "ConsoleApp"
	language "C++"

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
		"TradescantiaEngine/Source"
	}

	links
	{
		"TradescantiaEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "on"
		systemversion "10.0"

		defines
		{
			"TSC_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "TSC_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "TSC_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "TSC_DIST"
		symbols "On"