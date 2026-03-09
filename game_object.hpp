#pragma once

#include "engine_model.hpp"
#include <memory>

namespace engine {

    struct Transform2dComponent{
        glm::vec2 translation{};
        glm::vec2 scale{1.f,1.f};
        float rotation;

        glm::mat2 mat2() { 
            const float s = glm::sin(rotation);
            const float c = glm::cos(rotation);
            glm::mat2 rotMatrix {{c,s},{-s,c}};
            glm::mat2 scaleMat  {{scale.x, .0f},{0.f, scale.y}}; //glm constructor takes columns, the first pair is a column
            return rotMatrix*scaleMat;
        }
    };

    class GameObject {
        public:
            using id_t = unsigned int; //similar to typedef

            static GameObject createGameObject() {
                static id_t currentId = 0;
                return GameObject{currentId++};
            }

            GameObject(const GameObject &) = delete;
            GameObject &operator=(const GameObject &) = delete;
            GameObject(GameObject&&) = default;
            GameObject &operator=(GameObject&&) = default;

            id_t getId() { return id;}

            std::shared_ptr<Model> model{};
            glm::vec3 color{};
            Transform2dComponent transform2d;

        private:
            id_t id;
            GameObject(id_t objId) : id{objId} {}
    };
}