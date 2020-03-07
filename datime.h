#ifndef DATIME_H
#define DATIME_H
#include<iostream>
using namespace std;

class Datime
{
    public:
        int dd,m,hh,mm,ss,yy;
        void get_localtime();
        void retime(string);
        string form_time();
        Datime();
};

#endif // DATIME_H
