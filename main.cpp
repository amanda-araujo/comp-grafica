// Initializes OpenGL and runs the menu
#include <GL/glut.h>
#include <thread>
#include <atomic>
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include "Menu.h"
#include "PolygonDrawer.h"
#include "OpenGLWindow.h"

// Variáveis globais compartilhadas
std::atomic<bool> onScreen(false);
std::atomic<int> fillColor(1); // 1 = branco
std::atomic<int> lineWidth(1);
std::atomic<bool> clearScreen(false);
std::atomic<bool> fillPolygon(false);
std::atomic<bool> exitSystem(false);
std::atomic<bool> destroyerPolygon(false); // (adios)


std::vector<Point> points;

void mouse(int button, int state, int x, int y) {

    // Transformação coordenadas: janela >> grid
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    //std::cout << "Window size: (" << width << ", " << height << ")" << std::endl;

    // Converte para coordenadas OpenGL
    float x_gl = -1.0f + 2.0f * x / width;
    float y_gl =  1.0f - 2.0f * y / height;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Clique botão esquerdo: adiciona o ponto
        points.push_back({x_gl, y_gl});
        //std::cout << "Left button pressed: (" << x << ", " << y << ")" << std::endl;
        //std::cout << "Right button pressed (" << x_gl << ", " << y_gl << ")"  << std::endl;
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        // Clique botão direito: remove o ponto
        if (points.size() >= 1) {
            points.pop_back();
        } else {
            std::cout << "Nothing to delete!" << std::endl;
        }
        //std::cout << "Right button pressed (" << x << ", " << y << ")"  << std::endl;
        //std::cout << "Right button pressed (" << x_gl << ", " << y_gl << ")"  << std::endl;
    }

    glutPostRedisplay(); //Atualização da tela

}

void display() {
    if (clearScreen) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); // Limpar o buffer de cor

        if (destroyerPolygon) { // Adios Polygon bye bye
            points.clear();
            destroyerPolygon = false;
        }
        clearScreen = false;
    }

    // Define cor com base na especificação do usuário
    switch (fillColor.load()) {
        case 2: glColor3f(1.0f, 0.0f, 0.0f); break; // Vermelho
        case 3: glColor3f(0.0f, 0.0f, 1.0f); break; // Azul
        case 4: glColor3f(0.0f, 1.0f, 0.0f); break; // Verde
        default: glColor3f(1.0f, 1.0f, 1.0f); break; // Branco
    }

    // Espessura com base na especificação do usuário
    glLineWidth(lineWidth.load());

    // Desenho das arestas do polígono (triângulos)
    drawPolygon(points);

    // Preenchimento do polígono
    if (fillPolygon.load() && points.size() >= 3) {
        fillPolygonAET(points);
    }

    glutSwapBuffers(); // Atualiza a tela //glFlush();
}

void timer(int) {
    glutTimerFunc(100, timer, 0); // Callback timer
    glutPostRedisplay();
}

void idle_func() {
    if (exitSystem) {
        std::cout << "Encerrando sistema...\n";
        exit(0); // GLUT puro: encerra janela e threads
    }
    glutPostRedisplay();
}

void startOpenGLWindow(int argc, char** argv) {
    // OpenGL
    glutInit(&argc, argv); // Inicializando o GLUT
    glutCreateWindow("POLYGON System"); // Cria tela principal

    // Propriedades da janela
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Alterações na matriz de projeção da janela
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    // Callbacks
    glutDisplayFunc(display); // Callback de exibição
    glutMouseFunc(mouse); // Callback mouse
    glutIdleFunc(idle_func); // Verificação de estado
    glutTimerFunc(100, timer, 0);

    glutMainLoop(); // Loop principal do GLUT: thread principal
}

int main(int argc, char** argv){
    // Thread menu
    std::thread menuThread([]() {
        Menu menu;
        menu.init();
    });

    // OpenGl: GLUT
    while (!onScreen && !exitSystem) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    if (onScreen && !exitSystem) { // Start OpenGL
        int argc = 1;
        char* argv[1] = { (char*)"POLYGON System" };
        startOpenGLWindow(argc, argv);
        glutMainLoop(); // Loop principal do GLUT: thread principal
    }

    if (menuThread.joinable()) {
        menuThread.join();
    }

    return 0;
}