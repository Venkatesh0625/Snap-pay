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
using namespace std;
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

void file_modify(Snap_Accnt& snap)
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


bool login(Snap_Accnt& snap)
{
    fstream file;
    Snap_Accnt Accnt;
    json_class json;
    string id,pwd,str;
    char pw[20];
    int f=0,i=0;
    cout<<"\n\tEnter ID : ";
    getline(cin,id);
    cout<<"\n\tEnter Password : ";
    char ch;
    ch=getch();
    while(ch!=13)
    {
        pw[i]=ch;
        cout<<"*";
        ch=getch();
        i++;
    }
    pw[i]='\0';
    file.open("E:/Snap.txt",ios::in);
    while(file>>str)
    {
        json.json = str;
        json.slice();
        Accnt.retrieve_json(json);
        if(Accnt.get_id() == id && Accnt.get_password() == pw)
        {
            snap = Accnt;
            f=1;
            break;
        }
    }
    //returns 1 if the username and password are correct
    if(f==1)
    {
        file.close();
        return 1;
    }
    else
    {
        cout<<"\n\tPassword Incorrect \n" ;
        delay(1000);
        system("cls");
        file.close();
        return 0;
    }
}
int main()
{
    int opt;
    float amt;
    Contact cont;
    fstream file;
    string mobile;
    //These 2 Functions Holds the Information of Current login user
    Bank_Accnt bank;
    Snap_Accnt snap,s;
    bool flag=0,f=0,flag1=0,end=0;
    json_class json;
    do
    {
        flag=0;
        system("cls");
        cout<<"\t\t\tWELCOME TO SNAP PAY ";
        cout<<"\n\t1.Login \n\n\t2.Sign Up\n\n\t3.Create Bank Account\n\n\t4.Exit\n\n\t";
        cin>>opt;
        getchar();
        if(opt==1)
        {
            if(login(snap)==0)
                flag=1;
            else
            {
                Bank_Accnt b;
                cout<<"\n\n\t\t\t\tLogin Successful \n";
                //opens the bank file to check for the mobile no in the snap file
                file.open("E:/bank.txt",ios::in);
                while(file>>json.json)
                {
                    json.slice();
                    b.retrieve_json(json);
                    if(bank.get_mob_no() == snap.get_mob_no())
                        break;
                }
                file.close();
                bank = b;
            }
            cout<<"\n\n\t";
            system("pause");

        }
        else if(opt==2)
        {
            //snap accnt creation
            cin>>snap;
            flag=1;
            cout<<"\n\n\t";
            system("pause");
        }
        else if(opt==3)
        {
            //creates bank accnt
            Bank_Accnt b;
            cin>>b;
            cout<<"Bank Account Created Successfully ";
            delay(1000);
            flag=1;
            cout<<"\n\n\t";
            system("pause");
        }
        else
            exit(0);
    }
    while(flag==1);
    Bank_Accnt b;
    file.open("E:/bank.txt",ios::in);
    while(file>>json.json)
    {

        json.slice();
        b.retrieve_json(json);
        if(snap.get_mob_no() == b.get_mob_no())
            break;
    }
    file.close();
    bank = b;

    cout<<snap;
    do
    {
        flag1=0;
        bool flag2=0;
        cout<<"\n\n\t";
        system("pause");
        system("cls");
        cout<<"\n\n\t\t\tMenu ";
        cout<<"\n\n\t1.Send Money \n\n\t2.Add A Contact to this Device \n\n\t3.Send Money By Contacts\n\n\t4.Modify Account Details \n\n\t5.Transaction Details\n\n\t6.Exit\n\n\tEnter Option : ";
        cin>>opt;
        if(opt==1)
        {
            getchar();
            do
            {
                flag2=0;
                if(opt==1)
                {
                    try
                    {
                        cout<<"\n\tEnter Mobile Number to send Money : ";
                        getline(cin,mobile);
                        for(int i=0;i<mobile.size();i++)
                        {
                            if((!(mobile[i]>47 && mobile[i]<58)) && mobile.size()!=10)
                                throw(1);
                        }
                    }
                    catch(int)
                    {
                        cout<<"\n\tInvalid Input";
                        flag2=1;
                    }
                }
                cout<<"\n\n\t";
            }
            while(flag2==1);
            cout<<"\n\n\tEnter the Amount to be Transferred : ";
            cin>>amt;
            pay(bank,mobile,amt);
            cout<<"\n\n\t";
        }
        else if(opt==3)
        {
            int opt2;
            for(int i=0;i<cont.nbr_cont;i++)
                cout<<"\n\n\t"<<i+1<<" . "<<cont.contacts[i].get_name();
            cout<<"\n\n\tSelect A Contact Index To send Money ";
            cin>>opt2;
            getchar();
            cout<<"\n\n\tEnter the Amount to be Transferred : ";
            cin>>amt;
            //Calling The Pay Function getting number from Contact information
            pay(bank,cont[opt2-1],amt);
            cout<<"\n\n\t";
        }
        else if(opt==2)
        {
            cont.add_contact();
            cout<<"\n\n\tFinished Adding\n\n";
            cout<<"\n\n\t";
            system("pause");
        }
        else if(opt==4)
        {
            int l,flag=0;

            do
            {
                cout<<"\n\n\tDo you want to change the \n\n\t1.Name  \n\n\t2.Password:\n\n\tEnter Option : ";
                cin>>l;
                getchar();
                if(l==1)
                {
                    snap.change_name();
                    file_modify(snap);
                }
                else if(l==2)
                {
                    snap.change_password();
                    file_modify(snap);
                }
                else
                    flag=1;
                cout<<"\n\n\t";
                system("pause");

            }while(flag==1);
        }
        else if(opt==5)
        {
            show_transactions(bank.get_mob_no());
        }
        else
        {
            flag1=1;
        }
    }
    while(!flag1);
    return 0;
}
