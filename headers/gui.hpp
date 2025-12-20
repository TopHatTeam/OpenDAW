// ---------------------------------------------------------
//
//  OpenDAW
//
//  Andrew Conner Skatzes (C) 2025
//
//  BSD-3 Clause license
//
//  Description:
//      Graphical user interface for OpenDAW
//
// ---------------------------------------------------------

#ifndef GUI_HPP
#define GUI_HPP

#include <fmt/std.h>
#include <fmt/core.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#include <vulkan/vulkan.hpp>
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_vulkan.h"
#include "ImGuiFileDialog.h"
#include "AudioCore.h"

/* by the way if building this gives you multiple declaring of any of these things defined in the namespace
    it's most likely because of forgetting inline for variables
*/

using std::vector, std::string;

struct audio_track_t
{   
    string name;
    vector<audio_clip_t> clip;
};

namespace OpenDAW 
{
    inline VkAllocationCallbacks*   o_allocator         = nullptr;
    inline VkInstance               o_instance          = VK_NULL_HANDLE;
    inline VkPhysicalDevice         o_physicaldevice    = VK_NULL_HANDLE;
    inline VkDevice                 o_device            = VK_NULL_HANDLE;
    inline uint32_t                 o_queuefamily       = (uint32_t)-1;
    inline VkQueue                  o_queue             = VK_NULL_HANDLE;
    inline VkPipelineCache          o_pipelinecache     = VK_NULL_HANDLE;
    inline VkDescriptorPool         o_descriptorpool    = VK_NULL_HANDLE;
    inline ImGui_ImplVulkanH_Window o_mainwindowdata    = {};
    inline uint32_t                 o_minimagecount     = 2;
    inline bool                     o_swapchainrebuild  = false;

    inline VkSurfaceKHR                surface          = VK_NULL_HANDLE;
    inline VkResult                    window_error;
    inline int                         width, height;
    inline ImGui_ImplVulkanH_Window*   vk_window        = nullptr;

    static inline float                 timeline_zoom       = 1.0f;
    static inline float                 timeline_scroll     = 0.0f;
    static inline float                 timeline_scroll_h     = 0.0f;
    static inline float                 pixels_per_seconds  = 100.0f;
    static inline bool                  show_midi           = false;
    static inline bool                  show_mixer          = false;
    static inline bool                  quit_app            = false;

    
    // -- SDL3 variables --
    inline float                   main_scale;
    inline SDL_WindowFlags         window_flags;
    inline SDL_Window*             window                      = nullptr;
    inline ImVector<const char*>   extensions;

    void check_vk_result(VkResult err);

    bool is_extension_available(const ImVector<VkExtensionProperties>& properties, const char* extension);

    void setup_vulkan(ImVector<const char*> instance_extension);

    void setup_vulkan_window(ImGui_ImplVulkanH_Window* wd, VkSurfaceKHR surface, int width, int height);

    void cleanup_vulkan();

    void cleanup_vulkan_window();

    void frame_render(ImGui_ImplVulkanH_Window* wd, ImDrawData* draw_data);

    static void frame_present(ImGui_ImplVulkanH_Window* wd);

    int create_window();

    /**
     * @brief This renders the Graphical User Interface
     * @param clearcolor The color that displays when you clear the screen
     * @param tracks a vector reference to the tracks structure
     * @param width The width of the window
     * @param height The height of the window
     * @returns void
     */
    void render_gui(ImVec4 clearcolor, vector<audio_track_t>& tracks, int width, int height);

    void show_piano_roll();

    void gui_input();
}

#endif