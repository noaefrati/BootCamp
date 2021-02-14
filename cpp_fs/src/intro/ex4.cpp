#include <stdio.h>

typedef struct List List_t;
typedef struct Person Person_t;

struct List
{
    int list;
};

struct Person
{
    char age;
};

void *ll_find(List_t *ll, int key)
{
    return (NULL);
}

void foo(List_t *ll, int key, int age)
{
    void *vv = ll_find(ll, key);
   //long *cc = {0};
   Person_t *p = static_cast<Person_t*>(ll);
   p->age = age;
   // Person_t *p = (Person_t *)ll;
    //p->age = age;
    printf("%c\n", p->age);
}

int main()
{
   
   	List_t l = {10};
   	foo(&l, 0, 1);
    return (0);
}
