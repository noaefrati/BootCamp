#include <iostream>
#include <typeinfo>

using namespace std;

template<typename T>
void foo(T t)
{
	std::cout << t << " Generic foo for " << typeid(t).name() << std::endl;
}
template<>
void foo<int>(int t)
{
	std::cout << t << " Specialized foo (for int params)\n";
}

int main()
{
	std::cout << " calling foo int :\n";
	foo(4.2);
	std::cout << " calling foo int :\n";
	foo(5);
	std::cout << " calling foo template :\n";
	foo<int>(5);
	return 0;
}	