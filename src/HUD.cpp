#include "../include/HUD.h"
#include <sstream>
#include <iomanip>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

// Constructor
HUD::HUD() : fuenteCargada(false), contadorFrames(0), fpsActual(0.0f) {

    // Colores
    colorNeon = sf::Color(0, 140, 180, 255);
    colorTexto = sf::Color(255, 255, 255, 255);
    colorPanel = sf::Color(0, 0, 0, 150); 
    colorAdvertencia = sf::Color(255, 150, 50, 255);
}

// Cargar fuente
bool HUD::cargarFuente(const string& rutaFuente) {

    // Intentar con archivo
    if (fuente.openFromFile(rutaFuente)) {
        fuenteCargada = true;
        return true;
    }

    // intentar con fuente del sistema (Windows)
    if (fuente.openFromFile("C:/Windows/Fonts/coure.fon")) {
        fuenteCargada = true;
        return true;
    }

    if (fuente.openFromFile("C:/Windows/Fonts/consola.ttf")) {
        fuenteCargada = true;
        return true;
    }

    // si no hay fuente
    fuenteCargada = false;
    return false;    
}

// Dibujar el panel
void HUD::dibujarPanel(sf::RenderWindow& ventana, float x, float y, float ancho, float alto) {

    // Crear el fondo del panel
    sf::RectangleShape fondo({ancho, alto});
    fondo.setPosition({x, y});
    fondo.setFillColor(colorPanel);
    ventana.draw(fondo);

    // Crear el borde
    float grosorBorde = 2.0f;

    // Línea superior
    sf::RectangleShape bordeSuperior({ancho, grosorBorde});
    bordeSuperior.setPosition({x, y});
    bordeSuperior.setFillColor(colorNeon);
    ventana.draw(bordeSuperior);

    // Línea inferior
    sf::RectangleShape bordeInferior({ancho, grosorBorde});
    bordeInferior.setPosition({x, y + alto - grosorBorde});
    bordeInferior.setFillColor(colorNeon);
    ventana.draw(bordeInferior);

    // Linea izquierda
    sf::RectangleShape bordeIzquierdo({ancho, grosorBorde});
    bordeIzquierdo.setPosition({x, y});
    bordeIzquierdo.setFillColor(colorNeon);
    ventana.draw(bordeIzquierdo);

    // Línea derecha
    sf::RectangleShape bordeDerecho({ancho, grosorBorde});
    bordeDerecho.setPosition({x + ancho - grosorBorde, y});
    bordeDerecho.setFillColor(colorNeon);
    ventana.draw(bordeDerecho);
}

// Dibujar texto
void HUD::dibujarTexto(sf::RenderWindow& ventana, const string& texto,
                       float x, float y, unsigned int tamaño) {

    if (!fuenteCargada) return;

    // Dibujar sombra
    sf::Text sombra(fuente, texto, tamaño);
    sombra.setPosition({x + 2, y + 2});
    sombra.setFillColor(sf::Color(0, 0, 0, 150)); 
    ventana.draw(sombra);

    // Dibujar texto principal
    sf::Text textoReal(fuente, texto,  tamaño);
    textoReal.setPosition({x, y});
    textoReal.setFillColor(colorTexto);
    ventana.draw(textoReal);
}

// Actualizar FPS
void HUD::actualizarFPS() {
    
    // Calcular frames por segundo
    contadorFrames++;

    // Cada segundo, calcular FPS promedio
    if (relojFPS.getElapsedTime().asSeconds() >= 1.0f) {
        fpsActual = contadorFrames / relojFPS.restart().asSeconds();
        contadorFrames = 0;
    }
}

// Renderizar HUD completo
void HUD::renderizar(sf::RenderWindow& ventana, const Camera& camara,
                     int totalEstrellas, int estrellasVisibles) {

    // Para dibujar todos los elementos del HUD
                    
    if (!fuenteCargada) return;

    // PANEL SUPERIOR IZQUIERDO: Panel de información de cámara
    float panelX = 10.0f;
    float panelY = 10.0f;
    float panelAncho = 150.0f;
    float panelAlto = 120.0f;

    dibujarPanel(ventana, panelX, panelY, panelAncho, panelAlto);

    // Contenido del panel

    sf::Vector2f pos = camara.getPosition();
    float zoom = camara.getZoom();

    // Título del panel
    dibujarTexto(ventana, "[SISTEMA DE NAVEGACION]", panelX + 10, panelY + 10, 12);

    // Coordenadas
    ostringstream coordX, coordY, zoomStr;
    coordX << fixed << setprecision(1) << "Coord X: " << pos.x;
    coordY << fixed << setprecision(1) << "Coord Y: " << pos.y;
    zoomStr << fixed << setprecision(2) << "Zoom: " << zoom << "x";

    dibujarTexto(ventana, coordX.str(), panelX + 10, panelY + 35, 14);
    dibujarTexto(ventana, coordY.str(), panelX + 10, panelY + 55, 14);
    dibujarTexto(ventana, zoomStr.str(), panelX + 10, panelY + 75, 14);

    ostringstream velStr;
    velStr << "Vel: " << camara.getMoveSpeed();
    dibujarTexto(ventana, velStr.str(), panelX + 10, panelY + 95, 14);

    // Panel superior derecho
    float panel2X = ventana.getSize().x - 290.0f;
    float panel2Y = 10.0f;
    float panel2Ancho = 280.0f;
    float panel2Alto = 100.0f;

    dibujarPanel(ventana, panel2X, panel2Y, panel2Ancho, panel2Alto);

    dibujarTexto(ventana, "[ESTADISTICAS DEL SISTEMA]", panel2X + 10, panel2Y + 10, 12);
  
    ostringstream fpsStr, totalStr, visiblesStr;
    fpsStr << "FPS: " << static_cast<int>(fpsActual);
    totalStr << "Total objetos: " << totalEstrellas;
    visiblesStr << "En viewport: " << estrellasVisibles;

    dibujarTexto(ventana, fpsStr.str(), panel2X + 10, panel2Y + 35, 14);
    dibujarTexto(ventana, totalStr.str(), panel2X + 10, panel2Y + 55, 14);
    dibujarTexto(ventana, visiblesStr.str(), panel2X + 10, panel2Y + 75, 14);

    // Título Principal
    string titulo = "TELESCOPIO VIRTUAL";
    sf::Text tituloTexto(fuente);
    tituloTexto.setString(titulo);
    tituloTexto.setCharacterSize(40);
    tituloTexto.setFillColor(colorNeon);
    tituloTexto.setStyle(sf::Text::Bold);

    sf::FloatRect bounds = tituloTexto.getLocalBounds();
    float width = bounds.size.x;
    tituloTexto.setPosition({(ventana.getSize().x - width) / 2, 15});

    sf::Text sombraTitulo(fuente);
    sombraTitulo.setString(titulo);
    sombraTitulo.setCharacterSize(40);
    sombraTitulo.setFillColor(sf::Color(0, 0, 0, 200));
    sombraTitulo.setStyle(sf::Text::Bold);
    sombraTitulo.setPosition({tituloTexto.getPosition().x + 3, tituloTexto.getPosition().y + 3});

    ventana.draw(sombraTitulo);
    ventana.draw(tituloTexto);

    // Panel de controles
    float panel3X = 10.0f;
    float panel3Y = ventana.getSize().y - 150.f;
    float panel3Ancho = 150.0f;
    float panel3Alto = 115.0f;

    dibujarPanel(ventana, panel3X, panel3Y, panel3Ancho, panel3Alto);

    dibujarTexto(ventana, "[CONTROLES]", panel3X + 10, panel3Y + 10, 12);
    dibujarTexto(ventana, "WASD/Mouse - Navegacion", panel3X + 10, panel3Y + 30, 12);
    dibujarTexto(ventana, "Q/E/Rueda - Zoom", panel3X + 10, panel3Y + 50, 12);
    dibujarTexto(ventana, "Z - Reiniciar Zoom", panel3X + 10, panel3Y + 70, 12);
    dibujarTexto(ventana, "ESC - Salir", panel3X + 10, panel3Y + 90, 12);

}

// Dibujar Bienvenida
void HUD::dibujarBienvenida(sf::RenderWindow& ventana) { 
    
    if(!fuenteCargada) return;

    float centerX = ventana.getSize().x / 2.0f;
    float centerY = ventana.getSize().y / 2.0f;

    string mensaje = "SISTEMA INICIADO";
    sf::Text texto(fuente);
    texto.setString(mensaje);
    texto.setCharacterSize(32);
    texto.setFillColor(colorNeon);

    sf::FloatRect bounds = texto.getLocalBounds();
    float width = bounds.size.x;
    texto.setPosition({centerX - width/2, centerY});

    ventana.draw(texto);
}

// DIbujar Info. de Objeto
void HUD::dibujarInfoObjeto(sf::RenderWindow& ventana, const string& nombre,
                            const string& tipo, float magnitud, float distancia) {
    
    if (!fuenteCargada) return;

    float panelX = ventana.getSize().x - 310.0f;
    float panelY = 150.0f;
    float panelAncho = 300.0f;
    float panelAlto = 150.0f;

    dibujarPanel(ventana, panelX, panelY, panelAncho, panelAlto);

    dibujarTexto(ventana, "[OBJETO SELECCIONADO]", panelX + 10, panelY + 10, 12);
    dibujarTexto(ventana, nombre, panelX + 10, panelY + 35, 16);

    ostringstream info;
    info << "Tipo: " << tipo;
    dibujarTexto(ventana, info.str(), panelX + 10, panelY + 60, 12);

    info.str("");
    info << fixed << setprecision(2) << "Magnitud: " << magnitud;
    dibujarTexto(ventana, info.str(), panelX +10, panelY + 80, 12);

    info.str("");
    info << fixed << setprecision(1) << "Distancia: " << distancia << " ly";
    dibujarTexto(ventana, info.str(), panelX + 10, panelY + 100, 12);
}