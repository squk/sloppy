list(APPEND MAIN_APP_SOURCES
    main.c
    gbc_cpu.c
    gbc_mmu.c
    gbc_ops.c
    gbc_ppu.c
)

#file(GLOB GLOB_RESULT  include/*.h)
#list(APPEND MAIN_APP_SOURCES ${GLOB_RESULT})
#file(GLOB GLOB_RESULT  src/*.c)
#list(APPEND MAIN_APP_SOURCES ${GLOB_RESULT})

set(MAIN_APP_LIBRARIES
        imgui
        glfw
        )

list(APPEND MAIN_APP_INCLUDE_DIRS
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/cimgui"
        )

set(NAME sloppy-emu)
add_executable(${NAME} ${MAIN_APP_SOURCES})
target_include_directories(${NAME} PUBLIC ${MAIN_APP_INCLUDE_DIRS})
target_link_libraries(${NAME} ${MAIN_APP_LIBRARIES})
