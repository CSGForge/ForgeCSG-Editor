#include "WorldManager.hpp"

namespace ForgeEditor
{
    WorldManager::WorldManager()
    {
        mWorld = new ForgeCore::World();
        mModel = new Model(mWorld);
    }

    void WorldManager::Update()
    {
        mWorld->Update();
        if (mWorld->Modified())
            mModel->Rebuild(mWorld);
    }

    void WorldManager::Render(int view)
    {
        mModel->Render(view);
    }

    ForgeCore::World *WorldManager::GetWorld()
    {
        return mWorld;
    }

    // void WorldManager::Export(std::string path)
    // {
    //     if (mAiScene == nullptr)
    //         BuildAiScene();

    //     // Export stuff
    // }

    // void WorldManager::BuildAiScene()
    // {
    //     mAiScene = new aiScene();

    //     mAiScene->mRootNode = new aiNode();
    //     mAiScene->mRootNode->mName.Set("World");

    //     int num_meshes = mMeshes.size();

    //     // Preset the roots children
    //     mAiScene->mRootNode->mChildren = new aiNode *[num_meshes];
    //     mAiScene->mRootNode->mNumChildren++;

    //     for (int i = 0; i < num_meshes; i++)
    //     {
    //         auto mesh = mMeshes[i];

    //         auto child_node = new aiNode();
    //         child_node->mName = "Brush" + std::to_string(i);

    //         // Set parent child relations
    //         mAiScene->mRootNode->mChildren[i] = child_node;
    //         child_node->mParent = mAiScene->mRootNode;

    //         // Build mesh
    //         auto face_tri_counts = mesh.GetFaceTriCounts();
    //         auto num_faces = face_tri_counts.size();
    //         auto child_mesh = new aiMesh();
    //         child_mesh->mFaces = new aiFace[num_faces];
    //         child_mesh->mNumFaces = num_faces;
    //         child_mesh->mPrimitiveTypes = aiPrimitiveType_TRIANGLE;
    //         unsigned int index_offset;
    //         for (int j = 0; j < num_faces; j++)
    //         {
    //             // Build face
    //             auto ai_face = &child_mesh->mFaces[j];

    //             // TODO: I need to have the vertices and indices :) Or just the world
    //         }
    //     }
    // }
}