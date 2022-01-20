project "glfw"
    kind "StaticLib"
    language "C"

    includedirs {"glfw/include"}
    files {
        "glfw/include/GLFW/*.h",
        "glfw/src/context.c",
        "glfw/src/egl_context.*",
        "glfw/src/init.c",
        "glfw/src/input.c",
        "glfw/src/internal.h",
        "glfw/src/monitor.c",
        "glfw/src/mappings.h",
        "glfw/src/null*.*",
        "glfw/src/osmesa_context.*",
        "glfw/src/platform.*",
        "glfw/src/vulkan.c",
        "glfw/src/window.c"
    }

    filter "system:linux"
        defines "_GLFW_X11"
        files {
            "glfw/src/glx_context.*",
            "glfw/src/linux*.*",
            "glfw/src/posix*.*",
            "glfw/src/x11*.*",
            "glfw/src/xkb*.*"
        }