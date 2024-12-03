#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Farmacie
{
private:
    static int idCODUnic;
    const int CODUnic;
    string adresa;
    int nrMedicamente;
    float *preturiMedicamente;

public:
    // constructor fara parametrii;
    Farmacie() : CODUnic(idCODUnic++), adresa(""), nrMedicamente(0)
    {
        this->preturiMedicamente = nullptr;
    }
    // constructor cu parametrii;
    Farmacie(const string &adresa, int nrMedicamente, float *preturi) : CODUnic(idCODUnic++), adresa(adresa), nrMedicamente(nrMedicamente)
    {
        this->preturiMedicamente = new float[nrMedicamente];
        for (int i = 0; i < nrMedicamente; i++)
        {
            this->preturiMedicamente[i] = preturi[i];
        }
    }
    // Constructor de copiere;
    Farmacie(const Farmacie &farmacie) : CODUnic(idCODUnic++), adresa(farmacie.adresa), nrMedicamente(farmacie.nrMedicamente)
    { // deep copy;
        this->preturiMedicamente = new float[nrMedicamente];
        for (int i = 0; i < nrMedicamente; i++)
        {
            this->preturiMedicamente[i] = farmacie.preturiMedicamente[i];
        }
    }
    // Overloading operator (=);
    Farmacie &operator=(const Farmacie &obj)
    {
        if (this != &obj)
        {
            this->adresa = obj.adresa;
            this->nrMedicamente = obj.nrMedicamente;
            delete[] preturiMedicamente;
            this->preturiMedicamente = new float[obj.nrMedicamente];
            for (int i = 0; i < obj.nrMedicamente; i++)
            {
                this->preturiMedicamente[i] = obj.preturiMedicamente[i];
            }
        }
        return *this;
    }
    // Operator (+) , adauga numarMedicamente; Test;
    Farmacie operator+(int nrMed)
    {
        Farmacie temp = *this;
        temp.nrMedicamente += nrMed;
        return temp;
    }
    // Operator overloading (<<);
    friend ostream &operator<<(ostream &oStream, const Farmacie &f)
    {
        oStream << "Id-Farmacie: -->> " << f.idCODUnic
                << " ; Adresa farmaciei: -->> " << f.adresa
                << " ; Numarul de medicamente: -->> " << f.nrMedicamente
                << " ; Preturile la medicamente: ->> \n";
        for (int i = 0; i < f.nrMedicamente; i++)
        {
            oStream << f.preturiMedicamente[i] << " lei " << endl;
        }
        return oStream;
    }
    // Operator overloading (>>);
    friend istream &operator>>(istream &iStream, Farmacie &far)
    {
        cout << "Introduceti adresa farmaciei:";
        iStream.ignore();             // functia ignore, ignora fluxul de caractere ramase in fluxul de date;
        getline(iStream, far.adresa); // citeste intreaga linie a 'far.adresa' cand introduci, incluzand si spatiile goale;
        // iStream >> far.adresa;
        cout << "Introduceti numar medicamente:";
        iStream >> far.nrMedicamente;
        if (far.preturiMedicamente != nullptr)
        {
            delete[] far.preturiMedicamente;
        }
        far.preturiMedicamente = new float[far.nrMedicamente];
        for (int i = 0; i < far.nrMedicamente; i++)
        {
            cout << "Preturi pentru medicamente " << (i + 1) << ":";
            iStream >> far.preturiMedicamente[i];
        }
        return iStream;
    }
    bool operator>(const Farmacie &farmacie)
    {
        return this->nrMedicamente > farmacie.nrMedicamente;
    }
    // Operator [] - index; accesea adresa de memorie a unui vector; via index;
    float &operator[](int index)
    {
        if (index >= 0 && index < this->nrMedicamente)
        {
            return this->preturiMedicamente[index];
        }
    }
    // Getter and Setter;
    string getAdresa() const
    {
        return this->adresa;
    }
    void setAdresa(const string &adr)
    {
        this->adresa = adr;
    }
    int getNrMedicamente() const
    {
        return this->nrMedicamente;
    }
    int getCODunic() const
    {
        return this->CODUnic;
    }
    int getNrMedicamenteIeftine(float value)
    {
        int count = 0;
        int i = 0;
        while (i < nrMedicamente)
        {
            if (this->preturiMedicamente[i] < value)
            {
                count++;
            }
            ++i;
        }
        return count;
    }

    ~Farmacie()
    {
        if (this->preturiMedicamente != nullptr)
            delete[] preturiMedicamente;
        cout << "Destructor called: \n";
    }
};

// initializare membru static;
int Farmacie::idCODUnic = 0;

int main()
{
    Farmacie f("Calea 13 septembrie nr.128", 3, new float[3]{12.55, 22.55, 10.56});
    cout << f << endl;
    Farmacie f1(f); // constructor de copiere chemat;
    cout << endl;
    cout << "Constructor de copiere \n";
    cout << f1 << endl;
    f1.setAdresa("Calea Victoriei nr.44A");
    cout << "Noua adresa a famaciei este: -> " << f1.getAdresa() << " cu CODUnic: " << f1.getCODunic() << endl;
    cout << "Farmacia are in stoc un nr. de medicamente: ->> " << f1.getNrMedicamente() << endl;
    cout << f1 << endl;
    cout << endl;
    Farmacie f2;
    f2 = f1; // operator de atribuire;
    f2.setAdresa("Str. Armeneasca nr.67");
    cout << "S-a deschis o noua farmacie pe strada: ->> " << f2.getAdresa() << endl;
    Farmacie f3("Calea Rahovei 45", 6, new float[6]{4.55, 6.77, 89.22, 22.44, 44.10, 10.90});
    cout << f3.getNrMedicamenteIeftine(33.44) << endl;
    cout << f3 << endl;
    if (f3 > f1)
    {
        cout << "Farmacia F3 are mai multe medicamente. \n";
    }
    else
    {
        cout << "Farmacia f1 are un numar redus de medicamente. ";
    }
    // operator [];
    cout << f3[0] << endl; // 4.55;

    return 0;
}
