workspace "CSGForge-Editor"
    location "build"
    startproject "CSGForge-Editor"
    configurations {"Debug", "Release"}

    filter "configurations:Release"
        defines {"NDEBUG", "BX_CONFIG_DEBUG=0"}
        optimize "Full"
    
    filter "configurations:Debug"
        defines {"DEBUG", "BX_CONFIG_DEBUG=1"}
        optimize "Debug"
        symbols "On"

project "CSGForge-Editor"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++14"
    targetdir("bin/%{cfg.buildcfg}")

    includedirs {"libs/bgfx/include", "libs/bx/include", "libs/glfw/include"}
    includedirs {"libs/bgfx/include", "libs/bx/include", "libs/glfw/include", "libs/imgui"}
    files {"src/**.hpp", "src/**.cpp"}
    links {"bgfx", "bimg", "bx", "glfw", "imgui"}
    filter "system:linux"
		links { "dl", "GL", "pthread", "X11" }

include "libs/bgfx.lua"
include "libs/bimg.lua"
include "libs/bx.lua"
include "libs/glfw.lua"
include "libs/imgui.lua"