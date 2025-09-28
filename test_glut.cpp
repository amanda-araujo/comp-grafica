#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;

struct Point {
    float x, y;
};

vector<Point> points;
//points = {{-0.5, -0.5}, {0.5, -0.5}, {0.0, 0.5}};

void drawPolygon(vector<Point> points) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < points.size(); i++) {
        float x = points[i].x;
        float y = points[i].y;
        glVertex2f(x, y);
    }
    glEnd();
}

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
        std::cout << "Left button pressed: (" << x << ", " << y << ")" << std::endl;
        std::cout << "Right button pressed (" << x_gl << ", " << y_gl << ")"  << std::endl;
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        // Clique botão direito: remove o ponto
        if (points.size() >= 1) {
            points.pop_back();
        } else {
            std::cout << "Nothing to delete!" << std::endl;
        }

        std::cout << "Right button pressed (" << x << ", " << y << ")"  << std::endl;
        std::cout << "Right button pressed (" << x_gl << ", " << y_gl << ")"  << std::endl;
    }

    glutPostRedisplay(); //Atualização da tela

}


// Tela (janela)
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Limpar o buffer de cor

    /* Figura: triângulo */
    // glBegin(GL_TRIANGLES);
    // glColor3f(1.0, 0.0, 0.0); glVertex2f(-0.5, -0.5); // Color, Vertex
    // glColor3f(0.0, 1.0, 0.0); glVertex2f( 0.5, -0.5);
    // glColor3f(0.0, 0.0, 1.0); glVertex2f( 0.0,  0.5);
    // glEnd();

    drawPolygon(points);

    glFlush(); // Atualiza a tela
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Inicializando o GLUT
    glutCreateWindow("FreeGLUT test"); // Cria tela principal: 'nome'

    // Propriedades da janela
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Alterações na matriz de projeção da janela
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glutDisplayFunc(display); // Def. função de callback de exibição
    glutMouseFunc(mouse); // Callback mouse
    glutMainLoop(); // Iniciando o loop principal do GLUT

    return 0;
}
