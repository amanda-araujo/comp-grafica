cmake_minimum_required(VERSION 3.31)
project(comp_grafica)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(comp_grafica main.cpp
        testopengl.cpp
        test_glut.cpp
        new.cpp)
target_link_libraries(comp_grafica ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

add_executable(new new.cpp)
target_link_libraries(new ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

add_executable(test_glut test_glut.cpp)
target_link_libraries(test_glut ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

# Para rodar no terminal:
# g++ test_glut.cpp -lglut -lGLU -lGL -o test_glut
# >> Necessário passar explicitamente as bibliotecas utilizadas