# Introduccion a Sistemas Distribuidos

Repositorio de talleres y guias para la asignatura de Introduccion a los Sistemas Distribuidos de la Pontificia Universidad Javeriana. Contiene el codigo, las instrucciones y los archivos de despliegue necesarios para poner en practica distintos patrones de arquitectura distribuida usando contenedores y Kubernetes.

## Contenido

El repositorio esta organizado por patron. Cada carpeta incluye el codigo fuente, un Dockerfile cuando aplica, los manifiestos de Kubernetes y un documento de instrucciones en formato Word y PDF.

### Adapter

Muestra como integrar un servicio existente con otro sistema sin modificar su codigo original, por medio de una capa intermedia que traduce entre ambos. Incluye dos ejemplos: uno con MySQL, donde un adaptador expone un endpoint de salud que consulta la base de datos, y otro con Prometheus, donde se genera trafico de datos hacia Redis para poder visualizar metricas.

### Ambassador

Presenta un proxy local que se encarga de la comunicacion con un servicio remoto en nombre de la aplicacion principal, ocultando la complejidad de red y facilitando pruebas de carga contra un servicio expuesto en el clúster.

### Sidecar

Ilustra un proceso auxiliar que corre junto al proceso principal para dar soporte adicional sin mezclar responsabilidades, usando procesos hijos vigilados por un proceso padre.

### Publicador Suscriptor

Implementa el patron de mensajeria basado en eventos usando ZeroMQ. Un publicador emite datos y varios suscriptores los reciben de forma desacoplada, sin que el publicador conozca a sus consumidores.

### Proyecto Pequeño

Proyecto integrador que combina varios de los patrones anteriores en un sistema de biblioteca distribuido. Cuenta con un load manager que recibe solicitudes de clientes y coordina distintos actores de prestamo, devolucion y renovacion, comunicandose entre ellos mediante mensajeria. Todo el sistema esta dockerizado y cuenta con sus propios manifiestos de despliegue para Kubernetes.

## Requisitos

Para ejecutar los talleres se recomienda contar con:

1. Docker
2. Un clúster local de Kubernetes, por ejemplo minikube
3. kubectl configurado contra el clúster
4. CMake y un compilador de C++ para el Proyecto Pequeño y el Sidecar
5. Go para el Adapter de MySQL
6. Python con la libreria redis para el generador de datos de Prometheus

## Como usar este repositorio

Cada carpeta funciona de forma independiente. Se recomienda seguir el documento de instrucciones dentro de cada patron, que detalla paso a paso como construir las imagenes, aplicar los manifiestos de Kubernetes y verificar el funcionamiento del ejemplo. El Proyecto Pequeño incluye ademas scripts de apoyo para levantar el entorno, lanzar los actores y consultar los registros del sistema.

## Contexto academico

Este material se alimenta progresivamente con los codigos de los talleres de la asignatura, con el objetivo de que los estudiantes puedan experimentar de primera mano los patrones mas comunes en el diseño de sistemas distribuidos.
