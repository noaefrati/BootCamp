
OBJs =   src/sort.o  test/sort_test.o -lm
INCLUDE = include/sort.h 
TARGET = sort.out

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -I include/

$(TARGET) : $(OBJs) 
	$(CC) -o $(TARGET) $(OBJs)
		
$(OBJs) : $(INCLUDE)

.PHONY: clean
clean : 
	-rm $(TARGET) $(OBJs) 

