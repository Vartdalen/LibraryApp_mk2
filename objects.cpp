#include "objects.h"

// PATRON CLASS
//Patron::Patron(){}

string Patron::getName(){
    return this->name;
}

string Patron::getEmail(){
    return this->email;
}

string Patron::getPassword(){
    return this->password;
}

int Patron::getDebt(){
    return this->debt;
}

int Patron::getUserlvl(){
    return this->userlvl;
}

void Patron::setName(string inName){
    this->name = inName;
}

void Patron::setEmail(string inEmail){
    this->email = inEmail;
}

void Patron::setPassword(string inPassword){
    this->password = inPassword;
}

void Patron::setDebt(int inDebt){
    this->debt = inDebt;
}

void Patron::setUserlvl(int inUserlvl){
    this->userlvl = inUserlvl;
}

void Patron::clear(){
    this->name = "0";
    this->email = "0";
    this->password = "0";
    this->debt = 0;
    this->userlvl = 0;
}
