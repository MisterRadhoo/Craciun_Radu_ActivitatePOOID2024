#include <iostream>
using namespace std;

class Demo
{
public:
    int a, b; // data members
    Demo()
    {
        cout << "Default Constructor" << endl;
    }
    Demo(int a, int b) : a(a), b(b) // accesare data membrii
    {
        cout << "Parameterized Constructor values: " << a << " " << b << endl;
    }

} instance(50, 100); // create obj1;

int main()
{
    Demo instance; // create obj2;
    return 0;
}