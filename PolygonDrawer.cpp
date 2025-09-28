//
// Created by Amanda on 28/09/2025.
//

#include "PolygonDrawer.h"
#include <GL/glut.h>

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

// Preenchimento do polígono
void fillPolygonET(std::vector<Point> points) {}
void fillPolygonAET(std::vector<Point> points) {}

