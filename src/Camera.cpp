#include "Camera.hpp"

#include <iostream>

#include <bgfx/bgfx.h>
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>

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

            // Rotation angles
            const float m_ms = 0.01f;
            float x_angle = cursor_movement.x * m_ms;
            float y_angle = cursor_movement.y * m_ms;

            float new_y_angle = mAngleY + y_angle;
            if (new_y_angle >= 1.4 || new_y_angle <= -1.4) // Angles are equivalent to 80 degrees in radians
            {
                y_angle = 0;
                x_angle = 0;
            }
            mAngleY += y_angle;
            mAngleX += x_angle;
            std::cout << mAngleX << " " << mAngleY << std::endl;

            // Tilt
            if (y_angle != 0)
            {
                auto right = glm::cross(mUp, mForward);
                auto mtx = glm::rotate(glm::mat4(1), y_angle, right);
                mForward = glm::normalize(glm::mat3(glm::vec3(mtx[0]), glm::vec3(mtx[1]), glm::vec3(mtx[2])) * mForward);
            }

            // Pan
            if (x_angle != 0)
            {
                auto right = glm::cross(mUp, mForward);
                auto up = glm::cross(mForward, right);
                auto mtx = glm::rotate(glm::mat4(1), x_angle, up);
                mForward = glm::normalize(glm::mat3(glm::vec3(mtx[0]), glm::vec3(mtx[1]), glm::vec3(mtx[2])) * mForward);
            }

            // Truck/Dolly/Pedestal
            {
                auto right = glm::cross(mUp, mForward);
                auto up = glm::cross(mForward, right);
                glm::vec3 d_eye(0.0f);
                if (glfwGetKey(native_window, GLFW_KEY_W) == GLFW_PRESS)
                    d_eye += mForward;
                if (glfwGetKey(native_window, GLFW_KEY_A) == GLFW_PRESS)
                    d_eye -= right;
                if (glfwGetKey(native_window, GLFW_KEY_S) == GLFW_PRESS)
                    d_eye -= mForward;
                if (glfwGetKey(native_window, GLFW_KEY_D) == GLFW_PRESS)
                    d_eye += right;
                if (glfwGetKey(native_window, GLFW_KEY_Q) == GLFW_PRESS)
                    d_eye += up;
                if (glfwGetKey(native_window, GLFW_KEY_E) == GLFW_PRESS)
                    d_eye -= up;

                // Normalise speed
                if (glm::length(d_eye) != 0)
                    d_eye /= glm::length(d_eye);

                const float ms = 0.5f;
                mEye += ms * glm::vec3{d_eye.x, d_eye.y, d_eye.z};
            }

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