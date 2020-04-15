#pragma once

#include <stdio.h>
#include <string>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

#include "types.h"
#include "gbc_cpu.hpp"
#include "gbc_ppu.hpp"
#include "gbc_mmu.hpp"
//#include "gbc_ops.hpp"

// About Desktop OpenGL function loaders:
//  Modern desktop OpenGL doesn't have a standard portable header file to load OpenGL function pointers.
//  Helper libraries are often used for this purpose! Here we are supporting a few common ones (gl3w, glew, glad).
//  You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>            // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>            // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>          // Initialize with gladLoadGL()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
#define GLFW_INCLUDE_NONE       // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/Binding.h>  // Initialize with glbinding::Binding::initialize()
#include <glbinding/gl/gl.h>
using namespace gl;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
#define GLFW_INCLUDE_NONE       // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/glbinding.h>// Initialize with glbinding::initialize()
#include <glbinding/gl/gl.h>
using namespace gl;
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

class gbc_emu {
    private:
        void emulator_window();
        void map_window();
        void cpu_window();
        void mbc_window();
        void io_window();
        void serial_window();
        u32 get_paletted_color(u8 color);

    public:
        gbc_cpu cpu;
        gbc_ppu ppu;
        gbc_mmu mmu;

        SDL_Window *window = nullptr;
        SDL_GLContext gl_context;
        GLuint lcd_tex, bg_tex, win_tex;

        gbc_emu();
        void run();
        void test();

        int gui_init();
        int gui_step();
        void gui_exit();
};
