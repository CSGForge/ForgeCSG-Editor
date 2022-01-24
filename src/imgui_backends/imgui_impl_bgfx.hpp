#pragma once
#include <imgui/imgui.h>

IMGUI_IMPL_API void ImGui_Implbgfx_Init(int view);
IMGUI_IMPL_API void ImGui_Implbgfx_Shutdown();
IMGUI_IMPL_API void ImGui_Implbgfx_NewFrame();
IMGUI_IMPL_API void ImGui_Implbgfx_RenderDrawLists(struct ImDrawData* draw_data);

// Use if you want to reset your rendering device without losing ImGui state.
IMGUI_IMPL_API void ImGui_Implbgfx_InvalidateDeviceObjects();
IMGUI_IMPL_API bool ImGui_Implbgfx_CreateDeviceObjects();