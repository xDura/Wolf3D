project "ImGui"
    kind "StaticLib"
    language "C++"
    staticruntime "on"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
    files
    {
        "**.h",
        "**.cpp",
    }
	
	includedirs
	{
		"../Glad/include/"
	}
	
	defines "IMGUI_IMPL_OPENGL_LOADER_GLAD"
    
    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
