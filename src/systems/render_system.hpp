#pragma once

#include "system.hpp"
#include "engine_window.hpp"
#include "engine_pipeline.hpp"
#include "engine_model.hpp"
#include "entity.hpp"
#include "engine_renderer.hpp"
#include "engine_camera.hpp"
#include "engine_frame_info.hpp"

#include <memory>
#include <vector>

namespace engine {
    class RenderSystem : ISystem {
        public:
            
            RenderSystem(Device& device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);
            ~RenderSystem();

            RenderSystem(const RenderSystem&) = delete;
            RenderSystem& operator=(const RenderSystem&) = delete;

            void start(Registry &registry) override;
            void update(Registry &registry, float dt) override;

            void render(Registry &registry, FrameInfo &frameInfo);
        
        private:
            void renderEntities(Registry &registry, FrameInfo &frameInfo);
            void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
            void createPipeline(VkRenderPass renderPass);

            Device &device;

            
            std::unique_ptr<Pipeline> pipeline;
            VkPipelineLayout pipelineLayout;
    };
}