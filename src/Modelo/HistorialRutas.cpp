#include "HistorialRutas.h"

// Crea un historial vacío para la sesión.
HistorialRutas::HistorialRutas()
    : registros(nullptr), cantidadRegistros(0)
{
}

// Libera las copias de todos los registros.
HistorialRutas::~HistorialRutas()
{
    delete[] registros;
}

// Construye una copia independiente de todos los registros.
HistorialRutas::HistorialRutas(const HistorialRutas& otro)
    : registros(nullptr), cantidadRegistros(0)
{
    if (otro.cantidadRegistros > 0)
    {
        RegistroRuta* nuevos = new RegistroRuta[otro.cantidadRegistros];
        try
        {
            for (int indice = 0; indice < otro.cantidadRegistros; indice++)
            {
                nuevos[indice] = otro.registros[indice];
            }
        }
        catch (...)
        {
            delete[] nuevos;
            throw;
        }
        registros = nuevos;
        cantidadRegistros = otro.cantidadRegistros;
    }
}

// Reemplaza los registros mediante una copia profunda.
HistorialRutas& HistorialRutas::operator=(const HistorialRutas& otro)
{
    if (this == &otro)
    {
        return *this;
    }
    RegistroRuta* nuevos = nullptr;
    if (otro.cantidadRegistros > 0)
    {
        nuevos = new RegistroRuta[otro.cantidadRegistros];
        try
        {
            for (int indice = 0; indice < otro.cantidadRegistros; indice++)
            {
                nuevos[indice] = otro.registros[indice];
            }
        }
        catch (...)
        {
            delete[] nuevos;
            throw;
        }
    }
    delete[] registros;
    registros = nuevos;
    cantidadRegistros = otro.cantidadRegistros;
    return *this;
}

// Agrega una copia al final sin alterar el historial ante una excepción.
EstadoOperacion HistorialRutas::agregarRegistro(const RegistroRuta& registro)
{
    RegistroRuta* nuevos = new RegistroRuta[cantidadRegistros + 1];
    try
    {
        for (int indice = 0; indice < cantidadRegistros; indice++)
        {
            nuevos[indice] = registros[indice];
        }
        nuevos[cantidadRegistros] = registro;
    }
    catch (...)
    {
        delete[] nuevos;
        throw;
    }
    delete[] registros;
    registros = nuevos;
    cantidadRegistros++;
    return Correcto;
}

// Devuelve la cantidad de registros guardados en la sesión.
int HistorialRutas::obtenerCantidadRegistros() const
{
    return cantidadRegistros;
}

// Entrega una copia por índice sin exponer el arreglo interno.
EstadoOperacion HistorialRutas::consultarRegistro(int indice,
    RegistroRuta& salida) const
{
    if (indice < 0 || indice >= cantidadRegistros)
    {
        return IndiceInvalido;
    }
    salida = registros[indice];
    return Correcto;
}
