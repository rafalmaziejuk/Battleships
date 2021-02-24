workspace "Battleships"
	architecture "x86"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Battleships"
	location "Battleships"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.inl"
	}

	includedirs
	{
		"%{prj.name}/vendor/SFML/include"
	}

	libdirs
	{
		"%{prj.name}/vendor/SFML/lib"
	}

	links 
	{ 
		"opengl32.lib", 
		"freetype.lib", 
		"winmm.lib", 
		"gdi32.lib", 
		"openal32.lib", 
		"flac.lib", 
		"vorbisenc.lib", 
		"vorbisfile.lib", 
		"vorbis.lib", 
		"ogg.lib", 
		"ws2_32.lib" 
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"SFML_STATIC"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

		links
		{
			"sfml-audio-s-d.lib", 
			"sfml-graphics-s-d.lib", 
			"sfml-system-s-d.lib", 
			"sfml-window-s-d.lib",
			"sfml-network-s-d.lib"
		}

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

		links
		{
			"sfml-audio-s.lib", 
			"sfml-graphics-s.lib", 
			"sfml-system-s.lib", 
			"sfml-window-s.lib",
			"sfml-network-s.lib"
		}