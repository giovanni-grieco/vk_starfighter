#pragma once

#include "engine_window.hpp"
#include "engine_pipeline.hpp"
#include "engine_device.hpp"
#include "engine_swap_chain.hpp"
#include "engine_model.hpp"


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
            void loadModels();
            void createPipelineLayout();
            void createPipeline();
            void createCommandBuffers();
            void drawFrame();

            Window window {WIDTH, HEIGHT, "Vulkan Engine"};
            Device device {window};
            SwapChain swapChain{device, window.getExtent()};
            std::unique_ptr<Pipeline> pipeline;
            VkPipelineLayout pipelineLayout;
            std::vector<VkCommandBuffer> commandBuffers;
            std::unique_ptr<Model> model;


            static std::vector<Model::Vertex> sierpinskyTriangleGenerator(int depth);

    };
}