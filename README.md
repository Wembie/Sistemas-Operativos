# Sistemas-Operativos
## Juan Esteban Acosta López y Maria del Mar Villaquiran Dávila
## Remove_List_Tipica:
### Parametros:
Lista de nodos (Lista enlazada) y valor a remover
### Implementacion:
Primero creamos dentro de la función unas variables que nos ayudaran a lo largo de la ejecución de ella misma, las cuales son una anterior que luego lo usaremos para facilitar a la hora de remover el nodo y luego conectarlos y el nodo en el que trabajaremos una vez vamos recorriendo nodo a nodo dentro de la lista, luego de ello hacemos que dicho nodo se iguale a *l que es el first node dentro de la lista y con ello hacemos un while para recorrerla hasta encontrar el elemento a remover mientras no lo encuentra lo que hacemos es en la variable anterior hacemos igual al nodo en el que estamos, luego de ello la variable nodo que estamos usando la hacemos igual al nodo siguiente y así sucesivamente hasta encontrarlo, luego una lo encontremos tendremos como anterior al nodo anterior en el que estábamos usando, luego verificamos un condicional en el cual verificamos si el anterior es Null o no, en el caso que de que entre en el if de ¡anterior hacemos igual a la lista al nodo en que estamos y al siguiente, si no entonces cogemos el anterior y dentro de ese anterior hacemos igual al siguiente de el a al nodo en el que estamos pero al siguiente de el con ello ya se eliminaría el elemento deseado.
## Remove_List_Elegante:
### Parametros:
Lista de nodos (Lista enlazada) y valor a remover
### Implementacion:
Primero creamos una variable la cual llamaremos indirect que va hacer un apuntador al first node de la lista luego hacemos un while hasta que encontremos que el elemento deseado con ello vamos avanzando con el puntero hasta encontrarlo pero queremos estar uno antes del elemento que queremos borrar y eso los asignamos a indirect, ya una vez finalizado el ciclo hacemos un condicional para saber que indirect no sea null y asignamos un temporal que sea igual a indirect y con ellos hacemos que *indirect se vuelva a conectar a la lista pero uno mas alla del elemento que habiamos encontrado y luego de ello asignamos que el siguiente del temporal sea Null y ademas liberamos la memoria que tenia el temporal y con ello se eliminaria un elemento denuna lista de forma elegante y/o con punteros
