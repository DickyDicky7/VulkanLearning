    #define VK_USE_PLATFORM_WIN32_KHR
//  #define VK_USE_PLATFORM_WIN32_KHR
    #define GLFW_INCLUDE_VULKAN
//  #define GLFW_INCLUDE_VULKAN
    #include <GLFW/glfw3.h>
//  #include <GLFW/glfw3.h>
    #define GLFW_EXPOSE_NATIVE_WIN32
//  #define GLFW_EXPOSE_NATIVE_WIN32
    #include <GLFW/glfw3native.h>
//  #include <GLFW/glfw3native.h>

  #include <optional>
//#include <optional>
  #include <iostream>
//#include <iostream>
  #include <vector>
//#include <vector>
  #include <set>
//#include <set>
  #include <cstdint>
//#include <cstdint>
  #include <limits>
//#include <limits>
  #include <algorithm>
//#include <algorithm>


const std::vector<const char*> validationLayers =
{
    "VK_LAYER_KHRONOS_validation",
//  "VK_LAYER_KHRONOS_validation",
};
#ifdef    NDEBUG
const bool enableValidationLayers = 0;
#else
const bool enableValidationLayers = 1;
#endif // NDEBUG

const std::vector<const char*> deviceExtensions =
{
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
//  VK_KHR_SWAPCHAIN_EXTENSION_NAME,
};

static inline bool CheckSupportOfValidationLayers()
{
    std::uint32_t layerCount = 0;
//  std::uint32_t layerCount = 0;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
//  vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
//  std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
//  vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const auto& validationLayer : validationLayers)
//  for (const auto& validationLayer : validationLayers)
    {
        bool layerFound = false;
//      bool layerFound = false;
        for (const auto& availableLayer : availableLayers)
//      for (const auto& availableLayer : availableLayers)
        {
            if (std::strcmp(validationLayer, availableLayer.layerName) == 0)
//          if (std::strcmp(validationLayer, availableLayer.layerName) == 0)
            {
                layerFound = true;
//              layerFound = true;
                break;
//              break;
            }
        }
        if (!layerFound)
//      if (!layerFound)
        {
            return false;
//          return false;
        }
    }

    return true;
//  return true;
}

static inline std::vector<const char*> GetRequiredExtensions()
{
    std::uint32_t enabledExtensionCount = 0;
//  std::uint32_t enabledExtensionCount = 0;
    const char* const* ppEnabledExtensionNames;
//  const char* const* ppEnabledExtensionNames;
    ppEnabledExtensionNames = glfwGetRequiredInstanceExtensions(&enabledExtensionCount);
//  ppEnabledExtensionNames = glfwGetRequiredInstanceExtensions(&enabledExtensionCount);

    std::vector<const char*> extensions(ppEnabledExtensionNames, ppEnabledExtensionNames + enabledExtensionCount);
//  std::vector<const char*> extensions(ppEnabledExtensionNames, ppEnabledExtensionNames + enabledExtensionCount);

    if (enableValidationLayers)
    {
        extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
//      extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
//  return extensions;
}

static
  VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
//VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
{
    if (messageSeverity >= VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
    {
        std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl << std::endl;
//      std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl << std::endl;
    }
        return VK_FALSE;
//      return VK_FALSE;
}

struct QueueFamilyIndices
{
    std::optional<std::uint32_t> graphicsFamily;
//  std::optional<std::uint32_t> graphicsFamily;
    std::optional<std::uint32_t>  presentFamily;
//  std::optional<std::uint32_t>  presentFamily;
};

struct SwapChainSupportDetails
{
    std::vector<VkSurfaceFormatKHR> vkSurfaceFormatKHRs;
//  std::vector<VkSurfaceFormatKHR> vkSurfaceFormatKHRs;
    std::vector<VkPresentModeKHR> vkPresentModeKHRs;
//  std::vector<VkPresentModeKHR> vkPresentModeKHRs;
    VkSurfaceCapabilitiesKHR vkSurfaceCapabilitiesKHR;
//  VkSurfaceCapabilitiesKHR vkSurfaceCapabilitiesKHR;
};

struct SceneData
{
    std::vector<VkImage> swapChainImages;
//  std::vector<VkImage> swapChainImages;
    VkQueue vkPresentQueue = VK_NULL_HANDLE;
//  VkQueue vkPresentQueue = VK_NULL_HANDLE;
    VkQueue vkGraphicsQueue = VK_NULL_HANDLE;
//  VkQueue vkGraphicsQueue = VK_NULL_HANDLE;
    VkDevice vkDevice = VK_NULL_HANDLE;
//  VkDevice vkDevice = VK_NULL_HANDLE;
    VkPhysicalDevice vkPhysicalDevice = VK_NULL_HANDLE;
//  VkPhysicalDevice vkPhysicalDevice = VK_NULL_HANDLE;
    VkSwapchainKHR vkSwapchainKHR = VK_NULL_HANDLE;
//  VkSwapchainKHR vkSwapchainKHR = VK_NULL_HANDLE;
    VkDebugUtilsMessengerEXT debugMessenger;
//  VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR vkSurfaceKHR = VK_NULL_HANDLE;
//  VkSurfaceKHR vkSurfaceKHR = VK_NULL_HANDLE;
    VkInstance  vkInstance;
//  VkInstance  vkInstance;
    GLFWwindow* glfwWindow;
//  GLFWwindow* glfwWindow;
    const char* windowTitle;
//  const char* windowTitle;
    VkExtent2D swapChainExtent2D   ;
//  VkExtent2D swapChainExtent2D   ;
    VkFormat   swapChainImageFormat;
//  VkFormat   swapChainImageFormat;
    std::uint32_t windowW = 800;
    std::uint32_t windowH = 600;
};

static inline bool IsComplete(const QueueFamilyIndices& queueFamilyIndices)
{
    return queueFamilyIndices.graphicsFamily.has_value() && queueFamilyIndices.presentFamily.has_value();
//  return queueFamilyIndices.graphicsFamily.has_value() && queueFamilyIndices.presentFamily.has_value();
}

static inline QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice vkPhysicalDevice, VkSurfaceKHR vkSurfaceKHR)
{
    QueueFamilyIndices queueFamilyIndices{};
//  QueueFamilyIndices queueFamilyIndices{};

    std::uint32_t queueFamilyCount = 0;
//  std::uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(vkPhysicalDevice, &queueFamilyCount, nullptr);
//  vkGetPhysicalDeviceQueueFamilyProperties(vkPhysicalDevice, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
//  std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(vkPhysicalDevice, &queueFamilyCount, queueFamilies.data());
//  vkGetPhysicalDeviceQueueFamilyProperties(vkPhysicalDevice, &queueFamilyCount, queueFamilies.data());

    std::uint32_t i = 0;
//  std::uint32_t i = 0;
    for (const VkQueueFamilyProperties& queueFamily : queueFamilies)
//  for (const VkQueueFamilyProperties& queueFamily : queueFamilies)
    {
        if (queueFamily.queueFlags & VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT)
//      if (queueFamily.queueFlags & VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT)
        {
            queueFamilyIndices.graphicsFamily = i;
//          queueFamilyIndices.graphicsFamily = i;
        }
        VkBool32 presentSupport = false;
//      VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(vkPhysicalDevice, i, vkSurfaceKHR, &presentSupport);
//      vkGetPhysicalDeviceSurfaceSupportKHR(vkPhysicalDevice, i, vkSurfaceKHR, &presentSupport);
        if (presentSupport)
//      if (presentSupport)
        {
            queueFamilyIndices.presentFamily = i;
//          queueFamilyIndices.presentFamily = i;
        }
        if (IsComplete(queueFamilyIndices))
//      if (IsComplete(queueFamilyIndices))
        {
            break;
//          break;
        }
        ++i;
//      ++i;
    }

    return queueFamilyIndices;
//  return queueFamilyIndices;
}

static inline SwapChainSupportDetails QuerySwapChainSupportDetails(VkPhysicalDevice vkPhysicalDevice, VkSurfaceKHR vkSurfaceKHR)
{
    SwapChainSupportDetails details;
//  SwapChainSupportDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vkPhysicalDevice, vkSurfaceKHR, &details.vkSurfaceCapabilitiesKHR);
//  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vkPhysicalDevice, vkSurfaceKHR, &details.vkSurfaceCapabilitiesKHR);

    std::uint32_t surfaceFormatCount = 0;
//  std::uint32_t surfaceFormatCount = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR(vkPhysicalDevice, vkSurfaceKHR, &surfaceFormatCount, nullptr);
//  vkGetPhysicalDeviceSurfaceFormatsKHR(vkPhysicalDevice, vkSurfaceKHR, &surfaceFormatCount, nullptr);
    if (surfaceFormatCount != 0)
//  if (surfaceFormatCount != 0)
    {
        details.vkSurfaceFormatKHRs.resize(surfaceFormatCount);
//      details.vkSurfaceFormatKHRs.resize(surfaceFormatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(vkPhysicalDevice, vkSurfaceKHR, &surfaceFormatCount, details.vkSurfaceFormatKHRs.data());
//      vkGetPhysicalDeviceSurfaceFormatsKHR(vkPhysicalDevice, vkSurfaceKHR, &surfaceFormatCount, details.vkSurfaceFormatKHRs.data());
    }

    std::uint32_t presentModeCount = 0;
//  std::uint32_t presentModeCount = 0;
    vkGetPhysicalDeviceSurfacePresentModesKHR(vkPhysicalDevice, vkSurfaceKHR, &presentModeCount, nullptr);
//  vkGetPhysicalDeviceSurfacePresentModesKHR(vkPhysicalDevice, vkSurfaceKHR, &presentModeCount, nullptr);
    if (presentModeCount != 0)
//  if (presentModeCount != 0)
    {
        details.vkPresentModeKHRs.resize(presentModeCount);
//      details.vkPresentModeKHRs.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(vkPhysicalDevice, vkSurfaceKHR, &presentModeCount, details.vkPresentModeKHRs.data());
//      vkGetPhysicalDeviceSurfacePresentModesKHR(vkPhysicalDevice, vkSurfaceKHR, &presentModeCount, details.vkPresentModeKHRs.data());
    }

    return details;
//  return details;
}

static inline VkSurfaceFormatKHR ChooseSwapChainVkSurfaceFormatKHR(const std::vector<VkSurfaceFormatKHR>& availableVkSurfaceFormatKHRs)
{
    for (const VkSurfaceFormatKHR& availableVkSurfaceFormatKHR : availableVkSurfaceFormatKHRs)
//  for (const VkSurfaceFormatKHR& availableVkSurfaceFormatKHR : availableVkSurfaceFormatKHRs)
    {
        if (availableVkSurfaceFormatKHR.format == VkFormat::VK_FORMAT_B8G8R8A8_SRGB && availableVkSurfaceFormatKHR.colorSpace == VkColorSpaceKHR::VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
//      if (availableVkSurfaceFormatKHR.format == VkFormat::VK_FORMAT_B8G8R8A8_SRGB && availableVkSurfaceFormatKHR.colorSpace == VkColorSpaceKHR::VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
        {
            return availableVkSurfaceFormatKHR;
//          return availableVkSurfaceFormatKHR;
        }
    }

    return availableVkSurfaceFormatKHRs[0];
//  return availableVkSurfaceFormatKHRs[0];
}

static inline VkPresentModeKHR ChooseSwapChainVkPresentModeKHR(const std::vector<VkPresentModeKHR> availableVkPresentModeKHRs)
{
    for (const VkPresentModeKHR& availableVkPresentModeKHR : availableVkPresentModeKHRs)
//  for (const VkPresentModeKHR& availableVkPresentModeKHR : availableVkPresentModeKHRs)
    {
        if (availableVkPresentModeKHR == VkPresentModeKHR::VK_PRESENT_MODE_MAILBOX_KHR)
//      if (availableVkPresentModeKHR == VkPresentModeKHR::VK_PRESENT_MODE_MAILBOX_KHR)
        {
            return availableVkPresentModeKHR;
//          return availableVkPresentModeKHR;
        }
    }

    return VkPresentModeKHR::VK_PRESENT_MODE_FIFO_KHR;
//  return VkPresentModeKHR::VK_PRESENT_MODE_FIFO_KHR;
}

static inline VkExtent2D ChooseSwapChainVkExtent2D(const VkSurfaceCapabilitiesKHR& availableVkSurfaceCapabilitiesKHR, GLFWwindow* glfwWindow)
{
    if (availableVkSurfaceCapabilitiesKHR.currentExtent.width != (std::numeric_limits<std::uint32_t>::max)())
//  if (availableVkSurfaceCapabilitiesKHR.currentExtent.width != (std::numeric_limits<std::uint32_t>::max)())
    {
        return availableVkSurfaceCapabilitiesKHR.currentExtent;
//      return availableVkSurfaceCapabilitiesKHR.currentExtent;
    }
    else
    {
        int w;
//      int w;
        int h;
//      int h;
        glfwGetFramebufferSize(glfwWindow, &w, &h);
//      glfwGetFramebufferSize(glfwWindow, &w, &h);
        VkExtent2D actualVkExtent2D
//      VkExtent2D actualVkExtent2D
        { 
            .width  = std::clamp(static_cast<std::uint32_t>(w), availableVkSurfaceCapabilitiesKHR.minImageExtent.width , availableVkSurfaceCapabilitiesKHR.maxImageExtent.width ),
//          .width  = std::clamp(static_cast<std::uint32_t>(w), availableVkSurfaceCapabilitiesKHR.minImageExtent.width , availableVkSurfaceCapabilitiesKHR.maxImageExtent.width ),
            .height = std::clamp(static_cast<std::uint32_t>(h), availableVkSurfaceCapabilitiesKHR.minImageExtent.height, availableVkSurfaceCapabilitiesKHR.maxImageExtent.height),
//          .height = std::clamp(static_cast<std::uint32_t>(h), availableVkSurfaceCapabilitiesKHR.minImageExtent.height, availableVkSurfaceCapabilitiesKHR.maxImageExtent.height),
        };
        return actualVkExtent2D;
//      return actualVkExtent2D;
    }
}

static inline bool CheckDeviceExtensionsSupport(VkPhysicalDevice vkPhysicalDevice)
{
    std::uint32_t deviceExtensionsCount = 0;
//  std::uint32_t deviceExtensionsCount = 0;
    vkEnumerateDeviceExtensionProperties(vkPhysicalDevice, nullptr, &deviceExtensionsCount, nullptr);
//  vkEnumerateDeviceExtensionProperties(vkPhysicalDevice, nullptr, &deviceExtensionsCount, nullptr);

    std::vector<VkExtensionProperties> availableDeviceExtensions(deviceExtensionsCount);
//  std::vector<VkExtensionProperties> availableDeviceExtensions(deviceExtensionsCount);
    vkEnumerateDeviceExtensionProperties(vkPhysicalDevice, nullptr, &deviceExtensionsCount, availableDeviceExtensions.data());
//  vkEnumerateDeviceExtensionProperties(vkPhysicalDevice, nullptr, &deviceExtensionsCount, availableDeviceExtensions.data());

    std::set<std::string> requiredDeviceExtensions(deviceExtensions.begin(), deviceExtensions.end());
//  std::set<std::string> requiredDeviceExtensions(deviceExtensions.begin(), deviceExtensions.end());

    for (const VkExtensionProperties& vkExtensionProperties : availableDeviceExtensions)
//  for (const VkExtensionProperties& vkExtensionProperties : availableDeviceExtensions)
    {
        requiredDeviceExtensions.erase(vkExtensionProperties.extensionName);
//      requiredDeviceExtensions.erase(vkExtensionProperties.extensionName);
    }

    return requiredDeviceExtensions.empty();
//  return requiredDeviceExtensions.empty();
}

static inline bool IsVkPhysicalDeviceSuitable(VkPhysicalDevice vkPhysicalDevice, VkSurfaceKHR vkSurfaceKHR)
{
//    VkPhysicalDeviceProperties vkPhysicalDeviceProperties;
////  VkPhysicalDeviceProperties vkPhysicalDeviceProperties;
//    vkGetPhysicalDeviceProperties(vkPhysicalDevice, &vkPhysicalDeviceProperties);
////  vkGetPhysicalDeviceProperties(vkPhysicalDevice, &vkPhysicalDeviceProperties);
//
//    VkPhysicalDeviceFeatures vkPhysicalDeviceFeatures;
////  VkPhysicalDeviceFeatures vkPhysicalDeviceFeatures;
//    vkGetPhysicalDeviceFeatures(vkPhysicalDevice, &vkPhysicalDeviceFeatures);
////  vkGetPhysicalDeviceFeatures(vkPhysicalDevice, &vkPhysicalDeviceFeatures);
//
//    return vkPhysicalDeviceProperties.deviceType == VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && vkPhysicalDeviceFeatures.geometryShader;
////  return vkPhysicalDeviceProperties.deviceType == VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && vkPhysicalDeviceFeatures.geometryShader;

//    return true;
////  return true;

    const QueueFamilyIndices& queueFamilyIndices = FindQueueFamilies(vkPhysicalDevice, vkSurfaceKHR);
//  const QueueFamilyIndices& queueFamilyIndices = FindQueueFamilies(vkPhysicalDevice, vkSurfaceKHR);

    bool deviceExtensionsSupported = CheckDeviceExtensionsSupport(vkPhysicalDevice);
//  bool deviceExtensionsSupported = CheckDeviceExtensionsSupport(vkPhysicalDevice);

    bool swapChainAdequate = false;
//  bool swapChainAdequate = false;
    if (deviceExtensionsSupported)
//  if (deviceExtensionsSupported)
    {
        SwapChainSupportDetails swapChainSupportDetails = QuerySwapChainSupportDetails(vkPhysicalDevice, vkSurfaceKHR);
//      SwapChainSupportDetails swapChainSupportDetails = QuerySwapChainSupportDetails(vkPhysicalDevice, vkSurfaceKHR);
        swapChainAdequate = !swapChainSupportDetails.vkSurfaceFormatKHRs.empty() && !swapChainSupportDetails.vkPresentModeKHRs.empty();
//      swapChainAdequate = !swapChainSupportDetails.vkSurfaceFormatKHRs.empty() && !swapChainSupportDetails.vkPresentModeKHRs.empty();
    }

    return IsComplete(queueFamilyIndices) && deviceExtensionsSupported && swapChainAdequate;
//  return IsComplete(queueFamilyIndices) && deviceExtensionsSupported && swapChainAdequate;
}

static inline void InitWindow(SceneData& sd)
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
//  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
//  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    sd.glfwWindow = glfwCreateWindow(sd.windowW, sd.windowH, sd.windowTitle, nullptr, nullptr);
//  sd.glfwWindow = glfwCreateWindow(sd.windowW, sd.windowH, sd.windowTitle, nullptr, nullptr);    
}

static inline void InitVulkan(SceneData& sd)
{
    if (enableValidationLayers && !CheckSupportOfValidationLayers())
    {
        throw std::runtime_error(std::format("validation layers requested but not available!"));
//      throw std::runtime_error(std::format("validation layers requested but not available!"));
    }

    // Create Vulkan Instance - connection between application and Vulkan driver
    // Create Vulkan Instance - connection between application and Vulkan driver
    VkApplicationInfo vkApplicationInfo
    {
        .sType              = VkStructureType::VK_STRUCTURE_TYPE_APPLICATION_INFO,
//      .sType              = VkStructureType::VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName   = "My First Vulkan Application",
//      .pApplicationName   = "My First Vulkan Application",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
//      .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName        = "No Engine",
//      .pEngineName        = "No Engine",
        .engineVersion      = VK_MAKE_VERSION(1, 0, 0),
//      .engineVersion      = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion         = VK_API_VERSION_1_0,
//      .apiVersion         = VK_API_VERSION_1_0,
    };

    const std::vector<const char*>& requiredExtensions = GetRequiredExtensions();
//  const std::vector<const char*>& requiredExtensions = GetRequiredExtensions();
    std::uint32_t enabledExtensionCount = static_cast<std::uint32_t>(requiredExtensions.size());
//  std::uint32_t enabledExtensionCount = static_cast<std::uint32_t>(requiredExtensions.size());
    const char* const* ppEnabledExtensionNames = requiredExtensions.data();
//  const char* const* ppEnabledExtensionNames = requiredExtensions.data();

    std::uint32_t enabledLayerCount = 0;
//  std::uint32_t enabledLayerCount = 0;
    const char* const* ppEnabledLayerNames;
//  const char* const* ppEnabledLayerNames;
    ppEnabledLayerNames = nullptr;
//  ppEnabledLayerNames = nullptr;

    if (enableValidationLayers)
    {
        enabledLayerCount = static_cast<std::uint32_t>(validationLayers.size());
//      enabledLayerCount = static_cast<std::uint32_t>(validationLayers.size());
        ppEnabledLayerNames = validationLayers.data();
//      ppEnabledLayerNames = validationLayers.data();
    }

    VkInstanceCreateInfo vkInstanceCreateInfo
    {
        .sType                   = VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
//      .sType                   = VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo        = &vkApplicationInfo,
//      .pApplicationInfo        = &vkApplicationInfo,
        .  enabledLayerCount     =   enabledLayerCount,
//      .  enabledLayerCount     =   enabledLayerCount,
        .ppEnabledLayerNames     = ppEnabledLayerNames,
//      .ppEnabledLayerNames     = ppEnabledLayerNames,
        .  enabledExtensionCount =   enabledExtensionCount,
//      .  enabledExtensionCount =   enabledExtensionCount,
        .ppEnabledExtensionNames = ppEnabledExtensionNames,
//      .ppEnabledExtensionNames = ppEnabledExtensionNames,
    };

    VkDebugUtilsMessengerCreateInfoEXT
    vkDebugUtilsMessengerCreateInfoEXTMain{};
    if (enableValidationLayers)
    {
        vkDebugUtilsMessengerCreateInfoEXTMain.sType = VkStructureType::VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
//      vkDebugUtilsMessengerCreateInfoEXTMain.sType = VkStructureType::VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
        vkDebugUtilsMessengerCreateInfoEXTMain.messageSeverity = VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
//      vkDebugUtilsMessengerCreateInfoEXTMain.messageSeverity = VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
        vkDebugUtilsMessengerCreateInfoEXTMain.messageType = VkDebugUtilsMessageTypeFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VkDebugUtilsMessageTypeFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VkDebugUtilsMessageTypeFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
//      vkDebugUtilsMessengerCreateInfoEXTMain.messageType = VkDebugUtilsMessageTypeFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VkDebugUtilsMessageTypeFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VkDebugUtilsMessageTypeFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
        vkDebugUtilsMessengerCreateInfoEXTMain.pfnUserCallback = DebugCallback,
//      vkDebugUtilsMessengerCreateInfoEXTMain.pfnUserCallback = DebugCallback,
        vkDebugUtilsMessengerCreateInfoEXTMain.pUserData = nullptr, // Optional
//      vkDebugUtilsMessengerCreateInfoEXTMain.pUserData = nullptr, // Optional

        vkInstanceCreateInfo.pNext = &vkDebugUtilsMessengerCreateInfoEXTMain;
//      vkInstanceCreateInfo.pNext = &vkDebugUtilsMessengerCreateInfoEXTMain;
    }

    VkResult vkResult = vkCreateInstance(&vkInstanceCreateInfo, nullptr, &sd.vkInstance);
//  VkResult vkResult = vkCreateInstance(&vkInstanceCreateInfo, nullptr, &sd.vkInstance);

    if (vkResult == VkResult::VK_SUCCESS)
    {
        
    }
    else
    {
        throw std::runtime_error(std::format("!create vulkan instance failure! reason: {}", static_cast<std::int32_t>(vkResult)));
//      throw std::runtime_error(std::format("!create vulkan instance failure! reason: {}", static_cast<std::int32_t>(vkResult)));
    }


    if (enableValidationLayers)
    {
        VkDebugUtilsMessengerCreateInfoEXT vkDebugUtilsMessengerCreateInfoEXT
        {
            .sType = VkStructureType::VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
//          .sType = VkStructureType::VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
            .messageSeverity = VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
//          .messageSeverity = VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
            .messageType = VkDebugUtilsMessageTypeFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VkDebugUtilsMessageTypeFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VkDebugUtilsMessageTypeFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
//          .messageType = VkDebugUtilsMessageTypeFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VkDebugUtilsMessageTypeFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VkDebugUtilsMessageTypeFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
            .pfnUserCallback = DebugCallback,
//          .pfnUserCallback = DebugCallback,
            .pUserData = nullptr, // Optional
//          .pUserData = nullptr, // Optional
        };

        PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(sd.vkInstance, "vkCreateDebugUtilsMessengerEXT");
//      PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(sd.vkInstance, "vkCreateDebugUtilsMessengerEXT");
        VkResult createDebugUtilsMessengerEXTResult;
//      VkResult createDebugUtilsMessengerEXTResult;
        if (vkCreateDebugUtilsMessengerEXT != nullptr)
//      if (vkCreateDebugUtilsMessengerEXT != nullptr)
        {
            createDebugUtilsMessengerEXTResult  = vkCreateDebugUtilsMessengerEXT(sd.vkInstance, &vkDebugUtilsMessengerCreateInfoEXT, nullptr, &sd.debugMessenger);
//          createDebugUtilsMessengerEXTResult  = vkCreateDebugUtilsMessengerEXT(sd.vkInstance, &vkDebugUtilsMessengerCreateInfoEXT, nullptr, &sd.debugMessenger);
        }
        else
        {
            createDebugUtilsMessengerEXTResult  = VkResult::VK_ERROR_EXTENSION_NOT_PRESENT;
//          createDebugUtilsMessengerEXTResult  = VkResult::VK_ERROR_EXTENSION_NOT_PRESENT;
        }
        if (createDebugUtilsMessengerEXTResult != VkResult::VK_SUCCESS)
//      if (createDebugUtilsMessengerEXTResult != VkResult::VK_SUCCESS)
        {
            throw std::runtime_error(std::format("failed to set up debug messenger! reason: {}", static_cast<std::int32_t>(createDebugUtilsMessengerEXTResult)));
//          throw std::runtime_error(std::format("failed to set up debug messenger! reason: {}", static_cast<std::int32_t>(createDebugUtilsMessengerEXTResult)));
        }
    }





/*
    VkWin32SurfaceCreateInfoKHR vkWin32SurfaceCreateInfoKHR
    {
        .sType = VkStructureType::VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
//      .sType = VkStructureType::VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
        .hinstance = GetModuleHandle(nullptr),
//      .hinstance = GetModuleHandle(nullptr),
        .hwnd = glfwGetWin32Window(sd.glfwWindow),
//      .hwnd = glfwGetWin32Window(sd.glfwWindow),
    };
    if (VkResult vkResult = vkCreateWin32SurfaceKHR(sd.vkInstance, &vkWin32SurfaceCreateInfoKHR, nullptr, &sd.vkSurfaceKHR); vkResult != VkResult::VK_SUCCESS)
//  if (VkResult vkResult = vkCreateWin32SurfaceKHR(sd.vkInstance, &vkWin32SurfaceCreateInfoKHR, nullptr, &sd.vkSurfaceKHR); vkResult != VkResult::VK_SUCCESS)
    {
        throw std::runtime_error(std::format("failed to create window surface! reason: {}", static_cast<std::int32_t>(vkResult)));
//      throw std::runtime_error(std::format("failed to create window surface! reason: {}", static_cast<std::int32_t>(vkResult)));
    }
*/
    if (VkResult vkResult = glfwCreateWindowSurface(sd.vkInstance, sd.glfwWindow, nullptr, &sd.vkSurfaceKHR); vkResult != VkResult::VK_SUCCESS)
//  if (VkResult vkResult = glfwCreateWindowSurface(sd.vkInstance, sd.glfwWindow, nullptr, &sd.vkSurfaceKHR); vkResult != VkResult::VK_SUCCESS)
    {
        throw std::runtime_error(std::format("failed to create window surface! reason: {}", static_cast<std::int32_t>(vkResult)));
//      throw std::runtime_error(std::format("failed to create window surface! reason: {}", static_cast<std::int32_t>(vkResult)));
    }





    std::uint32_t deviceCount = 0;
//  std::uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(sd.vkInstance, &deviceCount, nullptr);
//  vkEnumeratePhysicalDevices(sd.vkInstance, &deviceCount, nullptr);

    if (deviceCount == 0)
//  if (deviceCount == 0)
    {
        throw std::runtime_error(std::format("failed to find GPUs with Vulkan support!"));
//      throw std::runtime_error(std::format("failed to find GPUs with Vulkan support!"));
    }

    std::vector<VkPhysicalDevice> vkPhysicalDevices(deviceCount);
//  std::vector<VkPhysicalDevice> vkPhysicalDevices(deviceCount);
    vkEnumeratePhysicalDevices(sd.vkInstance, &deviceCount, vkPhysicalDevices.data());
//  vkEnumeratePhysicalDevices(sd.vkInstance, &deviceCount, vkPhysicalDevices.data());

    for (const VkPhysicalDevice& vkPhysicalDevice : vkPhysicalDevices)
//  for (const VkPhysicalDevice& vkPhysicalDevice : vkPhysicalDevices)
    {
        if (IsVkPhysicalDeviceSuitable(vkPhysicalDevice, sd.vkSurfaceKHR))
//      if (IsVkPhysicalDeviceSuitable(vkPhysicalDevice, sd.vkSurfaceKHR))
        {
            sd.vkPhysicalDevice = vkPhysicalDevice;
//          sd.vkPhysicalDevice = vkPhysicalDevice;
            break;
//          break;
        }
    }

    if (sd.vkPhysicalDevice == VK_NULL_HANDLE)
//  if (sd.vkPhysicalDevice == VK_NULL_HANDLE)
    {
        throw std::runtime_error(std::format("failed to find a suitable GPU!"));
//      throw std::runtime_error(std::format("failed to find a suitable GPU!"));
    }





    const QueueFamilyIndices& queueFamilyIndices = FindQueueFamilies(sd.vkPhysicalDevice, sd.vkSurfaceKHR);
//  const QueueFamilyIndices& queueFamilyIndices = FindQueueFamilies(sd.vkPhysicalDevice, sd.vkSurfaceKHR);
    std::vector<VkDeviceQueueCreateInfo> vkDeviceQueueCreateInfos;
//  std::vector<VkDeviceQueueCreateInfo> vkDeviceQueueCreateInfos;
    std::set<std::uint32_t> uniqueQueueFamilies = { queueFamilyIndices.graphicsFamily.value(), queueFamilyIndices.presentFamily.value(), };
//  std::set<std::uint32_t> uniqueQueueFamilies = { queueFamilyIndices.graphicsFamily.value(), queueFamilyIndices.presentFamily.value(), };
    float queuePriority = 1.0f;
//  float queuePriority = 1.0f;
    for (std::uint32_t queueFamily : uniqueQueueFamilies)
//  for (std::uint32_t queueFamily : uniqueQueueFamilies)
    {
        vkDeviceQueueCreateInfos.emplace_back(VkDeviceQueueCreateInfo
//      vkDeviceQueueCreateInfos.emplace_back(VkDeviceQueueCreateInfo
        {
            .sType            = VkStructureType::VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
//          .sType            = VkStructureType::VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .pNext            = nullptr,
//          .pNext            = nullptr,
//          .flags            = ,
//          .flags            = ,
            .queueFamilyIndex = queueFamily,
//          .queueFamilyIndex = queueFamily,
            .queueCount       = 1,
//          .queueCount       = 1,
            .pQueuePriorities = &queuePriority,
//          .pQueuePriorities = &queuePriority,
        });
    }

    VkPhysicalDeviceFeatures vkPhysicalDeviceFeatures{};
//  VkPhysicalDeviceFeatures vkPhysicalDeviceFeatures{};

    VkDeviceCreateInfo vkDeviceCreateInfo
    {
        .sType                   = VkStructureType::VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
//      .sType                   = VkStructureType::VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .pNext                   = nullptr,
//      .pNext                   = nullptr,
//      .flags                   = ,
//      .flags                   = ,
        .queueCreateInfoCount    = static_cast<std::uint32_t>(vkDeviceQueueCreateInfos.size()),
//      .queueCreateInfoCount    = static_cast<std::uint32_t>(vkDeviceQueueCreateInfos.size()),
        .pQueueCreateInfos       = vkDeviceQueueCreateInfos.data(),
//      .pQueueCreateInfos       = vkDeviceQueueCreateInfos.data(),
        .enabledLayerCount       = 0,
//      .enabledLayerCount       = 0,
//      .ppEnabledLayerNames     = ,
//      .ppEnabledLayerNames     = ,
        .enabledExtensionCount   = static_cast<std::uint32_t>(deviceExtensions.size()),
//      .enabledExtensionCount   = static_cast<std::uint32_t>(deviceExtensions.size()),
        .ppEnabledExtensionNames = deviceExtensions.data(),
//      .ppEnabledExtensionNames = deviceExtensions.data(),
        .pEnabledFeatures        = &vkPhysicalDeviceFeatures,
//      .pEnabledFeatures        = &vkPhysicalDeviceFeatures,
    };

    if (VkResult vkResult = vkCreateDevice(sd.vkPhysicalDevice, &vkDeviceCreateInfo, nullptr, &sd.vkDevice); vkResult != VkResult::VK_SUCCESS)
//  if (VkResult vkResult = vkCreateDevice(sd.vkPhysicalDevice, &vkDeviceCreateInfo, nullptr, &sd.vkDevice); vkResult != VkResult::VK_SUCCESS)
    {
        throw std::runtime_error(std::format("failed to create logical device! reason: {}", static_cast<std::int32_t>(vkResult)));
//      throw std::runtime_error(std::format("failed to create logical device! reason: {}", static_cast<std::int32_t>(vkResult)));
    }

    vkGetDeviceQueue(sd.vkDevice, queueFamilyIndices.graphicsFamily.value(), 0, &sd.vkGraphicsQueue);
//  vkGetDeviceQueue(sd.vkDevice, queueFamilyIndices.graphicsFamily.value(), 0, &sd.vkGraphicsQueue);
    vkGetDeviceQueue(sd.vkDevice, queueFamilyIndices.presentFamily.value(), 0, &sd.vkPresentQueue);
//  vkGetDeviceQueue(sd.vkDevice, queueFamilyIndices.presentFamily.value(), 0, &sd.vkPresentQueue);










    SwapChainSupportDetails swapChainSupportDetails = QuerySwapChainSupportDetails(sd.vkPhysicalDevice, sd.vkSurfaceKHR);
//  SwapChainSupportDetails swapChainSupportDetails = QuerySwapChainSupportDetails(sd.vkPhysicalDevice, sd.vkSurfaceKHR);
    VkSurfaceFormatKHR bestAvailableVkSurfaceFormatKHR = ChooseSwapChainVkSurfaceFormatKHR(swapChainSupportDetails.vkSurfaceFormatKHRs);
//  VkSurfaceFormatKHR bestAvailableVkSurfaceFormatKHR = ChooseSwapChainVkSurfaceFormatKHR(swapChainSupportDetails.vkSurfaceFormatKHRs);
    VkPresentModeKHR bestAvailableVkPresentModeKHR = ChooseSwapChainVkPresentModeKHR(swapChainSupportDetails.vkPresentModeKHRs);
//  VkPresentModeKHR bestAvailableVkPresentModeKHR = ChooseSwapChainVkPresentModeKHR(swapChainSupportDetails.vkPresentModeKHRs);
    VkExtent2D actualAvailableVkExtent2D = ChooseSwapChainVkExtent2D(swapChainSupportDetails.vkSurfaceCapabilitiesKHR, sd.glfwWindow);
//  VkExtent2D actualAvailableVkExtent2D = ChooseSwapChainVkExtent2D(swapChainSupportDetails.vkSurfaceCapabilitiesKHR, sd.glfwWindow);
    std::uint32_t imageCount = swapChainSupportDetails.vkSurfaceCapabilitiesKHR.minImageCount + 1;
//  std::uint32_t imageCount = swapChainSupportDetails.vkSurfaceCapabilitiesKHR.minImageCount + 1;
    if (swapChainSupportDetails.vkSurfaceCapabilitiesKHR.maxImageCount > 0 && imageCount > swapChainSupportDetails.vkSurfaceCapabilitiesKHR.maxImageCount)
//  if (swapChainSupportDetails.vkSurfaceCapabilitiesKHR.maxImageCount > 0 && imageCount > swapChainSupportDetails.vkSurfaceCapabilitiesKHR.maxImageCount)
    {
        imageCount = swapChainSupportDetails.vkSurfaceCapabilitiesKHR.maxImageCount;
//      imageCount = swapChainSupportDetails.vkSurfaceCapabilitiesKHR.maxImageCount;
    }

    VkSwapchainCreateInfoKHR vkSwapchainCreateInfoKHR
    {
        .sType            = VkStructureType::VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
//      .sType            = VkStructureType::VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .surface          = sd.vkSurfaceKHR,
//      .surface          = sd.vkSurfaceKHR,
        .minImageCount    = imageCount,
//      .minImageCount    = imageCount,
        .imageFormat      = bestAvailableVkSurfaceFormatKHR.format,
//      .imageFormat      = bestAvailableVkSurfaceFormatKHR.format,
        .imageColorSpace  = bestAvailableVkSurfaceFormatKHR.colorSpace,
//      .imageColorSpace  = bestAvailableVkSurfaceFormatKHR.colorSpace,
        .imageExtent      = actualAvailableVkExtent2D,
//      .imageExtent      = actualAvailableVkExtent2D,
        .imageArrayLayers = 1,
//      .imageArrayLayers = 1,
        .imageUsage       = VkImageUsageFlagBits::VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
//      .imageUsage       = VkImageUsageFlagBits::VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        .preTransform     = swapChainSupportDetails.vkSurfaceCapabilitiesKHR.currentTransform,
//      .preTransform     = swapChainSupportDetails.vkSurfaceCapabilitiesKHR.currentTransform,
        .compositeAlpha   = VkCompositeAlphaFlagBitsKHR::VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
//      .compositeAlpha   = VkCompositeAlphaFlagBitsKHR::VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        .presentMode      = bestAvailableVkPresentModeKHR,
//      .presentMode      = bestAvailableVkPresentModeKHR,
        .clipped          = VK_TRUE,
//      .clipped          = VK_TRUE,
        .oldSwapchain     = VK_NULL_HANDLE,
//      .oldSwapchain     = VK_NULL_HANDLE,
    };
    if (queueFamilyIndices.graphicsFamily != queueFamilyIndices.presentFamily)
//  if (queueFamilyIndices.graphicsFamily != queueFamilyIndices.presentFamily)
    {
        std::uint32_t arrayOfQueueFamilyIndices[] = { queueFamilyIndices.graphicsFamily.value(), queueFamilyIndices.presentFamily.value(), };
//      std::uint32_t arrayOfQueueFamilyIndices[] = { queueFamilyIndices.graphicsFamily.value(), queueFamilyIndices.presentFamily.value(), };
        vkSwapchainCreateInfoKHR.imageSharingMode = VkSharingMode::VK_SHARING_MODE_CONCURRENT;
//      vkSwapchainCreateInfoKHR.imageSharingMode = VkSharingMode::VK_SHARING_MODE_CONCURRENT;
        vkSwapchainCreateInfoKHR.queueFamilyIndexCount = 2;
//      vkSwapchainCreateInfoKHR.queueFamilyIndexCount = 2;
        vkSwapchainCreateInfoKHR.pQueueFamilyIndices = arrayOfQueueFamilyIndices;
//      vkSwapchainCreateInfoKHR.pQueueFamilyIndices = arrayOfQueueFamilyIndices;
    }
    else
//  else
    {
        vkSwapchainCreateInfoKHR.imageSharingMode = VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;
//      vkSwapchainCreateInfoKHR.imageSharingMode = VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;
        vkSwapchainCreateInfoKHR.queueFamilyIndexCount = 0;
//      vkSwapchainCreateInfoKHR.queueFamilyIndexCount = 0;
        vkSwapchainCreateInfoKHR.pQueueFamilyIndices = nullptr;
//      vkSwapchainCreateInfoKHR.pQueueFamilyIndices = nullptr;
    }

    if (VkResult vkResult = vkCreateSwapchainKHR(sd.vkDevice, &vkSwapchainCreateInfoKHR, nullptr, &sd.vkSwapchainKHR); vkResult != VkResult::VK_SUCCESS)
//  if (VkResult vkResult = vkCreateSwapchainKHR(sd.vkDevice, &vkSwapchainCreateInfoKHR, nullptr, &sd.vkSwapchainKHR); vkResult != VkResult::VK_SUCCESS)
    {
        throw std::runtime_error(std::format("failed to create swap chain! reason: {}", static_cast<std::int32_t>(vkResult)));
//      throw std::runtime_error(std::format("failed to create swap chain! reason: {}", static_cast<std::int32_t>(vkResult)));
    }

    vkGetSwapchainImagesKHR(sd.vkDevice, sd.vkSwapchainKHR, &imageCount, nullptr);
//  vkGetSwapchainImagesKHR(sd.vkDevice, sd.vkSwapchainKHR, &imageCount, nullptr);
    sd.swapChainImages.resize(imageCount);
//  sd.swapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(sd.vkDevice, sd.vkSwapchainKHR, &imageCount, sd.swapChainImages.data());
//  vkGetSwapchainImagesKHR(sd.vkDevice, sd.vkSwapchainKHR, &imageCount, sd.swapChainImages.data());

    sd.swapChainExtent2D = actualAvailableVkExtent2D;
//  sd.swapChainExtent2D = actualAvailableVkExtent2D;
    sd.swapChainImageFormat = bestAvailableVkSurfaceFormatKHR.format;
//  sd.swapChainImageFormat = bestAvailableVkSurfaceFormatKHR.format;
}

static inline void MainLoop(SceneData& sd)
{
    while (!glfwWindowShouldClose(sd.glfwWindow))
    {
        glfwPollEvents();
//      glfwPollEvents();
    }
}

static inline void CleansUp(SceneData& sd)
{
    vkDestroySwapchainKHR(sd.vkDevice, sd.vkSwapchainKHR, nullptr);
//  vkDestroySwapchainKHR(sd.vkDevice, sd.vkSwapchainKHR, nullptr);
    vkDestroyDevice(sd.vkDevice, nullptr);
//  vkDestroyDevice(sd.vkDevice, nullptr);

    if (enableValidationLayers)
    {
        PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(sd.vkInstance, "vkDestroyDebugUtilsMessengerEXT");
//      PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(sd.vkInstance, "vkDestroyDebugUtilsMessengerEXT");
        if (vkDestroyDebugUtilsMessengerEXT != nullptr)
//      if (vkDestroyDebugUtilsMessengerEXT != nullptr)
        {
            vkDestroyDebugUtilsMessengerEXT(sd.vkInstance, sd.debugMessenger, nullptr);
//          vkDestroyDebugUtilsMessengerEXT(sd.vkInstance, sd.debugMessenger, nullptr);
        }
    }

    vkDestroySurfaceKHR(sd.vkInstance, sd.vkSurfaceKHR, nullptr);
//  vkDestroySurfaceKHR(sd.vkInstance, sd.vkSurfaceKHR, nullptr);
    vkDestroyInstance(sd.vkInstance, nullptr);
//  vkDestroyInstance(sd.vkInstance, nullptr);
    glfwDestroyWindow(sd.glfwWindow);
//  glfwDestroyWindow(sd.glfwWindow);
    glfwTerminate();
//  glfwTerminate();
}



int main()
{
    try
    {
        SceneData  sd{ .windowTitle = "Vulkan Application" };
//      SceneData  sd{ .windowTitle = "Vulkan Application" };
        InitWindow(sd);
        InitVulkan(sd);
        MainLoop(sd);
        CleansUp(sd);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
//      std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
