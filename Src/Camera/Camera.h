#pragma once

#include "../include/main.h"
using namespace glm;

typedef enum{
    LOCK_TARGET = 0,
    FREE_MOVE = 1,
}CameraType;

typedef enum{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
}CameraMovement;

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.05f;
const float ZOOM        =  45.0f;

class Camera{
public:
    vec3 m_position;
    vec3 m_target;
    vec3 m_dir;

    vec3 m_front;
    vec3 m_up;
    vec3 m_right;
    vec3 m_worldUp;
    
    // eular Angles
    float m_yaw;
    float m_pitch;
    float m_roll;
    
    // camera options
    float m_moveSpeed;
    float m_mouseSensity;
    float m_zoom;

    CameraType m_type;

    mat4 m_view;

    Camera(vec3 pos = vec3(0, 0, 0), vec3 up = vec3(0, 1, 0), float yaw = YAW, float pitch = PITCH);
    mat4 getViewMatrix();

    void setCameraType(CameraType type);

    void processKeyboard(CameraMovement direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void processMouseScroll(float yoffset);

private:
    void updateCameraVectors();
};