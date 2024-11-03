#include <iostream>
#include <cmath>
using namespace std;

// Distanta euclidiana dintre doua puncte "a" si "b";
class DistanceCalculator; // forward declaration of the friend class;
// Definirea un Clasei Point,in  coordonate bidimensionale;
class Point
{
private:
    int a, b;

public:
    // Constructor care initializea membrii privati ai clasei Point, 2 parametrii de tip int cu valori implicite;
    Point(int a = 0, int b = 0) : a(a), b(b)
    {
    }
    // Overload (+) operator (adauga distanta), se face printr-o functie friend pentru accesare membrii privati;
    friend Point operator+(const Point &p1, const Point &p2)
    {
        Point temp;
        temp.a = p1.a + p2.a;
        temp.b = p1.b + p2.b;
        return temp;
    }
    // Overloard (-) operator (scade distanta);
    friend Point operator-(const Point &p1, const Point &p2)
    {
        return Point(p1.a - p2.a, p1.b - p2.b);
    }
    friend class DistanceCalculator; // declare clasa prieten;
    void display() const
    {
        cout << " <--> Point of coordinates: " << "a = " << a << " | " << "b = " << b << endl;
    }
};

class DistanceCalculator
{
public:
    static double calculateDistance(const Point &p1, const Point &p2)
    {
        int distanceA = p1.a - p2.a;
        int distanceB = p1.b - p2.b;
        return sqrt(distanceA * distanceA + distanceB * distanceB);
    }
};

int main()
{
    Point p1(20, 30);
    Point p2(40, 70);
    p1.display();
    p2.display();
    cout << endl;
    Point p3 = p1 + p2; // overloading (+)s operator
    p3.display();

    Point p4 = p1 - p2; // overloading (-) operator
    cout << "p4 (p1 - p2) ";
    p4.display();
    // calculare distance dintre instantele de obiect p1 si p2;
    double distance = DistanceCalculator::calculateDistance(p1, p2);
    cout << "Distance between p1 and p2 is: " << distance << endl;
    cout << DistanceCalculator::calculateDistance(p3, p4) << " <<---Distance Beetween p3 and p4 objects. ";

    return 0;
}