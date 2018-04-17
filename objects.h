#ifndef OBJECTS_H
#define OBJECTS_H
#include "mainwindow.h"

#include <string>

using namespace std;

class Library
{
public:
    Library() {}
};
class Patron
{
private:
    string name;
    string email;
    string password;
    int debt;
    int userlvl;

public:
    Patron() {}

    //    Patron(string inEmail, string inPassword, int inDebt, int inUserlvl) {
//        this->email = inEmail;
//        this->password = inPassword;
//        this->debt = inDebt;
//        this->userlvl = inUserlvl;
//    }

    void setName(string inName);
    void setEmail(string inEmail);
    void setPassword(string inPassword);
    void setDebt(int inDebt);
    void setUserlvl(int inUserlvl);
    void clear();

    string getName();
    string getEmail();
    string getPassword();
    int getDebt();
    int getUserlvl();

};
class Book
{
public:
    Book() {}
};
class Transaction
{
public:
    Transaction() {}
};
#endif // OBJECTS_H
