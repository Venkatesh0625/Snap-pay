#ifndef BASIC_H
#define BASIC_H
#include<iostream>
#include<math.h>
using namespace std;
class basic
{
public:
    int a,b;
string digitalize(float balance)
{

    int a[10],i=0;
    int b=(int)balance;
    if(b==0)
    {
        a[0]=1;
        a[1]=0;
    }
    else
    {
        while(b!=0)
        {
            i++;
            a[i] = b%10;
            b=b/10;
        }
        a[0]=i;
    }
    string str;
    for(i=a[0];i>0;i--)
    {
        str.push_back(a[i]+48);
    }
    str.push_back('.');
    balance=balance-(int)balance;
    for(;i<6;i++)
    {
        balance*=10;
        str.push_back((int)(balance)%10+48);
    }
    return str;
}


float redigit(string str)
{
    if(str=="0.000000")
        return(0.0);
    int i,n=str.size();
    float balance,temp=0,result;
    for(i=0;i<6;i++)
    {
        temp+=((str[n-1-i]-48)*pow(10,i));
    }
    for(i=n-8;i>=0;i--)
    {
        balance+=(str[i]-48)*pow(10,n-8-i);
    }
    result = balance + (float)((float)temp/pow(10,6));
    return result;
}
};
#endif // BASIC_H
