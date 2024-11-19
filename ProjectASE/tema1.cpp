#include <iostream>
#include <cstring>
using namespace std;

// Tema1. Clasa Autobuz;
class Autobuz
{
private:
    static int nrAutobuze;
    const int idAutobuz;
    int capacitate;
    int nrPersoaneImbarcate;
    char *producator;

public:
    // Constructor fara parametrii;
    Autobuz() : idAutobuz(nrAutobuze++), capacitate(0), nrPersoaneImbarcate(0)
    {
        this->producator = new char[strlen("Unknown") + 1];
        strcpy(this->producator, "Unknown");
    }
    // Constructor cu parametrii;
    Autobuz(int cap, int nrPers, const char *prod) : idAutobuz(nrAutobuze++)
    {
        if (cap >= 0)
            this->capacitate = cap;
        if (nrPers <= cap)
        {
            this->nrPersoaneImbarcate = nrPers;
        }
        else
        {
            nrPers -= cap;
            cout << "Autobuzul este aglomerat. " << "Are o supracapacitate de: " << nrPers << " persoane " << "; Autobuzul: " << this->idAutobuz << endl;
            this->nrPersoaneImbarcate = cap;
            cout << "Capacitatea a fost redusa la numarul de persoane imbarcate.\n";
        }
        this->producator = new char[strlen(prod) + 1]; // alocare dinamica a memorie pentru string literal char *producator;
        strcpy(this->producator, prod);
    }
    // Constructorul de copiere;
    Autobuz(const Autobuz &bus) : idAutobuz(nrAutobuze++)
    {
        this->capacitate = bus.capacitate;
        this->nrPersoaneImbarcate = bus.nrPersoaneImbarcate;
        this->producator = new char[strlen(bus.producator) + 1]; // aloca dinamica a memorie pentru string literal char *producator;
        strcpy(this->producator, bus.producator);
    }
    ~Autobuz()
    {
        if (this->producator != NULL)
        {
            delete[] producator;
            cout << "Destructor chemat !!! \n";
        }
    }
    Autobuz &operator=(const Autobuz &atb)
    {
        if (this != &atb) // evita auto-atribuirea;
        {
            this->capacitate = atb.capacitate;
            this->nrPersoaneImbarcate = atb.nrPersoaneImbarcate;
            delete[] producator;
            this->producator = new char[strlen(atb.producator) + 1];
            strcpy(this->producator, atb.producator);
        }
        return *this; // returneaza referinta la obiectul Autobuz, evitand copierea obiectului
    }
    // Overloading operator <<
    friend ostream &operator<<(ostream &oStream, const Autobuz &autobuz)
    {
        oStream << "Autobuz ID: " << autobuz.idAutobuz
                << " ; Capacitatea autobuzului: " << autobuz.capacitate
                << " ; Numarul de persoane imbarcate: " << autobuz.nrPersoaneImbarcate
                << " ; Producator: " << (autobuz.producator ? autobuz.producator : "Unknown Company") << " ; ";
        return oStream;
    }

    bool operator>(const Autobuz &atb)
    {
        return this->capacitate > atb.capacitate;
    }
    // operator cast to int;
    operator int()
    {
        return this->nrPersoaneImbarcate;
    }
    // Getter and Setter;
    int getCapacitate() const
    {
        return this->capacitate;
    }
    void setCapacitate(int newCapacitate)
    {
        if (newCapacitate >= this->nrPersoaneImbarcate)
        {
            this->capacitate = newCapacitate;
            cout << "Noua capacitate a autobuzului a fost setata la: " << this->capacitate << endl;
        }
        else
            cout << "Noua capacitate nu poate fi mai mica decant numarul de persoane. \n";
    }

    int getPersoaneImbarcate() const
    {
        return this->nrPersoaneImbarcate;
    }
    void setPersoaneImbarcate(int pers)
    {
        if (pers <= this->capacitate)
        {
            this->nrPersoaneImbarcate = pers;
            cout << "Autobuzul are capacitatea admisa. \n";
        }
        else if (pers > this->capacitate)
        {
            this->nrPersoaneImbarcate = this->capacitate;
            cout << "Autobuzul are peste capacitatea admisa. " << "Autobuzul se opreste. \n";
            cout << (pers - this->capacitate) << " de persoane se vor da jos la oprire /in statie. \n";
        }
    }
    int getNumarLocuriLibere()
    {
        int locuriLibere = this->capacitate - this->nrPersoaneImbarcate;
        return locuriLibere;
    }
};

// Initializare membru/atribut static;
int Autobuz::nrAutobuze = 0;

int main()
{
    Autobuz autobuz1;
    Autobuz autobuz2(35, 25, "Dac-112UDM"); // creare instante de obiecte;
    Autobuz autobuz3(85, 95, "Mercedes");
    Autobuz autobuz4(55, 44, "Roman112U");
    Autobuz autobuz5(autobuz4); // copy constructor called;
    cout << autobuz1 << endl;
    cout << autobuz2 << endl;
    cout << autobuz3 << endl;
    cout << autobuz4 << endl;
    cout << endl;
    cout << "Constructorul de copiere chemat !!! \n";
    cout << autobuz5 << endl;
    autobuz5.setCapacitate(65);
    autobuz5.setPersoaneImbarcate(53);
    cout << "Capacitatea autobuzului este de: ->> " << autobuz5.getCapacitate() << " locuri pe scaune" << endl;
    cout << "In autobuz sunt imbarcate : ->> " << autobuz5.getPersoaneImbarcate() << " de persoane" << endl;
    cout << autobuz5 << endl;
    cout << endl;
    cout << "<< Overloading operator (=) >>\n";
    autobuz1 = autobuz5; // overloading operator (=);
    cout << autobuz1 << endl;
    cout << "Locuri ramase libere in autobuz: -->> " << autobuz1.getNumarLocuriLibere() << " locuri." << endl;
    int implicitNrPersoaneImbarcate = autobuz1;
    int explicitNrPersoaneImbarcate = int(autobuz1);
    cout << "Numar de persoane imbarcate in autobuz: " << implicitNrPersoaneImbarcate << " , conversie implicita.\n";
    cout << "Numar de persoane imbarcate in autobuz: " << explicitNrPersoaneImbarcate << " , conversie explicita. \n";
    cout << endl;
    cout << "<< Overloading operator (>) >>\n";
    if (autobuz3 > autobuz5)
    {
        cout << "Autobuzul3 are mai mare capacitate decat Autobuzul5. " << autobuz3.getCapacitate() << endl;
    }
    else
    {
        cout << "Autobuzul5 are capacitate mai mare decat Autobuzul3. " << autobuz5.getCapacitate() << endl;
    }
    cout << endl;
    cout << "Testare autobuz aglomerat. \n";
    Autobuz atb(95, 100, "Tesla-ROCAR-EH99");
    atb.setCapacitate(120);
    cout << atb << endl;
    atb.setPersoaneImbarcate(122);
    cout << atb << endl;
    cout << "Numar locuri libere: -->> " << atb.getNumarLocuriLibere() << endl;

    return 0;
}
