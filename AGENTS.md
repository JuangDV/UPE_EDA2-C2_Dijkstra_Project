# Instrucciones de desarrollo para agentes de IA

Estas reglas se aplican a todo el repositorio. Su objetivo es que el propietario controle el alcance, las decisiones y la integración de cada cambio.

## Fuente de verdad y alcance

- Leer este archivo, el README, el issue o pedido vigente y los archivos pertinentes antes de proponer trabajo.
- Tratar cada pedido como una tarea acotada. No convertir una sugerencia, un riesgo detectado o una tarea futura en trabajo autorizado.
- No inventar requisitos, arquitectura, datos ni resultados de pruebas. Señalar las dudas que afecten el comportamiento antes de implementar.
- Si una instrucción entra en conflicto con otra o el alcance no está claro, detener la parte afectada y pedir una decisión concreta.

## Puerta obligatoria antes de cambiar código

Antes de crear o editar código, pruebas, dependencias, configuración de compilación o workflows:

1. Hacer una inspección de solo lectura del estado actual.
2. Presentar un plan breve con objetivo, alcance, archivos previstos, decisiones técnicas, criterios de aceptación, pruebas y riesgos.
3. Esperar la aprobación explícita del propietario para **ese plan y esa tarea**. La aprobación de una tarea no se hereda a otra.
4. Si durante la ejecución cambia el alcance, una decisión técnica o la lista de archivos de forma material, actualizar el plan y obtener nueva aprobación antes de continuar.

Un pedido explícito que ya define el plan y autoriza implementarlo satisface esta puerta. No repetir preguntas ya respondidas.

## Ejecución de una tarea aprobada

- Trabajar en una rama de la tarea. No escribir directamente en `main`.
- Implementar el cambio mínimo que cumpla los criterios aprobados. Mantener separados los cambios ajenos a la tarea.
- Añadir o actualizar pruebas que verifiquen comportamiento relevante. Ejecutar las pruebas y la compilación disponibles; registrar comandos y resultados reales.
- Revisar el diff final para detectar archivos inesperados, datos sensibles y cambios fuera de alcance.
- Entregar un resumen de lo cambiado, evidencia de validación, limitaciones y decisiones pendientes. Abrir un PR revisable cuando el pedido incluya entregar el cambio en GitHub.
- No fusionar el PR ni desplegar sin autorización explícita del propietario. No hacer force push, borrar ramas o alterar historial sin autorización específica.

## Revisión y criterios de terminado

- Todo cambio de código pasa por PR, revisión humana del propietario y controles automáticos cuando existan.
- Para cambios no triviales, pedir una revisión independiente del diff. La revisión de IA es apoyo; no reemplaza la revisión humana.
- Un trabajo está listo para revisión cuando cumple los criterios de aceptación, compila, pasan las pruebas pertinentes y el PR explica qué cambió, por qué, cómo se comprobó y qué queda pendiente.
- Si no se pudo ejecutar una comprobación, informar el motivo y el riesgo. Nunca declarar que una prueba pasó sin haberla ejecutado.
- Una tarea termina al entregar el PR o resultado aprobado; no iniciar la siguiente tarea por iniciativa propia.

## Reglas del dominio

- El proyecto modela rutas con grafos dirigidos y ponderados. Dijkstra requiere pesos no negativos; rechazar o tratar explícitamente los negativos según la especificación aprobada.
- Definir y probar el comportamiento para vértices desconocidos, destinos inalcanzables, rutas alternativas y límites numéricos antes de dar por correcta la implementación.
- El formato de persistencia y los contratos de entrada/salida requieren una decisión documentada y pruebas de ida y vuelta antes de implementarse.
- Evitar introducir secretos, datos personales o archivos generados en el repositorio.

## Cambios a estas reglas

Modificar este archivo mediante un PR específico. Explicar el motivo y obtener revisión del propietario antes de integrarlo.
