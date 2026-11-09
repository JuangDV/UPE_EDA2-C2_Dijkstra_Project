#include "GestorLogistico.h"

#include <climits>
#include <cmath>
#include <limits>

// Crea una red vacía, sin dimensiones configuradas.
GestorLogistico::GestorLogistico()
    : ciudades(nullptr), cantidadCiudades(0), conexiones(nullptr),
      cantidadConexiones(0), matrizAdyacencia(nullptr), siguienteId(1),
      anchoMapa(0), altoMapa(0)
{
}

// Libera todos los arreglos propiedad del gestor.
GestorLogistico::~GestorLogistico()
{
    liberarMatriz(matrizAdyacencia, cantidadCiudades);
    delete[] conexiones;
    delete[] ciudades;
}

// Construye una copia independiente de las ciudades y conexiones.
GestorLogistico::GestorLogistico(const GestorLogistico& otro)
    : ciudades(nullptr), cantidadCiudades(otro.cantidadCiudades),
      conexiones(nullptr), cantidadConexiones(otro.cantidadConexiones),
      matrizAdyacencia(nullptr), siguienteId(otro.siguienteId),
      anchoMapa(otro.anchoMapa), altoMapa(otro.altoMapa)
{
    try
    {
        if (cantidadCiudades > 0)
        {
            ciudades = new Ciudad[cantidadCiudades];
            for (int indice = 0; indice < cantidadCiudades; indice++)
            {
                ciudades[indice] = otro.ciudades[indice];
            }
        }
        if (cantidadConexiones > 0)
        {
            conexiones = new Conexion[cantidadConexiones];
            for (int indice = 0; indice < cantidadConexiones; indice++)
            {
                conexiones[indice] = otro.conexiones[indice];
            }
        }
        matrizAdyacencia = construirMatriz(ciudades, cantidadCiudades,
            conexiones, cantidadConexiones);
    }
    catch (...)
    {
        delete[] conexiones;
        delete[] ciudades;
        throw;
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
    Conexion* nuevasConexiones = nullptr;
    double** nuevaMatriz = nullptr;
    try
    {
        if (otro.cantidadCiudades > 0)
        {
            nuevasCiudades = new Ciudad[otro.cantidadCiudades];
            for (int indice = 0; indice < otro.cantidadCiudades; indice++)
            {
                nuevasCiudades[indice] = otro.ciudades[indice];
            }
        }
        if (otro.cantidadConexiones > 0)
        {
            nuevasConexiones = new Conexion[otro.cantidadConexiones];
            for (int indice = 0; indice < otro.cantidadConexiones; indice++)
            {
                nuevasConexiones[indice] = otro.conexiones[indice];
            }
        }
        nuevaMatriz = construirMatriz(nuevasCiudades, otro.cantidadCiudades,
            nuevasConexiones, otro.cantidadConexiones);
    }
    catch (...)
    {
        delete[] nuevasConexiones;
        delete[] nuevasCiudades;
        throw;
    }

    liberarMatriz(matrizAdyacencia, cantidadCiudades);
    delete[] conexiones;
    delete[] ciudades;
    ciudades = nuevasCiudades;
    cantidadCiudades = otro.cantidadCiudades;
    conexiones = nuevasConexiones;
    cantidadConexiones = otro.cantidadConexiones;
    matrizAdyacencia = nuevaMatriz;
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

// Devuelve la cantidad de conexiones dirigidas almacenadas.
int GestorLogistico::obtenerCantidadConexiones() const
{
    return cantidadConexiones;
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

// Copia una conexión por posición sin exponer el arreglo interno.
EstadoOperacion GestorLogistico::consultarConexionPorIndice(
    int indice, Conexion& salida) const
{
    if (indice < 0 || indice >= cantidadConexiones)
    {
        return IndiceInvalido;
    }
    salida = conexiones[indice];
    return Correcto;
}

// Traduce el ID estable de una ciudad a su posición actual.
EstadoOperacion GestorLogistico::obtenerIndicePorId(int id, int& salida) const
{
    int indice = buscarIndiceCiudad(id);
    if (indice == -1)
    {
        return CiudadNoEncontrada;
    }
    salida = indice;
    return Correcto;
}

// Traduce una posición actual al ID estable de la ciudad.
EstadoOperacion GestorLogistico::obtenerIdPorIndice(
    int indice, int& salida) const
{
    if (indice < 0 || indice >= cantidadCiudades)
    {
        return IndiceInvalido;
    }
    salida = ciudades[indice].obtenerId();
    return Correcto;
}

// Devuelve una celda de la matriz vigente por índices de ciudad.
EstadoOperacion GestorLogistico::obtenerPeso(
    int origenIndice, int destinoIndice, double& salida) const
{
    if (origenIndice < 0 || origenIndice >= cantidadCiudades ||
        destinoIndice < 0 || destinoIndice >= cantidadCiudades)
    {
        return IndiceInvalido;
    }
    salida = matrizAdyacencia[origenIndice][destinoIndice];
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

    // Prepara ciudades y matriz antes de modificar el estado vigente.
    Ciudad* nuevasCiudades = nullptr;
    double** nuevaMatriz = nullptr;
    int nuevoId = siguienteId;
    try
    {
        nuevasCiudades = new Ciudad[cantidadCiudades + 1];
        for (int indice = 0; indice < cantidadCiudades; indice++)
        {
            nuevasCiudades[indice] = ciudades[indice];
        }
        nuevasCiudades[cantidadCiudades] = Ciudad(nuevoId, nombre, x, y);
        nuevaMatriz = construirMatriz(nuevasCiudades, cantidadCiudades + 1,
            conexiones, cantidadConexiones);
    }
    catch (...)
    {
        delete[] nuevasCiudades;
        throw;
    }

    // Incorpora ambos arreglos y actualiza los contadores.
    liberarMatriz(matrizAdyacencia, cantidadCiudades);
    delete[] ciudades;
    ciudades = nuevasCiudades;
    matrizAdyacencia = nuevaMatriz;
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

// Elimina una ciudad y todas sus conexiones entrantes y salientes.
EstadoOperacion GestorLogistico::eliminarCiudad(int id)
{
    int indiceEliminado = buscarIndiceCiudad(id);
    if (indiceEliminado == -1)
    {
        return CiudadNoEncontrada;
    }

    int nuevaCantidad = cantidadCiudades - 1;
    Ciudad* nuevasCiudades = nullptr;
    int nuevaCantidadConexiones = 0;
    for (int indice = 0; indice < cantidadConexiones; indice++)
    {
        if (conexiones[indice].obtenerOrigenId() != id &&
            conexiones[indice].obtenerDestinoId() != id)
        {
            nuevaCantidadConexiones++;
        }
    }
    Conexion* nuevasConexiones = nullptr;
    double** nuevaMatriz = nullptr;
    try
    {
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
        if (nuevaCantidadConexiones > 0)
        {
            nuevasConexiones = new Conexion[nuevaCantidadConexiones];
            int destino = 0;
            for (int indice = 0; indice < cantidadConexiones; indice++)
            {
                if (conexiones[indice].obtenerOrigenId() != id &&
                    conexiones[indice].obtenerDestinoId() != id)
                {
                    nuevasConexiones[destino] = conexiones[indice];
                    destino++;
                }
            }
        }
        nuevaMatriz = construirMatriz(nuevasCiudades, nuevaCantidad,
            nuevasConexiones, nuevaCantidadConexiones);
    }
    catch (...)
    {
        delete[] nuevasConexiones;
        delete[] nuevasCiudades;
        throw;
    }

    liberarMatriz(matrizAdyacencia, cantidadCiudades);
    delete[] conexiones;
    delete[] ciudades;
    ciudades = nuevasCiudades;
    conexiones = nuevasConexiones;
    matrizAdyacencia = nuevaMatriz;
    cantidadCiudades = nuevaCantidad;
    cantidadConexiones = nuevaCantidadConexiones;
    return Correcto;
}

// Agrega una conexión dirigida habilitada entre ciudades existentes.
EstadoOperacion GestorLogistico::agregarConexion(
    int origenId, int destinoId, double distancia)
{
    if (buscarIndiceCiudad(origenId) == -1 ||
        buscarIndiceCiudad(destinoId) == -1)
    {
        return CiudadNoEncontrada;
    }
    if (origenId == destinoId)
    {
        return OrigenDestinoIguales;
    }
    if (buscarIndiceConexion(origenId, destinoId) != -1)
    {
        return ConexionDuplicada;
    }
    if (!std::isfinite(distancia) || distancia <= 0)
    {
        return DistanciaInvalida;
    }

    Conexion* nuevasConexiones = nullptr;
    double** nuevaMatriz = nullptr;
    try
    {
        nuevasConexiones = new Conexion[cantidadConexiones + 1];
        for (int indice = 0; indice < cantidadConexiones; indice++)
        {
            nuevasConexiones[indice] = conexiones[indice];
        }
        nuevasConexiones[cantidadConexiones] =
            Conexion(origenId, destinoId, distancia, true);
        nuevaMatriz = construirMatriz(ciudades, cantidadCiudades,
            nuevasConexiones, cantidadConexiones + 1);
    }
    catch (...)
    {
        delete[] nuevasConexiones;
        throw;
    }

    liberarMatriz(matrizAdyacencia, cantidadCiudades);
    delete[] conexiones;
    conexiones = nuevasConexiones;
    matrizAdyacencia = nuevaMatriz;
    cantidadConexiones++;
    return Correcto;
}

// Cambia el peso sin modificar los extremos ni la disponibilidad.
EstadoOperacion GestorLogistico::modificarConexion(
    int origenId, int destinoId, double distancia)
{
    if (buscarIndiceCiudad(origenId) == -1 ||
        buscarIndiceCiudad(destinoId) == -1)
    {
        return CiudadNoEncontrada;
    }
    if (origenId == destinoId)
    {
        return OrigenDestinoIguales;
    }
    int indiceConexion = buscarIndiceConexion(origenId, destinoId);
    if (indiceConexion == -1)
    {
        return ConexionNoEncontrada;
    }
    if (!std::isfinite(distancia) || distancia <= 0)
    {
        return DistanciaInvalida;
    }

    Conexion* nuevasConexiones = nullptr;
    double** nuevaMatriz = nullptr;
    try
    {
        nuevasConexiones = new Conexion[cantidadConexiones];
        for (int indice = 0; indice < cantidadConexiones; indice++)
        {
            nuevasConexiones[indice] = conexiones[indice];
        }
        nuevasConexiones[indiceConexion] = Conexion(origenId, destinoId,
            distancia, conexiones[indiceConexion].estaHabilitada());
        nuevaMatriz = construirMatriz(ciudades, cantidadCiudades,
            nuevasConexiones, cantidadConexiones);
    }
    catch (...)
    {
        delete[] nuevasConexiones;
        throw;
    }

    liberarMatriz(matrizAdyacencia, cantidadCiudades);
    delete[] conexiones;
    conexiones = nuevasConexiones;
    matrizAdyacencia = nuevaMatriz;
    return Correcto;
}

// Elimina solo la dirección solicitada.
EstadoOperacion GestorLogistico::eliminarConexion(
    int origenId, int destinoId)
{
    if (buscarIndiceCiudad(origenId) == -1 ||
        buscarIndiceCiudad(destinoId) == -1)
    {
        return CiudadNoEncontrada;
    }
    if (origenId == destinoId)
    {
        return OrigenDestinoIguales;
    }
    int indiceEliminado = buscarIndiceConexion(origenId, destinoId);
    if (indiceEliminado == -1)
    {
        return ConexionNoEncontrada;
    }

    int nuevaCantidad = cantidadConexiones - 1;
    Conexion* nuevasConexiones = nullptr;
    double** nuevaMatriz = nullptr;
    try
    {
        if (nuevaCantidad > 0)
        {
            nuevasConexiones = new Conexion[nuevaCantidad];
            int destino = 0;
            for (int indice = 0; indice < cantidadConexiones; indice++)
            {
                if (indice != indiceEliminado)
                {
                    nuevasConexiones[destino] = conexiones[indice];
                    destino++;
                }
            }
        }
        nuevaMatriz = construirMatriz(ciudades, cantidadCiudades,
            nuevasConexiones, nuevaCantidad);
    }
    catch (...)
    {
        delete[] nuevasConexiones;
        throw;
    }

    liberarMatriz(matrizAdyacencia, cantidadCiudades);
    delete[] conexiones;
    conexiones = nuevasConexiones;
    matrizAdyacencia = nuevaMatriz;
    cantidadConexiones = nuevaCantidad;
    return Correcto;
}

// Deshabilita una dirección sin perder su distancia.
EstadoOperacion GestorLogistico::cortarConexion(int origenId, int destinoId)
{
    if (buscarIndiceCiudad(origenId) == -1 ||
        buscarIndiceCiudad(destinoId) == -1)
    {
        return CiudadNoEncontrada;
    }
    if (origenId == destinoId)
    {
        return OrigenDestinoIguales;
    }
    int indiceConexion = buscarIndiceConexion(origenId, destinoId);
    if (indiceConexion == -1)
    {
        return ConexionNoEncontrada;
    }
    if (!conexiones[indiceConexion].estaHabilitada())
    {
        return Correcto;
    }

    Conexion* nuevasConexiones = nullptr;
    double** nuevaMatriz = nullptr;
    try
    {
        nuevasConexiones = new Conexion[cantidadConexiones];
        for (int indice = 0; indice < cantidadConexiones; indice++)
        {
            nuevasConexiones[indice] = conexiones[indice];
        }
        nuevasConexiones[indiceConexion] = Conexion(origenId, destinoId,
            conexiones[indiceConexion].obtenerDistancia(), false);
        nuevaMatriz = construirMatriz(ciudades, cantidadCiudades,
            nuevasConexiones, cantidadConexiones);
    }
    catch (...)
    {
        delete[] nuevasConexiones;
        throw;
    }

    liberarMatriz(matrizAdyacencia, cantidadCiudades);
    delete[] conexiones;
    conexiones = nuevasConexiones;
    matrizAdyacencia = nuevaMatriz;
    return Correcto;
}

// Habilita una dirección y restaura su peso en la matriz.
EstadoOperacion GestorLogistico::habilitarConexion(int origenId, int destinoId)
{
    if (buscarIndiceCiudad(origenId) == -1 ||
        buscarIndiceCiudad(destinoId) == -1)
    {
        return CiudadNoEncontrada;
    }
    if (origenId == destinoId)
    {
        return OrigenDestinoIguales;
    }
    int indiceConexion = buscarIndiceConexion(origenId, destinoId);
    if (indiceConexion == -1)
    {
        return ConexionNoEncontrada;
    }
    if (conexiones[indiceConexion].estaHabilitada())
    {
        return Correcto;
    }

    Conexion* nuevasConexiones = nullptr;
    double** nuevaMatriz = nullptr;
    try
    {
        nuevasConexiones = new Conexion[cantidadConexiones];
        for (int indice = 0; indice < cantidadConexiones; indice++)
        {
            nuevasConexiones[indice] = conexiones[indice];
        }
        nuevasConexiones[indiceConexion] = Conexion(origenId, destinoId,
            conexiones[indiceConexion].obtenerDistancia(), true);
        nuevaMatriz = construirMatriz(ciudades, cantidadCiudades,
            nuevasConexiones, cantidadConexiones);
    }
    catch (...)
    {
        delete[] nuevasConexiones;
        throw;
    }

    liberarMatriz(matrizAdyacencia, cantidadCiudades);
    delete[] conexiones;
    conexiones = nuevasConexiones;
    matrizAdyacencia = nuevaMatriz;
    return Correcto;
}

// Calcula el camino de menor distancia sobre la matriz vigente.
EstadoOperacion GestorLogistico::calcularRutaOptima(
    int origenId, int destinoId, ResultadoRuta& salida) const
{
    salida = ResultadoRuta();
    int origen = buscarIndiceCiudad(origenId);
    int destino = buscarIndiceCiudad(destinoId);
    if (origen == -1 || destino == -1)
    {
        return CiudadNoEncontrada;
    }
    if (origen == destino)
    {
        return OrigenDestinoIguales;
    }

    double* distancias = nullptr;
    bool* visitados = nullptr;
    int* predecesores = nullptr;
    int* recorrido = nullptr;
    try
    {
        // Inicializa el estado local del algoritmo.
        distancias = new double[cantidadCiudades];
        visitados = new bool[cantidadCiudades];
        predecesores = new int[cantidadCiudades];
        for (int indice = 0; indice < cantidadCiudades; indice++)
        {
            distancias[indice] = std::numeric_limits<double>::infinity();
            visitados[indice] = false;
            predecesores[indice] = -1;
        }
        distancias[origen] = 0;

        // Fija el candidato alcanzable más próximo; el ID resuelve empates.
        for (int paso = 0; paso < cantidadCiudades; paso++)
        {
            int actual = -1;
            for (int indice = 0; indice < cantidadCiudades; indice++)
            {
                if (visitados[indice] || !std::isfinite(distancias[indice]))
                {
                    continue;
                }
                if (actual == -1 || distancias[indice] < distancias[actual] ||
                    (distancias[indice] == distancias[actual] &&
                     ciudades[indice].obtenerId() <
                         ciudades[actual].obtenerId()))
                {
                    actual = indice;
                }
            }
            if (actual == -1 || actual == destino)
            {
                break;
            }
            visitados[actual] = true;

            // Relaja únicamente las conexiones dirigidas habilitadas.
            for (int vecino = 0; vecino < cantidadCiudades; vecino++)
            {
                double peso = matrizAdyacencia[actual][vecino];
                if (visitados[vecino] || !std::isfinite(peso))
                {
                    continue;
                }
                double propuesta = distancias[actual] + peso;
                if (propuesta < distancias[vecino])
                {
                    distancias[vecino] = propuesta;
                    predecesores[vecino] = actual;
                }
            }
        }

        if (!std::isfinite(distancias[destino]))
        {
            delete[] predecesores;
            delete[] visitados;
            delete[] distancias;
            return SinCamino;
        }

        // Reconstruye los IDs desde el destino hacia el origen.
        int cantidad = 0;
        for (int indice = destino; indice != -1;
             indice = predecesores[indice])
        {
            cantidad++;
        }
        recorrido = new int[cantidad];
        int indice = destino;
        for (int posicion = cantidad - 1; posicion >= 0; posicion--)
        {
            recorrido[posicion] = ciudades[indice].obtenerId();
            indice = predecesores[indice];
        }
        ResultadoRuta encontrado(origenId, destinoId, recorrido, cantidad,
            distancias[destino]);
        salida = encontrado;
    }
    catch (...)
    {
        delete[] recorrido;
        delete[] predecesores;
        delete[] visitados;
        delete[] distancias;
        throw;
    }
    delete[] recorrido;
    delete[] predecesores;
    delete[] visitados;
    delete[] distancias;
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

// Busca una conexión por su par ordenado de IDs.
int GestorLogistico::buscarIndiceConexion(
    int origenId, int destinoId) const
{
    for (int indice = 0; indice < cantidadConexiones; indice++)
    {
        if (conexiones[indice].obtenerOrigenId() == origenId &&
            conexiones[indice].obtenerDestinoId() == destinoId)
        {
            return indice;
        }
    }
    return -1;
}

// Reconstruye una matriz independiente a partir de las conexiones vigentes.
double** GestorLogistico::construirMatriz(const Ciudad* ciudades,
    int cantidadCiudades, const Conexion* conexiones, int cantidadConexiones)
{
    if (cantidadCiudades == 0)
    {
        return nullptr;
    }

    double** matriz = new double*[cantidadCiudades];
    for (int fila = 0; fila < cantidadCiudades; fila++)
    {
        matriz[fila] = nullptr;
    }
    try
    {
        for (int fila = 0; fila < cantidadCiudades; fila++)
        {
            matriz[fila] = new double[cantidadCiudades];
            for (int columna = 0; columna < cantidadCiudades; columna++)
            {
                matriz[fila][columna] = fila == columna ? 0.0 :
                    std::numeric_limits<double>::infinity();
            }
        }

        for (int indice = 0; indice < cantidadConexiones; indice++)
        {
            if (!conexiones[indice].estaHabilitada())
            {
                continue;
            }
            int origenIndice = -1;
            int destinoIndice = -1;
            for (int ciudad = 0; ciudad < cantidadCiudades; ciudad++)
            {
                if (ciudades[ciudad].obtenerId() ==
                    conexiones[indice].obtenerOrigenId())
                {
                    origenIndice = ciudad;
                }
                if (ciudades[ciudad].obtenerId() ==
                    conexiones[indice].obtenerDestinoId())
                {
                    destinoIndice = ciudad;
                }
            }
            if (origenIndice != -1 && destinoIndice != -1)
            {
                matriz[origenIndice][destinoIndice] =
                    conexiones[indice].obtenerDistancia();
            }
        }
    }
    catch (...)
    {
        liberarMatriz(matriz, cantidadCiudades);
        throw;
    }
    return matriz;
}

// Libera todas las filas y el arreglo de punteros de la matriz.
void GestorLogistico::liberarMatriz(double** matriz, int cantidadCiudades)
{
    if (matriz == nullptr)
    {
        return;
    }
    for (int fila = 0; fila < cantidadCiudades; fila++)
    {
        delete[] matriz[fila];
    }
    delete[] matriz;
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
