#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

struct Persona {
    int id;
    std::string nombre;
    float promedio;
};

using namespace std;

bool idExiste(int idBuscado) {
    ifstream archivo("personas.txt");
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string campo;
        getline(ss, campo, ',');
        int idArchivo = stoi(campo);
        if (idArchivo == idBuscado) {
            return true;
        }
    }
    return false;
}

void guardarPromedio(float array[], int& total, float promedio) {
    array[total] = promedio;
    total++;
}

void ordenarPersonasPorPromedio(Persona personas[], int total) {
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (personas[j].promedio < personas[j + 1].promedio) {
                Persona temp = personas[j];
                personas[j] = personas[j + 1];
                personas[j + 1] = temp;
            }
        }
    }
}

void sobrescribirArchivo(Persona personas[], int total) {
    ofstream archivo("personas.txt", ios::trunc);
    for (int i = 0; i < total; i++) {
        archivo << personas[i].id << "," << personas[i].nombre << "," << personas[i].promedio << "\n";
    }
    archivo.close();
}

void guardarEnArchivo(const Persona& persona) {
    ifstream archivoLectura("personas.txt");
    Persona personas[100];
    int total = 0;
    string linea;

    while (getline(archivoLectura, linea)) {
        stringstream ss(linea);
        string idStr, nombre, promedioStr;
        getline(ss, idStr, ',');
        getline(ss, nombre, ',');
        getline(ss, promedioStr, ',');
        Persona p;
        p.id = stoi(idStr);
        p.nombre = nombre;
        p.promedio = stof(promedioStr);
        personas[total++] = p;
    }

    personas[total++] = persona;
    archivoLectura.close();

    ordenarPersonasPorPromedio(personas, total);
    sobrescribirArchivo(personas, total);
}

void consultarPersona(int idBuscado) {
    ifstream archivo("personas.txt");
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string campo;
        getline(ss, campo, ',');
        int idArchivo = stoi(campo);
        if (idArchivo == idBuscado) {
            cout << "Datos encontrados:\nID NOMBRE PROMEDIO\n" << linea << endl;
            return;
        }
    }
    cout << "No se encontró una persona con ese ID.\n";
}

void modificarPersona(int idBuscado) {
    ifstream archivo("personas.txt");
    string linea;
    Persona persona;
    bool modificarNombre = false;
    bool modificarPromedio = false;

    cout << "¿Qué desea modificar?\n";
    cout << "1. Nombre\n";
    cout << "2. Promedio\n";
    cout << "3. Ambos\n";
    cout << "Seleccione opción: ";
    int opcionMod;
    cin >> opcionMod;
    cin.ignore();

    if (opcionMod == 1) modificarNombre = true;
    else if (opcionMod == 2) modificarPromedio = true;
    else if (opcionMod == 3) {
        modificarNombre = true;
        modificarPromedio = true;
    } else {
        cout << "Opción inválida. No se harán cambios.\n";
        archivo.close();
        return;
    }

    if (modificarNombre) {
        cout << "Ingrese el nuevo nombre: ";
        getline(cin, persona.nombre);
    }

    if (modificarPromedio) {
        cout << "Ingrese el nuevo promedio: ";
        while (true) {
            cin >> persona.promedio;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Entrada inválida. Ingresa un número entre 1 y 10: ";
                continue;
            }
            if (persona.promedio >= 1.0 && persona.promedio <= 10.0) {
                cin.ignore();
                break;
            } else {
                cout << "El promedio debe estar entre 1 y 10. Inténtalo de nuevo: ";
            }
        }
    }

    Persona personas[100];
    int total = 0;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string idStr, nombreActual, promedioStr;
        getline(ss, idStr, ',');
        getline(ss, nombreActual, ',');
        getline(ss, promedioStr, ',');
        int idArchivo = stoi(idStr);
        float promedioActual = stof(promedioStr);

        Persona p;
        p.id = idArchivo;

        if (idArchivo == idBuscado) {
            p.nombre = modificarNombre ? persona.nombre : nombreActual;
            p.promedio = modificarPromedio ? persona.promedio : promedioActual;
        } else {
            p.nombre = nombreActual;
            p.promedio = promedioActual;
        }

        personas[total++] = p;
    }

    archivo.close();

    ordenarPersonasPorPromedio(personas, total);
    sobrescribirArchivo(personas, total);

    cout << "Persona modificada correctamente y archivo reordenado por promedio.\n";
}

void eliminarPersona(int idBuscado) {
    ifstream archivo("personas.txt");
    Persona personas[100];
    int total = 0;
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string idStr, nombre, promedioStr;
        getline(ss, idStr, ',');
        getline(ss, nombre, ',');
        getline(ss, promedioStr, ',');
        int idArchivo = stoi(idStr);
        float promedio = stof(promedioStr);

        if (idArchivo != idBuscado) {
            Persona p;
            p.id = idArchivo;
            p.nombre = nombre;
            p.promedio = promedio;
            personas[total++] = p;
        }
    }

    archivo.close();

    ordenarPersonasPorPromedio(personas, total);
    sobrescribirArchivo(personas, total);

    cout << "Persona eliminada correctamente y archivo reordenado por promedio.\n";
}

int main() {
    Persona persona;
    float array[100];
    int total = 0;

    cout << "Bienvenido al sistema de gestión de personas.\n";
    cout << "Se guardarán los datos en el archivo 'personas.txt'.\n";

    while (true) {
        cout << "\n¿Deseas ingresar una persona? (si/no): ";
        string continuar;
        cin >> continuar;
        if (continuar == "si") {
            while (true) {
                cout << "Ingresa el ID (entero): ";
                cin >> persona.id;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Entrada inválida. El ID debe ser un número entero.\n";
                    continue;
                }

                if (idExiste(persona.id)) {
                    cout << "El ID ya existe. Intenta con uno diferente.\n";
                } else {
                    break;
                }
            }

            cout << "Ingresa el nombre: ";
            cin.ignore();
            getline(cin, persona.nombre);

            cout << "Ingresa el promedio: ";
            while (true) {
                cin >> persona.promedio;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Entrada inválida. Ingresa un número entre 1 y 10: ";
                    continue;
                }

                if (persona.promedio >= 1.0 && persona.promedio <= 10.0) {
                    guardarPromedio(array, total, persona.promedio);
                    guardarEnArchivo(persona);
                    break;
                } else {
                    cout << "El promedio debe estar entre 1 y 10. Inténtalo de nuevo: ";
                }
            }

            cout << "\nDatos ingresados:\n";
            cout << "ID: " << persona.id << endl;
            cout << "Nombre: " << persona.nombre << endl;
            cout << "Promedio: " << persona.promedio << endl;
            cout << "--------------------------\n";
        } else if (continuar == "no") {
            cout << "No se ingresarán más personas.\n";
            break;
        } else {
            cout << "Opción inválida. Por favor, ingresa 'si' o 'no'.\n";
        }
    }

    int opcion, idConsulta;

    cout << "Ahora puedes consultar, modificar o eliminar personas.\n";
    do {
        cout << "\n--- MENÚ ---\n";
        cout << "1. Consultar persona\n";
        cout << "2. Modificar persona\n";
        cout << "3. Eliminar persona\n";
        cout << "4. Salir\n";

        // Validar entrada de opción
        while (true) {
            cout << "Seleccione una opción: ";
            cin >> opcion;
            if (cin.fail()) {
                cin.clear(); // limpia el error
                cin.ignore(10000, '\n'); // descarta la entrada inválida
                cout << "Entrada inválida. Debe ingresar un número entero.\n";
            } else {
                break;
            }
        }

        if (opcion >= 1 && opcion <= 3) {
            while (true) {
                cout << "Ingrese el ID de la persona: ";
                cin >> idConsulta;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Entrada inválida. Debe ingresar un número entero.\n";
                    continue;
                }

                if (idExiste(idConsulta)) {
                    break;
                } else {
                    cout << "Ingrese uno que ya existe.\n";
                }
            }
        }

        if (opcion == 1) {
            consultarPersona(idConsulta);
        } else if (opcion == 2) {
            modificarPersona(idConsulta);
        } else if (opcion == 3) {
            eliminarPersona(idConsulta);
        } else if (opcion == 4) {
            cout << "Saliendo...\n";
        } else {
            cout << "Opción inválida. Por favor, intente de nuevo.\n";
        }

    } while (opcion != 4);

    return 0;
}

