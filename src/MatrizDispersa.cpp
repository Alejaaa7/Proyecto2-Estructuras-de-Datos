#include "MatrizDispersa.h"
#include <iostream>
#include <cmath>

using namespace std;

// Constructor

MatrizDispersa::MatrizDispersa(int f, int c, float tamCelda)
    : filas(f), columnas(c), tamañoCelda(tamCelda)
{
    // las filas y columnas son el tamaño VIRTUAL de la matriz
    // el tamañoCelda es el tamaño de cada celda en el mundo
    // la matriz empieza vacía
}

Coordenada MatrizDispersa::mundoACelda(sf::Vector2f posicion) const {
    // convierte una posición del mundo a índices de celda

    // Calcular índices dividiendo por tamaño de celda
    int fila = static_cast<int>(floor(posicion.y / tamañoCelda));
    int col = static_cast<int>(floor(posicion.x / tamañoCelda));

    // Ajustar para coordenadas negativas (centrar en el origen)
    fila += filas / 2;
    col += columnas / 2;

    // Asegurar que esté dentro de los límits
    if (fila < 0) fila = 0;
    if (fila >= filas) fila = filas - 1;
    if (col < 0) col = 0;
    if (col >= columnas) col = columnas - 1;

    return {fila, col};
}

// Limpiar
void MatrizDispersa::limpiar() {
    // elimina todas las celdas de la matriz
    // la matriz vuelve a estar completamente vacía

    matriz.clear();
}

// Insertar
void MatrizDispersa::insertar(ObjetoAstronomico* objeto) {
    
    // Calcular en qué celda cae este objeto
    Coordenada celda = mundoACelda(objeto->getCoordenadas());

    // Si la celda NO existe, map la crea automaticamente
    // si ya existe, la obtiene
    // NO se crean celdas vacías innecesarias

    // Agregar el objeto a la celda
    matriz[celda].objetos.push_back(objeto);
    matriz[celda].ocupada = true;

    // si solo 50 de 10000 celdas tienen objetos, solo esas 50 existen en la memoria
}

// Obtener celda
vector<ObjetoAstronomico*>  MatrizDispersa::obtenerCelda(int fila, int col) const {

    // retorna los objetos en una celda específica

    Coordenada coord = {fila, col};

    // buscar si la celda existe
    auto it = matriz.find(coord);

    if (it != matriz.end()) {
        // La celda existe, retornar sus objetos
        return it->second.objetos;
    }

    // La celda NO existe (está vacía)
    return vector<ObjetoAstronomico*>(); // vector vacío
}

// Está ocupada
bool MatrizDispersa::estaOcupada(int fila, int col) const {

    // Verifica si una celda tiene objetos

    Coordenada cord = {fila, col};
    auto it = matriz.find(cord);

    // Si la celda no existe en el map, está vacía
    return (it != matriz.end() && it->second.ocupada);
}

// Obtener las celdas ocupadas
vector<Coordenada> MatrizDispersa::obtenerCeldasOcupadas() const {

    // Retorna lista de todas las celdas que tienen objetos

    vector<Coordenada> ocupadas;

    for(const auto& par : matriz) {
        if (par.second.ocupada) {
            ocupadas.push_back(par.first);
        }
    }

    return ocupadas;
}

// Estadísticas

int MatrizDispersa::getCeldasTotales() const {
    // Tamaño virtual de la matriz
    return filas * columnas;
}

int MatrizDispersa::getCeldasOcupadas() const {
    // Cuántas celdas REALMENTE existen en memoria
    return matriz.size();
}

float MatrizDispersa::getEficiencia() const {
    // Calcula cuánta memoria ahorramos :D
    
    int totales = getCeldasTotales();
    int ocupadas = getCeldasOcupadas();

    if (totales == 0) return 0.0f;

    // Porcentaje de memoria ahorrada
    return 100.0f * (1.0f - (float)ocupadas / (float)totales);
}

// Mostrar Estadísticas
void MatrizDispersa::mostrarEstadisticas() const {
    cout << "MATRIZ DISPERSA - ESTADÍSTICAS" << endl;
    cout << "Dimensiones virtuales: " << filas << " x " << columnas
         << " 0 " << getCeldasTotales() << " celdas" << endl;
    cout << "Celdas ocupadas: " << getCeldasOcupadas() << endl;
    cout << "Celdas vacías: " << (getCeldasTotales() - getCeldasOcupadas()) << endl;
    cout << "Eficiencia (ahorro de memoria): " << getEficiencia() << "%" << endl;
    cout << "Tamaño de celda: " << tamañoCelda << " unidades" << endl;
}