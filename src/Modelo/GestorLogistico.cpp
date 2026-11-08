#include "GestorLogistico.h"

#include <climits>

// Crea una red vacía, sin dimensiones configuradas.
GestorLogistico::GestorLogistico()
    : ciudades(nullptr), cantidadCiudades(0), siguienteId(1),
      anchoMapa(0), altoMapa(0)
{
}

// Libera el arreglo propiedad del gestor.
GestorLogistico::~GestorLogistico()
{
    delete[] ciudades;
}

// Construye una copia independiente de las ciudades y configuración.
GestorLogistico::GestorLogistico(const GestorLogistico& otro)
    : ciudades(nullptr), cantidadCiudades(otro.cantidadCiudades),
      siguienteId(otro.siguienteId), anchoMapa(otro.anchoMapa),
      altoMapa(otro.altoMapa)
{
    if (cantidadCiudades > 0)
    {
        ciudades = new Ciudad[cantidadCiudades];
        for (int indice = 0; indice < cantidadCiudades; indice++)
        {
            ciudades[indice] = otro.ciudades[indice];
        }
    }
}

// Reemplaza el contenido mediante una copia independiente.
GestorLogistico& GestorLogistico::operator=(const GestorLogistico& otro)
{
    if (this == &otro)
    {
        return *this;
    }

    Ciudad* nuevasCiudades = nullptr;
    if (otro.cantidadCiudades > 0)
    {
        nuevasCiudades = new Ciudad[otro.cantidadCiudades];
        for (int indice = 0; indice < otro.cantidadCiudades; indice++)
        {
            nuevasCiudades[indice] = otro.ciudades[indice];
        }
    }

    delete[] ciudades;
    ciudades = nuevasCiudades;
    cantidadCiudades = otro.cantidadCiudades;
    siguienteId = otro.siguienteId;
    anchoMapa = otro.anchoMapa;
    altoMapa = otro.altoMapa;
    return *this;
}

// Actualiza dimensiones solamente si conservan todas las ciudades dentro.
EstadoOperacion GestorLogistico::configurarMapa(int ancho, int alto)
{
    if (ancho <= 0 || alto <= 0)
    {
        return DimensionesInvalidas;
    }

    for (int indice = 0; indice < cantidadCiudades; indice++)
    {
        int x = ciudades[indice].obtenerX();
        int y = ciudades[indice].obtenerY();
        if (x < 0 || x >= ancho || y < 0 || y >= alto)
        {
            return CoordenadasInvalidas;
        }
    }

    anchoMapa = ancho;
    altoMapa = alto;
    return Correcto;
}

// Devuelve el ancho configurado, o cero si no existe mapa.
int GestorLogistico::obtenerAnchoMapa() const
{
    return anchoMapa;
}

// Devuelve el alto configurado, o cero si no existe mapa.
int GestorLogistico::obtenerAltoMapa() const
{
    return altoMapa;
}

// Devuelve el próximo identificador; INT_MAX indica agotamiento.
int GestorLogistico::obtenerSiguienteId() const
{
    return siguienteId;
}

// Devuelve la cantidad actual de ciudades.
int GestorLogistico::obtenerCantidadCiudades() const
{
    return cantidadCiudades;
}

// Copia una ciudad por ID sin alterar la salida si no existe.
EstadoOperacion GestorLogistico::consultarCiudad(int id, Ciudad& salida) const
{
    int indice = buscarIndiceCiudad(id);
    if (indice == -1)
    {
        return CiudadNoEncontrada;
    }

    salida = ciudades[indice];
    return Correcto;
}

// Copia una ciudad por posición sin exponer el arreglo interno.
EstadoOperacion GestorLogistico::consultarCiudadPorIndice(
    int indice, Ciudad& salida) const
{
    if (indice < 0 || indice >= cantidadCiudades)
    {
        return IndiceInvalido;
    }

    salida = ciudades[indice];
    return Correcto;
}

// Valida y agrega una ciudad al final con un ID nuevo.
EstadoOperacion GestorLogistico::agregarCiudad(
    const std::string& nombre, int x, int y, int& idGenerado)
{
    if (anchoMapa == 0 || altoMapa == 0)
    {
        return MapaNoConfigurado;
    }
    if (!nombreValido(nombre))
    {
        return NombreInvalido;
    }
    if (!coordenadasValidas(x, y))
    {
        return CoordenadasInvalidas;
    }
    if (siguienteId == INT_MAX)
    {
        return IdentificadoresAgotados;
    }

    // Preparación del arreglo del tamaño exacto.
    Ciudad* nuevasCiudades = new Ciudad[cantidadCiudades + 1];
    for (int indice = 0; indice < cantidadCiudades; indice++)
    {
        nuevasCiudades[indice] = ciudades[indice];
    }
    int nuevoId = siguienteId;
    nuevasCiudades[cantidadCiudades] = Ciudad(nuevoId, nombre, x, y);

    // Incorporación de la ciudad y actualización de los contadores.
    delete[] ciudades;
    ciudades = nuevasCiudades;
    cantidadCiudades++;
    siguienteId++;
    idGenerado = nuevoId;
    return Correcto;
}

// Cambia los datos de una ciudad conservando su ID y posición.
EstadoOperacion GestorLogistico::modificarCiudad(
    int id, const std::string& nombre, int x, int y)
{
    int indice = buscarIndiceCiudad(id);
    if (indice == -1)
    {
        return CiudadNoEncontrada;
    }
    if (!nombreValido(nombre))
    {
        return NombreInvalido;
    }
    if (!coordenadasValidas(x, y))
    {
        return CoordenadasInvalidas;
    }

    ciudades[indice] = Ciudad(id, nombre, x, y);
    return Correcto;
}

// Elimina una ciudad y conserva el orden y los IDs restantes.
EstadoOperacion GestorLogistico::eliminarCiudad(int id)
{
    int indiceEliminado = buscarIndiceCiudad(id);
    if (indiceEliminado == -1)
    {
        return CiudadNoEncontrada;
    }

    int nuevaCantidad = cantidadCiudades - 1;
    Ciudad* nuevasCiudades = nullptr;
    if (nuevaCantidad > 0)
    {
        nuevasCiudades = new Ciudad[nuevaCantidad];
        int destino = 0;
        for (int indice = 0; indice < cantidadCiudades; indice++)
        {
            if (indice != indiceEliminado)
            {
                nuevasCiudades[destino] = ciudades[indice];
                destino++;
            }
        }
    }

    delete[] ciudades;
    ciudades = nuevasCiudades;
    cantidadCiudades = nuevaCantidad;
    return Correcto;
}

// Busca secuencialmente la posición de un identificador estable.
int GestorLogistico::buscarIndiceCiudad(int id) const
{
    for (int indice = 0; indice < cantidadCiudades; indice++)
    {
        if (ciudades[indice].obtenerId() == id)
        {
            return indice;
        }
    }
    return -1;
}

// Comprueba el límite de bytes y que el texto no sea solo espacios.
bool GestorLogistico::nombreValido(const std::string& nombre) const
{
    if (nombre.empty() || nombre.size() > 99)
    {
        return false;
    }
    for (std::string::size_type indice = 0; indice < nombre.size(); indice++)
    {
        if (nombre[indice] != ' ')
        {
            return true;
        }
    }
    return false;
}

// Comprueba los límites de las coordenadas en el mapa configurado.
bool GestorLogistico::coordenadasValidas(int x, int y) const
{
    return x >= 0 && x < anchoMapa && y >= 0 && y < altoMapa;
}
