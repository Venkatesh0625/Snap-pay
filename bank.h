#ifndef BANK_H
#define BANK_H
#include<iostream>
#include "datime.h"
#include "user.h"
#include "bank_det.h"
#include "json.h"
#include "basic.h"
#include "snap.h"
using namespace std;

class Bank_Accnt : public user , public bank_det
{

    protected:
        string password;
        float balance;

        string internet_id;
    public:
        Datime open_time;
        string get_password(){ return password; }
        float get_balance(){ return balance; }
        string get_internet_id(){ return internet_id; }
        int deposit(float Amount);
        int withdraw(float Amount);
        void Create_json(json_class&);
        void retrieve_json(json_class&);
        Bank_Accnt();
        friend class Snap_Accnt;
        friend class json_class;
        friend istream& operator >>(istream&,Bank_Accnt&);
        friend ostream& operator <<(ostream&,Bank_Accnt&);

};

#endif // BANK_H
