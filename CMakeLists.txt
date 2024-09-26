cmake_minimum_required(VERSION 3.10)

project(particle_life VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find required packages
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
find_package(OpenMP REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.3 REQUIRED)

set(SFML_LIBS sfml-graphics sfml-system sfml-window)
set(OMP_LIBS OpenMP::OpenMP_CXX)
set(OGL_LIBS OpenGL::GL GLEW::GLEW glfw)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/graphics/*.cpp")
# Add the executable (replace main.cpp with your source files)
add_executable(particle_life ${SOURCES})

target_include_directories(particle_life PUBLIC ${CMAKE_SOURCE_DIR}/include)

if(OpenMP_CXX_FOUND)
  target_link_libraries(particle_life PUBLIC ${OMP_LIBS} ${OGL_LIBS})
endif()

# debug

# Add a separate executable for debugging
add_executable(particle_life_debug ${SOURCES})

# Set the debug compile options
target_compile_definitions(particle_life_debug PRIVATE DEBUG)

# Optionally set compiler flags for debug mode (this example assumes GCC/Clang)
target_compile_options(particle_life_debug PRIVATE
    $<$<CONFIG:DEBUG>:-g -O0>  # Enable debug symbols and disable optimizations
)

target_include_directories(particle_life_debug PUBLIC ${CMAKE_SOURCE_DIR}/include)

if(OpenMP_CXX_FOUND)
  target_link_libraries(particle_life_debug PUBLIC ${OMP_LIBS} ${OGL_LIBS})
endif()

# Set the debug executable as the target for the debug build
set_target_properties(particle_life_debug PROPERTIES DEBUG_POSTFIX "_debug")
