# Nombre del directorio de origen
SRCDIR = src

# Nombre del directorio de binarios
BINDIR = bin

# Nombres de los archivos fuente
SRCFILES = $(SRCDIR)/clientes2.cpp \
           $(SRCDIR)/Operaciones.cpp \
           $(SRCDIR)/main2.cpp

# Nombre del archivo ejecutable
TARGET = $(BINDIR)/GestionBancaria.exe

# Compilador
CXX = g++

# Flags del compilador
CXXFLAGS = -lsqlite3

# Comando por defecto
all: build run

# Regla para construir el archivo ejecutable
build: $(SRCFILES) | $(BINDIR)
	$(CXX) $(SRCFILES) -o $(TARGET) $(CXXFLAGS)

# Crear el directorio de binarios si no existe
$(BINDIR):
	mkdir -p $(BINDIR)

# Regla para ejecutar el programa
run: $(TARGET)
	./$(TARGET)

# Regla para limpiar archivos generados
clean:
	rm -f $(BINDIR)/*