#ifndef CONTACT_H
#define CONTACT_H
#include<iostream>
#include "user.h"
#include "json.h"
using namespace std;

class Contact
{
    public:
        user *contacts;
        //NUmber of Contacts
        int nbr_cont;
        Contact();
        void add_contact();
        string operator[](int);


};

#endif // CONTACT_H
