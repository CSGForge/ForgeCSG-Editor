#pragma once

#include <vector>

#include <CSGForge-Core/csg.hpp>

#include "Mesh.hpp"

namespace ForgeEditor
{
    class Model
    {
    public:
        Model(ForgeCore::World world);
        ~Model() = default;

        void Render(int view);

    private:
        std::vector<Mesh> mMeshes;
        bgfx::VertexLayout mVertexLayout;
        bgfx::ShaderHandle mVsh;
        bgfx::ShaderHandle mFsh;
        bgfx::ProgramHandle mProgram;
    };
}