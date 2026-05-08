#include <iostream>
#include "enrutador.h"

using namespace std;

int main()
{
    Enrutador r("A");

    r.agregarVecino("B", 4);
    r.agregarVecino("C", 10);
    r.agregarVecino("D", 5);

    r.actualizarCosto("A", 0);
    r.actualizarCosto("B", 4);
    r.actualizarCosto("C", 10);
    r.actualizarCosto("D", 5);

    cout << "Identificador: " << r.getIdentificador() << endl << endl;

    r.mostrarVecinos();
    cout << endl;
    r.mostrarTablaCostos();

    return 0;
}