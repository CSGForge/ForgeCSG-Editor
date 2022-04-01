#include "TimelinePanel.hpp"

#include <imgui/imgui.h>

namespace ForgeEditor
{
    TimelinePanel::TimelinePanel(ImGuiManager *imGuiManager, WorldManager *world_manager)
    {
        SetName("Brush Timeline");
        mImGuiManager = imGuiManager;
        mWorldManager = world_manager;
    }

    void TimelinePanel::Render()
    {
        bool visible = GetVisibility();
        if (!visible)
            return;
        ImGui::Begin(GetName().c_str(), &visible);
        auto selected_idx = mWorldManager->GetSelectedBrushIdx();
        if (ImGui::InputInt("Selected", &selected_idx))
            mWorldManager->SetSelectedBrushIdx(selected_idx);
        if (ImGui::BeginListBox("timeline", ImVec2(-FLT_MIN, -FLT_MIN)))
        {
            auto brush_count = mWorldManager->GetWorld()->GetBrushCount();
            for (int i = 0; i < brush_count; i++)
            {
                bool is_selected = i == selected_idx;
                if (ImGui::Selectable(("Brush " + std::to_string(i)).c_str(), is_selected))
                    mWorldManager->SetSelectedBrushIdx(i);
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndListBox();
        }
        ImGui::End();
        SetVisibility(visible);
    }
}