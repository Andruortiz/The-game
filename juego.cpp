#include "juego.h"
#include "jugador.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <vector>
using namespace std;

string Juego::palabraSeleccionada;
string Juego::palabraobtenida;
int Juego::puntuacionJugador;
int Juego::puntuacionMaquina;

void Juego::registrar(const string& nombre, int puntaje){
    fstream file;
    file.open("frases.txt",ios::out | ios::app);

    if(!file.is_open()){
    cout<<"el archivo no se abrio, error";
    return;
    }
    file<<nombre<<" "<<puntaje<<endl;
    file.close();
}

vector<Juego::PalabraDescripcion> Juego::palabras = {
        {"mercurio", "El planeta mas cercano al Sol."},
        {"venus", "El segundo planeta del sistema solar."},
        {"tierra", "Nuestro hogar, el unico planeta conocido habitado por vida."},
        {"marte", "Conocido como el planeta rojo, tiene una atmosfera delgada y polvorienta."},
        {"jupiter", "El planeta mas grande del sistema solar, conocido por su Gran Mancha Roja."},
        {"saturno", "Con sus impresionantes anillos, es uno de los planetas más reconocibles."},
        {"urano", "Un planeta gigante de hielo y gas."},
        {"neptuno", "El planeta mas alejado del Sol, conocido por sus intensos vientos."},
        {"pluton", "Un planeta enano en el borde de nuestro sistema solar, anteriormente clasificado como el noveno planeta."},
        {"ceres", "El planeta enano más grande del cinturon de asteroides entre Marte y Jupiter."},
        {"eris", "Un planeta enano en el cinturon de Kuiper, cuyo descubrimiento llevo a la redefinicion de lo que es un planeta."}
};

void Juego::iniciar() {
    cout << "Bienvenido al juego de adivina la palabra!" << endl;
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
            Jugador jugador("Jugador 1");
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
                cout << "Incorrecto! La palabra era " << palabraSeleccionada << endl;
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

    if (!respuestaCorrecta) {
        mostrarPuntuacion();
        perder();
    }
}


void Juego::mostrarPuntuacion() {
    cout << "Puntuacion del Jugador 1: " << puntuacionJugador << endl;
    cout << "Puntuacion de la Maquina: " << puntuacionMaquina << endl;
}

void Juego::perder() {
    if (puntuacionJugador <= 0) {
        cout << "Perdiste, tu puntuacion es cero o negativa." << endl;
        cout << "Empezando de nuevo..." << endl;
        puntuacionJugador = 5;
        puntuacionMaquina = 0;
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
