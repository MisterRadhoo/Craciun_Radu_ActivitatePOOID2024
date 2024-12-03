#include <iostream>
using namespace std;

// Blueprint, class Adidas;
class Adidas
{
public:
    float *masura;
    string material1;
    string material2;
    string brand;
    string materialTalpa;
    string fabricant;
    string taraDeOrigine;
    // Creare constructor functie;
    Adidas()
    {

        this->masura = new float(42.5); // alocare memorie pentru variabila "this->masura";
        this->material1 = "Piele";
        this->material2 = "Piele Sintetica";
        this->brand = "Air Jordan";
        this->materialTalpa = "Cauciuc";
        this->fabricant = "Nike";
        this->taraDeOrigine = "Fabricat in China";
    }

    Adidas(string newBrand, float newSize)
    {
        this->masura = new float(newSize); // alocare memorie;
        this->material1 = "Piele";
        this->material2 = "Piele Sintetica";
        this->brand = newBrand;
        this->materialTalpa = "Cauciuc";
        this->fabricant = "Nike";
        this->taraDeOrigine = "Fabricat in China";
    }
    Adidas(float newSize2,
           string newMaterial1,
           string newMaterial2,
           string newBrand,
           string newMaterialTalpa,
           string newFabricant,
           string newOriginCountry)
    {
        this->masura = new float(newSize2); // alocare memorie
        this->material1 = newMaterial1;
        this->material2 = newMaterial2;
        this->brand = newBrand;
        this->materialTalpa = newMaterialTalpa;
        this->fabricant = newFabricant;
        this->taraDeOrigine = newOriginCountry;
    }
    // Functie membra a clasei Adidas, adauga culoare;
    void addColor(string color)
    {
        if (color == "Red" || color == "Black" || color == "White" || color == "Blue")
        {
            cout << "Culoarea la adidasi: " << color << endl;
        }
        else
            cout << "Schimbati-o, Multummim!!! " << endl;
    }
    // Destructor functie pentru eliberarea memoriei alocate dinamic;
    ~Adidas()
    {
        delete masura; // eliberare memorie pentru pointerul 'masura' de tip float;
    }
    void toDisplay()
    {

        cout << "Masura este: " << *(this->masura) << endl;
        cout << "Brand adidas: " << this->brand << endl;
        cout << "Material de deasupra este: " << this->material1 << endl;
        cout << "Material de jos este: " << this->material2 << endl;
        cout << "Talpa adidasului e din: " << this->materialTalpa << endl;
        cout << "Fabricat de: " << this->fabricant << endl;
        cout << "Tara unde a fost fabricat adidasul: " << this->taraDeOrigine << endl;
    }
};

int main()
{
    Adidas adidas1; // creare obiect1;
    adidas1.addColor("Black");
    adidas1.toDisplay();
    cout << endl;                      // blank space between objects;
    Adidas adidas2("Air Force", 43.5); // creare obiect2;
    adidas2.addColor("Green");
    adidas2.toDisplay();
    cout << endl;
    Adidas adidas3(41.5, "Panza", "Panza", "SB", "Spuma", "Nike SB", "Fabricat in Vietnam"); // obiect3;
    adidas3.toDisplay();
    return 0;
}