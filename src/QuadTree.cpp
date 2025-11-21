#include "QuadTree.h"
#include <iostream>

using namespace std;

// Constructor
QuadTree::QuadTree(Rectangulo limites, int cap)
    : limites(limites), capacidad(cap), subdividido(false),
      noroeste(nullptr), noreste(nullptr), suroeste(nullptr),  sureste(nullptr)
{
    // Recibe el rectángulo que representa esta región
    // la capacidad es cuántas estrellas puede tener ANTES de subdividir
    // los 4 hijos empiezan en nullptr (todavía no existen)
}

// Destructor
QuadTree::~QuadTree() {
    // Cuando destruimos el nodo, se destruyen recursivamente todos sus hijos
    // eso libera la memoria de toodo el árbol

    delete noreste;
    delete noroeste;
    delete sureste;
    delete suroeste;
}

// Subdividir
void QuadTree::subdividir() {
    // esta función divide este nodo en 4 hijos (cuadrantes)
    float x = limites.x;
    float y = limites.y;
    float w = limites.ancho / 2;
    float h = limites.alto / 2; // cada hijo tiene la mitad de ancho y alto

    // Crear los 4 hijos con sus respectivas regiones

    // NOROESTE
    Rectangulo nw(x - w/2, y - h/2, w, h);
    noroeste = new QuadTree(nw, capacidad);

    // NORESTE
    Rectangulo ne(x + w/2, y - h/2, w, h);
    noreste = new QuadTree(ne, capacidad);

    // SUROESTE
    Rectangulo sw(x - w/2, y + h/2, w, h);
    suroeste = new QuadTree(sw, capacidad);

    // SURESTE
    Rectangulo se(x + w/2, y + w/2, w, h);
    sureste = new QuadTree(se, capacidad);

    subdividido = true; // marcar que ya se subdividió
}

// Insertar
bool QuadTree::insertar(ObjetoAstronomico* objeto) {
    
    // primero, verificar si el objeto está dentro de los límites de este nodo
    if (!limites.contiene(objeto->getCoordenadas())) {
        return false; // no está en esta región, no se inserta aquí
    } 

    // luego, si aún hay espacio y no se ha subdividido, agregarlo aquí
    if (objetos.size() < capacidad && !subdividido) {
        objetos.push_back(objeto);
        return true;
    }

    // si no hay espacio, subdividir (si no se ha hecho)
    if (!subdividido) {
        subdividir();

        // reubicar objetos existentes en los hijos
        for (auto obj : objetos) {
            noroeste->insertar(obj) || noreste->insertar(obj) ||
            suroeste->insertar(obj) || sureste->insertar(obj);
        }
        objetos.clear(); // ya no se necesitan los objetos aquí
    }

    // intentar insertar en alguno de los 4 hijos
    // el operador || hace que se intente en cada uno hasta que uno acepte
    return noroeste->insertar(objeto) || noreste->insertar(objeto) ||
           suroeste->insertar(objeto) || sureste->insertar(objeto);
}

// Buscar

vector<ObjetoAstronomico*> QuadTree::buscar(const Rectangulo& region) const {

    // retorna SOLO los objetos que están en la región especificada
    // NO revisa regiones que no intersectan

    vector<ObjetoAstronomico*> encontrados;

    // si esta región NO intersecta con la región buscada, retornar vacío
    if (!limites.intersecta(region)) {
        return encontrados; // vector vacío, no hay nada aquí
    }

    // si sí intersecta, revisar los objetos de este nodo
    for (auto obj : objetos) { 
        if (region.contiene(obj->getCoordenadas())) {
            encontrados.push_back(obj);
        }
    }

    // si este nodo está subdividido, se busca recursivamente en los hijos
    if (subdividido){
        // buscar en los 4 cuadrantes y combinar los resultados
        auto nw = noroeste->buscar(region);
        auto ne = noreste->buscar(region);
        auto sw = suroeste->buscar(region);
        auto se = sureste->buscar(region);

        // Agregar todos los resultados
        encontrados.insert(encontrados.end(), nw.begin(), nw.end());
        encontrados.insert(encontrados.end(), ne.begin(), ne.end());
        encontrados.insert(encontrados.end(), sw.begin(), sw.end());
        encontrados.insert(encontrados.end(), se.begin(), se.end());
    } 
    return encontrados;
}

// Obtener todos
vector<ObjetoAstronomico*> QuadTree::obtenerTodos() const {
    // retorna TODOS los objetos del árbol

    vector<ObjetoAstronomico*> todos = objetos;

    if (subdividido) {
        auto nw = noroeste->obtenerTodos();
        auto ne = noreste->obtenerTodos();
        auto sw = suroeste->obtenerTodos();
        auto se = sureste->obtenerTodos();

        todos.insert(todos.end(), nw.begin(), nw.end());
        todos.insert(todos.end(), ne.begin(), ne.end());
        todos.insert(todos.end(), sw.begin(), sw.end());
        todos.insert(todos.end(), se.begin(), se.end());

    }
    return todos;
}

// Limpiar

void QuadTree::limpiar() {
    
    // Elimina todos los objetos y destruye los hijos
    // para "resetear" el árbol

    objetos.clear();

    if (subdividido) {
        delete noroeste;
        delete noreste;
        delete suroeste;
        delete sureste;

        noroeste = noreste = suroeste = sureste = nullptr;
        subdividido = false;
    }
}

// Contar Objetos
int QuadTree::contarObjetos() const {

    // Cuenta recursivamente cuántos objetos hay EN TOTAL

    int count = objetos.size();

    if(subdividido) {
        count += noroeste->contarObjetos();
        count += noreste->contarObjetos();
        count += suroeste->contarObjetos();
        count += sureste->contarObjetos();
    }

    return count;
}

// Mostrar las estadísticas :)

void QuadTree::mostrarEstadisticas(int nivel) const{

    // Muestra información del árbol
    // el nivel es la profundidad en el árbol (0 es la raíz, 1 los hijos, 2 los nietos y etc)

    // imprimir identación según el nivel
    for (int i = 0; i < nivel; i++) cout << " ";

    cout << "Nivel " << nivel << ": "
         << objetos.size() << " objetos, "
         << "Subdividido: " << (subdividido ? "Sí" : "No") << endl;

    // Si está subdividido, mostrar estadísticas de los hijos

    if (subdividido) {
        noroeste->mostrarEstadisticas(nivel + 1);
        noreste->mostrarEstadisticas(nivel + 1);
        suroeste->mostrarEstadisticas(nivel + 1);
        sureste->mostrarEstadisticas(nivel + 1);
    }
}