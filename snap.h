#ifndef SNAP_H
#define SNAP_H
#include<iostream>
#include<conio.h>
#include "user.h"
#include "bank_det.h"
#include "json.h"
using namespace std;

class Snap_Accnt : public bank_det , public user
{
        string id;
        string password;
    public:
        bool created;
        Snap_Accnt();
        void retrieve_json(json_class&);
        void Create_json(json_class&);
        friend class Bank_Accnt;
        friend class json_class;
        string get_id(){ return id; }
        string get_password(){ return password; }
        void change_name();
        void change_password();
        friend istream& operator>> (istream&,Snap_Accnt&);
        friend ostream& operator<< (ostream&,Snap_Accnt&);
};

#endif // SNAP_H
