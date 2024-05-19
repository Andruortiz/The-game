//juego.h
#ifndef JUEGO_H_INCLUDE
#define JUEGO_H_INCLUDE


#include <string>
#include <vector>
using namespace std;

class Juego {
public:
    struct PalabraDescripcion {
        string palabra;
        string descripcion;
    };

    static vector<PalabraDescripcion> palabras;
    static string palabraSeleccionada;
    static string palabraobtenida;
    static int puntuacionJugador;
    static int puntuacionMaquina;

    void registrar(const std::string& nombre, int puntaje);
    void iniciar();
    string obtenerDescripcionAleatoria();
    string obtenerPalabra();
    bool verificarPalabra(const string& palabra);
    void mostrarMensaje(const string& mensaje);
    void actualizarPuntuacion(const string& jugador, bool respuestaCorrecta, int duracion);
    void mostrarPuntuacion();
    void perder();
    string obtenerPista();
    string obtenerEntradaMaquina();
};

#endif // JUEGO_H
