project "bx"
    kind "StaticLib"
    language "C++"
    cppdialect "C++14"
    defines "__STDC_FORMAT_MACROS"

    includedirs {"bx/include", "bx/3rdparty"}
    files {"bx/include/bx/*.h", "bx/include/bx/inline/*.inl", "bx/src/*.cpp"}
    excludes {"bx/src/amalgamated.cpp", "bx/src/crtnone.cpp"}