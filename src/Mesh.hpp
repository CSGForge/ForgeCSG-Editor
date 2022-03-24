#pragma once

#include <vector>
#include <string>

#include <bgfx/bgfx.h>
#include <glm/glm.hpp>

namespace ForgeEditor
{
    struct MeshVertex
    {
        glm::vec3 mPos;
        uint32_t mColour; // ABGR packed format
    };

    class Mesh
    {
    public:
        Mesh(const std::vector<MeshVertex> &vertices, const std::vector<unsigned int> &indices);
        ~Mesh() = default;

        void Render(int view);

    private:
        bgfx::VertexLayout mVertexLayout;
        bgfx::ShaderHandle mVsh;
        bgfx::ShaderHandle mFsh;
        bgfx::ProgramHandle mProgram;
        bgfx::VertexBufferHandle mVbh;
        bgfx::IndexBufferHandle mIbh;
    };
}