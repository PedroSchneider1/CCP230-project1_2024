# Nome do executável
TARGET = exchange.exe

# Compilador
CC = gcc

# Flags
CFLAGS = -Wall

# Lista de arquivos fonte
C_SOURCE=$(wildcard ./source/*.c)
H_SOURCE=$(wildcard ./source/*.h)

# Variavel para limpeza
RM = rm -f

# Regra principal: compilar o programa
$(TARGET): $(C_SOURCE) $(H_SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(C_SOURCE)

# Regra para limpar os arquivos gerados
clean:
	@ $(RM) $(TARGET)

.PHONY: all clean