#include "application.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#include <format>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <stdexcept>

Appl::Appl()
    : allocator(nullptr), instance(VK_NULL_HANDLE),
      physical_device(VK_NULL_HANDLE), device(VK_NULL_HANDLE),
      queue_family((uint32_t)-1), queue(VK_NULL_HANDLE),
      debug_report(VK_NULL_HANDLE), pipeline_cache(VK_NULL_HANDLE),
      descriptor_pool(VK_NULL_HANDLE), min_image_count(2),
      swapchain_rebuild(false), show_demo_window(true),
      show_another_window(false),
      clear_color(ImVec4(0.45f, 0.55f, 0.60f, 1.00f)), done(false) {
  // Setup SDL
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD) != 0)
    throw std::runtime_error(
        std::format("Error: SDL_Init(): {}\n", SDL_GetError()));

  // Create window with Vulkan graphics context
  auto window_flags =
      (SDL_WindowFlags)(SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE |
                        SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_HIDDEN);
  window = SDL_CreateWindow("Quill Art", 1280, 720, window_flags);
  if (window == nullptr)
    throw std::runtime_error(
        std::format("Error: SDL_CreateWindow(): {}\n", SDL_GetError()));

  ImVector<const char *> extensions;
  {
    uint32_t sdl_extensions_count = 0;
    auto sdl_extensions =
        SDL_Vulkan_GetInstanceExtensions(&sdl_extensions_count);
    for (uint32_t n = 0; n < sdl_extensions_count; ++n)
      extensions.push_back(sdl_extensions[n]);
  }
  setup_vulkan(extensions);

  // Create Window Surface
  VkSurfaceKHR surface;
  if (SDL_Vulkan_CreateSurface(window, instance, allocator, &surface) == 0)
    throw std::runtime_error("Failed to create Vulkan surface.\n");

  // Create Framebuffers
  int w, h;
  SDL_GetWindowSize(window, &w, &h);
  setup_vulkan_window(surface, w, h);
  SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
  SDL_ShowWindow(window);

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  io = ImGui::GetIO();
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();

  // Setup Platform/Renderer backends
  ImGui_ImplSDL3_InitForVulkan(window);
  ImGui_ImplVulkan_InitInfo init_info = {};
  // init_info.ApiVersion = VK_API_VERSION_1_3;              // Pass in your
  // value of VkApplicationInfo::apiVersion, otherwise will default to header
  // version.
  init_info.Instance = instance;
  init_info.PhysicalDevice = physical_device;
  init_info.Device = device;
  init_info.QueueFamily = queue_family;
  init_info.Queue = queue;
  init_info.PipelineCache = pipeline_cache;
  init_info.DescriptorPool = descriptor_pool;
  init_info.RenderPass = main_window_data.RenderPass;
  init_info.Subpass = 0;
  init_info.MinImageCount = min_image_count;
  init_info.ImageCount = main_window_data.ImageCount;
  init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
  init_info.Allocator = allocator;
  init_info.CheckVkResultFn = check_vk_result;
  ImGui_ImplVulkan_Init(&init_info);
}

void Appl::run() {
  while (!done) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL3_ProcessEvent(&event);
      if (event.type == SDL_EVENT_QUIT)
        done = true;
      if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED &&
          event.window.windowID == SDL_GetWindowID(window))
        done = true;
    }
    if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED) {
      SDL_Delay(10);
      continue;
    }
    int fb_width, fb_height;
    SDL_GetWindowSize(window, &fb_width, &fb_height);
    if (fb_width > 0 && fb_height > 0 &&
        (swapchain_rebuild || main_window_data.Width != fb_width ||
         main_window_data.Height != fb_height)) {
      ImGui_ImplVulkan_SetMinImageCount(min_image_count);
      ImGui_ImplVulkanH_CreateOrResizeWindow(
          instance, physical_device, device, &main_window_data, queue_family,
          allocator, fb_width, fb_height, min_image_count);
      main_window_data.FrameIndex = 0;
      swapchain_rebuild = false;
    }
    ImGui_ImplVulkan_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    if (show_demo_window)
      ImGui::ShowDemoWindow(&show_demo_window);
    {
      static float f = 0.0f;
      static int counter = 0;

      ImGui::Begin("Hello, world!"); // Create a window called "Hello,
      // world!"
      // and append into it.

      ImGui::Text("This is some useful text."); // Display some text (you can
                                                // use a format strings too)
      ImGui::Checkbox("Demo Window",
                      &show_demo_window); // Edit bools storing our window
                                          // open/close state
      ImGui::Checkbox("Another Window", &show_another_window);

      ImGui::SliderFloat("float", &f, 0.0f,
                         1.0f); // Edit 1 float using a slider from 0.0f
                                //  to 1.0f
      ImGui::ColorEdit3(
          "clear color",
          (float *)&clear_color); // Edit 3 floats representing a color

      if (ImGui::Button("Button")) // Buttons return true when clicked (most
                                   // widgets return true when
                                   //  edited/activated)
        counter++;
      ImGui::SameLine();
      ImGui::Text("counter = %d", counter);

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                  1000.0f / io.Framerate, io.Framerate);
      ImGui::End();
    }
    if (show_another_window) {
      ImGui::Begin(
          "Another Window",
          &show_another_window); // Pass a pointer to our bool variable (the
                                 // window will have a closing button that
                                 //  will
                                 // clear the bool when clicked)
      ImGui::Text("Hello from another window!");
      if (ImGui::Button("Close Me"))
        show_another_window = false;
      ImGui::End();
    }
    ImGui::Render();
    ImDrawData *draw_data = ImGui::GetDrawData();
    const bool is_minimized =
        (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f);
    if (!is_minimized) {
      main_window_data.ClearValue.color.float32[0] =
          clear_color.x * clear_color.w;
      main_window_data.ClearValue.color.float32[1] =
          clear_color.y * clear_color.w;
      main_window_data.ClearValue.color.float32[2] =
          clear_color.z * clear_color.w;
      main_window_data.ClearValue.color.float32[3] = clear_color.w;
      render_frame(draw_data);
      present_frame();
    }
  }
}

Appl::~Appl() {
  auto err = vkDeviceWaitIdle(device);
  check_vk_result(err);
  ImGui_ImplVulkan_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();
  cleanup_vulkan_window();
  cleanup_vulkan();
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Appl::setup_vulkan(ImVector<const char *> instance_extensions) {
  VkResult err;
#ifdef IMGUI_IMPL_VULKAN_USE_VOLK
  volkInitialize();
#endif

  // Create Vulkan Instance
  {
    VkInstanceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

    // Enumerate available extensions
    uint32_t properties_count;
    ImVector<VkExtensionProperties> properties;
    vkEnumerateInstanceExtensionProperties(nullptr, &properties_count, nullptr);
    properties.resize(properties_count);
    err = vkEnumerateInstanceExtensionProperties(nullptr, &properties_count,
                                                 properties.Data);
    check_vk_result(err);

    // Enable required extensions
    if (is_extension_available(
            properties, VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME))
      instance_extensions.push_back(
          VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
#ifdef VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME
    if (is_extension_available(properties,
                               VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME)) {
      instance_extensions.push_back(
          VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
      create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    }
#endif

    // Enabling validation layers
#ifdef APP_USE_VULKAN_DEBUG_REPORT
    auto layers[] = {"VK_LAYER_KHRONOS_validation"};
    create_info.enabledLayerCount = 1;
    create_info.ppEnabledLayerNames = layers;
    instance_extensions.push_back("VK_EXT_debug_report");
#endif

    // Create Vulkan Instance
    create_info.enabledExtensionCount = (uint32_t)instance_extensions.Size;
    create_info.ppEnabledExtensionNames = instance_extensions.Data;
    err = vkCreateInstance(&create_info, allocator, &instance);
    check_vk_result(err);
#ifdef IMGUI_IMPL_VULKAN_USE_VOLK
    volkLoadInstance(instance);
#endif

    // Setup the debug report callback
#ifdef APP_USE_VULKAN_DEBUG_REPORT
    auto f_vkCreateDebugReportCallbackEXT =
        (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(
            instance, "vkCreateDebugReportCallbackEXT");
    IM_ASSERT(f_vkCreateDebugReportCallbackEXT != nullptr);
    VkDebugReportCallbackCreateInfoEXT debug_report_ci = {};
    debug_report_ci.sType =
        VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
    debug_report_ci.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT |
                            VK_DEBUG_REPORT_WARNING_BIT_EXT |
                            VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
    debug_report_ci.pfnCallback = ::debug_report;
    debug_report_ci.pUserData = nullptr;
    err = f_vkCreateDebugReportCallbackEXT(instance, &debug_report_ci,
                                           allocator, &this->debug_report);
    check_vk_result(err);
#endif
  }

  // Select Physical Device (GPU)
  physical_device = ImGui_ImplVulkanH_SelectPhysicalDevice(instance);
  IM_ASSERT(physical_device != VK_NULL_HANDLE);

  // Select graphics queue family
  queue_family = ImGui_ImplVulkanH_SelectQueueFamilyIndex(physical_device);
  IM_ASSERT(queue_family != (uint32_t)-1);

  // Create Logical Device (with 1 queue)
  {
    ImVector<const char *> device_extensions;
    device_extensions.push_back("VK_KHR_swapchain");

    // Enumerate physical device extension
    uint32_t properties_count;
    ImVector<VkExtensionProperties> properties;
    vkEnumerateDeviceExtensionProperties(physical_device, nullptr,
                                         &properties_count, nullptr);
    properties.resize(properties_count);
    vkEnumerateDeviceExtensionProperties(physical_device, nullptr,
                                         &properties_count, properties.Data);
#ifdef VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME
    if (is_extension_available(properties,
                               VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME))
      device_extensions.push_back(VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME);
#endif

    const float queue_priority[] = {1.0f};
    VkDeviceQueueCreateInfo queue_info[1] = {};
    queue_info[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_info[0].queueFamilyIndex = queue_family;
    queue_info[0].queueCount = 1;
    queue_info[0].pQueuePriorities = queue_priority;
    VkDeviceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    create_info.queueCreateInfoCount =
        sizeof(queue_info) / sizeof(queue_info[0]);
    create_info.pQueueCreateInfos = queue_info;
    create_info.enabledExtensionCount = (uint32_t)device_extensions.Size;
    create_info.ppEnabledExtensionNames = device_extensions.Data;
    err = vkCreateDevice(physical_device, &create_info, allocator, &device);
    check_vk_result(err);
    vkGetDeviceQueue(device, queue_family, 0, &queue);
  }

  // Create Descriptor Pool
  // If you wish to load e.g. additional textures you may need to alter pools
  // sizes and maxSets.
  {
    VkDescriptorPoolSize pool_sizes[] = {
        {VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
         IMGUI_IMPL_VULKAN_MINIMUM_IMAGE_SAMPLER_POOL_SIZE},
    };
    VkDescriptorPoolCreateInfo pool_info = {};
    pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
    pool_info.maxSets = 0;
    for (VkDescriptorPoolSize &pool_size : pool_sizes)
      pool_info.maxSets += pool_size.descriptorCount;
    pool_info.poolSizeCount = (uint32_t)IM_ARRAYSIZE(pool_sizes);
    pool_info.pPoolSizes = pool_sizes;
    err =
        vkCreateDescriptorPool(device, &pool_info, allocator, &descriptor_pool);
    check_vk_result(err);
  }
}

// All the ImGui_ImplVulkanH_XXX structures/functions are optional helpers
// used by the demo. Your real engine/app may not use them.
void Appl::setup_vulkan_window(VkSurfaceKHR surface, int width, int height) {
  main_window_data.Surface = surface;

  // Check for WSI support
  VkBool32 res;
  vkGetPhysicalDeviceSurfaceSupportKHR(physical_device, queue_family,
                                       main_window_data.Surface, &res);
  if (res != VK_TRUE) {
    fprintf(stderr, "Error no WSI support on physical device 0\n");
    exit(-1);
  }

  // Select Surface Format
  const VkFormat requestSurfaceImageFormat[] = {
      VK_FORMAT_B8G8R8A8_UNORM, VK_FORMAT_R8G8B8A8_UNORM,
      VK_FORMAT_B8G8R8_UNORM, VK_FORMAT_R8G8B8_UNORM};
  const VkColorSpaceKHR requestSurfaceColorSpace =
      VK_COLORSPACE_SRGB_NONLINEAR_KHR;
  main_window_data.SurfaceFormat = ImGui_ImplVulkanH_SelectSurfaceFormat(
      physical_device, main_window_data.Surface, requestSurfaceImageFormat,
      (size_t)IM_ARRAYSIZE(requestSurfaceImageFormat),
      requestSurfaceColorSpace);

  // Select Present Mode
#ifdef APP_USE_UNLIMITED_FRAME_RATE
  VkPresentModeKHR present_modes[] = {VK_PRESENT_MODE_MAILBOX_KHR,
                                      VK_PRESENT_MODE_IMMEDIATE_KHR,
                                      VK_PRESENT_MODE_FIFO_KHR};
#else
  VkPresentModeKHR present_modes[] = {VK_PRESENT_MODE_FIFO_KHR};
#endif
  main_window_data.PresentMode = ImGui_ImplVulkanH_SelectPresentMode(
      physical_device, main_window_data.Surface, &present_modes[0],
      IM_ARRAYSIZE(present_modes));
  // printf("[vulkan] Selected PresentMode = %d\n",
  // &main_window_data->PresentMode);

  // Create SwapChain, RenderPass, Framebuffer, etc.
  IM_ASSERT(min_image_count >= 2);
  ImGui_ImplVulkanH_CreateOrResizeWindow(
      instance, physical_device, device, &main_window_data, queue_family,
      allocator, width, height, min_image_count);
}

void Appl::cleanup_vulkan() {
  vkDestroyDescriptorPool(device, descriptor_pool, allocator);

#ifdef APP_USE_VULKAN_DEBUG_REPORT
  // Remove the debug report callback
  auto f_vkDestroyDebugReportCallbackEXT =
      (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(
          instance, "vkDestroyDebugReportCallbackEXT");
  f_vkDestroyDebugReportCallbackEXT(instance, this->debug_report, allocator);
#endif // APP_USE_VULKAN_DEBUG_REPORT

  vkDestroyDevice(device, allocator);
  vkDestroyInstance(instance, allocator);
}

void Appl::cleanup_vulkan_window() {
  ImGui_ImplVulkanH_DestroyWindow(instance, device, &main_window_data,
                                  allocator);
}

void Appl::render_frame(ImDrawData *draw_data) {
  VkSemaphore image_acquired_semaphore =
      main_window_data.FrameSemaphores[main_window_data.SemaphoreIndex]
          .ImageAcquiredSemaphore;
  VkSemaphore render_complete_semaphore =
      main_window_data.FrameSemaphores[main_window_data.SemaphoreIndex]
          .RenderCompleteSemaphore;
  VkResult err = vkAcquireNextImageKHR(
      device, main_window_data.Swapchain, UINT64_MAX, image_acquired_semaphore,
      VK_NULL_HANDLE, &main_window_data.FrameIndex);
  if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR)
    swapchain_rebuild = true;
  if (err == VK_ERROR_OUT_OF_DATE_KHR)
    return;
  if (err != VK_SUBOPTIMAL_KHR)
    check_vk_result(err);

  ImGui_ImplVulkanH_Frame *fd =
      &main_window_data.Frames[main_window_data.FrameIndex];
  {
    err = vkWaitForFences(
        device, 1, &fd->Fence, VK_TRUE,
        UINT64_MAX); // wait indefinitely instead of periodically checking
    check_vk_result(err);

    err = vkResetFences(device, 1, &fd->Fence);
    check_vk_result(err);
  }
  {
    err = vkResetCommandPool(device, fd->CommandPool, 0);
    check_vk_result(err);
    VkCommandBufferBeginInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    err = vkBeginCommandBuffer(fd->CommandBuffer, &info);
    check_vk_result(err);
  }
  {
    VkRenderPassBeginInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    info.renderPass = main_window_data.RenderPass;
    info.framebuffer = fd->Framebuffer;
    info.renderArea.extent.width = main_window_data.Width;
    info.renderArea.extent.height = main_window_data.Height;
    info.clearValueCount = 1;
    info.pClearValues = &main_window_data.ClearValue;
    vkCmdBeginRenderPass(fd->CommandBuffer, &info, VK_SUBPASS_CONTENTS_INLINE);
  }

  // Record dear imgui primitives into command buffer
  ImGui_ImplVulkan_RenderDrawData(draw_data, fd->CommandBuffer);

  // Submit command buffer
  vkCmdEndRenderPass(fd->CommandBuffer);
  {
    VkPipelineStageFlags wait_stage =
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    VkSubmitInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    info.waitSemaphoreCount = 1;
    info.pWaitSemaphores = &image_acquired_semaphore;
    info.pWaitDstStageMask = &wait_stage;
    info.commandBufferCount = 1;
    info.pCommandBuffers = &fd->CommandBuffer;
    info.signalSemaphoreCount = 1;
    info.pSignalSemaphores = &render_complete_semaphore;

    err = vkEndCommandBuffer(fd->CommandBuffer);
    check_vk_result(err);
    err = vkQueueSubmit(queue, 1, &info, fd->Fence);
    check_vk_result(err);
  }
}

void Appl::present_frame() {
  if (swapchain_rebuild)
    return;
  VkSemaphore render_complete_semaphore =
      main_window_data.FrameSemaphores[main_window_data.SemaphoreIndex]
          .RenderCompleteSemaphore;
  VkPresentInfoKHR info = {};
  info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  info.waitSemaphoreCount = 1;
  info.pWaitSemaphores = &render_complete_semaphore;
  info.swapchainCount = 1;
  info.pSwapchains = &main_window_data.Swapchain;
  info.pImageIndices = &main_window_data.FrameIndex;
  VkResult err = vkQueuePresentKHR(queue, &info);
  if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR)
    swapchain_rebuild = true;
  if (err == VK_ERROR_OUT_OF_DATE_KHR)
    return;
  if (err != VK_SUBOPTIMAL_KHR)
    check_vk_result(err);
  main_window_data.SemaphoreIndex =
      (main_window_data.SemaphoreIndex + 1) %
      main_window_data
          .SemaphoreCount; // Now we can use the next set of semaphores
}

void check_vk_result(VkResult err) {
  if (err == VK_SUCCESS)
    return;
  if (err < 0) {
    std::stringstream ss;
    ss << "[vulkan] Error: VkResult = " << err << std::endl;
    std::cerr << ss.str();
  }
}

bool is_extension_available(const ImVector<VkExtensionProperties> &properties,
                            const char *extension) {
  for (const VkExtensionProperties &p : properties)
    if (strcmp(p.extensionName, extension) == 0)
      return true;
  return false;
}
