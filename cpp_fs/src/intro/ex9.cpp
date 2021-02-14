/*Type Conversion:*/
/*#include<iostream>  
using namespace std;  
 
void function(float x); 
void function(int y);  
 
void function(float x)  
{  
    std::cout << "Value of x is : " <<x<< std::endl;  
}  
 
void function(int y)  
{  
    std::cout << "Value of y is : " <<y<< std::endl;  
}  
 
int main()  
{  
    function(3.4);
    function(34);  
    return 0;  
}*/
/*Function with Default Arguments:*/
/*
#include<iostream>  
using namespace std;  
void function(int);  
void function(int,int);  
 
void function(int x)  
{  
    std::cout << "Value of x is : " <<x<< std::endl;  
}  
void function(int y,int z=12)  
{  
    std::cout << "Value of y is : " <<y<< std::endl;  
    std::cout << "Value of z is : " <<z<< std::endl;  
}  
int main()  
{  
    function(12);  
    
    return 0;  
}
*/
/*Function with pass by reference*/
#include <iostream>  
using namespace std;  
void function(int);  
void function(int &);   
 
void function(int a)  
{  
std::cout << "Value of a is : " <<a<< std::endl;  
}  
void function(int &b)  
{  
std::cout << "Value of b is : " <<b<< std::endl;  
}  
 
int main()  
{  
int x=10;  
function(x); 
return 0;  
}
