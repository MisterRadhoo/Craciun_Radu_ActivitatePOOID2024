#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
// Clase dupa numele "Craciun Radu-Mihai": (CloudService, Router, MachineLearningModel) -> Domeniul IT.
//  Faza 1{Task1-Completed}; Faza 2{Task2-Completed}; Faza 3{Task3-Completed}; Faza 4{Task4-Completed} ; Faza 5{Task5-Completed}; Faza 6{Task6-Completed}; Faza 7{Task7-Completed};
class CloudService
{
private:
    string tipServiciu;
    static int capacitateStocare;
    const string locatieServer;
    float costAbonament;
    int *utilizatoriConectati;

public:
    // Constructor fara parametri;
    CloudService() : tipServiciu("SaaS"), locatieServer("RO"), costAbonament(36.65)
    {
        this->utilizatoriConectati = new int[8];
    }
    // Constructor cu parametrii;
    CloudService(const string &tip, int capacitate) : tipServiciu(tip), locatieServer("BRA"), costAbonament(54.88)
    {
        this->capacitateStocare = capacitate;
        this->utilizatoriConectati = new int[12];
    }
    // Constructor cu toti parametrii;
    CloudService(const string &tip, int capacitate, const string &locatie, float cost) : tipServiciu(tip), locatieServer(locatie), costAbonament(cost)
    {
        this->capacitateStocare = capacitate;
        this->utilizatoriConectati = new int[18];
    } // Constructor de copiere;
    CloudService(const CloudService &cs) : tipServiciu(cs.tipServiciu), locatieServer(cs.locatieServer), costAbonament(cs.costAbonament)
    {
        this->utilizatoriConectati = new int[16];
        for (int i = 0; i < 16; ++i)
        {
            this->utilizatoriConectati[i] = cs.utilizatoriConectati[i];
        }
    } // Destructor;
    ~CloudService()
    {
        delete[] utilizatoriConectati;
        cout << "Service cloud terminat !" << endl;
    }
    // Overloading operators (= operator de atribuire);
    CloudService &operator=(const CloudService &obj)
    {
        if (this != &obj)
        {
            this->tipServiciu = obj.tipServiciu;
            this->costAbonament = obj.costAbonament;
            if (this->utilizatoriConectati != nullptr)
                delete[] this->utilizatoriConectati;
            this->utilizatoriConectati = new int[9];
            for (int i = 0; i < 9; ++i)
            {
                this->utilizatoriConectati[i] = obj.utilizatoriConectati[i];
            }
        }
        return *this;
    }
    // Overloading operator (+), aduna costurile abonamentului;
    CloudService operator+(float costExtra) const
    {
        CloudService temp = *this; // se creeaza o copie temporara o obiectului curent (*this-CloudService), acesta e practica comuna in supraincarcarea operatorilor.
        temp.costAbonament += costExtra;
        return temp;
    }
    // Overloading operator (-), scade costurile abonamentului;
    CloudService operator-(float reducere)
    {
        CloudService temp = *this;
        temp.costAbonament -= reducere;
        return temp;
    }
    // Overloading operator (==), compara doua tipuri de servicii;
    bool operator==(const CloudService &other) const
    {
        return this->tipServiciu == other.tipServiciu;
    }
    // Getters and Setters;- accesare si setare noi date pentru membrii privati ai clasei;
    string getTipServiciu() const
    {
        return this->tipServiciu;
    }
    void setTipServiciu(const string &tip)
    {
        this->tipServiciu = tip;
    }
    float getCostAbonament() const
    {
        return this->costAbonament;
    }
    void setCostAbonament(float cost)
    {
        this->costAbonament = cost;
    }
    static int getCapacitateStocare()
    {
        return capacitateStocare;
    }
    static void setCapacitateStocare(int cap)
    {
        capacitateStocare = cap;
    }
    // Functie care calculeaza costul total; tip static;
    // static float calculCostTotal(float timp, int utilizatori) // Faza1;
    // {

    //     return timp * utilizatori * capacitateStocare * 0.1;
    // }
    void displayCS() const
    {
        cout << "Tip serviciu: " << this->tipServiciu << endl;
        cout << "Capacitatea totala a serviciul: " << capacitateStocare << " GB" << endl;
        cout << "Locatia server-ului cloud: " << this->locatieServer << endl;
        cout << "Costul Abonamentului: " << this->costAbonament << " $" << endl;
        cout << "Numarul de utilizatori conectati: " << *utilizatoriConectati << " abonati" << endl;
    }
    // functie de scriere in fisier text; // Faza 6;
    void scriereInFisierText(const string &file) const
    {
        ofstream outFile(file);
        if (outFile.is_open())
        {
            outFile << this->tipServiciu << "\n"
                    << capacitateStocare << "\n"
                    << this->locatieServer << "\n"
                    << this->costAbonament << "\n";
            outFile.close();
            cout << "Datele au fost scrise/redactate in fisier text: " << file << endl;
        }
        else
        {
            cerr << "Error !!! " << file << endl;
        }
    }
    // functie de citire din fisier text; // Faza 6;
    void citireDinFisierText(const string &file)
    {
        ifstream inFile(file);
        if (inFile.is_open())
        {
            inFile >> this->tipServiciu;
            inFile >> capacitateStocare;
            inFile >> this->costAbonament;
            inFile.close();
            cout << "Datele au fost citire din fisier text: " << file << endl;
        }
        else
        {
            cerr << "Error !!! nu se pot citii datele din fisier@@@ " << file << endl;
        }
    }
    // functie prietena , acceseaza membrii privatii,
    friend void actualizareServiciu(CloudService &cs, float reducere);                     // Faza 2;
    friend CloudService combinaServicii(const CloudService &cs1, const CloudService &cs2); // Faza 3
};
void actualizareServiciu(CloudService &cs, float reducere)
{
    cs.costAbonament -= reducere;
    cout << "S-a facut o reducere de: " << reducere << " $ " << cs.tipServiciu << endl;
}
CloudService combinaServicii(const CloudService &cs1, const CloudService &cs2)
{
    CloudService combined = cs1;
    combined.costAbonament += cs2.costAbonament;
    return combined;
}

class Router
{
private:
    const string tipRouter;
    int numarPorturi;
    static int vitezaMaxima;
    string producator;
    int *reteleConectate;

public:
    // Constructor fara parametri;
    Router() : tipRouter("Wired"), numarPorturi(4), producator("Acer")
    {
        this->reteleConectate = new int[8];
    }
    // Constructor cu parametri;
    Router(const string &tip, int porturi) : tipRouter(tip), numarPorturi(porturi), producator("R-Link")
    {

        this->reteleConectate = new int[12];
    } // Constructor cu toti parametrii;
    Router(const string &tip, int porturi, string prod) : tipRouter(tip), numarPorturi(porturi), producator(prod)
    {

        this->reteleConectate = new int[21];
    }
    // Constructor de copiere;
    Router(const Router &r) : tipRouter(r.tipRouter), numarPorturi(r.numarPorturi), producator(r.producator)
    {
        this->reteleConectate = new int[17];
        for (int i = 0; i < 17; ++i)
        {
            this->reteleConectate[i] = r.reteleConectate[i];
        }
    }
    // Destructor;
    virtual ~Router()
    {
        delete[] this->reteleConectate;
        cout << "Nicio retea nu mai este conectata. " << endl;
    }
    // Operator de atribuire (=) obiectului Router prin referinta, overloading;
    Router operator=(const Router &r)
    {
        if (this != &r)
        {
            delete[] reteleConectate;
            numarPorturi = r.numarPorturi;
            producator = r.producator;
            this->reteleConectate = new int[7];
            for (int i = 0; i < 7; ++i)
            {
                this->reteleConectate[i] = r.reteleConectate[i];
            }
        }
        return *this;
    } // Operator de adaugare (+) porturi router, overloading;
    Router operator+(int porturi) const
    {
        Router temp = *this;
        temp.numarPorturi += porturi;
        return temp;
    } // Operator de scadere(-) porturi router, overloading;
    Router operator-(int porturiMinus) const
    {
        Router Port = *this;
        Port.numarPorturi -= porturiMinus;
        return Port;
    }
    // Operator pentru comparare (==) tipuri de router, overloading;
    bool operator==(const Router &router) const
    {
        return this->tipRouter == router.tipRouter;
    }
    //  Getters and Setters;
    int getNrPorturi() const
    {
        cout << this->numarPorturi << endl;
        return this->numarPorturi;
    }
    void setNrPorturi(int port)
    {
        this->numarPorturi = port;
    }
    string getProducator() const
    {
        return this->producator;
    }
    void setProducator(const string &prod)
    {
        this->producator = prod;
    }
    static int getVitezaMaxima()
    {
        return vitezaMaxima;
    }
    static void setVitezaMaxima(int viteza)
    {
        vitezaMaxima = viteza;
    }
    // Functia prieten;
    friend void optimizeazaBanda(Router &router, int viteza);    // Faza 2;
    friend Router upgRouter(const Router &r1, const Router &r2); // Faza 3;
    // functie statica de calcul;
    // static int calculBandaTotala(int numarPorturi)  // Faza1'
    // {
    //     return numarPorturi * vitezaMaxima;
    // }
    virtual void displayR() const
    {
        cout << "Conexiunea Router: " << this->tipRouter << endl;
        cout << "Numarul de porturi Router: " << this->numarPorturi << endl;
        cout << "Viteza de prelucrare a streaming-ului de date: " << this->vitezaMaxima << " Mbps" << endl;
        cout << "Fabricant: " << this->producator << endl;
    }

    // Functia de scriere in fisier text; // Faza 6;
    void scriereInFisierText(const string &file)
    {
        ofstream outFile(file);
        if (outFile.is_open())
        {
            outFile << this->tipRouter << "\n"
                    << this->numarPorturi << "\n"
                    << vitezaMaxima << "\n"
                    << this->producator << "\n";
            outFile.close();
            cout << "Datele routerului au fost scrise in fisier text: " << file << endl;
        }
        else
        {
            cerr << "Error !!!cannot read text file. " << file << endl;
        }
    }
    // Functia de citire din fisier text; // Faza 6;
    void citireDinFisierText(const string &file)
    {
        ifstream inFile(file);
        if (inFile.is_open())
        {
            string tempTipRouter;
            int tempNumarPorturi;
            int tempVitezaMaxima;
            string tempProducator;

            inFile >> tempTipRouter;
            inFile >> tempNumarPorturi;
            inFile >> tempVitezaMaxima;
            inFile >> tempProducator;

            this->numarPorturi = tempNumarPorturi;
            vitezaMaxima = tempVitezaMaxima;
            this->producator = tempProducator;

            cout << "Datele sunt citite din fisier text si actuliazate in obiect: \n";
            cout << "Tip router: -->> " << tempTipRouter << "\n";
            cout << "Numarul de porturi router: -->> " << this->numarPorturi << "\n";
            cout << "Maximum Speed -->> " << vitezaMaxima << " Mbps" << "\n";
            cout << "Fabricant router: -->> " << this->producator << "\n";
            inFile.close();
        }
        else
        {
            cerr << "Error !!! cannot open file text. " << file << endl;
        }
    }
    // Functie care scrie in fisier binar; // Faza 6;
    void sFB(const string &fb)
    {
        ofstream outFile(fb, ios::binary);
        if (outFile.is_open())
        {
            outFile.write((char *)&this->numarPorturi, sizeof(this->numarPorturi));
            outFile.write((char *)&vitezaMaxima, sizeof(vitezaMaxima));
            size_t prodSize = this->producator.size();
            outFile.write((char *)&prodSize, sizeof(prodSize));
            outFile.write(this->producator.c_str(), prodSize);
            cout << "Datele router-ului sunt scrise/redactate in fisier binar: " << fb << endl;
            outFile.close();
        }
        else
        {
            cerr << "Error !! cannot write on binary file. " << fb << endl;
        }
    }
    // Functie care citeste fisier binar; // Faza 6;
    void cFB(const string &file)
    {
        ifstream inFile(file, ios::binary);
        if (inFile.is_open())
        {
            int tempNrPorturi;
            int tempVitezaMaxima;
            size_t prodSize;
            char *tempProducator;

            inFile.read((char *)&tempNrPorturi, sizeof(tempNrPorturi));
            inFile.read((char *)&tempVitezaMaxima, sizeof(tempVitezaMaxima));
            inFile.read((char *)&prodSize, sizeof(prodSize));
            tempProducator = new char[prodSize + 1];
            inFile.read(tempProducator, prodSize);
            tempProducator[prodSize] = '\0';

            cout << "Date citite din fisier binar: \n";
            cout << "Numar porturi router: -->> " << tempNrPorturi << "\n";
            cout << "Max Speed router: -->> " << tempVitezaMaxima << " Mbps" << "\n";
            cout << "Fabricant router: -->> " << tempProducator << endl;
            delete[] tempProducator;
            inFile.close();
        }
        else
        {
            cerr << "Error !!! cannot open binary file. " << file << endl;
        }
    }
};

void optimizeazaBanda(Router &router, int viteza)
{
    if (viteza > Router::vitezaMaxima)
        router.numarPorturi -= -1;
    cout << "Viteza a crescut, nr. de porturi s-a redus cu: " << router.numarPorturi << " :Viteza Maxima pe router e: " << viteza << endl;
}
Router upgRouter(const Router &r1, const Router &r2)
{
    Router upgraded = r1;
    upgraded.numarPorturi += r2.numarPorturi;
    return upgraded;
}
// Clasa derivata, Faza 7.
class AdvancedRouter : public Router
{
private:
    bool support5G;

public:
    // Constructor fara parametrii,'Router'- apelam explicit constructorul clasei de baza pentru initializare a obiectului 'Router';
    AdvancedRouter() : Router(), support5G(false) {}
    // Constructor cu parametrii
    AdvancedRouter(const string &tipRouter, int porturi, const string &producator, bool support) : Router(tipRouter, porturi, producator), support5G(support) {}
    // Getter and Setter
    void setSupport5G(bool support)
    {
        this->support5G = support;
    }
    bool getSupport5G() const
    {
        return this->support5G;
    }
    int getMaxSpeed() const
    {
        return getVitezaMaxima();
    }
    void displayR() const override
    {
        Router::displayR();
        cout << "Router avansat are suport 5G: -->>> " << (this->support5G ? "Da" : "Nu") << endl;
    }
    // Destructor pentru clasa derivata 'AdvanceRouter';
    ~AdvancedRouter()
    {
        cout << "Destructor pentru AdvanceRouter... \n";
    }
};
// Clasa derivata din 'AdvacedRouter'; Faza 7;
class PortableRouter : public AdvancedRouter
{
private:
    int capacitateBaterie;

public:
    // Constructor fara parametri;
    PortableRouter() : AdvancedRouter(), capacitateBaterie(0) {}
    // Constructor cu parametrii;
    PortableRouter(const string &tipRouter, int nrPorturi, const string &producator, bool support5G, int baterie) : AdvancedRouter(tipRouter, nrPorturi, producator, support5G), capacitateBaterie(baterie) {}
    // Setter and getter;
    int getCapacitateBaterie() const
    {
        return this->capacitateBaterie;
    }
    void setCapacitateBaterie(int capacitate)
    {
        if (capacitate > 2000)
        {
            this->capacitateBaterie = capacitate;
        }
        else
        {
            cout << "Warning !!! Low batterry, Must be recharged !!! \n";
            this->capacitateBaterie = 2000;
            cout << "Battery remains at: " << this->capacitateBaterie << " mAh \n";
        }
    }
    void displayR() const override
    {
        Router::displayR();
        cout << "Router avansat are suport 5G: -->>> " << (getSupport5G() ? "Da" : "Nu") << endl;
        cout << "Capacitatea bateriei a router-lui e de: " << this->capacitateBaterie << " mAh \n";
    }
    double calculeazaDurata(int consumPeOra) const
    {
        return static_cast<double>(capacitateBaterie) / consumPeOra;
    }

    ~PortableRouter()
    {
        cout << "Destructor pentru PortableRouter chemat.....\n";
    }
};

class MachineLearningModel
{
private:
    const string tipModel;
    static int numarParametrii;
    float precizie;
    int numarEpoci;        // iteratii, trece prin datele de antrenament in mod automat, facand niste iteratii,
    float *setAntrenament; //
public:
    // Constructor fara parametri;
    MachineLearningModel() : tipModel("Retea Neurala"), precizie(0.6), numarEpoci(3)
    {
        this->setAntrenament = new float[100]; // alocare de memorie pentru datele de antrenament, maxim 100 elemente in vector;
    }
    // Constructor cu parametri;
    MachineLearningModel(const string &tip, float prec) : tipModel(tip), precizie(prec), numarEpoci(5) { this->setAntrenament = new float[150]; }
    // Constructor cu toti parametrii
    MachineLearningModel(const string &tip, float prec, int epoci) : tipModel(tip), precizie(prec), numarEpoci(epoci)
    {
        this->setAntrenament = new float[200];
    }
    // Constructor de copiere;
    MachineLearningModel(const MachineLearningModel &mlm) : tipModel(mlm.tipModel), precizie(mlm.precizie), numarEpoci(mlm.numarEpoci)
    {
        this->setAntrenament = new float[163];
        for (int i = 0; i < 163; ++i)
        {
            this->setAntrenament[i] = mlm.setAntrenament[i];
        }
    }
    // Destructor;
    ~MachineLearningModel()
    {
        delete[] this->setAntrenament;
        cout << "Elementele din vector au fost reduse la 0." << endl;
    } // Overloading operator (=), de atribuire;
    MachineLearningModel operator=(const MachineLearningModel &ml)
    {
        if (this != &ml)
        {
            this->precizie = ml.precizie;
            this->numarEpoci = ml.numarEpoci;
            if (this->setAntrenament != nullptr)
            {
                delete[] this->setAntrenament;
                this->setAntrenament = new float[85];
                for (int i = 0; i < 85; ++i)
                {
                    this->setAntrenament[i] = ml.setAntrenament[i];
                }
            }
        }
        return *this;
    }
    // Overloading operator(+), de adaugare nrEpoci;
    MachineLearningModel operator+(int nrExtraEpoci) const
    {
        MachineLearningModel mlTemp = *this;
        mlTemp.numarEpoci += nrExtraEpoci;
        return mlTemp;
    }
    // Overloading operator(-), de scaderea nrEpoci;
    MachineLearningModel operator-(int minusEpoci) const
    {
        MachineLearningModel tempEpoci = *this;
        tempEpoci.numarEpoci -= minusEpoci;
        return tempEpoci;
    }
    // Overloading operator(==), comparare a tipului de model;
    bool operator==(const MachineLearningModel &obj) const
    {
        return this->tipModel == obj.tipModel;
    }
    // Getter and setter;
    float getPrecizie() const
    {
        return this->precizie;
    }
    void setPrecizie(float prec)
    {
        this->precizie = prec;
    }

    int getNumarEpoci() const
    {
        return this->numarEpoci;
    }
    void setNumarEpoci(int epoca)
    {
        this->numarEpoci = epoca;
    }
    static int getNrParametrii()
    {
        return numarParametrii;
    }
    static void setNrParametrii(int numar)
    {
        numarParametrii = numar;
    }
    // // functia statica de calcul; Faza1;
    // static float calculMemorieNecesara(int numarParametri, float dimensiuneParametru)
    // {
    //     return numarParametri * dimensiuneParametru;
    // }
    void displayML() const
    {
        cout << "Tip(Algoritm): " << this->tipModel << endl;
        cout << "Numarul Parametrii: " << this->numarParametrii << endl;
        cout << "Precizie: " << this->precizie << endl;
        cout << "Numarul de iteratii: " << this->numarEpoci << endl;
    }

    // friend function;
    friend void
    improveModel(MachineLearningModel &ml, float crestePrecizie);                                                  // Faza 2;
    friend MachineLearningModel combinaModele(const MachineLearningModel &mlm1, const MachineLearningModel &mlm2); // Faza 3;
};

void improveModel(MachineLearningModel &ml, float crestePrecizie)
{
    ml.precizie += crestePrecizie;
    cout << "MLM a crescut in precizie <^-^>.... " << ml.precizie << endl;
}
// Friend function care combina 'numarEpoci' a doua obiecte "mlm1" si "mlm2" cu refereinta la clasa 'MachineLearningModel';
MachineLearningModel combinaModele(const MachineLearningModel &mlm1, const MachineLearningModel &mlm2)
{
    MachineLearningModel combinedMLM = mlm1;
    combinedMLM.numarEpoci += mlm2.numarEpoci;
    return combinedMLM;
}
// Class NetworkInfrastructure , Faza 5;
class NetworkInfrastructure
{
private:
    Router mainRouter; // Obiect de tip Router pentru relatia de tip has-a;
    int nrDispozitiveConectate;
    float costMentenantaAnuala;
    vector<CloudService> serviciiCloud; // Vector de obiecte de tip CloudService;
public:
    // Constructor default;
    NetworkInfrastructure() : nrDispozitiveConectate(12), costMentenantaAnuala(2000.55) {}
    // Constructor cu parametrii;
    NetworkInfrastructure(const Router &router, int dispozitive, float cost) : mainRouter(router), nrDispozitiveConectate(dispozitive), costMentenantaAnuala(cost) {}
    // Constructor de copiere;
    NetworkInfrastructure(const NetworkInfrastructure &r) : mainRouter(r.mainRouter), nrDispozitiveConectate(r.nrDispozitiveConectate),
                                                            costMentenantaAnuala(r.costMentenantaAnuala), serviciiCloud(r.serviciiCloud) {}
    // Destructor;
    ~NetworkInfrastructure()
    {
        cout << "Infrastructura retelei a fost eliberata din memorie: \n";
    }
    // Getter and Setter pentru nrDispozitiveConectate;
    int getNrDispozitiveConectate() const { return this->nrDispozitiveConectate; }
    void setNrDispozitiveConectate(int dispozitive) { this->nrDispozitiveConectate = dispozitive; }
    // Getter and Setter pentru constMentenantaAnuala;
    float getCostMentenanta() const { return this->costMentenantaAnuala; }
    void setCostMentenanta(float cost) { this->costMentenantaAnuala = cost; }
    // Overloading operator (+=), pentru a aduga un nou serviciu cloud;
    NetworkInfrastructure &operator+=(const CloudService &cs)
    {
        this->serviciiCloud.push_back(cs);
        return *this;
    }
    // Overloading operator(-), pentru a reduce numarul de dispozitive;
    NetworkInfrastructure operator-(int reduceDispozitive)
    {
        NetworkInfrastructure temp = *this;
        temp.nrDispozitiveConectate -= reduceDispozitive;
        return temp;
    }
    // Overloading operator (==), de comparare a 2 infrastructuri de retea;
    bool operator==(const NetworkInfrastructure &obj) const
    {
        return (this->nrDispozitiveConectate == obj.nrDispozitiveConectate && this->costMentenantaAnuala == obj.costMentenantaAnuala &&
                serviciiCloud.size() == obj.serviciiCloud.size());
    }
    // Afisare;
    void displayNI() const
    {
        cout << "Numar dispozitive conectate: " << this->nrDispozitiveConectate << endl;
        cout << "Cost mentenanta anual: " << this->costMentenantaAnuala << " $" << endl;
        cout << "Router principal: \n";
        mainRouter.displayR();
        cout << "Servicii Cloud conectate: " << serviciiCloud.size() << endl;
        for (const auto &service : serviciiCloud)
        {
            service.displayCS();
        }
    }
};

// initializare atribute statice;
int CloudService::capacitateStocare = 900;      // GB
int Router::vitezaMaxima = 250;                 // Gbps;
int MachineLearningModel::numarParametrii = 80; // valoare numerica;

// Driver Code
int main()
{
    cout << "\n--------------------------Testing CloudService Class--------------------------------------------\n";
    CloudService serviciu1; // creare obiect1;
    serviciu1.displayCS();
    cout << endl;
    CloudService::setCapacitateStocare(1024);
    CloudService serviciu2("PasS", 250); // creare obiect2;
    serviciu2.displayCS();
    cout << endl;
    CloudService serviciu3("IasS", 150, "US", 45.99); // creare obiect3;
    serviciu3.displayCS();
    CloudService serviciu4 = serviciu3; // copy constructor call;
    cout << "------Copy Constructor Called !!-------" << endl;
    serviciu4.displayCS();
    cout << "Setters and Getters" << "-----------------------------------------------------------------" << endl;
    serviciu4.setCapacitateStocare(180);
    cout << "Update Capacitate dupa set: " << serviciu4.getCapacitateStocare() << endl;
    serviciu4.setCostAbonament(35.99);
    cout << "Pret la abonament: " << serviciu4.getCostAbonament() << endl;
    actualizareServiciu(serviciu4, 5.99); // call friend function;
    cout << endl;
    serviciu4.displayCS();
    cout << "\nOverloading Operators--------------------------------------------------------------------\n";
    CloudService serviciu5("NaaS", 99, "FRA", 12.85);
    cout << "\nValori Originale ale obiectului serviciu5 inainte de atribuire pentru serviciu1: \n";
    serviciu5.displayCS();
    serviciu1 = serviciu5; // overloading operator (=) pentru serviciu1, i se atribuie 'tipServiciu' si 'costAbonament';
    cout << "\nValori serviciul1, dupa atribuire,overloading (=): \n";
    serviciu1.displayCS();
    CloudService serviciu6 = serviciu1 + 9.15; // overloading operator(+), adauga costAbonament la serviciu6;
    CloudService serviciu7 = serviciu1 - 2.85; // overloading operator(-), scade costAbonament la serviciu7;
    serviciu6.displayCS();
    serviciu7.displayCS();
    cout << endl;
    CloudService Comb = combinaServicii(serviciu6, serviciu7); // combina costul total al abonamentelor;
    Comb.displayCS();
    cout << endl;
    cout << "Sunt servicile de acelasi tip ? \n";
    // Overloading opertor (==);
    const string comparatie = (serviciu6 == serviciu7) ? "Serviciile sunt de acelasi tip." : "Serviciile nu sunt de acelasi tip. ";
    cout << comparatie << endl;
    //  cout << "Cost Total pentru 12 luni: " << CloudService::calculCostTotal(12, 85) << endl;  // Faza 1;
    cout
        << "Capacitatea totala de stocare este: " << CloudService::getCapacitateStocare() << " GB" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
    cout << "\n---------------------------Testing Router Class------------------------------------------------\n";
    Router router1;
    Router router2("Wired", 6);
    Router router3("Wireless", 8, "Asus");
    router1.displayR();
    cout << endl;
    // router3.displayR();
    Router router4("Wired", 16, "GravaStar"); // creare obiect 4;
    cout << "Getter and Setters:---------------------------------------------------------------------------" << endl;
    router4.setNrPorturi(10);
    cout << "Update Nr. Porturi: " << router4.getNrPorturi() << endl;
    router4.setVitezaMaxima(300);
    cout << "Setare Viteza Max: " << router4.getVitezaMaxima() << endl;
    optimizeazaBanda(router4, 480);
    router4.displayR();
    cout << "\nOverloading operators:------------------------------------------------------------------------------\n";
    Router::setVitezaMaxima(150);
    Router router5("Wireless", 8, "SkyRouter");
    router5.displayR();
    cout << "\nOverloading operator (=) to router1. \n";
    router1 = router5; // overloading operator (=);
    router1.displayR();
    cout << endl;
    Router router6 = router1 + 2;              // overloading (+); adaugam porturi;
    Router router7 = router1 - 3;              // overloading (-) scadem porturi;
    Router upgR = upgRouter(router6, router7); // chemare friend class function;
    optimizeazaBanda(upgR, 300);
    upgR.displayR();
    cout << "Router de acelasi tip? " << endl;
    const string compara = (router6 == router7) ? "Sunt de acelasi tip." : "Nu sunt de acelasi tip.";
    cout << compara << endl;
    cout << "Viteza Maxima pe banda este de: " << Router::getVitezaMaxima() << " Gbps" << endl;
    // cod -> Faza1;
    // cout << "Latimea bandei totale:" << Router::calculBandaTotala(router1.numarPorturi) << " Gbps" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
    cout << "\n----------------------------Testing MachineLearningModel Class----------------------------------\n";
    MachineLearningModel m1;
    m1.displayML();
    cout << endl;
    MachineLearningModel m2("Deep Q-Networks(DQN)", 0.5);            // creare obiect2;
    MachineLearningModel m3("Support Vector Machines(SVM)", 1.3, 6); // creare obiect3;
    m3.displayML();
    MachineLearningModel mlm = m3; // copy constructor call;
    mlm.displayML();
    cout << endl;
    cout << "Getters and Setter-----------------------------------------------------------------------------------------" << endl;
    mlm.setPrecizie(2.6);
    mlm.setNrParametrii(12);
    mlm.setNumarEpoci(7);
    cout << "Update Mlm object: " << "Precizie = " << mlm.getPrecizie() << "," << "Parametrii = " << mlm.getNrParametrii() << "," << "Nr.Epoci= " << mlm.getNumarEpoci() << endl;
    mlm.displayML();
    improveModel(mlm, 0.5);
    cout << endl;
    mlm.displayML();
    cout << "\nOverloading operators...........................................................................\n";
    MachineLearningModel model4("Random Forest", 0.5, 5);
    cout << "\nOverloading Operators (=), (+), (-), (==) pentru MachineLearningModel. \n";
    cout << "Overloading operator(=) de atribuire pentru obiectul 'm1'pentru 'precizie' si 'numarEpoci': " << endl;
    m1 = model4;
    m1.displayML();
    cout << endl;
    cout << "Overloading operator (+) and (-) numarEpoci" << endl;
    MachineLearningModel model5 = m1 + 9;                            // overloading operator(+), adaugam numarEpoci;
    MachineLearningModel model6 = m1 - 3;                            // overloading operator (-), scadem numarEpoci;
    MachineLearningModel combinaMLM = combinaModele(model5, model6); // call class friend function;
    combinaMLM.displayML();
    cout << "Numar de epoci: al obiectului combinat din modelele (model5) si (model6) --->>> " << combinaMLM.getNumarEpoci() << endl;
    cout << endl;
    cout << "Overloading operatorul (==) daca sunt de acelasi tip model5 si model 6 ? \n";
    string compare = (model5 == model6) ? "Same Type: " : "Not same type ";
    cout << compare << endl;
    cout << endl;
    // Cod -> Faza 1;
    // cout << "Memorie Necesara: -> " << MachineLearningModel::calculMemorieNecesara(250, 0.725) << " MB" << endl;
    cout << "\n--Vectori si Matrice pentru clase---------------Faza 4--------------------------------------- \n"; // Faza 4;

    vector<CloudService> vectorCloudServices;
    vector<Router> vectorRouters;
    vector<MachineLearningModel> vectorMLM;
    cout << "\nIntroduceti date pentru obiecte in CloudServices: \n";
    int nrCloud;
    cin >> nrCloud;
    for (int i = 0; i < nrCloud; ++i)
    {
        string tip;
        int capacitate;
        string locatie;
        float cost;
        cout << "Introduceti tip serviciu: \n";
        cin >> tip;
        cout << "Capacitatea server-ului: \n";
        cin >> capacitate;
        cout << "Locatia Server-ului: \n";
        cin >> locatie;
        cout << "Cost abonament: \n";
        cin >> cost;
        CloudService cs(tip, capacitate, locatie, cost);
        vectorCloudServices.push_back(cs);
    }
    cout << "\nObiecte CloudService: \n";
    for (const auto &cs : vectorCloudServices)
    {
        cs.displayCS();
    }
    cout << endl;
    cout << "\nAdd Router objects in vectorRouters: \n";
    int nrR;
    cin >> nrR;

    for (int i = 0; i < nrR; ++i)
    {
        string tip;
        int porturi;
        string producator;
        cout << "\nType of Router (Wired/Wireless): \n";
        cin >> tip;
        cout << "\nPorts numbers: \n";
        cin >> porturi;
        cout << "\nWas build by: \n";
        cin >> producator;
        Router r(tip, porturi, producator);
        cout << r.getVitezaMaxima() << " Mbps Speed" << endl;
        vectorRouters.push_back(r);
    }
    for (auto &r : vectorRouters)
    {
        r.displayR();
    }
    cout << endl;
    cout << "\nAdaugare MLM obiecte in vectorMLM: \n";
    int nrMLM;
    cin >> nrMLM;
    for (int i = 0; i < nrMLM; ++i)
    {
        string tip;
        float precizie;
        int nrEpoci;
        cout << "\nAlgoritmul obiectului MLM: \n";
        cin >> tip;
        cout << "\nPrecizia obiectului MLM: \n";
        cin >> precizie;
        cout << "\nNumarul de iteratii al obiectului MLM: \n";
        cin >> nrEpoci;
        MachineLearningModel mlm(tip, precizie, nrEpoci);
        cout << "Numarul de parametrii -->> " << mlm.getNrParametrii() << endl;
        vectorMLM.push_back(mlm);
    }
    for (auto &mlm : vectorMLM)
    {
        mlm.displayML();
    }
    // Creare si afisarea matricei de obiecte CloudService; // Faza 4;
    // Capacitatea tuturor instantelor de obiecte dupa clasa CloudService, va fi determinata, atunci cand setezi "capaciatea"
    // pentru ultimul obiect citit de la tastura, atributul 'static int capacitate' este de tip static si este valabil pentru toate instantele de obiect create
    // dupa clasa CloudService, el nu poate fii modificat, numai daca ii schimbi tipul de data in -> ( int capacitate).
    int rows, cols;
    cout << "\nIntroduceti nr. de randuri si coloane pentru matrice: \n";
    cin >> rows >> cols;
    vector<vector<CloudService>> matrixCS(rows, vector<CloudService>(cols));
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            string tip;
            int capacitate;
            string locatie;
            float cost;
            cout << "\nIntroducere date pentru CloudService[" << i << "][" << j << "]:\n";
            cout << "Tip serviciu: \n";
            cin >> tip;
            cout << "Capacitate Stocare (GB): \n";
            cin >> capacitate;
            cout << "Locatie server: \n";
            cin >> locatie;
            cout << "Cost abonament ($): \n";
            cin >> cost;
            // Initializare matrice;
            matrixCS[i][j] = CloudService(tip, capacitate, "default", cost);
        }
    }
    // Afisare Matrice;
    cout << "\nAfisare Matrice CloudService: \n";
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            cout << "CloudService: [" << i << "][" << j << "]: \n";
            matrixCS[i][j].displayCS();
            cout << endl;
        }
    }
    cout << endl;
    cout << "\n----------------------------Testing NetworkInfrastructure Class----Faza 5-----------------------\n";
    Router routerPrincipal("Wireless", 16, "Dell"); // creare obiect routerPrincipal al clasei 'Router';
    routerPrincipal.displayR();
    cout << endl;
    NetworkInfrastructure infra(routerPrincipal, 15, 759.99); // creare obiect de tip 'NetworkInfrastructe';
    infra.displayNI();
    cout << endl;
    CloudService cs("NaaS", 87, "BHS", 58.99); // creare obiect 'cs' de tip 'CloudService';
    CloudService cs2 = cs - 4.99;
    cs.displayCS();
    cout << endl;
    CloudService::setCapacitateStocare(120);
    cs2.displayCS();
    infra += cs2; // overloading operator (+=);
    cout << "After a cloud service have been added, the infrastructure will be: \n";
    infra.displayNI();
    cout << endl;
    NetworkInfrastructure infra2 = infra - 3; // overloading operator (-);
    infra2.displayNI();
    cout << endl;
    infra2.setNrDispozitiveConectate(25);
    cout << "Nr. de dispozitve conectate: " << infra2.getNrDispozitiveConectate() << endl;
    cout << "Cost Mentenanta anuala: " << infra2.getCostMentenanta() << " $" << endl;
    cout << endl;
    cout << "-------------------------------File Handling---Faza6----------------------------------------------\n";
    CloudService csFile("IaaS", 78, "ALG", 36.99); // creare obiect
    csFile.displayCS();
    cout << endl;
    csFile.scriereInFisierText("cloud.txt"); // scriere fisier txt;
    csFile.citireDinFisierText("cloud.txt"); // citire fisier txt;
    csFile.displayCS();
    cout << endl;
    Router routerFile("Wired", 12, "GigaByte");
    routerFile.displayR();
    cout << endl;
    routerFile.scriereInFisierText("router.txt");
    cout << endl;
    routerFile.citireDinFisierText("router.txt");
    routerFile.displayR();
    cout << endl;
    routerFile.sFB("router.bin"); // scrire fisier binar;
    routerFile.cFB("router.bin"); // citire fisier binar;
    cout << "-----------------------------Clase derivate-----Faza 7.------------------------------------\n";
    cout << endl;
    Router::setVitezaMaxima(450);
    AdvancedRouter ar; // creare obiect pentru clasa derivata;
    ar.setSupport5G(true);
    cout << "Router are suport 5G: ->> " << ar.getSupport5G() << endl;
    ar.displayR();
    cout << endl;
    AdvancedRouter ar1("Wireless", 16, "NitroSockets", true); // creare obiect2 pentru clasa derivata 'AdvancedRouter';
    ar1.displayR();
    cout << endl;
    ar = ar1;
    ar.displayR();
    cout << "--------------------------Upcastig---------------------------------------------------------------\n";
    Router *routerBase = new AdvancedRouter("Wireless", 10, "RouterTech", true);
    routerBase->displayR();
    cout << endl;
    routerBase = &ar1; // referinta unei  obiect din clasa derivata 'AdvancedRouter;
    routerBase->setNrPorturi(24);
    routerBase->setProducator("NitroUpg");
    routerBase->setVitezaMaxima(2000);
    *routerBase = *routerBase + 5;
    *routerBase = *routerBase - 1;
    optimizeazaBanda(*routerBase, 5000);
    routerBase->scriereInFisierText("routerBase.txt");
    routerBase->citireDinFisierText("routerBase.txt");
    cout << endl;
    routerBase->sFB("routerBinaryFile.bin");
    routerBase->cFB("routerBinaryFile.bin");
    cout << endl;
    routerBase->displayR();
    cout << endl;
    cout << "Nr. Porturi routerBase: -> " << routerBase->getNrPorturi() << endl;
    cout << "Noul fabricant pentru routerBase-> " << routerBase->getProducator() << endl;
    cout << "Viteza router, routerBase: -> " << routerBase->getVitezaMaxima() << " Mbps \n";

    delete routerBase;
    cout << endl;
    PortableRouter pr("Wired", 8, "ModuloRouter", false, 1500);
    pr.setCapacitateBaterie(1600);
    cout << endl;
    pr.displayR();
    cout << "Durata: ->> " << pr.calculeazaDurata(5) << " de minute. \n";
    cout << endl;
    PortableRouter pr1("Wireless", 16, "RX-R", true, 9000);
    Router *RR = &pr1; // referinta unui obiect din clasa derivata; // upcasting;
    RR->setNrPorturi(24);
    RR->setProducator("RX-R+");
    RR->setVitezaMaxima(2500);
    *RR = *RR - 4; // overloading operator (-);
    *RR = *RR + 2; // overloading operator (+);
    RR->scriereInFisierText("PortableRouter.txt");
    RR->citireDinFisierText("PortableRouter.txt");
    cout << endl;
    RR->displayR();

    delete RR;

    return 0;
}