#pragma once

#include "engine_window.hpp"
#include "engine_model.hpp"
#include "game_object.hpp"
#include "engine_renderer.hpp"

#include <memory>
#include <vector>

namespace engine {
    class FirstApp {
        public:
            static constexpr int WIDTH = 800;
            static constexpr int HEIGHT = 600;
            
            FirstApp();
            ~FirstApp();

            FirstApp(const FirstApp&) = delete;
            FirstApp& operator=(const FirstApp&) = delete;
            void run();
        private:
            void loadGameObjects();

            Window window {WIDTH, HEIGHT, "Vulkan Engine"};
            Device device {window};
            Renderer renderer {window, device};


            std::vector<GameObject> gameObjects;

            static std::unique_ptr<Model> createCubeModel(Device& device, glm::vec3 offset);

    };
}