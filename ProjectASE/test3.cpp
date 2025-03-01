#include <iostream>
#include <string>
#include <vector>
using namespace std;
// Class Portofel;
class Portofel
{
private:
    // static int contor;
    const int idPortofel;
    string culoare;
    int nrBuzunare;
    // sau tip int;
    float *latimeBuzunare;

public:
    // constructor fara parametrii
    Portofel() : idPortofel(0), culoare(" "), nrBuzunare(0)
    {
        this->latimeBuzunare = nullptr;
    }
    // constructor cu parametrii;
    Portofel(int id, const string culoare, int nrBuzunare, float *latimeBuzunare) : idPortofel(id), culoare(culoare), nrBuzunare(nrBuzunare)
    {
        this->latimeBuzunare = new float[nrBuzunare];
        for (int i = 0; i < nrBuzunare; i++)
        {
            this->latimeBuzunare[i] = latimeBuzunare[i];
        }
    }
    // constructor copiere;
    Portofel(const Portofel &portofel) : idPortofel(portofel.idPortofel), culoare(portofel.culoare), nrBuzunare(portofel.nrBuzunare)
    {
        this->latimeBuzunare = new float[portofel.nrBuzunare];
        for (int i = 0; i < portofel.nrBuzunare; i++)
        {
            this->latimeBuzunare[i] = portofel.latimeBuzunare[i];
        }
    }
    // overloading operator de atribuire (=);
    Portofel &operator=(const Portofel &p)
    { // evita auto-atribuirea;
        if (this != &p)
        {
            delete[] this->latimeBuzunare;
            this->culoare = p.culoare;
            this->nrBuzunare = p.nrBuzunare;
            if (this->latimeBuzunare != nullptr)
            {

                this->latimeBuzunare = new float[p.nrBuzunare];
                for (int i = 0; i < p.nrBuzunare; i++)
                {
                    this->latimeBuzunare[i] = p.latimeBuzunare[i];
                }
            }
            else
            {
                this->latimeBuzunare = nullptr;
            }
        }
        return *this;
    }
    // Overloading operator (+=);
    Portofel &operator+=(float addlatimeBuzunar)
    {
        this->nrBuzunare++;                        //  incrementeaza nrBuzunare;
        float *temp = new float[this->nrBuzunare]; // alocare de memorie in noul vector temp; cu valorile existente;
        for (int i = 0; i < this->nrBuzunare - 1; i++)
        {
            temp[i] = this->latimeBuzunare[i];
        }
        temp[this->nrBuzunare - 1] = addlatimeBuzunar;
        if (this->latimeBuzunare != nullptr)
        {
            delete[] this->latimeBuzunare;
        }
        this->latimeBuzunare = temp;
        return *this;
    }
    int getNrBuzunare()
    {
        return this->nrBuzunare;
    }
    void setNrBuzunare(int buzunare)
    {
        if (this->nrBuzunare > 0)
        {
            this->nrBuzunare = buzunare;
        }
        else
        {
            cout << "Nu se mai fabrica portofole de acest tip. \n";
        }
    }
    // set si get pentru  vectorul 'latimeBuzunar';
    float *getLatimeBuzunar() const
    {
        float *latimeBuzunar = new float[this->nrBuzunare];
        for (int i = 0; i < this->nrBuzunare; i++)
        {
            latimeBuzunar[i] = this->latimeBuzunare[i];
        }
        return latimeBuzunar;
    }
    void setLatimeBuzunar(float *newlatimeBuzunar, int nouaDimensiune)
    {
        setNrBuzunare(nouaDimensiune);
        if (this->latimeBuzunare != nullptr)
        {
            delete[] this->latimeBuzunare;
        }
        this->latimeBuzunare = new float[nouaDimensiune];
        for (int i = 0; i < nouaDimensiune; i++)
        {
            this->latimeBuzunare[i] = newlatimeBuzunar[i];
        }
        delete[] newlatimeBuzunar;
    }

    // Destructor;
    ~Portofel()
    {
        if (this->latimeBuzunare != nullptr)
        {
            delete[] this->latimeBuzunare;
        }
        cout << "Destructor chemat......Memorie eliberata.. \n";
    }
    friend ostream &operator<<(ostream &os, const Portofel &p)
    {
        os << " Id.Portorfel: " << p.idPortofel
           << " , Culoare la portofel: " << p.culoare
           << " , Portofelul are: " << p.nrBuzunare << " buzunare.\n";
        for (int i = 0; i < p.nrBuzunare; i++)
        {
            os << "Latimea unui buzunar este:  " << p.latimeBuzunare[i] << " cm" << endl;
        }
        return os;
    }
};

int main()
{
    Portofel p1;
    Portofel p2(1, "verde", 6, new float[6]{1, 2, 3, 4, 5, 6});
    Portofel p3(p2); // constructor copy;
    Portofel p4(2, "negru", 3, new float[3]{5, 6, 7});
    p4 = p2;
    cout << "Overloading operator (=) \n";
    cout << p4 << endl;
    p4 += 5.5f;
    cout << p4 << endl;
    cout << "Adresa de memorie a vectorului: -- >> " << p4.getLatimeBuzunar() << endl;
    p4.setNrBuzunare(9);
    p4.setLatimeBuzunar(new float[12]{1.2, 1.3, 3.5, 1.5, 6.7, 7.7, 8.8, 9.9, 10.09, 90.09, 14.15, 0.09}, 12);
    cout << p4.getLatimeBuzunar() << endl;
    return 0;
}

// int gerNrPortofeleBuzunar(); sa returneze nr de buzunare mai mare decat al doilea;
// atribut la alegere;
// overloading bool operator >
// overloading ostream <<;
// setter and getters pentru 2 atribute la alegere, si constructor de copiere;
// operator overloading +=;