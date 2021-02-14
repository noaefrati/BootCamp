#include <dlfcn.h>
#include <assert.h>
#include <cstddef>
#include <cstdio>

typedef void (func_t)(void);

int main(int argc, char const *argv[])
{
    func_t *func = NULL;
    void *handle = NULL;
	void *ptr = NULL;
	int a =9;
	
    assert(2 < argc);

    handle = dlopen(argv[1], RTLD_LAZY);
    if (NULL == handle)
    {
    	printf("Unable to open DLL\n");
    	return -1;
    }
    ptr = dlsym(handle, argv[2]);
     if (NULL == ptr)
    {
    	printf("Not found\n");
    	return -1;
    }
    
	func = (func_t *) ptr;
    func();

    dlclose(handle);

    return (0);
}
