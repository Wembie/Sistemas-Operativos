# Sistemas-Operativos
## Juan Esteban Acosta López y Maria del Mar Villaquiran Dávila
## Repuestas a Video:
Nos pareció un poco raro y a la vez interesante de como empezó Linus Torvalds el cual amaba programar y tirar código, comenzó a desarrollar a Linux como desde los 21 años y se volvio un proyecto personal, pero al pasar el tiempo se volvió un proyecto donde contribuían ideas  pero que no tocaran el código del si no que el hiciera prácticamente y le gustaba eso pero a la vez no ya que se contradecía porque no le gusta las personas mejor le gustaban los computadores y en parte si le gustan las personas pero no directamente si no que prefería interactuar con ellas vía email. Y ya por parte de git que pasar de 10 a 100 a 1000 a 10000 o a 100000 etc fue el nacimiento de el mismo (de código abierto, historial de versión de software etc etc) y nos da mucha risa ya que todo fue para no trabajar con tantas personas al tiempo (ya que él dice y siempre lo dira “I am not a people person) y con ello convertirse con lo que es ahora en la actualidad. Por otra parte, lo Tesla vs Edison, lo que me menciona es que Tesla es un científico visionario y una persona prácticamente con ideas locas en cambio Edison lo único que dijo fue sobre su cita más famosa el cual fue “El genio es un 1% de inspiración y el 99% de transpiración y si los comparas, Tesla tiene una clase de mente que atrapa por otro lado Edison no fue una persona tan intelectual o visionara pero que Linus Torvalds se quedaría con él, terminado verán la implementación en el video y funcionando de la lista enlazadas y por ulrimo algo a mencionar es que Linux no hubiera sido lo que es hoy en día si no hubiera sido un código abierto.
## Remove_List_Tipica:
### Parametros:
Lista de nodos (Lista enlazada) y valor a remover
### Implementacion:
Primero creamos dentro de la función unas variables que nos ayudaran a lo largo de la ejecución de ella misma, las cuales son una anterior que luego lo usaremos para facilitar a la hora de remover el nodo y luego conectarlos y el nodo en el que trabajaremos una vez vamos recorriendo nodo a nodo dentro de la lista, luego de ello hacemos que dicho nodo se iguale a *l que es el first node dentro de la lista y con ello hacemos un while para recorrerla hasta encontrar el elemento a remover mientras no lo encuentra lo que hacemos es en la variable anterior hacemos igual al nodo en el que estamos, luego de ello la variable nodo que estamos usando la hacemos igual al nodo siguiente y así sucesivamente hasta encontrarlo, luego una lo encontremos tendremos como anterior al nodo anterior en el que estábamos usando, luego verificamos un condicional en el cual verificamos si el anterior es Null o no, en el caso que de que entre en el if de ¡anterior hacemos igual a la lista al nodo en que estamos y al siguiente, si no entonces cogemos el anterior y dentro de ese anterior hacemos igual al siguiente de el a al nodo en el que estamos pero al siguiente de el con ello ya se eliminaría el elemento deseado.
## Remove_List_Elegante:
### Parametros:
Lista de nodos (Lista enlazada) y valor a remover
### Implementacion:
Primero creamos una variable la cual llamaremos indirect que va hacer un apuntador al first node de la lista luego hacemos un while hasta que encontremos que el elemento deseado con ello vamos avanzando con el puntero hasta encontrarlo pero queremos estar uno antes del elemento que queremos borrar y eso los asignamos a indirect, ya una vez finalizado el ciclo con ellos hacemos que *indirect se vuelva a conectar a la lista pero uno mas alla del elemento que habiamos encontrado y con ello se eliminaria un elemento de una lista de forma elegante y/o con punteros

##Video de explicación del codigo remove_list: https://youtu.be/2x0EVWj3DpY
