cmake_minimum_required(VERSION 3.5)

# ================================
# Project
# ================================
project(OFDM-PHY-Layer-Simulator
    VERSION 1.0.0
    DESCRIPTION "OFDM simulation in C with QAM modulation"
    LANGUAGES C
)

# ================================
# Generate compilation database
# ================================
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(STATUS "Building ${PROJECT_NAME} v${PROJECT_VERSION} on ${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR}")

# ================================
# Sources
# ================================
set(SOURCES
    src/main.c
    src/qam.c
    src/ofdm.c
    src/ifft.c
    src/fft.c
)

add_executable(run ${SOURCES})
target_include_directories(run PRIVATE ${CMAKE_SOURCE_DIR}/include)

# ================================
# Compiler version & flags
# ================================
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_C_COMPILER_VERSION VERSION_LESS 8.0)
        message(FATAL_ERROR "GCC >= 8.0 required")
    endif()
    target_compile_options(run PRIVATE
        -Wall -Wextra -Wpedantic
        -std=c99
        -Werror
        -Wconversion -Wsign-conversion
        -Wshadow
        -Wnull-dereference
        -fstack-protector-strong
        -fPIE -fPIC
        $<$<CONFIG:Release>:-O2>
    )

elseif(CMAKE_C_COMPILER_ID MATCHES "Clang")
    if(CMAKE_C_COMPILER_VERSION VERSION_LESS 6.0)
        message(FATAL_ERROR "Clang >= 6.0 required")
    endif()
    target_compile_options(run PRIVATE
        -Wall -Wextra -Wpedantic
        -std=c99
        -Werror
        -Wconversion -Wsign-conversion
        -Wshadow
        -Wnull-dereference
        -fstack-protector-strong
        -fPIE -fPIC
        $<$<CONFIG:Release>:-O2>
    )

elseif(MSVC)
    target_compile_options(run PRIVATE
        /W4 /WX
        /permissive-
        /guard:cf
        /GS
    )
endif()

# ================================
# clang-tidy (C mode)
# ================================
find_program(CLANG_TIDY_EXE NAMES clang-tidy)
if(CLANG_TIDY_EXE)
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set_target_properties(run PROPERTIES
        C_CLANG_TIDY "${CLANG_TIDY_EXE};--config-file=${CMAKE_SOURCE_DIR}/.clang-tidy"
    )
endif()

# ================================
# clang-format (manual target)
# ================================
find_program(CLANG_FORMAT_EXE NAMES clang-format)
if(CLANG_FORMAT_EXE)
    add_custom_target(format
        COMMAND ${CLANG_FORMAT_EXE} -i
            ${SOURCES}
            ${CMAKE_SOURCE_DIR}/include/*.h
        COMMENT "Running clang-format"
    )
endif()