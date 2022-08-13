#pragma once

#define GLFW_INCLUDE_VULKAN
#include<GLFW/glfw3.h>

#include<array>

#include "Settings.hpp"


namespace MyVulkanApp {
	std::ostream& operator<<(std::ostream& os, const glm::vec3& v);

	VkResult CreateDebugUtilsMessengerEXT( VkInstance instance,
                                           const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
                                           const VkAllocationCallbacks* pAllocator, 
                                           VkDebugUtilsMessengerEXT* pDebugMessenger );

    void DestroyDebugUtilsMessengerEXT( VkInstance instance, 
                                        VkDebugUtilsMessengerEXT debugMessenger, 
                                        const VkAllocationCallbacks* pAllocator );
}