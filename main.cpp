#include <iostream>
#include "enrutador.h"
#include "red.h"
using namespace std;

int main()
{
        Red red;
        int opcion;
        do {
            cout << " MENU " << endl;
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
            if (!(cin >> opcion)) {
                cin.clear();
                cin.ignore(1000, '\n');
                throw invalid_argument("La opcion debe ser un numero entero.");
            }

            if (opcion == 1) {
                string id;
                cout << "ID del enrutador: "; cin >> id;
                if (id.empty()) throw invalid_argument("El ID no puede estar vacio.");
                red.agregarEnrutador(id);

            } else if (opcion == 2) {
                red.mostrarEnrutadores();
                if (red.estaVacia()) throw runtime_error("No hay enrutadores en la red.");
                string id;
                cout << "ID del enrutador: "; cin >> id;
                red.eliminarEnrutador(id);

            } else if (opcion == 3) {
                red.mostrarEnrutadores();
                if (red.estaVacia()) throw runtime_error("No hay enrutadores. Agregue al menos dos primero.");
                string a, b; int c;
                cout << "Enrutador A: "; cin >> a;
                cout << "Enrutador B: "; cin >> b;
                cout << "Costo: ";       cin >> c;
                if (!(cin >> c)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    throw invalid_argument("El costo debe ser un numero entero positivo.");
                }
                if (c <= 0) throw invalid_argument("El costo debe ser mayor que cero.");
                red.agregarEnlace(a, b, c);

            } else if (opcion == 4) {
                red.mostrarEnrutadores();
                if (red.estaVacia()) throw runtime_error("No hay enrutadores en la red.");
                string a, b;
                cout << "Enrutador A: "; cin >> a;
                cout << "Enrutador B: "; cin >> b;
                red.eliminarEnlace(a, b);

            } else if (opcion == 5) {
                red.mostrarEnrutadores();
                if (red.estaVacia()) throw runtime_error("No hay enrutadores en la red.");
                string o, d;
                cout << "Origen: ";  cin >> o;
                cout << "Destino: "; cin >> d;
                if (o == d) throw invalid_argument("El origen y el destino no pueden ser iguales.");
                red.mostrarCamino(o, d);

            } else if (opcion == 6) {
                red.mostrarEnrutadores();
                if (red.estaVacia()) throw runtime_error("No hay enrutadores en la red.");
                string id;
                cout << "ID del enrutador: "; cin >> id;
                red.mostrarTablaEnrutador(id);

            } else if (opcion == 7) {
                if (red.estaVacia()) throw runtime_error("No hay enrutadores en la red.");
                red.mostrarTodasLasTablas();

            } else if (opcion == 8) {
                if (red.estaVacia()) throw runtime_error("No hay enrutadores en la red.");
                red.mostrarMatrizCostos();

            } else if (opcion == 9) {
                string ruta;
                cout << "Ruta del archivo: "; cin >> ruta;
                if (!red.cargarDesdeArchivo(ruta))
                    throw runtime_error("No se pudo cargar el archivo");

             } else if (opcion != 0) {
              throw out_of_range("Opcion invalida. Elija entre 0 y 9.");
         }
      } while (opcion != 0);
    }
