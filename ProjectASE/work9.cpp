#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <stack>
#include <iomanip>
using namespace std;

class Casa
{
private:
    bool cuEtaj;
    float ampretaSol;     // suprafata metrii patrati;
    int deschidereLaDrum; // lungime metrii;
    char *adresa;

public:
    Casa()
    {
        this->cuEtaj = false;
        this->ampretaSol = 0;       // suprafata metrii patrati;
        this->deschidereLaDrum = 0; // lungime metrii;
        this->adresa = new char[strlen("Unknown") + 1];
        strcpy(this->adresa, "Unknown");
    }
    Casa(bool cuEtaj, float amprentaSol, int descDrum, const char *adresaNoua)
    {
        this->cuEtaj = cuEtaj;
        this->ampretaSol = amprentaSol;
        this->deschidereLaDrum = descDrum;
        this->adresa = new char[strlen(adresaNoua) + 1];
        strcpy(this->adresa, adresaNoua);
    }
    Casa(const Casa &copy)
    {
        this->cuEtaj = copy.cuEtaj;
        this->ampretaSol = copy.ampretaSol;
        this->deschidereLaDrum = copy.deschidereLaDrum;
        this->adresa = new char[strlen(copy.adresa) + 1];
        strcpy(this->adresa, copy.adresa);
    }
    ~Casa()
    {

        if (this->adresa != nullptr)
        {
            delete[] this->adresa;
        }
        cout << "Casa a fost construita: --->>  Top\n";
    }
    Casa &operator=(const Casa &c)
    {
        if (this != &c)
        {
            delete[] this->adresa;
            this->cuEtaj = c.cuEtaj;
            this->ampretaSol = c.ampretaSol;
            this->deschidereLaDrum = c.deschidereLaDrum;
            if (c.adresa != nullptr)
            {
                this->adresa = new char[strlen(c.adresa) + 1];
                strcpy(this->adresa, c.adresa);
            }
            else
            {
                this->adresa = nullptr;
            }
        }
        return *this;
    }
    Casa &operator!()
    {
        this->cuEtaj = !this->cuEtaj;
        return *this;
    }
    operator float()
    {
        return this->ampretaSol;
    }
    const char *getAdresa()
    {
        return this->adresa;
    }
    void setAdresa(const char *newAdresa)
    {
        if (this->adresa != nullptr)
        {
            delete[] this->adresa;
        }
        this->adresa = new char[strlen(newAdresa) + 1];
        strcpy(this->adresa, newAdresa);
    }
    int getDeschidereLaDrum() const
    {
        return this->deschidereLaDrum;
    }
    void setDeschidereLaDum(int value)
    {
        this->deschidereLaDrum = value;
    }
    float getAmprentaLaSol() const
    {
        return this->ampretaSol;
    }
    friend ostream &operator<<(ostream &out, const Casa &c)
    {
        out << " Casa are etaj: -->> " << (c.cuEtaj ? "Da" : "Nu")
            << "; Ce suprafara are casa ? (m^2): -->> " << c.ampretaSol << " metrii patrati "
            << "; Ce dimensinea are deschiderea la drum a casei: -->> " << c.deschidereLaDrum << " m "
            << "; Adresa casei este: -->> " << c.adresa << endl;
        return out;
    }
};

class Camera : public Casa
{

private:
    float inaltimePerete;

public:
    Camera() : Casa(), inaltimePerete(0) {}
    Camera(bool cuEtaj, float amprentaSol, int deschidereLaDrum, const char *adresa, float hPerete) : Casa(cuEtaj, amprentaSol, deschidereLaDrum, adresa), inaltimePerete(hPerete) {}
    friend ostream &operator<<(ostream &out, const Camera &c)
    {
        out << " Camera casei are o H a peretelui: -->> " << c.inaltimePerete << " metrii " << endl;
        out << (Casa)c << endl;
        return out;
    }
    float getLatimePerete() const
    {
        float Latime = getAmprentaLaSol() / this->inaltimePerete;
        return Latime;
    }
};

int main()
{
    Casa c;
    cout << c << endl;
    Casa c1(true, 78.88, 9, "Str Diamantului nr.2");
    c1.setAdresa("Str. Rubinului nr.99");
    !c1;
    cout << c1 << endl;
    float implicit = c1;
    float explicitF = float(c1);
    cout << implicit << endl;
    cout << endl;
    Camera camera(true, 55.66, 7, "str. turturelor nr.42", 11.4);
    cout << fixed << showpoint;
    cout << setprecision(2);
    cout << " Latimea peretului din camera este de: -->> " << camera.getLatimePerete() << endl;
    return 0;
}