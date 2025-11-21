#include "Camera.h"
#include <cmath>

using namespace std;

Camera::Camera(float startX, float startY)
    : position(startX, startY),
      zoom(0.5f),
      moveSpeed(100.0f),
      zoomSpeed(1.0f),
      minZoom(0.3f),
      maxZoom(3.0f)
{
}

void Camera::move(float deltaX, float deltaY) {
    position.x += deltaX / zoom;
    position.y += deltaY / zoom;
}

void Camera::moveUp(float deltaTime) {
    position.y -= moveSpeed * deltaTime / zoom;
}

void Camera::moveDown(float deltaTime) {
    position.y += moveSpeed * deltaTime / zoom;
}

void Camera::moveLeft(float deltaTime) {
    position.x -= moveSpeed * deltaTime / zoom;
}

void Camera::moveRight(float deltaTime) {
    position.x += moveSpeed * deltaTime / zoom;
}

void Camera::zoomIn(float deltaTime) {
    zoom += moveSpeed * deltaTime;
    if(zoom > maxZoom) zoom = maxZoom;
}

void Camera::zoomOut(float deltaTime) {
    zoom -= moveSpeed * deltaTime;
    if(zoom < minZoom) zoom = minZoom;
}

void Camera::zoomReset(float deltaTime) { 
    zoom = 0.5f;
}

void Camera::setZoom(float newZoom) {
    zoom = newZoom;
    if(zoom < minZoom) zoom = minZoom;
    if(zoom > maxZoom) zoom = maxZoom;
}

sf::Vector2f Camera::getPosition() const {
    return position;
}

float Camera::getZoom() const {
    return zoom;
}

float Camera::getMoveSpeed() const {
    return moveSpeed;
}

void Camera::setPosition(sf::Vector2f newPos) {
    position = newPos;
}

void Camera::setMoveSpeed(float speed) {
    moveSpeed = speed;
}

sf::Vector2f Camera::screenToWorld(sf::Vector2i screenPos, sf::Vector2u windowSize) const {
    // Convertir posición de pantalla a coordenadas del mundo
    float worldX = position.x + (screenPos.x - windowSize.x / 2.0f) / zoom;
    float worldY = position.y + (screenPos.y - windowSize.y / 2.0f) / zoom;
    return sf::Vector2f(worldX, worldY);
}

sf::Vector2f Camera::worldToScreen(sf::Vector2f worldPos, sf::Vector2u windowSize) const {
    // Convertir posición de pantalla a coordenadas del mundo
    float screenX = (worldPos.x - position.x) * zoom + windowSize.x / 2.0f;
    float screenY = (worldPos.y - position.y) * zoom + windowSize.y / 2.0f;
    return sf::Vector2f(screenX, screenY);
}