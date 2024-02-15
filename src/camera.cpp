#include "camera.hpp"

Camera::Camera(float posX, float posY, float posZ, float yawInput, float pitchInput) {
    position = glm::vec3(posX, posY, posZ);
    front = glm::vec3(1.0f, 0.0f, 0.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    right = glm::vec3(0.0f, 0.0f, 1.0f);

    yaw = yawInput;
    pitch = pitchInput;

    movementSpeed = 2.5f;
    mouseSensitivity = 0.05f;
    fov = 45.0f;
}

glm::mat4 Camera::getViewMatrix() {
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    up = glm::normalize(glm::cross(right, front));

    return glm::lookAt(position, position + front, up);
}

void Camera::move(Direction direction, float deltaTime) {
    float velocity = movementSpeed * deltaTime;
    switch (direction) {
        case Forward:
            position += front * velocity;
            break;
        case Backward:
            position -= front * velocity;
            break;
        case Left:
            position -= right * velocity;
            break;
        case Right:
            position += right * velocity;
            break;
    }
}

void Camera::processMouseMovement(float xOffset, float yOffset, bool constrainPitch) {
    yaw += xOffset * mouseSensitivity;
    pitch += yOffset * mouseSensitivity;

    if (constrainPitch) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }
}