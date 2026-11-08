#ifndef CIUDAD_H
#define CIUDAD_H

#include <string>

// Representa una ciudad y su posición sobre el mapa original.
class Ciudad
{
private:
    int id;
    std::string nombre;
    int x;
    int y;

public:
    Ciudad();
    Ciudad(int id, const std::string& nombre, int x, int y);

    int obtenerId() const;
    std::string obtenerNombre() const;
    int obtenerX() const;
    int obtenerY() const;
};

#endif
