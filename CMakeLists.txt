cmake_minimum_required(VERSION 3.31)
project(comp_grafica)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(comp_grafica
        testopengl.cpp
        test_glut.cpp
        Menu.cpp
        Menu.h
        main.cpp
        PolygonDrawer.cpp
        PolygonDrawer.h
        OpenGLWindow.h
        test.cpp
)
target_link_libraries(comp_grafica ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

add_executable(test_glut test_glut.cpp)
target_link_libraries(test_glut ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

add_executable(menu Menu.cpp Menu.h
        OpenGLWindow.h)

add_executable(PolygonDrawer PolygonDrawer.cpp PolygonDrawer.h)
target_link_libraries(PolygonDrawer ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

add_executable(main main.cpp Menu.cpp PolygonDrawer.cpp
        OpenGLWindow.h)
target_link_libraries(main ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} pthread)

# Para rodar no terminal:
# g++ test_glut.cpp -lglut -lGLU -lGL -o test_glut
# >> Necessário passar explicitamente as bibliotecas utilizadasadd_executable(test test.cpp)


add_executable(test test.cpp)
target_link_libraries(test ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} pthread)