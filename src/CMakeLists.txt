list(APPEND MAIN_APP_SOURCES
    main.cpp
    gbc_emu.cpp
    gbc_cpu.cpp
    gbc_ops.c
    gbc_mmu.cpp
    gbc_mbc.cpp
    gbc_ppu.cpp

    sloppy_gui/emulator_window.cpp
    sloppy_gui/map_window.cpp
    sloppy_gui/cpu_window.cpp
    sloppy_gui/io_window.cpp
    sloppy_gui/mbc_window.cpp

    ../modules/imgui/imgui.cpp
    ../modules/imgui/imgui_draw.cpp
    ../modules/imgui/imgui_widgets.cpp

    imgui/imgui_impl_sdl.cpp
    imgui/imgui_impl_opengl3.cpp
    )

set(ENV{PATH} ${CMAKE_SOURCE_DIR}:$ENV{PATH})
set(CMAKE_C_COMPILER g++)

set(MAIN_APP_LIBRARIES
    glfw
    GLEW
    dl
    )

list(APPEND MAIN_APP_INCLUDE_DIRS
    "/usr/local/include"
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/modules/imgui"
    )

set(NAME sloppy-emu)
add_executable(${NAME} ${MAIN_APP_SOURCES})

target_include_directories(${NAME} PUBLIC ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
    ${SDL2_TTF_INCLUDE_DIR})
target_link_libraries(${NAME}
    ${GLFW_LIBRARIES}
    ${OPENGL_LIBRARY}
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES})

target_include_directories(${NAME} PUBLIC ${MAIN_APP_INCLUDE_DIRS})
target_link_libraries(${NAME} ${MAIN_APP_LIBRARIES})
