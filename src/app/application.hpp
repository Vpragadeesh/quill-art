#pragma once

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_vulkan.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#include <iostream>
#include <sstream>

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
struct State {
  VkAllocationCallbacks *allocator = nullptr;
  VkInstance instance = VK_NULL_HANDLE;
  VkPhysicalDevice physical_device = VK_NULL_HANDLE;
  VkDevice device = VK_NULL_HANDLE;
  uint32_t queue_family = (uint32_t)-1;
  VkQueue queue = VK_NULL_HANDLE;
  VkDebugReportCallbackEXT debug_report = VK_NULL_HANDLE;
  VkPipelineCache pipeline_cache = VK_NULL_HANDLE;
  VkDescriptorPool descriptor_pool = VK_NULL_HANDLE;
  ImGui_ImplVulkanH_Window main_window_data;
  uint32_t min_image_count = 2;
  bool swapchain_rebuild = false;

  void setup_vulkan(ImVector<const char *> instance_extensions);

  void setup_vulkan_window(ImGui_ImplVulkanH_Window *wd, VkSurfaceKHR surface,
                           int width, int height);

  void cleanup_vulkan();

  void cleanup_vulkan_window();

  void render_frame(ImGui_ImplVulkanH_Window *wd, ImDrawData *draw_data);

  void present_frame(ImGui_ImplVulkanH_Window *wd);
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
