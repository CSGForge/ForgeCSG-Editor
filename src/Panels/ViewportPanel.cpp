#include "ViewportPanel.hpp"

#include <imgui/imgui.h>

namespace ForgeEditor
{
    ViewportPanel::ViewportPanel()
    {
        mFramebufferHandle = bgfx::createFrameBuffer(1280, 720, bgfx::TextureFormat::BGRA8);
        bgfx::setViewFrameBuffer(1, mFramebufferHandle);
        bgfx::setViewClear(1, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x800000FF, 1.0f, 0);
    }

    ViewportPanel::~ViewportPanel()
    {
        bgfx::destroy(mFramebufferHandle);
    }

    void ViewportPanel::Render()
    {
        bgfx::touch(1); // Makes sure this view is rendered even if nothing is submitted for drawing
        if (ImGui::Begin("Viewport") && ImGui::BeginChild("Framebuffer"))
        {
            bgfx::setViewRect(1, 0, 0, 1280, 720);
            ImGui::Image((ImTextureID)(int64_t)bgfx::getTexture(mFramebufferHandle).idx, ImGui::GetWindowSize(), ImVec2(0, 1), ImVec2(1, 0));
            ImGui::EndChild();
            ImGui::End();
        }
    }
}