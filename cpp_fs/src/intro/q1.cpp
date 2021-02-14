#include <iostream>
#include <typeinfo>
#include <string>
#include <memory>
#include <cstring>
#include <cxxabi.h>

using namespace std;


struct X
{
int data;
};

int const *foo(int *v)
{
    return NULL;
}
           //int which is const
   const  int i = 0;   
    int const i2 = 0;       // const int same as 1
    int const *i3 = 0;      // pointer to const int
    struct X *const p = 0; //const pointer to X
    struct X const x1 = {0}; //
    const struct X *p1 = 0;
    const struct X **const p2= NULL; // X
    int const *(*const f)(int *) = foo;

int main(int argc, char const *argv[])
{
    cout << "const  int is " << typeid(i).name() << std::endl;
    cout << "int const i is " << typeid(i2).name() << std::endl;
    cout << "int const *i3 is " << typeid(i3).name() << std::endl;
    cout << " struct X *const p is " << typeid(p).name() << std::endl;
    cout << "struct X const x1 is " << typeid(x1).name() << std::endl;
    cout << "const struct X *p1; is " << typeid(p1).name() << std::endl;
    cout << "const struct X **const p2; is " << typeid(p2).name() << std::endl;
    cout << "int const *(*const f)(int *) is " << typeid(f).name() << std::endl;
    return 0;
}
