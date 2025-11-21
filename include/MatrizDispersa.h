#ifndef MATRIZ_DISPERSA_H
#define MATRIZ_DISPERSA_H

#include <map>
#include <vector>
#include <utility>
#include "ObjetoAstronomico.h"

using namespace std;

// Estructura de datos: MATRIZ DISPERSA

// Par de coordenadas (fila, columna) para indexar la matriz
using Coordenada = pair<int, int>;

// Celda de la matriz que contiene referencias a objetos
struct Celda {
    vector<ObjetoAstronomico*> objetos; // objetos en esta celda
    bool ocupada;

    Celda() : ocupada(false) {}
};

class MatrizDispersa{
private:
    // Solo almacena las celdas que tienen contenido
    // Clave: par (fila, columna)
    // Valor: celda con objetos
    map<Coordenada, Celda> matriz;

    int filas; // número de filas totales
    int columnas; // número de columnas totales
    float tamañoCelda; // tamaño de cada celda en unidades del mundo

    // Convertir coordenada del mundo a índice de celda
    Coordenada mundoACelda(sf::Vector2f posicion) const;

public:
    // Constructor
    // las filas y columnas definen el tamaño virtual de la matriz
    // tamCelda define el tamaño real de cada celda en el mundo
    MatrizDispersa(int filas, int columnas, float tamCelda);
    
    // Limpiar toda la matriz
    void limpiar();

    // Insertar objeto en la celda correspondiente
    void insertar(ObjetoAstronomico* objeto);

    // Obtener objetos  en una celda específica
    vector<ObjetoAstronomico*> obtenerCelda(int fila, int col) const;

    // Verificar si una celda está ocupada
    bool estaOcupada(int fila, int col) const;

    // Obtener todas las celdas ocupadas
    vector<Coordenada> obtenerCeldasOcupadas() const;

    // Estadísticas
    int getCeldasTotales() const; // tamaño virtual (filas x columnas)
    int getCeldasOcupadas() const; // cuántas realmente EXISTEN en la memoria
    float getEficiencia() const; // % de memoria ahorrada

    // Debug
    void mostrarEstadisticas() const;
};

#endif