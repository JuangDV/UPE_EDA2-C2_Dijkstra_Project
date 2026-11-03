# Metodología de trabajo

Este proyecto se desarrolla en entregas pequeñas, verificables y aprobadas por el propietario. Las instrucciones específicas para agentes están en [AGENTS.md](AGENTS.md).

## Ciclo por tarea

1. **Definir.** Registrar el problema, resultado esperado, límites y criterios observables de aceptación en un issue o pedido escrito. Una tarea debe poder revisarse en un PR pequeño.
2. **Investigar.** La IA inspecciona el repositorio sin modificarlo, identifica dependencias y presenta dudas reales.
3. **Aprobar el plan.** El propietario aprueba el alcance, los archivos previstos, las decisiones técnicas y la validación antes de cualquier cambio de código. Si el plan cambia materialmente, se vuelve a aprobar.
4. **Implementar.** La IA trabaja en una rama por tarea, agrega las pruebas necesarias y mantiene el diff dentro del alcance aprobado.
5. **Verificar y revisar.** La IA ejecuta compilación y pruebas, revisa el diff y entrega un PR con evidencia. En cambios no triviales se solicita una segunda revisión independiente; el propietario revisa y decide.
6. **Integrar.** Solo el propietario autoriza la fusión. Después se cierra la tarea y se registra cualquier deuda como trabajo nuevo.

## Decisiones que se acuerdan antes de programar

Para este proyecto, cada decisión relevante debe quedar en el plan o en un documento aprobado: compilador y versión de C++, sistema de compilación, interfaz de usuario, representación del grafo, rango y tipo de pesos, comportamiento ante rutas imposibles, formato de persistencia y política de errores. La IA puede proponer opciones con sus costos, pero no escoger silenciosamente una que cambie el producto.

## Revisión del PR

El PR debe mostrar el issue o pedido, el plan aprobado, los criterios de aceptación, los archivos cambiados, las pruebas ejecutadas con su resultado y los riesgos pendientes. La revisión comprueba especialmente corrección del algoritmo, casos límite, compatibilidad de datos y alcance. Los comentarios bloqueantes se resuelven antes de integrar.

## Automatización recomendada

Cuando exista un proyecto compilable, configurar CI para compilar y ejecutar pruebas en cada PR. Después configurar una regla de protección para `main` que requiera PR, comprobaciones exitosas y revisión. Las reglas escritas orientan a la IA; la protección de GitHub y CI hacen cumplir las condiciones de integración.

## Excepciones

Una urgencia no elimina la trazabilidad: documentar motivo, alcance y comprobaciones mínimas. El propietario decide y aprueba cualquier excepción antes de aplicarla.
