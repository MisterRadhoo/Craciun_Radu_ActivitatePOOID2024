
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

// blueprint bankAccount; class BANK;
class BANK
{
private:
    string *accHolderName;
    int *accountNumber; // private members;
    double *balance;
    string *transactions;
    int transactionCount;

public:
    BANK(const string &name, int accNr, double bal)
    {
        this->accHolderName = new string(name); // alocare dinamica de spatiu pentru pointer
        this->accountNumber = new int(accNr);
        this->balance = new double(bal);
        this->transactions = new string[200]; //  o asumare, un maxim de 200 de tranzactii,
        this->transactionCount = 0;
        addTransaction("Account created with balance: $" + formatAmount(bal));
    }
    // Copy costructor;
    BANK(const BANK &obj)
    {
        this->accHolderName = new string(*(obj.accHolderName)); // alocare spatiu de memorie pentru pointer catre string;
        this->accountNumber = new int(*(obj.accountNumber));
        this->balance = new double(*(obj.balance));
        this->transactions = new string[200];
        this->transactionCount = obj.transactionCount;
        for (int i = 0; i < this->transactionCount; i++)
        {
            transactions[i] = obj.transactions[i];
        }
    }
    // Destructor - free memory
    ~BANK()
    {
        delete accHolderName;
        delete accountNumber;
        delete balance;
        delete[] transactions;
        cout << "Memory released. " << endl;
    }
    // Formator pentru sume de bani cu (2 zecimale);
    string formatAmount(double amount) const
    {
        ostringstream stream;                         // creaza un string stream;
        stream << fixed << setprecision(2) << amount; // limiteaza formatul cu zecimale la dupa . la 2.
        return stream.str();                          // returneaza suma formata ca string (convertita in string);
    }
    void addTransaction(const string &transaction)
    {
        if (this->transactionCount < 200)
        {
            this->transactions[transactionCount++] = transaction;
        }
        else
        {
            cout << "Transaction history is full!! " << endl;
        }
    }
    // function to deposit money;
    void deposit(double _amount)
    {
        *balance += _amount;
        string transaction = "Deposited: $" + formatAmount(_amount) + ". New balance: $" + formatAmount(*balance);
        addTransaction(transaction);
        cout << transaction << endl;
    }
    // Function to withdraw money;
    void withdraw(double amount)
    {
        if (amount > *balance)
        {
            cout << "Insufficient funds!" << endl;
        }
        else
        {
            *balance -= amount;
            string transaction = "Withdrew: $" + formatAmount(amount) + ". Remaining balace: $" + formatAmount(*balance);
            addTransaction(transaction);
            cout << transaction << endl;
        }
    }
    void printStatement() const
    {
        cout << "Account Statement for: " << *accHolderName << " (Account Number: " << *accountNumber << "):\n";
        for (int i = 0; i < this->transactionCount; i++)
        {
            cout << this->transactions[i] << endl;
        }
    }
    void display() const
    {
        cout << "Account Holder: " << *accHolderName << endl;
        cout << "Account Number: " << *accountNumber << endl;
        cout << "Balance: $ " << formatAmount(*balance) << endl;
    }
};
int main()
{
    BANK acc1("Craciun Radu", 1000, 1500.58);
    acc1.display();
    acc1.deposit(6700.65);
    acc1.withdraw(20);
    acc1.withdraw(1500);
    cout << "\nPrinting Stament for account: \n";
    acc1.printStatement();
    cout << endl;
    BANK acc2 = acc1;
    acc2.deposit(1760);
    acc2.display();
    cout << endl;
    acc2.printStatement();

    return 0;
}