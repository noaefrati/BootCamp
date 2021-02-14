CC := gcc 
LIBFLAG := -fPIC -shared
LDFLAGS= -L/home/noa-efrati/watchdog/lib/debug -Wl,-rpath=/home/noa-efrati/watchdog/lib/debug
LRFLAGS=-L/home/noa-efrati/watchdog/lib/release -Wl,-rpath=/home/home/noa-efrati/watchdog/lib/release
DEBUG_FLAGS = -ansi -pedantic-errors -Wall -Wextra -g -pthread -I include/
REL_FLAGS = -ansi -pedantic-errors -Wall -Wextra -g  -pthread -I include/

#WATCH DOG USER

bin/debug/wd_user.out:  lib/debug/libdsD.so test/watchdog_test.c src/watchdog.c
	$(CC) $(DEBUG_FLAGS) $(LDFLAGS)  test/watchdog_test.c src/watchdog.c -o bin/debug/wd_user.out -ldsD
	
lib/debug/libdsD.so:src/heap.c src/priority_queue.c src/scheduler.c src/task.c src/thread_safe_uid.c src/vector_ref.c src/watchdog_utils.c
	$(CC) $(DEBUG_FLAGS)  $(LIBFLAG) src/heap.c src/priority_queue.c src/scheduler.c src/task.c src/thread_safe_uid.c src/vector_ref.c  src/watchdog_utils.c -o lib/debug/libdsD.so
	
bin/release/wd_user.out: lib/release/libdsR.so test/watchdog_test.c src/watchdog.c
	$(CC) $(DEBUG_FLAGS)  $(LRFLAGS) test/watchdog_test.c src/watchdog.c -o bin/release/wd_user.out -ldsR
		
lib/release/libdsR.so:src/heap.c src/priority_queue.c src/scheduler.c src/task.c src/thread_safe_uid.c src/vector_ref.c src/watchdog_utils.c
	$(CC) $(DEBUG_FLAGS) $(LIBFLAG) src/heap.c src/priority_queue.c src/scheduler.c src/task.c src/thread_safe_uid.c src/vector_ref.c  src/watchdog_utils.c -o lib/release/libdsR.so	

#WATCH DOG
bin/debug/wd.out:  lib/debug/libdsD.so src/watchdog_impl.c
	$(CC) $(DEBUG_FLAGS) $(LDFLAGS)  src/watchdog_impl.c -o bin/debug/wd.out -ldsD

bin/release/wd.out: lib/release/libdsR.so src/watchdog_impl.c
	$(CC) $(DEBUG_FLAGS) $(LRFLAGS)  src/watchdog_impl.c -o bin/debug/wd.out -ldsD



.PHONY: debug 
debug: lib/debug/libdsD.so

.PHONY: release 
release: lib/release/libdsR.so

.PHONY: test
test: lib/debug/libdsD.so bin/debug/wd_user.out bin/debug/wd.out

.PHONY: test_release
test_release: lib/release/libdsR.so bin/release/wd_user.out bin/release/wd.out


.PHONY: clean
clean:
	rm  bin/debug/*.out bin/debug/*.out lib/debug/*.so lib/release/*.so 
