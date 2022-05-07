cmake_minimum_required(VERSION 3.0)

# Notre projet est étiqueté mylib
project(GLhf)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Import library
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)

# Generate examples binaries
if(DEFINED EXAMPLES)
  add_subdirectory(examples)
endif(DEFINED EXAMPLES)

# Libraries
set(LIBS glfw glad)
set(glm_dir /usr/include/glm) # header only librairy

# Liste des fichiers sources
file(GLOB SRCS "src/*.cpp" "primitives/*.cpp")
# Liste des définitions
file(GLOB HEADERS "include/*.h" "primitives/*.h")
# Liste des shaders primitives
file(GLOB SHADERS "resources/shaders/examples/*" "resources/shaders/primitives/*")

set(BUILD_INCL ${CMAKE_SOURCE_DIR}/include;${glm_dir};${CMAKE_SOURCE_DIR}/primitives;${CMAKE_SOURCE_DIR}/external)

add_library(GLhf SHARED ${SRCS} ${HEADERS})
target_link_libraries(GLhf ${LIBS})
target_compile_options(GLhf PUBLIC -g)
target_include_directories(
  GLhf
  PUBLIC "$<BUILD_INTERFACE:${BUILD_INCL}>" # for
         # headers when building
         $<INSTALL_INTERFACE:/usr/local/include/GLhf> # for client in
                                                            # install mode
         $<INSTALL_INTERFACE:/usr/local/lib>) # for config_impl.hpp in install
                                              # mode)

install(
  TARGETS GLhf
  EXPORT GLhfConfig
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin/GLhf)
export(TARGETS GLhf FILE "${CMAKE_SOURCE_DIR}/GLhfConfig.cmake")
install(EXPORT GLhfConfig DESTINATION "lib/cmake/GLhf")
install(FILES ${HEADERS} DESTINATION /usr/local/include/GLhf)
install(FILES ${SHADERS} DESTINATION /usr/local/share/GLhf/)

string(ASCII 27 ESCAPE)
message("${ESCAPE}[1;36m")
message("======================= INSTALLATION =======================")
message(
  "
  To build the library
    * mkdir build
    * cd build
    * cmake ..
    * make
  ")
message("========================== USAGE ===========================")
message(
  "
  Include <GLhf/GLhf.h> in your script,
  and use the following structure to build your application :
  ")
message("${ESCAPE}[1;35m")
message(
  "
    ----------- Application -----------
    class ExampleApp : public App
    {
    public:
        void startup() override {}        // Initialize OpenGL objects
        void render() override {}         // Rendering protocole
        void processInput() override {}   // Input Management
        void shutdown() override {}       // Memory cleaning
    private:
        int member;
    }
    -----------------------------------
    /* function implementations */
    -----------------------------------
    DECLARE_MAIN(ExampleApp);
    -----------------------------------
")
message("${ESCAPE}[1;36m")
message("
  Now to compile use can use CMake with find_package(GLhf REQUIRED)
  ")
message("===========================================================")

message("${ESCAPE}[0m")
