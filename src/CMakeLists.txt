list(APPEND MAIN_APP_SOURCES
    main.cpp
    gbc_emu.cpp
    gbc_cpu.cpp
    gbc_ops.c
    gbc_mmu.cpp
    gbc_mbc.cpp
    gbc_ppu.cpp
    )

set(ENV{PATH} ${CMAKE_SOURCE_DIR}:$ENV{PATH})
set(CMAKE_C_COMPILER g++)

set(MAIN_APP_LIBRARIES)

list(APPEND MAIN_APP_INCLUDE_DIRS
        "/usr/local/include"
        "${CMAKE_SOURCE_DIR}/include"
        )

set(NAME sloppy-emu)
add_executable(${NAME} ${MAIN_APP_SOURCES})

target_include_directories(${NAME} PUBLIC ${MAIN_APP_INCLUDE_DIRS})
target_link_libraries(${NAME} ${MAIN_APP_LIBRARIES})
