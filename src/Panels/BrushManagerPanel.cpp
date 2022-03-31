#include "BrushManagerPanel.hpp"

#include <stdio.h>
#include <string>

#include <imgui/imgui.h>

namespace ForgeEditor
{
    static std::vector<ForgeCore::Plane> cube_planes{
        ForgeCore::Plane(glm::vec3(1, 0, 0), -1),
        ForgeCore::Plane(glm::vec3(-1, 0, 0), -1),
        ForgeCore::Plane(glm::vec3(0, 1, 0), -1),
        ForgeCore::Plane(glm::vec3(0, -1, 0), -1),
        ForgeCore::Plane(glm::vec3(0, 0, 1), -1),
        ForgeCore::Plane(glm::vec3(0, 0, -1), -1),
    };

    BrushManagerPanel::BrushManagerPanel(ForgeCore::World *world)
    {
        mWorld = world;
        mSelectedBrush = nullptr;
        mSelected = -1;
        SetName("Brush Manager");
    }

    void BrushManagerPanel::Render()
    {
        bool visible = GetVisibility();
        if (!visible)
            return;
        ImGui::Begin(GetName().c_str(), &visible);

        static std::vector<ForgeCore::Plane> planes;
        ImGui::BeginGroup();
        ImGui::BeginChild("hierarchy", ImVec2(150, -ImGui::GetFrameHeightWithSpacing()), true);
        // TODO: Add reordering
        for (int i = 0; i < mWorld->GetBrushCount(); i++)
            if (ImGui::Selectable(("Brush " + std::to_string(i)).c_str(), mSelected == i))
            {
                mSelected = i;
                mSelectedBrush = mWorld->GetBrush(i);
                planes = mSelectedBrush->GetPlanes();
            }
        ImGui::EndChild();
        if (ImGui::Button("Add"))
        {
            mSelectedBrush = mWorld->AddBrush();
            // Sets default cube planes
            // TODO: Option for different primitives
            mSelectedBrush->SetPlanes(cube_planes);
            mSelected = mWorld->GetBrushCount() - 1;
            planes = mSelectedBrush->GetPlanes();
        }
        ImGui::SameLine();
        if (ImGui::Button("Delete") && mSelectedBrush != nullptr)
        {
            mWorld->RemoveBrush(mSelectedBrush);
            mSelectedBrush = nullptr;
            mSelected = -1;
            planes.clear();
        }
        ImGui::EndGroup();
        ImGui::SameLine();
        ImGui::BeginChild("details", ImVec2(0, 0));
        ImGui::Text("Brush Details");
        ImGui::Separator();
        if (mSelectedBrush != nullptr)
        {
            ImGui::Value("Intersection Count", (int)mSelectedBrush->GetIntersections().size());
            ImGui::Value("Face Count", (int)mSelectedBrush->GetFaces().size());

            // Slider to change the brush operation
            auto brush_op = mSelectedBrush->GetOperation();
            std::string op_names[2] = {"Solid", "Air"};
            if (ImGui::SliderInt("Operation", (int *)&brush_op, 0, 1, op_names[brush_op].c_str()))
                mSelectedBrush->SetOperation(brush_op);

            // Time editing
            if (ImGui::SliderInt("Time", &mSelected, 0, mWorld->GetBrushCount() - 1))
                mWorld->SetBrushTime(mSelectedBrush, mSelected);

            // Inputs to change the brush transform
            if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
            {
                auto transform = mSelectedBrush->GetTransform();

                bool modified = false;
                modified |= ImGui::InputFloat3("Translation", (float *)&transform.mTranslation);
                modified |= ImGui::InputFloat3("Rotation", (float *)&transform.mRotation);
                modified |= ImGui::InputFloat3("Scale", (float *)&transform.mScale);
                if (modified)
                    mSelectedBrush->SetTransform(transform);
            }

            // Inputs to change brush plane equations
            if (ImGui::CollapsingHeader("Planes", ImGuiTreeNodeFlags_None))
            {
                bool modified = false;
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
                    mSelectedBrush->SetPlanes(planes);
            }
        }
        ImGui::EndChild();
        ImGui::End();
        SetVisibility(visible);
    }
}