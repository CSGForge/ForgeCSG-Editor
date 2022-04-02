#pragma once

#include <string>
#include <vector>

#include <CSGForge-Core/csg.hpp>

#include "Mesh.hpp"

namespace ForgeEditor
{
    class Model
    {
    public:
        Model(ForgeCore::World *world);
        ~Model();

        void Render(int view);
        void Rebuild(ForgeCore::World *world);

    private:
        std::vector<Mesh> mMeshes;
        bgfx::VertexLayout mVertexLayout;
        bgfx::ShaderHandle mVsh;
        bgfx::ShaderHandle mFsh;
        bgfx::ProgramHandle mProgram;
    };
}