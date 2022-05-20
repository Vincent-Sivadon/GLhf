cmake_minimum_required(VERSION 3.0)

# Notre projet est étiqueté mylib
project(GLhf)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Libraries
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} external/cmake/)
find_package(glfw3 REQUIRED)
find_package(glew REQUIRED)
find_package(glm REQUIRED)
set(LIBS opengl32 glew32 glfw3)

# Files
file(GLOB SRCS "src/*.cpp")
file(GLOB HEADERS "include/*.h")
file(GLOB SHADERS "resources/shaders/examples/*" "resources/shaders/primitives/*")

# Include directories
set(GLHF_INCLUDE_DIRS include)
set(LIB_INCLUDE_DIRS external/include)
set(INCLUDE_DIRS ${GLHF_INCLUDE_DIRS} ${LIB_INCLUDE_DIRS})

# Create GLhf library
add_library(GLhf SHARED ${SRCS} ${HEADERS})
target_link_libraries(GLhf ${LIBS})
target_include_directories(GLhf PUBLIC ${INCLUDE_DIRS})
target_compile_options(GLhf PUBLIC -g)

# GLhf Samples
file(GLOB SAMPLES samples/*.cpp)
foreach(sample_source ${SAMPLES})
  # Change source file with absolute path like C:/dev/GLhf/samples/instancing.cpp
  # to the target namem instancing
  string(REPLACE ".cpp" "" sample ${sample_source})
  string(REPLACE ${CMAKE_SOURCE_DIR}/samples/ "" sample ${sample})

  # Create executable
  add_executable(${sample} ${sample_source})
  target_link_libraries(${sample} GLhf)
  target_include_directories(${sample} PUBLIC ${GLHF_INCLUDE_DIRS})
  target_compile_options(${sample} PUBLIC -std=c++17 -g)
endforeach(sample_source ${SAMPLES})