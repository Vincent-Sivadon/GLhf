# ===== Examples of GLtemplate library ===== #

file(GLOB EXAMPLE_SRCS "src/*.cpp")

# For every EXAMPLE
foreach(example_source_file ${EXAMPLE_SRCS})
  # file ( GLOB ... ) gives absolute paths, we then transform it in relative
  # paths for example :
  # "/home/vincents/Documents/Projet/Enumeration-of-Maximal-Induced-Bicliques/examples/src/areConnectedTests"
  # changed in : "areConnectedTests"
  string(REPLACE ".cpp" "" example_name ${example_source_file})
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/src/ "" example_name
                 ${example_name})

  # on créé l'executable
  add_executable(${example_name} ${example_source_file})

  # on link les librairies
  target_link_libraries(${example_name} glad glfw GLtemplate)
  target_include_directories(${example_name} PUBLIC ${CMAKE_SOURCE_DIR}/external)
  target_compile_options(${example_name} PUBLIC -std=c++17 -g)

endforeach(example_source_file ${EXAMPLE_SRCS})
