#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace engine {
    class Window {

        public:
            Window(int w, int h, std::string name);
            ~Window();
            
            
            bool shouldClose() { return glfwWindowShouldClose(window); } //inline
            VkExtent2D getExtent() {return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; } //inline
            bool wasWindowsResized() { return framebufferResized; } //inline
            void resetWindowResizedFlag() { framebufferResized = false; } //inline
            
            void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
            
            
            Window(const Window&) = delete;
            Window& operator=(const Window&) = delete;

        private:
            static void frameBufferResizeCallback(GLFWwindow* window, int width, int height);
            void initWindow();
            int width;
            int height;
            bool framebufferResized = false;

            std::string windowName;

            GLFWwindow* window;
    };
}