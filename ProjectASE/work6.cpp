#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

class Petitie
{
private:
    static int termenRezolvare;
    const int Id;
    string dataDepunerii;
    string numePrenume;
    string categorie;
    string descriere;
    bool rezolvata;
    int nrPetitii;
    int *cutie;

public:
    // constructor implicit;
    Petitie() : Id(termenRezolvare), dataDepunerii("00/00/0000"), numePrenume("Unknown"), categorie("unSpecified"), descriere("unSpecified"), rezolvata(false), nrPetitii(0)
    {
        this->cutie = nullptr;
    }
    // constuctor cu parametrii;
    Petitie(const string &DD, const string &NP, const string &cat, const string &desc, bool rezol, int nrPet, int *box) : Id(termenRezolvare)
    {
        this->dataDepunerii = DD;
        this->numePrenume = NP;
        this->categorie = cat;
        this->descriere = desc;
        this->rezolvata = rezol;
        this->nrPetitii = nrPet;
        this->cutie = new int[nrPet]; // alocare de memorie pentru *pointer cutie la int;
        for (int i = 0; i < nrPet; i++)
        {
            this->cutie[i] = box[i];
        }
    }
    // Constructor de copiere;
    Petitie(const Petitie &copy) : Id(termenRezolvare), dataDepunerii(copy.dataDepunerii),
                                   numePrenume(copy.numePrenume), categorie(copy.categorie),
                                   descriere(copy.descriere), rezolvata(copy.rezolvata), nrPetitii(copy.nrPetitii)
    {
        this->cutie = new int[copy.nrPetitii];
        for (int i = 0; i < copy.nrPetitii; i++)
        {
            this->cutie[i] = copy.cutie[i];
        }
    }
    // Operator de (=);
    Petitie &operator=(const Petitie &obj)
    {
        if (this != &obj)
        {
            delete[] cutie;
            this->dataDepunerii = obj.dataDepunerii;
            this->numePrenume = obj.numePrenume;
            this->categorie = obj.categorie;
            this->descriere = obj.descriere;
            this->rezolvata = obj.rezolvata;
            this->nrPetitii = obj.nrPetitii;
            if (obj.cutie != nullptr)
            {
                this->cutie = new int[obj.nrPetitii];
                for (int i = 0; i < obj.nrPetitii; i++)
                {
                    this->cutie[i] = obj.cutie[i];
                }
            }
            else
            {
                this->cutie = nullptr;
            }
        }
        return *this;
    }
    // destructor;
    ~Petitie()
    {
        cout << "Box has free memory:-->> ###\n";
        if (this->cutie != nullptr)
        {
            delete[] cutie;
        }
    }
    static int getTermen()
    {
        return termenRezolvare;
    }
    int getNrPetitii() const
    {
        return this->nrPetitii;
    }
    int setNrPetitii(int numar)
    {
        if (numar >= 0)
        {
            this->nrPetitii = numar;
        }
        else
        {
            cout << "Valoarea e negativa, nu se pot depune petitii: -->> " << this->nrPetitii << endl;
            this->nrPetitii = -1;
        }
    }
    int *getCutie() const
    {
        int *newBox = new int[this->nrPetitii];
        for (int i = 0; i < this->nrPetitii; i++)
        {
            newBox[i] = this->cutie[i];
        }
        return newBox;
    }
    int setCutie(int *cutieNoua, int dimensiuneNoua)
    {
        setNrPetitii(dimensiuneNoua);
        if (this->cutie != nullptr)
        {
            delete[] this->cutie;
        }
        this->cutie = new int[dimensiuneNoua];
        for (int i = 0; i < dimensiuneNoua; i++)
        {
            this->cutie[i] = cutieNoua[i];
        }
        delete[] cutieNoua;
    }
    string getCategorie() const
    {
        return this->categorie;
    }
    Petitie &operator!()
    {
        this->rezolvata = !this->rezolvata;
        return *this;
    }
    int &operator[](int index)
    {
        if (index >= 0 && index < this->nrPetitii)
        {
            return this->cutie[index];
        }
    }
    int operator()()
    {
        int suma = 0;
        for (int i = 0; i < this->nrPetitii; i++)
        {
            suma += this->cutie[i];
        }
        return suma;
    }
    Petitie &operator~()
    {

        this->rezolvata = !this->rezolvata;
        cout << "Stare petitiei: -->> a fost schimbata la: " << (this->rezolvata ? "Rezolvata" : "Deschisa") << endl;
        return *this;
    }
    friend ostream &operator<<(ostream &out, const Petitie &p)
    {
        out << " ID petitie: -->> " << p.Id << endl;
        out << "; Termen de rezolvare: -->>  " << getTermen() << " Zile " << endl;
        out << "; Data depunerii petitiei: -->> " << p.dataDepunerii << endl;
        out << "; Numele depunatorului: -->> " << p.numePrenume << endl;
        out << "; Categorie petitie: -->> " << p.categorie << endl;
        out << "; Descriere petitie:-->> " << p.descriere << endl;
        out << "; Rezolvata: -->> " << (p.rezolvata ? "Da" : "Nu") << endl;
        out << "; Numarul de petitii: -->> " << p.nrPetitii << " , pe categoria:-->> " << p.categorie << " , cu descrierea: -->> " << p.descriere << endl;
        for (int i = 0; i < p.nrPetitii; i++)
        {
            out << "Sunt depuse un numar de petitii: -->> " << p.nrPetitii << " ; in cutie: -->> " << p.cutie[i] << endl;
        }

        return out;
    }
    friend istream &operator>>(istream &in, Petitie &p)
    {
        cout << "Introduceti datele petitiei:\n";
        cout << "Data depunerii (format DD/MM/YYYY): ";
        in >> p.dataDepunerii;

        cout << "Numele depunatorului: ";
        in.ignore(); // Ignorăm newline-ul rămas în buffer
        getline(in, p.numePrenume);

        cout << "Categorie petitie: ";
        getline(in, p.categorie);

        cout << "Descriere petitie: ";
        getline(in, p.descriere);

        cout << "Numarul de petitii: ";
        in >> p.nrPetitii;
        if (p.cutie != nullptr)
        {
            delete[] p.cutie;
        }
        p.cutie = new int[p.nrPetitii];
        cout << "Introduceti valorile din cutie (cate " << p.nrPetitii << " numere): ";
        for (int i = 0; i < p.nrPetitii; i++)
        {
            in >> p.cutie[i];
        }
        cout << "Rezolvata (1 pentru Da, 0 pentru Nu): ";
        int rezolvata;
        in >> rezolvata;
        p.rezolvata = (rezolvata != 0);

        return in;
    }
};

class Prioritate : public Petitie
{

private:
    string nivelPrioritate;
    int nrPrioritate;

public:
    Prioritate() : Petitie(), nivelPrioritate("Necunoscut"), nrPrioritate(0) {}
    Prioritate(const string &DD, const string &NP, const string &cat, const string &desc, bool rez, int nrPet, int *box, const string &nivelPrioritate, int nrPrioritate) : Petitie(DD, NP, cat, desc, rez, nrPet, box), nivelPrioritate(nivelPrioritate), nrPrioritate(nrPrioritate)
    {
    }
    Prioritate(const Prioritate &copy) : Petitie(copy), nivelPrioritate(copy.nivelPrioritate), nrPrioritate(copy.nrPrioritate) {}

    Prioritate &operator=(const Prioritate &p)
    {
        if (this != &p)
        {
            (Petitie) *this = (Petitie)p;
            this->nivelPrioritate = p.nivelPrioritate;
            this->nrPrioritate = p.nrPrioritate;
        }
        return *this;
    }
    Prioritate &operator+=(int value)
    {
        this->nrPrioritate += value;
        return *this;
    }
    Prioritate operator-(int scade)
    {
        Prioritate temp = *this;
        temp.nrPrioritate -= scade;
        return temp;
    }
    string getNivel() const
    {
        return this->nivelPrioritate;
    }
    void setNivel(const string &str)
    {
        this->nivelPrioritate = str;
    }
    int getNrPrioritate() const
    {
        return this->nrPrioritate;
    }
    int setNrPrioritate(int numar)
    {
        this->nrPrioritate = numar;
    }
    void afisare()
    {
        cout << *this;
        cout << " Nivel de prioritate a petitiei: -->> " << this->nivelPrioritate << endl;
        cout << " Numarul de prioritate a petitiei: -->> " << this->nrPrioritate << endl;
    }
    ~Prioritate() = default;
};

int Petitie::termenRezolvare = 30;

// Clasa Abstracta;// conceptul de virtualizare;
class Petition
{
protected:
    static int deadline;
    string day;
    string fullName;
    string group;
    string description;
    bool solved;

public:
    // constructor cu parametrii;
    Petition(const string &day, const string &name, const string &group, const string &desc, bool solved) : day(day), fullName(name), group(group), description(desc), solved(solved)
    {
    }
    virtual void processing(int nr, const string &str) = 0; // pure virtual function;
    static int getDeadline()
    {
        return deadline;
    }
    string getDay() const
    {
        return this->day;
    }
    string getFullName() const
    {
        return this->fullName;
    }
    string getGroup() const
    {
        return this->group;
    }
    string getDescription() const
    {
        return this->description;
    }
    bool getSolved() const
    {
        return this->solved;
    }
    virtual ~Petition() = default;
};

class Priority : public Petition
{
protected:
    string priorityLevel;
    int number;

public:
    Priority(const string &day, const string &name, const string &group, const string &desc, bool solved, const string &priorityLvl, int nr) : Petition(day, name, group, desc, solved), priorityLevel(priorityLvl), number(nr) {}
    string getPL() const
    {
        return this->priorityLevel;
    }
    string setPL(const string &level)
    {
        this->priorityLevel = level;
    }
    // functie care proceseaza, petitile care nu au fost rezolvate in termen de 21 de zile;
    void processing(int nr, const string &str)
    {
        if (!this->solved && this->number <= nr)
        {
            setPL(str);
            cout << "Petition with number: -->>" << this->number << " below " << nr << " will switch priority level to: " << str << endl;
            this->solved = true;
        }
        else if (this->solved)
        {
            setPL(str);
            cout << "Petition  with number: -->> " << this->number << " will switch priority level: " << str << endl;
        }
        else
        {
            cout << "Petition will not be proccesed. \n";
        }
    }

    void display() const
    {
        cout << "Inquaries form, for restoration of NYC: \n";
        cout << " Deadline: -->> " << getDeadline() << " days " << endl;
        cout << " Day: -->> " << getDay() << endl;
        cout << " Full Name: -->> " << getFullName() << endl;
        cout << " Grouped By: -->> " << getGroup() << endl;
        cout << " Description: -->> " << getDescription() << endl;
        cout << " Solved: --> " << (getSolved() ? "Yes" : "No") << endl;
        cout << " Priority Level: -->> " << this->priorityLevel << endl;
        cout << " Number: -->> " << this->number << endl;
    }
};

int Petition::deadline = 21;

int main()
{
    Petitie p;

    Petitie p1("15/12/2024", "Gigel Pistol", "Infrastructura", "Reparatii drumuri", false, 2, new int[2]{1, 2});
    Petitie p2("25/06/2025", "Fane Tragaci", "Educatie", "Renovare scoli si licee", true, 3, new int[3]{100, 101, 102});
    Petitie p3;
    p3 = p2;
    cout << endl;
    Petitie p4("12/12/2020", "Elena Tampon", "Sanatate", "Reabilitare Spitale", true, 3, new int[3]{97, 98, 99});
    // cout << p4 << endl;
    cout << endl;
    !p1; // overloading operator !;
    cout << "Termenul de: " << p1.getTermen() << " zile, a expirat." << endl;
    cout << p1 << endl;
    ~p1; // overloading operator!;
    cout << p1 << endl;
    p1.setNrPetitii(4);
    int *param = new int[4]{1, 2, 3, 4};
    int size = 4;
    p1.setCutie(param, 4);
    cout << "Numar de petitii actuale: " << p1.getNrPetitii() << endl;
    cout << p1 << endl;
    cout << endl;
    int *numar = p1.getCutie();
    for (int i = 0; i < 4; i++)
    {
        cout << "Update numar petitii: -->> " << numar[i] << endl;
    }
    delete numar;
    delete[] param;

    // container STL;
    vector<Petitie> categorii;
    categorii.push_back(p);
    categorii.push_back(p1);
    categorii.push_back(p2);
    categorii.push_back(p3);
    categorii.push_back(p4);

    for (int i = 0; i < categorii.size(); i++)
    {
        cout << "Container STL <vector> care stocheaza obiecte dupa categorii: -->> " << categorii[i].getCategorie() << endl;
    }
    cout << endl;
    cout << "Suma totala a petitilor din instanta obiectului p2: -->> " << p2() << endl;
    cout << "Index din instanta obiectului p2[0]: -->> " << p2[0] << endl;

    // container STL;
    stack<Petitie> categorie;
    categorie.push(p);
    categorie.push(p1);
    categorie.push(p2);
    categorie.push(p3);
    categorie.push(p4);
    categorie.push(Petitie("17/05/2019", "Ginela Vaginela", "Drumuri si poduri", "Asfaltare si contructii", false, 2, new int[2]{66, 67}));
    while (!categorie.empty())

    {
        Petitie topP = categorie.top();
        cout << "Afisare obiectul din top: -->> " << topP << endl;
        cout << " ----------------------------------------------------------\n";
        categorie.pop();
    }

    // clasa derivata;
    Prioritate pr("29/12/2023", "Ulan Bator", "Locuri publice", "Reparatii aeroport", true, 3, new int[3]{5, 6, 7}, "Ridicat", 2155);
    pr.afisare();
    pr += 60;
    pr.afisare();
    pr = pr - 200;
    pr.afisare();
    cout << endl;

    // clasa abstracta; concept de virtualizare;

    Priority pr1("09/08/2018", "Gogu Pandele", "Urban Area", "5th Avenue Restoration", true, "High", 5505);
    pr1.display();
    pr1.processing(10000, "Critical"); // concept de virtualizare;clasa abstracta;
    cout << endl;
    pr1.display();

    return 0;
}