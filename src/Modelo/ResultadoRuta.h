#ifndef RESULTADO_RUTA_H
#define RESULTADO_RUTA_H

#include "EstadoOperacion.h"

// Conserva una copia independiente del recorrido y su distancia total.
class ResultadoRuta
{
private:
    int origenId;
    int destinoId;
    int* ciudadesRecorridas;
    int cantidadCiudades;
    double distanciaTotal;

public:
    ResultadoRuta();
    ResultadoRuta(int origenId, int destinoId, const int* ids,
        int cantidad, double distancia);
    ~ResultadoRuta();
    ResultadoRuta(const ResultadoRuta& otro);
    ResultadoRuta& operator=(const ResultadoRuta& otro);

    int obtenerOrigenId() const;
    int obtenerDestinoId() const;
    int obtenerCantidadCiudades() const;
    double obtenerDistanciaTotal() const;
    EstadoOperacion consultarCiudadPorIndice(int indice, int& idSalida) const;
};

#endif
