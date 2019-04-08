local BUILD_DIR = "build"
local THIRDPARTY_DIR = "thirdparty"
local BX_DIR = path.join(THIRDPARTY_DIR, "bx")

solution "piranha76"
	configurations { "Release", "Debug" }
	if _OPTIONS["cc"] ~= nil then
		location(path.join(BUILD_DIR, _ACTION) .. "_" .. _OPTIONS["cc"])
	else
		location(path.join(BUILD_DIR, _ACTION))
	end
	if os.is64bit() and not os.istarget("windows") then
		platforms { "x86_64", "x86" }
	else
		platforms { "x86", "x86_64" }
	end
	startproject "piranha76"
	filter "platforms:x86"
		architecture "x86"
	filter "platforms:x86_64"
		architecture "x86_64"
	filter "configurations:Debug*"
		defines { "_DEBUG" }
		optimize "Debug"
		symbols "On"
	filter "configurations:Release"
		defines "NDEBUG"
		optimize "Full"
		
project "piranha76"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++14"
	exceptionhandling "Off"
	rtti "Off"
	warnings "Extra"
	files "source/*.*"
	includedirs
	{
		path.join(BX_DIR, "include")
	}
	links { "bx" }
	filter "system:windows"
		links { "psapi" }
	filter "action:vs*"
		includedirs { path.join(BX_DIR, "include/compat/msvc") }
	filter { "system:windows", "action:gmake" }
		includedirs { path.join(BX_DIR, "include/compat/mingw") }

group "thirdparty"

project "bx"
	kind "StaticLib"
	language "C++"
	cppdialect "C++14"
	exceptionhandling "Off"
	rtti "Off"
	defines	{ "__STDC_FORMAT_MACROS" }
	files
	{
		path.join(BX_DIR, "include/bx/*.h"),
		path.join(BX_DIR, "include/bx/inline/*.inl"),
		path.join(BX_DIR, "include/tinystl/*.h"),
		path.join(BX_DIR, "src/*.cpp")
	}
	excludes
	{
		path.join(BX_DIR, "src/amalgamated.cpp"),
		path.join(BX_DIR, "src/crtnone.cpp")
	}
	includedirs
	{
		path.join(BX_DIR, "3rdparty"),
		path.join(BX_DIR, "include")
	}
	filter "action:vs*"
		defines { "_CRT_SECURE_NO_WARNINGS" }
		includedirs { path.join(BX_DIR, "include/compat/msvc") }
	filter { "system:windows", "action:gmake" }
		includedirs { path.join(BX_DIR, "include/compat/mingw") }
