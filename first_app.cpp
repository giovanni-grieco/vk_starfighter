#include "first_app.hpp"

namespace engine {
    void FirstApp::run() {
        while (!window.shouldClose()){
            glfwPollEvents();
        }
    }
}