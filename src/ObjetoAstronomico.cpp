#include "ObjetoAstronomico.h"
#include <cmath>

// Constructor por defecto
ObjetoAstronomico::ObjetoAstronomico()
    : nombre("Desconocido"),
      tipo(TipoObjeto::ESTRELLA),
      coordenadas(0, 0),
      magnitud(0),
      tipoEspectral(TipoEspectral::G),
      distancia(0),
      descripcion("")
{
    color = getColorPorTipoEspectral(tipoEspectral);
}

// Constructor completo
ObjetoAstronomico::ObjetoAstronomico(string nom, TipoObjeto tip,
                                    sf::Vector2f coord, float mag,
                                    TipoEspectral espectral, float dist,
                                    string desc)
    : nombre(nom), tipo(tip), coordenadas(coord), magnitud(mag),
      tipoEspectral(espectral), distancia(dist), descripcion(desc)
{
    color = getColorPorTipoEspectral(tipoEspectral);
}

// Getters
string ObjetoAstronomico::getNombre() const { return nombre;}
TipoObjeto ObjetoAstronomico::getTipo() const { return tipo;}
sf::Vector2f ObjetoAstronomico::getCoordenadas() const {return coordenadas;}
float ObjetoAstronomico::getMagnitud() const { return magnitud;}
TipoEspectral ObjetoAstronomico::getTipoEspectral() const { return tipoEspectral;}
sf::Color ObjetoAstronomico::getColor() const { return color; }
float ObjetoAstronomico::getDistancia() const { return distancia;}
string ObjetoAstronomico::getDescripcion() const { return descripcion;}

// Radio visual basado en magnitud, más brillante es más grande
float ObjetoAstronomico::getRadioVisual() const {
    // escala: magnitud -1.5 a 6 -> radio 8 a 2
    float radio = 8.0f - magnitud;
    if (radio < 2.0f) radio = 2.0f;
    if (radio > 10.0f) radio = 10.0f;
    return radio;
}

// Setters
void ObjetoAstronomico::setNombre(string nom) { nombre =  nom;}
void ObjetoAstronomico::setCoordenadas(sf::Vector2f coord) { coordenadas = coord;}
void ObjetoAstronomico::setMagnitud(float mag) {magnitud = mag;}
void ObjetoAstronomico::setDescripcion(string desc) {descripcion = desc;}

// Conversión de tipo a string
string ObjetoAstronomico::getTipoString() const {
    switch(tipo) {
        case TipoObjeto::ESTRELLA: return "Estrella";
        case TipoObjeto::PLANETA: return "Planeta";
        case TipoObjeto::GALAXIA: return "Galaxia";
        case TipoObjeto::NEBULOSA: return "Nebulosa";
        case TipoObjeto::CUMULO: return "Cúmulo";
        case TipoObjeto::SATELITE: return "Satélite";
        case TipoObjeto::COMETA: return "Cometa";
        default: return "Desconocido";
    }
}

string ObjetoAstronomico::getTipoEspectralString() const {
    switch(tipoEspectral) {
        case TipoEspectral::O: return "O (Azul)";
        case TipoEspectral::B: return "B (Azul-Blanco)";
        case TipoEspectral::A: return "A (Blanco)";
        case TipoEspectral::F: return "F (Blanco-Amarillo)";
        case TipoEspectral::G: return "G (Amarillo)";
        case TipoEspectral::K: return "K (Naranja)";
        case TipoEspectral::M: return "M (Rojo)";
        default: return "Desconocido";
    }
}

// Operador de salida para debugging
ostream& operator<<(ostream& os, const ObjetoAstronomico& obj) {
    os << obj.nombre << " (" << obj.getTipoString() << ") - "
       << "Mag: " << obj.magnitud << ", Dist: " << obj.distancia << " ly";
    return os;
}

// Función para obtener color según tipo espectral
sf::Color getColorPorTipoEspectral(TipoEspectral tipo) {
    switch(tipo) {
        case TipoEspectral::O: return sf::Color(155, 176, 255);
        case TipoEspectral::B: return sf::Color(170, 191, 255);  // Azul-Blanco
        case TipoEspectral::A: return sf::Color(202, 215, 255);  // Blanco
        case TipoEspectral::F: return sf::Color(255, 0, 4);  // Blanco-Amarillo
        case TipoEspectral::G: return sf::Color(255, 244, 234);  // Amarillo (Sol)
        case TipoEspectral::K: return sf::Color(255, 210, 161);  // Naranja
        case TipoEspectral::M: return sf::Color(255, 204, 111);  // Rojo
        default: return sf::Color::White;
    }
}