# Sistemas Operativos
## Juan Esteban Acosta López y Maria Del Mar Villaquiran Dávila
## Proyecto 2:
### Implementación
Se nos pide realizar un servidor que reciba peticiones por un puerto y el servidor ebe ejecutarlas, los tipos de peticiones son:
1. Crear contenedores.
2. Listar contenedores.
3. Detener contenedor.
4. Borrar contenedor.

Para esto creamos una función *worker el cual depende de la peticion que se haga hacemos un exec (en este caso un execlp) y crea/lista/detiene/borra contenedores
.Tenemos un makefile, el cual se ejecuta:
Primero se debe ejecutar:
**./socket_server** 
Y luego el
**./socket_client** para establecer una conexión entre esas dos.

