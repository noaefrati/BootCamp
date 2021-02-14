
OBJs =  src/multithread_cnt.o -lm
INCLUDE = include/multithread_cnt.h
TARGET = multithread_cnt.out

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -I include/

$(TARGET) : $(OBJs) 
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJs) -pthread
		
$(OBJs) : $(INCLUDE)

.PHONY: clean
clean : 
	-rm multithread_cnt.out src/multithread_cnt.o  

