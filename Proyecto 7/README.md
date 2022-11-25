# Sistemas Operativos
## Juan Esteban Acosta López y Maria Del Mar Villaquiran Dávila
## Proyecto 7:
## 1.
### ¿Qué es el sistema de archivos de red (NFS)?
Se nos enseña temprano en nuestras vidas que compartir es bueno. Network File System (NFS) se construyó sobre el principio de compartir. NFS es un estándar de Internet, protocolo cliente/servidor desarrollado en 1984 por Sun Microsystems para admitir el acceso a datos (archivos) compartidos, originalmente sin estado, al almacenamiento de red conectado a LAN. Como tal, NFS permite que un cliente vea, almacene y actualice archivos en una computadora remota como si estuvieran almacenados localmente. En el back-end, el software de cliente NFS traduce los comandos de acceso a archivos POSIX emitidos por las aplicaciones en solicitudes de servidor NFS que responden con metadatos, datos y estado. Las principales versiones implementadas actualmente (cliente y servidor) son NFSv3, NFSv4 y NFSv4.1.

Network File System (NFS), fue un protocolo inventado en los años 80 para facilitar el intercambio remoto de archivos entre servidores. Existen múltiples versiones de NFS. NFS v3 es el más común. NFS es fácil de usar y administrar y requiere un cliente en el kernel que admita el montaje de NFS.

### Beneficios de usar NFS
A lo largo de los años, NFS ha evolucionado para admitir una mayor seguridad, un mejor uso compartido de archivos (bloqueo) y un mejor rendimiento (almacenamiento en caché). Además, es una solución relativamente asequible y fácil de usar para compartir archivos en red que utiliza la infraestructura de protocolo de Internet existente.

Actualmente, estos son los beneficios del servicio NFS:

- Múltiples clientes pueden usar los mismos archivos, lo que permite que todos en la red usen los mismos datos, accediendo a ellos en hosts remotos como si estuvieran accediendo a archivos locales.
- Las computadoras comparten aplicaciones, lo que elimina la necesidad de espacio en disco local y reduce los costos de almacenamiento.
- Todos los usuarios pueden leer los mismos archivos, por lo que los datos pueden permanecer actualizados y son consistentes y confiables.
- El montaje del sistema de archivos es transparente para todos los usuarios.
- La compatibilidad con entornos heterogéneos le permite ejecutar tecnología mixta de varios proveedores y utilizar componentes interoperables.
- La sobrecarga de administración del sistema se reduce debido a la centralización de datos.
- Menos discos extraíbles y unidades por ahí reduce los problemas de seguridad, ¡lo cual siempre es bueno!

### Desventajas del sistema de archivos de red

Hay muchos desafíos con el estándar de Internet NFS actual que pueden o no abordarse en el futuro; por ejemplo, algunas revisiones de NFSv4 y NFSv4.1 sugieren que estas versiones tienen un ancho de banda y escalabilidad limitados (mejorados con NFSv4.2) y que NFS se ralentiza durante el tráfico pesado de la red. Aquí hay algunos otros:

- Seguridad : lo primero y más importante es una preocupación de seguridad, dado que NFS se basa en RPC que son intrínsecamente inseguros y solo deben usarse en una red confiable detrás de un firewall. De lo contrario, NFS será vulnerable a las amenazas de Internet.
- Charla de protocolo: el protocolo cliente-servidor de NFS requiere que se configure una gran cantidad de actividad de solicitud para transferir datos. El protocolo NFS requiere muchas interacciones pequeñas o pasos para leer y escribir datos, lo que equivale a una tonelada de sobrecarga para alguien que interactúa activamente con las cargas de trabajo de AI/ML/DL de hoy en día que consumen una enorme cantidad de archivos pequeños.
- El uso compartido de archivos es muy complejo : configurar y configurar el acceso adecuado a los archivos compartidos mediante el bloqueo y el almacenamiento en caché de archivos es, en el mejor de los casos, una tarea desalentadora. Por un lado, agrega una gran cantidad de sobrecarga de protocolo, lo que lleva a la charlatanería mencionada anteriormente. Por otro lado, todavía deja mucho que desear, ya que cualquier comando de montaje de cada host para el mismo sistema de archivos puede salir mal fácilmente.
- Acceso a archivos paralelos : NFS se diseñó como una forma de acceder secuencialmente a un archivo de red compartido, pero en estos días las aplicaciones manejan archivos más grandes y se requiere acceso a archivos paralelos o no secuenciales. Esto se agregó a NFSv4, pero no muchos clientes lo admiten todavía.
Limitaciones de tamaño de bloque : el estándar de protocolo NFS actual permite transferir un máximo de 1 MB de datos durante una solicitud de lectura o escritura. En 1984, 1 MB era una gran cantidad de datos, pero ya no es así. Hay clases de aplicaciones que deberían transferir GB, no MB de datos.

Hay otros problemas con NFS, pero estos son nuestros cinco principales. Sí, las restricciones de tamaño de bloque podrían hacerse más grandes fácilmente, pero luego los tiempos de espera deberían ajustarse y tal vez repensarse. Y sí, se acerca el acceso a archivos en paralelo, pero los problemas de protocolo de conversación y uso compartido de archivos (bloqueo y almacenamiento en caché) enumerados anteriormente son mucho más difíciles de resolver.

NFS ha funcionado bien durante más de 35 años. No está claro si NFS se puede rescatar en el mundo de archivos pequeños de hoy. Se podría impulsar otra versión de NFS a través del comité del estándar, pero nuestra opinión es que el problema de la charlatanería es demasiado endémico en la definición del protocolo para eliminarlo por completo, Y NFS necesita admitir archivos compartidos por completo o no, hacer ambas cosas es una receta por fracaso

### 2. COMANDOS

Comando de extracción de ventana acoplable:
- mkdir nfs
- nano docker-compose.yml
Ahora colocamos en el .yml
````
version: "2.1"
services:
  # https://hub.docker.com/r/itsthenetwor...
  nfs:
    image: itsthenetwork/nfs-server-alpine:12
    container_name: nfs
    restart: always
    privileged: true
    environment:
      - SHARED_DIRECTORY=/data
    volumes:
      - /data/docker-volumes:/data
    ports:
      - 2049:2049
````
En esta parte estamos creando el sevidor.
- sudo apt install docker-compose
- docker-compose up
- Y ya con eso ponemos a correr el sevidor NFS
## 3. USAR SERVIDOR NFS
sudo apt install nfs-common -y
-Ahora creamos los clientes con el comando
- docker run -itd --privileged=true --net=host d3fk/nfs-client
- docker exec -it {practical_joliot} sh (sudo docker ps -a)
- Y luego para acceder al carpeta compartida del servidor accedemos a la carpeta mnt y colocamos:
- Pero para esto hay que saber a que ip debemos acceder a la nfs y colocamos
- docker inspect continer nfs
- sudo mount -v -o vers=4,loud 172.0.18.2:/ /mnt/nfs-1
- Creamos un directorio para probar 
- mkdir prueba1
- Y luego para comprobar eso
- sudo docker exec -it nfs /bin/bash
- Y accedemos a la carpeta compartida del servidor
- Y ahí estara el directorio
