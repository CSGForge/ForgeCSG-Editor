#pragma once

#include <unordered_map>
#include <string>

#include <bgfx/bgfx.h>

namespace ForgeEditor
{
    class TextureManager
    {
    public:
        TextureManager();
        ~TextureManager() = default;

        bgfx::TextureHandle GetTextureHandle(std::string path);
        static TextureManager &GetTextureManager();

    private:
        static TextureManager *sInstance;
        std::unordered_map<std::string, bgfx::TextureHandle> mHandleMap;
    };
}