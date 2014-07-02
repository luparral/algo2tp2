# Compilador que será utilizado
CC=g++

# flags de compilación
CFLAGS=-g -Wall

# flags de linkeo
LDFLAGS=

# Agregar acá los archivos .cpp a compilar
SOURCES= titulo.cpp promesa.cpp conjEstNat.cpp wolfie.cpp Driver.cpp test.cpp 

# Objetos que serán generados (no tocar)
OBJECTS=$(SOURCES:.cpp=.o)

# Nombre del ejecutable a generar
EXECUTABLE=test

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
