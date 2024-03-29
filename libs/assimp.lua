project "assimp"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    includedirs {
        "assimp_config/assimp",
        "assimp/include",
        "assimp/include/assimp",
        "assimp/include/assimp/Compiler",
        "assimp/code/",
        "assimp/contrib/unzip/",
        "assimp/contrib/zlib/",
    }

    files {
        "assimp/include",
        "assimp/include/assimp",

        "assimp/code/CApi/**", -- CApi_SRCS
        "assimp/code/Common/**", -- Common_SRCS
        "assimp/code/Material/**",
        "assimp/code/PostProcessing/**",

        -- Exporters
        "assimp/code/AssetLib/Obj/**",
        "assimp/code/AssetLib/3DS/**",
        "assimp/code/AssetLib/FBX/**",
        -- "assimp/code/AssetLib/glTF/glTFExporter.*",
        -- "assimp/code/AssetLib/glTF2/glTF2Exporter.*",

        -- 3rd party
        "assimp/contrib/unzip/**",
        "assimp/contrib/zlib/*.c",
        "assimp/contrib/zlib/*.h",
    }

    defines {
        -- Let assimp build zlib
        "ASSIMP_BUILD_NO_OWN_ZLIB",
        -- Disable unneeded importers
        "ASSIMP_BUILD_NO_AMF_IMPORTER",
        "ASSIMP_BUILD_NO_C4D_IMPORTER",
        -- "ASSIMP_BUILD_NO_3DS_IMPORTER", -- Required for the exporter
        "ASSIMP_BUILD_NO_AC_IMPORTER",
        "ASSIMP_BUILD_NO_ASE_IMPORTER",
        "ASSIMP_BUILD_NO_ASSBIN_IMPORTER",
        "ASSIMP_BUILD_NO_B3D_IMPORTER",
        "ASSIMP_BUILD_NO_BVH_IMPORTER",
        "ASSIMP_BUILD_NO_COLLADA_IMPORTER",
        "ASSIMP_BUILD_NO_DXF_IMPORTER",
        "ASSIMP_BUILD_NO_CSM_IMPORTER",
        "ASSIMP_BUILD_NO_HMP_IMPORTER",
        "ASSIMP_BUILD_NO_IRRMESH_IMPORTER",
        "ASSIMP_BUILD_NO_IQM_IMPORTER",
        "ASSIMP_BUILD_NO_IRR_IMPORTER",
        "ASSIMP_BUILD_NO_LWO_IMPORTER",
        "ASSIMP_BUILD_NO_LWS_IMPORTER",
        "ASSIMP_BUILD_NO_M3D_IMPORTER",
        "ASSIMP_BUILD_NO_MD2_IMPORTER",
        "ASSIMP_BUILD_NO_MD3_IMPORTER",
        "ASSIMP_BUILD_NO_MD5_IMPORTER",
        "ASSIMP_BUILD_NO_MDC_IMPORTER",
        "ASSIMP_BUILD_NO_MDL_IMPORTER",
        "ASSIMP_BUILD_NO_NFF_IMPORTER",
        "ASSIMP_BUILD_NO_NDO_IMPORTER",
        "ASSIMP_BUILD_NO_OFF_IMPORTER",
        -- "ASSIMP_BUILD_NO_OBJ_IMPORTER", -- Required for the exporter
        "ASSIMP_BUILD_NO_OGRE_IMPORTER",
        "ASSIMP_BUILD_NO_OPENGEX_IMPORTER",
        "ASSIMP_BUILD_NO_PLY_IMPORTER",
        "ASSIMP_BUILD_NO_MS3D_IMPORTER",
        "ASSIMP_BUILD_NO_COB_IMPORTER",
        "ASSIMP_BUILD_NO_BLEND_IMPORTER",
        "ASSIMP_BUILD_NO_IFC_IMPORTER",
        "ASSIMP_BUILD_NO_XGL_IMPORTER",
        -- "ASSIMP_BUILD_NO_FBX_IMPORTER", -- Required for the exporter
        "ASSIMP_BUILD_NO_Q3D_IMPORTER",
        "ASSIMP_BUILD_NO_Q3BSP_IMPORTER",
        "ASSIMP_BUILD_NO_RAW_IMPORTER",
        "ASSIMP_BUILD_NO_SIB_IMPORTER",
        "ASSIMP_BUILD_NO_SMD_IMPORTER",
        "ASSIMP_BUILD_NO_STL_IMPORTER",
        "ASSIMP_BUILD_NO_TERRAGEN_IMPORTER",
        "ASSIMP_BUILD_NO_3D_IMPORTER",
        "ASSIMP_BUILD_NO_X_IMPORTER",
        "ASSIMP_BUILD_NO_X3D_IMPORTER",
        "ASSIMP_BUILD_NO_GLTF_IMPORTER", -- Required for the exporter
        "ASSIMP_BUILD_NO_3MF_IMPORTER",
        "ASSIMP_BUILD_NO_MMD_IMPORTER",

        -- Disable unneeded exporters
        "ASSIMP_BUILD_NO_OPENGEX_EXPORTER",
        "ASSIMP_BUILD_NO_PLY_EXPORTER",
        "ASSIMP_BUILD_NO_ASSBIN_EXPORTER",
        "ASSIMP_BUILD_NO_ASSXML_EXPORTER",
        "ASSIMP_BUILD_NO_M3D_EXPORTER",
        "ASSIMP_BUILD_NO_COLLADA_EXPORTER",
        "ASSIMP_BUILD_NO_X_EXPORTER",
        "ASSIMP_BUILD_NO_STL_EXPORTER",
        "ASSIMP_BUILD_NO_X3D_EXPORTER",
        "ASSIMP_BUILD_NO_3MF_EXPORTER",
        "ASSIMP_BUILD_NO_PBRT_EXPORTER",
        "ASSIMP_BUILD_NO_ASSJSON_EXPORTER",
        "ASSIMP_BUILD_NO_STEP_EXPORTER",
        "ASSIMP_BUILD_NO_GLTF_EXPORTER", -- Caused issues when building
        -- "ASSIMP_BUILD_NO_3DS_EXPORTER",
        -- "ASSIMP_BUILD_NO_FBX_EXPORTER",
    }
    
    filter "system:windows"
        defines {"_WINDOWS"}
    filter "system:linux"
        defines {"HAVE_UNISTD_H"}
    