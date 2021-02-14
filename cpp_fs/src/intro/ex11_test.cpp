#include <dlfcn.h>
#include <assert.h>

typedef void (*func_t)(void);

int main(int argc, char const *argv[])
{
    func_t func = {0};
    void *handle = {0};

    assert(2 < argc);

    handle = dlopen(argv[1], RTLD_LAZY);
    *(void **)(&func) = dlsym(handle, argv[2]);

    func();

    assert(dlsym);

    dlclose(handle);

    return (0);
}
