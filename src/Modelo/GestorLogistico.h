#ifndef GESTOR_LOGISTICO_H
#define GESTOR_LOGISTICO_H

#include "Ciudad.h"
#include "Conexion.h"
#include "EstadoOperacion.h"
#include "HistorialRutas.h"
#include "ResultadoRuta.h"

// Administra la red, calcula rutas y registra los resultados de la sesión.
class GestorLogistico
{
private:
    Ciudad* ciudades;
    int cantidadCiudades;
    Conexion* conexiones;
    int cantidadConexiones;
    double** matrizAdyacencia;
    int siguienteId;
    int anchoMapa;
    int altoMapa;
    HistorialRutas& historial;

    int buscarIndiceCiudad(int id) const;
    int buscarIndiceConexion(int origenId, int destinoId) const;
    bool nombreValido(const std::string& nombre) const;
    bool coordenadasValidas(int x, int y) const;
    static double** construirMatriz(const Ciudad* ciudades,
        int cantidadCiudades, const Conexion* conexiones,
        int cantidadConexiones);
    static void liberarMatriz(double** matriz, int cantidadCiudades);

public:
    explicit GestorLogistico(HistorialRutas& historial);
    ~GestorLogistico();
    GestorLogistico(const GestorLogistico& otro);
    GestorLogistico& operator=(const GestorLogistico& otro);

    EstadoOperacion configurarMapa(int ancho, int alto);

    int obtenerAnchoMapa() const;
    int obtenerAltoMapa() const;
    int obtenerSiguienteId() const;
    int obtenerCantidadCiudades() const;
    int obtenerCantidadConexiones() const;

    EstadoOperacion consultarCiudad(int id, Ciudad& salida) const;
    EstadoOperacion consultarCiudadPorIndice(int indice, Ciudad& salida) const;
    EstadoOperacion consultarConexionPorIndice(int indice, Conexion& salida) const;
    EstadoOperacion obtenerIndicePorId(int id, int& salida) const;
    EstadoOperacion obtenerIdPorIndice(int indice, int& salida) const;
    EstadoOperacion obtenerPeso(int origenIndice, int destinoIndice,
        double& salida) const;
    EstadoOperacion agregarCiudad(
        const std::string& nombre, int x, int y, int& idGenerado);
    EstadoOperacion modificarCiudad(
        int id, const std::string& nombre, int x, int y);
    EstadoOperacion eliminarCiudad(int id);
    EstadoOperacion agregarConexion(int origenId, int destinoId,
        double distancia);
    EstadoOperacion modificarConexion(int origenId, int destinoId,
        double distancia);
    EstadoOperacion eliminarConexion(int origenId, int destinoId);
    EstadoOperacion cortarConexion(int origenId, int destinoId);
    EstadoOperacion habilitarConexion(int origenId, int destinoId);
    EstadoOperacion calcularRutaOptima(int origenId, int destinoId,
        ResultadoRuta& salida);
};

#endif
