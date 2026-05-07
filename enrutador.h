#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class Enrutador
{
private:
    string identificador;
    map<string, int> vecinos;
    map<string, int> tablaCostos;
    map<string, vector<string>> tablaCaminos;

public:
    Enrutador();
    Enrutador(const string& id);

    string getIdentificador() const;

    void agregarVecino(const string& vecino, int costo);
    void eliminarVecino(const string& vecino);

    bool tieneVecino(const string& vecino) const;
    int obtenerCostoVecino(const string& vecino) const;

    map<string, int> getVecinos() const;

    void actualizarRuta(const string& destino, int costo, const vector<string>& camino);
    void limpiarTabla();

    bool existeRutaA(const string& destino) const;
    int obtenerCostoADestino(const string& destino) const;
    vector<string> obtenerCaminoADestino(const string& destino) const;

    void mostrarVecinos() const;
    void mostrarTablaEnrutamiento() const;
};

#endif