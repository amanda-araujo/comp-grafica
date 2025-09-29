cmake_minimum_required(VERSION 3.31)
project(comp_grafica)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(comp_grafica
        Menu.cpp
        Menu.h
        main.cpp
        PolygonDrawer.cpp
        PolygonDrawer.h
        OpenGLWindow.h
)
target_link_libraries(comp_grafica ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

add_executable(menu Menu.cpp Menu.h OpenGLWindow.h)

add_executable(PolygonDrawer PolygonDrawer.cpp )
target_link_libraries(PolygonDrawer ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

add_executable(main main.cpp Menu.cpp PolygonDrawer.cpp OpenGLWindow.h)
target_link_libraries(main ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} pthread)

# Para rodar no terminal:
# g++ test_glut.cpp -lglut -lGLU -lGL -o test_glut
# >> Necessário passar explicitamente as bibliotecas utilizadasadd_executable(test test.cpp)