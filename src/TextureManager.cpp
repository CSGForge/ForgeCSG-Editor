#include "TextureManager.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <iostream>

namespace ForgeEditor
{
    TextureManager *TextureManager::sInstance = nullptr;

    TextureManager::TextureManager()
    {
        if (sInstance != nullptr)
            delete sInstance;
        sInstance = this;
    }

    bgfx::TextureHandle TextureManager::GetTextureHandle(std::string path)
    {
        // Return the texture handle if we have it
        auto it = mHandleMap.find(path);
        if (it != mHandleMap.end())
        {
            return it->second;
        }

        // Otherwise we load the texture and return that
        bgfx::TextureHandle handle = BGFX_INVALID_HANDLE;
        int x = 0, y = 0, comp = 0;
        auto data = stbi_load(path.c_str(), &x, &y, &comp, 4);
        if (data)
        {
            handle = bgfx::createTexture2D(x, y, false, 1, bgfx::TextureFormat::RGBA8, 0, bgfx::copy(data, x * y * 4));
            stbi_image_free(data);
        }
        mHandleMap[path] = handle;
        return handle;
    }

    TextureManager &TextureManager::GetTextureManager()
    {
        return *sInstance;
    }
}