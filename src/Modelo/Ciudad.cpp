#include "Ciudad.h"

// Inicializa un valor auxiliar sin identificador asignado.
Ciudad::Ciudad() : id(0), nombre(""), x(0), y(0)
{
}

// Conserva los datos recibidos; el gestor valida su incorporación.
Ciudad::Ciudad(int id, const std::string& nombre, int x, int y)
    : id(id), nombre(nombre), x(x), y(y)
{
}

// Devuelve el identificador estable de la ciudad.
int Ciudad::obtenerId() const
{
    return id;
}

// Entrega una copia del nombre.
std::string Ciudad::obtenerNombre() const
{
    return nombre;
}

// Devuelve la coordenada horizontal del mapa original.
int Ciudad::obtenerX() const
{
    return x;
}

// Devuelve la coordenada vertical del mapa original.
int Ciudad::obtenerY() const
{
    return y;
}
