#pragma once

#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include<GLFW/glfw3.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/hash.hpp>

#include<optional>
#include<vector>

#include "Camera.hpp"


namespace MyVulkanApp {

	struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    struct Vertex {
        alignas(16) glm::vec3 pos;
        alignas(16) glm::vec3 color;
        alignas(16) glm::vec2 texCoord;

        static VkVertexInputBindingDescription getBindingDescription() {
            VkVertexInputBindingDescription bindingDescription{};
            bindingDescription.binding = 1;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
            std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

            attributeDescriptions[0].binding = 1;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(Vertex, pos);

            attributeDescriptions[1].binding = 1;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(Vertex, color);

            attributeDescriptions[2].binding = 1;
            attributeDescriptions[2].location = 2;
            attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

            return attributeDescriptions;
        }

        bool operator==(const Vertex& other) const {
            return pos == other.pos && color == other.color && texCoord == other.texCoord;
        }
    };

    struct CubeMapVertex {
        alignas(16) glm::vec3 pos;
        alignas(16) glm::vec3 color;
        alignas(16) glm::vec3 cubeTexCoord;

        static VkVertexInputBindingDescription getBindingDescription() {
            VkVertexInputBindingDescription bindingDescription{};
            bindingDescription.binding = 2;
            bindingDescription.stride = sizeof(CubeMapVertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
            std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

            attributeDescriptions[0].binding = 2;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(CubeMapVertex, pos);

            attributeDescriptions[1].binding = 2;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(CubeMapVertex, color);

            attributeDescriptions[2].binding = 2;
            attributeDescriptions[2].location = 2;
            attributeDescriptions[2].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[2].offset = offsetof(CubeMapVertex, cubeTexCoord);

            return attributeDescriptions;
        }
        
    };

    struct UniformBufferObject {
        alignas(16) glm::mat4 model;
        alignas(16) glm::mat4 view;
        alignas(16) glm::mat4 proj;

        alignas(16) glm::vec3 camera_pos;
        alignas(16) glm::vec3 camera_dir;
        alignas(16) glm::vec3 camera_up;

        alignas(4)  int WIDTH;
        alignas(4)  int HEIGHT;
        alignas(4)  float time;
        alignas(4)  float fov;
    };

    static const bool enableValidationLayers = true;
    static const uint32_t WIDTH = 1200;
    static const uint32_t HEIGHT = 900;
    static const int MAX_FRAMES_IN_FLIGHT = 2;
    static bool IsFullscreen = false;
    static bool FullscreenUpdated = false;
    static double lastTime = 0.0;
    static int Frames = 0;
    static float TimeSpeed = 1.0f;
    static bool TimeStopped = false;
    static float lastX = 400, lastY = 300;
    static float yaw = 90.0f, pitch = 0.0;
    static bool firstMouse = true;
    static bool MouseHidden = true;

    static const std::string MODEL_PATH = "../models/viking_room.obj";
    static const std::string TEXTURE_PATH = "../textures/viking_room.png";

    static Camera camera{glm::vec3(0.0, 5.0, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 1.0, 0.0), glm::vec3(-1.0, 0.0, 0.0)};
    static bool IsRawAvail = false;

    static const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    static const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    static const std::vector<CubeMapVertex> cubeMapVertices = {

        // Positive X
        { { 1,  1, -1},  {1.0f, 0.0f, 0.0f},  { 1,  1, -1} }, 
        { { 1,  1,  1},  {1.0f, 0.0f, 0.0f},  { 1,  1,  1} },
        { { 1, -1,  1},  {1.0f, 0.0f, 0.0f},  { 1, -1,  1} },
        { { 1, -1,  1},  {1.0f, 0.0f, 0.0f},  { 1, -1,  1} },
        { { 1, -1, -1},  {1.0f, 0.0f, 0.0f},  { 1, -1, -1} },
        { { 1,  1, -1},  {1.0f, 0.0f, 0.0f},  { 1,  1, -1} },

        // Negative X
        { {-1,  1, -1},  {1.0f, 0.0f, 0.0f},  {-1,  1, -1} }, 
        { {-1, -1,  1},  {1.0f, 0.0f, 0.0f},  {-1, -1,  1} },
        { {-1,  1,  1},  {1.0f, 0.0f, 0.0f},  {-1,  1,  1} },
        { {-1, -1,  1},  {1.0f, 0.0f, 0.0f},  {-1, -1,  1} },
        { {-1,  1, -1},  {1.0f, 0.0f, 0.0f},  {-1,  1, -1} },
        { {-1, -1, -1},  {1.0f, 0.0f, 0.0f},  {-1, -1, -1} },

        // Positive Z
        { { 1,  1,  1},  {1.0f, 0.0f, 0.0f},  { 1,  1,  1} }, 
        { {-1,  1,  1},  {1.0f, 0.0f, 0.0f},  {-1,  1,  1} },
        { { 1, -1,  1},  {1.0f, 0.0f, 0.0f},  { 1, -1,  1} },
        { {-1,  1,  1},  {1.0f, 0.0f, 0.0f},  {-1,  1,  1} },
        { {-1, -1,  1},  {1.0f, 0.0f, 0.0f},  {-1, -1,  1} },
        { { 1, -1,  1},  {1.0f, 0.0f, 0.0f},  { 1, -1,  1} },

        // Negative Z
        { { 1,  1, -1},  {1.0f, 0.0f, 0.0f},  { 1,  1, -1} }, 
        { { 1, -1, -1},  {1.0f, 0.0f, 0.0f},  { 1, -1, -1} },
        { {-1,  1, -1},  {1.0f, 0.0f, 0.0f},  {-1,  1, -1} },
        { {-1,  1, -1},  {1.0f, 0.0f, 0.0f},  {-1,  1, -1} },
        { { 1, -1, -1},  {1.0f, 0.0f, 0.0f},  { 1, -1, -1} },
        { {-1, -1, -1},  {1.0f, 0.0f, 0.0f},  {-1, -1, -1} },

        // Positive Y
        { { 1,  1,  1},  {1.0f, 0.0f, 0.0f},  { 1,  1,  1} }, 
        { { 1,  1, -1},  {1.0f, 0.0f, 0.0f},  { 1,  1, -1} },
        { {-1,  1, -1},  {1.0f, 0.0f, 0.0f},  {-1,  1, -1} },
        { {-1,  1, -1},  {1.0f, 0.0f, 0.0f},  {-1,  1, -1} },
        { {-1,  1,  1},  {1.0f, 0.0f, 0.0f},  {-1,  1,  1} },
        { { 1,  1,  1},  {1.0f, 0.0f, 0.0f},  { 1,  1,  1} },

        // Negative Y
        { { 1, -1,  1},  {1.0f, 0.0f, 0.0f},  { 1, -1,  1} }, 
        { {-1, -1, -1},  {1.0f, 0.0f, 0.0f},  {-1, -1, -1} },
        { { 1, -1, -1},  {1.0f, 0.0f, 0.0f},  { 1, -1, -1} },
        { {-1, -1, -1},  {1.0f, 0.0f, 0.0f},  {-1, -1, -1} },
        { { 1, -1,  1},  {1.0f, 0.0f, 0.0f},  { 1, -1,  1} },
        { {-1, -1,  1},  {1.0f, 0.0f, 0.0f},  {-1, -1,  1} }
    };
}


namespace std {
    template<> struct hash<MyVulkanApp::Vertex> {
        size_t operator()(MyVulkanApp::Vertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex.pos) ^
                    (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^
                    (hash<glm::vec2>()(vertex.texCoord) << 1);
        }
    };
}