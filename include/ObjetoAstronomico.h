#ifndef OBJETO_ASTRONOMICO_H
#define OBJETO_ASTRONOMICO_H

#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

// Tipos de objetos celestes
enum class TipoObjeto {
    ESTRELLA,
    PLANETA,
    GALAXIA,
    NEBULOSA,
    CUMULO,
    SATELITE,
    COMETA
};

// Tipos espectrales de estrellas (de más caliente a más fría)
enum class TipoEspectral {
    O, // Azul - muy caliente
    B, // Azul - blanco
    A, // Blanco
    F, // Blanco - amarillo
    G, // Amarillo (como el sol)
    K, // Naranja
    M  // Rojo - más fría
};

class ObjetoAstronomico {
private:
    string nombre;
    TipoObjeto tipo;
    sf::Vector2f coordenadas;
    float magnitud;     // brillo
    TipoEspectral tipoEspectral; // para estrellas
    sf::Color color;
    float distancia;    // distancia en años luz
    string descripcion;

public:
    // Constructor por defecto
    ObjetoAstronomico();

    // Constructor completo
    ObjetoAstronomico(string nom, TipoObjeto tip,
                      sf::Vector2f coord, float mag,
                      TipoEspectral espectral, float dist,
                      string desc = "");

    // Getters
    string getNombre() const;
    TipoObjeto getTipo() const;
    sf::Vector2f getCoordenadas() const;
    float getMagnitud() const;
    TipoEspectral getTipoEspectral() const;
    sf::Color getColor() const;
    float getDistancia() const;
    string getDescripcion() const;
    float getRadioVisual() const; // radio basado en la magnitud

    // Setters
    void setNombre(string nom);
    void setCoordenadas(sf::Vector2f coord);
    void setMagnitud(float mag);
    void setDescripcion(string desc);

    // Utilidades
    string getTipoString() const;
    string getTipoEspectralString() const;

    // Operador para debugging
    friend ostream& operator<<(ostream& os, const ObjetoAstronomico& obj);
};

// Función auxiliar para obtener color según tipo espectral
sf::Color getColorPorTipoEspectral(TipoEspectral tipo);

#endif