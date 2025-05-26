#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

//Estructura para almacenar los datos de una persona
struct Persona {
    int id;
    std::string nombre;
    float promedio;
};

using namespace std;

//Funcion para verificar si un ID ya existe en el archivo
bool idExiste(int idBuscado) {
    ifstream archivo("personas.txt"); // Abrir el archivo en modo lectura
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string campo;
        getline(ss, campo, ','); // Funcion getline para obtener el ID
        int idArchivo = stoi(campo);
        if (idArchivo == idBuscado) {
            return true; // Si el ID existe, retorna true
        }
    }
    return false;
}

// Funcion para guardar el promedio en un array
void guardarPromedio(float array[], int& total, float promedio) {
    array[total] = promedio;
    total++;
}

// Funcion para ordenar las personas por promedio de forma descendente
void ordenarPersonasPorPromedio(Persona personas[], int total) {
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (personas[j].promedio < personas[j + 1].promedio) {
                Persona temp = personas[j]; // Intercambio de personas
                personas[j] = personas[j + 1]; // Asignación del siguiente elemento
                personas[j + 1] = temp; // Asignación del elemento temporal
            }
        }
    }
}

// Funcion para sobrescribir el archivo con los datos ordenados
void sobrescribirArchivo(Persona personas[], int total) {
    ofstream archivo("personas.txt", ios::trunc);
    for (int i = 0; i < total; i++) { // Iterar sobre el array de personas
        archivo << personas[i].id << "," << personas[i].nombre << "," << personas[i].promedio << "\n"; // Guardar datos en el archivo
    }
    archivo.close(); // Cerrar el archivo después de escribir
}

// Función para guardar una persona en el archivo

void guardarEnArchivo(const Persona& persona) {
    ifstream archivoLectura("personas.txt");// Abrir el archivo en modo lectura
    Persona personas[100];
    int total = 0;
    string linea;// Variable para almacenar cada línea leída
    // Leer el archivo línea por línea
    while (getline(archivoLectura, linea)) { // Leer cada línea del archivo
        stringstream ss(linea);
        string idStr, nombre, promedioStr;
        getline(ss, idStr, ',');
        getline(ss, nombre, ',');
        getline(ss, promedioStr, ',');
        Persona p;
        p.id = stoi(idStr); // Convertir el ID de string a entero
        p.nombre = nombre;
        p.promedio = stof(promedioStr);
        personas[total++] = p; // Agregar la persona al array
    }

    personas[total++] = persona;// Agregar la nueva persona al array
    archivoLectura.close();

    ordenarPersonasPorPromedio(personas, total);// Ordenar las personas por promedio
    sobrescribirArchivo(personas, total); // Sobrescribir el archivo con los datos ordenados
}

// Función para consultar una persona por ID
void consultarPersona(int idBuscado) {
    ifstream archivo("personas.txt"); // Abrir el archivo en modo lectura
    string linea; // Variable para almacenar cada línea leída
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string campo;
        getline(ss, campo, ',');
        int idArchivo = stoi(campo); // Convertir el ID de string a entero
        if (idArchivo == idBuscado) {
            cout << "Datos encontrados:\nID NOMBRE PROMEDIO\n" << linea << endl;
            return;
        }
    }
    cout << "No se encontró una persona con ese ID.\n";
}

// Función para modificar una persona por ID
void modificarPersona(int idBuscado) {
    ifstream archivo("personas.txt");
    string linea;
    Persona persona;
    bool modificarNombre = false; // Indica si se modificará el nombre
    bool modificarPromedio = false; // Indica si se modificará el promedio
    //menu de modificación
    cout << "¿Qué desea modificar?\n";
    cout << "1. Nombre\n";
    cout << "2. Promedio\n";
    cout << "3. Ambos\n";
    cout << "Seleccione opción: ";
    int opcionMod;
    cin >> opcionMod;
    cin.ignore();
    // Validar entrada de opción
    if (opcionMod == 1) modificarNombre = true;
    else if (opcionMod == 2) modificarPromedio = true; // Indica si se modificará el promedio
    else if (opcionMod == 3) {
        modificarNombre = true; // Indica que se modificará el nombre
        modificarPromedio = true; // Indica que se modificarán ambos campos
    } else {
        cout << "Opción inválida. No se harán cambios.\n";
        archivo.close(); // Cerrar el archivo antes de salir
        return;
    }
    // Buscar la persona por ID
    if (modificarNombre) {
        cout << "Ingrese el nuevo nombre: ";
        getline(cin, persona.nombre);// Leer el nombre completo
    }
    // Validar entrada del promedio

    if (modificarPromedio) {
        cout << "Ingrese el nuevo promedio: ";
        while (true) {
            cin >> persona.promedio;
            if (cin.fail()) { // Validar que la entrada sea un número
                // Si la entrada es inválida, limpiar el estado de cin y descartar la entrada
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Entrada inválida. Ingresa un número entre 1 y 10: ";
                continue;
            }
            if (persona.promedio >= 1.0 && persona.promedio <= 10.0) {
                cin.ignore(); // Limpiar el buffer de entrada
                break;
            } else {
                cout << "El promedio debe estar entre 1 y 10. Inténtalo de nuevo: ";
            }
        }
    }

    Persona personas[100];
    int total = 0;
    // Leer el archivo y modificar la persona
    // Si se encuentra la persona, se modifica su nombre y/o promedio
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string idStr, nombreActual, promedioStr;
        getline(ss, idStr, ','); // Obtener el ID
        getline(ss, nombreActual, ',');
        getline(ss, promedioStr, ',');
        int idArchivo = stoi(idStr); // Convertir el ID de string a entero
        float promedioActual = stof(promedioStr); // Convertir el promedio de string a float

        Persona p; // Crear una nueva persona
        p.id = idArchivo; // Asignar el ID de la persona leída

        // Si el ID coincide con el buscado, se modifica el nombre y promedio
        if (idArchivo == idBuscado) { 
            p.nombre = modificarNombre ? persona.nombre : nombreActual;
            p.promedio = modificarPromedio ? persona.promedio : promedioActual;
        } else {
            p.nombre = nombreActual;
            p.promedio = promedioActual;
        }

        personas[total++] = p; // Agregar la persona al array
    }

    archivo.close();

    ordenarPersonasPorPromedio(personas, total); // Ordenar las personas por promedio
    sobrescribirArchivo(personas, total); // Sobrescribir el archivo con los datos actualizados

    cout << "Persona modificada correctamente y archivo reordenado por promedio.\n";
}

// Función para eliminar una persona por ID
void eliminarPersona(int idBuscado) {
    ifstream archivo("personas.txt");
    Persona personas[100];
    int total = 0;
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea); // Leer cada línea del archivo
        string idStr, nombre, promedioStr;
        getline(ss, idStr, ','); // Obtener el ID
        getline(ss, nombre, ',');
        getline(ss, promedioStr, ',');
        int idArchivo = stoi(idStr);
        float promedio = stof(promedioStr);
        // Si el ID no coincide con el buscado, se agrega al array
        if (idArchivo != idBuscado) {
            Persona p;
            p.id = idArchivo;
            p.nombre = nombre;
            p.promedio = promedio;
            personas[total++] = p;
        }
    }

    archivo.close(); // Cerrar el archivo después de leer

    ordenarPersonasPorPromedio(personas, total); // Ordenar las personas por promedio
    sobrescribirArchivo(personas, total); // Sobrescribir el archivo con los datos actualizados

    cout << "Persona eliminada correctamente y archivo reordenado por promedio.\n";
}

int main() {
    Persona persona;
    float array[100];
    int total = 0;
    // Mensaje de bienvenida
    cout << "Bienvenido al sistema de gestión de personas.\n";
    cout << "Se guardarán los datos en el archivo 'personas.txt'.\n";
    // Bucle para ingresar personas
    while (true) {
        cout << "\n¿Deseas ingresar una persona? (si/no): ";
        string continuar; // Variable para continuar o no
        cin >> continuar;
        if (continuar == "si") { // Pregunta para continuar
            while (true) { // Validar entrada del ID
                cout << "Ingresa el ID (entero): ";
                cin >> persona.id;
                if (cin.fail()) { // Validar que la entrada sea un número entero
                    cin.clear();// Limpiar el estado de cin
                    cin.ignore(1000, '\n');
                    cout << "Entrada inválida. El ID debe ser un número entero.\n";
                    continue;
                }

                if (idExiste(persona.id)) { // Verificar si el ID ya existe
                    cout << "El ID ya existe. Intenta con uno diferente.\n";
                } else {
                    break; // Si el ID no existe, salir del bucle
                }
            }

            cout << "Ingresa el nombre: ";
            cin.ignore(); // Limpiar el buffer de entrada
            getline(cin, persona.nombre); // Leer el nombre completo

            cout << "Ingresa el promedio: ";
            while (true) {
                cin >> persona.promedio;
                if (cin.fail()) { // Validar que la entrada sea un número
                    cin.clear();
                    cin.ignore(1000, '\n'); 
                    cout << "Entrada inválida. Ingresa un número entre 1 y 10: ";
                    continue;// Si la entrada es inválida, limpiar el estado de cin y descartar la entrada
                }

                if (persona.promedio >= 1.0 && persona.promedio <= 10.0) { // Validar que el promedio esté en el rango correcto
                    guardarPromedio(array, total, persona.promedio); // Guardar el promedio en el array
                    guardarEnArchivo(persona);
                    break;
                } else {
                    cout << "El promedio debe estar entre 1 y 10. Inténtalo de nuevo: ";
                }
            }
            // Mostrar los datos ingresados
            cout << "\nDatos ingresados:\n";
            cout << "ID: " << persona.id << endl;
            cout << "Nombre: " << persona.nombre << endl;
            cout << "Promedio: " << persona.promedio << endl;
            cout << "--------------------------\n";

        } else if (continuar == "no") {
            cout << "No se ingresarán más personas.\n";
            break; // Salir del bucle
        } else {
            cout << "Opción inválida. Por favor, ingresa 'si' o 'no'.\n";
        }
    }

    int opcion, idConsulta;// Variable para almacenar la opción del menú y el ID a consultar

    cout << "Ahora puedes consultar, modificar o eliminar personas.\n";
    do {
        // Mostrar el menú de opciones
        cout << "\n--- MENÚ ---\n";
        cout << "1. Consultar persona\n";
        cout << "2. Modificar persona\n";
        cout << "3. Eliminar persona\n";
        cout << "4. Salir\n";

        // Validar entrada de opción
        while (true) {
            cout << "Seleccione una opción: ";
            cin >> opcion;
            if (cin.fail()) { // Validar que la entrada sea un número entero
                cin.clear(); // limpia el error
                cin.ignore(10000, '\n'); // descarta la entrada inválida
                cout << "Entrada inválida. Debe ingresar un número entero.\n";
            } else {
                break;
            }
        }
        // Validar que la opción esté en el rango correcto
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

                if (idExiste(idConsulta)) { // Verificar si el ID existe
                    break;
                } else { // Si el ID no existe, solicitar uno nuevo
                    cout << "Ingrese uno que ya existe.\n";
                }
            }
        }
        // Validar que la opción sea válida 

        if (opcion == 1) {
            consultarPersona(idConsulta); // Consultar persona por ID
        } else if (opcion == 2) {
            modificarPersona(idConsulta); // Modificar persona por ID
        } else if (opcion == 3) {
            eliminarPersona(idConsulta); // Eliminar persona por ID
        } else if (opcion == 4) {
            cout << "Saliendo...\n";
        } else {
            cout << "Opción inválida. Por favor, intente de nuevo.\n";
        }

    } while (opcion != 4); // Salir del bucle si la opción es 4

    return 0;
}

