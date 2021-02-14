#include <iostream>
using namespace std;

void Foo(const double &param)
{
    cout << param << endl;
    cout << &param << endl;
}

void Bar(double &param)
{
    cout << param << endl;
    cout << &param << endl;
}
void Int(int &)
{
    ;
}

int main()
{
    int x = 10;
    char ch = 'a';
	int &xx = x;
	
    unsigned int unint = 98989;
	  cout << " x address "<< &x << endl;
	   cout << " reference address "<< &xx << endl;
	    cout << " reference value "<< xx << endl;
		
    Foo(x);
  //  Foo(ch);
	//Bar((double&)x);
    Bar(x);
    //Int(reinterpret_cast<int &>(unint));

    return 0;
}