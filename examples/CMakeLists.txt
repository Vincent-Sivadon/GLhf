# ===== Examples of GLhf library ===== #

cmake_minimum_required(VERSION 3.0)

# Notre projet est étiqueté mylib
project(GLhfExamples)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

find_package(GLhf REQUIRED)



file(GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# For every EXAMPLE
foreach(example_source_file ${SRCS})
  # file ( GLOB ... ) gives absolute paths, we then transform it in relative
  # paths for example :
  # "/home/vincents/Documents/Projet/Enumeration-of-Maximal-Induced-Bicliques/examples/src/areConnectedTests"
  # changed in : "areConnectedTests"
  string(REPLACE ".cpp" "" example_name ${example_source_file})
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" example_name
                 ${example_name})

  # on créé l'executable
  add_executable(${example_name} ${example_source_file})

  # on link les librairies
  target_link_libraries(${example_name} GLhf)
  target_include_directories(${example_name} PUBLIC ${CMAKE_SOURCE_DIR}/external)
  target_compile_options(${example_name} PUBLIC -std=c++17 -Ofast)

endforeach(example_source_file ${SRCS})
