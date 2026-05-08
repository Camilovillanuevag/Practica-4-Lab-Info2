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

void Enrutador::actualizarRuta(const string& destino, int costo, const vector<string>& camino)
{
    tablaCostos[destino] = costo;
    tablaCaminos[destino] = camino;
}

void Enrutador::limpiarTabla()
{
    tablaCostos.clear();
    tablaCaminos.clear();
}

bool Enrutador::existeRutaA(const string& destino) const
{
    return tablaCostos.find(destino) != tablaCostos.end();
}

int Enrutador::obtenerCostoADestino(const string& destino) const
{
    auto it = tablaCostos.find(destino);

    if (it != tablaCostos.end()) {
        return it->second;
    }

    return -1;
}

vector<string> Enrutador::obtenerCaminoADestino(const string& destino) const
{
    auto it = tablaCaminos.find(destino);

    if (it != tablaCaminos.end()) {
        return it->second;
    }

    return vector<string>();
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

void Enrutador::mostrarTablaEnrutamiento() const
{
    cout << "Tabla de enrutamiento de " << identificador << endl;
    cout << "Destino\tCosto\tCamino" << endl;

    if (tablaCostos.empty()) {
        cout << "No hay rutas calculadas." << endl;
        return;
    }

    for (const auto& par : tablaCostos) {
        string destino = par.first;
        int costo = par.second;

        cout << destino << "\t" << costo << "\t";

        auto itCamino = tablaCaminos.find(destino);

        if (itCamino != tablaCaminos.end()) {
            const vector<string>& camino = itCamino->second;

            for (size_t i = 0; i < camino.size(); i++) {
                cout << camino[i];

                if (i + 1 < camino.size()) {
                    cout << " -> ";
                }
            }
        }

        cout << endl;
    }
}