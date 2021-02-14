/* gcc dynso_test.c -ldl -o dynso_test
./dynso_test so1.so Bla*/
#include <dlfcn.h>/*dlopen, dlsym*/

#include <stdio.h>/*printf*/
typedef void (func_t) (void);

int main(int argc, char *argv[])
{
	void *lib_handle = NULL;
	func_t *func = NULL;
	void *ptr = NULL;
  	lib_handle = (void *)dlopen(argv[1], RTLD_LAZY); 
  	 if(NULL != lib_handle) 
  	{
    
		ptr= dlsym(lib_handle, argv[2]);
		func = (func_t *)ptr;
		if(NULL != func)
		{
		  func();
		}
		else
		{
		  printf("Function entry not found in DLL");
		}
		dlclose(lib_handle);
  	}
  else
  {
    printf("Unable to open DLL");
  }
 
 	return (0);
}
