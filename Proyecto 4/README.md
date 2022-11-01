# Sistemas Operativos
## Juan Esteban Acosta López y Maria Del Mar Villaquiran Dávila
## Proyecto 4:
### Investigativa:

### (0.6 puntos) Explicar cada uno de los cambios que está haciendo.
1. En syscall.h , agregue las siguientes dos llamadas al sistema. Aquí, le he dado los números 22 y 23 a las llamadas del sistema. El cps es para la llamada al sistema ps y chpr (cambio de prioridad) es para la llamada al sistema agradable.
2. En el PCB del proceso, debemos agregar un nuevo atributo 'prioridad'. El PCB del proceso se almacena en el archivo proc.h.
3. Tenemos que incluir la definición de las funciones cps y chpr en proc.c
4. en sysproc.c , tenemos que definir una función en la que se llamarán nuestras funciones cps y chpr.
5. debemos realizar algunos cambios menores en el archivo usys.S. La extensión '.S' indica que este archivo tiene código de nivel de ensamblaje y este archivo interactúa con el hardware del sistema.
6. abrimos el archivo sysproc.c y agregamos las dos llamadas al sistema.
7. tenemos que crear un archivo ps.c y nice.c en el que se llamarán nuestras funciones cps y chpr respectivamente.
8. Ahora que hemos realizado nuestras llamadas al sistema, tenemos que trabajar en la asignación de prioridad del proceso. Para ello, en primer lugar definimos la prioridad por defecto de un proceso en la función allocproc del archivo proc.c.
9. Ahora, se espera que el proceso secundario tenga mayor prioridad que el proceso principal. Así que tenemos que cambiar la prioridad del proceso hijo cuando se crea. Para esto, haremos los cambios en el archivo exec.c.
10. Ahora, tenemos que crear un programa ac que cree una serie de procesos secundarios como lo menciona el usuario y consume tiempo de CPU para probar las llamadas y la programación de nuestro sistema. Entonces creamos un nuevo archivo dpro.c (programa ficticio)
11. Ahora, hacemos los cambios apropiados en el Makefile . En Makefile, en 'UPROGS' y También en la sección EXTRAS del Makefile, agregue nice.c , dpro.c y ps.c
12. El algoritmo de programación de CPU por turnos basado en prioridades se basa en la integración del algoritmo de programación por turnos y de prioridad. Conserva la ventaja del turno rotatorio para reducir el hambre y también integra la ventaja de la programación prioritaria. El algoritmo de programación de CPU por turnos existente no se puede implementar en el sistema operativo en tiempo real debido a sus altas tasas de cambio de contexto, gran tiempo de espera, gran tiempo de respuesta, gran tiempo de respuesta y menor rendimiento. El algoritmo propuesto mejora todos los inconvenientes del algoritmo de programación por turnos.
Para implementar esto, hacemos los cambios requeridos en la función del planificador en el archivo proc.c.
