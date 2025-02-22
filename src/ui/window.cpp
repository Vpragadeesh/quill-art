#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_vulkan.h>
#include <iostream>

#ifdef IMGUI_IMPL_VULKAN_USE_VOLK
#define VOLK_IMPLEMENTATION
#include <volk.h>
#endif

class State {
  VkAllocationCallbacks *allocator = nullptr;
  VkInstance instance = VK_NULL_HANDLE;
  VkPhysicalDevice physical_device = VK_NULL_HANDLE;
  VkDevice device = VK_NULL_HANDLE;
  uint32_t queue_family = (uint32_t)-1;
  VkQueue queue = VK_NULL_HANDLE;
  VkDebugReportCallbackEXT debug_report = VK_NULL_HANDLE;
  VkPipelineCache pipeline_cache = VK_NULL_HANDLE;
  VkDescriptorPool descriptor_pool = VK_NULL_HANDLE;
  ImGui_ImplVulkanH_Window window_data;
  uint32_t min_image_count = 2;
  bool swapchain_rebuild = false;
};

static void check_vk_result(VkResult err) {
  if (err == VK_SUCCESS)
    return;
  std::cerr << "[vulkan] Error: VkResult = " << err << std::endl;
  if (err < 0)
    abort();
}

#ifdef APP_USE_VULKAN_DEBUG_REPORT
static VKAPI_ATTR VkBool32 VKAPI_CALL debug_report_callback(
    VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT obj_type,
    std::uint64_t src_obj, std::size_t location, std::int32_t msg_code,
    const char *layer_prefix, const char *msg, void *user_data) {
  (void)flags;
  (void)src_obj;
  (void)location;
  (void)msg_code;
  (void)layer_prefix;
  (void)user_data;
  fprintf(stderr, "[vulkan] Debug report from object: %i\nMessage: %s\n\n",
          src_obj, msg);
  return VK_FALSE;
}
#endif
