#ifndef CONSTELACION_H
#define CONSTELACION_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

// Representa una constelación con sus estrellas conectadas
class Constelacion {
private:
    string nombre;
    sf::Color color;  // Color pastel único para cada constelación
    vector<string> nombresEstrellas;  // Nombres de las estrellas que la forman
    vector<pair<int, int>> conexiones;  // Pares de índices: qué estrellas conectar

public:
    Constelacion(string nom, sf::Color col);
    
    // Agregar estrella a la constelación
    void agregarEstrella(const string& nombreEstrella);
    
    // Conectar dos estrellas (por sus índices en el vector)
    void conectar(int indice1, int indice2);
    
    // Getters
    string getNombre() const;
    sf::Color getColor() const;
    vector<string> getEstrellas() const;
    vector<pair<int, int>> getConexiones() const;
};

// Manager de constelaciones
class GestorConstelaciones {
private:
    vector<Constelacion> constelaciones;

public:
    GestorConstelaciones();
    
    // Cargar constelaciones predefinidas
    void cargarConstelaciones();
    
    // Obtener todas las constelaciones
    vector<Constelacion> getConstelaciones() const;
    
    // Verificar si una estrella pertenece a alguna constelación
    bool perteneceAConstelacion(const string& nombreEstrella, string& nombreConstelacion) const;
};

#endif