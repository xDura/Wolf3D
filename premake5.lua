#!lua
workspace "Wolf3D"
	architecture "x86_64"
   startproject "Sample"
   
	configurations
	{
		"Debug",
		"Release",
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["Glad"] = "/Wolf3D/external/Glad/include"
IncludeDir["stb"] = "Wolf3D/external/stb"

group "Dependencies"
   include "Wolf3D/external/Glad"
group ""

project "Wolf3D"
   location "Wolf3D"
   kind "StaticLib"
   language "C++"
   cppdialect "C++11"
   staticruntime "on"

   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

   files
   {
      "%{prj.name}/src/**.h",
      "%{prj.name}/src/**.cpp",
   }

   pchheader "wf_pch.h"
   pchsource "Wolf3D/src/wf_pch.cpp"

   includedirs
   {
      "%{prj.name}/src",
      "%{IncludeDir.Glad}",
      "%{IncludeDir.stb}",
      "%{prj.name}/external/",
   }

   links 
	{ 
		"Glad",
	}

   filter "system:windows"
      systemversion "latest"

   filter "configurations:Debug"
      defines "WF_DEBUG"
      runtime "Debug"
      symbols "on"

   filter "configurations:Release"
      defines "WF_RELEASE"
      runtime "Release"
      optimize "on"


project "Sample"
   location "Sample"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++11"
   staticruntime "on"

   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

   files
   {
      "%{prj.name}/src/**.h",
      "%{prj.name}/src/**.cpp"
   }

   links
   {
      "Wolf3D"
   }

   filter "system:windows"
      systemversion "latest"
      
   filter "configurations:Debug"
      defines "WF_DEBUG"
      runtime "Debug"
      symbols "on"

   filter "configurations:Release"
      defines "WF_RELEASE"
      runtime "Release"
      optimize "on"
