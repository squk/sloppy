list(APPEND MAIN_APP_SOURCES
    main.c
    gbc_cpu.c
    gbc_mmu.c
    gbc_ops.c
    gbc_ppu.c
    imgui/imgui_impl_sdl.cpp
    imgui/imgui_impl_opengl3.cpp
    )

set(ENV{PATH} ${CMAKE_SOURCE_DIR}:$ENV{PATH})
set(CMAKE_C_COMPILER g++)
#file(GLOB GLOB_RESULT  include/*.h)
#list(APPEND MAIN_APP_SOURCES ${GLOB_RESULT})
#file(GLOB GLOB_RESULT  src/*.c)
#list(APPEND MAIN_APP_SOURCES ${GLOB_RESULT})

set(MAIN_APP_LIBRARIES
        imgui
        glfw
        )

list(APPEND MAIN_APP_INCLUDE_DIRS
        "${CMAKE_SOURCE_DIR}/include"
        "${CMAKE_SOURCE_DIR}/modules/nuklear"
        )

set(NAME sloppy-emu)
add_executable(${NAME} ${MAIN_APP_SOURCES})

target_include_directories(${NAME} PUBLIC ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
    ${SDL2_TTF_INCLUDE_DIR})
target_link_libraries(${NAME}
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES})

target_include_directories(${NAME} PUBLIC ${MAIN_APP_INCLUDE_DIRS})
target_link_libraries(${NAME} ${MAIN_APP_LIBRARIES})
