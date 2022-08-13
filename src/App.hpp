#pragma once

#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_RADIANS

#include "../external/tiny_obj_loader.h"
#include "../external/stb_image.h"

#include<glm/gtc/matrix_transform.hpp>

#include<GLFW/glfw3.h>
#include<glm/glm.hpp>

#include<iostream>
#include<stdexcept>
#include<cstdlib>
#include<cstring>
#include<sstream>
#include<vector>
#include<optional>
#include<set>
#include<array>
#include<cstdint>
#include<limits>
#include<algorithm>
#include<fstream>
#include<unordered_map>


#include "Camera.hpp"
#include "Settings.hpp"


namespace MyVulkanApp {
	class App 
    {
    public:
        void run();
    
    private:
        VkInstance instance;
        GLFWwindow* window;
        VkDebugUtilsMessengerEXT debugMessenger;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device;
        VkQueue graphicsQueue;
        VkSurfaceKHR surface;
        VkQueue presentQueue;

        VkSwapchainKHR oldswapChain = VK_NULL_HANDLE;
        VkSwapchainKHR swapChain = VK_NULL_HANDLE;
        
        std::vector<VkImage> swapChainImages;
        std::vector<VkImageView> swapChainImageViews;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
        VkRenderPass renderPass;

        VkPipelineLayout pipelineLayout;
        VkPipelineLayout skyboxPipelineLayout;
        VkPipeline graphicsPipeline;
        VkPipeline skyboxGraphicsPipeline;

        std::vector<VkFramebuffer> swapChainFramebuffers;
        VkCommandPool commandPool;

        std::vector<VkCommandBuffer> commandBuffers;
        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;

        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;

        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;

        VkBuffer CubeMapVertexBuffer;
        VkDeviceMemory CubeMapVertexBufferMemory;

        VkDescriptorSetLayout descriptorSetLayout;

        std::vector<VkBuffer> uniformBuffers;
        std::vector<VkDeviceMemory> uniformBuffersMemory;

        VkDescriptorPool descriptorPool;
        std::vector<VkDescriptorSet> descriptorSets;

        uint32_t mipLevels;
        uint32_t skyboxMipLevels;
        VkImage textureImage;
        VkDeviceMemory textureImageMemory;
        VkImageView textureImageView;
        VkSampler textureSampler;

        VkImage skyboxImage;
        VkDeviceMemory skyboxImageMemory;
        VkImageView skyboxImageView;
        VkSampler skyboxSampler;

        VkImage colorImage;
        VkDeviceMemory colorImageMemory;
        VkImageView colorImageView;

        VkImage depthImage;
        VkDeviceMemory depthImageMemory;
        VkImageView depthImageView;

        VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;

        UniformBufferObject ubo{glm::mat4(1.0), glm::mat4(1.0), glm::mat4(1.0), glm::vec3(0.0, 5.0, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 1.0, 0.0), 800, 600, 0.0f, 90.0f};

        bool framebufferResized = false;

        uint32_t currentFrame = 0;


        void initWindow();
        void initVulkan();
        void mainLoop();
        void cleanup();


        static void Keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void Mouse(GLFWwindow* window, int button, int action, int mods);
        static void CursorCallback(GLFWwindow* window, double xpos, double ypos);
        static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
        
        void showFPS(GLFWwindow *pWindow);
        
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
        void setupDebugMessenger();
        bool checkValidationLayerSupport();

        std::vector<const char*> getRequiredExtensions();
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        
        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback( VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                             VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                             const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                                             void* pUserData );

        void pickPhysicalDevice();
        bool isDeviceSuitable(VkPhysicalDevice device);
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        void createLogicalDevice();

		void createInstance();
        void createSurface();
        VkImageView createImageView( VkImage image, 
                                     VkFormat format, 
                                     VkImageViewType type, 
                                     VkImageAspectFlags aspectFlags, 
                                     uint32_t mipLevels, 
                                     uint32_t arrLayers );
        void createImageViews();

        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
        void createSwapChain();
        void cleanupSwapChain();
        void recreateSwapChain();

        static std::vector<char> readFile(const std::string& filename);

        void createRenderPass();
        void createFramebuffers();
        VkShaderModule createShaderModule(const std::vector<char>& code);
        void createGraphicsPipeline();
        void createSkyboxGraphicsPipeline();


        void createCommandPool();
        void createCommandBuffers();
        void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

        void createColorResources();
        void createDepthResources();
        VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
        VkFormat findDepthFormat();
        bool hasStencilComponent(VkFormat format);

        void drawFrame();

        void createSyncObjects();
        void createBuffer( VkDeviceSize size,
                           VkBufferUsageFlags usage, 
                           VkMemoryPropertyFlags properties, 
                           VkBuffer& buffer, 
                           VkDeviceMemory& bufferMemory );

        void loadModel(std::vector<Vertex>& verts, std::vector<uint32_t>& inds, const std::string model_path);

		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        template<typename T>
        void createVertexBuffer(const std::vector<T>& vert, VkBuffer& vertBuffer, VkDeviceMemory& vertBufferMemory);
        
        template<typename T>
        void createIndexBuffer(const std::vector<T>& ind, VkBuffer& indBuffer,  VkDeviceMemory& indBufferMemory);
        
        void createDescriptorSetLayout();
        void createDescriptorPool();
        void createDescriptorSets();
        void createUniformBuffers();
        void updateUniformBuffer(uint32_t currentImage);

        VkCommandBuffer beginSingleTimeCommands();
        void endSingleTimeCommands(VkCommandBuffer commandBuffer);

        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels, uint32_t arrLayers);
        void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t arrLayers);

        void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
        void createTextureImage();
        void createImage( uint32_t width, 
        				  uint32_t height, 
                          uint32_t mipLevels,
                          VkSampleCountFlagBits numSamples,
        				  VkFormat format, 
        				  VkImageTiling tiling, 
        				  VkImageUsageFlags usage, 
        				  VkMemoryPropertyFlags properties, 
        				  VkImage& image, 
        				  VkDeviceMemory& imageMemory, 
                          uint32_t arrLayers,
                          VkImageCreateFlags flags );

        void createTextureImageView();
        void createTextureSampler();

        void createSkybox();

        VkSampleCountFlagBits getMaxUsableSampleCount();

    };
}