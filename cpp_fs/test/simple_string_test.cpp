#include <cstring>
#include <iostream>

#include "simple_string.hpp"

using namespace std;
using namespace i"lrd;


void Test1(void);

int main()
{
	Test1();
	return 0;
}
void Test1(void)
{
	String s1("hello world");
	String s2();
	String s3(s1);
	
	int  ans  = (s1.Length() == 11); 
	ans += (s2.Length() == 1);
	ans += (s3.Length() == 11);
	
	if (ans == 3)
	{
		cout << "length function succssed!"<<endl;
	}
	else
	{
		cout << " length function failed!"<< endl;
	}
	
	s1 = s2;
	ans = (s1.Length() == 1); 
	if (ans == 1)
	{
		cout << "operator = function succssed!"<<endl;
	}
	else
	{
		cout << " operator = function failed!"<< endl;
	}
	s2 = s3;
	
	ans = (s1.Length() == 11); 
	if (ans == 11)
	{
		cout << "operator = function succssed!"<<endl;
	}
	else
	{
		cout << " operator = function failed!"<< endl;
	}
	
	
}
