#ifndef CONEXION_H
#define CONEXION_H

// Representa una conexión dirigida entre dos ciudades.
class Conexion
{
private:
    int origenId;
    int destinoId;
    double distancia;
    bool habilitada;

public:
    Conexion();
    Conexion(int origenId, int destinoId, double distancia, bool habilitada);

    int obtenerOrigenId() const;
    int obtenerDestinoId() const;
    double obtenerDistancia() const;
    bool estaHabilitada() const;
};

#endif
