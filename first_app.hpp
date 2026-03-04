#pragma once

#include "engine_window.hpp"
#include "engine_pipeline.hpp"
#include "engine_device.hpp"

namespace engine {
    class FirstApp {
        public:
            static constexpr int WIDTH = 800;
            static constexpr int HEIGHT = 600;
            void run();
        private:
            Window window {WIDTH, HEIGHT, "Vulkan Engine"};
            Device device {window};
            Pipeline pipeline{device, "shaders/simple_shader.vert.spv", "shaders/simple_shader.frag.spv", Pipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
    };
}