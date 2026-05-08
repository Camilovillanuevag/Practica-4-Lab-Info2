#include "enrutador.h"

Enrutador::Enrutador()
{
    identificador = "";
}

Enrutador::Enrutador(const string& id)
{
    identificador = id;
}

string Enrutador::getIdentificador() const
{
    return identificador;
}

void Enrutador::agregarVecino(const string& vecino, int costo)
{
    if (costo <= 0) {
        cout << "Error: el costo debe ser positivo." << endl;
        return;
    }

    vecinos[vecino] = costo;
}

void Enrutador::eliminarVecino(const string& vecino)
{
    vecinos.erase(vecino);
}

bool Enrutador::tieneVecino(const string& vecino) const
{
    return vecinos.find(vecino) != vecinos.end();
}

int Enrutador::obtenerCostoVecino(const string& vecino) const
{
    auto it = vecinos.find(vecino);

    if (it != vecinos.end()) {
        return it->second;
    }

    return -1;
}

map<string, int> Enrutador::getVecinos() const
{
    return vecinos;
}

void Enrutador::actualizarCosto(const string& destino, int costo)
{
    tablaCostos[destino] = costo;
}

void Enrutador::limpiarTablaCostos()
{
    tablaCostos.clear();
}

void Enrutador::mostrarVecinos() const
{
    cout << "Vecinos de " << identificador << ":" << endl;

    if (vecinos.empty()) {
        cout << "  No tiene vecinos directos." << endl;
        return;
    }

    for (const auto& par : vecinos) {
        cout << "  " << par.first << " con costo " << par.second << endl;
    }
}

void Enrutador::mostrarTablaCostos() const
{
    cout << "Tabla de costos de " << identificador << ":" << endl;

    if (tablaCostos.empty()) {
        cout << "  No hay costos registrados." << endl;
        return;
    }

    for (const auto& par : tablaCostos) {
        cout << "  Destino: " << par.first << " | Costo: " << par.second << endl;
    }
}