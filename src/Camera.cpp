#include "Camera.hpp"

#include <iostream>

#include <bgfx/bgfx.h>
#include <imgui/imgui.h>

namespace ForgeEditor
{
    Camera::Camera(float fov_y, float near_dist, float far_dist, glm::vec3 eye, glm::vec3 forward, glm::vec3 up)
        : mFovY(fov_y), mNearDist(near_dist), mFarDist(far_dist), mEye(eye), mForward(forward), mUp(up) {}

    void Camera::SetView(int view_id)
    {
        auto at_glm = mEye + mForward;
        bx::Vec3 eye = {mEye.x, mEye.y, mEye.z};
        bx::Vec3 at = {at_glm.x, at_glm.y, at_glm.z};
        bx::Vec3 up = {mUp.x, mUp.y, mUp.z};
        bx::mtxLookAt(mView, eye, at, up);
        bx::mtxProj(mProj, mFovY, mAspectRatio, mNearDist, mFarDist, bgfx::getCaps()->homogeneousDepth);
        bgfx::setViewTransform(view_id, mView, mProj);
    }

    void Camera::Update(std::unique_ptr<Window> &window)
    {
        mAspectRatio = (float)window->GetWidth() / (float)window->GetHeight();

        if (ImGui::GetIO().WantCaptureKeyboard || ImGui::GetIO().WantCaptureMouse)
            return;

        auto native_window = window->GetNativeWindow();
        if (glfwGetMouseButton(native_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
            if (!mCursorLocked)
            {
                mCursorLocked = true;
                glfwGetCursorPos(native_window, &mCursorPosition.x, &mCursorPosition.y);
                glfwSetInputMode(native_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }

            glm::dvec2 cursor_movement;
            glfwGetCursorPos(native_window, &cursor_movement.x, &cursor_movement.y);
            cursor_movement -= mCursorPosition;

            // Mouse changes mForward
            // - mdx = rotation around y axis
            // - mdy = rotation around x axis
            const float m_ms = -0.01f;
            const float mdx = cursor_movement.x * m_ms;
            const float mdy = cursor_movement.y * m_ms;
            const float sx = sin(mdy);
            const float cx = cos(mdy);
            const float sy = sin(mdx);
            const float cy = cos(mdx);
            glm::mat3 mtx = {{cy, 0, sy}, {sx * sy, cx, -sx * cy}, {-cx * sy, sx, cx * cy}};
            mForward = mtx * mForward;
            mForward /= glm::length(mForward);

            // KB changes mEye
            glm::vec3 d_eye(0.0f);
            if (glfwGetKey(native_window, GLFW_KEY_W) == GLFW_PRESS)
                d_eye.z += 1.0f;
            if (glfwGetKey(native_window, GLFW_KEY_A) == GLFW_PRESS)
                d_eye.x -= 1.0f;
            if (glfwGetKey(native_window, GLFW_KEY_S) == GLFW_PRESS)
                d_eye.z -= 1.0f;
            if (glfwGetKey(native_window, GLFW_KEY_D) == GLFW_PRESS)
                d_eye.x += 1.0f;
            if (glfwGetKey(native_window, GLFW_KEY_Q) == GLFW_PRESS)
                d_eye.y += 1.0f;
            if (glfwGetKey(native_window, GLFW_KEY_E) == GLFW_PRESS)
                d_eye.y -= 1.0f;
            if (glm::length(d_eye) != 0)
                d_eye /= glm::length(d_eye);
            // TODO: Move relative to forward direction

            float ms = 0.5f;
            mEye += d_eye * ms;

            glfwSetCursorPos(native_window, mCursorPosition.x, mCursorPosition.y);
        }
        else if (mCursorLocked)
        {
            mCursorLocked = false;
            glfwSetInputMode(native_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            glfwSetCursorPos(native_window, mCursorPosition.x, mCursorPosition.y);
        }
    }
}