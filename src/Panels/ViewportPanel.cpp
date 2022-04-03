#include "ViewportPanel.hpp"

#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>
#include <imgui/imgui.h>
#include <ImGuizmo/ImGuizmo.h>

#include "../WorldManager.hpp"

namespace ForgeEditor
{
    ViewportPanel::ViewportPanel()
    {
        SetName("Viewport");
        bgfx::TextureHandle buffer_tex[2] = {
            bgfx::createTexture2D(bgfx::BackbufferRatio::Equal, false, 1, bgfx::TextureFormat::RGBA32F, BGFX_TEXTURE_RT),
            bgfx::createTexture2D(bgfx::BackbufferRatio::Equal, false, 1, bgfx::TextureFormat::D32F, BGFX_TEXTURE_RT),
        };
        mFramebufferHandle = bgfx::createFrameBuffer(2, buffer_tex, true);
        bgfx::setViewFrameBuffer(1, mFramebufferHandle);
        bgfx::setViewClear(1, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x72726FFF, 1.0f, 0);
        mCamera = {60.0f, 0.1f, 100.f, {0.0f, 0.0f, -10.0f}};
        mGuizmoType = -1;
    }

    ViewportPanel::~ViewportPanel()
    {
        bgfx::destroy(mFramebufferHandle);
    }

    void ViewportPanel::Render()
    {
        // Set the view each frame because resizing display window drops this bind
        bgfx::setViewFrameBuffer(1, mFramebufferHandle);

        bool visible = GetVisibility();
        if (!visible)
            return;
        ImGui::Begin(GetName().c_str(), &visible);
        ImGui::BeginChild("Framebuffer");

        auto world_manager = &WorldManager::GetWorldManager();
        auto win_size = ImGui::GetWindowSize();
        auto io = &ImGui::GetIO();

        // Update camera. Use an invisible button to capture input
        auto viewport_start_pos = ImGui::GetCursorScreenPos();
        if (ImGui::IsMouseDown(ImGuiMouseButton_Right))
        {
            ImGui::InvisibleButton("viewport_area", win_size, ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);
            if (ImGui::IsItemHovered() && ImGui::IsItemActive())
            {
                CameraMoveState cam_mov_state;
                cam_mov_state.mAngleX = io->MouseDelta.x;
                cam_mov_state.mAngleY = io->MouseDelta.y;
                cam_mov_state.mForward = ImGui::IsKeyDown(ImGuiKey_W);
                cam_mov_state.mBackward = ImGui::IsKeyDown(ImGuiKey_S);
                cam_mov_state.mLeft = ImGui::IsKeyDown(ImGuiKey_A);
                cam_mov_state.mRight = ImGui::IsKeyDown(ImGuiKey_D);
                cam_mov_state.mUp = ImGui::IsKeyDown(ImGuiKey_Q);
                cam_mov_state.mDown = ImGui::IsKeyDown(ImGuiKey_E);
                mCamera.Update(cam_mov_state);

                // TODO: Reset mouse position
                // ImGui::SetMouseCursor(ImGuiMouseCursor_None);
            }
        }
        else if (ImGui::IsWindowFocused())
        {
            // Guizmo keybinds
            if (ImGui::IsKeyDown(ImGuiKey_Q))
                mGuizmoType = -1;
            if (ImGui::IsKeyDown(ImGuiKey_W))
                mGuizmoType = ImGuizmo::OPERATION::TRANSLATE;
            if (ImGui::IsKeyDown(ImGuiKey_E))
                mGuizmoType = ImGuizmo::OPERATION::ROTATE;
            if (ImGui::IsKeyDown(ImGuiKey_R))
                mGuizmoType = ImGuizmo::OPERATION::SCALE;
            if (ImGui::IsKeyDown(ImGuiKey_T))
                mGuizmoType = ImGuizmo::OPERATION::UNIVERSAL;
        }

        float aspect_ratio = win_size.x / win_size.y;
        mCamera.SetView(1, aspect_ratio);

        // Render world
        bgfx::setViewRect(1, 0, 0, win_size.x, win_size.y);
        bgfx::touch(1); // Makes sure this view is rendered even if nothing is submitted for drawing
        world_manager->Render(1);

        // Draw the framebuffer image. Need to set some imgui stuff to draw in the same place as the invis button
        ImGui::SetItemAllowOverlap();
        ImGui::SetCursorScreenPos(viewport_start_pos);
        auto dis_size = io->DisplaySize;
        auto uv1 = ImVec2(win_size.x / dis_size.x, 1.0f - win_size.y / dis_size.y);
        ImGui::Image((ImTextureID)(int64_t)bgfx::getTexture(mFramebufferHandle).idx, win_size, ImVec2(0, 1), uv1);

        // Draw guizmos
        auto selected_brush = world_manager->GetSelectedBrush();
        if (selected_brush && mGuizmoType != -1)
        {
            // Initialise the ImGuizmo stuff
            ImGuizmo::SetOrthographic(false);
            ImGuizmo::SetDrawlist();

            // Set the region
            auto win_pos = ImGui::GetWindowPos();
            ImGuizmo::SetRect(win_pos.x, win_pos.y, win_size.x, win_size.y);

            // Set the camera
            auto cam_view = mCamera.GetView();
            auto cam_proj = mCamera.GetProjection();
            auto transform = selected_brush->GetTransform();
            auto rot_rad = glm::radians(transform.mRotation);
            auto transform_mtx =
                glm::translate(glm::mat4(1.0f), transform.mTranslation) *
                glm::eulerAngleXYZ(rot_rad.x, rot_rad.y, rot_rad.z) *
                glm::scale(glm::mat4(1.0f), transform.mScale);

            // Render and update
            ImGuizmo::Manipulate(glm::value_ptr(cam_view), glm::value_ptr(cam_proj), (ImGuizmo::OPERATION)mGuizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform_mtx));
            if (ImGuizmo::IsUsing())
            {
                float translation[3], rotation[3], scale[3];
                ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(transform_mtx), translation, rotation, scale);
                selected_brush->SetTransform({glm::make_vec3(scale), glm::make_vec3(rotation), glm::make_vec3(translation)});
            }
        }
        ImGui::EndChild();
        ImGui::End();

        SetVisibility(visible);
    }
}