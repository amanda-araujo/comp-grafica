//
// Created by Amanda on 28/09/2025.
//

#include <cmath>
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

// Comparador para ordenar arestas pelo x
bool compareEdges(const Edge &a, const Edge &b) {
    return a.x < b.x;
}

// Funcao para desenhar um pixel
void drawPixel(float x, float y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}


// Preenchimento do polígono
void fillPolygonET(std::vector<Point> points) {}

void fillPolygonAET(std::vector<Point> points) {

    // Funcao para preencher o poligono
    if (points.size() < 3) return;

    // 1. Encontrar y_min e y_max do poligono
    int y_min = points[0].y;
    int y_max = points[0].y;
    for (auto& p : points) {
        if (p.y < y_min) y_min = p.y;
        if (p.y > y_max) y_max = p.y;
    }

    // 2. Construir a Edge Table (ET)
    std::vector<std::vector<Edge>> edge_table(y_max + 1);
    for (size_t i = 0; i < points.size(); ++i) {
        Point p1 = points[i];
        Point p2 = points[(i + 1) % points.size()];

        if (p1.y == p2.y) continue; // Ignora arestas horizontais

        Edge edge;
        if (p1.y < p2.y) {
            edge.y_max = p2.y;
            edge.x = p1.x;
            edge.slope_inv = (float)(p2.x - p1.x) / (p2.y - p1.y);
            edge_table[p1.y].push_back(edge);
        } else {
            edge.y_max = p1.y;
            edge.x = p2.x;
            edge.slope_inv = (float)(p1.x - p2.x) / (p1.y - p2.y);
            edge_table[p2.y].push_back(edge);
        }
    }

    // 3. Inicializar a Active Edge Table (AET) e preencher
    std::vector<Edge> aet;
    for (int y = y_min; y <= y_max; ++y) {
        // Mover novas arestas da ET para a AET
        for (const auto& new_edge : edge_table[y]) {
            aet.push_back(new_edge);
        }
        std::sort(aet.begin(), aet.end(), compareEdges);

        // Remover arestas inativas
        aet.erase(std::remove_if(aet.begin(), aet.end(), [y](const Edge& e) {
            return e.y_max == y;
        }), aet.end());

        // Preencher a linha de varredura
        for (size_t i = 0; i < aet.size(); i += 2) {
            for (int x = static_cast<int>(aet[i].x); x < static_cast<int>(aet[i + 1].x); ++x) {
                drawPixel(x, y);
            }
        }

        // Atualizar x para a próxima linha de varredura
        for (auto& edge : aet) {
            edge.x += edge.slope_inv;
        }
    }
}

