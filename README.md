INTEGRANTES
Fredi Antonio Orozco Orozco
Carlos Manuel Valdéz Escobar
Jorge Gabriel de León Barrios
Gadyel Santiago Navarro Rivera


Documentación del Proyecto Final
Este proyecto es un sistema de gestión de personas que permite realizar operaciones como agregar, consultar, modificar y eliminar personas almacenadas en un archivo de 
texto llamado personas.txt. A continuación, se explica cada parte del código de manera sencilla.

Documentación del Proyecto Final
Este proyecto es un sistema de gestión de personas que permite realizar operaciones como agregar, consultar, modificar y eliminar personas almacenadas 
en un archivo de texto llamado personas.txt. A continuación, se explica cada parte del código de manera sencilla.

struct Persona {
    int id;
    std::string nombre;
    float promedio;
};


2.1 Verificar si un ID ya existe
La función idExiste busca en el archivo personas.txt si un ID ya está registrado. Si lo encuentra, devuelve true; de lo contrario, devuelve false.
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

2.2 Guardar un promedio
La función guardarPromedio almacena un promedio en un arreglo y actualiza el contador total.


void guardarPromedio(float array[], int& total, float promedio) {
    array[total] = promedio;
    total++;
}


2.3 Ordenar personas por promedio
La función ordenarPersonasPorPromedio organiza un arreglo de personas en orden descendente según su promedio.

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



2.5 Guardar una nueva persona
La función guardarEnArchivo agrega una nueva persona al archivo, ordena los datos por promedio y sobrescribe el archivo



2.6 Consultar una persona
La función consultarPersona busca una persona por su ID en el archivo y muestra sus datos si se encuentra.

2.7 Modificar una persona
La función modificarPersona permite cambiar el nombre, el promedio o ambos de una persona identificada por su ID.

2.8 Eliminar una persona
La función eliminarPersona elimina a una persona del archivo según su ID y reordena los datos.


3. Menú Principal
El programa inicia mostrando un menú que permite al usuario:

Consultar una persona.
Modificar una persona.
Eliminar una persona.
Salir del programa.
El menú valida las entradas del usuario y realiza las operaciones correspondientes.


do {
    cout << "\n--- MENÚ ---\n";
    cout << "1. Consultar persona\n";
    cout << "2. Modificar persona\n";
    cout << "3. Eliminar persona\n";
    cout << "4. Salir\n";
    cout << "Seleccione una opción: ";
    cin >> opcion;

    if (opcion >= 1 && opcion <= 3) {
        cout << "Ingrese el ID de la persona: ";
        cin >> idConsulta;
        if (idExiste(idConsulta)) {
            if (opcion == 1) consultarPersona(idConsulta);
            else if (opcion == 2) modificarPersona(idConsulta);
            else if (opcion == 3) eliminarPersona(idConsulta);
        } else {
            cout << "El ID no existe.\n";
        }
    } else if (opcion == 4) {
        cout << "Saliendo...\n";
    } else {
        cout << "Opción inválida.\n";
    }
} while (opcion != 4);




4. Validaciones
El programa incluye validaciones para:

Asegurarse de que el ID sea un número entero.
Verificar que el promedio esté entre 1.0 y 10.0.
Confirmar que las opciones del menú sean válidas.


5. Archivo personas.txt
El archivo personas.txt almacena los datos de las personas en el formato:


ID,NOMBRE,PROMEDIO


6. Flujo del Programa
El usuario puede agregar personas al archivo.
Luego, puede consultar, modificar o eliminar personas mediante el menú.
Los datos se ordenan automáticamente por promedio cada vez que se realizan cambios.


Notas Finales
Este proyecto es ideal para aprender sobre:

Manejo de archivos en C++.
Validación de entradas del usuario.
Ordenamiento de datos.
Uso de estructuras y funciones.
