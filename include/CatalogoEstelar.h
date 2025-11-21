#ifndef CATALOGO_ESTELAR_H
#define CATALOGO_ESTELAR_H

#include <unordered_map>
#include <vector>
#include <string>
#include "ObjetoAstronomico.h"

using namespace std;

class CatalogoEstelar {
private:
    // Estructura de datos: Diccionario (es unordered_map)
    unordered_map<string, ObjetoAstronomico> objetos;

public:
    // Constructor
    CatalogoEstelar();

    // Operaciones del diccionario
    void agregar(const ObjetoAstronomico& objeto);
    bool buscar(const string& nombre) const; 
    ObjetoAstronomico obtener(const string& nombre) const;
    bool eliminat(const string& nombre);
    int getCantidad() const;

    // Obtener todos  los objetos (para renderizado)
    vector<ObjetoAstronomico> obtenerTodos() const;

    // Cargar catálogo inicial con estrellas reales
    void cargarCatalogoInicial();

    //Utilidades
    void mostrarEstadisticas() const;
    vector<string> listarNombres() const;
};

#endif