#include "ResultadoRuta.h"

// Crea un resultado vacío para recibir una búsqueda.
ResultadoRuta::ResultadoRuta()
    : origenId(0), destinoId(0), ciudadesRecorridas(nullptr),
      cantidadCiudades(0), distanciaTotal(0)
{
}

// Copia un recorrido ya validado en un arreglo propio.
ResultadoRuta::ResultadoRuta(int origenId, int destinoId, const int* ids,
    int cantidad, double distancia)
    : origenId(origenId), destinoId(destinoId),
      ciudadesRecorridas(new int[cantidad]), cantidadCiudades(cantidad),
      distanciaTotal(distancia)
{
    for (int indice = 0; indice < cantidad; indice++)
    {
        ciudadesRecorridas[indice] = ids[indice];
    }
}

// Libera el recorrido propio.
ResultadoRuta::~ResultadoRuta()
{
    delete[] ciudadesRecorridas;
}

// Construye una copia profunda, incluso si el origen está vacío.
ResultadoRuta::ResultadoRuta(const ResultadoRuta& otro)
    : origenId(otro.origenId), destinoId(otro.destinoId),
      ciudadesRecorridas(nullptr), cantidadCiudades(otro.cantidadCiudades),
      distanciaTotal(otro.distanciaTotal)
{
    if (cantidadCiudades > 0)
    {
        ciudadesRecorridas = new int[cantidadCiudades];
        for (int indice = 0; indice < cantidadCiudades; indice++)
        {
            ciudadesRecorridas[indice] = otro.ciudadesRecorridas[indice];
        }
    }
}

// Sustituye el recorrido por una copia independiente.
ResultadoRuta& ResultadoRuta::operator=(const ResultadoRuta& otro)
{
    if (this == &otro)
    {
        return *this;
    }
    int* nuevosIds = nullptr;
    if (otro.cantidadCiudades > 0)
    {
        nuevosIds = new int[otro.cantidadCiudades];
        for (int indice = 0; indice < otro.cantidadCiudades; indice++)
        {
            nuevosIds[indice] = otro.ciudadesRecorridas[indice];
        }
    }
    delete[] ciudadesRecorridas;
    ciudadesRecorridas = nuevosIds;
    cantidadCiudades = otro.cantidadCiudades;
    origenId = otro.origenId;
    destinoId = otro.destinoId;
    distanciaTotal = otro.distanciaTotal;
    return *this;
}

// Devuelve el ID de origen guardado.
int ResultadoRuta::obtenerOrigenId() const
{
    return origenId;
}

// Devuelve el ID de destino guardado.
int ResultadoRuta::obtenerDestinoId() const
{
    return destinoId;
}

// Devuelve la cantidad de ciudades del recorrido.
int ResultadoRuta::obtenerCantidadCiudades() const
{
    return cantidadCiudades;
}

// Devuelve la distancia acumulada del recorrido.
double ResultadoRuta::obtenerDistanciaTotal() const
{
    return distanciaTotal;
}

// Copia un ID por posición sin exponer el arreglo interno.
EstadoOperacion ResultadoRuta::consultarCiudadPorIndice(
    int indice, int& idSalida) const
{
    if (indice < 0 || indice >= cantidadCiudades)
    {
        return IndiceInvalido;
    }
    idSalida = ciudadesRecorridas[indice];
    return Correcto;
}
