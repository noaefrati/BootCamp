
OBJs =  shuff.o shuff_and_sort_utils.o
INCLUDE = shuff_and_sort_utils.h
TARGET = shuff.out

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -I include/

$(TARGET) : $(OBJs) 
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJs) -pthread
		
$(OBJs) : $(INCLUDE)

.PHONY: clean
clean : 
	-rm shuff.out shuff.o shuff_and_sort_utils.o 

