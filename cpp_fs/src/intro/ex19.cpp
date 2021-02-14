#include <iostream>

struct X
{
    explicit X(); //initialization function without parameters is named 
                  //defult constructor (ofter abbreviated as: Ctor)

    explicit X(int a_, int b_ = 8); //regular (non defult) Ctor

    ~X(); //deinitialization function is called destractor (Dtor)

    X(const X& other_); //copy initialization function is called 
                        //copy constructor or CCtor

    X& operator = (const X& other_); //assignment operator

    int m_a;
    const int m_b;
};

X::X(): m_a(3), m_b(4)  //implementation of the default Ctor. Why the X::X? 
                        //the code after the colon is called an initialization list
{
    // m_a = 3;
  //  m_b = 4;
    std::cout << "this:" << this <<
                " X default Ctor. m_a:" << m_a <<
                " m_b:" << m_b << std::endl;
}

X::X(int a_, int b_): m_a(a_), m_b(b_) //implementation of the second Ctor
{
    std::cout << "this:" << this <<
                " X int int Ctor. m_a:" << m_a <<
                " m_b:" << m_b << std::endl;
}

X::X(const X& other_): m_a(other_.m_a), m_b(other_.m_b) 
//implementation of the copy Ctor
{
    std::cout << "this:" << this <<
                " X copy Ctor. m_a:" << m_a <<
                " m_b:" << m_b << std::endl;
}

X& X::operator=(const X& other_)
{
    m_a=other_.m_a;
    //m_b=other_.m_b;
    std::cout << "this:" << this <<
                " X assignment operator. m_a:" << m_a <<
                "does not change m_b:" << m_b << std::endl;
    return *this;
}

X::~X()
{
    std::cout << "this:" << this <<
                " X Dtor. m_a:" << m_a <<
                " m_b:" << m_b << std::endl;
}

int main()
{
    X x1;
    X x2(7);
   // X *px = new X(x2);
    //X x3(9, 10);
   // X x4(x1);

  //  x1 = x3;

	
//    delete px; px = 0;

    return 0;
}