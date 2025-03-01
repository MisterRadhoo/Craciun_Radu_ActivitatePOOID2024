#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Macelarie
{
private:
    static int stoc;
    string tipProdus;
    string tipCarne;
    string dataExpirare;
    int numarProduse;
    float *pret;

public:
    // constructor implicit;
    Macelarie() : tipProdus(" "), tipCarne(" "), dataExpirare("00/00/0000"), numarProduse(0), pret(nullptr)
    {
        stoc++;
    }
    // constructor cu parametrii;
    Macelarie(string tipProdus, string tipCarne, string dataExpirare, int nrProduse, float *preturi) : tipProdus(tipProdus),
                                                                                                       tipCarne(tipCarne), dataExpirare(dataExpirare), numarProduse(nrProduse)
    {
        stoc++;
        this->pret = new float[nrProduse];
        for (int i = 0; i < nrProduse; i++)
        {
            this->pret[i] = preturi[i];
        }
    }
    // constructor de copiere;
    Macelarie(const Macelarie &mcl) : tipProdus(mcl.tipProdus), tipCarne(mcl.tipCarne),
                                      dataExpirare(mcl.dataExpirare), numarProduse(mcl.numarProduse)
    {
        this->pret = new float[mcl.numarProduse];
        for (int i = 0; i < mcl.numarProduse; i++)
        {
            this->pret[i] = mcl.pret[i];
        }
    }
    // Operator de atribuire (=);
    Macelarie &operator=(const Macelarie &macelarie)
    {
        if (this != &macelarie)
        {
            delete[] this->pret;
            this->tipProdus = macelarie.tipProdus;
            this->tipCarne = macelarie.tipCarne;
            this->dataExpirare = macelarie.dataExpirare;
            this->numarProduse = macelarie.numarProduse;
            if (macelarie.pret != nullptr)
            {
                this->pret = new float[macelarie.numarProduse];
                for (int i = 0; i < macelarie.numarProduse; i++)
                {
                    this->pret[i] = macelarie.pret[i];
                }
            }
            else
            {
                this->pret = nullptr;
            }
        }
        return *this;
    }
    // Operator de (*=); // calculeaza reducere pentru produsele care expira urmatoarea zi;
    Macelarie &operator*=(float reducere)
    {
        if (this->dataExpirare == getDataExpirare())
        {
            for (int i = 0; i < this->numarProduse; i++)
            {
                this->pret[i] *= (1 - reducere / 100);
                cout << " Reducere aplicata de: -->> " << reducere << " %, la produsele care expira in data de: -->> " << this->dataExpirare << " \n";
            }
        }
        else
        {
            cout << "Produsele nu sunt reduse, ca nu au data de expirare specificata: \n";
        }
        return *this;
    }
    // Operator bool (==); supraincarcare;
    bool operator==(const Macelarie &m)
    {
        return (this->tipProdus == m.tipProdus &&
                this->tipCarne == m.tipCarne &&
                this->dataExpirare == m.dataExpirare);
    }
    // destructor
    virtual ~Macelarie()
    {
        cout << "Macelarie este inchisa: " << endl;
        if (this->pret != nullptr)
        {
            delete[] this->pret;
        }
        stoc--;
    }
    static int getStoc()
    {
        return stoc;
    }
    // setter si Getter;
    string getTipProdus() const
    {
        return this->tipProdus;
    }
    void setTipProdus(const string &prod)
    {
        this->tipProdus = prod;
    }
    string getTipCarne() const
    {
        return this->tipCarne;
    }
    void setTipCarne(const string &carne)
    {
        this->tipCarne = carne;
    }
    string getDataExpirare() const
    {
        return this->dataExpirare;
    }
    void setDataExpirare(const string &data)
    {
        if (data == this->dataExpirare)
        {
            cout << getDataExpirare();
        }
        else
        {
            this->dataExpirare = data;
            cout << "Produsul a fost desfacut, termen de valabilitate 48h. \n";
        }
    }
    int getNrProduse() const
    {
        return this->numarProduse;
    }
    void setNrProduse(int numar)
    {
        if (numar >= 0)
        {
            this->numarProduse = numar;
        }
        else
        {
            cout << "Warning !!!, without negative values...\n";
        }
    }

    float *getPret()
    {
        float *temp = new float[this->numarProduse];
        for (int i = 0; i < this->numarProduse; i++)
        {
            temp[i] = this->pret[i];
        }
        return temp;
    }
    void setPret(float *nouPret, int dimensiune)
    {
        setNrProduse(dimensiune);
        if (this->pret != nullptr)
        {
            delete[] this->pret;
        }
        this->pret = new float[dimensiune];
        for (int i = 0; i < dimensiune; i++)
        {
            this->pret[i] = nouPret[i];
        }
        delete[] nouPret;
    }

    friend ostream &operator<<(ostream &out, const Macelarie &m1)
    {
        out << "Stoc Produs din macelarie: -->> " << getStoc()
            << "; Tip produs din macelarie: ->> " << m1.tipProdus
            << "; Tipul de carne al produsului/carne animala: ->> " << m1.tipCarne
            << "; Data expirarii prodsului: ->> " << m1.dataExpirare
            << "; Numar de produse: -->> " << m1.numarProduse << " , de tip: " << m1.tipProdus << " , din carne de: " << m1.tipCarne << endl;
        for (int i = 0; i < m1.numarProduse; i++)
        {
            out << "Cu preturi de: -->> " << m1.pret[i] << " lei/Kg" << endl;
        }
        return out;
    }
    virtual void display()
    {
        cout << "Stoc produs macelarie: ->> " << getStoc() << endl;
        cout << "Tip produs macelarie: -->> " << this->tipProdus << endl;
        cout << "Tipul de carne al produsului/carne animala: -->> " << this->tipCarne << endl;
        cout << "Data expirarii produsului: -->> " << this->dataExpirare << endl;
        cout << "Numar de produse: -->> " << this->numarProduse << " , de tip: " << this->tipProdus << " , din carne de: " << this->tipCarne << endl;
        for (int i = 0; i < this->numarProduse; i++)
        {
            cout << "Cu preturi de: -->> " << this->pret[i] << " lei/kg " << endl;
        }
    }
};

class GestiuneStoc
{
private:
    vector<Macelarie> stoc;

public:
    GestiuneStoc &operator+=(const Macelarie &produs)
    {
        for (auto &item : stoc)
        {
            if (item == produs)
            {
                item.setNrProduse(item.getNrProduse() + produs.getNrProduse());
                return *this;
            }
        }
        stoc.push_back(produs);
        return *this;
    }
    void functie()
    {
        vector<Macelarie> stocActualizat;
        for (const auto &produs : stoc)
        {
            if (produs.getNrProduse() > 0)
            {
                stocActualizat.push_back(produs);
            }
        }
        stoc = stocActualizat;
    }
    void afisareStoc()
    {
        if (stoc.empty())
        {
            cout << "Stocul este gol: \n";
        }
        else
        {
            for (const auto &produs : stoc)
            {
                cout << "Produsele din stoc sunt: -->> " << produs << endl;
            }
        }
    }
};

// initializare membru static;
int Macelarie::stoc = 0;

class Carnat : public Macelarie
{
private:
    string tip;
    string producator;

public:
    // costructor implicit;s
    Carnat() : Macelarie(), tip(" "), producator(" ")
    {
    }
    // constructor cu parametrii;
    Carnat(const string &tp, const string &tc, const string &DE, int nrProduse, float *preturi, const string &tip, const string &prod) : Macelarie(tp, tc, DE, nrProduse, preturi), tip(tip), producator(prod)
    {
    }
    string getTip() const
    {
        return this->tip;
    }
    void setTip(const string &tip)
    {
        this->tip = tip;
    }
    string getProducator() const
    {
        return this->producator;
    }
    void setProducator(const string &producator)
    {
        this->producator = producator;
    }
    ~Carnat()
    {
        cout << "S-a chemat un carnat obosit...\n";
    }
    void display()
    {
        Macelarie::display();
        cout << "Tipul carnatului: -->> " << this->tip << endl;
        cout << "Producator de carnati: -->> " << this->producator << endl;
    }
};

int main()
{
    // Macelarie m1("Carne congelata", "Vita", "12/05/2026", 5, new float[5]{4.5, 6.7, 7.7, 9.07, 10.56});
    // cout << m1 << endl;
    // m1.setPret(new float[4]{10.55, 67.88, 8.90, 4.56}, 4);

    // float *preturi = m1.getPret();
    // for (int i = 0; i < 4; i++)
    // {
    //     cout << preturi[i] << "lei/kg" << endl;
    // }
    // delete[] preturi;
    // Macelarie m2;
    // m2 = m1;
    // cout << m2 << endl;
    // Macelarie m3("Carne proaspata", "Porc", "14/03/2025", 2, new float[2]{6.8, 7.9});
    // m3 *= 15; // overloading operator *=;
    // m3.display();
    // cout << endl;
    // if (m3 == m1)
    // {
    //     cout << " = \n";
    // }
    // else
    // {
    //     cout << " != \n";
    // }
    cout << endl;
    // Inheritance;
    Carnat c1("Carne congelata", "oaie", "23/12/2030", 3, new float[3]{9.99, 7.89, 12.55}, "afumat", "Babic SA");
    // c1.display(); // amandoi destructorii din clasa de baza si clasa derivata sunt chematii;
    //  Upcasting;
    Macelarie *pointerBase = &c1;
    pointerBase->display(); // early binding, in compile-time, upcasting se utilizeaza, se cheama functia din clasa de baza ,display(), pentru ca nu este declarata cu keyword "virtual", pentru realizare a poliformismului;
    cout << "Am declarat functia display() din clasa de baza cu keyword Virtual, Poliformismul se realizeaza: \n";
    cout << endl;
    // Poliformism realizat, functia din clasa de baza e declarata cu 'virtual';
    pointerBase->display(); // late binding, in runtime, functia display() din baza de date este declarata virtual, functia din clasa derivata este chemata.
    delete pointerBase;
    return 0;
}