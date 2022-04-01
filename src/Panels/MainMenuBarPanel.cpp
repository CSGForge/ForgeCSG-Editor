#include "MainMenuBarPanel.hpp"

#include <bgfx/platform.h>
#include <imgui/imgui.h>
#include <portable-file-dialogs.h>

namespace ForgeEditor
{
    MainMenuBarPanel::MainMenuBarPanel(ImGuiManager *imGuiManager, WorldManager *world_manager)
    {
        SetName("Main Menu Bar");
        mImGuiManager = imGuiManager;
        mWorldManager = world_manager;
    }

    void MainMenuBarPanel::Render()
    {
        std::string menu_action = "";

        ImGui::BeginMainMenuBar();
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New", "Ctrl+N"))
                mWorldManager->NewWorld();
            if (ImGui::MenuItem("Open", "Ctrl+O"))
                ;
            if (ImGui::BeginMenu("Open Recent..."))
            {
                ImGui::MenuItem("No recent files...", nullptr, false, false);
                ImGui::EndMenu();
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Save", "Ctrl+S"))
                ;
            if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
                ;
            if (ImGui::MenuItem("Export", "Ctrl+Shift+E"))
            {
                auto selection = pfd::save_file("Export World...", ".fbx", {"FBX/OBJ", "*.obj *.fbx"}).result();
                if (!selection.empty())
                    mWorldManager->Export(selection);
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Quit", "Ctrl+Q"))
                ;
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "Ctrl+Z"))
                ;
            if (ImGui::MenuItem("Redo", "Ctrl+Shift+Z"))
                ;
            ImGui::Separator();
            if (ImGui::MenuItem("Brush", "Ctrl+1", true))
                ;
            if (ImGui::MenuItem("Clip", "Ctrl+2", false))
                ;
            if (ImGui::MenuItem("Vertex", "Ctrl+3", false))
                ;
            if (ImGui::MenuItem("Edge", "Ctrl+4", false))
                ;
            if (ImGui::MenuItem("Face", "Ctrl+5", false))
                ;
            ImGui::Separator();
            if (ImGui::MenuItem("Preferences", "Ctrl+,"))
                ;
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Next Panel", "Ctrl+Tab"))
                ;
            if (ImGui::MenuItem("Previous Panel", "Ctrl+Shift+Tab"))
                ;
            ImGui::Separator();
            if (ImGui::MenuItem("Lock UI", nullptr, false))
                ;
            if (ImGui::MenuItem("Reset UI"))
                ;
            ImGui::Separator();
            auto panels = mImGuiManager->GetPanels();
            for (int i = 0; i < panels.size(); i++)
            {
                auto panel = panels[i].get();
                if (panel == this)
                    continue;

                bool visible = panel->GetVisibility();
                ImGui::MenuItem(panel->GetName().c_str(), ("Ctrl+Alt+" + std::to_string(i + 1)).c_str(), &visible);
                panel->SetVisibility(visible);
            }
            // if (ImGui::MenuItem("World Editor", "Ctrl+Alt+2", false))
            //     ;
            // if (ImGui::MenuItem("Console", "Ctrl+Alt+4", false))
            //     ;
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("About"))
                menu_action = "open about window";
            if (ImGui::MenuItem("Website"))
            {
                auto url = "https://github.com/CSGForge/ForgeCSG-Editor";
#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
                system(std::string("xdg-open ").append(url).c_str());
#elif BX_PLATFORM_OSX
                system(std::string("open ").append(url).c_str());
#elif BX_PLATFORM_WINDOWS
                system(std::string("start ").append(url).c_str());
#endif
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Manual", "Ctrl+H"))
                ;
            if (ImGui::MenuItem("Report Bug"))
            {
                auto url = "https://github.com/CSGForge/ForgeCSG-Editor/issues/new";
#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
                system(std::string("xdg-open ").append(url).c_str());
#elif BX_PLATFORM_OSX
                system(std::string("open ").append(url).c_str());
#elif BX_PLATFORM_WINDOWS
                system(std::string("start ").append(url).c_str());
#endif
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();

        bool popup_open = true;
        if (menu_action == "open about window")
            ImGui::OpenPopup("About");
        if (ImGui::BeginPopupModal("About", &popup_open))
        {
            ImGui::Text("Developers");
            ImGui::Separator();
            ImGui::Text("Jarrod Doyle");
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Text("3rd Party Libraries");
            ImGui::Separator();
            ImGui::Text("Assimp (3d model export)");
            ImGui::Text("BGFX (Cross-platform rendering)");
            ImGui::Text("Bimg (BGFX images)");
            ImGui::Text("Bx (BGFX base");
            ImGui::Text("CSGForge-Core (Core CSG algorithm)");
            ImGui::Text("glfw (Multi-platform windowing and input)");
            ImGui::Text("Dear ImGui (User interface)");
            ImGui::Text("pfd (System file dialogs for Windows, Linux, and Mac)");

            ImGui::EndPopup();
        }
    }
}