
OBJs =   src/dhcp.o test/dhcp_test.o -lm
INCLUDE = include/dhcp.h
TARGET = dhcp.out

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -I include/

$(TARGET) : $(OBJs) 
	$(CC) -o $(TARGET) $(OBJs)
		
$(OBJs) : $(INCLUDE)

.PHONY: clean
clean : 
	-rm $(TARGET) $(OBJs) 

