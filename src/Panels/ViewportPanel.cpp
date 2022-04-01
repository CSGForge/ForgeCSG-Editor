#include "ViewportPanel.hpp"

#include <imgui/imgui.h>

#include "../Application.hpp"

namespace ForgeEditor
{
    ViewportPanel::ViewportPanel()
    {
        SetName("Viewport");
        mFramebufferHandle = bgfx::createFrameBuffer(bgfx::BackbufferRatio::Equal, bgfx::TextureFormat::BGRA8);
        bgfx::setViewClear(1, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x72726FFF, 1.0f, 0);
        mCamera = {60.0f, 0.1f, 100.f, {0.0f, 0.0f, -10.0f}};
    }

    ViewportPanel::~ViewportPanel()
    {
        bgfx::destroy(mFramebufferHandle);
    }

    void ViewportPanel::Render()
    {
        bool visible = GetVisibility();
        if (!visible)
            return;

        // Set the view each frame because resizing display window drops this bind
        bgfx::setViewFrameBuffer(1, mFramebufferHandle);

        ImGui::Begin(GetName().c_str(), &visible);
        ImGui::BeginChild("Framebuffer");

        // Update view
        auto win_size = ImGui::GetWindowSize();
        bgfx::setViewRect(1, 0, 0, win_size.x, win_size.y);
        float aspect_ratio = win_size.x / win_size.y;
        auto window = Application::GetApplication().GetWindow();
        mCamera.Update(&window);
        mCamera.SetView(1, aspect_ratio);

        auto dis_size = ImGui::GetIO().DisplaySize;
        auto uv1 = ImVec2(win_size.x / dis_size.x, 1.0f - win_size.y / dis_size.y);
        bgfx::touch(1); // Makes sure this view is rendered even if nothing is submitted for drawing

        ImGui::Image((ImTextureID)(int64_t)bgfx::getTexture(mFramebufferHandle).idx, win_size, ImVec2(0, 1), uv1);
        ImGui::EndChild();
        ImGui::End();

        SetVisibility(visible);
    }
}