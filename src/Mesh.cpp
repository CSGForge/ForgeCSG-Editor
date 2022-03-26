#include "Mesh.hpp"

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

    Mesh::Mesh(const std::vector<MeshVertex> &vertices, const std::vector<unsigned int> &indices)
    {
        mVertexLayout.begin()
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
            .end();

        int vn = vertices.size();
        MeshVertex *v_array = (MeshVertex *)malloc(vn * sizeof(MeshVertex));
        for (int i = 0; i < vn; i++)
            v_array[i] = vertices[i];
        mVbh = bgfx::createVertexBuffer(bgfx::makeRef(v_array, vn * sizeof(MeshVertex)), mVertexLayout);

        int in = indices.size();
        uint16_t *i_array = (uint16_t *)malloc(in * (sizeof(uint16_t)));
        for (int i = 0; i < in; i++)
            i_array[i] = indices[i];

        mIbh = bgfx::createIndexBuffer(bgfx::makeRef(i_array, in * sizeof(uint16_t)));

        mVsh = loadShader("res/shaders/glsl/vs_cubes.bin", "Vertex Shader");
        mFsh = loadShader("res/shaders/glsl/fs_cubes.bin", "Fragment Shader");
        mProgram = bgfx::createProgram(mVsh, mFsh, true);
        std::cout << bgfx::isValid(mVsh) << std::endl;
    }

    // Mesh::~Mesh()
    // {
    //     // bgfx::destroy(mProgram);
    //     // bgfx::destroy(mVbh); // TODO: Work out why this makes it die
    //     // bgfx::destroy(mIbh);
    // }

    void Mesh::Render(int view)
    {
        bgfx::setVertexBuffer(0, mVbh);
        bgfx::setIndexBuffer(mIbh);
        bgfx::submit(view, mProgram);
    }
}