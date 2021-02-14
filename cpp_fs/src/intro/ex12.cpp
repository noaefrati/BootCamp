#include <iostream>
using namespace std;

namespace useless
{
    unsigned int g_wasteful[400];
    extern int g_notthere;
    void Foo() { cout << " FOO 1 ! " << endl; }

    namespace wasteoftyme
    {
        void Foo(){}
    }
} // namespace useless

namespace stupid
{
    void Foo() { cout << " FOO stupid ! " << endl; }
    void Bar() { cout << " BAR stupid ! " << endl; }
    void DoNothing(unsigned int) { cout << " DoNothing stupid ! " << endl; }
} // namespace stupid

namespace useless
{
    void DoNothing(int) { cout << " DoNothing useless ! " << endl; }
} // namespace useless

using namespace useless;

void DoStuff()
{
    stupid::Bar();
    Foo();//useless
    using stupid::Foo;
    Foo();//stupid
    DoNothing(g_wasteful[3] + 1); //useless
}

void Foo()
{
    cout << "im Foo" << endl;
}

using namespace stupid;

namespace comeon = useless :: wasteoftyme;

void DoMoreStuff()
{
   using comeon::Foo;
// I added the using in 50 without it, it doesn't know what to use
    Foo(); //wasteoftyme
    Bar();
    DoNothing(g_wasteful[3] + 1); //stupid because of the type
}

namespace useless
{
    void DoUselessStuff()
    {
        DoNothing(g_wasteful[3] + 1);
    }
} // namespace useless

int main()
{
    DoMoreStuff();
    DoUselessStuff();
    stupid :: Foo();
    useless :: Foo();
    :: Foo();//global

    return (0);
}