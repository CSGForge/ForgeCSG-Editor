#include "BrushEditorPanel.hpp"

#include <imgui/imgui.h>

#include "../WorldManager.hpp"

namespace ForgeEditor
{
    BrushEditorPanel::BrushEditorPanel()
    {
        SetName("Brush Editor");
    }

    void BrushEditorPanel::Render()
    {
        bool visible = GetVisibility();
        if (!visible)
            return;
        ImGui::Begin(GetName().c_str(), &visible);
        auto world_manager = &WorldManager::GetWorldManager();
        auto brush = world_manager->GetSelectedBrush();
        if (brush != nullptr)
        {
            auto brush_time = world_manager->GetSelectedBrushIdx();
            auto world = world_manager->GetWorld();

            ImGui::Value("Intersection Count", (int)brush->GetIntersections().size());
            ImGui::Value("Face Count", (int)brush->GetFaces().size());

            // Slider to change the brush operation
            auto brush_op = brush->GetOperation();
            std::string op_names[2] = {"Solid", "Air"};
            if (ImGui::SliderInt("Operation", (int *)&brush_op, 0, 1, op_names[brush_op].c_str()))
                brush->SetOperation(brush_op);

            // Time editing
            if (ImGui::SliderInt("Time", &brush_time, 0, world->GetBrushCount() - 1))
            {
                world->SetBrushTime(brush, brush_time);
                world_manager->SetSelectedBrushIdx(brush_time);
            }

            // Inputs to change the brush transform
            if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
            {
                auto transform = brush->GetTransform();

                bool modified = false;
                modified |= ImGui::InputFloat3("Translation", (float *)&transform.mTranslation);
                modified |= ImGui::InputFloat3("Rotation", (float *)&transform.mRotation);
                modified |= ImGui::InputFloat3("Scale", (float *)&transform.mScale);
                if (modified)
                    brush->SetTransform(transform);
            }

            // Inputs to change brush plane equations
            if (ImGui::CollapsingHeader("Planes", ImGuiTreeNodeFlags_None))
            {
                bool modified = false;
                auto planes = brush->GetPlanes();
                ImGui::BeginTable("planes", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg);
                ImGui::TableSetupColumn("Normal", ImGuiTableColumnFlags_WidthStretch, 3.0f);
                ImGui::TableSetupColumn("Offset", ImGuiTableColumnFlags_WidthStretch, 1.0f);
                ImGui::TableHeadersRow();
                for (int i = 0; i < (int)planes.size(); i++)
                {
                    ImGui::TableNextRow();
                    if (i == 0)
                    {
                        ImGui::TableSetColumnIndex(0);
                        ImGui::PushItemWidth(-FLT_MIN);
                        ImGui::TableSetColumnIndex(1);
                        ImGui::PushItemWidth(-FLT_MIN);
                    }
                    ImGui::TableSetColumnIndex(0);
                    modified |= ImGui::InputFloat3(("n" + std::to_string(i)).c_str(), (float *)&planes[i].mBaseNormal);
                    ImGui::TableNextColumn();
                    modified |= ImGui::InputFloat(("o" + std::to_string(i)).c_str(), &planes[i].mBaseOffset);
                }
                ImGui::EndTable();
                if (modified)
                    brush->SetPlanes(planes);
            }
        }
        ImGui::End();
        SetVisibility(visible);
    }
}