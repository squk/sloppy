#include <iostream>
#include "gbc_emu.hpp"
#include "gbc_io.h"

#include "dmg_rom.h"
#include "01_special.h"
#include "02_interrupts.h"
#include "03_op_sp_hl.h"
#include "04_op_r_imm.h"
#include "05_op_rp.h"
#include "06_ld_r_r.h"
#include "07_jr_jp_call_ret_rst.h"
#include "08_misc_instr.h"
#include "09_op_r_r.h"
#include "10_bit_ops.h"
#include "11_op_a_mhl.h"

u32 purpg_palette[4] = {
    0x332c50,
    0x46878f,
    0x94e344,
    0xe2f3e4
};

u32 grey_palette[4] = {
    0xFFFFFF,
    0xAAAAAA,
    0x555555,
    0x000000
};

u32 gbc_emu::get_paletted_color(u8 color) {
    u8 r=0, g=0, b=0;
    //return purpg_palette[color];
    if (color > 3) {
        return 0xFF0000; // red is invalid color requested
    }
    return grey_palette[color];
}

gbc_emu::gbc_emu() {
    cpu.mmu = &mmu;
    cpu.mmu->counter = &cpu.counter;
    ppu.mmu = &mmu;
    cpu.ppu = &ppu;

#if defined(SLOPPY_RENDER)
    int r = gui_init();
    if (r) {
        std::cout << "failed to init GUI " << r << std::endl;
    }
#endif

    cpu.reset();
    mmu.init();
    ppu.init();
    //theme_corporate_grey();
    theme_grey();
}

void gbc_emu::run() {
    cpu.set_boot_state();
    cpu.loop();
}

void gbc_emu::test() {
    //memcpy(mmu.bios, DMG_ROM_bin, DMG_ROM_bin_len);
    cpu.set_boot_state();
    cpu.mmu->io[0x00] = 0xFF;

    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/ei_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/instr/daa.gb"); // PASSED

    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/oam_dma/basic.gb"); // PASSED
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/oam_dma/reg_read.gb"); // PASSED
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/oam_dma/sources-GS.gb");

    // instr timing tests
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/add_sp_e_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/boot_div-dmgABCmgb.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/boot_div2-S.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/boot_hwio-S.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/boot_hwio-dmgABCmgb.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/boot_regs-dmgABC.gb"); // PASS
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/boot_regs-mgb.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/boot_regs-sgb.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/boot_regs-sgb2.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/call_cc_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/call_cc_timing2.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/call_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/call_timing2.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/di_timing-GS.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/ei_sequence.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/ei_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/halt_ime0_ei.gb"); // PASS
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/halt_ime0_nointr_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/halt_ime1_timing.gb"); // PASS
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/halt_ime1_timing2-GS.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/if_ie_registers.gb"); // PASSED
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/intr_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/jp_cc_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/jp_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/ld_hl_sp_e_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/oam_dma_restart.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/oam_dma_start.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/oam_dma_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/pop_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/push_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/rapid_di_ei.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/ret_cc_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/ret_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/reti_intr_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/reti_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/rst_timing.gb");

    // timer tests
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/div_timing.gb"); // PASS
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/timer/div_write.gb"); // PASS
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/timer/rapid_toggle.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/timer/tim00.gb"); // PASS
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/timer/tim01.gb"); // PASS
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/timer/tim10.gb"); // PASS
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/timer/tim11.gb"); // PASS
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/timer/tim00_div_trigger.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/timer/tim01_div_trigger.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/timer/tim10_div_trigger.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/timer/tim11_div_trigger.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/timer/tima_reload.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/timer/tima_write_reloading.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/timer/tma_write_reloading.gb");

    // mbc tests
    //mmu.load_rom_file("./data/mbc1/bits_bank1.gb"); // PASSED
    //mmu.load_rom_file("./data/mbc1/bits_bank2.gb"); // PASSED
    //mmu.load_rom_file("./data/pokemon_blue_gb.bin");
    //mmu.load_rom_file("./data/mbc1/bits_mode.gb"); // PASSED
    //mmu.load_rom_file("./data/mbc1/bits_ramg.gb"); // PASSED
    //mmu.load_rom_file("./data/mbc1/multicart_rom_8Mb.gb");
    //mmu.load_rom_file("./data/mbc1/ram_64kb.gb");
    //mmu.load_rom_file("./data/mbc1/ram_256kb.gb"); // PASSED

    //mmu.load_rom_file("./data/mbc1/rom_512kb.gb"); // PASSED
    //mmu.load_rom_file("./data/mbc1/rom_1Mb.gb"); // PASSED
    //mmu.load_rom_file("./data/mbc1/rom_2Mb.gb"); // PASSED
    //mmu.load_rom_file("./data/mbc1/rom_4Mb.gb"); // PASSED
    //mmu.load_rom_file("./data/mbc1/rom_8Mb.gb"); // PASSED
    //mmu.load_rom_file("./data/mbc1/rom_16Mb.gb"); // PASSED

    // ppu tests
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/ppu/intr_2_mode0_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/ppu/intr_2_mode4_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/ppu/intr_2_oam_ok_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/ppu/intr_2_0_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/ppu/intr_2_mode0_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/ppu/intr_2_mode0_timing_sprites.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/ppu/intr_2_mode3_timing.gb");

    // interrupts
    //mmu.load_rom_file("./data/mooneye-gb_hwtests/acceptance/interrupts/ie_push.gb");
    //mmu.load_rom_file("./data/tests/interrupt_time/interrupt_time.gb");

    // mem-timing  - do this before interrupt timing?
    //mmu.load_rom_file("./data/tests/mem_timing/individual/01-read_timing.gb");
    //mmu.load_rom_file("./data/tests/mem_timing/individual/02-write_timing.gb");
    //mmu.load_rom_file("./data/tests/mem_timing/individual/03-modify_timing.gb");

    //mmu.load_rom_file("./DrMario.gb");
    //mmu.load_rom_file("./Tetris.gb");
    //mmu.load_rom_file("DK.gb");
    mmu.load_rom_file("./MarioLand.gb"); // required mapper
    //mmu.load_rom_file("data/m2_win_en_toggle.gb");
    //mmu.load_rom_file("dmg-acid2.gb"); // required mapper
    //mmu.load_rom_file("dmg-acid2-preview.gb"); // required mapper
    //mmu.load_rom_file("data/sprite_priority.gb");
    //mmu.load_rom_file("data/tests/oam_bug/rom_singles/4-scanline_timing.gb");

    // CPU instruction tests
    //mmu.load_rom_file("data/tests/oam_bug/oam_bug.gb");
    //mmu.load_rom_file("which.gb");
    //mmu.load_rom_file("data/tests/cpu_instrs/cpu_instrs.gb");
    //mmu.load_rom_file("data/tests/instr_timing/instr_timing.gb");
    while(!cpu.quit) {
        if (ppu.vblank) {
            ppu.vblank = false;
            int r = gui_step();
            if (r == -1) {
                cpu.quit = true;
            }
            ppu.start_frame(); // i don't like this here
        }
        cpu.step();
    }

#if defined(SLOPPY_RENDER)
    gui_exit();
#endif
}

#if defined(SLOPPY_RENDER)
const std::string shaderSource =
#include "sloppy_gui/shaders/gbc-color.vs"
;
#endif

int gbc_emu::gui_init() {
#if defined(SLOPPY_RENDER)
    // Setup SDL
    // (Some versions of SDL before <2.0.10 appears to have performance/stalling issues on a minority of Windows systems,
    // depending on whether SDL_INIT_GAMECONTROLLER is enabled or disabled.. updating to latest version of SDL is recommended!)
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // Decide GL+GLSL versions
#if __APPLE__
    // GL 3.2 Core + GLSL 150
    const char* glsl_version = "#version 150";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    window = SDL_CreateWindow("sloppy emu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    //SDL_GL_SetSwapInterval(1); // Enable vsync

    // Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
    bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
    bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
    bool err = gladLoadGL() == 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
    bool err = false;
    glbinding::Binding::initialize();
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
    bool err = false;
    glbinding::initialize([](const char* name) { return (glbinding::ProcAddress)SDL_GL_GetProcAddress(name); });
#else
    bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Create a OpenGL texture identifier
    glGenTextures(1, &lcd_tex);
    glGenTextures(1, &bg_tex);
    glGenTextures(1, &win_tex);
    glGenTextures(1, &obj_tex);
    glGenTextures(1, &tiledata_tex);

    // build and compile our shader program
    // vertex shader
    int shader = glCreateShader(GL_VERTEX_SHADER);
    const char* src = shaderSource.c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    // link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, shader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return -1;
    }
    glDeleteShader(shader);
    glUseProgram(shaderProgram);

#endif
    return 0;
}

int gbc_emu::gui_step() {
#if defined(SLOPPY_RENDER)
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImVec4 clear_color = ImVec4(0.5f, 0.5f, 0.5f, 1.00f);


    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
            return -1;
        if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE && e.window.windowID == SDL_GetWindowID(window))
            return -1;
        if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_ESCAPE) {
                return -1;
            }
        }
    }

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);
    ImGui::NewFrame();

    emulator_window();
    map_window();
    tiledata_window();
    cpu_window();
    mbc_window();
    io_window();
    serial_window();

    ImGui::Begin("Debug");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
    // Rendering
    ImGui::Render();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(window);
#endif
    return 0;
}

void gbc_emu::gui_exit() {
#if defined(SLOPPY_RENDER)
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
#endif
}
