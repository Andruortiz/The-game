// jugador.cpp
#include "jugador.h"
#include <iostream>
using namespace std;

Jugador::Jugador(const string& nombre) : nombre(nombre) {}

string Jugador::obtenerEntrada() {
    string entrada;
    cout << nombre << ", es tu turno"<<endl<<"ingresa tu respuesta o ingresar 'pista' para obtener la primera letra de la palabra'"<<endl<< "o ingresa salir para terminar el juego:";
    cin >> entrada;
    return entrada;
}

string Jugador::obtenerNombre() {
    return nombre;
    }