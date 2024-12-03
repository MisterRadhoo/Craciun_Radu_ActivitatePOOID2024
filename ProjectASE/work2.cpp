#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Programator; // forward declaration;;

class Laptop
{
private:
    static int nrLaptopuri;
    const int id;
    int RAM;
    string tipCPU;
    float rezolutieEcran;
    bool cameraWeb;
    int nrTaste;
    int *nrApasariTasta;

public:
    // constructor fara parametrii;
    Laptop() : id(nrLaptopuri++), RAM(0), tipCPU(""), rezolutieEcran(0.0), cameraWeb(false), nrTaste(0)
    {
        this->nrApasariTasta = nullptr;
    }
    // constructor cu parametrii;
    Laptop(int RAM, const string &tipCPU, float rezolutie, bool camera, int nrTaste, int *nrApasari)
        : id(nrLaptopuri++), RAM(RAM), tipCPU(tipCPU), rezolutieEcran(rezolutie), cameraWeb(camera), nrTaste(nrTaste)
    {
        this->nrApasariTasta = new int[nrTaste];
        for (int i = 0; i < nrTaste; i++)
        {
            this->nrApasariTasta[i] = nrApasari[i];
        }
    }
    // constructor de copiere;
    Laptop(const Laptop &l)
        : id(nrLaptopuri++), RAM(l.RAM), tipCPU(l.tipCPU), rezolutieEcran(l.rezolutieEcran), cameraWeb(l.cameraWeb), nrTaste(l.nrTaste)
    {
        this->nrApasariTasta = new int[nrTaste];
        for (int i = 0; i < nrTaste; i++)
        {
            this->nrApasariTasta[i] = l.nrApasariTasta[i];
        }
    } // operator de atribuire(=);
    Laptop &operator=(const Laptop &laptop)
    {
        if (this != &laptop)
        {
            delete[] this->nrApasariTasta;
            this->RAM = laptop.RAM;
            this->tipCPU = laptop.tipCPU;
            this->rezolutieEcran = laptop.rezolutieEcran;
            this->cameraWeb = laptop.cameraWeb;
            this->nrTaste = laptop.nrTaste;
            if (this->nrApasariTasta != nullptr)
            {
                this->nrApasariTasta = new int[laptop.nrTaste];
                for (int i = 0; i < laptop.nrTaste; i++)
                {
                    this->nrApasariTasta[i] = laptop.nrApasariTasta[i];
                }
            }
        }
        return *this;
    }
    // Overloading operator(+)
    Laptop operator+(int addRAM)
    {
        Laptop temp = *this;
        temp.RAM += addRAM;
        return temp;
    }
    // Overloading operator(-);
    Laptop operator-(int scadeRAM)
    {
        Laptop temp = *this;
        temp.RAM -= scadeRAM;
        return temp;
    }
    // Overload operator(++);
    Laptop operator++(int)
    {
        Laptop copie = *this;
        this->RAM++;
        return copie;
    }
    // Overloading ([]);
    int &operator[](int index)
    {
        if (index >= 0 && index < this->nrTaste)
            return this->nrApasariTasta[index];
    }
    // Overloading (+=), adauga si atribuie, modifica obiectul initial prin referinta, return *this ( obiectul curent);
    Laptop &operator+=(int value)
    {
        this->RAM += value;
        return *this;
    }
    int getRAM() const
    {
        return this->RAM;
    }
    void setMaxRAM(int maxRAM)
    {
        this->RAM = maxRAM;
    }
    string getTipCPU() const
    {
        return this->tipCPU;
    }
    void setTipCPU(const string tipCPU)
    {
        this->tipCPU = tipCPU;
    }
    float getRezolutie() const
    {
        return this->rezolutieEcran;
    }
    void setRezolutie(float rez)
    {
        if (rez > 0)
        {
            this->rezolutieEcran += rez;
        }
        else
        {
            cout << "Rezolutia nu poate fi valoare negativa si ramane setata in starea initiala:  " << this->rezolutieEcran << " pixeli \n";
        }
    }
    bool getCameraWeb() const
    {
        return this->cameraWeb;
    }
    void setCameraWeb(bool value)
    {
        this->cameraWeb = value;
    }
    int getID() const
    {
        return this->id;
    }
    int *getNrApasari() const
    {
        int *temp = new int[this->nrTaste];
        for (int i = 0; i < this->nrTaste; i++)
        {
            temp[i] = this->nrApasariTasta[i];
        }
        return temp;
    }

    friend class Programator;
    friend ostream &operator<<(ostream &os, const Laptop &l1)
    {
        os << "Laptop-ID: -->> " << l1.id
           << " ; Laptop RAM: -->> " << l1.RAM
           << " ; Laptop tip CPU: -->> " << l1.tipCPU
           << " ; Laptop rezolutie ecran : -->> " << l1.rezolutieEcran << " pixeli."
           << " ; Latop are camera web: -->> " << (l1.cameraWeb ? "DA" : "NU")
           << " ; Laptop are numar taste: -->> " << l1.nrTaste << endl;
        for (int i = 0; i < l1.nrTaste; i++)
        {
            os << " ; Numar apasari taste: " << l1.nrApasariTasta[i] << endl;
        }
        return os;
    }
    virtual void display() const
    {
        cout << "Laptop-ID: -->> " << this->id
             << " ; Laptop RAM: -->> " << this->RAM
             << " ; Laptop tip CPU: -->> " << this->tipCPU
             << " ; Laptop rezolutie ecran : -->> " << this->rezolutieEcran << " pixeli."
             << " ; Latop are camera web: -->> " << (this->cameraWeb ? "DA" : "NU")
             << " ; Laptop are numar taste: -->> " << this->nrTaste << endl;
        for (int i = 0; i < this->nrTaste; i++)
        {
            cout << " ; Numar apasari taste: " << this->nrApasariTasta[i] << endl;
        }
    }
    virtual ~Laptop()
    {
        if (this->nrApasariTasta != nullptr)
        {
            delete[] this->nrApasariTasta;
            cout << "Destructor Laptop accesat... \n";
        }
    }
};

// class Componente, clasa derivata din clasa Laptop(de baza), mostenire public (acces);
class Componente : public Laptop
{

private:
    string placaDeBaza;
    string placaVideo;
    int nrSSD;
    int *capacitate;

public:
    // constructor implicit;
    Componente() : Laptop(), placaDeBaza(""), placaVideo(""), nrSSD(0)
    {
        this->capacitate = nullptr;
    }
    // constructor cu parametrii;
    Componente(int RAM, const string &tipCPU, float rez, bool cameraWeb, int nrTaste, int *nrApasari, const string &placaDeBaza, const string &placaVideo, int nrSSD, int *capacitate) : Laptop(RAM, tipCPU, rez, true, nrTaste, nrApasari), placaDeBaza(placaDeBaza), placaVideo(placaVideo), nrSSD(nrSSD)
    {
        this->capacitate = new int[nrSSD];
        for (int i = 0; i < nrSSD; i++)
        {
            this->capacitate[i] = capacitate[i];
        }
    }
    // constructor de copiere;;
    Componente(const Componente &comp) : Laptop(comp), placaDeBaza(comp.placaDeBaza), placaVideo(comp.placaVideo), nrSSD(comp.nrSSD)
    {
        this->capacitate = new int[comp.nrSSD];
        for (int i = 0; i < comp.nrSSD; i++)
        {
            this->capacitate[i] = comp.capacitate[i];
        }
    }
    // operator de atribuire;
    Componente &operator=(const Componente &c)

    {
        if (this != &c)
        {
            (Laptop) *this = (Laptop)c;
            delete[] this->capacitate;
            this->placaDeBaza = c.placaDeBaza;
            this->placaVideo = c.placaVideo;
            this->nrSSD = c.nrSSD;
            if (this->capacitate != nullptr)
            {

                this->capacitate = new int[c.nrSSD];
                for (int i = 0; i < c.nrSSD; i++)
                {
                    this->capacitate[i] = c.capacitate[i];
                }
            }
        }
        return *this;
    }
    string getPlacaVideo() const
    {
        return this->placaVideo;
    }
    void setPlacaVideo(const string &pV)
    {
        this->placaVideo = pV;
    }
    ~Componente()
    {
        delete[] this->capacitate;
        cout << "Destructor derivat chemat: \n";
    }
    void display() const override
    {
        Laptop::display();
        cout << " Placa de baza: " << this->placaDeBaza << endl;
        cout << "; Placa video: " << this->placaVideo << endl;
        cout << "; Numar SSD-uri: " << this->nrSSD << endl;
        for (int i = 0; i < this->nrSSD; i++)
        {
            cout << this->capacitate[i] << endl;
        }
    }
};

// class Programator;
class Programator
{
private:
    string nume;
    Laptop laptopPrincipal; // relatia has-a;
public:
    Programator() : nume("") {}
    Programator(const Laptop &laptop1, string nume) : laptopPrincipal(laptop1), nume(nume) {}
    Programator(const Programator &prog) : laptopPrincipal(prog.laptopPrincipal), nume(prog.nume) {}

    bool poateIntraInConferintaVideo()
    {
        return this->laptopPrincipal.cameraWeb;
    }
    void display() const
    {
        cout << "Numele Progamatorului: -->> " << this->nume << endl;
        cout << laptopPrincipal << endl;
    }
    ~Programator()
    {
        cout << "Chemat" << endl;
    }
};

// initializare membru static;
int Laptop::nrLaptopuri = 0;

int main()

{

    Programator programator;
    Laptop laptop;
    Laptop laptop1(16, "Intel", 77.88, true, 4, new int[4]{12, 14, 13, 27});
    cout << laptop1 << endl;
    cout << endl;
    Laptop laptop2(laptop1); // constructor copy called;
    cout << laptop2 << endl;
    Laptop laptop3(32, "INTEL i7", 88.99, true, 5, new int[5]{44, 55, 66, 77, 88});
    laptop3.setMaxRAM(48);
    laptop1 = laptop3 + 5.5f;
    laptop1 = laptop3 + 8; // overloading operator (+);
    cout << laptop1 << endl;
    Programator programator1(laptop3, "Radu");
    programator1.display();
    cout << (programator1.poateIntraInConferintaVideo() ? "Poate sa intre cu camera video " : "NU") << endl;
    cout << endl;

    Componente c;
    c.display();
    cout << endl;
    int *param = new int[3]{1, 2, 3};
    // upcasting;
    Laptop *laptop500 = new Componente(32, "Intel i7", 79.99, true, 3, param, "Asus Prime", "Nvidia GTX 4050", 2, new int[2]{256, 512});
    *laptop500 = *laptop500 + 2;
    laptop500->setTipCPU("Intel Killin i9");
    laptop500->display();
    cout << endl;
    // eliberare memorie alocata.
    int *apasari = laptop1.getNrApasari();
    for (int i = 0; i < 5; i++)
    {
        cout << apasari[i] << endl;
    }
    int *taste = new int[3]{100, 200, 300};
    cout << endl;
    Componente c3(16, "AMD", 88.99, false, 3, taste, "AcerRocket", "Nvidia 5060GTX", 3, new int[3]{128, 256, 512});
    Componente c4(c3); // constructor de copiere;
    c3.setRezolutie(99.99);
    cout << "Rezolutie: " << c3.getRezolutie() << endl;
    c3.setPlacaVideo("Nvidia GTX 5588x");
    c3.display();
    Componente c5(32, "Intel I8", 84.86, false, 2, new int[2]{10, 20}, "Voodoo 3D", "Nvidia GTS 8800", 1, new int[1]{512});
    Componente c6;
    c6 = c5;
    c5.setCameraWeb(true);
    c5.setRezolutie(5.5);
    c5 += 16;
    c5.setPlacaVideo("Nvidia GTSX 8900x");
    c5.display();
    cout << endl;
    delete[] apasari;
    delete[] param;
    delete[] laptop500;
    delete[] taste;
    return 0;
}
