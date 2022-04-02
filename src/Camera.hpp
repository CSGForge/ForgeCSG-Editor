#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "Window.hpp"

namespace ForgeEditor
{
    class Camera
    {
    public:
        Camera() = default;
        Camera(float fov_y, float near_dist, float far_dist, glm::vec3 eye = {0.0f, 0.0f, -1.0f}, glm::vec3 forward = {0.0f, 0.0f, 1.0f}, glm::vec3 up = {0.0f, 1.0f, 0.0f});
        ~Camera() = default;

        void SetView(int view_id, float aspect_ratio);
        void Update(Window *window);

    private:
        glm::vec3 mEye;
        glm::vec3 mForward;
        glm::vec3 mUp;
        float mView[16];
        float mProj[16];
        float mFovY;
        float mNearDist;
        float mFarDist;
        bool mCursorLocked = false;
        glm::dvec2 mCursorPosition;
    };
}