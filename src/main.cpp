#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "../include/Camera.h"
#include "../include/CatalogoEstelar.h"
#include "../include/QuadTree.h"
#include "../include/MatrizDispersa.h"
#include "../include/HUD.h"
#include "../include/Constelacion.h"

using namespace std;

// Estructura para las estrellas de fondo
struct EstrellaFondo {
    sf::Vector2f posicion;
    float brillo;
};

int main() {
    // Crear ventana 1280x720
    sf::RenderWindow window(sf::VideoMode({1280u, 720u}), "Telescopio Virtual");
    window.setFramerateLimit(60);

    // Fondo negro espacial
    sf::Color espacioNegro(5, 5, 15);

    // Crear cámara
    Camera camera(0.0f, 0.0f);

    // Crear HUD
    HUD hud;
    if (!hud.cargarFuente("assets/fonts/coure.fon")) {
        cout << "Usando fuente del sistema" << endl;
    }

    // Sistema de selección de objetos
    ObjetoAstronomico* objetoSeleccionado = nullptr;
    bool mostrarInfo = false;

    // Sistema de Constelaciones
    GestorConstelaciones gestorConstelaciones;
    gestorConstelaciones.cargarConstelaciones();
    cout << "Constelaciones cargadas: " << gestorConstelaciones.getConstelaciones().size() << endl;

    // Crear catálogo estelar (DICCIONARIO)
    CatalogoEstelar catalogo;
    catalogo.cargarCatalogoInicial();

    // Crear Quadtree (ÁRBOL DE SEGMENTOS)
    Rectangulo universo(0, 0, 12000, 12000);
    QuadTree* arbol = new QuadTree(universo, 4);

    cout << "Construyendo árbol de segmentos..." << endl;

    // Obtener estrellas del catálogo
    vector<ObjetoAstronomico> estrellasReales = catalogo.obtenerTodos();

    // Insertar las estrellas reales en el árbol
    for (auto & estrella : estrellasReales) {
        arbol->insertar(&estrella);
    }

    // Crear y agregar estrellas aleatorias
    vector<ObjetoAstronomico> estrellasAleatorias;
    srand(time(0));

    for (int i = 0; i < 100; i++) {
        float x = (rand() % 10000) - 5000.0f;
        float y = (rand() % 10000) - 5000.0f;
        float mag = 2.0f + (rand() % 40) / 10.0f;

        TipoEspectral tipos[] = {
            TipoEspectral::O, TipoEspectral::B, TipoEspectral:: A,
            TipoEspectral::F, TipoEspectral::G, TipoEspectral::K, TipoEspectral::M
        };
        TipoEspectral tipo = tipos[rand() % 7];

        ObjetoAstronomico estrella("Star_" + to_string(i), TipoObjeto::ESTRELLA,
            {x, y}, mag, tipo, 100.0f + rand() % 500, "Estrella aleatoria");

        estrellasAleatorias.push_back(estrella);
        arbol->insertar(&estrellasAleatorias.back());
    }

    cout << "Estrellas insertadas en el árbol: " << arbol->contarObjetos() << endl;
    cout << "\nEstructura del árbol:" << endl;
    arbol->mostrarEstadisticas();

    // Crear matriz dispersa
    MatrizDispersa* gridEspacial = new MatrizDispersa(200, 200, 60.0f);

    cout << "Construyendo Matriz Dispersa..." << endl;

    for (auto& estrella : estrellasReales) {
        gridEspacial->insertar(&estrella);
    }
    for (auto& estrella : estrellasAleatorias) {
        gridEspacial->insertar(&estrella);
    }

    gridEspacial->mostrarEstadisticas();

    vector<Coordenada> celdasOcupadas = gridEspacial->obtenerCeldasOcupadas();
    cout << "Ejemplo de celdas con estrellas:" << endl;
    for (size_t i = 0; i < min(celdasOcupadas.size(), size_t(5)); i++) {
        auto coord = celdasOcupadas[i];
        vector<ObjetoAstronomico*> objetos = gridEspacial->obtenerCelda(coord.first, coord.second);
        cout << "  Celda (" << coord.first << ", " << coord.second << "): " 
             << objetos.size() << " estrellas" << endl;
    }
    cout << "  ... y " << (celdasOcupadas.size() - 5) << " celdas mas ocupadas" << endl;

    // Campo estelar de fondo
    vector<EstrellaFondo> estrellasFondo;
    for (int i = 0; i < 15000; i++) {
        float x = (rand() % 12000) - 6000.0f;
        float y = (rand() % 12000) - 6000.0f;
        float brillo = 0.3f + (rand() % 40) / 100.0f;
        estrellasFondo.push_back({{x, y}, brillo});
    }

    cout << "\nEstrellas disponibles para busqueda:" << endl;
    vector<string> nombres = catalogo.listarNombres();
    for (size_t i = 0; i < min(nombres.size(), size_t(5)); i++) {
        cout << "  - " << nombres[i] << endl;
    }
    cout << "  ... y " << (nombres.size() - 5) << " mas" << endl;

    // Reloj para deltaTime
    sf::Clock clock;

    cout << "  TELESCOPIO VIRTUAL " << endl;
    cout << "Controles:" << endl;
    cout << "  WASD      - Mover camara" << endl;
    cout << "  Mouse     - Mover al acercar a bordes" << endl;
    cout << "  Q/E/Rueda - Zoom Out/In" << endl;
    cout << "  Click Izq - Seleccionar objeto" << endl;
    cout << "  Click Der - Deseleccionar" << endl;
    cout << "  ESC       - Salir" << endl;

    // Game loop
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        hud.actualizarFPS();

        // Input continuo (movimiento y zoom con teclado)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            camera.moveUp(deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            camera.moveDown(deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            camera.moveLeft(deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            camera.moveRight(deltaTime);
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
            camera.zoomIn(deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
            camera.zoomOut(deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
            camera.zoomReset(deltaTime);

        // Movimiento con mouse en los bordes
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        const float edgeThreshold = 50.0f;
        const float edgeSpeed = 150.0f;

        if (mousePos.x < edgeThreshold) {
            camera.moveLeft(deltaTime * (edgeSpeed / camera.getMoveSpeed()));
        }
        if (mousePos.x > (int)window.getSize().x - edgeThreshold) {
            camera.moveRight(deltaTime * (edgeSpeed / camera.getMoveSpeed()));
        }
        if (mousePos.y < edgeThreshold) {
            camera.moveUp(deltaTime * (edgeSpeed / camera.getMoveSpeed()));
        }
        if (mousePos.y > (int)window.getSize().y - edgeThreshold) {
            camera.moveDown(deltaTime * (edgeSpeed / camera.getMoveSpeed()));
        }

        // Calcular región visible de la cámara
        sf::Vector2f topLeft = camera.screenToWorld({0, 0}, window.getSize());
        sf::Vector2f bottomRight = camera.screenToWorld({(int)window.getSize().x, (int)window.getSize().y}, window.getSize());

        float regionX = (topLeft.x + bottomRight.x) / 2;
        float regionY = (topLeft.y + bottomRight.y) / 2;
        float regionW = abs(bottomRight.x - topLeft.x);
        float regionH = abs(bottomRight.y - topLeft.y);

        Rectangulo regionVisible(regionX, regionY, regionW, regionH);

        // Buscar SOLO las estrellas en la región visible
        vector<ObjetoAstronomico*> estrellasVisibles = arbol->buscar(regionVisible);

        // Manejo de eventos
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code == sf::Keyboard::Key::Escape)
                    window.close();
            }

            // Zoom con rueda del mouse
            if (const auto* wheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>())
            {
                if (wheelScrolled->wheel == sf::Mouse::Wheel::Vertical)
                {
                    if (wheelScrolled->delta > 0) {
                        camera.zoomIn(0.1f);
                    } else {
                        camera.zoomOut(0.1f);
                    }
                }
            }

            // Click en objetos
            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mousePressed->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2i mousePosClick = sf::Mouse::getPosition(window);
                    sf::Vector2f worldPos = camera.screenToWorld(mousePosClick, window.getSize());
                    
                    float minDistancia = 50.0f / camera.getZoom();
                    objetoSeleccionado = nullptr;
                    
                    for (auto estrella : estrellasVisibles) {
                        sf::Vector2f pos = estrella->getCoordenadas();
                        float dx = worldPos.x - pos.x;
                        float dy = worldPos.y - pos.y;
                        float distancia = std::sqrt(dx*dx + dy*dy);
                        
                        if (distancia < minDistancia) {
                            minDistancia = distancia;
                            objetoSeleccionado = estrella;
                            mostrarInfo = true;
                        }
                    }
                    
                    if (objetoSeleccionado) {
                        cout << "Click en: " << objetoSeleccionado->getNombre() << endl;
                    }
                }
                
                if (mousePressed->button == sf::Mouse::Button::Right)
                {
                    objetoSeleccionado = nullptr;
                    mostrarInfo = false;
                }
            }
        }

    // Renderizado
        window.clear(espacioNegro);

        // DIBUJAR CONSTELACIONES
        for (const auto& constelacion : gestorConstelaciones.getConstelaciones()) {
            vector<string> nombresEstrellas = constelacion.getEstrellas();
            vector<pair<int, int>> conexiones = constelacion.getConexiones();
            
            vector<sf::Vector2f> posiciones;
            for (const auto& nombre : nombresEstrellas) {
                if (catalogo.buscar(nombre)) {
                    ObjetoAstronomico estrella = catalogo.obtener(nombre);
                    sf::Vector2f screenPos = camera.worldToScreen(estrella.getCoordenadas(), window.getSize());
                    posiciones.push_back(screenPos);
                } else {
                    posiciones.push_back({-9999, -9999});
                }
            }
            
            for (const auto& conexion : conexiones) {
                int idx1 = conexion.first;
                int idx2 = conexion.second;
                
                if (idx1 < posiciones.size() && idx2 < posiciones.size()) {
                    sf::Vector2f pos1 = posiciones[idx1];
                    sf::Vector2f pos2 = posiciones[idx2];
                    
                    if (pos1.x > -100 && pos1.x < 1380 && pos1.y > -100 && pos1.y < 820 &&
                        pos2.x > -100 && pos2.x < 1380 && pos2.y > -100 && pos2.y < 820) {
                        
                        sf::Vertex linea[2];
                        linea[0].position = pos1;
                        linea[0].color = constelacion.getColor();
                        linea[1].position = pos2;
                        linea[1].color = constelacion.getColor();
                        
                        window.draw(linea, 2, sf::PrimitiveType::Lines);
                    }
                }
            }
        }

        // 1. Dibujar estrellas de fondo
        for (const auto& estrella : estrellasFondo) {
            sf::Vector2f screenPos = camera.worldToScreen(estrella.posicion, window.getSize());
            
            if (screenPos.x >= -10 && screenPos.x <= 1290 &&
                screenPos.y >= -10 && screenPos.y <= 730) {
                
                float radio = 0.8f * camera.getZoom();
                if (radio < 0.5f) radio = 0.5f;
                if (radio > 2.0f) radio = 2.0f;
                
                sf::CircleShape circle(radio);
                sf::Color color(255, 255, 255, static_cast<unsigned char>(estrella.brillo * 255));
                circle.setFillColor(color);
                circle.setPosition(screenPos);
                circle.setOrigin({circle.getRadius(), circle.getRadius()});
                window.draw(circle);
            }
        }

        // 2. Dibujar estrellas principales
        for (auto estrella : estrellasVisibles) {
            sf::Vector2f screenPos = camera.worldToScreen(estrella->getCoordenadas(), window.getSize());
            
            if (screenPos.x >= -50 && screenPos.x <= 1330 &&
                screenPos.y >= -50 && screenPos.y <= 770) {
                
                float radio = estrella->getRadioVisual() * camera.getZoom();
                sf::CircleShape circle(radio);
                circle.setFillColor(estrella->getColor());
                circle.setPosition(screenPos);
                circle.setOrigin({circle.getRadius(), circle.getRadius()});
                window.draw(circle);
            }
        }

        // HUD
        hud.renderizar(window, camera, arbol->contarObjetos(), estrellasReales.size());
        
        // Info de objeto seleccionado
        if (mostrarInfo && objetoSeleccionado) {
            hud.dibujarInfoObjeto(window, 
                objetoSeleccionado->getNombre(),
                objetoSeleccionado->getTipoString(),
                objetoSeleccionado->getMagnitud(),
                objetoSeleccionado->getDistancia()
            );
        }

        window.display();
    }

    // Liberar memoria
    delete arbol;
    delete gridEspacial;
    
    return 0;

}