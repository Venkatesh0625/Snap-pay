#include<iostream>
#include<fstream>
#include<stdio.h>
#include "snap.h"
#include "bank.h"
using namespace std;


Snap_Accnt::Snap_Accnt()
{
    id = "\0";
    password = "\0";
    created = 0;
}
void Snap_Accnt::retrieve_json(json_class& js)
{
    id = js["Snap_id"];
    Accnt_no = js["Accnt_no"];
    name = js["Name"];
    mob_no = js["Mobile"];
    bank_name = js["Bank_Name"];
    ifsc_code = js["Ifsc"];
    password = js["Password"];
}
void Snap_Accnt::Create_json(json_class& js)
{
    js("Snap_id",id);
    js("Accnt_no",Accnt_no);
    js("Name",name);
    js("Mobile",mob_no);
    js("Bank_Name",bank_name);
    js("Ifsc",ifsc_code);
    js("Password",password);
    js.end();
    cout<<js.json<<endl<<endl<<"SnapAccnt\n";
}


ostream& operator<<(ostream& out,Snap_Accnt& Accnt)                  //display the details
{
    out<<"\n\n\tUser id : "<<Accnt.id;
    out<<"\n\n\tBank Account Number : "<<Accnt.Accnt_no;
    out<<"\n\n\tName : "<<Accnt.name;
    out<<"\n\n\tMobile Number : "<<Accnt.mob_no;
    out<<"\n\n\n";
}

istream& operator>>(istream& in,Snap_Accnt& Accnt)
{
    int flag=0;
    bool f1,f2;
    fstream file;
    string tmp,temp;
    json_class json,json_form;
    string js;
    char ch;
    Bank_Accnt bank;
    //Temperory objects
    Snap_Accnt snap;
    cout<<"\t\t\tSnap Account Creation :\n";

    do
    {
        flag=0;
        cout<<"\n\n\tEnter Mobile Number Registered With Bank Accnt :";
        getline(cin,tmp);
        try
        {
            for(int i=0;i<tmp.size();i++)
            {
                //Checking whether the String Contains Numbers only
                if((!(tmp[i]>47 && tmp[i]<58)) && tmp.size()!=10)
                    //Throwing Error
                    throw(1);
            }
        }
        catch(int x)
        {
            cout<<"\n\tInvalid Input ";
            flag=1;
        }
    }
    while(flag==1);
    flag=0;
    file.open("E:/bank.txt",ios::in);
    while(file>>js)
    {
        json.json = js;
        json.slice();
        bank.retrieve_json(json);
        if(bank.get_mob_no()==tmp)
        {
            flag=1;
            break;
        }
    }
    file.close();
    if(flag==1)
    {
        cout<<"\n\n\tAccount Found \n";
        cout<<bank;
        do
        {
            tmp.clear();
            flag=0;
            try
            {
                cout<<"\n\n\tEnter Internet Password : ";
                cin>>tmp;
                if(bank.get_password()==tmp)
                {
                    cout<<"\n\tAccount Verification Done ...\n";
                    flag=2;
                }
                else
                {
                    throw(1);
                }
            }
            catch(int x)
            {
                cout<<"\n\tIncorrect,do u want to Continue ?(y/n) ";
                ch=getch();
                if(ch=='y')
                    flag=1;
                else
                    flag=2;
            }
        }
        while(flag==1);
        //Creating New user id
        if(flag==2)
        {
            do
            {
                flag=0;
                try
                {
                    cout<<"\n\tCreate User id : ";
                    getchar();
                    getline(cin,tmp);
                    if(tmp.size()<5 && tmp.size()>10)
                    {
                        throw(1);
                    }
                    file.open("E:/Snap.txt",ios::in);
                    //Checking whether the given id exists Already
                    while(file>>json.json)
                    {
                        json.slice();
                        snap.retrieve_json(json);
                        if(snap.get_id() == tmp)
                            throw(1.1f);
                    }
                }
                catch(int x)
                {
                    cout<<"\n\tInvalid  ";
                    flag=1;

                }
                catch(float x)
                {
                    cout<<"\n\n\tUser Name Already Exists ";
                    flag=1;
                }
                file.close();
            }
            while(flag==1);
            do
            {
                flag=0;
                temp.clear();
                flag=0;
                try
                {
                    cout<<"\n\tCreate a password : ";
                    getline(cin,temp);
                    if(temp.size()<8 && temp.size()>24)
                    {
                        throw(1);
                    }
                }
                catch(int x)
                {
                    cout<<"\n\tInvalid ";
                    flag=1;
                }
            }
            while(flag==1);
            Accnt.password = temp;
            Accnt.id = tmp;
            //Copying Data s from Bank details
            Accnt.put_name(bank.get_name());
            Accnt.Accnt_no = bank.get_Accnt_no();
            Accnt.put_mob_no(bank.get_mob_no());;
            Accnt.put_bank_name(bank.get_bank_name());
            Accnt.put_bank_name(bank.get_ifsc_code());
            cout<<Accnt;
            cout<<"\n\tSnap Pay Account Created \n";
            file.open("E:/Snap.txt",ios::out | ios::app);
            Accnt.Create_json(json_form);
            file<<json_form.json;
            file<<"\n";
            file.close();
            //Slicing to Seperate the key and value from json
            json_form.slice();
            Accnt.retrieve_json(json_form);
            //cout<<Accnt;
            Accnt.created = 1;
        }
    }
    else
    {
        int opt;
        cout<<"\tAccount Not Found \n\t1.Re-Enter Mobile Number \n\n\t2.Return Main Menu\n\t";
        cin>>opt;
        getchar();
        switch(opt)
        {
            //Calling Again if we hit option of re entering else returning to main
            case 1: cin>>Accnt;
                    break;
            case 2: Accnt.created =0;
                    break;
        }
    }
}
void Snap_Accnt::change_name()
{
    bool flag=0;
    fstream file,f;
    json_class json;
    string str,temp;
    Snap_Accnt snap;
    str = id;
    do
    {

        flag=0;
        try
        {
            cout<<"\n\tEnter the new id : ";
            getline(cin,temp);

            if(temp.size()<5 && temp.size()>10)
            {
                    throw(1);
            }
            if(temp == id)
            {
                throw('a');
            }
            file.open("E:/Snap.txt",ios::in);
            //Checking whether the given id exists Already
            while(file>>json.json)
            {
                json.slice();
                snap.retrieve_json(json);
                if(snap.get_id() == temp)
                    throw(1.1f);
            }
            file.close();
        }
        catch(int x)
        {
            cout<<"\n\tInvalid  ";
            flag=1;

        }
        catch(float x)
        {
            cout<<"\n\n\tUser Name Already Exists ";
            flag=1;
        }
        catch(char a)
        {
            cout<<"\n\n\tYou are Entering the Old name Again ";
            flag=1;
        }
        id = temp;

    }
    while(flag==1);
}
void Snap_Accnt::change_password()
{
    bool flag=0;
    fstream file,f;
    json_class json;
    string str_password,temp;
    Snap_Accnt snap;
    do
    {
        //For Changinf the password Asking for old Password
        flag=0;
        try
        {
            cout<<"\n\n\t Enter the old password : ";
            cin>>str_password;
            getchar();
            cout<<"\n\tEnter the new password : ";
            getline(cin,temp);
            if(temp.size()<8 && temp.size()>24)
            {
                throw(1);
            }
            if(temp == id)
            {
                throw('a');
            }
            if(str_password!=password)
            {
                throw(1.2341234);
            }
        }
        catch(int x)
        {
            cout<<"\n\n\tInvalid ";
            flag=1;
        }
        catch(char)
        {
            cout<<"\n\n\tCreate a password that you have not used";
            flag=1;
        }
        catch(double)
        {
            cout<<"\n\n\tOld Password Incorrect ";
            flag=1;
        }
        password=temp;

    }
    while(flag==1);
}

