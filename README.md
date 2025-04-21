# i. Introducción
Este proyecto implementa un servidor web compatible con HTTP/1.1 utilizando sockets TCP en C++. El servidor es capaz de manejar múltiples clientes de forma concurrente mediante hilos (std::thread) y soporta los métodos HTTP más comunes: GET, HEAD y POST. Además, incorpora manejo de errores, registro de solicitudes y una arquitectura modular para facilitar su mantenimiento y escalabilidad.

Este servidor fue desarrollado por estudiantes como parte de un proyecto académico de la Universidad EAFIT en el marco del curso de Telemática

# ii. Desarrollo / Implementación

## Arquitectura del proyecto

El proyecto está organizado de manera modular, con los siguientes componentes principales:

### Módulo principal (server.cpp): 

Inicializa el socket, escucha por conexiones entrantes y crea un hilo por cada cliente.

### thread_handle: 

Función responsable de manejar cada conexión, procesando la petición HTTP y generando la respuesta adecuada.

### request_parser.cpp: 

Se encarga de interpretar la línea de solicitud HTTP, extrayendo el método, el recurso solicitado y validando la estructura.

### response_builder.cpp: 

Genera respuestas HTTP válidas dependiendo del resultado del acceso al recurso solicitado.

### logger.cpp: 

Registra cada solicitud en un archivo log.txt con información como IP del cliente, método, recurso y código de estado.

### error_handler.cpp: 

Gestiona las respuestas de error (400 y 404).

# Funcionalidades implementadas

- Manejo de métodos GET, HEAD y POST.

- Manejo de errores 400 Bad Request y 404 Not Found.

- Servido de archivos desde una carpeta raíz (www/).

- Concurrencia con hilos para atender múltiples clientes simultáneamente.

- Registro de logs con hora, IP, método HTTP, recurso y código de estado.

- Modularización para facilitar pruebas y futuras mejoras.

# iii. Conclusiones

El desarrollo de este servidor web nos permitió afianzar conocimientos sobre el protocolo HTTP, el uso de sockets en C++ y la programación concurrente. A través de una arquitectura modular, fue posible dividir el trabajo y facilitar la implementación colaborativa del proyecto. La implementación exitosa de los métodos HTTP y del manejo de errores básicos demostró el funcionamiento correcto del servidor frente a solicitudes reales con herramientas como curl o navegadores web.

# iv. Referencias

- GeeksforGeeks - TCP Server-Client implementation in C

- man7 - socket(7)
