//
// Created by Amanda on 28/09/2025.
//

#ifndef POLYGONDRAWER_H
#define POLYGONDRAWER_H

#include <vector>

//class PolygonDrawer {};

// Estrutura para pontos 2D
struct Point {
    float x, y;
};

// Estrutura para uma aresta
struct Edge {
    float ymax;
    float x;
    float invSlope;
};

// Funções para desenhar polígono
void drawPolygon(std::vector<Point> points);
void fillPolygonAET(const std::vector<Point> &points);


#endif //POLYGONDRAWER_H
