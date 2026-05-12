#ifndef RED_H
#define RED_H

#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <climits>
#include "enrutador.h"

using namespace std;

class Red
{
private:
    map<string, Enrutador> routers;
    map<string, map<string, vector<string>>> caminos;

    void ruta_mas_corta(const string& origen);
    void recalcularTodo();

public:
    // Alta / baja de enrutadores
    void agregarEnrutador(const string& id);
    void eliminarEnrutador(const string& id);

    // Alta / baja de enlaces
    void agregarEnlace(const string& a, const string& b, int costo);
    void eliminarEnlace(const string& a, const string& b);

    // Cálculo y muestra de camino mínimo
    void mostrarCamino(const string& origen, const string& destino) const;

    // Impresión de tablas
    void mostrarTablaEnrutador(const string& id);
    void mostrarTodasLasTablas();
    void mostrarMatrizCostos() const;

    // Carga desde archivo
    bool cargarDesdeArchivo(const string& ruta);
};

#endif
