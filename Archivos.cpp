#include<iostream>
#include<conio.h>
#include<cstdlib>
#include<windows.h>
#include<locale.h> 
#include <fstream>


using namespace std;

void Clean (){
    	getch();
		system("cls");
		
	} 
	
// Funci�n para agregar un nuevo libro al archivo
void agregarLibro() {
    ofstream archivo("libros.txt", ios::app); // Abrimos el archivo en modo a�adir
    if (!archivo) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    string titulo, autor;
    int anio;

    cout << "Introduce el t�tulo del libro: ";
    getline(cin, titulo);
    cout << "Introduce el autor del libro: ";
    getline(cin, autor);
    cout << "Introduce el a�o de publicaci�n: ";
    cin >> anio;
    cin.ignore(); // Limpiamos el buffer

    archivo << titulo << "," << autor << "," << anio << endl; // Escribimos los datos en el archivo
    archivo.close();
    cout << "Libro agregado correctamente." << endl;
}

// Funci�n para mostrar todos los libros almacenados en el archivo
void mostrarLibros() {
    ifstream archivo("libros.txt");
    if (!archivo) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    string linea;
    cout << "Libros almacenados en el archivo:\n";
    while (getline(archivo, linea)) {
        cout << linea << endl; // Mostrar cada l�nea del archivo
    }

    archivo.close();
}

// Funci�n para buscar un libro por su t�tulo
void buscarLibro() {
    ifstream archivo("libros.txt");
    if (!archivo) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    string tituloABuscar, linea;
    cout << "Introduce el t�tulo del libro que deseas buscar: ";
    getline(cin, tituloABuscar);

    bool encontrado = false;
    while (getline(archivo, linea)) {
        if (linea.find(tituloABuscar) != string::npos) { // Si se encuentra el t�tulo en la l�nea
            cout << "Libro encontrado: " << linea << endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "Libro no encontrado." << endl;
    }

    archivo.close();
}

// Funci�n para actualizar los datos de un libro
void actualizarLibro() {
    ifstream archivo("libros.txt");
    if (!archivo) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    ofstream temp("temp.txt"); // Archivo temporal para guardar los datos actualizados
    if (!temp) {
        cout << "No se pudo crear el archivo temporal." << endl;
        return;
    }

    string tituloABuscar, linea, nuevoTitulo, nuevoAutor;
    int nuevoAnio;
    bool encontrado = false;

    cout << "Introduce el t�tulo del libro que deseas actualizar: ";
    getline(cin, tituloABuscar);

    while (getline(archivo, linea)) {
        if (linea.find(tituloABuscar) != string::npos && !encontrado) {
            cout << "Libro encontrado. Introduce los nuevos datos:\n";
            cout << "Nuevo t�tulo: ";
            getline(cin, nuevoTitulo);
            cout << "Nuevo autor: ";
            getline(cin, nuevoAutor);
            cout << "Nuevo a�o de publicaci�n: ";
            cin >> nuevoAnio;
            cin.ignore();

            temp << nuevoTitulo << "," << nuevoAutor << "," << nuevoAnio << endl; // Escribir los nuevos datos en el archivo temporal
            encontrado = true;
        } else {
            temp << linea << endl; // Copiar los libros no modificados
        }
    }

    archivo.close();
    temp.close();

    remove("libros.txt");        // Eliminar el archivo original
    rename("temp.txt", "libros.txt"); // Renombrar el archivo temporal

    if (encontrado) {
        cout << "Libro actualizado correctamente." << endl;
    } else {
        cout << "Libro no encontrado." << endl;
    }
}

int main() {
    int opcion;
    setlocale(LC_ALL,"");
	system("color 1f");

    do {
        cout << "\n--- Men� de la Biblioteca ---\n";
        cout << "1. Agregar libro\n";
        cout << "2. Mostrar libros\n";
        cout << "3. Buscar libro\n";
        cout << "4. Actualizar libro\n";
        cout << "5. Salir\n";
        cout << "Selecciona una opci�n: ";
        cin >> opcion;
        cin.ignore(); // Limpiar buffer

        switch (opcion) {
            case 1:
                agregarLibro();
                break;
            case 2:
                mostrarLibros();
                break;
            case 3:
                buscarLibro();
                break;
            case 4:
                actualizarLibro();
                break;
            case 5:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opci�n no v�lida." << endl;
        }
    } while (opcion != 5);

    return 0;
}
