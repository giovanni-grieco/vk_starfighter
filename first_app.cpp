#include "first_app.hpp"

#include "simple_render_system.hpp"
#include "keyboard_movement_controller.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE // changes the range for 0 to 1
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

//std
#include <stdexcept>
#include <array>
#include <cassert>
#include <chrono>

namespace engine {

    FirstApp::FirstApp() {
        loadGameObjects();
    }

    FirstApp::~FirstApp() {}


    void FirstApp::loadGameObjects(){
        std::shared_ptr<Model> model = Model::createModelFromFile(device, "models/smooth_vase.obj");

        auto gameObject = GameObject::createGameObject();
        gameObject.model = model;
        gameObject.transform.translation = {0.f, 0.f, 0.f};
        gameObject.transform.scale = {.5f, .5f, .5f};
        gameObjects.push_back(std::move(gameObject));
    }

    void FirstApp::run() {
        SimpleRenderSystem simpleRenderSystem{device, renderer.getSwapChainRenderPass()};
        Camera camera{};

        auto viewerObject = GameObject::createGameObject();
        KeyboardMovementController cameraController{};

        auto currentTime = std::chrono::high_resolution_clock::now();

        while (!window.shouldClose()){
            glfwPollEvents();

            auto newTime = std::chrono::high_resolution_clock::now();

            float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
            
            currentTime = newTime;

            cameraController.moveInPlaneXZ(window.getGLFWwindow(), frameTime, viewerObject);
            camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);
            float aspect = renderer.getAspectRatio();
            //camera.setOrthographicProjection(-aspect, aspect, -1, 1, -1, 1);
            camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 100.f);
            if (auto commandBuffer = renderer.beginFrame()) {

                // we can add other stuff in the render pass.

                renderer.beginSwapChainRenderPass(commandBuffer);
                simpleRenderSystem.renderGameObjects(commandBuffer, gameObjects, camera);
                renderer.endSwapChainRenderPass(commandBuffer);
                renderer.endFrame();
            }
        }

        vkDeviceWaitIdle(device.device());
    }

}