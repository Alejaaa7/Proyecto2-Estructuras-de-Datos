#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "ObjetoAstronomico.h"

using namespace std;

// Estructura de Datos: ÁRBOL DE SEGMETNOS ESPACIAL (QuadTree)

// Representa un rectángulo en el espacio (región)

struct Rectangulo {
    float x, y; // Centro del rectágunlo
    float ancho, alto; // Dimensiones

    // Constructor
    Rectangulo(float cx, float cy, float w, float h)
        : x(cx), y(cy), ancho(w), alto(h) {}

    // Verificar si un punto está dentro del rectángulo
    bool contiene(sf::Vector2f punto) const {
        return (punto.x >= x - ancho/2 && punto.x <= x + ancho/2 &&
                punto.y >= y - alto/2 && punto.y <= y + alto/2);
    }

    // Verificar si este rectángulo intersecta con otro
    bool intersecta(const Rectangulo& otro) const {
        return !(otro.x - otro.ancho/2 > x + ancho/2 ||
                 otro.x + otro.ancho/2 < x - ancho/2 ||
                 otro.y - otro.alto/2 > y + alto/2 ||
                 otro.y + otro.alto/2 < y - alto/2);
    }
};

// Nodo del QuadTree
class QuadTree {
private:
    Rectangulo limites; // región que cubre este nodo
    int capacidad; // máximo de objetos antes de subdividir
    vector<ObjetoAstronomico*> objetos; // objetos en este nodo
    bool subdividido;

    // Los 4 hijos (cuadrantes)
    QuadTree* noroeste; // NW (arriba-izquierda)
    QuadTree* noreste; // NE (arrida-derecha)
    QuadTree* suroeste; // SW (abajo-izquierda)
    QuadTree* sureste; // SE (abajo-derecha)

    // Subdividir este nodo en 4 cuadrantes
    void subdividir();

public:
    // Constructor
    QuadTree(Rectangulo limites, int cap = 4);

    // Destructor
    ~QuadTree();

    // Insertar un objeto en el árbol - O(log n)
    bool insertar(ObjetoAstronomico* objeto);

    // Buscar objetos en una región específica - O(log n)
    vector<ObjetoAstronomico*> buscar(const Rectangulo& region) const;

    // Obtener todos los objetos del arbol - O(n)
    vector<ObjetoAstronomico*> obtenerTodos() const;

    // Limpiar el árbol
    void limpiar();

    // Contar objetos totales
    int contarObjetos() const;

    // Debug: mostrar estadísticas
    void mostrarEstadisticas(int nivel = 0) const;
};

#endif