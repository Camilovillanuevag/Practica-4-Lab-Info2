#include <iostream>
#include "enrutador.h"
#include "red.h"
using namespace std;

int main()
{
        Red red;
        int opcion;
        do {
            cout << " MENÚ " << endl;
            cout << " 1. Agregar enrutador"   << endl;
            cout << " 2. Eliminar enrutador"  << endl;
            cout << " 3. Agregar enlace"      << endl;
            cout << " 4. Eliminar enlace"     << endl;
            cout << " 5. Ver camino minimo"   << endl;
            cout << " 6. Ver tabla de un enrutador" << endl;
            cout << " 7. Ver todas las tablas"      << endl;
            cout << " 8. Ver matriz de costos"      << endl;
            cout << " 9. Cargar desde archivo"      << endl;
            cout << " 0. Salir"               << endl;
            cout << "Opcion: ";
            cin >> opcion;

            if (opcion == 1) {
                string id;
                cout << "ID del enrutador: "; cin >> id;
                red.agregarEnrutador(id);

            } else if (opcion == 2) {
                string id;
                cout << "ID del enrutador: "; cin >> id;
                red.eliminarEnrutador(id);

            } else if (opcion == 3) {
                string a, b; int c;
                cout << "Enrutador A: "; cin >> a;
                cout << "Enrutador B: "; cin >> b;
                cout << "Costo: ";       cin >> c;
                red.agregarEnlace(a, b, c);

            } else if (opcion == 4) {
                string a, b;
                cout << "Enrutador A: "; cin >> a;
                cout << "Enrutador B: "; cin >> b;
                red.eliminarEnlace(a, b);

            } else if (opcion == 5) {
                string o, d;
                cout << "Origen: ";  cin >> o;
                cout << "Destino: "; cin >> d;
                red.mostrarCamino(o, d);

            } else if (opcion == 6) {
                string id;
                cout << "ID del enrutador: "; cin >> id;
                red.mostrarTablaEnrutador(id);

            } else if (opcion == 7) {
                red.mostrarTodasLasTablas();

            } else if (opcion == 8) {
                red.mostrarMatrizCostos();

            } else if (opcion == 9) {
                string ruta;
                cout << "Ruta del archivo: "; cin >> ruta;
                red.cargarDesdeArchivo(ruta);
            }

        } while (opcion != 0);
    }
