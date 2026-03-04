#include "engine_pipeline.hpp"

#include <fstream>
#include <stdexcept>
#include <iostream>


namespace engine {


    Pipeline::Pipeline(Device &device, const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo &configInfo) : device{device} {
        createGraphicsPipeline(vertFilepath, fragFilepath, configInfo);
    }
    
    std::vector<char> Pipeline::readFile(const std::string& filepath) {
        //open the file at the end to get the size of the file

        std::ifstream file(filepath, std::ios::ate | std::ios::binary);
        if (!file.is_open()){
            throw std::runtime_error("failed to open file: " + filepath);
        }

        size_t fileSize = static_cast<size_t>(file.tellg());
        std::vector<char> buffer(fileSize);
        file.seekg(0);
        file.read(buffer.data(), fileSize);
        file.close();
        return buffer;
    }

    void Pipeline::createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo &configInfo) {
        auto vertShaderCode = readFile(vertFilepath);
        auto fragShaderCode = readFile(fragFilepath);
        std::cout << "Vertex shader code size: " << vertShaderCode.size() << " bytes" << std::endl;
        std::cout << "Fragment shader code size: " << fragShaderCode.size() << " bytes" << std::endl;

    }

    void Pipeline::createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule){
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());
        if (vkCreateShaderModule(device.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS) {
            throw std::runtime_error("failed to create shader module");
        }
    }

    PipelineConfigInfo Pipeline::defaultPipelineConfigInfo(uint32_t width, uint32_t height) {
        PipelineConfigInfo configInfo{};

        return configInfo;
    }
};
