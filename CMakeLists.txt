cmake_minimum_required(VERSION 3.0)

# Notre projet est étiqueté mylib
project(GLtemplate)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Import library
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)

# Génère les tests  : la commande "ctest" permet de lancer tout les tests
enable_testing()
add_subdirectory(tests)

# Libraries
set(LIBS glfw glad ${FREETYPE_LIBRARIES})
set(glm_dir /usr/include/glm) # header only librairy

# Liste des fichiers sources
file(GLOB SRCS "src/*.cpp" "primitives/*.cpp")
# Liste des définitions
file(GLOB HEADERS "include/*.h" "primitives/*.h")
# Liste des shaders primitives
file(GLOB SHADERS "primitives/shaders/*")

add_library(GLtemplate SHARED ${SRCS} ${HEADERS})
target_link_libraries(GLtemplate ${LIBS})
target_include_directories(
  GLtemplate
  PUBLIC "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include;${glm_dir}>" # for
         # headers when building
         $<INSTALL_INTERFACE:/usr/local/include/GLtemplate> # for client in
                                                            # install mode
         $<INSTALL_INTERFACE:/usr/local/lib>) # for config_impl.hpp in install
                                              # mode)

install(
  TARGETS GLtemplate
  EXPORT GLtemplateConfig
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin/GLtemplate)
export(TARGETS GLtemplate FILE "${CMAKE_SOURCE_DIR}/GLtemplateConfig.cmake")
install(EXPORT GLtemplateConfig DESTINATION "lib/cmake/GLtemplate")
install(FILES ${HEADERS} DESTINATION /usr/local/include/GLtemplate)
install(FILES ${SHADERS} DESTINATION /usr/local/share/GLtemplate/)

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
  Include <GLtemplate/GLtemplate.h> in your script,
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
  Now to compile use can use CMake with find_package(GLtemplate REQUIRED)
  ")
message("===========================================================")

message("${ESCAPE}[0m")
