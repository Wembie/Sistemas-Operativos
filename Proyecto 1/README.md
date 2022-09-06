# Sistemas Operativos
## Juan Esteban Acosta López y Maria Del Mar Villaquiran Dávila
## Proyecto 1:
### Implementación

Se nos pide realizar una interfaz de shell, en el cual el usuario realiza comandos que le permiten visualizar/hacer lo que dicho comando permite; Para esto se nos da a seguir un paso a paso que se divide en:
1. Crear el proceso hijo y ejecutar el comando en el hijo.
2. Hacer una función de historial.
3. Añadir sporte de redirección de entrada y salida.
4.  Permitir que los procesos padre e hijo se comuniquen via pipe.

Estos pasos los seguimos para poder resolver el primer proyecto. Lo que hicimos primero para aceptar la cadena que nos daba el usuario es crear un proceso hijo y como bien se pide en el punto 1 mencionado anteriormente, se crea y se ejecuta el comando en el proceso hijo, lo que se hace es hacer uso del execvp dandole los dos parametros. Por ejemplo:
<!-- UL -->
* El comando: **ls -l**
Lo que sucede en este comando es que el primer parametro del execvp va a ser **"ls"** y el segundo parametro va a ser todo el comando; quedaría execvp(entradaArgs[0], entradaArgs) y ya cuando termina de hacer esto se hace que en el padre espere (hasta que el hijo termine) y ya terminaría el comando y mostraría lo que el comando **ls -l** hace, es decir, muestra los archivos situados en la posición actual.

Esto pasa cuando el comando no tiene pipes, pero en caso de que el usuario ingrese un comando con pipes, lo que hacemos es primero verificar si tiene pipes (esto tambien lo hacemos en el caso de arriba, ya que en general hay que revisar si hay pipes o no en el comando ingresado), si tiene pipes, es decir **"|"** se pasa a dividir la linea para poder hacer el llamado del execEntradaPipe. Ya en la función execEntradaPipe le pasamos como parametro EntradaArgs y entradaPipe; en general, esta función el padre crea el pipe por lo que abre los extremos de escritura y lectura que los hijos heredan. En esto, se hacen dos proceso hijos el cual e primer hijo es el encargado de cerrar el extremo de lectura ya que va a escribir por defecto STDOUT con la funcion dup2 y cerramos el extremo; ya para el otro extremo tambien creamos el hijo, pero hacemos lo contrario, es decir, cerramos el extremo de escritura, ya que vamos a leer, hacemos uso de dup2 que por defecto toma STDIN y va a leer el extremo de lectura del pipe y luego lo cerramos.
