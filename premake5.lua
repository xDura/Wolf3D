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
IncludeDir["Glad"] = "Wolf3D/external/Glad/include"
IncludeDir["Imgui"] = "Wolf3D/external/Imgui"
IncludeDir["external"] = "Wolf3D/external"

group "Dependencies"
   include "Wolf3D/external/Glad"
   include "Wolf3D/external/Imgui"
group ""

project "Wolf3D"
   location "Wolf3D"
   kind "StaticLib"
   language "C++"
   cppdialect "C++11"
   staticruntime "on"

   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
   
   pchheader "wf_pch.h"
   pchsource "Wolf3D/src/wf_pch.cpp"
   
   files
   {
      "%{prj.name}/src/**.h",
      "%{prj.name}/src/**.cpp",
   }

   includedirs
   {
      "%{prj.name}/src",
      "%{IncludeDir.Glad}",
      "%{IncludeDir.Imgui}",
      "%{IncludeDir.external}",
   }

   links 
   {
      "ImGui",
      "Glad",
      "SDL2",
      "SDL2Main",
   }

   filter "system:windows"
      systemversion "latest"
      libdirs 
      {
         "Wolf3D/external/SDL2/bin/x64"
      }
      
      filter "system:linux"
      libdirs
      {
         "usr/bin" --TODO: CHECK IF I NEED THIS--
      }

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

   includedirs
	{
      "Wolf3D/src",
      "%{IncludeDir.Glad}",
      "%{IncludeDir.Imgui}",
      "%{IncludeDir.external}",
   }

   filter "system:windows"
      systemversion "latest"
      links
      {
         "Wolf3D",
      }
      
	filter "system:linux"
      libdirs 
      {
         "Wolf3D/external/SDL2/bin/linux/",
      }
      links
      {
         "Wolf3D",
         "SDL2",
         "SDL2main",
         "Glad",
         "ImGui",
         "dl"
      }
   filter "system:macosx"
      libdirs 
      {
         "Wolf3D/external/SDL2/bin/macos/",
      }
      links
      {
         "Wolf3D",
         "SDL2",
         "SDL2main",
         "Glad",
         "ImGui",
         "dl" --TODO: CHECK IF I NEED THIS-- 
      }

   filter "configurations:Debug"
      defines "WF_DEBUG"
      runtime "Debug"
      symbols "on"

   filter "configurations:Release"
      defines "WF_RELEASE"
      runtime "Release"
      optimize "on"
