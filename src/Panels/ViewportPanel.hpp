#pragma once

#include <bgfx/bgfx.h>

#include "BasePanel.hpp"
#include "../Camera.hpp"

namespace ForgeEditor
{
    class ViewportPanel : BasePanel
    {
    public:
        ViewportPanel();
        ~ViewportPanel();

        void Render() override;

    private:
        bgfx::FrameBufferHandle mFramebufferHandle;
        Camera mCamera;
    };
}