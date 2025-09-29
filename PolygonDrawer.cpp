#include <cmath>
#include <iostream>
#include <ostream>
#include <GL/glut.h>
#include "PolygonDrawer.h"

// Desenha arestas do polígono
void drawPolygon(std::vector<Point> points) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < points.size(); i++) {
        float x = points[i].x;
        float y = points[i].y;
        glVertex2f(x, y);
    }
    glEnd();
}

// Função principal de preenchimento Scanline-AET
void fillPolygonAET(const std::vector<Point> &points) {
    if (points.size() < 3) {
        std::cout << "Não há pontos suficientes!" << std::endl;
        return;
    }

    // Descobre ymin e yman
    float ymin = points[0].y;
    float ymax = points[0].y;
    for (auto &p : points) {
        if (p.y < ymin) ymin = p.y;
        if (p.y > ymax) ymax = p.y;
    }

    std::vector<Edge> AET;

    float yStep = 0.002f; // resolução scanline

    // Começa varredura das linhas
    for (float y = ymin; y <= ymax; y += yStep) {
        AET.clear();

        // Para cada aresta, verifica se cruza linha y
        for (size_t i = 0; i < points.size(); ++i) {
            Point p1 = points[i];
            Point p2 = points[(i+1) % points.size()];

            if (p1.y == p2.y) continue; // Ignora horizontais

            float ymin_e = std::min(p1.y, p2.y);
            float ymax_e = std::max(p1.y, p2.y);

            if (y >= ymin_e && y < ymax_e) {
                // Calcula intersecção x
                float x = p1.x + (y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
                AET.push_back({ymax_e, x}); // invSlope não mais necessário
            }
        }

        // Ordena intersecções (AET por x)
        std::sort(AET.begin(), AET.end(), [](Edge a, Edge b){ return a.x < b.x; });

        // Desenha linhas entre pares de interseções
        glBegin(GL_LINES);
        for (size_t j = 0; j + 1 < AET.size(); j += 2) {
            glVertex2f(AET[j].x, y);
            glVertex2f(AET[j+1].x, y);
        }
        glEnd();
    }

    glutSwapBuffers();
}