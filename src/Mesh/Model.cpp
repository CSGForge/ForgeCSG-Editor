#include "Model.hpp"

#include <fstream>
#include <iostream>

namespace ForgeEditor
{
    bgfx::ShaderHandle loadShader(std::string path, std::string name)
    {
        std::string shader_contents;

        // Open the file
        std::ifstream file(path, std::ios::binary);
        if (!file.is_open())
            return BGFX_INVALID_HANDLE;

        // Work out the file length
        std::istream::pos_type current_pos = file.tellg();
        if (current_pos == std::istream::pos_type(-1))
            return BGFX_INVALID_HANDLE;

        file.seekg(0, std::istream::end);
        std::istream::pos_type end_pos = file.tellg();
        file.seekg(current_pos);
        std::streamoff len = end_pos - current_pos;
        if (len == -1)
            return BGFX_INVALID_HANDLE;

        // Read the contents
        shader_contents.resize(static_cast<std::string::size_type>(len));
        file.read(&shader_contents[0], shader_contents.length());
        if (!file.good())
        {
            file.close();
            return BGFX_INVALID_HANDLE;
        }
        file.close();

        // Create the bgfx shader
        const bgfx::Memory *mem = bgfx::copy(shader_contents.data(), shader_contents.length());
        const bgfx::ShaderHandle handle = bgfx::createShader(mem);
        bgfx::setName(handle, name.c_str());

        return handle;
    }

    Model::Model(ForgeCore::World *world)
    {
        // Shader related stuffs
        mVertexLayout.begin()
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
            .end();
        auto vsh = loadShader("res/shaders/glsl/vs_cubes.bin", "Vertex Shader");
        auto fsh = loadShader("res/shaders/glsl/fs_cubes.bin", "Fragment Shader");
        mProgram = bgfx::createProgram(vsh, fsh, true);
        bgfx::destroy(vsh);
        bgfx::destroy(fsh);

        Rebuild(world);
    }

    Model::~Model()
    {
        bgfx::destroy(mProgram);
    }

    void Model::Rebuild(ForgeCore::World *world)
    {
        mMeshes.clear();
        srand(1); // Ensures consistent colours
        for (auto b : world->GetBrushes())
        {
            std::vector<MeshVertex> mesh_vs;
            std::vector<unsigned int> mesh_is;
            unsigned int offset = 0;
            for (auto f : b->GetFaces())
            {
                uint32_t colour = (255 << 24) + ((rand() % 256) << 16) + ((rand() % 256) << 8) + (rand() % 256);

                auto vs = f.GetTriangleVertices();
                for (auto v : vs)
                    mesh_vs.push_back({v, colour});
                for (auto i : f.GetIndices())
                    mesh_is.push_back(i + offset);
                offset += vs.size();
            }
            mMeshes.push_back(Mesh(mesh_vs, mesh_is, mVertexLayout));
        }
    }

    void Model::Render(int view)
    {
        for (auto mesh : mMeshes)
            mesh.Render(view, mProgram);
    }
}