cmake_minimum_required(VERSION 3.20)

project(astronomy_framework
    VERSION 0.0.1
    LANGUAGES C CXX
)

# -----------------------------------------------------------------------------
# 1. Compiler and Standard Settings
# -----------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Output binaries in a consistent directory across all platforms and generators
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# -----------------------------------------------------------------------------
# 2. Build Options
# -----------------------------------------------------------------------------
option(BUILD_TESTING "Build unit tests" ON)
option(FORCE_FETCH_RAYLIB "Force downloading Raylib via FetchContent" OFF)
option(USE_WAYLAND "Enable Wayland display backend for Raylib on Linux" OFF)

# -----------------------------------------------------------------------------
# 3. Platform & Cross-Compilation Adjustments
# -----------------------------------------------------------------------------
if(EMSCRIPTEN)
    set(PLATFORM "Web" CACHE STRING "Raylib target platform" FORCE)
endif()

# -----------------------------------------------------------------------------
# 4. Raylib Dependency Resolution
# -----------------------------------------------------------------------------
# Check if raylib is already installed on the host device (via apt, brew, vcpkg, pacman, etc.)
# If not found or forced, use FetchContent with shallow clone (fast, lightweight).
if(NOT FORCE_FETCH_RAYLIB)
    find_package(raylib QUIET)
endif()

if(NOT raylib_FOUND)
    include(FetchContent)
    set(FETCHCONTENT_QUIET FALSE)

    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG        5.0
        GIT_SHALLOW    TRUE
    )

    # Disable unnecessary targets to minimize build times and memory usage
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

    if(UNIX AND NOT APPLE AND NOT EMSCRIPTEN AND USE_WAYLAND)
        set(USE_WAYLAND ON CACHE BOOL "" FORCE)
    endif()

    FetchContent_MakeAvailable(raylib)
endif()

# Normalize Raylib target name across package and FetchContent modes
if(TARGET raylib::raylib AND NOT TARGET raylib)
    add_library(raylib ALIAS raylib::raylib)
endif()

# -----------------------------------------------------------------------------
# 5. Core Library (astronomy_core)
# -----------------------------------------------------------------------------
# Collect core sources (all src/*.cpp excluding main.cpp)
file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS
    "src/*.cpp"
)
list(FILTER CORE_SOURCES EXCLUDE REGEX ".*/main\\.cpp$")

# Build core logic once as a static library to prevent duplicate compilation
add_library(astronomy_core STATIC
    ${CORE_SOURCES}
)

target_include_directories(astronomy_core
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/external>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(astronomy_core
    PUBLIC
        raylib
)

# Cross-platform system library linkages
if(WIN32)
    target_link_libraries(astronomy_core PUBLIC winmm gdi32 opengl32 shell32 user32)
elseif(APPLE)
    target_link_libraries(astronomy_core PUBLIC
        "-framework IOKit"
        "-framework Cocoa"
        "-framework OpenGL"
        "-framework CoreVideo"
    )
elseif(UNIX AND NOT APPLE AND NOT EMSCRIPTEN)
    target_link_libraries(astronomy_core PUBLIC m pthread dl)
endif()

# Target-specific compiler options
if(MSVC)
    target_compile_options(astronomy_core PRIVATE /W4 /utf-8 /permissive- /MP)
    target_compile_definitions(astronomy_core PUBLIC _CRT_SECURE_NO_WARNINGS)
else()
    target_compile_options(astronomy_core PRIVATE -Wall -Wextra)
endif()

# -----------------------------------------------------------------------------
# 6. Main Executable (astronomy_framework)
# -----------------------------------------------------------------------------
add_executable(astronomy_framework
    src/main.cpp
)

target_link_libraries(astronomy_framework
    PRIVATE
        astronomy_core
)

if(MSVC)
    target_compile_options(astronomy_framework PRIVATE /W4 /utf-8 /permissive- /MP)
else()
    target_compile_options(astronomy_framework PRIVATE -Wall -Wextra)
endif()

# Emscripten / WebAssembly specific flags
if(EMSCRIPTEN)
    set_target_properties(astronomy_framework PROPERTIES SUFFIX ".html")
    target_link_options(astronomy_framework PRIVATE
        -sUSE_GLFW=3
        -sALLOW_MEMORY_GROWTH=1
    )
endif()

# -----------------------------------------------------------------------------
# 7. Unit Tests & CTest Integration
# -----------------------------------------------------------------------------
include(CTest)

if(BUILD_TESTING)
    add_executable(unit_tests_runner
        unit_tests/test_main.cpp
    )

    target_link_libraries(unit_tests_runner
        PRIVATE
            astronomy_core
    )

    if(MSVC)
        target_compile_options(unit_tests_runner PRIVATE /W4 /utf-8 /permissive- /MP)
    else()
        target_compile_options(unit_tests_runner PRIVATE -Wall -Wextra)
    endif()

    # Automatically copy test data file to test runner directory so tests run anywhere
    add_custom_command(
        TARGET unit_tests_runner POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/unit_tests/math_test.json"
            "$<TARGET_FILE_DIR:unit_tests_runner>/math_test.json"
        COMMENT "Copying math_test.json to unit_tests_runner output directory"
    )

    # Register CTest test with explicit working directory
    add_test(NAME unit_tests COMMAND unit_tests_runner)
    set_tests_properties(unit_tests PROPERTIES
        WORKING_DIRECTORY "$<TARGET_FILE_DIR:unit_tests_runner>"
    )
endif()

# -----------------------------------------------------------------------------
# 8. Installation Support
# -----------------------------------------------------------------------------
install(TARGETS astronomy_framework
    RUNTIME DESTINATION bin
)
install(DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)
