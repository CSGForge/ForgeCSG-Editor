project "bgfx"
    kind "StaticLib"
    language "C++"
    cppdialect "C++14"
    defines "__STDC_FORMAT_MACROS"

    includedirs {"bx/include", "bimg/include", "bgfx/include", "bgfx/3rdparty", "bgfx/3rdparty/dxsdk/include", "bgfx/3rdparty/khronos"}
    files {"bgfx/include/bgfx/**.h", "bgfx/src/*.cpp", "bgfx/src/*.h"}
    excludes {"bgfx/src/amalgamated.cpp"}

    filter "configurations:Debug"
		defines "BGFX_CONFIG_DEBUG=1"
    filter "configurations:Release"
		defines "BGFX_CONFIG_DEBUG=0"