# CMake generated Testfile for 
# Source directory: /home/tantham-tanthuvanit/projects/AstronomyFramework
# Build directory: /home/tantham-tanthuvanit/projects/AstronomyFramework/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[unit_tests]=] "/home/tantham-tanthuvanit/projects/AstronomyFramework/build/unit_tests_runner")
set_tests_properties([=[unit_tests]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/tantham-tanthuvanit/projects/AstronomyFramework/CMakeLists.txt;70;add_test;/home/tantham-tanthuvanit/projects/AstronomyFramework/CMakeLists.txt;0;")
subdirs("_deps/raylib-build")
