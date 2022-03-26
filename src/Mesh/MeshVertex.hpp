#pragma once

#include <glm/glm.hpp>

namespace ForgeEditor
{
    struct MeshVertex
    {
        glm::vec3 mPos;
        uint32_t mColour; // ABGR packed format
    };
}