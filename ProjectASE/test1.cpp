#include <iostream>
#include <string>
using namespace std;

// Defining Car class;
class Car
{
private:
    const int id; // membrii privati;
    static int nrMasini;
    string company;
    string model;
    int year;
    int *capacity;

public:
    // Constructorul default;
    Car() : id(++nrMasini)
    {
        this->company = "";
        this->model = "";
        this->year = 0;
        capacity = new int(0); // alocare de memorie pentru variabila/membru de date capacitate;
    }
    // Constructorul cu parametrii care inilializeaza lista cu membrii de date a clasei Car;
    Car(string comp, string mdl, int year, int cap) : id(++nrMasini), company(comp), model(mdl), year(year)
    {
        capacity = new int; // alocare memorie pentru pointer-ul capacity de tip int;
        *capacity = cap;    // setam valoarea scapacitatii;
    }
    // Constructorul de copiere;
    Car(const Car &obj) : id(++nrMasini)
    {
        company = obj.company;
        model = obj.model;
        year = obj.year;
        // Deep-copy object;
        capacity = new int;                                       // alocare memorie pentru pointer-ul capacity de tip int;
        *capacity = *(obj.capacity);                              // copiem valoarea capacitatii;
        cout << "Copy construct called, Deep-copy made " << endl; // nu creaza referinta la obiectul copiat, atunci cand user-ul cand defineste Constructor class;
    }
    ~Car()
    {
        delete capacity;
        cout << "Destructor called, memory freed for capacity." << endl;
    }
    // Getter functions to retrive private member variable;
    string getCompany() const
    {
        return company;
    }
    string getModel() const
    {
        return model;
    }
    int getYr() const
    {
        return year;
    }
    int getCapacity() const
    {
        return *capacity;
    }

    // Setter functions to modify private member variable;
    void setCompany(const string &_comp) { company = _comp; }
    void setModel(const string &mdl) { this->model = mdl; }
    void setYr(int year) { this->year = year; }
    void setCapacity(int _cap) { *capacity = _cap; }
    void toDisplay()
    {
        cout << "Car's ID: " << this->id << endl;
        cout << "Company car's Name: -> " << this->company << endl;
        cout << "Model of car: -> " << this->model << endl;
        cout << "Car's year: -> " << this->year << endl;
        cout << "Car's capacity is: " << *(this->capacity) << " liters" << endl;
    }
};

int Car::nrMasini = 0;

int main()
{
    Car car1;
    car1.toDisplay();
    cout << endl;
    Car car2("Renault", "Clio", 2007, 34);
    car2.toDisplay();
    cout << "------------------------------------------------------------------" << endl;
    car2.setCompany("Dacia");
    car2.setModel("Duster");
    car2.setYr(2019);
    car2.setCapacity(42);
    car2.toDisplay(); // afisare modifica obiect 'car2'
    car2.getCompany();
    cout << "Company: " << car2.getCompany() << endl;
    Car car3 = car2; // crearea obiectului 'car3' prin copierea obiectului 'car2'(constructor de copiere);
    car3.toDisplay();

    return 0;
}