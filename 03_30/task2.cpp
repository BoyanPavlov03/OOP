#include<iostream>

class BankAccount {
    private:
        char* name;
        char* accountnum;
        double balance;
    public:

    BankAccount(const char* name = "\0", const char* accountnum = "\0", double balance = 0);
    BankAccount(const BankAccount& other);
    ~BankAccount();
    BankAccount& operator=(const BankAccount& other);
};

BankAccount::BankAccount(const char* name, const char* accountnum, double balance)
: name(new char[strlen(name) + 1]), 
  accountnum(new char[strlen(accountnum) + 1]), 
  balance(balance) {

    strcpy(this->name, name);
    strcpy(this->accountnum, accountnum);
}

BankAccount::BankAccount(const BankAccount& other)
: name(new char[strlen(other.name) + 1]), 
  accountnum(new char[strlen(other.accountnum) + 1]), 
  balance(other.balance) {

    strcpy(this->name, other.name);
    strcpy(this->accountnum, other.accountnum);
}

BankAccount::~BankAccount() {
    delete[] name;
    delete[] accountnum;
}

BankAccount& BankAccount::operator=(const BankAccount& other) {
    if (&other != this) {
        delete[] name;
        delete[] accountnum;

        name = new char[strlen(other.name) + 1];
        accountnum = new char[strlen(other.accountnum) + 1];
        strcpy(name, other.name);
        strcpy(accountnum, other.accountnum);
        balance = other.balance;
    }

    return *this;
}

int main() {
    return 0;
}