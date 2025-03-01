#include <iostream>
#include <vector>
#include <cstring>
#include <string>
using namespace std;

class FlowerShop
{
private:
    const int shopId;
    char *name;
    string typeLocation;
    bool hasWebsite;
    string url;
    int nrSoldFlowers;
    static const float averageFlowerPrice;

public:
    FlowerShop() : shopId(0), typeLocation(""), hasWebsite(false), url(""), nrSoldFlowers(0)
    {
        this->name = new char[strlen("Unknown") + 1];
        strcpy(this->name, "Unknown");
    }
    FlowerShop(const int Id, const char *shopName, const string &loc, int nrSoldFlowers) : shopId(Id), typeLocation(loc), nrSoldFlowers(nrSoldFlowers)
    {
        this->name = new char[strlen(shopName) + 1];
        strcpy(this->name, shopName);
        this->hasWebsite = false;
        this->url = "N/A";
    }
    FlowerShop(const FlowerShop &fs) : shopId(fs.shopId), typeLocation(fs.typeLocation), hasWebsite(fs.hasWebsite), url(fs.url), nrSoldFlowers(fs.nrSoldFlowers)
    {
        this->name = new char[strlen(fs.name) + 1];
        strcpy(this->name, fs.name);
    }
    FlowerShop &operator=(const FlowerShop &fs1)
    {
        if (this != &fs1)
        {
            delete[] this->name;
            this->typeLocation = fs1.typeLocation;
            this->hasWebsite = fs1.hasWebsite;
            this->url = fs1.url;
            this->nrSoldFlowers = fs1.nrSoldFlowers;
            if (fs1.name != nullptr)
            {
                this->name = new char[strlen(fs1.name) + 1];
                strcpy(this->name, fs1.name);
            }
        }
        else
        {
            this->name = nullptr;
        }
        return *this;
    }
    FlowerShop operator+(int value)
    {
        FlowerShop temp = *this;
        temp.nrSoldFlowers += value;
        return temp;
    }
    friend FlowerShop operator+(int value, const FlowerShop &fs)
    {
        FlowerShop temp(fs);
        temp.nrSoldFlowers += value;
        return temp;
    }
    FlowerShop &operator+=(int value)
    {
        this->nrSoldFlowers += value;
        return *this;
    }
    FlowerShop &operator++(int)
    {
        this->nrSoldFlowers++;
        return *this;
    }
    FlowerShop &operator--(int)
    {
        this->nrSoldFlowers--;
        return *this;
    }
    bool operator==(const FlowerShop &fs)
    {
        return this->nrSoldFlowers == fs.nrSoldFlowers;
    }
    const char *getName()
    {
        return this->name;
    }
    void setName(const char *newName)
    {
        if (this->name != nullptr)
        {
            delete[] this->name;
        }
        this->name = new char[strlen(newName) + 1];
        strcpy(this->name, newName);
    }
    const getShopId()
    {
        return this->shopId;
    }
    int getNrSoldFlowers() const
    {
        return this->nrSoldFlowers;
    }
    void setNrSoldFlowers(int value)
    {
        this->nrSoldFlowers = value;
    }
    bool setHasWebsite(bool value)
    {
        this->hasWebsite = value;
    }
    string OpenWebsite(const string &url)
    {
        this->url = url;
    }
    float getTotalRevenue() const
    {
        return this->nrSoldFlowers * averageFlowerPrice;
    }
    ~FlowerShop()
    {
        if (this->name != nullptr)
        {
            delete[] this->name;
        }
        cout << "FlowerShop* has been freed from memory: \n";
    }
    void display()
    {
        cout << " ShopId: -->> " << this->shopId << endl;
        cout << " Shop Name: -->> " << (this->name ? this->name : "/") << endl;
        cout << " Shop Location: -->> " << this->typeLocation << endl;
        cout << " Flower shop has website: -->> " << (this->hasWebsite ? "Yes" : "No") << endl;
        cout << " FlowerShop site: -->> " << this->url << endl;
        cout << " FlowerShop number of flowers sold: " << this->nrSoldFlowers << " By/day " << endl;
        cout << " Average of flowers sold: -->> " << averageFlowerPrice << endl;
    }
    friend ostream &operator<<(ostream &out, const FlowerShop &fs) {}
};

// initializare variabila statica;
const float FlowerShop::averageFlowerPrice = 7.5;

int main()
{
    FlowerShop f1(1, "Maria", "Online", 15);
    // f1.display();
    f1.setName("Bella");
    f1.display();
    cout << "---------------------------------------------------------------------------\n";
    cout << "FlowerShop Id: -->> " << f1.getShopId() << endl;
    cout << "Name of FlowerShop: -->> " << f1.getName() << endl;
    cout << "Today FlowerShop, sold: -->> " << f1.getNrSoldFlowers() << " flowers " << endl;
    f1.OpenWebsite("www.maria.ro");
    f1.setHasWebsite(true);
    cout << "FlowerShop total revenue: -->> " << f1.getTotalRevenue() << " $ " << endl;
    cout << "-----------------------------------------------------------------------------\n";
    cout << "Copy constructor used: -->> \n";
    FlowerShop f2(f1);
    f2.display();
    FlowerShop f3(2, "Daisy", "Location", 35);
    f1 = f3; // overloading operator(=);
    f1.display();

    f3 = 23 + f1;
    f1.display();
    cout << endl;
    f3.display();
    f1 += 47;
    f1.display();
    cout << endl;
    f1--;
    f1++;
    f1.display();
    if (f1 == f2)
    {
        cout << "=" << endl;
    }
    else
    {
        cout << " not equal " << endl;
    }
    return 0;
}