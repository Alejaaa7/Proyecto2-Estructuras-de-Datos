#include "CatalogoEstelar.h"
#include <iostream>

CatalogoEstelar::CatalogoEstelar() {
    // es un constructor vacío, se llena con cargarCatalogoInicial()
}

// Agregar objeto al diccionario - O(1)
void CatalogoEstelar::agregar(const ObjetoAstronomico& objeto) {
    objetos[objeto.getNombre()] = objeto;
}

// Buscar objeto por nombre - O(1)
bool CatalogoEstelar::buscar(const string& nombre) const {
    return objetos.find(nombre) != objetos.end();
}

// Obtener objeto por nombre - O(1)
ObjetoAstronomico CatalogoEstelar::obtener(const string& nombre) const {
    auto it = objetos.find(nombre);
    if (it != objetos.end()) {
        return it->second;
    }
    return ObjetoAstronomico(); // Devuelve objeto vacío si no existe
}

// Obtener cantidad de objetos - O(!)
int CatalogoEstelar::getCantidad() const {
    return objetos.size();
}

// Obtener todos los objetos como vector - O(n)
vector<ObjetoAstronomico> CatalogoEstelar::obtenerTodos() const {
    vector<ObjetoAstronomico> lista;
    for (const auto& par : objetos) {
        lista.push_back(par.second);
    }
    return lista;
}

// Listar solo los nombres - O(n)
vector<string> CatalogoEstelar::listarNombres() const {
    vector<string> nombres;
    for (const auto& par : objetos) {
        nombres.push_back(par.first);
    }
    return nombres;
}

// Mostrar estadísticas del catálogo
void CatalogoEstelar::mostrarEstadisticas() const {
    cout << "CATALOGO ESTELAR - ESTADÍSTICAS" << endl;
    cout << "Total de objetos: " << getCantidad() << endl;
    cout << "Estructura: unordered_map (hash table)" << endl;
    cout << "Complejidad búsqueda: O(1) promedio" << endl;
}

// Catálogo inicial con 25 estrellas reales
void CatalogoEstelar::cargarCatalogoInicial() {
    cout << "Cargando catálogo de estrellas reales..." << endl;

    // Las coordenadas son simplificadas para el simulador 2D
    // ESTRELLAS MÁS BRILLANTES DEL CIELO
    agregar(ObjetoAstronomico("Sirius", TipoObjeto::ESTRELLA, 
        {-500, 1000}, -1.46f, TipoEspectral::A, 8.6f,
        "La estrella más brillante del cielo nocturno"));
    
    agregar(ObjetoAstronomico("Canopus", TipoObjeto::ESTRELLA,
        {1500, 2000}, -0.72f, TipoEspectral::A, 310.0f,
        "Segunda estrella más brillante"));
    
    agregar(ObjetoAstronomico("Rigil Kentaurus", TipoObjeto::ESTRELLA,
        {-1000, -1500}, -0.27f, TipoEspectral::G, 4.37f,
        "Sistema estelar más cercano al Sol"));
    
    agregar(ObjetoAstronomico("Arcturus", TipoObjeto::ESTRELLA,
        {2000, -500}, -0.05f, TipoEspectral::K, 36.7f,
        "Gigante roja en la constelación de Bootes"));
    
    agregar(ObjetoAstronomico("Vega", TipoObjeto::ESTRELLA,
        {-1500, -1000}, 0.03f, TipoEspectral::A, 25.0f,
        "Estrella principal de la constelación Lyra"));
    
    agregar(ObjetoAstronomico("Capella", TipoObjeto::ESTRELLA,
        {1000, -2000}, 0.08f, TipoEspectral::G, 42.2f,
        "Sistema estelar múltiple en Auriga"));
    
    agregar(ObjetoAstronomico("Rigel", TipoObjeto::ESTRELLA,
        {-2000, 1500}, 0.13f, TipoEspectral::B, 860.0f,
        "Supergigante azul en Orión"));
    
    agregar(ObjetoAstronomico("Procyon", TipoObjeto::ESTRELLA,
        {500, -1500}, 0.38f, TipoEspectral::F, 11.4f,
        "Estrella binaria en Canis Minor"));
    
    agregar(ObjetoAstronomico("Betelgeuse", TipoObjeto::ESTRELLA,
        {-1750, 1250}, 0.50f, TipoEspectral::M, 642.0f,
        "Supergigante roja en Orión"));
    
    agregar(ObjetoAstronomico("Altair", TipoObjeto::ESTRELLA,
        {1750, 750}, 0.77f, TipoEspectral::A, 16.7f,
        "Estrella principal de Aquila"));
    
    agregar(ObjetoAstronomico("Aldebaran", TipoObjeto::ESTRELLA,
        {-750, -2000}, 0.85f, TipoEspectral::K, 65.0f,
        "Ojo del Toro en Tauro"));
    
    agregar(ObjetoAstronomico("Spica", TipoObjeto::ESTRELLA,
        {2250, 1000}, 1.04f, TipoEspectral::B, 250.0f,
        "Estrella principal de Virgo"));
    
    agregar(ObjetoAstronomico("Antares", TipoObjeto::ESTRELLA,
        {-1250, 1750}, 1.09f, TipoEspectral::M, 550.0f,
        "Corazón del Escorpión"));
    
    agregar(ObjetoAstronomico("Pollux", TipoObjeto::ESTRELLA,
        {1250, -1250}, 1.14f, TipoEspectral::K, 33.7f,
        "Gigante naranja en Géminis"));
    
    agregar(ObjetoAstronomico("Fomalhaut", TipoObjeto::ESTRELLA,
        {-2250, -750}, 1.16f, TipoEspectral::A, 25.0f,
        "Estrella solitaria en Piscis Austrinus"));
    
    agregar(ObjetoAstronomico("Deneb", TipoObjeto::ESTRELLA,
        {2250, 1750}, 1.25f, TipoEspectral::A, 2600.0f,
        "Supergigante en el Cisne"));
    
    agregar(ObjetoAstronomico("Regulus", TipoObjeto::ESTRELLA,
        {750, 2250}, 1.35f, TipoEspectral::B, 79.0f,
        "Corazón del León"));
    
    agregar(ObjetoAstronomico("Castor", TipoObjeto::ESTRELLA,
        {1500, -1500}, 1.58f, TipoEspectral::A, 51.0f,
        "Sistema estelar séxtuple en Géminis"));
    
    agregar(ObjetoAstronomico("Bellatrix", TipoObjeto::ESTRELLA,
        {-1000, 2250}, 1.64f, TipoEspectral::B, 250.0f,
        "Hombro de Orión"));
    
    agregar(ObjetoAstronomico("Alnilam", TipoObjeto::ESTRELLA,
        {0, 1750}, 1.69f, TipoEspectral::B, 2000.0f,
        "Estrella central del Cinturón de Orión"));
    
    agregar(ObjetoAstronomico("Alnitak", TipoObjeto::ESTRELLA,
        {250, 1500}, 1.77f, TipoEspectral::O, 1260.0f,
        "Estrella del Cinturón de Orión"));
    
    agregar(ObjetoAstronomico("Polaris", TipoObjeto::ESTRELLA,
        {0, -2250}, 1.98f, TipoEspectral::F, 433.0f,
        "Estrella Polar del Norte"));
    
    agregar(ObjetoAstronomico("Mizar", TipoObjeto::ESTRELLA,
        {-2000, -1750}, 2.23f, TipoEspectral::A, 82.0f,
        "Estrella doble en la Osa Mayor"));
    
    agregar(ObjetoAstronomico("Alcor", TipoObjeto::ESTRELLA,
        {-1900, -1650}, 3.99f, TipoEspectral::A, 81.0f,
        "Compañera de Mizar"));
    
    agregar(ObjetoAstronomico("Mintaka", TipoObjeto::ESTRELLA,
        {-250, 1600}, 2.23f, TipoEspectral::O, 1200.0f,
        "Primera estrella del Cinturón de Orión"));

    // ESTRELLAS DE CONSTELACIONES
    agregar(ObjetoAstronomico("Dubhe", TipoObjeto::ESTRELLA,
            {-3000, -2000}, 1.79f, TipoEspectral::K, 123.0f,
        "Parte de la Osa Mayor"));
    
    agregar(ObjetoAstronomico("Merak", TipoObjeto::ESTRELLA,
        {-2700, -2300}, 2.37f, TipoEspectral::A, 79.0f,
        "Parte de la Osa Mayor"));
    
    agregar(ObjetoAstronomico("Phecda", TipoObjeto::ESTRELLA,
        {-2400, -2500}, 2.44f, TipoEspectral::A, 84.0f,
        "Parte de la Osa Mayor"));
    
    agregar(ObjetoAstronomico("Megrez", TipoObjeto::ESTRELLA,
        {-2100, -2400}, 3.31f, TipoEspectral::A, 81.0f,
        "Parte de la Osa Mayor"));
    
    agregar(ObjetoAstronomico("Alioth", TipoObjeto::ESTRELLA,
        {-1900, -2100}, 1.77f, TipoEspectral::A, 81.0f,
        "Parte de la Osa Mayor"));
    
    agregar(ObjetoAstronomico("Alkaid", TipoObjeto::ESTRELLA,
        {-1400, -1800}, 1.86f, TipoEspectral::B, 101.0f,
        "Parte de la Osa Mayor"));
    
    // OSA MENOR  
    agregar(ObjetoAstronomico("Yildun", TipoObjeto::ESTRELLA,
        {-100, -2800}, 4.36f, TipoEspectral::A, 172.0f,
        "Parte de la Osa Menor"));
    
    agregar(ObjetoAstronomico("Epsilon", TipoObjeto::ESTRELLA,
        {200, -3000}, 4.23f, TipoEspectral::G, 347.0f,
        "Parte de la Osa Menor"));
    
    agregar(ObjetoAstronomico("Anwar", TipoObjeto::ESTRELLA,
        {400, -2900}, 4.95f, TipoEspectral::K, 390.0f,
        "Parte de la Osa Menor"));
    
    agregar(ObjetoAstronomico("Alifa", TipoObjeto::ESTRELLA,
        {500, -2700}, 5.02f, TipoEspectral::K, 480.0f,
        "Parte de la Osa Menor"));
    
    agregar(ObjetoAstronomico("Pherkad", TipoObjeto::ESTRELLA,
        {450, -2400}, 3.05f, TipoEspectral::A, 480.0f,
        "Parte de la Osa Menor"));
    
    agregar(ObjetoAstronomico("Kochab", TipoObjeto::ESTRELLA,
        {250, -2350}, 2.08f, TipoEspectral::K, 131.0f,
        "Parte de la Osa Menor"));
    
    // CASIOPEA
    agregar(ObjetoAstronomico("Schedar", TipoObjeto::ESTRELLA,
        {3000, -1500}, 2.23f, TipoEspectral::K, 228.0f,
        "Parte de Casiopea"));
    
    agregar(ObjetoAstronomico("Caph", TipoObjeto::ESTRELLA,
        {3300, -1200}, 2.27f, TipoEspectral::F, 54.0f,
        "Parte de Casiopea"));
    
    agregar(ObjetoAstronomico("Navi", TipoObjeto::ESTRELLA,
        {3500, -1500}, 2.47f, TipoEspectral::B, 613.0f,
        "Parte de Casiopea"));
    
    agregar(ObjetoAstronomico("Ruchbah", TipoObjeto::ESTRELLA,
        {3600, -1800}, 2.66f, TipoEspectral::A, 99.0f,
        "Parte de Casiopea"));
    
    agregar(ObjetoAstronomico("Segin", TipoObjeto::ESTRELLA,
        {3800, -2000}, 3.38f, TipoEspectral::B, 442.0f,
        "Parte de Casiopea"));

    cout << "Catálogo cargado: " << getCantidad() << " estrellas" << endl;
    mostrarEstadisticas();
}