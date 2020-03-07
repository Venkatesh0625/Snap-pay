#include<iostream>
#include<time.h>
#include<fstream>
#include<stdlib.h>
#include<process.h>
#include<stdio.h>
#include "bank.h"
#include "snap.h"
#include "json.h"
#include "contact.h"
#include "transaction.h"
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while(goal > clock());
}

void file_modify(Bank_Accnt& sender,Bank_Accnt& receiver,float amt)
{
    Transaction t;
    fstream file,f;
    Bank_Accnt Accnt;
    json_class json;
    //Initialising Required things to Transaction Object
    t.put_mob_no1(sender.get_mob_no());
    t.put_mob_no2(receiver.get_mob_no());
    t.Time.get_localtime();
    t.put_amount(amt);
    t.Create_json(json);
    //Writing into A file
    file.open("E:/Transactions.txt",ios::out | ios::app);
    file<<json.json;
    file<<"\n";
    file.close();
    file.open("E:/bank.txt",ios::in);
    f.open("E:/temp.txt",ios::out);
    while(getline(file,json.json))
    {
        json.slice();
        Accnt.retrieve_json(json);
        if(Accnt.get_mob_no()!=sender.get_mob_no() && Accnt.get_mob_no()!=receiver.get_mob_no())
        {
            f<<json.json;
            f<<"\n";
        }
    }
    json.json = "{";
    sender.Create_json(json);
    json.end();
    f<<json.json;
    f<<"\n";

    json.json = "{";
    receiver.Create_json(json);
    json.end();
    f<<json.json;
    f<<"\n";
    file.close();
    f.close();
    file.open("E:/bank.txt",ios::out);
    f.open("E:/temp.txt",ios::in);
    while(getline(f,json.json))
    {
        file<<json.json;
        file<<"\n";
    }
    f.close();
    file.close();
    remove("E:/temp.txt");

}

void snap_file_modify(Snap_Accnt snap)
{
    Snap_Accnt s;
    json_class json;
    fstream file,f;
    bool flag=0;
    file.open("E:/Snap.txt",ios::in);
    f.open("E:/tmp.txt",ios::out);
    while(file>>json.json)
    {
        json.slice();
        s.retrieve_json(json);
        if(s.get_mob_no() != snap.get_mob_no())
        {
            f<<json.json;
            f<<"\n";
        }
    }
    json.json = "{";
    snap.Create_json(json);
    f<<json.json;
    f<<"\n";
    f.close();
    file.close();
    remove("E:/Snap.txt");
    rename("E:/tmp.txt","E:/Snap.txt");
}
int pay(Bank_Accnt bank,string mobile,float amt)
{
    fstream file;
    json_class json;
    bool f=0;
    Bank_Accnt b;
    Snap_Accnt s;

    file.open("E:/Snap.txt",ios::in);
    while(file>>json.json)
    {
        json.slice();
        s.retrieve_json(json);
        if(s.get_mob_no() == mobile)
        {
            f =1;
            break;
        }
    }
    file.close();
    if(f==0)
    {
        cout<<"\n\n\tThe Entered Number is not Registered With Snap ";
        delay(3000);
        return 0;
    }
    file.open("E:/bank.txt",ios::in);
    while(file>>json.json && f)
    {
        json.slice();
        b.retrieve_json(json);
        if(b.get_mob_no() == mobile)
        {
            if(bank.get_balance()>=amt)
            {

                bank.withdraw(amt);
                b.deposit(amt);
                file_modify(b,bank,amt);
                cout<<"\n\tTransfer Successful ";
                file.close();
                break;
            }
            else
            {
                cout<<"\n\n\tYour balance is not enough to proceed this Transaction ";
                file.close();
                return 0;
                break;
            }
        }
    }
    return 1;
}

void show_transactions(string mobile)
{
    Transaction t;
    bool f=0;
    fstream file;
    json_class json;
    file.open("E:/Transactions.txt",ios::in);
    while(getline(file,json.json))
    {
        json.slice();
        t.retrieve_json(json);
        if(t.get_mob_no1() == mobile || t.get_mob_no2() ==mobile)
        {
            cout<<t;
            f=1;
        }
    }
    if(f==0)
        cout<<"\n\n\tNo Transactions Found in your Account ";
    file.close();
    return;
}
