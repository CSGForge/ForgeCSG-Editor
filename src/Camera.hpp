#pragma once

#include <glm/glm.hpp>

namespace ForgeEditor
{
    struct CameraMoveState
    {
        float mAngleX = 0.0f;
        float mAngleY = 0.0f;
        bool mForward = false;
        bool mBackward = false;
        bool mLeft = false;
        bool mRight = false;
        bool mUp = false;
        bool mDown = false;
    };

    class Camera
    {
    public:
        Camera() = default;
        Camera(float fov_y, float near_dist, float far_dist, glm::vec3 eye = {0.0f, 0.0f, -1.0f}, glm::vec3 forward = {0.0f, 0.0f, 1.0f}, glm::vec3 up = {0.0f, 1.0f, 0.0f});
        ~Camera() = default;

        void SetView(int view_id, float aspect_ratio);
        void Update(CameraMoveState cam_mov_state);

        glm::mat4 GetView();
        glm::mat4 GetProjection();

    private:
        glm::vec3 mEye;
        glm::vec3 mForward;
        glm::vec3 mUp;
        float mView[16];
        float mProj[16];
        float mFovY;
        float mNearDist;
        float mFarDist;
    };
}