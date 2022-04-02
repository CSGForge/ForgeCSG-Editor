#include "Camera.hpp"

#include <bx/math.h>
#include <bgfx/bgfx.h>
#include <glm/gtc/matrix_transform.hpp>

namespace ForgeEditor
{
    Camera::Camera(float fov_y, float near_dist, float far_dist, glm::vec3 eye, glm::vec3 forward, glm::vec3 up)
        : mFovY(fov_y), mNearDist(near_dist), mFarDist(far_dist), mEye(eye), mForward(forward), mUp(up) {}

    void Camera::SetView(int view_id, float aspect_ratio)
    {
        auto at_glm = mEye + mForward;
        bx::Vec3 eye = {mEye.x, mEye.y, mEye.z};
        bx::Vec3 at = {at_glm.x, at_glm.y, at_glm.z};
        bx::Vec3 up = {mUp.x, mUp.y, mUp.z};
        bx::mtxLookAt(mView, eye, at, up);
        bx::mtxProj(mProj, mFovY, aspect_ratio, mNearDist, mFarDist, bgfx::getCaps()->homogeneousDepth);
        bgfx::setViewTransform(view_id, mView, mProj);
    }

    void Camera::Update(CameraMoveState cam_mov_state)
    {
        // Rotation angles
        const float m_ms = 0.005f;
        const float x_angle = cam_mov_state.mAngleX * m_ms;
        const float y_angle = cam_mov_state.mAngleY * m_ms;

        // Tilt
        if (y_angle != 0)
        {
            auto right = glm::cross(mUp, mForward);
            auto mtx = glm::rotate(glm::mat4(1), y_angle, right);
            auto new_forward = glm::normalize(glm::mat3(glm::vec3(mtx[0]), glm::vec3(mtx[1]), glm::vec3(mtx[2])) * mForward);
            if (std::abs(glm::dot(new_forward, mUp)) < 0.985f) // .985 == cos(10 degrees)/abs(sin(170 degrees))
                mForward = new_forward;
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
            if (cam_mov_state.mForward)
                d_eye += mForward;
            if (cam_mov_state.mBackward)
                d_eye -= mForward;
            if (cam_mov_state.mLeft)
                d_eye -= right;
            if (cam_mov_state.mRight)
                d_eye += right;
            if (cam_mov_state.mUp)
                d_eye += up;
            if (cam_mov_state.mDown)
                d_eye -= up;

            // Normalise speed
            if (glm::length(d_eye) != 0)
                d_eye /= glm::length(d_eye);

            const float ms = 0.5f;
            mEye += ms * glm::vec3{d_eye.x, d_eye.y, d_eye.z};
        }
    }
}