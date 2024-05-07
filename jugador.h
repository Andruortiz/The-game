// jugador.h
#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
using namespace std;

class Jugador {
public:
    Jugador(const string& nombre);
    string obtenerEntrada();
    string obtenerNombre();
private:
    string nombre;
};

#endif // JUGADOR_H
