#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <iostream>
#include <string>
#include <map>

using namespace std;

class Enrutador
{
private:
    string identificador;

    map<string, int> vecinos;
    map<string, int> tablaCostos;

public:
    Enrutador();
    Enrutador(const string& id);

    string getIdentificador() const;

    void agregarVecino(const string& vecino, int costo);
    void eliminarVecino(const string& vecino);

    bool tieneVecino(const string& vecino) const;
    int obtenerCostoVecino(const string& vecino) const;

    map<string, int> getVecinos() const;

    void actualizarCosto(const string& destino, int costo);
    void limpiarTablaCostos();

    void mostrarVecinos() const;
    void mostrarTablaCostos() const;
};

#endif