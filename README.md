# 🚀 Servidor HTTP en C++

Un servidor HTTP/1.1 minimalista escrito en C++ que soporta métodos GET, HEAD y POST, con manejo de archivos estáticos y concurrencia básica.

## 📦 Estructura del Proyecto
Proyecto_HTTP_Server/
├── src/
│ ├── server.cpp # Lógica principal del servidor
│ ├── request_parser.cpp # Análisis de solicitudes HTTP
│ ├── response_builder.cpp # Generación de respuestas
│ └── logger.cpp # Registro de eventos
├── include/ # Headers
├── www/ # Archivos estáticos (HTML, imágenes)
├── Makefile # Configuración de compilación
└── README.md # Este archivo

## 🧠 Módulos Principales

### 1. `server.cpp`
- **Responsabilidad**: Gestión de sockets y bucle principal.
- **Funciones clave**:
  - `main()`: Configura el socket, acepta conexiones y delega a hilos.
  - `handle_client()`: Procesa cada solicitud entrante.

### 2. `request_parser.cpp`
- **Qué hace**: Parsea solicitudes HTTP crudas.
- **Métodos soportados**:
  ```cpp
  GET /index.html HTTP/1.1
  HEAD /test HTTP/1.1
  POST /submit HTTP/1.1
  
### 3. response_builder.cpp
Respuestas generadas:

200 OK (archivos encontrados)

404 Not Found (archivos no existentes)

400 Bad Request (solicitudes malformadas)

### 4. logger.cpp
Registra en formato:

[TIMESTAMP] [GET] /index.html - 200

🛠️ Compilación
Requisitos
 - GCC/G++ ≥ 9.0
 - Make

▶️ Ejecución
#### Localmente:
bash
./server <PUERTO> <ARCHIVO_LOG> <CARPETA_WWW>
Ejemplo:
./server 8080 server.log ./www

#### En AWS EC2:
Conéctate via SSH:

bash
ssh -i "tu-key.pem" ec2-user@<IP_PUBBLICA>
Compila y ejecuta en background:

bash
nohup ./server 80 /var/log/server.log /home/ec2-user/Proyecto_HTTP_Server/www/ &

