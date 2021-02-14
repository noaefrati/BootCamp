
OBJs =   src/stack.o src/calculator.o test/calculator_test.o -lm
INCLUDE = include/calculator.h include/stack.h
TARGET = calculator.out

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -I include/

$(TARGET) : $(OBJs) 
	$(CC) -o $(TARGET) $(OBJs)
		
$(OBJs) : $(INCLUDE)

.PHONY: clean
clean : 
	-rm $(TARGET) $(OBJs) 

