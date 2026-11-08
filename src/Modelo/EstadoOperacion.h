#ifndef ESTADO_OPERACION_H
#define ESTADO_OPERACION_H

// Describe el resultado de una operación sobre las ciudades.
enum EstadoOperacion
{
    Correcto,
    IndiceInvalido,
    CiudadNoEncontrada,
    NombreInvalido,
    MapaNoConfigurado,
    DimensionesInvalidas,
    CoordenadasInvalidas,
    IdentificadoresAgotados
};

#endif
