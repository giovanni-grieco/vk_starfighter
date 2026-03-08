#include "first_app.hpp"

//std
#include <stdexcept>
#include <array>

namespace engine {

    FirstApp::FirstApp() {
        loadModels();
        createPipelineLayout();
        createPipeline();
        createCommandBuffers();
    }

    FirstApp::~FirstApp() {
        vkDestroyPipelineLayout(device.device(), pipelineLayout, nullptr);

    }

    void FirstApp::loadModels(){
        //std::vector<Model::Vertex> vertices = sierpinskyTriangleGenerator(5);
        std::vector<Model::Vertex> vertices = exampleTriangle();
        model = std::make_unique<Model>(device, vertices);
    }

    void FirstApp::createPipelineLayout() {
        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0;
        pipelineLayoutInfo.pSetLayouts = nullptr;
        pipelineLayoutInfo.pushConstantRangeCount = 0;
        pipelineLayoutInfo.pPushConstantRanges = nullptr;

        if (vkCreatePipelineLayout(device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
            throw std::runtime_error("failed to create pipeline layout!");
        }
    }

    void FirstApp::createPipeline() {
        auto pipelineConfig = Pipeline::defaultPipelineConfigInfo(swapChain.width(), swapChain.height());
        pipelineConfig.renderPass = swapChain.getRenderPass();
        pipelineConfig.pipelineLayout = pipelineLayout;
        pipeline = std::make_unique<Pipeline>(device, "shaders/simple_shader.vert.spv", "shaders/simple_shader.frag.spv", pipelineConfig);
    }

    void FirstApp::createCommandBuffers(){
        commandBuffers.resize(swapChain.imageCount()); 
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = device.getCommandPool();
        allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

        if (vkAllocateCommandBuffers(device.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate command buffers!");
        }

        for (int i=0; i < commandBuffers.size(); i++) {
            VkCommandBufferBeginInfo beginInfo{};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

            if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
                throw std::runtime_error("failed to begin recording command buffer!");
            }

            VkRenderPassBeginInfo renderPassInfo{};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = swapChain.getRenderPass();
            renderPassInfo.framebuffer = swapChain.getFrameBuffer(i);

            renderPassInfo.renderArea.offset = {0, 0};
            renderPassInfo.renderArea.extent = swapChain.getSwapChainExtent();

            std::array<VkClearValue, 2> clearValues{};
            clearValues[0].color = {0.01f, 0.01f, 0.01f, 1.0f};
            clearValues[1].depthStencil = {1.0f, 0};
            renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
            renderPassInfo.pClearValues = clearValues.data();

            vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
            pipeline->bind(commandBuffers[i]);

            model->bind(commandBuffers[i]);
            model->draw(commandBuffers[i]);

            vkCmdEndRenderPass(commandBuffers[i]);
            if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to record command buffer!");
            }
        }
    }

    void FirstApp::drawFrame() {
        uint32_t imageIndex;
        auto result = swapChain.acquireNextImage(&imageIndex);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to acquire swap chain image!");
        }

        result = swapChain.submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to present swap chain image!");
        }
    }


    void FirstApp::run() {
        while (!window.shouldClose()){
            glfwPollEvents();
            drawFrame();
        }

        vkDeviceWaitIdle(device.device());
    }

    std::vector<Model::Vertex> FirstApp::exampleTriangle(){
        std::vector<Model::Vertex> vertices {
            {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
            {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
            {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
        };
        return vertices;
    }

    std::vector<Model::Vertex> FirstApp::sierpinskyTriangleGenerator(int depth){
        std::vector<Model::Vertex> vertices;
        vertices.push_back({{0.0f, -0.5f}});
        vertices.push_back({{0.5f, 0.5f}});
        vertices.push_back({{-0.5f, 0.5f}});

        for (int i=0; i < depth; i++) {
            std::vector<Model::Vertex> newVertices;
            for (int j=0; j < vertices.size(); j+=3) {
                auto v1 = vertices[j];
                auto v2 = vertices[j+1];
                auto v3 = vertices[j+2];

                auto mid12 = Model::Vertex{{(v1.position.x + v2.position.x) / 2.0f, (v1.position.y + v2.position.y) / 2.0f}};
                auto mid23 = Model::Vertex{{(v2.position.x + v3.position.x) / 2.0f, (v2.position.y + v3.position.y) / 2.0f}};
                auto mid31 = Model::Vertex{{(v3.position.x + v1.position.x) / 2.0f, (v3.position.y + v1.position.y) / 2.0f}};

                newVertices.push_back(v1);
                newVertices.push_back(mid12);
                newVertices.push_back(mid31);

                newVertices.push_back(v2);
                newVertices.push_back(mid23);
                newVertices.push_back(mid12);

                newVertices.push_back(v3);
                newVertices.push_back(mid31);
                newVertices.push_back(mid23);
            }
            vertices = newVertices;
        }

        return vertices;
    }
}