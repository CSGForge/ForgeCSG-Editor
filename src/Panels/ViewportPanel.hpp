#pragma once

#include <bgfx/bgfx.h>

namespace ForgeEditor
{
    class ViewportPanel
    {
    public:
        ViewportPanel();
        ~ViewportPanel();

        void Render();

    private:
        bgfx::FrameBufferHandle mFramebufferHandle;
    };
}