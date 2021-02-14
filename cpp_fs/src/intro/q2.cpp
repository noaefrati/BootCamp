#include<iostream>
using namespace std;


enum E {AA, BB,CC,DD};
enum E2 {TT, KK};
enum E e =CC;
 //enum E2 e2=AA;

E2 e22 = KK;
//++e;

int i = e;

int main(int argc, char const *argv[])
{
    printf("%d\n",e);
    return 0;
}

