#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

class Camera {
private:
    sf::Vector2f position; // posición en coordenadas astronómicas (RA, Dec)
    float zoom; // nivel de zoom (1.0 = nomral)
    float moveSpeed; // velocidad de movimiento
    float zoomSpeed; // velocidad de zoom

    // Límites del campo visual
    float minZoom;
    float maxZoom;

public:

    // Constructor
    Camera(float startX = 0.0f, float startY = 0.0f);

    // Movimiento
    void move(float deltaX, float deltaY);
    void moveUp(float deltaTime);
    void moveDown(float deltaTime);
    void moveLeft(float deltaTime);
    void moveRight(float deltaTime);

    // Zoom
    void zoomIn(float deltaTime);
    void zoomOut(float deltaTime);
    void setZoom(float newZoom);
    void zoomReset(float deltaTime);

    // Getters
    sf::Vector2f getPosition() const;
    float getZoom() const;
    float getMoveSpeed() const;

    // Setters
    void setPosition(sf::Vector2f newPos);
    void setMoveSpeed(float speed);

    // Convertir coordenadas de pantalla a mundo
    sf::Vector2f screenToWorld(sf::Vector2i screenPos, sf::Vector2u windowSize) const;

    // Convertir coordenadas de mundo a pantalla
    sf::Vector2f worldToScreen(sf::Vector2f worldPos, sf::Vector2u windowSize) const;

};

#endif