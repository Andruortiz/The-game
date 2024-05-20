#include "juego.h"
#include "jugador.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

string Juego::palabraSeleccionada;
string Juego::palabraobtenida;
int Juego::puntuacionJugador;
int Juego::puntuacionMaquina;
vector<Juego::PalabraDescripcion> Juego::palabras;

void Juego::registrar(const string& nombre, int puntaje) {
    fstream file;
    file.open("frases.txt", ios::out | ios::app);

    if (!file.is_open()) {
        cout << "El archivo no se abrio, error" << endl;
        return;
    }
    file << nombre_jugador << " " << puntaje << endl;
    file.close();
}

void Juego::cargarPalabrasDesdeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir los datos de las palabras" << endl;
        cout << "Ruta del archivo: " << nombreArchivo << endl; // Imprimir la ruta del archivo
        return;
    }
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string palabra, descripcion;

        if (getline(ss, palabra, '|') && getline(ss, descripcion)) {
            palabras.push_back({palabra, descripcion});
        }
    }
    archivo.close();
}

void Juego::iniciar() {
    cout << "Bienvenido al juego de adivina la palabra!" << endl;
    cout<<"ingresa tu nombre: "<<endl;
    cin>>nombre_jugador;
    // Cargar palabras desde el archivo
    cargarPalabrasDesdeArchivo("palabras.txt");

    puntuacionJugador = 0;
    puntuacionMaquina = 0;

    srand(time(nullptr));

    while (true) {
        palabraobtenida = obtenerPalabra();
        palabraSeleccionada = obtenerDescripcionAleatoria();
        cout << "Definicion de la palabra: " << palabraSeleccionada << endl;

        bool seProporcionoPista = false;
        auto inicio = chrono::steady_clock::now(); // Inicio del contador de tiempo

        while (true) {
            Jugador jugador(nombre_jugador);
            string entrada;
            while (true) {
                entrada = jugador.obtenerEntrada();
                if (entrada != "") break;
            }

            auto fin = chrono::steady_clock::now(); // Fin del contador de tiempo
            auto duracion = chrono::duration_cast<chrono::seconds>(fin - inicio).count(); // Duración en segundos

            if (entrada == "salir") {
                cout << "Gracias por jugar!" << endl;
                return;
            }

            if (duracion > 35) {
                cout << "¡Demasiado tiempo! Has perdido." << endl;
                puntuacionJugador = max(0, puntuacionJugador - 2);
                mostrarPuntuacion();
                perder();
                break;
            } else if (duracion > 30) {
                cout << "Demasiado tiempo! Pierdes 2 puntos." << endl;
                puntuacionJugador = max(0, puntuacionJugador - 2);
                mostrarPuntuacion();
            } else if (duracion > 20) {
                cout << "Demasiado tiempo! Pierdes 1 punto." << endl;
                puntuacionJugador = max(0, puntuacionJugador - 1);
                mostrarPuntuacion();
            }

            if (entrada == "pista") {
                cout << "Pista: la primera letra de la palabra es " << obtenerPista() << endl;
                seProporcionoPista = true;
                continue;
            }

            bool respuestaCorrecta = verificarPalabra(entrada);
            actualizarPuntuacion("Jugador 1", respuestaCorrecta, duracion);

            if (respuestaCorrecta) {
                cout << "Correcto! Has deletreado la palabra correctamente." << endl;
            } else {
                cout << "Incorrecto! La palabra era " << palabraobtenida << endl;
            }

            mostrarPuntuacion();
            perder();

            seProporcionoPista = false;
            break;
        }
    }
}

string Juego::obtenerPalabra() {
    return palabras[rand() % palabras.size()].palabra;
}

string Juego::obtenerDescripcionAleatoria() {
    palabraSeleccionada = palabras[rand() % palabras.size()].descripcion;
    return palabraSeleccionada;
}

bool Juego::verificarPalabra(const string& palabra) {
    for (const auto& pd : palabras) {
        if (pd.descripcion == palabraSeleccionada) {
            return pd.palabra == palabra;
        }
    }
    return false;
}

void Juego::mostrarMensaje(const string& mensaje) {
    cout << mensaje << endl;
}

void Juego::actualizarPuntuacion(const string& jugador, bool respuestaCorrecta, int duracion) {
    if (jugador == "Jugador 1") {
        if (respuestaCorrecta) {
            cout << " Correcto! Has adivinado la palabra correctamente." << endl;
            if (duracion <= 10) {
                puntuacionJugador += 7;
            } else if (duracion <= 15) {
                puntuacionJugador += 6;
            } else if (duracion <= 30) {
                puntuacionJugador += 5;
            }
        } else {
            cout << " Incorrecto! La palabra era " << palabraobtenida << endl;
            puntuacionJugador--; // Restar puntos por respuesta incorrecta
        }
    } else if (jugador == "Maquina") {
        if (respuestaCorrecta) {
            cout << " Correcto! La maquina ha adivinado la palabra correctamente." << endl;
            puntuacionMaquina += 5;
        } else {
            cout << " Incorrecto! La palabra era " << palabraSeleccionada << endl;
        }
    }
//jsjsjssd
    if (!respuestaCorrecta) {
        mostrarPuntuacion();
        perder();
    }
}

void Juego::mostrarPuntuacion() {
    cout << "Puntuacion de"<<nombre_jugador<<": "<< puntuacionJugador << endl;
    cout << "Puntuacion de la Maquina: " << puntuacionMaquina << endl;
}

void Juego::perder() {
    if (puntuacionJugador <= 0) {
        cout << "Perdiste, tu puntuacion es cero o negativa." << endl;
        cout << "Empezando de nuevo..." << endl;
        puntuacionJugador = 1;
        puntuacionMaquina = 1;
    }
}

string Juego::obtenerPista() {
    for (const auto& pd : palabras) {
        if (pd.descripcion == palabraSeleccionada) {
            return pd.palabra.substr(0, 1);
        }
    }
    return "";
}

string Juego::obtenerEntradaMaquina() {
    return palabras[rand() % palabras.size()].palabra;
}
