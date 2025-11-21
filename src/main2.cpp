/*#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "../include/Camera.h"
#include "../include/CatalogoEstelar.h"
#include "../include/ObjetoAstronomico.h"
#include "../include/QuadTree.h"
#include "../include/MatrizDispersa.h"
#include "../include/HUD.h"
#include "../include/Constelacion.h"

using namespace std;

int main()
{
    // Crear ventana 1280x720
    sf::RenderWindow window(sf::VideoMode({1280u, 720u}), "Telescopio Virtual");
    window.setFramerateLimit(60);

    // Crear HUD
    HUD hud;
    if (!hud.cargarFuente("assets/fonts/coure.fon")) {
    }

    // SISTEMA DE SELECCIÓN DE OBJETOS
    ObjetoAstronomico* objetoSeleccionado = nullptr;
    bool mostrarInfo = false;

    // AHORA SISTEMA DE CONSTELACIONES
    GestorConstelaciones gestorConstelaciones;
    gestorConstelaciones.cargarConstelaciones();
    cout << "Constelaciones cargadas: " << gestorConstelaciones.getConstelaciones().size() << endl;

    // Fondo negro espacial
    sf::Color espacioNegro(5, 5, 15);

    // Crear cámara
    Camera camera(0.0f, 0.0f);

    // Crear catálogo estelar (DICCIONARIO)
    CatalogoEstelar catalogo;
    catalogo.cargarCatalogoInicial();
    
    // Crear QuadTree, el árbol de segmentos espacial
    // Definir límites del universo: -6000 a 6000 en X y Y
    
    Rectangulo universo(0, 0, 12000, 12000); // centro en {0, 0} y tamaño 12000x12000
    QuadTree* arbol = new QuadTree(universo, 4); // capacidad 4 estrellas por nodo

    cout << "Construyendo el árbol de segmentos" << endl;

    // Obtener estrellas del catálogo
    vector<ObjetoAstronomico> estrellasReales = catalogo.obtenerTodos();

    // insertar las 25 estrellas reales en el arbol
    for (auto& estrella : estrellasReales) {
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
            TipoEspectral::O, TipoEspectral::B, TipoEspectral::A, 
            TipoEspectral::F, TipoEspectral::G, TipoEspectral::K, TipoEspectral::M 
        };
        TipoEspectral tipo = tipos[rand() % 7];

        ObjetoAstronomico estrella("Star_" + to_string(i), TipoObjeto::ESTRELLA,
                {x, y}, mag, tipo, 100.0f + rand() % 500, "Estrella aleatoria");

        estrellasAleatorias.push_back(estrella); // se guarda en vector
        arbol->insertar(&estrellasAleatorias.back()); // se inserta en árbol
    }

    cout << "Estrellas insertadas en el árbol: " << arbol->contarObjetos() << endl;
    cout << "\nEstructura del árbol: " << endl;
    arbol->mostrarEstadisticas(); // se muestra cómo quedó el árbol
        
    cout << "Total de estrellas visibles: " << estrellasReales.size() << endl;
    cout << "  - Catalogadas: 25 estrellas reales" << endl;
    cout << "  - Adicionales: " << (estrellasReales.size() - 25) << " estrellas procedurales" << endl;
    
    // Campo estelar de fondo
    // Generar 200 estrellas diminutas para realismo y estética
    struct EstrellaFondo {
        sf::Vector2f posicion;
        float brillo;  // 0.3 a 1.0
    };
    
    vector<EstrellaFondo> estrellasFondo;
    srand(time(0));
    for (int i = 0; i < 25000; i++) {
        float x = (rand() % 12000) - 6000.0f;
        float y = (rand() % 12000) - 6000.0f;
        float brillo = 0.3f + (rand() % 70) / 100.0f;
        estrellasFondo.push_back({{x, y}, brillo});
    }
    
    cout << "Estrellas disponibles para busqueda:" << endl;
    vector<string> nombres = catalogo.listarNombres();
    for (size_t i = 0; i < min(nombres.size(), size_t(5)); i++) {
        cout << "  - " << nombres[i] << endl;
    }
    cout << "  ... y " << (nombres.size() - 5) << " más" << endl;

    // Crear Matriz Dispersa
    // Dividir eluniverso en grid de 200x200 celdas virtuales
    // Cada celda tiene 60 unidades de tamaño
    MatrizDispersa* gridEspacial = new MatrizDispersa(200, 200, 60.0f);

    cout << "Construtendo Matriz Dispersa" << endl;

    // Insertar todas las estrellas en la matrzi
    for (auto& estrella : estrellasReales) {
        gridEspacial->insertar(&estrella);
    }
    for (auto& estrella : estrellasAleatorias) {
        gridEspacial->insertar(&estrella);
    }

    // Mostrar estadísticas de la matriz
    gridEspacial->mostrarEstadisticas();

    // Obtener celdas ocupadas por referencia
    vector<Coordenada> celdasOcupadas = gridEspacial->obtenerCeldasOcupadas();
    cout << "Ejemplo de celdas con estrellas: " << endl;
    for (size_t i = 0; i < min(celdasOcupadas.size(), size_t(5)); i++) {
        auto coord = celdasOcupadas[i];
        vector<ObjetoAstronomico*> objetos = gridEspacial->obtenerCelda(coord.first, coord.second);
        cout << "Celda (" << coord.first << ", " << coord.second << "): "
             << objetos.size() << " estrellas" << endl;
    }

    cout << "... y" << (celdasOcupadas.size() - 5) << " celdas más ocupadas" << endl;

    // Reloj para deltaTime
    sf::Clock clock;

    cout << "TELESCOPIO VIRTUAL - v0.1" << endl;
    cout << "Controles:" << endl;
    cout << "  WASD      - Mover camara" << endl;
    cout << "  Mouse     - Mover al acercar a bordes" << endl;
    cout << "  Q/E/Rueda       - Zoom Out/In" << endl;
    cout << "  ESC       - Salir" << endl;

    // Game loop
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        hud.actualizarFPS();

        // Eventos
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code == sf::Keyboard::Key::Escape)
                    window.close();
            }

            if (const auto* wheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>()) {
                if (wheelScrolled->wheel == sf::Mouse::Wheel::Vertical) {
                    if (wheelScrolled->delta > 0) {
                        // hacia arriba = zoom in
                        camera.zoomIn(0.1f);
                    }
                    else {
                        // hacia abajo = zoom out
                        camera.zoomOut(0.1f);
                    }
                }
            }

        // Input continuo (movimiento y zoom)
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
        const float edgeThreshold = 50.0f;  // Pixeles desde el borde
        const float edgeSpeed = 150.0f;     // Velocidad en los bordes

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

        // Renderizado
        window.clear(espacioNegro);

        // Antes de todo, dibujar las constelaciones
         
        for (const auto& constelacion : gestorConstelaciones.getConstelaciones()) {
            vector<string> nombresEstrellas = constelacion.getEstrellas();
            vector<pair<int, int>> conexiones = constelacion.getConexiones();
            
            // Obtener posiciones de las estrellas de esta constelación
            vector<sf::Vector2f> posiciones;
            for (const auto& nombre : nombresEstrellas) {
                if (catalogo.buscar(nombre)) {
                    ObjetoAstronomico estrella = catalogo.obtener(nombre);
                    sf::Vector2f screenPos = camera.worldToScreen(estrella.getCoordenadas(), window.getSize());
                    posiciones.push_back(screenPos);
                } else {
                    posiciones.push_back({-9999, -9999});  // Fuera de pantalla si no existe
                }
            }
            
            // Dibujar líneas conectando las estrellas
            for (const auto& conexion : conexiones) {
                int idx1 = conexion.first;
                int idx2 = conexion.second;
                
                if (idx1 < posiciones.size() && idx2 < posiciones.size()) {
                    sf::Vector2f pos1 = posiciones[idx1];
                    sf::Vector2f pos2 = posiciones[idx2];
                    
                    // Solo dibujar si ambas están en pantalla
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

        // 1. Dibujar estrellas de fondo primero (más pequeñas)
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


        // Calcular región visible de la cámara
        sf::Vector2f topLeft = camera.screenToWorld({0, 0}, window.getSize());
        sf::Vector2f bottomRight = camera.screenToWorld({(int)window.getSize().x, (int)window.getSize().y}, window.getSize());

        float regionX = (topLeft.x + bottomRight.x) / 2;
        float regionY = (topLeft.y + bottomRight.y) / 2;
        float regionW = abs(bottomRight.x - topLeft.x);
        float regionH = abs(bottomRight.y - topLeft.y);

        Rectangulo regionVisible(regionX, regionY, regionW, regionH);

        // Buscar SOLO las estrellas en la región visible -O(log n)
        vector<ObjetoAstronomico*> estrellasVisibles = arbol->buscar(regionVisible);

        // Ahora solo se dibuja las estrellas que encontró el QuadTree
        for(auto estrella : estrellasVisibles) {
            sf::Vector2f screenPos = camera.worldToScreen(estrella->getCoordenadas(), window.getSize());

            // Solo dibujar si está en pantalla
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

        if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mousePressed->button == sf::Mouse::Button::Left) {
                    
                // Convertir posición del mouse a coordenadas del mundo
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f worldPos = camera.screenToWorld(mousePos, window.getSize());

                // Buscar objeto cercano al click
                float minDistancia = 50.0f / camera.getZoom();
                objetoSeleccionado = nullptr;

                for (auto estrella : estrellasVisibles) {
                    sf::Vector2f pos = estrella->getCoordenadas();
                    float dx = worldPos.x - pos.x;
                    float dy = worldPos.y - pos.y;
                    float distancia = sqrt(dx*dx + dy*dy);

                    if (distancia < minDistancia) {
                        minDistancia = distancia;
                        objetoSeleccionado = estrella;
                        mostrarInfo = true;
                    }
                }

                if (objetoSeleccionado) {
                    cout << "Click en: " <<objetoSeleccionado->getNombre() << endl;
                }
            }

            // Click derecho para deseleccionar
            if (mousePressed->button == sf::Mouse::Button::Right) {
                objetoSeleccionado = nullptr;
                mostrarInfo = false;
            }
        }
    }

        // HUD simple - Mostrar posición y zoom
        sf::Font font;
        // Nota: Por ahora sin fuente, agregaremos después
        
        // Dibujar la interfaz sobre todo lo demás
        hud.renderizar(window, camera, arbol->contarObjetos(), estrellasVisibles.size());
        
        // CAMBIO: Mostrar info del objeto seleccionado
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

    // Limpiar memoria
    delete arbol; 
    delete gridEspacial;

    return 0;
}*/