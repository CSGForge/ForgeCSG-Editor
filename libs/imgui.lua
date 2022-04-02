project "imgui"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    
    includedirs {"imgui", "imgui/imgui", "imgui/ImGuizmo"}
    files {
        "imgui/imgui/imconfig.h",
        "imgui/imgui/imgui_demo.cpp",
        "imgui/imgui/imgui_draw.cpp",
        "imgui/imgui/imgui_internal.h",
        "imgui/imgui/imgui_tables.cpp",
        "imgui/imgui/imgui_widgets.cpp",
        "imgui/imgui/imgui.*",
        "imgui/imgui/imstb_rectpack.h",
        "imgui/imgui/imstb_texedit.h",
        "imgui/imgui/imstb_truetype.h",
        "imgui/ImGuizmo/ImGuizmo.h",
        "imgui/ImGuizmo/ImGuizmo.cpp",
    }