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
    int y_max;
    float x;
    float slope_inv;
};



// Funções para desenhar polígono
void drawPolygon(std::vector<Point> points);
bool compareEdges(const Edge &a, const Edge &b);
void drawPixel(int x, int y);
void fillPolygonET(std::vector<Point> points);
void fillPolygonAET(std::vector<Point> points);


#endif //POLYGONDRAWER_H
