cmake_minimum_required(VERSION 3.20)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

project(astronomy_framework
    VERSION 0.0.1
    LANGUAGES C CXX
)

# 1. Compiler and C++ Standard Settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 2. Fetch and Build Raylib
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        5.0
)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # Don't build raylib examples
FetchContent_MakeAvailable(raylib)

# 3. Collect Source Files
file(GLOB_RECURSE CORE_SOURCES
    "src/*.cpp"
)
list(FILTER CORE_SOURCES EXCLUDE REGEX ".*/main\\.cpp$")

# 4. Create Main Application Executable
add_executable(astronomy_framework
    src/main.cpp
    ${CORE_SOURCES}
)

target_include_directories(astronomy_framework
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(astronomy_framework
    PRIVATE
        raylib
)

# 5. Unit Testing Target & CTest Integration
enable_testing()

add_executable(unit_tests_runner
    unit_tests/test_main.cpp
    ${CORE_SOURCES}
)

target_include_directories(unit_tests_runner
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(unit_tests_runner
    PRIVATE
        raylib
)

add_test(NAME unit_tests COMMAND unit_tests_runner)
