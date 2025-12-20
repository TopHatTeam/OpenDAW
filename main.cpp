// ---------------------------------------------------------
//
//  OpenDAW
//
//  Andrew Conner Skatzes (C) 2025
//
//  BSD-3 Clause license
//
//  Description:
//      The Main entry to the program
//
// ---------------------------------------------------------

#include "headers/AudioCore.h"
#include "headers/AudioError.h"
#include "headers/gui.hpp"
#include <pthread.h>
// #include "headers/DawUI.hpp"

using std::vector;

int main(int argc, char *argv[])
{
    static vector<audio_track_t> the_culprit;
    static vector<audio_track_t>& tracks = the_culprit;
    AudioCore_Init("default", 44100);

    /* We need to see the damages and make sure the program isn't total'd*/
    if (OpenDAW::create_window() != 0)
    {
        fmt::print("Failed to initalize OpenDAW window\n");
        return -1;
    }

    bool running = true;
    SDL_Event event;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    VkResult err;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(OpenDAW::main_scale);
    style.FontScaleDpi = OpenDAW::main_scale;

    ImGui_ImplSDL3_InitForVulkan(OpenDAW::window);

    if (!OpenDAW::vk_window)
    {
        printf("Vulkan window is null\n");
        //fmt::print("Vulkan window is null\n");
        return -1;
    }

    if (OpenDAW::vk_window->RenderPass == VK_NULL_HANDLE)
    {
        printf("Vulkan RenderPass is not ready\n");
        //fmt::print("Vulkan RenderPass is not ready\n");
        return -1;
    }

    ImGui_ImplVulkan_InitInfo init_info = {};
    init_info.Instance          = OpenDAW::o_instance;
    init_info.PhysicalDevice    = OpenDAW::o_physicaldevice;
    init_info.Device            = OpenDAW::o_device;
    init_info.QueueFamily       = OpenDAW::o_queuefamily;
    init_info.Queue             = OpenDAW::o_queue;
    init_info.PipelineCache     = OpenDAW::o_pipelinecache;
    init_info.DescriptorPool    = OpenDAW::o_descriptorpool;
    init_info.RenderPass        = OpenDAW::vk_window->RenderPass;
    init_info.Subpass           = 0;
    init_info.MinImageCount     = OpenDAW::o_minimagecount;
    init_info.ImageCount        = OpenDAW::vk_window->ImageCount;
    init_info.MSAASamples       = VK_SAMPLE_COUNT_1_BIT;
    init_info.Allocator         = OpenDAW::o_allocator;
    init_info.CheckVkResultFn   = OpenDAW::check_vk_result;
    ImGui_ImplVulkan_Init(&init_info);

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(OpenDAW::window))
            {
                running = false;
            }

            if (OpenDAW::quit_app != false)
            {
                running = false;
            }

            int fb_width;
            int fb_height;
            SDL_GetWindowSize(OpenDAW::window, &fb_width, &fb_height);
            if (fb_width > 0 && fb_height > 0 && (OpenDAW::o_swapchainrebuild 
                || OpenDAW::o_mainwindowdata.Width != fb_width 
                || OpenDAW::o_mainwindowdata.Height != fb_height))
            {
                ImGui_ImplVulkan_SetMinImageCount(OpenDAW::o_minimagecount);
                ImGui_ImplVulkanH_CreateOrResizeWindow(OpenDAW::o_instance, 
                    OpenDAW::o_physicaldevice, OpenDAW::o_device, 
                    &OpenDAW::o_mainwindowdata, OpenDAW::o_queuefamily,
                    OpenDAW::o_allocator, fb_width, fb_height, 
                    OpenDAW::o_minimagecount);
                OpenDAW::o_mainwindowdata.FrameIndex = 0;
                OpenDAW::o_swapchainrebuild = false;
            }

            /* Now here comes the real Graphical user interface*/
            OpenDAW::render_gui(clear_color, tracks, fb_width, fb_height);
            OpenDAW::gui_input();
        }
    }

    AudioCore_Cleanup();

    OpenDAW::cleanup_vulkan();
    OpenDAW::cleanup_vulkan_window();

    err = vkDeviceWaitIdle(OpenDAW::o_device);
    OpenDAW::check_vk_result(err);
    ImGui_ImplVulkan_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyWindow(OpenDAW::window);
    SDL_Quit();

    return 0;
}