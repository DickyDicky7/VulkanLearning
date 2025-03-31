# define  GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

  #include <optional>
//#include <optional>
  #include <iostream>
//#include <iostream>
  #include <vector>
//#include <vector>


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
};

struct SceneData
{
    VkQueue vkGraphicsQueue = VK_NULL_HANDLE;
//  VkQueue vkGraphicsQueue = VK_NULL_HANDLE;
    VkDevice vkDevice = VK_NULL_HANDLE;
//  VkDevice vkDevice = VK_NULL_HANDLE;
    VkPhysicalDevice vkPhysicalDevice = VK_NULL_HANDLE;
//  VkPhysicalDevice vkPhysicalDevice = VK_NULL_HANDLE;
    VkDebugUtilsMessengerEXT debugMessenger;
//  VkDebugUtilsMessengerEXT debugMessenger;
    VkInstance  vkInstance;
//  VkInstance  vkInstance;
    GLFWwindow* glfwWindow;
//  GLFWwindow* glfwWindow;
    const char* windowTitle;
//  const char* windowTitle;
    QueueFamilyIndices queueFamilyIndices;
//  QueueFamilyIndices queueFamilyIndices;
    std::uint32_t windowW = 800;
    std::uint32_t windowH = 600;
};

static inline bool IsComplete(const QueueFamilyIndices& queueFamilyIndices)
{
    return queueFamilyIndices.graphicsFamily.has_value();
//  return queueFamilyIndices.graphicsFamily.has_value();
}

static inline QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice vkPhysicalDevice)
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

    int i = 0;
//  int i = 0;
    for (const VkQueueFamilyProperties& queueFamily : queueFamilies)
//  for (const VkQueueFamilyProperties& queueFamily : queueFamilies)
    {
        if (queueFamily.queueFlags & VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT)
//      if (queueFamily.queueFlags & VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT)
        {
            queueFamilyIndices.graphicsFamily = i;
//          queueFamilyIndices.graphicsFamily = i;
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

static inline bool IsVkPhysicalDeviceSuitable(VkPhysicalDevice vkPhysicalDevice)
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

    const QueueFamilyIndices& queueFamilyIndices = FindQueueFamilies(vkPhysicalDevice);
//  const QueueFamilyIndices& queueFamilyIndices = FindQueueFamilies(vkPhysicalDevice);
    return IsComplete(queueFamilyIndices);
//  return IsComplete(queueFamilyIndices);
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
        throw std::runtime_error("validation layers requested but not available!");
//      throw std::runtime_error("validation layers requested but not available!");
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
        throw std::runtime_error("!create vulkan instance failure!");
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
            throw std::runtime_error("failed to set up debug messenger!");
//          throw std::runtime_error("failed to set up debug messenger!");
        }
    }



    std::uint32_t deviceCount = 0;
//  std::uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(sd.vkInstance, &deviceCount, nullptr);
//  vkEnumeratePhysicalDevices(sd.vkInstance, &deviceCount, nullptr);

    if (deviceCount == 0)
//  if (deviceCount == 0)
    {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
//      throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> vkPhysicalDevices(deviceCount);
//  std::vector<VkPhysicalDevice> vkPhysicalDevices(deviceCount);
    vkEnumeratePhysicalDevices(sd.vkInstance, &deviceCount, vkPhysicalDevices.data());
//  vkEnumeratePhysicalDevices(sd.vkInstance, &deviceCount, vkPhysicalDevices.data());

    for (const VkPhysicalDevice& vkPhysicalDevice : vkPhysicalDevices)
//  for (const VkPhysicalDevice& vkPhysicalDevice : vkPhysicalDevices)
    {
        if (IsVkPhysicalDeviceSuitable(vkPhysicalDevice))
//      if (IsVkPhysicalDeviceSuitable(vkPhysicalDevice))
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
        throw std::runtime_error("failed to find a suitable GPU!");
//      throw std::runtime_error("failed to find a suitable GPU!");
    }





    const QueueFamilyIndices& queueFamilyIndices = FindQueueFamilies(sd.vkPhysicalDevice);
//  const QueueFamilyIndices& queueFamilyIndices = FindQueueFamilies(sd.vkPhysicalDevice);
    float queuePriority = 1.0f;
//  float queuePriority = 1.0f;
    VkDeviceQueueCreateInfo vkDeviceQueueCreateInfo
    {
        .sType            = VkStructureType::VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
//      .sType            = VkStructureType::VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .pNext            = nullptr,
//      .pNext            = nullptr,
//      .flags            = ,
//      .flags            = ,
        .queueFamilyIndex = queueFamilyIndices.graphicsFamily.value(),
//      .queueFamilyIndex = queueFamilyIndices.graphicsFamily.value(),
        .queueCount       = 1,
//      .queueCount       = 1,
        .pQueuePriorities = &queuePriority,
//      .pQueuePriorities = &queuePriority,
    };

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
        .queueCreateInfoCount    = 1,
//      .queueCreateInfoCount    = 1,
        .pQueueCreateInfos       = &vkDeviceQueueCreateInfo,
//      .pQueueCreateInfos       = &vkDeviceQueueCreateInfo,
        .enabledLayerCount       = 0,
//      .enabledLayerCount       = 0,
//      .ppEnabledLayerNames     = ,
//      .ppEnabledLayerNames     = ,
        .enabledExtensionCount   = 0,
//      .enabledExtensionCount   = 0,
//      .ppEnabledExtensionNames = ,
//      .ppEnabledExtensionNames = ,
        .pEnabledFeatures        = &vkPhysicalDeviceFeatures,
//      .pEnabledFeatures        = &vkPhysicalDeviceFeatures,
    };

    if (VkResult vkResult = vkCreateDevice(sd.vkPhysicalDevice, &vkDeviceCreateInfo, nullptr, &sd.vkDevice); vkResult != VkResult::VK_SUCCESS)
//  if (VkResult vkResult = vkCreateDevice(sd.vkPhysicalDevice, &vkDeviceCreateInfo, nullptr, &sd.vkDevice); vkResult != VkResult::VK_SUCCESS)
    {
        throw std::runtime_error("failed to create logical device!");
//      throw std::runtime_error("failed to create logical device!");
    }

    vkGetDeviceQueue(sd.vkDevice, sd.queueFamilyIndices.graphicsFamily.value(), 0, &sd.vkGraphicsQueue);
//  vkGetDeviceQueue(sd.vkDevice, sd.queueFamilyIndices.graphicsFamily.value(), 0, &sd.vkGraphicsQueue);
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
