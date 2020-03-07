#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "bank.h"
basic b;
Bank_Accnt::Bank_Accnt()
{
    password = "\0";
    internet_id = "\0";
    balance = 0.0;
}
void Bank_Accnt::retrieve_json(json_class& js)
{
    Accnt_no = js["Accnt_no"];
    name = js["Name"];
    mob_no = js["Mobile"];
    internet_id = js["Internet_id"];
    password = js["Password"];
    bank_name = js["Bank_name"];
    balance = b.redigit(js["Balance"]);
    ifsc_code = js["Ifsc"];
    open_time.retime(js["Time"]);
}
void Bank_Accnt::Create_json(json_class& js)
{
    js("Accnt_no",Accnt_no);
    js("Name",name);
    js("Mobile",mob_no);
    js("Internet_id",internet_id);
    js("Password",password);
    js("Bank_name",bank_name);
    js("Balance",b.digitalize(balance));
    js("Ifsc",ifsc_code);
    js("Time",open_time.form_time());
    js.end();
}
int Bank_Accnt::deposit(float balance)
{
    this->balance+=balance;
}

int Bank_Accnt::withdraw(float balance)
{
    if(this->balance>=balance)
    {
        this->balance-=balance;
        return 1;
    }
}

ostream& operator <<(ostream& out,Bank_Accnt& Accnt)
{
    out<<"\n\n\t\t\tBank Account Details ";
    out<<"\n\n\tAccount Number : "<<Accnt.Accnt_no;
    out<<"\n\n\tHolders Name : "<<Accnt.name;
    out<<"\n\n\tMobile Number : "<<Accnt.mob_no;
    out<<"\n\n\tBank Name : "<<Accnt.bank_name;
    out<<"\n\n\tIfsc Code : "<<Accnt.ifsc_code;
    out<<"\n\n\tBalance : "<<Accnt.balance;
}
istream& operator >>(istream& in,Bank_Accnt& Accnt)
{
    string js;
    fstream file;
    char ch;
    string tmp;
    json_class json,json_form;
    int flag=0,opt;
    //For temperory use
    Bank_Accnt bank;
    do
    {
        flag=0;
        cout<<"\tSelect the Bank \n\t1.Sbi\n\t2.Sbt\n\t3.Sbk\n\n\tEnter Option : ";
        cin>>opt;
        switch(opt)
        {
            case 1: Accnt.bank_name = "Sbi";
                    break;
            case 2: Accnt.bank_name = "Sbt";
                    break;
            case 3: Accnt.bank_name = "Sbk";
                    break;
            default:cout<<"\tInvalid ..\n";
                    flag=1;
        }
    }while(flag==1);
    flag = 0;
    cout<<"\n\tEnter your Name : ";
    getchar();
    getline(cin,Accnt.name);
    do
    {
        flag=0;
        try
        {
            cout<<"\n\tEnter your Mobile Number : ";
            getline(cin,Accnt.mob_no);
            for(int i=0;i<Accnt.mob_no.size();i++)
            {
                //Checking Whether the Number having an alphabet
                if((!(Accnt.mob_no[i]>47 && Accnt.mob_no[i]<58)) && Accnt.mob_no.size()!=10)
                {
                    throw(1);
                }
            }
            file.open("E:/bank.txt",ios::in);
            //Checking whether the Mobile Number exists Already
            while(file>>json.json)
            {
                json.slice();
                bank.retrieve_json(json);
                if(bank.get_mob_no() == Accnt.mob_no)
                    throw(1.1f);
            }
        }
        catch(int x)
        {
            cout<<"\tInvalid Input \n\n";
            flag=1;
            break;
        }
        catch(float x)
        {
            cout<<"\n\tMobile Number Already Registered ";
            flag=1;
        }
        file.close();
    }
    while(flag==1);
    flag=0;
    do
    {
        try
        {
            flag=0;
            cout<<"\n\tEnter Internet id(Max 10 characters) : ";
            getline(in,Accnt.internet_id);
            //internet id should not start with a number
            if(Accnt.mob_no.size()>10 || Accnt.mob_no.size()<4 || (Accnt.internet_id[0]>48 && Accnt.internet_id[0]<58))
            {
                throw(1);
            }
        }
        catch(int)
        {
            cout<<"\tInvalid Input\n\n";
            flag=1;
        }
    }while(flag==1);
    flag=0;
    do
    {
        try
        {
            flag=0;
            cout<<"\n\tCreate a Password : ";
            getline(in,Accnt.password);
            //password must be greater than 8 and lesser than 24
            if(Accnt.password.size()<8 || Accnt.password.size()>24)
            {
                    throw(1);
            }
        }
        catch(int)
        {
            cout<<"\n\n\tLength is too Short or long\n ";
            flag=1;
        }
    }
    while(flag==1);
    srand(time(0));                                     //Seeding Random number
    for(int i=0;i<13;i++)
    {
        Accnt.Accnt_no.push_back(rand()%10+48);                 //Creating Random Account Number
    }
    Accnt.Accnt_no[13]='\0';
    cout<<"\n\tAccount Number (Generated) : "<<Accnt.Accnt_no<<endl;
    do
    {
        try
        {
            flag=0;
            cout<<"\n\tEnter your Bank's Ifsc Code(11 Characters) : ";      //Getting Ifsc Code
            getline(cin,Accnt.ifsc_code);
            //ifsc code must be exactly 11 characters
            if(Accnt.ifsc_code.size()!=11)
            {
                throw(1);
            }
        }
        catch(int x)
        {
            cout<<"\tInvalid Input \n\n";
            flag=1;
            break;
        }
    }
    while(flag==1);
    cout<<"\n\n\tEnter The Initial Amount to Deposit : ";
    cin>>Accnt.balance;
    cout<<"\n\n\t";
    while(flag==1);
    //Accnt.balance=0.0;
    Accnt.open_time.get_localtime();                        //Getting Local Time
    Accnt.Create_json(json_form);
    json_form.end();
    cout<<json_form.json;
    file.open("E:/bank.txt",ios::out | ios::app);
    file<<json_form.json;
    file<<"\n";
    file.close();
    return in;
}
