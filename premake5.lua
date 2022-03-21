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

    -- Hacky having to include+link cbop
    includedirs {"libs/bgfx/include", "libs/bx/include", "libs/glfw/include", "libs/imgui", "libs/CSGForge-Core/include", "libs/CSGForge-Core/libs/cbop"}
    files {"src/**.hpp", "src/**.cpp"}
    links {"CSGForge-Core", "bgfx", "bimg", "bx", "glfw", "imgui", "cbop"}
    filter "system:linux"
		links { "dl", "GL", "pthread", "X11" }

filter {}
include "libs/CSGForge-Core"
include "libs/CSGForge-Core/libs/cbop.lua"
include "libs/bgfx.lua"
include "libs/bimg.lua"
include "libs/bx.lua"
include "libs/glfw.lua"
include "libs/imgui.lua"