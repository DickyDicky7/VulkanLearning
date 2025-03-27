# define  GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


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

struct SceneData
{
    VkInstance  vkInstance;
//  VkInstance  vkInstance;
    GLFWwindow* glfwWindow;
//  GLFWwindow* glfwWindow;
    const char* windowTitle;
//  const char* windowTitle;
    std::uint32_t windowW = 800;
    std::uint32_t windowH = 600;
};

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

    std::uint32_t enabledExtensionCount = 0;
//  std::uint32_t enabledExtensionCount = 0;
    const char* const* ppEnabledExtensionNames;
//  const char* const* ppEnabledExtensionNames;
    ppEnabledExtensionNames = glfwGetRequiredInstanceExtensions(&enabledExtensionCount);
//  ppEnabledExtensionNames = glfwGetRequiredInstanceExtensions(&enabledExtensionCount);

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

    VkResult vkResult = vkCreateInstance(&vkInstanceCreateInfo, nullptr, &sd.vkInstance);
//  VkResult vkResult = vkCreateInstance(&vkInstanceCreateInfo, nullptr, &sd.vkInstance);

    if (vkResult == VkResult::VK_SUCCESS)
    {
        
    }
    else
    {
        throw std::runtime_error("!create vulkan instance failure!");
    }
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