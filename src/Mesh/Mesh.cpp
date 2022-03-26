#include "Mesh.hpp"

#include <fstream>
#include <iostream>

namespace ForgeEditor
{
    Mesh::Mesh(const std::vector<MeshVertex> &vertices, const std::vector<unsigned int> &indices, bgfx::VertexLayout vertexLayout)
    {
        int vn = vertices.size();
        MeshVertex *v_array = (MeshVertex *)malloc(vn * sizeof(MeshVertex));
        for (int i = 0; i < vn; i++)
            v_array[i] = vertices[i];
        mVbh = bgfx::createVertexBuffer(bgfx::makeRef(v_array, vn * sizeof(MeshVertex)), vertexLayout);

        int in = indices.size();
        uint16_t *i_array = (uint16_t *)malloc(in * (sizeof(uint16_t)));
        for (int i = 0; i < in; i++)
            i_array[i] = indices[i];

        mIbh = bgfx::createIndexBuffer(bgfx::makeRef(i_array, in * sizeof(uint16_t)));
    }

    void Mesh::Render(int view, bgfx::ProgramHandle program)
    {
        bgfx::setVertexBuffer(0, mVbh);
        bgfx::setIndexBuffer(mIbh);
        bgfx::submit(view, program);
    }
}