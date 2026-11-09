#include "RegistroRuta.h"

// Crea un registro vacío para consultas por copia.
RegistroRuta::RegistroRuta()
    : fechaHora(), idsCiudades(nullptr), nombresCiudades(nullptr),
      distanciasTramos(nullptr), cantidadCiudades(0), distanciaTotal(0)
{
}

// Copia los datos validados de una ruta a tres arreglos propios.
RegistroRuta::RegistroRuta(const std::string& fechaHora,
    const int* idsCiudades, const std::string* nombresCiudades,
    const double* distanciasTramos, int cantidadCiudades,
    double distanciaTotal)
    : fechaHora(fechaHora), idsCiudades(nullptr), nombresCiudades(nullptr),
      distanciasTramos(nullptr), cantidadCiudades(cantidadCiudades),
      distanciaTotal(distanciaTotal)
{
    try
    {
        if (cantidadCiudades > 0)
        {
            this->idsCiudades = new int[cantidadCiudades];
            this->nombresCiudades = new std::string[cantidadCiudades];
            this->distanciasTramos = new double[cantidadCiudades - 1];
            for (int indice = 0; indice < cantidadCiudades; indice++)
            {
                this->idsCiudades[indice] = idsCiudades[indice];
                this->nombresCiudades[indice] = nombresCiudades[indice];
                if (indice < cantidadCiudades - 1)
                {
                    this->distanciasTramos[indice] = distanciasTramos[indice];
                }
            }
        }
    }
    catch (...)
    {
        delete[] this->distanciasTramos;
        delete[] this->nombresCiudades;
        delete[] this->idsCiudades;
        throw;
    }
}

// Libera los tres arreglos del registro.
RegistroRuta::~RegistroRuta()
{
    delete[] distanciasTramos;
    delete[] nombresCiudades;
    delete[] idsCiudades;
}

// Construye una copia independiente de un registro, incluso vacío.
RegistroRuta::RegistroRuta(const RegistroRuta& otro)
    : RegistroRuta(otro.fechaHora, otro.idsCiudades, otro.nombresCiudades,
        otro.distanciasTramos, otro.cantidadCiudades, otro.distanciaTotal)
{
}

// Sustituye los datos tras preparar todas las copias nuevas.
RegistroRuta& RegistroRuta::operator=(const RegistroRuta& otro)
{
    if (this == &otro)
    {
        return *this;
    }
    std::string nuevaFecha = otro.fechaHora;
    int* nuevosIds = nullptr;
    std::string* nuevosNombres = nullptr;
    double* nuevasDistancias = nullptr;
    try
    {
        if (otro.cantidadCiudades > 0)
        {
            nuevosIds = new int[otro.cantidadCiudades];
            nuevosNombres = new std::string[otro.cantidadCiudades];
            nuevasDistancias = new double[otro.cantidadCiudades - 1];
            for (int indice = 0; indice < otro.cantidadCiudades; indice++)
            {
                nuevosIds[indice] = otro.idsCiudades[indice];
                nuevosNombres[indice] = otro.nombresCiudades[indice];
                if (indice < otro.cantidadCiudades - 1)
                {
                    nuevasDistancias[indice] = otro.distanciasTramos[indice];
                }
            }
        }
    }
    catch (...)
    {
        delete[] nuevasDistancias;
        delete[] nuevosNombres;
        delete[] nuevosIds;
        throw;
    }
    delete[] distanciasTramos;
    delete[] nombresCiudades;
    delete[] idsCiudades;
    idsCiudades = nuevosIds;
    nombresCiudades = nuevosNombres;
    distanciasTramos = nuevasDistancias;
    cantidadCiudades = otro.cantidadCiudades;
    distanciaTotal = otro.distanciaTotal;
    fechaHora.swap(nuevaFecha);
    return *this;
}

// Devuelve la fecha y hora guardadas.
std::string RegistroRuta::obtenerFechaHora() const
{
    return fechaHora;
}

// Devuelve la cantidad de ciudades del recorrido guardado.
int RegistroRuta::obtenerCantidadCiudades() const
{
    return cantidadCiudades;
}

// Devuelve la suma de las distancias de los tramos guardados.
double RegistroRuta::obtenerDistanciaTotal() const
{
    return distanciaTotal;
}

// Copia el ID y nombre de una ciudad por su posición histórica.
EstadoOperacion RegistroRuta::consultarCiudadPorIndice(int indice,
    int& idSalida, std::string& nombreSalida) const
{
    if (indice < 0 || indice >= cantidadCiudades)
    {
        return IndiceInvalido;
    }
    std::string nuevoNombre = nombresCiudades[indice];
    nombreSalida.swap(nuevoNombre);
    idSalida = idsCiudades[indice];
    return Correcto;
}

// Copia la distancia de un tramo por su posición histórica.
EstadoOperacion RegistroRuta::consultarDistanciaTramo(int indice,
    double& salida) const
{
    if (indice < 0 || indice >= cantidadCiudades - 1)
    {
        return IndiceInvalido;
    }
    salida = distanciasTramos[indice];
    return Correcto;
}
