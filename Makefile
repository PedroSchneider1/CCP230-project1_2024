# Nome do executável
TARGET_INVESTOR = exchange.exe
TARGET_ADM = adm.exe

# Compilador
CC = gcc

# Flags
CFLAGS = -Wall -I./source/include

# Lista de arquivos fonte
INV_C_SOURCE = $(wildcard ./source/srcInvestidor/*.c)
H_SOURCE = $(wildcard ./source/*.h)

ADM_C_SOURCE = $(wildcard ./source/srcAdm/*.c)


# Variavel para limpeza
RM = rm -f

# Regra principal: compilar o programa
# Obs.: '$@' identifica o target
#		'$^' identifica os pre-requisitos (sources)
all: $(TARGET_INVESTOR) $(TARGET_ADM)

$(TARGET_INVESTOR): $(INV_C_SOURCE) $(H_SOURCE)
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET_ADM): $(ADM_C_SOURCE) $(H_SOURCE)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para limpar os arquivos gerados
clean:
	@ $(RM) *.bin $(TARGET_INVESTOR) $(TARGET_ADM)

.PHONY: all clean
