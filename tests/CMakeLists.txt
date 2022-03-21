# ===== TEST DE LA LIBRAIRIE GLtemplate =====

file(GLOB TEST_SRCS "src/*.cpp")

# pour chaque TEST
foreach(testsourcefile ${TEST_SRCS})
  # file ( GLOB ... ) donne les path absolu, on le transform en relative path
  # exemple :
  # "/home/vincents/Documents/Projet/Enumeration-of-Maximal-Induced-Bicliques/tests/src/areConnectedTests"
  # transformé en : "areConnectedTests"
  string(REPLACE ".cpp" "" testname ${testsourcefile})
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/src/ "" testname ${testname})

  # on créé l'executable
  add_executable(${testname} ${testsourcefile})

  # on link les librairies
  target_link_libraries(${testname} glad glfw GLtemplate)
  target_compile_options(${testname} PUBLIC -std=c++17)

  # on ajoute cet executable à la liste des tests
  add_test(${testname} ${testname})

endforeach(testsourcefile ${TEST_SRCS})
