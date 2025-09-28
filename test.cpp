#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>

struct Point {
    int x, y;
};

struct Edge {
    int y_max;
    float x;
    float inv_slope;
};

std::vector<Point> points;
int width = 500, height = 500;
bool polygonClosed = false;

// Controle de tempo
auto lastClick = std::chrono::steady_clock::now();

// ------------------------------------------------------
// Desenha um pixel em coordenadas de tela
void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// ------------------------------------------------------
// Função de preenchimento com Active Edge Table
void fillPolygonAET(const std::vector<Point>& points) {
    if (points.size() < 3) return;

    int y_min = points[0].y, y_max = points[0].y;
    for (auto& p : points) {
        if (p.y < y_min) y_min = p.y;
        if (p.y > y_max) y_max = p.y;
    }

    std::vector<std::vector<Edge>> edge_table(y_max + 1);

    // Construir tabela de arestas
    for (size_t i = 0; i < points.size(); i++) {
        Point p1 = points[i];
        Point p2 = points[(i + 1) % points.size()];

        if (p1.y == p2.y) continue;

        if (p1.y > p2.y) std::swap(p1, p2);

        Edge e;
        e.y_max = p2.y;
        e.x = p1.x;
        e.inv_slope = (float)(p2.x - p1.x) / (float)(p2.y - p1.y);

        edge_table[p1.y].push_back(e);
    }

    std::vector<Edge> AET;

    // Varredura
    for (int y = y_min; y <= y_max; y++) {
        // Adiciona arestas que começam nesta linha
        for (auto& e : edge_table[y]) AET.push_back(e);

        // Remove arestas que terminaram
        AET.erase(std::remove_if(AET.begin(), AET.end(),
                                 [y](Edge& e){ return y >= e.y_max; }),
                  AET.end());

        // Ordena por x
        std::sort(AET.begin(), AET.end(),
                  [](Edge& a, Edge& b){ return a.x < b.x; });

        // Preenche entre pares
        for (size_t i = 0; i+1 < AET.size(); i+=2) {
            for (int x = (int)AET[i].x; x < (int)AET[i+1].x; x++) {
                drawPixel(x, y);
            }
        }

        // Atualiza X
        for (auto& e : AET) e.x += e.inv_slope;
    }
}

// ------------------------------------------------------
// Display
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenha contorno
    glColor3f(1, 1, 1);
    if (!points.empty()) {
        glBegin(GL_LINE_STRIP);
        for (auto& p : points)
            glVertex2i(p.x, p.y);
        glEnd();
    }

    // Se polígono foi fechado → preencher
    if (polygonClosed) {
        glColor3f(1, 0, 0);
        fillPolygonAET(points);
    }

    glFlush();
}

// ------------------------------------------------------
// Captura cliques do mouse
void mouse(int button, int state, int x, int y) {
    if (polygonClosed) return; // não aceita mais pontos

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int y_gl = height - y; // inverter eixo Y
        points.push_back({x, y_gl});

        // Atualiza tempo do último clique
        lastClick = std::chrono::steady_clock::now();

        glutPostRedisplay();
    }
}

// ------------------------------------------------------
// Checa timeout de 5 segundos
void checkTimeout() {
    if (polygonClosed) return;

    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - lastClick);

    if (elapsed.count() >= 5 && points.size() >= 3) {
        polygonClosed = true;
        glutPostRedisplay();
    }
}

// ------------------------------------------------------
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutCreateWindow("Preenchimento com AET e Timeout");

    gluOrtho2D(0, width, 0, height);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutIdleFunc(checkTimeout); // verifica timeout continuamente

    glutMainLoop();
    return 0;
}

