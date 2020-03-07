#include "datime.h"
#include<iostream>
#include<ctime>
using namespace std;

Datime::Datime()
{
    dd=0;
    m=0;
    hh=0;
    mm=0;
    ss=0;
    yy=0;
}
void Datime::get_localtime()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    yy=1900 + ltm->tm_year;
    m=1 + ltm->tm_mon;
    dd=ltm->tm_mday;
    hh=ltm->tm_hour;
    mm=ltm->tm_min;
    ss=ltm->tm_sec;
}

void Datime::retime(string str)
{
    dd = (str[0]-48)*10 + (str[1]-48);
    m  = (str[3]-48)*10 + (str[4]-48);
    yy = (str[6]-48)*1000 + (str[7]-48)*100 + (str[8]-48)*10 +(str[9]-48);
    hh = (str[11]-48)*10 + (str[12]-48);
    mm = (str[14]-48)*10 + (str[15]-48);
    ss = (str[17]-48)*10 + (str[18]-48);
}

string Datime::form_time()
{
    string str;
    int y=yy;
    str.push_back(dd/10+48);
    str.push_back(dd%10+48);
    str.push_back('.');
    str.push_back(m/10+48);
    str.push_back(m%10+48);
    str.push_back('.');
    str.push_back(y/1000+48);
    y=y%1000;
    str.push_back(y/100+48);
    y=y%100;
    str.push_back(y/10+48);
    str.push_back(y%10+48);
    str.push_back(':');
    str.push_back(hh/10+48);
    str.push_back(hh%10+48);
    str.push_back('.');
    str.push_back(mm/10+48);
    str.push_back(mm%10+48);
    str.push_back('.');
    str.push_back(ss/10+48);
    str.push_back(ss%10+48);
    return str;
}
