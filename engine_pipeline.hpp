#pragma once

#include <string>
#include <vector>
#include "engine_device.hpp"

namespace engine{

    struct PipelineConfigInfo {

    };

    class Pipeline {
        public:
            Pipeline(Device &device, const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo &configInfo);
            ~Pipeline(){};
            Pipeline(const Pipeline&) = delete;
            Pipeline& operator=(const Pipeline&) = delete;

            static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);
        private:
            Device &device; //Potentially memory unsafe but a pipeline will always be outlived by the device so it should be fine
            VkPipeline graphicsPipeline;
            VkShaderModule vertShaderModule;
            VkShaderModule fragShaderModule;

            static std::vector<char> readFile(const std::string& filepath);
            void createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo &configInfo);
            void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);
    };
}