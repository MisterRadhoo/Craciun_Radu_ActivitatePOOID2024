#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <queue>
using namespace std;

class Farmacie
{
private:
    static int nrCODUnic;
    const int CODUnic;
    string adresa;
    int nrMedicamente;
    float *preturiMedicamente;

public:
    Farmacie() : CODUnic(nrCODUnic++), adresa("Unknown"), nrMedicamente(0), preturiMedicamente(nullptr) {}
    Farmacie(const string &adresa, int nrMed, float *preturi) : CODUnic(nrCODUnic++), adresa(adresa), nrMedicamente(nrMed)
    {
        this->preturiMedicamente = new float[nrMed];
        for (int i = 0; i < nrMed; i++)
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
    Farmacie &operator=(const Farmacie &obj)
    {
        if (this != &obj)
        {
            delete[] this->preturiMedicamente;
            this->adresa = obj.adresa;
            this->nrMedicamente = obj.nrMedicamente;
            if (obj.preturiMedicamente != nullptr)
            {
                this->preturiMedicamente = new float[obj.nrMedicamente];
                for (int i = 0; i < obj.nrMedicamente; i++)
                {
                    this->preturiMedicamente[i] = obj.preturiMedicamente[i];
                }
            }
            else
            {
                this->preturiMedicamente = nullptr;
            }
        }
        return *this;
    }
    bool operator>(const Farmacie &f)
    {
        return this->nrMedicamente > f.nrMedicamente;
    }
    float &operator[](int index)
    {
        if (index >= 0 && index < this->nrMedicamente)
        {
            return this->preturiMedicamente[index];
        }
    }
    // suma totala a preturilor de medicamente din farmacie;
    float operator()()
    {
        float sum = 0;
        for (int i = 0; i < this->nrMedicamente; i++)
        {
            sum += this->preturiMedicamente[i];
        }
        return sum;
    }
    Farmacie &operator!()
    {
        this->nrMedicamente = !this->nrMedicamente;
        return *this;
    }
    Farmacie &operator~()
    {
        this->nrMedicamente = !this->nrMedicamente;
        return *this;
    }
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
    void setNrMedicamente(int nr)
    {
        if (nr >= 0)
        {
            this->nrMedicamente = nr;
        }
        else
        {
            cout << "Farmacia nu are suficente medicamente: \n";
            this->nrMedicamente = -1;
        }
    }
    float *getPreturiMedicamente()
    {
        float *tempPtr = this->preturiMedicamente;
        for (int i = 0; i < this->nrMedicamente; i++)
        {
            tempPtr[i] = this->preturiMedicamente[i];
        }
        return tempPtr;
    }
    void setPreturiMedicamente(float *newPret, int size)
    {
        setNrMedicamente(size);
        if (this->preturiMedicamente != nullptr)
        {
            delete[] this->preturiMedicamente;
        }
        this->preturiMedicamente = new float[size];
        for (int i = 0; i < size; i++)
        {
            this->preturiMedicamente[i] = newPret[i];
        }
        delete[] newPret;
    }
    int getCODUnic() const
    {
        return this->CODUnic;
    }
    float getNrMedicamenteIeftine(float value)
    {
        int count = 0;
        for (int i = 0; i < this->nrMedicamente; i++)
        {
            if (this->preturiMedicamente[i] < value)
            {
                cout << "Iteraria:-->> " << count << " / " << this->preturiMedicamente[i] << endl;
                count++;
            }
        }
        return count;
    }

    ~Farmacie()
    {
        if (this->preturiMedicamente != nullptr)
        {
            delete[] this->preturiMedicamente;
        }
        cout << "\nFarmacie este goala..., cu <CODUnic>-->> " << this->CODUnic << " <<-- Destructor chemat \n";
    }
    static int getNrCODunic()
    {
        return nrCODUnic;
    }
    void display()
    {
        cout << " Cod Unic Farmacie: -->> " << this->CODUnic << endl;
        cout << " Adresa Farmacie: -->> " << this->adresa << endl;
        cout << " Numarul de medicamente disponibil in Farmacie: -->> " << this->nrMedicamente << " cutii " << endl;
        for (int i = 0; i < this->nrMedicamente; i++)
        {
            cout << " Cu preturile urmatoare: -->> " << this->preturiMedicamente[i] << " lei/medicament " << endl;
        }
    }
    friend ostream &operator<<(ostream &out, const Farmacie &f)
    {
        out << " Cod Unic Farmacie: -->> " << f.CODUnic
            << " ; Adresa Farmacie: -->> " << f.adresa
            << " ; Numarul de medicamente in stoc, Farmacie: -->> " << f.nrMedicamente << " cutii " << endl;
        for (int i = 0; i < f.nrMedicamente; i++)
        {
            out << " Cu preturile urmatoare: -->> " << f.preturiMedicamente[i] << " lei/medicament " << endl;
        }
        return out;
    }
    friend istream &operator>>(istream &in, Farmacie &f)
    {
        cout << "Indroduceti adresa Farmacie: -->> ";
        in.ignore();
        getline(in, f.adresa);
        cout << " Indroduceti nr. de medicamente: -->> ";
        in >> f.nrMedicamente;
        if (f.preturiMedicamente != nullptr)
        {
            delete[] f.preturiMedicamente;
        }
        f.preturiMedicamente = new float[f.nrMedicamente];
        for (int i = 0; i < f.nrMedicamente; i++)
        {
            cout << " Preturi pentru medicamente: " << " index al vectorului " << i << " ; ";
            in >> f.preturiMedicamente[i];
        }
        return in;
    }
};

// initializare membru static din clasa Farmacie;
int Farmacie::nrCODUnic = 0;

int main()
{
    Farmacie f;
    f.display();
    cout << endl;
    Farmacie f1("Calea Mosilor nr.77D", 4, new float[4]{75.4, 35.50, 88.10, 25.55});
    f1.display();
    cout << f1[2] << endl; // operator []; // 88.10;
    cout << "---------Copy Constructor: --------- >> \n";
    Farmacie f2(f1);
    f2.display();
    f2.setAdresa("Blvd Unirii nr.44");
    cout << "Farmacia cu CODUnic " << f2.getCODUnic() << " s-a mutat la noua adresa: --->> " << f2.getAdresa() << endl;
    cout << "Avand pe stoc un numar de: -->> " << f2.getNrMedicamente() << " cutii/medicamente " << endl;
    cout << endl;
    f2.display();
    cout << endl;
    int dimensiune = 5;
    float *param = new float[5]{88.99, 15.60, 78.99, 99.99, 102.5};
    Farmacie f3("Str.Aleea Castanilor nr.99", dimensiune, param);
    // f3.display();
    cout << endl;
    f = f3; // overloading operator (=);
    f.display();
    cout << f << endl;
    cout << endl;

    delete[] param;
    cout << f3.getNrMedicamenteIeftine(90.90) << endl;
    // bool operator (>) overloading;
    if (f1 > f3)
    {
        cout << "Farmacia 1 are nr. > de medicamente: -->> " << f1.getNrMedicamente() << endl;
    }
    else
    {
        cout << " Farmacia 3 are nr > de medicamente decat Farmacia 1: --->> " << f3.getNrMedicamente() << endl;
    }
    cout << "Suma totala preturilor/medicamente a Farmaciei 3: -->> " << f3() << endl;
    !f3;
    cout << f3;
    ~f3;
    cout << f3;
    float *preturi = f1.getPreturiMedicamente();
    for (int i = 0; i < 4; i++)
    {
        cout << "preturi pentru Farmacia 1: -->> " << preturi[i] << endl;
    }
    delete[] preturi;
    f1.setPreturiMedicamente(new float[6]{67.99, 88.90, 55.10, 120.20, 55.90, 100.00}, 6);
    cout << f1 << endl;

    // // container STL; vector;
    // vector<Farmacie> nrMedicamente;
    // nrMedicamente.push_back(f);
    // nrMedicamente.push_back(f1);
    // nrMedicamente.push_back(f2);
    // nrMedicamente.push_back(f3);
    // // nrMedicamente.pop_back();

    // for (int i = 0; i < nrMedicamente.size(); i++)
    // {
    //     cout << "Container STL(vector) are un numar de medicamente: -->> " << nrMedicamente[i].getNrMedicamenteIeftine(99.99) << endl;
    // }

    // // constainer STL; stack; (LIFO);
    // stack<Farmacie> nrMed;
    // nrMed.push(f);
    // nrMed.push(f1);
    // nrMed.push(f2);
    // nrMed.push(f3);
    // nrMed.size();

    // while (!nrMed.empty())
    // {
    //     cout << nrMed.top() << " Cap; ";
    //     nrMed.pop();
    //     cout << "GOL" << endl;
    // }
    // // Container STL; Queue (FIFO);
    // queue<Farmacie> nrM;
    // nrM.push(f1);
    // nrM.push(f3);
    // nrM.size();
    // Farmacie back = nrM.back();
    // cout << "/ " << back << endl;
    // while (!nrM.empty())
    // {
    //     cout << nrM.front() << "Front";
    //     nrM.pop();
    // }

    return 0;
}