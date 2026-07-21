#pragma once

#include "engine_window.hpp"
#include "engine_pipeline.hpp"
#include "engine_model.hpp"
#include "entity.hpp"
#include "engine_renderer.hpp"
#include "engine_camera.hpp"
#include "engine_frame_info.hpp"
#include "system.hpp"

#include "components/point_light_component.hpp"

#include <memory>
#include <vector>

namespace engine {

    class PointLightSystem : ISystem {
        public:
            
            PointLightSystem(Device& device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);
            ~PointLightSystem();

            PointLightSystem(const PointLightSystem&) = delete;
            PointLightSystem& operator=(const PointLightSystem&) = delete;

            void start(Registry &registry) override;
            void update(Registry &registry, float dt) override;

            void render(Registry &registry, FrameInfo &frameInfo, GlobalUbo &ubo);

        private:
            void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
            void createPipeline(VkRenderPass renderPass);

            Device &device;

            
            std::unique_ptr<Pipeline> pipeline;
            VkPipelineLayout pipelineLayout;
    };
}