#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
// Class Desktop;
class Desktop
{
private:
    int RAM;
    char *brand;

public:
    // constructor implicit;
    Desktop() : RAM(0), brand(nullptr) {}
    // constructor cu parametrii;
    Desktop(int RAM, const char *prod) : RAM(RAM)
    {
        this->brand = new char[strlen(prod) + 1];
        strcpy(this->brand, prod);
    }
    // constructor copiere;
    Desktop(const Desktop &copy) : RAM(copy.RAM)
    {
        if (copy.brand != nullptr)
        {
            this->brand = new char[strlen(copy.brand) + 1];
            strcpy(this->brand, copy.brand);
        }
        else
        {
            this->brand = nullptr;
        }
    }
    // Operator de atribuire (=);
    Desktop &operator=(const Desktop &d3)
    {
        if (this != &d3)
        {
            delete[] this->brand;
            this->RAM = d3.RAM;
            if (d3.brand != nullptr)
            {
                this->brand = new char[strlen(d3.brand) + 1];
                strcpy(this->brand, d3.brand);
            }
            else
            {
                this->brand = nullptr;
            }
        }
        return *this;
    }
    // overloading operator (+);
    Desktop operator+(int addRAM)
    {
        Desktop temp = *this;
        temp.RAM += addRAM;
        return temp;
    }
    // Overloading operator(-);
    Desktop operator-(int scadeRAM)
    {
        Desktop temp = *this;
        temp.RAM -= scadeRAM;
        return temp;
    }
    // Overloading operator(+=);
    Desktop &operator+=(int addRAM)
    {
        this->RAM += addRAM;
        return *this;
    }
    // getter si setter;
    int getRAM() const
    {
        return this->RAM;
    }
    void setRAM(int setRAM)
    {
        this->RAM = setRAM;
    }
    // destructor;
    ~Desktop()
    {
        cout << "Destructor Clasa de Baza Desktop chemat..." << endl;
        if (this->brand != nullptr)
        {
            delete[] this->brand;
        }
    }
    friend ostream &operator<<(ostream &os, const Desktop &d1)
    {
        os << "Numarul de RAM, Desktop: -->> " << d1.RAM << " MegaBytes "
           << "; Brand Desktop: -->> " << d1.brand << endl;
        return os;
    }
    friend istream &operator>>(istream &in, Desktop &d2)
    {
        cout << "Input Numar de RAM: ";
        in >> d2.RAM;
        if (d2.brand != nullptr)
        {
            delete[] d2.brand;
            d2.brand = nullptr;
        }
        char buffer[40];
        cout << "Input Name Desktop: -->> ";
        in >> buffer;
        d2.brand = new char[strlen(buffer) + 1];
        strcpy(d2.brand, buffer);
        return in;
    }
    // friend function;
    friend Desktop suma(Desktop &desktop1, Desktop &desktop2);
};

Desktop suma(Desktop &desktop1, Desktop &desktop2)
{
    Desktop Sum = desktop1;
    Sum.RAM += desktop2.RAM;
    return Sum;
}

// class template;
template <class T>
T substract(T x, T y)
{
    return x - y;
}

// Class template Laptop; T-> placeholder pentru orice tip de data pentru variabile membre a clasei, functiile membre a clasei
template <class T>
class Locatie
{
private:
    int numarLocatie;
    T *vector;

public:
    // constructor implicit;
    Locatie() : numarLocatie(0), vector(nullptr) {}
    // constructor cu parametrii;
    Locatie(int nrLocatie, T *vector) : numarLocatie(nrLocatie)
    {
        this->vector = new T[nrLocatie];
        for (int i = 0; i < nrLocatie; i++)
        {
            this->vector[i] = vector[i];
        }
    }
    ~Locatie()
    {
        cout << "Class Template Locatie chemat....." << endl;
        if (this->vector != nullptr)
        {
            delete[] this->vector;
        }
    }
    void display() const
    {
        cout << "Camerele cu numerele, din locatia cu nr. " << this->numarLocatie << " sunt " << endl;
        for (int i = 0; i < this->numarLocatie; i++)
        {
            cout << this->vector[i] << endl;
        }
    }
};

void afisareVector(vector<int> lista)
{
    vector<int>::iterator it;
    cout << " Vectorul este: ->> : ";
    for (it = lista.begin(); it != lista.end(); it++)
    {
        cout << " " << *it;
    }
    cout << endl;
}

int main()
{
    // Desktop d;
    // cin >> d;
    // cout << d << endl;

    Desktop d1(1000, "Intel");
    Desktop d2(2000, "Mac OS");
    Desktop d3(3000, "Pac Man");
    cout << d1 << endl;
    cout << d2 << endl;
    cout << d3 << endl;
    d1 += 1500;
    d2 = d2 + 1000;
    cout << endl;
    cout << "Dupa adaugare RAM: " << endl;
    cout << "Desktop 1 are un spatiu : " << d1.getRAM() << " MegaBytes" << endl;
    cout << "Desktop 2 are un spatiu : " << d2.getRAM() << " MegaBytes" << endl;
    cout << endl;
    cout << suma(d1, d3);
    // Class Template;
    Locatie<int> loc1(2, new int[2]{1001, 1002}); // creare obiect din clasa template Locatie;
    loc1.display();

    int nrLocatie = 3;
    int *vectorLocatii = new int[nrLocatie]{301, 302, 303};
    Locatie<int> loc2(nrLocatie, vectorLocatii);
    loc2.display();

    nrLocatie = 2;
    Desktop *vectorDesktop = new Desktop[nrLocatie]{d2, d3};
    Locatie<Desktop> locatie(nrLocatie, vectorDesktop);
    locatie.display();

    delete[] vectorLocatii;
    delete[] vectorDesktop;

    vector<int> vectori;
    for (int i = 0; i < 7; i++)
    {
        vectori.push_back(i);
    }
    vectori.push_back(10);
    vectori.push_back(100);
    vectori.pop_back();
    vectori.at(3) = 13;
    vectori.size() - 1;
    cout << vectori.at(3) << endl;
    afisareVector(vectori);

    cout << substract<float>(3.3, 5.5) << endl;
    return 0;
}