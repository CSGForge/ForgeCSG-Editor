project "bimg"
    kind "StaticLib"
    language "C++"
    cppdialect "C++14"
    
    includedirs {"bx/include", "bimg/include", "bimg/3rdparty/astc-codec", "bimg/3rdparty/astc-codec/include"}
    files {"bimg/include/bimg/*.h", "bimg/src/image.cpp", "bimg/src/image_gnf.cpp", "bimg/src/*.h", "bimg/3rdparty/astc-codec/src/decoder/*.cc"}
