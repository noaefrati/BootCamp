#include <iostream>
#include <stdlib.h>

using namespace std;

float add(int lhs, int rhs);
float add(double lhs, double rhs);
float add(float lhs, float rhs);

int 
main(void)
{
    cout << "Main calls add(1, 2)" << endl;
    float sum = add(1, 2);
    cout << "result of add(1, 2) is: " << sum << endl;

    cout << "Main calls add(1.5, 2.5)" << endl;
    sum = add(1.5, 2.5);
    cout << "result of add(1.5, 2.5) is: " << sum << endl;

    cout << "Main calls add(float(1.5), float(2.5))" << endl;
    sum = add(float(1.5), float(2.5));
    cout << "result of add(float(1.5), float(2.5)) is: " << sum << endl;

    return 0;
}

float 
add(int lhs, int rhs)
{
    cout << "inside int addition" <<endl;
    return lhs + rhs;
}

float 
add(double lhs, double rhs)
{
    cout << "inside double addition" <<endl;
    return lhs + rhs;
}

float 
add(float lhs, float rhs)
{
    cout << "inside float addition" <<endl;
    return lhs + rhs;
}

