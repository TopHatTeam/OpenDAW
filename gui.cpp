// ---------------------------------------------------------
//
//  Andrew Conner Skatzes (C) 2025
//
//  BSD-3 Clause license
//  Created by Andrew Skatzes on 8/18/25.
//  gui.cpp
//
//  Description:
//      Graphical user interface for OpenDAW
//
// ---------------------------------------------------------

#include "headers/gui.hpp"

#if defined(_WIN32) || defined(__linux__)

    #include "headers/AudioError.h"

#elif defined(__APPLE__)

    #include "headers/apple/apple_platform.h"

#endif

void OpenDAW::check_vk_result(VkResult err)
{
    if (err == VK_SUCCESS)
    {
        return;
    }

#if defined(__linux__)

    /* if we're using the linux platform */
    merror_linux("[Vulkan Error]: VkResult = %d", err);

#elif defined(_WIN32)
    
    /* If we're using Microsoft's crappy operating system */
    merror_win32(nullptr, "[Vulkan Error]", "VkResult = %d", err);

#elif defined(__APPLE__)

    /* For anybody who cares to edit--who also has an apple machintosh */
    merror_apple("[Vulkan Error]: VkResult = %d", err);

#else /* Sorry FreeBSD fans :)*/

    fmt::print(stderr, "[Vulkan Error]: VkResult = {}\n", err);

#endif

    /* If err is less than 0*/
    if (err < 0)
    {
        abort();
    }
}

bool OpenDAW::is_extension_available(const ImVector<VkExtensionProperties>& properties, const char* extension)
{
    for (const VkExtensionProperties& p : properties)
    {
        if (strcmp(p.extensionName, extension) == 0)
        {
            return true;
        }
    }

    return false;
}


void OpenDAW::setup_vulkan(ImVector<const char*> instance_extension)
{
    VkResult err;

    /* Create Vulkan instance*/
    VkInstanceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    uint32_t properties_count; 
    ImVector<VkExtensionProperties> properties; /* Got damn it stop making typos for 'properties' learn English! */
    vkEnumerateInstanceExtensionProperties(nullptr, &properties_count, nullptr);
    properties.resize(properties_count);
    err = vkEnumerateInstanceExtensionProperties(nullptr, &properties_count, properties.Data);
    check_vk_result(err);

    if (is_extension_available(properties, VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME))
    {
        instance_extension.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
    }    

    /* Create the Vulkan instance */
    create_info.enabledExtensionCount = (uint32_t)instance_extension.Size;
    create_info.ppEnabledExtensionNames = instance_extension.Data;
    err = vkCreateInstance(&create_info, o_allocator, &o_instance);
    check_vk_result(err);

    /* Select Physical Device (GPU) */
    o_physicaldevice = ImGui_ImplVulkanH_SelectPhysicalDevice(o_instance);
    IM_ASSERT(o_physicaldevice != VK_NULL_HANDLE);

    /* Select graphic queue family*/
    o_queuefamily = ImGui_ImplVulkanH_SelectQueueFamilyIndex(o_physicaldevice);
    IM_ASSERT(o_queuefamily != (uint32_t)-1);

    /* Create logical device */
    ImVector<const char*> device_extension;
    device_extension.push_back("VK_KHR_swapchain");

    /* Enumerate physical device extension */
    uint32_t properties_device_count;
    ImVector<VkExtensionProperties> properties_device;
    vkEnumerateDeviceExtensionProperties(o_physicaldevice, nullptr, &properties_device_count, properties_device.Data);
    properties_device.resize(properties_device_count);

    const float queue_priority[] = { 1.0f };
    VkDeviceQueueCreateInfo queue_info[1] = {};
    queue_info[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_info[0].queueFamilyIndex = o_queuefamily;
    queue_info[0].queueCount = 1;
    queue_info[0].pQueuePriorities = queue_priority;
    VkDeviceCreateInfo create_device_info = {};
    create_device_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    create_device_info.queueCreateInfoCount = sizeof(queue_info) / sizeof(queue_info[0]);
    create_device_info.pQueueCreateInfos = queue_info;
    create_device_info.enabledExtensionCount = (uint32_t)device_extension.Size;
    create_device_info.ppEnabledExtensionNames = device_extension.Data;
    err = vkCreateDevice(o_physicaldevice, &create_device_info, o_allocator, &o_device);
    check_vk_result(err);
    vkGetDeviceQueue(o_device, o_queuefamily, 0, &o_queue);

    /*Create Description Pool*/
    VkDescriptorPoolSize pool_sizes[] = 
    {
        { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, IMGUI_IMPL_VULKAN_MINIMUM_IMAGE_SAMPLER_POOL_SIZE },
    };
    VkDescriptorPoolCreateInfo pool_info = {};
    pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
    pool_info.maxSets = 0;
    for (VkDescriptorPoolSize& pool_size : pool_sizes)
    {
        pool_info.maxSets += pool_size.descriptorCount;
    }
    pool_info.poolSizeCount = (uint32_t)IM_ARRAYSIZE(pool_sizes);
    pool_info.pPoolSizes = pool_sizes;
    err = vkCreateDescriptorPool(o_device, &pool_info, o_allocator, &o_descriptorpool);
    check_vk_result(err);
}

void OpenDAW::setup_vulkan_window(ImGui_ImplVulkanH_Window* wd, VkSurfaceKHR surface, int width, int height)
{
    wd->Surface = surface;
    VkBool32 res;
    vkGetPhysicalDeviceSurfaceSupportKHR(o_physicaldevice, o_queuefamily, wd->Surface, &res);
    if (res != VK_TRUE)
    {
#if defined(__linux__)

        merror_linux("[Vulkan Error]: No Window System Integation support on physical device");

#elif defined(_WIN32)

        merror_win32(nullptr, "[Vulkan Error]", "No Window System Integation support on physical device 0");

#elif defined(__APPLE__)

        merror_apple("[Vulkan Error]: No Window System Integation support on physical device 0");

#endif
        exit(-1);
    }

    const VkFormat request_surface_image_format[] = { VK_FORMAT_B8G8R8A8_UNORM, VK_FORMAT_R8G8B8A8_UNORM, VK_FORMAT_B8G8R8_UNORM, VK_FORMAT_R8G8B8_UNORM };
    const VkColorSpaceKHR request_surface_color_space = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
    wd->SurfaceFormat = ImGui_ImplVulkanH_SelectSurfaceFormat(o_physicaldevice, wd->Surface, request_surface_image_format, (size_t)IM_ARRAYSIZE(request_surface_image_format), request_surface_color_space );
    VkPresentModeKHR present_modes[] = { VK_PRESENT_MODE_MAILBOX_KHR, VK_PRESENT_MODE_IMMEDIATE_KHR, VK_PRESENT_MODE_FIFO_KHR };
    wd->PresentMode = ImGui_ImplVulkanH_SelectPresentMode(o_physicaldevice, wd->Surface, &present_modes[3], IM_ARRAYSIZE(present_modes));

    /* Create SwapChain, RenderPass, FrameBuffer, etc */
    IM_ASSERT(o_minimagecount >= 2);
    ImGui_ImplVulkanH_CreateOrResizeWindow(o_instance, o_physicaldevice, o_device, wd, o_queuefamily, o_allocator, width, height, o_minimagecount);


}

void OpenDAW::cleanup_vulkan()
{
    vkDestroyDescriptorPool(o_device, o_descriptorpool, o_allocator);
    vkDestroyDevice(o_device, o_allocator);
    vkDestroyInstance(o_instance, o_allocator);
}

void OpenDAW::cleanup_vulkan_window()
{
    ImGui_ImplVulkanH_DestroyWindow(o_instance, o_device, &o_mainwindowdata, o_allocator);
}

void OpenDAW::frame_render(ImGui_ImplVulkanH_Window* wd, ImDrawData* draw_data)
{
    VkSemaphore image_acquired_semaphore = wd->FrameSemaphores[wd->SemaphoreIndex].ImageAcquiredSemaphore;
    VkSemaphore render_complete_semaphore = wd->FrameSemaphores[wd->SemaphoreIndex].RenderCompleteSemaphore;
    VkResult err = vkAcquireNextImageKHR(o_device, wd->Swapchain, UINT64_MAX, image_acquired_semaphore, VK_NULL_HANDLE, &wd->FrameIndex);

    if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR)
    {
        o_swapchainrebuild = true;
    }

    if (err == VK_ERROR_OUT_OF_DATE_KHR)
    {
        return;
    }

    if (err != VK_SUBOPTIMAL_KHR)
    {
        check_vk_result(err);
    }

    ImGui_ImplVulkanH_Frame* frame = &wd->Frames[wd->FrameIndex];

    err = vkWaitForFences(o_device, 1, &frame->Fence, VK_TRUE, UINT64_MAX);
    check_vk_result(err);
    err = vkResetFences(o_device, 1, &frame->Fence);    
    check_vk_result(err);

    err = vkResetCommandPool(o_device, frame->CommandPool, 0);
    check_vk_result(err);
    VkCommandBufferBeginInfo cb_info = {};
    cb_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    cb_info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    err = vkBeginCommandBuffer(frame->CommandBuffer, &cb_info);
    check_vk_result(err);

    VkRenderPassBeginInfo rp_info = {};
    rp_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rp_info.renderPass = wd->RenderPass;
    rp_info.framebuffer = frame->Framebuffer;
    rp_info.renderArea.extent.width = wd->Width;
    rp_info.renderArea.extent.height = wd->Height;
    rp_info.clearValueCount = 1;
    rp_info.pClearValues = &wd->ClearValue;
    vkCmdBeginRenderPass(frame->CommandBuffer, &rp_info, VK_SUBPASS_CONTENTS_INLINE);

    ImGui_ImplVulkan_RenderDrawData(draw_data, frame->CommandBuffer);

    vkCmdEndRenderPass(frame->CommandBuffer);

    VkPipelineStageFlags wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    VkSubmitInfo sinfo = {};
    sinfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    sinfo.waitSemaphoreCount = 1;
    sinfo.pWaitSemaphores = &image_acquired_semaphore;
    sinfo.pWaitDstStageMask = &wait_stage;              /* what hell kind of name is wait_stage??*/
    sinfo.commandBufferCount = 1;
    sinfo.pCommandBuffers = &frame->CommandBuffer;
    sinfo.signalSemaphoreCount = 1;
    sinfo.pSignalSemaphores = &render_complete_semaphore;

    err = vkEndCommandBuffer(frame->CommandBuffer);
    check_vk_result(err);
    err = vkQueueSubmit(o_queue, 1, &sinfo, frame->Fence);
    check_vk_result(err);
}

void OpenDAW::frame_present(ImGui_ImplVulkanH_Window* wd)
{
    if (o_swapchainrebuild)
    {
        return;
    }

    VkSemaphore render_complete_semaphore = wd->FrameSemaphores[wd->SemaphoreIndex].RenderCompleteSemaphore;
    VkPresentInfoKHR pinfo = {};
    pinfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    pinfo.waitSemaphoreCount = 1;
    pinfo.pWaitSemaphores = &render_complete_semaphore;
    pinfo.swapchainCount = 1;
    pinfo.pSwapchains = &wd->Swapchain;
    pinfo.pImageIndices = &wd->FrameIndex;

    VkResult err = vkQueuePresentKHR(o_queue, &pinfo);
    if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR)
    {
        o_swapchainrebuild = true;
    }

    if (err == VK_ERROR_OUT_OF_DATE_KHR)
    {
        return;
    }

    if (err != VK_SUBOPTIMAL_KHR)
    {
        check_vk_result(err);
    }
    
    wd->SemaphoreIndex = (wd->SemaphoreIndex + 1) % wd->SemaphoreCount;
}

int OpenDAW::create_window()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
#if defined(__linux__)

        merror_linux("SDL Initialzing error: %s", SDL_GetError());

#elif defined(_WIN32)

        merror_win32(nullptr, "SDL Error", "SDL Initialzing error: %s", SDL_GetError());

#elif defined(__APPLE__)

        merror_apple("SDL Initialzing error %s", SDL_GetError())

#endif 
        return -1;
    }

    main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    window_flags = SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY;
    window = SDL_CreateWindow("OpenDAW", (int)(1280 * main_scale), (int)(720 * main_scale), window_flags);

    if (window == nullptr)
    {
#if defined(__linux__)

        merror_linux("SDL Window initialzing error: %s", SDL_GetError());

#elif defined(_WIN32)

        merror_win32(nullptr, "SDL Window Error", "SDL Initialzing error: %s", SDL_GetError());

#elif defined(__APPLE__)

        merror_apple("SDL Window initialzing error: %s", SDL_GetError());

#endif
        return -1;
    }

    uint32_t sdl_extension_count = 0;
    const char* const* sdl_extension = SDL_Vulkan_GetInstanceExtensions(&sdl_extension_count);
    for (uint32_t i = 0; i < sdl_extension_count; i++)
    {
        extensions.push_back(sdl_extension[i]);
    }
    setup_vulkan(extensions);

    /* Create window surface */
    if (SDL_Vulkan_CreateSurface(window, o_instance, o_allocator, &surface) == 0)
    {
#if defined(__linux__)

        merror_linux("Failed to create Vulkan surface");

#elif defined(_WIN32)

        merror_win32(nullptr, "SDL Initialzing Error", "Failed to create Vulkan surface");

#elif defined(__APPLE__)

        merror_apple("Failed to create Vulkan surface");

#endif
        return 1;
    }

    SDL_GetWindowSize(window, &width, &height);
    vk_window = &o_mainwindowdata;
    setup_vulkan_window(vk_window, surface, width, height);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    return 0;
}