#pragma once

#include "engine_window.hpp"
#include "engine_pipeline.hpp"
#include "engine_model.hpp"
#include "game_object.hpp"
#include "engine_renderer.hpp"
#include "engine_camera.hpp"
#include "engine_frame_info.hpp"

#include <memory>
#include <vector>

namespace engine {
    class SimpleRenderSystem {
        public:
            
            SimpleRenderSystem(Device& device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);
            ~SimpleRenderSystem();

            SimpleRenderSystem(const SimpleRenderSystem&) = delete;
            SimpleRenderSystem& operator=(const SimpleRenderSystem&) = delete;

            void renderGameObjects(FrameInfo &frameInfo);

        private:
            void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
            void createPipeline(VkRenderPass renderPass);

            Device &device;

            
            std::unique_ptr<Pipeline> pipeline;
            VkPipelineLayout pipelineLayout;
    };
}