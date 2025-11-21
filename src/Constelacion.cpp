#include "../include/Constelacion.h"


Constelacion::Constelacion(string nom, sf::Color col) 
    : nombre(nom), color(col) {}

void Constelacion::agregarEstrella(const string& nombreEstrella) {
    nombresEstrellas.push_back(nombreEstrella);
}

void Constelacion::conectar(int indice1, int indice2) {
    conexiones.push_back({indice1, indice2});
}

string Constelacion::getNombre() const { return nombre; }
sf::Color Constelacion::getColor() const { return color; }
vector<string> Constelacion::getEstrellas() const { return nombresEstrellas; }
vector<pair<int, int>> Constelacion::getConexiones() const { return conexiones; }

// ========================================
// GESTOR DE CONSTELACIONES
// ========================================
GestorConstelaciones::GestorConstelaciones() {}

void GestorConstelaciones::cargarConstelaciones() {
    // CONSTELACIÓN 1: OSA MAYOR
    Constelacion osaMayor("Osa Mayor", sf::Color(173, 216, 230, 200));
    
    // Las 7 estrellas principales del "cazo"
    osaMayor.agregarEstrella("Dubhe");      // 0
    osaMayor.agregarEstrella("Merak");      // 1  
    osaMayor.agregarEstrella("Phecda");     // 2
    osaMayor.agregarEstrella("Megrez");     // 3
    osaMayor.agregarEstrella("Alioth");     // 4
    osaMayor.agregarEstrella("Mizar");      // 5
    osaMayor.agregarEstrella("Alkaid");     // 6
    
    // Conectar para formar el "cazo"
    osaMayor.conectar(0, 1);  // Dubhe - Merak (borde del cazo)
    osaMayor.conectar(1, 2);  // Merak - Phecda
    osaMayor.conectar(2, 3);  // Phecda - Megrez
    osaMayor.conectar(3, 4);  // Megrez - Alioth (mango)
    osaMayor.conectar(4, 5);  // Alioth - Mizar
    osaMayor.conectar(5, 6);  // Mizar - Alkaid
    osaMayor.conectar(3, 0);  // Megrez - Dubhe (cerrar el cazo)
    
    constelaciones.push_back(osaMayor);
    
    // CONSTELACIÓN 2: OSA MENOR (Little Dipper)
    // Color: Verde menta pastel
    Constelacion osaMenor("Osa Menor", sf::Color(152, 251, 152, 200));
    
    osaMenor.agregarEstrella("Polaris");    // 0 - Estrella Polar
    osaMenor.agregarEstrella("Yildun");     // 1
    osaMenor.agregarEstrella("Epsilon");    // 2
    osaMenor.agregarEstrella("Anwar");      // 3
    osaMenor.agregarEstrella("Alifa");      // 4
    osaMenor.agregarEstrella("Pherkad");    // 5
    osaMenor.agregarEstrella("Kochab");     // 6
    
    // Formar el cazo pequeño
    osaMenor.conectar(0, 1);
    osaMenor.conectar(1, 2);
    osaMenor.conectar(2, 3);
    osaMenor.conectar(3, 4);
    osaMenor.conectar(4, 5);
    osaMenor.conectar(5, 6);
    osaMenor.conectar(6, 0);
    
    constelaciones.push_back(osaMenor);
    
    // CONSTELACIÓN 3: CASIOPEA
    Constelacion casiopea("Casiopea", sf::Color(255, 182, 193, 200));
    
    casiopea.agregarEstrella("Schedar");    // 0
    casiopea.agregarEstrella("Caph");       // 1
    casiopea.agregarEstrella("Navi");       // 2
    casiopea.agregarEstrella("Ruchbah");    // 3
    casiopea.agregarEstrella("Segin");      // 4
    
    // Formar la "W"
    casiopea.conectar(0, 1);
    casiopea.conectar(1, 2);
    casiopea.conectar(2, 3);
    casiopea.conectar(3, 4);
    
    constelaciones.push_back(casiopea);
    
    // CONSTELACIÓN 4: ORIÓN (El Cazador)
    Constelacion orion("Orión", sf::Color(255, 218, 185, 200));
    
    orion.agregarEstrella("Betelgeuse");   // 0 - Hombro
    orion.agregarEstrella("Bellatrix");    // 1 - Otro hombro
    orion.agregarEstrella("Rigel");        // 2 - Pie
    orion.agregarEstrella("Alnilam");      // 3 - Cinturón centro
    orion.agregarEstrella("Alnitak");      // 4 - Cinturón
    orion.agregarEstrella("Mintaka");      // 5 - Cinturón
    
    // Formar la figura de Orión
    orion.conectar(0, 1);  // Hombros
    orion.conectar(0, 3);  // Betelgeuse a cinturón
    orion.conectar(1, 3);  // Bellatrix a cinturón
    orion.conectar(3, 4);  // Cinturón
    orion.conectar(4, 5);  // Cinturón
    orion.conectar(3, 2);  // Cinturón a Rigel
    
    constelaciones.push_back(orion);
}

vector<Constelacion> GestorConstelaciones::getConstelaciones() const {
    return constelaciones;
}

bool GestorConstelaciones::perteneceAConstelacion(const string& nombreEstrella, 
                                                   string& nombreConstelacion) const {
    for (const auto& constelacion : constelaciones) {
        for (const auto& estrella : constelacion.getEstrellas()) {
            if (estrella == nombreEstrella) {
                nombreConstelacion = constelacion.getNombre();
                return true;
            }
        }
    }
    return false;
}