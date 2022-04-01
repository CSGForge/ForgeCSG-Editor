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

        void NewWorld();
        void Update();
        void Render(int view);
        void Export();
        ForgeCore::Brush *GetSelectedBrush();
        int GetSelectedBrushIdx();
        void SetSelectedBrushIdx(int idx);
        ForgeCore::World *GetWorld();

    private:
        int mSelectedBrushIdx;
        ForgeCore::World *mWorld;
        aiScene *mAiScene;
        Model *mModel;
        bool mSceneNeedsRebuild = true;

        void BuildAiScene();
    };
}