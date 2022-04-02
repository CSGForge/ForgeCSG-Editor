#pragma once

#include <vector>

#include <bgfx/bgfx.h>

#include "MeshVertex.hpp"

namespace ForgeEditor
{
    class Mesh
    {
    public:
        Mesh(const std::vector<MeshVertex> &vertices, const std::vector<unsigned int> &indices, bgfx::VertexLayout vertexLayout);
        ~Mesh() = default; // TODO: Delete buffers

        void Render(int view, bgfx::ProgramHandle program);

    private:
        bgfx::VertexBufferHandle mVbh;
        bgfx::IndexBufferHandle mIbh;
    };
}