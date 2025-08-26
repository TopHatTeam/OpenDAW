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
    uint32_t properties_device_count = 0;
    ImVector<VkExtensionProperties> properties_device;
    vkEnumerateDeviceExtensionProperties(o_physicaldevice, nullptr, &properties_device_count, nullptr);
    properties_device.resize(properties_device_count);
    vkEnumerateDeviceExtensionProperties(o_physicaldevice, nullptr, &properties_device_count, properties_device.Data);

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
    wd->Surface                         = surface;
    wd->Width                           = width;
    wd->Height                          = height;
    wd->ClearValue.color.float32[0]     = 0.0f;
    wd->ClearValue.color.float32[1]     = 0.0f;
    wd->ClearValue.color.float32[2]     = 0.0f;
    VkBool32 supported                  = VK_FALSE;
    vkGetPhysicalDeviceSurfaceSupportKHR(o_physicaldevice, o_queuefamily, wd->Surface, &supported);
    if (supported != VK_TRUE)
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
    wd->PresentMode = ImGui_ImplVulkanH_SelectPresentMode(o_physicaldevice, wd->Surface, present_modes, IM_ARRAYSIZE(present_modes));


    /* Create SwapChain, RenderPass, FrameBuffer, etc */
    IM_ASSERT(o_minimagecount >= 2);
    ImGui_ImplVulkanH_CreateOrResizeWindow(o_instance, o_physicaldevice, o_device, wd, o_queuefamily, o_allocator, width, height, o_minimagecount);

    fmt::print("Vulkan window ready: {}x{}, Image = {}\n", wd->Width, wd->Height, wd->ImageCount);
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

    fmt::print("Initializing SDL3\n");
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
#if defined(__linux__)

        fmt::print("SDL Initialzing error: {}", SDL_GetError());
        //merror_linux("SDL Initialzing error: %s", SDL_GetError());

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

        fmt::print("SDL Window initialzing error: {}", SDL_GetError());
        //merror_linux("SDL Window initialzing error: %s", SDL_GetError());

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

    if (o_instance == VK_NULL_HANDLE)
    {
        fmt::print("Vulkan instance is invalid\n");
        return -1;
    }

    /* Create window surface */
    if (SDL_Vulkan_CreateSurface(window, o_instance, o_allocator, &surface) == 0)
    {
#if defined(__linux__)

        fmt::print("Failed to create vulkan surface");
        //merror_linux("Failed to create Vulkan surface");

#elif defined(_WIN32)

        merror_win32(nullptr, "SDL Initialzing Error", "Failed to create Vulkan surface");

#elif defined(__APPLE__)

        merror_apple("Failed to create Vulkan surface");

#endif
        return 1;
    }

    SDL_GetWindowSize(window, &width, &height);
    /*
    memset(&o_mainwindowdata, 0, sizeof(o_mainwindowdata));
        fuck this piece of shit code 
    */
    vk_window = &o_mainwindowdata;
    setup_vulkan_window(vk_window, surface, width, height);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    /* Now to finally show the window after Vulkan setup*/
    SDL_ShowWindow(window);    

    return 0;
}

void OpenDAW::render_gui(ImVec4 clearcolor, vector<audio_track_t>& tracks, int width, int height)
{
    ImGui_ImplVulkan_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::Begin("OpenDAW", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar);

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New Project", "Ctrl+N"))
            {
                
            }

            if (ImGui::MenuItem("Open Project", "Ctrl+O"))
            {

            }

            if (ImGui::MenuItem("Save Project", "Ctrl+S"))
            {

            }

            if (ImGui::MenuItem("Import", "Ctrl+S"))
            {

            }
            
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Copy", "Ctrl+C"))
            {

            }

            if (ImGui::MenuItem("Paste", "Ctrl+V"))
            {

            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Show MIDI", "Alt+M"))
            {
                if (show_midi != true)
                {
                    show_midi = true;
                }
                else 
                {
                    show_midi = false;
                }
            }

            if (ImGui::MenuItem("Show Mixer", "Alt+N"))
            {

            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Settings"))
        {
            if (ImGui::MenuItem("Audio Settings"))
            {

            }

            if (ImGui::MenuItem("Artist Settings"))
            {
                
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }
    
    /* The timeline track's horizontal zoom and scoll*/
    ImGui::SliderFloat("Zoom", &timeline_zoom, 0.25f, 4.0f);
    ImGui::SliderFloat("Scroll Horizontal", &timeline_scroll, 0.0f, 100.0f);
    ImGui::SliderFloat("Scroll vertical", &timeline_scroll_h, 0.0f, 100.0f);

    int track_height_win = height / 2;

    ImGui::BeginChild("TimelineRegion", ImVec2(width, track_height_win), true, ImGuiWindowFlags_HorizontalScrollbar);

    float track_height      = 40.0f;
    float time_to_pixels    = pixels_per_seconds * timeline_zoom;
    float total_track_height = tracks.size() * track_height;

    ImDrawList* track_draw_list         = ImGui::GetWindowDrawList();
    ImVec2      track_cursor            = ImGui::GetCursorPos();

    /* Draw track timeline grid (vertical lines) */
    for (int i = 0; i < 60; i++)
    {
        float x = track_cursor.x - timeline_scroll + i * time_to_pixels;
        track_draw_list->AddLine(ImVec2(x, track_cursor.y), ImVec2(x, track_cursor.y + height), IM_COL32(200, 200, 200, 80));
    }

    // Currently in development
    /* Draw track timeline grid (horizontal lines)*/
    //for (int i = 0; i < 60; i++)
    //{
    //    float y = track_cursor.y + timeline_scroll_h + i * time_to_pixels;
    //    track_draw_list->AddLine(ImVec2(track_cursor.x, y), ImVec2(track_cursor.x + width, y), IM_COL32(200, 200, 200, 80)); 
    //}

    /* Iterate tracks */
    for (size_t i = 0; i < tracks.size(); i++)
    {
        float y = track_cursor.y + i * track_height;

        /* Draw the track background*/
        track_draw_list->AddRectFilled(ImVec2(track_cursor.x, y), ImVec2(track_cursor.x + width, track_height),
        IM_COL32(50, 50, 50, 255));

        /* Track text*/
        ImGui::SetCursorScreenPos(ImVec2(track_cursor.x + 5, y + 5));
        ImGui::Text("%s", tracks[i].name.c_str());

        /* Draw the clips there is a complex bullshit formula need to make this so read carefully*/
        for (auto& clip : tracks[i].clip)
        {
            float xx = track_cursor.x - timeline_scroll + clip.start * time_to_pixels;
            float xxx = xx + clip.length * time_to_pixels;

            /* This variable can be read as this 
                ImU32 color;
                if (clip.selected)
                {
                    color = IM_COL32(200, 100, 100, 255);
                }
                else 
                {
                    color = IM_COL32(100, 200, 100, 255);
                }
            */
            ImU32 color = clip.selected ? IM_COL32(200, 100, 100, 255) : IM_COL32(100, 200, 100, 255);

            /* Make that clip into a rectangle*/
            track_draw_list->AddRectFilled(ImVec2(xx, y), ImVec2(xxx, y + track_height - 2), color, 4.0f);

            ImGui::SetCursorScreenPos(ImVec2(xx, y));
            ImGui::InvisibleButton(("clip" + std::to_string((uintptr_t)&clip)).c_str(), ImVec2(xxx - xx, track_height - 2));

            if (ImGui::IsItemClicked())
            {
                clip.selected = !clip.selected;
            }

            if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
            {
                float delta = ImGui::GetIO().MouseDelta.x / time_to_pixels;
                clip.start += delta;
                if (clip.start < 0) clip.start = 0;
            }   
        }
    }

    ImGui::EndChild();
    
    ImGui::End();

    if (show_midi == true)
    {
        show_piano_roll();
    }

    ImGui::Render();


    ImDrawData* draw_data = ImGui::GetDrawData();
    const bool is_minimized = (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f);

    if (!is_minimized)
    {
        vk_window->ClearValue.color.float32[0] = clearcolor.x * clearcolor.w;
        vk_window->ClearValue.color.float32[1] = clearcolor.y * clearcolor.w;
        vk_window->ClearValue.color.float32[2] = clearcolor.z * clearcolor.w;
        vk_window->ClearValue.color.float32[3] = clearcolor.w;
        frame_render(vk_window, draw_data);
        frame_present(vk_window);
    }

}

void OpenDAW::show_piano_roll()
{
    const int number_of_notes = 128;
    const float note_height = 20.0f;
    const int number_of_beats = 64;
    const float beat_width = 40.0f;
    static float scrolly = 0.0f;
    static float scrollx = 0.0f;

    ImGui::Begin("Piano Roll", nullptr);

    ImGui::BeginChild("Piano Keys", ImVec2(100, 600), true);

    if (ImGui::IsWindowHovered())
    {
        scrolly -= ImGui::GetIO().MouseWheel * 30.0f;
    }

    for (int i = number_of_notes - 1; i >= 0; i--)
    {
        char label[16];
        sprintf(label, "%d", i);

        bool is_it_a_black_key = (i % 12 == 1 || i % 12 == 3 || i % 12 == 6 || i % 12 == 8 || i % 12 == 10);

        if (is_it_a_black_key)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(40, 40, 40, 255));
            ImGui::Button(label, ImVec2(-1, note_height));
        }
        else 
        {
            ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(200, 200, 200, 255));
            ImGui::Button(label, ImVec2(-3, note_height));
        }

        ImGui::PopStyleColor();
    }
    
    ImGui::EndChild();
    
    ImGui::SameLine();

    ImGui::BeginChild("Midi Grid", ImVec2(0, 600), true, ImGuiWindowFlags_HorizontalScrollbar);

    ImDrawList* midi_draw_list = ImGui::GetWindowDrawList();

    ImVec2 origin = ImGui::GetCursorScreenPos();

    if (ImGui::IsWindowHovered())
    {
        scrolly -= ImGui::GetIO().MouseWheel * 30.0f;
        scrollx -= ImGui::GetIO().MouseWheelH * 30.0f;
    }

    /* Draw the horizontal lines*/
    for (int i = 0;  i <= number_of_notes; i++)
    {
        float y = origin.y + i * note_height - scrolly;
        midi_draw_list->AddLine(
            ImVec2(origin.x, y), 
            ImVec2(origin.x + number_of_beats * beat_width, y),
            IM_COL32(200, 200, 200, 255)
        );
    }

    for (int i = 0; i <= number_of_beats; i++)
    {
        float x = origin.x + i * beat_width - scrollx;
        midi_draw_list->AddLine(
            ImVec2(x, origin.y),
            ImVec2(x, origin.y + number_of_notes * note_height),
            IM_COL32(180, 180, 180, 255)
        );
    }

    ImGui::EndChild();

    ImGui::End();
}   

void OpenDAW::gui_input()
{
    /* The reason we check if alt is held down and not check if m is held down; is because
        MAJOR LOGIC ERROR if you do so. Every frame 
    */
    if (ImGui::IsKeyDown(ImGuiMod_Alt) && ImGui::IsKeyPressed(ImGuiKey_M))
    {
        if (show_midi != true)
        {
            show_midi = true;
        }
        else 
        {
            show_midi = false;
        }
    }
}