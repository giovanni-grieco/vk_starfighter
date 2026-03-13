#include "first_app.hpp"

#include "simple_render_system.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE // changes the range for 0 to 1
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

//std
#include <stdexcept>
#include <array>
#include <cassert>

namespace engine {

    FirstApp::FirstApp() {
        loadGameObjects();
    }

    FirstApp::~FirstApp() {}


    void FirstApp::loadGameObjects(){
        //std::vector<Model::Vertex> vertices = sierpinskyTriangleGenerator(5);
        std::vector<Model::Vertex> vertices = exampleTriangle();
        auto model = std::make_shared<Model>(device, vertices);

        auto triangle = GameObject::createGameObject();
        triangle.model = model;
        triangle.color = {.1f, .8f, .1f};
        triangle.transform2d.translation.x = .2f;
        triangle.transform2d.scale = {2.f, 0.5f};
        triangle.transform2d.rotation = 0.25f * glm::two_pi<float>();

        gameObjects.push_back(std::move(triangle));
    }


    void FirstApp::run() {
        SimpleRenderSystem simpleRenderSystem{device, renderer.getSwapChainRenderPass()};
        while (!window.shouldClose()){
            glfwPollEvents();
            if (auto commandBuffer = renderer.beginFrame()) {

                // we can add other stuff in the render pass.

                renderer.beginSwapChainRenderPass(commandBuffer);
                simpleRenderSystem.renderGameObjects(commandBuffer, gameObjects);
                renderer.endSwapChainRenderPass(commandBuffer);
                renderer.endFrame();
            }
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