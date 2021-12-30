workspace "TradescantiaEngine"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Profile",
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "TradescantiaEngine/ThirdParty/GLFW/include"
IncludeDir["glad"] = "TradescantiaEngine/ThirdParty/glad/include"
IncludeDir["ImGui"] = "TradescantiaEngine/ThirdParty/ImGui"
IncludeDir["glm"] = "TradescantiaEngine/ThirdParty/glm"
IncludeDir["tracy"] = "TradescantiaEngine/ThirdParty/tracy"

include "TradescantiaEngine/ThirdParty/GLFW"
include "TradescantiaEngine/ThirdParty/glad"
include "TradescantiaEngine/ThirdParty/ImGui"
include "TradescantiaEngine/ThirdParty/tracy"

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
		"%{IncludeDir.glm}",
		"%{IncludeDir.tracy}",
	}

	links
	{
		"glad",
		"GLFW",
		"opengl32.lib",
		"ImGui",
		"tracy",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"TRACY_ENABLE",
	}

	filter "system:windows"
		systemversion "10.0"

		defines
		{
			"TSC_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines {"TSC_DEBUG"}
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines {"TSC_RELEASE"}
		runtime "Release"
		optimize "on"
		
	filter "configurations:Profile"
		defines {"TSC_RELEASE", "TSC_PROFILE", "TRACY_ENABLE"}
		runtime "Release"
		optimize "on"
		symbols "on"

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
		"%{IncludeDir.tracy}",
	}

	links
	{
		"TradescantiaEngine",
		"tracy",
	}
	
	defines 
	{
		"TRACY_ENABLE"
	}

	filter "system:windows"
		systemversion "10.0"

		defines
		{
			"TSC_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines {"TSC_DEBUG"}
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines {"TSC_RELEASE"}
		runtime "Release"
		optimize "on"