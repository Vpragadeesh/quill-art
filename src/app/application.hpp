#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_vulkan.h>

// Volk headers
#ifdef IMGUI_IMPL_VULKAN_USE_VOLK
#define VOLK_IMPLEMENTATION
#include <volk.h>
#endif
// #define APP_USE_UNLIMITED_FRAME_RATE
#ifdef _DEBUG
#define APP_USE_VULKAN_DEBUG_REPORT
#endif

// Data
struct Appl {
  VkAllocationCallbacks *allocator;
  VkInstance instance;
  VkPhysicalDevice physical_device;
  VkDevice device;
  uint32_t queue_family;
  VkQueue queue;
  VkDebugReportCallbackEXT debug_report;
  VkPipelineCache pipeline_cache;
  VkDescriptorPool descriptor_pool;
  ImGui_ImplVulkanH_Window main_window_data;
  uint32_t min_image_count;
  bool swapchain_rebuild;
  SDL_Window *window;
  ImGuiIO io;
  bool show_demo_window;
  bool show_another_window;
  ImVec4 clear_color;
  bool done;

  Appl();
  void run();
  ~Appl();

  void setup_vulkan(ImVector<const char *> instance_extensions);

  void setup_vulkan_window(VkSurfaceKHR surface, int width, int height);

  void cleanup_vulkan();

  void cleanup_vulkan_window();

  void render_frame(ImDrawData *draw_data);

  void present_frame();
};

void check_vk_result(VkResult err);

#ifdef APP_USE_VULKAN_DEBUG_REPORT
static VKAPI_ATTR VkBool32 VKAPI_CALL
debug_report(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType,
             uint64_t object, size_t location, int32_t messageCode,
             const char *pLayerPrefix, const char *pMessage, void *pUserData) {
  (void)flags;
  (void)object;
  (void)location;
  (void)messageCode;
  (void)pUserData;
  (void)pLayerPrefix; // Unused arguments
  std::stringstream ss;
  ss << "[vulkan] Debug report from ObjectType: " << objectType
     << "\nMessage: " << pMessage << "\n\n";
  std::cerr << ss.str();
  return VK_FALSE;
}
#endif // APP_USE_VULKAN_DEBUG_REPORT

bool is_extension_available(const ImVector<VkExtensionProperties> &properties,
                            const char *extension);
