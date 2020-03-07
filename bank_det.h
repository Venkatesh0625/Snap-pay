#ifndef BANK_DET_H
#define BANK_DET_H
#include<iostream>
using namespace std;

class bank_det
{
    protected:
        string bank_name;
        string ifsc_code;
        string Accnt_no;
    public:
        bank_det()
        {
            bank_name = "\0";
            ifsc_code = "\0";
            Accnt_no = "\0";
        }
        string get_bank_name(){ return bank_name; }
        string get_ifsc_code(){ return ifsc_code; }
        void put_bank_name(string bank_name){ this->bank_name=bank_name;}
        void put_ifsc_code(string ifsc_code){ this->ifsc_code=ifsc_code;}
        string get_Accnt_no(){ return Accnt_no; }

};

#endif // BANK_DET_H
