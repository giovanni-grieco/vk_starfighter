#pragma once

#include <glm/gtc/matrix_transform.hpp>

struct PhysicsComponent {
    glm::vec3 velocity{0.0f};
    glm::vec3 acceleration{0.0f};
    float mass = 1.0f;
    float drag = 0.98f; // Space friction so you don't drift forever
    float boundingRadius = 1.0f;
};