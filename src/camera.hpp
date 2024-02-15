#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Camera {
private:
    // vectors are only updated when getViewMatrix() is called
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;

public:
    enum Direction {
        Forward, Backward, Left, Right
    };

    glm::vec3 position;

    float yaw;
    float pitch;

    float movementSpeed;
    float mouseSensitivity;
    float fov;

    Camera(float posX, float posY, float posZ, float yawInput, float pitchInput);

    glm::mat4 getViewMatrix();
    void move(Direction direction, float deltaTime);
    void processMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
};

#endif