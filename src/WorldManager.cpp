#include "WorldManager.hpp"

#include <iostream>

#include <assimp/Exporter.hpp>
#include <portable-file-dialogs.h>

namespace ForgeEditor
{
    WorldManager *WorldManager::sInstance = nullptr;

    WorldManager::WorldManager()
    {
        if (sInstance != nullptr)
            delete sInstance;
        sInstance = this;

        mWorld = new ForgeCore::World();
        mModel = new Model(mWorld);
        mAiScene = nullptr;
        mSelectedBrushIdx = -1;
    }

    WorldManager &WorldManager::GetWorldManager()
    {
        return *sInstance;
    }

    void WorldManager::NewWorld()
    {
        delete mWorld;
        mWorld = new ForgeCore::World();
        mModel->Rebuild(mWorld);
        mSceneNeedsRebuild = true;
        mSelectedBrushIdx = -1;
        // TODO: Fix segfault that occurs when trying to add brushes after this
    }

    void WorldManager::Update()
    {
        mWorld->Update();
        if (mWorld->Modified())
        {
            mModel->Rebuild(mWorld);
            mSceneNeedsRebuild = true;
        }
    }

    void WorldManager::Render(int view)
    {
        mModel->Render(view);
    }

    ForgeCore::Brush *WorldManager::GetSelectedBrush()
    {
        return mWorld->GetBrush(mSelectedBrushIdx);
    }

    int WorldManager::GetSelectedBrushIdx()
    {
        return mSelectedBrushIdx;
    }

    void WorldManager::SetSelectedBrushIdx(int idx)
    {
        idx = std::clamp(idx, -1, mWorld->GetBrushCount() - 1);
        mSelectedBrushIdx = idx;
    }

    ForgeCore::World *WorldManager::GetWorld()
    {
        return mWorld;
    }

    void WorldManager::Export()
    {
        auto path = pfd::save_file("Export World...", ".fbx", {"FBX/OBJ", "*.obj *.fbx"}).result();
        if (path.empty())
            return;

        if (mSceneNeedsRebuild)
        {
            if (mAiScene != nullptr)
                free(mAiScene);
            BuildAiScene();
            mSceneNeedsRebuild = false;
        }

        // Export stuff
        Assimp::Exporter exporter;
        exporter.Export(mAiScene, path.substr(path.find_last_of(".") + 1), path);
    }

    void WorldManager::BuildAiScene()
    {
        srand(1); // Ensures consistent colours

        mAiScene = new aiScene();
        mAiScene->mPrivate = nullptr;
        mAiScene->mRootNode = new aiNode();
        mAiScene->mRootNode->mName.Set("World");

        auto brushes = mWorld->GetBrushes();

        // Build the children nodes
        std::vector<aiNode *> children;
        std::vector<aiMesh *> meshes;
        for (int b_idx = 0; b_idx < brushes.size(); b_idx++)
        {
            auto b = brushes[b_idx];

            // Separate mesh for each face
            unsigned int num_meshes = 0;
            auto fs = b->GetFaces();
            for (int f_idx = 0; f_idx < fs.size(); f_idx++)
            {
                auto f = fs[f_idx];
                auto vs = f.GetTriangleVertices();
                auto is = f.GetIndices();

                if (vs.size() == 0)
                    continue;

                auto mesh = new aiMesh();
                mesh->mName = "Face " + std::to_string(f_idx);
                mesh->mPrimitiveTypes = aiPrimitiveType_TRIANGLE;
                mesh->mMaterialIndex = 0;

                // Set mesh vertex information
                unsigned int num_vertices = vs.size();
                mesh->mNumVertices = num_vertices;
                mesh->mVertices = new aiVector3D[num_vertices];
                mesh->mColors[0] = new aiColor4D[num_vertices];
                auto colour = aiColor3D((rand() % 256) / 255.0, (rand() % 256) / 255.0, (rand() % 256) / 255.0);

                for (int i = 0; i < num_vertices; i++)
                {
                    auto v = vs[i];
                    mesh->mVertices[i] = aiVector3D(v.x, v.y, v.z);
                    mesh->mColors[0][i] = aiColor4D(colour.b, colour.g, colour.r, 1.0);
                }

                // Set mesh faces
                mesh->mNumFaces = is.size() / 3;
                mesh->mFaces = new aiFace[mesh->mNumFaces];
                for (int i = 0; i < mesh->mNumFaces; i++)
                {
                    auto face = &mesh->mFaces[i];
                    face->mNumIndices = 3;
                    face->mIndices = new unsigned int[3];
                    for (int j = 0; j < 3; j++)
                        face->mIndices[j] = is[3 * i + j];
                }

                // Update mesh list
                num_meshes++;
                meshes.push_back(mesh);
            }

            if (num_meshes == 0)
                continue;

            // Create the child node
            auto child = new aiNode();
            child->mName = "Brush " + std::to_string(b_idx);
            child->mParent = mAiScene->mRootNode;
            child->mNumMeshes = num_meshes;
            child->mMeshes = new unsigned int[num_meshes];
            for (int i = 0; i < num_meshes; i++)
                child->mMeshes[i] = meshes.size() - num_meshes + i;
            children.push_back(child);
        }

        // Set root node children
        unsigned int num_children = children.size();
        if (num_children == 0)
            return;

        mAiScene->mRootNode->mNumChildren = num_children;
        mAiScene->mRootNode->mChildren = new aiNode *[num_children];
        for (int i = 0; i < num_children; i++)
            mAiScene->mRootNode->mChildren[i] = children[i];

        // Set the meshes
        unsigned int mesh_count = meshes.size();
        mAiScene->mNumMeshes = mesh_count;
        mAiScene->mMeshes = new aiMesh *[mesh_count];
        for (int i = 0; i < mesh_count; i++)
            mAiScene->mMeshes[i] = meshes[i];

        // Set base material
        mAiScene->mNumMaterials = 1;
        mAiScene->mMaterials = new aiMaterial *[1];
        auto mat = new aiMaterial;
        aiString name(std::string("BaseMat"));
        mat->AddProperty(&name, AI_MATKEY_NAME);
        mAiScene->mMaterials[0] = mat;
    }
}