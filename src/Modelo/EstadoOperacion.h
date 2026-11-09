#ifndef ESTADO_OPERACION_H
#define ESTADO_OPERACION_H

// Describe el resultado de una operación sobre ciudades o conexiones.
enum EstadoOperacion
{
    Correcto,
    IndiceInvalido,
    CiudadNoEncontrada,
    NombreInvalido,
    MapaNoConfigurado,
    DimensionesInvalidas,
    CoordenadasInvalidas,
    IdentificadoresAgotados,
    ConexionNoEncontrada,
    ConexionDuplicada,
    DistanciaInvalida,
    OrigenDestinoIguales,
    SinCamino
};

#endif
