#include <iostream>
#include <string.h>
#include "ex15.hpp"

using namespace std;


int main()
{
	int arr[12];
	
	std:: cout << Max<int>(3, 5) <<" " << Max<double>(3.7, 12.9) << " ";
	std:: cout << Max<int *>(arr, arr + 8) << std::endl;
	std:: cout << Max('a', 'b') << std :: endl;
	std:: cout << Max("hello", "world") << std :: endl;
	std:: cout << strcmp("hello", "world") <<std::endl;
	
	std:: cout << Max<int>(3, 5) <<" " << Max<double>(3.7, 12.9) << " ";
	std:: cout << Max<int *>(arr, arr + 8) << std::endl;
	std:: cout << Max('a', 'b') << std :: endl;
	std:: cout << Max("hello", "world") << std :: endl;
	std:: cout << strcmp("hello", "world") <<std::endl;
	return 0;
}