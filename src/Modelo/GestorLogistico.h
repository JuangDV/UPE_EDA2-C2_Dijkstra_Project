#ifndef GESTOR_LOGISTICO_H
#define GESTOR_LOGISTICO_H

#include "Ciudad.h"
#include "EstadoOperacion.h"

// Administra ciudades, dimensiones e identificadores de la red.
class GestorLogistico
{
private:
    Ciudad* ciudades;
    int cantidadCiudades;
    int siguienteId;
    int anchoMapa;
    int altoMapa;

    int buscarIndiceCiudad(int id) const;
    bool nombreValido(const std::string& nombre) const;
    bool coordenadasValidas(int x, int y) const;

public:
    GestorLogistico();
    ~GestorLogistico();
    GestorLogistico(const GestorLogistico& otro);
    GestorLogistico& operator=(const GestorLogistico& otro);

    EstadoOperacion configurarMapa(int ancho, int alto);

    int obtenerAnchoMapa() const;
    int obtenerAltoMapa() const;
    int obtenerSiguienteId() const;
    int obtenerCantidadCiudades() const;

    EstadoOperacion consultarCiudad(int id, Ciudad& salida) const;
    EstadoOperacion consultarCiudadPorIndice(int indice, Ciudad& salida) const;
    EstadoOperacion agregarCiudad(
        const std::string& nombre, int x, int y, int& idGenerado);
    EstadoOperacion modificarCiudad(
        int id, const std::string& nombre, int x, int y);
    EstadoOperacion eliminarCiudad(int id);
};

#endif
