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

// Funções para desenhar polígono
void drawPolygon(std::vector<Point> points);
void fillPolygonET(std::vector<Point> points);
void fillPolygonAET(std::vector<Point> points);


#endif //POLYGONDRAWER_H
