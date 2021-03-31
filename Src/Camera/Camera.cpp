#include "Camera.h"

Camera::Camera(vec3 pos, vec3 up, float yaw, float pitch)
    :m_position(pos),
    m_worldUp(up),
    m_yaw(yaw),
    m_pitch(pitch),
    m_front(0, 0, -1),
    m_moveSpeed(SPEED),
    m_mouseSensity(SENSITIVITY),
    m_zoom(ZOOM){

    m_type = FREE_MOVE;
    updateCameraVectors();
}

void Camera::updateCameraVectors(){
    // calculate the new Front vector
    vec3 front;
    front.x = cos(radians(m_yaw)) * cos(radians(m_pitch));
    front.y = sin(radians(m_pitch));
    front.z = sin(radians(m_yaw)) * cos(radians(m_pitch));
    m_front = normalize(front);
    // also re-calculate the Right and Up vector
    m_right = normalize(cross(m_front, m_worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    m_up    = normalize(cross(m_right, m_front));
}

mat4 Camera::getViewMatrix(){
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::setCameraType(CameraType type){
    m_type = type;
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime){
    float velocity = deltaTime * m_moveSpeed;

    switch(direction){
        case FORWARD: m_position += m_front * velocity; break;
        
        case BACKWARD: m_position -= m_front * velocity; break;

        case LEFT: m_position -= m_right * velocity; break;

        case RIGHT: m_position += m_right * velocity; break;

        default:break;
    }
}

void Camera::processMouseScroll(float yoffset){
    m_zoom -= (float)yoffset;
    if (m_zoom < 1.0f) m_zoom = 1.0f;
    
    if (m_zoom > 45.0f) m_zoom = 45.0f; 
}

void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= m_mouseSensity;
    yoffset *= m_mouseSensity;

    m_yaw   += xoffset;
    m_pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}