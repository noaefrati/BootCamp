#how to run on terminal : make test TARGET=avl (avl th prefix of the file)
#lib in debug mode-                   make debug TARGET= 
#lib in release mode-                 make release TARGET= 
#lib + test file in debug mode-       make test TARGET= 
#lib + test file in relase mode-      make test_release TARGET= 


CC = gcc
FLAGS = -ansi -pedantic-errors -Wall -Wextra -g -I include
DEBUG_FLAGS = $(FLAGS) -g
RELEASE_FLAGS = $(FLAGS) -DNDEBUG -O3
SOFLAGS = -c -fPIC
LDFLAGS = -shared
RPATH = /home/user/noa-efrati/git/ds/lib
TARGET=
OBJ=  $(patsubst src/%.c,obj/debug/%.o,$(wildcard src/*.c))
LIBD = lib/libdsD.so
LIBR = lib/libdsR.so

### MAIN TARGETS
bin/release/$(TARGET).out: test/$(TARGET)_test.c
	$(CC) $(RELEASE_FLAGS) -o $@ $^ $(LIBR) -L$(RPATH) -Wl,-rpath=$(RPATH) -lm

bin/debug/$(TARGET).out: test/$(TARGET)_test.c
	$(CC) $(DEBUG_FLAGS) -o $@ $^ $(LIBD) -L$(RPATH) -Wl,-rpath=$(RPATH) -lm

$(LIBD): $(OBJ)
	$(CC) $(DEBUG_FLAGS) $(LDFLAGS) -o $@ $^
	
$(LIBR): obj/release/*.o
	$(CC) $(RELEASE_FLAGS) $(LDFLAGS) -o $@ $^
		
obj/debug/%.o: src/%.c
	$(CC) $(DEBUG_FLAGS) $(SOFLAGS) -o $@ $<
	
obj/release/%.o: src/%.c
	$(CC) $(RELEASE_FLAGS) $(SOFLAGS) -o $@ $<


### PHONY TARGETS
.PHONY: debug 
debug: $(LIBD)

.PHONY: release 
release: $(LIBR)

.PHONY: test
test: $(LIBD) bin/debug/$(TARGET).out 

.PHONY: test_release
test_release: $(LIBR) bin/release/$(TARGET).out 

.PHONY: all
all: debug release

.PHONY: clean	
clean:
	rm bin/release/* bin/debug/* obj/debug/*.o obj/release/*.o lib/*.so


## simple Makefile
#OBJs =  src/stack.o src/calculator.o test_other/calculator_test.o -lm
#INCLUDE = include/stack.h include/calculator.h 
#TARGET = calculator.out

#CC = gcc
#CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -I include/

#$(TARGET) : $(OBJs) 
#	$(CC) -o $(TARGET) $(OBJs)
#		
#$(OBJs) : $(INCLUDE)

#.PHONY: clean
#clean : 
#	-rm $(TARGET) $(OBJs) 

