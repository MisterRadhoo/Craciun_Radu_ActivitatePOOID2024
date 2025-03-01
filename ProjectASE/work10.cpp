#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Farmacie
{
private:
    static int nrCODUnic;
    const int CODUnic;
    string adresa;
    int nrMedicamente;
    float *preturiMedicamente;
    string eliberare;

public:
    Farmacie() : CODUnic(nrCODUnic++), adresa("N/A"), nrMedicamente(0)
    {
        this->preturiMedicamente = nullptr;
    }
    Farmacie(const string &adresa, int nrMedicamente, float *preturi) : CODUnic(nrCODUnic++), adresa(adresa), nrMedicamente(nrMedicamente)
    {
        this->preturiMedicamente = new float[this->nrMedicamente];
        for (int i = 0; i < this->nrMedicamente; i++)
        {
            this->preturiMedicamente[i] = preturi[i];
        }
    }
    Farmacie(const Farmacie &f) : CODUnic(f.CODUnic), adresa(f.adresa), nrMedicamente(f.nrMedicamente)
    {
        this->preturiMedicamente = new float[f.nrMedicamente];
        for (int i = 0; i < f.nrMedicamente; i++)
        {
            this->preturiMedicamente[i] = f.preturiMedicamente[i];
        }
    }
    Farmacie &operator=(const Farmacie &f)
    {
        if (this != &f)
        {
            delete[] this->preturiMedicamente;
            this->adresa = f.adresa;
            this->nrMedicamente = f.nrMedicamente;
            if (f.preturiMedicamente != nullptr)
            {
                this->preturiMedicamente = new float[f.nrMedicamente];
                for (int i = 0; i < f.nrMedicamente; i++)
                {
                    this->preturiMedicamente[i] = f.preturiMedicamente[i];
                }
            }
            else
            {
                this->preturiMedicamente = nullptr;
            }
        }
        return *this;
    }
    bool operator>(const Farmacie &farmacie)
    {
        return (this->nrMedicamente > farmacie.nrMedicamente);
    }
    float &operator[](int index)
    {
        if (index >= 0 && index < this->nrMedicamente)
            return this->preturiMedicamente[index];
    }
    float operator()()
    {
        float suma = 0;
        for (int i = 0; i < this->nrMedicamente; i++)
        {
            suma += this->preturiMedicamente[i];
        }
        return suma;
    }
    Farmacie operator++(int)
    {
        Farmacie temp = *this;
        this->nrMedicamente++;
        return temp;
    }
    string getAdresa() const
    {
        return this->adresa;
    }
    void setAdresa(const string &str)
    {
        this->adresa = str;
    }
    int getNrMedicamente() const
    {
        return this->nrMedicamente;
    }
    int getCODUnic() const
    {
        return this->CODUnic;
    }
    string getEliberare() const
    {
        return this->eliberare;
    }
    void setEliberare(const string &str1)
    {
        this->eliberare = str1;
    }

    virtual ~Farmacie()
    {
        if (this->preturiMedicamente != nullptr)
        {
            delete[] this->preturiMedicamente;
        }
        cout << "Destructor chemat: --->>\n";
    }
    friend ostream &operator<<(ostream &out, const Farmacie &f)
    {
        out << " Cod unic Farmacie: -->> " << f.CODUnic
            << "; Adresa farmaciei: -->> " << f.adresa
            << "; Nr. de medicamente disponibil: -->> " << f.nrMedicamente << endl;
        for (int i = 0; i < f.nrMedicamente; i++)
        {
            out << " Numarul de medicamente este: -->> " << f.nrMedicamente << ", cu preturile: -->> " << f.preturiMedicamente[i] << " lei/medicament " << endl;
        }

        return out;
    }
    virtual void display() const
    {
        cout << *this;
        cout << "early binding" << endl;
    }
};

class Nurofen : public Farmacie
{
private:
    int stoc;
    string brand;

public:
    Nurofen(const string &adresa, int nrMed, float *preturi, int stoc, const string &brand) : Farmacie(adresa, nrMed, preturi), stoc(stoc), brand(brand) {}

    void display() const
    {
        cout << *this;
        cout << " Stoc de nurofen in farmacie: --->> " << this->stoc << endl;
        cout << " Producator: --> " << this->brand << endl;
        cout << " Late binding:" << endl;
    }
    Nurofen &operator+=(int value)
    {
        this->stoc += value;
        return *this;
    }
    Nurofen &operator-=(int scadere)
    {
        this->stoc -= scadere;
        return *this;
    }

    ~Nurofen()
    {
        cout << "clasa derivata chemata:  \n";
    }
};

// initializare membru static;
int Farmacie::nrCODUnic = 0;

int main()
{
    Farmacie f;
    Farmacie f1("Calea Mosilor nr.55v", 4, new float[4]{55.55, 33.22, 89.05, 105.40});
    Farmacie f2(f1);
    cout << f << endl;
    cout << f1 << endl;
    cout << "copy constructor called: \n";
    cout << f2 << endl;
    int size = 5;
    float *preturi = new float[5]{32.4, 55.67, 77.77, 88.90, 110.45};
    cout << endl;
    Farmacie f3("Calea Victoriei nr.44", 5, preturi);
    cout << f3 << endl;
    f = f3;
    cout << f.getCODUnic() << endl;
    cout << f.getNrMedicamente() << endl;
    f.setAdresa("Blvd Unirii 66A");
    cout << f.getAdresa() << endl;
    cout << f << endl;
    cout << endl;
    if (f1 > f3)
    {
        cout << " Farmacia f1 are mai multe medicamente: \n";
    }
    else
    {
        cout << "Farmacia f3 are mai multe medicamente: \n";
    }

    cout << "Pretul medicamentului situat la index 4, din farmacia f3: -->> " << f[4] << " lei/medicament" << endl;
    cout << f3() << " lei " << endl;
    Nurofen n("Calea Vitan nr.42B", 3, new float[3]{12.22, 44.09, 16.99}, 3, "NuroPharm");
    Farmacie *ptr = &n;
    ptr->display();

    vector<Farmacie> nrMed;
    nrMed.push_back(f1);
    nrMed.push_back(f3);
    nrMed.push_back(n);
    for (int i = 0; i < nrMed.size(); i++)
    {
        cout << " Numarul de medicamente: -->> " << nrMed[i].getNrMedicamente() << endl;
    }

    delete[] preturi;
    delete ptr;
    return 0;
}