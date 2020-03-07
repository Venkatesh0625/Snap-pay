#ifndef USER_H
#define USER_H
#include<iostream>
using namespace std;

class user
{
    protected:
        string name;
        string mob_no;
    public:
        string get_name(){ return name; }
        string get_mob_no(){ return mob_no; }
        void put_name(string name){ this->name=name;}
        void put_mob_no(string mob_no){ this->mob_no=mob_no;}
        friend class Contact;
};


#endif // USER_H
