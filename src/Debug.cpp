#include "Debug.hpp"


std::ostream& MyVulkanApp::operator<<(std::ostream& os, const glm::vec3& v) {
    os << v.x << ", " << v.y << ", " << v.z;
    return os;
}


VkResult MyVulkanApp::CreateDebugUtilsMessengerEXT( VkInstance instance,
                                                    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
                                                    const VkAllocationCallbacks* pAllocator, 
                                                    VkDebugUtilsMessengerEXT* pDebugMessenger ) 
{
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr)
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    else
        return VK_ERROR_EXTENSION_NOT_PRESENT;
}


void MyVulkanApp::DestroyDebugUtilsMessengerEXT( VkInstance instance, 
                                                 VkDebugUtilsMessengerEXT debugMessenger, 
                                                 const VkAllocationCallbacks* pAllocator ) 
{    
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr)
        func(instance, debugMessenger, pAllocator);
}