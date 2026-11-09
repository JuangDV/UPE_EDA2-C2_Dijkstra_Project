#include "Conexion.h"

Conexion::Conexion()
    : origenId(0), destinoId(0), distancia(0), habilitada(false)
{
}

Conexion::Conexion(int origenId, int destinoId, double distancia, bool habilitada)
    : origenId(origenId), destinoId(destinoId), distancia(distancia),
      habilitada(habilitada)
{
}

int Conexion::obtenerOrigenId() const
{
    return origenId;
}

int Conexion::obtenerDestinoId() const
{
    return destinoId;
}

double Conexion::obtenerDistancia() const
{
    return distancia;
}

bool Conexion::estaHabilitada() const
{
    return habilitada;
}
