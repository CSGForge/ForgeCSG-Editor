#include "Application.hpp"

#include <fstream>
#include <iostream>

#include <imgui/imgui.h>
#include <bgfx/bgfx.h>
#include <bx/math.h>
#include <CSGForge-Core/csg.hpp>

#include "ImGuiManager.hpp"
#include "Panels/ViewportPanel.hpp"
#include "Panels/BrushManagerPanel.hpp"
#include "Mesh.hpp"

namespace ForgeEditor
{
    Application *Application::sInstance = nullptr;

    Mesh buildMesh(ForgeCore::World world)
    {
        std::vector<MeshVertex> mesh_vs;
        std::vector<unsigned int> mesh_is;

        unsigned int offset = 0;
        for (auto b : world.GetBrushes())
        {
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
        }

        return Mesh(mesh_vs, mesh_is);
    }

    Application::Application()
    {
        if (sInstance != nullptr)
        {
            // ! TODO: Shouldn't happen!
            delete sInstance;
        }

        sInstance = this;
        mName = "CSG Forge";
        mWindow = std::make_unique<Window>(1280, 720, mName);
    }

    Application::~Application()
    {
        bgfx::shutdown();
        glfwTerminate();
    }

    void Application::Run()
    {
        auto world = ForgeCore::World();
        auto imguiManager = ImGuiManager(mWindow->GetNativeWindow());
        auto viewport_panel = ViewportPanel();
        auto brush_manager_panel = BrushManagerPanel(&world);
        auto mesh = buildMesh(world);

        int counter = 0;
        while (!glfwWindowShouldClose(mWindow->GetNativeWindow()))
        {
            bgfx::touch(0);

            float view[16];
            bx::mtxLookAt(view, {0.0f, 0.0f, -10.0f}, {0.0f, 0.0f, 0.0f});
            float proj[16];
            bx::mtxProj(proj, 60.0f, float(1280) / float(720), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
            bgfx::setViewTransform(0, view, proj);
            float mtx[16];
            bx::mtxRotateXY(mtx, counter * 0.01f, counter * 0.01f);
            bgfx::setTransform(mtx);

            mesh.Render(0);

            imguiManager.BeginFrame();

            // TODO: Move Dear ImGui stuff
            ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
            // viewport_panel.Render();
            brush_manager_panel.Render();

            imguiManager.EndFrame(mWindow->GetWidth(), mWindow->GetHeight());

            auto start = clock();
            world.Update();
            if (world.Modified())
            {
                mesh = buildMesh(world);
                auto end = clock();
                printf("Update took %.3f seconds\n", (end - start) / (double)CLOCKS_PER_SEC);
            }
            mWindow->Update();
            counter++;
        }
    }
}