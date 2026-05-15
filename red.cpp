#include "red.h"

void Red::ruta_mas_corta(const string& origen) {
    map<string, int> dist;
    map<string, vector<string>> paths;
    // Inicializar todas las distancias en infinito
    for (auto& par : routers) {
        dist[par.first]  = INT_MAX;
        paths[par.first] = {};
    }
    dist[origen]  = 0;
    paths[origen] = {origen};

    // Lista de nodos pendientes por visitar
    list<string> pendientes;
    for (auto& par : routers) pendientes.push_back(par.first);

    while (!pendientes.empty()) {
        // Elegir el nodo con menor distancia actual
        auto minIt = pendientes.begin();
        for (auto it = pendientes.begin(); it != pendientes.end(); ++it)
            if (dist[*it] < dist[*minIt]) minIt = it;

        string u = *minIt;
        pendientes.erase(minIt);

        if (dist[u] == INT_MAX) break; // resto inaccesible

        for (auto& par : routers[u].getVecinos()) {
            const string& v = par.first;
            int           w = par.second;
            if (!routers.count(v)) continue;
            int nuevo = dist[u] + w;
            if (nuevo < dist[v]) {
                dist[v]  = nuevo;
                paths[v] = paths[u];
                paths[v].push_back(v);
            }
        }
    }

    routers[origen].limpiarTablaCostos();
    for (auto& par : dist)
        routers[origen].actualizarCosto(par.first, par.second);

    caminos[origen] = paths;
}

void Red::recalcularTodo() {
    for (auto& par : routers) ruta_mas_corta(par.first);
}

void Red::agregarEnrutador(const string& id) {
    if (routers.count(id)) {
        cout << "[!] El enrutador " << id << " ya existe." << endl;
        return;
    }
    routers[id] = Enrutador(id);
    recalcularTodo();
    cout << "[+] Enrutador " << id << " agregado." << endl;
}

void Red::eliminarEnrutador(const string& id) {
    if (!routers.count(id)) {
        cout << "[!] Enrutador " << id << " no encontrado." << endl;
        return;
    }
    for (auto& par : routers) par.second.eliminarVecino(id);
    routers.erase(id);
    caminos.erase(id);
    recalcularTodo();
    cout << "[-] Enrutador " << id << " eliminado." << endl;
}
void Red::agregarEnlace(const string& a, const string& b, int costo) {
    if (!routers.count(a) || !routers.count(b)) {
        cout << "[!] Uno o ambos enrutadores no existen." << endl;
        return;
    }
    routers[a].agregarVecino(b, costo);
    routers[b].agregarVecino(a, costo);
    recalcularTodo();
    cout << "[+] Enlace " << a << " <-> " << b
         << " (costo=" << costo << ") agregado." << endl;
}

void Red::eliminarEnlace(const string& a, const string& b) {
    if (!routers.count(a) || !routers.count(b)) {
        cout << "[!] Uno o ambos enrutadores no existen." << endl;
        return;
    }
    routers[a].eliminarVecino(b);
    routers[b].eliminarVecino(a);
    recalcularTodo();
    cout << "[-] Enlace " << a << " <-> " << b << " eliminado." << endl;
}


void Red::mostrarCamino(const string& origen, const string& destino) const {
    if (!routers.count(origen) || !routers.count(destino)) {
        cout << "[!] Origen o destino no encontrado." << endl;
        return;
    }
    const auto& paths = caminos.at(origen);
    cout << "\nCamino de " << origen << " a " << destino << ": ";

    if (!paths.count(destino) || paths.at(destino).empty()) {
        cout << "No hay camino." << endl;
        return;
    }

    const vector<string>& camino = paths.at(destino);
    for (size_t i = 0; i < camino.size(); ++i) {
        if (i) cout << " -> ";
        cout << camino[i];
    }

    // Calcular costo sumando enlace a enlace
    int costo = 0;
    for (size_t i = 0; i + 1 < camino.size(); ++i)
        costo += routers.at(camino[i]).obtenerCostoVecino(camino[i + 1]);

    cout << "  Costo total: " << costo << endl;
}
void Red::mostrarTablaEnrutador(const string& id) {
    if (!routers.count(id)) {
        cout << "[!] Enrutador " << id << " no encontrado." << endl;
        return;
    }
    routers[id].mostrarVecinos();
    cout << endl;
    routers[id].mostrarTablaCostos();
}

void Red::mostrarTodasLasTablas() {
    for (auto& par : routers) {
        cout << "\n" << endl;
        par.second.mostrarVecinos();
        cout << endl;
        par.second.mostrarTablaCostos();
    }
}
void Red::mostrarMatrizCostos() const {
    vector<string> ids;
    for (auto& par : routers) ids.push_back(par.first);

    cout << "\n Matriz de costos minimos " << endl;
    cout << "\t";
    for (auto& id : ids) cout << id << "\t";
    cout << endl;

    for (auto& origen : ids) {
        cout << origen << "\t";
        for (auto& dest : ids) {
            if (origen == dest) { cout << "0\t"; continue; }
            const auto& paths = caminos.at(origen);
            if (!paths.count(dest) || paths.at(dest).empty()) {
                cout << "0\t";
            } else {
                const vector<string>& c = paths.at(dest);
                int total = 0;
                for (size_t i = 0; i + 1 < c.size(); ++i)
                    total += routers.at(c[i]).obtenerCostoVecino(c[i + 1]);
                cout << total << "\t";
            }
        }
        cout << endl;
    }
}


bool Red::cargarDesdeArchivo(const string& ruta) {
    ifstream f(ruta);
    if (!f.is_open()) {
        cout << "[!] No se pudo abrir: " << ruta << endl;
        return false;
    }
    string linea;
    while (getline(f, linea)) {
        if (linea.empty() || linea[0] == '#') continue;
        istringstream ss(linea);
        string tipo; ss >> tipo;
        if (tipo == "enrutador") {
            string id; ss >> id;
            routers[id] = Enrutador(id);
        } else if (tipo == "enlace") {
            string a, b; int c;
            ss >> a >> b >> c;
            if (routers.count(a) && routers.count(b)) {
                routers[a].agregarVecino(b, c);
                routers[b].agregarVecino(a, c);
            }
        }
    }
    recalcularTodo();
    cout << " Red cargada desde " << ruta << endl;
    return true;
}

void Red::mostrarEnrutadores() const {
    cout << "\nEnrutadores en la red: ";
    if (routers.empty()) {
        cout << "(ninguno)" << endl;
        return;
    }
    for (auto& par : routers) cout << par.first << " ";
    cout << endl;
}
bool Red::estaVacia() const {
    return routers.empty();
}

