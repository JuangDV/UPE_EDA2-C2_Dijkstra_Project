#ifndef REGISTRO_RUTA_H
#define REGISTRO_RUTA_H

#include "EstadoOperacion.h"
#include <string>

// Conserva los datos de una ruta tal como eran al calcularla.
class RegistroRuta
{
private:
    std::string fechaHora;
    int* idsCiudades;
    std::string* nombresCiudades;
    double* distanciasTramos;
    int cantidadCiudades;
    double distanciaTotal;

public:
    RegistroRuta();
    RegistroRuta(const std::string& fechaHora, const int* idsCiudades,
        const std::string* nombresCiudades, const double* distanciasTramos,
        int cantidadCiudades, double distanciaTotal);
    ~RegistroRuta();
    RegistroRuta(const RegistroRuta& otro);
    RegistroRuta& operator=(const RegistroRuta& otro);

    std::string obtenerFechaHora() const;
    int obtenerCantidadCiudades() const;
    double obtenerDistanciaTotal() const;
    EstadoOperacion consultarCiudadPorIndice(int indice, int& idSalida,
        std::string& nombreSalida) const;
    EstadoOperacion consultarDistanciaTramo(int indice, double& salida) const;
};

#endif
