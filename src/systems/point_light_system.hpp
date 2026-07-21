#pragma once

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

    class PointLightSystem {
        public:
            
            PointLightSystem(Device& device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);
            ~PointLightSystem();

            PointLightSystem(const PointLightSystem&) = delete;
            PointLightSystem& operator=(const PointLightSystem&) = delete;
            void update(FrameInfo& frameInfo, GlobalUbo& ubo);
            void render(FrameInfo& frameInfo);

        private:
            void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
            void createPipeline(VkRenderPass renderPass);

            Device &device;

            
            std::unique_ptr<Pipeline> pipeline;
            VkPipelineLayout pipelineLayout;
    };
}