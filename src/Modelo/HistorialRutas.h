#ifndef HISTORIAL_RUTAS_H
#define HISTORIAL_RUTAS_H

#include "RegistroRuta.h"

// Administra los registros calculados durante una sesión.
class HistorialRutas
{
private:
    RegistroRuta* registros;
    int cantidadRegistros;

public:
    HistorialRutas();
    ~HistorialRutas();
    HistorialRutas(const HistorialRutas& otro);
    HistorialRutas& operator=(const HistorialRutas& otro);

    EstadoOperacion agregarRegistro(const RegistroRuta& registro);
    int obtenerCantidadRegistros() const;
    EstadoOperacion consultarRegistro(int indice, RegistroRuta& salida) const;
};

#endif
