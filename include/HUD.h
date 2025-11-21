#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Camera.h"

using namespace std;

class HUD {
private:
    sf::Font fuente;
    bool fuenteCargada;

    // COlores
    sf::Color colorNeon;
    sf::Color colorTexto;
    sf::Color colorPanel;
    sf::Color colorAdvertencia;

    // FPS tracking
    sf::Clock relojFPS;
    int contadorFrames;
    float fpsActual;
    
    // Dibujar un panel
    void dibujarPanel(sf::RenderWindow& ventana, float x, float y, float ancho, float alto);
    
    // Dibujar texto con sombra
    void dibujarTexto(sf::RenderWindow& ventana, const string& texto,
                      float x, float y, unsigned int tamaño = 14);
    
public:
    HUD();

    // Cargar fuente
    bool cargarFuente(const string& rutaFuente);

    // Renderizar todo el HUD
    void renderizar(sf::RenderWindow& ventana, const Camera& camara,
                    int totalEstrellas, int estrellasVisibles);
        
    // Actualizar FPS
    void actualizarFPS();

    // Dibujar mensaje de bienvenida
    void dibujarBienvenida(sf::RenderWindow& ventana);

    // Dibujar indicador de objeto seleccionado
    void dibujarInfoObjeto(sf::RenderWindow& ventana, const string& nombre,
                           const string& tipo, float magnitud, float distancia);
    
    // Dibujar cruz de mira
    void dibujarCruzDeMira(sf::RenderWindow& ventana);
};

#endif