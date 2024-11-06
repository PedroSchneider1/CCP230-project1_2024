# Nome do executável
TARGET_INVESTOR = exchange.exe
TARGET_ADM = adm.exe

# Compilador
CC = gcc

# Flags
INCLUDE_DIR = ./source/include
CFLAGS = -Wall -I$(INCLUDE_DIR)

# Lista de arquivos fonte
INV_DIR = ./source/srcInvestidor
INV_C_SOURCE = $(wildcard ./source/srcInvestidor/*.c)
ADM_C_SOURCE = $(wildcard ./source/srcAdm/*.c)
DEFAULT_SOURCE = $(INV_DIR)/verificaCPF.c $(INV_DIR)/limpaBuffer.c $(INV_DIR)/atualizarCotacao.c $(INV_DIR)/cadastro.c

H_SOURCE = $(wildcard ./source/include/*.h)

# Variavel para limpeza
RM = rm -f

# Regra principal: compilar o programa
# Obs.: '$@' identifica o target
#		'$^' identifica os pre-requisitos (sources)
all: $(TARGET_INVESTOR) $(TARGET_ADM)

$(TARGET_INVESTOR): $(INV_C_SOURCE) $(H_SOURCE)
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET_ADM): $(ADM_C_SOURCE) $(DEFAULT_SOURCE) $(H_SOURCE)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para limpar os arquivos gerados
clean:
	@ $(RM) *.bin $(TARGET_INVESTOR) $(TARGET_ADM)

.PHONY: all clean
