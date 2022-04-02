#include "TimelinePanel.hpp"

#include <imgui/imgui.h>

#include "../WorldManager.hpp"

namespace ForgeEditor
{
    TimelinePanel::TimelinePanel()
    {
        SetName("Brush Timeline");
    }

    void TimelinePanel::Render()
    {
        bool visible = GetVisibility();
        if (!visible)
            return;
        ImGui::Begin(GetName().c_str(), &visible);

        auto world_manager = &WorldManager::GetWorldManager();
        auto selected_idx = world_manager->GetSelectedBrushIdx();
        if (ImGui::InputInt("Selected", &selected_idx))
            world_manager->SetSelectedBrushIdx(selected_idx);
        if (ImGui::BeginListBox("timeline", ImVec2(-FLT_MIN, -FLT_MIN)))
        {
            auto brush_count = world_manager->GetWorld()->GetBrushCount();
            for (int i = 0; i < brush_count; i++)
            {
                bool is_selected = i == selected_idx;
                if (ImGui::Selectable(("Brush " + std::to_string(i)).c_str(), is_selected))
                    world_manager->SetSelectedBrushIdx(i);
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndListBox();
        }
        ImGui::End();
        SetVisibility(visible);
    }
}