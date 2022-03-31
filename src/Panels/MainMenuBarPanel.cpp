#include "MainMenuBarPanel.hpp"

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
                ;
            if (ImGui::MenuItem("Website"))
                ;
            ImGui::Separator();
            if (ImGui::MenuItem("Manual", "Ctrl+H"))
                ;
            if (ImGui::MenuItem("Report Bug"))
                ;
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}