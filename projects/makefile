#############################################################################
#																			#
#				makefile for watchdog										#
#																			#
#############################################################################

NAME = wd
SUB_NAME_1 = priority_queue
SUB_NAME_2 = task
SUB_NAME_3 = uid
SUB_NAME_4 = vector_ref
SUB_NAME_5 = heap

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -I ./include/ -iquote include
LDFLAGS = -shared

OBJ_PATH = obj/
LIB_PATH = lib/

.PHONY: client
client : lib/libwd_and_utils.so test/client.c
	$(CC) $(CFLAGS) -L./lib -Wl,-rpath=./lib \
	-o client.out $^ \
	-lwd_and_utils -pthread

.PHONY: watchdog_exe
watchdog_exe : src/watchdog_exe.c lib/libwd_utils.so
	$(CC) $(CFLAGS) -L./lib -Wl,-rpath=./lib -o watchdog_exe.out $^ -lwd_utils -pthread

lib/libwd_and_utils.so : obj/scheduler.o obj/priority_queue.o obj/task.o obj/uid.o obj/vector_ref.o obj/heap.o obj/wd.o obj/wd_utils.o
	$(CC) $(LDFLAGS) -o $@ $^


lib/libwd_utils.so : obj/wd_utils.o obj/scheduler.o  $(OBJ_PATH)$(SUB_NAME_1).o $(OBJ_PATH)$(SUB_NAME_2).o $(OBJ_PATH)$(SUB_NAME_3).o $(OBJ_PATH)$(SUB_NAME_4).o $(OBJ_PATH)$(SUB_NAME_5).o
	$(CC) $(LDFLAGS) -o $@ $^ 


obj/wd.o : src/wd.c  
	$(CC) $(CFLAGS) -c -fPIC -o $@ $^


obj/wd_utils.o : src/wd_utils.c
	$(CC) $(CFLAGS) -c -fPIC -o $@ $^ 
	

##data structures - utilities

obj/scheduler.o: src/scheduler.c
	$(CC) $(CFLAGS) -c -fPIC -o $@ $^

obj/priority_queue.o: src/priority_queue.c
	$(CC) $(CFLAGS) -c -fPIC -o $@ $^

obj/task.o: src/task.c
	$(CC) $(CFLAGS) -c -fPIC -o $@ $^
	
obj/uid.o: src/uid.c
	$(CC) $(CFLAGS) -c -fPIC -o $@ $^
	
obj/vector_ref.o: src/vector_ref.c
	$(CC) $(CFLAGS) -c -fPIC -o $@ $^	

obj/heap.o: src/heap.c
	$(CC) $(CFLAGS) -c -fPIC -o $@ $^
#############################################################################
#									PHONYS									#
#############################################################################

.PHONY: clean
clean : 
	rm obj/*.o lib/*.so client.out watchdog_exe.out

.PHONY: run_client
run_client:
	./client.out ./watchdog_exe.out

.PHONY: vlg
vlg:
	valgrind --leak-check=yes --track-origins=yes ./client.out ./watchdog_exe.out

#update git repository - ABSOLUTE PATH
.PHONY: gitp
gitp:
	cd ~/noa.efrati/; git add .; git commit -m "initial commit"; git push -u origin master; 
