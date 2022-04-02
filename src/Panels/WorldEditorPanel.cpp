#include "WorldEditorPanel.hpp"

#include <imgui/imgui.h>

#include "../WorldManager.hpp"

namespace ForgeEditor
{
    static std::vector<ForgeCore::Plane> primitive_planes[3] = {
        {
            ForgeCore::Plane(glm::vec3(1, 0, 0), -1),
            ForgeCore::Plane(glm::vec3(-1, 0, 0), -1),
            ForgeCore::Plane(glm::vec3(0, 1, 0), -1),
            ForgeCore::Plane(glm::vec3(0, -1, 0), -1),
            ForgeCore::Plane(glm::vec3(0, 0, 1), -1),
            ForgeCore::Plane(glm::vec3(0, 0, -1), -1),
        },
        {
            ForgeCore::Plane(glm::vec3(-1, 0, 0), -1),
            ForgeCore::Plane(glm::vec3(1, 1, 0), 0),
            ForgeCore::Plane(glm::vec3(0, -1, 0), -1),
            ForgeCore::Plane(glm::vec3(0, 0, 1), -1),
            ForgeCore::Plane(glm::vec3(0, 0, -1), -1),
        },
        {
            // TODO: Work out some cylinder planes
            ForgeCore::Plane(glm::vec3(1, 0, 0), -1),
            ForgeCore::Plane(glm::vec3(-1, 0, 0), -1),
            ForgeCore::Plane(glm::vec3(0, 1, 0), -1),
            ForgeCore::Plane(glm::vec3(0, -1, 0), -1),
            ForgeCore::Plane(glm::vec3(0, 0, 1), -1),
            ForgeCore::Plane(glm::vec3(0, 0, -1), -1),
        }};

    enum BrushType
    {
        CUBE,
        WEDGE,
        CYLINDER
    };

    struct BrushSetting
    {
        ForgeCore::Operation mOperation;
        BrushType mBrushType;
    };

    static auto new_brush_settings = BrushSetting(ForgeCore::Operation::ADDITION, CUBE);

    WorldEditorPanel::WorldEditorPanel()
    {
        SetName("World Editor");
    }

    void WorldEditorPanel::Render()
    {
        bool visible = GetVisibility();
        if (!visible)
            return;
        ImGui::Begin(GetName().c_str(), &visible);
        auto world_manager = &WorldManager::GetWorldManager();

        if (ImGui::Button("New"))
            world_manager->NewWorld();
        ImGui::SameLine();
        if (ImGui::Button("Save"))
            ;
        ImGui::SameLine();
        if (ImGui::Button("Save As"))
            ;
        ImGui::SameLine();
        if (ImGui::Button("Export"))
            world_manager->Export();

        // Slider to change the world void operation
        auto world = world_manager->GetWorld();
        int world_op = world->GetWorldType() / 3;
        std::string op_names[2] = {"Solid", "Air"};
        if (ImGui::SliderInt("Void", &world_op, 0, 1, op_names[world_op].c_str()))
            world->SetWorldType(ForgeCore::WorldType(world_op * 3));

        ImGui::Separator();
        ImGui::Text("New Brush Settings");
        if (ImGui::RadioButton("Cube", new_brush_settings.mBrushType == CUBE))
            new_brush_settings.mBrushType = CUBE;
        ImGui::SameLine();
        if (ImGui::RadioButton("Wedge", new_brush_settings.mBrushType == WEDGE))
            new_brush_settings.mBrushType = WEDGE;
        ImGui::SameLine();
        if (ImGui::RadioButton("Cylinder", new_brush_settings.mBrushType == CYLINDER))
            new_brush_settings.mBrushType = CYLINDER;
        ImGui::SliderInt("Operation", (int *)&new_brush_settings.mOperation, 0, 1, op_names[new_brush_settings.mOperation].c_str());

        ImGui::Separator();
        if (ImGui::Button("Add Brush"))
        {
            auto brush = world->AddBrush();
            world_manager->SetSelectedBrushIdx(world->GetBrushCount() - 1);
            brush->SetOperation(new_brush_settings.mOperation);
            brush->SetPlanes(primitive_planes[new_brush_settings.mBrushType]);
        }
        ImGui::SameLine();
        if (ImGui::Button("Delete Brush"))
        {
            auto selected_idx = world_manager->GetSelectedBrushIdx();
            if (selected_idx != -1)
            {
                world->RemoveBrush(world_manager->GetSelectedBrush());
                world_manager->SetSelectedBrushIdx(selected_idx);
            }
        }
        ImGui::End();
        SetVisibility(visible);
    }
}