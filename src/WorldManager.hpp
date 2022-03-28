#pragma once

#include <memory>

#include <assimp/scene.h>
#include <CSGForge-Core/csg.hpp>

#include "Mesh/Model.hpp"

namespace ForgeEditor
{
    class WorldManager
    {
    public:
        WorldManager();
        ~WorldManager() = default;

        void Update();
        void Render(int view);
        void Export(std::string path);
        ForgeCore::World *GetWorld();

    private:
        ForgeCore::World *mWorld;
        aiScene *mAiScene;
        Model *mModel;
        bool mSceneNeedsRebuild = false;

        void BuildAiScene();
    };
}