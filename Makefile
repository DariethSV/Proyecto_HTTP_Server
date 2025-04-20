# ---------------- Configuración del compilador ----------------
CC      := g++
CFLAGS  := -std=c++11 -Wall -Iinclude

# ---------------- Rutas y archivos ----------------
SRCDIR  := src
INCDIR  := include
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp, $(SRCDIR)/%.o, $(SOURCES))
EXEC    := server

# ---------------- Regla por defecto ----------------
all: $(EXEC)

# ---------------- Enlazado del ejecutable ----------------
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

# ---------------- Compilación de cada .cpp a .o ----------------
$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# ---------------- Limpieza ----------------
clean:
	rm -f $(SRCDIR)/*.o $(EXEC)
